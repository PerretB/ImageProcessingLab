[![Build Status](https://perretb.visualstudio.com/AzurePipelines/_apis/build/status/PerretB.ImageProcessingLab?branchName=refs%2Fpull%2F1%2Fmerge)](https://perretb.visualstudio.com/AzurePipelines/_build/latest?definitionId=1&branchName=refs%2Fpull%2F1%2Fmerge)

# Image Processing Lab

Lab exercises for the  [course on image processing](https://perso.esiee.fr/~perretb/I5FM/TAI/) (in French).



## Organization

There are 5 files to complete, each one corresponds to a course chapter:

1. ``src/tpHistogram.cpp``: histogram manipulation functions [related course chapter](https://perso.esiee.fr/~perretb/I5FM/TAI/histogramme/index.html)
2. ``src/tpConnectedComponents.cpp`` pixel adjacency and connected components [related course chapter](https://perso.esiee.fr/~perretb/I5FM/TAI/connexity/index.html)
3. ``src/tpGeometry.cpp`` geometric image transforms [related course chapter](https://perso.esiee.fr/~perretb/I5FM/TAI/geometry/index.html)
4. ``src/tpConvolution.cpp`` linear image filters [related course chapter](https://perso.esiee.fr/~perretb/I5FM/TAI/convolution/index.html)
5. ``src/tpMorphology.cpp`` non-linear image filters [related course chapter](https://perso.esiee.fr/~perretb/I5FM/TAI/morpho/index.html)

## How to


### Environment

This lab requires a working *nix environment with a c++ 11 compiler and valgrind.

The library *OpenCV4* is required to compile this project. To install a local version of this library just execute the script ``source ./init.sh``. This script will automatically download the library and set up the environment variable required by the makefile.  

**Important:** If you install **OpenCV** with the script ``source ./init.sh``, you have to run the script in every terminal used to work on this project!

### Compilation

Just run ``make`` in the top directory, this will create several executables in the ``bin`` directory. 

**Tip** When using *make*, use the argument ``-j n`` to launch a parallel compilation on ``n`` cores. For example: ``make -j 4`` while compile up to 4 files in parallel. 

### Executables

Each exercise is associated to its own command line tool. For exemple, the first function to code, ``inverse`` in the file ``src/tpHistogram.cpp``, is associated to the command line tool ``bin/inverse`` generated by *make*.

The usage of the command line tools is obtained with the argument ``--help``, for example, executing the command ``./inverse --help`` inside the ``bin`` directory produces the following output:

    Inverse
    Usage: ./inverse [OPTIONS]

    Options:
    -h,--help                   Print this help message and exit
    -I,--inputImage TEXT        Input image filename
    -O,--outputImage TEXT       Output image filename
    -S,--show                   Display input and output images in new windows

### Unit tests

Each command line tool is associated to a unit test that can be executed with the tool ``bin/test``. For example the tool ``inverse`` can be tested with the command ``./test -P inverse``. If the test detects an error, you can ask to see an error map with the argument ``-S``: this will display an image showing where the errors are located: the brighter a pixel is, the further it is from the expected result. 

**Important:** The unit tests work by comparing the result of your functions to results produced with reference implementations. Implementation details, especially when working with floatting point values can lead to small diprecancies between similar results. While the test program tries to deal with this issue it can still detect false positives, i.e., say that a function is wrong while it is indeed right. In case of doubt call a professor to check your work.

As with any unit test, it is also possible that the unit tests suffer from false negatives, i.e., say that a program is correct while it is not.

Note that the test program runs your functions with valgrind to detect any errors related to memory usage (especially reads and writes out of the bounds of an array). 
