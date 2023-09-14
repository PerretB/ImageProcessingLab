#include "common.h"
#include <exception>
#include <iostream>
#include <map>
#include "stdio.h"

using namespace cv;
using namespace std;

cv::Mat imreadHelper(std::string filename, bool forceFloat, bool forceGrayScale)
{
    cv::Mat image;
    image = cv::imread( filename.c_str(), (forceGrayScale)? 0 : -1 );

    if( !image.data )
    {
        throw std::runtime_error("No Image Data");
    }
    cv::Mat tmp;

    if(forceFloat)
    {
        int channels = image.channels();
        int depth = image.depth();
        int targetType;
        if(channels == 1)
            targetType = CV_32FC1;
        else if(channels == 3)
            targetType = CV_32FC3;
        else
            throw std::runtime_error("Unsupported number of channels");


        image.convertTo(tmp, targetType);

        if(depth<=1)
            tmp /= 255.0;
    } else {
        tmp = image;
    }


    return tmp;

}

void imwriteHelper(cv::Mat image, std::string filename)
{
    int depth = image.depth();
    if(depth<=1)
    {
        cv::imwrite(filename.c_str(), image);
    } else {
        double min, max;
        cv::minMaxLoc(image, &min, &max);
        if(min < -0.000001 || max > 1.000001)
            std::cerr << "!!!  Warning, saved image values not between 0 and 1." << std::endl;

        cv::Mat tmp = image.clone();
        tmp *= 255;

        cv::imwrite(filename.c_str(), tmp);
    }

}

void showimage(cv::Mat image, const char * name)
{
    static int count = 1;
    const char * tn;
    if (name==NULL)
    {
         char op[30];
         snprintf(op, 30, "%d", count++);
         tn = op;
    }else
    {
        tn = name;
    }

    cv::namedWindow( tn, cv::WINDOW_AUTOSIZE );
    cv::imshow( tn, image );
}


cv::Mat remap_labels(cv::Mat label_image)
{
    map<int, int> label_map;
    label_map[0] = 0;

    Mat res = Mat::zeros(label_image.rows, label_image.cols, CV_32SC1);
    int current_label = 1;

    for(int y = 0; y < label_image.rows; ++y){
        for(int x = 0; x < label_image.cols; ++x){
            int l = label_image.at<int>(y, x);
            if(label_map.count(l) == 0){
                label_map[l] = current_label;
                current_label++;
            }
            res.at<int>(y, x) = label_map[l];
        }
    }

    return res;
}