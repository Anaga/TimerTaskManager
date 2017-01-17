#ifndef HAL_H
#define HAL_H

#include <QObject>
#include <QTime>
#include <QTimer>
#include <QDebug>

class HAL : public QObject
{
    Q_OBJECT

    QTime currentTime;
    QTimer hwTimer;


public:
    explicit HAL(QObject *parent = 0);

    void HwTimerStart(unsigned int microseconds);
    void HwTimerStop(void);
    unsigned int GetMilliseconds(void);
    unsigned long long int GetMicroSeconds(void);

signals:
    void HwTimerInterrupt(void);

public slots:
    void hwTimeOut();
};

#endif // HAL_H
