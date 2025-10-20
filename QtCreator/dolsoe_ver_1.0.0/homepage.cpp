#include "homepage.h"

HomePage::HomePage(QWidget *parent)
    : QWidget(parent)
{
    // Set up the GIF label as background
    m_homeGifLabel = new QLabel(this);
    m_homeMovie = new QMovie(":/images/home.gif");
    m_homeGifLabel->setMovie(m_homeMovie);
    m_homeGifLabel->setScaledContents(true);
    m_homeGifLabel->setAlignment(Qt::AlignCenter);

    // Set up the text label
    m_homeTextLabel = new QLabel("돌쇠 퇴근해유~~", this);
    m_homeTextLabel->setAlignment(Qt::AlignCenter);
}

HomePage::~HomePage()
{
    // QMovie is owned by QLabel, so no explicit delete needed for m_homeMovie
}

void HomePage::resizeEvent(QResizeEvent *event)
{
    QWidget::resizeEvent(event);
    if (m_homeGifLabel) {
        m_homeGifLabel->setGeometry(this->rect());
    }
    if (m_homeTextLabel) {
        m_homeTextLabel->setGeometry(this->rect());
    }
}