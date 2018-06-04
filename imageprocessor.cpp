#include "imageprocessor.h"
#include <iostream>

using namespace cv;

ImageProcessor::ImageProcessor()
{

}

vector<Scalar> ImageProcessor::computeAverage(Mat img){
    vector<Mat> channels;
    split(img, channels);
    Scalar r = mean(channels[0]);
    Scalar g = mean(channels[1]);
    Scalar b = mean(channels[2]);

    vector<Scalar> averages;
    averages.push_back(r[0]);
    averages.push_back(g[0]);
    averages.push_back(b[0]);
    return averages;
}

vector<double> ImageProcessor::computeAverage(vector<Point> vect){
    vector<double> output;
    double ravg = 0;
    double gavg = 0;
    double bavg = 0;
    for(int i = 0 ; i<vect.size(); i++){
    //cout << fond.at<double>(vect[i])<<endl ;
        //string ty =  type2str( fond.type() );
        //cout << ty << endl;
        //Vec3f vect3d =  fond.at<Vec3f>(vect.at(i).x,vect.at(i).y);
        int R = (int)(fond.at<Vec3b>(vect.at(i).x,vect.at(i).y)[0]);
        int G  = (int)(fond.at<Vec3b>(vect.at(i).x,vect.at(i).y)[1]);
        int B = (int)(fond.at<Vec3b>(vect.at(i).x,vect.at(i).y)[2]);
       // cout << R << " "<< G<< " " <<B<<endl;
        ravg+=R;
        gavg+=G;
        bavg+=B;
    }
    ravg/=vect.size();
    gavg/=vect.size();
    bavg/=vect.size();
    output.push_back(ravg);
    output.push_back(gavg);
    output.push_back(bavg);
    return output;
}

void ImageProcessor::setBackground(Mat frame){
    fond = frame;
}

vector<Point> ImageProcessor::segmentation(Mat img, double threshold){
    //Subtraction
    Mat output;
    Mat grayOutput;
    vector<Point> vect;
    output = img - fond;

    cvtColor(output,grayOutput, CV_RGB2GRAY);
    for (int i = 0; i < output.rows ; i++ ){
        for (int j = 0; j < output.cols ; j++ ){
            int R = (int)(fond.at<Vec3b>(i,j)[0]);
            int G  = (int)(fond.at<Vec3b>(i,j)[1]);
            int B = (int)(fond.at<Vec3b>(i,j)[2]);
            //cout << R << " "<< G<< " " <<B<<endl;
            if (output.at<int>(i,j)>threshold){
                vect.push_back(Point(i,j));
                //cout<<Point(i,j)<<" ";
                //cout<<output.at<int>(Point(i,j))<<" ";
  //              cout<<fond.at<int>(Point(i,j))<<endl;
            }
        }
    }
    return vect;
}

string ImageProcessor::type2str(int type) {
  string r;

  uchar depth = type & CV_MAT_DEPTH_MASK;
  uchar chans = 1 + (type >> CV_CN_SHIFT);

  switch ( depth ) {
    case CV_8U:  r = "8U"; break;
    case CV_8S:  r = "8S"; break;
    case CV_16U: r = "16U"; break;
    case CV_16S: r = "16S"; break;
    case CV_32S: r = "32S"; break;
    case CV_32F: r = "32F"; break;
    case CV_64F: r = "64F"; break;
    default:     r = "User"; break;
  }

  r += "C";
  r += (chans+'0');

  return r;
}



