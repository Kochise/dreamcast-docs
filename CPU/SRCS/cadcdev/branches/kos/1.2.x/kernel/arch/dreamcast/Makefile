# KallistiOS ##version##
#
# arch/dreamcast Makefile
# (c)2001 Dan Potter
#   
# $Id: Makefile,v 1.4 2002/05/05 22:17:06 bardtx Exp $
	
SUBDIRS=fs hardware kernel math sound util

ifeq ($(KOS_SUBARCH), navi)
	SUBDIRS += navi
endif

include $(KOS_BASE)/Makefile.rules

all: subdirs
clean: clean_subdirs
