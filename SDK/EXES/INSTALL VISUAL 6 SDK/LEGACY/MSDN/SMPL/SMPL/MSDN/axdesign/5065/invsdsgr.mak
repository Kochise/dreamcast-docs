# Microsoft Developer Studio Generated NMAKE File, Format Version 4.10
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Dynamic-Link Library" 0x0102

!IF "$(CFG)" == ""
CFG=InvsDsgr - Win32 Debug
!MESSAGE No configuration specified.  Defaulting to InvsDsgr - Win32 Debug.
!ENDIF 

!IF "$(CFG)" != "InvsDsgr - Win32 Release" && "$(CFG)" !=\
 "InvsDsgr - Win32 Debug"
!MESSAGE Invalid configuration "$(CFG)" specified.
!MESSAGE You can specify a configuration when running NMAKE on this makefile
!MESSAGE by defining the macro CFG on the command line.  For example:
!MESSAGE 
!MESSAGE NMAKE /f "InvsDsgr.mak" CFG="InvsDsgr - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "InvsDsgr - Win32 Release" (based on\
 "Win32 (x86) Dynamic-Link Library")
!MESSAGE "InvsDsgr - Win32 Debug" (based on "Win32 (x86) Dynamic-Link Library")
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
# PROP Target_Last_Scanned "InvsDsgr - Win32 Debug"
CPP=cl.exe
RSC=rc.exe
MTL=mktyplib.exe

!IF  "$(CFG)" == "InvsDsgr - Win32 Release"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "InvsDsgr"
# PROP BASE Intermediate_Dir "InvsDsgr"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "RELEASE"
# PROP Intermediate_Dir "RELEASE"
# PROP Target_Dir ""
OUTDIR=.\RELEASE
INTDIR=.\RELEASE

ALL : ".\RELEASE\InvsDsgr.dll"

CLEAN : 
	-@erase ".\RELEASE\GUIDS.OBJ"
	-@erase ".\RELEASE\INVSDCTL.OBJ"
	-@erase ".\RELEASE\INVSDPPG.OBJ"
	-@erase ".\RELEASE\InvsDsgr.dll"
	-@erase ".\RELEASE\InvsDsgr.exp"
	-@erase ".\RELEASE\InvsDsgr.lib"
	-@erase ".\RELEASE\INVSDSGR.OBJ"
	-@erase ".\RELEASE\INVSDSGR.res"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

# ADD BASE CPP /nologo /MT /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /YX /c
# ADD CPP /nologo /MT /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /YX /c
CPP_PROJ=/nologo /MT /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS"\
 /Fp"$(INTDIR)/InvsDsgr.pch" /YX /Fo"$(INTDIR)/" /c 
CPP_OBJS=.\RELEASE/
CPP_SBRS=.\.
# ADD BASE MTL /nologo /D "NDEBUG" /win32
# ADD MTL /nologo /D "NDEBUG" /win32
MTL_PROJ=/nologo /D "NDEBUG" /win32 
# ADD BASE RSC /l 0x409 /d "NDEBUG"
# ADD RSC /l 0x409 /d "NDEBUG"
RSC_PROJ=/l 0x409 /fo"$(INTDIR)/INVSDSGR.res" /d "NDEBUG" 
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
BSC32_FLAGS=/nologo /o"$(OUTDIR)/InvsDsgr.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /dll /machine:I386
# ADD LINK32 AXFWr.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib ocx96.lib uuid2.lib /nologo /subsystem:windows /dll /machine:I386
LINK32_FLAGS=AXFWr.lib kernel32.lib user32.lib gdi32.lib winspool.lib\
 comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib\
 odbc32.lib odbccp32.lib ocx96.lib uuid2.lib /nologo /subsystem:windows /dll\
 /incremental:no /pdb:"$(OUTDIR)/InvsDsgr.pdb" /machine:I386\
 /def:".\INVSDSGR.DEF" /out:"$(OUTDIR)/InvsDsgr.dll"\
 /implib:"$(OUTDIR)/InvsDsgr.lib" 
DEF_FILE= \
	".\INVSDSGR.DEF"
LINK32_OBJS= \
	".\RELEASE\GUIDS.OBJ" \
	".\RELEASE\INVSDCTL.OBJ" \
	".\RELEASE\INVSDPPG.OBJ" \
	".\RELEASE\INVSDSGR.OBJ" \
	".\RELEASE\INVSDSGR.res"

".\RELEASE\InvsDsgr.dll" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ELSEIF  "$(CFG)" == "InvsDsgr - Win32 Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "InvsDsg0"
# PROP BASE Intermediate_Dir "InvsDsg0"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "DEBUG"
# PROP Intermediate_Dir "DEBUG"
# PROP Target_Dir ""
OUTDIR=.\DEBUG
INTDIR=.\DEBUG

ALL : ".\DEBUG\InvsDsgr.dll" ".\DEBUG\InvsDsgr.bsc"

CLEAN : 
	-@erase ".\DEBUG\GUIDS.OBJ"
	-@erase ".\DEBUG\GUIDS.SBR"
	-@erase ".\DEBUG\INVSDCTL.OBJ"
	-@erase ".\DEBUG\INVSDCTL.SBR"
	-@erase ".\DEBUG\INVSDPPG.OBJ"
	-@erase ".\DEBUG\INVSDPPG.SBR"
	-@erase ".\DEBUG\InvsDsgr.bsc"
	-@erase ".\DEBUG\InvsDsgr.dll"
	-@erase ".\DEBUG\InvsDsgr.exp"
	-@erase ".\DEBUG\InvsDsgr.ilk"
	-@erase ".\DEBUG\InvsDsgr.lib"
	-@erase ".\DEBUG\INVSDSGR.OBJ"
	-@erase ".\DEBUG\InvsDsgr.pdb"
	-@erase ".\DEBUG\INVSDSGR.res"
	-@erase ".\DEBUG\INVSDSGR.SBR"
	-@erase ".\DEBUG\vc40.idb"
	-@erase ".\DEBUG\vc40.pdb"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

# ADD BASE CPP /nologo /MTd /W3 /Gm /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /YX /c
# ADD CPP /nologo /MTd /W3 /Gm /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /FR /YX /c
CPP_PROJ=/nologo /MTd /W3 /Gm /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS"\
 /FR"$(INTDIR)/" /Fp"$(INTDIR)/InvsDsgr.pch" /YX /Fo"$(INTDIR)/" /Fd"$(INTDIR)/"\
 /c 
CPP_OBJS=.\DEBUG/
CPP_SBRS=.\DEBUG/
# ADD BASE MTL /nologo /D "_DEBUG" /win32
# ADD MTL /nologo /D "_DEBUG" /win32
MTL_PROJ=/nologo /D "_DEBUG" /win32 
# ADD BASE RSC /l 0x409 /d "_DEBUG"
# ADD RSC /l 0x409 /d "_DEBUG"
RSC_PROJ=/l 0x409 /fo"$(INTDIR)/INVSDSGR.res" /d "_DEBUG" 
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
BSC32_FLAGS=/nologo /o"$(OUTDIR)/InvsDsgr.bsc" 
BSC32_SBRS= \
	".\DEBUG\GUIDS.SBR" \
	".\DEBUG\INVSDCTL.SBR" \
	".\DEBUG\INVSDPPG.SBR" \
	".\DEBUG\INVSDSGR.SBR"

".\DEBUG\InvsDsgr.bsc" : "$(OUTDIR)" $(BSC32_SBRS)
    $(BSC32) @<<
  $(BSC32_FLAGS) $(BSC32_SBRS)
<<

LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /dll /debug /machine:I386
# ADD LINK32 AXFWd.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib ocx96.lib uuid2.lib /nologo /subsystem:windows /dll /debug /machine:I386
LINK32_FLAGS=AXFWd.lib kernel32.lib user32.lib gdi32.lib winspool.lib\
 comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib\
 odbc32.lib odbccp32.lib ocx96.lib uuid2.lib /nologo /subsystem:windows /dll\
 /incremental:yes /pdb:"$(OUTDIR)/InvsDsgr.pdb" /debug /machine:I386\
 /def:".\INVSDSGR.DEF" /out:"$(OUTDIR)/InvsDsgr.dll"\
 /implib:"$(OUTDIR)/InvsDsgr.lib" 
DEF_FILE= \
	".\INVSDSGR.DEF"
LINK32_OBJS= \
	".\DEBUG\GUIDS.OBJ" \
	".\DEBUG\INVSDCTL.OBJ" \
	".\DEBUG\INVSDPPG.OBJ" \
	".\DEBUG\INVSDSGR.OBJ" \
	".\DEBUG\INVSDSGR.res"

".\DEBUG\InvsDsgr.dll" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
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

# Name "InvsDsgr - Win32 Release"
# Name "InvsDsgr - Win32 Debug"

!IF  "$(CFG)" == "InvsDsgr - Win32 Release"

!ELSEIF  "$(CFG)" == "InvsDsgr - Win32 Debug"

!ENDIF 

################################################################################
# Begin Source File

SOURCE=.\INVSDSGR.CPP
DEP_CPP_INVSD=\
	"..\..\MSDEV\INCLUDE\AutoObj.H"\
	"..\..\MSDEV\INCLUDE\Debug.H"\
	"..\..\MSDEV\INCLUDE\Unknown.H"\
	".\Dispids.H"\
	".\Guids.H"\
	".\InvsDCtl.H"\
	".\InvsDPPG.H"\
	".\InvsDsgrInterfaces.H"\
	".\LocalObj.H"\
	".\Resource.H"\
	{$(INCLUDE)}"\CtrlObj.H"\
	{$(INCLUDE)}"\Designer.H"\
	{$(INCLUDE)}"\Globals.H"\
	{$(INCLUDE)}"\IPServer.H"\
	{$(INCLUDE)}"\LocalSrv.H"\
	{$(INCLUDE)}"\PropPage.H"\
	{$(INCLUDE)}"\Util.H"\
	

!IF  "$(CFG)" == "InvsDsgr - Win32 Release"


".\RELEASE\INVSDSGR.OBJ" : $(SOURCE) $(DEP_CPP_INVSD) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "InvsDsgr - Win32 Debug"


".\DEBUG\INVSDSGR.OBJ" : $(SOURCE) $(DEP_CPP_INVSD) "$(INTDIR)"

".\DEBUG\INVSDSGR.SBR" : $(SOURCE) $(DEP_CPP_INVSD) "$(INTDIR)"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\INVSDCTL.CPP
DEP_CPP_INVSDC=\
	"..\..\MSDEV\INCLUDE\AutoObj.H"\
	"..\..\MSDEV\INCLUDE\Debug.H"\
	"..\..\MSDEV\INCLUDE\Unknown.H"\
	".\Dispids.H"\
	".\Guids.H"\
	".\InvsDCtl.H"\
	".\InvsDsgrInterfaces.H"\
	".\LocalObj.H"\
	".\Resource.H"\
	{$(INCLUDE)}"\CtrlObj.H"\
	{$(INCLUDE)}"\Designer.H"\
	{$(INCLUDE)}"\Globals.H"\
	{$(INCLUDE)}"\IPServer.H"\
	{$(INCLUDE)}"\LocalSrv.H"\
	{$(INCLUDE)}"\Util.H"\
	

!IF  "$(CFG)" == "InvsDsgr - Win32 Release"


".\RELEASE\INVSDCTL.OBJ" : $(SOURCE) $(DEP_CPP_INVSDC) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "InvsDsgr - Win32 Debug"


".\DEBUG\INVSDCTL.OBJ" : $(SOURCE) $(DEP_CPP_INVSDC) "$(INTDIR)"

".\DEBUG\INVSDCTL.SBR" : $(SOURCE) $(DEP_CPP_INVSDC) "$(INTDIR)"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\INVSDPPG.CPP
DEP_CPP_INVSDP=\
	"..\..\MSDEV\INCLUDE\AutoObj.H"\
	"..\..\MSDEV\INCLUDE\Debug.H"\
	"..\..\MSDEV\INCLUDE\Unknown.H"\
	".\Dispids.H"\
	".\Guids.H"\
	".\InvsDCtl.H"\
	".\InvsDPPG.H"\
	".\InvsDsgrInterfaces.H"\
	".\LocalObj.H"\
	".\Resource.H"\
	{$(INCLUDE)}"\CtrlObj.H"\
	{$(INCLUDE)}"\Designer.H"\
	{$(INCLUDE)}"\Globals.H"\
	{$(INCLUDE)}"\IPServer.H"\
	{$(INCLUDE)}"\LocalSrv.H"\
	{$(INCLUDE)}"\PropPage.H"\
	{$(INCLUDE)}"\Util.H"\
	

!IF  "$(CFG)" == "InvsDsgr - Win32 Release"


".\RELEASE\INVSDPPG.OBJ" : $(SOURCE) $(DEP_CPP_INVSDP) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "InvsDsgr - Win32 Debug"


".\DEBUG\INVSDPPG.OBJ" : $(SOURCE) $(DEP_CPP_INVSDP) "$(INTDIR)"

".\DEBUG\INVSDPPG.SBR" : $(SOURCE) $(DEP_CPP_INVSDP) "$(INTDIR)"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\GUIDS.CPP
DEP_CPP_GUIDS=\
	"..\..\MSDEV\INCLUDE\Debug.H"\
	".\Guids.H"\
	".\InvsDsgrInterfaces.H"\
	{$(INCLUDE)}"\Designer.H"\
	{$(INCLUDE)}"\IPServer.H"\
	

!IF  "$(CFG)" == "InvsDsgr - Win32 Release"


".\RELEASE\GUIDS.OBJ" : $(SOURCE) $(DEP_CPP_GUIDS) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "InvsDsgr - Win32 Debug"


".\DEBUG\GUIDS.OBJ" : $(SOURCE) $(DEP_CPP_GUIDS) "$(INTDIR)"

".\DEBUG\GUIDS.SBR" : $(SOURCE) $(DEP_CPP_GUIDS) "$(INTDIR)"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\INVSDSGR.DEF

!IF  "$(CFG)" == "InvsDsgr - Win32 Release"

!ELSEIF  "$(CFG)" == "InvsDsgr - Win32 Debug"

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\INVSDSGR.RC
DEP_RSC_INVSDS=\
	".\InvsDCtl.Bmp"\
	".\InvsDsgr.TLB"\
	".\Resource.H"\
	{$(INCLUDE)}"\dwinvers.h"\
	

!IF  "$(CFG)" == "InvsDsgr - Win32 Release"


".\RELEASE\INVSDSGR.res" : $(SOURCE) $(DEP_RSC_INVSDS) "$(INTDIR)"
   $(RSC) $(RSC_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "InvsDsgr - Win32 Debug"


".\DEBUG\INVSDSGR.res" : $(SOURCE) $(DEP_RSC_INVSDS) "$(INTDIR)"
   $(RSC) $(RSC_PROJ) $(SOURCE)


!ENDIF 

# End Source File
# End Target
# End Project
################################################################################
