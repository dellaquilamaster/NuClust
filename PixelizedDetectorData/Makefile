CFLAGS    :=`root-config --cflags --libs` -lMathMore

DllSuf    := so
SrcSuf    := cpp
ObjSuf    := o
PcmSuf    := _rdict.pcm

INCLUDES  := -I$(NuClustSrc)
INCLUDES  += -I$(NuClustSrc)/PixelizedDetectorData/

CXXFLAGS  += $(INCLUDES) -std=c++11 -fPIC -O3 -Wall -Wpedantic

PIXELIZEDDETECTORDATA_LIB := libPixelizedDetectorData.$(DllSuf)
SRCS = $(wildcard *.$(SrcSuf))
OBJS = $(patsubst %.$(SrcSuf), %.$(ObjSuf), $(SRCS))

PIXELIZEDDETECTORDATA_DICT  := PixelizedDetectorDataDict.$(SrcSuf)
PIXELIZEDDETECTORDATA_DICTH := $(PIXELIZEDDETECTORDATA_DICT:.$(SrcSuf)=.h)
PIXELIZEDDETECTORDATA_DICTO := $(PIXELIZEDDETECTORDATA_DICT:.$(SrcSuf)=.$(ObjSuf))
PIXELIZEDDETECTORDATA_PCM   := PixelizedDetectorDataDict$(PcmSuf)

PIXELIZEDDETECTORDATA_HDRS  := $(wildcard Pixelized*.$(SrcSuf))
PIXELIZEDDETECTORDATA_HDRS  := $(PIXELIZEDDETECTORDATA_HDRS:.$(SrcSuf)=.h) PixelizedDetectorDataLinkDef.h
PIXELIZEDDETECTORDATA_HDRS  := $(filter-out $(PIXELIZEDDETECTORDATA_DICTH),$(PIXELIZEDDETECTORDATA_HDRS))

.$(SrcSuf).$(ObjSuf):
	@$(CXX) $(CXXFLAGS) -c $< $(SYSLIB) $(CFLAGS)
	@echo "$(CXX) $(CXXFLAGS) -c $< $(SYSLIB) $(CFLAGS)"

all: $(PIXELIZEDDETECTORDATA_LIB)

.SUFFIXES: .$(SrcSuf) .$(ObjSuf) .$(DllSuf) .$(PcmSuf)

$(PIXELIZEDDETECTORDATA_DICT): $(PIXELIZEDDETECTORDATA_HDRS)
	@echo "Generating dictionary $@..."
	rootcling -f $@ -p $(INCLUDES) $^

$(PIXELIZEDDETECTORDATA_LIB): $(OBJS) $(PIXELIZEDDETECTORDATA_DICTO)
	@$(CXX) $(CXXFLAGS) -shared -o $@ $^ $(CFLAGS) $(RLIBS)
	@echo "$(CXX) $(CXXFLAGS) -shared -o $@ $^ $(CFLAGS) $(RLIBS)"
		

install:
	@echo "cp $(PIXELIZEDDETECTORDATA_LIB) $(PIXELIZEDDETECTORDATA_PCM) $(NuClustSrc)lib/."
	@cp $(PIXELIZEDDETECTORDATA_LIB) $(PIXELIZEDDETECTORDATA_PCM) $(NuClustSrc)lib/.
	@echo "cp *.h $(NuClustSrc)include/."
	@cp *.h $(NuClustSrc)include/.		

.PHONY: distclean
distclean:
	@rm -f $(PIXELIZEDDETECTORDATA_LIB) $(PIXELIZEDDETECTORDATA_PCM) $(PIXELIZEDDETECTORDATA_DICT) $(OBJS)
	@rm -f $(NuClustSrc)lib/$(PIXELIZEDDETECTORDATA_LIB) $(NuClustSrc)lib/$(PIXELIZEDDETECTORDATA_PCM)

.PHONY: clean
clean:
	@$(RM) -f $(PIXELIZEDDETECTORDATA_LIB) $(PIXELIZEDDETECTORDATA_PCM) $(PIXELIZEDDETECTORDATA_DICT) $(OBJS)
	@$(RM) -f *.expand

.PHONY: lint
lint:
	$(LINT) $(INC_SRCH_PATH) $(SRCS)
