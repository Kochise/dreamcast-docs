# Microsoft Developer Studio Generated NMAKE File, Based on circ1.dsp
!IF "$(CFG)" == ""
CFG=Circ1 - Win32 Release
!MESSAGE No configuration specified. Defaulting to Circ1 - Win32 Release.
!ENDIF 

!IF "$(CFG)" != "Circ1 - Win32 Release" && "$(CFG)" != "Circ1 - Win32 Debug" && "$(CFG)" != "Circ1 - Win32 Unicode Debug" && "$(CFG)" != "Circ1 - Win32 Unicode Release"
!MESSAGE Invalid configuration "$(CFG)" specified.
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "circ1.mak" CFG="Circ1 - Win32 Release"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "Circ1 - Win32 Release" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE "Circ1 - Win32 Debug" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE "Circ1 - Win32 Unicode Debug" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE "Circ1 - Win32 Unicode Release" (based on "Win32 (x86) Dynamic-Link Library")
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

!IF  "$(CFG)" == "Circ1 - Win32 Release"

OUTDIR=.\Release
INTDIR=.\Release
# Begin Custom Macros
OutDir=.\.\Release
# End Custom Macros

ALL : "$(OUTDIR)\circ1.ocx" ".\.\Release\regsvr32.trg"


CLEAN :
	-@erase "$(INTDIR)\circ1.obj"
	-@erase "$(INTDIR)\circ1.pch"
	-@erase "$(INTDIR)\circ1.res"
	-@erase "$(INTDIR)\circ1.tlb"
	-@erase "$(INTDIR)\circ1ctl.obj"
	-@erase "$(INTDIR)\circ1ppg.obj"
	-@erase "$(INTDIR)\stdafx.obj"
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(OUTDIR)\circ1.exp"
	-@erase "$(OUTDIR)\circ1.lib"
	-@erase "$(OUTDIR)\circ1.ocx"
	-@erase ".\.\Release\regsvr32.trg"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP_PROJ=/nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /Fp"$(INTDIR)\circ1.pch" /Yu"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 
MTL_PROJ=/nologo /D "NDEBUG" /mktyplib203 /win32 
RSC_PROJ=/l 0x409 /fo"$(INTDIR)\circ1.res" /d "NDEBUG" /d "_AFXDLL" 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\circ1.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
LINK32_FLAGS=/nologo /subsystem:windows /dll /incremental:no /pdb:"$(OUTDIR)\circ1.pdb" /machine:I386 /def:".\circ1.def" /out:"$(OUTDIR)\circ1.ocx" /implib:"$(OUTDIR)\circ1.lib" 
DEF_FILE= \
	".\circ1.def"
LINK32_OBJS= \
	"$(INTDIR)\circ1.obj" \
	"$(INTDIR)\circ1ctl.obj" \
	"$(INTDIR)\circ1ppg.obj" \
	"$(INTDIR)\stdafx.obj" \
	"$(INTDIR)\circ1.res"

"$(OUTDIR)\circ1.ocx" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

OutDir=.\.\Release
TargetPath=.\Release\circ1.ocx
InputPath=.\Release\circ1.ocx
SOURCE=$(InputPath)

"$(OutDir)\regsvr32.trg"	 : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	<<tempfile.bat 
	@echo off 
	regsvr32 /s /c "$(TargetPath)" 
	echo regsvr32 exec. time > "$(OutDir)\regsvr32.trg" 
<< 
	

!ELSEIF  "$(CFG)" == "Circ1 - Win32 Debug"

OUTDIR=.\Debug
INTDIR=.\Debug
# Begin Custom Macros
OutDir=.\.\Debug
# End Custom Macros

ALL : "$(OUTDIR)\circ1.ocx" ".\.\Debug\regsvr32.trg"


CLEAN :
	-@erase "$(INTDIR)\circ1.obj"
	-@erase "$(INTDIR)\circ1.pch"
	-@erase "$(INTDIR)\circ1.res"
	-@erase "$(INTDIR)\circ1.tlb"
	-@erase "$(INTDIR)\circ1ctl.obj"
	-@erase "$(INTDIR)\circ1ppg.obj"
	-@erase "$(INTDIR)\stdafx.obj"
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(INTDIR)\vc60.pdb"
	-@erase "$(OUTDIR)\circ1.exp"
	-@erase "$(OUTDIR)\circ1.ilk"
	-@erase "$(OUTDIR)\circ1.lib"
	-@erase "$(OUTDIR)\circ1.ocx"
	-@erase "$(OUTDIR)\circ1.pdb"
	-@erase ".\.\Debug\regsvr32.trg"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP_PROJ=/nologo /MDd /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /Fp"$(INTDIR)\circ1.pch" /Yu"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 
MTL_PROJ=/nologo /D "_DEBUG" /mktyplib203 /win32 
RSC_PROJ=/l 0x409 /fo"$(INTDIR)\circ1.res" /d "_DEBUG" /d "_AFXDLL" 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\circ1.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
LINK32_FLAGS=/nologo /subsystem:windows /dll /incremental:yes /pdb:"$(OUTDIR)\circ1.pdb" /debug /machine:I386 /def:".\circ1.def" /out:"$(OUTDIR)\circ1.ocx" /implib:"$(OUTDIR)\circ1.lib" 
DEF_FILE= \
	".\circ1.def"
LINK32_OBJS= \
	"$(INTDIR)\circ1.obj" \
	"$(INTDIR)\circ1ctl.obj" \
	"$(INTDIR)\circ1ppg.obj" \
	"$(INTDIR)\stdafx.obj" \
	"$(INTDIR)\circ1.res"

"$(OUTDIR)\circ1.ocx" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

OutDir=.\.\Debug
TargetPath=.\Debug\circ1.ocx
InputPath=.\Debug\circ1.ocx
SOURCE=$(InputPath)

"$(OutDir)\regsvr32.trg"	 : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	<<tempfile.bat 
	@echo off 
	regsvr32 /s /c "$(TargetPath)" 
	echo regsvr32 exec. time > "$(OutDir)\regsvr32.trg" 
<< 
	

!ELSEIF  "$(CFG)" == "Circ1 - Win32 Unicode Debug"

OUTDIR=.\UniDebug
INTDIR=.\UniDebug
# Begin Custom Macros
OutDir=.\.\UniDebug
# End Custom Macros

ALL : "$(OUTDIR)\circ1.ocx" ".\.\UniDebug\regsvr32.trg"


CLEAN :
	-@erase "$(INTDIR)\circ1.obj"
	-@erase "$(INTDIR)\circ1.pch"
	-@erase "$(INTDIR)\circ1.res"
	-@erase "$(INTDIR)\circ1.tlb"
	-@erase "$(INTDIR)\circ1ctl.obj"
	-@erase "$(INTDIR)\circ1ppg.obj"
	-@erase "$(INTDIR)\stdafx.obj"
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(INTDIR)\vc60.pdb"
	-@erase "$(OUTDIR)\circ1.exp"
	-@erase "$(OUTDIR)\circ1.ilk"
	-@erase "$(OUTDIR)\circ1.lib"
	-@erase "$(OUTDIR)\circ1.ocx"
	-@erase "$(OUTDIR)\circ1.pdb"
	-@erase ".\.\UniDebug\regsvr32.trg"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP_PROJ=/nologo /MDd /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_UNICODE" /Fp"$(INTDIR)\circ1.pch" /Yu"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 
MTL_PROJ=/nologo /D "_DEBUG" /mktyplib203 /win32 
RSC_PROJ=/l 0x409 /fo"$(INTDIR)\circ1.res" /d "_DEBUG" /d "_AFXDLL" 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\circ1.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
LINK32_FLAGS=/nologo /subsystem:windows /dll /incremental:yes /pdb:"$(OUTDIR)\circ1.pdb" /debug /machine:I386 /def:".\circ1.def" /out:"$(OUTDIR)\circ1.ocx" /implib:"$(OUTDIR)\circ1.lib" 
DEF_FILE= \
	".\circ1.def"
LINK32_OBJS= \
	"$(INTDIR)\circ1.obj" \
	"$(INTDIR)\circ1ctl.obj" \
	"$(INTDIR)\circ1ppg.obj" \
	"$(INTDIR)\stdafx.obj" \
	"$(INTDIR)\circ1.res"

"$(OUTDIR)\circ1.ocx" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

OutDir=.\.\UniDebug
TargetPath=.\UniDebug\circ1.ocx
InputPath=.\UniDebug\circ1.ocx
SOURCE=$(InputPath)

"$(OutDir)\regsvr32.trg"	 : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	<<tempfile.bat 
	@echo off 
	regsvr32 /s /c "$(TargetPath)" 
	echo regsvr32 exec. time > "$(OutDir)\regsvr32.trg" 
<< 
	

!ELSEIF  "$(CFG)" == "Circ1 - Win32 Unicode Release"

OUTDIR=.\UniRelease
INTDIR=.\UniRelease
# Begin Custom Macros
OutDir=.\.\UniRelease
# End Custom Macros

ALL : "$(OUTDIR)\circ1.ocx" ".\.\UniRelease\regsvr32.trg"


CLEAN :
	-@erase "$(INTDIR)\circ1.obj"
	-@erase "$(INTDIR)\circ1.pch"
	-@erase "$(INTDIR)\circ1.res"
	-@erase "$(INTDIR)\circ1.tlb"
	-@erase "$(INTDIR)\circ1ctl.obj"
	-@erase "$(INTDIR)\circ1ppg.obj"
	-@erase "$(INTDIR)\stdafx.obj"
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(OUTDIR)\circ1.exp"
	-@erase "$(OUTDIR)\circ1.lib"
	-@erase "$(OUTDIR)\circ1.ocx"
	-@erase ".\.\UniRelease\regsvr32.trg"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP_PROJ=/nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_UNICODE" /Fp"$(INTDIR)\circ1.pch" /Yu"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 
MTL_PROJ=/nologo /D "NDEBUG" /mktyplib203 /win32 
RSC_PROJ=/l 0x409 /fo"$(INTDIR)\circ1.res" /d "NDEBUG" /d "_AFXDLL" 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\circ1.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
LINK32_FLAGS=/nologo /subsystem:windows /dll /incremental:no /pdb:"$(OUTDIR)\circ1.pdb" /machine:I386 /def:".\circ1.def" /out:"$(OUTDIR)\circ1.ocx" /implib:"$(OUTDIR)\circ1.lib" 
DEF_FILE= \
	".\circ1.def"
LINK32_OBJS= \
	"$(INTDIR)\circ1.obj" \
	"$(INTDIR)\circ1ctl.obj" \
	"$(INTDIR)\circ1ppg.obj" \
	"$(INTDIR)\stdafx.obj" \
	"$(INTDIR)\circ1.res"

"$(OUTDIR)\circ1.ocx" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

OutDir=.\.\UniRelease
TargetPath=.\UniRelease\circ1.ocx
InputPath=.\UniRelease\circ1.ocx
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
!IF EXISTS("circ1.dep")
!INCLUDE "circ1.dep"
!ELSE 
!MESSAGE Warning: cannot find "circ1.dep"
!ENDIF 
!ENDIF 


!IF "$(CFG)" == "Circ1 - Win32 Release" || "$(CFG)" == "Circ1 - Win32 Debug" || "$(CFG)" == "Circ1 - Win32 Unicode Debug" || "$(CFG)" == "Circ1 - Win32 Unicode Release"
SOURCE=.\circ1.cpp

"$(INTDIR)\circ1.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\circ1.pch"


SOURCE=.\circ1.odl

!IF  "$(CFG)" == "Circ1 - Win32 Release"

MTL_SWITCHES=/nologo /D "NDEBUG" /tlb "$(OUTDIR)\circ1.tlb" /mktyplib203 /win32 

"$(OUTDIR)\circ1.tlb" : $(SOURCE) "$(OUTDIR)"
	$(MTL) @<<
  $(MTL_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "Circ1 - Win32 Debug"

MTL_SWITCHES=/nologo /D "_DEBUG" /tlb "$(OUTDIR)\circ1.tlb" /mktyplib203 /win32 

"$(OUTDIR)\circ1.tlb" : $(SOURCE) "$(OUTDIR)"
	$(MTL) @<<
  $(MTL_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "Circ1 - Win32 Unicode Debug"

MTL_SWITCHES=/nologo /D "_DEBUG" /tlb "$(OUTDIR)\circ1.tlb" /mktyplib203 /win32 

"$(OUTDIR)\circ1.tlb" : $(SOURCE) "$(OUTDIR)"
	$(MTL) @<<
  $(MTL_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "Circ1 - Win32 Unicode Release"

MTL_SWITCHES=/nologo /D "NDEBUG" /tlb "$(OUTDIR)\circ1.tlb" /mktyplib203 /win32 

"$(OUTDIR)\circ1.tlb" : $(SOURCE) "$(OUTDIR)"
	$(MTL) @<<
  $(MTL_SWITCHES) $(SOURCE)
<<


!ENDIF 

SOURCE=.\circ1.rc

!IF  "$(CFG)" == "Circ1 - Win32 Release"


"$(INTDIR)\circ1.res" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\circ1.tlb"
	$(RSC) /l 0x409 /fo"$(INTDIR)\circ1.res" /i ".\Release" /d "NDEBUG" /d "_AFXDLL" $(SOURCE)


!ELSEIF  "$(CFG)" == "Circ1 - Win32 Debug"


"$(INTDIR)\circ1.res" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\circ1.tlb"
	$(RSC) /l 0x409 /fo"$(INTDIR)\circ1.res" /i ".\Debug" /d "_DEBUG" /d "_AFXDLL" $(SOURCE)


!ELSEIF  "$(CFG)" == "Circ1 - Win32 Unicode Debug"


"$(INTDIR)\circ1.res" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\circ1.tlb"
	$(RSC) /l 0x409 /fo"$(INTDIR)\circ1.res" /i ".\UniDebug" /d "_DEBUG" /d "_AFXDLL" $(SOURCE)


!ELSEIF  "$(CFG)" == "Circ1 - Win32 Unicode Release"


"$(INTDIR)\circ1.res" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\circ1.tlb"
	$(RSC) /l 0x409 /fo"$(INTDIR)\circ1.res" /i ".\UniRelease" /d "NDEBUG" /d "_AFXDLL" $(SOURCE)


!ENDIF 

SOURCE=.\circ1ctl.cpp

"$(INTDIR)\circ1ctl.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\circ1.pch"


SOURCE=.\circ1ppg.cpp

"$(INTDIR)\circ1ppg.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\circ1.pch"


SOURCE=.\stdafx.cpp

!IF  "$(CFG)" == "Circ1 - Win32 Release"

CPP_SWITCHES=/nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /Fp"$(INTDIR)\circ1.pch" /Yc"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 

"$(INTDIR)\stdafx.obj"	"$(INTDIR)\circ1.pch" : $(SOURCE) "$(INTDIR)"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "Circ1 - Win32 Debug"

CPP_SWITCHES=/nologo /MDd /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /Fp"$(INTDIR)\circ1.pch" /Yc"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 

"$(INTDIR)\stdafx.obj"	"$(INTDIR)\circ1.pch" : $(SOURCE) "$(INTDIR)"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "Circ1 - Win32 Unicode Debug"

CPP_SWITCHES=/nologo /MDd /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_UNICODE" /Fp"$(INTDIR)\circ1.pch" /Yc"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 

"$(INTDIR)\stdafx.obj"	"$(INTDIR)\circ1.pch" : $(SOURCE) "$(INTDIR)"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "Circ1 - Win32 Unicode Release"

CPP_SWITCHES=/nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_UNICODE" /Fp"$(INTDIR)\circ1.pch" /Yc"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 

"$(INTDIR)\stdafx.obj"	"$(INTDIR)\circ1.pch" : $(SOURCE) "$(INTDIR)"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ENDIF 


!ENDIF 

