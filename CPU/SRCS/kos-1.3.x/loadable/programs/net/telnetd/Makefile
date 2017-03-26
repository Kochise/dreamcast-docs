#
# KallistiOS lwIP test program
# (c)2002 Dan Potter
#   

# Put the filename of the output binary here
TARGET = telnetd.elf

# List all of your C files here, but change the extension to ".o"
OBJS = telnetd.o

LWIPDIR := $(KOS_BASE)/loadable/modules/net/net_lwip/lwip/src
ARCHDIR := $(LWIPDIR)/../../kos

KOS_LOCAL_CFLAGS := -DIPv4 \
	-I$(LWIPDIR)/include -I$(ARCHDIR)/include \
	-I$(LWIPDIR)/include/ipv4

include $(KOS_BASE)/loadable/programs/Makefile.prefab

