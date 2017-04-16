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
!MESSAGE NMAKE /f "MTTTY.mak" CFG="Win32 Debug"
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

ALL : $(OUTDIR)/MTTTY.exe $(OUTDIR)/MTTTY.bsc

$(OUTDIR) : 
    if not exist $(OUTDIR)/nul mkdir $(OUTDIR)

# ADD BASE MTL /nologo /D "NDEBUG" /win32
# ADD MTL /nologo /D "NDEBUG" /win32
MTL_PROJ=/nologo /D "NDEBUG" /win32 
# ADD BASE CPP /nologo /W3 /GX /YX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /FR /c
# ADD CPP /nologo /MD /W3 /GX /YX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /FR /c
CPP_PROJ=/nologo /MD /W3 /GX /YX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS"\
 /FR$(INTDIR)/ /Fp$(OUTDIR)/"MTTTY.pch" /Fo$(INTDIR)/ /c 
CPP_OBJS=.\WinRel/
# ADD BASE RSC /l 0x409 /d "NDEBUG"
# ADD RSC /l 0x409 /d "NDEBUG"
RSC_PROJ=/l 0x409 /fo$(INTDIR)/"MTTTY.res" /d "NDEBUG" 
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
BSC32_FLAGS=/nologo /o$(OUTDIR)/"MTTTY.bsc" 
BSC32_SBRS= \
	$(INTDIR)/MTTTY.sbr \
	$(INTDIR)/Status.sbr \
	$(INTDIR)/Reader.sbr \
	$(INTDIR)/Error.sbr \
	$(INTDIR)/About.sbr \
	$(INTDIR)/Settings.sbr \
	$(INTDIR)/Init.sbr \
	$(INTDIR)/Writer.sbr \
	$(INTDIR)/Transfer.sbr \
	$(INTDIR)/ReadStat.sbr

$(OUTDIR)/MTTTY.bsc : $(OUTDIR)  $(BSC32_SBRS)
    $(BSC32) @<<
  $(BSC32_FLAGS) $(BSC32_SBRS)
<<

LINK32=link.exe
# ADD BASE LINK32 winmm.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /NOLOGO /SUBSYSTEM:windows /MACHINE:I386
# ADD LINK32 winmm.lib comctl32.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /NOLOGO /SUBSYSTEM:windows /MACHINE:I386
LINK32_FLAGS=winmm.lib comctl32.lib kernel32.lib user32.lib gdi32.lib winspool.lib\
 comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib\
 odbc32.lib odbccp32.lib /NOLOGO /SUBSYSTEM:windows /INCREMENTAL:no\
 /PDB:$(OUTDIR)/"MTTTY.pdb" /MACHINE:I386 /OUT:$(OUTDIR)/"MTTTY.exe" 
DEF_FILE=
LINK32_OBJS= \
	$(INTDIR)/MTTTY.obj \
	$(INTDIR)/Status.obj \
	$(INTDIR)/Reader.obj \
	$(INTDIR)/Error.obj \
	$(INTDIR)/About.obj \
	$(INTDIR)/MTTTY.res \
	$(INTDIR)/Settings.obj \
	$(INTDIR)/Init.obj \
	$(INTDIR)/Writer.obj \
	$(INTDIR)/Transfer.obj \
	$(INTDIR)/ReadStat.obj

$(OUTDIR)/MTTTY.exe : $(OUTDIR)  $(DEF_FILE) $(LINK32_OBJS)
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

ALL : $(OUTDIR)/MTTTY.exe $(OUTDIR)/MTTTY.bsc

$(OUTDIR) : 
    if not exist $(OUTDIR)/nul mkdir $(OUTDIR)

# ADD BASE MTL /nologo /D "_DEBUG" /win32
# ADD MTL /nologo /D "_DEBUG" /win32
MTL_PROJ=/nologo /D "_DEBUG" /win32 
# ADD BASE CPP /nologo /W3 /GX /Zi /YX /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /FR /c
# ADD CPP /nologo /MD /W3 /GX /Zi /YX /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /FR /c
CPP_PROJ=/nologo /MD /W3 /GX /Zi /YX /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS"\
 /FR$(INTDIR)/ /Fp$(OUTDIR)/"MTTTY.pch" /Fo$(INTDIR)/ /Fd$(OUTDIR)/"MTTTY.pdb"\
 /c 
CPP_OBJS=.\WinDebug/
# ADD BASE RSC /l 0x409 /d "_DEBUG"
# ADD RSC /l 0x409 /d "_DEBUG"
RSC_PROJ=/l 0x409 /fo$(INTDIR)/"MTTTY.res" /d "_DEBUG" 
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
BSC32_FLAGS=/nologo /o$(OUTDIR)/"MTTTY.bsc" 
BSC32_SBRS= \
	$(INTDIR)/MTTTY.sbr \
	$(INTDIR)/Status.sbr \
	$(INTDIR)/Reader.sbr \
	$(INTDIR)/Error.sbr \
	$(INTDIR)/About.sbr \
	$(INTDIR)/Settings.sbr \
	$(INTDIR)/Init.sbr \
	$(INTDIR)/Writer.sbr \
	$(INTDIR)/Transfer.sbr \
	$(INTDIR)/ReadStat.sbr

$(OUTDIR)/MTTTY.bsc : $(OUTDIR)  $(BSC32_SBRS)
    $(BSC32) @<<
  $(BSC32_FLAGS) $(BSC32_SBRS)
<<

LINK32=link.exe
# ADD BASE LINK32 winmm.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /NOLOGO /SUBSYSTEM:windows /DEBUG /MACHINE:I386
# ADD LINK32 winmm.lib comctl32.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /NOLOGO /SUBSYSTEM:windows /DEBUG /MACHINE:I386
LINK32_FLAGS=winmm.lib comctl32.lib kernel32.lib user32.lib gdi32.lib winspool.lib\
 comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib\
 odbc32.lib odbccp32.lib /NOLOGO /SUBSYSTEM:windows /INCREMENTAL:yes\
 /PDB:$(OUTDIR)/"MTTTY.pdb" /DEBUG /MACHINE:I386 /OUT:$(OUTDIR)/"MTTTY.exe" 
DEF_FILE=
LINK32_OBJS= \
	$(INTDIR)/MTTTY.obj \
	$(INTDIR)/Status.obj \
	$(INTDIR)/Reader.obj \
	$(INTDIR)/Error.obj \
	$(INTDIR)/About.obj \
	$(INTDIR)/MTTTY.res \
	$(INTDIR)/Settings.obj \
	$(INTDIR)/Init.obj \
	$(INTDIR)/Writer.obj \
	$(INTDIR)/Transfer.obj \
	$(INTDIR)/ReadStat.obj

$(OUTDIR)/MTTTY.exe : $(OUTDIR)  $(DEF_FILE) $(LINK32_OBJS)
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

SOURCE=.\MTTTY.c
DEP_MTTTY=\
	.\MTTTY.h\
	.\TTYInfo.h

$(INTDIR)/MTTTY.obj :  $(SOURCE)  $(DEP_MTTTY) $(INTDIR)

# End Source File
################################################################################
# Begin Source File

SOURCE=.\Status.c
DEP_STATU=\
	.\MTTTY.h\
	.\TTYInfo.h

$(INTDIR)/Status.obj :  $(SOURCE)  $(DEP_STATU) $(INTDIR)

# End Source File
################################################################################
# Begin Source File

SOURCE=.\Reader.c
DEP_READE=\
	.\MTTTY.h\
	.\TTYInfo.h

$(INTDIR)/Reader.obj :  $(SOURCE)  $(DEP_READE) $(INTDIR)

# End Source File
################################################################################
# Begin Source File

SOURCE=.\Error.c
DEP_ERROR=\
	.\MTTTY.h\
	.\TTYInfo.h

$(INTDIR)/Error.obj :  $(SOURCE)  $(DEP_ERROR) $(INTDIR)

# End Source File
################################################################################
# Begin Source File

SOURCE=.\About.c
DEP_ABOUT=\
	.\MTTTY.h\
	.\TTYInfo.h

$(INTDIR)/About.obj :  $(SOURCE)  $(DEP_ABOUT) $(INTDIR)

# End Source File
################################################################################
# Begin Source File

SOURCE=.\MTTTY.RC
DEP_MTTTY_=\
	.\MTTTY.ICO\
	.\MTTTY2.ICO\
	.\MTTTY3.ICO\
	.\MTTTY4.ICO

$(INTDIR)/MTTTY.res :  $(SOURCE)  $(DEP_MTTTY_) $(INTDIR)
   $(RSC) $(RSC_PROJ)  $(SOURCE) 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\Settings.c
DEP_SETTI=\
	.\MTTTY.h\
	.\TTYInfo.h

$(INTDIR)/Settings.obj :  $(SOURCE)  $(DEP_SETTI) $(INTDIR)

# End Source File
################################################################################
# Begin Source File

SOURCE=.\Init.c
DEP_INIT_=\
	.\MTTTY.h\
	.\TTYInfo.h

$(INTDIR)/Init.obj :  $(SOURCE)  $(DEP_INIT_) $(INTDIR)

# End Source File
################################################################################
# Begin Source File

SOURCE=.\Writer.c
DEP_WRITE=\
	.\MTTTY.h\
	.\TTYInfo.h

$(INTDIR)/Writer.obj :  $(SOURCE)  $(DEP_WRITE) $(INTDIR)

# End Source File
################################################################################
# Begin Source File

SOURCE=.\Transfer.c
DEP_TRANS=\
	.\MTTTY.h\
	.\TTYInfo.h

$(INTDIR)/Transfer.obj :  $(SOURCE)  $(DEP_TRANS) $(INTDIR)

# End Source File
################################################################################
# Begin Source File

SOURCE=.\ReadStat.c
DEP_READS=\
	.\MTTTY.h\
	.\TTYInfo.h

$(INTDIR)/ReadStat.obj :  $(SOURCE)  $(DEP_READS) $(INTDIR)

# End Source File
# End Group
# End Project
################################################################################
