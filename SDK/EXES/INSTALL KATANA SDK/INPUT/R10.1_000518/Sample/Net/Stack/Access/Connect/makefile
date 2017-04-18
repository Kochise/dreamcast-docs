#------------------------------------------------------------------------------
# Connect.mak
#------------------------------------------------------------------------------

PROJECT	= Connect

PROJECT_SRC	= \
		sample1.c\
		njloop.c\
		sbinit.c\
		netutl.c\
		snprintf.c\

SYSTEM_LIBS	= \
		dmcast\
		mdmapi\
		modem\
		netuu\
		nt_utl\
		pwnet\
		tcp\
		ppp\
		dns\
		socket\
		dclan\

EXTRA_DEFS	= KGTRN_ACCESS
		# KGTRN_PLANET_WEB

ifeq ($(EXTRA_DEFS),KGTRN_PLANET_WEB)
SYSTEM_INCLUDE	= $(DEF_INCLUDE)\pw
else
SYSTEM_INCLUDE	= $(DEF_INCLUDE)\access
endif

OPTIMIZE =	1

#COMPILER =	SHC
GFXLIB	=	NINJA
OUTPUT	=	ELF

DEBUG	=	TRUE
LIST	=	FALSE

include $(KATANA_ROOT)\Sample\dc.inc

