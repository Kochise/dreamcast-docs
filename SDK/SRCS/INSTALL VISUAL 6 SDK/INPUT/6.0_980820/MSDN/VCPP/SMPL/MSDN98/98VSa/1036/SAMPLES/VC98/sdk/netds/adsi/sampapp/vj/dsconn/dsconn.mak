# Microsoft Developer Studio Generated NMAKE File, Format Version 4.20
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Dynamic-Link Library" 0x0102

!IF "$(CFG)" == ""
CFG=DSConn - Win32 Debug
!MESSAGE No configuration specified.  Defaulting to DSConn - Win32 Debug.
!ENDIF 

!IF "$(CFG)" != "DSConn - Win32 Release" && "$(CFG)" != "DSConn - Win32 Debug"\
 && "$(CFG)" != "DSConn - Win32 Unicode Release" && "$(CFG)" !=\
 "DSConn - Win32 Unicode Debug"
!MESSAGE Invalid configuration "$(CFG)" specified.
!MESSAGE You can specify a configuration when running NMAKE on this makefile
!MESSAGE by defining the macro CFG on the command line.  For example:
!MESSAGE 
!MESSAGE NMAKE /f "DSConn.mak" CFG="DSConn - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "DSConn - Win32 Release" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE "DSConn - Win32 Debug" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE "DSConn - Win32 Unicode Release" (based on\
 "Win32 (x86) Dynamic-Link Library")
!MESSAGE "DSConn - Win32 Unicode Debug" (based on\
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
# PROP Target_Last_Scanned "DSConn - Win32 Unicode Debug"
MTL=mktyplib.exe
RSC=rc.exe
CPP=cl.exe

!IF  "$(CFG)" == "DSConn - Win32 Release"

# PROP BASE Use_MFC 1
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "Release"
# PROP BASE Intermediate_Dir "Release"
# PROP BASE Target_Dir ""
# PROP Use_MFC 1
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "Release"
# PROP Intermediate_Dir "Release"
# PROP Target_Dir ""
OUTDIR=.\Release
INTDIR=.\Release
# Begin Custom Macros
OutDir=.\Release
# End Custom Macros

ALL : "$(OUTDIR)\DSConn.dll" "$(OUTDIR)\regsvr32.trg" ".\DSConn.tlb"

CLEAN : 
	-@erase "$(INTDIR)\dscnobj.obj"
	-@erase "$(INTDIR)\DSConn.obj"
	-@erase "$(INTDIR)\DSConn.pch"
	-@erase "$(INTDIR)\DSConn.res"
	-@erase "$(INTDIR)\StdAfx.obj"
	-@erase "$(OUTDIR)\DSConn.dll"
	-@erase "$(OUTDIR)\DSConn.exp"
	-@erase "$(OUTDIR)\DSConn.lib"
	-@erase "$(OUTDIR)\regsvr32.trg"
	-@erase ".\DSConn.h"
	-@erase ".\DSConn.tlb"
	-@erase ".\DSConn_i.c"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

# ADD BASE CPP /nologo /MT /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_WINDLL" /D "_MBCS" /Yu"stdafx.h" /c
# ADD CPP /nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_WINDLL" /D "_MBCS" /D "_USRDLL" /Yu"stdafx.h" /c
CPP_PROJ=/nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D\
 "_WINDLL" /D "_MBCS" /D "_USRDLL" /Fp"$(INTDIR)/DSConn.pch" /Yu"stdafx.h"\
 /Fo"$(INTDIR)/" /c 
CPP_OBJS=.\Release/
CPP_SBRS=.\.
# ADD BASE MTL /nologo /D "NDEBUG" /win32
# ADD MTL /nologo /D "NDEBUG" /win32
MTL_PROJ=/nologo /D "NDEBUG" /win32 
# ADD BASE RSC /l 0x409 /d "NDEBUG"
# ADD RSC /l 0x409 /d "NDEBUG"
RSC_PROJ=/l 0x409 /fo"$(INTDIR)/DSConn.res" /d "NDEBUG" 
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
BSC32_FLAGS=/nologo /o"$(OUTDIR)/DSConn.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /dll /machine:I386
# ADD LINK32 activeds.lib /nologo /subsystem:windows /dll /machine:I386
LINK32_FLAGS=activeds.lib /nologo /subsystem:windows /dll /incremental:no\
 /pdb:"$(OUTDIR)/DSConn.pdb" /machine:I386 /def:".\DSConn.def"\
 /out:"$(OUTDIR)/DSConn.dll" /implib:"$(OUTDIR)/DSConn.lib" 
DEF_FILE= \
	".\DSConn.def"
LINK32_OBJS= \
	"$(INTDIR)\dscnobj.obj" \
	"$(INTDIR)\DSConn.obj" \
	"$(INTDIR)\DSConn.res" \
	"$(INTDIR)\StdAfx.obj"

"$(OUTDIR)\DSConn.dll" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

# Begin Custom Build
OutDir=.\Release
TargetPath=.\Release\DSConn.dll
InputPath=.\Release\DSConn.dll
SOURCE=$(InputPath)

"$(OutDir)\regsvr32.trg" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   regsvr32 /s /c "$(TargetPath)"
   echo regsvr32 exec. time > "$(OutDir)\regsvr32.trg"

# End Custom Build

!ELSEIF  "$(CFG)" == "DSConn - Win32 Debug"

# PROP BASE Use_MFC 1
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "Debug"
# PROP BASE Intermediate_Dir "Debug"
# PROP BASE Target_Dir ""
# PROP Use_MFC 1
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "Debug"
# PROP Intermediate_Dir "Debug"
# PROP Target_Dir ""
OUTDIR=.\Debug
INTDIR=.\Debug
# Begin Custom Macros
OutDir=.\Debug
# End Custom Macros

ALL : "$(OUTDIR)\DSConn.dll" "$(OUTDIR)\regsvr32.trg" ".\DSConn.tlb"

CLEAN : 
	-@erase "$(INTDIR)\dscnobj.obj"
	-@erase "$(INTDIR)\DSConn.obj"
	-@erase "$(INTDIR)\DSConn.pch"
	-@erase "$(INTDIR)\DSConn.res"
	-@erase "$(INTDIR)\StdAfx.obj"
	-@erase "$(INTDIR)\vc40.idb"
	-@erase "$(INTDIR)\vc40.pdb"
	-@erase "$(OUTDIR)\DSConn.dll"
	-@erase "$(OUTDIR)\DSConn.exp"
	-@erase "$(OUTDIR)\DSConn.ilk"
	-@erase "$(OUTDIR)\DSConn.lib"
	-@erase "$(OUTDIR)\DSConn.pdb"
	-@erase "$(OUTDIR)\regsvr32.trg"
	-@erase ".\DSConn.h"
	-@erase ".\DSConn.tlb"
	-@erase ".\DSConn_i.c"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

# ADD BASE CPP /nologo /MTd /W3 /Gm /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_WINDLL" /D "_MBCS" /Yu"stdafx.h" /c
# ADD CPP /nologo /MDd /W3 /Gm /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_WINDLL" /D "_MBCS" /D "_USRDLL" /Yu"stdafx.h" /c
CPP_PROJ=/nologo /MDd /W3 /Gm /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS"\
 /D "_WINDLL" /D "_MBCS" /D "_USRDLL" /Fp"$(INTDIR)/DSConn.pch" /Yu"stdafx.h"\
 /Fo"$(INTDIR)/" /Fd"$(INTDIR)/" /c 
CPP_OBJS=.\Debug/
CPP_SBRS=.\.
# ADD BASE MTL /nologo /D "_DEBUG" /win32
# ADD MTL /nologo /D "_DEBUG" /win32
MTL_PROJ=/nologo /D "_DEBUG" /win32 
# ADD BASE RSC /l 0x409 /d "_DEBUG"
# ADD RSC /l 0x409 /d "_DEBUG"
RSC_PROJ=/l 0x409 /fo"$(INTDIR)/DSConn.res" /d "_DEBUG" 
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
BSC32_FLAGS=/nologo /o"$(OUTDIR)/DSConn.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /dll /debug /machine:I386
# ADD LINK32 activeds.lib /nologo /subsystem:windows /dll /debug /machine:I386
LINK32_FLAGS=activeds.lib /nologo /subsystem:windows /dll /incremental:yes\
 /pdb:"$(OUTDIR)/DSConn.pdb" /debug /machine:I386 /def:".\DSConn.def"\
 /out:"$(OUTDIR)/DSConn.dll" /implib:"$(OUTDIR)/DSConn.lib" 
DEF_FILE= \
	".\DSConn.def"
LINK32_OBJS= \
	"$(INTDIR)\dscnobj.obj" \
	"$(INTDIR)\DSConn.obj" \
	"$(INTDIR)\DSConn.res" \
	"$(INTDIR)\StdAfx.obj"

"$(OUTDIR)\DSConn.dll" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

# Begin Custom Build
OutDir=.\Debug
TargetPath=.\Debug\DSConn.dll
InputPath=.\Debug\DSConn.dll
SOURCE=$(InputPath)

"$(OutDir)\regsvr32.trg" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   regsvr32 /s /c "$(TargetPath)"
   echo regsvr32 exec. time > "$(OutDir)\regsvr32.trg"

# End Custom Build

!ELSEIF  "$(CFG)" == "DSConn - Win32 Unicode Release"

# PROP BASE Use_MFC 1
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "Unicode Release"
# PROP BASE Intermediate_Dir "Unicode Release"
# PROP BASE Target_Dir ""
# PROP Use_MFC 1
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "ReleaseU"
# PROP Intermediate_Dir "ReleaseU"
# PROP Target_Dir ""
OUTDIR=.\ReleaseU
INTDIR=.\ReleaseU
# Begin Custom Macros
OutDir=.\ReleaseU
# End Custom Macros

ALL : "$(OUTDIR)\DSConn.dll" "$(OUTDIR)\regsvr32.trg" ".\DSConn.tlb"

CLEAN : 
	-@erase "$(INTDIR)\dscnobj.obj"
	-@erase "$(INTDIR)\DSConn.obj"
	-@erase "$(INTDIR)\DSConn.pch"
	-@erase "$(INTDIR)\DSConn.res"
	-@erase "$(INTDIR)\StdAfx.obj"
	-@erase "$(OUTDIR)\DSConn.dll"
	-@erase "$(OUTDIR)\DSConn.exp"
	-@erase "$(OUTDIR)\DSConn.lib"
	-@erase "$(OUTDIR)\regsvr32.trg"
	-@erase ".\DSConn.h"
	-@erase ".\DSConn.tlb"
	-@erase ".\DSConn_i.c"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

# ADD BASE CPP /nologo /MT /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_WINDLL" /D "_MBCS" /D "_USRDLL" /Yu"stdafx.h" /c
# ADD CPP /nologo /MD /W3 /GX /O2 /D "NDEBUG" /D "WIN32" /D "_WINDOWS" /D "_WINDLL" /D "_MBCS" /D "_USRDLL" /D "_UNICODE" /Yu"stdafx.h" /c
CPP_PROJ=/nologo /MD /W3 /GX /O2 /D "NDEBUG" /D "WIN32" /D "_WINDOWS" /D\
 "_WINDLL" /D "_MBCS" /D "_USRDLL" /D "_UNICODE" /Fp"$(INTDIR)/DSConn.pch"\
 /Yu"stdafx.h" /Fo"$(INTDIR)/" /c 
CPP_OBJS=.\ReleaseU/
CPP_SBRS=.\.
# ADD BASE MTL /nologo /D "NDEBUG" /win32
# ADD MTL /nologo /D "NDEBUG" /win32
MTL_PROJ=/nologo /D "NDEBUG" /win32 
# ADD BASE RSC /l 0x409 /d "NDEBUG"
# ADD RSC /l 0x409 /d "NDEBUG"
RSC_PROJ=/l 0x409 /fo"$(INTDIR)/DSConn.res" /d "NDEBUG" 
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
BSC32_FLAGS=/nologo /o"$(OUTDIR)/DSConn.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /dll /machine:I386
# ADD LINK32 activeds.lib /nologo /subsystem:windows /dll /machine:I386
LINK32_FLAGS=activeds.lib /nologo /subsystem:windows /dll /incremental:no\
 /pdb:"$(OUTDIR)/DSConn.pdb" /machine:I386 /def:".\DSConn.def"\
 /out:"$(OUTDIR)/DSConn.dll" /implib:"$(OUTDIR)/DSConn.lib" 
DEF_FILE= \
	".\DSConn.def"
LINK32_OBJS= \
	"$(INTDIR)\dscnobj.obj" \
	"$(INTDIR)\DSConn.obj" \
	"$(INTDIR)\DSConn.res" \
	"$(INTDIR)\StdAfx.obj"

"$(OUTDIR)\DSConn.dll" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

# Begin Custom Build
OutDir=.\ReleaseU
TargetPath=.\ReleaseU\DSConn.dll
InputPath=.\ReleaseU\DSConn.dll
SOURCE=$(InputPath)

"$(OutDir)\regsvr32.trg" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   regsvr32 /s /c "$(TargetPath)"
   echo regsvr32 exec. time > "$(OutDir)\regsvr32.trg"

# End Custom Build

!ELSEIF  "$(CFG)" == "DSConn - Win32 Unicode Debug"

# PROP BASE Use_MFC 1
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "Unicode Debug"
# PROP BASE Intermediate_Dir "Unicode Debug"
# PROP BASE Target_Dir ""
# PROP Use_MFC 1
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "DebugU"
# PROP Intermediate_Dir "DebugU"
# PROP Target_Dir ""
OUTDIR=.\DebugU
INTDIR=.\DebugU
# Begin Custom Macros
OutDir=.\DebugU
# End Custom Macros

ALL : "$(OUTDIR)\DSConn.dll" "$(OUTDIR)\regsvr32.trg" ".\DSConn.tlb"

CLEAN : 
	-@erase "$(INTDIR)\dscnobj.obj"
	-@erase "$(INTDIR)\DSConn.obj"
	-@erase "$(INTDIR)\DSConn.pch"
	-@erase "$(INTDIR)\DSConn.res"
	-@erase "$(INTDIR)\StdAfx.obj"
	-@erase "$(INTDIR)\vc40.idb"
	-@erase "$(INTDIR)\vc40.pdb"
	-@erase "$(OUTDIR)\DSConn.dll"
	-@erase "$(OUTDIR)\DSConn.exp"
	-@erase "$(OUTDIR)\DSConn.ilk"
	-@erase "$(OUTDIR)\DSConn.lib"
	-@erase "$(OUTDIR)\DSConn.pdb"
	-@erase "$(OUTDIR)\regsvr32.trg"
	-@erase ".\DSConn.h"
	-@erase ".\DSConn.tlb"
	-@erase ".\DSConn_i.c"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

# ADD BASE CPP /nologo /MTd /W3 /Gm /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_WINDLL" /D "_MBCS" /D "_USRDLL" /Yu"stdafx.h" /c
# ADD CPP /nologo /MDd /W3 /Gm /GX /Zi /Od /D "_DEBUG" /D "WIN32" /D "_WINDOWS" /D "_WINDLL" /D "_MBCS" /D "_USRDLL" /D "_UNICODE" /Yu"stdafx.h" /c
CPP_PROJ=/nologo /MDd /W3 /Gm /GX /Zi /Od /D "_DEBUG" /D "WIN32" /D "_WINDOWS"\
 /D "_WINDLL" /D "_MBCS" /D "_USRDLL" /D "_UNICODE" /Fp"$(INTDIR)/DSConn.pch"\
 /Yu"stdafx.h" /Fo"$(INTDIR)/" /Fd"$(INTDIR)/" /c 
CPP_OBJS=.\DebugU/
CPP_SBRS=.\.
# ADD BASE MTL /nologo /D "_DEBUG" /win32
# ADD MTL /nologo /D "_DEBUG" /win32
MTL_PROJ=/nologo /D "_DEBUG" /win32 
# ADD BASE RSC /l 0x409 /d "_DEBUG"
# ADD RSC /l 0x409 /d "_DEBUG"
RSC_PROJ=/l 0x409 /fo"$(INTDIR)/DSConn.res" /d "_DEBUG" 
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
BSC32_FLAGS=/nologo /o"$(OUTDIR)/DSConn.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /dll /debug /machine:I386
# ADD LINK32 activeds.lib /nologo /subsystem:windows /dll /debug /machine:I386
LINK32_FLAGS=activeds.lib /nologo /subsystem:windows /dll /incremental:yes\
 /pdb:"$(OUTDIR)/DSConn.pdb" /debug /machine:I386 /def:".\DSConn.def"\
 /out:"$(OUTDIR)/DSConn.dll" /implib:"$(OUTDIR)/DSConn.lib" 
DEF_FILE= \
	".\DSConn.def"
LINK32_OBJS= \
	"$(INTDIR)\dscnobj.obj" \
	"$(INTDIR)\DSConn.obj" \
	"$(INTDIR)\DSConn.res" \
	"$(INTDIR)\StdAfx.obj"

"$(OUTDIR)\DSConn.dll" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

# Begin Custom Build
OutDir=.\DebugU
TargetPath=.\DebugU\DSConn.dll
InputPath=.\DebugU\DSConn.dll
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

# Name "DSConn - Win32 Release"
# Name "DSConn - Win32 Debug"
# Name "DSConn - Win32 Unicode Release"
# Name "DSConn - Win32 Unicode Debug"

!IF  "$(CFG)" == "DSConn - Win32 Release"

!ELSEIF  "$(CFG)" == "DSConn - Win32 Debug"

!ELSEIF  "$(CFG)" == "DSConn - Win32 Unicode Release"

!ELSEIF  "$(CFG)" == "DSConn - Win32 Unicode Debug"

!ENDIF 

################################################################################
# Begin Source File

SOURCE=.\StdAfx.cpp
DEP_CPP_STDAF=\
	".\StdAfx.h"\
	{$(INCLUDE)}"\atlbase.h"\
	{$(INCLUDE)}"\atlcom.h"\
	{$(INCLUDE)}"\atlimpl.cpp"\
	

!IF  "$(CFG)" == "DSConn - Win32 Release"

# ADD CPP /Yc"stdafx.h"

BuildCmds= \
	$(CPP) /nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D\
 "_WINDLL" /D "_MBCS" /D "_USRDLL" /Fp"$(INTDIR)/DSConn.pch" /Yc"stdafx.h"\
 /Fo"$(INTDIR)/" /c $(SOURCE) \
	

"$(INTDIR)\StdAfx.obj" : $(SOURCE) $(DEP_CPP_STDAF) "$(INTDIR)"
   $(BuildCmds)

"$(INTDIR)\DSConn.pch" : $(SOURCE) $(DEP_CPP_STDAF) "$(INTDIR)"
   $(BuildCmds)

!ELSEIF  "$(CFG)" == "DSConn - Win32 Debug"

# ADD CPP /Yc"stdafx.h"

BuildCmds= \
	$(CPP) /nologo /MDd /W3 /Gm /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS"\
 /D "_WINDLL" /D "_MBCS" /D "_USRDLL" /Fp"$(INTDIR)/DSConn.pch" /Yc"stdafx.h"\
 /Fo"$(INTDIR)/" /Fd"$(INTDIR)/" /c $(SOURCE) \
	

"$(INTDIR)\StdAfx.obj" : $(SOURCE) $(DEP_CPP_STDAF) "$(INTDIR)"
   $(BuildCmds)

"$(INTDIR)\DSConn.pch" : $(SOURCE) $(DEP_CPP_STDAF) "$(INTDIR)"
   $(BuildCmds)

!ELSEIF  "$(CFG)" == "DSConn - Win32 Unicode Release"

# ADD BASE CPP /Yc"stdafx.h"
# ADD CPP /Yc"stdafx.h"

BuildCmds= \
	$(CPP) /nologo /MD /W3 /GX /O2 /D "NDEBUG" /D "WIN32" /D "_WINDOWS" /D\
 "_WINDLL" /D "_MBCS" /D "_USRDLL" /D "_UNICODE" /Fp"$(INTDIR)/DSConn.pch"\
 /Yc"stdafx.h" /Fo"$(INTDIR)/" /c $(SOURCE) \
	

"$(INTDIR)\StdAfx.obj" : $(SOURCE) $(DEP_CPP_STDAF) "$(INTDIR)"
   $(BuildCmds)

"$(INTDIR)\DSConn.pch" : $(SOURCE) $(DEP_CPP_STDAF) "$(INTDIR)"
   $(BuildCmds)

!ELSEIF  "$(CFG)" == "DSConn - Win32 Unicode Debug"

# ADD BASE CPP /Yc"stdafx.h"
# ADD CPP /Yc"stdafx.h"

BuildCmds= \
	$(CPP) /nologo /MDd /W3 /Gm /GX /Zi /Od /D "_DEBUG" /D "WIN32" /D "_WINDOWS"\
 /D "_WINDLL" /D "_MBCS" /D "_USRDLL" /D "_UNICODE" /Fp"$(INTDIR)/DSConn.pch"\
 /Yc"stdafx.h" /Fo"$(INTDIR)/" /Fd"$(INTDIR)/" /c $(SOURCE) \
	

"$(INTDIR)\StdAfx.obj" : $(SOURCE) $(DEP_CPP_STDAF) "$(INTDIR)"
   $(BuildCmds)

"$(INTDIR)\DSConn.pch" : $(SOURCE) $(DEP_CPP_STDAF) "$(INTDIR)"
   $(BuildCmds)

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\DSConn.cpp
DEP_CPP_DSCON=\
	".\DSCnObj.h"\
	".\DSConn.h"\
	".\DSConn_i.c"\
	".\StdAfx.h"\
	{$(INCLUDE)}"\atlbase.h"\
	{$(INCLUDE)}"\atlcom.h"\
	

!IF  "$(CFG)" == "DSConn - Win32 Release"


"$(INTDIR)\DSConn.obj" : $(SOURCE) $(DEP_CPP_DSCON) "$(INTDIR)"\
 "$(INTDIR)\DSConn.pch" ".\DSConn.h" ".\DSConn_i.c"


!ELSEIF  "$(CFG)" == "DSConn - Win32 Debug"


"$(INTDIR)\DSConn.obj" : $(SOURCE) $(DEP_CPP_DSCON) "$(INTDIR)"\
 "$(INTDIR)\DSConn.pch" ".\DSConn.h" ".\DSConn_i.c"


!ELSEIF  "$(CFG)" == "DSConn - Win32 Unicode Release"


"$(INTDIR)\DSConn.obj" : $(SOURCE) $(DEP_CPP_DSCON) "$(INTDIR)"\
 "$(INTDIR)\DSConn.pch" ".\DSConn.h" ".\DSConn_i.c"


!ELSEIF  "$(CFG)" == "DSConn - Win32 Unicode Debug"


"$(INTDIR)\DSConn.obj" : $(SOURCE) $(DEP_CPP_DSCON) "$(INTDIR)"\
 "$(INTDIR)\DSConn.pch" ".\DSConn.h" ".\DSConn_i.c"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\DSConn.def

!IF  "$(CFG)" == "DSConn - Win32 Release"

!ELSEIF  "$(CFG)" == "DSConn - Win32 Debug"

!ELSEIF  "$(CFG)" == "DSConn - Win32 Unicode Release"

!ELSEIF  "$(CFG)" == "DSConn - Win32 Unicode Debug"

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\DSConn.rc

!IF  "$(CFG)" == "DSConn - Win32 Release"

NODEP_RSC_DSCONN=\
	".\Release\DSConn.tlb"\
	

"$(INTDIR)\DSConn.res" : $(SOURCE) "$(INTDIR)"
   $(RSC) $(RSC_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "DSConn - Win32 Debug"

NODEP_RSC_DSCONN=\
	".\Debug\DSConn.tlb"\
	

"$(INTDIR)\DSConn.res" : $(SOURCE) "$(INTDIR)"
   $(RSC) $(RSC_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "DSConn - Win32 Unicode Release"

NODEP_RSC_DSCONN=\
	".\ReleaseU\DSConn.tlb"\
	

"$(INTDIR)\DSConn.res" : $(SOURCE) "$(INTDIR)"
   $(RSC) $(RSC_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "DSConn - Win32 Unicode Debug"

NODEP_RSC_DSCONN=\
	".\DebugU\DSConn.tlb"\
	

"$(INTDIR)\DSConn.res" : $(SOURCE) "$(INTDIR)"
   $(RSC) $(RSC_PROJ) $(SOURCE)


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\DSConn.idl

!IF  "$(CFG)" == "DSConn - Win32 Release"

# Begin Custom Build
InputPath=.\DSConn.idl

BuildCmds= \
	midl DSConn.idl \
	

"DSConn.tlb" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"DSConn.h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"DSConn_i.c" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)
# End Custom Build

!ELSEIF  "$(CFG)" == "DSConn - Win32 Debug"

# Begin Custom Build
InputPath=.\DSConn.idl

BuildCmds= \
	midl DSConn.idl \
	

"DSConn.tlb" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"DSConn.h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"DSConn_i.c" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)
# End Custom Build

!ELSEIF  "$(CFG)" == "DSConn - Win32 Unicode Release"

# Begin Custom Build
InputPath=.\DSConn.idl

BuildCmds= \
	midl DSConn.idl \
	

"DSConn.tlb" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"DSConn.h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"DSConn_i.c" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)
# End Custom Build

!ELSEIF  "$(CFG)" == "DSConn - Win32 Unicode Debug"

# Begin Custom Build
InputPath=.\DSConn.idl

BuildCmds= \
	midl DSConn.idl \
	

"DSConn.tlb" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"DSConn.h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"DSConn_i.c" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)
# End Custom Build

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\dscnobj.cpp
DEP_CPP_DSCNO=\
	{$(INCLUDE)}"adserr.h"\
	{$(INCLUDE)}"adshlp.h"\
	{$(INCLUDE)}"adsiid.h"\
	{$(INCLUDE)}"adsnms.h"\
	{$(INCLUDE)}"adssts.h"\
	{$(INCLUDE)}"iads.h"\
	".\DSCnObj.h"\
	".\DSConn.h"\
	".\StdAfx.h"\
	{$(INCLUDE)}"\activeds.h"\
	{$(INCLUDE)}"\atlbase.h"\
	{$(INCLUDE)}"\atlcom.h"\
	

!IF  "$(CFG)" == "DSConn - Win32 Release"


"$(INTDIR)\dscnobj.obj" : $(SOURCE) $(DEP_CPP_DSCNO) "$(INTDIR)"\
 "$(INTDIR)\DSConn.pch" ".\DSConn.h"


!ELSEIF  "$(CFG)" == "DSConn - Win32 Debug"


"$(INTDIR)\dscnobj.obj" : $(SOURCE) $(DEP_CPP_DSCNO) "$(INTDIR)"\
 "$(INTDIR)\DSConn.pch" ".\DSConn.h"


!ELSEIF  "$(CFG)" == "DSConn - Win32 Unicode Release"


"$(INTDIR)\dscnobj.obj" : $(SOURCE) $(DEP_CPP_DSCNO) "$(INTDIR)"\
 "$(INTDIR)\DSConn.pch" ".\DSConn.h"


!ELSEIF  "$(CFG)" == "DSConn - Win32 Unicode Debug"


"$(INTDIR)\dscnobj.obj" : $(SOURCE) $(DEP_CPP_DSCNO) "$(INTDIR)"\
 "$(INTDIR)\DSConn.pch" ".\DSConn.h"


!ENDIF 

# End Source File
# End Target
# End Project
################################################################################
