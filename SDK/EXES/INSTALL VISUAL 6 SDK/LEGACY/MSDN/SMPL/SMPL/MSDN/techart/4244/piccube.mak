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
!MESSAGE NMAKE /f "PicCube.mak" CFG="Win32 Debug"
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
# PROP Use_MFC 5
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "WinDebug"
# PROP Intermediate_Dir "WinDebug"
OUTDIR=.\WinDebug
INTDIR=.\WinDebug

ALL : $(OUTDIR)/PicCube.scr $(OUTDIR)/PicCube.bsc

$(OUTDIR) : 
    if not exist $(OUTDIR)/nul mkdir $(OUTDIR)

# ADD BASE CPP /nologo /MD /W3 /GX /Zi /Od /D "_DEBUG" /D "WIN32" /D "_WINDOWS" /D "_MBCS" /D "_AFXDLL" /FR /Yu"stdafx.h" /c
# ADD CPP /nologo /MT /W3 /GX /Zi /Od /D "_DEBUG" /D "WIN32" /D "_WINDOWS" /D "_MBCS" /FR /Yu"stdafx.h" /c
CPP_PROJ=/nologo /MT /W3 /GX /Zi /Od /D "_DEBUG" /D "WIN32" /D "_WINDOWS" /D\
 "_MBCS" /FR$(INTDIR)/ /Fp$(OUTDIR)/"PicCube.pch" /Yu"stdafx.h" /Fo$(INTDIR)/\
 /Fd$(OUTDIR)/"PicCube.pdb" /c 
CPP_OBJS=.\WinDebug/
# ADD BASE RSC /l 0x409 /d "_DEBUG" /d "_AFXDLL"
# ADD RSC /l 0x409 /d "_DEBUG"
RSC_PROJ=/l 0x409 /fo$(INTDIR)/"PicCube.res" /d "_DEBUG" 
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
BSC32_FLAGS=/nologo /o$(OUTDIR)/"PicCube.bsc" 
BSC32_SBRS= \
	$(INTDIR)/stdafx.sbr \
	$(INTDIR)/PicCube.sbr \
	$(INTDIR)/movewnd.sbr \
	$(INTDIR)/savewnd.sbr \
	$(INTDIR)/glwnd.sbr \
	$(INTDIR)/Scene.sbr \
	$(INTDIR)/shapes.sbr \
	$(INTDIR)/configdl.sbr

$(OUTDIR)/PicCube.bsc : $(OUTDIR)  $(BSC32_SBRS)
    $(BSC32) @<<
  $(BSC32_FLAGS) $(BSC32_SBRS)
<<

LINK32=link.exe
# ADD BASE LINK32 /NOLOGO /SUBSYSTEM:windows /DEBUG /MACHINE:I386
# SUBTRACT BASE LINK32 /PDB:none
# ADD LINK32 GLlib-s-d.lib winmm.lib opengl32.lib glu32.lib glaux.lib animatesd.lib /NOLOGO /SUBSYSTEM:windows /DEBUG /MACHINE:I386 /OUT:"WinDebug/PicCube.scr"
# SUBTRACT LINK32 /PDB:none
LINK32_FLAGS=GLlib-s-d.lib winmm.lib opengl32.lib glu32.lib glaux.lib\
 animatesd.lib /NOLOGO /SUBSYSTEM:windows /INCREMENTAL:yes\
 /PDB:$(OUTDIR)/"PicCube.pdb" /DEBUG /MACHINE:I386 /OUT:"WinDebug/PicCube.scr" 
DEF_FILE=
LINK32_OBJS= \
	$(INTDIR)/stdafx.obj \
	$(INTDIR)/PicCube.obj \
	$(INTDIR)/PicCube.res \
	$(INTDIR)/movewnd.obj \
	$(INTDIR)/savewnd.obj \
	$(INTDIR)/glwnd.obj \
	$(INTDIR)/Scene.obj \
	$(INTDIR)/shapes.obj \
	$(INTDIR)/configdl.obj

$(OUTDIR)/PicCube.scr : $(OUTDIR)  $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ELSEIF  "$(CFG)" == "Win32 Release"

# PROP BASE Use_MFC 6
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "WinRel"
# PROP BASE Intermediate_Dir "WinRel"
# PROP Use_MFC 5
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "WinRel"
# PROP Intermediate_Dir "WinRel"
OUTDIR=.\WinRel
INTDIR=.\WinRel

ALL : $(OUTDIR)/PicCube.scr $(OUTDIR)/PicCube.bsc

$(OUTDIR) : 
    if not exist $(OUTDIR)/nul mkdir $(OUTDIR)

# ADD BASE CPP /nologo /MD /W3 /GX /O2 /D "NDEBUG" /D "WIN32" /D "_WINDOWS" /D "_MBCS" /D "_AFXDLL" /FR /Yu"stdafx.h" /c
# ADD CPP /nologo /MT /W3 /GX /O2 /D "NDEBUG" /D "WIN32" /D "_WINDOWS" /D "_MBCS" /FR /Yu"stdafx.h" /c
CPP_PROJ=/nologo /MT /W3 /GX /O2 /D "NDEBUG" /D "WIN32" /D "_WINDOWS" /D\
 "_MBCS" /FR$(INTDIR)/ /Fp$(OUTDIR)/"PicCube.pch" /Yu"stdafx.h" /Fo$(INTDIR)/ /c\
 
CPP_OBJS=.\WinRel/
# ADD BASE RSC /l 0x409 /d "NDEBUG" /d "_AFXDLL"
# ADD RSC /l 0x409 /d "NDEBUG"
RSC_PROJ=/l 0x409 /fo$(INTDIR)/"PicCube.res" /d "NDEBUG" 
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
BSC32_FLAGS=/nologo /o$(OUTDIR)/"PicCube.bsc" 
BSC32_SBRS= \
	$(INTDIR)/stdafx.sbr \
	$(INTDIR)/PicCube.sbr \
	$(INTDIR)/movewnd.sbr \
	$(INTDIR)/savewnd.sbr \
	$(INTDIR)/glwnd.sbr \
	$(INTDIR)/Scene.sbr \
	$(INTDIR)/shapes.sbr \
	$(INTDIR)/configdl.sbr

$(OUTDIR)/PicCube.bsc : $(OUTDIR)  $(BSC32_SBRS)
    $(BSC32) @<<
  $(BSC32_FLAGS) $(BSC32_SBRS)
<<

LINK32=link.exe
# ADD BASE LINK32 /NOLOGO /SUBSYSTEM:windows /MACHINE:I386
# SUBTRACT BASE LINK32 /PDB:none
# ADD LINK32 GLlib-s.lib winmm.lib opengl32.lib glu32.lib glaux.lib animatesr.lib /NOLOGO /SUBSYSTEM:windows /MACHINE:I386 /OUT:"WinRel/PicCube.scr"
# SUBTRACT LINK32 /PDB:none
LINK32_FLAGS=GLlib-s.lib winmm.lib opengl32.lib glu32.lib glaux.lib\
 animatesr.lib /NOLOGO /SUBSYSTEM:windows /INCREMENTAL:no\
 /PDB:$(OUTDIR)/"PicCube.pdb" /MACHINE:I386 /OUT:"WinRel/PicCube.scr" 
DEF_FILE=
LINK32_OBJS= \
	$(INTDIR)/stdafx.obj \
	$(INTDIR)/PicCube.obj \
	$(INTDIR)/PicCube.res \
	$(INTDIR)/movewnd.obj \
	$(INTDIR)/savewnd.obj \
	$(INTDIR)/glwnd.obj \
	$(INTDIR)/Scene.obj \
	$(INTDIR)/shapes.obj \
	$(INTDIR)/configdl.obj

$(OUTDIR)/PicCube.scr : $(OUTDIR)  $(DEF_FILE) $(LINK32_OBJS)
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
   $(CPP) /nologo /MT /W3 /GX /Zi /Od /D "_DEBUG" /D "WIN32" /D "_WINDOWS" /D\
 "_MBCS" /FR$(INTDIR)/ /Fp$(OUTDIR)/"PicCube.pch" /Yc"stdafx.h" /Fo$(INTDIR)/\
 /Fd$(OUTDIR)/"PicCube.pdb" /c  $(SOURCE) 

!ELSEIF  "$(CFG)" == "Win32 Release"

# ADD BASE CPP /Yc"stdafx.h"
# ADD CPP /Yc"stdafx.h"

$(INTDIR)/stdafx.obj :  $(SOURCE)  $(DEP_STDAF) $(INTDIR)
   $(CPP) /nologo /MT /W3 /GX /O2 /D "NDEBUG" /D "WIN32" /D "_WINDOWS" /D\
 "_MBCS" /FR$(INTDIR)/ /Fp$(OUTDIR)/"PicCube.pch" /Yc"stdafx.h" /Fo$(INTDIR)/ /c\
  $(SOURCE) 

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\PicCube.cpp
DEP_PICCU=\
	.\stdafx.h\
	.\PicCube.h\
	\articles\samples\OpenGL\GLlib\GLlib.h\
	.\Scene.h\
	.\glwnd.h\
	.\savewnd.h\
	.\movewnd.h\
	\DEV\MSVC20\INCLUDE\GL\GL.H\
	\DEV\MSVC20\INCLUDE\GL\GLU.H\
	\articles\samples\OpenGL\GLlib\cgl.h\
	\articles\samples\OpenGL\GLlib\glview.h\
	\articles\samples\OpenGL\GLlib\image.h\
	\articles\samples\OpenGL\animate\include\animate.h

$(INTDIR)/PicCube.obj :  $(SOURCE)  $(DEP_PICCU) $(INTDIR) $(INTDIR)/stdafx.obj

# End Source File
################################################################################
# Begin Source File

SOURCE=.\PicCube.rc
DEP_PICCUB=\
	.\res\PicCube.ico\
	.\res\PicCudoc.ico\
	.\res\cursor1.cur\
	.\res\PicCube.rc2

$(INTDIR)/PicCube.res :  $(SOURCE)  $(DEP_PICCUB) $(INTDIR)
   $(RSC) $(RSC_PROJ)  $(SOURCE) 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\movewnd.cpp
DEP_MOVEW=\
	.\stdafx.h\
	.\PicCube.h\
	\articles\samples\OpenGL\GLlib\GLlib.h\
	.\Scene.h\
	.\glwnd.h\
	.\savewnd.h\
	.\movewnd.h\
	\DEV\MSVC20\INCLUDE\GL\GL.H\
	\DEV\MSVC20\INCLUDE\GL\GLU.H\
	\articles\samples\OpenGL\GLlib\cgl.h\
	\articles\samples\OpenGL\GLlib\glview.h\
	\articles\samples\OpenGL\GLlib\image.h\
	\articles\samples\OpenGL\animate\include\animate.h

$(INTDIR)/movewnd.obj :  $(SOURCE)  $(DEP_MOVEW) $(INTDIR) $(INTDIR)/stdafx.obj

# End Source File
################################################################################
# Begin Source File

SOURCE=.\savewnd.cpp
DEP_SAVEW=\
	.\stdafx.h\
	.\savewnd.h

$(INTDIR)/savewnd.obj :  $(SOURCE)  $(DEP_SAVEW) $(INTDIR) $(INTDIR)/stdafx.obj

# End Source File
################################################################################
# Begin Source File

SOURCE=.\glwnd.cpp
DEP_GLWND=\
	.\stdafx.h\
	.\PicCube.h\
	\articles\samples\OpenGL\GLlib\GLlib.h\
	.\Scene.h\
	.\glwnd.h\
	\DEV\MSVC20\INCLUDE\GL\GL.H\
	\DEV\MSVC20\INCLUDE\GL\GLU.H\
	\articles\samples\OpenGL\GLlib\cgl.h\
	\articles\samples\OpenGL\GLlib\glview.h\
	\articles\samples\OpenGL\GLlib\image.h\
	\articles\samples\OpenGL\animate\include\animate.h

$(INTDIR)/glwnd.obj :  $(SOURCE)  $(DEP_GLWND) $(INTDIR) $(INTDIR)/stdafx.obj

# End Source File
################################################################################
# Begin Source File

SOURCE=.\Scene.cpp
DEP_SCENE=\
	.\stdafx.h\
	\DEV\MSVC20\INCLUDE\GL\GL.H\
	\DEV\MSVC20\INCLUDE\GL\GLU.H\
	\articles\samples\OpenGL\GLlib\GLlib.h\
	.\Scene.h\
	\articles\samples\OpenGL\GLlib\cgl.h\
	\articles\samples\OpenGL\GLlib\glview.h\
	\articles\samples\OpenGL\GLlib\image.h\
	\articles\samples\OpenGL\animate\include\animate.h

$(INTDIR)/Scene.obj :  $(SOURCE)  $(DEP_SCENE) $(INTDIR) $(INTDIR)/stdafx.obj

# End Source File
################################################################################
# Begin Source File

SOURCE=.\shapes.cpp
DEP_SHAPE=\
	.\stdafx.h\
	\DEV\MSVC20\INCLUDE\GL\GL.H\
	\DEV\MSVC20\INCLUDE\GL\GLU.H\
	\articles\samples\OpenGL\GLlib\GLlib.h\
	.\Scene.h\
	\articles\samples\OpenGL\GLlib\cgl.h\
	\articles\samples\OpenGL\GLlib\glview.h\
	\articles\samples\OpenGL\GLlib\image.h\
	\articles\samples\OpenGL\animate\include\animate.h

$(INTDIR)/shapes.obj :  $(SOURCE)  $(DEP_SHAPE) $(INTDIR) $(INTDIR)/stdafx.obj

# End Source File
################################################################################
# Begin Source File

SOURCE=.\configdl.cpp
DEP_CONFI=\
	.\stdafx.h\
	.\PicCube.h\
	.\configdl.h

$(INTDIR)/configdl.obj :  $(SOURCE)  $(DEP_CONFI) $(INTDIR)\
 $(INTDIR)/stdafx.obj

# End Source File
# End Group
# End Project
################################################################################
