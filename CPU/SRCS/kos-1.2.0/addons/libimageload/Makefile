all: libimageload.a

OBJS = readpcx.o readbmp.o readjpeg.o imageload.o jitter.o

$(OBJS):

libimageload.a: $(OBJS)
	rm -f $(KOS_ADDONS_BASE)/lib/libimageload.a
	$(KOS_AR) rcs $(KOS_ADDONS_BASE)/lib/libimageload.a $(OBJS)

include $(KOS_BASE)/Makefile.prefab
