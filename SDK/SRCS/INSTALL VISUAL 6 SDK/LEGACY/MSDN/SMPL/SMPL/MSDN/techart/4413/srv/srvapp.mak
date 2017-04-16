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
!MESSAGE NMAKE /f "srvapp.mak" CFG="Win32 Debug"
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

ALL : $(OUTDIR)/srvapp.exe $(OUTDIR)/srvapp.bsc

$(OUTDIR) : 
    if not exist $(OUTDIR)/nul mkdir $(OUTDIR)

# ADD BASE MTL /nologo /D "NDEBUG" /win32
# ADD MTL /nologo /D "NDEBUG" /win32
MTL_PROJ=/nologo /D "NDEBUG" /win32 
# ADD BASE CPP /nologo /W3 /GX /YX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /FR /c
# ADD CPP /nologo /MD /W3 /GX /YX /O2 /I ".\secstuff" /I ".\\" /I "..\common" /D "NDEBUG" /D "WIN32" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /D "SERVER" /D "SECURITY" /FR /c
CPP_PROJ=/nologo /MD /W3 /GX /YX /O2 /I ".\secstuff" /I ".\\" /I "..\common" /D\
 "NDEBUG" /D "WIN32" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /D "SERVER" /D\
 "SECURITY" /FR$(INTDIR)/ /Fp$(OUTDIR)/"srvapp.pch" /Fo$(INTDIR)/ /c 
CPP_OBJS=.\WinRel/
# ADD BASE RSC /l 0x409 /d "NDEBUG"
# ADD RSC /l 0x409 /d "NDEBUG" /d "_AFXDLL"
RSC_PROJ=/l 0x409 /fo$(INTDIR)/"srvapp.res" /d "NDEBUG" /d "_AFXDLL" 
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
BSC32_FLAGS=/nologo /o$(OUTDIR)/"srvapp.bsc" 
BSC32_SBRS= \
	$(INTDIR)/sec.sbr \
	$(INTDIR)/srvdoc.sbr \
	$(INTDIR)/dbdialog.sbr \
	$(INTDIR)/cfilemap.sbr \
	$(INTDIR)/mainfrm.sbr \
	$(INTDIR)/secdialo.sbr \
	$(INTDIR)/PROTOCOL.SBR \
	$(INTDIR)/examstff.sbr \
	$(INTDIR)/srvapp.sbr \
	$(INTDIR)/cmutex.sbr \
	$(INTDIR)/easyview.sbr \
	$(INTDIR)/COMCLASS.SBR \
	$(INTDIR)/dbcode.sbr \
	$(INTDIR)/srvview.sbr \
	$(INTDIR)/NPIPE.SBR \
	$(INTDIR)/stdafx.sbr

$(OUTDIR)/srvapp.bsc : $(OUTDIR)  $(BSC32_SBRS)
    $(BSC32) @<<
  $(BSC32_FLAGS) $(BSC32_SBRS)
<<

LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib /NOLOGO /SUBSYSTEM:windows /MACHINE:I386
# ADD LINK32 /NOLOGO /SUBSYSTEM:windows /MACHINE:I386
LINK32_FLAGS=/NOLOGO /SUBSYSTEM:windows /INCREMENTAL:no\
 /PDB:$(OUTDIR)/"srvapp.pdb" /MACHINE:I386 /OUT:$(OUTDIR)/"srvapp.exe" 
DEF_FILE=
LINK32_OBJS= \
	$(INTDIR)/sec.obj \
	$(INTDIR)/srvdoc.obj \
	$(INTDIR)/srvapp.res \
	$(INTDIR)/dbdialog.obj \
	$(INTDIR)/cfilemap.obj \
	$(INTDIR)/mainfrm.obj \
	$(INTDIR)/secdialo.obj \
	$(INTDIR)/PROTOCOL.OBJ \
	$(INTDIR)/examstff.obj \
	$(INTDIR)/srvapp.obj \
	$(INTDIR)/cmutex.obj \
	$(INTDIR)/easyview.obj \
	$(INTDIR)/COMCLASS.OBJ \
	$(INTDIR)/dbcode.obj \
	$(INTDIR)/srvview.obj \
	$(INTDIR)/NPIPE.OBJ \
	$(INTDIR)/stdafx.obj

$(OUTDIR)/srvapp.exe : $(OUTDIR)  $(DEF_FILE) $(LINK32_OBJS)
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

ALL : $(OUTDIR)/srvapp.exe $(OUTDIR)/srvapp.bsc

$(OUTDIR) : 
    if not exist $(OUTDIR)/nul mkdir $(OUTDIR)

# ADD BASE MTL /nologo /D "_DEBUG" /win32
# ADD MTL /nologo /D "_DEBUG" /win32
MTL_PROJ=/nologo /D "_DEBUG" /win32 
# ADD BASE CPP /nologo /W3 /GX /Zi /YX /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /FR /c
# ADD CPP /nologo /MD /W3 /GX /Zi /YX /Od /I ".\secstuff" /I ".\\" /I "..\common" /D "_DEBUG" /D "WIN32" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /D "SERVER" /D "SECURITY" /FR /c
CPP_PROJ=/nologo /MD /W3 /GX /Zi /YX /Od /I ".\secstuff" /I ".\\" /I\
 "..\common" /D "_DEBUG" /D "WIN32" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /D\
 "SERVER" /D "SECURITY" /FR$(INTDIR)/ /Fp$(OUTDIR)/"srvapp.pch" /Fo$(INTDIR)/\
 /Fd$(OUTDIR)/"srvapp.pdb" /c 
CPP_OBJS=.\WinDebug/
# ADD BASE RSC /l 0x409 /d "_DEBUG"
# ADD RSC /l 0x409 /d "_DEBUG" /d "_AFXDLL"
RSC_PROJ=/l 0x409 /fo$(INTDIR)/"srvapp.res" /d "_DEBUG" /d "_AFXDLL" 
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
BSC32_FLAGS=/nologo /o$(OUTDIR)/"srvapp.bsc" 
BSC32_SBRS= \
	$(INTDIR)/sec.sbr \
	$(INTDIR)/srvdoc.sbr \
	$(INTDIR)/dbdialog.sbr \
	$(INTDIR)/cfilemap.sbr \
	$(INTDIR)/mainfrm.sbr \
	$(INTDIR)/secdialo.sbr \
	$(INTDIR)/PROTOCOL.SBR \
	$(INTDIR)/examstff.sbr \
	$(INTDIR)/srvapp.sbr \
	$(INTDIR)/cmutex.sbr \
	$(INTDIR)/easyview.sbr \
	$(INTDIR)/COMCLASS.SBR \
	$(INTDIR)/dbcode.sbr \
	$(INTDIR)/srvview.sbr \
	$(INTDIR)/NPIPE.SBR \
	$(INTDIR)/stdafx.sbr

$(OUTDIR)/srvapp.bsc : $(OUTDIR)  $(BSC32_SBRS)
    $(BSC32) @<<
  $(BSC32_FLAGS) $(BSC32_SBRS)
<<

LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib /NOLOGO /SUBSYSTEM:windows /DEBUG /MACHINE:I386
# ADD LINK32 /NOLOGO /SUBSYSTEM:windows /DEBUG /MACHINE:I386
LINK32_FLAGS=/NOLOGO /SUBSYSTEM:windows /INCREMENTAL:yes\
 /PDB:$(OUTDIR)/"srvapp.pdb" /DEBUG /MACHINE:I386 /OUT:$(OUTDIR)/"srvapp.exe" 
DEF_FILE=
LINK32_OBJS= \
	$(INTDIR)/sec.obj \
	$(INTDIR)/srvdoc.obj \
	$(INTDIR)/srvapp.res \
	$(INTDIR)/dbdialog.obj \
	$(INTDIR)/cfilemap.obj \
	$(INTDIR)/mainfrm.obj \
	$(INTDIR)/secdialo.obj \
	$(INTDIR)/PROTOCOL.OBJ \
	$(INTDIR)/examstff.obj \
	$(INTDIR)/srvapp.obj \
	$(INTDIR)/cmutex.obj \
	$(INTDIR)/easyview.obj \
	$(INTDIR)/COMCLASS.OBJ \
	$(INTDIR)/dbcode.obj \
	$(INTDIR)/srvview.obj \
	$(INTDIR)/NPIPE.OBJ \
	$(INTDIR)/stdafx.obj

$(OUTDIR)/srvapp.exe : $(OUTDIR)  $(DEF_FILE) $(LINK32_OBJS)
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

SOURCE=.\secstuff\sec.cpp
DEP_SEC_C=\
	.\stdafx.h\
	.\secstuff\sec.h\
	.\secstuff\secdialo.h\
	.\secstuff\examstff.h

$(INTDIR)/sec.obj :  $(SOURCE)  $(DEP_SEC_C) $(INTDIR)
   $(CPP) $(CPP_PROJ)  $(SOURCE) 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\srvdoc.cpp
DEP_SRVDO=\
	.\stdafx.h\
	.\srvapp.h\
	.\srvdoc.h

$(INTDIR)/srvdoc.obj :  $(SOURCE)  $(DEP_SRVDO) $(INTDIR)

# End Source File
################################################################################
# Begin Source File

SOURCE=.\srvapp.rc
DEP_SRVAP=\
	.\res\npscesrv.ico\
	.\res\toolbar.bmp\
	.\res\npscesrv.rc2

$(INTDIR)/srvapp.res :  $(SOURCE)  $(DEP_SRVAP) $(INTDIR)
   $(RSC) $(RSC_PROJ)  $(SOURCE) 

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
	.\secstuff\sec.h\
	\projects\netstuff\security\common\cfilemap.h

$(INTDIR)/cfilemap.obj :  $(SOURCE)  $(DEP_CFILE) $(INTDIR)
   $(CPP) $(CPP_PROJ)  $(SOURCE) 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\mainfrm.cpp
DEP_MAINF=\
	.\stdafx.h\
	.\srvapp.h\
	.\mainfrm.h

$(INTDIR)/mainfrm.obj :  $(SOURCE)  $(DEP_MAINF) $(INTDIR)

# End Source File
################################################################################
# Begin Source File

SOURCE=.\secstuff\secdialo.cpp
DEP_SECDI=\
	.\stdafx.h\
	.\secstuff\secdialo.h

$(INTDIR)/secdialo.obj :  $(SOURCE)  $(DEP_SECDI) $(INTDIR)
   $(CPP) $(CPP_PROJ)  $(SOURCE) 

# End Source File
################################################################################
# Begin Source File

SOURCE=\projects\netstuff\security\common\PROTOCOL.CPP
DEP_PROTO=\
	.\stdafx.h\
	\projects\netstuff\security\common\common.h\
	\projects\netstuff\security\common\comclass.h\
	.\secstuff\sec.h\
	\projects\netstuff\security\common\dbcode.h\
	\projects\netstuff\security\common\protocol.h

$(INTDIR)/PROTOCOL.OBJ :  $(SOURCE)  $(DEP_PROTO) $(INTDIR)
   $(CPP) $(CPP_PROJ)  $(SOURCE) 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\secstuff\examstff.cpp
DEP_EXAMS=\
	.\stdafx.h\
	.\secstuff\examstff.h

$(INTDIR)/examstff.obj :  $(SOURCE)  $(DEP_EXAMS) $(INTDIR)
   $(CPP) $(CPP_PROJ)  $(SOURCE) 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\srvapp.cpp
DEP_SRVAPP=\
	.\stdafx.h\
	\projects\netstuff\security\common\common.h\
	.\srvapp.h\
	.\mainfrm.h\
	.\srvdoc.h\
	\projects\netstuff\security\common\easyview.h\
	.\srvview.h\
	.\secstuff\examstff.h\
	.\secstuff\sec.h

$(INTDIR)/srvapp.obj :  $(SOURCE)  $(DEP_SRVAPP) $(INTDIR)

# End Source File
################################################################################
# Begin Source File

SOURCE=\projects\netstuff\security\common\cmutex.cpp
DEP_CMUTE=\
	.\stdafx.h\
	.\secstuff\sec.h\
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

SOURCE=\projects\netstuff\security\common\COMCLASS.CPP
DEP_COMCL=\
	.\stdafx.h\
	\projects\netstuff\security\common\comclass.h

$(INTDIR)/COMCLASS.OBJ :  $(SOURCE)  $(DEP_COMCL) $(INTDIR)
   $(CPP) $(CPP_PROJ)  $(SOURCE) 

# End Source File
################################################################################
# Begin Source File

SOURCE=\projects\netstuff\security\common\dbcode.cpp
DEP_DBCOD=\
	.\stdafx.h\
	\projects\netstuff\security\common\comclass.h\
	.\secstuff\sec.h\
	\projects\netstuff\security\common\cmutex.h\
	\projects\netstuff\security\common\dbcode.h\
	\projects\netstuff\security\common\npipe.h

$(INTDIR)/dbcode.obj :  $(SOURCE)  $(DEP_DBCOD) $(INTDIR)
   $(CPP) $(CPP_PROJ)  $(SOURCE) 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\srvview.cpp
DEP_SRVVI=\
	.\stdafx.h\
	\projects\netstuff\security\common\common.h\
	.\srvapp.h\
	.\srvdoc.h\
	\projects\netstuff\security\common\easyview.h\
	.\srvview.h\
	\projects\netstuff\security\common\comclass.h\
	.\secstuff\sec.h\
	\projects\netstuff\security\common\npipe.h\
	\projects\netstuff\security\common\cmutex.h\
	\projects\netstuff\security\common\cfilemap.h\
	\projects\netstuff\security\common\dbcode.h\
	\projects\netstuff\security\common\protocol.h\
	.\secstuff\examstff.h\
	\projects\netstuff\security\common\dbdialog.h

$(INTDIR)/srvview.obj :  $(SOURCE)  $(DEP_SRVVI) $(INTDIR)

# End Source File
################################################################################
# Begin Source File

SOURCE=\projects\netstuff\security\common\NPIPE.CPP
DEP_NPIPE=\
	.\stdafx.h\
	\projects\netstuff\security\common\comclass.h\
	.\secstuff\sec.h\
	\projects\netstuff\security\common\npipe.h

$(INTDIR)/NPIPE.OBJ :  $(SOURCE)  $(DEP_NPIPE) $(INTDIR)
   $(CPP) $(CPP_PROJ)  $(SOURCE) 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\stdafx.cpp
DEP_STDAF=\
	.\stdafx.h

$(INTDIR)/stdafx.obj :  $(SOURCE)  $(DEP_STDAF) $(INTDIR)

# End Source File
# End Group
# End Project
################################################################################
