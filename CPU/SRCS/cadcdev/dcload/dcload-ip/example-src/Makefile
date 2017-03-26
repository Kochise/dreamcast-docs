include ../Makefile.cfg

CC	= $(TARGETCC)
INCLUDE	= -I../target-inc
CFLAGS	= $(TARGETCFLAGS)
OBJCOPY	= $(TARGETOBJCOPY)

OBJECTS	= crt0.o dcload-syscall.o dcload-syscalls.o memcpy.o

.c.o:
	$(CC) $(CFLAGS) $(INCLUDE) -o $@ -c $< 

.S.o:
	$(CC) $(CFLAGS) $(INCLUDE) -o $@ -c $< 

.s.o:
	$(CC) $(CFLAGS) $(INCLUDE) -o $@ -c $< 

all: console-test.bin exception-test.bin gethostinfo.bin

console-test.bin: console-test
	$(OBJCOPY) -O binary $< $@	

exception-test.bin: exception-test
	$(OBJCOPY) -O binary $< $@	

gethostinfo.bin: gethostinfo
	$(OBJCOPY) -O binary $< $@	

console-test: $(OBJECTS) console-test.o
	$(CC) $(CFLAGS) -Wl,-Tdc.x -nostartfiles -nostdlib $^ -o $@ -lgcc

gethostinfo: $(OBJECTS) gethostinfo.o
	$(CC) $(CFLAGS) -Wl,-Tdc.x -nostartfiles -nostdlib $^ -o $@ -lgcc

exception-test: $(OBJECTS) exception-test.o
	$(CC) $(CFLAGS) -Wl,-Tdc.x -nostartfiles -nostdlib $^ -o $@ -lgcc

.PHONY : clean
clean:
	rm -f *.o console-test exception-test gethostinfo

.PHONY : distclean
distclean: clean 
	rm -f *.bin
