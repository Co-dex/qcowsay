#include "mainwindow.h"
#include <QApplication>
#include <QString>
#include <QCommandLineOption>
#include <QCommandLineParser>
#include <cstdio>
#include <cstdlib>
//#define DEBUG_MODE

void paserArgv(QApplication &a, MainWindow &w);


void myMessageOutput(QtMsgType type, const QMessageLogContext &context, const QString &msg)
{
    QByteArray localMsg = msg.toLocal8Bit();
    switch (type) {
    case QtDebugMsg:
    #ifdef DEBUG_MODE
        fprintf(stderr, "Debug: %s (%s:%u, %s)\n", localMsg.constData(), context.file, context.line, context.function);
    #endif
        break;
    case QtInfoMsg:
        fprintf(stderr, "Info: %s (%s:%u, %s)\n", localMsg.constData(), context.file, context.line, context.function);
        break;
    case QtWarningMsg:
        fprintf(stderr, "Warning: %s (%s:%u, %s)\n", localMsg.constData(), context.file, context.line, context.function);
        break;
    case QtCriticalMsg:
        fprintf(stderr, "Critical: %s (%s:%u, %s)\n", localMsg.constData(), context.file, context.line, context.function);
        break;
    case QtFatalMsg:
        fprintf(stderr, "Fatal: %s (%s:%u, %s)\n", localMsg.constData(), context.file, context.line, context.function);
        abort();
    }
}

int main(int argc, char *argv[])
{
    qInstallMessageHandler(myMessageOutput); // in order to control qdebug() output.
    QApplication a(argc, argv);
    MainWindow w;
    paserArgv(a, w);
    w.move(1000,50);
    w.show();
    return a.exec();
}

void paserArgv(QApplication &a, MainWindow &w)
{
    QString file = "";
    QString height = "";
    QString time = "";
    a.setApplicationName("qcowsay");
    a.setApplicationVersion("0.0.1");
    QCommandLineParser paser;
    paser.addHelpOption();
    paser.addVersionOption();
    paser.setApplicationDescription("qcowsay is a small game based on Qt5 inspired by xcowsay");
    QCommandLineOption imageOption(QStringList() << "i" << "image", "Set custom image file path","filepath");
    paser.addOption(imageOption);
    QCommandLineOption heightOption(QStringList()<< "hi" << "height", "Set image default height, image will bound to the height default height is 500 px","height");
    paser.addOption(heightOption);
    QCommandLineOption timeOption(QStringList() << "t" << "time", "Set image dispaly time default is 3 seconds", "seconds");
    paser.addOption(timeOption);
    paser.setSingleDashWordOptionMode(QCommandLineParser::ParseAsLongOptions);
    paser.parse(a.arguments()); // setSingleDashWordOptionMode require this to apply change
    paser.process(a); // build-in options need this.

    file = paser.value(imageOption);
    time = paser.value(timeOption);
    height = paser.value(heightOption);

    w.setDefaultHight(height.toInt());
    w.setSeconds(time.toInt());
    w.setFilepath(file);

}
