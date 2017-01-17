#ifndef TIMERMANAGER_H
#define TIMERMANAGER_H

#include "hal.h"

#include <QObject>
#include <QDebug>

#define MAX_CB_NUMBER 40

typedef struct timerRec{
    int timeTillNextCall;
    int period;
    bool isActive;
    QString qsFnName;
    int (*cbFunc)(void *);
    //void *cbFunc;
    void *cbArg;
} timerRec ;

class TimerManager : public QObject
{
    Q_OBJECT
    HAL *HwTimer;
    QString qsTemp;
    int i;
    timerRec recArr[MAX_CB_NUMBER];
    timerRec *ptRec;
    bool isAnyTaskActive;

public:
    explicit TimerManager(QObject *parent = 0);

    int addTask(int startUp, int repeat, QString qsTaskName);
    int deleteTask(QString qsTaskName);
    int addCbFunc(int startUp, int repeat, int (*cb_func)(void *), void *cb_arg);

signals:

public slots:
    void on_HwInterupt();
private slots:
    void init();
    void printRecord(timerRec *recToPrint);

};

#endif // TIMERMANAGER_H
