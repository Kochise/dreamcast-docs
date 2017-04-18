# Microsoft Developer Studio Generated NMAKE File, Format Version 4.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Dynamic-Link Library" 0x0102

!IF "$(CFG)" == ""
CFG=MSJSock - Win32 Debug
!MESSAGE No configuration specified.  Defaulting to MSJSock - Win32 Debug.
!ENDIF 

!IF "$(CFG)" != "MSJSock - Win32 Release" && "$(CFG)" !=\
 "MSJSock - Win32 Debug" && "$(CFG)" != "MSJSock - Win32 Unicode Debug" &&\
 "$(CFG)" != "MSJSock - Win32 Unicode Release"
!MESSAGE Invalid configuration "$(CFG)" specified.
!MESSAGE You can specify a configuration when running NMAKE on this makefile
!MESSAGE by defining the macro CFG on the command line.  For example:
!MESSAGE 
!MESSAGE NMAKE /f "MSJSock.mak" CFG="MSJSock - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "MSJSock - Win32 Release" (based on\
 "Win32 (x86) Dynamic-Link Library")
!MESSAGE "MSJSock - Win32 Debug" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE "MSJSock - Win32 Unicode Debug" (based on\
 "Win32 (x86) Dynamic-Link Library")
!MESSAGE "MSJSock - Win32 Unicode Release" (based on\
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
# PROP Target_Last_Scanned "MSJSock - Win32 Debug"
CPP=cl.exe
MTL=mktyplib.exe
RSC=rc.exe

!IF  "$(CFG)" == "MSJSock - Win32 Release"

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

ALL : "$(OUTDIR)\MSJSock.ocx" "$(OUTDIR)\MSJSock.tlb" "$(OUTDIR)\regsvr32.trg"

CLEAN : 
	-@erase ".\Release\MSJSock.tlb"
	-@erase ".\Release\MSJSock.lib"
	-@erase ".\Release\StdAfx.obj"
	-@erase ".\Release\MSJSock.obj"
	-@erase ".\Release\MSJSock.pch"
	-@erase ".\Release\MSJSockPpg.obj"
	-@erase ".\Release\MSJSockCtl.obj"
	-@erase ".\Release\MSJSock.res"
	-@erase ".\Release\MSJSock.exp"
	-@erase ".\Release\regsvr32.trg"
	-@erase ".\Release\MSJSock.ocx"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

# ADD BASE CPP /nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_WINDLL" /D "_AFXDLL" /D "_MBCS" /Yu"stdafx.h" /c
# ADD CPP /nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_WINDLL" /D "_AFXDLL" /D "_MBCS" /D "_USRDLL" /Yu"stdafx.h" /c
CPP_PROJ=/nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D\
 "_WINDLL" /D "_AFXDLL" /D "_MBCS" /D "_USRDLL" /Fp"$(INTDIR)/MSJSock.pch"\
 /Yu"stdafx.h" /Fo"$(INTDIR)/" /c 
CPP_OBJS=.\Release/
CPP_SBRS=
# ADD BASE MTL /nologo /D "NDEBUG" /win32
# ADD MTL /nologo /D "NDEBUG" /win32
MTL_PROJ=/nologo /D "NDEBUG" /win32 
# ADD BASE RSC /l 0x409 /d "NDEBUG" /d "_AFXDLL"
# ADD RSC /l 0x409 /d "NDEBUG" /d "_AFXDLL"
RSC_PROJ=/l 0x409 /fo"$(INTDIR)/MSJSock.res" /d "NDEBUG" /d "_AFXDLL" 
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
BSC32_FLAGS=/nologo /o"$(OUTDIR)/MSJSock.bsc" 
BSC32_SBRS=
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /dll /machine:I386
# ADD LINK32 /nologo /subsystem:windows /dll /machine:I386
LINK32_FLAGS=/nologo /subsystem:windows /dll /incremental:no\
 /pdb:"$(OUTDIR)/MSJSock.pdb" /machine:I386 /def:".\MSJSock.def"\
 /out:"$(OUTDIR)/MSJSock.ocx" /implib:"$(OUTDIR)/MSJSock.lib" 
DEF_FILE= \
	".\MSJSock.def"
LINK32_OBJS= \
	"$(INTDIR)/StdAfx.obj" \
	"$(INTDIR)/MSJSock.obj" \
	"$(INTDIR)/MSJSockPpg.obj" \
	"$(INTDIR)/MSJSockCtl.obj" \
	"$(INTDIR)/MSJSock.res"

"$(OUTDIR)\MSJSock.ocx" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

# Begin Custom Build - Registering OLE control...
OutDir=.\Release
TargetPath=.\Release\MSJSock.ocx
InputPath=.\Release\MSJSock.ocx
SOURCE=$(InputPath)

"$(OutDir)\regsvr32.trg" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   regsvr32 /s /c "$(TargetPath)"
   echo regsvr32 exec. time > "$(OutDir)\regsvr32.trg"

# End Custom Build

!ELSEIF  "$(CFG)" == "MSJSock - Win32 Debug"

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

ALL : "$(OUTDIR)\MSJSock.ocx" "$(OUTDIR)\regsvr32.trg"

CLEAN : 
	-@erase ".\Debug\vc40.pdb"
	-@erase ".\Debug\MSJSock.pch"
	-@erase ".\Debug\vc40.idb"
	-@erase ".\Debug\MSJSock.ilk"
	-@erase ".\Debug\MSJSockPpg.obj"
	-@erase ".\Debug\MSJSockCtl.obj"
	-@erase ".\Debug\MSJSock.obj"
	-@erase ".\Debug\StdAfx.obj"
	-@erase ".\Debug\MSJSock.res"
	-@erase ".\Debug\MSJSock.tlb"
	-@erase ".\Debug\MSJSock.lib"
	-@erase ".\Debug\MSJSock.exp"
	-@erase ".\Debug\MSJSock.pdb"
	-@erase ".\Debug\regsvr32.trg"
	-@erase ".\Debug\MSJSock.ocx"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

# ADD BASE CPP /nologo /MDd /W3 /Gm /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_WINDLL" /D "_AFXDLL" /D "_MBCS" /Yu"stdafx.h" /c
# ADD CPP /nologo /MDd /W3 /Gm /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_WINDLL" /D "_AFXDLL" /D "_MBCS" /D "_USRDLL" /Yu"stdafx.h" /c
CPP_PROJ=/nologo /MDd /W3 /Gm /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS"\
 /D "_WINDLL" /D "_AFXDLL" /D "_MBCS" /D "_USRDLL" /Fp"$(INTDIR)/MSJSock.pch"\
 /Yu"stdafx.h" /Fo"$(INTDIR)/" /Fd"$(INTDIR)/" /c 
CPP_OBJS=.\Debug/
CPP_SBRS=
# ADD BASE MTL /nologo /D "_DEBUG" /win32
# ADD MTL /nologo /D "_DEBUG" /win32
MTL_PROJ=/nologo /D "_DEBUG" /win32 
# ADD BASE RSC /l 0x409 /d "_DEBUG" /d "_AFXDLL"
# ADD RSC /l 0x409 /d "_DEBUG" /d "_AFXDLL"
RSC_PROJ=/l 0x409 /fo"$(INTDIR)/MSJSock.res" /d "_DEBUG" /d "_AFXDLL" 
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
BSC32_FLAGS=/nologo /o"$(OUTDIR)/MSJSock.bsc" 
BSC32_SBRS=
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /dll /debug /machine:I386
# ADD LINK32 /nologo /subsystem:windows /dll /debug /machine:I386
LINK32_FLAGS=/nologo /subsystem:windows /dll /incremental:yes\
 /pdb:"$(OUTDIR)/MSJSock.pdb" /debug /machine:I386 /def:".\MSJSock.def"\
 /out:"$(OUTDIR)/MSJSock.ocx" /implib:"$(OUTDIR)/MSJSock.lib" 
DEF_FILE= \
	".\MSJSock.def"
LINK32_OBJS= \
	"$(INTDIR)/MSJSockPpg.obj" \
	"$(INTDIR)/MSJSockCtl.obj" \
	"$(INTDIR)/MSJSock.obj" \
	"$(INTDIR)/StdAfx.obj" \
	"$(INTDIR)/MSJSock.res"

"$(OUTDIR)\MSJSock.ocx" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

# Begin Custom Build - Registering OLE control...
OutDir=.\Debug
TargetPath=.\Debug\MSJSock.ocx
InputPath=.\Debug\MSJSock.ocx
SOURCE=$(InputPath)

"$(OutDir)\regsvr32.trg" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   regsvr32 /s /c "$(TargetPath)"
   echo regsvr32 exec. time > "$(OutDir)\regsvr32.trg"

# End Custom Build

!ELSEIF  "$(CFG)" == "MSJSock - Win32 Unicode Debug"

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

ALL : "$(OUTDIR)\MSJSock.ocx" "$(OUTDIR)\MSJSock.tlb" "$(OUTDIR)\regsvr32.trg"

CLEAN : 
	-@erase ".\DebugU\vc40.pdb"
	-@erase ".\DebugU\MSJSock.pch"
	-@erase ".\DebugU\vc40.idb"
	-@erase ".\DebugU\MSJSock.tlb"
	-@erase ".\DebugU\MSJSock.ilk"
	-@erase ".\DebugU\MSJSock.obj"
	-@erase ".\DebugU\StdAfx.obj"
	-@erase ".\DebugU\MSJSockPpg.obj"
	-@erase ".\DebugU\MSJSockCtl.obj"
	-@erase ".\DebugU\MSJSock.res"
	-@erase ".\DebugU\MSJSock.lib"
	-@erase ".\DebugU\MSJSock.exp"
	-@erase ".\DebugU\MSJSock.pdb"
	-@erase ".\DebugU\regsvr32.trg"
	-@erase ".\DebugU\MSJSock.ocx"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

# ADD BASE CPP /nologo /MDd /W3 /Gm /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_WINDLL" /D "_AFXDLL" /D "_MBCS" /D "_USRDLL" /Yu"stdafx.h" /c
# ADD CPP /nologo /MDd /W3 /Gm /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_WINDLL" /D "_AFXDLL" /D "_USRDLL" /D "_UNICODE" /Yu"stdafx.h" /c
CPP_PROJ=/nologo /MDd /W3 /Gm /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS"\
 /D "_WINDLL" /D "_AFXDLL" /D "_USRDLL" /D "_UNICODE" /Fp"$(INTDIR)/MSJSock.pch"\
 /Yu"stdafx.h" /Fo"$(INTDIR)/" /Fd"$(INTDIR)/" /c 
CPP_OBJS=.\DebugU/
CPP_SBRS=
# ADD BASE MTL /nologo /D "_DEBUG" /win32
# ADD MTL /nologo /D "_DEBUG" /win32
MTL_PROJ=/nologo /D "_DEBUG" /win32 
# ADD BASE RSC /l 0x409 /d "_DEBUG" /d "_AFXDLL"
# ADD RSC /l 0x409 /d "_DEBUG" /d "_AFXDLL"
RSC_PROJ=/l 0x409 /fo"$(INTDIR)/MSJSock.res" /d "_DEBUG" /d "_AFXDLL" 
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
BSC32_FLAGS=/nologo /o"$(OUTDIR)/MSJSock.bsc" 
BSC32_SBRS=
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /dll /debug /machine:I386
# ADD LINK32 /nologo /subsystem:windows /dll /debug /machine:I386
LINK32_FLAGS=/nologo /subsystem:windows /dll /incremental:yes\
 /pdb:"$(OUTDIR)/MSJSock.pdb" /debug /machine:I386 /def:".\MSJSock.def"\
 /out:"$(OUTDIR)/MSJSock.ocx" /implib:"$(OUTDIR)/MSJSock.lib" 
DEF_FILE= \
	".\MSJSock.def"
LINK32_OBJS= \
	"$(INTDIR)/MSJSock.obj" \
	"$(INTDIR)/StdAfx.obj" \
	"$(INTDIR)/MSJSockPpg.obj" \
	"$(INTDIR)/MSJSockCtl.obj" \
	"$(INTDIR)/MSJSock.res"

"$(OUTDIR)\MSJSock.ocx" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

# Begin Custom Build - Registering OLE control...
OutDir=.\DebugU
TargetPath=.\DebugU\MSJSock.ocx
InputPath=.\DebugU\MSJSock.ocx
SOURCE=$(InputPath)

"$(OutDir)\regsvr32.trg" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   regsvr32 /s /c "$(TargetPath)"
   echo regsvr32 exec. time > "$(OutDir)\regsvr32.trg"

# End Custom Build

!ELSEIF  "$(CFG)" == "MSJSock - Win32 Unicode Release"

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

ALL : "$(OUTDIR)\MSJSock.ocx" "$(OUTDIR)\MSJSock.tlb" "$(OUTDIR)\regsvr32.trg"

CLEAN : 
	-@erase ".\ReleaseU\MSJSock.tlb"
	-@erase ".\ReleaseU\MSJSock.lib"
	-@erase ".\ReleaseU\StdAfx.obj"
	-@erase ".\ReleaseU\MSJSock.obj"
	-@erase ".\ReleaseU\MSJSock.pch"
	-@erase ".\ReleaseU\MSJSockPpg.obj"
	-@erase ".\ReleaseU\MSJSockCtl.obj"
	-@erase ".\ReleaseU\MSJSock.res"
	-@erase ".\ReleaseU\MSJSock.exp"
	-@erase ".\ReleaseU\regsvr32.trg"
	-@erase ".\ReleaseU\MSJSock.ocx"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

# ADD BASE CPP /nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_WINDLL" /D "_AFXDLL" /D "_MBCS" /D "_USRDLL" /Yu"stdafx.h" /c
# ADD CPP /nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_WINDLL" /D "_AFXDLL" /D "_USRDLL" /D "_UNICODE" /Yu"stdafx.h" /c
CPP_PROJ=/nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D\
 "_WINDLL" /D "_AFXDLL" /D "_USRDLL" /D "_UNICODE" /Fp"$(INTDIR)/MSJSock.pch"\
 /Yu"stdafx.h" /Fo"$(INTDIR)/" /c 
CPP_OBJS=.\ReleaseU/
CPP_SBRS=
# ADD BASE MTL /nologo /D "NDEBUG" /win32
# ADD MTL /nologo /D "NDEBUG" /win32
MTL_PROJ=/nologo /D "NDEBUG" /win32 
# ADD BASE RSC /l 0x409 /d "NDEBUG" /d "_AFXDLL"
# ADD RSC /l 0x409 /d "NDEBUG" /d "_AFXDLL"
RSC_PROJ=/l 0x409 /fo"$(INTDIR)/MSJSock.res" /d "NDEBUG" /d "_AFXDLL" 
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
BSC32_FLAGS=/nologo /o"$(OUTDIR)/MSJSock.bsc" 
BSC32_SBRS=
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /dll /machine:I386
# ADD LINK32 /nologo /subsystem:windows /dll /machine:I386
LINK32_FLAGS=/nologo /subsystem:windows /dll /incremental:no\
 /pdb:"$(OUTDIR)/MSJSock.pdb" /machine:I386 /def:".\MSJSock.def"\
 /out:"$(OUTDIR)/MSJSock.ocx" /implib:"$(OUTDIR)/MSJSock.lib" 
DEF_FILE= \
	".\MSJSock.def"
LINK32_OBJS= \
	"$(INTDIR)/StdAfx.obj" \
	"$(INTDIR)/MSJSock.obj" \
	"$(INTDIR)/MSJSockPpg.obj" \
	"$(INTDIR)/MSJSockCtl.obj" \
	"$(INTDIR)/MSJSock.res"

"$(OUTDIR)\MSJSock.ocx" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

# Begin Custom Build - Registering OLE control...
OutDir=.\ReleaseU
TargetPath=.\ReleaseU\MSJSock.ocx
InputPath=.\ReleaseU\MSJSock.ocx
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

# Name "MSJSock - Win32 Release"
# Name "MSJSock - Win32 Debug"
# Name "MSJSock - Win32 Unicode Debug"
# Name "MSJSock - Win32 Unicode Release"

!IF  "$(CFG)" == "MSJSock - Win32 Release"

!ELSEIF  "$(CFG)" == "MSJSock - Win32 Debug"

!ELSEIF  "$(CFG)" == "MSJSock - Win32 Unicode Debug"

!ELSEIF  "$(CFG)" == "MSJSock - Win32 Unicode Release"

!ENDIF 

################################################################################
# Begin Source File

SOURCE=.\ReadMe.txt

!IF  "$(CFG)" == "MSJSock - Win32 Release"

!ELSEIF  "$(CFG)" == "MSJSock - Win32 Debug"

!ELSEIF  "$(CFG)" == "MSJSock - Win32 Unicode Debug"

!ELSEIF  "$(CFG)" == "MSJSock - Win32 Unicode Release"

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\StdAfx.cpp
DEP_CPP_STDAF=\
	".\stdafx.h"\
	

!IF  "$(CFG)" == "MSJSock - Win32 Release"

# ADD CPP /Yc"stdafx.h"

BuildCmds= \
	$(CPP) /nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D\
 "_WINDLL" /D "_AFXDLL" /D "_MBCS" /D "_USRDLL" /Fp"$(INTDIR)/MSJSock.pch"\
 /Yc"stdafx.h" /Fo"$(INTDIR)/" /c $(SOURCE) \
	

"$(INTDIR)\StdAfx.obj" : $(SOURCE) $(DEP_CPP_STDAF) "$(INTDIR)"
   $(BuildCmds)

"$(INTDIR)\MSJSock.pch" : $(SOURCE) $(DEP_CPP_STDAF) "$(INTDIR)"
   $(BuildCmds)

!ELSEIF  "$(CFG)" == "MSJSock - Win32 Debug"

# ADD CPP /Yc"stdafx.h"

BuildCmds= \
	$(CPP) /nologo /MDd /W3 /Gm /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS"\
 /D "_WINDLL" /D "_AFXDLL" /D "_MBCS" /D "_USRDLL" /Fp"$(INTDIR)/MSJSock.pch"\
 /Yc"stdafx.h" /Fo"$(INTDIR)/" /Fd"$(INTDIR)/" /c $(SOURCE) \
	

"$(INTDIR)\StdAfx.obj" : $(SOURCE) $(DEP_CPP_STDAF) "$(INTDIR)"
   $(BuildCmds)

"$(INTDIR)\MSJSock.pch" : $(SOURCE) $(DEP_CPP_STDAF) "$(INTDIR)"
   $(BuildCmds)

!ELSEIF  "$(CFG)" == "MSJSock - Win32 Unicode Debug"

# ADD BASE CPP /Yc"stdafx.h"
# ADD CPP /Yc"stdafx.h"

BuildCmds= \
	$(CPP) /nologo /MDd /W3 /Gm /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS"\
 /D "_WINDLL" /D "_AFXDLL" /D "_USRDLL" /D "_UNICODE" /Fp"$(INTDIR)/MSJSock.pch"\
 /Yc"stdafx.h" /Fo"$(INTDIR)/" /Fd"$(INTDIR)/" /c $(SOURCE) \
	

"$(INTDIR)\StdAfx.obj" : $(SOURCE) $(DEP_CPP_STDAF) "$(INTDIR)"
   $(BuildCmds)

"$(INTDIR)\MSJSock.pch" : $(SOURCE) $(DEP_CPP_STDAF) "$(INTDIR)"
   $(BuildCmds)

!ELSEIF  "$(CFG)" == "MSJSock - Win32 Unicode Release"

# ADD BASE CPP /Yc"stdafx.h"
# ADD CPP /Yc"stdafx.h"

BuildCmds= \
	$(CPP) /nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D\
 "_WINDLL" /D "_AFXDLL" /D "_USRDLL" /D "_UNICODE" /Fp"$(INTDIR)/MSJSock.pch"\
 /Yc"stdafx.h" /Fo"$(INTDIR)/" /c $(SOURCE) \
	

"$(INTDIR)\StdAfx.obj" : $(SOURCE) $(DEP_CPP_STDAF) "$(INTDIR)"
   $(BuildCmds)

"$(INTDIR)\MSJSock.pch" : $(SOURCE) $(DEP_CPP_STDAF) "$(INTDIR)"
   $(BuildCmds)

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\MSJSock.cpp

!IF  "$(CFG)" == "MSJSock - Win32 Release"

DEP_CPP_MSJSO=\
	".\stdafx.h"\
	".\MSJSock.h"\
	

"$(INTDIR)\MSJSock.obj" : $(SOURCE) $(DEP_CPP_MSJSO) "$(INTDIR)"\
 "$(INTDIR)\MSJSock.pch"


!ELSEIF  "$(CFG)" == "MSJSock - Win32 Debug"

DEP_CPP_MSJSO=\
	".\stdafx.h"\
	".\MSJSock.h"\
	

"$(INTDIR)\MSJSock.obj" : $(SOURCE) $(DEP_CPP_MSJSO) "$(INTDIR)"\
 "$(INTDIR)\MSJSock.pch"


!ELSEIF  "$(CFG)" == "MSJSock - Win32 Unicode Debug"

DEP_CPP_MSJSO=\
	".\stdafx.h"\
	".\MSJSock.h"\
	
NODEP_CPP_MSJSO=\
	".\AfxSocketInit"\
	

"$(INTDIR)\MSJSock.obj" : $(SOURCE) $(DEP_CPP_MSJSO) "$(INTDIR)"\
 "$(INTDIR)\MSJSock.pch"


!ELSEIF  "$(CFG)" == "MSJSock - Win32 Unicode Release"

DEP_CPP_MSJSO=\
	".\stdafx.h"\
	".\MSJSock.h"\
	

"$(INTDIR)\MSJSock.obj" : $(SOURCE) $(DEP_CPP_MSJSO) "$(INTDIR)"\
 "$(INTDIR)\MSJSock.pch"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\MSJSock.def

!IF  "$(CFG)" == "MSJSock - Win32 Release"

!ELSEIF  "$(CFG)" == "MSJSock - Win32 Debug"

!ELSEIF  "$(CFG)" == "MSJSock - Win32 Unicode Debug"

!ELSEIF  "$(CFG)" == "MSJSock - Win32 Unicode Release"

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\MSJSock.rc

!IF  "$(CFG)" == "MSJSock - Win32 Release"


"$(INTDIR)\MSJSock.res" : $(SOURCE) "$(INTDIR)"
   $(RSC) /l 0x409 /fo"$(INTDIR)/MSJSock.res" /i "Release" /d "NDEBUG" /d\
 "_AFXDLL" $(SOURCE)


!ELSEIF  "$(CFG)" == "MSJSock - Win32 Debug"

DEP_RSC_MSJSOC=\
	".\MSJSock.ico"\
	".\MSJSockCtl.bmp"\
	".\Debug\MSJSock.tlb"\
	

"$(INTDIR)\MSJSock.res" : $(SOURCE) $(DEP_RSC_MSJSOC) "$(INTDIR)"\
 "$(INTDIR)\MSJSock.tlb"
   $(RSC) /l 0x409 /fo"$(INTDIR)/MSJSock.res" /i "Debug" /d "_DEBUG" /d\
 "_AFXDLL" $(SOURCE)


!ELSEIF  "$(CFG)" == "MSJSock - Win32 Unicode Debug"


"$(INTDIR)\MSJSock.res" : $(SOURCE) "$(INTDIR)"
   $(RSC) /l 0x409 /fo"$(INTDIR)/MSJSock.res" /i "DebugU" /d "_DEBUG" /d\
 "_AFXDLL" $(SOURCE)


!ELSEIF  "$(CFG)" == "MSJSock - Win32 Unicode Release"


"$(INTDIR)\MSJSock.res" : $(SOURCE) "$(INTDIR)"
   $(RSC) /l 0x409 /fo"$(INTDIR)/MSJSock.res" /i "ReleaseU" /d "NDEBUG" /d\
 "_AFXDLL" $(SOURCE)


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\MSJSock.odl

!IF  "$(CFG)" == "MSJSock - Win32 Release"


"$(OUTDIR)\MSJSock.tlb" : $(SOURCE) "$(OUTDIR)"
   $(MTL) /nologo /D "NDEBUG" /tlb "$(OUTDIR)/MSJSock.tlb" /win32 $(SOURCE)


!ELSEIF  "$(CFG)" == "MSJSock - Win32 Debug"


"$(OUTDIR)\MSJSock.tlb" : $(SOURCE) "$(OUTDIR)"
   $(MTL) /nologo /D "_DEBUG" /tlb "$(OUTDIR)/MSJSock.tlb" /win32 $(SOURCE)


!ELSEIF  "$(CFG)" == "MSJSock - Win32 Unicode Debug"


"$(OUTDIR)\MSJSock.tlb" : $(SOURCE) "$(OUTDIR)"
   $(MTL) /nologo /D "_DEBUG" /tlb "$(OUTDIR)/MSJSock.tlb" /win32 $(SOURCE)


!ELSEIF  "$(CFG)" == "MSJSock - Win32 Unicode Release"


"$(OUTDIR)\MSJSock.tlb" : $(SOURCE) "$(OUTDIR)"
   $(MTL) /nologo /D "NDEBUG" /tlb "$(OUTDIR)/MSJSock.tlb" /win32 $(SOURCE)


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\MSJSockCtl.cpp

!IF  "$(CFG)" == "MSJSock - Win32 Release"

DEP_CPP_MSJSOCK=\
	".\stdafx.h"\
	".\MSJSock.h"\
	".\MSJSockCtl.h"\
	".\MSJSockPpg.h"\
	

"$(INTDIR)\MSJSockCtl.obj" : $(SOURCE) $(DEP_CPP_MSJSOCK) "$(INTDIR)"\
 "$(INTDIR)\MSJSock.pch"


!ELSEIF  "$(CFG)" == "MSJSock - Win32 Debug"

DEP_CPP_MSJSOCK=\
	".\stdafx.h"\
	".\MSJSock.h"\
	".\MSJSockCtl.h"\
	".\MSJSockPpg.h"\
	

"$(INTDIR)\MSJSockCtl.obj" : $(SOURCE) $(DEP_CPP_MSJSOCK) "$(INTDIR)"\
 "$(INTDIR)\MSJSock.pch"


!ELSEIF  "$(CFG)" == "MSJSock - Win32 Unicode Debug"

DEP_CPP_MSJSOCK=\
	".\stdafx.h"\
	".\MSJSock.h"\
	".\MSJSockCtl.h"\
	".\MSJSockPpg.h"\
	
NODEP_CPP_MSJSOCK=\
	".\ntohs"\
	

"$(INTDIR)\MSJSockCtl.obj" : $(SOURCE) $(DEP_CPP_MSJSOCK) "$(INTDIR)"\
 "$(INTDIR)\MSJSock.pch"


!ELSEIF  "$(CFG)" == "MSJSock - Win32 Unicode Release"

DEP_CPP_MSJSOCK=\
	".\stdafx.h"\
	".\MSJSock.h"\
	".\MSJSockCtl.h"\
	".\MSJSockPpg.h"\
	

"$(INTDIR)\MSJSockCtl.obj" : $(SOURCE) $(DEP_CPP_MSJSOCK) "$(INTDIR)"\
 "$(INTDIR)\MSJSock.pch"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\MSJSockPpg.cpp
DEP_CPP_MSJSOCKP=\
	".\stdafx.h"\
	".\MSJSock.h"\
	".\MSJSockPpg.h"\
	

!IF  "$(CFG)" == "MSJSock - Win32 Release"


"$(INTDIR)\MSJSockPpg.obj" : $(SOURCE) $(DEP_CPP_MSJSOCKP) "$(INTDIR)"\
 "$(INTDIR)\MSJSock.pch"


!ELSEIF  "$(CFG)" == "MSJSock - Win32 Debug"


"$(INTDIR)\MSJSockPpg.obj" : $(SOURCE) $(DEP_CPP_MSJSOCKP) "$(INTDIR)"\
 "$(INTDIR)\MSJSock.pch"


!ELSEIF  "$(CFG)" == "MSJSock - Win32 Unicode Debug"


"$(INTDIR)\MSJSockPpg.obj" : $(SOURCE) $(DEP_CPP_MSJSOCKP) "$(INTDIR)"\
 "$(INTDIR)\MSJSock.pch"


!ELSEIF  "$(CFG)" == "MSJSock - Win32 Unicode Release"


"$(INTDIR)\MSJSockPpg.obj" : $(SOURCE) $(DEP_CPP_MSJSOCKP) "$(INTDIR)"\
 "$(INTDIR)\MSJSock.pch"


!ENDIF 

# End Source File
# End Target
# End Project
################################################################################
