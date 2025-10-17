#ifndef GPIOHANDLER_H
#define GPIOHANDLER_H

#include <QObject>
#include <QTimer>
#include <gpiod.h>

class GpioHandler : public QObject
{
    Q_OBJECT
public:
    explicit GpioHandler(QObject *parent = nullptr);
    ~GpioHandler();

    bool initGpio(unsigned int outputPin, unsigned int buttonPin, unsigned int learningPin);

public slots:
    void sendStartRecordingSignal();
    void setLed(bool on);

private slots:
    void pollInputPins();

signals:
    void buttonPressed();
    void learningComplete();

private:
    gpiod_chip *m_chip = nullptr;
    gpiod_line *m_outputLine = nullptr;
    gpiod_line *m_inputLine = nullptr;
    gpiod_line *m_learningInputLine = nullptr;

    QTimer *m_inputPollTimer = nullptr;
    unsigned int m_outputPin;
    unsigned int m_inputPin;
    unsigned int m_learningInputPin;

    void setOutputLine(int value);
};

#endif
