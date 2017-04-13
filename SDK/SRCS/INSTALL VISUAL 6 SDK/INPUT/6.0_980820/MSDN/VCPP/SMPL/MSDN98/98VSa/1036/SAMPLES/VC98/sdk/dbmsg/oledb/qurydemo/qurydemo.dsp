# Microsoft Developer Studio Project File - Name="qurydemo" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 5.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Application" 0x0101
# TARGTYPE "Win32 (ALPHA) Application" 0x0601

CFG=qurydemo - Win32 x86 Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "qurydemo.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "qurydemo.mak" CFG="qurydemo - Win32 x86 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "qurydemo - Win32 x86 Debug" (based on "Win32 (x86) Application")
!MESSAGE "qurydemo - Win32 x86 Release" (based on "Win32 (x86) Application")
!MESSAGE "qurydemo - Win32 (ALPHA) axp Release" (based on\
 "Win32 (ALPHA) Application")
!MESSAGE "qurydemo - Win32 (ALPHA) axp Debug" (based on\
 "Win32 (ALPHA) Application")
!MESSAGE 

# Begin Project
# PROP Scc_ProjName ""$/Chinook/samples/qurydemo", UXAAAAAA"
# PROP Scc_LocalPath "."

!IF  "$(CFG)" == "qurydemo - Win32 x86 Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir ".\qurydemo"
# PROP BASE Intermediate_Dir ".\qurydemo"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir ".\X86_Debu"
# PROP Intermediate_Dir ".\X86_Debu"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
CPP=cl.exe
# ADD BASE CPP /nologo /W3 /Gm /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /YX /c
# ADD CPP /nologo /MDd /W3 /Gm /Zi /Od /I "..\..\include" /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /YX /FD /c
MTL=midl.exe
# ADD BASE MTL /nologo /D "_DEBUG" /win32
# ADD MTL /nologo /D "_DEBUG" /mktyplib203 /win32
RSC=rc.exe
# ADD BASE RSC /l 0x409 /d "_DEBUG"
# ADD RSC /l 0x409 /d "_DEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib /nologo /subsystem:windows /debug /machine:I386 /force
# ADD LINK32 oledb.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib /nologo /subsystem:windows /debug /machine:I386 /libpath:"..\..\LIB\$(PROCESSOR_ARCHITECTURE)"
# SUBTRACT LINK32 /force

!ELSEIF  "$(CFG)" == "qurydemo - Win32 x86 Release"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir ".\qurydem0"
# PROP BASE Intermediate_Dir ".\qurydem0"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir ".\X86_Rele"
# PROP Intermediate_Dir ".\X86_Rele"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
CPP=cl.exe
# ADD BASE CPP /nologo /W3 /Gm /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /YX /c
# ADD CPP /nologo /MD /W3 /Gm /Zi /Od /Ob1 /I "..\..\include" /D "WIN32" /D "_NDEBUG" /D "_WINDOWS" /FD /c
# SUBTRACT CPP /YX /Yc /Yu
MTL=midl.exe
# ADD BASE MTL /nologo /D "_DEBUG" /win32
# ADD MTL /nologo /D "_NDEBUG" /mktyplib203 /win32
RSC=rc.exe
# ADD BASE RSC /l 0x409 /d "_DEBUG"
# ADD RSC /l 0x409 /d "_NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib /nologo /subsystem:windows /debug /machine:I386 /force
# ADD LINK32 oledb.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib /nologo /subsystem:windows /machine:I386 /libpath:"..\..\LIB\$(PROCESSOR_ARCHITECTURE)"
# SUBTRACT LINK32 /debug /force

!ELSEIF  "$(CFG)" == "qurydemo - Win32 (ALPHA) axp Release"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir ".\qurydemo"
# PROP BASE Intermediate_Dir ".\qurydemo"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir ".\axp_Rele"
# PROP Intermediate_Dir ".\axp_Rele"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
MTL=midl.exe
# ADD BASE MTL /nologo /D "_DEBUG" /alpha
# ADD MTL /nologo /D "_DEBUG" /mktyplib203 /alpha
CPP=cl.exe
# ADD BASE CPP /nologo /Gt0 /W3 /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /YX /c
# ADD CPP /nologo /MD /Gt0 /W3 /O2 /I "..\..\include" /D "WIN32" /D "_WINDOWS" /YX /FD /c
RSC=rc.exe
# ADD BASE RSC /l 0x409 /d "_DEBUG"
# ADD RSC /l 0x409 /d "_NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib /nologo /subsystem:windows /debug /machine:ALPHA
# ADD LINK32 oledb.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib /nologo /subsystem:windows /machine:ALPHA /libpath:"..\..\LIB\$(PROCESSOR_ARCHITECTURE)"
# SUBTRACT LINK32 /debug

!ELSEIF  "$(CFG)" == "qurydemo - Win32 (ALPHA) axp Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir ".\qurydem0"
# PROP BASE Intermediate_Dir ".\qurydem0"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir ".\axp_Debu"
# PROP Intermediate_Dir ".\axp_Debu"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
MTL=midl.exe
# ADD BASE MTL /nologo /D "_DEBUG" /alpha
# ADD MTL /nologo /D "_DEBUG" /mktyplib203 /alpha
CPP=cl.exe
# ADD BASE CPP /nologo /Gt0 /W3 /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /YX /c
# ADD CPP /nologo /Gt0 /W3 /Zi /Od /I "..\..\include" /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /YX /FD /MDd /c
RSC=rc.exe
# ADD BASE RSC /l 0x409 /d "_DEBUG"
# ADD RSC /l 0x409 /d "_DEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib /nologo /subsystem:windows /debug /machine:ALPHA
# ADD LINK32 oledb.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib /nologo /subsystem:windows /debug /machine:ALPHA /libpath:"..\..\LIB\$(PROCESSOR_ARCHITECTURE)"

!ENDIF 

# Begin Target

# Name "qurydemo - Win32 x86 Debug"
# Name "qurydemo - Win32 x86 Release"
# Name "qurydemo - Win32 (ALPHA) axp Release"
# Name "qurydemo - Win32 (ALPHA) axp Debug"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;hpj;bat;for;f90"
# Begin Source File

SOURCE=.\main.cpp

!IF  "$(CFG)" == "qurydemo - Win32 x86 Debug"

!ELSEIF  "$(CFG)" == "qurydemo - Win32 x86 Release"

!ELSEIF  "$(CFG)" == "qurydemo - Win32 (ALPHA) axp Release"

DEP_CPP_MAIN_=\
	"..\..\include\oledb.h"\
	"..\..\include\oledberr.h"\
	"..\..\include\transact.h"\
	".\qurydemo.h"\
	

!ELSEIF  "$(CFG)" == "qurydemo - Win32 (ALPHA) axp Debug"

DEP_CPP_MAIN_=\
	"..\..\include\oledb.h"\
	"..\..\include\oledberr.h"\
	"..\..\include\transact.h"\
	".\qurydemo.h"\
	

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\query.cpp

!IF  "$(CFG)" == "qurydemo - Win32 x86 Debug"

!ELSEIF  "$(CFG)" == "qurydemo - Win32 x86 Release"

!ELSEIF  "$(CFG)" == "qurydemo - Win32 (ALPHA) axp Release"

DEP_CPP_QUERY=\
	"..\..\include\msdaguid.h"\
	"..\..\include\oledb.h"\
	"..\..\include\oledberr.h"\
	"..\..\include\transact.h"\
	".\qurydemo.h"\
	

!ELSEIF  "$(CFG)" == "qurydemo - Win32 (ALPHA) axp Debug"

DEP_CPP_QUERY=\
	"..\..\include\msdaguid.h"\
	"..\..\include\oledb.h"\
	"..\..\include\oledberr.h"\
	"..\..\include\transact.h"\
	".\qurydemo.h"\
	

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\qurydemo.rc
# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl;fi;fd"
# Begin Source File

SOURCE=.\qurydemo.h
# End Source File
# Begin Source File

SOURCE=.\quryver.h
# End Source File
# End Group
# Begin Group "Resource Files"

# PROP Default_Filter "ico;cur;bmp;dlg;rc2;rct;bin;cnt;rtf;gif;jpg;jpeg;jpe"
# Begin Source File

SOURCE=.\newquery.bmp
# End Source File
# Begin Source File

SOURCE=.\querywdw.ico
# End Source File
# Begin Source File

SOURCE=.\qurydemo.ico
# End Source File
# Begin Source File

SOURCE=.\qurydemo.rc2
# End Source File
# Begin Source File

SOURCE=.\runquery.bmp
# End Source File
# End Group
# End Target
# End Project
