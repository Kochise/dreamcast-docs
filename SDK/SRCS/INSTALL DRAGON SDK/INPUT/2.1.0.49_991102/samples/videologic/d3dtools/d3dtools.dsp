# Microsoft Developer Studio Project File - Name="D3DTools" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (WCE SH4) Static Library" 0x8604

CFG=D3DTools - Win32 (WCE SH4) Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "D3DTools.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "D3DTools.mak" CFG="D3DTools - Win32 (WCE SH4) Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "D3DTools - Win32 (WCE SH4) Release" (based on "Win32 (WCE SH4) Static Library")
!MESSAGE "D3DTools - Win32 (WCE SH4) Debug" (based on "Win32 (WCE SH4) Static Library")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath "Dreamcast"
# PROP WCE_FormatVersion "6.0"
CPP=shcl.exe

!IF  "$(CFG)" == "D3DTools - Win32 (WCE SH4) Release"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "WCESH4Rel"
# PROP BASE Intermediate_Dir "WCESH4Rel"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "WCESH4Rel"
# PROP Intermediate_Dir "WCESH4Rel"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MC /W3 /Zi /Ox /D _WIN32_WCE=$(CEVersion) /D "$(CEConfigName)" /D "NDEBUG" /D "SHx" /D "SH4" /D "_SH4_" /D UNDER_CE=$(CEVersion) /D "UNICODE" /D "_MBCS" /D "_UNICODE" /YX /Qsh4r7 /Qs /Qfast /Qgvp /c
# ADD CPP /nologo /MC /W3 /Zi /Ox /D _WIN32_WCE=$(CEVersion) /D "$(CEConfigName)" /D "NDEBUG" /D "SHx" /D "SH4" /D "_SH4_" /D UNDER_CE=$(CEVersion) /D "UNICODE" /D "_MBCS" /D "_UNICODE" /YX /Qsh4r7 /Qs /Qfast /Qgvp /c
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo
# ADD LIB32 /nologo /out:"lib\D3DTools.lib"

!ELSEIF  "$(CFG)" == "D3DTools - Win32 (WCE SH4) Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "WCESH4Dbg"
# PROP BASE Intermediate_Dir "WCESH4Dbg"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "WCESH4Dbg"
# PROP Intermediate_Dir "WCESH4Dbg"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MC /W3 /Zi /Od /D _WIN32_WCE=$(CEVersion) /D "$(CEConfigName)" /D "DEBUG" /D "SHx" /D "SH4" /D "_SH4_" /D UNDER_CE=$(CEVersion) /D "UNICODE" /D "_MBCS" /D "_UNICODE" /YX /Qsh4r7 /Qs /Qfast /c
# ADD CPP /nologo /MC /W3 /Zi /Od /D _WIN32_WCE=$(CEVersion) /D "$(CEConfigName)" /D "DEBUG" /D "SHx" /D "SH4" /D "_SH4_" /D UNDER_CE=$(CEVersion) /D "UNICODE" /D "_MBCS" /D "_UNICODE" /YX /Qsh4r7 /Qs /Qfast /c
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo
# ADD LIB32 /nologo /out:"lib\D3DTools.lib"

!ENDIF 

# Begin Target

# Name "D3DTools - Win32 (WCE SH4) Release"
# Name "D3DTools - Win32 (WCE SH4) Debug"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
# Begin Source File

SOURCE=.\D3DTBump.c
DEP_CPP_D3DTB=\
	".\D3DTools.h"\
	
NODEP_CPP_D3DTB=\
	".\hintr.h"\
	
# End Source File
# Begin Source File

SOURCE=.\D3DTController.c
DEP_CPP_D3DTC=\
	".\D3DTController.h"\
	
NODEP_CPP_D3DTC=\
	".\aplusag.h"\
	
# End Source File
# Begin Source File

SOURCE=.\D3DTLight.c
DEP_CPP_D3DTL=\
	".\D3DTLight.h"\
	".\D3DTMatrix.h"\
	
# End Source File
# Begin Source File

SOURCE=.\D3DTMatrix.c
DEP_CPP_D3DTM=\
	".\D3DTMatrix.h"\
	
NODEP_CPP_D3DTM=\
	".\hintr.h"\
	
# End Source File
# Begin Source File

SOURCE=.\D3DTMisc.c
DEP_CPP_D3DTMI=\
	".\D3DTMisc.h"\
	
# End Source File
# Begin Source File

SOURCE=.\D3DTPrint3D.c
DEP_CPP_D3DTP=\
	".\D3DTPrint3D.h"\
	
NODEP_CPP_D3DTP=\
	".\D3DTPrint3D.dat"\
	
# End Source File
# Begin Source File

SOURCE=.\D3DTTexture.c
DEP_CPP_D3DTT=\
	".\D3DTTexture.h"\
	
# End Source File
# Begin Source File

SOURCE=.\D3DTTrans.c
DEP_CPP_D3DTTR=\
	".\D3DTMatrix.h"\
	".\D3DTTrans.h"\
	
NODEP_CPP_D3DTTR=\
	".\hintr.h"\
	
# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl"
# End Group
# End Target
# End Project
