TARGET = libz.a
OBJS = adler32.o compress.o crc32.o uncompr.o trees.o deflate.o\
       zutil.o inflate.o infblock.o inftrees.o infcodes.o infutil.o \
	inffast.o gzio.o  kos_zlib.o

KOS_LOCAL_CFLAGS = -I$(KOS_ADDONS_BASE)/include/zlib -DNO_ERRNO_H

include ../Makefile.prefab
