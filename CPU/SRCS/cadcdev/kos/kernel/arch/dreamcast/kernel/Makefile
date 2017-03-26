# KallistiOS ##version##
#
# arch/dreamcast/kernel/Makefile
# (c)2000 Dan Potter
#   
# $Id: Makefile,v 1.14 2003/02/14 06:41:00 bardtx Exp $

# Generic kernel abstraction layer: this provides a set of routines
# that the portable part of the kernel expects to find on every
# target processor. Other routines may be present as well, but
# that minimum set must be present.

COPYOBJS = banner.o cache.o entry.o irq.o init.o mm.o panic.o
COPYOBJS += rtc.o timer.o
COPYOBJS += init_flags_default.o init_romdisk_default.o
COPYOBJS += mmu.o itlb.o
COPYOBJS += exec.o execasm.o stack.o gdb_stub.o thdswitch.o arch_exports.o
OBJS = $(COPYOBJS) startup.o
SUBDIRS = 

myall: $(OBJS)
	-cp $(COPYOBJS) $(KOS_BASE)/kernel/build/
	-rm banner.c banner.o

include $(KOS_BASE)/Makefile.prefab

banner.o: banner.c

banner.c: make_banner.sh
	./make_banner.sh

arch_exports.o: arch_exports.c

arch_exports.c: ../exports.txt
	$(KOS_BASE)/utils/genexports/genexports.sh ../exports.txt arch_exports.c arch_symtab

clean:
	-rm -f banner.c
	-rm -f $(OBJS)
	-rm -f arch_exports.c
	-rm -f arch_exports.c
