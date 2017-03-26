# KOS libexports ##version##
#
# Makefile
# Copyright (C)2003 Dan Potter
#   
# $Id: Makefile,v 1.2 2003/07/31 00:47:17 bardtx Exp $

OBJS	:= kernel_exports.o arch_exports.o maple_exports.o lwip_exports.o

all: $(OBJS)
	rm -f $(KOS_BASE)/lib/libexports.a
	$(KOS_AR) rcs $(KOS_BASE)/lib/libexports.a $(OBJS)

# Grab the shared Makefile pieces
include $(KOS_BASE)/Makefile.prefab

kernel_exports.c: $(KOS_BASE)/kernel/exports.txt
	$(KOS_BASE)/utils/genexports/genexportshims.sh $< kernel_exports.c

arch_exports.c: $(KOS_BASE)/kernel/arch/$(KOS_ARCH)/exports.txt
	$(KOS_BASE)/utils/genexports/genexportshims.sh $< arch_exports.c

maple_exports.c: $(KOS_BASE)/loadable/modules/drivers/dreamcast/maple/exports.txt
	$(KOS_BASE)/utils/genexports/genexportshims.sh $< maple_exports.c

lwip_exports.c: $(KOS_BASE)/loadable/modules/net/net_lwip/exports.txt
	$(KOS_BASE)/utils/genexports/genexportshims.sh $< lwip_exports.c

clean:
	rm -f $(OBJS) kernel_exports.c arch_exports.c maple_exports.c lwip_exports.c
