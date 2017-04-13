# Microsoft Developer Studio Generated NMAKE File, Based on Tear.dsp
!IF "$(CFG)" == ""
CFG=Tear - Win32 Release
!MESSAGE No configuration specified. Defaulting to Tear - Win32 Release.
!ENDIF 

!IF "$(CFG)" != "Tear - Win32 Release" && "$(CFG)" != "Tear - Win32 Debug" && "$(CFG)" != "Tear - Win32 Static Debug" && "$(CFG)" != "Tear - Win32 Static Release"
!MESSAGE Invalid configuration "$(CFG)" specified.
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "Tear.mak" CFG="Tear - Win32 Release"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "Tear - Win32 Release" (based on "Win32 (x86) Console Application")
!MESSAGE "Tear - Win32 Debug" (based on "Win32 (x86) Console Application")
!MESSAGE "Tear - Win32 Static Debug" (based on "Win32 (x86) Console Application")
!MESSAGE "Tear - Win32 Static Release" (based on "Win32 (x86) Console Application")
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

!IF  "$(CFG)" == "Tear - Win32 Release"

OUTDIR=.\Release
INTDIR=.\Release
# Begin Custom Macros
OutDir=.\.\Release
# End Custom Macros

ALL : "$(OUTDIR)\Tear.exe"


CLEAN :
	-@erase "$(INTDIR)\tear.obj"
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(OUTDIR)\Tear.exe"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP_PROJ=/nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_CONSOLE" /D "_AFXDLL" /D "_MBCS" /Fp"$(INTDIR)\Tear.pch" /YX /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\Tear.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
LINK32_FLAGS=/nologo /subsystem:console /incremental:no /pdb:"$(OUTDIR)\Tear.pdb" /machine:I386 /out:"$(OUTDIR)\Tear.exe" 
LINK32_OBJS= \
	"$(INTDIR)\tear.obj"

"$(OUTDIR)\Tear.exe" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ELSEIF  "$(CFG)" == "Tear - Win32 Debug"

OUTDIR=.\Debug
INTDIR=.\Debug
# Begin Custom Macros
OutDir=.\.\Debug
# End Custom Macros

ALL : "$(OUTDIR)\Tear.exe"


CLEAN :
	-@erase "$(INTDIR)\tear.obj"
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(INTDIR)\vc60.pdb"
	-@erase "$(OUTDIR)\Tear.exe"
	-@erase "$(OUTDIR)\Tear.ilk"
	-@erase "$(OUTDIR)\Tear.pdb"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP_PROJ=/nologo /MDd /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_CONSOLE" /D "_AFXDLL" /D "_MBCS" /Fp"$(INTDIR)\Tear.pch" /YX /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\Tear.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
LINK32_FLAGS=/nologo /subsystem:console /incremental:yes /pdb:"$(OUTDIR)\Tear.pdb" /debug /machine:I386 /out:"$(OUTDIR)\Tear.exe" 
LINK32_OBJS= \
	"$(INTDIR)\tear.obj"

"$(OUTDIR)\Tear.exe" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ELSEIF  "$(CFG)" == "Tear - Win32 Static Debug"

OUTDIR=.\SDebug
INTDIR=.\SDebug
# Begin Custom Macros
OutDir=.\.\SDebug
# End Custom Macros

ALL : "$(OUTDIR)\Tear.exe"


CLEAN :
	-@erase "$(INTDIR)\tear.obj"
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(INTDIR)\vc60.pdb"
	-@erase "$(OUTDIR)\Tear.exe"
	-@erase "$(OUTDIR)\Tear.ilk"
	-@erase "$(OUTDIR)\Tear.pdb"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP_PROJ=/nologo /MTd /W4 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_CONSOLE" /D "_MBCS" /Fp"$(INTDIR)\Tear.pch" /YX /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\Tear.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
LINK32_FLAGS=/nologo /subsystem:console /incremental:yes /pdb:"$(OUTDIR)\Tear.pdb" /debug /machine:I386 /out:"$(OUTDIR)\Tear.exe" 
LINK32_OBJS= \
	"$(INTDIR)\tear.obj"

"$(OUTDIR)\Tear.exe" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ELSEIF  "$(CFG)" == "Tear - Win32 Static Release"

OUTDIR=.\SRelease
INTDIR=.\SRelease
# Begin Custom Macros
OutDir=.\.\SRelease
# End Custom Macros

ALL : "$(OUTDIR)\Tear.exe"


CLEAN :
	-@erase "$(INTDIR)\tear.obj"
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(OUTDIR)\Tear.exe"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP_PROJ=/nologo /MT /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_CONSOLE" /D "_MBCS" /Fp"$(INTDIR)\Tear.pch" /YX /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\Tear.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
LINK32_FLAGS=/nologo /subsystem:console /incremental:no /pdb:"$(OUTDIR)\Tear.pdb" /machine:I386 /out:"$(OUTDIR)\Tear.exe" 
LINK32_OBJS= \
	"$(INTDIR)\tear.obj"

"$(OUTDIR)\Tear.exe" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
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
!IF EXISTS("Tear.dep")
!INCLUDE "Tear.dep"
!ELSE 
!MESSAGE Warning: cannot find "Tear.dep"
!ENDIF 
!ENDIF 


!IF "$(CFG)" == "Tear - Win32 Release" || "$(CFG)" == "Tear - Win32 Debug" || "$(CFG)" == "Tear - Win32 Static Debug" || "$(CFG)" == "Tear - Win32 Static Release"
SOURCE=.\tear.cpp

"$(INTDIR)\tear.obj" : $(SOURCE) "$(INTDIR)"



!ENDIF 

