# 
# Dreamcast PLIB Derivative makefile by Peter Hatch
# based on
# addons/libgl Makefile
# (c)2001 Dan Potter
#   

OBJS =  ulError.o sg.o fnt.o fntTXF.o
# Comment the next line out if you don't want sgd (SG stuff using doubles instead of floats) or sgIsect (I haven't checked, but FNT doesn't need it).
OBJS += sgd.o sgIsect.o
SUBDIRS =

myall: $(OBJS)
	rm -f $(KOS_ADDONS_BASE)/lib/libdcplib.a
	$(KOS_AR) rcs $(KOS_ADDONS_BASE)/lib/libdcplib.a $(OBJS)

include $(KOS_BASE)/Makefile.prefab


