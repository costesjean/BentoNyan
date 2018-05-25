#include "imageprocessor.h"

ImageProcessor::ImageProcessor()
{

}

vector<Scalar> computeAverage(Mat img){
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
