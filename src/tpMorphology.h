
#pragma once

#include <opencv2/opencv.hpp>


cv::Mat median(cv::Mat image, int size);

cv::Mat erode(cv::Mat image, cv::Mat structuringElement);

cv::Mat dilate(cv::Mat image, cv::Mat structuringElement);

cv::Mat open(cv::Mat image, cv::Mat structuringElement);

cv::Mat close(cv::Mat image, cv::Mat structuringElement);

cv::Mat morphologicalGradient(cv::Mat image, cv::Mat structuringElement);
