# Microsoft Developer Studio Generated NMAKE File, Format Version 4.20
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Application" 0x0101

!IF "$(CFG)" == ""
CFG=cliapp - Win32 Debug
!MESSAGE No configuration specified.  Defaulting to cliapp - Win32 Debug.
!ENDIF 

!IF "$(CFG)" != "cliapp - Win32 Release" && "$(CFG)" != "cliapp - Win32 Debug"
!MESSAGE Invalid configuration "$(CFG)" specified.
!MESSAGE You can specify a configuration when running NMAKE on this makefile
!MESSAGE by defining the macro CFG on the command line.  For example:
!MESSAGE 
!MESSAGE NMAKE /f "cliapp.mak" CFG="cliapp - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "cliapp - Win32 Release" (based on "Win32 (x86) Application")
!MESSAGE "cliapp - Win32 Debug" (based on "Win32 (x86) Application")
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
# PROP Target_Last_Scanned "cliapp - Win32 Debug"
CPP=cl.exe
RSC=rc.exe
MTL=mktyplib.exe

!IF  "$(CFG)" == "cliapp - Win32 Release"

# PROP BASE Use_MFC 6
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "Release"
# PROP BASE Intermediate_Dir "Release"
# PROP BASE Target_Dir ""
# PROP Use_MFC 6
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "Release"
# PROP Intermediate_Dir "Release"
# PROP Target_Dir ""
OUTDIR=.\Release
INTDIR=.\Release

ALL : "$(OUTDIR)\cliapp.exe"

CLEAN : 
	-@erase "$(INTDIR)\browsedi.obj"
	-@erase "$(INTDIR)\cfilemap.obj"
	-@erase "$(INTDIR)\cliapp.obj"
	-@erase "$(INTDIR)\cliapp.res"
	-@erase "$(INTDIR)\clidoc.obj"
	-@erase "$(INTDIR)\cliview.obj"
	-@erase "$(INTDIR)\cmutex.obj"
	-@erase "$(INTDIR)\comclass.obj"
	-@erase "$(INTDIR)\dbcode.obj"
	-@erase "$(INTDIR)\dbdialog.obj"
	-@erase "$(INTDIR)\easyview.obj"
	-@erase "$(INTDIR)\MainFrm.obj"
	-@erase "$(INTDIR)\npipe.obj"
	-@erase "$(INTDIR)\protocol.obj"
	-@erase "$(INTDIR)\StdAfx.obj"
	-@erase "$(OUTDIR)\cliapp.exe"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

# ADD BASE CPP /nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /Yu"stdafx.h" /c
# ADD CPP /nologo /MD /W3 /GX /O2 /I "..\common" /I "..\client" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /YX /c
CPP_PROJ=/nologo /MD /W3 /GX /O2 /I "..\common" /I "..\client" /D "WIN32" /D\
 "NDEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /Fp"$(INTDIR)/cliapp.pch" /YX\
 /Fo"$(INTDIR)/" /c 
CPP_OBJS=.\Release/
CPP_SBRS=.\.
# ADD BASE MTL /nologo /D "NDEBUG" /win32
# ADD MTL /nologo /D "NDEBUG" /win32
MTL_PROJ=/nologo /D "NDEBUG" /win32 
# ADD BASE RSC /l 0x409 /d "NDEBUG" /d "_AFXDLL"
# ADD RSC /l 0x409 /d "NDEBUG" /d "_AFXDLL"
RSC_PROJ=/l 0x409 /fo"$(INTDIR)/cliapp.res" /d "NDEBUG" /d "_AFXDLL" 
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
BSC32_FLAGS=/nologo /o"$(OUTDIR)/cliapp.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /machine:I386
# ADD LINK32 /nologo /subsystem:windows /machine:I386
LINK32_FLAGS=/nologo /subsystem:windows /incremental:no\
 /pdb:"$(OUTDIR)/cliapp.pdb" /machine:I386 /out:"$(OUTDIR)/cliapp.exe" 
LINK32_OBJS= \
	"$(INTDIR)\browsedi.obj" \
	"$(INTDIR)\cfilemap.obj" \
	"$(INTDIR)\cliapp.obj" \
	"$(INTDIR)\cliapp.res" \
	"$(INTDIR)\clidoc.obj" \
	"$(INTDIR)\cliview.obj" \
	"$(INTDIR)\cmutex.obj" \
	"$(INTDIR)\comclass.obj" \
	"$(INTDIR)\dbcode.obj" \
	"$(INTDIR)\dbdialog.obj" \
	"$(INTDIR)\easyview.obj" \
	"$(INTDIR)\MainFrm.obj" \
	"$(INTDIR)\npipe.obj" \
	"$(INTDIR)\protocol.obj" \
	"$(INTDIR)\StdAfx.obj"

"$(OUTDIR)\cliapp.exe" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ELSEIF  "$(CFG)" == "cliapp - Win32 Debug"

# PROP BASE Use_MFC 6
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "Debug"
# PROP BASE Intermediate_Dir "Debug"
# PROP BASE Target_Dir ""
# PROP Use_MFC 6
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "Debug"
# PROP Intermediate_Dir "Debug"
# PROP Target_Dir ""
OUTDIR=.\Debug
INTDIR=.\Debug

ALL : "$(OUTDIR)\cliapp.exe"

CLEAN : 
	-@erase "$(INTDIR)\browsedi.obj"
	-@erase "$(INTDIR)\cfilemap.obj"
	-@erase "$(INTDIR)\cliapp.obj"
	-@erase "$(INTDIR)\cliapp.res"
	-@erase "$(INTDIR)\clidoc.obj"
	-@erase "$(INTDIR)\cliview.obj"
	-@erase "$(INTDIR)\cmutex.obj"
	-@erase "$(INTDIR)\comclass.obj"
	-@erase "$(INTDIR)\dbcode.obj"
	-@erase "$(INTDIR)\dbdialog.obj"
	-@erase "$(INTDIR)\easyview.obj"
	-@erase "$(INTDIR)\MainFrm.obj"
	-@erase "$(INTDIR)\npipe.obj"
	-@erase "$(INTDIR)\protocol.obj"
	-@erase "$(INTDIR)\StdAfx.obj"
	-@erase "$(INTDIR)\vc40.idb"
	-@erase "$(INTDIR)\vc40.pdb"
	-@erase "$(OUTDIR)\cliapp.exe"
	-@erase "$(OUTDIR)\cliapp.ilk"
	-@erase "$(OUTDIR)\cliapp.pdb"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

# ADD BASE CPP /nologo /MDd /W3 /Gm /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /Yu"stdafx.h" /c
# ADD CPP /nologo /MDd /W3 /Gm /GX /Zi /Od /I "..\common" /I "..\client" /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /YX /c
CPP_PROJ=/nologo /MDd /W3 /Gm /GX /Zi /Od /I "..\common" /I "..\client" /D\
 "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS"\
 /Fp"$(INTDIR)/cliapp.pch" /YX /Fo"$(INTDIR)/" /Fd"$(INTDIR)/" /c 
CPP_OBJS=.\Debug/
CPP_SBRS=.\.
# ADD BASE MTL /nologo /D "_DEBUG" /win32
# ADD MTL /nologo /D "_DEBUG" /win32
MTL_PROJ=/nologo /D "_DEBUG" /win32 
# ADD BASE RSC /l 0x409 /d "_DEBUG" /d "_AFXDLL"
# ADD RSC /l 0x409 /d "_DEBUG" /d "_AFXDLL"
RSC_PROJ=/l 0x409 /fo"$(INTDIR)/cliapp.res" /d "_DEBUG" /d "_AFXDLL" 
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
BSC32_FLAGS=/nologo /o"$(OUTDIR)/cliapp.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /debug /machine:I386
# ADD LINK32 /nologo /subsystem:windows /debug /machine:I386
LINK32_FLAGS=/nologo /subsystem:windows /incremental:yes\
 /pdb:"$(OUTDIR)/cliapp.pdb" /debug /machine:I386 /out:"$(OUTDIR)/cliapp.exe" 
LINK32_OBJS= \
	"$(INTDIR)\browsedi.obj" \
	"$(INTDIR)\cfilemap.obj" \
	"$(INTDIR)\cliapp.obj" \
	"$(INTDIR)\cliapp.res" \
	"$(INTDIR)\clidoc.obj" \
	"$(INTDIR)\cliview.obj" \
	"$(INTDIR)\cmutex.obj" \
	"$(INTDIR)\comclass.obj" \
	"$(INTDIR)\dbcode.obj" \
	"$(INTDIR)\dbdialog.obj" \
	"$(INTDIR)\easyview.obj" \
	"$(INTDIR)\MainFrm.obj" \
	"$(INTDIR)\npipe.obj" \
	"$(INTDIR)\protocol.obj" \
	"$(INTDIR)\StdAfx.obj"

"$(OUTDIR)\cliapp.exe" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
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

################################################################################
# Begin Target

# Name "cliapp - Win32 Release"
# Name "cliapp - Win32 Debug"

!IF  "$(CFG)" == "cliapp - Win32 Release"

!ELSEIF  "$(CFG)" == "cliapp - Win32 Debug"

!ENDIF 

################################################################################
# Begin Source File

SOURCE=.\StdAfx.cpp
DEP_CPP_STDAF=\
	"..\client\stdafx.h"\
	

"$(INTDIR)\StdAfx.obj" : $(SOURCE) $(DEP_CPP_STDAF) "$(INTDIR)"


# End Source File
################################################################################
# Begin Source File

SOURCE=.\MainFrm.cpp
DEP_CPP_MAINF=\
	"..\client\stdafx.h"\
	".\cliapp.h"\
	".\MainFrm.h"\
	

"$(INTDIR)\MainFrm.obj" : $(SOURCE) $(DEP_CPP_MAINF) "$(INTDIR)"


# End Source File
################################################################################
# Begin Source File

SOURCE=.\cliview.cpp
DEP_CPP_CLIVI=\
	"..\client\stdafx.h"\
	"..\common\cfilemap.h"\
	"..\common\cmutex.h"\
	"..\common\comclass.h"\
	"..\common\common.h"\
	"..\common\dbcode.h"\
	"..\common\dbdialog.h"\
	"..\common\easyview.h"\
	"..\common\npipe.h"\
	"..\common\protocol.h"\
	".\browsedi.h"\
	".\cliapp.h"\
	".\clidoc.h"\
	".\cliview.h"\
	

"$(INTDIR)\cliview.obj" : $(SOURCE) $(DEP_CPP_CLIVI) "$(INTDIR)"


# End Source File
################################################################################
# Begin Source File

SOURCE=.\clidoc.cpp
DEP_CPP_CLIDO=\
	"..\client\stdafx.h"\
	".\cliapp.h"\
	".\clidoc.h"\
	

"$(INTDIR)\clidoc.obj" : $(SOURCE) $(DEP_CPP_CLIDO) "$(INTDIR)"


# End Source File
################################################################################
# Begin Source File

SOURCE=.\cliapp.rc
DEP_RSC_CLIAP=\
	".\res\npseccli.ico"\
	".\res\npseccli.rc2"\
	".\res\Toolbar.bmp"\
	

"$(INTDIR)\cliapp.res" : $(SOURCE) $(DEP_RSC_CLIAP) "$(INTDIR)"
   $(RSC) $(RSC_PROJ) $(SOURCE)


# End Source File
################################################################################
# Begin Source File

SOURCE=.\cliapp.cpp
DEP_CPP_CLIAPP=\
	"..\client\stdafx.h"\
	"..\common\common.h"\
	"..\common\dbcode.h"\
	"..\common\easyview.h"\
	".\browsedi.h"\
	".\cliapp.h"\
	".\clidoc.h"\
	".\cliview.h"\
	".\MainFrm.h"\
	

"$(INTDIR)\cliapp.obj" : $(SOURCE) $(DEP_CPP_CLIAPP) "$(INTDIR)"


# End Source File
################################################################################
# Begin Source File

SOURCE=.\browsedi.cpp
DEP_CPP_BROWS=\
	"..\client\stdafx.h"\
	".\browsedi.h"\
	".\cliapp.h"\
	

"$(INTDIR)\browsedi.obj" : $(SOURCE) $(DEP_CPP_BROWS) "$(INTDIR)"


# End Source File
################################################################################
# Begin Source File

SOURCE=\projects\iocps\common\protocol.cpp
DEP_CPP_PROTO=\
	"..\client\stdafx.h"\
	"..\common\comclass.h"\
	"..\common\common.h"\
	"..\common\dbcode.h"\
	"..\common\npipe.h"\
	"..\common\protocol.h"\
	
NODEP_CPP_PROTO=\
	"..\common\client.h"\
	

"$(INTDIR)\protocol.obj" : $(SOURCE) $(DEP_CPP_PROTO) "$(INTDIR)"
   $(CPP) $(CPP_PROJ) $(SOURCE)


# End Source File
################################################################################
# Begin Source File

SOURCE=\projects\iocps\common\npipe.cpp
DEP_CPP_NPIPE=\
	"..\client\stdafx.h"\
	"..\common\comclass.h"\
	"..\common\npipe.h"\
	

"$(INTDIR)\npipe.obj" : $(SOURCE) $(DEP_CPP_NPIPE) "$(INTDIR)"
   $(CPP) $(CPP_PROJ) $(SOURCE)


# End Source File
################################################################################
# Begin Source File

SOURCE=\projects\iocps\common\easyview.cpp
DEP_CPP_EASYV=\
	"..\client\stdafx.h"\
	"..\common\easyview.h"\
	

"$(INTDIR)\easyview.obj" : $(SOURCE) $(DEP_CPP_EASYV) "$(INTDIR)"
   $(CPP) $(CPP_PROJ) $(SOURCE)


# End Source File
################################################################################
# Begin Source File

SOURCE=\projects\iocps\common\dbdialog.cpp
DEP_CPP_DBDIA=\
	"..\client\stdafx.h"\
	"..\common\dbdialog.h"\
	

"$(INTDIR)\dbdialog.obj" : $(SOURCE) $(DEP_CPP_DBDIA) "$(INTDIR)"
   $(CPP) $(CPP_PROJ) $(SOURCE)


# End Source File
################################################################################
# Begin Source File

SOURCE=\projects\iocps\common\dbcode.cpp
DEP_CPP_DBCOD=\
	"..\client\stdafx.h"\
	"..\common\cmutex.h"\
	"..\common\comclass.h"\
	"..\common\dbcode.h"\
	"..\common\npipe.h"\
	

"$(INTDIR)\dbcode.obj" : $(SOURCE) $(DEP_CPP_DBCOD) "$(INTDIR)"
   $(CPP) $(CPP_PROJ) $(SOURCE)


# End Source File
################################################################################
# Begin Source File

SOURCE=\projects\iocps\common\comclass.cpp
DEP_CPP_COMCL=\
	"..\client\stdafx.h"\
	"..\common\comclass.h"\
	

"$(INTDIR)\comclass.obj" : $(SOURCE) $(DEP_CPP_COMCL) "$(INTDIR)"
   $(CPP) $(CPP_PROJ) $(SOURCE)


# End Source File
################################################################################
# Begin Source File

SOURCE=\projects\iocps\common\cmutex.cpp
DEP_CPP_CMUTE=\
	"..\client\stdafx.h"\
	"..\common\cmutex.h"\
	

"$(INTDIR)\cmutex.obj" : $(SOURCE) $(DEP_CPP_CMUTE) "$(INTDIR)"
   $(CPP) $(CPP_PROJ) $(SOURCE)


# End Source File
################################################################################
# Begin Source File

SOURCE=\projects\iocps\common\cfilemap.cpp
DEP_CPP_CFILE=\
	"..\client\stdafx.h"\
	"..\common\cfilemap.h"\
	

"$(INTDIR)\cfilemap.obj" : $(SOURCE) $(DEP_CPP_CFILE) "$(INTDIR)"
   $(CPP) $(CPP_PROJ) $(SOURCE)


# End Source File
# End Target
# End Project
################################################################################
