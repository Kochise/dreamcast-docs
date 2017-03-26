# KallistiOS ##version##
#
# examples/dreamcast/kgl/demos/Makefile
# (c)2001-2002 Dan Potter
#   
# $Id: Makefile,v 1.2 2002/03/04 05:00:45 bardtx Exp $

all:
ifdef KOS_CCPLUS
	$(KOS_MAKE) -C tunnel
endif
	$(KOS_MAKE) -C bubbles

clean:
ifdef KOS_CCPLUS
	$(KOS_MAKE) -C tunnel clean
endif
	$(KOS_MAKE) -C bubbles clean
		
dist:
ifdef KOS_CCPLUS
	$(KOS_MAKE) -C tunnel dist
endif
	$(KOS_MAKE) -C bubbles dist


