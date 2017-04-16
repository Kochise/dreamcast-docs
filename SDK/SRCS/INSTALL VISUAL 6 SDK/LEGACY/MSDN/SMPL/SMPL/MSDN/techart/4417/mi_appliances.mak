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
!MESSAGE NMAKE /f "MI_Appliances.mak" CFG="Win32 Debug"
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
# PROP Target_Last_Scanned "Win32 Debug"
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

ALL : MTL_TLBS $(OUTDIR)/"MI_Appliances.dll" $(OUTDIR)/"MI_Appliances.bsc"

$(OUTDIR) : 
    if not exist $(OUTDIR)/nul mkdir $(OUTDIR)

# ADD BASE MTL /nologo /D "_DEBUG" /win32
# ADD MTL /nologo /D "_DEBUG" /win32
MTL_PROJ=/nologo /D "_DEBUG" /win32 

MTL_TLBS : $(OUTDIR)/"MI_Appliances.tlb"
# ADD BASE CPP /nologo /MT /W3 /GX /Zi /Od /D "_DEBUG" /D "WIN32" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "_WINDLL" /FR /Yu"stdafx.h" /c
# ADD CPP /nologo /MT /W3 /GX /Zi /Od /D "_DEBUG" /D "WIN32" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "_WINDLL" /FR /Yu"stdafx.h" /c
CPP_PROJ=/nologo /MT /W3 /GX /Zi /Od /D "_DEBUG" /D "WIN32" /D "_WINDOWS" /D\
 "_MBCS" /D "_USRDLL" /D "_WINDLL" /FR$(INTDIR)/\
 /Fp$(OUTDIR)/"MI_Appliances.pch" /Yu"stdafx.h" /Fo$(INTDIR)/\
 /Fd$(OUTDIR)/"MI_Appliances.pdb" /c 
CPP_OBJS=".\x86-d/"
# ADD BASE RSC /l 0x0 /d "_DEBUG"
# ADD RSC /l 0x409 /d "_DEBUG"
RSC_PROJ=/l 0x409 /fo$(INTDIR)/"MI_Appliances.res" /d "_DEBUG" 
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
BSC32_FLAGS=/nologo /o$(OUTDIR)/"MI_Appliances.bsc" 
BSC32_SBRS= \
	$(INTDIR)/"stdafx.sbr" \
	$(INTDIR)/"MI_Appliances.sbr" \
	$(INTDIR)/"COMBASE.SBR" \
	$(INTDIR)/"guids.sbr" \
	$(INTDIR)/"CLightBulb.sbr" \
	$(INTDIR)/"CNotifyListObject.sbr" \
	$(INTDIR)/"CBitmapObject.sbr" \
	$(INTDIR)/"CStandardLamp.sbr" \
	$(INTDIR)/"radiodlg.sbr" \
	$(INTDIR)/"CRadio.sbr" \
	$(INTDIR)/"tvdlg.sbr" \
	$(INTDIR)/"CTelevision.sbr"

$(OUTDIR)/"MI_Appliances.bsc" : $(OUTDIR)  $(BSC32_SBRS)
    $(BSC32) @<<
  $(BSC32_FLAGS) $(BSC32_SBRS)
<<

LINK32=link.exe
# ADD BASE LINK32 /NOLOGO /SUBSYSTEM:windows /DLL /DEBUG /MACHINE:I386 /DEF:"MI_Appliances.def" /IMPLIB:"MI_Appliances.lib"
# SUBTRACT BASE LINK32 /PDB:none
# ADD LINK32 winmm.lib animatesd.lib /NOLOGO /SUBSYSTEM:windows /DLL /DEBUG /MACHINE:I386 /DEF:"MI_Appliances.def" /IMPLIB:"MI_Appliances.lib"
# SUBTRACT LINK32 /PDB:none
LINK32_FLAGS=winmm.lib animatesd.lib /NOLOGO /SUBSYSTEM:windows /DLL\
 /INCREMENTAL:yes /PDB:$(OUTDIR)/"MI_Appliances.pdb" /DEBUG /MACHINE:I386\
 /DEF:"MI_Appliances.def" /OUT:$(OUTDIR)/"MI_Appliances.dll"\
 /IMPLIB:"MI_Appliances.lib" 
DEF_FILE=
LINK32_OBJS= \
	$(INTDIR)/"stdafx.obj" \
	$(INTDIR)/"MI_Appliances.obj" \
	$(INTDIR)/"MI_Appliances.res" \
	$(INTDIR)/"COMBASE.OBJ" \
	$(INTDIR)/"guids.obj" \
	$(INTDIR)/"CLightBulb.obj" \
	$(INTDIR)/"CNotifyListObject.obj" \
	$(INTDIR)/"CBitmapObject.obj" \
	$(INTDIR)/"CStandardLamp.obj" \
	$(INTDIR)/"radiodlg.obj" \
	$(INTDIR)/"CRadio.obj" \
	$(INTDIR)/"tvdlg.obj" \
	$(INTDIR)/"CTelevision.obj"

$(OUTDIR)/"MI_Appliances.dll" : $(OUTDIR)  $(DEF_FILE) $(LINK32_OBJS)
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

ALL : MTL_TLBS $(OUTDIR)/"MI_Appliances.dll" $(OUTDIR)/"MI_Appliances.bsc"

$(OUTDIR) : 
    if not exist $(OUTDIR)/nul mkdir $(OUTDIR)

# ADD BASE MTL /nologo /D "NDEBUG" /win32
# ADD MTL /nologo /D "NDEBUG" /win32
MTL_PROJ=/nologo /D "NDEBUG" /win32 

MTL_TLBS : $(OUTDIR)/"MI_Appliances.tlb"
# ADD BASE CPP /nologo /MT /W3 /GX /O2 /D "NDEBUG" /D "WIN32" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "_WINDLL" /FR /Yu"stdafx.h" /c
# ADD CPP /nologo /MT /W3 /GX /O2 /D "NDEBUG" /D "WIN32" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "_WINDLL" /FR /Yu"stdafx.h" /c
CPP_PROJ=/nologo /MT /W3 /GX /O2 /D "NDEBUG" /D "WIN32" /D "_WINDOWS" /D\
 "_MBCS" /D "_USRDLL" /D "_WINDLL" /FR$(INTDIR)/\
 /Fp$(OUTDIR)/"MI_Appliances.pch" /Yu"stdafx.h" /Fo$(INTDIR)/ /c 
CPP_OBJS=".\x86-r/"
# ADD BASE RSC /l 0x0 /d "NDEBUG"
# ADD RSC /l 0x0 /d "NDEBUG"
RSC_PROJ=/l 0x0 /fo$(INTDIR)/"MI_Appliances.res" /d "NDEBUG" 
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
BSC32_FLAGS=/nologo /o$(OUTDIR)/"MI_Appliances.bsc" 
BSC32_SBRS= \
	$(INTDIR)/"stdafx.sbr" \
	$(INTDIR)/"MI_Appliances.sbr" \
	$(INTDIR)/"COMBASE.SBR" \
	$(INTDIR)/"guids.sbr" \
	$(INTDIR)/"CLightBulb.sbr" \
	$(INTDIR)/"CNotifyListObject.sbr" \
	$(INTDIR)/"CBitmapObject.sbr" \
	$(INTDIR)/"CStandardLamp.sbr" \
	$(INTDIR)/"radiodlg.sbr" \
	$(INTDIR)/"CRadio.sbr" \
	$(INTDIR)/"tvdlg.sbr" \
	$(INTDIR)/"CTelevision.sbr"

$(OUTDIR)/"MI_Appliances.bsc" : $(OUTDIR)  $(BSC32_SBRS)
    $(BSC32) @<<
  $(BSC32_FLAGS) $(BSC32_SBRS)
<<

LINK32=link.exe
# ADD BASE LINK32 /NOLOGO /SUBSYSTEM:windows /DLL /MACHINE:I386 /DEF:"MI_Appliances.def" /IMPLIB:"MI_Appliances.lib"
# SUBTRACT BASE LINK32 /PDB:none
# ADD LINK32 winmm.lib animatesr.lib /NOLOGO /SUBSYSTEM:windows /DLL /MACHINE:I386 /DEF:"MI_Appliances.def" /IMPLIB:"MI_Appliances.lib"
# SUBTRACT LINK32 /PDB:none
LINK32_FLAGS=winmm.lib animatesr.lib /NOLOGO /SUBSYSTEM:windows /DLL\
 /INCREMENTAL:no /PDB:$(OUTDIR)/"MI_Appliances.pdb" /MACHINE:I386\
 /DEF:"MI_Appliances.def" /OUT:$(OUTDIR)/"MI_Appliances.dll"\
 /IMPLIB:"MI_Appliances.lib" 
DEF_FILE=
LINK32_OBJS= \
	$(INTDIR)/"stdafx.obj" \
	$(INTDIR)/"MI_Appliances.obj" \
	$(INTDIR)/"MI_Appliances.res" \
	$(INTDIR)/"COMBASE.OBJ" \
	$(INTDIR)/"guids.obj" \
	$(INTDIR)/"CLightBulb.obj" \
	$(INTDIR)/"CNotifyListObject.obj" \
	$(INTDIR)/"CBitmapObject.obj" \
	$(INTDIR)/"CStandardLamp.obj" \
	$(INTDIR)/"radiodlg.obj" \
	$(INTDIR)/"CRadio.obj" \
	$(INTDIR)/"tvdlg.obj" \
	$(INTDIR)/"CTelevision.obj"

$(OUTDIR)/"MI_Appliances.dll" : $(OUTDIR)  $(DEF_FILE) $(LINK32_OBJS)
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
	\Articles\Samples\OpenGL\animate\include\animate.h

!IF  "$(CFG)" == "Win32 Debug"

# ADD BASE CPP /Yc"stdafx.h"
# ADD CPP /Yc"stdafx.h"

$(INTDIR)/"stdafx.obj" :  $(SOURCE)  $(DEP_STDAF) $(INTDIR)
   $(CPP) /nologo /MT /W3 /GX /Zi /Od /D "_DEBUG" /D "WIN32" /D "_WINDOWS" /D\
 "_MBCS" /D "_USRDLL" /D "_WINDLL" /FR$(INTDIR)/\
 /Fp$(OUTDIR)/"MI_Appliances.pch" /Yc"stdafx.h" /Fo$(INTDIR)/\
 /Fd$(OUTDIR)/"MI_Appliances.pdb" /c  $(SOURCE) 

!ELSEIF  "$(CFG)" == "Win32 Release"

# ADD BASE CPP /Yc"stdafx.h"
# ADD CPP /Yc"stdafx.h"

$(INTDIR)/"stdafx.obj" :  $(SOURCE)  $(DEP_STDAF) $(INTDIR)
   $(CPP) /nologo /MT /W3 /GX /O2 /D "NDEBUG" /D "WIN32" /D "_WINDOWS" /D\
 "_MBCS" /D "_USRDLL" /D "_WINDLL" /FR$(INTDIR)/\
 /Fp$(OUTDIR)/"MI_Appliances.pch" /Yc"stdafx.h" /Fo$(INTDIR)/ /c  $(SOURCE) 

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\MI_Appliances.cpp
DEP_MI_AP=\
	.\stdafx.h\
	.\COMBASE.h\
	.\MI_Appliances.h\
	..\include\idrawing.h\
	..\include\ioutlet.h\
	.\CLightBulb.h\
	..\include\inotify.h\
	..\include\inotifysrc.h\
	.\CNotifyListObject.h\
	..\include\ibitmap.h\
	.\CBitmapObject.h\
	..\include\ilight.h\
	.\CStandardLamp.h\
	..\include\iapplianceui.h\
	.\CRadio.h\
	..\include\appliancesid.h\
	\Articles\Samples\OpenGL\animate\include\animate.h

$(INTDIR)/"MI_Appliances.obj" :  $(SOURCE)  $(DEP_MI_AP) $(INTDIR)\
 $(INTDIR)/stdafx.obj

# End Source File
################################################################################
# Begin Source File

SOURCE=.\MI_Appliances.rc
DEP_MI_APP=\
	.\res\MI_Appliances.rc2

!IF  "$(CFG)" == "Win32 Debug"

$(INTDIR)/"MI_Appliances.res" :  $(SOURCE)  $(DEP_MI_APP) $(INTDIR)
   $(RSC) /l 0x409 /fo$(INTDIR)/"MI_Appliances.res" /i "$(OUTDIR)" /d "_DEBUG"\
  $(SOURCE) 

!ELSEIF  "$(CFG)" == "Win32 Release"

$(INTDIR)/"MI_Appliances.res" :  $(SOURCE)  $(DEP_MI_APP) $(INTDIR)
   $(RSC) /l 0x0 /fo$(INTDIR)/"MI_Appliances.res" /i "$(OUTDIR)" /d "NDEBUG"\
  $(SOURCE) 

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\readme.txt
# End Source File
################################################################################
# Begin Source File

SOURCE=.\MI_Appliances.odl

!IF  "$(CFG)" == "Win32 Debug"

$(OUTDIR)/"MI_Appliances.tlb" :  $(SOURCE)  $(OUTDIR)
   $(MTL) /nologo /D "_DEBUG" /tlb $(OUTDIR)/"MI_Appliances.tlb" /win32\
  $(SOURCE) 

!ELSEIF  "$(CFG)" == "Win32 Release"

$(OUTDIR)/"MI_Appliances.tlb" :  $(SOURCE)  $(OUTDIR)
   $(MTL) /nologo /D "NDEBUG" /tlb $(OUTDIR)/"MI_Appliances.tlb" /win32\
  $(SOURCE) 

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\COMBASE.CPP
DEP_COMBA=\
	.\stdafx.h\
	.\COMBASE.h\
	\Articles\Samples\OpenGL\animate\include\animate.h

$(INTDIR)/"COMBASE.OBJ" :  $(SOURCE)  $(DEP_COMBA) $(INTDIR)\
 $(INTDIR)/stdafx.obj

# End Source File
################################################################################
# Begin Source File

SOURCE=.\guids.cpp
DEP_GUIDS=\
	.\stdafx.h\
	..\include\appliancesid.h\
	..\include\ibitmap.h\
	..\include\idrawing.h\
	..\include\ioutlet.h\
	..\include\ilight.h\
	..\include\iapplianceui.h\
	..\include\inotify.h\
	..\include\inotifysrc.h\
	\Articles\Samples\OpenGL\animate\include\animate.h

$(INTDIR)/"guids.obj" :  $(SOURCE)  $(DEP_GUIDS) $(INTDIR) $(INTDIR)/stdafx.obj

# End Source File
################################################################################
# Begin Source File

SOURCE=.\CLightBulb.cpp
DEP_CLIGH=\
	.\stdafx.h\
	.\COMBASE.h\
	..\include\idrawing.h\
	..\include\ioutlet.h\
	.\CLightBulb.h\
	\Articles\Samples\OpenGL\animate\include\animate.h

$(INTDIR)/"CLightBulb.obj" :  $(SOURCE)  $(DEP_CLIGH) $(INTDIR)\
 $(INTDIR)/stdafx.obj

# End Source File
################################################################################
# Begin Source File

SOURCE=.\MI_Appliances.reg
# End Source File
################################################################################
# Begin Source File

SOURCE=.\CNotifyListObject.cpp
DEP_CNOTI=\
	.\stdafx.h\
	.\COMBASE.h\
	..\include\inotify.h\
	..\include\inotifysrc.h\
	.\CNotifyListObject.h\
	\Articles\Samples\OpenGL\animate\include\animate.h

$(INTDIR)/"CNotifyListObject.obj" :  $(SOURCE)  $(DEP_CNOTI) $(INTDIR)\
 $(INTDIR)/stdafx.obj

# End Source File
################################################################################
# Begin Source File

SOURCE=.\CBitmapObject.cpp
DEP_CBITM=\
	.\stdafx.h\
	.\COMBASE.h\
	..\include\idrawing.h\
	..\include\ibitmap.h\
	.\CBitmapObject.h\
	\Articles\Samples\OpenGL\animate\include\animate.h

$(INTDIR)/"CBitmapObject.obj" :  $(SOURCE)  $(DEP_CBITM) $(INTDIR)\
 $(INTDIR)/stdafx.obj

# End Source File
################################################################################
# Begin Source File

SOURCE=.\CStandardLamp.cpp
DEP_CSTAN=\
	.\stdafx.h\
	.\COMBASE.h\
	..\include\appliancesid.h\
	..\include\idrawing.h\
	..\include\ioutlet.h\
	..\include\ilight.h\
	..\include\inotify.h\
	..\include\inotifysrc.h\
	.\CStandardLamp.h\
	\Articles\Samples\OpenGL\animate\include\animate.h

$(INTDIR)/"CStandardLamp.obj" :  $(SOURCE)  $(DEP_CSTAN) $(INTDIR)\
 $(INTDIR)/stdafx.obj

# End Source File
################################################################################
# Begin Source File

SOURCE=.\radiodlg.cpp
DEP_RADIO=\
	.\stdafx.h\
	.\COMBASE.h\
	.\MI_Appliances.h\
	..\include\idrawing.h\
	..\include\iapplianceui.h\
	.\CRadio.h\
	.\radiodlg.h\
	\Articles\Samples\OpenGL\animate\include\animate.h

$(INTDIR)/"radiodlg.obj" :  $(SOURCE)  $(DEP_RADIO) $(INTDIR)\
 $(INTDIR)/stdafx.obj

# End Source File
################################################################################
# Begin Source File

SOURCE=.\CRadio.cpp
DEP_CRADI=\
	.\stdafx.h\
	.\COMBASE.h\
	..\include\appliancesid.h\
	..\include\iapplianceui.h\
	..\include\idrawing.h\
	..\include\ibitmap.h\
	.\CRadio.h\
	.\radiodlg.h\
	\Articles\Samples\OpenGL\animate\include\animate.h

$(INTDIR)/"CRadio.obj" :  $(SOURCE)  $(DEP_CRADI) $(INTDIR)\
 $(INTDIR)/stdafx.obj

# End Source File
################################################################################
# Begin Source File

SOURCE=.\tvdlg.cpp
DEP_TVDLG=\
	.\stdafx.h\
	.\COMBASE.h\
	..\include\idrawing.h\
	..\include\iapplianceui.h\
	.\MI_Appliances.h\
	.\CTelevision.h\
	.\tvdlg.h\
	\Articles\Samples\OpenGL\animate\include\animate.h

$(INTDIR)/"tvdlg.obj" :  $(SOURCE)  $(DEP_TVDLG) $(INTDIR) $(INTDIR)/stdafx.obj

# End Source File
################################################################################
# Begin Source File

SOURCE=.\CTelevision.cpp
DEP_CTELE=\
	.\stdafx.h\
	.\COMBASE.h\
	..\include\idrawing.h\
	..\include\iapplianceui.h\
	.\CTelevision.h\
	.\tvdlg.h\
	\Articles\Samples\OpenGL\animate\include\animate.h

$(INTDIR)/"CTelevision.obj" :  $(SOURCE)  $(DEP_CTELE) $(INTDIR)\
 $(INTDIR)/stdafx.obj

# End Source File
# End Group
# End Project
################################################################################
