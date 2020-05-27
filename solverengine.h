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
    SolverEngine();
    SolverEngine(cv::Mat picture);

    //Functions
    bool findSudoku();
    std::vector<short int> detectNumbers(cv::Mat);



    // Getter & Setter
    void setPicture(cv::Mat picture);
    cv::Mat getPicture() const;
    cv::Mat getDetectedSudoku() const;
    std::vector<short int> getSudokuNumbers();


private:
    cv::Mat m_picture;
    cv::Mat m_detectedSudoku;
    std::vector<short int> m_sudokuNumbers;


    // Sudoku Detector
    // Number Detector
    // Sudoku Solver
};

#endif // SOLVERENGINE_H
