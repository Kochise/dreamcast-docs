#	Buggy Demo v1.0
#   makefile( using Kos-1.1.8 & Kglx )
#
#   by La Cible (la.cible@free.fr)
#

APPLICATION = buggy
TARGET = buggy.elf
OBJS = Buggy.o

KOS_CFLAGS += -Iinclude -Llib -L../../lib/


all: rm-elf $(TARGET)

include $(KOS_BASE)/Makefile.rules

clean:
	-rm -f $(TARGET) $(OBJS) romdisk.*

rm-elf:
	-rm -f $(TARGET) romdisk.*

$(TARGET): $(OBJS) romdisk.o
	$(KOS_CC) $(KOS_CFLAGS) $(KOS_LDFLAGS) -o $(TARGET) $(KOS_START) \
		$(OBJS) romdisk.o $(OBJEXTRA) -lode -lkglx -lk++ -lm  -lpcx -ljpeg $(KOS_LIBS)

romdisk.img:
	$(KOS_GENROMFS) -f romdisk.img -d romdisk -v

romdisk.o: romdisk.img
	$(KOS_BASE)/utils/bin2o/bin2o romdisk.img romdisk romdisk.o

run: $(TARGET)
	$(KOS_LOADER) $(TARGET)

dist:
	rm -f $(OBJS) romdisk.o romdisk.img
	$(KOS_STRIP) $(TARGET)

		
				
emu:
	$(KOS_OBJCOPY) -R .stack -O binary $(APPLICATION).elf $(APPLICATION).bin
	mv  $(APPLICATION).bin /home/emu/test.bin
	
bin: 
	$(KOS_OBJCOPY) -R .stack -O binary $(APPLICATION).elf $(APPLICATION).bin
	