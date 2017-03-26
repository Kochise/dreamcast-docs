# Put the filename of the output binary here
TARGET = dns-client.elf

# List all of your C files here, but change the extension to ".o"
OBJS = dnslookup.o

LWIPDIR = $(KOS_BASE)/../kos-ports/lwip/lwip/src
ARCHDIR = $(LWIPDIR)/../../kos

all: rm-elf $(TARGET)

include $(KOS_BASE)/Makefile.rules

KOS_CFLAGS += -DIPv4 \
	-I$(LWIPDIR)/include -I$(ARCHDIR)/include \
	-I$(LWIPDIR)/include/ipv4

clean:
	rm -f $(TARGET) $(OBJS)

rm-elf:
	rm -f $(TARGET)

$(TARGET): $(OBJS)
	$(KOS_CC) $(KOS_CFLAGS) $(KOS_LDFLAGS) -o $(TARGET) $(KOS_START) \
		$(OBJS) $(OBJEXTRA) -llwip4 -lkosutils $(KOS_LIBS)

run: $(TARGET)
	dc-tool -n -x $(TARGET)
