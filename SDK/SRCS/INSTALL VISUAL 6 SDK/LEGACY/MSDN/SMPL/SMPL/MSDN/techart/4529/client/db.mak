# Microsoft Visual C++ Generated NMAKE File, Format Version 2.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Application" 0x0101

!IF "$(CFG)" == ""
CFG=Win32 Debug
!MESSAGE No configuration specified.  Defaulting to Win32 Debug.
!ENDIF 

!IF "$(CFG)" != "Win32 Debug" && "$(CFG)" != "Win32 Release" && "$(CFG)" !=\
 "Win32 Unicode Debug" && "$(CFG)" != "Win32 Unicode Release"
!MESSAGE Invalid configuration "$(CFG)" specified.
!MESSAGE You can specify a configuration when running NMAKE on this makefile
!MESSAGE by defining the macro CFG on the command line.  For example:
!MESSAGE 
!MESSAGE NMAKE /f "DB.MAK" CFG="Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "Win32 Debug" (based on "Win32 (x86) Application")
!MESSAGE "Win32 Release" (based on "Win32 (x86) Application")
!MESSAGE "Win32 Unicode Debug" (based on "Win32 (x86) Application")
!MESSAGE "Win32 Unicode Release" (based on "Win32 (x86) Application")
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

ALL : .\WinDebug\DB.exe .\WinDebug\DB.bsc

$(OUTDIR) : 
    if not exist $(OUTDIR)/nul mkdir $(OUTDIR)

# ADD BASE CPP /nologo /MD /W3 /GX /Zi /Od /D "_DEBUG" /D "WIN32" /D "_WINDOWS" /D "_MBCS" /D "_AFXDLL" /FR /Yu"stdafx.h" /c
# ADD CPP /nologo /MD /W3 /GX /Zi /Od /D "_DEBUG" /D "WIN32" /D "_WINDOWS" /D "_MBCS" /D "_AFXDLL" /FR /Yu"stdafx.h" /c
CPP_PROJ=/nologo /MD /W3 /GX /Zi /Od /D "_DEBUG" /D "WIN32" /D "_WINDOWS" /D\
 "_MBCS" /D "_AFXDLL" /FR$(INTDIR)/ /Fp$(OUTDIR)/"DB.pch" /Yu"stdafx.h"\
 /Fo$(INTDIR)/ /Fd$(OUTDIR)/"DB.pdb" /c 
CPP_OBJS=.\WinDebug/
# ADD BASE RSC /l 0x409 /d "_DEBUG" /d "_AFXDLL"
# ADD RSC /l 0x409 /d "_DEBUG" /d "_AFXDLL"
RSC_PROJ=/l 0x409 /fo$(INTDIR)/"DB.res" /d "_DEBUG" /d "_AFXDLL" 
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
BSC32_FLAGS=/nologo /o$(OUTDIR)/"DB.bsc" 
BSC32_SBRS= \
	.\WinDebug\STDAFX.SBR \
	.\WinDebug\DB.SBR \
	.\WinDebug\MAINFRM.SBR \
	.\WinDebug\DBDOC.SBR \
	.\WinDebug\DBVIEW.SBR

.\WinDebug\DB.bsc : $(OUTDIR)  $(BSC32_SBRS)
    $(BSC32) @<<
  $(BSC32_FLAGS) $(BSC32_SBRS)
<<

LINK32=link.exe
# ADD BASE LINK32 /NOLOGO /SUBSYSTEM:windows /DEBUG /MACHINE:I386
# SUBTRACT BASE LINK32 /PDB:none
# ADD LINK32 ole32.lib uuid.lib /NOLOGO /SUBSYSTEM:windows /DEBUG /MACHINE:I386
# SUBTRACT LINK32 /PDB:none
LINK32_FLAGS=ole32.lib uuid.lib /NOLOGO /SUBSYSTEM:windows /INCREMENTAL:yes\
 /PDB:$(OUTDIR)/"DB.pdb" /DEBUG /MACHINE:I386 /OUT:$(OUTDIR)/"DB.exe" 
DEF_FILE=
LINK32_OBJS= \
	.\WinDebug\STDAFX.OBJ \
	.\WinDebug\DB.OBJ \
	.\WinDebug\MAINFRM.OBJ \
	.\WinDebug\DBDOC.OBJ \
	.\WinDebug\DBVIEW.OBJ \
	.\WinDebug\DB.res

.\WinDebug\DB.exe : $(OUTDIR)  $(DEF_FILE) $(LINK32_OBJS)
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

ALL : .\WinRel\DB.exe .\WinRel\DB.bsc

$(OUTDIR) : 
    if not exist $(OUTDIR)/nul mkdir $(OUTDIR)

# ADD BASE CPP /nologo /MD /W3 /GX /O2 /D "NDEBUG" /D "WIN32" /D "_WINDOWS" /D "_MBCS" /D "_AFXDLL" /FR /Yu"stdafx.h" /c
# ADD CPP /nologo /MD /W3 /GX /O2 /D "NDEBUG" /D "WIN32" /D "_WINDOWS" /D "_MBCS" /D "_AFXDLL" /FR /Yu"stdafx.h" /c
CPP_PROJ=/nologo /MD /W3 /GX /O2 /D "NDEBUG" /D "WIN32" /D "_WINDOWS" /D\
 "_MBCS" /D "_AFXDLL" /FR$(INTDIR)/ /Fp$(OUTDIR)/"DB.pch" /Yu"stdafx.h"\
 /Fo$(INTDIR)/ /c 
CPP_OBJS=.\WinRel/
# ADD BASE RSC /l 0x409 /d "NDEBUG" /d "_AFXDLL"
# ADD RSC /l 0x409 /d "NDEBUG" /d "_AFXDLL"
RSC_PROJ=/l 0x409 /fo$(INTDIR)/"DB.res" /d "NDEBUG" /d "_AFXDLL" 
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
BSC32_FLAGS=/nologo /o$(OUTDIR)/"DB.bsc" 
BSC32_SBRS= \
	.\WinRel\STDAFX.SBR \
	.\WinRel\DB.SBR \
	.\WinRel\MAINFRM.SBR \
	.\WinRel\DBDOC.SBR \
	.\WinRel\DBVIEW.SBR

.\WinRel\DB.bsc : $(OUTDIR)  $(BSC32_SBRS)
    $(BSC32) @<<
  $(BSC32_FLAGS) $(BSC32_SBRS)
<<

LINK32=link.exe
# ADD BASE LINK32 /NOLOGO /SUBSYSTEM:windows /MACHINE:I386
# SUBTRACT BASE LINK32 /PDB:none
# ADD LINK32 ole32.lib uuid.lib /NOLOGO /SUBSYSTEM:windows /MACHINE:I386
# SUBTRACT LINK32 /PDB:none
LINK32_FLAGS=ole32.lib uuid.lib /NOLOGO /SUBSYSTEM:windows /INCREMENTAL:no\
 /PDB:$(OUTDIR)/"DB.pdb" /MACHINE:I386 /OUT:$(OUTDIR)/"DB.exe" 
DEF_FILE=
LINK32_OBJS= \
	.\WinRel\STDAFX.OBJ \
	.\WinRel\DB.OBJ \
	.\WinRel\MAINFRM.OBJ \
	.\WinRel\DBDOC.OBJ \
	.\WinRel\DBVIEW.OBJ \
	.\WinRel\DB.res

.\WinRel\DB.exe : $(OUTDIR)  $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ELSEIF  "$(CFG)" == "Win32 Unicode Debug"

# PROP BASE Use_MFC 6
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "Win32_Un"
# PROP BASE Intermediate_Dir "Win32_Un"
# PROP Use_MFC 6
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "WinDebUn"
# PROP Intermediate_Dir "WinDebUn"
OUTDIR=.\WinDebUn
INTDIR=.\WinDebUn

ALL : .\WinDebUn\DB.exe .\WinDebUn\DB.bsc

$(OUTDIR) : 
    if not exist $(OUTDIR)/nul mkdir $(OUTDIR)

# ADD BASE CPP /nologo /MD /W3 /GX /Zi /Od /D "_DEBUG" /D "WIN32" /D "_WINDOWS" /D "_MBCS" /D "_AFXDLL" /FR /Yu"stdafx.h" /c
# ADD CPP /nologo /MD /W3 /GX /Zi /Od /D "_DEBUG" /D "WIN32" /D "_WINDOWS" /D "_MBCS" /D "_AFXDLL" /D "UNICODE" /FR /Yu"stdafx.h" /c
CPP_PROJ=/nologo /MD /W3 /GX /Zi /Od /D "_DEBUG" /D "WIN32" /D "_WINDOWS" /D\
 "_MBCS" /D "_AFXDLL" /D "UNICODE" /FR$(INTDIR)/ /Fp$(OUTDIR)/"DB.pch"\
 /Yu"stdafx.h" /Fo$(INTDIR)/ /Fd$(OUTDIR)/"DB.pdb" /c 
CPP_OBJS=.\WinDebUn/
# ADD BASE RSC /l 0x409 /d "_DEBUG" /d "_AFXDLL"
# ADD RSC /l 0x409 /d "_DEBUG" /d "_AFXDLL"
RSC_PROJ=/l 0x409 /fo$(INTDIR)/"DB.res" /d "_DEBUG" /d "_AFXDLL" 
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
BSC32_FLAGS=/nologo /o$(OUTDIR)/"DB.bsc" 
BSC32_SBRS= \
	.\WinDebUn\STDAFX.SBR \
	.\WinDebUn\DB.SBR \
	.\WinDebUn\MAINFRM.SBR \
	.\WinDebUn\DBDOC.SBR \
	.\WinDebUn\DBVIEW.SBR

.\WinDebUn\DB.bsc : $(OUTDIR)  $(BSC32_SBRS)
    $(BSC32) @<<
  $(BSC32_FLAGS) $(BSC32_SBRS)
<<

LINK32=link.exe
# ADD BASE LINK32 /NOLOGO /SUBSYSTEM:windows /DEBUG /MACHINE:I386
# SUBTRACT BASE LINK32 /PDB:none
# ADD LINK32 ole32.lib uuid.lib /NOLOGO /ENTRY:"wWinMainCRTStartup" /SUBSYSTEM:windows /DEBUG /MACHINE:I386
# SUBTRACT LINK32 /PDB:none
LINK32_FLAGS=ole32.lib uuid.lib /NOLOGO /ENTRY:"wWinMainCRTStartup"\
 /SUBSYSTEM:windows /INCREMENTAL:yes /PDB:$(OUTDIR)/"DB.pdb" /DEBUG\
 /MACHINE:I386 /OUT:$(OUTDIR)/"DB.exe" 
DEF_FILE=
LINK32_OBJS= \
	.\WinDebUn\STDAFX.OBJ \
	.\WinDebUn\DB.OBJ \
	.\WinDebUn\MAINFRM.OBJ \
	.\WinDebUn\DBDOC.OBJ \
	.\WinDebUn\DBVIEW.OBJ \
	.\WinDebUn\DB.res

.\WinDebUn\DB.exe : $(OUTDIR)  $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ELSEIF  "$(CFG)" == "Win32 Unicode Release"

# PROP BASE Use_MFC 6
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "Win32_U0"
# PROP BASE Intermediate_Dir "Win32_U0"
# PROP Use_MFC 6
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "WinRelUn"
# PROP Intermediate_Dir "WinRelUn"
OUTDIR=.\WinRelUn
INTDIR=.\WinRelUn

ALL : .\WinRelUn\DB.exe .\WinRelUn\DB.bsc

$(OUTDIR) : 
    if not exist $(OUTDIR)/nul mkdir $(OUTDIR)

# ADD BASE CPP /nologo /MD /W3 /GX /O2 /D "NDEBUG" /D "WIN32" /D "_WINDOWS" /D "_MBCS" /D "_AFXDLL" /FR /Yu"stdafx.h" /c
# ADD CPP /nologo /MD /W3 /GX /O2 /D "NDEBUG" /D "WIN32" /D "_WINDOWS" /D "_MBCS" /D "_AFXDLL" /D "UNICODE" /FR /Yu"stdafx.h" /c
CPP_PROJ=/nologo /MD /W3 /GX /O2 /D "NDEBUG" /D "WIN32" /D "_WINDOWS" /D\
 "_MBCS" /D "_AFXDLL" /D "UNICODE" /FR$(INTDIR)/ /Fp$(OUTDIR)/"DB.pch"\
 /Yu"stdafx.h" /Fo$(INTDIR)/ /c 
CPP_OBJS=.\WinRelUn/
# ADD BASE RSC /l 0x409 /d "NDEBUG" /d "_AFXDLL"
# ADD RSC /l 0x409 /d "NDEBUG" /d "_AFXDLL"
RSC_PROJ=/l 0x409 /fo$(INTDIR)/"DB.res" /d "NDEBUG" /d "_AFXDLL" 
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
BSC32_FLAGS=/nologo /o$(OUTDIR)/"DB.bsc" 
BSC32_SBRS= \
	.\WinRelUn\STDAFX.SBR \
	.\WinRelUn\DB.SBR \
	.\WinRelUn\MAINFRM.SBR \
	.\WinRelUn\DBDOC.SBR \
	.\WinRelUn\DBVIEW.SBR

.\WinRelUn\DB.bsc : $(OUTDIR)  $(BSC32_SBRS)
    $(BSC32) @<<
  $(BSC32_FLAGS) $(BSC32_SBRS)
<<

LINK32=link.exe
# ADD BASE LINK32 /NOLOGO /SUBSYSTEM:windows /MACHINE:I386
# SUBTRACT BASE LINK32 /PDB:none
# ADD LINK32 ole32.lib uuid.lib /NOLOGO /ENTRY:"wWinMainCRTStartup" /SUBSYSTEM:windows /MACHINE:I386
# SUBTRACT LINK32 /PDB:none
LINK32_FLAGS=ole32.lib uuid.lib /NOLOGO /ENTRY:"wWinMainCRTStartup"\
 /SUBSYSTEM:windows /INCREMENTAL:no /PDB:$(OUTDIR)/"DB.pdb" /MACHINE:I386\
 /OUT:$(OUTDIR)/"DB.exe" 
DEF_FILE=
LINK32_OBJS= \
	.\WinRelUn\STDAFX.OBJ \
	.\WinRelUn\DB.OBJ \
	.\WinRelUn\MAINFRM.OBJ \
	.\WinRelUn\DBDOC.OBJ \
	.\WinRelUn\DBVIEW.OBJ \
	.\WinRelUn\DB.res

.\WinRelUn\DB.exe : $(OUTDIR)  $(DEF_FILE) $(LINK32_OBJS)
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

SOURCE=.\STDAFX.CPP
DEP_STDAF=\
	.\STDAFX.H

!IF  "$(CFG)" == "Win32 Debug"

# ADD BASE CPP /Yc"stdafx.h"
# ADD CPP /Yc"stdafx.h"

.\WinDebug\STDAFX.OBJ :  $(SOURCE)  $(DEP_STDAF) $(INTDIR)
   $(CPP) /nologo /MD /W3 /GX /Zi /Od /D "_DEBUG" /D "WIN32" /D "_WINDOWS" /D\
 "_MBCS" /D "_AFXDLL" /FR$(INTDIR)/ /Fp$(OUTDIR)/"DB.pch" /Yc"stdafx.h"\
 /Fo$(INTDIR)/ /Fd$(OUTDIR)/"DB.pdb" /c  $(SOURCE) 

!ELSEIF  "$(CFG)" == "Win32 Release"

# ADD BASE CPP /Yc"stdafx.h"
# ADD CPP /Yc"stdafx.h"

.\WinRel\STDAFX.OBJ :  $(SOURCE)  $(DEP_STDAF) $(INTDIR)
   $(CPP) /nologo /MD /W3 /GX /O2 /D "NDEBUG" /D "WIN32" /D "_WINDOWS" /D\
 "_MBCS" /D "_AFXDLL" /FR$(INTDIR)/ /Fp$(OUTDIR)/"DB.pch" /Yc"stdafx.h"\
 /Fo$(INTDIR)/ /c  $(SOURCE) 

!ELSEIF  "$(CFG)" == "Win32 Unicode Debug"

# ADD BASE CPP /Yc"stdafx.h"
# ADD CPP /Yc"stdafx.h"

.\WinDebUn\STDAFX.OBJ :  $(SOURCE)  $(DEP_STDAF) $(INTDIR)
   $(CPP) /nologo /MD /W3 /GX /Zi /Od /D "_DEBUG" /D "WIN32" /D "_WINDOWS" /D\
 "_MBCS" /D "_AFXDLL" /D "UNICODE" /FR$(INTDIR)/ /Fp$(OUTDIR)/"DB.pch"\
 /Yc"stdafx.h" /Fo$(INTDIR)/ /Fd$(OUTDIR)/"DB.pdb" /c  $(SOURCE) 

!ELSEIF  "$(CFG)" == "Win32 Unicode Release"

# ADD BASE CPP /Yc"stdafx.h"
# ADD CPP /Yc"stdafx.h"

.\WinRelUn\STDAFX.OBJ :  $(SOURCE)  $(DEP_STDAF) $(INTDIR)
   $(CPP) /nologo /MD /W3 /GX /O2 /D "NDEBUG" /D "WIN32" /D "_WINDOWS" /D\
 "_MBCS" /D "_AFXDLL" /D "UNICODE" /FR$(INTDIR)/ /Fp$(OUTDIR)/"DB.pch"\
 /Yc"stdafx.h" /Fo$(INTDIR)/ /c  $(SOURCE) 

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\DB.CPP
DEP_DB_CP=\
	.\STDAFX.H\
	.\DB.H\
	.\MAINFRM.H\
	.\dbdoc.h\
	.\DBVIEW.H\
	..\Interface\DBSRV.H

!IF  "$(CFG)" == "Win32 Debug"

.\WinDebug\DB.OBJ :  $(SOURCE)  $(DEP_DB_CP) $(INTDIR) .\WinDebug\STDAFX.OBJ

!ELSEIF  "$(CFG)" == "Win32 Release"

.\WinRel\DB.OBJ :  $(SOURCE)  $(DEP_DB_CP) $(INTDIR) .\WinRel\STDAFX.OBJ

!ELSEIF  "$(CFG)" == "Win32 Unicode Debug"

.\WinDebUn\DB.OBJ :  $(SOURCE)  $(DEP_DB_CP) $(INTDIR) .\WinDebUn\STDAFX.OBJ

!ELSEIF  "$(CFG)" == "Win32 Unicode Release"

.\WinRelUn\DB.OBJ :  $(SOURCE)  $(DEP_DB_CP) $(INTDIR) .\WinRelUn\STDAFX.OBJ

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\MAINFRM.CPP
DEP_MAINF=\
	.\STDAFX.H\
	.\DB.H\
	.\MAINFRM.H

!IF  "$(CFG)" == "Win32 Debug"

.\WinDebug\MAINFRM.OBJ :  $(SOURCE)  $(DEP_MAINF) $(INTDIR)\
 .\WinDebug\STDAFX.OBJ

!ELSEIF  "$(CFG)" == "Win32 Release"

.\WinRel\MAINFRM.OBJ :  $(SOURCE)  $(DEP_MAINF) $(INTDIR) .\WinRel\STDAFX.OBJ

!ELSEIF  "$(CFG)" == "Win32 Unicode Debug"

.\WinDebUn\MAINFRM.OBJ :  $(SOURCE)  $(DEP_MAINF) $(INTDIR)\
 .\WinDebUn\STDAFX.OBJ

!ELSEIF  "$(CFG)" == "Win32 Unicode Release"

.\WinRelUn\MAINFRM.OBJ :  $(SOURCE)  $(DEP_MAINF) $(INTDIR)\
 .\WinRelUn\STDAFX.OBJ

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\DBDOC.CPP
DEP_DBDOC=\
	.\STDAFX.H\
	.\DB.H\
	.\dbdoc.h\
	..\Interface\DBSRV.H

!IF  "$(CFG)" == "Win32 Debug"

.\WinDebug\DBDOC.OBJ :  $(SOURCE)  $(DEP_DBDOC) $(INTDIR) .\WinDebug\STDAFX.OBJ

!ELSEIF  "$(CFG)" == "Win32 Release"

.\WinRel\DBDOC.OBJ :  $(SOURCE)  $(DEP_DBDOC) $(INTDIR) .\WinRel\STDAFX.OBJ

!ELSEIF  "$(CFG)" == "Win32 Unicode Debug"

.\WinDebUn\DBDOC.OBJ :  $(SOURCE)  $(DEP_DBDOC) $(INTDIR) .\WinDebUn\STDAFX.OBJ

!ELSEIF  "$(CFG)" == "Win32 Unicode Release"

.\WinRelUn\DBDOC.OBJ :  $(SOURCE)  $(DEP_DBDOC) $(INTDIR) .\WinRelUn\STDAFX.OBJ

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\DBVIEW.CPP
DEP_DBVIE=\
	.\STDAFX.H\
	.\DB.H\
	.\dbdoc.h\
	.\DBVIEW.H\
	..\Interface\DBSRV.H

!IF  "$(CFG)" == "Win32 Debug"

.\WinDebug\DBVIEW.OBJ :  $(SOURCE)  $(DEP_DBVIE) $(INTDIR)\
 .\WinDebug\STDAFX.OBJ

!ELSEIF  "$(CFG)" == "Win32 Release"

.\WinRel\DBVIEW.OBJ :  $(SOURCE)  $(DEP_DBVIE) $(INTDIR) .\WinRel\STDAFX.OBJ

!ELSEIF  "$(CFG)" == "Win32 Unicode Debug"

.\WinDebUn\DBVIEW.OBJ :  $(SOURCE)  $(DEP_DBVIE) $(INTDIR)\
 .\WinDebUn\STDAFX.OBJ

!ELSEIF  "$(CFG)" == "Win32 Unicode Release"

.\WinRelUn\DBVIEW.OBJ :  $(SOURCE)  $(DEP_DBVIE) $(INTDIR)\
 .\WinRelUn\STDAFX.OBJ

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\DB.RC
DEP_DB_RC=\
	.\res\DB.ico\
	.\res\dbdoc.ico\
	.\res\TOOLBAR.BMP\
	.\res\db.rc2

!IF  "$(CFG)" == "Win32 Debug"

.\WinDebug\DB.res :  $(SOURCE)  $(DEP_DB_RC) $(INTDIR)
   $(RSC) $(RSC_PROJ)  $(SOURCE) 

!ELSEIF  "$(CFG)" == "Win32 Release"

.\WinRel\DB.res :  $(SOURCE)  $(DEP_DB_RC) $(INTDIR)
   $(RSC) $(RSC_PROJ)  $(SOURCE) 

!ELSEIF  "$(CFG)" == "Win32 Unicode Debug"

.\WinDebUn\DB.res :  $(SOURCE)  $(DEP_DB_RC) $(INTDIR)
   $(RSC) $(RSC_PROJ)  $(SOURCE) 

!ELSEIF  "$(CFG)" == "Win32 Unicode Release"

.\WinRelUn\DB.res :  $(SOURCE)  $(DEP_DB_RC) $(INTDIR)
   $(RSC) $(RSC_PROJ)  $(SOURCE) 

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\README.TXT
# End Source File
# End Group
# End Project
################################################################################
