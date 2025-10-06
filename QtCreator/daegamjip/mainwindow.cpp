#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "keyboard.h"
#include "ui_keyboard.h" // Added for full definition of Ui::Keyboard
#include "numpad.h"
#include "ui_numpad.h"   // Added for full definition of Ui::NumPad
#include <QEvent>
#include <QKeyEvent>
#include <QApplication>
#include <QVBoxLayout>
#include <QWidget>
#include <QHBoxLayout>
#include <QPushButton>
#include <QSpacerItem>
#include <algorithm> // For std::sort
#include <QTimer> // Added for QTimer functionality
#include <QDebug>
#include <QCameraInfo>
#include <QMessageBox>


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , m_previousStackIndex(0)
{
    ui->setupUi(this);

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
    m_koreanButton = new QPushButton(tr("한국어"));
    m_englishButton = new QPushButton(tr("English"));
    cornerLayout->addStretch(1);
    cornerLayout->addWidget(m_koreanButton);
    cornerLayout->addWidget(m_englishButton);
    ui->menubar->setCornerWidget(m_languageButtonWidget);

    connect(m_koreanButton, &QPushButton::clicked, this, &MainWindow::on_koreanButton_clicked);
    connect(m_englishButton, &QPushButton::clicked, this, &MainWindow::on_englishButton_clicked);

    translator = new QTranslator(this);

    // --- Keyboard & Numpad Setup ---
    keyboard = new Keyboard(this);
    keyboard->setWindowFlags(Qt::Window | Qt::Tool | Qt::FramelessWindowHint | Qt::WindowStaysOnTopHint);
    numpad = new NumPad(this);
    numpad->setWindowFlags(Qt::Window | Qt::Tool | Qt::FramelessWindowHint | Qt::WindowStaysOnTopHint);

    ui->nameLE->installEventFilter(this);
    ui->numberLE->installEventFilter(this);
    ui->pwLE->installEventFilter(this);
    ui->repwLE->installEventFilter(this);
    ui->numberLE->setEchoMode(QLineEdit::Normal); // Ensure numbers are visible

    // --- Country ComboBox Setup ---
    countryCodes.insert("대한민국", "+82");
    countryCodes.insert("United States", "+1");
    countryCodes.insert("日本", "+81");
    countryCodes.insert("中国", "+86");

    ui->countryCB->addItem(tr("-- 선택 --"));

    // Sort countries by country code
    QList<QPair<QString, QString>> sortedCountries;
    for (auto it = countryCodes.constBegin(); it != countryCodes.constEnd(); ++it) {
        sortedCountries.append({it.key(), it.value()});
    }

    std::sort(sortedCountries.begin(), sortedCountries.end(),
              [](const QPair<QString, QString>& a, const QPair<QString, QString>& b) {
        return a.second < b.second;
    });

    // Add "대한민국" first, then the rest sorted by code
    for (const auto& pair : sortedCountries) {
        if (pair.first == "대한민국") {
            // Add Korea after "-- 선택 --"
            ui->countryCB->addItem(tr("대한민국"));
            break; // Assuming "대한민국" is unique and we only want it once
        }
    }

    for (const auto& pair : sortedCountries) {
        if (pair.first != "대한민국") {
            ui->countryCB->addItem(pair.first);
        }
    }
    // --- Password Indicators Setup ---


    updatePasswordIndicators(0, m_pwIndicators);
    updatePasswordIndicators(0, m_repwIndicators);
    ui->pwokLabel->clear();

    // --- Signal & Slot Connections ---
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
    connect(ui->startButton, &QPushButton::clicked, this, &MainWindow::on_startButton_clicked);
    connect(ui->next, &QPushButton::clicked, this, &MainWindow::on_next_clicked);
    connect(ui->back, &QPushButton::clicked, this, &MainWindow::on_back_clicked);
    connect(ui->stack, &QStackedWidget::currentChanged, this, &MainWindow::onStackPageChanged);
    ui->stack->setCurrentIndex(0);
    qApp->installEventFilter(this);

    try {
        // --- Camera Setup ---
        const QList<QCameraInfo> devices = QCameraInfo::availableCameras();
        if (devices.isEmpty()) {
            qDebug() << "No cameras found!";
            m_camera = nullptr;
            m_videoWidget = nullptr;    // Initialize to nullptr if no camera
        } else {
            m_camera = new QCamera(devices.first(), this);
            connect(m_camera, SIGNAL(error(QCamera::Error)), this, SLOT(onCameraError(QCamera::Error)));

            m_videoWidget = new QVideoWidget(this);
            m_camera->setViewfinder(m_videoWidget);

            // Programmatically create the layout for cameraPage
            QVBoxLayout *cameraPageLayout = new QVBoxLayout(ui->cameraPage);
            cameraPageLayout->addWidget(m_videoWidget, 8); // 80% of the space
            cameraPageLayout->addWidget(ui->cameraLabel, 1); // 10% of the space
            cameraPageLayout->addWidget(ui->pushButton, 1); // 10% of the space
            ui->cameraPage->setLayout(cameraPageLayout);

            m_videoWidget->hide(); // Initially hide the video widget
        }
    } catch (...) {
        qDebug() << "An unknown error occurred during camera initialization. Disabling camera.";
        m_camera = nullptr;
        m_videoWidget = nullptr;
    }

    m_sequenceTimer = new QTimer(this);
    connect(m_sequenceTimer, &QTimer::timeout, this, &MainWindow::updateCountdown);
    m_sequenceState = Idle;
    m_stateCountdown = 0;

    m_finishPageTimer = new QTimer(this);
    m_finishPageTimer->setSingleShot(true);
    connect(m_finishPageTimer, &QTimer::timeout, this, &MainWindow::goToStartPage);
    qDebug() << "MainWindow constructor finished.";
}

MainWindow::~MainWindow()
{
    delete ui;
}

bool MainWindow::eventFilter(QObject *obj, QEvent *event)
{
    if (event->type() == QEvent::MouseButtonPress) {
        if (obj == ui->nameLE) {
            keyboard->setLineEdit(ui->nameLE);
            keyboard->show();
        } else if (obj == ui->numberLE) {
            numpad->setLineEdit(static_cast<QLineEdit*>(obj), false); // Pass false for isPasswordField
            numpad->move(200, 200);
            numpad->show();
        } else if (obj == ui->pwLE || obj == ui->repwLE) {
            numpad->setLineEdit(static_cast<QLineEdit*>(obj), true); // Pass true for isPasswordField
            numpad->move(200, 200);
            numpad->show();
        }
    }
    return QMainWindow::eventFilter(obj, event);
}

// --- Page Navigation Slots ---
void MainWindow::on_startButton_clicked()
{
    // Clear all input fields
    ui->nameLE->clear();
    ui->countryCB->setCurrentIndex(0); // Assuming index 0 is "-- 선택 --"
    ui->numberLE->clear();
    ui->pwLE->clear();
    ui->repwLE->clear();
    ui->privacyCheckBox->setChecked(false);

    ui->stack->setCurrentIndex(1);
}

void MainWindow::on_next_clicked()
{
    // 서버 주소와 포트
    QString serverAddress = "10.10.16.153";
    quint16 serverPort = 5000; // 서버 포트에 맞게 수정

    socket->connectToHost(serverAddress, serverPort);
    if (socket->waitForConnected(3000)) { // 3초 동안 연결 대기
        // UI에서 사용자 정보 가져오기
        QString name = ui->nameLE->text();
        QString countryCode = ui->countrynumLE->text();
        QString password = ui->pwLE->text();

        // 프로토콜에 맞춰 메시지 생성: STORE@이름@국가번호@비밀번호
        QString message = QString("STORE@%1@%2@%3").arg(name, countryCode, password);

        // 서버로 메시지 전송
        socket->write(message.toUtf8() + "\n");
        socket->flush(); // 버퍼를 비워 즉시 전송

        // 다음 페이지로 이동
        ui->stack->setCurrentIndex(ui->stack->indexOf(ui->cameraPage));
        m_languageButtonWidget->setVisible(false);

    } else {
        // 연결 실패 처리
        QMessageBox::critical(this, tr("Connection Failed"), tr("Could not connect to the server."));
        // 실패 시 다른 페이지로 이동하거나 현재 페이지에 머무를 수 있습니다.
        // 예: ui->stack->setCurrentIndex(ui->stack->indexOf(ui->noRobotPage));
    }
}


void MainWindow::onSocketReadyRead()
{
    // 서버로부터 응답을 받을 경우의 처리 (예: ACK@STORE)
    QByteArray data = socket->readAll();
    QString response = QString::fromUtf8(data).trimmed();
    qDebug() << "Received from server:" << response;

    if (response == "ACK@STORE") {
        // 성공적으로 저장됨
        // 다음 페이지로 이동 등의 추가 작업 수행 가능
    } else {
        // 저장 실패 또는 다른 응답 처리
    }
}


void MainWindow::on_pushButton_2_clicked() // "초기 화면" button
{
    qDebug() << "on_pushButton_2_clicked called.";
    m_finishPageTimer->stop();
    ui->stack->setCurrentIndex(0);
}

void MainWindow::on_pushButton_3_clicked() // "돌쇠야 가자" button
{
    if (socket->state() == QAbstractSocket::ConnectedState) {
        socket->write("SEND_TO_ROBOT\n");
        socket->flush();
        qDebug() << "Sent SEND_TO_ROBOT to server.";
    } else {
        // 서버 연결이 끊긴 경우, 다시 연결 시도 후 메시지 전송
        // 이 예제에서는 단순화를 위해 연결이 되어있다고 가정하고 바로 다음 페이지로 넘어갑니다.
        qDebug() << "Socket not connected, cannot send SEND_TO_ROBOT.";
    }
    // 다음 페이지(finishPage)로 이동
    ui->stack->setCurrentIndex(ui->stack->indexOf(ui->finishPage));
}

void MainWindow::on_pushButton_clicked()
{
    ui->pushButton->setVisible(false);
    m_videoWidget->show();
    startCamera();

    ui->cameraLabel->setText(tr("촬영을 시작합니다."));
    QTimer::singleShot(1500, this, [this]() {
        m_sequenceState = InitialCountdown;
        m_stateCountdown = 5;
                    ui->cameraLabel->setText(tr("%1초 뒤에 촬영을 시작합니다.").arg(m_stateCountdown));        m_sequenceTimer->start(1000); // 1-second ticks
    });
}

void MainWindow::updateCountdown()
{
    m_stateCountdown--;

    switch (m_sequenceState) {
    case InitialCountdown:
        if (m_stateCountdown > 0) {
            ui->cameraLabel->setText(tr("%1초 뒤에 촬영을 시작합니다.").arg(m_stateCountdown));
        }
        else {
            m_sequenceState = Shooting;
            m_stateCountdown = 3;
            ui->cameraLabel->setText(tr("촬영 중 (%1)").arg(m_stateCountdown));
        }
        break;
    case Shooting:
        if (m_stateCountdown > 0) {
            ui->cameraLabel->setText(tr("촬영 중 (%1)").arg(m_stateCountdown));
        }
        else {
            m_sequenceState = Turning;
            m_stateCountdown = 10;
            ui->cameraLabel->setText(tr("제자리에서 360도 천천히 돌아주세요 (%1)").arg(m_stateCountdown));
        }
        break;
    case Turning:
        if (m_stateCountdown > 0) {
            ui->cameraLabel->setText(tr("제자리에서 360도 천천히 돌아주세요 (%1)").arg(m_stateCountdown));
        }
        else {
            m_sequenceState = Recognizing;
            ui->cameraLabel->setText(tr("인식 중 (잠시만 기다려주세요)"));
            m_sequenceTimer->stop();
        }
        break;
    case Recognizing:
    case Idle:
        // Should not happen
        m_sequenceTimer->stop();
        break;
    }
}

void MainWindow::on_back_clicked()
{
    ui->stack->setCurrentIndex(0);
    m_languageButtonWidget->setVisible(true);
}

// --- Temporary Navigation Slots ---
void MainWindow::on_tempPrevButton_clicked()
{
    int currentIndex = ui->stack->currentIndex();
    int count = ui->stack->count();
    if (count == 0) return;
    int prevIndex = (currentIndex - 1 + count) % count;
    ui->stack->setCurrentIndex(prevIndex);
}

void MainWindow::on_tempNextButton_clicked()
{
    int currentIndex = ui->stack->currentIndex();
    int count = ui->stack->count();
    if (count == 0) return;
    int nextIndex = (currentIndex + 1) % count;
    ui->stack->setCurrentIndex(nextIndex);
}

void MainWindow::onStackPageChanged(int index)
{
    qDebug() << "onStackPageChanged: index =" << index;

    // If we are leaving the camera page, reset it
    if (m_previousStackIndex == ui->stack->indexOf(ui->cameraPage)) {
        resetCameraPage();
    }

    m_languageButtonWidget->setVisible(index == 0);
    if (index == ui->stack->indexOf(ui->finishPage)) { // Check if the current page is the finish page
        qDebug() << "Starting finish page timer.";
        if (m_finishPageTimer) {
            m_finishPageTimer->start(3000);
        } // 3 seconds
    } else {
        qDebug() << "Stopping finish page timer. m_finishPageTimer:" << m_finishPageTimer;
        if (m_finishPageTimer) {
            m_finishPageTimer->stop();
        }
    }

    m_previousStackIndex = index; // Update the previous index
}


// --- Form Logic Slots ---
void MainWindow::on_countryCB_currentIndexChanged(int index)
{
    if (index == 0) {
        ui->countrynumLE->clear();
    } else {
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

// --- Translation Logic ---
void MainWindow::on_koreanButton_clicked()
{
    changeLanguage("ko");
}

void MainWindow::on_englishButton_clicked()
{
    qDebug() << "English button clicked.";
    changeLanguage("en");
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

    ui->logo->setHtml(tr("<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n<html><head><meta name=\"qrichtext\" content=\"1\" /><meta charset=\"utf-8\" /><style type=\"text/css\">\np, li { white-space: pre-wrap; }\nhr { height: 1px; border-width: 0; }\nli.unchecked::marker { content: \"\\2610\"; }\nli.checked::marker { content: \"\\2612\"; }\n</style></head><body style=\" font-family:&apos;Ubuntu&apos;; font-size:11pt; font-weight:400; font-style:normal;\">\n<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-size:26pt;\">돌쇠야, 이리오너라!</span></p></body></html>"));

    // Retranslate language buttons
    if (m_koreanButton) {
        m_koreanButton->setText(tr("한국어"));
    }
    if (m_englishButton) {
        m_englishButton->setText(tr("English"));
    }

    // Re-populate country combo box to apply new translation
    ui->countryCB->clear();
    ui->countryCB->addItem(tr("-- 선택 --"));

    // Sort countries by country code
    QList<QPair<QString, QString>> sortedCountries;
    for (auto it = countryCodes.constBegin(); it != countryCodes.constEnd(); ++it) {
        sortedCountries.append({it.key(), it.value()});
    }

    std::sort(sortedCountries.begin(), sortedCountries.end(),
              [](const QPair<QString, QString>& a, const QPair<QString, QString>& b) {
        return a.second < b.second;
    });

    // Add "대한민국" first, then the rest sorted by code
    for (const auto& pair : sortedCountries) {
        if (pair.first == "대한민국") {
            // Add Korea after "-- 선택 --"
            ui->countryCB->addItem(tr("대한민국"));
            break; // Assuming "대한민국" is unique and we only want it once
        }
    }

    for (const auto& pair : sortedCountries) {
        if (pair.first != "대한민국") {
            ui->countryCB->addItem(pair.first);
        }
    }

    // Retranslate Keyboard and Numpad widgets
    keyboard->ui->retranslateUi(keyboard);
    numpad->ui->retranslateUi(numpad);

    handlePasswordChanged();
}

// --- Password Indicator UI Logic ---
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

void MainWindow::onCameraError(QCamera::Error error)
{
    qDebug() << "Camera Error:" << error;
}

void MainWindow::goToStartPage()
{
    qDebug() << "goToStartPage called.";
    ui->stack->setCurrentIndex(0);
}

void MainWindow::startCamera()
{
    if (m_camera) {
        m_camera->start();
        qDebug() << "Camera status:" << (m_camera->status() == QCamera::ActiveStatus);
    }
}

void MainWindow::stopCamera()
{
    if (m_camera) {
        m_camera->stop();
    }
}

void MainWindow::resetCameraPage()
{
    qDebug() << "Resetting camera page...";
    // Stop the camera and timers
    stopCamera();
    m_sequenceTimer->stop();

    // Reset state variables
    m_sequenceState = Idle;
    m_stateCountdown = 0;

    // Reset UI elements
    if (m_videoWidget) {
        m_videoWidget->hide();
    }
    ui->pushButton->setVisible(true);
    ui->cameraLabel->setText(tr("버튼을 누르면 촬영이 시작됩니다.")); // Reset label text
}
