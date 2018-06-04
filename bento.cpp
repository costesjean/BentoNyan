#include "bento.h"
#include "ui_bento.h"
#include "imageprocessor.h"
#include  <QGraphicsDropShadowEffect>

const unsigned int WIN_WIDTH  = 1600;
const unsigned int WIN_HEIGHT = 900;
const float MAX_DIMENSION     = 50.0f;

using namespace std;

Bento::Bento(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::Bento)
{
    //### Set up UI ###

    ui->setupUi(this);
    // Reglage de la taille/position
    setFixedSize(WIN_WIDTH, WIN_HEIGHT);
    move(QApplication::desktop()->screen()->rect().center() - rect().center());

    //### Set up camera ###

    connect(&timer_, SIGNAL(timeout()),this, SLOT(on_timeout()));
    timer_.start(30);
    cap.open(0);
    connect(&soundTimer_, SIGNAL(timeout()),this, SLOT(on_timeout1()));
    soundTimer_.start(1000);


    //### Set up Interface ###

    //Constantes
    //Width
    int win_width = 1200; // total
    int camWidth = 2*win_width/3; //camera
    int labelWidth = win_width/6;

    //Height
    int win_height = 900;
    int camHeight = 11*win_height/12;
    int height_title = (int)(win_height/12);
    // Layout contraintes et taille
    this->setFixedSize(win_width,win_height);
    this->centralWidget()->setMinimumSize(win_width,win_height);

    ui->titreLayout->setSizeConstraint(QLayout::SetMinimumSize);
    ui->mainLayout->setSizeConstraint(QLayout::SetMinimumSize);
    ui->userInstruction->setSizeConstraint(QLayout::SetMinimumSize);
    ui->couleurAJouerLayout->setSizeConstraint(QLayout::SetMinimumSize);
    ui->couleurJoueLayout->setSizeConstraint(QLayout::SetMinimumSize);
    ui->noteJouerLayout->setSizeConstraint(QLayout::SetMinimumSize);

    ui->camLabel->setFixedSize(camWidth,camHeight);
    ui->do_->setFixedWidth(labelWidth);ui->do_->setAlignment(Qt::AlignCenter);
    ui->re->setFixedWidth(labelWidth);ui->re->setAlignment(Qt::AlignCenter);
    ui->mi->setFixedWidth(labelWidth);ui->mi->setAlignment(Qt::AlignCenter);
    ui->fa->setFixedWidth(labelWidth);ui->fa->setAlignment(Qt::AlignCenter);
    ui->sol->setFixedWidth(labelWidth);ui->sol->setAlignment(Qt::AlignCenter);
    ui->la->setFixedWidth(labelWidth);ui->la->setAlignment(Qt::AlignCenter);
    ui->si->setFixedWidth(labelWidth);ui->si->setAlignment(Qt::AlignCenter);
    ui->couleurAJouerLabel->setFixedWidth(labelWidth);
    ui->couleurJoueeLabel->setFixedWidth(labelWidth);
    ui->couleurAJouerLabel->setAlignment(Qt::AlignCenter);
    ui->couleurJoueeLabel->setAlignment(Qt::AlignCenter);

    ui->appliName->setMinimumWidth(this->width());
    ui->appliName->setFixedHeight(height_title);
    ui->appliName->setAlignment(Qt::AlignCenter);

    // StyleSheet

    QString styleTitle = "color : #00d1b7; font-style : italic ; text-decoration : underline ; font-weight : bold; font-family : Merriweather; font-size : 50px ;";
    QString styleNote = "font-family : confortaa ; font-size : 20px ; ";
    QString styleSubTitle = "text-decoration : underline ; font-family : confortaa ; font-size : 20px ;";

    ui->couleurAJouerLabel->setStyleSheet(styleSubTitle);
    ui->couleurJoueeLabel->setStyleSheet(styleSubTitle);

    ui->re->setStyleSheet(styleNote);
    ui->do_->setStyleSheet(styleNote);
    ui->mi->setStyleSheet(styleNote);
    ui->fa->setStyleSheet(styleNote);
    ui->sol->setStyleSheet(styleNote);
    ui->la->setStyleSheet(styleNote);
    ui->si->setStyleSheet(styleNote);

    QGraphicsDropShadowEffect *effect = new QGraphicsDropShadowEffect(this);
    effect->setBlurRadius(0);
    effect->setColor(QColor("#92fff1"));
    effect->setOffset(3,3);
    ui->appliName->setGraphicsEffect(effect);
    ui->appliName->setStyleSheet(styleTitle);


    cout<<"width :"<<cap.get(CV_CAP_PROP_FRAME_WIDTH)<<endl;
    cout<<"height :"<<cap.get(CV_CAP_PROP_FRAME_HEIGHT)<<endl;
    cap.set(CV_CAP_PROP_FRAME_WIDTH,frameWidth);
    cap.set(CV_CAP_PROP_FRAME_HEIGHT,frameHeight);
    if(!cap.isOpened())  // check if we succeeded
    {
        cerr<<"Error openning the default camera"<<endl;
    }
    // Get frame
    cap >> frame;
    // Init output window
}
void Bento::on_timeout(){
    frame = this->getmat();
    cv::flip((frame),(frame),1);
    Mat dest;
    cvtColor(frame, dest,CV_BGR2RGB);
    cvtColor(frame, frame2,CV_BGR2RGB);
    QImage qframe= QImage((uchar*) dest.data, dest.cols, dest.rows, dest.step, QImage::Format_RGB888);
    QImage resized = qframe.scaled(ui->camLabel->width(),ui->camLabel->height(),Qt::KeepAspectRatio);
    ui->camLabel->setPixmap(QPixmap::fromImage(resized));
    //ui->camLabel->resize(ui->camLabel->pixmap()->size());
}

void Bento::on_timeout1(){
    vector<double> channels = ip.computeAverage(ip.segmentation(frame2,128.0));
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
