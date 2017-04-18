# Microsoft Developer Studio Generated NMAKE File, Based on circ2.dsp
!IF "$(CFG)" == ""
CFG=Circ2 - Win32 Release
!MESSAGE No configuration specified. Defaulting to Circ2 - Win32 Release.
!ENDIF 

!IF "$(CFG)" != "Circ2 - Win32 Release" && "$(CFG)" != "Circ2 - Win32 Debug" && "$(CFG)" != "Circ2 - Win32 Unicode Debug" && "$(CFG)" != "Circ2 - Win32 Unicode Release"
!MESSAGE Invalid configuration "$(CFG)" specified.
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "circ2.mak" CFG="Circ2 - Win32 Release"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "Circ2 - Win32 Release" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE "Circ2 - Win32 Debug" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE "Circ2 - Win32 Unicode Debug" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE "Circ2 - Win32 Unicode Release" (based on "Win32 (x86) Dynamic-Link Library")
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

!IF  "$(CFG)" == "Circ2 - Win32 Release"

OUTDIR=.\Release
INTDIR=.\Release
# Begin Custom Macros
OutDir=.\.\Release
# End Custom Macros

ALL : "$(OUTDIR)\circ2.ocx" ".\.\Release\regsvr32.trg"


CLEAN :
	-@erase "$(INTDIR)\circ2.obj"
	-@erase "$(INTDIR)\circ2.pch"
	-@erase "$(INTDIR)\circ2.res"
	-@erase "$(INTDIR)\circ2.tlb"
	-@erase "$(INTDIR)\circ2ctl.obj"
	-@erase "$(INTDIR)\circ2ppg.obj"
	-@erase "$(INTDIR)\stdafx.obj"
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(OUTDIR)\circ2.exp"
	-@erase "$(OUTDIR)\circ2.lib"
	-@erase "$(OUTDIR)\circ2.ocx"
	-@erase ".\.\Release\regsvr32.trg"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP_PROJ=/nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /Fp"$(INTDIR)\circ2.pch" /Yu"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 
MTL_PROJ=/nologo /D "NDEBUG" /mktyplib203 /win32 
RSC_PROJ=/l 0x409 /fo"$(INTDIR)\circ2.res" /d "NDEBUG" /d "_AFXDLL" 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\circ2.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
LINK32_FLAGS=/nologo /subsystem:windows /dll /incremental:no /pdb:"$(OUTDIR)\circ2.pdb" /machine:I386 /def:".\circ2.def" /out:"$(OUTDIR)\circ2.ocx" /implib:"$(OUTDIR)\circ2.lib" 
DEF_FILE= \
	".\circ2.def"
LINK32_OBJS= \
	"$(INTDIR)\circ2.obj" \
	"$(INTDIR)\circ2ctl.obj" \
	"$(INTDIR)\circ2ppg.obj" \
	"$(INTDIR)\stdafx.obj" \
	"$(INTDIR)\circ2.res"

"$(OUTDIR)\circ2.ocx" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

OutDir=.\.\Release
TargetPath=.\Release\circ2.ocx
InputPath=.\Release\circ2.ocx
SOURCE=$(InputPath)

"$(OutDir)\regsvr32.trg"	 : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	<<tempfile.bat 
	@echo off 
	regsvr32 /s /c "$(TargetPath)" 
	echo regsvr32 exec. time > "$(OutDir)\regsvr32.trg" 
<< 
	

!ELSEIF  "$(CFG)" == "Circ2 - Win32 Debug"

OUTDIR=.\Debug
INTDIR=.\Debug
# Begin Custom Macros
OutDir=.\.\Debug
# End Custom Macros

ALL : "$(OUTDIR)\circ2.ocx" ".\.\Debug\regsvr32.trg"


CLEAN :
	-@erase "$(INTDIR)\circ2.obj"
	-@erase "$(INTDIR)\circ2.pch"
	-@erase "$(INTDIR)\circ2.res"
	-@erase "$(INTDIR)\circ2.tlb"
	-@erase "$(INTDIR)\circ2ctl.obj"
	-@erase "$(INTDIR)\circ2ppg.obj"
	-@erase "$(INTDIR)\stdafx.obj"
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(INTDIR)\vc60.pdb"
	-@erase "$(OUTDIR)\circ2.exp"
	-@erase "$(OUTDIR)\circ2.ilk"
	-@erase "$(OUTDIR)\circ2.lib"
	-@erase "$(OUTDIR)\circ2.ocx"
	-@erase "$(OUTDIR)\circ2.pdb"
	-@erase ".\.\Debug\regsvr32.trg"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP_PROJ=/nologo /MDd /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /Fp"$(INTDIR)\circ2.pch" /Yu"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 
MTL_PROJ=/nologo /D "_DEBUG" /mktyplib203 /win32 
RSC_PROJ=/l 0x409 /fo"$(INTDIR)\circ2.res" /d "_DEBUG" /d "_AFXDLL" 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\circ2.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
LINK32_FLAGS=/nologo /subsystem:windows /dll /incremental:yes /pdb:"$(OUTDIR)\circ2.pdb" /debug /machine:I386 /def:".\circ2.def" /out:"$(OUTDIR)\circ2.ocx" /implib:"$(OUTDIR)\circ2.lib" 
DEF_FILE= \
	".\circ2.def"
LINK32_OBJS= \
	"$(INTDIR)\circ2.obj" \
	"$(INTDIR)\circ2ctl.obj" \
	"$(INTDIR)\circ2ppg.obj" \
	"$(INTDIR)\stdafx.obj" \
	"$(INTDIR)\circ2.res"

"$(OUTDIR)\circ2.ocx" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

OutDir=.\.\Debug
TargetPath=.\Debug\circ2.ocx
InputPath=.\Debug\circ2.ocx
SOURCE=$(InputPath)

"$(OutDir)\regsvr32.trg"	 : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	<<tempfile.bat 
	@echo off 
	regsvr32 /s /c "$(TargetPath)" 
	echo regsvr32 exec. time > "$(OutDir)\regsvr32.trg" 
<< 
	

!ELSEIF  "$(CFG)" == "Circ2 - Win32 Unicode Debug"

OUTDIR=.\UniDebug
INTDIR=.\UniDebug
# Begin Custom Macros
OutDir=.\.\UniDebug
# End Custom Macros

ALL : "$(OUTDIR)\circ2.ocx" ".\.\UniDebug\regsvr32.trg"


CLEAN :
	-@erase "$(INTDIR)\circ2.obj"
	-@erase "$(INTDIR)\circ2.pch"
	-@erase "$(INTDIR)\circ2.res"
	-@erase "$(INTDIR)\circ2.tlb"
	-@erase "$(INTDIR)\circ2ctl.obj"
	-@erase "$(INTDIR)\circ2ppg.obj"
	-@erase "$(INTDIR)\stdafx.obj"
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(INTDIR)\vc60.pdb"
	-@erase "$(OUTDIR)\circ2.exp"
	-@erase "$(OUTDIR)\circ2.ilk"
	-@erase "$(OUTDIR)\circ2.lib"
	-@erase "$(OUTDIR)\circ2.ocx"
	-@erase "$(OUTDIR)\circ2.pdb"
	-@erase ".\.\UniDebug\regsvr32.trg"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP_PROJ=/nologo /MDd /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_UNICODE" /Fp"$(INTDIR)\circ2.pch" /Yu"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 
MTL_PROJ=/nologo /D "_DEBUG" /mktyplib203 /win32 
RSC_PROJ=/l 0x409 /fo"$(INTDIR)\circ2.res" /d "_DEBUG" /d "_AFXDLL" 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\circ2.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
LINK32_FLAGS=/nologo /subsystem:windows /dll /incremental:yes /pdb:"$(OUTDIR)\circ2.pdb" /debug /machine:I386 /def:".\circ2.def" /out:"$(OUTDIR)\circ2.ocx" /implib:"$(OUTDIR)\circ2.lib" 
DEF_FILE= \
	".\circ2.def"
LINK32_OBJS= \
	"$(INTDIR)\circ2.obj" \
	"$(INTDIR)\circ2ctl.obj" \
	"$(INTDIR)\circ2ppg.obj" \
	"$(INTDIR)\stdafx.obj" \
	"$(INTDIR)\circ2.res"

"$(OUTDIR)\circ2.ocx" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

OutDir=.\.\UniDebug
TargetPath=.\UniDebug\circ2.ocx
InputPath=.\UniDebug\circ2.ocx
SOURCE=$(InputPath)

"$(OutDir)\regsvr32.trg"	 : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	<<tempfile.bat 
	@echo off 
	regsvr32 /s /c "$(TargetPath)" 
	echo regsvr32 exec. time > "$(OutDir)\regsvr32.trg" 
<< 
	

!ELSEIF  "$(CFG)" == "Circ2 - Win32 Unicode Release"

OUTDIR=.\UniRelease
INTDIR=.\UniRelease
# Begin Custom Macros
OutDir=.\.\UniRelease
# End Custom Macros

ALL : "$(OUTDIR)\circ2.ocx" ".\.\UniRelease\regsvr32.trg"


CLEAN :
	-@erase "$(INTDIR)\circ2.obj"
	-@erase "$(INTDIR)\circ2.pch"
	-@erase "$(INTDIR)\circ2.res"
	-@erase "$(INTDIR)\circ2.tlb"
	-@erase "$(INTDIR)\circ2ctl.obj"
	-@erase "$(INTDIR)\circ2ppg.obj"
	-@erase "$(INTDIR)\stdafx.obj"
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(OUTDIR)\circ2.exp"
	-@erase "$(OUTDIR)\circ2.lib"
	-@erase "$(OUTDIR)\circ2.ocx"
	-@erase ".\.\UniRelease\regsvr32.trg"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP_PROJ=/nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_UNICODE" /Fp"$(INTDIR)\circ2.pch" /Yu"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 
MTL_PROJ=/nologo /D "NDEBUG" /mktyplib203 /win32 
RSC_PROJ=/l 0x409 /fo"$(INTDIR)\circ2.res" /d "NDEBUG" /d "_AFXDLL" 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\circ2.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
LINK32_FLAGS=/nologo /subsystem:windows /dll /incremental:no /pdb:"$(OUTDIR)\circ2.pdb" /machine:I386 /def:".\circ2.def" /out:"$(OUTDIR)\circ2.ocx" /implib:"$(OUTDIR)\circ2.lib" 
DEF_FILE= \
	".\circ2.def"
LINK32_OBJS= \
	"$(INTDIR)\circ2.obj" \
	"$(INTDIR)\circ2ctl.obj" \
	"$(INTDIR)\circ2ppg.obj" \
	"$(INTDIR)\stdafx.obj" \
	"$(INTDIR)\circ2.res"

"$(OUTDIR)\circ2.ocx" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

OutDir=.\.\UniRelease
TargetPath=.\UniRelease\circ2.ocx
InputPath=.\UniRelease\circ2.ocx
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
!IF EXISTS("circ2.dep")
!INCLUDE "circ2.dep"
!ELSE 
!MESSAGE Warning: cannot find "circ2.dep"
!ENDIF 
!ENDIF 


!IF "$(CFG)" == "Circ2 - Win32 Release" || "$(CFG)" == "Circ2 - Win32 Debug" || "$(CFG)" == "Circ2 - Win32 Unicode Debug" || "$(CFG)" == "Circ2 - Win32 Unicode Release"
SOURCE=.\circ2.cpp

"$(INTDIR)\circ2.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\circ2.pch"


SOURCE=.\circ2.odl

!IF  "$(CFG)" == "Circ2 - Win32 Release"

MTL_SWITCHES=/nologo /D "NDEBUG" /tlb "$(OUTDIR)\circ2.tlb" /mktyplib203 /win32 

"$(OUTDIR)\circ2.tlb" : $(SOURCE) "$(OUTDIR)"
	$(MTL) @<<
  $(MTL_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "Circ2 - Win32 Debug"

MTL_SWITCHES=/nologo /D "_DEBUG" /tlb "$(OUTDIR)\circ2.tlb" /mktyplib203 /win32 

"$(OUTDIR)\circ2.tlb" : $(SOURCE) "$(OUTDIR)"
	$(MTL) @<<
  $(MTL_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "Circ2 - Win32 Unicode Debug"

MTL_SWITCHES=/nologo /D "_DEBUG" /tlb "$(OUTDIR)\circ2.tlb" /mktyplib203 /win32 

"$(OUTDIR)\circ2.tlb" : $(SOURCE) "$(OUTDIR)"
	$(MTL) @<<
  $(MTL_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "Circ2 - Win32 Unicode Release"

MTL_SWITCHES=/nologo /D "NDEBUG" /tlb "$(OUTDIR)\circ2.tlb" /mktyplib203 /win32 

"$(OUTDIR)\circ2.tlb" : $(SOURCE) "$(OUTDIR)"
	$(MTL) @<<
  $(MTL_SWITCHES) $(SOURCE)
<<


!ENDIF 

SOURCE=.\circ2.rc

!IF  "$(CFG)" == "Circ2 - Win32 Release"


"$(INTDIR)\circ2.res" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\circ2.tlb"
	$(RSC) /l 0x409 /fo"$(INTDIR)\circ2.res" /i ".\Release" /d "NDEBUG" /d "_AFXDLL" $(SOURCE)


!ELSEIF  "$(CFG)" == "Circ2 - Win32 Debug"


"$(INTDIR)\circ2.res" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\circ2.tlb"
	$(RSC) /l 0x409 /fo"$(INTDIR)\circ2.res" /i ".\Debug" /d "_DEBUG" /d "_AFXDLL" $(SOURCE)


!ELSEIF  "$(CFG)" == "Circ2 - Win32 Unicode Debug"


"$(INTDIR)\circ2.res" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\circ2.tlb"
	$(RSC) /l 0x409 /fo"$(INTDIR)\circ2.res" /i ".\UniDebug" /d "_DEBUG" /d "_AFXDLL" $(SOURCE)


!ELSEIF  "$(CFG)" == "Circ2 - Win32 Unicode Release"


"$(INTDIR)\circ2.res" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\circ2.tlb"
	$(RSC) /l 0x409 /fo"$(INTDIR)\circ2.res" /i ".\UniRelease" /d "NDEBUG" /d "_AFXDLL" $(SOURCE)


!ENDIF 

SOURCE=.\circ2ctl.cpp

"$(INTDIR)\circ2ctl.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\circ2.pch"


SOURCE=.\circ2ppg.cpp

"$(INTDIR)\circ2ppg.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\circ2.pch"


SOURCE=.\stdafx.cpp

!IF  "$(CFG)" == "Circ2 - Win32 Release"

CPP_SWITCHES=/nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /Fp"$(INTDIR)\circ2.pch" /Yc"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 

"$(INTDIR)\stdafx.obj"	"$(INTDIR)\circ2.pch" : $(SOURCE) "$(INTDIR)"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "Circ2 - Win32 Debug"

CPP_SWITCHES=/nologo /MDd /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /Fp"$(INTDIR)\circ2.pch" /Yc"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 

"$(INTDIR)\stdafx.obj"	"$(INTDIR)\circ2.pch" : $(SOURCE) "$(INTDIR)"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "Circ2 - Win32 Unicode Debug"

CPP_SWITCHES=/nologo /MDd /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_UNICODE" /Fp"$(INTDIR)\circ2.pch" /Yc"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 

"$(INTDIR)\stdafx.obj"	"$(INTDIR)\circ2.pch" : $(SOURCE) "$(INTDIR)"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "Circ2 - Win32 Unicode Release"

CPP_SWITCHES=/nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_UNICODE" /Fp"$(INTDIR)\circ2.pch" /Yc"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 

"$(INTDIR)\stdafx.obj"	"$(INTDIR)\circ2.pch" : $(SOURCE) "$(INTDIR)"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ENDIF 


!ENDIF 

