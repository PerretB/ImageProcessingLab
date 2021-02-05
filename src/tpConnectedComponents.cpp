#include "tpConnectedComponents.h"
#include <cmath>
#include <algorithm>
#include <tuple>
#include <vector>
#include <map>
using namespace cv;
using namespace std;


/**
    Performs a labeling of image connected component with 4 connectivity
    with a depth-first exploration.
    Any non zero pixel of the image is considered as present.
*/
cv::Mat ccLabel(cv::Mat image)
{
    Mat res = Mat::zeros(image.rows, image.cols, CV_32SC1); // 32 int image
    /********************************************
                YOUR CODE HERE
    *********************************************/
   
    /********************************************
                END OF YOUR CODE
    *********************************************/
    return res;
}

/**
    Deletes the connected components (4 connectivity) containg less than size pixels.
*/
cv::Mat ccAreaFilter(cv::Mat image, int size)
{
    Mat res = Mat::zeros(image.rows, image.cols, image.type());
    assert(size>0);
    /********************************************
                YOUR CODE HERE
    *********************************************/
    
    /********************************************
                END OF YOUR CODE
    *********************************************/
    return res;
}


/**
    Performs a labeling of image connected component with 4 connectivity using a
    2 pass algorithm.
    Any non zero pixel of the image is considered as present.
*/
cv::Mat ccTwoPassLabel(cv::Mat image)
{
    Mat res = Mat::zeros(image.rows, image.cols, CV_32SC1); // 32 int image
    /********************************************
                YOUR CODE HERE
    *********************************************/
  
    /********************************************
                END OF YOUR CODE
    *********************************************/
    return res;
}