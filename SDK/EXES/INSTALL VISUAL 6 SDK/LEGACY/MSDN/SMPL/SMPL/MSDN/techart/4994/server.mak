# Microsoft Developer Studio Generated NMAKE File, Format Version 4.20
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Application" 0x0101

!IF "$(CFG)" == ""
CFG=server - Win32 Debug
!MESSAGE No configuration specified.  Defaulting to server - Win32 Debug.
!ENDIF 

!IF "$(CFG)" != "server - Win32 Release" && "$(CFG)" != "server - Win32 Debug"
!MESSAGE Invalid configuration "$(CFG)" specified.
!MESSAGE You can specify a configuration when running NMAKE on this makefile
!MESSAGE by defining the macro CFG on the command line.  For example:
!MESSAGE 
!MESSAGE NMAKE /f "server.mak" CFG="server - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "server - Win32 Release" (based on "Win32 (x86) Application")
!MESSAGE "server - Win32 Debug" (based on "Win32 (x86) Application")
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
# PROP Target_Last_Scanned "server - Win32 Debug"
CPP=cl.exe
RSC=rc.exe
MTL=mktyplib.exe

!IF  "$(CFG)" == "server - Win32 Release"

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

ALL : "$(OUTDIR)\server.exe"

CLEAN : 
	-@erase "$(INTDIR)\cfilemap.obj"
	-@erase "$(INTDIR)\client.obj"
	-@erase "$(INTDIR)\cmutex.obj"
	-@erase "$(INTDIR)\comclass.obj"
	-@erase "$(INTDIR)\dbcode.obj"
	-@erase "$(INTDIR)\dbdialog.obj"
	-@erase "$(INTDIR)\easyview.obj"
	-@erase "$(INTDIR)\MainFrm.obj"
	-@erase "$(INTDIR)\npipe.obj"
	-@erase "$(INTDIR)\protocol.obj"
	-@erase "$(INTDIR)\srvapp.obj"
	-@erase "$(INTDIR)\srvapp.res"
	-@erase "$(INTDIR)\srvdoc.obj"
	-@erase "$(INTDIR)\srvview.obj"
	-@erase "$(INTDIR)\StdAfx.obj"
	-@erase "$(OUTDIR)\server.exe"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

# ADD BASE CPP /nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /Yu"stdafx.h" /c
# ADD CPP /nologo /MD /W3 /GX /O2 /I ".\secstuff" /I "..\server" /I "..\common" /D "NDEBUG" /D "WIN32" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /D "SERVER" /D "STATISTICS" /YX /c
CPP_PROJ=/nologo /MD /W3 /GX /O2 /I ".\secstuff" /I "..\server" /I "..\common"\
 /D "NDEBUG" /D "WIN32" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /D "SERVER" /D\
 "STATISTICS" /Fp"$(INTDIR)/server.pch" /YX /Fo"$(INTDIR)/" /c 
CPP_OBJS=.\Release/
CPP_SBRS=.\.
# ADD BASE MTL /nologo /D "NDEBUG" /win32
# ADD MTL /nologo /D "NDEBUG" /win32
MTL_PROJ=/nologo /D "NDEBUG" /win32 
# ADD BASE RSC /l 0x409 /d "NDEBUG" /d "_AFXDLL"
# ADD RSC /l 0x409 /d "NDEBUG" /d "_AFXDLL"
RSC_PROJ=/l 0x409 /fo"$(INTDIR)/srvapp.res" /d "NDEBUG" /d "_AFXDLL" 
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
BSC32_FLAGS=/nologo /o"$(OUTDIR)/server.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /machine:I386
# ADD LINK32 /nologo /subsystem:windows /machine:I386
LINK32_FLAGS=/nologo /subsystem:windows /incremental:no\
 /pdb:"$(OUTDIR)/server.pdb" /machine:I386 /out:"$(OUTDIR)/server.exe" 
LINK32_OBJS= \
	"$(INTDIR)\cfilemap.obj" \
	"$(INTDIR)\client.obj" \
	"$(INTDIR)\cmutex.obj" \
	"$(INTDIR)\comclass.obj" \
	"$(INTDIR)\dbcode.obj" \
	"$(INTDIR)\dbdialog.obj" \
	"$(INTDIR)\easyview.obj" \
	"$(INTDIR)\MainFrm.obj" \
	"$(INTDIR)\npipe.obj" \
	"$(INTDIR)\protocol.obj" \
	"$(INTDIR)\srvapp.obj" \
	"$(INTDIR)\srvapp.res" \
	"$(INTDIR)\srvdoc.obj" \
	"$(INTDIR)\srvview.obj" \
	"$(INTDIR)\StdAfx.obj"

"$(OUTDIR)\server.exe" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ELSEIF  "$(CFG)" == "server - Win32 Debug"

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

ALL : "$(OUTDIR)\server.exe"

CLEAN : 
	-@erase "$(INTDIR)\cfilemap.obj"
	-@erase "$(INTDIR)\client.obj"
	-@erase "$(INTDIR)\cmutex.obj"
	-@erase "$(INTDIR)\comclass.obj"
	-@erase "$(INTDIR)\dbcode.obj"
	-@erase "$(INTDIR)\dbdialog.obj"
	-@erase "$(INTDIR)\easyview.obj"
	-@erase "$(INTDIR)\MainFrm.obj"
	-@erase "$(INTDIR)\npipe.obj"
	-@erase "$(INTDIR)\protocol.obj"
	-@erase "$(INTDIR)\srvapp.obj"
	-@erase "$(INTDIR)\srvapp.res"
	-@erase "$(INTDIR)\srvdoc.obj"
	-@erase "$(INTDIR)\srvview.obj"
	-@erase "$(INTDIR)\StdAfx.obj"
	-@erase "$(INTDIR)\vc40.idb"
	-@erase "$(INTDIR)\vc40.pdb"
	-@erase "$(OUTDIR)\server.exe"
	-@erase "$(OUTDIR)\server.ilk"
	-@erase "$(OUTDIR)\server.pdb"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

# ADD BASE CPP /nologo /MDd /W3 /Gm /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /Yu"stdafx.h" /c
# ADD CPP /nologo /MDd /W3 /Gm /GX /Zi /Od /I ".\secstuff" /I "..\server" /I "..\common" /D "_DEBUG" /D "WIN32" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /D "SERVER" /D "STATISTICS" /YX /c
CPP_PROJ=/nologo /MDd /W3 /Gm /GX /Zi /Od /I ".\secstuff" /I "..\server" /I\
 "..\common" /D "_DEBUG" /D "WIN32" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /D\
 "SERVER" /D "STATISTICS" /Fp"$(INTDIR)/server.pch" /YX /Fo"$(INTDIR)/"\
 /Fd"$(INTDIR)/" /c 
CPP_OBJS=.\Debug/
CPP_SBRS=.\.
# ADD BASE MTL /nologo /D "_DEBUG" /win32
# ADD MTL /nologo /D "_DEBUG" /win32
MTL_PROJ=/nologo /D "_DEBUG" /win32 
# ADD BASE RSC /l 0x409 /d "_DEBUG" /d "_AFXDLL"
# ADD RSC /l 0x409 /d "_DEBUG" /d "_AFXDLL"
RSC_PROJ=/l 0x409 /fo"$(INTDIR)/srvapp.res" /d "_DEBUG" /d "_AFXDLL" 
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
BSC32_FLAGS=/nologo /o"$(OUTDIR)/server.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /debug /machine:I386
# ADD LINK32 /nologo /subsystem:windows /debug /machine:I386
LINK32_FLAGS=/nologo /subsystem:windows /incremental:yes\
 /pdb:"$(OUTDIR)/server.pdb" /debug /machine:I386 /out:"$(OUTDIR)/server.exe" 
LINK32_OBJS= \
	"$(INTDIR)\cfilemap.obj" \
	"$(INTDIR)\client.obj" \
	"$(INTDIR)\cmutex.obj" \
	"$(INTDIR)\comclass.obj" \
	"$(INTDIR)\dbcode.obj" \
	"$(INTDIR)\dbdialog.obj" \
	"$(INTDIR)\easyview.obj" \
	"$(INTDIR)\MainFrm.obj" \
	"$(INTDIR)\npipe.obj" \
	"$(INTDIR)\protocol.obj" \
	"$(INTDIR)\srvapp.obj" \
	"$(INTDIR)\srvapp.res" \
	"$(INTDIR)\srvdoc.obj" \
	"$(INTDIR)\srvview.obj" \
	"$(INTDIR)\StdAfx.obj"

"$(OUTDIR)\server.exe" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
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

# Name "server - Win32 Release"
# Name "server - Win32 Debug"

!IF  "$(CFG)" == "server - Win32 Release"

!ELSEIF  "$(CFG)" == "server - Win32 Debug"

!ENDIF 

################################################################################
# Begin Source File

SOURCE=.\StdAfx.cpp
DEP_CPP_STDAF=\
	"..\server\stdafx.h"\
	

"$(INTDIR)\StdAfx.obj" : $(SOURCE) $(DEP_CPP_STDAF) "$(INTDIR)"


# End Source File
################################################################################
# Begin Source File

SOURCE=.\srvview.cpp
DEP_CPP_SRVVI=\
	"..\common\cfilemap.h"\
	"..\common\cmutex.h"\
	"..\common\comclass.h"\
	"..\common\common.h"\
	"..\common\dbcode.h"\
	"..\common\dbdialog.h"\
	"..\common\easyview.h"\
	"..\common\npipe.h"\
	"..\common\protocol.h"\
	"..\server\client.h"\
	"..\server\stdafx.h"\
	".\srvapp.h"\
	".\srvdoc.h"\
	".\srvview.h"\
	

"$(INTDIR)\srvview.obj" : $(SOURCE) $(DEP_CPP_SRVVI) "$(INTDIR)"


# End Source File
################################################################################
# Begin Source File

SOURCE=.\srvdoc.cpp
DEP_CPP_SRVDO=\
	"..\server\stdafx.h"\
	".\srvapp.h"\
	".\srvdoc.h"\
	

"$(INTDIR)\srvdoc.obj" : $(SOURCE) $(DEP_CPP_SRVDO) "$(INTDIR)"


# End Source File
################################################################################
# Begin Source File

SOURCE=.\srvapp.rc
DEP_RSC_SRVAP=\
	".\res\npscesrv.ico"\
	".\res\npscesrv.rc2"\
	".\res\Toolbar.bmp"\
	

"$(INTDIR)\srvapp.res" : $(SOURCE) $(DEP_RSC_SRVAP) "$(INTDIR)"
   $(RSC) $(RSC_PROJ) $(SOURCE)


# End Source File
################################################################################
# Begin Source File

SOURCE=.\srvapp.cpp
DEP_CPP_SRVAPP=\
	"..\common\common.h"\
	"..\common\easyview.h"\
	"..\server\stdafx.h"\
	".\MainFrm.h"\
	".\srvapp.h"\
	".\srvdoc.h"\
	".\srvview.h"\
	

"$(INTDIR)\srvapp.obj" : $(SOURCE) $(DEP_CPP_SRVAPP) "$(INTDIR)"


# End Source File
################################################################################
# Begin Source File

SOURCE=.\MainFrm.cpp
DEP_CPP_MAINF=\
	"..\server\stdafx.h"\
	".\MainFrm.h"\
	".\srvapp.h"\
	

"$(INTDIR)\MainFrm.obj" : $(SOURCE) $(DEP_CPP_MAINF) "$(INTDIR)"


# End Source File
################################################################################
# Begin Source File

SOURCE=\projects\iocps\common\protocol.cpp
DEP_CPP_PROTO=\
	"..\common\comclass.h"\
	"..\common\common.h"\
	"..\common\dbcode.h"\
	"..\common\npipe.h"\
	"..\common\protocol.h"\
	"..\server\client.h"\
	"..\server\stdafx.h"\
	

"$(INTDIR)\protocol.obj" : $(SOURCE) $(DEP_CPP_PROTO) "$(INTDIR)"
   $(CPP) $(CPP_PROJ) $(SOURCE)


# End Source File
################################################################################
# Begin Source File

SOURCE=\projects\iocps\common\npipe.cpp
DEP_CPP_NPIPE=\
	"..\common\comclass.h"\
	"..\common\npipe.h"\
	"..\server\stdafx.h"\
	

"$(INTDIR)\npipe.obj" : $(SOURCE) $(DEP_CPP_NPIPE) "$(INTDIR)"
   $(CPP) $(CPP_PROJ) $(SOURCE)


# End Source File
################################################################################
# Begin Source File

SOURCE=\projects\iocps\common\easyview.cpp
DEP_CPP_EASYV=\
	"..\common\easyview.h"\
	"..\server\stdafx.h"\
	

"$(INTDIR)\easyview.obj" : $(SOURCE) $(DEP_CPP_EASYV) "$(INTDIR)"
   $(CPP) $(CPP_PROJ) $(SOURCE)


# End Source File
################################################################################
# Begin Source File

SOURCE=\projects\iocps\common\dbdialog.cpp
DEP_CPP_DBDIA=\
	"..\common\dbdialog.h"\
	"..\server\stdafx.h"\
	

"$(INTDIR)\dbdialog.obj" : $(SOURCE) $(DEP_CPP_DBDIA) "$(INTDIR)"
   $(CPP) $(CPP_PROJ) $(SOURCE)


# End Source File
################################################################################
# Begin Source File

SOURCE=\projects\iocps\common\dbcode.cpp
DEP_CPP_DBCOD=\
	"..\common\cmutex.h"\
	"..\common\comclass.h"\
	"..\common\dbcode.h"\
	"..\common\npipe.h"\
	"..\server\stdafx.h"\
	

"$(INTDIR)\dbcode.obj" : $(SOURCE) $(DEP_CPP_DBCOD) "$(INTDIR)"
   $(CPP) $(CPP_PROJ) $(SOURCE)


# End Source File
################################################################################
# Begin Source File

SOURCE=\projects\iocps\common\comclass.cpp
DEP_CPP_COMCL=\
	"..\common\comclass.h"\
	"..\server\stdafx.h"\
	

"$(INTDIR)\comclass.obj" : $(SOURCE) $(DEP_CPP_COMCL) "$(INTDIR)"
   $(CPP) $(CPP_PROJ) $(SOURCE)


# End Source File
################################################################################
# Begin Source File

SOURCE=\projects\iocps\common\cmutex.cpp
DEP_CPP_CMUTE=\
	"..\common\cmutex.h"\
	"..\server\stdafx.h"\
	

"$(INTDIR)\cmutex.obj" : $(SOURCE) $(DEP_CPP_CMUTE) "$(INTDIR)"
   $(CPP) $(CPP_PROJ) $(SOURCE)


# End Source File
################################################################################
# Begin Source File

SOURCE=\projects\iocps\common\cfilemap.cpp
DEP_CPP_CFILE=\
	"..\common\cfilemap.h"\
	"..\server\stdafx.h"\
	

"$(INTDIR)\cfilemap.obj" : $(SOURCE) $(DEP_CPP_CFILE) "$(INTDIR)"
   $(CPP) $(CPP_PROJ) $(SOURCE)


# End Source File
################################################################################
# Begin Source File

SOURCE=.\client.cpp
DEP_CPP_CLIEN=\
	"..\common\comclass.h"\
	"..\common\dbcode.h"\
	"..\common\npipe.h"\
	"..\common\protocol.h"\
	"..\server\client.h"\
	"..\server\stdafx.h"\
	

"$(INTDIR)\client.obj" : $(SOURCE) $(DEP_CPP_CLIEN) "$(INTDIR)"


# End Source File
# End Target
# End Project
################################################################################
