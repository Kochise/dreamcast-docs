# BUILDBOR.MAK - Make file for DB-Library Borland DOS examples.
#
#	     Copyright (C) 1995 Microsoft Corp.
#

CC = bcc.exe

!if  "$(DEBUG_TYPE)" == "debug"
CFLAGS_DEBUG = -v
!endif

!if "$(MODEL_TYPE)" == "medium"
MODEL_PREFIX = m
!else
MODEL_PREFIX = l
!endif

CFLAGS = -DDBMSDOS -m$(MODEL_PREFIX)

DBLIB_LIB = B$(MODEL_PREFIX)DBLIB.LIB

all: $(APP).exe

# Compile .c file
.c.exe:
    $(CC) $(CFLAGS) $(CFLAGS_DEBUG) -Ic:\sql\dblib\include -Lc:\sql\dblib\lib $(@B).C $(DBLIB_LIB)
    del $(@B).obj
