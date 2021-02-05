
#pragma once

#include <opencv2/opencv.hpp>

cv::Mat meanFilter(cv::Mat image, int size);

cv::Mat convolution(cv::Mat image, cv::Mat kernel);

cv::Mat edgeSobel(cv::Mat image);

cv::Mat bilateralFilter(cv::Mat image, cv::Mat kernel, double sigma_r);