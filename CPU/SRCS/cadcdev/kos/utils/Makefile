# KallistiOS ##version##
#
# utils/Makefile
# (c)2001 Dan Potter
#   
# $Id: Makefile,v 1.5 2002/12/12 20:35:48 gilm Exp $

DIRS = genromfs wav2adpcm vqenc gba-crcfix

# Ok for these to fail atm...

all:
	for i in $(DIRS); do $(KOS_MAKE) -C $$i; done

clean:
	for i in $(DIRS); do $(KOS_MAKE) -C $$i clean; done
		

