# Microsoft Visual C++ Generated NMAKE File, Format Version 20054
# MSVCPRJ: version 2.00.4251
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Application" 0x0101
# TARGTYPE "Win32 (MIPS) Application" 0x0501
# TARGTYPE "Win32 (ALPHA) Application" 0x0601

!IF "$(CFG)" == ""
CFG=Win32 Debug
!MESSAGE No configuration specified.  Defaulting to Win32 Debug.
!ENDIF 

!IF "$(CFG)" != "Win32 Debug" && "$(CFG)" != "Win32 Release" && "$(CFG)" !=\
 "Alpha Release" && "$(CFG)" != "Alpha Debug" && "$(CFG)" != "MIPs Release" &&\
 "$(CFG)" != "MIPs Debug"
!MESSAGE Invalid configuration "$(CFG)" specified.
!MESSAGE You can specify a configuration when running NMAKE on this makefile
!MESSAGE by defining the macro CFG on the command line.  For example:
!MESSAGE 
!MESSAGE NMAKE /f "EasyDIB.mak" CFG="Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "Win32 Debug" (based on "Win32 (x86) Application")
!MESSAGE "Win32 Release" (based on "Win32 (x86) Application")
!MESSAGE "Alpha Release" (based on "Win32 (ALPHA) Application")
!MESSAGE "Alpha Debug" (based on "Win32 (ALPHA) Application")
!MESSAGE "MIPs Release" (based on "Win32 (MIPS) Application")
!MESSAGE "MIPs Debug" (based on "Win32 (MIPS) Application")
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

ALL : $(OUTDIR)/"""EasyDIB.exe""" $(OUTDIR)/"""EasyDIB.bsc"""

$(OUTDIR) : 
    if not exist $(OUTDIR)/nul mkdir $(OUTDIR)

MTL=MkTypLib.exe
MTL_PROJ=
CPP=cl.exe
# ADD BASE CPP /nologo /MD /W3 /GX /Zi /Od /D "_DEBUG" /D "WIN32" /D "_WINDOWS" /D "_MBCS" /D "_AFXDLL" /FR /Yu"stdafx.h" /c
# ADD CPP /nologo /MD /W3 /GX /Zi /Od /D "_DEBUG" /D "WIN32" /D "_WINDOWS" /D "_MBCS" /D "_AFXDLL" /FR /Yu"stdafx.h" /c
CPP_PROJ=/nologo /MD /W3 /GX /Zi /Od /D "_DEBUG" /D "WIN32" /D "_WINDOWS" /D\
 "_MBCS" /D "_AFXDLL" /FR$(INTDIR)/ /Fp$(OUTDIR)/"EasyDIB.pch" /Yu"stdafx.h"\
 /Fo$(INTDIR)/ /Fd$(OUTDIR)/"EasyDIB.pdb" /c 
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
RSC_PROJ=/l 0x409 /fo$(INTDIR)/"EasyDIB.res" /d "_DEBUG" /d "_AFXDLL" 
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
BSC32_FLAGS=/nologo /o$(OUTDIR)/"EasyDIB.bsc" 
BSC32_SBRS= \
	$(INTDIR)/"stdafx.sbr" \
	$(INTDIR)/"EasyDIB.sbr" \
	$(INTDIR)/"mainfrm.sbr" \
	$(INTDIR)/"EasyDdoc.sbr" \
	$(INTDIR)/"SceneVw.sbr" \
	$(INTDIR)/"Scene.sbr"

$(OUTDIR)/"EasyDIB.bsc" : $(OUTDIR)  $(BSC32_SBRS)
    $(BSC32) @<<
  $(BSC32_FLAGS) $(BSC32_SBRS)
<<

LINK32=link.exe
# ADD BASE LINK32 /NOLOGO /SUBSYSTEM:windows /DEBUG /MACHINE:I386
# SUBTRACT BASE LINK32 /PDB:none
# ADD LINK32 opengl32.lib glu32.lib glaux.lib GLlib-d.lib /NOLOGO /SUBSYSTEM:windows /DEBUG /MACHINE:I386
# SUBTRACT LINK32 /PDB:none
LINK32_FLAGS=opengl32.lib glu32.lib glaux.lib GLlib-d.lib /NOLOGO\
 /SUBSYSTEM:windows /INCREMENTAL:yes /PDB:$(OUTDIR)/"EasyDIB.pdb" /DEBUG\
 /MACHINE:I386 /OUT:$(OUTDIR)/"EasyDIB.exe" 
DEF_FILE=
LINK32_OBJS= \
	$(INTDIR)/"stdafx.obj" \
	$(INTDIR)/"EasyDIB.obj" \
	$(INTDIR)/"mainfrm.obj" \
	$(INTDIR)/"EasyDdoc.obj" \
	$(INTDIR)/"SceneVw.obj" \
	$(INTDIR)/"EasyDIB.res" \
	$(INTDIR)/"Scene.obj"

$(OUTDIR)/"EasyDIB.exe" : $(OUTDIR)  $(DEF_FILE) $(LINK32_OBJS)
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

ALL : $(OUTDIR)/"""EasyDIB.exe""" $(OUTDIR)/"""EasyDIB.bsc"""

$(OUTDIR) : 
    if not exist $(OUTDIR)/nul mkdir $(OUTDIR)

MTL=MkTypLib.exe
MTL_PROJ=
CPP=cl.exe
# ADD BASE CPP /nologo /MD /W3 /GX /O2 /D "NDEBUG" /D "WIN32" /D "_WINDOWS" /D "_MBCS" /D "_AFXDLL" /FR /Yu"stdafx.h" /c
# ADD CPP /nologo /MD /W3 /GX /O2 /D "NDEBUG" /D "WIN32" /D "_WINDOWS" /D "_MBCS" /D "_AFXDLL" /FR /Yu"stdafx.h" /c
CPP_PROJ=/nologo /MD /W3 /GX /O2 /D "NDEBUG" /D "WIN32" /D "_WINDOWS" /D\
 "_MBCS" /D "_AFXDLL" /FR$(INTDIR)/ /Fp$(OUTDIR)/"EasyDIB.pch" /Yu"stdafx.h"\
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
RSC_PROJ=/l 0x409 /fo$(INTDIR)/"EasyDIB.res" /d "NDEBUG" /d "_AFXDLL" 
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
BSC32_FLAGS=/nologo /o$(OUTDIR)/"EasyDIB.bsc" 
BSC32_SBRS= \
	$(INTDIR)/"stdafx.sbr" \
	$(INTDIR)/"EasyDIB.sbr" \
	$(INTDIR)/"mainfrm.sbr" \
	$(INTDIR)/"EasyDdoc.sbr" \
	$(INTDIR)/"SceneVw.sbr" \
	$(INTDIR)/"Scene.sbr"

$(OUTDIR)/"EasyDIB.bsc" : $(OUTDIR)  $(BSC32_SBRS)
    $(BSC32) @<<
  $(BSC32_FLAGS) $(BSC32_SBRS)
<<

LINK32=link.exe
# ADD BASE LINK32 /NOLOGO /SUBSYSTEM:windows /MACHINE:I386
# SUBTRACT BASE LINK32 /PDB:none
# ADD LINK32 opengl32.lib glu32.lib glaux.lib GLlib.lib /NOLOGO /SUBSYSTEM:windows /MACHINE:I386
# SUBTRACT LINK32 /PDB:none
LINK32_FLAGS=opengl32.lib glu32.lib glaux.lib GLlib.lib /NOLOGO\
 /SUBSYSTEM:windows /INCREMENTAL:no /PDB:$(OUTDIR)/"EasyDIB.pdb" /MACHINE:I386\
 /OUT:$(OUTDIR)/"EasyDIB.exe" 
DEF_FILE=
LINK32_OBJS= \
	$(INTDIR)/"stdafx.obj" \
	$(INTDIR)/"EasyDIB.obj" \
	$(INTDIR)/"mainfrm.obj" \
	$(INTDIR)/"EasyDdoc.obj" \
	$(INTDIR)/"SceneVw.obj" \
	$(INTDIR)/"EasyDIB.res" \
	$(INTDIR)/"Scene.obj"

$(OUTDIR)/"EasyDIB.exe" : $(OUTDIR)  $(DEF_FILE) $(LINK32_OBJS)
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

ALL : $(OUTDIR)/"""EasyDIB.exe""" $(OUTDIR)/"""EasyDIB.bsc"""

$(OUTDIR) : 
    if not exist $(OUTDIR)/nul mkdir $(OUTDIR)

MTL=MkTypLib.exe
# ADD BASE MTL /nologo /D "NDEBUG" /alpha
# ADD MTL /nologo /D "NDEBUG" /alpha
MTL_PROJ=/nologo /D "NDEBUG" /alpha 
CPP=cl.exe
# ADD BASE CPP /nologo /ML /Gt0 /W3 /GX /YX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /FR /c
# ADD CPP /nologo /MD /Gt0 /W3 /GX /YX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /FR /c
CPP_PROJ=/nologo /MD /Gt0 /W3 /GX /YX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS"\
 /D "_AFXDLL" /D "_MBCS" /FR$(INTDIR)/ /Fp$(OUTDIR)/"EasyDIB.pch" /Fo$(INTDIR)/\
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
RSC_PROJ=/l 0x409 /fo$(INTDIR)/"EasyDIB.res" /d "NDEBUG" /d "_AFXDLL" 
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
BSC32_FLAGS=/nologo /o$(OUTDIR)/"EasyDIB.bsc" 
BSC32_SBRS= \
	".\Alpha-r\stdafx.sbr" \
	".\Alpha-r\EasyDIB.sbr" \
	".\Alpha-r\mainfrm.sbr" \
	".\Alpha-r\EasyDdoc.sbr" \
	".\Alpha-r\SceneVw.sbr" \
	".\Alpha-r\Scene.sbr"

".\Alpha-r\EasyDIB.bsc" : $(OUTDIR)  $(BSC32_SBRS)
    $(BSC32) @<<
  $(BSC32_FLAGS) $(BSC32_SBRS)
<<

LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib /NOLOGO /SUBSYSTEM:windows /MACHINE:ALPHA
# ADD LINK32 opengl32.lib glu32.lib glaux.lib GLlib.lib /NOLOGO /SUBSYSTEM:windows /MACHINE:ALPHA
LINK32_FLAGS=opengl32.lib glu32.lib glaux.lib GLlib.lib /NOLOGO\
 /SUBSYSTEM:windows /PDB:$(OUTDIR)/"EasyDIB.pdb" /MACHINE:ALPHA\
 /OUT:$(OUTDIR)/"EasyDIB.exe" 
DEF_FILE=
LINK32_OBJS= \
	".\Alpha-r\stdafx.obj" \
	".\Alpha-r\EasyDIB.obj" \
	".\Alpha-r\mainfrm.obj" \
	".\Alpha-r\EasyDdoc.obj" \
	".\Alpha-r\SceneVw.obj" \
	".\Alpha-r\EasyDIB.res" \
	".\Alpha-r\Scene.obj"

".\Alpha-r\EasyDIB.exe" : $(OUTDIR)  $(DEF_FILE) $(LINK32_OBJS)
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

ALL : $(OUTDIR)/"""EasyDIB.exe""" $(OUTDIR)/"""EasyDIB.bsc"""

$(OUTDIR) : 
    if not exist $(OUTDIR)/nul mkdir $(OUTDIR)

MTL=MkTypLib.exe
# ADD BASE MTL /nologo /D "_DEBUG" /alpha
# ADD MTL /nologo /D "_DEBUG" /alpha
MTL_PROJ=/nologo /D "_DEBUG" /alpha 
CPP=cl.exe
# ADD BASE CPP /nologo /ML /Gt0 /W3 /GX /Zi /YX /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /FR /c
# ADD CPP /nologo /MD /Gt0 /W3 /GX /Zi /YX /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /FR /c
CPP_PROJ=/nologo /MD /Gt0 /W3 /GX /Zi /YX /Od /D "WIN32" /D "_DEBUG" /D\
 "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /FR$(INTDIR)/ /Fp$(OUTDIR)/"EasyDIB.pch"\
 /Fo$(INTDIR)/ /Fd$(OUTDIR)/"EasyDIB.pdb" /c 
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
RSC_PROJ=/l 0x409 /fo$(INTDIR)/"EasyDIB.res" /d "_DEBUG" /d "_AFXDLL" 
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
BSC32_FLAGS=/nologo /o$(OUTDIR)/"EasyDIB.bsc" 
BSC32_SBRS= \
	".\Alpha-d\stdafx.sbr" \
	".\Alpha-d\EasyDIB.sbr" \
	".\Alpha-d\mainfrm.sbr" \
	".\Alpha-d\EasyDdoc.sbr" \
	".\Alpha-d\SceneVw.sbr" \
	".\Alpha-d\Scene.sbr"

".\Alpha-d\EasyDIB.bsc" : $(OUTDIR)  $(BSC32_SBRS)
    $(BSC32) @<<
  $(BSC32_FLAGS) $(BSC32_SBRS)
<<

LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib /NOLOGO /SUBSYSTEM:windows /DEBUG /MACHINE:ALPHA
# ADD LINK32 opengl32.lib glu32.lib glaux.lib GLlib-d.lib /NOLOGO /SUBSYSTEM:windows /DEBUG /MACHINE:ALPHA
LINK32_FLAGS=opengl32.lib glu32.lib glaux.lib GLlib-d.lib /NOLOGO\
 /SUBSYSTEM:windows /PDB:$(OUTDIR)/"EasyDIB.pdb" /DEBUG /MACHINE:ALPHA\
 /OUT:$(OUTDIR)/"EasyDIB.exe" 
DEF_FILE=
LINK32_OBJS= \
	".\Alpha-d\stdafx.obj" \
	".\Alpha-d\EasyDIB.obj" \
	".\Alpha-d\mainfrm.obj" \
	".\Alpha-d\EasyDdoc.obj" \
	".\Alpha-d\SceneVw.obj" \
	".\Alpha-d\EasyDIB.res" \
	".\Alpha-d\Scene.obj"

".\Alpha-d\EasyDIB.exe" : $(OUTDIR)  $(DEF_FILE) $(LINK32_OBJS)
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
# PROP Output_Dir "MIPS-r"
# PROP Intermediate_Dir "MIPs-r"
OUTDIR=.\MIPS-r
INTDIR=.\MIPs-r

ALL : $(OUTDIR)/"EasyDIB.exe" $(OUTDIR)/"EasyDIB.bsc"

$(OUTDIR) : 
    if not exist $(OUTDIR)/nul mkdir $(OUTDIR)

MTL=MkTypLib.exe
# ADD BASE MTL /nologo /D "NDEBUG" /mips
# ADD MTL /nologo /D "NDEBUG" /mips
MTL_PROJ=/nologo /D "NDEBUG" /mips 
CPP=cl.exe
# ADD BASE CPP /nologo /Gt0 /QMOb2000 /W3 /GX /YX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /FR /c
# ADD CPP /nologo /MD /Gt0 /QMOb2000 /W3 /GX /YX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /FR /c
CPP_PROJ=/nologo /MD /Gt0 /QMOb2000 /W3 /GX /YX /O2 /D "WIN32" /D "NDEBUG" /D\
 "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /FR$(INTDIR)/ /Fp$(OUTDIR)/"EasyDIB.pch"\
 /Fo$(INTDIR)/ /c 
CPP_OBJS=".\MIPs-r/"

.c{$(CPP_OBJS)}.obj:
   $(CPP) $(CPP_PROJ) $<  

.cpp{$(CPP_OBJS)}.obj:
   $(CPP) $(CPP_PROJ) $<  

.cxx{$(CPP_OBJS)}.obj:
   $(CPP) $(CPP_PROJ) $<  

RSC=rc.exe
# ADD BASE RSC /l 0x409 /d "NDEBUG"
# ADD RSC /l 0x409 /d "NDEBUG" /d "_AFXDLL"
RSC_PROJ=/l 0x409 /fo$(INTDIR)/"EasyDIB.res" /d "NDEBUG" /d "_AFXDLL" 
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
BSC32_FLAGS=/nologo /o$(OUTDIR)/"EasyDIB.bsc" 
BSC32_SBRS= \
	$(INTDIR)/"stdafx.sbr" \
	$(INTDIR)/"EasyDIB.sbr" \
	$(INTDIR)/"mainfrm.sbr" \
	$(INTDIR)/"EasyDdoc.sbr" \
	$(INTDIR)/"SceneVw.sbr" \
	$(INTDIR)/"Scene.sbr"

$(OUTDIR)/"EasyDIB.bsc" : $(OUTDIR)  $(BSC32_SBRS)
    $(BSC32) @<<
  $(BSC32_FLAGS) $(BSC32_SBRS)
<<

LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib /NOLOGO /SUBSYSTEM:windows /MACHINE:MIPS
# ADD LINK32 opengl32.lib glu32.lib glaux.lib GLlib.lib /NOLOGO /SUBSYSTEM:windows /MACHINE:MIPS
LINK32_FLAGS=opengl32.lib glu32.lib glaux.lib GLlib.lib /NOLOGO\
 /SUBSYSTEM:windows /PDB:$(OUTDIR)/"EasyDIB.pdb" /MACHINE:MIPS\
 /OUT:$(OUTDIR)/"EasyDIB.exe" 
DEF_FILE=
LINK32_OBJS= \
	$(INTDIR)/"stdafx.obj" \
	$(INTDIR)/"EasyDIB.obj" \
	$(INTDIR)/"mainfrm.obj" \
	$(INTDIR)/"EasyDdoc.obj" \
	$(INTDIR)/"SceneVw.obj" \
	$(INTDIR)/"EasyDIB.res" \
	$(INTDIR)/"Scene.obj"

$(OUTDIR)/"EasyDIB.exe" : $(OUTDIR)  $(DEF_FILE) $(LINK32_OBJS)
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
# PROP Intermediate_Dir "MIPs-d"
OUTDIR=.\MIPS-d
INTDIR=.\MIPs-d

ALL : $(OUTDIR)/"EasyDIB.exe" $(OUTDIR)/"EasyDIB.bsc"

$(OUTDIR) : 
    if not exist $(OUTDIR)/nul mkdir $(OUTDIR)

MTL=MkTypLib.exe
# ADD BASE MTL /nologo /D "_DEBUG" /mips
# ADD MTL /nologo /D "_DEBUG" /mips
MTL_PROJ=/nologo /D "_DEBUG" /mips 
CPP=cl.exe
# ADD BASE CPP /nologo /Gt0 /QMOb2000 /W3 /GX /Zi /YX /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /FR /c
# ADD CPP /nologo /MD /Gt0 /QMOb2000 /W3 /GX /Zi /YX /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /FR /c
CPP_PROJ=/nologo /MD /Gt0 /QMOb2000 /W3 /GX /Zi /YX /Od /D "WIN32" /D "_DEBUG"\
 /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /FR$(INTDIR)/ /Fp$(OUTDIR)/"EasyDIB.pch"\
 /Fo$(INTDIR)/ /Fd$(OUTDIR)/"EasyDIB.pdb" /c 
CPP_OBJS=".\MIPs-d/"

.c{$(CPP_OBJS)}.obj:
   $(CPP) $(CPP_PROJ) $<  

.cpp{$(CPP_OBJS)}.obj:
   $(CPP) $(CPP_PROJ) $<  

.cxx{$(CPP_OBJS)}.obj:
   $(CPP) $(CPP_PROJ) $<  

RSC=rc.exe
# ADD BASE RSC /l 0x409 /d "_DEBUG"
# ADD RSC /l 0x409 /d "_DEBUG" /d "_AFXDLL"
RSC_PROJ=/l 0x409 /fo$(INTDIR)/"EasyDIB.res" /d "_DEBUG" /d "_AFXDLL" 
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
BSC32_FLAGS=/nologo /o$(OUTDIR)/"EasyDIB.bsc" 
BSC32_SBRS= \
	$(INTDIR)/"stdafx.sbr" \
	$(INTDIR)/"EasyDIB.sbr" \
	$(INTDIR)/"mainfrm.sbr" \
	$(INTDIR)/"EasyDdoc.sbr" \
	$(INTDIR)/"SceneVw.sbr" \
	$(INTDIR)/"Scene.sbr"

$(OUTDIR)/"EasyDIB.bsc" : $(OUTDIR)  $(BSC32_SBRS)
    $(BSC32) @<<
  $(BSC32_FLAGS) $(BSC32_SBRS)
<<

LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib /NOLOGO /SUBSYSTEM:windows /DEBUG /MACHINE:MIPS
# ADD LINK32 opengl32.lib glu32.lib glaux.lib GLlib-d.lib /NOLOGO /SUBSYSTEM:windows /DEBUG /MACHINE:MIPS
LINK32_FLAGS=opengl32.lib glu32.lib glaux.lib GLlib-d.lib /NOLOGO\
 /SUBSYSTEM:windows /PDB:$(OUTDIR)/"EasyDIB.pdb" /DEBUG /MACHINE:MIPS\
 /OUT:$(OUTDIR)/"EasyDIB.exe" 
DEF_FILE=
LINK32_OBJS= \
	$(INTDIR)/"stdafx.obj" \
	$(INTDIR)/"EasyDIB.obj" \
	$(INTDIR)/"mainfrm.obj" \
	$(INTDIR)/"EasyDdoc.obj" \
	$(INTDIR)/"SceneVw.obj" \
	$(INTDIR)/"EasyDIB.res" \
	$(INTDIR)/"Scene.obj"

$(OUTDIR)/"EasyDIB.exe" : $(OUTDIR)  $(DEF_FILE) $(LINK32_OBJS)
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
 "_MBCS" /D "_AFXDLL" /FR$(INTDIR)/ /Fp$(OUTDIR)/"EasyDIB.pch" /Yc"stdafx.h"\
 /Fo$(INTDIR)/ /Fd$(OUTDIR)/"EasyDIB.pdb" /c  $(SOURCE) 

!ELSEIF  "$(CFG)" == "Win32 Release"

# ADD BASE CPP /Yc"stdafx.h"
# ADD CPP /Yc"stdafx.h"

$(INTDIR)/"stdafx.obj" :  $(SOURCE)  $(DEP_STDAF) $(INTDIR)
   $(CPP) /nologo /MD /W3 /GX /O2 /D "NDEBUG" /D "WIN32" /D "_WINDOWS" /D\
 "_MBCS" /D "_AFXDLL" /FR$(INTDIR)/ /Fp$(OUTDIR)/"EasyDIB.pch" /Yc"stdafx.h"\
 /Fo$(INTDIR)/ /c  $(SOURCE) 

!ELSEIF  "$(CFG)" == "Alpha Release"

".\Alpha-r\stdafx.obj" :  $(SOURCE)  $(DEP_STDAF) $(INTDIR)

!ELSEIF  "$(CFG)" == "Alpha Debug"

".\Alpha-d\stdafx.obj" :  $(SOURCE)  $(DEP_STDAF) $(INTDIR)

!ELSEIF  "$(CFG)" == "MIPs Release"

$(INTDIR)/"stdafx.obj" :  $(SOURCE)  $(DEP_STDAF) $(INTDIR)

!ELSEIF  "$(CFG)" == "MIPs Debug"

$(INTDIR)/"stdafx.obj" :  $(SOURCE)  $(DEP_STDAF) $(INTDIR)

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\EasyDIB.cpp
DEP_EASYD=\
	.\mainfrm.h\
	.\EasyDdoc.h\
	.\SceneVw.h\
	.\EasyDIB.h

!IF  "$(CFG)" == "Win32 Debug"

$(INTDIR)/"EasyDIB.obj" :  $(SOURCE)  $(DEP_EASYD) $(INTDIR)\
 $(INTDIR)/stdafx.obj

!ELSEIF  "$(CFG)" == "Win32 Release"

$(INTDIR)/"EasyDIB.obj" :  $(SOURCE)  $(DEP_EASYD) $(INTDIR)\
 $(INTDIR)/stdafx.obj

!ELSEIF  "$(CFG)" == "Alpha Release"

".\Alpha-r\EasyDIB.obj" :  $(SOURCE)  $(DEP_EASYD) $(INTDIR)

!ELSEIF  "$(CFG)" == "Alpha Debug"

".\Alpha-d\EasyDIB.obj" :  $(SOURCE)  $(DEP_EASYD) $(INTDIR)

!ELSEIF  "$(CFG)" == "MIPs Release"

$(INTDIR)/"EasyDIB.obj" :  $(SOURCE)  $(DEP_EASYD) $(INTDIR)

!ELSEIF  "$(CFG)" == "MIPs Debug"

$(INTDIR)/"EasyDIB.obj" :  $(SOURCE)  $(DEP_EASYD) $(INTDIR)

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\mainfrm.cpp
DEP_MAINF=\
	.\EasyDIB.h\
	.\mainfrm.h

!IF  "$(CFG)" == "Win32 Debug"

$(INTDIR)/"mainfrm.obj" :  $(SOURCE)  $(DEP_MAINF) $(INTDIR)\
 $(INTDIR)/stdafx.obj

!ELSEIF  "$(CFG)" == "Win32 Release"

$(INTDIR)/"mainfrm.obj" :  $(SOURCE)  $(DEP_MAINF) $(INTDIR)\
 $(INTDIR)/stdafx.obj

!ELSEIF  "$(CFG)" == "Alpha Release"

".\Alpha-r\mainfrm.obj" :  $(SOURCE)  $(DEP_MAINF) $(INTDIR)

!ELSEIF  "$(CFG)" == "Alpha Debug"

".\Alpha-d\mainfrm.obj" :  $(SOURCE)  $(DEP_MAINF) $(INTDIR)

!ELSEIF  "$(CFG)" == "MIPs Release"

$(INTDIR)/"mainfrm.obj" :  $(SOURCE)  $(DEP_MAINF) $(INTDIR)

!ELSEIF  "$(CFG)" == "MIPs Debug"

$(INTDIR)/"mainfrm.obj" :  $(SOURCE)  $(DEP_MAINF) $(INTDIR)

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\EasyDdoc.cpp
DEP_EASYDD=\
	.\EasyDIB.h\
	.\EasyDdoc.h

!IF  "$(CFG)" == "Win32 Debug"

$(INTDIR)/"EasyDdoc.obj" :  $(SOURCE)  $(DEP_EASYDD) $(INTDIR)\
 $(INTDIR)/stdafx.obj

!ELSEIF  "$(CFG)" == "Win32 Release"

$(INTDIR)/"EasyDdoc.obj" :  $(SOURCE)  $(DEP_EASYDD) $(INTDIR)\
 $(INTDIR)/stdafx.obj

!ELSEIF  "$(CFG)" == "Alpha Release"

".\Alpha-r\EasyDdoc.obj" :  $(SOURCE)  $(DEP_EASYDD) $(INTDIR)

!ELSEIF  "$(CFG)" == "Alpha Debug"

".\Alpha-d\EasyDdoc.obj" :  $(SOURCE)  $(DEP_EASYDD) $(INTDIR)

!ELSEIF  "$(CFG)" == "MIPs Release"

$(INTDIR)/"EasyDdoc.obj" :  $(SOURCE)  $(DEP_EASYDD) $(INTDIR)

!ELSEIF  "$(CFG)" == "MIPs Debug"

$(INTDIR)/"EasyDdoc.obj" :  $(SOURCE)  $(DEP_EASYDD) $(INTDIR)

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\SceneVw.cpp
DEP_SCENE=\
	.\EasyDIB.h\
	.\EasyDdoc.h\
	.\SceneVw.h

!IF  "$(CFG)" == "Win32 Debug"

$(INTDIR)/"SceneVw.obj" :  $(SOURCE)  $(DEP_SCENE) $(INTDIR)\
 $(INTDIR)/stdafx.obj

!ELSEIF  "$(CFG)" == "Win32 Release"

$(INTDIR)/"SceneVw.obj" :  $(SOURCE)  $(DEP_SCENE) $(INTDIR)\
 $(INTDIR)/stdafx.obj

!ELSEIF  "$(CFG)" == "Alpha Release"

".\Alpha-r\SceneVw.obj" :  $(SOURCE)  $(DEP_SCENE) $(INTDIR)

!ELSEIF  "$(CFG)" == "Alpha Debug"

".\Alpha-d\SceneVw.obj" :  $(SOURCE)  $(DEP_SCENE) $(INTDIR)

!ELSEIF  "$(CFG)" == "MIPs Release"

$(INTDIR)/"SceneVw.obj" :  $(SOURCE)  $(DEP_SCENE) $(INTDIR)

!ELSEIF  "$(CFG)" == "MIPs Debug"

$(INTDIR)/"SceneVw.obj" :  $(SOURCE)  $(DEP_SCENE) $(INTDIR)

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\EasyDIB.rc
DEP_EASYDI=\
	.\res\EasyDIB.ico\
	.\res\toolbar.bmp\
	.\res\EasyDIB.rc2

!IF  "$(CFG)" == "Win32 Debug"

$(INTDIR)/"EasyDIB.res" :  $(SOURCE)  $(DEP_EASYDI) $(INTDIR)
   $(RSC) $(RSC_PROJ)  $(SOURCE) 

!ELSEIF  "$(CFG)" == "Win32 Release"

$(INTDIR)/"EasyDIB.res" :  $(SOURCE)  $(DEP_EASYDI) $(INTDIR)
   $(RSC) $(RSC_PROJ)  $(SOURCE) 

!ELSEIF  "$(CFG)" == "Alpha Release"

".\Alpha-r\EasyDIB.res" :  $(SOURCE)  $(DEP_EASYDI) $(INTDIR)
   $(RSC) $(RSC_PROJ)  $(SOURCE) 

!ELSEIF  "$(CFG)" == "Alpha Debug"

".\Alpha-d\EasyDIB.res" :  $(SOURCE)  $(DEP_EASYDI) $(INTDIR)
   $(RSC) $(RSC_PROJ)  $(SOURCE) 

!ELSEIF  "$(CFG)" == "MIPs Release"

$(INTDIR)/"EasyDIB.res" :  $(SOURCE)  $(DEP_EASYDI) $(INTDIR)
   $(RSC) $(RSC_PROJ)  $(SOURCE) 

!ELSEIF  "$(CFG)" == "MIPs Debug"

$(INTDIR)/"EasyDIB.res" :  $(SOURCE)  $(DEP_EASYDI) $(INTDIR)
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
DEP_SCENE_=\
	.\stdafx.h\
	..\GLlib\GLlib.h\
	.\Scene.h\
	\articles\samples\OpenGL\GLlib\cgl.h\
	\articles\samples\OpenGL\GLlib\glview.h\
	\articles\samples\OpenGL\GLlib\image.h\
	..\animate\include\animate.h

!IF  "$(CFG)" == "Win32 Debug"

$(INTDIR)/"Scene.obj" :  $(SOURCE)  $(DEP_SCENE_) $(INTDIR)\
 $(INTDIR)/stdafx.obj

!ELSEIF  "$(CFG)" == "Win32 Release"

$(INTDIR)/"Scene.obj" :  $(SOURCE)  $(DEP_SCENE_) $(INTDIR)\
 $(INTDIR)/stdafx.obj

!ELSEIF  "$(CFG)" == "Alpha Release"

".\Alpha-r\Scene.obj" :  $(SOURCE)  $(DEP_SCENE_) $(INTDIR)

!ELSEIF  "$(CFG)" == "Alpha Debug"

".\Alpha-d\Scene.obj" :  $(SOURCE)  $(DEP_SCENE_) $(INTDIR)

!ELSEIF  "$(CFG)" == "MIPs Release"

$(INTDIR)/"Scene.obj" :  $(SOURCE)  $(DEP_SCENE_) $(INTDIR)

!ELSEIF  "$(CFG)" == "MIPs Debug"

$(INTDIR)/"Scene.obj" :  $(SOURCE)  $(DEP_SCENE_) $(INTDIR)

!ENDIF 

# End Source File
# End Group
# End Project
################################################################################
