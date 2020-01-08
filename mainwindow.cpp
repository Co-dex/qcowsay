#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QPainter>
#include <QBitmap>
#include <qdebug.h>
#include <QImageReader>
#include <QFileInfo>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    timer(new QTimer(this)),
    filepath(":/res/img/pet.png")
{
    ui->setupUi(this);
    this->setWindowFlag(Qt::FramelessWindowHint, true);
    this->setWindowFlag(Qt::WindowStaysOnTopHint, true);
    this->setAttribute(Qt::WA_TranslucentBackground, true);// if not add true the attr will be cleared
    this->setWindowOpacity(1);
    this->setCentralWidget(ui->label);
    connect(timer, SIGNAL(timeout()), this, SLOT(timeoutSlots()));
    petImage.load(filepath);


}

MainWindow::~MainWindow()
{
    delete ui;
    delete timer;

}

void MainWindow::setDefaultHight(int value)
{
    if(!value)
    {
        return;
    }
    defaultHight = value;
}

void MainWindow::setFilepath(const QString &value)
{
    if(!QFileInfo::exists(value))
        return;
    filepath = value;
    qDebug() <<"file path"<< filepath;
    QImageReader reader(filepath);
    float times = (float)reader.size().width() / reader.size().height();
    QSize sizetemp(times*defaultHight, defaultHight);
    reader.setScaledSize(sizetemp);
    petImage = reader.read();
}

void MainWindow::setSeconds(int value)
{
    if(!value) return;
    seconds = value;
}


void MainWindow::mousePressEvent(QMouseEvent *e)
{
    m_Pos = (e->globalPos()) - (this->pos());
    if(e->button() == Qt::RightButton)
    {
        QApplication::exit(0);
    }
    //bubble->show();
}

void MainWindow::mouseMoveEvent(QMouseEvent *e)
{
    this->move(e->globalPos() - m_Pos );
}

void MainWindow::showEvent(QShowEvent *event)
{
    //updateform();
}

void MainWindow::paintEvent(QPaintEvent *event)
{
    petSize = petImage.scaledToHeight(defaultHight).size();
    this->resize(petSize);
    qDebug() << size();
    petImage = petImage.scaled(petSize, Qt::IgnoreAspectRatio, Qt::SmoothTransformation);
    qDebug() << petImage.size();
    ui->label->setMask(QBitmap::fromImage(petImage.createAlphaMask()));
    QPainter painter(this);
    painter.drawImage(this->rect(), petImage);
    timer->start(seconds*1000);
}

void MainWindow::timeoutSlots()
{
    QApplication::exit(0);
}


void MainWindow::updateform()
{
//    QImageReader reader(filepath);
//    float times = (float)reader.size().width() / reader.size().height();
//    QSize sizetemp(times*defaultHight, defaultHight);
//    reader.setScaledSize(sizetemp);
//    petImage = reader.read();
    petSize = petImage.scaledToHeight(defaultHight).size();
    this->resize(petSize);
    qDebug() << size();
    petImage = petImage.scaled(petSize, Qt::IgnoreAspectRatio, Qt::SmoothTransformation);
    qDebug() << petImage.size();
    ui->label->setMask(QBitmap::fromImage(petImage.createAlphaMask()));
    ui->label->setPixmap(QPixmap::fromImage(petImage));
    ui->label->setText("Hello world");
    timer->start(seconds*1000);
}
