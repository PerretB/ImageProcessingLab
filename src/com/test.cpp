
#include <map>
#include <iostream>
#include "../common.h"
#include <vector>
#include <stdlib.h>
#include <sys/stat.h>
#include <fstream>
#include <exception>
#include "CLI11.hpp"

using namespace cv;
using namespace std;


/* FOREGROUND */
#define RST  "\x1B[0m"
#define KRED  "\x1B[31m"
#define KGRN  "\x1B[32m"
#define KYEL  "\x1B[33m"
#define KBLU  "\x1B[34m"
#define KMAG  "\x1B[35m"
#define KCYN  "\x1B[36m"
#define KWHT  "\x1B[37m"

#define BOLD "\x1B[1m"
#define UNDL "\x1B[4m"




string outname = string("out.png");

#define SENSITIVITY 1e-4


bool compIm(Mat im1, Mat im2, string msg, bool show)
{
    if(im1.cols != im2.cols || im1.rows != im2.rows)
    {
        cerr << "\tDimensions incorrect, command:" << msg << endl;
        return false;
    }

    if(im1.channels() != im2.channels())
    {
        cerr << "\tChannel number incorrect, command:" << msg << endl;
        return false;
    }

    im1.convertTo(im1, CV_64F);
    im2.convertTo(im2, CV_64F);
    im1 = im1 / 255.0;
    im2 = im2 / 255.0;
    Mat tmp0 = im1 - im2;
    Mat tmp;
    pow(tmp0,2.0,tmp);
    double err = sum(tmp)[0];

    bool flag=false;
    
    if(err > SENSITIVITY)
    {
        cerr <<  "\tRelative error " << err << ": problem detected, command: " << msg << endl;
        flag=true;
    }

    if(show && flag)
    {
        Mat op;
        normalize(tmp,op,0,255,NORM_MINMAX);
        showimage(op, msg.c_str());
        waitKey(0);
        destroyAllWindows();
    }
    return !flag;
}

Mat testImInjection(Mat im1, Mat im2){
    std::array<short, 256> map;
    for(std::size_t i = 0; i < 256; ++i)
        map[i] = -1;

    int height = im1.rows;
    int width = im1.cols; 

    Mat diff = Mat::zeros(height, width, CV_8UC1);

    for(int i = 0; i < height; i++)
        for(int j = 0; j < width; j++)
        {
            uchar v = im1.at<uchar>(i, j);
            if(map[v] == -1){
                map[v] = im2.at<uchar>(i, j);
                diff.at<uchar>(i, j) = 0;
            }else{
                if(map[v] != im2.at<uchar>(i, j)){
                    diff.at<uchar>(i, j) = 255;
                }
            
            }
        }
    return diff;
}

bool compImBijection(Mat im1, Mat im2, string msg, bool show)
{
    if(im1.cols != im2.cols || im1.rows != im2.rows)
    {
        cerr << "\tDimensions incorrect, command:" << msg << endl;
        return false;
    }

    if(im1.channels() != im2.channels())
    {
        cerr << "\tChannel number incorrect, command:" << msg << endl;
        return false;
    }

    if(im1.channels() != 1)
    {
        cerr << "\tBijection test only works for scalar images, command:" << msg << endl;
        return false;
    }

    auto d1 = testImInjection(im1, im2);
    auto d2 = testImInjection(im2, im1);

    auto v1 = cv::sum( cv::abs( d1 ) )[0];
    auto v2 = cv::sum( cv::abs( d2 ) )[0];

    if(v1 != 0 || v2 != 0)
    {
        cerr <<  "\tError, labels do not match, command: " << msg << endl;
        if(show)
        {
            showimage(cv::max(d1,d2), msg.c_str());
            waitKey(0);
            destroyAllWindows();
        }
        return false;
    } 
    return true;
}

bool exists_test (const std::string& name) {
  struct stat buffer;
  return (stat (name.c_str(), &buffer) == 0);
}

void copyFile(string source, string destination)
{
    ifstream  src(source, std::ifstream::in | std::ifstream::binary);
    std::ofstream  dst(destination, std::ifstream::out | std::ifstream::binary);

    dst << src.rdbuf();
}

void printFail()
{
    cout << KRED << "\tFailed" << RST << endl;

}

struct unittest{
    using fun_t = std::function<bool(Mat, Mat, string, bool)>;
    string commande;
    fun_t comparisonFunction;

    unittest(string _commande, fun_t _comparisonFunction = compIm): commande(_commande), comparisonFunction(_comparisonFunction){

    }
};

void process(string name, vector<unittest> tests, bool record, bool show, bool memorycheck)
{
    if(exists_test(name))
    {
        int c=0;
        cout << KCYN << BOLD << name << RST << RST  << endl;
        for(auto t : tests)
        {
            auto com = t.commande;
            auto testFun = t.comparisonFunction;
            c++;
            string refOutput = string("expected_results/") + string(name) + to_string(c) + string(".png");

            if(!record && !exists_test(refOutput))
            {
                cout << "\tCannot find reference result, command: " << com << endl;
                cout << "\tExpected file is: " << refOutput << endl;
                printFail();
                break;
            }

            if(memorycheck)
            {
                string comValgrind = string("valgrind --error-exitcode=1 -q --log-file='/dev/null' ") + com;
                int rValgrind  = system (comValgrind.c_str());
                if(rValgrind != 0)
                {
                    cout << "\tValgrind has detected a memory corruption ! command: " << com << endl;
                    printFail();
                    break;
                }
            }
      
            int r = system (com.c_str());
            if(r!=0)
            {
                cout << "\tReturn code different from 0, command: " << com << endl;
                printFail();
                break;
            }

            if(!exists_test(outname))
            {
                cout << "\tOutput file does not exist, command: " << com << endl;
                printFail();
                break;
            }

            if(record)
            {
                copyFile(outname, refOutput);
                cout << KGRN << "\tok" << RST << endl;
            } else
            {
                bool r = false;
                try
                {
                    Mat refIm = imreadHelper(refOutput,false,false);
                    Mat testIm = imreadHelper(outname,false,false);
                    r = testFun(refIm, testIm, com, show);
                }
                catch (exception& e)
                {
                    cout << "\tException " << e.what() << endl;
                }
                if(r)
                    cout << "\tCommand: "<< com << endl << KGRN << "\tok" << RST << endl;
                else 
                    printFail();
            }


        }
    }


}




int main( int argc, char** argv )
{
    map<string,vector<unittest>> p;
    p["inverse"] = {unittest("./inverse -I cat.jpg -O out.png")};
    p["normalize"] = {unittest("./normalize -I blobs-bad.png -O out.png")};
    p["ccAreaFilter"] = {unittest("./ccAreaFilter -I binary.png -F 200 -O out.png")};
    p["ccLabel"] = {unittest("./ccLabel -I binary.png -O out.png", compImBijection)};
    p["ccLabel2pass"] = {unittest("./ccLabel2pass -I binary.png -O out.png", compImBijection)};
    p["equalize"] = {unittest("./equalize -I camera_mauvaise_balance.png -O out.png")};
    p["expand"] = {unittest("./expand -I cat.jpg -F 3 -P nearest -O out.png"), 
                    unittest("./expand -I cat.jpg -F 3 -P bilinear -O out.png")};
    p["quantize"] = {unittest("./quantize -I cat.jpg -Q 3 -O out.png")};
    p["rotate"] = {unittest("./rotate -I cat.jpg -A 30 -P nearest -O out.png"), 
                    unittest("./rotate -I cat.jpg -A 30 -P bilinear -O out.png")};
    p["threshold"] = {unittest("./threshold -I cat.jpg -L 0.2 -H 0.8 -O out.png")};
    p["transpose"] = {unittest("./transpose -I cat.jpg -O out.png")};

    p["convolution"] = {unittest("./convolution -I cat.jpg -O out.png -K maskGauss5x5.png")};
    p["meanFilter"] = {unittest("./meanFilter -I cat.jpg -M 5 -O out.png")};
    p["edgeSobel"] = {unittest("./edgeSobel -I cat.jpg -O out.png")};
    p["bilateralFilter"] = {unittest("./bilateralFilter -I cat.jpg -C 0.1 -K maskGauss5x5.png -O out.png")};

    p["median"] = {unittest("./median -I camera_bruit_poivre_et_sel.png -M 2 -O out.png")};
    p["erode"] = {unittest("./erode -I binary.png -E morphoLineV.png -O out.png"),
                    unittest("./erode -I cat.jpg -E morphoCross.png -O out.png")};
    p["dilate"] = {unittest("./dilate -I binary.png -E morphoLineV.png -O out.png"),
                    unittest("./dilate -I cat.jpg -E morphoLineV.png -O out.png")};
    p["open"] = {unittest("./open -I binary.png -E morphoLineV.png -O out.png"),
                unittest("./open -I cat.jpg -E morphoLineV.png -O out.png")};
    p["close"] = {unittest("./close -I binary.png -E morphoCircle.png -O out.png"),
                unittest("./close -I cat.jpg -E morphoCircle.png -O out.png")};
    p["morphologicalGradient"]  = {unittest("./morphologicalGradient -I binary.png -E morphoCross.png -O out.png"),
                                unittest("./morphologicalGradient -I cat.jpg -E morphoCross.png -O out.png")};

    p["thresholdOtsu"] = {unittest("./thresholdOtsu -I cat.jpg -O out.png")};

    /*p["detectRectangle"] = {"./detectRectangle -I cas1.png -O out.png",
                            "./detectRectangle -I cas2.png -O out.png",
                            "./detectRectangle -I cas3.png -O out.png",
                            "./detectRectangle -I cas4.png -O out.png",
                            "./detectRectangle -I cas5.png -O out.png",
                            "./detectRectangle -I cas6.png -O out.png"};
    
    p["thresholdKMean"] = {"./thresholdKMean -I cat.jpg -O out.png"};
    
    p["thresholdSigmaClipping"] = {"./thresholdSigmaClipping -I img1-11.tiff -O out.png"};*/

    CLI::App app{"Test program"};

    string program = "";
    app.add_option("-P,--program", program, "Command to test");

    bool record = false;
    app.add_flag("--recordmode", record, "Record new test results");

    bool fastmode = false;
    app.add_flag("--fast", fastmode, "Disable memory corruption detection");

    bool show = false;
    app.add_flag("-S,--show", show, "Display input and output images in new windows");

    CLI11_PARSE(app, argc, argv);



    if(program.size() != 0)
    {
        string & prog = program;
        if (p.count(prog))
        {
            if(!exists_test(prog))
            {
                cerr << "Cannot find program " << prog << endl;
                exit(1);
            }
            process(prog, p[prog],record, show, !fastmode);
        }else{
            cerr << "Unknown program " << prog << endl;
            exit(1);
        }
    }else{
        for(auto iter = p.begin(); iter != p.end(); ++iter)
        {
            string k = iter->first;
            process(k, iter->second, record, show, !fastmode);
        }

    }




    return 0;
}

