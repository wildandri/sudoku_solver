#ifndef NUMBERDETECTOR_H
#define NUMBERDETECTOR_H

#include <iostream>
#include <opencv2/highgui.hpp>
#include <opencv2/core.hpp>
#include <opencv2/imgproc.hpp>

#include "tesseract/baseapi.h"
#include "leptonica/alltypes.h"

class NumberDetector
{
public:
    NumberDetector();

    std::vector<short int> findNumbers(cv::Mat &picture);

private:
    char num_detection(cv::Mat &sub);

    tesseract::TessBaseAPI *ocr;
};

#endif // NUMBERDETECTOR_H
