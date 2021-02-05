
#include "../common.h"
#include "../tpGeometry.h"
#include "CLI11.hpp"

using namespace cv;
using namespace std;

int main( int argc, char** argv )
{
    CLI::App app{"Rotate"};

    string inputImage = "cat.jpg";
    app.add_option("-I,--inputImage", inputImage, "Input image filename");

    string outputImage = "out.png";
    app.add_option("-O,--outputImage", outputImage, "Output image filename");

    bool showImages = false;
    app.add_flag("-S,--show", showImages, "Display input and output images in new windows");

    float rotationAngle = 0;
    app.add_option("-A,--rotationAngle", rotationAngle, "Rotation angle (degree)")->required();

    string interpolation = "bilinear";
    app.add_option("-P,--interpolation", interpolation, "Interpolation method ('nearest' or 'bilinear')");

    CLI11_PARSE(app, argc, argv);

    float (* interpolationMethod)(Mat, float, float);
    if(interpolation.compare("bilinear")==0)
        interpolationMethod = interpolate_bilinear;
    else if(interpolation.compare("nearest")==0)
        interpolationMethod = interpolate_nearest;
    else
    {
        std::cerr << "Interpolation method unknown:" << interpolation << std::endl;
        exit(1);
    }

    Mat image = imreadHelper(inputImage);
    Mat res_image = rotate(image, rotationAngle, interpolationMethod);
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

