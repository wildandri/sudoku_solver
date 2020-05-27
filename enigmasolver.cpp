#include "enigmasolver.h"

EnigmaSolver::EnigmaSolver()
{

}

EnigmaSolver::EnigmaSolver(cv::Mat picture, TYPE):
    m_picture(picture)
{

}

void EnigmaSolver::set_picture(cv::Mat picture)
{
    m_picture = picture;
}
