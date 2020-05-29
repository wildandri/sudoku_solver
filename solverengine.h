#ifndef SOLVERENGINE_H
#define SOLVERENGINE_H

#include <iostream>
#include "opencv2/core.hpp"
#include <opencv2/highgui.hpp>

#include "sudokudetector.h"
#include "numberdetector.h"
#include "sudokusolver.h"

class SolverEngine
{
public:
    // Constructors
    SolverEngine(int height, int width);

    //Functions
    bool findSudoku();
    std::vector<short int> detectNumbers(cv::Mat picture);

    // Getter & Setter
    int getHeight() const;
    int getWidth() const;
    void setPicture(cv::Mat &picture);
    cv::Mat getPicture() const;
    cv::Mat getDetectedSudoku() const;
    std::vector<short int> getSudokuNumbers();


private:
    int m_height;
    int m_width;
    cv::Mat m_picture;
    cv::Mat m_detectedSudoku;
    std::vector<short int> m_sudokuNumbers;
    SudokuDetector m_sudokuDetector;
    NumberDetector m_numberDetector;
};

#endif // SOLVERENGINE_H
