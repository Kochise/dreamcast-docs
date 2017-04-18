##-----------------------------------------------------------------------------
##
##	FILE:		a64thunk.mak
##
##	DESC:		Makefile for a64thunk sample
##
##	HISTORY:	2000.01.xx	Reworked samples/boilerplates for R10 release.
##
##-----------------------------------------------------------------------------

PROJECT			= a64thunk

PROJECT_SRC		=\
				sbinit.c\
				main.c\
				a64chain.c\
				a64dma.c\
				a64file.c\
				bpacsetup.c\
				bpprintf.c

SYSTEM_LIBS		=\
				audio64

OPTIMIZE		= 1

#COMPILER		= SHC
GFXLIB			= NINJA
OUTPUT			= ELF

DEBUG			= TRUE
LIST			= FALSE

include $(KATANA_ROOT)\sample\dc.inc
