
TIKI_DIR=../../
CFLAGS=-I$(TIKI_DIR)$(TIKI_PLAT)/include -I$(TIKI_DIR)include
OBJS = $(patsubst %.cpp,%.o,$(wildcard src/*.cpp))

all: $(OBJS)
	$(CXX) $(LDFLAGS) -L$(TIKI_DIR)$(TIKI_PLAT) -L$(TIKI_DIR)$(TIKI_PLAT)/lib $(OBJS) $(TIKI_BASE_LIBS) -o tikitest

clean:
	-rm -f $(OBJS) tikitest

DEPSDIR=$(CURDIR)
include $(TIKI_DIR)$(TIKI_PLAT)/Makefile.rules
