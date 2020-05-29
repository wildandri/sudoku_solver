#include "sudokudetector.h"


SudokuDetector::SudokuDetector(int width, int height):
    m_height(height),m_width(width)
{
    m_isComplete = false;

    m_detectedSudoku = cv::Mat::zeros(RESULT_SIZE, RESULT_SIZE, cv::COLOR_BGRA2GRAY);

    m_warpCorners[0] = cv::Point2f( 0.f, 0.f );
    m_warpCorners[1] = cv::Point2f( RESULT_SIZE - 1.f, 0.f );
    m_warpCorners[2] = cv::Point2f( RESULT_SIZE - 1.f , RESULT_SIZE - 1.f);
    m_warpCorners[3] = cv::Point2f( 0.f, RESULT_SIZE - 1.f );
}


bool SudokuDetector::detect(cv::Mat &picture)
{
    cv::Mat copy_pic = picture.clone();

    cv::GaussianBlur( copy_pic, copy_pic, cv::Size( 3, 3 ), 0 );
    cv::Canny(copy_pic,copy_pic,50,150);

    std::vector<std::vector<cv::Point>> contours;
    std::vector<cv::Vec4i> hierarchy;
    std::vector<cv::Point> approx;

    cv::findContours( copy_pic, contours, hierarchy, cv::RETR_TREE,cv::CHAIN_APPROX_SIMPLE, cv::Point(0, 0) );

    for(size_t i = 0; i < contours.size(); i ++){
       cv::approxPolyDP(contours[i], approx, cv::arcLength(contours[i], true)*0.02, true);

            // 4 Punkte                     // Fläche                //Keine selbst-überschneidungen
       if( approx.size() == 4 && fabs(cv::contourArea(approx)) > MIN_SUDOKU_AREA && cv::isContourConvex(approx) )
       {
           calcSudokuCorner(approx);
           cv::Mat warp_mat = cv::getPerspectiveTransform(m_sudoku_corner,m_warpCorners);
           cv::warpPerspective(picture,m_detectedSudoku,warp_mat,m_detectedSudoku.size());
           m_isComplete = true;
           return true;
       }
    }
    return false;
}

void SudokuDetector::calcSudokuCorner(std::vector<cv::Point> &approx)
{


    std::vector<std::vector<cv::Point>> squares_points;
    std::vector<cv::Point> approx_points;

    squares_points.push_back(approx);
    approx_points.push_back(approx[0]);
    approx_points.push_back(approx[2]);

    cv::RotatedRect minBox = minAreaRect(approx_points);

    //draw center point and rectangles in each edge
    cv::Point sudoku_center = minBox.center;

    //Points for perspective Transformation

    cv::Rect point_area[4];


    point_area[0] = cv::Rect(cv::Point2f(0.0f,0.0f),sudoku_center);
    point_area[1] = cv::Rect(cv::Point2f(m_width,0.0f),sudoku_center);
    point_area[2] = cv::Rect(cv::Point2f(m_width,m_height),sudoku_center);
    point_area[3] = cv::Rect(cv::Point2f(0.0f,m_height),sudoku_center);

    for (size_t j = 0; j < 4; j ++) {
        for(size_t k = 0; k < 4; k ++){
            if(squares_points[0][k].inside(point_area[j])){
                m_sudoku_corner[j]= squares_points[0][k];
            }
        }
    }
}

void SudokuDetector::drawDetectedSudoku(cv::Mat &picture)
{
    //********************** DRAW *******************************
    //edge markers
    cv::Mat drawPicture = picture.clone();
    cvtColor( drawPicture, drawPicture, cv::COLOR_GRAY2BGR );

    int marker_size = 20;
    drawMarker(drawPicture,m_sudoku_corner[0],cv::Scalar(0,0,255),cv::MARKER_CROSS,marker_size,1,8);
    drawMarker(drawPicture,m_sudoku_corner[1],cv::Scalar(0,255,0),cv::MARKER_CROSS,marker_size,1,8);
    drawMarker(drawPicture,m_sudoku_corner[2],cv::Scalar(255,0,0),cv::MARKER_CROSS,marker_size,1,8);
    drawMarker(drawPicture,m_sudoku_corner[3],cv::Scalar(50,225,235),cv::MARKER_CROSS,marker_size,1,8);

    //rectangle(m_picture,Point2f(0.0f,0.0f),m_picture_center,Scalar(255,0,0),1,LINE_4,0);
    //rectangle(m_picture,Point2f(m_picture.cols,0.0f),m_picture_center,Scalar(0,255,0),1,LINE_4,0);
    //rectangle(m_picture,Point2f(m_picture.cols,m_picture.rows),m_picture_center,Scalar(0,0,255),1,LINE_4,0);
    //rectangle(m_picture,Point2f(0.0f,m_picture.rows),m_picture_center,Scalar(255,255,255),1,LINE_4,0);

    //drawMarker(drawPicture,minBox.center,cv::Scalar(0,0,255),cv::MARKER_CROSS,20,1,cv::LINE_8);
    imshow("Markers",drawPicture);

    //************************************************************
}

bool SudokuDetector::isDetectionComplete() const
{
    return m_isComplete;
}


cv::Mat SudokuDetector::getDetectedSudoku() const
{
    return this->m_detectedSudoku;
}
