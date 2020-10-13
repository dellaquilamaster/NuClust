CFLAGS    :=`root-config --cflags --libs` -lMathMore

DllSuf    := so
SrcSuf    := cpp
ObjSuf    := o
PcmSuf    := _rdict.pcm

INCLUDES  := -I$(NuClustSrc)

CXXFLAGS  += $(INCLUDES) -std=c++11 -fPIC -O3 -Wall -Wpedantic

SRIMENERGYLOSSMODULE_LIB := libSRIMEnergyLossModule.$(DllSuf)
SRCS = $(wildcard *.$(SrcSuf))
OBJS = $(patsubst %.$(SrcSuf), %.$(ObjSuf), $(SRCS))

.$(SrcSuf).$(ObjSuf):
	@$(CXX) $(CXXFLAGS) -c $< $(SYSLIB) $(CFLAGS)
	@echo "$(CXX) $(CXXFLAGS) -c $< $(SYSLIB) $(CFLAGS)"

all: $(SRIMENERGYLOSSMODULE_LIB)

.SUFFIXES: .$(SrcSuf) .$(ObjSuf) .$(DllSuf)

$(SRIMENERGYLOSSMODULE_LIB): $(OBJS)
	@$(CXX) $(CXXFLAGS) -shared -o $@ $^ $(CFLAGS) $(RLIBS)
	@echo "$(CXX) $(CXXFLAGS) -shared -o $@ $^ $(CFLAGS) $(RLIBS)"

install:
	@echo "cp $(SRIMENERGYLOSSMODULE_LIB) $(NuClustSrc)lib/."
	@cp $(SRIMENERGYLOSSMODULE_LIB) $(NuClustSrc)lib/.
	@echo "cp *.h $(NuClustSrc)include/."
	@cp *.h $(NuClustSrc)include/.		

.PHONY: distclean
distclean:
	@rm -f $(SRIMENERGYLOSSMODULE_LIB) $(OBJS)
	@rm -f $(NuClustSrc)lib/$(SRIMENERGYLOSSMODULE_LIB)

.PHONY: clean
clean:
	@$(RM) -f $(SRIMENERGYLOSSMODULE_LIB) $(OBJS)
	@$(RM) -f *.expand

.PHONY: lint
lint:
	$(LINT) $(INC_SRCH_PATH) $(SRCS)
