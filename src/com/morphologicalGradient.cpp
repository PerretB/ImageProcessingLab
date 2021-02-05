
#include "../common.h"
#include "../tpMorphology.h"
#include "CLI11.hpp"

using namespace cv;
using namespace std;

int main( int argc, char** argv )
{
    CLI::App app{"Morphological Gradient"};

    string inputImage = "camera.png";
    app.add_option("-I,--inputImage", inputImage, "Input image filename");

    string outputImage = "out.png";
    app.add_option("-O,--outputImage", outputImage, "Output image filename");

    bool showImages = false;
    app.add_flag("-S,--show", showImages, "Display input and output images in new windows");

    string structuringElement = "";
    app.add_option("-E,--structuringElement", structuringElement, "Structuring element filename")->required();

    CLI11_PARSE(app, argc, argv);


    Mat image = imreadHelper(inputImage);
    Mat se = imreadHelper(structuringElement);
    Mat res_image = morphologicalGradient(image,se);
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
