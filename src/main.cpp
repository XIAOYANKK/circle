#include <opencv2/opencv.hpp>  
#include <opencv2/imgproc/imgproc.hpp>  

int main()
{
    //开起摄像头
    cv::VideoCapture capture;
    capture.open(1);


    cv::Mat edges;  //定义转化的灰度图
    if (!capture.isOpened())
        return -1;
    namedWindow("【效果图】", cv::WINDOW_NORMAL);
    while (1)
    {
        cv::Mat frame;
        capture >> frame;
        if (!frame.data)
            return -1;
        cvtColor(frame, edges,cv::COLOR_BGR2GRAY);
        //高斯滤波
        GaussianBlur(edges, edges, cv::Size(7, 7), 2, 2);
        std::vector<cv::Vec3f> circles;
        //霍夫圆
        HoughCircles(edges, circles, cv::HOUGH_GRADIENT, 1.5, 10, 200, 100, 0, 0);
        for (size_t i = 0; i < circles.size(); i++)
        {
            cv::Point center(cvRound(circles[i][0]), cvRound(circles[i][1]));
            int radius = cvRound(circles[i][2]);
            //绘制圆心  
            circle(frame, center, 3, cv::Scalar(0, 255, 0), -1, 8, 0);
            //绘制圆轮廓  
            circle(frame, center, radius, cv::Scalar(155, 50, 255), 3, 8, 0);
        }


        imshow("【效果图】", frame);


        cv::waitKey(30);

    }

    return 0;
}

