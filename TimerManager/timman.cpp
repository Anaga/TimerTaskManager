#include "timman.h"

TimerManager::TimerManager(QObject *parent) : QObject(parent)
{
    HwTimer = new HAL(this);
    connect(HwTimer,  SIGNAL(HwTimerInterrupt()),  SLOT(on_HwInterupt()) );
    init();
}

void TimerManager::init()
{
    ptRec = recArr;
    qDebug() << "TimerManager::init";

    for (i=0; i<MAX_CB_NUMBER; i++, ptRec++){
        qsTemp = QString("Func %1 init").arg(i+1);

        ptRec->isActive = false;
        ptRec->period = 0;
        ptRec->timeTillNextCall = 0;
        ptRec->qsFnName = qsTemp;
        ptRec->cbFunc = NULL;
        ptRec->cbArg = NULL;
    }
    qDebug() << "TimerManager::init, done";
    isAnyTaskActive = false;
}

int TimerManager::addTask(int startUp, int repeat, QString qsTaskName)
{
    ptRec = recArr;

    qsTemp = QString("TimerManager::addTask(startUp %1, repeat%2, qsTaskName%3)").arg(startUp).arg(repeat).arg(qsTaskName);
    qDebug() << qsTemp;

    for (i=0; i<MAX_CB_NUMBER; i++, ptRec++){
        if (!(ptRec->isActive)){
            ptRec->period = repeat;
            ptRec->timeTillNextCall = startUp;
            ptRec->qsFnName = qsTaskName;
            ptRec->isActive = true;
            ptRec->cbFunc = NULL;
            ptRec->cbArg = NULL;

            qsTemp = QString("TimerManager::addTask, ok, add new task to pos %1!").arg(i);
            qDebug() << qsTemp;

            if (!isAnyTaskActive){
                HwTimer->HwTimerStart(1);
                isAnyTaskActive = true;
            }
            return i+1;
        }
    }
    qsTemp = "TimerManager::addTask, can't find unactive record for new task!";
    qDebug() << qsTemp;
    return 0;
}

int TimerManager::deleteTask(QString qsTaskName)
{
    ptRec = recArr;

    qsTemp = QString("TimerManager::deleteTask(qsTaskName%1)").arg(qsTaskName);
    qDebug() << qsTemp;

    for (i=0; i<MAX_CB_NUMBER; i++, ptRec++){
        if (ptRec->isActive){
            if (qsTaskName == ptRec->qsFnName){
                ptRec->isActive = false;
                qsTemp = QString("TimerManager::deleteTask, disable task with count %1").arg(i);
                qDebug() << qsTemp;
                printRecord(ptRec);
                return i+1;
            }
        }
    }
    qsTemp = "TimerManager::deleteTask, can't find any active task to delete";
    qDebug() << qsTemp;

    return 0;
}

int TimerManager::removeCbFunc(int (*cb_func)(void *)){
     ptRec = recArr;
     for (i=0; i<MAX_CB_NUMBER; i++, ptRec++){
         if (ptRec->isActive){
             if (cb_func == ptRec->cbFunc){
                 ptRec->isActive = false;
                 ptRec->cbArg = NULL;
                 ptRec->cbFunc = NULL;
                 qsTemp = QString("Remove function with count %1").arg(i);
                 qDebug() << qsTemp;
                 printRecord(ptRec);
                 return i+1;
             }
         }
     }
     qDebug() << "Can't find any active function to delete";
     return 0;
}

int TimerManager::addCbFunc(int startUp, int repeat, int (*cb_func)(void *), void*cb_arg)
{
    QString qsFuncName = " ";
    ptRec = recArr;

    qsTemp = QString("StartUp %1, Repeat%2, qsFuncName%3)").arg(startUp).arg(repeat).arg(qsFuncName);

    qDebug() << qsTemp;

    for (i=0; i<MAX_CB_NUMBER; i++, ptRec++){
        if (!(ptRec->isActive)){
            ptRec->period = repeat;
            ptRec->timeTillNextCall = startUp;
            ptRec->qsFnName = qsFuncName;
            ptRec->cbFunc = cb_func;
            ptRec->cbArg  = cb_arg;
            ptRec->isActive = true;
            qsTemp = QString("ok, add new Cb func to pos %1!").arg(i);
            qDebug() << qsTemp;
            if (!isAnyTaskActive){
                HwTimer->HwTimerStart(1);
                isAnyTaskActive = true;
            }
            return i+1;
        }
    }
    qsTemp = "Can't find unactive record for new task!";
    qCritical() << qsTemp;
    return 0;

}

void TimerManager::on_HwInterupt()
{
    bool timeToCall = false;
    bool isSinglCall = false;
    int (*cb_func)(void *);
    void *cb_arg;

    ptRec = recArr;
    isAnyTaskActive = false;

    //start next timer befor run all tasks;
    HwTimer->HwTimerStart(1);

    for (i=0; i< MAX_CB_NUMBER; i++, ptRec++){
        //printRecord(ptRec);
        if (ptRec->isActive){
            isAnyTaskActive = true;
            timeToCall  = (0 >= ptRec->timeTillNextCall);
            isSinglCall = (0 >= ptRec->period);

            if (timeToCall) {
               // qDebug() << "Call function " << ptRec->qsFnName;
                if ((NULL !=ptRec->cbFunc) && (NULL != ptRec->cbArg)){
                    cb_func = ptRec->cbFunc;
                    cb_arg  = ptRec->cbArg;
                    cb_func(cb_arg);
                   // qDebug() << "Return is " << cbVal;
                }

                if (isSinglCall){
                    ptRec->isActive = false;
                }else {
                    ptRec->timeTillNextCall = ptRec->period;
                }
            }
            ptRec->timeTillNextCall--;
        }
    }
    if (!isAnyTaskActive) {
        HwTimer->HwTimerStop();
    }
}

void TimerManager::printRecord(timerRec *recToPrint)
{
    qsTemp = "Function: TaskName%1, wait %2, repeat %3, act %4";
    QString s = recToPrint->qsFnName;
    int t = recToPrint->timeTillNextCall;
    int r = recToPrint->period;
    bool act = recToPrint->isActive;

    qsTemp = qsTemp.arg(s).arg(t).arg(r).arg(act);
    qDebug() << qsTemp;
}
