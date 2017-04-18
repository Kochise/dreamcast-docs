# Microsoft Developer Studio Generated NMAKE File, Format Version 4.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Dynamic-Link Library" 0x0102

!IF "$(CFG)" == ""
CFG=NtSvc - Win32 Debug
!MESSAGE No configuration specified.  Defaulting to NtSvc - Win32 Debug.
!ENDIF 

!IF "$(CFG)" != "NtSvc - Win32 Release" && "$(CFG)" != "NtSvc - Win32 Debug" &&\
 "$(CFG)" != "NtSvc - Win32 Unicode Debug" && "$(CFG)" !=\
 "NtSvc - Win32 Unicode Release"
!MESSAGE Invalid configuration "$(CFG)" specified.
!MESSAGE You can specify a configuration when running NMAKE on this makefile
!MESSAGE by defining the macro CFG on the command line.  For example:
!MESSAGE 
!MESSAGE NMAKE /f "NtSvc.mak" CFG="NtSvc - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "NtSvc - Win32 Release" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE "NtSvc - Win32 Debug" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE "NtSvc - Win32 Unicode Debug" (based on\
 "Win32 (x86) Dynamic-Link Library")
!MESSAGE "NtSvc - Win32 Unicode Release" (based on\
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
# PROP Target_Last_Scanned "NtSvc - Win32 Debug"
RSC=rc.exe
MTL=mktyplib.exe
CPP=cl.exe

!IF  "$(CFG)" == "NtSvc - Win32 Release"

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

ALL : "$(OUTDIR)\NtSvc.ocx" "$(OUTDIR)\regsvr32.trg"

CLEAN : 
	-@erase ".\Release\NtSvc.lib"
	-@erase ".\Release\NtSvcCtl.obj"
	-@erase ".\Release\NtSvc.pch"
	-@erase ".\ntservmsg.h"
	-@erase ".\Release\StdAfx.obj"
	-@erase ".\Release\NtSvc.obj"
	-@erase ".\Release\NtSvc.res"
	-@erase ".\Release\NtSvc.tlb"
	-@erase ".\ntservmsg.rc"
	-@erase ".\Release\NtSvc.exp"
	-@erase ".\Release\regsvr32.trg"
	-@erase ".\Release\NtSvc.ocx"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

# ADD BASE CPP /nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_WINDLL" /D "_AFXDLL" /D "_MBCS" /Yu"stdafx.h" /c
# ADD CPP /nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_WINDLL" /D "_AFXDLL" /D "_MBCS" /D "_USRDLL" /Yu"stdafx.h" /c
CPP_PROJ=/nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D\
 "_WINDLL" /D "_AFXDLL" /D "_MBCS" /D "_USRDLL" /Fp"$(INTDIR)/NtSvc.pch"\
 /Yu"stdafx.h" /Fo"$(INTDIR)/" /c 
CPP_OBJS=.\Release/
CPP_SBRS=
# ADD BASE MTL /nologo /D "NDEBUG" /win32
# ADD MTL /nologo /D "NDEBUG" /win32
MTL_PROJ=/nologo /D "NDEBUG" /win32 
# ADD BASE RSC /l 0x409 /d "NDEBUG" /d "_AFXDLL"
# ADD RSC /l 0x409 /d "NDEBUG" /d "_AFXDLL"
RSC_PROJ=/l 0x409 /fo"$(INTDIR)/NtSvc.res" /d "NDEBUG" /d "_AFXDLL" 
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
BSC32_FLAGS=/nologo /o"$(OUTDIR)/NtSvc.bsc" 
BSC32_SBRS=
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /dll /machine:I386
# ADD LINK32 /nologo /subsystem:windows /dll /machine:I386
LINK32_FLAGS=/nologo /subsystem:windows /dll /incremental:no\
 /pdb:"$(OUTDIR)/NtSvc.pdb" /machine:I386 /def:".\NtSvc.def"\
 /out:"$(OUTDIR)/NtSvc.ocx" /implib:"$(OUTDIR)/NtSvc.lib" 
DEF_FILE= \
	".\NtSvc.def"
LINK32_OBJS= \
	"$(INTDIR)/NtSvcCtl.obj" \
	"$(INTDIR)/StdAfx.obj" \
	"$(INTDIR)/NtSvc.obj" \
	"$(INTDIR)/NtSvc.res"

"$(OUTDIR)\NtSvc.ocx" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

# Begin Custom Build - Registering OLE control...
OutDir=.\Release
TargetPath=.\Release\NtSvc.ocx
InputPath=.\Release\NtSvc.ocx
SOURCE=$(InputPath)

"$(OutDir)\regsvr32.trg" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   regsvr32 /s /c "$(TargetPath)"
   echo regsvr32 exec. time > "$(OutDir)\regsvr32.trg"

# End Custom Build

!ELSEIF  "$(CFG)" == "NtSvc - Win32 Debug"

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

ALL : "$(OUTDIR)\NtSvc.ocx" "$(OUTDIR)\regsvr32.trg"

CLEAN : 
	-@erase ".\Debug\vc40.pdb"
	-@erase ".\Debug\NtSvc.pch"
	-@erase ".\ntservmsg.h"
	-@erase ".\Debug\vc40.idb"
	-@erase ".\Debug\NtSvc.ilk"
	-@erase ".\Debug\StdAfx.obj"
	-@erase ".\Debug\NtSvc.obj"
	-@erase ".\Debug\NtSvcCtl.obj"
	-@erase ".\Debug\NtSvc.res"
	-@erase ".\Debug\NtSvc.tlb"
	-@erase ".\ntservmsg.rc"
	-@erase ".\Debug\NtSvc.lib"
	-@erase ".\Debug\NtSvc.exp"
	-@erase ".\Debug\NtSvc.pdb"
	-@erase ".\Debug\regsvr32.trg"
	-@erase ".\Debug\NtSvc.ocx"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

# ADD BASE CPP /nologo /MDd /W3 /Gm /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_WINDLL" /D "_AFXDLL" /D "_MBCS" /Yu"stdafx.h" /c
# ADD CPP /nologo /MDd /W3 /Gm /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_WINDLL" /D "_AFXDLL" /D "_MBCS" /D "_USRDLL" /Yu"stdafx.h" /c
CPP_PROJ=/nologo /MDd /W3 /Gm /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS"\
 /D "_WINDLL" /D "_AFXDLL" /D "_MBCS" /D "_USRDLL" /Fp"$(INTDIR)/NtSvc.pch"\
 /Yu"stdafx.h" /Fo"$(INTDIR)/" /Fd"$(INTDIR)/" /c 
CPP_OBJS=.\Debug/
CPP_SBRS=
# ADD BASE MTL /nologo /D "_DEBUG" /win32
# ADD MTL /nologo /D "_DEBUG" /win32
MTL_PROJ=/nologo /D "_DEBUG" /win32 
# ADD BASE RSC /l 0x409 /d "_DEBUG" /d "_AFXDLL"
# ADD RSC /l 0x409 /d "_DEBUG" /d "_AFXDLL"
RSC_PROJ=/l 0x409 /fo"$(INTDIR)/NtSvc.res" /d "_DEBUG" /d "_AFXDLL" 
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
BSC32_FLAGS=/nologo /o"$(OUTDIR)/NtSvc.bsc" 
BSC32_SBRS=
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /dll /debug /machine:I386
# ADD LINK32 /nologo /subsystem:windows /dll /debug /machine:I386
LINK32_FLAGS=/nologo /subsystem:windows /dll /incremental:yes\
 /pdb:"$(OUTDIR)/NtSvc.pdb" /debug /machine:I386 /def:".\NtSvc.def"\
 /out:"$(OUTDIR)/NtSvc.ocx" /implib:"$(OUTDIR)/NtSvc.lib" 
DEF_FILE= \
	".\NtSvc.def"
LINK32_OBJS= \
	"$(INTDIR)/StdAfx.obj" \
	"$(INTDIR)/NtSvc.obj" \
	"$(INTDIR)/NtSvcCtl.obj" \
	"$(INTDIR)/NtSvc.res"

"$(OUTDIR)\NtSvc.ocx" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

# Begin Custom Build - Registering OLE control...
OutDir=.\Debug
TargetPath=.\Debug\NtSvc.ocx
InputPath=.\Debug\NtSvc.ocx
SOURCE=$(InputPath)

"$(OutDir)\regsvr32.trg" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   regsvr32 /s /c "$(TargetPath)"
   echo regsvr32 exec. time > "$(OutDir)\regsvr32.trg"

# End Custom Build

!ELSEIF  "$(CFG)" == "NtSvc - Win32 Unicode Debug"

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

ALL : "$(OUTDIR)\NtSvc.ocx" "$(OUTDIR)\regsvr32.trg"

CLEAN : 
	-@erase ".\DebugU\vc40.pdb"
	-@erase ".\DebugU\NtSvc.pch"
	-@erase ".\ntservmsg.h"
	-@erase ".\DebugU\vc40.idb"
	-@erase ".\DebugU\NtSvc.ilk"
	-@erase ".\DebugU\NtSvcCtl.obj"
	-@erase ".\DebugU\NtSvc.obj"
	-@erase ".\DebugU\StdAfx.obj"
	-@erase ".\DebugU\NtSvc.res"
	-@erase ".\DebugU\NtSvc.tlb"
	-@erase ".\ntservmsg.rc"
	-@erase ".\DebugU\NtSvc.lib"
	-@erase ".\DebugU\NtSvc.exp"
	-@erase ".\DebugU\NtSvc.pdb"
	-@erase ".\DebugU\regsvr32.trg"
	-@erase ".\DebugU\NtSvc.ocx"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

# ADD BASE CPP /nologo /MDd /W3 /Gm /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_WINDLL" /D "_AFXDLL" /D "_MBCS" /D "_USRDLL" /Yu"stdafx.h" /c
# ADD CPP /nologo /MDd /W3 /Gm /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_WINDLL" /D "_AFXDLL" /D "_USRDLL" /D "_UNICODE" /Yu"stdafx.h" /c
CPP_PROJ=/nologo /MDd /W3 /Gm /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS"\
 /D "_WINDLL" /D "_AFXDLL" /D "_USRDLL" /D "_UNICODE" /Fp"$(INTDIR)/NtSvc.pch"\
 /Yu"stdafx.h" /Fo"$(INTDIR)/" /Fd"$(INTDIR)/" /c 
CPP_OBJS=.\DebugU/
CPP_SBRS=
# ADD BASE MTL /nologo /D "_DEBUG" /win32
# ADD MTL /nologo /D "_DEBUG" /win32
MTL_PROJ=/nologo /D "_DEBUG" /win32 
# ADD BASE RSC /l 0x409 /d "_DEBUG" /d "_AFXDLL"
# ADD RSC /l 0x409 /d "_DEBUG" /d "_AFXDLL"
RSC_PROJ=/l 0x409 /fo"$(INTDIR)/NtSvc.res" /d "_DEBUG" /d "_AFXDLL" 
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
BSC32_FLAGS=/nologo /o"$(OUTDIR)/NtSvc.bsc" 
BSC32_SBRS=
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /dll /debug /machine:I386
# ADD LINK32 /nologo /subsystem:windows /dll /debug /machine:I386
LINK32_FLAGS=/nologo /subsystem:windows /dll /incremental:yes\
 /pdb:"$(OUTDIR)/NtSvc.pdb" /debug /machine:I386 /def:".\NtSvc.def"\
 /out:"$(OUTDIR)/NtSvc.ocx" /implib:"$(OUTDIR)/NtSvc.lib" 
DEF_FILE= \
	".\NtSvc.def"
LINK32_OBJS= \
	"$(INTDIR)/NtSvcCtl.obj" \
	"$(INTDIR)/NtSvc.obj" \
	"$(INTDIR)/StdAfx.obj" \
	"$(INTDIR)/NtSvc.res"

"$(OUTDIR)\NtSvc.ocx" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

# Begin Custom Build - Registering OLE control...
OutDir=.\DebugU
TargetPath=.\DebugU\NtSvc.ocx
InputPath=.\DebugU\NtSvc.ocx
SOURCE=$(InputPath)

"$(OutDir)\regsvr32.trg" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   regsvr32 /s /c "$(TargetPath)"
   echo regsvr32 exec. time > "$(OutDir)\regsvr32.trg"

# End Custom Build

!ELSEIF  "$(CFG)" == "NtSvc - Win32 Unicode Release"

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

ALL : "$(OUTDIR)\NtSvc.ocx" "$(OUTDIR)\regsvr32.trg"

CLEAN : 
	-@erase ".\ReleaseU\NtSvc.lib"
	-@erase ".\ReleaseU\StdAfx.obj"
	-@erase ".\ReleaseU\NtSvc.obj"
	-@erase ".\ReleaseU\NtSvc.pch"
	-@erase ".\ntservmsg.h"
	-@erase ".\ReleaseU\NtSvcCtl.obj"
	-@erase ".\ReleaseU\NtSvc.res"
	-@erase ".\ReleaseU\NtSvc.tlb"
	-@erase ".\ntservmsg.rc"
	-@erase ".\ReleaseU\NtSvc.exp"
	-@erase ".\ReleaseU\regsvr32.trg"
	-@erase ".\ReleaseU\NtSvc.ocx"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

# ADD BASE CPP /nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_WINDLL" /D "_AFXDLL" /D "_MBCS" /D "_USRDLL" /Yu"stdafx.h" /c
# ADD CPP /nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_WINDLL" /D "_AFXDLL" /D "_USRDLL" /D "_UNICODE" /Yu"stdafx.h" /c
CPP_PROJ=/nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D\
 "_WINDLL" /D "_AFXDLL" /D "_USRDLL" /D "_UNICODE" /Fp"$(INTDIR)/NtSvc.pch"\
 /Yu"stdafx.h" /Fo"$(INTDIR)/" /c 
CPP_OBJS=.\ReleaseU/
CPP_SBRS=
# ADD BASE MTL /nologo /D "NDEBUG" /win32
# ADD MTL /nologo /D "NDEBUG" /win32
MTL_PROJ=/nologo /D "NDEBUG" /win32 
# ADD BASE RSC /l 0x409 /d "NDEBUG" /d "_AFXDLL"
# ADD RSC /l 0x409 /d "NDEBUG" /d "_AFXDLL"
RSC_PROJ=/l 0x409 /fo"$(INTDIR)/NtSvc.res" /d "NDEBUG" /d "_AFXDLL" 
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
BSC32_FLAGS=/nologo /o"$(OUTDIR)/NtSvc.bsc" 
BSC32_SBRS=
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /dll /machine:I386
# ADD LINK32 /nologo /subsystem:windows /dll /machine:I386
LINK32_FLAGS=/nologo /subsystem:windows /dll /incremental:no\
 /pdb:"$(OUTDIR)/NtSvc.pdb" /machine:I386 /def:".\NtSvc.def"\
 /out:"$(OUTDIR)/NtSvc.ocx" /implib:"$(OUTDIR)/NtSvc.lib" 
DEF_FILE= \
	".\NtSvc.def"
LINK32_OBJS= \
	"$(INTDIR)/StdAfx.obj" \
	"$(INTDIR)/NtSvc.obj" \
	"$(INTDIR)/NtSvcCtl.obj" \
	"$(INTDIR)/NtSvc.res"

"$(OUTDIR)\NtSvc.ocx" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

# Begin Custom Build - Registering OLE control...
OutDir=.\ReleaseU
TargetPath=.\ReleaseU\NtSvc.ocx
InputPath=.\ReleaseU\NtSvc.ocx
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

# Name "NtSvc - Win32 Release"
# Name "NtSvc - Win32 Debug"
# Name "NtSvc - Win32 Unicode Debug"
# Name "NtSvc - Win32 Unicode Release"

!IF  "$(CFG)" == "NtSvc - Win32 Release"

!ELSEIF  "$(CFG)" == "NtSvc - Win32 Debug"

!ELSEIF  "$(CFG)" == "NtSvc - Win32 Unicode Debug"

!ELSEIF  "$(CFG)" == "NtSvc - Win32 Unicode Release"

!ENDIF 

################################################################################
# Begin Source File

SOURCE=.\StdAfx.cpp
DEP_CPP_STDAF=\
	".\StdAfx.h"\
	

!IF  "$(CFG)" == "NtSvc - Win32 Release"

# ADD CPP /Yc"stdafx.h"

BuildCmds= \
	$(CPP) /nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D\
 "_WINDLL" /D "_AFXDLL" /D "_MBCS" /D "_USRDLL" /Fp"$(INTDIR)/NtSvc.pch"\
 /Yc"stdafx.h" /Fo"$(INTDIR)/" /c $(SOURCE) \
	

"$(INTDIR)\StdAfx.obj" : $(SOURCE) $(DEP_CPP_STDAF) "$(INTDIR)"
   $(BuildCmds)

"$(INTDIR)\NtSvc.pch" : $(SOURCE) $(DEP_CPP_STDAF) "$(INTDIR)"
   $(BuildCmds)

!ELSEIF  "$(CFG)" == "NtSvc - Win32 Debug"

# ADD CPP /Yc"stdafx.h"

BuildCmds= \
	$(CPP) /nologo /MDd /W3 /Gm /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS"\
 /D "_WINDLL" /D "_AFXDLL" /D "_MBCS" /D "_USRDLL" /Fp"$(INTDIR)/NtSvc.pch"\
 /Yc"stdafx.h" /Fo"$(INTDIR)/" /Fd"$(INTDIR)/" /c $(SOURCE) \
	

"$(INTDIR)\StdAfx.obj" : $(SOURCE) $(DEP_CPP_STDAF) "$(INTDIR)"
   $(BuildCmds)

"$(INTDIR)\NtSvc.pch" : $(SOURCE) $(DEP_CPP_STDAF) "$(INTDIR)"
   $(BuildCmds)

!ELSEIF  "$(CFG)" == "NtSvc - Win32 Unicode Debug"

# ADD BASE CPP /Yc"stdafx.h"
# ADD CPP /Yc"stdafx.h"

BuildCmds= \
	$(CPP) /nologo /MDd /W3 /Gm /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS"\
 /D "_WINDLL" /D "_AFXDLL" /D "_USRDLL" /D "_UNICODE" /Fp"$(INTDIR)/NtSvc.pch"\
 /Yc"stdafx.h" /Fo"$(INTDIR)/" /Fd"$(INTDIR)/" /c $(SOURCE) \
	

"$(INTDIR)\StdAfx.obj" : $(SOURCE) $(DEP_CPP_STDAF) "$(INTDIR)"
   $(BuildCmds)

"$(INTDIR)\NtSvc.pch" : $(SOURCE) $(DEP_CPP_STDAF) "$(INTDIR)"
   $(BuildCmds)

!ELSEIF  "$(CFG)" == "NtSvc - Win32 Unicode Release"

# ADD BASE CPP /Yc"stdafx.h"
# ADD CPP /Yc"stdafx.h"

BuildCmds= \
	$(CPP) /nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D\
 "_WINDLL" /D "_AFXDLL" /D "_USRDLL" /D "_UNICODE" /Fp"$(INTDIR)/NtSvc.pch"\
 /Yc"stdafx.h" /Fo"$(INTDIR)/" /c $(SOURCE) \
	

"$(INTDIR)\StdAfx.obj" : $(SOURCE) $(DEP_CPP_STDAF) "$(INTDIR)"
   $(BuildCmds)

"$(INTDIR)\NtSvc.pch" : $(SOURCE) $(DEP_CPP_STDAF) "$(INTDIR)"
   $(BuildCmds)

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\NtSvc.cpp
DEP_CPP_NTSVC=\
	".\StdAfx.h"\
	".\NtSvc.h"\
	".\ntservmsg.h"\
	

!IF  "$(CFG)" == "NtSvc - Win32 Release"


"$(INTDIR)\NtSvc.obj" : $(SOURCE) $(DEP_CPP_NTSVC) "$(INTDIR)"\
 "$(INTDIR)\NtSvc.pch" ".\ntservmsg.h"


!ELSEIF  "$(CFG)" == "NtSvc - Win32 Debug"


"$(INTDIR)\NtSvc.obj" : $(SOURCE) $(DEP_CPP_NTSVC) "$(INTDIR)"\
 "$(INTDIR)\NtSvc.pch" ".\ntservmsg.h"


!ELSEIF  "$(CFG)" == "NtSvc - Win32 Unicode Debug"


"$(INTDIR)\NtSvc.obj" : $(SOURCE) $(DEP_CPP_NTSVC) "$(INTDIR)"\
 "$(INTDIR)\NtSvc.pch" ".\ntservmsg.h"


!ELSEIF  "$(CFG)" == "NtSvc - Win32 Unicode Release"


"$(INTDIR)\NtSvc.obj" : $(SOURCE) $(DEP_CPP_NTSVC) "$(INTDIR)"\
 "$(INTDIR)\NtSvc.pch" ".\ntservmsg.h"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\NtSvc.def

!IF  "$(CFG)" == "NtSvc - Win32 Release"

!ELSEIF  "$(CFG)" == "NtSvc - Win32 Debug"

!ELSEIF  "$(CFG)" == "NtSvc - Win32 Unicode Debug"

!ELSEIF  "$(CFG)" == "NtSvc - Win32 Unicode Release"

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\NtSvc.rc

!IF  "$(CFG)" == "NtSvc - Win32 Release"

DEP_RSC_NTSVC_=\
	".\ntsvc.ico"\
	".\NtSvcCtl.bmp"\
	".\ntservmsg.rc"\
	".\MSG00001.bin"\
	
NODEP_RSC_NTSVC_=\
	".\Release\NtSvc.tlb"\
	

"$(INTDIR)\NtSvc.res" : $(SOURCE) $(DEP_RSC_NTSVC_) "$(INTDIR)"\
 "$(INTDIR)\NtSvc.tlb" ".\ntservmsg.rc"
   $(RSC) /l 0x409 /fo"$(INTDIR)/NtSvc.res" /i "Release" /d "NDEBUG" /d\
 "_AFXDLL" $(SOURCE)


!ELSEIF  "$(CFG)" == "NtSvc - Win32 Debug"

DEP_RSC_NTSVC_=\
	".\ntsvc.ico"\
	".\NtSvcCtl.bmp"\
	".\Debug\NtSvc.tlb"\
	".\ntservmsg.rc"\
	".\MSG00001.bin"\
	

"$(INTDIR)\NtSvc.res" : $(SOURCE) $(DEP_RSC_NTSVC_) "$(INTDIR)"\
 "$(INTDIR)\NtSvc.tlb" ".\ntservmsg.rc"
   $(RSC) /l 0x409 /fo"$(INTDIR)/NtSvc.res" /i "Debug" /d "_DEBUG" /d "_AFXDLL"\
 $(SOURCE)


!ELSEIF  "$(CFG)" == "NtSvc - Win32 Unicode Debug"

DEP_RSC_NTSVC_=\
	".\ntsvc.ico"\
	".\NtSvcCtl.bmp"\
	".\ntservmsg.rc"\
	".\MSG00001.bin"\
	
NODEP_RSC_NTSVC_=\
	".\DebugU\NtSvc.tlb"\
	

"$(INTDIR)\NtSvc.res" : $(SOURCE) $(DEP_RSC_NTSVC_) "$(INTDIR)"\
 "$(INTDIR)\NtSvc.tlb" ".\ntservmsg.rc"
   $(RSC) /l 0x409 /fo"$(INTDIR)/NtSvc.res" /i "DebugU" /d "_DEBUG" /d\
 "_AFXDLL" $(SOURCE)


!ELSEIF  "$(CFG)" == "NtSvc - Win32 Unicode Release"

DEP_RSC_NTSVC_=\
	".\ntsvc.ico"\
	".\NtSvcCtl.bmp"\
	".\ntservmsg.rc"\
	".\MSG00001.bin"\
	
NODEP_RSC_NTSVC_=\
	".\ReleaseU\NtSvc.tlb"\
	

"$(INTDIR)\NtSvc.res" : $(SOURCE) $(DEP_RSC_NTSVC_) "$(INTDIR)"\
 "$(INTDIR)\NtSvc.tlb" ".\ntservmsg.rc"
   $(RSC) /l 0x409 /fo"$(INTDIR)/NtSvc.res" /i "ReleaseU" /d "NDEBUG" /d\
 "_AFXDLL" $(SOURCE)


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\NtSvc.odl

!IF  "$(CFG)" == "NtSvc - Win32 Release"


"$(OUTDIR)\NtSvc.tlb" : $(SOURCE) "$(OUTDIR)"
   $(MTL) /nologo /D "NDEBUG" /tlb "$(OUTDIR)/NtSvc.tlb" /win32 $(SOURCE)


!ELSEIF  "$(CFG)" == "NtSvc - Win32 Debug"


"$(OUTDIR)\NtSvc.tlb" : $(SOURCE) "$(OUTDIR)"
   $(MTL) /nologo /D "_DEBUG" /tlb "$(OUTDIR)/NtSvc.tlb" /win32 $(SOURCE)


!ELSEIF  "$(CFG)" == "NtSvc - Win32 Unicode Debug"


"$(OUTDIR)\NtSvc.tlb" : $(SOURCE) "$(OUTDIR)"
   $(MTL) /nologo /D "_DEBUG" /tlb "$(OUTDIR)/NtSvc.tlb" /win32 $(SOURCE)


!ELSEIF  "$(CFG)" == "NtSvc - Win32 Unicode Release"


"$(OUTDIR)\NtSvc.tlb" : $(SOURCE) "$(OUTDIR)"
   $(MTL) /nologo /D "NDEBUG" /tlb "$(OUTDIR)/NtSvc.tlb" /win32 $(SOURCE)


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\NtSvcCtl.cpp
DEP_CPP_NTSVCC=\
	".\StdAfx.h"\
	".\NtSvc.h"\
	".\NtSvcCtl.h"\
	".\ntservmsg.h"\
	

!IF  "$(CFG)" == "NtSvc - Win32 Release"


"$(INTDIR)\NtSvcCtl.obj" : $(SOURCE) $(DEP_CPP_NTSVCC) "$(INTDIR)"\
 "$(INTDIR)\NtSvc.pch" ".\ntservmsg.h"


!ELSEIF  "$(CFG)" == "NtSvc - Win32 Debug"


"$(INTDIR)\NtSvcCtl.obj" : $(SOURCE) $(DEP_CPP_NTSVCC) "$(INTDIR)"\
 "$(INTDIR)\NtSvc.pch" ".\ntservmsg.h"


!ELSEIF  "$(CFG)" == "NtSvc - Win32 Unicode Debug"


"$(INTDIR)\NtSvcCtl.obj" : $(SOURCE) $(DEP_CPP_NTSVCC) "$(INTDIR)"\
 "$(INTDIR)\NtSvc.pch" ".\ntservmsg.h"


!ELSEIF  "$(CFG)" == "NtSvc - Win32 Unicode Release"


"$(INTDIR)\NtSvcCtl.obj" : $(SOURCE) $(DEP_CPP_NTSVCC) "$(INTDIR)"\
 "$(INTDIR)\NtSvc.pch" ".\ntservmsg.h"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\ntservmsg.mc

!IF  "$(CFG)" == "NtSvc - Win32 Release"

# Begin Custom Build - Compiling messages
InputPath=.\ntservmsg.mc
InputName=ntservmsg

BuildCmds= \
	mc $(InputPath) \
	

"$(InputName).h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"$(InputName).rc" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)
# End Custom Build

!ELSEIF  "$(CFG)" == "NtSvc - Win32 Debug"

# Begin Custom Build - Compiling messages
InputPath=.\ntservmsg.mc
InputName=ntservmsg

BuildCmds= \
	mc $(InputPath) \
	

"$(InputName).h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"$(InputName).rc" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)
# End Custom Build

!ELSEIF  "$(CFG)" == "NtSvc - Win32 Unicode Debug"

# Begin Custom Build - Compiling messages
InputPath=.\ntservmsg.mc
InputName=ntservmsg

BuildCmds= \
	mc $(InputPath) \
	

"$(InputName).h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"$(InputName).rc" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)
# End Custom Build

!ELSEIF  "$(CFG)" == "NtSvc - Win32 Unicode Release"

# Begin Custom Build - Compiling messages
InputPath=.\ntservmsg.mc
InputName=ntservmsg

BuildCmds= \
	mc $(InputPath) \
	

"$(InputName).h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"$(InputName).rc" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)
# End Custom Build

!ENDIF 

# End Source File
# End Target
# End Project
################################################################################
