# Microsoft Developer Studio Generated NMAKE File, Format Version 4.10
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Dynamic-Link Library" 0x0102

!IF "$(CFG)" == ""
CFG=DiffDsgn - Win32 Debug
!MESSAGE No configuration specified.  Defaulting to DiffDsgn - Win32 Debug.
!ENDIF 

!IF "$(CFG)" != "DiffDsgn - Win32 Release" && "$(CFG)" !=\
 "DiffDsgn - Win32 Debug"
!MESSAGE Invalid configuration "$(CFG)" specified.
!MESSAGE You can specify a configuration when running NMAKE on this makefile
!MESSAGE by defining the macro CFG on the command line.  For example:
!MESSAGE 
!MESSAGE NMAKE /f "DiffDsgn.mak" CFG="DiffDsgn - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "DiffDsgn - Win32 Release" (based on\
 "Win32 (x86) Dynamic-Link Library")
!MESSAGE "DiffDsgn - Win32 Debug" (based on "Win32 (x86) Dynamic-Link Library")
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
# PROP Target_Last_Scanned "DiffDsgn - Win32 Debug"
CPP=cl.exe
RSC=rc.exe
MTL=mktyplib.exe

!IF  "$(CFG)" == "DiffDsgn - Win32 Release"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "DiffDsgn"
# PROP BASE Intermediate_Dir "DiffDsgn"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "RELEASE"
# PROP Intermediate_Dir "RELEASE"
# PROP Target_Dir ""
OUTDIR=.\RELEASE
INTDIR=.\RELEASE

ALL : ".\RELEASE\DiffDsgn.dll"

CLEAN : 
	-@erase ".\RELEASE\DIFFDCTL.OBJ"
	-@erase ".\RELEASE\DIFFDPPG.OBJ"
	-@erase ".\RELEASE\DiffDsgn.dll"
	-@erase ".\RELEASE\DiffDsgn.exp"
	-@erase ".\RELEASE\DiffDsgn.lib"
	-@erase ".\RELEASE\DIFFDSGR.OBJ"
	-@erase ".\RELEASE\DIFFDSGR.res"
	-@erase ".\RELEASE\GUIDS.OBJ"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

# ADD BASE CPP /nologo /MT /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /YX /c
# ADD CPP /nologo /MT /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /YX /c
CPP_PROJ=/nologo /MT /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS"\
 /Fp"$(INTDIR)/DiffDsgn.pch" /YX /Fo"$(INTDIR)/" /c 
CPP_OBJS=.\RELEASE/
CPP_SBRS=.\.
# ADD BASE MTL /nologo /D "NDEBUG" /win32
# ADD MTL /nologo /D "NDEBUG" /win32
MTL_PROJ=/nologo /D "NDEBUG" /win32 
# ADD BASE RSC /l 0x409 /d "NDEBUG"
# ADD RSC /l 0x409 /d "NDEBUG"
RSC_PROJ=/l 0x409 /fo"$(INTDIR)/DIFFDSGR.res" /d "NDEBUG" 
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
BSC32_FLAGS=/nologo /o"$(OUTDIR)/DiffDsgn.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /dll /machine:I386
# ADD LINK32 AXFWr.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib ocx96.lib uuid2.lib /nologo /subsystem:windows /dll /machine:I386
LINK32_FLAGS=AXFWr.lib kernel32.lib user32.lib gdi32.lib winspool.lib\
 comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib\
 odbc32.lib odbccp32.lib ocx96.lib uuid2.lib /nologo /subsystem:windows /dll\
 /incremental:no /pdb:"$(OUTDIR)/DiffDsgn.pdb" /machine:I386\
 /def:".\DIFFDSGR.DEF" /out:"$(OUTDIR)/DiffDsgn.dll"\
 /implib:"$(OUTDIR)/DiffDsgn.lib" 
DEF_FILE= \
	".\DIFFDSGR.DEF"
LINK32_OBJS= \
	".\RELEASE\DIFFDCTL.OBJ" \
	".\RELEASE\DIFFDPPG.OBJ" \
	".\RELEASE\DIFFDSGR.OBJ" \
	".\RELEASE\DIFFDSGR.res" \
	".\RELEASE\GUIDS.OBJ"

".\RELEASE\DiffDsgn.dll" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ELSEIF  "$(CFG)" == "DiffDsgn - Win32 Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "DiffDsg0"
# PROP BASE Intermediate_Dir "DiffDsg0"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "DEBUG"
# PROP Intermediate_Dir "DEBUG"
# PROP Target_Dir ""
OUTDIR=.\DEBUG
INTDIR=.\DEBUG

ALL : ".\DEBUG\DiffDsgn.dll" ".\DEBUG\DiffDsgn.bsc"

CLEAN : 
	-@erase ".\DEBUG\DIFFDCTL.OBJ"
	-@erase ".\DEBUG\DIFFDCTL.SBR"
	-@erase ".\DEBUG\DIFFDPPG.OBJ"
	-@erase ".\DEBUG\DIFFDPPG.SBR"
	-@erase ".\DEBUG\DiffDsgn.bsc"
	-@erase ".\DEBUG\DiffDsgn.dll"
	-@erase ".\DEBUG\DiffDsgn.exp"
	-@erase ".\DEBUG\DiffDsgn.ilk"
	-@erase ".\DEBUG\DiffDsgn.lib"
	-@erase ".\DEBUG\DiffDsgn.pdb"
	-@erase ".\DEBUG\DIFFDSGR.OBJ"
	-@erase ".\DEBUG\DIFFDSGR.res"
	-@erase ".\DEBUG\DIFFDSGR.SBR"
	-@erase ".\DEBUG\GUIDS.OBJ"
	-@erase ".\DEBUG\GUIDS.SBR"
	-@erase ".\DEBUG\vc40.idb"
	-@erase ".\DEBUG\vc40.pdb"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

# ADD BASE CPP /nologo /MTd /W3 /Gm /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /YX /c
# ADD CPP /nologo /MTd /W3 /Gm /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /FR /YX /c
CPP_PROJ=/nologo /MTd /W3 /Gm /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS"\
 /FR"$(INTDIR)/" /Fp"$(INTDIR)/DiffDsgn.pch" /YX /Fo"$(INTDIR)/" /Fd"$(INTDIR)/"\
 /c 
CPP_OBJS=.\DEBUG/
CPP_SBRS=.\DEBUG/
# ADD BASE MTL /nologo /D "_DEBUG" /win32
# ADD MTL /nologo /D "_DEBUG" /win32
MTL_PROJ=/nologo /D "_DEBUG" /win32 
# ADD BASE RSC /l 0x409 /d "_DEBUG"
# ADD RSC /l 0x409 /d "_DEBUG"
RSC_PROJ=/l 0x409 /fo"$(INTDIR)/DIFFDSGR.res" /d "_DEBUG" 
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
BSC32_FLAGS=/nologo /o"$(OUTDIR)/DiffDsgn.bsc" 
BSC32_SBRS= \
	".\DEBUG\DIFFDCTL.SBR" \
	".\DEBUG\DIFFDPPG.SBR" \
	".\DEBUG\DIFFDSGR.SBR" \
	".\DEBUG\GUIDS.SBR"

".\DEBUG\DiffDsgn.bsc" : "$(OUTDIR)" $(BSC32_SBRS)
    $(BSC32) @<<
  $(BSC32_FLAGS) $(BSC32_SBRS)
<<

LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /dll /debug /machine:I386
# ADD LINK32 AXFWd.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib ocx96.lib uuid2.lib /nologo /subsystem:windows /dll /debug /machine:I386
LINK32_FLAGS=AXFWd.lib kernel32.lib user32.lib gdi32.lib winspool.lib\
 comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib\
 odbc32.lib odbccp32.lib ocx96.lib uuid2.lib /nologo /subsystem:windows /dll\
 /incremental:yes /pdb:"$(OUTDIR)/DiffDsgn.pdb" /debug /machine:I386\
 /def:".\DIFFDSGR.DEF" /out:"$(OUTDIR)/DiffDsgn.dll"\
 /implib:"$(OUTDIR)/DiffDsgn.lib" 
DEF_FILE= \
	".\DIFFDSGR.DEF"
LINK32_OBJS= \
	".\DEBUG\DIFFDCTL.OBJ" \
	".\DEBUG\DIFFDPPG.OBJ" \
	".\DEBUG\DIFFDSGR.OBJ" \
	".\DEBUG\DIFFDSGR.res" \
	".\DEBUG\GUIDS.OBJ"

".\DEBUG\DiffDsgn.dll" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
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

# Name "DiffDsgn - Win32 Release"
# Name "DiffDsgn - Win32 Debug"

!IF  "$(CFG)" == "DiffDsgn - Win32 Release"

!ELSEIF  "$(CFG)" == "DiffDsgn - Win32 Debug"

!ENDIF 

################################################################################
# Begin Source File

SOURCE=.\GUIDS.CPP
DEP_CPP_GUIDS=\
	".\DiffDsgrInterfaces.H"\
	".\Guids.H"\
	".\IPServer.H"\
	{$(INCLUDE)}"\Debug.H"\
	{$(INCLUDE)}"\Designer.H"\
	

!IF  "$(CFG)" == "DiffDsgn - Win32 Release"


".\RELEASE\GUIDS.OBJ" : $(SOURCE) $(DEP_CPP_GUIDS) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "DiffDsgn - Win32 Debug"


".\DEBUG\GUIDS.OBJ" : $(SOURCE) $(DEP_CPP_GUIDS) "$(INTDIR)"

".\DEBUG\GUIDS.SBR" : $(SOURCE) $(DEP_CPP_GUIDS) "$(INTDIR)"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\DIFFDPPG.CPP
DEP_CPP_DIFFD=\
	"..\..\MSDEV\INCLUDE\AutoObj.H"\
	"..\..\MSDEV\INCLUDE\Unknown.H"\
	".\DiffDCtl.H"\
	".\DiffDPPG.H"\
	".\DiffDsgrInterfaces.H"\
	".\Dispids.H"\
	".\Guids.H"\
	".\IPServer.H"\
	".\LocalObj.H"\
	".\Resource.H"\
	{$(INCLUDE)}"\CtrlObj.H"\
	{$(INCLUDE)}"\Debug.H"\
	{$(INCLUDE)}"\Designer.H"\
	{$(INCLUDE)}"\Globals.H"\
	{$(INCLUDE)}"\LocalSrv.H"\
	{$(INCLUDE)}"\PropPage.H"\
	{$(INCLUDE)}"\Util.H"\
	

!IF  "$(CFG)" == "DiffDsgn - Win32 Release"


".\RELEASE\DIFFDPPG.OBJ" : $(SOURCE) $(DEP_CPP_DIFFD) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "DiffDsgn - Win32 Debug"


".\DEBUG\DIFFDPPG.OBJ" : $(SOURCE) $(DEP_CPP_DIFFD) "$(INTDIR)"

".\DEBUG\DIFFDPPG.SBR" : $(SOURCE) $(DEP_CPP_DIFFD) "$(INTDIR)"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\DIFFDSGR.CPP
DEP_CPP_DIFFDS=\
	"..\..\MSDEV\INCLUDE\AutoObj.H"\
	"..\..\MSDEV\INCLUDE\Unknown.H"\
	".\DiffDCtl.H"\
	".\DiffDPPG.H"\
	".\DiffDsgrInterfaces.H"\
	".\Dispids.H"\
	".\Guids.H"\
	".\IPServer.H"\
	".\LocalObj.H"\
	".\Resource.H"\
	{$(INCLUDE)}"\CtrlObj.H"\
	{$(INCLUDE)}"\Debug.H"\
	{$(INCLUDE)}"\Designer.H"\
	{$(INCLUDE)}"\Globals.H"\
	{$(INCLUDE)}"\LocalSrv.H"\
	{$(INCLUDE)}"\PropPage.H"\
	{$(INCLUDE)}"\Util.H"\
	

!IF  "$(CFG)" == "DiffDsgn - Win32 Release"


".\RELEASE\DIFFDSGR.OBJ" : $(SOURCE) $(DEP_CPP_DIFFDS) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "DiffDsgn - Win32 Debug"


".\DEBUG\DIFFDSGR.OBJ" : $(SOURCE) $(DEP_CPP_DIFFDS) "$(INTDIR)"

".\DEBUG\DIFFDSGR.SBR" : $(SOURCE) $(DEP_CPP_DIFFDS) "$(INTDIR)"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\DIFFDCTL.CPP
DEP_CPP_DIFFDC=\
	"..\..\MSDEV\INCLUDE\AutoObj.H"\
	"..\..\MSDEV\INCLUDE\Unknown.H"\
	".\DiffDCtl.H"\
	".\DiffDsgrInterfaces.H"\
	".\Dispids.H"\
	".\Guids.H"\
	".\IPServer.H"\
	".\LocalObj.H"\
	".\Resource.H"\
	{$(INCLUDE)}"\CtrlObj.H"\
	{$(INCLUDE)}"\Debug.H"\
	{$(INCLUDE)}"\Designer.H"\
	{$(INCLUDE)}"\Globals.H"\
	{$(INCLUDE)}"\LocalSrv.H"\
	{$(INCLUDE)}"\Util.H"\
	

!IF  "$(CFG)" == "DiffDsgn - Win32 Release"


".\RELEASE\DIFFDCTL.OBJ" : $(SOURCE) $(DEP_CPP_DIFFDC) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "DiffDsgn - Win32 Debug"


".\DEBUG\DIFFDCTL.OBJ" : $(SOURCE) $(DEP_CPP_DIFFDC) "$(INTDIR)"

".\DEBUG\DIFFDCTL.SBR" : $(SOURCE) $(DEP_CPP_DIFFDC) "$(INTDIR)"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\DIFFDSGR.DEF

!IF  "$(CFG)" == "DiffDsgn - Win32 Release"

!ELSEIF  "$(CFG)" == "DiffDsgn - Win32 Debug"

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\DIFFDSGR.RC
DEP_RSC_DIFFDSG=\
	".\DiffDCtl.Bmp"\
	".\DiffDsgr.TLB"\
	".\Resource.H"\
	{$(INCLUDE)}"\dwinvers.h"\
	

!IF  "$(CFG)" == "DiffDsgn - Win32 Release"


".\RELEASE\DIFFDSGR.res" : $(SOURCE) $(DEP_RSC_DIFFDSG) "$(INTDIR)"
   $(RSC) $(RSC_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "DiffDsgn - Win32 Debug"


".\DEBUG\DIFFDSGR.res" : $(SOURCE) $(DEP_RSC_DIFFDSG) "$(INTDIR)"
   $(RSC) $(RSC_PROJ) $(SOURCE)


!ENDIF 

# End Source File
# End Target
# End Project
################################################################################
