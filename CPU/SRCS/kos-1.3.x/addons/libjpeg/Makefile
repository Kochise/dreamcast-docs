# KallistiOS ##version##
#
# kernel Makefile
# (c)2001 Dan Potter
#   
# $Id: Makefile,v 1.4 2003/02/27 04:25:40 bardtx Exp $

OBJS = 	jcapimin.o jcapistd.o jccoefct.o jccolor.o jcdctmgr.o jchuff.o \
	jcinit.o jcmainct.o jcmarker.o jcmaster.o jcomapi.o jcparam.o \
        jcphuff.o jcprepct.o jcsample.o jctrans.o jdapimin.o jdapistd.o \
        jdatadst.o jdatasrc.o jdcoefct.o jdcolor.o jddctmgr.o jdhuff.o \
        jdinput.o jdmainct.o jdmarker.o jdmaster.o jdmerge.o jdphuff.o \
        jdpostct.o jdsample.o jdtrans.o jerror.o jfdctflt.o \
        jidctflt.o jidctred.o jquant1.o \
        jquant2.o jutils.o jmemmgr.o
OBJS +=	jmemnobs.o
OBJS += kos_img.o

# Compat with older KOS functions for DC usage
ifeq ($(KOS_ARCH), dreamcast)
	OBJS += kos_texture.o
endif

SUBDIRS =

myall: $(OBJS)
	rm -f $(KOS_ADDONS_BASE)/lib/libjpeg.a
	$(KOS_AR) rcs $(KOS_ADDONS_BASE)/lib/libjpeg.a $(OBJS)

include $(KOS_BASE)/Makefile.prefab


