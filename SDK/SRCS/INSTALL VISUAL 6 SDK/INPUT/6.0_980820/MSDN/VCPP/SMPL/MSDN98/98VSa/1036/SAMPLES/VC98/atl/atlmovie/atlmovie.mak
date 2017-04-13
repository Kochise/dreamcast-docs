# Microsoft Developer Studio Generated NMAKE File, Based on ATLMovie.dsp
!IF "$(CFG)" == ""
CFG=ATLMovie - Win32 Debug
!MESSAGE No configuration specified. Defaulting to ATLMovie - Win32 Debug.
!ENDIF 

!IF "$(CFG)" != "ATLMovie - Win32 Debug" && "$(CFG)" != "ATLMovie - Win32 Unicode Debug" && "$(CFG)" != "ATLMovie - Win32 Release MinSize" && "$(CFG)" != "ATLMovie - Win32 Release MinDependency" && "$(CFG)" != "ATLMovie - Win32 Unicode Release MinSize" && "$(CFG)" != "ATLMovie - Win32 Unicode Release MinDependency"
!MESSAGE Invalid configuration "$(CFG)" specified.
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "ATLMovie.mak" CFG="ATLMovie - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "ATLMovie - Win32 Debug" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE "ATLMovie - Win32 Unicode Debug" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE "ATLMovie - Win32 Release MinSize" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE "ATLMovie - Win32 Release MinDependency" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE "ATLMovie - Win32 Unicode Release MinSize" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE "ATLMovie - Win32 Unicode Release MinDependency" (based on "Win32 (x86) Dynamic-Link Library")
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

!IF  "$(CFG)" == "ATLMovie - Win32 Debug"

OUTDIR=.\Debug
INTDIR=.\Debug
# Begin Custom Macros
OutDir=.\Debug
# End Custom Macros

ALL : "$(OUTDIR)\ATLMovie.dll" ".\Debug\regsvr32.trg"


CLEAN :
	-@erase "$(INTDIR)\ATLMovie.obj"
	-@erase "$(INTDIR)\ATLMovie.pch"
	-@erase "$(INTDIR)\ATLMovie.res"
	-@erase "$(INTDIR)\MovieCtl.obj"
	-@erase "$(INTDIR)\StdAfx.obj"
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(INTDIR)\vc60.pdb"
	-@erase "$(OUTDIR)\ATLMovie.dll"
	-@erase "$(OUTDIR)\ATLMovie.exp"
	-@erase "$(OUTDIR)\ATLMovie.ilk"
	-@erase "$(OUTDIR)\ATLMovie.lib"
	-@erase "$(OUTDIR)\ATLMovie.pdb"
	-@erase ".\ATLMovie.h"
	-@erase ".\ATLMovie.tlb"
	-@erase ".\ATLMovie_i.c"
	-@erase ".\Debug\regsvr32.trg"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP_PROJ=/nologo /MTd /W3 /Gm /Zi /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_USRDLL" /Fp"$(INTDIR)\ATLMovie.pch" /Yu"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 
MTL_PROJ=/nologo /D "_DEBUG" /mktyplib203 /o "NUL" /win32 
RSC_PROJ=/l 0x409 /fo"$(INTDIR)\ATLMovie.res" /d "_DEBUG" 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\ATLMovie.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
LINK32_FLAGS=kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /dll /incremental:yes /pdb:"$(OUTDIR)\ATLMovie.pdb" /debug /machine:I386 /nodefaultlib:"msvcrt.lib" /def:".\ATLMovie.def" /out:"$(OUTDIR)\ATLMovie.dll" /implib:"$(OUTDIR)\ATLMovie.lib" /pdbtype:sept 
DEF_FILE= \
	".\ATLMovie.def"
LINK32_OBJS= \
	"$(INTDIR)\ATLMovie.obj" \
	"$(INTDIR)\MovieCtl.obj" \
	"$(INTDIR)\StdAfx.obj" \
	"$(INTDIR)\ATLMovie.res"

"$(OUTDIR)\ATLMovie.dll" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

OutDir=.\Debug
TargetPath=.\Debug\ATLMovie.dll
InputPath=.\Debug\ATLMovie.dll
SOURCE=$(InputPath)

"$(OutDir)\regsvr32.trg"	 : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	<<tempfile.bat 
	@echo off 
	regsvr32 /s /c "$(TargetPath)" 
	echo regsvr32 exec. time > "$(OutDir)\regsvr32.trg" 
<< 
	

!ELSEIF  "$(CFG)" == "ATLMovie - Win32 Unicode Debug"

OUTDIR=.\DebugU
INTDIR=.\DebugU
# Begin Custom Macros
OutDir=.\DebugU
# End Custom Macros

ALL : "$(OUTDIR)\ATLMovie.dll" ".\ATLMovie_i.c" ".\ATLMovie.h" ".\DebugU\regsvr32.trg"


CLEAN :
	-@erase "$(INTDIR)\ATLMovie.obj"
	-@erase "$(INTDIR)\ATLMovie.pch"
	-@erase "$(INTDIR)\ATLMovie.res"
	-@erase "$(INTDIR)\MovieCtl.obj"
	-@erase "$(INTDIR)\StdAfx.obj"
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(INTDIR)\vc60.pdb"
	-@erase "$(OUTDIR)\ATLMovie.dll"
	-@erase "$(OUTDIR)\ATLMovie.exp"
	-@erase "$(OUTDIR)\ATLMovie.ilk"
	-@erase "$(OUTDIR)\ATLMovie.lib"
	-@erase "$(OUTDIR)\ATLMovie.pdb"
	-@erase ".\ATLMovie.h"
	-@erase ".\ATLMovie.tlb"
	-@erase ".\ATLMovie_i.c"
	-@erase ".\DebugU\regsvr32.trg"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP_PROJ=/nologo /MTd /W3 /Gm /Zi /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_USRDLL" /D "_UNICODE" /Fp"$(INTDIR)\ATLMovie.pch" /Yu"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 
MTL_PROJ=/nologo /D "_DEBUG" /mktyplib203 /o "NUL" /win32 
RSC_PROJ=/l 0x409 /fo"$(INTDIR)\ATLMovie.res" /d "_DEBUG" 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\ATLMovie.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
LINK32_FLAGS=kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /dll /incremental:yes /pdb:"$(OUTDIR)\ATLMovie.pdb" /debug /machine:I386 /nodefaultlib:"msvcrt.lib" /def:".\ATLMovie.def" /out:"$(OUTDIR)\ATLMovie.dll" /implib:"$(OUTDIR)\ATLMovie.lib" /pdbtype:sept 
DEF_FILE= \
	".\ATLMovie.def"
LINK32_OBJS= \
	"$(INTDIR)\ATLMovie.obj" \
	"$(INTDIR)\MovieCtl.obj" \
	"$(INTDIR)\StdAfx.obj" \
	"$(INTDIR)\ATLMovie.res"

"$(OUTDIR)\ATLMovie.dll" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

OutDir=.\DebugU
TargetPath=.\DebugU\ATLMovie.dll
InputPath=.\DebugU\ATLMovie.dll
SOURCE=$(InputPath)

"$(OutDir)\regsvr32.trg"	 : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	<<tempfile.bat 
	@echo off 
	regsvr32 /s /c "$(TargetPath)" 
	echo regsvr32 exec. time > "$(OutDir)\regsvr32.trg" 
<< 
	

!ELSEIF  "$(CFG)" == "ATLMovie - Win32 Release MinSize"

OUTDIR=.\ReleaseMinSize
INTDIR=.\ReleaseMinSize
# Begin Custom Macros
OutDir=.\ReleaseMinSize
# End Custom Macros

ALL : "$(OUTDIR)\ATLMovie.dll" ".\ATLMovie_i.c" ".\ATLMovie.h" ".\ReleaseMinSize\regsvr32.trg"


CLEAN :
	-@erase "$(INTDIR)\ATLMovie.obj"
	-@erase "$(INTDIR)\ATLMovie.pch"
	-@erase "$(INTDIR)\ATLMovie.res"
	-@erase "$(INTDIR)\MovieCtl.obj"
	-@erase "$(INTDIR)\StdAfx.obj"
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(OUTDIR)\ATLMovie.dll"
	-@erase "$(OUTDIR)\ATLMovie.exp"
	-@erase "$(OUTDIR)\ATLMovie.lib"
	-@erase ".\ATLMovie.h"
	-@erase ".\ATLMovie.tlb"
	-@erase ".\ATLMovie_i.c"
	-@erase ".\ReleaseMinSize\regsvr32.trg"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP_PROJ=/nologo /MT /W3 /O1 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_USRDLL" /D "_ATL_DLL" /D "_ATL_MIN_CRT" /Fp"$(INTDIR)\ATLMovie.pch" /Yu"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 
MTL_PROJ=/nologo /D "NDEBUG" /mktyplib203 /o "NUL" /win32 
RSC_PROJ=/l 0x409 /fo"$(INTDIR)\ATLMovie.res" /d "NDEBUG" 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\ATLMovie.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
LINK32_FLAGS=kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /dll /incremental:no /pdb:"$(OUTDIR)\ATLMovie.pdb" /machine:I386 /nodefaultlib:"msvcrt.lib" /def:".\ATLMovie.def" /out:"$(OUTDIR)\ATLMovie.dll" /implib:"$(OUTDIR)\ATLMovie.lib" 
DEF_FILE= \
	".\ATLMovie.def"
LINK32_OBJS= \
	"$(INTDIR)\ATLMovie.obj" \
	"$(INTDIR)\MovieCtl.obj" \
	"$(INTDIR)\StdAfx.obj" \
	"$(INTDIR)\ATLMovie.res"

"$(OUTDIR)\ATLMovie.dll" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

OutDir=.\ReleaseMinSize
TargetPath=.\ReleaseMinSize\ATLMovie.dll
InputPath=.\ReleaseMinSize\ATLMovie.dll
SOURCE=$(InputPath)

"$(OutDir)\regsvr32.trg"	 : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	<<tempfile.bat 
	@echo off 
	regsvr32 /s /c "$(TargetPath)" 
	echo regsvr32 exec. time > "$(OutDir)\regsvr32.trg" 
<< 
	

!ELSEIF  "$(CFG)" == "ATLMovie - Win32 Release MinDependency"

OUTDIR=.\ReleaseMinDependency
INTDIR=.\ReleaseMinDependency
# Begin Custom Macros
OutDir=.\ReleaseMinDependency
# End Custom Macros

ALL : "$(OUTDIR)\ATLMovie.dll" ".\ATLMovie_i.c" ".\ATLMovie.h" ".\ReleaseMinDependency\regsvr32.trg"


CLEAN :
	-@erase "$(INTDIR)\ATLMovie.obj"
	-@erase "$(INTDIR)\ATLMovie.pch"
	-@erase "$(INTDIR)\ATLMovie.res"
	-@erase "$(INTDIR)\MovieCtl.obj"
	-@erase "$(INTDIR)\StdAfx.obj"
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(OUTDIR)\ATLMovie.dll"
	-@erase "$(OUTDIR)\ATLMovie.exp"
	-@erase "$(OUTDIR)\ATLMovie.lib"
	-@erase ".\ATLMovie.h"
	-@erase ".\ATLMovie.tlb"
	-@erase ".\ATLMovie_i.c"
	-@erase ".\ReleaseMinDependency\regsvr32.trg"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP_PROJ=/nologo /MT /W3 /O1 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_USRDLL" /D "_ATL_STATIC_REGISTRY" /D "_ATL_MIN_CRT" /Fp"$(INTDIR)\ATLMovie.pch" /Yu"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 
MTL_PROJ=/nologo /D "NDEBUG" /mktyplib203 /o "NUL" /win32 
RSC_PROJ=/l 0x409 /fo"$(INTDIR)\ATLMovie.res" /d "NDEBUG" 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\ATLMovie.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
LINK32_FLAGS=kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /dll /incremental:no /pdb:"$(OUTDIR)\ATLMovie.pdb" /machine:I386 /nodefaultlib:"msvcrt.lib" /def:".\ATLMovie.def" /out:"$(OUTDIR)\ATLMovie.dll" /implib:"$(OUTDIR)\ATLMovie.lib" 
DEF_FILE= \
	".\ATLMovie.def"
LINK32_OBJS= \
	"$(INTDIR)\ATLMovie.obj" \
	"$(INTDIR)\MovieCtl.obj" \
	"$(INTDIR)\StdAfx.obj" \
	"$(INTDIR)\ATLMovie.res"

"$(OUTDIR)\ATLMovie.dll" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

OutDir=.\ReleaseMinDependency
TargetPath=.\ReleaseMinDependency\ATLMovie.dll
InputPath=.\ReleaseMinDependency\ATLMovie.dll
SOURCE=$(InputPath)

"$(OutDir)\regsvr32.trg"	 : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	<<tempfile.bat 
	@echo off 
	regsvr32 /s /c "$(TargetPath)" 
	echo regsvr32 exec. time > "$(OutDir)\regsvr32.trg" 
<< 
	

!ELSEIF  "$(CFG)" == "ATLMovie - Win32 Unicode Release MinSize"

OUTDIR=.\ReleaseUMinSize
INTDIR=.\ReleaseUMinSize
# Begin Custom Macros
OutDir=.\ReleaseUMinSize
# End Custom Macros

ALL : "$(OUTDIR)\ATLMovie.dll" ".\ATLMovie_i.c" ".\ATLMovie.h" ".\ReleaseUMinSize\regsvr32.trg"


CLEAN :
	-@erase "$(INTDIR)\ATLMovie.obj"
	-@erase "$(INTDIR)\ATLMovie.pch"
	-@erase "$(INTDIR)\ATLMovie.res"
	-@erase "$(INTDIR)\MovieCtl.obj"
	-@erase "$(INTDIR)\StdAfx.obj"
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(OUTDIR)\ATLMovie.dll"
	-@erase "$(OUTDIR)\ATLMovie.exp"
	-@erase "$(OUTDIR)\ATLMovie.lib"
	-@erase ".\ATLMovie.h"
	-@erase ".\ATLMovie.tlb"
	-@erase ".\ATLMovie_i.c"
	-@erase ".\ReleaseUMinSize\regsvr32.trg"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP_PROJ=/nologo /MT /W3 /O1 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_USRDLL" /D "_UNICODE" /D "_ATL_DLL" /D "_ATL_MIN_CRT" /Fp"$(INTDIR)\ATLMovie.pch" /Yu"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 
MTL_PROJ=/nologo /D "NDEBUG" /mktyplib203 /o "NUL" /win32 
RSC_PROJ=/l 0x409 /fo"$(INTDIR)\ATLMovie.res" /d "NDEBUG" 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\ATLMovie.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
LINK32_FLAGS=kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /dll /incremental:no /pdb:"$(OUTDIR)\ATLMovie.pdb" /machine:I386 /nodefaultlib:"msvcrt.lib" /def:".\ATLMovie.def" /out:"$(OUTDIR)\ATLMovie.dll" /implib:"$(OUTDIR)\ATLMovie.lib" 
DEF_FILE= \
	".\ATLMovie.def"
LINK32_OBJS= \
	"$(INTDIR)\ATLMovie.obj" \
	"$(INTDIR)\MovieCtl.obj" \
	"$(INTDIR)\StdAfx.obj" \
	"$(INTDIR)\ATLMovie.res"

"$(OUTDIR)\ATLMovie.dll" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

OutDir=.\ReleaseUMinSize
TargetPath=.\ReleaseUMinSize\ATLMovie.dll
InputPath=.\ReleaseUMinSize\ATLMovie.dll
SOURCE=$(InputPath)

"$(OutDir)\regsvr32.trg"	 : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	<<tempfile.bat 
	@echo off 
	regsvr32 /s /c "$(TargetPath)" 
	echo regsvr32 exec. time > "$(OutDir)\regsvr32.trg" 
<< 
	

!ELSEIF  "$(CFG)" == "ATLMovie - Win32 Unicode Release MinDependency"

OUTDIR=.\ReleaseUMinDependency
INTDIR=.\ReleaseUMinDependency
# Begin Custom Macros
OutDir=.\ReleaseUMinDependency
# End Custom Macros

ALL : "$(OUTDIR)\ATLMovie.dll" ".\ATLMovie_i.c" ".\ATLMovie.h" ".\ReleaseUMinDependency\regsvr32.trg"


CLEAN :
	-@erase "$(INTDIR)\ATLMovie.obj"
	-@erase "$(INTDIR)\ATLMovie.pch"
	-@erase "$(INTDIR)\ATLMovie.res"
	-@erase "$(INTDIR)\MovieCtl.obj"
	-@erase "$(INTDIR)\StdAfx.obj"
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(OUTDIR)\ATLMovie.dll"
	-@erase "$(OUTDIR)\ATLMovie.exp"
	-@erase "$(OUTDIR)\ATLMovie.lib"
	-@erase ".\ATLMovie.h"
	-@erase ".\ATLMovie.tlb"
	-@erase ".\ATLMovie_i.c"
	-@erase ".\ReleaseUMinDependency\regsvr32.trg"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP_PROJ=/nologo /MT /W3 /O1 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_USRDLL" /D "_UNICODE" /D "_ATL_STATIC_REGISTRY" /D "_ATL_MIN_CRT" /Fp"$(INTDIR)\ATLMovie.pch" /Yu"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 
MTL_PROJ=/nologo /D "NDEBUG" /mktyplib203 /o "NUL" /win32 
RSC_PROJ=/l 0x409 /fo"$(INTDIR)\ATLMovie.res" /d "NDEBUG" 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\ATLMovie.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
LINK32_FLAGS=kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /dll /incremental:no /pdb:"$(OUTDIR)\ATLMovie.pdb" /machine:I386 /nodefaultlib:"msvcrt.lib" /def:".\ATLMovie.def" /out:"$(OUTDIR)\ATLMovie.dll" /implib:"$(OUTDIR)\ATLMovie.lib" 
DEF_FILE= \
	".\ATLMovie.def"
LINK32_OBJS= \
	"$(INTDIR)\ATLMovie.obj" \
	"$(INTDIR)\MovieCtl.obj" \
	"$(INTDIR)\StdAfx.obj" \
	"$(INTDIR)\ATLMovie.res"

"$(OUTDIR)\ATLMovie.dll" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

OutDir=.\ReleaseUMinDependency
TargetPath=.\ReleaseUMinDependency\ATLMovie.dll
InputPath=.\ReleaseUMinDependency\ATLMovie.dll
SOURCE=$(InputPath)

"$(OutDir)\regsvr32.trg"	 : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	<<tempfile.bat 
	@echo off 
	regsvr32 /s /c "$(TargetPath)" 
	echo regsvr32 exec. time > "$(OutDir)\regsvr32.trg" 
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
!IF EXISTS("ATLMovie.dep")
!INCLUDE "ATLMovie.dep"
!ELSE 
!MESSAGE Warning: cannot find "ATLMovie.dep"
!ENDIF 
!ENDIF 


!IF "$(CFG)" == "ATLMovie - Win32 Debug" || "$(CFG)" == "ATLMovie - Win32 Unicode Debug" || "$(CFG)" == "ATLMovie - Win32 Release MinSize" || "$(CFG)" == "ATLMovie - Win32 Release MinDependency" || "$(CFG)" == "ATLMovie - Win32 Unicode Release MinSize" || "$(CFG)" == "ATLMovie - Win32 Unicode Release MinDependency"
SOURCE=.\ATLMovie.cpp

"$(INTDIR)\ATLMovie.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\ATLMovie.pch" ".\ATLMovie.h" ".\ATLMovie_i.c"


SOURCE=.\ATLMovie.idl

!IF  "$(CFG)" == "ATLMovie - Win32 Debug"

MTL_SWITCHES=/nologo /D "_DEBUG" /tlb "./ATLMovie.tlb" /h "ATLMovie.h" /iid "ATLMovie_i.c" /o "NUL" /win32 

".\ATLMovie.tlb"	".\ATLMovie.h"	".\ATLMovie_i.c" : $(SOURCE) "$(INTDIR)"
	$(MTL) @<<
  $(MTL_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "ATLMovie - Win32 Unicode Debug"

MTL_SWITCHES=/nologo /D "_DEBUG" /tlb "./ATLMovie.tlb" /h "ATLMovie.h" /iid "ATLMovie_i.c" /o "NUL" /win32 

".\ATLMovie.tlb"	".\ATLMovie.h"	".\ATLMovie_i.c" : $(SOURCE) "$(INTDIR)"
	$(MTL) @<<
  $(MTL_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "ATLMovie - Win32 Release MinSize"

MTL_SWITCHES=/nologo /D "NDEBUG" /tlb "./ATLMovie.tlb" /h "ATLMovie.h" /iid "ATLMovie_i.c" /o "NUL" /win32 

".\ATLMovie.tlb"	".\ATLMovie.h"	".\ATLMovie_i.c" : $(SOURCE) "$(INTDIR)"
	$(MTL) @<<
  $(MTL_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "ATLMovie - Win32 Release MinDependency"

MTL_SWITCHES=/nologo /D "NDEBUG" /tlb "./ATLMovie.tlb" /h "ATLMovie.h" /iid "ATLMovie_i.c" /o "NUL" /win32 

".\ATLMovie.tlb"	".\ATLMovie.h"	".\ATLMovie_i.c" : $(SOURCE) "$(INTDIR)"
	$(MTL) @<<
  $(MTL_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "ATLMovie - Win32 Unicode Release MinSize"

MTL_SWITCHES=/nologo /D "NDEBUG" /tlb "./ATLMovie.tlb" /h "ATLMovie.h" /iid "ATLMovie_i.c" /o "NUL" /win32 

".\ATLMovie.tlb"	".\ATLMovie.h"	".\ATLMovie_i.c" : $(SOURCE) "$(INTDIR)"
	$(MTL) @<<
  $(MTL_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "ATLMovie - Win32 Unicode Release MinDependency"

MTL_SWITCHES=/nologo /D "NDEBUG" /tlb "./ATLMovie.tlb" /h "ATLMovie.h" /iid "ATLMovie_i.c" /o "NUL" /win32 

".\ATLMovie.tlb"	".\ATLMovie.h"	".\ATLMovie_i.c" : $(SOURCE) "$(INTDIR)"
	$(MTL) @<<
  $(MTL_SWITCHES) $(SOURCE)
<<


!ENDIF 

SOURCE=.\ATLMovie.rc

"$(INTDIR)\ATLMovie.res" : $(SOURCE) "$(INTDIR)" ".\ATLMovie.tlb"
	$(RSC) $(RSC_PROJ) $(SOURCE)


SOURCE=.\MovieCtl.cpp

"$(INTDIR)\MovieCtl.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\ATLMovie.pch" ".\ATLMovie.h"


SOURCE=.\StdAfx.cpp

!IF  "$(CFG)" == "ATLMovie - Win32 Debug"

CPP_SWITCHES=/nologo /MTd /W3 /Gm /Zi /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_USRDLL" /Fp"$(INTDIR)\ATLMovie.pch" /Yc"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 

"$(INTDIR)\StdAfx.obj"	"$(INTDIR)\ATLMovie.pch" : $(SOURCE) "$(INTDIR)"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "ATLMovie - Win32 Unicode Debug"

CPP_SWITCHES=/nologo /MTd /W3 /Gm /Zi /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_USRDLL" /D "_UNICODE" /Fp"$(INTDIR)\ATLMovie.pch" /Yc"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 

"$(INTDIR)\StdAfx.obj"	"$(INTDIR)\ATLMovie.pch" : $(SOURCE) "$(INTDIR)"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "ATLMovie - Win32 Release MinSize"

CPP_SWITCHES=/nologo /MT /W3 /O1 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_USRDLL" /D "_ATL_DLL" /D "_ATL_MIN_CRT" /Fp"$(INTDIR)\ATLMovie.pch" /Yc"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 

"$(INTDIR)\StdAfx.obj"	"$(INTDIR)\ATLMovie.pch" : $(SOURCE) "$(INTDIR)"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "ATLMovie - Win32 Release MinDependency"

CPP_SWITCHES=/nologo /MT /W3 /O1 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_USRDLL" /D "_ATL_STATIC_REGISTRY" /D "_ATL_MIN_CRT" /Fp"$(INTDIR)\ATLMovie.pch" /Yc"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 

"$(INTDIR)\StdAfx.obj"	"$(INTDIR)\ATLMovie.pch" : $(SOURCE) "$(INTDIR)"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "ATLMovie - Win32 Unicode Release MinSize"

CPP_SWITCHES=/nologo /MT /W3 /O1 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_USRDLL" /D "_UNICODE" /D "_ATL_DLL" /D "_ATL_MIN_CRT" /Fp"$(INTDIR)\ATLMovie.pch" /Yc"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 

"$(INTDIR)\StdAfx.obj"	"$(INTDIR)\ATLMovie.pch" : $(SOURCE) "$(INTDIR)"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "ATLMovie - Win32 Unicode Release MinDependency"

CPP_SWITCHES=/nologo /MT /W3 /O1 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_USRDLL" /D "_UNICODE" /D "_ATL_STATIC_REGISTRY" /D "_ATL_MIN_CRT" /Fp"$(INTDIR)\ATLMovie.pch" /Yc"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 

"$(INTDIR)\StdAfx.obj"	"$(INTDIR)\ATLMovie.pch" : $(SOURCE) "$(INTDIR)"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ENDIF 


!ENDIF 

