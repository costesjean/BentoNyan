#ifndef IMAGEPROCESSOR_H
#define IMAGEPROCESSOR_H

using namespace std;
using namespace cv;

class ImageProcessor
{
public:
    ImageProcessor();
    vector<Scalar> computeAverage(Mat img);
};

#endif // IMAGEPROCESSOR_H
