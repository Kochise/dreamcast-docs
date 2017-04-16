# Microsoft Developer Studio Generated NMAKE File, Format Version 40001
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Application" 0x0101

!IF "$(CFG)" == ""
CFG=Moby Dick 3 - Win32 Debug
!MESSAGE No configuration specified.  Defaulting to Moby Dick 3 - Win32 Debug.
!ENDIF 

!IF "$(CFG)" != "Moby Dick 3 - Win32 Release" && "$(CFG)" !=\
 "Moby Dick 3 - Win32 Debug"
!MESSAGE Invalid configuration "$(CFG)" specified.
!MESSAGE You can specify a configuration when running NMAKE on this makefile
!MESSAGE by defining the macro CFG on the command line.  For example:
!MESSAGE 
!MESSAGE NMAKE /f "Moby Dick 3.mak" CFG="Moby Dick 3 - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "Moby Dick 3 - Win32 Release" (based on "Win32 (x86) Application")
!MESSAGE "Moby Dick 3 - Win32 Debug" (based on "Win32 (x86) Application")
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
# PROP Target_Last_Scanned "Moby Dick 3 - Win32 Debug"
CPP=cl.exe
RSC=rc.exe
MTL=mktyplib.exe

!IF  "$(CFG)" == "Moby Dick 3 - Win32 Release"

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

ALL : "$(OUTDIR)\Moby Dick 3.exe"

CLEAN : 
	-@erase ".\Release\Moby Dick 3.exe"
	-@erase ".\Release\ttfont.obj"
	-@erase ".\Release\wave.obj"
	-@erase ".\Release\moby.obj"
	-@erase ".\Release\draw.obj"
	-@erase ".\Release\sound.obj"
	-@erase ".\Release\moby.res"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

# ADD BASE CPP /nologo /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /YX /c
# ADD CPP /nologo /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /YX /c
CPP_PROJ=/nologo /ML /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS"\
 /Fp"$(INTDIR)/Moby Dick 3.pch" /YX /Fo"$(INTDIR)/" /c 
CPP_OBJS=.\Release/
CPP_SBRS=
# ADD BASE MTL /nologo /D "NDEBUG" /win32
# ADD MTL /nologo /D "NDEBUG" /win32
MTL_PROJ=/nologo /D "NDEBUG" /win32 
# ADD BASE RSC /l 0x409 /d "NDEBUG"
# ADD RSC /l 0x409 /d "NDEBUG"
RSC_PROJ=/l 0x409 /fo"$(INTDIR)/moby.res" /d "NDEBUG" 
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
BSC32_FLAGS=/nologo /o"$(OUTDIR)/Moby Dick 3.bsc" 
BSC32_SBRS=
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /machine:I386
# ADD LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib winmm.lib dsound.lib dxguid.lib ddraw.lib /nologo /subsystem:windows /machine:I386
LINK32_FLAGS=kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib\
 advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib\
 odbccp32.lib winmm.lib dsound.lib dxguid.lib ddraw.lib /nologo\
 /subsystem:windows /incremental:no /pdb:"$(OUTDIR)/Moby Dick 3.pdb"\
 /machine:I386 /out:"$(OUTDIR)/Moby Dick 3.exe" 
LINK32_OBJS= \
	"$(INTDIR)/ttfont.obj" \
	"$(INTDIR)/wave.obj" \
	"$(INTDIR)/moby.obj" \
	"$(INTDIR)/draw.obj" \
	"$(INTDIR)/sound.obj" \
	"$(INTDIR)/moby.res"

"$(OUTDIR)\Moby Dick 3.exe" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ELSEIF  "$(CFG)" == "Moby Dick 3 - Win32 Debug"

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

ALL : "$(OUTDIR)\Moby Dick 3.exe"

CLEAN : 
	-@erase ".\Debug\vc40.pdb"
	-@erase ".\Debug\vc40.idb"
	-@erase ".\Debug\Moby Dick 3.exe"
	-@erase ".\Debug\moby.obj"
	-@erase ".\Debug\ttfont.obj"
	-@erase ".\Debug\sound.obj"
	-@erase ".\Debug\wave.obj"
	-@erase ".\Debug\draw.obj"
	-@erase ".\Debug\moby.res"
	-@erase ".\Debug\Moby Dick 3.ilk"
	-@erase ".\Debug\Moby Dick 3.pdb"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

# ADD BASE CPP /nologo /W3 /Gm /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /YX /c
# ADD CPP /nologo /W3 /Gm /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /YX /c
CPP_PROJ=/nologo /MLd /W3 /Gm /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS"\
 /Fp"$(INTDIR)/Moby Dick 3.pch" /YX /Fo"$(INTDIR)/" /Fd"$(INTDIR)/" /c 
CPP_OBJS=.\Debug/
CPP_SBRS=
# ADD BASE MTL /nologo /D "_DEBUG" /win32
# ADD MTL /nologo /D "_DEBUG" /win32
MTL_PROJ=/nologo /D "_DEBUG" /win32 
# ADD BASE RSC /l 0x409 /d "_DEBUG"
# ADD RSC /l 0x409 /d "_DEBUG"
RSC_PROJ=/l 0x409 /fo"$(INTDIR)/moby.res" /d "_DEBUG" 
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
BSC32_FLAGS=/nologo /o"$(OUTDIR)/Moby Dick 3.bsc" 
BSC32_SBRS=
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /debug /machine:I386
# ADD LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib winmm.lib dsound.lib dxguid.lib ddraw.lib /nologo /subsystem:windows /debug /machine:I386
LINK32_FLAGS=kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib\
 advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib\
 odbccp32.lib winmm.lib dsound.lib dxguid.lib ddraw.lib /nologo\
 /subsystem:windows /incremental:yes /pdb:"$(OUTDIR)/Moby Dick 3.pdb" /debug\
 /machine:I386 /out:"$(OUTDIR)/Moby Dick 3.exe" 
LINK32_OBJS= \
	"$(INTDIR)/moby.obj" \
	"$(INTDIR)/ttfont.obj" \
	"$(INTDIR)/sound.obj" \
	"$(INTDIR)/wave.obj" \
	"$(INTDIR)/draw.obj" \
	"$(INTDIR)/moby.res"

"$(OUTDIR)\Moby Dick 3.exe" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
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

# Name "Moby Dick 3 - Win32 Release"
# Name "Moby Dick 3 - Win32 Debug"

!IF  "$(CFG)" == "Moby Dick 3 - Win32 Release"

!ELSEIF  "$(CFG)" == "Moby Dick 3 - Win32 Debug"

!ENDIF 

################################################################################
# Begin Source File

SOURCE=.\resource.h

!IF  "$(CFG)" == "Moby Dick 3 - Win32 Release"

!ELSEIF  "$(CFG)" == "Moby Dick 3 - Win32 Debug"

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\moby.cpp

!IF  "$(CFG)" == "Moby Dick 3 - Win32 Release"

DEP_CPP_MOBY_=\
	".\draw.h"\
	".\sound.h"\
	{$(INCLUDE)}"\dsound.h"\
	{$(INCLUDE)}"\d3dtypes.h"\
	
NODEP_CPP_MOBY_=\
	".\..\..\..\Dxsdk\sdk\inc\subwtype.h"\
	

"$(INTDIR)\moby.obj" : $(SOURCE) $(DEP_CPP_MOBY_) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "Moby Dick 3 - Win32 Debug"

DEP_CPP_MOBY_=\
	".\draw.h"\
	".\sound.h"\
	{$(INCLUDE)}"\ddraw.h"\
	{$(INCLUDE)}"\dsound.h"\
	{$(INCLUDE)}"\d3dtypes.h"\
	
NODEP_CPP_MOBY_=\
	".\..\..\..\Dxsdk\sdk\inc\subwtype.h"\
	

"$(INTDIR)\moby.obj" : $(SOURCE) $(DEP_CPP_MOBY_) "$(INTDIR)"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\moby.rc
DEP_RSC_MOBY_R=\
	".\ahab.bmp"\
	".\wake.bmp"\
	".\moby.bmp"\
	".\spout.bmp"\
	".\map.bmp"\
	".\blow.wav"\
	".\boing.wav"\
	

"$(INTDIR)\moby.res" : $(SOURCE) $(DEP_RSC_MOBY_R) "$(INTDIR)"
   $(RSC) $(RSC_PROJ) $(SOURCE)


# End Source File
################################################################################
# Begin Source File

SOURCE=.\sound.cpp

!IF  "$(CFG)" == "Moby Dick 3 - Win32 Release"

DEP_CPP_SOUND=\
	".\sound.h"\
	".\wave.h"\
	{$(INCLUDE)}"\dsound.h"\
	{$(INCLUDE)}"\d3dtypes.h"\
	
NODEP_CPP_SOUND=\
	".\..\..\..\Dxsdk\sdk\inc\subwtype.h"\
	

"$(INTDIR)\sound.obj" : $(SOURCE) $(DEP_CPP_SOUND) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "Moby Dick 3 - Win32 Debug"

DEP_CPP_SOUND=\
	".\sound.h"\
	".\wave.h"\
	{$(INCLUDE)}"\dsound.h"\
	{$(INCLUDE)}"\d3dtypes.h"\
	{$(INCLUDE)}"\ddraw.h"\
	
NODEP_CPP_SOUND=\
	".\..\..\..\Dxsdk\sdk\inc\subwtype.h"\
	

"$(INTDIR)\sound.obj" : $(SOURCE) $(DEP_CPP_SOUND) "$(INTDIR)"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\wave.cpp

!IF  "$(CFG)" == "Moby Dick 3 - Win32 Release"

DEP_CPP_WAVE_=\
	".\wave.h"\
	{$(INCLUDE)}"\dsound.h"\
	{$(INCLUDE)}"\d3dtypes.h"\
	
NODEP_CPP_WAVE_=\
	".\..\..\..\Dxsdk\sdk\inc\subwtype.h"\
	

"$(INTDIR)\wave.obj" : $(SOURCE) $(DEP_CPP_WAVE_) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "Moby Dick 3 - Win32 Debug"

DEP_CPP_WAVE_=\
	".\wave.h"\
	{$(INCLUDE)}"\dsound.h"\
	{$(INCLUDE)}"\d3dtypes.h"\
	{$(INCLUDE)}"\ddraw.h"\
	
NODEP_CPP_WAVE_=\
	".\..\..\..\Dxsdk\sdk\inc\subwtype.h"\
	

"$(INTDIR)\wave.obj" : $(SOURCE) $(DEP_CPP_WAVE_) "$(INTDIR)"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\draw.cpp

!IF  "$(CFG)" == "Moby Dick 3 - Win32 Release"

DEP_CPP_DRAW_=\
	".\draw.h"\
	".\ttfont.h"\
	

"$(INTDIR)\draw.obj" : $(SOURCE) $(DEP_CPP_DRAW_) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "Moby Dick 3 - Win32 Debug"

DEP_CPP_DRAW_=\
	".\draw.h"\
	".\ttfont.h"\
	{$(INCLUDE)}"\ddraw.h"\
	

"$(INTDIR)\draw.obj" : $(SOURCE) $(DEP_CPP_DRAW_) "$(INTDIR)"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\ttfont.cpp
DEP_CPP_TTFON=\
	".\ttfont.h"\
	

"$(INTDIR)\ttfont.obj" : $(SOURCE) $(DEP_CPP_TTFON) "$(INTDIR)"


# End Source File
# End Target
# End Project
################################################################################
