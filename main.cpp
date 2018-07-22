#include <opencv2/opencv.hpp>

#include <iostream>

using namespace std;
using namespace cv;



Mat change_contrast(Mat src, double alpha, int beta) {
    Mat new_image = Mat::zeros( src.size(), src.type() );

    /// 执行运算 new_image(i,j) = alpha*image(i,j) + beta
    for( int y = 0; y < src.rows; y++ )
    {
        for( int x = 0; x < src.cols; x++ )
        {
            for( int c = 0; c < 3; c++ )
            {
                new_image.at<Vec3b>(y,x)[c] = saturate_cast<uchar>( alpha*( src.at<Vec3b>(y,x)[c] ) + beta );
            }
        }
    }

    return new_image;
}


/*
H参数表示色彩信息，即所处的光谱颜色的位置。该参数用一角度量来表示，红、绿、蓝分别相隔120度。互补色分别相差180度。
纯度S为一比例值，范围从0到1，它表示成所选颜色的纯度和该颜色最大的纯度之间的比率。S=0时，只有灰度。
V表示色彩的明亮程度，范围从0到1。有一点要注意：它和光强度之间并没有直接的联系。*/

Mat change_chroma(Mat src, float h, float s, float v) {
    Mat new_image;

    cv::cvtColor(src, new_image, CV_BGR2HSV);


    for( int y = 0; y < src.rows; y++ )
    {
        for( int x = 0; x < src.cols; x++ )
        {
            new_image.at<Vec3b>(y,x)[0] = static_cast<uchar>((int) (new_image.at<Vec3b>(y,x)[0] + h) % 360);
            new_image.at<Vec3b>(y,x)[1] = static_cast<uchar>(new_image.at<Vec3b>(y,x)[1] * s);
            new_image.at<Vec3b>(y,x)[2] = static_cast<uchar>(new_image.at<Vec3b>(y,x)[2] * v);
        }
    }

    cv::cvtColor(new_image, new_image, CV_HSV2BGR);

    return new_image;
}

int main()
{

    Mat image = imread("./input.jpg");

    Mat contrast_test, chroma_test;

    contrast_test = change_contrast(image, 2, 50); // alpha ~ [1,3], beta ~ [0,100]

    chroma_test = change_chroma(image, 180, 1, 1); // h ~ [0, 360], s ~ [0,1], v ~ [0,1]

    imshow("Original Image", image);
    imshow("New Image", chroma_test);


    waitKey(0);
    return 0;
}