# Microsoft Developer Studio Generated NMAKE File, Format Version 4.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Application" 0x0101

!IF "$(CFG)" == ""
CFG=windonut - Win32 Debug
!MESSAGE No configuration specified.  Defaulting to windonut - Win32 Debug.
!ENDIF 

!IF "$(CFG)" != "windonut - Win32 Release" && "$(CFG)" !=\
 "windonut - Win32 Debug"
!MESSAGE Invalid configuration "$(CFG)" specified.
!MESSAGE You can specify a configuration when running NMAKE on this makefile
!MESSAGE by defining the macro CFG on the command line.  For example:
!MESSAGE 
!MESSAGE NMAKE /f "windonut.mak" CFG="windonut - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "windonut - Win32 Release" (based on "Win32 (x86) Application")
!MESSAGE "windonut - Win32 Debug" (based on "Win32 (x86) Application")
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
MTL=mktyplib.exe
RSC=rc.exe
CPP=cl.exe

!IF  "$(CFG)" == "windonut - Win32 Release"

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

ALL : "$(OUTDIR)\windonut.exe"

CLEAN : 
	-@erase ".\WinRel\windonut.exe"
	-@erase ".\WinRel\memory.obj"
	-@erase ".\WinRel\windows.obj"
	-@erase ".\WinRel\spritehigh.obj"
	-@erase ".\WinRel\spritelow.obj"
	-@erase ".\WinRel\windonut.obj"
	-@erase ".\WinRel\WAVE.OBJ"
	-@erase ".\WinRel\directsound.obj"
	-@erase ".\WinRel\Directdraw.obj"
	-@erase ".\WinRel\windonut.res"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

# ADD BASE CPP /nologo /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /FR /YX /c
# ADD CPP /nologo /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /YX /c
# SUBTRACT CPP /Fr
CPP_PROJ=/nologo /ML /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS"\
 /Fp"$(INTDIR)/windonut.pch" /YX /Fo"$(INTDIR)/" /c 
CPP_OBJS=.\WinRel/
CPP_SBRS=
# ADD BASE MTL /nologo /D "NDEBUG" /win32
# ADD MTL /nologo /D "NDEBUG" /win32
MTL_PROJ=/nologo /D "NDEBUG" /win32 
# ADD BASE RSC /l 0x409 /d "NDEBUG"
# ADD RSC /l 0x409 /d "NDEBUG"
RSC_PROJ=/l 0x409 /fo"$(INTDIR)/windonut.res" /d "NDEBUG" 
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
BSC32_FLAGS=/nologo /o"$(OUTDIR)/windonut.bsc" 
BSC32_SBRS=
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /machine:I386
# ADD LINK32 ddraw.lib dsound.lib winmm.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /machine:I386
LINK32_FLAGS=ddraw.lib dsound.lib winmm.lib kernel32.lib user32.lib gdi32.lib\
 winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib\
 uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /incremental:no\
 /pdb:"$(OUTDIR)/windonut.pdb" /machine:I386 /out:"$(OUTDIR)/windonut.exe" 
LINK32_OBJS= \
	"$(INTDIR)/memory.obj" \
	"$(INTDIR)/windows.obj" \
	"$(INTDIR)/spritehigh.obj" \
	"$(INTDIR)/spritelow.obj" \
	"$(INTDIR)/windonut.obj" \
	"$(INTDIR)/WAVE.OBJ" \
	"$(INTDIR)/directsound.obj" \
	"$(INTDIR)/Directdraw.obj" \
	"$(INTDIR)/windonut.res"

"$(OUTDIR)\windonut.exe" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ELSEIF  "$(CFG)" == "windonut - Win32 Debug"

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

ALL : "$(OUTDIR)\windonut.exe"

CLEAN : 
	-@erase ".\WinDebug\windonut.exe"
	-@erase ".\WinDebug\memory.obj"
	-@erase ".\WinDebug\windows.obj"
	-@erase ".\WinDebug\spritehigh.obj"
	-@erase ".\WinDebug\spritelow.obj"
	-@erase ".\WinDebug\windonut.obj"
	-@erase ".\WinDebug\WAVE.OBJ"
	-@erase ".\WinDebug\directsound.obj"
	-@erase ".\WinDebug\Directdraw.obj"
	-@erase ".\WinDebug\windonut.res"
	-@erase ".\WinDebug\windonut.ilk"
	-@erase ".\WinDebug\windonut.pdb"
	-@erase ".\WinDebug\vc40.pdb"
	-@erase ".\WinDebug\vc40.idb"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

# ADD BASE CPP /nologo /ML /W3 /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /FR /YX /c
# ADD CPP /nologo /W3 /Gm /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /YX /c
# SUBTRACT CPP /Fr
CPP_PROJ=/nologo /MLd /W3 /Gm /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS"\
 /Fp"$(INTDIR)/windonut.pch" /YX /Fo"$(INTDIR)/" /Fd"$(INTDIR)/" /c 
CPP_OBJS=.\WinDebug/
CPP_SBRS=
# ADD BASE MTL /nologo /D "_DEBUG" /win32
# ADD MTL /nologo /D "_DEBUG" /win32
MTL_PROJ=/nologo /D "_DEBUG" /win32 
# ADD BASE RSC /l 0x409 /d "_DEBUG"
# ADD RSC /l 0x409 /d "_DEBUG"
RSC_PROJ=/l 0x409 /fo"$(INTDIR)/windonut.res" /d "_DEBUG" 
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
BSC32_FLAGS=/nologo /o"$(OUTDIR)/windonut.bsc" 
BSC32_SBRS=
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /debug /machine:I386
# ADD LINK32 ddraw.lib dsound.lib winmm.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /debug /machine:I386
LINK32_FLAGS=ddraw.lib dsound.lib winmm.lib kernel32.lib user32.lib gdi32.lib\
 winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib\
 uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /incremental:yes\
 /pdb:"$(OUTDIR)/windonut.pdb" /debug /machine:I386\
 /out:"$(OUTDIR)/windonut.exe" 
LINK32_OBJS= \
	"$(INTDIR)/memory.obj" \
	"$(INTDIR)/windows.obj" \
	"$(INTDIR)/spritehigh.obj" \
	"$(INTDIR)/spritelow.obj" \
	"$(INTDIR)/windonut.obj" \
	"$(INTDIR)/WAVE.OBJ" \
	"$(INTDIR)/directsound.obj" \
	"$(INTDIR)/Directdraw.obj" \
	"$(INTDIR)/windonut.res"

"$(OUTDIR)\windonut.exe" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
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

# Name "windonut - Win32 Release"
# Name "windonut - Win32 Debug"

!IF  "$(CFG)" == "windonut - Win32 Release"

!ELSEIF  "$(CFG)" == "windonut - Win32 Debug"

!ENDIF 

################################################################################
# Begin Source File

SOURCE=.\memory.c
DEP_CPP_MEMOR=\
	".\windonut.h"\
	{$(INCLUDE)}"\ddraw.h"\
	{$(INCLUDE)}"\dsound.h"\
	".\basedefs.h"\
	".\windonutui.h"\
	".\memory.h"\
	".\directdraw.h"\
	".\spritelow.h"\
	".\spritehigh.h"\
	".\wave.h"\
	".\directsound.h"\
	

"$(INTDIR)\memory.obj" : $(SOURCE) $(DEP_CPP_MEMOR) "$(INTDIR)"


# End Source File
################################################################################
# Begin Source File

SOURCE=.\windows.c
DEP_CPP_WINDO=\
	".\windonut.h"\
	{$(INCLUDE)}"\ddraw.h"\
	{$(INCLUDE)}"\dsound.h"\
	".\basedefs.h"\
	".\windonutui.h"\
	".\memory.h"\
	".\directdraw.h"\
	".\spritelow.h"\
	".\spritehigh.h"\
	".\wave.h"\
	".\directsound.h"\
	

"$(INTDIR)\windows.obj" : $(SOURCE) $(DEP_CPP_WINDO) "$(INTDIR)"


# End Source File
################################################################################
# Begin Source File

SOURCE=.\spritehigh.c
DEP_CPP_SPRIT=\
	".\windonut.h"\
	{$(INCLUDE)}"\ddraw.h"\
	{$(INCLUDE)}"\dsound.h"\
	".\basedefs.h"\
	".\windonutui.h"\
	".\memory.h"\
	".\directdraw.h"\
	".\spritelow.h"\
	".\spritehigh.h"\
	".\wave.h"\
	".\directsound.h"\
	

"$(INTDIR)\spritehigh.obj" : $(SOURCE) $(DEP_CPP_SPRIT) "$(INTDIR)"


# End Source File
################################################################################
# Begin Source File

SOURCE=.\spritelow.c
DEP_CPP_SPRITE=\
	".\windonut.h"\
	{$(INCLUDE)}"\ddraw.h"\
	{$(INCLUDE)}"\dsound.h"\
	".\basedefs.h"\
	".\windonutui.h"\
	".\memory.h"\
	".\directdraw.h"\
	".\spritelow.h"\
	".\spritehigh.h"\
	".\wave.h"\
	".\directsound.h"\
	

"$(INTDIR)\spritelow.obj" : $(SOURCE) $(DEP_CPP_SPRITE) "$(INTDIR)"


# End Source File
################################################################################
# Begin Source File

SOURCE=.\windonut.c
DEP_CPP_WINDON=\
	".\windonut.h"\
	{$(INCLUDE)}"\ddraw.h"\
	{$(INCLUDE)}"\dsound.h"\
	".\basedefs.h"\
	".\windonutui.h"\
	".\memory.h"\
	".\directdraw.h"\
	".\spritelow.h"\
	".\spritehigh.h"\
	".\wave.h"\
	".\directsound.h"\
	

"$(INTDIR)\windonut.obj" : $(SOURCE) $(DEP_CPP_WINDON) "$(INTDIR)"


# End Source File
################################################################################
# Begin Source File

SOURCE=.\WAVE.C
DEP_CPP_WAVE_=\
	".\windonut.h"\
	{$(INCLUDE)}"\memory.h"\
	{$(INCLUDE)}"\ddraw.h"\
	{$(INCLUDE)}"\dsound.h"\
	".\basedefs.h"\
	".\windonutui.h"\
	".\memory.h"\
	".\directdraw.h"\
	".\spritelow.h"\
	".\spritehigh.h"\
	".\wave.h"\
	".\directsound.h"\
	

"$(INTDIR)\WAVE.OBJ" : $(SOURCE) $(DEP_CPP_WAVE_) "$(INTDIR)"


# End Source File
################################################################################
# Begin Source File

SOURCE=.\directsound.c
DEP_CPP_DIREC=\
	".\windonut.h"\
	{$(INCLUDE)}"\ddraw.h"\
	{$(INCLUDE)}"\dsound.h"\
	".\basedefs.h"\
	".\windonutui.h"\
	".\memory.h"\
	".\directdraw.h"\
	".\spritelow.h"\
	".\spritehigh.h"\
	".\wave.h"\
	".\directsound.h"\
	

"$(INTDIR)\directsound.obj" : $(SOURCE) $(DEP_CPP_DIREC) "$(INTDIR)"


# End Source File
################################################################################
# Begin Source File

SOURCE=.\Directdraw.c
DEP_CPP_DIRECT=\
	".\windonut.h"\
	{$(INCLUDE)}"\ddraw.h"\
	{$(INCLUDE)}"\dsound.h"\
	".\basedefs.h"\
	".\windonutui.h"\
	".\memory.h"\
	".\directdraw.h"\
	".\spritelow.h"\
	".\spritehigh.h"\
	".\wave.h"\
	".\directsound.h"\
	

"$(INTDIR)\Directdraw.obj" : $(SOURCE) $(DEP_CPP_DIRECT) "$(INTDIR)"


# End Source File
################################################################################
# Begin Source File

SOURCE=.\windonut.rc
DEP_RSC_WINDONU=\
	".\windonut.ico"\
	".\windonutui.h"\
	

"$(INTDIR)\windonut.res" : $(SOURCE) $(DEP_RSC_WINDONU) "$(INTDIR)"
   $(RSC) $(RSC_PROJ) $(SOURCE)


# End Source File
# End Target
# End Project
################################################################################
