#include "mainwindow.h"
#include "ui_mainwindow.h"

char ArgForFunc1[] = "This is argument for Function 1";
char ArgForFunc2[] = "This is argument for other function";
char ArgForFunc3[] = "Function 3";
char ArgForFunc4[] = "Function with number 4";
char ArgForFunc5[] = "Function 5";
char ArgForFunc6[] = "Callback Function 6";

HAL GlobalTimer;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->dial->setNotchesVisible(true);
    ui->dial->hide();

    HwTimer = new HAL(this);
    connect(HwTimer,  SIGNAL(HwTimerInterrupt()),  SLOT(on_HwInterupt()) );
    timMang = new TimerManager;
    uint mill = GlobalTimer.GetMilliseconds();
    ui->label_time->setText( QString::number(mill) );

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

/*End of Hw Timer part */


/* Start of cb func implementation */


int cb_func1(void *arg){
    qDebug() << QString("cb_func1 runs with arg \'%1\'").arg((char *) arg);
    return 1;
}

int cb_func1a(void *arg){
    qDebug() << "cb 1a";
    qDebug() << (char*) arg;
    return 1;
}

int cb_func2(void *arg){
    static QTime lastTimeCall;
    QString qsTemp = "cb_func2 runs, my arg is %1, my last time to call was %2!";
    QString qsTime(lastTimeCall.toString("HH:mm:ss,zzz"));
    char *pArr = (char *) arg;

    qsTemp = qsTemp.arg(pArr).arg(qsTime);
    qDebug() << qsTemp;

    lastTimeCall = QTime::currentTime();
    return 1;
}

int cb_func3(void *arg){
    QString qsTemp = "cb_func3 runs, my arg is %1, now is %2 sec aftre startup!";
    uint mill = GlobalTimer.GetMilliseconds();
    char *pArr = (char *) arg;

    qsTemp = qsTemp.arg(pArr).arg(mill);
    qDebug() << qsTemp;
    return 1;
}


void MainWindow::on_pushButton_add1_clicked()
{
    void *vP;
    vP = (void *) ArgForFunc1;
    int (*cb) (void *); // Function pointer

    uint startUpTime = uint(1000 * ui->doubleSpinBox_t1_Start->value());
    uint redoTime = uint(1000* ui->doubleSpinBox_t1_Redo->value());

    cb = cb_func1;
    timMang->addCbFunc(startUpTime, redoTime, cb, vP);
}

void MainWindow::on_pushButton_add2_clicked()
{
    /*
    void *vP;
    vP = (void *) ArgForFunc2;
    int (*cb) (void *); // Function pointer
    cb = cb_func2;
    */
    uint startUpTime = uint(1000 * ui->doubleSpinBox_t2_Start->value());
    uint redoTime = uint(1000* ui->doubleSpinBox_t2_Redo->value());
    timMang->addCbFunc(startUpTime, redoTime, cb_func2, ArgForFunc2);
}

void MainWindow::on_pushButton_add3_clicked()
{
    uint startUpTime = uint(1000 * ui->doubleSpinBox_t3_Start->value());
    uint redoTime = uint(1000* ui->doubleSpinBox_t3_Redo->value());
    timMang->addCbFunc(startUpTime, redoTime, cb_func3, ArgForFunc3);
}

void MainWindow::on_pushButton_rem1_clicked()
{
    timMang->removeCbFunc(cb_func1);
}

void MainWindow::on_pushButton_rem2_clicked()
{
    timMang->removeCbFunc(cb_func2);
}

void MainWindow::on_pushButton_rem3_clicked()
{
    timMang->removeCbFunc(cb_func3);
}

void MainWindow::on_pushButton_addCb1_clicked()
{   
    uint startUpTime = uint(1000 * ui->doubleSpinBox_t4_Start->value());
    uint redoTime = uint(1000* ui->doubleSpinBox_t4_Redo->value());
    timMang->addCbFunc(startUpTime, redoTime, cb_func1a, ArgForFunc4);
}


void MainWindow::on_pushButton_rem1a_clicked()
{
    timMang->removeCbFunc(cb_func1a);
}
