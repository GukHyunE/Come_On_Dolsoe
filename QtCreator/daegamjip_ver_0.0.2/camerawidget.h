#ifndef CAMERAWIDGET_H
#define CAMERAWIDGET_H

#include <QWidget>
#include <QPaintEvent>

class CameraWidget : public QWidget
{
    Q_OBJECT

public:
    explicit CameraWidget(QWidget *parent = nullptr);
    ~CameraWidget(); // Add destructor

public slots:
    void updateOverlay(bool isPersonDetected, const QRect &detectionRect);

protected:
    void paintEvent(QPaintEvent *event) override;

private:
    bool m_isPersonDetected = false;
    QRect m_detectionRect;
};

#endif // CAMERAWIDGET_H
