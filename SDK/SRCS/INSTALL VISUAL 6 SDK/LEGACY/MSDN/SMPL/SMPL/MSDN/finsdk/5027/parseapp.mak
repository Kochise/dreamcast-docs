# Microsoft Developer Studio Generated NMAKE File, Format Version 4.10
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Application" 0x0101

!IF "$(CFG)" == ""
CFG=ParseApp - Win32 Debug
!MESSAGE No configuration specified.  Defaulting to ParseApp - Win32 Debug.
!ENDIF 

!IF "$(CFG)" != "ParseApp - Win32 Release" && "$(CFG)" !=\
 "ParseApp - Win32 Debug"
!MESSAGE Invalid configuration "$(CFG)" specified.
!MESSAGE You can specify a configuration when running NMAKE on this makefile
!MESSAGE by defining the macro CFG on the command line.  For example:
!MESSAGE 
!MESSAGE NMAKE /f "parseapp.mak" CFG="ParseApp - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "ParseApp - Win32 Release" (based on "Win32 (x86) Application")
!MESSAGE "ParseApp - Win32 Debug" (based on "Win32 (x86) Application")
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
# PROP Target_Last_Scanned "ParseApp - Win32 Debug"
RSC=rc.exe
MTL=mktyplib.exe
CPP=cl.exe

!IF  "$(CFG)" == "ParseApp - Win32 Release"

# PROP BASE Use_MFC 5
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

ALL : "$(OUTDIR)\parseapp.exe" "$(OUTDIR)\parseapp.pch"

CLEAN : 
	-@erase "$(INTDIR)\build.obj"
	-@erase "$(INTDIR)\ofcbuild.obj"
	-@erase "$(INTDIR)\ofclink.obj"
	-@erase "$(INTDIR)\ofcparse.obj"
	-@erase "$(INTDIR)\PAppDlg.obj"
	-@erase "$(INTDIR)\parse.obj"
	-@erase "$(INTDIR)\ParseApp.obj"
	-@erase "$(INTDIR)\parseapp.pch"
	-@erase "$(INTDIR)\ParseApp.res"
	-@erase "$(INTDIR)\pbanking.obj"
	-@erase "$(INTDIR)\pclean.obj"
	-@erase "$(INTDIR)\pelement.obj"
	-@erase "$(INTDIR)\ppayment.obj"
	-@erase "$(INTDIR)\StdAfx.obj"
	-@erase "$(INTDIR)\token.obj"
	-@erase "$(INTDIR)\validlst.obj"
	-@erase "$(OUTDIR)\parseapp.exe"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

# ADD BASE CPP /nologo /MT /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /Yu"stdafx.h" /c
# ADD CPP /nologo /MT /W4 /GX /O2 /D "NDEBUG" /D "WIN32" /D "_WINDOWS" /D "_MBCS" /D "_TESTAPP" /c
# SUBTRACT CPP /YX /Yc /Yu
CPP_PROJ=/nologo /MT /W4 /GX /O2 /D "NDEBUG" /D "WIN32" /D "_WINDOWS" /D\
 "_MBCS" /D "_TESTAPP" /Fo"$(INTDIR)/" /c 
CPP_OBJS=.\Release/
CPP_SBRS=.\.
# ADD BASE MTL /nologo /D "NDEBUG" /win32
# ADD MTL /nologo /D "NDEBUG" /win32
MTL_PROJ=/nologo /D "NDEBUG" /win32 
# ADD BASE RSC /l 0x409 /d "NDEBUG"
# ADD RSC /l 0x409 /d "NDEBUG"
RSC_PROJ=/l 0x409 /fo"$(INTDIR)/ParseApp.res" /d "NDEBUG" 
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
BSC32_FLAGS=/nologo /o"$(OUTDIR)/parseapp.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /machine:I386
# ADD LINK32 /nologo /subsystem:windows /machine:I386
LINK32_FLAGS=/nologo /subsystem:windows /incremental:no\
 /pdb:"$(OUTDIR)/parseapp.pdb" /machine:I386 /out:"$(OUTDIR)/parseapp.exe" 
LINK32_OBJS= \
	"$(INTDIR)\build.obj" \
	"$(INTDIR)\ofcbuild.obj" \
	"$(INTDIR)\ofclink.obj" \
	"$(INTDIR)\ofcparse.obj" \
	"$(INTDIR)\PAppDlg.obj" \
	"$(INTDIR)\parse.obj" \
	"$(INTDIR)\ParseApp.obj" \
	"$(INTDIR)\ParseApp.res" \
	"$(INTDIR)\pbanking.obj" \
	"$(INTDIR)\pclean.obj" \
	"$(INTDIR)\pelement.obj" \
	"$(INTDIR)\ppayment.obj" \
	"$(INTDIR)\StdAfx.obj" \
	"$(INTDIR)\token.obj" \
	"$(INTDIR)\validlst.obj"

"$(OUTDIR)\parseapp.exe" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ELSEIF  "$(CFG)" == "ParseApp - Win32 Debug"

# PROP BASE Use_MFC 5
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

ALL : "$(OUTDIR)\parseapp.exe" "$(OUTDIR)\parseapp.pch"

CLEAN : 
	-@erase "$(INTDIR)\build.obj"
	-@erase "$(INTDIR)\ofcbuild.obj"
	-@erase "$(INTDIR)\ofclink.obj"
	-@erase "$(INTDIR)\ofcparse.obj"
	-@erase "$(INTDIR)\PAppDlg.obj"
	-@erase "$(INTDIR)\parse.obj"
	-@erase "$(INTDIR)\ParseApp.obj"
	-@erase "$(INTDIR)\parseapp.pch"
	-@erase "$(INTDIR)\ParseApp.res"
	-@erase "$(INTDIR)\pbanking.obj"
	-@erase "$(INTDIR)\pclean.obj"
	-@erase "$(INTDIR)\pelement.obj"
	-@erase "$(INTDIR)\ppayment.obj"
	-@erase "$(INTDIR)\StdAfx.obj"
	-@erase "$(INTDIR)\token.obj"
	-@erase "$(INTDIR)\validlst.obj"
	-@erase "$(INTDIR)\vc40.idb"
	-@erase "$(INTDIR)\vc40.pdb"
	-@erase "$(OUTDIR)\parseapp.exe"
	-@erase "$(OUTDIR)\parseapp.ilk"
	-@erase "$(OUTDIR)\parseapp.pdb"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

# ADD BASE CPP /nologo /MTd /W3 /Gm /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /Yu"stdafx.h" /c
# ADD CPP /nologo /MTd /W4 /Gm /GX /Zi /Od /D "_DEBUG" /D "WIN32" /D "_WINDOWS" /D "_MBCS" /D "_TESTAPP" /c
# SUBTRACT CPP /YX /Yc /Yu
CPP_PROJ=/nologo /MTd /W4 /Gm /GX /Zi /Od /D "_DEBUG" /D "WIN32" /D "_WINDOWS"\
 /D "_MBCS" /D "_TESTAPP" /Fo"$(INTDIR)/" /Fd"$(INTDIR)/" /c 
CPP_OBJS=.\Debug/
CPP_SBRS=.\.
# ADD BASE MTL /nologo /D "_DEBUG" /win32
# ADD MTL /nologo /D "_DEBUG" /win32
MTL_PROJ=/nologo /D "_DEBUG" /win32 
# ADD BASE RSC /l 0x409 /d "_DEBUG"
# ADD RSC /l 0x409 /d "_DEBUG"
RSC_PROJ=/l 0x409 /fo"$(INTDIR)/ParseApp.res" /d "_DEBUG" 
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
BSC32_FLAGS=/nologo /o"$(OUTDIR)/parseapp.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /debug /machine:I386
# ADD LINK32 /nologo /subsystem:windows /debug /machine:I386
LINK32_FLAGS=/nologo /subsystem:windows /incremental:yes\
 /pdb:"$(OUTDIR)/parseapp.pdb" /debug /machine:I386\
 /out:"$(OUTDIR)/parseapp.exe" 
LINK32_OBJS= \
	"$(INTDIR)\build.obj" \
	"$(INTDIR)\ofcbuild.obj" \
	"$(INTDIR)\ofclink.obj" \
	"$(INTDIR)\ofcparse.obj" \
	"$(INTDIR)\PAppDlg.obj" \
	"$(INTDIR)\parse.obj" \
	"$(INTDIR)\ParseApp.obj" \
	"$(INTDIR)\ParseApp.res" \
	"$(INTDIR)\pbanking.obj" \
	"$(INTDIR)\pclean.obj" \
	"$(INTDIR)\pelement.obj" \
	"$(INTDIR)\ppayment.obj" \
	"$(INTDIR)\StdAfx.obj" \
	"$(INTDIR)\token.obj" \
	"$(INTDIR)\validlst.obj"

"$(OUTDIR)\parseapp.exe" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
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

# Name "ParseApp - Win32 Release"
# Name "ParseApp - Win32 Debug"

!IF  "$(CFG)" == "ParseApp - Win32 Release"

!ELSEIF  "$(CFG)" == "ParseApp - Win32 Debug"

!ENDIF 

################################################################################
# Begin Source File

SOURCE=.\ParseApp.cpp
DEP_CPP_PARSE=\
	".\PAppDlg.h"\
	".\ParseApp.h"\
	".\StdAfx.h"\
	

"$(INTDIR)\ParseApp.obj" : $(SOURCE) $(DEP_CPP_PARSE) "$(INTDIR)"


# End Source File
################################################################################
# Begin Source File

SOURCE=.\PAppDlg.cpp
DEP_CPP_PAPPD=\
	".\ofcbuild.h"\
	".\ofcdtd.h"\
	".\ofcparse.h"\
	".\PAppDlg.h"\
	".\ParseApp.h"\
	".\StdAfx.h"\
	".\validlst.h"\
	

"$(INTDIR)\PAppDlg.obj" : $(SOURCE) $(DEP_CPP_PAPPD) "$(INTDIR)"


# End Source File
################################################################################
# Begin Source File

SOURCE=.\StdAfx.cpp
DEP_CPP_STDAF=\
	".\StdAfx.h"\
	

!IF  "$(CFG)" == "ParseApp - Win32 Release"

# ADD CPP /Yc"stdafx.h"

BuildCmds= \
	$(CPP) /nologo /MT /W4 /GX /O2 /D "NDEBUG" /D "WIN32" /D "_WINDOWS" /D "_MBCS"\
 /D "_TESTAPP" /Fp"$(INTDIR)/parseapp.pch" /Yc"stdafx.h" /Fo"$(INTDIR)/" /c\
 $(SOURCE) \
	

"$(INTDIR)\StdAfx.obj" : $(SOURCE) $(DEP_CPP_STDAF) "$(INTDIR)"
   $(BuildCmds)

"$(INTDIR)\parseapp.pch" : $(SOURCE) $(DEP_CPP_STDAF) "$(INTDIR)"
   $(BuildCmds)

!ELSEIF  "$(CFG)" == "ParseApp - Win32 Debug"

# ADD CPP /Yc"stdafx.h"

BuildCmds= \
	$(CPP) /nologo /MTd /W4 /Gm /GX /Zi /Od /D "_DEBUG" /D "WIN32" /D "_WINDOWS"\
 /D "_MBCS" /D "_TESTAPP" /Fp"$(INTDIR)/parseapp.pch" /Yc"stdafx.h"\
 /Fo"$(INTDIR)/" /Fd"$(INTDIR)/" /c $(SOURCE) \
	

"$(INTDIR)\StdAfx.obj" : $(SOURCE) $(DEP_CPP_STDAF) "$(INTDIR)"
   $(BuildCmds)

"$(INTDIR)\parseapp.pch" : $(SOURCE) $(DEP_CPP_STDAF) "$(INTDIR)"
   $(BuildCmds)

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\ParseApp.rc
DEP_RSC_PARSEA=\
	".\res\ParseApp.ico"\
	".\res\ParseApp.rc2"\
	

"$(INTDIR)\ParseApp.res" : $(SOURCE) $(DEP_RSC_PARSEA) "$(INTDIR)"
   $(RSC) $(RSC_PROJ) $(SOURCE)


# End Source File
################################################################################
# Begin Source File

SOURCE=.\parse.c
DEP_CPP_PARSE_=\
	".\ofcdtd.h"\
	".\ofclink.h"\
	".\parse.h"\
	".\pbtypes.h"\
	

"$(INTDIR)\parse.obj" : $(SOURCE) $(DEP_CPP_PARSE_) "$(INTDIR)"


# End Source File
################################################################################
# Begin Source File

SOURCE=.\ofclink.c
DEP_CPP_OFCLI=\
	".\ofcdtd.h"\
	".\ofclink.h"\
	

"$(INTDIR)\ofclink.obj" : $(SOURCE) $(DEP_CPP_OFCLI) "$(INTDIR)"


# End Source File
################################################################################
# Begin Source File

SOURCE=.\ofcparse.c
DEP_CPP_OFCPA=\
	".\ofcdtd.h"\
	".\ofcparse.h"\
	".\parse.h"\
	".\pbtypes.h"\
	

"$(INTDIR)\ofcparse.obj" : $(SOURCE) $(DEP_CPP_OFCPA) "$(INTDIR)"


# End Source File
################################################################################
# Begin Source File

SOURCE=.\validlst.c
DEP_CPP_VALID=\
	".\ofcdtd.h"\
	".\validlst.h"\
	

"$(INTDIR)\validlst.obj" : $(SOURCE) $(DEP_CPP_VALID) "$(INTDIR)"


# End Source File
################################################################################
# Begin Source File

SOURCE=.\token.c
DEP_CPP_TOKEN=\
	".\ofcdtd.h"\
	".\ofclink.h"\
	".\parse.h"\
	".\pbtypes.h"\
	

"$(INTDIR)\token.obj" : $(SOURCE) $(DEP_CPP_TOKEN) "$(INTDIR)"


# End Source File
################################################################################
# Begin Source File

SOURCE=.\pelement.c
DEP_CPP_PELEM=\
	".\ofcdtd.h"\
	".\ofclink.h"\
	".\parse.h"\
	".\pbtypes.h"\
	

"$(INTDIR)\pelement.obj" : $(SOURCE) $(DEP_CPP_PELEM) "$(INTDIR)"


# End Source File
################################################################################
# Begin Source File

SOURCE=.\pbanking.c
DEP_CPP_PBANK=\
	".\ofcdtd.h"\
	".\ofclink.h"\
	".\parse.h"\
	".\pbtypes.h"\
	

"$(INTDIR)\pbanking.obj" : $(SOURCE) $(DEP_CPP_PBANK) "$(INTDIR)"


# End Source File
################################################################################
# Begin Source File

SOURCE=.\ppayment.c
DEP_CPP_PPAYM=\
	".\ofcdtd.h"\
	".\ofclink.h"\
	".\parse.h"\
	".\pbtypes.h"\
	

"$(INTDIR)\ppayment.obj" : $(SOURCE) $(DEP_CPP_PPAYM) "$(INTDIR)"


# End Source File
################################################################################
# Begin Source File

SOURCE=.\build.c
DEP_CPP_BUILD=\
	".\build.h"\
	".\ofcdtd.h"\
	".\pbtypes.h"\
	".\validlst.h"\
	

"$(INTDIR)\build.obj" : $(SOURCE) $(DEP_CPP_BUILD) "$(INTDIR)"


# End Source File
################################################################################
# Begin Source File

SOURCE=.\ofcbuild.c
DEP_CPP_OFCBU=\
	".\build.h"\
	".\ofcbuild.h"\
	".\ofcdtd.h"\
	".\pbtypes.h"\
	

"$(INTDIR)\ofcbuild.obj" : $(SOURCE) $(DEP_CPP_OFCBU) "$(INTDIR)"


# End Source File
################################################################################
# Begin Source File

SOURCE=.\pclean.c
DEP_CPP_PCLEA=\
	".\ofcdtd.h"\
	".\parse.h"\
	".\pbtypes.h"\
	

"$(INTDIR)\pclean.obj" : $(SOURCE) $(DEP_CPP_PCLEA) "$(INTDIR)"


# End Source File
# End Target
# End Project
################################################################################
