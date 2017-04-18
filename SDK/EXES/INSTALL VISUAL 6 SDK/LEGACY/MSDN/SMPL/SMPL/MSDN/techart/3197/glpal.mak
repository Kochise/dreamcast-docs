# Microsoft Visual C++ Generated NMAKE File, Format Version 20054
# MSVCPRJ: version 2.00.4215
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
!MESSAGE NMAKE /f "glpal.mak" CFG="Win32 Debug"
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

ALL : ".\x86-d\glpal.exe" ".\x86-d\glpal.bsc"

$(OUTDIR) : 
    if not exist $(OUTDIR)/nul mkdir $(OUTDIR)

# ADD BASE CPP /nologo /MT /W3 /GX /Zi /Od /D "_DEBUG" /D "WIN32" /D "_WINDOWS" /D "_MBCS" /FR /Yu"stdafx.h" /c
# ADD CPP /nologo /MT /W3 /GX /Zi /Od /D "_DEBUG" /D "WIN32" /D "_WINDOWS" /D "_MBCS" /FR /Yu"stdafx.h" /c
CPP_PROJ=/nologo /MT /W3 /GX /Zi /Od /D "_DEBUG" /D "WIN32" /D "_WINDOWS" /D\
 "_MBCS" /FR$(INTDIR)/ /Fp$(OUTDIR)/"glpal.pch" /Yu"stdafx.h" /Fo$(INTDIR)/\
 /Fd$(OUTDIR)/"glpal.pdb" /c 
CPP_OBJS=".\x86-d/"
# ADD BASE RSC /l 0x409 /d "_DEBUG"
# ADD RSC /l 0x409 /d "_DEBUG"
RSC_PROJ=/l 0x409 /fo$(INTDIR)/"glpal.res" /d "_DEBUG" 
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
BSC32_FLAGS=/nologo /o$(OUTDIR)/"glpal.bsc" 
BSC32_SBRS= \
	".\x86-d\stdafx.sbr" \
	".\x86-d\glpal.sbr" \
	".\x86-d\mainfrm.sbr" \
	".\x86-d\glpaldoc.sbr" \
	".\x86-d\glpalvw.sbr" \
	".\x86-d\paldlg.sbr"

".\x86-d\glpal.bsc" : $(OUTDIR)  $(BSC32_SBRS)
    $(BSC32) @<<
  $(BSC32_FLAGS) $(BSC32_SBRS)
<<

LINK32=link.exe
# ADD BASE LINK32 /NOLOGO /SUBSYSTEM:windows /DEBUG /MACHINE:I386
# SUBTRACT BASE LINK32 /PDB:none
# ADD LINK32 opengl32.lib glu32.lib /NOLOGO /SUBSYSTEM:windows /DEBUG /MACHINE:I386
# SUBTRACT LINK32 /PDB:none
LINK32_FLAGS=opengl32.lib glu32.lib /NOLOGO /SUBSYSTEM:windows /INCREMENTAL:yes\
 /PDB:$(OUTDIR)/"glpal.pdb" /DEBUG /MACHINE:I386 /OUT:$(OUTDIR)/"glpal.exe" 
DEF_FILE=
LINK32_OBJS= \
	".\x86-d\stdafx.obj" \
	".\x86-d\glpal.obj" \
	".\x86-d\mainfrm.obj" \
	".\x86-d\glpaldoc.obj" \
	".\x86-d\glpalvw.obj" \
	".\x86-d\glpal.res" \
	".\x86-d\paldlg.obj"

".\x86-d\glpal.exe" : $(OUTDIR)  $(DEF_FILE) $(LINK32_OBJS)
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

ALL : ".\x86-r\glpal.exe" ".\x86-r\glpal.bsc"

$(OUTDIR) : 
    if not exist $(OUTDIR)/nul mkdir $(OUTDIR)

# ADD BASE CPP /nologo /MT /W3 /GX /O2 /D "NDEBUG" /D "WIN32" /D "_WINDOWS" /D "_MBCS" /FR /Yu"stdafx.h" /c
# ADD CPP /nologo /MT /W3 /GX /O2 /D "NDEBUG" /D "WIN32" /D "_WINDOWS" /D "_MBCS" /FR /Yu"stdafx.h" /c
CPP_PROJ=/nologo /MT /W3 /GX /O2 /D "NDEBUG" /D "WIN32" /D "_WINDOWS" /D\
 "_MBCS" /FR$(INTDIR)/ /Fp$(OUTDIR)/"glpal.pch" /Yu"stdafx.h" /Fo$(INTDIR)/ /c 
CPP_OBJS=".\x86-r/"
# ADD BASE RSC /l 0x409 /d "NDEBUG"
# ADD RSC /l 0x409 /d "NDEBUG"
RSC_PROJ=/l 0x409 /fo$(INTDIR)/"glpal.res" /d "NDEBUG" 
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
BSC32_FLAGS=/nologo /o$(OUTDIR)/"glpal.bsc" 
BSC32_SBRS= \
	".\x86-r\stdafx.sbr" \
	".\x86-r\glpal.sbr" \
	".\x86-r\mainfrm.sbr" \
	".\x86-r\glpaldoc.sbr" \
	".\x86-r\glpalvw.sbr" \
	".\x86-r\paldlg.sbr"

".\x86-r\glpal.bsc" : $(OUTDIR)  $(BSC32_SBRS)
    $(BSC32) @<<
  $(BSC32_FLAGS) $(BSC32_SBRS)
<<

LINK32=link.exe
# ADD BASE LINK32 /NOLOGO /SUBSYSTEM:windows /MACHINE:I386
# SUBTRACT BASE LINK32 /PDB:none
# ADD LINK32 opengl32.lib glu32.lib /NOLOGO /SUBSYSTEM:windows /MACHINE:I386
# SUBTRACT LINK32 /PDB:none
LINK32_FLAGS=opengl32.lib glu32.lib /NOLOGO /SUBSYSTEM:windows /INCREMENTAL:no\
 /PDB:$(OUTDIR)/"glpal.pdb" /MACHINE:I386 /OUT:$(OUTDIR)/"glpal.exe" 
DEF_FILE=
LINK32_OBJS= \
	".\x86-r\stdafx.obj" \
	".\x86-r\glpal.obj" \
	".\x86-r\mainfrm.obj" \
	".\x86-r\glpaldoc.obj" \
	".\x86-r\glpalvw.obj" \
	".\x86-r\glpal.res" \
	".\x86-r\paldlg.obj"

".\x86-r\glpal.exe" : $(OUTDIR)  $(DEF_FILE) $(LINK32_OBJS)
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

".\x86-d\stdafx.obj" :  $(SOURCE)  $(DEP_STDAF) $(INTDIR)
   $(CPP) /nologo /MT /W3 /GX /Zi /Od /D "_DEBUG" /D "WIN32" /D "_WINDOWS" /D\
 "_MBCS" /FR$(INTDIR)/ /Fp$(OUTDIR)/"glpal.pch" /Yc"stdafx.h" /Fo$(INTDIR)/\
 /Fd$(OUTDIR)/"glpal.pdb" /c  $(SOURCE) 

!ELSEIF  "$(CFG)" == "Win32 Release"

# ADD BASE CPP /Yc"stdafx.h"
# ADD CPP /Yc"stdafx.h"

".\x86-r\stdafx.obj" :  $(SOURCE)  $(DEP_STDAF) $(INTDIR)
   $(CPP) /nologo /MT /W3 /GX /O2 /D "NDEBUG" /D "WIN32" /D "_WINDOWS" /D\
 "_MBCS" /FR$(INTDIR)/ /Fp$(OUTDIR)/"glpal.pch" /Yc"stdafx.h" /Fo$(INTDIR)/ /c\
  $(SOURCE) 

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\glpal.cpp
DEP_GLPAL=\
	.\mainfrm.h\
	.\glpaldoc.h\
	.\glpalvw.h\
	.\glpal.h

!IF  "$(CFG)" == "Win32 Debug"

".\x86-d\glpal.obj" :  $(SOURCE)  $(DEP_GLPAL) $(INTDIR) .\x86-d\stdafx.obj

!ELSEIF  "$(CFG)" == "Win32 Release"

".\x86-r\glpal.obj" :  $(SOURCE)  $(DEP_GLPAL) $(INTDIR) .\x86-r\stdafx.obj

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\mainfrm.cpp
DEP_MAINF=\
	.\glpal.h\
	.\mainfrm.h

!IF  "$(CFG)" == "Win32 Debug"

".\x86-d\mainfrm.obj" :  $(SOURCE)  $(DEP_MAINF) $(INTDIR) .\x86-d\stdafx.obj

!ELSEIF  "$(CFG)" == "Win32 Release"

".\x86-r\mainfrm.obj" :  $(SOURCE)  $(DEP_MAINF) $(INTDIR) .\x86-r\stdafx.obj

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\glpaldoc.cpp
DEP_GLPALD=\
	.\glpal.h\
	.\glpaldoc.h

!IF  "$(CFG)" == "Win32 Debug"

".\x86-d\glpaldoc.obj" :  $(SOURCE)  $(DEP_GLPALD) $(INTDIR) .\x86-d\stdafx.obj

!ELSEIF  "$(CFG)" == "Win32 Release"

".\x86-r\glpaldoc.obj" :  $(SOURCE)  $(DEP_GLPALD) $(INTDIR) .\x86-r\stdafx.obj

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\glpalvw.cpp
DEP_GLPALV=\
	.\glpal.h\
	.\glpaldoc.h\
	.\glpalvw.h

!IF  "$(CFG)" == "Win32 Debug"

".\x86-d\glpalvw.obj" :  $(SOURCE)  $(DEP_GLPALV) $(INTDIR) .\x86-d\stdafx.obj

!ELSEIF  "$(CFG)" == "Win32 Release"

".\x86-r\glpalvw.obj" :  $(SOURCE)  $(DEP_GLPALV) $(INTDIR) .\x86-r\stdafx.obj

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\glpal.rc
DEP_GLPAL_=\
	.\res\glpal.ico\
	.\res\glpal.rc2

!IF  "$(CFG)" == "Win32 Debug"

".\x86-d\glpal.res" :  $(SOURCE)  $(DEP_GLPAL_) $(INTDIR)
   $(RSC) $(RSC_PROJ)  $(SOURCE) 

!ELSEIF  "$(CFG)" == "Win32 Release"

".\x86-r\glpal.res" :  $(SOURCE)  $(DEP_GLPAL_) $(INTDIR)
   $(RSC) $(RSC_PROJ)  $(SOURCE) 

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\readme.txt
# End Source File
################################################################################
# Begin Source File

SOURCE=.\paldlg.cpp
DEP_PALDL=\
	.\stdafx.h\
	.\glpal.h\
	.\paldlg.h

!IF  "$(CFG)" == "Win32 Debug"

".\x86-d\paldlg.obj" :  $(SOURCE)  $(DEP_PALDL) $(INTDIR) .\x86-d\stdafx.obj

!ELSEIF  "$(CFG)" == "Win32 Release"

".\x86-r\paldlg.obj" :  $(SOURCE)  $(DEP_PALDL) $(INTDIR) .\x86-r\stdafx.obj

!ENDIF 

# End Source File
# End Group
# End Project
################################################################################
