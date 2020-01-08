#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QImage>
#include <QPaintEvent>
#include <QMouseEvent>
#include <QPainter>
#include <QTimer>


namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow() override;
    void setDefaultHight(int value);
    void setFilepath(const QString &value);

    void setSeconds(int value);

private:
    Ui::MainWindow *ui;
    QImage petImage;
    QSize petSize;
    int defaultHight = 500;
    int seconds = 3;
    QPoint m_Pos; // 存储移动坐标偏移
    QString filepath; // image file path
    void updateform();
    QTimer *timer;

    // QWidget interface
protected:
    void mousePressEvent(QMouseEvent *e) override;
    void mouseMoveEvent(QMouseEvent *event) override;
    void showEvent(QShowEvent *event) override;
    void paintEvent(QPaintEvent *event) override;


private slots:
    void timeoutSlots();

};

#endif // MAINWINDOW_H
