# Microsoft Visual C++ Generated NMAKE File, Format Version 2.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Application" 0x0101

!IF "$(CFG)" == ""
CFG=Win32 Debug
!MESSAGE No configuration specified.  Defaulting to Win32 Debug.
!ENDIF 

!IF "$(CFG)" != "Win32 Debug" && "$(CFG)" != "Win32 Release"
!MESSAGE Invalid configuration "$(CFG)" specified.
!MESSAGE You can specify a configuration when running NMAKE on this makefile
!MESSAGE by defining the macro CFG on the command line.  For example:
!MESSAGE 
!MESSAGE NMAKE /f "EasyFont.mak" CFG="Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "Win32 Debug" (based on "Win32 (x86) Application")
!MESSAGE "Win32 Release" (based on "Win32 (x86) Application")
!MESSAGE 
!ERROR An invalid configuration is specified.
!ENDIF 

################################################################################
# Begin Project
# PROP Target_Last_Scanned "Win32 Debug"
MTL=MkTypLib.exe
CPP=cl.exe
RSC=rc.exe

!IF  "$(CFG)" == "Win32 Debug"

# PROP BASE Use_MFC 6
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "WinDebug"
# PROP BASE Intermediate_Dir "WinDebug"
# PROP Use_MFC 6
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "WinDebug"
# PROP Intermediate_Dir "WinDebug"
OUTDIR=.\WinDebug
INTDIR=.\WinDebug

ALL : $(OUTDIR)/EasyFont.exe $(OUTDIR)/EasyFont.bsc

$(OUTDIR) : 
    if not exist $(OUTDIR)/nul mkdir $(OUTDIR)

# ADD BASE CPP /nologo /MD /W3 /GX /Zi /Od /D "_DEBUG" /D "WIN32" /D "_WINDOWS" /D "_MBCS" /D "_AFXDLL" /FR /Yu"stdafx.h" /c
# ADD CPP /nologo /MD /W3 /GX /Zi /Od /D "_DEBUG" /D "WIN32" /D "_WINDOWS" /D "_MBCS" /D "_AFXDLL" /FR /Yu"stdafx.h" /c
CPP_PROJ=/nologo /MD /W3 /GX /Zi /Od /D "_DEBUG" /D "WIN32" /D "_WINDOWS" /D\
 "_MBCS" /D "_AFXDLL" /FR$(INTDIR)/ /Fp$(OUTDIR)/"EasyFont.pch" /Yu"stdafx.h"\
 /Fo$(INTDIR)/ /Fd$(OUTDIR)/"EasyFont.pdb" /c 
CPP_OBJS=.\WinDebug/
# ADD BASE RSC /l 0x409 /d "_DEBUG" /d "_AFXDLL"
# ADD RSC /l 0x409 /d "_DEBUG" /d "_AFXDLL"
RSC_PROJ=/l 0x409 /fo$(INTDIR)/"EasyFont.res" /d "_DEBUG" /d "_AFXDLL" 
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
BSC32_FLAGS=/nologo /o$(OUTDIR)/"EasyFont.bsc" 
BSC32_SBRS= \
	$(INTDIR)/stdafx.sbr \
	$(INTDIR)/EasyFont.sbr \
	$(INTDIR)/mainfrm.sbr \
	$(INTDIR)/EasyFdoc.sbr \
	$(INTDIR)/SceneVw.sbr \
	$(INTDIR)/Scene.sbr \
	$(INTDIR)/fontparamdlg.sbr

$(OUTDIR)/EasyFont.bsc : $(OUTDIR)  $(BSC32_SBRS)
    $(BSC32) @<<
  $(BSC32_FLAGS) $(BSC32_SBRS)
<<

LINK32=link.exe
# ADD BASE LINK32 /NOLOGO /SUBSYSTEM:windows /DEBUG /MACHINE:I386
# SUBTRACT BASE LINK32 /PDB:none
# ADD LINK32 GLlib-d.lib winmm.lib opengl32.lib glu32.lib glaux.lib /NOLOGO /SUBSYSTEM:windows /DEBUG /MACHINE:I386
# SUBTRACT LINK32 /PDB:none
LINK32_FLAGS=GLlib-d.lib winmm.lib opengl32.lib glu32.lib glaux.lib /NOLOGO\
 /SUBSYSTEM:windows /INCREMENTAL:yes /PDB:$(OUTDIR)/"EasyFont.pdb" /DEBUG\
 /MACHINE:I386 /OUT:$(OUTDIR)/"EasyFont.exe" 
DEF_FILE=
LINK32_OBJS= \
	$(INTDIR)/stdafx.obj \
	$(INTDIR)/EasyFont.obj \
	$(INTDIR)/mainfrm.obj \
	$(INTDIR)/EasyFdoc.obj \
	$(INTDIR)/SceneVw.obj \
	$(INTDIR)/EasyFont.res \
	$(INTDIR)/Scene.obj \
	$(INTDIR)/fontparamdlg.obj

$(OUTDIR)/EasyFont.exe : $(OUTDIR)  $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ELSEIF  "$(CFG)" == "Win32 Release"

# PROP BASE Use_MFC 6
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "WinRel"
# PROP BASE Intermediate_Dir "WinRel"
# PROP Use_MFC 6
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "WinRel"
# PROP Intermediate_Dir "WinRel"
OUTDIR=.\WinRel
INTDIR=.\WinRel

ALL : $(OUTDIR)/EasyFont.exe $(OUTDIR)/EasyFont.bsc

$(OUTDIR) : 
    if not exist $(OUTDIR)/nul mkdir $(OUTDIR)

# ADD BASE CPP /nologo /MD /W3 /GX /O2 /D "NDEBUG" /D "WIN32" /D "_WINDOWS" /D "_MBCS" /D "_AFXDLL" /FR /Yu"stdafx.h" /c
# ADD CPP /nologo /MD /W3 /GX /O2 /D "NDEBUG" /D "WIN32" /D "_WINDOWS" /D "_MBCS" /D "_AFXDLL" /FR /Yu"stdafx.h" /c
CPP_PROJ=/nologo /MD /W3 /GX /O2 /D "NDEBUG" /D "WIN32" /D "_WINDOWS" /D\
 "_MBCS" /D "_AFXDLL" /FR$(INTDIR)/ /Fp$(OUTDIR)/"EasyFont.pch" /Yu"stdafx.h"\
 /Fo$(INTDIR)/ /c 
CPP_OBJS=.\WinRel/
# ADD BASE RSC /l 0x409 /d "NDEBUG" /d "_AFXDLL"
# ADD RSC /l 0x409 /d "NDEBUG" /d "_AFXDLL"
RSC_PROJ=/l 0x409 /fo$(INTDIR)/"EasyFont.res" /d "NDEBUG" /d "_AFXDLL" 
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
BSC32_FLAGS=/nologo /o$(OUTDIR)/"EasyFont.bsc" 
BSC32_SBRS= \
	$(INTDIR)/stdafx.sbr \
	$(INTDIR)/EasyFont.sbr \
	$(INTDIR)/mainfrm.sbr \
	$(INTDIR)/EasyFdoc.sbr \
	$(INTDIR)/SceneVw.sbr \
	$(INTDIR)/Scene.sbr \
	$(INTDIR)/fontparamdlg.sbr

$(OUTDIR)/EasyFont.bsc : $(OUTDIR)  $(BSC32_SBRS)
    $(BSC32) @<<
  $(BSC32_FLAGS) $(BSC32_SBRS)
<<

LINK32=link.exe
# ADD BASE LINK32 /NOLOGO /SUBSYSTEM:windows /MACHINE:I386
# SUBTRACT BASE LINK32 /PDB:none
# ADD LINK32 GLlib.lib winmm.lib opengl32.lib glu32.lib glaux.lib /NOLOGO /SUBSYSTEM:windows /MACHINE:I386
# SUBTRACT LINK32 /PDB:none
LINK32_FLAGS=GLlib.lib winmm.lib opengl32.lib glu32.lib glaux.lib /NOLOGO\
 /SUBSYSTEM:windows /INCREMENTAL:no /PDB:$(OUTDIR)/"EasyFont.pdb" /MACHINE:I386\
 /OUT:$(OUTDIR)/"EasyFont.exe" 
DEF_FILE=
LINK32_OBJS= \
	$(INTDIR)/stdafx.obj \
	$(INTDIR)/EasyFont.obj \
	$(INTDIR)/mainfrm.obj \
	$(INTDIR)/EasyFdoc.obj \
	$(INTDIR)/SceneVw.obj \
	$(INTDIR)/EasyFont.res \
	$(INTDIR)/Scene.obj \
	$(INTDIR)/fontparamdlg.obj

$(OUTDIR)/EasyFont.exe : $(OUTDIR)  $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ENDIF 

MTL_PROJ=

.c{$(CPP_OBJS)}.obj:
   $(CPP) $(CPP_PROJ) $<  

.cpp{$(CPP_OBJS)}.obj:
   $(CPP) $(CPP_PROJ) $<  

.cxx{$(CPP_OBJS)}.obj:
   $(CPP) $(CPP_PROJ) $<  

################################################################################
# Begin Group "Source Files"

################################################################################
# Begin Source File

SOURCE=.\stdafx.cpp
DEP_STDAF=\
	.\stdafx.h

!IF  "$(CFG)" == "Win32 Debug"

# ADD BASE CPP /Yc"stdafx.h"
# ADD CPP /Yc"stdafx.h"

$(INTDIR)/stdafx.obj :  $(SOURCE)  $(DEP_STDAF) $(INTDIR)
   $(CPP) /nologo /MD /W3 /GX /Zi /Od /D "_DEBUG" /D "WIN32" /D "_WINDOWS" /D\
 "_MBCS" /D "_AFXDLL" /FR$(INTDIR)/ /Fp$(OUTDIR)/"EasyFont.pch" /Yc"stdafx.h"\
 /Fo$(INTDIR)/ /Fd$(OUTDIR)/"EasyFont.pdb" /c  $(SOURCE) 

!ELSEIF  "$(CFG)" == "Win32 Release"

# ADD BASE CPP /Yc"stdafx.h"
# ADD CPP /Yc"stdafx.h"

$(INTDIR)/stdafx.obj :  $(SOURCE)  $(DEP_STDAF) $(INTDIR)
   $(CPP) /nologo /MD /W3 /GX /O2 /D "NDEBUG" /D "WIN32" /D "_WINDOWS" /D\
 "_MBCS" /D "_AFXDLL" /FR$(INTDIR)/ /Fp$(OUTDIR)/"EasyFont.pch" /Yc"stdafx.h"\
 /Fo$(INTDIR)/ /c  $(SOURCE) 

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\EasyFont.cpp
DEP_EASYF=\
	.\stdafx.h\
	.\EasyFont.h\
	.\mainfrm.h\
	.\EasyFdoc.h\
	.\SceneVw.h\
	\articles\samples\opengl\gllib\GLlib.h\
	.\Scene.h\
	\articles\samples\opengl\gllib\cgl.h\
	\articles\samples\opengl\gllib\glview.h\
	\articles\samples\opengl\gllib\image.h\
	\articles\samples\opengl\animate\include\animate.h

$(INTDIR)/EasyFont.obj :  $(SOURCE)  $(DEP_EASYF) $(INTDIR)\
 $(INTDIR)/stdafx.obj

# End Source File
################################################################################
# Begin Source File

SOURCE=.\mainfrm.cpp
DEP_MAINF=\
	.\stdafx.h\
	.\EasyFont.h\
	.\mainfrm.h

$(INTDIR)/mainfrm.obj :  $(SOURCE)  $(DEP_MAINF) $(INTDIR) $(INTDIR)/stdafx.obj

# End Source File
################################################################################
# Begin Source File

SOURCE=.\EasyFdoc.cpp
DEP_EASYFD=\
	.\stdafx.h\
	.\EasyFont.h\
	.\EasyFdoc.h

$(INTDIR)/EasyFdoc.obj :  $(SOURCE)  $(DEP_EASYFD) $(INTDIR)\
 $(INTDIR)/stdafx.obj

# End Source File
################################################################################
# Begin Source File

SOURCE=.\SceneVw.cpp
DEP_SCENE=\
	.\stdafx.h\
	.\EasyFont.h\
	.\EasyFdoc.h\
	.\SceneVw.h\
	\articles\samples\opengl\gllib\GLlib.h\
	.\Scene.h\
	\articles\samples\opengl\gllib\cgl.h\
	\articles\samples\opengl\gllib\glview.h\
	\articles\samples\opengl\gllib\image.h\
	\articles\samples\opengl\animate\include\animate.h

$(INTDIR)/SceneVw.obj :  $(SOURCE)  $(DEP_SCENE) $(INTDIR) $(INTDIR)/stdafx.obj

# End Source File
################################################################################
# Begin Source File

SOURCE=.\EasyFont.rc
DEP_EASYFO=\
	.\res\EasyFont.ico\
	.\res\EasyFdoc.ico\
	.\res\EasyFont.rc2

$(INTDIR)/EasyFont.res :  $(SOURCE)  $(DEP_EASYFO) $(INTDIR)
   $(RSC) $(RSC_PROJ)  $(SOURCE) 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\readme.txt
# End Source File
################################################################################
# Begin Source File

SOURCE=.\Scene.cpp
DEP_SCENE_=\
	.\stdafx.h\
	\articles\samples\opengl\gllib\GLlib.h\
	.\Scene.h\
	\articles\samples\opengl\gllib\cgl.h\
	\articles\samples\opengl\gllib\glview.h\
	\articles\samples\opengl\gllib\image.h\
	\articles\samples\opengl\animate\include\animate.h

$(INTDIR)/Scene.obj :  $(SOURCE)  $(DEP_SCENE_) $(INTDIR) $(INTDIR)/stdafx.obj

# End Source File
################################################################################
# Begin Source File

SOURCE=.\fontparamdlg.cpp
DEP_FONTP=\
	.\stdafx.h\
	.\EasyFont.h\
	.\fontparamdlg.h

$(INTDIR)/fontparamdlg.obj :  $(SOURCE)  $(DEP_FONTP) $(INTDIR)\
 $(INTDIR)/stdafx.obj

# End Source File
# End Group
# End Project
################################################################################
