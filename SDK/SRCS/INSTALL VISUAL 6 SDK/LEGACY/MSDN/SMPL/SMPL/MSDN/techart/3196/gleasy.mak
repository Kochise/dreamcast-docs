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
!MESSAGE NMAKE /f "gleasy.mak" CFG="Win32 Debug"
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
# PROP Target_Last_Scanned "MIPs Debug"

!IF  "$(CFG)" == "Win32 Debug"

# PROP BASE Use_MFC 5
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "WinDebug"
# PROP BASE Intermediate_Dir "WinDebug"
# PROP Use_MFC 5
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "x86-d"
# PROP Intermediate_Dir "x86-d"
OUTDIR=.\x86-d
INTDIR=.\x86-d

ALL : ".\x86-d\"gleasy.exe"" ".\x86-d\"gleasy.bsc""

$(OUTDIR) : 
    if not exist $(OUTDIR)/nul mkdir $(OUTDIR)

MTL=MkTypLib.exe
MTL_PROJ=
CPP=cl.exe
# ADD BASE CPP /nologo /MT /W3 /GX /Zi /Od /D "_DEBUG" /D "WIN32" /D "_WINDOWS" /D "_MBCS" /FR /Yu"stdafx.h" /c
# ADD CPP /nologo /MT /W3 /GX /Zi /Od /D "_DEBUG" /D "WIN32" /D "_WINDOWS" /D "_MBCS" /FR /Yu"stdafx.h" /c
CPP_PROJ=/nologo /MT /W3 /GX /Zi /Od /D "_DEBUG" /D "WIN32" /D "_WINDOWS" /D\
 "_MBCS" /FR$(INTDIR)/ /Fp$(OUTDIR)/"gleasy.pch" /Yu"stdafx.h" /Fo$(INTDIR)/\
 /Fd$(OUTDIR)/"gleasy.pdb" /c 
CPP_OBJS=".\x86-d/"

.c{$(CPP_OBJS)}.obj:
   $(CPP) $(CPP_PROJ) $<  

.cpp{$(CPP_OBJS)}.obj:
   $(CPP) $(CPP_PROJ) $<  

.cxx{$(CPP_OBJS)}.obj:
   $(CPP) $(CPP_PROJ) $<  

RSC=rc.exe
# ADD BASE RSC /l 0x409 /d "_DEBUG"
# ADD RSC /l 0x409 /d "_DEBUG"
RSC_PROJ=/l 0x409 /fo$(INTDIR)/"gleasy.res" /d "_DEBUG" 
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
BSC32_FLAGS=/nologo /o$(OUTDIR)/"gleasy.bsc" 
BSC32_SBRS= \
	$(INTDIR)/"stdafx.sbr" \
	$(INTDIR)/"gleasy.sbr" \
	$(INTDIR)/"mainfrm.sbr" \
	$(INTDIR)/"gleasdoc.sbr" \
	$(INTDIR)/"gleasvw.sbr"

$(OUTDIR)/"gleasy.bsc" : $(OUTDIR)  $(BSC32_SBRS)
    $(BSC32) @<<
  $(BSC32_FLAGS) $(BSC32_SBRS)
<<

LINK32=link.exe
# ADD BASE LINK32 /NOLOGO /SUBSYSTEM:windows /DEBUG /MACHINE:I386
# SUBTRACT BASE LINK32 /PDB:none
# ADD LINK32 opengl32.lib glu32.lib glaux.lib winmm.lib /NOLOGO /SUBSYSTEM:windows /DEBUG /MACHINE:I386
# SUBTRACT LINK32 /PDB:none
LINK32_FLAGS=opengl32.lib glu32.lib glaux.lib winmm.lib /NOLOGO\
 /SUBSYSTEM:windows /INCREMENTAL:yes /PDB:$(OUTDIR)/"gleasy.pdb" /DEBUG\
 /MACHINE:I386 /OUT:$(OUTDIR)/"gleasy.exe" 
DEF_FILE=
LINK32_OBJS= \
	$(INTDIR)/"stdafx.obj" \
	$(INTDIR)/"gleasy.obj" \
	$(INTDIR)/"mainfrm.obj" \
	$(INTDIR)/"gleasdoc.obj" \
	$(INTDIR)/"gleasvw.obj" \
	$(INTDIR)/"gleasy.res"

$(OUTDIR)/"gleasy.exe" : $(OUTDIR)  $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ELSEIF  "$(CFG)" == "Win32 Release"

# PROP BASE Use_MFC 5
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "WinRel"
# PROP BASE Intermediate_Dir "WinRel"
# PROP Use_MFC 5
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "x86-r"
# PROP Intermediate_Dir "x86-r"
OUTDIR=.\x86-r
INTDIR=.\x86-r

ALL : ".\x86-r\"gleasy.exe"" ".\x86-r\"gleasy.bsc""

$(OUTDIR) : 
    if not exist $(OUTDIR)/nul mkdir $(OUTDIR)

MTL=MkTypLib.exe
MTL_PROJ=
CPP=cl.exe
# ADD BASE CPP /nologo /MT /W3 /GX /O2 /D "NDEBUG" /D "WIN32" /D "_WINDOWS" /D "_MBCS" /FR /Yu"stdafx.h" /c
# ADD CPP /nologo /MT /W3 /GX /O2 /D "NDEBUG" /D "WIN32" /D "_WINDOWS" /D "_MBCS" /FR /Yu"stdafx.h" /c
CPP_PROJ=/nologo /MT /W3 /GX /O2 /D "NDEBUG" /D "WIN32" /D "_WINDOWS" /D\
 "_MBCS" /FR$(INTDIR)/ /Fp$(OUTDIR)/"gleasy.pch" /Yu"stdafx.h" /Fo$(INTDIR)/ /c 
CPP_OBJS=".\x86-r/"

.c{$(CPP_OBJS)}.obj:
   $(CPP) $(CPP_PROJ) $<  

.cpp{$(CPP_OBJS)}.obj:
   $(CPP) $(CPP_PROJ) $<  

.cxx{$(CPP_OBJS)}.obj:
   $(CPP) $(CPP_PROJ) $<  

RSC=rc.exe
# ADD BASE RSC /l 0x409 /d "NDEBUG"
# ADD RSC /l 0x409 /d "NDEBUG"
RSC_PROJ=/l 0x409 /fo$(INTDIR)/"gleasy.res" /d "NDEBUG" 
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
BSC32_FLAGS=/nologo /o$(OUTDIR)/"gleasy.bsc" 
BSC32_SBRS= \
	$(INTDIR)/"stdafx.sbr" \
	$(INTDIR)/"gleasy.sbr" \
	$(INTDIR)/"mainfrm.sbr" \
	$(INTDIR)/"gleasdoc.sbr" \
	$(INTDIR)/"gleasvw.sbr"

$(OUTDIR)/"gleasy.bsc" : $(OUTDIR)  $(BSC32_SBRS)
    $(BSC32) @<<
  $(BSC32_FLAGS) $(BSC32_SBRS)
<<

LINK32=link.exe
# ADD BASE LINK32 /NOLOGO /SUBSYSTEM:windows /MACHINE:I386
# SUBTRACT BASE LINK32 /PDB:none
# ADD LINK32 opengl32.lib glu32.lib glaux.lib winmm.lib /NOLOGO /SUBSYSTEM:windows /MACHINE:I386
# SUBTRACT LINK32 /PDB:none
LINK32_FLAGS=opengl32.lib glu32.lib glaux.lib winmm.lib /NOLOGO\
 /SUBSYSTEM:windows /INCREMENTAL:no /PDB:$(OUTDIR)/"gleasy.pdb" /MACHINE:I386\
 /OUT:$(OUTDIR)/"gleasy.exe" 
DEF_FILE=
LINK32_OBJS= \
	$(INTDIR)/"stdafx.obj" \
	$(INTDIR)/"gleasy.obj" \
	$(INTDIR)/"mainfrm.obj" \
	$(INTDIR)/"gleasdoc.obj" \
	$(INTDIR)/"gleasvw.obj" \
	$(INTDIR)/"gleasy.res"

$(OUTDIR)/"gleasy.exe" : $(OUTDIR)  $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ELSEIF  "$(CFG)" == "MIPs Release"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "MIPs_Rel"
# PROP BASE Intermediate_Dir "MIPs_Rel"
# PROP Use_MFC 1
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "MIPS-r"
# PROP Intermediate_Dir "MIPS-r"
OUTDIR=.\MIPS-r
INTDIR=.\MIPS-r

ALL : ".\MIPS-r\"gleasy.exe"" ".\MIPS-r\"gleasy.bsc""

$(OUTDIR) : 
    if not exist $(OUTDIR)/nul mkdir $(OUTDIR)

MTL=MkTypLib.exe
# ADD BASE MTL /nologo /D "NDEBUG" /mips
# ADD MTL /nologo /D "NDEBUG" /mips
MTL_PROJ=/nologo /D "NDEBUG" /mips 
CPP=cl.exe
# ADD BASE CPP /nologo /ML /Gt0 /QMOb2000 /W3 /GX /YX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /FR /c
# ADD CPP /nologo /MT /Gt0 /QMOb2000 /W3 /GX /YX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /FR /c
CPP_PROJ=/nologo /MT /Gt0 /QMOb2000 /W3 /GX /YX /O2 /D "WIN32" /D "NDEBUG" /D\
 "_WINDOWS" /D "_MBCS" /FR$(INTDIR)/ /Fp$(OUTDIR)/"gleasy.pch" /Fo$(INTDIR)/ /c 
CPP_OBJS=".\MIPS-r/"

.c{$(CPP_OBJS)}.obj:
   $(CPP) $(CPP_PROJ) $<  

.cpp{$(CPP_OBJS)}.obj:
   $(CPP) $(CPP_PROJ) $<  

.cxx{$(CPP_OBJS)}.obj:
   $(CPP) $(CPP_PROJ) $<  

RSC=rc.exe
# ADD BASE RSC /l 0x409 /d "NDEBUG"
# ADD RSC /l 0x409 /d "NDEBUG"
RSC_PROJ=/l 0x409 /fo$(INTDIR)/"gleasy.res" /d "NDEBUG" 
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
BSC32_FLAGS=/nologo /o$(OUTDIR)/"gleasy.bsc" 
BSC32_SBRS= \
	".\MIPS-r\stdafx.sbr" \
	".\MIPS-r\gleasy.sbr" \
	".\MIPS-r\mainfrm.sbr" \
	".\MIPS-r\gleasdoc.sbr" \
	".\MIPS-r\gleasvw.sbr"

".\MIPS-r\gleasy.bsc" : $(OUTDIR)  $(BSC32_SBRS)
    $(BSC32) @<<
  $(BSC32_FLAGS) $(BSC32_SBRS)
<<

LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib /NOLOGO /SUBSYSTEM:windows /MACHINE:MIPS
# ADD LINK32 opengl32.lib glu32.lib glaux.lib /NOLOGO /SUBSYSTEM:windows /MACHINE:MIPS
LINK32_FLAGS=opengl32.lib glu32.lib glaux.lib /NOLOGO /SUBSYSTEM:windows\
 /PDB:$(OUTDIR)/"gleasy.pdb" /MACHINE:MIPS /OUT:$(OUTDIR)/"gleasy.exe" 
DEF_FILE=
LINK32_OBJS= \
	".\MIPS-r\stdafx.obj" \
	".\MIPS-r\gleasy.obj" \
	".\MIPS-r\mainfrm.obj" \
	".\MIPS-r\gleasdoc.obj" \
	".\MIPS-r\gleasvw.obj" \
	".\MIPS-r\gleasy.res"

".\MIPs-r\gleasy.exe" : $(OUTDIR)  $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ELSEIF  "$(CFG)" == "MIPs Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "MIPs_Deb"
# PROP BASE Intermediate_Dir "MIPs_Deb"
# PROP Use_MFC 1
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "MIPS-d"
# PROP Intermediate_Dir "MIPS-d"
OUTDIR=.\MIPS-d
INTDIR=.\MIPS-d

ALL : ".\MIPS-d\"gleasy.exe"" ".\MIPS-d\"gleasy.bsc""

$(OUTDIR) : 
    if not exist $(OUTDIR)/nul mkdir $(OUTDIR)

MTL=MkTypLib.exe
# ADD BASE MTL /nologo /D "_DEBUG" /mips
# ADD MTL /nologo /D "_DEBUG" /mips
MTL_PROJ=/nologo /D "_DEBUG" /mips 
CPP=cl.exe
# ADD BASE CPP /nologo /ML /Gt0 /QMOb2000 /W3 /GX /Zi /YX /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /FR /c
# ADD CPP /nologo /MT /Gt0 /QMOb2000 /W3 /GX /Zi /YX /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /FR /c
CPP_PROJ=/nologo /MT /Gt0 /QMOb2000 /W3 /GX /Zi /YX /Od /D "WIN32" /D "_DEBUG"\
 /D "_WINDOWS" /D "_MBCS" /FR$(INTDIR)/ /Fp$(OUTDIR)/"gleasy.pch" /Fo$(INTDIR)/\
 /Fd$(OUTDIR)/"gleasy.pdb" /c 
CPP_OBJS=".\MIPS-d/"

.c{$(CPP_OBJS)}.obj:
   $(CPP) $(CPP_PROJ) $<  

.cpp{$(CPP_OBJS)}.obj:
   $(CPP) $(CPP_PROJ) $<  

.cxx{$(CPP_OBJS)}.obj:
   $(CPP) $(CPP_PROJ) $<  

RSC=rc.exe
# ADD BASE RSC /l 0x409 /d "_DEBUG"
# ADD RSC /l 0x409 /d "_DEBUG"
RSC_PROJ=/l 0x409 /fo$(INTDIR)/"gleasy.res" /d "_DEBUG" 
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
BSC32_FLAGS=/nologo /o$(OUTDIR)/"gleasy.bsc" 
BSC32_SBRS= \
	".\MIPS-d\stdafx.sbr" \
	".\MIPS-d\gleasy.sbr" \
	".\MIPS-d\mainfrm.sbr" \
	".\MIPS-d\gleasdoc.sbr" \
	".\MIPS-d\gleasvw.sbr"

".\MIPS-d\gleasy.bsc" : $(OUTDIR)  $(BSC32_SBRS)
    $(BSC32) @<<
  $(BSC32_FLAGS) $(BSC32_SBRS)
<<

LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib /NOLOGO /SUBSYSTEM:windows /DEBUG /MACHINE:MIPS
# ADD LINK32 opengl32.lib glu32.lib glaux.lib /NOLOGO /SUBSYSTEM:windows /DEBUG /MACHINE:MIPS
LINK32_FLAGS=opengl32.lib glu32.lib glaux.lib /NOLOGO /SUBSYSTEM:windows\
 /PDB:$(OUTDIR)/"gleasy.pdb" /DEBUG /MACHINE:MIPS /OUT:$(OUTDIR)/"gleasy.exe" 
DEF_FILE=
LINK32_OBJS= \
	".\MIPS-d\stdafx.obj" \
	".\MIPS-d\gleasy.obj" \
	".\MIPS-d\mainfrm.obj" \
	".\MIPS-d\gleasdoc.obj" \
	".\MIPS-d\gleasvw.obj" \
	".\MIPS-d\gleasy.res"

".\MIPS-d\gleasy.exe" : $(OUTDIR)  $(DEF_FILE) $(LINK32_OBJS)
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

ALL : ".\Alpha-r\gleasy.exe" ".\Alpha-r\gleasy.bsc"

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
 /D "_AFXDLL" /D "_MBCS" /FR$(INTDIR)/ /Fp$(OUTDIR)/"gleasy.pch" /Fo$(INTDIR)/\
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
RSC_PROJ=/l 0x409 /fo$(INTDIR)/"gleasy.res" /d "NDEBUG" /d "_AFXDLL" 
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
BSC32_FLAGS=/nologo /o$(OUTDIR)/"gleasy.bsc" 
BSC32_SBRS= \
	".\Alpha-r\stdafx.sbr" \
	".\Alpha-r\gleasy.sbr" \
	".\Alpha-r\mainfrm.sbr" \
	".\Alpha-r\gleasdoc.sbr" \
	".\Alpha-r\gleasvw.sbr"

".\Alpha-r\gleasy.bsc" : $(OUTDIR)  $(BSC32_SBRS)
    $(BSC32) @<<
  $(BSC32_FLAGS) $(BSC32_SBRS)
<<

LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib /NOLOGO /SUBSYSTEM:windows /MACHINE:ALPHA
# ADD LINK32 opengl32.lib glu32.lib glaux.lib /NOLOGO /SUBSYSTEM:windows /MACHINE:ALPHA
LINK32_FLAGS=opengl32.lib glu32.lib glaux.lib /NOLOGO /SUBSYSTEM:windows\
 /PDB:$(OUTDIR)/"gleasy.pdb" /MACHINE:ALPHA /OUT:$(OUTDIR)/"gleasy.exe" 
DEF_FILE=
LINK32_OBJS= \
	".\Alpha-r\stdafx.obj" \
	".\Alpha-r\gleasy.obj" \
	".\Alpha-r\mainfrm.obj" \
	".\Alpha-r\gleasdoc.obj" \
	".\Alpha-r\gleasvw.obj" \
	".\Alpha-r\gleasy.res"

".\Alpha-r\gleasy.exe" : $(OUTDIR)  $(DEF_FILE) $(LINK32_OBJS)
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

ALL : ".\Alpha-d\gleasy.exe" ".\Alpha-d\gleasy.bsc"

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
 "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /FR$(INTDIR)/ /Fp$(OUTDIR)/"gleasy.pch"\
 /Fo$(INTDIR)/ /Fd$(OUTDIR)/"gleasy.pdb" /c 
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
RSC_PROJ=/l 0x409 /fo$(INTDIR)/"gleasy.res" /d "_DEBUG" /d "_AFXDLL" 
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
BSC32_FLAGS=/nologo /o$(OUTDIR)/"gleasy.bsc" 
BSC32_SBRS= \
	".\Alpha-d\stdafx.sbr" \
	".\Alpha-d\gleasy.sbr" \
	".\Alpha-d\mainfrm.sbr" \
	".\Alpha-d\gleasdoc.sbr" \
	".\Alpha-d\gleasvw.sbr"

".\Alpha-d\gleasy.bsc" : $(OUTDIR)  $(BSC32_SBRS)
    $(BSC32) @<<
  $(BSC32_FLAGS) $(BSC32_SBRS)
<<

LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib /NOLOGO /SUBSYSTEM:windows /DEBUG /MACHINE:ALPHA
# ADD LINK32 opengl32.lib glu32.lib glaux.lib /NOLOGO /SUBSYSTEM:windows /DEBUG /MACHINE:ALPHA
LINK32_FLAGS=opengl32.lib glu32.lib glaux.lib /NOLOGO /SUBSYSTEM:windows\
 /PDB:$(OUTDIR)/"gleasy.pdb" /DEBUG /MACHINE:ALPHA /OUT:$(OUTDIR)/"gleasy.exe" 
DEF_FILE=
LINK32_OBJS= \
	".\Alpha-d\stdafx.obj" \
	".\Alpha-d\gleasy.obj" \
	".\Alpha-d\mainfrm.obj" \
	".\Alpha-d\gleasdoc.obj" \
	".\Alpha-d\gleasvw.obj" \
	".\Alpha-d\gleasy.res"

".\Alpha-d\gleasy.exe" : $(OUTDIR)  $(DEF_FILE) $(LINK32_OBJS)
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
	.\stdafx.h\
	D:\MSVC20\INCLUDE\GL\GL.H\
	D:\MSVC20\INCLUDE\GL\GLU.H\
	D:\MSVC20\INCLUDE\GL\GLAUX.H

!IF  "$(CFG)" == "Win32 Debug"

# ADD BASE CPP /Yc"stdafx.h"
# ADD CPP /Yc"stdafx.h"

$(INTDIR)/"stdafx.obj" :  $(SOURCE)  $(DEP_STDAF) $(INTDIR)
   $(CPP) /nologo /MT /W3 /GX /Zi /Od /D "_DEBUG" /D "WIN32" /D "_WINDOWS" /D\
 "_MBCS" /FR$(INTDIR)/ /Fp$(OUTDIR)/"gleasy.pch" /Yc"stdafx.h" /Fo$(INTDIR)/\
 /Fd$(OUTDIR)/"gleasy.pdb" /c  $(SOURCE) 

!ELSEIF  "$(CFG)" == "Win32 Release"

# ADD BASE CPP /Yc"stdafx.h"
# ADD CPP /Yc"stdafx.h"

$(INTDIR)/"stdafx.obj" :  $(SOURCE)  $(DEP_STDAF) $(INTDIR)
   $(CPP) /nologo /MT /W3 /GX /O2 /D "NDEBUG" /D "WIN32" /D "_WINDOWS" /D\
 "_MBCS" /FR$(INTDIR)/ /Fp$(OUTDIR)/"gleasy.pch" /Yc"stdafx.h" /Fo$(INTDIR)/ /c\
  $(SOURCE) 

!ELSEIF  "$(CFG)" == "MIPs Release"

".\MIPS-r\stdafx.obj" :  $(SOURCE)  $(DEP_STDAF) $(INTDIR)

!ELSEIF  "$(CFG)" == "MIPs Debug"

".\MIPS-d\stdafx.obj" :  $(SOURCE)  $(DEP_STDAF) $(INTDIR)

!ELSEIF  "$(CFG)" == "Alpha Release"

".\Alpha-r\stdafx.obj" :  $(SOURCE)  $(DEP_STDAF) $(INTDIR)

!ELSEIF  "$(CFG)" == "Alpha Debug"

".\Alpha-d\stdafx.obj" :  $(SOURCE)  $(DEP_STDAF) $(INTDIR)

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\gleasy.cpp
DEP_GLEAS=\
	.\stdafx.h\
	.\gleasy.h\
	.\mainfrm.h\
	.\gleasdoc.h\
	.\gleasvw.h\
	D:\MSVC20\INCLUDE\GL\GL.H\
	D:\MSVC20\INCLUDE\GL\GLU.H\
	D:\MSVC20\INCLUDE\GL\GLAUX.H

!IF  "$(CFG)" == "Win32 Debug"

$(INTDIR)/"gleasy.obj" :  $(SOURCE)  $(DEP_GLEAS) $(INTDIR)\
 $(INTDIR)/stdafx.obj

!ELSEIF  "$(CFG)" == "Win32 Release"

$(INTDIR)/"gleasy.obj" :  $(SOURCE)  $(DEP_GLEAS) $(INTDIR)\
 $(INTDIR)/stdafx.obj

!ELSEIF  "$(CFG)" == "MIPs Release"

".\MIPS-r\gleasy.obj" :  $(SOURCE)  $(DEP_GLEAS) $(INTDIR)

!ELSEIF  "$(CFG)" == "MIPs Debug"

".\MIPS-d\gleasy.obj" :  $(SOURCE)  $(DEP_GLEAS) $(INTDIR)

!ELSEIF  "$(CFG)" == "Alpha Release"

".\Alpha-r\gleasy.obj" :  $(SOURCE)  $(DEP_GLEAS) $(INTDIR)

!ELSEIF  "$(CFG)" == "Alpha Debug"

".\Alpha-d\gleasy.obj" :  $(SOURCE)  $(DEP_GLEAS) $(INTDIR)

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\mainfrm.cpp
DEP_MAINF=\
	.\stdafx.h\
	.\gleasy.h\
	.\mainfrm.h\
	D:\MSVC20\INCLUDE\GL\GL.H\
	D:\MSVC20\INCLUDE\GL\GLU.H\
	D:\MSVC20\INCLUDE\GL\GLAUX.H

!IF  "$(CFG)" == "Win32 Debug"

$(INTDIR)/"mainfrm.obj" :  $(SOURCE)  $(DEP_MAINF) $(INTDIR)\
 $(INTDIR)/stdafx.obj

!ELSEIF  "$(CFG)" == "Win32 Release"

$(INTDIR)/"mainfrm.obj" :  $(SOURCE)  $(DEP_MAINF) $(INTDIR)\
 $(INTDIR)/stdafx.obj

!ELSEIF  "$(CFG)" == "MIPs Release"

".\MIPS-r\mainfrm.obj" :  $(SOURCE)  $(DEP_MAINF) $(INTDIR)

!ELSEIF  "$(CFG)" == "MIPs Debug"

".\MIPS-d\mainfrm.obj" :  $(SOURCE)  $(DEP_MAINF) $(INTDIR)

!ELSEIF  "$(CFG)" == "Alpha Release"

".\Alpha-r\mainfrm.obj" :  $(SOURCE)  $(DEP_MAINF) $(INTDIR)

!ELSEIF  "$(CFG)" == "Alpha Debug"

".\Alpha-d\mainfrm.obj" :  $(SOURCE)  $(DEP_MAINF) $(INTDIR)

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\gleasdoc.cpp
DEP_GLEASD=\
	.\stdafx.h\
	.\gleasy.h\
	.\gleasdoc.h\
	D:\MSVC20\INCLUDE\GL\GL.H\
	D:\MSVC20\INCLUDE\GL\GLU.H\
	D:\MSVC20\INCLUDE\GL\GLAUX.H

!IF  "$(CFG)" == "Win32 Debug"

$(INTDIR)/"gleasdoc.obj" :  $(SOURCE)  $(DEP_GLEASD) $(INTDIR)\
 $(INTDIR)/stdafx.obj

!ELSEIF  "$(CFG)" == "Win32 Release"

$(INTDIR)/"gleasdoc.obj" :  $(SOURCE)  $(DEP_GLEASD) $(INTDIR)\
 $(INTDIR)/stdafx.obj

!ELSEIF  "$(CFG)" == "MIPs Release"

".\MIPS-r\gleasdoc.obj" :  $(SOURCE)  $(DEP_GLEASD) $(INTDIR)

!ELSEIF  "$(CFG)" == "MIPs Debug"

".\MIPS-d\gleasdoc.obj" :  $(SOURCE)  $(DEP_GLEASD) $(INTDIR)

!ELSEIF  "$(CFG)" == "Alpha Release"

".\Alpha-r\gleasdoc.obj" :  $(SOURCE)  $(DEP_GLEASD) $(INTDIR)

!ELSEIF  "$(CFG)" == "Alpha Debug"

".\Alpha-d\gleasdoc.obj" :  $(SOURCE)  $(DEP_GLEASD) $(INTDIR)

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\gleasvw.cpp
DEP_GLEASV=\
	.\stdafx.h\
	.\gleasy.h\
	.\gleasdoc.h\
	.\gleasvw.h\
	D:\MSVC20\INCLUDE\GL\GL.H\
	D:\MSVC20\INCLUDE\GL\GLU.H\
	D:\MSVC20\INCLUDE\GL\GLAUX.H

!IF  "$(CFG)" == "Win32 Debug"

$(INTDIR)/"gleasvw.obj" :  $(SOURCE)  $(DEP_GLEASV) $(INTDIR)\
 $(INTDIR)/stdafx.obj

!ELSEIF  "$(CFG)" == "Win32 Release"

$(INTDIR)/"gleasvw.obj" :  $(SOURCE)  $(DEP_GLEASV) $(INTDIR)\
 $(INTDIR)/stdafx.obj

!ELSEIF  "$(CFG)" == "MIPs Release"

".\MIPS-r\gleasvw.obj" :  $(SOURCE)  $(DEP_GLEASV) $(INTDIR)

!ELSEIF  "$(CFG)" == "MIPs Debug"

".\MIPS-d\gleasvw.obj" :  $(SOURCE)  $(DEP_GLEASV) $(INTDIR)

!ELSEIF  "$(CFG)" == "Alpha Release"

".\Alpha-r\gleasvw.obj" :  $(SOURCE)  $(DEP_GLEASV) $(INTDIR)

!ELSEIF  "$(CFG)" == "Alpha Debug"

".\Alpha-d\gleasvw.obj" :  $(SOURCE)  $(DEP_GLEASV) $(INTDIR)

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\gleasy.rc
DEP_GLEASY=\
	.\res\gleasy.ico\
	.\res\msdn.ico\
	.\res\toolbar.bmp\
	.\res\gleasy.rc2

!IF  "$(CFG)" == "Win32 Debug"

$(INTDIR)/"gleasy.res" :  $(SOURCE)  $(DEP_GLEASY) $(INTDIR)
   $(RSC) $(RSC_PROJ)  $(SOURCE) 

!ELSEIF  "$(CFG)" == "Win32 Release"

$(INTDIR)/"gleasy.res" :  $(SOURCE)  $(DEP_GLEASY) $(INTDIR)
   $(RSC) $(RSC_PROJ)  $(SOURCE) 

!ELSEIF  "$(CFG)" == "MIPs Release"

".\MIPS-r\gleasy.res" :  $(SOURCE)  $(DEP_GLEASY) $(INTDIR)
   $(RSC) $(RSC_PROJ)  $(SOURCE) 

!ELSEIF  "$(CFG)" == "MIPs Debug"

".\MIPS-d\gleasy.res" :  $(SOURCE)  $(DEP_GLEASY) $(INTDIR)
   $(RSC) $(RSC_PROJ)  $(SOURCE) 

!ELSEIF  "$(CFG)" == "Alpha Release"

".\Alpha-r\gleasy.res" :  $(SOURCE)  $(DEP_GLEASY) $(INTDIR)
   $(RSC) $(RSC_PROJ)  $(SOURCE) 

!ELSEIF  "$(CFG)" == "Alpha Debug"

".\Alpha-d\gleasy.res" :  $(SOURCE)  $(DEP_GLEASY) $(INTDIR)
   $(RSC) $(RSC_PROJ)  $(SOURCE) 

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\readme.txt
# End Source File
# End Group
# End Project
################################################################################
