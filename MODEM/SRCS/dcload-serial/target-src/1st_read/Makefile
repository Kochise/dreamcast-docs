include ../../Makefile.cfg

LZOPATH = ../../minilzo.106

CC	= $(TARGETCC)
CFLAGS	= $(TARGETCFLAGS)
INCLUDE = -I../dcload -I$(LZOPATH) -I../../target-inc
OBJCOPY	= $(TARGETOBJCOPY)
LD	= $(TARGETLD)

OBJECTS	= crt0.o 1st_read.o disable.o memcpy.o memset.o memmove.o memcmp.o minilzo.o dcload.o exception.o
LZOFILES = $(LZOPATH)/minilzo.c $(LZOPATH)/minilzo.h $(LZOPATH)/lzoconf.h

.c.o:
	$(CC) $(CFLAGS) $(INCLUDE) -o $@ -c $< 

.S.o:
	$(CC) $(CFLAGS) $(INCLUDE) -o $@ -c $< 

.s.o:
	$(CC) $(CFLAGS) $(INCLUDE) -o $@ -c $< 

all: 1st_read.bin 1st_read.srec

1st_read.bin: 1st_read
	$(OBJCOPY) -O binary $< $@	

1st_read.srec: 1st_read
	$(OBJCOPY) -O srec $< $@	

1st_read: $(OBJECTS)
	$(CC) $(CFLAGS) -Wl,-Tdc.x -nostartfiles -nostdlib $^ -o $@ -lgcc

minilzo.o: $(LZOFILES)
	$(CC) $(CFLAGS) $(INCLUDE) -o $@ -c $< 

dcload.lzo: ../dcload/dcload.lzo
	cp $< $@

exception.lzo: ../dcload/exception.lzo
	cp $< $@

dcload.o: dcload.lzo
	$(LD) -A sh -b binary --oformat elf32-shl $< -o $@ -r -EL --no-warn-mismatch

exception.o: exception.lzo
	$(LD) -A sh -b binary --oformat elf32-shl $< -o $@ -r -EL --no-warn-mismatch

.PHONY : clean
clean:
	rm -f $(OBJECTS) 1st_read dcload.lzo exception.lzo

.PHONY : distclean
distclean: clean 
	rm -f 1st_read.bin 1st_read.srec 
