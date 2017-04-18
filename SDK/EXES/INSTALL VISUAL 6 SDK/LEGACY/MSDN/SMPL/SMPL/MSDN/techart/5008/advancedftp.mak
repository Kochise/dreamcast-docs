# Microsoft Developer Studio Generated NMAKE File, Format Version 4.20
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Application" 0x0101

!IF "$(CFG)" == ""
CFG=AdvancedFTP - Win32 Debug
!MESSAGE No configuration specified.  Defaulting to AdvancedFTP - Win32 Debug.
!ENDIF 

!IF "$(CFG)" != "AdvancedFTP - Win32 Release" && "$(CFG)" !=\
 "AdvancedFTP - Win32 Debug"
!MESSAGE Invalid configuration "$(CFG)" specified.
!MESSAGE You can specify a configuration when running NMAKE on this makefile
!MESSAGE by defining the macro CFG on the command line.  For example:
!MESSAGE 
!MESSAGE NMAKE /f "AdvancedFTP.mak" CFG="AdvancedFTP - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "AdvancedFTP - Win32 Release" (based on "Win32 (x86) Application")
!MESSAGE "AdvancedFTP - Win32 Debug" (based on "Win32 (x86) Application")
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
# PROP Target_Last_Scanned "AdvancedFTP - Win32 Debug"
CPP=cl.exe
RSC=rc.exe
MTL=mktyplib.exe

!IF  "$(CFG)" == "AdvancedFTP - Win32 Release"

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

ALL : "$(OUTDIR)\AdvancedFTP.exe" "$(OUTDIR)\AdvancedFTP.hlp"

CLEAN : 
	-@erase "$(INTDIR)\AdvancedFTP.hlp"
	-@erase "$(INTDIR)\AdvancedFTP.obj"
	-@erase "$(INTDIR)\AdvancedFTP.pch"
	-@erase "$(INTDIR)\AdvancedFTP.res"
	-@erase "$(INTDIR)\AdvancedFTPDlg.obj"
	-@erase "$(INTDIR)\StdAfx.obj"
	-@erase "$(OUTDIR)\AdvancedFTP.exe"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

# ADD BASE CPP /nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /Yu"stdafx.h" /c
# ADD CPP /nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /Yu"stdafx.h" /c
CPP_PROJ=/nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D\
 "_AFXDLL" /D "_MBCS" /Fp"$(INTDIR)/AdvancedFTP.pch" /Yu"stdafx.h"\
 /Fo"$(INTDIR)/" /c 
CPP_OBJS=.\Release/
CPP_SBRS=.\.
# ADD BASE MTL /nologo /D "NDEBUG" /win32
# ADD MTL /nologo /D "NDEBUG" /win32
MTL_PROJ=/nologo /D "NDEBUG" /win32 
# ADD BASE RSC /l 0x409 /d "NDEBUG" /d "_AFXDLL"
# ADD RSC /l 0x409 /d "NDEBUG" /d "_AFXDLL"
RSC_PROJ=/l 0x409 /fo"$(INTDIR)/AdvancedFTP.res" /d "NDEBUG" /d "_AFXDLL" 
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
BSC32_FLAGS=/nologo /o"$(OUTDIR)/AdvancedFTP.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /machine:I386
# ADD LINK32 /nologo /subsystem:windows /machine:I386
LINK32_FLAGS=/nologo /subsystem:windows /incremental:no\
 /pdb:"$(OUTDIR)/AdvancedFTP.pdb" /machine:I386 /out:"$(OUTDIR)/AdvancedFTP.exe"\
 
LINK32_OBJS= \
	"$(INTDIR)\AdvancedFTP.obj" \
	"$(INTDIR)\AdvancedFTP.res" \
	"$(INTDIR)\AdvancedFTPDlg.obj" \
	"$(INTDIR)\StdAfx.obj" \
	"D:\INetSDK\Lib\Wininet.lib"

"$(OUTDIR)\AdvancedFTP.exe" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ELSEIF  "$(CFG)" == "AdvancedFTP - Win32 Debug"

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

ALL : "$(OUTDIR)\AdvancedFTP.exe" "$(OUTDIR)\AdvancedFTP.hlp"

CLEAN : 
	-@erase "$(INTDIR)\AdvancedFTP.hlp"
	-@erase "$(INTDIR)\AdvancedFTP.obj"
	-@erase "$(INTDIR)\AdvancedFTP.pch"
	-@erase "$(INTDIR)\AdvancedFTP.res"
	-@erase "$(INTDIR)\AdvancedFTPDlg.obj"
	-@erase "$(INTDIR)\StdAfx.obj"
	-@erase "$(INTDIR)\vc40.idb"
	-@erase "$(INTDIR)\vc40.pdb"
	-@erase "$(OUTDIR)\AdvancedFTP.exe"
	-@erase "$(OUTDIR)\AdvancedFTP.ilk"
	-@erase "$(OUTDIR)\AdvancedFTP.pdb"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

# ADD BASE CPP /nologo /MDd /W3 /Gm /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /Yu"stdafx.h" /c
# ADD CPP /nologo /MDd /W3 /Gm /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /Yu"stdafx.h" /c
CPP_PROJ=/nologo /MDd /W3 /Gm /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS"\
 /D "_AFXDLL" /D "_MBCS" /Fp"$(INTDIR)/AdvancedFTP.pch" /Yu"stdafx.h"\
 /Fo"$(INTDIR)/" /Fd"$(INTDIR)/" /c 
CPP_OBJS=.\Debug/
CPP_SBRS=.\.
# ADD BASE MTL /nologo /D "_DEBUG" /win32
# ADD MTL /nologo /D "_DEBUG" /win32
MTL_PROJ=/nologo /D "_DEBUG" /win32 
# ADD BASE RSC /l 0x409 /d "_DEBUG" /d "_AFXDLL"
# ADD RSC /l 0x409 /d "_DEBUG" /d "_AFXDLL"
RSC_PROJ=/l 0x409 /fo"$(INTDIR)/AdvancedFTP.res" /d "_DEBUG" /d "_AFXDLL" 
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
BSC32_FLAGS=/nologo /o"$(OUTDIR)/AdvancedFTP.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /debug /machine:I386
# ADD LINK32 /nologo /subsystem:windows /debug /machine:I386
LINK32_FLAGS=/nologo /subsystem:windows /incremental:yes\
 /pdb:"$(OUTDIR)/AdvancedFTP.pdb" /debug /machine:I386\
 /out:"$(OUTDIR)/AdvancedFTP.exe" 
LINK32_OBJS= \
	"$(INTDIR)\AdvancedFTP.obj" \
	"$(INTDIR)\AdvancedFTP.res" \
	"$(INTDIR)\AdvancedFTPDlg.obj" \
	"$(INTDIR)\StdAfx.obj" \
	"D:\INetSDK\Lib\Wininet.lib"

"$(OUTDIR)\AdvancedFTP.exe" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
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

# Name "AdvancedFTP - Win32 Release"
# Name "AdvancedFTP - Win32 Debug"

!IF  "$(CFG)" == "AdvancedFTP - Win32 Release"

!ELSEIF  "$(CFG)" == "AdvancedFTP - Win32 Debug"

!ENDIF 

################################################################################
# Begin Source File

SOURCE=.\ReadMe.txt

!IF  "$(CFG)" == "AdvancedFTP - Win32 Release"

!ELSEIF  "$(CFG)" == "AdvancedFTP - Win32 Debug"

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\AdvancedFTP.cpp
DEP_CPP_ADVAN=\
	".\AdvancedFTP.h"\
	".\AdvancedFTPDlg.h"\
	".\StdAfx.h"\
	

"$(INTDIR)\AdvancedFTP.obj" : $(SOURCE) $(DEP_CPP_ADVAN) "$(INTDIR)"\
 "$(INTDIR)\AdvancedFTP.pch"


# End Source File
################################################################################
# Begin Source File

SOURCE=.\AdvancedFTPDlg.cpp
DEP_CPP_ADVANC=\
	".\AdvancedFTP.h"\
	".\AdvancedFTPDlg.h"\
	".\StdAfx.h"\
	

"$(INTDIR)\AdvancedFTPDlg.obj" : $(SOURCE) $(DEP_CPP_ADVANC) "$(INTDIR)"\
 "$(INTDIR)\AdvancedFTP.pch"


# End Source File
################################################################################
# Begin Source File

SOURCE=.\StdAfx.cpp
DEP_CPP_STDAF=\
	".\StdAfx.h"\
	

!IF  "$(CFG)" == "AdvancedFTP - Win32 Release"

# ADD CPP /Yc"stdafx.h"

BuildCmds= \
	$(CPP) /nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D\
 "_AFXDLL" /D "_MBCS" /Fp"$(INTDIR)/AdvancedFTP.pch" /Yc"stdafx.h"\
 /Fo"$(INTDIR)/" /c $(SOURCE) \
	

"$(INTDIR)\StdAfx.obj" : $(SOURCE) $(DEP_CPP_STDAF) "$(INTDIR)"
   $(BuildCmds)

"$(INTDIR)\AdvancedFTP.pch" : $(SOURCE) $(DEP_CPP_STDAF) "$(INTDIR)"
   $(BuildCmds)

!ELSEIF  "$(CFG)" == "AdvancedFTP - Win32 Debug"

# ADD CPP /Yc"stdafx.h"

BuildCmds= \
	$(CPP) /nologo /MDd /W3 /Gm /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS"\
 /D "_AFXDLL" /D "_MBCS" /Fp"$(INTDIR)/AdvancedFTP.pch" /Yc"stdafx.h"\
 /Fo"$(INTDIR)/" /Fd"$(INTDIR)/" /c $(SOURCE) \
	

"$(INTDIR)\StdAfx.obj" : $(SOURCE) $(DEP_CPP_STDAF) "$(INTDIR)"
   $(BuildCmds)

"$(INTDIR)\AdvancedFTP.pch" : $(SOURCE) $(DEP_CPP_STDAF) "$(INTDIR)"
   $(BuildCmds)

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\AdvancedFTP.rc
DEP_RSC_ADVANCE=\
	".\res\AdvancedFTP.ico"\
	".\res\AdvancedFTP.rc2"\
	

"$(INTDIR)\AdvancedFTP.res" : $(SOURCE) $(DEP_RSC_ADVANCE) "$(INTDIR)"
   $(RSC) $(RSC_PROJ) $(SOURCE)


# End Source File
################################################################################
# Begin Source File

SOURCE=.\hlp\AdvancedFTP.hpj

!IF  "$(CFG)" == "AdvancedFTP - Win32 Release"

# Begin Custom Build - Making help file...
OutDir=.\Release
ProjDir=.
TargetName=AdvancedFTP
InputPath=.\hlp\AdvancedFTP.hpj

"$(OutDir)\$(TargetName).hlp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   "$(ProjDir)\makehelp.bat"

# End Custom Build

!ELSEIF  "$(CFG)" == "AdvancedFTP - Win32 Debug"

# Begin Custom Build - Making help file...
OutDir=.\Debug
ProjDir=.
TargetName=AdvancedFTP
InputPath=.\hlp\AdvancedFTP.hpj

"$(OutDir)\$(TargetName).hlp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   "$(ProjDir)\makehelp.bat"

# End Custom Build

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=D:\INetSDK\Lib\Wininet.lib

!IF  "$(CFG)" == "AdvancedFTP - Win32 Release"

!ELSEIF  "$(CFG)" == "AdvancedFTP - Win32 Debug"

!ENDIF 

# End Source File
# End Target
# End Project
################################################################################
