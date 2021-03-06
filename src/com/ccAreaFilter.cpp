
#include "../common.h"
#include "../tpConnectedComponents.h"
#include "CLI11.hpp"

using namespace cv;
using namespace std;

int main( int argc, char** argv )
{
    CLI::App app{"Area filter"};

    string inputImage = "binary.png";
    app.add_option("-I,--inputImage", inputImage, "Input image filename");

    string outputImage = "out.png";
    app.add_option("-O,--outputImage", outputImage, "Output image filename");

    int areaThreshold = 50;
    app.add_option("-F,--areaThreshold", areaThreshold, "Size limit for area filter")->required();

    bool showImages = false;
    app.add_flag("-S,--show", showImages, "Display input and output images in new windows");

    CLI11_PARSE(app, argc, argv);

    Mat image = imreadHelper(inputImage);
    Mat res_image = ccAreaFilter(image, areaThreshold);
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

