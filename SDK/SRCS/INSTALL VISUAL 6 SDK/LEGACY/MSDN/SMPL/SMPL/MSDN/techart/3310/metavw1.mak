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
!MESSAGE NMAKE /f "metavw1.mak" CFG="Win32 Debug"
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
# PROP Output_Dir "WinDebug"
# PROP Intermediate_Dir "WinDebug"
OUTDIR=.\WinDebug
INTDIR=.\WinDebug

ALL : .\WinDebug\metavw1.exe .\WinDebug\metavw1.bsc

$(OUTDIR) : 
    if not exist $(OUTDIR)/nul mkdir $(OUTDIR)

# ADD BASE CPP /nologo /MT /W3 /GX /Zi /Od /D "_DEBUG" /D "WIN32" /D "_WINDOWS" /D "_MBCS" /FR /Yu"stdafx.h" /c
# ADD CPP /nologo /MT /W3 /GX /Zi /Od /D "_DEBUG" /D "WIN32" /D "_WINDOWS" /D "_MBCS" /FR /Yu"stdafx.h" /c
CPP_PROJ=/nologo /MT /W3 /GX /Zi /Od /D "_DEBUG" /D "WIN32" /D "_WINDOWS" /D\
 "_MBCS" /FR$(INTDIR)/ /Fp$(OUTDIR)/"metavw1.pch" /Yu"stdafx.h" /Fo$(INTDIR)/\
 /Fd$(OUTDIR)/"metavw1.pdb" /c 
CPP_OBJS=.\WinDebug/
# ADD BASE RSC /l 0x409 /d "_DEBUG"
# ADD RSC /l 0x409 /d "_DEBUG"
RSC_PROJ=/l 0x409 /fo$(INTDIR)/"metavw1.res" /d "_DEBUG" 
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
BSC32_FLAGS=/nologo /o$(OUTDIR)/"metavw1.bsc" 
BSC32_SBRS= \
	.\WinDebug\stdafx.sbr \
	.\WinDebug\metavw1.sbr \
	.\WinDebug\mainfrm.sbr \
	.\WinDebug\metavdoc.sbr \
	.\WinDebug\metavvw.sbr \
	.\WinDebug\cemf.sbr \
	.\WinDebug\emfinfov.sbr

.\WinDebug\metavw1.bsc : $(OUTDIR)  $(BSC32_SBRS)
    $(BSC32) @<<
  $(BSC32_FLAGS) $(BSC32_SBRS)
<<

LINK32=link.exe
# ADD BASE LINK32 /NOLOGO /SUBSYSTEM:windows /DEBUG /MACHINE:I386
# SUBTRACT BASE LINK32 /PDB:none
# ADD LINK32 /NOLOGO /SUBSYSTEM:windows /DEBUG /MACHINE:I386
# SUBTRACT LINK32 /PDB:none
LINK32_FLAGS=/NOLOGO /SUBSYSTEM:windows /INCREMENTAL:yes\
 /PDB:$(OUTDIR)/"metavw1.pdb" /DEBUG /MACHINE:I386 /OUT:$(OUTDIR)/"metavw1.exe" 
DEF_FILE=
LINK32_OBJS= \
	.\WinDebug\stdafx.obj \
	.\WinDebug\metavw1.obj \
	.\WinDebug\mainfrm.obj \
	.\WinDebug\metavdoc.obj \
	.\WinDebug\metavvw.obj \
	.\WinDebug\metavw1.res \
	.\WinDebug\cemf.obj \
	.\WinDebug\emfinfov.obj

.\WinDebug\metavw1.exe : $(OUTDIR)  $(DEF_FILE) $(LINK32_OBJS)
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
# PROP Output_Dir "WinRel"
# PROP Intermediate_Dir "WinRel"
OUTDIR=.\WinRel
INTDIR=.\WinRel

ALL : .\WinRel\metavw1.exe .\WinRel\metavw1.bsc

$(OUTDIR) : 
    if not exist $(OUTDIR)/nul mkdir $(OUTDIR)

# ADD BASE CPP /nologo /MT /W3 /GX /O2 /D "NDEBUG" /D "WIN32" /D "_WINDOWS" /D "_MBCS" /FR /Yu"stdafx.h" /c
# ADD CPP /nologo /MT /W3 /GX /O2 /D "NDEBUG" /D "WIN32" /D "_WINDOWS" /D "_MBCS" /FR /Yu"stdafx.h" /c
CPP_PROJ=/nologo /MT /W3 /GX /O2 /D "NDEBUG" /D "WIN32" /D "_WINDOWS" /D\
 "_MBCS" /FR$(INTDIR)/ /Fp$(OUTDIR)/"metavw1.pch" /Yu"stdafx.h" /Fo$(INTDIR)/ /c\
 
CPP_OBJS=.\WinRel/
# ADD BASE RSC /l 0x409 /d "NDEBUG"
# ADD RSC /l 0x409 /d "NDEBUG"
RSC_PROJ=/l 0x409 /fo$(INTDIR)/"metavw1.res" /d "NDEBUG" 
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
BSC32_FLAGS=/nologo /o$(OUTDIR)/"metavw1.bsc" 
BSC32_SBRS= \
	.\WinRel\stdafx.sbr \
	.\WinRel\metavw1.sbr \
	.\WinRel\mainfrm.sbr \
	.\WinRel\metavdoc.sbr \
	.\WinRel\metavvw.sbr \
	.\WinRel\cemf.sbr \
	.\WinRel\emfinfov.sbr

.\WinRel\metavw1.bsc : $(OUTDIR)  $(BSC32_SBRS)
    $(BSC32) @<<
  $(BSC32_FLAGS) $(BSC32_SBRS)
<<

LINK32=link.exe
# ADD BASE LINK32 /NOLOGO /SUBSYSTEM:windows /MACHINE:I386
# SUBTRACT BASE LINK32 /PDB:none
# ADD LINK32 /NOLOGO /SUBSYSTEM:windows /MACHINE:I386
# SUBTRACT LINK32 /PDB:none
LINK32_FLAGS=/NOLOGO /SUBSYSTEM:windows /INCREMENTAL:no\
 /PDB:$(OUTDIR)/"metavw1.pdb" /MACHINE:I386 /OUT:$(OUTDIR)/"metavw1.exe" 
DEF_FILE=
LINK32_OBJS= \
	.\WinRel\stdafx.obj \
	.\WinRel\metavw1.obj \
	.\WinRel\mainfrm.obj \
	.\WinRel\metavdoc.obj \
	.\WinRel\metavvw.obj \
	.\WinRel\metavw1.res \
	.\WinRel\cemf.obj \
	.\WinRel\emfinfov.obj

.\WinRel\metavw1.exe : $(OUTDIR)  $(DEF_FILE) $(LINK32_OBJS)
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

.\WinDebug\stdafx.obj :  $(SOURCE)  $(DEP_STDAF) $(INTDIR)
   $(CPP) /nologo /MT /W3 /GX /Zi /Od /D "_DEBUG" /D "WIN32" /D "_WINDOWS" /D\
 "_MBCS" /FR$(INTDIR)/ /Fp$(OUTDIR)/"metavw1.pch" /Yc"stdafx.h" /Fo$(INTDIR)/\
 /Fd$(OUTDIR)/"metavw1.pdb" /c  $(SOURCE) 

!ELSEIF  "$(CFG)" == "Win32 Release"

# ADD BASE CPP /Yc"stdafx.h"
# ADD CPP /Yc"stdafx.h"

.\WinRel\stdafx.obj :  $(SOURCE)  $(DEP_STDAF) $(INTDIR)
   $(CPP) /nologo /MT /W3 /GX /O2 /D "NDEBUG" /D "WIN32" /D "_WINDOWS" /D\
 "_MBCS" /FR$(INTDIR)/ /Fp$(OUTDIR)/"metavw1.pch" /Yc"stdafx.h" /Fo$(INTDIR)/ /c\
  $(SOURCE) 

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\metavw1.cpp
DEP_METAV=\
	.\stdafx.h\
	.\metavw1.h\
	.\mainfrm.h\
	.\metavdoc.h\
	.\metavvw.h\
	.\emfinfov.h\
	.\cemf.h

!IF  "$(CFG)" == "Win32 Debug"

.\WinDebug\metavw1.obj :  $(SOURCE)  $(DEP_METAV) $(INTDIR)\
 .\WinDebug\stdafx.obj

!ELSEIF  "$(CFG)" == "Win32 Release"

.\WinRel\metavw1.obj :  $(SOURCE)  $(DEP_METAV) $(INTDIR) .\WinRel\stdafx.obj

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\mainfrm.cpp
DEP_MAINF=\
	.\stdafx.h\
	.\metavw1.h\
	.\metavdoc.h\
	.\emfinfov.h\
	.\metavvw.h\
	.\mainfrm.h\
	.\cemf.h

!IF  "$(CFG)" == "Win32 Debug"

.\WinDebug\mainfrm.obj :  $(SOURCE)  $(DEP_MAINF) $(INTDIR)\
 .\WinDebug\stdafx.obj

!ELSEIF  "$(CFG)" == "Win32 Release"

.\WinRel\mainfrm.obj :  $(SOURCE)  $(DEP_MAINF) $(INTDIR) .\WinRel\stdafx.obj

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\metavdoc.cpp
DEP_METAVD=\
	.\stdafx.h\
	.\metavw1.h\
	.\metavdoc.h\
	.\cemf.h

!IF  "$(CFG)" == "Win32 Debug"

.\WinDebug\metavdoc.obj :  $(SOURCE)  $(DEP_METAVD) $(INTDIR)\
 .\WinDebug\stdafx.obj

!ELSEIF  "$(CFG)" == "Win32 Release"

.\WinRel\metavdoc.obj :  $(SOURCE)  $(DEP_METAVD) $(INTDIR) .\WinRel\stdafx.obj

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\metavvw.cpp
DEP_METAVV=\
	.\stdafx.h\
	.\metavw1.h\
	.\metavdoc.h\
	.\metavvw.h\
	.\cemf.h

!IF  "$(CFG)" == "Win32 Debug"

.\WinDebug\metavvw.obj :  $(SOURCE)  $(DEP_METAVV) $(INTDIR)\
 .\WinDebug\stdafx.obj

!ELSEIF  "$(CFG)" == "Win32 Release"

.\WinRel\metavvw.obj :  $(SOURCE)  $(DEP_METAVV) $(INTDIR) .\WinRel\stdafx.obj

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\metavw1.rc
DEP_METAVW=\
	.\res\metavw1.ico\
	.\res\metavdoc.ico\
	.\res\idr_emfi.ico\
	.\res\toolbar.bmp\
	.\res\metavw1.rc2

!IF  "$(CFG)" == "Win32 Debug"

.\WinDebug\metavw1.res :  $(SOURCE)  $(DEP_METAVW) $(INTDIR)
   $(RSC) $(RSC_PROJ)  $(SOURCE) 

!ELSEIF  "$(CFG)" == "Win32 Release"

.\WinRel\metavw1.res :  $(SOURCE)  $(DEP_METAVW) $(INTDIR)
   $(RSC) $(RSC_PROJ)  $(SOURCE) 

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\readme.txt
# End Source File
################################################################################
# Begin Source File

SOURCE=.\cemf.cpp
DEP_CEMF_=\
	.\stdafx.h\
	.\cemf.h

!IF  "$(CFG)" == "Win32 Debug"

.\WinDebug\cemf.obj :  $(SOURCE)  $(DEP_CEMF_) $(INTDIR) .\WinDebug\stdafx.obj

!ELSEIF  "$(CFG)" == "Win32 Release"

.\WinRel\cemf.obj :  $(SOURCE)  $(DEP_CEMF_) $(INTDIR) .\WinRel\stdafx.obj

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\emfinfov.cpp
DEP_EMFIN=\
	.\stdafx.h\
	.\metavw1.h\
	.\metavdoc.h\
	.\emfinfov.h\
	.\cemf.h

!IF  "$(CFG)" == "Win32 Debug"

.\WinDebug\emfinfov.obj :  $(SOURCE)  $(DEP_EMFIN) $(INTDIR)\
 .\WinDebug\stdafx.obj

!ELSEIF  "$(CFG)" == "Win32 Release"

.\WinRel\emfinfov.obj :  $(SOURCE)  $(DEP_EMFIN) $(INTDIR) .\WinRel\stdafx.obj

!ENDIF 

# End Source File
# End Group
# End Project
################################################################################
