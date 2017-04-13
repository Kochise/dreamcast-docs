# Microsoft Developer Studio Generated NMAKE File, Based on Trace.dsp
!IF "$(CFG)" == ""
CFG=Trace - Win32 Release
!MESSAGE No configuration specified. Defaulting to Trace - Win32 Release.
!ENDIF 

!IF "$(CFG)" != "Trace - Win32 Release" && "$(CFG)" != "Trace - Win32 Debug"
!MESSAGE Invalid configuration "$(CFG)" specified.
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "Trace.mak" CFG="Trace - Win32 Release"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "Trace - Win32 Release" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE "Trace - Win32 Debug" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE 
!ERROR An invalid configuration is specified.
!ENDIF 

!IF "$(OS)" == "Windows_NT"
NULL=
!ELSE 
NULL=nul
!ENDIF 

!IF  "$(CFG)" == "Trace - Win32 Release"

OUTDIR=.\Release
INTDIR=.\Release
# Begin Custom Macros
OutDir=.\.\Release
# End Custom Macros

ALL : "$(OUTDIR)\Trace.dll"


CLEAN :
	-@erase "$(INTDIR)\trace.obj"
	-@erase "$(INTDIR)\trace.res"
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(OUTDIR)\Trace.dll"
	-@erase "$(OUTDIR)\Trace.exp"
	-@erase "$(OUTDIR)\Trace.lib"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP=cl.exe
CPP_PROJ=/nologo /MT /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_USRDLL" /D "_WINDLL" /D "_MBCS" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 

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

MTL=midl.exe
MTL_PROJ=/nologo /D "NDEBUG" /mktyplib203 /win32 
RSC=rc.exe
RSC_PROJ=/l 0x409 /fo"$(INTDIR)\trace.res" /d "NDEBUG" 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\Trace.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
LINK32_FLAGS=/nologo /subsystem:windows /dll /incremental:no /pdb:"$(OUTDIR)\Trace.pdb" /machine:I386 /def:".\trace.def" /out:"$(OUTDIR)\Trace.dll" /implib:"$(OUTDIR)\Trace.lib" 
DEF_FILE= \
	".\trace.def"
LINK32_OBJS= \
	"$(INTDIR)\trace.obj" \
	"$(INTDIR)\trace.res"

"$(OUTDIR)\Trace.dll" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ELSEIF  "$(CFG)" == "Trace - Win32 Debug"

OUTDIR=.\Debug
INTDIR=.\Debug
# Begin Custom Macros
OutDir=.\.\Debug
# End Custom Macros

ALL : "$(OUTDIR)\Trace.dll"


CLEAN :
	-@erase "$(INTDIR)\trace.obj"
	-@erase "$(INTDIR)\trace.res"
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(INTDIR)\vc60.pdb"
	-@erase "$(OUTDIR)\Trace.dll"
	-@erase "$(OUTDIR)\Trace.exp"
	-@erase "$(OUTDIR)\Trace.ilk"
	-@erase "$(OUTDIR)\Trace.lib"
	-@erase "$(OUTDIR)\Trace.pdb"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP=cl.exe
CPP_PROJ=/nologo /MTd /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_USRDLL" /D "_WINDLL" /D "_MBCS" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 

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

MTL=midl.exe
MTL_PROJ=/nologo /D "_DEBUG" /mktyplib203 /win32 
RSC=rc.exe
RSC_PROJ=/l 0x409 /fo"$(INTDIR)\trace.res" /d "_DEBUG" 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\Trace.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
LINK32_FLAGS=/nologo /subsystem:windows /dll /incremental:yes /pdb:"$(OUTDIR)\Trace.pdb" /debug /machine:I386 /def:".\trace.def" /out:"$(OUTDIR)\Trace.dll" /implib:"$(OUTDIR)\Trace.lib" 
DEF_FILE= \
	".\trace.def"
LINK32_OBJS= \
	"$(INTDIR)\trace.obj" \
	"$(INTDIR)\trace.res"

"$(OUTDIR)\Trace.dll" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ENDIF 


!IF "$(NO_EXTERNAL_DEPS)" != "1"
!IF EXISTS("Trace.dep")
!INCLUDE "Trace.dep"
!ELSE 
!MESSAGE Warning: cannot find "Trace.dep"
!ENDIF 
!ENDIF 


!IF "$(CFG)" == "Trace - Win32 Release" || "$(CFG)" == "Trace - Win32 Debug"
SOURCE=.\trace.cpp

"$(INTDIR)\trace.obj" : $(SOURCE) "$(INTDIR)"


SOURCE=.\trace.rc

"$(INTDIR)\trace.res" : $(SOURCE) "$(INTDIR)"
	$(RSC) $(RSC_PROJ) $(SOURCE)



!ENDIF 

