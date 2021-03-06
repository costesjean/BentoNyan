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
    if(vect.size()>1000){
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
    }
    output.push_back(ravg);
    output.push_back(gavg);
    output.push_back(bavg);
    return output;
}

void ImageProcessor::setBackground(Mat frame){
    //Mat frame_ = this->equalization(frame);
    fond = frame;
}

vector<Point> ImageProcessor::segmentation(Mat img, double threshold){
    //Subtraction
    Mat output;
    Mat grayOutput;
    vector<Point> vect;
    absdiff(img, fond, output);
    //cvtColor(output,grayOutput, CV_RGB2GRAY);
    for (int i = 0; i < output.rows ; i++ ){
        for (int j = 0; j < output.cols ; j++ ){
            int R = (int)(output.at<Vec3b>(i,j)[0]);
            int G  = (int)(output.at<Vec3b>(i,j)[1]);
            int B = (int)(output.at<Vec3b>(i,j)[2]);
            //cout << R << " "<< G<< " " <<B<<endl;
            if ((R>threshold) || (G>threshold) || (B>threshold)){
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

Mat ImageProcessor::equalization( Mat inputImage)
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
        cvtColor(inputImage,ycr,CV_RGB2YCrCb);
        vector<Mat> channels2;
        split(ycr,channels2);
        Mat Y;
        equalizeHist( channels2[0], Y );
        vector<Mat> combined2;
        combined2.push_back(Y);
        combined2.push_back(channels2[1]);
        combined2.push_back(channels2[2]);
        Mat result2;
        merge(combined2,result2);
        Mat final;
        cvtColor(result2,final,CV_YCrCb2RGB);
        return final;
        //return result;
    }
    return Mat();
}


