# Microsoft Developer Studio Generated NMAKE File, Format Version 4.10
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Dynamic-Link Library" 0x0102

!IF "$(CFG)" == ""
CFG=WinTlb - Win32 Release
!MESSAGE No configuration specified.  Defaulting to WinTlb - Win32 Release.
!ENDIF 

!IF "$(CFG)" != "WinTlb - Win32 Release" && "$(CFG)" !=\
 "WinTlb - Win32 Release 16"
!MESSAGE Invalid configuration "$(CFG)" specified.
!MESSAGE You can specify a configuration when running NMAKE on this makefile
!MESSAGE by defining the macro CFG on the command line.  For example:
!MESSAGE 
!MESSAGE NMAKE /f "WINTLB.MAK" CFG="WinTlb - Win32 Release"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "WinTlb - Win32 Release" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE "WinTlb - Win32 Release 16" (based on\
 "Win32 (x86) Dynamic-Link Library")
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
# PROP Target_Last_Scanned "WinTlb - Win32 Release 16"
MTL=mktyplib.exe
CPP=cl.exe
RSC=rc.exe

!IF  "$(CFG)" == "WinTlb - Win32 Release"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "Release"
# PROP BASE Intermediate_Dir "Release"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "Release"
# PROP Intermediate_Dir "Release"
# PROP Target_Dir ""
OUTDIR=.\Release
INTDIR=.\Release

ALL : "..\..\WINDOWS\WIN32.tlb"

CLEAN : 
	-@erase "..\..\WINDOWS\WIN32.tlb"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

# ADD BASE CPP /nologo /MT /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /YX /c
# ADD CPP /nologo /MT /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /YX /c
CPP_OBJS=.\Release/
CPP_SBRS=.\.
# ADD BASE MTL /nologo /D "NDEBUG" /win32
# ADD MTL /nologo /D "NDEBUG" /D "WIN32" /win32
MTL_PROJ=/nologo /D "NDEBUG" /D "WIN32" /win32 
# ADD BASE RSC /l 0x409 /d "NDEBUG"
# ADD RSC /l 0x409 /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
BSC32_FLAGS=/nologo /o"$(OUTDIR)/WINTLB.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib /nologo /subsystem:windows /dll /machine:I386
# ADD LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib /nologo /subsystem:windows /dll /machine:I386
LINK32_FLAGS=kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib\
 advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib /nologo\
 /subsystem:windows /dll /incremental:no /pdb:"$(OUTDIR)/WINTLB.pdb"\
 /machine:I386 /out:"$(OUTDIR)/WINTLB.dll" /implib:"$(OUTDIR)/WINTLB.lib" 
LINK32_OBJS= \
	

!ELSEIF  "$(CFG)" == "WinTlb - Win32 Release 16"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "Release 16"
# PROP BASE Intermediate_Dir "Release 16"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "Release 16"
# PROP Intermediate_Dir "Release 16"
# PROP Target_Dir ""
OUTDIR=.\Release 16
INTDIR=.\Release 16

ALL : "..\..\WINDOWS\WIN16.tlb"

CLEAN : 
	-@erase "..\..\WINDOWS\WIN16.tlb"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

# ADD BASE CPP /nologo /MT /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /YX /c
# ADD CPP /nologo /MT /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /YX /c
CPP_OBJS=".\Release 16/"
CPP_SBRS=.\.
# ADD BASE MTL /nologo /D "NDEBUG" /win32
# ADD MTL /nologo /D "NDEBUG" /D "WIN16" /win16
MTL_PROJ=/nologo /D "NDEBUG" /D "WIN16" /win16 
# ADD BASE RSC /l 0x409 /d "NDEBUG"
# ADD RSC /l 0x409 /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
BSC32_FLAGS=/nologo /o"$(OUTDIR)/WINTLB.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib /nologo /subsystem:windows /dll /machine:I386
# ADD LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib /nologo /subsystem:windows /dll /machine:I386
LINK32_FLAGS=kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib\
 advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib /nologo\
 /subsystem:windows /dll /incremental:no /pdb:"$(OUTDIR)/WINTLB.pdb"\
 /machine:I386 /out:"$(OUTDIR)/WINTLB.dll" /implib:"$(OUTDIR)/WINTLB.lib" 
LINK32_OBJS= \
	

!ENDIF 

CPP_PROJ=/nologo /MT /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS"\
 /Fp"$(INTDIR)/WINTLB.pch" /YX /Fo"$(INTDIR)/" /c 

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

# Name "WinTlb - Win32 Release"
# Name "WinTlb - Win32 Release 16"

!IF  "$(CFG)" == "WinTlb - Win32 Release"

!ELSEIF  "$(CFG)" == "WinTlb - Win32 Release 16"

!ENDIF 

################################################################################
# Begin Source File

SOURCE=.\WIN.ODL
DEP_MTL_WIN_O=\
	".\comconst.odl"\
	".\comctl.odl"\
	".\gdi.odl"\
	".\intrface.odl"\
	".\kernel.odl"\
	".\network.odl"\
	".\oleauto.odl"\
	".\registry.odl"\
	".\shell.odl"\
	".\user.odl"\
	".\winbase.odl"\
	".\winerr.odl"\
	".\winmm.odl"\
	".\winmsg.odl"\
	".\wintype.odl"\
	

!IF  "$(CFG)" == "WinTlb - Win32 Release"

# ADD MTL /tlb "C:\WINDOWS\WIN32.tlb"

"..\..\WINDOWS\WIN32.tlb" : $(SOURCE) $(DEP_MTL_WIN_O) "$(OUTDIR)"
   $(MTL) /nologo /D "NDEBUG" /D "WIN32" /tlb "C:\WINDOWS\WIN32.tlb" /win32\
 $(SOURCE)


!ELSEIF  "$(CFG)" == "WinTlb - Win32 Release 16"

# ADD MTL /tlb "C:\WINDOWS\WIN16.tlb"

"..\..\WINDOWS\WIN16.tlb" : $(SOURCE) $(DEP_MTL_WIN_O) "$(OUTDIR)"
   $(MTL) /nologo /D "NDEBUG" /D "WIN16" /tlb "C:\WINDOWS\WIN16.tlb" /win16\
 $(SOURCE)


!ENDIF 

# End Source File
# End Target
# End Project
################################################################################
