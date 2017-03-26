TARGET = libbz2.a
OBJS= blocksort.o  \
      huffman.o    \
      crctable.o   \
      randtable.o  \
      compress.o   \
      decompress.o \
      bzlib.o

include ../Makefile.prefab
KOS_LOCAL_CFLAGS := $(KOS_LOCAL_CFLAGS) -I$(KOS_ADDONS_BASE)/include/bzlib

