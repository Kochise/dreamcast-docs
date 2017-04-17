romdisk.img:
	genromfs -f romdisk.img -d romdisk -v

romdisk.o: romdisk.img
	bin2o romdisk.img romdisk romdisk.o

all-before: romdisk.o
	
	
all-after : 
#	dc-tool -e -x $(BIN)
