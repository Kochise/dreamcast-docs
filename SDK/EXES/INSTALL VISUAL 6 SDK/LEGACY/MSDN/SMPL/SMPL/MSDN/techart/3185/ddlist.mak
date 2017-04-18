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
!MESSAGE NMAKE /f "ddlist.mak" CFG="Win32 Debug"
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
# PROP Target_Last_Scanned "Win32 Debug"
MTL=MkTypLib.exe
CPP=cl.exe
RSC=rc.exe

!IF  "$(CFG)" == "Win32 Release"

# PROP BASE Use_MFC 1
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "WinRel"
# PROP BASE Intermediate_Dir "WinRel"
# PROP Use_MFC 1
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "WinRel"
# PROP Intermediate_Dir "WinRel"
OUTDIR=.\WinRel
INTDIR=.\WinRel

ALL : $(OUTDIR)/ddlist.exe $(OUTDIR)/ddlist.bsc

$(OUTDIR) : 
    if not exist $(OUTDIR)/nul mkdir $(OUTDIR)

# ADD BASE MTL /nologo /D "NDEBUG" /win32
# ADD MTL /nologo /D "NDEBUG" /win32
MTL_PROJ=/nologo /D "NDEBUG" /win32 
# ADD BASE CPP /nologo /MT /W3 /GX /YX /Ox /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_X86_" /D "_MBCS" /FR /c
# ADD CPP /nologo /MT /W3 /GX /Ox /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_X86_" /D "_MBCS" /FR /Yu"STDAFX.H" /c
CPP_PROJ=/nologo /MT /W3 /GX /Ox /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D\
 "_X86_" /D "_MBCS" /FR$(INTDIR)/ /Fp$(OUTDIR)/"ddlist.pch" /Yu"STDAFX.H"\
 /Fo$(INTDIR)/ /c 
CPP_OBJS=.\WinRel/
# ADD BASE RSC /l 0x409 /d "NDEBUG"
# ADD RSC /l 0x409 /d "NDEBUG"
RSC_PROJ=/l 0x409 /fo$(INTDIR)/"ddlist.res" /d "NDEBUG" 
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
BSC32_FLAGS=/nologo /o$(OUTDIR)/"ddlist.bsc" 
BSC32_SBRS= \
	$(INTDIR)/stdafx.sbr \
	$(INTDIR)/ddlist.sbr \
	$(INTDIR)/mainfrm.sbr \
	$(INTDIR)/ddlisdoc.sbr \
	$(INTDIR)/ddlisvw.sbr \
	$(INTDIR)/strlist.sbr \
	$(INTDIR)/ddlstbox.sbr \
	$(INTDIR)/ddclip.sbr

$(OUTDIR)/ddlist.bsc : $(OUTDIR)  $(BSC32_SBRS)
    $(BSC32) @<<
  $(BSC32_FLAGS) $(BSC32_SBRS)
<<

LINK32=link.exe
# ADD BASE LINK32 nafxcw.lib olecli32.lib olesvr32.lib /NOLOGO /SUBSYSTEM:windows /MACHINE:IX86
# ADD LINK32 nafxcw.lib olecli32.lib olesvr32.lib /NOLOGO /SUBSYSTEM:windows /MACHINE:IX86
LINK32_FLAGS=nafxcw.lib olecli32.lib olesvr32.lib /NOLOGO /SUBSYSTEM:windows\
 /INCREMENTAL:no /PDB:$(OUTDIR)/"ddlist.pdb" /MACHINE:IX86\
 /OUT:$(OUTDIR)/"ddlist.exe" 
DEF_FILE=
LINK32_OBJS= \
	$(INTDIR)/ddlist.res \
	$(INTDIR)/stdafx.obj \
	$(INTDIR)/ddlist.obj \
	$(INTDIR)/mainfrm.obj \
	$(INTDIR)/ddlisdoc.obj \
	$(INTDIR)/ddlisvw.obj \
	$(INTDIR)/strlist.obj \
	$(INTDIR)/ddlstbox.obj \
	$(INTDIR)/ddclip.obj

$(OUTDIR)/ddlist.exe : $(OUTDIR)  $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ELSEIF  "$(CFG)" == "Win32 Debug"

# PROP BASE Use_MFC 1
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "WinDebug"
# PROP BASE Intermediate_Dir "WinDebug"
# PROP Use_MFC 1
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "WinDebug"
# PROP Intermediate_Dir "WinDebug"
OUTDIR=.\WinDebug
INTDIR=.\WinDebug

ALL : $(OUTDIR)/ddlist.exe $(OUTDIR)/ddlist.bsc

$(OUTDIR) : 
    if not exist $(OUTDIR)/nul mkdir $(OUTDIR)

# ADD BASE MTL /nologo /D "_DEBUG" /win32
# ADD MTL /nologo /D "_DEBUG" /win32
MTL_PROJ=/nologo /D "_DEBUG" /win32 
# ADD BASE CPP /nologo /MT /W3 /GX /Zi /YX /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_X86_" /D "_MBCS" /FR /c
# ADD CPP /nologo /MT /W3 /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_X86_" /D "_MBCS" /FR /Yu"STDAFX.H" /c
CPP_PROJ=/nologo /MT /W3 /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D\
 "_X86_" /D "_MBCS" /FR$(INTDIR)/ /Fp$(OUTDIR)/"ddlist.pch" /Yu"STDAFX.H"\
 /Fo$(INTDIR)/ /Fd$(OUTDIR)/"ddlist.pdb" /c 
CPP_OBJS=.\WinDebug/
# ADD BASE RSC /l 0x409 /d "_DEBUG"
# ADD RSC /l 0x409 /d "_DEBUG"
RSC_PROJ=/l 0x409 /fo$(INTDIR)/"ddlist.res" /d "_DEBUG" 
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
BSC32_FLAGS=/nologo /o$(OUTDIR)/"ddlist.bsc" 
BSC32_SBRS= \
	$(INTDIR)/stdafx.sbr \
	$(INTDIR)/ddlist.sbr \
	$(INTDIR)/mainfrm.sbr \
	$(INTDIR)/ddlisdoc.sbr \
	$(INTDIR)/ddlisvw.sbr \
	$(INTDIR)/strlist.sbr \
	$(INTDIR)/ddlstbox.sbr \
	$(INTDIR)/ddclip.sbr

$(OUTDIR)/ddlist.bsc : $(OUTDIR)  $(BSC32_SBRS)
    $(BSC32) @<<
  $(BSC32_FLAGS) $(BSC32_SBRS)
<<

LINK32=link.exe
# ADD BASE LINK32 nafxcwd.lib olecli32.lib olesvr32.lib /NOLOGO /SUBSYSTEM:windows /DEBUG /MACHINE:IX86
# ADD LINK32 nafxcwd.lib olecli32.lib olesvr32.lib /NOLOGO /SUBSYSTEM:windows /DEBUG /MACHINE:IX86
LINK32_FLAGS=nafxcwd.lib olecli32.lib olesvr32.lib /NOLOGO /SUBSYSTEM:windows\
 /INCREMENTAL:yes /PDB:$(OUTDIR)/"ddlist.pdb" /DEBUG /MACHINE:IX86\
 /OUT:$(OUTDIR)/"ddlist.exe" 
DEF_FILE=
LINK32_OBJS= \
	$(INTDIR)/ddlist.res \
	$(INTDIR)/stdafx.obj \
	$(INTDIR)/ddlist.obj \
	$(INTDIR)/mainfrm.obj \
	$(INTDIR)/ddlisdoc.obj \
	$(INTDIR)/ddlisvw.obj \
	$(INTDIR)/strlist.obj \
	$(INTDIR)/ddlstbox.obj \
	$(INTDIR)/ddclip.obj

$(OUTDIR)/ddlist.exe : $(OUTDIR)  $(DEF_FILE) $(LINK32_OBJS)
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

SOURCE=.\ddlist.rc
DEP_DDLIS=\
	.\RES\DDLIST.ICO\
	.\RES\DDLISDOC.ICO\
	.\RES\TOOLBAR.BMP\
	.\RES\DRAG1.CUR\
	.\res\ddlist.rc2

$(INTDIR)/ddlist.res :  $(SOURCE)  $(DEP_DDLIS) $(INTDIR)
   $(RSC) $(RSC_PROJ)  $(SOURCE) 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\stdafx.cpp
DEP_STDAF=\
	.\stdafx.h

!IF  "$(CFG)" == "Win32 Release"

# ADD BASE CPP /Yc"STDAFX.H"
# ADD CPP /Yc"STDAFX.H"

$(INTDIR)/stdafx.obj :  $(SOURCE)  $(DEP_STDAF) $(INTDIR)
   $(CPP) /nologo /MT /W3 /GX /Ox /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D\
 "_X86_" /D "_MBCS" /FR$(INTDIR)/ /Fp$(OUTDIR)/"ddlist.pch" /Yc"STDAFX.H"\
 /Fo$(INTDIR)/ /c  $(SOURCE) 

!ELSEIF  "$(CFG)" == "Win32 Debug"

# ADD BASE CPP /Yc"STDAFX.H"
# ADD CPP /Yc"STDAFX.H"

$(INTDIR)/stdafx.obj :  $(SOURCE)  $(DEP_STDAF) $(INTDIR)
   $(CPP) /nologo /MT /W3 /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D\
 "_X86_" /D "_MBCS" /FR$(INTDIR)/ /Fp$(OUTDIR)/"ddlist.pch" /Yc"STDAFX.H"\
 /Fo$(INTDIR)/ /Fd$(OUTDIR)/"ddlist.pdb" /c  $(SOURCE) 

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\ddlist.cpp
DEP_DDLIST=\
	.\stdafx.h\
	.\ddlist.h\
	.\strlist.h\
	.\mainfrm.h\
	.\ddlisdoc.h\
	.\ddlisvw.h\
	.\ddlstbox.h

$(INTDIR)/ddlist.obj :  $(SOURCE)  $(DEP_DDLIST) $(INTDIR) $(INTDIR)/stdafx.obj

# End Source File
################################################################################
# Begin Source File

SOURCE=.\mainfrm.cpp
DEP_MAINF=\
	.\stdafx.h\
	.\ddlist.h\
	.\mainfrm.h

$(INTDIR)/mainfrm.obj :  $(SOURCE)  $(DEP_MAINF) $(INTDIR) $(INTDIR)/stdafx.obj

# End Source File
################################################################################
# Begin Source File

SOURCE=.\ddlisdoc.cpp
DEP_DDLISD=\
	.\stdafx.h\
	.\ddlist.h\
	.\strlist.h\
	.\ddlisdoc.h

$(INTDIR)/ddlisdoc.obj :  $(SOURCE)  $(DEP_DDLISD) $(INTDIR)\
 $(INTDIR)/stdafx.obj

# End Source File
################################################################################
# Begin Source File

SOURCE=.\ddlisvw.cpp
DEP_DDLISV=\
	.\stdafx.h\
	.\ddlist.h\
	.\strlist.h\
	.\ddlisdoc.h\
	.\ddclip.h\
	.\ddlisvw.h\
	.\ddlstbox.h

$(INTDIR)/ddlisvw.obj :  $(SOURCE)  $(DEP_DDLISV) $(INTDIR)\
 $(INTDIR)/stdafx.obj

# End Source File
################################################################################
# Begin Source File

SOURCE=.\strlist.cpp
DEP_STRLI=\
	.\stdafx.h\
	.\strlist.h

$(INTDIR)/strlist.obj :  $(SOURCE)  $(DEP_STRLI) $(INTDIR) $(INTDIR)/stdafx.obj

# End Source File
################################################################################
# Begin Source File

SOURCE=.\ddlstbox.cpp
DEP_DDLST=\
	.\stdafx.h\
	.\ddlstbox.h\
	.\ddclip.h

$(INTDIR)/ddlstbox.obj :  $(SOURCE)  $(DEP_DDLST) $(INTDIR)\
 $(INTDIR)/stdafx.obj

# End Source File
################################################################################
# Begin Source File

SOURCE=.\ddclip.cpp
DEP_DDCLI=\
	.\stdafx.h\
	.\ddclip.h

$(INTDIR)/ddclip.obj :  $(SOURCE)  $(DEP_DDCLI) $(INTDIR) $(INTDIR)/stdafx.obj

# End Source File
# End Group
# End Project
################################################################################
