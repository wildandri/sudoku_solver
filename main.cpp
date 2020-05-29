#include "solverengine.h"
#include "opencv2/core.hpp"
#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <iostream>
#include <vector>


int main()
{
    std::cout << "- - - START PROGRAMM - - -" << std::endl;
    double time = (double)cv::getTickCount();

//     Load Image
//    cv::Mat frame = cv::imread("/home/andri/frametures/pic.jpg",cv::IMREAD_GRAYSCALE);
//    if( pic.empty() )
//    {
//      std::cout << "Could not open or find the image!\n" << std::endl;
//      return -1;
//    }


    // Video stream input
    cv::Mat frame;
    cv::VideoCapture cameraFrame(0);
    if(!cameraFrame.isOpened()){
        std::cout << "Video stream not opened !!!" << std::endl;
    }

    SolverEngine es = SolverEngine(1280,720);

    cameraFrame.set(cv::CAP_PROP_FRAME_WIDTH ,es.getWidth());
    cameraFrame.set(cv::CAP_PROP_FRAME_HEIGHT ,es.getHeight());

    do
    {
        cameraFrame >> frame;
        cvtColor( frame, frame, cv::COLOR_BGR2GRAY );
        cv::imshow("Livestream", frame);

        es.setPicture(frame);
        cv::waitKey(1);

    } while (!es.findSudoku());

    cameraFrame.release();

    std::vector<short int> result = es.detectNumbers(es.getDetectedSudoku());

    for(size_t i = 1; i < result.size() + 1; i++)
    {
        std::cout << result[i-1] << " ";
        if(i % 9 == 0){
            std::cout << std::endl;
        }
    }

    time = ((double)cv::getTickCount() - time)/cv::getTickFrequency();
    std::cout << "Times passed in ms: " << time*1000 << std::endl;

    std::cout << "- - - END PROGRAMM - - -" << std::endl;
    cv::waitKey(0);
    return 0;
}

