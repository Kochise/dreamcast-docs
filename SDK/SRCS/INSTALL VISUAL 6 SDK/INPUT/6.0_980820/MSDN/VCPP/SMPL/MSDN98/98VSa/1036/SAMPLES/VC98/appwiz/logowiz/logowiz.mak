# Microsoft Developer Studio Generated NMAKE File, Based on LogoWiz.dsp
!IF "$(CFG)" == ""
CFG=LogoWiz - Win32 Release
!MESSAGE No configuration specified. Defaulting to LogoWiz - Win32 Release.
!ENDIF 

!IF "$(CFG)" != "LogoWiz - Win32 Release" && "$(CFG)" != "LogoWiz - Win32 Pseudo-Debug"
!MESSAGE Invalid configuration "$(CFG)" specified.
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "LogoWiz.mak" CFG="LogoWiz - Win32 Release"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "LogoWiz - Win32 Release" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE "LogoWiz - Win32 Pseudo-Debug" (based on "Win32 (x86) Dynamic-Link Library")
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

!IF  "$(CFG)" == "LogoWiz - Win32 Release"

OUTDIR=.\Release
INTDIR=.\Release
# Begin Custom Macros
OutDir=.\.\Release
# End Custom Macros

ALL : "$(OUTDIR)\LogoWiz.awx" "C:\PROGRAM FILES\MICROSOFT VISUAL STUDIO\COMMON\MSDEV98\Template\LogoWiz.awx"


CLEAN :
	-@erase "$(INTDIR)\chooser.obj"
	-@erase "$(INTDIR)\cstm1dlg.obj"
	-@erase "$(INTDIR)\debug.obj"
	-@erase "$(INTDIR)\logowaw.obj"
	-@erase "$(INTDIR)\logowiz.obj"
	-@erase "$(INTDIR)\LogoWiz.pch"
	-@erase "$(INTDIR)\logowiz.res"
	-@erase "$(INTDIR)\stdafx.obj"
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(OUTDIR)\LogoWiz.awx"
	-@erase "$(OUTDIR)\LogoWiz.exp"
	-@erase "$(OUTDIR)\LogoWiz.lib"
	-@erase "C:\PROGRAM FILES\MICROSOFT VISUAL STUDIO\COMMON\MSDEV98\Template\LogoWiz.awx"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

F90=fl32.exe
CPP_PROJ=/nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /Fp"$(INTDIR)\LogoWiz.pch" /Yu"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 
RSC_PROJ=/l 0x409 /fo"$(INTDIR)\logowiz.res" /d "NDEBUG" /d "_AFXDLL" 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\LogoWiz.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
LINK32_FLAGS=/nologo /subsystem:windows /dll /incremental:no /pdb:"$(OUTDIR)\LogoWiz.pdb" /machine:I386 /out:"$(OUTDIR)\LogoWiz.awx" /implib:"$(OUTDIR)\LogoWiz.lib" 
LINK32_OBJS= \
	"$(INTDIR)\chooser.obj" \
	"$(INTDIR)\cstm1dlg.obj" \
	"$(INTDIR)\debug.obj" \
	"$(INTDIR)\logowaw.obj" \
	"$(INTDIR)\logowiz.obj" \
	"$(INTDIR)\stdafx.obj" \
	"$(INTDIR)\logowiz.res"

"$(OUTDIR)\LogoWiz.awx" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

OutDir=.\.\Release
TargetPath=.\Release\LogoWiz.awx
TargetName=LogoWiz
InputPath=.\Release\LogoWiz.awx
SOURCE=$(InputPath)

"$(MSDEVDIR)\Template\$(TargetName).awx"	 : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	<<tempfile.bat 
	@echo off 
	if not exist $(MSDEVDIR)\Template\nul md $(MSDEVDIR)\Template 
	copy "$(TargetPath)" "$(MSDEVDIR)\Template" 
	if exist "$(OutDir)\$(TargetName).pdb" copy "$(OutDir)\$(TargetName).pdb"      "$(MSDEVDIR)\Template" 
<< 
	

!ELSEIF  "$(CFG)" == "LogoWiz - Win32 Pseudo-Debug"

OUTDIR=.\Debug
INTDIR=.\Debug
# Begin Custom Macros
OutDir=.\.\Debug
# End Custom Macros

ALL : "$(OUTDIR)\LogoWiz.awx" "C:\PROGRAM FILES\MICROSOFT VISUAL STUDIO\COMMON\MSDEV98\Template\LogoWiz.awx"


CLEAN :
	-@erase "$(INTDIR)\chooser.obj"
	-@erase "$(INTDIR)\cstm1dlg.obj"
	-@erase "$(INTDIR)\debug.obj"
	-@erase "$(INTDIR)\logowaw.obj"
	-@erase "$(INTDIR)\logowiz.obj"
	-@erase "$(INTDIR)\LogoWiz.pch"
	-@erase "$(INTDIR)\logowiz.res"
	-@erase "$(INTDIR)\stdafx.obj"
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(INTDIR)\vc60.pdb"
	-@erase "$(OUTDIR)\LogoWiz.awx"
	-@erase "$(OUTDIR)\LogoWiz.exp"
	-@erase "$(OUTDIR)\LogoWiz.ilk"
	-@erase "$(OUTDIR)\LogoWiz.lib"
	-@erase "$(OUTDIR)\LogoWiz.pdb"
	-@erase "C:\PROGRAM FILES\MICROSOFT VISUAL STUDIO\COMMON\MSDEV98\Template\LogoWiz.awx"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

F90=fl32.exe
CPP_PROJ=/nologo /MD /W3 /Gm /GX /ZI /Od /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_PSEUDO_DEBUG" /D "_AFXDLL" /D "_MBCS" /Fp"$(INTDIR)\LogoWiz.pch" /Yu"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 
RSC_PROJ=/l 0x409 /fo"$(INTDIR)\logowiz.res" /d "NDEBUG" /d "_PSEUDO_DEBUG" /d "_AFXDLL" 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\LogoWiz.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
LINK32_FLAGS=/nologo /subsystem:windows /dll /incremental:yes /pdb:"$(OUTDIR)\LogoWiz.pdb" /debug /machine:I386 /out:"$(OUTDIR)\LogoWiz.awx" /implib:"$(OUTDIR)\LogoWiz.lib" 
LINK32_OBJS= \
	"$(INTDIR)\chooser.obj" \
	"$(INTDIR)\cstm1dlg.obj" \
	"$(INTDIR)\debug.obj" \
	"$(INTDIR)\logowaw.obj" \
	"$(INTDIR)\logowiz.obj" \
	"$(INTDIR)\stdafx.obj" \
	"$(INTDIR)\logowiz.res"

"$(OUTDIR)\LogoWiz.awx" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

OutDir=.\.\Debug
TargetPath=.\Debug\LogoWiz.awx
TargetName=LogoWiz
InputPath=.\Debug\LogoWiz.awx
SOURCE=$(InputPath)

"$(MSDEVDIR)\Template\$(TargetName).awx"	 : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	<<tempfile.bat 
	@echo off 
	if not exist $(MSDEVDIR)\Template\nul md $(MSDEVDIR)\Template 
	copy "$(TargetPath)" "$(MSDEVDIR)\Template" 
	if exist "$(OutDir)\$(TargetName).pdb" copy "$(OutDir)\$(TargetName).pdb"      "$(MSDEVDIR)\Template" 
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

MTL_PROJ=/nologo /D "NDEBUG" /mktyplib203 /win32 

!IF "$(NO_EXTERNAL_DEPS)" != "1"
!IF EXISTS("LogoWiz.dep")
!INCLUDE "LogoWiz.dep"
!ELSE 
!MESSAGE Warning: cannot find "LogoWiz.dep"
!ENDIF 
!ENDIF 


!IF "$(CFG)" == "LogoWiz - Win32 Release" || "$(CFG)" == "LogoWiz - Win32 Pseudo-Debug"
SOURCE=.\chooser.cpp

"$(INTDIR)\chooser.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\LogoWiz.pch"


SOURCE=.\cstm1dlg.cpp

"$(INTDIR)\cstm1dlg.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\LogoWiz.pch"


SOURCE=.\debug.cpp

"$(INTDIR)\debug.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\LogoWiz.pch"


SOURCE=.\logowaw.cpp

"$(INTDIR)\logowaw.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\LogoWiz.pch"


SOURCE=.\logowiz.cpp

"$(INTDIR)\logowiz.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\LogoWiz.pch"


SOURCE=.\logowiz.rc

"$(INTDIR)\logowiz.res" : $(SOURCE) "$(INTDIR)"
	$(RSC) $(RSC_PROJ) $(SOURCE)


SOURCE=.\stdafx.cpp

!IF  "$(CFG)" == "LogoWiz - Win32 Release"

CPP_SWITCHES=/nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /Fp"$(INTDIR)\LogoWiz.pch" /Yc"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 

"$(INTDIR)\stdafx.obj"	"$(INTDIR)\LogoWiz.pch" : $(SOURCE) "$(INTDIR)"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "LogoWiz - Win32 Pseudo-Debug"

CPP_SWITCHES=/nologo /MD /W3 /Gm /GX /ZI /Od /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_PSEUDO_DEBUG" /D "_AFXDLL" /D "_MBCS" /Fp"$(INTDIR)\LogoWiz.pch" /Yc"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 

"$(INTDIR)\stdafx.obj"	"$(INTDIR)\LogoWiz.pch" : $(SOURCE) "$(INTDIR)"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ENDIF 

SOURCE=.\TEMPLATE\dialog.cpp
SOURCE=.\TEMPLATE\dlgall.rc
SOURCE=.\TEMPLATE\DLGLOC.RC
SOURCE=.\TEMPLATE\pressdlg.cpp

!ENDIF 

