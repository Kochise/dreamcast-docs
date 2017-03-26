TARGET = ghettoplay.elf
OBJS = romdisk.o ghettoplay.o texture.o bkg.o 3dutils.o songmenu.o

all: rm-elf $(TARGET)

rm-elf:
	-rm -f $(TARGET)
	-rm -f romdisk.o romdisk.img

clean: rm-elf
	-rm -f $(OBJS)
	
$(TARGET): $(OBJS)
	kos-cc -o $(TARGET) $(OBJS) -loggvorbisplay -lm

romdisk.img:
	$(KOS_GENROMFS) -f romdisk.img -d romdisk -v

romdisk.o: romdisk.img
	$(KOS_BASE)/utils/bin2o/bin2o romdisk.img romdisk romdisk.o

run: 
	$(KOS_LOADER) $(TARGET)

dist:
	rm -f $(OBJS) romdisk.o romdisk.img
	$(KOS_STRIP) $(TARGET)
	
include ${KOS_BASE}/Makefile.rules

