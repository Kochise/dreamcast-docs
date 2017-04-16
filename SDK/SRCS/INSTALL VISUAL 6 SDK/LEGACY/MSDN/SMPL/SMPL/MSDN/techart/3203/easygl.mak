# Microsoft Visual C++ Generated NMAKE File, Format Version 2.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Application" 0x0101
# TARGTYPE "Win32 (MIPS) Application" 0x0501
# TARGTYPE "Win32 (ALPHA) Application" 0x0601

!IF "$(CFG)" == ""
CFG=Win32 Debug
!MESSAGE No configuration specified.  Defaulting to Win32 Debug.
!ENDIF 

!IF "$(CFG)" != "Win32 Debug" && "$(CFG)" != "Win32 Release" && "$(CFG)" !=\
 "MIPs Release" && "$(CFG)" != "MIPs Debug" && "$(CFG)" != "Alpha Release" &&\
 "$(CFG)" != "Alpha Debug"
!MESSAGE Invalid configuration "$(CFG)" specified.
!MESSAGE You can specify a configuration when running NMAKE on this makefile
!MESSAGE by defining the macro CFG on the command line.  For example:
!MESSAGE 
!MESSAGE NMAKE /f "easygl.mak" CFG="Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "Win32 Debug" (based on "Win32 (x86) Application")
!MESSAGE "Win32 Release" (based on "Win32 (x86) Application")
!MESSAGE "MIPs Release" (based on "Win32 (MIPS) Application")
!MESSAGE "MIPs Debug" (based on "Win32 (MIPS) Application")
!MESSAGE "Alpha Release" (based on "Win32 (ALPHA) Application")
!MESSAGE "Alpha Debug" (based on "Win32 (ALPHA) Application")
!MESSAGE 
!ERROR An invalid configuration is specified.
!ENDIF 

################################################################################
# Begin Project
# PROP Target_Last_Scanned "Win32 Debug"

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

ALL : $(OUTDIR)/""easygl.exe"" $(OUTDIR)/""easygl.bsc""

$(OUTDIR) : 
    if not exist $(OUTDIR)/nul mkdir $(OUTDIR)

MTL=MkTypLib.exe
MTL_PROJ=
CPP=cl.exe
# ADD BASE CPP /nologo /MD /W3 /GX /Zi /Od /D "_DEBUG" /D "WIN32" /D "_WINDOWS" /D "_MBCS" /D "_AFXDLL" /FR /Yu"stdafx.h" /c
# ADD CPP /nologo /MD /W3 /GX /Zi /Od /D "_DEBUG" /D "WIN32" /D "_WINDOWS" /D "_MBCS" /D "_AFXDLL" /FR /Yu"stdafx.h" /c
CPP_PROJ=/nologo /MD /W3 /GX /Zi /Od /D "_DEBUG" /D "WIN32" /D "_WINDOWS" /D\
 "_MBCS" /D "_AFXDLL" /FR$(INTDIR)/ /Fp$(OUTDIR)/"easygl.pch" /Yu"stdafx.h"\
 /Fo$(INTDIR)/ /Fd$(OUTDIR)/"easygl.pdb" /c 
CPP_OBJS=".\x86-d/"

.c{$(CPP_OBJS)}.obj:
   $(CPP) $(CPP_PROJ) $<  

.cpp{$(CPP_OBJS)}.obj:
   $(CPP) $(CPP_PROJ) $<  

.cxx{$(CPP_OBJS)}.obj:
   $(CPP) $(CPP_PROJ) $<  

RSC=rc.exe
# ADD BASE RSC /l 0x409 /d "_DEBUG" /d "_AFXDLL"
# ADD RSC /l 0x409 /d "_DEBUG" /d "_AFXDLL"
RSC_PROJ=/l 0x409 /fo$(INTDIR)/"easygl.res" /d "_DEBUG" /d "_AFXDLL" 
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
BSC32_FLAGS=/nologo /o$(OUTDIR)/"easygl.bsc" 
BSC32_SBRS= \
	$(INTDIR)/"stdafx.sbr" \
	$(INTDIR)/"easygl.sbr" \
	$(INTDIR)/"mainfrm.sbr" \
	$(INTDIR)/"easygdoc.sbr" \
	$(INTDIR)/"Scene.sbr" \
	$(INTDIR)/"SceneVw.sbr"

$(OUTDIR)/"easygl.bsc" : $(OUTDIR)  $(BSC32_SBRS)
    $(BSC32) @<<
  $(BSC32_FLAGS) $(BSC32_SBRS)
<<

LINK32=link.exe
# ADD BASE LINK32 /NOLOGO /SUBSYSTEM:windows /DEBUG /MACHINE:I386
# SUBTRACT BASE LINK32 /PDB:none
# ADD LINK32 GLlib-d.lib opengl32.lib glu32.lib glaux.lib /NOLOGO /SUBSYSTEM:windows /DEBUG /MACHINE:I386
# SUBTRACT LINK32 /PDB:none
LINK32_FLAGS=GLlib-d.lib opengl32.lib glu32.lib glaux.lib /NOLOGO\
 /SUBSYSTEM:windows /INCREMENTAL:yes /PDB:$(OUTDIR)/"easygl.pdb" /DEBUG\
 /MACHINE:I386 /OUT:$(OUTDIR)/"easygl.exe" 
DEF_FILE=
LINK32_OBJS= \
	$(INTDIR)/"stdafx.obj" \
	$(INTDIR)/"easygl.obj" \
	$(INTDIR)/"mainfrm.obj" \
	$(INTDIR)/"easygdoc.obj" \
	$(INTDIR)/"easygl.res" \
	$(INTDIR)/"Scene.obj" \
	$(INTDIR)/"SceneVw.obj"

$(OUTDIR)/"easygl.exe" : $(OUTDIR)  $(DEF_FILE) $(LINK32_OBJS)
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

ALL : $(OUTDIR)/""easygl.exe"" $(OUTDIR)/""easygl.bsc""

$(OUTDIR) : 
    if not exist $(OUTDIR)/nul mkdir $(OUTDIR)

MTL=MkTypLib.exe
MTL_PROJ=
CPP=cl.exe
# ADD BASE CPP /nologo /MD /W3 /GX /O2 /D "NDEBUG" /D "WIN32" /D "_WINDOWS" /D "_MBCS" /D "_AFXDLL" /FR /Yu"stdafx.h" /c
# ADD CPP /nologo /MD /W3 /GX /O2 /D "NDEBUG" /D "WIN32" /D "_WINDOWS" /D "_MBCS" /D "_AFXDLL" /FR /Yu"stdafx.h" /c
CPP_PROJ=/nologo /MD /W3 /GX /O2 /D "NDEBUG" /D "WIN32" /D "_WINDOWS" /D\
 "_MBCS" /D "_AFXDLL" /FR$(INTDIR)/ /Fp$(OUTDIR)/"easygl.pch" /Yu"stdafx.h"\
 /Fo$(INTDIR)/ /c 
CPP_OBJS=".\x86-r/"

.c{$(CPP_OBJS)}.obj:
   $(CPP) $(CPP_PROJ) $<  

.cpp{$(CPP_OBJS)}.obj:
   $(CPP) $(CPP_PROJ) $<  

.cxx{$(CPP_OBJS)}.obj:
   $(CPP) $(CPP_PROJ) $<  

RSC=rc.exe
# ADD BASE RSC /l 0x409 /d "NDEBUG" /d "_AFXDLL"
# ADD RSC /l 0x409 /d "NDEBUG" /d "_AFXDLL"
RSC_PROJ=/l 0x409 /fo$(INTDIR)/"easygl.res" /d "NDEBUG" /d "_AFXDLL" 
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
BSC32_FLAGS=/nologo /o$(OUTDIR)/"easygl.bsc" 
BSC32_SBRS= \
	$(INTDIR)/"stdafx.sbr" \
	$(INTDIR)/"easygl.sbr" \
	$(INTDIR)/"mainfrm.sbr" \
	$(INTDIR)/"easygdoc.sbr" \
	$(INTDIR)/"Scene.sbr" \
	$(INTDIR)/"SceneVw.sbr"

$(OUTDIR)/"easygl.bsc" : $(OUTDIR)  $(BSC32_SBRS)
    $(BSC32) @<<
  $(BSC32_FLAGS) $(BSC32_SBRS)
<<

LINK32=link.exe
# ADD BASE LINK32 /NOLOGO /SUBSYSTEM:windows /MACHINE:I386
# SUBTRACT BASE LINK32 /PDB:none
# ADD LINK32 GLlib.lib opengl32.lib glu32.lib glaux.lib /NOLOGO /SUBSYSTEM:windows /MACHINE:I386
# SUBTRACT LINK32 /PDB:none
LINK32_FLAGS=GLlib.lib opengl32.lib glu32.lib glaux.lib /NOLOGO\
 /SUBSYSTEM:windows /INCREMENTAL:no /PDB:$(OUTDIR)/"easygl.pdb" /MACHINE:I386\
 /OUT:$(OUTDIR)/"easygl.exe" 
DEF_FILE=
LINK32_OBJS= \
	$(INTDIR)/"stdafx.obj" \
	$(INTDIR)/"easygl.obj" \
	$(INTDIR)/"mainfrm.obj" \
	$(INTDIR)/"easygdoc.obj" \
	$(INTDIR)/"easygl.res" \
	$(INTDIR)/"Scene.obj" \
	$(INTDIR)/"SceneVw.obj"

$(OUTDIR)/"easygl.exe" : $(OUTDIR)  $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ELSEIF  "$(CFG)" == "MIPs Release"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "MIPs_Rel"
# PROP BASE Intermediate_Dir "MIPs_Rel"
# PROP Use_MFC 2
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "MIPs-r"
# PROP Intermediate_Dir "MIPS-r"
OUTDIR=.\MIPs-r
INTDIR=.\MIPS-r

ALL : $(OUTDIR)/"""easygl.exe""" $(OUTDIR)/"""easygl.bsc"""

$(OUTDIR) : 
    if not exist $(OUTDIR)/nul mkdir $(OUTDIR)

MTL=MkTypLib.exe
# ADD BASE MTL /nologo /D "NDEBUG" /mips
# ADD MTL /nologo /D "NDEBUG" /mips
MTL_PROJ=/nologo /D "NDEBUG" /mips 
CPP=cl.exe
# ADD BASE CPP /nologo /ML /Gt0 /QMOb2000 /W3 /GX /YX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /FR /c
# ADD CPP /nologo /MD /Gt0 /QMOb2000 /W3 /GX /YX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /FR /c
CPP_PROJ=/nologo /MD /Gt0 /QMOb2000 /W3 /GX /YX /O2 /D "WIN32" /D "NDEBUG" /D\
 "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /FR$(INTDIR)/ /Fp$(OUTDIR)/"easygl.pch"\
 /Fo$(INTDIR)/ /c 
CPP_OBJS=".\MIPS-r/"

.c{$(CPP_OBJS)}.obj:
   $(CPP) $(CPP_PROJ) $<  

.cpp{$(CPP_OBJS)}.obj:
   $(CPP) $(CPP_PROJ) $<  

.cxx{$(CPP_OBJS)}.obj:
   $(CPP) $(CPP_PROJ) $<  

RSC=rc.exe
# ADD BASE RSC /l 0x409 /d "NDEBUG"
# ADD RSC /l 0x409 /d "NDEBUG" /d "_AFXDLL"
RSC_PROJ=/l 0x409 /fo$(INTDIR)/"easygl.res" /d "NDEBUG" /d "_AFXDLL" 
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
BSC32_FLAGS=/nologo /o$(OUTDIR)/"easygl.bsc" 
BSC32_SBRS= \
	$(INTDIR)/"stdafx.sbr" \
	$(INTDIR)/"easygl.sbr" \
	$(INTDIR)/"mainfrm.sbr" \
	$(INTDIR)/"easygdoc.sbr" \
	$(INTDIR)/"Scene.sbr" \
	$(INTDIR)/"SceneVw.sbr"

$(OUTDIR)/"easygl.bsc" : $(OUTDIR)  $(BSC32_SBRS)
    $(BSC32) @<<
  $(BSC32_FLAGS) $(BSC32_SBRS)
<<

LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib /NOLOGO /SUBSYSTEM:windows /MACHINE:MIPS
# ADD LINK32 opengl32.lib glu32.lib glaux.lib GLlib.dll /NOLOGO /SUBSYSTEM:windows /MACHINE:MIPS
LINK32_FLAGS=opengl32.lib glu32.lib glaux.lib GLlib.dll /NOLOGO\
 /SUBSYSTEM:windows /PDB:$(OUTDIR)/"easygl.pdb" /MACHINE:MIPS\
 /OUT:$(OUTDIR)/"easygl.exe" 
DEF_FILE=
LINK32_OBJS= \
	$(INTDIR)/"stdafx.obj" \
	$(INTDIR)/"easygl.obj" \
	$(INTDIR)/"mainfrm.obj" \
	$(INTDIR)/"easygdoc.obj" \
	$(INTDIR)/"easygl.res" \
	$(INTDIR)/"Scene.obj" \
	$(INTDIR)/"SceneVw.obj"

$(OUTDIR)/"easygl.exe" : $(OUTDIR)  $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ELSEIF  "$(CFG)" == "MIPs Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "MIPs_Deb"
# PROP BASE Intermediate_Dir "MIPs_Deb"
# PROP Use_MFC 2
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "MIPS-d"
# PROP Intermediate_Dir "MIPS-d"
OUTDIR=.\MIPS-d
INTDIR=.\MIPS-d

ALL : $(OUTDIR)/"""easygl.exe""" $(OUTDIR)/"""easygl.bsc"""

$(OUTDIR) : 
    if not exist $(OUTDIR)/nul mkdir $(OUTDIR)

MTL=MkTypLib.exe
# ADD BASE MTL /nologo /D "_DEBUG" /mips
# ADD MTL /nologo /D "_DEBUG" /mips
MTL_PROJ=/nologo /D "_DEBUG" /mips 
CPP=cl.exe
# ADD BASE CPP /nologo /ML /Gt0 /QMOb2000 /W3 /GX /Zi /YX /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /FR /c
# ADD CPP /nologo /MD /Gt0 /QMOb2000 /W3 /GX /Zi /YX /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /FR /c
CPP_PROJ=/nologo /MD /Gt0 /QMOb2000 /W3 /GX /Zi /YX /Od /D "WIN32" /D "_DEBUG"\
 /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /FR$(INTDIR)/ /Fp$(OUTDIR)/"easygl.pch"\
 /Fo$(INTDIR)/ /Fd$(OUTDIR)/"easygl.pdb" /c 
CPP_OBJS=".\MIPS-d/"

.c{$(CPP_OBJS)}.obj:
   $(CPP) $(CPP_PROJ) $<  

.cpp{$(CPP_OBJS)}.obj:
   $(CPP) $(CPP_PROJ) $<  

.cxx{$(CPP_OBJS)}.obj:
   $(CPP) $(CPP_PROJ) $<  

RSC=rc.exe
# ADD BASE RSC /l 0x409 /d "_DEBUG"
# ADD RSC /l 0x409 /d "_DEBUG" /d "_AFXDLL"
RSC_PROJ=/l 0x409 /fo$(INTDIR)/"easygl.res" /d "_DEBUG" /d "_AFXDLL" 
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
BSC32_FLAGS=/nologo /o$(OUTDIR)/"easygl.bsc" 
BSC32_SBRS= \
	$(INTDIR)/"stdafx.sbr" \
	$(INTDIR)/"easygl.sbr" \
	$(INTDIR)/"mainfrm.sbr" \
	$(INTDIR)/"easygdoc.sbr" \
	$(INTDIR)/"Scene.sbr" \
	$(INTDIR)/"SceneVw.sbr"

$(OUTDIR)/"easygl.bsc" : $(OUTDIR)  $(BSC32_SBRS)
    $(BSC32) @<<
  $(BSC32_FLAGS) $(BSC32_SBRS)
<<

LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib /NOLOGO /SUBSYSTEM:windows /DEBUG /MACHINE:MIPS
# ADD LINK32 opengl32.lib glu32.lib glaux.lib GLlib-d.lib /NOLOGO /SUBSYSTEM:windows /DEBUG /MACHINE:MIPS
LINK32_FLAGS=opengl32.lib glu32.lib glaux.lib GLlib-d.lib /NOLOGO\
 /SUBSYSTEM:windows /PDB:$(OUTDIR)/"easygl.pdb" /DEBUG /MACHINE:MIPS\
 /OUT:$(OUTDIR)/"easygl.exe" 
DEF_FILE=
LINK32_OBJS= \
	$(INTDIR)/"stdafx.obj" \
	$(INTDIR)/"easygl.obj" \
	$(INTDIR)/"mainfrm.obj" \
	$(INTDIR)/"easygdoc.obj" \
	$(INTDIR)/"easygl.res" \
	$(INTDIR)/"Scene.obj" \
	$(INTDIR)/"SceneVw.obj"

$(OUTDIR)/"easygl.exe" : $(OUTDIR)  $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ELSEIF  "$(CFG)" == "Alpha Release"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "Alpha_Re"
# PROP BASE Intermediate_Dir "Alpha_Re"
# PROP Use_MFC 2
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "Alpha-r"
# PROP Intermediate_Dir "Alpha-r"
OUTDIR=.\Alpha-r
INTDIR=.\Alpha-r

ALL : $(OUTDIR)/"easygl.exe" $(OUTDIR)/"easygl.bsc"

$(OUTDIR) : 
    if not exist $(OUTDIR)/nul mkdir $(OUTDIR)

MTL=MkTypLib.exe
# ADD BASE MTL /nologo /D "NDEBUG" /alpha
# ADD MTL /nologo /D "NDEBUG" /alpha
MTL_PROJ=/nologo /D "NDEBUG" /alpha 
CPP=cl.exe
# ADD BASE CPP /nologo /Gt0 /W3 /GX /YX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /FR /c
# ADD CPP /nologo /MD /Gt0 /W3 /GX /YX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /FR /c
CPP_PROJ=/nologo /MD /Gt0 /W3 /GX /YX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS"\
 /D "_AFXDLL" /D "_MBCS" /FR$(INTDIR)/ /Fp$(OUTDIR)/"easygl.pch" /Fo$(INTDIR)/\
 /c 
CPP_OBJS=".\Alpha-r/"

.c{$(CPP_OBJS)}.obj:
   $(CPP) $(CPP_PROJ) $<  

.cpp{$(CPP_OBJS)}.obj:
   $(CPP) $(CPP_PROJ) $<  

.cxx{$(CPP_OBJS)}.obj:
   $(CPP) $(CPP_PROJ) $<  

RSC=rc.exe
# ADD BASE RSC /l 0x409 /d "NDEBUG"
# ADD RSC /l 0x409 /d "NDEBUG" /d "_AFXDLL"
RSC_PROJ=/l 0x409 /fo$(INTDIR)/"easygl.res" /d "NDEBUG" /d "_AFXDLL" 
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
BSC32_FLAGS=/nologo /o$(OUTDIR)/"easygl.bsc" 
BSC32_SBRS= \
	$(INTDIR)/"stdafx.sbr" \
	$(INTDIR)/"easygl.sbr" \
	$(INTDIR)/"mainfrm.sbr" \
	$(INTDIR)/"easygdoc.sbr" \
	$(INTDIR)/"Scene.sbr" \
	$(INTDIR)/"SceneVw.sbr"

$(OUTDIR)/"easygl.bsc" : $(OUTDIR)  $(BSC32_SBRS)
    $(BSC32) @<<
  $(BSC32_FLAGS) $(BSC32_SBRS)
<<

LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib /NOLOGO /SUBSYSTEM:windows /MACHINE:ALPHA
# ADD LINK32 opengl32.lib glu32.lib glaux.lib GLlib.lib /NOLOGO /SUBSYSTEM:windows /MACHINE:ALPHA
LINK32_FLAGS=opengl32.lib glu32.lib glaux.lib GLlib.lib /NOLOGO\
 /SUBSYSTEM:windows /PDB:$(OUTDIR)/"easygl.pdb" /MACHINE:ALPHA\
 /OUT:$(OUTDIR)/"easygl.exe" 
DEF_FILE=
LINK32_OBJS= \
	$(INTDIR)/"stdafx.obj" \
	$(INTDIR)/"easygl.obj" \
	$(INTDIR)/"mainfrm.obj" \
	$(INTDIR)/"easygdoc.obj" \
	$(INTDIR)/"easygl.res" \
	$(INTDIR)/"Scene.obj" \
	$(INTDIR)/"SceneVw.obj"

$(OUTDIR)/"easygl.exe" : $(OUTDIR)  $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ELSEIF  "$(CFG)" == "Alpha Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "Alpha_De"
# PROP BASE Intermediate_Dir "Alpha_De"
# PROP Use_MFC 2
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "Alpha-d"
# PROP Intermediate_Dir "Alpha-d"
OUTDIR=.\Alpha-d
INTDIR=.\Alpha-d

ALL : $(OUTDIR)/"easygl.exe" $(OUTDIR)/"easygl.bsc"

$(OUTDIR) : 
    if not exist $(OUTDIR)/nul mkdir $(OUTDIR)

MTL=MkTypLib.exe
# ADD BASE MTL /nologo /D "_DEBUG" /alpha
# ADD MTL /nologo /D "_DEBUG" /alpha
MTL_PROJ=/nologo /D "_DEBUG" /alpha 
CPP=cl.exe
# ADD BASE CPP /nologo /Gt0 /W3 /GX /Zi /YX /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /FR /c
# ADD CPP /nologo /MD /Gt0 /W3 /GX /Zi /YX /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /FR /c
CPP_PROJ=/nologo /MD /Gt0 /W3 /GX /Zi /YX /Od /D "WIN32" /D "_DEBUG" /D\
 "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /FR$(INTDIR)/ /Fp$(OUTDIR)/"easygl.pch"\
 /Fo$(INTDIR)/ /Fd$(OUTDIR)/"easygl.pdb" /c 
CPP_OBJS=".\Alpha-d/"

.c{$(CPP_OBJS)}.obj:
   $(CPP) $(CPP_PROJ) $<  

.cpp{$(CPP_OBJS)}.obj:
   $(CPP) $(CPP_PROJ) $<  

.cxx{$(CPP_OBJS)}.obj:
   $(CPP) $(CPP_PROJ) $<  

RSC=rc.exe
# ADD BASE RSC /l 0x409 /d "_DEBUG"
# ADD RSC /l 0x409 /d "_DEBUG" /d "_AFXDLL"
RSC_PROJ=/l 0x409 /fo$(INTDIR)/"easygl.res" /d "_DEBUG" /d "_AFXDLL" 
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
BSC32_FLAGS=/nologo /o$(OUTDIR)/"easygl.bsc" 
BSC32_SBRS= \
	$(INTDIR)/"stdafx.sbr" \
	$(INTDIR)/"easygl.sbr" \
	$(INTDIR)/"mainfrm.sbr" \
	$(INTDIR)/"easygdoc.sbr" \
	$(INTDIR)/"Scene.sbr" \
	$(INTDIR)/"SceneVw.sbr"

$(OUTDIR)/"easygl.bsc" : $(OUTDIR)  $(BSC32_SBRS)
    $(BSC32) @<<
  $(BSC32_FLAGS) $(BSC32_SBRS)
<<

LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib /NOLOGO /SUBSYSTEM:windows /DEBUG /MACHINE:ALPHA
# ADD LINK32 opengl32.lib glu32.lib glaux.lib GLlib-d.lib /NOLOGO /SUBSYSTEM:windows /DEBUG /MACHINE:ALPHA
LINK32_FLAGS=opengl32.lib glu32.lib glaux.lib GLlib-d.lib /NOLOGO\
 /SUBSYSTEM:windows /PDB:$(OUTDIR)/"easygl.pdb" /DEBUG /MACHINE:ALPHA\
 /OUT:$(OUTDIR)/"easygl.exe" 
DEF_FILE=
LINK32_OBJS= \
	$(INTDIR)/"stdafx.obj" \
	$(INTDIR)/"easygl.obj" \
	$(INTDIR)/"mainfrm.obj" \
	$(INTDIR)/"easygdoc.obj" \
	$(INTDIR)/"easygl.res" \
	$(INTDIR)/"Scene.obj" \
	$(INTDIR)/"SceneVw.obj"

$(OUTDIR)/"easygl.exe" : $(OUTDIR)  $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ENDIF 

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
 "_MBCS" /D "_AFXDLL" /FR$(INTDIR)/ /Fp$(OUTDIR)/"easygl.pch" /Yc"stdafx.h"\
 /Fo$(INTDIR)/ /Fd$(OUTDIR)/"easygl.pdb" /c  $(SOURCE) 

!ELSEIF  "$(CFG)" == "Win32 Release"

# ADD BASE CPP /Yc"stdafx.h"
# ADD CPP /Yc"stdafx.h"

$(INTDIR)/"stdafx.obj" :  $(SOURCE)  $(DEP_STDAF) $(INTDIR)
   $(CPP) /nologo /MD /W3 /GX /O2 /D "NDEBUG" /D "WIN32" /D "_WINDOWS" /D\
 "_MBCS" /D "_AFXDLL" /FR$(INTDIR)/ /Fp$(OUTDIR)/"easygl.pch" /Yc"stdafx.h"\
 /Fo$(INTDIR)/ /c  $(SOURCE) 

!ELSEIF  "$(CFG)" == "MIPs Release"

$(INTDIR)/"stdafx.obj" :  $(SOURCE)  $(DEP_STDAF) $(INTDIR)

!ELSEIF  "$(CFG)" == "MIPs Debug"

$(INTDIR)/"stdafx.obj" :  $(SOURCE)  $(DEP_STDAF) $(INTDIR)

!ELSEIF  "$(CFG)" == "Alpha Release"

$(INTDIR)/"stdafx.obj" :  $(SOURCE)  $(DEP_STDAF) $(INTDIR)

!ELSEIF  "$(CFG)" == "Alpha Debug"

$(INTDIR)/"stdafx.obj" :  $(SOURCE)  $(DEP_STDAF) $(INTDIR)

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\easygl.cpp
DEP_EASYG=\
	.\stdafx.h\
	.\easygl.h\
	.\mainfrm.h\
	.\easygdoc.h\
	.\SceneVw.h\
	..\GLlib\GLlib.h\
	.\Scene.h\
	\articles\samples\OpenGL\GLlib\cgl.h\
	\articles\samples\OpenGL\GLlib\glview.h

!IF  "$(CFG)" == "Win32 Debug"

$(INTDIR)/"easygl.obj" :  $(SOURCE)  $(DEP_EASYG) $(INTDIR)\
 $(INTDIR)/stdafx.obj

!ELSEIF  "$(CFG)" == "Win32 Release"

$(INTDIR)/"easygl.obj" :  $(SOURCE)  $(DEP_EASYG) $(INTDIR)\
 $(INTDIR)/stdafx.obj

!ELSEIF  "$(CFG)" == "MIPs Release"

$(INTDIR)/"easygl.obj" :  $(SOURCE)  $(DEP_EASYG) $(INTDIR)

!ELSEIF  "$(CFG)" == "MIPs Debug"

$(INTDIR)/"easygl.obj" :  $(SOURCE)  $(DEP_EASYG) $(INTDIR)

!ELSEIF  "$(CFG)" == "Alpha Release"

$(INTDIR)/"easygl.obj" :  $(SOURCE)  $(DEP_EASYG) $(INTDIR)

!ELSEIF  "$(CFG)" == "Alpha Debug"

$(INTDIR)/"easygl.obj" :  $(SOURCE)  $(DEP_EASYG) $(INTDIR)

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\mainfrm.cpp
DEP_MAINF=\
	.\stdafx.h\
	.\easygl.h\
	.\mainfrm.h

!IF  "$(CFG)" == "Win32 Debug"

$(INTDIR)/"mainfrm.obj" :  $(SOURCE)  $(DEP_MAINF) $(INTDIR)\
 $(INTDIR)/stdafx.obj

!ELSEIF  "$(CFG)" == "Win32 Release"

$(INTDIR)/"mainfrm.obj" :  $(SOURCE)  $(DEP_MAINF) $(INTDIR)\
 $(INTDIR)/stdafx.obj

!ELSEIF  "$(CFG)" == "MIPs Release"

$(INTDIR)/"mainfrm.obj" :  $(SOURCE)  $(DEP_MAINF) $(INTDIR)

!ELSEIF  "$(CFG)" == "MIPs Debug"

$(INTDIR)/"mainfrm.obj" :  $(SOURCE)  $(DEP_MAINF) $(INTDIR)

!ELSEIF  "$(CFG)" == "Alpha Release"

$(INTDIR)/"mainfrm.obj" :  $(SOURCE)  $(DEP_MAINF) $(INTDIR)

!ELSEIF  "$(CFG)" == "Alpha Debug"

$(INTDIR)/"mainfrm.obj" :  $(SOURCE)  $(DEP_MAINF) $(INTDIR)

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\easygdoc.cpp
DEP_EASYGD=\
	.\stdafx.h\
	.\easygl.h\
	.\easygdoc.h

!IF  "$(CFG)" == "Win32 Debug"

$(INTDIR)/"easygdoc.obj" :  $(SOURCE)  $(DEP_EASYGD) $(INTDIR)\
 $(INTDIR)/stdafx.obj

!ELSEIF  "$(CFG)" == "Win32 Release"

$(INTDIR)/"easygdoc.obj" :  $(SOURCE)  $(DEP_EASYGD) $(INTDIR)\
 $(INTDIR)/stdafx.obj

!ELSEIF  "$(CFG)" == "MIPs Release"

$(INTDIR)/"easygdoc.obj" :  $(SOURCE)  $(DEP_EASYGD) $(INTDIR)

!ELSEIF  "$(CFG)" == "MIPs Debug"

$(INTDIR)/"easygdoc.obj" :  $(SOURCE)  $(DEP_EASYGD) $(INTDIR)

!ELSEIF  "$(CFG)" == "Alpha Release"

$(INTDIR)/"easygdoc.obj" :  $(SOURCE)  $(DEP_EASYGD) $(INTDIR)

!ELSEIF  "$(CFG)" == "Alpha Debug"

$(INTDIR)/"easygdoc.obj" :  $(SOURCE)  $(DEP_EASYGD) $(INTDIR)

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\easygl.rc
DEP_EASYGL=\
	.\res\easygl.ico\
	.\res\easygl.rc2

!IF  "$(CFG)" == "Win32 Debug"

$(INTDIR)/"easygl.res" :  $(SOURCE)  $(DEP_EASYGL) $(INTDIR)
   $(RSC) $(RSC_PROJ)  $(SOURCE) 

!ELSEIF  "$(CFG)" == "Win32 Release"

$(INTDIR)/"easygl.res" :  $(SOURCE)  $(DEP_EASYGL) $(INTDIR)
   $(RSC) $(RSC_PROJ)  $(SOURCE) 

!ELSEIF  "$(CFG)" == "MIPs Release"

$(INTDIR)/"easygl.res" :  $(SOURCE)  $(DEP_EASYGL) $(INTDIR)
   $(RSC) $(RSC_PROJ)  $(SOURCE) 

!ELSEIF  "$(CFG)" == "MIPs Debug"

$(INTDIR)/"easygl.res" :  $(SOURCE)  $(DEP_EASYGL) $(INTDIR)
   $(RSC) $(RSC_PROJ)  $(SOURCE) 

!ELSEIF  "$(CFG)" == "Alpha Release"

$(INTDIR)/"easygl.res" :  $(SOURCE)  $(DEP_EASYGL) $(INTDIR)
   $(RSC) $(RSC_PROJ)  $(SOURCE) 

!ELSEIF  "$(CFG)" == "Alpha Debug"

$(INTDIR)/"easygl.res" :  $(SOURCE)  $(DEP_EASYGL) $(INTDIR)
   $(RSC) $(RSC_PROJ)  $(SOURCE) 

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\readme.txt
# End Source File
################################################################################
# Begin Source File

SOURCE=.\Scene.cpp
DEP_SCENE=\
	.\stdafx.h\
	..\GLlib\GLlib.h\
	.\Scene.h\
	\articles\samples\OpenGL\GLlib\cgl.h\
	\articles\samples\OpenGL\GLlib\glview.h

!IF  "$(CFG)" == "Win32 Debug"

$(INTDIR)/"Scene.obj" :  $(SOURCE)  $(DEP_SCENE) $(INTDIR) $(INTDIR)/stdafx.obj

!ELSEIF  "$(CFG)" == "Win32 Release"

$(INTDIR)/"Scene.obj" :  $(SOURCE)  $(DEP_SCENE) $(INTDIR) $(INTDIR)/stdafx.obj

!ELSEIF  "$(CFG)" == "MIPs Release"

$(INTDIR)/"Scene.obj" :  $(SOURCE)  $(DEP_SCENE) $(INTDIR)

!ELSEIF  "$(CFG)" == "MIPs Debug"

$(INTDIR)/"Scene.obj" :  $(SOURCE)  $(DEP_SCENE) $(INTDIR)

!ELSEIF  "$(CFG)" == "Alpha Release"

$(INTDIR)/"Scene.obj" :  $(SOURCE)  $(DEP_SCENE) $(INTDIR)

!ELSEIF  "$(CFG)" == "Alpha Debug"

$(INTDIR)/"Scene.obj" :  $(SOURCE)  $(DEP_SCENE) $(INTDIR)

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\SceneVw.cpp
DEP_SCENEV=\
	.\stdafx.h\
	.\easygl.h\
	.\easygdoc.h\
	.\SceneVw.h\
	..\GLlib\GLlib.h\
	.\Scene.h\
	\articles\samples\OpenGL\GLlib\cgl.h\
	\articles\samples\OpenGL\GLlib\glview.h

!IF  "$(CFG)" == "Win32 Debug"

$(INTDIR)/"SceneVw.obj" :  $(SOURCE)  $(DEP_SCENEV) $(INTDIR)\
 $(INTDIR)/stdafx.obj

!ELSEIF  "$(CFG)" == "Win32 Release"

$(INTDIR)/"SceneVw.obj" :  $(SOURCE)  $(DEP_SCENEV) $(INTDIR)\
 $(INTDIR)/stdafx.obj

!ELSEIF  "$(CFG)" == "MIPs Release"

$(INTDIR)/"SceneVw.obj" :  $(SOURCE)  $(DEP_SCENEV) $(INTDIR)

!ELSEIF  "$(CFG)" == "MIPs Debug"

$(INTDIR)/"SceneVw.obj" :  $(SOURCE)  $(DEP_SCENEV) $(INTDIR)

!ELSEIF  "$(CFG)" == "Alpha Release"

$(INTDIR)/"SceneVw.obj" :  $(SOURCE)  $(DEP_SCENEV) $(INTDIR)

!ELSEIF  "$(CFG)" == "Alpha Debug"

$(INTDIR)/"SceneVw.obj" :  $(SOURCE)  $(DEP_SCENEV) $(INTDIR)

!ENDIF 

# End Source File
# End Group
# End Project
################################################################################
