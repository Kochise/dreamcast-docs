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
!MESSAGE NMAKE /f "Appliances.mak" CFG="Win32 Debug"
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

ALL : MTL_TLBS .\WinDebug\Appliances.dll .\WinDebug\Appliances.bsc

$(OUTDIR) : 
    if not exist $(OUTDIR)/nul mkdir $(OUTDIR)

# ADD BASE MTL /nologo /D "_DEBUG" /win32
# ADD MTL /nologo /D "_DEBUG" /win32
MTL_PROJ=/nologo /D "_DEBUG" /win32 

MTL_TLBS : .\WinDebug\Appliances.tlb
# ADD BASE CPP /nologo /MT /W3 /GX /Zi /Od /D "_DEBUG" /D "WIN32" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "_WINDLL" /FR /Yu"stdafx.h" /c
# ADD CPP /nologo /MT /W3 /GX /Zi /Od /D "_DEBUG" /D "WIN32" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "_WINDLL" /Yu"stdafx.h" /c
# SUBTRACT CPP /Fr
CPP_PROJ=/nologo /MT /W3 /GX /Zi /Od /D "_DEBUG" /D "WIN32" /D "_WINDOWS" /D\
 "_MBCS" /D "_USRDLL" /D "_WINDLL" /Fp$(OUTDIR)/"Appliances.pch" /Yu"stdafx.h"\
 /Fo$(INTDIR)/ /Fd$(OUTDIR)/"Appliances.pdb" /c 
CPP_OBJS=.\WinDebug/
# ADD BASE RSC /l 0x0 /d "_DEBUG"
# ADD RSC /l 0x0 /d "_DEBUG"
RSC_PROJ=/l 0x0 /fo$(INTDIR)/"Appliances.res" /d "_DEBUG" 
BSC32=bscmake.exe
BSC32_SBRS= \
	
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
BSC32_FLAGS=/nologo /o$(OUTDIR)/"Appliances.bsc" 

.\WinDebug\Appliances.bsc : $(OUTDIR)  $(BSC32_SBRS)
LINK32=link.exe
# ADD BASE LINK32 /NOLOGO /SUBSYSTEM:windows /DLL /DEBUG /MACHINE:I386 /DEF:"Appliances.def" /IMPLIB:"Appliances.lib"
# SUBTRACT BASE LINK32 /PDB:none
# ADD LINK32 winmm.lib animatesd.lib /NOLOGO /SUBSYSTEM:windows /DLL /DEBUG /MACHINE:I386 /DEF:"Appliances.def" /IMPLIB:"Appliances.lib"
# SUBTRACT LINK32 /PDB:none
LINK32_FLAGS=winmm.lib animatesd.lib /NOLOGO /SUBSYSTEM:windows /DLL\
 /INCREMENTAL:yes /PDB:$(OUTDIR)/"Appliances.pdb" /DEBUG /MACHINE:I386\
 /DEF:"Appliances.def" /OUT:$(OUTDIR)/"Appliances.dll" /IMPLIB:"Appliances.lib" 
DEF_FILE=
LINK32_OBJS= \
	.\WinDebug\stdafx.obj \
	.\WinDebug\Appliances.obj \
	.\WinDebug\Appliances.res \
	.\WinDebug\guids.obj \
	.\WinDebug\lightbl.obj

.\WinDebug\Appliances.dll : $(OUTDIR)  $(DEF_FILE) $(LINK32_OBJS)
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

ALL : MTL_TLBS .\WinRel\Appliances.dll .\WinRel\Appliances.bsc

$(OUTDIR) : 
    if not exist $(OUTDIR)/nul mkdir $(OUTDIR)

# ADD BASE MTL /nologo /D "NDEBUG" /win32
# ADD MTL /nologo /D "NDEBUG" /win32
MTL_PROJ=/nologo /D "NDEBUG" /win32 

MTL_TLBS : .\WinRel\Appliances.tlb
# ADD BASE CPP /nologo /MT /W3 /GX /O2 /D "NDEBUG" /D "WIN32" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "_WINDLL" /FR /Yu"stdafx.h" /c
# ADD CPP /nologo /MT /W3 /GX /O2 /D "NDEBUG" /D "WIN32" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "_WINDLL" /Yu"stdafx.h" /c
# SUBTRACT CPP /Fr
CPP_PROJ=/nologo /MT /W3 /GX /O2 /D "NDEBUG" /D "WIN32" /D "_WINDOWS" /D\
 "_MBCS" /D "_USRDLL" /D "_WINDLL" /Fp$(OUTDIR)/"Appliances.pch" /Yu"stdafx.h"\
 /Fo$(INTDIR)/ /c 
CPP_OBJS=.\WinRel/
# ADD BASE RSC /l 0x0 /d "NDEBUG"
# ADD RSC /l 0x0 /d "NDEBUG"
RSC_PROJ=/l 0x0 /fo$(INTDIR)/"Appliances.res" /d "NDEBUG" 
BSC32=bscmake.exe
BSC32_SBRS= \
	
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
BSC32_FLAGS=/nologo /o$(OUTDIR)/"Appliances.bsc" 

.\WinRel\Appliances.bsc : $(OUTDIR)  $(BSC32_SBRS)
LINK32=link.exe
# ADD BASE LINK32 /NOLOGO /SUBSYSTEM:windows /DLL /MACHINE:I386 /DEF:"Appliances.def" /IMPLIB:"Appliances.lib"
# SUBTRACT BASE LINK32 /PDB:none
# ADD LINK32 winmm.lib animatesr.lib /NOLOGO /SUBSYSTEM:windows /DLL /MACHINE:I386 /DEF:"Appliances.def" /IMPLIB:"Appliances.lib"
# SUBTRACT LINK32 /PDB:none
LINK32_FLAGS=winmm.lib animatesr.lib /NOLOGO /SUBSYSTEM:windows /DLL\
 /INCREMENTAL:no /PDB:$(OUTDIR)/"Appliances.pdb" /MACHINE:I386\
 /DEF:"Appliances.def" /OUT:$(OUTDIR)/"Appliances.dll" /IMPLIB:"Appliances.lib" 
DEF_FILE=
LINK32_OBJS= \
	.\WinRel\stdafx.obj \
	.\WinRel\Appliances.obj \
	.\WinRel\Appliances.res \
	.\WinRel\guids.obj \
	.\WinRel\lightbl.obj

.\WinRel\Appliances.dll : $(OUTDIR)  $(DEF_FILE) $(LINK32_OBJS)
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
	.\stdafx.h\
	\SMPLS\TECH\WIN32\Animate\INCLUDE\ANIMATE.H

!IF  "$(CFG)" == "Win32 Debug"

# ADD BASE CPP /Yc"stdafx.h"
# ADD CPP /Yc"stdafx.h"

.\WinDebug\stdafx.obj :  $(SOURCE)  $(DEP_STDAF) $(INTDIR)
   $(CPP) /nologo /MT /W3 /GX /Zi /Od /D "_DEBUG" /D "WIN32" /D "_WINDOWS" /D\
 "_MBCS" /D "_USRDLL" /D "_WINDLL" /Fp$(OUTDIR)/"Appliances.pch" /Yc"stdafx.h"\
 /Fo$(INTDIR)/ /Fd$(OUTDIR)/"Appliances.pdb" /c  $(SOURCE) 

!ELSEIF  "$(CFG)" == "Win32 Release"

# ADD BASE CPP /Yc"stdafx.h"
# ADD CPP /Yc"stdafx.h"

.\WinRel\stdafx.obj :  $(SOURCE)  $(DEP_STDAF) $(INTDIR)
   $(CPP) /nologo /MT /W3 /GX /O2 /D "NDEBUG" /D "WIN32" /D "_WINDOWS" /D\
 "_MBCS" /D "_USRDLL" /D "_WINDLL" /Fp$(OUTDIR)/"Appliances.pch" /Yc"stdafx.h"\
 /Fo$(INTDIR)/ /c  $(SOURCE) 

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\Appliances.cpp
DEP_APPLI=\
	.\stdafx.h\
	.\Appliances.h\
	\SMPLS\TECH\WIN32\Animate\INCLUDE\ANIMATE.H

!IF  "$(CFG)" == "Win32 Debug"

.\WinDebug\Appliances.obj :  $(SOURCE)  $(DEP_APPLI) $(INTDIR)\
 .\WinDebug\stdafx.obj

!ELSEIF  "$(CFG)" == "Win32 Release"

.\WinRel\Appliances.obj :  $(SOURCE)  $(DEP_APPLI) $(INTDIR)\
 .\WinRel\stdafx.obj

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\Appliances.rc
DEP_APPLIA=\
	.\res\Appliances.rc2

!IF  "$(CFG)" == "Win32 Debug"

.\WinDebug\Appliances.res :  $(SOURCE)  $(DEP_APPLIA) $(INTDIR)
   $(RSC) /l 0x0 /fo$(INTDIR)/"Appliances.res" /i "$(OUTDIR)" /d "_DEBUG"\
  $(SOURCE) 

!ELSEIF  "$(CFG)" == "Win32 Release"

.\WinRel\Appliances.res :  $(SOURCE)  $(DEP_APPLIA) $(INTDIR)
   $(RSC) /l 0x0 /fo$(INTDIR)/"Appliances.res" /i "$(OUTDIR)" /d "NDEBUG"\
  $(SOURCE) 

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\readme.txt
# End Source File
################################################################################
# Begin Source File

SOURCE=.\Appliances.odl

!IF  "$(CFG)" == "Win32 Debug"

.\WinDebug\Appliances.tlb :  $(SOURCE)  $(OUTDIR)
   $(MTL) /nologo /D "_DEBUG" /tlb $(OUTDIR)/"Appliances.tlb" /win32  $(SOURCE)\
 

!ELSEIF  "$(CFG)" == "Win32 Release"

.\WinRel\Appliances.tlb :  $(SOURCE)  $(OUTDIR)
   $(MTL) /nologo /D "NDEBUG" /tlb $(OUTDIR)/"Appliances.tlb" /win32  $(SOURCE)\
 

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\guids.cpp
DEP_GUIDS=\
	.\stdafx.h\
	..\Include\appliancesid.h\
	..\Include\idrawing.h\
	\SMPLS\TECH\WIN32\Animate\INCLUDE\ANIMATE.H

!IF  "$(CFG)" == "Win32 Debug"

.\WinDebug\guids.obj :  $(SOURCE)  $(DEP_GUIDS) $(INTDIR) .\WinDebug\stdafx.obj

!ELSEIF  "$(CFG)" == "Win32 Release"

.\WinRel\guids.obj :  $(SOURCE)  $(DEP_GUIDS) $(INTDIR) .\WinRel\stdafx.obj

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\lightbl.cpp
DEP_LIGHT=\
	.\stdafx.h\
	.\Appliances.h\
	..\Include\idrawing.h\
	.\lightbl.h\
	\SMPLS\TECH\WIN32\Animate\INCLUDE\ANIMATE.H

!IF  "$(CFG)" == "Win32 Debug"

.\WinDebug\lightbl.obj :  $(SOURCE)  $(DEP_LIGHT) $(INTDIR)\
 .\WinDebug\stdafx.obj

!ELSEIF  "$(CFG)" == "Win32 Release"

.\WinRel\lightbl.obj :  $(SOURCE)  $(DEP_LIGHT) $(INTDIR) .\WinRel\stdafx.obj

!ENDIF 

# End Source File
# End Group
# End Project
################################################################################
