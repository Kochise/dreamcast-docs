include ../../Makefile.cfg

LZOPATH = ../../minilzo.106

CC	= $(HOSTCC)
CFLAGS	= $(HOSTCFLAGS) -DBAUD_RATE=$(SERIALSPEED) -DSERIALDEVICE="\"$(SERIALDEVICE)\"" -DHAVE_GETOPT
INCLUDE	= -I$(LZOPATH) -I$(BFDINCLUDE)

DCTOOL	= dc-tool$(EXECUTABLEEXTENSION)

OBJECTS	= dc-tool.o minilzo.o syscalls.o unlink.o
LZOFILES = $(LZOPATH)/minilzo.c $(LZOPATH)/minilzo.h $(LZOPATH)/lzoconf.h

.c.o:
	$(CC) $(CFLAGS) $(INCLUDE) -o $@ -c $< 

all: $(DCTOOL)

$(DCTOOL): $(OBJECTS)
	$(CC) -o $@ $(OBJECTS) $(BFDLIB)

minilzo.o: $(LZOFILES)
	$(CC) $(CFLAGS) $(INCLUDE) -o $@ -c $< 

.PHONY : install
install: $(DCTOOL)
	cp $(DCTOOL) $(TOOLINSTALLDIR)

.PHONY : clean
clean:
	rm -f $(OBJECTS)

.PHONY : distclean
distclean: clean 
	rm -f $(DCTOOL)
