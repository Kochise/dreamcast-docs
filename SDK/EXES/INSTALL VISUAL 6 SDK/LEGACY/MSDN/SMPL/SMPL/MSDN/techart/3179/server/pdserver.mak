# Microsoft Visual C++ Generated NMAKE File, Format Version 20054
# MSVCPRJ: version 2.00.4215
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
!MESSAGE NMAKE /f "PDSERVER.MAK" CFG="Win32 Debug"
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
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "WinRel"
# PROP Intermediate_Dir "WinRel"
OUTDIR=.\WinRel
INTDIR=.\WinRel

ALL : .\WinRel\PDSERVER.exe .\WinRel\PDSERVER.bsc

$(OUTDIR) : 
    if not exist $(OUTDIR)/nul mkdir $(OUTDIR)

# ADD BASE MTL /nologo /D "NDEBUG" /win32
# ADD MTL /nologo /I "c:\mstools\idl" /D "NDEBUG" /win32
MTL_PROJ=/nologo /I "c:\mstools\idl" /D "NDEBUG" /win32 
# ADD BASE CPP /nologo /W3 /GX /YX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /FR /c
# ADD CPP /nologo /W3 /GX /YX /O2 /I "c:\mstools\idl" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_UNICODE" /D "UNICODE" /FR /c
CPP_PROJ=/nologo /W3 /GX /YX /O2 /I "c:\mstools\idl" /D "WIN32" /D "NDEBUG" /D\
 "_WINDOWS" /D "_UNICODE" /D "UNICODE" /FR$(INTDIR)/ /Fp$(OUTDIR)/"PDSERVER.pch"\
 /Fo$(INTDIR)/ /c 
CPP_OBJS=.\WinRel/
# ADD BASE RSC /l 0x409 /d "NDEBUG"
# ADD RSC /l 0x409 /i "c:\mstools\idl" /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
BSC32_FLAGS=/nologo /o$(OUTDIR)/"PDSERVER.bsc" 
BSC32_SBRS= \
	.\WinRel\ICF.SBR \
	.\WinRel\APP.SBR \
	.\WinRel\OBJ.SBR

.\WinRel\PDSERVER.bsc : $(OUTDIR)  $(BSC32_SBRS)
    $(BSC32) @<<
  $(BSC32_FLAGS) $(BSC32_SBRS)
<<

LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /NOLOGO /SUBSYSTEM:windows /MACHINE:I386
# ADD LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /NOLOGO /SUBSYSTEM:windows /MACHINE:I386
LINK32_FLAGS=kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib\
 advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib\
 odbccp32.lib /NOLOGO /SUBSYSTEM:windows /INCREMENTAL:no\
 /PDB:$(OUTDIR)/"PDSERVER.pdb" /MACHINE:I386 /DEF:".\PDSERVER.DEF"\
 /OUT:$(OUTDIR)/"PDSERVER.exe" 
DEF_FILE=.\PDSERVER.DEF
LINK32_OBJS= \
	.\WinRel\ICF.OBJ \
	.\WinRel\APP.OBJ \
	.\WinRel\OBJ.OBJ

.\WinRel\PDSERVER.exe : $(OUTDIR)  $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ELSEIF  "$(CFG)" == "Win32 Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "WinDebug"
# PROP BASE Intermediate_Dir "WinDebug"
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "WinDebug"
# PROP Intermediate_Dir "WinDebug"
OUTDIR=.\WinDebug
INTDIR=.\WinDebug

ALL : .\WinDebug\PDSERVER.exe .\WinDebug\PDSERVER.bsc

$(OUTDIR) : 
    if not exist $(OUTDIR)/nul mkdir $(OUTDIR)

# ADD BASE MTL /nologo /D "_DEBUG" /win32
# ADD MTL /nologo /I "c:\mstools\idl" /D "_DEBUG" /win32
MTL_PROJ=/nologo /I "c:\mstools\idl" /D "_DEBUG" /win32 
# ADD BASE CPP /nologo /W3 /GX /Zi /YX /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /FR /c
# ADD CPP /nologo /W3 /GX /Zi /YX"pre.h" /Od /I "c:\mstools\idl" /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_UNICODE" /D "UNICODE" /FR /c
CPP_PROJ=/nologo /W3 /GX /Zi /YX"pre.h" /Od /I "c:\mstools\idl" /D "WIN32" /D\
 "_DEBUG" /D "_WINDOWS" /D "_UNICODE" /D "UNICODE" /FR$(INTDIR)/\
 /Fp$(OUTDIR)/"PDSERVER.pch" /Fo$(INTDIR)/ /Fd$(OUTDIR)/"PDSERVER.pdb" /c 
CPP_OBJS=.\WinDebug/
# ADD BASE RSC /l 0x409 /d "_DEBUG"
# ADD RSC /l 0x409 /i "c:\mstools\idl" /d "_DEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
BSC32_FLAGS=/nologo /o$(OUTDIR)/"PDSERVER.bsc" 
BSC32_SBRS= \
	.\WinDebug\ICF.SBR \
	.\WinDebug\APP.SBR \
	.\WinDebug\OBJ.SBR

.\WinDebug\PDSERVER.bsc : $(OUTDIR)  $(BSC32_SBRS)
    $(BSC32) @<<
  $(BSC32_FLAGS) $(BSC32_SBRS)
<<

LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /NOLOGO /SUBSYSTEM:windows /DEBUG /MACHINE:I386
# ADD LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /NOLOGO /SUBSYSTEM:windows /DEBUG /MACHINE:I386
# SUBTRACT LINK32 /PDB:none
LINK32_FLAGS=kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib\
 advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib\
 odbccp32.lib /NOLOGO /SUBSYSTEM:windows /INCREMENTAL:yes\
 /PDB:$(OUTDIR)/"PDSERVER.pdb" /DEBUG /MACHINE:I386 /DEF:".\PDSERVER.DEF"\
 /OUT:$(OUTDIR)/"PDSERVER.exe" 
DEF_FILE=.\PDSERVER.DEF
LINK32_OBJS= \
	.\WinDebug\ICF.OBJ \
	.\WinDebug\APP.OBJ \
	.\WinDebug\OBJ.OBJ

.\WinDebug\PDSERVER.exe : $(OUTDIR)  $(DEF_FILE) $(LINK32_OBJS)
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

SOURCE=.\ICF.CPP
DEP_ICF_C=\
	.\PRE.H\
	.\APP.H\
	.\ICF.H\
	.\OBJ.H\
	..\idl\pd.h\
	\MSTOOLS\idl\UNKNWN.H

!IF  "$(CFG)" == "Win32 Release"

.\WinRel\ICF.OBJ :  $(SOURCE)  $(DEP_ICF_C) $(INTDIR)

!ELSEIF  "$(CFG)" == "Win32 Debug"

.\WinDebug\ICF.OBJ :  $(SOURCE)  $(DEP_ICF_C) $(INTDIR)

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\APP.CPP
DEP_APP_C=\
	.\PRE.H\
	.\OBJ.H\
	.\APP.H\
	.\ICF.H\
	..\guids.h\
	..\idl\pd.h\
	\MSTOOLS\idl\UNKNWN.H

!IF  "$(CFG)" == "Win32 Release"

.\WinRel\APP.OBJ :  $(SOURCE)  $(DEP_APP_C) $(INTDIR)

!ELSEIF  "$(CFG)" == "Win32 Debug"

.\WinDebug\APP.OBJ :  $(SOURCE)  $(DEP_APP_C) $(INTDIR)

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\OBJ.CPP
DEP_OBJ_C=\
	.\PRE.H\
	.\OBJ.H\
	.\ICF.H\
	.\APP.H\
	..\guids.h\
	..\idl\pd.h\
	\MSTOOLS\idl\UNKNWN.H

!IF  "$(CFG)" == "Win32 Release"

.\WinRel\OBJ.OBJ :  $(SOURCE)  $(DEP_OBJ_C) $(INTDIR)

!ELSEIF  "$(CFG)" == "Win32 Debug"

.\WinDebug\OBJ.OBJ :  $(SOURCE)  $(DEP_OBJ_C) $(INTDIR)

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\PDSERVER.DEF
# End Source File
# End Group
# End Project
################################################################################
