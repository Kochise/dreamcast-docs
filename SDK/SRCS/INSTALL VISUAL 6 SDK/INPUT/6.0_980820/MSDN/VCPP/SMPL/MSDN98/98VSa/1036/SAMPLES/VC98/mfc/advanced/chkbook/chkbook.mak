# Microsoft Developer Studio Generated NMAKE File, Based on chkbook.dsp
!IF "$(CFG)" == ""
CFG=ChkBook - Win32 Release
!MESSAGE No configuration specified. Defaulting to ChkBook - Win32 Release.
!ENDIF 

!IF "$(CFG)" != "ChkBook - Win32 Release" && "$(CFG)" != "ChkBook - Win32 Debug" && "$(CFG)" != "ChkBook - Win32 Unicode Release" && "$(CFG)" != "ChkBook - Win32 Unicode Debug"
!MESSAGE Invalid configuration "$(CFG)" specified.
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "chkbook.mak" CFG="ChkBook - Win32 Release"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "ChkBook - Win32 Release" (based on "Win32 (x86) Application")
!MESSAGE "ChkBook - Win32 Debug" (based on "Win32 (x86) Application")
!MESSAGE "ChkBook - Win32 Unicode Release" (based on "Win32 (x86) Application")
!MESSAGE "ChkBook - Win32 Unicode Debug" (based on "Win32 (x86) Application")
!MESSAGE 
!ERROR An invalid configuration is specified.
!ENDIF 

!IF "$(OS)" == "Windows_NT"
NULL=
!ELSE 
NULL=nul
!ENDIF 

!IF  "$(CFG)" == "ChkBook - Win32 Release"

OUTDIR=.\Release
INTDIR=.\Release
# Begin Custom Macros
OutDir=.\Release
# End Custom Macros

ALL : "$(OUTDIR)\chkbook.exe"


CLEAN :
	-@erase "$(INTDIR)\bookvw.obj"
	-@erase "$(INTDIR)\checkdoc.obj"
	-@erase "$(INTDIR)\checkvw.obj"
	-@erase "$(INTDIR)\chkbkfrm.obj"
	-@erase "$(INTDIR)\chkbook.obj"
	-@erase "$(INTDIR)\chkbook.pch"
	-@erase "$(INTDIR)\chkbook.res"
	-@erase "$(INTDIR)\dollcent.obj"
	-@erase "$(INTDIR)\fxrecdoc.obj"
	-@erase "$(INTDIR)\mainfrm.obj"
	-@erase "$(INTDIR)\rowview.obj"
	-@erase "$(INTDIR)\stdafx.obj"
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(OUTDIR)\chkbook.exe"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP=cl.exe
CPP_PROJ=/nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /Fp"$(INTDIR)\chkbook.pch" /Yu"Stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 

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
RSC_PROJ=/l 0x409 /fo"$(INTDIR)\chkbook.res" /d "NDEBUG" /d "_AFXDLL" 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\chkbook.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
LINK32_FLAGS=/nologo /subsystem:windows /incremental:no /pdb:"$(OUTDIR)\chkbook.pdb" /machine:I386 /out:"$(OUTDIR)\chkbook.exe" 
LINK32_OBJS= \
	"$(INTDIR)\bookvw.obj" \
	"$(INTDIR)\checkdoc.obj" \
	"$(INTDIR)\checkvw.obj" \
	"$(INTDIR)\chkbkfrm.obj" \
	"$(INTDIR)\chkbook.obj" \
	"$(INTDIR)\dollcent.obj" \
	"$(INTDIR)\fxrecdoc.obj" \
	"$(INTDIR)\mainfrm.obj" \
	"$(INTDIR)\rowview.obj" \
	"$(INTDIR)\stdafx.obj" \
	"$(INTDIR)\chkbook.res"

"$(OUTDIR)\chkbook.exe" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ELSEIF  "$(CFG)" == "ChkBook - Win32 Debug"

OUTDIR=.\Debug
INTDIR=.\Debug
# Begin Custom Macros
OutDir=.\Debug
# End Custom Macros

ALL : "$(OUTDIR)\chkbook.exe"


CLEAN :
	-@erase "$(INTDIR)\bookvw.obj"
	-@erase "$(INTDIR)\checkdoc.obj"
	-@erase "$(INTDIR)\checkvw.obj"
	-@erase "$(INTDIR)\chkbkfrm.obj"
	-@erase "$(INTDIR)\chkbook.obj"
	-@erase "$(INTDIR)\chkbook.pch"
	-@erase "$(INTDIR)\chkbook.res"
	-@erase "$(INTDIR)\dollcent.obj"
	-@erase "$(INTDIR)\fxrecdoc.obj"
	-@erase "$(INTDIR)\mainfrm.obj"
	-@erase "$(INTDIR)\rowview.obj"
	-@erase "$(INTDIR)\stdafx.obj"
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(INTDIR)\vc60.pdb"
	-@erase "$(OUTDIR)\chkbook.exe"
	-@erase "$(OUTDIR)\chkbook.ilk"
	-@erase "$(OUTDIR)\chkbook.pdb"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP=cl.exe
CPP_PROJ=/nologo /MDd /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /Fp"$(INTDIR)\chkbook.pch" /Yu"Stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 

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
RSC_PROJ=/l 0x409 /fo"$(INTDIR)\chkbook.res" /d "_DEBUG" /d "_AFXDLL" 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\chkbook.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
LINK32_FLAGS=/nologo /subsystem:windows /incremental:yes /pdb:"$(OUTDIR)\chkbook.pdb" /debug /machine:I386 /out:"$(OUTDIR)\chkbook.exe" 
LINK32_OBJS= \
	"$(INTDIR)\bookvw.obj" \
	"$(INTDIR)\checkdoc.obj" \
	"$(INTDIR)\checkvw.obj" \
	"$(INTDIR)\chkbkfrm.obj" \
	"$(INTDIR)\chkbook.obj" \
	"$(INTDIR)\dollcent.obj" \
	"$(INTDIR)\fxrecdoc.obj" \
	"$(INTDIR)\mainfrm.obj" \
	"$(INTDIR)\rowview.obj" \
	"$(INTDIR)\stdafx.obj" \
	"$(INTDIR)\chkbook.res"

"$(OUTDIR)\chkbook.exe" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ELSEIF  "$(CFG)" == "ChkBook - Win32 Unicode Release"

OUTDIR=.\UniRelease
INTDIR=.\UniRelease
# Begin Custom Macros
OutDir=.\UniRelease
# End Custom Macros

ALL : "$(OUTDIR)\chkbook.exe"


CLEAN :
	-@erase "$(INTDIR)\bookvw.obj"
	-@erase "$(INTDIR)\checkdoc.obj"
	-@erase "$(INTDIR)\checkvw.obj"
	-@erase "$(INTDIR)\chkbkfrm.obj"
	-@erase "$(INTDIR)\chkbook.obj"
	-@erase "$(INTDIR)\chkbook.pch"
	-@erase "$(INTDIR)\chkbook.res"
	-@erase "$(INTDIR)\dollcent.obj"
	-@erase "$(INTDIR)\fxrecdoc.obj"
	-@erase "$(INTDIR)\mainfrm.obj"
	-@erase "$(INTDIR)\rowview.obj"
	-@erase "$(INTDIR)\stdafx.obj"
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(OUTDIR)\chkbook.exe"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP=cl.exe
CPP_PROJ=/nologo /MD /W3 /GX /O2 /D "NDEBUG" /D "WIN32" /D "_WINDOWS" /D "_UNICODE" /D "_AFXDLL" /D "_MBCS" /Fp"$(INTDIR)\chkbook.pch" /Yu"Stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 

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
RSC_PROJ=/l 0x409 /fo"$(INTDIR)\chkbook.res" /d "NDEBUG" /d "_AFXDLL" 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\chkbook.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
LINK32_FLAGS=/nologo /entry:"wWinMainCRTStartup" /subsystem:windows /incremental:no /pdb:"$(OUTDIR)\chkbook.pdb" /machine:I386 /out:"$(OUTDIR)\chkbook.exe" 
LINK32_OBJS= \
	"$(INTDIR)\bookvw.obj" \
	"$(INTDIR)\checkdoc.obj" \
	"$(INTDIR)\checkvw.obj" \
	"$(INTDIR)\chkbkfrm.obj" \
	"$(INTDIR)\chkbook.obj" \
	"$(INTDIR)\dollcent.obj" \
	"$(INTDIR)\fxrecdoc.obj" \
	"$(INTDIR)\mainfrm.obj" \
	"$(INTDIR)\rowview.obj" \
	"$(INTDIR)\stdafx.obj" \
	"$(INTDIR)\chkbook.res"

"$(OUTDIR)\chkbook.exe" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ELSEIF  "$(CFG)" == "ChkBook - Win32 Unicode Debug"

OUTDIR=.\UniDebug
INTDIR=.\UniDebug
# Begin Custom Macros
OutDir=.\UniDebug
# End Custom Macros

ALL : "$(OUTDIR)\chkbook.exe"


CLEAN :
	-@erase "$(INTDIR)\bookvw.obj"
	-@erase "$(INTDIR)\checkdoc.obj"
	-@erase "$(INTDIR)\checkvw.obj"
	-@erase "$(INTDIR)\chkbkfrm.obj"
	-@erase "$(INTDIR)\chkbook.obj"
	-@erase "$(INTDIR)\chkbook.pch"
	-@erase "$(INTDIR)\chkbook.res"
	-@erase "$(INTDIR)\dollcent.obj"
	-@erase "$(INTDIR)\fxrecdoc.obj"
	-@erase "$(INTDIR)\mainfrm.obj"
	-@erase "$(INTDIR)\rowview.obj"
	-@erase "$(INTDIR)\stdafx.obj"
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(INTDIR)\vc60.pdb"
	-@erase "$(OUTDIR)\chkbook.exe"
	-@erase "$(OUTDIR)\chkbook.ilk"
	-@erase "$(OUTDIR)\chkbook.pdb"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP=cl.exe
CPP_PROJ=/nologo /MDd /W3 /Gm /GX /ZI /Od /D "_DEBUG" /D "WIN32" /D "_WINDOWS" /D "_UNICODE" /D "_AFXDLL" /D "_MBCS" /Fp"$(INTDIR)\chkbook.pch" /Yu"Stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 

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
RSC_PROJ=/l 0x409 /fo"$(INTDIR)\chkbook.res" /d "_DEBUG" /d "_AFXDLL" 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\chkbook.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
LINK32_FLAGS=/nologo /entry:"wWinMainCRTStartup" /subsystem:windows /incremental:yes /pdb:"$(OUTDIR)\chkbook.pdb" /debug /machine:I386 /out:"$(OUTDIR)\chkbook.exe" 
LINK32_OBJS= \
	"$(INTDIR)\bookvw.obj" \
	"$(INTDIR)\checkdoc.obj" \
	"$(INTDIR)\checkvw.obj" \
	"$(INTDIR)\chkbkfrm.obj" \
	"$(INTDIR)\chkbook.obj" \
	"$(INTDIR)\dollcent.obj" \
	"$(INTDIR)\fxrecdoc.obj" \
	"$(INTDIR)\mainfrm.obj" \
	"$(INTDIR)\rowview.obj" \
	"$(INTDIR)\stdafx.obj" \
	"$(INTDIR)\chkbook.res"

"$(OUTDIR)\chkbook.exe" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ENDIF 


!IF "$(NO_EXTERNAL_DEPS)" != "1"
!IF EXISTS("chkbook.dep")
!INCLUDE "chkbook.dep"
!ELSE 
!MESSAGE Warning: cannot find "chkbook.dep"
!ENDIF 
!ENDIF 


!IF "$(CFG)" == "ChkBook - Win32 Release" || "$(CFG)" == "ChkBook - Win32 Debug" || "$(CFG)" == "ChkBook - Win32 Unicode Release" || "$(CFG)" == "ChkBook - Win32 Unicode Debug"
SOURCE=.\bookvw.cpp

"$(INTDIR)\bookvw.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\chkbook.pch"


SOURCE=.\checkdoc.cpp

"$(INTDIR)\checkdoc.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\chkbook.pch"


SOURCE=.\checkvw.cpp

"$(INTDIR)\checkvw.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\chkbook.pch"


SOURCE=.\chkbkfrm.cpp

"$(INTDIR)\chkbkfrm.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\chkbook.pch"


SOURCE=.\chkbook.cpp

"$(INTDIR)\chkbook.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\chkbook.pch"


SOURCE=.\chkbook.rc

"$(INTDIR)\chkbook.res" : $(SOURCE) "$(INTDIR)"
	$(RSC) $(RSC_PROJ) $(SOURCE)


SOURCE=.\dollcent.cpp

"$(INTDIR)\dollcent.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\chkbook.pch"


SOURCE=.\fxrecdoc.cpp

"$(INTDIR)\fxrecdoc.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\chkbook.pch"


SOURCE=.\mainfrm.cpp

"$(INTDIR)\mainfrm.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\chkbook.pch"


SOURCE=.\rowview.cpp

"$(INTDIR)\rowview.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\chkbook.pch"


SOURCE=.\stdafx.cpp

!IF  "$(CFG)" == "ChkBook - Win32 Release"

CPP_SWITCHES=/nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /Fp"$(INTDIR)\chkbook.pch" /Yc"Stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 

"$(INTDIR)\stdafx.obj"	"$(INTDIR)\chkbook.pch" : $(SOURCE) "$(INTDIR)"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "ChkBook - Win32 Debug"

CPP_SWITCHES=/nologo /MDd /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /Fp"$(INTDIR)\chkbook.pch" /Yc"Stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 

"$(INTDIR)\stdafx.obj"	"$(INTDIR)\chkbook.pch" : $(SOURCE) "$(INTDIR)"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "ChkBook - Win32 Unicode Release"

CPP_SWITCHES=/nologo /MD /W3 /GX /O2 /D "NDEBUG" /D "WIN32" /D "_WINDOWS" /D "_UNICODE" /D "_AFXDLL" /D "_MBCS" /Fp"$(INTDIR)\chkbook.pch" /Yc"Stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 

"$(INTDIR)\stdafx.obj"	"$(INTDIR)\chkbook.pch" : $(SOURCE) "$(INTDIR)"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "ChkBook - Win32 Unicode Debug"

CPP_SWITCHES=/nologo /MDd /W3 /Gm /GX /ZI /Od /D "_DEBUG" /D "WIN32" /D "_WINDOWS" /D "_UNICODE" /D "_AFXDLL" /D "_MBCS" /Fp"$(INTDIR)\chkbook.pch" /Yc"Stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 

"$(INTDIR)\stdafx.obj"	"$(INTDIR)\chkbook.pch" : $(SOURCE) "$(INTDIR)"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ENDIF 


!ENDIF 

