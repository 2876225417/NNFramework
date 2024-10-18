

#include "../headers/opencv.h"

#include <filesystem>
#include <iostream>

int main(){
    cv::Mat image = cv::imread("../NNFramework/pic_src/cont5.png", cv::IMREAD_GRAYSCALE);

    if(image.empty()) return 0;

    std::cout << __FILE__;

    cv::Mat bin_img;
    cv::Mat blurredImage;
    cv::GaussianBlur(image, blurredImage, cv::Size(7, 7), 1.5);

    cv::threshold(image,bin_img, 190, 255, cv::THRESH_BINARY);

    int kernelSize = 4;
    cv::Mat kernel =
            cv::getStructuringElement(cv::MORPH_ELLIPSE,
                                      cv::Size(kernelSize,
                                               kernelSize));

    cv::Mat morphImage;
    cv::morphologyEx(
            bin_img,
            morphImage,
            cv::MORPH_OPEN,
            kernel);



    cv::Mat edges;
    double lowerThreshold = 100;
    double upperThreshold = 200;
    cv::Canny(blurredImage, edges, lowerThreshold, upperThreshold);

    cv::imshow("morph", morphImage);
    cv::imshow("edges", edges);
    cv::imshow("cont5.jpg", image);
    cv::imshow("cont5_bin.jpg", bin_img);

    cv::waitKey(0);
}

