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
!MESSAGE NMAKE /f "XlAuto.mak" CFG="Win32 Debug"
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

# PROP BASE Use_MFC 6
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "WinDebug"
# PROP BASE Intermediate_Dir "WinDebug"
# PROP Use_MFC 6
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "WinDebug"
# PROP Intermediate_Dir "WinDebug"
OUTDIR=.\WinDebug
INTDIR=.\WinDebug

ALL : MTL_TLBS .\WinDebug\XlAuto.exe .\WinDebug\XlAuto.bsc

$(OUTDIR) : 
    if not exist $(OUTDIR)/nul mkdir $(OUTDIR)

# ADD BASE MTL /nologo /D "_DEBUG" /win32
# ADD MTL /nologo /D "_DEBUG" /win32
MTL_PROJ=/nologo /D "_DEBUG" /win32 

MTL_TLBS : .\WinDebug\XlAuto.tlb
# ADD BASE CPP /nologo /MD /W3 /GX /Zi /Od /D "_DEBUG" /D "WIN32" /D "_WINDOWS" /D "_MBCS" /D "_AFXDLL" /FR /Yu"stdafx.h" /c
# ADD CPP /nologo /MD /W4 /GX /Zi /Od /D "_DEBUG" /D "WIN32" /D "_WINDOWS" /D "_MBCS" /D "_AFXDLL" /FR /Yu"stdafx.h" /c
CPP_PROJ=/nologo /MD /W4 /GX /Zi /Od /D "_DEBUG" /D "WIN32" /D "_WINDOWS" /D\
 "_MBCS" /D "_AFXDLL" /FR$(INTDIR)/ /Fp$(OUTDIR)/"XlAuto.pch" /Yu"stdafx.h"\
 /Fo$(INTDIR)/ /Fd$(OUTDIR)/"XlAuto.pdb" /c 
CPP_OBJS=.\WinDebug/
# ADD BASE RSC /l 0x409 /d "_DEBUG" /d "_AFXDLL"
# ADD RSC /l 0x409 /d "_DEBUG" /d "_AFXDLL"
RSC_PROJ=/l 0x409 /fo$(INTDIR)/"XlAuto.res" /d "_DEBUG" /d "_AFXDLL" 
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
BSC32_FLAGS=/nologo /o$(OUTDIR)/"XlAuto.bsc" 
BSC32_SBRS= \
	.\WinDebug\stdafx.sbr \
	.\WinDebug\XlAuto.sbr \
	.\WinDebug\mainfrm.sbr \
	.\WinDebug\XlAutdoc.sbr \
	.\WinDebug\XlAutvw.sbr \
	.\WinDebug\cntritem.sbr \
	.\WinDebug\xlrange.sbr \
	.\WinDebug\xlsheet.sbr \
	.\WinDebug\xlchtobj.sbr \
	.\WinDebug\chartdlg.sbr \
	.\WinDebug\xlchtobs.sbr \
	.\WinDebug\xlchart.sbr

.\WinDebug\XlAuto.bsc : $(OUTDIR)  $(BSC32_SBRS)
    $(BSC32) @<<
  $(BSC32_FLAGS) $(BSC32_SBRS)
<<

LINK32=link.exe
# ADD BASE LINK32 /NOLOGO /SUBSYSTEM:windows /DEBUG /MACHINE:I386
# SUBTRACT BASE LINK32 /PDB:none
# ADD LINK32 /NOLOGO /SUBSYSTEM:windows /DEBUG /MACHINE:I386
# SUBTRACT LINK32 /PDB:none
LINK32_FLAGS=/NOLOGO /SUBSYSTEM:windows /INCREMENTAL:yes\
 /PDB:$(OUTDIR)/"XlAuto.pdb" /DEBUG /MACHINE:I386 /OUT:$(OUTDIR)/"XlAuto.exe" 
DEF_FILE=
LINK32_OBJS= \
	.\WinDebug\stdafx.obj \
	.\WinDebug\XlAuto.obj \
	.\WinDebug\mainfrm.obj \
	.\WinDebug\XlAutdoc.obj \
	.\WinDebug\XlAutvw.obj \
	.\WinDebug\cntritem.obj \
	.\WinDebug\XlAuto.res \
	.\WinDebug\xlrange.obj \
	.\WinDebug\xlsheet.obj \
	.\WinDebug\xlchtobj.obj \
	.\WinDebug\chartdlg.obj \
	.\WinDebug\xlchtobs.obj \
	.\WinDebug\xlchart.obj

.\WinDebug\XlAuto.exe : $(OUTDIR)  $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ELSEIF  "$(CFG)" == "Win32 Release"

# PROP BASE Use_MFC 6
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "WinRel"
# PROP BASE Intermediate_Dir "WinRel"
# PROP Use_MFC 6
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "WinRel"
# PROP Intermediate_Dir "WinRel"
OUTDIR=.\WinRel
INTDIR=.\WinRel

ALL : MTL_TLBS .\WinRel\XlAuto.exe .\WinRel\XlAuto.bsc

$(OUTDIR) : 
    if not exist $(OUTDIR)/nul mkdir $(OUTDIR)

# ADD BASE MTL /nologo /D "NDEBUG" /win32
# ADD MTL /nologo /D "NDEBUG" /win32
MTL_PROJ=/nologo /D "NDEBUG" /win32 

MTL_TLBS : .\WinRel\XlAuto.tlb
# ADD BASE CPP /nologo /MD /W3 /GX /O2 /D "NDEBUG" /D "WIN32" /D "_WINDOWS" /D "_MBCS" /D "_AFXDLL" /FR /Yu"stdafx.h" /c
# ADD CPP /nologo /MD /W4 /GX /O2 /D "NDEBUG" /D "WIN32" /D "_WINDOWS" /D "_MBCS" /D "_AFXDLL" /FR /Yu"stdafx.h" /c
CPP_PROJ=/nologo /MD /W4 /GX /O2 /D "NDEBUG" /D "WIN32" /D "_WINDOWS" /D\
 "_MBCS" /D "_AFXDLL" /FR$(INTDIR)/ /Fp$(OUTDIR)/"XlAuto.pch" /Yu"stdafx.h"\
 /Fo$(INTDIR)/ /c 
CPP_OBJS=.\WinRel/
# ADD BASE RSC /l 0x409 /d "NDEBUG" /d "_AFXDLL"
# ADD RSC /l 0x409 /d "NDEBUG" /d "_AFXDLL"
RSC_PROJ=/l 0x409 /fo$(INTDIR)/"XlAuto.res" /d "NDEBUG" /d "_AFXDLL" 
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
BSC32_FLAGS=/nologo /o$(OUTDIR)/"XlAuto.bsc" 
BSC32_SBRS= \
	.\WinRel\stdafx.sbr \
	.\WinRel\XlAuto.sbr \
	.\WinRel\mainfrm.sbr \
	.\WinRel\XlAutdoc.sbr \
	.\WinRel\XlAutvw.sbr \
	.\WinRel\cntritem.sbr \
	.\WinRel\xlrange.sbr \
	.\WinRel\xlsheet.sbr \
	.\WinRel\xlchtobj.sbr \
	.\WinRel\chartdlg.sbr \
	.\WinRel\xlchtobs.sbr \
	.\WinRel\xlchart.sbr

.\WinRel\XlAuto.bsc : $(OUTDIR)  $(BSC32_SBRS)
    $(BSC32) @<<
  $(BSC32_FLAGS) $(BSC32_SBRS)
<<

LINK32=link.exe
# ADD BASE LINK32 /NOLOGO /SUBSYSTEM:windows /MACHINE:I386
# SUBTRACT BASE LINK32 /PDB:none
# ADD LINK32 /NOLOGO /SUBSYSTEM:windows /MACHINE:I386
# SUBTRACT LINK32 /PDB:none
LINK32_FLAGS=/NOLOGO /SUBSYSTEM:windows /INCREMENTAL:no\
 /PDB:$(OUTDIR)/"XlAuto.pdb" /MACHINE:I386 /OUT:$(OUTDIR)/"XlAuto.exe" 
DEF_FILE=
LINK32_OBJS= \
	.\WinRel\stdafx.obj \
	.\WinRel\XlAuto.obj \
	.\WinRel\mainfrm.obj \
	.\WinRel\XlAutdoc.obj \
	.\WinRel\XlAutvw.obj \
	.\WinRel\cntritem.obj \
	.\WinRel\XlAuto.res \
	.\WinRel\xlrange.obj \
	.\WinRel\xlsheet.obj \
	.\WinRel\xlchtobj.obj \
	.\WinRel\chartdlg.obj \
	.\WinRel\xlchtobs.obj \
	.\WinRel\xlchart.obj

.\WinRel\XlAuto.exe : $(OUTDIR)  $(DEF_FILE) $(LINK32_OBJS)
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

!IF  "$(CFG)" == "Win32 Debug"

# ADD BASE CPP /Yc"stdafx.h"
# ADD CPP /Yc"stdafx.h"

.\WinDebug\stdafx.obj :  $(SOURCE)  $(DEP_STDAF) $(INTDIR)
   $(CPP) /nologo /MD /W4 /GX /Zi /Od /D "_DEBUG" /D "WIN32" /D "_WINDOWS" /D\
 "_MBCS" /D "_AFXDLL" /FR$(INTDIR)/ /Fp$(OUTDIR)/"XlAuto.pch" /Yc"stdafx.h"\
 /Fo$(INTDIR)/ /Fd$(OUTDIR)/"XlAuto.pdb" /c  $(SOURCE) 

!ELSEIF  "$(CFG)" == "Win32 Release"

# ADD BASE CPP /Yc"stdafx.h"
# ADD CPP /Yc"stdafx.h"

.\WinRel\stdafx.obj :  $(SOURCE)  $(DEP_STDAF) $(INTDIR)
   $(CPP) /nologo /MD /W4 /GX /O2 /D "NDEBUG" /D "WIN32" /D "_WINDOWS" /D\
 "_MBCS" /D "_AFXDLL" /FR$(INTDIR)/ /Fp$(OUTDIR)/"XlAuto.pch" /Yc"stdafx.h"\
 /Fo$(INTDIR)/ /c  $(SOURCE) 

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\XlAuto.cpp
DEP_XLAUT=\
	.\stdafx.h\
	.\XlAuto.h\
	.\mainfrm.h\
	.\XlAutdoc.h\
	.\XlAutvw.h

!IF  "$(CFG)" == "Win32 Debug"

.\WinDebug\XlAuto.obj :  $(SOURCE)  $(DEP_XLAUT) $(INTDIR)\
 .\WinDebug\stdafx.obj

!ELSEIF  "$(CFG)" == "Win32 Release"

.\WinRel\XlAuto.obj :  $(SOURCE)  $(DEP_XLAUT) $(INTDIR) .\WinRel\stdafx.obj

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\mainfrm.cpp
DEP_MAINF=\
	.\stdafx.h\
	.\XlAuto.h\
	.\mainfrm.h

!IF  "$(CFG)" == "Win32 Debug"

.\WinDebug\mainfrm.obj :  $(SOURCE)  $(DEP_MAINF) $(INTDIR)\
 .\WinDebug\stdafx.obj

!ELSEIF  "$(CFG)" == "Win32 Release"

.\WinRel\mainfrm.obj :  $(SOURCE)  $(DEP_MAINF) $(INTDIR) .\WinRel\stdafx.obj

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\XlAutdoc.cpp
DEP_XLAUTD=\
	.\stdafx.h\
	.\XlAuto.h\
	.\XlAutdoc.h\
	.\cntritem.h\
	.\xlsheet.h\
	.\xlrange.h

!IF  "$(CFG)" == "Win32 Debug"

.\WinDebug\XlAutdoc.obj :  $(SOURCE)  $(DEP_XLAUTD) $(INTDIR)\
 .\WinDebug\stdafx.obj

!ELSEIF  "$(CFG)" == "Win32 Release"

.\WinRel\XlAutdoc.obj :  $(SOURCE)  $(DEP_XLAUTD) $(INTDIR) .\WinRel\stdafx.obj

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\XlAutvw.cpp
DEP_XLAUTV=\
	.\stdafx.h\
	.\XlAuto.h\
	.\XlAutdoc.h\
	.\cntritem.h\
	.\XlAutvw.h\
	.\chartdlg.h\
	.\xlchtobs.h\
	.\xlchtobj.h\
	.\xlsheet.h\
	.\xlrange.h

!IF  "$(CFG)" == "Win32 Debug"

.\WinDebug\XlAutvw.obj :  $(SOURCE)  $(DEP_XLAUTV) $(INTDIR)\
 .\WinDebug\stdafx.obj

!ELSEIF  "$(CFG)" == "Win32 Release"

.\WinRel\XlAutvw.obj :  $(SOURCE)  $(DEP_XLAUTV) $(INTDIR) .\WinRel\stdafx.obj

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\cntritem.cpp
DEP_CNTRI=\
	.\stdafx.h\
	.\XlAuto.h\
	.\XlAutdoc.h\
	.\cntritem.h\
	.\xlsheet.h\
	.\xlrange.h

!IF  "$(CFG)" == "Win32 Debug"

.\WinDebug\cntritem.obj :  $(SOURCE)  $(DEP_CNTRI) $(INTDIR)\
 .\WinDebug\stdafx.obj

!ELSEIF  "$(CFG)" == "Win32 Release"

.\WinRel\cntritem.obj :  $(SOURCE)  $(DEP_CNTRI) $(INTDIR) .\WinRel\stdafx.obj

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\XlAuto.rc
DEP_XLAUTO=\
	.\res\XlAuto.ico\
	.\res\XlAutdoc.ico\
	.\res\toolbar.bmp\
	.\res\XlAuto.rc2

!IF  "$(CFG)" == "Win32 Debug"

.\WinDebug\XlAuto.res :  $(SOURCE)  $(DEP_XLAUTO) $(INTDIR)
   $(RSC) /l 0x409 /fo$(INTDIR)/"XlAuto.res" /i "$(OUTDIR)" /d "_DEBUG" /d\
 "_AFXDLL"  $(SOURCE) 

!ELSEIF  "$(CFG)" == "Win32 Release"

.\WinRel\XlAuto.res :  $(SOURCE)  $(DEP_XLAUTO) $(INTDIR)
   $(RSC) /l 0x409 /fo$(INTDIR)/"XlAuto.res" /i "$(OUTDIR)" /d "NDEBUG" /d\
 "_AFXDLL"  $(SOURCE) 

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\readme.txt
# End Source File
################################################################################
# Begin Source File

SOURCE=.\XlAuto.odl

!IF  "$(CFG)" == "Win32 Debug"

.\WinDebug\XlAuto.tlb :  $(SOURCE)  $(OUTDIR)
   $(MTL) /nologo /D "_DEBUG" /tlb $(OUTDIR)/"XlAuto.tlb" /win32  $(SOURCE) 

!ELSEIF  "$(CFG)" == "Win32 Release"

.\WinRel\XlAuto.tlb :  $(SOURCE)  $(OUTDIR)
   $(MTL) /nologo /D "NDEBUG" /tlb $(OUTDIR)/"XlAuto.tlb" /win32  $(SOURCE) 

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\xlrange.cpp
DEP_XLRAN=\
	.\stdafx.h\
	.\xlrange.h

!IF  "$(CFG)" == "Win32 Debug"

.\WinDebug\xlrange.obj :  $(SOURCE)  $(DEP_XLRAN) $(INTDIR)\
 .\WinDebug\stdafx.obj

!ELSEIF  "$(CFG)" == "Win32 Release"

.\WinRel\xlrange.obj :  $(SOURCE)  $(DEP_XLRAN) $(INTDIR) .\WinRel\stdafx.obj

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\xlsheet.cpp
DEP_XLSHE=\
	.\stdafx.h\
	.\xlsheet.h

!IF  "$(CFG)" == "Win32 Debug"

.\WinDebug\xlsheet.obj :  $(SOURCE)  $(DEP_XLSHE) $(INTDIR)\
 .\WinDebug\stdafx.obj

!ELSEIF  "$(CFG)" == "Win32 Release"

.\WinRel\xlsheet.obj :  $(SOURCE)  $(DEP_XLSHE) $(INTDIR) .\WinRel\stdafx.obj

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\xlchtobj.cpp
DEP_XLCHT=\
	.\stdafx.h\
	.\xlchtobj.h

!IF  "$(CFG)" == "Win32 Debug"

.\WinDebug\xlchtobj.obj :  $(SOURCE)  $(DEP_XLCHT) $(INTDIR)\
 .\WinDebug\stdafx.obj

!ELSEIF  "$(CFG)" == "Win32 Release"

.\WinRel\xlchtobj.obj :  $(SOURCE)  $(DEP_XLCHT) $(INTDIR) .\WinRel\stdafx.obj

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\chartdlg.cpp
DEP_CHART=\
	.\stdafx.h\
	.\XlAuto.h\
	.\chartdlg.h

!IF  "$(CFG)" == "Win32 Debug"

.\WinDebug\chartdlg.obj :  $(SOURCE)  $(DEP_CHART) $(INTDIR)\
 .\WinDebug\stdafx.obj

!ELSEIF  "$(CFG)" == "Win32 Release"

.\WinRel\chartdlg.obj :  $(SOURCE)  $(DEP_CHART) $(INTDIR) .\WinRel\stdafx.obj

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\xlchtobs.cpp
DEP_XLCHTO=\
	.\stdafx.h\
	.\xlchtobs.h

!IF  "$(CFG)" == "Win32 Debug"

.\WinDebug\xlchtobs.obj :  $(SOURCE)  $(DEP_XLCHTO) $(INTDIR)\
 .\WinDebug\stdafx.obj

!ELSEIF  "$(CFG)" == "Win32 Release"

.\WinRel\xlchtobs.obj :  $(SOURCE)  $(DEP_XLCHTO) $(INTDIR) .\WinRel\stdafx.obj

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\xlchart.cpp
DEP_XLCHA=\
	.\stdafx.h\
	.\xlchart.h

!IF  "$(CFG)" == "Win32 Debug"

.\WinDebug\xlchart.obj :  $(SOURCE)  $(DEP_XLCHA) $(INTDIR)\
 .\WinDebug\stdafx.obj

!ELSEIF  "$(CFG)" == "Win32 Release"

.\WinRel\xlchart.obj :  $(SOURCE)  $(DEP_XLCHA) $(INTDIR) .\WinRel\stdafx.obj

!ENDIF 

# End Source File
# End Group
# End Project
################################################################################
