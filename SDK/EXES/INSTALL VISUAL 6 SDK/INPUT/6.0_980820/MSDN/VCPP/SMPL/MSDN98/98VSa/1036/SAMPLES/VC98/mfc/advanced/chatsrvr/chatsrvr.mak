# Microsoft Developer Studio Generated NMAKE File, Based on chatsrvr.dsp
!IF "$(CFG)" == ""
CFG=ChatSrvr - Win32 Release
!MESSAGE No configuration specified. Defaulting to ChatSrvr - Win32 Release.
!ENDIF 

!IF "$(CFG)" != "ChatSrvr - Win32 Release" && "$(CFG)" != "ChatSrvr - Win32 Debug" && "$(CFG)" != "ChatSrvr - Win32 Unicode Release" && "$(CFG)" != "ChatSrvr - Win32 Unicode Debug"
!MESSAGE Invalid configuration "$(CFG)" specified.
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "chatsrvr.mak" CFG="ChatSrvr - Win32 Release"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "ChatSrvr - Win32 Release" (based on "Win32 (x86) Application")
!MESSAGE "ChatSrvr - Win32 Debug" (based on "Win32 (x86) Application")
!MESSAGE "ChatSrvr - Win32 Unicode Release" (based on "Win32 (x86) Application")
!MESSAGE "ChatSrvr - Win32 Unicode Debug" (based on "Win32 (x86) Application")
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

!IF  "$(CFG)" == "ChatSrvr - Win32 Release"

OUTDIR=.\Release
INTDIR=.\Release
# Begin Custom Macros
OutDir=.\.\Release
# End Custom Macros

ALL : "$(OUTDIR)\chatsrvr.exe"


CLEAN :
	-@erase "$(INTDIR)\Chatsrvr.obj"
	-@erase "$(INTDIR)\chatsrvr.pch"
	-@erase "$(INTDIR)\Chatsrvr.res"
	-@erase "$(INTDIR)\Clntsock.obj"
	-@erase "$(INTDIR)\Dialogs.obj"
	-@erase "$(INTDIR)\Lstnsock.obj"
	-@erase "$(INTDIR)\Mainfrm.obj"
	-@erase "$(INTDIR)\Msg.obj"
	-@erase "$(INTDIR)\Srvrdoc.obj"
	-@erase "$(INTDIR)\Srvrvw.obj"
	-@erase "$(INTDIR)\Stdafx.obj"
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(OUTDIR)\chatsrvr.exe"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP_PROJ=/nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /Fp"$(INTDIR)\chatsrvr.pch" /Yu"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 
MTL_PROJ=/nologo /D "NDEBUG" /mktyplib203 /win32 
RSC_PROJ=/l 0x409 /fo"$(INTDIR)\Chatsrvr.res" /d "NDEBUG" /d "_AFXDLL" 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\chatsrvr.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
LINK32_FLAGS=/nologo /subsystem:windows /incremental:no /pdb:"$(OUTDIR)\chatsrvr.pdb" /machine:I386 /out:"$(OUTDIR)\chatsrvr.exe" 
LINK32_OBJS= \
	"$(INTDIR)\Chatsrvr.obj" \
	"$(INTDIR)\Clntsock.obj" \
	"$(INTDIR)\Dialogs.obj" \
	"$(INTDIR)\Lstnsock.obj" \
	"$(INTDIR)\Mainfrm.obj" \
	"$(INTDIR)\Msg.obj" \
	"$(INTDIR)\Srvrdoc.obj" \
	"$(INTDIR)\Srvrvw.obj" \
	"$(INTDIR)\Stdafx.obj" \
	"$(INTDIR)\Chatsrvr.res"

"$(OUTDIR)\chatsrvr.exe" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ELSEIF  "$(CFG)" == "ChatSrvr - Win32 Debug"

OUTDIR=.\Debug
INTDIR=.\Debug
# Begin Custom Macros
OutDir=.\.\Debug
# End Custom Macros

ALL : "$(OUTDIR)\chatsrvr.exe"


CLEAN :
	-@erase "$(INTDIR)\Chatsrvr.obj"
	-@erase "$(INTDIR)\chatsrvr.pch"
	-@erase "$(INTDIR)\Chatsrvr.res"
	-@erase "$(INTDIR)\Clntsock.obj"
	-@erase "$(INTDIR)\Dialogs.obj"
	-@erase "$(INTDIR)\Lstnsock.obj"
	-@erase "$(INTDIR)\Mainfrm.obj"
	-@erase "$(INTDIR)\Msg.obj"
	-@erase "$(INTDIR)\Srvrdoc.obj"
	-@erase "$(INTDIR)\Srvrvw.obj"
	-@erase "$(INTDIR)\Stdafx.obj"
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(INTDIR)\vc60.pdb"
	-@erase "$(OUTDIR)\chatsrvr.exe"
	-@erase "$(OUTDIR)\chatsrvr.ilk"
	-@erase "$(OUTDIR)\chatsrvr.pdb"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP_PROJ=/nologo /MDd /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /Fp"$(INTDIR)\chatsrvr.pch" /Yu"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 
MTL_PROJ=/nologo /D "_DEBUG" /mktyplib203 /win32 
RSC_PROJ=/l 0x409 /fo"$(INTDIR)\Chatsrvr.res" /d "_DEBUG" /d "_AFXDLL" 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\chatsrvr.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
LINK32_FLAGS=/nologo /subsystem:windows /incremental:yes /pdb:"$(OUTDIR)\chatsrvr.pdb" /debug /machine:I386 /out:"$(OUTDIR)\chatsrvr.exe" 
LINK32_OBJS= \
	"$(INTDIR)\Chatsrvr.obj" \
	"$(INTDIR)\Clntsock.obj" \
	"$(INTDIR)\Dialogs.obj" \
	"$(INTDIR)\Lstnsock.obj" \
	"$(INTDIR)\Mainfrm.obj" \
	"$(INTDIR)\Msg.obj" \
	"$(INTDIR)\Srvrdoc.obj" \
	"$(INTDIR)\Srvrvw.obj" \
	"$(INTDIR)\Stdafx.obj" \
	"$(INTDIR)\Chatsrvr.res"

"$(OUTDIR)\chatsrvr.exe" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ELSEIF  "$(CFG)" == "ChatSrvr - Win32 Unicode Release"

OUTDIR=.\UniRelease
INTDIR=.\UniRelease
# Begin Custom Macros
OutDir=.\.\UniRelease
# End Custom Macros

ALL : "$(OUTDIR)\chatsrvr.exe"


CLEAN :
	-@erase "$(INTDIR)\Chatsrvr.obj"
	-@erase "$(INTDIR)\chatsrvr.pch"
	-@erase "$(INTDIR)\Chatsrvr.res"
	-@erase "$(INTDIR)\Clntsock.obj"
	-@erase "$(INTDIR)\Dialogs.obj"
	-@erase "$(INTDIR)\Lstnsock.obj"
	-@erase "$(INTDIR)\Mainfrm.obj"
	-@erase "$(INTDIR)\Msg.obj"
	-@erase "$(INTDIR)\Srvrdoc.obj"
	-@erase "$(INTDIR)\Srvrvw.obj"
	-@erase "$(INTDIR)\Stdafx.obj"
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(OUTDIR)\chatsrvr.exe"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP_PROJ=/nologo /MD /W3 /GX /O2 /D "NDEBUG" /D "WIN32" /D "_WINDOWS" /D "_UNICODE" /D "_AFXDLL" /D "_MBCS" /Fp"$(INTDIR)\chatsrvr.pch" /Yu"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 
MTL_PROJ=/nologo /D "NDEBUG" /mktyplib203 /win32 
RSC_PROJ=/l 0x409 /fo"$(INTDIR)\Chatsrvr.res" /d "NDEBUG" /d "_AFXDLL" 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\chatsrvr.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
LINK32_FLAGS=/nologo /entry:"wWinMainCRTStartup" /subsystem:windows /incremental:no /pdb:"$(OUTDIR)\chatsrvr.pdb" /machine:I386 /out:"$(OUTDIR)\chatsrvr.exe" 
LINK32_OBJS= \
	"$(INTDIR)\Chatsrvr.obj" \
	"$(INTDIR)\Clntsock.obj" \
	"$(INTDIR)\Dialogs.obj" \
	"$(INTDIR)\Lstnsock.obj" \
	"$(INTDIR)\Mainfrm.obj" \
	"$(INTDIR)\Msg.obj" \
	"$(INTDIR)\Srvrdoc.obj" \
	"$(INTDIR)\Srvrvw.obj" \
	"$(INTDIR)\Stdafx.obj" \
	"$(INTDIR)\Chatsrvr.res"

"$(OUTDIR)\chatsrvr.exe" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ELSEIF  "$(CFG)" == "ChatSrvr - Win32 Unicode Debug"

OUTDIR=.\UniDebug
INTDIR=.\UniDebug
# Begin Custom Macros
OutDir=.\.\UniDebug
# End Custom Macros

ALL : "$(OUTDIR)\chatsrvr.exe"


CLEAN :
	-@erase "$(INTDIR)\Chatsrvr.obj"
	-@erase "$(INTDIR)\chatsrvr.pch"
	-@erase "$(INTDIR)\Chatsrvr.res"
	-@erase "$(INTDIR)\Clntsock.obj"
	-@erase "$(INTDIR)\Dialogs.obj"
	-@erase "$(INTDIR)\Lstnsock.obj"
	-@erase "$(INTDIR)\Mainfrm.obj"
	-@erase "$(INTDIR)\Msg.obj"
	-@erase "$(INTDIR)\Srvrdoc.obj"
	-@erase "$(INTDIR)\Srvrvw.obj"
	-@erase "$(INTDIR)\Stdafx.obj"
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(INTDIR)\vc60.pdb"
	-@erase "$(OUTDIR)\chatsrvr.exe"
	-@erase "$(OUTDIR)\chatsrvr.ilk"
	-@erase "$(OUTDIR)\chatsrvr.pdb"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP_PROJ=/nologo /MDd /W3 /Gm /GX /ZI /Od /D "_DEBUG" /D "WIN32" /D "_WINDOWS" /D "_UNICODE" /D "_AFXDLL" /D "_MBCS" /Fp"$(INTDIR)\chatsrvr.pch" /Yu"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 
MTL_PROJ=/nologo /D "_DEBUG" /mktyplib203 /win32 
RSC_PROJ=/l 0x409 /fo"$(INTDIR)\Chatsrvr.res" /d "_DEBUG" /d "_AFXDLL" 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\chatsrvr.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
LINK32_FLAGS=/nologo /entry:"wWinMainCRTStartup" /subsystem:windows /incremental:yes /pdb:"$(OUTDIR)\chatsrvr.pdb" /debug /machine:I386 /out:"$(OUTDIR)\chatsrvr.exe" 
LINK32_OBJS= \
	"$(INTDIR)\Chatsrvr.obj" \
	"$(INTDIR)\Clntsock.obj" \
	"$(INTDIR)\Dialogs.obj" \
	"$(INTDIR)\Lstnsock.obj" \
	"$(INTDIR)\Mainfrm.obj" \
	"$(INTDIR)\Msg.obj" \
	"$(INTDIR)\Srvrdoc.obj" \
	"$(INTDIR)\Srvrvw.obj" \
	"$(INTDIR)\Stdafx.obj" \
	"$(INTDIR)\Chatsrvr.res"

"$(OUTDIR)\chatsrvr.exe" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
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
!IF EXISTS("chatsrvr.dep")
!INCLUDE "chatsrvr.dep"
!ELSE 
!MESSAGE Warning: cannot find "chatsrvr.dep"
!ENDIF 
!ENDIF 


!IF "$(CFG)" == "ChatSrvr - Win32 Release" || "$(CFG)" == "ChatSrvr - Win32 Debug" || "$(CFG)" == "ChatSrvr - Win32 Unicode Release" || "$(CFG)" == "ChatSrvr - Win32 Unicode Debug"
SOURCE=.\Chatsrvr.cpp

"$(INTDIR)\Chatsrvr.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\chatsrvr.pch"


SOURCE=.\Chatsrvr.rc

"$(INTDIR)\Chatsrvr.res" : $(SOURCE) "$(INTDIR)"
	$(RSC) $(RSC_PROJ) $(SOURCE)


SOURCE=.\Clntsock.cpp

"$(INTDIR)\Clntsock.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\chatsrvr.pch"


SOURCE=.\Dialogs.cpp

"$(INTDIR)\Dialogs.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\chatsrvr.pch"


SOURCE=.\Lstnsock.cpp

"$(INTDIR)\Lstnsock.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\chatsrvr.pch"


SOURCE=.\Mainfrm.cpp

"$(INTDIR)\Mainfrm.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\chatsrvr.pch"


SOURCE=.\Msg.cpp

"$(INTDIR)\Msg.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\chatsrvr.pch"


SOURCE=.\Srvrdoc.cpp

"$(INTDIR)\Srvrdoc.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\chatsrvr.pch"


SOURCE=.\Srvrvw.cpp

"$(INTDIR)\Srvrvw.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\chatsrvr.pch"


SOURCE=.\Stdafx.cpp

!IF  "$(CFG)" == "ChatSrvr - Win32 Release"

CPP_SWITCHES=/nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /Fp"$(INTDIR)\chatsrvr.pch" /Yc"Stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 

"$(INTDIR)\Stdafx.obj"	"$(INTDIR)\chatsrvr.pch" : $(SOURCE) "$(INTDIR)"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "ChatSrvr - Win32 Debug"

CPP_SWITCHES=/nologo /MDd /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /Fp"$(INTDIR)\chatsrvr.pch" /Yc"Stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 

"$(INTDIR)\Stdafx.obj"	"$(INTDIR)\chatsrvr.pch" : $(SOURCE) "$(INTDIR)"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "ChatSrvr - Win32 Unicode Release"

CPP_SWITCHES=/nologo /MD /W3 /GX /O2 /D "NDEBUG" /D "WIN32" /D "_WINDOWS" /D "_UNICODE" /D "_AFXDLL" /D "_MBCS" /Fp"$(INTDIR)\chatsrvr.pch" /Yc /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 

"$(INTDIR)\Stdafx.obj"	"$(INTDIR)\chatsrvr.pch" : $(SOURCE) "$(INTDIR)"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "ChatSrvr - Win32 Unicode Debug"

CPP_SWITCHES=/nologo /MDd /W3 /Gm /GX /ZI /Od /D "_DEBUG" /D "WIN32" /D "_WINDOWS" /D "_UNICODE" /D "_AFXDLL" /D "_MBCS" /Fp"$(INTDIR)\chatsrvr.pch" /Yc"Stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 

"$(INTDIR)\Stdafx.obj"	"$(INTDIR)\chatsrvr.pch" : $(SOURCE) "$(INTDIR)"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ENDIF 


!ENDIF 

