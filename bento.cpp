#include "bento.h"
#include "ui_bento.h"
#include "imageprocessor.h"
#include "math.h"
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
    soundTimer_.start(100);

    //### Reset Boutton ###
    connect(ui->resetFond,SIGNAL(clicked()),this,SLOT(resetFond()));


    //### Set up Interface ###

    //Constantes
    //Width
    int win_width = 1200; // total
    int camWidth = 2*win_width/3; //camera
    int labelWidth = win_width/6;

    //Height

    int camHeight = 900;
    int height_title = 70;
    int win_height = camHeight + height_title ;
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
   // ui->ImageFond->setFixedSize(50,50);

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
    frame = this->getmat();
    ip.setBackground(frame);

}
void Bento::on_timeout(){
    frame = this->getmat();
    // CAMERA
    Mat dest = frame;
    QImage qframe= QImage((uchar*) dest.data, dest.cols, dest.rows, dest.step, QImage::Format_RGB888);
    QImage resized = qframe.scaled(ui->camLabel->width(),ui->camLabel->height(),Qt::KeepAspectRatio);
    ui->camLabel->setPixmap(QPixmap::fromImage(resized));
    //ui->camLabel->resize(ui->camLabel->pixmap()->size());

    // FOND
   // Mat destFond = ip.getFond();
   Mat destFond = ip.getFond() - dest;
   //Mat destFond;
   // cvtColor(dest,destFond,CV_BGR2YCrCb);

    QImage qframeFond= QImage((uchar*) destFond.data, destFond.cols, destFond.rows, destFond.step, QImage::Format_RGB888);
    QImage resizedFond = qframeFond.scaled(ui->ImageFond->width(),ui->ImageFond->height(),Qt::KeepAspectRatio);
    ui->ImageFond->setPixmap(QPixmap::fromImage(resizedFond));
}

void Bento::on_timeout1(){
    vector<double> channels = ip.computeAverage(ip.segmentation(frame,40.0));
    cout << channels[0] << " "<< channels[1]<< " "<< channels[2]<<endl;
    double hue = this->calculHue(channels[0],channels[1],channels[2]);
    cout<<hue<<endl;
    //
}

void Bento::resetFond(){
    Mat fond = this->getmat();

    ip.setBackground(fond);
}

Mat Bento::getmat(){
    Mat m,dest,dest2;

    if(cap.isOpened())  // check if we succeeded
    {
        //Lecture
        cap.read(m);
        cvtColor(m, dest,CV_BGR2RGB);
        cv::flip((dest),(dest),1);
        dest2 = this->equalization(dest);
    // get a new frame from camera
    }
    else{
        cerr<<"Error openning the default camera"<<endl;
    }
    return dest2;
}

Bento::~Bento()
{
    delete ui;
}

int Bento::calculCouleur(vector<double> vect){
    /*if (){ // Red

    }
    else if(){ // Green

    }
    else if(){ // Blue

    }
    else if(){ // Magenta

    }
    else if(){ // Cyan

    }
    else if(){// Yellow

    }
    else if(){ // White

    }*/
}
Mat Bento::equalization( Mat inputImage)
{
    if(inputImage.channels() >= 3)
    {
        vector<Mat> channels;
        split(inputImage,channels);
        Mat B,G,R;
        equalizeHist( channels[0], B );
        equalizeHist( channels[1], G );
        equalizeHist( channels[2], R );
        vector<Mat> combined;
        combined.push_back(B);
        combined.push_back(G);
        combined.push_back(R);
        Mat result;
        merge(combined,result);

        Mat ycr ;
        cvtColor(inputImage,ycr,CV_RGB2Lab);
        vector<Mat> channels2;
        split(ycr,channels2);
        Mat L;
        equalizeHist( channels2[0], L );
        vector<Mat> combined2;
        combined2.push_back(L);
        combined2.push_back(channels2[1]);
        combined2.push_back(channels2[2]);
        Mat result2;
        merge(combined2,result2);
        Mat final;
        cvtColor(result2,final,CV_Lab2RGB);
        return final;
        //return result;
    }
    return Mat();
}

double Bento::calculHue(double R, double G, double B){
    double hue, min, max;
    if (R>G && R>B){ // max R
        max = R;
        if (G<B){
             min = G;
        }
        else{
            min = B;
         }
         hue = (G-B)/(max-min);
    }
    else if(G>R && G>B){ // max G
        if (R<B){
            min = R;
        }
        else{
            min = B;
        }
        hue = 2.0 + (B-R)/(max-min);
    }
    else{ // Max B
        max = B;
        if(R<G){
            min = R;
        }
        else{
            min = G;
        }
        hue = 4.0 + (R-G)/(max-min);
    }
    hue = hue *60;
    if (hue<0){
        hue +=360;
    }
    return hue;
}
