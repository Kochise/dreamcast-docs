OBJS= blocksort.o  \
      huffman.o    \
      crctable.o   \
      randtable.o  \
      compress.o   \
      decompress.o \
      bzlib.o

myall: $(OBJS)
	rm -f $(KOS_ADDONS_BASE)/lib/libbz2.a
	$(KOS_AR) rcs $(KOS_ADDONS_BASE)/lib/libbz2.a $(OBJS)

KOS_LOCAL_CFLAGS = -I$(KOS_ADDONS_BASE)/include/bzlib

include $(KOS_BASE)/Makefile.prefab

