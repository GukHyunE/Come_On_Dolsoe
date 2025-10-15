#include "videoworker.h"
#include <QDebug>
#include <QNetworkAccessManager>
#include <QNetworkRequest>
#include <QNetworkReply>
#include <QRegularExpression>
#include <vector>
#include <opencv2/imgcodecs.hpp>
#include <QTimer>

VideoWorker::VideoWorker(const QString &url, QObject *parent)
    : QObject(parent), m_url(url)
{
    m_networkManager = new QNetworkAccessManager(this);
    m_reconnectTimer = new QTimer(this);
    m_reconnectTimer->setInterval(3000); // Try to reconnect every 3 seconds
    m_reconnectTimer->setSingleShot(true);
    connect(m_reconnectTimer, &QTimer::timeout, this, &VideoWorker::reconnect);
}

VideoWorker::~VideoWorker()
{
    stop();
    qDebug() << "VideoWorker destroyed.";
}

void VideoWorker::start()
{
    if (m_running) {
        qDebug() << "VideoWorker is already running.";
        return;
    }

    qDebug() << "--- Video Worker Diagnostics (QNetwork) ---";
    qDebug() << "Starting stream from:" << m_url;

    QNetworkRequest request(m_url);
    m_reply = m_networkManager->get(request);

    connect(m_reply, &QNetworkReply::metaDataChanged, this, [this](){
        qDebug() << "[DEBUG] MetaDataChanged signal received.";
        qDebug() << "[DEBUG] Content-Type Header:" << m_reply->header(QNetworkRequest::ContentTypeHeader).toString();
        // Try to extract boundary here as well, in case readyRead is delayed
        if (m_boundary.isEmpty()) {
            QRegularExpression re("boundary=([^\\s;]+)");
            QString contentType = m_reply->header(QNetworkRequest::ContentTypeHeader).toString();
            QRegularExpressionMatch match = re.match(contentType);
            if (match.hasMatch()) {
                m_boundary = "--" + match.captured(1).toUtf8();
                qDebug() << "[DEBUG] Found stream boundary from MetaDataChanged:" << m_boundary;
            } else {
                qDebug() << "[DEBUG] Could not find multipart boundary in Content-Type header from MetaDataChanged:" << contentType;
            }
        }
    });

    connect(m_reply, &QNetworkReply::readyRead, this, &VideoWorker::onReadyRead);
    connect(m_reply, &QNetworkReply::finished, this, [this](){
        qDebug() << "[DEBUG] Network reply finished signal received. Error:" << m_reply->error() << m_reply->errorString();
        if (m_reply->error() != QNetworkReply::NoError) {
            qDebug() << "[DEBUG] Stopping worker due to finished signal with error.";
            stop(true); // Stop and signal for restart
        } else {
            // For MJPEG streams, a 'finished' signal with NoError might indicate a server-side close
            // or an unexpected end of stream. We should attempt to restart.
            qDebug() << "[DEBUG] Network reply finished with NoError. Attempting restart.";
            stop(true); // Stop and signal for restart
        }
    });
    connect(m_reply, static_cast<void(QNetworkReply::*)(QNetworkReply::NetworkError)>(&QNetworkReply::error), this, [this](QNetworkReply::NetworkError code){
        qDebug() << "[FATAL] Network error occurred:" << code << m_reply->errorString();
        stop(true); // Stop and signal for restart
    });

    m_running = true;
}

void VideoWorker::stop(bool restart)
{
    if (!m_running && !m_reply) {
        return;
    }
    m_running = false;
    qDebug() << "Stopping video worker...";
    if (m_reply) {
        // Disconnect all signals from the reply to prevent any further processing
        disconnect(m_reply, nullptr, this, nullptr);
        if (m_reply->isRunning()) {
            m_reply->abort();
        }
        m_reply->deleteLater();
        m_reply = nullptr;
    }
    m_buffer.clear();
    m_boundary.clear();

    if (restart) {
        qDebug() << "[DEBUG] Reconnect timer started.";
        m_reconnectTimer->start();
    }
}

void VideoWorker::reconnect()
{
    qDebug() << "[DEBUG] Attempting to reconnect...";
    start();
}

void VideoWorker::onReadyRead()
{
    qDebug() << "[DEBUG] onReadyRead called.";
    m_buffer.append(m_reply->readAll());

    if (m_boundary.isEmpty()) {
        QRegularExpression re("boundary=([^\\s;]+)");
        QString contentType = m_reply->header(QNetworkRequest::ContentTypeHeader).toString();
        QRegularExpressionMatch match = re.match(contentType);
        if (match.hasMatch()) {
            m_boundary = "--" + match.captured(1).toUtf8();
            qDebug() << "[DEBUG] Found stream boundary from onReadyRead:" << m_boundary;
        } else {
            qDebug() << "[ERROR] Could not find multipart boundary in Content-Type header:" << contentType;
            stop(true);
            return;
        }
    }

    while (true) {
        qDebug() << "[DEBUG] onReadyRead loop: Buffer size:" << m_buffer.size();
        int boundaryIndex = m_buffer.indexOf(m_boundary);
        if (boundaryIndex == -1) {
            qDebug() << "[DEBUG] onReadyRead loop: No boundary found, breaking.";
            break;
        }
        qDebug() << "[DEBUG] onReadyRead loop: Boundary found at:" << boundaryIndex;

        QByteArray jpegHeader = "Content-Type: image/jpeg\r\n\r\n"; // Changed to \r\n for CRLF
        int jpegStartIndex = m_buffer.indexOf(jpegHeader, boundaryIndex);
        if (jpegStartIndex == -1) {
            qDebug() << "[DEBUG] onReadyRead loop: JPEG header not found after boundary at:" << boundaryIndex;
            // If JPEG header is not found, it might be a boundary for the previous frame, or just not enough data yet.
            // Let's try to find the next boundary to avoid getting stuck.
            int nextBoundaryCandidate = m_buffer.indexOf(m_boundary, boundaryIndex + m_boundary.length());
            if (nextBoundaryCandidate != -1) {
                qDebug() << "[DEBUG] onReadyRead loop: Skipping to next boundary candidate at:" << nextBoundaryCandidate;
                m_buffer = m_buffer.mid(nextBoundaryCandidate);
                continue;
            } else {
                qDebug() << "[DEBUG] onReadyRead loop: No next boundary candidate, breaking.";
                break;
            }
        }
        jpegStartIndex += jpegHeader.length();
        qDebug() << "[DEBUG] onReadyRead loop: JPEG start index:" << jpegStartIndex;

        int nextBoundaryIndex = m_buffer.indexOf(m_boundary, jpegStartIndex);
        if (nextBoundaryIndex == -1) {
            qDebug() << "[DEBUG] onReadyRead loop: Next boundary not found, breaking.";
            break;
        }
        qDebug() << "[DEBUG] onReadyRead loop: Next boundary found at:" << nextBoundaryIndex;

        QByteArray jpegData = m_buffer.mid(jpegStartIndex, nextBoundaryIndex - jpegStartIndex);
        qDebug() << "[DEBUG] onReadyRead loop: Extracted JPEG data size:" << jpegData.size();

        if (jpegData.isEmpty()) {
            qDebug() << "[WARNING] Extracted JPEG data is empty.";
            m_buffer = m_buffer.mid(nextBoundaryIndex);
            continue;
        }

        std::vector<char> data(jpegData.constData(), jpegData.constData() + jpegData.size());
        cv::Mat frame = cv::imdecode(data, cv::IMREAD_COLOR);

        if (!frame.empty()) {
            emit frameReady(frame);
            qDebug() << "[DEBUG] onReadyRead loop: Emitted frameReady signal.";
        } else {
            qDebug() << "[WARNING] Failed to decode JPEG frame. JPEG data size:" << jpegData.size();
            // Optionally save jpegData to a file for inspection
            // QFile file("failed_frame.jpg");
            // if (file.open(QIODevice::WriteOnly)) { file.write(jpegData); file.close(); }
        }

        m_buffer = m_buffer.mid(nextBoundaryIndex);
    }
}