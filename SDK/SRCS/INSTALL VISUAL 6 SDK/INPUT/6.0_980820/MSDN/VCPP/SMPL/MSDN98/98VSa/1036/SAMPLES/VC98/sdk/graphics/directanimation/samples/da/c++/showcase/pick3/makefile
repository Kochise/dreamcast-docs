# Microsoft Developer Studio Generated NMAKE File, Based on pick3.dsp
!IF "$(CFG)" == ""
CFG=pick3 - Win32 Release
!MESSAGE No configuration specified. Defaulting to pick3 - Win32 Release.
!ENDIF 

!IF "$(CFG)" != "pick3 - Win32 Release" && "$(CFG)" != "pick3 - Win32 Debug"
!MESSAGE Invalid configuration "$(CFG)" specified.
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "pick3.mak" CFG="pick3 - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "pick3 - Win32 Release" (based on "Win32 (x86) Application")
!MESSAGE "pick3 - Win32 Debug" (based on "Win32 (x86) Application")
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

!IF  "$(CFG)" == "pick3 - Win32 Release"

OUTDIR=.
INTDIR=.
# Begin Custom Macros
OutDir=.
# End Custom Macros

!IF "$(RECURSE)" == "0" 

ALL : "$(OUTDIR)\pick3.exe"

!ELSE 

ALL : "$(OUTDIR)\pick3.exe"

!ENDIF 

CLEAN :
	-@erase "$(INTDIR)\dxa.obj"
	-@erase "$(INTDIR)\pick3.obj"
	-@erase "$(INTDIR)\vc50.idb"
	-@erase "$(OUTDIR)\pick3.exe"

CPP_PROJ=/nologo /ML /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS"\
 /Fp"$(INTDIR)\pick3.pch" /YX /FD /c 
CPP_OBJS=.
CPP_SBRS=.
MTL_PROJ=/nologo /D "NDEBUG" /mktyplib203 /o NUL /win32 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\pick3.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
LINK32_FLAGS=kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib\
 advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib\
 odbccp32.lib guids.lib /nologo /subsystem:windows /incremental:no\
 /pdb:"$(OUTDIR)\pick3.pdb" /machine:I386 /out:"$(OUTDIR)\pick3.exe" 
LINK32_OBJS= \
	"$(INTDIR)\dxa.obj" \
	"$(INTDIR)\pick3.obj"

"$(OUTDIR)\pick3.exe" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ELSEIF  "$(CFG)" == "pick3 - Win32 Debug"

OUTDIR=.
INTDIR=.
# Begin Custom Macros
OutDir=.
# End Custom Macros

!IF "$(RECURSE)" == "0" 

ALL : "$(OUTDIR)\pick3.exe"

!ELSE 

ALL : "$(OUTDIR)\pick3.exe"

!ENDIF 

CLEAN :
	-@erase "$(INTDIR)\dxa.obj"
	-@erase "$(INTDIR)\pick3.obj"
	-@erase "$(INTDIR)\vc50.idb"
	-@erase "$(INTDIR)\vc50.pdb"
	-@erase "$(OUTDIR)\pick3.exe"
	-@erase "$(OUTDIR)\pick3.ilk"
	-@erase "$(OUTDIR)\pick3.pdb"

CPP_PROJ=/nologo /MLd /W3 /Gm /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS"\
 /Fp"$(INTDIR)\pick3.pch" /YX /FD /c 
CPP_OBJS=.
CPP_SBRS=.
MTL_PROJ=/nologo /D "_DEBUG" /mktyplib203 /o NUL /win32 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\pick3.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
LINK32_FLAGS=guids.lib kernel32.lib user32.lib gdi32.lib winspool.lib\
 comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib\
 odbc32.lib odbccp32.lib /nologo /subsystem:windows /incremental:yes\
 /pdb:"$(OUTDIR)\pick3.pdb" /debug /machine:I386 /out:"$(OUTDIR)\pick3.exe"\
 /pdbtype:sept 
LINK32_OBJS= \
	"$(INTDIR)\dxa.obj" \
	"$(INTDIR)\pick3.obj"

"$(OUTDIR)\pick3.exe" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
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


!IF "$(CFG)" == "pick3 - Win32 Release" || "$(CFG)" == "pick3 - Win32 Debug"
SOURCE=.\dxa.cpp
DEP_CPP_DXA_C=\
	".\dxa.h"\
	

"$(INTDIR)\dxa.obj" : $(SOURCE) $(DEP_CPP_DXA_C) "$(INTDIR)"


SOURCE=.\pick3.cpp
DEP_CPP_PICK3=\
	".\dxa.h"\
	{$(INCLUDE)}"ddrawex.h"\
	

"$(INTDIR)\pick3.obj" : $(SOURCE) $(DEP_CPP_PICK3) "$(INTDIR)"



!ENDIF 
