# Microsoft Developer Studio Generated NMAKE File, Based on foxisapi.dsp
!IF "$(CFG)" == ""
CFG=foxisapi - Win32 Release
!MESSAGE No configuration specified. Defaulting to foxisapi - Win32 Release.
!ENDIF 

!IF "$(CFG)" != "foxisapi - Win32 Release" && "$(CFG)" !=\
 "foxisapi - Win32 Debug"
!MESSAGE Invalid configuration "$(CFG)" specified.
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "foxisapi.mak" CFG="foxisapi - Win32 Release"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "foxisapi - Win32 Release" (based on\
 "Win32 (x86) Dynamic-Link Library")
!MESSAGE "foxisapi - Win32 Debug" (based on "Win32 (x86) Dynamic-Link Library")
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

!IF  "$(CFG)" == "foxisapi - Win32 Release"

OUTDIR=.
INTDIR=.
# Begin Custom Macros
OutDir=.
# End Custom Macros

!IF "$(RECURSE)" == "0" 

ALL : "$(OUTDIR)\foxisapi.dll"

!ELSE 

ALL : "$(OUTDIR)\foxisapi.dll"

!ENDIF 

CLEAN :
	-@erase "$(INTDIR)\foxisapi.obj"
	-@erase "$(INTDIR)\foxisapi.res"
	-@erase "$(OUTDIR)\foxisapi.dll"
	-@erase "$(OUTDIR)\foxisapi.exp"
	-@erase "$(OUTDIR)\foxisapi.lib"

CPP_PROJ=/nologo /MT /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS"\
 /Fp"$(INTDIR)\foxisapi.pch" /YX /FD /c 
CPP_OBJS=.
CPP_SBRS=.
MTL_PROJ=/nologo /D "NDEBUG" /mktyplib203 /win32 
RSC_PROJ=/l 0x409 /fo"$(INTDIR)\foxisapi.res" /d "NDEBUG" 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\foxisapi.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
LINK32_FLAGS=kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib\
 advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib\
 odbccp32.lib winmm.lib /nologo /subsystem:windows /dll /incremental:no\
 /pdb:"$(OUTDIR)\foxisapi.pdb" /machine:I386 /def:".\foxisapi.def"\
 /out:"$(OUTDIR)\foxisapi.dll" /implib:"$(OUTDIR)\foxisapi.lib" 
DEF_FILE= \
	".\foxisapi.def"
LINK32_OBJS= \
	"$(INTDIR)\foxisapi.obj" \
	"$(INTDIR)\foxisapi.res"

"$(OUTDIR)\foxisapi.dll" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ELSEIF  "$(CFG)" == "foxisapi - Win32 Debug"

OUTDIR=.
INTDIR=.
# Begin Custom Macros
OutDir=.
# End Custom Macros

!IF "$(RECURSE)" == "0" 

ALL : "$(OUTDIR)\foxisapi.dll" "$(OUTDIR)\foxisapi.bsc"

!ELSE 

ALL : "$(OUTDIR)\foxisapi.dll" "$(OUTDIR)\foxisapi.bsc"

!ENDIF 

CLEAN :
	-@erase "$(INTDIR)\foxisapi.obj"
	-@erase "$(INTDIR)\foxisapi.res"
	-@erase "$(INTDIR)\foxisapi.sbr"
	-@erase "$(INTDIR)\vc50.idb"
	-@erase "$(INTDIR)\vc50.pdb"
	-@erase "$(OUTDIR)\foxisapi.bsc"
	-@erase "$(OUTDIR)\foxisapi.dll"
	-@erase "$(OUTDIR)\foxisapi.exp"
	-@erase "$(OUTDIR)\foxisapi.ilk"
	-@erase "$(OUTDIR)\foxisapi.lib"
	-@erase "$(OUTDIR)\foxisapi.pdb"

CPP_PROJ=/nologo /MTd /W3 /Gm /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS"\
 /FR /Fp"$(INTDIR)\foxisapi.pch" /YX /FD /c 
CPP_OBJS=.
CPP_SBRS=.
MTL_PROJ=/nologo /D "_DEBUG" /mktyplib203 /win32 
RSC_PROJ=/l 0x409 /fo"$(INTDIR)\foxisapi.res" /d "_DEBUG" 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\foxisapi.bsc" 
BSC32_SBRS= \
	"$(INTDIR)\foxisapi.sbr"

"$(OUTDIR)\foxisapi.bsc" : "$(OUTDIR)" $(BSC32_SBRS)
    $(BSC32) @<<
  $(BSC32_FLAGS) $(BSC32_SBRS)
<<

LINK32=link.exe
LINK32_FLAGS=kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib\
 advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib\
 odbccp32.lib winmm.lib /nologo /subsystem:windows /dll /incremental:yes\
 /pdb:"$(OUTDIR)\foxisapi.pdb" /debug /machine:I386 /def:".\foxisapi.def"\
 /out:"$(OUTDIR)\foxisapi.dll" /implib:"$(OUTDIR)\foxisapi.lib" 
DEF_FILE= \
	".\foxisapi.def"
LINK32_OBJS= \
	"$(INTDIR)\foxisapi.obj" \
	"$(INTDIR)\foxisapi.res"

"$(OUTDIR)\foxisapi.dll" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
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


!IF "$(CFG)" == "foxisapi - Win32 Release" || "$(CFG)" ==\
 "foxisapi - Win32 Debug"
SOURCE=.\foxisapi.cpp

!IF  "$(CFG)" == "foxisapi - Win32 Release"


"$(INTDIR)\foxisapi.obj" : $(SOURCE) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "foxisapi - Win32 Debug"


"$(INTDIR)\foxisapi.obj"	"$(INTDIR)\foxisapi.sbr" : $(SOURCE) "$(INTDIR)"


!ENDIF 

SOURCE=.\foxisapi.rc

"$(INTDIR)\foxisapi.res" : $(SOURCE) "$(INTDIR)"
	$(RSC) $(RSC_PROJ) $(SOURCE)



!ENDIF 

