# Microsoft Developer Studio Generated NMAKE File, Based on Counter.dsp
!IF "$(CFG)" == ""
CFG=counter - Win32 Release
!MESSAGE No configuration specified. Defaulting to counter - Win32 Release.
!ENDIF 

!IF "$(CFG)" != "counter - Win32 Release" && "$(CFG)" != "counter - Win32 Debug"
!MESSAGE Invalid configuration "$(CFG)" specified.
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "Counter.mak" CFG="counter - Win32 Release"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "counter - Win32 Release" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE "counter - Win32 Debug" (based on "Win32 (x86) Dynamic-Link Library")
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

!IF  "$(CFG)" == "counter - Win32 Release"

OUTDIR=.\Release
INTDIR=.\Release
# Begin Custom Macros
OutDir=.\.\Release
# End Custom Macros

ALL : "$(OUTDIR)\Counter.dll" "$(OUTDIR)\Counter.bsc"


CLEAN :
	-@erase "$(INTDIR)\Counter.obj"
	-@erase "$(INTDIR)\Counter.res"
	-@erase "$(INTDIR)\Counter.sbr"
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(OUTDIR)\Counter.bsc"
	-@erase "$(OUTDIR)\Counter.dll"
	-@erase "$(OUTDIR)\Counter.exp"
	-@erase "$(OUTDIR)\Counter.lib"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP_PROJ=/nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_USRDLL" /D "_WINDLL" /D "_AFXDLL" /D "_MBCS" /FR"$(INTDIR)\\" /Fp"$(INTDIR)\Counter.pch" /YX /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 
MTL_PROJ=/nologo /D "NDEBUG" /mktyplib203 /win32 
RSC_PROJ=/l 0x409 /fo"$(INTDIR)\Counter.res" /d "NDEBUG" /d "_AFXDLL" 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\Counter.bsc" 
BSC32_SBRS= \
	"$(INTDIR)\Counter.sbr"

"$(OUTDIR)\Counter.bsc" : "$(OUTDIR)" $(BSC32_SBRS)
    $(BSC32) @<<
  $(BSC32_FLAGS) $(BSC32_SBRS)
<<

LINK32=link.exe
LINK32_FLAGS=/nologo /subsystem:windows /dll /incremental:no /pdb:"$(OUTDIR)\Counter.pdb" /machine:I386 /def:".\Counter.def" /out:"$(OUTDIR)\Counter.dll" /implib:"$(OUTDIR)\Counter.lib" 
DEF_FILE= \
	".\Counter.def"
LINK32_OBJS= \
	"$(INTDIR)\Counter.obj" \
	"$(INTDIR)\Counter.res"

"$(OUTDIR)\Counter.dll" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ELSEIF  "$(CFG)" == "counter - Win32 Debug"

OUTDIR=.\Debug
INTDIR=.\Debug
# Begin Custom Macros
OutDir=.\.\Debug
# End Custom Macros

ALL : "$(OUTDIR)\Counter.dll" "$(OUTDIR)\Counter.bsc"


CLEAN :
	-@erase "$(INTDIR)\Counter.obj"
	-@erase "$(INTDIR)\Counter.res"
	-@erase "$(INTDIR)\Counter.sbr"
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(INTDIR)\vc60.pdb"
	-@erase "$(OUTDIR)\Counter.bsc"
	-@erase "$(OUTDIR)\Counter.dll"
	-@erase "$(OUTDIR)\Counter.exp"
	-@erase "$(OUTDIR)\Counter.ilk"
	-@erase "$(OUTDIR)\Counter.lib"
	-@erase "$(OUTDIR)\Counter.pdb"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP_PROJ=/nologo /MDd /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_USRDLL" /D "_WINDLL" /D "_AFXDLL" /D "_MBCS" /FR"$(INTDIR)\\" /Fp"$(INTDIR)\Counter.pch" /YX /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 
MTL_PROJ=/nologo /D "_DEBUG" /mktyplib203 /win32 
RSC_PROJ=/l 0x409 /fo"$(INTDIR)\Counter.res" /d "_DEBUG" /d "_AFXDLL" 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\Counter.bsc" 
BSC32_SBRS= \
	"$(INTDIR)\Counter.sbr"

"$(OUTDIR)\Counter.bsc" : "$(OUTDIR)" $(BSC32_SBRS)
    $(BSC32) @<<
  $(BSC32_FLAGS) $(BSC32_SBRS)
<<

LINK32=link.exe
LINK32_FLAGS=/nologo /subsystem:windows /dll /incremental:yes /pdb:"$(OUTDIR)\Counter.pdb" /debug /machine:I386 /def:".\Counter.def" /out:"$(OUTDIR)\Counter.dll" /implib:"$(OUTDIR)\Counter.lib" 
DEF_FILE= \
	".\Counter.def"
LINK32_OBJS= \
	"$(INTDIR)\Counter.obj" \
	"$(INTDIR)\Counter.res"

"$(OUTDIR)\Counter.dll" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
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
!IF EXISTS("Counter.dep")
!INCLUDE "Counter.dep"
!ELSE 
!MESSAGE Warning: cannot find "Counter.dep"
!ENDIF 
!ENDIF 


!IF "$(CFG)" == "counter - Win32 Release" || "$(CFG)" == "counter - Win32 Debug"
SOURCE=.\Counter.cpp

"$(INTDIR)\Counter.obj"	"$(INTDIR)\Counter.sbr" : $(SOURCE) "$(INTDIR)"


SOURCE=.\Counter.rc

"$(INTDIR)\Counter.res" : $(SOURCE) "$(INTDIR)"
	$(RSC) $(RSC_PROJ) $(SOURCE)



!ENDIF 

