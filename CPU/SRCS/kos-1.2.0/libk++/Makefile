#
# libk++
#
# Simplified libstdc++ for KOS
#
# Makefile (c)2002 Dan Potter
#   

OBJS = mem.o pure_virtual.o
SUBDIRS =

myall: $(OBJS)
	rm -f $(KOS_BASE)/lib/libk++.a
	$(KOS_AR) rcs $(KOS_BASE)/lib/libk++.a $(OBJS)

include $(KOS_BASE)/Makefile.prefab


