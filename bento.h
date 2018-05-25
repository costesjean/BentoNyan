#ifndef BENTO_H
#define BENTO_H

#include <QMainWindow>
#include "opencv2/opencv.hpp"
#include <iostream>
#include <QTimer>
#include <QDesktopWidget>

using namespace cv;
using namespace std;


namespace Ui {
class Bento;
}

class Bento : public QMainWindow
{
    Q_OBJECT

private slots:
        void on_timeout();
public:
    explicit Bento(QWidget *parent = 0);
    ~Bento();
    Mat getmat();


private:
    Ui::Bento *ui;
    Mat frame;
    VideoCapture cap;
    QTimer timer_;
    int frameWidth=320;
    int frameHeight=240;
    int subImageWidth=100;
    int subImageHeight=100;
    int templateWidth=25;
    int templateHeight=25;

};

#endif // BENTO_H
