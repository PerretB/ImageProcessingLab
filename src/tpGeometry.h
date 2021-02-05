
#pragma once

#include <opencv2/opencv.hpp>

cv::Mat transpose(cv::Mat image);

float interpolate_nearest(cv::Mat image, float y, float x);

float interpolate_bilinear(cv::Mat image, float y, float x);

cv::Mat expand(cv::Mat image, int factor, float(* interpolationFunction)(cv::Mat image, float y, float x));

cv::Mat rotate(cv::Mat image, float angle, float(* interpolationFunction)(cv::Mat image, float y, float x));
