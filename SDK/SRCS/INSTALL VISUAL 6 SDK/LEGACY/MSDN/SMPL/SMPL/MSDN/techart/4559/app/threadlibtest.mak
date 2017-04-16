# Microsoft Developer Studio Generated NMAKE File, Format Version 4.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Application" 0x0101

!IF "$(CFG)" == ""
CFG=threadlibtest - Win32 Debug
!MESSAGE No configuration specified.  Defaulting to threadlibtest - Win32\
 Debug.
!ENDIF 

!IF "$(CFG)" != "threadlibtest - Win32 Release" && "$(CFG)" !=\
 "threadlibtest - Win32 Debug"
!MESSAGE Invalid configuration "$(CFG)" specified.
!MESSAGE You can specify a configuration when running NMAKE on this makefile
!MESSAGE by defining the macro CFG on the command line.  For example:
!MESSAGE 
!MESSAGE NMAKE /f "threadlibtest.mak" CFG="threadlibtest - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "threadlibtest - Win32 Release" (based on "Win32 (x86) Application")
!MESSAGE "threadlibtest - Win32 Debug" (based on "Win32 (x86) Application")
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
# PROP Target_Last_Scanned "threadlibtest - Win32 Debug"
RSC=rc.exe
CPP=cl.exe
MTL=mktyplib.exe

!IF  "$(CFG)" == "threadlibtest - Win32 Release"

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

ALL : "$(OUTDIR)\threadlibtest.exe" "$(OUTDIR)\threadlibtest.pch"

CLEAN : 
	-@erase ".\Release\threadlibtest.pch"
	-@erase ".\Release\threadlibtest.exe"
	-@erase ".\Release\easyview.obj"
	-@erase ".\Release\xl5en32.obj"
	-@erase ".\Release\NoThreadDialog.obj"
	-@erase ".\Release\threadlibtestView.obj"
	-@erase ".\Release\threadlibtestDoc.obj"
	-@erase ".\Release\StdAfx.obj"
	-@erase ".\Release\MainFrm.obj"
	-@erase ".\Release\threadlibtest.obj"
	-@erase ".\Release\threadlibtest.res"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

# ADD BASE CPP /nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /Yu"stdafx.h" /c
# ADD CPP /nologo /G4 /MT /W3 /GX /Od /I "d:\projects\thrdlib" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /YX /c
CPP_PROJ=/nologo /G4 /MT /W3 /GX /Od /I "d:\projects\thrdlib" /D "WIN32" /D\
 "NDEBUG" /D "_WINDOWS" /Fp"$(INTDIR)/threadlibtest.pch" /YX /Fo"$(INTDIR)/" /c 
CPP_OBJS=.\Release/
CPP_SBRS=
# ADD BASE MTL /nologo /D "NDEBUG" /win32
# ADD MTL /nologo /D "NDEBUG" /win32
MTL_PROJ=/nologo /D "NDEBUG" /win32 
# ADD BASE RSC /l 0x409 /d "NDEBUG" /d "_AFXDLL"
# ADD RSC /l 0x409 /d "NDEBUG"
RSC_PROJ=/l 0x409 /fo"$(INTDIR)/threadlibtest.res" /d "NDEBUG" 
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
BSC32_FLAGS=/nologo /o"$(OUTDIR)/threadlibtest.bsc" 
BSC32_SBRS=
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /machine:I386
# ADD LINK32 winmm.lib d:\projects\thrdlib\release\thrdlib.lib /nologo /subsystem:windows /machine:I386
LINK32_FLAGS=winmm.lib d:\projects\thrdlib\release\thrdlib.lib /nologo\
 /subsystem:windows /incremental:no /pdb:"$(OUTDIR)/threadlibtest.pdb"\
 /machine:I386 /out:"$(OUTDIR)/threadlibtest.exe" 
LINK32_OBJS= \
	"$(INTDIR)/easyview.obj" \
	"$(INTDIR)/xl5en32.obj" \
	"$(INTDIR)/NoThreadDialog.obj" \
	"$(INTDIR)/threadlibtestView.obj" \
	"$(INTDIR)/threadlibtestDoc.obj" \
	"$(INTDIR)/StdAfx.obj" \
	"$(INTDIR)/MainFrm.obj" \
	"$(INTDIR)/threadlibtest.obj" \
	"$(INTDIR)/threadlibtest.res"

"$(OUTDIR)\threadlibtest.exe" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ELSEIF  "$(CFG)" == "threadlibtest - Win32 Debug"

# PROP BASE Use_MFC 6
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "Debug"
# PROP BASE Intermediate_Dir "Debug"
# PROP BASE Target_Dir ""
# PROP Use_MFC 6
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "Debug"
# PROP Intermediate_Dir "Debug"
# PROP Target_Dir ""
OUTDIR=.\Debug
INTDIR=.\Debug

ALL : "$(OUTDIR)\threadlibtest.exe" "$(OUTDIR)\threadlibtest.pch"

CLEAN : 
	-@erase ".\Debug\vc40.pdb"
	-@erase ".\Debug\vc40.idb"
	-@erase ".\Debug\threadlibtest.pch"
	-@erase ".\Debug\threadlibtest.exe"
	-@erase ".\Debug\threadlibtest.obj"
	-@erase ".\Debug\easyview.obj"
	-@erase ".\Debug\threadlibtestDoc.obj"
	-@erase ".\Debug\threadlibtestView.obj"
	-@erase ".\Debug\NoThreadDialog.obj"
	-@erase ".\Debug\xl5en32.obj"
	-@erase ".\Debug\StdAfx.obj"
	-@erase ".\Debug\MainFrm.obj"
	-@erase ".\Debug\threadlibtest.res"
	-@erase ".\Debug\threadlibtest.ilk"
	-@erase ".\Debug\threadlibtest.pdb"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

# ADD BASE CPP /nologo /MDd /W3 /Gm /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /Yu"stdafx.h" /c
# ADD CPP /nologo /G4 /MTd /W3 /Gm /GX /Zi /Od /I "d:\projects\thrdlib" /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /FAcs /YX /c
CPP_PROJ=/nologo /G4 /MTd /W3 /Gm /GX /Zi /Od /I "d:\projects\thrdlib" /D\
 "WIN32" /D "_DEBUG" /D "_WINDOWS" /FAcs /Fa"$(INTDIR)/"\
 /Fp"$(INTDIR)/threadlibtest.pch" /YX /Fo"$(INTDIR)/" /Fd"$(INTDIR)/" /c 
CPP_OBJS=.\Debug/
CPP_SBRS=
# ADD BASE MTL /nologo /D "_DEBUG" /win32
# ADD MTL /nologo /D "_DEBUG" /win32
MTL_PROJ=/nologo /D "_DEBUG" /win32 
# ADD BASE RSC /l 0x409 /d "_DEBUG" /d "_AFXDLL"
# ADD RSC /l 0x409 /d "_DEBUG"
RSC_PROJ=/l 0x409 /fo"$(INTDIR)/threadlibtest.res" /d "_DEBUG" 
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
BSC32_FLAGS=/nologo /o"$(OUTDIR)/threadlibtest.bsc" 
BSC32_SBRS=
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /debug /machine:I386
# ADD LINK32 kernel32.lib user32.lib gdi32.lib winmm.lib d:\projects\thrdlib\debug\thrdlib.lib /nologo /subsystem:windows /debug /machine:I386
# SUBTRACT LINK32 /nodefaultlib
LINK32_FLAGS=kernel32.lib user32.lib gdi32.lib winmm.lib\
 d:\projects\thrdlib\debug\thrdlib.lib /nologo /subsystem:windows\
 /incremental:yes /pdb:"$(OUTDIR)/threadlibtest.pdb" /debug /machine:I386\
 /out:"$(OUTDIR)/threadlibtest.exe" 
LINK32_OBJS= \
	"$(INTDIR)/threadlibtest.obj" \
	"$(INTDIR)/easyview.obj" \
	"$(INTDIR)/threadlibtestDoc.obj" \
	"$(INTDIR)/threadlibtestView.obj" \
	"$(INTDIR)/NoThreadDialog.obj" \
	"$(INTDIR)/xl5en32.obj" \
	"$(INTDIR)/StdAfx.obj" \
	"$(INTDIR)/MainFrm.obj" \
	"$(INTDIR)/threadlibtest.res"

"$(OUTDIR)\threadlibtest.exe" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
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

# Name "threadlibtest - Win32 Release"
# Name "threadlibtest - Win32 Debug"

!IF  "$(CFG)" == "threadlibtest - Win32 Release"

!ELSEIF  "$(CFG)" == "threadlibtest - Win32 Debug"

!ENDIF 

################################################################################
# Begin Source File

SOURCE=.\threadlibtest.cpp
DEP_CPP_THREA=\
	".\StdAfx.h"\
	".\threadlibtest.h"\
	".\MainFrm.h"\
	".\easyview.h"\
	".\threadlibtestDoc.h"\
	".\threadlibtestView.h"\
	

"$(INTDIR)\threadlibtest.obj" : $(SOURCE) $(DEP_CPP_THREA) "$(INTDIR)"


# End Source File
################################################################################
# Begin Source File

SOURCE=.\StdAfx.cpp
DEP_CPP_STDAF=\
	".\StdAfx.h"\
	

!IF  "$(CFG)" == "threadlibtest - Win32 Release"

# ADD CPP /Yc"stdafx.h"

BuildCmds= \
	$(CPP) /nologo /G4 /MT /W3 /GX /Od /I "d:\projects\thrdlib" /D "WIN32" /D\
 "NDEBUG" /D "_WINDOWS" /Fp"$(INTDIR)/threadlibtest.pch" /Yc"stdafx.h"\
 /Fo"$(INTDIR)/" /c $(SOURCE) \
	

"$(INTDIR)\StdAfx.obj" : $(SOURCE) $(DEP_CPP_STDAF) "$(INTDIR)"
   $(BuildCmds)

"$(INTDIR)\threadlibtest.pch" : $(SOURCE) $(DEP_CPP_STDAF) "$(INTDIR)"
   $(BuildCmds)

!ELSEIF  "$(CFG)" == "threadlibtest - Win32 Debug"

# ADD CPP /Yc"stdafx.h"

BuildCmds= \
	$(CPP) /nologo /G4 /MTd /W3 /Gm /GX /Zi /Od /I "d:\projects\thrdlib" /D\
 "WIN32" /D "_DEBUG" /D "_WINDOWS" /FAcs /Fa"$(INTDIR)/"\
 /Fp"$(INTDIR)/threadlibtest.pch" /Yc"stdafx.h" /Fo"$(INTDIR)/" /Fd"$(INTDIR)/"\
 /c $(SOURCE) \
	

"$(INTDIR)\StdAfx.obj" : $(SOURCE) $(DEP_CPP_STDAF) "$(INTDIR)"
   $(BuildCmds)

"$(INTDIR)\threadlibtest.pch" : $(SOURCE) $(DEP_CPP_STDAF) "$(INTDIR)"
   $(BuildCmds)

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\MainFrm.cpp
DEP_CPP_MAINF=\
	".\StdAfx.h"\
	".\threadlibtest.h"\
	".\MainFrm.h"\
	

"$(INTDIR)\MainFrm.obj" : $(SOURCE) $(DEP_CPP_MAINF) "$(INTDIR)"


# End Source File
################################################################################
# Begin Source File

SOURCE=.\threadlibtestDoc.cpp
DEP_CPP_THREAD=\
	".\StdAfx.h"\
	".\threadlibtest.h"\
	".\threadlibtestDoc.h"\
	

"$(INTDIR)\threadlibtestDoc.obj" : $(SOURCE) $(DEP_CPP_THREAD) "$(INTDIR)"


# End Source File
################################################################################
# Begin Source File

SOURCE=.\threadlibtestView.cpp
DEP_CPP_THREADL=\
	".\StdAfx.h"\
	".\easyview.h"\
	".\threadlibtest.h"\
	".\threadlibtestDoc.h"\
	".\threadlibtestView.h"\
	".\NoThreadDialog.h"\
	".\xl5en32.h"\
	"d:\projects\thrdlib\thrdlib.h"\
	

"$(INTDIR)\threadlibtestView.obj" : $(SOURCE) $(DEP_CPP_THREADL) "$(INTDIR)"


# End Source File
################################################################################
# Begin Source File

SOURCE=.\threadlibtest.rc
DEP_RSC_THREADLI=\
	".\res\threadlibtest.ico"\
	".\res\threadlibtestDoc.ico"\
	".\res\threadlibtest.rc2"\
	

"$(INTDIR)\threadlibtest.res" : $(SOURCE) $(DEP_RSC_THREADLI) "$(INTDIR)"
   $(RSC) $(RSC_PROJ) $(SOURCE)


# End Source File
################################################################################
# Begin Source File

SOURCE=.\easyview.cpp
DEP_CPP_EASYV=\
	".\StdAfx.h"\
	".\easyview.h"\
	

"$(INTDIR)\easyview.obj" : $(SOURCE) $(DEP_CPP_EASYV) "$(INTDIR)"


# End Source File
################################################################################
# Begin Source File

SOURCE=.\NoThreadDialog.cpp
DEP_CPP_NOTHR=\
	".\StdAfx.h"\
	".\threadlibtest.h"\
	".\NoThreadDialog.h"\
	

"$(INTDIR)\NoThreadDialog.obj" : $(SOURCE) $(DEP_CPP_NOTHR) "$(INTDIR)"


# End Source File
################################################################################
# Begin Source File

SOURCE=.\xl5en32.cpp
DEP_CPP_XL5EN=\
	".\StdAfx.h"\
	".\xl5en32.h"\
	

"$(INTDIR)\xl5en32.obj" : $(SOURCE) $(DEP_CPP_XL5EN) "$(INTDIR)"


# End Source File
# End Target
# End Project
################################################################################
