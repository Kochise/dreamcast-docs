#
# KallistiOS lwIP test program
# (c)2002 Dan Potter
#   

# Put the filename of the output binary here
TARGET = httpd.elf

# List all of your C files here, but change the extension to ".o"
OBJS = simhost.o httpd.o romdisk.o

LWIPDIR = $(KOS_BASE)/../kos-ports/lwip/lwip/src
ARCHDIR = $(LWIPDIR)/../../kos

KOS_CFLAGS += -DIPv4 \
	-I$(LWIPDIR)/include -I$(ARCHDIR)/include \
	-I$(LWIPDIR)/include/ipv4

all: rm-elf $(TARGET)

include $(KOS_BASE)/Makefile.rules

clean:
	rm -f $(TARGET) $(OBJS) romdisk.img

rm-elf:
	rm -f $(TARGET) romdisk.*

$(TARGET): $(OBJS)
	$(KOS_CC) $(KOS_CFLAGS) $(KOS_LDFLAGS) -o $(TARGET) $(KOS_START) \
		$(OBJS) $(OBJEXTRA) -llwip4 -lkosutils $(KOS_LIBS)

romdisk.img:
	$(KOS_GENROMFS) -f romdisk.img -d romdisk -v

romdisk.o: romdisk.img
	$(KOS_BASE)/utils/bin2o/bin2o romdisk.img romdisk romdisk.o

run: $(TARGET)
	dc-tool -n -x $(TARGET)
