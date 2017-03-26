include ../../Makefile.cfg

CC	= $(TARGETCC)
CFLAGS	= $(TARGETCFLAGS)
INCLUDE = -I../../target-inc
OBJCOPY	= $(TARGETOBJCOPY)
LD	= $(TARGETLD)

OBJECTS	= crt0.o 1st_read.o disable.o memcpy.o dcload.o exception.o

.c.o:
	$(CC) $(CFLAGS) $(INCLUDE) -o $@ -c $< 

.S.o:
	$(CC) $(CFLAGS) $(INCLUDE) -o $@ -c $< 

.s.o:
	$(CC) $(CFLAGS) $(INCLUDE) -o $@ -c $< 

all: 1st_read.bin 1st_read.srec

dcload.bin: ../dcload/dcload.bin
	cp $< $@

exception.bin: ../dcload/exception.bin
	cp $< $@

dcload.o: dcload.bin
	$(LD) -A sh -b binary --oformat elf32-shl $< -o $@ -r -EL --no-warn-mismatch

exception.o: exception.bin
	$(LD) -A sh -b binary --oformat elf32-shl $< -o $@ -r -EL --no-warn-mismatch

1st_read.bin: 1st_read
	$(OBJCOPY) -O binary $< $@	

1st_read.srec: 1st_read
	$(OBJCOPY) -O srec $< $@	

1st_read: $(OBJECTS)
	$(CC) $(CFLAGS) -Wl,-Tdc.x -nostartfiles -nostdlib $^ -o $@ -lgcc

.PHONY : clean
clean:
	rm -f $(OBJECTS) 1st_read dcload.bin exception.bin

.PHONY : distclean
distclean: clean 
	rm -f 1st_read.bin 1st_read.srec
