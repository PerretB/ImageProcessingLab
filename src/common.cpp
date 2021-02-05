#include "common.h"
#include <exception>
#include <iostream>
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
         sprintf(op, "%d", count++);
         tn = op;
    }else
    {
        tn = name;
    }

    cv::namedWindow( tn, cv::WINDOW_AUTOSIZE );
    cv::imshow( tn, image );
}

