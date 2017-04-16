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
!MESSAGE NMAKE /f "viewfile.mak" CFG="Win32 Debug"
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
# PROP Target_Last_Scanned "Win32 Release"
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

ALL : $(OUTDIR)/yahu.exe $(OUTDIR)/viewfile.bsc

$(OUTDIR) : 
    if not exist $(OUTDIR)/nul mkdir $(OUTDIR)

# ADD BASE CPP /nologo /MD /W3 /GX /Zi /Od /D "_DEBUG" /D "WIN32" /D "_WINDOWS" /D "_MBCS" /D "_AFXDLL" /FR /Yu"stdafx.h" /c
# ADD CPP /nologo /Zp1 /MD /W3 /GX /Zi /Od /D "_DEBUG" /D "WIN32" /D "_WINDOWS" /D "_MBCS" /D "_AFXDLL" /FR /Yu"stdafx.h" /c
CPP_PROJ=/nologo /Zp1 /MD /W3 /GX /Zi /Od /D "_DEBUG" /D "WIN32" /D "_WINDOWS"\
 /D "_MBCS" /D "_AFXDLL" /FR$(INTDIR)/ /Fp$(OUTDIR)/"viewfile.pch" /Yu"stdafx.h"\
 /Fo$(INTDIR)/ /Fd$(OUTDIR)/"viewfile.pdb" /c 
CPP_OBJS=.\WinDebug/
# ADD BASE RSC /l 0x409 /d "_DEBUG" /d "_AFXDLL"
# ADD RSC /l 0x409 /d "_DEBUG" /d "_AFXDLL"
RSC_PROJ=/l 0x409 /fo$(INTDIR)/"viewfile.res" /d "_DEBUG" /d "_AFXDLL" 
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
BSC32_FLAGS=/nologo /o$(OUTDIR)/"viewfile.bsc" 
BSC32_SBRS= \
	$(INTDIR)/stdafx.sbr \
	$(INTDIR)/viewfile.sbr \
	$(INTDIR)/mainfrm.sbr \
	$(INTDIR)/childfrm.sbr \
	$(INTDIR)/viewfdoc.sbr \
	$(INTDIR)/viewfvw.sbr \
	$(INTDIR)/rawview.sbr \
	$(INTDIR)/fileview.sbr \
	$(INTDIR)/peview.sbr \
	$(INTDIR)/neview.sbr \
	$(INTDIR)/leview.sbr \
	$(INTDIR)/dosview.sbr \
	$(INTDIR)/pecframe.sbr \
	$(INTDIR)/necframe.sbr \
	$(INTDIR)/lecframe.sbr \
	$(INTDIR)/dosframe.sbr \
	$(INTDIR)/rawframe.sbr \
	$(INTDIR)/pviewdoc.sbr \
	$(INTDIR)/pview.sbr \
	$(INTDIR)/plist.sbr \
	$(INTDIR)/nosysfra.sbr \
	$(INTDIR)/injlib.sbr

$(OUTDIR)/viewfile.bsc : $(OUTDIR)  $(BSC32_SBRS)
    $(BSC32) @<<
  $(BSC32_FLAGS) $(BSC32_SBRS)
<<

LINK32=link.exe
# ADD BASE LINK32 /NOLOGO /SUBSYSTEM:windows /DEBUG /MACHINE:I386
# SUBTRACT BASE LINK32 /PDB:none
# ADD LINK32 /NOLOGO /SUBSYSTEM:windows /DEBUG /MACHINE:I386 /OUT:"windebug\yahu.exe"
# SUBTRACT LINK32 /PDB:none
LINK32_FLAGS=/NOLOGO /SUBSYSTEM:windows /INCREMENTAL:yes\
 /PDB:$(OUTDIR)/"viewfile.pdb" /DEBUG /MACHINE:I386 /OUT:"windebug\yahu.exe" 
DEF_FILE=
LINK32_OBJS= \
	$(INTDIR)/stdafx.obj \
	$(INTDIR)/viewfile.obj \
	$(INTDIR)/mainfrm.obj \
	$(INTDIR)/childfrm.obj \
	$(INTDIR)/viewfdoc.obj \
	$(INTDIR)/viewfvw.obj \
	$(INTDIR)/viewfile.res \
	$(INTDIR)/rawview.obj \
	$(INTDIR)/fileview.obj \
	$(INTDIR)/peview.obj \
	$(INTDIR)/neview.obj \
	$(INTDIR)/leview.obj \
	$(INTDIR)/dosview.obj \
	$(INTDIR)/pecframe.obj \
	$(INTDIR)/necframe.obj \
	$(INTDIR)/lecframe.obj \
	$(INTDIR)/dosframe.obj \
	$(INTDIR)/rawframe.obj \
	$(INTDIR)/pviewdoc.obj \
	$(INTDIR)/pview.obj \
	$(INTDIR)/plist.obj \
	$(INTDIR)/nosysfra.obj \
	$(INTDIR)/injlib.obj

$(OUTDIR)/yahu.exe : $(OUTDIR)  $(DEF_FILE) $(LINK32_OBJS)
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

ALL : $(OUTDIR)/yahu.exe $(OUTDIR)/viewfile.bsc

$(OUTDIR) : 
    if not exist $(OUTDIR)/nul mkdir $(OUTDIR)

# ADD BASE CPP /nologo /MD /W3 /GX /O2 /D "NDEBUG" /D "WIN32" /D "_WINDOWS" /D "_MBCS" /D "_AFXDLL" /FR /Yu"stdafx.h" /c
# ADD CPP /nologo /Zp1 /MD /W1 /GX /O2 /D "NDEBUG" /D "WIN32" /D "_WINDOWS" /D "_MBCS" /D "_AFXDLL" /FR /Yu"stdafx.h" /c
CPP_PROJ=/nologo /Zp1 /MD /W1 /GX /O2 /D "NDEBUG" /D "WIN32" /D "_WINDOWS" /D\
 "_MBCS" /D "_AFXDLL" /FR$(INTDIR)/ /Fp$(OUTDIR)/"viewfile.pch" /Yu"stdafx.h"\
 /Fo$(INTDIR)/ /c 
CPP_OBJS=.\WinRel/
# ADD BASE RSC /l 0x409 /d "NDEBUG" /d "_AFXDLL"
# ADD RSC /l 0x409 /d "NDEBUG" /d "_AFXDLL"
RSC_PROJ=/l 0x409 /fo$(INTDIR)/"viewfile.res" /d "NDEBUG" /d "_AFXDLL" 
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
BSC32_FLAGS=/nologo /o$(OUTDIR)/"viewfile.bsc" 
BSC32_SBRS= \
	$(INTDIR)/stdafx.sbr \
	$(INTDIR)/viewfile.sbr \
	$(INTDIR)/mainfrm.sbr \
	$(INTDIR)/childfrm.sbr \
	$(INTDIR)/viewfdoc.sbr \
	$(INTDIR)/viewfvw.sbr \
	$(INTDIR)/rawview.sbr \
	$(INTDIR)/fileview.sbr \
	$(INTDIR)/peview.sbr \
	$(INTDIR)/neview.sbr \
	$(INTDIR)/leview.sbr \
	$(INTDIR)/dosview.sbr \
	$(INTDIR)/pecframe.sbr \
	$(INTDIR)/necframe.sbr \
	$(INTDIR)/lecframe.sbr \
	$(INTDIR)/dosframe.sbr \
	$(INTDIR)/rawframe.sbr \
	$(INTDIR)/pviewdoc.sbr \
	$(INTDIR)/pview.sbr \
	$(INTDIR)/plist.sbr \
	$(INTDIR)/nosysfra.sbr \
	$(INTDIR)/injlib.sbr

$(OUTDIR)/viewfile.bsc : $(OUTDIR)  $(BSC32_SBRS)
    $(BSC32) @<<
  $(BSC32_FLAGS) $(BSC32_SBRS)
<<

LINK32=link.exe
# ADD BASE LINK32 /NOLOGO /SUBSYSTEM:windows /MACHINE:I386
# SUBTRACT BASE LINK32 /PDB:none
# ADD LINK32 /NOLOGO /SUBSYSTEM:windows /MACHINE:I386 /OUT:"winrel\yahu.exe"
# SUBTRACT LINK32 /PDB:none
LINK32_FLAGS=/NOLOGO /SUBSYSTEM:windows /INCREMENTAL:no\
 /PDB:$(OUTDIR)/"viewfile.pdb" /MACHINE:I386 /OUT:"winrel\yahu.exe" 
DEF_FILE=
LINK32_OBJS= \
	$(INTDIR)/stdafx.obj \
	$(INTDIR)/viewfile.obj \
	$(INTDIR)/mainfrm.obj \
	$(INTDIR)/childfrm.obj \
	$(INTDIR)/viewfdoc.obj \
	$(INTDIR)/viewfvw.obj \
	$(INTDIR)/viewfile.res \
	$(INTDIR)/rawview.obj \
	$(INTDIR)/fileview.obj \
	$(INTDIR)/peview.obj \
	$(INTDIR)/neview.obj \
	$(INTDIR)/leview.obj \
	$(INTDIR)/dosview.obj \
	$(INTDIR)/pecframe.obj \
	$(INTDIR)/necframe.obj \
	$(INTDIR)/lecframe.obj \
	$(INTDIR)/dosframe.obj \
	$(INTDIR)/rawframe.obj \
	$(INTDIR)/pviewdoc.obj \
	$(INTDIR)/pview.obj \
	$(INTDIR)/plist.obj \
	$(INTDIR)/nosysfra.obj \
	$(INTDIR)/injlib.obj

$(OUTDIR)/yahu.exe : $(OUTDIR)  $(DEF_FILE) $(LINK32_OBJS)
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
   $(CPP) /nologo /Zp1 /MD /W3 /GX /Zi /Od /D "_DEBUG" /D "WIN32" /D "_WINDOWS"\
 /D "_MBCS" /D "_AFXDLL" /FR$(INTDIR)/ /Fp$(OUTDIR)/"viewfile.pch" /Yc"stdafx.h"\
 /Fo$(INTDIR)/ /Fd$(OUTDIR)/"viewfile.pdb" /c  $(SOURCE) 

!ELSEIF  "$(CFG)" == "Win32 Release"

# ADD BASE CPP /Yc"stdafx.h"
# ADD CPP /Yc"stdafx.h"

$(INTDIR)/stdafx.obj :  $(SOURCE)  $(DEP_STDAF) $(INTDIR)
   $(CPP) /nologo /Zp1 /MD /W1 /GX /O2 /D "NDEBUG" /D "WIN32" /D "_WINDOWS" /D\
 "_MBCS" /D "_AFXDLL" /FR$(INTDIR)/ /Fp$(OUTDIR)/"viewfile.pch" /Yc"stdafx.h"\
 /Fo$(INTDIR)/ /c  $(SOURCE) 

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\viewfile.cpp
DEP_VIEWF=\
	.\stdafx.h\
	.\viewfile.h\
	.\headers.h\
	.\mainfrm.h\
	.\childfrm.h\
	.\viewfdoc.h\
	.\fileview.h\
	.\pview.h\
	.\pviewdoc.h\
	.\nosysfra.h\
	.\viewfvw.h\
	.\leview.h\
	.\neview.h\
	.\rawview.h\
	.\peview.h\
	.\dosview.h\
	.\rawframe.h\
	.\dosframe.h\
	.\lecframe.h\
	.\pecframe.h\
	.\necframe.h\
	.\headstr.h

$(INTDIR)/viewfile.obj :  $(SOURCE)  $(DEP_VIEWF) $(INTDIR)\
 $(INTDIR)/stdafx.obj

# End Source File
################################################################################
# Begin Source File

SOURCE=.\mainfrm.cpp
DEP_MAINF=\
	.\stdafx.h\
	.\viewfile.h\
	.\viewfdoc.h\
	.\mainfrm.h

$(INTDIR)/mainfrm.obj :  $(SOURCE)  $(DEP_MAINF) $(INTDIR) $(INTDIR)/stdafx.obj

# End Source File
################################################################################
# Begin Source File

SOURCE=.\childfrm.cpp
DEP_CHILD=\
	.\stdafx.h\
	.\viewfile.h\
	.\fileview.h\
	.\viewfdoc.h\
	.\childfrm.h\
	.\headstr.h

$(INTDIR)/childfrm.obj :  $(SOURCE)  $(DEP_CHILD) $(INTDIR)\
 $(INTDIR)/stdafx.obj

# End Source File
################################################################################
# Begin Source File

SOURCE=.\viewfdoc.cpp
DEP_VIEWFD=\
	.\stdafx.h\
	.\viewfile.h\
	.\viewfdoc.h\
	.\headers.h\
	.\fileview.h\
	.\leview.h\
	.\neview.h\
	.\rawview.h\
	.\peview.h\
	.\dosview.h\
	.\headstr.h

$(INTDIR)/viewfdoc.obj :  $(SOURCE)  $(DEP_VIEWFD) $(INTDIR)\
 $(INTDIR)/stdafx.obj

# End Source File
################################################################################
# Begin Source File

SOURCE=.\viewfvw.cpp
DEP_VIEWFV=\
	.\stdafx.h\
	.\viewfile.h\
	.\viewfdoc.h\
	.\viewfvw.h

$(INTDIR)/viewfvw.obj :  $(SOURCE)  $(DEP_VIEWFV) $(INTDIR)\
 $(INTDIR)/stdafx.obj

# End Source File
################################################################################
# Begin Source File

SOURCE=.\viewfile.rc
DEP_VIEWFI=\
	.\res\viewfile.ico\
	.\res\viewfdoc.ico\
	.\res\icon1.ico\
	.\res\idr_dost.ico\
	.\res\idr_pety.ico\
	.\res\idr_lety.ico\
	.\res\idr_pvie.ico\
	.\res\toolbar.bmp\
	.\res\viewfile.rc2

$(INTDIR)/viewfile.res :  $(SOURCE)  $(DEP_VIEWFI) $(INTDIR)
   $(RSC) $(RSC_PROJ)  $(SOURCE) 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\readme.txt
# End Source File
################################################################################
# Begin Source File

SOURCE=.\rawview.cpp
DEP_RAWVI=\
	.\stdafx.h\
	.\viewfile.h\
	.\viewfdoc.h\
	.\rawview.h

$(INTDIR)/rawview.obj :  $(SOURCE)  $(DEP_RAWVI) $(INTDIR) $(INTDIR)/stdafx.obj

# End Source File
################################################################################
# Begin Source File

SOURCE=.\fileview.cpp
DEP_FILEV=\
	.\stdafx.h\
	.\viewfile.h\
	.\viewfdoc.h\
	.\pviewdoc.h\
	.\fileview.h\
	.\headers.h\
	.\headstr.h

$(INTDIR)/fileview.obj :  $(SOURCE)  $(DEP_FILEV) $(INTDIR)\
 $(INTDIR)/stdafx.obj

# End Source File
################################################################################
# Begin Source File

SOURCE=.\peview.cpp
DEP_PEVIE=\
	.\stdafx.h\
	.\viewfile.h\
	.\fileview.h\
	.\peview.h\
	.\childfrm.h\
	.\pecframe.h\
	.\headers.h\
	.\injlib.h\
	.\headstr.h

$(INTDIR)/peview.obj :  $(SOURCE)  $(DEP_PEVIE) $(INTDIR) $(INTDIR)/stdafx.obj

# End Source File
################################################################################
# Begin Source File

SOURCE=.\neview.cpp
DEP_NEVIE=\
	.\stdafx.h\
	.\viewfile.h\
	.\fileview.h\
	.\headers.h\
	.\neview.h\
	.\childfrm.h\
	.\necframe.h\
	.\injlib.h\
	.\headstr.h

$(INTDIR)/neview.obj :  $(SOURCE)  $(DEP_NEVIE) $(INTDIR) $(INTDIR)/stdafx.obj

# End Source File
################################################################################
# Begin Source File

SOURCE=.\leview.cpp
DEP_LEVIE=\
	.\stdafx.h\
	.\viewfile.h\
	.\fileview.h\
	.\leview.h\
	.\headstr.h

$(INTDIR)/leview.obj :  $(SOURCE)  $(DEP_LEVIE) $(INTDIR) $(INTDIR)/stdafx.obj

# End Source File
################################################################################
# Begin Source File

SOURCE=.\dosview.cpp
DEP_DOSVI=\
	.\stdafx.h\
	.\headers.h\
	.\viewfile.h\
	.\fileview.h\
	.\dosview.h\
	.\viewfdoc.h\
	.\headstr.h

$(INTDIR)/dosview.obj :  $(SOURCE)  $(DEP_DOSVI) $(INTDIR) $(INTDIR)/stdafx.obj

# End Source File
################################################################################
# Begin Source File

SOURCE=.\pecframe.cpp
DEP_PECFR=\
	.\stdafx.h\
	.\viewfile.h\
	.\fileview.h\
	.\viewfdoc.h\
	.\headers.h\
	.\peview.h\
	.\childfrm.h\
	.\pecframe.h\
	.\headstr.h

$(INTDIR)/pecframe.obj :  $(SOURCE)  $(DEP_PECFR) $(INTDIR)\
 $(INTDIR)/stdafx.obj

# End Source File
################################################################################
# Begin Source File

SOURCE=.\necframe.cpp
DEP_NECFR=\
	.\stdafx.h\
	.\viewfile.h\
	.\fileview.h\
	.\viewfdoc.h\
	.\headers.h\
	.\neview.h\
	.\childfrm.h\
	.\necframe.h\
	.\headstr.h

$(INTDIR)/necframe.obj :  $(SOURCE)  $(DEP_NECFR) $(INTDIR)\
 $(INTDIR)/stdafx.obj

# End Source File
################################################################################
# Begin Source File

SOURCE=.\lecframe.cpp
DEP_LECFR=\
	.\stdafx.h\
	.\viewfile.h\
	.\childfrm.h\
	.\lecframe.h

$(INTDIR)/lecframe.obj :  $(SOURCE)  $(DEP_LECFR) $(INTDIR)\
 $(INTDIR)/stdafx.obj

# End Source File
################################################################################
# Begin Source File

SOURCE=.\dosframe.cpp
DEP_DOSFR=\
	.\stdafx.h\
	.\viewfile.h\
	.\fileview.h\
	.\viewfdoc.h\
	.\headers.h\
	.\dosview.h\
	.\childfrm.h\
	.\dosframe.h\
	.\headstr.h

$(INTDIR)/dosframe.obj :  $(SOURCE)  $(DEP_DOSFR) $(INTDIR)\
 $(INTDIR)/stdafx.obj

# End Source File
################################################################################
# Begin Source File

SOURCE=.\rawframe.cpp
DEP_RAWFR=\
	.\stdafx.h\
	.\viewfile.h\
	.\rawframe.h

$(INTDIR)/rawframe.obj :  $(SOURCE)  $(DEP_RAWFR) $(INTDIR)\
 $(INTDIR)/stdafx.obj

# End Source File
################################################################################
# Begin Source File

SOURCE=.\pviewdoc.cpp
DEP_PVIEW=\
	.\stdafx.h\
	.\viewfile.h\
	.\fileview.h\
	.\pviewdoc.h\
	.\headstr.h

$(INTDIR)/pviewdoc.obj :  $(SOURCE)  $(DEP_PVIEW) $(INTDIR)\
 $(INTDIR)/stdafx.obj

# End Source File
################################################################################
# Begin Source File

SOURCE=.\pview.cpp
DEP_PVIEW_=\
	.\stdafx.h\
	.\viewfile.h\
	.\fileview.h\
	.\pview.h\
	.\plist.h\
	.\headstr.h

$(INTDIR)/pview.obj :  $(SOURCE)  $(DEP_PVIEW_) $(INTDIR) $(INTDIR)/stdafx.obj

# End Source File
################################################################################
# Begin Source File

SOURCE=.\plist.cpp
DEP_PLIST=\
	.\stdafx.h\
	.\viewfile.h\
	.\fileview.h\
	.\pview.h\
	.\plist.h\
	.\headstr.h

$(INTDIR)/plist.obj :  $(SOURCE)  $(DEP_PLIST) $(INTDIR) $(INTDIR)/stdafx.obj

# End Source File
################################################################################
# Begin Source File

SOURCE=.\nosysfra.cpp
DEP_NOSYS=\
	.\stdafx.h\
	.\viewfile.h\
	.\nosysfra.h

$(INTDIR)/nosysfra.obj :  $(SOURCE)  $(DEP_NOSYS) $(INTDIR)\
 $(INTDIR)/stdafx.obj

# End Source File
################################################################################
# Begin Source File

SOURCE=.\injlib.cpp
DEP_INJLI=\
	.\stdafx.h\
	.\injlib.h

$(INTDIR)/injlib.obj :  $(SOURCE)  $(DEP_INJLI) $(INTDIR) $(INTDIR)/stdafx.obj

# End Source File
# End Group
# End Project
################################################################################
