#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "hal.h"
#include "timman.h"

#include <QMainWindow>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

    HAL *HwTimer;
    TimerManager *timMang;
    QString qsTemp;

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_pushButton_GetMil_clicked();
    void on_pushButton_GetMicro_clicked();

    void on_pushButton_StartTimer_clicked();
    void on_pushButton_Stop_clicked();

    void on_HwInterupt();
    void turnLedOn();
    void turnLedOff();


    void on_pushButton_add1_clicked();

    void on_pushButton_add2_clicked();

    void on_pushButton_rem1_clicked();

    void on_pushButton_rem2_clicked();

    void on_pushButton_add3_clicked();

    void on_pushButton_rem3_clicked();

    void on_pushButton_addCb1_clicked();

    void on_pushButton_clicked();

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
