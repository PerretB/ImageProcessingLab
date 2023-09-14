#! /bin/bash

CURDIR=`pwd`

# check if conda is already in the path
if ! command -v "conda" &> /dev/null
then
   
   # check if miniconda has laready been installed locally
   if [[ -x "./miniconda/bin/conda" ]]
   then
      echo "Conda found: ./miniconda/bin/conda"
   else
      echo "Conda cannot be found: installing Miniconda"
      if [[ $CURDIR =~ " " ]]; then
         echo "Error: the current path contains a space character, Miniconda does not support this!"
         echo $CURDIR
         exit
      fi

      unameOut=`uname -s`
      case "${unameOut}" in
         Linux*)     MINICONDA_LINUX="Linux-x86_64";;
         Darwin*)    MACOS=1
				     MINICONDA_LINUX="MacOSX-x86_64";;
         *)          echo "UNKNOWN system"
                     exit 1;;
      esac

      MINICONDA_VERSION="latest"
      
      wget "http://repo.continuum.io/miniconda/Miniconda3-$MINICONDA_VERSION-$MINICONDA_LINUX.sh" -O miniconda.sh;
      bash miniconda.sh -b -p ./miniconda
      rm miniconda.sh
   fi

   CONDA_ROOT_PATH="$CURDIR/miniconda"
   export PATH="$CONDA_ROOT_PATH/bin:$PATH"
   
else
   # "configure" conda
   conda activate
   conda_path=`which python`
   echo "Conda found: $conda_path"
   conda_bin_dir=`dirname $conda_path`
   CONDA_ROOT_PATH=`dirname $conda_bin_dir`   
fi

# is opencv installed on conda
opencv_package=`conda list | grep libopencv`
if [[ -z "$opencv_package" ]]
then
   conda config --set always_yes yes --set changeps1 no
   conda install -c conda-forge opencv
fi

export OPENCV_LIB_DIR=$CONDA_ROOT_PATH/lib

export CPLUS_INCLUDE_PATH=$CONDA_ROOT_PATH/include/opencv4:$CPLUS_INCLUDE_PATH
