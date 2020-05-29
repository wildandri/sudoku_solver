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
    SudokuDetector(int height, int width);

    bool detect(cv::Mat &picture);

    bool isDetectionComplete() const;
    cv::Mat getDetectedSudoku() const;


private:
    void calcSudokuCorner(std::vector<cv::Point> &approx);
    void prepare();

    cv::Mat m_detectedSudoku;
    bool m_isComplete;
    int m_height;
    int m_width;
    long m_minSudokuArea;
    cv::Point2f m_warpCorners[4];
    cv::Point2f m_sudoku_corner[4];
};

#endif // SUDOKUDETECTOR_H
