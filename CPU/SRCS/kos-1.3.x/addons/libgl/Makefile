# KallistiOS ##version##
#
# addons/libgl Makefile
# (c)2001 Dan Potter
#   
# $Id: Makefile,v 1.5 2003/02/27 04:25:39 bardtx Exp $

OBJS =  gldepth.o gldraw.o glkos.o gllight.o glmisc.o
OBJS += gltex.o gltrans.o glvars.o glblend.o glfog.o glmodifier.o glnzclip.o
SUBDIRS =

myall: $(OBJS)
	rm -f $(KOS_ADDONS_BASE)/lib/libgl.a
	$(KOS_AR) rcs $(KOS_ADDONS_BASE)/lib/libgl.a $(OBJS)

include $(KOS_BASE)/Makefile.prefab


