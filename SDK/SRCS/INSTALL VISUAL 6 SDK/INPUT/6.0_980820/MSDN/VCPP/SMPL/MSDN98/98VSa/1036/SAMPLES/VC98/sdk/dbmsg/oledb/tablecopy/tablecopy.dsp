# Microsoft Developer Studio Project File - Name="TableCopy" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 5.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Application" 0x0101
# TARGTYPE "Win32 (ALPHA) Application" 0x0601

CFG=TableCopy - Win32 x86 Release
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "TableCopy.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "TableCopy.mak" CFG="TableCopy - Win32 x86 Release"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "TableCopy - Win32 x86 Release" (based on "Win32 (x86) Application")
!MESSAGE "TableCopy - Win32 x86 Debug" (based on "Win32 (x86) Application")
!MESSAGE "TableCopy - Win32 (ALPHA) axp Debug" (based on\
 "Win32 (ALPHA) Application")
!MESSAGE "TableCopy - Win32 (ALPHA) axp Release" (based on\
 "Win32 (ALPHA) Application")
!MESSAGE 

# Begin Project
# PROP Scc_ProjName ""$/OLE DB SDK/samples/tablecopy", QJQAAAAA"
# PROP Scc_LocalPath "."

!IF  "$(CFG)" == "TableCopy - Win32 x86 Release"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir ".\TableCop"
# PROP BASE Intermediate_Dir ".\TableCop"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir ".\x86_Rele"
# PROP Intermediate_Dir ".\x86_Rele"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
CPP=cl.exe
# ADD BASE CPP /nologo /W3 /GX /O1 /D "NDEBUG" /FR /YX /c
# ADD CPP /nologo /W3 /O1 /I "..\..\INCLUDE" /D "NDEBUG" /FD /c
# SUBTRACT CPP /WX /Fr /YX
MTL=midl.exe
# ADD BASE MTL /nologo /D "NDEBUG" /win32
# ADD MTL /nologo /D "NDEBUG" /mktyplib203 /win32
RSC=rc.exe
# ADD BASE RSC /l 0x409 /d "NDEBUG"
# ADD RSC /l 0x409 /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 oledb.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /machine:I386
# ADD LINK32 oledb.lib msvcrt.lib kernel32.lib ole32.lib oleaut32.lib user32.lib uuid.lib comctl32.lib /nologo /subsystem:windows /machine:I386 /nodefaultlib /libpath:"..\..\LIB\$(PROCESSOR_ARCHITECTURE)"

!ELSEIF  "$(CFG)" == "TableCopy - Win32 x86 Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir ".\TableCo0"
# PROP BASE Intermediate_Dir ".\TableCo0"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir ".\x86_Debu"
# PROP Intermediate_Dir ".\x86_Debu"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
CPP=cl.exe
# ADD BASE CPP /nologo /W3 /Gm /GX /Zi /Od /D "_DEBUG" /D "FINDLEAKS" /FR /YX /c
# ADD CPP /nologo /W3 /Gm /Gi /Zi /Od /I "..\..\INCLUDE" /D "_DEBUG" /D "FINDLEAKS" /FD /c
# SUBTRACT CPP /WX /Gf /Gy /Fr /YX
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
# ADD BASE LINK32 oledb.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /debug /machine:I386
# ADD LINK32 oledb.lib msvcrt.lib kernel32.lib ole32.lib oleaut32.lib user32.lib uuid.lib comctl32.lib /nologo /subsystem:windows /incremental:no /debug /machine:I386 /nodefaultlib /libpath:"..\..\LIB\$(PROCESSOR_ARCHITECTURE)"

!ELSEIF  "$(CFG)" == "TableCopy - Win32 (ALPHA) axp Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir ".\TableCo1"
# PROP BASE Intermediate_Dir ".\TableCo1"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir ".\axp_Debu"
# PROP Intermediate_Dir ".\axp_Debu"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
MTL=midl.exe
# ADD BASE MTL /nologo /D "_DEBUG" /win32
# ADD MTL /nologo /D "_DEBUG" /mktyplib203 /win32
CPP=cl.exe
# ADD BASE CPP /nologo /Gt0 /W3 /GX /Zi /Od /D "_DEBUG" /D "FINDLEAKS" /FR /YX /c
# ADD CPP /nologo /Gt0 /W3 /Zi /Od /I "..\..\INCLUDE" /D "_DEBUG" /D "FINDLEAKS" /FD /c
# SUBTRACT CPP /WX /Gf /Gy /Fr /YX
RSC=rc.exe
# ADD BASE RSC /l 0x409 /d "_DEBUG"
# ADD RSC /l 0x409 /d "_DEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 oledbd.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /debug /machine:ALPHA
# ADD LINK32 oledb.lib msvcrt.lib kernel32.lib ole32.lib oleaut32.lib user32.lib uuid.lib comctl32.lib /nologo /subsystem:windows /debug /machine:ALPHA /nodefaultlib /libpath:"..\..\LIB\$(PROCESSOR_ARCHITECTURE)"

!ELSEIF  "$(CFG)" == "TableCopy - Win32 (ALPHA) axp Release"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir ".\TableCo2"
# PROP BASE Intermediate_Dir ".\TableCo2"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir ".\axp_Rele"
# PROP Intermediate_Dir ".\axp_Rele"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
MTL=midl.exe
# ADD BASE MTL /nologo /D "NDEBUG" /win32
# ADD MTL /nologo /D "NDEBUG" /mktyplib203 /win32
CPP=cl.exe
# ADD BASE CPP /nologo /Gt0 /W3 /GX /O1 /D "NDEBUG" /FR /YX /c
# ADD CPP /nologo /Gt0 /W3 /O1 /I "..\..\INCLUDE" /D "NDEBUG" /FD /c
# SUBTRACT CPP /WX /Fr /YX
RSC=rc.exe
# ADD BASE RSC /l 0x409 /d "NDEBUG"
# ADD RSC /l 0x409 /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 oledb.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /machine:ALPHA
# ADD LINK32 oledb.lib msvcrt.lib kernel32.lib ole32.lib oleaut32.lib user32.lib uuid.lib comctl32.lib /nologo /subsystem:windows /machine:ALPHA /nodefaultlib /libpath:"..\..\LIB\$(PROCESSOR_ARCHITECTURE)"

!ENDIF 

# Begin Target

# Name "TableCopy - Win32 x86 Release"
# Name "TableCopy - Win32 x86 Debug"
# Name "TableCopy - Win32 (ALPHA) axp Debug"
# Name "TableCopy - Win32 (ALPHA) axp Release"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;hpj;bat;for;f90"
# Begin Source File

SOURCE=.\COMMON.CPP

!IF  "$(CFG)" == "TableCopy - Win32 x86 Release"

!ELSEIF  "$(CFG)" == "TableCopy - Win32 x86 Debug"

!ELSEIF  "$(CFG)" == "TableCopy - Win32 (ALPHA) axp Debug"

DEP_CPP_COMMO=\
	"..\..\include\oledb.h"\
	"..\..\include\oledberr.h"\
	"..\..\include\transact.h"\
	".\COMMON.H"\
	".\DataSource.h"\
	".\Error.h"\
	".\Property.h"\
	".\Table.h"\
	".\TableCopy.h"\
	".\WinMain.h"\
	

!ELSEIF  "$(CFG)" == "TableCopy - Win32 (ALPHA) axp Release"

DEP_CPP_COMMO=\
	"..\..\include\oledb.h"\
	"..\..\include\oledberr.h"\
	"..\..\include\transact.h"\
	".\COMMON.H"\
	".\DataSource.h"\
	".\Error.h"\
	".\Property.h"\
	".\Table.h"\
	".\TableCopy.h"\
	".\WinMain.h"\
	

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\DataSource.cpp

!IF  "$(CFG)" == "TableCopy - Win32 x86 Release"

!ELSEIF  "$(CFG)" == "TableCopy - Win32 x86 Debug"

!ELSEIF  "$(CFG)" == "TableCopy - Win32 (ALPHA) axp Debug"

DEP_CPP_DATAS=\
	"..\..\include\msdaguid.h"\
	"..\..\include\oledb.h"\
	"..\..\include\oledberr.h"\
	"..\..\include\transact.h"\
	".\COMMON.H"\
	".\DataSource.h"\
	".\Error.h"\
	".\Property.h"\
	".\TableCopy.h"\
	".\WinMain.h"\
	

!ELSEIF  "$(CFG)" == "TableCopy - Win32 (ALPHA) axp Release"

DEP_CPP_DATAS=\
	"..\..\include\msdaguid.h"\
	"..\..\include\oledb.h"\
	"..\..\include\oledberr.h"\
	"..\..\include\transact.h"\
	".\COMMON.H"\
	".\DataSource.h"\
	".\Error.h"\
	".\Property.h"\
	".\TableCopy.h"\
	".\WinMain.h"\
	

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\Error.cpp

!IF  "$(CFG)" == "TableCopy - Win32 x86 Release"

!ELSEIF  "$(CFG)" == "TableCopy - Win32 x86 Debug"

!ELSEIF  "$(CFG)" == "TableCopy - Win32 (ALPHA) axp Debug"

DEP_CPP_ERROR=\
	"..\..\include\oledb.h"\
	"..\..\include\oledberr.h"\
	"..\..\include\transact.h"\
	".\COMMON.H"\
	".\Error.h"\
	".\TableCopy.h"\
	".\WinMain.h"\
	

!ELSEIF  "$(CFG)" == "TableCopy - Win32 (ALPHA) axp Release"

DEP_CPP_ERROR=\
	"..\..\include\oledb.h"\
	"..\..\include\oledberr.h"\
	"..\..\include\transact.h"\
	".\COMMON.H"\
	".\Error.h"\
	".\TableCopy.h"\
	".\WinMain.h"\
	

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\PROGRESS.CPP

!IF  "$(CFG)" == "TableCopy - Win32 x86 Release"

!ELSEIF  "$(CFG)" == "TableCopy - Win32 x86 Debug"

!ELSEIF  "$(CFG)" == "TableCopy - Win32 (ALPHA) axp Debug"

DEP_CPP_PROGR=\
	"..\..\include\oledb.h"\
	"..\..\include\oledberr.h"\
	"..\..\include\transact.h"\
	".\COMMON.H"\
	".\DataSource.h"\
	".\Error.h"\
	".\PROGRESS.H"\
	".\Property.h"\
	".\Table.h"\
	".\TableCopy.h"\
	".\WinMain.h"\
	".\Wizard.h"\
	

!ELSEIF  "$(CFG)" == "TableCopy - Win32 (ALPHA) axp Release"

DEP_CPP_PROGR=\
	"..\..\include\oledb.h"\
	"..\..\include\oledberr.h"\
	"..\..\include\transact.h"\
	".\COMMON.H"\
	".\DataSource.h"\
	".\Error.h"\
	".\PROGRESS.H"\
	".\Property.h"\
	".\Table.h"\
	".\TableCopy.h"\
	".\WinMain.h"\
	".\Wizard.h"\
	

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\Property.cpp

!IF  "$(CFG)" == "TableCopy - Win32 x86 Release"

!ELSEIF  "$(CFG)" == "TableCopy - Win32 x86 Debug"

!ELSEIF  "$(CFG)" == "TableCopy - Win32 (ALPHA) axp Debug"

DEP_CPP_PROPE=\
	"..\..\include\oledb.h"\
	"..\..\include\oledberr.h"\
	"..\..\include\transact.h"\
	".\COMMON.H"\
	".\Error.h"\
	".\Property.h"\
	".\TableCopy.h"\
	".\WinMain.h"\
	

!ELSEIF  "$(CFG)" == "TableCopy - Win32 (ALPHA) axp Release"

DEP_CPP_PROPE=\
	"..\..\include\oledb.h"\
	"..\..\include\oledberr.h"\
	"..\..\include\transact.h"\
	".\COMMON.H"\
	".\Error.h"\
	".\Property.h"\
	".\TableCopy.h"\
	".\WinMain.h"\
	

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\Spy.cpp

!IF  "$(CFG)" == "TableCopy - Win32 x86 Release"

!ELSEIF  "$(CFG)" == "TableCopy - Win32 x86 Debug"

!ELSEIF  "$(CFG)" == "TableCopy - Win32 (ALPHA) axp Debug"

DEP_CPP_SPY_C=\
	"..\..\include\oledb.h"\
	"..\..\include\oledberr.h"\
	"..\..\include\transact.h"\
	".\COMMON.H"\
	".\Error.h"\
	".\List.h"\
	".\Spy.h"\
	".\TableCopy.h"\
	".\WinMain.h"\
	

!ELSEIF  "$(CFG)" == "TableCopy - Win32 (ALPHA) axp Release"

DEP_CPP_SPY_C=\
	"..\..\include\oledb.h"\
	"..\..\include\oledberr.h"\
	"..\..\include\transact.h"\
	".\COMMON.H"\
	".\Error.h"\
	".\List.h"\
	".\Spy.h"\
	".\TableCopy.h"\
	".\WinMain.h"\
	

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\STEP1.CPP

!IF  "$(CFG)" == "TableCopy - Win32 x86 Release"

!ELSEIF  "$(CFG)" == "TableCopy - Win32 x86 Debug"

!ELSEIF  "$(CFG)" == "TableCopy - Win32 (ALPHA) axp Debug"

DEP_CPP_STEP1=\
	"..\..\include\oledb.h"\
	"..\..\include\oledberr.h"\
	"..\..\include\transact.h"\
	".\COMMON.H"\
	".\DataSource.h"\
	".\Error.h"\
	".\Property.h"\
	".\Table.h"\
	".\TableCopy.h"\
	".\WinMain.h"\
	".\Wizard.h"\
	

!ELSEIF  "$(CFG)" == "TableCopy - Win32 (ALPHA) axp Release"

DEP_CPP_STEP1=\
	"..\..\include\oledb.h"\
	"..\..\include\oledberr.h"\
	"..\..\include\transact.h"\
	".\COMMON.H"\
	".\DataSource.h"\
	".\Error.h"\
	".\Property.h"\
	".\Table.h"\
	".\TableCopy.h"\
	".\WinMain.h"\
	".\Wizard.h"\
	

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\STEP2.CPP

!IF  "$(CFG)" == "TableCopy - Win32 x86 Release"

!ELSEIF  "$(CFG)" == "TableCopy - Win32 x86 Debug"

!ELSEIF  "$(CFG)" == "TableCopy - Win32 (ALPHA) axp Debug"

DEP_CPP_STEP2=\
	"..\..\include\oledb.h"\
	"..\..\include\oledberr.h"\
	"..\..\include\transact.h"\
	".\COMMON.H"\
	".\DataSource.h"\
	".\Error.h"\
	".\Property.h"\
	".\Table.h"\
	".\TableCopy.h"\
	".\WinMain.h"\
	".\Wizard.h"\
	

!ELSEIF  "$(CFG)" == "TableCopy - Win32 (ALPHA) axp Release"

DEP_CPP_STEP2=\
	"..\..\include\oledb.h"\
	"..\..\include\oledberr.h"\
	"..\..\include\transact.h"\
	".\COMMON.H"\
	".\DataSource.h"\
	".\Error.h"\
	".\Property.h"\
	".\Table.h"\
	".\TableCopy.h"\
	".\WinMain.h"\
	".\Wizard.h"\
	

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\STEP3.CPP

!IF  "$(CFG)" == "TableCopy - Win32 x86 Release"

!ELSEIF  "$(CFG)" == "TableCopy - Win32 x86 Debug"

!ELSEIF  "$(CFG)" == "TableCopy - Win32 (ALPHA) axp Debug"

DEP_CPP_STEP3=\
	"..\..\include\oledb.h"\
	"..\..\include\oledberr.h"\
	"..\..\include\transact.h"\
	".\COMMON.H"\
	".\DataSource.h"\
	".\Error.h"\
	".\Property.h"\
	".\Table.h"\
	".\TableCopy.h"\
	".\WinMain.h"\
	".\Wizard.h"\
	

!ELSEIF  "$(CFG)" == "TableCopy - Win32 (ALPHA) axp Release"

DEP_CPP_STEP3=\
	"..\..\include\oledb.h"\
	"..\..\include\oledberr.h"\
	"..\..\include\transact.h"\
	".\COMMON.H"\
	".\DataSource.h"\
	".\Error.h"\
	".\Property.h"\
	".\Table.h"\
	".\TableCopy.h"\
	".\WinMain.h"\
	".\Wizard.h"\
	

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\STEP4.CPP

!IF  "$(CFG)" == "TableCopy - Win32 x86 Release"

!ELSEIF  "$(CFG)" == "TableCopy - Win32 x86 Debug"

!ELSEIF  "$(CFG)" == "TableCopy - Win32 (ALPHA) axp Debug"

DEP_CPP_STEP4=\
	"..\..\include\oledb.h"\
	"..\..\include\oledberr.h"\
	"..\..\include\transact.h"\
	".\COMMON.H"\
	".\DataSource.h"\
	".\Error.h"\
	".\Property.h"\
	".\Table.h"\
	".\TableCopy.h"\
	".\WinMain.h"\
	".\Wizard.h"\
	

!ELSEIF  "$(CFG)" == "TableCopy - Win32 (ALPHA) axp Release"

DEP_CPP_STEP4=\
	"..\..\include\oledb.h"\
	"..\..\include\oledberr.h"\
	"..\..\include\transact.h"\
	".\COMMON.H"\
	".\DataSource.h"\
	".\Error.h"\
	".\Property.h"\
	".\Table.h"\
	".\TableCopy.h"\
	".\WinMain.h"\
	".\Wizard.h"\
	

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\Table.cpp

!IF  "$(CFG)" == "TableCopy - Win32 x86 Release"

!ELSEIF  "$(CFG)" == "TableCopy - Win32 x86 Debug"

!ELSEIF  "$(CFG)" == "TableCopy - Win32 (ALPHA) axp Debug"

DEP_CPP_TABLE=\
	"..\..\include\oledb.h"\
	"..\..\include\oledberr.h"\
	"..\..\include\transact.h"\
	".\COMMON.H"\
	".\DataSource.h"\
	".\Error.h"\
	".\PROGRESS.H"\
	".\Property.h"\
	".\Table.h"\
	".\TableCopy.h"\
	".\WinMain.h"\
	".\Wizard.h"\
	

!ELSEIF  "$(CFG)" == "TableCopy - Win32 (ALPHA) axp Release"

DEP_CPP_TABLE=\
	"..\..\include\oledb.h"\
	"..\..\include\oledberr.h"\
	"..\..\include\transact.h"\
	".\COMMON.H"\
	".\DataSource.h"\
	".\Error.h"\
	".\PROGRESS.H"\
	".\Property.h"\
	".\Table.h"\
	".\TableCopy.h"\
	".\WinMain.h"\
	".\Wizard.h"\
	

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\TableCopy.cpp

!IF  "$(CFG)" == "TableCopy - Win32 x86 Release"

!ELSEIF  "$(CFG)" == "TableCopy - Win32 x86 Debug"

!ELSEIF  "$(CFG)" == "TableCopy - Win32 (ALPHA) axp Debug"

DEP_CPP_TABLEC=\
	"..\..\include\msdaguid.h"\
	"..\..\include\oledb.h"\
	"..\..\include\oledberr.h"\
	"..\..\include\transact.h"\
	".\COMMON.H"\
	".\DataSource.h"\
	".\Error.h"\
	".\Property.h"\
	".\Table.h"\
	".\TableCopy.h"\
	".\WinMain.h"\
	".\Wizard.h"\
	

!ELSEIF  "$(CFG)" == "TableCopy - Win32 (ALPHA) axp Release"

DEP_CPP_TABLEC=\
	"..\..\include\msdaguid.h"\
	"..\..\include\oledb.h"\
	"..\..\include\oledberr.h"\
	"..\..\include\transact.h"\
	".\COMMON.H"\
	".\DataSource.h"\
	".\Error.h"\
	".\Property.h"\
	".\Table.h"\
	".\TableCopy.h"\
	".\WinMain.h"\
	".\Wizard.h"\
	

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\TableCopy.rc
# End Source File
# Begin Source File

SOURCE=.\WinMain.cpp

!IF  "$(CFG)" == "TableCopy - Win32 x86 Release"

!ELSEIF  "$(CFG)" == "TableCopy - Win32 x86 Debug"

!ELSEIF  "$(CFG)" == "TableCopy - Win32 (ALPHA) axp Debug"

DEP_CPP_WINMA=\
	"..\..\include\oledb.h"\
	"..\..\include\oledberr.h"\
	"..\..\include\transact.h"\
	".\COMMON.H"\
	".\DataSource.h"\
	".\Error.h"\
	".\List.h"\
	".\Property.h"\
	".\Spy.h"\
	".\Table.h"\
	".\TableCopy.h"\
	".\WinMain.h"\
	".\Wizard.h"\
	

!ELSEIF  "$(CFG)" == "TableCopy - Win32 (ALPHA) axp Release"

DEP_CPP_WINMA=\
	"..\..\include\oledb.h"\
	"..\..\include\oledberr.h"\
	"..\..\include\transact.h"\
	".\COMMON.H"\
	".\DataSource.h"\
	".\Error.h"\
	".\List.h"\
	".\Property.h"\
	".\Spy.h"\
	".\Table.h"\
	".\TableCopy.h"\
	".\WinMain.h"\
	".\Wizard.h"\
	

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\Wizard.cpp

!IF  "$(CFG)" == "TableCopy - Win32 x86 Release"

!ELSEIF  "$(CFG)" == "TableCopy - Win32 x86 Debug"

!ELSEIF  "$(CFG)" == "TableCopy - Win32 (ALPHA) axp Debug"

DEP_CPP_WIZAR=\
	"..\..\include\oledb.h"\
	"..\..\include\oledberr.h"\
	"..\..\include\transact.h"\
	".\COMMON.H"\
	".\DataSource.h"\
	".\Error.h"\
	".\PROGRESS.H"\
	".\Property.h"\
	".\Table.h"\
	".\TableCopy.h"\
	".\WinMain.h"\
	".\Wizard.h"\
	

!ELSEIF  "$(CFG)" == "TableCopy - Win32 (ALPHA) axp Release"

DEP_CPP_WIZAR=\
	"..\..\include\oledb.h"\
	"..\..\include\oledberr.h"\
	"..\..\include\transact.h"\
	".\COMMON.H"\
	".\DataSource.h"\
	".\Error.h"\
	".\PROGRESS.H"\
	".\Property.h"\
	".\Table.h"\
	".\TableCopy.h"\
	".\WinMain.h"\
	".\Wizard.h"\
	

!ENDIF 

# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl;fi;fd"
# Begin Source File

SOURCE=.\COMMON.H
# End Source File
# Begin Source File

SOURCE=.\DataSource.h
# End Source File
# Begin Source File

SOURCE=.\Error.h
# End Source File
# Begin Source File

SOURCE=.\List.h
# End Source File
# Begin Source File

SOURCE=.\PROGRESS.H
# End Source File
# Begin Source File

SOURCE=.\Property.h
# End Source File
# Begin Source File

SOURCE=.\Spy.h
# End Source File
# Begin Source File

SOURCE=.\Table.h
# End Source File
# Begin Source File

SOURCE=.\TableCopy.h
# End Source File
# Begin Source File

SOURCE=.\version.h
# End Source File
# Begin Source File

SOURCE=.\WinMain.h
# End Source File
# Begin Source File

SOURCE=.\Wizard.h
# End Source File
# End Group
# Begin Group "Resource Files"

# PROP Default_Filter "ico;cur;bmp;dlg;rc2;rct;bin;cnt;rtf;gif;jpg;jpeg;jpe"
# Begin Source File

SOURCE=.\Catalog.ico
# End Source File
# Begin Source File

SOURCE=.\Column.ico
# End Source File
# Begin Source File

SOURCE=.\columnlong.ico
# End Source File
# Begin Source File

SOURCE=.\columnread.ico
# End Source File
# Begin Source File

SOURCE=.\Index.ico
# End Source File
# Begin Source File

SOURCE=.\PrimaryKey.ico
# End Source File
# Begin Source File

SOURCE=.\Schema.ico
# End Source File
# Begin Source File

SOURCE=.\SelTable.ico
# End Source File
# Begin Source File

SOURCE=.\SelType.ico
# End Source File
# Begin Source File

SOURCE=.\Synonym.ico
# End Source File
# Begin Source File

SOURCE=.\SysTable.ico
# End Source File
# Begin Source File

SOURCE=.\Table.ico
# End Source File
# Begin Source File

SOURCE=.\TABLE_CO.ICO
# End Source File
# Begin Source File

SOURCE=.\TableCopy.rc2
# End Source File
# Begin Source File

SOURCE=.\Type.ico
# End Source File
# Begin Source File

SOURCE=.\View.ico
# End Source File
# End Group
# End Target
# End Project
