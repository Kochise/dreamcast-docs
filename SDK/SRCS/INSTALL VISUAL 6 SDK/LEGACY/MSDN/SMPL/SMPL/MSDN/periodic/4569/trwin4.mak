# Microsoft Developer Studio Generated NMAKE File, Format Version 4.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Application" 0x0101

!IF "$(CFG)" == ""
CFG=Tracewin - Win32 Debug
!MESSAGE No configuration specified.  Defaulting to Tracewin - Win32 Debug.
!ENDIF 

!IF "$(CFG)" != "Tracewin - Win32 Release" && "$(CFG)" !=\
 "Tracewin - Win32 Debug"
!MESSAGE Invalid configuration "$(CFG)" specified.
!MESSAGE You can specify a configuration when running NMAKE on this makefile
!MESSAGE by defining the macro CFG on the command line.  For example:
!MESSAGE 
!MESSAGE NMAKE /f "trwin4.mak" CFG="Tracewin - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "Tracewin - Win32 Release" (based on "Win32 (x86) Application")
!MESSAGE "Tracewin - Win32 Debug" (based on "Win32 (x86) Application")
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
MTL=mktyplib.exe
CPP=cl.exe
RSC=rc.exe

!IF  "$(CFG)" == "Tracewin - Win32 Release"

# PROP BASE Use_MFC 1
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "WinRel"
# PROP BASE Intermediate_Dir "WinRel"
# PROP Use_MFC 2
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "WinRel"
# PROP Intermediate_Dir "WinRel"
OUTDIR=.\WinRel
INTDIR=.\WinRel

ALL : "$(OUTDIR)\trwin4.exe"

CLEAN : 
	-@erase ".\WinRel\trwin4.exe"
	-@erase ".\WinRel\STDAFX.OBJ"
	-@erase ".\WinRel\mainfrm.obj"
	-@erase ".\WinRel\trwin4.pch"
	-@erase ".\WinRel\APP.OBJ"
	-@erase ".\WinRel\bufwnd.obj"
	-@erase ".\WinRel\TRACEWIN.res"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

# ADD BASE CPP /nologo /MT /W3 /GX /O1 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /FR /YX /c
# ADD CPP /nologo /MD /W3 /GX /O1 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /Yu"STDAFX.H" /c
# SUBTRACT CPP /Fr
CPP_PROJ=/nologo /MD /W3 /GX /O1 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D\
 "_AFXDLL" /D "_MBCS" /Fp"$(INTDIR)/trwin4.pch" /Yu"STDAFX.H" /Fo"$(INTDIR)/" /c\
 
CPP_OBJS=.\WinRel/
CPP_SBRS=
# ADD BASE MTL /nologo /D "NDEBUG" /win32
# ADD MTL /nologo /D "NDEBUG" /win32
MTL_PROJ=/nologo /D "NDEBUG" /win32 
# ADD BASE RSC /l 0x409 /d "NDEBUG"
# ADD RSC /l 0x409 /d "NDEBUG" /d "_AFXDLL"
RSC_PROJ=/l 0x409 /fo"$(INTDIR)/TRACEWIN.res" /d "NDEBUG" /d "_AFXDLL" 
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
BSC32_FLAGS=/nologo /o"$(OUTDIR)/trwin4.bsc" 
BSC32_SBRS=
LINK32=link.exe
# ADD BASE LINK32 oldnames.lib /nologo /stack:0x10240 /subsystem:windows /machine:IX86
# ADD LINK32 oldnames.lib /nologo /stack:0x10240 /subsystem:windows /machine:IX86
LINK32_FLAGS=oldnames.lib /nologo /stack:0x10240 /subsystem:windows\
 /incremental:no /pdb:"$(OUTDIR)/trwin4.pdb" /machine:IX86\
 /out:"$(OUTDIR)/trwin4.exe" 
LINK32_OBJS= \
	"$(INTDIR)/STDAFX.OBJ" \
	"$(INTDIR)/mainfrm.obj" \
	"$(INTDIR)/APP.OBJ" \
	"$(INTDIR)/bufwnd.obj" \
	"$(INTDIR)/TRACEWIN.res"

"$(OUTDIR)\trwin4.exe" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ELSEIF  "$(CFG)" == "Tracewin - Win32 Debug"

# PROP BASE Use_MFC 1
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "WinDebug"
# PROP BASE Intermediate_Dir "WinDebug"
# PROP Use_MFC 2
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "WinDebug"
# PROP Intermediate_Dir "WinDebug"
OUTDIR=.\WinDebug
INTDIR=.\WinDebug

ALL : "$(OUTDIR)\trwin4.exe"

CLEAN : 
	-@erase ".\WinDebug\vc40.pdb"
	-@erase ".\WinDebug\trwin4.pch"
	-@erase ".\WinDebug\vc40.idb"
	-@erase ".\WinDebug\trwin4.exe"
	-@erase ".\WinDebug\STDAFX.OBJ"
	-@erase ".\WinDebug\mainfrm.obj"
	-@erase ".\WinDebug\APP.OBJ"
	-@erase ".\WinDebug\bufwnd.obj"
	-@erase ".\WinDebug\TRACEWIN.res"
	-@erase ".\WinDebug\trwin4.ilk"
	-@erase ".\WinDebug\trwin4.pdb"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

# ADD BASE CPP /nologo /MT /W3 /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /FR /YX /c
# ADD CPP /nologo /MDd /W3 /Gm /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /Yu"STDAFX.H" /c
# SUBTRACT CPP /Fr
CPP_PROJ=/nologo /MDd /W3 /Gm /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS"\
 /D "_AFXDLL" /D "_MBCS" /Fp"$(INTDIR)/trwin4.pch" /Yu"STDAFX.H" /Fo"$(INTDIR)/"\
 /Fd"$(INTDIR)/" /c 
CPP_OBJS=.\WinDebug/
CPP_SBRS=
# ADD BASE MTL /nologo /D "_DEBUG" /win32
# ADD MTL /nologo /D "_DEBUG" /win32
MTL_PROJ=/nologo /D "_DEBUG" /win32 
# ADD BASE RSC /l 0x409 /d "_DEBUG"
# ADD RSC /l 0x409 /d "_DEBUG" /d "_AFXDLL"
RSC_PROJ=/l 0x409 /fo"$(INTDIR)/TRACEWIN.res" /d "_DEBUG" /d "_AFXDLL" 
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
BSC32_FLAGS=/nologo /o"$(OUTDIR)/trwin4.bsc" 
BSC32_SBRS=
LINK32=link.exe
# ADD BASE LINK32 oldnames.lib /nologo /stack:0x10240 /subsystem:windows /debug /machine:IX86
# ADD LINK32 oldnames.lib /nologo /stack:0x10240 /subsystem:windows /debug /machine:IX86
LINK32_FLAGS=oldnames.lib /nologo /stack:0x10240 /subsystem:windows\
 /incremental:yes /pdb:"$(OUTDIR)/trwin4.pdb" /debug /machine:IX86\
 /out:"$(OUTDIR)/trwin4.exe" 
LINK32_OBJS= \
	"$(INTDIR)/STDAFX.OBJ" \
	"$(INTDIR)/mainfrm.obj" \
	"$(INTDIR)/APP.OBJ" \
	"$(INTDIR)/bufwnd.obj" \
	"$(INTDIR)/TRACEWIN.res"

"$(OUTDIR)\trwin4.exe" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
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

# Name "Tracewin - Win32 Release"
# Name "Tracewin - Win32 Debug"

!IF  "$(CFG)" == "Tracewin - Win32 Release"

!ELSEIF  "$(CFG)" == "Tracewin - Win32 Debug"

!ENDIF 

################################################################################
# Begin Source File

SOURCE=.\TRACEWIN.RC
DEP_RSC_TRACE=\
	".\RES\TRACEWIN.ICO"\
	".\RES\TRACEWIN.RC2"\
	

"$(INTDIR)\TRACEWIN.res" : $(SOURCE) $(DEP_RSC_TRACE) "$(INTDIR)"
   $(RSC) $(RSC_PROJ) $(SOURCE)


# End Source File
################################################################################
# Begin Source File

SOURCE=.\STDAFX.CPP
DEP_CPP_STDAF=\
	".\STDAFX.H"\
	

!IF  "$(CFG)" == "Tracewin - Win32 Release"

# ADD BASE CPP /Yc"STDAFX.H"
# ADD CPP /Yc"STDAFX.H"

BuildCmds= \
	$(CPP) /nologo /MD /W3 /GX /O1 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D\
 "_AFXDLL" /D "_MBCS" /Fp"$(INTDIR)/trwin4.pch" /Yc"STDAFX.H" /Fo"$(INTDIR)/" /c\
 $(SOURCE) \
	

"$(INTDIR)\STDAFX.OBJ" : $(SOURCE) $(DEP_CPP_STDAF) "$(INTDIR)"
   $(BuildCmds)

"$(INTDIR)\trwin4.pch" : $(SOURCE) $(DEP_CPP_STDAF) "$(INTDIR)"
   $(BuildCmds)

!ELSEIF  "$(CFG)" == "Tracewin - Win32 Debug"

# ADD BASE CPP /Yc"STDAFX.H"
# ADD CPP /Yc"STDAFX.H"

BuildCmds= \
	$(CPP) /nologo /MDd /W3 /Gm /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS"\
 /D "_AFXDLL" /D "_MBCS" /Fp"$(INTDIR)/trwin4.pch" /Yc"STDAFX.H" /Fo"$(INTDIR)/"\
 /Fd"$(INTDIR)/" /c $(SOURCE) \
	

"$(INTDIR)\STDAFX.OBJ" : $(SOURCE) $(DEP_CPP_STDAF) "$(INTDIR)"
   $(BuildCmds)

"$(INTDIR)\trwin4.pch" : $(SOURCE) $(DEP_CPP_STDAF) "$(INTDIR)"
   $(BuildCmds)

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\mainfrm.cpp
DEP_CPP_MAINF=\
	".\STDAFX.H"\
	".\APP.H"\
	".\mainfrm.h"\
	".\TRACEWIN.H"\
	".\bufwnd.h"\
	

"$(INTDIR)\mainfrm.obj" : $(SOURCE) $(DEP_CPP_MAINF) "$(INTDIR)"\
 "$(INTDIR)\trwin4.pch"


# End Source File
################################################################################
# Begin Source File

SOURCE=.\APP.CPP
DEP_CPP_APP_C=\
	".\STDAFX.H"\
	".\APP.H"\
	".\mainfrm.h"\
	".\bufwnd.h"\
	

"$(INTDIR)\APP.OBJ" : $(SOURCE) $(DEP_CPP_APP_C) "$(INTDIR)"\
 "$(INTDIR)\trwin4.pch"


# End Source File
################################################################################
# Begin Source File

SOURCE=.\bufwnd.cpp
DEP_CPP_BUFWN=\
	".\STDAFX.H"\
	".\bufwnd.h"\
	

"$(INTDIR)\bufwnd.obj" : $(SOURCE) $(DEP_CPP_BUFWN) "$(INTDIR)"\
 "$(INTDIR)\trwin4.pch"


# End Source File
# End Target
# End Project
################################################################################
