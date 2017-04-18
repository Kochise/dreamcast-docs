# Microsoft Developer Studio Generated NMAKE File, Format Version 4.10
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Application" 0x0101

!IF "$(CFG)" == ""
CFG=OCCSamp - Win32 Debug
!MESSAGE No configuration specified.  Defaulting to OCCSamp - Win32 Debug.
!ENDIF 

!IF "$(CFG)" != "OCCSamp - Win32 Release" && "$(CFG)" !=\
 "OCCSamp - Win32 Debug"
!MESSAGE Invalid configuration "$(CFG)" specified.
!MESSAGE You can specify a configuration when running NMAKE on this makefile
!MESSAGE by defining the macro CFG on the command line.  For example:
!MESSAGE 
!MESSAGE NMAKE /f "OCCSamp.mak" CFG="OCCSamp - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "OCCSamp - Win32 Release" (based on "Win32 (x86) Application")
!MESSAGE "OCCSamp - Win32 Debug" (based on "Win32 (x86) Application")
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
# PROP Target_Last_Scanned "OCCSamp - Win32 Debug"
CPP=cl.exe
RSC=rc.exe
MTL=mktyplib.exe
F90=fl32.exe

!IF  "$(CFG)" == "OCCSamp - Win32 Release"

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

ALL : "$(OUTDIR)\OCCSamp.exe" "$(OUTDIR)\OCCSamp.bsc"

CLEAN : 
	-@erase "$(INTDIR)\DocProps.obj"
	-@erase "$(INTDIR)\DocProps.sbr"
	-@erase "$(INTDIR)\MainFrm.obj"
	-@erase "$(INTDIR)\MainFrm.sbr"
	-@erase "$(INTDIR)\OCCDoc.obj"
	-@erase "$(INTDIR)\OCCDoc.sbr"
	-@erase "$(INTDIR)\OCCSamp.obj"
	-@erase "$(INTDIR)\OCCSamp.pch"
	-@erase "$(INTDIR)\OCCSamp.res"
	-@erase "$(INTDIR)\OCCSamp.sbr"
	-@erase "$(INTDIR)\OCCView.obj"
	-@erase "$(INTDIR)\OCCView.sbr"
	-@erase "$(INTDIR)\StdAfx.obj"
	-@erase "$(INTDIR)\StdAfx.sbr"
	-@erase "$(OUTDIR)\OCCSamp.bsc"
	-@erase "$(OUTDIR)\OCCSamp.exe"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

# ADD BASE F90 /Ox /I "Release/" /c /nologo
# ADD F90 /Ox /FR /I "Release/" /c /nologo
F90_PROJ=/Ox /FR"Release/" /I "Release/" /c /nologo /Fo"Release/" 
F90_OBJS=.\Release/
# ADD BASE CPP /nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /Yu"stdafx.h" /c
# ADD CPP /nologo /MD /W3 /GX /O2 /D "NDEBUG" /D "WIN32" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /FR /Yu"stdafx.h" /c
CPP_PROJ=/nologo /MD /W3 /GX /O2 /D "NDEBUG" /D "WIN32" /D "_WINDOWS" /D\
 "_AFXDLL" /D "_MBCS" /FR"$(INTDIR)/" /Fp"$(INTDIR)/OCCSamp.pch" /Yu"stdafx.h"\
 /Fo"$(INTDIR)/" /c 
CPP_OBJS=.\Release/
CPP_SBRS=.\Release/
# ADD BASE MTL /nologo /D "NDEBUG" /win32
# ADD MTL /nologo /D "NDEBUG" /win32
MTL_PROJ=/nologo /D "NDEBUG" /win32 
# ADD BASE RSC /l 0x409 /d "NDEBUG" /d "_AFXDLL"
# ADD RSC /l 0x409 /d "NDEBUG" /d "_AFXDLL"
RSC_PROJ=/l 0x409 /fo"$(INTDIR)/OCCSamp.res" /d "NDEBUG" /d "_AFXDLL" 
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
BSC32_FLAGS=/nologo /o"$(OUTDIR)/OCCSamp.bsc" 
BSC32_SBRS= \
	"$(INTDIR)\DocProps.sbr" \
	"$(INTDIR)\MainFrm.sbr" \
	"$(INTDIR)\OCCDoc.sbr" \
	"$(INTDIR)\OCCSamp.sbr" \
	"$(INTDIR)\OCCView.sbr" \
	"$(INTDIR)\StdAfx.sbr"

"$(OUTDIR)\OCCSamp.bsc" : "$(OUTDIR)" $(BSC32_SBRS)
    $(BSC32) @<<
  $(BSC32_FLAGS) $(BSC32_SBRS)
<<

LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /machine:I386
# ADD LINK32 /nologo /subsystem:windows /machine:I386
LINK32_FLAGS=/nologo /subsystem:windows /incremental:no\
 /pdb:"$(OUTDIR)/OCCSamp.pdb" /machine:I386 /out:"$(OUTDIR)/OCCSamp.exe" 
LINK32_OBJS= \
	"$(INTDIR)\DocProps.obj" \
	"$(INTDIR)\MainFrm.obj" \
	"$(INTDIR)\OCCDoc.obj" \
	"$(INTDIR)\OCCSamp.obj" \
	"$(INTDIR)\OCCSamp.res" \
	"$(INTDIR)\OCCView.obj" \
	"$(INTDIR)\StdAfx.obj"

"$(OUTDIR)\OCCSamp.exe" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ELSEIF  "$(CFG)" == "OCCSamp - Win32 Debug"

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

ALL : "$(OUTDIR)\OCCSamp.exe" "$(OUTDIR)\OCCSamp.bsc"

CLEAN : 
	-@erase "$(INTDIR)\DocProps.obj"
	-@erase "$(INTDIR)\DocProps.sbr"
	-@erase "$(INTDIR)\MainFrm.obj"
	-@erase "$(INTDIR)\MainFrm.sbr"
	-@erase "$(INTDIR)\OCCDoc.obj"
	-@erase "$(INTDIR)\OCCDoc.sbr"
	-@erase "$(INTDIR)\OCCSamp.obj"
	-@erase "$(INTDIR)\OCCSamp.pch"
	-@erase "$(INTDIR)\OCCSamp.res"
	-@erase "$(INTDIR)\OCCSamp.sbr"
	-@erase "$(INTDIR)\OCCView.obj"
	-@erase "$(INTDIR)\OCCView.sbr"
	-@erase "$(INTDIR)\StdAfx.obj"
	-@erase "$(INTDIR)\StdAfx.sbr"
	-@erase "$(INTDIR)\vc40.idb"
	-@erase "$(INTDIR)\vc40.pdb"
	-@erase "$(OUTDIR)\OCCSamp.bsc"
	-@erase "$(OUTDIR)\OCCSamp.exe"
	-@erase "$(OUTDIR)\OCCSamp.ilk"
	-@erase "$(OUTDIR)\OCCSamp.pdb"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

# ADD BASE F90 /Zi /I "Debug/" /c /nologo
# ADD F90 /FR /Zi /I "Debug/" /c /nologo
F90_PROJ=/FR"Debug/" /Zi /I "Debug/" /c /nologo /Fo"Debug/"\
 /Fd"Debug/OCCSamp.pdb" 
F90_OBJS=.\Debug/
# ADD BASE CPP /nologo /MDd /W3 /Gm /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /Yu"stdafx.h" /c
# ADD CPP /nologo /MDd /W3 /Gm /GX /Zi /Od /D "_DEBUG" /D "WIN32" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /FR /Yu"stdafx.h" /c
CPP_PROJ=/nologo /MDd /W3 /Gm /GX /Zi /Od /D "_DEBUG" /D "WIN32" /D "_WINDOWS"\
 /D "_AFXDLL" /D "_MBCS" /FR"$(INTDIR)/" /Fp"$(INTDIR)/OCCSamp.pch"\
 /Yu"stdafx.h" /Fo"$(INTDIR)/" /Fd"$(INTDIR)/" /c 
CPP_OBJS=.\Debug/
CPP_SBRS=.\Debug/
# ADD BASE MTL /nologo /D "_DEBUG" /win32
# ADD MTL /nologo /D "_DEBUG" /win32
MTL_PROJ=/nologo /D "_DEBUG" /win32 
# ADD BASE RSC /l 0x409 /d "_DEBUG" /d "_AFXDLL"
# ADD RSC /l 0x409 /d "_DEBUG" /d "_AFXDLL"
RSC_PROJ=/l 0x409 /fo"$(INTDIR)/OCCSamp.res" /d "_DEBUG" /d "_AFXDLL" 
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
BSC32_FLAGS=/nologo /o"$(OUTDIR)/OCCSamp.bsc" 
BSC32_SBRS= \
	"$(INTDIR)\DocProps.sbr" \
	"$(INTDIR)\MainFrm.sbr" \
	"$(INTDIR)\OCCDoc.sbr" \
	"$(INTDIR)\OCCSamp.sbr" \
	"$(INTDIR)\OCCView.sbr" \
	"$(INTDIR)\StdAfx.sbr"

"$(OUTDIR)\OCCSamp.bsc" : "$(OUTDIR)" $(BSC32_SBRS)
    $(BSC32) @<<
  $(BSC32_FLAGS) $(BSC32_SBRS)
<<

LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /debug /machine:I386
# ADD LINK32 /nologo /subsystem:windows /debug /machine:I386
LINK32_FLAGS=/nologo /subsystem:windows /incremental:yes\
 /pdb:"$(OUTDIR)/OCCSamp.pdb" /debug /machine:I386 /out:"$(OUTDIR)/OCCSamp.exe" 
LINK32_OBJS= \
	"$(INTDIR)\DocProps.obj" \
	"$(INTDIR)\MainFrm.obj" \
	"$(INTDIR)\OCCDoc.obj" \
	"$(INTDIR)\OCCSamp.obj" \
	"$(INTDIR)\OCCSamp.res" \
	"$(INTDIR)\OCCView.obj" \
	"$(INTDIR)\StdAfx.obj"

"$(OUTDIR)\OCCSamp.exe" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
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

.for{$(F90_OBJS)}.obj:
   $(F90) $(F90_PROJ) $<  

.f{$(F90_OBJS)}.obj:
   $(F90) $(F90_PROJ) $<  

.f90{$(F90_OBJS)}.obj:
   $(F90) $(F90_PROJ) $<  

################################################################################
# Begin Target

# Name "OCCSamp - Win32 Release"
# Name "OCCSamp - Win32 Debug"

!IF  "$(CFG)" == "OCCSamp - Win32 Release"

!ELSEIF  "$(CFG)" == "OCCSamp - Win32 Debug"

!ENDIF 

################################################################################
# Begin Source File

SOURCE=.\ReadMe.txt

!IF  "$(CFG)" == "OCCSamp - Win32 Release"

!ELSEIF  "$(CFG)" == "OCCSamp - Win32 Debug"

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\OCCSamp.cpp
DEP_CPP_OCCSA=\
	".\MainFrm.h"\
	".\msoc97.h"\
	".\OCCDoc.h"\
	".\OCCSamp.h"\
	".\OCCView.h"\
	".\StdAfx.h"\
	

"$(INTDIR)\OCCSamp.obj" : $(SOURCE) $(DEP_CPP_OCCSA) "$(INTDIR)"\
 "$(INTDIR)\OCCSamp.pch"

"$(INTDIR)\OCCSamp.sbr" : $(SOURCE) $(DEP_CPP_OCCSA) "$(INTDIR)"\
 "$(INTDIR)\OCCSamp.pch"


# End Source File
################################################################################
# Begin Source File

SOURCE=.\StdAfx.cpp
DEP_CPP_STDAF=\
	".\StdAfx.h"\
	

!IF  "$(CFG)" == "OCCSamp - Win32 Release"

# ADD CPP /Yc"stdafx.h"

BuildCmds= \
	$(CPP) /nologo /MD /W3 /GX /O2 /D "NDEBUG" /D "WIN32" /D "_WINDOWS" /D\
 "_AFXDLL" /D "_MBCS" /FR"$(INTDIR)/" /Fp"$(INTDIR)/OCCSamp.pch" /Yc"stdafx.h"\
 /Fo"$(INTDIR)/" /c $(SOURCE) \
	

"$(INTDIR)\StdAfx.obj" : $(SOURCE) $(DEP_CPP_STDAF) "$(INTDIR)"
   $(BuildCmds)

"$(INTDIR)\StdAfx.sbr" : $(SOURCE) $(DEP_CPP_STDAF) "$(INTDIR)"
   $(BuildCmds)

"$(INTDIR)\OCCSamp.pch" : $(SOURCE) $(DEP_CPP_STDAF) "$(INTDIR)"
   $(BuildCmds)

!ELSEIF  "$(CFG)" == "OCCSamp - Win32 Debug"

# ADD CPP /Yc"stdafx.h"

BuildCmds= \
	$(CPP) /nologo /MDd /W3 /Gm /GX /Zi /Od /D "_DEBUG" /D "WIN32" /D "_WINDOWS"\
 /D "_AFXDLL" /D "_MBCS" /FR"$(INTDIR)/" /Fp"$(INTDIR)/OCCSamp.pch"\
 /Yc"stdafx.h" /Fo"$(INTDIR)/" /Fd"$(INTDIR)/" /c $(SOURCE) \
	

"$(INTDIR)\StdAfx.obj" : $(SOURCE) $(DEP_CPP_STDAF) "$(INTDIR)"
   $(BuildCmds)

"$(INTDIR)\StdAfx.sbr" : $(SOURCE) $(DEP_CPP_STDAF) "$(INTDIR)"
   $(BuildCmds)

"$(INTDIR)\OCCSamp.pch" : $(SOURCE) $(DEP_CPP_STDAF) "$(INTDIR)"
   $(BuildCmds)

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\MainFrm.cpp
DEP_CPP_MAINF=\
	".\MainFrm.h"\
	".\msoc97.h"\
	".\OCCSamp.h"\
	".\StdAfx.h"\
	

"$(INTDIR)\MainFrm.obj" : $(SOURCE) $(DEP_CPP_MAINF) "$(INTDIR)"\
 "$(INTDIR)\OCCSamp.pch"

"$(INTDIR)\MainFrm.sbr" : $(SOURCE) $(DEP_CPP_MAINF) "$(INTDIR)"\
 "$(INTDIR)\OCCSamp.pch"


# End Source File
################################################################################
# Begin Source File

SOURCE=.\OCCSamp.rc
DEP_RSC_OCCSAM=\
	".\OCCDoc.ico"\
	".\OCCSamp.ico"\
	".\OCCSamp.rc2"\
	".\Toolbar.bmp"\
	

"$(INTDIR)\OCCSamp.res" : $(SOURCE) $(DEP_RSC_OCCSAM) "$(INTDIR)"
   $(RSC) $(RSC_PROJ) $(SOURCE)


# End Source File
################################################################################
# Begin Source File

SOURCE=.\DocProps.cpp
DEP_CPP_DOCPR=\
	".\DocProps.h"\
	".\msoc97.h"\
	".\OCCSamp.h"\
	".\StdAfx.h"\
	

"$(INTDIR)\DocProps.obj" : $(SOURCE) $(DEP_CPP_DOCPR) "$(INTDIR)"\
 "$(INTDIR)\OCCSamp.pch"

"$(INTDIR)\DocProps.sbr" : $(SOURCE) $(DEP_CPP_DOCPR) "$(INTDIR)"\
 "$(INTDIR)\OCCSamp.pch"


# End Source File
################################################################################
# Begin Source File

SOURCE=.\OCCView.cpp
DEP_CPP_OCCVI=\
	".\DocProps.h"\
	".\msoc97.h"\
	".\OCCDoc.h"\
	".\OCCSamp.h"\
	".\OCCView.h"\
	".\StdAfx.h"\
	

"$(INTDIR)\OCCView.obj" : $(SOURCE) $(DEP_CPP_OCCVI) "$(INTDIR)"\
 "$(INTDIR)\OCCSamp.pch"

"$(INTDIR)\OCCView.sbr" : $(SOURCE) $(DEP_CPP_OCCVI) "$(INTDIR)"\
 "$(INTDIR)\OCCSamp.pch"


# End Source File
################################################################################
# Begin Source File

SOURCE=.\OCCDoc.cpp
DEP_CPP_OCCDO=\
	".\msoc97.h"\
	".\OCCDoc.h"\
	".\OCCSamp.h"\
	".\StdAfx.h"\
	

"$(INTDIR)\OCCDoc.obj" : $(SOURCE) $(DEP_CPP_OCCDO) "$(INTDIR)"\
 "$(INTDIR)\OCCSamp.pch"

"$(INTDIR)\OCCDoc.sbr" : $(SOURCE) $(DEP_CPP_OCCDO) "$(INTDIR)"\
 "$(INTDIR)\OCCSamp.pch"


# End Source File
# End Target
# End Project
################################################################################
