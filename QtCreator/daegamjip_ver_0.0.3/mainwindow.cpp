#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "keyboard.h"
#include "ui_keyboard.h"
#include "numpad.h"
#include "ui_numpad.h"
#ifdef RPI_BUILD
#include "gpiohandler.h"
#endif
#include <QEvent>
#include <QKeyEvent>
#include <QApplication>
#include <QVBoxLayout>
#include <QWidget>
#include <QHBoxLayout>
#include <QPushButton>
#include <QSpacerItem>
#include <algorithm>
#include <QTimer>
#include <QDebug>
#include <QMessageBox>
#include <QPropertyAnimation>
#include <QGraphicsOpacityEffect>
#include <QParallelAnimationGroup>
#include <opencv2/imgproc.hpp>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    // Initialize ROS2 node and publishers
    node_ = std::make_shared<rclcpp::Node>("daegamjip_node");
    servo_publisher_ = node_->create_publisher<std_msgs::msg::UInt16>("/servo_cmd", 10);
    mp3_publisher_ = node_->create_publisher<std_msgs::msg::String>("/mp3_cmd", 10);

    // Connect the "돌쇠야 가자" button
    connect(ui->pushButton_3, &QPushButton::clicked, this, &MainWindow::on_pushButton_3_clicked);

    QMovie *movie = new QMovie(":/images/namu.gif");
    ui->namuLabel->setMovie(movie);
    movie->start();

    setFixedSize(1080, 1920); // Set fixed size: width 1080, height 1920

    // Socket setup
    socket = new QTcpSocket(this);
    connect(socket, &QTcpSocket::readyRead, this, &MainWindow::onSocketReadyRead);

    // Create and configure temporary buttons programmatically
    tempPrevButton = new QPushButton("Temp Prev", ui->centralwidget);
    tempPrevButton->setGeometry(10, 540, 100, 30);
    connect(tempPrevButton, &QPushButton::clicked, this, &MainWindow::on_tempPrevButton_clicked);
    tempPrevButton->show();

    tempNextButton = new QPushButton("Temp Next", ui->centralwidget);
    tempNextButton->setGeometry(690, 540, 100, 30);
    connect(tempNextButton, &QPushButton::clicked, this, &MainWindow::on_tempNextButton_clicked);
    tempNextButton->show();

    // --- Language Buttons Setup ---
    m_languageButtonWidget = new QWidget(this);
    QHBoxLayout *cornerLayout = new QHBoxLayout(m_languageButtonWidget);
    cornerLayout->setContentsMargins(0, 0, 10, 0);
    m_koreanButton = new QPushButton(tr("언어 / Lang"));
    cornerLayout->addStretch(1);
    cornerLayout->addWidget(m_koreanButton);
    ui->menubar->setCornerWidget(m_languageButtonWidget);

    connect(m_koreanButton, &QPushButton::clicked, this, &MainWindow::on_koreanButton_clicked);

    translator = new QTranslator(this);

    // --- New Start Page Setup ---
    ui->backgroundLabel->setPixmap(QPixmap(":/images/daegamjip.png"));
    m_currentLanguage = KOREAN;

    QPixmap titlePixmap(":/images/title_kor.png");
    ui->titleLabel->setPixmap(titlePixmap.scaled(ui->titleLabel->size(), Qt::KeepAspectRatio, Qt::SmoothTransformation));

    QPixmap dolsoePixmap(":/images/dolsoe_attention.png");
    ui->dolsoeLabel->setPixmap(dolsoePixmap.scaled(ui->dolsoeLabel->size(), Qt::KeepAspectRatio, Qt::SmoothTransformation));

    ui->dolsoeLabel->hide();
    ui->wakeUpButton->hide();

    m_titleOpacityEffect = new QGraphicsOpacityEffect(ui->titleLabel);
    ui->titleLabel->setGraphicsEffect(m_titleOpacityEffect);
    m_titleAnimation = new QPropertyAnimation(m_titleOpacityEffect, "opacity");
    m_titleAnimation->setDuration(1500);
    m_titleAnimation->setStartValue(0.0);
    m_titleAnimation->setEndValue(1.0);
    m_titleAnimation->setEasingCurve(QEasingCurve::InOutQuad);

    connect(m_titleAnimation, &QPropertyAnimation::finished, this, &MainWindow::showDolsoeAndButton);
    connect(ui->wakeUpButton, &QPushButton::clicked, this, &MainWindow::on_wakeUpButton_clicked);

    QTimer::singleShot(500, this, &MainWindow::startTitleAnimation);

    // --- Keyboard & Numpad Setup ---
    keyboard = new Keyboard(this);
    keyboard->setWindowFlags(Qt::Window | Qt::Tool | Qt::FramelessWindowHint | Qt::WindowStaysOnTopHint);
    numpad = new NumPad(this);
    numpad->setWindowFlags(Qt::Window | Qt::Tool | Qt::FramelessWindowHint | Qt::WindowStaysOnTopHint);

    ui->nameLE->installEventFilter(this);
    ui->numberLE->installEventFilter(this);
    ui->pwLE->installEventFilter(this);
    ui->repwLE->installEventFilter(this);
    ui->numberLE->setEchoMode(QLineEdit::Normal);

    // --- Country ComboBox Setup ---
    countryCodes.insert("대한민국", "+82");
    countryCodes.insert("United States", "+1");
    countryCodes.insert("日本", "+81");
    countryCodes.insert("中国", "+86");

    ui->countryCB->addItem(tr("-- 선택 --"));

    QList<QPair<QString, QString>> sortedCountries;
    for (auto it = countryCodes.constBegin(); it != countryCodes.constEnd(); ++it) {
        sortedCountries.append({it.key(), it.value()});
    }

    std::sort(sortedCountries.begin(), sortedCountries.end(),
              [](const QPair<QString, QString>& a, const QPair<QString, QString>& b) {
        return a.second < b.second;
    });

    for (const auto& pair : sortedCountries) {
        if (pair.first == "대한민국") {
            ui->countryCB->addItem(tr("대한민국"));
            break;
        }
    }

    for (const auto& pair : sortedCountries) {
        if (pair.first != "대한민국") {
            ui->countryCB->addItem(pair.first);
        }
    }

    updatePasswordIndicators(0, m_pwIndicators);
    updatePasswordIndicators(0, m_repwIndicators);
    ui->pwokLabel->clear();

    // --- Video Label Setup ---
    m_videoLabel = new QLabel();
    m_videoLabel->setAlignment(Qt::AlignCenter);
    m_videoLabel->setStyleSheet("background-color: black;");
    m_videoLabel->setFixedSize(1056, 792); // Set fixed size for the camera display area (640x480 * 1.65)

    QVBoxLayout *cameraPageLayout = new QVBoxLayout(ui->cameraPage);
    cameraPageLayout->addStretch(); // Top spacer to push content down
    cameraPageLayout->addWidget(m_videoLabel, 0, Qt::AlignCenter); // Align center, no stretch
    cameraPageLayout->addWidget(ui->cameraLabel, 0, Qt::AlignCenter);
    cameraPageLayout->addWidget(ui->pushButton, 0, Qt::AlignCenter);
    cameraPageLayout->addStretch(); // Bottom spacer to push content up
    ui->cameraPage->setLayout(cameraPageLayout);
    m_videoLabel->hide();

    // --- Video Worker Setup (Create once and reuse) ---
    m_videoThread = new QThread(this);
    m_videoWorker = new VideoWorker("http://10.10.16.129:8080/video_feed");
    m_videoWorker->moveToThread(m_videoThread);

    // When the worker is deleted, delete the thread too
    connect(m_videoWorker, &QObject::destroyed, m_videoThread, &QObject::deleteLater);
    connect(m_videoWorker, &VideoWorker::frameReady, this, &MainWindow::updateFrame);
    m_videoThread->start();

#ifdef RPI_BUILD
    // --- GPIO Handler Setup ---
    m_gpioHandler = new GpioHandler(this);
    if (!m_gpioHandler->initGpio(17, 27, 22)) { // Using pins 17, 27, 22
        qCritical() << "Failed to initialize GPIO handler.";
    }
    connect(m_gpioHandler, &GpioHandler::buttonPressed, this, &MainWindow::onButtonPressed);
    connect(m_gpioHandler, &GpioHandler::learningComplete, this, &MainWindow::onLearningComplete);
#endif

    // --- Timers Setup ---
    m_sequenceTimer = new QTimer(this);
    connect(m_sequenceTimer, &QTimer::timeout, this, &MainWindow::updateCountdown);
    m_sequenceState = Idle;
    m_stateCountdown = 0;

    // --- New Learning Page Setup ---
    m_learningPage = new QWidget();
    m_learningPage->setStyleSheet("background-image: url(:/images/studying.png); background-repeat: no-repeat; background-position: center;");
    QVBoxLayout *learningLayout = new QVBoxLayout(m_learningPage);
    QLabel *learningLabel = new QLabel(tr("영상 학습 중..."));
    learningLabel->setStyleSheet("background-color: transparent;");
    learningLabel->setAlignment(Qt::AlignCenter);
    learningLayout->addWidget(learningLabel);
    ui->stack->addWidget(m_learningPage);

    // --- Letsgo Page Setup ---
    QPixmap carryingPixmap(":/images/carrying.jpg");
    ui->carryingLabel->setPixmap(carryingPixmap.scaledToWidth(1080, Qt::SmoothTransformation));

    QVBoxLayout *letsgoLayout = new QVBoxLayout(ui->letsgoPage);
    letsgoLayout->addStretch();
    letsgoLayout->addWidget(ui->pushButton_3);
    letsgoLayout->setAlignment(ui->pushButton_3, Qt::AlignCenter);
    letsgoLayout->addWidget(ui->carryingLabel);
    letsgoLayout->addStretch();
    ui->letsgoPage->setLayout(letsgoLayout);

    // --- Final Signal & Slot Connections ---
    connect(ui->countryCB, SIGNAL(currentIndexChanged(int)), this, SLOT(on_countryCB_currentIndexChanged(int)));
    connect(ui->pwLE, &QLineEdit::textChanged, this, &MainWindow::handlePasswordChanged);
    connect(ui->repwLE, &QLineEdit::textChanged, this, &MainWindow::handlePasswordChanged);
    connect(ui->nameLE, &QLineEdit::textChanged, this, &MainWindow::checkFormCompleteness);
    connect(ui->countryCB, SIGNAL(currentIndexChanged(int)), this, SLOT(checkFormCompleteness()));
    connect(ui->numberLE, &QLineEdit::textChanged, this, &MainWindow::checkFormCompleteness);
    connect(ui->pwLE, &QLineEdit::textChanged, this, &MainWindow::checkFormCompleteness);
    connect(ui->repwLE, &QLineEdit::textChanged, this, &MainWindow::checkFormCompleteness);
    connect(ui->privacyCheckBox, &QCheckBox::stateChanged, this, &MainWindow::checkFormCompleteness);
    connect(ui->pushButton, &QPushButton::clicked, this, &MainWindow::on_pushButton_clicked);
    connect(ui->next, &QPushButton::clicked, this, &MainWindow::on_next_clicked);
    connect(ui->back, &QPushButton::clicked, this, &MainWindow::on_back_clicked);
    connect(ui->stack, &QStackedWidget::currentChanged, this, &MainWindow::onStackPageChanged);
    connect(ui->pushButton_2, &QPushButton::clicked, this, &MainWindow::on_finishPage_homeButton_clicked);

    m_finishPageTimer = new QTimer(this);
    m_finishPageTimer->setSingleShot(true);
    connect(m_finishPageTimer, &QTimer::timeout, this, &MainWindow::on_finishPage_timeout);

    
    ui->stack->setCurrentIndex(0);
    qApp->installEventFilter(this);
    qDebug() << "MainWindow constructor finished.";
}

MainWindow::~MainWindow()
{
    if (m_videoThread && m_videoThread->isRunning()) {
        QMetaObject::invokeMethod(m_videoWorker, "stop", Qt::QueuedConnection);
        m_videoThread->quit();
        m_videoThread->wait();
    }
#ifdef RPI_BUILD
    // Delete GpioHandler
    if (m_gpioHandler) {
        delete m_gpioHandler;
        m_gpioHandler = nullptr;
    }
#endif
    rclcpp::shutdown();
    delete ui;
}

bool MainWindow::eventFilter(QObject *obj, QEvent *event)
{
    if (event->type() == QEvent::MouseButtonPress) {
        if (obj == ui->nameLE) {
            keyboard->setLineEdit(ui->nameLE);
            keyboard->show();
        } else if (obj == ui->numberLE) {
            numpad->setLineEdit(static_cast<QLineEdit*>(obj), false);
            numpad->move(200, 200);
            numpad->show();
        } else if (obj == ui->pwLE || obj == ui->repwLE) {
            numpad->setLineEdit(static_cast<QLineEdit*>(obj), true);
            numpad->move(200, 200);
            numpad->show();
        }
    }
    return QMainWindow::eventFilter(obj, event);
}

void MainWindow::on_wakeUpButton_clicked()
{
    ui->nameLE->clear();
    ui->countryCB->setCurrentIndex(0);
    ui->numberLE->clear();
    ui->pwLE->clear();
    ui->repwLE->clear();
    ui->privacyCheckBox->setChecked(false);
    ui->stack->setCurrentIndex(1);
}

void MainWindow::startTitleAnimation()
{
    m_titleAnimation->start();
}

void MainWindow::showDolsoeAndButton()
{
    ui->dolsoeLabel->show();
    ui->wakeUpButton->show();

    QPropertyAnimation *dolsoePosAnim = new QPropertyAnimation(ui->dolsoeLabel, "pos");
    dolsoePosAnim->setDuration(1000);
    dolsoePosAnim->setStartValue(QPoint(ui->dolsoeLabel->x(), ui->dolsoeLabel->y() + 100));
    dolsoePosAnim->setEndValue(ui->dolsoeLabel->pos());
    dolsoePosAnim->setEasingCurve(QEasingCurve::OutCubic);

    QGraphicsOpacityEffect *dolsoeEffect = new QGraphicsOpacityEffect(ui->dolsoeLabel);
    ui->dolsoeLabel->setGraphicsEffect(dolsoeEffect);
    QPropertyAnimation *dolsoeFadeAnim = new QPropertyAnimation(dolsoeEffect, "opacity");
    dolsoeFadeAnim->setDuration(1000);
    dolsoeFadeAnim->setStartValue(0.0);
    dolsoeFadeAnim->setEndValue(1.0);

    QPropertyAnimation *buttonPosAnim = new QPropertyAnimation(ui->wakeUpButton, "pos");
    buttonPosAnim->setDuration(1000);
    buttonPosAnim->setStartValue(QPoint(ui->wakeUpButton->x(), ui->wakeUpButton->y() + 100));
    buttonPosAnim->setEndValue(ui->wakeUpButton->pos());
    buttonPosAnim->setEasingCurve(QEasingCurve::OutCubic);

    QGraphicsOpacityEffect *buttonEffect = new QGraphicsOpacityEffect(ui->wakeUpButton);
    ui->wakeUpButton->setGraphicsEffect(buttonEffect);
    QPropertyAnimation *buttonFadeAnim = new QPropertyAnimation(buttonEffect, "opacity");
    buttonFadeAnim->setDuration(1000);
    buttonFadeAnim->setStartValue(0.0);
    buttonFadeAnim->setEndValue(1.0);

    QParallelAnimationGroup *group = new QParallelAnimationGroup(this);
    group->addAnimation(dolsoePosAnim);
    group->addAnimation(dolsoeFadeAnim);
    group->addAnimation(buttonPosAnim);
    group->addAnimation(buttonFadeAnim);

    group->start(QAbstractAnimation::DeleteWhenStopped);
}

void MainWindow::on_next_clicked()
{
    QString serverAddress = "10.10.16.63";
    quint16 serverPort = 5000;

    socket->connectToHost(serverAddress, serverPort);
    qDebug() << "Attempting to connect to server:" << serverAddress << ":" << serverPort;
    if (socket->waitForConnected(3000)) {
        qDebug() << "Successfully connected to server.";
        QString name = ui->nameLE->text();
        QString countryCode = ui->countrynumLE->text();
        QString password = ui->pwLE->text();
        QString message = QString("STORE@%1@%2@%3").arg(name, countryCode, password);
        socket->write(message.toUtf8() + "\n");
        socket->flush();
        ui->stack->setCurrentIndex(ui->stack->indexOf(ui->cameraPage));
        m_languageButtonWidget->setVisible(false);
    } else {
        ui->stack->setCurrentWidget(ui->noRobotPage);
    }
}

void MainWindow::onSocketReadyRead()
{
    QByteArray data = socket->readAll();
    QString response = QString::fromUtf8(data).trimmed();
    qDebug() << "Received from server:" << response;

    if (response == "LEARNING_COMPLETE") {
        ui->stack->setCurrentWidget(ui->finishPage);
    } else if (response == "SHOOTING_COMPLETE") {
        ui->stack->setCurrentWidget(ui->letsgoPage);
    }
}

#ifdef RPI_BUILD
void MainWindow::onLearningComplete()
{
    qDebug() << "Learning complete signal received. Navigating to finish page. Index:" << ui->stack->indexOf(ui->finishPage);
    ui->stack->setCurrentIndex(ui->stack->indexOf(ui->finishPage));
}
#endif

void MainWindow::on_pushButton_3_clicked()
{
    // Publish servo command
    auto servo_message = std_msgs::msg::UInt16();
    servo_message.data = 180;
    servo_publisher_->publish(servo_message);
    RCLCPP_INFO(node_->get_logger(), "Published servo command: '%d'", servo_message.data);

    // Publish MP3 command
    auto mp3_message = std_msgs::msg::String();
    mp3_message.data = "001";
    mp3_publisher_->publish(mp3_message);
    RCLCPP_INFO(node_->get_logger(), "Published MP3 command: '%s'", mp3_message.data.c_str());

    // Send command to server to send password to Dolsoe
    if (socket->state() == QAbstractSocket::ConnectedState) {
        QString message_to_server = "SEND_TO_ROBOT";
        socket->write(message_to_server.toUtf8() + "\n");
        socket->flush();
        qDebug() << "Sent to server:" << message_to_server;
    } else {
        qWarning() << "Socket not connected. Cannot send password request to server.";
    }

    // Navigate to the finish page
    ui->stack->setCurrentWidget(ui->finishPage);
}

void MainWindow::onStackPageChanged(int index)
{
    qDebug() << "onStackPageChanged: index =" << index << ", finishPage index =" << ui->stack->indexOf(ui->finishPage);

    // Stop timer if we are leaving the finish page
    if (m_previousStackIndex == ui->stack->indexOf(ui->finishPage)) {
        m_finishPageTimer->stop();
    }

    if (m_previousStackIndex == ui->stack->indexOf(ui->cameraPage) && !m_isTempNavigation) {
        resetCameraPage();
    }

    if (index == ui->stack->indexOf(ui->cameraPage)) {
        m_videoLabel->show();
        // Signal the existing worker to start processing the video stream.
        QMetaObject::invokeMethod(m_videoWorker, "start", Qt::QueuedConnection);
    } else if (index == ui->stack->indexOf(ui->finishPage)) {
        qDebug() << "Starting finish page timer.";
        m_finishPageTimer->start(5000);
    }

    m_languageButtonWidget->setVisible(index == 0);

    m_previousStackIndex = index;
    m_isTempNavigation = false;
}

void MainWindow::on_pushButton_clicked()
{
#ifdef RPI_BUILD
    if (m_gpioHandler) {
        m_gpioHandler->sendStartRecordingSignal();
    }
#endif
    if (!m_videoLabel) {
        QMessageBox::warning(this, tr("오류"), tr("비디오 위젯이 없어 촬영을 시작할 수 없습니다."));
        return;
    }
    ui->pushButton->setVisible(false);

    ui->cameraLabel->setText(tr(" 촬영을 시작합니다."));
    QTimer::singleShot(1500, this, [this]() {
        m_sequenceState = InitialCountdown;
        m_stateCountdown = 5;
        ui->cameraLabel->setText(tr("%1초 뒤에 촬영을 시작합니다.").arg(m_stateCountdown));
        m_sequenceTimer->start(1000);
    });
}

void MainWindow::updateCountdown()
{
    m_stateCountdown--;

    switch (m_sequenceState) {
    case InitialCountdown:
        if (m_stateCountdown > 0) {
            ui->cameraLabel->setText(tr("%1초 뒤에 촬영을 시작합니다.").arg(m_stateCountdown));
        } else {
            m_sequenceState = Shooting;
            m_stateCountdown = 3;
            ui->cameraLabel->setText(tr(" 촬영 중 (%1)").arg(m_stateCountdown));
        }
        break;
    case Shooting:
        if (m_stateCountdown > 0) {
            ui->cameraLabel->setText(tr(" 촬영 중 (%1)").arg(m_stateCountdown));
        }
        break;
    case Turning:
        if (m_stateCountdown > 0) {
            ui->cameraLabel->setText(tr("제자리에서 360도 천천히 돌아주세요 (%1)").arg(m_stateCountdown));
        }
        break;
    case Recognizing:
    case Idle:
        m_sequenceTimer->stop();
        break;
    }
}

void MainWindow::on_back_clicked()
{
    ui->stack->setCurrentIndex(0);
    m_languageButtonWidget->setVisible(true);
}

void MainWindow::on_tempPrevButton_clicked()
{
    m_isTempNavigation = true;
    int currentIndex = ui->stack->currentIndex();
    int count = ui->stack->count();
    if (count == 0) return;
    int prevIndex = (currentIndex - 1 + count) % count;
    ui->stack->setCurrentIndex(prevIndex);
}

void MainWindow::on_tempNextButton_clicked()
{
    m_isTempNavigation = true;
    QWidget *currentPage = ui->stack->currentWidget();

    if (currentPage == ui->startPage) {
        ui->stack->setCurrentWidget(ui->inputPage);
    } else if (currentPage == ui->inputPage) {
        ui->stack->setCurrentWidget(ui->cameraPage);
    } else if (currentPage == ui->cameraPage) {
        ui->stack->setCurrentWidget(ui->letsgoPage);
    } else if (currentPage == ui->letsgoPage) {
        ui->stack->setCurrentWidget(m_learningPage);
    } else if (currentPage == m_learningPage) {
        ui->stack->setCurrentWidget(ui->finishPage);
    } else if (currentPage == ui->finishPage) {
        ui->stack->setCurrentWidget(ui->noRobotPage);
    } else if (currentPage == ui->noRobotPage) {
        ui->stack->setCurrentIndex(0); // Go back to startPage
    }
}



void MainWindow::on_countryCB_currentIndexChanged(int index)
{
    if (index == 0) {
        ui->countrynumLE->clear();
    }
    else {
        QString selectedCountry = ui->countryCB->currentText();
        ui->countrynumLE->setText(countryCodes.value(selectedCountry));
    }
}

void MainWindow::handlePasswordChanged()
{
    updatePasswordIndicators(ui->pwLE->text().length(), m_pwIndicators);
    updatePasswordIndicators(ui->repwLE->text().length(), m_repwIndicators);

    QString pw = ui->pwLE->text();
    QString repw = ui->repwLE->text();

    if (repw.isEmpty()) {
        ui->pwokLabel->clear();
        return;
    }

    if (pw == repw) {
        ui->pwokLabel->setText(tr("비밀번호가 일치합니다."));
        ui->pwokLabel->setStyleSheet("color: blue;");
    } else {
        ui->pwokLabel->setText(tr("비밀번호가 일치하지 않습니다."));
        ui->pwokLabel->setStyleSheet("color: red;");
    }
}

void MainWindow::checkFormCompleteness()
{
    bool isNameValid = !ui->nameLE->text().isEmpty();
    bool isCountryValid = ui->countryCB->currentIndex() != 0;
    bool isNumberValid = !ui->numberLE->text().isEmpty();
    bool isPwValid = ui->pwLE->text().length() == 4;
    bool isRepwValid = ui->repwLE->text().length() == 4;
    bool isPwMatch = (ui->pwLE->text() == ui->repwLE->text());
    bool isPrivacyChecked = ui->privacyCheckBox->isChecked();

    if (isNameValid && isCountryValid && isNumberValid && isPwValid && isRepwValid && isPwMatch && isPrivacyChecked) {
        ui->next->setEnabled(true);
    } else {
        ui->next->setEnabled(false);
    }
}

void MainWindow::on_koreanButton_clicked()
{
    QPropertyAnimation *fadeOutTitleAnimation = new QPropertyAnimation(m_titleOpacityEffect, "opacity");
    fadeOutTitleAnimation->setDuration(300);
    fadeOutTitleAnimation->setStartValue(1.0);
    fadeOutTitleAnimation->setEndValue(0.0);
    fadeOutTitleAnimation->setEasingCurve(QEasingCurve::OutQuad);

    QGraphicsOpacityEffect *dolsoeEffect = ui->dolsoeLabel->graphicsEffect() ? static_cast<QGraphicsOpacityEffect*>(ui->dolsoeLabel->graphicsEffect()) : new QGraphicsOpacityEffect(ui->dolsoeLabel);
    if (!ui->dolsoeLabel->graphicsEffect()) ui->dolsoeLabel->setGraphicsEffect(dolsoeEffect);
    QPropertyAnimation *fadeOutDolsoeAnimation = new QPropertyAnimation(dolsoeEffect, "opacity");
    fadeOutDolsoeAnimation->setDuration(300);
    fadeOutDolsoeAnimation->setStartValue(1.0);
    fadeOutDolsoeAnimation->setEndValue(0.0);

    QGraphicsOpacityEffect *buttonEffect = ui->wakeUpButton->graphicsEffect() ? static_cast<QGraphicsOpacityEffect*>(ui->wakeUpButton->graphicsEffect()) : new QGraphicsOpacityEffect(ui->wakeUpButton);
    if (!ui->wakeUpButton->graphicsEffect()) ui->wakeUpButton->setGraphicsEffect(buttonEffect);
    QPropertyAnimation *fadeOutButtonAnimation = new QPropertyAnimation(buttonEffect, "opacity");
    fadeOutButtonAnimation->setDuration(300);
    fadeOutButtonAnimation->setStartValue(1.0);
    fadeOutButtonAnimation->setEndValue(0.0);

    QParallelAnimationGroup *fadeOutGroup = new QParallelAnimationGroup(this);
    fadeOutGroup->addAnimation(fadeOutTitleAnimation);
    fadeOutGroup->addAnimation(fadeOutDolsoeAnimation);
    fadeOutGroup->addAnimation(fadeOutButtonAnimation);

    connect(fadeOutGroup, &QParallelAnimationGroup::finished, this, [this, fadeOutGroup, dolsoeEffect, buttonEffect]() {
        if (m_currentLanguage == KOREAN) {
            changeLanguage("en");
            m_currentLanguage = ENGLISH;
            QPixmap titlePixmap(":/images/title_eng.png");
            ui->titleLabel->setPixmap(titlePixmap.scaled(ui->titleLabel->size(), Qt::KeepAspectRatio, Qt::SmoothTransformation));
            ui->wakeUpButton->setText(tr("Wake up Dolsoe"));
        } else {
            changeLanguage("ko");
            m_currentLanguage = KOREAN;
            QPixmap titlePixmap(":/images/title_kor.png");
            ui->titleLabel->setPixmap(titlePixmap.scaled(ui->titleLabel->size(), Qt::KeepAspectRatio, Qt::SmoothTransformation));
            ui->wakeUpButton->setText(tr("돌쇠 깨우기"));
        }

        QPropertyAnimation *fadeInTitleAnimation = new QPropertyAnimation(m_titleOpacityEffect, "opacity");
        fadeInTitleAnimation->setDuration(500);
        fadeInTitleAnimation->setStartValue(0.0);
        fadeInTitleAnimation->setEndValue(1.0);
        fadeInTitleAnimation->setEasingCurve(QEasingCurve::InQuad);

        ui->dolsoeLabel->show();
        ui->wakeUpButton->show();

        QPropertyAnimation *dolsoePosAnim = new QPropertyAnimation(ui->dolsoeLabel, "pos");
        dolsoePosAnim->setDuration(1000);
        dolsoePosAnim->setStartValue(QPoint(ui->dolsoeLabel->x(), ui->dolsoeLabel->y() + 100));
        dolsoePosAnim->setEndValue(ui->dolsoeLabel->pos());
        dolsoePosAnim->setEasingCurve(QEasingCurve::OutCubic);

        QPropertyAnimation *fadeInDolsoeAnimation = new QPropertyAnimation(dolsoeEffect, "opacity");
        fadeInDolsoeAnimation->setDuration(1000);
        fadeInDolsoeAnimation->setStartValue(0.0);
        fadeInDolsoeAnimation->setEndValue(1.0);

        QPropertyAnimation *buttonPosAnim = new QPropertyAnimation(ui->wakeUpButton, "pos");
        buttonPosAnim->setDuration(1000);
        buttonPosAnim->setStartValue(QPoint(ui->wakeUpButton->x(), ui->wakeUpButton->y() + 100));
        buttonPosAnim->setEndValue(ui->wakeUpButton->pos());
        buttonPosAnim->setEasingCurve(QEasingCurve::OutCubic);

        QPropertyAnimation *fadeInButtonAnimation = new QPropertyAnimation(buttonEffect, "opacity");
        fadeInButtonAnimation->setDuration(1000);
        fadeInButtonAnimation->setStartValue(0.0);
        fadeInButtonAnimation->setEndValue(1.0);

        QParallelAnimationGroup *dolsoeButtonGroup = new QParallelAnimationGroup(this);
        dolsoeButtonGroup->addAnimation(dolsoePosAnim);
        dolsoeButtonGroup->addAnimation(fadeInDolsoeAnimation);
        dolsoeButtonGroup->addAnimation(buttonPosAnim);
        dolsoeButtonGroup->addAnimation(fadeInButtonAnimation);

        connect(fadeInTitleAnimation, &QPropertyAnimation::finished, this, [dolsoeButtonGroup]() {
            dolsoeButtonGroup->start(QAbstractAnimation::DeleteWhenStopped);
        });

        fadeInTitleAnimation->start(QAbstractAnimation::DeleteWhenStopped);

        fadeOutGroup->deleteLater();
    });

    fadeOutGroup->start();
}

void MainWindow::changeLanguage(const QString &language)
{
    qDebug() << "Changing language to:" << language;
    qApp->removeTranslator(translator);

    if (language != "ko") {
        if (translator->load("daegamjip_" + language, ":/")) {
            qDebug() << "Translator loaded successfully for:" << language;
            qApp->installTranslator(translator);
        }
    }
    ui->retranslateUi(this);

    if (m_koreanButton) {
        m_koreanButton->setText(tr("언어 / Lang"));
    }

    ui->countryCB->clear();
    ui->countryCB->addItem(tr("-- 선택 --"));

    QList<QPair<QString, QString>> sortedCountries;
    for (auto it = countryCodes.constBegin(); it != countryCodes.constEnd(); ++it) {
        sortedCountries.append({it.key(), it.value()});
    }

    std::sort(sortedCountries.begin(), sortedCountries.end(),
              [](const QPair<QString, QString>& a, const QPair<QString, QString>& b) {
        return a.second < b.second;
    });

    for (const auto& pair : sortedCountries) {
        if (pair.first == "대한민국") {
            ui->countryCB->addItem(tr("대한민국"));
            break;
        }
    }

    for (const auto& pair : sortedCountries) {
        if (pair.first != "대한민국") {
            ui->countryCB->addItem(pair.first);
        }
    }

    keyboard->ui->retranslateUi(keyboard);
    numpad->ui->retranslateUi(numpad);

    handlePasswordChanged();
}

void MainWindow::updatePasswordIndicators(int length, const QList<QLabel*>& indicators)
{
    for (int i = 0; i < indicators.size(); ++i) {
        if (i < length) {
            indicators[i]->setText("*");
        } else {
            indicators[i]->setText("");
        }
    }
}



#ifdef RPI_BUILD
void MainWindow::onButtonPressed()
{
    qDebug() << "Button pressed signal received. Navigating to next page.";
    int currentIndex = ui->stack->currentIndex();
    int count = ui->stack->count();
    if (count == 0) return;
    int nextIndex = (currentIndex + 1) % count;
    ui->stack->setCurrentIndex(nextIndex);
}
#endif

void MainWindow::updateFrame(const cv::Mat &frame)
{
    if (frame.empty()) {
        qDebug() << "[DEBUG] updateFrame: Received empty frame.";
        return;
    }

    cv::Mat processedFrame;
    cv::cvtColor(frame, processedFrame, cv::COLOR_BGR2RGB);

    QImage qimg(processedFrame.data, processedFrame.cols, processedFrame.rows, processedFrame.step, QImage::Format_RGB888);
    m_videoLabel->setPixmap(QPixmap::fromImage(qimg).scaled(QSize(1056, 792),
                                                             Qt::KeepAspectRatio, // Maintain aspect ratio
                                                             Qt::FastTransformation));
    qDebug() << "[DEBUG] updateFrame: Frame displayed on m_videoLabel. Size:" << m_videoLabel->size();
}

void MainWindow::resizeEvent(QResizeEvent* event)
{
    QMainWindow::resizeEvent(event);
}

void MainWindow::resetCameraPage()
{
#ifdef RPI_BUILD
    if (m_gpioHandler) {
        m_gpioHandler->setLed(false);
    }
#endif
    m_sequenceTimer->stop();
    m_sequenceState = Idle;
    m_stateCountdown = 0;
    ui->cameraLabel->setText(tr("돌쇠가 당신의 모습을 촬영합니다"));
    ui->pushButton->setVisible(true);
    m_videoLabel->hide();
    QMetaObject::invokeMethod(m_videoWorker, "stop", Qt::QueuedConnection);
}

void MainWindow::on_finishPage_homeButton_clicked()
{
    m_finishPageTimer->stop();
    ui->stack->setCurrentIndex(0);
}

void MainWindow::on_finishPage_timeout()
{
    qDebug() << "Finish page timer timed out. Navigating to start page.";
    ui->stack->setCurrentIndex(0);
}
