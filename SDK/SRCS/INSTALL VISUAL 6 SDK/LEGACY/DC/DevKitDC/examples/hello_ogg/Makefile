# KallistiOS Ogg/Vorbis Decoder Library
#
# Library Makefile
# (c)2001 Thorsten Titze
# Based on KOS Makefiles by Dan Potter

TARGET = vorbistest.elf
OBJS = romdisk.o vorbistest.o

all: clean $(TARGET)

include $(KOS_BASE)/Makefile.rules

clean:
	-rm -f $(TARGET) $(OBJS)
	-rm -f romdisk.o romdisk.img

$(TARGET): $(OBJS) 
	$(KOS_CC) $(KOS_CFLAGS) $(KOS_LDFLAGS) -o $(TARGET) $(KOS_START) \
	$(OBJS)  $(DATAOBJS) $(OBJEXTRA) -L$(KOS_BASE)/lib -loggvorbisplay -ldcutils -lkallisti -lm -lgcc 

romdisk.img:
	$(KOS_GENROMFS) -f romdisk.img -d romdisk -v

romdisk.o: romdisk.img
	$(KOS_BASE)/utils/bin2o/bin2o romdisk.img romdisk romdisk.o

run: 
#	$(KOS_LOADER) $(TARGET)
	dc-tool -p -b 115200 -x $(TARGET)

dist:
	rm -f $(OBJS)
	$(KOS_CC_BASE)/bin/sh-elf-strip $(TARGET)

