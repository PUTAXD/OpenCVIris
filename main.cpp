#include <opencv2/highgui.hpp>
#include <opencv2/core.hpp>
#include <opencv2/video.hpp>
#include <opencv2/opencv.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <iostream>

using namespace cv;
using namespace std;

int hue_high, sat_high, val_high;
int hue_low, sat_low, val_low;

int main()
{
    // namedWindow("Mask");

    // //nilai tinggi
    // createTrackbar("Hue High","Mask", &hue_high, 255);
    // createTrackbar("Sat High","Mask", &sat_high, 255);
    // createTrackbar("Val High","Mask", &val_high, 255);

    // //nilai rendah
    // createTrackbar("Hue Low","Mask", &hue_low, 255);
    // createTrackbar("Sat Low","Mask", &sat_low, 255);
    // createTrackbar("Val Low","Mask", &val_low, 255);

    // //set awal low;
    // setTrackbarPos("Hue Low","Mask", 90);
    // setTrackbarPos("Sat Low","Mask", 0);
    // setTrackbarPos("Val Low","Mask", 97);

    // //set awal high
    // setTrackbarPos("Hue High","Mask", 255);
    // setTrackbarPos("Sat High","Mask", 127);
    // setTrackbarPos("Val High","Mask", 255);

    VideoCapture video_reader("D:/robotic 22/programming/projectiris/plastik.mkv");
    Mat frame_foto;

    double largest_area=0;
    int largest_contour_index=0;
    Rect bounding_rect;
     while (true)
    {
        video_reader >> frame_foto;
        Mat gaussian_blur;
        GaussianBlur(frame_foto, gaussian_blur, Size(5, 5),0,0);
        Mat hsv;
        cvtColor(gaussian_blur,hsv,cv::COLOR_BGR2HSV);
        // imshow("HSV",hsv);
        // waitKey(20);

        // Mat track;
        // imshow("video3",frame_foto);
        // inRange(hsv,Scalar(hue_low,sat_low,val_low),Scalar(hue_high,sat_high,val_high),track);
        // imshow("video4",track);
        // waitKey(20);

        Mat bola;
        inRange(hsv,Scalar(0,151,60),Scalar(28,255,255), bola);
        // imshow("Bola", bola);
        // waitKey(10);

        Mat plastik;
        inRange(hsv, Scalar(90, 0, 97), Scalar(255, 127, 255), plastik);
        // imshow("plastik",plastik);
        // waitKey(10);

        vector<vector<Point>> contour_plastik;
        vector<Vec4i> hierarchy_plastik;

        findContours(plastik, contour_plastik, hierarchy_plastik, RETR_EXTERNAL,CHAIN_APPROX_SIMPLE);
        // Mat mask = cv::Mat::zeros(plastik.size(), CV_8UC3);
        Mat hasil;
        Rect r_plastik;
        for (int i = 0; i < contour_plastik.size(); i++)
        {
            if (contourArea(contour_plastik[i]) > 4000)
            {
                drawContours(frame_foto, contour_plastik, i, Scalar(200,0,0), 2);
                rectangle(frame_foto, boundingRect(contour_plastik[i]), Scalar(255, 255, 255), 1);
            }
        }

        // Mat plastik2;
        // threshold(hasil,plastik2,255,255,255);
        // imshow("Bola",plastik2);
        // waitKey(10);
        // imshow("out",hasil);
        
        vector<vector<Point>> contour_bola;
        vector<Vec4i> hierarchy_bola;
        
        findContours(bola, contour_bola, hierarchy_bola, RETR_EXTERNAL, CHAIN_APPROX_SIMPLE);
        // print contour terbesar bola 
        for (int i = 0; i < contour_bola.size(); i++)
        {
            if (contourArea(contour_bola[i]) > 1000)
            {
                drawContours(frame_foto, contour_bola, i, Scalar(115,226,167), 2);
            }
        }
        //titik tengah bola
        Point center;
        vector<Moments> M(contour_bola.size());
        for(int i =0;i<(int)contour_bola.size();i++){
            if (contourArea(contour_bola[i]) > 1000)
            {
                M[i] = moments(contour_bola[i]);
                
                Point center((int)(M[i].m10/M[i].m00), (int)(M[i].m01 / M[i].m00));
                cout << "Bola : X = " << center.x << " Y = " << center.y << " " << endl;
                circle(frame_foto, center, 5, Scalar(255, 255, 255), FILLED);
                if(center.x>208&&center.x<480&&center.y<292&&center.y>88){
                    putText(frame_foto, "Bola Masuk!", center,FONT_HERSHEY_SIMPLEX,1.0,Scalar(1,1,1),2);
                }
            }
        }

        // titik tengah plastik
        Point center2;
        vector<Moments> P(contour_plastik.size());
        for (int i = 0; i < (int)contour_plastik.size(); i++)
        {
            if (contourArea(contour_plastik[i]) > 1000)
            {
                P[i] = moments(contour_plastik[i]);
                Point center2((int)(P[i].m10 / P[i].m00),(int) (P[i].m01 / P[i].m00));
                cout << "plastik : X = " << center2.x << " Y = " << center2.y << " " << endl;
                circle(frame_foto, center2, 5, Scalar(255, 255, 255), FILLED);
            }
        }
        imshow("out", frame_foto);
        waitKey(10);
 
    }


    return 0;
}