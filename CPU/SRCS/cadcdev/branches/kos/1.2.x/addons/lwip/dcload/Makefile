OBJS = dcload-lwip.o syscalls.o dcload_lwip_syscall.o commands.o

LWIPDIR := $(KOS_BASE)/addons/lwip/src
LWIPARCH := kos
KOS_CFLAGS := $(KOS_CFLAGS) -DIPv4 -DLWIP_DEBUG \
	-I$(LWIPDIR)/include -I$(LWIPDIR)/arch/$(LWIPARCH)/include \
	-I$(LWIPDIR)/include/ipv4 -I$(LWIPDIR)/..

all: $(OBJS)

include $(KOS_BASE)/Makefile.prefab
