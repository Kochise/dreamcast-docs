TARGET = ghettoplay.elf
OBJS = romdisk.o ghettoplay.o texture.o bkg.o 3dutils.o songmenu.o

all: clean $(TARGET)

clean:
	-rm -f $(TARGET) $(OBJS)
	-rm -f romdisk.o romdisk.img
	
$(TARGET): $(OBJS)
	$(KOS_CC) $(KOS_CFLAGS) $(KOS_LDFLAGS) -o $(TARGET) $(KOS_START) \
	$(OBJS)  $(DATAOBJS) $(OBJEXTRA) -L$(KOS_BASE)/lib -loggvorbisplay -ldcutils -lkallisti  -lgcc -lm 
	#$(OBJS)  $(DATAOBJS) $(OBJEXTRA) -L$(KOS_BASE)/lib -loggvorbisplay -ldcutils -lkallisti -lgcc 

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
	
include ${KOS_BASE}/Makefile.rules

