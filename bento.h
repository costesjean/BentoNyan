#ifndef BENTO_H
#define BENTO_H

#include <QMainWindow>
#include "opencv2/opencv.hpp"
#include <iostream>
#include <QTimer>

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
    Mat* frame;
    VideoCapture cap;
    QTimer timer_;

};

#endif // BENTO_H
