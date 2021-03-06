CFLAGS    :=`root-config --cflags --libs` -lMathMore

DllSuf    := so
SrcSuf    := cpp
ObjSuf    := o
PcmSuf    := _rdict.pcm

INCLUDES  := -I$(NuClustSrc)

CXXFLAGS  += $(INCLUDES) -std=c++11 -fPIC -O3 -Wall -Wpedantic

NUCLEARMASSES_LIB := libnuclear_masses.$(DllSuf)
SRCS = $(wildcard *.$(SrcSuf))
OBJS = $(patsubst %.$(SrcSuf), %.$(ObjSuf), $(SRCS))

.$(SrcSuf).$(ObjSuf):
	@$(CXX) $(CXXFLAGS) -c $< $(SYSLIB) $(CFLAGS)
	@echo "$(CXX) $(CXXFLAGS) -c $< $(SYSLIB) $(CFLAGS)"

all: $(NUCLEARMASSES_LIB)

.SUFFIXES: .$(SrcSuf) .$(ObjSuf) .$(DllSuf)

$(NUCLEARMASSES_LIB): $(OBJS)
	@$(CXX) $(CXXFLAGS) -shared -o $@ $^ $(CFLAGS) $(RLIBS)
	@echo "$(CXX) $(CXXFLAGS) -shared -o $@ $^ $(CFLAGS) $(RLIBS)"

install:
	@echo "cp $(NUCLEARMASSES_LIB) $(NuClustSrc)lib/."
	@cp $(NUCLEARMASSES_LIB) $(NuClustSrc)lib/.
	@echo "cp *.h $(NuClustSrc)include/."
	@cp *.h $(NuClustSrc)include/.		

.PHONY: distclean
distclean:
	@rm -f $(NUCLEARMASSES_LIB) $(OBJS)
	@rm -f $(NuClustSrc)lib/$(NUCLEARMASSES_LIB)

.PHONY: clean
clean:
	@$(RM) -f $(NUCLEARMASSES_LIB) $(OBJS)
	@$(RM) -f *.expand

.PHONY: lint
lint:
	$(LINT) $(INC_SRCH_PATH) $(SRCS)
