#include "mainwindow.h"
#include "ui_mainwindow.h"

char ArgForFunc1[] = "This is argument for Function 1";
char ArgForFunc2[] = "This is argument for other function";

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->dial->setNotchesVisible(true);
    ui->dial->hide();

    HwTimer = new HAL(this);
    connect(HwTimer,  SIGNAL(HwTimerInterrupt()),  SLOT(on_HwInterupt()) );
    qDebug() << "redy to start TimerManager";
    timMang = new TimerManager;
    qDebug() << "redy to start TimerManager";

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_GetMil_clicked()
{
    unsigned int milliSec = HwTimer->GetMilliseconds();
    qsTemp = QString("Now is %1 MilliSeconds").arg(milliSec);
    ui->label_time->setText(qsTemp);
    ui->lcdNumber->display( (int) milliSec);
}

void MainWindow::on_pushButton_GetMicro_clicked()
{
    unsigned long long microSec = HwTimer->GetMicroSeconds();
    qsTemp = QString("Now is %1 MicroSeconds").arg(microSec);
    ui->label_time->setText(qsTemp);
    qsTemp = QString("%1").arg(microSec);
    ui->lcdNumber->display( qsTemp);
}

void MainWindow::on_HwInterupt()
{
    turnLedOn();
    QTimer::singleShot(600, this, SLOT(turnLedOff()));

}

void MainWindow::turnLedOn()
{
    ui->dial->setVisible(true);
}

void MainWindow::turnLedOff()
{
    ui->dial->hide();
}

void MainWindow::on_pushButton_StartTimer_clicked()
{
    double fDelay = ui->doubleSpinBox->value();
    qsTemp = QString("Get HW Timer Interupt after %1 sec").arg(fDelay);
    ui->label_time->setText(qsTemp);

    HwTimer->HwTimerStart(int(fDelay * 1000));
}

void MainWindow::on_pushButton_Stop_clicked()
{
    ui->label_time->setText("Hardware Timer Stop");
    HwTimer->HwTimerStop();
}

void MainWindow::on_pushButton_add1_clicked()
{
    timMang->addTask(1000,3000,"Task 1 ");
}

void MainWindow::on_pushButton_add2_clicked()
{
    timMang->addTask(5000,1000,"Task 2 ");
}

void MainWindow::on_pushButton_rem1_clicked()
{
    timMang->deleteTask("Task 1 ");
}

void MainWindow::on_pushButton_rem2_clicked()
{
    timMang->deleteTask("Task 2 ");
}

void MainWindow::on_pushButton_add3_clicked()
{
     timMang->addTask(15000,0,"Singli Task 3 ");
}

void MainWindow::on_pushButton_rem3_clicked()
{
     timMang->deleteTask("Singli Task 3 ");
}


int cb_func1(void *arg){
    QString qsTemp = "app %1!";
    qDebug() << "cb_func1 runs";
    char *pArr = (char *) arg;
    qsTemp = qsTemp.arg(pArr);

    qDebug() << "!" << qsTemp << "!";
    return 1;
}

void MainWindow::on_pushButton_clicked()
{
    void *vP;
    vP = (void *) ArgForFunc1;
    qDebug() << "cb_func1 is " << (cb_func1(vP));
}

void MainWindow::on_pushButton_addCb1_clicked()
{
    void *vP;
    vP = (void *) ArgForFunc2;
    int (*cb) (void *); // Function pointer

    cb = cb_func1;
    timMang->addCbFunc(1000,1000, cb, vP);
}

