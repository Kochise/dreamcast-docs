include ../../Makefile.cfg

LZOPATH = ../../minilzo.106

CC	= $(HOSTCC)
CFLAGS	= $(HOSTCFLAGS)
INCLUDE	= -I$(LZOPATH)
LZOFILES = $(LZOPATH)/minilzo.c $(LZOPATH)/minilzo.h $(LZOPATH)/lzoconf.h

.c.o:
	$(CC) $(CFLAGS) $(INCLUDE) -o $@ -c $< 

all: lzo

lzo: lzo.c minilzo.o
	$(CC) $(CFLAGS) $(INCLUDE) -o $@ $^

minilzo.o: $(LZOFILES)
	$(CC) $(CFLAGS) $(INCLUDE) -o $@ -c $< 

.PHONY : clean
clean:
	rm -f *.o

.PHONY : distclean
distclean: clean
	rm -f lzo