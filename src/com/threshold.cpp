
#include "../common.h"
#include "../tpHistogram.h"
#include "CLI11.hpp"

using namespace cv;
using namespace std;

int main( int argc, char** argv )
{
    CLI::App app{"Threshold"};

    string inputImage = "blobs.png";
    app.add_option("-I,--inputImage", inputImage, "Input image filename");

    string outputImage = "out.png";
    app.add_option("-O,--outputImage", outputImage, "Output image filename");

    bool showImages = false;
    app.add_flag("-S,--show", showImages, "Display input and output images in new windows");

    float thresholdLow = 0;
    app.add_option("-L,--thresholdLow", thresholdLow, "Low threshold")->required();

    float thresholdHigh = 0;
    app.add_option("-H,--thresholdHigh", thresholdHigh, "High threshold")->required();

    CLI11_PARSE(app, argc, argv);


    Mat image = imreadHelper(inputImage);
    Mat res_image = threshold(image, thresholdLow, thresholdHigh);
    imwriteHelper(res_image, outputImage);

    // maybe show result
    if (showImages) {
        showimage(image, "Input Image");
        showimage(res_image, "Output Image");
        waitKey(0);
        destroyAllWindows();
    }


    return 0;
}

