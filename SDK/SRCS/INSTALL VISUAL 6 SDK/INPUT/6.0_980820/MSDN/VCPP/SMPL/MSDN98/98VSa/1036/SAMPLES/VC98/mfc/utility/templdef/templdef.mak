# Microsoft Developer Studio Generated NMAKE File, Based on templdef.dsp
!IF "$(CFG)" == ""
CFG=TemplDef - Win32 Release
!MESSAGE No configuration specified. Defaulting to TemplDef - Win32 Release.
!ENDIF 

!IF "$(CFG)" != "TemplDef - Win32 Release" && "$(CFG)" != "TemplDef - Win32 Debug"
!MESSAGE Invalid configuration "$(CFG)" specified.
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "templdef.mak" CFG="TemplDef - Win32 Release"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "TemplDef - Win32 Release" (based on "Win32 (x86) Console Application")
!MESSAGE "TemplDef - Win32 Debug" (based on "Win32 (x86) Console Application")
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

!IF  "$(CFG)" == "TemplDef - Win32 Release"

OUTDIR=.\Release
INTDIR=.\Release
# Begin Custom Macros
OutDir=.\.\Release
# End Custom Macros

ALL : "$(OUTDIR)\templdef.exe" "$(OUTDIR)\templdef.bsc"


CLEAN :
	-@erase "$(INTDIR)\Templdef.obj"
	-@erase "$(INTDIR)\Templdef.sbr"
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(OUTDIR)\templdef.bsc"
	-@erase "$(OUTDIR)\templdef.exe"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP_PROJ=/nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_CONSOLE" /D "_AFXDLL" /D "_MBCS" /FR"$(INTDIR)\\" /Fp"$(INTDIR)\templdef.pch" /YX /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\templdef.bsc" 
BSC32_SBRS= \
	"$(INTDIR)\Templdef.sbr"

"$(OUTDIR)\templdef.bsc" : "$(OUTDIR)" $(BSC32_SBRS)
    $(BSC32) @<<
  $(BSC32_FLAGS) $(BSC32_SBRS)
<<

LINK32=link.exe
LINK32_FLAGS=/nologo /subsystem:console /incremental:no /pdb:"$(OUTDIR)\templdef.pdb" /machine:I386 /out:"$(OUTDIR)\templdef.exe" 
LINK32_OBJS= \
	"$(INTDIR)\Templdef.obj"

"$(OUTDIR)\templdef.exe" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ELSEIF  "$(CFG)" == "TemplDef - Win32 Debug"

OUTDIR=.\Debug
INTDIR=.\Debug
# Begin Custom Macros
OutDir=.\.\Debug
# End Custom Macros

ALL : "$(OUTDIR)\templdef.exe" "$(OUTDIR)\templdef.bsc"


CLEAN :
	-@erase "$(INTDIR)\Templdef.obj"
	-@erase "$(INTDIR)\Templdef.sbr"
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(INTDIR)\vc60.pdb"
	-@erase "$(OUTDIR)\templdef.bsc"
	-@erase "$(OUTDIR)\templdef.exe"
	-@erase "$(OUTDIR)\templdef.ilk"
	-@erase "$(OUTDIR)\templdef.pdb"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP_PROJ=/nologo /MDd /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_CONSOLE" /D "_AFXDLL" /D "_MBCS" /FR"$(INTDIR)\\" /Fp"$(INTDIR)\templdef.pch" /YX /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\templdef.bsc" 
BSC32_SBRS= \
	"$(INTDIR)\Templdef.sbr"

"$(OUTDIR)\templdef.bsc" : "$(OUTDIR)" $(BSC32_SBRS)
    $(BSC32) @<<
  $(BSC32_FLAGS) $(BSC32_SBRS)
<<

LINK32=link.exe
LINK32_FLAGS=/nologo /subsystem:console /incremental:yes /pdb:"$(OUTDIR)\templdef.pdb" /debug /machine:I386 /out:"$(OUTDIR)\templdef.exe" 
LINK32_OBJS= \
	"$(INTDIR)\Templdef.obj"

"$(OUTDIR)\templdef.exe" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
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
!IF EXISTS("templdef.dep")
!INCLUDE "templdef.dep"
!ELSE 
!MESSAGE Warning: cannot find "templdef.dep"
!ENDIF 
!ENDIF 


!IF "$(CFG)" == "TemplDef - Win32 Release" || "$(CFG)" == "TemplDef - Win32 Debug"
SOURCE=.\Templdef.cpp

"$(INTDIR)\Templdef.obj"	"$(INTDIR)\Templdef.sbr" : $(SOURCE) "$(INTDIR)"



!ENDIF 

