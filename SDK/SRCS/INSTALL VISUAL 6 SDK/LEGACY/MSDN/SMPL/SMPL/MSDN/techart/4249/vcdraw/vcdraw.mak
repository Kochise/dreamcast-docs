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
!MESSAGE NMAKE /f "VCDraw.mak" CFG="Win32 Debug"
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
# PROP Output_Dir "x86-d"
# PROP Intermediate_Dir "x86-d"
OUTDIR=.\x86-d
INTDIR=.\x86-d

ALL : MTL_TLBS ".\x86-d\VCDraw.exe" ".\x86-d\VCDraw.bsc"

$(OUTDIR) : 
    if not exist $(OUTDIR)/nul mkdir $(OUTDIR)

# ADD BASE MTL /nologo /D "_DEBUG" /win32
# ADD MTL /nologo /D "_DEBUG" /win32
MTL_PROJ=/nologo /D "_DEBUG" /win32 

MTL_TLBS : ".\x86-d\VCDraw.tlb"
# ADD BASE CPP /nologo /MD /W3 /GX /Zi /Od /D "_DEBUG" /D "WIN32" /D "_WINDOWS" /D "_MBCS" /D "_AFXDLL" /FR /Yu"stdafx.h" /c
# ADD CPP /nologo /MD /W3 /GX /Zi /Od /D "_DEBUG" /D "WIN32" /D "_WINDOWS" /D "_MBCS" /D "_AFXDLL" /Yu"stdafx.h" /c
# SUBTRACT CPP /Fr
CPP_PROJ=/nologo /MD /W3 /GX /Zi /Od /D "_DEBUG" /D "WIN32" /D "_WINDOWS" /D\
 "_MBCS" /D "_AFXDLL" /Fp$(OUTDIR)/"VCDraw.pch" /Yu"stdafx.h" /Fo$(INTDIR)/\
 /Fd$(OUTDIR)/"VCDraw.pdb" /c 
CPP_OBJS=".\x86-d/"
# ADD BASE RSC /l 0x409 /d "_DEBUG" /d "_AFXDLL"
# ADD RSC /l 0x409 /d "_DEBUG" /d "_AFXDLL"
RSC_PROJ=/l 0x409 /fo$(INTDIR)/"VCDraw.res" /d "_DEBUG" /d "_AFXDLL" 
BSC32=bscmake.exe
BSC32_SBRS= \
	
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
BSC32_FLAGS=/nologo /o$(OUTDIR)/"VCDraw.bsc" 

".\x86-d\VCDraw.bsc" : $(OUTDIR)  $(BSC32_SBRS)
LINK32=link.exe
# ADD BASE LINK32 /NOLOGO /SUBSYSTEM:windows /DEBUG /MACHINE:I386
# SUBTRACT BASE LINK32 /PDB:none
# ADD LINK32 /NOLOGO /SUBSYSTEM:windows /DEBUG /MACHINE:I386
# SUBTRACT LINK32 /PDB:none
LINK32_FLAGS=/NOLOGO /SUBSYSTEM:windows /INCREMENTAL:yes\
 /PDB:$(OUTDIR)/"VCDraw.pdb" /DEBUG /MACHINE:I386 /OUT:$(OUTDIR)/"VCDraw.exe" 
DEF_FILE=
LINK32_OBJS= \
	".\x86-d\stdafx.obj" \
	".\x86-d\VCDraw.obj" \
	".\x86-d\mainfrm.obj" \
	".\x86-d\VCDradoc.obj" \
	".\x86-d\VCDravw.obj" \
	".\x86-d\VCDraw.res" \
	".\x86-d\icopalob.obj" \
	".\x86-d\idsobj.obj"

".\x86-d\VCDraw.exe" : $(OUTDIR)  $(DEF_FILE) $(LINK32_OBJS)
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
# PROP Output_Dir "x86-r"
# PROP Intermediate_Dir "x86-r"
OUTDIR=.\x86-r
INTDIR=.\x86-r

ALL : MTL_TLBS ".\x86-r\VCDraw.exe" ".\x86-r\VCDraw.bsc"

$(OUTDIR) : 
    if not exist $(OUTDIR)/nul mkdir $(OUTDIR)

# ADD BASE MTL /nologo /D "NDEBUG" /win32
# ADD MTL /nologo /D "NDEBUG" /win32
MTL_PROJ=/nologo /D "NDEBUG" /win32 

MTL_TLBS : ".\x86-r\VCDraw.tlb"
# ADD BASE CPP /nologo /MD /W3 /GX /O2 /D "NDEBUG" /D "WIN32" /D "_WINDOWS" /D "_MBCS" /D "_AFXDLL" /FR /Yu"stdafx.h" /c
# ADD CPP /nologo /MD /W3 /GX /O2 /D "NDEBUG" /D "WIN32" /D "_WINDOWS" /D "_MBCS" /D "_AFXDLL" /Yu"stdafx.h" /c
# SUBTRACT CPP /Fr
CPP_PROJ=/nologo /MD /W3 /GX /O2 /D "NDEBUG" /D "WIN32" /D "_WINDOWS" /D\
 "_MBCS" /D "_AFXDLL" /Fp$(OUTDIR)/"VCDraw.pch" /Yu"stdafx.h" /Fo$(INTDIR)/ /c 
CPP_OBJS=".\x86-r/"
# ADD BASE RSC /l 0x409 /d "NDEBUG" /d "_AFXDLL"
# ADD RSC /l 0x409 /d "NDEBUG" /d "_AFXDLL"
RSC_PROJ=/l 0x409 /fo$(INTDIR)/"VCDraw.res" /d "NDEBUG" /d "_AFXDLL" 
BSC32=bscmake.exe
BSC32_SBRS= \
	
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
BSC32_FLAGS=/nologo /o$(OUTDIR)/"VCDraw.bsc" 

".\x86-r\VCDraw.bsc" : $(OUTDIR)  $(BSC32_SBRS)
LINK32=link.exe
# ADD BASE LINK32 /NOLOGO /SUBSYSTEM:windows /MACHINE:I386
# SUBTRACT BASE LINK32 /PDB:none
# ADD LINK32 /NOLOGO /SUBSYSTEM:windows /MACHINE:I386
# SUBTRACT LINK32 /PDB:none
LINK32_FLAGS=/NOLOGO /SUBSYSTEM:windows /INCREMENTAL:no\
 /PDB:$(OUTDIR)/"VCDraw.pdb" /MACHINE:I386 /OUT:$(OUTDIR)/"VCDraw.exe" 
DEF_FILE=
LINK32_OBJS= \
	".\x86-r\stdafx.obj" \
	".\x86-r\VCDraw.obj" \
	".\x86-r\mainfrm.obj" \
	".\x86-r\VCDradoc.obj" \
	".\x86-r\VCDravw.obj" \
	".\x86-r\VCDraw.res" \
	".\x86-r\icopalob.obj" \
	".\x86-r\idsobj.obj"

".\x86-r\VCDraw.exe" : $(OUTDIR)  $(DEF_FILE) $(LINK32_OBJS)
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

".\x86-d\stdafx.obj" :  $(SOURCE)  $(DEP_STDAF) $(INTDIR)
   $(CPP) /nologo /MD /W3 /GX /Zi /Od /D "_DEBUG" /D "WIN32" /D "_WINDOWS" /D\
 "_MBCS" /D "_AFXDLL" /Fp$(OUTDIR)/"VCDraw.pch" /Yc"stdafx.h" /Fo$(INTDIR)/\
 /Fd$(OUTDIR)/"VCDraw.pdb" /c  $(SOURCE) 

!ELSEIF  "$(CFG)" == "Win32 Release"

# ADD BASE CPP /Yc"stdafx.h"
# ADD CPP /Yc"stdafx.h"

".\x86-r\stdafx.obj" :  $(SOURCE)  $(DEP_STDAF) $(INTDIR)
   $(CPP) /nologo /MD /W3 /GX /O2 /D "NDEBUG" /D "WIN32" /D "_WINDOWS" /D\
 "_MBCS" /D "_AFXDLL" /Fp$(OUTDIR)/"VCDraw.pch" /Yc"stdafx.h" /Fo$(INTDIR)/ /c\
  $(SOURCE) 

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\VCDraw.cpp
DEP_VCDRA=\
	.\stdafx.h\
	.\VCDraw.h\
	.\mainfrm.h\
	.\VCDradoc.h\
	.\VCDravw.h\
	.\icopalob.h\
	.\idsobj.h

!IF  "$(CFG)" == "Win32 Debug"

".\x86-d\VCDraw.obj" :  $(SOURCE)  $(DEP_VCDRA) $(INTDIR) .\x86-d\stdafx.obj

!ELSEIF  "$(CFG)" == "Win32 Release"

".\x86-r\VCDraw.obj" :  $(SOURCE)  $(DEP_VCDRA) $(INTDIR) .\x86-r\stdafx.obj

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\mainfrm.cpp
DEP_MAINF=\
	.\stdafx.h\
	.\VCDraw.h\
	.\mainfrm.h

!IF  "$(CFG)" == "Win32 Debug"

".\x86-d\mainfrm.obj" :  $(SOURCE)  $(DEP_MAINF) $(INTDIR) .\x86-d\stdafx.obj

!ELSEIF  "$(CFG)" == "Win32 Release"

".\x86-r\mainfrm.obj" :  $(SOURCE)  $(DEP_MAINF) $(INTDIR) .\x86-r\stdafx.obj

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\VCDradoc.cpp
DEP_VCDRAD=\
	.\stdafx.h\
	.\VCDraw.h\
	.\VCDradoc.h

!IF  "$(CFG)" == "Win32 Debug"

".\x86-d\VCDradoc.obj" :  $(SOURCE)  $(DEP_VCDRAD) $(INTDIR) .\x86-d\stdafx.obj

!ELSEIF  "$(CFG)" == "Win32 Release"

".\x86-r\VCDradoc.obj" :  $(SOURCE)  $(DEP_VCDRAD) $(INTDIR) .\x86-r\stdafx.obj

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\VCDravw.cpp
DEP_VCDRAV=\
	.\stdafx.h\
	.\VCDraw.h\
	..\Include\DrawingID.h\
	.\VCDradoc.h\
	.\VCDravw.h\
	.\icopalob.h\
	.\idsobj.h

!IF  "$(CFG)" == "Win32 Debug"

".\x86-d\VCDravw.obj" :  $(SOURCE)  $(DEP_VCDRAV) $(INTDIR) .\x86-d\stdafx.obj

!ELSEIF  "$(CFG)" == "Win32 Release"

".\x86-r\VCDravw.obj" :  $(SOURCE)  $(DEP_VCDRAV) $(INTDIR) .\x86-r\stdafx.obj

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\VCDraw.rc
DEP_VCDRAW=\
	.\res\VCDraw.ico\
	.\res\VCDradoc.ico\
	.\res\toolbar.bmp\
	.\res\VCDraw.rc2

!IF  "$(CFG)" == "Win32 Debug"

".\x86-d\VCDraw.res" :  $(SOURCE)  $(DEP_VCDRAW) $(INTDIR)
   $(RSC) /l 0x409 /fo$(INTDIR)/"VCDraw.res" /i "$(OUTDIR)" /d "_DEBUG" /d\
 "_AFXDLL"  $(SOURCE) 

!ELSEIF  "$(CFG)" == "Win32 Release"

".\x86-r\VCDraw.res" :  $(SOURCE)  $(DEP_VCDRAW) $(INTDIR)
   $(RSC) /l 0x409 /fo$(INTDIR)/"VCDraw.res" /i "$(OUTDIR)" /d "NDEBUG" /d\
 "_AFXDLL"  $(SOURCE) 

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\readme.txt
# End Source File
################################################################################
# Begin Source File

SOURCE=.\VCDraw.odl

!IF  "$(CFG)" == "Win32 Debug"

".\x86-d\VCDraw.tlb" :  $(SOURCE)  $(OUTDIR)
   $(MTL) /nologo /D "_DEBUG" /tlb $(OUTDIR)/"VCDraw.tlb" /win32  $(SOURCE) 

!ELSEIF  "$(CFG)" == "Win32 Release"

".\x86-r\VCDraw.tlb" :  $(SOURCE)  $(OUTDIR)
   $(MTL) /nologo /D "NDEBUG" /tlb $(OUTDIR)/"VCDraw.tlb" /win32  $(SOURCE) 

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\icopalob.cpp
DEP_ICOPA=\
	.\stdafx.h\
	.\icopalob.h

!IF  "$(CFG)" == "Win32 Debug"

".\x86-d\icopalob.obj" :  $(SOURCE)  $(DEP_ICOPA) $(INTDIR) .\x86-d\stdafx.obj

!ELSEIF  "$(CFG)" == "Win32 Release"

".\x86-r\icopalob.obj" :  $(SOURCE)  $(DEP_ICOPA) $(INTDIR) .\x86-r\stdafx.obj

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\idsobj.cpp
DEP_IDSOB=\
	.\stdafx.h\
	.\idsobj.h

!IF  "$(CFG)" == "Win32 Debug"

".\x86-d\idsobj.obj" :  $(SOURCE)  $(DEP_IDSOB) $(INTDIR) .\x86-d\stdafx.obj

!ELSEIF  "$(CFG)" == "Win32 Release"

".\x86-r\idsobj.obj" :  $(SOURCE)  $(DEP_IDSOB) $(INTDIR) .\x86-r\stdafx.obj

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\VCDraw.reg
# End Source File
# End Group
# End Project
################################################################################
