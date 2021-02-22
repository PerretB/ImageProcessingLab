
#include "../common.h"
#include "../tpConvolution.h"
#include "CLI11.hpp"

using namespace cv;
using namespace std;

int main( int argc, char** argv )
{
    CLI::App app{"Convolution"};

    string inputImage = "camera_bruit_gaussien.png";
    app.add_option("-I,--inputImage", inputImage, "Input image filename");

    string outputImage = "out.png";
    app.add_option("-O,--outputImage", outputImage, "Output image filename");

    bool showImages = false;
    app.add_flag("-S,--show", showImages, "Display input and output images in new windows");

    string kernelImage = "maskGauss5x5.png";
    app.add_option("-K,--kernel", kernelImage, "Structuring element filename");

    float intensityScale = 0.1f;
    app.add_option("-C,--intensityScale", intensityScale, "Intensity scale (Gaussian standard deviation)")->required();

    CLI11_PARSE(app, argc, argv);


    Mat image = imreadHelper(inputImage);
    Mat kernel = imreadHelper(kernelImage);
    kernel = kernel / sum(kernel)[0];

    Mat res_image = bilateralFilter(image, kernel, intensityScale);
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