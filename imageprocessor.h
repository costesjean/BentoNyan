#ifndef IMAGEPROCESSOR_H
#define IMAGEPROCESSOR_H

#include "opencv2/opencv.hpp"

using namespace std;
using namespace cv;

class ImageProcessor
{
private:
    Mat fond;
    VideoCapture cap;
public:
    ImageProcessor();
    Mat getFond(){return fond;}
    vector<Scalar> computeAverage(Mat img);
    vector<double> computeAverage(vector<Point> vect);
    vector<Point> segmentation(Mat img, double threshold);
    void setBackground(Mat frame);
    string type2str(int type);
};

#endif // IMAGEPROCESSOR_H
