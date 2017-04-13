# Microsoft Developer Studio Generated NMAKE File, Based on HierWiz.dsp
!IF "$(CFG)" == ""
CFG=hierwiz - Win32 Release
!MESSAGE No configuration specified. Defaulting to hierwiz - Win32 Release.
!ENDIF 

!IF "$(CFG)" != "hierwiz - Win32 Release" && "$(CFG)" != "hierwiz - Win32 Pseudo-Debug"
!MESSAGE Invalid configuration "$(CFG)" specified.
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "HierWiz.mak" CFG="hierwiz - Win32 Release"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "hierwiz - Win32 Release" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE "hierwiz - Win32 Pseudo-Debug" (based on "Win32 (x86) Dynamic-Link Library")
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

!IF  "$(CFG)" == "hierwiz - Win32 Release"

OUTDIR=.\Release
INTDIR=.\Release
# Begin Custom Macros
OutDir=.\.\Release
# End Custom Macros

ALL : "$(OUTDIR)\hierwiz.awx" "$(OUTDIR)\HierWiz.bsc" "C:\PROGRAM FILES\MICROSOFT VISUAL STUDIO\COMMON\MSDEV98\Template\hierwiz.awx"


CLEAN :
	-@erase "$(INTDIR)\chooser.obj"
	-@erase "$(INTDIR)\chooser.sbr"
	-@erase "$(INTDIR)\cstm1dlg.obj"
	-@erase "$(INTDIR)\cstm1dlg.sbr"
	-@erase "$(INTDIR)\debug.obj"
	-@erase "$(INTDIR)\debug.sbr"
	-@erase "$(INTDIR)\editdlg.obj"
	-@erase "$(INTDIR)\editdlg.sbr"
	-@erase "$(INTDIR)\hierwaw.obj"
	-@erase "$(INTDIR)\hierwaw.sbr"
	-@erase "$(INTDIR)\hierwiz.obj"
	-@erase "$(INTDIR)\HierWiz.pch"
	-@erase "$(INTDIR)\hierwiz.res"
	-@erase "$(INTDIR)\hierwiz.sbr"
	-@erase "$(INTDIR)\loadfile.obj"
	-@erase "$(INTDIR)\loadfile.sbr"
	-@erase "$(INTDIR)\stdafx.obj"
	-@erase "$(INTDIR)\stdafx.sbr"
	-@erase "$(INTDIR)\usreditc.obj"
	-@erase "$(INTDIR)\usreditc.sbr"
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(OUTDIR)\hierwiz.awx"
	-@erase "$(OUTDIR)\HierWiz.bsc"
	-@erase "$(OUTDIR)\hierwiz.exp"
	-@erase "$(OUTDIR)\hierwiz.lib"
	-@erase "C:\PROGRAM FILES\MICROSOFT VISUAL STUDIO\COMMON\MSDEV98\Template\hierwiz.awx"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP_PROJ=/nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /FR"$(INTDIR)\\" /Fp"$(INTDIR)\HierWiz.pch" /Yu"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 
RSC_PROJ=/l 0x409 /fo"$(INTDIR)\hierwiz.res" /d "NDEBUG" /d "_AFXDLL" 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\HierWiz.bsc" 
BSC32_SBRS= \
	"$(INTDIR)\chooser.sbr" \
	"$(INTDIR)\cstm1dlg.sbr" \
	"$(INTDIR)\debug.sbr" \
	"$(INTDIR)\editdlg.sbr" \
	"$(INTDIR)\hierwaw.sbr" \
	"$(INTDIR)\hierwiz.sbr" \
	"$(INTDIR)\loadfile.sbr" \
	"$(INTDIR)\stdafx.sbr" \
	"$(INTDIR)\usreditc.sbr"

"$(OUTDIR)\HierWiz.bsc" : "$(OUTDIR)" $(BSC32_SBRS)
    $(BSC32) @<<
  $(BSC32_FLAGS) $(BSC32_SBRS)
<<

LINK32=link.exe
LINK32_FLAGS=/nologo /subsystem:windows /dll /incremental:no /pdb:"$(OUTDIR)\hierwiz.pdb" /machine:I386 /out:"$(OUTDIR)\hierwiz.awx" /implib:"$(OUTDIR)\hierwiz.lib" 
LINK32_OBJS= \
	"$(INTDIR)\chooser.obj" \
	"$(INTDIR)\cstm1dlg.obj" \
	"$(INTDIR)\debug.obj" \
	"$(INTDIR)\editdlg.obj" \
	"$(INTDIR)\hierwaw.obj" \
	"$(INTDIR)\hierwiz.obj" \
	"$(INTDIR)\loadfile.obj" \
	"$(INTDIR)\stdafx.obj" \
	"$(INTDIR)\usreditc.obj" \
	"$(INTDIR)\hierwiz.res"

"$(OUTDIR)\hierwiz.awx" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

OutDir=.\.\Release
TargetPath=.\Release\hierwiz.awx
TargetName=hierwiz
InputPath=.\Release\hierwiz.awx
SOURCE=$(InputPath)

"$(MSDEVDIR)\Template\$(TargetName).awx"	 : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	<<tempfile.bat 
	@echo off 
	if not exist $(MSDEVDIR)\Template\nul md $(MSDEVDIR)\Template 
	copy "$(TargetPath)" "$(MSDEVDIR)\Template" 
	if exist "$(OutDir)\$(TargetName).pdb" copy "$(OutDir)\$(TargetName).pdb"      "$(MSDEVDIR)\Template" 
<< 
	

!ELSEIF  "$(CFG)" == "hierwiz - Win32 Pseudo-Debug"

OUTDIR=.\Debug
INTDIR=.\Debug
# Begin Custom Macros
OutDir=.\.\Debug
# End Custom Macros

ALL : "$(OUTDIR)\hierwiz.awx" "$(OUTDIR)\HierWiz.bsc" "C:\PROGRAM FILES\MICROSOFT VISUAL STUDIO\COMMON\MSDEV98\Template\hierwiz.awx"


CLEAN :
	-@erase "$(INTDIR)\chooser.obj"
	-@erase "$(INTDIR)\chooser.sbr"
	-@erase "$(INTDIR)\cstm1dlg.obj"
	-@erase "$(INTDIR)\cstm1dlg.sbr"
	-@erase "$(INTDIR)\debug.obj"
	-@erase "$(INTDIR)\debug.sbr"
	-@erase "$(INTDIR)\editdlg.obj"
	-@erase "$(INTDIR)\editdlg.sbr"
	-@erase "$(INTDIR)\hierwaw.obj"
	-@erase "$(INTDIR)\hierwaw.sbr"
	-@erase "$(INTDIR)\hierwiz.obj"
	-@erase "$(INTDIR)\HierWiz.pch"
	-@erase "$(INTDIR)\hierwiz.res"
	-@erase "$(INTDIR)\hierwiz.sbr"
	-@erase "$(INTDIR)\loadfile.obj"
	-@erase "$(INTDIR)\loadfile.sbr"
	-@erase "$(INTDIR)\stdafx.obj"
	-@erase "$(INTDIR)\stdafx.sbr"
	-@erase "$(INTDIR)\usreditc.obj"
	-@erase "$(INTDIR)\usreditc.sbr"
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(INTDIR)\vc60.pdb"
	-@erase "$(OUTDIR)\hierwiz.awx"
	-@erase "$(OUTDIR)\HierWiz.bsc"
	-@erase "$(OUTDIR)\hierwiz.exp"
	-@erase "$(OUTDIR)\hierwiz.lib"
	-@erase "$(OUTDIR)\hierwiz.pdb"
	-@erase "C:\PROGRAM FILES\MICROSOFT VISUAL STUDIO\COMMON\MSDEV98\Template\hierwiz.awx"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP_PROJ=/nologo /MD /W3 /GX /ZI /Od /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_PSEUDO_DEBUG" /D "_AFXDLL" /D "_MBCS" /FR"$(INTDIR)\\" /Fp"$(INTDIR)\HierWiz.pch" /Yu"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 
RSC_PROJ=/l 0x409 /fo"$(INTDIR)\hierwiz.res" /d "NDEBUG" /d "_PSEUDO_DEBUG" /d "_AFXDLL" 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\HierWiz.bsc" 
BSC32_SBRS= \
	"$(INTDIR)\chooser.sbr" \
	"$(INTDIR)\cstm1dlg.sbr" \
	"$(INTDIR)\debug.sbr" \
	"$(INTDIR)\editdlg.sbr" \
	"$(INTDIR)\hierwaw.sbr" \
	"$(INTDIR)\hierwiz.sbr" \
	"$(INTDIR)\loadfile.sbr" \
	"$(INTDIR)\stdafx.sbr" \
	"$(INTDIR)\usreditc.sbr"

"$(OUTDIR)\HierWiz.bsc" : "$(OUTDIR)" $(BSC32_SBRS)
    $(BSC32) @<<
  $(BSC32_FLAGS) $(BSC32_SBRS)
<<

LINK32=link.exe
LINK32_FLAGS=/nologo /subsystem:windows /dll /incremental:no /pdb:"$(OUTDIR)\hierwiz.pdb" /debug /machine:I386 /out:"$(OUTDIR)\hierwiz.awx" /implib:"$(OUTDIR)\hierwiz.lib" 
LINK32_OBJS= \
	"$(INTDIR)\chooser.obj" \
	"$(INTDIR)\cstm1dlg.obj" \
	"$(INTDIR)\debug.obj" \
	"$(INTDIR)\editdlg.obj" \
	"$(INTDIR)\hierwaw.obj" \
	"$(INTDIR)\hierwiz.obj" \
	"$(INTDIR)\loadfile.obj" \
	"$(INTDIR)\stdafx.obj" \
	"$(INTDIR)\usreditc.obj" \
	"$(INTDIR)\hierwiz.res"

"$(OUTDIR)\hierwiz.awx" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

OutDir=.\.\Debug
TargetPath=.\Debug\hierwiz.awx
TargetName=hierwiz
InputPath=.\Debug\hierwiz.awx
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
!IF EXISTS("HierWiz.dep")
!INCLUDE "HierWiz.dep"
!ELSE 
!MESSAGE Warning: cannot find "HierWiz.dep"
!ENDIF 
!ENDIF 


!IF "$(CFG)" == "hierwiz - Win32 Release" || "$(CFG)" == "hierwiz - Win32 Pseudo-Debug"
SOURCE=.\chooser.cpp

"$(INTDIR)\chooser.obj"	"$(INTDIR)\chooser.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\HierWiz.pch"


SOURCE=.\cstm1dlg.cpp

"$(INTDIR)\cstm1dlg.obj"	"$(INTDIR)\cstm1dlg.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\HierWiz.pch"


SOURCE=.\debug.cpp

"$(INTDIR)\debug.obj"	"$(INTDIR)\debug.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\HierWiz.pch"


SOURCE=.\editdlg.cpp

"$(INTDIR)\editdlg.obj"	"$(INTDIR)\editdlg.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\HierWiz.pch"


SOURCE=.\hierwaw.cpp

"$(INTDIR)\hierwaw.obj"	"$(INTDIR)\hierwaw.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\HierWiz.pch"


SOURCE=.\hierwiz.cpp

"$(INTDIR)\hierwiz.obj"	"$(INTDIR)\hierwiz.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\HierWiz.pch"


SOURCE=.\hierwiz.rc

"$(INTDIR)\hierwiz.res" : $(SOURCE) "$(INTDIR)"
	$(RSC) $(RSC_PROJ) $(SOURCE)


SOURCE=.\loadfile.cpp

"$(INTDIR)\loadfile.obj"	"$(INTDIR)\loadfile.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\HierWiz.pch"


SOURCE=.\stdafx.cpp

!IF  "$(CFG)" == "hierwiz - Win32 Release"

CPP_SWITCHES=/nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /FR"$(INTDIR)\\" /Fp"$(INTDIR)\HierWiz.pch" /Yc"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 

"$(INTDIR)\stdafx.obj"	"$(INTDIR)\stdafx.sbr"	"$(INTDIR)\HierWiz.pch" : $(SOURCE) "$(INTDIR)"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "hierwiz - Win32 Pseudo-Debug"

CPP_SWITCHES=/nologo /MD /W3 /GX /ZI /Od /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_PSEUDO_DEBUG" /D "_AFXDLL" /D "_MBCS" /FR"$(INTDIR)\\" /Fp"$(INTDIR)\HierWiz.pch" /Yc"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 

"$(INTDIR)\stdafx.obj"	"$(INTDIR)\stdafx.sbr"	"$(INTDIR)\HierWiz.pch" : $(SOURCE) "$(INTDIR)"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ENDIF 

SOURCE=.\usreditc.cpp

"$(INTDIR)\usreditc.obj"	"$(INTDIR)\usreditc.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\HierWiz.pch"


SOURCE=.\template\ipframe.cpp
SOURCE=.\template\mainfrm.cpp
SOURCE=.\template\root.cpp
SOURCE=.\template\root.rc
SOURCE=.\template\stdafx.cpp
SOURCE=.\template\svrdoc.cpp
SOURCE=.\template\svritem.cpp
SOURCE=.\template\svrview.cpp
SOURCE=.\template\textview.cpp
SOURCE=.\template\zoomdlg.cpp

!ENDIF 

