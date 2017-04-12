# This is a part of the Microsoft Foundation Classes C++ library.
# Copyright (C) 1992-1998 Microsoft Corporation
# All rights reserved.
#
# This source code is only intended as a supplement to the
# Microsoft Foundation Classes Reference and related
# electronic documentation provided with the library.
# See these sources for detailed information regarding the
# Microsoft Foundation Classes product.

# MFCN42[D].DLL is a DLL
#  which exports all the MFC/NET classes
#
# If you need a private build of the MFC NET DLL, be sure to rename
#  "MFCN42.DLL" to something more appropriate for your application.
# Please do not re-distribute a privately built version with the
#  name "MFCN42.DLL".
#
# Use nmake /f mfcnet.mak LIBNAME=<my name> to do this.
#
# Note: LIBNAME must be 6 characters or less.

!ifndef LIBNAME
!error LIBNAME is not defined. LIBNAME=MFCN42 builds the prebuilt DLL.
!endif

!ifndef REGEN
REGEN=0
!endif

!if "$(DEBUG)" != "0"
CRTDLL=msvcrtd.lib
!else
CRTDLL=msvcrt.lib
!endif

TARGET=w
DLL=2
TARG=$(LIBNAME)
TARGDEFS=/D_AFX_NET_IMPL
MFCDLL=MFC42
#LFLAGS=/nodefaultlib

!if "$(UNICODE)" == "1"
TARG=$(TARG)U
MFCDLL=$(MFCDLL)U
!else
LFLAGS=$(LFLAGS) /filealign:4096
!endif

!if "$(DEBUG)" != "0"
# Debug DLL build
RCDEFINES=/D_DEBUG
LFLAGS=$(LFLAGS)
PCH_FILE=$D\stdafxn.pch
PCH_CPP=dllnet
TARG=$(TARG)D
MFCDLL=$(MFCDLL)D

!ELSE
# Release DLL build
RCDEFINES=
LFLAGS=$(LFLAGS)
PCH_FILE=$D\stdafxn.pch
PCH_CPP=dllnet
!ENDIF

DEFFILE=$(PLATFORM)\$(TARG).DEF

MFCDLL=..\lib\$(MFCDLL).lib

!if "$(DEBUGTYPE)" == ""
DEBUGTYPE=cv
!endif

!if "$(CODEVIEW)" != "0"
!if "$(REGEN)" != "1"
LFLAGS=$(LFLAGS) /debug:full /debugtype:$(DEBUGTYPE)
!else
LFLAGS=$(LFLAGS) /debug:none
!endif
!if "$(NO_PDB)" != "1" && "$(REGEN)" != "1"
LFLAGS=$(LFLAGS) /pdb:$(TARG).pdb
!else
LFLAGS=$(LFLAGS) /pdb:none
!endif
!else
LFLAGS=$(LFLAGS) /debug:none /incremental:no
!endif

!ifdef RELEASE # Release VERSION info
RCDEFINES=$(RCDEFINES) /DRELEASE
LFLAGS=$(LFLAGS) /release
!endif

LFLAGS=$(LFLAGS) /dll

# OPT:noref keeps unreferenced functions (ie. no dead-code elimination)
!if "$(REGEN)" == "0"
LFLAGS=$(LFLAGS) /opt:noref /opt:icf,32
!else
LFLAGS=$(LFLAGS) /opt:ref
!endif

LFLAGS=$(LFLAGS) /version:6.00 /base:0x5F600000

LIBS=$(MFCDLL) $(CRTDLL) kernel32.lib gdi32.lib user32.lib

!if "$(ORDER)" == "1"
!if exist($(PLATFORM)\$(TARG).prf)
DEFS=$(DEFS) /D_AFX_FUNCTION_ORDER
LFLAGS=$(LFLAGS) /order:@$(PLATFORM)\$(TARG).prf
!endif
!endif

dll_goal: create2.dir $(TARG).dll ..\lib\$(TARG).lib

#############################################################################
# import most rules and library files from normal makefile

!include makefile

create2.dir:
	@-if not exist $D\*.* mkdir $D

#############################################################################
# Build target

$D\$(TARG).res: mfcnet.rc ..\include\afxbld_.h
	rc /r $(RCFLAGS) $(RCDEFINES) /fo $D\$(TARG).res mfcnet.rc

DLL_OBJS=$(SOCKETS)
$(TARG).dll ..\lib\$(TARG).lib: $D\$(PCH_CPP).obj $(DLL_OBJS) $(DEFFILE) $D\$(TARG).res
	link @<<
$(LFLAGS)
$(LIBS)
$D\$(PCH_CPP).obj
$(DLL_OBJS)
$D\$(TARG).res
/def:$(DEFFILE)
/out:$(TARG).DLL
/map:$D\$(TARG).MAP
/implib:..\lib\$(TARG).LIB
/ignore:4199
/filealign:4096
/delayload:comdlg32.dll
/delayload:comctl32.dll
/delayload:shell32.dll
/delayload:advapi32.dll
/delayload:wininet.dll
/delayload:wsock32.dll
/delayload:ole32.dll
/delayload:oleaut32.dll
/delayload:oledlg.dll
/delayload:urlmon.dll
/delayload:odbc32.dll
/delayload:winspool.drv
mfcdload.lib
delayimp.lib
<<
	if exist ..\lib\$(TARG).exp del ..\lib\$(TARG).exp

#############################################################################
