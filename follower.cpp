#include "follower.hpp"
using namespace cv;

Follower::Follower()
    : m_st(Unknown)
{
    namedWindow("Binary");
    createTrackbar("min hue",        "Binary", NULL, 180);
    createTrackbar("max hue",        "Binary", NULL, 180);
    createTrackbar("min saturation", "Binary", NULL, 255);
    createTrackbar("max saturation", "Binary", NULL, 255);
    createTrackbar("min value",      "Binary", NULL, 255);
    createTrackbar("max value",      "Binary", NULL, 255);
}

Follower::~Follower()
{}

void Follower::process(const cv::Mat& img, bool save)
{
    Mat hsv;
    cvtColor(img, hsv, CV_BGR2HSV);

    Mat binary(img.size(), CV_8UC1);
    /* Creating the binary picture. */
    for(int i = 0; i < img.rows; ++i) {
        for(int j = 0; j < img.cols; ++j) {
            auto vec = hsv.at<Vec<unsigned char,3>>(i,j);

            if(vec[0] >= getTrackbarPos("min hue", "Binary")
                    && vec[0] <= getTrackbarPos("max hue", "Binary")
                    && vec[1] >= getTrackbarPos("min saturation", "Binary")
                    && vec[1] <= getTrackbarPos("max saturation", "Binary")
                    && vec[2] >= getTrackbarPos("min value", "Binary")
                    && vec[2] <= getTrackbarPos("max value", "Binary")
                    )
                binary.at<unsigned char>(i,j) = 255;
            else
                binary.at<unsigned char>(i,j) = 0;
        }
    }
    imshow("Binary", binary);

    static int nb = 0;
    if(save) {
        std::ostringstream oss;
        oss << "pict" << nb << ".png";
        imwrite("bin/" + oss.str(), binary);
        imwrite("img/" + oss.str(), img);
        ++nb;
    }
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

