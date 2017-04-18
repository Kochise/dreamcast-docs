# Microsoft Developer Studio Generated NMAKE File, Format Version 40001
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Application" 0x0101

!IF "$(CFG)" == ""
CFG=DelExe - Win32 Debug
!MESSAGE No configuration specified.  Defaulting to DelExe - Win32 Debug.
!ENDIF 

!IF "$(CFG)" != "DelExe - Win32 Release" && "$(CFG)" != "DelExe - Win32 Debug"
!MESSAGE Invalid configuration "$(CFG)" specified.
!MESSAGE You can specify a configuration when running NMAKE on this makefile
!MESSAGE by defining the macro CFG on the command line.  For example:
!MESSAGE 
!MESSAGE NMAKE /f "DelExe.mak" CFG="DelExe - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "DelExe - Win32 Release" (based on "Win32 (x86) Application")
!MESSAGE "DelExe - Win32 Debug" (based on "Win32 (x86) Application")
!MESSAGE 
!ERROR An invalid configuration is specified.
!ENDIF 

!IF "$(OS)" == "Windows_NT"
NULL=
!ELSE 
NULL=nul
!ENDIF 
################################################################################
# Begin Project
# PROP Target_Last_Scanned "DelExe - Win32 Debug"
MTL=mktyplib.exe
RSC=rc.exe
CPP=cl.exe

!IF  "$(CFG)" == "DelExe - Win32 Release"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "Release"
# PROP BASE Intermediate_Dir "Release"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "Release"
# PROP Intermediate_Dir "Release"
# PROP Target_Dir ""
OUTDIR=.\Release
INTDIR=.\Release

ALL : "$(OUTDIR)\DelExe.exe"

CLEAN : 
	-@erase ".\Release\DelExe.exe"
	-@erase ".\Release\DelExe.obj"
	-@erase ".\Release\DelExeBF.obj"
	-@erase ".\Release\RFoR.obj"
	-@erase ".\Release\TDelExe.obj"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

# ADD BASE CPP /nologo /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /YX /c
# ADD CPP /nologo /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /YX /c
# SUBTRACT CPP /Fr
CPP_PROJ=/nologo /ML /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS"\
 /Fp"$(INTDIR)/DelExe.pch" /YX /Fo"$(INTDIR)/" /c 
CPP_OBJS=.\Release/
CPP_SBRS=
# ADD BASE MTL /nologo /D "NDEBUG" /win32
# ADD MTL /nologo /D "NDEBUG" /win32
MTL_PROJ=/nologo /D "NDEBUG" /win32 
# ADD BASE RSC /l 0x409 /d "NDEBUG"
# ADD RSC /l 0x409 /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
BSC32_FLAGS=/nologo /o"$(OUTDIR)/DelExe.bsc" 
BSC32_SBRS=
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib /nologo /subsystem:windows /machine:I386
# ADD LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib /nologo /subsystem:windows /machine:I386
LINK32_FLAGS=kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib\
 advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib /nologo\
 /subsystem:windows /incremental:no /pdb:"$(OUTDIR)/DelExe.pdb" /machine:I386\
 /out:"$(OUTDIR)/DelExe.exe" 
LINK32_OBJS= \
	"$(INTDIR)/DelExe.obj" \
	"$(INTDIR)/DelExeBF.obj" \
	"$(INTDIR)/RFoR.obj" \
	"$(INTDIR)/TDelExe.obj"

"$(OUTDIR)\DelExe.exe" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ELSEIF  "$(CFG)" == "DelExe - Win32 Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "Debug"
# PROP BASE Intermediate_Dir "Debug"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "Debug"
# PROP Intermediate_Dir "Debug"
# PROP Target_Dir ""
OUTDIR=.\Debug
INTDIR=.\Debug

ALL : "$(OUTDIR)\DelExe.exe"

CLEAN : 
	-@erase ".\Debug\vc40.pdb"
	-@erase ".\Debug\vc40.idb"
	-@erase ".\Debug\DelExe.exe"
	-@erase ".\Debug\RFoR.obj"
	-@erase ".\Debug\TDelExe.obj"
	-@erase ".\Debug\DelExeBF.obj"
	-@erase ".\Debug\DelExe.obj"
	-@erase ".\Debug\DelExe.ilk"
	-@erase ".\Debug\DelExe.pdb"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

# ADD BASE CPP /nologo /W3 /Gm /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /YX /c
# ADD CPP /nologo /W3 /Gm /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /YX /c
# SUBTRACT CPP /Fr
CPP_PROJ=/nologo /MLd /W3 /Gm /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS"\
 /Fp"$(INTDIR)/DelExe.pch" /YX /Fo"$(INTDIR)/" /Fd"$(INTDIR)/" /c 
CPP_OBJS=.\Debug/
CPP_SBRS=
# ADD BASE MTL /nologo /D "_DEBUG" /win32
# ADD MTL /nologo /D "_DEBUG" /win32
MTL_PROJ=/nologo /D "_DEBUG" /win32 
# ADD BASE RSC /l 0x409 /d "_DEBUG"
# ADD RSC /l 0x409 /d "_DEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
BSC32_FLAGS=/nologo /o"$(OUTDIR)/DelExe.bsc" 
BSC32_SBRS=
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib /nologo /subsystem:windows /debug /machine:I386
# ADD LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib /nologo /subsystem:windows /debug /machine:I386
LINK32_FLAGS=kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib\
 advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib /nologo\
 /subsystem:windows /incremental:yes /pdb:"$(OUTDIR)/DelExe.pdb" /debug\
 /machine:I386 /out:"$(OUTDIR)/DelExe.exe" 
LINK32_OBJS= \
	"$(INTDIR)/RFoR.obj" \
	"$(INTDIR)/TDelExe.obj" \
	"$(INTDIR)/DelExeBF.obj" \
	"$(INTDIR)/DelExe.obj"

"$(OUTDIR)\DelExe.exe" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
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

.c{$(CPP_SBRS)}.sbr:
   $(CPP) $(CPP_PROJ) $<  

.cpp{$(CPP_SBRS)}.sbr:
   $(CPP) $(CPP_PROJ) $<  

.cxx{$(CPP_SBRS)}.sbr:
   $(CPP) $(CPP_PROJ) $<  

################################################################################
# Begin Target

# Name "DelExe - Win32 Release"
# Name "DelExe - Win32 Debug"

!IF  "$(CFG)" == "DelExe - Win32 Release"

!ELSEIF  "$(CFG)" == "DelExe - Win32 Debug"

!ENDIF 

################################################################################
# Begin Source File

SOURCE=.\TDelExe.c

!IF  "$(CFG)" == "DelExe - Win32 Release"

DEP_CPP_TDELE=\
	".\DelExe.h"\
	".\DelExeBF.h"\
	".\RFoR.h"\
	

"$(INTDIR)\TDelExe.obj" : $(SOURCE) $(DEP_CPP_TDELE) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "DelExe - Win32 Debug"

DEP_CPP_TDELE=\
	".\RFoR.h"\
	".\DelExe.h"\
	".\DelExeBF.h"\
	

"$(INTDIR)\TDelExe.obj" : $(SOURCE) $(DEP_CPP_TDELE) "$(INTDIR)"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\DelExe.c
DEP_CPP_DELEX=\
	".\DelExe.h"\
	

"$(INTDIR)\DelExe.obj" : $(SOURCE) $(DEP_CPP_DELEX) "$(INTDIR)"


# End Source File
################################################################################
# Begin Source File

SOURCE=.\DelExeBF.c
DEP_CPP_DELEXE=\
	".\DelExeBF.h"\
	

"$(INTDIR)\DelExeBF.obj" : $(SOURCE) $(DEP_CPP_DELEXE) "$(INTDIR)"


# End Source File
################################################################################
# Begin Source File

SOURCE=.\RFoR.c
DEP_CPP_RFOR_=\
	".\RFoR.h"\
	

"$(INTDIR)\RFoR.obj" : $(SOURCE) $(DEP_CPP_RFOR_) "$(INTDIR)"


# End Source File
# End Target
# End Project
################################################################################
