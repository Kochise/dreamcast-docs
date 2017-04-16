# Microsoft Developer Studio Generated NMAKE File, Format Version 4.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Application" 0x0101

!IF "$(CFG)" == ""
CFG=ShellRun - Win32 Debug
!MESSAGE No configuration specified.  Defaulting to ShellRun - Win32 Debug.
!ENDIF 

!IF "$(CFG)" != "ShellRun - Win32 Release" && "$(CFG)" !=\
 "ShellRun - Win32 Debug"
!MESSAGE Invalid configuration "$(CFG)" specified.
!MESSAGE You can specify a configuration when running NMAKE on this makefile
!MESSAGE by defining the macro CFG on the command line.  For example:
!MESSAGE 
!MESSAGE NMAKE /f "SHELLRUN.MAK" CFG="ShellRun - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "ShellRun - Win32 Release" (based on "Win32 (x86) Application")
!MESSAGE "ShellRun - Win32 Debug" (based on "Win32 (x86) Application")
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
# PROP Target_Last_Scanned "ShellRun - Win32 Debug"
RSC=rc.exe
MTL=mktyplib.exe
CPP=cl.exe

!IF  "$(CFG)" == "ShellRun - Win32 Release"

# PROP BASE Use_MFC 6
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "Release"
# PROP BASE Intermediate_Dir "Release"
# PROP BASE Target_Dir ""
# PROP Use_MFC 6
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "Release"
# PROP Intermediate_Dir "Release"
# PROP Target_Dir ""
OUTDIR=.\Release
INTDIR=.\Release

ALL : "$(OUTDIR)\SHELLRUN.exe"

CLEAN : 
	-@erase ".\Release\SHELLRUN.exe"
	-@erase ".\Release\AppBar.obj"
	-@erase ".\Release\SHELLRUN.pch"
	-@erase ".\Release\ShellRun.obj"
	-@erase ".\Release\SRBar.obj"
	-@erase ".\Release\StdAfx.obj"
	-@erase ".\Release\ShellRun.res"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

# ADD BASE CPP /nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /Yu"stdafx.h" /c
# ADD CPP /nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /Yu"stdafx.h" /c
CPP_PROJ=/nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D\
 "_AFXDLL" /D "_MBCS" /Fp"$(INTDIR)/SHELLRUN.pch" /Yu"stdafx.h" /Fo"$(INTDIR)/"\
 /c 
CPP_OBJS=.\Release/
CPP_SBRS=
# ADD BASE MTL /nologo /D "NDEBUG" /win32
# ADD MTL /nologo /D "NDEBUG" /win32
MTL_PROJ=/nologo /D "NDEBUG" /win32 
# ADD BASE RSC /l 0x409 /d "NDEBUG" /d "_AFXDLL"
# ADD RSC /l 0x409 /d "NDEBUG" /d "_AFXDLL"
RSC_PROJ=/l 0x409 /fo"$(INTDIR)/ShellRun.res" /d "NDEBUG" /d "_AFXDLL" 
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
BSC32_FLAGS=/nologo /o"$(OUTDIR)/SHELLRUN.bsc" 
BSC32_SBRS=
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /machine:I386
# ADD LINK32 /nologo /subsystem:windows /machine:I386
LINK32_FLAGS=/nologo /subsystem:windows /incremental:no\
 /pdb:"$(OUTDIR)/SHELLRUN.pdb" /machine:I386 /out:"$(OUTDIR)/SHELLRUN.exe" 
LINK32_OBJS= \
	"$(INTDIR)/AppBar.obj" \
	"$(INTDIR)/ShellRun.obj" \
	"$(INTDIR)/SRBar.obj" \
	"$(INTDIR)/StdAfx.obj" \
	"$(INTDIR)/ShellRun.res"

"$(OUTDIR)\SHELLRUN.exe" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ELSEIF  "$(CFG)" == "ShellRun - Win32 Debug"

# PROP BASE Use_MFC 6
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "ShellRun_"
# PROP BASE Intermediate_Dir "ShellRun_"
# PROP BASE Target_Dir ""
# PROP Use_MFC 6
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "WinDebug"
# PROP Intermediate_Dir "WinDebug"
# PROP Target_Dir ""
OUTDIR=.\WinDebug
INTDIR=.\WinDebug

ALL : "$(OUTDIR)\SHELLRUN.exe" "$(OUTDIR)\SHELLRUN.bsc"

CLEAN : 
	-@erase ".\WinDebug\vc40.pdb"
	-@erase ".\WinDebug\SHELLRUN.pch"
	-@erase ".\WinDebug\vc40.idb"
	-@erase ".\WinDebug\SHELLRUN.bsc"
	-@erase ".\WinDebug\SRBar.sbr"
	-@erase ".\WinDebug\StdAfx.sbr"
	-@erase ".\WinDebug\ShellRun.sbr"
	-@erase ".\WinDebug\AppBar.sbr"
	-@erase ".\WinDebug\SHELLRUN.exe"
	-@erase ".\WinDebug\ShellRun.obj"
	-@erase ".\WinDebug\AppBar.obj"
	-@erase ".\WinDebug\SRBar.obj"
	-@erase ".\WinDebug\StdAfx.obj"
	-@erase ".\WinDebug\ShellRun.res"
	-@erase ".\WinDebug\SHELLRUN.ilk"
	-@erase ".\WinDebug\SHELLRUN.pdb"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

# ADD BASE CPP /nologo /MDd /W3 /Gm /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /Yu"stdafx.h" /c
# ADD CPP /nologo /Gz /MD /W3 /Gm /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /Fr /Yu"stdafx.h" /c
CPP_PROJ=/nologo /Gz /MD /W3 /Gm /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D\
 "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /Fr"$(INTDIR)/" /Fp"$(INTDIR)/SHELLRUN.pch"\
 /Yu"stdafx.h" /Fo"$(INTDIR)/" /Fd"$(INTDIR)/" /c 
CPP_OBJS=.\WinDebug/
CPP_SBRS=.\WinDebug/
# ADD BASE MTL /nologo /D "_DEBUG" /win32
# ADD MTL /nologo /D "_DEBUG" /win32
MTL_PROJ=/nologo /D "_DEBUG" /win32 
# ADD BASE RSC /l 0x409 /d "_DEBUG" /d "_AFXDLL"
# ADD RSC /l 0x409 /d "_DEBUG" /d "_AFXDLL"
RSC_PROJ=/l 0x409 /fo"$(INTDIR)/ShellRun.res" /d "_DEBUG" /d "_AFXDLL" 
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
BSC32_FLAGS=/nologo /o"$(OUTDIR)/SHELLRUN.bsc" 
BSC32_SBRS= \
	"$(INTDIR)/SRBar.sbr" \
	"$(INTDIR)/StdAfx.sbr" \
	"$(INTDIR)/ShellRun.sbr" \
	"$(INTDIR)/AppBar.sbr"

"$(OUTDIR)\SHELLRUN.bsc" : "$(OUTDIR)" $(BSC32_SBRS)
    $(BSC32) @<<
  $(BSC32_FLAGS) $(BSC32_SBRS)
<<

LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /debug /machine:I386
# ADD LINK32 /nologo /subsystem:windows /debug /machine:I386 /nodefaultlib:"msvcrtd.lib"
# SUBTRACT LINK32 /pdb:none
LINK32_FLAGS=/nologo /subsystem:windows /incremental:yes\
 /pdb:"$(OUTDIR)/SHELLRUN.pdb" /debug /machine:I386 /nodefaultlib:"msvcrtd.lib"\
 /out:"$(OUTDIR)/SHELLRUN.exe" 
LINK32_OBJS= \
	"$(INTDIR)/ShellRun.obj" \
	"$(INTDIR)/AppBar.obj" \
	"$(INTDIR)/SRBar.obj" \
	"$(INTDIR)/StdAfx.obj" \
	"$(INTDIR)/ShellRun.res"

"$(OUTDIR)\SHELLRUN.exe" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

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

# Name "ShellRun - Win32 Release"
# Name "ShellRun - Win32 Debug"

!IF  "$(CFG)" == "ShellRun - Win32 Release"

!ELSEIF  "$(CFG)" == "ShellRun - Win32 Debug"

!ENDIF 

################################################################################
# Begin Source File

SOURCE=.\ShellRun.cpp
DEP_CPP_SHELL=\
	".\AppBar.h"\
	".\ShellRun.h"\
	".\SRBar.h"\
	".\StdAfx.h"\
	

!IF  "$(CFG)" == "ShellRun - Win32 Release"


"$(INTDIR)\ShellRun.obj" : $(SOURCE) $(DEP_CPP_SHELL) "$(INTDIR)"\
 "$(INTDIR)\SHELLRUN.pch"


!ELSEIF  "$(CFG)" == "ShellRun - Win32 Debug"


"$(INTDIR)\ShellRun.obj" : $(SOURCE) $(DEP_CPP_SHELL) "$(INTDIR)"\
 "$(INTDIR)\SHELLRUN.pch"

"$(INTDIR)\ShellRun.sbr" : $(SOURCE) $(DEP_CPP_SHELL) "$(INTDIR)"\
 "$(INTDIR)\SHELLRUN.pch"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\StdAfx.cpp
DEP_CPP_STDAF=\
	".\StdAfx.h"\
	

!IF  "$(CFG)" == "ShellRun - Win32 Release"

# ADD CPP /Yc"stdafx.h"

BuildCmds= \
	$(CPP) /nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D\
 "_AFXDLL" /D "_MBCS" /Fp"$(INTDIR)/SHELLRUN.pch" /Yc"stdafx.h" /Fo"$(INTDIR)/"\
 /c $(SOURCE) \
	

"$(INTDIR)\StdAfx.obj" : $(SOURCE) $(DEP_CPP_STDAF) "$(INTDIR)"
   $(BuildCmds)

"$(INTDIR)\SHELLRUN.pch" : $(SOURCE) $(DEP_CPP_STDAF) "$(INTDIR)"
   $(BuildCmds)

!ELSEIF  "$(CFG)" == "ShellRun - Win32 Debug"

# ADD CPP /Yc"stdafx.h"

BuildCmds= \
	$(CPP) /nologo /Gz /MD /W3 /Gm /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D\
 "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /Fr"$(INTDIR)/" /Fp"$(INTDIR)/SHELLRUN.pch"\
 /Yc"stdafx.h" /Fo"$(INTDIR)/" /Fd"$(INTDIR)/" /c $(SOURCE) \
	

"$(INTDIR)\StdAfx.obj" : $(SOURCE) $(DEP_CPP_STDAF) "$(INTDIR)"
   $(BuildCmds)

"$(INTDIR)\StdAfx.sbr" : $(SOURCE) $(DEP_CPP_STDAF) "$(INTDIR)"
   $(BuildCmds)

"$(INTDIR)\SHELLRUN.pch" : $(SOURCE) $(DEP_CPP_STDAF) "$(INTDIR)"
   $(BuildCmds)

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\ShellRun.rc
DEP_RSC_SHELLR=\
	".\res\ShellRun.ico"\
	".\res\ShellRun.rc2"\
	

"$(INTDIR)\ShellRun.res" : $(SOURCE) $(DEP_RSC_SHELLR) "$(INTDIR)"
   $(RSC) $(RSC_PROJ) $(SOURCE)


# End Source File
################################################################################
# Begin Source File

SOURCE=.\AppBar.cpp

!IF  "$(CFG)" == "ShellRun - Win32 Release"

DEP_CPP_APPBA=\
	".\StdAfx.h"\
	".\AppBar.h"\
	
NODEP_CPP_APPBA=\
	".\rc"\
	

"$(INTDIR)\AppBar.obj" : $(SOURCE) $(DEP_CPP_APPBA) "$(INTDIR)"\
 "$(INTDIR)\SHELLRUN.pch"


!ELSEIF  "$(CFG)" == "ShellRun - Win32 Debug"

DEP_CPP_APPBA=\
	".\StdAfx.h"\
	".\AppBar.h"\
	

"$(INTDIR)\AppBar.obj" : $(SOURCE) $(DEP_CPP_APPBA) "$(INTDIR)"\
 "$(INTDIR)\SHELLRUN.pch"

"$(INTDIR)\AppBar.sbr" : $(SOURCE) $(DEP_CPP_APPBA) "$(INTDIR)"\
 "$(INTDIR)\SHELLRUN.pch"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\SRBar.cpp

!IF  "$(CFG)" == "ShellRun - Win32 Release"

DEP_CPP_SRBAR=\
	".\StdAfx.h"\
	".\ShellRun.h"\
	".\AppBar.h"\
	".\SRBar.h"\
	
NODEP_CPP_SRBAR=\
	".\OnInitDialog"\
	

"$(INTDIR)\SRBar.obj" : $(SOURCE) $(DEP_CPP_SRBAR) "$(INTDIR)"\
 "$(INTDIR)\SHELLRUN.pch"


!ELSEIF  "$(CFG)" == "ShellRun - Win32 Debug"

DEP_CPP_SRBAR=\
	".\AppBar.h"\
	".\ShellRun.h"\
	".\SRBar.h"\
	".\StdAfx.h"\
	

"$(INTDIR)\SRBar.obj" : $(SOURCE) $(DEP_CPP_SRBAR) "$(INTDIR)"\
 "$(INTDIR)\SHELLRUN.pch"

"$(INTDIR)\SRBar.sbr" : $(SOURCE) $(DEP_CPP_SRBAR) "$(INTDIR)"\
 "$(INTDIR)\SHELLRUN.pch"


!ENDIF 

# End Source File
# End Target
# End Project
################################################################################
