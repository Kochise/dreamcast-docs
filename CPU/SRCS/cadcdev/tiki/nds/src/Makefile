
OBJS = $(patsubst %.cpp,%.o,$(wildcard *.cpp))
OBJS += $(patsubst %.cpp,%.o,$(wildcard audio/*.cpp))

all: $(OBJS)
	$(AR) ru ../libtiki.a $(OBJS)

clean:
	-rm -f $(OBJS)
	
DEPSDIR=$(CURDIR)
TIKI_DIR=$(CURDIR)/../../
include ../Makefile.rules
