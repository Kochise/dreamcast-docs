# Microsoft Developer Studio Generated NMAKE File, Based on mfcucase.dsp
!IF "$(CFG)" == ""
CFG=MFCUCASE - Win32 Release
!MESSAGE No configuration specified. Defaulting to MFCUCASE - Win32 Release.
!ENDIF 

!IF "$(CFG)" != "MFCUCASE - Win32 Release" && "$(CFG)" != "MFCUCASE - Win32 Debug" && "$(CFG)" != "MFCUCASE - Win32 AFXDLL Debug" && "$(CFG)" != "MFCUCASE - Win32 AFXDLL Release"
!MESSAGE Invalid configuration "$(CFG)" specified.
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "mfcucase.mak" CFG="MFCUCASE - Win32 Release"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "MFCUCASE - Win32 Release" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE "MFCUCASE - Win32 Debug" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE "MFCUCASE - Win32 AFXDLL Debug" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE "MFCUCASE - Win32 AFXDLL Release" (based on "Win32 (x86) Dynamic-Link Library")
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

!IF  "$(CFG)" == "MFCUCASE - Win32 Release"

OUTDIR=.\Release
INTDIR=.\Release
# Begin Custom Macros
OutDir=.\.\Release
# End Custom Macros

ALL : "$(OUTDIR)\mfcucase.dll"


CLEAN :
	-@erase "$(INTDIR)\Mfcucase.obj"
	-@erase "$(INTDIR)\Mfcucase.res"
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(OUTDIR)\mfcucase.dll"
	-@erase "$(OUTDIR)\mfcucase.exp"
	-@erase "$(OUTDIR)\mfcucase.lib"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP_PROJ=/nologo /MT /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /Fp"$(INTDIR)\mfcucase.pch" /YX /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 
MTL_PROJ=/nologo /D "NDEBUG" /mktyplib203 /win32 
RSC_PROJ=/l 0x409 /fo"$(INTDIR)\Mfcucase.res" /d "NDEBUG" 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\mfcucase.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
LINK32_FLAGS=kernel32.lib user32.lib gdi32.lib advapi32.lib uuid.lib /nologo /subsystem:windows /dll /incremental:no /pdb:"$(OUTDIR)\mfcucase.pdb" /machine:I386 /def:".\Mfcucase.def" /out:"$(OUTDIR)\mfcucase.dll" /implib:"$(OUTDIR)\mfcucase.lib" 
DEF_FILE= \
	".\Mfcucase.def"
LINK32_OBJS= \
	"$(INTDIR)\Mfcucase.obj" \
	"$(INTDIR)\Mfcucase.res"

"$(OUTDIR)\mfcucase.dll" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ELSEIF  "$(CFG)" == "MFCUCASE - Win32 Debug"

OUTDIR=.\Debug
INTDIR=.\Debug
# Begin Custom Macros
OutDir=.\.\Debug
# End Custom Macros

ALL : "$(OUTDIR)\mfcucase.dll"


CLEAN :
	-@erase "$(INTDIR)\Mfcucase.obj"
	-@erase "$(INTDIR)\Mfcucase.res"
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(INTDIR)\vc60.pdb"
	-@erase "$(OUTDIR)\mfcucase.dll"
	-@erase "$(OUTDIR)\mfcucase.exp"
	-@erase "$(OUTDIR)\mfcucase.ilk"
	-@erase "$(OUTDIR)\mfcucase.lib"
	-@erase "$(OUTDIR)\mfcucase.pdb"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP_PROJ=/nologo /MTd /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /Fp"$(INTDIR)\mfcucase.pch" /YX /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 
MTL_PROJ=/nologo /D "_DEBUG" /mktyplib203 /win32 
RSC_PROJ=/l 0x409 /fo"$(INTDIR)\Mfcucase.res" /d "_DEBUG" 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\mfcucase.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
LINK32_FLAGS=kernel32.lib user32.lib gdi32.lib advapi32.lib uuid.lib /nologo /subsystem:windows /dll /incremental:yes /pdb:"$(OUTDIR)\mfcucase.pdb" /debug /machine:I386 /def:".\Mfcucase.def" /out:"$(OUTDIR)\mfcucase.dll" /implib:"$(OUTDIR)\mfcucase.lib" 
DEF_FILE= \
	".\Mfcucase.def"
LINK32_OBJS= \
	"$(INTDIR)\Mfcucase.obj" \
	"$(INTDIR)\Mfcucase.res"

"$(OUTDIR)\mfcucase.dll" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ELSEIF  "$(CFG)" == "MFCUCASE - Win32 AFXDLL Debug"

OUTDIR=.\DLLDebug
INTDIR=.\DLLDebug
# Begin Custom Macros
OutDir=.\.\DLLDebug
# End Custom Macros

ALL : "$(OUTDIR)\mfcucase.dll"


CLEAN :
	-@erase "$(INTDIR)\Mfcucase.obj"
	-@erase "$(INTDIR)\Mfcucase.res"
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(INTDIR)\vc60.pdb"
	-@erase "$(OUTDIR)\mfcucase.dll"
	-@erase "$(OUTDIR)\mfcucase.exp"
	-@erase "$(OUTDIR)\mfcucase.ilk"
	-@erase "$(OUTDIR)\mfcucase.lib"
	-@erase "$(OUTDIR)\mfcucase.pdb"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP_PROJ=/nologo /MDd /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_WINDLL" /D "_AFXDLL" /D "_MBCS" /D "_USRDLL" /Fp"$(INTDIR)\mfcucase.pch" /YX /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 
MTL_PROJ=/nologo /D "_DEBUG" /mktyplib203 /win32 
RSC_PROJ=/l 0x409 /fo"$(INTDIR)\Mfcucase.res" /d "_DEBUG" /d "_AFXDLL" 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\mfcucase.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
LINK32_FLAGS=/nologo /subsystem:windows /dll /incremental:yes /pdb:"$(OUTDIR)\mfcucase.pdb" /debug /machine:I386 /def:".\Mfcucase.def" /out:"$(OUTDIR)\mfcucase.dll" /implib:"$(OUTDIR)\mfcucase.lib" 
DEF_FILE= \
	".\Mfcucase.def"
LINK32_OBJS= \
	"$(INTDIR)\Mfcucase.obj" \
	"$(INTDIR)\Mfcucase.res"

"$(OUTDIR)\mfcucase.dll" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ELSEIF  "$(CFG)" == "MFCUCASE - Win32 AFXDLL Release"

OUTDIR=.\DLLRelll
INTDIR=.\DLLRel
# Begin Custom Macros
OutDir=.\.\DLLRelll
# End Custom Macros

ALL : "$(OUTDIR)\mfcucase.dll"


CLEAN :
	-@erase "$(INTDIR)\Mfcucase.obj"
	-@erase "$(INTDIR)\Mfcucase.res"
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(OUTDIR)\mfcucase.dll"
	-@erase "$(OUTDIR)\mfcucase.exp"
	-@erase "$(OUTDIR)\mfcucase.lib"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

"$(INTDIR)" :
    if not exist "$(INTDIR)/$(NULL)" mkdir "$(INTDIR)"

CPP_PROJ=/nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_WINDLL" /D "_AFXDLL" /D "_MBCS" /D "_USRDLL" /Fp"$(INTDIR)\mfcucase.pch" /YX /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 
MTL_PROJ=/nologo /D "NDEBUG" /mktyplib203 /win32 
RSC_PROJ=/l 0x409 /fo"$(INTDIR)\Mfcucase.res" /d "NDEBUG" /d "_AFXDLL" 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\mfcucase.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
LINK32_FLAGS=/nologo /subsystem:windows /dll /incremental:no /pdb:"$(OUTDIR)\mfcucase.pdb" /machine:I386 /def:".\Mfcucase.def" /out:"$(OUTDIR)\mfcucase.dll" /implib:"$(OUTDIR)\mfcucase.lib" 
DEF_FILE= \
	".\Mfcucase.def"
LINK32_OBJS= \
	"$(INTDIR)\Mfcucase.obj" \
	"$(INTDIR)\Mfcucase.res"

"$(OUTDIR)\mfcucase.dll" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
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
!IF EXISTS("mfcucase.dep")
!INCLUDE "mfcucase.dep"
!ELSE 
!MESSAGE Warning: cannot find "mfcucase.dep"
!ENDIF 
!ENDIF 


!IF "$(CFG)" == "MFCUCASE - Win32 Release" || "$(CFG)" == "MFCUCASE - Win32 Debug" || "$(CFG)" == "MFCUCASE - Win32 AFXDLL Debug" || "$(CFG)" == "MFCUCASE - Win32 AFXDLL Release"
SOURCE=.\Mfcucase.cpp

"$(INTDIR)\Mfcucase.obj" : $(SOURCE) "$(INTDIR)"


SOURCE=.\Mfcucase.rc

"$(INTDIR)\Mfcucase.res" : $(SOURCE) "$(INTDIR)"
	$(RSC) $(RSC_PROJ) $(SOURCE)



!ENDIF 

