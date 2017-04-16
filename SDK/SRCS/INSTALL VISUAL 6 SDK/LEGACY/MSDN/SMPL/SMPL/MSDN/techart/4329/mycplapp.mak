# Microsoft Visual C++ Generated NMAKE File, Format Version 2.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Dynamic-Link Library" 0x0102

!IF "$(CFG)" == ""
CFG=Win32 Debug
!MESSAGE No configuration specified.  Defaulting to Win32 Debug.
!ENDIF 

!IF "$(CFG)" != "Win32 Debug" && "$(CFG)" != "Win32 Release"
!MESSAGE Invalid configuration "$(CFG)" specified.
!MESSAGE You can specify a configuration when running NMAKE on this makefile
!MESSAGE by defining the macro CFG on the command line.  For example:
!MESSAGE 
!MESSAGE NMAKE /f "MyCplApp.mak" CFG="Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "Win32 Debug" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE "Win32 Release" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE 
!ERROR An invalid configuration is specified.
!ENDIF 

################################################################################
# Begin Project
# PROP Target_Last_Scanned "Win32 Release"
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

ALL : c:\NT351\system32\MyCplApp.cpl $(OUTDIR)/MyCplApp.bsc

$(OUTDIR) : 
    if not exist $(OUTDIR)/nul mkdir $(OUTDIR)

# ADD BASE CPP /nologo /MT /W3 /GX /Zi /Od /D "_DEBUG" /D "WIN32" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "_WINDLL" /FR /Yu"stdafx.h" /c
# ADD CPP /nologo /MT /W3 /GX /Zi /Od /D "_DEBUG" /D "WIN32" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "_WINDLL" /Yu"stdafx.h" /c
# SUBTRACT CPP /Fr
CPP_PROJ=/nologo /MT /W3 /GX /Zi /Od /D "_DEBUG" /D "WIN32" /D "_WINDOWS" /D\
 "_MBCS" /D "_USRDLL" /D "_WINDLL" /Fp$(OUTDIR)/"MyCplApp.pch" /Yu"stdafx.h"\
 /Fo$(INTDIR)/ /Fd$(OUTDIR)/"MyCplApp.pdb" /c 
CPP_OBJS=.\WinDebug/
# ADD BASE RSC /l 0x0 /d "_DEBUG"
# ADD RSC /l 0x0 /d "_DEBUG"
RSC_PROJ=/l 0x0 /fo$(INTDIR)/"MyCplApp.res" /d "_DEBUG" 
BSC32=bscmake.exe
BSC32_SBRS= \
	
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
BSC32_FLAGS=/nologo /o$(OUTDIR)/"MyCplApp.bsc" 

$(OUTDIR)/MyCplApp.bsc : $(OUTDIR)  $(BSC32_SBRS)
LINK32=link.exe
# ADD BASE LINK32 /NOLOGO /SUBSYSTEM:windows /DLL /DEBUG /MACHINE:I386 /DEF:"MyCplApp.def" /IMPLIB:"MyCplApp.lib"
# SUBTRACT BASE LINK32 /PDB:none
# ADD LINK32 /NOLOGO /SUBSYSTEM:windows /DLL /DEBUG /MACHINE:I386 /DEF:"MyCplApp.def" /OUT:"c:\NT351\system32\MyCplApp.cpl" /IMPLIB:"MyCplApp.lib"
# SUBTRACT LINK32 /PDB:none
LINK32_FLAGS=/NOLOGO /SUBSYSTEM:windows /DLL /INCREMENTAL:yes\
 /PDB:$(OUTDIR)/"MyCplApp.pdb" /DEBUG /MACHINE:I386 /DEF:"MyCplApp.def"\
 /OUT:"c:\NT351\system32\MyCplApp.cpl" /IMPLIB:"MyCplApp.lib" 
DEF_FILE=
LINK32_OBJS= \
	$(INTDIR)/stdafx.obj \
	$(INTDIR)/MyCplApp.obj \
	$(INTDIR)/MyCplApp.res \
	$(INTDIR)/ctrlpan.obj \
	$(INTDIR)/mypanel.obj \
	$(INTDIR)/mydialog.obj

c:\NT351\system32\MyCplApp.cpl : $(OUTDIR)  $(DEF_FILE) $(LINK32_OBJS)
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

ALL : $(OUTDIR)/MyCplApp.dll $(OUTDIR)/MyCplApp.bsc

$(OUTDIR) : 
    if not exist $(OUTDIR)/nul mkdir $(OUTDIR)

# ADD BASE CPP /nologo /MT /W3 /GX /O2 /D "NDEBUG" /D "WIN32" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "_WINDLL" /FR /Yu"stdafx.h" /c
# ADD CPP /nologo /MT /W3 /GX /O2 /D "NDEBUG" /D "WIN32" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "_WINDLL" /Yu"stdafx.h" /c
# SUBTRACT CPP /Fr
CPP_PROJ=/nologo /MT /W3 /GX /O2 /D "NDEBUG" /D "WIN32" /D "_WINDOWS" /D\
 "_MBCS" /D "_USRDLL" /D "_WINDLL" /Fp$(OUTDIR)/"MyCplApp.pch" /Yu"stdafx.h"\
 /Fo$(INTDIR)/ /c 
CPP_OBJS=.\WinRel/
# ADD BASE RSC /l 0x0 /d "NDEBUG"
# ADD RSC /l 0x0 /d "NDEBUG"
RSC_PROJ=/l 0x0 /fo$(INTDIR)/"MyCplApp.res" /d "NDEBUG" 
BSC32=bscmake.exe
BSC32_SBRS= \
	
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
BSC32_FLAGS=/nologo /o$(OUTDIR)/"MyCplApp.bsc" 

$(OUTDIR)/MyCplApp.bsc : $(OUTDIR)  $(BSC32_SBRS)
LINK32=link.exe
# ADD BASE LINK32 /NOLOGO /SUBSYSTEM:windows /DLL /MACHINE:I386 /DEF:"MyCplApp.def" /IMPLIB:"MyCplApp.lib"
# SUBTRACT BASE LINK32 /PDB:none
# ADD LINK32 /NOLOGO /SUBSYSTEM:windows /DLL /MACHINE:I386 /DEF:"MyCplApp.def" /IMPLIB:"MyCplApp.lib"
# SUBTRACT LINK32 /PDB:none
LINK32_FLAGS=/NOLOGO /SUBSYSTEM:windows /DLL /INCREMENTAL:no\
 /PDB:$(OUTDIR)/"MyCplApp.pdb" /MACHINE:I386 /DEF:"MyCplApp.def"\
 /OUT:$(OUTDIR)/"MyCplApp.dll" /IMPLIB:"MyCplApp.lib" 
DEF_FILE=
LINK32_OBJS= \
	$(INTDIR)/stdafx.obj \
	$(INTDIR)/MyCplApp.obj \
	$(INTDIR)/MyCplApp.res \
	$(INTDIR)/ctrlpan.obj \
	$(INTDIR)/mypanel.obj \
	$(INTDIR)/mydialog.obj

$(OUTDIR)/MyCplApp.dll : $(OUTDIR)  $(DEF_FILE) $(LINK32_OBJS)
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

$(INTDIR)/stdafx.obj :  $(SOURCE)  $(DEP_STDAF) $(INTDIR)
   $(CPP) /nologo /MT /W3 /GX /Zi /Od /D "_DEBUG" /D "WIN32" /D "_WINDOWS" /D\
 "_MBCS" /D "_USRDLL" /D "_WINDLL" /Fp$(OUTDIR)/"MyCplApp.pch" /Yc"stdafx.h"\
 /Fo$(INTDIR)/ /Fd$(OUTDIR)/"MyCplApp.pdb" /c  $(SOURCE) 

!ELSEIF  "$(CFG)" == "Win32 Release"

# ADD BASE CPP /Yc"stdafx.h"
# ADD CPP /Yc"stdafx.h"

$(INTDIR)/stdafx.obj :  $(SOURCE)  $(DEP_STDAF) $(INTDIR)
   $(CPP) /nologo /MT /W3 /GX /O2 /D "NDEBUG" /D "WIN32" /D "_WINDOWS" /D\
 "_MBCS" /D "_USRDLL" /D "_WINDLL" /Fp$(OUTDIR)/"MyCplApp.pch" /Yc"stdafx.h"\
 /Fo$(INTDIR)/ /c  $(SOURCE) 

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\MyCplApp.cpp
DEP_MYCPL=\
	.\stdafx.h\
	.\MyCplApp.h\
	.\mypanel.h\
	.\mydialog.h\
	.\ctrlpan.h

$(INTDIR)/MyCplApp.obj :  $(SOURCE)  $(DEP_MYCPL) $(INTDIR)\
 $(INTDIR)/stdafx.obj

# End Source File
################################################################################
# Begin Source File

SOURCE=.\MyCplApp.rc
DEP_MYCPLA=\
	.\icon1.ico\
	.\res\MyCplApp.rc2

$(INTDIR)/MyCplApp.res :  $(SOURCE)  $(DEP_MYCPLA) $(INTDIR)
   $(RSC) $(RSC_PROJ)  $(SOURCE) 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\readme.txt
# End Source File
################################################################################
# Begin Source File

SOURCE=.\ctrlpan.cpp
DEP_CTRLP=\
	.\stdafx.h\
	.\ctrlpan.h

$(INTDIR)/ctrlpan.obj :  $(SOURCE)  $(DEP_CTRLP) $(INTDIR) $(INTDIR)/stdafx.obj

# End Source File
################################################################################
# Begin Source File

SOURCE=.\mypanel.cpp
DEP_MYPAN=\
	.\stdafx.h\
	.\MyCplApp.h\
	.\mypanel.h\
	.\mydialog.h\
	.\ctrlpan.h

$(INTDIR)/mypanel.obj :  $(SOURCE)  $(DEP_MYPAN) $(INTDIR) $(INTDIR)/stdafx.obj

# End Source File
################################################################################
# Begin Source File

SOURCE=.\mydialog.cpp
DEP_MYDIA=\
	.\stdafx.h\
	.\MyCplApp.h\
	.\mypanel.h\
	.\mydialog.h\
	.\ctrlpan.h

$(INTDIR)/mydialog.obj :  $(SOURCE)  $(DEP_MYDIA) $(INTDIR)\
 $(INTDIR)/stdafx.obj

# End Source File
# End Group
# End Project
################################################################################
