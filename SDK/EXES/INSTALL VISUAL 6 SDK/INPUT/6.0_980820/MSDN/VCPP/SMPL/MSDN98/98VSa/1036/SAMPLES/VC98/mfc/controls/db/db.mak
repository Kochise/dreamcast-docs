# Microsoft Developer Studio Generated NMAKE File, Based on db.dsp
!IF "$(CFG)" == ""
CFG=DB - Win32 Release
!MESSAGE No configuration specified. Defaulting to DB - Win32 Release.
!ENDIF 

!IF "$(CFG)" != "DB - Win32 Release" && "$(CFG)" != "DB - Win32 Debug"
!MESSAGE Invalid configuration "$(CFG)" specified.
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "db.mak" CFG="DB - Win32 Release"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "DB - Win32 Release" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE "DB - Win32 Debug" (based on "Win32 (x86) Dynamic-Link Library")
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

!IF  "$(CFG)" == "DB - Win32 Release"

OUTDIR=.\Release
INTDIR=.\Release
# Begin Custom Macros
OutDir=.\.\Release
# End Custom Macros

ALL : "$(OUTDIR)\db.ocx" ".\.\Release\regsvr32.trg"


CLEAN :
	-@erase "$(INTDIR)\db.obj"
	-@erase "$(INTDIR)\db.pch"
	-@erase "$(INTDIR)\db.res"
	-@erase "$(INTDIR)\db.tlb"
	-@erase "$(INTDIR)\dbctl.obj"
	-@erase "$(INTDIR)\dbppg.obj"
	-@erase "$(INTDIR)\stdafx.obj"
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(OUTDIR)\db.exp"
	-@erase "$(OUTDIR)\db.lib"
	-@erase "$(OUTDIR)\db.ocx"
	-@erase ".\.\Release\regsvr32.trg"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP_PROJ=/nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /Fp"$(INTDIR)\db.pch" /Yu"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 
MTL_PROJ=/nologo /D "NDEBUG" /mktyplib203 /win32 
RSC_PROJ=/l 0x409 /fo"$(INTDIR)\db.res" /d "NDEBUG" /d "_AFXDLL" 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\db.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
LINK32_FLAGS=/nologo /subsystem:windows /dll /incremental:no /pdb:"$(OUTDIR)\db.pdb" /machine:I386 /def:".\db.def" /out:"$(OUTDIR)\db.ocx" /implib:"$(OUTDIR)\db.lib" 
DEF_FILE= \
	".\db.def"
LINK32_OBJS= \
	"$(INTDIR)\db.obj" \
	"$(INTDIR)\dbctl.obj" \
	"$(INTDIR)\dbppg.obj" \
	"$(INTDIR)\stdafx.obj" \
	"$(INTDIR)\db.res"

"$(OUTDIR)\db.ocx" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

OutDir=.\.\Release
TargetPath=.\Release\db.ocx
InputPath=.\Release\db.ocx
SOURCE=$(InputPath)

"$(OutDir)\regsvr32.trg"	 : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	<<tempfile.bat 
	@echo off 
	regsvr32 /s /c "$(TargetPath)" 
	echo regsvr32 exec. time > "$(OutDir)\regsvr32.trg" 
<< 
	

!ELSEIF  "$(CFG)" == "DB - Win32 Debug"

OUTDIR=.\Debug
INTDIR=.\Debug
# Begin Custom Macros
OutDir=.\.\Debug
# End Custom Macros

ALL : "$(OUTDIR)\db.ocx" ".\.\Debug\regsvr32.trg"


CLEAN :
	-@erase "$(INTDIR)\db.obj"
	-@erase "$(INTDIR)\db.pch"
	-@erase "$(INTDIR)\db.res"
	-@erase "$(INTDIR)\db.tlb"
	-@erase "$(INTDIR)\dbctl.obj"
	-@erase "$(INTDIR)\dbppg.obj"
	-@erase "$(INTDIR)\stdafx.obj"
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(INTDIR)\vc60.pdb"
	-@erase "$(OUTDIR)\db.exp"
	-@erase "$(OUTDIR)\db.ilk"
	-@erase "$(OUTDIR)\db.lib"
	-@erase "$(OUTDIR)\db.ocx"
	-@erase "$(OUTDIR)\db.pdb"
	-@erase ".\.\Debug\regsvr32.trg"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP_PROJ=/nologo /MDd /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /Fp"$(INTDIR)\db.pch" /Yu"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 
MTL_PROJ=/nologo /D "_DEBUG" /mktyplib203 /win32 
RSC_PROJ=/l 0x409 /fo"$(INTDIR)\db.res" /d "_DEBUG" /d "_AFXDLL" 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\db.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
LINK32_FLAGS=/nologo /subsystem:windows /dll /incremental:yes /pdb:"$(OUTDIR)\db.pdb" /debug /machine:I386 /def:".\db.def" /out:"$(OUTDIR)\db.ocx" /implib:"$(OUTDIR)\db.lib" 
DEF_FILE= \
	".\db.def"
LINK32_OBJS= \
	"$(INTDIR)\db.obj" \
	"$(INTDIR)\dbctl.obj" \
	"$(INTDIR)\dbppg.obj" \
	"$(INTDIR)\stdafx.obj" \
	"$(INTDIR)\db.res"

"$(OUTDIR)\db.ocx" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

OutDir=.\.\Debug
TargetPath=.\Debug\db.ocx
InputPath=.\Debug\db.ocx
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
!IF EXISTS("db.dep")
!INCLUDE "db.dep"
!ELSE 
!MESSAGE Warning: cannot find "db.dep"
!ENDIF 
!ENDIF 


!IF "$(CFG)" == "DB - Win32 Release" || "$(CFG)" == "DB - Win32 Debug"
SOURCE=.\db.cpp

"$(INTDIR)\db.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\db.pch"


SOURCE=.\db.odl

!IF  "$(CFG)" == "DB - Win32 Release"

MTL_SWITCHES=/nologo /D "NDEBUG" /tlb "$(OUTDIR)\db.tlb" /mktyplib203 /win32 

"$(OUTDIR)\db.tlb" : $(SOURCE) "$(OUTDIR)"
	$(MTL) @<<
  $(MTL_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "DB - Win32 Debug"

MTL_SWITCHES=/nologo /D "_DEBUG" /tlb "$(OUTDIR)\db.tlb" /mktyplib203 /win32 

"$(OUTDIR)\db.tlb" : $(SOURCE) "$(OUTDIR)"
	$(MTL) @<<
  $(MTL_SWITCHES) $(SOURCE)
<<


!ENDIF 

SOURCE=.\db.rc

!IF  "$(CFG)" == "DB - Win32 Release"


"$(INTDIR)\db.res" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\db.tlb"
	$(RSC) /l 0x409 /fo"$(INTDIR)\db.res" /i ".\Release" /d "NDEBUG" /d "_AFXDLL" $(SOURCE)


!ELSEIF  "$(CFG)" == "DB - Win32 Debug"


"$(INTDIR)\db.res" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\db.tlb"
	$(RSC) /l 0x409 /fo"$(INTDIR)\db.res" /i ".\Debug" /d "_DEBUG" /d "_AFXDLL" $(SOURCE)


!ENDIF 

SOURCE=.\dbctl.cpp

"$(INTDIR)\dbctl.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\db.pch"


SOURCE=.\dbppg.cpp

"$(INTDIR)\dbppg.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\db.pch"


SOURCE=.\stdafx.cpp

!IF  "$(CFG)" == "DB - Win32 Release"

CPP_SWITCHES=/nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /Fp"$(INTDIR)\db.pch" /Yc"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 

"$(INTDIR)\stdafx.obj"	"$(INTDIR)\db.pch" : $(SOURCE) "$(INTDIR)"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "DB - Win32 Debug"

CPP_SWITCHES=/nologo /MDd /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /Fp"$(INTDIR)\db.pch" /Yc"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 

"$(INTDIR)\stdafx.obj"	"$(INTDIR)\db.pch" : $(SOURCE) "$(INTDIR)"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ENDIF 


!ENDIF 

