# Microsoft Developer Studio Generated NMAKE File, Format Version 4.10
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Static Library" 0x0104

!IF "$(CFG)" == ""
CFG=VC_FRAMEWORK - Win32 Debug
!MESSAGE No configuration specified.  Defaulting to VC_FRAMEWORK - Win32 Debug.
!ENDIF 

!IF "$(CFG)" != "VC_FRAMEWORK - Win32 Release" && "$(CFG)" !=\
 "VC_FRAMEWORK - Win32 Debug"
!MESSAGE Invalid configuration "$(CFG)" specified.
!MESSAGE You can specify a configuration when running NMAKE on this makefile
!MESSAGE by defining the macro CFG on the command line.  For example:
!MESSAGE 
!MESSAGE NMAKE /f "VC_FRAMEWORK.mak" CFG="VC_FRAMEWORK - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "VC_FRAMEWORK - Win32 Release" (based on "Win32 (x86) Static Library")
!MESSAGE "VC_FRAMEWORK - Win32 Debug" (based on "Win32 (x86) Static Library")
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
# PROP Target_Last_Scanned "VC_FRAMEWORK - Win32 Debug"
CPP=cl.exe

!IF  "$(CFG)" == "VC_FRAMEWORK - Win32 Release"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "VC_FRAME"
# PROP BASE Intermediate_Dir "VC_FRAME"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "RELEASE"
# PROP Intermediate_Dir "RELEASE"
# PROP Target_Dir ""
OUTDIR=.\RELEASE
INTDIR=.\RELEASE

ALL : "$(OUTDIR)\AxfwR.lib"

CLEAN : 
	-@erase "$(INTDIR)\AUTOOBJ.OBJ"
	-@erase "$(INTDIR)\CLASSF.OBJ"
	-@erase "$(INTDIR)\CTLEMBED.OBJ"
	-@erase "$(INTDIR)\CTLHELP.OBJ"
	-@erase "$(INTDIR)\CTLMISC.OBJ"
	-@erase "$(INTDIR)\CTLOCX96.OBJ"
	-@erase "$(INTDIR)\CTLPSST.OBJ"
	-@erase "$(INTDIR)\CTLVIEW.OBJ"
	-@erase "$(INTDIR)\CTLWRAP.OBJ"
	-@erase "$(INTDIR)\DEBUG.OBJ"
	-@erase "$(INTDIR)\GLOBALS.OBJ"
	-@erase "$(INTDIR)\IPSERVER.OBJ"
	-@erase "$(INTDIR)\PROPPAGE.OBJ"
	-@erase "$(INTDIR)\STDENUM.OBJ"
	-@erase "$(INTDIR)\UNKNOWN.OBJ"
	-@erase "$(INTDIR)\UTIL.OBJ"
	-@erase "$(OUTDIR)\AxfwR.lib"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

# ADD BASE CPP /nologo /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /YX /c
# ADD CPP /nologo /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /YX /TP /c
CPP_PROJ=/nologo /ML /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS"\
 /Fp"$(INTDIR)/VC_FRAMEWORK.pch" /YX /Fo"$(INTDIR)/" /TP /c 
CPP_OBJS=.\RELEASE/
CPP_SBRS=.\.
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
BSC32_FLAGS=/nologo /o"$(OUTDIR)/VC_FRAMEWORK.bsc" 
BSC32_SBRS= \
	
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo
# ADD LIB32 /nologo /out:"release\AxfwR.lib"
LIB32_FLAGS=/nologo /out:"$(OUTDIR)/AxfwR.lib" 
LIB32_OBJS= \
	"$(INTDIR)\AUTOOBJ.OBJ" \
	"$(INTDIR)\CLASSF.OBJ" \
	"$(INTDIR)\CTLEMBED.OBJ" \
	"$(INTDIR)\CTLHELP.OBJ" \
	"$(INTDIR)\CTLMISC.OBJ" \
	"$(INTDIR)\CTLOCX96.OBJ" \
	"$(INTDIR)\CTLPSST.OBJ" \
	"$(INTDIR)\CTLVIEW.OBJ" \
	"$(INTDIR)\CTLWRAP.OBJ" \
	"$(INTDIR)\DEBUG.OBJ" \
	"$(INTDIR)\GLOBALS.OBJ" \
	"$(INTDIR)\IPSERVER.OBJ" \
	"$(INTDIR)\PROPPAGE.OBJ" \
	"$(INTDIR)\STDENUM.OBJ" \
	"$(INTDIR)\UNKNOWN.OBJ" \
	"$(INTDIR)\UTIL.OBJ"

"$(OUTDIR)\AxfwR.lib" : "$(OUTDIR)" $(DEF_FILE) $(LIB32_OBJS)
    $(LIB32) @<<
  $(LIB32_FLAGS) $(DEF_FLAGS) $(LIB32_OBJS)
<<

!ELSEIF  "$(CFG)" == "VC_FRAMEWORK - Win32 Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "VC_FRAM0"
# PROP BASE Intermediate_Dir "VC_FRAM0"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "DEBUG"
# PROP Intermediate_Dir "DEBUG"
# PROP Target_Dir ""
OUTDIR=.\DEBUG
INTDIR=.\DEBUG

ALL : "$(OUTDIR)\AxfwD.lib" "$(OUTDIR)\VC_FRAMEWORK.bsc"

CLEAN : 
	-@erase "$(INTDIR)\AUTOOBJ.OBJ"
	-@erase "$(INTDIR)\AUTOOBJ.SBR"
	-@erase "$(INTDIR)\CLASSF.OBJ"
	-@erase "$(INTDIR)\CLASSF.SBR"
	-@erase "$(INTDIR)\CTLEMBED.OBJ"
	-@erase "$(INTDIR)\CTLEMBED.SBR"
	-@erase "$(INTDIR)\CTLHELP.OBJ"
	-@erase "$(INTDIR)\CTLHELP.SBR"
	-@erase "$(INTDIR)\CTLMISC.OBJ"
	-@erase "$(INTDIR)\CTLMISC.SBR"
	-@erase "$(INTDIR)\CTLOCX96.OBJ"
	-@erase "$(INTDIR)\CTLOCX96.SBR"
	-@erase "$(INTDIR)\CTLPSST.OBJ"
	-@erase "$(INTDIR)\CTLPSST.SBR"
	-@erase "$(INTDIR)\CTLVIEW.OBJ"
	-@erase "$(INTDIR)\CTLVIEW.SBR"
	-@erase "$(INTDIR)\CTLWRAP.OBJ"
	-@erase "$(INTDIR)\CTLWRAP.SBR"
	-@erase "$(INTDIR)\DEBUG.OBJ"
	-@erase "$(INTDIR)\DEBUG.SBR"
	-@erase "$(INTDIR)\GLOBALS.OBJ"
	-@erase "$(INTDIR)\GLOBALS.SBR"
	-@erase "$(INTDIR)\IPSERVER.OBJ"
	-@erase "$(INTDIR)\IPSERVER.SBR"
	-@erase "$(INTDIR)\PROPPAGE.OBJ"
	-@erase "$(INTDIR)\PROPPAGE.SBR"
	-@erase "$(INTDIR)\STDENUM.OBJ"
	-@erase "$(INTDIR)\STDENUM.SBR"
	-@erase "$(INTDIR)\UNKNOWN.OBJ"
	-@erase "$(INTDIR)\UNKNOWN.SBR"
	-@erase "$(INTDIR)\UTIL.OBJ"
	-@erase "$(INTDIR)\UTIL.SBR"
	-@erase "$(OUTDIR)\AxfwD.lib"
	-@erase "$(OUTDIR)\VC_FRAMEWORK.bsc"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

# ADD BASE CPP /nologo /W3 /GX /Z7 /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /YX /c
# ADD CPP /nologo /W3 /GX /Z7 /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /FR /YX /TP /c
CPP_PROJ=/nologo /MLd /W3 /GX /Z7 /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS"\
 /FR"$(INTDIR)/" /Fp"$(INTDIR)/VC_FRAMEWORK.pch" /YX /Fo"$(INTDIR)/" /TP /c 
CPP_OBJS=.\DEBUG/
CPP_SBRS=.\DEBUG/
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
BSC32_FLAGS=/nologo /o"$(OUTDIR)/VC_FRAMEWORK.bsc" 
BSC32_SBRS= \
	"$(INTDIR)\AUTOOBJ.SBR" \
	"$(INTDIR)\CLASSF.SBR" \
	"$(INTDIR)\CTLEMBED.SBR" \
	"$(INTDIR)\CTLHELP.SBR" \
	"$(INTDIR)\CTLMISC.SBR" \
	"$(INTDIR)\CTLOCX96.SBR" \
	"$(INTDIR)\CTLPSST.SBR" \
	"$(INTDIR)\CTLVIEW.SBR" \
	"$(INTDIR)\CTLWRAP.SBR" \
	"$(INTDIR)\DEBUG.SBR" \
	"$(INTDIR)\GLOBALS.SBR" \
	"$(INTDIR)\IPSERVER.SBR" \
	"$(INTDIR)\PROPPAGE.SBR" \
	"$(INTDIR)\STDENUM.SBR" \
	"$(INTDIR)\UNKNOWN.SBR" \
	"$(INTDIR)\UTIL.SBR"

"$(OUTDIR)\VC_FRAMEWORK.bsc" : "$(OUTDIR)" $(BSC32_SBRS)
    $(BSC32) @<<
  $(BSC32_FLAGS) $(BSC32_SBRS)
<<

LIB32=link.exe -lib
# ADD BASE LIB32 /nologo
# ADD LIB32 /nologo /out:"debug\AxfwD.lib"
LIB32_FLAGS=/nologo /out:"$(OUTDIR)/AxfwD.lib" 
LIB32_OBJS= \
	"$(INTDIR)\AUTOOBJ.OBJ" \
	"$(INTDIR)\CLASSF.OBJ" \
	"$(INTDIR)\CTLEMBED.OBJ" \
	"$(INTDIR)\CTLHELP.OBJ" \
	"$(INTDIR)\CTLMISC.OBJ" \
	"$(INTDIR)\CTLOCX96.OBJ" \
	"$(INTDIR)\CTLPSST.OBJ" \
	"$(INTDIR)\CTLVIEW.OBJ" \
	"$(INTDIR)\CTLWRAP.OBJ" \
	"$(INTDIR)\DEBUG.OBJ" \
	"$(INTDIR)\GLOBALS.OBJ" \
	"$(INTDIR)\IPSERVER.OBJ" \
	"$(INTDIR)\PROPPAGE.OBJ" \
	"$(INTDIR)\STDENUM.OBJ" \
	"$(INTDIR)\UNKNOWN.OBJ" \
	"$(INTDIR)\UTIL.OBJ"

"$(OUTDIR)\AxfwD.lib" : "$(OUTDIR)" $(DEF_FILE) $(LIB32_OBJS)
    $(LIB32) @<<
  $(LIB32_FLAGS) $(DEF_FLAGS) $(LIB32_OBJS)
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

# Name "VC_FRAMEWORK - Win32 Release"
# Name "VC_FRAMEWORK - Win32 Debug"

!IF  "$(CFG)" == "VC_FRAMEWORK - Win32 Release"

!ELSEIF  "$(CFG)" == "VC_FRAMEWORK - Win32 Debug"

!ENDIF 

################################################################################
# Begin Source File

SOURCE=.\AUTOOBJ.CPP
DEP_CPP_AUTOO=\
	"..\..\MSDEV\INCLUDE\Debug.H"\
	{$(INCLUDE)}"\AutoObj.H"\
	{$(INCLUDE)}"\Globals.H"\
	{$(INCLUDE)}"\IPServer.H"\
	{$(INCLUDE)}"\LocalSrv.H"\
	{$(INCLUDE)}"\StdEnum.H"\
	{$(INCLUDE)}"\Unknown.H"\
	{$(INCLUDE)}"\Util.H"\
	

!IF  "$(CFG)" == "VC_FRAMEWORK - Win32 Release"


"$(INTDIR)\AUTOOBJ.OBJ" : $(SOURCE) $(DEP_CPP_AUTOO) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "VC_FRAMEWORK - Win32 Debug"


"$(INTDIR)\AUTOOBJ.OBJ" : $(SOURCE) $(DEP_CPP_AUTOO) "$(INTDIR)"

"$(INTDIR)\AUTOOBJ.SBR" : $(SOURCE) $(DEP_CPP_AUTOO) "$(INTDIR)"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\UTIL.CPP
DEP_CPP_UTIL_=\
	"..\..\MSDEV\INCLUDE\Debug.H"\
	{$(INCLUDE)}"\Globals.H"\
	{$(INCLUDE)}"\IPServer.H"\
	{$(INCLUDE)}"\Util.H"\
	

!IF  "$(CFG)" == "VC_FRAMEWORK - Win32 Release"


"$(INTDIR)\UTIL.OBJ" : $(SOURCE) $(DEP_CPP_UTIL_) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "VC_FRAMEWORK - Win32 Debug"


"$(INTDIR)\UTIL.OBJ" : $(SOURCE) $(DEP_CPP_UTIL_) "$(INTDIR)"

"$(INTDIR)\UTIL.SBR" : $(SOURCE) $(DEP_CPP_UTIL_) "$(INTDIR)"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\CTLEMBED.CPP
DEP_CPP_CTLEM=\
	"..\..\MSDEV\INCLUDE\Debug.H"\
	".\CtlHelp.H"\
	{$(INCLUDE)}"\AutoObj.H"\
	{$(INCLUDE)}"\CtrlObj.H"\
	{$(INCLUDE)}"\Globals.H"\
	{$(INCLUDE)}"\IPServer.H"\
	{$(INCLUDE)}"\LocalSrv.H"\
	{$(INCLUDE)}"\StdEnum.H"\
	{$(INCLUDE)}"\Unknown.H"\
	{$(INCLUDE)}"\Util.H"\
	

!IF  "$(CFG)" == "VC_FRAMEWORK - Win32 Release"


"$(INTDIR)\CTLEMBED.OBJ" : $(SOURCE) $(DEP_CPP_CTLEM) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "VC_FRAMEWORK - Win32 Debug"


"$(INTDIR)\CTLEMBED.OBJ" : $(SOURCE) $(DEP_CPP_CTLEM) "$(INTDIR)"

"$(INTDIR)\CTLEMBED.SBR" : $(SOURCE) $(DEP_CPP_CTLEM) "$(INTDIR)"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\CTLHELP.CPP
DEP_CPP_CTLHE=\
	"..\..\MSDEV\INCLUDE\Debug.H"\
	".\CtlHelp.H"\
	{$(INCLUDE)}"\AutoObj.H"\
	{$(INCLUDE)}"\CtrlObj.H"\
	{$(INCLUDE)}"\Globals.H"\
	{$(INCLUDE)}"\IPServer.H"\
	{$(INCLUDE)}"\LocalSrv.H"\
	{$(INCLUDE)}"\Unknown.H"\
	{$(INCLUDE)}"\Util.H"\
	

!IF  "$(CFG)" == "VC_FRAMEWORK - Win32 Release"


"$(INTDIR)\CTLHELP.OBJ" : $(SOURCE) $(DEP_CPP_CTLHE) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "VC_FRAMEWORK - Win32 Debug"


"$(INTDIR)\CTLHELP.OBJ" : $(SOURCE) $(DEP_CPP_CTLHE) "$(INTDIR)"

"$(INTDIR)\CTLHELP.SBR" : $(SOURCE) $(DEP_CPP_CTLHE) "$(INTDIR)"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\CTLMISC.CPP
DEP_CPP_CTLMI=\
	"..\..\MSDEV\INCLUDE\Debug.H"\
	".\CtlHelp.H"\
	{$(INCLUDE)}"\AutoObj.H"\
	{$(INCLUDE)}"\CtrlObj.H"\
	{$(INCLUDE)}"\Globals.H"\
	{$(INCLUDE)}"\IPServer.H"\
	{$(INCLUDE)}"\LocalSrv.H"\
	{$(INCLUDE)}"\Unknown.H"\
	{$(INCLUDE)}"\Util.H"\
	

!IF  "$(CFG)" == "VC_FRAMEWORK - Win32 Release"


"$(INTDIR)\CTLMISC.OBJ" : $(SOURCE) $(DEP_CPP_CTLMI) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "VC_FRAMEWORK - Win32 Debug"


"$(INTDIR)\CTLMISC.OBJ" : $(SOURCE) $(DEP_CPP_CTLMI) "$(INTDIR)"

"$(INTDIR)\CTLMISC.SBR" : $(SOURCE) $(DEP_CPP_CTLMI) "$(INTDIR)"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\CTLOCX96.CPP
DEP_CPP_CTLOC=\
	"..\..\MSDEV\INCLUDE\Debug.H"\
	{$(INCLUDE)}"\AutoObj.H"\
	{$(INCLUDE)}"\CtrlObj.H"\
	{$(INCLUDE)}"\Globals.H"\
	{$(INCLUDE)}"\IPServer.H"\
	{$(INCLUDE)}"\LocalSrv.H"\
	{$(INCLUDE)}"\Unknown.H"\
	

!IF  "$(CFG)" == "VC_FRAMEWORK - Win32 Release"


"$(INTDIR)\CTLOCX96.OBJ" : $(SOURCE) $(DEP_CPP_CTLOC) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "VC_FRAMEWORK - Win32 Debug"


"$(INTDIR)\CTLOCX96.OBJ" : $(SOURCE) $(DEP_CPP_CTLOC) "$(INTDIR)"

"$(INTDIR)\CTLOCX96.SBR" : $(SOURCE) $(DEP_CPP_CTLOC) "$(INTDIR)"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\CTLPSST.CPP
DEP_CPP_CTLPS=\
	"..\..\MSDEV\INCLUDE\Debug.H"\
	".\CtlHelp.H"\
	{$(INCLUDE)}"\AutoObj.H"\
	{$(INCLUDE)}"\CtrlObj.H"\
	{$(INCLUDE)}"\Globals.H"\
	{$(INCLUDE)}"\IPServer.H"\
	{$(INCLUDE)}"\LocalSrv.H"\
	{$(INCLUDE)}"\Unknown.H"\
	{$(INCLUDE)}"\Util.H"\
	

!IF  "$(CFG)" == "VC_FRAMEWORK - Win32 Release"


"$(INTDIR)\CTLPSST.OBJ" : $(SOURCE) $(DEP_CPP_CTLPS) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "VC_FRAMEWORK - Win32 Debug"


"$(INTDIR)\CTLPSST.OBJ" : $(SOURCE) $(DEP_CPP_CTLPS) "$(INTDIR)"

"$(INTDIR)\CTLPSST.SBR" : $(SOURCE) $(DEP_CPP_CTLPS) "$(INTDIR)"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\CTLVIEW.CPP
DEP_CPP_CTLVI=\
	"..\..\MSDEV\INCLUDE\Debug.H"\
	{$(INCLUDE)}"\AutoObj.H"\
	{$(INCLUDE)}"\CtrlObj.H"\
	{$(INCLUDE)}"\Globals.H"\
	{$(INCLUDE)}"\IPServer.H"\
	{$(INCLUDE)}"\LocalSrv.H"\
	{$(INCLUDE)}"\Unknown.H"\
	{$(INCLUDE)}"\Util.H"\
	

!IF  "$(CFG)" == "VC_FRAMEWORK - Win32 Release"


"$(INTDIR)\CTLVIEW.OBJ" : $(SOURCE) $(DEP_CPP_CTLVI) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "VC_FRAMEWORK - Win32 Debug"


"$(INTDIR)\CTLVIEW.OBJ" : $(SOURCE) $(DEP_CPP_CTLVI) "$(INTDIR)"

"$(INTDIR)\CTLVIEW.SBR" : $(SOURCE) $(DEP_CPP_CTLVI) "$(INTDIR)"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\CTLWRAP.CPP
DEP_CPP_CTLWR=\
	"..\..\MSDEV\INCLUDE\Debug.H"\
	{$(INCLUDE)}"\AutoObj.H"\
	{$(INCLUDE)}"\CtrlObj.H"\
	{$(INCLUDE)}"\IPServer.H"\
	{$(INCLUDE)}"\LocalSrv.H"\
	{$(INCLUDE)}"\Unknown.H"\
	

!IF  "$(CFG)" == "VC_FRAMEWORK - Win32 Release"


"$(INTDIR)\CTLWRAP.OBJ" : $(SOURCE) $(DEP_CPP_CTLWR) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "VC_FRAMEWORK - Win32 Debug"


"$(INTDIR)\CTLWRAP.OBJ" : $(SOURCE) $(DEP_CPP_CTLWR) "$(INTDIR)"

"$(INTDIR)\CTLWRAP.SBR" : $(SOURCE) $(DEP_CPP_CTLWR) "$(INTDIR)"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\DEBUG.CPP
DEP_CPP_DEBUG=\
	"..\..\MSDEV\INCLUDE\Debug.H"\
	{$(INCLUDE)}"\IPServer.H"\
	

!IF  "$(CFG)" == "VC_FRAMEWORK - Win32 Release"


"$(INTDIR)\DEBUG.OBJ" : $(SOURCE) $(DEP_CPP_DEBUG) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "VC_FRAMEWORK - Win32 Debug"


"$(INTDIR)\DEBUG.OBJ" : $(SOURCE) $(DEP_CPP_DEBUG) "$(INTDIR)"

"$(INTDIR)\DEBUG.SBR" : $(SOURCE) $(DEP_CPP_DEBUG) "$(INTDIR)"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\GLOBALS.C
DEP_CPP_GLOBA=\
	"..\..\MSDEV\INCLUDE\Debug.H"\
	{$(INCLUDE)}"\IPServer.H"\
	

!IF  "$(CFG)" == "VC_FRAMEWORK - Win32 Release"


"$(INTDIR)\GLOBALS.OBJ" : $(SOURCE) $(DEP_CPP_GLOBA) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "VC_FRAMEWORK - Win32 Debug"


"$(INTDIR)\GLOBALS.OBJ" : $(SOURCE) $(DEP_CPP_GLOBA) "$(INTDIR)"

"$(INTDIR)\GLOBALS.SBR" : $(SOURCE) $(DEP_CPP_GLOBA) "$(INTDIR)"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\IPSERVER.CPP
DEP_CPP_IPSER=\
	"..\..\MSDEV\INCLUDE\Debug.H"\
	".\ClassF.H"\
	{$(INCLUDE)}"\AutoObj.H"\
	{$(INCLUDE)}"\CtrlObj.H"\
	{$(INCLUDE)}"\Globals.H"\
	{$(INCLUDE)}"\IPServer.H"\
	{$(INCLUDE)}"\LocalSrv.H"\
	{$(INCLUDE)}"\Unknown.H"\
	{$(INCLUDE)}"\Util.H"\
	

!IF  "$(CFG)" == "VC_FRAMEWORK - Win32 Release"


"$(INTDIR)\IPSERVER.OBJ" : $(SOURCE) $(DEP_CPP_IPSER) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "VC_FRAMEWORK - Win32 Debug"


"$(INTDIR)\IPSERVER.OBJ" : $(SOURCE) $(DEP_CPP_IPSER) "$(INTDIR)"

"$(INTDIR)\IPSERVER.SBR" : $(SOURCE) $(DEP_CPP_IPSER) "$(INTDIR)"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\PROPPAGE.CPP
DEP_CPP_PROPP=\
	"..\..\MSDEV\INCLUDE\Debug.H"\
	{$(INCLUDE)}"\Globals.H"\
	{$(INCLUDE)}"\IPServer.H"\
	{$(INCLUDE)}"\LocalSrv.H"\
	{$(INCLUDE)}"\PropPage.H"\
	{$(INCLUDE)}"\Unknown.H"\
	{$(INCLUDE)}"\Util.H"\
	

!IF  "$(CFG)" == "VC_FRAMEWORK - Win32 Release"


"$(INTDIR)\PROPPAGE.OBJ" : $(SOURCE) $(DEP_CPP_PROPP) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "VC_FRAMEWORK - Win32 Debug"


"$(INTDIR)\PROPPAGE.OBJ" : $(SOURCE) $(DEP_CPP_PROPP) "$(INTDIR)"

"$(INTDIR)\PROPPAGE.SBR" : $(SOURCE) $(DEP_CPP_PROPP) "$(INTDIR)"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\STDENUM.CPP
DEP_CPP_STDEN=\
	"..\..\MSDEV\INCLUDE\Debug.H"\
	{$(INCLUDE)}"\Globals.H"\
	{$(INCLUDE)}"\IPServer.H"\
	{$(INCLUDE)}"\StdEnum.H"\
	{$(INCLUDE)}"\Unknown.H"\
	

!IF  "$(CFG)" == "VC_FRAMEWORK - Win32 Release"


"$(INTDIR)\STDENUM.OBJ" : $(SOURCE) $(DEP_CPP_STDEN) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "VC_FRAMEWORK - Win32 Debug"


"$(INTDIR)\STDENUM.OBJ" : $(SOURCE) $(DEP_CPP_STDEN) "$(INTDIR)"

"$(INTDIR)\STDENUM.SBR" : $(SOURCE) $(DEP_CPP_STDEN) "$(INTDIR)"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\UNKNOWN.CPP
DEP_CPP_UNKNO=\
	"..\..\MSDEV\INCLUDE\Debug.H"\
	{$(INCLUDE)}"\IPServer.H"\
	{$(INCLUDE)}"\Unknown.H"\
	

!IF  "$(CFG)" == "VC_FRAMEWORK - Win32 Release"


"$(INTDIR)\UNKNOWN.OBJ" : $(SOURCE) $(DEP_CPP_UNKNO) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "VC_FRAMEWORK - Win32 Debug"


"$(INTDIR)\UNKNOWN.OBJ" : $(SOURCE) $(DEP_CPP_UNKNO) "$(INTDIR)"

"$(INTDIR)\UNKNOWN.SBR" : $(SOURCE) $(DEP_CPP_UNKNO) "$(INTDIR)"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\CLASSF.CPP
DEP_CPP_CLASS=\
	"..\..\MSDEV\INCLUDE\Debug.H"\
	".\ClassF.H"\
	{$(INCLUDE)}"\Globals.H"\
	{$(INCLUDE)}"\IPServer.H"\
	{$(INCLUDE)}"\LocalSrv.H"\
	{$(INCLUDE)}"\Unknown.H"\
	

!IF  "$(CFG)" == "VC_FRAMEWORK - Win32 Release"


"$(INTDIR)\CLASSF.OBJ" : $(SOURCE) $(DEP_CPP_CLASS) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "VC_FRAMEWORK - Win32 Debug"


"$(INTDIR)\CLASSF.OBJ" : $(SOURCE) $(DEP_CPP_CLASS) "$(INTDIR)"

"$(INTDIR)\CLASSF.SBR" : $(SOURCE) $(DEP_CPP_CLASS) "$(INTDIR)"


!ENDIF 

# End Source File
# End Target
# End Project
################################################################################
