
CFLAGS = -I../include -I../../include
OBJS = $(patsubst %.cpp,%.o,$(wildcard *.cpp))

all: $(OBJS)
	$(AR) ru ../libtiki.a $(OBJS)

clean:
	-rm -f $(OBJS)
	
include ../Makefile.rules
