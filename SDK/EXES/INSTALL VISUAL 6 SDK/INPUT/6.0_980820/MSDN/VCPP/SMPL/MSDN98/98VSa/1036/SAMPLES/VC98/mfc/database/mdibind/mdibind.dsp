# Microsoft Developer Studio Project File - Name="MDIBind" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 60000
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Application" 0x0101

CFG=MDIBind - Win32 Release
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "mdibind.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "mdibind.mak" CFG="MDIBind - Win32 Release"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "MDIBind - Win32 Release" (based on "Win32 (x86) Application")
!MESSAGE "MDIBind - Win32 Debug" (based on "Win32 (x86) Application")
!MESSAGE "MDIBind - Win32 Unicode Debug" (based on "Win32 (x86) Application")
!MESSAGE "MDIBind - Win32 Unicode Release" (based on "Win32 (x86) Application")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
CPP=cl.exe
MTL=midl.exe
RSC=rc.exe

!IF  "$(CFG)" == "MDIBind - Win32 Release"

# PROP BASE Use_MFC 5
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir ".\Release"
# PROP BASE Intermediate_Dir ".\Release"
# PROP BASE Target_Dir ""
# PROP Use_MFC 6
# PROP Use_Debug_Libraries 0
# PROP Output_Dir ".\Release"
# PROP Intermediate_Dir ".\Release"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
F90=fl32.exe
# ADD BASE F90 /I "Release/"
# ADD F90 /I "Release/"
# ADD BASE CPP /nologo /MT /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /Yu"stdafx.h" /c
# ADD CPP /nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /Yu"stdafx.h" /FD /c
# ADD BASE MTL /nologo /D "NDEBUG" /win32
# ADD MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x409 /d "NDEBUG"
# ADD RSC /l 0x409 /d "NDEBUG" /d "_AFXDLL"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /machine:I386
# ADD LINK32 odbc32.lib /nologo /subsystem:windows /machine:I386

!ELSEIF  "$(CFG)" == "MDIBind - Win32 Debug"

# PROP BASE Use_MFC 5
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir ".\Debug"
# PROP BASE Intermediate_Dir ".\Debug"
# PROP BASE Target_Dir ""
# PROP Use_MFC 6
# PROP Use_Debug_Libraries 1
# PROP Output_Dir ".\Debug"
# PROP Intermediate_Dir ".\Debug"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
F90=fl32.exe
# ADD BASE F90 /I "Debug/"
# ADD F90 /I "Debug/"
# ADD BASE CPP /nologo /MTd /W3 /Gm /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /Yu"stdafx.h" /c
# ADD CPP /nologo /MDd /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /Yu"stdafx.h" /FD /c
# ADD BASE MTL /nologo /D "_DEBUG" /win32
# ADD MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x409 /d "_DEBUG"
# ADD RSC /l 0x409 /d "_DEBUG" /d "_AFXDLL"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /debug /machine:I386
# ADD LINK32 odbc32.lib /nologo /subsystem:windows /debug /machine:I386

!ELSEIF  "$(CFG)" == "MDIBind - Win32 Unicode Debug"

# PROP BASE Use_MFC 5
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir ".\MDIBind_"
# PROP BASE Intermediate_Dir ".\MDIBind_"
# PROP BASE Target_Dir ""
# PROP Use_MFC 6
# PROP Use_Debug_Libraries 1
# PROP Output_Dir ".\UniDebug"
# PROP Intermediate_Dir ".\UniDebug"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
F90=fl32.exe
# ADD BASE F90 /I "MDIBind_/"
# ADD F90 /I "UniDebug/"
# ADD BASE CPP /nologo /MTd /W3 /Gm /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /Yu"stdafx.h" /c
# ADD CPP /nologo /MDd /W3 /Gm /GX /ZI /Od /D "_DEBUG" /D "WIN32" /D "_WINDOWS" /D "_UNICODE" /D "_AFXDLL" /D "_MBCS" /Yu"stdafx.h" /FD /c
# ADD BASE MTL /nologo /D "_DEBUG" /win32
# ADD MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x409 /d "_DEBUG"
# ADD RSC /l 0x409 /d "_DEBUG" /d "_AFXDLL"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /debug /machine:I386
# ADD LINK32 odbc32.lib /nologo /entry:"wWinMainCRTStartup" /subsystem:windows /debug /machine:I386

!ELSEIF  "$(CFG)" == "MDIBind - Win32 Unicode Release"

# PROP BASE Use_MFC 5
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir ".\MDIBind0"
# PROP BASE Intermediate_Dir ".\MDIBind0"
# PROP BASE Target_Dir ""
# PROP Use_MFC 6
# PROP Use_Debug_Libraries 0
# PROP Output_Dir ".\UniRel"
# PROP Intermediate_Dir ".\UniRel"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
F90=fl32.exe
# ADD BASE F90 /I "MDIBind0/"
# ADD F90 /I "UniRel/"
# ADD BASE CPP /nologo /MT /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /Yu"stdafx.h" /c
# ADD CPP /nologo /MD /W3 /GX /O2 /D "NDEBUG" /D "WIN32" /D "_WINDOWS" /D "_UNICODE" /D "_AFXDLL" /D "_MBCS" /Yu"stdafx.h" /FD /c
# ADD BASE MTL /nologo /D "NDEBUG" /win32
# ADD MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x409 /d "NDEBUG"
# ADD RSC /l 0x409 /d "NDEBUG" /d "_AFXDLL"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /machine:I386
# ADD LINK32 odbc32.lib /nologo /entry:"wWinMainCRTStartup" /subsystem:windows /machine:I386

!ENDIF 

# Begin Target

# Name "MDIBind - Win32 Release"
# Name "MDIBind - Win32 Debug"
# Name "MDIBind - Win32 Unicode Debug"
# Name "MDIBind - Win32 Unicode Release"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;hpj;bat;for;f90"
# Begin Source File

SOURCE=.\DSNDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\gridfrm.cpp
# End Source File
# Begin Source File

SOURCE=.\gridview.cpp
# End Source File
# Begin Source File

SOURCE=.\MainFrm.cpp
# End Source File
# Begin Source File

SOURCE=.\maskfrm.cpp
# End Source File
# Begin Source File

SOURCE=.\maskview.cpp
# End Source File
# Begin Source File

SOURCE=.\MDIBind.cpp
# End Source File
# Begin Source File

SOURCE=.\MDIBind.rc
# End Source File
# Begin Source File

SOURCE=.\MDIDoc.cpp
# End Source File
# Begin Source File

SOURCE=.\msdgrid.cpp
# End Source File
# Begin Source File

SOURCE=.\msmask.cpp
# End Source File
# Begin Source File

SOURCE=.\rdc.cpp
# End Source File
# Begin Source File

SOURCE=.\RDCDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\RDCFrm.cpp
# End Source File
# Begin Source File

SOURCE=.\RDCView.cpp
# End Source File
# Begin Source File

SOURCE=.\rdocol.cpp
# End Source File
# Begin Source File

SOURCE=.\rdocols.cpp
# End Source File
# Begin Source File

SOURCE=.\rdoreslt.cpp
# End Source File
# Begin Source File

SOURCE=.\StdAfx.cpp
# ADD CPP /Yc"stdafx.h"
# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;inl;fi;fd"
# Begin Source File

SOURCE=.\DSNDlg.h
# End Source File
# Begin Source File

SOURCE=.\gridfrm.h
# End Source File
# Begin Source File

SOURCE=.\gridview.h
# End Source File
# Begin Source File

SOURCE=.\MainFrm.h
# End Source File
# Begin Source File

SOURCE=.\maskfrm.h
# End Source File
# Begin Source File

SOURCE=.\maskview.h
# End Source File
# Begin Source File

SOURCE=.\mcsdsc.h
# End Source File
# Begin Source File

SOURCE=.\MDIBind.h
# End Source File
# Begin Source File

SOURCE=.\MDIDoc.h
# End Source File
# Begin Source File

SOURCE=.\msdgrid.h
# End Source File
# Begin Source File

SOURCE=.\msmask.h
# End Source File
# Begin Source File

SOURCE=.\RDCDlg.h
# End Source File
# Begin Source File

SOURCE=.\RDCFrm.h
# End Source File
# Begin Source File

SOURCE=.\RDCView.h
# End Source File
# Begin Source File

SOURCE=.\rdocol.h
# End Source File
# Begin Source File

SOURCE=.\rdocols.h
# End Source File
# Begin Source File

SOURCE=.\rdoreslt.h
# End Source File
# Begin Source File

SOURCE=.\StdAfx.h
# End Source File
# End Group
# Begin Group "Resource Files"

# PROP Default_Filter "ico;cur;bmp;dlg;rc2;rct;cnt;rtf;gif;jpg;jpeg;jpe"
# Begin Source File

SOURCE=.\res\grid.ico
# End Source File
# Begin Source File

SOURCE=.\res\mask.ico
# End Source File
# Begin Source File

SOURCE=.\res\MDIBind.ico
# End Source File
# Begin Source File

SOURCE=.\res\MDIBind.rc2
# End Source File
# Begin Source File

SOURCE=.\res\MDIDoc.ico
# End Source File
# Begin Source File

SOURCE=.\res\Toolbar.bmp
# End Source File
# End Group
# End Target
# End Project
# Section OLE Controls
# 	{00028C00-0000-0000-0000-000000000046}
# 	{C932BA85-4374-101B-A56C-00AA003668DC}
# 	{4F5F826A-8AAF-11CE-A77F-08002B2F4E98}
# End Section
# Section MDIBind : {4F5F826A-8AAF-11CE-A77F-08002B2F4E98}
# 	0:12:rdoColumns.h:C:\mfc42\nonship\MDIBind\rdoColumns.h
# 	0:25:rdoPreparedStatements.cpp:C:\mfc42\nonship\MDIBind\rdoPreparedStatements.cpp
# 	0:8:Font.cpp:C:\mfc42\nonship\MDIBind\Font.cpp
# 	0:13:rdoColumn.cpp:C:\mfc42\nonship\MDIBind\rdoColumn.cpp
# 	0:14:rdoResultset.h:C:\mfc42\nonship\MDIBind\rdoResultset.h
# 	0:6:Font.h:C:\mfc42\nonship\MDIBind\Font.h
# 	0:11:rdoColumn.h:C:\mfc42\nonship\MDIBind\rdoColumn.h
# 	0:15:rdoParameters.h:C:\mfc42\nonship\MDIBind\rdoParameters.h
# 	0:8:McsDsc.h:C:\mfc42\nonship\MDIBind\McsDsc.h
# 	0:10:rdoTable.h:C:\mfc42\nonship\MDIBind\rdoTable.h
# 	0:17:rdoConnection.cpp:C:\mfc42\nonship\MDIBind\rdoConnection.cpp
# 	0:23:rdoPreparedStatements.h:C:\mfc42\nonship\MDIBind\rdoPreparedStatements.h
# 	0:15:rdoConnection.h:C:\mfc42\nonship\MDIBind\rdoConnection.h
# 	0:18:rdoEnvironment.cpp:C:\mfc42\nonship\MDIBind\rdoEnvironment.cpp
# 	0:17:rdoParameters.cpp:C:\mfc42\nonship\MDIBind\rdoParameters.cpp
# 	0:10:McsDsc.cpp:C:\mfc42\nonship\MDIBind\McsDsc.cpp
# 	0:14:rdoColumns.cpp:C:\mfc42\nonship\MDIBind\rdoColumns.cpp
# 	0:14:rdoParameter.h:C:\mfc42\nonship\MDIBind\rdoParameter.h
# 	0:11:rdoTables.h:C:\mfc42\nonship\MDIBind\rdoTables.h
# 	0:12:rdoTable.cpp:C:\mfc42\nonship\MDIBind\rdoTable.cpp
# 	0:18:rdoConnections.cpp:C:\mfc42\nonship\MDIBind\rdoConnections.cpp
# 	0:13:rdoTables.cpp:C:\mfc42\nonship\MDIBind\rdoTables.cpp
# 	0:16:rdoEnvironment.h:C:\mfc42\nonship\MDIBind\rdoEnvironment.h
# 	0:16:rdoConnections.h:C:\mfc42\nonship\MDIBind\rdoConnections.h
# 	0:24:rdoPreparedStatement.cpp:C:\mfc42\nonship\MDIBind\rdoPreparedStatement.cpp
# 	0:16:rdoResultset.cpp:C:\mfc42\nonship\MDIBind\rdoResultset.cpp
# 	0:17:rdoResultsets.cpp:C:\mfc42\nonship\MDIBind\rdoResultsets.cpp
# 	0:22:rdoPreparedStatement.h:C:\mfc42\nonship\MDIBind\rdoPreparedStatement.h
# 	0:16:rdoParameter.cpp:C:\mfc42\nonship\MDIBind\rdoParameter.cpp
# 	0:15:rdoResultsets.h:C:\mfc42\nonship\MDIBind\rdoResultsets.h
# 	2:21:DefaultSinkHeaderFile:mcsdsc.h
# 	2:16:DefaultSinkClass:CMcsDsc
# End Section
# Section MDIBind : {00028C02-0000-0000-0000-000000000046}
# 	2:5:Class:CMsDgridCtrl
# 	2:10:HeaderFile:msdgrid.h
# 	2:8:ImplFile:msdgrid.cpp
# End Section
# Section MDIBind : {B541C03A-63BC-11CE-920C-08002B369A33}
# 	2:5:Class:CrdoColumn
# 	2:10:HeaderFile:rdocol.h
# 	2:8:ImplFile:rdocol.cpp
# End Section
# Section MDIBind : {2E746492-6ED1-11CE-9223-08002B369A33}
# 	2:5:Class:CrdoColumns
# 	2:10:HeaderFile:rdocols.h
# 	2:8:ImplFile:rdocols.cpp
# End Section
# Section MDIBind : {B541C03E-63BC-11CE-920C-08002B369A33}
# 	2:5:Class:CrdoResultset
# 	2:10:HeaderFile:rdoreslt.h
# 	2:8:ImplFile:rdoreslt.cpp
# End Section
# Section MDIBind : {C932BA86-4374-101B-A56C-00AA003668DC}
# 	2:5:Class:CMsmask
# 	2:10:HeaderFile:msmask.h
# 	2:8:ImplFile:msmask.cpp
# End Section
# Section MDIBind : {00028C00-0000-0000-0000-000000000046}
# 	0:9:Picture.h:C:\mfc42\nonship\MDIBind\Picture.h
# 	0:8:Font.cpp:C:\mfc42\nonship\MDIBind\Font.cpp
# 	0:6:Font.h:C:\mfc42\nonship\MDIBind\Font.h
# 	0:11:Picture.cpp:C:\mfc42\nonship\MDIBind\Picture.cpp
# 	0:13:MsDgridCtrl.h:C:\mfc42\nonship\MDIBind\MsDgridCtrl.h
# 	0:15:MsDgridCtrl.cpp:C:\mfc42\nonship\MDIBind\MsDgridCtrl.cpp
# 	2:21:DefaultSinkHeaderFile:msdgrid.h
# 	2:16:DefaultSinkClass:CMsDgridCtrl
# End Section
# Section MDIBind : {4F5F8265-8AAF-11CE-A77F-08002B2F4E98}
# 	2:5:Class:CMcsDsc
# 	2:10:HeaderFile:mcsdsc.h
# 	2:8:ImplFile:mcsdsc.cpp
# End Section
# Section MDIBind : {C932BA85-4374-101B-A56C-00AA003668DC}
# 	0:9:Picture.h:C:\mfc42\nonship\MDIBind\Picture.h
# 	0:8:Font.cpp:C:\mfc42\nonship\MDIBind\Font.cpp
# 	0:6:Font.h:C:\mfc42\nonship\MDIBind\Font.h
# 	0:11:Picture.cpp:C:\mfc42\nonship\MDIBind\Picture.cpp
# 	0:8:Msmask.h:C:\mfc42\nonship\MDIBind\Msmask.h
# 	0:10:Msmask.cpp:C:\mfc42\nonship\MDIBind\Msmask.cpp
# 	2:21:DefaultSinkHeaderFile:msmask.h
# 	2:16:DefaultSinkClass:CMsmask
# End Section
