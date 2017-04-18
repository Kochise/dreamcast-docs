#######################################################################
#
# Hermes Makefile
#
# (C) 1993-1994 Microsoft
#
# a-petesk       12-30-93       Created
#
# Note:  This makefile uses the herm.mk master makefile
#        For more information, see documentation on herm.mk
#
######################################################################## HERMES makefile
#

OPSYS=NT


RELEASE=site.srv\$(RELDIR)
TARGET=viewdll.dll
DEFFILE=
NO_IMPLIB=TRUE

SUBDIRS=\

CONSOLE=1
USEMFC=0
CFILES=\
      .\viewdll.c

RCFILES=\
      .\viewdll.rc

LIBS=\
        $(CONLIBS) \
        $(CLIB)\ntwdblib.lib

!include $(COMMON)\herm.mk

