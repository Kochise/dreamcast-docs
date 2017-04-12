# Microsoft Developer Studio Generated NMAKE File, Based on Atl.dsp
!IF "$(CFG)" == ""
CFG=atl - Win32 Debug
!MESSAGE No configuration specified. Defaulting to atl - Win32 Debug.
!ENDIF 

!IF "$(CFG)" != "atl - Win32 Debug" && "$(CFG)" != "atl - Win32 Unicode Debug" && "$(CFG)" != "atl - Win32 Release" && "$(CFG)" != "atl - Win32 Unicode Release"
!MESSAGE Invalid configuration "$(CFG)" specified.
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "Atl.mak" CFG="atl - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "atl - Win32 Debug" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE "atl - Win32 Unicode Debug" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE "atl - Win32 Release" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE "atl - Win32 Unicode Release" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE 
!ERROR An invalid configuration is specified.
!ENDIF 

!IF "$(OS)" == "Windows_NT"
NULL=
!ELSE 
NULL=nul
!ENDIF 

!IF  "$(CFG)" == "atl - Win32 Debug"

OUTDIR=.\Debug
INTDIR=.\Debug
# Begin Custom Macros
OutDir=.\.\Debug
# End Custom Macros

ALL : "atl_i.c" "atl.tlb" "atl.h" "$(OUTDIR)\Atl.dll" ".\.\Debug\regsvr32.trg"


CLEAN :
	-@erase "$(INTDIR)\atl.obj"
	-@erase "$(INTDIR)\Atl.pch"
	-@erase "$(INTDIR)\atl.res"
	-@erase "$(INTDIR)\RegObj.obj"
	-@erase "$(INTDIR)\StdAfx.obj"
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(INTDIR)\vc60.pdb"
	-@erase "$(OUTDIR)\Atl.dll"
	-@erase "$(OUTDIR)\Atl.exp"
	-@erase "$(OUTDIR)\Atl.ilk"
	-@erase "$(OUTDIR)\Atl.lib"
	-@erase "$(OUTDIR)\Atl.pdb"
	-@erase ".\.\Debug\regsvr32.trg"
	-@erase "atl.h"
	-@erase "atl.tlb"
	-@erase "atl_i.c"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP=cl.exe
CPP_PROJ=/nologo /MDd /W3 /Gm /Od /I "." /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_WINDLL" /D "_MBCS" /Fp"$(INTDIR)\Atl.pch" /Yu"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c

!if "$(_VCBUILD)" == "1"
CPP_PROJ=$(CPP_PROJ) /Zi
!else
CPP_PROJ=$(CPP_PROJ) /ZI
!endif

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
RSC_PROJ=/l 0x409 /fo"$(INTDIR)\atl.res" /d "_DEBUG" 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\Atl.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
!if "$(PROCESSOR_ARCHITECTURE)" == "ALPHA"
LINK32_FLAGS=/nologo /base:"0x5f3e0000" /version:2.0 /subsystem:windows /dll /incremental:yes /pdb:"$(OUTDIR)\Atl.pdb" /debug /machine:ALPHA /def:".\atl.def" /out:"$(OUTDIR)\Atl.dll" /implib:"$(OUTDIR)\Atl.lib" 
!else
LINK32_FLAGS=/nologo /base:"0x5f3e0000" /version:2.0 /subsystem:windows /dll /incremental:yes /pdb:"$(OUTDIR)\Atl.pdb" /debug /machine:I386 /def:".\atl.def" /out:"$(OUTDIR)\Atl.dll" /implib:"$(OUTDIR)\Atl.lib" 
!endif
DEF_FILE= \
	".\atl.def"
LINK32_OBJS= \
	"$(INTDIR)\atl.obj" \
	"$(INTDIR)\RegObj.obj" \
	"$(INTDIR)\StdAfx.obj" \
	"$(INTDIR)\atl.res"

"$(OUTDIR)\Atl.dll" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

OutDir=.\.\Debug
TargetPath=.\Debug\Atl.dll
InputPath=.\Debug\Atl.dll
SOURCE=$(InputPath)

"$(OutDir)\regsvr32.trg"	 : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	<<tempfile.bat 
	@echo off 
	echo regsvr32 /s /c "$(TargetPath)" 
	echo regsvr32 exec. time > "$(OutDir)\regsvr32.trg" 
<< 
	

!ELSEIF  "$(CFG)" == "atl - Win32 Unicode Debug"

OUTDIR=.\DebugU
INTDIR=.\DebugU
# Begin Custom Macros
OutDir=.\.\DebugU
# End Custom Macros

ALL : "atl_i.c" "atl.tlb" "atl.h" "$(OUTDIR)\Atl.dll" ".\.\DebugU\regsvr32.trg"


CLEAN :
	-@erase "$(INTDIR)\atl.obj"
	-@erase "$(INTDIR)\Atl.pch"
	-@erase "$(INTDIR)\atl.res"
	-@erase "$(INTDIR)\RegObj.obj"
	-@erase "$(INTDIR)\StdAfx.obj"
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(INTDIR)\vc60.pdb"
	-@erase "$(OUTDIR)\Atl.dll"
	-@erase "$(OUTDIR)\Atl.exp"
	-@erase "$(OUTDIR)\Atl.ilk"
	-@erase "$(OUTDIR)\Atl.lib"
	-@erase "$(OUTDIR)\Atl.pdb"
	-@erase ".\.\DebugU\regsvr32.trg"
	-@erase "atl.h"
	-@erase "atl.tlb"
	-@erase "atl_i.c"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP=cl.exe
CPP_PROJ=/nologo /MDd /W3 /Gm /Od /D "_DEBUG" /D "WIN32" /D "_WINDOWS" /D "_WINDLL" /D "_UNICODE" /Fp"$(INTDIR)\Atl.pch" /Yu"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c

!if "$(_VCBUILD)" == "1"
CPP_PROJ=$(CPP_PROJ) /Zi
!else
CPP_PROJ=$(CPP_PROJ) /ZI
!endif

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
RSC_PROJ=/l 0x409 /fo"$(INTDIR)\atl.res" /d "_DEBUG" /d "_UNICODE" 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\Atl.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
!if "$(PROCESSOR_ARCHITECTURE)" == "ALPHA"
LINK32_FLAGS=/nologo /base:"0x5f3e0000" /version:2.0 /subsystem:windows /dll /incremental:yes /pdb:"$(OUTDIR)\Atl.pdb" /debug /machine:ALPHA /def:".\atl.def" /out:"$(OUTDIR)\Atl.dll" /implib:"$(OUTDIR)\Atl.lib" 
!else
LINK32_FLAGS=/nologo /base:"0x5f3e0000" /version:2.0 /subsystem:windows /dll /incremental:yes /pdb:"$(OUTDIR)\Atl.pdb" /debug /machine:I386 /def:".\atl.def" /out:"$(OUTDIR)\Atl.dll" /implib:"$(OUTDIR)\Atl.lib" 
!endif
DEF_FILE= \
	".\atl.def"
LINK32_OBJS= \
	"$(INTDIR)\atl.obj" \
	"$(INTDIR)\RegObj.obj" \
	"$(INTDIR)\StdAfx.obj" \
	"$(INTDIR)\atl.res"

"$(OUTDIR)\Atl.dll" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

OutDir=.\.\DebugU
TargetPath=.\DebugU\Atl.dll
InputPath=.\DebugU\Atl.dll
SOURCE=$(InputPath)

"$(OutDir)\regsvr32.trg"	 : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	<<tempfile.bat 
	@echo off 
	echo regsvr32 /s /c "$(TargetPath)" 
	echo regsvr32 exec. time > "$(OutDir)\regsvr32.trg" 
<< 
	

!ELSEIF  "$(CFG)" == "atl - Win32 Release"

OUTDIR=.\Release
INTDIR=.\Release
# Begin Custom Macros
OutDir=.\.\Release
# End Custom Macros

ALL : "atl_i.c" "atl.tlb" "atl.h" "$(OUTDIR)\Atl.dll" ".\.\Release\regsvr32.trg"


CLEAN :
	-@erase "$(INTDIR)\atl.obj"
	-@erase "$(INTDIR)\Atl.pch"
	-@erase "$(INTDIR)\atl.res"
	-@erase "$(INTDIR)\RegObj.obj"
	-@erase "$(INTDIR)\StdAfx.obj"
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(INTDIR)\vc60.pdb"
	-@erase "$(OUTDIR)\Atl.pdb"
	-@erase "$(OUTDIR)\Atl.dll"
	-@erase "$(OUTDIR)\Atl.exp"
	-@erase "$(OUTDIR)\Atl.lib"
	-@erase ".\.\Release\regsvr32.trg"
	-@erase "atl.h"
	-@erase "atl.tlb"
	-@erase "atl_i.c"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP=cl.exe
CPP_PROJ=/nologo /MT /W3 /Zi /O1 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_WINDLL" /D "_MBCS" /D "_ATL_MIN_CRT" /Fp"$(INTDIR)\Atl.pch" /Yu"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 

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
RSC_PROJ=/l 0x409 /fo"$(INTDIR)\atl.res" /d "NDEBUG" 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\Atl.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
!if "$(PROCESSOR_ARCHITECTURE)" == "ALPHA"
LINK32_FLAGS=delayimp.lib atldload.lib /nologo /base:"0x5f3e0000" /version:2.0 /entry:"DllMain" /subsystem:windows /dll /incremental:no /pdb:"$(OUTDIR)\Atl.pdb" /machine:ALPHA /def:".\atl.def" /out:"$(OUTDIR)\Atl.dll" /implib:"$(OUTDIR)\Atl.lib" /delayload:user32.dll /delayload:gdi32.dll /delayload:ole32.dll /delayload:oleaut32.dll /delayload:advapi32.dll /delayload:olepro32.dll 
!else
LINK32_FLAGS=delayimp.lib  atldload.lib /nologo /base:"0x5f3e0000" /version:2.0 /entry:"DllMain" /subsystem:windows /dll /incremental:no /pdb:"$(OUTDIR)\Atl.pdb" /debug /machine:I386 /def:".\atl.def" /out:"$(OUTDIR)\Atl.dll" /implib:"$(OUTDIR)\Atl.lib" /delayload:user32.dll /delayload:gdi32.dll /delayload:ole32.dll /delayload:oleaut32.dll /delayload:advapi32.dll /delayload:olepro32.dll 
!endif
DEF_FILE= \
	".\atl.def"
LINK32_OBJS= \
	"$(INTDIR)\atl.obj" \
	"$(INTDIR)\RegObj.obj" \
	"$(INTDIR)\StdAfx.obj" \
	"$(INTDIR)\atl.res"

"$(OUTDIR)\Atl.dll" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

OutDir=.\.\Release
TargetPath=.\Release\Atl.dll
InputPath=.\Release\Atl.dll
SOURCE=$(InputPath)

"$(OutDir)\regsvr32.trg"	 : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	<<tempfile.bat 
	@echo off 
	echo regsvr32 /s /c "$(TargetPath)" 
	echo regsvr32 exec. time > "$(OutDir)\regsvr32.trg" 
<< 
	

!ELSEIF  "$(CFG)" == "atl - Win32 Unicode Release"

OUTDIR=.\ReleaseU
INTDIR=.\ReleaseU
# Begin Custom Macros
OutDir=.\.\ReleaseU
# End Custom Macros

ALL : "atl_i.c" "atl.tlb" "atl.h" "$(OUTDIR)\Atl.dll" ".\.\ReleaseU\regsvr32.trg"


CLEAN :
	-@erase "$(INTDIR)\atl.obj"
	-@erase "$(INTDIR)\Atl.pch"
	-@erase "$(INTDIR)\atl.res"
	-@erase "$(INTDIR)\RegObj.obj"
	-@erase "$(INTDIR)\StdAfx.obj"
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(INTDIR)\vc60.pdb"
	-@erase "$(OUTDIR)\Atl.pdb"
	-@erase "$(OUTDIR)\Atl.dll"
	-@erase "$(OUTDIR)\Atl.exp"
	-@erase "$(OUTDIR)\Atl.lib"
	-@erase ".\.\ReleaseU\regsvr32.trg"
	-@erase "atl.h"
	-@erase "atl.tlb"
	-@erase "atl_i.c"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP=cl.exe
CPP_PROJ=/nologo /MT /W3 /Zi /O1 /D "NDEBUG" /D "WIN32" /D "_WINDOWS" /D "_WINDLL" /D "_UNICODE" /D "_ATL_MIN_CRT" /Fp"$(INTDIR)\Atl.pch" /Yu"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 

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
RSC_PROJ=/l 0x409 /fo"$(INTDIR)\atl.res" /d "NDEBUG" /d "_UNICODE" 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\Atl.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
!if "$(PROCESSOR_ARCHITECTURE)" == "ALPHA"
LINK32_FLAGS=delayimp.lib  atldload.lib /nologo /base:"0x5f3e0000" /version:2.0 /entry:"DllMain" /subsystem:windows /dll /incremental:no /pdb:"$(OUTDIR)\Atl.pdb" /machine:ALPHA /def:".\atl.def" /out:"$(OUTDIR)\Atl.dll" /implib:"$(OUTDIR)\Atl.lib" /delayload:user32.dll /delayload:gdi32.dll /delayload:ole32.dll /delayload:oleaut32.dll /delayload:advapi32.dll /delayload:olepro32.dll 
!else
LINK32_FLAGS=delayimp.lib  atldload.lib /nologo /base:"0x5f3e0000" /version:2.0 /entry:"DllMain" /subsystem:windows /dll /incremental:no /pdb:"$(OUTDIR)\Atl.pdb" /debug /opt:nowin98 /machine:I386 /def:".\atl.def" /out:"$(OUTDIR)\Atl.dll" /implib:"$(OUTDIR)\Atl.lib" /delayload:user32.dll /delayload:gdi32.dll /delayload:ole32.dll /delayload:oleaut32.dll /delayload:advapi32.dll /delayload:olepro32.dll 
!endif
DEF_FILE= \
	".\atl.def"
LINK32_OBJS= \
	"$(INTDIR)\atl.obj" \
	"$(INTDIR)\RegObj.obj" \
	"$(INTDIR)\StdAfx.obj" \
	"$(INTDIR)\atl.res"

"$(OUTDIR)\Atl.dll" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

OutDir=.\.\ReleaseU
TargetPath=.\ReleaseU\Atl.dll
InputPath=.\ReleaseU\Atl.dll
SOURCE=$(InputPath)

"$(OutDir)\regsvr32.trg"	 : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	<<tempfile.bat 
	@echo off 
	echo regsvr32 /s /c "$(TargetPath)" 
	echo regsvr32 exec. time > "$(OutDir)\regsvr32.trg" 
<< 
	

!ENDIF 


!IF "$(NO_EXTERNAL_DEPS)" != "1"
!IF EXISTS("Atl.dep")
!INCLUDE "Atl.dep"
!ELSE 
!MESSAGE Warning: cannot find "Atl.dep"
!ENDIF 
!ENDIF 


!IF "$(CFG)" == "atl - Win32 Debug" || "$(CFG)" == "atl - Win32 Unicode Debug" || "$(CFG)" == "atl - Win32 Release" || "$(CFG)" == "atl - Win32 Unicode Release"
SOURCE=.\atl.cpp

"$(INTDIR)\atl.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\Atl.pch"



".\ReleaseU\atl.obj" : $(SOURCE) "$(INTDIR)" ".\ReleaseU\Atl.pch"


SOURCE=.\atl.idl

!IF  "$(CFG)" == "atl - Win32 Debug"

InputPath=.\atl.idl

"atl.tlb"	"atl.h"	"atl_i.c"	 : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	<<tempfile.bat 
	@echo off 
	midl /h atl.h /iid atl_i.c atl.idl
<< 
	

!ELSEIF  "$(CFG)" == "atl - Win32 Unicode Debug"

InputPath=.\atl.idl

"atl.tlb"	"atl.h"	"atl_i.c"	 : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	<<tempfile.bat 
	@echo off 
	midl /h atl.h /iid atl_i.c atl.idl
<< 
	

!ELSEIF  "$(CFG)" == "atl - Win32 Release"

InputPath=.\atl.idl

"atl.tlb"	"atl.h"	"atl_i.c"	 : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	<<tempfile.bat 
	@echo off 
	midl /h atl.h /iid atl_i.c atl.idl
<< 
	

!ELSEIF  "$(CFG)" == "atl - Win32 Unicode Release"

InputPath=.\atl.idl

"atl.tlb"	"atl.h"	"atl_i.c"	 : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	<<tempfile.bat 
	@echo off 
	midl /h atl.h /iid atl_i.c atl.idl
<< 
	

!ENDIF 

SOURCE=.\atl.rc

"$(INTDIR)\atl.res" : $(SOURCE) "$(INTDIR)"
	$(RSC) $(RSC_PROJ) $(SOURCE)



".\ReleaseU\atl.res" : $(SOURCE) "$(INTDIR)"
	$(RSC) $(RSC_PROJ) $(SOURCE)


SOURCE=.\RegObj.cpp

"$(INTDIR)\RegObj.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\Atl.pch"



".\ReleaseU\RegObj.obj" : $(SOURCE) "$(INTDIR)" ".\ReleaseU\Atl.pch"


SOURCE=.\StdAfx.cpp

!IF  "$(CFG)" == "atl - Win32 Debug"

CPP_SWITCHES=/nologo /MDd /W3 /Gm /Od /I "." /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_WINDLL" /D "_MBCS" /Fp"$(INTDIR)\Atl.pch" /Yc"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c

!if "$(_VCBUILD)" == "1"
CPP_SWITCHES=$(CPP_SWITCHES) /Zi
!else
CPP_SWITCHES=$(CPP_SWITCHES) /ZI
!endif

"$(INTDIR)\StdAfx.obj"	"$(INTDIR)\Atl.pch" : $(SOURCE) "$(INTDIR)"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "atl - Win32 Unicode Debug"

CPP_SWITCHES=/nologo /MDd /W3 /Gm /Od /D "_DEBUG" /D "WIN32" /D "_WINDOWS" /D "_WINDLL" /D "_UNICODE" /Fp"$(INTDIR)\Atl.pch" /Yc"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c

!if "$(_VCBUILD)" == "1"
CPP_SWITCHES=$(CPP_SWITCHES) /Zi
!else
CPP_SWITCHES=$(CPP_SWITCHES) /ZI
!endif

"$(INTDIR)\StdAfx.obj"	"$(INTDIR)\Atl.pch" : $(SOURCE) "$(INTDIR)"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "atl - Win32 Release"

CPP_SWITCHES=/nologo /MT /W3 /Zi /O1 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_WINDLL" /D "_MBCS" /D "_ATL_MIN_CRT" /Fp"$(INTDIR)\Atl.pch" /Yc"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 

"$(INTDIR)\StdAfx.obj"	"$(INTDIR)\Atl.pch" : $(SOURCE) "$(INTDIR)"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "atl - Win32 Unicode Release"

CPP_SWITCHES=/nologo /MT /W3 /Zi /O1 /D "NDEBUG" /D "WIN32" /D "_WINDOWS" /D "_WINDLL" /D "_UNICODE" /D "_ATL_MIN_CRT" /Fp"$(INTDIR)\Atl.pch" /Yc"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 

"$(INTDIR)\StdAfx.obj"	"$(INTDIR)\Atl.pch" : $(SOURCE) "$(INTDIR)"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ENDIF 


!ENDIF 
