# Microsoft Developer Studio Generated NMAKE File, Based on VdMFC.dsp
#
# VdMFC.mak: makefile
#
# Copyright (C) 1997 Microsoft Corporation
# All rights reserved.
#
# This source code is only intended as a supplement to the
# Broadcast Architecture Programmer's Reference.
# For detailed information regarding Broadcast
# Architecture, see the reference.
#
!IF "$(CFG)" == ""
CFG=VdMFC - Win32 Debug
!MESSAGE No configuration specified. Defaulting to VdMFC - Win32 Debug.
!ENDIF 

!IF "$(CFG)" != "VdMFC - Win32 Release" && "$(CFG)" != "VdMFC - Win32 Debug"
!MESSAGE Invalid configuration "$(CFG)" specified.
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "VdMFC.mak" CFG="VdMFC - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "VdMFC - Win32 Release" (based on "Win32 (x86) Application")
!MESSAGE "VdMFC - Win32 Debug" (based on "Win32 (x86) Application")
!MESSAGE 
!ERROR An invalid configuration is specified.
!ENDIF 

!IF "$(OS)" == "Windows_NT"
NULL=
!ELSE 
NULL=nul
!ENDIF 

!IF  "$(CFG)" == "VdMFC - Win32 Release"

OUTDIR=.\Release
INTDIR=.\Release
# Begin Custom Macros
OutDir=.\Release
# End Custom Macros

!IF "$(RECURSE)" == "0" 

ALL : "$(OUTDIR)\VdMFC.exe"

!ELSE 

ALL : "$(OUTDIR)\VdMFC.exe"

!ENDIF 

CLEAN :
	-@erase "$(INTDIR)\bpcbase.obj"
	-@erase "$(INTDIR)\bpcdev.obj"
	-@erase "$(INTDIR)\bpcvid.obj"
	-@erase "$(INTDIR)\StdAfx.obj"
	-@erase "$(INTDIR)\vc50.idb"
	-@erase "$(INTDIR)\VdMFC.obj"
	-@erase "$(INTDIR)\VdMFC.pch"
	-@erase "$(INTDIR)\VdMFC.res"
	-@erase "$(INTDIR)\VdMFCDlg.obj"
	-@erase "$(OUTDIR)\VdMFC.exe"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP=cl.exe
CPP_PROJ=/nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D\
 "_AFXDLL" /Fp"$(INTDIR)\VdMFC.pch" /Yu"stdafx.h" /Fo"$(INTDIR)\\"\
 /Fd"$(INTDIR)\\" /FD /c 
CPP_OBJS=.\Release/
CPP_SBRS=.

.c{$(CPP_OBJS)}.obj::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.cpp{$(CPP_OBJS)}.obj::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.cxx{$(CPP_OBJS)}.obj::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.c{$(CPP_SBRS)}.sbr::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.cpp{$(CPP_SBRS)}.sbr::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.cxx{$(CPP_SBRS)}.sbr::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

MTL=midl.exe
MTL_PROJ=/nologo /D "NDEBUG" /mktyplib203 /o NUL /win32 
RSC=rc.exe
RSC_PROJ=/l 0x409 /fo"$(INTDIR)\VdMFC.res" /d "NDEBUG" /d "_AFXDLL" 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\VdMFC.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
LINK32_FLAGS=/nologo /subsystem:windows /incremental:no\
 /pdb:"$(OUTDIR)\VdMFC.pdb" /machine:I386 /out:"$(OUTDIR)\VdMFC.exe" 
LINK32_OBJS= \
	"$(INTDIR)\bpcbase.obj" \
	"$(INTDIR)\bpcdev.obj" \
	"$(INTDIR)\bpcvid.obj" \
	"$(INTDIR)\StdAfx.obj" \
	"$(INTDIR)\VdMFC.obj" \
	"$(INTDIR)\VdMFC.res" \
	"$(INTDIR)\VdMFCDlg.obj"

"$(OUTDIR)\VdMFC.exe" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ELSEIF  "$(CFG)" == "VdMFC - Win32 Debug"

OUTDIR=.\Debug
INTDIR=.\Debug
# Begin Custom Macros
OutDir=.\Debug
# End Custom Macros

!IF "$(RECURSE)" == "0" 

ALL : "$(OUTDIR)\VdMFC.exe"

!ELSE 

ALL : "$(OUTDIR)\VdMFC.exe"

!ENDIF 

CLEAN :
	-@erase "$(INTDIR)\bpcbase.obj"
	-@erase "$(INTDIR)\bpcdev.obj"
	-@erase "$(INTDIR)\bpcvid.obj"
	-@erase "$(INTDIR)\StdAfx.obj"
	-@erase "$(INTDIR)\vc50.idb"
	-@erase "$(INTDIR)\vc50.pdb"
	-@erase "$(INTDIR)\VdMFC.obj"
	-@erase "$(INTDIR)\VdMFC.pch"
	-@erase "$(INTDIR)\VdMFC.res"
	-@erase "$(INTDIR)\VdMFCDlg.obj"
	-@erase "$(OUTDIR)\VdMFC.exe"
	-@erase "$(OUTDIR)\VdMFC.ilk"
	-@erase "$(OUTDIR)\VdMFC.pdb"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP=cl.exe
CPP_PROJ=/nologo /MDd /W3 /Gm /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS"\
 /D "_AFXDLL" /Fp"$(INTDIR)\VdMFC.pch" /Yu"stdafx.h" /Fo"$(INTDIR)\\"\
 /Fd"$(INTDIR)\\" /FD /c 
CPP_OBJS=.\Debug/
CPP_SBRS=.

.c{$(CPP_OBJS)}.obj::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.cpp{$(CPP_OBJS)}.obj::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.cxx{$(CPP_OBJS)}.obj::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.c{$(CPP_SBRS)}.sbr::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.cpp{$(CPP_SBRS)}.sbr::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.cxx{$(CPP_SBRS)}.sbr::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

MTL=midl.exe
MTL_PROJ=/nologo /D "_DEBUG" /mktyplib203 /o NUL /win32 
RSC=rc.exe
RSC_PROJ=/l 0x409 /fo"$(INTDIR)\VdMFC.res" /d "_DEBUG" /d "_AFXDLL" 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\VdMFC.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
LINK32_FLAGS=/nologo /subsystem:windows /incremental:yes\
 /pdb:"$(OUTDIR)\VdMFC.pdb" /debug /machine:I386 /out:"$(OUTDIR)\VdMFC.exe"\
 /pdbtype:sept 
LINK32_OBJS= \
	"$(INTDIR)\bpcbase.obj" \
	"$(INTDIR)\bpcdev.obj" \
	"$(INTDIR)\bpcvid.obj" \
	"$(INTDIR)\StdAfx.obj" \
	"$(INTDIR)\VdMFC.obj" \
	"$(INTDIR)\VdMFC.res" \
	"$(INTDIR)\VdMFCDlg.obj"

"$(OUTDIR)\VdMFC.exe" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ENDIF 


!IF "$(CFG)" == "VdMFC - Win32 Release" || "$(CFG)" == "VdMFC - Win32 Debug"
SOURCE=.\bpcbase.cpp

!IF  "$(CFG)" == "VdMFC - Win32 Release"

DEP_CPP_BPCBA=\
	".\bpcbase.h"\
	".\StdAfx.h"\
	

"$(INTDIR)\bpcbase.obj" : $(SOURCE) $(DEP_CPP_BPCBA) "$(INTDIR)"\
 "$(INTDIR)\VdMFC.pch"


!ELSEIF  "$(CFG)" == "VdMFC - Win32 Debug"

DEP_CPP_BPCBA=\
	".\bpcbase.h"\
	

"$(INTDIR)\bpcbase.obj" : $(SOURCE) $(DEP_CPP_BPCBA) "$(INTDIR)"\
 "$(INTDIR)\VdMFC.pch"


!ENDIF 

SOURCE=.\bpcdev.cpp

!IF  "$(CFG)" == "VdMFC - Win32 Release"

DEP_CPP_BPCDE=\
	".\bpcbase.h"\
	".\bpcdev.h"\
	".\StdAfx.h"\
	

"$(INTDIR)\bpcdev.obj" : $(SOURCE) $(DEP_CPP_BPCDE) "$(INTDIR)"\
 "$(INTDIR)\VdMFC.pch"


!ELSEIF  "$(CFG)" == "VdMFC - Win32 Debug"

DEP_CPP_BPCDE=\
	".\bpcbase.h"\
	".\bpcdev.h"\
	

"$(INTDIR)\bpcdev.obj" : $(SOURCE) $(DEP_CPP_BPCDE) "$(INTDIR)"\
 "$(INTDIR)\VdMFC.pch"


!ENDIF 

SOURCE=.\bpcvid.cpp

!IF  "$(CFG)" == "VdMFC - Win32 Release"

DEP_CPP_BPCVI=\
	".\bpcbase.h"\
	".\bpcdev.h"\
	".\bpcvid.h"\
	".\StdAfx.h"\
	

"$(INTDIR)\bpcvid.obj" : $(SOURCE) $(DEP_CPP_BPCVI) "$(INTDIR)"\
 "$(INTDIR)\VdMFC.pch"


!ELSEIF  "$(CFG)" == "VdMFC - Win32 Debug"

DEP_CPP_BPCVI=\
	".\bpcbase.h"\
	".\bpcdev.h"\
	".\bpcvid.h"\
	

"$(INTDIR)\bpcvid.obj" : $(SOURCE) $(DEP_CPP_BPCVI) "$(INTDIR)"\
 "$(INTDIR)\VdMFC.pch"


!ENDIF 

SOURCE=.\StdAfx.cpp
DEP_CPP_STDAF=\
	".\StdAfx.h"\
	

!IF  "$(CFG)" == "VdMFC - Win32 Release"

CPP_SWITCHES=/nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D\
 "_AFXDLL" /Fp"$(INTDIR)\VdMFC.pch" /Yc"stdafx.h" /Fo"$(INTDIR)\\"\
 /Fd"$(INTDIR)\\" /FD /c 

"$(INTDIR)\StdAfx.obj"	"$(INTDIR)\VdMFC.pch" : $(SOURCE) $(DEP_CPP_STDAF)\
 "$(INTDIR)"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "VdMFC - Win32 Debug"

CPP_SWITCHES=/nologo /MDd /W3 /Gm /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D\
 "_WINDOWS" /D "_AFXDLL" /Fp"$(INTDIR)\VdMFC.pch" /Yc"stdafx.h" /Fo"$(INTDIR)\\"\
 /Fd"$(INTDIR)\\" /FD /c 

"$(INTDIR)\StdAfx.obj"	"$(INTDIR)\VdMFC.pch" : $(SOURCE) $(DEP_CPP_STDAF)\
 "$(INTDIR)"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ENDIF 

SOURCE=.\VdMFC.cpp

!IF  "$(CFG)" == "VdMFC - Win32 Release"

DEP_CPP_VDMFC=\
	".\bpcbase.h"\
	".\bpcdev.h"\
	".\bpcvid.h"\
	".\StdAfx.h"\
	".\VdMFC.h"\
	".\VdMFCDlg.h"\
	".\vidtypes.h"\
	

"$(INTDIR)\VdMFC.obj" : $(SOURCE) $(DEP_CPP_VDMFC) "$(INTDIR)"\
 "$(INTDIR)\VdMFC.pch"


!ELSEIF  "$(CFG)" == "VdMFC - Win32 Debug"

DEP_CPP_VDMFC=\
	".\bpcbase.h"\
	".\bpcdev.h"\
	".\bpcvid.h"\
	".\VdMFC.h"\
	".\VdMFCDlg.h"\
	".\vidtypes.h"\
	

"$(INTDIR)\VdMFC.obj" : $(SOURCE) $(DEP_CPP_VDMFC) "$(INTDIR)"\
 "$(INTDIR)\VdMFC.pch"


!ENDIF 

SOURCE=.\VdMFC.rc
DEP_RSC_VDMFC_=\
	".\res\VdMFC.ico"\
	".\res\VdMFC.rc2"\
	

"$(INTDIR)\VdMFC.res" : $(SOURCE) $(DEP_RSC_VDMFC_) "$(INTDIR)"
	$(RSC) $(RSC_PROJ) $(SOURCE)


SOURCE=.\VdMFCDlg.cpp

!IF  "$(CFG)" == "VdMFC - Win32 Release"

DEP_CPP_VDMFCD=\
	".\bpcbase.h"\
	".\bpcdev.h"\
	".\bpcvid.h"\
	".\StdAfx.h"\
	".\VdMFC.h"\
	".\VdMFCDlg.h"\
	".\vidtypes.h"\
	

"$(INTDIR)\VdMFCDlg.obj" : $(SOURCE) $(DEP_CPP_VDMFCD) "$(INTDIR)"\
 "$(INTDIR)\VdMFC.pch"


!ELSEIF  "$(CFG)" == "VdMFC - Win32 Debug"

DEP_CPP_VDMFCD=\
	".\bpcbase.h"\
	".\bpcdev.h"\
	".\bpcvid.h"\
	".\VdMFC.h"\
	".\VdMFCDlg.h"\
	".\vidtypes.h"\
	

"$(INTDIR)\VdMFCDlg.obj" : $(SOURCE) $(DEP_CPP_VDMFCD) "$(INTDIR)"\
 "$(INTDIR)\VdMFC.pch"


!ENDIF 


!ENDIF 

