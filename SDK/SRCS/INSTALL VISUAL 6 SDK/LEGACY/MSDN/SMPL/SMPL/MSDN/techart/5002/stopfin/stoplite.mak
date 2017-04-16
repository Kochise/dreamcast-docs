# Microsoft Developer Studio Generated NMAKE File, Format Version 4.10
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Dynamic-Link Library" 0x0102

!IF "$(CFG)" == ""
CFG=StopLite - Win32 Debug
!MESSAGE No configuration specified.  Defaulting to StopLite - Win32 Debug.
!ENDIF 

!IF "$(CFG)" != "StopLite - Win32 Release" && "$(CFG)" !=\
 "StopLite - Win32 Debug" && "$(CFG)" != "StopLite - Win32 Unicode Debug" &&\
 "$(CFG)" != "StopLite - Win32 Unicode Release"
!MESSAGE Invalid configuration "$(CFG)" specified.
!MESSAGE You can specify a configuration when running NMAKE on this makefile
!MESSAGE by defining the macro CFG on the command line.  For example:
!MESSAGE 
!MESSAGE NMAKE /f "StopLite.mak" CFG="StopLite - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "StopLite - Win32 Release" (based on\
 "Win32 (x86) Dynamic-Link Library")
!MESSAGE "StopLite - Win32 Debug" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE "StopLite - Win32 Unicode Debug" (based on\
 "Win32 (x86) Dynamic-Link Library")
!MESSAGE "StopLite - Win32 Unicode Release" (based on\
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
# PROP Target_Last_Scanned "StopLite - Win32 Debug"
CPP=cl.exe
MTL=mktyplib.exe
RSC=rc.exe

!IF  "$(CFG)" == "StopLite - Win32 Release"

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

ALL : "$(OUTDIR)\StopLite.ocx" "$(OUTDIR)\regsvr32.trg"

CLEAN : 
	-@erase "$(INTDIR)\Helpers.obj"
	-@erase "$(INTDIR)\StdAfx.obj"
	-@erase "$(INTDIR)\StopLite.obj"
	-@erase "$(INTDIR)\StopLite.pch"
	-@erase "$(INTDIR)\StopLite.res"
	-@erase "$(INTDIR)\StopLite.tlb"
	-@erase "$(INTDIR)\StopLiteCtl.obj"
	-@erase "$(INTDIR)\StopLitePpg.obj"
	-@erase "$(OUTDIR)\regsvr32.trg"
	-@erase "$(OUTDIR)\StopLite.exp"
	-@erase "$(OUTDIR)\StopLite.lib"
	-@erase "$(OUTDIR)\StopLite.ocx"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

# ADD BASE CPP /nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_WINDLL" /D "_AFXDLL" /D "_MBCS" /Yu"stdafx.h" /c
# ADD CPP /nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_WINDLL" /D "_AFXDLL" /D "_MBCS" /D "_USRDLL" /Yu"stdafx.h" /c
CPP_PROJ=/nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D\
 "_WINDLL" /D "_AFXDLL" /D "_MBCS" /D "_USRDLL" /Fp"$(INTDIR)/StopLite.pch"\
 /Yu"stdafx.h" /Fo"$(INTDIR)/" /c 
CPP_OBJS=.\Release/
CPP_SBRS=.\.
# ADD BASE MTL /nologo /D "NDEBUG" /win32
# ADD MTL /nologo /D "NDEBUG" /win32
MTL_PROJ=/nologo /D "NDEBUG" /win32 
# ADD BASE RSC /l 0x409 /d "NDEBUG" /d "_AFXDLL"
# ADD RSC /l 0x409 /d "NDEBUG" /d "_AFXDLL"
RSC_PROJ=/l 0x409 /fo"$(INTDIR)/StopLite.res" /d "NDEBUG" /d "_AFXDLL" 
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
BSC32_FLAGS=/nologo /o"$(OUTDIR)/StopLite.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /dll /machine:I386
# ADD LINK32 /nologo /subsystem:windows /dll /machine:I386
LINK32_FLAGS=/nologo /subsystem:windows /dll /incremental:no\
 /pdb:"$(OUTDIR)/StopLite.pdb" /machine:I386 /def:".\StopLite.def"\
 /out:"$(OUTDIR)/StopLite.ocx" /implib:"$(OUTDIR)/StopLite.lib" 
DEF_FILE= \
	".\StopLite.def"
LINK32_OBJS= \
	"$(INTDIR)\Helpers.obj" \
	"$(INTDIR)\StdAfx.obj" \
	"$(INTDIR)\StopLite.obj" \
	"$(INTDIR)\StopLite.res" \
	"$(INTDIR)\StopLiteCtl.obj" \
	"$(INTDIR)\StopLitePpg.obj"

"$(OUTDIR)\StopLite.ocx" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

# Begin Custom Build - Registering OLE control...
OutDir=.\Release
TargetPath=.\Release\StopLite.ocx
InputPath=.\Release\StopLite.ocx
SOURCE=$(InputPath)

"$(OutDir)\regsvr32.trg" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   regsvr32 /s /c "$(TargetPath)"
   echo regsvr32 exec. time > "$(OutDir)\regsvr32.trg"

# End Custom Build

!ELSEIF  "$(CFG)" == "StopLite - Win32 Debug"

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

ALL : "$(OUTDIR)\StopLite.ocx" "$(OUTDIR)\StopLite.bsc"\
 "$(OUTDIR)\regsvr32.trg"

CLEAN : 
	-@erase "$(INTDIR)\Helpers.obj"
	-@erase "$(INTDIR)\Helpers.sbr"
	-@erase "$(INTDIR)\StdAfx.obj"
	-@erase "$(INTDIR)\StdAfx.sbr"
	-@erase "$(INTDIR)\StopLite.obj"
	-@erase "$(INTDIR)\StopLite.pch"
	-@erase "$(INTDIR)\StopLite.res"
	-@erase "$(INTDIR)\StopLite.sbr"
	-@erase "$(INTDIR)\StopLite.tlb"
	-@erase "$(INTDIR)\StopLiteCtl.obj"
	-@erase "$(INTDIR)\StopLiteCtl.sbr"
	-@erase "$(INTDIR)\StopLitePpg.obj"
	-@erase "$(INTDIR)\StopLitePpg.sbr"
	-@erase "$(INTDIR)\vc40.idb"
	-@erase "$(INTDIR)\vc40.pdb"
	-@erase "$(OUTDIR)\regsvr32.trg"
	-@erase "$(OUTDIR)\StopLite.bsc"
	-@erase "$(OUTDIR)\StopLite.exp"
	-@erase "$(OUTDIR)\StopLite.ilk"
	-@erase "$(OUTDIR)\StopLite.lib"
	-@erase "$(OUTDIR)\StopLite.ocx"
	-@erase "$(OUTDIR)\StopLite.pdb"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

# ADD BASE CPP /nologo /MDd /W3 /Gm /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_WINDLL" /D "_AFXDLL" /D "_MBCS" /Yu"stdafx.h" /c
# ADD CPP /nologo /MDd /W3 /Gm /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_WINDLL" /D "_AFXDLL" /D "_MBCS" /D "_USRDLL" /FR /Yu"stdafx.h" /c
CPP_PROJ=/nologo /MDd /W3 /Gm /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS"\
 /D "_WINDLL" /D "_AFXDLL" /D "_MBCS" /D "_USRDLL" /FR"$(INTDIR)/"\
 /Fp"$(INTDIR)/StopLite.pch" /Yu"stdafx.h" /Fo"$(INTDIR)/" /Fd"$(INTDIR)/" /c 
CPP_OBJS=.\Debug/
CPP_SBRS=.\Debug/
# ADD BASE MTL /nologo /D "_DEBUG" /win32
# ADD MTL /nologo /D "_DEBUG" /win32
MTL_PROJ=/nologo /D "_DEBUG" /win32 
# ADD BASE RSC /l 0x409 /d "_DEBUG" /d "_AFXDLL"
# ADD RSC /l 0x409 /d "_DEBUG" /d "_AFXDLL"
RSC_PROJ=/l 0x409 /fo"$(INTDIR)/StopLite.res" /d "_DEBUG" /d "_AFXDLL" 
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
BSC32_FLAGS=/nologo /o"$(OUTDIR)/StopLite.bsc" 
BSC32_SBRS= \
	"$(INTDIR)\Helpers.sbr" \
	"$(INTDIR)\StdAfx.sbr" \
	"$(INTDIR)\StopLite.sbr" \
	"$(INTDIR)\StopLiteCtl.sbr" \
	"$(INTDIR)\StopLitePpg.sbr"

"$(OUTDIR)\StopLite.bsc" : "$(OUTDIR)" $(BSC32_SBRS)
    $(BSC32) @<<
  $(BSC32_FLAGS) $(BSC32_SBRS)
<<

LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /dll /debug /machine:I386
# ADD LINK32 /nologo /subsystem:windows /dll /debug /machine:I386
LINK32_FLAGS=/nologo /subsystem:windows /dll /incremental:yes\
 /pdb:"$(OUTDIR)/StopLite.pdb" /debug /machine:I386 /def:".\StopLite.def"\
 /out:"$(OUTDIR)/StopLite.ocx" /implib:"$(OUTDIR)/StopLite.lib" 
DEF_FILE= \
	".\StopLite.def"
LINK32_OBJS= \
	"$(INTDIR)\Helpers.obj" \
	"$(INTDIR)\StdAfx.obj" \
	"$(INTDIR)\StopLite.obj" \
	"$(INTDIR)\StopLite.res" \
	"$(INTDIR)\StopLiteCtl.obj" \
	"$(INTDIR)\StopLitePpg.obj"

"$(OUTDIR)\StopLite.ocx" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

# Begin Custom Build - Registering OLE control...
OutDir=.\Debug
TargetPath=.\Debug\StopLite.ocx
InputPath=.\Debug\StopLite.ocx
SOURCE=$(InputPath)

"$(OutDir)\regsvr32.trg" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   regsvr32 /s /c "$(TargetPath)"
   echo regsvr32 exec. time > "$(OutDir)\regsvr32.trg"

# End Custom Build

!ELSEIF  "$(CFG)" == "StopLite - Win32 Unicode Debug"

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

ALL : "$(OUTDIR)\StopLite.ocx" "$(OUTDIR)\regsvr32.trg"

CLEAN : 
	-@erase "$(INTDIR)\Helpers.obj"
	-@erase "$(INTDIR)\StdAfx.obj"
	-@erase "$(INTDIR)\StopLite.obj"
	-@erase "$(INTDIR)\StopLite.pch"
	-@erase "$(INTDIR)\StopLite.res"
	-@erase "$(INTDIR)\StopLite.tlb"
	-@erase "$(INTDIR)\StopLiteCtl.obj"
	-@erase "$(INTDIR)\StopLitePpg.obj"
	-@erase "$(INTDIR)\vc40.idb"
	-@erase "$(INTDIR)\vc40.pdb"
	-@erase "$(OUTDIR)\regsvr32.trg"
	-@erase "$(OUTDIR)\StopLite.exp"
	-@erase "$(OUTDIR)\StopLite.ilk"
	-@erase "$(OUTDIR)\StopLite.lib"
	-@erase "$(OUTDIR)\StopLite.ocx"
	-@erase "$(OUTDIR)\StopLite.pdb"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

# ADD BASE CPP /nologo /MDd /W3 /Gm /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_WINDLL" /D "_AFXDLL" /D "_MBCS" /D "_USRDLL" /Yu"stdafx.h" /c
# ADD CPP /nologo /MDd /W3 /Gm /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_WINDLL" /D "_AFXDLL" /D "_USRDLL" /D "_UNICODE" /Yu"stdafx.h" /c
CPP_PROJ=/nologo /MDd /W3 /Gm /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS"\
 /D "_WINDLL" /D "_AFXDLL" /D "_USRDLL" /D "_UNICODE"\
 /Fp"$(INTDIR)/StopLite.pch" /Yu"stdafx.h" /Fo"$(INTDIR)/" /Fd"$(INTDIR)/" /c 
CPP_OBJS=.\DebugU/
CPP_SBRS=.\.
# ADD BASE MTL /nologo /D "_DEBUG" /win32
# ADD MTL /nologo /D "_DEBUG" /win32
MTL_PROJ=/nologo /D "_DEBUG" /win32 
# ADD BASE RSC /l 0x409 /d "_DEBUG" /d "_AFXDLL"
# ADD RSC /l 0x409 /d "_DEBUG" /d "_AFXDLL"
RSC_PROJ=/l 0x409 /fo"$(INTDIR)/StopLite.res" /d "_DEBUG" /d "_AFXDLL" 
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
BSC32_FLAGS=/nologo /o"$(OUTDIR)/StopLite.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /dll /debug /machine:I386
# ADD LINK32 /nologo /subsystem:windows /dll /debug /machine:I386
LINK32_FLAGS=/nologo /subsystem:windows /dll /incremental:yes\
 /pdb:"$(OUTDIR)/StopLite.pdb" /debug /machine:I386 /def:".\StopLite.def"\
 /out:"$(OUTDIR)/StopLite.ocx" /implib:"$(OUTDIR)/StopLite.lib" 
DEF_FILE= \
	".\StopLite.def"
LINK32_OBJS= \
	"$(INTDIR)\Helpers.obj" \
	"$(INTDIR)\StdAfx.obj" \
	"$(INTDIR)\StopLite.obj" \
	"$(INTDIR)\StopLite.res" \
	"$(INTDIR)\StopLiteCtl.obj" \
	"$(INTDIR)\StopLitePpg.obj"

"$(OUTDIR)\StopLite.ocx" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

# Begin Custom Build - Registering OLE control...
OutDir=.\DebugU
TargetPath=.\DebugU\StopLite.ocx
InputPath=.\DebugU\StopLite.ocx
SOURCE=$(InputPath)

"$(OutDir)\regsvr32.trg" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   regsvr32 /s /c "$(TargetPath)"
   echo regsvr32 exec. time > "$(OutDir)\regsvr32.trg"

# End Custom Build

!ELSEIF  "$(CFG)" == "StopLite - Win32 Unicode Release"

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

ALL : "$(OUTDIR)\StopLite.ocx" "$(OUTDIR)\regsvr32.trg"

CLEAN : 
	-@erase "$(INTDIR)\Helpers.obj"
	-@erase "$(INTDIR)\StdAfx.obj"
	-@erase "$(INTDIR)\StopLite.obj"
	-@erase "$(INTDIR)\StopLite.pch"
	-@erase "$(INTDIR)\StopLite.res"
	-@erase "$(INTDIR)\StopLite.tlb"
	-@erase "$(INTDIR)\StopLiteCtl.obj"
	-@erase "$(INTDIR)\StopLitePpg.obj"
	-@erase "$(OUTDIR)\regsvr32.trg"
	-@erase "$(OUTDIR)\StopLite.exp"
	-@erase "$(OUTDIR)\StopLite.lib"
	-@erase "$(OUTDIR)\StopLite.ocx"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

# ADD BASE CPP /nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_WINDLL" /D "_AFXDLL" /D "_MBCS" /D "_USRDLL" /Yu"stdafx.h" /c
# ADD CPP /nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_WINDLL" /D "_AFXDLL" /D "_USRDLL" /D "_UNICODE" /Yu"stdafx.h" /c
CPP_PROJ=/nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D\
 "_WINDLL" /D "_AFXDLL" /D "_USRDLL" /D "_UNICODE" /Fp"$(INTDIR)/StopLite.pch"\
 /Yu"stdafx.h" /Fo"$(INTDIR)/" /c 
CPP_OBJS=.\ReleaseU/
CPP_SBRS=.\.
# ADD BASE MTL /nologo /D "NDEBUG" /win32
# ADD MTL /nologo /D "NDEBUG" /win32
MTL_PROJ=/nologo /D "NDEBUG" /win32 
# ADD BASE RSC /l 0x409 /d "NDEBUG" /d "_AFXDLL"
# ADD RSC /l 0x409 /d "NDEBUG" /d "_AFXDLL"
RSC_PROJ=/l 0x409 /fo"$(INTDIR)/StopLite.res" /d "NDEBUG" /d "_AFXDLL" 
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
BSC32_FLAGS=/nologo /o"$(OUTDIR)/StopLite.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /dll /machine:I386
# ADD LINK32 /nologo /subsystem:windows /dll /machine:I386
LINK32_FLAGS=/nologo /subsystem:windows /dll /incremental:no\
 /pdb:"$(OUTDIR)/StopLite.pdb" /machine:I386 /def:".\StopLite.def"\
 /out:"$(OUTDIR)/StopLite.ocx" /implib:"$(OUTDIR)/StopLite.lib" 
DEF_FILE= \
	".\StopLite.def"
LINK32_OBJS= \
	"$(INTDIR)\Helpers.obj" \
	"$(INTDIR)\StdAfx.obj" \
	"$(INTDIR)\StopLite.obj" \
	"$(INTDIR)\StopLite.res" \
	"$(INTDIR)\StopLiteCtl.obj" \
	"$(INTDIR)\StopLitePpg.obj"

"$(OUTDIR)\StopLite.ocx" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

# Begin Custom Build - Registering OLE control...
OutDir=.\ReleaseU
TargetPath=.\ReleaseU\StopLite.ocx
InputPath=.\ReleaseU\StopLite.ocx
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

# Name "StopLite - Win32 Release"
# Name "StopLite - Win32 Debug"
# Name "StopLite - Win32 Unicode Debug"
# Name "StopLite - Win32 Unicode Release"

!IF  "$(CFG)" == "StopLite - Win32 Release"

!ELSEIF  "$(CFG)" == "StopLite - Win32 Debug"

!ELSEIF  "$(CFG)" == "StopLite - Win32 Unicode Debug"

!ELSEIF  "$(CFG)" == "StopLite - Win32 Unicode Release"

!ENDIF 

################################################################################
# Begin Source File

SOURCE=.\ReadMe.txt

!IF  "$(CFG)" == "StopLite - Win32 Release"

!ELSEIF  "$(CFG)" == "StopLite - Win32 Debug"

!ELSEIF  "$(CFG)" == "StopLite - Win32 Unicode Debug"

!ELSEIF  "$(CFG)" == "StopLite - Win32 Unicode Release"

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\StdAfx.cpp
DEP_CPP_STDAF=\
	".\StdAfx.h"\
	

!IF  "$(CFG)" == "StopLite - Win32 Release"

# ADD CPP /Yc"stdafx.h"

BuildCmds= \
	$(CPP) /nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D\
 "_WINDLL" /D "_AFXDLL" /D "_MBCS" /D "_USRDLL" /Fp"$(INTDIR)/StopLite.pch"\
 /Yc"stdafx.h" /Fo"$(INTDIR)/" /c $(SOURCE) \
	

"$(INTDIR)\StdAfx.obj" : $(SOURCE) $(DEP_CPP_STDAF) "$(INTDIR)"
   $(BuildCmds)

"$(INTDIR)\StopLite.pch" : $(SOURCE) $(DEP_CPP_STDAF) "$(INTDIR)"
   $(BuildCmds)

!ELSEIF  "$(CFG)" == "StopLite - Win32 Debug"

# ADD CPP /Yc"stdafx.h"

BuildCmds= \
	$(CPP) /nologo /MDd /W3 /Gm /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS"\
 /D "_WINDLL" /D "_AFXDLL" /D "_MBCS" /D "_USRDLL" /FR"$(INTDIR)/"\
 /Fp"$(INTDIR)/StopLite.pch" /Yc"stdafx.h" /Fo"$(INTDIR)/" /Fd"$(INTDIR)/" /c\
 $(SOURCE) \
	

"$(INTDIR)\StdAfx.obj" : $(SOURCE) $(DEP_CPP_STDAF) "$(INTDIR)"
   $(BuildCmds)

"$(INTDIR)\StdAfx.sbr" : $(SOURCE) $(DEP_CPP_STDAF) "$(INTDIR)"
   $(BuildCmds)

"$(INTDIR)\StopLite.pch" : $(SOURCE) $(DEP_CPP_STDAF) "$(INTDIR)"
   $(BuildCmds)

!ELSEIF  "$(CFG)" == "StopLite - Win32 Unicode Debug"

# ADD BASE CPP /Yc"stdafx.h"
# ADD CPP /Yc"stdafx.h"

BuildCmds= \
	$(CPP) /nologo /MDd /W3 /Gm /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS"\
 /D "_WINDLL" /D "_AFXDLL" /D "_USRDLL" /D "_UNICODE"\
 /Fp"$(INTDIR)/StopLite.pch" /Yc"stdafx.h" /Fo"$(INTDIR)/" /Fd"$(INTDIR)/" /c\
 $(SOURCE) \
	

"$(INTDIR)\StdAfx.obj" : $(SOURCE) $(DEP_CPP_STDAF) "$(INTDIR)"
   $(BuildCmds)

"$(INTDIR)\StopLite.pch" : $(SOURCE) $(DEP_CPP_STDAF) "$(INTDIR)"
   $(BuildCmds)

!ELSEIF  "$(CFG)" == "StopLite - Win32 Unicode Release"

# ADD BASE CPP /Yc"stdafx.h"
# ADD CPP /Yc"stdafx.h"

BuildCmds= \
	$(CPP) /nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D\
 "_WINDLL" /D "_AFXDLL" /D "_USRDLL" /D "_UNICODE" /Fp"$(INTDIR)/StopLite.pch"\
 /Yc"stdafx.h" /Fo"$(INTDIR)/" /c $(SOURCE) \
	

"$(INTDIR)\StdAfx.obj" : $(SOURCE) $(DEP_CPP_STDAF) "$(INTDIR)"
   $(BuildCmds)

"$(INTDIR)\StopLite.pch" : $(SOURCE) $(DEP_CPP_STDAF) "$(INTDIR)"
   $(BuildCmds)

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\StopLite.cpp
DEP_CPP_STOPL=\
	".\StdAfx.h"\
	".\StopLite.h"\
	

!IF  "$(CFG)" == "StopLite - Win32 Release"


"$(INTDIR)\StopLite.obj" : $(SOURCE) $(DEP_CPP_STOPL) "$(INTDIR)"\
 "$(INTDIR)\StopLite.pch"


!ELSEIF  "$(CFG)" == "StopLite - Win32 Debug"


"$(INTDIR)\StopLite.obj" : $(SOURCE) $(DEP_CPP_STOPL) "$(INTDIR)"\
 "$(INTDIR)\StopLite.pch"

"$(INTDIR)\StopLite.sbr" : $(SOURCE) $(DEP_CPP_STOPL) "$(INTDIR)"\
 "$(INTDIR)\StopLite.pch"


!ELSEIF  "$(CFG)" == "StopLite - Win32 Unicode Debug"


"$(INTDIR)\StopLite.obj" : $(SOURCE) $(DEP_CPP_STOPL) "$(INTDIR)"\
 "$(INTDIR)\StopLite.pch"


!ELSEIF  "$(CFG)" == "StopLite - Win32 Unicode Release"


"$(INTDIR)\StopLite.obj" : $(SOURCE) $(DEP_CPP_STOPL) "$(INTDIR)"\
 "$(INTDIR)\StopLite.pch"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\StopLite.def

!IF  "$(CFG)" == "StopLite - Win32 Release"

!ELSEIF  "$(CFG)" == "StopLite - Win32 Debug"

!ELSEIF  "$(CFG)" == "StopLite - Win32 Unicode Debug"

!ELSEIF  "$(CFG)" == "StopLite - Win32 Unicode Release"

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\StopLite.rc

!IF  "$(CFG)" == "StopLite - Win32 Release"

DEP_RSC_STOPLI=\
	".\Release\StopLite.tlb"\
	".\StopLite.ico"\
	".\StopLiteCtl.bmp"\
	

"$(INTDIR)\StopLite.res" : $(SOURCE) $(DEP_RSC_STOPLI) "$(INTDIR)"\
 "$(INTDIR)\StopLite.tlb"
   $(RSC) /l 0x409 /fo"$(INTDIR)/StopLite.res" /i "Release" /d "NDEBUG" /d\
 "_AFXDLL" $(SOURCE)


!ELSEIF  "$(CFG)" == "StopLite - Win32 Debug"

DEP_RSC_STOPLI=\
	".\Debug\StopLite.tlb"\
	".\StopLite.ico"\
	".\StopLiteCtl.bmp"\
	

"$(INTDIR)\StopLite.res" : $(SOURCE) $(DEP_RSC_STOPLI) "$(INTDIR)"\
 "$(INTDIR)\StopLite.tlb"
   $(RSC) /l 0x409 /fo"$(INTDIR)/StopLite.res" /i "Debug" /d "_DEBUG" /d\
 "_AFXDLL" $(SOURCE)


!ELSEIF  "$(CFG)" == "StopLite - Win32 Unicode Debug"

DEP_RSC_STOPLI=\
	".\StopLite.ico"\
	".\StopLiteCtl.bmp"\
	
NODEP_RSC_STOPLI=\
	".\DebugU\StopLite.tlb"\
	

"$(INTDIR)\StopLite.res" : $(SOURCE) $(DEP_RSC_STOPLI) "$(INTDIR)"\
 "$(INTDIR)\StopLite.tlb"
   $(RSC) /l 0x409 /fo"$(INTDIR)/StopLite.res" /i "DebugU" /d "_DEBUG" /d\
 "_AFXDLL" $(SOURCE)


!ELSEIF  "$(CFG)" == "StopLite - Win32 Unicode Release"

DEP_RSC_STOPLI=\
	".\StopLite.ico"\
	".\StopLiteCtl.bmp"\
	
NODEP_RSC_STOPLI=\
	".\ReleaseU\StopLite.tlb"\
	

"$(INTDIR)\StopLite.res" : $(SOURCE) $(DEP_RSC_STOPLI) "$(INTDIR)"\
 "$(INTDIR)\StopLite.tlb"
   $(RSC) /l 0x409 /fo"$(INTDIR)/StopLite.res" /i "ReleaseU" /d "NDEBUG" /d\
 "_AFXDLL" $(SOURCE)


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\StopLite.odl
DEP_MTL_STOPLIT=\
	{$(INCLUDE)}"\idispids.h"\
	

!IF  "$(CFG)" == "StopLite - Win32 Release"


"$(OUTDIR)\StopLite.tlb" : $(SOURCE) $(DEP_MTL_STOPLIT) "$(OUTDIR)"
   $(MTL) /nologo /D "NDEBUG" /tlb "$(OUTDIR)/StopLite.tlb" /win32 $(SOURCE)


!ELSEIF  "$(CFG)" == "StopLite - Win32 Debug"


"$(OUTDIR)\StopLite.tlb" : $(SOURCE) $(DEP_MTL_STOPLIT) "$(OUTDIR)"
   $(MTL) /nologo /D "_DEBUG" /tlb "$(OUTDIR)/StopLite.tlb" /win32 $(SOURCE)


!ELSEIF  "$(CFG)" == "StopLite - Win32 Unicode Debug"


"$(OUTDIR)\StopLite.tlb" : $(SOURCE) $(DEP_MTL_STOPLIT) "$(OUTDIR)"
   $(MTL) /nologo /D "_DEBUG" /tlb "$(OUTDIR)/StopLite.tlb" /win32 $(SOURCE)


!ELSEIF  "$(CFG)" == "StopLite - Win32 Unicode Release"


"$(OUTDIR)\StopLite.tlb" : $(SOURCE) $(DEP_MTL_STOPLIT) "$(OUTDIR)"
   $(MTL) /nologo /D "NDEBUG" /tlb "$(OUTDIR)/StopLite.tlb" /win32 $(SOURCE)


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\StopLiteCtl.cpp

!IF  "$(CFG)" == "StopLite - Win32 Release"

DEP_CPP_STOPLITE=\
	".\helpers.h"\
	".\StdAfx.h"\
	".\StopLite.h"\
	".\StopLiteCtl.h"\
	".\StopLitePpg.h"\
	{$(INCLUDE)}"\comcat.h"\
	{$(INCLUDE)}"\objsafe.h"\
	

"$(INTDIR)\StopLiteCtl.obj" : $(SOURCE) $(DEP_CPP_STOPLITE) "$(INTDIR)"\
 "$(INTDIR)\StopLite.pch"


!ELSEIF  "$(CFG)" == "StopLite - Win32 Debug"

DEP_CPP_STOPLITE=\
	".\helpers.h"\
	".\StdAfx.h"\
	".\StopLite.h"\
	".\StopLiteCtl.h"\
	".\StopLitePpg.h"\
	{$(INCLUDE)}"\comcat.h"\
	{$(INCLUDE)}"\objsafe.h"\
	

"$(INTDIR)\StopLiteCtl.obj" : $(SOURCE) $(DEP_CPP_STOPLITE) "$(INTDIR)"\
 "$(INTDIR)\StopLite.pch"

"$(INTDIR)\StopLiteCtl.sbr" : $(SOURCE) $(DEP_CPP_STOPLITE) "$(INTDIR)"\
 "$(INTDIR)\StopLite.pch"


!ELSEIF  "$(CFG)" == "StopLite - Win32 Unicode Debug"

DEP_CPP_STOPLITE=\
	".\helpers.h"\
	".\StdAfx.h"\
	".\StopLite.h"\
	".\StopLiteCtl.h"\
	".\StopLitePpg.h"\
	{$(INCLUDE)}"\comcat.h"\
	{$(INCLUDE)}"\objsafe.h"\
	
NODEP_CPP_STOPLITE=\
	".\#ifdef"\
	

"$(INTDIR)\StopLiteCtl.obj" : $(SOURCE) $(DEP_CPP_STOPLITE) "$(INTDIR)"\
 "$(INTDIR)\StopLite.pch"


!ELSEIF  "$(CFG)" == "StopLite - Win32 Unicode Release"

DEP_CPP_STOPLITE=\
	".\helpers.h"\
	".\StdAfx.h"\
	".\StopLite.h"\
	".\StopLiteCtl.h"\
	".\StopLitePpg.h"\
	{$(INCLUDE)}"\comcat.h"\
	{$(INCLUDE)}"\objsafe.h"\
	

"$(INTDIR)\StopLiteCtl.obj" : $(SOURCE) $(DEP_CPP_STOPLITE) "$(INTDIR)"\
 "$(INTDIR)\StopLite.pch"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\StopLitePpg.cpp
DEP_CPP_STOPLITEP=\
	".\StdAfx.h"\
	".\StopLite.h"\
	".\StopLitePpg.h"\
	

!IF  "$(CFG)" == "StopLite - Win32 Release"


"$(INTDIR)\StopLitePpg.obj" : $(SOURCE) $(DEP_CPP_STOPLITEP) "$(INTDIR)"\
 "$(INTDIR)\StopLite.pch"


!ELSEIF  "$(CFG)" == "StopLite - Win32 Debug"


"$(INTDIR)\StopLitePpg.obj" : $(SOURCE) $(DEP_CPP_STOPLITEP) "$(INTDIR)"\
 "$(INTDIR)\StopLite.pch"

"$(INTDIR)\StopLitePpg.sbr" : $(SOURCE) $(DEP_CPP_STOPLITEP) "$(INTDIR)"\
 "$(INTDIR)\StopLite.pch"


!ELSEIF  "$(CFG)" == "StopLite - Win32 Unicode Debug"


"$(INTDIR)\StopLitePpg.obj" : $(SOURCE) $(DEP_CPP_STOPLITEP) "$(INTDIR)"\
 "$(INTDIR)\StopLite.pch"


!ELSEIF  "$(CFG)" == "StopLite - Win32 Unicode Release"


"$(INTDIR)\StopLitePpg.obj" : $(SOURCE) $(DEP_CPP_STOPLITEP) "$(INTDIR)"\
 "$(INTDIR)\StopLite.pch"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\Helpers.cpp
DEP_CPP_HELPE=\
	".\helpers.h"\
	".\StdAfx.h"\
	{$(INCLUDE)}"\comcat.h"\
	

!IF  "$(CFG)" == "StopLite - Win32 Release"


"$(INTDIR)\Helpers.obj" : $(SOURCE) $(DEP_CPP_HELPE) "$(INTDIR)"\
 "$(INTDIR)\StopLite.pch"


!ELSEIF  "$(CFG)" == "StopLite - Win32 Debug"


"$(INTDIR)\Helpers.obj" : $(SOURCE) $(DEP_CPP_HELPE) "$(INTDIR)"\
 "$(INTDIR)\StopLite.pch"

"$(INTDIR)\Helpers.sbr" : $(SOURCE) $(DEP_CPP_HELPE) "$(INTDIR)"\
 "$(INTDIR)\StopLite.pch"


!ELSEIF  "$(CFG)" == "StopLite - Win32 Unicode Debug"


"$(INTDIR)\Helpers.obj" : $(SOURCE) $(DEP_CPP_HELPE) "$(INTDIR)"\
 "$(INTDIR)\StopLite.pch"


!ELSEIF  "$(CFG)" == "StopLite - Win32 Unicode Release"


"$(INTDIR)\Helpers.obj" : $(SOURCE) $(DEP_CPP_HELPE) "$(INTDIR)"\
 "$(INTDIR)\StopLite.pch"


!ENDIF 

# End Source File
# End Target
# End Project
################################################################################
