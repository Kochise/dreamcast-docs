all-before:
	rm -f romdisk.img romdisk.o wfont.o
	bin2o wfont.bin wfont wfont.o
	genromfs -f romdisk.img -d romdisk -v
	bin2o romdisk.img romdisk_boot romdisk.o
	
	
all-after : 
	dc-tool -e -x $(BIN)
