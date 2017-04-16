# Microsoft Visual C++ Generated NMAKE File, Format Version 2.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Dynamic-Link Library" 0x0102

!IF "$(CFG)" == ""
CFG=Win32 ANSI Debug
!MESSAGE No configuration specified.  Defaulting to Win32 ANSI Debug.
!ENDIF 

!IF "$(CFG)" != "Win32 ANSI Release" && "$(CFG)" != "Win32 ANSI Debug" &&\
 "$(CFG)" != "Win32 Unicode Release" && "$(CFG)" != "Win32 Unicode Debug"
!MESSAGE Invalid configuration "$(CFG)" specified.
!MESSAGE You can specify a configuration when running NMAKE on this makefile
!MESSAGE by defining the macro CFG on the command line.  For example:
!MESSAGE 
!MESSAGE NMAKE /f "CBACK32.MAK" CFG="Win32 ANSI Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "Win32 ANSI Release" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE "Win32 ANSI Debug" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE "Win32 Unicode Release" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE "Win32 Unicode Debug" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE 
!ERROR An invalid configuration is specified.
!ENDIF 

################################################################################
# Begin Project
# PROP Target_Last_Scanned "Win32 ANSI Debug"
MTL=MkTypLib.exe
CPP=cl.exe
RSC=rc.exe

!IF  "$(CFG)" == "Win32 ANSI Release"

# PROP BASE Use_MFC 2
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Classwizard_Name "cback.clw"
# PROP Use_MFC 2
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "obj32"
# PROP Intermediate_Dir "obj32"
# PROP Classwizard_Name "cback.clw"
OUTDIR=.\obj32
INTDIR=.\obj32

ALL : MTL_TLBS $(OUTDIR)/cback.ocx $(OUTDIR)/cback.bsc

$(OUTDIR) : 
    if not exist $(OUTDIR)/nul mkdir $(OUTDIR)

# ADD BASE MTL /nologo /D "NDEBUG" /D "_WIN32" /win32
# ADD MTL /nologo /D "NDEBUG" /D "_WIN32" /win32
MTL_PROJ=/nologo /D "NDEBUG" /D "_WIN32" /win32 

MTL_TLBS : $(OUTDIR)/CBACK.tlb
# ADD BASE CPP /nologo /MD /W3 /GX /Ox /D "NDEBUG" /D "_MBCS" /D "_WINDOWS" /D "_AFXDLL" /D "_AFXCTL" /D "_WINDLL" /FR /Yu"stdafx.h" /c
# ADD CPP /nologo /MD /W3 /GX /Ox /D "NDEBUG" /D "_MBCS" /D "_WINDOWS" /D "_AFXDLL" /D "_AFXCTL" /D "_WINDLL" /FR /Yu"stdafx.h" /c
CPP_PROJ=/nologo /MD /W3 /GX /Ox /D "NDEBUG" /D "_MBCS" /D "_WINDOWS" /D\
 "_AFXDLL" /D "_AFXCTL" /D "_WINDLL" /FR$(INTDIR)/ /Fp$(OUTDIR)/"CBACK32.pch"\
 /Yu"stdafx.h" /Fo$(INTDIR)/ /c 
CPP_OBJS=.\obj32/
# ADD BASE RSC /l 0x409 /i "$(OUTDIR)" /d "NDEBUG" /d "_WIN32"
# ADD RSC /l 0x409 /i "$(OUTDIR)" /d "NDEBUG" /d "_WIN32"
RSC_PROJ=/l 0x409 /fo$(INTDIR)/"CBACK.res" /i "$(OUTDIR)" /d "NDEBUG" /d\
 "_WIN32" 
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo /o"obj32/cback.bsc"
# SUBTRACT BASE BSC32 /Iu
# ADD BSC32 /nologo /o"obj32/cback.bsc"
# SUBTRACT BSC32 /Iu
BSC32_FLAGS=/nologo /o"obj32/cback.bsc" 
BSC32_SBRS= \
	$(INTDIR)/STDAFX.SBR \
	$(INTDIR)/CBACK.SBR \
	$(INTDIR)/CALLBCTL.SBR \
	$(INTDIR)/CALLBPPG.SBR

$(OUTDIR)/cback.bsc : $(OUTDIR)  $(BSC32_SBRS)
    $(BSC32) @<<
  $(BSC32_FLAGS) $(BSC32_SBRS)
<<

LINK32=link.exe
# ADD BASE LINK32 ocs30.lib /NOLOGO /SUBSYSTEM:windows /DLL /MACHINE:IX86 /OUT:"obj32/cback.ocx"
# SUBTRACT BASE LINK32 /PDB:none /NODEFAULTLIB
# ADD LINK32 ocs30.lib /NOLOGO /SUBSYSTEM:windows /DLL /MACHINE:IX86 /OUT:"obj32/cback.ocx"
# SUBTRACT LINK32 /PDB:none /NODEFAULTLIB
LINK32_FLAGS=ocs30.lib /NOLOGO /SUBSYSTEM:windows /DLL /INCREMENTAL:no\
 /PDB:$(OUTDIR)/"CBACK32.pdb" /MACHINE:IX86 /DEF:".\CBACK32.DEF"\
 /OUT:"obj32/cback.ocx" /IMPLIB:$(OUTDIR)/"CBACK32.lib" 
DEF_FILE=.\CBACK32.DEF
LINK32_OBJS= \
	$(INTDIR)/STDAFX.OBJ \
	$(INTDIR)/CBACK.OBJ \
	$(INTDIR)/CALLBCTL.OBJ \
	$(INTDIR)/CALLBPPG.OBJ \
	$(INTDIR)/CBACK.res

$(OUTDIR)/cback.ocx : $(OUTDIR)  $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ELSEIF  "$(CFG)" == "Win32 ANSI Debug"

# PROP BASE Use_MFC 2
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Classwizard_Name "cback.clw"
# PROP Use_MFC 2
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "objd32"
# PROP Intermediate_Dir "objd32"
# PROP Classwizard_Name "cback.clw"
OUTDIR=.\objd32
INTDIR=.\objd32

ALL : MTL_TLBS $(OUTDIR)/cback.ocx $(OUTDIR)/cback.bsc

$(OUTDIR) : 
    if not exist $(OUTDIR)/nul mkdir $(OUTDIR)

# ADD BASE MTL /nologo /D "_DEBUG" /D "_WIN32" /win32
# ADD MTL /nologo /D "_DEBUG" /D "_WIN32" /win32
MTL_PROJ=/nologo /D "_DEBUG" /D "_WIN32" /win32 

MTL_TLBS : $(OUTDIR)/CBACK.TLB
# ADD BASE CPP /nologo /MD /W3 /GX /Zi /Od /D "_DEBUG" /D "_MBCS" /D "_WINDOWS" /D "_AFXDLL" /D "_AFXCTL" /D "_WINDLL" /FR /Yu"stdafx.h" /c
# ADD CPP /nologo /MD /W3 /GX /Zi /Od /D "_DEBUG" /D "_MBCS" /D "_WINDOWS" /D "_AFXDLL" /D "_AFXCTL" /D "_WINDLL" /FR /Yu"stdafx.h" /c
# SUBTRACT CPP /WX
CPP_PROJ=/nologo /MD /W3 /GX /Zi /Od /D "_DEBUG" /D "_MBCS" /D "_WINDOWS" /D\
 "_AFXDLL" /D "_AFXCTL" /D "_WINDLL" /FR$(INTDIR)/ /Fp$(OUTDIR)/"CBACK32.pch"\
 /Yu"stdafx.h" /Fo$(INTDIR)/ /Fd$(OUTDIR)/"CBACK32.pdb" /c 
CPP_OBJS=.\objd32/
# ADD BASE RSC /l 0x409 /i "$(OUTDIR)" /d "_DEBUG" /d "_WIN32"
# ADD RSC /l 0x409 /i "$(OUTDIR)" /d "_DEBUG" /d "_WIN32"
RSC_PROJ=/l 0x409 /fo$(INTDIR)/"CBACK.res" /i "$(OUTDIR)" /d "_DEBUG" /d\
 "_WIN32" 
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo /o"objd32/cback.bsc"
# SUBTRACT BASE BSC32 /Iu
# ADD BSC32 /nologo /o"objd32/cback.bsc"
# SUBTRACT BSC32 /Iu
BSC32_FLAGS=/nologo /o"objd32/cback.bsc" 
BSC32_SBRS= \
	$(INTDIR)/STDAFX.SBR \
	$(INTDIR)/CBACK.SBR \
	$(INTDIR)/CALLBCTL.SBR \
	$(INTDIR)/CALLBPPG.SBR

$(OUTDIR)/cback.bsc : $(OUTDIR)  $(BSC32_SBRS)
    $(BSC32) @<<
  $(BSC32_FLAGS) $(BSC32_SBRS)
<<

LINK32=link.exe
# ADD BASE LINK32 ocs30d.lib /NOLOGO /SUBSYSTEM:windows /DLL /DEBUG /MACHINE:IX86 /OUT:"objd32/cback.ocx"
# SUBTRACT BASE LINK32 /PDB:none /NODEFAULTLIB
# ADD LINK32 ocs30d.lib /NOLOGO /SUBSYSTEM:windows /DLL /DEBUG /MACHINE:IX86 /OUT:"objd32/cback.ocx"
# SUBTRACT LINK32 /PDB:none /NODEFAULTLIB
LINK32_FLAGS=ocs30d.lib /NOLOGO /SUBSYSTEM:windows /DLL /INCREMENTAL:yes\
 /PDB:$(OUTDIR)/"CBACK32.pdb" /DEBUG /MACHINE:IX86 /DEF:".\CBACK32.DEF"\
 /OUT:"objd32/cback.ocx" /IMPLIB:$(OUTDIR)/"CBACK32.lib" 
DEF_FILE=.\CBACK32.DEF
LINK32_OBJS= \
	$(INTDIR)/STDAFX.OBJ \
	$(INTDIR)/CBACK.OBJ \
	$(INTDIR)/CALLBCTL.OBJ \
	$(INTDIR)/CALLBPPG.OBJ \
	$(INTDIR)/CBACK.res

$(OUTDIR)/cback.ocx : $(OUTDIR)  $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ELSEIF  "$(CFG)" == "Win32 Unicode Release"

# PROP BASE Use_MFC 2
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Classwizard_Name "cback.clw"
# PROP Use_MFC 2
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "obju32"
# PROP Intermediate_Dir "obju32"
# PROP Classwizard_Name "cback.clw"
OUTDIR=.\obju32
INTDIR=.\obju32

ALL : MTL_TLBS $(OUTDIR)/cback.ocx $(OUTDIR)/cback.bsc

$(OUTDIR) : 
    if not exist $(OUTDIR)/nul mkdir $(OUTDIR)

# ADD BASE MTL /nologo /D "NDEBUG" /D "_UNICODE" /D "_WIN32" /win32
# ADD MTL /nologo /D "NDEBUG" /D "_UNICODE" /D "_WIN32" /win32
MTL_PROJ=/nologo /D "NDEBUG" /D "_UNICODE" /D "_WIN32" /win32 

MTL_TLBS : $(OUTDIR)/CBACK.tlb
# ADD BASE CPP /nologo /MD /W3 /GX /Ox /D "NDEBUG" /D "_UNICODE" /D "_WINDOWS" /D "_AFXDLL" /D "_AFXCTL" /D "_WINDLL" /FR /Yu"stdafx.h" /c
# ADD CPP /nologo /MD /W3 /GX /Ox /D "NDEBUG" /D "_UNICODE" /D "_WINDOWS" /D "_AFXDLL" /D "_AFXCTL" /D "_WINDLL" /FR /Yu"stdafx.h" /c
CPP_PROJ=/nologo /MD /W3 /GX /Ox /D "NDEBUG" /D "_UNICODE" /D "_WINDOWS" /D\
 "_AFXDLL" /D "_AFXCTL" /D "_WINDLL" /FR$(INTDIR)/ /Fp$(OUTDIR)/"CBACK32.pch"\
 /Yu"stdafx.h" /Fo$(INTDIR)/ /c 
CPP_OBJS=.\obju32/
# ADD BASE RSC /l 0x409 /i "$(OUTDIR)" /d "NDEBUG" /d "_WIN32" /d "_UNICODE"
# ADD RSC /l 0x409 /i "$(OUTDIR)" /d "NDEBUG" /d "_WIN32" /d "_UNICODE"
RSC_PROJ=/l 0x409 /fo$(INTDIR)/"CBACK.res" /i "$(OUTDIR)" /d "NDEBUG" /d\
 "_WIN32" /d "_UNICODE" 
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo /o"obju32/cback.bsc"
# SUBTRACT BASE BSC32 /Iu
# ADD BSC32 /nologo /o"obju32/cback.bsc"
# SUBTRACT BSC32 /Iu
BSC32_FLAGS=/nologo /o"obju32/cback.bsc" 
BSC32_SBRS= \
	$(INTDIR)/STDAFX.SBR \
	$(INTDIR)/CBACK.SBR \
	$(INTDIR)/CALLBCTL.SBR \
	$(INTDIR)/CALLBPPG.SBR

$(OUTDIR)/cback.bsc : $(OUTDIR)  $(BSC32_SBRS)
    $(BSC32) @<<
  $(BSC32_FLAGS) $(BSC32_SBRS)
<<

LINK32=link.exe
# ADD BASE LINK32 ocs30u.lib /NOLOGO /SUBSYSTEM:windows /DLL /MACHINE:IX86 /OUT:"obju32/cback.ocx"
# SUBTRACT BASE LINK32 /PDB:none /NODEFAULTLIB
# ADD LINK32 ocs30u.lib /NOLOGO /SUBSYSTEM:windows /DLL /MACHINE:IX86 /OUT:"obju32/cback.ocx"
# SUBTRACT LINK32 /PDB:none /NODEFAULTLIB
LINK32_FLAGS=ocs30u.lib /NOLOGO /SUBSYSTEM:windows /DLL /INCREMENTAL:no\
 /PDB:$(OUTDIR)/"CBACK32.pdb" /MACHINE:IX86 /DEF:".\CBACK32.DEF"\
 /OUT:"obju32/cback.ocx" /IMPLIB:$(OUTDIR)/"CBACK32.lib" 
DEF_FILE=.\CBACK32.DEF
LINK32_OBJS= \
	$(INTDIR)/STDAFX.OBJ \
	$(INTDIR)/CBACK.OBJ \
	$(INTDIR)/CALLBCTL.OBJ \
	$(INTDIR)/CALLBPPG.OBJ \
	$(INTDIR)/CBACK.res

$(OUTDIR)/cback.ocx : $(OUTDIR)  $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ELSEIF  "$(CFG)" == "Win32 Unicode Debug"

# PROP BASE Use_MFC 2
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Classwizard_Name "cback.clw"
# PROP Use_MFC 2
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "objdu32"
# PROP Intermediate_Dir "objdu32"
# PROP Classwizard_Name "cback.clw"
OUTDIR=.\objdu32
INTDIR=.\objdu32

ALL : MTL_TLBS $(OUTDIR)/cback.ocx $(OUTDIR)/cback.bsc

$(OUTDIR) : 
    if not exist $(OUTDIR)/nul mkdir $(OUTDIR)

# ADD BASE MTL /nologo /D "_DEBUG" /D "_UNICODE" /D "_WIN32" /win32
# ADD MTL /nologo /D "_DEBUG" /D "_UNICODE" /D "_WIN32" /win32
MTL_PROJ=/nologo /D "_DEBUG" /D "_UNICODE" /D "_WIN32" /win32 

MTL_TLBS : $(OUTDIR)/CBACK.tlb
# ADD BASE CPP /nologo /MD /W3 /GX /Zi /Od /D "_DEBUG" /D "_UNICODE" /D "_WINDOWS" /D "_AFXDLL" /D "_AFXCTL" /D "_WINDLL" /FR /Yu"stdafx.h" /c
# SUBTRACT BASE CPP /WX
# ADD CPP /nologo /MD /W3 /GX /Zi /Od /D "_DEBUG" /D "_UNICODE" /D "_WINDOWS" /D "_AFXDLL" /D "_AFXCTL" /D "_WINDLL" /FR /Yu"stdafx.h" /c
# SUBTRACT CPP /WX
CPP_PROJ=/nologo /MD /W3 /GX /Zi /Od /D "_DEBUG" /D "_UNICODE" /D "_WINDOWS" /D\
 "_AFXDLL" /D "_AFXCTL" /D "_WINDLL" /FR$(INTDIR)/ /Fp$(OUTDIR)/"CBACK32.pch"\
 /Yu"stdafx.h" /Fo$(INTDIR)/ /Fd$(OUTDIR)/"CBACK32.pdb" /c 
CPP_OBJS=.\objdu32/
# ADD BASE RSC /l 0x409 /i "$(OUTDIR)" /d "_DEBUG" /d "_WIN32" /d "_UNICODE"
# ADD RSC /l 0x409 /i "$(OUTDIR)" /d "_DEBUG" /d "_WIN32" /d "_UNICODE"
RSC_PROJ=/l 0x409 /fo$(INTDIR)/"CBACK.res" /i "$(OUTDIR)" /d "_DEBUG" /d\
 "_WIN32" /d "_UNICODE" 
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo /o"objdu32/cback.bsc"
# SUBTRACT BASE BSC32 /Iu
# ADD BSC32 /nologo /o"objdu32/cback.bsc"
# SUBTRACT BSC32 /Iu
BSC32_FLAGS=/nologo /o"objdu32/cback.bsc" 
BSC32_SBRS= \
	$(INTDIR)/STDAFX.SBR \
	$(INTDIR)/CBACK.SBR \
	$(INTDIR)/CALLBCTL.SBR \
	$(INTDIR)/CALLBPPG.SBR

$(OUTDIR)/cback.bsc : $(OUTDIR)  $(BSC32_SBRS)
    $(BSC32) @<<
  $(BSC32_FLAGS) $(BSC32_SBRS)
<<

LINK32=link.exe
# ADD BASE LINK32 ocs30ud.lib /NOLOGO /SUBSYSTEM:windows /DLL /DEBUG /MACHINE:IX86 /OUT:"objdu32/cback.ocx"
# SUBTRACT BASE LINK32 /PDB:none /NODEFAULTLIB
# ADD LINK32 ocs30ud.lib /NOLOGO /SUBSYSTEM:windows /DLL /DEBUG /MACHINE:IX86 /OUT:"objdu32/cback.ocx"
# SUBTRACT LINK32 /PDB:none /NODEFAULTLIB
LINK32_FLAGS=ocs30ud.lib /NOLOGO /SUBSYSTEM:windows /DLL /INCREMENTAL:yes\
 /PDB:$(OUTDIR)/"CBACK32.pdb" /DEBUG /MACHINE:IX86 /DEF:".\CBACK32.DEF"\
 /OUT:"objdu32/cback.ocx" /IMPLIB:$(OUTDIR)/"CBACK32.lib" 
DEF_FILE=.\CBACK32.DEF
LINK32_OBJS= \
	$(INTDIR)/STDAFX.OBJ \
	$(INTDIR)/CBACK.OBJ \
	$(INTDIR)/CALLBCTL.OBJ \
	$(INTDIR)/CALLBPPG.OBJ \
	$(INTDIR)/CBACK.res

$(OUTDIR)/cback.ocx : $(OUTDIR)  $(DEF_FILE) $(LINK32_OBJS)
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

SOURCE=.\STDAFX.CPP
DEP_STDAF=\
	.\STDAFX.H

!IF  "$(CFG)" == "Win32 ANSI Release"

# ADD BASE CPP /Yc"STDAFX.H"
# ADD CPP /Yc"STDAFX.H"

$(INTDIR)/STDAFX.OBJ :  $(SOURCE)  $(DEP_STDAF) $(INTDIR)
   $(CPP) /nologo /MD /W3 /GX /Ox /D "NDEBUG" /D "_MBCS" /D "_WINDOWS" /D\
 "_AFXDLL" /D "_AFXCTL" /D "_WINDLL" /FR$(INTDIR)/ /Fp$(OUTDIR)/"CBACK32.pch"\
 /Yc"STDAFX.H" /Fo$(INTDIR)/ /c  $(SOURCE) 

!ELSEIF  "$(CFG)" == "Win32 ANSI Debug"

# ADD BASE CPP /Yc"STDAFX.H"
# ADD CPP /Yc"STDAFX.H"

$(INTDIR)/STDAFX.OBJ :  $(SOURCE)  $(DEP_STDAF) $(INTDIR)
   $(CPP) /nologo /MD /W3 /GX /Zi /Od /D "_DEBUG" /D "_MBCS" /D "_WINDOWS" /D\
 "_AFXDLL" /D "_AFXCTL" /D "_WINDLL" /FR$(INTDIR)/ /Fp$(OUTDIR)/"CBACK32.pch"\
 /Yc"STDAFX.H" /Fo$(INTDIR)/ /Fd$(OUTDIR)/"CBACK32.pdb" /c  $(SOURCE) 

!ELSEIF  "$(CFG)" == "Win32 Unicode Release"

# ADD BASE CPP /Yc"STDAFX.H"
# ADD CPP /Yc"STDAFX.H"

$(INTDIR)/STDAFX.OBJ :  $(SOURCE)  $(DEP_STDAF) $(INTDIR)
   $(CPP) /nologo /MD /W3 /GX /Ox /D "NDEBUG" /D "_UNICODE" /D "_WINDOWS" /D\
 "_AFXDLL" /D "_AFXCTL" /D "_WINDLL" /FR$(INTDIR)/ /Fp$(OUTDIR)/"CBACK32.pch"\
 /Yc"STDAFX.H" /Fo$(INTDIR)/ /c  $(SOURCE) 

!ELSEIF  "$(CFG)" == "Win32 Unicode Debug"

# ADD BASE CPP /Yc"STDAFX.H"
# ADD CPP /Yc"STDAFX.H"

$(INTDIR)/STDAFX.OBJ :  $(SOURCE)  $(DEP_STDAF) $(INTDIR)
   $(CPP) /nologo /MD /W3 /GX /Zi /Od /D "_DEBUG" /D "_UNICODE" /D "_WINDOWS"\
 /D "_AFXDLL" /D "_AFXCTL" /D "_WINDLL" /FR$(INTDIR)/ /Fp$(OUTDIR)/"CBACK32.pch"\
 /Yc"STDAFX.H" /Fo$(INTDIR)/ /Fd$(OUTDIR)/"CBACK32.pdb" /c  $(SOURCE) 

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\CBACK.CPP
DEP_CBACK=\
	.\STDAFX.H\
	.\CBACK.H

!IF  "$(CFG)" == "Win32 ANSI Release"

$(INTDIR)/CBACK.OBJ :  $(SOURCE)  $(DEP_CBACK) $(INTDIR) $(INTDIR)/STDAFX.OBJ

!ELSEIF  "$(CFG)" == "Win32 ANSI Debug"

$(INTDIR)/CBACK.OBJ :  $(SOURCE)  $(DEP_CBACK) $(INTDIR) $(INTDIR)/STDAFX.OBJ

!ELSEIF  "$(CFG)" == "Win32 Unicode Release"

$(INTDIR)/CBACK.OBJ :  $(SOURCE)  $(DEP_CBACK) $(INTDIR) $(INTDIR)/STDAFX.OBJ

!ELSEIF  "$(CFG)" == "Win32 Unicode Debug"

$(INTDIR)/CBACK.OBJ :  $(SOURCE)  $(DEP_CBACK) $(INTDIR) $(INTDIR)/STDAFX.OBJ

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\CALLBCTL.CPP
DEP_CALLB=\
	.\STDAFX.H\
	.\CBACK.H\
	.\CALLBCTL.H\
	.\CALLBPPG.H

!IF  "$(CFG)" == "Win32 ANSI Release"

$(INTDIR)/CALLBCTL.OBJ :  $(SOURCE)  $(DEP_CALLB) $(INTDIR)\
 $(INTDIR)/STDAFX.OBJ

!ELSEIF  "$(CFG)" == "Win32 ANSI Debug"

$(INTDIR)/CALLBCTL.OBJ :  $(SOURCE)  $(DEP_CALLB) $(INTDIR)\
 $(INTDIR)/STDAFX.OBJ

!ELSEIF  "$(CFG)" == "Win32 Unicode Release"

$(INTDIR)/CALLBCTL.OBJ :  $(SOURCE)  $(DEP_CALLB) $(INTDIR)\
 $(INTDIR)/STDAFX.OBJ

!ELSEIF  "$(CFG)" == "Win32 Unicode Debug"

$(INTDIR)/CALLBCTL.OBJ :  $(SOURCE)  $(DEP_CALLB) $(INTDIR)\
 $(INTDIR)/STDAFX.OBJ

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\CALLBPPG.CPP
DEP_CALLBP=\
	.\STDAFX.H\
	.\CBACK.H\
	.\CALLBPPG.H

!IF  "$(CFG)" == "Win32 ANSI Release"

$(INTDIR)/CALLBPPG.OBJ :  $(SOURCE)  $(DEP_CALLBP) $(INTDIR)\
 $(INTDIR)/STDAFX.OBJ

!ELSEIF  "$(CFG)" == "Win32 ANSI Debug"

$(INTDIR)/CALLBPPG.OBJ :  $(SOURCE)  $(DEP_CALLBP) $(INTDIR)\
 $(INTDIR)/STDAFX.OBJ

!ELSEIF  "$(CFG)" == "Win32 Unicode Release"

$(INTDIR)/CALLBPPG.OBJ :  $(SOURCE)  $(DEP_CALLBP) $(INTDIR)\
 $(INTDIR)/STDAFX.OBJ

!ELSEIF  "$(CFG)" == "Win32 Unicode Debug"

$(INTDIR)/CALLBPPG.OBJ :  $(SOURCE)  $(DEP_CALLBP) $(INTDIR)\
 $(INTDIR)/STDAFX.OBJ

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\CBACK32.DEF
# End Source File
################################################################################
# Begin Source File

SOURCE=.\CBACK.RC
DEP_CBACK_=\
	$(OUTDIR)/CBACK.TLB\
	.\CBACK.ICO\
	.\CALLBCTL.BMP\
	.\CBACK.RC2

!IF  "$(CFG)" == "Win32 ANSI Release"

$(INTDIR)/CBACK.res :  $(SOURCE)  $(DEP_CBACK_) $(INTDIR)
   $(RSC) /l 0x409 /fo$(INTDIR)/"CBACK.res" /i "$(OUTDIR)" /d "NDEBUG" /d\
 "_WIN32"  $(SOURCE) 

!ELSEIF  "$(CFG)" == "Win32 ANSI Debug"

$(INTDIR)/CBACK.res :  $(SOURCE)  $(DEP_CBACK_) $(INTDIR)
   $(RSC) /l 0x409 /fo$(INTDIR)/"CBACK.res" /i "$(OUTDIR)" /d "_DEBUG" /d\
 "_WIN32"  $(SOURCE) 

!ELSEIF  "$(CFG)" == "Win32 Unicode Release"

$(INTDIR)/CBACK.res :  $(SOURCE)  $(DEP_CBACK_) $(INTDIR)
   $(RSC) /l 0x409 /fo$(INTDIR)/"CBACK.res" /i "$(OUTDIR)" /d "NDEBUG" /d\
 "_WIN32" /d "_UNICODE"  $(SOURCE) 

!ELSEIF  "$(CFG)" == "Win32 Unicode Debug"

$(INTDIR)/CBACK.res :  $(SOURCE)  $(DEP_CBACK_) $(INTDIR)
   $(RSC) /l 0x409 /fo$(INTDIR)/"CBACK.res" /i "$(OUTDIR)" /d "_DEBUG" /d\
 "_WIN32" /d "_UNICODE"  $(SOURCE) 

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\CBACK.ODL

!IF  "$(CFG)" == "Win32 ANSI Release"

$(OUTDIR)/CBACK.tlb :  $(SOURCE)  $(OUTDIR)
   $(MTL) /nologo /D "NDEBUG" /D "_WIN32" /tlb $(OUTDIR)/"CBACK.tlb" /win32\
   $(SOURCE) 

!ELSEIF  "$(CFG)" == "Win32 ANSI Debug"

$(OUTDIR)/CBACK.TLB :  $(SOURCE)  $(OUTDIR)
   $(MTL) /nologo /D "_DEBUG" /D "_WIN32" /tlb $(OUTDIR)/"CBACK.tlb" /win32\
   $(SOURCE) 

!ELSEIF  "$(CFG)" == "Win32 Unicode Release"

$(OUTDIR)/CBACK.tlb :  $(SOURCE)  $(OUTDIR)
   $(MTL) /nologo /D "NDEBUG" /D "_UNICODE" /D "_WIN32" /tlb\
 $(OUTDIR)/"CBACK.tlb" /win32   $(SOURCE) 

!ELSEIF  "$(CFG)" == "Win32 Unicode Debug"

$(OUTDIR)/CBACK.tlb :  $(SOURCE)  $(OUTDIR)
   $(MTL) /nologo /D "_DEBUG" /D "_UNICODE" /D "_WIN32" /tlb\
 $(OUTDIR)/"CBACK.tlb" /win32   $(SOURCE) 

!ENDIF 

# End Source File
# End Group
# End Project
################################################################################
