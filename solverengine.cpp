#include "solverengine.h"

SolverEngine::SolverEngine(int height, int width):
    m_height(height),
    m_width(width),
    m_sudokuDetector(SudokuDetector(height, width)),
    m_numberDetector(NumberDetector())
{
}

bool SolverEngine::findSudoku()
{
    if(!m_picture.empty())
    {
        bool isDetectionSuccessfully = m_sudokuDetector.detect(m_picture);

        if(isDetectionSuccessfully)
        {
            this->m_detectedSudoku = m_sudokuDetector.getDetectedSudoku();
            cv::imshow("Result",m_detectedSudoku);
            return true;
        }
    }
    return false;
}


std::vector<short int> SolverEngine::detectNumbers(cv::Mat picture)
{
    m_sudokuNumbers = m_numberDetector.findNumbers(picture);

    return m_sudokuNumbers;
}

void SolverEngine::setPicture(cv::Mat &picture)
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

int SolverEngine::getHeight() const
{
    return m_height;
}

int SolverEngine::getWidth() const
{
    return m_width;
}
