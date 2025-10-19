// camerawidget.cpp (paintEvent 부분)
#include <QPainter>
#include <QFont>
#include "camerawidget.h"

CameraWidget::CameraWidget(QWidget *parent) : QWidget(parent)
{
    // Ensure the widget is transparent
    setAttribute(Qt::WA_TranslucentBackground);
    // Allow mouse events to pass through to widgets underneath
    setAttribute(Qt::WA_TransparentForMouseEvents);
}

CameraWidget::~CameraWidget()
{
}

void CameraWidget::updateOverlay(bool isPersonDetected, const QRect &detectionRect)
{
    m_isPersonDetected = isPersonDetected;
    m_detectionRect = detectionRect;
    update(); // Request a repaint
}

void CameraWidget::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event);
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);

    // Draw only if the widget is visible and has data
    if (isVisible()) {
        painter.setBrush(Qt::NoBrush);

        if (m_isPersonDetected) {
            painter.setPen(QPen(QColor(0, 255, 0, 200), 4));
            painter.drawRect(m_detectionRect);
            painter.setPen(Qt::white);
            painter.setFont(QFont("Arial", 14, QFont::Bold));
            painter.drawText(m_detectionRect.adjusted(0, -30, 0, -30), Qt::AlignCenter, "스캔중입니다...");
        } else {
            painter.setPen(QPen(QColor(255, 0, 0, 200), 4));
            painter.drawRect(m_detectionRect);
            painter.setPen(Qt::white);
            painter.setFont(QFont("Arial", 14, QFont::Bold));
            painter.drawText(m_detectionRect.adjusted(0, -30, 0, -30), Qt::AlignCenter, "네모 안에 서주세요");
        }
    }
}
