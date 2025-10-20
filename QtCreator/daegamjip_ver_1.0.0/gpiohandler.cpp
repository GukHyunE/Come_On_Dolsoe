#include "gpiohandler.h"
#include <QDebug>
#include <unistd.h> // For usleep

// Define GPIO chip path (usually /dev/gpiochip0 for Raspberry Pi)
#define GPIO_CHIP_PATH "/dev/gpiochip0"

GpioHandler::GpioHandler(QObject *parent) : QObject(parent)
{
    m_inputPollTimer = new QTimer(this);
    m_inputPollTimer->setInterval(50); // Poll every 50ms
    connect(m_inputPollTimer, &QTimer::timeout, this, &GpioHandler::pollInputPins);
}

GpioHandler::~GpioHandler()
{
    if (m_inputPollTimer->isActive()) {
        m_inputPollTimer->stop();
    }
    if (m_outputLine) {
        gpiod_line_release(m_outputLine);
    }
    if (m_inputLine) {
        gpiod_line_release(m_inputLine);
    }
    if (m_chip) {
        gpiod_chip_close(m_chip);
    }
    qDebug() << "GpioHandler destroyed.";
}

bool GpioHandler::initGpio(unsigned int outputPin, unsigned int buttonPin, unsigned int learningPin)
{
    m_outputPin = outputPin;
    m_inputPin = buttonPin;
    m_learningInputPin = learningPin;

    qDebug() << "Initializing GPIO...";
    m_chip = gpiod_chip_open(GPIO_CHIP_PATH);
    if (!m_chip) {
        qCritical() << "Failed to open GPIO chip:" << GPIO_CHIP_PATH;
        return false;
    }
    qDebug() << "GPIO chip opened successfully.";

    // Request output line
    m_outputLine = gpiod_chip_get_line(m_chip, m_outputPin);
    if (!m_outputLine || gpiod_line_request_output(m_outputLine, "gpio_output", 0) < 0) {
        qCritical() << "Failed to request output line for pin:" << m_outputPin;
        gpiod_chip_close(m_chip);
        m_chip = nullptr;
        return false;
    }
    qDebug() << "GPIO Output line" << m_outputPin << "initialized.";
    setOutputLine(0);

    // Request button input line
    m_inputLine = gpiod_chip_get_line(m_chip, m_inputPin);
    if (!m_inputLine || gpiod_line_request_input(m_inputLine, "gpio_input") < 0) {
        qCritical() << "Failed to request input line for pin:" << m_inputPin;
        // Release previously requested resources
        gpiod_line_release(m_outputLine);
        gpiod_chip_close(m_chip);
        m_chip = nullptr;
        return false;
    }
    qDebug() << "GPIO Input line" << m_inputPin << "initialized.";

    // Request learning complete input line
    m_learningInputLine = gpiod_chip_get_line(m_chip, m_learningInputPin);
    if (!m_learningInputLine || gpiod_line_request_input(m_learningInputLine, "gpio_input") < 0) {
        qCritical() << "Failed to request input line for pin:" << m_learningInputPin;
        // Release previously requested resources
        gpiod_line_release(m_outputLine);
        gpiod_line_release(m_inputLine);
        gpiod_chip_close(m_chip);
        m_chip = nullptr;
        return false;
    }
    qDebug() << "GPIO Input line" << m_learningInputPin << "initialized.";

    m_inputPollTimer->start();
    qDebug() << "GPIO initialized successfully.";
    return true;
}

void GpioHandler::pollInputPins()
{
    if (m_inputLine) {
        int value = gpiod_line_get_value(m_inputLine);
        if (value < 0) {
            qCritical() << "Failed to get value from input line (GPIO" << m_inputPin << ").";
        } else {
            static int previousValue = 0;
            if (value == 1 && previousValue == 0) {
                qDebug() << "Button press detected (GPIO" << m_inputPin << ").";
                emit buttonPressed();
            }
            previousValue = value;
        }
    }

    if (m_learningInputLine) {
        int value = gpiod_line_get_value(m_learningInputLine);
        if (value < 0) {
            qCritical() << "Failed to get value from learning input line (GPIO" << m_learningInputPin << ").";
        } else {
            static int previousValue = 0;
            if (value == 1 && previousValue == 0) {
                qDebug() << "Learning complete signal detected (GPIO" << m_learningInputPin << ").";
                emit learningComplete();
            }
            previousValue = value;
        }
    }
}

void GpioHandler::setOutputLine(int value)
{
    if (m_outputLine) {
        qDebug() << "Setting output line" << m_outputPin << "to" << value;
        int ret = gpiod_line_set_value(m_outputLine, value);
        if (ret < 0) {
            qCritical() << "Failed to set value for output line" << m_outputPin;
        }
    } else {
        qWarning() << "Cannot set output line value, line is not initialized.";
    }
}

void GpioHandler::sendStartRecordingSignal()
{
    if (m_outputLine) {
        qDebug() << "Sending start recording signal (GPIO" << m_outputPin << " High for 100ms)";
        setOutputLine(1); // Set high
        QTimer::singleShot(100, this, [this](){
            setOutputLine(0); // Set low after 100ms
            qDebug() << "Start recording signal (GPIO" << m_outputPin << ") set Low.";
        });
    } else {
        qWarning() << "GPIO Output line not initialized. Cannot send start recording signal.";
    }
}

void GpioHandler::setLed(bool on)
{
    if (m_outputLine) {
        int value = on ? 1 : 0;
        qDebug() << "Setting LED (GPIO" << m_outputPin << ") to" << value;
        setOutputLine(value);
    } else {
        qWarning() << "GPIO Output line not initialized. Cannot set LED state.";
    }
}
