#include <iostream>
#include <fstream>
#include <sstream>
#include <opencv2/opencv.hpp>
#include "follower.hpp"

int main()
{
    Follower f;
    cv::VideoCapture cam(1);

    bool cont = true;
    bool save = false;
    cv::Mat img;
    while(cont) {
        cam.grab();
        cam.retrieve(img);
        cv::imshow("Stream", img);
        f.process(img, save);

        save = false;
        char c = (char)cvWaitKey(1);
        if(c == ' ')
            cont = false;
        else if(c == 'a')
            save = true;
    }

    return 0;
}

