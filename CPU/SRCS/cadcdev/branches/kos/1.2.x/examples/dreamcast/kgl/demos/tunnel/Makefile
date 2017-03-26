# KallistiOS ##version##
# 
# tunnel Makefile
#
# $Id: Makefile,v 1.4 2002/09/05 07:40:48 bardtx Exp $
#   

TARGET = tunnel.elf
OBJS = tunnel.o plprint.o menu.o tunneldat.o

all: rm-elf $(TARGET)

include $(KOS_BASE)/Makefile.rules

clean:
	-rm -f $(TARGET) $(BIN) $(OBJS) romdisk.*

rm-elf:
	-rm -f $(TARGET) $(BIN) romdisk.*

$(TARGET): $(OBJS) romdisk.o
	$(KOS_CC) $(KOS_CFLAGS) $(KOS_LDFLAGS) -o $(TARGET) $(KOS_START) \
	$(OBJS) romdisk.o $(OBJEXTRA) -L$(KOS_BASE)/lib -ldcplib -lk++ -lgl -lpcx -lkosutils -lm $(KOS_LIBS)


romdisk.img:
	$(KOS_GENROMFS) -f romdisk.img -d romdisk -v

romdisk.o: romdisk.img
	$(KOS_BASE)/utils/bin2o/bin2o romdisk.img romdisk romdisk.o

run: $(TARGET)
	$(KOS_LOADER) $(TARGET)

dist: 
	rm -f $(OBJS) romdisk.*
	$(KOS_STRIP) $(TARGET)


