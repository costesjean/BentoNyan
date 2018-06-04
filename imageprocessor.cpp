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

        ravg+=fond.at<double>(vect.at(i).x, vect.at(i).y, 0);
        gavg+=fond.at<double>(vect.at(i).x, vect.at(i).y, 1);
        bavg+=fond.at<double>(vect.at(i).x, vect.at(i).y, 2);
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
    for (int i = 0; i < grayOutput.rows ; i++ ){
        for (int j = 0; j < grayOutput.cols ; j++ ){
            if (grayOutput.at<int>(i,j)>threshold){
                vect.push_back(Point(i,j));
                cout<<Point(i,j)<<" ";
                cout<<grayOutput.at<int>(Point(i,j))<<" ";
  //              cout<<fond.at<int>(Point(i,j))<<endl;
            }
        }
    }

    return vect;
}


