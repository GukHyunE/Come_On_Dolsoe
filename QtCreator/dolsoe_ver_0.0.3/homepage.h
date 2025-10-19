#ifndef HOMEPAGE_H
#define HOMEPAGE_H

#include <QWidget>
#include <QLabel>
#include <QMovie>
#include <QVBoxLayout>

class HomePage : public QWidget
{
    Q_OBJECT
public:
    explicit HomePage(QWidget *parent = nullptr);
    ~HomePage();

    QMovie* getHomeMovie() const { return m_homeMovie; }

protected:
    void resizeEvent(QResizeEvent *event) override;

private:
    QLabel *m_homeGifLabel;
    QMovie *m_homeMovie;
    QLabel *m_homeTextLabel;
};

#endif // HOMEPAGE_H
