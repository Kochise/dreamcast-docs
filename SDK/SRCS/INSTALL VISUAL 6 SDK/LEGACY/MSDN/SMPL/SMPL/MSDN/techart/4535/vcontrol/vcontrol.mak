# Microsoft Developer Studio Generated NMAKE File, Format Version 4.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Dynamic-Link Library" 0x0102

!IF "$(CFG)" == ""
CFG=VControl - Win32 Debug
!MESSAGE No configuration specified.  Defaulting to VControl - Win32 Debug.
!ENDIF 

!IF "$(CFG)" != "VControl - Win32 Release" && "$(CFG)" !=\
 "VControl - Win32 Debug" && "$(CFG)" != "VControl - Win32 Unicode Debug" &&\
 "$(CFG)" != "VControl - Win32 Unicode Release"
!MESSAGE Invalid configuration "$(CFG)" specified.
!MESSAGE You can specify a configuration when running NMAKE on this makefile
!MESSAGE by defining the macro CFG on the command line.  For example:
!MESSAGE 
!MESSAGE NMAKE /f "VControl.mak" CFG="VControl - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "VControl - Win32 Release" (based on\
 "Win32 (x86) Dynamic-Link Library")
!MESSAGE "VControl - Win32 Debug" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE "VControl - Win32 Unicode Debug" (based on\
 "Win32 (x86) Dynamic-Link Library")
!MESSAGE "VControl - Win32 Unicode Release" (based on\
 "Win32 (x86) Dynamic-Link Library")
!MESSAGE 
!ERROR An invalid configuration is specified.
!ENDIF 

!IF "$(OS)" == "Windows_NT"
NULL=
!ELSE 
NULL=nul
!ENDIF 
################################################################################
# Begin Project
# PROP Target_Last_Scanned "VControl - Win32 Debug"
MTL=mktyplib.exe
RSC=rc.exe
CPP=cl.exe

!IF  "$(CFG)" == "VControl - Win32 Release"

# PROP BASE Use_MFC 2
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "Release"
# PROP BASE Intermediate_Dir "Release"
# PROP BASE Target_Dir ""
# PROP BASE Target_Ext "ocx"
# PROP Use_MFC 2
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "Release"
# PROP Intermediate_Dir "Release"
# PROP Target_Dir ""
# PROP Target_Ext "ocx"
OUTDIR=.\Release
INTDIR=.\Release
# Begin Custom Macros
OutDir=.\Release
# End Custom Macros

ALL : "$(OUTDIR)\VControl.ocx" "$(OUTDIR)\regsvr32.trg"

CLEAN : 
	-@erase ".\Release\VControl.lib"
	-@erase ".\Release\VControl.obj"
	-@erase ".\Release\VControl.pch"
	-@erase ".\Release\StdAfx.obj"
	-@erase ".\Release\ResltDlg.obj"
	-@erase ".\Release\VConPpg.obj"
	-@erase ".\Release\VConCtl.obj"
	-@erase ".\Release\VControl.res"
	-@erase ".\Release\VControl.tlb"
	-@erase ".\Release\VControl.exp"
	-@erase ".\Release\regsvr32.trg"
	-@erase ".\Release\VControl.ocx"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

# ADD BASE CPP /nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_WINDLL" /D "_AFXDLL" /D "_MBCS" /Yu"stdafx.h" /c
# ADD CPP /nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_WINDLL" /D "_AFXDLL" /D "_MBCS" /D "_USRDLL" /Yu"stdafx.h" /c
CPP_PROJ=/nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D\
 "_WINDLL" /D "_AFXDLL" /D "_MBCS" /D "_USRDLL" /Fp"$(INTDIR)/VControl.pch"\
 /Yu"stdafx.h" /Fo"$(INTDIR)/" /c 
CPP_OBJS=.\Release/
CPP_SBRS=
# ADD BASE MTL /nologo /D "NDEBUG" /win32
# ADD MTL /nologo /D "NDEBUG" /win32
MTL_PROJ=/nologo /D "NDEBUG" /win32 
# ADD BASE RSC /l 0x409 /d "NDEBUG" /d "_AFXDLL"
# ADD RSC /l 0x409 /d "NDEBUG" /d "_AFXDLL"
RSC_PROJ=/l 0x409 /fo"$(INTDIR)/VControl.res" /d "NDEBUG" /d "_AFXDLL" 
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
BSC32_FLAGS=/nologo /o"$(OUTDIR)/VControl.bsc" 
BSC32_SBRS=
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /dll /machine:I386
# ADD LINK32 /nologo /subsystem:windows /dll /machine:I386
LINK32_FLAGS=/nologo /subsystem:windows /dll /incremental:no\
 /pdb:"$(OUTDIR)/VControl.pdb" /machine:I386 /def:".\VControl.def"\
 /out:"$(OUTDIR)/VControl.ocx" /implib:"$(OUTDIR)/VControl.lib" 
DEF_FILE= \
	".\VControl.def"
LINK32_OBJS= \
	"$(INTDIR)/VControl.obj" \
	"$(INTDIR)/StdAfx.obj" \
	"$(INTDIR)/ResltDlg.obj" \
	"$(INTDIR)/VConPpg.obj" \
	"$(INTDIR)/VConCtl.obj" \
	"$(INTDIR)/VControl.res"

"$(OUTDIR)\VControl.ocx" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

# Begin Custom Build - Registering OLE control...
OutDir=.\Release
TargetPath=.\Release\VControl.ocx
InputPath=.\Release\VControl.ocx
SOURCE=$(InputPath)

"$(OutDir)\regsvr32.trg" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   regsvr32 /s /c "$(TargetPath)"
   echo regsvr32 exec. time > "$(OutDir)\regsvr32.trg"

# End Custom Build

!ELSEIF  "$(CFG)" == "VControl - Win32 Debug"

# PROP BASE Use_MFC 2
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "Debug"
# PROP BASE Intermediate_Dir "Debug"
# PROP BASE Target_Dir ""
# PROP BASE Target_Ext "ocx"
# PROP Use_MFC 2
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "Debug"
# PROP Intermediate_Dir "Debug"
# PROP Target_Dir ""
# PROP Target_Ext "ocx"
OUTDIR=.\Debug
INTDIR=.\Debug
# Begin Custom Macros
OutDir=.\Debug
# End Custom Macros

ALL : "$(OUTDIR)\VControl.ocx" "$(OUTDIR)\VControl.bsc"\
 "$(OUTDIR)\regsvr32.trg"

CLEAN : 
	-@erase ".\Debug\vc40.pdb"
	-@erase ".\Debug\VControl.pch"
	-@erase ".\Debug\vc40.idb"
	-@erase ".\Debug\VControl.bsc"
	-@erase ".\Debug\StdAfx.sbr"
	-@erase ".\Debug\ResltDlg.sbr"
	-@erase ".\Debug\VConPpg.sbr"
	-@erase ".\Debug\VConCtl.sbr"
	-@erase ".\Debug\VControl.sbr"
	-@erase ".\Debug\VControl.ilk"
	-@erase ".\Debug\VConCtl.obj"
	-@erase ".\Debug\VControl.obj"
	-@erase ".\Debug\StdAfx.obj"
	-@erase ".\Debug\ResltDlg.obj"
	-@erase ".\Debug\VConPpg.obj"
	-@erase ".\Debug\VControl.res"
	-@erase ".\Debug\VControl.tlb"
	-@erase ".\Debug\VControl.lib"
	-@erase ".\Debug\VControl.exp"
	-@erase ".\Debug\VControl.pdb"
	-@erase ".\Debug\regsvr32.trg"
	-@erase ".\Debug\VControl.ocx"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

# ADD BASE CPP /nologo /MDd /W3 /Gm /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_WINDLL" /D "_AFXDLL" /D "_MBCS" /Yu"stdafx.h" /c
# ADD CPP /nologo /MDd /W3 /Gm /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_WINDLL" /D "_AFXDLL" /D "_MBCS" /D "_USRDLL" /FR /Yu"stdafx.h" /c
CPP_PROJ=/nologo /MDd /W3 /Gm /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS"\
 /D "_WINDLL" /D "_AFXDLL" /D "_MBCS" /D "_USRDLL" /FR"$(INTDIR)/"\
 /Fp"$(INTDIR)/VControl.pch" /Yu"stdafx.h" /Fo"$(INTDIR)/" /Fd"$(INTDIR)/" /c 
CPP_OBJS=.\Debug/
CPP_SBRS=.\Debug/
# ADD BASE MTL /nologo /D "_DEBUG" /win32
# ADD MTL /nologo /D "_DEBUG" /win32
MTL_PROJ=/nologo /D "_DEBUG" /win32 
# ADD BASE RSC /l 0x409 /d "_DEBUG" /d "_AFXDLL"
# ADD RSC /l 0x409 /d "_DEBUG" /d "_AFXDLL"
RSC_PROJ=/l 0x409 /fo"$(INTDIR)/VControl.res" /d "_DEBUG" /d "_AFXDLL" 
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
BSC32_FLAGS=/nologo /o"$(OUTDIR)/VControl.bsc" 
BSC32_SBRS= \
	"$(INTDIR)/StdAfx.sbr" \
	"$(INTDIR)/ResltDlg.sbr" \
	"$(INTDIR)/VConPpg.sbr" \
	"$(INTDIR)/VConCtl.sbr" \
	"$(INTDIR)/VControl.sbr"

"$(OUTDIR)\VControl.bsc" : "$(OUTDIR)" $(BSC32_SBRS)
    $(BSC32) @<<
  $(BSC32_FLAGS) $(BSC32_SBRS)
<<

LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /dll /debug /machine:I386
# ADD LINK32 /nologo /subsystem:windows /dll /debug /machine:I386
LINK32_FLAGS=/nologo /subsystem:windows /dll /incremental:yes\
 /pdb:"$(OUTDIR)/VControl.pdb" /debug /machine:I386 /def:".\VControl.def"\
 /out:"$(OUTDIR)/VControl.ocx" /implib:"$(OUTDIR)/VControl.lib" 
DEF_FILE= \
	".\VControl.def"
LINK32_OBJS= \
	"$(INTDIR)/VConCtl.obj" \
	"$(INTDIR)/VControl.obj" \
	"$(INTDIR)/StdAfx.obj" \
	"$(INTDIR)/ResltDlg.obj" \
	"$(INTDIR)/VConPpg.obj" \
	"$(INTDIR)/VControl.res"

"$(OUTDIR)\VControl.ocx" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

# Begin Custom Build - Registering OLE control...
OutDir=.\Debug
TargetPath=.\Debug\VControl.ocx
InputPath=.\Debug\VControl.ocx
SOURCE=$(InputPath)

"$(OutDir)\regsvr32.trg" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   regsvr32 /s /c "$(TargetPath)"
   echo regsvr32 exec. time > "$(OutDir)\regsvr32.trg"

# End Custom Build

!ELSEIF  "$(CFG)" == "VControl - Win32 Unicode Debug"

# PROP BASE Use_MFC 2
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "DebugU"
# PROP BASE Intermediate_Dir "DebugU"
# PROP BASE Target_Dir ""
# PROP BASE Target_Ext "ocx"
# PROP Use_MFC 2
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "DebugU"
# PROP Intermediate_Dir "DebugU"
# PROP Target_Dir ""
# PROP Target_Ext "ocx"
OUTDIR=.\DebugU
INTDIR=.\DebugU
# Begin Custom Macros
OutDir=.\DebugU
# End Custom Macros

ALL : "$(OUTDIR)\VControl.ocx" "$(OUTDIR)\regsvr32.trg"

CLEAN : 
	-@erase ".\DebugU\vc40.pdb"
	-@erase ".\DebugU\VControl.pch"
	-@erase ".\DebugU\vc40.idb"
	-@erase ".\DebugU\VControl.ilk"
	-@erase ".\DebugU\ResltDlg.obj"
	-@erase ".\DebugU\StdAfx.obj"
	-@erase ".\DebugU\VConPpg.obj"
	-@erase ".\DebugU\VConCtl.obj"
	-@erase ".\DebugU\VControl.obj"
	-@erase ".\DebugU\VControl.res"
	-@erase ".\DebugU\VControl.tlb"
	-@erase ".\DebugU\VControl.lib"
	-@erase ".\DebugU\VControl.exp"
	-@erase ".\DebugU\VControl.pdb"
	-@erase ".\DebugU\regsvr32.trg"
	-@erase ".\DebugU\VControl.ocx"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

# ADD BASE CPP /nologo /MDd /W3 /Gm /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_WINDLL" /D "_AFXDLL" /D "_MBCS" /D "_USRDLL" /Yu"stdafx.h" /c
# ADD CPP /nologo /MDd /W3 /Gm /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_WINDLL" /D "_AFXDLL" /D "_USRDLL" /D "_UNICODE" /Yu"stdafx.h" /c
CPP_PROJ=/nologo /MDd /W3 /Gm /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS"\
 /D "_WINDLL" /D "_AFXDLL" /D "_USRDLL" /D "_UNICODE"\
 /Fp"$(INTDIR)/VControl.pch" /Yu"stdafx.h" /Fo"$(INTDIR)/" /Fd"$(INTDIR)/" /c 
CPP_OBJS=.\DebugU/
CPP_SBRS=
# ADD BASE MTL /nologo /D "_DEBUG" /win32
# ADD MTL /nologo /D "_DEBUG" /win32
MTL_PROJ=/nologo /D "_DEBUG" /win32 
# ADD BASE RSC /l 0x409 /d "_DEBUG" /d "_AFXDLL"
# ADD RSC /l 0x409 /d "_DEBUG" /d "_AFXDLL"
RSC_PROJ=/l 0x409 /fo"$(INTDIR)/VControl.res" /d "_DEBUG" /d "_AFXDLL" 
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
BSC32_FLAGS=/nologo /o"$(OUTDIR)/VControl.bsc" 
BSC32_SBRS=
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /dll /debug /machine:I386
# ADD LINK32 /nologo /subsystem:windows /dll /debug /machine:I386
LINK32_FLAGS=/nologo /subsystem:windows /dll /incremental:yes\
 /pdb:"$(OUTDIR)/VControl.pdb" /debug /machine:I386 /def:".\VControl.def"\
 /out:"$(OUTDIR)/VControl.ocx" /implib:"$(OUTDIR)/VControl.lib" 
DEF_FILE= \
	".\VControl.def"
LINK32_OBJS= \
	"$(INTDIR)/ResltDlg.obj" \
	"$(INTDIR)/StdAfx.obj" \
	"$(INTDIR)/VConPpg.obj" \
	"$(INTDIR)/VConCtl.obj" \
	"$(INTDIR)/VControl.obj" \
	"$(INTDIR)/VControl.res"

"$(OUTDIR)\VControl.ocx" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

# Begin Custom Build - Registering OLE control...
OutDir=.\DebugU
TargetPath=.\DebugU\VControl.ocx
InputPath=.\DebugU\VControl.ocx
SOURCE=$(InputPath)

"$(OutDir)\regsvr32.trg" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   regsvr32 /s /c "$(TargetPath)"
   echo regsvr32 exec. time > "$(OutDir)\regsvr32.trg"

# End Custom Build

!ELSEIF  "$(CFG)" == "VControl - Win32 Unicode Release"

# PROP BASE Use_MFC 2
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "ReleaseU"
# PROP BASE Intermediate_Dir "ReleaseU"
# PROP BASE Target_Dir ""
# PROP BASE Target_Ext "ocx"
# PROP Use_MFC 2
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "ReleaseU"
# PROP Intermediate_Dir "ReleaseU"
# PROP Target_Dir ""
# PROP Target_Ext "ocx"
OUTDIR=.\ReleaseU
INTDIR=.\ReleaseU
# Begin Custom Macros
OutDir=.\ReleaseU
# End Custom Macros

ALL : "$(OUTDIR)\VControl.ocx" "$(OUTDIR)\regsvr32.trg"

CLEAN : 
	-@erase ".\ReleaseU\VControl.lib"
	-@erase ".\ReleaseU\VControl.obj"
	-@erase ".\ReleaseU\VControl.pch"
	-@erase ".\ReleaseU\VConPpg.obj"
	-@erase ".\ReleaseU\VConCtl.obj"
	-@erase ".\ReleaseU\StdAfx.obj"
	-@erase ".\ReleaseU\ResltDlg.obj"
	-@erase ".\ReleaseU\VControl.res"
	-@erase ".\ReleaseU\VControl.tlb"
	-@erase ".\ReleaseU\VControl.exp"
	-@erase ".\ReleaseU\regsvr32.trg"
	-@erase ".\ReleaseU\VControl.ocx"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

# ADD BASE CPP /nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_WINDLL" /D "_AFXDLL" /D "_MBCS" /D "_USRDLL" /Yu"stdafx.h" /c
# ADD CPP /nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_WINDLL" /D "_AFXDLL" /D "_USRDLL" /D "_UNICODE" /Yu"stdafx.h" /c
CPP_PROJ=/nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D\
 "_WINDLL" /D "_AFXDLL" /D "_USRDLL" /D "_UNICODE" /Fp"$(INTDIR)/VControl.pch"\
 /Yu"stdafx.h" /Fo"$(INTDIR)/" /c 
CPP_OBJS=.\ReleaseU/
CPP_SBRS=
# ADD BASE MTL /nologo /D "NDEBUG" /win32
# ADD MTL /nologo /D "NDEBUG" /win32
MTL_PROJ=/nologo /D "NDEBUG" /win32 
# ADD BASE RSC /l 0x409 /d "NDEBUG" /d "_AFXDLL"
# ADD RSC /l 0x409 /d "NDEBUG" /d "_AFXDLL"
RSC_PROJ=/l 0x409 /fo"$(INTDIR)/VControl.res" /d "NDEBUG" /d "_AFXDLL" 
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
BSC32_FLAGS=/nologo /o"$(OUTDIR)/VControl.bsc" 
BSC32_SBRS=
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /dll /machine:I386
# ADD LINK32 /nologo /subsystem:windows /dll /machine:I386
LINK32_FLAGS=/nologo /subsystem:windows /dll /incremental:no\
 /pdb:"$(OUTDIR)/VControl.pdb" /machine:I386 /def:".\VControl.def"\
 /out:"$(OUTDIR)/VControl.ocx" /implib:"$(OUTDIR)/VControl.lib" 
DEF_FILE= \
	".\VControl.def"
LINK32_OBJS= \
	"$(INTDIR)/VControl.obj" \
	"$(INTDIR)/VConPpg.obj" \
	"$(INTDIR)/VConCtl.obj" \
	"$(INTDIR)/StdAfx.obj" \
	"$(INTDIR)/ResltDlg.obj" \
	"$(INTDIR)/VControl.res"

"$(OUTDIR)\VControl.ocx" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

# Begin Custom Build - Registering OLE control...
OutDir=.\ReleaseU
TargetPath=.\ReleaseU\VControl.ocx
InputPath=.\ReleaseU\VControl.ocx
SOURCE=$(InputPath)

"$(OutDir)\regsvr32.trg" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   regsvr32 /s /c "$(TargetPath)"
   echo regsvr32 exec. time > "$(OutDir)\regsvr32.trg"

# End Custom Build

!ENDIF 

.c{$(CPP_OBJS)}.obj:
   $(CPP) $(CPP_PROJ) $<  

.cpp{$(CPP_OBJS)}.obj:
   $(CPP) $(CPP_PROJ) $<  

.cxx{$(CPP_OBJS)}.obj:
   $(CPP) $(CPP_PROJ) $<  

.c{$(CPP_SBRS)}.sbr:
   $(CPP) $(CPP_PROJ) $<  

.cpp{$(CPP_SBRS)}.sbr:
   $(CPP) $(CPP_PROJ) $<  

.cxx{$(CPP_SBRS)}.sbr:
   $(CPP) $(CPP_PROJ) $<  

################################################################################
# Begin Target

# Name "VControl - Win32 Release"
# Name "VControl - Win32 Debug"
# Name "VControl - Win32 Unicode Debug"
# Name "VControl - Win32 Unicode Release"

!IF  "$(CFG)" == "VControl - Win32 Release"

!ELSEIF  "$(CFG)" == "VControl - Win32 Debug"

!ELSEIF  "$(CFG)" == "VControl - Win32 Unicode Debug"

!ELSEIF  "$(CFG)" == "VControl - Win32 Unicode Release"

!ENDIF 

################################################################################
# Begin Source File

SOURCE=.\StdAfx.cpp
DEP_CPP_STDAF=\
	".\StdAfx.h"\
	

!IF  "$(CFG)" == "VControl - Win32 Release"

# ADD CPP /Yc"stdafx.h"

BuildCmds= \
	$(CPP) /nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D\
 "_WINDLL" /D "_AFXDLL" /D "_MBCS" /D "_USRDLL" /Fp"$(INTDIR)/VControl.pch"\
 /Yc"stdafx.h" /Fo"$(INTDIR)/" /c $(SOURCE) \
	

"$(INTDIR)\StdAfx.obj" : $(SOURCE) $(DEP_CPP_STDAF) "$(INTDIR)"
   $(BuildCmds)

"$(INTDIR)\VControl.pch" : $(SOURCE) $(DEP_CPP_STDAF) "$(INTDIR)"
   $(BuildCmds)

!ELSEIF  "$(CFG)" == "VControl - Win32 Debug"

# ADD CPP /Yc"stdafx.h"

BuildCmds= \
	$(CPP) /nologo /MDd /W3 /Gm /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS"\
 /D "_WINDLL" /D "_AFXDLL" /D "_MBCS" /D "_USRDLL" /FR"$(INTDIR)/"\
 /Fp"$(INTDIR)/VControl.pch" /Yc"stdafx.h" /Fo"$(INTDIR)/" /Fd"$(INTDIR)/" /c\
 $(SOURCE) \
	

"$(INTDIR)\StdAfx.obj" : $(SOURCE) $(DEP_CPP_STDAF) "$(INTDIR)"
   $(BuildCmds)

"$(INTDIR)\StdAfx.sbr" : $(SOURCE) $(DEP_CPP_STDAF) "$(INTDIR)"
   $(BuildCmds)

"$(INTDIR)\VControl.pch" : $(SOURCE) $(DEP_CPP_STDAF) "$(INTDIR)"
   $(BuildCmds)

!ELSEIF  "$(CFG)" == "VControl - Win32 Unicode Debug"

# ADD BASE CPP /Yc"stdafx.h"
# ADD CPP /Yc"stdafx.h"

BuildCmds= \
	$(CPP) /nologo /MDd /W3 /Gm /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS"\
 /D "_WINDLL" /D "_AFXDLL" /D "_USRDLL" /D "_UNICODE"\
 /Fp"$(INTDIR)/VControl.pch" /Yc"stdafx.h" /Fo"$(INTDIR)/" /Fd"$(INTDIR)/" /c\
 $(SOURCE) \
	

"$(INTDIR)\StdAfx.obj" : $(SOURCE) $(DEP_CPP_STDAF) "$(INTDIR)"
   $(BuildCmds)

"$(INTDIR)\VControl.pch" : $(SOURCE) $(DEP_CPP_STDAF) "$(INTDIR)"
   $(BuildCmds)

!ELSEIF  "$(CFG)" == "VControl - Win32 Unicode Release"

# ADD BASE CPP /Yc"stdafx.h"
# ADD CPP /Yc"stdafx.h"

BuildCmds= \
	$(CPP) /nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D\
 "_WINDLL" /D "_AFXDLL" /D "_USRDLL" /D "_UNICODE" /Fp"$(INTDIR)/VControl.pch"\
 /Yc"stdafx.h" /Fo"$(INTDIR)/" /c $(SOURCE) \
	

"$(INTDIR)\StdAfx.obj" : $(SOURCE) $(DEP_CPP_STDAF) "$(INTDIR)"
   $(BuildCmds)

"$(INTDIR)\VControl.pch" : $(SOURCE) $(DEP_CPP_STDAF) "$(INTDIR)"
   $(BuildCmds)

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\VControl.cpp
DEP_CPP_VCONT=\
	".\StdAfx.h"\
	".\VControl.h"\
	

!IF  "$(CFG)" == "VControl - Win32 Release"


"$(INTDIR)\VControl.obj" : $(SOURCE) $(DEP_CPP_VCONT) "$(INTDIR)"\
 "$(INTDIR)\VControl.pch"


!ELSEIF  "$(CFG)" == "VControl - Win32 Debug"


"$(INTDIR)\VControl.obj" : $(SOURCE) $(DEP_CPP_VCONT) "$(INTDIR)"\
 "$(INTDIR)\VControl.pch"

"$(INTDIR)\VControl.sbr" : $(SOURCE) $(DEP_CPP_VCONT) "$(INTDIR)"\
 "$(INTDIR)\VControl.pch"


!ELSEIF  "$(CFG)" == "VControl - Win32 Unicode Debug"


"$(INTDIR)\VControl.obj" : $(SOURCE) $(DEP_CPP_VCONT) "$(INTDIR)"\
 "$(INTDIR)\VControl.pch"


!ELSEIF  "$(CFG)" == "VControl - Win32 Unicode Release"


"$(INTDIR)\VControl.obj" : $(SOURCE) $(DEP_CPP_VCONT) "$(INTDIR)"\
 "$(INTDIR)\VControl.pch"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\VControl.def

!IF  "$(CFG)" == "VControl - Win32 Release"

!ELSEIF  "$(CFG)" == "VControl - Win32 Debug"

!ELSEIF  "$(CFG)" == "VControl - Win32 Unicode Debug"

!ELSEIF  "$(CFG)" == "VControl - Win32 Unicode Release"

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\VControl.rc

!IF  "$(CFG)" == "VControl - Win32 Release"

DEP_RSC_VCONTR=\
	".\VControl.ico"\
	".\VControl.bmp"\
	".\Release\VControl.tlb"\
	

"$(INTDIR)\VControl.res" : $(SOURCE) $(DEP_RSC_VCONTR) "$(INTDIR)"\
 "$(INTDIR)\VControl.tlb"
   $(RSC) /l 0x409 /fo"$(INTDIR)/VControl.res" /i "Release" /d "NDEBUG" /d\
 "_AFXDLL" $(SOURCE)


!ELSEIF  "$(CFG)" == "VControl - Win32 Debug"

DEP_RSC_VCONTR=\
	".\VControl.ico"\
	".\VControl.bmp"\
	".\Debug\VControl.tlb"\
	

"$(INTDIR)\VControl.res" : $(SOURCE) $(DEP_RSC_VCONTR) "$(INTDIR)"\
 "$(INTDIR)\VControl.tlb"
   $(RSC) /l 0x409 /fo"$(INTDIR)/VControl.res" /i "Debug" /d "_DEBUG" /d\
 "_AFXDLL" $(SOURCE)


!ELSEIF  "$(CFG)" == "VControl - Win32 Unicode Debug"

DEP_RSC_VCONTR=\
	".\VControl.ico"\
	".\VControl.bmp"\
	
NODEP_RSC_VCONTR=\
	".\DebugU\VControl.tlb"\
	

"$(INTDIR)\VControl.res" : $(SOURCE) $(DEP_RSC_VCONTR) "$(INTDIR)"\
 "$(INTDIR)\VControl.tlb"
   $(RSC) /l 0x409 /fo"$(INTDIR)/VControl.res" /i "DebugU" /d "_DEBUG" /d\
 "_AFXDLL" $(SOURCE)


!ELSEIF  "$(CFG)" == "VControl - Win32 Unicode Release"

DEP_RSC_VCONTR=\
	".\VControl.ico"\
	".\VControl.bmp"\
	
NODEP_RSC_VCONTR=\
	".\ReleaseU\VControl.tlb"\
	

"$(INTDIR)\VControl.res" : $(SOURCE) $(DEP_RSC_VCONTR) "$(INTDIR)"\
 "$(INTDIR)\VControl.tlb"
   $(RSC) /l 0x409 /fo"$(INTDIR)/VControl.res" /i "ReleaseU" /d "NDEBUG" /d\
 "_AFXDLL" $(SOURCE)


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\VControl.odl

!IF  "$(CFG)" == "VControl - Win32 Release"


"$(OUTDIR)\VControl.tlb" : $(SOURCE) "$(OUTDIR)"
   $(MTL) /nologo /D "NDEBUG" /tlb "$(OUTDIR)/VControl.tlb" /win32 $(SOURCE)


!ELSEIF  "$(CFG)" == "VControl - Win32 Debug"


"$(OUTDIR)\VControl.tlb" : $(SOURCE) "$(OUTDIR)"
   $(MTL) /nologo /D "_DEBUG" /tlb "$(OUTDIR)/VControl.tlb" /win32 $(SOURCE)


!ELSEIF  "$(CFG)" == "VControl - Win32 Unicode Debug"


"$(OUTDIR)\VControl.tlb" : $(SOURCE) "$(OUTDIR)"
   $(MTL) /nologo /D "_DEBUG" /tlb "$(OUTDIR)/VControl.tlb" /win32 $(SOURCE)


!ELSEIF  "$(CFG)" == "VControl - Win32 Unicode Release"


"$(OUTDIR)\VControl.tlb" : $(SOURCE) "$(OUTDIR)"
   $(MTL) /nologo /D "NDEBUG" /tlb "$(OUTDIR)/VControl.tlb" /win32 $(SOURCE)


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\VConCtl.cpp

!IF  "$(CFG)" == "VControl - Win32 Release"

DEP_CPP_VCONC=\
	".\StdAfx.h"\
	".\VControl.h"\
	".\VConCtl.h"\
	".\VConPpg.h"\
	".\ResltDlg.h"\
	
NODEP_CPP_VCONC=\
	".\m_verifyMe"\
	

"$(INTDIR)\VConCtl.obj" : $(SOURCE) $(DEP_CPP_VCONC) "$(INTDIR)"\
 "$(INTDIR)\VControl.pch"


!ELSEIF  "$(CFG)" == "VControl - Win32 Debug"

DEP_CPP_VCONC=\
	".\StdAfx.h"\
	".\VControl.h"\
	".\VConCtl.h"\
	".\VConPpg.h"\
	".\ResltDlg.h"\
	

"$(INTDIR)\VConCtl.obj" : $(SOURCE) $(DEP_CPP_VCONC) "$(INTDIR)"\
 "$(INTDIR)\VControl.pch"

"$(INTDIR)\VConCtl.sbr" : $(SOURCE) $(DEP_CPP_VCONC) "$(INTDIR)"\
 "$(INTDIR)\VControl.pch"


!ELSEIF  "$(CFG)" == "VControl - Win32 Unicode Debug"

DEP_CPP_VCONC=\
	".\StdAfx.h"\
	".\VControl.h"\
	".\VConCtl.h"\
	".\VConPpg.h"\
	".\ResltDlg.h"\
	

"$(INTDIR)\VConCtl.obj" : $(SOURCE) $(DEP_CPP_VCONC) "$(INTDIR)"\
 "$(INTDIR)\VControl.pch"


!ELSEIF  "$(CFG)" == "VControl - Win32 Unicode Release"

DEP_CPP_VCONC=\
	".\StdAfx.h"\
	".\VControl.h"\
	".\VConCtl.h"\
	".\VConPpg.h"\
	".\ResltDlg.h"\
	

"$(INTDIR)\VConCtl.obj" : $(SOURCE) $(DEP_CPP_VCONC) "$(INTDIR)"\
 "$(INTDIR)\VControl.pch"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\VConPpg.cpp
DEP_CPP_VCONP=\
	".\StdAfx.h"\
	".\VControl.h"\
	".\VConPpg.h"\
	

!IF  "$(CFG)" == "VControl - Win32 Release"


"$(INTDIR)\VConPpg.obj" : $(SOURCE) $(DEP_CPP_VCONP) "$(INTDIR)"\
 "$(INTDIR)\VControl.pch"


!ELSEIF  "$(CFG)" == "VControl - Win32 Debug"


"$(INTDIR)\VConPpg.obj" : $(SOURCE) $(DEP_CPP_VCONP) "$(INTDIR)"\
 "$(INTDIR)\VControl.pch"

"$(INTDIR)\VConPpg.sbr" : $(SOURCE) $(DEP_CPP_VCONP) "$(INTDIR)"\
 "$(INTDIR)\VControl.pch"


!ELSEIF  "$(CFG)" == "VControl - Win32 Unicode Debug"


"$(INTDIR)\VConPpg.obj" : $(SOURCE) $(DEP_CPP_VCONP) "$(INTDIR)"\
 "$(INTDIR)\VControl.pch"


!ELSEIF  "$(CFG)" == "VControl - Win32 Unicode Release"


"$(INTDIR)\VConPpg.obj" : $(SOURCE) $(DEP_CPP_VCONP) "$(INTDIR)"\
 "$(INTDIR)\VControl.pch"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\ResltDlg.cpp
DEP_CPP_RESLT=\
	".\StdAfx.h"\
	".\VControl.h"\
	".\VConCtl.h"\
	".\ResltDlg.h"\
	

!IF  "$(CFG)" == "VControl - Win32 Release"


"$(INTDIR)\ResltDlg.obj" : $(SOURCE) $(DEP_CPP_RESLT) "$(INTDIR)"\
 "$(INTDIR)\VControl.pch"


!ELSEIF  "$(CFG)" == "VControl - Win32 Debug"


"$(INTDIR)\ResltDlg.obj" : $(SOURCE) $(DEP_CPP_RESLT) "$(INTDIR)"\
 "$(INTDIR)\VControl.pch"

"$(INTDIR)\ResltDlg.sbr" : $(SOURCE) $(DEP_CPP_RESLT) "$(INTDIR)"\
 "$(INTDIR)\VControl.pch"


!ELSEIF  "$(CFG)" == "VControl - Win32 Unicode Debug"


"$(INTDIR)\ResltDlg.obj" : $(SOURCE) $(DEP_CPP_RESLT) "$(INTDIR)"\
 "$(INTDIR)\VControl.pch"


!ELSEIF  "$(CFG)" == "VControl - Win32 Unicode Release"


"$(INTDIR)\ResltDlg.obj" : $(SOURCE) $(DEP_CPP_RESLT) "$(INTDIR)"\
 "$(INTDIR)\VControl.pch"


!ENDIF 

# End Source File
# End Target
# End Project
################################################################################
