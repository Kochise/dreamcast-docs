# lwIP for KOS 1.2.0
#
# Makefile
# (c)2002 Dan Potter
#   
# $Id: Makefile,v 1.5 2003/02/27 04:25:43 bardtx Exp $

LWIPDIR := src
LWIPARCH := kos
KOS_CFLAGS := $(KOS_CFLAGS) -DIPv4 -DLWIP_DEBUG \
	-I$(LWIPDIR)/include -I$(LWIPDIR)/arch/$(LWIPARCH)/include \
	-I$(LWIPDIR)/include/ipv4 -I.

# COREFILES, CORE4FILES: The minimum set of files needed for lwIP.
COREFILES=$(LWIPDIR)/core/mem.c $(LWIPDIR)/core/memp.c $(LWIPDIR)/core/netif.c \
	$(LWIPDIR)/core/pbuf.c $(LWIPDIR)/core/stats.c $(LWIPDIR)/core/sys.c \
        $(LWIPDIR)/core/tcp.c $(LWIPDIR)/core/tcp_input.c \
        $(LWIPDIR)/core/tcp_output.c $(LWIPDIR)/core/udp.c 
CORE4FILES=$(LWIPDIR)/core/ipv4/icmp.c $(LWIPDIR)/core/ipv4/ip.c \
	$(LWIPDIR)/core/inet.c $(LWIPDIR)/core/ipv4/ip_addr.c


# APIFILES: The files which implement the sequential and socket APIs.
APIFILES=$(LWIPDIR)/api/api_lib.c $(LWIPDIR)/api/api_msg.c $(LWIPDIR)/api/tcpip.c \
	$(LWIPDIR)/api/err.c $(LWIPDIR)/api/sockets.c 

# NETIFFILES: Files implementing various generic network interface functions.'
NETIFFILES=$(LWIPDIR)/netif/loopif.c \
	$(LWIPDIR)/netif/arp.c \
	$(LWIPDIR)/netif/tcpdump.c

# ARCHFILES: Archiecture specific files.
ARCHFILES=$(wildcard $(LWIPDIR)/arch/$(LWIPARCH)/*.c $(LWIPDIR)/arch/$(LWIPARCH)/netif/*.c)

# LWIPFILES: All the above.
LWIPFILES=$(COREFILES) $(CORE4FILES) $(APIFILES) $(NETIFFILES) $(ARCHFILES)
#LWIPFILESW=$(wildcard $(LWIPFILES))
LWIPOBJS=$(LWIPFILES:.c=.o)

DCLOADOBJS=dcload/commands.o dcload/dcload-lwip.o dcload/dcload_lwip_syscall.o dcload/syscalls.o

OBJS = $(LWIPOBJS) liblwip.o dhcp/dhcp.o $(DCLOADOBJS)

SUBDIRS = dcload

all: $(OBJS)
	rm -f $(KOS_ADDONS_BASE)/lib/liblwip4.a
	$(KOS_AR) rcs $(KOS_ADDONS_BASE)/lib/liblwip4.a $(OBJS)

# Grab the shared Makefile pieces
include $(KOS_BASE)/Makefile.prefab

