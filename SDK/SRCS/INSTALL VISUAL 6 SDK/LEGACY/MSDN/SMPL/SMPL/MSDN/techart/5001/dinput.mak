# Microsoft Developer Studio Generated NMAKE File, Format Version 4.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Application" 0x0101

!IF "$(CFG)" == ""
CFG=DInput - Win32 Debug
!MESSAGE No configuration specified.  Defaulting to DInput - Win32 Debug.
!ENDIF 

!IF "$(CFG)" != "DInput - Win32 Release" && "$(CFG)" != "DInput - Win32 Debug"
!MESSAGE Invalid configuration "$(CFG)" specified.
!MESSAGE You can specify a configuration when running NMAKE on this makefile
!MESSAGE by defining the macro CFG on the command line.  For example:
!MESSAGE 
!MESSAGE NMAKE /f "DInput.mak" CFG="DInput - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "DInput - Win32 Release" (based on "Win32 (x86) Application")
!MESSAGE "DInput - Win32 Debug" (based on "Win32 (x86) Application")
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
# PROP Target_Last_Scanned "DInput - Win32 Debug"
CPP=cl.exe
RSC=rc.exe
MTL=mktyplib.exe

!IF  "$(CFG)" == "DInput - Win32 Release"

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

ALL : "$(OUTDIR)\DInput.exe"

CLEAN : 
	-@erase ".\Release\DInput.exe"
	-@erase ".\Release\input.obj"
	-@erase ".\Release\output.obj"
	-@erase ".\Release\DIMain.obj"
	-@erase ".\Release\dinput.res"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

# ADD BASE CPP /nologo /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /YX /c
# ADD CPP /nologo /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /YX /c
CPP_PROJ=/nologo /ML /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS"\
 /Fp"$(INTDIR)/DInput.pch" /YX /Fo"$(INTDIR)/" /c 
CPP_OBJS=.\Release/
CPP_SBRS=
# ADD BASE MTL /nologo /D "NDEBUG" /win32
# ADD MTL /nologo /D "NDEBUG" /win32
MTL_PROJ=/nologo /D "NDEBUG" /win32 
# ADD BASE RSC /l 0x409 /d "NDEBUG"
# ADD RSC /l 0x409 /d "NDEBUG"
RSC_PROJ=/l 0x409 /fo"$(INTDIR)/dinput.res" /d "NDEBUG" 
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
BSC32_FLAGS=/nologo /o"$(OUTDIR)/DInput.bsc" 
BSC32_SBRS=
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /machine:I386
# ADD LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib winmm.lib dinput.lib dxguid.lib /nologo /subsystem:windows /machine:I386 /nodefaultlib:"libc.lib" /nodefaultlib:" libcmt.lib" /nodefaultlib:" msvcrt.lib" /nodefaultlib:" libcd.lib" /nodefaultlib:" msvcrtd.lib"
# SUBTRACT LINK32 /nodefaultlib
LINK32_FLAGS=kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib\
 advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib\
 odbccp32.lib winmm.lib dinput.lib dxguid.lib /nologo /subsystem:windows\
 /incremental:no /pdb:"$(OUTDIR)/DInput.pdb" /machine:I386\
 /nodefaultlib:"libc.lib" /nodefaultlib:" libcmt.lib"\
 /nodefaultlib:" msvcrt.lib" /nodefaultlib:" libcd.lib"\
 /nodefaultlib:" msvcrtd.lib" /out:"$(OUTDIR)/DInput.exe" 
LINK32_OBJS= \
	"$(INTDIR)/input.obj" \
	"$(INTDIR)/output.obj" \
	"$(INTDIR)/DIMain.obj" \
	"$(INTDIR)/dinput.res"

"$(OUTDIR)\DInput.exe" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ELSEIF  "$(CFG)" == "DInput - Win32 Debug"

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

ALL : "$(OUTDIR)\DInput.exe"

CLEAN : 
	-@erase ".\Debug\vc40.pdb"
	-@erase ".\Debug\vc40.idb"
	-@erase ".\Debug\DInput.exe"
	-@erase ".\Debug\output.obj"
	-@erase ".\Debug\input.obj"
	-@erase ".\Debug\DIMain.obj"
	-@erase ".\Debug\dinput.res"
	-@erase ".\Debug\DInput.ilk"
	-@erase ".\Debug\DInput.pdb"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

# ADD BASE CPP /nologo /W3 /Gm /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /YX /c
# ADD CPP /nologo /W3 /Gm /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /YX /c
CPP_PROJ=/nologo /MLd /W3 /Gm /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS"\
 /Fp"$(INTDIR)/DInput.pch" /YX /Fo"$(INTDIR)/" /Fd"$(INTDIR)/" /c 
CPP_OBJS=.\Debug/
CPP_SBRS=
# ADD BASE MTL /nologo /D "_DEBUG" /win32
# ADD MTL /nologo /D "_DEBUG" /win32
MTL_PROJ=/nologo /D "_DEBUG" /win32 
# ADD BASE RSC /l 0x409 /d "_DEBUG"
# ADD RSC /l 0x409 /d "_DEBUG"
RSC_PROJ=/l 0x409 /fo"$(INTDIR)/dinput.res" /d "_DEBUG" 
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
BSC32_FLAGS=/nologo /o"$(OUTDIR)/DInput.bsc" 
BSC32_SBRS=
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /debug /machine:I386
# ADD LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib winmm.lib dinput.lib dxguid.lib /nologo /subsystem:windows /debug /machine:I386 /nodefaultlib:"libc.lib" /nodefaultlib:" libcmt.lib" /nodefaultlib:" msvcrt.lib" /nodefaultlib:" libcd.lib" /nodefaultlib:" msvcrtd.lib"
# SUBTRACT LINK32 /nodefaultlib
LINK32_FLAGS=kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib\
 advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib\
 odbccp32.lib winmm.lib dinput.lib dxguid.lib /nologo /subsystem:windows\
 /incremental:yes /pdb:"$(OUTDIR)/DInput.pdb" /debug /machine:I386\
 /nodefaultlib:"libc.lib" /nodefaultlib:" libcmt.lib"\
 /nodefaultlib:" msvcrt.lib" /nodefaultlib:" libcd.lib"\
 /nodefaultlib:" msvcrtd.lib" /out:"$(OUTDIR)/DInput.exe" 
LINK32_OBJS= \
	"$(INTDIR)/output.obj" \
	"$(INTDIR)/input.obj" \
	"$(INTDIR)/DIMain.obj" \
	"$(INTDIR)/dinput.res"

"$(OUTDIR)\DInput.exe" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
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

# Name "DInput - Win32 Release"
# Name "DInput - Win32 Debug"

!IF  "$(CFG)" == "DInput - Win32 Release"

!ELSEIF  "$(CFG)" == "DInput - Win32 Debug"

!ENDIF 

################################################################################
# Begin Source File

SOURCE=.\input.cpp
DEP_CPP_INPUT=\
	{$(INCLUDE)}"\dinput.h"\
	".\input.h"\
	".\output.h"\
	

"$(INTDIR)\input.obj" : $(SOURCE) $(DEP_CPP_INPUT) "$(INTDIR)"


# End Source File
################################################################################
# Begin Source File

SOURCE=.\DIMain.cpp

!IF  "$(CFG)" == "DInput - Win32 Release"

DEP_CPP_DIMAI=\
	{$(INCLUDE)}"\dinput.h"\
	".\input.h"\
	
NODEP_CPP_DIMAI=\
	".\resource.h"\
	

"$(INTDIR)\DIMain.obj" : $(SOURCE) $(DEP_CPP_DIMAI) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "DInput - Win32 Debug"

DEP_CPP_DIMAI=\
	{$(INCLUDE)}"\dinput.h"\
	".\input.h"\
	
NODEP_CPP_DIMAI=\
	".\diMouseInstance"\
	

"$(INTDIR)\DIMain.obj" : $(SOURCE) $(DEP_CPP_DIMAI) "$(INTDIR)"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\dinput.rc
DEP_RSC_DINPU=\
	".\icon1.ico"\
	

"$(INTDIR)\dinput.res" : $(SOURCE) $(DEP_RSC_DINPU) "$(INTDIR)"
   $(RSC) $(RSC_PROJ) $(SOURCE)


# End Source File
################################################################################
# Begin Source File

SOURCE=.\output.cpp
DEP_CPP_OUTPU=\
	".\output.h"\
	

"$(INTDIR)\output.obj" : $(SOURCE) $(DEP_CPP_OUTPU) "$(INTDIR)"


# End Source File
# End Target
# End Project
################################################################################
