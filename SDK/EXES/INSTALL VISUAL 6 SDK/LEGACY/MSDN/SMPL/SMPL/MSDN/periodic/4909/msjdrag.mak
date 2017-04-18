# Microsoft Developer Studio Generated NMAKE File, Format Version 4.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Dynamic-Link Library" 0x0102

!IF "$(CFG)" == ""
CFG=msjdrag - Win32 Debug
!MESSAGE No configuration specified.  Defaulting to msjdrag - Win32 Debug.
!ENDIF 

!IF "$(CFG)" != "msjdrag - Win32 Release" && "$(CFG)" !=\
 "msjdrag - Win32 Debug" && "$(CFG)" != "msjdrag - Win32 Unicode Debug" &&\
 "$(CFG)" != "msjdrag - Win32 Unicode Release"
!MESSAGE Invalid configuration "$(CFG)" specified.
!MESSAGE You can specify a configuration when running NMAKE on this makefile
!MESSAGE by defining the macro CFG on the command line.  For example:
!MESSAGE 
!MESSAGE NMAKE /f "msjdrag.mak" CFG="msjdrag - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "msjdrag - Win32 Release" (based on\
 "Win32 (x86) Dynamic-Link Library")
!MESSAGE "msjdrag - Win32 Debug" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE "msjdrag - Win32 Unicode Debug" (based on\
 "Win32 (x86) Dynamic-Link Library")
!MESSAGE "msjdrag - Win32 Unicode Release" (based on\
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
# PROP Target_Last_Scanned "msjdrag - Win32 Debug"
CPP=cl.exe
MTL=mktyplib.exe
RSC=rc.exe

!IF  "$(CFG)" == "msjdrag - Win32 Release"

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

ALL : "$(OUTDIR)\msjdrag.ocx" "$(OUTDIR)\regsvr32.trg"

CLEAN : 
	-@erase ".\Release\msjdrag.lib"
	-@erase ".\Release\msjdrag.obj"
	-@erase ".\Release\msjdrag.pch"
	-@erase ".\Release\StdAfx.obj"
	-@erase ".\Release\MSJDragPpg.obj"
	-@erase ".\Release\MSJDragCtl.obj"
	-@erase ".\Release\msjdrag.res"
	-@erase ".\Release\msjdrag.tlb"
	-@erase ".\Release\VBFrWnd.obj"
	-@erase ".\Release\msjdrag.exp"
	-@erase ".\Release\regsvr32.trg"
	-@erase ".\Release\msjdrag.ocx"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

# ADD BASE CPP /nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_WINDLL" /D "_AFXDLL" /D "_MBCS" /Yu"stdafx.h" /c
# ADD CPP /nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_WINDLL" /D "_AFXDLL" /D "_MBCS" /D "_USRDLL" /Yu"stdafx.h" /c
CPP_PROJ=/nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D\
 "_WINDLL" /D "_AFXDLL" /D "_MBCS" /D "_USRDLL" /Fp"$(INTDIR)/msjdrag.pch"\
 /Yu"stdafx.h" /Fo"$(INTDIR)/" /c 
CPP_OBJS=.\Release/
CPP_SBRS=
# ADD BASE MTL /nologo /D "NDEBUG" /win32
# ADD MTL /nologo /D "NDEBUG" /win32
MTL_PROJ=/nologo /D "NDEBUG" /win32 
# ADD BASE RSC /l 0x409 /d "NDEBUG" /d "_AFXDLL"
# ADD RSC /l 0x409 /d "NDEBUG" /d "_AFXDLL"
RSC_PROJ=/l 0x409 /fo"$(INTDIR)/msjdrag.res" /d "NDEBUG" /d "_AFXDLL" 
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
BSC32_FLAGS=/nologo /o"$(OUTDIR)/msjdrag.bsc" 
BSC32_SBRS=
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /dll /machine:I386
# ADD LINK32 /nologo /subsystem:windows /dll /machine:I386
LINK32_FLAGS=/nologo /subsystem:windows /dll /incremental:no\
 /pdb:"$(OUTDIR)/msjdrag.pdb" /machine:I386 /def:".\msjdrag.def"\
 /out:"$(OUTDIR)/msjdrag.ocx" /implib:"$(OUTDIR)/msjdrag.lib" 
DEF_FILE= \
	".\msjdrag.def"
LINK32_OBJS= \
	"$(INTDIR)/msjdrag.obj" \
	"$(INTDIR)/StdAfx.obj" \
	"$(INTDIR)/MSJDragPpg.obj" \
	"$(INTDIR)/MSJDragCtl.obj" \
	"$(INTDIR)/VBFrWnd.obj" \
	"$(INTDIR)/msjdrag.res"

"$(OUTDIR)\msjdrag.ocx" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

# Begin Custom Build - Registering OLE control...
OutDir=.\Release
TargetPath=.\Release\msjdrag.ocx
InputPath=.\Release\msjdrag.ocx
SOURCE=$(InputPath)

"$(OutDir)\regsvr32.trg" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   regsvr32 /s /c "$(TargetPath)"
   echo regsvr32 exec. time > "$(OutDir)\regsvr32.trg"

# End Custom Build

!ELSEIF  "$(CFG)" == "msjdrag - Win32 Debug"

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

ALL : "$(OUTDIR)\msjdrag.ocx" "$(OUTDIR)\msjdrag.bsc" "$(OUTDIR)\regsvr32.trg"

CLEAN : 
	-@erase ".\Debug\vc40.pdb"
	-@erase ".\Debug\msjdrag.pch"
	-@erase ".\Debug\vc40.idb"
	-@erase ".\Debug\msjdrag.bsc"
	-@erase ".\Debug\MSJDragPpg.sbr"
	-@erase ".\Debug\StdAfx.sbr"
	-@erase ".\Debug\MSJDragCtl.sbr"
	-@erase ".\Debug\msjdrag.sbr"
	-@erase ".\Debug\VBFrWnd.sbr"
	-@erase ".\Debug\msjdrag.ilk"
	-@erase ".\Debug\MSJDragPpg.obj"
	-@erase ".\Debug\StdAfx.obj"
	-@erase ".\Debug\MSJDragCtl.obj"
	-@erase ".\Debug\msjdrag.obj"
	-@erase ".\Debug\msjdrag.res"
	-@erase ".\Debug\msjdrag.tlb"
	-@erase ".\Debug\VBFrWnd.obj"
	-@erase ".\Debug\msjdrag.lib"
	-@erase ".\Debug\msjdrag.exp"
	-@erase ".\Debug\msjdrag.pdb"
	-@erase ".\Debug\regsvr32.trg"
	-@erase ".\Debug\msjdrag.ocx"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

# ADD BASE CPP /nologo /MDd /W3 /Gm /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_WINDLL" /D "_AFXDLL" /D "_MBCS" /Yu"stdafx.h" /c
# ADD CPP /nologo /MDd /W3 /Gm /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_WINDLL" /D "_AFXDLL" /D "_MBCS" /D "_USRDLL" /FR /Yu"stdafx.h" /c
CPP_PROJ=/nologo /MDd /W3 /Gm /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS"\
 /D "_WINDLL" /D "_AFXDLL" /D "_MBCS" /D "_USRDLL" /FR"$(INTDIR)/"\
 /Fp"$(INTDIR)/msjdrag.pch" /Yu"stdafx.h" /Fo"$(INTDIR)/" /Fd"$(INTDIR)/" /c 
CPP_OBJS=.\Debug/
CPP_SBRS=.\Debug/
# ADD BASE MTL /nologo /D "_DEBUG" /win32
# ADD MTL /nologo /D "_DEBUG" /win32
MTL_PROJ=/nologo /D "_DEBUG" /win32 
# ADD BASE RSC /l 0x409 /d "_DEBUG" /d "_AFXDLL"
# ADD RSC /l 0x409 /d "_DEBUG" /d "_AFXDLL"
RSC_PROJ=/l 0x409 /fo"$(INTDIR)/msjdrag.res" /d "_DEBUG" /d "_AFXDLL" 
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
BSC32_FLAGS=/nologo /o"$(OUTDIR)/msjdrag.bsc" 
BSC32_SBRS= \
	"$(INTDIR)/MSJDragPpg.sbr" \
	"$(INTDIR)/StdAfx.sbr" \
	"$(INTDIR)/MSJDragCtl.sbr" \
	"$(INTDIR)/msjdrag.sbr" \
	"$(INTDIR)/VBFrWnd.sbr"

"$(OUTDIR)\msjdrag.bsc" : "$(OUTDIR)" $(BSC32_SBRS)
    $(BSC32) @<<
  $(BSC32_FLAGS) $(BSC32_SBRS)
<<

LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /dll /debug /machine:I386
# ADD LINK32 /nologo /subsystem:windows /dll /debug /machine:I386
LINK32_FLAGS=/nologo /subsystem:windows /dll /incremental:yes\
 /pdb:"$(OUTDIR)/msjdrag.pdb" /debug /machine:I386 /def:".\msjdrag.def"\
 /out:"$(OUTDIR)/msjdrag.ocx" /implib:"$(OUTDIR)/msjdrag.lib" 
DEF_FILE= \
	".\msjdrag.def"
LINK32_OBJS= \
	"$(INTDIR)/MSJDragPpg.obj" \
	"$(INTDIR)/StdAfx.obj" \
	"$(INTDIR)/MSJDragCtl.obj" \
	"$(INTDIR)/msjdrag.obj" \
	"$(INTDIR)/VBFrWnd.obj" \
	"$(INTDIR)/msjdrag.res"

"$(OUTDIR)\msjdrag.ocx" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

# Begin Custom Build - Registering OLE control...
OutDir=.\Debug
TargetPath=.\Debug\msjdrag.ocx
InputPath=.\Debug\msjdrag.ocx
SOURCE=$(InputPath)

"$(OutDir)\regsvr32.trg" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   regsvr32 /s /c "$(TargetPath)"
   echo regsvr32 exec. time > "$(OutDir)\regsvr32.trg"

# End Custom Build

!ELSEIF  "$(CFG)" == "msjdrag - Win32 Unicode Debug"

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

ALL : "$(OUTDIR)\msjdrag.ocx" "$(OUTDIR)\regsvr32.trg"

CLEAN : 
	-@erase ".\DebugU\vc40.pdb"
	-@erase ".\DebugU\msjdrag.pch"
	-@erase ".\DebugU\vc40.idb"
	-@erase ".\DebugU\msjdrag.ilk"
	-@erase ".\DebugU\msjdrag.obj"
	-@erase ".\DebugU\MSJDragPpg.obj"
	-@erase ".\DebugU\MSJDragCtl.obj"
	-@erase ".\DebugU\StdAfx.obj"
	-@erase ".\DebugU\msjdrag.res"
	-@erase ".\DebugU\msjdrag.tlb"
	-@erase ".\DebugU\VBFrWnd.obj"
	-@erase ".\DebugU\msjdrag.lib"
	-@erase ".\DebugU\msjdrag.exp"
	-@erase ".\DebugU\msjdrag.pdb"
	-@erase ".\DebugU\regsvr32.trg"
	-@erase ".\DebugU\msjdrag.ocx"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

# ADD BASE CPP /nologo /MDd /W3 /Gm /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_WINDLL" /D "_AFXDLL" /D "_MBCS" /D "_USRDLL" /Yu"stdafx.h" /c
# ADD CPP /nologo /MDd /W3 /Gm /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_WINDLL" /D "_AFXDLL" /D "_USRDLL" /D "_UNICODE" /Yu"stdafx.h" /c
CPP_PROJ=/nologo /MDd /W3 /Gm /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS"\
 /D "_WINDLL" /D "_AFXDLL" /D "_USRDLL" /D "_UNICODE" /Fp"$(INTDIR)/msjdrag.pch"\
 /Yu"stdafx.h" /Fo"$(INTDIR)/" /Fd"$(INTDIR)/" /c 
CPP_OBJS=.\DebugU/
CPP_SBRS=
# ADD BASE MTL /nologo /D "_DEBUG" /win32
# ADD MTL /nologo /D "_DEBUG" /win32
MTL_PROJ=/nologo /D "_DEBUG" /win32 
# ADD BASE RSC /l 0x409 /d "_DEBUG" /d "_AFXDLL"
# ADD RSC /l 0x409 /d "_DEBUG" /d "_AFXDLL"
RSC_PROJ=/l 0x409 /fo"$(INTDIR)/msjdrag.res" /d "_DEBUG" /d "_AFXDLL" 
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
BSC32_FLAGS=/nologo /o"$(OUTDIR)/msjdrag.bsc" 
BSC32_SBRS=
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /dll /debug /machine:I386
# ADD LINK32 /nologo /subsystem:windows /dll /debug /machine:I386
LINK32_FLAGS=/nologo /subsystem:windows /dll /incremental:yes\
 /pdb:"$(OUTDIR)/msjdrag.pdb" /debug /machine:I386 /def:".\msjdrag.def"\
 /out:"$(OUTDIR)/msjdrag.ocx" /implib:"$(OUTDIR)/msjdrag.lib" 
DEF_FILE= \
	".\msjdrag.def"
LINK32_OBJS= \
	"$(INTDIR)/msjdrag.obj" \
	"$(INTDIR)/MSJDragPpg.obj" \
	"$(INTDIR)/MSJDragCtl.obj" \
	"$(INTDIR)/StdAfx.obj" \
	"$(INTDIR)/VBFrWnd.obj" \
	"$(INTDIR)/msjdrag.res"

"$(OUTDIR)\msjdrag.ocx" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

# Begin Custom Build - Registering OLE control...
OutDir=.\DebugU
TargetPath=.\DebugU\msjdrag.ocx
InputPath=.\DebugU\msjdrag.ocx
SOURCE=$(InputPath)

"$(OutDir)\regsvr32.trg" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   regsvr32 /s /c "$(TargetPath)"
   echo regsvr32 exec. time > "$(OutDir)\regsvr32.trg"

# End Custom Build

!ELSEIF  "$(CFG)" == "msjdrag - Win32 Unicode Release"

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

ALL : "$(OUTDIR)\msjdrag.ocx" "$(OUTDIR)\regsvr32.trg"

CLEAN : 
	-@erase ".\ReleaseU\msjdrag.lib"
	-@erase ".\ReleaseU\MSJDragCtl.obj"
	-@erase ".\ReleaseU\msjdrag.pch"
	-@erase ".\ReleaseU\StdAfx.obj"
	-@erase ".\ReleaseU\MSJDragPpg.obj"
	-@erase ".\ReleaseU\msjdrag.obj"
	-@erase ".\ReleaseU\msjdrag.res"
	-@erase ".\ReleaseU\msjdrag.tlb"
	-@erase ".\ReleaseU\VBFrWnd.obj"
	-@erase ".\ReleaseU\msjdrag.exp"
	-@erase ".\ReleaseU\regsvr32.trg"
	-@erase ".\ReleaseU\msjdrag.ocx"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

# ADD BASE CPP /nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_WINDLL" /D "_AFXDLL" /D "_MBCS" /D "_USRDLL" /Yu"stdafx.h" /c
# ADD CPP /nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_WINDLL" /D "_AFXDLL" /D "_USRDLL" /D "_UNICODE" /Yu"stdafx.h" /c
CPP_PROJ=/nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D\
 "_WINDLL" /D "_AFXDLL" /D "_USRDLL" /D "_UNICODE" /Fp"$(INTDIR)/msjdrag.pch"\
 /Yu"stdafx.h" /Fo"$(INTDIR)/" /c 
CPP_OBJS=.\ReleaseU/
CPP_SBRS=
# ADD BASE MTL /nologo /D "NDEBUG" /win32
# ADD MTL /nologo /D "NDEBUG" /win32
MTL_PROJ=/nologo /D "NDEBUG" /win32 
# ADD BASE RSC /l 0x409 /d "NDEBUG" /d "_AFXDLL"
# ADD RSC /l 0x409 /d "NDEBUG" /d "_AFXDLL"
RSC_PROJ=/l 0x409 /fo"$(INTDIR)/msjdrag.res" /d "NDEBUG" /d "_AFXDLL" 
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
BSC32_FLAGS=/nologo /o"$(OUTDIR)/msjdrag.bsc" 
BSC32_SBRS=
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /dll /machine:I386
# ADD LINK32 /nologo /subsystem:windows /dll /machine:I386
LINK32_FLAGS=/nologo /subsystem:windows /dll /incremental:no\
 /pdb:"$(OUTDIR)/msjdrag.pdb" /machine:I386 /def:".\msjdrag.def"\
 /out:"$(OUTDIR)/msjdrag.ocx" /implib:"$(OUTDIR)/msjdrag.lib" 
DEF_FILE= \
	".\msjdrag.def"
LINK32_OBJS= \
	"$(INTDIR)/MSJDragCtl.obj" \
	"$(INTDIR)/StdAfx.obj" \
	"$(INTDIR)/MSJDragPpg.obj" \
	"$(INTDIR)/msjdrag.obj" \
	"$(INTDIR)/VBFrWnd.obj" \
	"$(INTDIR)/msjdrag.res"

"$(OUTDIR)\msjdrag.ocx" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

# Begin Custom Build - Registering OLE control...
OutDir=.\ReleaseU
TargetPath=.\ReleaseU\msjdrag.ocx
InputPath=.\ReleaseU\msjdrag.ocx
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

# Name "msjdrag - Win32 Release"
# Name "msjdrag - Win32 Debug"
# Name "msjdrag - Win32 Unicode Debug"
# Name "msjdrag - Win32 Unicode Release"

!IF  "$(CFG)" == "msjdrag - Win32 Release"

!ELSEIF  "$(CFG)" == "msjdrag - Win32 Debug"

!ELSEIF  "$(CFG)" == "msjdrag - Win32 Unicode Debug"

!ELSEIF  "$(CFG)" == "msjdrag - Win32 Unicode Release"

!ENDIF 

################################################################################
# Begin Source File

SOURCE=.\ReadMe.txt

!IF  "$(CFG)" == "msjdrag - Win32 Release"

!ELSEIF  "$(CFG)" == "msjdrag - Win32 Debug"

!ELSEIF  "$(CFG)" == "msjdrag - Win32 Unicode Debug"

!ELSEIF  "$(CFG)" == "msjdrag - Win32 Unicode Release"

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\StdAfx.cpp
DEP_CPP_STDAF=\
	".\StdAfx.h"\
	

!IF  "$(CFG)" == "msjdrag - Win32 Release"

# ADD CPP /Yc"stdafx.h"

BuildCmds= \
	$(CPP) /nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D\
 "_WINDLL" /D "_AFXDLL" /D "_MBCS" /D "_USRDLL" /Fp"$(INTDIR)/msjdrag.pch"\
 /Yc"stdafx.h" /Fo"$(INTDIR)/" /c $(SOURCE) \
	

"$(INTDIR)\StdAfx.obj" : $(SOURCE) $(DEP_CPP_STDAF) "$(INTDIR)"
   $(BuildCmds)

"$(INTDIR)\msjdrag.pch" : $(SOURCE) $(DEP_CPP_STDAF) "$(INTDIR)"
   $(BuildCmds)

!ELSEIF  "$(CFG)" == "msjdrag - Win32 Debug"

# ADD CPP /Yc"stdafx.h"

BuildCmds= \
	$(CPP) /nologo /MDd /W3 /Gm /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS"\
 /D "_WINDLL" /D "_AFXDLL" /D "_MBCS" /D "_USRDLL" /FR"$(INTDIR)/"\
 /Fp"$(INTDIR)/msjdrag.pch" /Yc"stdafx.h" /Fo"$(INTDIR)/" /Fd"$(INTDIR)/" /c\
 $(SOURCE) \
	

"$(INTDIR)\StdAfx.obj" : $(SOURCE) $(DEP_CPP_STDAF) "$(INTDIR)"
   $(BuildCmds)

"$(INTDIR)\StdAfx.sbr" : $(SOURCE) $(DEP_CPP_STDAF) "$(INTDIR)"
   $(BuildCmds)

"$(INTDIR)\msjdrag.pch" : $(SOURCE) $(DEP_CPP_STDAF) "$(INTDIR)"
   $(BuildCmds)

!ELSEIF  "$(CFG)" == "msjdrag - Win32 Unicode Debug"

# ADD BASE CPP /Yc"stdafx.h"
# ADD CPP /Yc"stdafx.h"

BuildCmds= \
	$(CPP) /nologo /MDd /W3 /Gm /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS"\
 /D "_WINDLL" /D "_AFXDLL" /D "_USRDLL" /D "_UNICODE" /Fp"$(INTDIR)/msjdrag.pch"\
 /Yc"stdafx.h" /Fo"$(INTDIR)/" /Fd"$(INTDIR)/" /c $(SOURCE) \
	

"$(INTDIR)\StdAfx.obj" : $(SOURCE) $(DEP_CPP_STDAF) "$(INTDIR)"
   $(BuildCmds)

"$(INTDIR)\msjdrag.pch" : $(SOURCE) $(DEP_CPP_STDAF) "$(INTDIR)"
   $(BuildCmds)

!ELSEIF  "$(CFG)" == "msjdrag - Win32 Unicode Release"

# ADD BASE CPP /Yc"stdafx.h"
# ADD CPP /Yc"stdafx.h"

BuildCmds= \
	$(CPP) /nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D\
 "_WINDLL" /D "_AFXDLL" /D "_USRDLL" /D "_UNICODE" /Fp"$(INTDIR)/msjdrag.pch"\
 /Yc"stdafx.h" /Fo"$(INTDIR)/" /c $(SOURCE) \
	

"$(INTDIR)\StdAfx.obj" : $(SOURCE) $(DEP_CPP_STDAF) "$(INTDIR)"
   $(BuildCmds)

"$(INTDIR)\msjdrag.pch" : $(SOURCE) $(DEP_CPP_STDAF) "$(INTDIR)"
   $(BuildCmds)

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\msjdrag.cpp
DEP_CPP_MSJDR=\
	".\StdAfx.h"\
	".\msjdrag.h"\
	

!IF  "$(CFG)" == "msjdrag - Win32 Release"


"$(INTDIR)\msjdrag.obj" : $(SOURCE) $(DEP_CPP_MSJDR) "$(INTDIR)"\
 "$(INTDIR)\msjdrag.pch"


!ELSEIF  "$(CFG)" == "msjdrag - Win32 Debug"


"$(INTDIR)\msjdrag.obj" : $(SOURCE) $(DEP_CPP_MSJDR) "$(INTDIR)"\
 "$(INTDIR)\msjdrag.pch"

"$(INTDIR)\msjdrag.sbr" : $(SOURCE) $(DEP_CPP_MSJDR) "$(INTDIR)"\
 "$(INTDIR)\msjdrag.pch"


!ELSEIF  "$(CFG)" == "msjdrag - Win32 Unicode Debug"


"$(INTDIR)\msjdrag.obj" : $(SOURCE) $(DEP_CPP_MSJDR) "$(INTDIR)"\
 "$(INTDIR)\msjdrag.pch"


!ELSEIF  "$(CFG)" == "msjdrag - Win32 Unicode Release"


"$(INTDIR)\msjdrag.obj" : $(SOURCE) $(DEP_CPP_MSJDR) "$(INTDIR)"\
 "$(INTDIR)\msjdrag.pch"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\msjdrag.def

!IF  "$(CFG)" == "msjdrag - Win32 Release"

!ELSEIF  "$(CFG)" == "msjdrag - Win32 Debug"

!ELSEIF  "$(CFG)" == "msjdrag - Win32 Unicode Debug"

!ELSEIF  "$(CFG)" == "msjdrag - Win32 Unicode Release"

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\msjdrag.rc

!IF  "$(CFG)" == "msjdrag - Win32 Release"

DEP_RSC_MSJDRA=\
	".\MSJDragCtl.bmp"\
	
NODEP_RSC_MSJDRA=\
	".\Release\msjdrag.tlb"\
	

"$(INTDIR)\msjdrag.res" : $(SOURCE) $(DEP_RSC_MSJDRA) "$(INTDIR)"\
 "$(INTDIR)\msjdrag.tlb"
   $(RSC) /l 0x409 /fo"$(INTDIR)/msjdrag.res" /i "Release" /d "NDEBUG" /d\
 "_AFXDLL" $(SOURCE)


!ELSEIF  "$(CFG)" == "msjdrag - Win32 Debug"

DEP_RSC_MSJDRA=\
	".\MSJDragCtl.bmp"\
	
NODEP_RSC_MSJDRA=\
	".\Debug\msjdrag.tlb"\
	

"$(INTDIR)\msjdrag.res" : $(SOURCE) $(DEP_RSC_MSJDRA) "$(INTDIR)"\
 "$(INTDIR)\msjdrag.tlb"
   $(RSC) /l 0x409 /fo"$(INTDIR)/msjdrag.res" /i "Debug" /d "_DEBUG" /d\
 "_AFXDLL" $(SOURCE)


!ELSEIF  "$(CFG)" == "msjdrag - Win32 Unicode Debug"

DEP_RSC_MSJDRA=\
	".\MSJDragCtl.bmp"\
	
NODEP_RSC_MSJDRA=\
	".\DebugU\msjdrag.tlb"\
	

"$(INTDIR)\msjdrag.res" : $(SOURCE) $(DEP_RSC_MSJDRA) "$(INTDIR)"\
 "$(INTDIR)\msjdrag.tlb"
   $(RSC) /l 0x409 /fo"$(INTDIR)/msjdrag.res" /i "DebugU" /d "_DEBUG" /d\
 "_AFXDLL" $(SOURCE)


!ELSEIF  "$(CFG)" == "msjdrag - Win32 Unicode Release"

DEP_RSC_MSJDRA=\
	".\MSJDragCtl.bmp"\
	
NODEP_RSC_MSJDRA=\
	".\ReleaseU\msjdrag.tlb"\
	

"$(INTDIR)\msjdrag.res" : $(SOURCE) $(DEP_RSC_MSJDRA) "$(INTDIR)"\
 "$(INTDIR)\msjdrag.tlb"
   $(RSC) /l 0x409 /fo"$(INTDIR)/msjdrag.res" /i "ReleaseU" /d "NDEBUG" /d\
 "_AFXDLL" $(SOURCE)


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\msjdrag.odl

!IF  "$(CFG)" == "msjdrag - Win32 Release"


"$(OUTDIR)\msjdrag.tlb" : $(SOURCE) "$(OUTDIR)"
   $(MTL) /nologo /D "NDEBUG" /tlb "$(OUTDIR)/msjdrag.tlb" /win32 $(SOURCE)


!ELSEIF  "$(CFG)" == "msjdrag - Win32 Debug"


"$(OUTDIR)\msjdrag.tlb" : $(SOURCE) "$(OUTDIR)"
   $(MTL) /nologo /D "_DEBUG" /tlb "$(OUTDIR)/msjdrag.tlb" /win32 $(SOURCE)


!ELSEIF  "$(CFG)" == "msjdrag - Win32 Unicode Debug"


"$(OUTDIR)\msjdrag.tlb" : $(SOURCE) "$(OUTDIR)"
   $(MTL) /nologo /D "_DEBUG" /tlb "$(OUTDIR)/msjdrag.tlb" /win32 $(SOURCE)


!ELSEIF  "$(CFG)" == "msjdrag - Win32 Unicode Release"


"$(OUTDIR)\msjdrag.tlb" : $(SOURCE) "$(OUTDIR)"
   $(MTL) /nologo /D "NDEBUG" /tlb "$(OUTDIR)/msjdrag.tlb" /win32 $(SOURCE)


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\MSJDragCtl.cpp

!IF  "$(CFG)" == "msjdrag - Win32 Release"

DEP_CPP_MSJDRAG=\
	".\StdAfx.h"\
	".\msjdrag.h"\
	".\MSJDragCtl.h"\
	".\MSJDragPpg.h"\
	".\VBFrWnd.h"\
	

"$(INTDIR)\MSJDragCtl.obj" : $(SOURCE) $(DEP_CPP_MSJDRAG) "$(INTDIR)"\
 "$(INTDIR)\msjdrag.pch"


!ELSEIF  "$(CFG)" == "msjdrag - Win32 Debug"

DEP_CPP_MSJDRAG=\
	".\StdAfx.h"\
	".\msjdrag.h"\
	".\MSJDragCtl.h"\
	".\MSJDragPpg.h"\
	".\VBFrWnd.h"\
	

"$(INTDIR)\MSJDragCtl.obj" : $(SOURCE) $(DEP_CPP_MSJDRAG) "$(INTDIR)"\
 "$(INTDIR)\msjdrag.pch"

"$(INTDIR)\MSJDragCtl.sbr" : $(SOURCE) $(DEP_CPP_MSJDRAG) "$(INTDIR)"\
 "$(INTDIR)\msjdrag.pch"


!ELSEIF  "$(CFG)" == "msjdrag - Win32 Unicode Debug"

DEP_CPP_MSJDRAG=\
	".\StdAfx.h"\
	".\msjdrag.h"\
	".\MSJDragCtl.h"\
	".\MSJDragPpg.h"\
	".\VBFrWnd.h"\
	

"$(INTDIR)\MSJDragCtl.obj" : $(SOURCE) $(DEP_CPP_MSJDRAG) "$(INTDIR)"\
 "$(INTDIR)\msjdrag.pch"


!ELSEIF  "$(CFG)" == "msjdrag - Win32 Unicode Release"

DEP_CPP_MSJDRAG=\
	".\StdAfx.h"\
	".\msjdrag.h"\
	".\MSJDragCtl.h"\
	".\MSJDragPpg.h"\
	".\VBFrWnd.h"\
	
NODEP_CPP_MSJDRAG=\
	".\FromHandle"\
	

"$(INTDIR)\MSJDragCtl.obj" : $(SOURCE) $(DEP_CPP_MSJDRAG) "$(INTDIR)"\
 "$(INTDIR)\msjdrag.pch"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\MSJDragPpg.cpp
DEP_CPP_MSJDRAGP=\
	".\StdAfx.h"\
	".\msjdrag.h"\
	".\MSJDragPpg.h"\
	

!IF  "$(CFG)" == "msjdrag - Win32 Release"


"$(INTDIR)\MSJDragPpg.obj" : $(SOURCE) $(DEP_CPP_MSJDRAGP) "$(INTDIR)"\
 "$(INTDIR)\msjdrag.pch"


!ELSEIF  "$(CFG)" == "msjdrag - Win32 Debug"


"$(INTDIR)\MSJDragPpg.obj" : $(SOURCE) $(DEP_CPP_MSJDRAGP) "$(INTDIR)"\
 "$(INTDIR)\msjdrag.pch"

"$(INTDIR)\MSJDragPpg.sbr" : $(SOURCE) $(DEP_CPP_MSJDRAGP) "$(INTDIR)"\
 "$(INTDIR)\msjdrag.pch"


!ELSEIF  "$(CFG)" == "msjdrag - Win32 Unicode Debug"


"$(INTDIR)\MSJDragPpg.obj" : $(SOURCE) $(DEP_CPP_MSJDRAGP) "$(INTDIR)"\
 "$(INTDIR)\msjdrag.pch"


!ELSEIF  "$(CFG)" == "msjdrag - Win32 Unicode Release"


"$(INTDIR)\MSJDragPpg.obj" : $(SOURCE) $(DEP_CPP_MSJDRAGP) "$(INTDIR)"\
 "$(INTDIR)\msjdrag.pch"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\VBFrWnd.cpp
DEP_CPP_VBFRW=\
	".\StdAfx.h"\
	".\msjdrag.h"\
	".\VBFrWnd.h"\
	".\MSJDragCtl.h"\
	

!IF  "$(CFG)" == "msjdrag - Win32 Release"


"$(INTDIR)\VBFrWnd.obj" : $(SOURCE) $(DEP_CPP_VBFRW) "$(INTDIR)"\
 "$(INTDIR)\msjdrag.pch"


!ELSEIF  "$(CFG)" == "msjdrag - Win32 Debug"


"$(INTDIR)\VBFrWnd.obj" : $(SOURCE) $(DEP_CPP_VBFRW) "$(INTDIR)"\
 "$(INTDIR)\msjdrag.pch"

"$(INTDIR)\VBFrWnd.sbr" : $(SOURCE) $(DEP_CPP_VBFRW) "$(INTDIR)"\
 "$(INTDIR)\msjdrag.pch"


!ELSEIF  "$(CFG)" == "msjdrag - Win32 Unicode Debug"


"$(INTDIR)\VBFrWnd.obj" : $(SOURCE) $(DEP_CPP_VBFRW) "$(INTDIR)"\
 "$(INTDIR)\msjdrag.pch"


!ELSEIF  "$(CFG)" == "msjdrag - Win32 Unicode Release"


"$(INTDIR)\VBFrWnd.obj" : $(SOURCE) $(DEP_CPP_VBFRW) "$(INTDIR)"\
 "$(INTDIR)\msjdrag.pch"


!ENDIF 

# End Source File
# End Target
# End Project
################################################################################
