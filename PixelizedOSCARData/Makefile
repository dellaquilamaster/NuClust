CFLAGS    :=`root-config --cflags --libs` -lMathMore

DllSuf    := so
SrcSuf    := cpp
ObjSuf    := o
PcmSuf    := _rdict.pcm

INCLUDES  := -I$(NuClustSrc)
INCLUDES  += -I$(NuClustSrc)/PixelizedOSCARData/

CXXFLAGS  += $(INCLUDES) -std=c++11 -fPIC -O3 -Wall -Wpedantic

PIXELIZEDOSCARDATA_LIB := libPixelizedOSCARData.$(DllSuf)
SRCS = $(wildcard *.$(SrcSuf))
OBJS = $(patsubst %.$(SrcSuf), %.$(ObjSuf), $(SRCS))

PIXELIZEDOSCARDATA_DICT  := PixelizedOSCARDataDict.$(SrcSuf)
PIXELIZEDOSCARDATA_DICTH := $(PIXELIZEDOSCARDATA_DICT:.$(SrcSuf)=.h)
PIXELIZEDOSCARDATA_DICTO := $(PIXELIZEDOSCARDATA_DICT:.$(SrcSuf)=.$(ObjSuf))
PIXELIZEDOSCARDATA_PCM   := PixelizedOSCARDataDict$(PcmSuf)

PIXELIZEDOSCARDATA_HDRS  := $(wildcard Pixelized*.$(SrcSuf))
PIXELIZEDOSCARDATA_HDRS  := $(PIXELIZEDOSCARDATA_HDRS:.$(SrcSuf)=.h) PixelizedOSCARDataLinkDef.h
PIXELIZEDOSCARDATA_HDRS  := $(filter-out $(PIXELIZEDOSCARDATA_DICTH),$(PIXELIZEDOSCARDATA_HDRS))

.$(SrcSuf).$(ObjSuf):
	@$(CXX) $(CXXFLAGS) -c $< $(SYSLIB) $(CFLAGS)
	@echo "$(CXX) $(CXXFLAGS) -c $< $(SYSLIB) $(CFLAGS)"

all: $(PIXELIZEDOSCARDATA_LIB)

.SUFFIXES: .$(SrcSuf) .$(ObjSuf) .$(DllSuf) .$(PcmSuf)

$(PIXELIZEDOSCARDATA_DICT): $(PIXELIZEDOSCARDATA_HDRS)
	@echo "Generating dictionary $@..."
	rootcling -f $@ -p $(INCLUDES) $^

$(PIXELIZEDOSCARDATA_LIB): $(OBJS) $(PIXELIZEDOSCARDATA_DICTO)
	@$(CXX) $(CXXFLAGS) -shared -o $@ $^ $(CFLAGS) $(RLIBS)
	@echo "$(CXX) $(CXXFLAGS) -shared -o $@ $^ $(CFLAGS) $(RLIBS)"
		

install:
	@echo "cp $(PIXELIZEDOSCARDATA_LIB) $(PIXELIZEDOSCARDATA_PCM) $(NuClustSrc)lib/."
	@cp $(PIXELIZEDOSCARDATA_LIB) $(PIXELIZEDOSCARDATA_PCM) $(NuClustSrc)lib/.
	@echo "cp *.h $(NuClustSrc)include/."
	@cp *.h $(NuClustSrc)include/.		

.PHONY: distclean
distclean:
	@rm -f $(PIXELIZEDOSCARDATA_LIB) $(PIXELIZEDOSCARDATA_PCM) $(PIXELIZEDOSCARDATA_DICT) $(OBJS)
	@rm -f $(NuClustSrc)lib/$(PIXELIZEDOSCARDATA_LIB) $(NuClustSrc)lib/$(PIXELIZEDOSCARDATA_PCM)

.PHONY: clean
clean:
	@$(RM) -f $(PIXELIZEDOSCARDATA_LIB) $(PIXELIZEDOSCARDATA_PCM) $(PIXELIZEDOSCARDATA_DICT) $(OBJS)
	@$(RM) -f *.expand

.PHONY: lint
lint:
	$(LINT) $(INC_SRCH_PATH) $(SRCS)
