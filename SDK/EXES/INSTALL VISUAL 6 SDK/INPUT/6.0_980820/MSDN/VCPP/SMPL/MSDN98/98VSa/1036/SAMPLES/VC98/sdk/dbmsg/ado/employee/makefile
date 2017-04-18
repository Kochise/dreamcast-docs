# ADO Employee Sample
# Copyright 1995 - 1998 Microsoft Corporation

!ifdef NODEBUG
DEBUG=Release
!else
DEBUG=Debug
!endif

!if ( "$(CPU)" == "ALPHA" ) || ( "$(PROCESSOR_ARCHITEECTURE)" == "ALPHA" )
PROC=Win32 (ALPHA)
!else
PROC=Win32
!endif

All:
 $(MAKE) -l$(MAKEFLAGS) -f Emp.Mak CFG="Emp - $(PROC) $(DEBUG)"
