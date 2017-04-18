# Microsoft Developer Studio Generated NMAKE File, Format Version 4.10
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Dynamic-Link Library" 0x0102

!IF "$(CFG)" == ""
CFG=INVSINST - Win32 Debug
!MESSAGE No configuration specified.  Defaulting to INVSINST - Win32 Debug.
!ENDIF 

!IF "$(CFG)" != "INVSINST - Win32 Release" && "$(CFG)" !=\
 "INVSINST - Win32 Debug"
!MESSAGE Invalid configuration "$(CFG)" specified.
!MESSAGE You can specify a configuration when running NMAKE on this makefile
!MESSAGE by defining the macro CFG on the command line.  For example:
!MESSAGE 
!MESSAGE NMAKE /f "INVSINST.mak" CFG="INVSINST - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "INVSINST - Win32 Release" (based on\
 "Win32 (x86) Dynamic-Link Library")
!MESSAGE "INVSINST - Win32 Debug" (based on "Win32 (x86) Dynamic-Link Library")
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
# PROP Target_Last_Scanned "INVSINST - Win32 Debug"
CPP=cl.exe
RSC=rc.exe
MTL=mktyplib.exe

!IF  "$(CFG)" == "INVSINST - Win32 Release"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "INVSINST"
# PROP BASE Intermediate_Dir "INVSINST"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "RELEASE"
# PROP Intermediate_Dir "RELEASE"
# PROP Target_Dir ""
OUTDIR=.\RELEASE
INTDIR=.\RELEASE

ALL : "$(OUTDIR)\INVSINST.dll"

CLEAN : 
	-@erase "$(INTDIR)\GUIDS.OBJ"
	-@erase "$(INTDIR)\INVSINST.OBJ"
	-@erase "$(INTDIR)\INVSINST.res"
	-@erase "$(INTDIR)\INVSIOBJ.OBJ"
	-@erase "$(OUTDIR)\INVSINST.dll"
	-@erase "$(OUTDIR)\INVSINST.exp"
	-@erase "$(OUTDIR)\INVSINST.lib"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

# ADD BASE CPP /nologo /MT /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /YX /c
# ADD CPP /nologo /MT /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /YX /c
CPP_PROJ=/nologo /MT /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS"\
 /Fp"$(INTDIR)/INVSINST.pch" /YX /Fo"$(INTDIR)/" /c 
CPP_OBJS=.\RELEASE/
CPP_SBRS=.\.
# ADD BASE MTL /nologo /D "NDEBUG" /win32
# ADD MTL /nologo /D "NDEBUG" /win32
MTL_PROJ=/nologo /D "NDEBUG" /win32 
# ADD BASE RSC /l 0x409 /d "NDEBUG"
# ADD RSC /l 0x409 /d "NDEBUG"
RSC_PROJ=/l 0x409 /fo"$(INTDIR)/INVSINST.res" /d "NDEBUG" 
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
BSC32_FLAGS=/nologo /o"$(OUTDIR)/INVSINST.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /dll /machine:I386
# ADD LINK32 AXFWr.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib ocx96.lib uuid2.lib /nologo /subsystem:windows /dll /machine:I386 /nodefaultlib:"libCD.lib"
LINK32_FLAGS=AXFWr.lib kernel32.lib user32.lib gdi32.lib winspool.lib\
 comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib\
 odbc32.lib odbccp32.lib ocx96.lib uuid2.lib /nologo /subsystem:windows /dll\
 /incremental:no /pdb:"$(OUTDIR)/INVSINST.pdb" /machine:I386\
 /nodefaultlib:"libCD.lib" /def:".\INVSINST.DEF" /out:"$(OUTDIR)/INVSINST.dll"\
 /implib:"$(OUTDIR)/INVSINST.lib" 
DEF_FILE= \
	".\INVSINST.DEF"
LINK32_OBJS= \
	"$(INTDIR)\GUIDS.OBJ" \
	"$(INTDIR)\INVSINST.OBJ" \
	"$(INTDIR)\INVSINST.res" \
	"$(INTDIR)\INVSIOBJ.OBJ"

"$(OUTDIR)\INVSINST.dll" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ELSEIF  "$(CFG)" == "INVSINST - Win32 Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "INVSINS0"
# PROP BASE Intermediate_Dir "INVSINS0"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "DEBUG"
# PROP Intermediate_Dir "DEBUG"
# PROP Target_Dir ""
OUTDIR=.\DEBUG
INTDIR=.\DEBUG

ALL : "$(OUTDIR)\INVSINST.dll"

CLEAN : 
	-@erase "$(INTDIR)\GUIDS.OBJ"
	-@erase "$(INTDIR)\INVSINST.OBJ"
	-@erase "$(INTDIR)\INVSINST.res"
	-@erase "$(INTDIR)\INVSIOBJ.OBJ"
	-@erase "$(INTDIR)\vc40.idb"
	-@erase "$(INTDIR)\vc40.pdb"
	-@erase "$(OUTDIR)\INVSINST.dll"
	-@erase "$(OUTDIR)\INVSINST.exp"
	-@erase "$(OUTDIR)\INVSINST.ilk"
	-@erase "$(OUTDIR)\INVSINST.lib"
	-@erase "$(OUTDIR)\INVSINST.pdb"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

# ADD BASE CPP /nologo /MTd /W3 /Gm /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /YX /c
# ADD CPP /nologo /MTd /W3 /Gm /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /YX /c
CPP_PROJ=/nologo /MTd /W3 /Gm /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS"\
 /Fp"$(INTDIR)/INVSINST.pch" /YX /Fo"$(INTDIR)/" /Fd"$(INTDIR)/" /c 
CPP_OBJS=.\DEBUG/
CPP_SBRS=.\.
# ADD BASE MTL /nologo /D "_DEBUG" /win32
# ADD MTL /nologo /D "_DEBUG" /win32
MTL_PROJ=/nologo /D "_DEBUG" /win32 
# ADD BASE RSC /l 0x409 /d "_DEBUG"
# ADD RSC /l 0x409 /d "_DEBUG"
RSC_PROJ=/l 0x409 /fo"$(INTDIR)/INVSINST.res" /d "_DEBUG" 
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
BSC32_FLAGS=/nologo /o"$(OUTDIR)/INVSINST.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /dll /debug /machine:I386
# ADD LINK32 AXFWd.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib ocx96.lib uuid2.lib /nologo /subsystem:windows /dll /debug /machine:I386 /nodefaultlib:"libCD.lib"
LINK32_FLAGS=AXFWd.lib kernel32.lib user32.lib gdi32.lib winspool.lib\
 comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib\
 odbc32.lib odbccp32.lib ocx96.lib uuid2.lib /nologo /subsystem:windows /dll\
 /incremental:yes /pdb:"$(OUTDIR)/INVSINST.pdb" /debug /machine:I386\
 /nodefaultlib:"libCD.lib" /def:".\INVSINST.DEF" /out:"$(OUTDIR)/INVSINST.dll"\
 /implib:"$(OUTDIR)/INVSINST.lib" 
DEF_FILE= \
	".\INVSINST.DEF"
LINK32_OBJS= \
	"$(INTDIR)\GUIDS.OBJ" \
	"$(INTDIR)\INVSINST.OBJ" \
	"$(INTDIR)\INVSINST.res" \
	"$(INTDIR)\INVSIOBJ.OBJ"

"$(OUTDIR)\INVSINST.dll" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
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

# Name "INVSINST - Win32 Release"
# Name "INVSINST - Win32 Debug"

!IF  "$(CFG)" == "INVSINST - Win32 Release"

!ELSEIF  "$(CFG)" == "INVSINST - Win32 Debug"

!ENDIF 

################################################################################
# Begin Source File

SOURCE=.\INVSIOBJ.CPP
DEP_CPP_INVSI=\
	"..\..\MSDEV\INCLUDE\Debug.H"\
	"..\..\MSDEV\INCLUDE\Unknown.H"\
	".\InvsInstInterfaces.H"\
	".\InvsIObj.H"\
	".\LocalObj.H"\
	{$(INCLUDE)}"\autoobj.h"\
	{$(INCLUDE)}"\CtrlObj.h"\
	{$(INCLUDE)}"\Globals.H"\
	{$(INCLUDE)}"\IPServer.H"\
	{$(INCLUDE)}"\LocalSrv.H"\
	{$(INCLUDE)}"\Util.H"\
	

"$(INTDIR)\INVSIOBJ.OBJ" : $(SOURCE) $(DEP_CPP_INVSI) "$(INTDIR)"


# End Source File
################################################################################
# Begin Source File

SOURCE=.\INVSINST.CPP
DEP_CPP_INVSIN=\
	"..\..\MSDEV\INCLUDE\Debug.H"\
	"..\..\MSDEV\INCLUDE\Unknown.H"\
	".\InvsInstInterfaces.H"\
	".\InvsIObj.H"\
	".\LocalObj.H"\
	".\Resource.H"\
	{$(INCLUDE)}"\autoobj.h"\
	{$(INCLUDE)}"\CtrlObj.h"\
	{$(INCLUDE)}"\Globals.H"\
	{$(INCLUDE)}"\IPServer.H"\
	{$(INCLUDE)}"\LocalSrv.H"\
	{$(INCLUDE)}"\Util.H"\
	

"$(INTDIR)\INVSINST.OBJ" : $(SOURCE) $(DEP_CPP_INVSIN) "$(INTDIR)"


# End Source File
################################################################################
# Begin Source File

SOURCE=.\GUIDS.CPP
DEP_CPP_GUIDS=\
	"..\..\MSDEV\INCLUDE\Debug.H"\
	".\Guids.H"\
	".\InvsInstInterfaces.H"\
	{$(INCLUDE)}"\IPServer.H"\
	

"$(INTDIR)\GUIDS.OBJ" : $(SOURCE) $(DEP_CPP_GUIDS) "$(INTDIR)"


# End Source File
################################################################################
# Begin Source File

SOURCE=.\INVSINST.DEF

!IF  "$(CFG)" == "INVSINST - Win32 Release"

!ELSEIF  "$(CFG)" == "INVSINST - Win32 Debug"

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\INVSINST.RC
DEP_RSC_INVSINS=\
	".\InvsInst.TLB"\
	".\Resource.H"\
	{$(INCLUDE)}"\dwinvers.h"\
	

"$(INTDIR)\INVSINST.res" : $(SOURCE) $(DEP_RSC_INVSINS) "$(INTDIR)"
   $(RSC) $(RSC_PROJ) $(SOURCE)


# End Source File
# End Target
# End Project
################################################################################
