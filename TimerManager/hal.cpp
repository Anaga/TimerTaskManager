#include "hal.h"


HAL::HAL(QObject *parent) : QObject(parent)
{
    qInfo() << "HAL init";
    currentTime = QTime::currentTime();
    connect(&hwTimer, SIGNAL(timeout()), this, SLOT(hwTimeOut()));
    hwTimer.setSingleShot(true);

}

void HAL::HwTimerStart(unsigned int microseconds){
   // qInfo() << "HwTimerStart for " <<microseconds << " microseconds";
    hwTimer.start(microseconds);
}

void HAL::HwTimerStop(){
    qInfo() << "HwTimerStop";
    hwTimer.stop();
}

unsigned int HAL::GetMilliseconds(){
    int i;
    currentTime = QTime::currentTime();
    qInfo() << "now is "<< currentTime.toString("hh:mm:ss.zzz");
    i = currentTime.msecsSinceStartOfDay();
    qDebug() << "currentTime.msecsSinceStartOfDay() is " << i;
    return i;
}

unsigned long long HAL::GetMicroSeconds(){
    unsigned long long i;
    currentTime = QTime::currentTime();
    qDebug() << currentTime.toString("hh:mm:ss.zzz");
    qInfo() << "now is "<< currentTime.toString("hh:mm:ss.zzz");
    i = currentTime.msecsSinceStartOfDay();
    i = i*100;
    qDebug() << "currentTime.msecsSinceStartOfDay() is " << i;
    return i;
}

void HAL::hwTimeOut(){
   // qInfo() << "emit(HwTimerInterrupt())";
    emit(HwTimerInterrupt());
}
