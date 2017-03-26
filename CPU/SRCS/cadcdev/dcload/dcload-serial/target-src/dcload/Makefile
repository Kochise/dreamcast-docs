include ../../Makefile.cfg

LZOPATH = ../../minilzo.106
LZO	= ../../host-src/misc/lzo

CC	= $(TARGETCC)
CFLAGS	= $(TARGETCFLAGS) -DSERIALSPEED=$(SERIALSPEED)
INCLUDE	= -I$(LZOPATH) -I../../target-inc

OBJCOPY	= $(TARGETOBJCOPY)

#DCLOBJECTS	= dcload-crt0.o syscalls.o memcpy.o memset.o memmove.o memcmp.o scif.o disable.o go.o video.o minilzo.o dcload.o cdfs_redir.o cdfs_syscalls.o bswap.o
DCLOBJECTS	= dcload-crt0.o syscalls.o memcpy.o memset.o memmove.o memcmp.o scif.o disable.o go.o video.o minilzo.o dcload.o cdfs_redir.o cdfs_syscalls.o
EXCOBJECTS	= exception.o
LZOFILES = $(LZOPATH)/minilzo.c $(LZOPATH)/minilzo.h $(LZOPATH)/lzoconf.h

.c.o:
	$(CC) $(CFLAGS) $(INCLUDE) -o $@ -c $< 
.s.o:
	$(CC) $(CFLAGS) $(INCLUDE) -o $@ -c $< 
.S.o:
	$(CC) $(CFLAGS) $(INCLUDE) -o $@ -c $< 

all: dcload.lzo exception.lzo

dcload.lzo: dcload.bin
	$(LZO) $< $@	

dcload.bin: dcload
	$(OBJCOPY) -R .stack -O binary $< $@

dcload: $(DCLOBJECTS)
	$(CC) $(CFLAGS) -Wl,-Tdcload.x -nostartfiles -nostdlib $^ -o $@ -lgcc

exception.lzo: exception.bin
	$(LZO) $< $@	

exception.bin: exception
	$(OBJCOPY) -O binary $< $@	

exception: $(EXCOBJECTS)
	$(CC) $(CFLAGS) -Wl,-Ttext=0x8c00f400 -nostartfiles -nostdlib $^ -o $@

minilzo.o: $(LZOFILES)
	$(CC) $(CFLAGS) $(INCLUDE) -o $@ -c $< 

.PHONY : clean
clean:
	rm -f $(DCLOBJECTS) $(EXCOBJECTS) dcload exception dcload.bin exception.bin

.PHONY : distclean
distclean: clean 
	rm -f *.lzo
