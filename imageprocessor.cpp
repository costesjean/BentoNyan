#include "imageprocessor.h"

ImageProcessor::ImageProcessor()
{

}

vector<Scalar> computeAverage(Mat img){
    vector<Mat> channels;
    split(img, chanels);
    Scalar r = mean(channels[0]);
    Scalar g = mean(channels[1]);
    Scalar b = mean(channels[2]);

    vector<Scalar> averages;
    averages.add(r[0]);
    averages.add(g[0]);
    averages.add(b[0]);
    return averages;
}
