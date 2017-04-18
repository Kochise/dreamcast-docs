# Microsoft Developer Studio Project File - Name="DCCE" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (WCE SH4) Application" 0x8601

CFG=DCCE - Win32 (WCE SH4) Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "DCCE.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "DCCE.mak" CFG="DCCE - Win32 (WCE SH4) Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "DCCE - Win32 (WCE SH4) Release" (based on "Win32 (WCE SH4) Application")
!MESSAGE "DCCE - Win32 (WCE SH4) Debug" (based on "Win32 (WCE SH4) Application")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath "Dreamcast"
# PROP WCE_FormatVersion "6.0"
CPP=shcl.exe
MTL=midl.exe
RSC=rc.exe

!IF  "$(CFG)" == "DCCE - Win32 (WCE SH4) Release"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "WCESH4Rel"
# PROP BASE Intermediate_Dir "WCESH4Rel"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "..\..\temp\WCESH4Rel"
# PROP Intermediate_Dir "..\..\temp\WCESH4Rel"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MC /W3 /Zi /Ox /D _WIN32_WCE=$(CEVersion) /D "$(CEConfigName)" /D "NDEBUG" /D "SHx" /D "SH4" /D "_SH4_" /D UNDER_CE=$(CEVersion) /D "UNICODE" /D "_MBCS" /D "_UNICODE" /YX /Qsh4r7 /Qs /Qfast /Qgvp /c
# ADD CPP /nologo /MC /W3 /Ox /D "NDEBUG" /D "DREAMCAST" /D _WIN32_WCE=$(CEVersion) /D "$(CEConfigName)" /D "SHx" /D "SH4" /D "_SH4_" /D UNDER_CE=$(CEVersion) /D "UNICODE" /D "_MBCS" /D "_UNICODE" /YX /Qsh4r7 /Qs /Qfast /Qgvp /c
# ADD BASE RSC /l 0x409 /r /d "SHx" /d "SH4" /d "_SH4_" /d UNDER_CE=$(CEVersion) /d _WIN32_WCE=$(CEVersion) /d "$(CEConfigName)" /d "UNICODE" /d "NDEBUG"
# ADD RSC /l 0x409 /r /d "SHx" /d "SH4" /d "_SH4_" /d UNDER_CE=$(CEVersion) /d _WIN32_WCE=$(CEVersion) /d "$(CEConfigName)" /d "UNICODE" /d "NDEBUG"
# ADD BASE MTL /nologo /D "NDEBUG" /mktyplib203 /o "NUL" /win32
# ADD MTL /nologo /D "NDEBUG" /mktyplib203 /o "NUL" /win32
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 coredll.lib /nologo /machine:SH4 /nodefaultlib:"$(CENoDefaultLib)" /subsystem:$(CESubsystem) /STACK:65536,4096
# ADD LINK32 platutil.lib floatmath.lib dsound.lib dplayx.lib ddraw.lib dinput.lib dxguid.lib /nologo /machine:SH4 /nodefaultlib:"$(CENoDefaultLib)" /out:"..\..\DCCE.exe" /subsystem:$(CESubsystem) /STACK:65536,4096
# SUBTRACT LINK32 /debug

!ELSEIF  "$(CFG)" == "DCCE - Win32 (WCE SH4) Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "WCESH4Dbg"
# PROP BASE Intermediate_Dir "WCESH4Dbg"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "..\..\temp\WCESH4Dbg"
# PROP Intermediate_Dir "..\..\temp\WCESH4Dbg"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MC /W3 /Zi /Od /D _WIN32_WCE=$(CEVersion) /D "$(CEConfigName)" /D "DEBUG" /D "SHx" /D "SH4" /D "_SH4_" /D UNDER_CE=$(CEVersion) /D "UNICODE" /D "_MBCS" /D "_UNICODE" /YX /Qsh4r7 /Qs /Qfast /c
# ADD CPP /nologo /MC /W3 /Zi /Od /D "DEBUG" /D "DREAMCAST" /D _WIN32_WCE=$(CEVersion) /D "$(CEConfigName)" /D "SHx" /D "SH4" /D "_SH4_" /D UNDER_CE=$(CEVersion) /D "UNICODE" /D "_MBCS" /D "_UNICODE" /YX /Qsh4r7 /Qs /Qfast /c
# ADD BASE RSC /l 0x409 /r /d "SHx" /d "SH4" /d "_SH4_" /d UNDER_CE=$(CEVersion) /d _WIN32_WCE=$(CEVersion) /d "$(CEConfigName)" /d "UNICODE" /d "DEBUG"
# ADD RSC /l 0x409 /r /d "SHx" /d "SH4" /d "_SH4_" /d UNDER_CE=$(CEVersion) /d _WIN32_WCE=$(CEVersion) /d "$(CEConfigName)" /d "UNICODE" /d "DEBUG"
# ADD BASE MTL /nologo /D "_DEBUG" /mktyplib203 /o "NUL" /win32
# ADD MTL /nologo /D "_DEBUG" /mktyplib203 /o "NUL" /win32
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 coredll.lib /nologo /debug /machine:SH4 /nodefaultlib:"$(CENoDefaultLib)" /subsystem:$(CESubsystem) /STACK:65536,4096
# ADD LINK32 platutil.lib floatmath.lib dsound.lib dplayx.lib ddraw.lib dinput.lib dxguid.lib /nologo /debug /machine:SH4 /nodefaultlib:"$(CENoDefaultLib)" /out:"..\..\DCCE.exe" /subsystem:$(CESubsystem) /STACK:65536,4096

!ENDIF 

# Begin Target

# Name "DCCE - Win32 (WCE SH4) Release"
# Name "DCCE - Win32 (WCE SH4) Debug"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
# Begin Group "Entities"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\ENBase.cpp
DEP_CPP_ENBAS=\
	"..\DC.h"\
	"..\DC3DMath.h"\
	"..\DCDebug.h"\
	"..\DCEnergy.h"\
	"..\DCGame.h"\
	"..\DCNoise.h"\
	"..\DCTimer.h"\
	{$(INCLUDE)}"FloatMathLib.h"\
	
# End Source File
# Begin Source File

SOURCE=..\ENBomb.cpp
DEP_CPP_ENBOM=\
	"..\DC.h"\
	"..\DC3DMath.h"\
	"..\DCDebug.h"\
	"..\DCEnergy.h"\
	"..\DCGame.h"\
	"..\DCNoise.h"\
	"..\DCSound.h"\
	"..\DCTimer.h"\
	{$(INCLUDE)}"FloatMathLib.h"\
	
# End Source File
# Begin Source File

SOURCE=..\ENBomberSquad.cpp
DEP_CPP_ENBOMB=\
	"..\DC.h"\
	"..\DC3DMath.h"\
	"..\DCCollide.h"\
	"..\DCDebug.h"\
	"..\DCEnergy.h"\
	"..\DCGame.h"\
	"..\DCNoise.h"\
	"..\DCSound.h"\
	"..\DCTimer.h"\
	"..\DCWorld.h"\
	{$(INCLUDE)}"FloatMathLib.h"\
	
# End Source File
# Begin Source File

SOURCE=..\ENBuilding.cpp
DEP_CPP_ENBUI=\
	"..\DC.h"\
	"..\DC3DMath.h"\
	"..\DCCollide.h"\
	"..\DCDebug.h"\
	"..\DCEnergy.h"\
	"..\DCGame.h"\
	"..\DCNoise.h"\
	"..\DCTimer.h"\
	{$(INCLUDE)}"FloatMathLib.h"\
	
# End Source File
# Begin Source File

SOURCE=..\ENBullet.cpp
DEP_CPP_ENBUL=\
	"..\DC.h"\
	"..\DC3DMath.h"\
	"..\DCDebug.h"\
	"..\DCEnergy.h"\
	"..\DCGame.h"\
	"..\DCNoise.h"\
	"..\DCSound.h"\
	"..\DCTimer.h"\
	{$(INCLUDE)}"FloatMathLib.h"\
	
# End Source File
# Begin Source File

SOURCE=..\ENLord.cpp
DEP_CPP_ENLOR=\
	"..\DC.h"\
	"..\DC3DMath.h"\
	"..\DCDebug.h"\
	"..\DCGame.h"\
	"..\DCNoise.h"\
	"..\DCTimer.h"\
	"..\DCWorld.h"\
	{$(INCLUDE)}"FloatMathLib.h"\
	
# End Source File
# Begin Source File

SOURCE=..\ENMFighterSquad.cpp
DEP_CPP_ENMFI=\
	"..\DC.h"\
	"..\DC3DMath.h"\
	"..\DCCollide.h"\
	"..\DCDebug.h"\
	"..\DCEnergy.h"\
	"..\DCGame.h"\
	"..\DCNoise.h"\
	"..\DCSound.h"\
	"..\DCTimer.h"\
	"..\DCWorld.h"\
	{$(INCLUDE)}"FloatMathLib.h"\
	
# End Source File
# Begin Source File

SOURCE=..\ENMissile.cpp
DEP_CPP_ENMIS=\
	"..\DC.h"\
	"..\DC3DMath.h"\
	"..\DCDebug.h"\
	"..\DCEnergy.h"\
	"..\DCGame.h"\
	"..\DCNoise.h"\
	"..\DCParticle.h"\
	"..\DCSound.h"\
	"..\DCTimer.h"\
	"..\DCWorld.h"\
	{$(INCLUDE)}"FloatMathLib.h"\
	
# End Source File
# Begin Source File

SOURCE=..\ENPowerUp.cpp
DEP_CPP_ENPOW=\
	"..\DC.h"\
	"..\DC3DMath.h"\
	"..\DCDebug.h"\
	"..\DCGame.h"\
	"..\DCNoise.h"\
	"..\DCSound.h"\
	"..\DCTimer.h"\
	{$(INCLUDE)}"FloatMathLib.h"\
	
# End Source File
# Begin Source File

SOURCE=..\ENPowerUpDroneSquad.cpp
DEP_CPP_ENPOWE=\
	"..\DC.h"\
	"..\DC3DMath.h"\
	"..\DCCollide.h"\
	"..\DCDebug.h"\
	"..\DCEnergy.h"\
	"..\DCGame.h"\
	"..\DCNoise.h"\
	"..\DCSound.h"\
	"..\DCTimer.h"\
	"..\DCWorld.h"\
	{$(INCLUDE)}"FloatMathLib.h"\
	
# End Source File
# Begin Source File

SOURCE=..\ENRocket.cpp
DEP_CPP_ENROC=\
	"..\DC.h"\
	"..\DC3DMath.h"\
	"..\DCDebug.h"\
	"..\DCEnergy.h"\
	"..\DCGame.h"\
	"..\DCNoise.h"\
	"..\DCParticle.h"\
	"..\DCSound.h"\
	"..\DCTimer.h"\
	{$(INCLUDE)}"FloatMathLib.h"\
	
# End Source File
# Begin Source File

SOURCE=..\ENSFighterSquad.cpp
DEP_CPP_ENSFI=\
	"..\DC.h"\
	"..\DC3DMath.h"\
	"..\DCCollide.h"\
	"..\DCDebug.h"\
	"..\DCEnergy.h"\
	"..\DCGame.h"\
	"..\DCNoise.h"\
	"..\DCSound.h"\
	"..\DCTimer.h"\
	"..\DCWorld.h"\
	{$(INCLUDE)}"FloatMathLib.h"\
	
# End Source File
# Begin Source File

SOURCE=..\ENSmartBomb.cpp
DEP_CPP_ENSMA=\
	"..\DC.h"\
	"..\DC3DMath.h"\
	"..\DCDebug.h"\
	"..\DCGame.h"\
	"..\DCNoise.h"\
	"..\DCSound.h"\
	"..\DCTimer.h"\
	{$(INCLUDE)}"FloatMathLib.h"\
	
# End Source File
# Begin Source File

SOURCE=..\ENTurret.cpp
DEP_CPP_ENTUR=\
	"..\DC.h"\
	"..\DC3DMath.h"\
	"..\DCDebug.h"\
	"..\DCEnergy.h"\
	"..\DCGame.h"\
	"..\DCNoise.h"\
	"..\DCRHUD.h"\
	"..\DCSound.h"\
	"..\DCTimer.h"\
	"..\DCWorld.h"\
	{$(INCLUDE)}"FloatMathLib.h"\
	
# End Source File
# Begin Source File

SOURCE=..\ENTurretSwivel.cpp
DEP_CPP_ENTURR=\
	"..\DC.h"\
	"..\DC3DMath.h"\
	"..\DCDebug.h"\
	"..\DCGame.h"\
	"..\DCNoise.h"\
	"..\DCTimer.h"\
	{$(INCLUDE)}"FloatMathLib.h"\
	
# End Source File
# End Group
# Begin Source File

SOURCE=..\3DMath.cpp
DEP_CPP_3DMAT=\
	"..\DC.h"\
	"..\DC3DMath.h"\
	"..\DCDebug.h"\
	"..\DCNoise.h"\
	"..\DCTimer.h"\
	{$(INCLUDE)}"FloatMathLib.h"\
	
# End Source File
# Begin Source File

SOURCE=..\CControllerCE.cpp
DEP_CPP_CCONT=\
	"..\CControllerCE.h"\
	"..\DC.h"\
	"..\DC3DMath.h"\
	"..\DCDebug.h"\
	"..\DCNoise.h"\
	"..\DCTimer.h"\
	{$(INCLUDE)}"FloatMathLib.h"\
	{$(INCLUDE)}"maplusag.h"\
	
# End Source File
# Begin Source File

SOURCE=..\Collide.cpp
DEP_CPP_COLLI=\
	"..\DC.h"\
	"..\DC3DMath.h"\
	"..\DCCollide.h"\
	"..\DCDebug.h"\
	"..\DCGame.h"\
	"..\DCNoise.h"\
	"..\DCTimer.h"\
	"..\DCWorld.h"\
	{$(INCLUDE)}"FloatMathLib.h"\
	
# End Source File
# Begin Source File

SOURCE=..\Error.cpp
DEP_CPP_ERROR=\
	"..\DC.h"\
	"..\DC3DMath.h"\
	"..\DCDebug.h"\
	"..\DCNoise.h"\
	"..\DCTimer.h"\
	{$(INCLUDE)}"FloatMathLib.h"\
	
# End Source File
# Begin Source File

SOURCE=..\GACreate.cpp
DEP_CPP_GACRE=\
	"..\DC.h"\
	"..\DC3DMath.h"\
	"..\DCDebug.h"\
	"..\DCGame.h"\
	"..\DCMesh.h"\
	"..\DCNetwork.h"\
	"..\DCNoise.h"\
	"..\DCParticle.h"\
	"..\DCTimer.h"\
	"..\TSMesh.h"\
	{$(INCLUDE)}"FloatMathLib.h"\
	
# End Source File
# Begin Source File

SOURCE=..\GADemoPlayback.cpp
DEP_CPP_GADEM=\
	"..\DC.h"\
	"..\DC3DMath.h"\
	"..\DCDebug.h"\
	"..\DCGame.h"\
	"..\DCNoise.h"\
	"..\DCTimer.h"\
	{$(INCLUDE)}"FloatMathLib.h"\
	
# End Source File
# Begin Source File

SOURCE=..\GADemoRecord.cpp
DEP_CPP_GADEMO=\
	"..\DC.h"\
	"..\DC3DMath.h"\
	"..\DCDebug.h"\
	"..\DCGame.h"\
	"..\DCNoise.h"\
	"..\DCTimer.h"\
	{$(INCLUDE)}"FloatMathLib.h"\
	
# End Source File
# Begin Source File

SOURCE=..\GAEntity.cpp
DEP_CPP_GAENT=\
	"..\DC.h"\
	"..\DC3DMath.h"\
	"..\DCDebug.h"\
	"..\DCGame.h"\
	"..\DCNoise.h"\
	"..\DCTimer.h"\
	{$(INCLUDE)}"FloatMathLib.h"\
	
# End Source File
# Begin Source File

SOURCE=..\GAMain.cpp
DEP_CPP_GAMAI=\
	"..\DC.h"\
	"..\DC3DMath.h"\
	"..\DCDebug.h"\
	"..\DCGame.h"\
	"..\DCNetwork.h"\
	"..\DCNoise.h"\
	"..\DCTimer.h"\
	{$(INCLUDE)}"FloatMathLib.h"\
	
# End Source File
# Begin Source File

SOURCE=..\GANetwork.cpp
DEP_CPP_GANET=\
	"..\DC.h"\
	"..\DC3DMath.h"\
	"..\DCDebug.h"\
	"..\DCGame.h"\
	"..\DCNetwork.h"\
	"..\DCNoise.h"\
	"..\DCSound.h"\
	"..\DCTimer.h"\
	{$(INCLUDE)}"FloatMathLib.h"\
	
# End Source File
# Begin Source File

SOURCE=..\GASound.cpp
DEP_CPP_GASOU=\
	"..\DC.h"\
	"..\DC3DMath.h"\
	"..\DCDebug.h"\
	"..\DCGame.h"\
	"..\DCNoise.h"\
	"..\DCSound.h"\
	"..\DCTimer.h"\
	{$(INCLUDE)}"FloatMathLib.h"\
	
# End Source File
# Begin Source File

SOURCE=..\GAState.cpp
DEP_CPP_GASTA=\
	"..\DC.h"\
	"..\DC3DMath.h"\
	"..\DCDebug.h"\
	"..\DCGame.h"\
	"..\DCNoise.h"\
	"..\DCTimer.h"\
	{$(INCLUDE)}"FloatMathLib.h"\
	
# End Source File
# Begin Source File

SOURCE=..\GATick.cpp
DEP_CPP_GATIC=\
	"..\DC.h"\
	"..\DC3DMath.h"\
	"..\DCCollide.h"\
	"..\DCDebug.h"\
	"..\DCEnergy.h"\
	"..\DCGame.h"\
	"..\DCNetwork.h"\
	"..\DCNoise.h"\
	"..\DCTimer.h"\
	{$(INCLUDE)}"FloatMathLib.h"\
	
# End Source File
# Begin Source File

SOURCE=..\GAView.cpp
DEP_CPP_GAVIE=\
	"..\DC.h"\
	"..\DC3DMath.h"\
	"..\DCCollide.h"\
	"..\DCDebug.h"\
	"..\DCGame.h"\
	"..\DCNoise.h"\
	"..\DCTimer.h"\
	{$(INCLUDE)}"FloatMathLib.h"\
	
# End Source File
# Begin Source File

SOURCE=..\GRCE.cpp
DEP_CPP_GRCE_=\
	"..\DC.h"\
	"..\DC3DMath.h"\
	"..\DCDebug.h"\
	"..\DCGraphics.h"\
	"..\DCInput.h"\
	"..\DCNoise.h"\
	"..\DCTimer.h"\
	{$(INCLUDE)}"FloatMathLib.h"\
	{$(INCLUDE)}"netinfo.h"\
	{$(INCLUDE)}"PlatUtil.h"\
	
# End Source File
# Begin Source File

SOURCE=..\GRDraw.cpp
DEP_CPP_GRDRA=\
	"..\DC.h"\
	"..\DC3DMath.h"\
	"..\DCDebug.h"\
	"..\DCGraphics.h"\
	"..\DCNoise.h"\
	"..\DCTimer.h"\
	{$(INCLUDE)}"FloatMathLib.h"\
	
# End Source File
# Begin Source File

SOURCE=..\GRMain.cpp
DEP_CPP_GRMAI=\
	"..\DC.h"\
	"..\DC3DMath.h"\
	"..\DCDebug.h"\
	"..\DCGraphics.h"\
	"..\DCNoise.h"\
	"..\DCTimer.h"\
	{$(INCLUDE)}"FloatMathLib.h"\
	
# End Source File
# Begin Source File

SOURCE=..\GRMatrix.cpp
DEP_CPP_GRMAT=\
	"..\DC.h"\
	"..\DC3DMath.h"\
	"..\DCDebug.h"\
	"..\DCGraphics.h"\
	"..\DCNoise.h"\
	"..\DCTimer.h"\
	{$(INCLUDE)}"FloatMathLib.h"\
	
# End Source File
# Begin Source File

SOURCE=..\GRTex.cpp
DEP_CPP_GRTEX=\
	"..\DC.h"\
	"..\DC3DMath.h"\
	"..\DCDebug.h"\
	"..\DCGraphics.h"\
	"..\DCNoise.h"\
	"..\DCTimer.h"\
	{$(INCLUDE)}"FloatMathLib.h"\
	
# End Source File
# Begin Source File

SOURCE=..\InitCE.cpp
DEP_CPP_INITC=\
	"..\DC.h"\
	"..\DC3DMath.h"\
	"..\DCDebug.h"\
	"..\DCGraphics.h"\
	"..\DCInput.h"\
	"..\DCNetwork.h"\
	"..\DCNoise.h"\
	"..\DCSound.h"\
	"..\DCTimer.h"\
	{$(INCLUDE)}"FloatMathLib.h"\
	
# End Source File
# Begin Source File

SOURCE=..\Input.cpp
DEP_CPP_INPUT=\
	"..\DC.h"\
	"..\DC3DMath.h"\
	"..\DCDebug.h"\
	"..\DCGame.h"\
	"..\DCGraphics.h"\
	"..\DCInput.h"\
	"..\DCNoise.h"\
	"..\DCTimer.h"\
	{$(INCLUDE)}"FloatMathLib.h"\
	
# End Source File
# Begin Source File

SOURCE=..\Intro.cpp
DEP_CPP_INTRO=\
	"..\DC.h"\
	"..\DC3DMath.h"\
	"..\DCDebug.h"\
	"..\DCGraphics.h"\
	"..\DCNoise.h"\
	"..\DCTimer.h"\
	{$(INCLUDE)}"FloatMathLib.h"\
	
# End Source File
# Begin Source File

SOURCE=..\JoyCE.cpp
DEP_CPP_JOYCE=\
	"..\CControllerCE.h"\
	"..\DC.h"\
	"..\DC3DMath.h"\
	"..\DCDebug.h"\
	"..\DCGame.h"\
	"..\DCInput.h"\
	"..\DCNoise.h"\
	"..\DCTimer.h"\
	{$(INCLUDE)}"FloatMathLib.h"\
	{$(INCLUDE)}"maplusag.h"\
	
# End Source File
# Begin Source File

SOURCE=..\Main.cpp
DEP_CPP_MAIN_=\
	"..\DC.h"\
	"..\DC3DMath.h"\
	"..\DCDebug.h"\
	"..\DCNoise.h"\
	"..\DCTimer.h"\
	{$(INCLUDE)}"FloatMathLib.h"\
	
# End Source File
# Begin Source File

SOURCE=..\Mesh.cpp
DEP_CPP_MESH_=\
	"..\DC.h"\
	"..\DC3DMath.h"\
	"..\DCDebug.h"\
	"..\DCGraphics.h"\
	"..\DCMesh.h"\
	"..\DCNoise.h"\
	"..\DCTimer.h"\
	"..\TSMesh.h"\
	{$(INCLUDE)}"FloatMathLib.h"\
	
# End Source File
# Begin Source File

SOURCE=..\MiscCE.cpp
DEP_CPP_MISCC=\
	"..\DC.h"\
	"..\DC3DMath.h"\
	"..\DCDebug.h"\
	"..\DCNoise.h"\
	"..\DCTimer.h"\
	{$(INCLUDE)}"FloatMathLib.h"\
	
# End Source File
# Begin Source File

SOURCE=..\Network.cpp
DEP_CPP_NETWO=\
	"..\DC.h"\
	"..\DC3DMath.h"\
	"..\DCDebug.h"\
	"..\DCNetwork.h"\
	"..\DCNoise.h"\
	"..\DCTimer.h"\
	{$(INCLUDE)}"FloatMathLib.h"\
	
# End Source File
# Begin Source File

SOURCE=..\Noise.cpp
DEP_CPP_NOISE=\
	"..\DC.h"\
	"..\DC3DMath.h"\
	"..\DCDebug.h"\
	"..\DCNoise.h"\
	"..\DCTimer.h"\
	{$(INCLUDE)}"FloatMathLib.h"\
	
# End Source File
# Begin Source File

SOURCE=..\RFishEye.cpp
DEP_CPP_RFISH=\
	"..\DC.h"\
	"..\DC3DMath.h"\
	"..\DCDebug.h"\
	"..\DCGraphics.h"\
	"..\DCNoise.h"\
	"..\DCRender.h"\
	"..\DCTimer.h"\
	"..\DCWorld.h"\
	{$(INCLUDE)}"FloatMathLib.h"\
	
# End Source File
# Begin Source File

SOURCE=..\RHUD.cpp
DEP_CPP_RHUD_=\
	"..\DC.h"\
	"..\DC3DMath.h"\
	"..\DCDebug.h"\
	"..\DCGame.h"\
	"..\DCGraphics.h"\
	"..\DCNetwork.h"\
	"..\DCNoise.h"\
	"..\DCRender.h"\
	"..\DCRHUD.h"\
	"..\DCRText.h"\
	"..\DCTimer.h"\
	"..\DCWorld.h"\
	{$(INCLUDE)}"FloatMathLib.h"\
	
# End Source File
# Begin Source File

SOURCE=..\RMain.cpp
DEP_CPP_RMAIN=\
	"..\DC.h"\
	"..\DC3DMath.h"\
	"..\DCDebug.h"\
	"..\DCGame.h"\
	"..\DCGraphics.h"\
	"..\DCNoise.h"\
	"..\DCRender.h"\
	"..\DCTimer.h"\
	"..\DCVis.h"\
	"..\DCWorld.h"\
	{$(INCLUDE)}"FloatMathLib.h"\
	
# End Source File
# Begin Source File

SOURCE=..\RMesh.cpp
DEP_CPP_RMESH=\
	"..\DC.h"\
	"..\DC3DMath.h"\
	"..\DCDebug.h"\
	"..\DCGame.h"\
	"..\DCGraphics.h"\
	"..\DCMesh.h"\
	"..\DCNoise.h"\
	"..\DCRender.h"\
	"..\DCTimer.h"\
	"..\DCVis.h"\
	"..\DCWorld.h"\
	"..\TSMesh.h"\
	{$(INCLUDE)}"FloatMathLib.h"\
	
# End Source File
# Begin Source File

SOURCE=..\RParticle.cpp
DEP_CPP_RPART=\
	"..\DC.h"\
	"..\DC3DMath.h"\
	"..\DCDebug.h"\
	"..\DCGraphics.h"\
	"..\DCNoise.h"\
	"..\DCParticle.h"\
	"..\DCRender.h"\
	"..\DCTimer.h"\
	{$(INCLUDE)}"FloatMathLib.h"\
	
# End Source File
# Begin Source File

SOURCE=..\RSky.cpp
DEP_CPP_RSKY_=\
	"..\DC.h"\
	"..\DC3DMath.h"\
	"..\DCDebug.h"\
	"..\DCGraphics.h"\
	"..\DCNoise.h"\
	"..\DCRender.h"\
	"..\DCTimer.h"\
	"..\DCWorld.h"\
	{$(INCLUDE)}"FloatMathLib.h"\
	
# End Source File
# Begin Source File

SOURCE=..\RSmoke.cpp
DEP_CPP_RSMOK=\
	"..\DC.h"\
	"..\DC3DMath.h"\
	"..\DCDebug.h"\
	"..\DCGraphics.h"\
	"..\DCNoise.h"\
	"..\DCTimer.h"\
	{$(INCLUDE)}"FloatMathLib.h"\
	
# End Source File
# Begin Source File

SOURCE=..\RSun.cpp
DEP_CPP_RSUN_=\
	"..\DC.h"\
	"..\DC3DMath.h"\
	"..\DCDebug.h"\
	"..\DCGraphics.h"\
	"..\DCNoise.h"\
	"..\DCRender.h"\
	"..\DCTimer.h"\
	"..\DCWorld.h"\
	{$(INCLUDE)}"FloatMathLib.h"\
	
# End Source File
# Begin Source File

SOURCE=..\RTerrain.cpp
DEP_CPP_RTERR=\
	"..\DC.h"\
	"..\DC3DMath.h"\
	"..\DCDebug.h"\
	"..\DCGraphics.h"\
	"..\DCNoise.h"\
	"..\DCRender.h"\
	"..\DCTimer.h"\
	"..\DCVis.h"\
	"..\DCWorld.h"\
	{$(INCLUDE)}"FloatMathLib.h"\
	
# End Source File
# Begin Source File

SOURCE=..\RText.cpp
DEP_CPP_RTEXT=\
	"..\DC.h"\
	"..\DC3DMath.h"\
	"..\DCDebug.h"\
	"..\DCGraphics.h"\
	"..\DCNoise.h"\
	"..\DCRText.h"\
	"..\DCTimer.h"\
	"..\DCWorld.h"\
	{$(INCLUDE)}"FloatMathLib.h"\
	
# End Source File
# Begin Source File

SOURCE=..\RTracer.cpp
DEP_CPP_RTRAC=\
	"..\DC.h"\
	"..\DC3DMath.h"\
	"..\DCDebug.h"\
	"..\DCGraphics.h"\
	"..\DCMesh.h"\
	"..\DCNoise.h"\
	"..\DCRender.h"\
	"..\DCTimer.h"\
	"..\DCVis.h"\
	"..\TSMesh.h"\
	{$(INCLUDE)}"FloatMathLib.h"\
	
# End Source File
# Begin Source File

SOURCE=..\Sound.cpp
DEP_CPP_SOUND=\
	"..\DC.h"\
	"..\DC3DMath.h"\
	"..\DCDebug.h"\
	"..\DCNoise.h"\
	"..\DCSound.h"\
	"..\DCTimer.h"\
	{$(INCLUDE)}"FloatMathLib.h"\
	
# End Source File
# Begin Source File

SOURCE=..\TexRead.cpp
DEP_CPP_TEXRE=\
	"..\DC.h"\
	"..\DC3DMath.h"\
	"..\DCDebug.h"\
	"..\DCGraphics.h"\
	"..\DCNoise.h"\
	"..\DCTimer.h"\
	{$(INCLUDE)}"FloatMathLib.h"\
	
# End Source File
# Begin Source File

SOURCE=..\Timer.cpp
DEP_CPP_TIMER=\
	"..\DC.h"\
	"..\DC3DMath.h"\
	"..\DCDebug.h"\
	"..\DCNoise.h"\
	"..\DCTimer.h"\
	{$(INCLUDE)}"FloatMathLib.h"\
	
# End Source File
# Begin Source File

SOURCE=..\Util.cpp
DEP_CPP_UTIL_=\
	"..\DC.h"\
	"..\DC3DMath.h"\
	"..\DCDebug.h"\
	"..\DCNoise.h"\
	"..\DCTimer.h"\
	{$(INCLUDE)}"FloatMathLib.h"\
	
# End Source File
# Begin Source File

SOURCE=..\Vis.cpp
DEP_CPP_VIS_C=\
	"..\DC.h"\
	"..\DC3DMath.h"\
	"..\DCDebug.h"\
	"..\DCNoise.h"\
	"..\DCTimer.h"\
	"..\DCVis.h"\
	{$(INCLUDE)}"FloatMathLib.h"\
	
# End Source File
# Begin Source File

SOURCE=..\WinMain.cpp
DEP_CPP_WINMA=\
	"..\DC.h"\
	"..\DC3DMath.h"\
	"..\DCDebug.h"\
	"..\DCNoise.h"\
	"..\DCTimer.h"\
	{$(INCLUDE)}"FloatMathLib.h"\
	
# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl"
# Begin Source File

SOURCE=..\CControllerCE.h
# End Source File
# Begin Source File

SOURCE=..\DC.h
# End Source File
# Begin Source File

SOURCE=..\DC3DMath.h
# End Source File
# Begin Source File

SOURCE=..\DCCollide.h
# End Source File
# Begin Source File

SOURCE=..\DCDebug.h
# End Source File
# Begin Source File

SOURCE=..\DCGame.h
# End Source File
# Begin Source File

SOURCE=..\DCGraphics.h
# End Source File
# Begin Source File

SOURCE=..\DCInput.h
# End Source File
# Begin Source File

SOURCE=..\DCNetwork.h
# End Source File
# Begin Source File

SOURCE=..\DCNoise.h
# End Source File
# Begin Source File

SOURCE=..\DCParticle.h
# End Source File
# Begin Source File

SOURCE=..\DCRender.h
# End Source File
# Begin Source File

SOURCE=..\DCRText.h
# End Source File
# Begin Source File

SOURCE=..\DCSound.h
# End Source File
# Begin Source File

SOURCE=..\DCTimer.h
# End Source File
# Begin Source File

SOURCE=..\DCVis.h
# End Source File
# Begin Source File

SOURCE=..\DCWorld.h
# End Source File
# Begin Source File

SOURCE=..\TSMesh.h
# End Source File
# End Group
# Begin Group "Resource Files"

# PROP Default_Filter "ico;cur;bmp;dlg;rc2;rct;bin;rgs;gif;jpg;jpeg;jpe"
# Begin Source File

SOURCE=.\CE.rc
# End Source File
# End Group
# End Target
# End Project
