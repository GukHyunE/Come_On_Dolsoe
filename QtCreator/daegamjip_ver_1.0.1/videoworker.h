#ifndef VIDEOWORKER_H
#define VIDEOWORKER_H

#include <QObject>
#include <QString>
#include <opencv2/core/mat.hpp>
#include <QTimer> // Added for QTimer

// Forward declarations
class QNetworkAccessManager;
class QNetworkReply;
class QByteArray;

class VideoWorker : public QObject
{
    Q_OBJECT
public:
    explicit VideoWorker(const QString &url, QObject *parent = nullptr);
    ~VideoWorker();

public slots:
    void start();
    void stop(bool restart = false);

signals:
    void frameReady(const cv::Mat &frame);

private slots:
    void onReadyRead();
    void reconnect();

private:
    QString m_url;
    QNetworkAccessManager *m_networkManager = nullptr;
    QNetworkReply *m_reply = nullptr;
    QByteArray m_buffer;
    QByteArray m_boundary;
    volatile bool m_running = false;
    QTimer *m_reconnectTimer = nullptr;
};

#endif // VIDEOWORKER_H