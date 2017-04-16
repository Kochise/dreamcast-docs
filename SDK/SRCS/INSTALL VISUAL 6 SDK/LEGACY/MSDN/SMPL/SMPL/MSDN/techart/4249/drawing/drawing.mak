# Microsoft Visual C++ Generated NMAKE File, Format Version 2.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Dynamic-Link Library" 0x0102

!IF "$(CFG)" == ""
CFG=Win32 Debug
!MESSAGE No configuration specified.  Defaulting to Win32 Debug.
!ENDIF 

!IF "$(CFG)" != "Win32 Debug" && "$(CFG)" != "Win32 Release"
!MESSAGE Invalid configuration "$(CFG)" specified.
!MESSAGE You can specify a configuration when running NMAKE on this makefile
!MESSAGE by defining the macro CFG on the command line.  For example:
!MESSAGE 
!MESSAGE NMAKE /f "Drawing.mak" CFG="Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "Win32 Debug" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE "Win32 Release" (based on "Win32 (x86) Dynamic-Link Library")
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

# PROP BASE Use_MFC 5
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "WinDebug"
# PROP BASE Intermediate_Dir "WinDebug"
# PROP Use_MFC 5
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "x86-d"
# PROP Intermediate_Dir "x86-d"
OUTDIR=.\x86-d
INTDIR=.\x86-d

ALL : MTL_TLBS $(OUTDIR)/"Drawing.dll" $(OUTDIR)/"Drawing.bsc"

$(OUTDIR) : 
    if not exist $(OUTDIR)/nul mkdir $(OUTDIR)

# ADD BASE MTL /nologo /D "_DEBUG" /win32
# ADD MTL /nologo /D "_DEBUG" /win32
MTL_PROJ=/nologo /D "_DEBUG" /win32 

MTL_TLBS : $(OUTDIR)/"Drawing.tlb"
# ADD BASE CPP /nologo /MT /W3 /GX /Zi /Od /D "_DEBUG" /D "WIN32" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "_WINDLL" /FR /Yu"stdafx.h" /c
# ADD CPP /nologo /MT /W3 /GX /Zi /Od /D "_DEBUG" /D "WIN32" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "_WINDLL" /Yu"stdafx.h" /c
# SUBTRACT CPP /Fr
CPP_PROJ=/nologo /MT /W3 /GX /Zi /Od /D "_DEBUG" /D "WIN32" /D "_WINDOWS" /D\
 "_MBCS" /D "_USRDLL" /D "_WINDLL" /Fp$(OUTDIR)/"Drawing.pch" /Yu"stdafx.h"\
 /Fo$(INTDIR)/ /Fd$(OUTDIR)/"Drawing.pdb" /c 
CPP_OBJS=".\x86-d/"
# ADD BASE RSC /l 0x0 /d "_DEBUG"
# ADD RSC /l 0x0 /d "_DEBUG"
RSC_PROJ=/l 0x0 /fo$(INTDIR)/"Drawing.res" /d "_DEBUG" 
BSC32=bscmake.exe
BSC32_SBRS= \
	
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
BSC32_FLAGS=/nologo /o$(OUTDIR)/"Drawing.bsc" 

$(OUTDIR)/"Drawing.bsc" : $(OUTDIR)  $(BSC32_SBRS)
LINK32=link.exe
# ADD BASE LINK32 /NOLOGO /SUBSYSTEM:windows /DLL /DEBUG /MACHINE:I386 /DEF:"Drawing.def" /IMPLIB:"Drawing.lib"
# SUBTRACT BASE LINK32 /PDB:none
# ADD LINK32 winmm.lib animatesd.lib /NOLOGO /SUBSYSTEM:windows /DLL /DEBUG /MACHINE:I386 /DEF:"Drawing.def" /IMPLIB:"Drawing.lib"
# SUBTRACT LINK32 /PDB:none
LINK32_FLAGS=winmm.lib animatesd.lib /NOLOGO /SUBSYSTEM:windows /DLL\
 /INCREMENTAL:yes /PDB:$(OUTDIR)/"Drawing.pdb" /DEBUG /MACHINE:I386\
 /DEF:"Drawing.def" /OUT:$(OUTDIR)/"Drawing.dll" /IMPLIB:"Drawing.lib" 
DEF_FILE=
LINK32_OBJS= \
	$(INTDIR)/"stdafx.obj" \
	$(INTDIR)/"Drawing.obj" \
	$(INTDIR)/"Drawing.res" \
	$(INTDIR)/"guids.obj" \
	$(INTDIR)/"palobj.obj" \
	$(INTDIR)/"dsurfobj.obj" \
	$(INTDIR)/"image.obj" \
	$(INTDIR)/"ids.obj"

$(OUTDIR)/"Drawing.dll" : $(OUTDIR)  $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ELSEIF  "$(CFG)" == "Win32 Release"

# PROP BASE Use_MFC 5
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "WinRel"
# PROP BASE Intermediate_Dir "WinRel"
# PROP Use_MFC 5
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "x86-r"
# PROP Intermediate_Dir "x86-r"
OUTDIR=.\x86-r
INTDIR=.\x86-r

ALL : MTL_TLBS $(OUTDIR)/"Drawing.dll" $(OUTDIR)/"Drawing.bsc"

$(OUTDIR) : 
    if not exist $(OUTDIR)/nul mkdir $(OUTDIR)

# ADD BASE MTL /nologo /D "NDEBUG" /win32
# ADD MTL /nologo /D "NDEBUG" /win32
MTL_PROJ=/nologo /D "NDEBUG" /win32 

MTL_TLBS : $(OUTDIR)/"Drawing.tlb"
# ADD BASE CPP /nologo /MT /W3 /GX /O2 /D "NDEBUG" /D "WIN32" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "_WINDLL" /FR /Yu"stdafx.h" /c
# ADD CPP /nologo /MT /W3 /GX /O2 /D "NDEBUG" /D "WIN32" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "_WINDLL" /Yu"stdafx.h" /c
# SUBTRACT CPP /Fr
CPP_PROJ=/nologo /MT /W3 /GX /O2 /D "NDEBUG" /D "WIN32" /D "_WINDOWS" /D\
 "_MBCS" /D "_USRDLL" /D "_WINDLL" /Fp$(OUTDIR)/"Drawing.pch" /Yu"stdafx.h"\
 /Fo$(INTDIR)/ /c 
CPP_OBJS=".\x86-r/"
# ADD BASE RSC /l 0x0 /d "NDEBUG"
# ADD RSC /l 0x0 /d "NDEBUG"
RSC_PROJ=/l 0x0 /fo$(INTDIR)/"Drawing.res" /d "NDEBUG" 
BSC32=bscmake.exe
BSC32_SBRS= \
	
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
BSC32_FLAGS=/nologo /o$(OUTDIR)/"Drawing.bsc" 

$(OUTDIR)/"Drawing.bsc" : $(OUTDIR)  $(BSC32_SBRS)
LINK32=link.exe
# ADD BASE LINK32 /NOLOGO /SUBSYSTEM:windows /DLL /MACHINE:I386 /DEF:"Drawing.def" /IMPLIB:"Drawing.lib"
# SUBTRACT BASE LINK32 /PDB:none
# ADD LINK32 winmm.lib animatesr.lib /NOLOGO /SUBSYSTEM:windows /DLL /MACHINE:I386 /DEF:"Drawing.def" /IMPLIB:"Drawing.lib"
# SUBTRACT LINK32 /PDB:none
LINK32_FLAGS=winmm.lib animatesr.lib /NOLOGO /SUBSYSTEM:windows /DLL\
 /INCREMENTAL:no /PDB:$(OUTDIR)/"Drawing.pdb" /MACHINE:I386 /DEF:"Drawing.def"\
 /OUT:$(OUTDIR)/"Drawing.dll" /IMPLIB:"Drawing.lib" 
DEF_FILE=
LINK32_OBJS= \
	$(INTDIR)/"stdafx.obj" \
	$(INTDIR)/"Drawing.obj" \
	$(INTDIR)/"Drawing.res" \
	$(INTDIR)/"guids.obj" \
	$(INTDIR)/"palobj.obj" \
	$(INTDIR)/"dsurfobj.obj" \
	$(INTDIR)/"image.obj" \
	$(INTDIR)/"ids.obj"

$(OUTDIR)/"Drawing.dll" : $(OUTDIR)  $(DEF_FILE) $(LINK32_OBJS)
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
	.\stdafx.h\
	\smpls\tech\win32\animate\include\animate.h

!IF  "$(CFG)" == "Win32 Debug"

# ADD BASE CPP /Yc"stdafx.h"
# ADD CPP /Yc"stdafx.h"

$(INTDIR)/"stdafx.obj" :  $(SOURCE)  $(DEP_STDAF) $(INTDIR)
   $(CPP) /nologo /MT /W3 /GX /Zi /Od /D "_DEBUG" /D "WIN32" /D "_WINDOWS" /D\
 "_MBCS" /D "_USRDLL" /D "_WINDLL" /Fp$(OUTDIR)/"Drawing.pch" /Yc"stdafx.h"\
 /Fo$(INTDIR)/ /Fd$(OUTDIR)/"Drawing.pdb" /c  $(SOURCE) 

!ELSEIF  "$(CFG)" == "Win32 Release"

# ADD BASE CPP /Yc"stdafx.h"
# ADD CPP /Yc"stdafx.h"

$(INTDIR)/"stdafx.obj" :  $(SOURCE)  $(DEP_STDAF) $(INTDIR)
   $(CPP) /nologo /MT /W3 /GX /O2 /D "NDEBUG" /D "WIN32" /D "_WINDOWS" /D\
 "_MBCS" /D "_USRDLL" /D "_WINDLL" /Fp$(OUTDIR)/"Drawing.pch" /Yc"stdafx.h"\
 /Fo$(INTDIR)/ /c  $(SOURCE) 

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\Drawing.cpp
DEP_DRAWI=\
	.\stdafx.h\
	.\Drawing.h\
	\smpls\tech\win32\animate\include\animate.h

$(INTDIR)/"Drawing.obj" :  $(SOURCE)  $(DEP_DRAWI) $(INTDIR)\
 $(INTDIR)/stdafx.obj

# End Source File
################################################################################
# Begin Source File

SOURCE=.\Drawing.rc
DEP_DRAWIN=\
	.\res\Drawing.rc2

!IF  "$(CFG)" == "Win32 Debug"

$(INTDIR)/"Drawing.res" :  $(SOURCE)  $(DEP_DRAWIN) $(INTDIR)
   $(RSC) /l 0x0 /fo$(INTDIR)/"Drawing.res" /i "$(OUTDIR)" /d "_DEBUG"\
  $(SOURCE) 

!ELSEIF  "$(CFG)" == "Win32 Release"

$(INTDIR)/"Drawing.res" :  $(SOURCE)  $(DEP_DRAWIN) $(INTDIR)
   $(RSC) /l 0x0 /fo$(INTDIR)/"Drawing.res" /i "$(OUTDIR)" /d "NDEBUG"\
  $(SOURCE) 

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\readme.txt
# End Source File
################################################################################
# Begin Source File

SOURCE=.\Drawing.odl

!IF  "$(CFG)" == "Win32 Debug"

$(OUTDIR)/"Drawing.tlb" :  $(SOURCE)  $(OUTDIR)
   $(MTL) /nologo /D "_DEBUG" /tlb $(OUTDIR)/"Drawing.tlb" /win32  $(SOURCE) 

!ELSEIF  "$(CFG)" == "Win32 Release"

$(OUTDIR)/"Drawing.tlb" :  $(SOURCE)  $(OUTDIR)
   $(MTL) /nologo /D "NDEBUG" /tlb $(OUTDIR)/"Drawing.tlb" /win32  $(SOURCE) 

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\guids.cpp
DEP_GUIDS=\
	.\stdafx.h\
	..\Include\DrawingID.h\
	\smpls\tech\win32\animate\include\animate.h

$(INTDIR)/"guids.obj" :  $(SOURCE)  $(DEP_GUIDS) $(INTDIR) $(INTDIR)/stdafx.obj

# End Source File
################################################################################
# Begin Source File

SOURCE=.\palobj.cpp
DEP_PALOB=\
	.\stdafx.h\
	.\Drawing.h\
	.\palobj.h\
	.\ids.h\
	\smpls\tech\win32\animate\include\animate.h\
	.\colorpal.h\
	.\image.h

$(INTDIR)/"palobj.obj" :  $(SOURCE)  $(DEP_PALOB) $(INTDIR)\
 $(INTDIR)/stdafx.obj

# End Source File
################################################################################
# Begin Source File

SOURCE=.\dsurfobj.cpp
DEP_DSURF=\
	.\stdafx.h\
	.\Drawing.h\
	.\ids.h\
	.\dsurfobj.h\
	\smpls\tech\win32\animate\include\animate.h\
	.\colorpal.h\
	.\image.h

$(INTDIR)/"dsurfobj.obj" :  $(SOURCE)  $(DEP_DSURF) $(INTDIR)\
 $(INTDIR)/stdafx.obj

# End Source File
################################################################################
# Begin Source File

SOURCE=.\image.cpp
DEP_IMAGE=\
	.\stdafx.h\
	.\image.h\
	\smpls\tech\win32\animate\include\animate.h

$(INTDIR)/"image.obj" :  $(SOURCE)  $(DEP_IMAGE) $(INTDIR) $(INTDIR)/stdafx.obj

# End Source File
################################################################################
# Begin Source File

SOURCE=.\ids.cpp
DEP_IDS_C=\
	.\stdafx.h\
	.\ids.h\
	\smpls\tech\win32\animate\include\animate.h

$(INTDIR)/"ids.obj" :  $(SOURCE)  $(DEP_IDS_C) $(INTDIR) $(INTDIR)/stdafx.obj

# End Source File
# End Group
# End Project
################################################################################
