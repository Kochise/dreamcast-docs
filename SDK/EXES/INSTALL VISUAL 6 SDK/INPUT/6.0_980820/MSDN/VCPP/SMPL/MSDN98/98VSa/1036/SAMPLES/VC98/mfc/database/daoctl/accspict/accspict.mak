# Microsoft Developer Studio Generated NMAKE File, Based on accspict.dsp
!IF "$(CFG)" == ""
CFG=AccsPict - Win32 Release
!MESSAGE No configuration specified. Defaulting to AccsPict - Win32 Release.
!ENDIF 

!IF "$(CFG)" != "AccsPict - Win32 Release" && "$(CFG)" != "AccsPict - Win32 Debug" && "$(CFG)" != "AccsPict - Win32 Debug Unicode" && "$(CFG)" != "AccsPict - Win32 Release Unicode"
!MESSAGE Invalid configuration "$(CFG)" specified.
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "accspict.mak" CFG="AccsPict - Win32 Release"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "AccsPict - Win32 Release" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE "AccsPict - Win32 Debug" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE "AccsPict - Win32 Debug Unicode" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE "AccsPict - Win32 Release Unicode" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE 
!ERROR An invalid configuration is specified.
!ENDIF 

!IF "$(OS)" == "Windows_NT"
NULL=
!ELSE 
NULL=nul
!ENDIF 

!IF  "$(CFG)" == "AccsPict - Win32 Release"

OUTDIR=.\Release
INTDIR=.\Release
# Begin Custom Macros
OutDir=.\Release
# End Custom Macros

ALL : "$(OUTDIR)\accspict.ocx" "$(OUTDIR)\accspict.tlb" ".\Release\regsvr32.trg"


CLEAN :
	-@erase "$(INTDIR)\AccsCtl.obj"
	-@erase "$(INTDIR)\accspict.obj"
	-@erase "$(INTDIR)\accspict.pch"
	-@erase "$(INTDIR)\accspict.res"
	-@erase "$(INTDIR)\accspict.tlb"
	-@erase "$(INTDIR)\AccsPpg.obj"
	-@erase "$(INTDIR)\StdAfx.obj"
	-@erase "$(INTDIR)\strmdib.obj"
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(INTDIR)\vc60.pdb"
	-@erase "$(OUTDIR)\accspict.exp"
	-@erase "$(OUTDIR)\accspict.lib"
	-@erase "$(OUTDIR)\accspict.ocx"
	-@erase ".\Release\regsvr32.trg"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP=cl.exe
CPP_PROJ=/nologo /MD /W3 /GX /ZI /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /Fp"$(INTDIR)\accspict.pch" /Yu"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 

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
RSC_PROJ=/l 0x409 /fo"$(INTDIR)\accspict.res" /d "NDEBUG" /d "_AFXDLL" 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\accspict.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
LINK32_FLAGS=/nologo /subsystem:windows /dll /incremental:no /pdb:"$(OUTDIR)\accspict.pdb" /machine:I386 /def:".\AccsPict.def" /out:"$(OUTDIR)\accspict.ocx" /implib:"$(OUTDIR)\accspict.lib" 
DEF_FILE= \
	".\AccsPict.def"
LINK32_OBJS= \
	"$(INTDIR)\AccsCtl.obj" \
	"$(INTDIR)\accspict.obj" \
	"$(INTDIR)\AccsPpg.obj" \
	"$(INTDIR)\StdAfx.obj" \
	"$(INTDIR)\strmdib.obj" \
	"$(INTDIR)\accspict.res"

"$(OUTDIR)\accspict.ocx" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

OutDir=.\Release
TargetPath=.\Release\accspict.ocx
InputPath=.\Release\accspict.ocx
SOURCE="$(InputPath)"

"$(OUTDIR)\regsvr32.trg" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	<<tempfile.bat 
	@echo off 
	regsvr32 /s /c "$(TargetPath)" 
	echo regsvr32 exec. time > "$(OutDir)\regsvr32.trg" 
<< 
	

!ELSEIF  "$(CFG)" == "AccsPict - Win32 Debug"

OUTDIR=.\Debug
INTDIR=.\Debug
# Begin Custom Macros
OutDir=.\Debug
# End Custom Macros

ALL : "$(OUTDIR)\accspict.ocx" ".\Debug\regsvr32.trg"


CLEAN :
	-@erase "$(INTDIR)\AccsCtl.obj"
	-@erase "$(INTDIR)\accspict.obj"
	-@erase "$(INTDIR)\accspict.pch"
	-@erase "$(INTDIR)\accspict.res"
	-@erase "$(INTDIR)\accspict.tlb"
	-@erase "$(INTDIR)\AccsPpg.obj"
	-@erase "$(INTDIR)\StdAfx.obj"
	-@erase "$(INTDIR)\strmdib.obj"
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(INTDIR)\vc60.pdb"
	-@erase "$(OUTDIR)\accspict.exp"
	-@erase "$(OUTDIR)\accspict.ilk"
	-@erase "$(OUTDIR)\accspict.lib"
	-@erase "$(OUTDIR)\accspict.ocx"
	-@erase "$(OUTDIR)\accspict.pdb"
	-@erase ".\Debug\regsvr32.trg"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP=cl.exe
CPP_PROJ=/nologo /MDd /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /Fp"$(INTDIR)\accspict.pch" /Yu"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 

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
RSC_PROJ=/l 0x409 /fo"$(INTDIR)\accspict.res" /d "_DEBUG" /d "_AFXDLL" 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\accspict.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
LINK32_FLAGS=/nologo /subsystem:windows /dll /incremental:yes /pdb:"$(OUTDIR)\accspict.pdb" /debug /machine:I386 /def:".\AccsPict.def" /out:"$(OUTDIR)\accspict.ocx" /implib:"$(OUTDIR)\accspict.lib" 
DEF_FILE= \
	".\AccsPict.def"
LINK32_OBJS= \
	"$(INTDIR)\AccsCtl.obj" \
	"$(INTDIR)\accspict.obj" \
	"$(INTDIR)\AccsPpg.obj" \
	"$(INTDIR)\StdAfx.obj" \
	"$(INTDIR)\strmdib.obj" \
	"$(INTDIR)\accspict.res"

"$(OUTDIR)\accspict.ocx" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

OutDir=.\Debug
TargetPath=.\Debug\accspict.ocx
InputPath=.\Debug\accspict.ocx
SOURCE="$(InputPath)"

"$(OUTDIR)\regsvr32.trg" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	<<tempfile.bat 
	@echo off 
	regsvr32 /s /c "$(TargetPath)" 
	echo regsvr32 exec. time > "$(OutDir)\regsvr32.trg" 
<< 
	

!ELSEIF  "$(CFG)" == "AccsPict - Win32 Debug Unicode"

OUTDIR=.\DebugU
INTDIR=.\DebugU
# Begin Custom Macros
OutDir=.\DebugU
# End Custom Macros

ALL : "$(OUTDIR)\accspict.ocx" "$(OUTDIR)\accspict.tlb" ".\DebugU\regsvr32.trg"


CLEAN :
	-@erase "$(INTDIR)\AccsCtl.obj"
	-@erase "$(INTDIR)\accspict.obj"
	-@erase "$(INTDIR)\accspict.pch"
	-@erase "$(INTDIR)\accspict.res"
	-@erase "$(INTDIR)\accspict.tlb"
	-@erase "$(INTDIR)\AccsPpg.obj"
	-@erase "$(INTDIR)\StdAfx.obj"
	-@erase "$(INTDIR)\strmdib.obj"
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(INTDIR)\vc60.pdb"
	-@erase "$(OUTDIR)\accspict.exp"
	-@erase "$(OUTDIR)\accspict.ilk"
	-@erase "$(OUTDIR)\accspict.lib"
	-@erase "$(OUTDIR)\accspict.ocx"
	-@erase "$(OUTDIR)\accspict.pdb"
	-@erase ".\DebugU\regsvr32.trg"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP=cl.exe
CPP_PROJ=/nologo /MDd /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_UNICODE" /Fp"$(INTDIR)\accspict.pch" /Yu"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 

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
RSC_PROJ=/l 0x409 /fo"$(INTDIR)\accspict.res" /d "_DEBUG" /d "_AFXDLL" 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\accspict.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
LINK32_FLAGS=/nologo /subsystem:windows /dll /incremental:yes /pdb:"$(OUTDIR)\accspict.pdb" /debug /machine:I386 /def:".\AccsPict.def" /out:"$(OUTDIR)\accspict.ocx" /implib:"$(OUTDIR)\accspict.lib" 
DEF_FILE= \
	".\AccsPict.def"
LINK32_OBJS= \
	"$(INTDIR)\AccsCtl.obj" \
	"$(INTDIR)\accspict.obj" \
	"$(INTDIR)\AccsPpg.obj" \
	"$(INTDIR)\StdAfx.obj" \
	"$(INTDIR)\strmdib.obj" \
	"$(INTDIR)\accspict.res"

"$(OUTDIR)\accspict.ocx" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

OutDir=.\DebugU
TargetPath=.\DebugU\accspict.ocx
InputPath=.\DebugU\accspict.ocx
SOURCE="$(InputPath)"

"$(OUTDIR)\regsvr32.trg" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	<<tempfile.bat 
	@echo off 
	regsvr32 /s /c "$(TargetPath)" 
	echo regsvr32 exec. time > "$(OutDir)\regsvr32.trg" 
<< 
	

!ELSEIF  "$(CFG)" == "AccsPict - Win32 Release Unicode"

OUTDIR=.\ReleaseU
INTDIR=.\ReleaseU
# Begin Custom Macros
OutDir=.\ReleaseU
# End Custom Macros

ALL : "$(OUTDIR)\accspict.ocx" "$(OUTDIR)\accspict.tlb" ".\ReleaseU\regsvr32.trg"


CLEAN :
	-@erase "$(INTDIR)\AccsCtl.obj"
	-@erase "$(INTDIR)\accspict.obj"
	-@erase "$(INTDIR)\accspict.pch"
	-@erase "$(INTDIR)\accspict.res"
	-@erase "$(INTDIR)\accspict.tlb"
	-@erase "$(INTDIR)\AccsPpg.obj"
	-@erase "$(INTDIR)\StdAfx.obj"
	-@erase "$(INTDIR)\strmdib.obj"
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(OUTDIR)\accspict.exp"
	-@erase "$(OUTDIR)\accspict.lib"
	-@erase "$(OUTDIR)\accspict.ocx"
	-@erase ".\ReleaseU\regsvr32.trg"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP=cl.exe
CPP_PROJ=/nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_UNICODE" /Fp"$(INTDIR)\accspict.pch" /Yu"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 

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
RSC_PROJ=/l 0x409 /fo"$(INTDIR)\accspict.res" /d "NDEBUG" /d "_AFXDLL" 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\accspict.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
LINK32_FLAGS=/nologo /subsystem:windows /dll /incremental:no /pdb:"$(OUTDIR)\accspict.pdb" /machine:I386 /def:".\AccsPict.def" /out:"$(OUTDIR)\accspict.ocx" /implib:"$(OUTDIR)\accspict.lib" 
DEF_FILE= \
	".\AccsPict.def"
LINK32_OBJS= \
	"$(INTDIR)\AccsCtl.obj" \
	"$(INTDIR)\accspict.obj" \
	"$(INTDIR)\AccsPpg.obj" \
	"$(INTDIR)\StdAfx.obj" \
	"$(INTDIR)\strmdib.obj" \
	"$(INTDIR)\accspict.res"

"$(OUTDIR)\accspict.ocx" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

OutDir=.\ReleaseU
TargetPath=.\ReleaseU\accspict.ocx
InputPath=.\ReleaseU\accspict.ocx
SOURCE="$(InputPath)"

"$(OUTDIR)\regsvr32.trg" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	<<tempfile.bat 
	@echo off 
	regsvr32 /s /c "$(TargetPath)" 
	echo regsvr32 exec. time > "$(OutDir)\regsvr32.trg" 
<< 
	

!ENDIF 


!IF "$(NO_EXTERNAL_DEPS)" != "1"
!IF EXISTS("accspict.dep")
!INCLUDE "accspict.dep"
!ELSE 
!MESSAGE Warning: cannot find "accspict.dep"
!ENDIF 
!ENDIF 


!IF "$(CFG)" == "AccsPict - Win32 Release" || "$(CFG)" == "AccsPict - Win32 Debug" || "$(CFG)" == "AccsPict - Win32 Debug Unicode" || "$(CFG)" == "AccsPict - Win32 Release Unicode"
SOURCE=.\AccsCtl.cpp

"$(INTDIR)\AccsCtl.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\accspict.pch"


SOURCE=.\accspict.cpp

"$(INTDIR)\accspict.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\accspict.pch"


SOURCE=.\accspict.odl

!IF  "$(CFG)" == "AccsPict - Win32 Release"

MTL_SWITCHES=/nologo /D "NDEBUG" /tlb "$(OUTDIR)\accspict.tlb" /mktyplib203 /win32 

"$(OUTDIR)\accspict.tlb" : $(SOURCE) "$(OUTDIR)"
	$(MTL) @<<
  $(MTL_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "AccsPict - Win32 Debug"

MTL_SWITCHES=/nologo /D "_DEBUG" /tlb "$(OUTDIR)\accspict.tlb" /mktyplib203 /win32 

"$(OUTDIR)\accspict.tlb" : $(SOURCE) "$(OUTDIR)"
	$(MTL) @<<
  $(MTL_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "AccsPict - Win32 Debug Unicode"

MTL_SWITCHES=/nologo /D "_DEBUG" /tlb "$(OUTDIR)\accspict.tlb" /mktyplib203 /win32 

"$(OUTDIR)\accspict.tlb" : $(SOURCE) "$(OUTDIR)"
	$(MTL) @<<
  $(MTL_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "AccsPict - Win32 Release Unicode"

MTL_SWITCHES=/nologo /D "NDEBUG" /tlb "$(OUTDIR)\accspict.tlb" /mktyplib203 /win32 

"$(OUTDIR)\accspict.tlb" : $(SOURCE) "$(OUTDIR)"
	$(MTL) @<<
  $(MTL_SWITCHES) $(SOURCE)
<<


!ENDIF 

SOURCE=.\accspict.rc

!IF  "$(CFG)" == "AccsPict - Win32 Release"


"$(INTDIR)\accspict.res" : $(SOURCE) "$(INTDIR)"
	$(RSC) /l 0x409 /fo"$(INTDIR)\accspict.res" /i ".\Release" /d "NDEBUG" /d "_AFXDLL" $(SOURCE)


!ELSEIF  "$(CFG)" == "AccsPict - Win32 Debug"


"$(INTDIR)\accspict.res" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\accspict.tlb"
	$(RSC) /l 0x409 /fo"$(INTDIR)\accspict.res" /i ".\Debug" /d "_DEBUG" /d "_AFXDLL" $(SOURCE)


!ELSEIF  "$(CFG)" == "AccsPict - Win32 Debug Unicode"


"$(INTDIR)\accspict.res" : $(SOURCE) "$(INTDIR)"
	$(RSC) /l 0x409 /fo"$(INTDIR)\accspict.res" /i ".\DebugU" /d "_DEBUG" /d "_AFXDLL" $(SOURCE)


!ELSEIF  "$(CFG)" == "AccsPict - Win32 Release Unicode"


"$(INTDIR)\accspict.res" : $(SOURCE) "$(INTDIR)"
	$(RSC) /l 0x409 /fo"$(INTDIR)\accspict.res" /i ".\ReleaseU" /d "NDEBUG" /d "_AFXDLL" $(SOURCE)


!ENDIF 

SOURCE=.\AccsPpg.cpp

"$(INTDIR)\AccsPpg.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\accspict.pch"


SOURCE=.\StdAfx.cpp

!IF  "$(CFG)" == "AccsPict - Win32 Release"

CPP_SWITCHES=/nologo /MD /W3 /GX /ZI /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /Fp"$(INTDIR)\accspict.pch" /Yc"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 

"$(INTDIR)\StdAfx.obj"	"$(INTDIR)\accspict.pch" : $(SOURCE) "$(INTDIR)"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "AccsPict - Win32 Debug"

CPP_SWITCHES=/nologo /MDd /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /Fp"$(INTDIR)\accspict.pch" /Yc"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 

"$(INTDIR)\StdAfx.obj"	"$(INTDIR)\accspict.pch" : $(SOURCE) "$(INTDIR)"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "AccsPict - Win32 Debug Unicode"

CPP_SWITCHES=/nologo /MDd /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_UNICODE" /Fp"$(INTDIR)\accspict.pch" /Yc"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 

"$(INTDIR)\StdAfx.obj"	"$(INTDIR)\accspict.pch" : $(SOURCE) "$(INTDIR)"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "AccsPict - Win32 Release Unicode"

CPP_SWITCHES=/nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_UNICODE" /Fp"$(INTDIR)\accspict.pch" /Yc"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 

"$(INTDIR)\StdAfx.obj"	"$(INTDIR)\accspict.pch" : $(SOURCE) "$(INTDIR)"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ENDIF 

SOURCE=.\strmdib.cpp

"$(INTDIR)\strmdib.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\accspict.pch"



!ENDIF 

