CFLAGS    :=`root-config --cflags --libs` -lMathMore

DllSuf    := so
SrcSuf    := cpp
ObjSuf    := o
PcmSuf    := _rdict.pcm

INCLUDES  := -I$(NuClustSrc)
INCLUDES  += -I$(NuClustSrc)/ParticleIdentificationTools

CXXFLAGS  += $(INCLUDES) -std=c++11 -fPIC -O3 -Wall -Wpedantic

PARTICLEIDENTIFICATIONTOOLS_LIB := libParticleIdentificationTools.$(DllSuf)
SRCS = $(wildcard *.$(SrcSuf))
OBJS = $(patsubst %.$(SrcSuf), %.$(ObjSuf), $(SRCS))

.$(SrcSuf).$(ObjSuf):
	@$(CXX) $(CXXFLAGS) -c $< $(SYSLIB) $(CFLAGS)
	@echo "$(CXX) $(CXXFLAGS) -c $< $(SYSLIB) $(CFLAGS)"

all: $(PARTICLEIDENTIFICATIONTOOLS_LIB)

.SUFFIXES: .$(SrcSuf) .$(ObjSuf) .$(DllSuf)

$(PARTICLEIDENTIFICATIONTOOLS_LIB): $(OBJS)
	@$(CXX) $(CXXFLAGS) -shared -o $@ $^ $(CFLAGS) $(RLIBS)
	@echo "$(CXX) $(CXXFLAGS) -shared -o $@ $^ $(CFLAGS) $(RLIBS)"

install:
	@echo "cp $(PARTICLEIDENTIFICATIONTOOLS_LIB) $(NuClustSrc)lib/."
	@cp $(PARTICLEIDENTIFICATIONTOOLS_LIB) $(NuClustSrc)lib/.
	@echo "cp *.h $(NuClustSrc)include/."
	@cp *.h $(NuClustSrc)include/.		

.PHONY: distclean
distclean:
	@rm -f $(PARTICLEIDENTIFICATIONTOOLS_LIB) $(OBJS)
	@rm -f $(NuClustSrc)lib/$(PARTICLEIDENTIFICATIONTOOLS_LIB)

.PHONY: clean
clean:
	@$(RM) -f $(PARTICLEIDENTIFICATIONTOOLS_LIB) $(OBJS)
	@$(RM) -f *.expand

.PHONY: lint
lint:
	$(LINT) $(INC_SRCH_PATH) $(SRCS)
