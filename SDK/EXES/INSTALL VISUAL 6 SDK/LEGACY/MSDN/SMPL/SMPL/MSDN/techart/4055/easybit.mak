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
!MESSAGE NMAKE /f "EasyBit.mak" CFG="Win32 Debug"
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
# PROP Output_Dir "x86-d"
# PROP Intermediate_Dir "x86-d"
OUTDIR=.\x86-d
INTDIR=.\x86-d

ALL : $(OUTDIR)/"EasyBit.exe" $(OUTDIR)/"EasyBit.bsc"

$(OUTDIR) : 
    if not exist $(OUTDIR)/nul mkdir $(OUTDIR)

# ADD BASE CPP /nologo /MD /W3 /GX /Zi /Od /D "_DEBUG" /D "WIN32" /D "_WINDOWS" /D "_MBCS" /D "_AFXDLL" /FR /Yu"stdafx.h" /c
# ADD CPP /nologo /MD /W3 /GX /Zi /Od /D "_DEBUG" /D "WIN32" /D "_WINDOWS" /D "_MBCS" /D "_AFXDLL" /FR /Yu"stdafx.h" /c
CPP_PROJ=/nologo /MD /W3 /GX /Zi /Od /D "_DEBUG" /D "WIN32" /D "_WINDOWS" /D\
 "_MBCS" /D "_AFXDLL" /FR$(INTDIR)/ /Fp$(OUTDIR)/"EasyBit.pch" /Yu"stdafx.h"\
 /Fo$(INTDIR)/ /Fd$(OUTDIR)/"EasyBit.pdb" /c 
CPP_OBJS=".\x86-d/"
# ADD BASE RSC /l 0x409 /d "_DEBUG" /d "_AFXDLL"
# ADD RSC /l 0x409 /d "_DEBUG" /d "_AFXDLL"
RSC_PROJ=/l 0x409 /fo$(INTDIR)/"EasyBit.res" /d "_DEBUG" /d "_AFXDLL" 
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
BSC32_FLAGS=/nologo /o$(OUTDIR)/"EasyBit.bsc" 
BSC32_SBRS= \
	$(INTDIR)/"stdafx.sbr" \
	$(INTDIR)/"EasyBit.sbr" \
	$(INTDIR)/"mainfrm.sbr" \
	$(INTDIR)/"EasyBdoc.sbr" \
	$(INTDIR)/"SceneVw.sbr" \
	$(INTDIR)/"Scene.sbr" \
	$(INTDIR)/"CSimpleDib.sbr" \
	$(INTDIR)/"shapes.sbr" \
	$(INTDIR)/"CSceneDodec.sbr" \
	$(INTDIR)/"CSceneBox.sbr" \
	$(INTDIR)/"CScenePyramid.sbr" \
	$(INTDIR)/"SceneCI.sbr" \
	$(INTDIR)/"CMyStatusBar.sbr" \
	$(INTDIR)/"CShapeMenu.sbr"

$(OUTDIR)/"EasyBit.bsc" : $(OUTDIR)  $(BSC32_SBRS)
    $(BSC32) @<<
  $(BSC32_FLAGS) $(BSC32_SBRS)
<<

LINK32=link.exe
# ADD BASE LINK32 /NOLOGO /SUBSYSTEM:windows /DEBUG /MACHINE:I386
# SUBTRACT BASE LINK32 /PDB:none
# ADD LINK32 GLlib-d.lib animated.lib winmm.lib opengl32.lib glu32.lib glaux.lib /NOLOGO /SUBSYSTEM:windows /DEBUG /MACHINE:I386
# SUBTRACT LINK32 /PDB:none
LINK32_FLAGS=GLlib-d.lib animated.lib winmm.lib opengl32.lib glu32.lib\
 glaux.lib /NOLOGO /SUBSYSTEM:windows /INCREMENTAL:yes\
 /PDB:$(OUTDIR)/"EasyBit.pdb" /DEBUG /MACHINE:I386 /OUT:$(OUTDIR)/"EasyBit.exe" 
DEF_FILE=
LINK32_OBJS= \
	$(INTDIR)/"stdafx.obj" \
	$(INTDIR)/"EasyBit.obj" \
	$(INTDIR)/"mainfrm.obj" \
	$(INTDIR)/"EasyBdoc.obj" \
	$(INTDIR)/"SceneVw.obj" \
	$(INTDIR)/"EasyBit.res" \
	$(INTDIR)/"Scene.obj" \
	$(INTDIR)/"CSimpleDib.obj" \
	$(INTDIR)/"shapes.obj" \
	$(INTDIR)/"CSceneDodec.obj" \
	$(INTDIR)/"CSceneBox.obj" \
	$(INTDIR)/"CScenePyramid.obj" \
	$(INTDIR)/"SceneCI.obj" \
	$(INTDIR)/"CMyStatusBar.obj" \
	$(INTDIR)/"CShapeMenu.obj"

$(OUTDIR)/"EasyBit.exe" : $(OUTDIR)  $(DEF_FILE) $(LINK32_OBJS)
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
# PROP Output_Dir "x86-r"
# PROP Intermediate_Dir "x86-r"
OUTDIR=.\x86-r
INTDIR=.\x86-r

ALL : $(OUTDIR)/"EasyBit.exe" $(OUTDIR)/"EasyBit.bsc"

$(OUTDIR) : 
    if not exist $(OUTDIR)/nul mkdir $(OUTDIR)

# ADD BASE CPP /nologo /MD /W3 /GX /O2 /D "NDEBUG" /D "WIN32" /D "_WINDOWS" /D "_MBCS" /D "_AFXDLL" /FR /Yu"stdafx.h" /c
# ADD CPP /nologo /MD /W3 /GX /O2 /D "NDEBUG" /D "WIN32" /D "_WINDOWS" /D "_MBCS" /D "_AFXDLL" /FR /Yu"stdafx.h" /c
CPP_PROJ=/nologo /MD /W3 /GX /O2 /D "NDEBUG" /D "WIN32" /D "_WINDOWS" /D\
 "_MBCS" /D "_AFXDLL" /FR$(INTDIR)/ /Fp$(OUTDIR)/"EasyBit.pch" /Yu"stdafx.h"\
 /Fo$(INTDIR)/ /c 
CPP_OBJS=".\x86-r/"
# ADD BASE RSC /l 0x409 /d "NDEBUG" /d "_AFXDLL"
# ADD RSC /l 0x409 /d "NDEBUG" /d "_AFXDLL"
RSC_PROJ=/l 0x409 /fo$(INTDIR)/"EasyBit.res" /d "NDEBUG" /d "_AFXDLL" 
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
BSC32_FLAGS=/nologo /o$(OUTDIR)/"EasyBit.bsc" 
BSC32_SBRS= \
	$(INTDIR)/"stdafx.sbr" \
	$(INTDIR)/"EasyBit.sbr" \
	$(INTDIR)/"mainfrm.sbr" \
	$(INTDIR)/"EasyBdoc.sbr" \
	$(INTDIR)/"SceneVw.sbr" \
	$(INTDIR)/"Scene.sbr" \
	$(INTDIR)/"CSimpleDib.sbr" \
	$(INTDIR)/"shapes.sbr" \
	$(INTDIR)/"CSceneDodec.sbr" \
	$(INTDIR)/"CSceneBox.sbr" \
	$(INTDIR)/"CScenePyramid.sbr" \
	$(INTDIR)/"SceneCI.sbr" \
	$(INTDIR)/"CMyStatusBar.sbr" \
	$(INTDIR)/"CShapeMenu.sbr"

$(OUTDIR)/"EasyBit.bsc" : $(OUTDIR)  $(BSC32_SBRS)
    $(BSC32) @<<
  $(BSC32_FLAGS) $(BSC32_SBRS)
<<

LINK32=link.exe
# ADD BASE LINK32 /NOLOGO /SUBSYSTEM:windows /MACHINE:I386
# SUBTRACT BASE LINK32 /PDB:none
# ADD LINK32 GLlib.lib animater.lib winmm.lib opengl32.lib glu32.lib glaux.lib /NOLOGO /SUBSYSTEM:windows /MACHINE:I386
# SUBTRACT LINK32 /PDB:none
LINK32_FLAGS=GLlib.lib animater.lib winmm.lib opengl32.lib glu32.lib glaux.lib\
 /NOLOGO /SUBSYSTEM:windows /INCREMENTAL:no /PDB:$(OUTDIR)/"EasyBit.pdb"\
 /MACHINE:I386 /OUT:$(OUTDIR)/"EasyBit.exe" 
DEF_FILE=
LINK32_OBJS= \
	$(INTDIR)/"stdafx.obj" \
	$(INTDIR)/"EasyBit.obj" \
	$(INTDIR)/"mainfrm.obj" \
	$(INTDIR)/"EasyBdoc.obj" \
	$(INTDIR)/"SceneVw.obj" \
	$(INTDIR)/"EasyBit.res" \
	$(INTDIR)/"Scene.obj" \
	$(INTDIR)/"CSimpleDib.obj" \
	$(INTDIR)/"shapes.obj" \
	$(INTDIR)/"CSceneDodec.obj" \
	$(INTDIR)/"CSceneBox.obj" \
	$(INTDIR)/"CScenePyramid.obj" \
	$(INTDIR)/"SceneCI.obj" \
	$(INTDIR)/"CMyStatusBar.obj" \
	$(INTDIR)/"CShapeMenu.obj"

$(OUTDIR)/"EasyBit.exe" : $(OUTDIR)  $(DEF_FILE) $(LINK32_OBJS)
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

$(INTDIR)/"stdafx.obj" :  $(SOURCE)  $(DEP_STDAF) $(INTDIR)
   $(CPP) /nologo /MD /W3 /GX /Zi /Od /D "_DEBUG" /D "WIN32" /D "_WINDOWS" /D\
 "_MBCS" /D "_AFXDLL" /FR$(INTDIR)/ /Fp$(OUTDIR)/"EasyBit.pch" /Yc"stdafx.h"\
 /Fo$(INTDIR)/ /Fd$(OUTDIR)/"EasyBit.pdb" /c  $(SOURCE) 

!ELSEIF  "$(CFG)" == "Win32 Release"

# ADD BASE CPP /Yc"stdafx.h"
# ADD CPP /Yc"stdafx.h"

$(INTDIR)/"stdafx.obj" :  $(SOURCE)  $(DEP_STDAF) $(INTDIR)
   $(CPP) /nologo /MD /W3 /GX /O2 /D "NDEBUG" /D "WIN32" /D "_WINDOWS" /D\
 "_MBCS" /D "_AFXDLL" /FR$(INTDIR)/ /Fp$(OUTDIR)/"EasyBit.pch" /Yc"stdafx.h"\
 /Fo$(INTDIR)/ /c  $(SOURCE) 

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\EasyBit.cpp
DEP_EASYB=\
	.\stdafx.h\
	.\EasyBit.h\
	.\mainfrm.h\
	.\EasyBdoc.h\
	.\SceneVw.h\
	.\CMyStatusBar.h\
	.\CShapeMenu.h\
	\articles\samples\OpenGL\GLlib\GLlib.h\
	\articles\samples\OpenGL\animate\include\animate.h\
	.\Scene.h\
	.\SceneCI.h\
	.\CSceneBox.h\
	.\CSceneDodec.h\
	.\CScenePyramid.h\
	.\CSimpleDib.h\
	\DEV\MSVC20\INCLUDE\GL\GL.H\
	\DEV\MSVC20\INCLUDE\GL\GLU.H\
	\articles\samples\OpenGL\GLlib\cgl.h\
	\articles\samples\OpenGL\GLlib\glview.h\
	\articles\samples\OpenGL\GLlib\image.h

$(INTDIR)/"EasyBit.obj" :  $(SOURCE)  $(DEP_EASYB) $(INTDIR)\
 $(INTDIR)/stdafx.obj

# End Source File
################################################################################
# Begin Source File

SOURCE=.\mainfrm.cpp
DEP_MAINF=\
	.\stdafx.h\
	.\EasyBit.h\
	.\mainfrm.h\
	.\CMyStatusBar.h\
	.\CShapeMenu.h\
	\articles\samples\OpenGL\GLlib\GLlib.h\
	.\CSceneBox.h\
	.\CSceneDodec.h\
	.\CScenePyramid.h\
	.\CSimpleDib.h\
	\DEV\MSVC20\INCLUDE\GL\GL.H\
	\DEV\MSVC20\INCLUDE\GL\GLU.H\
	\articles\samples\OpenGL\GLlib\cgl.h\
	\articles\samples\OpenGL\GLlib\glview.h\
	\articles\samples\OpenGL\GLlib\image.h\
	\articles\samples\OpenGL\animate\include\animate.h

$(INTDIR)/"mainfrm.obj" :  $(SOURCE)  $(DEP_MAINF) $(INTDIR)\
 $(INTDIR)/stdafx.obj

# End Source File
################################################################################
# Begin Source File

SOURCE=.\EasyBdoc.cpp
DEP_EASYBD=\
	.\stdafx.h\
	.\EasyBit.h\
	.\EasyBdoc.h

$(INTDIR)/"EasyBdoc.obj" :  $(SOURCE)  $(DEP_EASYBD) $(INTDIR)\
 $(INTDIR)/stdafx.obj

# End Source File
################################################################################
# Begin Source File

SOURCE=.\SceneVw.cpp
DEP_SCENE=\
	.\stdafx.h\
	.\EasyBit.h\
	.\mainfrm.h\
	.\EasyBdoc.h\
	.\SceneVw.h\
	.\CMyStatusBar.h\
	.\CShapeMenu.h\
	\articles\samples\OpenGL\GLlib\GLlib.h\
	\articles\samples\OpenGL\animate\include\animate.h\
	.\Scene.h\
	.\SceneCI.h\
	.\CSceneBox.h\
	.\CSceneDodec.h\
	.\CScenePyramid.h\
	.\CSimpleDib.h\
	\DEV\MSVC20\INCLUDE\GL\GL.H\
	\DEV\MSVC20\INCLUDE\GL\GLU.H\
	\articles\samples\OpenGL\GLlib\cgl.h\
	\articles\samples\OpenGL\GLlib\glview.h\
	\articles\samples\OpenGL\GLlib\image.h

$(INTDIR)/"SceneVw.obj" :  $(SOURCE)  $(DEP_SCENE) $(INTDIR)\
 $(INTDIR)/stdafx.obj

# End Source File
################################################################################
# Begin Source File

SOURCE=.\EasyBit.rc
DEP_EASYBI=\
	.\res\msdn.ico\
	.\res\EasyBit.ico\
	.\res\toolbar.bmp\
	.\res\EasyBit.rc2

$(INTDIR)/"EasyBit.res" :  $(SOURCE)  $(DEP_EASYBI) $(INTDIR)
   $(RSC) $(RSC_PROJ)  $(SOURCE) 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\Scene.cpp
DEP_SCENE_=\
	.\stdafx.h\
	\DEV\MSVC20\INCLUDE\GL\GL.H\
	\DEV\MSVC20\INCLUDE\GL\GLU.H\
	\articles\samples\OpenGL\GLlib\GLlib.h\
	.\Scene.h\
	.\Shapes.h\
	\articles\samples\OpenGL\GLlib\cgl.h\
	\articles\samples\OpenGL\GLlib\glview.h\
	\articles\samples\OpenGL\GLlib\image.h\
	\articles\samples\OpenGL\animate\include\animate.h

$(INTDIR)/"Scene.obj" :  $(SOURCE)  $(DEP_SCENE_) $(INTDIR)\
 $(INTDIR)/stdafx.obj

# End Source File
################################################################################
# Begin Source File

SOURCE=.\CSimpleDib.cpp
DEP_CSIMP=\
	.\stdafx.h\
	.\CSimpleDib.h

$(INTDIR)/"CSimpleDib.obj" :  $(SOURCE)  $(DEP_CSIMP) $(INTDIR)\
 $(INTDIR)/stdafx.obj

# End Source File
################################################################################
# Begin Source File

SOURCE=.\shapes.cpp
DEP_SHAPE=\
	.\stdafx.h\
	\DEV\MSVC20\INCLUDE\GL\GL.H\
	\DEV\MSVC20\INCLUDE\GL\GLU.H\
	.\Shapes.h

$(INTDIR)/"shapes.obj" :  $(SOURCE)  $(DEP_SHAPE) $(INTDIR)\
 $(INTDIR)/stdafx.obj

# End Source File
################################################################################
# Begin Source File

SOURCE=.\CSceneDodec.cpp
DEP_CSCEN=\
	.\stdafx.h\
	\DEV\MSVC20\INCLUDE\GL\GL.H\
	\DEV\MSVC20\INCLUDE\GL\GLU.H\
	\articles\samples\OpenGL\GLlib\GLlib.h\
	.\CSceneDodec.h\
	.\Shapes.h\
	\articles\samples\OpenGL\GLlib\cgl.h\
	\articles\samples\OpenGL\GLlib\glview.h\
	\articles\samples\OpenGL\GLlib\image.h\
	\articles\samples\OpenGL\animate\include\animate.h

$(INTDIR)/"CSceneDodec.obj" :  $(SOURCE)  $(DEP_CSCEN) $(INTDIR)\
 $(INTDIR)/stdafx.obj

# End Source File
################################################################################
# Begin Source File

SOURCE=.\CSceneBox.cpp
DEP_CSCENE=\
	.\stdafx.h\
	\DEV\MSVC20\INCLUDE\GL\GL.H\
	\DEV\MSVC20\INCLUDE\GL\GLU.H\
	\articles\samples\OpenGL\GLlib\GLlib.h\
	.\CSceneBox.h\
	.\Shapes.h\
	\articles\samples\OpenGL\GLlib\cgl.h\
	\articles\samples\OpenGL\GLlib\glview.h\
	\articles\samples\OpenGL\GLlib\image.h\
	\articles\samples\OpenGL\animate\include\animate.h

$(INTDIR)/"CSceneBox.obj" :  $(SOURCE)  $(DEP_CSCENE) $(INTDIR)\
 $(INTDIR)/stdafx.obj

# End Source File
################################################################################
# Begin Source File

SOURCE=.\CScenePyramid.cpp
DEP_CSCENEP=\
	.\stdafx.h\
	\DEV\MSVC20\INCLUDE\GL\GL.H\
	\DEV\MSVC20\INCLUDE\GL\GLU.H\
	\articles\samples\OpenGL\GLlib\GLlib.h\
	.\CScenePyramid.h\
	.\Shapes.h\
	\articles\samples\OpenGL\GLlib\cgl.h\
	\articles\samples\OpenGL\GLlib\glview.h\
	\articles\samples\OpenGL\GLlib\image.h\
	\articles\samples\OpenGL\animate\include\animate.h

$(INTDIR)/"CScenePyramid.obj" :  $(SOURCE)  $(DEP_CSCENEP) $(INTDIR)\
 $(INTDIR)/stdafx.obj

# End Source File
################################################################################
# Begin Source File

SOURCE=.\SceneCI.cpp
DEP_SCENEC=\
	.\stdafx.h\
	\DEV\MSVC20\INCLUDE\GL\GL.H\
	\DEV\MSVC20\INCLUDE\GL\GLU.H\
	\articles\samples\OpenGL\GLlib\GLlib.h\
	.\SceneCI.h\
	.\Shapes.h\
	\articles\samples\OpenGL\GLlib\cgl.h\
	\articles\samples\OpenGL\GLlib\glview.h\
	\articles\samples\OpenGL\GLlib\image.h\
	\articles\samples\OpenGL\animate\include\animate.h

$(INTDIR)/"SceneCI.obj" :  $(SOURCE)  $(DEP_SCENEC) $(INTDIR)\
 $(INTDIR)/stdafx.obj

# End Source File
################################################################################
# Begin Source File

SOURCE=.\CMyStatusBar.cpp
DEP_CMYST=\
	.\stdafx.h\
	.\CMyStatusBar.h\
	\articles\samples\OpenGL\GLlib\GLlib.h\
	.\CSceneBox.h\
	.\CSceneDodec.h\
	.\CScenePyramid.h\
	.\CSimpleDib.h\
	\DEV\MSVC20\INCLUDE\GL\GL.H\
	\DEV\MSVC20\INCLUDE\GL\GLU.H\
	\articles\samples\OpenGL\GLlib\cgl.h\
	\articles\samples\OpenGL\GLlib\glview.h\
	\articles\samples\OpenGL\GLlib\image.h\
	\articles\samples\OpenGL\animate\include\animate.h

$(INTDIR)/"CMyStatusBar.obj" :  $(SOURCE)  $(DEP_CMYST) $(INTDIR)\
 $(INTDIR)/stdafx.obj

# End Source File
################################################################################
# Begin Source File

SOURCE=.\CShapeMenu.cpp
DEP_CSHAP=\
	.\stdafx.h\
	.\CShapeMenu.h\
	\articles\samples\OpenGL\GLlib\GLlib.h\
	.\CSceneBox.h\
	.\CSceneDodec.h\
	.\CScenePyramid.h\
	.\CSimpleDib.h\
	\DEV\MSVC20\INCLUDE\GL\GL.H\
	\DEV\MSVC20\INCLUDE\GL\GLU.H\
	\articles\samples\OpenGL\GLlib\cgl.h\
	\articles\samples\OpenGL\GLlib\glview.h\
	\articles\samples\OpenGL\GLlib\image.h\
	\articles\samples\OpenGL\animate\include\animate.h

$(INTDIR)/"CShapeMenu.obj" :  $(SOURCE)  $(DEP_CSHAP) $(INTDIR)\
 $(INTDIR)/stdafx.obj

# End Source File
# End Group
# End Project
################################################################################
