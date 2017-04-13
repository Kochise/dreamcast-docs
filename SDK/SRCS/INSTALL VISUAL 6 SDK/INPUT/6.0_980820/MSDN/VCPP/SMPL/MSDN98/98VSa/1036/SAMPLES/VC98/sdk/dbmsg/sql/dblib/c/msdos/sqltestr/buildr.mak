# BUILDR.MAK - Make file for DB-Library DOS examples.
#
#	     Copyright (C) 1995 Microsoft Corp.
#

LINK         = link.exe
CC           = cl.exe
RC				 = rc.exe

!if  "$(DEBUG_TYPE)" == "debug"
CFLAGS_DEBUG = -Zid
LFLAGS_DEBUG = /CO
!endif

!if "$(MODEL_TYPE)" == "medium"
MODEL_PREFIX = M
!else
MODEL_PREFIX = L
!endif

CFLAGS = -DDBMSDOS /c /Zi /Lr /A$(MODEL_PREFIX)
LFLAGS = /STACK:20000

DBLIB_LIB = R$(MODEL_PREFIX)dblib.LIB

all: $(APP).exe

# Compile .c file
.c.exe:
    $(CC) $(CFLAGS) $(CFLAGS_DEBUG) $(@B).C
    $(LINK) $(@B).OBJ,$(@B).EXE,,$(DBLIB_LIB),nul.def $(LFLAGS) $(LFLAGS_DEBUG)
	 del $(@B).obj
