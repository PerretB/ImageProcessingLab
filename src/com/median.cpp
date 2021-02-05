
#include "../common.h"
#include "../tpMorphology.h"
#include "CLI11.hpp"

using namespace cv;
using namespace std;

int main( int argc, char** argv )
{
    CLI::App app{"Median Filter"};

    string inputImage = "camera_bruit_poivre_et_sel.png";
    app.add_option("-I,--inputImage", inputImage, "Input image filename");

    string outputImage = "out.png";
    app.add_option("-O,--outputImage", outputImage, "Output image filename");

    bool showImages = false;
    app.add_flag("-S,--show", showImages, "Display input and output images in new windows");

    int filterSize = 5;
    app.add_option("-M,--filterSize", filterSize, "Filter size ((X*2+1)*(X*2+1) square)")->required();

    CLI11_PARSE(app, argc, argv);

    Mat image = imreadHelper(inputImage);
    Mat res_image = median(image, filterSize);
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

