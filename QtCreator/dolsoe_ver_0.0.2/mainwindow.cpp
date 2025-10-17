#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "numpad.h"
#include <QMessageBox>
#include <QTimer>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , m_numpad(new NumPad(this))
    , m_numpadReason(NumpadReason::None)
    , m_currentLanguage("KR") // Default to Korean
    , m_isStopped(false) // Default to running state
    , m_isBusy(false)
{
    ui->setupUi(this);
    setFixedSize(800, 480);

    // --- Image/GIF Display Setup ---
    m_imageDisplayLabel = new QLabel(ui->centralwidget);
    m_imageDisplayLabel->setAlignment(Qt::AlignCenter);
    m_imageDisplayLabel->hide();
    m_imageDisplayLabel->lower(); // Send to back

    m_workingMovie = new QMovie(":/images/working.gif");
    m_restPixmap = QPixmap(":/images/rest.png");

    m_isBusy = true; // Set busy to true for default working.gif display
    updateImageDisplay(); // Update display immediately

    // --- Home Page Setup ---
    m_homePage = new QWidget();
    m_homeGifLabel = new QLabel(m_homePage); // GIF is the background
    m_homeMovie = new QMovie(":/images/home.gif");
    m_homeGifLabel->setMovie(m_homeMovie);
    m_homeGifLabel->setScaledContents(true);

    // Widgets to overlay
    QLabel *homeText = new QLabel("돌쇠 퇴근해유~~", m_homePage);
    homeText->setAlignment(Qt::AlignCenter);

    // Layout for the home page
    QVBoxLayout *homePageLayout = new QVBoxLayout(m_homePage);
    homePageLayout->setContentsMargins(0, 0, 0, 0);
    homePageLayout->setSpacing(0);
    homePageLayout->addWidget(m_homeGifLabel);
    m_homePage->setLayout(homePageLayout);

    // Layout for the overlay widgets
    QVBoxLayout *overlayLayout = new QVBoxLayout();
    overlayLayout->setContentsMargins(0, 0, 0, 0);
    overlayLayout->setSpacing(0);
    overlayLayout->addStretch();
    overlayLayout->addWidget(homeText);
    overlayLayout->addStretch();

    // Container for overlay widgets
    QWidget *overlayContainer = new QWidget(m_homePage);
    overlayContainer->setLayout(overlayLayout);
    overlayContainer->setGeometry(m_homePage->rect());
    overlayContainer->show();

    ui->stackedWidget->addWidget(m_homePage);

    updateTexts(); // Set initial texts

    // Numpad is a separate dialog, which will be launched modally
    // connect the passwordEntered signal from the numpad to our slot
    connect(m_numpad, &NumPad::passwordEntered, this, &MainWindow::onPasswordEntered);

    // --- Network Setup ---
    m_socket = new QTcpSocket(this);
    connect(m_socket, &QTcpSocket::connected, this, &MainWindow::onConnected);
    connect(m_socket, &QTcpSocket::readyRead, this, &MainWindow::onReadyRead);
    connect(m_socket, &QTcpSocket::disconnected, this, &MainWindow::onDisconnected);

    connectToServer();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::connectToServer()
{
    // 서버 주소와 포트 (Server 애플리케이션에 맞게 수정 필요)
    QString serverAddress = "10.10.16.153";
    quint16 serverPort = 5000;
    ui->statusLabel->setText(m_currentLanguage == "KR" ? "서버에 연결하는 중..." : "Connecting to server...");
    m_socket->connectToHost(serverAddress, serverPort);
}

void MainWindow::onConnected()
{
    ui->statusLabel->setText(m_currentLanguage == "KR" ? "서버에 연결됨. 대기 중..." : "Connected to server. Waiting...");
    // 로봇 ID를 'dolsoe_01'로 가정하고 서버에 준비 완료 메시지 전송
    m_socket->write("ROBOT_READY@dolsoe_01\n");
}

void MainWindow::onReadyRead()
{
    QByteArray data = m_socket->readAll();
    QString message = QString::fromUtf8(data).trimmed();

    if (message.startsWith("ASSIGN_TASK")) {
        m_assignedPassword = message.section('@', 1, 1);
        ui->statusLabel->setText(m_currentLanguage == "KR" ? "작업 할당됨. 이제부터 사용 가능합니다." : "Task assigned. Ready for use.");
        // 비밀번호를 받으면, 정지 상태를 해제
        m_isStopped = false;
        updateTexts();
    }
}

void MainWindow::onDisconnected()
{
    ui->statusLabel->setText(m_currentLanguage == "KR" ? "서버 연결 끊김. 5초 후 재시도..." : "Server disconnected. Retrying in 5 seconds...");
    // 5초 후에 다시 연결 시도
    QTimer::singleShot(5000, this, &MainWindow::connectToServer);
}

void MainWindow::resizeEvent(QResizeEvent *event)
{
    QMainWindow::resizeEvent(event);
    if (m_imageDisplayLabel) {
        m_imageDisplayLabel->setGeometry(ui->centralwidget->rect());
    }
}


void MainWindow::updateTexts()
{
    if (m_currentLanguage == "KR") {
        // Set Korean texts
        ui->langKrPB->setText("한국어");
        ui->langEnPB->setText("English");
        ui->label->setText("바프찍는돌쇠");
        ui->carryPB->setText("따라오너라");
        ui->endCB->setText("종료하거라");
        ui->label_2->setText("돌쇠 집가는 사진");
        ui->label_3->setText("돌쇠 퇴근해유~~");

        if (m_isStopped) {
            ui->tempPB->setText("시작하거라");
        } else {
            ui->tempPB->setText("정지하거라");
        }

        // ComboBox items
        ui->naviCB->clear();
        ui->naviCB->addItem("안내하거라");
        ui->naviCB->addItem("스타벅스");
        ui->naviCB->addItem("화장실");
        ui->naviCB->addItem("면세점");

    } else if (m_currentLanguage == "EN") {
        // Set English texts
        ui->langKrPB->setText("한국어");
        ui->langEnPB->setText("English");
        ui->label->setText("Dolsoe taking a body profile photo");
        ui->carryPB->setText("Follow Me");
        ui->endCB->setText("Shutdown");
        ui->label_2->setText("Dolsoe going home");
        ui->label_3->setText("Dolsoe is leaving~~");

        if (m_isStopped) {
            ui->tempPB->setText("Start");
        } else {
            ui->tempPB->setText("Stop");
        }

        // ComboBox items
        ui->naviCB->clear();
        ui->naviCB->addItem("Guide");
        ui->naviCB->addItem("Starbucks");
        ui->naviCB->addItem("Restroom");
        ui->naviCB->addItem("Duty-Free");
    }
    m_numpad->updateLanguage(m_currentLanguage);
}

void MainWindow::updateImageDisplay()
{
    if (m_isStopped) {
        m_workingMovie->stop();
        m_imageDisplayLabel->setPixmap(m_restPixmap.scaled(m_imageDisplayLabel->size(), Qt::KeepAspectRatio, Qt::SmoothTransformation));
        m_imageDisplayLabel->show();
    } else {
        if (m_isBusy) {
            m_imageDisplayLabel->setMovie(m_workingMovie);
            m_workingMovie->start();
            m_imageDisplayLabel->show();
        } else {
            m_workingMovie->stop();
            m_imageDisplayLabel->hide();
        }
    }
}

void MainWindow::on_langKrPB_clicked()
{
    m_currentLanguage = "KR";
    updateTexts();
}

void MainWindow::on_langEnPB_clicked()
{
    m_currentLanguage = "EN";
    updateTexts();
}

void MainWindow::on_carryPB_clicked()
{
    m_isBusy = true;
    updateImageDisplay();
    if (m_currentLanguage == "KR") {
        ui->statusLabel->setText("돌쇠가 마님을 따라가는 중입니다");
    } else {
        ui->statusLabel->setText("Dolsoe is following you.");
    }
}

void MainWindow::on_naviCB_activated(int index)
{
    if (index > 0) {
        m_isBusy = true;
    } else {
        m_isBusy = false;
    }
    updateImageDisplay();

    if (m_currentLanguage == "KR") {
        switch(index) {
            case 0: // 길안내
                ui->statusLabel->setText("어디로 뫼실까요?");
                break;
            case 1: // 스타벅스
                ui->statusLabel->setText("돌쇠가 스타벅스로 마님을 모시는 중입니다.");
                break;
            case 2: // 화장실
                ui->statusLabel->setText("돌쇠가 화장실로 마님을 모시는 중입니다.");
                break;
            case 3: // 면세점
                ui->statusLabel->setText("돌쇠가 면세점으로 마님을 모시는 중입니다.");
                break;
        }
    } else { // English
        switch(index) {
            case 0: // Guide
                ui->statusLabel->setText("Where can I take you?");
                break;
            case 1: // Starbucks
                ui->statusLabel->setText("Dolsoe is taking you to Starbucks.");
                break;
            case 2: // Restroom
                ui->statusLabel->setText("Dolsoe is taking you to the restroom.");
                break;
            case 3: // Duty-Free
                ui->statusLabel->setText("Dolsoe is taking you to the duty-free shop.");
                break;
        }
    }
}

void MainWindow::on_tempPB_clicked()
{
    if (m_isStopped) { // If it is stopped, we want to start
        m_numpadReason = NumpadReason::Start;
        m_numpad->clear();
        m_numpad->exec();
    } else { // If it is running, we want to stop
        m_isStopped = true;
        m_isBusy = false; // Stop implies not busy
        updateTexts();
        updateImageDisplay();
    }
}

void MainWindow::on_endCB_clicked()
{
    QMessageBox::StandardButton reply;
    QString title = (m_currentLanguage == "KR") ? "종료하거라" : "Shutdown";
    QString text = (m_currentLanguage == "KR") ? "정말 종료하시겠습니까?" : "Are you sure you want to shut down?";

    reply = QMessageBox::question(this, title, text,
                                    QMessageBox::Yes|QMessageBox::No);
    if (reply == QMessageBox::Yes) {
        m_numpadReason = NumpadReason::Shutdown;
        m_numpad->clear();
        m_numpad->exec();
    }
}

void MainWindow::onPasswordEntered(const QString &password)
{
    // 이유를 확인하고 즉시 초기화하여 중복 실행 방지
    NumpadReason reason = m_numpadReason;

    // numpad가 호출된 이유가 없으면 아무것도 하지 않음
    if (reason == NumpadReason::None) {
        // 이 경우는 거의 없지만, 안전장치로 둠
        return;
    }

    // 서버로부터 할당받은 비밀번호가 있는지, 그리고 비어있지 않은지 확인
    if (m_assignedPassword.isNull() || m_assignedPassword.isEmpty()) {
        if (m_currentLanguage == "KR") {
            QMessageBox::warning(this, "실패", "아직 서버로부터 작업이 할당되지 않았습니다.");
        } else {
            QMessageBox::warning(this, "Failure", "No task has been assigned by the server yet.");
        }
        m_numpadReason = NumpadReason::None; // 이유 초기화
        m_numpad->acceptAndClose(); // 작업 할당이 안됐으므로 넘패드 닫기
        return;
    }

    if (password == m_assignedPassword) {
        m_numpadReason = NumpadReason::None; // 이유 초기화

        switch (reason) { // 캡처해둔 이유를 사용
            case NumpadReason::Start:
                m_isStopped = false; // Now it is running
                m_isBusy = true; // Robot is busy when running
                updateTexts();
                updateImageDisplay();
                if (m_currentLanguage == "KR") {
                    QMessageBox::information(this, "성공", "인증에 성공했습니다.");
                }
                else {
                    QMessageBox::information(this, "Success", "Authentication successful.");
                }
                break;
            case NumpadReason::Shutdown:
                ui->stackedWidget->setCurrentWidget(m_homePage);
                m_homeMovie->start();
                m_assignedPassword.clear();
                onConnected(); // 다시 'ROBOT_READY' 전송
                break;
            case NumpadReason::None:
                break;
        }
        m_numpad->acceptAndClose(); // 성공했으므로 넘패드 닫기
    } else {
        // 비밀번호가 틀렸을 경우, 팝업 중복 호출을 막기 위해 신호 연결을 잠시 끊음
        disconnect(m_numpad, &NumPad::passwordEntered, this, &MainWindow::onPasswordEntered);

        if (m_currentLanguage == "KR") {
            QMessageBox::warning(this, "인증 실패", "다시 한 번 시도해 주세요.");
        } else {
            QMessageBox::warning(this, "Auth Failed", "Please try again.");
        }

        m_numpad->clear(); // 넘패드 입력 초기화

        // 0.1초 후에 다시 신호를 연결하여 중복 이벤트 회피
        QTimer::singleShot(100, this, [this]() {
            connect(m_numpad, &NumPad::passwordEntered, this, &MainWindow::onPasswordEntered);
        });
    }
}
