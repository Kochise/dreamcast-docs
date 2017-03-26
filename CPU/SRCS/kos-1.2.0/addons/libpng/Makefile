OBJS = pngerror.o pnggccrd.o pngget.o pngmem.o pngpread.o pngread.o \
	pngrio.o pngrtran.o pngrutil.o pngset.o pngtrans.o pngvcrd.o \
	pngwrite.o pngwtran.o pngwutil.o png.o readpng.o kos_img.o

# Compat with older KOS functions for DC usage
ifeq ($(KOS_ARCH), dreamcast)
	OBJS += kos_texture.o
endif

myall: $(OBJS)
	rm -f $(KOS_ADDONS_BASE)/lib/libpng.a
	$(KOS_AR) rcs $(KOS_ADDONS_BASE)/lib/libpng.a $(OBJS)

KOS_LOCAL_CFLAGS = -I$(KOS_ADDONS_BASE)/include/png \
	-I$(KOS_ADDONS_BASE)/include/zlib \
	-DPNG_NO_MNG_FEATURES \
	-DPNG_NO_READ_sCAL -DPNG_NO_WRITE_sCAL \
	-DPNG_NO_SETJMP_SUPPORTED \
	-DPNG_NO_WRITE_tIME

include $(KOS_BASE)/Makefile.prefab
