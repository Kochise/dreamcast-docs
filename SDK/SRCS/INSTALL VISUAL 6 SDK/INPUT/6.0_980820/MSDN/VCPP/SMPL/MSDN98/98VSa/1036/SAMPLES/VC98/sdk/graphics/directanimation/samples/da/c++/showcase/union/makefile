# Microsoft Developer Studio Generated NMAKE File, Based on union.dsp
!IF "$(CFG)" == ""
CFG=union - Win32 Release
!MESSAGE No configuration specified. Defaulting to union - Win32 Release.
!ENDIF 

!IF "$(CFG)" != "union - Win32 Release" && "$(CFG)" != "union - Win32 Debug"
!MESSAGE Invalid configuration "$(CFG)" specified.
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "union.mak" CFG="union - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "union - Win32 Release" (based on "Win32 (x86) Application")
!MESSAGE "union - Win32 Debug" (based on "Win32 (x86) Application")
!MESSAGE 
!ERROR An invalid configuration is specified.
!ENDIF 

!IF "$(OS)" == "Windows_NT"
NULL=
!ELSE 
NULL=nul
!ENDIF 

CPP=cl.exe
MTL=midl.exe
RSC=rc.exe

!IF  "$(CFG)" == "union - Win32 Release"

OUTDIR=.
INTDIR=.
# Begin Custom Macros
OutDir=.
# End Custom Macros

!IF "$(RECURSE)" == "0" 

ALL : "$(OUTDIR)\union.exe"

!ELSE 

ALL : "$(OUTDIR)\union.exe"

!ENDIF 

CLEAN :
	-@erase "$(INTDIR)\dxa.obj"
	-@erase "$(INTDIR)\union.obj"
	-@erase "$(INTDIR)\vc50.idb"
	-@erase "$(OUTDIR)\union.exe"

CPP_PROJ=/nologo /ML /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS"\
 /Fp"$(INTDIR)\union.pch" /YX /FD /c 
CPP_OBJS=.
CPP_SBRS=.
MTL_PROJ=/nologo /D "NDEBUG" /mktyplib203 /o NUL /win32 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\union.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
LINK32_FLAGS=kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib\
 advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib\
 odbccp32.lib guids.lib /nologo /subsystem:windows /incremental:no\
 /pdb:"$(OUTDIR)\union.pdb" /machine:I386 /out:"$(OUTDIR)\union.exe" 
LINK32_OBJS= \
	"$(INTDIR)\dxa.obj" \
	"$(INTDIR)\union.obj"

"$(OUTDIR)\union.exe" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ELSEIF  "$(CFG)" == "union - Win32 Debug"

OUTDIR=.
INTDIR=.
# Begin Custom Macros
OutDir=.
# End Custom Macros

!IF "$(RECURSE)" == "0" 

ALL : "$(OUTDIR)\union.exe"

!ELSE 

ALL : "$(OUTDIR)\union.exe"

!ENDIF 

CLEAN :
	-@erase "$(INTDIR)\dxa.obj"
	-@erase "$(INTDIR)\union.obj"
	-@erase "$(INTDIR)\vc50.idb"
	-@erase "$(INTDIR)\vc50.pdb"
	-@erase "$(OUTDIR)\union.exe"
	-@erase "$(OUTDIR)\union.ilk"
	-@erase "$(OUTDIR)\union.pdb"

CPP_PROJ=/nologo /MLd /W3 /Gm /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS"\
 /Fp"$(INTDIR)\union.pch" /YX /FD /c 
CPP_OBJS=.
CPP_SBRS=.
MTL_PROJ=/nologo /D "_DEBUG" /mktyplib203 /o NUL /win32 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\union.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
LINK32_FLAGS=kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib\
 advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib\
 odbccp32.lib guids.lib /nologo /subsystem:windows /incremental:yes\
 /pdb:"$(OUTDIR)\union.pdb" /debug /machine:I386 /out:"$(OUTDIR)\union.exe"\
 /pdbtype:sept 
LINK32_OBJS= \
	"$(INTDIR)\dxa.obj" \
	"$(INTDIR)\union.obj"

"$(OUTDIR)\union.exe" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ENDIF 

.c{$(CPP_OBJS)}.obj::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.cpp{$(CPP_OBJS)}.obj::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.cxx{$(CPP_OBJS)}.obj::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.c{$(CPP_SBRS)}.sbr::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.cpp{$(CPP_SBRS)}.sbr::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.cxx{$(CPP_SBRS)}.sbr::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<


!IF "$(CFG)" == "union - Win32 Release" || "$(CFG)" == "union - Win32 Debug"
SOURCE=.\dxa.cpp
DEP_CPP_DXA_C=\
	".\dxa.h"\
	

"$(INTDIR)\dxa.obj" : $(SOURCE) $(DEP_CPP_DXA_C) "$(INTDIR)"


SOURCE=.\union.cpp
DEP_CPP_UNION=\
	".\dxa.h"\
	{$(INCLUDE)}"ddrawex.h"\
	

"$(INTDIR)\union.obj" : $(SOURCE) $(DEP_CPP_UNION) "$(INTDIR)"



!ENDIF 
