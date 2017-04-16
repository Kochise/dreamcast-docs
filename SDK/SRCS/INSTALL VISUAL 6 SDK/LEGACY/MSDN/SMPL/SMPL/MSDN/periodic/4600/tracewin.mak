# Microsoft Developer Studio Generated NMAKE File, Format Version 4.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Application" 0x0101

!IF "$(CFG)" == ""
CFG=TraceWin - Win32 Debug
!MESSAGE No configuration specified.  Defaulting to TraceWin - Win32 Debug.
!ENDIF 

!IF "$(CFG)" != "TraceWin - Win32 Release" && "$(CFG)" !=\
 "TraceWin - Win32 Debug"
!MESSAGE Invalid configuration "$(CFG)" specified.
!MESSAGE You can specify a configuration when running NMAKE on this makefile
!MESSAGE by defining the macro CFG on the command line.  For example:
!MESSAGE 
!MESSAGE NMAKE /f "Trwin4.mak" CFG="TraceWin - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "TraceWin - Win32 Release" (based on "Win32 (x86) Application")
!MESSAGE "TraceWin - Win32 Debug" (based on "Win32 (x86) Application")
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
# PROP Target_Last_Scanned "TraceWin - Win32 Debug"
MTL=mktyplib.exe
RSC=rc.exe
CPP=cl.exe

!IF  "$(CFG)" == "TraceWin - Win32 Release"

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

ALL : "$(OUTDIR)\TraceWin.EXE"

CLEAN : 
	-@erase ".\WinRel\TraceWin.EXE"
	-@erase ".\WinRel\MainFrm.obj"
	-@erase ".\WinRel\TraceWin.pch"
	-@erase ".\WinRel\App.OBJ"
	-@erase ".\WinRel\BufWnd.obj"
	-@erase ".\WinRel\WinPlace.obj"
	-@erase ".\WinRel\StdAfx.OBJ"
	-@erase ".\WinRel\TraceWin.res"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

# ADD BASE CPP /nologo /MT /W3 /GX /O1 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /FR /YX /c
# ADD CPP /nologo /MD /W3 /GX /O1 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /Yu"StdAfx.h" /c
# SUBTRACT CPP /Fr
CPP_PROJ=/nologo /MD /W3 /GX /O1 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D\
 "_AFXDLL" /D "_MBCS" /Fp"$(INTDIR)/TraceWin.pch" /Yu"StdAfx.h" /Fo"$(INTDIR)/" /c\
 
CPP_OBJS=.\WinRel/
CPP_SBRS=
# ADD BASE MTL /nologo /D "NDEBUG" /win32
# ADD MTL /nologo /D "NDEBUG" /win32
MTL_PROJ=/nologo /D "NDEBUG" /win32 
# ADD BASE RSC /l 0x409 /d "NDEBUG"
# ADD RSC /l 0x409 /d "NDEBUG" /d "_AFXDLL"
RSC_PROJ=/l 0x409 /fo"$(INTDIR)/TraceWin.res" /d "NDEBUG" /d "_AFXDLL" 
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
BSC32_FLAGS=/nologo /o"$(OUTDIR)/TraceWin.bsc" 
BSC32_SBRS=
LINK32=link.exe
# ADD BASE LINK32 oldnames.lib /nologo /stack:0x10240 /subsystem:windows /machine:IX86
# ADD LINK32 oldnames.lib /nologo /stack:0x10240 /subsystem:windows /machine:IX86 /out:"WinRel\TraceWin.EXE"
LINK32_FLAGS=oldnames.lib /nologo /stack:0x10240 /subsystem:windows\
 /incremental:no /pdb:"$(OUTDIR)/TraceWin.pdb" /machine:IX86\
 /out:"$(OUTDIR)/TraceWin.EXE" 
LINK32_OBJS= \
	"$(INTDIR)/MainFrm.obj" \
	"$(INTDIR)/App.OBJ" \
	"$(INTDIR)/BufWnd.obj" \
	"$(INTDIR)/WinPlace.obj" \
	"$(INTDIR)/StdAfx.OBJ" \
	"$(INTDIR)/TraceWin.res"

"$(OUTDIR)\TraceWin.EXE" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ELSEIF  "$(CFG)" == "TraceWin - Win32 Debug"

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

ALL : "$(OUTDIR)\TraceWin.EXE"

CLEAN : 
	-@erase ".\WinDebug\vc40.pdb"
	-@erase ".\WinDebug\TraceWin.pch"
	-@erase ".\WinDebug\vc40.idb"
	-@erase ".\WinDebug\TraceWin.EXE"
	-@erase ".\WinDebug\App.OBJ"
	-@erase ".\WinDebug\WinPlace.obj"
	-@erase ".\WinDebug\StdAfx.OBJ"
	-@erase ".\WinDebug\BufWnd.obj"
	-@erase ".\WinDebug\MainFrm.obj"
	-@erase ".\WinDebug\TraceWin.res"
	-@erase ".\WinDebug\TraceWin.ILK"
	-@erase ".\WinDebug\TraceWin.pdb"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

# ADD BASE CPP /nologo /MT /W3 /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /FR /YX /c
# ADD CPP /nologo /MDd /W3 /Gm /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /Yu"StdAfx.h" /c
# SUBTRACT CPP /Fr
CPP_PROJ=/nologo /MDd /W3 /Gm /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS"\
 /D "_AFXDLL" /D "_MBCS" /Fp"$(INTDIR)/TraceWin.pch" /Yu"StdAfx.h" /Fo"$(INTDIR)/"\
 /Fd"$(INTDIR)/" /c 
CPP_OBJS=.\WinDebug/
CPP_SBRS=
# ADD BASE MTL /nologo /D "_DEBUG" /win32
# ADD MTL /nologo /D "_DEBUG" /win32
MTL_PROJ=/nologo /D "_DEBUG" /win32 
# ADD BASE RSC /l 0x409 /d "_DEBUG"
# ADD RSC /l 0x409 /d "_DEBUG" /d "_AFXDLL"
RSC_PROJ=/l 0x409 /fo"$(INTDIR)/TraceWin.res" /d "_DEBUG" /d "_AFXDLL" 
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
BSC32_FLAGS=/nologo /o"$(OUTDIR)/TraceWin.bsc" 
BSC32_SBRS=
LINK32=link.exe
# ADD BASE LINK32 oldnames.lib /nologo /stack:0x10240 /subsystem:windows /debug /machine:IX86
# ADD LINK32 oldnames.lib /nologo /stack:0x10240 /subsystem:windows /debug /machine:IX86 /out:"WinDebug\TraceWin.EXE"
LINK32_FLAGS=oldnames.lib /nologo /stack:0x10240 /subsystem:windows\
 /incremental:yes /pdb:"$(OUTDIR)/TraceWin.pdb" /debug /machine:IX86\
 /out:"$(OUTDIR)/TraceWin.EXE" 
LINK32_OBJS= \
	"$(INTDIR)/App.OBJ" \
	"$(INTDIR)/WinPlace.obj" \
	"$(INTDIR)/StdAfx.OBJ" \
	"$(INTDIR)/BufWnd.obj" \
	"$(INTDIR)/MainFrm.obj" \
	"$(INTDIR)/TraceWin.res"

"$(OUTDIR)\TraceWin.EXE" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
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

# Name "TraceWin - Win32 Release"
# Name "TraceWin - Win32 Debug"

!IF  "$(CFG)" == "TraceWin - Win32 Release"

!ELSEIF  "$(CFG)" == "TraceWin - Win32 Debug"

!ENDIF 

################################################################################
# Begin Source File

SOURCE=.\TraceWin.rc
DEP_RSC_TRACE=\
	".\RES\TraceWin.ico"\
	".\RES\TraceWin.rc2"\
	

"$(INTDIR)\TraceWin.res" : $(SOURCE) $(DEP_RSC_TRACE) "$(INTDIR)"
   $(RSC) $(RSC_PROJ) $(SOURCE)


# End Source File
################################################################################
# Begin Source File

SOURCE=.\StdAfx.cpp
DEP_CPP_STDAF=\
	".\StdAfx.h"\
	

!IF  "$(CFG)" == "TraceWin - Win32 Release"

# ADD BASE CPP /Yc"StdAfx.h"
# ADD CPP /Yc"StdAfx.h"

BuildCmds= \
	$(CPP) /nologo /MD /W3 /GX /O1 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D\
 "_AFXDLL" /D "_MBCS" /Fp"$(INTDIR)/TraceWin.pch" /Yc"StdAfx.h" /Fo"$(INTDIR)/" /c\
 $(SOURCE) \
	

"$(INTDIR)\StdAfx.OBJ" : $(SOURCE) $(DEP_CPP_STDAF) "$(INTDIR)"
   $(BuildCmds)

"$(INTDIR)\TraceWin.pch" : $(SOURCE) $(DEP_CPP_STDAF) "$(INTDIR)"
   $(BuildCmds)

!ELSEIF  "$(CFG)" == "TraceWin - Win32 Debug"

# ADD BASE CPP /Yc"StdAfx.h"
# ADD CPP /Yc"StdAfx.h"

BuildCmds= \
	$(CPP) /nologo /MDd /W3 /Gm /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS"\
 /D "_AFXDLL" /D "_MBCS" /Fp"$(INTDIR)/TraceWin.pch" /Yc"StdAfx.h" /Fo"$(INTDIR)/"\
 /Fd"$(INTDIR)/" /c $(SOURCE) \
	

"$(INTDIR)\StdAfx.OBJ" : $(SOURCE) $(DEP_CPP_STDAF) "$(INTDIR)"
   $(BuildCmds)

"$(INTDIR)\TraceWin.pch" : $(SOURCE) $(DEP_CPP_STDAF) "$(INTDIR)"
   $(BuildCmds)

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\MainFrm.cpp
DEP_CPP_MAINF=\
	".\StdAfx.h"\
	".\App.h"\
	".\MainFrm.h"\
	".\WinPlace.h"\
	".\TraceWin.h"\
	".\BufWnd.h"\
	

"$(INTDIR)\MainFrm.obj" : $(SOURCE) $(DEP_CPP_MAINF) "$(INTDIR)"\
 "$(INTDIR)\TraceWin.pch"


# End Source File
################################################################################
# Begin Source File

SOURCE=.\App.cpp
DEP_CPP_APP_C=\
	".\StdAfx.h"\
	".\App.h"\
	".\MainFrm.h"\
	".\WinPlace.h"\
	".\BufWnd.h"\
	

"$(INTDIR)\App.OBJ" : $(SOURCE) $(DEP_CPP_APP_C) "$(INTDIR)"\
 "$(INTDIR)\TraceWin.pch"


# End Source File
################################################################################
# Begin Source File

SOURCE=.\BufWnd.cpp
DEP_CPP_BUFWN=\
	".\StdAfx.h"\
	".\BufWnd.h"\
	

"$(INTDIR)\BufWnd.obj" : $(SOURCE) $(DEP_CPP_BUFWN) "$(INTDIR)"\
 "$(INTDIR)\TraceWin.pch"


# End Source File
################################################################################
# Begin Source File

SOURCE=.\WinPlace.cpp
DEP_CPP_WINPL=\
	".\StdAfx.h"\
	".\WinPlace.h"\
	

"$(INTDIR)\WinPlace.obj" : $(SOURCE) $(DEP_CPP_WINPL) "$(INTDIR)"\
 "$(INTDIR)\TraceWin.pch"


# End Source File
# End Target
# End Project
################################################################################
