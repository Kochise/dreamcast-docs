# Microsoft Developer Studio Generated NMAKE File, Based on mindriv.dsp
!IF "$(CFG)" == ""
CFG=mindriv - Win32 Release
!MESSAGE No configuration specified. Defaulting to mindriv - Win32 Release.
!ENDIF 

!IF "$(CFG)" != "mindriv - Win32 Release" && "$(CFG)" != "mindriv - Win32 Debug"
!MESSAGE Invalid configuration "$(CFG)" specified.
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "mindriv.mak" CFG="mindriv - Win32 Release"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "mindriv - Win32 Release" (based on "Win32 (x86) Console Application")
!MESSAGE "mindriv - Win32 Debug" (based on "Win32 (x86) Console Application")
!MESSAGE 
!ERROR An invalid configuration is specified.
!ENDIF 

!IF "$(OS)" == "Windows_NT"
NULL=
!ELSE 
NULL=nul
!ENDIF 

CPP=cl.exe
RSC=rc.exe

!IF  "$(CFG)" == "mindriv - Win32 Release"

OUTDIR=.\Release
INTDIR=.\Release
# Begin Custom Macros
OutDir=.\.\Release
# End Custom Macros

ALL : "$(OUTDIR)\mindriv.exe"


CLEAN :
	-@erase "$(INTDIR)\mindriv.obj"
	-@erase "$(INTDIR)\mindriv.pch"
	-@erase "$(INTDIR)\premindr.obj"
	-@erase "$(OUTDIR)\mindriv.exe"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP_PROJ=/nologo /ML /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_CONSOLE" /Fp"$(INTDIR)\mindriv.pch" /Yu"premindr.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\mindriv.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
LINK32_FLAGS=kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:console /incremental:no /pdb:"$(OUTDIR)\mindriv.pdb" /machine:I386 /out:"$(OUTDIR)\mindriv.exe" 
LINK32_OBJS= \
	"$(INTDIR)\mindriv.obj" \
	"$(INTDIR)\premindr.obj"

"$(OUTDIR)\mindriv.exe" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ELSEIF  "$(CFG)" == "mindriv - Win32 Debug"

OUTDIR=.\Debug
INTDIR=.\Debug
# Begin Custom Macros
OutDir=.\.\Debug
# End Custom Macros

ALL : "$(OUTDIR)\mindriv.exe"


CLEAN :
	-@erase "$(INTDIR)\mindriv.obj"
	-@erase "$(INTDIR)\mindriv.pch"
	-@erase "$(INTDIR)\premindr.obj"
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(INTDIR)\vc60.pdb"
	-@erase "$(OUTDIR)\mindriv.exe"
	-@erase "$(OUTDIR)\mindriv.ilk"
	-@erase "$(OUTDIR)\mindriv.pdb"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP_PROJ=/nologo /MLd /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_CONSOLE" /Fp"$(INTDIR)\mindriv.pch" /Yu"premindr.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\mindriv.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
LINK32_FLAGS=kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:console /incremental:yes /pdb:"$(OUTDIR)\mindriv.pdb" /debug /machine:I386 /out:"$(OUTDIR)\mindriv.exe" 
LINK32_OBJS= \
	"$(INTDIR)\mindriv.obj" \
	"$(INTDIR)\premindr.obj"

"$(OUTDIR)\mindriv.exe" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ENDIF 

.c{$(INTDIR)}.obj::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.cpp{$(INTDIR)}.obj::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.cxx{$(INTDIR)}.obj::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.c{$(INTDIR)}.sbr::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.cpp{$(INTDIR)}.sbr::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.cxx{$(INTDIR)}.sbr::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<


!IF "$(NO_EXTERNAL_DEPS)" != "1"
!IF EXISTS("mindriv.dep")
!INCLUDE "mindriv.dep"
!ELSE 
!MESSAGE Warning: cannot find "mindriv.dep"
!ENDIF 
!ENDIF 


!IF "$(CFG)" == "mindriv - Win32 Release" || "$(CFG)" == "mindriv - Win32 Debug"
SOURCE=.\mindriv.cpp

"$(INTDIR)\mindriv.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\mindriv.pch"


SOURCE=.\premindr.cpp

!IF  "$(CFG)" == "mindriv - Win32 Release"

CPP_SWITCHES=/nologo /ML /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_CONSOLE" /Fp"$(INTDIR)\mindriv.pch" /Yc"premindr.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 

"$(INTDIR)\premindr.obj"	"$(INTDIR)\mindriv.pch" : $(SOURCE) "$(INTDIR)"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "mindriv - Win32 Debug"

CPP_SWITCHES=/nologo /MLd /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_CONSOLE" /Fp"$(INTDIR)\mindriv.pch" /Yc"premindr.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 

"$(INTDIR)\premindr.obj"	"$(INTDIR)\mindriv.pch" : $(SOURCE) "$(INTDIR)"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ENDIF 


!ENDIF 

