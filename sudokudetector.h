#ifndef SUDOKUDETECTOR_H
#define SUDOKUDETECTOR_H

#include <math.h>
#include <vector>
#include <iostream>

#include "opencv2/core.hpp"
#include "opencv2/imgproc.hpp"
#include <opencv2/highgui.hpp>

class SudokuDetector
{
public:
    SudokuDetector();
    SudokuDetector(cv::Mat);

    bool detect();

    bool isDetectionComplete() const;
    cv::Mat getDetectedSudoku() const;


private:
    cv::Mat extractSudoku(std::vector<cv::Point>) const;

    cv::Mat m_picture;
    cv::Mat m_detectedSudoku;
    bool m_isComplete;
};

#endif // SUDOKUDETECTOR_H
