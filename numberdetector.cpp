#include "numberdetector.h"



NumberDetector::NumberDetector()
{

    ocr = new tesseract::TessBaseAPI();
    ocr->Init(NULL, "eng", tesseract::OEM_LSTM_ONLY);
    ocr->SetPageSegMode(tesseract::PSM_SINGLE_CHAR);
    ocr->SetVariable("debug_file", "/dev/null");
}

std::vector<short int> NumberDetector::findNumbers(cv::Mat &picture)
{

    std::vector<short int> sudokuNumbers;
    threshold(picture,picture,100,255,cv::THRESH_BINARY);
    cv::imshow("Number Detection" , picture);

    int x_size = picture.cols;
    int y_size = picture.rows;

    float x_dist = x_size / 9;
    float y_dist = y_size / 9;

    static cv::Rect2f num_rect[9][9];

    for (size_t k = 1; k < 10; k ++) {
        for (size_t j = 1; j < 10; j ++) {

            cv::Point2f p1 = cv::Point2f((j * x_dist) - x_dist + 5,(k * y_dist) - y_dist + 3);
            cv::Point2f p2 = cv::Point2f((j*x_dist) - 5, (k * y_dist) - 3);

            num_rect[k-1][j-1] = cv::Rect2f(p1,p2);
        }
    }

    for (size_t k = 0; k < 9; k ++) {
           for (size_t j = 0; j < 9; j ++) {

               cv::Mat sub_mat = cv::Mat(picture,num_rect[k][j]);

               char number = num_detection(sub_mat);
               if(!isdigit(number)){
                   sudokuNumbers.push_back(0);
                   continue;
               }
               sudokuNumbers.push_back(atoi(&number));
           }
       }
    return sudokuNumbers;
}


char NumberDetector::num_detection(cv::Mat &sub)
{
    ocr->SetImage((uchar*)sub.data, sub.cols, sub.rows, sub.channels(), sub.step1());
    ocr->Recognize(0);
    ///Run Tesseract OCR on image
    const char* out= ocr->GetUTF8Text();
    return *out;
}
