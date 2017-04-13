# Microsoft Developer Studio Generated NMAKE File, Based on daoedit.dsp
!IF "$(CFG)" == ""
CFG=DaoEdit - Win32 Release
!MESSAGE No configuration specified. Defaulting to DaoEdit - Win32 Release.
!ENDIF 

!IF "$(CFG)" != "DaoEdit - Win32 Release" && "$(CFG)" != "DaoEdit - Win32 Debug" && "$(CFG)" != "DaoEdit - Win32 Debug Unicode" && "$(CFG)" != "DaoEdit - Win32 Release Unicode"
!MESSAGE Invalid configuration "$(CFG)" specified.
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "daoedit.mak" CFG="DaoEdit - Win32 Release"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "DaoEdit - Win32 Release" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE "DaoEdit - Win32 Debug" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE "DaoEdit - Win32 Debug Unicode" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE "DaoEdit - Win32 Release Unicode" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE 
!ERROR An invalid configuration is specified.
!ENDIF 

!IF "$(OS)" == "Windows_NT"
NULL=
!ELSE 
NULL=nul
!ENDIF 

!IF  "$(CFG)" == "DaoEdit - Win32 Release"

OUTDIR=.\Release
INTDIR=.\Release
# Begin Custom Macros
OutDir=.\Release
# End Custom Macros

ALL : "$(OUTDIR)\daoedit.ocx" "$(OUTDIR)\DaoEdit.tlb" ".\Release\regsvr32.trg"


CLEAN :
	-@erase "$(INTDIR)\daoctl.obj"
	-@erase "$(INTDIR)\DaoEdit.obj"
	-@erase "$(INTDIR)\daoedit.pch"
	-@erase "$(INTDIR)\DaoEdit.res"
	-@erase "$(INTDIR)\DaoEdit.tlb"
	-@erase "$(INTDIR)\daoppg.obj"
	-@erase "$(INTDIR)\StdAfx.obj"
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(OUTDIR)\daoedit.exp"
	-@erase "$(OUTDIR)\daoedit.lib"
	-@erase "$(OUTDIR)\daoedit.ocx"
	-@erase ".\Release\regsvr32.trg"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP=cl.exe
CPP_PROJ=/nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /Fp"$(INTDIR)\daoedit.pch" /Yu"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 

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
RSC_PROJ=/l 0x409 /fo"$(INTDIR)\DaoEdit.res" /d "NDEBUG" /d "_AFXDLL" 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\daoedit.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
LINK32_FLAGS=/nologo /subsystem:windows /dll /incremental:no /pdb:"$(OUTDIR)\daoedit.pdb" /machine:I386 /def:".\DaoEdit.def" /out:"$(OUTDIR)\daoedit.ocx" /implib:"$(OUTDIR)\daoedit.lib" 
DEF_FILE= \
	".\DaoEdit.def"
LINK32_OBJS= \
	"$(INTDIR)\daoctl.obj" \
	"$(INTDIR)\DaoEdit.obj" \
	"$(INTDIR)\daoppg.obj" \
	"$(INTDIR)\StdAfx.obj" \
	"$(INTDIR)\DaoEdit.res"

"$(OUTDIR)\daoedit.ocx" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

OutDir=.\Release
TargetPath=.\Release\daoedit.ocx
InputPath=.\Release\daoedit.ocx
SOURCE="$(InputPath)"

"$(OUTDIR)\regsvr32.trg" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	<<tempfile.bat 
	@echo off 
	regsvr32 /s /c "$(TargetPath)" 
	echo regsvr32 exec. time > "$(OutDir)\regsvr32.trg" 
<< 
	

!ELSEIF  "$(CFG)" == "DaoEdit - Win32 Debug"

OUTDIR=.\Debug
INTDIR=.\Debug
# Begin Custom Macros
OutDir=.\Debug
# End Custom Macros

ALL : "$(OUTDIR)\daoedit.ocx" "$(OUTDIR)\DaoEdit.tlb" ".\Debug\regsvr32.trg"


CLEAN :
	-@erase "$(INTDIR)\daoctl.obj"
	-@erase "$(INTDIR)\DaoEdit.obj"
	-@erase "$(INTDIR)\daoedit.pch"
	-@erase "$(INTDIR)\DaoEdit.res"
	-@erase "$(INTDIR)\DaoEdit.tlb"
	-@erase "$(INTDIR)\daoppg.obj"
	-@erase "$(INTDIR)\StdAfx.obj"
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(INTDIR)\vc60.pdb"
	-@erase "$(OUTDIR)\daoedit.exp"
	-@erase "$(OUTDIR)\daoedit.ilk"
	-@erase "$(OUTDIR)\daoedit.lib"
	-@erase "$(OUTDIR)\daoedit.ocx"
	-@erase "$(OUTDIR)\daoedit.pdb"
	-@erase ".\Debug\regsvr32.trg"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP=cl.exe
CPP_PROJ=/nologo /MDd /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /Fp"$(INTDIR)\daoedit.pch" /Yu"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 

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
RSC_PROJ=/l 0x409 /fo"$(INTDIR)\DaoEdit.res" /d "_DEBUG" /d "_AFXDLL" 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\daoedit.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
LINK32_FLAGS=/nologo /subsystem:windows /dll /incremental:yes /pdb:"$(OUTDIR)\daoedit.pdb" /debug /machine:I386 /def:".\DaoEdit.def" /out:"$(OUTDIR)\daoedit.ocx" /implib:"$(OUTDIR)\daoedit.lib" 
DEF_FILE= \
	".\DaoEdit.def"
LINK32_OBJS= \
	"$(INTDIR)\daoctl.obj" \
	"$(INTDIR)\DaoEdit.obj" \
	"$(INTDIR)\daoppg.obj" \
	"$(INTDIR)\StdAfx.obj" \
	"$(INTDIR)\DaoEdit.res"

"$(OUTDIR)\daoedit.ocx" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

OutDir=.\Debug
TargetPath=.\Debug\daoedit.ocx
InputPath=.\Debug\daoedit.ocx
SOURCE="$(InputPath)"

"$(OUTDIR)\regsvr32.trg" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	<<tempfile.bat 
	@echo off 
	regsvr32 /s /c "$(TargetPath)" 
	echo regsvr32 exec. time > "$(OutDir)\regsvr32.trg" 
<< 
	

!ELSEIF  "$(CFG)" == "DaoEdit - Win32 Debug Unicode"

OUTDIR=.\DebugU
INTDIR=.\DebugU
# Begin Custom Macros
OutDir=.\DebugU
# End Custom Macros

ALL : "$(OUTDIR)\daoedit.ocx" ".\DebugU\regsvr32.trg"


CLEAN :
	-@erase "$(INTDIR)\daoctl.obj"
	-@erase "$(INTDIR)\DaoEdit.obj"
	-@erase "$(INTDIR)\daoedit.pch"
	-@erase "$(INTDIR)\DaoEdit.res"
	-@erase "$(INTDIR)\DaoEdit.tlb"
	-@erase "$(INTDIR)\daoppg.obj"
	-@erase "$(INTDIR)\StdAfx.obj"
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(INTDIR)\vc60.pdb"
	-@erase "$(OUTDIR)\daoedit.exp"
	-@erase "$(OUTDIR)\daoedit.ilk"
	-@erase "$(OUTDIR)\daoedit.lib"
	-@erase "$(OUTDIR)\daoedit.ocx"
	-@erase "$(OUTDIR)\daoedit.pdb"
	-@erase ".\DebugU\regsvr32.trg"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP=cl.exe
CPP_PROJ=/nologo /MDd /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_UNICODE" /Fp"$(INTDIR)\daoedit.pch" /Yu"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 

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
RSC_PROJ=/l 0x409 /fo"$(INTDIR)\DaoEdit.res" /d "_DEBUG" /d "_AFXDLL" 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\daoedit.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
LINK32_FLAGS=/nologo /subsystem:windows /dll /incremental:yes /pdb:"$(OUTDIR)\daoedit.pdb" /debug /machine:I386 /def:".\DaoEdit.def" /out:"$(OUTDIR)\daoedit.ocx" /implib:"$(OUTDIR)\daoedit.lib" 
DEF_FILE= \
	".\DaoEdit.def"
LINK32_OBJS= \
	"$(INTDIR)\daoctl.obj" \
	"$(INTDIR)\DaoEdit.obj" \
	"$(INTDIR)\daoppg.obj" \
	"$(INTDIR)\StdAfx.obj" \
	"$(INTDIR)\DaoEdit.res"

"$(OUTDIR)\daoedit.ocx" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

OutDir=.\DebugU
TargetPath=.\DebugU\daoedit.ocx
InputPath=.\DebugU\daoedit.ocx
SOURCE="$(InputPath)"

"$(OUTDIR)\regsvr32.trg" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	<<tempfile.bat 
	@echo off 
	regsvr32 /s /c "$(TargetPath)" 
	echo regsvr32 exec. time > "$(OutDir)\regsvr32.trg" 
<< 
	

!ELSEIF  "$(CFG)" == "DaoEdit - Win32 Release Unicode"

OUTDIR=.\ReleaseU
INTDIR=.\ReleaseU
# Begin Custom Macros
OutDir=.\ReleaseU
# End Custom Macros

ALL : "$(OUTDIR)\daoedit.ocx" "$(OUTDIR)\DaoEdit.tlb" ".\ReleaseU\regsvr32.trg"


CLEAN :
	-@erase "$(INTDIR)\daoctl.obj"
	-@erase "$(INTDIR)\DaoEdit.obj"
	-@erase "$(INTDIR)\daoedit.pch"
	-@erase "$(INTDIR)\DaoEdit.res"
	-@erase "$(INTDIR)\DaoEdit.tlb"
	-@erase "$(INTDIR)\daoppg.obj"
	-@erase "$(INTDIR)\StdAfx.obj"
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(INTDIR)\vc60.pdb"
	-@erase "$(OUTDIR)\daoedit.exp"
	-@erase "$(OUTDIR)\daoedit.lib"
	-@erase "$(OUTDIR)\daoedit.ocx"
	-@erase ".\ReleaseU\regsvr32.trg"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP=cl.exe
CPP_PROJ=/nologo /MD /W3 /GX /ZI /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_UNICODE" /Fp"$(INTDIR)\daoedit.pch" /Yu"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 

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
RSC_PROJ=/l 0x409 /fo"$(INTDIR)\DaoEdit.res" /d "NDEBUG" /d "_AFXDLL" 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\daoedit.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
LINK32_FLAGS=/nologo /subsystem:windows /dll /incremental:no /pdb:"$(OUTDIR)\daoedit.pdb" /machine:I386 /def:".\DaoEdit.def" /out:"$(OUTDIR)\daoedit.ocx" /implib:"$(OUTDIR)\daoedit.lib" 
DEF_FILE= \
	".\DaoEdit.def"
LINK32_OBJS= \
	"$(INTDIR)\daoctl.obj" \
	"$(INTDIR)\DaoEdit.obj" \
	"$(INTDIR)\daoppg.obj" \
	"$(INTDIR)\StdAfx.obj" \
	"$(INTDIR)\DaoEdit.res"

"$(OUTDIR)\daoedit.ocx" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

OutDir=.\ReleaseU
TargetPath=.\ReleaseU\daoedit.ocx
InputPath=.\ReleaseU\daoedit.ocx
SOURCE="$(InputPath)"

"$(OUTDIR)\regsvr32.trg" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	<<tempfile.bat 
	@echo off 
	regsvr32 /s /c "$(TargetPath)" 
	echo regsvr32 exec. time > "$(OutDir)\regsvr32.trg" 
<< 
	

!ENDIF 


!IF "$(NO_EXTERNAL_DEPS)" != "1"
!IF EXISTS("daoedit.dep")
!INCLUDE "daoedit.dep"
!ELSE 
!MESSAGE Warning: cannot find "daoedit.dep"
!ENDIF 
!ENDIF 


!IF "$(CFG)" == "DaoEdit - Win32 Release" || "$(CFG)" == "DaoEdit - Win32 Debug" || "$(CFG)" == "DaoEdit - Win32 Debug Unicode" || "$(CFG)" == "DaoEdit - Win32 Release Unicode"
SOURCE=.\daoctl.cpp

"$(INTDIR)\daoctl.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\daoedit.pch"


SOURCE=.\DaoEdit.cpp

"$(INTDIR)\DaoEdit.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\daoedit.pch"


SOURCE=.\DaoEdit.odl

!IF  "$(CFG)" == "DaoEdit - Win32 Release"

MTL_SWITCHES=/nologo /D "NDEBUG" /tlb "$(OUTDIR)\DaoEdit.tlb" /mktyplib203 /win32 

"$(OUTDIR)\DaoEdit.tlb" : $(SOURCE) "$(OUTDIR)"
	$(MTL) @<<
  $(MTL_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "DaoEdit - Win32 Debug"

MTL_SWITCHES=/nologo /D "_DEBUG" /tlb "$(OUTDIR)\DaoEdit.tlb" /mktyplib203 /win32 

"$(OUTDIR)\DaoEdit.tlb" : $(SOURCE) "$(OUTDIR)"
	$(MTL) @<<
  $(MTL_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "DaoEdit - Win32 Debug Unicode"

MTL_SWITCHES=/nologo /D "_DEBUG" /tlb "$(OUTDIR)\DaoEdit.tlb" /mktyplib203 /win32 

"$(OUTDIR)\DaoEdit.tlb" : $(SOURCE) "$(OUTDIR)"
	$(MTL) @<<
  $(MTL_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "DaoEdit - Win32 Release Unicode"

MTL_SWITCHES=/nologo /D "NDEBUG" /tlb "$(OUTDIR)\DaoEdit.tlb" /mktyplib203 /win32 

"$(OUTDIR)\DaoEdit.tlb" : $(SOURCE) "$(OUTDIR)"
	$(MTL) @<<
  $(MTL_SWITCHES) $(SOURCE)
<<


!ENDIF 

SOURCE=.\DaoEdit.rc

!IF  "$(CFG)" == "DaoEdit - Win32 Release"


"$(INTDIR)\DaoEdit.res" : $(SOURCE) "$(INTDIR)"
	$(RSC) /l 0x409 /fo"$(INTDIR)\DaoEdit.res" /i ".\Release" /d "NDEBUG" /d "_AFXDLL" $(SOURCE)


!ELSEIF  "$(CFG)" == "DaoEdit - Win32 Debug"


"$(INTDIR)\DaoEdit.res" : $(SOURCE) "$(INTDIR)"
	$(RSC) /l 0x409 /fo"$(INTDIR)\DaoEdit.res" /i ".\Debug" /d "_DEBUG" /d "_AFXDLL" $(SOURCE)


!ELSEIF  "$(CFG)" == "DaoEdit - Win32 Debug Unicode"


"$(INTDIR)\DaoEdit.res" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\DaoEdit.tlb"
	$(RSC) /l 0x409 /fo"$(INTDIR)\DaoEdit.res" /i ".\DebugU" /d "_DEBUG" /d "_AFXDLL" $(SOURCE)


!ELSEIF  "$(CFG)" == "DaoEdit - Win32 Release Unicode"


"$(INTDIR)\DaoEdit.res" : $(SOURCE) "$(INTDIR)"
	$(RSC) /l 0x409 /fo"$(INTDIR)\DaoEdit.res" /i ".\ReleaseU" /d "NDEBUG" /d "_AFXDLL" $(SOURCE)


!ENDIF 

SOURCE=.\daoppg.cpp

"$(INTDIR)\daoppg.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\daoedit.pch"


SOURCE=.\StdAfx.cpp

!IF  "$(CFG)" == "DaoEdit - Win32 Release"

CPP_SWITCHES=/nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /Fp"$(INTDIR)\daoedit.pch" /Yc"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 

"$(INTDIR)\StdAfx.obj"	"$(INTDIR)\daoedit.pch" : $(SOURCE) "$(INTDIR)"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "DaoEdit - Win32 Debug"

CPP_SWITCHES=/nologo /MDd /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /Fp"$(INTDIR)\daoedit.pch" /Yc"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 

"$(INTDIR)\StdAfx.obj"	"$(INTDIR)\daoedit.pch" : $(SOURCE) "$(INTDIR)"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "DaoEdit - Win32 Debug Unicode"

CPP_SWITCHES=/nologo /MDd /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_UNICODE" /Fp"$(INTDIR)\daoedit.pch" /Yc"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 

"$(INTDIR)\StdAfx.obj"	"$(INTDIR)\daoedit.pch" : $(SOURCE) "$(INTDIR)"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "DaoEdit - Win32 Release Unicode"

CPP_SWITCHES=/nologo /MD /W3 /GX /ZI /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_UNICODE" /Fp"$(INTDIR)\daoedit.pch" /Yc"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 

"$(INTDIR)\StdAfx.obj"	"$(INTDIR)\daoedit.pch" : $(SOURCE) "$(INTDIR)"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ENDIF 


!ENDIF 

