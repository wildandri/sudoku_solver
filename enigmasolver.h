#ifndef ENIGMASOLVER_H
#define ENIGMASOLVER_H

#include "opencv2/core.hpp"

// Enum {Sudoku, Crossword, ...}


enum TYPE
{
    SUDOKU = 1,
    CROSSWORD = 2
};

class EnigmaSolver
{
public:
    EnigmaSolver();
    EnigmaSolver(cv::Mat picture,TYPE);

    void set_picture(cv::Mat picture);


private:
    cv::Mat m_picture;
    short int matrix[9][9];


    // Sudoku Detector
    // Number Detector
    // Sudoku Solver
};

#endif // ENIGMASOLVER_H


