# Microsoft Developer Studio Generated NMAKE File, Format Version 4.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Application" 0x0101

!IF "$(CFG)" == ""
CFG=TrayTest - Win32 Debug
!MESSAGE No configuration specified.  Defaulting to TrayTest - Win32 Debug.
!ENDIF 

!IF "$(CFG)" != "TrayTest - Win32 Release" && "$(CFG)" !=\
 "TrayTest - Win32 Debug"
!MESSAGE Invalid configuration "$(CFG)" specified.
!MESSAGE You can specify a configuration when running NMAKE on this makefile
!MESSAGE by defining the macro CFG on the command line.  For example:
!MESSAGE 
!MESSAGE NMAKE /f "TrayTest.mak" CFG="TrayTest - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "TrayTest - Win32 Release" (based on "Win32 (x86) Application")
!MESSAGE "TrayTest - Win32 Debug" (based on "Win32 (x86) Application")
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
# PROP Target_Last_Scanned "TrayTest - Win32 Debug"
MTL=mktyplib.exe
RSC=rc.exe
CPP=cl.exe

!IF  "$(CFG)" == "TrayTest - Win32 Release"

# PROP BASE Use_MFC 1
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "Release"
# PROP BASE Intermediate_Dir "Release"
# PROP BASE Target_Dir ""
# PROP Use_MFC 2
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "Release"
# PROP Intermediate_Dir "Release"
# PROP Target_Dir ""
OUTDIR=.\Release
INTDIR=.\Release

ALL : "$(OUTDIR)\TrayTest.exe" "$(OUTDIR)\TrayTest.bsc"

CLEAN : 
	-@erase ".\Release\TrayTest.bsc"
	-@erase ".\Release\TrayIcon.sbr"
	-@erase ".\Release\TrayTest.pch"
	-@erase ".\Release\Mainfrm.sbr"
	-@erase ".\Release\Stdafx.sbr"
	-@erase ".\Release\TrayTest.sbr"
	-@erase ".\Release\TrayTest.exe"
	-@erase ".\Release\TrayTest.obj"
	-@erase ".\Release\TrayIcon.obj"
	-@erase ".\Release\Mainfrm.obj"
	-@erase ".\Release\Stdafx.obj"
	-@erase ".\Release\TrayTest.res"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

# ADD BASE CPP /nologo /MT /W3 /GX /O1 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /FR /Yu"STDAFX.H" /c
# ADD CPP /nologo /MD /W3 /GX /O1 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /FR /Yu"STDAFX.H" /c
CPP_PROJ=/nologo /MD /W3 /GX /O1 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D\
 "_AFXDLL" /D "_MBCS" /FR"$(INTDIR)/" /Fp"$(INTDIR)/TrayTest.pch" /Yu"STDAFX.H"\
 /Fo"$(INTDIR)/" /c 
CPP_OBJS=.\Release/
CPP_SBRS=.\Release/
# ADD BASE MTL /nologo /D "NDEBUG" /win32
# ADD MTL /nologo /D "NDEBUG" /win32
MTL_PROJ=/nologo /D "NDEBUG" /win32 
# ADD BASE RSC /l 0x409 /d "NDEBUG"
# ADD RSC /l 0x409 /d "NDEBUG" /d "_AFXDLL"
RSC_PROJ=/l 0x409 /fo"$(INTDIR)/TrayTest.res" /d "NDEBUG" /d "_AFXDLL" 
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
BSC32_FLAGS=/nologo /o"$(OUTDIR)/TrayTest.bsc" 
BSC32_SBRS= \
	".\Release\TrayIcon.sbr" \
	".\Release\Mainfrm.sbr" \
	".\Release\Stdafx.sbr" \
	".\Release\TrayTest.sbr"

"$(OUTDIR)\TrayTest.bsc" : "$(OUTDIR)" $(BSC32_SBRS)
    $(BSC32) @<<
  $(BSC32_FLAGS) $(BSC32_SBRS)
<<

LINK32=link.exe
# ADD BASE LINK32 oldnames.lib /nologo /stack:0x2800 /subsystem:windows /machine:IX86
# ADD LINK32 oldnames.lib /nologo /stack:0x2800 /subsystem:windows /machine:IX86
LINK32_FLAGS=oldnames.lib /nologo /stack:0x2800 /subsystem:windows\
 /incremental:no /pdb:"$(OUTDIR)/TrayTest.pdb" /machine:IX86\
 /out:"$(OUTDIR)/TrayTest.exe" 
LINK32_OBJS= \
	".\Release\TrayTest.obj" \
	".\Release\TrayIcon.obj" \
	".\Release\Mainfrm.obj" \
	".\Release\Stdafx.obj" \
	".\Release\TrayTest.res"

"$(OUTDIR)\TrayTest.exe" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ELSEIF  "$(CFG)" == "TrayTest - Win32 Debug"

# PROP BASE Use_MFC 1
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "Debug"
# PROP BASE Intermediate_Dir "Debug"
# PROP BASE Target_Dir ""
# PROP Use_MFC 2
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "Debug"
# PROP Intermediate_Dir "Debug"
# PROP Target_Dir ""
OUTDIR=.\Debug
INTDIR=.\Debug

ALL : "$(OUTDIR)\TrayTest.exe"

CLEAN : 
	-@erase ".\Debug\vc40.pdb"
	-@erase ".\Debug\TrayTest.pch"
	-@erase ".\Debug\vc40.idb"
	-@erase ".\Debug\TrayTest.exe"
	-@erase ".\Debug\TrayTest.obj"
	-@erase ".\Debug\Stdafx.obj"
	-@erase ".\Debug\TrayIcon.obj"
	-@erase ".\Debug\Mainfrm.obj"
	-@erase ".\Debug\TrayTest.res"
	-@erase ".\Debug\TrayTest.ilk"
	-@erase ".\Debug\TrayTest.pdb"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

# ADD BASE CPP /nologo /MTd /W3 /Gm /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /Yu"STDAFX.H" /c
# ADD CPP /nologo /MDd /W3 /Gm /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /Yu"STDAFX.H" /c
CPP_PROJ=/nologo /MDd /W3 /Gm /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS"\
 /D "_AFXDLL" /D "_MBCS" /Fp"$(INTDIR)/TrayTest.pch" /Yu"STDAFX.H"\
 /Fo"$(INTDIR)/" /Fd"$(INTDIR)/" /c 
CPP_OBJS=.\Debug/
CPP_SBRS=
# ADD BASE MTL /nologo /D "_DEBUG" /win32
# ADD MTL /nologo /D "_DEBUG" /win32
MTL_PROJ=/nologo /D "_DEBUG" /win32 
# ADD BASE RSC /l 0x409 /d "_DEBUG"
# ADD RSC /l 0x409 /d "_DEBUG" /d "_AFXDLL"
RSC_PROJ=/l 0x409 /fo"$(INTDIR)/TrayTest.res" /d "_DEBUG" /d "_AFXDLL" 
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
BSC32_FLAGS=/nologo /o"$(OUTDIR)/TrayTest.bsc" 
BSC32_SBRS=
LINK32=link.exe
# ADD BASE LINK32 oldnames.lib /nologo /stack:0x2800 /subsystem:windows /debug /machine:IX86
# ADD LINK32 oldnames.lib /nologo /stack:0x2800 /subsystem:windows /debug /machine:IX86
LINK32_FLAGS=oldnames.lib /nologo /stack:0x2800 /subsystem:windows\
 /incremental:yes /pdb:"$(OUTDIR)/TrayTest.pdb" /debug /machine:IX86\
 /out:"$(OUTDIR)/TrayTest.exe" 
LINK32_OBJS= \
	".\Debug\TrayTest.obj" \
	".\Debug\Stdafx.obj" \
	".\Debug\TrayIcon.obj" \
	".\Debug\Mainfrm.obj" \
	".\Debug\TrayTest.res"

"$(OUTDIR)\TrayTest.exe" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
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

# Name "TrayTest - Win32 Release"
# Name "TrayTest - Win32 Debug"

!IF  "$(CFG)" == "TrayTest - Win32 Release"

!ELSEIF  "$(CFG)" == "TrayTest - Win32 Debug"

!ENDIF 

################################################################################
# Begin Source File

SOURCE=.\TrayTest.rc
DEP_RSC_TRAYT=\
	".\res\app.ico"\
	".\res\myicon.ico"\
	".\res\myicon2.ico"\
	".\res\app.rc2"\
	

"$(INTDIR)\TrayTest.res" : $(SOURCE) $(DEP_RSC_TRAYT) "$(INTDIR)"
   $(RSC) $(RSC_PROJ) $(SOURCE)


# End Source File
################################################################################
# Begin Source File

SOURCE=.\Stdafx.cpp
DEP_CPP_STDAF=\
	".\stdafx.h"\
	

!IF  "$(CFG)" == "TrayTest - Win32 Release"

# ADD BASE CPP /Yc"STDAFX.H"
# ADD CPP /Yc"STDAFX.H"

BuildCmds= \
	$(CPP) /nologo /MD /W3 /GX /O1 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D\
 "_AFXDLL" /D "_MBCS" /FR"$(INTDIR)/" /Fp"$(INTDIR)/TrayTest.pch" /Yc"STDAFX.H"\
 /Fo"$(INTDIR)/" /c $(SOURCE) \
	

"$(INTDIR)\Stdafx.obj" : $(SOURCE) $(DEP_CPP_STDAF) "$(INTDIR)"
   $(BuildCmds)

"$(INTDIR)\Stdafx.sbr" : $(SOURCE) $(DEP_CPP_STDAF) "$(INTDIR)"
   $(BuildCmds)

"$(INTDIR)\TrayTest.pch" : $(SOURCE) $(DEP_CPP_STDAF) "$(INTDIR)"
   $(BuildCmds)

!ELSEIF  "$(CFG)" == "TrayTest - Win32 Debug"

# ADD BASE CPP /Yc"STDAFX.H"
# ADD CPP /Yc"STDAFX.H"

BuildCmds= \
	$(CPP) /nologo /MDd /W3 /Gm /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS"\
 /D "_AFXDLL" /D "_MBCS" /Fp"$(INTDIR)/TrayTest.pch" /Yc"STDAFX.H"\
 /Fo"$(INTDIR)/" /Fd"$(INTDIR)/" /c $(SOURCE) \
	

"$(INTDIR)\Stdafx.obj" : $(SOURCE) $(DEP_CPP_STDAF) "$(INTDIR)"
   $(BuildCmds)

"$(INTDIR)\TrayTest.pch" : $(SOURCE) $(DEP_CPP_STDAF) "$(INTDIR)"
   $(BuildCmds)

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\TrayTest.cpp
DEP_CPP_TRAYTE=\
	".\stdafx.h"\
	".\TrayTest.h"\
	".\mainfrm.h"\
	".\trayicon.h"\
	

!IF  "$(CFG)" == "TrayTest - Win32 Release"


"$(INTDIR)\TrayTest.obj" : $(SOURCE) $(DEP_CPP_TRAYTE) "$(INTDIR)"\
 "$(INTDIR)\TrayTest.pch"

"$(INTDIR)\TrayTest.sbr" : $(SOURCE) $(DEP_CPP_TRAYTE) "$(INTDIR)"\
 "$(INTDIR)\TrayTest.pch"


!ELSEIF  "$(CFG)" == "TrayTest - Win32 Debug"


"$(INTDIR)\TrayTest.obj" : $(SOURCE) $(DEP_CPP_TRAYTE) "$(INTDIR)"\
 "$(INTDIR)\TrayTest.pch"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\Mainfrm.cpp
DEP_CPP_MAINF=\
	".\stdafx.h"\
	".\TrayTest.h"\
	".\mainfrm.h"\
	".\trayicon.h"\
	

!IF  "$(CFG)" == "TrayTest - Win32 Release"


"$(INTDIR)\Mainfrm.obj" : $(SOURCE) $(DEP_CPP_MAINF) "$(INTDIR)"\
 "$(INTDIR)\TrayTest.pch"

"$(INTDIR)\Mainfrm.sbr" : $(SOURCE) $(DEP_CPP_MAINF) "$(INTDIR)"\
 "$(INTDIR)\TrayTest.pch"


!ELSEIF  "$(CFG)" == "TrayTest - Win32 Debug"


"$(INTDIR)\Mainfrm.obj" : $(SOURCE) $(DEP_CPP_MAINF) "$(INTDIR)"\
 "$(INTDIR)\TrayTest.pch"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\TrayIcon.CPP
DEP_CPP_TRAYI=\
	".\stdafx.h"\
	".\trayicon.h"\
	

!IF  "$(CFG)" == "TrayTest - Win32 Release"


"$(INTDIR)\TrayIcon.obj" : $(SOURCE) $(DEP_CPP_TRAYI) "$(INTDIR)"\
 "$(INTDIR)\TrayTest.pch"

"$(INTDIR)\TrayIcon.sbr" : $(SOURCE) $(DEP_CPP_TRAYI) "$(INTDIR)"\
 "$(INTDIR)\TrayTest.pch"


!ELSEIF  "$(CFG)" == "TrayTest - Win32 Debug"


"$(INTDIR)\TrayIcon.obj" : $(SOURCE) $(DEP_CPP_TRAYI) "$(INTDIR)"\
 "$(INTDIR)\TrayTest.pch"


!ENDIF 

# End Source File
# End Target
# End Project
################################################################################
