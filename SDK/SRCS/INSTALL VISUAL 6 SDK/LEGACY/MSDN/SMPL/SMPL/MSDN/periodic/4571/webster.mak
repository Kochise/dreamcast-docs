# Microsoft Developer Studio Generated NMAKE File, Format Version 4.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Application" 0x0101

!IF "$(CFG)" == ""
CFG=Webster - Win32 Debug
!MESSAGE No configuration specified.  Defaulting to Webster - Win32 Debug.
!ENDIF 

!IF "$(CFG)" != "Webster - Win32 Release" && "$(CFG)" !=\
 "Webster - Win32 Debug"
!MESSAGE Invalid configuration "$(CFG)" specified.
!MESSAGE You can specify a configuration when running NMAKE on this makefile
!MESSAGE by defining the macro CFG on the command line.  For example:
!MESSAGE 
!MESSAGE NMAKE /f "WEBSTER.MAK" CFG="Webster - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "Webster - Win32 Release" (based on "Win32 (x86) Application")
!MESSAGE "Webster - Win32 Debug" (based on "Win32 (x86) Application")
!MESSAGE 
!ERROR An invalid configuration is specified.
!ENDIF 

!IF "$(OS)" == "Windows_NT"
NULL=
!ELSE 
NULL=nul
!ENDIF 
################################################################################
# Begin Project
# PROP Target_Last_Scanned "Webster - Win32 Debug"
RSC=rc.exe
MTL=mktyplib.exe
CPP=cl.exe
F90=fl32.exe

!IF  "$(CFG)" == "Webster - Win32 Release"

# PROP BASE Use_MFC 6
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "Release"
# PROP BASE Intermediate_Dir "Release"
# PROP BASE Target_Dir ""
# PROP Use_MFC 5
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "Release"
# PROP Intermediate_Dir "Release"
# PROP Target_Dir ""
OUTDIR=.\Release
INTDIR=.\Release

ALL : "$(OUTDIR)\WEBSTER.exe"

CLEAN : 
	-@erase ".\Release\WEBSTER.exe"
	-@erase ".\Release\WebDoc.obj"
	-@erase ".\Release\WEBSTER.pch"
	-@erase ".\Release\StdAfx.obj"
	-@erase ".\Release\cclient.obj"
	-@erase ".\Release\TrayNot.obj"
	-@erase ".\Release\WebView.obj"
	-@erase ".\Release\MainFrm.obj"
	-@erase ".\Release\Webster.obj"
	-@erase ".\Release\Splash.obj"
	-@erase ".\Release\Props.obj"
	-@erase ".\Release\service.obj"
	-@erase ".\Release\clisten.obj"
	-@erase ".\Release\Config.obj"
	-@erase ".\Release\Webster.res"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

# ADD BASE F90 /I "Release/"
# ADD F90 /I "Release/"
F90_OBJS=.\Release/
# ADD BASE CPP /nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /Yu"stdafx.h" /c
# ADD CPP /nologo /MT /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /Yu"stdafx.h" /c
CPP_PROJ=/nologo /MT /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D\
 "_MBCS" /Fp"$(INTDIR)/WEBSTER.pch" /Yu"stdafx.h" /Fo"$(INTDIR)/" /c 
CPP_OBJS=.\Release/
CPP_SBRS=
# ADD BASE MTL /nologo /D "NDEBUG" /win32
# ADD MTL /nologo /D "NDEBUG" /win32
MTL_PROJ=/nologo /D "NDEBUG" /win32 
# ADD BASE RSC /l 0x409 /d "NDEBUG" /d "_AFXDLL"
# ADD RSC /l 0x409 /d "NDEBUG"
RSC_PROJ=/l 0x409 /fo"$(INTDIR)/Webster.res" /d "NDEBUG" 
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
BSC32_FLAGS=/nologo /o"$(OUTDIR)/WEBSTER.bsc" 
BSC32_SBRS=
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /machine:I386
# ADD LINK32 winmm.lib /nologo /subsystem:windows /machine:I386
LINK32_FLAGS=winmm.lib /nologo /subsystem:windows /incremental:no\
 /pdb:"$(OUTDIR)/WEBSTER.pdb" /machine:I386 /out:"$(OUTDIR)/WEBSTER.exe" 
LINK32_OBJS= \
	".\Release\WebDoc.obj" \
	".\Release\StdAfx.obj" \
	".\Release\cclient.obj" \
	".\Release\TrayNot.obj" \
	".\Release\WebView.obj" \
	".\Release\MainFrm.obj" \
	".\Release\Webster.obj" \
	".\Release\Splash.obj" \
	".\Release\Props.obj" \
	".\Release\service.obj" \
	".\Release\clisten.obj" \
	".\Release\Config.obj" \
	".\Release\Webster.res"

"$(OUTDIR)\WEBSTER.exe" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ELSEIF  "$(CFG)" == "Webster - Win32 Debug"

# PROP BASE Use_MFC 6
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "Debug"
# PROP BASE Intermediate_Dir "Debug"
# PROP BASE Target_Dir ""
# PROP Use_MFC 5
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "Debug"
# PROP Intermediate_Dir "Debug"
# PROP Target_Dir ""
OUTDIR=.\Debug
INTDIR=.\Debug

ALL : "$(OUTDIR)\WEBSTER.exe"

CLEAN : 
	-@erase ".\Debug\vc40.pdb"
	-@erase ".\Debug\WEBSTER.pch"
	-@erase ".\Debug\vc40.idb"
	-@erase ".\Debug\WEBSTER.exe"
	-@erase ".\Debug\WebView.obj"
	-@erase ".\Debug\WebDoc.obj"
	-@erase ".\Debug\service.obj"
	-@erase ".\Debug\TrayNot.obj"
	-@erase ".\Debug\Props.obj"
	-@erase ".\Debug\MainFrm.obj"
	-@erase ".\Debug\Splash.obj"
	-@erase ".\Debug\Webster.obj"
	-@erase ".\Debug\clisten.obj"
	-@erase ".\Debug\Config.obj"
	-@erase ".\Debug\StdAfx.obj"
	-@erase ".\Debug\cclient.obj"
	-@erase ".\Debug\Webster.res"
	-@erase ".\Debug\WEBSTER.ilk"
	-@erase ".\Debug\WEBSTER.pdb"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

# ADD BASE F90 /I "Debug/"
# ADD F90 /I "Debug/"
F90_OBJS=.\Debug/
# ADD BASE CPP /nologo /MDd /W3 /Gm /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /Yu"stdafx.h" /c
# ADD CPP /nologo /MTd /W3 /Gm /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /Yu"stdafx.h" /c
CPP_PROJ=/nologo /MTd /W3 /Gm /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS"\
 /D "_MBCS" /Fp"$(INTDIR)/WEBSTER.pch" /Yu"stdafx.h" /Fo"$(INTDIR)/"\
 /Fd"$(INTDIR)/" /c 
CPP_OBJS=.\Debug/
CPP_SBRS=
# ADD BASE MTL /nologo /D "_DEBUG" /win32
# ADD MTL /nologo /D "_DEBUG" /win32
MTL_PROJ=/nologo /D "_DEBUG" /win32 
# ADD BASE RSC /l 0x409 /d "_DEBUG" /d "_AFXDLL"
# ADD RSC /l 0x409 /d "_DEBUG"
RSC_PROJ=/l 0x409 /fo"$(INTDIR)/Webster.res" /d "_DEBUG" 
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
BSC32_FLAGS=/nologo /o"$(OUTDIR)/WEBSTER.bsc" 
BSC32_SBRS=
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /debug /machine:I386
# ADD LINK32 winmm.lib /nologo /subsystem:windows /debug /machine:I386
LINK32_FLAGS=winmm.lib /nologo /subsystem:windows /incremental:yes\
 /pdb:"$(OUTDIR)/WEBSTER.pdb" /debug /machine:I386 /out:"$(OUTDIR)/WEBSTER.exe" 
LINK32_OBJS= \
	".\Debug\WebView.obj" \
	".\Debug\WebDoc.obj" \
	".\Debug\service.obj" \
	".\Debug\TrayNot.obj" \
	".\Debug\Props.obj" \
	".\Debug\MainFrm.obj" \
	".\Debug\Splash.obj" \
	".\Debug\Webster.obj" \
	".\Debug\clisten.obj" \
	".\Debug\Config.obj" \
	".\Debug\StdAfx.obj" \
	".\Debug\cclient.obj" \
	".\Debug\Webster.res"

"$(OUTDIR)\WEBSTER.exe" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ENDIF 

.c{$(CPP_OBJS)}.obj:
   $(CPP) $(CPP_PROJ) $<  

.cpp{$(CPP_OBJS)}.obj:
   $(CPP) $(CPP_PROJ) $<  

.cxx{$(CPP_OBJS)}.obj:
   $(CPP) $(CPP_PROJ) $<  

.c{$(CPP_SBRS)}.sbr:
   $(CPP) $(CPP_PROJ) $<  

.cpp{$(CPP_SBRS)}.sbr:
   $(CPP) $(CPP_PROJ) $<  

.cxx{$(CPP_SBRS)}.sbr:
   $(CPP) $(CPP_PROJ) $<  

F90_PROJ=/I "Release/" /Fo"Release/" 

.for{$(F90_OBJS)}.obj:
   $(F90) $(F90_PROJ) $<  

.f{$(F90_OBJS)}.obj:
   $(F90) $(F90_PROJ) $<  

.f90{$(F90_OBJS)}.obj:
   $(F90) $(F90_PROJ) $<  

################################################################################
# Begin Target

# Name "Webster - Win32 Release"
# Name "Webster - Win32 Debug"

!IF  "$(CFG)" == "Webster - Win32 Release"

!ELSEIF  "$(CFG)" == "Webster - Win32 Debug"

!ENDIF 

################################################################################
# Begin Source File

SOURCE=.\Webster.cpp
DEP_CPP_WEBST=\
	".\STDAFX.H"\
	".\WEBSTER.H"\
	".\MAINFRM.H"\
	".\WEBDOC.H"\
	".\WEBVIEW.H"\
	".\SPLASH.H"\
	".\PROPS.H"\
	".\CONFIG.H"\
	".\TRAYNOT.H"\
	".\LOGGER.H"\
	

"$(INTDIR)\Webster.obj" : $(SOURCE) $(DEP_CPP_WEBST) "$(INTDIR)"\
 "$(INTDIR)\WEBSTER.pch"


# End Source File
################################################################################
# Begin Source File

SOURCE=.\StdAfx.cpp
DEP_CPP_STDAF=\
	".\STDAFX.H"\
	

!IF  "$(CFG)" == "Webster - Win32 Release"

# ADD CPP /Yc"stdafx.h"

BuildCmds= \
	$(CPP) /nologo /MT /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS"\
 /Fp"$(INTDIR)/WEBSTER.pch" /Yc"stdafx.h" /Fo"$(INTDIR)/" /c $(SOURCE) \
	

"$(INTDIR)\StdAfx.obj" : $(SOURCE) $(DEP_CPP_STDAF) "$(INTDIR)"
   $(BuildCmds)

"$(INTDIR)\WEBSTER.pch" : $(SOURCE) $(DEP_CPP_STDAF) "$(INTDIR)"
   $(BuildCmds)

!ELSEIF  "$(CFG)" == "Webster - Win32 Debug"

# ADD CPP /Yc"stdafx.h"

BuildCmds= \
	$(CPP) /nologo /MTd /W3 /Gm /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS"\
 /D "_MBCS" /Fp"$(INTDIR)/WEBSTER.pch" /Yc"stdafx.h" /Fo"$(INTDIR)/"\
 /Fd"$(INTDIR)/" /c $(SOURCE) \
	

"$(INTDIR)\StdAfx.obj" : $(SOURCE) $(DEP_CPP_STDAF) "$(INTDIR)"
   $(BuildCmds)

"$(INTDIR)\WEBSTER.pch" : $(SOURCE) $(DEP_CPP_STDAF) "$(INTDIR)"
   $(BuildCmds)

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\MainFrm.cpp
DEP_CPP_MAINF=\
	".\STDAFX.H"\
	".\WEBSTER.H"\
	".\MAINFRM.H"\
	".\WEBDOC.H"\
	".\PROPS.H"\
	".\CONFIG.H"\
	".\TRAYNOT.H"\
	".\LOGGER.H"\
	

"$(INTDIR)\MainFrm.obj" : $(SOURCE) $(DEP_CPP_MAINF) "$(INTDIR)"\
 "$(INTDIR)\WEBSTER.pch"


# End Source File
################################################################################
# Begin Source File

SOURCE=.\WebDoc.cpp
DEP_CPP_WEBDO=\
	".\STDAFX.H"\
	".\WEBSTER.H"\
	".\WEBDOC.H"\
	".\WEBVIEW.H"\
	".\Clisten.h"\
	".\Cclient.h"\
	".\PROPS.H"\
	".\CONFIG.H"\
	".\LOGGER.H"\
	

"$(INTDIR)\WebDoc.obj" : $(SOURCE) $(DEP_CPP_WEBDO) "$(INTDIR)"\
 "$(INTDIR)\WEBSTER.pch"


# End Source File
################################################################################
# Begin Source File

SOURCE=.\WebView.cpp
DEP_CPP_WEBVI=\
	".\STDAFX.H"\
	".\WEBSTER.H"\
	".\WEBDOC.H"\
	".\WEBVIEW.H"\
	".\PROPS.H"\
	".\CONFIG.H"\
	".\LOGGER.H"\
	

"$(INTDIR)\WebView.obj" : $(SOURCE) $(DEP_CPP_WEBVI) "$(INTDIR)"\
 "$(INTDIR)\WEBSTER.pch"


# End Source File
################################################################################
# Begin Source File

SOURCE=.\Webster.rc
DEP_RSC_WEBSTE=\
	".\RES\Webster.ico"\
	".\res\Connect.ico"\
	".\res\Idle.ico"\
	".\res\Toolbar.bmp"\
	".\res\Webster.rc2"\
	

"$(INTDIR)\Webster.res" : $(SOURCE) $(DEP_RSC_WEBSTE) "$(INTDIR)"
   $(RSC) $(RSC_PROJ) $(SOURCE)


# End Source File
################################################################################
# Begin Source File

SOURCE=.\Props.cpp
DEP_CPP_PROPS=\
	".\STDAFX.H"\
	".\PROPS.H"\
	".\WEBSTER.H"\
	".\CONFIG.H"\
	

"$(INTDIR)\Props.obj" : $(SOURCE) $(DEP_CPP_PROPS) "$(INTDIR)"\
 "$(INTDIR)\WEBSTER.pch"


# End Source File
################################################################################
# Begin Source File

SOURCE=.\Config.cpp
DEP_CPP_CONFI=\
	".\STDAFX.H"\
	".\CONFIG.H"\
	

"$(INTDIR)\Config.obj" : $(SOURCE) $(DEP_CPP_CONFI) "$(INTDIR)"\
 "$(INTDIR)\WEBSTER.pch"


# End Source File
################################################################################
# Begin Source File

SOURCE=.\clisten.CPP
DEP_CPP_CLIST=\
	".\STDAFX.H"\
	".\Clisten.h"\
	".\WEBDOC.H"\
	".\LOGGER.H"\
	

"$(INTDIR)\clisten.obj" : $(SOURCE) $(DEP_CPP_CLIST) "$(INTDIR)"\
 "$(INTDIR)\WEBSTER.pch"


# End Source File
################################################################################
# Begin Source File

SOURCE=.\cclient.CPP
DEP_CPP_CCLIE=\
	".\STDAFX.H"\
	".\Cclient.h"\
	".\WEBDOC.H"\
	".\WEBSTER.H"\
	".\MAINFRM.H"\
	".\LOGGER.H"\
	".\PROPS.H"\
	".\CONFIG.H"\
	".\TRAYNOT.H"\
	

"$(INTDIR)\cclient.obj" : $(SOURCE) $(DEP_CPP_CCLIE) "$(INTDIR)"\
 "$(INTDIR)\WEBSTER.pch"


# End Source File
################################################################################
# Begin Source File

SOURCE=.\service.cpp
DEP_CPP_SERVI=\
	".\STDAFX.H"\
	".\Cclient.h"\
	".\WEBDOC.H"\
	".\WEBSTER.H"\
	".\MAINFRM.H"\
	".\LOGGER.H"\
	".\PROPS.H"\
	".\CONFIG.H"\
	".\TRAYNOT.H"\
	

"$(INTDIR)\service.obj" : $(SOURCE) $(DEP_CPP_SERVI) "$(INTDIR)"\
 "$(INTDIR)\WEBSTER.pch"


# End Source File
################################################################################
# Begin Source File

SOURCE=.\Splash.cpp
DEP_CPP_SPLAS=\
	".\STDAFX.H"\
	".\WEBSTER.H"\
	".\SPLASH.H"\
	".\PROPS.H"\
	".\CONFIG.H"\
	

"$(INTDIR)\Splash.obj" : $(SOURCE) $(DEP_CPP_SPLAS) "$(INTDIR)"\
 "$(INTDIR)\WEBSTER.pch"


# End Source File
################################################################################
# Begin Source File

SOURCE=.\TrayNot.cpp
DEP_CPP_TRAYN=\
	".\STDAFX.H"\
	".\TRAYNOT.H"\
	

"$(INTDIR)\TrayNot.obj" : $(SOURCE) $(DEP_CPP_TRAYN) "$(INTDIR)"\
 "$(INTDIR)\WEBSTER.pch"


# End Source File
# End Target
# End Project
################################################################################
