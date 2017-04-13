# Microsoft Developer Studio Project File - Name="sampclnt" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 5.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Console Application" 0x0103
# TARGTYPE "Win32 (ALPHA) Console Application" 0x0603

CFG=sampclnt - Win32 x86 Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "sampclnt.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "sampclnt.mak" CFG="sampclnt - Win32 x86 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "sampclnt - Win32 x86 Debug" (based on\
 "Win32 (x86) Console Application")
!MESSAGE "sampclnt - Win32 x86 Release" (based on\
 "Win32 (x86) Console Application")
!MESSAGE "sampclnt - Win32 (ALPHA) axp Debug" (based on\
 "Win32 (ALPHA) Console Application")
!MESSAGE "sampclnt - Win32 (ALPHA) axp Release" (based on\
 "Win32 (ALPHA) Console Application")
!MESSAGE 

# Begin Project
# PROP Scc_ProjName ""$/Chinook/samples/sampclnt", ABBAAAAA"
# PROP Scc_LocalPath "."

!IF  "$(CFG)" == "sampclnt - Win32 x86 Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir ".\sampclnt"
# PROP BASE Intermediate_Dir ".\sampclnt"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir ".\x86_debu"
# PROP Intermediate_Dir ".\x86_debu"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
CPP=cl.exe
# ADD BASE CPP /nologo /W3 /Gm /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_CONSOLE" /YX /c
# SUBTRACT BASE CPP /Fr
# ADD CPP /nologo /W3 /Gm /Zi /Od /I "..\..\include" /D "WIN32" /D "_DEBUG" /D "_CONSOLE" /YX /FD /c
# SUBTRACT CPP /Fr
RSC=rc.exe
# ADD BASE RSC /l 0x409 /d "_DEBUG"
# ADD RSC /l 0x409 /d "_DEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 dbuuid.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:console /debug /machine:I386
# SUBTRACT BASE LINK32 /map
# ADD LINK32 oledb.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib /nologo /subsystem:console /debug /machine:I386 /libpath:"..\..\LIB\$(PROCESSOR_ARCHITECTURE)"
# SUBTRACT LINK32 /map

!ELSEIF  "$(CFG)" == "sampclnt - Win32 x86 Release"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir ".\sampclnt"
# PROP BASE Intermediate_Dir ".\sampclnt"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir ".\x86_Rele"
# PROP Intermediate_Dir ".\x86_Rele"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
CPP=cl.exe
# ADD BASE CPP /nologo /W3 /Gm /GX /Zi /O2 /D "WIN32" /D "_CONSOLE" /YX /c
# SUBTRACT BASE CPP /Fr
# ADD CPP /nologo /MD /W3 /Gi /O2 /I "..\..\include" /D "WIN32" /D "_CONSOLE" /YX /FD /c
RSC=rc.exe
# ADD BASE RSC /l 0x409
# ADD RSC /l 0x409
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 dbuuid.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib /nologo /subsystem:console /debug /machine:I386
# SUBTRACT BASE LINK32 /map
# ADD LINK32 oledb.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib /nologo /subsystem:console /machine:I386 /libpath:"..\..\LIB\$(PROCESSOR_ARCHITECTURE)"
# SUBTRACT LINK32 /pdb:none /map /debug

!ELSEIF  "$(CFG)" == "sampclnt - Win32 (ALPHA) axp Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir ".\sampclnt"
# PROP BASE Intermediate_Dir ".\sampclnt"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir ".\axp_Debu"
# PROP Intermediate_Dir ".\axp_Debu"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
CPP=cl.exe
# ADD BASE CPP /nologo /Gt0 /W3 /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_CONSOLE" /YX /c
# ADD CPP /nologo /Gt0 /W3 /Zi /Od /I "..\..\include" /D "WIN32" /D "_DEBUG" /D "_CONSOLE" /YX /FD /c
RSC=rc.exe
# ADD BASE RSC /l 0x409 /d "_DEBUG"
# ADD RSC /l 0x409 /d "_DEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:console /debug /machine:ALPHA
# ADD LINK32 oledb.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib /nologo /subsystem:console /debug /machine:ALPHA /libpath:"..\..\LIB\$(PROCESSOR_ARCHITECTURE)"

!ELSEIF  "$(CFG)" == "sampclnt - Win32 (ALPHA) axp Release"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir ".\sampclnt"
# PROP BASE Intermediate_Dir ".\sampclnt"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir ".\axp_Rele"
# PROP Intermediate_Dir ".\axp_Rele"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
CPP=cl.exe
# ADD BASE CPP /nologo /Gt0 /W3 /GX /Zi /O2 /D "WIN32" /D "_DEBUG" /D "_CONSOLE" /YX /c
# ADD CPP /nologo /MD /Gt0 /W3 /O2 /I "..\..\include" /D "WIN32" /D "_CONSOLE" /YX /FD /c
RSC=rc.exe
# ADD BASE RSC /l 0x409 /d "_DEBUG"
# ADD RSC /l 0x409 /d "_DEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 oledb.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:console /machine:ALPHA
# SUBTRACT BASE LINK32 /pdb:none /map /debug
# ADD LINK32 odbc32.lib odbccp32.lib oledb.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib /nologo /subsystem:console /machine:ALPHA /libpath:"..\..\LIB\$(PROCESSOR_ARCHITECTURE)"
# SUBTRACT LINK32 /pdb:none /map /debug

!ENDIF 

# Begin Target

# Name "sampclnt - Win32 x86 Debug"
# Name "sampclnt - Win32 x86 Release"
# Name "sampclnt - Win32 (ALPHA) axp Debug"
# Name "sampclnt - Win32 (ALPHA) axp Release"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;hpj;bat;for;f90"
# Begin Source File

SOURCE=.\dump.cpp

!IF  "$(CFG)" == "sampclnt - Win32 x86 Debug"

!ELSEIF  "$(CFG)" == "sampclnt - Win32 x86 Release"

!ELSEIF  "$(CFG)" == "sampclnt - Win32 (ALPHA) axp Debug"

DEP_CPP_DUMP_=\
	"..\..\include\oledb.h"\
	"..\..\include\oledberr.h"\
	"..\..\include\transact.h"\
	".\sampclnt.h"\
	

!ELSEIF  "$(CFG)" == "sampclnt - Win32 (ALPHA) axp Release"

DEP_CPP_DUMP_=\
	"..\..\include\oledb.h"\
	"..\..\include\oledberr.h"\
	"..\..\include\transact.h"\
	".\sampclnt.h"\
	

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\sampclnt.cpp

!IF  "$(CFG)" == "sampclnt - Win32 x86 Debug"

!ELSEIF  "$(CFG)" == "sampclnt - Win32 x86 Release"

!ELSEIF  "$(CFG)" == "sampclnt - Win32 (ALPHA) axp Debug"

DEP_CPP_SAMPC=\
	"..\..\include\oledb.h"\
	"..\..\include\oledberr.h"\
	"..\..\include\transact.h"\
	".\sampclnt.h"\
	

!ELSEIF  "$(CFG)" == "sampclnt - Win32 (ALPHA) axp Release"

DEP_CPP_SAMPC=\
	"..\..\include\oledb.h"\
	"..\..\include\oledberr.h"\
	"..\..\include\transact.h"\
	".\sampclnt.h"\
	

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\sampclnt.rc
# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl;fi;fd"
# Begin Source File

SOURCE=.\sampclnt.h
# End Source File
# Begin Source File

SOURCE=.\sampver.h
# End Source File
# End Group
# Begin Group "Resource Files"

# PROP Default_Filter "ico;cur;bmp;dlg;rc2;rct;bin;cnt;rtf;gif;jpg;jpeg;jpe"
# Begin Source File

SOURCE=.\sampclnt.rc2
# End Source File
# End Group
# End Target
# End Project
