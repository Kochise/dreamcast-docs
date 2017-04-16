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
!MESSAGE NMAKE /f "DBLocal.mak" CFG="Win32 Debug"
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

ALL : .\WinDebug\DBLocal.exe .\WinDebug\DBLocal.bsc

$(OUTDIR) : 
    if not exist $(OUTDIR)/nul mkdir $(OUTDIR)

# ADD BASE CPP /nologo /MD /W3 /GX /Zi /Od /D "_DEBUG" /D "WIN32" /D "_WINDOWS" /D "_MBCS" /D "_AFXDLL" /FR /Yu"stdafx.h" /c
# ADD CPP /nologo /MD /W3 /GX /Zi /Od /D "_DEBUG" /D "WIN32" /D "_WINDOWS" /D "_MBCS" /D "_AFXDLL" /D "LOCALSERVER" /FR /Yu"stdafx.h" /c
CPP_PROJ=/nologo /MD /W3 /GX /Zi /Od /D "_DEBUG" /D "WIN32" /D "_WINDOWS" /D\
 "_MBCS" /D "_AFXDLL" /D "LOCALSERVER" /FR$(INTDIR)/ /Fp$(OUTDIR)/"DBLocal.pch"\
 /Yu"stdafx.h" /Fo$(INTDIR)/ /Fd$(OUTDIR)/"DBLocal.pdb" /c 
CPP_OBJS=.\WinDebug/
# ADD BASE RSC /l 0x409 /d "_DEBUG" /d "_AFXDLL"
# ADD RSC /l 0x409 /d "_DEBUG" /d "_AFXDLL"
RSC_PROJ=/l 0x409 /fo$(INTDIR)/"DBLocal.res" /d "_DEBUG" /d "_AFXDLL" 
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
BSC32_FLAGS=/nologo /o$(OUTDIR)/"DBLocal.bsc" 
BSC32_SBRS= \
	.\WinDebug\stdafx.sbr \
	.\WinDebug\DBLocal.sbr \
	.\WinDebug\mainfrm.sbr \
	.\WinDebug\DBLocdoc.sbr \
	.\WinDebug\DBLocvw.sbr \
	.\WinDebug\DBSRV.SBR \
	.\WinDebug\DBSrvFact.sbr \
	.\WinDebug\guids.sbr \
	.\WinDebug\idb_i.sbr

.\WinDebug\DBLocal.bsc : $(OUTDIR)  $(BSC32_SBRS)
    $(BSC32) @<<
  $(BSC32_FLAGS) $(BSC32_SBRS)
<<

LINK32=link.exe
# ADD BASE LINK32 /NOLOGO /SUBSYSTEM:windows /DEBUG /MACHINE:I386
# SUBTRACT BASE LINK32 /PDB:none
# ADD LINK32 uuid.lib ole32.lib /NOLOGO /SUBSYSTEM:windows /DEBUG /MACHINE:I386
# SUBTRACT LINK32 /PDB:none
LINK32_FLAGS=uuid.lib ole32.lib /NOLOGO /SUBSYSTEM:windows /INCREMENTAL:yes\
 /PDB:$(OUTDIR)/"DBLocal.pdb" /DEBUG /MACHINE:I386 /OUT:$(OUTDIR)/"DBLocal.exe" 
DEF_FILE=
LINK32_OBJS= \
	.\WinDebug\stdafx.obj \
	.\WinDebug\DBLocal.obj \
	.\WinDebug\mainfrm.obj \
	.\WinDebug\DBLocdoc.obj \
	.\WinDebug\DBLocvw.obj \
	.\WinDebug\DBLocal.res \
	.\WinDebug\DBSRV.OBJ \
	.\WinDebug\DBSrvFact.obj \
	.\WinDebug\guids.obj \
	.\WinDebug\idb_i.obj

.\WinDebug\DBLocal.exe : $(OUTDIR)  $(DEF_FILE) $(LINK32_OBJS)
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

ALL : .\WinRel\DBLocal.exe .\WinRel\DBLocal.bsc

$(OUTDIR) : 
    if not exist $(OUTDIR)/nul mkdir $(OUTDIR)

# ADD BASE CPP /nologo /MD /W3 /GX /O2 /D "NDEBUG" /D "WIN32" /D "_WINDOWS" /D "_MBCS" /D "_AFXDLL" /FR /Yu"stdafx.h" /c
# ADD CPP /nologo /MD /W3 /GX /O2 /D "NDEBUG" /D "WIN32" /D "_WINDOWS" /D "_MBCS" /D "_AFXDLL" /D "LOCALSERVER" /FR /Yu"stdafx.h" /c
CPP_PROJ=/nologo /MD /W3 /GX /O2 /D "NDEBUG" /D "WIN32" /D "_WINDOWS" /D\
 "_MBCS" /D "_AFXDLL" /D "LOCALSERVER" /FR$(INTDIR)/ /Fp$(OUTDIR)/"DBLocal.pch"\
 /Yu"stdafx.h" /Fo$(INTDIR)/ /c 
CPP_OBJS=.\WinRel/
# ADD BASE RSC /l 0x409 /d "NDEBUG" /d "_AFXDLL"
# ADD RSC /l 0x409 /d "NDEBUG" /d "_AFXDLL"
RSC_PROJ=/l 0x409 /fo$(INTDIR)/"DBLocal.res" /d "NDEBUG" /d "_AFXDLL" 
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
BSC32_FLAGS=/nologo /o$(OUTDIR)/"DBLocal.bsc" 
BSC32_SBRS= \
	.\WinRel\stdafx.sbr \
	.\WinRel\DBLocal.sbr \
	.\WinRel\mainfrm.sbr \
	.\WinRel\DBLocdoc.sbr \
	.\WinRel\DBLocvw.sbr \
	.\WinRel\DBSRV.SBR \
	.\WinRel\DBSrvFact.sbr \
	.\WinRel\guids.sbr \
	.\WinRel\idb_i.sbr

.\WinRel\DBLocal.bsc : $(OUTDIR)  $(BSC32_SBRS)
    $(BSC32) @<<
  $(BSC32_FLAGS) $(BSC32_SBRS)
<<

LINK32=link.exe
# ADD BASE LINK32 /NOLOGO /SUBSYSTEM:windows /MACHINE:I386
# SUBTRACT BASE LINK32 /PDB:none
# ADD LINK32 uuid.lib ole32.lib /NOLOGO /SUBSYSTEM:windows /MACHINE:I386
# SUBTRACT LINK32 /PDB:none
LINK32_FLAGS=uuid.lib ole32.lib /NOLOGO /SUBSYSTEM:windows /INCREMENTAL:no\
 /PDB:$(OUTDIR)/"DBLocal.pdb" /MACHINE:I386 /OUT:$(OUTDIR)/"DBLocal.exe" 
DEF_FILE=
LINK32_OBJS= \
	.\WinRel\stdafx.obj \
	.\WinRel\DBLocal.obj \
	.\WinRel\mainfrm.obj \
	.\WinRel\DBLocdoc.obj \
	.\WinRel\DBLocvw.obj \
	.\WinRel\DBLocal.res \
	.\WinRel\DBSRV.OBJ \
	.\WinRel\DBSrvFact.obj \
	.\WinRel\guids.obj \
	.\WinRel\idb_i.obj

.\WinRel\DBLocal.exe : $(OUTDIR)  $(DEF_FILE) $(LINK32_OBJS)
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

ALL : .\WinDebUn\DBLocal.exe .\WinDebUn\DBLocal.bsc

$(OUTDIR) : 
    if not exist $(OUTDIR)/nul mkdir $(OUTDIR)

# ADD BASE CPP /nologo /MD /W3 /GX /Zi /Od /D "_DEBUG" /D "WIN32" /D "_WINDOWS" /D "_MBCS" /D "_AFXDLL" /D "LOCALSERVER" /FR /Yu"stdafx.h" /c
# ADD CPP /nologo /MD /W3 /GX /Zi /Od /D "_DEBUG" /D "WIN32" /D "_WINDOWS" /D "_MBCS" /D "_AFXDLL" /D "LOCALSERVER" /D "UNICODE" /FR /Yu"stdafx.h" /c
CPP_PROJ=/nologo /MD /W3 /GX /Zi /Od /D "_DEBUG" /D "WIN32" /D "_WINDOWS" /D\
 "_MBCS" /D "_AFXDLL" /D "LOCALSERVER" /D "UNICODE" /FR$(INTDIR)/\
 /Fp$(OUTDIR)/"DBLocal.pch" /Yu"stdafx.h" /Fo$(INTDIR)/\
 /Fd$(OUTDIR)/"DBLocal.pdb" /c 
CPP_OBJS=.\WinDebUn/
# ADD BASE RSC /l 0x409 /d "_DEBUG" /d "_AFXDLL"
# ADD RSC /l 0x409 /d "_DEBUG" /d "_AFXDLL"
RSC_PROJ=/l 0x409 /fo$(INTDIR)/"DBLocal.res" /d "_DEBUG" /d "_AFXDLL" 
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
BSC32_FLAGS=/nologo /o$(OUTDIR)/"DBLocal.bsc" 
BSC32_SBRS= \
	.\WinDebUn\stdafx.sbr \
	.\WinDebUn\DBLocal.sbr \
	.\WinDebUn\mainfrm.sbr \
	.\WinDebUn\DBLocdoc.sbr \
	.\WinDebUn\DBLocvw.sbr \
	.\WinDebUn\DBSRV.SBR \
	.\WinDebUn\DBSrvFact.sbr \
	.\WinDebUn\guids.sbr \
	.\WinDebUn\idb_i.sbr

.\WinDebUn\DBLocal.bsc : $(OUTDIR)  $(BSC32_SBRS)
    $(BSC32) @<<
  $(BSC32_FLAGS) $(BSC32_SBRS)
<<

LINK32=link.exe
# ADD BASE LINK32 /NOLOGO /SUBSYSTEM:windows /DEBUG /MACHINE:I386
# SUBTRACT BASE LINK32 /PDB:none
# ADD LINK32 uuid.lib ole32.lib /NOLOGO /SUBSYSTEM:windows /DEBUG /MACHINE:I386
# SUBTRACT LINK32 /PDB:none
LINK32_FLAGS=uuid.lib ole32.lib /NOLOGO /SUBSYSTEM:windows /INCREMENTAL:yes\
 /PDB:$(OUTDIR)/"DBLocal.pdb" /DEBUG /MACHINE:I386 /OUT:$(OUTDIR)/"DBLocal.exe" 
DEF_FILE=
LINK32_OBJS= \
	.\WinDebUn\stdafx.obj \
	.\WinDebUn\DBLocal.obj \
	.\WinDebUn\mainfrm.obj \
	.\WinDebUn\DBLocdoc.obj \
	.\WinDebUn\DBLocvw.obj \
	.\WinDebUn\DBLocal.res \
	.\WinDebUn\DBSRV.OBJ \
	.\WinDebUn\DBSrvFact.obj \
	.\WinDebUn\guids.obj \
	.\WinDebUn\idb_i.obj

.\WinDebUn\DBLocal.exe : $(OUTDIR)  $(DEF_FILE) $(LINK32_OBJS)
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

ALL : .\WinRelUn\DBLocal.exe .\WinRelUn\DBLocal.bsc

$(OUTDIR) : 
    if not exist $(OUTDIR)/nul mkdir $(OUTDIR)

# ADD BASE CPP /nologo /MD /W3 /GX /O2 /D "NDEBUG" /D "WIN32" /D "_WINDOWS" /D "_MBCS" /D "_AFXDLL" /D "LOCALSERVER" /FR /Yu"stdafx.h" /c
# ADD CPP /nologo /MD /W3 /GX /O2 /D "NDEBUG" /D "WIN32" /D "_WINDOWS" /D "_MBCS" /D "_AFXDLL" /D "LOCALSERVER" /D "UNICODE" /FR /Yu"stdafx.h" /c
CPP_PROJ=/nologo /MD /W3 /GX /O2 /D "NDEBUG" /D "WIN32" /D "_WINDOWS" /D\
 "_MBCS" /D "_AFXDLL" /D "LOCALSERVER" /D "UNICODE" /FR$(INTDIR)/\
 /Fp$(OUTDIR)/"DBLocal.pch" /Yu"stdafx.h" /Fo$(INTDIR)/ /c 
CPP_OBJS=.\WinRelUn/
# ADD BASE RSC /l 0x409 /d "NDEBUG" /d "_AFXDLL"
# ADD RSC /l 0x409 /d "NDEBUG" /d "_AFXDLL"
RSC_PROJ=/l 0x409 /fo$(INTDIR)/"DBLocal.res" /d "NDEBUG" /d "_AFXDLL" 
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
BSC32_FLAGS=/nologo /o$(OUTDIR)/"DBLocal.bsc" 
BSC32_SBRS= \
	.\WinRelUn\stdafx.sbr \
	.\WinRelUn\DBLocal.sbr \
	.\WinRelUn\mainfrm.sbr \
	.\WinRelUn\DBLocdoc.sbr \
	.\WinRelUn\DBLocvw.sbr \
	.\WinRelUn\DBSRV.SBR \
	.\WinRelUn\DBSrvFact.sbr \
	.\WinRelUn\guids.sbr \
	.\WinRelUn\idb_i.sbr

.\WinRelUn\DBLocal.bsc : $(OUTDIR)  $(BSC32_SBRS)
    $(BSC32) @<<
  $(BSC32_FLAGS) $(BSC32_SBRS)
<<

LINK32=link.exe
# ADD BASE LINK32 /NOLOGO /SUBSYSTEM:windows /MACHINE:I386
# SUBTRACT BASE LINK32 /PDB:none
# ADD LINK32 uuid.lib ole32.lib /NOLOGO /SUBSYSTEM:windows /MACHINE:I386
# SUBTRACT LINK32 /PDB:none
LINK32_FLAGS=uuid.lib ole32.lib /NOLOGO /SUBSYSTEM:windows /INCREMENTAL:no\
 /PDB:$(OUTDIR)/"DBLocal.pdb" /MACHINE:I386 /OUT:$(OUTDIR)/"DBLocal.exe" 
DEF_FILE=
LINK32_OBJS= \
	.\WinRelUn\stdafx.obj \
	.\WinRelUn\DBLocal.obj \
	.\WinRelUn\mainfrm.obj \
	.\WinRelUn\DBLocdoc.obj \
	.\WinRelUn\DBLocvw.obj \
	.\WinRelUn\DBLocal.res \
	.\WinRelUn\DBSRV.OBJ \
	.\WinRelUn\DBSrvFact.obj \
	.\WinRelUn\guids.obj \
	.\WinRelUn\idb_i.obj

.\WinRelUn\DBLocal.exe : $(OUTDIR)  $(DEF_FILE) $(LINK32_OBJS)
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

.\WinDebug\stdafx.obj :  $(SOURCE)  $(DEP_STDAF) $(INTDIR)
   $(CPP) /nologo /MD /W3 /GX /Zi /Od /D "_DEBUG" /D "WIN32" /D "_WINDOWS" /D\
 "_MBCS" /D "_AFXDLL" /D "LOCALSERVER" /FR$(INTDIR)/ /Fp$(OUTDIR)/"DBLocal.pch"\
 /Yc"stdafx.h" /Fo$(INTDIR)/ /Fd$(OUTDIR)/"DBLocal.pdb" /c  $(SOURCE) 

!ELSEIF  "$(CFG)" == "Win32 Release"

# ADD BASE CPP /Yc"stdafx.h"
# ADD CPP /Yc"stdafx.h"

.\WinRel\stdafx.obj :  $(SOURCE)  $(DEP_STDAF) $(INTDIR)
   $(CPP) /nologo /MD /W3 /GX /O2 /D "NDEBUG" /D "WIN32" /D "_WINDOWS" /D\
 "_MBCS" /D "_AFXDLL" /D "LOCALSERVER" /FR$(INTDIR)/ /Fp$(OUTDIR)/"DBLocal.pch"\
 /Yc"stdafx.h" /Fo$(INTDIR)/ /c  $(SOURCE) 

!ELSEIF  "$(CFG)" == "Win32 Unicode Debug"

# ADD BASE CPP /Yc"stdafx.h"
# ADD CPP /Yc"stdafx.h"

.\WinDebUn\stdafx.obj :  $(SOURCE)  $(DEP_STDAF) $(INTDIR)
   $(CPP) /nologo /MD /W3 /GX /Zi /Od /D "_DEBUG" /D "WIN32" /D "_WINDOWS" /D\
 "_MBCS" /D "_AFXDLL" /D "LOCALSERVER" /D "UNICODE" /FR$(INTDIR)/\
 /Fp$(OUTDIR)/"DBLocal.pch" /Yc"stdafx.h" /Fo$(INTDIR)/\
 /Fd$(OUTDIR)/"DBLocal.pdb" /c  $(SOURCE) 

!ELSEIF  "$(CFG)" == "Win32 Unicode Release"

# ADD BASE CPP /Yc"stdafx.h"
# ADD CPP /Yc"stdafx.h"

.\WinRelUn\stdafx.obj :  $(SOURCE)  $(DEP_STDAF) $(INTDIR)
   $(CPP) /nologo /MD /W3 /GX /O2 /D "NDEBUG" /D "WIN32" /D "_WINDOWS" /D\
 "_MBCS" /D "_AFXDLL" /D "LOCALSERVER" /D "UNICODE" /FR$(INTDIR)/\
 /Fp$(OUTDIR)/"DBLocal.pch" /Yc"stdafx.h" /Fo$(INTDIR)/ /c  $(SOURCE) 

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\DBLocal.cpp
DEP_DBLOC=\
	.\stdafx.h\
	.\DBLocal.h\
	.\mainfrm.h\
	.\DBLocdoc.h\
	.\DBLocvw.h\
	..\Object\dbsrvimp.h\
	..\interface\dbsrv.h\
	\CPPtoCOM\DBCOMRem\interface\idb.h\
	\CPPtoCOM\DBCOMRem\interface\refshort.h

!IF  "$(CFG)" == "Win32 Debug"

.\WinDebug\DBLocal.obj :  $(SOURCE)  $(DEP_DBLOC) $(INTDIR)\
 .\WinDebug\stdafx.obj

!ELSEIF  "$(CFG)" == "Win32 Release"

.\WinRel\DBLocal.obj :  $(SOURCE)  $(DEP_DBLOC) $(INTDIR) .\WinRel\stdafx.obj

!ELSEIF  "$(CFG)" == "Win32 Unicode Debug"

.\WinDebUn\DBLocal.obj :  $(SOURCE)  $(DEP_DBLOC) $(INTDIR)\
 .\WinDebUn\stdafx.obj

!ELSEIF  "$(CFG)" == "Win32 Unicode Release"

.\WinRelUn\DBLocal.obj :  $(SOURCE)  $(DEP_DBLOC) $(INTDIR)\
 .\WinRelUn\stdafx.obj

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\mainfrm.cpp
DEP_MAINF=\
	.\stdafx.h\
	.\DBLocal.h\
	.\mainfrm.h

!IF  "$(CFG)" == "Win32 Debug"

.\WinDebug\mainfrm.obj :  $(SOURCE)  $(DEP_MAINF) $(INTDIR)\
 .\WinDebug\stdafx.obj

!ELSEIF  "$(CFG)" == "Win32 Release"

.\WinRel\mainfrm.obj :  $(SOURCE)  $(DEP_MAINF) $(INTDIR) .\WinRel\stdafx.obj

!ELSEIF  "$(CFG)" == "Win32 Unicode Debug"

.\WinDebUn\mainfrm.obj :  $(SOURCE)  $(DEP_MAINF) $(INTDIR)\
 .\WinDebUn\stdafx.obj

!ELSEIF  "$(CFG)" == "Win32 Unicode Release"

.\WinRelUn\mainfrm.obj :  $(SOURCE)  $(DEP_MAINF) $(INTDIR)\
 .\WinRelUn\stdafx.obj

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\DBLocdoc.cpp
DEP_DBLOCD=\
	.\stdafx.h\
	.\DBLocal.h\
	.\DBLocdoc.h

!IF  "$(CFG)" == "Win32 Debug"

.\WinDebug\DBLocdoc.obj :  $(SOURCE)  $(DEP_DBLOCD) $(INTDIR)\
 .\WinDebug\stdafx.obj

!ELSEIF  "$(CFG)" == "Win32 Release"

.\WinRel\DBLocdoc.obj :  $(SOURCE)  $(DEP_DBLOCD) $(INTDIR) .\WinRel\stdafx.obj

!ELSEIF  "$(CFG)" == "Win32 Unicode Debug"

.\WinDebUn\DBLocdoc.obj :  $(SOURCE)  $(DEP_DBLOCD) $(INTDIR)\
 .\WinDebUn\stdafx.obj

!ELSEIF  "$(CFG)" == "Win32 Unicode Release"

.\WinRelUn\DBLocdoc.obj :  $(SOURCE)  $(DEP_DBLOCD) $(INTDIR)\
 .\WinRelUn\stdafx.obj

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\DBLocvw.cpp
DEP_DBLOCV=\
	.\stdafx.h\
	.\DBLocal.h\
	.\DBLocdoc.h\
	.\DBLocvw.h

!IF  "$(CFG)" == "Win32 Debug"

.\WinDebug\DBLocvw.obj :  $(SOURCE)  $(DEP_DBLOCV) $(INTDIR)\
 .\WinDebug\stdafx.obj

!ELSEIF  "$(CFG)" == "Win32 Release"

.\WinRel\DBLocvw.obj :  $(SOURCE)  $(DEP_DBLOCV) $(INTDIR) .\WinRel\stdafx.obj

!ELSEIF  "$(CFG)" == "Win32 Unicode Debug"

.\WinDebUn\DBLocvw.obj :  $(SOURCE)  $(DEP_DBLOCV) $(INTDIR)\
 .\WinDebUn\stdafx.obj

!ELSEIF  "$(CFG)" == "Win32 Unicode Release"

.\WinRelUn\DBLocvw.obj :  $(SOURCE)  $(DEP_DBLOCV) $(INTDIR)\
 .\WinRelUn\stdafx.obj

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\DBLocal.rc
DEP_DBLOCA=\
	.\res\DBLocal.ico\
	.\res\DBLocdoc.ico\
	.\res\toolbar.bmp\
	.\res\DBLocal.rc2

!IF  "$(CFG)" == "Win32 Debug"

.\WinDebug\DBLocal.res :  $(SOURCE)  $(DEP_DBLOCA) $(INTDIR)
   $(RSC) $(RSC_PROJ)  $(SOURCE) 

!ELSEIF  "$(CFG)" == "Win32 Release"

.\WinRel\DBLocal.res :  $(SOURCE)  $(DEP_DBLOCA) $(INTDIR)
   $(RSC) $(RSC_PROJ)  $(SOURCE) 

!ELSEIF  "$(CFG)" == "Win32 Unicode Debug"

.\WinDebUn\DBLocal.res :  $(SOURCE)  $(DEP_DBLOCA) $(INTDIR)
   $(RSC) $(RSC_PROJ)  $(SOURCE) 

!ELSEIF  "$(CFG)" == "Win32 Unicode Release"

.\WinRelUn\DBLocal.res :  $(SOURCE)  $(DEP_DBLOCA) $(INTDIR)
   $(RSC) $(RSC_PROJ)  $(SOURCE) 

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\readme.txt
# End Source File
################################################################################
# Begin Source File

SOURCE=\CPPtoCOM\DBCOMRem\Object\DBSRV.CPP
DEP_DBSRV=\
	\CPPtoCOM\DBCOMRem\Object\stdafx.h\
	..\Object\dbsrvimp.h\
	.\DBLocal.h\
	..\interface\dbsrv.h\
	\CPPtoCOM\DBCOMRem\interface\idb.h\
	\CPPtoCOM\DBCOMRem\interface\refshort.h

!IF  "$(CFG)" == "Win32 Debug"

.\WinDebug\DBSRV.OBJ :  $(SOURCE)  $(DEP_DBSRV) $(INTDIR) .\WinDebug\stdafx.obj
   $(CPP) $(CPP_PROJ)  $(SOURCE) 

!ELSEIF  "$(CFG)" == "Win32 Release"

.\WinRel\DBSRV.OBJ :  $(SOURCE)  $(DEP_DBSRV) $(INTDIR) .\WinRel\stdafx.obj
   $(CPP) $(CPP_PROJ)  $(SOURCE) 

!ELSEIF  "$(CFG)" == "Win32 Unicode Debug"

.\WinDebUn\DBSRV.OBJ :  $(SOURCE)  $(DEP_DBSRV) $(INTDIR) .\WinDebUn\stdafx.obj
   $(CPP) $(CPP_PROJ)  $(SOURCE) 

!ELSEIF  "$(CFG)" == "Win32 Unicode Release"

.\WinRelUn\DBSRV.OBJ :  $(SOURCE)  $(DEP_DBSRV) $(INTDIR) .\WinRelUn\stdafx.obj
   $(CPP) $(CPP_PROJ)  $(SOURCE) 

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=\CPPtoCOM\DBCOMRem\Object\DBSrvFact.CPP
DEP_DBSRVF=\
	\CPPtoCOM\DBCOMRem\Object\stdafx.h\
	..\Object\dbsrvimp.h\
	..\interface\dbsrv.h\
	\CPPtoCOM\DBCOMRem\interface\idb.h\
	\CPPtoCOM\DBCOMRem\interface\refshort.h

!IF  "$(CFG)" == "Win32 Debug"

.\WinDebug\DBSrvFact.obj :  $(SOURCE)  $(DEP_DBSRVF) $(INTDIR)\
 .\WinDebug\stdafx.obj
   $(CPP) $(CPP_PROJ)  $(SOURCE) 

!ELSEIF  "$(CFG)" == "Win32 Release"

.\WinRel\DBSrvFact.obj :  $(SOURCE)  $(DEP_DBSRVF) $(INTDIR)\
 .\WinRel\stdafx.obj
   $(CPP) $(CPP_PROJ)  $(SOURCE) 

!ELSEIF  "$(CFG)" == "Win32 Unicode Debug"

.\WinDebUn\DBSrvFact.obj :  $(SOURCE)  $(DEP_DBSRVF) $(INTDIR)\
 .\WinDebUn\stdafx.obj
   $(CPP) $(CPP_PROJ)  $(SOURCE) 

!ELSEIF  "$(CFG)" == "Win32 Unicode Release"

.\WinRelUn\DBSrvFact.obj :  $(SOURCE)  $(DEP_DBSRVF) $(INTDIR)\
 .\WinRelUn\stdafx.obj
   $(CPP) $(CPP_PROJ)  $(SOURCE) 

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=\CPPtoCOM\DBCOMRem\Interface\guids.cpp
DEP_GUIDS=\
	..\interface\dbsrv.h\
	\CPPtoCOM\DBCOMRem\interface\idb.h\
	\CPPtoCOM\DBCOMRem\interface\refshort.h

!IF  "$(CFG)" == "Win32 Debug"

# SUBTRACT CPP /Yu

.\WinDebug\guids.obj :  $(SOURCE)  $(DEP_GUIDS) $(INTDIR)
   $(CPP) /nologo /MD /W3 /GX /Zi /Od /D "_DEBUG" /D "WIN32" /D "_WINDOWS" /D\
 "_MBCS" /D "_AFXDLL" /D "LOCALSERVER" /FR$(INTDIR)/ /Fo$(INTDIR)/\
 /Fd$(OUTDIR)/"DBLocal.pdb" /c  $(SOURCE) 

!ELSEIF  "$(CFG)" == "Win32 Release"

# SUBTRACT CPP /Yu

.\WinRel\guids.obj :  $(SOURCE)  $(DEP_GUIDS) $(INTDIR)
   $(CPP) /nologo /MD /W3 /GX /O2 /D "NDEBUG" /D "WIN32" /D "_WINDOWS" /D\
 "_MBCS" /D "_AFXDLL" /D "LOCALSERVER" /FR$(INTDIR)/ /Fo$(INTDIR)/ /c  $(SOURCE)\
 

!ELSEIF  "$(CFG)" == "Win32 Unicode Debug"

# SUBTRACT CPP /Yu

.\WinDebUn\guids.obj :  $(SOURCE)  $(DEP_GUIDS) $(INTDIR)
   $(CPP) /nologo /MD /W3 /GX /Zi /Od /D "_DEBUG" /D "WIN32" /D "_WINDOWS" /D\
 "_MBCS" /D "_AFXDLL" /D "LOCALSERVER" /D "UNICODE" /FR$(INTDIR)/ /Fo$(INTDIR)/\
 /Fd$(OUTDIR)/"DBLocal.pdb" /c  $(SOURCE) 

!ELSEIF  "$(CFG)" == "Win32 Unicode Release"

# SUBTRACT CPP /Yu

.\WinRelUn\guids.obj :  $(SOURCE)  $(DEP_GUIDS) $(INTDIR)
   $(CPP) /nologo /MD /W3 /GX /O2 /D "NDEBUG" /D "WIN32" /D "_WINDOWS" /D\
 "_MBCS" /D "_AFXDLL" /D "LOCALSERVER" /D "UNICODE" /FR$(INTDIR)/ /Fo$(INTDIR)/\
 /c  $(SOURCE) 

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=\CPPtoCOM\DBCOMRem\Interface\idb_i.c

!IF  "$(CFG)" == "Win32 Debug"

# SUBTRACT CPP /Yu

.\WinDebug\idb_i.obj :  $(SOURCE)  $(INTDIR)
   $(CPP) /nologo /MD /W3 /GX /Zi /Od /D "_DEBUG" /D "WIN32" /D "_WINDOWS" /D\
 "_MBCS" /D "_AFXDLL" /D "LOCALSERVER" /FR$(INTDIR)/ /Fo$(INTDIR)/\
 /Fd$(OUTDIR)/"DBLocal.pdb" /c  $(SOURCE) 

!ELSEIF  "$(CFG)" == "Win32 Release"

# SUBTRACT CPP /Yu

.\WinRel\idb_i.obj :  $(SOURCE)  $(INTDIR)
   $(CPP) /nologo /MD /W3 /GX /O2 /D "NDEBUG" /D "WIN32" /D "_WINDOWS" /D\
 "_MBCS" /D "_AFXDLL" /D "LOCALSERVER" /FR$(INTDIR)/ /Fo$(INTDIR)/ /c  $(SOURCE)\
 

!ELSEIF  "$(CFG)" == "Win32 Unicode Debug"

# SUBTRACT CPP /Yu

.\WinDebUn\idb_i.obj :  $(SOURCE)  $(INTDIR)
   $(CPP) /nologo /MD /W3 /GX /Zi /Od /D "_DEBUG" /D "WIN32" /D "_WINDOWS" /D\
 "_MBCS" /D "_AFXDLL" /D "LOCALSERVER" /D "UNICODE" /FR$(INTDIR)/ /Fo$(INTDIR)/\
 /Fd$(OUTDIR)/"DBLocal.pdb" /c  $(SOURCE) 

!ELSEIF  "$(CFG)" == "Win32 Unicode Release"

# SUBTRACT CPP /Yu

.\WinRelUn\idb_i.obj :  $(SOURCE)  $(INTDIR)
   $(CPP) /nologo /MD /W3 /GX /O2 /D "NDEBUG" /D "WIN32" /D "_WINDOWS" /D\
 "_MBCS" /D "_AFXDLL" /D "LOCALSERVER" /D "UNICODE" /FR$(INTDIR)/ /Fo$(INTDIR)/\
 /c  $(SOURCE) 

!ENDIF 

# End Source File
# End Group
# End Project
################################################################################
