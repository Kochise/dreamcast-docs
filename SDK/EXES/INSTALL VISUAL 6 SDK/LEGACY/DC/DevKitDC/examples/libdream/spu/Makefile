BIN = spu
OBJS = spu.o romdisk.o
EXTRA_CLEAN = romdisk.img

include ../Makefile.prefab

romdisk.o: romdisk.img
	$(KOS_BASE)/utils/bin2o/bin2o romdisk.img romdisk romdisk.o

romdisk.img:
	$(KOS_GENROMFS) -f romdisk.img -d romdisk -v


