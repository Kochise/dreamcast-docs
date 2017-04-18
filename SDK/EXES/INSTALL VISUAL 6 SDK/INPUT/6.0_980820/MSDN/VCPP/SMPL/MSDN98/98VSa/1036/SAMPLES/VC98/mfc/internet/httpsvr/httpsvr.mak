# Microsoft Developer Studio Generated NMAKE File, Based on httpsvr.dsp
!IF "$(CFG)" == ""
CFG=HttpSvr - Win32 Release
!MESSAGE No configuration specified. Defaulting to HttpSvr - Win32 Release.
!ENDIF 

!IF "$(CFG)" != "HttpSvr - Win32 Release" && "$(CFG)" != "HttpSvr - Win32 Debug"
!MESSAGE Invalid configuration "$(CFG)" specified.
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "httpsvr.mak" CFG="HttpSvr - Win32 Release"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "HttpSvr - Win32 Release" (based on "Win32 (x86) Application")
!MESSAGE "HttpSvr - Win32 Debug" (based on "Win32 (x86) Application")
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

!IF  "$(CFG)" == "HttpSvr - Win32 Release"

OUTDIR=.\Release
INTDIR=.\Release
# Begin Custom Macros
OutDir=.\.\Release
# End Custom Macros

ALL : "$(OUTDIR)\httpsvr.exe"


CLEAN :
	-@erase "$(INTDIR)\GenPage.obj"
	-@erase "$(INTDIR)\Http.obj"
	-@erase "$(INTDIR)\HttpDoc.obj"
	-@erase "$(INTDIR)\HttpSvr.obj"
	-@erase "$(INTDIR)\httpsvr.pch"
	-@erase "$(INTDIR)\HttpSvr.res"
	-@erase "$(INTDIR)\HttpView.obj"
	-@erase "$(INTDIR)\Listen.obj"
	-@erase "$(INTDIR)\MainFrm.obj"
	-@erase "$(INTDIR)\NamePage.obj"
	-@erase "$(INTDIR)\NoRoot.obj"
	-@erase "$(INTDIR)\ReqSock.obj"
	-@erase "$(INTDIR)\Request.obj"
	-@erase "$(INTDIR)\RootDlg.obj"
	-@erase "$(INTDIR)\RootPage.obj"
	-@erase "$(INTDIR)\StdAfx.obj"
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(OUTDIR)\httpsvr.exe"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP_PROJ=/nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /Fp"$(INTDIR)\httpsvr.pch" /Yu"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 
MTL_PROJ=/nologo /D "NDEBUG" /mktyplib203 /win32 
RSC_PROJ=/l 0x409 /fo"$(INTDIR)\HttpSvr.res" /d "NDEBUG" /d "_AFXDLL" 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\httpsvr.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
LINK32_FLAGS=/nologo /subsystem:windows /incremental:no /pdb:"$(OUTDIR)\httpsvr.pdb" /machine:I386 /out:"$(OUTDIR)\httpsvr.exe" 
LINK32_OBJS= \
	"$(INTDIR)\GenPage.obj" \
	"$(INTDIR)\Http.obj" \
	"$(INTDIR)\HttpDoc.obj" \
	"$(INTDIR)\HttpSvr.obj" \
	"$(INTDIR)\HttpView.obj" \
	"$(INTDIR)\Listen.obj" \
	"$(INTDIR)\MainFrm.obj" \
	"$(INTDIR)\NamePage.obj" \
	"$(INTDIR)\NoRoot.obj" \
	"$(INTDIR)\ReqSock.obj" \
	"$(INTDIR)\Request.obj" \
	"$(INTDIR)\RootDlg.obj" \
	"$(INTDIR)\RootPage.obj" \
	"$(INTDIR)\StdAfx.obj" \
	"$(INTDIR)\HttpSvr.res"

"$(OUTDIR)\httpsvr.exe" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ELSEIF  "$(CFG)" == "HttpSvr - Win32 Debug"

OUTDIR=.\Debug
INTDIR=.\Debug
# Begin Custom Macros
OutDir=.\.\Debug
# End Custom Macros

ALL : "$(OUTDIR)\httpsvr.exe" "$(OUTDIR)\httpsvr.bsc"


CLEAN :
	-@erase "$(INTDIR)\GenPage.obj"
	-@erase "$(INTDIR)\GenPage.sbr"
	-@erase "$(INTDIR)\Http.obj"
	-@erase "$(INTDIR)\Http.sbr"
	-@erase "$(INTDIR)\HttpDoc.obj"
	-@erase "$(INTDIR)\HttpDoc.sbr"
	-@erase "$(INTDIR)\HttpSvr.obj"
	-@erase "$(INTDIR)\httpsvr.pch"
	-@erase "$(INTDIR)\HttpSvr.res"
	-@erase "$(INTDIR)\HttpSvr.sbr"
	-@erase "$(INTDIR)\HttpView.obj"
	-@erase "$(INTDIR)\HttpView.sbr"
	-@erase "$(INTDIR)\Listen.obj"
	-@erase "$(INTDIR)\Listen.sbr"
	-@erase "$(INTDIR)\MainFrm.obj"
	-@erase "$(INTDIR)\MainFrm.sbr"
	-@erase "$(INTDIR)\NamePage.obj"
	-@erase "$(INTDIR)\NamePage.sbr"
	-@erase "$(INTDIR)\NoRoot.obj"
	-@erase "$(INTDIR)\NoRoot.sbr"
	-@erase "$(INTDIR)\ReqSock.obj"
	-@erase "$(INTDIR)\ReqSock.sbr"
	-@erase "$(INTDIR)\Request.obj"
	-@erase "$(INTDIR)\Request.sbr"
	-@erase "$(INTDIR)\RootDlg.obj"
	-@erase "$(INTDIR)\RootDlg.sbr"
	-@erase "$(INTDIR)\RootPage.obj"
	-@erase "$(INTDIR)\RootPage.sbr"
	-@erase "$(INTDIR)\StdAfx.obj"
	-@erase "$(INTDIR)\StdAfx.sbr"
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(INTDIR)\vc60.pdb"
	-@erase "$(OUTDIR)\httpsvr.bsc"
	-@erase "$(OUTDIR)\httpsvr.exe"
	-@erase "$(OUTDIR)\httpsvr.ilk"
	-@erase "$(OUTDIR)\httpsvr.pdb"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP_PROJ=/nologo /MDd /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /FR"$(INTDIR)\\" /Fp"$(INTDIR)\httpsvr.pch" /Yu"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 
MTL_PROJ=/nologo /D "_DEBUG" /mktyplib203 /win32 
RSC_PROJ=/l 0x409 /fo"$(INTDIR)\HttpSvr.res" /d "_DEBUG" /d "_AFXDLL" 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\httpsvr.bsc" 
BSC32_SBRS= \
	"$(INTDIR)\GenPage.sbr" \
	"$(INTDIR)\Http.sbr" \
	"$(INTDIR)\HttpDoc.sbr" \
	"$(INTDIR)\HttpSvr.sbr" \
	"$(INTDIR)\HttpView.sbr" \
	"$(INTDIR)\Listen.sbr" \
	"$(INTDIR)\MainFrm.sbr" \
	"$(INTDIR)\NamePage.sbr" \
	"$(INTDIR)\NoRoot.sbr" \
	"$(INTDIR)\ReqSock.sbr" \
	"$(INTDIR)\Request.sbr" \
	"$(INTDIR)\RootDlg.sbr" \
	"$(INTDIR)\RootPage.sbr" \
	"$(INTDIR)\StdAfx.sbr"

"$(OUTDIR)\httpsvr.bsc" : "$(OUTDIR)" $(BSC32_SBRS)
    $(BSC32) @<<
  $(BSC32_FLAGS) $(BSC32_SBRS)
<<

LINK32=link.exe
LINK32_FLAGS=/nologo /subsystem:windows /incremental:yes /pdb:"$(OUTDIR)\httpsvr.pdb" /debug /machine:I386 /out:"$(OUTDIR)\httpsvr.exe" 
LINK32_OBJS= \
	"$(INTDIR)\GenPage.obj" \
	"$(INTDIR)\Http.obj" \
	"$(INTDIR)\HttpDoc.obj" \
	"$(INTDIR)\HttpSvr.obj" \
	"$(INTDIR)\HttpView.obj" \
	"$(INTDIR)\Listen.obj" \
	"$(INTDIR)\MainFrm.obj" \
	"$(INTDIR)\NamePage.obj" \
	"$(INTDIR)\NoRoot.obj" \
	"$(INTDIR)\ReqSock.obj" \
	"$(INTDIR)\Request.obj" \
	"$(INTDIR)\RootDlg.obj" \
	"$(INTDIR)\RootPage.obj" \
	"$(INTDIR)\StdAfx.obj" \
	"$(INTDIR)\HttpSvr.res"

"$(OUTDIR)\httpsvr.exe" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
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
!IF EXISTS("httpsvr.dep")
!INCLUDE "httpsvr.dep"
!ELSE 
!MESSAGE Warning: cannot find "httpsvr.dep"
!ENDIF 
!ENDIF 


!IF "$(CFG)" == "HttpSvr - Win32 Release" || "$(CFG)" == "HttpSvr - Win32 Debug"
SOURCE=.\GenPage.cpp

!IF  "$(CFG)" == "HttpSvr - Win32 Release"


"$(INTDIR)\GenPage.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\httpsvr.pch"


!ELSEIF  "$(CFG)" == "HttpSvr - Win32 Debug"


"$(INTDIR)\GenPage.obj"	"$(INTDIR)\GenPage.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\httpsvr.pch"


!ENDIF 

SOURCE=.\Http.cpp

!IF  "$(CFG)" == "HttpSvr - Win32 Release"


"$(INTDIR)\Http.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\httpsvr.pch"


!ELSEIF  "$(CFG)" == "HttpSvr - Win32 Debug"


"$(INTDIR)\Http.obj"	"$(INTDIR)\Http.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\httpsvr.pch"


!ENDIF 

SOURCE=.\HttpDoc.cpp

!IF  "$(CFG)" == "HttpSvr - Win32 Release"


"$(INTDIR)\HttpDoc.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\httpsvr.pch"


!ELSEIF  "$(CFG)" == "HttpSvr - Win32 Debug"


"$(INTDIR)\HttpDoc.obj"	"$(INTDIR)\HttpDoc.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\httpsvr.pch"


!ENDIF 

SOURCE=.\HttpSvr.cpp

!IF  "$(CFG)" == "HttpSvr - Win32 Release"


"$(INTDIR)\HttpSvr.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\httpsvr.pch"


!ELSEIF  "$(CFG)" == "HttpSvr - Win32 Debug"


"$(INTDIR)\HttpSvr.obj"	"$(INTDIR)\HttpSvr.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\httpsvr.pch"


!ENDIF 

SOURCE=.\HttpSvr.rc

"$(INTDIR)\HttpSvr.res" : $(SOURCE) "$(INTDIR)"
	$(RSC) $(RSC_PROJ) $(SOURCE)


SOURCE=.\HttpView.cpp

!IF  "$(CFG)" == "HttpSvr - Win32 Release"


"$(INTDIR)\HttpView.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\httpsvr.pch"


!ELSEIF  "$(CFG)" == "HttpSvr - Win32 Debug"


"$(INTDIR)\HttpView.obj"	"$(INTDIR)\HttpView.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\httpsvr.pch"


!ENDIF 

SOURCE=.\Listen.cpp

!IF  "$(CFG)" == "HttpSvr - Win32 Release"


"$(INTDIR)\Listen.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\httpsvr.pch"


!ELSEIF  "$(CFG)" == "HttpSvr - Win32 Debug"


"$(INTDIR)\Listen.obj"	"$(INTDIR)\Listen.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\httpsvr.pch"


!ENDIF 

SOURCE=.\MainFrm.cpp

!IF  "$(CFG)" == "HttpSvr - Win32 Release"


"$(INTDIR)\MainFrm.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\httpsvr.pch"


!ELSEIF  "$(CFG)" == "HttpSvr - Win32 Debug"


"$(INTDIR)\MainFrm.obj"	"$(INTDIR)\MainFrm.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\httpsvr.pch"


!ENDIF 

SOURCE=.\NamePage.cpp

!IF  "$(CFG)" == "HttpSvr - Win32 Release"


"$(INTDIR)\NamePage.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\httpsvr.pch"


!ELSEIF  "$(CFG)" == "HttpSvr - Win32 Debug"


"$(INTDIR)\NamePage.obj"	"$(INTDIR)\NamePage.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\httpsvr.pch"


!ENDIF 

SOURCE=.\NoRoot.cpp

!IF  "$(CFG)" == "HttpSvr - Win32 Release"


"$(INTDIR)\NoRoot.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\httpsvr.pch"


!ELSEIF  "$(CFG)" == "HttpSvr - Win32 Debug"


"$(INTDIR)\NoRoot.obj"	"$(INTDIR)\NoRoot.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\httpsvr.pch"


!ENDIF 

SOURCE=.\ReqSock.cpp

!IF  "$(CFG)" == "HttpSvr - Win32 Release"


"$(INTDIR)\ReqSock.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\httpsvr.pch"


!ELSEIF  "$(CFG)" == "HttpSvr - Win32 Debug"


"$(INTDIR)\ReqSock.obj"	"$(INTDIR)\ReqSock.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\httpsvr.pch"


!ENDIF 

SOURCE=.\Request.cpp

!IF  "$(CFG)" == "HttpSvr - Win32 Release"


"$(INTDIR)\Request.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\httpsvr.pch"


!ELSEIF  "$(CFG)" == "HttpSvr - Win32 Debug"


"$(INTDIR)\Request.obj"	"$(INTDIR)\Request.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\httpsvr.pch"


!ENDIF 

SOURCE=.\RootDlg.cpp

!IF  "$(CFG)" == "HttpSvr - Win32 Release"


"$(INTDIR)\RootDlg.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\httpsvr.pch"


!ELSEIF  "$(CFG)" == "HttpSvr - Win32 Debug"


"$(INTDIR)\RootDlg.obj"	"$(INTDIR)\RootDlg.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\httpsvr.pch"


!ENDIF 

SOURCE=.\RootPage.cpp

!IF  "$(CFG)" == "HttpSvr - Win32 Release"


"$(INTDIR)\RootPage.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\httpsvr.pch"


!ELSEIF  "$(CFG)" == "HttpSvr - Win32 Debug"


"$(INTDIR)\RootPage.obj"	"$(INTDIR)\RootPage.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\httpsvr.pch"


!ENDIF 

SOURCE=.\StdAfx.cpp

!IF  "$(CFG)" == "HttpSvr - Win32 Release"

CPP_SWITCHES=/nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /Fp"$(INTDIR)\httpsvr.pch" /Yc"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 

"$(INTDIR)\StdAfx.obj"	"$(INTDIR)\httpsvr.pch" : $(SOURCE) "$(INTDIR)"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "HttpSvr - Win32 Debug"

CPP_SWITCHES=/nologo /MDd /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /FR"$(INTDIR)\\" /Fp"$(INTDIR)\httpsvr.pch" /Yc"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 

"$(INTDIR)\StdAfx.obj"	"$(INTDIR)\StdAfx.sbr"	"$(INTDIR)\httpsvr.pch" : $(SOURCE) "$(INTDIR)"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ENDIF 


!ENDIF 

