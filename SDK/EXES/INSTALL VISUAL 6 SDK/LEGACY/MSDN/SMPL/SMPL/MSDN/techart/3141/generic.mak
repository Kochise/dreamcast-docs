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
!MESSAGE NMAKE /f "GENERIC.MAK" CFG="Win32 Debug"
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
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
OUTDIR=.
INTDIR=.

ALL : .\GENERIC.exe .\GENERIC.bsc

# ADD BASE MTL /nologo /D "NDEBUG" /win32
# ADD MTL /nologo /D "NDEBUG" /win32
MTL_PROJ=/nologo /D "NDEBUG" /win32 
# ADD BASE CPP /nologo /W3 /YX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_X86_" /FR /c
# ADD CPP /nologo /W3 /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_X86_" /FR /c
CPP_PROJ=/nologo /W3 /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_X86_"\
 /FR$(INTDIR)/ /Fo$(INTDIR)/ /c 
# ADD BASE RSC /l 0x1 /d "NDEBUG" /dNDEBUG,WIN32
# ADD RSC /l 0x409 /d "NDEBUG" /dNDEBUG,WIN32
RSC_PROJ=/l 0x409 /fo$(INTDIR)/"GENERIC.res" /d "NDEBUG" /dNDEBUG,WIN32 
BSC32=bscmake.exe
BSC32_SBRS= \
	.\GENERIC.SBR
# ADD BASE BSC32 /nologo
# SUBTRACT BASE BSC32 /Iu
# ADD BSC32 /nologo
# SUBTRACT BSC32 /Iu
BSC32_FLAGS=/nologo /o$(OUTDIR)/"GENERIC.bsc" 

.\GENERIC.bsc : $(OUTDIR)  $(BSC32_SBRS)
    $(BSC32) @<<
  $(BSC32_FLAGS) $(BSC32_SBRS)
<<

LINK32=link.exe
DEF_FILE=.\GENERIC.DEF
LINK32_OBJS= \
	.\GENERIC.OBJ \
	.\GENERIC.res
# ADD BASE LINK32 user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib olecli32.lib olesvr32.lib /NOLOGO /SUBSYSTEM:windows /MACHINE:IX86
# ADD LINK32 version.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib olecli32.lib olesvr32.lib /NOLOGO /SUBSYSTEM:windows /MACHINE:IX86
LINK32_FLAGS=version.lib user32.lib gdi32.lib winspool.lib comdlg32.lib\
 advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib olecli32.lib\
 olesvr32.lib /NOLOGO /SUBSYSTEM:windows /INCREMENTAL:no\
 /PDB:$(OUTDIR)/"GENERIC.pdb" /MACHINE:IX86 /DEF:".\GENERIC.DEF"\
 /OUT:$(OUTDIR)/"GENERIC.exe" 

.\GENERIC.exe : $(OUTDIR)  $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ELSEIF  "$(CFG)" == "Win32 Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
OUTDIR=.
INTDIR=.

ALL : .\GENERIC.exe .\GENERIC.bsc

# ADD BASE MTL /nologo /D "_DEBUG" /win32
# ADD MTL /nologo /D "_DEBUG" /win32
MTL_PROJ=/nologo /D "_DEBUG" /win32 
# ADD BASE CPP /nologo /W3 /Zi /YX /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_X86_" /FR /c
# ADD CPP /nologo /W3 /Zi /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_X86_" /FR /c
CPP_PROJ=/nologo /W3 /Zi /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_X86_"\
 /FR$(INTDIR)/ /Fo$(INTDIR)/ /Fd$(OUTDIR)/"GENERIC.pdb" /c 
# ADD BASE RSC /l 0x1 /d "_DEBUG" /d_DEBUG,WIN32
# ADD RSC /l 0x409 /d "_DEBUG" /d_DEBUG,WIN32
RSC_PROJ=/l 0x409 /fo$(INTDIR)/"GENERIC.res" /d "_DEBUG" /d_DEBUG,WIN32 
BSC32=bscmake.exe
BSC32_SBRS= \
	.\GENERIC.SBR
# ADD BASE BSC32 /nologo
# SUBTRACT BASE BSC32 /Iu
# ADD BSC32 /nologo
# SUBTRACT BSC32 /Iu
BSC32_FLAGS=/nologo /o$(OUTDIR)/"GENERIC.bsc" 

.\GENERIC.bsc : $(OUTDIR)  $(BSC32_SBRS)
    $(BSC32) @<<
  $(BSC32_FLAGS) $(BSC32_SBRS)
<<

LINK32=link.exe
DEF_FILE=.\GENERIC.DEF
LINK32_OBJS= \
	.\GENERIC.OBJ \
	.\GENERIC.res
# ADD BASE LINK32 user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib olecli32.lib olesvr32.lib /NOLOGO /SUBSYSTEM:windows /DEBUG /MACHINE:IX86
# ADD LINK32 version.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib olecli32.lib olesvr32.lib /NOLOGO /SUBSYSTEM:windows /DEBUG /MACHINE:IX86
LINK32_FLAGS=version.lib user32.lib gdi32.lib winspool.lib comdlg32.lib\
 advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib olecli32.lib\
 olesvr32.lib /NOLOGO /SUBSYSTEM:windows /INCREMENTAL:yes\
 /PDB:$(OUTDIR)/"GENERIC.pdb" /DEBUG /MACHINE:IX86 /DEF:".\GENERIC.DEF"\
 /OUT:$(OUTDIR)/"GENERIC.exe" 

.\GENERIC.exe : $(OUTDIR)  $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ENDIF 

.c.obj:
   $(CPP) $(CPP_PROJ) $<  

.cpp.obj:
   $(CPP) $(CPP_PROJ) $<  

.cxx.obj:
   $(CPP) $(CPP_PROJ) $<  

################################################################################
# Begin Group "Source Files"

################################################################################
# Begin Source File

SOURCE=.\GENERIC.C
DEP_GENER=\
	.\GENERIC.H

.\GENERIC.OBJ :  $(SOURCE)  $(DEP_GENER) $(INTDIR)

# End Source File
################################################################################
# Begin Source File

SOURCE=.\GENERIC.RC
DEP_GENERI=\
	.\GENERIC.ICO\
	.\document.ico\
	.\SMALL.ICO\
	.\GENERIC.H

!IF  "$(CFG)" == "Win32 Release"

.\GENERIC.res :  $(SOURCE)  $(DEP_GENERI) $(INTDIR)
   $(RSC) /l 0x409 /fo$(INTDIR)/"GENERIC.res" /d "NDEBUG" /dNDEBUG,WIN32\
  $(SOURCE) 

!ELSEIF  "$(CFG)" == "Win32 Debug"

# PROP Exclude_From_Build 0
# ADD BASE RSC /l 0x409
# ADD RSC /l 0x0
# SUBTRACT RSC /x

.\GENERIC.res :  $(SOURCE)  $(DEP_GENERI) $(INTDIR)
   $(RSC) /l 0x0 /fo$(INTDIR)/"GENERIC.res" /d "_DEBUG" /d_DEBUG,WIN32\
  $(SOURCE) 

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\GENERIC.DEF
# End Source File
# End Group
# End Project
################################################################################
