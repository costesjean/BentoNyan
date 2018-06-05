#ifndef BENTO_H
#define BENTO_H

#include <QMainWindow>
#include "opencv2/opencv.hpp"
#include <iostream>
#include <QTimer>
#include <QDesktopWidget>
#include "imageprocessor.h"
#include <QSound>

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
        void play_sound(int id);

public:
    explicit Bento(QWidget *parent = 0);
    ~Bento();
    Mat getmat();
    int calculCouleur(vector<double> vect);
    Mat equalization( Mat inputImage);


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
    QSound *son;
    std::vector<QSound*> playlist;
};

#endif // BENTO_H
