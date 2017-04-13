# Microsoft Developer Studio Generated NMAKE File, Based on DRAWPIC.DSP
!IF "$(CFG)" == ""
CFG=DrawPic - Win32 Release
!MESSAGE No configuration specified. Defaulting to DrawPic - Win32 Release.
!ENDIF 

!IF "$(CFG)" != "DrawPic - Win32 Release" && "$(CFG)" != "DrawPic - Win32 Debug" && "$(CFG)" != "DrawPic - Win32 Unicode Debug" && "$(CFG)" != "DrawPic - Win32 Unicode Release"
!MESSAGE Invalid configuration "$(CFG)" specified.
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "DRAWPIC.MAK" CFG="DrawPic - Win32 Release"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "DrawPic - Win32 Release" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE "DrawPic - Win32 Debug" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE "DrawPic - Win32 Unicode Debug" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE "DrawPic - Win32 Unicode Release" (based on "Win32 (x86) Dynamic-Link Library")
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

!IF  "$(CFG)" == "DrawPic - Win32 Release"

OUTDIR=.\Release
INTDIR=.\Release
# Begin Custom Macros
OutDir=.\.\Release
# End Custom Macros

ALL : "$(OUTDIR)\DRAWPIC.ocx" ".\.\Release\regsvr32.trg"


CLEAN :
	-@erase "$(INTDIR)\DrawPic.obj"
	-@erase "$(INTDIR)\DRAWPIC.pch"
	-@erase "$(INTDIR)\DrawPic.res"
	-@erase "$(INTDIR)\DrawPic.tlb"
	-@erase "$(INTDIR)\DrawPicC.obj"
	-@erase "$(INTDIR)\DrawPicP.obj"
	-@erase "$(INTDIR)\StdAfx.obj"
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(OUTDIR)\DRAWPIC.exp"
	-@erase "$(OUTDIR)\DRAWPIC.lib"
	-@erase "$(OUTDIR)\DRAWPIC.ocx"
	-@erase ".\.\Release\regsvr32.trg"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP_PROJ=/nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_WINDLL" /D "_AFXDLL" /D "_MBCS" /D "_USRDLL" /Fp"$(INTDIR)\DRAWPIC.pch" /Yu"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 
MTL_PROJ=/nologo /D "NDEBUG" /mktyplib203 /win32 
RSC_PROJ=/l 0x409 /fo"$(INTDIR)\DrawPic.res" /d "NDEBUG" /d "_AFXDLL" 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\DRAWPIC.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
LINK32_FLAGS=/nologo /subsystem:windows /dll /incremental:no /pdb:"$(OUTDIR)\DRAWPIC.pdb" /machine:I386 /def:".\DrawPic.def" /out:"$(OUTDIR)\DRAWPIC.ocx" /implib:"$(OUTDIR)\DRAWPIC.lib" 
DEF_FILE= \
	".\DrawPic.def"
LINK32_OBJS= \
	"$(INTDIR)\DrawPic.obj" \
	"$(INTDIR)\DrawPicC.obj" \
	"$(INTDIR)\DrawPicP.obj" \
	"$(INTDIR)\StdAfx.obj" \
	"$(INTDIR)\DrawPic.res"

"$(OUTDIR)\DRAWPIC.ocx" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

OutDir=.\.\Release
TargetPath=.\Release\DRAWPIC.ocx
InputPath=.\Release\DRAWPIC.ocx
SOURCE=$(InputPath)

"$(OutDir)\regsvr32.trg"	 : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	<<tempfile.bat 
	@echo off 
	regsvr32 /s /c "$(TargetPath)" 
	echo regsvr32 exec. time > "$(OutDir)\regsvr32.trg" 
<< 
	

!ELSEIF  "$(CFG)" == "DrawPic - Win32 Debug"

OUTDIR=.\Debug
INTDIR=.\Debug
# Begin Custom Macros
OutDir=.\.\Debug
# End Custom Macros

ALL : "$(OUTDIR)\DRAWPIC.ocx" ".\.\Debug\regsvr32.trg"


CLEAN :
	-@erase "$(INTDIR)\DrawPic.obj"
	-@erase "$(INTDIR)\DRAWPIC.pch"
	-@erase "$(INTDIR)\DrawPic.res"
	-@erase "$(INTDIR)\DrawPic.tlb"
	-@erase "$(INTDIR)\DrawPicC.obj"
	-@erase "$(INTDIR)\DrawPicP.obj"
	-@erase "$(INTDIR)\StdAfx.obj"
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(INTDIR)\vc60.pdb"
	-@erase "$(OUTDIR)\DRAWPIC.exp"
	-@erase "$(OUTDIR)\DRAWPIC.ilk"
	-@erase "$(OUTDIR)\DRAWPIC.lib"
	-@erase "$(OUTDIR)\DRAWPIC.ocx"
	-@erase "$(OUTDIR)\DRAWPIC.pdb"
	-@erase ".\.\Debug\regsvr32.trg"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP_PROJ=/nologo /MDd /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_WINDLL" /D "_AFXDLL" /D "_MBCS" /D "_USRDLL" /Fp"$(INTDIR)\DRAWPIC.pch" /Yu"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 
MTL_PROJ=/nologo /D "_DEBUG" /mktyplib203 /win32 
RSC_PROJ=/l 0x409 /fo"$(INTDIR)\DrawPic.res" /d "_DEBUG" /d "_AFXDLL" 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\DRAWPIC.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
LINK32_FLAGS=/nologo /subsystem:windows /dll /incremental:yes /pdb:"$(OUTDIR)\DRAWPIC.pdb" /debug /machine:I386 /def:".\DrawPic.def" /out:"$(OUTDIR)\DRAWPIC.ocx" /implib:"$(OUTDIR)\DRAWPIC.lib" 
DEF_FILE= \
	".\DrawPic.def"
LINK32_OBJS= \
	"$(INTDIR)\DrawPic.obj" \
	"$(INTDIR)\DrawPicC.obj" \
	"$(INTDIR)\DrawPicP.obj" \
	"$(INTDIR)\StdAfx.obj" \
	"$(INTDIR)\DrawPic.res"

"$(OUTDIR)\DRAWPIC.ocx" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

OutDir=.\.\Debug
TargetPath=.\Debug\DRAWPIC.ocx
InputPath=.\Debug\DRAWPIC.ocx
SOURCE=$(InputPath)

"$(OutDir)\regsvr32.trg"	 : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	<<tempfile.bat 
	@echo off 
	regsvr32 /s /c "$(TargetPath)" 
	echo regsvr32 exec. time > "$(OutDir)\regsvr32.trg" 
<< 
	

!ELSEIF  "$(CFG)" == "DrawPic - Win32 Unicode Debug"

OUTDIR=.\DebugU
INTDIR=.\DebugU
# Begin Custom Macros
OutDir=.\.\DebugU
# End Custom Macros

ALL : "$(OUTDIR)\DRAWPIC.ocx" ".\.\DebugU\regsvr32.trg"


CLEAN :
	-@erase "$(INTDIR)\DrawPic.obj"
	-@erase "$(INTDIR)\DRAWPIC.pch"
	-@erase "$(INTDIR)\DrawPic.res"
	-@erase "$(INTDIR)\DrawPic.tlb"
	-@erase "$(INTDIR)\DrawPicC.obj"
	-@erase "$(INTDIR)\DrawPicP.obj"
	-@erase "$(INTDIR)\StdAfx.obj"
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(INTDIR)\vc60.pdb"
	-@erase "$(OUTDIR)\DRAWPIC.exp"
	-@erase "$(OUTDIR)\DRAWPIC.ilk"
	-@erase "$(OUTDIR)\DRAWPIC.lib"
	-@erase "$(OUTDIR)\DRAWPIC.ocx"
	-@erase "$(OUTDIR)\DRAWPIC.pdb"
	-@erase ".\.\DebugU\regsvr32.trg"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP_PROJ=/nologo /MDd /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_WINDLL" /D "_AFXDLL" /D "_USRDLL" /D "_UNICODE" /Fp"$(INTDIR)\DRAWPIC.pch" /Yu"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 
MTL_PROJ=/nologo /D "_DEBUG" /mktyplib203 /win32 
RSC_PROJ=/l 0x409 /fo"$(INTDIR)\DrawPic.res" /d "_DEBUG" /d "_AFXDLL" 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\DRAWPIC.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
LINK32_FLAGS=/nologo /subsystem:windows /dll /incremental:yes /pdb:"$(OUTDIR)\DRAWPIC.pdb" /debug /machine:I386 /def:".\DrawPic.def" /out:"$(OUTDIR)\DRAWPIC.ocx" /implib:"$(OUTDIR)\DRAWPIC.lib" 
DEF_FILE= \
	".\DrawPic.def"
LINK32_OBJS= \
	"$(INTDIR)\DrawPic.obj" \
	"$(INTDIR)\DrawPicC.obj" \
	"$(INTDIR)\DrawPicP.obj" \
	"$(INTDIR)\StdAfx.obj" \
	"$(INTDIR)\DrawPic.res"

"$(OUTDIR)\DRAWPIC.ocx" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

OutDir=.\.\DebugU
TargetPath=.\DebugU\DRAWPIC.ocx
InputPath=.\DebugU\DRAWPIC.ocx
SOURCE=$(InputPath)

"$(OutDir)\regsvr32.trg"	 : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	<<tempfile.bat 
	@echo off 
	regsvr32 /s /c "$(TargetPath)" 
	echo regsvr32 exec. time > "$(OutDir)\regsvr32.trg" 
<< 
	

!ELSEIF  "$(CFG)" == "DrawPic - Win32 Unicode Release"

OUTDIR=.\ReleaseU
INTDIR=.\ReleaseU
# Begin Custom Macros
OutDir=.\.\ReleaseU
# End Custom Macros

ALL : "$(OUTDIR)\DRAWPIC.ocx" ".\.\ReleaseU\regsvr32.trg"


CLEAN :
	-@erase "$(INTDIR)\DrawPic.obj"
	-@erase "$(INTDIR)\DRAWPIC.pch"
	-@erase "$(INTDIR)\DrawPic.res"
	-@erase "$(INTDIR)\DrawPic.tlb"
	-@erase "$(INTDIR)\DrawPicC.obj"
	-@erase "$(INTDIR)\DrawPicP.obj"
	-@erase "$(INTDIR)\StdAfx.obj"
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(OUTDIR)\DRAWPIC.exp"
	-@erase "$(OUTDIR)\DRAWPIC.lib"
	-@erase "$(OUTDIR)\DRAWPIC.ocx"
	-@erase ".\.\ReleaseU\regsvr32.trg"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP_PROJ=/nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_WINDLL" /D "_AFXDLL" /D "_USRDLL" /D "_UNICODE" /Fp"$(INTDIR)\DRAWPIC.pch" /Yu"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 
MTL_PROJ=/nologo /D "NDEBUG" /mktyplib203 /win32 
RSC_PROJ=/l 0x409 /fo"$(INTDIR)\DrawPic.res" /d "NDEBUG" /d "_AFXDLL" 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\DRAWPIC.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
LINK32_FLAGS=/nologo /subsystem:windows /dll /incremental:no /pdb:"$(OUTDIR)\DRAWPIC.pdb" /machine:I386 /def:".\DrawPic.def" /out:"$(OUTDIR)\DRAWPIC.ocx" /implib:"$(OUTDIR)\DRAWPIC.lib" 
DEF_FILE= \
	".\DrawPic.def"
LINK32_OBJS= \
	"$(INTDIR)\DrawPic.obj" \
	"$(INTDIR)\DrawPicC.obj" \
	"$(INTDIR)\DrawPicP.obj" \
	"$(INTDIR)\StdAfx.obj" \
	"$(INTDIR)\DrawPic.res"

"$(OUTDIR)\DRAWPIC.ocx" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

OutDir=.\.\ReleaseU
TargetPath=.\ReleaseU\DRAWPIC.ocx
InputPath=.\ReleaseU\DRAWPIC.ocx
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
!IF EXISTS("DRAWPIC.DEP")
!INCLUDE "DRAWPIC.DEP"
!ELSE 
!MESSAGE Warning: cannot find "DRAWPIC.DEP"
!ENDIF 
!ENDIF 


!IF "$(CFG)" == "DrawPic - Win32 Release" || "$(CFG)" == "DrawPic - Win32 Debug" || "$(CFG)" == "DrawPic - Win32 Unicode Debug" || "$(CFG)" == "DrawPic - Win32 Unicode Release"
SOURCE=.\DrawPic.cpp

"$(INTDIR)\DrawPic.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\DRAWPIC.pch"


SOURCE=.\DrawPic.odl

!IF  "$(CFG)" == "DrawPic - Win32 Release"

MTL_SWITCHES=/nologo /D "NDEBUG" /tlb "$(OUTDIR)\DrawPic.tlb" /mktyplib203 /win32 

"$(OUTDIR)\DrawPic.tlb" : $(SOURCE) "$(OUTDIR)"
	$(MTL) @<<
  $(MTL_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "DrawPic - Win32 Debug"

MTL_SWITCHES=/nologo /D "_DEBUG" /tlb "$(OUTDIR)\DrawPic.tlb" /mktyplib203 /win32 

"$(OUTDIR)\DrawPic.tlb" : $(SOURCE) "$(OUTDIR)"
	$(MTL) @<<
  $(MTL_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "DrawPic - Win32 Unicode Debug"

MTL_SWITCHES=/nologo /D "_DEBUG" /tlb "$(OUTDIR)\DrawPic.tlb" /mktyplib203 /win32 

"$(OUTDIR)\DrawPic.tlb" : $(SOURCE) "$(OUTDIR)"
	$(MTL) @<<
  $(MTL_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "DrawPic - Win32 Unicode Release"

MTL_SWITCHES=/nologo /D "NDEBUG" /tlb "$(OUTDIR)\DrawPic.tlb" /mktyplib203 /win32 

"$(OUTDIR)\DrawPic.tlb" : $(SOURCE) "$(OUTDIR)"
	$(MTL) @<<
  $(MTL_SWITCHES) $(SOURCE)
<<


!ENDIF 

SOURCE=.\DrawPic.rc

!IF  "$(CFG)" == "DrawPic - Win32 Release"


"$(INTDIR)\DrawPic.res" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\DrawPic.tlb"
	$(RSC) /l 0x409 /fo"$(INTDIR)\DrawPic.res" /i ".\Release" /d "NDEBUG" /d "_AFXDLL" $(SOURCE)


!ELSEIF  "$(CFG)" == "DrawPic - Win32 Debug"


"$(INTDIR)\DrawPic.res" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\DrawPic.tlb"
	$(RSC) /l 0x409 /fo"$(INTDIR)\DrawPic.res" /i ".\Debug" /d "_DEBUG" /d "_AFXDLL" $(SOURCE)


!ELSEIF  "$(CFG)" == "DrawPic - Win32 Unicode Debug"


"$(INTDIR)\DrawPic.res" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\DrawPic.tlb"
	$(RSC) /l 0x409 /fo"$(INTDIR)\DrawPic.res" /i ".\DebugU" /d "_DEBUG" /d "_AFXDLL" $(SOURCE)


!ELSEIF  "$(CFG)" == "DrawPic - Win32 Unicode Release"


"$(INTDIR)\DrawPic.res" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\DrawPic.tlb"
	$(RSC) /l 0x409 /fo"$(INTDIR)\DrawPic.res" /i ".\ReleaseU" /d "NDEBUG" /d "_AFXDLL" $(SOURCE)


!ENDIF 

SOURCE=.\DrawPicC.cpp

"$(INTDIR)\DrawPicC.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\DRAWPIC.pch"


SOURCE=.\DrawPicP.cpp

"$(INTDIR)\DrawPicP.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\DRAWPIC.pch"


SOURCE=.\StdAfx.cpp

!IF  "$(CFG)" == "DrawPic - Win32 Release"

CPP_SWITCHES=/nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_WINDLL" /D "_AFXDLL" /D "_MBCS" /D "_USRDLL" /Fp"$(INTDIR)\DRAWPIC.pch" /Yc"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 

"$(INTDIR)\StdAfx.obj"	"$(INTDIR)\DRAWPIC.pch" : $(SOURCE) "$(INTDIR)"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "DrawPic - Win32 Debug"

CPP_SWITCHES=/nologo /MDd /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_WINDLL" /D "_AFXDLL" /D "_MBCS" /D "_USRDLL" /Fp"$(INTDIR)\DRAWPIC.pch" /Yc"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 

"$(INTDIR)\StdAfx.obj"	"$(INTDIR)\DRAWPIC.pch" : $(SOURCE) "$(INTDIR)"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "DrawPic - Win32 Unicode Debug"

CPP_SWITCHES=/nologo /MDd /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_WINDLL" /D "_AFXDLL" /D "_USRDLL" /D "_UNICODE" /Fp"$(INTDIR)\DRAWPIC.pch" /Yc"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 

"$(INTDIR)\StdAfx.obj"	"$(INTDIR)\DRAWPIC.pch" : $(SOURCE) "$(INTDIR)"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "DrawPic - Win32 Unicode Release"

CPP_SWITCHES=/nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_WINDLL" /D "_AFXDLL" /D "_USRDLL" /D "_UNICODE" /Fp"$(INTDIR)\DRAWPIC.pch" /Yc"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 

"$(INTDIR)\StdAfx.obj"	"$(INTDIR)\DRAWPIC.pch" : $(SOURCE) "$(INTDIR)"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ENDIF 


!ENDIF 

