# Microsoft Developer Studio Generated NMAKE File, Format Version 4.10
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Dynamic-Link Library" 0x0102

!IF "$(CFG)" == ""
CFG=Circle - Win32 Debug
!MESSAGE No configuration specified.  Defaulting to Circle - Win32 Debug.
!ENDIF 

!IF "$(CFG)" != "Circle - Win32 Release" && "$(CFG)" != "Circle - Win32 Debug"
!MESSAGE Invalid configuration "$(CFG)" specified.
!MESSAGE You can specify a configuration when running NMAKE on this makefile
!MESSAGE by defining the macro CFG on the command line.  For example:
!MESSAGE 
!MESSAGE NMAKE /f "Circle.mak" CFG="Circle - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "Circle - Win32 Release" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE "Circle - Win32 Debug" (based on "Win32 (x86) Dynamic-Link Library")
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
# PROP Target_Last_Scanned "Circle - Win32 Debug"
CPP=cl.exe
RSC=rc.exe
MTL=mktyplib.exe

!IF  "$(CFG)" == "Circle - Win32 Release"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "Circle__"
# PROP BASE Intermediate_Dir "Circle__"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "RELEASE"
# PROP Intermediate_Dir "RELEASE"
# PROP Target_Dir ""
OUTDIR=.\RELEASE
INTDIR=.\RELEASE

ALL : ".\RELEASE\Circle.dll"

CLEAN : 
	-@erase ".\RELEASE\CIRCDISP.OBJ"
	-@erase ".\RELEASE\CIRCLCTL.OBJ"
	-@erase ".\RELEASE\Circle.dll"
	-@erase ".\RELEASE\Circle.exp"
	-@erase ".\RELEASE\Circle.lib"
	-@erase ".\RELEASE\CIRCLE.OBJ"
	-@erase ".\RELEASE\CIRCLECO.OBJ"
	-@erase ".\RELEASE\CIRCLECO.res"
	-@erase ".\RELEASE\CIRCSEL.OBJ"
	-@erase ".\RELEASE\CIRCTI.OBJ"
	-@erase ".\RELEASE\GUIDS.OBJ"
	-@erase ".\RELEASE\MISC.OBJ"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

# ADD BASE CPP /nologo /MT /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /YX /c
# ADD CPP /nologo /MT /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /YX /TP /c
CPP_PROJ=/nologo /MT /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS"\
 /Fp"$(INTDIR)/Circle.pch" /YX /Fo"$(INTDIR)/" /TP /c 
CPP_OBJS=.\RELEASE/
CPP_SBRS=.\.
# ADD BASE MTL /nologo /D "NDEBUG" /win32
# ADD MTL /nologo /D "NDEBUG" /win32
MTL_PROJ=/nologo /D "NDEBUG" /win32 
# ADD BASE RSC /l 0x409 /d "NDEBUG"
# ADD RSC /l 0x409 /d "NDEBUG"
RSC_PROJ=/l 0x409 /fo"$(INTDIR)/CIRCLECO.res" /d "NDEBUG" 
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
BSC32_FLAGS=/nologo /o"$(OUTDIR)/Circle.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /dll /machine:I386
# ADD LINK32 AXFWr.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib ocx96.lib uuid2.lib /nologo /subsystem:windows /dll /machine:I386 /nodefaultlib:"LIBCD.LIB"
# SUBTRACT LINK32 /nodefaultlib
LINK32_FLAGS=AXFWr.lib kernel32.lib user32.lib gdi32.lib winspool.lib\
 comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib\
 odbc32.lib odbccp32.lib ocx96.lib uuid2.lib /nologo /subsystem:windows /dll\
 /incremental:no /pdb:"$(OUTDIR)/Circle.pdb" /machine:I386\
 /nodefaultlib:"LIBCD.LIB" /def:".\CIRCLECO.DEF" /out:"$(OUTDIR)/Circle.dll"\
 /implib:"$(OUTDIR)/Circle.lib" 
DEF_FILE= \
	".\CIRCLECO.DEF"
LINK32_OBJS= \
	".\RELEASE\CIRCDISP.OBJ" \
	".\RELEASE\CIRCLCTL.OBJ" \
	".\RELEASE\CIRCLE.OBJ" \
	".\RELEASE\CIRCLECO.OBJ" \
	".\RELEASE\CIRCLECO.res" \
	".\RELEASE\CIRCSEL.OBJ" \
	".\RELEASE\CIRCTI.OBJ" \
	".\RELEASE\GUIDS.OBJ" \
	".\RELEASE\MISC.OBJ"

".\RELEASE\Circle.dll" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ELSEIF  "$(CFG)" == "Circle - Win32 Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "Circle_0"
# PROP BASE Intermediate_Dir "Circle_0"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "DEBUG"
# PROP Intermediate_Dir "DEBUG"
# PROP Target_Dir ""
OUTDIR=.\DEBUG
INTDIR=.\DEBUG

ALL : ".\DEBUG\Circle.dll" ".\DEBUG\Circle.bsc"

CLEAN : 
	-@erase ".\DEBUG\CIRCDISP.OBJ"
	-@erase ".\DEBUG\CIRCDISP.SBR"
	-@erase ".\DEBUG\CIRCLCTL.OBJ"
	-@erase ".\DEBUG\CIRCLCTL.SBR"
	-@erase ".\DEBUG\Circle.bsc"
	-@erase ".\DEBUG\Circle.dll"
	-@erase ".\DEBUG\Circle.exp"
	-@erase ".\DEBUG\Circle.ilk"
	-@erase ".\DEBUG\Circle.lib"
	-@erase ".\DEBUG\CIRCLE.OBJ"
	-@erase ".\DEBUG\Circle.pdb"
	-@erase ".\DEBUG\CIRCLE.SBR"
	-@erase ".\DEBUG\CIRCLECO.OBJ"
	-@erase ".\DEBUG\CIRCLECO.res"
	-@erase ".\DEBUG\CIRCLECO.SBR"
	-@erase ".\DEBUG\CIRCSEL.OBJ"
	-@erase ".\DEBUG\CIRCSEL.SBR"
	-@erase ".\DEBUG\CIRCTI.OBJ"
	-@erase ".\DEBUG\CIRCTI.SBR"
	-@erase ".\DEBUG\GUIDS.OBJ"
	-@erase ".\DEBUG\GUIDS.SBR"
	-@erase ".\DEBUG\MISC.OBJ"
	-@erase ".\DEBUG\MISC.SBR"
	-@erase ".\DEBUG\vc40.idb"
	-@erase ".\DEBUG\vc40.pdb"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

# ADD BASE CPP /nologo /MTd /W3 /Gm /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /YX /c
# ADD CPP /nologo /MTd /W3 /Gm /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /FR /YX /TP /c
CPP_PROJ=/nologo /MTd /W3 /Gm /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS"\
 /FR"$(INTDIR)/" /Fp"$(INTDIR)/Circle.pch" /YX /Fo"$(INTDIR)/" /Fd"$(INTDIR)/"\
 /TP /c 
CPP_OBJS=.\DEBUG/
CPP_SBRS=.\DEBUG/
# ADD BASE MTL /nologo /D "_DEBUG" /win32
# ADD MTL /nologo /D "_DEBUG" /win32
MTL_PROJ=/nologo /D "_DEBUG" /win32 
# ADD BASE RSC /l 0x409 /d "_DEBUG"
# ADD RSC /l 0x409 /d "_DEBUG"
RSC_PROJ=/l 0x409 /fo"$(INTDIR)/CIRCLECO.res" /d "_DEBUG" 
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
BSC32_FLAGS=/nologo /o"$(OUTDIR)/Circle.bsc" 
BSC32_SBRS= \
	".\DEBUG\CIRCDISP.SBR" \
	".\DEBUG\CIRCLCTL.SBR" \
	".\DEBUG\CIRCLE.SBR" \
	".\DEBUG\CIRCLECO.SBR" \
	".\DEBUG\CIRCSEL.SBR" \
	".\DEBUG\CIRCTI.SBR" \
	".\DEBUG\GUIDS.SBR" \
	".\DEBUG\MISC.SBR"

".\DEBUG\Circle.bsc" : "$(OUTDIR)" $(BSC32_SBRS)
    $(BSC32) @<<
  $(BSC32_FLAGS) $(BSC32_SBRS)
<<

LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /dll /debug /machine:I386
# ADD LINK32 AXFWd.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib ocx96.lib uuid2.lib /nologo /subsystem:windows /dll /debug /machine:I386 /nodefaultlib:"LIBCD.LIB"
# SUBTRACT LINK32 /nodefaultlib
LINK32_FLAGS=AXFWd.lib kernel32.lib user32.lib gdi32.lib winspool.lib\
 comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib\
 odbc32.lib odbccp32.lib ocx96.lib uuid2.lib /nologo /subsystem:windows /dll\
 /incremental:yes /pdb:"$(OUTDIR)/Circle.pdb" /debug /machine:I386\
 /nodefaultlib:"LIBCD.LIB" /def:".\CIRCLECO.DEF" /out:"$(OUTDIR)/Circle.dll"\
 /implib:"$(OUTDIR)/Circle.lib" 
DEF_FILE= \
	".\CIRCLECO.DEF"
LINK32_OBJS= \
	".\DEBUG\CIRCDISP.OBJ" \
	".\DEBUG\CIRCLCTL.OBJ" \
	".\DEBUG\CIRCLE.OBJ" \
	".\DEBUG\CIRCLECO.OBJ" \
	".\DEBUG\CIRCLECO.res" \
	".\DEBUG\CIRCSEL.OBJ" \
	".\DEBUG\CIRCTI.OBJ" \
	".\DEBUG\GUIDS.OBJ" \
	".\DEBUG\MISC.OBJ"

".\DEBUG\Circle.dll" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
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

# Name "Circle - Win32 Release"
# Name "Circle - Win32 Debug"

!IF  "$(CFG)" == "Circle - Win32 Release"

!ELSEIF  "$(CFG)" == "Circle - Win32 Debug"

!ENDIF 

################################################################################
# Begin Source File

SOURCE=.\CIRCLCTL.CPP
DEP_CPP_CIRCL=\
	"..\..\MSDEV\INCLUDE\Debug.H"\
	"..\..\MSDEV\INCLUDE\Unknown.H"\
	".\CIRCLCTL.H"\
	".\CircleCoInterfaces.H"\
	".\DISPIDS.H"\
	".\GUIDS.H"\
	".\LOCALOBJ.H"\
	".\MISC.H"\
	".\RESOURCE.H"\
	{$(INCLUDE)}"\AutoObj.H"\
	{$(INCLUDE)}"\CtrlObj.H"\
	{$(INCLUDE)}"\Designer.H"\
	{$(INCLUDE)}"\Globals.H"\
	{$(INCLUDE)}"\IPServer.H"\
	{$(INCLUDE)}"\LocalSrv.H"\
	{$(INCLUDE)}"\Util.H"\
	

!IF  "$(CFG)" == "Circle - Win32 Release"


".\RELEASE\CIRCLCTL.OBJ" : $(SOURCE) $(DEP_CPP_CIRCL) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "Circle - Win32 Debug"


".\DEBUG\CIRCLCTL.OBJ" : $(SOURCE) $(DEP_CPP_CIRCL) "$(INTDIR)"

".\DEBUG\CIRCLCTL.SBR" : $(SOURCE) $(DEP_CPP_CIRCL) "$(INTDIR)"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\CIRCLE.CPP
DEP_CPP_CIRCLE=\
	"..\..\MSDEV\INCLUDE\Debug.H"\
	"..\..\MSDEV\INCLUDE\Unknown.H"\
	".\CIRCLE.H"\
	".\CircleCoInterfaces.H"\
	".\DISPIDS.H"\
	".\GUIDS.H"\
	".\LOCALOBJ.H"\
	".\RESOURCE.H"\
	{$(INCLUDE)}"\AutoObj.H"\
	{$(INCLUDE)}"\Globals.H"\
	{$(INCLUDE)}"\IPServer.H"\
	{$(INCLUDE)}"\LocalSrv.H"\
	{$(INCLUDE)}"\Util.H"\
	

!IF  "$(CFG)" == "Circle - Win32 Release"


".\RELEASE\CIRCLE.OBJ" : $(SOURCE) $(DEP_CPP_CIRCLE) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "Circle - Win32 Debug"


".\DEBUG\CIRCLE.OBJ" : $(SOURCE) $(DEP_CPP_CIRCLE) "$(INTDIR)"

".\DEBUG\CIRCLE.SBR" : $(SOURCE) $(DEP_CPP_CIRCLE) "$(INTDIR)"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\CIRCLECO.CPP
DEP_CPP_CIRCLEC=\
	"..\..\MSDEV\INCLUDE\Debug.H"\
	"..\..\MSDEV\INCLUDE\Unknown.H"\
	".\CIRCLCTL.H"\
	".\CIRCLE.H"\
	".\CircleCoInterfaces.H"\
	".\DISPIDS.H"\
	".\LOCALOBJ.H"\
	".\RESOURCE.H"\
	{$(INCLUDE)}"\AutoObj.H"\
	{$(INCLUDE)}"\CtrlObj.H"\
	{$(INCLUDE)}"\Designer.H"\
	{$(INCLUDE)}"\Globals.H"\
	{$(INCLUDE)}"\IPServer.H"\
	{$(INCLUDE)}"\LocalSrv.H"\
	{$(INCLUDE)}"\Util.H"\
	

!IF  "$(CFG)" == "Circle - Win32 Release"


".\RELEASE\CIRCLECO.OBJ" : $(SOURCE) $(DEP_CPP_CIRCLEC) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "Circle - Win32 Debug"


".\DEBUG\CIRCLECO.OBJ" : $(SOURCE) $(DEP_CPP_CIRCLEC) "$(INTDIR)"

".\DEBUG\CIRCLECO.SBR" : $(SOURCE) $(DEP_CPP_CIRCLEC) "$(INTDIR)"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\CIRCLECO.RC
DEP_RSC_CIRCLECO=\
	".\CIRCLCTL.BMP"\
	".\CircleCo.TLB"\
	".\RESOURCE.H"\
	{$(INCLUDE)}"\DWINVERS.H"\
	

!IF  "$(CFG)" == "Circle - Win32 Release"


".\RELEASE\CIRCLECO.res" : $(SOURCE) $(DEP_RSC_CIRCLECO) "$(INTDIR)"
   $(RSC) $(RSC_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "Circle - Win32 Debug"


".\DEBUG\CIRCLECO.res" : $(SOURCE) $(DEP_RSC_CIRCLECO) "$(INTDIR)"
   $(RSC) $(RSC_PROJ) $(SOURCE)


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\CIRCSEL.CPP
DEP_CPP_CIRCS=\
	"..\..\MSDEV\INCLUDE\Debug.H"\
	"..\..\MSDEV\INCLUDE\Unknown.H"\
	".\CIRCLCTL.H"\
	".\CircleCoInterfaces.H"\
	".\DISPIDS.H"\
	".\GUIDS.H"\
	".\LOCALOBJ.H"\
	".\MISC.H"\
	".\RESOURCE.H"\
	{$(INCLUDE)}"\AutoObj.H"\
	{$(INCLUDE)}"\CtrlObj.H"\
	{$(INCLUDE)}"\Designer.H"\
	{$(INCLUDE)}"\Globals.H"\
	{$(INCLUDE)}"\IPServer.H"\
	{$(INCLUDE)}"\LocalSrv.H"\
	{$(INCLUDE)}"\Util.H"\
	

!IF  "$(CFG)" == "Circle - Win32 Release"


".\RELEASE\CIRCSEL.OBJ" : $(SOURCE) $(DEP_CPP_CIRCS) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "Circle - Win32 Debug"


".\DEBUG\CIRCSEL.OBJ" : $(SOURCE) $(DEP_CPP_CIRCS) "$(INTDIR)"

".\DEBUG\CIRCSEL.SBR" : $(SOURCE) $(DEP_CPP_CIRCS) "$(INTDIR)"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\CIRCTI.CPP
DEP_CPP_CIRCT=\
	"..\..\MSDEV\INCLUDE\Debug.H"\
	"..\..\MSDEV\INCLUDE\Unknown.H"\
	".\CIRCLCTL.H"\
	".\CircleCoInterfaces.H"\
	".\DISPIDS.H"\
	".\MISC.H"\
	".\RESOURCE.H"\
	{$(INCLUDE)}"\AutoObj.H"\
	{$(INCLUDE)}"\CtrlObj.H"\
	{$(INCLUDE)}"\Designer.H"\
	{$(INCLUDE)}"\Globals.H"\
	{$(INCLUDE)}"\IPServer.H"\
	{$(INCLUDE)}"\LocalSrv.H"\
	{$(INCLUDE)}"\Util.H"\
	

!IF  "$(CFG)" == "Circle - Win32 Release"


".\RELEASE\CIRCTI.OBJ" : $(SOURCE) $(DEP_CPP_CIRCT) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "Circle - Win32 Debug"


".\DEBUG\CIRCTI.OBJ" : $(SOURCE) $(DEP_CPP_CIRCT) "$(INTDIR)"

".\DEBUG\CIRCTI.SBR" : $(SOURCE) $(DEP_CPP_CIRCT) "$(INTDIR)"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\GUIDS.CPP
DEP_CPP_GUIDS=\
	"..\..\MSDEV\INCLUDE\Debug.H"\
	".\CircleCoInterfaces.H"\
	".\GUIDS.H"\
	{$(INCLUDE)}"\Designer.H"\
	{$(INCLUDE)}"\IPServer.H"\
	

!IF  "$(CFG)" == "Circle - Win32 Release"


".\RELEASE\GUIDS.OBJ" : $(SOURCE) $(DEP_CPP_GUIDS) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "Circle - Win32 Debug"


".\DEBUG\GUIDS.OBJ" : $(SOURCE) $(DEP_CPP_GUIDS) "$(INTDIR)"

".\DEBUG\GUIDS.SBR" : $(SOURCE) $(DEP_CPP_GUIDS) "$(INTDIR)"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\MISC.CPP
DEP_CPP_MISC_=\
	"..\..\MSDEV\INCLUDE\Debug.H"\
	"..\..\MSDEV\INCLUDE\Unknown.H"\
	".\CIRCLCTL.H"\
	".\CircleCoInterfaces.H"\
	".\DISPIDS.H"\
	".\MISC.H"\
	".\RESOURCE.H"\
	{$(INCLUDE)}"\AutoObj.H"\
	{$(INCLUDE)}"\CtrlObj.H"\
	{$(INCLUDE)}"\Designer.H"\
	{$(INCLUDE)}"\Globals.H"\
	{$(INCLUDE)}"\IPServer.H"\
	{$(INCLUDE)}"\LocalSrv.H"\
	{$(INCLUDE)}"\Util.H"\
	

!IF  "$(CFG)" == "Circle - Win32 Release"


".\RELEASE\MISC.OBJ" : $(SOURCE) $(DEP_CPP_MISC_) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "Circle - Win32 Debug"


".\DEBUG\MISC.OBJ" : $(SOURCE) $(DEP_CPP_MISC_) "$(INTDIR)"

".\DEBUG\MISC.SBR" : $(SOURCE) $(DEP_CPP_MISC_) "$(INTDIR)"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\CIRCDISP.CPP
DEP_CPP_CIRCD=\
	"..\..\MSDEV\INCLUDE\Debug.H"\
	"..\..\MSDEV\INCLUDE\Unknown.H"\
	".\CIRCLCTL.H"\
	".\CircleCoInterfaces.H"\
	".\DISPIDS.H"\
	".\GUIDS.H"\
	".\LOCALOBJ.H"\
	".\MISC.H"\
	".\RESOURCE.H"\
	{$(INCLUDE)}"\AutoObj.H"\
	{$(INCLUDE)}"\CtrlObj.H"\
	{$(INCLUDE)}"\Designer.H"\
	{$(INCLUDE)}"\Globals.H"\
	{$(INCLUDE)}"\IPServer.H"\
	{$(INCLUDE)}"\LocalSrv.H"\
	{$(INCLUDE)}"\Util.H"\
	

!IF  "$(CFG)" == "Circle - Win32 Release"


".\RELEASE\CIRCDISP.OBJ" : $(SOURCE) $(DEP_CPP_CIRCD) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "Circle - Win32 Debug"


".\DEBUG\CIRCDISP.OBJ" : $(SOURCE) $(DEP_CPP_CIRCD) "$(INTDIR)"

".\DEBUG\CIRCDISP.SBR" : $(SOURCE) $(DEP_CPP_CIRCD) "$(INTDIR)"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\CIRCLECO.DEF

!IF  "$(CFG)" == "Circle - Win32 Release"

!ELSEIF  "$(CFG)" == "Circle - Win32 Debug"

!ENDIF 

# End Source File
# End Target
# End Project
################################################################################
