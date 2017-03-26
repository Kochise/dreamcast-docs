include ../../Makefile.cfg

CC	= $(HOSTCC)
CFLAGS	= $(HOSTCFLAGS) -DDREAMCAST_IP=\"$(DREAMCAST_IP)\" -DHAVE_GETOPT
INCLUDE	= -I$(BFDINCLUDE)

OBJECTS	= dc-tool.o syscalls.o

.c.o:
	$(CC) $(CFLAGS) $(INCLUDE) -o $@ -c $< 

all: dc-tool

dc-tool: $(OBJECTS)
	$(CC) -o $@ $(OBJECTS) $(BFDLIB)

.PHONY : install
install: dc-tool
	cp dc-tool$(EXECUTABLEEXTENSION) $(TOOLINSTALLDIR)

.PHONY : clean
clean:
	rm -f $(OBJECTS)

.PHONY : distclean
distclean: clean 
	rm -f dc-tool