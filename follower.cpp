#include "follower.hpp"
using namespace cv;

Follower::Follower()
    : m_st(Unknown)
{}

Follower::~Follower()
{}

void Follower::process(const cv::Mat& img)
{
    Mat binary(img.size(), CV_8UC1);
    /* Creating the binary picture. */
    for(int i = 0; i < img.rows; ++i) {
        for(int j = 0; j < img.cols; ++j) {
            auto vec = img.at<Vec<unsigned char,3>>(i,j);
            if(vec[0] < 50 && vec[1] < 50 && vec[2] > 200)
                binary.at<unsigned char>(i,j) = 255;
            else
                binary.at<unsigned char>(i,j) = 0;
        }
    }
    imshow("Binary", binary);
}

const char* Follower::status() const
{
    switch(m_st) {
        case Left:    return "left";
        case Right:   return "right";
        case Center:  return "center";
        case Unknown: return "unknown";
    }
    return "error";
}

Follower::Status Follower::pos() const
{
    return m_st;
}

