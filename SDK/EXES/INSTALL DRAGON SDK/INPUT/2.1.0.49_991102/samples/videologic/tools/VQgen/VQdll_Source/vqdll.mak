# Microsoft Developer Studio Generated NMAKE File, Based on vqdll.dsp
!IF "$(CFG)" == ""
CFG=vqdll - Win32 Debug
!MESSAGE No configuration specified. Defaulting to vqdll - Win32 Debug.
!ENDIF 

!IF "$(CFG)" != "vqdll - Win32 Release" && "$(CFG)" != "vqdll - Win32 Debug"
!MESSAGE Invalid configuration "$(CFG)" specified.
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "vqdll.mak" CFG="vqdll - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "vqdll - Win32 Release" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE "vqdll - Win32 Debug" (based on "Win32 (x86) Dynamic-Link Library")
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

!IF  "$(CFG)" == "vqdll - Win32 Release"

OUTDIR=.\Release
INTDIR=.\Release

!IF "$(RECURSE)" == "0" 

ALL : ".\DLL\vqdll.dll"

!ELSE 

ALL : ".\DLL\vqdll.dll"

!ENDIF 

CLEAN :
	-@erase "$(INTDIR)\vc50.idb"
	-@erase "$(INTDIR)\vqcalc.obj"
	-@erase "$(INTDIR)\vqdll.obj"
	-@erase "$(INTDIR)\vqdll.res"
	-@erase "$(OUTDIR)\vqdll.exp"
	-@erase "$(OUTDIR)\vqdll.lib"
	-@erase ".\DLL\vqdll.dll"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP_PROJ=/nologo /MT /W3 /GX /O2 /I "..\include" /D "WIN32" /D "NDEBUG" /D\
 "_WINDOWS" /Fp"$(INTDIR)\vqdll.pch" /YX /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD\
 /c 
CPP_OBJS=.\Release/
CPP_SBRS=.
MTL_PROJ=/nologo /D "NDEBUG" /mktyplib203 /o NUL /win32 
RSC_PROJ=/l 0x809 /fo"$(INTDIR)\vqdll.res" /d "NDEBUG" 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\vqdll.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
LINK32_FLAGS=kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib\
 advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib\
 odbccp32.lib /nologo /subsystem:windows /dll /incremental:no\
 /pdb:"$(OUTDIR)\vqdll.pdb" /machine:I386 /out:"Dll/vqdll.dll"\
 /implib:"$(OUTDIR)\vqdll.lib" 
LINK32_OBJS= \
	"$(INTDIR)\vqcalc.obj" \
	"$(INTDIR)\vqdll.obj" \
	"$(INTDIR)\vqdll.res"

".\DLL\vqdll.dll" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

SOURCE=$(InputPath)
DS_POSTBUILD_DEP=$(INTDIR)\postbld.dep

ALL : $(DS_POSTBUILD_DEP)

$(DS_POSTBUILD_DEP) : ".\DLL\vqdll.dll"
   if NOT exist ..\lib\nul mkdir ..\lib
	if exist  Release\vqdll.lib                copy Release\vqdll.lib ..\lib
	echo Helper for Post-build step > "$(DS_POSTBUILD_DEP)"

!ELSEIF  "$(CFG)" == "vqdll - Win32 Debug"

OUTDIR=.\Debug
INTDIR=.\Debug
# Begin Custom Macros
OutDir=.\Debug
# End Custom Macros

!IF "$(RECURSE)" == "0" 

ALL : ".\DLL\vqdll.dll" "$(OUTDIR)\vqdll.bsc"

!ELSE 

ALL : ".\DLL\vqdll.dll" "$(OUTDIR)\vqdll.bsc"

!ENDIF 

CLEAN :
	-@erase "$(INTDIR)\vc50.idb"
	-@erase "$(INTDIR)\vc50.pdb"
	-@erase "$(INTDIR)\vqcalc.obj"
	-@erase "$(INTDIR)\vqcalc.sbr"
	-@erase "$(INTDIR)\vqdll.obj"
	-@erase "$(INTDIR)\vqdll.res"
	-@erase "$(INTDIR)\vqdll.sbr"
	-@erase "$(OUTDIR)\vqdll.bsc"
	-@erase "$(OUTDIR)\vqdll.exp"
	-@erase "$(OUTDIR)\vqdll.lib"
	-@erase "$(OUTDIR)\vqdll.pdb"
	-@erase ".\DLL\vqdll.dll"
	-@erase ".\DLL\vqdll.ilk"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP_PROJ=/nologo /MTd /W3 /Gm /GX /Zi /Od /I "..\include" /D "WIN32" /D\
 "_DEBUG" /D "_WINDOWS" /FR"$(INTDIR)\\" /Fp"$(INTDIR)\vqdll.pch" /YX\
 /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 
CPP_OBJS=.\Debug/
CPP_SBRS=.\Debug/
MTL_PROJ=/nologo /D "_DEBUG" /mktyplib203 /o NUL /win32 
RSC_PROJ=/l 0x809 /fo"$(INTDIR)\vqdll.res" /d "_DEBUG" 
BSC32=bscmake.exe
BSC32_FLAGS=/o"$(OUTDIR)\vqdll.bsc" 
BSC32_SBRS= \
	"$(INTDIR)\vqcalc.sbr" \
	"$(INTDIR)\vqdll.sbr"

"$(OUTDIR)\vqdll.bsc" : "$(OUTDIR)" $(BSC32_SBRS)
    $(BSC32) @<<
  $(BSC32_FLAGS) $(BSC32_SBRS)
<<

LINK32=link.exe
LINK32_FLAGS=kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib\
 advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib\
 odbccp32.lib /nologo /subsystem:windows /dll /incremental:yes\
 /pdb:"$(OUTDIR)\vqdll.pdb" /debug /machine:I386 /out:"DLL/vqdll.dll"\
 /implib:"$(OUTDIR)\vqdll.lib" /pdbtype:sept 
LINK32_OBJS= \
	"$(INTDIR)\vqcalc.obj" \
	"$(INTDIR)\vqdll.obj" \
	"$(INTDIR)\vqdll.res"

".\DLL\vqdll.dll" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

SOURCE=$(InputPath)
DS_POSTBUILD_DEP=$(INTDIR)\postbld.dep

ALL : $(DS_POSTBUILD_DEP)

# Begin Custom Macros
OutDir=.\Debug
# End Custom Macros

$(DS_POSTBUILD_DEP) : ".\DLL\vqdll.dll" "$(OUTDIR)\vqdll.bsc"
   if NOT exist ..\libdbg\nul mkdir ..\libdbg
	if exist        debug\vqdll.lib copy debug\vqdll.lib ..\libdbg
	echo Helper for Post-build step > "$(DS_POSTBUILD_DEP)"

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


!IF "$(CFG)" == "vqdll - Win32 Release" || "$(CFG)" == "vqdll - Win32 Debug"
SOURCE=.\vqcalc.c
DEP_CPP_VQCAL=\
	".\vqcalc.h"\
	

!IF  "$(CFG)" == "vqdll - Win32 Release"


"$(INTDIR)\vqcalc.obj" : $(SOURCE) $(DEP_CPP_VQCAL) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "vqdll - Win32 Debug"


"$(INTDIR)\vqcalc.obj"	"$(INTDIR)\vqcalc.sbr" : $(SOURCE) $(DEP_CPP_VQCAL)\
 "$(INTDIR)"


!ENDIF 

SOURCE=.\vqdll.c
DEP_CPP_VQDLL=\
	".\vqcalc.h"\
	".\vqdll.h"\
	

!IF  "$(CFG)" == "vqdll - Win32 Release"


"$(INTDIR)\vqdll.obj" : $(SOURCE) $(DEP_CPP_VQDLL) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "vqdll - Win32 Debug"


"$(INTDIR)\vqdll.obj"	"$(INTDIR)\vqdll.sbr" : $(SOURCE) $(DEP_CPP_VQDLL)\
 "$(INTDIR)"


!ENDIF 

SOURCE=.\vqdll.rc
DEP_RSC_VQDLL_=\
	".\autover.h"\
	".\vqdll.rc2"\
	

"$(INTDIR)\vqdll.res" : $(SOURCE) $(DEP_RSC_VQDLL_) "$(INTDIR)"
	$(RSC) $(RSC_PROJ) $(SOURCE)



!ENDIF 

