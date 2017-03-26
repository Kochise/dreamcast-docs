
CFLAGS=-I../../../$(TIKI_PLAT)/include -I../../../include
OBJS = $(patsubst %.cpp,%.o,$(wildcard src/*.cpp))

all: $(OBJS)
	$(CXX) -L../../../$(TIKI_PLAT) -L../../../$(TIKI_PLAT)/lib $(OBJS) $(TIKI_BASE_LIBS) -o tikisnake

clean:
	-rm -f $(OBJS) tikisnake

include ../../../$(TIKI_PLAT)/Makefile.rules
