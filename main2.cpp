#include <opencv2/highgui.hpp>
#include <opencv2/core.hpp>
#include <opencv2/video.hpp>
#include <opencv2/opencv.hpp>
#include <iostream>

using namespace cv;
using namespace std;

int main(){
    VideoCapture video_reader("plastik.mp4");
    Mat frame_foto;

    while(true)
    {
        video_reader >> frame_foto;
        imshow("video", frame_foto);
        waitKey(1);
    }
    return 0;
}