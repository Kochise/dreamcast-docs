# Microsoft Visual C++ Generated NMAKE File, Format Version 2.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Application" 0x0101

!IF "$(CFG)" == ""
CFG=x86 Debug
!MESSAGE No configuration specified.  Defaulting to x86 Debug.
!ENDIF 

!IF "$(CFG)" != "x86 Release" && "$(CFG)" != "x86 Debug"
!MESSAGE Invalid configuration "$(CFG)" specified.
!MESSAGE You can specify a configuration when running NMAKE on this makefile
!MESSAGE by defining the macro CFG on the command line.  For example:
!MESSAGE 
!MESSAGE NMAKE /f "fwtest.mak" CFG="x86 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "x86 Release" (based on "Win32 (x86) Application")
!MESSAGE "x86 Debug" (based on "Win32 (x86) Application")
!MESSAGE 
!ERROR An invalid configuration is specified.
!ENDIF 

################################################################################
# Begin Project
# PROP Target_Last_Scanned "x86 Debug"
MTL=MkTypLib.exe
CPP=cl.exe
RSC=rc.exe

!IF  "$(CFG)" == "x86 Release"

# PROP BASE Use_MFC 1
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "WinRel"
# PROP BASE Intermediate_Dir "WinRel"
# PROP Use_MFC 1
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "x86-r"
# PROP Intermediate_Dir "x86-r"
OUTDIR=.\x86-r
INTDIR=.\x86-r

ALL : $(OUTDIR)/"fwtest.exe" $(OUTDIR)/"fwtest.bsc"

$(OUTDIR) : 
    if not exist $(OUTDIR)/nul mkdir $(OUTDIR)

# ADD BASE MTL /nologo /D "NDEBUG" /win32
# ADD MTL /nologo /D "NDEBUG" /win32
MTL_PROJ=/nologo /D "NDEBUG" /win32 
# ADD BASE CPP /nologo /MT /W3 /GX /YX /Ox /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_X86_" /D "_MBCS" /FR /c
# ADD CPP /nologo /MT /W3 /GX /Ox /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_X86_" /D "_MBCS" /Yu"STDAFX.H" /c
# SUBTRACT CPP /Fr
CPP_PROJ=/nologo /MT /W3 /GX /Ox /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D\
 "_X86_" /D "_MBCS" /Fp$(OUTDIR)/"fwtest.pch" /Yu"STDAFX.H" /Fo$(INTDIR)/ /c 
CPP_OBJS=".\x86-r/"
# ADD BASE RSC /l 0x409 /d "NDEBUG"
# ADD RSC /l 0x409 /d "NDEBUG"
RSC_PROJ=/l 0x409 /fo$(INTDIR)/"FWTEST.res" /d "NDEBUG" 
BSC32=bscmake.exe
BSC32_SBRS= \
	
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
BSC32_FLAGS=/nologo /o$(OUTDIR)/"fwtest.bsc" 

$(OUTDIR)/"fwtest.bsc" : $(OUTDIR)  $(BSC32_SBRS)
LINK32=link.exe
# ADD BASE LINK32 nafxcw.lib olecli32.lib olesvr32.lib winmm.lib ..\animate\lib\animater.lib /NOLOGO /SUBSYSTEM:windows /MACHINE:IX86
# ADD LINK32 nafxcw.lib olecli32.lib olesvr32.lib winmm.lib animater.lib /NOLOGO /SUBSYSTEM:windows /MACHINE:IX86
LINK32_FLAGS=nafxcw.lib olecli32.lib olesvr32.lib winmm.lib animater.lib\
 /NOLOGO /SUBSYSTEM:windows /INCREMENTAL:no /PDB:$(OUTDIR)/"fwtest.pdb"\
 /MACHINE:IX86 /OUT:$(OUTDIR)/"fwtest.exe" 
DEF_FILE=
LINK32_OBJS= \
	$(INTDIR)/"FWTEST.res" \
	$(INTDIR)/"stdafx.obj" \
	$(INTDIR)/"mainfrm.obj" \
	$(INTDIR)/"fwtesdoc.obj" \
	$(INTDIR)/"fwtesvw.obj" \
	$(INTDIR)/"scopefra.obj" \
	$(INTDIR)/"scopescr.obj" \
	$(INTDIR)/"dlgpanel.obj" \
	$(INTDIR)/"rotary.obj" \
	$(INTDIR)/"updnctl.obj" \
	$(INTDIR)/"panelfra.obj" \
	$(INTDIR)/"dlgtempl.obj" \
	$(INTDIR)/"dlgpanfm.obj" \
	$(INTDIR)/"fwtest.obj"

$(OUTDIR)/"fwtest.exe" : $(OUTDIR)  $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ELSEIF  "$(CFG)" == "x86 Debug"

# PROP BASE Use_MFC 1
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "WinDebug"
# PROP BASE Intermediate_Dir "WinDebug"
# PROP Use_MFC 1
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "x86-d"
# PROP Intermediate_Dir "x86-d"
OUTDIR=.\x86-d
INTDIR=.\x86-d

ALL : $(OUTDIR)/"fwtest.exe" $(OUTDIR)/"fwtest.bsc"

$(OUTDIR) : 
    if not exist $(OUTDIR)/nul mkdir $(OUTDIR)

# ADD BASE MTL /nologo /D "_DEBUG" /win32
# ADD MTL /nologo /D "_DEBUG" /win32
MTL_PROJ=/nologo /D "_DEBUG" /win32 
# ADD BASE CPP /nologo /MT /W3 /GX /Zi /YX /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_X86_" /D "_MBCS" /FR /c
# ADD CPP /nologo /MT /W3 /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_X86_" /D "_MBCS" /Yu"STDAFX.H" /c
# SUBTRACT CPP /Fr
CPP_PROJ=/nologo /MT /W3 /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D\
 "_X86_" /D "_MBCS" /Fp$(OUTDIR)/"fwtest.pch" /Yu"STDAFX.H" /Fo$(INTDIR)/\
 /Fd$(OUTDIR)/"fwtest.pdb" /c 
CPP_OBJS=".\x86-d/"
# ADD BASE RSC /l 0x409 /d "_DEBUG"
# ADD RSC /l 0x409 /d "_DEBUG"
RSC_PROJ=/l 0x409 /fo$(INTDIR)/"FWTEST.res" /d "_DEBUG" 
BSC32=bscmake.exe
BSC32_SBRS= \
	
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
BSC32_FLAGS=/nologo /o$(OUTDIR)/"fwtest.bsc" 

$(OUTDIR)/"fwtest.bsc" : $(OUTDIR)  $(BSC32_SBRS)
LINK32=link.exe
# ADD BASE LINK32 nafxcwd.lib olecli32.lib olesvr32.lib winmm.lib ..\animate\lib\animated.lib /NOLOGO /SUBSYSTEM:windows /DEBUG /MACHINE:IX86
# ADD LINK32 nafxcwd.lib olecli32.lib olesvr32.lib winmm.lib animated.lib /NOLOGO /SUBSYSTEM:windows /DEBUG /MACHINE:IX86
LINK32_FLAGS=nafxcwd.lib olecli32.lib olesvr32.lib winmm.lib animated.lib\
 /NOLOGO /SUBSYSTEM:windows /INCREMENTAL:yes /PDB:$(OUTDIR)/"fwtest.pdb" /DEBUG\
 /MACHINE:IX86 /OUT:$(OUTDIR)/"fwtest.exe" 
DEF_FILE=
LINK32_OBJS= \
	$(INTDIR)/"FWTEST.res" \
	$(INTDIR)/"stdafx.obj" \
	$(INTDIR)/"mainfrm.obj" \
	$(INTDIR)/"fwtesdoc.obj" \
	$(INTDIR)/"fwtesvw.obj" \
	$(INTDIR)/"scopefra.obj" \
	$(INTDIR)/"scopescr.obj" \
	$(INTDIR)/"dlgpanel.obj" \
	$(INTDIR)/"rotary.obj" \
	$(INTDIR)/"updnctl.obj" \
	$(INTDIR)/"panelfra.obj" \
	$(INTDIR)/"dlgtempl.obj" \
	$(INTDIR)/"dlgpanfm.obj" \
	$(INTDIR)/"fwtest.obj"

$(OUTDIR)/"fwtest.exe" : $(OUTDIR)  $(DEF_FILE) $(LINK32_OBJS)
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

SOURCE=.\FWTEST.RC
DEP_FWTES=\
	.\res\fwtest.ico\
	.\res\fwtesdoc.ico\
	.\res\idr_scop.ico\
	.\res\IDR_PANE.ICO\
	.\res\toolbar.bmp\
	.\res\bitmap1.bmp\
	.\res\BITMAP2.BMP\
	.\res\fwtest.rc2

$(INTDIR)/"FWTEST.res" :  $(SOURCE)  $(DEP_FWTES) $(INTDIR)
   $(RSC) $(RSC_PROJ)  $(SOURCE) 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\stdafx.cpp
DEP_STDAF=\
	.\stdafx.h

!IF  "$(CFG)" == "x86 Release"

# ADD BASE CPP /Yc"STDAFX.H"
# ADD CPP /Yc"STDAFX.H"

$(INTDIR)/"stdafx.obj" :  $(SOURCE)  $(DEP_STDAF) $(INTDIR)
   $(CPP) /nologo /MT /W3 /GX /Ox /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D\
 "_X86_" /D "_MBCS" /Fp$(OUTDIR)/"fwtest.pch" /Yc"STDAFX.H" /Fo$(INTDIR)/ /c\
  $(SOURCE) 

!ELSEIF  "$(CFG)" == "x86 Debug"

# ADD BASE CPP /Yc"STDAFX.H"
# ADD CPP /Yc"STDAFX.H"

$(INTDIR)/"stdafx.obj" :  $(SOURCE)  $(DEP_STDAF) $(INTDIR)
   $(CPP) /nologo /MT /W3 /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D\
 "_X86_" /D "_MBCS" /Fp$(OUTDIR)/"fwtest.pch" /Yc"STDAFX.H" /Fo$(INTDIR)/\
 /Fd$(OUTDIR)/"fwtest.pdb" /c  $(SOURCE) 

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\mainfrm.cpp
DEP_MAINF=\
	.\stdafx.h\
	.\fwtest.h\
	.\dlgpanel.h\
	.\dlgpanfm.h\
	.\rotary.h\
	.\updnctl.h\
	.\scopefra.h\
	.\panelfra.h\
	.\mainfrm.h\
	.\scopescr.h

$(INTDIR)/"mainfrm.obj" :  $(SOURCE)  $(DEP_MAINF) $(INTDIR)\
 $(INTDIR)/stdafx.obj

# End Source File
################################################################################
# Begin Source File

SOURCE=.\fwtesdoc.cpp
DEP_FWTESD=\
	.\stdafx.h\
	.\fwtest.h\
	.\fwtesdoc.h

$(INTDIR)/"fwtesdoc.obj" :  $(SOURCE)  $(DEP_FWTESD) $(INTDIR)\
 $(INTDIR)/stdafx.obj

# End Source File
################################################################################
# Begin Source File

SOURCE=.\fwtesvw.cpp
DEP_FWTESV=\
	.\stdafx.h\
	.\fwtest.h\
	.\fwtesdoc.h\
	.\fwtesvw.h

$(INTDIR)/"fwtesvw.obj" :  $(SOURCE)  $(DEP_FWTESV) $(INTDIR)\
 $(INTDIR)/stdafx.obj

# End Source File
################################################################################
# Begin Source File

SOURCE=.\scopefra.cpp
DEP_SCOPE=\
	.\stdafx.h\
	.\fwtest.h\
	.\dlgpanel.h\
	.\rotary.h\
	.\updnctl.h\
	.\scopefra.h\
	.\scopescr.h

$(INTDIR)/"scopefra.obj" :  $(SOURCE)  $(DEP_SCOPE) $(INTDIR)\
 $(INTDIR)/stdafx.obj

# End Source File
################################################################################
# Begin Source File

SOURCE=.\scopescr.cpp
DEP_SCOPES=\
	.\stdafx.h\
	.\fwtest.h\
	.\scopescr.h

$(INTDIR)/"scopescr.obj" :  $(SOURCE)  $(DEP_SCOPES) $(INTDIR)\
 $(INTDIR)/stdafx.obj

# End Source File
################################################################################
# Begin Source File

SOURCE=.\dlgpanel.cpp
DEP_DLGPA=\
	.\stdafx.h\
	.\fwtest.h\
	.\DLGTEMPL.H\
	.\dlgpanel.h

$(INTDIR)/"dlgpanel.obj" :  $(SOURCE)  $(DEP_DLGPA) $(INTDIR)\
 $(INTDIR)/stdafx.obj

# End Source File
################################################################################
# Begin Source File

SOURCE=.\rotary.cpp
DEP_ROTAR=\
	.\stdafx.h\
	.\dlgpanel.h\
	.\rotary.h

$(INTDIR)/"rotary.obj" :  $(SOURCE)  $(DEP_ROTAR) $(INTDIR)\
 $(INTDIR)/stdafx.obj

# End Source File
################################################################################
# Begin Source File

SOURCE=.\updnctl.cpp
DEP_UPDNC=\
	.\stdafx.h\
	.\dlgpanel.h\
	.\updnctl.h

$(INTDIR)/"updnctl.obj" :  $(SOURCE)  $(DEP_UPDNC) $(INTDIR)\
 $(INTDIR)/stdafx.obj

# End Source File
################################################################################
# Begin Source File

SOURCE=.\panelfra.cpp
DEP_PANEL=\
	.\stdafx.h\
	.\fwtest.h\
	.\dlgpanel.h\
	.\dlgpanfm.h\
	.\panelfra.h

$(INTDIR)/"panelfra.obj" :  $(SOURCE)  $(DEP_PANEL) $(INTDIR)\
 $(INTDIR)/stdafx.obj

# End Source File
################################################################################
# Begin Source File

SOURCE=.\dlgtempl.cpp
DEP_DLGTE=\
	.\stdafx.h\
	.\DLGTEMPL.H

$(INTDIR)/"dlgtempl.obj" :  $(SOURCE)  $(DEP_DLGTE) $(INTDIR)\
 $(INTDIR)/stdafx.obj

# End Source File
################################################################################
# Begin Source File

SOURCE=.\dlgpanfm.cpp
DEP_DLGPAN=\
	.\stdafx.h\
	.\dlgpanel.h\
	.\dlgpanfm.h

$(INTDIR)/"dlgpanfm.obj" :  $(SOURCE)  $(DEP_DLGPAN) $(INTDIR)\
 $(INTDIR)/stdafx.obj

# End Source File
################################################################################
# Begin Source File

SOURCE=.\fwtest.cpp
DEP_FWTEST=\
	.\stdafx.h\
	.\fwtest.h\
	.\mainfrm.h\
	.\fwtesdoc.h\
	.\fwtesvw.h

$(INTDIR)/"fwtest.obj" :  $(SOURCE)  $(DEP_FWTEST) $(INTDIR)\
 $(INTDIR)/stdafx.obj

# End Source File
# End Group
# End Project
################################################################################
