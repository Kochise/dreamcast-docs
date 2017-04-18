# Microsoft Developer Studio Generated NMAKE File, Based on wbpost.dsp
!IF "$(CFG)" == ""
CFG=wbpost - Win32 Debug
!MESSAGE No configuration specified. Defaulting to wbpost - Win32 Debug.
!ENDIF 

!IF "$(CFG)" != "wbpost - Win32 Release" && "$(CFG)" != "wbpost - Win32 Debug"
!MESSAGE Invalid configuration "$(CFG)" specified.
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "wbpost.mak" CFG="wbpost - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "wbpost - Win32 Release" (based on "Win32 (x86) Console Application")
!MESSAGE "wbpost - Win32 Debug" (based on "Win32 (x86) Console Application")
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

!IF  "$(CFG)" == "wbpost - Win32 Release"

OUTDIR=.\Release
INTDIR=.\Release
# Begin Custom Macros
OutDir=.\Release
# End Custom Macros

!IF "$(RECURSE)" == "0" 

ALL : "wpspi.h" "$(OUTDIR)\wbpost.exe"

!ELSE 

ALL : "wpspi.h" "$(OUTDIR)\wbpost.exe"

!ENDIF 

CLEAN :
	-@erase "$(INTDIR)\vc50.idb"
	-@erase "$(INTDIR)\wbpost.obj"
	-@erase "$(OUTDIR)\wbpost.exe"
	-@erase "wpspi.h"
	-@erase "dlldata.c"
	-@erase "wpspi_i.c"
	-@erase "wpspi_p.c"


"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP_PROJ=/nologo /ML /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_CONSOLE" /D\
 "_MBCS" /Fp"$(INTDIR)\wbpost.pch" /YX /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 
CPP_OBJS=.\Release/
CPP_SBRS=.
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\wbpost.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
LINK32_FLAGS=webpost.lib kernel32.lib user32.lib gdi32.lib winspool.lib\
 comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib\
 odbc32.lib odbccp32.lib /nologo /subsystem:console /incremental:no\
 /pdb:"$(OUTDIR)\wbpost.pdb" /out:"$(OUTDIR)\wbpost.exe"

LINK32_OBJS= \
	"$(INTDIR)\wbpost.obj"

"$(OUTDIR)\wbpost.exe" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ELSEIF  "$(CFG)" == "wbpost - Win32 Debug"

OUTDIR=.\Debug
INTDIR=.\Debug
# Begin Custom Macros
OutDir=.\Debug
# End Custom Macros

!IF "$(RECURSE)" == "0" 

ALL : "wpspi.h" "$(OUTDIR)\wbpost.exe"

!ELSE 

ALL : "wpspi.h" "$(OUTDIR)\wbpost.exe"

!ENDIF 

CLEAN :
	-@erase "$(INTDIR)\vc50.idb"
	-@erase "$(INTDIR)\vc50.pdb"
	-@erase "$(INTDIR)\wbpost.obj"
	-@erase "$(OUTDIR)\wbpost.exe"
	-@erase "$(OUTDIR)\wbpost.ilk"
	-@erase "$(OUTDIR)\wbpost.pdb"
	-@erase "wpspi.h" 
	-@erase "dlldata.c"
	-@erase "wpspi_i.c"
	-@erase "wpspi_p.c"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP_PROJ=/nologo /MLd /W3 /Gm /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_CONSOLE"\
 /D "_MBCS" /Fp"$(INTDIR)\wbpost.pch" /YX /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD\
 /c 
CPP_OBJS=.\Debug/
CPP_SBRS=.
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\wbpost.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
LINK32_FLAGS=webpost.lib kernel32.lib user32.lib gdi32.lib winspool.lib\
 comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib\
 odbc32.lib odbccp32.lib /nologo /subsystem:console /incremental:yes\
 /pdb:"$(OUTDIR)\wbpost.pdb" /debug /out:"$(OUTDIR)\wbpost.exe"\
 /pdbtype:sept
LINK32_OBJS= \
	"$(INTDIR)\wbpost.obj"

"$(OUTDIR)\wbpost.exe" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
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


!IF "$(CFG)" == "wbpost - Win32 Release" || "$(CFG)" == "wbpost - Win32 Debug"
SOURCE=.\wbpost.cpp

!IF  "$(CFG)" == "wbpost - Win32 Release"

DEP_CPP_WBPOS=

"$(INTDIR)\wbpost.obj" : $(SOURCE) $(DEP_CPP_WBPOS) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "wbpost - Win32 Debug"

DEP_CPP_WBPOS=

"$(INTDIR)\wbpost.obj" : $(SOURCE) $(DEP_CPP_WBPOS) "$(INTDIR)"


!ENDIF 

SOURCE=wpspi.idl

!IF  "$(CFG)" == "wbpost - Win32 Release"

InputDir=
ProjDir=.
InputPath=wpspi.idl

"wpspi.h" : $(INTDIR) "$(OUTDIR)"
        midl /h $(ProjDir)\wpspi.h wpspi.idl

!ELSEIF  "$(CFG)" == "wbpost - Win32 Debug"

InputDir=
ProjDir=.
InputPath=wpspi.idl

"wpspi.h" : $(INTDIR) "$(OUTDIR)"
        midl /h $(ProjDir)\wpspi.h wpspi.idl

!ENDIF

!ENDIF 
