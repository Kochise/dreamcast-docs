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
!MESSAGE NMAKE /f "COMMCHAT.MAK" CFG="Win32 Debug"
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
# PROP Target_Last_Scanned "Win32 Release"
MTL=MkTypLib.exe
CPP=cl.exe
RSC=rc.exe

!IF  "$(CFG)" == "Win32 Release"

# PROP BASE Use_MFC 1
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "WinRel"
# PROP BASE Intermediate_Dir "WinRel"
# PROP Use_MFC 1
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "WinRel"
# PROP Intermediate_Dir "WinRel"
OUTDIR=.\WinRel
INTDIR=.\WinRel

ALL : $(OUTDIR)/COMMCHAT.exe $(OUTDIR)/COMMCHAT.bsc

$(OUTDIR) : 
    if not exist $(OUTDIR)/nul mkdir $(OUTDIR)

# ADD BASE MTL /nologo /D "NDEBUG" /win32
# ADD MTL /nologo /D "NDEBUG" /win32
MTL_PROJ=/nologo /D "NDEBUG" /win32 
# ADD BASE CPP /nologo /MT /W3 /GX /YX /Ox /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_X86_" /D "_MBCS" /FR /c
# ADD CPP /nologo /MT /W3 /GX /YX /Ox /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_X86_" /D "_MBCS" /FR /c
CPP_PROJ=/nologo /MT /W3 /GX /YX /Ox /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D\
 "_X86_" /D "_MBCS" /FR$(INTDIR)/ /Fp$(OUTDIR)/"COMMCHAT.pch" /Fo$(INTDIR)/ /c 
CPP_OBJS=.\WinRel/
# ADD BASE RSC /l 0x409 /d "NDEBUG"
# ADD RSC /l 0x409 /d "NDEBUG"
RSC_PROJ=/l 0x409 /fo$(INTDIR)/"COMMCHAT.res" /d "NDEBUG" 
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
BSC32_FLAGS=/nologo /o$(OUTDIR)/"COMMCHAT.bsc" 
BSC32_SBRS= \
	$(INTDIR)/BROWSEDI.SBR \
	$(INTDIR)/COMCLASS.SBR \
	$(INTDIR)/COMMCDOC.SBR \
	$(INTDIR)/COMMCHAT.SBR \
	$(INTDIR)/COMMCVW.SBR \
	$(INTDIR)/MAINFRM.SBR \
	$(INTDIR)/NPIPE.SBR \
	$(INTDIR)/PROTOCOL.SBR \
	$(INTDIR)/SPLITFRM.SBR \
	$(INTDIR)/STDAFX.SBR \
	$(INTDIR)/SUBSPLIT.SBR \
	$(INTDIR)/SOCKETS.SBR \
	$(INTDIR)/netbios.sbr \
	$(INTDIR)/cncb.sbr

$(OUTDIR)/COMMCHAT.bsc : $(OUTDIR)  $(BSC32_SBRS)
    $(BSC32) @<<
  $(BSC32_FLAGS) $(BSC32_SBRS)
<<

LINK32=link.exe
# ADD BASE LINK32 nafxcw.lib olecli32.lib olesvr32.lib wsock32.lib /NOLOGO /SUBSYSTEM:windows /MACHINE:IX86
# ADD LINK32 nafxcw.lib wsock32.lib netapi32.lib /NOLOGO /SUBSYSTEM:windows /MACHINE:IX86
LINK32_FLAGS=nafxcw.lib wsock32.lib netapi32.lib /NOLOGO /SUBSYSTEM:windows\
 /INCREMENTAL:no /PDB:$(OUTDIR)/"COMMCHAT.pdb" /MACHINE:IX86\
 /OUT:$(OUTDIR)/"COMMCHAT.exe" 
DEF_FILE=
LINK32_OBJS= \
	$(INTDIR)/BROWSEDI.OBJ \
	$(INTDIR)/COMCLASS.OBJ \
	$(INTDIR)/COMMCDOC.OBJ \
	$(INTDIR)/COMMCHAT.OBJ \
	$(INTDIR)/COMMCVW.OBJ \
	$(INTDIR)/MAINFRM.OBJ \
	$(INTDIR)/NPIPE.OBJ \
	$(INTDIR)/PROTOCOL.OBJ \
	$(INTDIR)/SPLITFRM.OBJ \
	$(INTDIR)/STDAFX.OBJ \
	$(INTDIR)/SUBSPLIT.OBJ \
	$(INTDIR)/COMMCHAT.res \
	$(INTDIR)/SOCKETS.OBJ \
	$(INTDIR)/netbios.obj \
	$(INTDIR)/cncb.obj

$(OUTDIR)/COMMCHAT.exe : $(OUTDIR)  $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ELSEIF  "$(CFG)" == "Win32 Debug"

# PROP BASE Use_MFC 1
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "WinDebug"
# PROP BASE Intermediate_Dir "WinDebug"
# PROP Use_MFC 1
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "WinDebug"
# PROP Intermediate_Dir "WinDebug"
OUTDIR=.\WinDebug
INTDIR=.\WinDebug

ALL : $(OUTDIR)/COMMCHAT.exe $(OUTDIR)/COMMCHAT.bsc

$(OUTDIR) : 
    if not exist $(OUTDIR)/nul mkdir $(OUTDIR)

# ADD BASE MTL /nologo /D "_DEBUG" /win32
# ADD MTL /nologo /D "_DEBUG" /win32
MTL_PROJ=/nologo /D "_DEBUG" /win32 
# ADD BASE CPP /nologo /MT /W3 /GX /Zi /YX /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_X86_" /D "_MBCS" /FR /c
# ADD CPP /nologo /MT /W3 /GX /Zi /YX /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_X86_" /D "_MBCS" /FR /c
CPP_PROJ=/nologo /MT /W3 /GX /Zi /YX /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS"\
 /D "_X86_" /D "_MBCS" /FR$(INTDIR)/ /Fp$(OUTDIR)/"COMMCHAT.pch" /Fo$(INTDIR)/\
 /Fd$(OUTDIR)/"COMMCHAT.pdb" /c 
CPP_OBJS=.\WinDebug/
# ADD BASE RSC /l 0x409 /d "_DEBUG"
# ADD RSC /l 0x409 /d "_DEBUG"
RSC_PROJ=/l 0x409 /fo$(INTDIR)/"COMMCHAT.res" /d "_DEBUG" 
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
BSC32_FLAGS=/nologo /o$(OUTDIR)/"COMMCHAT.bsc" 
BSC32_SBRS= \
	$(INTDIR)/BROWSEDI.SBR \
	$(INTDIR)/COMCLASS.SBR \
	$(INTDIR)/COMMCDOC.SBR \
	$(INTDIR)/COMMCHAT.SBR \
	$(INTDIR)/COMMCVW.SBR \
	$(INTDIR)/MAINFRM.SBR \
	$(INTDIR)/NPIPE.SBR \
	$(INTDIR)/PROTOCOL.SBR \
	$(INTDIR)/SPLITFRM.SBR \
	$(INTDIR)/STDAFX.SBR \
	$(INTDIR)/SUBSPLIT.SBR \
	$(INTDIR)/SOCKETS.SBR \
	$(INTDIR)/netbios.sbr \
	$(INTDIR)/cncb.sbr

$(OUTDIR)/COMMCHAT.bsc : $(OUTDIR)  $(BSC32_SBRS)
    $(BSC32) @<<
  $(BSC32_FLAGS) $(BSC32_SBRS)
<<

LINK32=link.exe
# ADD BASE LINK32 nafxcwd.lib olecli32.lib olesvr32.lib wsock32.lib /NOLOGO /SUBSYSTEM:windows /DEBUG /MACHINE:IX86
# ADD LINK32 nafxcwd.lib wsock32.lib netapi32.lib /NOLOGO /SUBSYSTEM:windows /DEBUG /MACHINE:IX86
LINK32_FLAGS=nafxcwd.lib wsock32.lib netapi32.lib /NOLOGO /SUBSYSTEM:windows\
 /INCREMENTAL:yes /PDB:$(OUTDIR)/"COMMCHAT.pdb" /DEBUG /MACHINE:IX86\
 /OUT:$(OUTDIR)/"COMMCHAT.exe" 
DEF_FILE=
LINK32_OBJS= \
	$(INTDIR)/BROWSEDI.OBJ \
	$(INTDIR)/COMCLASS.OBJ \
	$(INTDIR)/COMMCDOC.OBJ \
	$(INTDIR)/COMMCHAT.OBJ \
	$(INTDIR)/COMMCVW.OBJ \
	$(INTDIR)/MAINFRM.OBJ \
	$(INTDIR)/NPIPE.OBJ \
	$(INTDIR)/PROTOCOL.OBJ \
	$(INTDIR)/SPLITFRM.OBJ \
	$(INTDIR)/STDAFX.OBJ \
	$(INTDIR)/SUBSPLIT.OBJ \
	$(INTDIR)/COMMCHAT.res \
	$(INTDIR)/SOCKETS.OBJ \
	$(INTDIR)/netbios.obj \
	$(INTDIR)/cncb.obj

$(OUTDIR)/COMMCHAT.exe : $(OUTDIR)  $(DEF_FILE) $(LINK32_OBJS)
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

SOURCE=.\BROWSEDI.CPP
DEP_BROWS=\
	.\STDAFX.H\
	.\PROTOCOL.H\
	.\commchat.h\
	.\BROWSEDI.H

$(INTDIR)/BROWSEDI.OBJ :  $(SOURCE)  $(DEP_BROWS) $(INTDIR)

# End Source File
################################################################################
# Begin Source File

SOURCE=.\COMCLASS.CPP
DEP_COMCL=\
	.\STDAFX.H\
	.\COMCLASS.H

$(INTDIR)/COMCLASS.OBJ :  $(SOURCE)  $(DEP_COMCL) $(INTDIR)

# End Source File
################################################################################
# Begin Source File

SOURCE=.\COMMCDOC.CPP
DEP_COMMC=\
	.\STDAFX.H\
	.\PROTOCOL.H\
	.\commchat.h\
	.\COMCLASS.H\
	.\COMMCDOC.H\
	.\COMMCVW.H

$(INTDIR)/COMMCDOC.OBJ :  $(SOURCE)  $(DEP_COMMC) $(INTDIR)

# End Source File
################################################################################
# Begin Source File

SOURCE=.\COMMCHAT.CPP
DEP_COMMCH=\
	.\STDAFX.H\
	.\COMCLASS.H\
	.\NPIPE.H\
	.\SOCKETS.H\
	.\netbios.h\
	.\PROTOCOL.H\
	.\commchat.h\
	.\MAINFRM.H\
	.\COMMCDOC.H\
	.\COMMCVW.H\
	.\SUBSPLIT.H\
	.\SPLITFRM.H\
	.\BROWSEDI.H\
	.\cncb.h

$(INTDIR)/COMMCHAT.OBJ :  $(SOURCE)  $(DEP_COMMCH) $(INTDIR)

# End Source File
################################################################################
# Begin Source File

SOURCE=.\COMMCVW.CPP
DEP_COMMCV=\
	.\STDAFX.H\
	.\PROTOCOL.H\
	.\commchat.h\
	.\COMCLASS.H\
	.\COMMCDOC.H\
	.\COMMCVW.H

$(INTDIR)/COMMCVW.OBJ :  $(SOURCE)  $(DEP_COMMCV) $(INTDIR)

# End Source File
################################################################################
# Begin Source File

SOURCE=.\MAINFRM.CPP
DEP_MAINF=\
	.\STDAFX.H\
	.\PROTOCOL.H\
	.\commchat.h\
	.\MAINFRM.H

$(INTDIR)/MAINFRM.OBJ :  $(SOURCE)  $(DEP_MAINF) $(INTDIR)

# End Source File
################################################################################
# Begin Source File

SOURCE=.\NPIPE.CPP
DEP_NPIPE=\
	.\STDAFX.H\
	.\COMCLASS.H\
	.\NPIPE.H

$(INTDIR)/NPIPE.OBJ :  $(SOURCE)  $(DEP_NPIPE) $(INTDIR)

# End Source File
################################################################################
# Begin Source File

SOURCE=.\PROTOCOL.CPP
DEP_PROTO=\
	.\STDAFX.H\
	.\COMCLASS.H\
	.\PROTOCOL.H

$(INTDIR)/PROTOCOL.OBJ :  $(SOURCE)  $(DEP_PROTO) $(INTDIR)

# End Source File
################################################################################
# Begin Source File

SOURCE=.\SPLITFRM.CPP
DEP_SPLIT=\
	.\STDAFX.H\
	.\SUBSPLIT.H\
	.\COMCLASS.H\
	.\PROTOCOL.H\
	.\SPLITFRM.H\
	.\COMMCDOC.H\
	.\COMMCVW.H

$(INTDIR)/SPLITFRM.OBJ :  $(SOURCE)  $(DEP_SPLIT) $(INTDIR)

# End Source File
################################################################################
# Begin Source File

SOURCE=.\STDAFX.CPP
DEP_STDAF=\
	.\STDAFX.H

$(INTDIR)/STDAFX.OBJ :  $(SOURCE)  $(DEP_STDAF) $(INTDIR)

# End Source File
################################################################################
# Begin Source File

SOURCE=.\SUBSPLIT.CPP
DEP_SUBSP=\
	.\STDAFX.H\
	.\PROTOCOL.H\
	.\commchat.h\
	.\SUBSPLIT.H\
	.\COMCLASS.H\
	.\COMMCDOC.H\
	.\COMMCVW.H

$(INTDIR)/SUBSPLIT.OBJ :  $(SOURCE)  $(DEP_SUBSP) $(INTDIR)

# End Source File
################################################################################
# Begin Source File

SOURCE=.\COMMCHAT.RC
DEP_COMMCHA=\
	.\res\COMMCHAT.ICO\
	.\res\COMMCDOC.ICO\
	.\res\TOOLBAR.BMP\
	.\res\COMMCHAT.RC2

$(INTDIR)/COMMCHAT.res :  $(SOURCE)  $(DEP_COMMCHA) $(INTDIR)
   $(RSC) $(RSC_PROJ)  $(SOURCE) 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\SOCKETS.CPP
DEP_SOCKE=\
	.\STDAFX.H\
	.\COMCLASS.H\
	.\SOCKETS.H

$(INTDIR)/SOCKETS.OBJ :  $(SOURCE)  $(DEP_SOCKE) $(INTDIR)

# End Source File
################################################################################
# Begin Source File

SOURCE=.\netbios.cpp
DEP_NETBI=\
	.\STDAFX.H\
	.\COMCLASS.H\
	.\netbios.h\
	.\cncb.h

$(INTDIR)/netbios.obj :  $(SOURCE)  $(DEP_NETBI) $(INTDIR)

# End Source File
################################################################################
# Begin Source File

SOURCE=.\cncb.cpp
DEP_CNCB_=\
	.\cncb.h

$(INTDIR)/cncb.obj :  $(SOURCE)  $(DEP_CNCB_) $(INTDIR)

# End Source File
# End Group
# End Project
################################################################################
