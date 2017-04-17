# Microsoft Developer Studio Project File - Name="DCPC" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Application" 0x0101

CFG=DCPC - Win32 Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "DCPC.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "DCPC.mak" CFG="DCPC - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "DCPC - Win32 Release" (based on "Win32 (x86) Application")
!MESSAGE "DCPC - Win32 Debug" (based on "Win32 (x86) Application")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath "Desktop"
# PROP WCE_FormatVersion ""
CPP=cl.exe
MTL=midl.exe
RSC=rc.exe

!IF  "$(CFG)" == "DCPC - Win32 Release"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "Release"
# PROP BASE Intermediate_Dir "Release"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "..\temp\Release"
# PROP Intermediate_Dir "..\temp\Release"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /YX /FD /c
# ADD CPP /nologo /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /YX /FD /c
# ADD BASE MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x409 /d "NDEBUG"
# ADD RSC /l 0x409 /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /machine:I386
# ADD LINK32 dsound.lib dplayx.lib dinput.lib dxguid.lib ddraw.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /machine:I386 /out:"..\DCPC.exe"

!ELSEIF  "$(CFG)" == "DCPC - Win32 Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "Debug"
# PROP BASE Intermediate_Dir "Debug"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "..\temp\Debug"
# PROP Intermediate_Dir "..\temp\Debug"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /YX /FD /GZ /c
# ADD CPP /nologo /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /YX /FD /GZ /c
# ADD BASE MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x409 /d "_DEBUG"
# ADD RSC /l 0x409 /d "_DEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /debug /machine:I386 /pdbtype:sept
# ADD LINK32 dsound.lib dplayx.lib dinput.lib dxguid.lib ddraw.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /debug /machine:I386 /out:"..\DCPC.exe" /pdbtype:sept

!ENDIF 

# Begin Target

# Name "DCPC - Win32 Release"
# Name "DCPC - Win32 Debug"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
# Begin Group "Entities"

# PROP Default_Filter ""
# Begin Group "Enemy Craft"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\ENBomberSquad.cpp
# End Source File
# Begin Source File

SOURCE=.\ENMFighterSquad.cpp
# End Source File
# Begin Source File

SOURCE=.\ENPowerUpDroneSquad.cpp
# End Source File
# Begin Source File

SOURCE=.\ENSFighterSquad.cpp
# End Source File
# End Group
# Begin Source File

SOURCE=.\ENBase.cpp
# End Source File
# Begin Source File

SOURCE=.\ENBomb.cpp
# End Source File
# Begin Source File

SOURCE=.\ENBuilding.cpp
# End Source File
# Begin Source File

SOURCE=.\ENBullet.cpp
# End Source File
# Begin Source File

SOURCE=.\ENLord.cpp
# End Source File
# Begin Source File

SOURCE=.\ENMissile.cpp
# End Source File
# Begin Source File

SOURCE=.\ENPowerUp.cpp
# End Source File
# Begin Source File

SOURCE=.\ENRocket.cpp
# End Source File
# Begin Source File

SOURCE=.\ENSmartBomb.cpp
# End Source File
# Begin Source File

SOURCE=.\ENTurret.cpp
# End Source File
# Begin Source File

SOURCE=.\ENTurretSwivel.cpp
# End Source File
# End Group
# Begin Source File

SOURCE=.\3DMath.cpp
# End Source File
# Begin Source File

SOURCE=.\Collide.cpp
# End Source File
# Begin Source File

SOURCE=.\Error.cpp
# End Source File
# Begin Source File

SOURCE=.\GACreate.cpp
# End Source File
# Begin Source File

SOURCE=.\GADemoPlayback.cpp
# End Source File
# Begin Source File

SOURCE=.\GADemoRecord.cpp
# End Source File
# Begin Source File

SOURCE=.\GAEntity.cpp
# End Source File
# Begin Source File

SOURCE=.\GAMain.cpp
# End Source File
# Begin Source File

SOURCE=.\GANetwork.cpp
# End Source File
# Begin Source File

SOURCE=.\GASound.cpp
# End Source File
# Begin Source File

SOURCE=.\GAState.cpp
# End Source File
# Begin Source File

SOURCE=.\GATick.cpp
# End Source File
# Begin Source File

SOURCE=.\GAView.cpp
# End Source File
# Begin Source File

SOURCE=.\GRDraw.cpp
# End Source File
# Begin Source File

SOURCE=.\GRMain.cpp
# End Source File
# Begin Source File

SOURCE=.\GRMatrix.cpp
# End Source File
# Begin Source File

SOURCE=.\GRPC.cpp
# End Source File
# Begin Source File

SOURCE=.\GRTex.cpp
# End Source File
# Begin Source File

SOURCE=.\InitPC.cpp
# End Source File
# Begin Source File

SOURCE=.\Input.cpp
# End Source File
# Begin Source File

SOURCE=.\Intro.cpp
# End Source File
# Begin Source File

SOURCE=.\JoyPC.cpp
# End Source File
# Begin Source File

SOURCE=.\Main.cpp
# End Source File
# Begin Source File

SOURCE=.\Mesh.cpp
# End Source File
# Begin Source File

SOURCE=.\MiscPC.cpp
# End Source File
# Begin Source File

SOURCE=.\Network.cpp
# End Source File
# Begin Source File

SOURCE=.\Noise.cpp
# End Source File
# Begin Source File

SOURCE=.\RFishEye.cpp
# End Source File
# Begin Source File

SOURCE=.\RHUD.cpp
# End Source File
# Begin Source File

SOURCE=.\RMain.cpp
# End Source File
# Begin Source File

SOURCE=.\RMesh.cpp
# End Source File
# Begin Source File

SOURCE=.\RParticle.cpp
# End Source File
# Begin Source File

SOURCE=.\RSky.cpp
# End Source File
# Begin Source File

SOURCE=.\RSmoke.cpp
# End Source File
# Begin Source File

SOURCE=.\RSun.cpp
# End Source File
# Begin Source File

SOURCE=.\RTerrain.cpp
# End Source File
# Begin Source File

SOURCE=.\RText.cpp
# End Source File
# Begin Source File

SOURCE=.\RTracer.cpp
# End Source File
# Begin Source File

SOURCE=.\Sound.cpp
# End Source File
# Begin Source File

SOURCE=.\TexRead.cpp
# End Source File
# Begin Source File

SOURCE=.\Timer.cpp
# End Source File
# Begin Source File

SOURCE=.\Util.cpp
# End Source File
# Begin Source File

SOURCE=.\Vis.cpp
# End Source File
# Begin Source File

SOURCE=.\WinMain.cpp
# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl"
# Begin Source File

SOURCE=.\DC.h
# End Source File
# Begin Source File

SOURCE=.\DC3DMath.h
# End Source File
# Begin Source File

SOURCE=.\DCCollide.h
# End Source File
# Begin Source File

SOURCE=.\DCDebug.h
# End Source File
# Begin Source File

SOURCE=.\DCEnergy.h
# End Source File
# Begin Source File

SOURCE=.\DCGame.h
# End Source File
# Begin Source File

SOURCE=.\DCGraphics.h
# End Source File
# Begin Source File

SOURCE=.\DCInput.h
# End Source File
# Begin Source File

SOURCE=.\DCMesh.h
# End Source File
# Begin Source File

SOURCE=.\DCNetwork.h
# End Source File
# Begin Source File

SOURCE=.\DCNoise.h
# End Source File
# Begin Source File

SOURCE=.\DCParticle.h
# End Source File
# Begin Source File

SOURCE=.\DCRender.h
# End Source File
# Begin Source File

SOURCE=.\DCRHUD.h
# End Source File
# Begin Source File

SOURCE=.\DCRText.h
# End Source File
# Begin Source File

SOURCE=.\DCSound.h
# End Source File
# Begin Source File

SOURCE=.\DCTimer.h
# End Source File
# Begin Source File

SOURCE=.\DCVis.h
# End Source File
# Begin Source File

SOURCE=.\DCWorld.h
# End Source File
# Begin Source File

SOURCE=.\TSMesh.h
# End Source File
# End Group
# Begin Group "Resource Files"

# PROP Default_Filter "ico;cur;bmp;dlg;rc2;rct;bin;rgs;gif;jpg;jpeg;jpe"
# Begin Source File

SOURCE=.\PC.rc
# End Source File
# End Group
# End Target
# End Project
