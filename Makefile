OPENCVLIBS = -lopencv_core -lopencv_imgproc -lopencv_highgui -lopencv_imgcodecs
ifneq (${OPENCV_LIB_DIR}, "")
LIBS = -L${OPENCV_LIB_DIR} ${OPENCVLIBS}
else
LIBS = ${OPENCVLIBS}
endif

CFLAGS =  -fPIE -Wall -ggdb -Werror -Wextra -pedantic -std=c++11 -Wno-unused-parameter -I./lib/

com_targets := $(addprefix bin/, $(basename $(notdir $(wildcard src/com/*.cpp))))
com_obj := $(addprefix obj/com/,$(notdir $(addsuffix .o, $(com_targets))))

CPP_FILES_COMMON := $(wildcard src/*.cpp)
OBJ_FILES_COMMON := $(addprefix obj/,$(addsuffix .o, $(basename $(notdir $(CPP_FILES_COMMON)))))


all: TP1 TP2 TP3 TP4 TP5 bin/test


bin/test: obj/com/test.o obj/common.o
	g++ $(CFLAGS) -o $@ $^ $(LIBS)



TP1: bin/inverse bin/threshold bin/quantize bin/normalize bin/equalize bin/thresholdOtsu

bin/inverse: obj/com/inverse.o obj/common.o obj/tpHistogram.o 
	g++ $(CFLAGS) -o $@ $^ $(LIBS)

bin/threshold: obj/com/threshold.o obj/common.o obj/tpHistogram.o 
	g++ $(CFLAGS) -o $@ $^ $(LIBS)

bin/quantize: obj/com/quantize.o obj/common.o obj/tpHistogram.o 
	g++ $(CFLAGS) -o $@ $^ $(LIBS)

bin/normalize: obj/com/normalize.o obj/common.o obj/tpHistogram.o 
	g++ $(CFLAGS) -o $@ $^ $(LIBS)

bin/equalize: obj/com/equalize.o obj/common.o obj/tpHistogram.o 
	g++ $(CFLAGS) -o $@ $^ $(LIBS)

bin/thresholdOtsu: obj/com/thresholdOtsu.o obj/common.o obj/tpHistogram.o 
	g++ $(CFLAGS) -o $@ $^ $(LIBS)



TP2: bin/ccLabel bin/ccAreaFilter bin/ccLabel2pass

bin/ccLabel: obj/com/ccLabel.o obj/common.o obj/tpConnectedComponents.o 
	g++ $(CFLAGS) -o $@ $^ $(LIBS)

bin/ccAreaFilter: obj/com/ccAreaFilter.o obj/common.o obj/tpConnectedComponents.o 
	g++ $(CFLAGS) -o $@ $^ $(LIBS)

bin/ccLabel2pass: obj/com/ccLabel2pass.o obj/common.o obj/tpConnectedComponents.o 
	g++ $(CFLAGS) -o $@ $^ $(LIBS)	



TP3: bin/transpose bin/expand bin/rotate

bin/transpose: obj/com/transpose.o obj/common.o obj/tpGeometry.o 
	g++ $(CFLAGS) -o $@ $^ $(LIBS)

bin/expand: obj/com/expand.o obj/common.o obj/tpGeometry.o 
	g++ $(CFLAGS) -o $@ $^ $(LIBS)

bin/rotate: obj/com/rotate.o obj/common.o obj/tpGeometry.o  
	g++ $(CFLAGS) -o $@ $^ $(LIBS)	



TP4: bin/meanFilter bin/convolution bin/edgeSobel bin/bilateralFilter

bin/meanFilter: obj/com/meanFilter.o obj/common.o obj/tpConvolution.o 
	g++ $(CFLAGS) -o $@ $^ $(LIBS)

bin/convolution: obj/com/convolution.o obj/common.o obj/tpConvolution.o 
	g++ $(CFLAGS) -o $@ $^ $(LIBS)

bin/edgeSobel: obj/com/edgeSobel.o obj/common.o obj/tpConvolution.o 
	g++ $(CFLAGS) -o $@ $^ $(LIBS)

bin/bilateralFilter: obj/com/bilateralFilter.o obj/common.o obj/tpConvolution.o 
	g++ $(CFLAGS) -o $@ $^ $(LIBS)



TP5: bin/median bin/erode bin/dilate bin/open bin/close bin/morphologicalGradient

bin/median: obj/com/median.o obj/common.o obj/tpMorphology.o 
	g++ $(CFLAGS) -o $@ $^ $(LIBS)

bin/erode: obj/com/erode.o obj/common.o obj/tpMorphology.o 
	g++ $(CFLAGS) -o $@ $^ $(LIBS)

bin/dilate: obj/com/dilate.o obj/common.o obj/tpMorphology.o 
	g++ $(CFLAGS) -o $@ $^ $(LIBS)

bin/open: obj/com/open.o obj/common.o obj/tpMorphology.o 
	g++ $(CFLAGS) -o $@ $^ $(LIBS)

bin/close: obj/com/close.o obj/common.o obj/tpMorphology.o 
	g++ $(CFLAGS) -o $@ $^ $(LIBS)

bin/morphologicalGradient: obj/com/morphologicalGradient.o obj/common.o obj/tpMorphology.o 
	g++ $(CFLAGS) -o $@ $^ $(LIBS)



obj/com/%.o : src/com/%.cpp
	g++ $(CFLAGS) -o $@ -c $<

obj/%.o : src/%.cpp src/%.h
	g++ $(CFLAGS) -o $@ -c $<



.PHONY: clean

clean:
	rm -f $(com_targets) 
	rm -f obj/*.o
	rm -f obj/com/*.o


