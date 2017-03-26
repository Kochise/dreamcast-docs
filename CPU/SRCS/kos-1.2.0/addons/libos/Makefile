# KallistiOS 1.2.0
#
# os/Makefile
# (c)2001 Dan Potter
#   
# $Id: Makefile,v 1.2 2002/01/05 07:03:12 bardtx Exp $

all:
	rm -f $(KOS_BASE)/lib/libos.a
	$(KOS_MAKE) -C process
	$(KOS_AR) rcs $(KOS_BASE)/lib/libos.a build/*.o

clean:
	$(KOS_MAKE) -C process clean
	$(KOS_MAKE) -C main clean
	$(KOS_MAKE) -C userland clean
	-rm -f build/*.o

run:

