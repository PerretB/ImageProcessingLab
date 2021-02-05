
#pragma once

#include <opencv2/opencv.hpp>


cv::Mat inverse(cv::Mat image);

cv::Mat threshold(cv::Mat image, float lowT, float highT);

cv::Mat normalize(cv::Mat image,  float minValue=0, float maxValue=1);

cv::Mat quantize(cv::Mat image, int numberOfLevels);

cv::Mat equalize(cv::Mat image);

cv::Mat thresholdOtsu(cv::Mat image);

