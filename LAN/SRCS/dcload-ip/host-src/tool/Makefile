include ../../Makefile.cfg

CC	= $(HOSTCC)
CFLAGS	= $(HOSTCFLAGS) -DDREAMCAST_IP=\"$(DREAMCAST_IP)\" -DHAVE_GETOPT
INCLUDE	= -I$(BFDINCLUDE)

DCTOOL	= dc-tool$(EXECUTABLEEXTENSION)

OBJECTS	= dc-tool.o syscalls.o

.c.o:
	$(CC) $(CFLAGS) $(INCLUDE) -o $@ -c $< 

all: $(DCTOOL)

$(DCTOOL): $(OBJECTS)
	$(CC) -o $@ $(OBJECTS) $(BFDLIB)

.PHONY : install
install: $(DCTOOL)
	cp $(DCTOOL) $(TOOLINSTALLDIR)

.PHONY : clean
clean:
	rm -f $(OBJECTS)

.PHONY : distclean
distclean: clean 
	rm -f $(DCTOOL)
