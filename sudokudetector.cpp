#include "sudokudetector.h"


SudokuDetector::SudokuDetector()
{
    m_isComplete = false;
}

SudokuDetector::SudokuDetector(cv::Mat picture):
    m_picture(picture)
{
    m_isComplete = false;
}

bool SudokuDetector::detect()
{
    cv::Mat copy_pic = m_picture.clone();

    cv::GaussianBlur( copy_pic, copy_pic, cv::Size( 3, 3 ), 0 );
    cv::Canny(copy_pic,copy_pic,50,150);


    std::vector<std::vector<cv::Point>> contours;
    std::vector<cv::Vec4i> hierarchy;
    std::vector<cv::Point> approx;


    cv::findContours( copy_pic, contours, hierarchy, cv::RETR_TREE,cv::CHAIN_APPROX_SIMPLE, cv::Point(0, 0) );

    for(size_t i = 0; i < contours.size(); i ++){
       cv::approxPolyDP(contours[i], approx, cv::arcLength(contours[i], true)*0.02, true);

            // 4 Punkte                     // Fläche                //Keine selbst-überschneidungen
       if( approx.size() == 4 && fabs(cv::contourArea(approx)) > 60000 && cv::isContourConvex(approx) )
       {
           m_detectedSudoku = extractSudoku(approx);
           cv::imshow("result: ", m_detectedSudoku);
           m_isComplete = true;
           return true;
       }
    }
    return false;
}

cv::Mat SudokuDetector::extractSudoku(std::vector<cv::Point> approx) const
{
    cv::Mat warp_dst = cv::Mat::zeros(m_picture.rows,m_picture.cols,m_picture.type());

    std::vector<std::vector<cv::Point>> squares_points;
    std::vector<cv::Point> approx_points;

    squares_points.push_back(approx);
    approx_points.push_back(approx[0]);
    approx_points.push_back(approx[2]);

    cv::RotatedRect minBox = minAreaRect(approx_points);

    //draw center point and rectangles in each edge
    cv::Point sudoku_center = minBox.center;

    //Points for perspective Transformation
    cv::Point2f sudoku_corner[4];
    cv::Point2f mat_corner[4];
    cv::Rect point_area[4];

    mat_corner[0] = cv::Point2f( 0.f, 0.f );
    mat_corner[1] = cv::Point2f( warp_dst.cols - 1.f, 0.f );
    mat_corner[2] = cv::Point2f( warp_dst.cols - 1.f , warp_dst.rows - 1.f);
    mat_corner[3] = cv::Point2f( 0.f, warp_dst.rows - 1.f );

    point_area[0] = cv::Rect(cv::Point2f(0.0f,0.0f),sudoku_center);
    point_area[1] = cv::Rect(cv::Point2f(m_picture.cols,0.0f),sudoku_center);
    point_area[2] = cv::Rect(cv::Point2f(m_picture.cols,m_picture.rows),sudoku_center);
    point_area[3] = cv::Rect(cv::Point2f(0.0f,m_picture.rows),sudoku_center);

    for (size_t j = 0; j < 4; j ++) {
        for(size_t k = 0; k < 4; k ++){
            if(squares_points[0][k].inside(point_area[j])){
                sudoku_corner[j]= squares_points[0][k];
            }
        }
    }


    //********************** DRAW *******************************
    //edge markers
    cv::Mat m_picture_copy = m_picture.clone();
    cvtColor( m_picture_copy, m_picture_copy, cv::COLOR_GRAY2BGR );

    int marker_size = 20;
    drawMarker(m_picture_copy,sudoku_corner[0],cv::Scalar(0,0,255),cv::MARKER_CROSS,marker_size,1,8);
    drawMarker(m_picture_copy,sudoku_corner[1],cv::Scalar(0,255,0),cv::MARKER_CROSS,marker_size,1,8);
    drawMarker(m_picture_copy,sudoku_corner[2],cv::Scalar(255,0,0),cv::MARKER_CROSS,marker_size,1,8);
    drawMarker(m_picture_copy,sudoku_corner[3],cv::Scalar(50,225,235),cv::MARKER_CROSS,marker_size,1,8);

    //rectangle(m_picture,Point2f(0.0f,0.0f),m_picture_center,Scalar(255,0,0),1,LINE_4,0);
    //rectangle(m_picture,Point2f(m_picture.cols,0.0f),m_picture_center,Scalar(0,255,0),1,LINE_4,0);
    //rectangle(m_picture,Point2f(m_picture.cols,m_picture.rows),m_picture_center,Scalar(0,0,255),1,LINE_4,0);
    //rectangle(m_picture,Point2f(0.0f,m_picture.rows),m_picture_center,Scalar(255,255,255),1,LINE_4,0);

    drawMarker(m_picture_copy,minBox.center,cv::Scalar(0,0,255),cv::MARKER_CROSS,20,1,cv::LINE_8);
    imshow("Markers",m_picture_copy);

    //************************************************************



    cv::Mat warp_mat = cv::getPerspectiveTransform(sudoku_corner,mat_corner);
    cv::warpPerspective(m_picture,warp_dst,warp_mat,warp_dst.size());

    return warp_dst;

}

bool SudokuDetector::isDetectionComplete() const
{
    return m_isComplete;
}


cv::Mat SudokuDetector::getDetectedSudoku() const
{
    return this->m_detectedSudoku;
}
