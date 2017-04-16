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
!MESSAGE NMAKE /f "TRACEWIN.MAK" CFG="Win32 Debug"
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
# PROP Target_Last_Scanned "Win32 Release"
MTL=MkTypLib.exe
CPP=cl.exe
RSC=rc.exe

!IF  "$(CFG)" == "Win32 Release"

# PROP BASE Use_MFC 1
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "WinRel"
# PROP BASE Intermediate_Dir "WinRel"
# PROP Use_MFC 2
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "WinRel"
# PROP Intermediate_Dir "WinRel"
OUTDIR=.\WinRel
INTDIR=.\WinRel

ALL : .\WinRel\TRACEWIN.exe .\WinRel\TRACEWIN.bsc

$(OUTDIR) : 
    if not exist $(OUTDIR)/nul mkdir $(OUTDIR)

# ADD BASE MTL /nologo /D "NDEBUG" /win32
# ADD MTL /nologo /D "NDEBUG" /win32
MTL_PROJ=/nologo /D "NDEBUG" /win32 
# ADD BASE CPP /nologo /MT /W3 /GX /YX /O1 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /FR /c
# ADD CPP /nologo /MD /W3 /GX /O1 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /FR /Yu"STDAFX.H" /c
CPP_PROJ=/nologo /MD /W3 /GX /O1 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D\
 "_AFXDLL" /D "_MBCS" /FR$(INTDIR)/ /Fp$(OUTDIR)/"TRACEWIN.pch" /Yu"STDAFX.H"\
 /Fo$(INTDIR)/ /c 
CPP_OBJS=.\WinRel/
# ADD BASE RSC /l 0x409 /d "NDEBUG"
# ADD RSC /l 0x409 /d "NDEBUG" /d "_AFXDLL"
RSC_PROJ=/l 0x409 /fo$(INTDIR)/"TRACEWIN.res" /d "NDEBUG" /d "_AFXDLL" 
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
BSC32_FLAGS=/nologo /o$(OUTDIR)/"TRACEWIN.bsc" 
BSC32_SBRS= \
	.\WinRel\STDAFX.SBR \
	.\WinRel\mainfrm.sbr \
	.\WinRel\APP.SBR \
	.\WinRel\bufwnd.sbr

.\WinRel\TRACEWIN.bsc : $(OUTDIR)  $(BSC32_SBRS)
    $(BSC32) @<<
  $(BSC32_FLAGS) $(BSC32_SBRS)
<<

LINK32=link.exe
# ADD BASE LINK32 oldnames.lib /NOLOGO /STACK:0x10240 /SUBSYSTEM:windows /MACHINE:IX86
# ADD LINK32 oldnames.lib /NOLOGO /STACK:0x10240 /SUBSYSTEM:windows /MACHINE:IX86
LINK32_FLAGS=oldnames.lib /NOLOGO /STACK:0x10240 /SUBSYSTEM:windows\
 /INCREMENTAL:no /PDB:$(OUTDIR)/"TRACEWIN.pdb" /MACHINE:IX86\
 /OUT:$(OUTDIR)/"TRACEWIN.exe" 
DEF_FILE=
LINK32_OBJS= \
	.\WinRel\TRACEWIN.res \
	.\WinRel\STDAFX.OBJ \
	.\WinRel\mainfrm.obj \
	.\WinRel\APP.OBJ \
	.\WinRel\bufwnd.obj

.\WinRel\TRACEWIN.exe : $(OUTDIR)  $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ELSEIF  "$(CFG)" == "Win32 Debug"

# PROP BASE Use_MFC 1
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "WinDebug"
# PROP BASE Intermediate_Dir "WinDebug"
# PROP Use_MFC 2
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "WinDebug"
# PROP Intermediate_Dir "WinDebug"
OUTDIR=.\WinDebug
INTDIR=.\WinDebug

ALL : .\WinDebug\TRACEWIN.exe .\WinDebug\TRACEWIN.bsc

$(OUTDIR) : 
    if not exist $(OUTDIR)/nul mkdir $(OUTDIR)

# ADD BASE MTL /nologo /D "_DEBUG" /win32
# ADD MTL /nologo /D "_DEBUG" /win32
MTL_PROJ=/nologo /D "_DEBUG" /win32 
# ADD BASE CPP /nologo /MT /W3 /GX /Zi /YX /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /FR /c
# ADD CPP /nologo /MD /W3 /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /FR /Yu"STDAFX.H" /c
CPP_PROJ=/nologo /MD /W3 /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D\
 "_AFXDLL" /D "_MBCS" /FR$(INTDIR)/ /Fp$(OUTDIR)/"TRACEWIN.pch" /Yu"STDAFX.H"\
 /Fo$(INTDIR)/ /Fd$(OUTDIR)/"TRACEWIN.pdb" /c 
CPP_OBJS=.\WinDebug/
# ADD BASE RSC /l 0x409 /d "_DEBUG"
# ADD RSC /l 0x409 /d "_DEBUG" /d "_AFXDLL"
RSC_PROJ=/l 0x409 /fo$(INTDIR)/"TRACEWIN.res" /d "_DEBUG" /d "_AFXDLL" 
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
BSC32_FLAGS=/nologo /o$(OUTDIR)/"TRACEWIN.bsc" 
BSC32_SBRS= \
	.\WinDebug\STDAFX.SBR \
	.\WinDebug\mainfrm.sbr \
	.\WinDebug\APP.SBR \
	.\WinDebug\bufwnd.sbr

.\WinDebug\TRACEWIN.bsc : $(OUTDIR)  $(BSC32_SBRS)
    $(BSC32) @<<
  $(BSC32_FLAGS) $(BSC32_SBRS)
<<

LINK32=link.exe
# ADD BASE LINK32 oldnames.lib /NOLOGO /STACK:0x10240 /SUBSYSTEM:windows /DEBUG /MACHINE:IX86
# ADD LINK32 oldnames.lib /NOLOGO /STACK:0x10240 /SUBSYSTEM:windows /DEBUG /MACHINE:IX86
LINK32_FLAGS=oldnames.lib /NOLOGO /STACK:0x10240 /SUBSYSTEM:windows\
 /INCREMENTAL:yes /PDB:$(OUTDIR)/"TRACEWIN.pdb" /DEBUG /MACHINE:IX86\
 /OUT:$(OUTDIR)/"TRACEWIN.exe" 
DEF_FILE=
LINK32_OBJS= \
	.\WinDebug\TRACEWIN.res \
	.\WinDebug\STDAFX.OBJ \
	.\WinDebug\mainfrm.obj \
	.\WinDebug\APP.OBJ \
	.\WinDebug\bufwnd.obj

.\WinDebug\TRACEWIN.exe : $(OUTDIR)  $(DEF_FILE) $(LINK32_OBJS)
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

SOURCE=.\TRACEWIN.RC
DEP_TRACE=\
	.\RES\TRACEWIN.ICO\
	.\RES\TRACEWIN.RC2

!IF  "$(CFG)" == "Win32 Release"

.\WinRel\TRACEWIN.res :  $(SOURCE)  $(DEP_TRACE) $(INTDIR)
   $(RSC) $(RSC_PROJ)  $(SOURCE) 

!ELSEIF  "$(CFG)" == "Win32 Debug"

.\WinDebug\TRACEWIN.res :  $(SOURCE)  $(DEP_TRACE) $(INTDIR)
   $(RSC) $(RSC_PROJ)  $(SOURCE) 

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\STDAFX.CPP
DEP_STDAF=\
	.\STDAFX.H

!IF  "$(CFG)" == "Win32 Release"

# ADD BASE CPP /Yc"STDAFX.H"
# ADD CPP /Yc"STDAFX.H"

.\WinRel\STDAFX.OBJ :  $(SOURCE)  $(DEP_STDAF) $(INTDIR)
   $(CPP) /nologo /MD /W3 /GX /O1 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D\
 "_AFXDLL" /D "_MBCS" /FR$(INTDIR)/ /Fp$(OUTDIR)/"TRACEWIN.pch" /Yc"STDAFX.H"\
 /Fo$(INTDIR)/ /c  $(SOURCE) 

!ELSEIF  "$(CFG)" == "Win32 Debug"

# ADD BASE CPP /Yc"STDAFX.H"
# ADD CPP /Yc"STDAFX.H"

.\WinDebug\STDAFX.OBJ :  $(SOURCE)  $(DEP_STDAF) $(INTDIR)
   $(CPP) /nologo /MD /W3 /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D\
 "_AFXDLL" /D "_MBCS" /FR$(INTDIR)/ /Fp$(OUTDIR)/"TRACEWIN.pch" /Yc"STDAFX.H"\
 /Fo$(INTDIR)/ /Fd$(OUTDIR)/"TRACEWIN.pdb" /c  $(SOURCE) 

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\mainfrm.cpp
DEP_MAINF=\
	.\STDAFX.H\
	.\APP.H\
	.\mainfrm.h\
	.\TRACEWIN.H\
	.\bufwnd.h

!IF  "$(CFG)" == "Win32 Release"

.\WinRel\mainfrm.obj :  $(SOURCE)  $(DEP_MAINF) $(INTDIR) .\WinRel\STDAFX.OBJ

!ELSEIF  "$(CFG)" == "Win32 Debug"

.\WinDebug\mainfrm.obj :  $(SOURCE)  $(DEP_MAINF) $(INTDIR)\
 .\WinDebug\STDAFX.OBJ

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\APP.CPP
DEP_APP_C=\
	.\STDAFX.H\
	.\APP.H\
	.\mainfrm.h\
	.\bufwnd.h

!IF  "$(CFG)" == "Win32 Release"

.\WinRel\APP.OBJ :  $(SOURCE)  $(DEP_APP_C) $(INTDIR) .\WinRel\STDAFX.OBJ

!ELSEIF  "$(CFG)" == "Win32 Debug"

.\WinDebug\APP.OBJ :  $(SOURCE)  $(DEP_APP_C) $(INTDIR) .\WinDebug\STDAFX.OBJ

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\bufwnd.cpp
DEP_BUFWN=\
	.\STDAFX.H\
	.\bufwnd.h

!IF  "$(CFG)" == "Win32 Release"

.\WinRel\bufwnd.obj :  $(SOURCE)  $(DEP_BUFWN) $(INTDIR) .\WinRel\STDAFX.OBJ

!ELSEIF  "$(CFG)" == "Win32 Debug"

.\WinDebug\bufwnd.obj :  $(SOURCE)  $(DEP_BUFWN) $(INTDIR)\
 .\WinDebug\STDAFX.OBJ

!ENDIF 

# End Source File
# End Group
# End Project
################################################################################
