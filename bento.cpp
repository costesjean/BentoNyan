#include "bento.h"
#include "ui_bento.h"

Bento::Bento(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::Bento)
{
    //### Set up UI ###

    ui->setupUi(this);

    //### Set up camera ###

    connect(&timer_, SIGNAL(timeout()),this, SLOT(on_timeout()));
    timer_.start(30);
    frame = new Mat();
    cap.open(0);


    //### Set up Interface ###

    //Constantes
    int win_width = 800;
    int win_height = 600;
    int height_title = (int)(win_height/12);
    // Layout contraintes et taille
    this->setMinimumSize(win_width,win_height);
    ui->centralWidget->setMinimumSize(win_width,win_height);
    ui->titreLayout->setSizeConstraint(QLayout::SetMinAndMaxSize);
    ui->appliName->setMaximumSize(win_width,height_title);
    ui->appliName->setAlignment(Qt::AlignCenter);
    //Style
    ui->appliName->setStyleSheet("color: red");



}
void Bento::on_timeout(){
    *frame = this->getmat();
    cv::flip((*frame),(*frame),1);
    Mat dest;
    cvtColor(*frame, dest,CV_BGR2RGB);
    QImage qframe= QImage((uchar*) dest.data, dest.cols, dest.rows, dest.step, QImage::Format_RGB888);
    QImage resized = qframe.scaled(ui->camLabel->width(),ui->camLabel->height(),Qt::KeepAspectRatio);
    ui->camLabel->setPixmap(QPixmap::fromImage(resized));
    //ui->camLabel->resize(ui->camLabel->pixmap()->size());
}

Mat Bento::getmat(){
    Mat m;

    if(cap.isOpened())  // check if we succeeded
    {
        //Lecture
        cap >> m; // get a new frame from camera
    }
    else{
        cerr<<"Error openning the default camera"<<endl;
    }
    return m;
}

Bento::~Bento()
{
    delete ui;
}
