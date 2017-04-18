# Microsoft Developer Studio Generated NMAKE File, Format Version 4.10
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Application" 0x0101

!IF "$(CFG)" == ""
CFG=Modelview - Win32 Debug
!MESSAGE No configuration specified.  Defaulting to Modelview - Win32 Debug.
!ENDIF 

!IF "$(CFG)" != "Modelview - Win32 Release" && "$(CFG)" !=\
 "Modelview - Win32 Debug"
!MESSAGE Invalid configuration "$(CFG)" specified.
!MESSAGE You can specify a configuration when running NMAKE on this makefile
!MESSAGE by defining the macro CFG on the command line.  For example:
!MESSAGE 
!MESSAGE NMAKE /f "Modelview.mak" CFG="Modelview - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "Modelview - Win32 Release" (based on "Win32 (x86) Application")
!MESSAGE "Modelview - Win32 Debug" (based on "Win32 (x86) Application")
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
# PROP Target_Last_Scanned "Modelview - Win32 Debug"
RSC=rc.exe
MTL=mktyplib.exe
CPP=cl.exe

!IF  "$(CFG)" == "Modelview - Win32 Release"

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

ALL : "$(OUTDIR)\Modelview.exe"

CLEAN : 
	-@erase "$(INTDIR)\COpenGLView.obj"
	-@erase "$(INTDIR)\MainFrm.obj"
	-@erase "$(INTDIR)\MatrixDialog.obj"
	-@erase "$(INTDIR)\Modelview.obj"
	-@erase "$(INTDIR)\Modelview.pch"
	-@erase "$(INTDIR)\Modelview.res"
	-@erase "$(INTDIR)\ModelviewDoc.obj"
	-@erase "$(INTDIR)\ModelviewView.obj"
	-@erase "$(INTDIR)\StdAfx.obj"
	-@erase "$(OUTDIR)\Modelview.exe"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

# ADD BASE CPP /nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /Yu"stdafx.h" /c
# ADD CPP /nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /Yu"stdafx.h" /c
CPP_PROJ=/nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D\
 "_AFXDLL" /D "_MBCS" /Fp"$(INTDIR)/Modelview.pch" /Yu"stdafx.h" /Fo"$(INTDIR)/"\
 /c 
CPP_OBJS=.\Release/
CPP_SBRS=.\.
# ADD BASE MTL /nologo /D "NDEBUG" /win32
# ADD MTL /nologo /D "NDEBUG" /win32
MTL_PROJ=/nologo /D "NDEBUG" /win32 
# ADD BASE RSC /l 0x409 /d "NDEBUG" /d "_AFXDLL"
# ADD RSC /l 0x409 /d "NDEBUG" /d "_AFXDLL"
RSC_PROJ=/l 0x409 /fo"$(INTDIR)/Modelview.res" /d "NDEBUG" /d "_AFXDLL" 
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
BSC32_FLAGS=/nologo /o"$(OUTDIR)/Modelview.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /machine:I386
# ADD LINK32 opengl32.lib glu32.lib glaux.lib winmm.lib /nologo /subsystem:windows /machine:I386
LINK32_FLAGS=opengl32.lib glu32.lib glaux.lib winmm.lib /nologo\
 /subsystem:windows /incremental:no /pdb:"$(OUTDIR)/Modelview.pdb" /machine:I386\
 /out:"$(OUTDIR)/Modelview.exe" 
LINK32_OBJS= \
	"$(INTDIR)\COpenGLView.obj" \
	"$(INTDIR)\MainFrm.obj" \
	"$(INTDIR)\MatrixDialog.obj" \
	"$(INTDIR)\Modelview.obj" \
	"$(INTDIR)\Modelview.res" \
	"$(INTDIR)\ModelviewDoc.obj" \
	"$(INTDIR)\ModelviewView.obj" \
	"$(INTDIR)\StdAfx.obj"

"$(OUTDIR)\Modelview.exe" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ELSEIF  "$(CFG)" == "Modelview - Win32 Debug"

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

ALL : "$(OUTDIR)\Modelview.exe"

CLEAN : 
	-@erase "$(INTDIR)\COpenGLView.obj"
	-@erase "$(INTDIR)\MainFrm.obj"
	-@erase "$(INTDIR)\MatrixDialog.obj"
	-@erase "$(INTDIR)\Modelview.obj"
	-@erase "$(INTDIR)\Modelview.pch"
	-@erase "$(INTDIR)\Modelview.res"
	-@erase "$(INTDIR)\ModelviewDoc.obj"
	-@erase "$(INTDIR)\ModelviewView.obj"
	-@erase "$(INTDIR)\StdAfx.obj"
	-@erase "$(INTDIR)\vc40.idb"
	-@erase "$(INTDIR)\vc40.pdb"
	-@erase "$(OUTDIR)\Modelview.exe"
	-@erase "$(OUTDIR)\Modelview.ilk"
	-@erase "$(OUTDIR)\Modelview.pdb"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

# ADD BASE CPP /nologo /MDd /W3 /Gm /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /Yu"stdafx.h" /c
# ADD CPP /nologo /MDd /W3 /Gm /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /Yu"stdafx.h" /c
CPP_PROJ=/nologo /MDd /W3 /Gm /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS"\
 /D "_AFXDLL" /D "_MBCS" /Fp"$(INTDIR)/Modelview.pch" /Yu"stdafx.h"\
 /Fo"$(INTDIR)/" /Fd"$(INTDIR)/" /c 
CPP_OBJS=.\Debug/
CPP_SBRS=.\.
# ADD BASE MTL /nologo /D "_DEBUG" /win32
# ADD MTL /nologo /D "_DEBUG" /win32
MTL_PROJ=/nologo /D "_DEBUG" /win32 
# ADD BASE RSC /l 0x409 /d "_DEBUG" /d "_AFXDLL"
# ADD RSC /l 0x409 /d "_DEBUG" /d "_AFXDLL"
RSC_PROJ=/l 0x409 /fo"$(INTDIR)/Modelview.res" /d "_DEBUG" /d "_AFXDLL" 
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
BSC32_FLAGS=/nologo /o"$(OUTDIR)/Modelview.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /debug /machine:I386
# ADD LINK32 opengl32.lib glu32.lib glaux.lib winmm.lib /nologo /subsystem:windows /debug /machine:I386
LINK32_FLAGS=opengl32.lib glu32.lib glaux.lib winmm.lib /nologo\
 /subsystem:windows /incremental:yes /pdb:"$(OUTDIR)/Modelview.pdb" /debug\
 /machine:I386 /out:"$(OUTDIR)/Modelview.exe" 
LINK32_OBJS= \
	"$(INTDIR)\COpenGLView.obj" \
	"$(INTDIR)\MainFrm.obj" \
	"$(INTDIR)\MatrixDialog.obj" \
	"$(INTDIR)\Modelview.obj" \
	"$(INTDIR)\Modelview.res" \
	"$(INTDIR)\ModelviewDoc.obj" \
	"$(INTDIR)\ModelviewView.obj" \
	"$(INTDIR)\StdAfx.obj"

"$(OUTDIR)\Modelview.exe" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
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

# Name "Modelview - Win32 Release"
# Name "Modelview - Win32 Debug"

!IF  "$(CFG)" == "Modelview - Win32 Release"

!ELSEIF  "$(CFG)" == "Modelview - Win32 Debug"

!ENDIF 

################################################################################
# Begin Source File

SOURCE=.\ReadMe.txt

!IF  "$(CFG)" == "Modelview - Win32 Release"

!ELSEIF  "$(CFG)" == "Modelview - Win32 Debug"

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\Modelview.cpp
DEP_CPP_MODEL=\
	".\COpenGLView.h"\
	".\MainFrm.h"\
	".\MatrixDialog.h"\
	".\Modelview.h"\
	".\ModelviewDoc.h"\
	".\ModelviewView.h"\
	".\StdAfx.h"\
	{$(INCLUDE)}"\gl\Gl.h"\
	{$(INCLUDE)}"\gl\Glaux.h"\
	{$(INCLUDE)}"\gl\Glu.h"\
	

"$(INTDIR)\Modelview.obj" : $(SOURCE) $(DEP_CPP_MODEL) "$(INTDIR)"\
 "$(INTDIR)\Modelview.pch"


# End Source File
################################################################################
# Begin Source File

SOURCE=.\StdAfx.cpp
DEP_CPP_STDAF=\
	".\StdAfx.h"\
	

!IF  "$(CFG)" == "Modelview - Win32 Release"

# ADD CPP /Yc"stdafx.h"

BuildCmds= \
	$(CPP) /nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D\
 "_AFXDLL" /D "_MBCS" /Fp"$(INTDIR)/Modelview.pch" /Yc"stdafx.h" /Fo"$(INTDIR)/"\
 /c $(SOURCE) \
	

"$(INTDIR)\StdAfx.obj" : $(SOURCE) $(DEP_CPP_STDAF) "$(INTDIR)"
   $(BuildCmds)

"$(INTDIR)\Modelview.pch" : $(SOURCE) $(DEP_CPP_STDAF) "$(INTDIR)"
   $(BuildCmds)

!ELSEIF  "$(CFG)" == "Modelview - Win32 Debug"

# ADD CPP /Yc"stdafx.h"

BuildCmds= \
	$(CPP) /nologo /MDd /W3 /Gm /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS"\
 /D "_AFXDLL" /D "_MBCS" /Fp"$(INTDIR)/Modelview.pch" /Yc"stdafx.h"\
 /Fo"$(INTDIR)/" /Fd"$(INTDIR)/" /c $(SOURCE) \
	

"$(INTDIR)\StdAfx.obj" : $(SOURCE) $(DEP_CPP_STDAF) "$(INTDIR)"
   $(BuildCmds)

"$(INTDIR)\Modelview.pch" : $(SOURCE) $(DEP_CPP_STDAF) "$(INTDIR)"
   $(BuildCmds)

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\MainFrm.cpp
DEP_CPP_MAINF=\
	".\MainFrm.h"\
	".\Modelview.h"\
	".\StdAfx.h"\
	

"$(INTDIR)\MainFrm.obj" : $(SOURCE) $(DEP_CPP_MAINF) "$(INTDIR)"\
 "$(INTDIR)\Modelview.pch"


# End Source File
################################################################################
# Begin Source File

SOURCE=.\ModelviewDoc.cpp
DEP_CPP_MODELV=\
	".\Modelview.h"\
	".\ModelviewDoc.h"\
	".\StdAfx.h"\
	

"$(INTDIR)\ModelviewDoc.obj" : $(SOURCE) $(DEP_CPP_MODELV) "$(INTDIR)"\
 "$(INTDIR)\Modelview.pch"


# End Source File
################################################################################
# Begin Source File

SOURCE=.\ModelviewView.cpp
DEP_CPP_MODELVI=\
	".\COpenGLView.h"\
	".\MatrixDialog.h"\
	".\Modelview.h"\
	".\ModelviewDoc.h"\
	".\ModelviewView.h"\
	".\StdAfx.h"\
	{$(INCLUDE)}"\gl\Gl.h"\
	{$(INCLUDE)}"\gl\Glaux.h"\
	{$(INCLUDE)}"\gl\Glu.h"\
	

"$(INTDIR)\ModelviewView.obj" : $(SOURCE) $(DEP_CPP_MODELVI) "$(INTDIR)"\
 "$(INTDIR)\Modelview.pch"


# End Source File
################################################################################
# Begin Source File

SOURCE=.\Modelview.rc
DEP_RSC_MODELVIE=\
	".\res\Modelview.ico"\
	".\res\Modelview.rc2"\
	".\res\ModelviewDoc.ico"\
	

"$(INTDIR)\Modelview.res" : $(SOURCE) $(DEP_RSC_MODELVIE) "$(INTDIR)"
   $(RSC) $(RSC_PROJ) $(SOURCE)


# End Source File
################################################################################
# Begin Source File

SOURCE=.\MatrixDialog.cpp
DEP_CPP_MATRI=\
	".\MatrixDialog.h"\
	".\Modelview.h"\
	".\StdAfx.h"\
	{$(INCLUDE)}"\gl\Gl.h"\
	{$(INCLUDE)}"\gl\Glaux.h"\
	{$(INCLUDE)}"\gl\Glu.h"\
	

"$(INTDIR)\MatrixDialog.obj" : $(SOURCE) $(DEP_CPP_MATRI) "$(INTDIR)"\
 "$(INTDIR)\Modelview.pch"


# End Source File
################################################################################
# Begin Source File

SOURCE=.\COpenGLView.cpp
DEP_CPP_COPEN=\
	".\COpenGLView.h"\
	".\StdAfx.h"\
	

"$(INTDIR)\COpenGLView.obj" : $(SOURCE) $(DEP_CPP_COPEN) "$(INTDIR)"\
 "$(INTDIR)\Modelview.pch"


# End Source File
# End Target
# End Project
################################################################################
