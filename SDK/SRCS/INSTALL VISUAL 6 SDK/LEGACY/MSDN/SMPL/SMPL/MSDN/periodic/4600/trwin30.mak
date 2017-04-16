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
!MESSAGE NMAKE /f "TRWIN30.MAK" CFG="Win32 Debug"
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

ALL : $(OUTDIR)/TraceWin.exe $(OUTDIR)/TRWIN30.bsc

$(OUTDIR) : 
    if not exist $(OUTDIR)/nul mkdir $(OUTDIR)

# ADD BASE MTL /nologo /D "NDEBUG" /win32
# ADD MTL /nologo /D "NDEBUG" /win32
MTL_PROJ=/nologo /D "NDEBUG" /win32 
# ADD BASE CPP /nologo /MT /W3 /GX /YX /O1 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /FR /c
# ADD CPP /nologo /MD /W3 /GX /O1 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /FR /Yu"STDAFX.H" /c
CPP_PROJ=/nologo /MD /W3 /GX /O1 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D\
 "_AFXDLL" /D "_MBCS" /FR$(INTDIR)/ /Fp$(OUTDIR)/"TRWIN30.pch" /Yu"STDAFX.H"\
 /Fo$(INTDIR)/ /c 
CPP_OBJS=.\WinRel/
# ADD BASE RSC /l 0x409 /d "NDEBUG"
# ADD RSC /l 0x409 /d "NDEBUG" /d "_AFXDLL"
RSC_PROJ=/l 0x409 /fo$(INTDIR)/"TraceWin.res" /d "NDEBUG" /d "_AFXDLL" 
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
BSC32_FLAGS=/nologo /o$(OUTDIR)/"TRWIN30.bsc" 
BSC32_SBRS= \
	$(INTDIR)/StdAfx.sbr \
	$(INTDIR)/MainFrm.sbr \
	$(INTDIR)/App.sbr \
	$(INTDIR)/BufWnd.sbr \
	$(INTDIR)/WinPlace.sbr

$(OUTDIR)/TRWIN30.bsc : $(OUTDIR)  $(BSC32_SBRS)
    $(BSC32) @<<
  $(BSC32_FLAGS) $(BSC32_SBRS)
<<

LINK32=link.exe
# ADD BASE LINK32 oldnames.lib /NOLOGO /STACK:0x10240 /SUBSYSTEM:windows /MACHINE:IX86
# ADD LINK32 oldnames.lib /NOLOGO /STACK:0x10240 /SUBSYSTEM:windows /MACHINE:IX86 /OUT:"WinRel/TraceWin.exe"
LINK32_FLAGS=oldnames.lib /NOLOGO /STACK:0x10240 /SUBSYSTEM:windows\
 /INCREMENTAL:no /PDB:$(OUTDIR)/"TRWIN30.pdb" /MACHINE:IX86\
 /OUT:"WinRel/TraceWin.exe" 
DEF_FILE=
LINK32_OBJS= \
	$(INTDIR)/TraceWin.res \
	$(INTDIR)/StdAfx.obj \
	$(INTDIR)/MainFrm.obj \
	$(INTDIR)/App.obj \
	$(INTDIR)/BufWnd.obj \
	$(INTDIR)/WinPlace.obj

$(OUTDIR)/TraceWin.exe : $(OUTDIR)  $(DEF_FILE) $(LINK32_OBJS)
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

ALL : $(OUTDIR)/TraceWin.exe $(OUTDIR)/TRWIN30.bsc

$(OUTDIR) : 
    if not exist $(OUTDIR)/nul mkdir $(OUTDIR)

# ADD BASE MTL /nologo /D "_DEBUG" /win32
# ADD MTL /nologo /D "_DEBUG" /win32
MTL_PROJ=/nologo /D "_DEBUG" /win32 
# ADD BASE CPP /nologo /MT /W3 /GX /Zi /YX /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /FR /c
# ADD CPP /nologo /MD /W3 /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /FR /Yu"STDAFX.H" /c
CPP_PROJ=/nologo /MD /W3 /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D\
 "_AFXDLL" /D "_MBCS" /FR$(INTDIR)/ /Fp$(OUTDIR)/"TRWIN30.pch" /Yu"STDAFX.H"\
 /Fo$(INTDIR)/ /Fd$(OUTDIR)/"TRWIN30.pdb" /c 
CPP_OBJS=.\WinDebug/
# ADD BASE RSC /l 0x409 /d "_DEBUG"
# ADD RSC /l 0x409 /d "_DEBUG" /d "_AFXDLL"
RSC_PROJ=/l 0x409 /fo$(INTDIR)/"TraceWin.res" /d "_DEBUG" /d "_AFXDLL" 
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
BSC32_FLAGS=/nologo /o$(OUTDIR)/"TRWIN30.bsc" 
BSC32_SBRS= \
	$(INTDIR)/StdAfx.sbr \
	$(INTDIR)/MainFrm.sbr \
	$(INTDIR)/App.sbr \
	$(INTDIR)/BufWnd.sbr \
	$(INTDIR)/WinPlace.sbr

$(OUTDIR)/TRWIN30.bsc : $(OUTDIR)  $(BSC32_SBRS)
    $(BSC32) @<<
  $(BSC32_FLAGS) $(BSC32_SBRS)
<<

LINK32=link.exe
# ADD BASE LINK32 oldnames.lib /NOLOGO /STACK:0x10240 /SUBSYSTEM:windows /DEBUG /MACHINE:IX86
# ADD LINK32 oldnames.lib /NOLOGO /STACK:0x10240 /SUBSYSTEM:windows /DEBUG /MACHINE:IX86 /OUT:"WinDebug/TraceWin.exe"
LINK32_FLAGS=oldnames.lib /NOLOGO /STACK:0x10240 /SUBSYSTEM:windows\
 /INCREMENTAL:yes /PDB:$(OUTDIR)/"TRWIN30.pdb" /DEBUG /MACHINE:IX86\
 /OUT:"WinDebug/TraceWin.exe" 
DEF_FILE=
LINK32_OBJS= \
	$(INTDIR)/TraceWin.res \
	$(INTDIR)/StdAfx.obj \
	$(INTDIR)/MainFrm.obj \
	$(INTDIR)/App.obj \
	$(INTDIR)/BufWnd.obj \
	$(INTDIR)/WinPlace.obj

$(OUTDIR)/TraceWin.exe : $(OUTDIR)  $(DEF_FILE) $(LINK32_OBJS)
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

SOURCE=.\TraceWin.RC
DEP_TRACE=\
	.\RES\TRACEWIN.ICO\
	.\RES\TRACEWIN.RC2

$(INTDIR)/TraceWin.res :  $(SOURCE)  $(DEP_TRACE) $(INTDIR)
   $(RSC) $(RSC_PROJ)  $(SOURCE) 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\StdAfx.cpp
DEP_STDAF=\
	.\StdAfx.h

!IF  "$(CFG)" == "Win32 Release"

# ADD BASE CPP /Yc"STDAFX.H"
# ADD CPP /Yc"STDAFX.H"

$(INTDIR)/StdAfx.obj :  $(SOURCE)  $(DEP_STDAF) $(INTDIR)
   $(CPP) /nologo /MD /W3 /GX /O1 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D\
 "_AFXDLL" /D "_MBCS" /FR$(INTDIR)/ /Fp$(OUTDIR)/"TRWIN30.pch" /Yc"STDAFX.H"\
 /Fo$(INTDIR)/ /c  $(SOURCE) 

!ELSEIF  "$(CFG)" == "Win32 Debug"

# ADD BASE CPP /Yc"STDAFX.H"
# ADD CPP /Yc"STDAFX.H"

$(INTDIR)/StdAfx.obj :  $(SOURCE)  $(DEP_STDAF) $(INTDIR)
   $(CPP) /nologo /MD /W3 /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D\
 "_AFXDLL" /D "_MBCS" /FR$(INTDIR)/ /Fp$(OUTDIR)/"TRWIN30.pch" /Yc"STDAFX.H"\
 /Fo$(INTDIR)/ /Fd$(OUTDIR)/"TRWIN30.pdb" /c  $(SOURCE) 

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\MainFrm.cpp
DEP_MAINF=\
	.\StdAfx.h\
	.\App.h\
	.\MainFrm.h\
	.\TraceWin.h\
	.\BufWnd.h

$(INTDIR)/MainFrm.obj :  $(SOURCE)  $(DEP_MAINF) $(INTDIR) $(INTDIR)/StdAfx.obj

# End Source File
################################################################################
# Begin Source File

SOURCE=.\App.cpp
DEP_APP_C=\
	.\StdAfx.h\
	.\App.h\
	.\MainFrm.h\
	.\BufWnd.h

$(INTDIR)/App.obj :  $(SOURCE)  $(DEP_APP_C) $(INTDIR) $(INTDIR)/StdAfx.obj

# End Source File
################################################################################
# Begin Source File

SOURCE=.\BufWnd.cpp
DEP_BUFWN=\
	.\StdAfx.h\
	.\BufWnd.h

$(INTDIR)/BufWnd.obj :  $(SOURCE)  $(DEP_BUFWN) $(INTDIR) $(INTDIR)/StdAfx.obj

# End Source File
################################################################################
# Begin Source File

SOURCE=.\WinPlace.cpp
DEP_WINPL=\
	.\StdAfx.h\
	.\WinPlace.h

$(INTDIR)/WinPlace.obj :  $(SOURCE)  $(DEP_WINPL) $(INTDIR)\
 $(INTDIR)/StdAfx.obj

# End Source File
# End Group
# End Project
################################################################################
