#ifndef BENTO_H
#define BENTO_H

#include <QMainWindow>
#include "opencv2/opencv.hpp"
#include <iostream>
#include <QTimer>
#include <QDesktopWidget>
#include "imageprocessor.h"

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
        void on_timeout1();
        void resetFond();

public:
    explicit Bento(QWidget *parent = 0);
    ~Bento();
    Mat getmat();
    int calculCouleur(double hue);
    Mat equalization( Mat inputImage);
    double calculHue(double R, double G, double B);


private:
    Ui::Bento *ui;
    Mat frame;
    Mat frame2;
    VideoCapture cap;
    QTimer timer_;
    QTimer soundTimer_;
    int frameWidth=320;
    int frameHeight=240;
    int subImageWidth=100;
    int subImageHeight=100;
    int templateWidth=25;
    int templateHeight=25;
    ImageProcessor ip;
};

#endif // BENTO_H
