include ../../Makefile.cfg

CC	= $(TARGETCC)
CFLAGS	= $(TARGETCFLAGS) -DDREAMCAST_IP=\"$(DREAMCAST_IP)\"
INCLUDE	= -I../../target-inc

OBJCOPY	= $(TARGETOBJCOPY)

DCLOBJECTS	= dcload-crt0.o syscalls.o memcpy.o memset.o memcmp.o disable.o go.o video.o dcload.o cdfs_redir.o cdfs_syscalls.o bswap.o packet.o rtl8139.o net.o commands.o adapter.o lan_adapter.o
EXCOBJECTS	= exception.o

%.o : %.c
	$(CC) $(CFLAGS) $(INCLUDE) -o $@ -c $< 
%.o : %.s
	$(CC) $(CFLAGS) $(INCLUDE) -o $@ -c $< 
%.o : %.S
	$(CC) $(CFLAGS) $(INCLUDE) -o $@ -c $< 
%.bin: %
	$(OBJCOPY) -R .stack -O binary $< $@    

all: dcload.bin exception.bin

dcload: $(DCLOBJECTS)
	$(CC) $(CFLAGS) -Wl,-Tdcload.x -nostartfiles -nostdlib $^ -o $@ -lgcc

exception: $(EXCOBJECTS)
	$(CC) $(CFLAGS) -Wl,-Ttext=0x8c00f400 -nostartfiles -nostdlib $^ -o $@

.PHONY : clean
clean:
	rm -f $(DCLOBJECTS) $(EXCOBJECTS) dcload exception

.PHONY : distclean
distclean: clean 
	rm -f dcload.bin exception.bin
