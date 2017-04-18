# Microsoft Visual C++ Generated NMAKE File, Format Version 2.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Application" 0x0101

!IF "$(CFG)" == ""
CFG=Win32 Debug
!MESSAGE No configuration specified.  Defaulting to Win32 Debug.
!ENDIF 

!IF "$(CFG)" != "Win32 Release" && "$(CFG)" != "Win32 Debug"
!MESSAGE Invalid configuration "$(CFG)" specified.
!MESSAGE You can specify a configuration when running NMAKE on this makefile
!MESSAGE by defining the macro CFG on the command line.  For example:
!MESSAGE 
!MESSAGE NMAKE /f "EasyTex.mak" CFG="Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "Win32 Release" (based on "Win32 (x86) Application")
!MESSAGE "Win32 Debug" (based on "Win32 (x86) Application")
!MESSAGE 
!ERROR An invalid configuration is specified.
!ENDIF 

################################################################################
# Begin Project
MTL=MkTypLib.exe
CPP=cl.exe
RSC=rc.exe

!IF  "$(CFG)" == "Win32 Release"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "WinRel"
# PROP BASE Intermediate_Dir "WinRel"
# PROP Use_MFC 2
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "x86-r"
# PROP Intermediate_Dir "x86-r"
OUTDIR=.\x86-r
INTDIR=.\x86-r

ALL : $(OUTDIR)/"EasyTex.exe" $(OUTDIR)/"EasyTex.bsc"

$(OUTDIR) : 
    if not exist $(OUTDIR)/nul mkdir $(OUTDIR)

# ADD BASE MTL /nologo /D "NDEBUG" /win32
# ADD MTL /nologo /D "NDEBUG" /win32
MTL_PROJ=/nologo /D "NDEBUG" /win32 
# ADD BASE CPP /nologo /ML /W3 /GX /YX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /FR /c
# ADD CPP /nologo /MD /W3 /GX /YX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /FR /c
CPP_PROJ=/nologo /MD /W3 /GX /YX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D\
 "_AFXDLL" /D "_MBCS" /FR$(INTDIR)/ /Fp$(OUTDIR)/"EasyTex.pch" /Fo$(INTDIR)/ /c 
CPP_OBJS=".\x86-r/"
# ADD BASE RSC /l 0x409 /d "NDEBUG"
# ADD RSC /l 0x409 /d "NDEBUG" /d "_AFXDLL"
RSC_PROJ=/l 0x409 /fo$(INTDIR)/"EasyTex.res" /d "NDEBUG" /d "_AFXDLL" 
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
BSC32_FLAGS=/nologo /o$(OUTDIR)/"EasyTex.bsc" 
BSC32_SBRS= \
	$(INTDIR)/"EasyTdoc.sbr" \
	$(INTDIR)/"SceneVw.sbr" \
	$(INTDIR)/"mainfrm.sbr" \
	$(INTDIR)/"EasyTex.sbr" \
	$(INTDIR)/"Scene.sbr" \
	$(INTDIR)/"stdafx.sbr" \
	$(INTDIR)/"shapes.sbr"

$(OUTDIR)/"EasyTex.bsc" : $(OUTDIR)  $(BSC32_SBRS)
    $(BSC32) @<<
  $(BSC32_FLAGS) $(BSC32_SBRS)
<<

LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /NOLOGO /SUBSYSTEM:windows /MACHINE:I386
# ADD LINK32 GLlib.lib winmm.lib opengl32.lib glu32.lib glaux.lib /NOLOGO /SUBSYSTEM:windows /MACHINE:I386
LINK32_FLAGS=GLlib.lib winmm.lib opengl32.lib glu32.lib glaux.lib /NOLOGO\
 /SUBSYSTEM:windows /INCREMENTAL:no /PDB:$(OUTDIR)/"EasyTex.pdb" /MACHINE:I386\
 /OUT:$(OUTDIR)/"EasyTex.exe" 
DEF_FILE=
LINK32_OBJS= \
	$(INTDIR)/"EasyTdoc.obj" \
	$(INTDIR)/"EasyTex.res" \
	$(INTDIR)/"SceneVw.obj" \
	$(INTDIR)/"mainfrm.obj" \
	$(INTDIR)/"EasyTex.obj" \
	$(INTDIR)/"Scene.obj" \
	$(INTDIR)/"stdafx.obj" \
	$(INTDIR)/"shapes.obj"

$(OUTDIR)/"EasyTex.exe" : $(OUTDIR)  $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ELSEIF  "$(CFG)" == "Win32 Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "WinDebug"
# PROP BASE Intermediate_Dir "WinDebug"
# PROP Use_MFC 2
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "x86-d"
# PROP Intermediate_Dir "x86-d"
OUTDIR=.\x86-d
INTDIR=.\x86-d

ALL : $(OUTDIR)/"EasyTex.exe" $(OUTDIR)/"EasyTex.bsc"

$(OUTDIR) : 
    if not exist $(OUTDIR)/nul mkdir $(OUTDIR)

# ADD BASE MTL /nologo /D "_DEBUG" /win32
# ADD MTL /nologo /D "_DEBUG" /win32
MTL_PROJ=/nologo /D "_DEBUG" /win32 
# ADD BASE CPP /nologo /ML /W3 /GX /Zi /YX /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /FR /c
# ADD CPP /nologo /MD /W3 /GX /Zi /YX /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /FR /c
CPP_PROJ=/nologo /MD /W3 /GX /Zi /YX /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS"\
 /D "_AFXDLL" /D "_MBCS" /FR$(INTDIR)/ /Fp$(OUTDIR)/"EasyTex.pch" /Fo$(INTDIR)/\
 /Fd$(OUTDIR)/"EasyTex.pdb" /c 
CPP_OBJS=".\x86-d/"
# ADD BASE RSC /l 0x409 /d "_DEBUG"
# ADD RSC /l 0x409 /d "_DEBUG" /d "_AFXDLL"
RSC_PROJ=/l 0x409 /fo$(INTDIR)/"EasyTex.res" /d "_DEBUG" /d "_AFXDLL" 
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
BSC32_FLAGS=/nologo /o$(OUTDIR)/"EasyTex.bsc" 
BSC32_SBRS= \
	$(INTDIR)/"EasyTdoc.sbr" \
	$(INTDIR)/"SceneVw.sbr" \
	$(INTDIR)/"mainfrm.sbr" \
	$(INTDIR)/"EasyTex.sbr" \
	$(INTDIR)/"Scene.sbr" \
	$(INTDIR)/"stdafx.sbr" \
	$(INTDIR)/"shapes.sbr"

$(OUTDIR)/"EasyTex.bsc" : $(OUTDIR)  $(BSC32_SBRS)
    $(BSC32) @<<
  $(BSC32_FLAGS) $(BSC32_SBRS)
<<

LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /NOLOGO /SUBSYSTEM:windows /DEBUG /MACHINE:I386
# ADD LINK32 GLlib-d.lib winmm.lib opengl32.lib glu32.lib glaux.lib /NOLOGO /SUBSYSTEM:windows /DEBUG /MACHINE:I386
LINK32_FLAGS=GLlib-d.lib winmm.lib opengl32.lib glu32.lib glaux.lib /NOLOGO\
 /SUBSYSTEM:windows /INCREMENTAL:yes /PDB:$(OUTDIR)/"EasyTex.pdb" /DEBUG\
 /MACHINE:I386 /OUT:$(OUTDIR)/"EasyTex.exe" 
DEF_FILE=
LINK32_OBJS= \
	$(INTDIR)/"EasyTdoc.obj" \
	$(INTDIR)/"EasyTex.res" \
	$(INTDIR)/"SceneVw.obj" \
	$(INTDIR)/"mainfrm.obj" \
	$(INTDIR)/"EasyTex.obj" \
	$(INTDIR)/"Scene.obj" \
	$(INTDIR)/"stdafx.obj" \
	$(INTDIR)/"shapes.obj"

$(OUTDIR)/"EasyTex.exe" : $(OUTDIR)  $(DEF_FILE) $(LINK32_OBJS)
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

################################################################################
# Begin Group "Source Files"

################################################################################
# Begin Source File

SOURCE=.\EasyTdoc.cpp
DEP_EASYT=\
	.\stdafx.h\
	.\EasyTex.h\
	.\EasyTdoc.h

$(INTDIR)/"EasyTdoc.obj" :  $(SOURCE)  $(DEP_EASYT) $(INTDIR)

# End Source File
################################################################################
# Begin Source File

SOURCE=.\EasyTex.rc
DEP_EASYTE=\
	.\res\EasyTex.ico\
	.\res\EasyTdoc.ico\
	.\res\EasyTex.rc2

$(INTDIR)/"EasyTex.res" :  $(SOURCE)  $(DEP_EASYTE) $(INTDIR)
   $(RSC) $(RSC_PROJ)  $(SOURCE) 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\SceneVw.cpp
DEP_SCENE=\
	.\stdafx.h\
	.\EasyTex.h\
	.\EasyTdoc.h\
	.\SceneVw.h\
	\articles\samples\opengl\gllib\GLlib.h\
	.\Scene.h\
	\DEV\MSVC20\INCLUDE\gl\gl.h\
	\DEV\MSVC20\INCLUDE\gl\glu.h\
	\articles\samples\opengl\gllib\cgl.h\
	\articles\samples\opengl\gllib\glview.h\
	\articles\samples\opengl\gllib\image.h\
	\articles\samples\opengl\animate\include\animate.h

$(INTDIR)/"SceneVw.obj" :  $(SOURCE)  $(DEP_SCENE) $(INTDIR)

# End Source File
################################################################################
# Begin Source File

SOURCE=.\mainfrm.cpp
DEP_MAINF=\
	.\stdafx.h\
	.\EasyTex.h\
	.\mainfrm.h

$(INTDIR)/"mainfrm.obj" :  $(SOURCE)  $(DEP_MAINF) $(INTDIR)

# End Source File
################################################################################
# Begin Source File

SOURCE=.\EasyTex.cpp
DEP_EASYTEX=\
	.\stdafx.h\
	.\EasyTex.h\
	.\mainfrm.h\
	.\EasyTdoc.h\
	.\SceneVw.h\
	\articles\samples\opengl\gllib\GLlib.h\
	.\Scene.h\
	\DEV\MSVC20\INCLUDE\gl\gl.h\
	\DEV\MSVC20\INCLUDE\gl\glu.h\
	\articles\samples\opengl\gllib\cgl.h\
	\articles\samples\opengl\gllib\glview.h\
	\articles\samples\opengl\gllib\image.h\
	\articles\samples\opengl\animate\include\animate.h

$(INTDIR)/"EasyTex.obj" :  $(SOURCE)  $(DEP_EASYTEX) $(INTDIR)

# End Source File
################################################################################
# Begin Source File

SOURCE=.\Scene.cpp
DEP_SCENE_=\
	.\stdafx.h\
	\DEV\MSVC20\INCLUDE\gl\gl.h\
	\DEV\MSVC20\INCLUDE\gl\glu.h\
	\articles\samples\opengl\gllib\GLlib.h\
	.\Scene.h\
	\articles\samples\opengl\gllib\cgl.h\
	\articles\samples\opengl\gllib\glview.h\
	\articles\samples\opengl\gllib\image.h\
	\articles\samples\opengl\animate\include\animate.h

$(INTDIR)/"Scene.obj" :  $(SOURCE)  $(DEP_SCENE_) $(INTDIR)

# End Source File
################################################################################
# Begin Source File

SOURCE=.\stdafx.cpp
DEP_STDAF=\
	.\stdafx.h

$(INTDIR)/"stdafx.obj" :  $(SOURCE)  $(DEP_STDAF) $(INTDIR)

# End Source File
################################################################################
# Begin Source File

SOURCE=.\shapes.cpp
DEP_SHAPE=\
	.\stdafx.h\
	\DEV\MSVC20\INCLUDE\gl\gl.h\
	\DEV\MSVC20\INCLUDE\gl\glu.h\
	\articles\samples\opengl\gllib\GLlib.h\
	.\Scene.h\
	\articles\samples\opengl\gllib\cgl.h\
	\articles\samples\opengl\gllib\glview.h\
	\articles\samples\opengl\gllib\image.h\
	\articles\samples\opengl\animate\include\animate.h

$(INTDIR)/"shapes.obj" :  $(SOURCE)  $(DEP_SHAPE) $(INTDIR)

# End Source File
# End Group
# End Project
################################################################################
