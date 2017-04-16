# Microsoft Visual C++ Generated NMAKE File, Format Version 2.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Dynamic-Link Library" 0x0102

!IF "$(CFG)" == ""
CFG=NT kernel driver (debug)
!MESSAGE No configuration specified.  Defaulting to NT kernel driver (debug).
!ENDIF 

!IF "$(CFG)" != "NT kernel driver (release)" && "$(CFG)" !=\
 "NT kernel driver (debug)"
!MESSAGE Invalid configuration "$(CFG)" specified.
!MESSAGE You can specify a configuration when running NMAKE on this makefile
!MESSAGE by defining the macro CFG on the command line.  For example:
!MESSAGE 
!MESSAGE NMAKE /f "kbdcl.mak" CFG="NT kernel driver (debug)"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "NT kernel driver (release)" (based on\
 "Win32 (x86) Dynamic-Link Library")
!MESSAGE "NT kernel driver (debug)" (based on\
 "Win32 (x86) Dynamic-Link Library")
!MESSAGE 
!ERROR An invalid configuration is specified.
!ENDIF 

################################################################################
# Begin Project
# PROP Target_Last_Scanned "NT kernel driver (debug)"
MTL=MkTypLib.exe
CPP=cl.exe
RSC=rc.exe

!IF  "$(CFG)" == "NT kernel driver (release)"

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

ALL : \ddk\lib\i386\free\kbdclass.sys $(OUTDIR)/kbdcl.bsc

$(OUTDIR) : 
    if not exist $(OUTDIR)/nul mkdir $(OUTDIR)

# ADD BASE MTL /nologo /D "NDEBUG" /win32
# ADD MTL /nologo /D "NDEBUG" /win32
MTL_PROJ=/nologo /D "NDEBUG" /win32 
# ADD BASE CPP /nologo /MT /W3 /GX /YX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /FR /c
# ADD CPP /nologo /G4 /Gz /W3 /Ox /Gf /Gy /I "i386\\" /I "..\inc" /I "c:\ddk\inc" /D "NDEBUG" /D "_X86_" /D "i386" /D "STD_CALL" /D "CONDITION_HANDLING" /D "WIN32_LEAN_AND_MEAN" /D "NT_UP" /U "NT_INST" /FR /c
# SUBTRACT CPP /YX /Ot /Oa /Ow /Og /Oi /Os
CPP_PROJ=/nologo /G4 /Gz /W3 /Ox /Gf /Gy /I "i386\\" /I "..\inc" /I\
 "c:\ddk\inc" /D "NDEBUG" /D "_X86_" /D "i386" /D "STD_CALL" /D\
 "CONDITION_HANDLING" /D "WIN32_LEAN_AND_MEAN" /D "NT_UP" /U "NT_INST"\
 /FR$(INTDIR)/ /Fo$(INTDIR)/ /c 
CPP_OBJS=.\WinRel/
# ADD BASE RSC /l 0x409 /d "NDEBUG"
# ADD RSC /l 0x409 /d "NDEBUG"
RSC_PROJ=/l 0x409 /fo$(INTDIR)/"MOUCLASS.res" /d "NDEBUG" 
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
BSC32_FLAGS=/nologo /o$(OUTDIR)/"kbdcl.bsc" 
BSC32_SBRS= \
	$(INTDIR)/drvclass.sbr \
	$(INTDIR)/inpclass.sbr \
	$(INTDIR)/mclasses.sbr

$(OUTDIR)/kbdcl.bsc : $(OUTDIR)  $(BSC32_SBRS)
    $(BSC32) @<<
  $(BSC32_FLAGS) $(BSC32_SBRS)
<<

LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib /NOLOGO /SUBSYSTEM:windows /DLL /MACHINE:I386
# ADD LINK32 ntoskrnl.lib hal.lib /NOLOGO /BASE:0x10000 /ENTRY:"DriverEntry@8" /PDB:"mousecl.pdb" /MACHINE:I386 /NODEFAULTLIB /OUT:"c:\ddk\lib\i386\free\kbdclass.sys" /SUBSYSTEM:native
# SUBTRACT LINK32 /PDB:none
LINK32_FLAGS=ntoskrnl.lib hal.lib /NOLOGO /BASE:0x10000 /ENTRY:"DriverEntry@8"\
 /INCREMENTAL:no /PDB:"mousecl.pdb" /MACHINE:I386 /NODEFAULTLIB\
 /OUT:"c:\ddk\lib\i386\free\kbdclass.sys" /SUBSYSTEM:native  
DEF_FILE=
LINK32_OBJS= \
	$(INTDIR)/drvclass.obj \
	$(INTDIR)/MOUCLASS.res \
	$(INTDIR)/inpclass.obj \
	$(INTDIR)/mclasses.obj

\ddk\lib\i386\free\kbdclass.sys : $(OUTDIR)  $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ELSEIF  "$(CFG)" == "NT kernel driver (debug)"

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

ALL : \ddk\lib\i386\checked\kbdclass.sys $(OUTDIR)/kbdcl.map\
 $(OUTDIR)/kbdcl.bsc

$(OUTDIR) : 
    if not exist $(OUTDIR)/nul mkdir $(OUTDIR)

# ADD BASE MTL /nologo /D "_DEBUG" /win32
# ADD MTL /nologo /D "_DEBUG" /win32
MTL_PROJ=/nologo /D "_DEBUG" /win32 
# ADD BASE CPP /nologo /MT /W3 /GX /Zi /YX /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /FR /c
# ADD CPP /nologo /G4 /Gz /W3 /Z7 /Oi /Gf /Gy /I "i386\\" /I "..\inc" /I "c:\ddk\inc" /D "_DEBUG" /D "_X86_" /D "i386" /D "STD_CALL" /D "CONDITION_HANDLING" /D "WIN32_LEAN_AND_MEAN" /D "NT_UP" /D "RDRDBG" /D "SRVDBG" /D "DBG" /D "_IDWBUILD" /U "NT_INST" /FR /Zel /QI6  /c
CPP_PROJ=/nologo /G4 /Gz /W3 /Z7 /Oi /Gf /Gy /I "i386\\" /I "..\inc" /I\
 "c:\ddk\inc" /D "_DEBUG" /D "_X86_" /D "i386" /D "STD_CALL" /D\
 "CONDITION_HANDLING" /D "WIN32_LEAN_AND_MEAN" /D "NT_UP" /D "RDRDBG" /D\
 "SRVDBG" /D "DBG" /D "_IDWBUILD" /U "NT_INST" /FR$(INTDIR)/ /Fo$(INTDIR)/ /Zel\
 /QI6  /c 
CPP_OBJS=.\WinDebug/
# ADD BASE RSC /l 0x409 /d "_DEBUG"
# ADD RSC /l 0x409 /d "_DEBUG"
RSC_PROJ=/l 0x409 /fo$(INTDIR)/"MOUCLASS.res" /d "_DEBUG" 
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
BSC32_FLAGS=/nologo /o$(OUTDIR)/"kbdcl.bsc" 
BSC32_SBRS= \
	$(INTDIR)/drvclass.sbr \
	$(INTDIR)/inpclass.sbr \
	$(INTDIR)/mclasses.sbr

$(OUTDIR)/kbdcl.bsc : $(OUTDIR)  $(BSC32_SBRS)
    $(BSC32) @<<
  $(BSC32_FLAGS) $(BSC32_SBRS)
<<

LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib /NOLOGO /SUBSYSTEM:windows /DLL /DEBUG /MACHINE:I386
# ADD LINK32 ntoskrnl.lib hal.lib /NOLOGO /BASE:0x10000 /ENTRY:"DriverEntry@8" /PDB:none /MAP /DEBUG /DEBUGTYPE:both /MACHINE:I386 /NODEFAULTLIB /OUT:"c:\ddk\lib\i386\checked\kbdclass.sys" /DEBUG:full /SUBSYSTEM:native
LINK32_FLAGS=ntoskrnl.lib hal.lib /NOLOGO /BASE:0x10000 /ENTRY:"DriverEntry@8"\
 /PDB:none /MAP:$(INTDIR)/"kbdcl.map" /DEBUG /DEBUGTYPE:both /MACHINE:I386\
 /NODEFAULTLIB /OUT:"c:\ddk\lib\i386\checked\kbdclass.sys" /DEBUG:full\
 /SUBSYSTEM:native  
DEF_FILE=
LINK32_OBJS= \
	$(INTDIR)/drvclass.obj \
	$(INTDIR)/MOUCLASS.res \
	$(INTDIR)/inpclass.obj \
	$(INTDIR)/mclasses.obj

\ddk\lib\i386\checked\kbdclass.sys : $(OUTDIR)  $(DEF_FILE) $(LINK32_OBJS)
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

SOURCE=.\drvclass.cpp
DEP_DRVCL=\
	.\drvclass.h

$(INTDIR)/drvclass.obj :  $(SOURCE)  $(DEP_DRVCL) $(INTDIR)

# End Source File
################################################################################
# Begin Source File

SOURCE=.\MOUCLASS.RC
DEP_MOUCL=\
	.\moulog.rc

$(INTDIR)/MOUCLASS.res :  $(SOURCE)  $(DEP_MOUCL) $(INTDIR)
   $(RSC) $(RSC_PROJ)  $(SOURCE) 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\inpclass.cpp
DEP_INPCL=\
	.\mouclass.h\
	.\moulog.h\
	.\kbdclass.h\
	.\kbdlog.h\
	.\drvclass.h

$(INTDIR)/inpclass.obj :  $(SOURCE)  $(DEP_INPCL) $(INTDIR)

# End Source File
################################################################################
# Begin Source File

SOURCE=.\mclasses.cpp
DEP_MCLAS=\
	.\mouclass.h\
	.\moulog.h\
	.\kbdclass.h\
	.\kbdlog.h\
	.\drvclass.h

$(INTDIR)/mclasses.obj :  $(SOURCE)  $(DEP_MCLAS) $(INTDIR)

# End Source File
# End Group
# End Project
################################################################################
