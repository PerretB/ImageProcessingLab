// Some helper functions

#pragma once
#include <opencv2/opencv.hpp>
#include <string>
#include <initializer_list>


/**
    Read an image from a file.

    options:
        - forceFloat: ensures that the loaded image is in float format. If original image
            was a byte image, its values are divided by 255.
        - forceGrayScale: ensures that the loaded image contains a single channel
*/
cv::Mat imreadHelper(std::string filename, bool forceFloat=true, bool forceGrayScale=true);

/**
    Write an image to disk.
*/
void imwriteHelper(cv::Mat image, std::string filename);

/**
    Display an image in a window with the given name as title.
*/
void showimage(cv::Mat image, const char * name=NULL);

/**
 * Remaps a label image between 0 and the number of labels - 1
 */
cv::Mat remap_labels(cv::Mat label_image);