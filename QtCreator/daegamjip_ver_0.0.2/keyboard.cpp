#include "keyboard.h"
#include "ui_keyboard.h"
#include <QtGui>
#include <QDebug>
#include <QTimer>

static QMap<QChar, int> cho_map;
static QMap<QChar, int> jung_map;
static QMap<QChar, int> jong_map;
static QMap<QPair<QChar, QChar>, QChar> jong_compose_map;
static QMap<QPair<QChar, QChar>, QChar> jung_compose_map;

Keyboard::Keyboard(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Keyboard),
    m_outputLineEdit(nullptr),
    m_isKorean(false),
    m_isShift(false),
    m_cho(-1), m_jung(-1), m_jong(-1),
    m_isComposing(false),
    m_backButtonBlocked(false)
{
    ui->setupUi(this);
    this->setFont(QFont("NanumGothic", 12));
    initializeMaps();
    ui->shiftButton->setCheckable(true);
    ui->langButton->setCheckable(true);

    const auto buttons = findChildren<QPushButton*>();
    for (QPushButton *button : buttons) {
        if (button->objectName().startsWith("Button")) {
            connect(button, &QPushButton::clicked, this, &Keyboard::keyboardHandler);
        }
    }
    connect(ui->shiftButton, &QPushButton::toggled, this, &Keyboard::on_shiftButton_toggled);
    connect(ui->langButton, &QPushButton::toggled, this, &Keyboard::on_langButton_toggled);
    connect(ui->backButton, &QPushButton::clicked, this, &Keyboard::on_backButton_clicked);
    connect(ui->spaceButton, &QPushButton::clicked, this, &Keyboard::on_spaceButton_clicked);
    connect(ui->enterButton, &QPushButton::clicked, this, &Keyboard::on_enterButton_clicked);
    updateKeyLabels();
}

Keyboard::~Keyboard()
{
    delete ui;
}

void Keyboard::setLineEdit(QLineEdit *line)
{
    m_outputLineEdit = line;
    if (m_outputLineEdit) {
        ui->lineEdit->setText(m_outputLineEdit->text());
    }
}

void Keyboard::keyboardHandler()
{
    if (!m_outputLineEdit) return;
    QPushButton *button = qobject_cast<QPushButton*>(sender());
    if (!button) return;
    QString keyText = button->text();

    if (m_isKorean) {
        processKorean(keyText.at(0));
        if (m_isShift) {
            // Check if the pressed key is a double consonant or shifted vowel
            if (keyText == "ㅃ" || keyText == "ㅉ" || keyText == "ㄸ" || keyText == "ㄲ" || keyText == "ㅆ" || keyText == "ㅒ" || keyText == "ㅖ") {
                m_isShift = false;
                ui->shiftButton->setChecked(false);
                updateKeyLabels();
            }
        }
    } else {
        commitComposition();
        m_outputLineEdit->insert(keyText);
        if (m_isShift) {
            m_isShift = false;
            ui->shiftButton->setChecked(false);
            updateKeyLabels();
        }
    }
    ui->lineEdit->setText(m_outputLineEdit->text());
}

void Keyboard::on_shiftButton_toggled(bool checked)
{
    m_isShift = checked;
    updateKeyLabels();
}

void Keyboard::on_langButton_toggled(bool checked)
{
    commitComposition();
    m_isKorean = checked;
    if(m_isShift) {
        m_isShift = false;
        ui->shiftButton->setChecked(false);
    }
    updateKeyLabels();
}

void Keyboard::on_backButton_clicked()
{
    if (m_backButtonBlocked) return; // Prevent re-entry

    m_backButtonBlocked = true; // Block further entries

    if (!m_outputLineEdit) {
        // Unblock after a short delay even if m_outputLineEdit is null
        QTimer::singleShot(100, this, [this]() { m_backButtonBlocked = false; });
        return;
    }

    QString text = m_outputLineEdit->text();
    if (m_isComposing) {
        text.chop(1);
        if (m_jong != -1) {
            QChar prevJongChar = jong_map.key(m_jong);
            bool isComposite = false;
            for(auto it = jong_compose_map.constBegin(); it != jong_compose_map.constEnd(); ++it) {
                if (it.value() == prevJongChar) {
                    m_jong = jong_map.value(it.key().first); isComposite = true; break;
                }
            }
            if (!isComposite) m_jong = -1;
        } else if (m_jung != -1) {
            QChar prevJungChar = jung_map.key(m_jung);
            bool isComposite = false;
            for(auto it = jung_compose_map.constBegin(); it != jung_compose_map.constEnd(); ++it) {
                if (it.value() == prevJungChar) {
                    m_jung = jung_map.value(it.key().first); isComposite = true; break;
                }
            }
            if (!isComposite) m_jung = -1;
        } else if (m_cho != -1) {
            m_cho = -1;
        }
        m_isComposing = (m_cho != -1);
        if (m_isComposing) {
            text += compose();
        }
    } else {
        text.chop(1);
    }
    m_outputLineEdit->setText(text);
    ui->lineEdit->setText(text);

    // Unblock after a short delay
    QTimer::singleShot(100, this, [this]() { m_backButtonBlocked = false; });
}


void Keyboard::on_spaceButton_clicked()
{
    if (!m_outputLineEdit) return;
    commitComposition();
    m_outputLineEdit->insert(" ");
    ui->lineEdit->setText(m_outputLineEdit->text());
}

void Keyboard::on_enterButton_clicked()
{
    commitComposition();
    close();
}


void Keyboard::processKorean(const QChar& c)
{
    QString text = m_outputLineEdit->text();
    if (m_isComposing) {
        text.chop(1);
    }

    if (cho_map.contains(c)) {
        if (!m_isComposing) {
            m_cho = cho_map.value(c);
        } else if (m_jung == -1) {
            text += compose();
            m_cho = cho_map.value(c);
        } else if (m_jong == -1) {
            if (jong_map.contains(c)) {
                m_jong = jong_map.value(c);
            } else {
                text += compose();
                m_cho = cho_map.value(c), m_jung = -1, m_jong = -1;
            }
        } else {
            QChar prevJong = jong_map.key(m_jong);
            if (jong_compose_map.contains({prevJong, c})) {
                m_jong = jong_map.value(jong_compose_map.value({prevJong, c}));
            } else {
                text += compose();
                m_cho = cho_map.value(c), m_jung = -1, m_jong = -1;
            }
        }
    } else if (jung_map.contains(c)) {
        if (!m_isComposing) {
            text += c;
            m_cho = -1, m_jung = -1, m_jong = -1;
        } else if (m_jung == -1) {
            m_jung = jung_map.value(c);
        } else if (m_jong == -1) {
            QChar prevJung = jung_map.key(m_jung);
            if (jung_compose_map.contains({prevJung, c})) {
                m_jung = jung_map.value(jung_compose_map.value({prevJung, c}));
            } else {
                text += compose();
                text += c;
                m_cho = -1, m_jung = -1, m_jong = -1;
            }
        } else {
            QChar jongChar = jong_map.key(m_jong);
            QPair<QChar, QChar> pair = {jongChar, QChar()};
            bool isComposite = false;
            for(auto it = jong_compose_map.constBegin(); it != jong_compose_map.constEnd(); ++it) {
                if(it.value() == jongChar) { pair = it.key(); isComposite = true; break; }
            }

            m_jong = isComposite ? jong_map.value(pair.first) : -1;
            text += compose();
            m_cho = cho_map.value(isComposite ? pair.second : pair.first);
            m_jung = jung_map.value(c);
            m_jong = -1;
        }
    }

    m_isComposing = (m_cho != -1);

    if (m_isComposing) {
        text += compose();
    }
    m_outputLineEdit->setText(text);
}


void Keyboard::commitComposition()
{
    if (!m_isComposing) return;
    QString text = m_outputLineEdit->text();
    text.chop(1);
    text += compose();
    m_outputLineEdit->setText(text);

    m_cho = -1;
    m_jung = -1;
    m_jong = -1;
    m_isComposing = false;
}

QChar Keyboard::compose()
{
    if (m_cho == -1) return QChar();
    if (m_jung == -1) return cho_map.key(m_cho);
    uint uni = 0xAC00 + (m_cho * 21 * 28) + (m_jung * 28) + (m_jong > 0 ? m_jong : 0);
    return QChar(uni);
}

void Keyboard::updateKeyLabels()
{
    const QMap<QPushButton*, QString> *map = nullptr;
    if (m_isKorean) {
        map = m_isShift ? &m_mapKorShift : &m_mapKorNormal;
        ui->langButton->setText("ENG");
    } else {
        map = m_isShift ? &m_mapEngShift : &m_mapEngNormal;
        ui->langButton->setText("한글");
    }
    if (!map) return;
    QMapIterator<QPushButton*, QString> i(*map);
    while (i.hasNext()) {
        i.next();
        i.key()->setText(i.value());
    }
}

void Keyboard::initializeMaps()
{
    if (cho_map.isEmpty()) {
        cho_map.insert(QChar(0x3131), 0); cho_map.insert(QChar(0x3132), 1); cho_map.insert(QChar(0x3134), 2);
        cho_map.insert(QChar(0x3137), 3); cho_map.insert(QChar(0x3138), 4); cho_map.insert(QChar(0x3139), 5);
        cho_map.insert(QChar(0x3141), 6); cho_map.insert(QChar(0x3142), 7); cho_map.insert(QChar(0x3143), 8);
        cho_map.insert(QChar(0x3145), 9); cho_map.insert(QChar(0x3146), 10); cho_map.insert(QChar(0x3147), 11);
        cho_map.insert(QChar(0x3148), 12); cho_map.insert(QChar(0x3149), 13); cho_map.insert(QChar(0x314A), 14);
        cho_map.insert(QChar(0x314B), 15); cho_map.insert(QChar(0x314C), 16); cho_map.insert(QChar(0x314D), 17);
        cho_map.insert(QChar(0x314E), 18);
        jung_map.insert(QChar(0x314F), 0); jung_map.insert(QChar(0x3150), 1); jung_map.insert(QChar(0x3151), 2);
        jung_map.insert(QChar(0x3152), 3); jung_map.insert(QChar(0x3153), 4); jung_map.insert(QChar(0x3154), 5);
        jung_map.insert(QChar(0x3155), 6); jung_map.insert(QChar(0x3156), 7); jung_map.insert(QChar(0x3157), 8);
        jung_map.insert(QChar(0x3158), 9); jung_map.insert(QChar(0x3159), 10); jung_map.insert(QChar(0x315A), 11);
        jung_map.insert(QChar(0x315B), 12); jung_map.insert(QChar(0x315C), 13); jung_map.insert(QChar(0x315D), 14);
        jung_map.insert(QChar(0x315E), 15); jung_map.insert(QChar(0x315F), 16); jung_map.insert(QChar(0x3160), 17);
        jung_map.insert(QChar(0x3161), 18); jung_map.insert(QChar(0x3162), 19); jung_map.insert(QChar(0x3163), 20);
        jong_map.insert(QChar(0x3131), 1); jong_map.insert(QChar(0x3132), 2); jong_map.insert(QChar(0x3133), 3);
        jong_map.insert(QChar(0x3134), 4); jong_map.insert(QChar(0x3135), 5); jong_map.insert(QChar(0x3136), 6);
        jong_map.insert(QChar(0x3137), 7); jong_map.insert(QChar(0x3139), 8); jong_map.insert(QChar(0x313A), 9);
        jong_map.insert(QChar(0x313B), 10); jong_map.insert(QChar(0x313C), 11); jong_map.insert(QChar(0x313D), 12);
        jong_map.insert(QChar(0x313E), 13); jong_map.insert(QChar(0x313F), 14); jong_map.insert(QChar(0x3140), 15);
        jong_map.insert(QChar(0x3141), 16); jong_map.insert(QChar(0x3142), 17); jong_map.insert(QChar(0x3144), 18);
        jong_map.insert(QChar(0x3145), 19); jong_map.insert(QChar(0x3146), 20); jong_map.insert(QChar(0x3147), 21);
        jong_map.insert(QChar(0x3148), 22); jong_map.insert(QChar(0x314A), 23); jong_map.insert(QChar(0x314B), 24);
        jong_map.insert(QChar(0x314C), 25); jong_map.insert(QChar(0x314D), 26); jong_map.insert(QChar(0x314E), 27);
        jong_compose_map.insert({QChar(0x3131), QChar(0x3145)}, QChar(0x3133));
        jong_compose_map.insert({QChar(0x3134), QChar(0x3148)}, QChar(0x3135));
        jong_compose_map.insert({QChar(0x3134), QChar(0x314E)}, QChar(0x3136));
        jong_compose_map.insert({QChar(0x3139), QChar(0x3131)}, QChar(0x313A));
        jong_compose_map.insert({QChar(0x3139), QChar(0x3141)}, QChar(0x313B));
        jong_compose_map.insert({QChar(0x3139), QChar(0x3142)}, QChar(0x313C));
        jong_compose_map.insert({QChar(0x3139), QChar(0x3145)}, QChar(0x313D));
        jong_compose_map.insert({QChar(0x3139), QChar(0x314C)}, QChar(0x313E));
        jong_compose_map.insert({QChar(0x3139), QChar(0x314D)}, QChar(0x313F));
        jong_compose_map.insert({QChar(0x3139), QChar(0x314E)}, QChar(0x3140));
        jong_compose_map.insert({QChar(0x3142), QChar(0x3145)}, QChar(0x3144));
        jung_compose_map.insert({QChar(0x3157), QChar(0x314F)}, QChar(0x3158));
        jung_compose_map.insert({QChar(0x3157), QChar(0x3150)}, QChar(0x3159));
        jung_compose_map.insert({QChar(0x3157), QChar(0x3163)}, QChar(0x315A));
        jung_compose_map.insert({QChar(0x315C), QChar(0x3153)}, QChar(0x315D));
        jung_compose_map.insert({QChar(0x315C), QChar(0x3154)}, QChar(0x315E));
        jung_compose_map.insert({QChar(0x315C), QChar(0x3163)}, QChar(0x315F));
        jung_compose_map.insert({QChar(0x3161), QChar(0x3163)}, QChar(0x3162));
    }
    m_mapEngNormal.clear(); m_mapEngShift.clear(); m_mapKorNormal.clear(); m_mapKorShift.clear();
    m_mapEngNormal.insert(ui->Buttonq, "q"); m_mapEngNormal.insert(ui->Buttonw, "w"); m_mapEngNormal.insert(ui->Buttone, "e"); m_mapEngNormal.insert(ui->Buttonr, "r"); m_mapEngNormal.insert(ui->Buttont, "t"); m_mapEngNormal.insert(ui->Buttony, "y"); m_mapEngNormal.insert(ui->Buttonu, "u"); m_mapEngNormal.insert(ui->Buttoni, "i"); m_mapEngNormal.insert(ui->Buttono, "o"); m_mapEngNormal.insert(ui->Buttonp, "p"); m_mapEngNormal.insert(ui->Buttona, "a"); m_mapEngNormal.insert(ui->Buttons, "s"); m_mapEngNormal.insert(ui->Buttond, "d"); m_mapEngNormal.insert(ui->Buttonf, "f"); m_mapEngNormal.insert(ui->Buttong, "g"); m_mapEngNormal.insert(ui->Buttonh, "h"); m_mapEngNormal.insert(ui->Buttonj, "j"); m_mapEngNormal.insert(ui->Buttonk, "k"); m_mapEngNormal.insert(ui->Buttonl, "l"); m_mapEngNormal.insert(ui->Buttonz, "z"); m_mapEngNormal.insert(ui->Buttonx, "x"); m_mapEngNormal.insert(ui->Buttonc, "c"); m_mapEngNormal.insert(ui->Buttonv, "v"); m_mapEngNormal.insert(ui->Buttonb, "b"); m_mapEngNormal.insert(ui->Buttonn, "n"); m_mapEngNormal.insert(ui->Buttonm, "m");
    m_mapEngShift.insert(ui->Buttonq, "Q"); m_mapEngShift.insert(ui->Buttonw, "W"); m_mapEngShift.insert(ui->Buttone, "E"); m_mapEngShift.insert(ui->Buttonr, "R"); m_mapEngShift.insert(ui->Buttont, "T"); m_mapEngShift.insert(ui->Buttony, "Y"); m_mapEngShift.insert(ui->Buttonu, "U"); m_mapEngShift.insert(ui->Buttoni, "I"); m_mapEngShift.insert(ui->Buttono, "O"); m_mapEngShift.insert(ui->Buttonp, "P"); m_mapEngShift.insert(ui->Buttona, "A"); m_mapEngShift.insert(ui->Buttons, "S"); m_mapEngShift.insert(ui->Buttond, "D"); m_mapEngShift.insert(ui->Buttonf, "F"); m_mapEngShift.insert(ui->Buttong, "G"); m_mapEngShift.insert(ui->Buttonh, "H"); m_mapEngShift.insert(ui->Buttonj, "J"); m_mapEngShift.insert(ui->Buttonk, "K"); m_mapEngShift.insert(ui->Buttonl, "L"); m_mapEngShift.insert(ui->Buttonz, "Z"); m_mapEngShift.insert(ui->Buttonx, "X"); m_mapEngShift.insert(ui->Buttonc, "C"); m_mapEngShift.insert(ui->Buttonv, "V"); m_mapEngShift.insert(ui->Buttonb, "B"); m_mapEngShift.insert(ui->Buttonn, "N"); m_mapEngShift.insert(ui->Buttonm, "M");
    m_mapKorNormal.insert(ui->Buttonq, "ㅂ"); m_mapKorNormal.insert(ui->Buttonw, "ㅈ"); m_mapKorNormal.insert(ui->Buttone, "ㄷ"); m_mapKorNormal.insert(ui->Buttonr, "ㄱ"); m_mapKorNormal.insert(ui->Buttont, "ㅅ"); m_mapKorNormal.insert(ui->Buttony, "ㅛ"); m_mapKorNormal.insert(ui->Buttonu, "ㅕ"); m_mapKorNormal.insert(ui->Buttoni, "ㅑ"); m_mapKorNormal.insert(ui->Buttono, "ㅐ"); m_mapKorNormal.insert(ui->Buttonp, "ㅔ"); m_mapKorNormal.insert(ui->Buttona, "ㅁ"); m_mapKorNormal.insert(ui->Buttons, "ㄴ"); m_mapKorNormal.insert(ui->Buttond, "ㅇ"); m_mapKorNormal.insert(ui->Buttonf, "ㄹ"); m_mapKorNormal.insert(ui->Buttong, "ㅎ"); m_mapKorNormal.insert(ui->Buttonh, "ㅗ"); m_mapKorNormal.insert(ui->Buttonj, "ㅓ"); m_mapKorNormal.insert(ui->Buttonk, "ㅏ"); m_mapKorNormal.insert(ui->Buttonl, "ㅣ"); m_mapKorNormal.insert(ui->Buttonz, "ㅋ"); m_mapKorNormal.insert(ui->Buttonx, "ㅌ"); m_mapKorNormal.insert(ui->Buttonc, "ㅊ"); m_mapKorNormal.insert(ui->Buttonv, "ㅍ"); m_mapKorNormal.insert(ui->Buttonb, "ㅠ"); m_mapKorNormal.insert(ui->Buttonn, "ㅜ"); m_mapKorNormal.insert(ui->Buttonm, "ㅡ");
    m_mapKorShift.insert(ui->Buttonq, "ㅃ"); m_mapKorShift.insert(ui->Buttonw, "ㅉ"); m_mapKorShift.insert(ui->Buttone, "ㄸ"); m_mapKorShift.insert(ui->Buttonr, "ㄲ"); m_mapKorShift.insert(ui->Buttont, "ㅆ"); m_mapKorShift.insert(ui->Buttony, "ㅛ"); m_mapKorShift.insert(ui->Buttonu, "ㅕ"); m_mapKorShift.insert(ui->Buttoni, "ㅑ"); m_mapKorShift.insert(ui->Buttono, "ㅒ"); m_mapKorShift.insert(ui->Buttonp, "ㅖ"); m_mapKorShift.insert(ui->Buttona, "ㅁ"); m_mapKorShift.insert(ui->Buttons, "ㄴ"); m_mapKorShift.insert(ui->Buttond, "ㅇ"); m_mapKorShift.insert(ui->Buttonf, "ㄹ"); m_mapKorShift.insert(ui->Buttong, "ㅎ"); m_mapKorShift.insert(ui->Buttonh, "ㅗ"); m_mapKorShift.insert(ui->Buttonj, "ㅓ"); m_mapKorShift.insert(ui->Buttonk, "ㅏ"); m_mapKorShift.insert(ui->Buttonl, "ㅣ"); m_mapKorShift.insert(ui->Buttonz, "ㅋ"); m_mapKorShift.insert(ui->Buttonx, "ㅌ"); m_mapKorShift.insert(ui->Buttonc, "ㅊ"); m_mapKorShift.insert(ui->Buttonv, "ㅍ"); m_mapKorShift.insert(ui->Buttonb, "ㅠ"); m_mapKorShift.insert(ui->Buttonn, "ㅜ"); m_mapKorShift.insert(ui->Buttonm, "ㅡ");
}
