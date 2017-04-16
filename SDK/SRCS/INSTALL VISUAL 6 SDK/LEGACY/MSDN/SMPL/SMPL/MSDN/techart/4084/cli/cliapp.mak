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
!MESSAGE NMAKE /f "cliapp.mak" CFG="Win32 Debug"
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

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "WinRel"
# PROP BASE Intermediate_Dir "WinRel"
# PROP Use_MFC 2
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "WinRel"
# PROP Intermediate_Dir "WinRel"
OUTDIR=.\WinRel
INTDIR=.\WinRel

ALL : $(OUTDIR)/cliapp.exe $(OUTDIR)/cliapp.bsc

$(OUTDIR) : 
    if not exist $(OUTDIR)/nul mkdir $(OUTDIR)

# ADD BASE MTL /nologo /D "NDEBUG" /win32
# ADD MTL /nologo /D "NDEBUG" /win32
MTL_PROJ=/nologo /D "NDEBUG" /win32 
# ADD BASE CPP /nologo /W3 /GX /YX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /FR /c
# ADD CPP /nologo /MD /W3 /GX /YX /O2 /I ".\\" /I "..\common" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /FR /c
CPP_PROJ=/nologo /MD /W3 /GX /YX /O2 /I ".\\" /I "..\common" /D "WIN32" /D\
 "NDEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /FR$(INTDIR)/\
 /Fp$(OUTDIR)/"cliapp.pch" /Fo$(INTDIR)/ /c 
CPP_OBJS=.\WinRel/
# ADD BASE RSC /l 0x409 /d "NDEBUG"
# ADD RSC /l 0x409 /d "NDEBUG" /d "_AFXDLL"
RSC_PROJ=/l 0x409 /fo$(INTDIR)/"cliapp.res" /d "NDEBUG" /d "_AFXDLL" 
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
BSC32_FLAGS=/nologo /o$(OUTDIR)/"cliapp.bsc" 
BSC32_SBRS= \
	$(INTDIR)/stdafx.sbr \
	$(INTDIR)/dbdialog.sbr \
	$(INTDIR)/cfilemap.sbr \
	$(INTDIR)/cliapp.sbr \
	$(INTDIR)/PROTOCOL.SBR \
	$(INTDIR)/mainfrm.sbr \
	$(INTDIR)/BROWSEDI.SBR \
	$(INTDIR)/cmutex.sbr \
	$(INTDIR)/easyview.sbr \
	$(INTDIR)/cliview.sbr \
	$(INTDIR)/COMCLASS.SBR \
	$(INTDIR)/clidoc.sbr \
	$(INTDIR)/dbcode.sbr \
	$(INTDIR)/NPIPE.SBR

$(OUTDIR)/cliapp.bsc : $(OUTDIR)  $(BSC32_SBRS)
    $(BSC32) @<<
  $(BSC32_FLAGS) $(BSC32_SBRS)
<<

LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib /NOLOGO /SUBSYSTEM:windows /MACHINE:I386
# ADD LINK32 /NOLOGO /SUBSYSTEM:windows /MACHINE:I386
LINK32_FLAGS=/NOLOGO /SUBSYSTEM:windows /INCREMENTAL:no\
 /PDB:$(OUTDIR)/"cliapp.pdb" /MACHINE:I386 /OUT:$(OUTDIR)/"cliapp.exe" 
DEF_FILE=
LINK32_OBJS= \
	$(INTDIR)/stdafx.obj \
	$(INTDIR)/dbdialog.obj \
	$(INTDIR)/cfilemap.obj \
	$(INTDIR)/cliapp.res \
	$(INTDIR)/cliapp.obj \
	$(INTDIR)/PROTOCOL.OBJ \
	$(INTDIR)/mainfrm.obj \
	$(INTDIR)/BROWSEDI.OBJ \
	$(INTDIR)/cmutex.obj \
	$(INTDIR)/easyview.obj \
	$(INTDIR)/cliview.obj \
	$(INTDIR)/COMCLASS.OBJ \
	$(INTDIR)/clidoc.obj \
	$(INTDIR)/dbcode.obj \
	$(INTDIR)/NPIPE.OBJ

$(OUTDIR)/cliapp.exe : $(OUTDIR)  $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ELSEIF  "$(CFG)" == "Win32 Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "WinDebug"
# PROP BASE Intermediate_Dir "WinDebug"
# PROP Use_MFC 2
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "WinDebug"
# PROP Intermediate_Dir "WinDebug"
OUTDIR=.\WinDebug
INTDIR=.\WinDebug

ALL : $(OUTDIR)/cliapp.exe $(OUTDIR)/cliapp.bsc

$(OUTDIR) : 
    if not exist $(OUTDIR)/nul mkdir $(OUTDIR)

# ADD BASE MTL /nologo /D "_DEBUG" /win32
# ADD MTL /nologo /D "_DEBUG" /win32
MTL_PROJ=/nologo /D "_DEBUG" /win32 
# ADD BASE CPP /nologo /W3 /GX /Zi /YX /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /FR /c
# ADD CPP /nologo /MD /W3 /GX /Zi /YX /Od /I ".\\" /I "..\common" /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /FR /c
CPP_PROJ=/nologo /MD /W3 /GX /Zi /YX /Od /I ".\\" /I "..\common" /D "WIN32" /D\
 "_DEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /FR$(INTDIR)/\
 /Fp$(OUTDIR)/"cliapp.pch" /Fo$(INTDIR)/ /Fd$(OUTDIR)/"cliapp.pdb" /c 
CPP_OBJS=.\WinDebug/
# ADD BASE RSC /l 0x409 /d "_DEBUG"
# ADD RSC /l 0x409 /d "_DEBUG" /d "_AFXDLL"
RSC_PROJ=/l 0x409 /fo$(INTDIR)/"cliapp.res" /d "_DEBUG" /d "_AFXDLL" 
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
BSC32_FLAGS=/nologo /o$(OUTDIR)/"cliapp.bsc" 
BSC32_SBRS= \
	$(INTDIR)/stdafx.sbr \
	$(INTDIR)/dbdialog.sbr \
	$(INTDIR)/cfilemap.sbr \
	$(INTDIR)/cliapp.sbr \
	$(INTDIR)/PROTOCOL.SBR \
	$(INTDIR)/mainfrm.sbr \
	$(INTDIR)/BROWSEDI.SBR \
	$(INTDIR)/cmutex.sbr \
	$(INTDIR)/easyview.sbr \
	$(INTDIR)/cliview.sbr \
	$(INTDIR)/COMCLASS.SBR \
	$(INTDIR)/clidoc.sbr \
	$(INTDIR)/dbcode.sbr \
	$(INTDIR)/NPIPE.SBR

$(OUTDIR)/cliapp.bsc : $(OUTDIR)  $(BSC32_SBRS)
    $(BSC32) @<<
  $(BSC32_FLAGS) $(BSC32_SBRS)
<<

LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib /NOLOGO /SUBSYSTEM:windows /DEBUG /MACHINE:I386
# ADD LINK32 /NOLOGO /SUBSYSTEM:windows /DEBUG /MACHINE:I386
LINK32_FLAGS=/NOLOGO /SUBSYSTEM:windows /INCREMENTAL:yes\
 /PDB:$(OUTDIR)/"cliapp.pdb" /DEBUG /MACHINE:I386 /OUT:$(OUTDIR)/"cliapp.exe" 
DEF_FILE=
LINK32_OBJS= \
	$(INTDIR)/stdafx.obj \
	$(INTDIR)/dbdialog.obj \
	$(INTDIR)/cfilemap.obj \
	$(INTDIR)/cliapp.res \
	$(INTDIR)/cliapp.obj \
	$(INTDIR)/PROTOCOL.OBJ \
	$(INTDIR)/mainfrm.obj \
	$(INTDIR)/BROWSEDI.OBJ \
	$(INTDIR)/cmutex.obj \
	$(INTDIR)/easyview.obj \
	$(INTDIR)/cliview.obj \
	$(INTDIR)/COMCLASS.OBJ \
	$(INTDIR)/clidoc.obj \
	$(INTDIR)/dbcode.obj \
	$(INTDIR)/NPIPE.OBJ

$(OUTDIR)/cliapp.exe : $(OUTDIR)  $(DEF_FILE) $(LINK32_OBJS)
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

SOURCE=.\stdafx.cpp
DEP_STDAF=\
	.\stdafx.h

$(INTDIR)/stdafx.obj :  $(SOURCE)  $(DEP_STDAF) $(INTDIR)

# End Source File
################################################################################
# Begin Source File

SOURCE=\projects\netstuff\security\common\dbdialog.cpp
DEP_DBDIA=\
	.\stdafx.h\
	\projects\netstuff\security\common\dbdialog.h

$(INTDIR)/dbdialog.obj :  $(SOURCE)  $(DEP_DBDIA) $(INTDIR)
   $(CPP) $(CPP_PROJ)  $(SOURCE) 

# End Source File
################################################################################
# Begin Source File

SOURCE=\projects\netstuff\security\common\cfilemap.cpp
DEP_CFILE=\
	.\stdafx.h\
	\projects\netstuff\security\common\cfilemap.h

$(INTDIR)/cfilemap.obj :  $(SOURCE)  $(DEP_CFILE) $(INTDIR)
   $(CPP) $(CPP_PROJ)  $(SOURCE) 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\cliapp.rc
DEP_CLIAP=\
	.\res\npseccli.ico\
	.\res\toolbar.bmp\
	.\res\npseccli.rc2

$(INTDIR)/cliapp.res :  $(SOURCE)  $(DEP_CLIAP) $(INTDIR)
   $(RSC) $(RSC_PROJ)  $(SOURCE) 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\cliapp.cpp
DEP_CLIAPP=\
	.\stdafx.h\
	\projects\netstuff\security\common\common.h\
	.\cliapp.h\
	.\mainfrm.h\
	\projects\netstuff\security\common\easyview.h\
	.\clidoc.h\
	.\cliview.h\
	.\BROWSEDI.H

$(INTDIR)/cliapp.obj :  $(SOURCE)  $(DEP_CLIAPP) $(INTDIR)

# End Source File
################################################################################
# Begin Source File

SOURCE=\projects\netstuff\security\common\PROTOCOL.CPP
DEP_PROTO=\
	.\stdafx.h\
	\projects\netstuff\security\common\common.h\
	\projects\netstuff\security\common\comclass.h\
	\projects\netstuff\security\common\dbcode.h\
	\projects\netstuff\security\common\protocol.h

$(INTDIR)/PROTOCOL.OBJ :  $(SOURCE)  $(DEP_PROTO) $(INTDIR)
   $(CPP) $(CPP_PROJ)  $(SOURCE) 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\mainfrm.cpp
DEP_MAINF=\
	.\stdafx.h\
	.\cliapp.h\
	.\mainfrm.h

$(INTDIR)/mainfrm.obj :  $(SOURCE)  $(DEP_MAINF) $(INTDIR)

# End Source File
################################################################################
# Begin Source File

SOURCE=.\BROWSEDI.CPP
DEP_BROWS=\
	.\stdafx.h\
	.\cliapp.h\
	.\BROWSEDI.H

$(INTDIR)/BROWSEDI.OBJ :  $(SOURCE)  $(DEP_BROWS) $(INTDIR)

# End Source File
################################################################################
# Begin Source File

SOURCE=\projects\netstuff\security\common\cmutex.cpp
DEP_CMUTE=\
	.\stdafx.h\
	\projects\netstuff\security\common\cmutex.h

$(INTDIR)/cmutex.obj :  $(SOURCE)  $(DEP_CMUTE) $(INTDIR)
   $(CPP) $(CPP_PROJ)  $(SOURCE) 

# End Source File
################################################################################
# Begin Source File

SOURCE=\projects\netstuff\security\common\easyview.cpp
DEP_EASYV=\
	.\stdafx.h\
	\projects\netstuff\security\common\easyview.h

$(INTDIR)/easyview.obj :  $(SOURCE)  $(DEP_EASYV) $(INTDIR)
   $(CPP) $(CPP_PROJ)  $(SOURCE) 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\cliview.cpp
DEP_CLIVI=\
	.\stdafx.h\
	\projects\netstuff\security\common\common.h\
	.\cliapp.h\
	\projects\netstuff\security\common\protocol.h\
	\projects\netstuff\security\common\easyview.h\
	.\clidoc.h\
	.\cliview.h\
	\projects\netstuff\security\common\comclass.h\
	\projects\netstuff\security\common\npipe.h\
	\projects\netstuff\security\common\cmutex.h\
	\projects\netstuff\security\common\cfilemap.h\
	\projects\netstuff\security\common\dbcode.h\
	.\BROWSEDI.H\
	\projects\netstuff\security\common\dbdialog.h

$(INTDIR)/cliview.obj :  $(SOURCE)  $(DEP_CLIVI) $(INTDIR)

# End Source File
################################################################################
# Begin Source File

SOURCE=\projects\netstuff\security\common\COMCLASS.CPP
DEP_COMCL=\
	.\stdafx.h\
	\projects\netstuff\security\common\comclass.h

$(INTDIR)/COMCLASS.OBJ :  $(SOURCE)  $(DEP_COMCL) $(INTDIR)
   $(CPP) $(CPP_PROJ)  $(SOURCE) 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\clidoc.cpp
DEP_CLIDO=\
	.\stdafx.h\
	.\cliapp.h\
	.\clidoc.h

$(INTDIR)/clidoc.obj :  $(SOURCE)  $(DEP_CLIDO) $(INTDIR)

# End Source File
################################################################################
# Begin Source File

SOURCE=\projects\netstuff\security\common\dbcode.cpp
DEP_DBCOD=\
	.\stdafx.h\
	\projects\netstuff\security\common\comclass.h\
	\projects\netstuff\security\common\cmutex.h\
	\projects\netstuff\security\common\dbcode.h\
	\projects\netstuff\security\common\npipe.h

$(INTDIR)/dbcode.obj :  $(SOURCE)  $(DEP_DBCOD) $(INTDIR)
   $(CPP) $(CPP_PROJ)  $(SOURCE) 

# End Source File
################################################################################
# Begin Source File

SOURCE=\projects\netstuff\security\common\NPIPE.CPP
DEP_NPIPE=\
	.\stdafx.h\
	\projects\netstuff\security\common\comclass.h\
	\projects\netstuff\security\common\npipe.h

$(INTDIR)/NPIPE.OBJ :  $(SOURCE)  $(DEP_NPIPE) $(INTDIR)
   $(CPP) $(CPP_PROJ)  $(SOURCE) 

# End Source File
# End Group
# End Project
################################################################################
