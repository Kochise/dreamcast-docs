# Microsoft Developer Studio Generated NMAKE File, Based on beeper.dsp
!IF "$(CFG)" == ""
CFG=beeper - Win32 Release
!MESSAGE No configuration specified. Defaulting to beeper - Win32 Release.
!ENDIF 

!IF "$(CFG)" != "beeper - Win32 Release" && "$(CFG)" != "beeper - Win32 Debug" && "$(CFG)" != "beeper - Win32 Unicode Debug" && "$(CFG)" != "beeper - Win32 Unicode Release" && "$(CFG)" != "beeper - Win32 EXE Release" && "$(CFG)" != "beeper - Win32 EXE Debug" && "$(CFG)" != "beeper - Win32 EXE Unicode Debug" && "$(CFG)" != "beeper - Win32 EXE Unicode Release" && "$(CFG)" != "beeper - Win32 Release MINCRT"
!MESSAGE Invalid configuration "$(CFG)" specified.
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "beeper.mak" CFG="beeper - Win32 Release"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "beeper - Win32 Release" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE "beeper - Win32 Debug" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE "beeper - Win32 Unicode Debug" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE "beeper - Win32 Unicode Release" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE "beeper - Win32 EXE Release" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE "beeper - Win32 EXE Debug" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE "beeper - Win32 EXE Unicode Debug" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE "beeper - Win32 EXE Unicode Release" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE "beeper - Win32 Release MINCRT" (based on "Win32 (x86) Dynamic-Link Library")
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

!IF  "$(CFG)" == "beeper - Win32 Release"

OUTDIR=.\Release
INTDIR=.\Release
# Begin Custom Macros
OutDir=.\.\Release
# End Custom Macros

ALL : "$(OUTDIR)\beeper.dll" ".\beeper_i.c" ".\beeper.h" ".\beeper.tlb" ".\.\Release\regsvr32.trg"


CLEAN :
	-@erase "$(INTDIR)\beeper.obj"
	-@erase "$(INTDIR)\beeper.pch"
	-@erase "$(INTDIR)\beeper.res"
	-@erase "$(INTDIR)\beepobj.obj"
	-@erase "$(INTDIR)\prebeep.obj"
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(OUTDIR)\beeper.dll"
	-@erase "$(OUTDIR)\beeper.exp"
	-@erase "$(OUTDIR)\beeper.lib"
	-@erase "$(OUTDIR)\beeper.map"
	-@erase ".\beeper.h"
	-@erase ".\beeper.tlb"
	-@erase ".\beeper_i.c"
	-@erase ".\.\Release\regsvr32.trg"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP_PROJ=/nologo /MT /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_WINDLL" /D "_MBCS" /Fp"$(INTDIR)\beeper.pch" /Yu"prebeep.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 
MTL_PROJ=/nologo /D "NDEBUG" /mktyplib203 /win32 
RSC_PROJ=/l 0x409 /fo"$(INTDIR)\beeper.res" /d "NDEBUG" 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\beeper.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
LINK32_FLAGS=/nologo /subsystem:windows /dll /incremental:no /pdb:"$(OUTDIR)\beeper.pdb" /map:"$(INTDIR)\beeper.map" /machine:I386 /def:".\beeper.def" /out:"$(OUTDIR)\beeper.dll" /implib:"$(OUTDIR)\beeper.lib" 
DEF_FILE= \
	".\beeper.def"
LINK32_OBJS= \
	"$(INTDIR)\beeper.obj" \
	"$(INTDIR)\beepobj.obj" \
	"$(INTDIR)\prebeep.obj" \
	"$(INTDIR)\beeper.res"

"$(OUTDIR)\beeper.dll" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

OutDir=.\.\Release
TargetPath=.\Release\beeper.dll
InputPath=.\Release\beeper.dll
SOURCE=$(InputPath)

"$(OutDir)\regsvr32.trg"	 : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	<<tempfile.bat 
	@echo off 
	regsvr32 /s /c "$(TargetPath)" 
	echo regsvr32 exec. time > "$(OutDir)\regsvr32.trg" 
<< 
	

!ELSEIF  "$(CFG)" == "beeper - Win32 Debug"

OUTDIR=.\Debug
INTDIR=.\Debug
# Begin Custom Macros
OutDir=.\.\Debug
# End Custom Macros

ALL : "$(OUTDIR)\beeper.dll" ".\beeper_i.c" ".\beeper.h" ".\beeper.tlb" ".\.\Debug\regsvr32.trg"


CLEAN :
	-@erase "$(INTDIR)\beeper.obj"
	-@erase "$(INTDIR)\beeper.pch"
	-@erase "$(INTDIR)\beeper.res"
	-@erase "$(INTDIR)\beepobj.obj"
	-@erase "$(INTDIR)\prebeep.obj"
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(INTDIR)\vc60.pdb"
	-@erase "$(OUTDIR)\beeper.dll"
	-@erase "$(OUTDIR)\beeper.exp"
	-@erase "$(OUTDIR)\beeper.ilk"
	-@erase "$(OUTDIR)\beeper.lib"
	-@erase "$(OUTDIR)\beeper.pdb"
	-@erase ".\beeper.h"
	-@erase ".\beeper.tlb"
	-@erase ".\beeper_i.c"
	-@erase ".\.\Debug\regsvr32.trg"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP_PROJ=/nologo /MTd /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_WINDLL" /D "_MBCS" /Fp"$(INTDIR)\beeper.pch" /Yu"prebeep.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 
MTL_PROJ=/nologo /D "_DEBUG" /mktyplib203 /win32 
RSC_PROJ=/l 0x409 /fo"$(INTDIR)\beeper.res" /d "_DEBUG" 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\beeper.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
LINK32_FLAGS=/nologo /subsystem:windows /dll /incremental:yes /pdb:"$(OUTDIR)\beeper.pdb" /debug /machine:I386 /def:".\beeper.def" /out:"$(OUTDIR)\beeper.dll" /implib:"$(OUTDIR)\beeper.lib" 
DEF_FILE= \
	".\beeper.def"
LINK32_OBJS= \
	"$(INTDIR)\beeper.obj" \
	"$(INTDIR)\beepobj.obj" \
	"$(INTDIR)\prebeep.obj" \
	"$(INTDIR)\beeper.res"

"$(OUTDIR)\beeper.dll" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

OutDir=.\.\Debug
TargetPath=.\Debug\beeper.dll
InputPath=.\Debug\beeper.dll
SOURCE=$(InputPath)

"$(OutDir)\regsvr32.trg"	 : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	<<tempfile.bat 
	@echo off 
	regsvr32 /s /c "$(TargetPath)" 
	echo regsvr32 exec. time > "$(OutDir)\regsvr32.trg" 
<< 
	

!ELSEIF  "$(CFG)" == "beeper - Win32 Unicode Debug"

OUTDIR=.\DebugU
INTDIR=.\DebugU
# Begin Custom Macros
OutDir=.\.\DebugU
# End Custom Macros

ALL : "$(OUTDIR)\beeper.dll" ".\beeper_i.c" ".\beeper.h" ".\beeper.tlb" ".\.\DebugU\regsvr32.trg"


CLEAN :
	-@erase "$(INTDIR)\beeper.obj"
	-@erase "$(INTDIR)\beeper.pch"
	-@erase "$(INTDIR)\beeper.res"
	-@erase "$(INTDIR)\beepobj.obj"
	-@erase "$(INTDIR)\prebeep.obj"
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(INTDIR)\vc60.pdb"
	-@erase "$(OUTDIR)\beeper.dll"
	-@erase "$(OUTDIR)\beeper.exp"
	-@erase "$(OUTDIR)\beeper.ilk"
	-@erase "$(OUTDIR)\beeper.lib"
	-@erase "$(OUTDIR)\beeper.pdb"
	-@erase ".\beeper.h"
	-@erase ".\beeper.tlb"
	-@erase ".\beeper_i.c"
	-@erase ".\.\DebugU\regsvr32.trg"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP_PROJ=/nologo /MTd /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_UNICODE" /D "_WINDLL" /D "_MBCS" /Fp"$(INTDIR)\beeper.pch" /Yu"prebeep.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 
MTL_PROJ=/nologo /D "_DEBUG" /mktyplib203 /win32 
RSC_PROJ=/l 0x409 /fo"$(INTDIR)\beeper.res" /d "_DEBUG" 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\beeper.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
LINK32_FLAGS=/nologo /subsystem:windows /dll /incremental:yes /pdb:"$(OUTDIR)\beeper.pdb" /debug /machine:I386 /def:".\beeper.def" /out:"$(OUTDIR)\beeper.dll" /implib:"$(OUTDIR)\beeper.lib" 
DEF_FILE= \
	".\beeper.def"
LINK32_OBJS= \
	"$(INTDIR)\beeper.obj" \
	"$(INTDIR)\beepobj.obj" \
	"$(INTDIR)\prebeep.obj" \
	"$(INTDIR)\beeper.res"

"$(OUTDIR)\beeper.dll" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

OutDir=.\.\DebugU
TargetPath=.\DebugU\beeper.dll
InputPath=.\DebugU\beeper.dll
SOURCE=$(InputPath)

"$(OutDir)\regsvr32.trg"	 : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	<<tempfile.bat 
	@echo off 
	regsvr32 /s /c "$(TargetPath)" 
	echo regsvr32 exec. time > "$(OutDir)\regsvr32.trg" 
<< 
	

!ELSEIF  "$(CFG)" == "beeper - Win32 Unicode Release"

OUTDIR=.\ReleaseU
INTDIR=.\ReleaseU
# Begin Custom Macros
OutDir=.\.\ReleaseU
# End Custom Macros

ALL : "$(OUTDIR)\beeper.dll" ".\beeper_i.c" ".\beeper.h" ".\beeper.tlb" ".\.\ReleaseU\regsvr32.trg"


CLEAN :
	-@erase "$(INTDIR)\beeper.obj"
	-@erase "$(INTDIR)\beeper.pch"
	-@erase "$(INTDIR)\beeper.res"
	-@erase "$(INTDIR)\beepobj.obj"
	-@erase "$(INTDIR)\prebeep.obj"
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(OUTDIR)\beeper.dll"
	-@erase "$(OUTDIR)\beeper.exp"
	-@erase "$(OUTDIR)\beeper.lib"
	-@erase ".\beeper.h"
	-@erase ".\beeper.tlb"
	-@erase ".\beeper_i.c"
	-@erase ".\.\ReleaseU\regsvr32.trg"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP_PROJ=/nologo /MT /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_UNICODE" /D "_WINDLL" /D "_MBCS" /Fp"$(INTDIR)\beeper.pch" /Yu"prebeep.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 
MTL_PROJ=/nologo /D "NDEBUG" /mktyplib203 /win32 
RSC_PROJ=/l 0x409 /fo"$(INTDIR)\beeper.res" /d "NDEBUG" 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\beeper.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
LINK32_FLAGS=/nologo /subsystem:windows /dll /incremental:no /pdb:"$(OUTDIR)\beeper.pdb" /machine:I386 /def:".\beeper.def" /out:"$(OUTDIR)\beeper.dll" /implib:"$(OUTDIR)\beeper.lib" 
DEF_FILE= \
	".\beeper.def"
LINK32_OBJS= \
	"$(INTDIR)\beeper.obj" \
	"$(INTDIR)\beepobj.obj" \
	"$(INTDIR)\prebeep.obj" \
	"$(INTDIR)\beeper.res"

"$(OUTDIR)\beeper.dll" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

OutDir=.\.\ReleaseU
TargetPath=.\ReleaseU\beeper.dll
InputPath=.\ReleaseU\beeper.dll
SOURCE=$(InputPath)

"$(OutDir)\regsvr32.trg"	 : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	<<tempfile.bat 
	@echo off 
	regsvr32 /s /c "$(TargetPath)" 
	echo regsvr32 exec. time > "$(OutDir)\regsvr32.trg" 
<< 
	

!ELSEIF  "$(CFG)" == "beeper - Win32 EXE Release"

OUTDIR=.\RelExe
INTDIR=.\RelExe
# Begin Custom Macros
OutDir=.\.\RelExe
# End Custom Macros

ALL : "$(OUTDIR)\beeper.exe" ".\beeper_i.c" ".\beeper.h" ".\beeper.tlb" ".\.\RelExe\regsvr32.trg"


CLEAN :
	-@erase "$(INTDIR)\beeper.obj"
	-@erase "$(INTDIR)\beeper.pch"
	-@erase "$(INTDIR)\beeper.res"
	-@erase "$(INTDIR)\beepobj.obj"
	-@erase "$(INTDIR)\prebeep.obj"
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(OUTDIR)\beeper.exe"
	-@erase "$(OUTDIR)\beeper.map"
	-@erase ".\beeper.h"
	-@erase ".\beeper.tlb"
	-@erase ".\beeper_i.c"
	-@erase ".\.\RelExe\regsvr32.trg"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP_PROJ=/nologo /MT /W3 /GX /O2 /D "NDEBUG" /D "WIN32" /D "_WINDOWS" /D "_MBCS" /Fp"$(INTDIR)\beeper.pch" /Yu"prebeep.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 
MTL_PROJ=/nologo /D "NDEBUG" /mktyplib203 /win32 
RSC_PROJ=/l 0x409 /fo"$(INTDIR)\beeper.res" /d "NDEBUG" 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\beeper.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
LINK32_FLAGS=/nologo /subsystem:windows /incremental:no /pdb:"$(OUTDIR)\beeper.pdb" /map:"$(INTDIR)\beeper.map" /machine:I386 /out:"$(OUTDIR)\beeper.exe" 
LINK32_OBJS= \
	"$(INTDIR)\beeper.obj" \
	"$(INTDIR)\beepobj.obj" \
	"$(INTDIR)\prebeep.obj" \
	"$(INTDIR)\beeper.res"

"$(OUTDIR)\beeper.exe" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

OutDir=.\.\RelExe
TargetName=beeper
InputPath=.\RelExe\beeper.exe
SOURCE=$(InputPath)

"$(OutDir)\regsvr32.trg"	 : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	<<tempfile.bat 
	@echo off 
	$(OutDir)\$(TargetName) /RegServer 
	echo $(TargetName) exec. time > "$(OutDir)\regsvr32.trg" 
<< 
	

!ELSEIF  "$(CFG)" == "beeper - Win32 EXE Debug"

OUTDIR=.\DebExe
INTDIR=.\DebExe
# Begin Custom Macros
OutDir=.\.\DebExe
# End Custom Macros

ALL : "$(OUTDIR)\beeper.exe" ".\beeper_i.c" ".\beeper.h" ".\beeper.tlb" ".\.\DebExe\regsvr32.trg"


CLEAN :
	-@erase "$(INTDIR)\beeper.obj"
	-@erase "$(INTDIR)\beeper.pch"
	-@erase "$(INTDIR)\beeper.res"
	-@erase "$(INTDIR)\beepobj.obj"
	-@erase "$(INTDIR)\prebeep.obj"
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(INTDIR)\vc60.pdb"
	-@erase "$(OUTDIR)\beeper.exe"
	-@erase "$(OUTDIR)\beeper.ilk"
	-@erase "$(OUTDIR)\beeper.pdb"
	-@erase ".\beeper.h"
	-@erase ".\beeper.tlb"
	-@erase ".\beeper_i.c"
	-@erase ".\.\DebExe\regsvr32.trg"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP_PROJ=/nologo /MTd /W3 /Gm /GX /ZI /Od /D "_DEBUG" /D "WIN32" /D "_WINDOWS" /D "_MBCS" /Fp"$(INTDIR)\beeper.pch" /Yu"prebeep.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 
MTL_PROJ=/nologo /D "_DEBUG" /mktyplib203 /win32 
RSC_PROJ=/l 0x409 /fo"$(INTDIR)\beeper.res" /d "_DEBUG" 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\beeper.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
LINK32_FLAGS=/nologo /subsystem:windows /incremental:yes /pdb:"$(OUTDIR)\beeper.pdb" /debug /machine:I386 /out:"$(OUTDIR)\beeper.exe" 
LINK32_OBJS= \
	"$(INTDIR)\beeper.obj" \
	"$(INTDIR)\beepobj.obj" \
	"$(INTDIR)\prebeep.obj" \
	"$(INTDIR)\beeper.res"

"$(OUTDIR)\beeper.exe" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

OutDir=.\.\DebExe
TargetName=beeper
InputPath=.\DebExe\beeper.exe
SOURCE=$(InputPath)

"$(OutDir)\regsvr32.trg"	 : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	<<tempfile.bat 
	@echo off 
	$(OutDir)\$(TargetName) /RegServer 
	echo $(TargetName) exec. time > "$(OutDir)\regsvr32.trg" 
<< 
	

!ELSEIF  "$(CFG)" == "beeper - Win32 EXE Unicode Debug"

OUTDIR=.\DebExeU
INTDIR=.\DebExeU
# Begin Custom Macros
OutDir=.\.\DebExeU
# End Custom Macros

ALL : "$(OUTDIR)\beeper.exe" ".\beeper_i.c" ".\beeper.h" ".\beeper.tlb" ".\.\DebExeU\regsvr32.trg"


CLEAN :
	-@erase "$(INTDIR)\beeper.obj"
	-@erase "$(INTDIR)\beeper.pch"
	-@erase "$(INTDIR)\beeper.res"
	-@erase "$(INTDIR)\beepobj.obj"
	-@erase "$(INTDIR)\prebeep.obj"
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(INTDIR)\vc60.pdb"
	-@erase "$(OUTDIR)\beeper.exe"
	-@erase "$(OUTDIR)\beeper.ilk"
	-@erase "$(OUTDIR)\beeper.pdb"
	-@erase ".\beeper.h"
	-@erase ".\beeper.tlb"
	-@erase ".\beeper_i.c"
	-@erase ".\.\DebExeU\regsvr32.trg"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP_PROJ=/nologo /MTd /W3 /Gm /GX /ZI /Od /D "_DEBUG" /D "_UNICODE" /D "WIN32" /D "_WINDOWS" /D "_MBCS" /Fp"$(INTDIR)\beeper.pch" /Yu"prebeep.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 
MTL_PROJ=/nologo /D "_DEBUG" /mktyplib203 /win32 
RSC_PROJ=/l 0x409 /fo"$(INTDIR)\beeper.res" /d "_DEBUG" 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\beeper.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
LINK32_FLAGS=/nologo /entry:"wWinMainCRTStartup" /subsystem:windows /incremental:yes /pdb:"$(OUTDIR)\beeper.pdb" /debug /machine:I386 /out:"$(OUTDIR)\beeper.exe" 
LINK32_OBJS= \
	"$(INTDIR)\beeper.obj" \
	"$(INTDIR)\beepobj.obj" \
	"$(INTDIR)\prebeep.obj" \
	"$(INTDIR)\beeper.res"

"$(OUTDIR)\beeper.exe" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

OutDir=.\.\DebExeU
TargetName=beeper
InputPath=.\DebExeU\beeper.exe
SOURCE=$(InputPath)

"$(OutDir)\regsvr32.trg"	 : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	<<tempfile.bat 
	@echo off 
	$(OutDir)\$(TargetName) /RegServer 
	echo $(TargetName) exec. time > "$(OutDir)\regsvr32.trg" 
<< 
	

!ELSEIF  "$(CFG)" == "beeper - Win32 EXE Unicode Release"

OUTDIR=.\RelExeU
INTDIR=.\RelExeU
# Begin Custom Macros
OutDir=.\.\RelExeU
# End Custom Macros

ALL : "$(OUTDIR)\beeper.exe" ".\beeper_i.c" ".\beeper.h" ".\beeper.tlb" ".\.\RelExeU\regsvr32.trg"


CLEAN :
	-@erase "$(INTDIR)\beeper.obj"
	-@erase "$(INTDIR)\beeper.pch"
	-@erase "$(INTDIR)\beeper.res"
	-@erase "$(INTDIR)\beepobj.obj"
	-@erase "$(INTDIR)\prebeep.obj"
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(OUTDIR)\beeper.exe"
	-@erase ".\beeper.h"
	-@erase ".\beeper.tlb"
	-@erase ".\beeper_i.c"
	-@erase ".\.\RelExeU\regsvr32.trg"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP_PROJ=/nologo /MT /W3 /GX /O2 /D "NDEBUG" /D "_UNICODE" /D "WIN32" /D "_WINDOWS" /D "_MBCS" /Fp"$(INTDIR)\beeper.pch" /Yu"prebeep.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 
MTL_PROJ=/nologo /D "NDEBUG" /mktyplib203 /win32 
RSC_PROJ=/l 0x409 /fo"$(INTDIR)\beeper.res" /d "NDEBUG" 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\beeper.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
LINK32_FLAGS=/nologo /entry:"wWinMainCRTStartup" /subsystem:windows /incremental:no /pdb:"$(OUTDIR)\beeper.pdb" /machine:I386 /out:"$(OUTDIR)\beeper.exe" 
LINK32_OBJS= \
	"$(INTDIR)\beeper.obj" \
	"$(INTDIR)\beepobj.obj" \
	"$(INTDIR)\prebeep.obj" \
	"$(INTDIR)\beeper.res"

"$(OUTDIR)\beeper.exe" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

OutDir=.\.\RelExeU
TargetName=beeper
InputPath=.\RelExeU\beeper.exe
SOURCE=$(InputPath)

"$(OutDir)\regsvr32.trg"	 : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	<<tempfile.bat 
	@echo off 
	$(OutDir)\$(TargetName) /RegServer 
	echo $(TargetName) exec. time > "$(OutDir)\regsvr32.trg" 
<< 
	

!ELSEIF  "$(CFG)" == "beeper - Win32 Release MINCRT"

OUTDIR=.\MinCRT
INTDIR=.\MinCRT
# Begin Custom Macros
OutDir=.\.\MinCRT
# End Custom Macros

ALL : "$(OUTDIR)\beeper.dll" ".\beeper_i.c" ".\beeper.h" ".\beeper.tlb" ".\.\MinCRT\regsvr32.trg"


CLEAN :
	-@erase "$(INTDIR)\beeper.obj"
	-@erase "$(INTDIR)\beeper.pch"
	-@erase "$(INTDIR)\beeper.res"
	-@erase "$(INTDIR)\beepobj.obj"
	-@erase "$(INTDIR)\prebeep.obj"
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(OUTDIR)\beeper.dll"
	-@erase "$(OUTDIR)\beeper.exp"
	-@erase "$(OUTDIR)\beeper.lib"
	-@erase "$(OUTDIR)\beeper.map"
	-@erase ".\beeper.h"
	-@erase ".\beeper.tlb"
	-@erase ".\beeper_i.c"
	-@erase ".\.\MinCRT\regsvr32.trg"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP_PROJ=/nologo /MT /W3 /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_WINDLL" /D "_MBCS" /D "_ATL_MIN_CRT" /Fp"$(INTDIR)\beeper.pch" /Yu"prebeep.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 
MTL_PROJ=/nologo /D "NDEBUG" /mktyplib203 /win32 
RSC_PROJ=/l 0x409 /fo"$(INTDIR)\beeper.res" /d "NDEBUG" 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\beeper.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
LINK32_FLAGS=/nologo /entry:"DllMain" /subsystem:windows /dll /incremental:no /pdb:"$(OUTDIR)\beeper.pdb" /map:"$(INTDIR)\beeper.map" /machine:I386 /def:".\beeper.def" /out:"$(OUTDIR)\beeper.dll" /implib:"$(OUTDIR)\beeper.lib" 
DEF_FILE= \
	".\beeper.def"
LINK32_OBJS= \
	"$(INTDIR)\beeper.obj" \
	"$(INTDIR)\beepobj.obj" \
	"$(INTDIR)\prebeep.obj" \
	"$(INTDIR)\beeper.res"

"$(OUTDIR)\beeper.dll" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

OutDir=.\.\MinCRT
TargetPath=.\MinCRT\beeper.dll
InputPath=.\MinCRT\beeper.dll
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
!IF EXISTS("beeper.dep")
!INCLUDE "beeper.dep"
!ELSE 
!MESSAGE Warning: cannot find "beeper.dep"
!ENDIF 
!ENDIF 


!IF "$(CFG)" == "beeper - Win32 Release" || "$(CFG)" == "beeper - Win32 Debug" || "$(CFG)" == "beeper - Win32 Unicode Debug" || "$(CFG)" == "beeper - Win32 Unicode Release" || "$(CFG)" == "beeper - Win32 EXE Release" || "$(CFG)" == "beeper - Win32 EXE Debug" || "$(CFG)" == "beeper - Win32 EXE Unicode Debug" || "$(CFG)" == "beeper - Win32 EXE Unicode Release" || "$(CFG)" == "beeper - Win32 Release MINCRT"
SOURCE=.\beeper.cpp

"$(INTDIR)\beeper.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\beeper.pch"


SOURCE=.\beeper.idl

!IF  "$(CFG)" == "beeper - Win32 Release"

MTL_SWITCHES=/nologo /D "NDEBUG" /tlb ".\beeper.tlb" /h "beeper.h" /iid "beeper_i.c" /win32 

".\beeper.tlb"	".\beeper.h"	".\beeper_i.c" : $(SOURCE) "$(INTDIR)"
	$(MTL) @<<
  $(MTL_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "beeper - Win32 Debug"

MTL_SWITCHES=/nologo /D "_DEBUG" /tlb ".\beeper.tlb" /h "beeper.h" /iid "beeper_i.c" /win32 

".\beeper.tlb"	".\beeper.h"	".\beeper_i.c" : $(SOURCE) "$(INTDIR)"
	$(MTL) @<<
  $(MTL_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "beeper - Win32 Unicode Debug"

MTL_SWITCHES=/nologo /D "_DEBUG" /tlb ".\beeper.tlb" /h "beeper.h" /iid "beeper_i.c" /win32 

".\beeper.tlb"	".\beeper.h"	".\beeper_i.c" : $(SOURCE) "$(INTDIR)"
	$(MTL) @<<
  $(MTL_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "beeper - Win32 Unicode Release"

MTL_SWITCHES=/nologo /D "NDEBUG" /tlb ".\beeper.tlb" /h "beeper.h" /iid "beeper_i.c" /win32 

".\beeper.tlb"	".\beeper.h"	".\beeper_i.c" : $(SOURCE) "$(INTDIR)"
	$(MTL) @<<
  $(MTL_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "beeper - Win32 EXE Release"

MTL_SWITCHES=/nologo /D "NDEBUG" /tlb ".\beeper.tlb" /h "beeper.h" /iid "beeper_i.c" /win32 

".\beeper.tlb"	".\beeper.h"	".\beeper_i.c" : $(SOURCE) "$(INTDIR)"
	$(MTL) @<<
  $(MTL_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "beeper - Win32 EXE Debug"

MTL_SWITCHES=/nologo /D "_DEBUG" /tlb ".\beeper.tlb" /h "beeper.h" /iid "beeper_i.c" /win32 

".\beeper.tlb"	".\beeper.h"	".\beeper_i.c" : $(SOURCE) "$(INTDIR)"
	$(MTL) @<<
  $(MTL_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "beeper - Win32 EXE Unicode Debug"

MTL_SWITCHES=/nologo /D "_DEBUG" /tlb ".\beeper.tlb" /h "beeper.h" /iid "beeper_i.c" /win32 

".\beeper.tlb"	".\beeper.h"	".\beeper_i.c" : $(SOURCE) "$(INTDIR)"
	$(MTL) @<<
  $(MTL_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "beeper - Win32 EXE Unicode Release"

MTL_SWITCHES=/nologo /D "NDEBUG" /tlb ".\beeper.tlb" /h "beeper.h" /iid "beeper_i.c" /win32 

".\beeper.tlb"	".\beeper.h"	".\beeper_i.c" : $(SOURCE) "$(INTDIR)"
	$(MTL) @<<
  $(MTL_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "beeper - Win32 Release MINCRT"

MTL_SWITCHES=/nologo /D "NDEBUG" /tlb ".\beeper.tlb" /h "beeper.h" /iid "beeper_i.c" /win32 

".\beeper.tlb"	".\beeper.h"	".\beeper_i.c" : $(SOURCE) "$(INTDIR)"
	$(MTL) @<<
  $(MTL_SWITCHES) $(SOURCE)
<<


!ENDIF 

SOURCE=.\beeper.rc

"$(INTDIR)\beeper.res" : $(SOURCE) "$(INTDIR)"
	$(RSC) $(RSC_PROJ) $(SOURCE)


SOURCE=.\beepobj.cpp

"$(INTDIR)\beepobj.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\beeper.pch"


SOURCE=.\prebeep.cpp

!IF  "$(CFG)" == "beeper - Win32 Release"

CPP_SWITCHES=/nologo /MT /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_WINDLL" /D "_MBCS" /Fp"$(INTDIR)\beeper.pch" /Yc"prebeep.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 

"$(INTDIR)\prebeep.obj"	"$(INTDIR)\beeper.pch" : $(SOURCE) "$(INTDIR)"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "beeper - Win32 Debug"

CPP_SWITCHES=/nologo /MTd /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_WINDLL" /D "_MBCS" /Fp"$(INTDIR)\beeper.pch" /Yc"prebeep.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 

"$(INTDIR)\prebeep.obj"	"$(INTDIR)\beeper.pch" : $(SOURCE) "$(INTDIR)"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "beeper - Win32 Unicode Debug"

CPP_SWITCHES=/nologo /MTd /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_UNICODE" /D "_WINDLL" /D "_MBCS" /Fp"$(INTDIR)\beeper.pch" /Yc"prebeep.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 

"$(INTDIR)\prebeep.obj"	"$(INTDIR)\beeper.pch" : $(SOURCE) "$(INTDIR)"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "beeper - Win32 Unicode Release"

CPP_SWITCHES=/nologo /MT /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_UNICODE" /D "_WINDLL" /D "_MBCS" /Fp"$(INTDIR)\beeper.pch" /Yc"prebeep.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 

"$(INTDIR)\prebeep.obj"	"$(INTDIR)\beeper.pch" : $(SOURCE) "$(INTDIR)"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "beeper - Win32 EXE Release"

CPP_SWITCHES=/nologo /MT /W3 /GX /O2 /D "NDEBUG" /D "WIN32" /D "_WINDOWS" /D "_MBCS" /Fp"$(INTDIR)\beeper.pch" /Yc"prebeep.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 

"$(INTDIR)\prebeep.obj"	"$(INTDIR)\beeper.pch" : $(SOURCE) "$(INTDIR)"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "beeper - Win32 EXE Debug"

CPP_SWITCHES=/nologo /MTd /W3 /Gm /GX /ZI /Od /D "_DEBUG" /D "WIN32" /D "_WINDOWS" /D "_MBCS" /Fp"$(INTDIR)\beeper.pch" /Yc"prebeep.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 

"$(INTDIR)\prebeep.obj"	"$(INTDIR)\beeper.pch" : $(SOURCE) "$(INTDIR)"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "beeper - Win32 EXE Unicode Debug"

CPP_SWITCHES=/nologo /MTd /W3 /Gm /GX /ZI /Od /D "_DEBUG" /D "_UNICODE" /D "WIN32" /D "_WINDOWS" /D "_MBCS" /Fp"$(INTDIR)\beeper.pch" /Yc"prebeep.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 

"$(INTDIR)\prebeep.obj"	"$(INTDIR)\beeper.pch" : $(SOURCE) "$(INTDIR)"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "beeper - Win32 EXE Unicode Release"

CPP_SWITCHES=/nologo /MT /W3 /GX /O2 /D "NDEBUG" /D "_UNICODE" /D "WIN32" /D "_WINDOWS" /D "_MBCS" /Fp"$(INTDIR)\beeper.pch" /Yc"prebeep.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 

"$(INTDIR)\prebeep.obj"	"$(INTDIR)\beeper.pch" : $(SOURCE) "$(INTDIR)"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "beeper - Win32 Release MINCRT"

CPP_SWITCHES=/nologo /MT /W3 /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_WINDLL" /D "_MBCS" /D "_ATL_MIN_CRT" /Fp"$(INTDIR)\beeper.pch" /Yc"prebeep.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 

"$(INTDIR)\prebeep.obj"	"$(INTDIR)\beeper.pch" : $(SOURCE) "$(INTDIR)"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ENDIF 


!ENDIF 

