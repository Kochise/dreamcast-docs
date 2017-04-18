# Microsoft Developer Studio Generated NMAKE File, Format Version 4.10
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Dynamic-Link Library" 0x0102

!IF "$(CFG)" == ""
CFG=DiffInst - Win32 Debug
!MESSAGE No configuration specified.  Defaulting to DiffInst - Win32 Debug.
!ENDIF 

!IF "$(CFG)" != "DiffInst - Win32 Release" && "$(CFG)" !=\
 "DiffInst - Win32 Debug"
!MESSAGE Invalid configuration "$(CFG)" specified.
!MESSAGE You can specify a configuration when running NMAKE on this makefile
!MESSAGE by defining the macro CFG on the command line.  For example:
!MESSAGE 
!MESSAGE NMAKE /f "DiffInst.mak" CFG="DiffInst - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "DiffInst - Win32 Release" (based on\
 "Win32 (x86) Dynamic-Link Library")
!MESSAGE "DiffInst - Win32 Debug" (based on "Win32 (x86) Dynamic-Link Library")
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
# PROP Target_Last_Scanned "DiffInst - Win32 Debug"
CPP=cl.exe
RSC=rc.exe
MTL=mktyplib.exe

!IF  "$(CFG)" == "DiffInst - Win32 Release"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "DiffInst"
# PROP BASE Intermediate_Dir "DiffInst"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "RELEASE"
# PROP Intermediate_Dir "RELEASE"
# PROP Target_Dir ""
OUTDIR=.\RELEASE
INTDIR=.\RELEASE

ALL : ".\RELEASE\DiffInst.dll"

CLEAN : 
	-@erase ".\RELEASE\DIFFICTL.OBJ"
	-@erase ".\RELEASE\DiffInst.dll"
	-@erase ".\RELEASE\DiffInst.exp"
	-@erase ".\RELEASE\DiffInst.lib"
	-@erase ".\RELEASE\DIFFINST.OBJ"
	-@erase ".\RELEASE\DIFFINST.res"
	-@erase ".\RELEASE\DIFFIPPG.OBJ"
	-@erase ".\RELEASE\GUIDS.OBJ"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

# ADD BASE CPP /nologo /MT /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /YX /c
# ADD CPP /nologo /MT /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /YX /c
CPP_PROJ=/nologo /MT /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS"\
 /Fp"$(INTDIR)/DiffInst.pch" /YX /Fo"$(INTDIR)/" /c 
CPP_OBJS=.\RELEASE/
CPP_SBRS=.\.
# ADD BASE MTL /nologo /D "NDEBUG" /win32
# ADD MTL /nologo /D "NDEBUG" /win32
MTL_PROJ=/nologo /D "NDEBUG" /win32 
# ADD BASE RSC /l 0x409 /d "NDEBUG"
# ADD RSC /l 0x409 /d "NDEBUG"
RSC_PROJ=/l 0x409 /fo"$(INTDIR)/DIFFINST.res" /d "NDEBUG" 
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
BSC32_FLAGS=/nologo /o"$(OUTDIR)/DiffInst.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /dll /machine:I386
# ADD LINK32 AXFWr.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib ocx96.lib uuid2.lib /nologo /subsystem:windows /dll /machine:I386
LINK32_FLAGS=AXFWr.lib kernel32.lib user32.lib gdi32.lib winspool.lib\
 comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib\
 odbc32.lib odbccp32.lib ocx96.lib uuid2.lib /nologo /subsystem:windows /dll\
 /incremental:no /pdb:"$(OUTDIR)/DiffInst.pdb" /machine:I386\
 /def:".\DIFFINST.DEF" /out:"$(OUTDIR)/DiffInst.dll"\
 /implib:"$(OUTDIR)/DiffInst.lib" 
DEF_FILE= \
	".\DIFFINST.DEF"
LINK32_OBJS= \
	".\RELEASE\DIFFICTL.OBJ" \
	".\RELEASE\DIFFINST.OBJ" \
	".\RELEASE\DIFFINST.res" \
	".\RELEASE\DIFFIPPG.OBJ" \
	".\RELEASE\GUIDS.OBJ"

".\RELEASE\DiffInst.dll" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ELSEIF  "$(CFG)" == "DiffInst - Win32 Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "DiffIns0"
# PROP BASE Intermediate_Dir "DiffIns0"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "DEBUG"
# PROP Intermediate_Dir "DEBUG"
# PROP Target_Dir ""
OUTDIR=.\DEBUG
INTDIR=.\DEBUG

ALL : ".\DEBUG\DiffInst.dll"

CLEAN : 
	-@erase ".\DEBUG\DIFFICTL.OBJ"
	-@erase ".\DEBUG\DiffInst.dll"
	-@erase ".\DEBUG\DiffInst.exp"
	-@erase ".\DEBUG\DiffInst.ilk"
	-@erase ".\DEBUG\DiffInst.lib"
	-@erase ".\DEBUG\DIFFINST.OBJ"
	-@erase ".\DEBUG\DiffInst.pdb"
	-@erase ".\DEBUG\DIFFINST.res"
	-@erase ".\DEBUG\DIFFIPPG.OBJ"
	-@erase ".\DEBUG\GUIDS.OBJ"
	-@erase ".\DEBUG\vc40.idb"
	-@erase ".\DEBUG\vc40.pdb"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

# ADD BASE CPP /nologo /MTd /W3 /Gm /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /YX /c
# ADD CPP /nologo /MTd /W3 /Gm /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /YX /c
CPP_PROJ=/nologo /MTd /W3 /Gm /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS"\
 /Fp"$(INTDIR)/DiffInst.pch" /YX /Fo"$(INTDIR)/" /Fd"$(INTDIR)/" /c 
CPP_OBJS=.\DEBUG/
CPP_SBRS=.\.
# ADD BASE MTL /nologo /D "_DEBUG" /win32
# ADD MTL /nologo /D "_DEBUG" /win32
MTL_PROJ=/nologo /D "_DEBUG" /win32 
# ADD BASE RSC /l 0x409 /d "_DEBUG"
# ADD RSC /l 0x409 /d "_DEBUG"
RSC_PROJ=/l 0x409 /fo"$(INTDIR)/DIFFINST.res" /d "_DEBUG" 
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
BSC32_FLAGS=/nologo /o"$(OUTDIR)/DiffInst.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /dll /debug /machine:I386
# ADD LINK32 AXFWd.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib ocx96.lib uuid2.lib /nologo /subsystem:windows /dll /debug /machine:I386
LINK32_FLAGS=AXFWd.lib kernel32.lib user32.lib gdi32.lib winspool.lib\
 comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib\
 odbc32.lib odbccp32.lib ocx96.lib uuid2.lib /nologo /subsystem:windows /dll\
 /incremental:yes /pdb:"$(OUTDIR)/DiffInst.pdb" /debug /machine:I386\
 /def:".\DIFFINST.DEF" /out:"$(OUTDIR)/DiffInst.dll"\
 /implib:"$(OUTDIR)/DiffInst.lib" 
DEF_FILE= \
	".\DIFFINST.DEF"
LINK32_OBJS= \
	".\DEBUG\DIFFICTL.OBJ" \
	".\DEBUG\DIFFINST.OBJ" \
	".\DEBUG\DIFFINST.res" \
	".\DEBUG\DIFFIPPG.OBJ" \
	".\DEBUG\GUIDS.OBJ"

".\DEBUG\DiffInst.dll" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
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

# Name "DiffInst - Win32 Release"
# Name "DiffInst - Win32 Debug"

!IF  "$(CFG)" == "DiffInst - Win32 Release"

!ELSEIF  "$(CFG)" == "DiffInst - Win32 Debug"

!ENDIF 

################################################################################
# Begin Source File

SOURCE=.\DIFFICTL.CPP
DEP_CPP_DIFFI=\
	"..\..\MSDEV\INCLUDE\AutoObj.H"\
	"..\..\MSDEV\INCLUDE\Debug.H"\
	"..\..\MSDEV\INCLUDE\Unknown.H"\
	".\DiffICtl.H"\
	".\DiffInstInterfaces.H"\
	".\Dispids.H"\
	".\Guids.H"\
	".\LocalObj.H"\
	".\Resource.H"\
	{$(INCLUDE)}"\CtrlObj.H"\
	{$(INCLUDE)}"\Globals.H"\
	{$(INCLUDE)}"\IPServer.H"\
	{$(INCLUDE)}"\LocalSrv.H"\
	{$(INCLUDE)}"\Util.H"\
	

!IF  "$(CFG)" == "DiffInst - Win32 Release"


".\RELEASE\DIFFICTL.OBJ" : $(SOURCE) $(DEP_CPP_DIFFI) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "DiffInst - Win32 Debug"


".\DEBUG\DIFFICTL.OBJ" : $(SOURCE) $(DEP_CPP_DIFFI) "$(INTDIR)"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\GUIDS.CPP
DEP_CPP_GUIDS=\
	"..\..\MSDEV\INCLUDE\Debug.H"\
	".\DiffInstInterfaces.H"\
	".\Guids.H"\
	{$(INCLUDE)}"\IPServer.H"\
	

!IF  "$(CFG)" == "DiffInst - Win32 Release"


".\RELEASE\GUIDS.OBJ" : $(SOURCE) $(DEP_CPP_GUIDS) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "DiffInst - Win32 Debug"


".\DEBUG\GUIDS.OBJ" : $(SOURCE) $(DEP_CPP_GUIDS) "$(INTDIR)"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\DIFFIPPG.CPP
DEP_CPP_DIFFIP=\
	"..\..\MSDEV\INCLUDE\AutoObj.H"\
	"..\..\MSDEV\INCLUDE\Debug.H"\
	"..\..\MSDEV\INCLUDE\Unknown.H"\
	".\DiffICtl.H"\
	".\DiffInstInterfaces.H"\
	".\DiffIPPG.H"\
	".\Dispids.H"\
	".\Guids.H"\
	".\LocalObj.H"\
	".\Resource.H"\
	{$(INCLUDE)}"\CtrlObj.H"\
	{$(INCLUDE)}"\Globals.H"\
	{$(INCLUDE)}"\IPServer.H"\
	{$(INCLUDE)}"\LocalSrv.H"\
	{$(INCLUDE)}"\PropPage.H"\
	{$(INCLUDE)}"\Util.H"\
	

!IF  "$(CFG)" == "DiffInst - Win32 Release"


".\RELEASE\DIFFIPPG.OBJ" : $(SOURCE) $(DEP_CPP_DIFFIP) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "DiffInst - Win32 Debug"


".\DEBUG\DIFFIPPG.OBJ" : $(SOURCE) $(DEP_CPP_DIFFIP) "$(INTDIR)"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\DIFFINST.CPP
DEP_CPP_DIFFIN=\
	"..\..\MSDEV\INCLUDE\AutoObj.H"\
	"..\..\MSDEV\INCLUDE\Debug.H"\
	"..\..\MSDEV\INCLUDE\Unknown.H"\
	".\DiffICtl.H"\
	".\DiffInstInterfaces.H"\
	".\DiffIPPG.H"\
	".\Dispids.H"\
	".\Guids.H"\
	".\LocalObj.H"\
	".\Resource.H"\
	{$(INCLUDE)}"\CtrlObj.H"\
	{$(INCLUDE)}"\Globals.H"\
	{$(INCLUDE)}"\IPServer.H"\
	{$(INCLUDE)}"\LocalSrv.H"\
	{$(INCLUDE)}"\PropPage.H"\
	{$(INCLUDE)}"\Util.H"\
	

!IF  "$(CFG)" == "DiffInst - Win32 Release"


".\RELEASE\DIFFINST.OBJ" : $(SOURCE) $(DEP_CPP_DIFFIN) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "DiffInst - Win32 Debug"


".\DEBUG\DIFFINST.OBJ" : $(SOURCE) $(DEP_CPP_DIFFIN) "$(INTDIR)"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\DIFFINST.DEF

!IF  "$(CFG)" == "DiffInst - Win32 Release"

!ELSEIF  "$(CFG)" == "DiffInst - Win32 Debug"

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\DIFFINST.RC
DEP_RSC_DIFFINS=\
	".\DIFFICTL.BMP"\
	".\DiffInst.TLB"\
	".\Resource.H"\
	{$(INCLUDE)}"\DWINVERS.H"\
	

!IF  "$(CFG)" == "DiffInst - Win32 Release"


".\RELEASE\DIFFINST.res" : $(SOURCE) $(DEP_RSC_DIFFINS) "$(INTDIR)"
   $(RSC) $(RSC_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "DiffInst - Win32 Debug"


".\DEBUG\DIFFINST.res" : $(SOURCE) $(DEP_RSC_DIFFINS) "$(INTDIR)"
   $(RSC) $(RSC_PROJ) $(SOURCE)


!ENDIF 

# End Source File
# End Target
# End Project
################################################################################
