#include "mainwindow.h"
#include <QApplication>
#include <QMutexLocker>
#include <QFile>
#include <QTextStream>

void messageHandler(QtMsgType type, const QMessageLogContext &context, const QString &message)
{
    static QMutex mutex;
    QMutexLocker lock(&mutex);
    QFile outFile("file.log");

    QDateTime dateTime(QDateTime::currentDateTime());
    QString timeStr(dateTime.toString("dd-MM-yyyy HH:mm:ss,zzz"));
    QString contextString(QString("(%1, %2").arg(context.function).arg(context.line, 4));
    QString qsLine(QString("%1 %2: %3 \n").arg(timeStr).arg(contextString).arg(message));

    outFile.open(QIODevice::WriteOnly | QIODevice::Append);
    QTextStream stream(&outFile);
    QTextStream consol(stdout);
    switch (type) {
        case QtDebugMsg:
            stream << "Debug: "<<qsLine;
            consol << "Debug: "<<qsLine;
            break;

        case QtInfoMsg:
            stream << "Info:  "<<qsLine;
            consol << "Info:  "<<qsLine;
            break;

        case QtWarningMsg:
            stream << "Warning: "<<qsLine;
            consol << "Warning: "<<qsLine;
            break;

        case QtCriticalMsg:
            stream << "Critical: "<<qsLine;
            consol << "Critical: "<<qsLine;
            break;

        case QtFatalMsg:
            stream << "Fatal: "<<qsLine;
            consol << "Fatal: "<<qsLine;
            abort();
    }
}


int main(int argc, char *argv[])
{
    qInstallMessageHandler(messageHandler);
    QApplication a(argc, argv);
    MainWindow w;
    w.show();

    return a.exec();
}
