#include "solverengine.h"

SolverEngine::SolverEngine(){}

SolverEngine::SolverEngine(cv::Mat picture):
    m_picture(picture)
{

}

bool SolverEngine::findSudoku()
{
    if(!m_picture.empty())
    {
        SudokuDetector sd = SudokuDetector(m_picture);
        bool isDetectionSuccessfully = sd.detect();

        if(isDetectionSuccessfully)
        {
            this->m_detectedSudoku = sd.getDetectedSudoku();
            return true;
        }
    }
    return false;
}


std::vector<short int> SolverEngine::detectNumbers(cv::Mat picture)
{
    NumberDetector nd = NumberDetector();
    m_sudokuNumbers = nd.findNumbers(picture);

    return m_sudokuNumbers;
}

void SolverEngine::setPicture(cv::Mat picture)
{
    m_picture = picture;
}

cv::Mat SolverEngine::getDetectedSudoku() const
{
    return this->m_detectedSudoku;
}


std::vector<short int> SolverEngine::getSudokuNumbers(){
    return m_sudokuNumbers;
}
