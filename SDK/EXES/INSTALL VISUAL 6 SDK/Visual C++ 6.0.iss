; TYPE    DU SCRIPT : MICROSOFT VISUAL
; AUTEUR  DU SCRIPT : Kochise
; VERSION DU SCRIPT : 2008/06/03

; Installation 'perso' de Visual C++ 6 orienté vers le
; développement DreamCast (profil par défaut). Inclus un
; Wizard pour la compilation croisée SH4 mais il n'est pas
; vraiment stable. Je conseille plutôt d'utiliser dans ce
; cas le fichier PLATFORM.ZIP avec DevCpp 4.9.9.2 !
; Une fois installé Visual C++ 6 il faut aussi installer
; Dragon SDK (toujours sur le DVD) pour le développement
; sous Windows CE pour DreamCast.
; Vous pouvez aussi choisir d'installer Visual C++ 6 pour
; le developpement Win32 avec le dernier Service Pack (SP6)
; mais dans ce cas là Dragon SDK ne fonctionnera pas ! Je
; laisse néanmoins le script ouvert pour celui qui connait
; la manipulation pour faire fonctionner les deux environnements
; en parallèle.

; === DEFINE VISUAL ====================================================================================================
; Bon, principalement les chemins des fichiers sources

; - - 8< - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

; JUST EDIT THIS PLACE FROM ONE SDK REVISION TO ANOTHER

#define SETUP_VERSION  "2.8.6.3"

#define VISUAL_FIRM    "Microsoft"
#define VISUAL_NAME    "Visual Studio"
#define VISUAL_SHORT   "Visual"
#define VISUAL_TYPE    "C++"
#define VISUAL_VER     "6"
#define VISUAL_REV     "0"
#define VISUAL_DATE    "980820"
#define VISUAL_URL     "http://www.microsoft.com/"
;#define VISUAL_DEBUG
#define VISUAL_MSDN

#define INSTALL_WNDTABS
#define INSTALL_KALLISTIOS

; - - 8< - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

#define VISUAL_INSTALL "."
#define VISUAL_FILES   VISUAL_INSTALL+"\INPUT\"+VISUAL_VER+"."+VISUAL_REV+"_"+VISUAL_DATE
#define VISUAL_TOOLS   VISUAL_INSTALL+"\TOOLS"
#define VISUAL_SPLASH  VISUAL_TOOLS+"\Splash"
#define VISUAL_TEXT    VISUAL_TOOLS+"\Text"

#if VER < 0x05000000
  #define USE_MODIFYREPAIRDELETE
#endif

[Setup]
; Je met tout (et dans l'ordre de la doc), comme ça c'est plus simple pour savoir ce qui est fait ou non
; En commentaire, les parametres dont la valeur est par défaut
;; En double commentaire, les parametres dont la valeur n'a pas de raison d'être définie
;;; En triple commentaire, les parametres obsolètes

// Page 51=
;;;Bits=32
UseSetupLdr=no
;BackColor=clBlue
;BackColor2=clBlack
;BackColorDirection=toptobottom
;BackSolid=no
// 52=
AppName={#VISUAL_NAME}
AppVerName={#VISUAL_NAME} {#VISUAL_VER}.{#VISUAL_REV}
AppId={#VISUAL_NAME}
// 53=
;;AppMutex=
AppCopyright=Copyright (c) {#VISUAL_FIRM} 1998-2004
AppComments=No support at all
AppContact=support@microsoft.com
AppPublisher={#VISUAL_FIRM}
AppPublisherURL={#VISUAL_URL}
AppSupportURL={#VISUAL_URL}
AppUpdatesURL={#VISUAL_URL}
AppVersion={#VISUAL_VER}.{#VISUAL_REV}
// Page 54=
DefaultDirName={reg:HKLM\SOFTWARE\{#VISUAL_FIRM}\{#VISUAL_NAME},Path|{pf}\{#VISUAL_FIRM} {#VISUAL_NAME}}
;Uninstallable=yes
;MinVersion=4,4
;OnlyBelowVersion=0,0
// Page 55=
;;;AdminPrivilegesRequired=yes
PrivilegesRequired=admin
;;;DisableAppendDir=no
;EnableDirDoesntExistWarning=no
;;;AlwaysCreateUninstallIcon
;ExtraDiskSpaceRequired=0
// Page 56=
;Compression=lzma
;SolidCompression=no
// Page 57=
InternalCompressLevel=max
;CreateAppDir=yes
;CreateUninstallRegKey=yes
;;;OverwriteUninstRegEntries
;DirExistsWarning=yes
;;;DisableDirExistsWarning=no
;DisableDirPage=no
// Page 58=
;DisableFinishedPage=no
;DisableProgramGroupPage=yes
DisableReadyMemo=yes
DisableReadyPage=yes
;UserInfoPage=no
// Page 59=
;DefaultUserInfoName={sysuserinfoname}
;DefaultUserInfoOrg={sysuserinfoorg}
;DefaultUserInfoSerial=
;AlwaysUsePersonalGroup=no
OutputBaseFilename=setup_{#VISUAL_SHORT}_{#VISUAL_TYPE}_{#VISUAL_VER}{#VISUAL_REV}
UninstallFilesDir={pf}\{#VISUAL_FIRM}\Setup\{#VISUAL_SHORT} {#VISUAL_TYPE} {#VISUAL_VER}{#VISUAL_REV}
// Page 60=
UninstallDisplayIcon={uninstallexe},0
;;UninstallDisplayName=
;;;UninstallIconName=
;UninstallLogMode=append
;UninstallRestartComputer=no
// Page 61=
;UpdateUninstallLogAppName=yes
DefaultGroupName={#VISUAL_FIRM}\{#VISUAL_SHORT} {#VISUAL_TYPE} {#VISUAL_VER}.{#VISUAL_REV}
;DisableStartupPrompt=yes
;DiskSpanning=no
// Page 62=
;DiskSliceSize=1457664
;DiskClusterSize=512
;SlicesPerDisk=1
;ReserveBytes=0
// Page 63=
;MergeDuplicateFiles=yes
;;;DontMergeDuplicateFiles=no
;AllowCancelDuringInstall=yes
;AllowNoIcons=no
;AllowRootDirectory=no
AllowUNCPath=no
// Page 64=
;AlwaysRestart=no
;RestartIfNeededByRun=yes
;;;MessageFile=
;;LicenseFile={#VISUAL_FILES}\Legal.txt
;;InfoBeforeFile=
// Page 65=
;;InfoAfterFile=
;;ChangesAssociations=yes
;ChangesEnvironment=no
;UsePreviousAppDir=yes
// Page 66=
;UsePreviousGroup=yes
;UsePreviousSetupType=yes
;UsePreviousTasks=yes
;UsePreviousUserInfo=yes
// Page 67=
;;Password=
WizardImageFile={#VISUAL_SPLASH}\BannerLeft{#VISUAL_SHORT}.bmp
;WindowShowCaption=yes
WindowStartMaximized=no
;WindowResizable=yes
// Page 68=
;WindowVisible=no
;WizardImageBackColor=$400000
;WizardImageStretch=yes
;WizardSmallImageBackColor=clWhite
;;SourceDir=
OutputDir=OUTPUT\{#VISUAL_SHORT} {#VISUAL_TYPE} {#VISUAL_VER}.{#VISUAL_REV}
// Page 70=
;;;WizardStyle=modern
;UninstallStyle=modern
;;WizardSmallImageFile={#RESEAU_SPLASH}\BannerTopReseauSmall.bmp
;AlwaysShowComponentsList=yes
;AlwaysShowDirOnReadyPage=no
;AlwaysShowGroupOnReadyPage=no
// Page 71=
;FlatComponentsList=yes
;ShowComponentSizes=yes
;ShowTasksTreeLines=no
ShowLanguageDialog=auto
;LanguageDetectionMethod=uilanguage
// Page 72=
;TimeStampRounding=2
;TimeStampsInUTC=no
SetupIconFile={#VISUAL_SPLASH}\{#VISUAL_SHORT}.ico
;;VersionInfoCompany=
;;VersionInfoDescription=
;;VersionInfoTextVersion=
// Page 73=
VersionInfoVersion={#SETUP_VERSION}
;;;UninstallIconFile={#VISUAL_SPLASH}\Trash.ico
;AppendDefaultDirName=yes
;AppendDefaultGroupName=yes
;TouchDate=current
// Page 74=
;TouchTime=current
;Encryption=no
;;AppModifyPath=
;;OutputManifestFile=Setup-Manifest.txt

; === DEFINE ISSI =====================================================================================================
; C'est incroyable comme on devient vite fainéant à utiliser le code des autres...

; --- FUNCTIONAL ------------------------------------------------------------------------------------------------------

#define ISSI_UninsHs

#define ISSI_NewEvents
;#define ISSI_NewEventsDispatcher

#define ISSI_DoNotIncludeLanguagesSection

;#define ISSI_English
;#define ISSI_French
;#define ISSI_Dutch
;#define ISSI_German
;#define ISSI_Danish
;#define ISSI_Hungarian
;#define ISSI_Spanish

;#define ISSI_AssociateExt     "mcp"
;#define ISSI_AssociateProgram "CodeWarrior"
;#define ISSI_AssociateName    "CodeWarrior Project"

;#define ISSI_AppName
;#define ISSI_AppVersion
;#define ISSI_AppPublisher
;#define ISSI_AppStartMenu
;#define ISSI_AppTemplate

;#define ISSI_Compression

#define ISSI_Constants          "YYMDHMS"
#define ISSI_ConstantsSeperator "/"

;#define ISSI_Download
;#define ISSI_Download_Title "Title Of Download"
;#define ISSI_Download_DLL   "C:\Program Files\ISX Download DLL\isxdl.dll"
;#define ISSI_Download_URL   "http://someserver.com/folder/setup.exe"

;#define ISSI_About

#define ISSI_URL
#define ISSI_URLText

;#define ISSI_ScriptBackup     {#VISUAL_FIRM}+" "+VISUAL_SHORT+" "+VISUAL_TYPE+" "+VISUAL_VER+"."+VISUAL_REV+".iss"
;#define ISSI_ScriptBackup_Key "restorescriptbackup"

#define ISSI_UPDATE            VISUAL_NAME
#define ISSI_UpdateOrInstall
#define ISSI_UpdateTitle       VISUAL_NAME
#define ISSI_UpdateAppVersion  VISUAL_VER+"."+VISUAL_REV

#define ISSI_LicensePrint

;#define ISSI_ScreenSaver "myScreensaver.scr"

; --- APPEARANCE ------------------------------------------------------------------------------------------------------

;#define ISSI_WizardImages

#define ISSI_BeveledApp

;#define ISSI_Image "splash.bmp"

#define ISSI_Splash   VISUAL_SPLASH+"\setup.bmp"
#define ISSI_Splash_T 2
#define ISSI_Splash_X 431
#define ISSI_Splash_Y 331
;#define ISSI_Splash_CORNER 8

;#define ISSI_WizardBitmapImage "splash_495x314.bmp"
;#define ISSI_WizardBitmapImage_x 495
;#define ISSI_WizardBitmapImage2 "albartus_com.bmp"
;#define ISSI_WizardBitmapImage2_x 164

#define ISSI_WizardSmallBitmapImage   VISUAL_SPLASH+"\BannerTop"+VISUAL_SHORT+".bmp"
#define ISSI_WizardSmallBitmapImage_x 120

;#define ISSI_PlayMidi "myMusic.mid"
;#define ISSI_PlayMidiExternal

;#define ISSI_PlayWav "myMusic.wav"
;#define ISSI_PlayWavExternal
;#define ISSI_PlayWavLoop

; --- CUSTOM ----------------------------------------------------------------------------------------------------------

;#define ISSI_Debug
;#define ISSI_UserInclude "no"

// IF defined(ISSI_SCRIPTBACKUP) || defined(ISSI_DOWNLOAD_URL) || defined(ISSI_UPDATE)=
;#define ISSI_UseMyInitializeSetup
// IF defined(ISSI_SPLASH) || defined(ISSI_IMAGE) || defined(ISSI_ABOUT) || defined(ISSI_URLTEXT) || defined(ISSI_WizardBitmapImage) || defined(ISSI_PlayWav) || defined(ISSI_PlayMidi)=
#define ISSI_UseMyInitializeWizard
// IF defined(ISSI_PlayWav) || defined(ISSI_PlayMidi)=
;;#define ISSI_UseMyDeInitializeSetup
// IF defined(ISSI_DOWNLOAD_URL)=
;;#define ISSI_UseMyNextButtonClick
// IF defined(ISSI_DOWNLOAD_URL)=
;;#define ISSI_UseMyBackButtonClick
// IF defined(ISSI_WizardBitmapImage) || defined(ISSI_LicensePrint)=
;#define ISSI_UseMyCurPageChanged
// IF defined(ISSI_UNINSHS) || defined(ISSI_UPDATE)=
;;#define ISSI_UseMySkipCurPage
// IF defined(ISSI_Dispatcher)=
;;#define ISSI_UseMyCurStepChanged

; --- INCLUDE ---------------------------------------------------------------------------------------------------------

#define ISSI_IncludePath VISUAL_TOOLS+"\ISSI"

; === DEFINE ISSI =====================================================================================================

// Page 13=
[Types]
Name: Wce; Description: {cm:VisualTypesWce}
Name: Vcpp; Description: {cm:VisualTypesVcpp}
Name: Custom; Description: {cm:VisualTypesCustom}; Flags: iscustom
Name: Typique; Description: {cm:VisualTypesTypique}
Name: Minimal; Description: {cm:VisualTypesMinimal}

// Page 14: 
[Components]
Name: VisualCpp; Description: {cm:VisualComponentsVisualCpp}; Types: Wce Vcpp Custom Typique Minimal
Name: VisualCpp\ServicePack; Description: {cm:VisualComponentsServicePack}; Types: Vcpp Custom; Flags: exclusive
Name: VisualCpp\CeTools; Description: {cm:VisualComponentsCeTools}; Types: Wce Custom Typique; Flags: exclusive
Name: Preconfig; Description: {cm:VisualComponentsPreconfig}; Types: Wce Vcpp Custom Typique Minimal
#ifdef INSTALL_WNDTABS
Name: WndTabs; Description: {cm:VisualComponentsWndTabs}; Types: Wce Vcpp Custom Typique
Name: WndTabs\Src; Description: {cm:VisualComponentsWndTabsSrc}
#endif
#ifdef INSTALL_KALLISTIOS
Name: KallistiOS; Description: {cm:VisualComponentsKallistiOS}; Types: Vcpp Custom Typique
#endif
Name: VisualToolkit2003; Description: {cm:VisualComponentsVctk2003}; Types: Vcpp Custom Typique
#ifdef VISUAL_MSDN
Name: Msdn; Description: {cm:VisualComponentsMsdn}; Types: Vcpp Custom Typique
Name: Msdn\Indx; Description: {cm:VisualComponentsMsdnIndx}; Types: Vcpp Custom Typique
;Name: Msdn\Vb; Description: {cm:VisualComponentsMsdnVb}
;Name: Msdn\Vb\Doc; Description: {cm:VisualComponentsMsdnVbDoc}
;Name: Msdn\Vb\Exe; Description: {cm:VisualComponentsMsdnVbExe}
;Name: Msdn\Vb\Smpl; Description: {cm:VisualComponentsMsdnVbSmpl}
Name: Msdn\Vcpp; Description: {cm:VisualComponentsMsdnVcpp}; Types: Vcpp Custom Typique
Name: Msdn\Vcpp\Doc; Description: {cm:VisualComponentsMsdnVcppDoc}; Types: Vcpp Custom Typique
Name: Msdn\Vcpp\Smpl; Description: {cm:VisualComponentsMsdnVcppSmpl}
;Name: Msdn\Vfp\Doc; Description: {cm:VisualComponentsMsdnVfpDoc}
;Name: Msdn\Vfp\Exe; Description: {cm:VisualComponentsMsdnVfpExe}
;Name: Msdn\Vfp\Smpl; Description: {cm:VisualComponentsMsdnVfpSmpl}
;Name: Msdn\Vid; Description: {cm:VisualComponentsMsdnVid}
;Name: Msdn\Vid\Doc; Description: {cm:VisualComponentsMsdnVidDoc}
;Name: Msdn\Vid\Smpl; Description: {cm:VisualComponentsMsdnVidSmpl}
;Name: Msdn\Vjpp; Description: {cm:VisualComponentsMsdnVjpp}
;Name: Msdn\Vjpp\Doc; Description: {cm:VisualComponentsMsdnVjppDoc}
;Name: Msdn\Vjpp\Exe; Description: {cm:VisualComponentsMsdnVjppExe}
;Name: Msdn\Vjpp\Smpl; Description: {cm:VisualComponentsMsdnVjppSmpl}
Name: Msdn\Sdk; Description: {cm:VisualComponentsMsdnSdk}; Types: Vcpp Custom Typique
Name: Msdn\Sdk\Doc; Description: {cm:VisualComponentsMsdnSdkDoc}; Types: Vcpp Custom Typique
Name: Msdn\Vs; Description: {cm:VisualComponentsMsdnVs}; Types: Vcpp Custom Typique
Name: Msdn\Vs\Doc; Description: {cm:VisualComponentsMsdnVsDoc}; Types: Vcpp Custom Typique
Name: Msdn\Vs\Smpl; Description: {cm:VisualComponentsMsdnVsSmpl}
Name: Msdn\Rep; Description: {cm:VisualComponentsMsdnRep}; Types: Vcpp Custom Typique
Name: Msdn\Rep\Smpl; Description: {cm:VisualComponentsMsdnRepSmpl}; Types: Vcpp Custom Typique
;Name: Msdn\Vss; Description: {cm:VisualComponentsMsdnVss}
;Name: Msdn\Vss\Doc; Description: {cm:VisualComponentsMsdnVssDoc}
Name: Msdn\Other; Description: {cm:VisualComponentsMsdnOther}; Types: Vcpp Custom Typique
;Name: Msdn\Other\Doc; Description: {cm:VisualComponentsMsdnOtherDoc}; Types: Vcpp Custom Typique
;Name: Msdn\Smpl; Description: {cm:VisualComponentsMsdnSmpl}
;Name: Msdn\Smpl\Ihn; Description: {cm:VisualComponentsMsdnSmplIhn}
;Name: Msdn\Smpl\Smpl; Description: {cm:VisualComponentsMsdnSmplSmpl}
#endif
Name: Backup; Description: {cm:VisualComponentsBackup}

// Page 16: 
[Tasks]
Name: desktopicon; Description: {cm:CreateDesktopIcon}; GroupDescription: {cm:AdditionalIcons}
Name: quicklaunchicon; Description: {cm:CreateQuickLaunchIcon}; GroupDescription: {cm:AdditionalIcons}; Flags: unchecked
;Name: extractinstall; Description: {cm:VisualTasksBackupInstall}; GroupDescription: {cm:VisualDescriptionBackup}; Flags: unchecked

// Page 18: 
[Dirs]
Name: {app}; Permissions: everyone-modify

// Page 20: 
[Files]
#ifndef VISUAL_DEBUG
; NOTE: Ne pas utiliser "Flags: ignoreversion" sur les fichier système partagés
; Visual C++ 6 common files between SP0, SP6 and CET
Source: {#VISUAL_FILES}\VC6\COMMON\*; DestDir: {app}\Common; Excludes: MSDev98\Bin\*,Tools\*; Components: VisualCpp; Flags: recursesubdirs
Source: {#VISUAL_FILES}\VC6\COMMON\MSDev98\Bin\*; DestDir: {app}\Common\MSDev98\Bin; Components: VisualCpp; Flags: recursesubdirs sharedfile uninsnosharedfileprompt
Source: {#VISUAL_FILES}\VC6\COMMON\Tools\*; DestDir: {app}\Common\Tools; Components: VisualCpp; Flags: recursesubdirs sharedfile uninsnosharedfileprompt
Source: {#VISUAL_FILES}\VC6\COMREG\*; DestDir: {app}\Common; Components: VisualCpp; Flags: recursesubdirs sharedfile uninsnosharedfileprompt regserver
Source: {#VISUAL_FILES}\VC6\COMTYP\*; DestDir: {app}\Common; Components: VisualCpp; Flags: recursesubdirs sharedfile uninsnosharedfileprompt regtypelib
Source: {#VISUAL_FILES}\VC6\HELP\*; DestDir: {win}\Help; Components: VisualCpp; Flags: recursesubdirs
Source: {#VISUAL_FILES}\VC6\SHARED\*; DestDir: {cf}; Components: VisualCpp; Flags: recursesubdirs sharedfile uninsnosharedfileprompt
Source: {#VISUAL_FILES}\VC6\SHAREG\*.dll; DestDir: {cf}; Components: VisualCpp; Flags: recursesubdirs sharedfile uninsnosharedfileprompt regserver
;Source: {#VISUAL_FILES}\VC6\SHAREG\*.tlb; DestDir: {cf}; Components: VisualCpp; Flags: recursesubdirs sharedfile uninsnosharedfileprompt regtypelib
Source: {#VISUAL_FILES}\VC6\SHATYP\*.dll; DestDir: {cf}; Components: VisualCpp; Flags: recursesubdirs sharedfile uninsnosharedfileprompt regtypelib
Source: {#VISUAL_FILES}\VC6\SYS\*; DestDir: {sys}; Excludes: *.dep,*.dll,*.ocx; Components: VisualCpp
Source: {#VISUAL_FILES}\VC6\SYS\*.dep; DestDir: {sys}; Components: VisualCpp; Flags: sharedfile uninsnosharedfileprompt
Source: {#VISUAL_FILES}\VC6\SYS\*.dll; DestDir: {sys}; Components: VisualCpp; Flags: sharedfile uninsnosharedfileprompt
Source: {#VISUAL_FILES}\VC6\SYS\Register\*.dll; DestDir: {sys}; Components: VisualCpp; Flags: sharedfile uninsnosharedfileprompt regserver
Source: {#VISUAL_FILES}\VC6\SYS\Register\*.ocx; DestDir: {sys}; Components: VisualCpp; Flags: sharedfile uninsnosharedfileprompt regserver
Source: {#VISUAL_FILES}\VC6\SYS\Register\*.tlb; DestDir: {sys}; Components: VisualCpp; Flags: sharedfile uninsnosharedfileprompt regtypelib skipifsourcedoesntexist
Source: {#VISUAL_FILES}\VC6\VC98\*; DestDir: {app}\VC98; Components: VisualCpp; Flags: recursesubdirs
Source: {#VISUAL_FILES}\VC6\WIN\*; DestDir: {win}; Components: VisualCpp
; Visual C++ 6 common files between SP6 and CET
Source: {#VISUAL_FILES}\ADD\SHARNO\*; DestDir: {cf}; Components: VisualCpp\ServicePack or VisualCpp\CeTools; Flags: recursesubdirs uninsnosharedfileprompt skipifsourcedoesntexist
Source: {#VISUAL_FILES}\ADD\SHARED\*; DestDir: {cf}; Components: VisualCpp\ServicePack or VisualCpp\CeTools; Flags: recursesubdirs sharedfile uninsnosharedfileprompt skipifsourcedoesntexist
Source: {#VISUAL_FILES}\ADD\SHAREG\*.dll; DestDir: {cf}; Components: VisualCpp\ServicePack or VisualCpp\CeTools; Flags: recursesubdirs uninsnosharedfileprompt regserver
Source: {#VISUAL_FILES}\ADD\SHATYP\*.dll; DestDir: {cf}; Components: VisualCpp\ServicePack or VisualCpp\CeTools; Flags: recursesubdirs sharedfile uninsnosharedfileprompt regtypelib
Source: {#VISUAL_FILES}\ADD\SYS\*; DestDir: {sys}; Excludes: *.dep,*.dll,*.ocx; Components: VisualCpp\ServicePack or VisualCpp\CeTools
Source: {#VISUAL_FILES}\ADD\SYS\*.dll; DestDir: {sys}; Components: VisualCpp\ServicePack or VisualCpp\CeTools; Flags: sharedfile uninsnosharedfileprompt
; Visual C++ 6 SP0 used ONLY with CET (avoid write/register twice when used with SP6)
Source: {#VISUAL_FILES}\SP0\COMMON\*; DestDir: {app}\Common; Excludes: MSDev98\Bin\*,Tools\*; Components: VisualCpp\CeTools; Flags: recursesubdirs
Source: {#VISUAL_FILES}\SP0\COMMON\MSDev98\Bin\*; DestDir: {app}\Common\MSDev98\Bin; Components: VisualCpp\CeTools; Flags: recursesubdirs sharedfile uninsnosharedfileprompt
Source: {#VISUAL_FILES}\SP0\COMREG\*; DestDir: {app}\Common; Components: VisualCpp\CeTools; Flags: recursesubdirs sharedfile uninsnosharedfileprompt regserver
Source: {#VISUAL_FILES}\SP0\SHARED\*; DestDir: {cf}; Components: VisualCpp\CeTools; Flags: recursesubdirs sharedfile uninsnosharedfileprompt
Source: {#VISUAL_FILES}\SP0\SHAREG\*.dll; DestDir: {cf}; Components: VisualCpp\CeTools; Flags: recursesubdirs sharedfile uninsnosharedfileprompt regserver
;Source: {#VISUAL_FILES}\SP0\SHAREG\*.tlb; DestDir: {cf}; Components: VisualCpp\CeTools; Flags: recursesubdirs sharedfile uninsnosharedfileprompt regtypelib
Source: {#VISUAL_FILES}\SP0\SYS\*; DestDir: {sys}; Excludes: *.dep,*.dll,*.ocx; Components: VisualCpp\CeTools
Source: {#VISUAL_FILES}\SP0\SYS\*.dep; DestDir: {sys}; Components: VisualCpp\CeTools; Flags: sharedfile uninsnosharedfileprompt
Source: {#VISUAL_FILES}\SP0\SYS\*.dll; DestDir: {sys}; Components: VisualCpp\CeTools; Flags: sharedfile uninsnosharedfileprompt
Source: {#VISUAL_FILES}\SP0\SYS\Register\*.dll; DestDir: {sys}; Components: VisualCpp\CeTools; Flags: sharedfile uninsnosharedfileprompt regserver
Source: {#VISUAL_FILES}\SP0\SYS\Register\*.ocx; DestDir: {sys}; Components: VisualCpp\CeTools; Flags: sharedfile uninsnosharedfileprompt regserver
Source: {#VISUAL_FILES}\SP0\SYS\Register\*.tlb; DestDir: {sys}; Components: VisualCpp\CeTools; Flags: sharedfile uninsnosharedfileprompt regtypelib skipifsourcedoesntexist
Source: {#VISUAL_FILES}\SP0\VC98\*; DestDir: {app}\VC98; Components: VisualCpp\CeTools; Flags: recursesubdirs
; Visual C++ 6 SP6
Source: {#VISUAL_FILES}\SP6\COMMON\*; DestDir: {app}\Common; Excludes: MSDev98\Bin\*,Tools\*; Components: VisualCpp\ServicePack; Flags: recursesubdirs
Source: {#VISUAL_FILES}\SP6\COMMON\MSDev98\Bin\*; DestDir: {app}\Common\MSDev98\Bin; Components: VisualCpp\ServicePack; Flags: recursesubdirs sharedfile uninsnosharedfileprompt
Source: {#VISUAL_FILES}\SP6\COMMON\Tools\*; DestDir: {app}\Common\Tools; Components: VisualCpp\ServicePack; Flags: recursesubdirs sharedfile uninsnosharedfileprompt skipifsourcedoesntexist
Source: {#VISUAL_FILES}\SP6\COMREG\*; DestDir: {app}\Common; Components: VisualCpp\ServicePack; Flags: recursesubdirs sharedfile uninsnosharedfileprompt regserver
Source: {#VISUAL_FILES}\SP6\SHARED\*; DestDir: {cf}; Components: VisualCpp\ServicePack; Flags: recursesubdirs sharedfile uninsnosharedfileprompt skipifsourcedoesntexist
Source: {#VISUAL_FILES}\SP6\SHAREG\*.dll; DestDir: {cf}; Components: VisualCpp\ServicePack; Flags: recursesubdirs sharedfile uninsnosharedfileprompt regserver
;Source: {#VISUAL_FILES}\SP6\SHAREG\*.tlb; DestDir: {cf}; Components: VisualCpp\ServicePack; Flags: recursesubdirs sharedfile uninsnosharedfileprompt regtypelib
Source: {#VISUAL_FILES}\SP6\SYS\*; DestDir: {sys}; Excludes: *.dep,*.dll,*.ocx; Components: VisualCpp\ServicePack
Source: {#VISUAL_FILES}\SP6\SYS\*.dep; DestDir: {sys}; Components: VisualCpp\ServicePack; Flags: sharedfile uninsnosharedfileprompt
Source: {#VISUAL_FILES}\SP6\SYS\*.dll; DestDir: {sys}; Components: VisualCpp\ServicePack; Flags: sharedfile uninsnosharedfileprompt
Source: {#VISUAL_FILES}\SP6\SYS\Register\*.dll; DestDir: {sys}; Components: VisualCpp\ServicePack; Flags: sharedfile uninsnosharedfileprompt regserver
Source: {#VISUAL_FILES}\SP6\SYS\Register\*.ocx; DestDir: {sys}; Components: VisualCpp\ServicePack; Flags: sharedfile uninsnosharedfileprompt regserver
Source: {#VISUAL_FILES}\SP6\SYS\Register\*.tlb; DestDir: {sys}; Components: VisualCpp\ServicePack; Flags: sharedfile uninsnosharedfileprompt regtypelib skipifsourcedoesntexist
Source: {#VISUAL_FILES}\SP6\VC98\*; DestDir: {app}\VC98; Components: VisualCpp\ServicePack; Flags: recursesubdirs
Source: {#VISUAL_FILES}\SP6\WIN\*; DestDir: {win}; Components: VisualCpp\ServicePack
; Windows CE Tools
Source: {#VISUAL_FILES}\CET\COMMON\*; DestDir: {app}\Common; Excludes: MSDev98\Bin\*,Tools\*; Components: VisualCpp\CeTools; Flags: recursesubdirs
Source: {#VISUAL_FILES}\CET\COMMON\MSDev98\Bin\*; DestDir: {app}\Common\MSDev98\Bin; Components: VisualCpp\CeTools; Flags: recursesubdirs sharedfile uninsnosharedfileprompt
Source: {#VISUAL_FILES}\CET\COMMON\Tools\*; DestDir: {app}\Common\Tools; Components: VisualCpp\CeTools; Flags: recursesubdirs sharedfile uninsnosharedfileprompt skipifsourcedoesntexist
Source: {#VISUAL_FILES}\CET\COMREG\*; DestDir: {app}\Common; Components: VisualCpp\CeTools; Flags: recursesubdirs sharedfile uninsnosharedfileprompt regserver
Source: {#VISUAL_FILES}\CET\SHARED\*; DestDir: {cf}; Components: VisualCpp\CeTools; Flags: recursesubdirs sharedfile uninsnosharedfileprompt skipifsourcedoesntexist
Source: {#VISUAL_FILES}\CET\SHAREG\*.dll; DestDir: {cf}; Components: VisualCpp\CeTools; Flags: recursesubdirs sharedfile uninsnosharedfileprompt regserver
;Source: {#VISUAL_FILES}\CET\SHAREG\*.tlb; DestDir: {cf}; Components: VisualCpp\CeTools; Flags: recursesubdirs sharedfile uninsnosharedfileprompt regtypelib
#endif
Source: {#VISUAL_FILES}\CET\HELP\*; DestDir: {win}\Help; Components: VisualCpp\CeTools; Flags: recursesubdirs
Source: {#VISUAL_FILES}\CET\SYS\*; DestDir: {sys}; Excludes: *.dep,*.dll,*.ocx; Components: VisualCpp\CeTools
Source: {#VISUAL_FILES}\CET\SYS\*.dep; DestDir: {sys}; Components: VisualCpp\CeTools; Flags: sharedfile uninsnosharedfileprompt skipifsourcedoesntexist
Source: {#VISUAL_FILES}\CET\SYS\*.dll; DestDir: {sys}; Components: VisualCpp\CeTools; Flags: sharedfile uninsnosharedfileprompt skipifsourcedoesntexist
Source: {#VISUAL_FILES}\CET\SYS\Register\*.dll; DestDir: {sys}; Components: VisualCpp\CeTools; Flags: sharedfile uninsnosharedfileprompt regserver skipifsourcedoesntexist
Source: {#VISUAL_FILES}\CET\SYS\Register\*.ocx; DestDir: {sys}; Components: VisualCpp\CeTools; Flags: sharedfile uninsnosharedfileprompt regserver skipifsourcedoesntexist
Source: {#VISUAL_FILES}\CET\SYS\Register\*.tlb; DestDir: {sys}; Components: VisualCpp\CeTools; Flags: sharedfile uninsnosharedfileprompt regtypelib skipifsourcedoesntexist
Source: {#VISUAL_FILES}\CET\VC98\*; DestDir: {app}\VC98; Components: VisualCpp\CeTools; Flags: recursesubdirs
Source: {#VISUAL_FILES}\CET\WCET\*; DestDir: {app}\Windows CE Tools; Components: VisualCpp\CeTools; Flags: recursesubdirs
#ifdef INSTALL_WNDTABS
; WndTabs
Source: {#VISUAL_FILES}\WND\SHAREG\*.dll; DestDir: {app}\WndTabs; Components: WndTabs; Flags: regserver
Source: {#VISUAL_FILES}\WND\TABS\*; DestDir: {app}\WndTabs; Components: WndTabs; Flags: recursesubdirs
Source: {#VISUAL_FILES}\WND\SRC\*; DestDir: {app}\WndTabs\Source; Components: WndTabs\Src; Flags: recursesubdirs
#endif
#ifdef INSTALL_KALLISTIOS
; KallistiOS
Source: {#VISUAL_FILES}\DC\COMMON\*; DestDir: {app}\Common; Components: KallistiOS; Flags: recursesubdirs skipifsourcedoesntexist
Source: {#VISUAL_FILES}\DC\DevKitDC\*; DestDir: {sd}\DevKitDC; Components: KallistiOS; Flags: recursesubdirs skipifsourcedoesntexist
Source: {#VISUAL_FILES}\DC\DevKitDC\bin\*.dll; DestDir: {sys}; Components: KallistiOS; Flags: sharedfile uninsnosharedfileprompt skipifsourcedoesntexist
#endif
; Visual C++ Toolkit 2003
Source: {#VISUAL_FILES}\VC2003\TOOLKIT\*; DestDir: {app}\VCTK2003; Components: VisualToolkit2003; Flags: recursesubdirs
#ifdef VISUAL_MSDN
; MSDN
Source: {#VISUAL_FILES}\MSDN\ROOT\*; DestDir: {app}; Components: Msdn; Flags: recursesubdirs
Source: {#VISUAL_FILES}\MSDN\DOCSET\*; DestDir: {userappdata}; Components: Msdn; Flags: recursesubdirs
Source: {#VISUAL_FILES}\MSDN\HELP\*; DestDir: {win}\Help; Components: Msdn; Flags: recursesubdirs
Source: {#VISUAL_FILES}\MSDN\SYS\*.dll; DestDir: {sys}; Components: Msdn; Flags: sharedfile uninsnosharedfileprompt skipifsourcedoesntexist
Source: {#VISUAL_FILES}\MSDN\INDEX\DOC\*; DestDir: {app}; Components: Msdn\Indx; Flags: recursesubdirs
;Source: {#VISUAL_FILES}\MSDN\VB\DOC\*; DestDir: {app}; Components: Msdn\Vb\Doc; Flags: recursesubdirs skipifsourcedoesntexist
;Source: {#VISUAL_FILES}\MSDN\VB\EXE\*; DestDir: {app}; Components: Msdn\Vb\Exe; Flags: recursesubdirs skipifsourcedoesntexist
;Source: {#VISUAL_FILES}\MSDN\VB\SMPL\*; DestDir: {app}; Components: Msdn\Vb\Smpl; Flags: recursesubdirs skipifsourcedoesntexist
Source: {#VISUAL_FILES}\MSDN\VCPP\DOC\*; DestDir: {app}; Components: Msdn\Vcpp\Doc; Flags: recursesubdirs
Source: {#VISUAL_FILES}\MSDN\VCPP\SMPL\*; DestDir: {app}; Components: Msdn\Vcpp\Smpl; Flags: recursesubdirs
;Source: {#VISUAL_FILES}\MSDN\VFP\DOC\*; DestDir: {app}; Components: Msdn\Vfp\Doc; Flags: recursesubdirs skipifsourcedoesntexist
;Source: {#VISUAL_FILES}\MSDN\VFP\EXE\*; DestDir: {app}; Components: Msdn\Vfp\Exe; Flags: recursesubdirs skipifsourcedoesntexist
;Source: {#VISUAL_FILES}\MSDN\VFP\SMPL\*; DestDir: {app}; Components: Msdn\Vfp\Smpl; Flags: recursesubdirs skipifsourcedoesntexist
;Source: {#VISUAL_FILES}\MSDN\VID\DOC\*; DestDir: {app}; Components: Msdn\Vid\Doc; Flags: recursesubdirs
;Source: {#VISUAL_FILES}\MSDN\VID\SMPL\*; DestDir: {app}; Components: Msdn\Vid\Smpl; Flags: recursesubdirs
;Source: {#VISUAL_FILES}\MSDN\VJPP\DOC\*; DestDir: {app}; Components: Msdn\Vjpp\Doc; Flags: recursesubdirs skipifsourcedoesntexist
;Source: {#VISUAL_FILES}\MSDN\VJPP\EXE\*; DestDir: {app}; Components: Msdn\Vjpp\Exe; Flags: recursesubdirs skipifsourcedoesntexist
;Source: {#VISUAL_FILES}\MSDN\VJPP\SMPL\*; DestDir: {app}; Components: Msdn\Vjpp\Smpl; Flags: recursesubdirs skipifsourcedoesntexist
Source: {#VISUAL_FILES}\MSDN\SDK\DOC\*; DestDir: {app}; Components: Msdn\Sdk\Doc; Flags: recursesubdirs
Source: {#VISUAL_FILES}\MSDN\VS\DOC\*; DestDir: {app}; Components: Msdn\Vs\Doc; Flags: recursesubdirs
Source: {#VISUAL_FILES}\MSDN\VS\SMPL\*; DestDir: {app}; Components: Msdn\Vs\Smpl; Flags: recursesubdirs
Source: {#VISUAL_FILES}\MSDN\REP\SMPL\*; DestDir: {app}; Components: Msdn\Rep\Smpl; Flags: recursesubdirs
;Source: {#VISUAL_FILES}\MSDN\VSS\DOC\*; DestDir: {app}; Components: Msdn\Vss\Doc; Flags: recursesubdirs skipifsourcedoesntexist
Source: {#VISUAL_FILES}\MSDN\OTHER\DOC\*; DestDir: {app}; Components: Msdn\Other; Flags: recursesubdirs
;Source: {#VISUAL_FILES}\MSDN\SMPL\IHN\*; DestDir: {app}; Components: Msdn\Smpl\Ihn; Flags: recursesubdirs skipifsourcedoesntexist
;Source: {#VISUAL_FILES}\MSDN\SMPL\SMPL\*; DestDir: {app}; Components: Msdn\Smpl\Smpl; Flags: recursesubdirs skipifsourcedoesntexist
#endif
; Icones
Source: {#VISUAL_SPLASH}\trash.ico; DestDir: {pf}\{#VISUAL_FIRM}\Setup\{#VISUAL_SHORT} {#VISUAL_TYPE} {#VISUAL_VER}{#VISUAL_REV}
; Install
;Source: {#VISUAL_INSTALL}\{#VISUAL_SHORT} {#VISUAL_TYPE} {#VISUAL_VER}.{#VISUAL_REV}.iss; DestDir: {app}\Inst
;Source: {#VISUAL_TOOLS}\Setup{#VISUAL_SHORT}.isi; DestDir: {app}\Inst
;Source: {#ISSI_IncludePath}\*; DestDir: {app}\Inst\ISSI; Flags: recursesubdirs
;Source: {#VISUAL_SPLASH}\*; DestDir: {app}\Inst\Splash; Flags: recursesubdirs
;Source: {#VISUAL_TEXT}\*; DestDir: {app}\Inst\Text; Flags: recursesubdirs
#ifndef VISUAL_DEBUG
; Backup
Source: {#VISUAL_INSTALL}\*; DestDir: {app}\BACKUP; Excludes: \OUTPUT\{#VISUAL_SHORT}*\*.bin,\OUTPUT\{#VISUAL_SHORT}*\*.exe,\LEGACY\*,\TXT\*; Flags: recursesubdirs; Components: Backup
; Tasks: extractinstall
#endif
; UninsHs
#ifdef USE_MODIFYREPAIRDELETE
Source: {#ISSI_IncludePath}\UninsHs.exe; DestDir: {pf}\Sega\Setup\{#VISUAL_SHORT} {#VISUAL_TYPE} {#VISUAL_VER}{#VISUAL_REV}; Flags: ignoreversion onlyifdoesntexist
#endif

// Page 26: 
[Icons]
; Sur le bureau
Name: {commondesktop}\{#VISUAL_SHORT} {#VISUAL_TYPE} {#VISUAL_VER}.{#VISUAL_REV}; Filename: {app}\Common\MSDev98\Bin\MSDEV.EXE; Tasks: desktopicon; Components: VisualCpp
; En démarrage rapide
Name: {userappdata}\Microsoft\Internet Explorer\Quick Launch\{#VISUAL_SHORT} {#VISUAL_TYPE} {#VISUAL_VER}.{#VISUAL_REV}; Filename: {app}\Common\MSDev98\Bin\MSDEV.EXE; Tasks: quicklaunchicon; Components: VisualCpp
; Les outils
Name: {group}\{#VISUAL_FIRM} {#VISUAL_SHORT} {#VISUAL_TYPE} {#VISUAL_VER}.{#VISUAL_REV} Tools\ActiveX Control Test Container; Filename: {app}\Common\Tools\TSTCON32.EXE; Components: VisualCpp
Name: {group}\{#VISUAL_FIRM} {#VISUAL_SHORT} {#VISUAL_TYPE} {#VISUAL_VER}.{#VISUAL_REV} Tools\DataObject Viewer; Filename: {app}\Common\Tools\DOBJVIEW.EXE; Components: VisualCpp
Name: {group}\{#VISUAL_FIRM} {#VISUAL_SHORT} {#VISUAL_TYPE} {#VISUAL_VER}.{#VISUAL_REV} Tools\DDE Spy; Filename: {app}\Common\Tools\WinNT\DDESPY.EXE; Components: VisualCpp
Name: {group}\{#VISUAL_FIRM} {#VISUAL_SHORT} {#VISUAL_TYPE} {#VISUAL_VER}.{#VISUAL_REV} Tools\Depends; Filename: {app}\Common\Tools\DEPENDS.EXE; Components: VisualCpp
Name: {group}\{#VISUAL_FIRM} {#VISUAL_SHORT} {#VISUAL_TYPE} {#VISUAL_VER}.{#VISUAL_REV} Tools\DocFile Viewer; Filename: {app}\Common\Tools\DFVIEW.EXE; Components: VisualCpp
Name: {group}\{#VISUAL_FIRM} {#VISUAL_SHORT} {#VISUAL_TYPE} {#VISUAL_VER}.{#VISUAL_REV} Tools\Error Lookup; Filename: {app}\Common\Tools\ERRLOOK.EXE; Components: VisualCpp
Name: {group}\{#VISUAL_FIRM} {#VISUAL_SHORT} {#VISUAL_TYPE} {#VISUAL_VER}.{#VISUAL_REV} Tools\Help Workshop; Filename: {app}\Common\Tools\HCW.EXE; Components: VisualCpp
Name: {group}\{#VISUAL_FIRM} {#VISUAL_SHORT} {#VISUAL_TYPE} {#VISUAL_VER}.{#VISUAL_REV} Tools\OLE Client Test; Filename: {app}\Common\Tools\WinNT\CL32TEST.EXE; Components: VisualCpp
Name: {group}\{#VISUAL_FIRM} {#VISUAL_SHORT} {#VISUAL_TYPE} {#VISUAL_VER}.{#VISUAL_REV} Tools\OLE Server Test; Filename: {app}\Common\Tools\WinNT\SR32TEST.EXE; Components: VisualCpp
Name: {group}\{#VISUAL_FIRM} {#VISUAL_SHORT} {#VISUAL_TYPE} {#VISUAL_VER}.{#VISUAL_REV} Tools\OLE Tools; Filename: {app}\Common\Tools\OLETOOLS.HLP; Components: VisualCpp
Name: {group}\{#VISUAL_FIRM} {#VISUAL_SHORT} {#VISUAL_TYPE} {#VISUAL_VER}.{#VISUAL_REV} Tools\OLE View; Filename: {app}\Common\Tools\OLEVIEW.EXE; Components: VisualCpp
Name: {group}\{#VISUAL_FIRM} {#VISUAL_SHORT} {#VISUAL_TYPE} {#VISUAL_VER}.{#VISUAL_REV} Tools\Process Viewer; Filename: {app}\Common\Tools\WinNT\PVIEW.EXE; Components: VisualCpp
Name: {group}\{#VISUAL_FIRM} {#VISUAL_SHORT} {#VISUAL_TYPE} {#VISUAL_VER}.{#VISUAL_REV} Tools\ROT Viewer; Filename: {app}\Common\Tools\IROTVIEW.EXE; Components: VisualCpp
Name: {group}\{#VISUAL_FIRM} {#VISUAL_SHORT} {#VISUAL_TYPE} {#VISUAL_VER}.{#VISUAL_REV} Tools\Spy++; Filename: {app}\Common\Tools\SPYXX.EXE; Components: VisualCpp
Name: {group}\{#VISUAL_FIRM} {#VISUAL_SHORT} {#VISUAL_TYPE} {#VISUAL_VER}.{#VISUAL_REV} Tools\Tracer; Filename: {app}\Common\Tools\TRACER.EXE; Components: VisualCpp
Name: {group}\{#VISUAL_FIRM} {#VISUAL_SHORT} {#VISUAL_TYPE} {#VISUAL_VER}.{#VISUAL_REV} Tools\Windiff; Filename: {app}\Common\Tools\WINDIFF.EXE; Components: VisualCpp
Name: {group}\{#VISUAL_FIRM} {#VISUAL_SHORT} {#VISUAL_TYPE} {#VISUAL_VER}.{#VISUAL_REV} Tools\Windows NT Symbols Setup; Filename: {app}\Common\MSDev98\Bin\SETUPDBG.EXE; WorkingDir: {app}\Common\MSDev98\Bin; Components: VisualCpp
Name: {group}\{#VISUAL_FIRM} {#VISUAL_SHORT} {#VISUAL_TYPE} {#VISUAL_VER}.{#VISUAL_REV} Tools\Zoomin; Filename: {app}\Common\Tools\ZOOMIN.EXE; Components: VisualCpp
; Sur les programmes
Name: {group}\{#VISUAL_FIRM} {#VISUAL_SHORT} {#VISUAL_TYPE} {#VISUAL_VER}.{#VISUAL_REV}; Filename: {app}\Common\MSDev98\Bin\MSDEV.EXE; Components: VisualCpp
; Sur Windows CE
Name: {group}\Windows CE Tools\Remote File Viewer; Filename: {app}\Windows CE Tools\WCE200\BIN\CEFILEVW.EXE; WorkingDir: {app}\Windows CE Tools\WCE200\BIN; Components: VisualCpp\CeTools
Name: {group}\Windows CE Tools\Remote Heap Walker; Filename: {app}\Windows CE Tools\WCE200\BIN\CEHEAPWK.EXE; WorkingDir: {app}\Windows CE Tools\WCE200\BIN; Components: VisualCpp\CeTools
Name: {group}\Windows CE Tools\Remote Process Viewer; Filename: {app}\Windows CE Tools\WCE200\BIN\CEPVIEW.EXE; WorkingDir: {app}\Windows CE Tools\WCE200\BIN; Components: VisualCpp\CeTools
Name: {group}\Windows CE Tools\Remote Registry Editor; Filename: {app}\Windows CE Tools\WCE200\BIN\CEREGEDT.EXE; WorkingDir: {app}\Windows CE Tools\WCE200\BIN; Components: VisualCpp\CeTools
Name: {group}\Windows CE Tools\Remote Spy++; Filename: {app}\Windows CE Tools\WCE200\BIN\CESPY.EXE; WorkingDir: {app}\Windows CE Tools\WCE200\BIN; Components: VisualCpp\CeTools
Name: {group}\Windows CE Tools\Remote Zoomin; Filename: {app}\Windows CE Tools\WCE200\BIN\CEZOOM.EXE; WorkingDir: {app}\Windows CE Tools\WCE200\BIN; Components: VisualCpp\CeTools
Name: {group}\Windows CE Tools\WCE Toolkit for VC++ Release Notes; Filename: {app}\Windows CE Tools\RLNVCCE6.HTM; WorkingDir: {app}\Windows CE Tools\; Components: VisualCpp\CeTools
Name: {group}\Windows CE Tools\Windows CE Documentation; Filename: {win}\hh.exe; Parameters: {app}\Windows CE Tools\htmlhelp\wince.col; WorkingDir: {win}; Components: VisualCpp\CeTools
#ifdef INSTALL_WNDTABS
; WndTabs
Name: {group}\WndTabs\WndTabs Help File; Filename: {app}\WndTabs\WndTabs.chm; Components: WndTabs
Name: {group}\WndTabs\WndTabs Readme File; Filename: {app}\WndTabs\ReadMe.txt; Components: WndTabs
Name: {group}\WndTabs\WndTabs Website; Filename: {app}\WndTabs\WndTabs.url; Components: WndTabs
#endif
; Visual C++ Toolkit 2003
Name: {group}\Microsoft Visual C++ Toolkit 2003\Visual C++ Toolkit 2003 Command Prompt; Filename: %comspec%; Parameters: /k vcvars32.bat; WorkingDir: %VCToolkitInstallDir%; Comment: Open Visual C++ Toolkit 2003 Command Prompt; Components: VisualToolkit2003
Name: {group}\Microsoft Visual C++ Toolkit 2003\Visual C++ Toolkit 2003 Readme; Filename: {app}\VCTK2003\README.htm; Comment: Readme file for Visual C++ Toolkit 2003; Components: VisualToolkit2003
Name: {app}\VCTK2003\Visual C++ Toolkit 2003 Command Prompt; Filename: %comspec%; Parameters: /k vcvars32.bat; WorkingDir: %VCToolkitInstallDir%; Comment: Open Visual C++ Toolkit 2003 Command Prompt; Components: VisualToolkit2003
#ifdef VISUAL_MSDN
; MSDN
Name: {group}\Microsoft Developer Network\MSDN Library Visual Studio 6.0a; Filename: {win}\hh.exe; Parameters: {app}\MSDN98\98VSa\1036\msdnvs6a.col; WorkingDir: {app}\MSDN98\98VSa\1036\; Components: Msdn
#endif
; Le reste
#ifdef USE_MODIFYREPAIRDELETE
Name: {group}\{cm:VisualTxtUninstall,{#VISUAL_SHORT}}; Filename: {pf}\{#VISUAL_FIRM}\Setup\{#VISUAL_SHORT} {#VISUAL_TYPE} {#VISUAL_VER}{#VISUAL_REV}\UninsHs.exe
#else
Name: {group}\{cm:VisualTxtUninstall,{#VISUAL_SHORT}}; Filename: {uninstallexe}; IconFilename: {pf}\{#VISUAL_FIRM}\Setup\{#VISUAL_SHORT} {#VISUAL_TYPE} {#VISUAL_VER}{#VISUAL_REV}\trash.ico
#endif

// Page 29: 
[INI]
#ifdef USE_MODIFYREPAIRDELETE
FileName: {pf}\{#VISUAL_FIRM}\Setup\{#VISUAL_SHORT} {#VISUAL_TYPE} {#VISUAL_VER}{#VISUAL_REV}\UninsHs.dat; Section: Common; Key: Software; String: {#VISUAL_NAME}
FileName: {pf}\{#VISUAL_FIRM}\Setup\{#VISUAL_SHORT} {#VISUAL_TYPE} {#VISUAL_VER}{#VISUAL_REV}\UninsHs.dat; Section: Common; Key: Install; String: {srcexe}
FileName: {pf}\{#VISUAL_FIRM}\Setup\{#VISUAL_SHORT} {#VISUAL_TYPE} {#VISUAL_VER}{#VISUAL_REV}\UninsHs.dat; Section: Common; Key: Language; String: {language}
FileName: {pf}\{#VISUAL_FIRM}\Setup\{#VISUAL_SHORT} {#VISUAL_TYPE} {#VISUAL_VER}{#VISUAL_REV}\UninsHs.dat; Section: Common; Key: Remove; String: {uninstallexe}
FileName: {pf}\{#VISUAL_FIRM}\Setup\{#VISUAL_SHORT} {#VISUAL_TYPE} {#VISUAL_VER}{#VISUAL_REV}\UninsHs.dat; Section: Common; Key: Group; String: {groupname}
FileName: {pf}\{#VISUAL_FIRM}\Setup\{#VISUAL_SHORT} {#VISUAL_TYPE} {#VISUAL_VER}{#VISUAL_REV}\UninsHs.dat; Section: Common; Key: Components; String: {code:ComponentList|x}
FileName: {pf}\{#VISUAL_FIRM}\Setup\{#VISUAL_SHORT} {#VISUAL_TYPE} {#VISUAL_VER}{#VISUAL_REV}\UninsHs.dat; Section: Common; Key: Uninstall; String: {#VISUAL_NAME}
FileName: {pf}\{#VISUAL_FIRM}\Setup\{#VISUAL_SHORT} {#VISUAL_TYPE} {#VISUAL_VER}{#VISUAL_REV}\UninsHs.dat; Section: Common; Key: Dir; String: {app}
#endif

// Page 30 -> 41: 
[InstallDelete]
; Un peu de nettoyage d'une précédente installation
;Type: files; Name: {app}\SetPaths.bat

// Page 31: 
[Languages]
Name: en; MessagesFile: compiler:Default.isl,{#VISUAL_TEXT}\CmVisualEnglish.isl,{#ISSI_IncludePath}\Languages\_issi_English.isl; LicenseFile: {#VISUAL_FILES}\Eula.txt
//Name: fr; MessagesFile: compiler:Languages\French.isl,{#VISUAL_TEXT}\CmVisualFrench.isl,{#ISSI_IncludePath}\Languages\_issi_French.isl; LicenseFile: {#VISUAL_FILES}\EulaFr.txt

// Page 32: 
[Messages]
; Un peu de pub pour super InnoSetup
BeveledLabel=InnoSetup is installing {#VISUAL_NAME} {#VISUAL_VER}.{#VISUAL_REV}

// Page 33=
[CustomMessages]
; On fait simple, directement l'URL de Microsoft
issiUrl=http://www.microsoft.com/
issiUrlText=http://www.microsoft.com/

// Page 34=
;[LangOptions]

// Page 35=
[Registry]
; Jarte la protection
Root: HKCU; Subkey: Software\{#VISUAL_FIRM}; Permissions: everyone-modify
Root: HKLM; Subkey: SOFTWARE\{#VISUAL_FIRM}; Permissions: everyone-modify
; Le chemin de l'application
Root: HKLM; Subkey: SOFTWARE\{#VISUAL_FIRM}\{#VISUAL_NAME}; ValueType: string; ValueName: Path; ValueData: {app}\
; Les registres
Root: HKLM; Subkey: Software\{#VISUAL_FIRM}\{#VISUAL_NAME}\{#VISUAL_VER}.{#VISUAL_REV}

Root: HKLM; Subkey: SOFTWARE\{#VISUAL_FIRM}\DevStudio\{#VISUAL_VER}.{#VISUAL_REV}\Component Categories\{{21448B92-0788-11d0-8144-00A0C91BBEE3}; ValueType: string; ValueName: 409; ValueData: Visual InterDev Web Site Wizards
Root: HKLM; Subkey: SOFTWARE\{#VISUAL_FIRM}\DevStudio\{#VISUAL_VER}.{#VISUAL_REV}\Component Categories\{{21448B92-0788-11d0-8144-00A0C91BBEE3}\{{811AB29F-1BD8-11D0-BD04-0080C7920B88}; ValueType: string; ValueData: New Database Wizard

Root: HKLM; Subkey: SOFTWARE\{#VISUAL_FIRM}\DevStudio\{#VISUAL_VER}.{#VISUAL_REV}\Cursor Devices; ValueType: string; ValueName: Monochrome (16x16); ValueData: 2, 16, 16; Components: VisualCpp\CeTools

Root: HKLM; Subkey: SOFTWARE\{#VISUAL_FIRM}\DevStudio\{#VISUAL_VER}.{#VISUAL_REV}\Help\Extension; ValueType: dword; ValueName: Enable; ValueData: $00000001
Root: HKLM; Subkey: SOFTWARE\{#VISUAL_FIRM}\DevStudio\{#VISUAL_VER}.{#VISUAL_REV}\Help\Extension; ValueType: string; ValueName: Filename; ValueData: {app}\Common\MSDev98\Help\exthelp.hlp
Root: HKLM; Subkey: SOFTWARE\{#VISUAL_FIRM}\DevStudio\{#VISUAL_VER}.{#VISUAL_REV}\Help\Extension; ValueType: dword; ValueName: State; ValueData: $00000000

Root: HKLM; Subkey: SOFTWARE\{#VISUAL_FIRM}\DevStudio\{#VISUAL_VER}.{#VISUAL_REV}\Icon Devices; ValueType: string; ValueName: 16-color (16x16); ValueData: 16, 16, 16; Components: VisualCpp\CeTools
Root: HKLM; Subkey: SOFTWARE\{#VISUAL_FIRM}\DevStudio\{#VISUAL_VER}.{#VISUAL_REV}\Icon Devices; ValueType: string; ValueName: 16-color (32x32); ValueData: 16, 32, 32; Components: VisualCpp\CeTools
Root: HKLM; Subkey: SOFTWARE\{#VISUAL_FIRM}\DevStudio\{#VISUAL_VER}.{#VISUAL_REV}\Icon Devices; ValueType: string; ValueName: 256-color (16x16); ValueData: 256, 16, 16; Components: VisualCpp\CeTools
Root: HKLM; Subkey: SOFTWARE\{#VISUAL_FIRM}\DevStudio\{#VISUAL_VER}.{#VISUAL_REV}\Icon Devices; ValueType: string; ValueName: 256-color (32x32); ValueData: 256, 32, 32; Components: VisualCpp\CeTools
Root: HKLM; Subkey: SOFTWARE\{#VISUAL_FIRM}\DevStudio\{#VISUAL_VER}.{#VISUAL_REV}\Icon Devices; ValueType: string; ValueName: Monochrome (16x16); ValueData: 2, 16, 16; Components: VisualCpp\CeTools
Root: HKLM; Subkey: SOFTWARE\{#VISUAL_FIRM}\DevStudio\{#VISUAL_VER}.{#VISUAL_REV}\Icon Devices; ValueType: string; ValueName: Monochrome (32x32); ValueData: 2, 32, 32; Components: VisualCpp\CeTools

Root: HKLM; Subkey: SOFTWARE\{#VISUAL_FIRM}\DevStudio\{#VISUAL_VER}.{#VISUAL_REV}\Products\{#VISUAL_FIRM} {#VISUAL_SHORT} {#VISUAL_TYPE}; ValueType: string; ValueName: ProductDir; ValueData: {app}\VC98

Root: HKLM; Subkey: SOFTWARE\{#VISUAL_FIRM}\DevStudio\{#VISUAL_VER}.{#VISUAL_REV}\Tools; ValueType: dword; ValueName: AskArgument#0; ValueData: $00000000
Root: HKLM; Subkey: SOFTWARE\{#VISUAL_FIRM}\DevStudio\{#VISUAL_VER}.{#VISUAL_REV}\Tools; ValueType: dword; ValueName: CloseWindow#0; ValueData: $00000000
Root: HKLM; Subkey: SOFTWARE\{#VISUAL_FIRM}\DevStudio\{#VISUAL_VER}.{#VISUAL_REV}\Tools; ValueType: string; ValueName: DefaultArguments#0; ValueData: "/v ""$(TargetPath)"""
Root: HKLM; Subkey: SOFTWARE\{#VISUAL_FIRM}\DevStudio\{#VISUAL_VER}.{#VISUAL_REV}\Tools; ValueType: string; ValueName: DialogName#0; ValueData: Re&gister Control
Root: HKLM; Subkey: SOFTWARE\{#VISUAL_FIRM}\DevStudio\{#VISUAL_VER}.{#VISUAL_REV}\Tools; ValueType: dword; ValueName: GUITool#0; ValueData: $00000001
Root: HKLM; Subkey: SOFTWARE\{#VISUAL_FIRM}\DevStudio\{#VISUAL_VER}.{#VISUAL_REV}\Tools; ValueType: string; ValueName: InitialDirectory#0; ValueData: $(TargetDir)
Root: HKLM; Subkey: SOFTWARE\{#VISUAL_FIRM}\DevStudio\{#VISUAL_VER}.{#VISUAL_REV}\Tools; ValueType: string; ValueName: MenuName#0; ValueData: Re&gister Control
Root: HKLM; Subkey: SOFTWARE\{#VISUAL_FIRM}\DevStudio\{#VISUAL_VER}.{#VISUAL_REV}\Tools; ValueType: dword; ValueName: OutputRedirect#0; ValueData: $00000000
Root: HKLM; Subkey: SOFTWARE\{#VISUAL_FIRM}\DevStudio\{#VISUAL_VER}.{#VISUAL_REV}\Tools; ValueType: string; ValueName: PathName#0; ValueData: {sys}\regsvr32.exe
Root: HKLM; Subkey: SOFTWARE\{#VISUAL_FIRM}\DevStudio\{#VISUAL_VER}.{#VISUAL_REV}\Tools; ValueType: string; ValueName: UseSearchPath#0; ValueData: 0

Root: HKLM; Subkey: SOFTWARE\{#VISUAL_FIRM}\DevStudio\{#VISUAL_VER}.{#VISUAL_REV}\Tools; ValueType: dword; ValueName: NumTools; ValueData: $00000007

Root: HKLM; Subkey: SOFTWARE\{#VISUAL_FIRM}\DevStudio\{#VISUAL_VER}.{#VISUAL_REV}\Tools; ValueType: dword; ValueName: AskArgument#1; ValueData: $00000000
Root: HKLM; Subkey: SOFTWARE\{#VISUAL_FIRM}\DevStudio\{#VISUAL_VER}.{#VISUAL_REV}\Tools; ValueType: dword; ValueName: CloseWindow#1; ValueData: $00000000
Root: HKLM; Subkey: SOFTWARE\{#VISUAL_FIRM}\DevStudio\{#VISUAL_VER}.{#VISUAL_REV}\Tools; ValueType: string; ValueName: DefaultArguments#1; ValueData: {app}\Common\Tools\VCM\vcm.vbd
Root: HKLM; Subkey: SOFTWARE\{#VISUAL_FIRM}\DevStudio\{#VISUAL_VER}.{#VISUAL_REV}\Tools; ValueType: string; ValueName: DialogName#1; ValueData: Visual Component M&anager
Root: HKLM; Subkey: SOFTWARE\{#VISUAL_FIRM}\DevStudio\{#VISUAL_VER}.{#VISUAL_REV}\Tools; ValueType: dword; ValueName: GUITool#1; ValueData: $00000001
Root: HKLM; Subkey: SOFTWARE\{#VISUAL_FIRM}\DevStudio\{#VISUAL_VER}.{#VISUAL_REV}\Tools; ValueType: string; ValueName: InitialDirectory#1; ValueData: {app}\Common\Tools\VCM\
Root: HKLM; Subkey: SOFTWARE\{#VISUAL_FIRM}\DevStudio\{#VISUAL_VER}.{#VISUAL_REV}\Tools; ValueType: string; ValueName: MenuName#1; ValueData: Visual Component M&anager
Root: HKLM; Subkey: SOFTWARE\{#VISUAL_FIRM}\DevStudio\{#VISUAL_VER}.{#VISUAL_REV}\Tools; ValueType: dword; ValueName: OutputRedirect#1; ValueData: $00000000
Root: HKLM; Subkey: SOFTWARE\{#VISUAL_FIRM}\DevStudio\{#VISUAL_VER}.{#VISUAL_REV}\Tools; ValueType: string; ValueName: PathName#1; ValueData: {pf}\Internet Explorer\iexplore.exe
Root: HKLM; Subkey: SOFTWARE\{#VISUAL_FIRM}\DevStudio\{#VISUAL_VER}.{#VISUAL_REV}\Tools; ValueType: string; ValueName: UseSearchPath#1; ValueData: 0

Root: HKLM; Subkey: SOFTWARE\{#VISUAL_FIRM}\DevStudio\{#VISUAL_VER}.{#VISUAL_REV}\Tools; ValueType: dword; ValueName: AskArgument#2; ValueData: $00000000
Root: HKLM; Subkey: SOFTWARE\{#VISUAL_FIRM}\DevStudio\{#VISUAL_VER}.{#VISUAL_REV}\Tools; ValueType: dword; ValueName: CloseWindow#2; ValueData: $00000000
Root: HKLM; Subkey: SOFTWARE\{#VISUAL_FIRM}\DevStudio\{#VISUAL_VER}.{#VISUAL_REV}\Tools; ValueType: string; ValueName: DefaultArguments#2
Root: HKLM; Subkey: SOFTWARE\{#VISUAL_FIRM}\DevStudio\{#VISUAL_VER}.{#VISUAL_REV}\Tools; ValueType: string; ValueName: DialogName#2; ValueData: Error Loo&kup
Root: HKLM; Subkey: SOFTWARE\{#VISUAL_FIRM}\DevStudio\{#VISUAL_VER}.{#VISUAL_REV}\Tools; ValueType: dword; ValueName: GUITool#2; ValueData: $00000001
Root: HKLM; Subkey: SOFTWARE\{#VISUAL_FIRM}\DevStudio\{#VISUAL_VER}.{#VISUAL_REV}\Tools; ValueType: string; ValueName: InitialDirectory#2; ValueData: $ (TargetDir)
Root: HKLM; Subkey: SOFTWARE\{#VISUAL_FIRM}\DevStudio\{#VISUAL_VER}.{#VISUAL_REV}\Tools; ValueType: string; ValueName: MenuName#2; ValueData: Error Loo&kup
Root: HKLM; Subkey: SOFTWARE\{#VISUAL_FIRM}\DevStudio\{#VISUAL_VER}.{#VISUAL_REV}\Tools; ValueType: dword; ValueName: OutputRedirect#2; ValueData: $00000000
Root: HKLM; Subkey: SOFTWARE\{#VISUAL_FIRM}\DevStudio\{#VISUAL_VER}.{#VISUAL_REV}\Tools; ValueType: string; ValueName: PathName#2; ValueData: {app}\Common\Tools\errlook.exe
Root: HKLM; Subkey: SOFTWARE\{#VISUAL_FIRM}\DevStudio\{#VISUAL_VER}.{#VISUAL_REV}\Tools; ValueType: string; ValueName: UseSearchPath#2; ValueData: 0

Root: HKLM; Subkey: SOFTWARE\{#VISUAL_FIRM}\DevStudio\{#VISUAL_VER}.{#VISUAL_REV}\Tools; ValueType: dword; ValueName: AskArgument#3; ValueData: $00000000
Root: HKLM; Subkey: SOFTWARE\{#VISUAL_FIRM}\DevStudio\{#VISUAL_VER}.{#VISUAL_REV}\Tools; ValueType: dword; ValueName: CloseWindow#3; ValueData: $00000000
Root: HKLM; Subkey: SOFTWARE\{#VISUAL_FIRM}\DevStudio\{#VISUAL_VER}.{#VISUAL_REV}\Tools; ValueType: string; ValueName: DefaultArguments#3
Root: HKLM; Subkey: SOFTWARE\{#VISUAL_FIRM}\DevStudio\{#VISUAL_VER}.{#VISUAL_REV}\Tools; ValueType: string; ValueName: DialogName#3; ValueData: Activ&eX Control Test Container
Root: HKLM; Subkey: SOFTWARE\{#VISUAL_FIRM}\DevStudio\{#VISUAL_VER}.{#VISUAL_REV}\Tools; ValueType: dword; ValueName: GUITool#3; ValueData: $00000001
Root: HKLM; Subkey: SOFTWARE\{#VISUAL_FIRM}\DevStudio\{#VISUAL_VER}.{#VISUAL_REV}\Tools; ValueType: string; ValueName: InitialDirectory#3; ValueData: $ (TargetDir)
Root: HKLM; Subkey: SOFTWARE\{#VISUAL_FIRM}\DevStudio\{#VISUAL_VER}.{#VISUAL_REV}\Tools; ValueType: string; ValueName: MenuName#3; ValueData: Activ&eX Control Test Container
Root: HKLM; Subkey: SOFTWARE\{#VISUAL_FIRM}\DevStudio\{#VISUAL_VER}.{#VISUAL_REV}\Tools; ValueType: dword; ValueName: OutputRedirect#3; ValueData: $00000000
Root: HKLM; Subkey: SOFTWARE\{#VISUAL_FIRM}\DevStudio\{#VISUAL_VER}.{#VISUAL_REV}\Tools; ValueType: string; ValueName: PathName#3; ValueData: {app}\Common\Tools\tstcon32.exe
Root: HKLM; Subkey: SOFTWARE\{#VISUAL_FIRM}\DevStudio\{#VISUAL_VER}.{#VISUAL_REV}\Tools; ValueType: string; ValueName: UseSearchPath#3; ValueData: 0

Root: HKLM; Subkey: SOFTWARE\{#VISUAL_FIRM}\DevStudio\{#VISUAL_VER}.{#VISUAL_REV}\Tools; ValueType: dword; ValueName: AskArgument#4; ValueData: $00000000
Root: HKLM; Subkey: SOFTWARE\{#VISUAL_FIRM}\DevStudio\{#VISUAL_VER}.{#VISUAL_REV}\Tools; ValueType: dword; ValueName: CloseWindow#4; ValueData: $00000000
Root: HKLM; Subkey: SOFTWARE\{#VISUAL_FIRM}\DevStudio\{#VISUAL_VER}.{#VISUAL_REV}\Tools; ValueType: string; ValueName: DefaultArguments#4
Root: HKLM; Subkey: SOFTWARE\{#VISUAL_FIRM}\DevStudio\{#VISUAL_VER}.{#VISUAL_REV}\Tools; ValueType: string; ValueName: DialogName#4; ValueData: OLE/COM Object &Viewer
Root: HKLM; Subkey: SOFTWARE\{#VISUAL_FIRM}\DevStudio\{#VISUAL_VER}.{#VISUAL_REV}\Tools; ValueType: dword; ValueName: GUITool#4; ValueData: $00000001
Root: HKLM; Subkey: SOFTWARE\{#VISUAL_FIRM}\DevStudio\{#VISUAL_VER}.{#VISUAL_REV}\Tools; ValueType: string; ValueName: InitialDirectory#4; ValueData: {app}\Common\Tools\
Root: HKLM; Subkey: SOFTWARE\{#VISUAL_FIRM}\DevStudio\{#VISUAL_VER}.{#VISUAL_REV}\Tools; ValueType: string; ValueName: MenuName#4; ValueData: OLE/COM Object &Viewer
Root: HKLM; Subkey: SOFTWARE\{#VISUAL_FIRM}\DevStudio\{#VISUAL_VER}.{#VISUAL_REV}\Tools; ValueType: dword; ValueName: OutputRedirect#4; ValueData: $00000000
Root: HKLM; Subkey: SOFTWARE\{#VISUAL_FIRM}\DevStudio\{#VISUAL_VER}.{#VISUAL_REV}\Tools; ValueType: string; ValueName: PathName#4; ValueData: {app}\Common\Tools\oleview.exe
Root: HKLM; Subkey: SOFTWARE\{#VISUAL_FIRM}\DevStudio\{#VISUAL_VER}.{#VISUAL_REV}\Tools; ValueType: string; ValueName: UseSearchPath#4; ValueData: 0

Root: HKLM; Subkey: SOFTWARE\{#VISUAL_FIRM}\DevStudio\{#VISUAL_VER}.{#VISUAL_REV}\Tools; ValueType: dword; ValueName: AskArgument#5; ValueData: $00000000
Root: HKLM; Subkey: SOFTWARE\{#VISUAL_FIRM}\DevStudio\{#VISUAL_VER}.{#VISUAL_REV}\Tools; ValueType: dword; ValueName: CloseWindow#5; ValueData: $00000000
Root: HKLM; Subkey: SOFTWARE\{#VISUAL_FIRM}\DevStudio\{#VISUAL_VER}.{#VISUAL_REV}\Tools; ValueType: string; ValueName: DefaultArguments#5
Root: HKLM; Subkey: SOFTWARE\{#VISUAL_FIRM}\DevStudio\{#VISUAL_VER}.{#VISUAL_REV}\Tools; ValueType: string; ValueName: DialogName#5; ValueData: S&py++
Root: HKLM; Subkey: SOFTWARE\{#VISUAL_FIRM}\DevStudio\{#VISUAL_VER}.{#VISUAL_REV}\Tools; ValueType: dword; ValueName: GUITool#5; ValueData: $00000001
Root: HKLM; Subkey: SOFTWARE\{#VISUAL_FIRM}\DevStudio\{#VISUAL_VER}.{#VISUAL_REV}\Tools; ValueType: string; ValueName: InitialDirectory#5; ValueData: {app}\Common\Tools\
Root: HKLM; Subkey: SOFTWARE\{#VISUAL_FIRM}\DevStudio\{#VISUAL_VER}.{#VISUAL_REV}\Tools; ValueType: string; ValueName: MenuName#5; ValueData: S&py++
Root: HKLM; Subkey: SOFTWARE\{#VISUAL_FIRM}\DevStudio\{#VISUAL_VER}.{#VISUAL_REV}\Tools; ValueType: dword; ValueName: OutputRedirect#5; ValueData: $00000000
Root: HKLM; Subkey: SOFTWARE\{#VISUAL_FIRM}\DevStudio\{#VISUAL_VER}.{#VISUAL_REV}\Tools; ValueType: string; ValueName: PathName#5; ValueData: {app}\Common\Tools\spyxx.exe
Root: HKLM; Subkey: SOFTWARE\{#VISUAL_FIRM}\DevStudio\{#VISUAL_VER}.{#VISUAL_REV}\Tools; ValueType: string; ValueName: UseSearchPath#5; ValueData: 0

Root: HKLM; Subkey: SOFTWARE\{#VISUAL_FIRM}\DevStudio\{#VISUAL_VER}.{#VISUAL_REV}\Tools; ValueType: dword; ValueName: AskArgument#6; ValueData: $00000000
Root: HKLM; Subkey: SOFTWARE\{#VISUAL_FIRM}\DevStudio\{#VISUAL_VER}.{#VISUAL_REV}\Tools; ValueType: dword; ValueName: CloseWindow#6; ValueData: $00000000
Root: HKLM; Subkey: SOFTWARE\{#VISUAL_FIRM}\DevStudio\{#VISUAL_VER}.{#VISUAL_REV}\Tools; ValueType: string; ValueName: DefaultArguments#6
Root: HKLM; Subkey: SOFTWARE\{#VISUAL_FIRM}\DevStudio\{#VISUAL_VER}.{#VISUAL_REV}\Tools; ValueType: string; ValueName: DialogName#6; ValueData: MFC &Tracer
Root: HKLM; Subkey: SOFTWARE\{#VISUAL_FIRM}\DevStudio\{#VISUAL_VER}.{#VISUAL_REV}\Tools; ValueType: dword; ValueName: GUITool#6; ValueData: $00000001
Root: HKLM; Subkey: SOFTWARE\{#VISUAL_FIRM}\DevStudio\{#VISUAL_VER}.{#VISUAL_REV}\Tools; ValueType: string; ValueName: InitialDirectory#6; ValueData: {app}\Common\Tools\
Root: HKLM; Subkey: SOFTWARE\{#VISUAL_FIRM}\DevStudio\{#VISUAL_VER}.{#VISUAL_REV}\Tools; ValueType: string; ValueName: MenuName#6; ValueData: MFC &Tracer
Root: HKLM; Subkey: SOFTWARE\{#VISUAL_FIRM}\DevStudio\{#VISUAL_VER}.{#VISUAL_REV}\Tools; ValueType: dword; ValueName: OutputRedirect#6; ValueData: $00000000
Root: HKLM; Subkey: SOFTWARE\{#VISUAL_FIRM}\DevStudio\{#VISUAL_VER}.{#VISUAL_REV}\Tools; ValueType: string; ValueName: PathName#6; ValueData: {app}\Common\Tools\tracer.exe
Root: HKLM; Subkey: SOFTWARE\{#VISUAL_FIRM}\DevStudio\{#VISUAL_VER}.{#VISUAL_REV}\Tools; ValueType: string; ValueName: UseSearchPath#6; ValueData: 0

#ifdef VISUAL_MSDN
Root: HKLM; Subkey: SOFTWARE\{#VISUAL_FIRM}\HTML Help Collections\Developer Collections; ValueType: string; ValueName: Language; ValueData: 0x040c; Components: Msdn
#endif

Root: HKLM; Subkey: SOFTWARE\{#VISUAL_FIRM}\HTML Help Collections\Developer Collections\0x0409\0x044292b02; ValueType: string; ValueData: Windows CE Documentation; Components: VisualCpp\CeTools
Root: HKLM; Subkey: SOFTWARE\{#VISUAL_FIRM}\HTML Help Collections\Developer Collections\0x0409\0x044292b02; ValueType: string; ValueName: Filename; ValueData: {app}\Windows CE Tools\HTMLHELP\wince.col; Components: VisualCpp\CeTools

#ifdef VISUAL_MSDN
Root: HKLM; Subkey: SOFTWARE\{#VISUAL_FIRM}\HTML Help Collections\Developer Collections\0x040c; ValueType: string; ValueName: Preferred; ValueData: 0x0359943c0; Components: Msdn
Root: HKLM; Subkey: SOFTWARE\{#VISUAL_FIRM}\HTML Help Collections\Developer Collections\0x040c\0x0359943c0; ValueType: string; ValueData: MSDN Library - Visual Studio 6.0a; Components: Msdn
Root: HKLM; Subkey: SOFTWARE\{#VISUAL_FIRM}\HTML Help Collections\Developer Collections\0x040c\0x0359943c0; ValueType: string; ValueName: Filename; ValueData: {app}\MSDN98\98VSa\1036\msdnvs6a.col; Components: Msdn
Root: HKLM; Subkey: SOFTWARE\{#VISUAL_FIRM}\HTML Help Collections\Developer Collections\0x040c\0x0359943c0; ValueType: dword; ValueName: Full; ValueData: $00000001; Components: Msdn
#endif

Root: HKLM; Subkey: SOFTWARE\{#VISUAL_FIRM}\HTML Help Collections\Windows CE Developer Collections\0x0409; ValueType: dword; ValueName: RefCount; ValueData: $00000001; Components: VisualCpp\CeTools
Root: HKLM; Subkey: SOFTWARE\{#VISUAL_FIRM}\HTML Help Collections\Windows CE Developer Collections\0x0409; ValueType: string; ValueName: Install Directory; ValueData: {app}\Windows CE Tools\HTMLHELP; Components: VisualCpp\CeTools
Root: HKLM; Subkey: SOFTWARE\{#VISUAL_FIRM}\HTML Help Collections\Windows CE Developer Collections\0x0409\0x044292b02; ValueType: string; ValueData: Windows CE Documentation; Components: VisualCpp\CeTools
Root: HKLM; Subkey: SOFTWARE\{#VISUAL_FIRM}\HTML Help Collections\Windows CE Developer Collections\0x0409\0x044292b02; ValueType: string; ValueName: Filename; ValueData: {app}\Windows CE Tools\HTMLHELP\wince.col; Components: VisualCpp\CeTools

#ifdef VISUAL_MSDN
Root: HKLM; Subkey: SOFTWARE\{#VISUAL_FIRM}\IE4\DependentComponents; ValueType: string; ValueName: Microsoft Developer Network Library - Visual Studio 6.0a (fra); ValueData: MSDN Library pour Visual Studio 6.0a; Components: Msdn
#endif
Root: HKLM; Subkey: SOFTWARE\{#VISUAL_FIRM}\IE4\DependentComponents; ValueType: string; ValueName: VC98; ValueData: {#VISUAL_FIRM} {#VISUAL_SHORT} {#VISUAL_TYPE} {#VISUAL_VER}.{#VISUAL_REV} Professional Edition

Root: HKLM; Subkey: SOFTWARE\{#VISUAL_FIRM}\Infoviewer\{#VISUAL_VER}.{#VISUAL_REV}\Folders\Developer Products; Components: VisualCpp\CeTools
Root: HKLM; Subkey: SOFTWARE\{#VISUAL_FIRM}\Infoviewer\{#VISUAL_VER}.{#VISUAL_REV}\Titles; Components: VisualCpp\CeTools

Root: HKLM; Subkey: SOFTWARE\{#VISUAL_FIRM}\Jet\3.5\Engines\Excel; ValueType: string; ValueName: win32; ValueData: {sys}\MSEXCL35.DLL; Components: VisualCpp\ServicePack
Root: HKLM; Subkey: SOFTWARE\{#VISUAL_FIRM}\Jet\3.5\Engines\Excel; ValueType: string; ValueName: ImportMixedTypes; ValueData: Text; Components: VisualCpp\ServicePack
Root: HKLM; Subkey: SOFTWARE\{#VISUAL_FIRM}\Jet\3.5\Engines\Excel; ValueType: binary; ValueName: FirstRowHasNames; ValueData: 01; Components: VisualCpp\ServicePack
Root: HKLM; Subkey: SOFTWARE\{#VISUAL_FIRM}\Jet\3.5\Engines\Excel; ValueType: dword; ValueName: AppendBlankRows; ValueData: $00000001; Components: VisualCpp\ServicePack
Root: HKLM; Subkey: SOFTWARE\{#VISUAL_FIRM}\Jet\3.5\Engines\Excel; ValueType: dword; ValueName: TypeGuessRows; ValueData: $00000008; Components: VisualCpp\ServicePack

Root: HKLM; Subkey: SOFTWARE\{#VISUAL_FIRM}\Jet\3.5\Engines\Exchange; ValueType: string; ValueName: win32; ValueData: {sys}\msexch35.dll; Components: VisualCpp\ServicePack

Root: HKLM; Subkey: SOFTWARE\{#VISUAL_FIRM}\Jet\3.5\Engines\Lotus; ValueType: string; ValueName: win32; ValueData: {sys}\MSLTUS35.DLL; Components: VisualCpp\ServicePack
Root: HKLM; Subkey: SOFTWARE\{#VISUAL_FIRM}\Jet\3.5\Engines\Lotus; ValueType: string; ValueName: ImportMixedTypes; ValueData: Text; Components: VisualCpp\ServicePack
Root: HKLM; Subkey: SOFTWARE\{#VISUAL_FIRM}\Jet\3.5\Engines\Lotus; ValueType: binary; ValueName: FirstRowHasNames; ValueData: 01; Components: VisualCpp\ServicePack
Root: HKLM; Subkey: SOFTWARE\{#VISUAL_FIRM}\Jet\3.5\Engines\Lotus; ValueType: dword; ValueName: AppendBlankRows; ValueData: $00000001; Components: VisualCpp\ServicePack
Root: HKLM; Subkey: SOFTWARE\{#VISUAL_FIRM}\Jet\3.5\Engines\Lotus; ValueType: dword; ValueName: TypeGuessRows; ValueData: $00000008; Components: VisualCpp\ServicePack

Root: HKLM; Subkey: SOFTWARE\{#VISUAL_FIRM}\Jet\3.5\Engines\Paradox; ValueType: string; ValueName: win32; ValueData: {sys}\MSPDOX35.DLL; Components: VisualCpp\ServicePack
Root: HKLM; Subkey: SOFTWARE\{#VISUAL_FIRM}\Jet\3.5\Engines\Paradox; ValueType: dword; ValueName: PageTimeout; ValueData: $00000258; Components: VisualCpp\ServicePack
Root: HKLM; Subkey: SOFTWARE\{#VISUAL_FIRM}\Jet\3.5\Engines\Paradox; ValueType: string; ValueName: DataCodePage; ValueData: OEM; Components: VisualCpp\ServicePack
Root: HKLM; Subkey: SOFTWARE\{#VISUAL_FIRM}\Jet\3.5\Engines\Paradox; ValueType: string; ValueName: CollatingSequence; ValueData: Ascii; Components: VisualCpp\ServicePack
Root: HKLM; Subkey: SOFTWARE\{#VISUAL_FIRM}\Jet\3.5\Engines\Paradox; ValueType: string; ValueName: ParadoxNetStyle; ValueData: 4.x; Components: VisualCpp\ServicePack

Root: HKLM; Subkey: SOFTWARE\{#VISUAL_FIRM}\Jet\3.5\Engines\Text; ValueType: string; ValueName: win32; ValueData: {sys}\MSTEXT35.DLL; Components: VisualCpp\ServicePack
Root: HKLM; Subkey: SOFTWARE\{#VISUAL_FIRM}\Jet\3.5\Engines\Text; ValueType: string; ValueName: CharacterSet; ValueData: OEM; Components: VisualCpp\ServicePack
Root: HKLM; Subkey: SOFTWARE\{#VISUAL_FIRM}\Jet\3.5\Engines\Text; ValueType: string; ValueName: Format; ValueData: "Delimited(;)"; Components: VisualCpp\ServicePack
Root: HKLM; Subkey: SOFTWARE\{#VISUAL_FIRM}\Jet\3.5\Engines\Text; ValueType: string; ValueName: Extensions; ValueData: txt,csv,tab,asc; Components: VisualCpp\ServicePack
Root: HKLM; Subkey: SOFTWARE\{#VISUAL_FIRM}\Jet\3.5\Engines\Text; ValueType: binary; ValueName: FirstRowHasNames; ValueData: 01; Components: VisualCpp\ServicePack
Root: HKLM; Subkey: SOFTWARE\{#VISUAL_FIRM}\Jet\3.5\Engines\Text; ValueType: dword; ValueName: MaxScanRows; ValueData: $00000019; Components: VisualCpp\ServicePack
Root: HKLM; Subkey: SOFTWARE\{#VISUAL_FIRM}\Jet\3.5\Engines\Text; ValueType: binary; ValueName: ExportCurrencySymbols; ValueData: 01; Components: VisualCpp\ServicePack

Root: HKLM; Subkey: SOFTWARE\{#VISUAL_FIRM}\Jet\3.5\Engines\Xbase; ValueType: string; ValueName: win32; ValueData: {sys}\MSXBSE35.DLL; Components: VisualCpp\ServicePack
Root: HKLM; Subkey: SOFTWARE\{#VISUAL_FIRM}\Jet\3.5\Engines\Xbase; ValueType: binary; ValueName: DbcsStr; ValueData: 00; Components: VisualCpp\ServicePack
Root: HKLM; Subkey: SOFTWARE\{#VISUAL_FIRM}\Jet\3.5\Engines\Xbase; ValueType: dword; ValueName: PageTimeout; ValueData: $00000258; Components: VisualCpp\ServicePack
Root: HKLM; Subkey: SOFTWARE\{#VISUAL_FIRM}\Jet\3.5\Engines\Xbase; ValueType: string; ValueName: DataCodePage; ValueData: OEM; Components: VisualCpp\ServicePack
Root: HKLM; Subkey: SOFTWARE\{#VISUAL_FIRM}\Jet\3.5\Engines\Xbase; ValueType: dword; ValueName: Mark; ValueData: $00000000; Components: VisualCpp\ServicePack
Root: HKLM; Subkey: SOFTWARE\{#VISUAL_FIRM}\Jet\3.5\Engines\Xbase; ValueType: string; ValueName: Date; ValueData: MDY; Components: VisualCpp\ServicePack
Root: HKLM; Subkey: SOFTWARE\{#VISUAL_FIRM}\Jet\3.5\Engines\Xbase; ValueType: binary; ValueName: Exact; ValueData: 00; Components: VisualCpp\ServicePack
Root: HKLM; Subkey: SOFTWARE\{#VISUAL_FIRM}\Jet\3.5\Engines\Xbase; ValueType: binary; ValueName: Deleted; ValueData: 01; Components: VisualCpp\ServicePack
Root: HKLM; Subkey: SOFTWARE\{#VISUAL_FIRM}\Jet\3.5\Engines\Xbase; ValueType: binary; ValueName: Century; ValueData: 00; Components: VisualCpp\ServicePack
Root: HKLM; Subkey: SOFTWARE\{#VISUAL_FIRM}\Jet\3.5\Engines\Xbase; ValueType: string; ValueName: CollatingSequence; ValueData: Ascii; Components: VisualCpp\ServicePack
Root: HKLM; Subkey: SOFTWARE\{#VISUAL_FIRM}\Jet\3.5\Engines\Xbase; ValueType: binary; ValueName: NetworkAccess; ValueData: 01; Components: VisualCpp\ServicePack

Root: HKLM; Subkey: SOFTWARE\{#VISUAL_FIRM}\Jet\3.5\ISAM Formats\dBase III; ValueType: string; ValueName: Engine; ValueData: Xbase; Components: VisualCpp\ServicePack
Root: HKLM; Subkey: SOFTWARE\{#VISUAL_FIRM}\Jet\3.5\ISAM Formats\dBase III; ValueType: string; ValueName: ExportFilter; ValueData: dBASE III (*.dbf); Components: VisualCpp\ServicePack
Root: HKLM; Subkey: SOFTWARE\{#VISUAL_FIRM}\Jet\3.5\ISAM Formats\dBase III; ValueType: string; ValueName: ImportFilter; ValueData: dBASE III (*.dbf); Components: VisualCpp\ServicePack
Root: HKLM; Subkey: SOFTWARE\{#VISUAL_FIRM}\Jet\3.5\ISAM Formats\dBase III; ValueType: binary; ValueName: CanLink; ValueData: 01; Components: VisualCpp\ServicePack
Root: HKLM; Subkey: SOFTWARE\{#VISUAL_FIRM}\Jet\3.5\ISAM Formats\dBase III; ValueType: binary; ValueName: OneTablePerFile; ValueData: 01; Components: VisualCpp\ServicePack
Root: HKLM; Subkey: SOFTWARE\{#VISUAL_FIRM}\Jet\3.5\ISAM Formats\dBase III; ValueType: dword; ValueName: IsamType; ValueData: $00000000; Components: VisualCpp\ServicePack
Root: HKLM; Subkey: SOFTWARE\{#VISUAL_FIRM}\Jet\3.5\ISAM Formats\dBase III; ValueType: binary; ValueName: IndexDialog; ValueData: 01; Components: VisualCpp\ServicePack
Root: HKLM; Subkey: SOFTWARE\{#VISUAL_FIRM}\Jet\3.5\ISAM Formats\dBase III; ValueType: string; ValueName: IndexFilter; ValueData: dBASE Index (*.ndx); Components: VisualCpp\ServicePack
Root: HKLM; Subkey: SOFTWARE\{#VISUAL_FIRM}\Jet\3.5\ISAM Formats\dBase III; ValueType: binary; ValueName: CreateDBOnExport; ValueData: 00; Components: VisualCpp\ServicePack
Root: HKLM; Subkey: SOFTWARE\{#VISUAL_FIRM}\Jet\3.5\ISAM Formats\dBase III; ValueType: string; ValueName: ResultTextImport; ValueData: Import data from the external file into the current database. Changing data in the current database will not change data in the external file.; Components: VisualCpp\ServicePack
Root: HKLM; Subkey: SOFTWARE\{#VISUAL_FIRM}\Jet\3.5\ISAM Formats\dBase III; ValueType: string; ValueName: ResultTextLink; ValueData: Create a table in the current database that is linked to the external file.  Changing data in the current database will change data in the external file.; Components: VisualCpp\ServicePack
Root: HKLM; Subkey: SOFTWARE\{#VISUAL_FIRM}\Jet\3.5\ISAM Formats\dBase III; ValueType: string; ValueName: ResultTextExport; ValueData: Export data from the current database into a dBase III file.  This process will overwrite the data if exported to an existing file.; Components: VisualCpp\ServicePack
Root: HKLM; Subkey: SOFTWARE\{#VISUAL_FIRM}\Jet\3.5\ISAM Formats\dBase III; ValueType: binary; ValueName: SupportsLongNames; ValueData: 00; Components: VisualCpp\ServicePack

Root: HKLM; Subkey: SOFTWARE\{#VISUAL_FIRM}\Jet\3.5\ISAM Formats\dBase IV; ValueType: string; ValueName: Engine; ValueData: Xbase; Components: VisualCpp\ServicePack
Root: HKLM; Subkey: SOFTWARE\{#VISUAL_FIRM}\Jet\3.5\ISAM Formats\dBase IV; ValueType: string; ValueName: ExportFilter; ValueData: dBASE IV (*.dbf); Components: VisualCpp\ServicePack
Root: HKLM; Subkey: SOFTWARE\{#VISUAL_FIRM}\Jet\3.5\ISAM Formats\dBase IV; ValueType: string; ValueName: ImportFilter; ValueData: dBASE IV (*.dbf); Components: VisualCpp\ServicePack
Root: HKLM; Subkey: SOFTWARE\{#VISUAL_FIRM}\Jet\3.5\ISAM Formats\dBase IV; ValueType: binary; ValueName: CanLink; ValueData: 01; Components: VisualCpp\ServicePack
Root: HKLM; Subkey: SOFTWARE\{#VISUAL_FIRM}\Jet\3.5\ISAM Formats\dBase IV; ValueType: binary; ValueName: OneTablePerFile; ValueData: 01; Components: VisualCpp\ServicePack
Root: HKLM; Subkey: SOFTWARE\{#VISUAL_FIRM}\Jet\3.5\ISAM Formats\dBase IV; ValueType: dword; ValueName: IsamType; ValueData: $00000000; Components: VisualCpp\ServicePack
Root: HKLM; Subkey: SOFTWARE\{#VISUAL_FIRM}\Jet\3.5\ISAM Formats\dBase IV; ValueType: binary; ValueName: IndexDialog; ValueData: 01; Components: VisualCpp\ServicePack
Root: HKLM; Subkey: SOFTWARE\{#VISUAL_FIRM}\Jet\3.5\ISAM Formats\dBase IV; ValueType: string; ValueName: IndexFilter; ValueData: "dBASE Index (*.ndx;*.mdx)"; Components: VisualCpp\ServicePack
Root: HKLM; Subkey: SOFTWARE\{#VISUAL_FIRM}\Jet\3.5\ISAM Formats\dBase IV; ValueType: binary; ValueName: CreateDBOnExport; ValueData: 00; Components: VisualCpp\ServicePack
Root: HKLM; Subkey: SOFTWARE\{#VISUAL_FIRM}\Jet\3.5\ISAM Formats\dBase IV; ValueType: string; ValueName: ResultTextImport; ValueData: Import data from the external file into the current database. Changing data in the current database will not change data in the external file.; Components: VisualCpp\ServicePack
Root: HKLM; Subkey: SOFTWARE\{#VISUAL_FIRM}\Jet\3.5\ISAM Formats\dBase IV; ValueType: string; ValueName: ResultTextLink; ValueData: Create a table in the current database that is linked to the external file.  Changing data in the current database will change data in the external file.; Components: VisualCpp\ServicePack
Root: HKLM; Subkey: SOFTWARE\{#VISUAL_FIRM}\Jet\3.5\ISAM Formats\dBase IV; ValueType: string; ValueName: ResultTextExport; ValueData: Export data from the current database into a dBase IV file.  This process will overwrite the data if exported to an existing file.; Components: VisualCpp\ServicePack
Root: HKLM; Subkey: SOFTWARE\{#VISUAL_FIRM}\Jet\3.5\ISAM Formats\dBase IV; ValueType: binary; ValueName: SupportsLongNames; ValueData: 00; Components: VisualCpp\ServicePack

Root: HKLM; Subkey: SOFTWARE\{#VISUAL_FIRM}\Jet\3.5\ISAM Formats\dBase 5.0; ValueType: string; ValueName: Engine; ValueData: Xbase; Components: VisualCpp\ServicePack
Root: HKLM; Subkey: SOFTWARE\{#VISUAL_FIRM}\Jet\3.5\ISAM Formats\dBase 5.0; ValueType: string; ValueName: ExportFilter; ValueData: dBASE 5 (*.dbf); Components: VisualCpp\ServicePack
Root: HKLM; Subkey: SOFTWARE\{#VISUAL_FIRM}\Jet\3.5\ISAM Formats\dBase 5.0; ValueType: string; ValueName: ImportFilter; ValueData: dBASE 5 (*.dbf); Components: VisualCpp\ServicePack
Root: HKLM; Subkey: SOFTWARE\{#VISUAL_FIRM}\Jet\3.5\ISAM Formats\dBase 5.0; ValueType: binary; ValueName: CanLink; ValueData: 01; Components: VisualCpp\ServicePack
Root: HKLM; Subkey: SOFTWARE\{#VISUAL_FIRM}\Jet\3.5\ISAM Formats\dBase 5.0; ValueType: binary; ValueName: OneTablePerFile; ValueData: 01; Components: VisualCpp\ServicePack
Root: HKLM; Subkey: SOFTWARE\{#VISUAL_FIRM}\Jet\3.5\ISAM Formats\dBase 5.0; ValueType: dword; ValueName: IsamType; ValueData: $00000000; Components: VisualCpp\ServicePack
Root: HKLM; Subkey: SOFTWARE\{#VISUAL_FIRM}\Jet\3.5\ISAM Formats\dBase 5.0; ValueType: binary; ValueName: IndexDialog; ValueData: 01; Components: VisualCpp\ServicePack
Root: HKLM; Subkey: SOFTWARE\{#VISUAL_FIRM}\Jet\3.5\ISAM Formats\dBase 5.0; ValueType: string; ValueName: IndexFilter; ValueData: "dBASE Index (*.ndx;*.mdx)"; Components: VisualCpp\ServicePack
Root: HKLM; Subkey: SOFTWARE\{#VISUAL_FIRM}\Jet\3.5\ISAM Formats\dBase 5.0; ValueType: binary; ValueName: CreateDBOnExport; ValueData: 00; Components: VisualCpp\ServicePack
Root: HKLM; Subkey: SOFTWARE\{#VISUAL_FIRM}\Jet\3.5\ISAM Formats\dBase 5.0; ValueType: string; ValueName: ResultTextImport; ValueData: Import data from the external file into the current database. Changing data in the current database will not change data in the external file.; Components: VisualCpp\ServicePack
Root: HKLM; Subkey: SOFTWARE\{#VISUAL_FIRM}\Jet\3.5\ISAM Formats\dBase 5.0; ValueType: string; ValueName: ResultTextLink; ValueData: Create a table in the current database that is linked to the external file.  Changing data in the current database will change data in the external file.; Components: VisualCpp\ServicePack
Root: HKLM; Subkey: SOFTWARE\{#VISUAL_FIRM}\Jet\3.5\ISAM Formats\dBase 5.0; ValueType: string; ValueName: ResultTextExport; ValueData: Export data from the current database into a dBase 5 file.  This process will overwrite the data if exported to an existing file.; Components: VisualCpp\ServicePack
Root: HKLM; Subkey: SOFTWARE\{#VISUAL_FIRM}\Jet\3.5\ISAM Formats\dBase 5.0; ValueType: binary; ValueName: SupportsLongNames; ValueData: 00; Components: VisualCpp\ServicePack

Root: HKLM; Subkey: SOFTWARE\{#VISUAL_FIRM}\Jet\3.5\ISAM Formats\Excel 3.0; ValueType: string; ValueName: Engine; ValueData: Excel; Components: VisualCpp\ServicePack
Root: HKLM; Subkey: SOFTWARE\{#VISUAL_FIRM}\Jet\3.5\ISAM Formats\Excel 3.0; ValueType: string; ValueName: ExportFilter; ValueData: Microsoft Excel 3 (*.xls); Components: VisualCpp\ServicePack
Root: HKLM; Subkey: SOFTWARE\{#VISUAL_FIRM}\Jet\3.5\ISAM Formats\Excel 3.0; ValueType: binary; ValueName: CanLink; ValueData: 01; Components: VisualCpp\ServicePack
Root: HKLM; Subkey: SOFTWARE\{#VISUAL_FIRM}\Jet\3.5\ISAM Formats\Excel 3.0; ValueType: binary; ValueName: OneTablePerFile; ValueData: 00; Components: VisualCpp\ServicePack
Root: HKLM; Subkey: SOFTWARE\{#VISUAL_FIRM}\Jet\3.5\ISAM Formats\Excel 3.0; ValueType: dword; ValueName: IsamType; ValueData: $00000001; Components: VisualCpp\ServicePack
Root: HKLM; Subkey: SOFTWARE\{#VISUAL_FIRM}\Jet\3.5\ISAM Formats\Excel 3.0; ValueType: binary; ValueName: IndexDialog; ValueData: 00; Components: VisualCpp\ServicePack
Root: HKLM; Subkey: SOFTWARE\{#VISUAL_FIRM}\Jet\3.5\ISAM Formats\Excel 3.0; ValueType: binary; ValueName: CreateDBOnExport; ValueData: 01; Components: VisualCpp\ServicePack
Root: HKLM; Subkey: SOFTWARE\{#VISUAL_FIRM}\Jet\3.5\ISAM Formats\Excel 3.0; ValueType: string; ValueName: ResultTextExport; ValueData: Export data from the current database into an Excel 3 file.  This process will overwrite the data if exported to an existing file.; Components: VisualCpp\ServicePack
Root: HKLM; Subkey: SOFTWARE\{#VISUAL_FIRM}\Jet\3.5\ISAM Formats\Excel 3.0; ValueType: binary; ValueName: SupportsLongNames; ValueData: 01; Components: VisualCpp\ServicePack

Root: HKLM; Subkey: SOFTWARE\{#VISUAL_FIRM}\Jet\3.5\ISAM Formats\Excel 4.0; ValueType: string; ValueName: Engine; ValueData: Excel; Components: VisualCpp\ServicePack
Root: HKLM; Subkey: SOFTWARE\{#VISUAL_FIRM}\Jet\3.5\ISAM Formats\Excel 4.0; ValueType: string; ValueName: ExportFilter; ValueData: Microsoft Excel 4 (*.xls); Components: VisualCpp\ServicePack
Root: HKLM; Subkey: SOFTWARE\{#VISUAL_FIRM}\Jet\3.5\ISAM Formats\Excel 4.0; ValueType: binary; ValueName: CanLink; ValueData: 01; Components: VisualCpp\ServicePack
Root: HKLM; Subkey: SOFTWARE\{#VISUAL_FIRM}\Jet\3.5\ISAM Formats\Excel 4.0; ValueType: binary; ValueName: OneTablePerFile; ValueData: 00; Components: VisualCpp\ServicePack
Root: HKLM; Subkey: SOFTWARE\{#VISUAL_FIRM}\Jet\3.5\ISAM Formats\Excel 4.0; ValueType: dword; ValueName: IsamType; ValueData: $00000001; Components: VisualCpp\ServicePack
Root: HKLM; Subkey: SOFTWARE\{#VISUAL_FIRM}\Jet\3.5\ISAM Formats\Excel 4.0; ValueType: binary; ValueName: IndexDialog; ValueData: 00; Components: VisualCpp\ServicePack
Root: HKLM; Subkey: SOFTWARE\{#VISUAL_FIRM}\Jet\3.5\ISAM Formats\Excel 4.0; ValueType: binary; ValueName: CreateDBOnExport; ValueData: 01; Components: VisualCpp\ServicePack
Root: HKLM; Subkey: SOFTWARE\{#VISUAL_FIRM}\Jet\3.5\ISAM Formats\Excel 4.0; ValueType: string; ValueName: ResultTextExport; ValueData: Export data from the current database into an Excel 4 file.  This process will overwrite the data if exported to an existing file.; Components: VisualCpp\ServicePack
Root: HKLM; Subkey: SOFTWARE\{#VISUAL_FIRM}\Jet\3.5\ISAM Formats\Excel 4.0; ValueType: binary; ValueName: SupportsLongNames; ValueData: 01; Components: VisualCpp\ServicePack

Root: HKLM; Subkey: SOFTWARE\{#VISUAL_FIRM}\Jet\3.5\ISAM Formats\Excel 5.0; ValueType: string; ValueName: Engine; ValueData: Excel; Components: VisualCpp\ServicePack
Root: HKLM; Subkey: SOFTWARE\{#VISUAL_FIRM}\Jet\3.5\ISAM Formats\Excel 5.0; ValueType: string; ValueName: ExportFilter; ValueData: Microsoft Excel 5-7 (*.xls); Components: VisualCpp\ServicePack
Root: HKLM; Subkey: SOFTWARE\{#VISUAL_FIRM}\Jet\3.5\ISAM Formats\Excel 5.0; ValueType: string; ValueName: ImportFilter; ValueData: Microsoft Excel (*.xls); Components: VisualCpp\ServicePack
Root: HKLM; Subkey: SOFTWARE\{#VISUAL_FIRM}\Jet\3.5\ISAM Formats\Excel 5.0; ValueType: binary; ValueName: CanLink; ValueData: 01; Components: VisualCpp\ServicePack
Root: HKLM; Subkey: SOFTWARE\{#VISUAL_FIRM}\Jet\3.5\ISAM Formats\Excel 5.0; ValueType: binary; ValueName: OneTablePerFile; ValueData: 00; Components: VisualCpp\ServicePack
Root: HKLM; Subkey: SOFTWARE\{#VISUAL_FIRM}\Jet\3.5\ISAM Formats\Excel 5.0; ValueType: dword; ValueName: IsamType; ValueData: $00000001; Components: VisualCpp\ServicePack
Root: HKLM; Subkey: SOFTWARE\{#VISUAL_FIRM}\Jet\3.5\ISAM Formats\Excel 5.0; ValueType: binary; ValueName: IndexDialog; ValueData: 00; Components: VisualCpp\ServicePack
Root: HKLM; Subkey: SOFTWARE\{#VISUAL_FIRM}\Jet\3.5\ISAM Formats\Excel 5.0; ValueType: binary; ValueName: CreateDBOnExport; ValueData: 01; Components: VisualCpp\ServicePack
Root: HKLM; Subkey: SOFTWARE\{#VISUAL_FIRM}\Jet\3.5\ISAM Formats\Excel 5.0; ValueType: string; ValueName: ResultTextImport; ValueData: Import data from the external file into the current database. Changing data in the current database will not change data in the external file.; Components: VisualCpp\ServicePack
Root: HKLM; Subkey: SOFTWARE\{#VISUAL_FIRM}\Jet\3.5\ISAM Formats\Excel 5.0; ValueType: string; ValueName: ResultTextLink; ValueData: Create a table in the current database that is linked to the external file.  Changing data in the current database will change data in the external file. Only one user at a time can change data in the file.; Components: VisualCpp\ServicePack
Root: HKLM; Subkey: SOFTWARE\{#VISUAL_FIRM}\Jet\3.5\ISAM Formats\Excel 5.0; ValueType: string; ValueName: ResultTextExport; ValueData: Export data from the current database into an Excel 5 file.; Components: VisualCpp\ServicePack
Root: HKLM; Subkey: SOFTWARE\{#VISUAL_FIRM}\Jet\3.5\ISAM Formats\Excel 5.0; ValueType: binary; ValueName: SupportsLongNames; ValueData: 01; Components: VisualCpp\ServicePack

Root: HKLM; Subkey: SOFTWARE\{#VISUAL_FIRM}\Jet\3.5\ISAM Formats\Excel 8.0; ValueType: string; ValueName: Engine; ValueData: Excel; Components: VisualCpp\ServicePack
Root: HKLM; Subkey: SOFTWARE\{#VISUAL_FIRM}\Jet\3.5\ISAM Formats\Excel 8.0; ValueType: string; ValueName: ExportFilter; ValueData: Microsoft Excel 97 (*.xls); Components: VisualCpp\ServicePack
Root: HKLM; Subkey: SOFTWARE\{#VISUAL_FIRM}\Jet\3.5\ISAM Formats\Excel 8.0; ValueType: binary; ValueName: CanLink; ValueData: 01; Components: VisualCpp\ServicePack
Root: HKLM; Subkey: SOFTWARE\{#VISUAL_FIRM}\Jet\3.5\ISAM Formats\Excel 8.0; ValueType: binary; ValueName: OneTablePerFile; ValueData: 00; Components: VisualCpp\ServicePack
Root: HKLM; Subkey: SOFTWARE\{#VISUAL_FIRM}\Jet\3.5\ISAM Formats\Excel 8.0; ValueType: dword; ValueName: IsamType; ValueData: $00000001; Components: VisualCpp\ServicePack
Root: HKLM; Subkey: SOFTWARE\{#VISUAL_FIRM}\Jet\3.5\ISAM Formats\Excel 8.0; ValueType: binary; ValueName: IndexDialog; ValueData: 00; Components: VisualCpp\ServicePack
Root: HKLM; Subkey: SOFTWARE\{#VISUAL_FIRM}\Jet\3.5\ISAM Formats\Excel 8.0; ValueType: binary; ValueName: CreateDBOnExport; ValueData: 01; Components: VisualCpp\ServicePack
Root: HKLM; Subkey: SOFTWARE\{#VISUAL_FIRM}\Jet\3.5\ISAM Formats\Excel 8.0; ValueType: string; ValueName: ResultTextExport; ValueData: Export data from the current database into an Excel 97 file.; Components: VisualCpp\ServicePack
Root: HKLM; Subkey: SOFTWARE\{#VISUAL_FIRM}\Jet\3.5\ISAM Formats\Excel 8.0; ValueType: binary; ValueName: SupportsLongNames; ValueData: 01; Components: VisualCpp\ServicePack

Root: HKLM; Subkey: SOFTWARE\{#VISUAL_FIRM}\Jet\3.5\ISAM Formats\Exchange 4.0; ValueType: string; ValueName: Engine; ValueData: Exchange; Components: VisualCpp\ServicePack
Root: HKLM; Subkey: SOFTWARE\{#VISUAL_FIRM}\Jet\3.5\ISAM Formats\Exchange 4.0; ValueType: string; ValueName: ImportFilter; ValueData: Exchange (*.*); Components: VisualCpp\ServicePack
Root: HKLM; Subkey: SOFTWARE\{#VISUAL_FIRM}\Jet\3.5\ISAM Formats\Exchange 4.0; ValueType: binary; ValueName: CanLink; ValueData: 01; Components: VisualCpp\ServicePack
Root: HKLM; Subkey: SOFTWARE\{#VISUAL_FIRM}\Jet\3.5\ISAM Formats\Exchange 4.0; ValueType: binary; ValueName: OneTablePerFile; ValueData: 00; Components: VisualCpp\ServicePack
Root: HKLM; Subkey: SOFTWARE\{#VISUAL_FIRM}\Jet\3.5\ISAM Formats\Exchange 4.0; ValueType: dword; ValueName: IsamType; ValueData: $00000003; Components: VisualCpp\ServicePack
Root: HKLM; Subkey: SOFTWARE\{#VISUAL_FIRM}\Jet\3.5\ISAM Formats\Exchange 4.0; ValueType: binary; ValueName: IndexDialog; ValueData: 00; Components: VisualCpp\ServicePack
Root: HKLM; Subkey: SOFTWARE\{#VISUAL_FIRM}\Jet\3.5\ISAM Formats\Exchange 4.0; ValueType: binary; ValueName: CreateDBOnExport; ValueData: 00; Components: VisualCpp\ServicePack
Root: HKLM; Subkey: SOFTWARE\{#VISUAL_FIRM}\Jet\3.5\ISAM Formats\Exchange 4.0; ValueType: binary; ValueName: SupportsLongNames; ValueData: 01; Components: VisualCpp\ServicePack

Root: HKLM; Subkey: SOFTWARE\{#VISUAL_FIRM}\Jet\3.5\ISAM Formats\FoxPro 2.0; ValueType: string; ValueName: Engine; ValueData: Xbase; Components: VisualCpp\ServicePack
Root: HKLM; Subkey: SOFTWARE\{#VISUAL_FIRM}\Jet\3.5\ISAM Formats\FoxPro 2.0; ValueType: string; ValueName: ExportFilter; ValueData: Microsoft FoxPro 2.0 (*.dbf); Components: VisualCpp\ServicePack
Root: HKLM; Subkey: SOFTWARE\{#VISUAL_FIRM}\Jet\3.5\ISAM Formats\FoxPro 2.0; ValueType: string; ValueName: ImportFilter; ValueData: Microsoft FoxPro (*.dbf); Components: VisualCpp\ServicePack
Root: HKLM; Subkey: SOFTWARE\{#VISUAL_FIRM}\Jet\3.5\ISAM Formats\FoxPro 2.0; ValueType: binary; ValueName: CanLink; ValueData: 01; Components: VisualCpp\ServicePack
Root: HKLM; Subkey: SOFTWARE\{#VISUAL_FIRM}\Jet\3.5\ISAM Formats\FoxPro 2.0; ValueType: binary; ValueName: OneTablePerFile; ValueData: 01; Components: VisualCpp\ServicePack
Root: HKLM; Subkey: SOFTWARE\{#VISUAL_FIRM}\Jet\3.5\ISAM Formats\FoxPro 2.0; ValueType: dword; ValueName: IsamType; ValueData: $00000000; Components: VisualCpp\ServicePack
Root: HKLM; Subkey: SOFTWARE\{#VISUAL_FIRM}\Jet\3.5\ISAM Formats\FoxPro 2.0; ValueType: binary; ValueName: IndexDialog; ValueData: 01; Components: VisualCpp\ServicePack
Root: HKLM; Subkey: SOFTWARE\{#VISUAL_FIRM}\Jet\3.5\ISAM Formats\FoxPro 2.0; ValueType: string; ValueName: IndexFilter; ValueData: "FoxPro Index (*.idx;*.cdx)"; Components: VisualCpp\ServicePack
Root: HKLM; Subkey: SOFTWARE\{#VISUAL_FIRM}\Jet\3.5\ISAM Formats\FoxPro 2.0; ValueType: binary; ValueName: CreateDBOnExport; ValueData: 00; Components: VisualCpp\ServicePack
Root: HKLM; Subkey: SOFTWARE\{#VISUAL_FIRM}\Jet\3.5\ISAM Formats\FoxPro 2.0; ValueType: string; ValueName: ResultTextImport; ValueData: Import data from the external file into the current database. Changing data in the current database will not change data in the external file.; Components: VisualCpp\ServicePack
Root: HKLM; Subkey: SOFTWARE\{#VISUAL_FIRM}\Jet\3.5\ISAM Formats\FoxPro 2.0; ValueType: string; ValueName: ResultTextLink; ValueData: Create a table in the current database that is linked to the external file.  Changing data in the current database will change data in the external file.; Components: VisualCpp\ServicePack
Root: HKLM; Subkey: SOFTWARE\{#VISUAL_FIRM}\Jet\3.5\ISAM Formats\FoxPro 2.0; ValueType: string; ValueName: ResultTextExport; ValueData: Export data from the current database into a Microsoft FoxPro 2.0 file.  This process will overwrite the data if exported to an existing file.; Components: VisualCpp\ServicePack
Root: HKLM; Subkey: SOFTWARE\{#VISUAL_FIRM}\Jet\3.5\ISAM Formats\FoxPro 2.0; ValueType: binary; ValueName: SupportsLongNames; ValueData: 00; Components: VisualCpp\ServicePack

Root: HKLM; Subkey: SOFTWARE\{#VISUAL_FIRM}\Jet\3.5\ISAM Formats\FoxPro 2.5; ValueType: string; ValueName: Engine; ValueData: Xbase; Components: VisualCpp\ServicePack
Root: HKLM; Subkey: SOFTWARE\{#VISUAL_FIRM}\Jet\3.5\ISAM Formats\FoxPro 2.5; ValueType: string; ValueName: ExportFilter; ValueData: Microsoft FoxPro 2.5 (*.dbf); Components: VisualCpp\ServicePack
Root: HKLM; Subkey: SOFTWARE\{#VISUAL_FIRM}\Jet\3.5\ISAM Formats\FoxPro 2.5; ValueType: binary; ValueName: CanLink; ValueData: 01; Components: VisualCpp\ServicePack
Root: HKLM; Subkey: SOFTWARE\{#VISUAL_FIRM}\Jet\3.5\ISAM Formats\FoxPro 2.5; ValueType: binary; ValueName: OneTablePerFile; ValueData: 01; Components: VisualCpp\ServicePack
Root: HKLM; Subkey: SOFTWARE\{#VISUAL_FIRM}\Jet\3.5\ISAM Formats\FoxPro 2.5; ValueType: dword; ValueName: IsamType; ValueData: $00000000; Components: VisualCpp\ServicePack
Root: HKLM; Subkey: SOFTWARE\{#VISUAL_FIRM}\Jet\3.5\ISAM Formats\FoxPro 2.5; ValueType: binary; ValueName: IndexDialog; ValueData: 01; Components: VisualCpp\ServicePack
Root: HKLM; Subkey: SOFTWARE\{#VISUAL_FIRM}\Jet\3.5\ISAM Formats\FoxPro 2.5; ValueType: string; ValueName: IndexFilter; ValueData: "FoxPro Index (*.idx;*.cdx)"; Components: VisualCpp\ServicePack
Root: HKLM; Subkey: SOFTWARE\{#VISUAL_FIRM}\Jet\3.5\ISAM Formats\FoxPro 2.5; ValueType: binary; ValueName: CreateDBOnExport; ValueData: 00; Components: VisualCpp\ServicePack
Root: HKLM; Subkey: SOFTWARE\{#VISUAL_FIRM}\Jet\3.5\ISAM Formats\FoxPro 2.5; ValueType: string; ValueName: ResultTextExport; ValueData: Export data from the current database into a Microsoft FoxPro 2.5 file.  This process will overwrite the data if exported to an existing file.; Components: VisualCpp\ServicePack
Root: HKLM; Subkey: SOFTWARE\{#VISUAL_FIRM}\Jet\3.5\ISAM Formats\FoxPro 2.5; ValueType: binary; ValueName: SupportsLongNames; ValueData: 00; Components: VisualCpp\ServicePack

Root: HKLM; Subkey: SOFTWARE\{#VISUAL_FIRM}\Jet\3.5\ISAM Formats\FoxPro 2.6; ValueType: string; ValueName: Engine; ValueData: Xbase; Components: VisualCpp\ServicePack
Root: HKLM; Subkey: SOFTWARE\{#VISUAL_FIRM}\Jet\3.5\ISAM Formats\FoxPro 2.6; ValueType: string; ValueName: ExportFilter; ValueData: Microsoft FoxPro 2.6 (*.dbf); Components: VisualCpp\ServicePack
Root: HKLM; Subkey: SOFTWARE\{#VISUAL_FIRM}\Jet\3.5\ISAM Formats\FoxPro 2.6; ValueType: binary; ValueName: CanLink; ValueData: 01; Components: VisualCpp\ServicePack
Root: HKLM; Subkey: SOFTWARE\{#VISUAL_FIRM}\Jet\3.5\ISAM Formats\FoxPro 2.6; ValueType: binary; ValueName: OneTablePerFile; ValueData: 01; Components: VisualCpp\ServicePack
Root: HKLM; Subkey: SOFTWARE\{#VISUAL_FIRM}\Jet\3.5\ISAM Formats\FoxPro 2.6; ValueType: dword; ValueName: IsamType; ValueData: $00000000; Components: VisualCpp\ServicePack
Root: HKLM; Subkey: SOFTWARE\{#VISUAL_FIRM}\Jet\3.5\ISAM Formats\FoxPro 2.6; ValueType: binary; ValueName: IndexDialog; ValueData: 01; Components: VisualCpp\ServicePack
Root: HKLM; Subkey: SOFTWARE\{#VISUAL_FIRM}\Jet\3.5\ISAM Formats\FoxPro 2.6; ValueType: string; ValueName: IndexFilter; ValueData: "FoxPro Index (*.idx;*.cdx)"; Components: VisualCpp\ServicePack
Root: HKLM; Subkey: SOFTWARE\{#VISUAL_FIRM}\Jet\3.5\ISAM Formats\FoxPro 2.6; ValueType: binary; ValueName: CreateDBOnExport; ValueData: 00; Components: VisualCpp\ServicePack
Root: HKLM; Subkey: SOFTWARE\{#VISUAL_FIRM}\Jet\3.5\ISAM Formats\FoxPro 2.6; ValueType: string; ValueName: ResultTextExport; ValueData: Export data from the current database into a Microsoft FoxPro 2.6 file.  This process will overwrite the data if exported to an existing file.; Components: VisualCpp\ServicePack
Root: HKLM; Subkey: SOFTWARE\{#VISUAL_FIRM}\Jet\3.5\ISAM Formats\FoxPro 2.6; ValueType: binary; ValueName: SupportsLongNames; ValueData: 00; Components: VisualCpp\ServicePack

Root: HKLM; Subkey: SOFTWARE\{#VISUAL_FIRM}\Jet\3.5\ISAM Formats\FoxPro 3.0; ValueType: string; ValueName: Engine; ValueData: Xbase; Components: VisualCpp\ServicePack
Root: HKLM; Subkey: SOFTWARE\{#VISUAL_FIRM}\Jet\3.5\ISAM Formats\FoxPro 3.0; ValueType: string; ValueName: ExportFilter; ValueData: Microsoft FoxPro 3.0 (*.dbf); Components: VisualCpp\ServicePack
Root: HKLM; Subkey: SOFTWARE\{#VISUAL_FIRM}\Jet\3.5\ISAM Formats\FoxPro 3.0; ValueType: binary; ValueName: CanLink; ValueData: 00; Components: VisualCpp\ServicePack
Root: HKLM; Subkey: SOFTWARE\{#VISUAL_FIRM}\Jet\3.5\ISAM Formats\FoxPro 3.0; ValueType: binary; ValueName: OneTablePerFile; ValueData: 01; Components: VisualCpp\ServicePack
Root: HKLM; Subkey: SOFTWARE\{#VISUAL_FIRM}\Jet\3.5\ISAM Formats\FoxPro 3.0; ValueType: dword; ValueName: IsamType; ValueData: $00000000; Components: VisualCpp\ServicePack
Root: HKLM; Subkey: SOFTWARE\{#VISUAL_FIRM}\Jet\3.5\ISAM Formats\FoxPro 3.0; ValueType: binary; ValueName: IndexDialog; ValueData: 00; Components: VisualCpp\ServicePack
Root: HKLM; Subkey: SOFTWARE\{#VISUAL_FIRM}\Jet\3.5\ISAM Formats\FoxPro 3.0; ValueType: binary; ValueName: CreateDBOnExport; ValueData: 00; Components: VisualCpp\ServicePack
Root: HKLM; Subkey: SOFTWARE\{#VISUAL_FIRM}\Jet\3.5\ISAM Formats\FoxPro 3.0; ValueType: string; ValueName: ResultTextExport; ValueData: Export data from the current database into a Microsoft FoxPro 3.0 file.  This process will overwrite the data if exported to an existing file.; Components: VisualCpp\ServicePack
Root: HKLM; Subkey: SOFTWARE\{#VISUAL_FIRM}\Jet\3.5\ISAM Formats\FoxPro 3.0; ValueType: binary; ValueName: SupportsLongNames; ValueData: 00; Components: VisualCpp\ServicePack

Root: HKLM; Subkey: SOFTWARE\{#VISUAL_FIRM}\Jet\3.5\ISAM Formats\FoxPro DBC; ValueType: string; ValueName: Engine; ValueData: Xbase; Components: VisualCpp\ServicePack
Root: HKLM; Subkey: SOFTWARE\{#VISUAL_FIRM}\Jet\3.5\ISAM Formats\FoxPro DBC; ValueType: string; ValueName: ImportFilter; ValueData: Microsoft FoxPro 3.0 (*.dbc); Components: VisualCpp\ServicePack
Root: HKLM; Subkey: SOFTWARE\{#VISUAL_FIRM}\Jet\3.5\ISAM Formats\FoxPro DBC; ValueType: binary; ValueName: CanLink; ValueData: 00; Components: VisualCpp\ServicePack
Root: HKLM; Subkey: SOFTWARE\{#VISUAL_FIRM}\Jet\3.5\ISAM Formats\FoxPro DBC; ValueType: binary; ValueName: OneTablePerFile; ValueData: 00; Components: VisualCpp\ServicePack
Root: HKLM; Subkey: SOFTWARE\{#VISUAL_FIRM}\Jet\3.5\ISAM Formats\FoxPro DBC; ValueType: dword; ValueName: IsamType; ValueData: $00000000; Components: VisualCpp\ServicePack
Root: HKLM; Subkey: SOFTWARE\{#VISUAL_FIRM}\Jet\3.5\ISAM Formats\FoxPro DBC; ValueType: binary; ValueName: IndexDialog; ValueData: 00; Components: VisualCpp\ServicePack
Root: HKLM; Subkey: SOFTWARE\{#VISUAL_FIRM}\Jet\3.5\ISAM Formats\FoxPro DBC; ValueType: binary; ValueName: CreateDBOnExport; ValueData: 00; Components: VisualCpp\ServicePack
Root: HKLM; Subkey: SOFTWARE\{#VISUAL_FIRM}\Jet\3.5\ISAM Formats\FoxPro DBC; ValueType: string; ValueName: ResultTextImport; ValueData: Import data from the external file into the current database. Changing data in the current database will not change data in the external file.; Components: VisualCpp\ServicePack
Root: HKLM; Subkey: SOFTWARE\{#VISUAL_FIRM}\Jet\3.5\ISAM Formats\FoxPro DBC; ValueType: binary; ValueName: SupportsLongNames; ValueData: 00; Components: VisualCpp\ServicePack

Root: HKLM; Subkey: SOFTWARE\{#VISUAL_FIRM}\Jet\3.5\ISAM Formats\HTML Export; ValueType: string; ValueName: Engine; ValueData: Text; Components: VisualCpp\ServicePack
Root: HKLM; Subkey: SOFTWARE\{#VISUAL_FIRM}\Jet\3.5\ISAM Formats\HTML Export; ValueType: string; ValueName: ExportFilter; ValueData: "HTML Documents (*.html;*.htm)"; Components: VisualCpp\ServicePack
Root: HKLM; Subkey: SOFTWARE\{#VISUAL_FIRM}\Jet\3.5\ISAM Formats\HTML Export; ValueType: binary; ValueName: CanLink; ValueData: 00; Components: VisualCpp\ServicePack
Root: HKLM; Subkey: SOFTWARE\{#VISUAL_FIRM}\Jet\3.5\ISAM Formats\HTML Export; ValueType: binary; ValueName: OneTablePerFile; ValueData: 01; Components: VisualCpp\ServicePack
Root: HKLM; Subkey: SOFTWARE\{#VISUAL_FIRM}\Jet\3.5\ISAM Formats\HTML Export; ValueType: dword; ValueName: IsamType; ValueData: $00000002; Components: VisualCpp\ServicePack
Root: HKLM; Subkey: SOFTWARE\{#VISUAL_FIRM}\Jet\3.5\ISAM Formats\HTML Export; ValueType: binary; ValueName: IndexDialog; ValueData: 00; Components: VisualCpp\ServicePack
Root: HKLM; Subkey: SOFTWARE\{#VISUAL_FIRM}\Jet\3.5\ISAM Formats\HTML Export; ValueType: binary; ValueName: CreateDBOnExport; ValueData: 00; Components: VisualCpp\ServicePack
Root: HKLM; Subkey: SOFTWARE\{#VISUAL_FIRM}\Jet\3.5\ISAM Formats\HTML Export; ValueType: string; ValueName: ResultTextExport; ValueData: Export data from the current database into a text file.  This process will overwrite data if exported to an existing file.; Components: VisualCpp\ServicePack
Root: HKLM; Subkey: SOFTWARE\{#VISUAL_FIRM}\Jet\3.5\ISAM Formats\HTML Export; ValueType: binary; ValueName: SupportsLongNames; ValueData: 01; Components: VisualCpp\ServicePack

Root: HKLM; Subkey: SOFTWARE\{#VISUAL_FIRM}\Jet\3.5\ISAM Formats\HTML Import; ValueType: string; ValueName: Engine; ValueData: Text; Components: VisualCpp\ServicePack
Root: HKLM; Subkey: SOFTWARE\{#VISUAL_FIRM}\Jet\3.5\ISAM Formats\HTML Import; ValueType: string; ValueName: ImportFilter; ValueData: "HTML Documents (*.html;*.htm)"; Components: VisualCpp\ServicePack
Root: HKLM; Subkey: SOFTWARE\{#VISUAL_FIRM}\Jet\3.5\ISAM Formats\HTML Import; ValueType: binary; ValueName: CanLink; ValueData: 01; Components: VisualCpp\ServicePack
Root: HKLM; Subkey: SOFTWARE\{#VISUAL_FIRM}\Jet\3.5\ISAM Formats\HTML Import; ValueType: binary; ValueName: OneTablePerFile; ValueData: 00; Components: VisualCpp\ServicePack
Root: HKLM; Subkey: SOFTWARE\{#VISUAL_FIRM}\Jet\3.5\ISAM Formats\HTML Import; ValueType: dword; ValueName: IsamType; ValueData: $00000002; Components: VisualCpp\ServicePack
Root: HKLM; Subkey: SOFTWARE\{#VISUAL_FIRM}\Jet\3.5\ISAM Formats\HTML Import; ValueType: binary; ValueName: IndexDialog; ValueData: 00; Components: VisualCpp\ServicePack
Root: HKLM; Subkey: SOFTWARE\{#VISUAL_FIRM}\Jet\3.5\ISAM Formats\HTML Import; ValueType: binary; ValueName: CreateDBOnExport; ValueData: 00; Components: VisualCpp\ServicePack
Root: HKLM; Subkey: SOFTWARE\{#VISUAL_FIRM}\Jet\3.5\ISAM Formats\HTML Import; ValueType: string; ValueName: ResultTextImport; ValueData: Import data from the external file into the current database. Changing data in the current database will not change data in the external file.; Components: VisualCpp\ServicePack
Root: HKLM; Subkey: SOFTWARE\{#VISUAL_FIRM}\Jet\3.5\ISAM Formats\HTML Import; ValueType: string; ValueName: ResultTextLink; ValueData: Create a table in the current database that is linked to the external file.  Changing data in the current database will change data in the external file.; Components: VisualCpp\ServicePack
Root: HKLM; Subkey: SOFTWARE\{#VISUAL_FIRM}\Jet\3.5\ISAM Formats\HTML Import; ValueType: binary; ValueName: SupportsLongNames; ValueData: 01; Components: VisualCpp\ServicePack

Root: HKLM; Subkey: SOFTWARE\{#VISUAL_FIRM}\Jet\3.5\ISAM Formats\Lotus WK1; ValueType: string; ValueName: Engine; ValueData: Lotus; Components: VisualCpp\ServicePack
Root: HKLM; Subkey: SOFTWARE\{#VISUAL_FIRM}\Jet\3.5\ISAM Formats\Lotus WK1; ValueType: string; ValueName: ExportFilter; ValueData: Lotus 1-2-3 WK1 (*.wk1); Components: VisualCpp\ServicePack
Root: HKLM; Subkey: SOFTWARE\{#VISUAL_FIRM}\Jet\3.5\ISAM Formats\Lotus WK1; ValueType: string; ValueName: ImportFilter; ValueData: Lotus 1-2-3 (*.wk*); Components: VisualCpp\ServicePack
Root: HKLM; Subkey: SOFTWARE\{#VISUAL_FIRM}\Jet\3.5\ISAM Formats\Lotus WK1; ValueType: binary; ValueName: CanLink; ValueData: 00; Components: VisualCpp\ServicePack
Root: HKLM; Subkey: SOFTWARE\{#VISUAL_FIRM}\Jet\3.5\ISAM Formats\Lotus WK1; ValueType: binary; ValueName: OneTablePerFile; ValueData: 00; Components: VisualCpp\ServicePack
Root: HKLM; Subkey: SOFTWARE\{#VISUAL_FIRM}\Jet\3.5\ISAM Formats\Lotus WK1; ValueType: dword; ValueName: IsamType; ValueData: $00000001; Components: VisualCpp\ServicePack
Root: HKLM; Subkey: SOFTWARE\{#VISUAL_FIRM}\Jet\3.5\ISAM Formats\Lotus WK1; ValueType: binary; ValueName: IndexDialog; ValueData: 00; Components: VisualCpp\ServicePack
Root: HKLM; Subkey: SOFTWARE\{#VISUAL_FIRM}\Jet\3.5\ISAM Formats\Lotus WK1; ValueType: binary; ValueName: CreateDBOnExport; ValueData: 01; Components: VisualCpp\ServicePack
Root: HKLM; Subkey: SOFTWARE\{#VISUAL_FIRM}\Jet\3.5\ISAM Formats\Lotus WK1; ValueType: string; ValueName: ResultTextImport; ValueData: Import data from the external file into the current database. Changing data in the current database will not change data in the external file.; Components: VisualCpp\ServicePack
Root: HKLM; Subkey: SOFTWARE\{#VISUAL_FIRM}\Jet\3.5\ISAM Formats\Lotus WK1; ValueType: string; ValueName: ResultTextExport; ValueData: Export data from the current database into a Lotus 1-2-3 version 2 file.  This process will overwrite data if exported to an existing file.; Components: VisualCpp\ServicePack
Root: HKLM; Subkey: SOFTWARE\{#VISUAL_FIRM}\Jet\3.5\ISAM Formats\Lotus WK1; ValueType: binary; ValueName: SupportsLongNames; ValueData: 01; Components: VisualCpp\ServicePack

Root: HKLM; Subkey: SOFTWARE\{#VISUAL_FIRM}\Jet\3.5\ISAM Formats\Lotus WK3; ValueType: string; ValueName: Engine; ValueData: Lotus; Components: VisualCpp\ServicePack
Root: HKLM; Subkey: SOFTWARE\{#VISUAL_FIRM}\Jet\3.5\ISAM Formats\Lotus WK3; ValueType: string; ValueName: ExportFilter; ValueData: Lotus 1-2-3 WK3 (*.wk3); Components: VisualCpp\ServicePack
Root: HKLM; Subkey: SOFTWARE\{#VISUAL_FIRM}\Jet\3.5\ISAM Formats\Lotus WK3; ValueType: binary; ValueName: CanLink; ValueData: 00; Components: VisualCpp\ServicePack
Root: HKLM; Subkey: SOFTWARE\{#VISUAL_FIRM}\Jet\3.5\ISAM Formats\Lotus WK3; ValueType: binary; ValueName: OneTablePerFile; ValueData: 00; Components: VisualCpp\ServicePack
Root: HKLM; Subkey: SOFTWARE\{#VISUAL_FIRM}\Jet\3.5\ISAM Formats\Lotus WK3; ValueType: dword; ValueName: IsamType; ValueData: $00000001; Components: VisualCpp\ServicePack
Root: HKLM; Subkey: SOFTWARE\{#VISUAL_FIRM}\Jet\3.5\ISAM Formats\Lotus WK3; ValueType: binary; ValueName: IndexDialog; ValueData: 00; Components: VisualCpp\ServicePack
Root: HKLM; Subkey: SOFTWARE\{#VISUAL_FIRM}\Jet\3.5\ISAM Formats\Lotus WK3; ValueType: binary; ValueName: CreateDBOnExport; ValueData: 01; Components: VisualCpp\ServicePack
Root: HKLM; Subkey: SOFTWARE\{#VISUAL_FIRM}\Jet\3.5\ISAM Formats\Lotus WK3; ValueType: string; ValueName: ResultTextExport; ValueData: Export data from the current database into a Lotus 1-2-3 version 3 file.; Components: VisualCpp\ServicePack
Root: HKLM; Subkey: SOFTWARE\{#VISUAL_FIRM}\Jet\3.5\ISAM Formats\Lotus WK3; ValueType: binary; ValueName: SupportsLongNames; ValueData: 01; Components: VisualCpp\ServicePack

Root: HKLM; Subkey: SOFTWARE\{#VISUAL_FIRM}\Jet\3.5\ISAM Formats\Lotus WK4; ValueType: string; ValueName: Engine; ValueData: Lotus; Components: VisualCpp\ServicePack
Root: HKLM; Subkey: SOFTWARE\{#VISUAL_FIRM}\Jet\3.5\ISAM Formats\Lotus WK4; ValueType: binary; ValueName: CanLink; ValueData: 00; Components: VisualCpp\ServicePack
Root: HKLM; Subkey: SOFTWARE\{#VISUAL_FIRM}\Jet\3.5\ISAM Formats\Lotus WK4; ValueType: binary; ValueName: OneTablePerFile; ValueData: 00; Components: VisualCpp\ServicePack
Root: HKLM; Subkey: SOFTWARE\{#VISUAL_FIRM}\Jet\3.5\ISAM Formats\Lotus WK4; ValueType: dword; ValueName: IsamType; ValueData: $00000001; Components: VisualCpp\ServicePack
Root: HKLM; Subkey: SOFTWARE\{#VISUAL_FIRM}\Jet\3.5\ISAM Formats\Lotus WK4; ValueType: binary; ValueName: IndexDialog; ValueData: 00; Components: VisualCpp\ServicePack
Root: HKLM; Subkey: SOFTWARE\{#VISUAL_FIRM}\Jet\3.5\ISAM Formats\Lotus WK4; ValueType: binary; ValueName: CreateDBOnExport; ValueData: 01; Components: VisualCpp\ServicePack
Root: HKLM; Subkey: SOFTWARE\{#VISUAL_FIRM}\Jet\3.5\ISAM Formats\Lotus WK4; ValueType: binary; ValueName: SupportsLongNames; ValueData: 01; Components: VisualCpp\ServicePack

Root: HKLM; Subkey: SOFTWARE\{#VISUAL_FIRM}\Jet\3.5\ISAM Formats\Paradox 3.X; ValueType: string; ValueName: Engine; ValueData: Paradox; Components: VisualCpp\ServicePack
Root: HKLM; Subkey: SOFTWARE\{#VISUAL_FIRM}\Jet\3.5\ISAM Formats\Paradox 3.X; ValueType: string; ValueName: ExportFilter; ValueData: Paradox 3 (*.db); Components: VisualCpp\ServicePack
Root: HKLM; Subkey: SOFTWARE\{#VISUAL_FIRM}\Jet\3.5\ISAM Formats\Paradox 3.X; ValueType: string; ValueName: ImportFilter; ValueData: Paradox (*.db); Components: VisualCpp\ServicePack
Root: HKLM; Subkey: SOFTWARE\{#VISUAL_FIRM}\Jet\3.5\ISAM Formats\Paradox 3.X; ValueType: binary; ValueName: CanLink; ValueData: 01; Components: VisualCpp\ServicePack
Root: HKLM; Subkey: SOFTWARE\{#VISUAL_FIRM}\Jet\3.5\ISAM Formats\Paradox 3.X; ValueType: binary; ValueName: OneTablePerFile; ValueData: 01; Components: VisualCpp\ServicePack
Root: HKLM; Subkey: SOFTWARE\{#VISUAL_FIRM}\Jet\3.5\ISAM Formats\Paradox 3.X; ValueType: dword; ValueName: IsamType; ValueData: $00000000; Components: VisualCpp\ServicePack
Root: HKLM; Subkey: SOFTWARE\{#VISUAL_FIRM}\Jet\3.5\ISAM Formats\Paradox 3.X; ValueType: binary; ValueName: IndexDialog; ValueData: 00; Components: VisualCpp\ServicePack
Root: HKLM; Subkey: SOFTWARE\{#VISUAL_FIRM}\Jet\3.5\ISAM Formats\Paradox 3.X; ValueType: binary; ValueName: CreateDBOnExport; ValueData: 00; Components: VisualCpp\ServicePack
Root: HKLM; Subkey: SOFTWARE\{#VISUAL_FIRM}\Jet\3.5\ISAM Formats\Paradox 3.X; ValueType: string; ValueName: ResultTextImport; ValueData: Import data from the external file into the current database. Changing data in the current database will not change data in the external file.; Components: VisualCpp\ServicePack
Root: HKLM; Subkey: SOFTWARE\{#VISUAL_FIRM}\Jet\3.5\ISAM Formats\Paradox 3.X; ValueType: string; ValueName: ResultTextLink; ValueData: Create a table in the current database that is linked to the external file.  Changing data in the current database will change data in the external file.; Components: VisualCpp\ServicePack
Root: HKLM; Subkey: SOFTWARE\{#VISUAL_FIRM}\Jet\3.5\ISAM Formats\Paradox 3.X; ValueType: string; ValueName: ResultTextExport; ValueData: Export data from the current database into a Paradox 3 file.  This process will overwrite the data if exported to an existing file.; Components: VisualCpp\ServicePack
Root: HKLM; Subkey: SOFTWARE\{#VISUAL_FIRM}\Jet\3.5\ISAM Formats\Paradox 3.X; ValueType: binary; ValueName: SupportsLongNames; ValueData: 00; Components: VisualCpp\ServicePack

Root: HKLM; Subkey: SOFTWARE\{#VISUAL_FIRM}\Jet\3.5\ISAM Formats\Paradox 4.X; ValueType: string; ValueName: Engine; ValueData: Paradox; Components: VisualCpp\ServicePack
Root: HKLM; Subkey: SOFTWARE\{#VISUAL_FIRM}\Jet\3.5\ISAM Formats\Paradox 4.X; ValueType: string; ValueName: ExportFilter; ValueData: Paradox 4 (*.db); Components: VisualCpp\ServicePack
Root: HKLM; Subkey: SOFTWARE\{#VISUAL_FIRM}\Jet\3.5\ISAM Formats\Paradox 4.X; ValueType: binary; ValueName: CanLink; ValueData: 01; Components: VisualCpp\ServicePack
Root: HKLM; Subkey: SOFTWARE\{#VISUAL_FIRM}\Jet\3.5\ISAM Formats\Paradox 4.X; ValueType: binary; ValueName: OneTablePerFile; ValueData: 01; Components: VisualCpp\ServicePack
Root: HKLM; Subkey: SOFTWARE\{#VISUAL_FIRM}\Jet\3.5\ISAM Formats\Paradox 4.X; ValueType: dword; ValueName: IsamType; ValueData: $00000000; Components: VisualCpp\ServicePack
Root: HKLM; Subkey: SOFTWARE\{#VISUAL_FIRM}\Jet\3.5\ISAM Formats\Paradox 4.X; ValueType: binary; ValueName: IndexDialog; ValueData: 00; Components: VisualCpp\ServicePack
Root: HKLM; Subkey: SOFTWARE\{#VISUAL_FIRM}\Jet\3.5\ISAM Formats\Paradox 4.X; ValueType: binary; ValueName: CreateDBOnExport; ValueData: 00; Components: VisualCpp\ServicePack
Root: HKLM; Subkey: SOFTWARE\{#VISUAL_FIRM}\Jet\3.5\ISAM Formats\Paradox 4.X; ValueType: string; ValueName: ResultTextExport; ValueData: Export data from the current database into a Paradox 4 file.  This process will overwrite the data if exported to an existing file.; Components: VisualCpp\ServicePack
Root: HKLM; Subkey: SOFTWARE\{#VISUAL_FIRM}\Jet\3.5\ISAM Formats\Paradox 4.X; ValueType: binary; ValueName: SupportsLongNames; ValueData: 00; Components: VisualCpp\ServicePack

Root: HKLM; Subkey: SOFTWARE\{#VISUAL_FIRM}\Jet\3.5\ISAM Formats\Paradox 5.X; ValueType: string; ValueName: Engine; ValueData: Paradox; Components: VisualCpp\ServicePack
Root: HKLM; Subkey: SOFTWARE\{#VISUAL_FIRM}\Jet\3.5\ISAM Formats\Paradox 5.X; ValueType: string; ValueName: ExportFilter; ValueData: Paradox 5 (*.db); Components: VisualCpp\ServicePack
Root: HKLM; Subkey: SOFTWARE\{#VISUAL_FIRM}\Jet\3.5\ISAM Formats\Paradox 5.X; ValueType: binary; ValueName: CanLink; ValueData: 01; Components: VisualCpp\ServicePack
Root: HKLM; Subkey: SOFTWARE\{#VISUAL_FIRM}\Jet\3.5\ISAM Formats\Paradox 5.X; ValueType: binary; ValueName: OneTablePerFile; ValueData: 01; Components: VisualCpp\ServicePack
Root: HKLM; Subkey: SOFTWARE\{#VISUAL_FIRM}\Jet\3.5\ISAM Formats\Paradox 5.X; ValueType: dword; ValueName: IsamType; ValueData: $00000000; Components: VisualCpp\ServicePack
Root: HKLM; Subkey: SOFTWARE\{#VISUAL_FIRM}\Jet\3.5\ISAM Formats\Paradox 5.X; ValueType: binary; ValueName: IndexDialog; ValueData: 00; Components: VisualCpp\ServicePack
Root: HKLM; Subkey: SOFTWARE\{#VISUAL_FIRM}\Jet\3.5\ISAM Formats\Paradox 5.X; ValueType: binary; ValueName: CreateDBOnExport; ValueData: 00; Components: VisualCpp\ServicePack
Root: HKLM; Subkey: SOFTWARE\{#VISUAL_FIRM}\Jet\3.5\ISAM Formats\Paradox 5.X; ValueType: string; ValueName: ResultTextExport; ValueData: Export data from the current database into a Paradox 5 file.  This process will overwrite the data if exported to an existing file.; Components: VisualCpp\ServicePack
Root: HKLM; Subkey: SOFTWARE\{#VISUAL_FIRM}\Jet\3.5\ISAM Formats\Paradox 5.X; ValueType: binary; ValueName: SupportsLongNames; ValueData: 00; Components: VisualCpp\ServicePack

Root: HKLM; Subkey: SOFTWARE\{#VISUAL_FIRM}\Jet\3.5\ISAM Formats\Text; ValueType: string; ValueName: Engine; ValueData: Text; Components: VisualCpp\ServicePack
Root: HKLM; Subkey: SOFTWARE\{#VISUAL_FIRM}\Jet\3.5\ISAM Formats\Text; ValueType: string; ValueName: ExportFilter; ValueData: "Text Files (*.txt;*.csv;*.tab;*.asc)"; Components: VisualCpp\ServicePack
Root: HKLM; Subkey: SOFTWARE\{#VISUAL_FIRM}\Jet\3.5\ISAM Formats\Text; ValueType: string; ValueName: ImportFilter; ValueData: "Text Files (*.txt;*.csv;*.tab;*.asc)"; Components: VisualCpp\ServicePack
Root: HKLM; Subkey: SOFTWARE\{#VISUAL_FIRM}\Jet\3.5\ISAM Formats\Text; ValueType: binary; ValueName: CanLink; ValueData: 01; Components: VisualCpp\ServicePack
Root: HKLM; Subkey: SOFTWARE\{#VISUAL_FIRM}\Jet\3.5\ISAM Formats\Text; ValueType: binary; ValueName: OneTablePerFile; ValueData: 01; Components: VisualCpp\ServicePack
Root: HKLM; Subkey: SOFTWARE\{#VISUAL_FIRM}\Jet\3.5\ISAM Formats\Text; ValueType: dword; ValueName: IsamType; ValueData: $00000002; Components: VisualCpp\ServicePack
Root: HKLM; Subkey: SOFTWARE\{#VISUAL_FIRM}\Jet\3.5\ISAM Formats\Text; ValueType: binary; ValueName: IndexDialog; ValueData: 00; Components: VisualCpp\ServicePack
Root: HKLM; Subkey: SOFTWARE\{#VISUAL_FIRM}\Jet\3.5\ISAM Formats\Text; ValueType: binary; ValueName: CreateDBOnExport; ValueData: 00; Components: VisualCpp\ServicePack
Root: HKLM; Subkey: SOFTWARE\{#VISUAL_FIRM}\Jet\3.5\ISAM Formats\Text; ValueType: string; ValueName: ResultTextImport; ValueData: Import data from the external file into the current database. Changing data in the current database will not change data in the external file.; Components: VisualCpp\ServicePack
Root: HKLM; Subkey: SOFTWARE\{#VISUAL_FIRM}\Jet\3.5\ISAM Formats\Text; ValueType: string; ValueName: ResultTextLink; ValueData: Create a table in the current database that is linked to the external file.  Changing data in the current database will change data in the external file.; Components: VisualCpp\ServicePack
Root: HKLM; Subkey: SOFTWARE\{#VISUAL_FIRM}\Jet\3.5\ISAM Formats\Text; ValueType: string; ValueName: ResultTextExport; ValueData: Export data from the current database into a text file.  This process will overwrite data if exported to an existing file.; Components: VisualCpp\ServicePack
Root: HKLM; Subkey: SOFTWARE\{#VISUAL_FIRM}\Jet\3.5\ISAM Formats\Text; ValueType: binary; ValueName: SupportsLongNames; ValueData: 01; Components: VisualCpp\ServicePack

Root: HKLM; Subkey: SOFTWARE\{#VISUAL_FIRM}\MS Setup (ACME)\Table Files; ValueType: string; ValueName: {#VISUAL_SHORT} {#VISUAL_TYPE} {#VISUAL_VER}.{#VISUAL_REV} Professional Edition@v{#VISUAL_VER}.{#VISUAL_REV}.0.0.0626 (1033); ValueData: {app}\VC98\Setup\1033\setup.stf
#ifdef VISUAL_MSDN
Root: HKLM; Subkey: SOFTWARE\{#VISUAL_FIRM}\MS Setup (ACME)\Table Files; ValueType: string; ValueName: Microsoft Developer Network - Visual Studio 6.0a@v6.0.0.1.0902 (1036); ValueData: {app}\MSDN98\98VSa\1036\Setup\setup.stf; Components: Msdn
#endif

Root: HKLM; Subkey: SOFTWARE\{#VISUAL_FIRM}\Shared Tools\addinwz.awx; ValueType: string; ValueName: Path; ValueData: {app}\Common\MSDev98\Bin\IDE\ADDINWZ.AWX
Root: HKLM; Subkey: SOFTWARE\{#VISUAL_FIRM}\Shared Tools\addinwz.awx\Clients; ValueType: string; ValueName: {app}\VC98\Setup\1033\VC98PRO.DLL
Root: HKLM; Subkey: SOFTWARE\{#VISUAL_FIRM}\Shared Tools\appwzenu.dll; ValueType: string; ValueName: Path; ValueData: {app}\Common\MSDev98\Bin\IDE\APPWZENU.DLL
Root: HKLM; Subkey: SOFTWARE\{#VISUAL_FIRM}\Shared Tools\appwzenu.dll\Clients; ValueType: string; ValueName: {app}\VC98\Setup\1033\VC98PRO.DLL
Root: HKLM; Subkey: SOFTWARE\{#VISUAL_FIRM}\Shared Tools\atl.dll; ValueType: string; ValueName: Path; ValueData: {sys}\atl.dll
Root: HKLM; Subkey: SOFTWARE\{#VISUAL_FIRM}\Shared Tools\atl.dll\Clients; ValueType: string; ValueName: {app}\VC98\Setup\1033\VC98PRO.DLL
Root: HKLM; Subkey: SOFTWARE\{#VISUAL_FIRM}\Shared Tools\autolayt.dll; ValueType: string; ValueName: Path; ValueData: {app}\Common\MSDev98\Bin\AUTOLAYT.DLL
Root: HKLM; Subkey: SOFTWARE\{#VISUAL_FIRM}\Shared Tools\autolayt.dll\Clients; ValueType: string; ValueName: {app}\VC98\Setup\1033\VC98PRO.DLL
Root: HKLM; Subkey: SOFTWARE\{#VISUAL_FIRM}\Shared Tools\bind.exe; ValueType: string; ValueName: Path; ValueData: {app}\Common\Tools\BIND.EXE
Root: HKLM; Subkey: SOFTWARE\{#VISUAL_FIRM}\Shared Tools\bind.exe\Clients; ValueType: string; ValueName: {app}\VC98\Setup\1033\VC98PRO.DLL
Root: HKLM; Subkey: SOFTWARE\{#VISUAL_FIRM}\Shared Tools\cawutil.dll; ValueType: string; ValueName: Path; ValueData: {app}\Common\MSDev98\Bin\IDE\CAWUTIL.DLL
Root: HKLM; Subkey: SOFTWARE\{#VISUAL_FIRM}\Shared Tools\cawutil.dll\Clients; ValueType: string; ValueName: {app}\VC98\Setup\1033\VC98PRO.DLL
Root: HKLM; Subkey: SOFTWARE\{#VISUAL_FIRM}\Shared Tools\cawutil.hlp; ValueType: string; ValueName: Path; ValueData: {app}\Common\MSDev98\Bin\IDE\CAWUTIL.HLP
Root: HKLM; Subkey: SOFTWARE\{#VISUAL_FIRM}\Shared Tools\cawutil.hlp\Clients; ValueType: string; ValueName: {app}\VC98\Setup\1033\VC98PRO.DLL
Root: HKLM; Subkey: SOFTWARE\{#VISUAL_FIRM}\Shared Tools\cl32test.exe_NT; ValueType: string; ValueName: Path; ValueData: {app}\Common\Tools\WinNT\CL32TEST.EXE
Root: HKLM; Subkey: SOFTWARE\{#VISUAL_FIRM}\Shared Tools\cl32test.exe_NT\Clients; ValueType: string; ValueName: {app}\VC98\Setup\1033\VC98PRO.DLL
Root: HKLM; Subkey: SOFTWARE\{#VISUAL_FIRM}\Shared Tools\clipasst.dll; ValueType: string; ValueName: Path; ValueData: {app}\Common\MSDev98\Bin\IDE\CLIPASST.DLL
Root: HKLM; Subkey: SOFTWARE\{#VISUAL_FIRM}\Shared Tools\clipasst.dll\Clients; ValueType: string; ValueName: {app}\VC98\Setup\1033\VC98PRO.DLL
Root: HKLM; Subkey: SOFTWARE\{#VISUAL_FIRM}\Shared Tools\clipasst.hlp; ValueType: string; ValueName: Path; ValueData: {app}\Common\MSDev98\Bin\IDE\CLIPASST.HLP
Root: HKLM; Subkey: SOFTWARE\{#VISUAL_FIRM}\Shared Tools\clipasst.hlp\Clients; ValueType: string; ValueName: {app}\VC98\Setup\1033\VC98PRO.DLL
Root: HKLM; Subkey: SOFTWARE\{#VISUAL_FIRM}\Shared Tools\comct232.dep; ValueType: string; ValueName: Path; ValueData: {sys}\COMCT232.DEP
Root: HKLM; Subkey: SOFTWARE\{#VISUAL_FIRM}\Shared Tools\comct232.dep\Clients; ValueType: string; ValueName: {app}\VC98\Setup\1033\VC98PRO.DLL
Root: HKLM; Subkey: SOFTWARE\{#VISUAL_FIRM}\Shared Tools\comct232.ocx; ValueType: string; ValueName: Path; ValueData: {sys}\COMCT232.OCX
Root: HKLM; Subkey: SOFTWARE\{#VISUAL_FIRM}\Shared Tools\comct232.ocx\Clients; ValueType: string; ValueName: {app}\VC98\Setup\1033\VC98PRO.DLL
Root: HKLM; Subkey: SOFTWARE\{#VISUAL_FIRM}\Shared Tools\comctl32.dep; ValueType: string; ValueName: Path; ValueData: {sys}\COMCTL32.DEP
Root: HKLM; Subkey: SOFTWARE\{#VISUAL_FIRM}\Shared Tools\comctl32.dep\Clients; ValueType: string; ValueName: {app}\VC98\Setup\1033\VC98PRO.DLL
Root: HKLM; Subkey: SOFTWARE\{#VISUAL_FIRM}\Shared Tools\comctl32.ocx; ValueType: string; ValueName: Path; ValueData: {sys}\COMCTL32.OCX
Root: HKLM; Subkey: SOFTWARE\{#VISUAL_FIRM}\Shared Tools\comctl32.ocx\Clients; ValueType: string; ValueName: {app}\VC98\Setup\1033\VC98PRO.DLL
Root: HKLM; Subkey: SOFTWARE\{#VISUAL_FIRM}\Shared Tools\comdlg32.dep; ValueType: string; ValueName: Path; ValueData: {sys}\COMDLG32.DEP
Root: HKLM; Subkey: SOFTWARE\{#VISUAL_FIRM}\Shared Tools\comdlg32.dep\Clients; ValueType: string; ValueName: {app}\VC98\Setup\1033\VC98PRO.DLL
Root: HKLM; Subkey: SOFTWARE\{#VISUAL_FIRM}\Shared Tools\comdlg32.ocx; ValueType: string; ValueName: Path; ValueData: {sys}\COMDLG32.OCX
Root: HKLM; Subkey: SOFTWARE\{#VISUAL_FIRM}\Shared Tools\comdlg32.ocx\Clients; ValueType: string; ValueName: {app}\VC98\Setup\1033\VC98PRO.DLL
Root: HKLM; Subkey: SOFTWARE\{#VISUAL_FIRM}\Shared Tools\crt.ncb; ValueType: string; ValueName: Path; ValueData: {app}\Common\MSDev98\Bin\CRT.NCB
Root: HKLM; Subkey: SOFTWARE\{#VISUAL_FIRM}\Shared Tools\crt.ncb\Clients; ValueType: string; ValueName: {app}\VC98\Setup\1033\VC98PRO.DLL
Root: HKLM; Subkey: SOFTWARE\{#VISUAL_FIRM}\Shared Tools\ctip.dll; ValueType: string; ValueName: Path; ValueData: {app}\Common\MSDev98\Bin\IDE\CTIP.DLL
Root: HKLM; Subkey: SOFTWARE\{#VISUAL_FIRM}\Shared Tools\ctip.dll\Clients; ValueType: string; ValueName: {app}\VC98\Setup\1033\VC98PRO.DLL
Root: HKLM; Subkey: SOFTWARE\{#VISUAL_FIRM}\Shared Tools\ctip.hlp; ValueType: string; ValueName: Path; ValueData: {app}\Common\MSDev98\Bin\IDE\CTIP.HLP
Root: HKLM; Subkey: SOFTWARE\{#VISUAL_FIRM}\Shared Tools\ctip.hlp\Clients; ValueType: string; ValueName: {app}\VC98\Setup\1033\VC98PRO.DLL
Root: HKLM; Subkey: SOFTWARE\{#VISUAL_FIRM}\Shared Tools\custmwz.awx; ValueType: string; ValueName: Path; ValueData: {app}\Common\MSDev98\Bin\IDE\CUSTMWZ.AWX
Root: HKLM; Subkey: SOFTWARE\{#VISUAL_FIRM}\Shared Tools\custmwz.awx\Clients; ValueType: string; ValueName: {app}\VC98\Setup\1033\VC98PRO.DLL
Root: HKLM; Subkey: SOFTWARE\{#VISUAL_FIRM}\Shared Tools\custmwz.hlp; ValueType: string; ValueName: Path; ValueData: {app}\Common\MSDev98\Bin\IDE\CUSTMWZ.HLP
Root: HKLM; Subkey: SOFTWARE\{#VISUAL_FIRM}\Shared Tools\custmwz.hlp\Clients; ValueType: string; ValueName: {app}\VC98\Setup\1033\VC98PRO.DLL
Root: HKLM; Subkey: SOFTWARE\{#VISUAL_FIRM}\Shared Tools\dao2535.tlb; ValueType: string; ValueName: Path; ValueData: {cf}\Microsoft Shared\DAO\DAO2535.TLB
Root: HKLM; Subkey: SOFTWARE\{#VISUAL_FIRM}\Shared Tools\dao2535.tlb\Clients; ValueType: string; ValueName: {app}\VC98\Setup\1033\VC98PRO.DLL
Root: HKLM; Subkey: SOFTWARE\{#VISUAL_FIRM}\Shared Tools\dao350.dll; ValueType: string; ValueName: Path; ValueData: {cf}\Microsoft Shared\DAO\DAO350.DLL
Root: HKLM; Subkey: SOFTWARE\{#VISUAL_FIRM}\Shared Tools\dao350.dll\Clients; ValueType: string; ValueName: {app}\VC98\Setup\1033\VC98PRO.DLL
Root: HKLM; Subkey: SOFTWARE\{#VISUAL_FIRM}\Shared Tools\dao360.dll; ValueType: string; ValueName: Path; ValueData: {cf}\Microsoft Shared\DAO\dao360.dll
Root: HKLM; Subkey: SOFTWARE\{#VISUAL_FIRM}\Shared Tools\dao360.dll\Clients; ValueType: string; ValueName: {sys}\MSJET35.DLL
Root: HKLM; Subkey: SOFTWARE\{#VISUAL_FIRM}\Shared Tools\dbgrid32.dep; ValueType: string; ValueName: Path; ValueData: {sys}\DBGRID32.DEP
Root: HKLM; Subkey: SOFTWARE\{#VISUAL_FIRM}\Shared Tools\dbgrid32.dep\Clients; ValueType: string; ValueName: {app}\VC98\Setup\1033\VC98PRO.DLL
Root: HKLM; Subkey: SOFTWARE\{#VISUAL_FIRM}\Shared Tools\dbgrid32.ocx; ValueType: string; ValueName: Path; ValueData: {sys}\DBGRID32.OCX
Root: HKLM; Subkey: SOFTWARE\{#VISUAL_FIRM}\Shared Tools\dbgrid32.ocx\Clients; ValueType: string; ValueName: {app}\VC98\Setup\1033\VC98PRO.DLL
Root: HKLM; Subkey: SOFTWARE\{#VISUAL_FIRM}\Shared Tools\dblist32.dep; ValueType: string; ValueName: Path; ValueData: {sys}\DBLIST32.DEP
Root: HKLM; Subkey: SOFTWARE\{#VISUAL_FIRM}\Shared Tools\dblist32.dep\Clients; ValueType: string; ValueName: {app}\VC98\Setup\1033\VC98PRO.DLL
Root: HKLM; Subkey: SOFTWARE\{#VISUAL_FIRM}\Shared Tools\dblist32.ocx; ValueType: string; ValueName: Path; ValueData: {sys}\DBLIST32.OCX
Root: HKLM; Subkey: SOFTWARE\{#VISUAL_FIRM}\Shared Tools\dblist32.ocx\Clients; ValueType: string; ValueName: {app}\VC98\Setup\1033\VC98PRO.DLL
Root: HKLM; Subkey: SOFTWARE\{#VISUAL_FIRM}\Shared Tools\dbwiz1.dll; ValueType: string; ValueName: Path; ValueData: {app}\Common\Wizards98\DBWIZ1.DLL
Root: HKLM; Subkey: SOFTWARE\{#VISUAL_FIRM}\Shared Tools\dbwiz1.dll\Clients; ValueType: string; ValueName: {app}\VC98\Setup\1033\VC98PRO.DLL
Root: HKLM; Subkey: SOFTWARE\{#VISUAL_FIRM}\Shared Tools\dbwiz1.srg; ValueType: string; ValueName: Path; ValueData: {app}\Common\Wizards98\DBWIZ1.SRG
Root: HKLM; Subkey: SOFTWARE\{#VISUAL_FIRM}\Shared Tools\dbwiz1.srg\Clients; ValueType: string; ValueName: {app}\VC98\Setup\1033\VC98PRO.DLL
Root: HKLM; Subkey: SOFTWARE\{#VISUAL_FIRM}\Shared Tools\ddespy.exe_NT; ValueType: string; ValueName: Path; ValueData: {app}\Common\Tools\WinNT\DDESPY.EXE
Root: HKLM; Subkey: SOFTWARE\{#VISUAL_FIRM}\Shared Tools\ddespy.exe_NT\Clients; ValueType: string; ValueName: {app}\VC98\Setup\1033\VC98PRO.DLL
Root: HKLM; Subkey: SOFTWARE\{#VISUAL_FIRM}\Shared Tools\depends.cnt; ValueType: string; ValueName: Path; ValueData: {app}\Common\Tools\DEPENDS.CNT
Root: HKLM; Subkey: SOFTWARE\{#VISUAL_FIRM}\Shared Tools\depends.cnt\Clients; ValueType: string; ValueName: {app}\VC98\Setup\1033\VC98PRO.DLL
Root: HKLM; Subkey: SOFTWARE\{#VISUAL_FIRM}\Shared Tools\depends.exe; ValueType: string; ValueName: Path; ValueData: {app}\Common\Tools\DEPENDS.EXE
Root: HKLM; Subkey: SOFTWARE\{#VISUAL_FIRM}\Shared Tools\depends.exe\Clients; ValueType: string; ValueName: {app}\VC98\Setup\1033\VC98PRO.DLL
Root: HKLM; Subkey: SOFTWARE\{#VISUAL_FIRM}\Shared Tools\depends.hlp; ValueType: string; ValueName: Path; ValueData: {app}\Common\Tools\DEPENDS.HLP
Root: HKLM; Subkey: SOFTWARE\{#VISUAL_FIRM}\Shared Tools\depends.hlp\Clients; ValueType: string; ValueName: {app}\VC98\Setup\1033\VC98PRO.DLL
Root: HKLM; Subkey: SOFTWARE\{#VISUAL_FIRM}\Shared Tools\devaut1.pkg; ValueType: string; ValueName: Path; ValueData: {app}\Common\MSDev98\Bin\IDE\DEVAUT1.PKG
Root: HKLM; Subkey: SOFTWARE\{#VISUAL_FIRM}\Shared Tools\devaut1.pkg\Clients; ValueType: string; ValueName: {app}\VC98\Setup\1033\VC98PRO.DLL
Root: HKLM; Subkey: SOFTWARE\{#VISUAL_FIRM}\Shared Tools\devbied.pkg; ValueType: string; ValueName: Path; ValueData: {app}\Common\MSDev98\Bin\IDE\DEVBIED.PKG
Root: HKLM; Subkey: SOFTWARE\{#VISUAL_FIRM}\Shared Tools\devbied.pkg\Clients; ValueType: string; ValueName: {app}\VC98\Setup\1033\VC98PRO.DLL
Root: HKLM; Subkey: SOFTWARE\{#VISUAL_FIRM}\Shared Tools\devbld.pkg; ValueType: string; ValueName: Path; ValueData: {app}\Common\MSDev98\Bin\IDE\DEVBLD.PKG
Root: HKLM; Subkey: SOFTWARE\{#VISUAL_FIRM}\Shared Tools\devbld.pkg\Clients; ValueType: string; ValueName: {app}\VC98\Setup\1033\VC98PRO.DLL
Root: HKLM; Subkey: SOFTWARE\{#VISUAL_FIRM}\Shared Tools\devclvw.pkg; ValueType: string; ValueName: Path; ValueData: {app}\Common\MSDev98\Bin\IDE\DEVCLVW.PKG
Root: HKLM; Subkey: SOFTWARE\{#VISUAL_FIRM}\Shared Tools\devclvw.pkg\Clients; ValueType: string; ValueName: {app}\VC98\Setup\1033\VC98PRO.DLL
Root: HKLM; Subkey: SOFTWARE\{#VISUAL_FIRM}\Shared Tools\devcpp.pkg; ValueType: string; ValueName: Path; ValueData: {app}\Common\MSDev98\Bin\IDE\DEVCPP.PKG
Root: HKLM; Subkey: SOFTWARE\{#VISUAL_FIRM}\Shared Tools\devcpp.pkg\Clients; ValueType: string; ValueName: {app}\VC98\Setup\1033\VC98PRO.DLL
Root: HKLM; Subkey: SOFTWARE\{#VISUAL_FIRM}\Shared Tools\devdbg.pkg; ValueType: string; ValueName: Path; ValueData: {app}\Common\MSDev98\Bin\IDE\DEVDBG.PKG
Root: HKLM; Subkey: SOFTWARE\{#VISUAL_FIRM}\Shared Tools\devdbg.pkg\Clients; ValueType: string; ValueName: {app}\VC98\Setup\1033\VC98PRO.DLL
Root: HKLM; Subkey: SOFTWARE\{#VISUAL_FIRM}\Shared Tools\devdtg.pkg; ValueType: string; ValueName: Path; ValueData: {app}\Common\MSDev98\Bin\IDE\DEVDTG.PKG
Root: HKLM; Subkey: SOFTWARE\{#VISUAL_FIRM}\Shared Tools\devdtg.pkg\Clients; ValueType: string; ValueName: {app}\VC98\Setup\1033\VC98PRO.DLL
Root: HKLM; Subkey: SOFTWARE\{#VISUAL_FIRM}\Shared Tools\devedit_pkg; ValueType: string; ValueName: Path; ValueData: {app}\Common\MSDev98\Bin\DEVEDIT.PKG
Root: HKLM; Subkey: SOFTWARE\{#VISUAL_FIRM}\Shared Tools\devedit_pkg\Clients; ValueType: string; ValueName: {app}\VC98\Setup\1033\VC98PRO.DLL
Root: HKLM; Subkey: SOFTWARE\{#VISUAL_FIRM}\Shared Tools\devgal.pkg; ValueType: string; ValueName: Path; ValueData: {app}\Common\MSDev98\Bin\IDE\DEVGAL.PKG
Root: HKLM; Subkey: SOFTWARE\{#VISUAL_FIRM}\Shared Tools\devgal.pkg\Clients; ValueType: string; ValueName: {app}\VC98\Setup\1033\VC98PRO.DLL
Root: HKLM; Subkey: SOFTWARE\{#VISUAL_FIRM}\Shared Tools\devhtmx.pkg; ValueType: string; ValueName: Path; ValueData: {app}\Common\MSDev98\Bin\IDE\DEVHTMX.PKG
Root: HKLM; Subkey: SOFTWARE\{#VISUAL_FIRM}\Shared Tools\devhtmx.pkg\Clients; ValueType: string; ValueName: {app}\VC98\Setup\1033\VC98PRO.DLL
Root: HKLM; Subkey: SOFTWARE\{#VISUAL_FIRM}\Shared Tools\devncb.pkg; ValueType: string; ValueName: Path; ValueData: {app}\Common\MSDev98\Bin\IDE\DEVNCB.PKG
Root: HKLM; Subkey: SOFTWARE\{#VISUAL_FIRM}\Shared Tools\devncb.pkg\Clients; ValueType: string; ValueName: {app}\VC98\Setup\1033\VC98PRO.DLL
Root: HKLM; Subkey: SOFTWARE\{#VISUAL_FIRM}\Shared Tools\devodl.pkg; ValueType: string; ValueName: Path; ValueData: {app}\Common\MSDev98\Bin\IDE\DEVODL.PKG
Root: HKLM; Subkey: SOFTWARE\{#VISUAL_FIRM}\Shared Tools\devodl.pkg\Clients; ValueType: string; ValueName: {app}\VC98\Setup\1033\VC98PRO.DLL
Root: HKLM; Subkey: SOFTWARE\{#VISUAL_FIRM}\Shared Tools\devprj_pkg; ValueType: string; ValueName: Path; ValueData: {app}\Common\MSDev98\Bin\DEVPRJ.PKG
Root: HKLM; Subkey: SOFTWARE\{#VISUAL_FIRM}\Shared Tools\devprj_pkg\Clients; ValueType: string; ValueName: {app}\VC98\Setup\1033\VC98PRO.DLL
Root: HKLM; Subkey: SOFTWARE\{#VISUAL_FIRM}\Shared Tools\devres.pkg; ValueType: string; ValueName: Path; ValueData: {app}\Common\MSDev98\Bin\IDE\DEVRES.PKG
Root: HKLM; Subkey: SOFTWARE\{#VISUAL_FIRM}\Shared Tools\devres.pkg\Clients; ValueType: string; ValueName: {app}\VC98\Setup\1033\VC98PRO.DLL
Root: HKLM; Subkey: SOFTWARE\{#VISUAL_FIRM}\Shared Tools\devshl_dll; ValueType: string; ValueName: Path; ValueData: {app}\Common\MSDev98\Bin\DEVSHL.DLL
Root: HKLM; Subkey: SOFTWARE\{#VISUAL_FIRM}\Shared Tools\devshl_dll\Clients; ValueType: string; ValueName: {app}\VC98\Setup\1033\VC98PRO.DLL
Root: HKLM; Subkey: SOFTWARE\{#VISUAL_FIRM}\Shared Tools\devtldc.dll; ValueType: string; ValueName: Path; ValueData: {sys}\DEVTLDC.DLL
Root: HKLM; Subkey: SOFTWARE\{#VISUAL_FIRM}\Shared Tools\devtldc.dll\Clients; ValueType: string; ValueName: {app}\VC98\Setup\1033\VC98PRO.DLL
Root: HKLM; Subkey: SOFTWARE\{#VISUAL_FIRM}\Shared Tools\devtool.pkg; ValueType: string; ValueName: Path; ValueData: {app}\Common\MSDev98\Bin\IDE\DEVTOOL.PKG
Root: HKLM; Subkey: SOFTWARE\{#VISUAL_FIRM}\Shared Tools\devtool.pkg\Clients; ValueType: string; ValueName: {app}\VC98\Setup\1033\VC98PRO.DLL
Root: HKLM; Subkey: SOFTWARE\{#VISUAL_FIRM}\Shared Tools\devxpgl.dll; ValueType: string; ValueName: Path; ValueData: {app}\Common\MSDev98\Bin\IDE\DEVXPGL.DLL
Root: HKLM; Subkey: SOFTWARE\{#VISUAL_FIRM}\Shared Tools\devxpgl.dll\Clients; ValueType: string; ValueName: {app}\VC98\Setup\1033\VC98PRO.DLL
Root: HKLM; Subkey: SOFTWARE\{#VISUAL_FIRM}\Shared Tools\dfview.exe; ValueType: string; ValueName: Path; ValueData: {app}\Common\Tools\DFVIEW.EXE
Root: HKLM; Subkey: SOFTWARE\{#VISUAL_FIRM}\Shared Tools\dfview.exe\Clients; ValueType: string; ValueName: {app}\VC98\Setup\1033\VC98PRO.DLL
Root: HKLM; Subkey: SOFTWARE\{#VISUAL_FIRM}\Shared Tools\dlgbar.dll; ValueType: string; ValueName: Path; ValueData: {app}\Common\MSDev98\Bin\IDE\DLGBAR.DLL
Root: HKLM; Subkey: SOFTWARE\{#VISUAL_FIRM}\Shared Tools\dlgbar.dll\Clients; ValueType: string; ValueName: {app}\VC98\Setup\1033\VC98PRO.DLL
Root: HKLM; Subkey: SOFTWARE\{#VISUAL_FIRM}\Shared Tools\dlgbar.hlp; ValueType: string; ValueName: Path; ValueData: {app}\Common\MSDev98\Bin\IDE\DLGBAR.HLP
Root: HKLM; Subkey: SOFTWARE\{#VISUAL_FIRM}\Shared Tools\dlgbar.hlp\Clients; ValueType: string; ValueName: {app}\VC98\Setup\1033\VC98PRO.DLL
Root: HKLM; Subkey: SOFTWARE\{#VISUAL_FIRM}\Shared Tools\dobjview.exe; ValueType: string; ValueName: Path; ValueData: {app}\Common\Tools\DOBJVIEW.EXE
Root: HKLM; Subkey: SOFTWARE\{#VISUAL_FIRM}\Shared Tools\dobjview.exe\Clients; ValueType: string; ValueName: {app}\VC98\Setup\1033\VC98PRO.DLL
Root: HKLM; Subkey: SOFTWARE\{#VISUAL_FIRM}\Shared Tools\docreg.dll; ValueType: string; ValueName: Path; ValueData: {app}\Common\MSDev98\Bin\IDE\DOCREG.DLL
Root: HKLM; Subkey: SOFTWARE\{#VISUAL_FIRM}\Shared Tools\docreg.dll\Clients; ValueType: string; ValueName: {app}\VC98\Setup\1033\VC98PRO.DLL
Root: HKLM; Subkey: SOFTWARE\{#VISUAL_FIRM}\Shared Tools\docreg.hlp; ValueType: string; ValueName: Path; ValueData: {app}\Common\MSDev98\Bin\IDE\DOCREG.HLP
Root: HKLM; Subkey: SOFTWARE\{#VISUAL_FIRM}\Shared Tools\docreg.hlp\Clients; ValueType: string; ValueName: {app}\VC98\Setup\1033\VC98PRO.DLL
Root: HKLM; Subkey: SOFTWARE\{#VISUAL_FIRM}\Shared Tools\errlook.exe; ValueType: string; ValueName: Path; ValueData: {app}\Common\Tools\ERRLOOK.EXE
Root: HKLM; Subkey: SOFTWARE\{#VISUAL_FIRM}\Shared Tools\errlook.exe\Clients; ValueType: string; ValueName: {app}\VC98\Setup\1033\VC98PRO.DLL
Root: HKLM; Subkey: SOFTWARE\{#VISUAL_FIRM}\Shared Tools\errlook.hlp; ValueType: string; ValueName: Path; ValueData: {app}\Common\Tools\ERRLOOK.HLP
Root: HKLM; Subkey: SOFTWARE\{#VISUAL_FIRM}\Shared Tools\errlook.hlp\Clients; ValueType: string; ValueName: {app}\VC98\Setup\1033\VC98PRO.DLL
Root: HKLM; Subkey: SOFTWARE\{#VISUAL_FIRM}\Shared Tools\exthelp.cnt; ValueType: string; ValueName: Path; ValueData: {app}\Common\MSDev98\Help\EXTHELP.CNT
Root: HKLM; Subkey: SOFTWARE\{#VISUAL_FIRM}\Shared Tools\exthelp.cnt\Clients; ValueType: string; ValueName: {app}\VC98\Setup\1033\VC98PRO.DLL
Root: HKLM; Subkey: SOFTWARE\{#VISUAL_FIRM}\Shared Tools\exthelp.hlp; ValueType: string; ValueName: Path; ValueData: {app}\Common\MSDev98\Help\EXTHELP.HLP
Root: HKLM; Subkey: SOFTWARE\{#VISUAL_FIRM}\Shared Tools\exthelp.hlp\Clients; ValueType: string; ValueName: {app}\VC98\Setup\1033\VC98PRO.DLL
Root: HKLM; Subkey: SOFTWARE\{#VISUAL_FIRM}\Shared Tools\feacp.dll; ValueType: string; ValueName: Path; ValueData: {app}\Common\MSDev98\Bin\FEACP.DLL
Root: HKLM; Subkey: SOFTWARE\{#VISUAL_FIRM}\Shared Tools\feacp.dll\Clients; ValueType: string; ValueName: {app}\VC98\Setup\1033\VC98PRO.DLL
Root: HKLM; Subkey: SOFTWARE\{#VISUAL_FIRM}\Shared Tools\Fontedit.exe; ValueType: string; ValueName: Path; ValueData: {app}\Common\Tools\FONTEDIT.EXE
Root: HKLM; Subkey: SOFTWARE\{#VISUAL_FIRM}\Shared Tools\Fontedit.exe\Clients; ValueType: string; ValueName: {app}\VC98\Setup\1033\VC98PRO.DLL
Root: HKLM; Subkey: SOFTWARE\{#VISUAL_FIRM}\Shared Tools\Fontedit.hlp; ValueType: string; ValueName: Path; ValueData: {app}\Common\Tools\FONTEDIT.HLP
Root: HKLM; Subkey: SOFTWARE\{#VISUAL_FIRM}\Shared Tools\Fontedit.hlp\Clients; ValueType: string; ValueName: {app}\VC98\Setup\1033\VC98PRO.DLL
Root: HKLM; Subkey: SOFTWARE\{#VISUAL_FIRM}\Shared Tools\guidgen.dll; ValueType: string; ValueName: Path; ValueData: {app}\Common\MSDev98\Bin\IDE\GUIDGEN.DLL
Root: HKLM; Subkey: SOFTWARE\{#VISUAL_FIRM}\Shared Tools\guidgen.dll\Clients; ValueType: string; ValueName: {app}\VC98\Setup\1033\VC98PRO.DLL
Root: HKLM; Subkey: SOFTWARE\{#VISUAL_FIRM}\Shared Tools\guidgen.exe; ValueType: string; ValueName: Path; ValueData: {app}\Common\Tools\GUIDGEN.EXE
Root: HKLM; Subkey: SOFTWARE\{#VISUAL_FIRM}\Shared Tools\guidgen.exe\Clients; ValueType: string; ValueName: {app}\VC98\Setup\1033\VC98PRO.DLL
Root: HKLM; Subkey: SOFTWARE\{#VISUAL_FIRM}\Shared Tools\guidgen.hlp; ValueType: string; ValueName: Path; ValueData: {app}\Common\MSDev98\Bin\IDE\GUIDGEN.HLP
Root: HKLM; Subkey: SOFTWARE\{#VISUAL_FIRM}\Shared Tools\guidgen.hlp\Clients; ValueType: string; ValueName: {app}\VC98\Setup\1033\VC98PRO.DLL
Root: HKLM; Subkey: SOFTWARE\{#VISUAL_FIRM}\Shared Tools\gutils.dll; ValueType: string; ValueName: Path; ValueData: {app}\Common\Tools\GUTILS.DLL
Root: HKLM; Subkey: SOFTWARE\{#VISUAL_FIRM}\Shared Tools\gutils.dll\Clients; ValueType: string; ValueName: {app}\VC98\Setup\1033\VC98PRO.DLL
Root: HKLM; Subkey: SOFTWARE\{#VISUAL_FIRM}\Shared Tools\hcrtf.exe; ValueType: string; ValueName: Path; ValueData: {app}\Common\Tools\HCRTF.EXE
Root: HKLM; Subkey: SOFTWARE\{#VISUAL_FIRM}\Shared Tools\hcrtf.exe\Clients; ValueType: string; ValueName: {app}\VC98\Setup\1033\VC98PRO.DLL
Root: HKLM; Subkey: SOFTWARE\{#VISUAL_FIRM}\Shared Tools\hcw.cnt; ValueType: string; ValueName: Path; ValueData: {app}\Common\Tools\HCW.CNT
Root: HKLM; Subkey: SOFTWARE\{#VISUAL_FIRM}\Shared Tools\hcw.cnt\Clients; ValueType: string; ValueName: {app}\VC98\Setup\1033\VC98PRO.DLL
Root: HKLM; Subkey: SOFTWARE\{#VISUAL_FIRM}\Shared Tools\hcw.exe; ValueType: string; ValueName: Path; ValueData: {app}\Common\Tools\HCW.EXE
Root: HKLM; Subkey: SOFTWARE\{#VISUAL_FIRM}\Shared Tools\hcw.exe\Clients; ValueType: string; ValueName: {app}\VC98\Setup\1033\VC98PRO.DLL
Root: HKLM; Subkey: SOFTWARE\{#VISUAL_FIRM}\Shared Tools\hcw.hlp; ValueType: string; ValueName: Path; ValueData: {app}\Common\Tools\HCW.HLP
Root: HKLM; Subkey: SOFTWARE\{#VISUAL_FIRM}\Shared Tools\hcw.hlp\Clients; ValueType: string; ValueName: {app}\VC98\Setup\1033\VC98PRO.DLL
Root: HKLM; Subkey: SOFTWARE\{#VISUAL_FIRM}\Shared Tools\hwdll.dll; ValueType: string; ValueName: Path; ValueData: {app}\Common\Tools\HWDLL.DLL
Root: HKLM; Subkey: SOFTWARE\{#VISUAL_FIRM}\Shared Tools\hwdll.dll\Clients; ValueType: string; ValueName: {app}\VC98\Setup\1033\VC98PRO.DLL
Root: HKLM; Subkey: SOFTWARE\{#VISUAL_FIRM}\Shared Tools\idle.dll; ValueType: string; ValueName: Path; ValueData: {app}\Common\MSDev98\Bin\IDE\IDLE.DLL
Root: HKLM; Subkey: SOFTWARE\{#VISUAL_FIRM}\Shared Tools\idle.dll\Clients; ValueType: string; ValueName: {app}\VC98\Setup\1033\VC98PRO.DLL
Root: HKLM; Subkey: SOFTWARE\{#VISUAL_FIRM}\Shared Tools\idle.hlp; ValueType: string; ValueName: Path; ValueData: {app}\Common\MSDev98\Bin\IDE\IDLE.HLP
Root: HKLM; Subkey: SOFTWARE\{#VISUAL_FIRM}\Shared Tools\idle.hlp\Clients; ValueType: string; ValueName: {app}\VC98\Setup\1033\VC98PRO.DLL
Root: HKLM; Subkey: SOFTWARE\{#VISUAL_FIRM}\Shared Tools\inetawz.awx; ValueType: string; ValueName: Path; ValueData: {app}\Common\MSDev98\Bin\IDE\INETAWZ.AWX
Root: HKLM; Subkey: SOFTWARE\{#VISUAL_FIRM}\Shared Tools\inetawz.awx\Clients; ValueType: string; ValueName: {app}\VC98\Setup\1033\VC98PRO.DLL
Root: HKLM; Subkey: SOFTWARE\{#VISUAL_FIRM}\Shared Tools\insrepim.dll; ValueType: string; ValueName: Path; ValueData: {cf}\Microsoft Shared\Repostry\INSREPIM.DLL
Root: HKLM; Subkey: SOFTWARE\{#VISUAL_FIRM}\Shared Tools\insrepim.dll\Clients; ValueType: string; ValueName: {app}\VC98\Setup\1033\VC98PRO.DLL; ValueData: 
Root: HKLM; Subkey: SOFTWARE\{#VISUAL_FIRM}\Shared Tools\irotview.exe; ValueType: string; ValueName: Path; ValueData: {app}\Common\Tools\IROTVIEW.EXE
Root: HKLM; Subkey: SOFTWARE\{#VISUAL_FIRM}\Shared Tools\irotview.exe\Clients; ValueType: string; ValueName: {app}\VC98\Setup\1033\VC98PRO.DLL
Root: HKLM; Subkey: SOFTWARE\{#VISUAL_FIRM}\Shared Tools\iswframe.dll; ValueType: string; ValueName: Path; ValueData: {app}\Common\Wizards98\ISWFRAME.DLL
Root: HKLM; Subkey: SOFTWARE\{#VISUAL_FIRM}\Shared Tools\iswframe.dll\Clients; ValueType: string; ValueName: {app}\VC98\Setup\1033\VC98PRO.DLL
Root: HKLM; Subkey: SOFTWARE\{#VISUAL_FIRM}\Shared Tools\iviewers.dll; ValueType: string; ValueName: Path; ValueData: {app}\Common\Tools\IVIEWERS.DLL
Root: HKLM; Subkey: SOFTWARE\{#VISUAL_FIRM}\Shared Tools\iviewers.dll\Clients; ValueType: string; ValueName: {app}\VC98\Setup\1033\VC98PRO.DLL
Root: HKLM; Subkey: SOFTWARE\{#VISUAL_FIRM}\Shared Tools\langext.dat; ValueType: string; ValueName: Path; ValueData: {app}\Common\MSDev98\Bin\LANGEXT.DAT
Root: HKLM; Subkey: SOFTWARE\{#VISUAL_FIRM}\Shared Tools\langext.dat\Clients; ValueType: string; ValueName: {app}\VC98\Setup\1033\VC98PRO.DLL
Root: HKLM; Subkey: SOFTWARE\{#VISUAL_FIRM}\Shared Tools\macrocpp.dat; ValueType: string; ValueName: Path; ValueData: {app}\Common\MSDev98\Bin\MACROCPP.DAT
Root: HKLM; Subkey: SOFTWARE\{#VISUAL_FIRM}\Shared Tools\macrocpp.dat\Clients; ValueType: string; ValueName: {app}\VC98\Setup\1033\VC98PRO.DLL
Root: HKLM; Subkey: SOFTWARE\{#VISUAL_FIRM}\Shared Tools\makehm.exe; ValueType: string; ValueName: Path; ValueData: {app}\Common\Tools\MAKEHM.EXE
Root: HKLM; Subkey: SOFTWARE\{#VISUAL_FIRM}\Shared Tools\makehm.exe\Clients; ValueType: string; ValueName: {app}\VC98\Setup\1033\VC98PRO.DLL
Root: HKLM; Subkey: SOFTWARE\{#VISUAL_FIRM}\Shared Tools\mapicomp.dll; ValueType: string; ValueName: Path; ValueData: {app}\Common\MSDev98\Bin\IDE\MAPICOMP.DLL
Root: HKLM; Subkey: SOFTWARE\{#VISUAL_FIRM}\Shared Tools\mapicomp.dll\Clients; ValueType: string; ValueName: {app}\VC98\Setup\1033\VC98PRO.DLL
Root: HKLM; Subkey: SOFTWARE\{#VISUAL_FIRM}\Shared Tools\mapicomp.hlp; ValueType: string; ValueName: Path; ValueData: {app}\Common\MSDev98\Bin\IDE\MAPICOMP.HLP
Root: HKLM; Subkey: SOFTWARE\{#VISUAL_FIRM}\Shared Tools\mapicomp.hlp\Clients; ValueType: string; ValueName: {app}\VC98\Setup\1033\VC98PRO.DLL
Root: HKLM; Subkey: SOFTWARE\{#VISUAL_FIRM}\Shared Tools\mci32.dep; ValueType: string; ValueName: Path; ValueData: {sys}\MCI32.DEP
Root: HKLM; Subkey: SOFTWARE\{#VISUAL_FIRM}\Shared Tools\mci32.dep\Clients; ValueType: string; ValueName: {app}\VC98\Setup\1033\VC98PRO.DLL
Root: HKLM; Subkey: SOFTWARE\{#VISUAL_FIRM}\Shared Tools\mci32.ocx; ValueType: string; ValueName: Path; ValueData: {sys}\MCI32.OCX
Root: HKLM; Subkey: SOFTWARE\{#VISUAL_FIRM}\Shared Tools\mci32.ocx\Clients; ValueType: string; ValueName: {app}\VC98\Setup\1033\VC98PRO.DLL
Root: HKLM; Subkey: SOFTWARE\{#VISUAL_FIRM}\Shared Tools\mdt2db.dll; ValueType: string; ValueName: Path; ValueData: {cf}\Microsoft Shared\MSDesigners98\MDT2DB.DLL
Root: HKLM; Subkey: SOFTWARE\{#VISUAL_FIRM}\Shared Tools\mdt2db.dll\Clients; ValueType: string; ValueName: {app}\VC98\Setup\1033\VC98PRO.DLL
Root: HKLM; Subkey: SOFTWARE\{#VISUAL_FIRM}\Shared Tools\mdt2dbns.dll; ValueType: string; ValueName: Path; ValueData: {cf}\Microsoft Shared\MSDesigners98\MDT2DBNS.DLL
Root: HKLM; Subkey: SOFTWARE\{#VISUAL_FIRM}\Shared Tools\mdt2dbns.dll\Clients; ValueType: string; ValueName: {app}\VC98\Setup\1033\VC98PRO.DLL
Root: HKLM; Subkey: SOFTWARE\{#VISUAL_FIRM}\Shared Tools\mdt2dd.dll; ValueType: string; ValueName: Path; ValueData: {cf}\Microsoft Shared\MSDesigners98\MDT2DD.DLL
Root: HKLM; Subkey: SOFTWARE\{#VISUAL_FIRM}\Shared Tools\mdt2dd.dll\Clients; ValueType: string; ValueName: {app}\VC98\Setup\1033\VC98PRO.DLL
Root: HKLM; Subkey: SOFTWARE\{#VISUAL_FIRM}\Shared Tools\mdt2df.dll; ValueType: string; ValueName: Path; ValueData: {cf}\Microsoft Shared\MSDesigners98\MDT2DF.DLL
Root: HKLM; Subkey: SOFTWARE\{#VISUAL_FIRM}\Shared Tools\mdt2df.dll\Clients; ValueType: string; ValueName: {app}\VC98\Setup\1033\VC98PRO.DLL
Root: HKLM; Subkey: SOFTWARE\{#VISUAL_FIRM}\Shared Tools\mdt2dfx.dll; ValueType: string; ValueName: Path; ValueData: {cf}\Microsoft Shared\MSDesigners98\MDT2DFX.DLL
Root: HKLM; Subkey: SOFTWARE\{#VISUAL_FIRM}\Shared Tools\mdt2dfx.dll\Clients; ValueType: string; ValueName: {app}\VC98\Setup\1033\VC98PRO.DLL
Root: HKLM; Subkey: SOFTWARE\{#VISUAL_FIRM}\Shared Tools\mdt2fref.dll; ValueType: string; ValueName: Path; ValueData: {cf}\Microsoft Shared\MSDesigners98\MDT2FREF.DLL
Root: HKLM; Subkey: SOFTWARE\{#VISUAL_FIRM}\Shared Tools\mdt2fref.dll\Clients; ValueType: string; ValueName: {app}\VC98\Setup\1033\VC98PRO.DLL
Root: HKLM; Subkey: SOFTWARE\{#VISUAL_FIRM}\Shared Tools\mdt2fw.dll; ValueType: string; ValueName: Path; ValueData: {cf}\Microsoft Shared\MSDesigners98\MDT2FW.DLL
Root: HKLM; Subkey: SOFTWARE\{#VISUAL_FIRM}\Shared Tools\mdt2fw.dll\Clients; ValueType: string; ValueName: {app}\VC98\Setup\1033\VC98PRO.DLL
Root: HKLM; Subkey: SOFTWARE\{#VISUAL_FIRM}\Shared Tools\mdt2fw95.dll; ValueType: string; ValueName: Path; ValueData: {sys}\MDT2FW95.DLL
Root: HKLM; Subkey: SOFTWARE\{#VISUAL_FIRM}\Shared Tools\mdt2fw95.dll\Clients; ValueType: string; ValueName: {app}\VC98\Setup\1033\VC98PRO.DLL
Root: HKLM; Subkey: SOFTWARE\{#VISUAL_FIRM}\Shared Tools\mdt2fwui.dll(enu); ValueType: string; ValueName: Path; ValueData: {cf}\Microsoft Shared\MSDesigners98\resources\1033\MDT2FWUI.DLL
Root: HKLM; Subkey: SOFTWARE\{#VISUAL_FIRM}\Shared Tools\mdt2fwui.dll(enu)\Clients; ValueType: string; ValueName: {app}\VC98\Setup\1033\VC98PRO.DLL
Root: HKLM; Subkey: SOFTWARE\{#VISUAL_FIRM}\Shared Tools\mdt2g.dll; ValueType: string; ValueName: Path; ValueData: {cf}\Microsoft Shared\MSDesigners98\MDT2G.DLL
Root: HKLM; Subkey: SOFTWARE\{#VISUAL_FIRM}\Shared Tools\mdt2g.dll\Clients; ValueType: string; ValueName: {app}\VC98\Setup\1033\VC98PRO.DLL
Root: HKLM; Subkey: SOFTWARE\{#VISUAL_FIRM}\Shared Tools\mdt2gddo.dll; ValueType: string; ValueName: Path; ValueData: {cf}\Microsoft Shared\MSDesigners98\MDT2GDDO.DLL
Root: HKLM; Subkey: SOFTWARE\{#VISUAL_FIRM}\Shared Tools\mdt2gddo.dll\Clients; ValueType: string; ValueName: {app}\VC98\Setup\1033\VC98PRO.DLL
Root: HKLM; Subkey: SOFTWARE\{#VISUAL_FIRM}\Shared Tools\mdt2gddr.dll; ValueType: string; ValueName: Path; ValueData: {cf}\Microsoft Shared\MSDesigners98\MDT2GDDR.DLL
Root: HKLM; Subkey: SOFTWARE\{#VISUAL_FIRM}\Shared Tools\mdt2gddr.dll\Clients; ValueType: string; ValueName: {app}\VC98\Setup\1033\VC98PRO.DLL
Root: HKLM; Subkey: SOFTWARE\{#VISUAL_FIRM}\Shared Tools\mdt2gkor.dll; ValueType: string; ValueName: Path; ValueData: {cf}\Microsoft Shared\MSDesigners98\MDT2GKOR.DLL
Root: HKLM; Subkey: SOFTWARE\{#VISUAL_FIRM}\Shared Tools\mdt2gkor.dll\Clients; ValueType: string; ValueName: {app}\VC98\Setup\1033\VC98PRO.DLL
Root: HKLM; Subkey: SOFTWARE\{#VISUAL_FIRM}\Shared Tools\mdt2qd.dll; ValueType: string; ValueName: Path; ValueData: {cf}\Microsoft Shared\MSDesigners98\MDT2QD.DLL
Root: HKLM; Subkey: SOFTWARE\{#VISUAL_FIRM}\Shared Tools\mdt2qd.dll\Clients; ValueType: string; ValueName: {app}\VC98\Setup\1033\VC98PRO.DLL
Root: HKLM; Subkey: SOFTWARE\{#VISUAL_FIRM}\Shared Tools\media.dll; ValueType: string; ValueName: Path; ValueData: {app}\Common\MSDev98\Bin\IDE\MEDIA.DLL
Root: HKLM; Subkey: SOFTWARE\{#VISUAL_FIRM}\Shared Tools\media.dll\Clients; ValueType: string; ValueName: {app}\VC98\Setup\1033\VC98PRO.DLL
Root: HKLM; Subkey: SOFTWARE\{#VISUAL_FIRM}\Shared Tools\media.hlp; ValueType: string; ValueName: Path; ValueData: {app}\Common\MSDev98\Bin\IDE\MEDIA.HLP
Root: HKLM; Subkey: SOFTWARE\{#VISUAL_FIRM}\Shared Tools\media.hlp\Clients; ValueType: string; ValueName: {app}\VC98\Setup\1033\VC98PRO.DLL
Root: HKLM; Subkey: SOFTWARE\{#VISUAL_FIRM}\Shared Tools\mfc.rct; ValueType: string; ValueName: Path; ValueData: {app}\Common\MSDev98\Template\MFC.RCT
Root: HKLM; Subkey: SOFTWARE\{#VISUAL_FIRM}\Shared Tools\mfc.rct\Clients; ValueType: string; ValueName: {app}\VC98\Setup\1033\VC98PRO.DLL
Root: HKLM; Subkey: SOFTWARE\{#VISUAL_FIRM}\Shared Tools\mfc42d.dll; ValueType: string; ValueName: Path; ValueData: {sys}\MFC42D.DLL
Root: HKLM; Subkey: SOFTWARE\{#VISUAL_FIRM}\Shared Tools\mfc42d.dll\Clients; ValueType: string; ValueName: {app}\VC98\Setup\1033\VC98PRO.DLL
Root: HKLM; Subkey: SOFTWARE\{#VISUAL_FIRM}\Shared Tools\mfcapwz.dll; ValueType: string; ValueName: Path; ValueData: {app}\Common\MSDev98\Bin\IDE\MFCAPWZ.DLL
Root: HKLM; Subkey: SOFTWARE\{#VISUAL_FIRM}\Shared Tools\mfcapwz.dll\Clients; ValueType: string; ValueName: {app}\VC98\Setup\1033\VC98PRO.DLL
Root: HKLM; Subkey: SOFTWARE\{#VISUAL_FIRM}\Shared Tools\mfcatl.ncb; ValueType: string; ValueName: Path; ValueData: {app}\Common\MSDev98\Bin\MFCATL.NCB
Root: HKLM; Subkey: SOFTWARE\{#VISUAL_FIRM}\Shared Tools\mfcatl.ncb\Clients; ValueType: string; ValueName: {app}\VC98\Setup\1033\VC98PRO.DLL
Root: HKLM; Subkey: SOFTWARE\{#VISUAL_FIRM}\Shared Tools\mfcclwz.dll; ValueType: string; ValueName: Path; ValueData: {app}\Common\MSDev98\Bin\MFCCLWZ.DLL
Root: HKLM; Subkey: SOFTWARE\{#VISUAL_FIRM}\Shared Tools\mfcclwz.dll\Clients; ValueType: string; ValueName: {app}\VC98\Setup\1033\VC98PRO.DLL
Root: HKLM; Subkey: SOFTWARE\{#VISUAL_FIRM}\Shared Tools\mfctlwz.awx; ValueType: string; ValueName: Path; ValueData: {app}\Common\MSDev98\Bin\IDE\MFCTLWZ.AWX
Root: HKLM; Subkey: SOFTWARE\{#VISUAL_FIRM}\Shared Tools\mfctlwz.awx\Clients; ValueType: string; ValueName: {app}\VC98\Setup\1033\VC98PRO.DLL
Root: HKLM; Subkey: SOFTWARE\{#VISUAL_FIRM}\Shared Tools\mrbc.exe; ValueType: string; ValueName: Path; ValueData: {app}\Common\Tools\MRBC.EXE
Root: HKLM; Subkey: SOFTWARE\{#VISUAL_FIRM}\Shared Tools\mrbc.exe\Clients; ValueType: string; ValueName: {app}\VC98\Setup\1033\VC98PRO.DLL
Root: HKLM; Subkey: SOFTWARE\{#VISUAL_FIRM}\Shared Tools\msaddndr.dep; ValueType: string; ValueName: Path; ValueData: {cf}\designer\MSADDNDR.DEP
Root: HKLM; Subkey: SOFTWARE\{#VISUAL_FIRM}\Shared Tools\msaddndr.dep\Clients; ValueType: string; ValueName: {app}\VC98\Setup\1033\VC98PRO.DLL; ValueData: 
Root: HKLM; Subkey: SOFTWARE\{#VISUAL_FIRM}\Shared Tools\msaddndr.dll; ValueType: string; ValueName: Path; ValueData: {cf}\designer\MSADDNDR.DLL
Root: HKLM; Subkey: SOFTWARE\{#VISUAL_FIRM}\Shared Tools\msaddndr.dll\Clients; ValueType: string; ValueName: {app}\VC98\Setup\1033\VC98PRO.DLL; ValueData: 
Root: HKLM; Subkey: SOFTWARE\{#VISUAL_FIRM}\Shared Tools\msaddndr.tlb; ValueType: string; ValueName: Path; ValueData: {cf}\designer\MSADDNDR.TLB
Root: HKLM; Subkey: SOFTWARE\{#VISUAL_FIRM}\Shared Tools\msaddndr.tlb\Clients; ValueType: string; ValueName: {app}\VC98\Setup\1033\VC98PRO.DLL; ValueData: 
Root: HKLM; Subkey: SOFTWARE\{#VISUAL_FIRM}\Shared Tools\msadodc.dep; ValueType: string; ValueName: Path; ValueData: {sys}\MSADODC.DEP
Root: HKLM; Subkey: SOFTWARE\{#VISUAL_FIRM}\Shared Tools\msadodc.dep\Clients; ValueType: string; ValueName: {app}\VC98\Setup\1033\VC98PRO.DLL
Root: HKLM; Subkey: SOFTWARE\{#VISUAL_FIRM}\Shared Tools\msadodc.ocx; ValueType: string; ValueName: Path; ValueData: {sys}\MSADODC.OCX
Root: HKLM; Subkey: SOFTWARE\{#VISUAL_FIRM}\Shared Tools\msadodc.ocx\Clients; ValueType: string; ValueName: {app}\VC98\Setup\1033\VC98PRO.DLL
Root: HKLM; Subkey: SOFTWARE\{#VISUAL_FIRM}\Shared Tools\msbind.dll; ValueType: string; ValueName: Path; ValueData: {sys}\MSBIND.DLL
Root: HKLM; Subkey: SOFTWARE\{#VISUAL_FIRM}\Shared Tools\msbind.dll\Clients; ValueType: string; ValueName: {app}\VC98\Setup\1033\VC98PRO.DLL
Root: HKLM; Subkey: SOFTWARE\{#VISUAL_FIRM}\Shared Tools\MSComCt2.dep; ValueType: string; ValueName: Path; ValueData: {sys}\MSCOMCT2.DEP
Root: HKLM; Subkey: SOFTWARE\{#VISUAL_FIRM}\Shared Tools\MSComCt2.dep\Clients; ValueType: string; ValueName: {app}\VC98\Setup\1033\VC98PRO.DLL
Root: HKLM; Subkey: SOFTWARE\{#VISUAL_FIRM}\Shared Tools\mscomct2.ocx; ValueType: string; ValueName: Path; ValueData: {sys}\MSCOMCT2.OCX
Root: HKLM; Subkey: SOFTWARE\{#VISUAL_FIRM}\Shared Tools\mscomct2.ocx\Clients; ValueType: string; ValueName: {app}\VC98\Setup\1033\VC98PRO.DLL
Root: HKLM; Subkey: SOFTWARE\{#VISUAL_FIRM}\Shared Tools\MSComCtl.dep; ValueType: string; ValueName: Path; ValueData: {sys}\MSCOMCTL.DEP
Root: HKLM; Subkey: SOFTWARE\{#VISUAL_FIRM}\Shared Tools\MSComCtl.dep\Clients; ValueType: string; ValueName: {app}\VC98\Setup\1033\VC98PRO.DLL
Root: HKLM; Subkey: SOFTWARE\{#VISUAL_FIRM}\Shared Tools\mscomctl.ocx; ValueType: string; ValueName: Path; ValueData: {sys}\MSCOMCTL.OCX
Root: HKLM; Subkey: SOFTWARE\{#VISUAL_FIRM}\Shared Tools\mscomctl.ocx\Clients; ValueType: string; ValueName: {app}\VC98\Setup\1033\VC98PRO.DLL
Root: HKLM; Subkey: SOFTWARE\{#VISUAL_FIRM}\Shared Tools\mscomm32.dep; ValueType: string; ValueName: Path; ValueData: {sys}\MSCOMM32.DEP
Root: HKLM; Subkey: SOFTWARE\{#VISUAL_FIRM}\Shared Tools\mscomm32.dep\Clients; ValueType: string; ValueName: {app}\VC98\Setup\1033\VC98PRO.DLL
Root: HKLM; Subkey: SOFTWARE\{#VISUAL_FIRM}\Shared Tools\mscomm32.ocx; ValueType: string; ValueName: Path; ValueData: {sys}\MSCOMM32.OCX
Root: HKLM; Subkey: SOFTWARE\{#VISUAL_FIRM}\Shared Tools\mscomm32.ocx\Clients; ValueType: string; ValueName: {app}\VC98\Setup\1033\VC98PRO.DLL
Root: HKLM; Subkey: SOFTWARE\{#VISUAL_FIRM}\Shared Tools\msdatgrd.dep; ValueType: string; ValueName: Path; ValueData: {sys}\MSDATGRD.DEP
Root: HKLM; Subkey: SOFTWARE\{#VISUAL_FIRM}\Shared Tools\msdatgrd.dep\Clients; ValueType: string; ValueName: {app}\VC98\Setup\1033\VC98PRO.DLL
Root: HKLM; Subkey: SOFTWARE\{#VISUAL_FIRM}\Shared Tools\MSDatGrd.ocx; ValueType: string; ValueName: Path; ValueData: {sys}\MSDATGRD.OCX
Root: HKLM; Subkey: SOFTWARE\{#VISUAL_FIRM}\Shared Tools\MSDatGrd.ocx\Clients; ValueType: string; ValueName: {app}\VC98\Setup\1033\VC98PRO.DLL
Root: HKLM; Subkey: SOFTWARE\{#VISUAL_FIRM}\Shared Tools\MSDatLst.dep; ValueType: string; ValueName: Path; ValueData: {sys}\MSDATLST.DEP
Root: HKLM; Subkey: SOFTWARE\{#VISUAL_FIRM}\Shared Tools\MSDatLst.dep\Clients; ValueType: string; ValueName: {app}\VC98\Setup\1033\VC98PRO.DLL
Root: HKLM; Subkey: SOFTWARE\{#VISUAL_FIRM}\Shared Tools\msdatlst.ocx; ValueType: string; ValueName: Path; ValueData: {sys}\MSDATLST.OCX
Root: HKLM; Subkey: SOFTWARE\{#VISUAL_FIRM}\Shared Tools\msdatlst.ocx\Clients; ValueType: string; ValueName: {app}\VC98\Setup\1033\VC98PRO.DLL
Root: HKLM; Subkey: SOFTWARE\{#VISUAL_FIRM}\Shared Tools\MSDatRep.dep; ValueType: string; ValueName: Path; ValueData: {sys}\MSDATREP.DEP
Root: HKLM; Subkey: SOFTWARE\{#VISUAL_FIRM}\Shared Tools\MSDatRep.dep\Clients; ValueType: string; ValueName: {app}\VC98\Setup\1033\VC98PRO.DLL
Root: HKLM; Subkey: SOFTWARE\{#VISUAL_FIRM}\Shared Tools\MSDatRep.ocx; ValueType: string; ValueName: Path; ValueData: {sys}\MSDATREP.OCX
Root: HKLM; Subkey: SOFTWARE\{#VISUAL_FIRM}\Shared Tools\MSDatRep.ocx\Clients; ValueType: string; ValueName: {app}\VC98\Setup\1033\VC98PRO.DLL
Root: HKLM; Subkey: SOFTWARE\{#VISUAL_FIRM}\Shared Tools\msdev.com; ValueType: string; ValueName: Path; ValueData: {app}\Common\MSDev98\Bin\MSDEV.COM
Root: HKLM; Subkey: SOFTWARE\{#VISUAL_FIRM}\Shared Tools\msdev.com\Clients; ValueType: string; ValueName: {app}\VC98\Setup\1033\VC98PRO.DLL
Root: HKLM; Subkey: SOFTWARE\{#VISUAL_FIRM}\Shared Tools\msdev.exe; ValueType: string; ValueName: Path; ValueData: {app}\Common\MSDev98\Bin\MSDEV.EXE
Root: HKLM; Subkey: SOFTWARE\{#VISUAL_FIRM}\Shared Tools\msdev.exe\Clients; ValueType: string; ValueName: {app}\VC98\Setup\1033\VC98PRO.DLL
Root: HKLM; Subkey: SOFTWARE\{#VISUAL_FIRM}\Shared Tools\msdev.hlp; ValueType: string; ValueName: Path; ValueData: {app}\Common\MSDev98\Help\MSDEV.HLP
Root: HKLM; Subkey: SOFTWARE\{#VISUAL_FIRM}\Shared Tools\msdev.hlp\Clients; ValueType: string; ValueName: {app}\VC98\Setup\1033\VC98PRO.DLL
Root: HKLM; Subkey: SOFTWARE\{#VISUAL_FIRM}\Shared Tools\msdev.tip; ValueType: string; ValueName: Path; ValueData: {app}\Common\MSDev98\Bin\IDE\MSDEV.TIP
Root: HKLM; Subkey: SOFTWARE\{#VISUAL_FIRM}\Shared Tools\msdev.tip\Clients; ValueType: string; ValueName: {app}\VC98\Setup\1033\VC98PRO.DLL
Root: HKLM; Subkey: SOFTWARE\{#VISUAL_FIRM}\Shared Tools\msdis110.dll; ValueType: string; ValueName: Path; ValueData: {app}\Common\MSDev98\Bin\MSDIS110.DLL
Root: HKLM; Subkey: SOFTWARE\{#VISUAL_FIRM}\Shared Tools\msdis110.dll\Clients; ValueType: string; ValueName: {app}\VC98\Setup\1033\VC98PRO.DLL
Root: HKLM; Subkey: SOFTWARE\{#VISUAL_FIRM}\Shared Tools\msflxgrd.dep; ValueType: string; ValueName: Path; ValueData: {sys}\MSFLXGRD.DEP
Root: HKLM; Subkey: SOFTWARE\{#VISUAL_FIRM}\Shared Tools\msflxgrd.dep\Clients; ValueType: string; ValueName: {app}\VC98\Setup\1033\VC98PRO.DLL
Root: HKLM; Subkey: SOFTWARE\{#VISUAL_FIRM}\Shared Tools\msflxgrd.ocx; ValueType: string; ValueName: Path; ValueData: {sys}\MSFLXGRD.OCX
Root: HKLM; Subkey: SOFTWARE\{#VISUAL_FIRM}\Shared Tools\msflxgrd.ocx\Clients; ValueType: string; ValueName: {app}\VC98\Setup\1033\VC98PRO.DLL
Root: HKLM; Subkey: SOFTWARE\{#VISUAL_FIRM}\Shared Tools\mshflxgd.ocx; ValueType: string; ValueName: Path; ValueData: {sys}\MSHFLXGD.OCX
Root: HKLM; Subkey: SOFTWARE\{#VISUAL_FIRM}\Shared Tools\mshflxgd.ocx\Clients; ValueType: string; ValueName: {app}\VC98\Setup\1033\VC98PRO.DLL
Root: HKLM; Subkey: SOFTWARE\{#VISUAL_FIRM}\Shared Tools\msinet.dep; ValueType: string; ValueName: Path; ValueData: {sys}\MSINET.DEP
Root: HKLM; Subkey: SOFTWARE\{#VISUAL_FIRM}\Shared Tools\msinet.dep\Clients; ValueType: string; ValueName: {app}\VC98\Setup\1033\VC98PRO.DLL
Root: HKLM; Subkey: SOFTWARE\{#VISUAL_FIRM}\Shared Tools\msinet.ocx; ValueType: string; ValueName: Path; ValueData: {sys}\MSINET.OCX
Root: HKLM; Subkey: SOFTWARE\{#VISUAL_FIRM}\Shared Tools\msinet.ocx\Clients; ValueType: string; ValueName: {app}\VC98\Setup\1033\VC98PRO.DLL
Root: HKLM; Subkey: SOFTWARE\{#VISUAL_FIRM}\Shared Tools\msmapi32.dep; ValueType: string; ValueName: Path; ValueData: {sys}\MSMAPI32.DEP
Root: HKLM; Subkey: SOFTWARE\{#VISUAL_FIRM}\Shared Tools\msmapi32.dep\Clients; ValueType: string; ValueName: {app}\VC98\Setup\1033\VC98PRO.DLL
Root: HKLM; Subkey: SOFTWARE\{#VISUAL_FIRM}\Shared Tools\msmapi32.ocx; ValueType: string; ValueName: Path; ValueData: {sys}\MSMAPI32.OCX
Root: HKLM; Subkey: SOFTWARE\{#VISUAL_FIRM}\Shared Tools\msmapi32.ocx\Clients; ValueType: string; ValueName: {app}\VC98\Setup\1033\VC98PRO.DLL
Root: HKLM; Subkey: SOFTWARE\{#VISUAL_FIRM}\Shared Tools\msmask32.dep; ValueType: string; ValueName: Path; ValueData: {sys}\MSMASK32.DEP
Root: HKLM; Subkey: SOFTWARE\{#VISUAL_FIRM}\Shared Tools\msmask32.dep\Clients; ValueType: string; ValueName: {app}\VC98\Setup\1033\VC98PRO.DLL
Root: HKLM; Subkey: SOFTWARE\{#VISUAL_FIRM}\Shared Tools\msmask32.ocx; ValueType: string; ValueName: Path; ValueData: {sys}\MSMASK32.OCX
Root: HKLM; Subkey: SOFTWARE\{#VISUAL_FIRM}\Shared Tools\msmask32.ocx\Clients; ValueType: string; ValueName: {app}\VC98\Setup\1033\VC98PRO.DLL
Root: HKLM; Subkey: SOFTWARE\{#VISUAL_FIRM}\Shared Tools\mspdb60.dll; ValueType: string; ValueName: Path; ValueData: {app}\Common\MSDev98\Bin\MSPDB60.DLL
Root: HKLM; Subkey: SOFTWARE\{#VISUAL_FIRM}\Shared Tools\mspdb60.dll\Clients; ValueType: string; ValueName: {app}\VC98\Setup\1033\VC98PRO.DLL
Root: HKLM; Subkey: SOFTWARE\{#VISUAL_FIRM}\Shared Tools\msrdc20.dep; ValueType: string; ValueName: Path; ValueData: {sys}\MSRDC20.DEP
Root: HKLM; Subkey: SOFTWARE\{#VISUAL_FIRM}\Shared Tools\msrdc20.dep\Clients; ValueType: string; ValueName: {app}\VC98\Setup\1033\VC98PRO.DLL
Root: HKLM; Subkey: SOFTWARE\{#VISUAL_FIRM}\Shared Tools\msrdc20.ocx; ValueType: string; ValueName: Path; ValueData: {sys}\MSRDC20.OCX
Root: HKLM; Subkey: SOFTWARE\{#VISUAL_FIRM}\Shared Tools\msrdc20.ocx\Clients; ValueType: string; ValueName: {app}\VC98\Setup\1033\VC98PRO.DLL
Root: HKLM; Subkey: SOFTWARE\{#VISUAL_FIRM}\Shared Tools\msrdo20.dep; ValueType: string; ValueName: Path; ValueData: {sys}\MSRDO20.DEP
Root: HKLM; Subkey: SOFTWARE\{#VISUAL_FIRM}\Shared Tools\msrdo20.dep\Clients; ValueType: string; ValueName: {app}\VC98\Setup\1033\VC98PRO.DLL
Root: HKLM; Subkey: SOFTWARE\{#VISUAL_FIRM}\Shared Tools\msrdo20.dll; ValueType: string; ValueName: Path; ValueData: {sys}\MSRDO20.DLL
Root: HKLM; Subkey: SOFTWARE\{#VISUAL_FIRM}\Shared Tools\msrdo20.dll\Clients; ValueType: string; ValueName: {app}\VC98\Setup\1033\VC98PRO.DLL
Root: HKLM; Subkey: SOFTWARE\{#VISUAL_FIRM}\Shared Tools\msstdfmt.dll; ValueType: string; ValueName: Path; ValueData: {sys}\MSSTDFMT.DLL
Root: HKLM; Subkey: SOFTWARE\{#VISUAL_FIRM}\Shared Tools\msstdfmt.dll\Clients; ValueType: string; ValueName: {app}\VC98\Setup\1033\VC98PRO.DLL
Root: HKLM; Subkey: SOFTWARE\{#VISUAL_FIRM}\Shared Tools\msvcp60.dll; ValueType: string; ValueName: Path; ValueData: {sys}\msvcp60.dll
Root: HKLM; Subkey: SOFTWARE\{#VISUAL_FIRM}\Shared Tools\msvcp60.dll\Clients; ValueType: string; ValueName: {app}\VC98\Setup\1033\VC98PRO.DLL
Root: HKLM; Subkey: SOFTWARE\{#VISUAL_FIRM}\Shared Tools\mswinsck.dep; ValueType: string; ValueName: Path; ValueData: {sys}\MSWINSCK.DEP
Root: HKLM; Subkey: SOFTWARE\{#VISUAL_FIRM}\Shared Tools\mswinsck.dep\Clients; ValueType: string; ValueName: {app}\VC98\Setup\1033\VC98PRO.DLL
Root: HKLM; Subkey: SOFTWARE\{#VISUAL_FIRM}\Shared Tools\mswinsck.ocx; ValueType: string; ValueName: Path; ValueData: {sys}\MSWINSCK.OCX
Root: HKLM; Subkey: SOFTWARE\{#VISUAL_FIRM}\Shared Tools\mswinsck.ocx\Clients; ValueType: string; ValueName: {app}\VC98\Setup\1033\VC98PRO.DLL
Root: HKLM; Subkey: SOFTWARE\{#VISUAL_FIRM}\Shared Tools\occ.dll; ValueType: string; ValueName: Path; ValueData: {app}\Common\MSDev98\Bin\IDE\OCC.DLL
Root: HKLM; Subkey: SOFTWARE\{#VISUAL_FIRM}\Shared Tools\occ.dll\Clients; ValueType: string; ValueName: {app}\VC98\Setup\1033\VC98PRO.DLL
Root: HKLM; Subkey: SOFTWARE\{#VISUAL_FIRM}\Shared Tools\occ.hlp; ValueType: string; ValueName: Path; ValueData: {app}\Common\MSDev98\Bin\IDE\OCC.HLP
Root: HKLM; Subkey: SOFTWARE\{#VISUAL_FIRM}\Shared Tools\occ.hlp\Clients; ValueType: string; ValueName: {app}\VC98\Setup\1033\VC98PRO.DLL
Root: HKLM; Subkey: SOFTWARE\{#VISUAL_FIRM}\Shared Tools\oletools.hlp; ValueType: string; ValueName: Path; ValueData: {app}\Common\Tools\OLETOOLS.HLP
Root: HKLM; Subkey: SOFTWARE\{#VISUAL_FIRM}\Shared Tools\oletools.hlp\Clients; ValueType: string; ValueName: {app}\VC98\Setup\1033\VC98PRO.DLL
Root: HKLM; Subkey: SOFTWARE\{#VISUAL_FIRM}\Shared Tools\oleview.exe; ValueType: string; ValueName: Path; ValueData: {app}\Common\Tools\OLEVIEW.EXE
Root: HKLM; Subkey: SOFTWARE\{#VISUAL_FIRM}\Shared Tools\oleview.exe\Clients; ValueType: string; ValueName: {app}\VC98\Setup\1033\VC98PRO.DLL
Root: HKLM; Subkey: SOFTWARE\{#VISUAL_FIRM}\Shared Tools\owndraw.dll; ValueType: string; ValueName: Path; ValueData: {app}\Common\MSDev98\Bin\IDE\OWNDRAW.DLL
Root: HKLM; Subkey: SOFTWARE\{#VISUAL_FIRM}\Shared Tools\owndraw.dll\Clients; ValueType: string; ValueName: {app}\VC98\Setup\1033\VC98PRO.DLL
Root: HKLM; Subkey: SOFTWARE\{#VISUAL_FIRM}\Shared Tools\owndraw.hlp; ValueType: string; ValueName: Path; ValueData: {app}\Common\MSDev98\Bin\IDE\OWNDRAW.HLP
Root: HKLM; Subkey: SOFTWARE\{#VISUAL_FIRM}\Shared Tools\owndraw.hlp\Clients; ValueType: string; ValueName: {app}\VC98\Setup\1033\VC98PRO.DLL
Root: HKLM; Subkey: SOFTWARE\{#VISUAL_FIRM}\Shared Tools\palette.dll; ValueType: string; ValueName: Path; ValueData: {app}\Common\MSDev98\Bin\IDE\PALETTE.DLL
Root: HKLM; Subkey: SOFTWARE\{#VISUAL_FIRM}\Shared Tools\palette.dll\Clients; ValueType: string; ValueName: {app}\VC98\Setup\1033\VC98PRO.DLL
Root: HKLM; Subkey: SOFTWARE\{#VISUAL_FIRM}\Shared Tools\palette.hlp; ValueType: string; ValueName: Path; ValueData: {app}\Common\MSDev98\Bin\IDE\PALETTE.HLP
Root: HKLM; Subkey: SOFTWARE\{#VISUAL_FIRM}\Shared Tools\palette.hlp\Clients; ValueType: string; ValueName: {app}\VC98\Setup\1033\VC98PRO.DLL
Root: HKLM; Subkey: SOFTWARE\{#VISUAL_FIRM}\Shared Tools\picclp32.dep; ValueType: string; ValueName: Path; ValueData: {sys}\PICCLP32.DEP
Root: HKLM; Subkey: SOFTWARE\{#VISUAL_FIRM}\Shared Tools\picclp32.dep\Clients; ValueType: string; ValueName: {app}\VC98\Setup\1033\VC98PRO.DLL
Root: HKLM; Subkey: SOFTWARE\{#VISUAL_FIRM}\Shared Tools\picclp32.ocx; ValueType: string; ValueName: Path; ValueData: {sys}\PICCLP32.OCX
Root: HKLM; Subkey: SOFTWARE\{#VISUAL_FIRM}\Shared Tools\picclp32.ocx\Clients; ValueType: string; ValueName: {app}\VC98\Setup\1033\VC98PRO.DLL
Root: HKLM; Subkey: SOFTWARE\{#VISUAL_FIRM}\Shared Tools\popup.dll; ValueType: string; ValueName: Path; ValueData: {app}\Common\MSDev98\Bin\IDE\POPUP.DLL
Root: HKLM; Subkey: SOFTWARE\{#VISUAL_FIRM}\Shared Tools\popup.dll\Clients; ValueType: string; ValueName: {app}\VC98\Setup\1033\VC98PRO.DLL
Root: HKLM; Subkey: SOFTWARE\{#VISUAL_FIRM}\Shared Tools\popup.hlp; ValueType: string; ValueName: Path; ValueData: {app}\Common\MSDev98\Bin\IDE\POPUP.HLP
Root: HKLM; Subkey: SOFTWARE\{#VISUAL_FIRM}\Shared Tools\popup.hlp\Clients; ValueType: string; ValueName: {app}\VC98\Setup\1033\VC98PRO.DLL
Root: HKLM; Subkey: SOFTWARE\{#VISUAL_FIRM}\Shared Tools\progdlg.dll; ValueType: string; ValueName: Path; ValueData: {app}\Common\MSDev98\Bin\IDE\PROGDLG.DLL
Root: HKLM; Subkey: SOFTWARE\{#VISUAL_FIRM}\Shared Tools\progdlg.dll\Clients; ValueType: string; ValueName: {app}\VC98\Setup\1033\VC98PRO.DLL
Root: HKLM; Subkey: SOFTWARE\{#VISUAL_FIRM}\Shared Tools\progdlg.hlp; ValueType: string; ValueName: Path; ValueData: {app}\Common\MSDev98\Bin\IDE\PROGDLG.HLP
Root: HKLM; Subkey: SOFTWARE\{#VISUAL_FIRM}\Shared Tools\progdlg.hlp\Clients; ValueType: string; ValueName: {app}\VC98\Setup\1033\VC98PRO.DLL
Root: HKLM; Subkey: SOFTWARE\{#VISUAL_FIRM}\Shared Tools\propsht.dll; ValueType: string; ValueName: Path; ValueData: {app}\Common\MSDev98\Bin\IDE\PROPSHT.DLL
Root: HKLM; Subkey: SOFTWARE\{#VISUAL_FIRM}\Shared Tools\propsht.dll\Clients; ValueType: string; ValueName: {app}\VC98\Setup\1033\VC98PRO.DLL
Root: HKLM; Subkey: SOFTWARE\{#VISUAL_FIRM}\Shared Tools\propsht.hlp; ValueType: string; ValueName: Path; ValueData: {app}\Common\MSDev98\Bin\IDE\PROPSHT.HLP
Root: HKLM; Subkey: SOFTWARE\{#VISUAL_FIRM}\Shared Tools\propsht.hlp\Clients; ValueType: string; ValueName: {app}\VC98\Setup\1033\VC98PRO.DLL
Root: HKLM; Subkey: SOFTWARE\{#VISUAL_FIRM}\Shared Tools\psapi.dll; ValueType: string; ValueName: Path; ValueData: {sys}\psapi.dll
Root: HKLM; Subkey: SOFTWARE\{#VISUAL_FIRM}\Shared Tools\psapi.dll\Clients; ValueType: string; ValueName: {app}\VC98\Setup\1033\VC98PRO.DLL
Root: HKLM; Subkey: SOFTWARE\{#VISUAL_FIRM}\Shared Tools\pstat.exe; ValueType: string; ValueName: Path; ValueData: {app}\Common\Tools\WinNT\PSTAT.EXE
Root: HKLM; Subkey: SOFTWARE\{#VISUAL_FIRM}\Shared Tools\pstat.exe\Clients; ValueType: string; ValueName: {app}\VC98\Setup\1033\VC98PRO.DLL
Root: HKLM; Subkey: SOFTWARE\{#VISUAL_FIRM}\Shared Tools\pview.exe; ValueType: string; ValueName: Path; ValueData: {app}\Common\Tools\WinNT\PVIEW.EXE
Root: HKLM; Subkey: SOFTWARE\{#VISUAL_FIRM}\Shared Tools\pview.exe\Clients; ValueType: string; ValueName: {app}\VC98\Setup\1033\VC98PRO.DLL
Root: HKLM; Subkey: SOFTWARE\{#VISUAL_FIRM}\Shared Tools\repodbc.dll_v6; ValueType: string; ValueName: Path; ValueData: {cf}\Microsoft Shared\Repostry\REPODBC.DLL
Root: HKLM; Subkey: SOFTWARE\{#VISUAL_FIRM}\Shared Tools\repodbc.dll_v6\Clients; ValueType: string; ValueName: {app}\VC98\Setup\1033\VC98PRO.DLL; ValueData: 
Root: HKLM; Subkey: SOFTWARE\{#VISUAL_FIRM}\Shared Tools\reprc.dll_v6; ValueType: string; ValueName: Path; ValueData: {cf}\Microsoft Shared\Repostry\REPRC.DLL
Root: HKLM; Subkey: SOFTWARE\{#VISUAL_FIRM}\Shared Tools\reprc.dll_v6\Clients; ValueType: string; ValueName: {app}\VC98\Setup\1033\VC98PRO.DLL; ValueData: 
Root: HKLM; Subkey: SOFTWARE\{#VISUAL_FIRM}\Shared Tools\richtx32.dep; ValueType: string; ValueName: Path; ValueData: {sys}\RICHTX32.DEP
Root: HKLM; Subkey: SOFTWARE\{#VISUAL_FIRM}\Shared Tools\richtx32.dep\Clients; ValueType: string; ValueName: {app}\VC98\Setup\1033\VC98PRO.DLL
Root: HKLM; Subkey: SOFTWARE\{#VISUAL_FIRM}\Shared Tools\richtx32.ocx; ValueType: string; ValueName: Path; ValueData: {sys}\RICHTX32.OCX
Root: HKLM; Subkey: SOFTWARE\{#VISUAL_FIRM}\Shared Tools\richtx32.ocx\Clients; ValueType: string; ValueName: {app}\VC98\Setup\1033\VC98PRO.DLL
Root: HKLM; Subkey: SOFTWARE\{#VISUAL_FIRM}\Shared Tools\sample.dsm; ValueType: string; ValueName: Path; ValueData: {app}\Common\MSDev98\Macros\SAMPLE.DSM
Root: HKLM; Subkey: SOFTWARE\{#VISUAL_FIRM}\Shared Tools\sample.dsm\Clients; ValueType: string; ValueName: {app}\VC98\Setup\1033\VC98PRO.DLL
Root: HKLM; Subkey: SOFTWARE\{#VISUAL_FIRM}\Shared Tools\selfreg.dll; ValueType: string; ValueName: Path; ValueData: {sys}\SELFREG.DLL
Root: HKLM; Subkey: SOFTWARE\{#VISUAL_FIRM}\Shared Tools\selfreg.dll\Clients; ValueType: string; ValueName: {app}\VC98\Setup\1033\VC98PRO.DLL
#ifdef VISUAL_MSDN
Root: HKLM; Subkey: SOFTWARE\{#VISUAL_FIRM}\Shared Tools\selfreg.dll\Clients; ValueType: string; ValueName: {app}\MSDN98\98VSa\1036\Setup\MSDN98.DLL; Components: Msdn
#endif
Root: HKLM; Subkey: SOFTWARE\{#VISUAL_FIRM}\Shared Tools\shcv.dll; ValueType: string; ValueName: Path; ValueData: {app}\Common\MSDev98\Bin\SHCV.DLL
Root: HKLM; Subkey: SOFTWARE\{#VISUAL_FIRM}\Shared Tools\shcv.dll\Clients; ValueType: string; ValueName: {app}\VC98\Setup\1033\VC98PRO.DLL
Root: HKLM; Subkey: SOFTWARE\{#VISUAL_FIRM}\Shared Tools\shed.exe; ValueType: string; ValueName: Path; ValueData: {app}\Common\Tools\SHED.EXE
Root: HKLM; Subkey: SOFTWARE\{#VISUAL_FIRM}\Shared Tools\shed.exe\Clients; ValueType: string; ValueName: {app}\VC98\Setup\1033\VC98PRO.DLL
Root: HKLM; Subkey: SOFTWARE\{#VISUAL_FIRM}\Shared Tools\shed.hlp; ValueType: string; ValueName: Path; ValueData: {app}\Common\Tools\SHED.HLP
Root: HKLM; Subkey: SOFTWARE\{#VISUAL_FIRM}\Shared Tools\shed.hlp\Clients; ValueType: string; ValueName: {app}\VC98\Setup\1033\VC98PRO.DLL
Root: HKLM; Subkey: SOFTWARE\{#VISUAL_FIRM}\Shared Tools\sockets.dll; ValueType: string; ValueName: Path; ValueData: {app}\Common\MSDev98\Bin\IDE\SOCKETS.DLL
Root: HKLM; Subkey: SOFTWARE\{#VISUAL_FIRM}\Shared Tools\sockets.dll\Clients; ValueType: string; ValueName: {app}\VC98\Setup\1033\VC98PRO.DLL
Root: HKLM; Subkey: SOFTWARE\{#VISUAL_FIRM}\Shared Tools\sockets.hlp; ValueType: string; ValueName: Path; ValueData: {app}\Common\MSDev98\Bin\IDE\SOCKETS.HLP
Root: HKLM; Subkey: SOFTWARE\{#VISUAL_FIRM}\Shared Tools\sockets.hlp\Clients; ValueType: string; ValueName: {app}\VC98\Setup\1033\VC98PRO.DLL
Root: HKLM; Subkey: SOFTWARE\{#VISUAL_FIRM}\Shared Tools\splash.dll; ValueType: string; ValueName: Path; ValueData: {app}\Common\MSDev98\Bin\IDE\SPLASH.DLL
Root: HKLM; Subkey: SOFTWARE\{#VISUAL_FIRM}\Shared Tools\splash.dll\Clients; ValueType: string; ValueName: {app}\VC98\Setup\1033\VC98PRO.DLL
Root: HKLM; Subkey: SOFTWARE\{#VISUAL_FIRM}\Shared Tools\splash.hlp; ValueType: string; ValueName: Path; ValueData: {app}\Common\MSDev98\Bin\IDE\SPLASH.HLP
Root: HKLM; Subkey: SOFTWARE\{#VISUAL_FIRM}\Shared Tools\splash.hlp\Clients; ValueType: string; ValueName: {app}\VC98\Setup\1033\VC98PRO.DLL
Root: HKLM; Subkey: SOFTWARE\{#VISUAL_FIRM}\Shared Tools\splitter.dll; ValueType: string; ValueName: Path; ValueData: {app}\Common\MSDev98\Bin\IDE\SPLITTER.DLL
Root: HKLM; Subkey: SOFTWARE\{#VISUAL_FIRM}\Shared Tools\splitter.dll\Clients; ValueType: string; ValueName: {app}\VC98\Setup\1033\VC98PRO.DLL
Root: HKLM; Subkey: SOFTWARE\{#VISUAL_FIRM}\Shared Tools\splitter.hlp; ValueType: string; ValueName: Path; ValueData: {app}\Common\MSDev98\Bin\IDE\SPLITTER.HLP
Root: HKLM; Subkey: SOFTWARE\{#VISUAL_FIRM}\Shared Tools\splitter.hlp\Clients; ValueType: string; ValueName: {app}\VC98\Setup\1033\VC98PRO.DLL
Root: HKLM; Subkey: SOFTWARE\{#VISUAL_FIRM}\Shared Tools\spyhk55.dll; ValueType: string; ValueName: Path; ValueData: {app}\Common\Tools\SPYHK55.DLL
Root: HKLM; Subkey: SOFTWARE\{#VISUAL_FIRM}\Shared Tools\spyhk55.dll\Clients; ValueType: string; ValueName: {app}\VC98\Setup\1033\VC98PRO.DLL
Root: HKLM; Subkey: SOFTWARE\{#VISUAL_FIRM}\Shared Tools\spyxx.cnt; ValueType: string; ValueName: Path; ValueData: {app}\Common\Tools\SPYXX.CNT
Root: HKLM; Subkey: SOFTWARE\{#VISUAL_FIRM}\Shared Tools\spyxx.cnt\Clients; ValueType: string; ValueName: {app}\VC98\Setup\1033\VC98PRO.DLL
Root: HKLM; Subkey: SOFTWARE\{#VISUAL_FIRM}\Shared Tools\spyxx.exe; ValueType: string; ValueName: Path; ValueData: {app}\Common\Tools\SPYXX.EXE
Root: HKLM; Subkey: SOFTWARE\{#VISUAL_FIRM}\Shared Tools\spyxx.exe\Clients; ValueType: string; ValueName: {app}\VC98\Setup\1033\VC98PRO.DLL
Root: HKLM; Subkey: SOFTWARE\{#VISUAL_FIRM}\Shared Tools\spyxx.hlp; ValueType: string; ValueName: Path; ValueData: {app}\Common\Tools\SPYXX.HLP
Root: HKLM; Subkey: SOFTWARE\{#VISUAL_FIRM}\Shared Tools\spyxx.hlp\Clients; ValueType: string; ValueName: {app}\VC98\Setup\1033\VC98PRO.DLL
Root: HKLM; Subkey: SOFTWARE\{#VISUAL_FIRM}\Shared Tools\sr32test.exe_NT; ValueType: string; ValueName: Path; ValueData: {app}\Common\Tools\WinNT\SR32TEST.EXE
Root: HKLM; Subkey: SOFTWARE\{#VISUAL_FIRM}\Shared Tools\sr32test.exe_NT\Clients; ValueType: string; ValueName: {app}\VC98\Setup\1033\VC98PRO.DLL
Root: HKLM; Subkey: SOFTWARE\{#VISUAL_FIRM}\Shared Tools\statbar.dll; ValueType: string; ValueName: Path; ValueData: {app}\Common\MSDev98\Bin\IDE\STATBAR.DLL
Root: HKLM; Subkey: SOFTWARE\{#VISUAL_FIRM}\Shared Tools\statbar.dll\Clients; ValueType: string; ValueName: {app}\VC98\Setup\1033\VC98PRO.DLL
Root: HKLM; Subkey: SOFTWARE\{#VISUAL_FIRM}\Shared Tools\statbar.hlp; ValueType: string; ValueName: Path; ValueData: {app}\Common\MSDev98\Bin\IDE\STATBAR.HLP
Root: HKLM; Subkey: SOFTWARE\{#VISUAL_FIRM}\Shared Tools\statbar.hlp\Clients; ValueType: string; ValueName: {app}\VC98\Setup\1033\VC98PRO.DLL
Root: HKLM; Subkey: SOFTWARE\{#VISUAL_FIRM}\Shared Tools\sysincl.dat; ValueType: string; ValueName: Path; ValueData: {app}\Common\MSDev98\Bin\SYSINCL.DAT
Root: HKLM; Subkey: SOFTWARE\{#VISUAL_FIRM}\Shared Tools\sysincl.dat\Clients; ValueType: string; ValueName: {app}\VC98\Setup\1033\VC98PRO.DLL
Root: HKLM; Subkey: SOFTWARE\{#VISUAL_FIRM}\Shared Tools\sysinfo.dep; ValueType: string; ValueName: Path; ValueData: {sys}\SYSINFO.DEP
Root: HKLM; Subkey: SOFTWARE\{#VISUAL_FIRM}\Shared Tools\sysinfo.dep\Clients; ValueType: string; ValueName: {app}\VC98\Setup\1033\VC98PRO.DLL
Root: HKLM; Subkey: SOFTWARE\{#VISUAL_FIRM}\Shared Tools\sysinfo.dll; ValueType: string; ValueName: Path; ValueData: {app}\Common\MSDev98\Bin\IDE\SYSINFO.DLL
Root: HKLM; Subkey: SOFTWARE\{#VISUAL_FIRM}\Shared Tools\sysinfo.dll\Clients; ValueType: string; ValueName: {app}\VC98\Setup\1033\VC98PRO.DLL
Root: HKLM; Subkey: SOFTWARE\{#VISUAL_FIRM}\Shared Tools\sysinfo.hlp; ValueType: string; ValueName: Path; ValueData: {app}\Common\MSDev98\Bin\IDE\SYSINFO.HLP
Root: HKLM; Subkey: SOFTWARE\{#VISUAL_FIRM}\Shared Tools\sysinfo.hlp\Clients; ValueType: string; ValueName: {app}\VC98\Setup\1033\VC98PRO.DLL
Root: HKLM; Subkey: SOFTWARE\{#VISUAL_FIRM}\Shared Tools\sysinfo.ocx; ValueType: string; ValueName: Path; ValueData: {sys}\SYSINFO.OCX
Root: HKLM; Subkey: SOFTWARE\{#VISUAL_FIRM}\Shared Tools\sysinfo.ocx\Clients; ValueType: string; ValueName: {app}\VC98\Setup\1033\VC98PRO.DLL
Root: HKLM; Subkey: SOFTWARE\{#VISUAL_FIRM}\Shared Tools\tabctl32.dep; ValueType: string; ValueName: Path; ValueData: {sys}\TABCTL32.DEP
Root: HKLM; Subkey: SOFTWARE\{#VISUAL_FIRM}\Shared Tools\tabctl32.dep\Clients; ValueType: string; ValueName: {app}\VC98\Setup\1033\VC98PRO.DLL
Root: HKLM; Subkey: SOFTWARE\{#VISUAL_FIRM}\Shared Tools\tabctl32.ocx; ValueType: string; ValueName: Path; ValueData: {sys}\TABCTL32.OCX
Root: HKLM; Subkey: SOFTWARE\{#VISUAL_FIRM}\Shared Tools\tabctl32.ocx\Clients; ValueType: string; ValueName: {app}\VC98\Setup\1033\VC98PRO.DLL
Root: HKLM; Subkey: SOFTWARE\{#VISUAL_FIRM}\Shared Tools\tcprops.dll; ValueType: string; ValueName: Path; ValueData: {app}\Common\Tools\TCPROPS.DLL
Root: HKLM; Subkey: SOFTWARE\{#VISUAL_FIRM}\Shared Tools\tcprops.dll\Clients; ValueType: string; ValueName: {app}\VC98\Setup\1033\VC98PRO.DLL
Root: HKLM; Subkey: SOFTWARE\{#VISUAL_FIRM}\Shared Tools\tools.tip; ValueType: string; ValueName: Path; ValueData: {app}\Common\MSDev98\Bin\IDE\TOOLS.TIP
Root: HKLM; Subkey: SOFTWARE\{#VISUAL_FIRM}\Shared Tools\tools.tip\Clients; ValueType: string; ValueName: {app}\VC98\Setup\1033\VC98PRO.DLL
Root: HKLM; Subkey: SOFTWARE\{#VISUAL_FIRM}\Shared Tools\tooltips.dll; ValueType: string; ValueName: Path; ValueData: {app}\Common\MSDev98\Bin\IDE\TOOLTIPS.DLL
Root: HKLM; Subkey: SOFTWARE\{#VISUAL_FIRM}\Shared Tools\tooltips.dll\Clients; ValueType: string; ValueName: {app}\VC98\Setup\1033\VC98PRO.DLL
Root: HKLM; Subkey: SOFTWARE\{#VISUAL_FIRM}\Shared Tools\tooltips.hlp; ValueType: string; ValueName: Path; ValueData: {app}\Common\MSDev98\Bin\IDE\TOOLTIPS.HLP
Root: HKLM; Subkey: SOFTWARE\{#VISUAL_FIRM}\Shared Tools\tooltips.hlp\Clients; ValueType: string; ValueName: {app}\VC98\Setup\1033\VC98PRO.DLL
Root: HKLM; Subkey: SOFTWARE\{#VISUAL_FIRM}\Shared Tools\tracer.exe; ValueType: string; ValueName: Path; ValueData: {app}\Common\Tools\TRACER.EXE
Root: HKLM; Subkey: SOFTWARE\{#VISUAL_FIRM}\Shared Tools\tracer.exe\Clients; ValueType: string; ValueName: {app}\VC98\Setup\1033\VC98PRO.DLL
Root: HKLM; Subkey: SOFTWARE\{#VISUAL_FIRM}\Shared Tools\tstcon32.cnt; ValueType: string; ValueName: Path; ValueData: {app}\Common\Tools\TSTCON32.CNT
Root: HKLM; Subkey: SOFTWARE\{#VISUAL_FIRM}\Shared Tools\tstcon32.cnt\Clients; ValueType: string; ValueName: {app}\VC98\Setup\1033\VC98PRO.DLL
Root: HKLM; Subkey: SOFTWARE\{#VISUAL_FIRM}\Shared Tools\tstcon32.exe; ValueType: string; ValueName: Path; ValueData: {app}\Common\Tools\TSTCON32.EXE
Root: HKLM; Subkey: SOFTWARE\{#VISUAL_FIRM}\Shared Tools\tstcon32.exe\Clients; ValueType: string; ValueName: {app}\VC98\Setup\1033\VC98PRO.DLL
Root: HKLM; Subkey: SOFTWARE\{#VISUAL_FIRM}\Shared Tools\tstcon32.hlp; ValueType: string; ValueName: Path; ValueData: {app}\Common\Tools\TSTCON32.HLP
Root: HKLM; Subkey: SOFTWARE\{#VISUAL_FIRM}\Shared Tools\tstcon32.hlp\Clients; ValueType: string; ValueName: {app}\VC98\Setup\1033\VC98PRO.DLL
Root: HKLM; Subkey: SOFTWARE\{#VISUAL_FIRM}\Shared Tools\uml.dll; ValueType: string; ValueName: Path; ValueData: {cf}\Microsoft Shared\Repostry\infoMdl\UML.DLL
Root: HKLM; Subkey: SOFTWARE\{#VISUAL_FIRM}\Shared Tools\uml.dll\Clients; ValueType: string; ValueName: {app}\VC98\Setup\1033\VC98PRO.DLL; ValueData: 
Root: HKLM; Subkey: SOFTWARE\{#VISUAL_FIRM}\Shared Tools\undname.exe; ValueType: string; ValueName: Path; ValueData: {app}\Common\Tools\UNDNAME.EXE
Root: HKLM; Subkey: SOFTWARE\{#VISUAL_FIRM}\Shared Tools\undname.exe\Clients; ValueType: string; ValueName: {app}\VC98\Setup\1033\VC98PRO.DLL
Root: HKLM; Subkey: SOFTWARE\{#VISUAL_FIRM}\Shared Tools\uuidgen.exe; ValueType: string; ValueName: Path; ValueData: {app}\Common\Tools\UUIDGEN.EXE
Root: HKLM; Subkey: SOFTWARE\{#VISUAL_FIRM}\Shared Tools\uuidgen.exe\Clients; ValueType: string; ValueName: {app}\VC98\Setup\1033\VC98PRO.DLL
Root: HKLM; Subkey: SOFTWARE\{#VISUAL_FIRM}\Shared Tools\vbcmn98.chi; ValueType: string; ValueName: Path; ValueData: {win}\Help\VBCMN98.CHI
Root: HKLM; Subkey: SOFTWARE\{#VISUAL_FIRM}\Shared Tools\vbcmn98.chi\Clients; ValueType: string; ValueName: {app}\VC98\Setup\1033\VC98PRO.DLL
Root: HKLM; Subkey: SOFTWARE\{#VISUAL_FIRM}\Shared Tools\VCM setup tagfile; ValueType: string; ValueName: Path; ValueData: {app}\Common\Tools\VCM\VCMCAB.DLL
Root: HKLM; Subkey: SOFTWARE\{#VISUAL_FIRM}\Shared Tools\VCM setup tagfile\Clients; ValueType: string; ValueName: {app}\VC98\Setup\1033\VC98PRO.DLL; ValueData: 
Root: HKLM; Subkey: SOFTWARE\{#VISUAL_FIRM}\Shared Tools\vcspawn.exe; ValueType: string; ValueName: Path; ValueData: {app}\Common\MSDev98\Bin\VCSPAWN.EXE
Root: HKLM; Subkey: SOFTWARE\{#VISUAL_FIRM}\Shared Tools\vcspawn.exe\Clients; ValueType: string; ValueName: {app}\VC98\Setup\1033\VC98PRO.DLL
Root: HKLM; Subkey: SOFTWARE\{#VISUAL_FIRM}\Shared Tools\vcxx.tip; ValueType: string; ValueName: Path; ValueData: {app}\Common\MSDev98\Bin\IDE\VCXX.TIP
Root: HKLM; Subkey: SOFTWARE\{#VISUAL_FIRM}\Shared Tools\vcxx.tip\Clients; ValueType: string; ValueName: {app}\VC98\Setup\1033\VC98PRO.DLL
Root: HKLM; Subkey: SOFTWARE\{#VISUAL_FIRM}\Shared Tools\viwzrt.dll; ValueType: string; ValueName: Path; ValueData: {cf}\Microsoft Shared\Wizards98\VIWZRT.DLL
Root: HKLM; Subkey: SOFTWARE\{#VISUAL_FIRM}\Shared Tools\viwzrt.dll\Clients; ValueType: string; ValueName: {app}\VC98\Setup\1033\VC98PRO.DLL
Root: HKLM; Subkey: SOFTWARE\{#VISUAL_FIRM}\Shared Tools\vshelp.dll; ValueType: string; ValueName: Path; ValueData: {cf}\Microsoft Shared\VS98\VSHELP.DLL
Root: HKLM; Subkey: SOFTWARE\{#VISUAL_FIRM}\Shared Tools\vshelp.dll\Clients; ValueType: string; ValueName: {app}\VC98\Setup\1033\VC98PRO.DLL
Root: HKLM; Subkey: SOFTWARE\{#VISUAL_FIRM}\Shared Tools\vshelpui.dll(enu); ValueType: string; ValueName: Path; ValueData: {cf}\Microsoft Shared\VS98\resources\1033\VSHELPUI.DLL
Root: HKLM; Subkey: SOFTWARE\{#VISUAL_FIRM}\Shared Tools\vshelpui.dll(enu)\Clients; ValueType: string; ValueName: {app}\VC98\Setup\1033\VC98PRO.DLL
Root: HKLM; Subkey: SOFTWARE\{#VISUAL_FIRM}\Shared Tools\win32.ncb; ValueType: string; ValueName: Path; ValueData: {app}\Common\MSDev98\Bin\WIN32.NCB
Root: HKLM; Subkey: SOFTWARE\{#VISUAL_FIRM}\Shared Tools\win32.ncb\Clients; ValueType: string; ValueName: {app}\VC98\Setup\1033\VC98PRO.DLL
Root: HKLM; Subkey: SOFTWARE\{#VISUAL_FIRM}\Shared Tools\windiff.exe; ValueType: string; ValueName: Path; ValueData: {app}\Common\Tools\WINDIFF.EXE
Root: HKLM; Subkey: SOFTWARE\{#VISUAL_FIRM}\Shared Tools\windiff.exe\Clients; ValueType: string; ValueName: {app}\VC98\Setup\1033\VC98PRO.DLL
Root: HKLM; Subkey: SOFTWARE\{#VISUAL_FIRM}\Shared Tools\windiff.hlp; ValueType: string; ValueName: Path; ValueData: {app}\Common\Tools\WINDIFF.HLP
Root: HKLM; Subkey: SOFTWARE\{#VISUAL_FIRM}\Shared Tools\windiff.hlp\Clients; ValueType: string; ValueName: {app}\VC98\Setup\1033\VC98PRO.DLL
Root: HKLM; Subkey: SOFTWARE\{#VISUAL_FIRM}\Shared Tools\zoomin.exe; ValueType: string; ValueName: Path; ValueData: {app}\Common\Tools\ZOOMIN.EXE
Root: HKLM; Subkey: SOFTWARE\{#VISUAL_FIRM}\Shared Tools\zoomin.exe\Clients; ValueType: string; ValueName: {app}\VC98\Setup\1033\VC98PRO.DLL

Root: HKLM; Subkey: SOFTWARE\{#VISUAL_FIRM}\Visual Component Manager; ValueType: string; ValueName: RepositoryURL; ValueData: {app}\Common\Tools\VCM\vcm.mdb

#ifdef INSTALL_KALLISTIOS
Root: HKLM; Subkey: SOFTWARE\{#VISUAL_FIRM}\VisualStudio\DC_DK_AW; ValueType: string; ValueName: DevKitDir; ValueData: {sd}\DevKitDC\; Components: KallistiOS
#endif

Root: HKLM; Subkey: SOFTWARE\{#VISUAL_FIRM}\VisualStudio\{#VISUAL_VER}.{#VISUAL_REV}\Menus; ValueType: string; ValueName: {{6A30AD81-10FD-11d1-9603-00600818410C}; ValueData: ,203,22

Root: HKLM; Subkey: SOFTWARE\{#VISUAL_FIRM}\VisualStudio\{#VISUAL_VER}.{#VISUAL_REV}\Packages\{{6A30AD81-10FD-11d1-9603-00600818410C}; ValueType: string; ValueData: Vcm Package
Root: HKLM; Subkey: SOFTWARE\{#VISUAL_FIRM}\VisualStudio\{#VISUAL_VER}.{#VISUAL_REV}\Packages\{{6A30AD81-10FD-11d1-9603-00600818410C}; ValueType: string; ValueName: InprocServer32; ValueData: {app}\Common\IDE\IDE98\VCMPK.DLL
Root: HKLM; Subkey: SOFTWARE\{#VISUAL_FIRM}\VisualStudio\{#VISUAL_VER}.{#VISUAL_REV}\Packages\{{6A30AD81-10FD-11d1-9603-00600818410C}; ValueType: string; ValueName: Preload; ValueData: 1
Root: HKLM; Subkey: SOFTWARE\{#VISUAL_FIRM}\VisualStudio\{#VISUAL_VER}.{#VISUAL_REV}\Packages\{{6A30AD81-10FD-11d1-9603-00600818410C}\SatelliteDll; ValueType: string; ValueName: DllName; ValueData: VCMPKui.DLL
Root: HKLM; Subkey: SOFTWARE\{#VISUAL_FIRM}\VisualStudio\{#VISUAL_VER}.{#VISUAL_REV}\Packages\{{6A30AD81-10FD-11d1-9603-00600818410C}\SatelliteDll; ValueType: string; ValueName: Path; ValueData: {app}\Common\IDE\IDE98\resources\

Root: HKLM; Subkey: SOFTWARE\{#VISUAL_FIRM}\VisualStudio\{#VISUAL_VER}.{#VISUAL_REV}\ServicePacks; ValueType: string; ValueName: sp6; Components: VisualCpp\ServicePack
Root: HKLM; Subkey: SOFTWARE\{#VISUAL_FIRM}\VisualStudio\{#VISUAL_VER}.{#VISUAL_REV}\ServicePacks; ValueType: dword; ValueName: latest; ValueData: $00000006; Components: VisualCpp\ServicePack

Root: HKLM; Subkey: SOFTWARE\{#VISUAL_FIRM}\VisualStudio\{#VISUAL_VER}.{#VISUAL_REV}\Setup; ValueType: string; ValueName: VsCommonDir; ValueData: {app}\Common
Root: HKLM; Subkey: SOFTWARE\{#VISUAL_FIRM}\VisualStudio\{#VISUAL_VER}.{#VISUAL_REV}\Setup\{#VISUAL_FIRM} {#VISUAL_SHORT} {#VISUAL_TYPE}; ValueType: string; ValueName: ProductDir; ValueData: {app}\VC98
Root: HKLM; Subkey: SOFTWARE\{#VISUAL_FIRM}\VisualStudio\{#VISUAL_VER}.{#VISUAL_REV}\Setup\{#VISUAL_FIRM} {#VISUAL_SHORT} {#VISUAL_TYPE}\SetupWizard; ValueType: dword; ValueName: crc; ValueData: $349642a9
Root: HKLM; Subkey: SOFTWARE\{#VISUAL_FIRM}\VisualStudio\{#VISUAL_VER}.{#VISUAL_REV}\Setup\{#VISUAL_FIRM} {#VISUAL_SHORT} {#VISUAL_TYPE}\SetupWizard; ValueType: dword; ValueName: aspo; ValueData: $38395356

Root: HKLM; Subkey: SOFTWARE\{#VISUAL_FIRM}\VisualStudio\{#VISUAL_VER}.{#VISUAL_REV}\Setup\{#VISUAL_FIRM} {#VISUAL_SHORT} {#VISUAL_TYPE}\SetupWizard-1033-PRO; ValueType: dword; ValueName: WizardState; ValueData: $0000001f
Root: HKLM; Subkey: SOFTWARE\{#VISUAL_FIRM}\VisualStudio\{#VISUAL_VER}.{#VISUAL_REV}\Setup\{#VISUAL_FIRM} {#VISUAL_SHORT} {#VISUAL_TYPE}\SetupWizard-1033-PRO; ValueType: dword; ValueName: SP State; ValueData: $00000002
Root: HKLM; Subkey: SOFTWARE\{#VISUAL_FIRM}\VisualStudio\{#VISUAL_VER}.{#VISUAL_REV}\Setup\{#VISUAL_FIRM} {#VISUAL_SHORT} {#VISUAL_TYPE}\SetupWizard-1033-PRO; ValueType: dword; ValueName: IE State; ValueData: $00000002
Root: HKLM; Subkey: SOFTWARE\{#VISUAL_FIRM}\VisualStudio\{#VISUAL_VER}.{#VISUAL_REV}\Setup\{#VISUAL_FIRM} {#VISUAL_SHORT} {#VISUAL_TYPE}\SetupWizard-1033-PRO; ValueType: binary; ValueName: heuristics; ValueData: f0 91 00 a8 20 00 00 00

#ifdef VISUAL_MSDN
Root: HKLM; Subkey: SOFTWARE\{#VISUAL_FIRM}\VisualStudio\{#VISUAL_VER}.{#VISUAL_REV}\Setup\Microsoft Developer Network Library - Visual Studio 6.0a; ValueType: string; ValueName: ProductDir; ValueData: {app}\MSDN98\98VSa\1036; Components: Msdn
#endif

Root: HKLM; Subkey: SOFTWARE\{#VISUAL_FIRM}\VisualStudio\{#VISUAL_VER}.{#VISUAL_REV}\ToolWindows\{{162AD4F0-2BBC-11d1-9617-00600818410C}; ValueType: string; ValueData: {{6A30AD81-10FD-11d1-9603-00600818410C}
Root: HKLM; Subkey: SOFTWARE\{#VISUAL_FIRM}\VisualStudio\{#VISUAL_VER}.{#VISUAL_REV}\ToolWindows\{{162AD4F0-2BBC-11d1-9617-00600818410C}; ValueType: string; ValueName: Style; ValueData: Float
Root: HKLM; Subkey: SOFTWARE\{#VISUAL_FIRM}\VisualStudio\{#VISUAL_VER}.{#VISUAL_REV}\ToolWindows\{{162AD4F0-2BBC-11d1-9617-00600818410C}; ValueType: string; ValueName: Orientation; ValueData: Right
Root: HKLM; Subkey: SOFTWARE\{#VISUAL_FIRM}\VisualStudio\{#VISUAL_VER}.{#VISUAL_REV}\ToolWindows\{{162AD4F0-2BBC-11d1-9617-00600818410C}; ValueType: string; ValueName: FLOAT; ValueData: 300,300,900,700
Root: HKLM; Subkey: SOFTWARE\{#VISUAL_FIRM}\VisualStudio\{#VISUAL_VER}.{#VISUAL_REV}\ToolWindows\{{162AD4F0-2BBC-11d1-9617-00600818410C}; ValueType: string; ValueName: Window; ValueData: {{Eefa5220-e298-11d0-8f78-00a0c9110057}

;Root: HKLM; Subkey: SOFTWARE\{#VISUAL_FIRM}\WBEM\PROVIDERS\Logging; ValueType: dword; ValueName: Logging; ValueData: $00000000; Components: VisualCpp\ServicePack

;Root: HKLM; Subkey: SOFTWARE\{#VISUAL_FIRM}\WBEM\PROVIDERS\Logging\NTEVT; ValueType: dword; ValueName: Level; ValueData: $00000000; Components: VisualCpp\ServicePack
;Root: HKLM; Subkey: SOFTWARE\{#VISUAL_FIRM}\WBEM\PROVIDERS\Logging\NTEVT; ValueType: dword; ValueName: MaxFileSize; ValueData: $0000ffff; Components: VisualCpp\ServicePack
;Root: HKLM; Subkey: SOFTWARE\{#VISUAL_FIRM}\WBEM\PROVIDERS\Logging\NTEVT; ValueType: string; ValueName: File; ValueData: {sys}\WBEM\Logs\NTEVT.log; Components: VisualCpp\ServicePack
;Root: HKLM; Subkey: SOFTWARE\{#VISUAL_FIRM}\WBEM\PROVIDERS\Logging\NTEVT; ValueType: string; ValueName: Type; ValueData: File; Components: VisualCpp\ServicePack

;Root: HKLM; Subkey: SOFTWARE\{#VISUAL_FIRM}\WBEM\PROVIDERS\Logging\WBEMSNMP; ValueType: dword; ValueName: Level; ValueData: $00000000; Components: VisualCpp\ServicePack
;Root: HKLM; Subkey: SOFTWARE\{#VISUAL_FIRM}\WBEM\PROVIDERS\Logging\WBEMSNMP; ValueType: dword; ValueName: MaxFileSize; ValueData: $0000ffff; Components: VisualCpp\ServicePack
;Root: HKLM; Subkey: SOFTWARE\{#VISUAL_FIRM}\WBEM\PROVIDERS\Logging\WBEMSNMP; ValueType: string; ValueName: File; ValueData: {sys}\WBEM\Logs\WBEMSNMP.log; Components: VisualCpp\ServicePack
;Root: HKLM; Subkey: SOFTWARE\{#VISUAL_FIRM}\WBEM\PROVIDERS\Logging\WBEMSNMP; ValueType: string; ValueName: Type; ValueData: File; Components: VisualCpp\ServicePack

Root: HKLM; Subkey: SOFTWARE\{#VISUAL_FIRM}\Windows CE Developer Tools\Windows CE Toolkit for Visual C++ 6.0; ValueType: string; ValueName: ProductDir; ValueData: {app}\Windows CE Tools\; Components: VisualCpp\CeTools

Root: HKLM; Subkey: SOFTWARE\{#VISUAL_FIRM}\Windows CE Developer Tools\Windows CE Toolkit for Visual C++ 6.0\Build System; ValueType: dword; ValueName: AlwaysDownloadBIN; ValueData: $00000001; Components: VisualCpp\CeTools
Root: HKLM; Subkey: SOFTWARE\{#VISUAL_FIRM}\Windows CE Developer Tools\Windows CE Toolkit for Visual C++ 6.0\Build System; ValueType: dword; ValueName: AlwaysDownloadDLLs; ValueData: $00000001; Components: VisualCpp\CeTools

Root: HKLM; Subkey: SOFTWARE\{#VISUAL_FIRM}\Windows CE Developer Tools\Windows CE Toolkit for Visual C++ 6.0\Tools; ValueType: dword; ValueName: AskArgument#0; ValueData: $00000000; Components: VisualCpp\CeTools
Root: HKLM; Subkey: SOFTWARE\{#VISUAL_FIRM}\Windows CE Developer Tools\Windows CE Toolkit for Visual C++ 6.0\Tools; ValueType: dword; ValueName: AskArgument#1; ValueData: $00000000; Components: VisualCpp\CeTools
Root: HKLM; Subkey: SOFTWARE\{#VISUAL_FIRM}\Windows CE Developer Tools\Windows CE Toolkit for Visual C++ 6.0\Tools; ValueType: dword; ValueName: AskArgument#2; ValueData: $00000000; Components: VisualCpp\CeTools
Root: HKLM; Subkey: SOFTWARE\{#VISUAL_FIRM}\Windows CE Developer Tools\Windows CE Toolkit for Visual C++ 6.0\Tools; ValueType: dword; ValueName: AskArgument#3; ValueData: $00000000; Components: VisualCpp\CeTools
Root: HKLM; Subkey: SOFTWARE\{#VISUAL_FIRM}\Windows CE Developer Tools\Windows CE Toolkit for Visual C++ 6.0\Tools; ValueType: dword; ValueName: AskArgument#4; ValueData: $00000000; Components: VisualCpp\CeTools
Root: HKLM; Subkey: SOFTWARE\{#VISUAL_FIRM}\Windows CE Developer Tools\Windows CE Toolkit for Visual C++ 6.0\Tools; ValueType: dword; ValueName: AskArgument#5; ValueData: $00000000; Components: VisualCpp\CeTools

Root: HKLM; Subkey: SOFTWARE\{#VISUAL_FIRM}\Windows CE Developer Tools\Windows CE Toolkit for Visual C++ 6.0\Tools; ValueType: dword; ValueName: CloseWindow#0; ValueData: $00000000; Components: VisualCpp\CeTools
Root: HKLM; Subkey: SOFTWARE\{#VISUAL_FIRM}\Windows CE Developer Tools\Windows CE Toolkit for Visual C++ 6.0\Tools; ValueType: dword; ValueName: CloseWindow#1; ValueData: $00000000; Components: VisualCpp\CeTools
Root: HKLM; Subkey: SOFTWARE\{#VISUAL_FIRM}\Windows CE Developer Tools\Windows CE Toolkit for Visual C++ 6.0\Tools; ValueType: dword; ValueName: CloseWindow#2; ValueData: $00000000; Components: VisualCpp\CeTools
Root: HKLM; Subkey: SOFTWARE\{#VISUAL_FIRM}\Windows CE Developer Tools\Windows CE Toolkit for Visual C++ 6.0\Tools; ValueType: dword; ValueName: CloseWindow#3; ValueData: $00000000; Components: VisualCpp\CeTools
Root: HKLM; Subkey: SOFTWARE\{#VISUAL_FIRM}\Windows CE Developer Tools\Windows CE Toolkit for Visual C++ 6.0\Tools; ValueType: dword; ValueName: CloseWindow#4; ValueData: $00000000; Components: VisualCpp\CeTools
Root: HKLM; Subkey: SOFTWARE\{#VISUAL_FIRM}\Windows CE Developer Tools\Windows CE Toolkit for Visual C++ 6.0\Tools; ValueType: dword; ValueName: CloseWindow#5; ValueData: $00000000; Components: VisualCpp\CeTools

Root: HKLM; Subkey: SOFTWARE\{#VISUAL_FIRM}\Windows CE Developer Tools\Windows CE Toolkit for Visual C++ 6.0\Tools; ValueType: dword; ValueName: GUITool#0; ValueData: $00000001; Components: VisualCpp\CeTools
Root: HKLM; Subkey: SOFTWARE\{#VISUAL_FIRM}\Windows CE Developer Tools\Windows CE Toolkit for Visual C++ 6.0\Tools; ValueType: dword; ValueName: GUITool#1; ValueData: $00000001; Components: VisualCpp\CeTools
Root: HKLM; Subkey: SOFTWARE\{#VISUAL_FIRM}\Windows CE Developer Tools\Windows CE Toolkit for Visual C++ 6.0\Tools; ValueType: dword; ValueName: GUITool#2; ValueData: $00000001; Components: VisualCpp\CeTools
Root: HKLM; Subkey: SOFTWARE\{#VISUAL_FIRM}\Windows CE Developer Tools\Windows CE Toolkit for Visual C++ 6.0\Tools; ValueType: dword; ValueName: GUITool#3; ValueData: $00000001; Components: VisualCpp\CeTools
Root: HKLM; Subkey: SOFTWARE\{#VISUAL_FIRM}\Windows CE Developer Tools\Windows CE Toolkit for Visual C++ 6.0\Tools; ValueType: dword; ValueName: GUITool#4; ValueData: $00000001; Components: VisualCpp\CeTools
Root: HKLM; Subkey: SOFTWARE\{#VISUAL_FIRM}\Windows CE Developer Tools\Windows CE Toolkit for Visual C++ 6.0\Tools; ValueType: dword; ValueName: GUITool#5; ValueData: $00000001; Components: VisualCpp\CeTools

Root: HKLM; Subkey: SOFTWARE\{#VISUAL_FIRM}\Windows CE Developer Tools\Windows CE Toolkit for Visual C++ 6.0\Tools; ValueType: dword; ValueName: NumTools; ValueData: $00000006; Components: VisualCpp\CeTools

Root: HKLM; Subkey: SOFTWARE\{#VISUAL_FIRM}\Windows CE Developer Tools\Windows CE Toolkit for Visual C++ 6.0\Tools; ValueType: dword; ValueName: OutputRedirect#0; ValueData: $00000000; Components: VisualCpp\CeTools
Root: HKLM; Subkey: SOFTWARE\{#VISUAL_FIRM}\Windows CE Developer Tools\Windows CE Toolkit for Visual C++ 6.0\Tools; ValueType: dword; ValueName: OutputRedirect#1; ValueData: $00000000; Components: VisualCpp\CeTools
Root: HKLM; Subkey: SOFTWARE\{#VISUAL_FIRM}\Windows CE Developer Tools\Windows CE Toolkit for Visual C++ 6.0\Tools; ValueType: dword; ValueName: OutputRedirect#2; ValueData: $00000000; Components: VisualCpp\CeTools
Root: HKLM; Subkey: SOFTWARE\{#VISUAL_FIRM}\Windows CE Developer Tools\Windows CE Toolkit for Visual C++ 6.0\Tools; ValueType: dword; ValueName: OutputRedirect#3; ValueData: $00000000; Components: VisualCpp\CeTools
Root: HKLM; Subkey: SOFTWARE\{#VISUAL_FIRM}\Windows CE Developer Tools\Windows CE Toolkit for Visual C++ 6.0\Tools; ValueType: dword; ValueName: OutputRedirect#4; ValueData: $00000000; Components: VisualCpp\CeTools
Root: HKLM; Subkey: SOFTWARE\{#VISUAL_FIRM}\Windows CE Developer Tools\Windows CE Toolkit for Visual C++ 6.0\Tools; ValueType: dword; ValueName: OutputRedirect#5; ValueData: $00000000; Components: VisualCpp\CeTools

Root: HKLM; Subkey: SOFTWARE\{#VISUAL_FIRM}\Windows CE Developer Tools\Windows CE Toolkit for Visual C++ 6.0\Tools; ValueType: dword; ValueName: UseSearchPath#0; ValueData: $00000000; Components: VisualCpp\CeTools
Root: HKLM; Subkey: SOFTWARE\{#VISUAL_FIRM}\Windows CE Developer Tools\Windows CE Toolkit for Visual C++ 6.0\Tools; ValueType: dword; ValueName: UseSearchPath#1; ValueData: $00000000; Components: VisualCpp\CeTools
Root: HKLM; Subkey: SOFTWARE\{#VISUAL_FIRM}\Windows CE Developer Tools\Windows CE Toolkit for Visual C++ 6.0\Tools; ValueType: dword; ValueName: UseSearchPath#2; ValueData: $00000000; Components: VisualCpp\CeTools
Root: HKLM; Subkey: SOFTWARE\{#VISUAL_FIRM}\Windows CE Developer Tools\Windows CE Toolkit for Visual C++ 6.0\Tools; ValueType: dword; ValueName: UseSearchPath#3; ValueData: $00000000; Components: VisualCpp\CeTools
Root: HKLM; Subkey: SOFTWARE\{#VISUAL_FIRM}\Windows CE Developer Tools\Windows CE Toolkit for Visual C++ 6.0\Tools; ValueType: dword; ValueName: UseSearchPath#4; ValueData: $00000000; Components: VisualCpp\CeTools
Root: HKLM; Subkey: SOFTWARE\{#VISUAL_FIRM}\Windows CE Developer Tools\Windows CE Toolkit for Visual C++ 6.0\Tools; ValueType: dword; ValueName: UseSearchPath#5; ValueData: $00000000; Components: VisualCpp\CeTools

Root: HKLM; Subkey: SOFTWARE\{#VISUAL_FIRM}\Windows CE Developer Tools\Windows CE Toolkit for Visual C++ 6.0\Tools; ValueType: string; ValueName: DefaultArguments#0; Components: VisualCpp\CeTools
Root: HKLM; Subkey: SOFTWARE\{#VISUAL_FIRM}\Windows CE Developer Tools\Windows CE Toolkit for Visual C++ 6.0\Tools; ValueType: string; ValueName: DefaultArguments#1; Components: VisualCpp\CeTools
Root: HKLM; Subkey: SOFTWARE\{#VISUAL_FIRM}\Windows CE Developer Tools\Windows CE Toolkit for Visual C++ 6.0\Tools; ValueType: string; ValueName: DefaultArguments#2; Components: VisualCpp\CeTools
Root: HKLM; Subkey: SOFTWARE\{#VISUAL_FIRM}\Windows CE Developer Tools\Windows CE Toolkit for Visual C++ 6.0\Tools; ValueType: string; ValueName: DefaultArguments#3; Components: VisualCpp\CeTools
Root: HKLM; Subkey: SOFTWARE\{#VISUAL_FIRM}\Windows CE Developer Tools\Windows CE Toolkit for Visual C++ 6.0\Tools; ValueType: string; ValueName: DefaultArguments#4; Components: VisualCpp\CeTools
Root: HKLM; Subkey: SOFTWARE\{#VISUAL_FIRM}\Windows CE Developer Tools\Windows CE Toolkit for Visual C++ 6.0\Tools; ValueType: string; ValueName: DefaultArguments#5; Components: VisualCpp\CeTools

Root: HKLM; Subkey: SOFTWARE\{#VISUAL_FIRM}\Windows CE Developer Tools\Windows CE Toolkit for Visual C++ 6.0\Tools; ValueType: string; ValueName: DialogName#0; ValueData: Remote &Spy++; Components: VisualCpp\CeTools
Root: HKLM; Subkey: SOFTWARE\{#VISUAL_FIRM}\Windows CE Developer Tools\Windows CE Toolkit for Visual C++ 6.0\Tools; ValueType: string; ValueName: DialogName#1; ValueData: Remote &Registry Editor; Components: VisualCpp\CeTools
Root: HKLM; Subkey: SOFTWARE\{#VISUAL_FIRM}\Windows CE Developer Tools\Windows CE Toolkit for Visual C++ 6.0\Tools; ValueType: string; ValueName: DialogName#2; ValueData: Remote &Heap Walker; Components: VisualCpp\CeTools
Root: HKLM; Subkey: SOFTWARE\{#VISUAL_FIRM}\Windows CE Developer Tools\Windows CE Toolkit for Visual C++ 6.0\Tools; ValueType: string; ValueName: DialogName#3; ValueData: Remote &Process Viewer; Components: VisualCpp\CeTools
Root: HKLM; Subkey: SOFTWARE\{#VISUAL_FIRM}\Windows CE Developer Tools\Windows CE Toolkit for Visual C++ 6.0\Tools; ValueType: string; ValueName: DialogName#4; ValueData: Remote &Zoomin; Components: VisualCpp\CeTools
Root: HKLM; Subkey: SOFTWARE\{#VISUAL_FIRM}\Windows CE Developer Tools\Windows CE Toolkit for Visual C++ 6.0\Tools; ValueType: string; ValueName: DialogName#5; ValueData: Remote &File Viewer; Components: VisualCpp\CeTools

Root: HKLM; Subkey: SOFTWARE\{#VISUAL_FIRM}\Windows CE Developer Tools\Windows CE Toolkit for Visual C++ 6.0\Tools; ValueType: string; ValueName: InitialDirectory#0; ValueData: {app}\Windows CE Tools\Wce200\bin; Components: VisualCpp\CeTools
Root: HKLM; Subkey: SOFTWARE\{#VISUAL_FIRM}\Windows CE Developer Tools\Windows CE Toolkit for Visual C++ 6.0\Tools; ValueType: string; ValueName: InitialDirectory#1; ValueData: {app}\Windows CE Tools\Wce200\bin; Components: VisualCpp\CeTools
Root: HKLM; Subkey: SOFTWARE\{#VISUAL_FIRM}\Windows CE Developer Tools\Windows CE Toolkit for Visual C++ 6.0\Tools; ValueType: string; ValueName: InitialDirectory#2; ValueData: {app}\Windows CE Tools\Wce200\bin; Components: VisualCpp\CeTools
Root: HKLM; Subkey: SOFTWARE\{#VISUAL_FIRM}\Windows CE Developer Tools\Windows CE Toolkit for Visual C++ 6.0\Tools; ValueType: string; ValueName: InitialDirectory#3; ValueData: {app}\Windows CE Tools\Wce200\bin; Components: VisualCpp\CeTools
Root: HKLM; Subkey: SOFTWARE\{#VISUAL_FIRM}\Windows CE Developer Tools\Windows CE Toolkit for Visual C++ 6.0\Tools; ValueType: string; ValueName: InitialDirectory#4; ValueData: {app}\Windows CE Tools\Wce200\bin; Components: VisualCpp\CeTools
Root: HKLM; Subkey: SOFTWARE\{#VISUAL_FIRM}\Windows CE Developer Tools\Windows CE Toolkit for Visual C++ 6.0\Tools; ValueType: string; ValueName: InitialDirectory#5; ValueData: {app}\Windows CE Tools\Wce200\bin; Components: VisualCpp\CeTools

Root: HKLM; Subkey: SOFTWARE\{#VISUAL_FIRM}\Windows CE Developer Tools\Windows CE Toolkit for Visual C++ 6.0\Tools; ValueType: string; ValueName: MenuName#0; ValueData: Remote &Spy++; Components: VisualCpp\CeTools
Root: HKLM; Subkey: SOFTWARE\{#VISUAL_FIRM}\Windows CE Developer Tools\Windows CE Toolkit for Visual C++ 6.0\Tools; ValueType: string; ValueName: MenuName#1; ValueData: Remote &Registry Editor; Components: VisualCpp\CeTools
Root: HKLM; Subkey: SOFTWARE\{#VISUAL_FIRM}\Windows CE Developer Tools\Windows CE Toolkit for Visual C++ 6.0\Tools; ValueType: string; ValueName: MenuName#2; ValueData: Remote &Heap Walker; Components: VisualCpp\CeTools
Root: HKLM; Subkey: SOFTWARE\{#VISUAL_FIRM}\Windows CE Developer Tools\Windows CE Toolkit for Visual C++ 6.0\Tools; ValueType: string; ValueName: MenuName#3; ValueData: Remote &Process Viewer; Components: VisualCpp\CeTools
Root: HKLM; Subkey: SOFTWARE\{#VISUAL_FIRM}\Windows CE Developer Tools\Windows CE Toolkit for Visual C++ 6.0\Tools; ValueType: string; ValueName: MenuName#4; ValueData: Remote &Zoomin; Components: VisualCpp\CeTools
Root: HKLM; Subkey: SOFTWARE\{#VISUAL_FIRM}\Windows CE Developer Tools\Windows CE Toolkit for Visual C++ 6.0\Tools; ValueType: string; ValueName: MenuName#5; ValueData: Remote &File Viewer; Components: VisualCpp\CeTools

Root: HKLM; Subkey: SOFTWARE\{#VISUAL_FIRM}\Windows CE Developer Tools\Windows CE Toolkit for Visual C++ 6.0\Tools; ValueType: string; ValueName: PathName#0; ValueData: {app}\Windows CE Tools\Wce200\bin\CESPY.EXE; Components: VisualCpp\CeTools
Root: HKLM; Subkey: SOFTWARE\{#VISUAL_FIRM}\Windows CE Developer Tools\Windows CE Toolkit for Visual C++ 6.0\Tools; ValueType: string; ValueName: PathName#1; ValueData: {app}\Windows CE Tools\Wce200\bin\CEREGEDT.EXE; Components: VisualCpp\CeTools
Root: HKLM; Subkey: SOFTWARE\{#VISUAL_FIRM}\Windows CE Developer Tools\Windows CE Toolkit for Visual C++ 6.0\Tools; ValueType: string; ValueName: PathName#2; ValueData: {app}\Windows CE Tools\Wce200\bin\CEHEAPWK.EXE; Components: VisualCpp\CeTools
Root: HKLM; Subkey: SOFTWARE\{#VISUAL_FIRM}\Windows CE Developer Tools\Windows CE Toolkit for Visual C++ 6.0\Tools; ValueType: string; ValueName: PathName#3; ValueData: {app}\Windows CE Tools\Wce200\bin\CEPVIEW.EXE; Components: VisualCpp\CeTools
Root: HKLM; Subkey: SOFTWARE\{#VISUAL_FIRM}\Windows CE Developer Tools\Windows CE Toolkit for Visual C++ 6.0\Tools; ValueType: string; ValueName: PathName#4; ValueData: {app}\Windows CE Tools\Wce200\bin\CEZOOM.EXE; Components: VisualCpp\CeTools
Root: HKLM; Subkey: SOFTWARE\{#VISUAL_FIRM}\Windows CE Developer Tools\Windows CE Toolkit for Visual C++ 6.0\Tools; ValueType: string; ValueName: PathName#5; ValueData: {app}\Windows CE Tools\Wce200\bin\CEFILEVW.EXE; Components: VisualCpp\CeTools

Root: HKLM; Subkey: SOFTWARE\{#VISUAL_FIRM}\Windows CE Tools\Platform Manager; ValueType: dword; ValueName: KeepAlive; ValueData: $00000001; Components: VisualCpp\CeTools

Root: HKLM; Subkey: SOFTWARE\{#VISUAL_FIRM}\Windows CE Tools\Platform Manager\{{2A4F783A-014E-11D2-BBA0-00A0C9C9CCEE}; ValueType: string; ValueData: Packages; Components: VisualCpp\CeTools
Root: HKLM; Subkey: SOFTWARE\{#VISUAL_FIRM}\Windows CE Tools\Platform Manager\{{2A4F783A-014E-11D2-BBA0-00A0C9C9CCEE}\{{919E8310-4C05-11D2-BD39-0060089A6894}; ValueType: string; ValueData: cemon.exe; Components: VisualCpp\CeTools
Root: HKLM; Subkey: SOFTWARE\{#VISUAL_FIRM}\Windows CE Tools\Platform Manager\{{2A4F783A-014E-11D2-BBA0-00A0C9C9CCEE}\{{919E8310-4C05-11D2-BD39-0060089A6894}\CEMON.EXE; ValueType: binary; ValueName: {app}\Windows CE Tools\wce200\target\MIPS\CEMON.EXE; ValueData: 02 00 00 00 01 00 00 00 00 00 00 00 00 00 00 00 00 10 00 00 02 00 00 00 00 00 00 00 01 00 00 00; Components: VisualCpp\CeTools
Root: HKLM; Subkey: SOFTWARE\{#VISUAL_FIRM}\Windows CE Tools\Platform Manager\{{2A4F783A-014E-11D2-BBA0-00A0C9C9CCEE}\{{919E8310-4C05-11D2-BD39-0060089A6894}\CEMON.EXE; ValueType: binary; ValueName: {app}\Windows CE Tools\wce200\target\SH3\CEMON.EXE; ValueData: 02 00 00 00 04 00 00 00 13 27 00 00 00 00 00 00 00 10 00 00 02 00 00 00 00 00 00 00 01 00 00 00; Components: VisualCpp\CeTools
Root: HKLM; Subkey: SOFTWARE\{#VISUAL_FIRM}\Windows CE Tools\Platform Manager\{{2A4F783A-014E-11D2-BBA0-00A0C9C9CCEE}\{{919E8310-4C05-11D2-BD39-0060089A6894}\CEMON.EXE; ValueType: binary; ValueName: {app}\Windows CE Tools\wce201\target\MIPS\CEMON.EXE; ValueData: 02 00 00 00 01 00 00 00 00 00 00 00 00 00 00 00 00 10 00 00 02 00 01 00 00 00 00 00 01 00 00 00; Components: VisualCpp\CeTools
Root: HKLM; Subkey: SOFTWARE\{#VISUAL_FIRM}\Windows CE Tools\Platform Manager\{{2A4F783A-014E-11D2-BBA0-00A0C9C9CCEE}\{{919E8310-4C05-11D2-BD39-0060089A6894}\CEMON.EXE; ValueType: binary; ValueName: {app}\Windows CE Tools\wce201\target\SH3\CEMON.EXE; ValueData: 02 00 00 00 04 00 00 00 13 27 00 00 00 00 00 00 00 10 00 00 02 00 01 00 00 00 00 00 01 00 00 00; Components: VisualCpp\CeTools
Root: HKLM; Subkey: SOFTWARE\{#VISUAL_FIRM}\Windows CE Tools\Platform Manager\{{2A4F783A-014E-11D2-BBA0-00A0C9C9CCEE}\{{919E8310-4C05-11D2-BD39-0060089A6894}\CEMON.EXE; ValueType: binary; ValueName: {app}\Windows CE Tools\wce210\target\ARM\CEMON.EXE; ValueData: 02 00 00 00 05 00 00 00 00 00 00 00 00 00 00 00 00 10 00 00 02 00 0a 00 00 00 00 00 01 00 00 00; Components: VisualCpp\CeTools
Root: HKLM; Subkey: SOFTWARE\{#VISUAL_FIRM}\Windows CE Tools\Platform Manager\{{2A4F783A-014E-11D2-BBA0-00A0C9C9CCEE}\{{919E8310-4C05-11D2-BD39-0060089A6894}\CEMON.EXE; ValueType: binary; ValueName: {app}\Windows CE Tools\wce210\target\MIPS\CEMON.EXE; ValueData: 02 00 00 00 01 00 00 00 00 00 00 00 00 00 00 00 00 10 00 00 02 00 0a 00 00 00 00 00 01 00 00 00; Components: VisualCpp\CeTools
Root: HKLM; Subkey: SOFTWARE\{#VISUAL_FIRM}\Windows CE Tools\Platform Manager\{{2A4F783A-014E-11D2-BBA0-00A0C9C9CCEE}\{{919E8310-4C05-11D2-BD39-0060089A6894}\CEMON.EXE; ValueType: binary; ValueName: {app}\Windows CE Tools\wce210\target\MIPSFP\CEMON.EXE; ValueData: 02 00 00 00 01 00 00 00 cc 10 00 00 00 00 00 00 00 10 00 00 02 00 0a 00 00 00 00 00 01 00 00 00; Components: VisualCpp\CeTools
Root: HKLM; Subkey: SOFTWARE\{#VISUAL_FIRM}\Windows CE Tools\Platform Manager\{{2A4F783A-014E-11D2-BBA0-00A0C9C9CCEE}\{{919E8310-4C05-11D2-BD39-0060089A6894}\CEMON.EXE; ValueType: binary; ValueName: {app}\Windows CE Tools\wce210\target\PPC\CEMON.EXE; ValueData: 02 00 00 00 03 00 00 00 00 00 00 00 00 00 00 00 00 10 00 00 02 00 0a 00 00 00 00 00 01 00 00 00; Components: VisualCpp\CeTools
Root: HKLM; Subkey: SOFTWARE\{#VISUAL_FIRM}\Windows CE Tools\Platform Manager\{{2A4F783A-014E-11D2-BBA0-00A0C9C9CCEE}\{{919E8310-4C05-11D2-BD39-0060089A6894}\CEMON.EXE; ValueType: binary; ValueName: {app}\Windows CE Tools\wce210\target\SH3\CEMON.EXE; ValueData: 02 00 00 00 04 00 00 00 13 27 00 00 00 00 00 00 00 10 00 00 02 00 0a 00 00 00 00 00 01 00 00 00; Components: VisualCpp\CeTools
Root: HKLM; Subkey: SOFTWARE\{#VISUAL_FIRM}\Windows CE Tools\Platform Manager\{{2A4F783A-014E-11D2-BBA0-00A0C9C9CCEE}\{{919E8310-4C05-11D2-BD39-0060089A6894}\CEMON.EXE; ValueType: binary; ValueName: {app}\Windows CE Tools\wce210\target\SH4\CEMON.EXE; ValueData: 02 00 00 00 04 00 00 00 15 27 00 00 00 00 00 00 00 10 00 00 02 00 0a 00 00 00 00 00 01 00 00 00; Components: VisualCpp\CeTools
Root: HKLM; Subkey: SOFTWARE\{#VISUAL_FIRM}\Windows CE Tools\Platform Manager\{{2A4F783A-014E-11D2-BBA0-00A0C9C9CCEE}\{{919E8310-4C05-11D2-BD39-0060089A6894}\CEMON.EXE; ValueType: binary; ValueName: {app}\Windows CE Tools\wce210\target\X86\CEMON.EXE; ValueData: 02 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 10 00 00 02 00 0a 00 00 00 00 00 01 00 00 00; Components: VisualCpp\CeTools
Root: HKLM; Subkey: SOFTWARE\{#VISUAL_FIRM}\Windows CE Tools\Platform Manager\{{2A4F783A-014E-11D2-BBA0-00A0C9C9CCEE}\{{919E8310-4C05-11D2-BD39-0060089A6894}\CEMON.EXE; ValueType: binary; ValueName: {app}\Windows CE Tools\wce211\target\ARM\CEMON.EXE; ValueData: 02 00 00 00 05 00 00 00 00 00 00 00 00 00 00 00 00 10 00 00 02 00 0b 00 00 00 00 00 01 00 00 00; Components: VisualCpp\CeTools
Root: HKLM; Subkey: SOFTWARE\{#VISUAL_FIRM}\Windows CE Tools\Platform Manager\{{2A4F783A-014E-11D2-BBA0-00A0C9C9CCEE}\{{919E8310-4C05-11D2-BD39-0060089A6894}\CEMON.EXE; ValueType: binary; ValueName: {app}\Windows CE Tools\wce211\target\MIPS\CEMON.EXE; ValueData: 02 00 00 00 01 00 00 00 00 00 00 00 00 00 00 00 00 10 00 00 02 00 0b 00 00 00 00 00 01 00 00 00; Components: VisualCpp\CeTools
Root: HKLM; Subkey: SOFTWARE\{#VISUAL_FIRM}\Windows CE Tools\Platform Manager\{{2A4F783A-014E-11D2-BBA0-00A0C9C9CCEE}\{{919E8310-4C05-11D2-BD39-0060089A6894}\CEMON.EXE; ValueType: binary; ValueName: {app}\Windows CE Tools\wce211\target\MIPSFP\CEMON.EXE; ValueData: 02 00 00 00 01 00 00 00 cc 10 00 00 00 00 00 00 00 10 00 00 02 00 0b 00 00 00 00 00 01 00 00 00; Components: VisualCpp\CeTools
Root: HKLM; Subkey: SOFTWARE\{#VISUAL_FIRM}\Windows CE Tools\Platform Manager\{{2A4F783A-014E-11D2-BBA0-00A0C9C9CCEE}\{{919E8310-4C05-11D2-BD39-0060089A6894}\CEMON.EXE; ValueType: binary; ValueName: {app}\Windows CE Tools\wce211\target\PPC\CEMON.EXE; ValueData: 02 00 00 00 03 00 00 00 00 00 00 00 00 00 00 00 00 10 00 00 02 00 0b 00 00 00 00 00 01 00 00 00; Components: VisualCpp\CeTools
Root: HKLM; Subkey: SOFTWARE\{#VISUAL_FIRM}\Windows CE Tools\Platform Manager\{{2A4F783A-014E-11D2-BBA0-00A0C9C9CCEE}\{{919E8310-4C05-11D2-BD39-0060089A6894}\CEMON.EXE; ValueType: binary; ValueName: {app}\Windows CE Tools\wce211\target\SH3\CEMON.EXE; ValueData: 02 00 00 00 04 00 00 00 13 27 00 00 00 00 00 00 00 10 00 00 02 00 0b 00 00 00 00 00 01 00 00 00; Components: VisualCpp\CeTools
Root: HKLM; Subkey: SOFTWARE\{#VISUAL_FIRM}\Windows CE Tools\Platform Manager\{{2A4F783A-014E-11D2-BBA0-00A0C9C9CCEE}\{{919E8310-4C05-11D2-BD39-0060089A6894}\CEMON.EXE; ValueType: binary; ValueName: {app}\Windows CE Tools\wce211\target\SH4\CEMON.EXE; ValueData: 02 00 00 00 04 00 00 00 15 27 00 00 00 00 00 00 00 10 00 00 02 00 0b 00 00 00 00 00 01 00 00 00; Components: VisualCpp\CeTools
Root: HKLM; Subkey: SOFTWARE\{#VISUAL_FIRM}\Windows CE Tools\Platform Manager\{{2A4F783A-014E-11D2-BBA0-00A0C9C9CCEE}\{{919E8310-4C05-11D2-BD39-0060089A6894}\CEMON.EXE; ValueType: binary; ValueName: {app}\Windows CE Tools\wce211\target\X86\CEMON.EXE; ValueData: 02 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 10 00 00 02 00 0b 00 00 00 00 00 01 00 00 00; Components: VisualCpp\CeTools

Root: HKLM; Subkey: SOFTWARE\{#VISUAL_FIRM}\Windows CE Tools\Platform Manager\{{46DD9FD8-427F-11D2-BBB4-00A0C9C9CCEE}; ValueType: string; ValueData: Toolkits; Components: VisualCpp\CeTools
Root: HKLM; Subkey: SOFTWARE\{#VISUAL_FIRM}\Windows CE Tools\Platform Manager\{{46DD9FD8-427F-11D2-BBB4-00A0C9C9CCEE}; ValueType: string; ValueName: {{733F9BF0-4421-11D2-BD33-0060089A6894}; ValueData: Windows CE Toolkit for Visual C++ 6.0; Components: VisualCpp\CeTools
Root: HKLM; Subkey: SOFTWARE\{#VISUAL_FIRM}\Windows CE Tools\Platform Manager\{{F384D888-F9AA-11D1-BB9E-00A0C9C9CCEE}; ValueType: string; ValueData: Platforms; Components: VisualCpp\CeTools
Root: HKLM; Subkey: SOFTWARE\{#VISUAL_FIRM}\Windows CE Tools\Platform Manager\{{F384D894-F9AA-11D1-BB9E-00A0C9C9CCEE}; ValueType: string; ValueData: Properties; Components: VisualCpp\CeTools

Root: HKLM; Subkey: SOFTWARE\{#VISUAL_FIRM}\Windows NT\CurrentVersion\AeDebug; ValueType: dword; ValueName: UserDebuggerHotKey; ValueData: $00000000
Root: HKLM; Subkey: SOFTWARE\{#VISUAL_FIRM}\Windows NT\CurrentVersion\AeDebug; ValueType: string; ValueName: Auto; ValueData: 0
Root: HKLM; Subkey: SOFTWARE\{#VISUAL_FIRM}\Windows NT\CurrentVersion\AeDebug; ValueType: string; ValueName: Debugger; ValueData: """{app}\Common\MSDev98\Bin\msdev.exe"" -p %ld -e %ld"

Root: HKLM; Subkey: SOFTWARE\{#VISUAL_FIRM}\Windows NT\CurrentVersion\DebugObjectRPCEnabled

Root: HKLM; Subkey: SOFTWARE\{#VISUAL_FIRM}\Windows\CurrentVersion\App Paths\msdev.exe; ValueType: string; ValueData: {app}\Common\MSDev98\Bin\msdev.exe

;Root: HKLM; Subkey: SOFTWARE\{#VISUAL_FIRM}\Windows\CurrentVersion\Explorer\BitBucket\c

Root: HKLM; Subkey: SOFTWARE\{#VISUAL_FIRM}\Windows\Help; ValueType: string; ValueName: cawutil.hlp; ValueData: {app}\Common\MSDev98\Bin\IDE
Root: HKLM; Subkey: SOFTWARE\{#VISUAL_FIRM}\Windows\Help; ValueType: string; ValueName: clipasst.hlp; ValueData: {app}\Common\MSDev98\Bin\IDE
Root: HKLM; Subkey: SOFTWARE\{#VISUAL_FIRM}\Windows\Help; ValueType: string; ValueName: comctl1.cnt; ValueData: {win}\Help
Root: HKLM; Subkey: SOFTWARE\{#VISUAL_FIRM}\Windows\Help; ValueType: string; ValueName: comctl1.hlp; ValueData: {win}\Help
Root: HKLM; Subkey: SOFTWARE\{#VISUAL_FIRM}\Windows\Help; ValueType: string; ValueName: comctl2.cnt; ValueData: {win}\Help
Root: HKLM; Subkey: SOFTWARE\{#VISUAL_FIRM}\Windows\Help; ValueType: string; ValueName: comctl2.hlp; ValueData: {win}\Help
Root: HKLM; Subkey: SOFTWARE\{#VISUAL_FIRM}\Windows\Help; ValueType: string; ValueName: ctip.hlp; ValueData: {app}\Common\MSDev98\Bin\IDE
Root: HKLM; Subkey: SOFTWARE\{#VISUAL_FIRM}\Windows\Help; ValueType: string; ValueName: dao35.cnt; ValueData: {win}\Help
Root: HKLM; Subkey: SOFTWARE\{#VISUAL_FIRM}\Windows\Help; ValueType: string; ValueName: dao35.hlp; ValueData: {win}\Help
Root: HKLM; Subkey: SOFTWARE\{#VISUAL_FIRM}\Windows\Help; ValueType: string; ValueName: dbgrid96.cnt; ValueData: {win}\Help
Root: HKLM; Subkey: SOFTWARE\{#VISUAL_FIRM}\Windows\Help; ValueType: string; ValueName: dbgrid96.hlp; ValueData: {win}\Help
Root: HKLM; Subkey: SOFTWARE\{#VISUAL_FIRM}\Windows\Help; ValueType: string; ValueName: depends.hlp; ValueData: {app}\Common\Tools
Root: HKLM; Subkey: SOFTWARE\{#VISUAL_FIRM}\Windows\Help; ValueType: string; ValueName: dlgbar.hlp; ValueData: {app}\Common\MSDev98\Bin\IDE
Root: HKLM; Subkey: SOFTWARE\{#VISUAL_FIRM}\Windows\Help; ValueType: string; ValueName: docreg.hlp; ValueData: {app}\Common\MSDev98\Bin\IDE
Root: HKLM; Subkey: SOFTWARE\{#VISUAL_FIRM}\Windows\Help; ValueType: string; ValueName: errlook.hlp; ValueData: {app}\Common\Tools
Root: HKLM; Subkey: SOFTWARE\{#VISUAL_FIRM}\Windows\Help; ValueType: string; ValueName: exthelp.cnt; ValueData: {app}\Common\MSDev98\Help
Root: HKLM; Subkey: SOFTWARE\{#VISUAL_FIRM}\Windows\Help; ValueType: string; ValueName: exthelp.hlp; ValueData: {app}\Common\MSDev98\Help
Root: HKLM; Subkey: SOFTWARE\{#VISUAL_FIRM}\Windows\Help; ValueType: string; ValueName: guidgen.hlp; ValueData: {app}\Common\MSDev98\Bin\IDE
Root: HKLM; Subkey: SOFTWARE\{#VISUAL_FIRM}\Windows\Help; ValueType: string; ValueName: hcw.cnt; ValueData: {app}\Common\Tools
Root: HKLM; Subkey: SOFTWARE\{#VISUAL_FIRM}\Windows\Help; ValueType: string; ValueName: hcw.hlp; ValueData: {app}\Common\Tools
Root: HKLM; Subkey: SOFTWARE\{#VISUAL_FIRM}\Windows\Help; ValueType: string; ValueName: idle.hlp; ValueData: {app}\Common\MSDev98\Bin\IDE
Root: HKLM; Subkey: SOFTWARE\{#VISUAL_FIRM}\Windows\Help; ValueType: string; ValueName: mapicomp.hlp; ValueData: {app}\Common\MSDev98\Bin\IDE
Root: HKLM; Subkey: SOFTWARE\{#VISUAL_FIRM}\Windows\Help; ValueType: string; ValueName: mc.hlp; ValueData: {app}\VC98\Bin
Root: HKLM; Subkey: SOFTWARE\{#VISUAL_FIRM}\Windows\Help; ValueType: string; ValueName: media.hlp; ValueData: {app}\Common\MSDev98\Bin\IDE
Root: HKLM; Subkey: SOFTWARE\{#VISUAL_FIRM}\Windows\Help; ValueType: string; ValueName: msdev.hlp; ValueData: {app}\Common\MSDev98\Help
Root: HKLM; Subkey: SOFTWARE\{#VISUAL_FIRM}\Windows\Help; ValueType: string; ValueName: occ.hlp; ValueData: {app}\Common\MSDev98\Bin\IDE
Root: HKLM; Subkey: SOFTWARE\{#VISUAL_FIRM}\Windows\Help; ValueType: string; ValueName: oletools.hlp; ValueData: {app}\Common\Tools
Root: HKLM; Subkey: SOFTWARE\{#VISUAL_FIRM}\Windows\Help; ValueType: string; ValueName: owndraw.hlp; ValueData: {app}\Common\MSDev98\Bin\IDE
Root: HKLM; Subkey: SOFTWARE\{#VISUAL_FIRM}\Windows\Help; ValueType: string; ValueName: palette.hlp; ValueData: {app}\Common\MSDev98\Bin\IDE
Root: HKLM; Subkey: SOFTWARE\{#VISUAL_FIRM}\Windows\Help; ValueType: string; ValueName: popup.hlp; ValueData: {app}\Common\MSDev98\Bin\IDE
Root: HKLM; Subkey: SOFTWARE\{#VISUAL_FIRM}\Windows\Help; ValueType: string; ValueName: progdlg.hlp; ValueData: {app}\Common\MSDev98\Bin\IDE
Root: HKLM; Subkey: SOFTWARE\{#VISUAL_FIRM}\Windows\Help; ValueType: string; ValueName: propsht.hlp; ValueData: {app}\Common\MSDev98\Bin\IDE
Root: HKLM; Subkey: SOFTWARE\{#VISUAL_FIRM}\Windows\Help; ValueType: string; ValueName: rc.hlp; ValueData: {app}\Common\MSDev98\Bin
Root: HKLM; Subkey: SOFTWARE\{#VISUAL_FIRM}\Windows\Help; ValueType: string; ValueName: sample.dsm; ValueData: {app}\Common\MSDev98\Macros
Root: HKLM; Subkey: SOFTWARE\{#VISUAL_FIRM}\Windows\Help; ValueType: string; ValueName: shed.hlp; ValueData: {app}\Common\Tools
Root: HKLM; Subkey: SOFTWARE\{#VISUAL_FIRM}\Windows\Help; ValueType: string; ValueName: sockets.hlp; ValueData: {app}\Common\MSDev98\Bin\IDE
Root: HKLM; Subkey: SOFTWARE\{#VISUAL_FIRM}\Windows\Help; ValueType: string; ValueName: splash.hlp; ValueData: {app}\Common\MSDev98\Bin\IDE
Root: HKLM; Subkey: SOFTWARE\{#VISUAL_FIRM}\Windows\Help; ValueType: string; ValueName: splitter.hlp; ValueData: {app}\Common\MSDev98\Bin\IDE
Root: HKLM; Subkey: SOFTWARE\{#VISUAL_FIRM}\Windows\Help; ValueType: string; ValueName: spyxx.cnt; ValueData: {app}\Common\Tools
Root: HKLM; Subkey: SOFTWARE\{#VISUAL_FIRM}\Windows\Help; ValueType: string; ValueName: spyxx.hlp; ValueData: {app}\Common\Tools
Root: HKLM; Subkey: SOFTWARE\{#VISUAL_FIRM}\Windows\Help; ValueType: string; ValueName: statbar.hlp; ValueData: {app}\Common\MSDev98\Bin\IDE
Root: HKLM; Subkey: SOFTWARE\{#VISUAL_FIRM}\Windows\Help; ValueType: string; ValueName: sysinfo.hlp; ValueData: {app}\Common\MSDev98\Bin\IDE
Root: HKLM; Subkey: SOFTWARE\{#VISUAL_FIRM}\Windows\Help; ValueType: string; ValueName: tooltips.hlp; ValueData: {app}\Common\MSDev98\Bin\IDE
Root: HKLM; Subkey: SOFTWARE\{#VISUAL_FIRM}\Windows\Help; ValueType: string; ValueName: tstcon32.cnt; ValueData: {app}\Common\Tools
Root: HKLM; Subkey: SOFTWARE\{#VISUAL_FIRM}\Windows\Help; ValueType: string; ValueName: tstcon32.hlp; ValueData: {app}\Common\Tools
Root: HKLM; Subkey: SOFTWARE\{#VISUAL_FIRM}\Windows\Help; ValueType: string; ValueName: vb5def.hlp; ValueData: {win}\Help
Root: HKLM; Subkey: SOFTWARE\{#VISUAL_FIRM}\Windows\Help; ValueType: string; ValueName: vbcmn96.cnt; ValueData: {win}\Help
Root: HKLM; Subkey: SOFTWARE\{#VISUAL_FIRM}\Windows\Help; ValueType: string; ValueName: vbcmn96.hlp; ValueData: {win}\Help
Root: HKLM; Subkey: SOFTWARE\{#VISUAL_FIRM}\Windows\Help; ValueType: string; ValueName: windiff.hlp; ValueData: {app}\Common\Tools

Root: HKLM; Subkey: SOFTWARE\Classes\.bsc; ValueType: string; ValueData: bscfile
Root: HKLM; Subkey: SOFTWARE\Classes\bscfile; ValueType: string; ValueData: BSC File
Root: HKLM; Subkey: SOFTWARE\Classes\bscfile; ValueType: string; ValueName: AlwaysShowExt
Root: HKLM; Subkey: SOFTWARE\Classes\bscfile\DefaultIcon; ValueType: string; ValueData: {app}\Common\MSDev98\Bin\msdev.exe,-20212
Root: HKLM; Subkey: SOFTWARE\Classes\bscfile\shell\&Open with MSDev; ValueType: string; ValueData: &Open with MSDEV
Root: HKLM; Subkey: SOFTWARE\Classes\bscfile\shell\&Open with MSDev\command; ValueType: string; ValueData: """{app}\Common\MSDev98\Bin\msdev.exe"" ""%1"""
Root: HKLM; Subkey: SOFTWARE\Classes\bscfile\shell\&Open with MSDev\ddeexec; ValueType: string; ValueData: "Open(""%1"")"
Root: HKLM; Subkey: SOFTWARE\Classes\bscfile\shell\&Open with MSDev\ddeexec\application; ValueType: string; ValueData: msdev
Root: HKLM; Subkey: SOFTWARE\Classes\bscfile\shell\&Open with MSDev\ddeexec\topic; ValueType: string; ValueData: system

Root: HKLM; Subkey: SOFTWARE\Classes\.c; ValueType: string; ValueData: cfile
Root: HKLM; Subkey: SOFTWARE\Classes\.c; ValueType: string; ValueName: PerceivedType; ValueData: text
Root: HKLM; Subkey: SOFTWARE\Classes\cfile; ValueType: string; ValueData: C Source file
Root: HKLM; Subkey: SOFTWARE\Classes\cfile; ValueType: string; ValueName: AlwaysShowExt
Root: HKLM; Subkey: SOFTWARE\Classes\cfile\DefaultIcon; ValueType: string; ValueData: {app}\Common\MSDev98\Bin\msdev.exe,-20210
Root: HKLM; Subkey: SOFTWARE\Classes\cfile\shell\&Open with MSDev; ValueType: string; ValueData: &Open with MSDEV
Root: HKLM; Subkey: SOFTWARE\Classes\cfile\shell\&Open with MSDev\command; ValueType: string; ValueData: """{app}\Common\MSDev98\Bin\msdev.exe"" ""%1"""
Root: HKLM; Subkey: SOFTWARE\Classes\cfile\shell\&Open with MSDev\ddeexec; ValueType: string; ValueData: "Open(""%1"")"
Root: HKLM; Subkey: SOFTWARE\Classes\cfile\shell\&Open with MSDev\ddeexec\application; ValueType: string; ValueData: msdev
Root: HKLM; Subkey: SOFTWARE\Classes\cfile\shell\&Open with MSDev\ddeexec\topic; ValueType: string; ValueData: system

Root: HKLM; Subkey: SOFTWARE\Classes\.cpp; ValueType: string; ValueData: cppfile
Root: HKLM; Subkey: SOFTWARE\Classes\.cpp; ValueType: string; ValueName: PerceivedType; ValueData: text
Root: HKLM; Subkey: SOFTWARE\Classes\cppfile; ValueType: string; ValueData: C++ Source file
Root: HKLM; Subkey: SOFTWARE\Classes\cppfile; ValueType: string; ValueName: AlwaysShowExt
Root: HKLM; Subkey: SOFTWARE\Classes\cppfile\DefaultIcon; ValueType: string; ValueData: {app}\Common\MSDev98\Bin\msdev.exe,-20209
Root: HKLM; Subkey: SOFTWARE\Classes\cppfile\shell\&Open with MSDev; ValueType: string; ValueData: &Open with MSDEV
Root: HKLM; Subkey: SOFTWARE\Classes\cppfile\shell\&Open with MSDev\command; ValueType: string; ValueData: """{app}\Common\MSDev98\Bin\msdev.exe"" ""%1"""
Root: HKLM; Subkey: SOFTWARE\Classes\cppfile\shell\&Open with MSDev\ddeexec; ValueType: string; ValueData: "Open(""%1"")"
Root: HKLM; Subkey: SOFTWARE\Classes\cppfile\shell\&Open with MSDev\ddeexec\application; ValueType: string; ValueData: msdev
Root: HKLM; Subkey: SOFTWARE\Classes\cppfile\shell\&Open with MSDev\ddeexec\topic; ValueType: string; ValueData: system

Root: HKLM; Subkey: SOFTWARE\Classes\.cxx; ValueType: string; ValueData: cxxfile
Root: HKLM; Subkey: SOFTWARE\Classes\.cxx; ValueType: string; ValueName: PerceivedType; ValueData: text
Root: HKLM; Subkey: SOFTWARE\Classes\cxxfile; ValueType: string; ValueData: CXX File
Root: HKLM; Subkey: SOFTWARE\Classes\cxxfile; ValueType: string; ValueName: AlwaysShowExt
Root: HKLM; Subkey: SOFTWARE\Classes\cxxfile\DefaultIcon; ValueType: string; ValueData: {app}\Common\MSDev98\Bin\msdev.exe,-20210
Root: HKLM; Subkey: SOFTWARE\Classes\cxxfile\shell\&Open with MSDev; ValueType: string; ValueData: &Open with MSDEV
Root: HKLM; Subkey: SOFTWARE\Classes\cxxfile\shell\&Open with MSDev\command; ValueType: string; ValueData: """{app}\Common\MSDev98\Bin\msdev.exe"" ""%1"""
Root: HKLM; Subkey: SOFTWARE\Classes\cxxfile\shell\&Open with MSDev\ddeexec; ValueType: string; ValueData: "Open(""%1"")"
Root: HKLM; Subkey: SOFTWARE\Classes\cxxfile\shell\&Open with MSDev\ddeexec\application; ValueType: string; ValueData: msdev
Root: HKLM; Subkey: SOFTWARE\Classes\cxxfile\shell\&Open with MSDev\ddeexec\topic; ValueType: string; ValueData: system

Root: HKLM; Subkey: SOFTWARE\Classes\.dsm; ValueType: string; ValueData: dsmfile
Root: HKLM; Subkey: SOFTWARE\Classes\dsmfile; ValueType: string; ValueData: DSM File
Root: HKLM; Subkey: SOFTWARE\Classes\dsmfile; ValueType: string; ValueName: AlwaysShowExt
Root: HKLM; Subkey: SOFTWARE\Classes\dsmfile\DefaultIcon; ValueType: string; ValueData: {app}\Common\MSDev98\Bin\msdev.exe,-20212
Root: HKLM; Subkey: SOFTWARE\Classes\dsmfile\shell\&Open with MSDev; ValueType: string; ValueData: &Open with MSDEV
Root: HKLM; Subkey: SOFTWARE\Classes\dsmfile\shell\&Open with MSDev\command; ValueType: string; ValueData: """{app}\Common\MSDev98\Bin\msdev.exe"" ""%1"""
Root: HKLM; Subkey: SOFTWARE\Classes\dsmfile\shell\&Open with MSDev\ddeexec; ValueType: string; ValueData: "Open(""%1"")"
Root: HKLM; Subkey: SOFTWARE\Classes\dsmfile\shell\&Open with MSDev\ddeexec\application; ValueType: string; ValueData: msdev
Root: HKLM; Subkey: SOFTWARE\Classes\dsmfile\shell\&Open with MSDev\ddeexec\topic; ValueType: string; ValueData: system

Root: HKLM; Subkey: SOFTWARE\Classes\.dsp; ValueType: string; ValueData: dspfile
Root: HKLM; Subkey: SOFTWARE\Classes\dspfile; ValueType: string; ValueData: Project File
Root: HKLM; Subkey: SOFTWARE\Classes\dspfile; ValueType: string; ValueName: AlwaysShowExt
Root: HKLM; Subkey: SOFTWARE\Classes\dspfile\DefaultIcon; ValueType: string; ValueData: {app}\Common\MSDev98\Bin\msdev.exe,-20214
Root: HKLM; Subkey: SOFTWARE\Classes\dspfile\shell\&Open with MSDev; ValueType: string; ValueData: &Open with MSDEV
Root: HKLM; Subkey: SOFTWARE\Classes\dspfile\shell\&Open with MSDev\command; ValueType: string; ValueData: """{app}\Common\MSDev98\Bin\msdev.exe"" ""%1"""
Root: HKLM; Subkey: SOFTWARE\Classes\dspfile\shell\&Open with MSDev\ddeexec; ValueType: string; ValueData: "Open(""%1"")"
Root: HKLM; Subkey: SOFTWARE\Classes\dspfile\shell\&Open with MSDev\ddeexec\application; ValueType: string; ValueData: msdev
Root: HKLM; Subkey: SOFTWARE\Classes\dspfile\shell\&Open with MSDev\ddeexec\topic; ValueType: string; ValueData: system

Root: HKLM; Subkey: SOFTWARE\Classes\.dsw; ValueType: string; ValueData: dswfile
Root: HKLM; Subkey: SOFTWARE\Classes\dswfile; ValueType: string; ValueData: Project Workspace
Root: HKLM; Subkey: SOFTWARE\Classes\dswfile; ValueType: string; ValueName: AlwaysShowExt
Root: HKLM; Subkey: SOFTWARE\Classes\dswfile\DefaultIcon; ValueType: string; ValueData: {app}\Common\MSDev98\Bin\msdev.exe,-20214
Root: HKLM; Subkey: SOFTWARE\Classes\dswfile\shell\&Open with MSDev; ValueType: string; ValueData: &Open with MSDEV
Root: HKLM; Subkey: SOFTWARE\Classes\dswfile\shell\&Open with MSDev\command; ValueType: string; ValueData: """{app}\Common\MSDev98\Bin\msdev.exe"" ""%1"""
Root: HKLM; Subkey: SOFTWARE\Classes\dswfile\shell\&Open with MSDev\ddeexec; ValueType: string; ValueData: "Open(""%1"")"
Root: HKLM; Subkey: SOFTWARE\Classes\dswfile\shell\&Open with MSDev\ddeexec\application; ValueType: string; ValueData: msdev
Root: HKLM; Subkey: SOFTWARE\Classes\dswfile\shell\&Open with MSDev\ddeexec\topic; ValueType: string; ValueData: system

Root: HKLM; Subkey: SOFTWARE\Classes\.h; ValueType: string; ValueData: hfile
Root: HKLM; Subkey: SOFTWARE\Classes\.h; ValueType: string; ValueName: PerceivedType; ValueData: text
Root: HKLM; Subkey: SOFTWARE\Classes\hfile; ValueType: string; ValueData: C Header file
Root: HKLM; Subkey: SOFTWARE\Classes\hfile; ValueType: string; ValueName: AlwaysShowExt
Root: HKLM; Subkey: SOFTWARE\Classes\hfile\DefaultIcon; ValueType: string; ValueData: {app}\Common\MSDev98\Bin\msdev.exe,-20211
Root: HKLM; Subkey: SOFTWARE\Classes\hfile\shell\&Open with MSDev; ValueType: string; ValueData: &Open with MSDEV
Root: HKLM; Subkey: SOFTWARE\Classes\hfile\shell\&Open with MSDev\command; ValueType: string; ValueData: """{app}\Common\MSDev98\Bin\msdev.exe"" ""%1"""
Root: HKLM; Subkey: SOFTWARE\Classes\hfile\shell\&Open with MSDev\ddeexec; ValueType: string; ValueData: "Open(""%1"")"
Root: HKLM; Subkey: SOFTWARE\Classes\hfile\shell\&Open with MSDev\ddeexec\application; ValueType: string; ValueData: msdev
Root: HKLM; Subkey: SOFTWARE\Classes\hfile\shell\&Open with MSDev\ddeexec\topic; ValueType: string; ValueData: system

Root: HKLM; Subkey: SOFTWARE\Classes\.hpp; ValueType: string; ValueData: hppfile
Root: HKLM; Subkey: SOFTWARE\Classes\.hpp; ValueType: string; ValueName: PerceivedType; ValueData: text
Root: HKLM; Subkey: SOFTWARE\Classes\hppfile; ValueType: string; ValueData: HPP file
Root: HKLM; Subkey: SOFTWARE\Classes\hppfile; ValueType: string; ValueName: AlwaysShowExt
Root: HKLM; Subkey: SOFTWARE\Classes\hppfile\DefaultIcon; ValueType: string; ValueData: {app}\Common\MSDev98\Bin\msdev.exe,-20208
Root: HKLM; Subkey: SOFTWARE\Classes\hppfile\shell\&Open with MSDev; ValueType: string; ValueData: &Open with MSDEV
Root: HKLM; Subkey: SOFTWARE\Classes\hppfile\shell\&Open with MSDev\command; ValueType: string; ValueData: """{app}\Common\MSDev98\Bin\msdev.exe"" ""%1"""
Root: HKLM; Subkey: SOFTWARE\Classes\hppfile\shell\&Open with MSDev\ddeexec; ValueType: string; ValueData: "Open(""%1"")"
Root: HKLM; Subkey: SOFTWARE\Classes\hppfile\shell\&Open with MSDev\ddeexec\application; ValueType: string; ValueData: msdev
Root: HKLM; Subkey: SOFTWARE\Classes\hppfile\shell\&Open with MSDev\ddeexec\topic; ValueType: string; ValueData: system

Root: HKLM; Subkey: SOFTWARE\Classes\.hxx; ValueType: string; ValueData: hxxfile
Root: HKLM; Subkey: SOFTWARE\Classes\.hxx; ValueType: string; ValueName: PerceivedType; ValueData: text
Root: HKLM; Subkey: SOFTWARE\Classes\hxxfile; ValueType: string; ValueData: HXX file
Root: HKLM; Subkey: SOFTWARE\Classes\hxxfile; ValueType: string; ValueName: AlwaysShowExt
Root: HKLM; Subkey: SOFTWARE\Classes\hxxfile\DefaultIcon; ValueType: string; ValueData: {app}\Common\MSDev98\Bin\msdev.exe,-20211
Root: HKLM; Subkey: SOFTWARE\Classes\hxxfile\shell\&Open with MSDev; ValueType: string; ValueData: &Open with MSDEV
Root: HKLM; Subkey: SOFTWARE\Classes\hxxfile\shell\&Open with MSDev\command; ValueType: string; ValueData: """{app}\Common\MSDev98\Bin\msdev.exe"" ""%1"""
Root: HKLM; Subkey: SOFTWARE\Classes\hxxfile\shell\&Open with MSDev\ddeexec; ValueType: string; ValueData: "Open(""%1"")"
Root: HKLM; Subkey: SOFTWARE\Classes\hxxfile\shell\&Open with MSDev\ddeexec\application; ValueType: string; ValueData: msdev
Root: HKLM; Subkey: SOFTWARE\Classes\hxxfile\shell\&Open with MSDev\ddeexec\topic; ValueType: string; ValueData: system

Root: HKLM; Subkey: SOFTWARE\Classes\.ic2; ValueType: string; ValueData: icofile; Components: VisualCpp\CeTools

Root: HKLM; Subkey: SOFTWARE\Classes\.idb; ValueType: string; ValueData: idbfile
Root: HKLM; Subkey: SOFTWARE\Classes\idbfile; ValueType: string; ValueData: Intermediate file
Root: HKLM; Subkey: SOFTWARE\Classes\idbfile; ValueType: string; ValueName: AlwaysShowExt
Root: HKLM; Subkey: SOFTWARE\Classes\idbfile\DefaultIcon; ValueType: string; ValueData: {app}\Common\MSDev98\Bin\msdev.exe,-20215

Root: HKLM; Subkey: SOFTWARE\Classes\.idl; ValueType: string; ValueData: idlfile
Root: HKLM; Subkey: SOFTWARE\Classes\idlfile; ValueType: string; ValueData: IDL file
Root: HKLM; Subkey: SOFTWARE\Classes\idlfile; ValueType: string; ValueName: AlwaysShowExt
Root: HKLM; Subkey: SOFTWARE\Classes\idlfile\DefaultIcon; ValueType: string; ValueData: {app}\Common\MSDev98\Bin\msdev.exe,-20213
Root: HKLM; Subkey: SOFTWARE\Classes\idlfile\shell\&Open with MSDev; ValueType: string; ValueData: &Open with MSDEV
Root: HKLM; Subkey: SOFTWARE\Classes\idlfile\shell\&Open with MSDev\command; ValueType: string; ValueData: """{app}\Common\MSDev98\Bin\msdev.exe"" ""%1"""
Root: HKLM; Subkey: SOFTWARE\Classes\idlfile\shell\&Open with MSDev\ddeexec; ValueType: string; ValueData: "Open(""%1"")"
Root: HKLM; Subkey: SOFTWARE\Classes\idlfile\shell\&Open with MSDev\ddeexec\application; ValueType: string; ValueData: msdev
Root: HKLM; Subkey: SOFTWARE\Classes\idlfile\shell\&Open with MSDev\ddeexec\topic; ValueType: string; ValueData: system

Root: HKLM; Subkey: SOFTWARE\Classes\.ilk; ValueType: string; ValueData: ilkfile
Root: HKLM; Subkey: SOFTWARE\Classes\ilkfile; ValueType: string; ValueData: Intermediate file
Root: HKLM; Subkey: SOFTWARE\Classes\ilkfile; ValueType: string; ValueName: AlwaysShowExt
Root: HKLM; Subkey: SOFTWARE\Classes\ilkfile\DefaultIcon; ValueType: string; ValueData: {app}\Common\MSDev98\Bin\msdev.exe,-20215

Root: HKLM; Subkey: SOFTWARE\Classes\.mdp; ValueType: string; ValueData: mdpfile
Root: HKLM; Subkey: SOFTWARE\Classes\mdpfile; ValueType: string; ValueData: MDP file
Root: HKLM; Subkey: SOFTWARE\Classes\mdpfile; ValueType: string; ValueName: AlwaysShowExt
Root: HKLM; Subkey: SOFTWARE\Classes\mdpfile\DefaultIcon; ValueType: string; ValueData: {app}\Common\MSDev98\Bin\msdev.exe,-20213
Root: HKLM; Subkey: SOFTWARE\Classes\mdpfile\shell\&Open with MSDev; ValueType: string; ValueData: &Open with MSDEV
Root: HKLM; Subkey: SOFTWARE\Classes\mdpfile\shell\&Open with MSDev\command; ValueType: string; ValueData: """{app}\Common\MSDev98\Bin\msdev.exe"" ""%1"""
Root: HKLM; Subkey: SOFTWARE\Classes\mdpfile\shell\&Open with MSDev\ddeexec; ValueType: string; ValueData: "Open(""%1"")"
Root: HKLM; Subkey: SOFTWARE\Classes\mdpfile\shell\&Open with MSDev\ddeexec\application; ValueType: string; ValueData: msdev
Root: HKLM; Subkey: SOFTWARE\Classes\mdpfile\shell\&Open with MSDev\ddeexec\topic; ValueType: string; ValueData: system

Root: HKLM; Subkey: SOFTWARE\Classes\.obj; ValueType: string; ValueData: objfile
Root: HKLM; Subkey: SOFTWARE\Classes\objfile; ValueType: string; ValueData: Intermediate file
Root: HKLM; Subkey: SOFTWARE\Classes\objfile; ValueType: string; ValueName: AlwaysShowExt
Root: HKLM; Subkey: SOFTWARE\Classes\objfile\DefaultIcon; ValueType: string; ValueData: {app}\Common\MSDev98\Bin\msdev.exe,-20215

Root: HKLM; Subkey: SOFTWARE\Classes\.odl; ValueType: string; ValueData: odlfile
Root: HKLM; Subkey: SOFTWARE\Classes\odlfile; ValueType: string; ValueData: Object Definition Language file
Root: HKLM; Subkey: SOFTWARE\Classes\odlfile; ValueType: string; ValueName: AlwaysShowExt
Root: HKLM; Subkey: SOFTWARE\Classes\odlfile\DefaultIcon; ValueType: string; ValueData: {app}\Common\MSDev98\Bin\msdev.exe,-20213
Root: HKLM; Subkey: SOFTWARE\Classes\odlfile\shell\&Open with MSDev; ValueType: string; ValueData: &Open with MSDEV
Root: HKLM; Subkey: SOFTWARE\Classes\odlfile\shell\&Open with MSDev\command; ValueType: string; ValueData: """{app}\Common\MSDev98\Bin\msdev.exe,<"" ""%1"""
Root: HKLM; Subkey: SOFTWARE\Classes\odlfile\shell\&Open with MSDev\ddeexec; ValueType: string; ValueData: "Open(""%1"")"
Root: HKLM; Subkey: SOFTWARE\Classes\odlfile\shell\&Open with MSDev\ddeexec\application; ValueType: string; ValueData: msdev
Root: HKLM; Subkey: SOFTWARE\Classes\odlfile\shell\&Open with MSDev\ddeexec\topic; ValueType: string; ValueData: system

Root: HKLM; Subkey: SOFTWARE\Classes\.pch; ValueType: string; ValueData: pchfile
Root: HKLM; Subkey: SOFTWARE\Classes\pchfile; ValueType: string; ValueData: Intermediate file
Root: HKLM; Subkey: SOFTWARE\Classes\pchfile; ValueType: string; ValueName: AlwaysShowExt
Root: HKLM; Subkey: SOFTWARE\Classes\pchfile\DefaultIcon; ValueType: string; ValueData: {app}\Common\MSDev98\Bin\msdev.exe,-20215

Root: HKLM; Subkey: SOFTWARE\Classes\.pdb; ValueType: string; ValueData: pdbfile
Root: HKLM; Subkey: SOFTWARE\Classes\pdbfile; ValueType: string; ValueData: Intermediate file
Root: HKLM; Subkey: SOFTWARE\Classes\pdbfile; ValueType: string; ValueName: AlwaysShowExt
Root: HKLM; Subkey: SOFTWARE\Classes\pdbfile\DefaultIcon; ValueType: string; ValueData: {app}\Common\MSDev98\Bin\msdev.exe,-20215

Root: HKLM; Subkey: SOFTWARE\Classes\.plg; ValueType: string; ValueData: htmlfile
Root: HKLM; Subkey: SOFTWARE\Classes\.plg; ValueType: string; ValueName: Content Type; ValueData: text/html
Root: HKLM; Subkey: SOFTWARE\Classes\.plg; ValueType: string; ValueName: PerceivedType; ValueData: text

Root: HKLM; Subkey: SOFTWARE\Classes\.rc; ValueType: string; ValueData: rcfile
Root: HKLM; Subkey: SOFTWARE\Classes\rcfile; ValueType: string; ValueData: Resource Template
Root: HKLM; Subkey: SOFTWARE\Classes\rcfile; ValueType: string; ValueName: AlwaysShowExt
Root: HKLM; Subkey: SOFTWARE\Classes\rcfile\DefaultIcon; ValueType: string; ValueData: {app}\Common\MSDev98\Bin\msdev.exe,-20212
Root: HKLM; Subkey: SOFTWARE\Classes\rcfile\shell\&Open with MSDev; ValueType: string; ValueData: &Open with MSDEV
Root: HKLM; Subkey: SOFTWARE\Classes\rcfile\shell\&Open with MSDev\command; ValueType: string; ValueData: """{app}\Common\MSDev98\Bin\msdev.exe"" ""%1"""
Root: HKLM; Subkey: SOFTWARE\Classes\rcfile\shell\&Open with MSDev\ddeexec; ValueType: string; ValueData: "Open(""%1"")"
Root: HKLM; Subkey: SOFTWARE\Classes\rcfile\shell\&Open with MSDev\ddeexec\application; ValueType: string; ValueData: msdev
Root: HKLM; Subkey: SOFTWARE\Classes\rcfile\shell\&Open with MSDev\ddeexec\topic; ValueType: string; ValueData: system

Root: HKLM; Subkey: SOFTWARE\Classes\.rct; ValueType: string; ValueData: rctfile
Root: HKLM; Subkey: SOFTWARE\Classes\rctfile; ValueType: string; ValueData: Resource Template
Root: HKLM; Subkey: SOFTWARE\Classes\rctfile; ValueType: string; ValueName: AlwaysShowExt
Root: HKLM; Subkey: SOFTWARE\Classes\rctfile\DefaultIcon; ValueType: string; ValueData: {app}\Common\MSDev98\Bin\msdev.exe,-20212
Root: HKLM; Subkey: SOFTWARE\Classes\rctfile\shell\&Open with MSDev; ValueType: string; ValueData: &Open with MSDEV
Root: HKLM; Subkey: SOFTWARE\Classes\rctfile\shell\&Open with MSDev\command; ValueType: string; ValueData: """{app}\Common\MSDev98\Bin\msdev.exe"" ""%1"""
Root: HKLM; Subkey: SOFTWARE\Classes\rctfile\shell\&Open with MSDev\ddeexec; ValueType: string; ValueData: "Open(""%1"")"
Root: HKLM; Subkey: SOFTWARE\Classes\rctfile\shell\&Open with MSDev\ddeexec\application; ValueType: string; ValueData: msdev
Root: HKLM; Subkey: SOFTWARE\Classes\rctfile\shell\&Open with MSDev\ddeexec\topic; ValueType: string; ValueData: system

Root: HKLM; Subkey: SOFTWARE\Classes\.res; ValueType: string; ValueData: resfile
Root: HKLM; Subkey: SOFTWARE\Classes\resfile; ValueType: string; ValueData: RES File
Root: HKLM; Subkey: SOFTWARE\Classes\resfile; ValueType: string; ValueName: AlwaysShowExt
Root: HKLM; Subkey: SOFTWARE\Classes\resfile\DefaultIcon; ValueType: string; ValueData: {app}\Common\MSDev98\Bin\msdev.exe,-20215
Root: HKLM; Subkey: SOFTWARE\Classes\resfile\shell\&Open with MSDev; ValueType: string; ValueData: &Open with MSDEV
Root: HKLM; Subkey: SOFTWARE\Classes\resfile\shell\&Open with MSDev\command; ValueType: string; ValueData: """{app}\Common\MSDev98\Bin\msdev.exe"" ""%1"""
Root: HKLM; Subkey: SOFTWARE\Classes\resfile\shell\&Open with MSDev\ddeexec; ValueType: string; ValueData: "Open(""%1"")"
Root: HKLM; Subkey: SOFTWARE\Classes\resfile\shell\&Open with MSDev\ddeexec\application; ValueType: string; ValueData: msdev
Root: HKLM; Subkey: SOFTWARE\Classes\resfile\shell\&Open with MSDev\ddeexec\topic; ValueType: string; ValueData: system

Root: HKLM; Subkey: SOFTWARE\Classes\.sbr; ValueType: string; ValueData: sbrfile
Root: HKLM; Subkey: SOFTWARE\Classes\sbrfile; ValueType: string; ValueData: Intermediate file
Root: HKLM; Subkey: SOFTWARE\Classes\sbrfile; ValueType: string; ValueName: AlwaysShowExt
Root: HKLM; Subkey: SOFTWARE\Classes\sbrfile\DefaultIcon; ValueType: string; ValueData: {app}\Common\MSDev98\Bin\msdev.exe,-20215

Root: HKLM; Subkey: SOFTWARE\Classes\.tlb; ValueType: string; ValueData: tlbfile
Root: HKLM; Subkey: SOFTWARE\Classes\tlbfile; ValueType: string; ValueData: Type Library
Root: HKLM; Subkey: SOFTWARE\Classes\tlbfile; ValueType: string; ValueName: AlwaysShowExt
Root: HKLM; Subkey: SOFTWARE\Classes\tlbfile\DefaultIcon; ValueType: string; ValueData: {app}\Common\MSDev98\Bin\msdev.exe,-20215

Root: HKLM; Subkey: SOFTWARE\Classes\.tlh; ValueType: string; ValueData: tlhfile
Root: HKLM; Subkey: SOFTWARE\Classes\tlhfile; ValueType: string; ValueData: TLH file
Root: HKLM; Subkey: SOFTWARE\Classes\tlhfile; ValueType: string; ValueName: AlwaysShowExt
Root: HKLM; Subkey: SOFTWARE\Classes\tlhfile\DefaultIcon; ValueType: string; ValueData: {app}\Common\MSDev98\Bin\msdev.exe,-20215
Root: HKLM; Subkey: SOFTWARE\Classes\tlhfile\shell\&Open with MSDev; ValueType: string; ValueData: &Open with MSDEV
Root: HKLM; Subkey: SOFTWARE\Classes\tlhfile\shell\&Open with MSDev\command; ValueType: string; ValueData: """{app}\Common\MSDev98\Bin\msdev.exe"" ""%1"""
Root: HKLM; Subkey: SOFTWARE\Classes\tlhfile\shell\&Open with MSDev\ddeexec; ValueType: string; ValueData: "Open(""%1"")"
Root: HKLM; Subkey: SOFTWARE\Classes\tlhfile\shell\&Open with MSDev\ddeexec\application; ValueType: string; ValueData: msdev
Root: HKLM; Subkey: SOFTWARE\Classes\tlhfile\shell\&Open with MSDev\ddeexec\topic; ValueType: string; ValueData: system

Root: HKLM; Subkey: SOFTWARE\Classes\.tli; ValueType: string; ValueData: tlifile
Root: HKLM; Subkey: SOFTWARE\Classes\tlifile; ValueType: string; ValueData: TLI file
Root: HKLM; Subkey: SOFTWARE\Classes\tlifile; ValueType: string; ValueName: AlwaysShowExt
Root: HKLM; Subkey: SOFTWARE\Classes\tlifile\DefaultIcon; ValueType: string; ValueData: {app}\Common\MSDev98\Bin\msdev.exe,-20215
Root: HKLM; Subkey: SOFTWARE\Classes\tlifile\shell\&Open with MSDev; ValueType: string; ValueData: &Open with MSDEV
Root: HKLM; Subkey: SOFTWARE\Classes\tlifile\shell\&Open with MSDev\command; ValueType: string; ValueData: """{app}\Common\MSDev98\Bin\msdev.exe"" ""%1"""
Root: HKLM; Subkey: SOFTWARE\Classes\tlifile\shell\&Open with MSDev\ddeexec; ValueType: string; ValueData: "Open(""%1"")"
Root: HKLM; Subkey: SOFTWARE\Classes\tlifile\shell\&Open with MSDev\ddeexec\application; ValueType: string; ValueData: msdev
Root: HKLM; Subkey: SOFTWARE\Classes\tlifile\shell\&Open with MSDev\ddeexec\topic; ValueType: string; ValueData: system

Root: HKLM; Subkey: SOFTWARE\Classes\AppID\{{2C99AFCC-F99D-11D1-BB9D-00A0C9C9CCEE}; ValueType: string; ValueData: cemgr; Components: VisualCpp\CeTools
Root: HKLM; Subkey: SOFTWARE\Classes\AppID\cemgr.EXE; ValueType: string; ValueName: AppID; ValueData: {{2C99AFCC-F99D-11D1-BB9D-00A0C9C9CCEE}; Components: VisualCpp\CeTools

Root: HKLM; Subkey: SOFTWARE\Classes\AxBrowse.AxBrowser; ValueType: string; ValueData: AxBrowse.AxBrowser
Root: HKLM; Subkey: SOFTWARE\Classes\AxBrowse.AxBrowser\Clsid; ValueType: string; ValueData: {{A8F8E829-06DA-11D2-8D70-00A0C98B28E2}

Root: HKLM; Subkey: SOFTWARE\Classes\Cemgrui.PlatformManagerUI.1; ValueType: string; ValueData: PlatformManagerUI Class; Components: VisualCpp\CeTools
Root: HKLM; Subkey: SOFTWARE\Classes\Cemgrui.PlatformManagerUI.1\CLSID; ValueType: string; ValueData: {{E835B190-3DDF-11D2-BBB2-00A0C9C9CCEE}; Components: VisualCpp\CeTools
Root: HKLM; Subkey: SOFTWARE\Classes\Cemgrui.PlatformManagerUI; ValueType: string; ValueData: PlatformManagerUI Class; Components: VisualCpp\CeTools
Root: HKLM; Subkey: SOFTWARE\Classes\Cemgrui.PlatformManagerUI\CLSID; ValueType: string; ValueData: {{E835B190-3DDF-11D2-BBB2-00A0C9C9CCEE}; Components: VisualCpp\CeTools

Root: HKLM; Subkey: SOFTWARE\Classes\CLSID\{{09BB1114-3755-11D1-962B-00600818410C}; ValueType: string; ValueData: ItemProperties Class
Root: HKLM; Subkey: SOFTWARE\Classes\CLSID\{{09BB1114-3755-11D1-962B-00600818410C}\InprocServer32; ValueType: string; ValueData: {app}\Common\IDE\IDE98\VCMPK.DLL
Root: HKLM; Subkey: SOFTWARE\Classes\CLSID\{{09BB1114-3755-11D1-962B-00600818410C}\InprocServer32; ValueType: string; ValueName: ThreadingModel; ValueData: Apartment
Root: HKLM; Subkey: SOFTWARE\Classes\CLSID\{{09BB1114-3755-11D1-962B-00600818410C}\ProgID; ValueType: string; ValueData: VcmPackage.ItemProperties.1
Root: HKLM; Subkey: SOFTWARE\Classes\CLSID\{{09BB1114-3755-11D1-962B-00600818410C}\Programmable
Root: HKLM; Subkey: SOFTWARE\Classes\CLSID\{{09BB1114-3755-11D1-962B-00600818410C}\VersionIndependentProgID; ValueType: string; ValueData: VcmPackage.ItemProperties

Root: HKLM; Subkey: SOFTWARE\Classes\CLSID\{{09BB1116-3755-11D1-962B-00600818410C}; ValueType: string; ValueData: ItemProperty Class
Root: HKLM; Subkey: SOFTWARE\Classes\CLSID\{{09BB1116-3755-11D1-962B-00600818410C}\InprocServer32; ValueType: string; ValueData: {app}\Common\IDE\IDE98\VCMPK.DLL
Root: HKLM; Subkey: SOFTWARE\Classes\CLSID\{{09BB1116-3755-11D1-962B-00600818410C}\InprocServer32; ValueType: string; ValueName: ThreadingModel; ValueData: Apartment
Root: HKLM; Subkey: SOFTWARE\Classes\CLSID\{{09BB1116-3755-11D1-962B-00600818410C}\ProgID; ValueType: string; ValueData: VcmPackage.ItemProperty.1
Root: HKLM; Subkey: SOFTWARE\Classes\CLSID\{{09BB1116-3755-11D1-962B-00600818410C}\Programmable
Root: HKLM; Subkey: SOFTWARE\Classes\CLSID\{{09BB1116-3755-11D1-962B-00600818410C}\VersionIndependentProgID; ValueType: string; ValueData: VcmPackage.ItemProperty

Root: HKLM; Subkey: SOFTWARE\Classes\CLSID\{{0BE35200-8F91-11CE-9DE3-00AA004BB851}\InprocServer32; ValueType: string; ValueData: {sys}\MFC40.DLL; Components: VisualCpp\ServicePack
Root: HKLM; Subkey: SOFTWARE\Classes\CLSID\{{0BE35201-8F91-11CE-9DE3-00AA004BB851}\InprocServer32; ValueType: string; ValueData: {sys}\MFC40.DLL; Components: VisualCpp\ServicePack
Root: HKLM; Subkey: SOFTWARE\Classes\CLSID\{{0BE35202-8F91-11CE-9DE3-00AA004BB851}\InprocServer32; ValueType: string; ValueData: {sys}\MFC40.DLL; Components: VisualCpp\ServicePack

#ifdef INSTALL_WNDTABS
;Root: HKLM; Subkey: SOFTWARE\Classes\CLSID\{{1432D665-1AB1-4175-9991-8CCA5FC52578}; ValueType: string; ValueData: WndTabs SDK Sample Add-In; Components: WndTabs
;Root: HKLM; Subkey: SOFTWARE\Classes\CLSID\{{1432D665-1AB1-4175-9991-8CCA5FC52578}\Description; ValueType: string; ValueData: A sample of things you can achieve using the WndTabs SDK; Components: WndTabs
;Root: HKLM; Subkey: SOFTWARE\Classes\CLSID\{{1432D665-1AB1-4175-9991-8CCA5FC52578}\InprocServer32; ValueType: string; ValueData: {app}\WndTabs\WTSDK_Samp.dll; Components: WndTabs
;Root: HKLM; Subkey: SOFTWARE\Classes\CLSID\{{1432D665-1AB1-4175-9991-8CCA5FC52578}\InprocServer32; ValueType: string; ValueName: ThreadingModel; ValueData: both; Components: WndTabs
;Root: HKLM; Subkey: SOFTWARE\Classes\CLSID\{{1432D665-1AB1-4175-9991-8CCA5FC52578}\ProgID; ValueType: string; ValueData: WTSDK_Samp.DSAddIn.1; Components: WndTabs
;Root: HKLM; Subkey: SOFTWARE\Classes\CLSID\{{1432D665-1AB1-4175-9991-8CCA5FC52578}\VersionIndependentProgID; ValueType: string; ValueData: WTSDK_SAMP Developer Studio Add-in; Components: WndTabs
#endif

Root: HKLM; Subkey: SOFTWARE\Classes\CLSID\{{18BF406A-A8C4-11D1-AE5C-00600818410C}; ValueType: string; ValueData: VcmMgr.VsHelp
Root: HKLM; Subkey: SOFTWARE\Classes\CLSID\{{18BF406A-A8C4-11D1-AE5C-00600818410C}\Implemented Categories\{{40FC6ED5-2438-11CF-A3DB-080036F12502}
Root: HKLM; Subkey: SOFTWARE\Classes\CLSID\{{18BF406A-A8C4-11D1-AE5C-00600818410C}\ProgID; ValueType: string; ValueData: VcmMgr.VsHelp
Root: HKLM; Subkey: SOFTWARE\Classes\CLSID\{{18BF406A-A8C4-11D1-AE5C-00600818410C}\Programmable
Root: HKLM; Subkey: SOFTWARE\Classes\CLSID\{{18BF406A-A8C4-11D1-AE5C-00600818410C}\TypeLib; ValueType: string; ValueData: {{18BF4063-A8C4-11D1-AE5C-00600818410C}
Root: HKLM; Subkey: SOFTWARE\Classes\CLSID\{{18BF406A-A8C4-11D1-AE5C-00600818410C}\VERSION; ValueType: string; ValueData: 7.0

Root: HKLM; Subkey: SOFTWARE\Classes\CLSID\{{18BF406C-A8C4-11D1-AE5C-00600818410C}; ValueType: string; ValueData: Visual Component Manager 6.0
Root: HKLM; Subkey: SOFTWARE\Classes\CLSID\{{18BF406C-A8C4-11D1-AE5C-00600818410C}\Implemented Categories\{{40FC6ED5-2438-11CF-A3DB-080036F12502}
Root: HKLM; Subkey: SOFTWARE\Classes\CLSID\{{18BF406C-A8C4-11D1-AE5C-00600818410C}\InprocServer32; ValueType: string; ValueData: {app}\Common\Tools\VCM\VCMMGR.DLL
Root: HKLM; Subkey: SOFTWARE\Classes\CLSID\{{18BF406C-A8C4-11D1-AE5C-00600818410C}\ProgID; ValueType: string; ValueData: VcmMgr.Connect
Root: HKLM; Subkey: SOFTWARE\Classes\CLSID\{{18BF406C-A8C4-11D1-AE5C-00600818410C}\Programmable
Root: HKLM; Subkey: SOFTWARE\Classes\CLSID\{{18BF406C-A8C4-11D1-AE5C-00600818410C}\TypeLib; ValueType: string; ValueData: {{18BF4063-A8C4-11D1-AE5C-00600818410C}
Root: HKLM; Subkey: SOFTWARE\Classes\CLSID\{{18BF406C-A8C4-11D1-AE5C-00600818410C}\VERSION; ValueType: string; ValueData: 7.0

Root: HKLM; Subkey: SOFTWARE\Classes\CLSID\{{18BF4078-A8C4-11D1-AE5C-00600818410C}; ValueType: string; ValueData: VcmMgr.TypeDefinition
Root: HKLM; Subkey: SOFTWARE\Classes\CLSID\{{18BF4078-A8C4-11D1-AE5C-00600818410C}\Implemented Categories\{{40FC6ED5-2438-11CF-A3DB-080036F12502}
Root: HKLM; Subkey: SOFTWARE\Classes\CLSID\{{18BF4078-A8C4-11D1-AE5C-00600818410C}\InprocServer32; ValueType: string; ValueData: {app}\Common\Tools\VCM\VCMMGR.DLL
Root: HKLM; Subkey: SOFTWARE\Classes\CLSID\{{18BF4078-A8C4-11D1-AE5C-00600818410C}\ProgID; ValueType: string; ValueData: VcmMgr.TypeDefinition
Root: HKLM; Subkey: SOFTWARE\Classes\CLSID\{{18BF4078-A8C4-11D1-AE5C-00600818410C}\Programmable
Root: HKLM; Subkey: SOFTWARE\Classes\CLSID\{{18BF4078-A8C4-11D1-AE5C-00600818410C}\TypeLib; ValueType: string; ValueData: {{18BF4063-A8C4-11D1-AE5C-00600818410C}
Root: HKLM; Subkey: SOFTWARE\Classes\CLSID\{{18BF4078-A8C4-11D1-AE5C-00600818410C}\VERSION; ValueType: string; ValueData: 7.0

Root: HKLM; Subkey: SOFTWARE\Classes\CLSID\{{18BF407C-A8C4-11D1-AE5C-00600818410C}; ValueType: string; ValueData: VcmMgr.ItemProperty
Root: HKLM; Subkey: SOFTWARE\Classes\CLSID\{{18BF407C-A8C4-11D1-AE5C-00600818410C}\Implemented Categories\{{40FC6ED5-2438-11CF-A3DB-080036F12502}
Root: HKLM; Subkey: SOFTWARE\Classes\CLSID\{{18BF407C-A8C4-11D1-AE5C-00600818410C}\InprocServer32; ValueType: string; ValueData: {app}\Common\Tools\VCM\VCMMGR.DLL
Root: HKLM; Subkey: SOFTWARE\Classes\CLSID\{{18BF407C-A8C4-11D1-AE5C-00600818410C}\ProgID; ValueType: string; ValueData: VcmMgr.ItemProperty
Root: HKLM; Subkey: SOFTWARE\Classes\CLSID\{{18BF407C-A8C4-11D1-AE5C-00600818410C}\Programmable
Root: HKLM; Subkey: SOFTWARE\Classes\CLSID\{{18BF407C-A8C4-11D1-AE5C-00600818410C}\TypeLib; ValueType: string; ValueData: {{18BF4063-A8C4-11D1-AE5C-00600818410C}
Root: HKLM; Subkey: SOFTWARE\Classes\CLSID\{{18BF407C-A8C4-11D1-AE5C-00600818410C}\VERSION; ValueType: string; ValueData: 7.0

Root: HKLM; Subkey: SOFTWARE\Classes\CLSID\{{18BF407F-A8C4-11D1-AE5C-00600818410C}; ValueType: string; ValueData: VcmMgr.CabProgress
Root: HKLM; Subkey: SOFTWARE\Classes\CLSID\{{18BF407F-A8C4-11D1-AE5C-00600818410C}\Implemented Categories\{{40FC6ED5-2438-11CF-A3DB-080036F12502}
Root: HKLM; Subkey: SOFTWARE\Classes\CLSID\{{18BF407F-A8C4-11D1-AE5C-00600818410C}\InprocServer32; ValueType: string; ValueData: {app}\Common\Tools\VCM\VCMMGR.DLL
Root: HKLM; Subkey: SOFTWARE\Classes\CLSID\{{18BF407F-A8C4-11D1-AE5C-00600818410C}\ProgID; ValueType: string; ValueData: VcmMgr.CabProgress
Root: HKLM; Subkey: SOFTWARE\Classes\CLSID\{{18BF407F-A8C4-11D1-AE5C-00600818410C}\Programmable
Root: HKLM; Subkey: SOFTWARE\Classes\CLSID\{{18BF407F-A8C4-11D1-AE5C-00600818410C}\TypeLib; ValueType: string; ValueData: {{18BF4063-A8C4-11D1-AE5C-00600818410C}
Root: HKLM; Subkey: SOFTWARE\Classes\CLSID\{{18BF407F-A8C4-11D1-AE5C-00600818410C}\VERSION; ValueType: string; ValueData: 7.0

Root: HKLM; Subkey: SOFTWARE\Classes\CLSID\{{18BF4085-A8C4-11D1-AE5C-00600818410C}; ValueType: string; ValueData: Item Handler for Group Type items.
Root: HKLM; Subkey: SOFTWARE\Classes\CLSID\{{18BF4085-A8C4-11D1-AE5C-00600818410C}\Implemented Categories\{{40FC6ED5-2438-11CF-A3DB-080036F12502}
Root: HKLM; Subkey: SOFTWARE\Classes\CLSID\{{18BF4085-A8C4-11D1-AE5C-00600818410C}\InprocServer32; ValueType: string; ValueData: {app}\Common\Tools\VCM\VCMMGR.DLL
Root: HKLM; Subkey: SOFTWARE\Classes\CLSID\{{18BF4085-A8C4-11D1-AE5C-00600818410C}\ProgID; ValueType: string; ValueData: VcmMgr.ActiveXHandler
Root: HKLM; Subkey: SOFTWARE\Classes\CLSID\{{18BF4085-A8C4-11D1-AE5C-00600818410C}\Programmable
Root: HKLM; Subkey: SOFTWARE\Classes\CLSID\{{18BF4085-A8C4-11D1-AE5C-00600818410C}\TypeLib; ValueType: string; ValueData: {{18BF4063-A8C4-11D1-AE5C-00600818410C}
Root: HKLM; Subkey: SOFTWARE\Classes\CLSID\{{18BF4085-A8C4-11D1-AE5C-00600818410C}\VERSION; ValueType: string; ValueData: 7.0

Root: HKLM; Subkey: SOFTWARE\Classes\CLSID\{{18BF4087-A8C4-11D1-AE5C-00600818410C}; ValueType: string; ValueData: Item Handler for Project Type items.
Root: HKLM; Subkey: SOFTWARE\Classes\CLSID\{{18BF4087-A8C4-11D1-AE5C-00600818410C}\Implemented Categories\{{40FC6ED5-2438-11CF-A3DB-080036F12502}
Root: HKLM; Subkey: SOFTWARE\Classes\CLSID\{{18BF4087-A8C4-11D1-AE5C-00600818410C}\InprocServer32; ValueType: string; ValueData: {app}\Common\Tools\VCM\VCMMGR.DLL
Root: HKLM; Subkey: SOFTWARE\Classes\CLSID\{{18BF4087-A8C4-11D1-AE5C-00600818410C}\ProgID; ValueType: string; ValueData: VcmMgr.DocumentHandler
Root: HKLM; Subkey: SOFTWARE\Classes\CLSID\{{18BF4087-A8C4-11D1-AE5C-00600818410C}\Programmable
Root: HKLM; Subkey: SOFTWARE\Classes\CLSID\{{18BF4087-A8C4-11D1-AE5C-00600818410C}\TypeLib; ValueType: string; ValueData: {{18BF4063-A8C4-11D1-AE5C-00600818410C}
Root: HKLM; Subkey: SOFTWARE\Classes\CLSID\{{18BF4087-A8C4-11D1-AE5C-00600818410C}\VERSION; ValueType: string; ValueData: 7.0

Root: HKLM; Subkey: SOFTWARE\Classes\CLSID\{{18BF4089-A8C4-11D1-AE5C-00600818410C}; ValueType: string; ValueData: Item Handler for Project Type items.
Root: HKLM; Subkey: SOFTWARE\Classes\CLSID\{{18BF4089-A8C4-11D1-AE5C-00600818410C}\Implemented Categories\{{40FC6ED5-2438-11CF-A3DB-080036F12502}
Root: HKLM; Subkey: SOFTWARE\Classes\CLSID\{{18BF4089-A8C4-11D1-AE5C-00600818410C}\InprocServer32; ValueType: string; ValueData: {app}\Common\Tools\VCM\VCMMGR.DLL
Root: HKLM; Subkey: SOFTWARE\Classes\CLSID\{{18BF4089-A8C4-11D1-AE5C-00600818410C}\ProgID; ValueType: string; ValueData: VcmMgr.VBProjectHandler
Root: HKLM; Subkey: SOFTWARE\Classes\CLSID\{{18BF4089-A8C4-11D1-AE5C-00600818410C}\Programmable
Root: HKLM; Subkey: SOFTWARE\Classes\CLSID\{{18BF4089-A8C4-11D1-AE5C-00600818410C}\TypeLib; ValueType: string; ValueData: {{18BF4063-A8C4-11D1-AE5C-00600818410C}
Root: HKLM; Subkey: SOFTWARE\Classes\CLSID\{{18BF4089-A8C4-11D1-AE5C-00600818410C}\VERSION; ValueType: string; ValueData: 7.0

Root: HKLM; Subkey: SOFTWARE\Classes\CLSID\{{18BF408B-A8C4-11D1-AE5C-00600818410C}; ValueType: string; ValueData: Item Handler for Project Type items.
Root: HKLM; Subkey: SOFTWARE\Classes\CLSID\{{18BF408B-A8C4-11D1-AE5C-00600818410C}\Implemented Categories\{{40FC6ED5-2438-11CF-A3DB-080036F12502}
Root: HKLM; Subkey: SOFTWARE\Classes\CLSID\{{18BF408B-A8C4-11D1-AE5C-00600818410C}\InprocServer32; ValueType: string; ValueData: {app}\Common\Tools\VCM\VCMMGR.DLL
Root: HKLM; Subkey: SOFTWARE\Classes\CLSID\{{18BF408B-A8C4-11D1-AE5C-00600818410C}\ProgID; ValueType: string; ValueData: VcmMgr.VBConnectionHandler
Root: HKLM; Subkey: SOFTWARE\Classes\CLSID\{{18BF408B-A8C4-11D1-AE5C-00600818410C}\Programmable
Root: HKLM; Subkey: SOFTWARE\Classes\CLSID\{{18BF408B-A8C4-11D1-AE5C-00600818410C}\TypeLib; ValueType: string; ValueData: {{18BF4063-A8C4-11D1-AE5C-00600818410C}
Root: HKLM; Subkey: SOFTWARE\Classes\CLSID\{{18BF408B-A8C4-11D1-AE5C-00600818410C}\VERSION; ValueType: string; ValueData: 7.0

Root: HKLM; Subkey: SOFTWARE\Classes\CLSID\{{18BF408D-A8C4-11D1-AE5C-00600818410C}; ValueType: string; ValueData: Item Handler for Template Type items.
Root: HKLM; Subkey: SOFTWARE\Classes\CLSID\{{18BF408D-A8C4-11D1-AE5C-00600818410C}\Implemented Categories\{{40FC6ED5-2438-11CF-A3DB-080036F12502}
Root: HKLM; Subkey: SOFTWARE\Classes\CLSID\{{18BF408D-A8C4-11D1-AE5C-00600818410C}\InprocServer32; ValueType: string; ValueData: {app}\Common\Tools\VCM\VCMMGR.DLL
Root: HKLM; Subkey: SOFTWARE\Classes\CLSID\{{18BF408D-A8C4-11D1-AE5C-00600818410C}\ProgID; ValueType: string; ValueData: VcmMgr.VBTemplateHandler
Root: HKLM; Subkey: SOFTWARE\Classes\CLSID\{{18BF408D-A8C4-11D1-AE5C-00600818410C}\Programmable
Root: HKLM; Subkey: SOFTWARE\Classes\CLSID\{{18BF408D-A8C4-11D1-AE5C-00600818410C}\TypeLib; ValueType: string; ValueData: {{18BF4063-A8C4-11D1-AE5C-00600818410C}
Root: HKLM; Subkey: SOFTWARE\Classes\CLSID\{{18BF408D-A8C4-11D1-AE5C-00600818410C}\VERSION; ValueType: string; ValueData: 7.0

Root: HKLM; Subkey: SOFTWARE\Classes\CLSID\{{18BF4091-A8C4-11D1-AE5C-00600818410C}; ValueType: string; ValueData: VcmMgr.JavaHandler
Root: HKLM; Subkey: SOFTWARE\Classes\CLSID\{{18BF4091-A8C4-11D1-AE5C-00600818410C}\Implemented Categories\{{40FC6ED5-2438-11CF-A3DB-080036F12502}
Root: HKLM; Subkey: SOFTWARE\Classes\CLSID\{{18BF4091-A8C4-11D1-AE5C-00600818410C}\InprocServer32; ValueType: string; ValueData: {app}\Common\Tools\VCM\VCMMGR.DLL
Root: HKLM; Subkey: SOFTWARE\Classes\CLSID\{{18BF4091-A8C4-11D1-AE5C-00600818410C}\ProgID; ValueType: string; ValueData: VcmMgr.JavaHandler
Root: HKLM; Subkey: SOFTWARE\Classes\CLSID\{{18BF4091-A8C4-11D1-AE5C-00600818410C}\Programmable
Root: HKLM; Subkey: SOFTWARE\Classes\CLSID\{{18BF4091-A8C4-11D1-AE5C-00600818410C}\TypeLib; ValueType: string; ValueData: {{18BF4063-A8C4-11D1-AE5C-00600818410C}
Root: HKLM; Subkey: SOFTWARE\Classes\CLSID\{{18BF4091-A8C4-11D1-AE5C-00600818410C}\VERSION; ValueType: string; ValueData: 7.0

Root: HKLM; Subkey: SOFTWARE\Classes\CLSID\{{1E9A88A2-2968-11D1-851D-00A0C911E8B0}; ValueType: string; ValueData: VisModelBrowser.VMBrowser
Root: HKLM; Subkey: SOFTWARE\Classes\CLSID\{{1E9A88A2-2968-11D1-851D-00A0C911E8B0}\Control; ValueType: string; ValueData: 
Root: HKLM; Subkey: SOFTWARE\Classes\CLSID\{{1E9A88A2-2968-11D1-851D-00A0C911E8B0}\Implemented Categories\{{0DE86A52-2BAA-11CF-A229-00AA003D7352}
Root: HKLM; Subkey: SOFTWARE\Classes\CLSID\{{1E9A88A2-2968-11D1-851D-00A0C911E8B0}\Implemented Categories\{{0DE86A53-2BAA-11CF-A229-00AA003D7352}
Root: HKLM; Subkey: SOFTWARE\Classes\CLSID\{{1E9A88A2-2968-11D1-851D-00A0C911E8B0}\Implemented Categories\{{0DE86A57-2BAA-11CF-A229-00AA003D7352}
Root: HKLM; Subkey: SOFTWARE\Classes\CLSID\{{1E9A88A2-2968-11D1-851D-00A0C911E8B0}\Implemented Categories\{{40FC6ED4-2438-11CF-A3DB-080036F12502}
Root: HKLM; Subkey: SOFTWARE\Classes\CLSID\{{1E9A88A2-2968-11D1-851D-00A0C911E8B0}\InprocServer32; ValueType: string; ValueData: {app}\Common\Tools\VCM\VCMVMB.OCX
Root: HKLM; Subkey: SOFTWARE\Classes\CLSID\{{1E9A88A2-2968-11D1-851D-00A0C911E8B0}\MiscStatus; ValueType: string; ValueData: 0
Root: HKLM; Subkey: SOFTWARE\Classes\CLSID\{{1E9A88A2-2968-11D1-851D-00A0C911E8B0}\MiscStatus\1; ValueType: string; ValueData: 131473
Root: HKLM; Subkey: SOFTWARE\Classes\CLSID\{{1E9A88A2-2968-11D1-851D-00A0C911E8B0}\ProgID; ValueType: string; ValueData: VisModelBrowser.VMBrowser
Root: HKLM; Subkey: SOFTWARE\Classes\CLSID\{{1E9A88A2-2968-11D1-851D-00A0C911E8B0}\ToolboxBitmap32; ValueType: string; ValueData: {app}\Common\Tools\VCM\VCMVMB.OCX, 30000
Root: HKLM; Subkey: SOFTWARE\Classes\CLSID\{{1E9A88A2-2968-11D1-851D-00A0C911E8B0}\TypeLib; ValueType: string; ValueData: {{1E9A88A4-2968-11D1-851D-00A0C911E8B0}
Root: HKLM; Subkey: SOFTWARE\Classes\CLSID\{{1E9A88A2-2968-11D1-851D-00A0C911E8B0}\VERSION; ValueType: string; ValueData: 1.0

Root: HKLM; Subkey: SOFTWARE\Classes\CLSID\{{2A4F783A-014E-11D2-BBA0-00A0C9C9CCEE}; ValueType: string; ValueData: PSFactoryBuffer; Components: VisualCpp\CeTools
Root: HKLM; Subkey: SOFTWARE\Classes\CLSID\{{2A4F783A-014E-11D2-BBA0-00A0C9C9CCEE}\InProcServer32; ValueType: string; ValueData: {app}\Windows CE Tools\BIN\CEMGRPS.DLL; Components: VisualCpp\CeTools
Root: HKLM; Subkey: SOFTWARE\Classes\CLSID\{{2A4F783A-014E-11D2-BBA0-00A0C9C9CCEE}\InProcServer32; ValueType: string; ValueName: ThreadingModel; ValueData: Both; Components: VisualCpp\CeTools

Root: HKLM; Subkey: SOFTWARE\Classes\CLSID\{{2E338C70-8ED1-11D1-AC54-00A0C94A8147}; ValueType: string; ValueData: VIWFrame.CBitmap; Components: VisualCpp\CeTools
Root: HKLM; Subkey: SOFTWARE\Classes\CLSID\{{2E338C70-8ED1-11D1-AC54-00A0C94A8147}\Implemented Categories; Components: VisualCpp\CeTools
Root: HKLM; Subkey: SOFTWARE\Classes\CLSID\{{2E338C70-8ED1-11D1-AC54-00A0C94A8147}\Implemented Categories\{{40FC6ED5-2438-11CF-A3DB-080036F12502}; Components: VisualCpp\CeTools
Root: HKLM; Subkey: SOFTWARE\Classes\CLSID\{{2E338C70-8ED1-11D1-AC54-00A0C94A8147}\InprocServer32; ValueType: string; ValueData: {cf}\Microsoft Shared\Wizards98\VIWZRT.DLL; Components: VisualCpp\CeTools
Root: HKLM; Subkey: SOFTWARE\Classes\CLSID\{{2E338C70-8ED1-11D1-AC54-00A0C94A8147}\ProgID; ValueType: string; ValueData: VIWFrame.CBitmap; Components: VisualCpp\CeTools
Root: HKLM; Subkey: SOFTWARE\Classes\CLSID\{{2E338C70-8ED1-11D1-AC54-00A0C94A8147}\Programmable; Components: VisualCpp\CeTools
Root: HKLM; Subkey: SOFTWARE\Classes\CLSID\{{2E338C70-8ED1-11D1-AC54-00A0C94A8147}\TypeLib; ValueType: string; ValueData: {{CBE51AA8-A410-11D1-80D0-006097C9987D}; Components: VisualCpp\CeTools
Root: HKLM; Subkey: SOFTWARE\Classes\CLSID\{{2E338C70-8ED1-11D1-AC54-00A0C94A8147}\VERSION; ValueType: string; ValueData: 1.0; Components: VisualCpp\CeTools

Root: HKLM; Subkey: SOFTWARE\Classes\CLSID\{{2E338C71-8ED1-11D1-AC54-00A0C94A8147}; ValueType: string; ValueData: VIWFrame.CBitmaps; Components: VisualCpp\CeTools
Root: HKLM; Subkey: SOFTWARE\Classes\CLSID\{{2E338C71-8ED1-11D1-AC54-00A0C94A8147}\Implemented Categories; Components: VisualCpp\CeTools
Root: HKLM; Subkey: SOFTWARE\Classes\CLSID\{{2E338C71-8ED1-11D1-AC54-00A0C94A8147}\Implemented Categories\{{40FC6ED5-2438-11CF-A3DB-080036F12502}; Components: VisualCpp\CeTools
Root: HKLM; Subkey: SOFTWARE\Classes\CLSID\{{2E338C71-8ED1-11D1-AC54-00A0C94A8147}\InprocServer32; ValueType: string; ValueData: {cf}\Microsoft Shared\Wizards98\VIWZRT.DLL; Components: VisualCpp\CeTools
Root: HKLM; Subkey: SOFTWARE\Classes\CLSID\{{2E338C71-8ED1-11D1-AC54-00A0C94A8147}\ProgID; ValueType: string; ValueData: VIWFrame.CBitmaps; Components: VisualCpp\CeTools
Root: HKLM; Subkey: SOFTWARE\Classes\CLSID\{{2E338C71-8ED1-11D1-AC54-00A0C94A8147}\Programmable; Components: VisualCpp\CeTools
Root: HKLM; Subkey: SOFTWARE\Classes\CLSID\{{2E338C71-8ED1-11D1-AC54-00A0C94A8147}\TypeLib; ValueType: string; ValueData: {{CBE51AA8-A410-11D1-80D0-006097C9987D}; Components: VisualCpp\CeTools
Root: HKLM; Subkey: SOFTWARE\Classes\CLSID\{{2E338C71-8ED1-11D1-AC54-00A0C94A8147}\VERSION; ValueType: string; ValueData: 1.0; Components: VisualCpp\CeTools

Root: HKLM; Subkey: SOFTWARE\Classes\CLSID\{{2E338C72-8ED1-11D1-AC54-00A0C94A8147}; ValueType: string; ValueData: VIWFrame.CError; Components: VisualCpp\CeTools
Root: HKLM; Subkey: SOFTWARE\Classes\CLSID\{{2E338C72-8ED1-11D1-AC54-00A0C94A8147}\Implemented Categories; Components: VisualCpp\CeTools
Root: HKLM; Subkey: SOFTWARE\Classes\CLSID\{{2E338C72-8ED1-11D1-AC54-00A0C94A8147}\Implemented Categories\{{40FC6ED5-2438-11CF-A3DB-080036F12502}; Components: VisualCpp\CeTools
Root: HKLM; Subkey: SOFTWARE\Classes\CLSID\{{2E338C72-8ED1-11D1-AC54-00A0C94A8147}\InprocServer32; ValueType: string; ValueData: {cf}\Microsoft Shared\Wizards98\VIWZRT.DLL; Components: VisualCpp\CeTools
Root: HKLM; Subkey: SOFTWARE\Classes\CLSID\{{2E338C72-8ED1-11D1-AC54-00A0C94A8147}\ProgID; ValueType: string; ValueData: VIWFrame.CError; Components: VisualCpp\CeTools
Root: HKLM; Subkey: SOFTWARE\Classes\CLSID\{{2E338C72-8ED1-11D1-AC54-00A0C94A8147}\Programmable; Components: VisualCpp\CeTools
Root: HKLM; Subkey: SOFTWARE\Classes\CLSID\{{2E338C72-8ED1-11D1-AC54-00A0C94A8147}\TypeLib; ValueType: string; ValueData: {{CBE51AA8-A410-11D1-80D0-006097C9987D}; Components: VisualCpp\CeTools
Root: HKLM; Subkey: SOFTWARE\Classes\CLSID\{{2E338C72-8ED1-11D1-AC54-00A0C94A8147}\VERSION; ValueType: string; ValueData: 1.0; Components: VisualCpp\CeTools

Root: HKLM; Subkey: SOFTWARE\Classes\CLSID\{{2E338C73-8ED1-11D1-AC54-00A0C94A8147}; ValueType: string; ValueData: VIWFrame.CErrors; Components: VisualCpp\CeTools
Root: HKLM; Subkey: SOFTWARE\Classes\CLSID\{{2E338C73-8ED1-11D1-AC54-00A0C94A8147}\Implemented Categories; Components: VisualCpp\CeTools
Root: HKLM; Subkey: SOFTWARE\Classes\CLSID\{{2E338C73-8ED1-11D1-AC54-00A0C94A8147}\Implemented Categories\{{40FC6ED5-2438-11CF-A3DB-080036F12502}; Components: VisualCpp\CeTools
Root: HKLM; Subkey: SOFTWARE\Classes\CLSID\{{2E338C73-8ED1-11D1-AC54-00A0C94A8147}\InprocServer32; ValueType: string; ValueData: {cf}\Microsoft Shared\Wizards98\VIWZRT.DLL; Components: VisualCpp\CeTools
Root: HKLM; Subkey: SOFTWARE\Classes\CLSID\{{2E338C73-8ED1-11D1-AC54-00A0C94A8147}\ProgID; ValueType: string; ValueData: VIWFrame.CErrors; Components: VisualCpp\CeTools
Root: HKLM; Subkey: SOFTWARE\Classes\CLSID\{{2E338C73-8ED1-11D1-AC54-00A0C94A8147}\Programmable; Components: VisualCpp\CeTools
Root: HKLM; Subkey: SOFTWARE\Classes\CLSID\{{2E338C73-8ED1-11D1-AC54-00A0C94A8147}\TypeLib; ValueType: string; ValueData: {{CBE51AA8-A410-11D1-80D0-006097C9987D}; Components: VisualCpp\CeTools
Root: HKLM; Subkey: SOFTWARE\Classes\CLSID\{{2E338C73-8ED1-11D1-AC54-00A0C94A8147}\VERSION; ValueType: string; ValueData: 1.0; Components: VisualCpp\CeTools

Root: HKLM; Subkey: SOFTWARE\Classes\CLSID\{{2E338C74-8ED1-11D1-AC54-00A0C94A8147}; ValueType: string; ValueData: VIWFrame.CField; Components: VisualCpp\CeTools
Root: HKLM; Subkey: SOFTWARE\Classes\CLSID\{{2E338C74-8ED1-11D1-AC54-00A0C94A8147}\Implemented Categories; Components: VisualCpp\CeTools
Root: HKLM; Subkey: SOFTWARE\Classes\CLSID\{{2E338C74-8ED1-11D1-AC54-00A0C94A8147}\Implemented Categories\{{40FC6ED5-2438-11CF-A3DB-080036F12502}; Components: VisualCpp\CeTools
Root: HKLM; Subkey: SOFTWARE\Classes\CLSID\{{2E338C74-8ED1-11D1-AC54-00A0C94A8147}\InprocServer32; ValueType: string; ValueData: {cf}\Microsoft Shared\Wizards98\VIWZRT.DLL; Components: VisualCpp\CeTools
Root: HKLM; Subkey: SOFTWARE\Classes\CLSID\{{2E338C74-8ED1-11D1-AC54-00A0C94A8147}\ProgID; ValueType: string; ValueData: VIWFrame.CField; Components: VisualCpp\CeTools
Root: HKLM; Subkey: SOFTWARE\Classes\CLSID\{{2E338C74-8ED1-11D1-AC54-00A0C94A8147}\Programmable; Components: VisualCpp\CeTools
Root: HKLM; Subkey: SOFTWARE\Classes\CLSID\{{2E338C74-8ED1-11D1-AC54-00A0C94A8147}\TypeLib; ValueType: string; ValueData: {{CBE51AA8-A410-11D1-80D0-006097C9987D}; Components: VisualCpp\CeTools
Root: HKLM; Subkey: SOFTWARE\Classes\CLSID\{{2E338C74-8ED1-11D1-AC54-00A0C94A8147}\VERSION; ValueType: string; ValueData: 1.0; Components: VisualCpp\CeTools

Root: HKLM; Subkey: SOFTWARE\Classes\CLSID\{{2E338C75-8ED1-11D1-AC54-00A0C94A8147}; ValueType: string; ValueData: VIWFrame.CFields; Components: VisualCpp\CeTools
Root: HKLM; Subkey: SOFTWARE\Classes\CLSID\{{2E338C75-8ED1-11D1-AC54-00A0C94A8147}\Implemented Categories; Components: VisualCpp\CeTools
Root: HKLM; Subkey: SOFTWARE\Classes\CLSID\{{2E338C75-8ED1-11D1-AC54-00A0C94A8147}\Implemented Categories\{{40FC6ED5-2438-11CF-A3DB-080036F12502}; Components: VisualCpp\CeTools
Root: HKLM; Subkey: SOFTWARE\Classes\CLSID\{{2E338C75-8ED1-11D1-AC54-00A0C94A8147}\InprocServer32; ValueType: string; ValueData: {cf}\Microsoft Shared\Wizards98\VIWZRT.DLL; Components: VisualCpp\CeTools
Root: HKLM; Subkey: SOFTWARE\Classes\CLSID\{{2E338C75-8ED1-11D1-AC54-00A0C94A8147}\ProgID; ValueType: string; ValueData: VIWFrame.CFields; Components: VisualCpp\CeTools
Root: HKLM; Subkey: SOFTWARE\Classes\CLSID\{{2E338C75-8ED1-11D1-AC54-00A0C94A8147}\Programmable; Components: VisualCpp\CeTools
Root: HKLM; Subkey: SOFTWARE\Classes\CLSID\{{2E338C75-8ED1-11D1-AC54-00A0C94A8147}\TypeLib; ValueType: string; ValueData: {{CBE51AA8-A410-11D1-80D0-006097C9987D}; Components: VisualCpp\CeTools
Root: HKLM; Subkey: SOFTWARE\Classes\CLSID\{{2E338C75-8ED1-11D1-AC54-00A0C94A8147}\VERSION; ValueType: string; ValueData: 1.0; Components: VisualCpp\CeTools

Root: HKLM; Subkey: SOFTWARE\Classes\CLSID\{{2E338C76-8ED1-11D1-AC54-00A0C94A8147}; ValueType: string; ValueData: VIWFrame.CFPServer; Components: VisualCpp\CeTools
Root: HKLM; Subkey: SOFTWARE\Classes\CLSID\{{2E338C76-8ED1-11D1-AC54-00A0C94A8147}\Implemented Categories; Components: VisualCpp\CeTools
Root: HKLM; Subkey: SOFTWARE\Classes\CLSID\{{2E338C76-8ED1-11D1-AC54-00A0C94A8147}\Implemented Categories\{{40FC6ED5-2438-11CF-A3DB-080036F12502}; Components: VisualCpp\CeTools
Root: HKLM; Subkey: SOFTWARE\Classes\CLSID\{{2E338C76-8ED1-11D1-AC54-00A0C94A8147}\InprocServer32; ValueType: string; ValueData: {cf}\Microsoft Shared\Wizards98\VIWZRT.DLL; Components: VisualCpp\CeTools
Root: HKLM; Subkey: SOFTWARE\Classes\CLSID\{{2E338C76-8ED1-11D1-AC54-00A0C94A8147}\ProgID; ValueType: string; ValueData: VIWFrame.CFPServer; Components: VisualCpp\CeTools
Root: HKLM; Subkey: SOFTWARE\Classes\CLSID\{{2E338C76-8ED1-11D1-AC54-00A0C94A8147}\Programmable; Components: VisualCpp\CeTools
Root: HKLM; Subkey: SOFTWARE\Classes\CLSID\{{2E338C76-8ED1-11D1-AC54-00A0C94A8147}\TypeLib; ValueType: string; ValueData: {{CBE51AA8-A410-11D1-80D0-006097C9987D}; Components: VisualCpp\CeTools
Root: HKLM; Subkey: SOFTWARE\Classes\CLSID\{{2E338C76-8ED1-11D1-AC54-00A0C94A8147}\VERSION; ValueType: string; ValueData: 1.0; Components: VisualCpp\CeTools

Root: HKLM; Subkey: SOFTWARE\Classes\CLSID\{{2E338C77-8ED1-11D1-AC54-00A0C94A8147}; ValueType: string; ValueData: VIWFrame.CGraphic; Components: VisualCpp\CeTools
Root: HKLM; Subkey: SOFTWARE\Classes\CLSID\{{2E338C77-8ED1-11D1-AC54-00A0C94A8147}\Implemented Categories; Components: VisualCpp\CeTools
Root: HKLM; Subkey: SOFTWARE\Classes\CLSID\{{2E338C77-8ED1-11D1-AC54-00A0C94A8147}\Implemented Categories\{{40FC6ED5-2438-11CF-A3DB-080036F12502}; Components: VisualCpp\CeTools
Root: HKLM; Subkey: SOFTWARE\Classes\CLSID\{{2E338C77-8ED1-11D1-AC54-00A0C94A8147}\InprocServer32; ValueType: string; ValueData: {cf}\Microsoft Shared\Wizards98\VIWZRT.DLL; Components: VisualCpp\CeTools
Root: HKLM; Subkey: SOFTWARE\Classes\CLSID\{{2E338C77-8ED1-11D1-AC54-00A0C94A8147}\ProgID; ValueType: string; ValueData: VIWFrame.CGraphic; Components: VisualCpp\CeTools
Root: HKLM; Subkey: SOFTWARE\Classes\CLSID\{{2E338C77-8ED1-11D1-AC54-00A0C94A8147}\Programmable; Components: VisualCpp\CeTools
Root: HKLM; Subkey: SOFTWARE\Classes\CLSID\{{2E338C77-8ED1-11D1-AC54-00A0C94A8147}\TypeLib; ValueType: string; ValueData: {{CBE51AA8-A410-11D1-80D0-006097C9987D}; Components: VisualCpp\CeTools
Root: HKLM; Subkey: SOFTWARE\Classes\CLSID\{{2E338C77-8ED1-11D1-AC54-00A0C94A8147}\VERSION; ValueType: string; ValueData: 1.0; Components: VisualCpp\CeTools

Root: HKLM; Subkey: SOFTWARE\Classes\CLSID\{{2E338C78-8ED1-11D1-AC54-00A0C94A8147}; ValueType: string; ValueData: VIWFrame.CGraphics; Components: VisualCpp\CeTools
Root: HKLM; Subkey: SOFTWARE\Classes\CLSID\{{2E338C78-8ED1-11D1-AC54-00A0C94A8147}\Implemented Categories; Components: VisualCpp\CeTools
Root: HKLM; Subkey: SOFTWARE\Classes\CLSID\{{2E338C78-8ED1-11D1-AC54-00A0C94A8147}\Implemented Categories\{{40FC6ED5-2438-11CF-A3DB-080036F12502}; Components: VisualCpp\CeTools
Root: HKLM; Subkey: SOFTWARE\Classes\CLSID\{{2E338C78-8ED1-11D1-AC54-00A0C94A8147}\InprocServer32; ValueType: string; ValueData: {cf}\Microsoft Shared\Wizards98\VIWZRT.DLL; Components: VisualCpp\CeTools
Root: HKLM; Subkey: SOFTWARE\Classes\CLSID\{{2E338C78-8ED1-11D1-AC54-00A0C94A8147}\ProgID; ValueType: string; ValueData: VIWFrame.CGraphics; Components: VisualCpp\CeTools
Root: HKLM; Subkey: SOFTWARE\Classes\CLSID\{{2E338C78-8ED1-11D1-AC54-00A0C94A8147}\Programmable; Components: VisualCpp\CeTools
Root: HKLM; Subkey: SOFTWARE\Classes\CLSID\{{2E338C78-8ED1-11D1-AC54-00A0C94A8147}\TypeLib; ValueType: string; ValueData: {{CBE51AA8-A410-11D1-80D0-006097C9987D}; Components: VisualCpp\CeTools
Root: HKLM; Subkey: SOFTWARE\Classes\CLSID\{{2E338C78-8ED1-11D1-AC54-00A0C94A8147}\VERSION; ValueType: string; ValueData: 1.0; Components: VisualCpp\CeTools

Root: HKLM; Subkey: SOFTWARE\Classes\CLSID\{{2E338C79-8ED1-11D1-AC54-00A0C94A8147}; ValueType: string; ValueData: VIWFrame.CHTMLStream; Components: VisualCpp\CeTools
Root: HKLM; Subkey: SOFTWARE\Classes\CLSID\{{2E338C79-8ED1-11D1-AC54-00A0C94A8147}\Implemented Categories; Components: VisualCpp\CeTools
Root: HKLM; Subkey: SOFTWARE\Classes\CLSID\{{2E338C79-8ED1-11D1-AC54-00A0C94A8147}\Implemented Categories\{{40FC6ED5-2438-11CF-A3DB-080036F12502}; Components: VisualCpp\CeTools
Root: HKLM; Subkey: SOFTWARE\Classes\CLSID\{{2E338C79-8ED1-11D1-AC54-00A0C94A8147}\InprocServer32; ValueType: string; ValueData: {cf}\Microsoft Shared\Wizards98\VIWZRT.DLL; Components: VisualCpp\CeTools
Root: HKLM; Subkey: SOFTWARE\Classes\CLSID\{{2E338C79-8ED1-11D1-AC54-00A0C94A8147}\ProgID; ValueType: string; ValueData: VIWFrame.CHTMLStream; Components: VisualCpp\CeTools
Root: HKLM; Subkey: SOFTWARE\Classes\CLSID\{{2E338C79-8ED1-11D1-AC54-00A0C94A8147}\Programmable; Components: VisualCpp\CeTools
Root: HKLM; Subkey: SOFTWARE\Classes\CLSID\{{2E338C79-8ED1-11D1-AC54-00A0C94A8147}\TypeLib; ValueType: string; ValueData: {{CBE51AA8-A410-11D1-80D0-006097C9987D}; Components: VisualCpp\CeTools
Root: HKLM; Subkey: SOFTWARE\Classes\CLSID\{{2E338C79-8ED1-11D1-AC54-00A0C94A8147}\VERSION; ValueType: string; ValueData: 1.0; Components: VisualCpp\CeTools

Root: HKLM; Subkey: SOFTWARE\Classes\CLSID\{{2E338C7A-8ED1-11D1-AC54-00A0C94A8147}; ValueType: string; ValueData: VIWFrame.CHTMLStreams; Components: VisualCpp\CeTools
Root: HKLM; Subkey: SOFTWARE\Classes\CLSID\{{2E338C7A-8ED1-11D1-AC54-00A0C94A8147}\Implemented Categories; Components: VisualCpp\CeTools
Root: HKLM; Subkey: SOFTWARE\Classes\CLSID\{{2E338C7A-8ED1-11D1-AC54-00A0C94A8147}\Implemented Categories\{{40FC6ED5-2438-11CF-A3DB-080036F12502}; Components: VisualCpp\CeTools
Root: HKLM; Subkey: SOFTWARE\Classes\CLSID\{{2E338C7A-8ED1-11D1-AC54-00A0C94A8147}\InprocServer32; ValueType: string; ValueData: {cf}\Microsoft Shared\Wizards98\VIWZRT.DLL; Components: VisualCpp\CeTools
Root: HKLM; Subkey: SOFTWARE\Classes\CLSID\{{2E338C7A-8ED1-11D1-AC54-00A0C94A8147}\ProgID; ValueType: string; ValueData: VIWFrame.CHTMLStreams; Components: VisualCpp\CeTools
Root: HKLM; Subkey: SOFTWARE\Classes\CLSID\{{2E338C7A-8ED1-11D1-AC54-00A0C94A8147}\Programmable; Components: VisualCpp\CeTools
Root: HKLM; Subkey: SOFTWARE\Classes\CLSID\{{2E338C7A-8ED1-11D1-AC54-00A0C94A8147}\TypeLib; ValueType: string; ValueData: {{CBE51AA8-A410-11D1-80D0-006097C9987D}; Components: VisualCpp\CeTools
Root: HKLM; Subkey: SOFTWARE\Classes\CLSID\{{2E338C7A-8ED1-11D1-AC54-00A0C94A8147}\VERSION; ValueType: string; ValueData: 1.0; Components: VisualCpp\CeTools

Root: HKLM; Subkey: SOFTWARE\Classes\CLSID\{{2E338C7B-8ED1-11D1-AC54-00A0C94A8147}; ValueType: string; ValueData: VIWFrame.CImage; Components: VisualCpp\CeTools
Root: HKLM; Subkey: SOFTWARE\Classes\CLSID\{{2E338C7B-8ED1-11D1-AC54-00A0C94A8147}\Implemented Categories; Components: VisualCpp\CeTools
Root: HKLM; Subkey: SOFTWARE\Classes\CLSID\{{2E338C7B-8ED1-11D1-AC54-00A0C94A8147}\Implemented Categories\{{40FC6ED5-2438-11CF-A3DB-080036F12502}; Components: VisualCpp\CeTools
Root: HKLM; Subkey: SOFTWARE\Classes\CLSID\{{2E338C7B-8ED1-11D1-AC54-00A0C94A8147}\InprocServer32; ValueType: string; ValueData: {cf}\Microsoft Shared\Wizards98\VIWZRT.DLL; Components: VisualCpp\CeTools
Root: HKLM; Subkey: SOFTWARE\Classes\CLSID\{{2E338C7B-8ED1-11D1-AC54-00A0C94A8147}\ProgID; ValueType: string; ValueData: VIWFrame.CImage; Components: VisualCpp\CeTools
Root: HKLM; Subkey: SOFTWARE\Classes\CLSID\{{2E338C7B-8ED1-11D1-AC54-00A0C94A8147}\Programmable; Components: VisualCpp\CeTools
Root: HKLM; Subkey: SOFTWARE\Classes\CLSID\{{2E338C7B-8ED1-11D1-AC54-00A0C94A8147}\TypeLib; ValueType: string; ValueData: {{CBE51AA8-A410-11D1-80D0-006097C9987D}; Components: VisualCpp\CeTools
Root: HKLM; Subkey: SOFTWARE\Classes\CLSID\{{2E338C7B-8ED1-11D1-AC54-00A0C94A8147}\VERSION; ValueType: string; ValueData: 1.0; Components: VisualCpp\CeTools

Root: HKLM; Subkey: SOFTWARE\Classes\CLSID\{{2E338C7C-8ED1-11D1-AC54-00A0C94A8147}; ValueType: string; ValueData: VIWFrame.CImages; Components: VisualCpp\CeTools
Root: HKLM; Subkey: SOFTWARE\Classes\CLSID\{{2E338C7C-8ED1-11D1-AC54-00A0C94A8147}\Implemented Categories; Components: VisualCpp\CeTools
Root: HKLM; Subkey: SOFTWARE\Classes\CLSID\{{2E338C7C-8ED1-11D1-AC54-00A0C94A8147}\Implemented Categories\{{40FC6ED5-2438-11CF-A3DB-080036F12502}; Components: VisualCpp\CeTools
Root: HKLM; Subkey: SOFTWARE\Classes\CLSID\{{2E338C7C-8ED1-11D1-AC54-00A0C94A8147}\InprocServer32; ValueType: string; ValueData: {cf}\Microsoft Shared\Wizards98\VIWZRT.DLL; Components: VisualCpp\CeTools
Root: HKLM; Subkey: SOFTWARE\Classes\CLSID\{{2E338C7C-8ED1-11D1-AC54-00A0C94A8147}\ProgID; ValueType: string; ValueData: VIWFrame.CImages; Components: VisualCpp\CeTools
Root: HKLM; Subkey: SOFTWARE\Classes\CLSID\{{2E338C7C-8ED1-11D1-AC54-00A0C94A8147}\Programmable; Components: VisualCpp\CeTools
Root: HKLM; Subkey: SOFTWARE\Classes\CLSID\{{2E338C7C-8ED1-11D1-AC54-00A0C94A8147}\TypeLib; ValueType: string; ValueData: {{CBE51AA8-A410-11D1-80D0-006097C9987D}; Components: VisualCpp\CeTools
Root: HKLM; Subkey: SOFTWARE\Classes\CLSID\{{2E338C7C-8ED1-11D1-AC54-00A0C94A8147}\VERSION; ValueType: string; ValueData: 1.0; Components: VisualCpp\CeTools

Root: HKLM; Subkey: SOFTWARE\Classes\CLSID\{{2E338C7D-8ED1-11D1-AC54-00A0C94A8147}; ValueType: string; ValueData: VIWFrame.CMultiPick; Components: VisualCpp\CeTools
Root: HKLM; Subkey: SOFTWARE\Classes\CLSID\{{2E338C7D-8ED1-11D1-AC54-00A0C94A8147}\Implemented Categories; Components: VisualCpp\CeTools
Root: HKLM; Subkey: SOFTWARE\Classes\CLSID\{{2E338C7D-8ED1-11D1-AC54-00A0C94A8147}\Implemented Categories\{{40FC6ED5-2438-11CF-A3DB-080036F12502}; Components: VisualCpp\CeTools
Root: HKLM; Subkey: SOFTWARE\Classes\CLSID\{{2E338C7D-8ED1-11D1-AC54-00A0C94A8147}\InprocServer32; ValueType: string; ValueData: {cf}\Microsoft Shared\Wizards98\VIWZRT.DLL; Components: VisualCpp\CeTools
Root: HKLM; Subkey: SOFTWARE\Classes\CLSID\{{2E338C7D-8ED1-11D1-AC54-00A0C94A8147}\ProgID; ValueType: string; ValueData: VIWFrame.CMultiPick; Components: VisualCpp\CeTools
Root: HKLM; Subkey: SOFTWARE\Classes\CLSID\{{2E338C7D-8ED1-11D1-AC54-00A0C94A8147}\Programmable; Components: VisualCpp\CeTools
Root: HKLM; Subkey: SOFTWARE\Classes\CLSID\{{2E338C7D-8ED1-11D1-AC54-00A0C94A8147}\TypeLib; ValueType: string; ValueData: {{CBE51AA8-A410-11D1-80D0-006097C9987D}; Components: VisualCpp\CeTools
Root: HKLM; Subkey: SOFTWARE\Classes\CLSID\{{2E338C7D-8ED1-11D1-AC54-00A0C94A8147}\VERSION; ValueType: string; ValueData: 1.0; Components: VisualCpp\CeTools

Root: HKLM; Subkey: SOFTWARE\Classes\CLSID\{{2E338C7E-8ED1-11D1-AC54-00A0C94A8147}; ValueType: string; ValueData: VIWFrame.CNavigation; Components: VisualCpp\CeTools
Root: HKLM; Subkey: SOFTWARE\Classes\CLSID\{{2E338C7E-8ED1-11D1-AC54-00A0C94A8147}\Implemented Categories; Components: VisualCpp\CeTools
Root: HKLM; Subkey: SOFTWARE\Classes\CLSID\{{2E338C7E-8ED1-11D1-AC54-00A0C94A8147}\Implemented Categories\{{40FC6ED5-2438-11CF-A3DB-080036F12502}; Components: VisualCpp\CeTools
Root: HKLM; Subkey: SOFTWARE\Classes\CLSID\{{2E338C7E-8ED1-11D1-AC54-00A0C94A8147}\InprocServer32; ValueType: string; ValueData: {cf}\Microsoft Shared\Wizards98\VIWZRT.DLL; Components: VisualCpp\CeTools
Root: HKLM; Subkey: SOFTWARE\Classes\CLSID\{{2E338C7E-8ED1-11D1-AC54-00A0C94A8147}\ProgID; ValueType: string; ValueData: VIWFrame.CNavigation; Components: VisualCpp\CeTools
Root: HKLM; Subkey: SOFTWARE\Classes\CLSID\{{2E338C7E-8ED1-11D1-AC54-00A0C94A8147}\Programmable; Components: VisualCpp\CeTools
Root: HKLM; Subkey: SOFTWARE\Classes\CLSID\{{2E338C7E-8ED1-11D1-AC54-00A0C94A8147}\TypeLib; ValueType: string; ValueData: {{CBE51AA8-A410-11D1-80D0-006097C9987D}; Components: VisualCpp\CeTools
Root: HKLM; Subkey: SOFTWARE\Classes\CLSID\{{2E338C7E-8ED1-11D1-AC54-00A0C94A8147}\VERSION; ValueType: string; ValueData: 1.0; Components: VisualCpp\CeTools

Root: HKLM; Subkey: SOFTWARE\Classes\CLSID\{{2E338C7F-8ED1-11D1-AC54-00A0C94A8147}; ValueType: string; ValueData: VIWFrame.CNavInfo; Components: VisualCpp\CeTools
Root: HKLM; Subkey: SOFTWARE\Classes\CLSID\{{2E338C7F-8ED1-11D1-AC54-00A0C94A8147}\Implemented Categories; Components: VisualCpp\CeTools
Root: HKLM; Subkey: SOFTWARE\Classes\CLSID\{{2E338C7F-8ED1-11D1-AC54-00A0C94A8147}\Implemented Categories\{{40FC6ED5-2438-11CF-A3DB-080036F12502}; Components: VisualCpp\CeTools
Root: HKLM; Subkey: SOFTWARE\Classes\CLSID\{{2E338C7F-8ED1-11D1-AC54-00A0C94A8147}\InprocServer32; ValueType: string; ValueData: {cf}\Microsoft Shared\Wizards98\VIWZRT.DLL; Components: VisualCpp\CeTools
Root: HKLM; Subkey: SOFTWARE\Classes\CLSID\{{2E338C7F-8ED1-11D1-AC54-00A0C94A8147}\ProgID; ValueType: string; ValueData: VIWFrame.CNavInfo; Components: VisualCpp\CeTools
Root: HKLM; Subkey: SOFTWARE\Classes\CLSID\{{2E338C7F-8ED1-11D1-AC54-00A0C94A8147}\Programmable; Components: VisualCpp\CeTools
Root: HKLM; Subkey: SOFTWARE\Classes\CLSID\{{2E338C7F-8ED1-11D1-AC54-00A0C94A8147}\TypeLib; ValueType: string; ValueData: {{CBE51AA8-A410-11D1-80D0-006097C9987D}; Components: VisualCpp\CeTools
Root: HKLM; Subkey: SOFTWARE\Classes\CLSID\{{2E338C7F-8ED1-11D1-AC54-00A0C94A8147}\VERSION; ValueType: string; ValueData: 1.0; Components: VisualCpp\CeTools

Root: HKLM; Subkey: SOFTWARE\Classes\CLSID\{{2E338C80-8ED1-11D1-AC54-00A0C94A8147}; ValueType: string; ValueData: VIWFrame.CODBCConnection; Components: VisualCpp\CeTools
Root: HKLM; Subkey: SOFTWARE\Classes\CLSID\{{2E338C80-8ED1-11D1-AC54-00A0C94A8147}\Implemented Categories; Components: VisualCpp\CeTools
Root: HKLM; Subkey: SOFTWARE\Classes\CLSID\{{2E338C80-8ED1-11D1-AC54-00A0C94A8147}\Implemented Categories\{{40FC6ED5-2438-11CF-A3DB-080036F12502}; Components: VisualCpp\CeTools
Root: HKLM; Subkey: SOFTWARE\Classes\CLSID\{{2E338C80-8ED1-11D1-AC54-00A0C94A8147}\InprocServer32; ValueType: string; ValueData: {cf}\Microsoft Shared\Wizards98\VIWZRT.DLL; Components: VisualCpp\CeTools
Root: HKLM; Subkey: SOFTWARE\Classes\CLSID\{{2E338C80-8ED1-11D1-AC54-00A0C94A8147}\ProgID; ValueType: string; ValueData: VIWFrame.CODBCConnection; Components: VisualCpp\CeTools
Root: HKLM; Subkey: SOFTWARE\Classes\CLSID\{{2E338C80-8ED1-11D1-AC54-00A0C94A8147}\Programmable; Components: VisualCpp\CeTools
Root: HKLM; Subkey: SOFTWARE\Classes\CLSID\{{2E338C80-8ED1-11D1-AC54-00A0C94A8147}\TypeLib; ValueType: string; ValueData: {{CBE51AA8-A410-11D1-80D0-006097C9987D}; Components: VisualCpp\CeTools
Root: HKLM; Subkey: SOFTWARE\Classes\CLSID\{{2E338C80-8ED1-11D1-AC54-00A0C94A8147}\VERSION; ValueType: string; ValueData: 1.0; Components: VisualCpp\CeTools

Root: HKLM; Subkey: SOFTWARE\Classes\CLSID\{{2E338C81-8ED1-11D1-AC54-00A0C94A8147}; ValueType: string; ValueData: VIWFrame.CReplacement; Components: VisualCpp\CeTools
Root: HKLM; Subkey: SOFTWARE\Classes\CLSID\{{2E338C81-8ED1-11D1-AC54-00A0C94A8147}\Implemented Categories; Components: VisualCpp\CeTools
Root: HKLM; Subkey: SOFTWARE\Classes\CLSID\{{2E338C81-8ED1-11D1-AC54-00A0C94A8147}\Implemented Categories\{{40FC6ED5-2438-11CF-A3DB-080036F12502}; Components: VisualCpp\CeTools
Root: HKLM; Subkey: SOFTWARE\Classes\CLSID\{{2E338C81-8ED1-11D1-AC54-00A0C94A8147}\InprocServer32; ValueType: string; ValueData: {cf}\Microsoft Shared\Wizards98\VIWZRT.DLL; Components: VisualCpp\CeTools
Root: HKLM; Subkey: SOFTWARE\Classes\CLSID\{{2E338C81-8ED1-11D1-AC54-00A0C94A8147}\ProgID; ValueType: string; ValueData: VIWFrame.CReplacement; Components: VisualCpp\CeTools
Root: HKLM; Subkey: SOFTWARE\Classes\CLSID\{{2E338C81-8ED1-11D1-AC54-00A0C94A8147}\Programmable; Components: VisualCpp\CeTools
Root: HKLM; Subkey: SOFTWARE\Classes\CLSID\{{2E338C81-8ED1-11D1-AC54-00A0C94A8147}\TypeLib; ValueType: string; ValueData: {{CBE51AA8-A410-11D1-80D0-006097C9987D}; Components: VisualCpp\CeTools
Root: HKLM; Subkey: SOFTWARE\Classes\CLSID\{{2E338C81-8ED1-11D1-AC54-00A0C94A8147}\VERSION; ValueType: string; ValueData: 1.0; Components: VisualCpp\CeTools

Root: HKLM; Subkey: SOFTWARE\Classes\CLSID\{{2E338C82-8ED1-11D1-AC54-00A0C94A8147}; ValueType: string; ValueData: VIWFrame.CReplacements; Components: VisualCpp\CeTools
Root: HKLM; Subkey: SOFTWARE\Classes\CLSID\{{2E338C82-8ED1-11D1-AC54-00A0C94A8147}\Implemented Categories; Components: VisualCpp\CeTools
Root: HKLM; Subkey: SOFTWARE\Classes\CLSID\{{2E338C82-8ED1-11D1-AC54-00A0C94A8147}\Implemented Categories\{{40FC6ED5-2438-11CF-A3DB-080036F12502}; Components: VisualCpp\CeTools
Root: HKLM; Subkey: SOFTWARE\Classes\CLSID\{{2E338C82-8ED1-11D1-AC54-00A0C94A8147}\InprocServer32; ValueType: string; ValueData: {cf}\Microsoft Shared\Wizards98\VIWZRT.DLL; Components: VisualCpp\CeTools
Root: HKLM; Subkey: SOFTWARE\Classes\CLSID\{{2E338C82-8ED1-11D1-AC54-00A0C94A8147}\ProgID; ValueType: string; ValueData: VIWFrame.CReplacements; Components: VisualCpp\CeTools
Root: HKLM; Subkey: SOFTWARE\Classes\CLSID\{{2E338C82-8ED1-11D1-AC54-00A0C94A8147}\Programmable; Components: VisualCpp\CeTools
Root: HKLM; Subkey: SOFTWARE\Classes\CLSID\{{2E338C82-8ED1-11D1-AC54-00A0C94A8147}\TypeLib; ValueType: string; ValueData: {{CBE51AA8-A410-11D1-80D0-006097C9987D}; Components: VisualCpp\CeTools
Root: HKLM; Subkey: SOFTWARE\Classes\CLSID\{{2E338C82-8ED1-11D1-AC54-00A0C94A8147}\VERSION; ValueType: string; ValueData: 1.0; Components: VisualCpp\CeTools

Root: HKLM; Subkey: SOFTWARE\Classes\CLSID\{{2E338C83-8ED1-11D1-AC54-00A0C94A8147}; ValueType: string; ValueData: VIWFrame.CServerForms; Components: VisualCpp\CeTools
Root: HKLM; Subkey: SOFTWARE\Classes\CLSID\{{2E338C83-8ED1-11D1-AC54-00A0C94A8147}\Implemented Categories; Components: VisualCpp\CeTools
Root: HKLM; Subkey: SOFTWARE\Classes\CLSID\{{2E338C83-8ED1-11D1-AC54-00A0C94A8147}\Implemented Categories\{{40FC6ED5-2438-11CF-A3DB-080036F12502}; Components: VisualCpp\CeTools
Root: HKLM; Subkey: SOFTWARE\Classes\CLSID\{{2E338C83-8ED1-11D1-AC54-00A0C94A8147}\InprocServer32; ValueType: string; ValueData: {cf}\Microsoft Shared\Wizards98\VIWZRT.DLL; Components: VisualCpp\CeTools
Root: HKLM; Subkey: SOFTWARE\Classes\CLSID\{{2E338C83-8ED1-11D1-AC54-00A0C94A8147}\ProgID; ValueType: string; ValueData: VIWFrame.CServerForms; Components: VisualCpp\CeTools
Root: HKLM; Subkey: SOFTWARE\Classes\CLSID\{{2E338C83-8ED1-11D1-AC54-00A0C94A8147}\Programmable; Components: VisualCpp\CeTools
Root: HKLM; Subkey: SOFTWARE\Classes\CLSID\{{2E338C83-8ED1-11D1-AC54-00A0C94A8147}\TypeLib; ValueType: string; ValueData: {{CBE51AA8-A410-11D1-80D0-006097C9987D}; Components: VisualCpp\CeTools
Root: HKLM; Subkey: SOFTWARE\Classes\CLSID\{{2E338C83-8ED1-11D1-AC54-00A0C94A8147}\VERSION; ValueType: string; ValueData: 1.0; Components: VisualCpp\CeTools

Root: HKLM; Subkey: SOFTWARE\Classes\CLSID\{{2E338C84-8ED1-11D1-AC54-00A0C94A8147}; ValueType: string; ValueData: VIWFrame.CStdError; Components: VisualCpp\CeTools
Root: HKLM; Subkey: SOFTWARE\Classes\CLSID\{{2E338C84-8ED1-11D1-AC54-00A0C94A8147}\Implemented Categories; Components: VisualCpp\CeTools
Root: HKLM; Subkey: SOFTWARE\Classes\CLSID\{{2E338C84-8ED1-11D1-AC54-00A0C94A8147}\Implemented Categories\{{40FC6ED5-2438-11CF-A3DB-080036F12502}; Components: VisualCpp\CeTools
Root: HKLM; Subkey: SOFTWARE\Classes\CLSID\{{2E338C84-8ED1-11D1-AC54-00A0C94A8147}\InprocServer32; ValueType: string; ValueData: {cf}\Microsoft Shared\Wizards98\VIWZRT.DLL; Components: VisualCpp\CeTools
Root: HKLM; Subkey: SOFTWARE\Classes\CLSID\{{2E338C84-8ED1-11D1-AC54-00A0C94A8147}\ProgID; ValueType: string; ValueData: VIWFrame.CStdError; Components: VisualCpp\CeTools
Root: HKLM; Subkey: SOFTWARE\Classes\CLSID\{{2E338C84-8ED1-11D1-AC54-00A0C94A8147}\Programmable; Components: VisualCpp\CeTools
Root: HKLM; Subkey: SOFTWARE\Classes\CLSID\{{2E338C84-8ED1-11D1-AC54-00A0C94A8147}\TypeLib; ValueType: string; ValueData: {{CBE51AA8-A410-11D1-80D0-006097C9987D}; Components: VisualCpp\CeTools
Root: HKLM; Subkey: SOFTWARE\Classes\CLSID\{{2E338C84-8ED1-11D1-AC54-00A0C94A8147}\VERSION; ValueType: string; ValueData: 1.0; Components: VisualCpp\CeTools

Root: HKLM; Subkey: SOFTWARE\Classes\CLSID\{{2E338C85-8ED1-11D1-AC54-00A0C94A8147}; ValueType: string; ValueData: VIWFrame.CStdErrors; Components: VisualCpp\CeTools
Root: HKLM; Subkey: SOFTWARE\Classes\CLSID\{{2E338C85-8ED1-11D1-AC54-00A0C94A8147}\Implemented Categories; Components: VisualCpp\CeTools
Root: HKLM; Subkey: SOFTWARE\Classes\CLSID\{{2E338C85-8ED1-11D1-AC54-00A0C94A8147}\Implemented Categories\{{40FC6ED5-2438-11CF-A3DB-080036F12502}; Components: VisualCpp\CeTools
Root: HKLM; Subkey: SOFTWARE\Classes\CLSID\{{2E338C85-8ED1-11D1-AC54-00A0C94A8147}\InprocServer32; ValueType: string; ValueData: {cf}\Microsoft Shared\Wizards98\VIWZRT.DLL; Components: VisualCpp\CeTools
Root: HKLM; Subkey: SOFTWARE\Classes\CLSID\{{2E338C85-8ED1-11D1-AC54-00A0C94A8147}\ProgID; ValueType: string; ValueData: VIWFrame.CStdErrors; Components: VisualCpp\CeTools
Root: HKLM; Subkey: SOFTWARE\Classes\CLSID\{{2E338C85-8ED1-11D1-AC54-00A0C94A8147}\Programmable; Components: VisualCpp\CeTools
Root: HKLM; Subkey: SOFTWARE\Classes\CLSID\{{2E338C85-8ED1-11D1-AC54-00A0C94A8147}\TypeLib; ValueType: string; ValueData: {{CBE51AA8-A410-11D1-80D0-006097C9987D}; Components: VisualCpp\CeTools
Root: HKLM; Subkey: SOFTWARE\Classes\CLSID\{{2E338C85-8ED1-11D1-AC54-00A0C94A8147}\VERSION; ValueType: string; ValueData: 1.0; Components: VisualCpp\CeTools

Root: HKLM; Subkey: SOFTWARE\Classes\CLSID\{{2E338C86-8ED1-11D1-AC54-00A0C94A8147}; ValueType: string; ValueData: VIWFrame.CString; Components: VisualCpp\CeTools
Root: HKLM; Subkey: SOFTWARE\Classes\CLSID\{{2E338C86-8ED1-11D1-AC54-00A0C94A8147}\Implemented Categories; Components: VisualCpp\CeTools
Root: HKLM; Subkey: SOFTWARE\Classes\CLSID\{{2E338C86-8ED1-11D1-AC54-00A0C94A8147}\Implemented Categories\{{40FC6ED5-2438-11CF-A3DB-080036F12502}; Components: VisualCpp\CeTools
Root: HKLM; Subkey: SOFTWARE\Classes\CLSID\{{2E338C86-8ED1-11D1-AC54-00A0C94A8147}\InprocServer32; ValueType: string; ValueData: {cf}\Microsoft Shared\Wizards98\VIWZRT.DLL; Components: VisualCpp\CeTools
Root: HKLM; Subkey: SOFTWARE\Classes\CLSID\{{2E338C86-8ED1-11D1-AC54-00A0C94A8147}\ProgID; ValueType: string; ValueData: VIWFrame.CString; Components: VisualCpp\CeTools
Root: HKLM; Subkey: SOFTWARE\Classes\CLSID\{{2E338C86-8ED1-11D1-AC54-00A0C94A8147}\Programmable; Components: VisualCpp\CeTools
Root: HKLM; Subkey: SOFTWARE\Classes\CLSID\{{2E338C86-8ED1-11D1-AC54-00A0C94A8147}\TypeLib; ValueType: string; ValueData: {{CBE51AA8-A410-11D1-80D0-006097C9987D}; Components: VisualCpp\CeTools
Root: HKLM; Subkey: SOFTWARE\Classes\CLSID\{{2E338C86-8ED1-11D1-AC54-00A0C94A8147}\VERSION; ValueType: string; ValueData: 1.0; Components: VisualCpp\CeTools

Root: HKLM; Subkey: SOFTWARE\Classes\CLSID\{{2E338C87-8ED1-11D1-AC54-00A0C94A8147}; ValueType: string; ValueData: VIWFrame.CStrings; Components: VisualCpp\CeTools
Root: HKLM; Subkey: SOFTWARE\Classes\CLSID\{{2E338C87-8ED1-11D1-AC54-00A0C94A8147}\Implemented Categories; Components: VisualCpp\CeTools
Root: HKLM; Subkey: SOFTWARE\Classes\CLSID\{{2E338C87-8ED1-11D1-AC54-00A0C94A8147}\Implemented Categories\{{40FC6ED5-2438-11CF-A3DB-080036F12502}; Components: VisualCpp\CeTools
Root: HKLM; Subkey: SOFTWARE\Classes\CLSID\{{2E338C87-8ED1-11D1-AC54-00A0C94A8147}\InprocServer32; ValueType: string; ValueData: {cf}\Microsoft Shared\Wizards98\VIWZRT.DLL; Components: VisualCpp\CeTools
Root: HKLM; Subkey: SOFTWARE\Classes\CLSID\{{2E338C87-8ED1-11D1-AC54-00A0C94A8147}\ProgID; ValueType: string; ValueData: VIWFrame.CStrings; Components: VisualCpp\CeTools
Root: HKLM; Subkey: SOFTWARE\Classes\CLSID\{{2E338C87-8ED1-11D1-AC54-00A0C94A8147}\Programmable; Components: VisualCpp\CeTools
Root: HKLM; Subkey: SOFTWARE\Classes\CLSID\{{2E338C87-8ED1-11D1-AC54-00A0C94A8147}\TypeLib; ValueType: string; ValueData: {{CBE51AA8-A410-11D1-80D0-006097C9987D}; Components: VisualCpp\CeTools
Root: HKLM; Subkey: SOFTWARE\Classes\CLSID\{{2E338C87-8ED1-11D1-AC54-00A0C94A8147}\VERSION; ValueType: string; ValueData: 1.0; Components: VisualCpp\CeTools

Root: HKLM; Subkey: SOFTWARE\Classes\CLSID\{{2E338C88-8ED1-11D1-AC54-00A0C94A8147}; ValueType: string; ValueData: VIWFrame.CTable; Components: VisualCpp\CeTools
Root: HKLM; Subkey: SOFTWARE\Classes\CLSID\{{2E338C88-8ED1-11D1-AC54-00A0C94A8147}\Implemented Categories; Components: VisualCpp\CeTools
Root: HKLM; Subkey: SOFTWARE\Classes\CLSID\{{2E338C88-8ED1-11D1-AC54-00A0C94A8147}\Implemented Categories\{{40FC6ED5-2438-11CF-A3DB-080036F12502}; Components: VisualCpp\CeTools
Root: HKLM; Subkey: SOFTWARE\Classes\CLSID\{{2E338C88-8ED1-11D1-AC54-00A0C94A8147}\InprocServer32; ValueType: string; ValueData: {cf}\Microsoft Shared\Wizards98\VIWZRT.DLL; Components: VisualCpp\CeTools
Root: HKLM; Subkey: SOFTWARE\Classes\CLSID\{{2E338C88-8ED1-11D1-AC54-00A0C94A8147}\ProgID; ValueType: string; ValueData: VIWFrame.CTable; Components: VisualCpp\CeTools
Root: HKLM; Subkey: SOFTWARE\Classes\CLSID\{{2E338C88-8ED1-11D1-AC54-00A0C94A8147}\Programmable; Components: VisualCpp\CeTools
Root: HKLM; Subkey: SOFTWARE\Classes\CLSID\{{2E338C88-8ED1-11D1-AC54-00A0C94A8147}\TypeLib; ValueType: string; ValueData: {{CBE51AA8-A410-11D1-80D0-006097C9987D}; Components: VisualCpp\CeTools
Root: HKLM; Subkey: SOFTWARE\Classes\CLSID\{{2E338C88-8ED1-11D1-AC54-00A0C94A8147}\VERSION; ValueType: string; ValueData: 1.0; Components: VisualCpp\CeTools

Root: HKLM; Subkey: SOFTWARE\Classes\CLSID\{{2E338C89-8ED1-11D1-AC54-00A0C94A8147}; ValueType: string; ValueData: VIWFrame.CTables; Components: VisualCpp\CeTools
Root: HKLM; Subkey: SOFTWARE\Classes\CLSID\{{2E338C89-8ED1-11D1-AC54-00A0C94A8147}\Implemented Categories; Components: VisualCpp\CeTools
Root: HKLM; Subkey: SOFTWARE\Classes\CLSID\{{2E338C89-8ED1-11D1-AC54-00A0C94A8147}\Implemented Categories\{{40FC6ED5-2438-11CF-A3DB-080036F12502}; Components: VisualCpp\CeTools
Root: HKLM; Subkey: SOFTWARE\Classes\CLSID\{{2E338C89-8ED1-11D1-AC54-00A0C94A8147}\InprocServer32; ValueType: string; ValueData: {cf}\Microsoft Shared\Wizards98\VIWZRT.DLL; Components: VisualCpp\CeTools
Root: HKLM; Subkey: SOFTWARE\Classes\CLSID\{{2E338C89-8ED1-11D1-AC54-00A0C94A8147}\ProgID; ValueType: string; ValueData: VIWFrame.CTables; Components: VisualCpp\CeTools
Root: HKLM; Subkey: SOFTWARE\Classes\CLSID\{{2E338C89-8ED1-11D1-AC54-00A0C94A8147}\Programmable; Components: VisualCpp\CeTools
Root: HKLM; Subkey: SOFTWARE\Classes\CLSID\{{2E338C89-8ED1-11D1-AC54-00A0C94A8147}\TypeLib; ValueType: string; ValueData: {{CBE51AA8-A410-11D1-80D0-006097C9987D}; Components: VisualCpp\CeTools
Root: HKLM; Subkey: SOFTWARE\Classes\CLSID\{{2E338C89-8ED1-11D1-AC54-00A0C94A8147}\VERSION; ValueType: string; ValueData: 1.0; Components: VisualCpp\CeTools

Root: HKLM; Subkey: SOFTWARE\Classes\CLSID\{{2E338C8A-8ED1-11D1-AC54-00A0C94A8147}; ValueType: string; ValueData: VIWFrame.CTemplate; Components: VisualCpp\CeTools
Root: HKLM; Subkey: SOFTWARE\Classes\CLSID\{{2E338C8A-8ED1-11D1-AC54-00A0C94A8147}\Implemented Categories; Components: VisualCpp\CeTools
Root: HKLM; Subkey: SOFTWARE\Classes\CLSID\{{2E338C8A-8ED1-11D1-AC54-00A0C94A8147}\Implemented Categories\{{40FC6ED5-2438-11CF-A3DB-080036F12502}; Components: VisualCpp\CeTools
Root: HKLM; Subkey: SOFTWARE\Classes\CLSID\{{2E338C8A-8ED1-11D1-AC54-00A0C94A8147}\InprocServer32; ValueType: string; ValueData: {cf}\Microsoft Shared\Wizards98\VIWZRT.DLL; Components: VisualCpp\CeTools
Root: HKLM; Subkey: SOFTWARE\Classes\CLSID\{{2E338C8A-8ED1-11D1-AC54-00A0C94A8147}\ProgID; ValueType: string; ValueData: VIWFrame.CTemplate; Components: VisualCpp\CeTools
Root: HKLM; Subkey: SOFTWARE\Classes\CLSID\{{2E338C8A-8ED1-11D1-AC54-00A0C94A8147}\Programmable; Components: VisualCpp\CeTools
Root: HKLM; Subkey: SOFTWARE\Classes\CLSID\{{2E338C8A-8ED1-11D1-AC54-00A0C94A8147}\TypeLib; ValueType: string; ValueData: {{CBE51AA8-A410-11D1-80D0-006097C9987D}; Components: VisualCpp\CeTools
Root: HKLM; Subkey: SOFTWARE\Classes\CLSID\{{2E338C8A-8ED1-11D1-AC54-00A0C94A8147}\VERSION; ValueType: string; ValueData: 1.0; Components: VisualCpp\CeTools

Root: HKLM; Subkey: SOFTWARE\Classes\CLSID\{{2E338C8B-8ED1-11D1-AC54-00A0C94A8147}; ValueType: string; ValueData: VIWFrame.CTemplates; Components: VisualCpp\CeTools
Root: HKLM; Subkey: SOFTWARE\Classes\CLSID\{{2E338C8B-8ED1-11D1-AC54-00A0C94A8147}\Implemented Categories; Components: VisualCpp\CeTools
Root: HKLM; Subkey: SOFTWARE\Classes\CLSID\{{2E338C8B-8ED1-11D1-AC54-00A0C94A8147}\Implemented Categories\{{40FC6ED5-2438-11CF-A3DB-080036F12502}; Components: VisualCpp\CeTools
Root: HKLM; Subkey: SOFTWARE\Classes\CLSID\{{2E338C8B-8ED1-11D1-AC54-00A0C94A8147}\InprocServer32; ValueType: string; ValueData: {cf}\Microsoft Shared\Wizards98\VIWZRT.DLL; Components: VisualCpp\CeTools
Root: HKLM; Subkey: SOFTWARE\Classes\CLSID\{{2E338C8B-8ED1-11D1-AC54-00A0C94A8147}\ProgID; ValueType: string; ValueData: VIWFrame.CTemplates; Components: VisualCpp\CeTools
Root: HKLM; Subkey: SOFTWARE\Classes\CLSID\{{2E338C8B-8ED1-11D1-AC54-00A0C94A8147}\Programmable; Components: VisualCpp\CeTools
Root: HKLM; Subkey: SOFTWARE\Classes\CLSID\{{2E338C8B-8ED1-11D1-AC54-00A0C94A8147}\TypeLib; ValueType: string; ValueData: {{CBE51AA8-A410-11D1-80D0-006097C9987D}; Components: VisualCpp\CeTools
Root: HKLM; Subkey: SOFTWARE\Classes\CLSID\{{2E338C8B-8ED1-11D1-AC54-00A0C94A8147}\VERSION; ValueType: string; ValueData: 1.0; Components: VisualCpp\CeTools

Root: HKLM; Subkey: SOFTWARE\Classes\CLSID\{{2E338C8C-8ED1-11D1-AC54-00A0C94A8147}; ValueType: string; ValueData: VIWFrame.CTemplateType; Components: VisualCpp\CeTools
Root: HKLM; Subkey: SOFTWARE\Classes\CLSID\{{2E338C8C-8ED1-11D1-AC54-00A0C94A8147}\Implemented Categories; Components: VisualCpp\CeTools
Root: HKLM; Subkey: SOFTWARE\Classes\CLSID\{{2E338C8C-8ED1-11D1-AC54-00A0C94A8147}\Implemented Categories\{{40FC6ED5-2438-11CF-A3DB-080036F12502}; Components: VisualCpp\CeTools
Root: HKLM; Subkey: SOFTWARE\Classes\CLSID\{{2E338C8C-8ED1-11D1-AC54-00A0C94A8147}\InprocServer32; ValueType: string; ValueData: {cf}\Microsoft Shared\Wizards98\VIWZRT.DLL; Components: VisualCpp\CeTools
Root: HKLM; Subkey: SOFTWARE\Classes\CLSID\{{2E338C8C-8ED1-11D1-AC54-00A0C94A8147}\ProgID; ValueType: string; ValueData: VIWFrame.CTemplateType; Components: VisualCpp\CeTools
Root: HKLM; Subkey: SOFTWARE\Classes\CLSID\{{2E338C8C-8ED1-11D1-AC54-00A0C94A8147}\Programmable; Components: VisualCpp\CeTools
Root: HKLM; Subkey: SOFTWARE\Classes\CLSID\{{2E338C8C-8ED1-11D1-AC54-00A0C94A8147}\TypeLib; ValueType: string; ValueData: {{CBE51AA8-A410-11D1-80D0-006097C9987D}; Components: VisualCpp\CeTools
Root: HKLM; Subkey: SOFTWARE\Classes\CLSID\{{2E338C8C-8ED1-11D1-AC54-00A0C94A8147}\VERSION; ValueType: string; ValueData: 1.0; Components: VisualCpp\CeTools

Root: HKLM; Subkey: SOFTWARE\Classes\CLSID\{{2E338C8D-8ED1-11D1-AC54-00A0C94A8147}; ValueType: string; ValueData: VIWFrame.CTemplateTypes; Components: VisualCpp\CeTools
Root: HKLM; Subkey: SOFTWARE\Classes\CLSID\{{2E338C8D-8ED1-11D1-AC54-00A0C94A8147}\Implemented Categories; Components: VisualCpp\CeTools
Root: HKLM; Subkey: SOFTWARE\Classes\CLSID\{{2E338C8D-8ED1-11D1-AC54-00A0C94A8147}\Implemented Categories\{{40FC6ED5-2438-11CF-A3DB-080036F12502}; Components: VisualCpp\CeTools
Root: HKLM; Subkey: SOFTWARE\Classes\CLSID\{{2E338C8D-8ED1-11D1-AC54-00A0C94A8147}\InprocServer32; ValueType: string; ValueData: {cf}\Microsoft Shared\Wizards98\VIWZRT.DLL; Components: VisualCpp\CeTools
Root: HKLM; Subkey: SOFTWARE\Classes\CLSID\{{2E338C8D-8ED1-11D1-AC54-00A0C94A8147}\ProgID; ValueType: string; ValueData: VIWFrame.CTemplateTypes; Components: VisualCpp\CeTools
Root: HKLM; Subkey: SOFTWARE\Classes\CLSID\{{2E338C8D-8ED1-11D1-AC54-00A0C94A8147}\Programmable; Components: VisualCpp\CeTools
Root: HKLM; Subkey: SOFTWARE\Classes\CLSID\{{2E338C8D-8ED1-11D1-AC54-00A0C94A8147}\TypeLib; ValueType: string; ValueData: {{CBE51AA8-A410-11D1-80D0-006097C9987D}; Components: VisualCpp\CeTools
Root: HKLM; Subkey: SOFTWARE\Classes\CLSID\{{2E338C8D-8ED1-11D1-AC54-00A0C94A8147}\VERSION; ValueType: string; ValueData: 1.0; Components: VisualCpp\CeTools

Root: HKLM; Subkey: SOFTWARE\Classes\CLSID\{{2E338C8E-8ED1-11D1-AC54-00A0C94A8147}; ValueType: string; ValueData: VIWFrame.CTheme; Components: VisualCpp\CeTools
Root: HKLM; Subkey: SOFTWARE\Classes\CLSID\{{2E338C8E-8ED1-11D1-AC54-00A0C94A8147}\Implemented Categories; Components: VisualCpp\CeTools
Root: HKLM; Subkey: SOFTWARE\Classes\CLSID\{{2E338C8E-8ED1-11D1-AC54-00A0C94A8147}\Implemented Categories\{{40FC6ED5-2438-11CF-A3DB-080036F12502}; Components: VisualCpp\CeTools
Root: HKLM; Subkey: SOFTWARE\Classes\CLSID\{{2E338C8E-8ED1-11D1-AC54-00A0C94A8147}\InprocServer32; ValueType: string; ValueData: {cf}\Microsoft Shared\Wizards98\VIWZRT.DLL; Components: VisualCpp\CeTools
Root: HKLM; Subkey: SOFTWARE\Classes\CLSID\{{2E338C8E-8ED1-11D1-AC54-00A0C94A8147}\ProgID; ValueType: string; ValueData: VIWFrame.CTheme; Components: VisualCpp\CeTools
Root: HKLM; Subkey: SOFTWARE\Classes\CLSID\{{2E338C8E-8ED1-11D1-AC54-00A0C94A8147}\Programmable; Components: VisualCpp\CeTools
Root: HKLM; Subkey: SOFTWARE\Classes\CLSID\{{2E338C8E-8ED1-11D1-AC54-00A0C94A8147}\TypeLib; ValueType: string; ValueData: {{CBE51AA8-A410-11D1-80D0-006097C9987D}; Components: VisualCpp\CeTools
Root: HKLM; Subkey: SOFTWARE\Classes\CLSID\{{2E338C8E-8ED1-11D1-AC54-00A0C94A8147}\VERSION; ValueType: string; ValueData: 1.0; Components: VisualCpp\CeTools
Root: HKLM; Subkey: SOFTWARE\Classes\CLSID\{{2E338C8F-8ED1-11D1-AC54-00A0C94A8147}; ValueType: string; ValueData: VIWFrame.CThemes; Components: VisualCpp\CeTools

Root: HKLM; Subkey: SOFTWARE\Classes\CLSID\{{2E338C8F-8ED1-11D1-AC54-00A0C94A8147}\Implemented Categories; Components: VisualCpp\CeTools
Root: HKLM; Subkey: SOFTWARE\Classes\CLSID\{{2E338C8F-8ED1-11D1-AC54-00A0C94A8147}\Implemented Categories\{{40FC6ED5-2438-11CF-A3DB-080036F12502}; Components: VisualCpp\CeTools
Root: HKLM; Subkey: SOFTWARE\Classes\CLSID\{{2E338C8F-8ED1-11D1-AC54-00A0C94A8147}\InprocServer32; ValueType: string; ValueData: {cf}\Microsoft Shared\Wizards98\VIWZRT.DLL; Components: VisualCpp\CeTools
Root: HKLM; Subkey: SOFTWARE\Classes\CLSID\{{2E338C8F-8ED1-11D1-AC54-00A0C94A8147}\ProgID; ValueType: string; ValueData: VIWFrame.CThemes; Components: VisualCpp\CeTools
Root: HKLM; Subkey: SOFTWARE\Classes\CLSID\{{2E338C8F-8ED1-11D1-AC54-00A0C94A8147}\Programmable; Components: VisualCpp\CeTools
Root: HKLM; Subkey: SOFTWARE\Classes\CLSID\{{2E338C8F-8ED1-11D1-AC54-00A0C94A8147}\TypeLib; ValueType: string; ValueData: {{CBE51AA8-A410-11D1-80D0-006097C9987D}; Components: VisualCpp\CeTools
Root: HKLM; Subkey: SOFTWARE\Classes\CLSID\{{2E338C8F-8ED1-11D1-AC54-00A0C94A8147}\VERSION; ValueType: string; ValueData: 1.0; Components: VisualCpp\CeTools

Root: HKLM; Subkey: SOFTWARE\Classes\CLSID\{{2E338C90-8ED1-11D1-AC54-00A0C94A8147}; ValueType: string; ValueData: VIWFrame.CTreeview; Components: VisualCpp\CeTools
Root: HKLM; Subkey: SOFTWARE\Classes\CLSID\{{2E338C90-8ED1-11D1-AC54-00A0C94A8147}\Implemented Categories; Components: VisualCpp\CeTools
Root: HKLM; Subkey: SOFTWARE\Classes\CLSID\{{2E338C90-8ED1-11D1-AC54-00A0C94A8147}\Implemented Categories\{{40FC6ED5-2438-11CF-A3DB-080036F12502}; Components: VisualCpp\CeTools
Root: HKLM; Subkey: SOFTWARE\Classes\CLSID\{{2E338C90-8ED1-11D1-AC54-00A0C94A8147}\InprocServer32; ValueType: string; ValueData: {cf}\Microsoft Shared\Wizards98\VIWZRT.DLL; Components: VisualCpp\CeTools
Root: HKLM; Subkey: SOFTWARE\Classes\CLSID\{{2E338C90-8ED1-11D1-AC54-00A0C94A8147}\ProgID; ValueType: string; ValueData: VIWFrame.CTreeview; Components: VisualCpp\CeTools
Root: HKLM; Subkey: SOFTWARE\Classes\CLSID\{{2E338C90-8ED1-11D1-AC54-00A0C94A8147}\Programmable; Components: VisualCpp\CeTools
Root: HKLM; Subkey: SOFTWARE\Classes\CLSID\{{2E338C90-8ED1-11D1-AC54-00A0C94A8147}\TypeLib; ValueType: string; ValueData: {{CBE51AA8-A410-11D1-80D0-006097C9987D}; Components: VisualCpp\CeTools
Root: HKLM; Subkey: SOFTWARE\Classes\CLSID\{{2E338C90-8ED1-11D1-AC54-00A0C94A8147}\VERSION; ValueType: string; ValueData: 1.0; Components: VisualCpp\CeTools

Root: HKLM; Subkey: SOFTWARE\Classes\CLSID\{{2E338C91-8ED1-11D1-AC54-00A0C94A8147}; ValueType: string; ValueData: VIWFrame.CWebPage; Components: VisualCpp\CeTools
Root: HKLM; Subkey: SOFTWARE\Classes\CLSID\{{2E338C91-8ED1-11D1-AC54-00A0C94A8147}\Implemented Categories; Components: VisualCpp\CeTools
Root: HKLM; Subkey: SOFTWARE\Classes\CLSID\{{2E338C91-8ED1-11D1-AC54-00A0C94A8147}\Implemented Categories\{{40FC6ED5-2438-11CF-A3DB-080036F12502}; Components: VisualCpp\CeTools
Root: HKLM; Subkey: SOFTWARE\Classes\CLSID\{{2E338C91-8ED1-11D1-AC54-00A0C94A8147}\InprocServer32; ValueType: string; ValueData: {cf}\Microsoft Shared\Wizards98\VIWZRT.DLL; Components: VisualCpp\CeTools
Root: HKLM; Subkey: SOFTWARE\Classes\CLSID\{{2E338C91-8ED1-11D1-AC54-00A0C94A8147}\ProgID; ValueType: string; ValueData: VIWFrame.CWebPage; Components: VisualCpp\CeTools
Root: HKLM; Subkey: SOFTWARE\Classes\CLSID\{{2E338C91-8ED1-11D1-AC54-00A0C94A8147}\Programmable; Components: VisualCpp\CeTools
Root: HKLM; Subkey: SOFTWARE\Classes\CLSID\{{2E338C91-8ED1-11D1-AC54-00A0C94A8147}\TypeLib; ValueType: string; ValueData: {{CBE51AA8-A410-11D1-80D0-006097C9987D}; Components: VisualCpp\CeTools
Root: HKLM; Subkey: SOFTWARE\Classes\CLSID\{{2E338C91-8ED1-11D1-AC54-00A0C94A8147}\VERSION; ValueType: string; ValueData: 1.0; Components: VisualCpp\CeTools

Root: HKLM; Subkey: SOFTWARE\Classes\CLSID\{{2E338C92-8ED1-11D1-AC54-00A0C94A8147}; ValueType: string; ValueData: VIWFrame.CWebPages; Components: VisualCpp\CeTools
Root: HKLM; Subkey: SOFTWARE\Classes\CLSID\{{2E338C92-8ED1-11D1-AC54-00A0C94A8147}\Implemented Categories; Components: VisualCpp\CeTools
Root: HKLM; Subkey: SOFTWARE\Classes\CLSID\{{2E338C92-8ED1-11D1-AC54-00A0C94A8147}\Implemented Categories\{{40FC6ED5-2438-11CF-A3DB-080036F12502}; Components: VisualCpp\CeTools
Root: HKLM; Subkey: SOFTWARE\Classes\CLSID\{{2E338C92-8ED1-11D1-AC54-00A0C94A8147}\InprocServer32; ValueType: string; ValueData: {cf}\Microsoft Shared\Wizards98\VIWZRT.DLL; Components: VisualCpp\CeTools
Root: HKLM; Subkey: SOFTWARE\Classes\CLSID\{{2E338C92-8ED1-11D1-AC54-00A0C94A8147}\ProgID; ValueType: string; ValueData: VIWFrame.CWebPages; Components: VisualCpp\CeTools
Root: HKLM; Subkey: SOFTWARE\Classes\CLSID\{{2E338C92-8ED1-11D1-AC54-00A0C94A8147}\Programmable; Components: VisualCpp\CeTools
Root: HKLM; Subkey: SOFTWARE\Classes\CLSID\{{2E338C92-8ED1-11D1-AC54-00A0C94A8147}\TypeLib; ValueType: string; ValueData: {{CBE51AA8-A410-11D1-80D0-006097C9987D}; Components: VisualCpp\CeTools
Root: HKLM; Subkey: SOFTWARE\Classes\CLSID\{{2E338C92-8ED1-11D1-AC54-00A0C94A8147}\VERSION; ValueType: string; ValueData: 1.0; Components: VisualCpp\CeTools

Root: HKLM; Subkey: SOFTWARE\Classes\CLSID\{{2E338C93-8ED1-11D1-AC54-00A0C94A8147}; ValueType: string; ValueData: VIWFrame.CWizardApp; Components: VisualCpp\CeTools
Root: HKLM; Subkey: SOFTWARE\Classes\CLSID\{{2E338C93-8ED1-11D1-AC54-00A0C94A8147}\Implemented Categories; Components: VisualCpp\CeTools
Root: HKLM; Subkey: SOFTWARE\Classes\CLSID\{{2E338C93-8ED1-11D1-AC54-00A0C94A8147}\Implemented Categories\{{40FC6ED5-2438-11CF-A3DB-080036F12502}; Components: VisualCpp\CeTools
Root: HKLM; Subkey: SOFTWARE\Classes\CLSID\{{2E338C93-8ED1-11D1-AC54-00A0C94A8147}\InprocServer32; ValueType: string; ValueData: {cf}\Microsoft Shared\Wizards98\VIWZRT.DLL; Components: VisualCpp\CeTools
Root: HKLM; Subkey: SOFTWARE\Classes\CLSID\{{2E338C93-8ED1-11D1-AC54-00A0C94A8147}\ProgID; ValueType: string; ValueData: VIWFrame.CWizardApp; Components: VisualCpp\CeTools
Root: HKLM; Subkey: SOFTWARE\Classes\CLSID\{{2E338C93-8ED1-11D1-AC54-00A0C94A8147}\Programmable; Components: VisualCpp\CeTools
Root: HKLM; Subkey: SOFTWARE\Classes\CLSID\{{2E338C93-8ED1-11D1-AC54-00A0C94A8147}\TypeLib; ValueType: string; ValueData: {{CBE51AA8-A410-11D1-80D0-006097C9987D}; Components: VisualCpp\CeTools
Root: HKLM; Subkey: SOFTWARE\Classes\CLSID\{{2E338C93-8ED1-11D1-AC54-00A0C94A8147}\VERSION; ValueType: string; ValueData: 1.0; Components: VisualCpp\CeTools

Root: HKLM; Subkey: SOFTWARE\Classes\CLSID\{{2E338C94-8ED1-11D1-AC54-00A0C94A8147}; ValueType: string; ValueData: VIWFrame.CThemeManager; Components: VisualCpp\CeTools
Root: HKLM; Subkey: SOFTWARE\Classes\CLSID\{{2E338C94-8ED1-11D1-AC54-00A0C94A8147}\Implemented Categories; Components: VisualCpp\CeTools
Root: HKLM; Subkey: SOFTWARE\Classes\CLSID\{{2E338C94-8ED1-11D1-AC54-00A0C94A8147}\Implemented Categories\{{40FC6ED5-2438-11CF-A3DB-080036F12502}; Components: VisualCpp\CeTools
Root: HKLM; Subkey: SOFTWARE\Classes\CLSID\{{2E338C94-8ED1-11D1-AC54-00A0C94A8147}\InprocServer32; ValueType: string; ValueData: {cf}\Microsoft Shared\Wizards98\VIWZRT.DLL; Components: VisualCpp\CeTools
Root: HKLM; Subkey: SOFTWARE\Classes\CLSID\{{2E338C94-8ED1-11D1-AC54-00A0C94A8147}\ProgID; ValueType: string; ValueData: VIWFrame.CThemeManager; Components: VisualCpp\CeTools
Root: HKLM; Subkey: SOFTWARE\Classes\CLSID\{{2E338C94-8ED1-11D1-AC54-00A0C94A8147}\Programmable; Components: VisualCpp\CeTools
Root: HKLM; Subkey: SOFTWARE\Classes\CLSID\{{2E338C94-8ED1-11D1-AC54-00A0C94A8147}\TypeLib; ValueType: string; ValueData: {{CBE51AA8-A410-11D1-80D0-006097C9987D}; Components: VisualCpp\CeTools
Root: HKLM; Subkey: SOFTWARE\Classes\CLSID\{{2E338C94-8ED1-11D1-AC54-00A0C94A8147}\VERSION; ValueType: string; ValueData: 1.0; Components: VisualCpp\CeTools

Root: HKLM; Subkey: SOFTWARE\Classes\CLSID\{{2E338C95-8ED1-11D1-AC54-00A0C94A8147}; ValueType: string; ValueData: VIWFrame.CDBManager; Components: VisualCpp\CeTools
Root: HKLM; Subkey: SOFTWARE\Classes\CLSID\{{2E338C95-8ED1-11D1-AC54-00A0C94A8147}\Implemented Categories; Components: VisualCpp\CeTools
Root: HKLM; Subkey: SOFTWARE\Classes\CLSID\{{2E338C95-8ED1-11D1-AC54-00A0C94A8147}\Implemented Categories\{{40FC6ED5-2438-11CF-A3DB-080036F12502}; Components: VisualCpp\CeTools
Root: HKLM; Subkey: SOFTWARE\Classes\CLSID\{{2E338C95-8ED1-11D1-AC54-00A0C94A8147}\InprocServer32; ValueType: string; ValueData: {cf}\Microsoft Shared\Wizards98\VIWZRT.DLL; Components: VisualCpp\CeTools
Root: HKLM; Subkey: SOFTWARE\Classes\CLSID\{{2E338C95-8ED1-11D1-AC54-00A0C94A8147}\ProgID; ValueType: string; ValueData: VIWFrame.CDBManager; Components: VisualCpp\CeTools
Root: HKLM; Subkey: SOFTWARE\Classes\CLSID\{{2E338C95-8ED1-11D1-AC54-00A0C94A8147}\Programmable; Components: VisualCpp\CeTools
Root: HKLM; Subkey: SOFTWARE\Classes\CLSID\{{2E338C95-8ED1-11D1-AC54-00A0C94A8147}\TypeLib; ValueType: string; ValueData: {{CBE51AA8-A410-11D1-80D0-006097C9987D}; Components: VisualCpp\CeTools
Root: HKLM; Subkey: SOFTWARE\Classes\CLSID\{{2E338C95-8ED1-11D1-AC54-00A0C94A8147}\VERSION; ValueType: string; ValueData: 1.0; Components: VisualCpp\CeTools

Root: HKLM; Subkey: SOFTWARE\Classes\CLSID\{{2E338C96-8ED1-11D1-AC54-00A0C94A8147}; ValueType: string; ValueData: VIWFrame.CLayoutManager; Components: VisualCpp\CeTools
Root: HKLM; Subkey: SOFTWARE\Classes\CLSID\{{2E338C96-8ED1-11D1-AC54-00A0C94A8147}\Implemented Categories; Components: VisualCpp\CeTools
Root: HKLM; Subkey: SOFTWARE\Classes\CLSID\{{2E338C96-8ED1-11D1-AC54-00A0C94A8147}\Implemented Categories\{{40FC6ED5-2438-11CF-A3DB-080036F12502}; Components: VisualCpp\CeTools
Root: HKLM; Subkey: SOFTWARE\Classes\CLSID\{{2E338C96-8ED1-11D1-AC54-00A0C94A8147}\InprocServer32; ValueType: string; ValueData: {cf}\Microsoft Shared\Wizards98\VIWZRT.DLL; Components: VisualCpp\CeTools
Root: HKLM; Subkey: SOFTWARE\Classes\CLSID\{{2E338C96-8ED1-11D1-AC54-00A0C94A8147}\ProgID; ValueType: string; ValueData: VIWFrame.CLayoutManager; Components: VisualCpp\CeTools
Root: HKLM; Subkey: SOFTWARE\Classes\CLSID\{{2E338C96-8ED1-11D1-AC54-00A0C94A8147}\Programmable; Components: VisualCpp\CeTools
Root: HKLM; Subkey: SOFTWARE\Classes\CLSID\{{2E338C96-8ED1-11D1-AC54-00A0C94A8147}\TypeLib; ValueType: string; ValueData: {{CBE51AA8-A410-11D1-80D0-006097C9987D}; Components: VisualCpp\CeTools
Root: HKLM; Subkey: SOFTWARE\Classes\CLSID\{{2E338C96-8ED1-11D1-AC54-00A0C94A8147}\VERSION; ValueType: string; ValueData: 1.0; Components: VisualCpp\CeTools

Root: HKLM; Subkey: SOFTWARE\Classes\CLSID\{{323E7DB7-C174-11D1-ABF9-006008C6167D}; ValueType: string; ValueData: VMEventHandler.ItemProperty
Root: HKLM; Subkey: SOFTWARE\Classes\CLSID\{{323E7DB7-C174-11D1-ABF9-006008C6167D}\Implemented Categories\{{40FC6ED5-2438-11CF-A3DB-080036F12502}
Root: HKLM; Subkey: SOFTWARE\Classes\CLSID\{{323E7DB7-C174-11D1-ABF9-006008C6167D}\ProgID; ValueType: string; ValueData: VMEventHandler.ItemProperty
Root: HKLM; Subkey: SOFTWARE\Classes\CLSID\{{323E7DB7-C174-11D1-ABF9-006008C6167D}\Programmable
Root: HKLM; Subkey: SOFTWARE\Classes\CLSID\{{323E7DB7-C174-11D1-ABF9-006008C6167D}\TypeLib; ValueType: string; ValueData: {{6661B73C-9D9C-11D1-B931-00C04FBBC221}
Root: HKLM; Subkey: SOFTWARE\Classes\CLSID\{{323E7DB7-C174-11D1-ABF9-006008C6167D}\VERSION; ValueType: string; ValueData: 1.2

Root: HKLM; Subkey: SOFTWARE\Classes\CLSID\{{3FF69183-1582-11D1-9605-00600818410C}; ValueType: string; ValueData: Cabinet Class
Root: HKLM; Subkey: SOFTWARE\Classes\CLSID\{{3FF69183-1582-11D1-9605-00600818410C}\InprocServer32; ValueType: string; ValueData: {app}\Common\Tools\VCM\VCMCAB.DLL
Root: HKLM; Subkey: SOFTWARE\Classes\CLSID\{{3FF69183-1582-11D1-9605-00600818410C}\InprocServer32; ValueType: string; ValueName: ThreadingModel; ValueData: Apartment
Root: HKLM; Subkey: SOFTWARE\Classes\CLSID\{{3FF69183-1582-11D1-9605-00600818410C}\ProgID; ValueType: string; ValueData: Vcm.Cabinet.1
Root: HKLM; Subkey: SOFTWARE\Classes\CLSID\{{3FF69183-1582-11D1-9605-00600818410C}\Programmable
Root: HKLM; Subkey: SOFTWARE\Classes\CLSID\{{3FF69183-1582-11D1-9605-00600818410C}\VersionIndependentProgID; ValueType: string; ValueData: Vcm.Cabinet

Root: HKLM; Subkey: SOFTWARE\Classes\CLSID\{{48FCA4A7-A8C0-11D1-AE5C-00600818410C}; ValueType: string; ValueData: VcmMgr.PropHandler
Root: HKLM; Subkey: SOFTWARE\Classes\CLSID\{{48FCA4A7-A8C0-11D1-AE5C-00600818410C}\Implemented Categories\{{40FC6ED5-2438-11CF-A3DB-080036F12502}
Root: HKLM; Subkey: SOFTWARE\Classes\CLSID\{{48FCA4A7-A8C0-11D1-AE5C-00600818410C}\InprocServer32; ValueType: string; ValueData: {app}\Common\Tools\VCM\VCMMGR.DLL
Root: HKLM; Subkey: SOFTWARE\Classes\CLSID\{{48FCA4A7-A8C0-11D1-AE5C-00600818410C}\ProgID; ValueType: string; ValueData: VcmMgr.PropHandler
Root: HKLM; Subkey: SOFTWARE\Classes\CLSID\{{48FCA4A7-A8C0-11D1-AE5C-00600818410C}\Programmable
Root: HKLM; Subkey: SOFTWARE\Classes\CLSID\{{48FCA4A7-A8C0-11D1-AE5C-00600818410C}\TypeLib; ValueType: string; ValueData: {{18BF4063-A8C4-11D1-AE5C-00600818410C}
Root: HKLM; Subkey: SOFTWARE\Classes\CLSID\{{48FCA4A7-A8C0-11D1-AE5C-00600818410C}\VERSION; ValueType: string; ValueData: 7.0

Root: HKLM; Subkey: SOFTWARE\Classes\CLSID\{{48FCA4AD-A8C0-11D1-AE5C-00600818410C}; ValueType: string; ValueData: VcmMgr.Vcm
Root: HKLM; Subkey: SOFTWARE\Classes\CLSID\{{48FCA4AD-A8C0-11D1-AE5C-00600818410C}\DefaultIcon; ValueType: string; ValueData: {app}\Common\Tools\VCM\VCMMGR.DLL, 0
Root: HKLM; Subkey: SOFTWARE\Classes\CLSID\{{48FCA4AD-A8C0-11D1-AE5C-00600818410C}\DocObject; ValueType: string; ValueData: 4
Root: HKLM; Subkey: SOFTWARE\Classes\CLSID\{{48FCA4AD-A8C0-11D1-AE5C-00600818410C}\Implemented Categories\{{0DE86A52-2BAA-11CF-A229-00AA003D7352}
Root: HKLM; Subkey: SOFTWARE\Classes\CLSID\{{48FCA4AD-A8C0-11D1-AE5C-00600818410C}\Implemented Categories\{{0DE86A53-2BAA-11CF-A229-00AA003D7352}
Root: HKLM; Subkey: SOFTWARE\Classes\CLSID\{{48FCA4AD-A8C0-11D1-AE5C-00600818410C}\Implemented Categories\{{0DE86A56-2BAA-11CF-A229-00AA003D7352}
Root: HKLM; Subkey: SOFTWARE\Classes\CLSID\{{48FCA4AD-A8C0-11D1-AE5C-00600818410C}\Implemented Categories\{{0DE86A57-2BAA-11CF-A229-00AA003D7352}
Root: HKLM; Subkey: SOFTWARE\Classes\CLSID\{{48FCA4AD-A8C0-11D1-AE5C-00600818410C}\Implemented Categories\{{40FC6ED8-2438-11CF-A3DB-080036F12502}
Root: HKLM; Subkey: SOFTWARE\Classes\CLSID\{{48FCA4AD-A8C0-11D1-AE5C-00600818410C}\InprocServer32; ValueType: string; ValueData: {app}\Common\Tools\VCM\VCMMGR.DLL
Root: HKLM; Subkey: SOFTWARE\Classes\CLSID\{{48FCA4AD-A8C0-11D1-AE5C-00600818410C}\MiscStatus; ValueType: string; ValueData: 0
Root: HKLM; Subkey: SOFTWARE\Classes\CLSID\{{48FCA4AD-A8C0-11D1-AE5C-00600818410C}\MiscStatus\1; ValueType: string; ValueData: 131473
Root: HKLM; Subkey: SOFTWARE\Classes\CLSID\{{48FCA4AD-A8C0-11D1-AE5C-00600818410C}\ProgID; ValueType: string; ValueData: VcmMgr.Vcm
Root: HKLM; Subkey: SOFTWARE\Classes\CLSID\{{48FCA4AD-A8C0-11D1-AE5C-00600818410C}\TypeLib; ValueType: string; ValueData: {{18BF4063-A8C4-11D1-AE5C-00600818410C}
Root: HKLM; Subkey: SOFTWARE\Classes\CLSID\{{48FCA4AD-A8C0-11D1-AE5C-00600818410C}\VERSION; ValueType: string; ValueData: 7.0

Root: HKLM; Subkey: SOFTWARE\Classes\CLSID\{{48FCA4AF-A8C0-11D1-AE5C-00600818410C}; ValueType: string; ValueData: VcmMgr.docShadow
Root: HKLM; Subkey: SOFTWARE\Classes\CLSID\{{48FCA4AF-A8C0-11D1-AE5C-00600818410C}\Implemented Categories\{{40FC6ED5-2438-11CF-A3DB-080036F12502}
Root: HKLM; Subkey: SOFTWARE\Classes\CLSID\{{48FCA4AF-A8C0-11D1-AE5C-00600818410C}\InprocServer32; ValueType: string; ValueData: {app}\Common\Tools\VCM\VCMMGR.DLL
Root: HKLM; Subkey: SOFTWARE\Classes\CLSID\{{48FCA4AF-A8C0-11D1-AE5C-00600818410C}\ProgID; ValueType: string; ValueData: VcmMgr.docShadow
Root: HKLM; Subkey: SOFTWARE\Classes\CLSID\{{48FCA4AF-A8C0-11D1-AE5C-00600818410C}\Programmable
Root: HKLM; Subkey: SOFTWARE\Classes\CLSID\{{48FCA4AF-A8C0-11D1-AE5C-00600818410C}\TypeLib; ValueType: string; ValueData: {{18BF4063-A8C4-11D1-AE5C-00600818410C}
Root: HKLM; Subkey: SOFTWARE\Classes\CLSID\{{48FCA4AF-A8C0-11D1-AE5C-00600818410C}\VERSION; ValueType: string; ValueData: 7.0

Root: HKLM; Subkey: SOFTWARE\Classes\CLSID\{{6661B740-9D9C-11D1-B931-00C04FBBC221}; ValueType: string; ValueData: VMEventHandler.VisualModelHandler
Root: HKLM; Subkey: SOFTWARE\Classes\CLSID\{{6661B740-9D9C-11D1-B931-00C04FBBC221}\Implemented Categories\{{40FC6ED5-2438-11CF-A3DB-080036F12502}
Root: HKLM; Subkey: SOFTWARE\Classes\CLSID\{{6661B740-9D9C-11D1-B931-00C04FBBC221}\InprocServer32; ValueType: string; ValueData: {app}\Common\Tools\VCM\VCMVMH.DLL
Root: HKLM; Subkey: SOFTWARE\Classes\CLSID\{{6661B740-9D9C-11D1-B931-00C04FBBC221}\ProgID; ValueType: string; ValueData: VMEventHandler.VisualModelHandler
Root: HKLM; Subkey: SOFTWARE\Classes\CLSID\{{6661B740-9D9C-11D1-B931-00C04FBBC221}\Programmable
Root: HKLM; Subkey: SOFTWARE\Classes\CLSID\{{6661B740-9D9C-11D1-B931-00C04FBBC221}\TypeLib; ValueType: string; ValueData: {{6661B73C-9D9C-11D1-B931-00C04FBBC221}
Root: HKLM; Subkey: SOFTWARE\Classes\CLSID\{{6661B740-9D9C-11D1-B931-00C04FBBC221}\VERSION; ValueType: string; ValueData: 1.2

#ifdef INSTALL_WNDTABS
;Root: HKLM; Subkey: SOFTWARE\Classes\CLSID\{{6A06C123-4748-11D1-BC91-0000010016A6}; ValueType: string; ValueData: WndTabs; Components: WndTabs
;Root: HKLM; Subkey: SOFTWARE\Classes\CLSID\{{6A06C123-4748-11D1-BC91-0000010016A6}\Description; ValueType: string; ValueData: Displays tabs of all open windows.; Components: WndTabs
;Root: HKLM; Subkey: SOFTWARE\Classes\CLSID\{{6A06C123-4748-11D1-BC91-0000010016A6}\InprocServer32; ValueType: string; ValueData: {app}\WndTabs\WndTabs.dll; Components: WndTabs
;Root: HKLM; Subkey: SOFTWARE\Classes\CLSID\{{6A06C123-4748-11D1-BC91-0000010016A6}\InprocServer32; ValueType: string; ValueName: ThreadingModel; ValueData: both; Components: WndTabs
;Root: HKLM; Subkey: SOFTWARE\Classes\CLSID\{{6A06C123-4748-11D1-BC91-0000010016A6}\ProgID; ValueType: string; ValueData: Window Tabs; Components: WndTabs
;Root: HKLM; Subkey: SOFTWARE\Classes\CLSID\{{6A06C123-4748-11D1-BC91-0000010016A6}\VersionIndependentProgID; ValueType: string; ValueData: WNDTABS Developer Studio Add-in; Components: WndTabs
#endif

Root: HKLM; Subkey: SOFTWARE\Classes\CLSID\{{723AA6D1-3B50-11D1-9636-00600818410C}; ValueType: string; ValueData: VcmReg Class
Root: HKLM; Subkey: SOFTWARE\Classes\CLSID\{{723AA6D1-3B50-11D1-9636-00600818410C}\InprocServer32; ValueType: string; ValueData: {app}\Common\Tools\VCM\VCMUTL.DLL
Root: HKLM; Subkey: SOFTWARE\Classes\CLSID\{{723AA6D1-3B50-11D1-9636-00600818410C}\InprocServer32; ValueType: string; ValueName: ThreadingModel; ValueData: Apartment
Root: HKLM; Subkey: SOFTWARE\Classes\CLSID\{{723AA6D1-3B50-11D1-9636-00600818410C}\ProgID; ValueType: string; ValueData: VcmUtl.VcmReg.1
Root: HKLM; Subkey: SOFTWARE\Classes\CLSID\{{723AA6D1-3B50-11D1-9636-00600818410C}\Programmable
Root: HKLM; Subkey: SOFTWARE\Classes\CLSID\{{723AA6D1-3B50-11D1-9636-00600818410C}\VersionIndependentProgID; ValueType: string; ValueData: VcmUtl.VcmReg

Root: HKLM; Subkey: SOFTWARE\Classes\CLSID\{{73750660-a067-11cf-9aa3-00aa006cc905}; ValueType: string; ValueData: PegFile; Components: VisualCpp\CeTools
Root: HKLM; Subkey: SOFTWARE\Classes\CLSID\{{73750660-a067-11cf-9aa3-00aa006cc905}\InprocServer32; ValueType: string; ValueData: pegemul.dll; Components: VisualCpp\CeTools
Root: HKLM; Subkey: SOFTWARE\Classes\CLSID\{{73750660-a067-11cf-9aa3-00aa006cc905}\ProgID; ValueType: string; ValueData: OSViewer\PegFile; Components: VisualCpp\CeTools

Root: HKLM; Subkey: SOFTWARE\Classes\CLSID\{{73750661-a067-11cf-9aa3-00aa006cc905}; ValueType: string; ValueData: PegDatabase; Components: VisualCpp\CeTools
Root: HKLM; Subkey: SOFTWARE\Classes\CLSID\{{73750661-a067-11cf-9aa3-00aa006cc905}\InprocServer32; ValueType: string; ValueData: pegemul.dll; Components: VisualCpp\CeTools
Root: HKLM; Subkey: SOFTWARE\Classes\CLSID\{{73750661-a067-11cf-9aa3-00aa006cc905}\ProgID; ValueType: string; ValueData: OSViewer\PegDatabase; Components: VisualCpp\CeTools

Root: HKLM; Subkey: SOFTWARE\Classes\CLSID\{{73750662-a067-11cf-9aa3-00aa006cc905}; ValueType: string; ValueData: Local; Components: VisualCpp\CeTools
Root: HKLM; Subkey: SOFTWARE\Classes\CLSID\{{73750662-a067-11cf-9aa3-00aa006cc905}\InprocServer32; ValueType: string; ValueData: peghost.dll; Components: VisualCpp\CeTools
Root: HKLM; Subkey: SOFTWARE\Classes\CLSID\{{73750662-a067-11cf-9aa3-00aa006cc905}\ProgID; ValueType: string; ValueData: OSViewer\Local; Components: VisualCpp\CeTools

Root: HKLM; Subkey: SOFTWARE\Classes\CLSID\{{73750663-a067-11cf-9aa3-00aa006cc905}; ValueType: string; ValueData: DeviceFile; Components: VisualCpp\CeTools
Root: HKLM; Subkey: SOFTWARE\Classes\CLSID\{{73750663-a067-11cf-9aa3-00aa006cc905}\InprocServer32; ValueType: string; ValueData: peg_rmt.dll; Components: VisualCpp\CeTools
Root: HKLM; Subkey: SOFTWARE\Classes\CLSID\{{73750663-a067-11cf-9aa3-00aa006cc905}\ProgID; ValueType: string; ValueData: OSViewer\DeviceFile; Components: VisualCpp\CeTools

Root: HKLM; Subkey: SOFTWARE\Classes\CLSID\{{73750664-a067-11cf-9aa3-00aa006cc905}; ValueType: string; ValueData: DeviceDatabase; Components: VisualCpp\CeTools
Root: HKLM; Subkey: SOFTWARE\Classes\CLSID\{{73750664-a067-11cf-9aa3-00aa006cc905}\InprocServer32; ValueType: string; ValueData: peg_rmt.dll; Components: VisualCpp\CeTools
Root: HKLM; Subkey: SOFTWARE\Classes\CLSID\{{73750664-a067-11cf-9aa3-00aa006cc905}\ProgID; ValueType: string; ValueData: OSViewer\DeviceDatabase; Components: VisualCpp\CeTools

Root: HKLM; Subkey: SOFTWARE\Classes\CLSID\{{811AB29D-1BD8-11D0-BD04-0080C7920B88}; ValueType: string; ValueData: DBWiz1.CDBDevice
Root: HKLM; Subkey: SOFTWARE\Classes\CLSID\{{811AB29D-1BD8-11D0-BD04-0080C7920B88}\Implemented Categories\{{40FC6ED5-2438-11CF-A3DB-080036F12502}
Root: HKLM; Subkey: SOFTWARE\Classes\CLSID\{{811AB29D-1BD8-11D0-BD04-0080C7920B88}\InprocServer32; ValueType: string; ValueData: {app}\Common\Wizards98\DBWIZ1.DLL
Root: HKLM; Subkey: SOFTWARE\Classes\CLSID\{{811AB29D-1BD8-11D0-BD04-0080C7920B88}\ProgID; ValueType: string; ValueData: DBWiz1.CDBDevice
Root: HKLM; Subkey: SOFTWARE\Classes\CLSID\{{811AB29D-1BD8-11D0-BD04-0080C7920B88}\Programmable
Root: HKLM; Subkey: SOFTWARE\Classes\CLSID\{{811AB29D-1BD8-11D0-BD04-0080C7920B88}\TypeLib; ValueType: string; ValueData: {{47485243-D317-11D1-AFB6-006097C9A8F0}
Root: HKLM; Subkey: SOFTWARE\Classes\CLSID\{{811AB29D-1BD8-11D0-BD04-0080C7920B88}\VERSION; ValueType: string; ValueData: 1.0

Root: HKLM; Subkey: SOFTWARE\Classes\CLSID\{{811AB29E-1BD8-11D0-BD04-0080C7920B88}; ValueType: string; ValueData: DBWiz1.CDBDevices
Root: HKLM; Subkey: SOFTWARE\Classes\CLSID\{{811AB29E-1BD8-11D0-BD04-0080C7920B88}\Implemented Categories\{{40FC6ED5-2438-11CF-A3DB-080036F12502}
Root: HKLM; Subkey: SOFTWARE\Classes\CLSID\{{811AB29E-1BD8-11D0-BD04-0080C7920B88}\InprocServer32; ValueType: string; ValueData: {app}\Common\Wizards98\DBWIZ1.DLL
Root: HKLM; Subkey: SOFTWARE\Classes\CLSID\{{811AB29E-1BD8-11D0-BD04-0080C7920B88}\ProgID; ValueType: string; ValueData: DBWiz1.CDBDevices
Root: HKLM; Subkey: SOFTWARE\Classes\CLSID\{{811AB29E-1BD8-11D0-BD04-0080C7920B88}\Programmable
Root: HKLM; Subkey: SOFTWARE\Classes\CLSID\{{811AB29E-1BD8-11D0-BD04-0080C7920B88}\TypeLib; ValueType: string; ValueData: {{47485243-D317-11D1-AFB6-006097C9A8F0}
Root: HKLM; Subkey: SOFTWARE\Classes\CLSID\{{811AB29E-1BD8-11D0-BD04-0080C7920B88}\VERSION; ValueType: string; ValueData: 1.0

Root: HKLM; Subkey: SOFTWARE\Classes\CLSID\{{811AB29F-1BD8-11D0-BD04-0080C7920B88}; ValueType: string; ValueData: New Database Wizard
Root: HKLM; Subkey: SOFTWARE\Classes\CLSID\{{811AB29F-1BD8-11D0-BD04-0080C7920B88}\DefaultIcon; ValueType: string; ValueData: {app}\Common\Wizards98\dbwiz1.dll,0
Root: HKLM; Subkey: SOFTWARE\Classes\CLSID\{{811AB29F-1BD8-11D0-BD04-0080C7920B88}\Implemented Categories\{{21448B92-0788-11D0-8144-00A0C91BBEE3}
Root: HKLM; Subkey: SOFTWARE\Classes\CLSID\{{811AB29F-1BD8-11D0-BD04-0080C7920B88}\Implemented Categories\{{40FC6ED5-2438-11CF-A3DB-080036F12502}
Root: HKLM; Subkey: SOFTWARE\Classes\CLSID\{{811AB29F-1BD8-11D0-BD04-0080C7920B88}\InprocServer32; ValueType: string; ValueData: {app}\Common\Wizards98\DBWIZ1.DLL
Root: HKLM; Subkey: SOFTWARE\Classes\CLSID\{{811AB29F-1BD8-11D0-BD04-0080C7920B88}\ProgID; ValueType: string; ValueData: DBWiz1.CNewDatabaseWizard
Root: HKLM; Subkey: SOFTWARE\Classes\CLSID\{{811AB29F-1BD8-11D0-BD04-0080C7920B88}\Programmable
Root: HKLM; Subkey: SOFTWARE\Classes\CLSID\{{811AB29F-1BD8-11D0-BD04-0080C7920B88}\ProjectType; ValueType: string; ValueData: {{8B072243-8C1A-11CF-BE23-00AA0062C2EF}
Root: HKLM; Subkey: SOFTWARE\Classes\CLSID\{{811AB29F-1BD8-11D0-BD04-0080C7920B88}\TypeLib; ValueType: string; ValueData: {{47485243-D317-11D1-AFB6-006097C9A8F0}
Root: HKLM; Subkey: SOFTWARE\Classes\CLSID\{{811AB29F-1BD8-11D0-BD04-0080C7920B88}\VERSION; ValueType: string; ValueData: 1.0

Root: HKLM; Subkey: SOFTWARE\Classes\CLSID\{{811AB2A1-1BD8-11D0-BD04-0080C7920B88}; ValueType: string; ValueData: DBWiz1.CStatusContainer
Root: HKLM; Subkey: SOFTWARE\Classes\CLSID\{{811AB2A1-1BD8-11D0-BD04-0080C7920B88}\Implemented Categories\{{40FC6ED5-2438-11CF-A3DB-080036F12502}
Root: HKLM; Subkey: SOFTWARE\Classes\CLSID\{{811AB2A1-1BD8-11D0-BD04-0080C7920B88}\InprocServer32; ValueType: string; ValueData: {app}\Common\Wizards98\DBWIZ1.DLL
Root: HKLM; Subkey: SOFTWARE\Classes\CLSID\{{811AB2A1-1BD8-11D0-BD04-0080C7920B88}\ProgID; ValueType: string; ValueData: DBWiz1.CStatusContainer
Root: HKLM; Subkey: SOFTWARE\Classes\CLSID\{{811AB2A1-1BD8-11D0-BD04-0080C7920B88}\Programmable
Root: HKLM; Subkey: SOFTWARE\Classes\CLSID\{{811AB2A1-1BD8-11D0-BD04-0080C7920B88}\TypeLib; ValueType: string; ValueData: {{47485243-D317-11D1-AFB6-006097C9A8F0}
Root: HKLM; Subkey: SOFTWARE\Classes\CLSID\{{811AB2A1-1BD8-11D0-BD04-0080C7920B88}\VERSION; ValueType: string; ValueData: 1.0

Root: HKLM; Subkey: SOFTWARE\Classes\CLSID\{{9B969EEA-EF39-11D1-8D6D-00A0C98B28E2}; ValueType: string; ValueData: VcmMgr.Importer
Root: HKLM; Subkey: SOFTWARE\Classes\CLSID\{{9B969EEA-EF39-11D1-8D6D-00A0C98B28E2}\Implemented Categories\{{40FC6ED5-2438-11CF-A3DB-080036F12502}
Root: HKLM; Subkey: SOFTWARE\Classes\CLSID\{{9B969EEA-EF39-11D1-8D6D-00A0C98B28E2}\InprocServer32; ValueType: string; ValueData: {app}\Common\Tools\VCM\VCMMGR.DLL
Root: HKLM; Subkey: SOFTWARE\Classes\CLSID\{{9B969EEA-EF39-11D1-8D6D-00A0C98B28E2}\ProgID; ValueType: string; ValueData: VcmMgr.Importer
Root: HKLM; Subkey: SOFTWARE\Classes\CLSID\{{9B969EEA-EF39-11D1-8D6D-00A0C98B28E2}\Programmable
Root: HKLM; Subkey: SOFTWARE\Classes\CLSID\{{9B969EEA-EF39-11D1-8D6D-00A0C98B28E2}\TypeLib; ValueType: string; ValueData: {{18BF4063-A8C4-11D1-AE5C-00600818410C}
Root: HKLM; Subkey: SOFTWARE\Classes\CLSID\{{9B969EEA-EF39-11D1-8D6D-00A0C98B28E2}\VERSION; ValueType: string; ValueData: 7.0

Root: HKLM; Subkey: SOFTWARE\Classes\CLSID\{{9B969EEE-EF39-11D1-8D6D-00A0C98B28E2}; ValueType: string; ValueData: VcmMgr.RepTableItem
Root: HKLM; Subkey: SOFTWARE\Classes\CLSID\{{9B969EEE-EF39-11D1-8D6D-00A0C98B28E2}\Implemented Categories\{{40FC6ED5-2438-11CF-A3DB-080036F12502}
Root: HKLM; Subkey: SOFTWARE\Classes\CLSID\{{9B969EEE-EF39-11D1-8D6D-00A0C98B28E2}\InprocServer32; ValueType: string; ValueData: {app}\Common\Tools\VCM\VCMMGR.DLL
Root: HKLM; Subkey: SOFTWARE\Classes\CLSID\{{9B969EEE-EF39-11D1-8D6D-00A0C98B28E2}\ProgID; ValueType: string; ValueData: VcmMgr.RepTableItem
Root: HKLM; Subkey: SOFTWARE\Classes\CLSID\{{9B969EEE-EF39-11D1-8D6D-00A0C98B28E2}\Programmable
Root: HKLM; Subkey: SOFTWARE\Classes\CLSID\{{9B969EEE-EF39-11D1-8D6D-00A0C98B28E2}\TypeLib; ValueType: string; ValueData: {{18BF4063-A8C4-11D1-AE5C-00600818410C}
Root: HKLM; Subkey: SOFTWARE\Classes\CLSID\{{9B969EEE-EF39-11D1-8D6D-00A0C98B28E2}\VERSION; ValueType: string; ValueData: 7.0

Root: HKLM; Subkey: SOFTWARE\Classes\CLSID\{{A8F8E829-06DA-11D2-8D70-00A0C98B28E2}; ValueType: string; ValueData: AxBrowse.AxBrowser
Root: HKLM; Subkey: SOFTWARE\Classes\CLSID\{{A8F8E829-06DA-11D2-8D70-00A0C98B28E2}\Control; ValueType: string; ValueData: 
Root: HKLM; Subkey: SOFTWARE\Classes\CLSID\{{A8F8E829-06DA-11D2-8D70-00A0C98B28E2}\Implemented Categories
Root: HKLM; Subkey: SOFTWARE\Classes\CLSID\{{A8F8E829-06DA-11D2-8D70-00A0C98B28E2}\Implemented Categories\{{0DE86A52-2BAA-11CF-A229-00AA003D7352}
Root: HKLM; Subkey: SOFTWARE\Classes\CLSID\{{A8F8E829-06DA-11D2-8D70-00A0C98B28E2}\Implemented Categories\{{0DE86A53-2BAA-11CF-A229-00AA003D7352}
Root: HKLM; Subkey: SOFTWARE\Classes\CLSID\{{A8F8E829-06DA-11D2-8D70-00A0C98B28E2}\Implemented Categories\{{0DE86A57-2BAA-11CF-A229-00AA003D7352}
Root: HKLM; Subkey: SOFTWARE\Classes\CLSID\{{A8F8E829-06DA-11D2-8D70-00A0C98B28E2}\Implemented Categories\{{40FC6ED4-2438-11CF-A3DB-080036F12502}
Root: HKLM; Subkey: SOFTWARE\Classes\CLSID\{{A8F8E829-06DA-11D2-8D70-00A0C98B28E2}\InprocServer32; ValueType: string; ValueData: {app}\Common\Tools\VCM\VCMAXB.OCX
Root: HKLM; Subkey: SOFTWARE\Classes\CLSID\{{A8F8E829-06DA-11D2-8D70-00A0C98B28E2}\MiscStatus; ValueType: string; ValueData: 0
Root: HKLM; Subkey: SOFTWARE\Classes\CLSID\{{A8F8E829-06DA-11D2-8D70-00A0C98B28E2}\MiscStatus\1; ValueType: string; ValueData: 131473
Root: HKLM; Subkey: SOFTWARE\Classes\CLSID\{{A8F8E829-06DA-11D2-8D70-00A0C98B28E2}\ProgID; ValueType: string; ValueData: AxBrowse.AxBrowser
Root: HKLM; Subkey: SOFTWARE\Classes\CLSID\{{A8F8E829-06DA-11D2-8D70-00A0C98B28E2}\ToolboxBitmap32; ValueType: string; ValueData: {app}\Common\Tools\VCM\VCMAXB.OCX, 30000
Root: HKLM; Subkey: SOFTWARE\Classes\CLSID\{{A8F8E829-06DA-11D2-8D70-00A0C98B28E2}\TypeLib; ValueType: string; ValueData: {{A8F8E827-06DA-11D2-8D70-00A0C98B28E2}
Root: HKLM; Subkey: SOFTWARE\Classes\CLSID\{{A8F8E829-06DA-11D2-8D70-00A0C98B28E2}\VERSION; ValueType: string; ValueData: 1.0

Root: HKLM; Subkey: SOFTWARE\Classes\CLSID\{{A9E78841-19E7-11D1-9608-00600818410C}; ValueType: string; ValueData: PSFactoryBuffer
Root: HKLM; Subkey: SOFTWARE\Classes\CLSID\{{A9E78841-19E7-11D1-9608-00600818410C}\InProcServer32; ValueType: string; ValueData: {app}\Common\Tools\VCM\VCMCAB.DLL
Root: HKLM; Subkey: SOFTWARE\Classes\CLSID\{{A9E78841-19E7-11D1-9608-00600818410C}\InProcServer32; ValueType: string; ValueName: ThreadingModel; ValueData: Both

Root: HKLM; Subkey: SOFTWARE\Classes\CLSID\{{AC0714F6-3D04-11D1-AE7D-00A0C90F26F4}; ValueType: string; ValueData: Addin Class
Root: HKLM; Subkey: SOFTWARE\Classes\CLSID\{{AC0714F6-3D04-11D1-AE7D-00A0C90F26F4}\DesignerFeatures; ValueType: dword; ValueName: Required; ValueData: $00000025
Root: HKLM; Subkey: SOFTWARE\Classes\CLSID\{{AC0714F6-3D04-11D1-AE7D-00A0C90F26F4}\Implemented Categories
Root: HKLM; Subkey: SOFTWARE\Classes\CLSID\{{AC0714F6-3D04-11D1-AE7D-00A0C90F26F4}\Implemented Categories\{{0DE86A52-2BAA-11CF-A229-00AA003D7352}
Root: HKLM; Subkey: SOFTWARE\Classes\CLSID\{{AC0714F6-3D04-11D1-AE7D-00A0C90F26F4}\Implemented Categories\{{0DE86A53-2BAA-11CF-A229-00AA003D7352}
Root: HKLM; Subkey: SOFTWARE\Classes\CLSID\{{AC0714F6-3D04-11D1-AE7D-00A0C90F26F4}\Implemented Categories\{{0DE86A57-2BAA-11CF-A229-00AA003D7352}
Root: HKLM; Subkey: SOFTWARE\Classes\CLSID\{{AC0714F6-3D04-11D1-AE7D-00A0C90F26F4}\Implemented Categories\{{40FC6ED5-2438-11CF-A3DB-080036F12502}
Root: HKLM; Subkey: SOFTWARE\Classes\CLSID\{{AC0714F6-3D04-11D1-AE7D-00A0C90F26F4}\Implemented Categories\{{4EB304D0-7555-11cf-A0C2-00AA0062BE57}
Root: HKLM; Subkey: SOFTWARE\Classes\CLSID\{{AC0714F6-3D04-11D1-AE7D-00A0C90F26F4}\InprocServer32; ValueType: string; ValueData: {cf}\designer\MSADDNDR.DLL
Root: HKLM; Subkey: SOFTWARE\Classes\CLSID\{{AC0714F6-3D04-11D1-AE7D-00A0C90F26F4}\InprocServer32; ValueType: string; ValueName: ThreadingModel; ValueData: Apartment
Root: HKLM; Subkey: SOFTWARE\Classes\CLSID\{{AC0714F6-3D04-11D1-AE7D-00A0C90F26F4}\Instance CLSID; ValueType: string; ValueData: {{AC0714F7-3D04-11d1-AE7D-00A0C90F26F4}
Root: HKLM; Subkey: SOFTWARE\Classes\CLSID\{{AC0714F6-3D04-11D1-AE7D-00A0C90F26F4}\MiscStatus; ValueType: string; ValueData: 0
Root: HKLM; Subkey: SOFTWARE\Classes\CLSID\{{AC0714F6-3D04-11D1-AE7D-00A0C90F26F4}\MiscStatus\1; ValueType: string; ValueData: 132496
Root: HKLM; Subkey: SOFTWARE\Classes\CLSID\{{AC0714F6-3D04-11D1-AE7D-00A0C90F26F4}\ProgID; ValueType: string; ValueData: MSAddnDr.AddInDesigner.1
Root: HKLM; Subkey: SOFTWARE\Classes\CLSID\{{AC0714F6-3D04-11D1-AE7D-00A0C90F26F4}\Programmable
Root: HKLM; Subkey: SOFTWARE\Classes\CLSID\{{AC0714F6-3D04-11D1-AE7D-00A0C90F26F4}\TypeLib; ValueType: string; ValueData: {{AC0714F2-3D04-11D1-AE7D-00A0C90F26F4}
Root: HKLM; Subkey: SOFTWARE\Classes\CLSID\{{AC0714F6-3D04-11D1-AE7D-00A0C90F26F4}\Version; ValueType: string; ValueData: 1.0
Root: HKLM; Subkey: SOFTWARE\Classes\CLSID\{{AC0714F6-3D04-11D1-AE7D-00A0C90F26F4}\VersionIndependentProgID; ValueType: string; ValueData: MSAddnDr.AddInDesigner

Root: HKLM; Subkey: SOFTWARE\Classes\CLSID\{{AC0714F7-3D04-11D1-AE7D-00A0C90F26F4}; ValueType: string; ValueData: Microsoft Add-In Authouring Designer
Root: HKLM; Subkey: SOFTWARE\Classes\CLSID\{{AC0714F7-3D04-11D1-AE7D-00A0C90F26F4}\Implemented Categories
Root: HKLM; Subkey: SOFTWARE\Classes\CLSID\{{AC0714F7-3D04-11D1-AE7D-00A0C90F26F4}\Implemented Categories\{{40FC6ED5-2438-11CF-A3DB-080036F12502}
Root: HKLM; Subkey: SOFTWARE\Classes\CLSID\{{AC0714F7-3D04-11D1-AE7D-00A0C90F26F4}\InprocServer32; ValueType: string; ValueData: {cf}\designer\MSADDNDR.DLL
Root: HKLM; Subkey: SOFTWARE\Classes\CLSID\{{AC0714F7-3D04-11D1-AE7D-00A0C90F26F4}\InprocServer32; ValueType: string; ValueName: ThreadingModel; ValueData: Apartment
Root: HKLM; Subkey: SOFTWARE\Classes\CLSID\{{AC0714F7-3D04-11D1-AE7D-00A0C90F26F4}\MiscStatus
Root: HKLM; Subkey: SOFTWARE\Classes\CLSID\{{AC0714F7-3D04-11D1-AE7D-00A0C90F26F4}\MiscStatus\1; ValueType: string; ValueData: 1024
Root: HKLM; Subkey: SOFTWARE\Classes\CLSID\{{AC0714F7-3D04-11D1-AE7D-00A0C90F26F4}\ProgID; ValueType: string; ValueData: MSAddnDr.AddInInstance.1
Root: HKLM; Subkey: SOFTWARE\Classes\CLSID\{{AC0714F7-3D04-11D1-AE7D-00A0C90F26F4}\Programmable
Root: HKLM; Subkey: SOFTWARE\Classes\CLSID\{{AC0714F7-3D04-11D1-AE7D-00A0C90F26F4}\TypeLib; ValueType: string; ValueData: {{AC0714F2-3D04-11D1-AE7D-00A0C90F26F4}
Root: HKLM; Subkey: SOFTWARE\Classes\CLSID\{{AC0714F7-3D04-11D1-AE7D-00A0C90F26F4}\Version; ValueType: string; ValueData: 1.0
Root: HKLM; Subkey: SOFTWARE\Classes\CLSID\{{AC0714F7-3D04-11D1-AE7D-00A0C90F26F4}\VersionIndependentProgID; ValueType: string; ValueData: MSAddnDr.AddInInstance

Root: HKLM; Subkey: SOFTWARE\Classes\CLSID\{{AEB7F2FC-06DA-11D2-8D70-00A0C98B28E2}; ValueType: string; ValueData: VcmEnu.IResource
Root: HKLM; Subkey: SOFTWARE\Classes\CLSID\{{AEB7F2FC-06DA-11D2-8D70-00A0C98B28E2}\Implemented Categories
Root: HKLM; Subkey: SOFTWARE\Classes\CLSID\{{AEB7F2FC-06DA-11D2-8D70-00A0C98B28E2}\Implemented Categories\{{40FC6ED5-2438-11CF-A3DB-080036F12502}
Root: HKLM; Subkey: SOFTWARE\Classes\CLSID\{{AEB7F2FC-06DA-11D2-8D70-00A0C98B28E2}\InprocServer32; ValueType: string; ValueData: {app}\Common\Tools\VCM\resources\1033\VCMUI.DLL
Root: HKLM; Subkey: SOFTWARE\Classes\CLSID\{{AEB7F2FC-06DA-11D2-8D70-00A0C98B28E2}\InprocServer32; ValueType: string; ValueName: ThreadingModel; ValueData: Apartment
Root: HKLM; Subkey: SOFTWARE\Classes\CLSID\{{AEB7F2FC-06DA-11D2-8D70-00A0C98B28E2}\ProgID; ValueType: string; ValueData: VcmEnu.IResource
Root: HKLM; Subkey: SOFTWARE\Classes\CLSID\{{AEB7F2FC-06DA-11D2-8D70-00A0C98B28E2}\Programmable
Root: HKLM; Subkey: SOFTWARE\Classes\CLSID\{{AEB7F2FC-06DA-11D2-8D70-00A0C98B28E2}\TypeLib; ValueType: string; ValueData: {{AEB7F2FA-06DA-11D2-8D70-00A0C98B28E2}
Root: HKLM; Subkey: SOFTWARE\Classes\CLSID\{{AEB7F2FC-06DA-11D2-8D70-00A0C98B28E2}\VERSION; ValueType: string; ValueData: 1.0

Root: HKLM; Subkey: SOFTWARE\Classes\CLSID\{{CF1B2C10-3772-11D1-962B-00600818410C}; ValueType: string; ValueData: PSFactoryBuffer
Root: HKLM; Subkey: SOFTWARE\Classes\CLSID\{{CF1B2C10-3772-11D1-962B-00600818410C}\InProcServer32; ValueType: string; ValueData: {app}\Common\IDE\IDE98\VCMPK.DLL
Root: HKLM; Subkey: SOFTWARE\Classes\CLSID\{{CF1B2C10-3772-11D1-962B-00600818410C}\InProcServer32; ValueType: string; ValueName: ThreadingModel; ValueData: Both

Root: HKLM; Subkey: SOFTWARE\Classes\CLSID\{{E835B190-3DDF-11D2-BBB2-00A0C9C9CCEE}; ValueType: string; ValueData: PlatformManagerUI Class; Components: VisualCpp\CeTools
Root: HKLM; Subkey: SOFTWARE\Classes\CLSID\{{E835B190-3DDF-11D2-BBB2-00A0C9C9CCEE}\InprocServer32; ValueType: string; ValueData: {app}\Windows CE Tools\BIN\CEMGRUI.DLL; Components: VisualCpp\CeTools
Root: HKLM; Subkey: SOFTWARE\Classes\CLSID\{{E835B190-3DDF-11D2-BBB2-00A0C9C9CCEE}\InprocServer32; ValueType: string; ValueName: ThreadingModel; ValueData: Both; Components: VisualCpp\CeTools
Root: HKLM; Subkey: SOFTWARE\Classes\CLSID\{{E835B190-3DDF-11D2-BBB2-00A0C9C9CCEE}\ProgID; ValueType: string; ValueData: Cemgrui.PlatformManagerUI.1; Components: VisualCpp\CeTools
Root: HKLM; Subkey: SOFTWARE\Classes\CLSID\{{E835B190-3DDF-11D2-BBB2-00A0C9C9CCEE}\VersionIndependentProgID; ValueType: string; ValueData: Cemgrui.PlatformManagerUI; Components: VisualCpp\CeTools

Root: HKLM; Subkey: SOFTWARE\Classes\CLSID\{{F384D883-F9AA-11D1-BB9E-00A0C9C9CCEE}; ValueType: string; ValueData: PlatformManager Class; Components: VisualCpp\CeTools
Root: HKLM; Subkey: SOFTWARE\Classes\CLSID\{{F384D883-F9AA-11D1-BB9E-00A0C9C9CCEE}; ValueType: string; ValueName: AppID; ValueData: {{2C99AFCC-F99D-11D1-BB9D-00A0C9C9CCEE}; Components: VisualCpp\CeTools
Root: HKLM; Subkey: SOFTWARE\Classes\CLSID\{{F384D883-F9AA-11D1-BB9E-00A0C9C9CCEE}\LocalServer32; ValueType: string; ValueData: {app}\Windows CE Tools\BIN\cemgr.exe; Components: VisualCpp\CeTools
Root: HKLM; Subkey: SOFTWARE\Classes\CLSID\{{F384D883-F9AA-11D1-BB9E-00A0C9C9CCEE}\ProgID; ValueType: string; ValueData: PlatformManager.PlatformManager.1; Components: VisualCpp\CeTools
Root: HKLM; Subkey: SOFTWARE\Classes\CLSID\{{F384D883-F9AA-11D1-BB9E-00A0C9C9CCEE}\VersionIndependentProgID; ValueType: string; ValueData: PlatformManager.PlatformManager; Components: VisualCpp\CeTools

Root: HKLM; Subkey: SOFTWARE\Classes\CLSID\{{FB7FDAE2-89B8-11CF-9BE8-00A0C90A632C}; ValueType: string; ValueData: MSDEV.APPLICATION; Components: VisualCpp\CeTools
Root: HKLM; Subkey: SOFTWARE\Classes\CLSID\{{FB7FDAE2-89B8-11CF-9BE8-00A0C90A632C}\InprocHandler32; ValueType: string; ValueData: ole32.DLL; Components: VisualCpp\CeTools
Root: HKLM; Subkey: SOFTWARE\Classes\CLSID\{{FB7FDAE2-89B8-11CF-9BE8-00A0C90A632C}\LocalServer32; ValueType: string; ValueData: {app}\Common\MSDev98\Bin\MSDEV.EXE; Components: VisualCpp\CeTools
Root: HKLM; Subkey: SOFTWARE\Classes\CLSID\{{FB7FDAE2-89B8-11CF-9BE8-00A0C90A632C}\ProgID; ValueType: string; ValueData: MSDEV.APPLICATION; Components: VisualCpp\CeTools

Root: HKLM; Subkey: SOFTWARE\Classes\Component Categories\{{21448B92-0788-11d0-8144-00A0C91BBEE3}; ValueType: string; ValueName: 409; ValueData: Visual InterDev Web Site Wizards; Components: VisualCpp\CeTools
Root: HKLM; Subkey: SOFTWARE\Classes\Component Categories\{{21448B92-0788-11d0-8144-00A0C91BBEE3}; ValueType: string; ValueName: 409; ValueData: Visual InterDev Web Site Wizards; Components: VisualCpp\ServicePack

Root: HKLM; Subkey: SOFTWARE\Classes\DBWiz1.CDBDevice; ValueType: string; ValueData: DBWiz1.CDBDevice
Root: HKLM; Subkey: SOFTWARE\Classes\DBWiz1.CDBDevice\Clsid; ValueType: string; ValueData: {{811AB29D-1BD8-11D0-BD04-0080C7920B88}
Root: HKLM; Subkey: SOFTWARE\Classes\DBWiz1.CDBDevices; ValueType: string; ValueData: DBWiz1.CDBDevices
Root: HKLM; Subkey: SOFTWARE\Classes\DBWiz1.CDBDevices\Clsid; ValueType: string; ValueData: {{811AB29E-1BD8-11D0-BD04-0080C7920B88}
Root: HKLM; Subkey: SOFTWARE\Classes\DBWiz1.CNewDatabaseWizard; ValueType: string; ValueData: DBWiz1.CNewDatabaseWizard
Root: HKLM; Subkey: SOFTWARE\Classes\DBWiz1.CNewDatabaseWizard\Clsid; ValueType: string; ValueData: {{811AB29F-1BD8-11D0-BD04-0080C7920B88}
Root: HKLM; Subkey: SOFTWARE\Classes\DBWiz1.CStatusContainer; ValueType: string; ValueData: DBWiz1.CStatusContainer
Root: HKLM; Subkey: SOFTWARE\Classes\DBWiz1.CStatusContainer\Clsid; ValueType: string; ValueData: {{811AB2A1-1BD8-11D0-BD04-0080C7920B88}

Root: HKLM; Subkey: SOFTWARE\Classes\IMInstall.IMInstall.1; ValueType: string; ValueData: IMInstall Class; Components: VisualCpp\ServicePack
Root: HKLM; Subkey: SOFTWARE\Classes\IMInstall.IMInstall.1\CLSID; ValueType: string; ValueData: {{D24FD4A5-BEBC-11D1-8CB9-00C04FC2F51A}; Components: VisualCpp\ServicePack
Root: HKLM; Subkey: SOFTWARE\Classes\IMInstall.IMInstall; ValueType: string; ValueData: IMInstall Class; Components: VisualCpp\ServicePack
Root: HKLM; Subkey: SOFTWARE\Classes\IMInstall.IMInstall\CurVer; ValueType: string; ValueData: IMInstall.IMInstall.1; Components: VisualCpp\ServicePack

Root: HKLM; Subkey: SOFTWARE\Classes\Interface\{{0452FFE0-A81D-11CF-AD07-00A0C9034965}; ValueType: string; ValueData: IDispBuildProject; Components: VisualCpp\CeTools
Root: HKLM; Subkey: SOFTWARE\Classes\Interface\{{0452FFE0-A81D-11CF-AD07-00A0C9034965}\ProxyStubClsid; ValueType: string; ValueData: {{00020420-0000-0000-C000-000000000046}; Components: VisualCpp\CeTools
Root: HKLM; Subkey: SOFTWARE\Classes\Interface\{{0452FFE0-A81D-11CF-AD07-00A0C9034965}\ProxyStubClsid32; ValueType: string; ValueData: {{00020420-0000-0000-C000-000000000046}; Components: VisualCpp\CeTools
Root: HKLM; Subkey: SOFTWARE\Classes\Interface\{{0452FFE0-A81D-11CF-AD07-00A0C9034965}\TypeLib; ValueType: string; ValueData: {{96961265-A819-11CF-AD07-00A0C9034965}; Components: VisualCpp\CeTools
Root: HKLM; Subkey: SOFTWARE\Classes\Interface\{{0452FFE0-A81D-11CF-AD07-00A0C9034965}\TypeLib; ValueType: string; ValueName: Version; ValueData: 6.0; Components: VisualCpp\CeTools

Root: HKLM; Subkey: SOFTWARE\Classes\Interface\{{0452FFE2-A81D-11CF-AD07-00A0C9034965}; ValueType: string; ValueData: IDispConfiguration; Components: VisualCpp\CeTools
Root: HKLM; Subkey: SOFTWARE\Classes\Interface\{{0452FFE2-A81D-11CF-AD07-00A0C9034965}\ProxyStubClsid; ValueType: string; ValueData: {{00020420-0000-0000-C000-000000000046}; Components: VisualCpp\CeTools
Root: HKLM; Subkey: SOFTWARE\Classes\Interface\{{0452FFE2-A81D-11CF-AD07-00A0C9034965}\ProxyStubClsid32; ValueType: string; ValueData: {{00020420-0000-0000-C000-000000000046}; Components: VisualCpp\CeTools
Root: HKLM; Subkey: SOFTWARE\Classes\Interface\{{0452FFE2-A81D-11CF-AD07-00A0C9034965}\TypeLib; ValueType: string; ValueData: {{96961265-A819-11CF-AD07-00A0C9034965}; Components: VisualCpp\CeTools
Root: HKLM; Subkey: SOFTWARE\Classes\Interface\{{0452FFE2-A81D-11CF-AD07-00A0C9034965}\TypeLib; ValueType: string; ValueName: Version; ValueData: 6.0; Components: VisualCpp\CeTools

Root: HKLM; Subkey: SOFTWARE\Classes\Interface\{{05092F20-833F-11CF-AB59-00AA00C091A1}; ValueType: string; ValueData: ITextSelection; Components: VisualCpp\CeTools
Root: HKLM; Subkey: SOFTWARE\Classes\Interface\{{05092F20-833F-11CF-AB59-00AA00C091A1}\ProxyStubClsid; ValueType: string; ValueData: {{00020424-0000-0000-C000-000000000046}; Components: VisualCpp\CeTools
Root: HKLM; Subkey: SOFTWARE\Classes\Interface\{{05092F20-833F-11CF-AB59-00AA00C091A1}\ProxyStubClsid32; ValueType: string; ValueData: {{00020424-0000-0000-C000-000000000046}; Components: VisualCpp\CeTools
Root: HKLM; Subkey: SOFTWARE\Classes\Interface\{{05092F20-833F-11CF-AB59-00AA00C091A1}\TypeLib; ValueType: string; ValueData: {{2A6DF200-8240-11CF-AB59-00AA00C091A1}; Components: VisualCpp\CeTools
Root: HKLM; Subkey: SOFTWARE\Classes\Interface\{{05092F20-833F-11CF-AB59-00AA00C091A1}\TypeLib; ValueType: string; ValueName: Version; ValueData: 6.0; Components: VisualCpp\CeTools

Root: HKLM; Subkey: SOFTWARE\Classes\Interface\{{08541520-83D3-11CF-AB59-00AA00C091A1}; ValueType: string; ValueData: ITextWindow; Components: VisualCpp\CeTools
Root: HKLM; Subkey: SOFTWARE\Classes\Interface\{{08541520-83D3-11CF-AB59-00AA00C091A1}\ProxyStubClsid; ValueType: string; ValueData: {{00020424-0000-0000-C000-000000000046}; Components: VisualCpp\CeTools
Root: HKLM; Subkey: SOFTWARE\Classes\Interface\{{08541520-83D3-11CF-AB59-00AA00C091A1}\ProxyStubClsid32; ValueType: string; ValueData: {{00020424-0000-0000-C000-000000000046}; Components: VisualCpp\CeTools
Root: HKLM; Subkey: SOFTWARE\Classes\Interface\{{08541520-83D3-11CF-AB59-00AA00C091A1}\TypeLib; ValueType: string; ValueData: {{2A6DF200-8240-11CF-AB59-00AA00C091A1}; Components: VisualCpp\CeTools
Root: HKLM; Subkey: SOFTWARE\Classes\Interface\{{08541520-83D3-11CF-AB59-00AA00C091A1}\TypeLib; ValueType: string; ValueName: Version; ValueData: 6.0; Components: VisualCpp\CeTools

Root: HKLM; Subkey: SOFTWARE\Classes\Interface\{{0DE5B3A0-A420-11CF-AB59-00AA00C091A1}; ValueType: string; ValueData: ITextEditor; Components: VisualCpp\CeTools
Root: HKLM; Subkey: SOFTWARE\Classes\Interface\{{0DE5B3A0-A420-11CF-AB59-00AA00C091A1}\ProxyStubClsid; ValueType: string; ValueData: {{00020424-0000-0000-C000-000000000046}; Components: VisualCpp\CeTools
Root: HKLM; Subkey: SOFTWARE\Classes\Interface\{{0DE5B3A0-A420-11CF-AB59-00AA00C091A1}\ProxyStubClsid32; ValueType: string; ValueData: {{00020424-0000-0000-C000-000000000046}; Components: VisualCpp\CeTools
Root: HKLM; Subkey: SOFTWARE\Classes\Interface\{{0DE5B3A0-A420-11CF-AB59-00AA00C091A1}\TypeLib; ValueType: string; ValueData: {{2A6DF200-8240-11CF-AB59-00AA00C091A1}; Components: VisualCpp\CeTools
Root: HKLM; Subkey: SOFTWARE\Classes\Interface\{{0DE5B3A0-A420-11CF-AB59-00AA00C091A1}\TypeLib; ValueType: string; ValueName: Version; ValueData: 6.0; Components: VisualCpp\CeTools

Root: HKLM; Subkey: SOFTWARE\Classes\Interface\{{13BF7741-A7E8-11CF-AD07-00A0C9034965}; ValueType: string; ValueData: IProjects; Components: VisualCpp\CeTools
Root: HKLM; Subkey: SOFTWARE\Classes\Interface\{{13BF7741-A7E8-11CF-AD07-00A0C9034965}\ProxyStubClsid; ValueType: string; ValueData: {{00020424-0000-0000-C000-000000000046}; Components: VisualCpp\CeTools
Root: HKLM; Subkey: SOFTWARE\Classes\Interface\{{13BF7741-A7E8-11CF-AD07-00A0C9034965}\ProxyStubClsid32; ValueType: string; ValueData: {{00020424-0000-0000-C000-000000000046}; Components: VisualCpp\CeTools
Root: HKLM; Subkey: SOFTWARE\Classes\Interface\{{13BF7741-A7E8-11CF-AD07-00A0C9034965}\TypeLib; ValueType: string; ValueData: {{B3CF8E20-19B6-11CF-8E4D-00AA004254C4}; Components: VisualCpp\CeTools
Root: HKLM; Subkey: SOFTWARE\Classes\Interface\{{13BF7741-A7E8-11CF-AD07-00A0C9034965}\TypeLib; ValueType: string; ValueName: Version; ValueData: 6.0; Components: VisualCpp\CeTools

;Root: HKLM; Subkey: SOFTWARE\Classes\Interface\{{1E9A88A1-2968-11D1-851D-00A0C911E8B0}; ValueType: string; ValueData: VMBrowser

;Root: HKLM; Subkey: SOFTWARE\Classes\Interface\{{1E9A88A3-2968-11D1-851D-00A0C911E8B0}; ValueType: string; ValueData: VMBrowser

Root: HKLM; Subkey: SOFTWARE\Classes\Interface\{{2A4F783A-014E-11D2-BBA0-00A0C9C9CCEE}; ValueType: string; ValueData: IPackage; Components: VisualCpp\CeTools
Root: HKLM; Subkey: SOFTWARE\Classes\Interface\{{2A4F783A-014E-11D2-BBA0-00A0C9C9CCEE}\NumMethods; ValueType: string; ValueData: 7; Components: VisualCpp\CeTools
Root: HKLM; Subkey: SOFTWARE\Classes\Interface\{{2A4F783A-014E-11D2-BBA0-00A0C9C9CCEE}\ProxyStubClsid32; ValueType: string; ValueData: {{2A4F783A-014E-11D2-BBA0-00A0C9C9CCEE}; Components: VisualCpp\CeTools

Root: HKLM; Subkey: SOFTWARE\Classes\Interface\{{2A4F783D-014E-11D2-BBA0-00A0C9C9CCEE}; ValueType: string; ValueData: IEnumPackageFiles; Components: VisualCpp\CeTools
Root: HKLM; Subkey: SOFTWARE\Classes\Interface\{{2A4F783D-014E-11D2-BBA0-00A0C9C9CCEE}\NumMethods; ValueType: string; ValueData: 9; Components: VisualCpp\CeTools
Root: HKLM; Subkey: SOFTWARE\Classes\Interface\{{2A4F783D-014E-11D2-BBA0-00A0C9C9CCEE}\ProxyStubClsid32; ValueType: string; ValueData: {{2A4F783A-014E-11D2-BBA0-00A0C9C9CCEE}; Components: VisualCpp\CeTools

Root: HKLM; Subkey: SOFTWARE\Classes\Interface\{{2A6DF201-8240-11CF-AB59-00AA00C091A1}; ValueType: string; ValueData: ITextDocument; Components: VisualCpp\CeTools
Root: HKLM; Subkey: SOFTWARE\Classes\Interface\{{2A6DF201-8240-11CF-AB59-00AA00C091A1}\ProxyStubClsid; ValueType: string; ValueData: {{00020424-0000-0000-C000-000000000046}; Components: VisualCpp\CeTools
Root: HKLM; Subkey: SOFTWARE\Classes\Interface\{{2A6DF201-8240-11CF-AB59-00AA00C091A1}\ProxyStubClsid32; ValueType: string; ValueData: {{00020424-0000-0000-C000-000000000046}; Components: VisualCpp\CeTools
Root: HKLM; Subkey: SOFTWARE\Classes\Interface\{{2A6DF201-8240-11CF-AB59-00AA00C091A1}\TypeLib; ValueType: string; ValueData: {{2A6DF200-8240-11CF-AB59-00AA00C091A1}; Components: VisualCpp\CeTools
Root: HKLM; Subkey: SOFTWARE\Classes\Interface\{{2A6DF201-8240-11CF-AB59-00AA00C091A1}\TypeLib; ValueType: string; ValueName: Version; ValueData: 6.0; Components: VisualCpp\CeTools

;Root: HKLM; Subkey: SOFTWARE\Classes\Interface\{{323E7DB6-C174-11D1-ABF9-006008C6167D}; ValueType: string; ValueData: ItemProperty

Root: HKLM; Subkey: SOFTWARE\Classes\Interface\{{34C63001-AE64-11CF-AB59-00AA00C091A1}; ValueType: string; ValueData: IDebugger; Components: VisualCpp\CeTools
Root: HKLM; Subkey: SOFTWARE\Classes\Interface\{{34C63001-AE64-11CF-AB59-00AA00C091A1}\ProxyStubClsid; ValueType: string; ValueData: {{00020424-0000-0000-C000-000000000046}; Components: VisualCpp\CeTools
Root: HKLM; Subkey: SOFTWARE\Classes\Interface\{{34C63001-AE64-11CF-AB59-00AA00C091A1}\ProxyStubClsid32; ValueType: string; ValueData: {{00020424-0000-0000-C000-000000000046}; Components: VisualCpp\CeTools
Root: HKLM; Subkey: SOFTWARE\Classes\Interface\{{34C63001-AE64-11CF-AB59-00AA00C091A1}\TypeLib; ValueType: string; ValueData: {{34C63000-AE64-11CF-AB59-00AA00C091A1}; Components: VisualCpp\CeTools
Root: HKLM; Subkey: SOFTWARE\Classes\Interface\{{34C63001-AE64-11CF-AB59-00AA00C091A1}\TypeLib; ValueType: string; ValueName: Version; ValueData: 6.0; Components: VisualCpp\CeTools

Root: HKLM; Subkey: SOFTWARE\Classes\Interface\{{34C63002-AE64-11CF-AB59-00AA00C091A1}; ValueType: string; ValueData: IDispDebugger; Components: VisualCpp\CeTools
Root: HKLM; Subkey: SOFTWARE\Classes\Interface\{{34C63002-AE64-11CF-AB59-00AA00C091A1}\ProxyStubClsid; ValueType: string; ValueData: {{00020420-0000-0000-C000-000000000046}; Components: VisualCpp\CeTools
Root: HKLM; Subkey: SOFTWARE\Classes\Interface\{{34C63002-AE64-11CF-AB59-00AA00C091A1}\ProxyStubClsid32; ValueType: string; ValueData: {{00020420-0000-0000-C000-000000000046}; Components: VisualCpp\CeTools
Root: HKLM; Subkey: SOFTWARE\Classes\Interface\{{34C63002-AE64-11CF-AB59-00AA00C091A1}\TypeLib; ValueType: string; ValueData: {{34C63000-AE64-11CF-AB59-00AA00C091A1}; Components: VisualCpp\CeTools
Root: HKLM; Subkey: SOFTWARE\Classes\Interface\{{34C63002-AE64-11CF-AB59-00AA00C091A1}\TypeLib; ValueType: string; ValueName: Version; ValueData: 6.0; Components: VisualCpp\CeTools

Root: HKLM; Subkey: SOFTWARE\Classes\Interface\{{34C63004-AE64-11CF-AB59-00AA00C091A1}; ValueType: string; ValueData: IBreakpoint; Components: VisualCpp\CeTools
Root: HKLM; Subkey: SOFTWARE\Classes\Interface\{{34C63004-AE64-11CF-AB59-00AA00C091A1}\ProxyStubClsid; ValueType: string; ValueData: {{00020424-0000-0000-C000-000000000046}; Components: VisualCpp\CeTools
Root: HKLM; Subkey: SOFTWARE\Classes\Interface\{{34C63004-AE64-11CF-AB59-00AA00C091A1}\ProxyStubClsid32; ValueType: string; ValueData: {{00020424-0000-0000-C000-000000000046}; Components: VisualCpp\CeTools
Root: HKLM; Subkey: SOFTWARE\Classes\Interface\{{34C63004-AE64-11CF-AB59-00AA00C091A1}\TypeLib; ValueType: string; ValueData: {{34C63000-AE64-11CF-AB59-00AA00C091A1}; Components: VisualCpp\CeTools
Root: HKLM; Subkey: SOFTWARE\Classes\Interface\{{34C63004-AE64-11CF-AB59-00AA00C091A1}\TypeLib; ValueType: string; ValueName: Version; ValueData: 6.0; Components: VisualCpp\CeTools

Root: HKLM; Subkey: SOFTWARE\Classes\Interface\{{34C63005-AE64-11CF-AB59-00AA00C091A1}; ValueType: string; ValueData: IDispBreakpoint; Components: VisualCpp\CeTools
Root: HKLM; Subkey: SOFTWARE\Classes\Interface\{{34C63005-AE64-11CF-AB59-00AA00C091A1}\ProxyStubClsid; ValueType: string; ValueData: {{00020420-0000-0000-C000-000000000046}; Components: VisualCpp\CeTools
Root: HKLM; Subkey: SOFTWARE\Classes\Interface\{{34C63005-AE64-11CF-AB59-00AA00C091A1}\ProxyStubClsid32; ValueType: string; ValueData: {{00020420-0000-0000-C000-000000000046}; Components: VisualCpp\CeTools
Root: HKLM; Subkey: SOFTWARE\Classes\Interface\{{34C63005-AE64-11CF-AB59-00AA00C091A1}\TypeLib; ValueType: string; ValueData: {{34C63000-AE64-11CF-AB59-00AA00C091A1}; Components: VisualCpp\CeTools
Root: HKLM; Subkey: SOFTWARE\Classes\Interface\{{34C63005-AE64-11CF-AB59-00AA00C091A1}\TypeLib; ValueType: string; ValueName: Version; ValueData: 6.0; Components: VisualCpp\CeTools

Root: HKLM; Subkey: SOFTWARE\Classes\Interface\{{34C63007-AE64-11CF-AB59-00AA00C091A1}; ValueType: string; ValueData: IBreakpoints; Components: VisualCpp\CeTools
Root: HKLM; Subkey: SOFTWARE\Classes\Interface\{{34C63007-AE64-11CF-AB59-00AA00C091A1}\ProxyStubClsid; ValueType: string; ValueData: {{00020424-0000-0000-C000-000000000046}; Components: VisualCpp\CeTools
Root: HKLM; Subkey: SOFTWARE\Classes\Interface\{{34C63007-AE64-11CF-AB59-00AA00C091A1}\ProxyStubClsid32; ValueType: string; ValueData: {{00020424-0000-0000-C000-000000000046}; Components: VisualCpp\CeTools
Root: HKLM; Subkey: SOFTWARE\Classes\Interface\{{34C63007-AE64-11CF-AB59-00AA00C091A1}\TypeLib; ValueType: string; ValueData: {{34C63000-AE64-11CF-AB59-00AA00C091A1}; Components: VisualCpp\CeTools
Root: HKLM; Subkey: SOFTWARE\Classes\Interface\{{34C63007-AE64-11CF-AB59-00AA00C091A1}\TypeLib; ValueType: string; ValueName: Version; ValueData: 6.0; Components: VisualCpp\CeTools

Root: HKLM; Subkey: SOFTWARE\Classes\Interface\{{34C63008-AE64-11CF-AB59-00AA00C091A1}; ValueType: string; ValueData: IDispBreakpoints; Components: VisualCpp\CeTools
Root: HKLM; Subkey: SOFTWARE\Classes\Interface\{{34C63008-AE64-11CF-AB59-00AA00C091A1}\ProxyStubClsid; ValueType: string; ValueData: {{00020420-0000-0000-C000-000000000046}; Components: VisualCpp\CeTools
Root: HKLM; Subkey: SOFTWARE\Classes\Interface\{{34C63008-AE64-11CF-AB59-00AA00C091A1}\ProxyStubClsid32; ValueType: string; ValueData: {{00020420-0000-0000-C000-000000000046}; Components: VisualCpp\CeTools
Root: HKLM; Subkey: SOFTWARE\Classes\Interface\{{34C63008-AE64-11CF-AB59-00AA00C091A1}\TypeLib; ValueType: string; ValueData: {{34C63000-AE64-11CF-AB59-00AA00C091A1}; Components: VisualCpp\CeTools
Root: HKLM; Subkey: SOFTWARE\Classes\Interface\{{34C63008-AE64-11CF-AB59-00AA00C091A1}\TypeLib; ValueType: string; ValueName: Version; ValueData: 6.0; Components: VisualCpp\CeTools

Root: HKLM; Subkey: SOFTWARE\Classes\Interface\{{34C6301A-AE64-11CF-AB59-00AA00C091A1}; ValueType: string; ValueData: IDebuggerEvents; Components: VisualCpp\CeTools
Root: HKLM; Subkey: SOFTWARE\Classes\Interface\{{34C6301A-AE64-11CF-AB59-00AA00C091A1}\ProxyStubClsid; ValueType: string; ValueData: {{00020424-0000-0000-C000-000000000046}; Components: VisualCpp\CeTools
Root: HKLM; Subkey: SOFTWARE\Classes\Interface\{{34C6301A-AE64-11CF-AB59-00AA00C091A1}\ProxyStubClsid32; ValueType: string; ValueData: {{00020424-0000-0000-C000-000000000046}; Components: VisualCpp\CeTools
Root: HKLM; Subkey: SOFTWARE\Classes\Interface\{{34C6301A-AE64-11CF-AB59-00AA00C091A1}\TypeLib; ValueType: string; ValueData: {{34C63000-AE64-11CF-AB59-00AA00C091A1}; Components: VisualCpp\CeTools
Root: HKLM; Subkey: SOFTWARE\Classes\Interface\{{34C6301A-AE64-11CF-AB59-00AA00C091A1}\TypeLib; ValueType: string; ValueName: Version; ValueData: 6.0; Components: VisualCpp\CeTools

Root: HKLM; Subkey: SOFTWARE\Classes\Interface\{{34C6301B-AE64-11CF-AB59-00AA00C091A1}; ValueType: string; ValueData: IDispDebuggerEvents; Components: VisualCpp\CeTools
Root: HKLM; Subkey: SOFTWARE\Classes\Interface\{{34C6301B-AE64-11CF-AB59-00AA00C091A1}\ProxyStubClsid; ValueType: string; ValueData: {{00020420-0000-0000-C000-000000000046}; Components: VisualCpp\CeTools
Root: HKLM; Subkey: SOFTWARE\Classes\Interface\{{34C6301B-AE64-11CF-AB59-00AA00C091A1}\ProxyStubClsid32; ValueType: string; ValueData: {{00020420-0000-0000-C000-000000000046}; Components: VisualCpp\CeTools
Root: HKLM; Subkey: SOFTWARE\Classes\Interface\{{34C6301B-AE64-11CF-AB59-00AA00C091A1}\TypeLib; ValueType: string; ValueData: {{34C63000-AE64-11CF-AB59-00AA00C091A1}; Components: VisualCpp\CeTools
Root: HKLM; Subkey: SOFTWARE\Classes\Interface\{{34C6301B-AE64-11CF-AB59-00AA00C091A1}\TypeLib; ValueType: string; ValueName: Version; ValueData: 6.0; Components: VisualCpp\CeTools

Root: HKLM; Subkey: SOFTWARE\Classes\Interface\{{3928F551-96E6-11CF-9C00-00A0C90A632C}; ValueType: string; ValueData: IWindows; Components: VisualCpp\CeTools
Root: HKLM; Subkey: SOFTWARE\Classes\Interface\{{3928F551-96E6-11CF-9C00-00A0C90A632C}\ProxyStubClsid; ValueType: string; ValueData: {{00020424-0000-0000-C000-000000000046}; Components: VisualCpp\CeTools
Root: HKLM; Subkey: SOFTWARE\Classes\Interface\{{3928F551-96E6-11CF-9C00-00A0C90A632C}\ProxyStubClsid32; ValueType: string; ValueData: {{00020424-0000-0000-C000-000000000046}; Components: VisualCpp\CeTools
Root: HKLM; Subkey: SOFTWARE\Classes\Interface\{{3928F551-96E6-11CF-9C00-00A0C90A632C}\TypeLib; ValueType: string; ValueData: {{B3CF8E20-19B6-11CF-8E4D-00AA004254C4}; Components: VisualCpp\CeTools
Root: HKLM; Subkey: SOFTWARE\Classes\Interface\{{3928F551-96E6-11CF-9C00-00A0C90A632C}\TypeLib; ValueType: string; ValueName: Version; ValueData: 6.0; Components: VisualCpp\CeTools

Root: HKLM; Subkey: SOFTWARE\Classes\Interface\{{3B37807A-EA99-11D1-8A30-00E029089FF3}; ValueType: string; ValueData: PropHandler
Root: HKLM; Subkey: SOFTWARE\Classes\Interface\{{3B37807A-EA99-11D1-8A30-00E029089FF3}\ProxyStubClsid; ValueType: string; ValueData: {{00020424-0000-0000-C000-000000000046}
Root: HKLM; Subkey: SOFTWARE\Classes\Interface\{{3B37807A-EA99-11D1-8A30-00E029089FF3}\ProxyStubClsid32; ValueType: string; ValueData: {{00020424-0000-0000-C000-000000000046}
Root: HKLM; Subkey: SOFTWARE\Classes\Interface\{{3B37807A-EA99-11D1-8A30-00E029089FF3}\TypeLib; ValueType: string; ValueData: {{18BF4063-A8C4-11D1-AE5C-00600818410C}
Root: HKLM; Subkey: SOFTWARE\Classes\Interface\{{3B37807A-EA99-11D1-8A30-00E029089FF3}\TypeLib; ValueType: string; ValueName: Version; ValueData: 7.0

Root: HKLM; Subkey: SOFTWARE\Classes\Interface\{{3B378080-EA99-11D1-8A30-00E029089FF3}; ValueType: string; ValueData: Vcm
Root: HKLM; Subkey: SOFTWARE\Classes\Interface\{{3B378080-EA99-11D1-8A30-00E029089FF3}\ProxyStubClsid; ValueType: string; ValueData: {{00020424-0000-0000-C000-000000000046}
Root: HKLM; Subkey: SOFTWARE\Classes\Interface\{{3B378080-EA99-11D1-8A30-00E029089FF3}\ProxyStubClsid32; ValueType: string; ValueData: {{00020424-0000-0000-C000-000000000046}
Root: HKLM; Subkey: SOFTWARE\Classes\Interface\{{3B378080-EA99-11D1-8A30-00E029089FF3}\TypeLib; ValueType: string; ValueData: {{18BF4063-A8C4-11D1-AE5C-00600818410C}
Root: HKLM; Subkey: SOFTWARE\Classes\Interface\{{3B378080-EA99-11D1-8A30-00E029089FF3}\TypeLib; ValueType: string; ValueName: Version; ValueData: 7.0

Root: HKLM; Subkey: SOFTWARE\Classes\Interface\{{3B378081-EA99-11D1-8A30-00E029089FF3}; ValueType: string; ValueData: docShadow
Root: HKLM; Subkey: SOFTWARE\Classes\Interface\{{3B378081-EA99-11D1-8A30-00E029089FF3}\ProxyStubClsid; ValueType: string; ValueData: {{00020424-0000-0000-C000-000000000046}
Root: HKLM; Subkey: SOFTWARE\Classes\Interface\{{3B378081-EA99-11D1-8A30-00E029089FF3}\ProxyStubClsid32; ValueType: string; ValueData: {{00020424-0000-0000-C000-000000000046}
Root: HKLM; Subkey: SOFTWARE\Classes\Interface\{{3B378081-EA99-11D1-8A30-00E029089FF3}\TypeLib; ValueType: string; ValueData: {{18BF4063-A8C4-11D1-AE5C-00600818410C}
Root: HKLM; Subkey: SOFTWARE\Classes\Interface\{{3B378081-EA99-11D1-8A30-00E029089FF3}\TypeLib; ValueType: string; ValueName: Version; ValueData: 7.0

Root: HKLM; Subkey: SOFTWARE\Classes\Interface\{{3B378082-EA99-11D1-8A30-00E029089FF3}; ValueType: string; ValueData: VsHelp
Root: HKLM; Subkey: SOFTWARE\Classes\Interface\{{3B378082-EA99-11D1-8A30-00E029089FF3}\ProxyStubClsid; ValueType: string; ValueData: {{00020424-0000-0000-C000-000000000046}
Root: HKLM; Subkey: SOFTWARE\Classes\Interface\{{3B378082-EA99-11D1-8A30-00E029089FF3}\ProxyStubClsid32; ValueType: string; ValueData: {{00020424-0000-0000-C000-000000000046}
Root: HKLM; Subkey: SOFTWARE\Classes\Interface\{{3B378082-EA99-11D1-8A30-00E029089FF3}\TypeLib; ValueType: string; ValueData: {{18BF4063-A8C4-11D1-AE5C-00600818410C}
Root: HKLM; Subkey: SOFTWARE\Classes\Interface\{{3B378082-EA99-11D1-8A30-00E029089FF3}\TypeLib; ValueType: string; ValueName: Version; ValueData: 7.0

Root: HKLM; Subkey: SOFTWARE\Classes\Interface\{{3B378084-EA99-11D1-8A30-00E029089FF3}; ValueType: string; ValueData: Connect
Root: HKLM; Subkey: SOFTWARE\Classes\Interface\{{3B378084-EA99-11D1-8A30-00E029089FF3}\ProxyStubClsid; ValueType: string; ValueData: {{00020424-0000-0000-C000-000000000046}
Root: HKLM; Subkey: SOFTWARE\Classes\Interface\{{3B378084-EA99-11D1-8A30-00E029089FF3}\ProxyStubClsid32; ValueType: string; ValueData: {{00020424-0000-0000-C000-000000000046}
Root: HKLM; Subkey: SOFTWARE\Classes\Interface\{{3B378084-EA99-11D1-8A30-00E029089FF3}\TypeLib; ValueType: string; ValueData: {{18BF4063-A8C4-11D1-AE5C-00600818410C}
Root: HKLM; Subkey: SOFTWARE\Classes\Interface\{{3B378084-EA99-11D1-8A30-00E029089FF3}\TypeLib; ValueType: string; ValueName: Version; ValueData: 7.0

Root: HKLM; Subkey: SOFTWARE\Classes\Interface\{{3B37808F-EA99-11D1-8A30-00E029089FF3}; ValueType: string; ValueData: TypeDefinition
Root: HKLM; Subkey: SOFTWARE\Classes\Interface\{{3B37808F-EA99-11D1-8A30-00E029089FF3}\ProxyStubClsid; ValueType: string; ValueData: {{00020424-0000-0000-C000-000000000046}
Root: HKLM; Subkey: SOFTWARE\Classes\Interface\{{3B37808F-EA99-11D1-8A30-00E029089FF3}\ProxyStubClsid32; ValueType: string; ValueData: {{00020424-0000-0000-C000-000000000046}
Root: HKLM; Subkey: SOFTWARE\Classes\Interface\{{3B37808F-EA99-11D1-8A30-00E029089FF3}\TypeLib; ValueType: string; ValueData: {{18BF4063-A8C4-11D1-AE5C-00600818410C}
Root: HKLM; Subkey: SOFTWARE\Classes\Interface\{{3B37808F-EA99-11D1-8A30-00E029089FF3}\TypeLib; ValueType: string; ValueName: Version; ValueData: 7.0

Root: HKLM; Subkey: SOFTWARE\Classes\Interface\{{3B378092-EA99-11D1-8A30-00E029089FF3}; ValueType: string; ValueData: ItemProperty
Root: HKLM; Subkey: SOFTWARE\Classes\Interface\{{3B378092-EA99-11D1-8A30-00E029089FF3}\ProxyStubClsid; ValueType: string; ValueData: {{00020424-0000-0000-C000-000000000046}
Root: HKLM; Subkey: SOFTWARE\Classes\Interface\{{3B378092-EA99-11D1-8A30-00E029089FF3}\ProxyStubClsid32; ValueType: string; ValueData: {{00020424-0000-0000-C000-000000000046}
Root: HKLM; Subkey: SOFTWARE\Classes\Interface\{{3B378092-EA99-11D1-8A30-00E029089FF3}\TypeLib; ValueType: string; ValueData: {{18BF4063-A8C4-11D1-AE5C-00600818410C}
Root: HKLM; Subkey: SOFTWARE\Classes\Interface\{{3B378092-EA99-11D1-8A30-00E029089FF3}\TypeLib; ValueType: string; ValueName: Version; ValueData: 7.0

Root: HKLM; Subkey: SOFTWARE\Classes\Interface\{{3B378094-EA99-11D1-8A30-00E029089FF3}; ValueType: string; ValueData: CabProgress
Root: HKLM; Subkey: SOFTWARE\Classes\Interface\{{3B378094-EA99-11D1-8A30-00E029089FF3}\ProxyStubClsid; ValueType: string; ValueData: {{00020424-0000-0000-C000-000000000046}
Root: HKLM; Subkey: SOFTWARE\Classes\Interface\{{3B378094-EA99-11D1-8A30-00E029089FF3}\ProxyStubClsid32; ValueType: string; ValueData: {{00020424-0000-0000-C000-000000000046}
Root: HKLM; Subkey: SOFTWARE\Classes\Interface\{{3B378094-EA99-11D1-8A30-00E029089FF3}\TypeLib; ValueType: string; ValueData: {{18BF4063-A8C4-11D1-AE5C-00600818410C}
Root: HKLM; Subkey: SOFTWARE\Classes\Interface\{{3B378094-EA99-11D1-8A30-00E029089FF3}\TypeLib; ValueType: string; ValueName: Version; ValueData: 7.0

Root: HKLM; Subkey: SOFTWARE\Classes\Interface\{{3B378099-EA99-11D1-8A30-00E029089FF3}; ValueType: string; ValueData: ActiveXHandler
Root: HKLM; Subkey: SOFTWARE\Classes\Interface\{{3B378099-EA99-11D1-8A30-00E029089FF3}\ProxyStubClsid; ValueType: string; ValueData: {{00020424-0000-0000-C000-000000000046}
Root: HKLM; Subkey: SOFTWARE\Classes\Interface\{{3B378099-EA99-11D1-8A30-00E029089FF3}\ProxyStubClsid32; ValueType: string; ValueData: {{00020424-0000-0000-C000-000000000046}
Root: HKLM; Subkey: SOFTWARE\Classes\Interface\{{3B378099-EA99-11D1-8A30-00E029089FF3}\TypeLib; ValueType: string; ValueData: {{18BF4063-A8C4-11D1-AE5C-00600818410C}
Root: HKLM; Subkey: SOFTWARE\Classes\Interface\{{3B378099-EA99-11D1-8A30-00E029089FF3}\TypeLib; ValueType: string; ValueName: Version; ValueData: 7.0

Root: HKLM; Subkey: SOFTWARE\Classes\Interface\{{3B37809A-EA99-11D1-8A30-00E029089FF3}; ValueType: string; ValueData: DocumentHandler
Root: HKLM; Subkey: SOFTWARE\Classes\Interface\{{3B37809A-EA99-11D1-8A30-00E029089FF3}\ProxyStubClsid; ValueType: string; ValueData: {{00020424-0000-0000-C000-000000000046}
Root: HKLM; Subkey: SOFTWARE\Classes\Interface\{{3B37809A-EA99-11D1-8A30-00E029089FF3}\ProxyStubClsid32; ValueType: string; ValueData: {{00020424-0000-0000-C000-000000000046}
Root: HKLM; Subkey: SOFTWARE\Classes\Interface\{{3B37809A-EA99-11D1-8A30-00E029089FF3}\TypeLib; ValueType: string; ValueData: {{18BF4063-A8C4-11D1-AE5C-00600818410C}
Root: HKLM; Subkey: SOFTWARE\Classes\Interface\{{3B37809A-EA99-11D1-8A30-00E029089FF3}\TypeLib; ValueType: string; ValueName: Version; ValueData: 7.0

Root: HKLM; Subkey: SOFTWARE\Classes\Interface\{{3B37809B-EA99-11D1-8A30-00E029089FF3}; ValueType: string; ValueData: VBProjectHandler
Root: HKLM; Subkey: SOFTWARE\Classes\Interface\{{3B37809B-EA99-11D1-8A30-00E029089FF3}\ProxyStubClsid; ValueType: string; ValueData: {{00020424-0000-0000-C000-000000000046}
Root: HKLM; Subkey: SOFTWARE\Classes\Interface\{{3B37809B-EA99-11D1-8A30-00E029089FF3}\ProxyStubClsid32; ValueType: string; ValueData: {{00020424-0000-0000-C000-000000000046}
Root: HKLM; Subkey: SOFTWARE\Classes\Interface\{{3B37809B-EA99-11D1-8A30-00E029089FF3}\TypeLib; ValueType: string; ValueData: {{18BF4063-A8C4-11D1-AE5C-00600818410C}
Root: HKLM; Subkey: SOFTWARE\Classes\Interface\{{3B37809B-EA99-11D1-8A30-00E029089FF3}\TypeLib; ValueType: string; ValueName: Version; ValueData: 7.0

Root: HKLM; Subkey: SOFTWARE\Classes\Interface\{{3B37809C-EA99-11D1-8A30-00E029089FF3}; ValueType: string; ValueData: VBConnectionHandler
Root: HKLM; Subkey: SOFTWARE\Classes\Interface\{{3B37809C-EA99-11D1-8A30-00E029089FF3}\ProxyStubClsid; ValueType: string; ValueData: {{00020424-0000-0000-C000-000000000046}
Root: HKLM; Subkey: SOFTWARE\Classes\Interface\{{3B37809C-EA99-11D1-8A30-00E029089FF3}\ProxyStubClsid32; ValueType: string; ValueData: {{00020424-0000-0000-C000-000000000046}
Root: HKLM; Subkey: SOFTWARE\Classes\Interface\{{3B37809C-EA99-11D1-8A30-00E029089FF3}\TypeLib; ValueType: string; ValueData: {{18BF4063-A8C4-11D1-AE5C-00600818410C}
Root: HKLM; Subkey: SOFTWARE\Classes\Interface\{{3B37809C-EA99-11D1-8A30-00E029089FF3}\TypeLib; ValueType: string; ValueName: Version; ValueData: 7.0

Root: HKLM; Subkey: SOFTWARE\Classes\Interface\{{3B37809D-EA99-11D1-8A30-00E029089FF3}; ValueType: string; ValueData: VBTemplateHandler
Root: HKLM; Subkey: SOFTWARE\Classes\Interface\{{3B37809D-EA99-11D1-8A30-00E029089FF3}\ProxyStubClsid; ValueType: string; ValueData: {{00020424-0000-0000-C000-000000000046}
Root: HKLM; Subkey: SOFTWARE\Classes\Interface\{{3B37809D-EA99-11D1-8A30-00E029089FF3}\ProxyStubClsid32; ValueType: string; ValueData: {{00020424-0000-0000-C000-000000000046}
Root: HKLM; Subkey: SOFTWARE\Classes\Interface\{{3B37809D-EA99-11D1-8A30-00E029089FF3}\TypeLib; ValueType: string; ValueData: {{18BF4063-A8C4-11D1-AE5C-00600818410C}
Root: HKLM; Subkey: SOFTWARE\Classes\Interface\{{3B37809D-EA99-11D1-8A30-00E029089FF3}\TypeLib; ValueType: string; ValueName: Version; ValueData: 7.0

Root: HKLM; Subkey: SOFTWARE\Classes\Interface\{{3B3780A0-EA99-11D1-8A30-00E029089FF3}; ValueType: string; ValueData: JavaHandler
Root: HKLM; Subkey: SOFTWARE\Classes\Interface\{{3B3780A0-EA99-11D1-8A30-00E029089FF3}\ProxyStubClsid; ValueType: string; ValueData: {{00020424-0000-0000-C000-000000000046}
Root: HKLM; Subkey: SOFTWARE\Classes\Interface\{{3B3780A0-EA99-11D1-8A30-00E029089FF3}\ProxyStubClsid32; ValueType: string; ValueData: {{00020424-0000-0000-C000-000000000046}
Root: HKLM; Subkey: SOFTWARE\Classes\Interface\{{3B3780A0-EA99-11D1-8A30-00E029089FF3}\TypeLib; ValueType: string; ValueData: {{18BF4063-A8C4-11D1-AE5C-00600818410C}
Root: HKLM; Subkey: SOFTWARE\Classes\Interface\{{3B3780A0-EA99-11D1-8A30-00E029089FF3}\TypeLib; ValueType: string; ValueName: Version; ValueData: 7.0

Root: HKLM; Subkey: SOFTWARE\Classes\Interface\{{3EF35B90-3062-11D1-961F-00600818410C}\NumMethods; ValueType: string; ValueData: 16
Root: HKLM; Subkey: SOFTWARE\Classes\Interface\{{3FF69180-1582-11D1-9605-00600818410C}\NumMethods; ValueType: string; ValueData: 19

Root: HKLM; Subkey: SOFTWARE\Classes\Interface\{{426524E0-A41F-11CF-AB59-00AA00C091A1}; ValueType: string; ValueData: IDispTextEditor; Components: VisualCpp\CeTools
Root: HKLM; Subkey: SOFTWARE\Classes\Interface\{{426524E0-A41F-11CF-AB59-00AA00C091A1}\ProxyStubClsid; ValueType: string; ValueData: {{00020420-0000-0000-C000-000000000046}; Components: VisualCpp\CeTools
Root: HKLM; Subkey: SOFTWARE\Classes\Interface\{{426524E0-A41F-11CF-AB59-00AA00C091A1}\ProxyStubClsid32; ValueType: string; ValueData: {{00020420-0000-0000-C000-000000000046}; Components: VisualCpp\CeTools
Root: HKLM; Subkey: SOFTWARE\Classes\Interface\{{426524E0-A41F-11CF-AB59-00AA00C091A1}\TypeLib; ValueType: string; ValueData: {{2A6DF200-8240-11CF-AB59-00AA00C091A1}; Components: VisualCpp\CeTools
Root: HKLM; Subkey: SOFTWARE\Classes\Interface\{{426524E0-A41F-11CF-AB59-00AA00C091A1}\TypeLib; ValueType: string; ValueName: Version; ValueData: 6.0; Components: VisualCpp\CeTools

;Root: HKLM; Subkey: SOFTWARE\Classes\Interface\{{4748524D-D317-11D1-AFB6-006097C9A8F0}; ValueType: string; ValueData: CDBDevice
;Root: HKLM; Subkey: SOFTWARE\Classes\Interface\{{4748524F-D317-11D1-AFB6-006097C9A8F0}; ValueType: string; ValueData: CDBDevices
;Root: HKLM; Subkey: SOFTWARE\Classes\Interface\{{47485251-D317-11D1-AFB6-006097C9A8F0}; ValueType: string; ValueData: CStatusContainer
;Root: HKLM; Subkey: SOFTWARE\Classes\Interface\{{4748525A-D317-11D1-AFB6-006097C9A8F0}; ValueType: string; ValueData: CNewDatabaseWizard

Root: HKLM; Subkey: SOFTWARE\Classes\Interface\{{4D1F3146-833C-11CF-AB59-00AA00C091A1}; ValueType: string; ValueData: IDispTextSelection; Components: VisualCpp\CeTools
Root: HKLM; Subkey: SOFTWARE\Classes\Interface\{{4D1F3146-833C-11CF-AB59-00AA00C091A1}\ProxyStubClsid; ValueType: string; ValueData: {{00020420-0000-0000-C000-000000000046}; Components: VisualCpp\CeTools
Root: HKLM; Subkey: SOFTWARE\Classes\Interface\{{4D1F3146-833C-11CF-AB59-00AA00C091A1}\ProxyStubClsid32; ValueType: string; ValueData: {{00020420-0000-0000-C000-000000000046}; Components: VisualCpp\CeTools
Root: HKLM; Subkey: SOFTWARE\Classes\Interface\{{4D1F3146-833C-11CF-AB59-00AA00C091A1}\TypeLib; ValueType: string; ValueData: {{2A6DF200-8240-11CF-AB59-00AA00C091A1}; Components: VisualCpp\CeTools
Root: HKLM; Subkey: SOFTWARE\Classes\Interface\{{4D1F3146-833C-11CF-AB59-00AA00C091A1}\TypeLib; ValueType: string; ValueName: Version; ValueData: 6.0; Components: VisualCpp\CeTools

Root: HKLM; Subkey: SOFTWARE\Classes\Interface\{{4D1F3148-833C-11CF-AB59-00AA00C091A1}; ValueType: string; ValueData: IDispTextWindow; Components: VisualCpp\CeTools
Root: HKLM; Subkey: SOFTWARE\Classes\Interface\{{4D1F3148-833C-11CF-AB59-00AA00C091A1}\ProxyStubClsid; ValueType: string; ValueData: {{00020420-0000-0000-C000-000000000046}; Components: VisualCpp\CeTools
Root: HKLM; Subkey: SOFTWARE\Classes\Interface\{{4D1F3148-833C-11CF-AB59-00AA00C091A1}\ProxyStubClsid32; ValueType: string; ValueData: {{00020420-0000-0000-C000-000000000046}; Components: VisualCpp\CeTools
Root: HKLM; Subkey: SOFTWARE\Classes\Interface\{{4D1F3148-833C-11CF-AB59-00AA00C091A1}\TypeLib; ValueType: string; ValueData: {{2A6DF200-8240-11CF-AB59-00AA00C091A1}; Components: VisualCpp\CeTools
Root: HKLM; Subkey: SOFTWARE\Classes\Interface\{{4D1F3148-833C-11CF-AB59-00AA00C091A1}\TypeLib; ValueType: string; ValueName: Version; ValueData: 6.0; Components: VisualCpp\CeTools

#ifdef INSTALL_WNDTABS
;Root: HKLM; Subkey: SOFTWARE\Classes\Interface\{{4FFD4C59-A7F2-4B5F-9256-E199C4064088}; ValueType: string; ValueData: ICommands; Components: WndTabs
;Root: HKLM; Subkey: SOFTWARE\Classes\Interface\{{4FFD4C59-A7F2-4B5F-9256-E199C4064088}\ProxyStubClsid; ValueType: string; ValueData: {{00020424-0000-0000-C000-000000000046}; Components: WndTabs
;Root: HKLM; Subkey: SOFTWARE\Classes\Interface\{{4FFD4C59-A7F2-4B5F-9256-E199C4064088}\ProxyStubClsid32; ValueType: string; ValueData: {{00020424-0000-0000-C000-000000000046}; Components: WndTabs
;Root: HKLM; Subkey: SOFTWARE\Classes\Interface\{{4FFD4C59-A7F2-4B5F-9256-E199C4064088}\TypeLib; ValueType: string; ValueData: {{680356D7-4BEB-40DD-BF56-8A7D2D3F330F}; Components: WndTabs
;Root: HKLM; Subkey: SOFTWARE\Classes\Interface\{{4FFD4C59-A7F2-4B5F-9256-E199C4064088}\TypeLib; ValueType: string; ValueName: Version; ValueData: 1.0; Components: WndTabs
#endif

Root: HKLM; Subkey: SOFTWARE\Classes\Interface\{{520BEC60-31E8-11D0-B17F-00A0C91BC8ED}; ValueType: string; ValueData: IDispGenericProject; Components: VisualCpp\CeTools
Root: HKLM; Subkey: SOFTWARE\Classes\Interface\{{520BEC60-31E8-11D0-B17F-00A0C91BC8ED}\ProxyStubClsid; ValueType: string; ValueData: {{00020420-0000-0000-C000-000000000046}; Components: VisualCpp\CeTools
Root: HKLM; Subkey: SOFTWARE\Classes\Interface\{{520BEC60-31E8-11D0-B17F-00A0C91BC8ED}\ProxyStubClsid32; ValueType: string; ValueData: {{00020420-0000-0000-C000-000000000046}; Components: VisualCpp\CeTools
Root: HKLM; Subkey: SOFTWARE\Classes\Interface\{{520BEC60-31E8-11D0-B17F-00A0C91BC8ED}\TypeLib; ValueType: string; ValueData: {{B3CF8E20-19B6-11CF-8E4D-00AA004254C4}; Components: VisualCpp\CeTools
Root: HKLM; Subkey: SOFTWARE\Classes\Interface\{{520BEC60-31E8-11D0-B17F-00A0C91BC8ED}\TypeLib; ValueType: string; ValueName: Version; ValueData: 6.0; Components: VisualCpp\CeTools

Root: HKLM; Subkey: SOFTWARE\Classes\Interface\{{5774D191-96E1-11CF-9C00-00A0C90A632C}; ValueType: string; ValueData: IDispWindows; Components: VisualCpp\CeTools
Root: HKLM; Subkey: SOFTWARE\Classes\Interface\{{5774D191-96E1-11CF-9C00-00A0C90A632C}\ProxyStubClsid; ValueType: string; ValueData: {{00020420-0000-0000-C000-000000000046}; Components: VisualCpp\CeTools
Root: HKLM; Subkey: SOFTWARE\Classes\Interface\{{5774D191-96E1-11CF-9C00-00A0C90A632C}\ProxyStubClsid32; ValueType: string; ValueData: {{00020420-0000-0000-C000-000000000046}; Components: VisualCpp\CeTools
Root: HKLM; Subkey: SOFTWARE\Classes\Interface\{{5774D191-96E1-11CF-9C00-00A0C90A632C}\TypeLib; ValueType: string; ValueData: {{B3CF8E20-19B6-11CF-8E4D-00AA004254C4}; Components: VisualCpp\CeTools
Root: HKLM; Subkey: SOFTWARE\Classes\Interface\{{5774D191-96E1-11CF-9C00-00A0C90A632C}\TypeLib; ValueType: string; ValueName: Version; ValueData: 6.0; Components: VisualCpp\CeTools

Root: HKLM; Subkey: SOFTWARE\Classes\Interface\{{5C6F612B-0158-11D2-BBA0-00A0C9C9CCEE}; ValueType: string; ValueData: ITransport; Components: VisualCpp\CeTools
Root: HKLM; Subkey: SOFTWARE\Classes\Interface\{{5C6F612B-0158-11D2-BBA0-00A0C9C9CCEE}\NumMethods; ValueType: string; ValueData: 10; Components: VisualCpp\CeTools
Root: HKLM; Subkey: SOFTWARE\Classes\Interface\{{5C6F612B-0158-11D2-BBA0-00A0C9C9CCEE}\ProxyStubClsid32; ValueType: string; ValueData: {{2A4F783A-014E-11D2-BBA0-00A0C9C9CCEE}; Components: VisualCpp\CeTools
Root: HKLM; Subkey: SOFTWARE\Classes\Interface\{{5C6F612D-0158-11D2-BBA0-00A0C9C9CCEE}; ValueType: string; ValueData: ITransportConnection; Components: VisualCpp\CeTools
Root: HKLM; Subkey: SOFTWARE\Classes\Interface\{{5C6F612D-0158-11D2-BBA0-00A0C9C9CCEE}\NumMethods; ValueType: string; ValueData: 6; Components: VisualCpp\CeTools
Root: HKLM; Subkey: SOFTWARE\Classes\Interface\{{5C6F612D-0158-11D2-BBA0-00A0C9C9CCEE}\ProxyStubClsid32; ValueType: string; ValueData: {{2A4F783A-014E-11D2-BBA0-00A0C9C9CCEE}; Components: VisualCpp\CeTools

Root: HKLM; Subkey: SOFTWARE\Classes\Interface\{{6661B73F-9D9C-11D1-B931-00C04FBBC221}; ValueType: string; ValueData: VisualModelHandler
Root: HKLM; Subkey: SOFTWARE\Classes\Interface\{{6661B73F-9D9C-11D1-B931-00C04FBBC221}\Forward; ValueType: string; ValueData: {{9F65F6C4-06DA-11D2-8D70-00A0C98B28E2}
Root: HKLM; Subkey: SOFTWARE\Classes\Interface\{{6661B73F-9D9C-11D1-B931-00C04FBBC221}\ProxyStubClsid; ValueType: string; ValueData: {{00020424-0000-0000-C000-000000000046}
Root: HKLM; Subkey: SOFTWARE\Classes\Interface\{{6661B73F-9D9C-11D1-B931-00C04FBBC221}\ProxyStubClsid32; ValueType: string; ValueData: {{00020424-0000-0000-C000-000000000046}

Root: HKLM; Subkey: SOFTWARE\Classes\Interface\{{66B6C2DD-2590-11D2-BBA9-00A0C9C9CCEE}; ValueType: string; ValueData: IEnumCPU; Components: VisualCpp\CeTools
Root: HKLM; Subkey: SOFTWARE\Classes\Interface\{{66B6C2DD-2590-11D2-BBA9-00A0C9C9CCEE}\NumMethods; ValueType: string; ValueData: 9; Components: VisualCpp\CeTools
Root: HKLM; Subkey: SOFTWARE\Classes\Interface\{{66B6C2DD-2590-11D2-BBA9-00A0C9C9CCEE}\ProxyStubClsid32; ValueType: string; ValueData: {{2A4F783A-014E-11D2-BBA0-00A0C9C9CCEE}; Components: VisualCpp\CeTools

#ifdef INSTALL_WNDTABS
;Root: HKLM; Subkey: SOFTWARE\Classes\Interface\{{6A06C124-4748-11D1-BC91-0000010016A6}; ValueType: string; ValueData: "ICommands""; Components: WndTabs"
;Root: HKLM; Subkey: SOFTWARE\Classes\Interface\{{6A06C124-4748-11D1-BC91-0000010016A6}\ProxyStubClsid; ValueType: string; ValueData: {{00020424-0000-0000-C000-000000000046}; Components: WndTabs
;Root: HKLM; Subkey: SOFTWARE\Classes\Interface\{{6A06C124-4748-11D1-BC91-0000010016A6}\ProxyStubClsid32; ValueType: string; ValueData: {{00020424-0000-0000-C000-000000000046}; Components: WndTabs
;Root: HKLM; Subkey: SOFTWARE\Classes\Interface\{{6A06C124-4748-11D1-BC91-0000010016A6}\TypeLib; ValueType: string; ValueData: {{6A06C128-4748-11D1-BC91-0000010016A6}; Components: WndTabs
;Root: HKLM; Subkey: SOFTWARE\Classes\Interface\{{6A06C124-4748-11D1-BC91-0000010016A6}\TypeLib; ValueType: string; ValueName: Version; ValueData: 1.0; Components: WndTabs
#endif

;Root: HKLM; Subkey: SOFTWARE\Classes\Interface\{{77B42B8B-0000-11D2-991E-006097C99385}; ValueType: string; ValueData: CNavInfo; Components: VisualCpp\CeTools
;Root: HKLM; Subkey: SOFTWARE\Classes\Interface\{{77B42B8D-0000-11D2-991E-006097C99385}; ValueType: string; ValueData: CNavigation; Components: VisualCpp\CeTools
;Root: HKLM; Subkey: SOFTWARE\Classes\Interface\{{77B42B8F-0000-11D2-991E-006097C99385}; ValueType: string; ValueData: CHTMLStream; Components: VisualCpp\CeTools
;Root: HKLM; Subkey: SOFTWARE\Classes\Interface\{{77B42B91-0000-11D2-991E-006097C99385}; ValueType: string; ValueData: CHTMLStreams; Components: VisualCpp\CeTools
;Root: HKLM; Subkey: SOFTWARE\Classes\Interface\{{77B42B93-0000-11D2-991E-006097C99385}; ValueType: string; ValueData: CBitmap; Components: VisualCpp\CeTools
;Root: HKLM; Subkey: SOFTWARE\Classes\Interface\{{77B42B95-0000-11D2-991E-006097C99385}; ValueType: string; ValueData: CBitmaps; Components: VisualCpp\CeTools
;Root: HKLM; Subkey: SOFTWARE\Classes\Interface\{{77B42B97-0000-11D2-991E-006097C99385}; ValueType: string; ValueData: CGraphic; Components: VisualCpp\CeTools
;Root: HKLM; Subkey: SOFTWARE\Classes\Interface\{{77B42B99-0000-11D2-991E-006097C99385}; ValueType: string; ValueData: CGraphics; Components: VisualCpp\CeTools
;Root: HKLM; Subkey: SOFTWARE\Classes\Interface\{{77B42B9B-0000-11D2-991E-006097C99385}; ValueType: string; ValueData: CTheme; Components: VisualCpp\CeTools
;Root: HKLM; Subkey: SOFTWARE\Classes\Interface\{{77B42B9D-0000-11D2-991E-006097C99385}; ValueType: string; ValueData: CThemes; Components: VisualCpp\CeTools
;Root: HKLM; Subkey: SOFTWARE\Classes\Interface\{{77B42B9F-0000-11D2-991E-006097C99385}; ValueType: string; ValueData: CTemplate; Components: VisualCpp\CeTools
;Root: HKLM; Subkey: SOFTWARE\Classes\Interface\{{77B42BA1-0000-11D2-991E-006097C99385}; ValueType: string; ValueData: CTemplates; Components: VisualCpp\CeTools
;Root: HKLM; Subkey: SOFTWARE\Classes\Interface\{{77B42BA3-0000-11D2-991E-006097C99385}; ValueType: string; ValueData: CTemplateType; Components: VisualCpp\CeTools
;Root: HKLM; Subkey: SOFTWARE\Classes\Interface\{{77B42BA5-0000-11D2-991E-006097C99385}; ValueType: string; ValueData: CTemplateTypes; Components: VisualCpp\CeTools
;Root: HKLM; Subkey: SOFTWARE\Classes\Interface\{{77B42BA7-0000-11D2-991E-006097C99385}; ValueType: string; ValueData: CServerForms; Components: VisualCpp\CeTools
;Root: HKLM; Subkey: SOFTWARE\Classes\Interface\{{77B42BA9-0000-11D2-991E-006097C99385}; ValueType: string; ValueData: CStdError; Components: VisualCpp\CeTools
;Root: HKLM; Subkey: SOFTWARE\Classes\Interface\{{77B42BAB-0000-11D2-991E-006097C99385}; ValueType: string; ValueData: CStdErrors; Components: VisualCpp\CeTools
;Root: HKLM; Subkey: SOFTWARE\Classes\Interface\{{77B42BAD-0000-11D2-991E-006097C99385}; ValueType: string; ValueData: CWizardApp; Components: VisualCpp\CeTools
;Root: HKLM; Subkey: SOFTWARE\Classes\Interface\{{77B42BAF-0000-11D2-991E-006097C99385}; ValueType: string; ValueData: CString; Components: VisualCpp\CeTools
;Root: HKLM; Subkey: SOFTWARE\Classes\Interface\{{77B42BB1-0000-11D2-991E-006097C99385}; ValueType: string; ValueData: CStrings; Components: VisualCpp\CeTools
;Root: HKLM; Subkey: SOFTWARE\Classes\Interface\{{77B42BB3-0000-11D2-991E-006097C99385}; ValueType: string; ValueData: CReplacement; Components: VisualCpp\CeTools
;Root: HKLM; Subkey: SOFTWARE\Classes\Interface\{{77B42BB5-0000-11D2-991E-006097C99385}; ValueType: string; ValueData: CTables; Components: VisualCpp\CeTools
;Root: HKLM; Subkey: SOFTWARE\Classes\Interface\{{77B42BB7-0000-11D2-991E-006097C99385}; ValueType: string; ValueData: CError; Components: VisualCpp\CeTools
;Root: HKLM; Subkey: SOFTWARE\Classes\Interface\{{77B42BB9-0000-11D2-991E-006097C99385}; ValueType: string; ValueData: CErrors; Components: VisualCpp\CeTools
;Root: HKLM; Subkey: SOFTWARE\Classes\Interface\{{77B42BBB-0000-11D2-991E-006097C99385}; ValueType: string; ValueData: CDBManager; Components: VisualCpp\CeTools
;Root: HKLM; Subkey: SOFTWARE\Classes\Interface\{{77B42BBD-0000-11D2-991E-006097C99385}; ValueType: string; ValueData: CFields; Components: VisualCpp\CeTools
;Root: HKLM; Subkey: SOFTWARE\Classes\Interface\{{77B42BBF-0000-11D2-991E-006097C99385}; ValueType: string; ValueData: CTable; Components: VisualCpp\CeTools

;Root: HKLM; Subkey: SOFTWARE\Classes\Interface\{{77B42BC1-0000-11D2-991E-006097C99385}; ValueType: string; ValueData: CField; Components: VisualCpp\CeTools
Root: HKLM; Subkey: SOFTWARE\Classes\Interface\{{77B42BC1-0000-11D2-991E-006097C99385}\TypeLib; ValueType: string; ValueData: {{CBE51AA8-A410-11D1-80D0-006097C9987D}; Components: VisualCpp\ServicePack
Root: HKLM; Subkey: SOFTWARE\Classes\Interface\{{77B42BC1-0000-11D2-991E-006097C99385}\TypeLib; ValueType: string; ValueName: Version; ValueData: 1.0; Components: VisualCpp\ServicePack

;Root: HKLM; Subkey: SOFTWARE\Classes\Interface\{{77B42BC7-0000-11D2-991E-006097C99385}; ValueType: string; ValueData: CWebPage; Components: VisualCpp\CeTools
;Root: HKLM; Subkey: SOFTWARE\Classes\Interface\{{77B42BC9-0000-11D2-991E-006097C99385}; ValueType: string; ValueData: CWebPages; Components: VisualCpp\CeTools
;Root: HKLM; Subkey: SOFTWARE\Classes\Interface\{{77B42BCB-0000-11D2-991E-006097C99385}; ValueType: string; ValueData: CImage; Components: VisualCpp\CeTools
;Root: HKLM; Subkey: SOFTWARE\Classes\Interface\{{77B42BCD-0000-11D2-991E-006097C99385}; ValueType: string; ValueData: CImages; Components: VisualCpp\CeTools
;Root: HKLM; Subkey: SOFTWARE\Classes\Interface\{{77B42BCF-0000-11D2-991E-006097C99385}; ValueType: string; ValueData: CTreeview; Components: VisualCpp\CeTools
;Root: HKLM; Subkey: SOFTWARE\Classes\Interface\{{77B42BD4-0000-11D2-991E-006097C99385}; ValueType: string; ValueData: CFPServer; Components: VisualCpp\CeTools
;Root: HKLM; Subkey: SOFTWARE\Classes\Interface\{{77B42BDE-0000-11D2-991E-006097C99385}; ValueType: string; ValueData: CReplacements; Components: VisualCpp\CeTools
;Root: HKLM; Subkey: SOFTWARE\Classes\Interface\{{77B42BE0-0000-11D2-991E-006097C99385}; ValueType: string; ValueData: CThemeManager; Components: VisualCpp\CeTools
;Root: HKLM; Subkey: SOFTWARE\Classes\Interface\{{77B42BE2-0000-11D2-991E-006097C99385}; ValueType: string; ValueData: CLayoutManager; Components: VisualCpp\CeTools
;Root: HKLM; Subkey: SOFTWARE\Classes\Interface\{{77B42BE8-0000-11D2-991E-006097C99385}; ValueType: string; ValueData: CMultiPick; Components: VisualCpp\CeTools
;Root: HKLM; Subkey: SOFTWARE\Classes\Interface\{{77B42BEA-0000-11D2-991E-006097C99385}; ValueType: string; ValueData: CODBCConnection; Components: VisualCpp\CeTools

Root: HKLM; Subkey: SOFTWARE\Classes\Interface\{{87D4D2A0-8250-11CF-AB59-00AA00C091A1}; ValueType: string; ValueData: IDispTextDocument; Components: VisualCpp\CeTools
Root: HKLM; Subkey: SOFTWARE\Classes\Interface\{{87D4D2A0-8250-11CF-AB59-00AA00C091A1}\ProxyStubClsid; ValueType: string; ValueData: {{00020420-0000-0000-C000-000000000046}; Components: VisualCpp\CeTools
Root: HKLM; Subkey: SOFTWARE\Classes\Interface\{{87D4D2A0-8250-11CF-AB59-00AA00C091A1}\ProxyStubClsid32; ValueType: string; ValueData: {{00020420-0000-0000-C000-000000000046}; Components: VisualCpp\CeTools
Root: HKLM; Subkey: SOFTWARE\Classes\Interface\{{87D4D2A0-8250-11CF-AB59-00AA00C091A1}\TypeLib; ValueType: string; ValueData: {{2A6DF200-8240-11CF-AB59-00AA00C091A1}; Components: VisualCpp\CeTools
Root: HKLM; Subkey: SOFTWARE\Classes\Interface\{{87D4D2A0-8250-11CF-AB59-00AA00C091A1}\TypeLib; ValueType: string; ValueName: Version; ValueData: 6.0; Components: VisualCpp\CeTools

Root: HKLM; Subkey: SOFTWARE\Classes\Interface\{{8CA5A960-FC7D-11CF-927D-00A0C9138C45}; ValueType: string; ValueData: IGenericProject; Components: VisualCpp\CeTools
Root: HKLM; Subkey: SOFTWARE\Classes\Interface\{{8CA5A960-FC7D-11CF-927D-00A0C9138C45}\ProxyStubClsid; ValueType: string; ValueData: {{00020424-0000-0000-C000-000000000046}; Components: VisualCpp\CeTools
Root: HKLM; Subkey: SOFTWARE\Classes\Interface\{{8CA5A960-FC7D-11CF-927D-00A0C9138C45}\ProxyStubClsid32; ValueType: string; ValueData: {{00020424-0000-0000-C000-000000000046}; Components: VisualCpp\CeTools
Root: HKLM; Subkey: SOFTWARE\Classes\Interface\{{8CA5A960-FC7D-11CF-927D-00A0C9138C45}\TypeLib; ValueType: string; ValueData: {{96961265-A819-11CF-AD07-00A0C9034965}; Components: VisualCpp\CeTools
Root: HKLM; Subkey: SOFTWARE\Classes\Interface\{{8CA5A960-FC7D-11CF-927D-00A0C9138C45}\TypeLib; ValueType: string; ValueName: Version; ValueData: 6.0; Components: VisualCpp\CeTools

Root: HKLM; Subkey: SOFTWARE\Classes\Interface\{{8EA3F900-4A9F-11CF-8E4E-00AA004254C4}; ValueType: string; ValueData: IApplicationEvents; Components: VisualCpp\CeTools
Root: HKLM; Subkey: SOFTWARE\Classes\Interface\{{8EA3F900-4A9F-11CF-8E4E-00AA004254C4}\ProxyStubClsid; ValueType: string; ValueData: {{00020424-0000-0000-C000-000000000046}; Components: VisualCpp\CeTools
Root: HKLM; Subkey: SOFTWARE\Classes\Interface\{{8EA3F900-4A9F-11CF-8E4E-00AA004254C4}\ProxyStubClsid32; ValueType: string; ValueData: {{00020424-0000-0000-C000-000000000046}; Components: VisualCpp\CeTools
Root: HKLM; Subkey: SOFTWARE\Classes\Interface\{{8EA3F900-4A9F-11CF-8E4E-00AA004254C4}\TypeLib; ValueType: string; ValueData: {{B3CF8E20-19B6-11CF-8E4D-00AA004254C4}; Components: VisualCpp\CeTools
Root: HKLM; Subkey: SOFTWARE\Classes\Interface\{{8EA3F900-4A9F-11CF-8E4E-00AA004254C4}\TypeLib; ValueType: string; ValueName: Version; ValueData: 6.0; Components: VisualCpp\CeTools

Root: HKLM; Subkey: SOFTWARE\Classes\Interface\{{96961260-A819-11CF-AD07-00A0C9034965}; ValueType: string; ValueData: IConfigurations; Components: VisualCpp\CeTools
Root: HKLM; Subkey: SOFTWARE\Classes\Interface\{{96961260-A819-11CF-AD07-00A0C9034965}\ProxyStubClsid; ValueType: string; ValueData: {{00020424-0000-0000-C000-000000000046}; Components: VisualCpp\CeTools
Root: HKLM; Subkey: SOFTWARE\Classes\Interface\{{96961260-A819-11CF-AD07-00A0C9034965}\ProxyStubClsid32; ValueType: string; ValueData: {{00020424-0000-0000-C000-000000000046}; Components: VisualCpp\CeTools
Root: HKLM; Subkey: SOFTWARE\Classes\Interface\{{96961260-A819-11CF-AD07-00A0C9034965}\TypeLib; ValueType: string; ValueData: {{96961265-A819-11CF-AD07-00A0C9034965}; Components: VisualCpp\CeTools
Root: HKLM; Subkey: SOFTWARE\Classes\Interface\{{96961260-A819-11CF-AD07-00A0C9034965}\TypeLib; ValueType: string; ValueName: Version; ValueData: 6.0; Components: VisualCpp\CeTools

Root: HKLM; Subkey: SOFTWARE\Classes\Interface\{{96961261-A819-11CF-AD07-00A0C9034965}; ValueType: string; ValueData: IDispConfigurations; Components: VisualCpp\CeTools
Root: HKLM; Subkey: SOFTWARE\Classes\Interface\{{96961261-A819-11CF-AD07-00A0C9034965}\ProxyStubClsid; ValueType: string; ValueData: {{00020420-0000-0000-C000-000000000046}; Components: VisualCpp\CeTools
Root: HKLM; Subkey: SOFTWARE\Classes\Interface\{{96961261-A819-11CF-AD07-00A0C9034965}\ProxyStubClsid32; ValueType: string; ValueData: {{00020420-0000-0000-C000-000000000046}; Components: VisualCpp\CeTools
Root: HKLM; Subkey: SOFTWARE\Classes\Interface\{{96961261-A819-11CF-AD07-00A0C9034965}\TypeLib; ValueType: string; ValueData: {{96961265-A819-11CF-AD07-00A0C9034965}; Components: VisualCpp\CeTools
Root: HKLM; Subkey: SOFTWARE\Classes\Interface\{{96961261-A819-11CF-AD07-00A0C9034965}\TypeLib; ValueType: string; ValueName: Version; ValueData: 6.0; Components: VisualCpp\CeTools

Root: HKLM; Subkey: SOFTWARE\Classes\Interface\{{96961263-A819-11CF-AD07-00A0C9034965}; ValueType: string; ValueData: IConfiguration; Components: VisualCpp\CeTools
Root: HKLM; Subkey: SOFTWARE\Classes\Interface\{{96961263-A819-11CF-AD07-00A0C9034965}\ProxyStubClsid; ValueType: string; ValueData: {{00020424-0000-0000-C000-000000000046}; Components: VisualCpp\CeTools
Root: HKLM; Subkey: SOFTWARE\Classes\Interface\{{96961263-A819-11CF-AD07-00A0C9034965}\ProxyStubClsid32; ValueType: string; ValueData: {{00020424-0000-0000-C000-000000000046}; Components: VisualCpp\CeTools
Root: HKLM; Subkey: SOFTWARE\Classes\Interface\{{96961263-A819-11CF-AD07-00A0C9034965}\TypeLib; ValueType: string; ValueData: {{96961265-A819-11CF-AD07-00A0C9034965}; Components: VisualCpp\CeTools
Root: HKLM; Subkey: SOFTWARE\Classes\Interface\{{96961263-A819-11CF-AD07-00A0C9034965}\TypeLib; ValueType: string; ValueName: Version; ValueData: 6.0; Components: VisualCpp\CeTools

Root: HKLM; Subkey: SOFTWARE\Classes\Interface\{{96961264-A819-11CF-AD07-00A0C9034965}; ValueType: string; ValueData: IBuildProject; Components: VisualCpp\CeTools
Root: HKLM; Subkey: SOFTWARE\Classes\Interface\{{96961264-A819-11CF-AD07-00A0C9034965}\ProxyStubClsid; ValueType: string; ValueData: {{00020424-0000-0000-C000-000000000046}; Components: VisualCpp\CeTools
Root: HKLM; Subkey: SOFTWARE\Classes\Interface\{{96961264-A819-11CF-AD07-00A0C9034965}\ProxyStubClsid32; ValueType: string; ValueData: {{00020424-0000-0000-C000-000000000046}; Components: VisualCpp\CeTools
Root: HKLM; Subkey: SOFTWARE\Classes\Interface\{{96961264-A819-11CF-AD07-00A0C9034965}\TypeLib; ValueType: string; ValueData: {{96961265-A819-11CF-AD07-00A0C9034965}; Components: VisualCpp\CeTools
Root: HKLM; Subkey: SOFTWARE\Classes\Interface\{{96961264-A819-11CF-AD07-00A0C9034965}\TypeLib; ValueType: string; ValueName: Version; ValueData: 6.0; Components: VisualCpp\CeTools

Root: HKLM; Subkey: SOFTWARE\Classes\Interface\{{9B969EE9-EF39-11D1-8D6D-00A0C98B28E2}; ValueType: string; ValueData: Importer
Root: HKLM; Subkey: SOFTWARE\Classes\Interface\{{9B969EE9-EF39-11D1-8D6D-00A0C98B28E2}\ProxyStubClsid; ValueType: string; ValueData: {{00020424-0000-0000-C000-000000000046}
Root: HKLM; Subkey: SOFTWARE\Classes\Interface\{{9B969EE9-EF39-11D1-8D6D-00A0C98B28E2}\ProxyStubClsid32; ValueType: string; ValueData: {{00020424-0000-0000-C000-000000000046}
Root: HKLM; Subkey: SOFTWARE\Classes\Interface\{{9B969EE9-EF39-11D1-8D6D-00A0C98B28E2}\TypeLib; ValueType: string; ValueData: {{18BF4063-A8C4-11D1-AE5C-00600818410C}
Root: HKLM; Subkey: SOFTWARE\Classes\Interface\{{9B969EE9-EF39-11D1-8D6D-00A0C98B28E2}\TypeLib; ValueType: string; ValueName: Version; ValueData: 7.0
Root: HKLM; Subkey: SOFTWARE\Classes\Interface\{{9B969EED-EF39-11D1-8D6D-00A0C98B28E2}; ValueType: string; ValueData: RepTableItem
Root: HKLM; Subkey: SOFTWARE\Classes\Interface\{{9B969EED-EF39-11D1-8D6D-00A0C98B28E2}\ProxyStubClsid; ValueType: string; ValueData: {{00020424-0000-0000-C000-000000000046}
Root: HKLM; Subkey: SOFTWARE\Classes\Interface\{{9B969EED-EF39-11D1-8D6D-00A0C98B28E2}\ProxyStubClsid32; ValueType: string; ValueData: {{00020424-0000-0000-C000-000000000046}
Root: HKLM; Subkey: SOFTWARE\Classes\Interface\{{9B969EED-EF39-11D1-8D6D-00A0C98B28E2}\TypeLib; ValueType: string; ValueData: {{18BF4063-A8C4-11D1-AE5C-00600818410C}
Root: HKLM; Subkey: SOFTWARE\Classes\Interface\{{9B969EED-EF39-11D1-8D6D-00A0C98B28E2}\TypeLib; ValueType: string; ValueName: Version; ValueData: 7.0

;Root: HKLM; Subkey: SOFTWARE\Classes\Interface\{{9F65F6C4-06DA-11D2-8D70-00A0C98B28E2}; ValueType: string; ValueData: VisualModelHandler

Root: HKLM; Subkey: SOFTWARE\Classes\Interface\{{9FD2DF20-190D-11CF-8E4D-00AA004254C4}; ValueType: string; ValueData: IDispApplication; Components: VisualCpp\CeTools
Root: HKLM; Subkey: SOFTWARE\Classes\Interface\{{9FD2DF20-190D-11CF-8E4D-00AA004254C4}\ProxyStubClsid; ValueType: string; ValueData: {{00020420-0000-0000-C000-000000000046}; Components: VisualCpp\CeTools
Root: HKLM; Subkey: SOFTWARE\Classes\Interface\{{9FD2DF20-190D-11CF-8E4D-00AA004254C4}\ProxyStubClsid32; ValueType: string; ValueData: {{00020420-0000-0000-C000-000000000046}; Components: VisualCpp\CeTools
Root: HKLM; Subkey: SOFTWARE\Classes\Interface\{{9FD2DF20-190D-11CF-8E4D-00AA004254C4}\TypeLib; ValueType: string; ValueData: {{B3CF8E20-19B6-11CF-8E4D-00AA004254C4}; Components: VisualCpp\CeTools
Root: HKLM; Subkey: SOFTWARE\Classes\Interface\{{9FD2DF20-190D-11CF-8E4D-00AA004254C4}\TypeLib; ValueType: string; ValueName: Version; ValueData: 6.0; Components: VisualCpp\CeTools

;Root: HKLM; Subkey: SOFTWARE\Classes\Interface\{{A8F8E828-06DA-11D2-8D70-00A0C98B28E2}; ValueType: string; ValueData: AxBrowser

;Root: HKLM; Subkey: SOFTWARE\Classes\Interface\{{A8F8E82A-06DA-11D2-8D70-00A0C98B28E2}; ValueType: string; ValueData: AxBrowser

Root: HKLM; Subkey: SOFTWARE\Classes\Interface\{{A9E78841-19E7-11D1-9608-00600818410C}; ValueType: string; ValueData: ICabinetCallbacks
Root: HKLM; Subkey: SOFTWARE\Classes\Interface\{{A9E78841-19E7-11D1-9608-00600818410C}\NumMethods; ValueType: string; ValueData: 4
Root: HKLM; Subkey: SOFTWARE\Classes\Interface\{{A9E78841-19E7-11D1-9608-00600818410C}\ProxyStubClsid32; ValueType: string; ValueData: {{A9E78841-19E7-11D1-9608-00600818410C}

Root: HKLM; Subkey: SOFTWARE\Classes\Interface\{{AE166B02-A9A0-11CF-AD07-00A0C9034965}; ValueType: string; ValueData: IDispApplicationEvents; Components: VisualCpp\CeTools
Root: HKLM; Subkey: SOFTWARE\Classes\Interface\{{AE166B02-A9A0-11CF-AD07-00A0C9034965}\ProxyStubClsid; ValueType: string; ValueData: {{00020420-0000-0000-C000-000000000046}; Components: VisualCpp\CeTools
Root: HKLM; Subkey: SOFTWARE\Classes\Interface\{{AE166B02-A9A0-11CF-AD07-00A0C9034965}\ProxyStubClsid32; ValueType: string; ValueData: {{00020420-0000-0000-C000-000000000046}; Components: VisualCpp\CeTools
Root: HKLM; Subkey: SOFTWARE\Classes\Interface\{{AE166B02-A9A0-11CF-AD07-00A0C9034965}\TypeLib; ValueType: string; ValueData: {{B3CF8E20-19B6-11CF-8E4D-00AA004254C4}; Components: VisualCpp\CeTools
Root: HKLM; Subkey: SOFTWARE\Classes\Interface\{{AE166B02-A9A0-11CF-AD07-00A0C9034965}\TypeLib; ValueType: string; ValueName: Version; ValueData: 6.0; Components: VisualCpp\CeTools

;Root: HKLM; Subkey: SOFTWARE\Classes\Interface\{{AEB7F2FB-06DA-11D2-8D70-00A0C98B28E2}; ValueType: string; ValueData: IResource

Root: HKLM; Subkey: SOFTWARE\Classes\Interface\{{C0002F81-AE2E-11CF-AD07-00A0C9034965}; ValueType: string; ValueData: IDSAddIn; Components: VisualCpp\CeTools
Root: HKLM; Subkey: SOFTWARE\Classes\Interface\{{C0002F81-AE2E-11CF-AD07-00A0C9034965}\ProxyStubClsid; ValueType: string; ValueData: {{00020424-0000-0000-C000-000000000046}; Components: VisualCpp\CeTools
Root: HKLM; Subkey: SOFTWARE\Classes\Interface\{{C0002F81-AE2E-11CF-AD07-00A0C9034965}\ProxyStubClsid32; ValueType: string; ValueData: {{00020424-0000-0000-C000-000000000046}; Components: VisualCpp\CeTools
Root: HKLM; Subkey: SOFTWARE\Classes\Interface\{{C0002F81-AE2E-11CF-AD07-00A0C9034965}\TypeLib; ValueType: string; ValueData: {{B3CF8E20-19B6-11CF-8E4D-00AA004254C4}; Components: VisualCpp\CeTools
Root: HKLM; Subkey: SOFTWARE\Classes\Interface\{{C0002F81-AE2E-11CF-AD07-00A0C9034965}\TypeLib; ValueType: string; ValueName: Version; ValueData: 6.0; Components: VisualCpp\CeTools

Root: HKLM; Subkey: SOFTWARE\Classes\Interface\{{CF1B2C10-3772-11D1-962B-00600818410C}\NumMethods; ValueType: string; ValueData: 12

Root: HKLM; Subkey: SOFTWARE\Classes\Interface\{{DA438BAA-FA87-11D1-BB9E-00A0C9C9CCEE}; ValueType: string; ValueData: IConnection; Components: VisualCpp\CeTools
Root: HKLM; Subkey: SOFTWARE\Classes\Interface\{{DA438BAA-FA87-11D1-BB9E-00A0C9C9CCEE}\NumMethods; ValueType: string; ValueData: 19; Components: VisualCpp\CeTools
Root: HKLM; Subkey: SOFTWARE\Classes\Interface\{{DA438BAA-FA87-11D1-BB9E-00A0C9C9CCEE}\ProxyStubClsid32; ValueType: string; ValueData: {{2A4F783A-014E-11D2-BBA0-00A0C9C9CCEE}; Components: VisualCpp\CeTools

Root: HKLM; Subkey: SOFTWARE\Classes\Interface\{{DA438BB0-FA87-11D1-BB9E-00A0C9C9CCEE}; ValueType: string; ValueData: IConnectionStream; Components: VisualCpp\CeTools
Root: HKLM; Subkey: SOFTWARE\Classes\Interface\{{DA438BB0-FA87-11D1-BB9E-00A0C9C9CCEE}\NumMethods; ValueType: string; ValueData: 9; Components: VisualCpp\CeTools
Root: HKLM; Subkey: SOFTWARE\Classes\Interface\{{DA438BB0-FA87-11D1-BB9E-00A0C9C9CCEE}\ProxyStubClsid32; ValueType: string; ValueData: {{2A4F783A-014E-11D2-BBA0-00A0C9C9CCEE}; Components: VisualCpp\CeTools

Root: HKLM; Subkey: SOFTWARE\Classes\Interface\{{DA438BB3-FA87-11D1-BB9E-00A0C9C9CCEE}; ValueType: string; ValueData: ICallBack; Components: VisualCpp\CeTools
Root: HKLM; Subkey: SOFTWARE\Classes\Interface\{{DA438BB3-FA87-11D1-BB9E-00A0C9C9CCEE}\NumMethods; ValueType: string; ValueData: 10; Components: VisualCpp\CeTools
Root: HKLM; Subkey: SOFTWARE\Classes\Interface\{{DA438BB3-FA87-11D1-BB9E-00A0C9C9CCEE}\ProxyStubClsid32; ValueType: string; ValueData: {{2A4F783A-014E-11D2-BBA0-00A0C9C9CCEE}; Components: VisualCpp\CeTools

Root: HKLM; Subkey: SOFTWARE\Classes\Interface\{{DA438BC2-FA87-11D1-BB9E-00A0C9C9CCEE}; ValueType: string; ValueData: IPlatformManagerConfig; Components: VisualCpp\CeTools
Root: HKLM; Subkey: SOFTWARE\Classes\Interface\{{DA438BC2-FA87-11D1-BB9E-00A0C9C9CCEE}\NumMethods; ValueType: string; ValueData: 11; Components: VisualCpp\CeTools
Root: HKLM; Subkey: SOFTWARE\Classes\Interface\{{DA438BC2-FA87-11D1-BB9E-00A0C9C9CCEE}\ProxyStubClsid32; ValueType: string; ValueData: {{2A4F783A-014E-11D2-BBA0-00A0C9C9CCEE}; Components: VisualCpp\CeTools

Root: HKLM; Subkey: SOFTWARE\Classes\Interface\{{DA438BC7-FA87-11D1-BB9E-00A0C9C9CCEE}; ValueType: string; ValueData: IPlatformConfig; Components: VisualCpp\CeTools
Root: HKLM; Subkey: SOFTWARE\Classes\Interface\{{DA438BC7-FA87-11D1-BB9E-00A0C9C9CCEE}\NumMethods; ValueType: string; ValueData: 15; Components: VisualCpp\CeTools
Root: HKLM; Subkey: SOFTWARE\Classes\Interface\{{DA438BC7-FA87-11D1-BB9E-00A0C9C9CCEE}\ProxyStubClsid32; ValueType: string; ValueData: {{2A4F783A-014E-11D2-BBA0-00A0C9C9CCEE}; Components: VisualCpp\CeTools

Root: HKLM; Subkey: SOFTWARE\Classes\Interface\{{DA438BCA-FA87-11D1-BB9E-00A0C9C9CCEE}; ValueType: string; ValueData: IRemoteDeviceConfig; Components: VisualCpp\CeTools
Root: HKLM; Subkey: SOFTWARE\Classes\Interface\{{DA438BCA-FA87-11D1-BB9E-00A0C9C9CCEE}\NumMethods; ValueType: string; ValueData: 7; Components: VisualCpp\CeTools
Root: HKLM; Subkey: SOFTWARE\Classes\Interface\{{DA438BCA-FA87-11D1-BB9E-00A0C9C9CCEE}\ProxyStubClsid32; ValueType: string; ValueData: {{2A4F783A-014E-11D2-BBA0-00A0C9C9CCEE}; Components: VisualCpp\CeTools

Root: HKLM; Subkey: SOFTWARE\Classes\Interface\{{DA438BCD-FA87-11D1-BB9E-00A0C9C9CCEE}; ValueType: string; ValueData: IEnumComponent; Components: VisualCpp\CeTools
Root: HKLM; Subkey: SOFTWARE\Classes\Interface\{{DA438BCD-FA87-11D1-BB9E-00A0C9C9CCEE}\NumMethods; ValueType: string; ValueData: 9; Components: VisualCpp\CeTools
Root: HKLM; Subkey: SOFTWARE\Classes\Interface\{{DA438BCD-FA87-11D1-BB9E-00A0C9C9CCEE}\ProxyStubClsid32; ValueType: string; ValueData: {{2A4F783A-014E-11D2-BBA0-00A0C9C9CCEE}; Components: VisualCpp\CeTools

Root: HKLM; Subkey: SOFTWARE\Classes\Interface\{{DFAC7C40-A810-11CF-AD07-00A0C9034965}; ValueType: string; ValueData: IDispProjects; Components: VisualCpp\CeTools
Root: HKLM; Subkey: SOFTWARE\Classes\Interface\{{DFAC7C40-A810-11CF-AD07-00A0C9034965}\ProxyStubClsid; ValueType: string; ValueData: {{00020420-0000-0000-C000-000000000046}; Components: VisualCpp\CeTools
Root: HKLM; Subkey: SOFTWARE\Classes\Interface\{{DFAC7C40-A810-11CF-AD07-00A0C9034965}\ProxyStubClsid32; ValueType: string; ValueData: {{00020420-0000-0000-C000-000000000046}; Components: VisualCpp\CeTools
Root: HKLM; Subkey: SOFTWARE\Classes\Interface\{{DFAC7C40-A810-11CF-AD07-00A0C9034965}\TypeLib; ValueType: string; ValueData: {{B3CF8E20-19B6-11CF-8E4D-00AA004254C4}; Components: VisualCpp\CeTools
Root: HKLM; Subkey: SOFTWARE\Classes\Interface\{{DFAC7C40-A810-11CF-AD07-00A0C9034965}\TypeLib; ValueType: string; ValueName: Version; ValueData: 6.0; Components: VisualCpp\CeTools

Root: HKLM; Subkey: SOFTWARE\Classes\Interface\{{E0E270C0-C0BE-11D0-8FE4-00A0C90A6341}; ValueType: string; ValueData: OLEDBSimpleProvider
Root: HKLM; Subkey: SOFTWARE\Classes\Interface\{{E0E270C0-C0BE-11D0-8FE4-00A0C90A6341}\TypeLib; ValueType: string; ValueData: {{E0E270C2-C0BE-11D0-8FE4-00A0C90A6341}; Components: VisualCpp\CeTools
Root: HKLM; Subkey: SOFTWARE\Classes\Interface\{{E0E270C0-C0BE-11D0-8FE4-00A0C90A6341}\TypeLib; ValueType: string; ValueName: Version; ValueData: 1.5; Components: VisualCpp\CeTools

Root: HKLM; Subkey: SOFTWARE\Classes\Interface\{{E0E270C1-C0BE-11D0-8FE4-00A0C90A6341}\ProxyStubClsid; ValueType: string; ValueData: {{00020424-0000-0000-C000-000000000046}
Root: HKLM; Subkey: SOFTWARE\Classes\Interface\{{E0E270C1-C0BE-11D0-8FE4-00A0C90A6341}\ProxyStubClsid32; ValueType: string; ValueData: {{00020424-0000-0000-C000-000000000046}
Root: HKLM; Subkey: SOFTWARE\Classes\Interface\{{E0E270C1-C0BE-11D0-8FE4-00A0C90A6341}\TypeLib; ValueType: string; ValueData: {{E0E270C2-C0BE-11D0-8FE4-00A0C90A6341}
Root: HKLM; Subkey: SOFTWARE\Classes\Interface\{{E0E270C1-C0BE-11D0-8FE4-00A0C90A6341}\TypeLib; ValueType: string; ValueName: Version; ValueData: 1.5

Root: HKLM; Subkey: SOFTWARE\Classes\Interface\{{E1870221-933A-11CF-9BF9-00A0C90A632C}; ValueType: string; ValueData: IDispGenericDocument; Components: VisualCpp\CeTools
Root: HKLM; Subkey: SOFTWARE\Classes\Interface\{{E1870221-933A-11CF-9BF9-00A0C90A632C}\ProxyStubClsid; ValueType: string; ValueData: {{00020420-0000-0000-C000-000000000046}; Components: VisualCpp\CeTools
Root: HKLM; Subkey: SOFTWARE\Classes\Interface\{{E1870221-933A-11CF-9BF9-00A0C90A632C}\ProxyStubClsid32; ValueType: string; ValueData: {{00020420-0000-0000-C000-000000000046}; Components: VisualCpp\CeTools
Root: HKLM; Subkey: SOFTWARE\Classes\Interface\{{E1870221-933A-11CF-9BF9-00A0C90A632C}\TypeLib; ValueType: string; ValueData: {{B3CF8E20-19B6-11CF-8E4D-00AA004254C4}; Components: VisualCpp\CeTools
Root: HKLM; Subkey: SOFTWARE\Classes\Interface\{{E1870221-933A-11CF-9BF9-00A0C90A632C}\TypeLib; ValueType: string; ValueName: Version; ValueData: 6.0; Components: VisualCpp\CeTools

Root: HKLM; Subkey: SOFTWARE\Classes\Interface\{{E1870223-933A-11CF-9BF9-00A0C90A632C}; ValueType: string; ValueData: IDispGenericWindow; Components: VisualCpp\CeTools
Root: HKLM; Subkey: SOFTWARE\Classes\Interface\{{E1870223-933A-11CF-9BF9-00A0C90A632C}\ProxyStubClsid; ValueType: string; ValueData: {{00020420-0000-0000-C000-000000000046}; Components: VisualCpp\CeTools
Root: HKLM; Subkey: SOFTWARE\Classes\Interface\{{E1870223-933A-11CF-9BF9-00A0C90A632C}\ProxyStubClsid32; ValueType: string; ValueData: {{00020420-0000-0000-C000-000000000046}; Components: VisualCpp\CeTools
Root: HKLM; Subkey: SOFTWARE\Classes\Interface\{{E1870223-933A-11CF-9BF9-00A0C90A632C}\TypeLib; ValueType: string; ValueData: {{B3CF8E20-19B6-11CF-8E4D-00AA004254C4}; Components: VisualCpp\CeTools
Root: HKLM; Subkey: SOFTWARE\Classes\Interface\{{E1870223-933A-11CF-9BF9-00A0C90A632C}\TypeLib; ValueType: string; ValueName: Version; ValueData: 6.0; Components: VisualCpp\CeTools

Root: HKLM; Subkey: SOFTWARE\Classes\Interface\{{E1EBB0FC-00A2-11D2-BBA0-00A0C9C9CCEE}; ValueType: string; ValueData: IServer; Components: VisualCpp\CeTools
Root: HKLM; Subkey: SOFTWARE\Classes\Interface\{{E1EBB0FC-00A2-11D2-BBA0-00A0C9C9CCEE}\NumMethods; ValueType: string; ValueData: 7; Components: VisualCpp\CeTools
Root: HKLM; Subkey: SOFTWARE\Classes\Interface\{{E1EBB0FC-00A2-11D2-BBA0-00A0C9C9CCEE}\ProxyStubClsid32; ValueType: string; ValueData: {{2A4F783A-014E-11D2-BBA0-00A0C9C9CCEE}; Components: VisualCpp\CeTools

Root: HKLM; Subkey: SOFTWARE\Classes\Interface\{{E1EBB0FE-00A2-11D2-BBA0-00A0C9C9CCEE}; ValueType: string; ValueData: IServerConnection; Components: VisualCpp\CeTools
Root: HKLM; Subkey: SOFTWARE\Classes\Interface\{{E1EBB0FE-00A2-11D2-BBA0-00A0C9C9CCEE}\NumMethods; ValueType: string; ValueData: 7; Components: VisualCpp\CeTools
Root: HKLM; Subkey: SOFTWARE\Classes\Interface\{{E1EBB0FE-00A2-11D2-BBA0-00A0C9C9CCEE}\ProxyStubClsid32; ValueType: string; ValueData: {{2A4F783A-014E-11D2-BBA0-00A0C9C9CCEE}; Components: VisualCpp\CeTools

Root: HKLM; Subkey: SOFTWARE\Classes\Interface\{{E9EB1AE1-89A8-11CF-9BE8-00A0C90A632C}; ValueType: string; ValueData: IDispDocuments; Components: VisualCpp\CeTools
Root: HKLM; Subkey: SOFTWARE\Classes\Interface\{{E9EB1AE1-89A8-11CF-9BE8-00A0C90A632C}\ProxyStubClsid; ValueType: string; ValueData: {{00020420-0000-0000-C000-000000000046}; Components: VisualCpp\CeTools
Root: HKLM; Subkey: SOFTWARE\Classes\Interface\{{E9EB1AE1-89A8-11CF-9BE8-00A0C90A632C}\ProxyStubClsid32; ValueType: string; ValueData: {{00020420-0000-0000-C000-000000000046}; Components: VisualCpp\CeTools
Root: HKLM; Subkey: SOFTWARE\Classes\Interface\{{E9EB1AE1-89A8-11CF-9BE8-00A0C90A632C}\TypeLib; ValueType: string; ValueData: {{B3CF8E20-19B6-11CF-8E4D-00AA004254C4}; Components: VisualCpp\CeTools
Root: HKLM; Subkey: SOFTWARE\Classes\Interface\{{E9EB1AE1-89A8-11CF-9BE8-00A0C90A632C}\TypeLib; ValueType: string; ValueName: Version; ValueData: 6.0; Components: VisualCpp\CeTools

Root: HKLM; Subkey: SOFTWARE\Classes\Interface\{{EC1D73A1-8CC4-11CF-9BE9-00A0C90A632C}; ValueType: string; ValueData: IApplication; Components: VisualCpp\CeTools
Root: HKLM; Subkey: SOFTWARE\Classes\Interface\{{EC1D73A1-8CC4-11CF-9BE9-00A0C90A632C}\ProxyStubClsid; ValueType: string; ValueData: {{00020424-0000-0000-C000-000000000046}; Components: VisualCpp\CeTools
Root: HKLM; Subkey: SOFTWARE\Classes\Interface\{{EC1D73A1-8CC4-11CF-9BE9-00A0C90A632C}\ProxyStubClsid32; ValueType: string; ValueData: {{00020424-0000-0000-C000-000000000046}; Components: VisualCpp\CeTools
Root: HKLM; Subkey: SOFTWARE\Classes\Interface\{{EC1D73A1-8CC4-11CF-9BE9-00A0C90A632C}\TypeLib; ValueType: string; ValueData: {{B3CF8E20-19B6-11CF-8E4D-00AA004254C4}; Components: VisualCpp\CeTools
Root: HKLM; Subkey: SOFTWARE\Classes\Interface\{{EC1D73A1-8CC4-11CF-9BE9-00A0C90A632C}\TypeLib; ValueType: string; ValueName: Version; ValueData: 6.0; Components: VisualCpp\CeTools

Root: HKLM; Subkey: SOFTWARE\Classes\Interface\{{F384D882-F9AA-11D1-BB9E-00A0C9C9CCEE}; ValueType: string; ValueData: IPlatformManager; Components: VisualCpp\CeTools
Root: HKLM; Subkey: SOFTWARE\Classes\Interface\{{F384D882-F9AA-11D1-BB9E-00A0C9C9CCEE}\NumMethods; ValueType: string; ValueData: 9; Components: VisualCpp\CeTools
Root: HKLM; Subkey: SOFTWARE\Classes\Interface\{{F384D882-F9AA-11D1-BB9E-00A0C9C9CCEE}\ProxyStubClsid32; ValueType: string; ValueData: {{2A4F783A-014E-11D2-BBA0-00A0C9C9CCEE}; Components: VisualCpp\CeTools

Root: HKLM; Subkey: SOFTWARE\Classes\Interface\{{F384D885-F9AA-11D1-BB9E-00A0C9C9CCEE}; ValueType: string; ValueData: IEnumPlatformCE; Components: VisualCpp\CeTools
Root: HKLM; Subkey: SOFTWARE\Classes\Interface\{{F384D885-F9AA-11D1-BB9E-00A0C9C9CCEE}\NumMethods; ValueType: string; ValueData: 9; Components: VisualCpp\CeTools
Root: HKLM; Subkey: SOFTWARE\Classes\Interface\{{F384D885-F9AA-11D1-BB9E-00A0C9C9CCEE}\ProxyStubClsid32; ValueType: string; ValueData: {{2A4F783A-014E-11D2-BBA0-00A0C9C9CCEE}; Components: VisualCpp\CeTools

Root: HKLM; Subkey: SOFTWARE\Classes\Interface\{{F384D888-F9AA-11D1-BB9E-00A0C9C9CCEE}; ValueType: string; ValueData: IPlatformCE; Components: VisualCpp\CeTools
Root: HKLM; Subkey: SOFTWARE\Classes\Interface\{{F384D888-F9AA-11D1-BB9E-00A0C9C9CCEE}\NumMethods; ValueType: string; ValueData: 13; Components: VisualCpp\CeTools
Root: HKLM; Subkey: SOFTWARE\Classes\Interface\{{F384D888-F9AA-11D1-BB9E-00A0C9C9CCEE}\ProxyStubClsid32; ValueType: string; ValueData: {{2A4F783A-014E-11D2-BBA0-00A0C9C9CCEE}; Components: VisualCpp\CeTools

Root: HKLM; Subkey: SOFTWARE\Classes\Interface\{{F384D88B-F9AA-11D1-BB9E-00A0C9C9CCEE}; ValueType: string; ValueData: IRemoteDevice; Components: VisualCpp\CeTools
Root: HKLM; Subkey: SOFTWARE\Classes\Interface\{{F384D88B-F9AA-11D1-BB9E-00A0C9C9CCEE}\NumMethods; ValueType: string; ValueData: 11; Components: VisualCpp\CeTools
Root: HKLM; Subkey: SOFTWARE\Classes\Interface\{{F384D88B-F9AA-11D1-BB9E-00A0C9C9CCEE}\ProxyStubClsid32; ValueType: string; ValueData: {{2A4F783A-014E-11D2-BBA0-00A0C9C9CCEE}; Components: VisualCpp\CeTools

Root: HKLM; Subkey: SOFTWARE\Classes\Interface\{{F384D88E-F9AA-11D1-BB9E-00A0C9C9CCEE}; ValueType: string; ValueData: IEnumDevice; Components: VisualCpp\CeTools
Root: HKLM; Subkey: SOFTWARE\Classes\Interface\{{F384D88E-F9AA-11D1-BB9E-00A0C9C9CCEE}\NumMethods; ValueType: string; ValueData: 9; Components: VisualCpp\CeTools
Root: HKLM; Subkey: SOFTWARE\Classes\Interface\{{F384D88E-F9AA-11D1-BB9E-00A0C9C9CCEE}\ProxyStubClsid32; ValueType: string; ValueData: {{2A4F783A-014E-11D2-BBA0-00A0C9C9CCEE}; Components: VisualCpp\CeTools

Root: HKLM; Subkey: SOFTWARE\Classes\Interface\{{F384D891-F9AA-11D1-BB9E-00A0C9C9CCEE}; ValueType: string; ValueData: IEnumProperty; Components: VisualCpp\CeTools
Root: HKLM; Subkey: SOFTWARE\Classes\Interface\{{F384D891-F9AA-11D1-BB9E-00A0C9C9CCEE}\NumMethods; ValueType: string; ValueData: 9; Components: VisualCpp\CeTools
Root: HKLM; Subkey: SOFTWARE\Classes\Interface\{{F384D891-F9AA-11D1-BB9E-00A0C9C9CCEE}\ProxyStubClsid32; ValueType: string; ValueData: {{2A4F783A-014E-11D2-BBA0-00A0C9C9CCEE}; Components: VisualCpp\CeTools

Root: HKLM; Subkey: SOFTWARE\Classes\Interface\{{F384D894-F9AA-11D1-BB9E-00A0C9C9CCEE}; ValueType: string; ValueData: IProperty; Components: VisualCpp\CeTools
Root: HKLM; Subkey: SOFTWARE\Classes\Interface\{{F384D894-F9AA-11D1-BB9E-00A0C9C9CCEE}\NumMethods; ValueType: string; ValueData: 12; Components: VisualCpp\CeTools
Root: HKLM; Subkey: SOFTWARE\Classes\Interface\{{F384D894-F9AA-11D1-BB9E-00A0C9C9CCEE}\ProxyStubClsid32; ValueType: string; ValueData: {{2A4F783A-014E-11D2-BBA0-00A0C9C9CCEE}; Components: VisualCpp\CeTools

Root: HKLM; Subkey: SOFTWARE\Classes\Interface\{{F384D897-F9AA-11D1-BB9E-00A0C9C9CCEE}; ValueType: string; ValueData: IEnumPropInfo; Components: VisualCpp\CeTools
Root: HKLM; Subkey: SOFTWARE\Classes\Interface\{{F384D897-F9AA-11D1-BB9E-00A0C9C9CCEE}\NumMethods; ValueType: string; ValueData: 9; Components: VisualCpp\CeTools
Root: HKLM; Subkey: SOFTWARE\Classes\Interface\{{F384D897-F9AA-11D1-BB9E-00A0C9C9CCEE}\ProxyStubClsid32; ValueType: string; ValueData: {{2A4F783A-014E-11D2-BBA0-00A0C9C9CCEE}; Components: VisualCpp\CeTools

Root: HKLM; Subkey: SOFTWARE\Classes\Interface\{{F77D4DF3-1FBF-11D1-960B-00600818410C}\NumMethods; ValueType: string; ValueData: 12
Root: HKLM; Subkey: SOFTWARE\Classes\Interface\{{F77D4DF5-1FBF-11D1-960B-00600818410C}\NumMethods; ValueType: string; ValueData: 15

Root: HKLM; Subkey: SOFTWARE\Classes\Interface\{{FB7FDAE1-89B8-11CF-9BE8-00A0C90A632C}; ValueType: string; ValueData: IGenericDocument; Components: VisualCpp\CeTools
Root: HKLM; Subkey: SOFTWARE\Classes\Interface\{{FB7FDAE1-89B8-11CF-9BE8-00A0C90A632C}\ProxyStubClsid; ValueType: string; ValueData: {{00020424-0000-0000-C000-000000000046}; Components: VisualCpp\CeTools
Root: HKLM; Subkey: SOFTWARE\Classes\Interface\{{FB7FDAE1-89B8-11CF-9BE8-00A0C90A632C}\ProxyStubClsid32; ValueType: string; ValueData: {{00020424-0000-0000-C000-000000000046}; Components: VisualCpp\CeTools
Root: HKLM; Subkey: SOFTWARE\Classes\Interface\{{FB7FDAE1-89B8-11CF-9BE8-00A0C90A632C}\TypeLib; ValueType: string; ValueData: {{96961265-A819-11CF-AD07-00A0C9034965}; Components: VisualCpp\CeTools
Root: HKLM; Subkey: SOFTWARE\Classes\Interface\{{FB7FDAE1-89B8-11CF-9BE8-00A0C90A632C}\TypeLib; ValueType: string; ValueName: Version; ValueData: 6.0; Components: VisualCpp\CeTools

Root: HKLM; Subkey: SOFTWARE\Classes\Interface\{{FB7FDAE3-89B8-11CF-9BE8-00A0C90A632C}; ValueType: string; ValueData: IDocuments; Components: VisualCpp\CeTools
Root: HKLM; Subkey: SOFTWARE\Classes\Interface\{{FB7FDAE3-89B8-11CF-9BE8-00A0C90A632C}\ProxyStubClsid; ValueType: string; ValueData: {{00020424-0000-0000-C000-000000000046}; Components: VisualCpp\CeTools
Root: HKLM; Subkey: SOFTWARE\Classes\Interface\{{FB7FDAE3-89B8-11CF-9BE8-00A0C90A632C}\ProxyStubClsid32; ValueType: string; ValueData: {{00020424-0000-0000-C000-000000000046}; Components: VisualCpp\CeTools
Root: HKLM; Subkey: SOFTWARE\Classes\Interface\{{FB7FDAE3-89B8-11CF-9BE8-00A0C90A632C}\TypeLib; ValueType: string; ValueData: {{B3CF8E20-19B6-11CF-8E4D-00AA004254C4}; Components: VisualCpp\CeTools
Root: HKLM; Subkey: SOFTWARE\Classes\Interface\{{FB7FDAE3-89B8-11CF-9BE8-00A0C90A632C}\TypeLib; ValueType: string; ValueName: Version; ValueData: 6.0; Components: VisualCpp\CeTools

Root: HKLM; Subkey: SOFTWARE\Classes\Interface\{{FD20FC80-A9D2-11CF-9C13-00A0C90A632C}; ValueType: string; ValueData: IGenericWindow; Components: VisualCpp\CeTools
Root: HKLM; Subkey: SOFTWARE\Classes\Interface\{{FD20FC80-A9D2-11CF-9C13-00A0C90A632C}\ProxyStubClsid; ValueType: string; ValueData: {{00020424-0000-0000-C000-000000000046}; Components: VisualCpp\CeTools
Root: HKLM; Subkey: SOFTWARE\Classes\Interface\{{FD20FC80-A9D2-11CF-9C13-00A0C90A632C}\ProxyStubClsid32; ValueType: string; ValueData: {{00020424-0000-0000-C000-000000000046}; Components: VisualCpp\CeTools
Root: HKLM; Subkey: SOFTWARE\Classes\Interface\{{FD20FC80-A9D2-11CF-9C13-00A0C90A632C}\TypeLib; ValueType: string; ValueData: {{96961265-A819-11CF-AD07-00A0C9034965}; Components: VisualCpp\CeTools
Root: HKLM; Subkey: SOFTWARE\Classes\Interface\{{FD20FC80-A9D2-11CF-9C13-00A0C90A632C}\TypeLib; ValueType: string; ValueName: Version; ValueData: 6.0; Components: VisualCpp\CeTools

Root: HKLM; Subkey: SOFTWARE\Classes\Licenses; ValueType: string; ValueData: Licensing: Copying the keys may be a violation of established copyrights.
Root: HKLM; Subkey: SOFTWARE\Classes\Licenses\096EFC40-6ABF-11cf-850C-08002B30345D; ValueType: string; ValueData: knsgigmnmngnmnigthmgpninrmumhgkgrlrk
Root: HKLM; Subkey: SOFTWARE\Classes\Licenses\190B7910-992A-11cf-8AFA-00AA00C00905; ValueType: string; ValueData: gclclcejjcmjdcccoikjlcecoioijjcjnhng
Root: HKLM; Subkey: SOFTWARE\Classes\Licenses\1F3D5522-3F42-11d1-B2FA-00A0C908FB55; ValueType: string; ValueData: gcfjdjecpchcncdjpdejijgcrdoijjfcieod
Root: HKLM; Subkey: SOFTWARE\Classes\Licenses\2c49f800-c2dd-11cf-9ad6-0080c7e7b78d; ValueType: string; ValueData: mlrljgrlhltlngjlthrligklpkrhllglqlrk
Root: HKLM; Subkey: SOFTWARE\Classes\Licenses\4250E830-6AC2-11cf-8ADB-00AA00C00905; ValueType: string; ValueData: kjljvjjjoquqmjjjvpqqkqmqykypoqjquoun
Root: HKLM; Subkey: SOFTWARE\Classes\Licenses\43478d75-78e0-11cf-8e78-00a0d100038e; ValueType: string; ValueData: imshohohphlmnhimuinmphmmuiminhlmsmsl
Root: HKLM; Subkey: SOFTWARE\Classes\Licenses\4D553650-6ABE-11cf-8ADB-00AA00C00905; ValueType: string; ValueData: gfjmrfkfifkmkfffrlmmgmhmnlulkmfmqkqj
Root: HKLM; Subkey: SOFTWARE\Classes\Licenses\4F86BADF-9F77-11d1-B1B7-0000F8753F5D; ValueType: string; ValueData: iplpwpnippopupiivjrioppisjsjlpiiokuj
Root: HKLM; Subkey: SOFTWARE\Classes\Licenses\556C75F1-EFBC-11CF-B9F3-00A0247033C4; ValueType: string; ValueData: xybiedobrqsprbijaegcbislrsiucfjdhisl
Root: HKLM; Subkey: SOFTWARE\Classes\Licenses\57CBF9E0-6AA7-11cf-8ADB-00AA00C00905; ValueType: string; ValueData: aahakhchghkhfhaamghhbhbhkbpgfhahlfle
Root: HKLM; Subkey: SOFTWARE\Classes\Licenses\6FB38640-6AC7-11cf-8ADB-00AA00C00905; ValueType: string; ValueData: gdjkokgdldikhdddpjkkekgknesjikdkoioh
Root: HKLM; Subkey: SOFTWARE\Classes\Licenses\72E67120-5959-11cf-91F6-C2863C385E30; ValueType: string; ValueData: ibcbbbebqbdbciebmcobmbhifcmciibblgmf
Root: HKLM; Subkey: SOFTWARE\Classes\Licenses\78E1BDD1-9941-11cf-9756-00AA00C00908; ValueType: string; ValueData: yjrjvqkjlqqjnqkjvprqsjnjvkuknjpjtoun
Root: HKLM; Subkey: SOFTWARE\Classes\Licenses\899B3E80-6AC6-11cf-8ADB-00AA00C00905; ValueType: string; ValueData: wjsjjjlqmjpjrjjjvpqqkqmqukypoqjquoun
Root: HKLM; Subkey: SOFTWARE\Classes\Licenses\9E799BF1-8817-11cf-958F-0020AFC28C3B; ValueType: string; ValueData: uqpqnqkjujkjjjjqwktjrjkjtkupsjnjtoun
Root: HKLM; Subkey: SOFTWARE\Classes\Licenses\A133F000-CCB0-11d0-A316-00AA00688B10; ValueType: string; ValueData: cibbcimbpihbbbbbnhdbeidiocmcbbdbgdoc
Root: HKLM; Subkey: SOFTWARE\Classes\Licenses\B1692F60-23B0-11D0-8E95-00A0C90F26F8; ValueType: string; ValueData: mjjjccncgjijrcfjpdfjfcejpdkdkcgjojpd
Root: HKLM; Subkey: SOFTWARE\Classes\Licenses\B1EFCCF0-6AC1-11cf-8ADB-00AA00C00905; ValueType: string; ValueData: qqkjvqpqmqjjpqjjvpqqkqmqvkypoqjquoun
Root: HKLM; Subkey: SOFTWARE\Classes\Licenses\BC96F860-9928-11cf-8AFA-00AA00C00905; ValueType: string; ValueData: mmimfflflmqmlfffrlnmofhfkgrlmmfmqkqj
Root: HKLM; Subkey: SOFTWARE\Classes\Licenses\C4145310-469C-11d1-B182-00A0C922E820; ValueType: string; ValueData: konhqhioohihphkouimonhqhvnwiqhhhnjti
Root: HKLM; Subkey: SOFTWARE\Classes\Licenses\CDE57A55-8B86-11D0-b3C6-00A0C90AEA82; ValueType: string; ValueData: ekpkhddkjkekpdjkqemkfkldoeoefkfdjfqe
Root: HKLM; Subkey: SOFTWARE\Classes\Licenses\D015B071-D2ED-11d0-A31A-00AA00688B10; ValueType: string; ValueData: gjdcfjpcmjicjcdcoihcechjlioiccechepd
Root: HKLM; Subkey: SOFTWARE\Classes\Licenses\DC4D7920-6AC8-11cf-8ADB-00AA00C00905; ValueType: string; ValueData: iokouhloohrojhhhtnooiokomiwnmohosmsl
Root: HKLM; Subkey: SOFTWARE\Classes\Licenses\E32E2733-1BC5-11d0-B8C3-00A0C90DCA10; ValueType: string; ValueData: kmhfimlflmmfpffmsgfmhmimngtghmoflhsg
Root: HKLM; Subkey: SOFTWARE\Classes\Licenses\ED4B87C4-9F76-11d1-8BF7-0000F8754DA1; ValueType: string; ValueData: knlggnmntgggrninthpgmnngrhqhnnjnslsh
Root: HKLM; Subkey: SOFTWARE\Classes\Licenses\F4FC596D-DFFE-11CF-9551-00AA00A3DC45; ValueType: string; ValueData: mbmabptebkjcdlgtjmskjwtsdhjbmkmwtrak

Root: HKLM; Subkey: SOFTWARE\Classes\MSAddnDr.AddInDesigner.1; ValueType: string; ValueData: Addin Class
Root: HKLM; Subkey: SOFTWARE\Classes\MSAddnDr.AddInDesigner.1\CLSID; ValueType: string; ValueData: {{AC0714F6-3D04-11D1-AE7D-00A0C90F26F4}
Root: HKLM; Subkey: SOFTWARE\Classes\MSAddnDr.AddInDesigner; ValueType: string; ValueData: Addin Class
Root: HKLM; Subkey: SOFTWARE\Classes\MSAddnDr.AddInDesigner\CLSID; ValueType: string; ValueData: {{AC0714F6-3D04-11D1-AE7D-00A0C90F26F4}
Root: HKLM; Subkey: SOFTWARE\Classes\MSAddnDr.AddInDesigner\CurVer; ValueType: string; ValueData: MSAddnDr.AddInDesigner.1
Root: HKLM; Subkey: SOFTWARE\Classes\MSAddnDr.AddInInstance.1; ValueType: string; ValueData: Addin Class
Root: HKLM; Subkey: SOFTWARE\Classes\MSAddnDr.AddInInstance.1\CLSID; ValueType: string; ValueData: {{AC0714F7-3D04-11D1-AE7D-00A0C90F26F4}
Root: HKLM; Subkey: SOFTWARE\Classes\MSAddnDr.AddInInstance; ValueType: string; ValueData: Addin Class
Root: HKLM; Subkey: SOFTWARE\Classes\MSAddnDr.AddInInstance\CLSID; ValueType: string; ValueData: {{AC0714F7-3D04-11D1-AE7D-00A0C90F26F4}
Root: HKLM; Subkey: SOFTWARE\Classes\MSAddnDr.AddInInstance\CurVer; ValueType: string; ValueData: MSAddnDr.AddInInstance.1

Root: HKLM; Subkey: SOFTWARE\Classes\MSDEV.APPLICATION; ValueType: string; ValueData: MSDEV.APPLICATION; Components: VisualCpp\CeTools
Root: HKLM; Subkey: SOFTWARE\Classes\MSDEV.APPLICATION\CLSID; ValueType: string; ValueData: {{FB7FDAE2-89B8-11CF-9BE8-00A0C90A632C}; Components: VisualCpp\CeTools

Root: HKLM; Subkey: SOFTWARE\Classes\ODBC.FileDSN; ValueType: string; ValueData: Source de données ODBC
Root: HKLM; Subkey: SOFTWARE\Classes\ODBC.FileDSN\DefaultIcon; ValueType: string; ValueData: {win}\System32\odbcint.dll,1

Root: HKLM; Subkey: SOFTWARE\Classes\OSVIEWER\DeviceDatabase; ValueType: string; ValueData: Pegasus Remote Database; Components: VisualCpp\CeTools
Root: HKLM; Subkey: SOFTWARE\Classes\OSVIEWER\DeviceDatabase\CLSID; ValueType: string; ValueData: {{73750664-a067-11cf-9aa3-00aa006cc905}; Components: VisualCpp\CeTools
Root: HKLM; Subkey: SOFTWARE\Classes\OSVIEWER\DeviceFile; ValueType: string; ValueData: Pegasus Remote File; Components: VisualCpp\CeTools
Root: HKLM; Subkey: SOFTWARE\Classes\OSVIEWER\DeviceFile\CLSID; ValueType: string; ValueData: {{73750663-a067-11cf-9aa3-00aa006cc905}; Components: VisualCpp\CeTools
Root: HKLM; Subkey: SOFTWARE\Classes\OSVIEWER\Local; ValueType: string; ValueData: Host View Server; Components: VisualCpp\CeTools
Root: HKLM; Subkey: SOFTWARE\Classes\OSVIEWER\Local\CLSID; ValueType: string; ValueData: {{73750662-a067-11cf-9aa3-00aa006cc905}; Components: VisualCpp\CeTools
Root: HKLM; Subkey: SOFTWARE\Classes\OSVIEWER\PegDatabase; ValueType: string; ValueData: Pegasus Emulator Database; Components: VisualCpp\CeTools
Root: HKLM; Subkey: SOFTWARE\Classes\OSVIEWER\PegDatabase\CLSID; ValueType: string; ValueData: {{73750661-a067-11cf-9aa3-00aa006cc905}; Components: VisualCpp\CeTools
Root: HKLM; Subkey: SOFTWARE\Classes\OSVIEWER\PegFile; ValueType: string; ValueData: Pegasus Emulator File; Components: VisualCpp\CeTools
Root: HKLM; Subkey: SOFTWARE\Classes\OSVIEWER\PegFile\CLSID; ValueType: string; ValueData: {{73750660-a067-11cf-9aa3-00aa006cc905}; Components: VisualCpp\CeTools

Root: HKLM; Subkey: SOFTWARE\Classes\PlatformManager.PlatformManager.1; ValueType: string; ValueData: PlatformManager Class; Components: VisualCpp\CeTools
Root: HKLM; Subkey: SOFTWARE\Classes\PlatformManager.PlatformManager.1\CLSID; ValueType: string; ValueData: {{F384D883-F9AA-11D1-BB9E-00A0C9C9CCEE}; Components: VisualCpp\CeTools
Root: HKLM; Subkey: SOFTWARE\Classes\PlatformManager.PlatformManager; ValueType: string; ValueData: PlatformManager Class; Components: VisualCpp\CeTools
Root: HKLM; Subkey: SOFTWARE\Classes\PlatformManager.PlatformManager\CurVer; ValueType: string; ValueData: PlatformManager.PlatformManager.1; Components: VisualCpp\CeTools

Root: HKLM; Subkey: SOFTWARE\Classes\TypeLib\{{18BF4063-A8C4-11D1-AE5C-00600818410C}\7.0; ValueType: string; ValueData: Visual Component Manager 6
Root: HKLM; Subkey: SOFTWARE\Classes\TypeLib\{{18BF4063-A8C4-11D1-AE5C-00600818410C}\7.0\0\win32; ValueType: string; ValueData: {app}\Common\Tools\VCM\VCMMGR.DLL
Root: HKLM; Subkey: SOFTWARE\Classes\TypeLib\{{18BF4063-A8C4-11D1-AE5C-00600818410C}\7.0\FLAGS; ValueType: string; ValueData: 0
Root: HKLM; Subkey: SOFTWARE\Classes\TypeLib\{{18BF4063-A8C4-11D1-AE5C-00600818410C}\7.0\HELPDIR; ValueType: string; ValueData: {app}\Common\Tools\VCM

Root: HKLM; Subkey: SOFTWARE\Classes\TypeLib\{{2A6DF200-8240-11CF-AB59-00AA00C091A1}\6.0; ValueType: string; ValueData: Visual C++ Text Editor; Components: VisualCpp\CeTools
Root: HKLM; Subkey: SOFTWARE\Classes\TypeLib\{{2A6DF200-8240-11CF-AB59-00AA00C091A1}\6.0\0\win32; ValueType: string; ValueData: {app}\Common\MSDev98\Bin\devedit.pkg; Components: VisualCpp\CeTools
Root: HKLM; Subkey: SOFTWARE\Classes\TypeLib\{{2A6DF200-8240-11CF-AB59-00AA00C091A1}\6.0\FLAGS; ValueType: string; ValueData: 0; Components: VisualCpp\CeTools
Root: HKLM; Subkey: SOFTWARE\Classes\TypeLib\{{2A6DF200-8240-11CF-AB59-00AA00C091A1}\6.0\HELPDIR; ValueType: string; ValueData: {app}\Common\MSDev98\Bin; Components: VisualCpp\CeTools

Root: HKLM; Subkey: SOFTWARE\Classes\TypeLib\{{34C63000-AE64-11CF-AB59-00AA00C091A1}\6.0; ValueType: string; ValueData: Visual C++ Debugger; Components: VisualCpp\CeTools
Root: HKLM; Subkey: SOFTWARE\Classes\TypeLib\{{34C63000-AE64-11CF-AB59-00AA00C091A1}\6.0\0\win32; ValueType: string; ValueData: {app}\Common\MSDev98\Bin\IDE\devdbg.pkg; Components: VisualCpp\CeTools
Root: HKLM; Subkey: SOFTWARE\Classes\TypeLib\{{34C63000-AE64-11CF-AB59-00AA00C091A1}\6.0\FLAGS; ValueType: string; ValueData: 0; Components: VisualCpp\CeTools
Root: HKLM; Subkey: SOFTWARE\Classes\TypeLib\{{34C63000-AE64-11CF-AB59-00AA00C091A1}\6.0\HELPDIR; ValueType: string; ValueData: {app}\Common\MSDev98\Bin\IDE; Components: VisualCpp\CeTools

Root: HKLM; Subkey: SOFTWARE\Classes\TypeLib\{{3FF69171-1582-11D1-9605-00600818410C}\1.0\HELPDIR; ValueType: string; ValueData: {app}\Common\Tools\VCM\

#ifdef INSTALL_WNDTABS
;Root: HKLM; Subkey: SOFTWARE\Classes\TypeLib\{{680356D7-4BEB-40DD-BF56-8A7D2D3F330F}\1.0; ValueType: string; ValueData: WTSDK_SAMP Developer Studio Add-in; Components: WndTabs
;Root: HKLM; Subkey: SOFTWARE\Classes\TypeLib\{{680356D7-4BEB-40DD-BF56-8A7D2D3F330F}\1.0\0\win32; ValueType: string; ValueData: {app}\WndTabs\WTSDK_Samp.dll; Components: WndTabs
;Root: HKLM; Subkey: SOFTWARE\Classes\TypeLib\{{680356D7-4BEB-40DD-BF56-8A7D2D3F330F}\1.0\FLAGS; ValueType: string; ValueData: 0; Components: WndTabs
;Root: HKLM; Subkey: SOFTWARE\Classes\TypeLib\{{680356D7-4BEB-40DD-BF56-8A7D2D3F330F}\1.0\HELPDIR; ValueType: string; ValueData: {app}\WndTabs\; Components: WndTabs

;Root: HKLM; Subkey: SOFTWARE\Classes\TypeLib\{{6A06C128-4748-11D1-BC91-0000010016A6}\1.0; ValueType: string; ValueData: WNDTABS Developer Studio Add-in; Components: WndTabs
;Root: HKLM; Subkey: SOFTWARE\Classes\TypeLib\{{6A06C128-4748-11D1-BC91-0000010016A6}\1.0\0\win32; ValueType: string; ValueData: {app}\WndTabs\WndTabs.dll; Components: WndTabs
;Root: HKLM; Subkey: SOFTWARE\Classes\TypeLib\{{6A06C128-4748-11D1-BC91-0000010016A6}\1.0\FLAGS; ValueType: string; ValueData: 0; Components: WndTabs
;Root: HKLM; Subkey: SOFTWARE\Classes\TypeLib\{{6A06C128-4748-11D1-BC91-0000010016A6}\1.0\HELPDIR; ValueType: string; ValueData: {app}\WndTabs\; Components: WndTabs
#endif

Root: HKLM; Subkey: SOFTWARE\Classes\TypeLib\{{6A30AD80-10FD-11D1-9603-00600818410C}\1.0\HELPDIR; ValueType: string; ValueData: {app}\Common\IDE\IDE98\

Root: HKLM; Subkey: SOFTWARE\Classes\TypeLib\{{723AA6C1-3B50-11D1-9636-00600818410C}\1.0\HELPDIR; ValueType: string; ValueData: {app}\Common\Tools\VCM\

Root: HKLM; Subkey: SOFTWARE\Classes\TypeLib\{{96961265-A819-11CF-AD07-00A0C9034965}\6.0; ValueType: string; ValueData: Visual C++ Project System; Components: VisualCpp\CeTools
Root: HKLM; Subkey: SOFTWARE\Classes\TypeLib\{{96961265-A819-11CF-AD07-00A0C9034965}\6.0\0\win32; ValueType: string; ValueData: {app}\Common\MSDev98\Bin\IDE\devbld.pkg; Components: VisualCpp\CeTools
Root: HKLM; Subkey: SOFTWARE\Classes\TypeLib\{{96961265-A819-11CF-AD07-00A0C9034965}\6.0\FLAGS; ValueType: string; ValueData: 0; Components: VisualCpp\CeTools
Root: HKLM; Subkey: SOFTWARE\Classes\TypeLib\{{96961265-A819-11CF-AD07-00A0C9034965}\6.0\HELPDIR; ValueType: string; ValueData: {app}\Common\MSDev98\Bin\IDE; Components: VisualCpp\CeTools

Root: HKLM; Subkey: SOFTWARE\Classes\TypeLib\{{AC0714F2-3D04-11D1-AE7D-00A0C90F26F4}\1.0\0\win32; ValueType: string; ValueData: {cf}\designer\MSADDNDR.TLB
Root: HKLM; Subkey: SOFTWARE\Classes\TypeLib\{{AC0714F2-3D04-11D1-AE7D-00A0C90F26F4}\1.0\HELPDIR; ValueType: string; ValueData: 

Root: HKLM; Subkey: SOFTWARE\Classes\TypeLib\{{B3CF8E20-19B6-11CF-8E4D-00AA004254C4}\6.0; ValueType: string; ValueData: Visual C++ Shared Objects; Components: VisualCpp\CeTools
Root: HKLM; Subkey: SOFTWARE\Classes\TypeLib\{{B3CF8E20-19B6-11CF-8E4D-00AA004254C4}\6.0\0\win32; ValueType: string; ValueData: {app}\Common\MSDev98\Bin\devshl.DLL; Components: VisualCpp\CeTools
Root: HKLM; Subkey: SOFTWARE\Classes\TypeLib\{{B3CF8E20-19B6-11CF-8E4D-00AA004254C4}\6.0\FLAGS; ValueType: string; ValueData: 0; Components: VisualCpp\CeTools
Root: HKLM; Subkey: SOFTWARE\Classes\TypeLib\{{B3CF8E20-19B6-11CF-8E4D-00AA004254C4}\6.0\HELPDIR; ValueType: string; ValueData: {app}\Common\MSDev98\Bin; Components: VisualCpp\CeTools

Root: HKLM; Subkey: SOFTWARE\Classes\TypeLib\{{CBE51AA8-A410-11D1-80D0-006097C9987D}\1.0; ValueType: string; ValueData: Microsoft Visual Wizard Framework; Components: VisualCpp\ServicePack
Root: HKLM; Subkey: SOFTWARE\Classes\TypeLib\{{CBE51AA8-A410-11D1-80D0-006097C9987D}\1.0\0\win32; ValueType: string; ValueData: {cf}\Microsoft Shared\Wizards98\VIWZRT.DLL; Components: VisualCpp\ServicePack
Root: HKLM; Subkey: SOFTWARE\Classes\TypeLib\{{CBE51AA8-A410-11D1-80D0-006097C9987D}\1.0\FLAGS; ValueType: string; ValueData: 0; Components: VisualCpp\ServicePack
Root: HKLM; Subkey: SOFTWARE\Classes\TypeLib\{{CBE51AA8-A410-11D1-80D0-006097C9987D}\1.0\HELPDIR; ValueType: string; ValueData: {cf}\Microsoft Shared\Wizards98; Components: VisualCpp\ServicePack

Root: HKLM; Subkey: SOFTWARE\Classes\TypeLib\{{E0E270C2-C0BE-11D0-8FE4-00A0C90A6341}\1.5; ValueType: string; ValueData: Microsoft OLE DB Simple Provider 1.5 Library
Root: HKLM; Subkey: SOFTWARE\Classes\TypeLib\{{E0E270C2-C0BE-11D0-8FE4-00A0C90A6341}\1.5\409\win32; ValueType: string; ValueData: {sys}\simpdata.tlb
Root: HKLM; Subkey: SOFTWARE\Classes\TypeLib\{{E0E270C2-C0BE-11D0-8FE4-00A0C90A6341}\1.5\FLAGS; ValueType: string; ValueData: 0
Root: HKLM; Subkey: SOFTWARE\Classes\TypeLib\{{E0E270C2-C0BE-11D0-8FE4-00A0C90A6341}\1.5\HELPDIR; ValueType: string; ValueData: {sys}

Root: HKLM; Subkey: SOFTWARE\Classes\Vcm.Cabinet.1; ValueType: string; ValueData: Cabinet Class
Root: HKLM; Subkey: SOFTWARE\Classes\Vcm.Cabinet.1\CLSID; ValueType: string; ValueData: {{3FF69183-1582-11D1-9605-00600818410C}
Root: HKLM; Subkey: SOFTWARE\Classes\Vcm.Cabinet; ValueType: string; ValueData: Cabinet Class
Root: HKLM; Subkey: SOFTWARE\Classes\Vcm.Cabinet\CurVer; ValueType: string; ValueData: Vcm.Cabinet.1

Root: HKLM; Subkey: SOFTWARE\Classes\VcmEnu.IResource; ValueType: string; ValueData: VcmEnu.IResource
Root: HKLM; Subkey: SOFTWARE\Classes\VcmEnu.IResource\Clsid; ValueType: string; ValueData: {{AEB7F2FC-06DA-11D2-8D70-00A0C98B28E2}
Root: HKLM; Subkey: SOFTWARE\Classes\VcmMgr.ActiveXHandler; ValueType: string; ValueData: Item Handler for Group Type items.

Root: HKLM; Subkey: SOFTWARE\Classes\VcmMgr.ActiveXHandler\Clsid; ValueType: string; ValueData: {{18BF4085-A8C4-11D1-AE5C-00600818410C}

Root: HKLM; Subkey: SOFTWARE\Classes\VcmMgr.CabProgress; ValueType: string; ValueData: VcmMgr.CabProgress
Root: HKLM; Subkey: SOFTWARE\Classes\VcmMgr.CabProgress\Clsid; ValueType: string; ValueData: {{18BF407F-A8C4-11D1-AE5C-00600818410C}

Root: HKLM; Subkey: SOFTWARE\Classes\VcmMgr.Connect; ValueType: string; ValueData: Visual Component Manager 6.0
Root: HKLM; Subkey: SOFTWARE\Classes\VcmMgr.Connect\Clsid; ValueType: string; ValueData: {{18BF406C-A8C4-11D1-AE5C-00600818410C}

Root: HKLM; Subkey: SOFTWARE\Classes\VcmMgr.docShadow; ValueType: string; ValueData: VcmMgr.docShadow
Root: HKLM; Subkey: SOFTWARE\Classes\VcmMgr.docShadow\Clsid; ValueType: string; ValueData: {{48FCA4AF-A8C0-11D1-AE5C-00600818410C}

Root: HKLM; Subkey: SOFTWARE\Classes\VcmMgr.DocumentHandler; ValueType: string; ValueData: Item Handler for Project Type items.
Root: HKLM; Subkey: SOFTWARE\Classes\VcmMgr.DocumentHandler\Clsid; ValueType: string; ValueData: {{18BF4087-A8C4-11D1-AE5C-00600818410C}

Root: HKLM; Subkey: SOFTWARE\Classes\VcmMgr.Importer; ValueType: string; ValueData: VcmMgr.Importer
Root: HKLM; Subkey: SOFTWARE\Classes\VcmMgr.Importer\Clsid; ValueType: string; ValueData: {{9B969EEA-EF39-11D1-8D6D-00A0C98B28E2}

Root: HKLM; Subkey: SOFTWARE\Classes\VcmMgr.ItemProperty; ValueType: string; ValueData: VcmMgr.ItemProperty
Root: HKLM; Subkey: SOFTWARE\Classes\VcmMgr.ItemProperty\Clsid; ValueType: string; ValueData: {{18BF407C-A8C4-11D1-AE5C-00600818410C}

Root: HKLM; Subkey: SOFTWARE\Classes\VcmMgr.JavaHandler; ValueType: string; ValueData: VcmMgr.JavaHandler
Root: HKLM; Subkey: SOFTWARE\Classes\VcmMgr.JavaHandler\Clsid; ValueType: string; ValueData: {{18BF4091-A8C4-11D1-AE5C-00600818410C}

Root: HKLM; Subkey: SOFTWARE\Classes\VcmMgr.PropHandler; ValueType: string; ValueData: VcmMgr.PropHandler
Root: HKLM; Subkey: SOFTWARE\Classes\VcmMgr.PropHandler\Clsid; ValueType: string; ValueData: {{48FCA4A7-A8C0-11D1-AE5C-00600818410C}

Root: HKLM; Subkey: SOFTWARE\Classes\VcmMgr.RepTableItem; ValueType: string; ValueData: VcmMgr.RepTableItem
Root: HKLM; Subkey: SOFTWARE\Classes\VcmMgr.RepTableItem\Clsid; ValueType: string; ValueData: {{9B969EEE-EF39-11D1-8D6D-00A0C98B28E2}

Root: HKLM; Subkey: SOFTWARE\Classes\VcmMgr.TypeDefinition; ValueType: string; ValueData: VcmMgr.TypeDefinition
Root: HKLM; Subkey: SOFTWARE\Classes\VcmMgr.TypeDefinition\Clsid; ValueType: string; ValueData: {{18BF4078-A8C4-11D1-AE5C-00600818410C}

Root: HKLM; Subkey: SOFTWARE\Classes\VcmMgr.VBConnectionHandler; ValueType: string; ValueData: Item Handler for Project Type items.
Root: HKLM; Subkey: SOFTWARE\Classes\VcmMgr.VBConnectionHandler\Clsid; ValueType: string; ValueData: {{18BF408B-A8C4-11D1-AE5C-00600818410C}

Root: HKLM; Subkey: SOFTWARE\Classes\VcmMgr.VBProjectHandler; ValueType: string; ValueData: Item Handler for Project Type items.
Root: HKLM; Subkey: SOFTWARE\Classes\VcmMgr.VBProjectHandler\Clsid; ValueType: string; ValueData: {{18BF4089-A8C4-11D1-AE5C-00600818410C}

Root: HKLM; Subkey: SOFTWARE\Classes\VcmMgr.VBTemplateHandler; ValueType: string; ValueData: Item Handler for Template Type items.
Root: HKLM; Subkey: SOFTWARE\Classes\VcmMgr.VBTemplateHandler\Clsid; ValueType: string; ValueData: {{18BF408D-A8C4-11D1-AE5C-00600818410C}

Root: HKLM; Subkey: SOFTWARE\Classes\VcmMgr.Vcm; ValueType: string; ValueData: VcmMgr.Vcm
Root: HKLM; Subkey: SOFTWARE\Classes\VcmMgr.Vcm; ValueType: binary; ValueName: EditFlags; ValueData: 00 00 01 00
Root: HKLM; Subkey: SOFTWARE\Classes\VcmMgr.Vcm; ValueType: binary; ValueName: BrowserFlags; ValueData: 00 10 00 00
Root: HKLM; Subkey: SOFTWARE\Classes\VcmMgr.Vcm\Clsid; ValueType: string; ValueData: {{48FCA4AD-A8C0-11D1-AE5C-00600818410C}
Root: HKLM; Subkey: SOFTWARE\Classes\VcmMgr.Vcm\DocObject; ValueType: string; ValueData: 8

Root: HKLM; Subkey: SOFTWARE\Classes\VcmMgr.VsHelp; ValueType: string; ValueData: VcmMgr.VsHelp
Root: HKLM; Subkey: SOFTWARE\Classes\VcmMgr.VsHelp\Clsid; ValueType: string; ValueData: {{18BF406A-A8C4-11D1-AE5C-00600818410C}

Root: HKLM; Subkey: SOFTWARE\Classes\VcmPackage.ItemProperties.1; ValueType: string; ValueData: ItemProperties Class
Root: HKLM; Subkey: SOFTWARE\Classes\VcmPackage.ItemProperties.1\CLSID; ValueType: string; ValueData: {{09BB1114-3755-11D1-962B-00600818410C}
Root: HKLM; Subkey: SOFTWARE\Classes\VcmPackage.ItemProperties; ValueType: string; ValueData: ItemProperties Class
Root: HKLM; Subkey: SOFTWARE\Classes\VcmPackage.ItemProperties\CurVer; ValueType: string; ValueData: VcmPackage.ItemProperties.1
Root: HKLM; Subkey: SOFTWARE\Classes\VcmPackage.ItemProperty.1; ValueType: string; ValueData: ItemProperty Class
Root: HKLM; Subkey: SOFTWARE\Classes\VcmPackage.ItemProperty.1\CLSID; ValueType: string; ValueData: {{09BB1116-3755-11D1-962B-00600818410C}
Root: HKLM; Subkey: SOFTWARE\Classes\VcmPackage.ItemProperty; ValueType: string; ValueData: ItemProperty Class
Root: HKLM; Subkey: SOFTWARE\Classes\VcmPackage.ItemProperty\CurVer; ValueType: string; ValueData: VcmPackage.ItemProperty.1

Root: HKLM; Subkey: SOFTWARE\Classes\VcmUtl.VcmReg.1; ValueType: string; ValueData: VcmReg Class
Root: HKLM; Subkey: SOFTWARE\Classes\VcmUtl.VcmReg.1\CLSID; ValueType: string; ValueData: {{723AA6D1-3B50-11D1-9636-00600818410C}
Root: HKLM; Subkey: SOFTWARE\Classes\VcmUtl.VcmReg; ValueType: string; ValueData: VcmReg Class
Root: HKLM; Subkey: SOFTWARE\Classes\VcmUtl.VcmReg\CurVer; ValueType: string; ValueData: VcmUtl.VcmReg.1

Root: HKLM; Subkey: SOFTWARE\Classes\VisModelBrowser.VMBrowser; ValueType: string; ValueData: VisModelBrowser.VMBrowser
Root: HKLM; Subkey: SOFTWARE\Classes\VisModelBrowser.VMBrowser\Clsid; ValueType: string; ValueData: {{1E9A88A2-2968-11D1-851D-00A0C911E8B0}

Root: HKLM; Subkey: SOFTWARE\Classes\VIWFrame.CBitmap; ValueType: string; ValueData: VIWFrame.CBitmap; Components: VisualCpp\CeTools
Root: HKLM; Subkey: SOFTWARE\Classes\VIWFrame.CBitmap\Clsid; ValueType: string; ValueData: {{2E338C70-8ED1-11D1-AC54-00A0C94A8147}; Components: VisualCpp\CeTools
Root: HKLM; Subkey: SOFTWARE\Classes\VIWFrame.CBitmaps; ValueType: string; ValueData: VIWFrame.CBitmaps; Components: VisualCpp\CeTools
Root: HKLM; Subkey: SOFTWARE\Classes\VIWFrame.CBitmaps\Clsid; ValueType: string; ValueData: {{2E338C71-8ED1-11D1-AC54-00A0C94A8147}; Components: VisualCpp\CeTools
Root: HKLM; Subkey: SOFTWARE\Classes\VIWFrame.CDBManager; ValueType: string; ValueData: VIWFrame.CDBManager; Components: VisualCpp\CeTools
Root: HKLM; Subkey: SOFTWARE\Classes\VIWFrame.CDBManager\Clsid; ValueType: string; ValueData: {{2E338C95-8ED1-11D1-AC54-00A0C94A8147}; Components: VisualCpp\CeTools
Root: HKLM; Subkey: SOFTWARE\Classes\VIWFrame.CError; ValueType: string; ValueData: VIWFrame.CError; Components: VisualCpp\CeTools
Root: HKLM; Subkey: SOFTWARE\Classes\VIWFrame.CError\Clsid; ValueType: string; ValueData: {{2E338C72-8ED1-11D1-AC54-00A0C94A8147}; Components: VisualCpp\CeTools
Root: HKLM; Subkey: SOFTWARE\Classes\VIWFrame.CErrors; ValueType: string; ValueData: VIWFrame.CErrors; Components: VisualCpp\CeTools
Root: HKLM; Subkey: SOFTWARE\Classes\VIWFrame.CErrors\Clsid; ValueType: string; ValueData: {{2E338C73-8ED1-11D1-AC54-00A0C94A8147}; Components: VisualCpp\CeTools
Root: HKLM; Subkey: SOFTWARE\Classes\VIWFrame.CField; ValueType: string; ValueData: VIWFrame.CField; Components: VisualCpp\CeTools
Root: HKLM; Subkey: SOFTWARE\Classes\VIWFrame.CField\Clsid; ValueType: string; ValueData: {{2E338C74-8ED1-11D1-AC54-00A0C94A8147}; Components: VisualCpp\CeTools
Root: HKLM; Subkey: SOFTWARE\Classes\VIWFrame.CFields; ValueType: string; ValueData: VIWFrame.CFields; Components: VisualCpp\CeTools
Root: HKLM; Subkey: SOFTWARE\Classes\VIWFrame.CFields\Clsid; ValueType: string; ValueData: {{2E338C75-8ED1-11D1-AC54-00A0C94A8147}; Components: VisualCpp\CeTools
Root: HKLM; Subkey: SOFTWARE\Classes\VIWFrame.CFPServer; ValueType: string; ValueData: VIWFrame.CFPServer; Components: VisualCpp\CeTools
Root: HKLM; Subkey: SOFTWARE\Classes\VIWFrame.CFPServer\Clsid; ValueType: string; ValueData: {{2E338C76-8ED1-11D1-AC54-00A0C94A8147}; Components: VisualCpp\CeTools
Root: HKLM; Subkey: SOFTWARE\Classes\VIWFrame.CGraphic; ValueType: string; ValueData: VIWFrame.CGraphic; Components: VisualCpp\CeTools
Root: HKLM; Subkey: SOFTWARE\Classes\VIWFrame.CGraphic\Clsid; ValueType: string; ValueData: {{2E338C77-8ED1-11D1-AC54-00A0C94A8147}; Components: VisualCpp\CeTools
Root: HKLM; Subkey: SOFTWARE\Classes\VIWFrame.CGraphics; ValueType: string; ValueData: VIWFrame.CGraphics; Components: VisualCpp\CeTools
Root: HKLM; Subkey: SOFTWARE\Classes\VIWFrame.CGraphics\Clsid; ValueType: string; ValueData: {{2E338C78-8ED1-11D1-AC54-00A0C94A8147}; Components: VisualCpp\CeTools
Root: HKLM; Subkey: SOFTWARE\Classes\VIWFrame.CHTMLStream; ValueType: string; ValueData: VIWFrame.CHTMLStream; Components: VisualCpp\CeTools
Root: HKLM; Subkey: SOFTWARE\Classes\VIWFrame.CHTMLStream\Clsid; ValueType: string; ValueData: {{2E338C79-8ED1-11D1-AC54-00A0C94A8147}; Components: VisualCpp\CeTools
Root: HKLM; Subkey: SOFTWARE\Classes\VIWFrame.CHTMLStreams; ValueType: string; ValueData: VIWFrame.CHTMLStreams; Components: VisualCpp\CeTools
Root: HKLM; Subkey: SOFTWARE\Classes\VIWFrame.CHTMLStreams\Clsid; ValueType: string; ValueData: {{2E338C7A-8ED1-11D1-AC54-00A0C94A8147}; Components: VisualCpp\CeTools
Root: HKLM; Subkey: SOFTWARE\Classes\VIWFrame.CImage; ValueType: string; ValueData: VIWFrame.CImage; Components: VisualCpp\CeTools
Root: HKLM; Subkey: SOFTWARE\Classes\VIWFrame.CImage\Clsid; ValueType: string; ValueData: {{2E338C7B-8ED1-11D1-AC54-00A0C94A8147}; Components: VisualCpp\CeTools
Root: HKLM; Subkey: SOFTWARE\Classes\VIWFrame.CImages; ValueType: string; ValueData: VIWFrame.CImages; Components: VisualCpp\CeTools
Root: HKLM; Subkey: SOFTWARE\Classes\VIWFrame.CImages\Clsid; ValueType: string; ValueData: {{2E338C7C-8ED1-11D1-AC54-00A0C94A8147}; Components: VisualCpp\CeTools
Root: HKLM; Subkey: SOFTWARE\Classes\VIWFrame.CLayoutManager; ValueType: string; ValueData: VIWFrame.CLayoutManager; Components: VisualCpp\CeTools
Root: HKLM; Subkey: SOFTWARE\Classes\VIWFrame.CLayoutManager\Clsid; ValueType: string; ValueData: {{2E338C96-8ED1-11D1-AC54-00A0C94A8147}; Components: VisualCpp\CeTools
Root: HKLM; Subkey: SOFTWARE\Classes\VIWFrame.CMultiPick; ValueType: string; ValueData: VIWFrame.CMultiPick; Components: VisualCpp\CeTools
Root: HKLM; Subkey: SOFTWARE\Classes\VIWFrame.CMultiPick\Clsid; ValueType: string; ValueData: {{2E338C7D-8ED1-11D1-AC54-00A0C94A8147}; Components: VisualCpp\CeTools
Root: HKLM; Subkey: SOFTWARE\Classes\VIWFrame.CNavigation; ValueType: string; ValueData: VIWFrame.CNavigation; Components: VisualCpp\CeTools
Root: HKLM; Subkey: SOFTWARE\Classes\VIWFrame.CNavigation\Clsid; ValueType: string; ValueData: {{2E338C7E-8ED1-11D1-AC54-00A0C94A8147}; Components: VisualCpp\CeTools
Root: HKLM; Subkey: SOFTWARE\Classes\VIWFrame.CNavInfo; ValueType: string; ValueData: VIWFrame.CNavInfo; Components: VisualCpp\CeTools
Root: HKLM; Subkey: SOFTWARE\Classes\VIWFrame.CNavInfo\Clsid; ValueType: string; ValueData: {{2E338C7F-8ED1-11D1-AC54-00A0C94A8147}; Components: VisualCpp\CeTools
Root: HKLM; Subkey: SOFTWARE\Classes\VIWFrame.CODBCConnection; ValueType: string; ValueData: VIWFrame.CODBCConnection; Components: VisualCpp\CeTools
Root: HKLM; Subkey: SOFTWARE\Classes\VIWFrame.CODBCConnection\Clsid; ValueType: string; ValueData: {{2E338C80-8ED1-11D1-AC54-00A0C94A8147}; Components: VisualCpp\CeTools
Root: HKLM; Subkey: SOFTWARE\Classes\VIWFrame.CReplacement; ValueType: string; ValueData: VIWFrame.CReplacement; Components: VisualCpp\CeTools
Root: HKLM; Subkey: SOFTWARE\Classes\VIWFrame.CReplacement\Clsid; ValueType: string; ValueData: {{2E338C81-8ED1-11D1-AC54-00A0C94A8147}; Components: VisualCpp\CeTools
Root: HKLM; Subkey: SOFTWARE\Classes\VIWFrame.CReplacements; ValueType: string; ValueData: VIWFrame.CReplacements; Components: VisualCpp\CeTools
Root: HKLM; Subkey: SOFTWARE\Classes\VIWFrame.CReplacements\Clsid; ValueType: string; ValueData: {{2E338C82-8ED1-11D1-AC54-00A0C94A8147}; Components: VisualCpp\CeTools
Root: HKLM; Subkey: SOFTWARE\Classes\VIWFrame.CServerForms; ValueType: string; ValueData: VIWFrame.CServerForms; Components: VisualCpp\CeTools
Root: HKLM; Subkey: SOFTWARE\Classes\VIWFrame.CServerForms\Clsid; ValueType: string; ValueData: {{2E338C83-8ED1-11D1-AC54-00A0C94A8147}; Components: VisualCpp\CeTools
Root: HKLM; Subkey: SOFTWARE\Classes\VIWFrame.CStdError; ValueType: string; ValueData: VIWFrame.CStdError; Components: VisualCpp\CeTools
Root: HKLM; Subkey: SOFTWARE\Classes\VIWFrame.CStdError\Clsid; ValueType: string; ValueData: {{2E338C84-8ED1-11D1-AC54-00A0C94A8147}; Components: VisualCpp\CeTools
Root: HKLM; Subkey: SOFTWARE\Classes\VIWFrame.CStdErrors; ValueType: string; ValueData: VIWFrame.CStdErrors; Components: VisualCpp\CeTools
Root: HKLM; Subkey: SOFTWARE\Classes\VIWFrame.CStdErrors\Clsid; ValueType: string; ValueData: {{2E338C85-8ED1-11D1-AC54-00A0C94A8147}; Components: VisualCpp\CeTools
Root: HKLM; Subkey: SOFTWARE\Classes\VIWFrame.CString; ValueType: string; ValueData: VIWFrame.CString; Components: VisualCpp\CeTools
Root: HKLM; Subkey: SOFTWARE\Classes\VIWFrame.CString\Clsid; ValueType: string; ValueData: {{2E338C86-8ED1-11D1-AC54-00A0C94A8147}; Components: VisualCpp\CeTools
Root: HKLM; Subkey: SOFTWARE\Classes\VIWFrame.CStrings; ValueType: string; ValueData: VIWFrame.CStrings; Components: VisualCpp\CeTools
Root: HKLM; Subkey: SOFTWARE\Classes\VIWFrame.CStrings\Clsid; ValueType: string; ValueData: {{2E338C87-8ED1-11D1-AC54-00A0C94A8147}; Components: VisualCpp\CeTools
Root: HKLM; Subkey: SOFTWARE\Classes\VIWFrame.CTable; ValueType: string; ValueData: VIWFrame.CTable; Components: VisualCpp\CeTools
Root: HKLM; Subkey: SOFTWARE\Classes\VIWFrame.CTable\Clsid; ValueType: string; ValueData: {{2E338C88-8ED1-11D1-AC54-00A0C94A8147}; Components: VisualCpp\CeTools
Root: HKLM; Subkey: SOFTWARE\Classes\VIWFrame.CTables; ValueType: string; ValueData: VIWFrame.CTables; Components: VisualCpp\CeTools
Root: HKLM; Subkey: SOFTWARE\Classes\VIWFrame.CTables\Clsid; ValueType: string; ValueData: {{2E338C89-8ED1-11D1-AC54-00A0C94A8147}; Components: VisualCpp\CeTools
Root: HKLM; Subkey: SOFTWARE\Classes\VIWFrame.CTemplate; ValueType: string; ValueData: VIWFrame.CTemplate; Components: VisualCpp\CeTools
Root: HKLM; Subkey: SOFTWARE\Classes\VIWFrame.CTemplate\Clsid; ValueType: string; ValueData: {{2E338C8A-8ED1-11D1-AC54-00A0C94A8147}; Components: VisualCpp\CeTools
Root: HKLM; Subkey: SOFTWARE\Classes\VIWFrame.CTemplates; ValueType: string; ValueData: VIWFrame.CTemplates; Components: VisualCpp\CeTools
Root: HKLM; Subkey: SOFTWARE\Classes\VIWFrame.CTemplates\Clsid; ValueType: string; ValueData: {{2E338C8B-8ED1-11D1-AC54-00A0C94A8147}; Components: VisualCpp\CeTools
Root: HKLM; Subkey: SOFTWARE\Classes\VIWFrame.CTemplateType; ValueType: string; ValueData: VIWFrame.CTemplateType; Components: VisualCpp\CeTools
Root: HKLM; Subkey: SOFTWARE\Classes\VIWFrame.CTemplateType\Clsid; ValueType: string; ValueData: {{2E338C8C-8ED1-11D1-AC54-00A0C94A8147}; Components: VisualCpp\CeTools
Root: HKLM; Subkey: SOFTWARE\Classes\VIWFrame.CTemplateTypes; ValueType: string; ValueData: VIWFrame.CTemplateTypes; Components: VisualCpp\CeTools
Root: HKLM; Subkey: SOFTWARE\Classes\VIWFrame.CTemplateTypes\Clsid; ValueType: string; ValueData: {{2E338C8D-8ED1-11D1-AC54-00A0C94A8147}; Components: VisualCpp\CeTools
Root: HKLM; Subkey: SOFTWARE\Classes\VIWFrame.CTheme; ValueType: string; ValueData: VIWFrame.CTheme; Components: VisualCpp\CeTools
Root: HKLM; Subkey: SOFTWARE\Classes\VIWFrame.CTheme\Clsid; ValueType: string; ValueData: {{2E338C8E-8ED1-11D1-AC54-00A0C94A8147}; Components: VisualCpp\CeTools
Root: HKLM; Subkey: SOFTWARE\Classes\VIWFrame.CThemeManager; ValueType: string; ValueData: VIWFrame.CThemeManager; Components: VisualCpp\CeTools
Root: HKLM; Subkey: SOFTWARE\Classes\VIWFrame.CThemeManager\Clsid; ValueType: string; ValueData: {{2E338C94-8ED1-11D1-AC54-00A0C94A8147}; Components: VisualCpp\CeTools
Root: HKLM; Subkey: SOFTWARE\Classes\VIWFrame.CThemes; ValueType: string; ValueData: VIWFrame.CThemes; Components: VisualCpp\CeTools
Root: HKLM; Subkey: SOFTWARE\Classes\VIWFrame.CThemes\Clsid; ValueType: string; ValueData: {{2E338C8F-8ED1-11D1-AC54-00A0C94A8147}; Components: VisualCpp\CeTools
Root: HKLM; Subkey: SOFTWARE\Classes\VIWFrame.CTreeview; ValueType: string; ValueData: VIWFrame.CTreeview; Components: VisualCpp\CeTools
Root: HKLM; Subkey: SOFTWARE\Classes\VIWFrame.CTreeview\Clsid; ValueType: string; ValueData: {{2E338C90-8ED1-11D1-AC54-00A0C94A8147}; Components: VisualCpp\CeTools
Root: HKLM; Subkey: SOFTWARE\Classes\VIWFrame.CWebPage; ValueType: string; ValueData: VIWFrame.CWebPage; Components: VisualCpp\CeTools
Root: HKLM; Subkey: SOFTWARE\Classes\VIWFrame.CWebPage\Clsid; ValueType: string; ValueData: {{2E338C91-8ED1-11D1-AC54-00A0C94A8147}; Components: VisualCpp\CeTools
Root: HKLM; Subkey: SOFTWARE\Classes\VIWFrame.CWebPages; ValueType: string; ValueData: VIWFrame.CWebPages; Components: VisualCpp\CeTools
Root: HKLM; Subkey: SOFTWARE\Classes\VIWFrame.CWebPages\Clsid; ValueType: string; ValueData: {{2E338C92-8ED1-11D1-AC54-00A0C94A8147}; Components: VisualCpp\CeTools
Root: HKLM; Subkey: SOFTWARE\Classes\VIWFrame.CWizardApp; ValueType: string; ValueData: VIWFrame.CWizardApp; Components: VisualCpp\CeTools
Root: HKLM; Subkey: SOFTWARE\Classes\VIWFrame.CWizardApp\Clsid; ValueType: string; ValueData: {{2E338C93-8ED1-11D1-AC54-00A0C94A8147}; Components: VisualCpp\CeTools

Root: HKLM; Subkey: SOFTWARE\Classes\VMEventHandler.ItemProperty; ValueType: string; ValueData: VMEventHandler.ItemProperty
Root: HKLM; Subkey: SOFTWARE\Classes\VMEventHandler.ItemProperty\Clsid; ValueType: string; ValueData: {{323E7DB7-C174-11D1-ABF9-006008C6167D}
Root: HKLM; Subkey: SOFTWARE\Classes\VMEventHandler.VisualModelHandler; ValueType: string; ValueData: VMEventHandler.VisualModelHandler
Root: HKLM; Subkey: SOFTWARE\Classes\VMEventHandler.VisualModelHandler\Clsid; ValueType: string; ValueData: {{6661B740-9D9C-11D1-B931-00C04FBBC221}

#ifdef INSTALL_WNDTABS
;Root: HKLM; Subkey: SOFTWARE\Classes\Window Tabs; ValueType: string; ValueData: WndTabs; Components: WndTabs
;Root: HKLM; Subkey: SOFTWARE\Classes\Window Tabs\CLSID; ValueType: string; ValueData: {{6A06C123-4748-11D1-BC91-0000010016A6}; Components: WndTabs

;Root: HKLM; Subkey: SOFTWARE\Classes\WNDTABS Developer Studio Add-in; ValueType: string; ValueData: WndTabs; Components: WndTabs
;Root: HKLM; Subkey: SOFTWARE\Classes\WNDTABS Developer Studio Add-in\CLSID; ValueType: string; ValueData: {{6A06C123-4748-11D1-BC91-0000010016A6}; Components: WndTabs

;Root: HKLM; Subkey: SOFTWARE\Classes\WTSDK_SAMP Developer Studio Add-in; ValueType: string; ValueData: WndTabs SDK Sample Add-In; Components: WndTabs
;Root: HKLM; Subkey: SOFTWARE\Classes\WTSDK_SAMP Developer Studio Add-in\CLSID; ValueType: string; ValueData: {{1432D665-1AB1-4175-9991-8CCA5FC52578}; Components: WndTabs
;Root: HKLM; Subkey: SOFTWARE\Classes\WTSDK_Samp.DSAddIn.1; ValueType: string; ValueData: WndTabs SDK Sample Add-In; Components: WndTabs
;Root: HKLM; Subkey: SOFTWARE\Classes\WTSDK_Samp.DSAddIn.1\CLSID; ValueType: string; ValueData: {{1432D665-1AB1-4175-9991-8CCA5FC52578}; Components: WndTabs
#endif

#ifdef INSTALL_KALLISTIOS
Root: HKLM; Subkey: SOFTWARE\DevKitDC; ValueType: string; ValueName: Install_Dir; ValueData: {sd}\DevKitDC; Components: KallistiOS
#endif

;Root: HKLM; Subkey: SOFTWARE\ODBC\ODBCINST.INI\Microsoft FoxPro Driver (*.dbf); ValueType: dword; ValueName: UsageCount; ValueData: $00000001; Components: VisualCpp
Root: HKLM; Subkey: SOFTWARE\ODBC\ODBCINST.INI\Microsoft FoxPro Driver (*.dbf); ValueType: string; ValueName: APILevel; ValueData: 1; Components: VisualCpp
Root: HKLM; Subkey: SOFTWARE\ODBC\ODBCINST.INI\Microsoft FoxPro Driver (*.dbf); ValueType: string; ValueName: ConnectFunctions; ValueData: YYN; Components: VisualCpp
Root: HKLM; Subkey: SOFTWARE\ODBC\ODBCINST.INI\Microsoft FoxPro Driver (*.dbf); ValueType: string; ValueName: Driver; ValueData: {sys}\odbcjt32.dll; Components: VisualCpp
Root: HKLM; Subkey: SOFTWARE\ODBC\ODBCINST.INI\Microsoft FoxPro Driver (*.dbf); ValueType: string; ValueName: DriverODBCVer; ValueData: 02.50; Components: VisualCpp
Root: HKLM; Subkey: SOFTWARE\ODBC\ODBCINST.INI\Microsoft FoxPro Driver (*.dbf); ValueType: string; ValueName: FileExtns; ValueData: *.dbf,*.cdx,*.idx,*.ftp; Components: VisualCpp
Root: HKLM; Subkey: SOFTWARE\ODBC\ODBCINST.INI\Microsoft FoxPro Driver (*.dbf); ValueType: string; ValueName: FileUsage; ValueData: 1; Components: VisualCpp
Root: HKLM; Subkey: SOFTWARE\ODBC\ODBCINST.INI\Microsoft FoxPro Driver (*.dbf); ValueType: string; ValueName: Setup; ValueData: {sys}\odfox32.dll; Components: VisualCpp
Root: HKLM; Subkey: SOFTWARE\ODBC\ODBCINST.INI\Microsoft FoxPro Driver (*.dbf); ValueType: string; ValueName: SQLLevel; ValueData: 0; Components: VisualCpp

;Root: HKLM; Subkey: SOFTWARE\ODBC\ODBCINST.INI\ODBC Core; ValueType: dword; ValueName: UsageCount; ValueData: $00000001; Components: VisualCpp
Root: HKLM; Subkey: SOFTWARE\ODBC\ODBCINST.INI\ODBC Drivers; ValueType: string; ValueName: Microsoft FoxPro Driver (*.dbf); ValueData: Installed; Components: VisualCpp

#ifdef INSTALL_WNDTABS
Root: HKLM; Subkey: SOFTWARE\WndTabs.com\AddInComm; ValueType: string; ValueName: Path; ValueData: {app}\WndTabs; Components: WndTabs

Root: HKLM; Subkey: SOFTWARE\WndTabsExt; ValueType: string; ValueName: UserName; ValueData: HOMEBREW 4DC; Components: WndTabs
Root: HKLM; Subkey: SOFTWARE\WndTabsExt; ValueType: string; ValueName: UserCode; ValueData: 43B68AA0-0BAFT-6D03D6D3; Components: WndTabs
Root: HKLM; Subkey: SOFTWARE\WndTabsExt; ValueType: string; ValueName: LA; ValueData: 00160711; Components: WndTabs
Root: HKLM; Subkey: SOFTWARE\WndTabsExt; ValueType: string; ValueName: FA; ValueData: 00160711; Components: WndTabs
#endif

#ifdef INSTALL_WNDTABS
;Root: HKU; Subkey: .DEFAULT\AppEvents\EventLabels\BuildComplete; ValueType: string; ValueData: Build Complete; Components: WndTabs
;Root: HKU; Subkey: .DEFAULT\AppEvents\EventLabels\BuildError; ValueType: string; ValueData: Build Error; Components: WndTabs
;Root: HKU; Subkey: .DEFAULT\AppEvents\EventLabels\BuildWarning; ValueType: string; ValueData: Build Warning; Components: WndTabs
#endif

#ifdef INSTALL_WNDTABS
;Root: HKU; Subkey: .DEFAULT\AppEvents\EventLabels\MSVC_HitBP; ValueType: string; ValueData: Breakpoint Hit; Components: WndTabs
;Root: HKU; Subkey: .DEFAULT\AppEvents\EventLabels\MSVC_OutputError; ValueType: string; ValueData: Error in Output; Components: WndTabs
;Root: HKU; Subkey: .DEFAULT\AppEvents\EventLabels\MSVC_OutputWarning; ValueType: string; ValueData: Warning in Output; Components: WndTabs
#endif

#ifdef INSTALL_WNDTABS
;Root: HKU; Subkey: .DEFAULT\AppEvents\Schemes\Apps\MSDev; ValueType: string; ValueData: Microsoft Developer; Components: WndTabs
;Root: HKU; Subkey: .DEFAULT\AppEvents\Schemes\Apps\MSDev\BuildComplete; ValueType: string; ValueData: Build Complete; Components: WndTabs
;Root: HKU; Subkey: .DEFAULT\AppEvents\Schemes\Apps\MSDev\BuildError; ValueType: string; ValueData: Build Error; Components: WndTabs
;Root: HKU; Subkey: .DEFAULT\AppEvents\Schemes\Apps\MSDev\BuildWarning; ValueType: string; ValueData: Build Warning; Components: WndTabs
;Root: HKU; Subkey: .DEFAULT\AppEvents\Schemes\Apps\MSDev\MSVC_HitBP; ValueType: string; ValueData: Breakpoint Hit; Components: WndTabs
;Root: HKU; Subkey: .DEFAULT\AppEvents\Schemes\Apps\MSDev\MSVC_OutputError; ValueType: string; ValueData: Error in Output; Components: WndTabs
;Root: HKU; Subkey: .DEFAULT\AppEvents\Schemes\Apps\MSDev\MSVC_OutputWarning; ValueType: string; ValueData: Warning in Output; Components: WndTabs
#endif

#ifdef INSTALL_WNDTABS
Root: HKU; Subkey: .DEFAULT\Software\{#VISUAL_FIRM}\CEStudio\3.0\evc\AddIns\Window Tabs; ValueType: string; ValueData: 1; Components: WndTabs
Root: HKU; Subkey: .DEFAULT\Software\{#VISUAL_FIRM}\CEStudio\3.0\evc\AddIns\Window Tabs; ValueType: string; ValueName: Description; ValueData: Displays tabs of all open windows.; Components: WndTabs
Root: HKU; Subkey: .DEFAULT\Software\{#VISUAL_FIRM}\CEStudio\3.0\evc\AddIns\Window Tabs; ValueType: string; ValueName: DisplayName; ValueData: WndTabs; Components: WndTabs
Root: HKU; Subkey: .DEFAULT\Software\{#VISUAL_FIRM}\CEStudio\3.0\evc\AddIns\Window Tabs; ValueType: string; ValueName: Filename; ValueData: {app}\WndTabs\WndTabs.dll; Components: WndTabs

Root: HKU; Subkey: .DEFAULT\Software\{#VISUAL_FIRM}\CEStudio\3.0\evc\AddIns\WTSDK_Samp.DSAddIn.1; ValueType: string; ValueName: Description; ValueData: A sample of things you can achieve using the WndTabs SDK; Components: WndTabs
Root: HKU; Subkey: .DEFAULT\Software\{#VISUAL_FIRM}\CEStudio\3.0\evc\AddIns\WTSDK_Samp.DSAddIn.1; ValueType: string; ValueName: DisplayName; ValueData: WndTabs SDK Sample Add-In; Components: WndTabs
Root: HKU; Subkey: .DEFAULT\Software\{#VISUAL_FIRM}\CEStudio\3.0\evc\AddIns\WTSDK_Samp.DSAddIn.1; ValueType: string; ValueName: Filename; ValueData: {app}\WndTabs\WTSDK_Samp.dll; Components: WndTabs

Root: HKU; Subkey: .DEFAULT\Software\{#VISUAL_FIRM}\CEStudio\4.0\evc\AddIns\Window Tabs; ValueType: string; ValueData: 1; Components: WndTabs
Root: HKU; Subkey: .DEFAULT\Software\{#VISUAL_FIRM}\CEStudio\4.0\evc\AddIns\Window Tabs; ValueType: string; ValueName: Description; ValueData: Displays tabs of all open windows.; Components: WndTabs
Root: HKU; Subkey: .DEFAULT\Software\{#VISUAL_FIRM}\CEStudio\4.0\evc\AddIns\Window Tabs; ValueType: string; ValueName: DisplayName; ValueData: WndTabs; Components: WndTabs
Root: HKU; Subkey: .DEFAULT\Software\{#VISUAL_FIRM}\CEStudio\4.0\evc\AddIns\Window Tabs; ValueType: string; ValueName: Filename; ValueData: {app}\WndTabs\WndTabs.dll; Components: WndTabs

Root: HKU; Subkey: .DEFAULT\Software\{#VISUAL_FIRM}\CEStudio\4.0\evc\AddIns\WTSDK_Samp.DSAddIn.1; ValueType: string; ValueName: Description; ValueData: A sample of things you can achieve using the WndTabs SDK; Components: WndTabs
Root: HKU; Subkey: .DEFAULT\Software\{#VISUAL_FIRM}\CEStudio\4.0\evc\AddIns\WTSDK_Samp.DSAddIn.1; ValueType: string; ValueName: DisplayName; ValueData: WndTabs SDK Sample Add-In; Components: WndTabs
Root: HKU; Subkey: .DEFAULT\Software\{#VISUAL_FIRM}\CEStudio\4.0\evc\AddIns\WTSDK_Samp.DSAddIn.1; ValueType: string; ValueName: Filename; ValueData: {app}\WndTabs\WTSDK_Samp.dll; Components: WndTabs

Root: HKU; Subkey: .DEFAULT\Software\{#VISUAL_FIRM}\DevStudio\5.0\AddIns\Window Tabs; ValueType: string; ValueData: 1; Components: WndTabs
Root: HKU; Subkey: .DEFAULT\Software\{#VISUAL_FIRM}\DevStudio\5.0\AddIns\Window Tabs; ValueType: string; ValueName: Description; ValueData: Displays tabs of all open windows.; Components: WndTabs
Root: HKU; Subkey: .DEFAULT\Software\{#VISUAL_FIRM}\DevStudio\5.0\AddIns\Window Tabs; ValueType: string; ValueName: DisplayName; ValueData: WndTabs; Components: WndTabs
Root: HKU; Subkey: .DEFAULT\Software\{#VISUAL_FIRM}\DevStudio\5.0\AddIns\Window Tabs; ValueType: string; ValueName: Filename; ValueData: {app}\WndTabs\WndTabs.dll; Components: WndTabs

Root: HKU; Subkey: .DEFAULT\Software\{#VISUAL_FIRM}\DevStudio\5.0\AddIns\WTSDK_Samp.DSAddIn.1; ValueType: string; ValueName: Description; ValueData: A sample of things you can achieve using the WndTabs SDK; Components: WndTabs
Root: HKU; Subkey: .DEFAULT\Software\{#VISUAL_FIRM}\DevStudio\5.0\AddIns\WTSDK_Samp.DSAddIn.1; ValueType: string; ValueName: DisplayName; ValueData: WndTabs SDK Sample Add-In; Components: WndTabs
Root: HKU; Subkey: .DEFAULT\Software\{#VISUAL_FIRM}\DevStudio\5.0\AddIns\WTSDK_Samp.DSAddIn.1; ValueType: string; ValueName: Filename; ValueData: {app}\WndTabs\WTSDK_Samp.dll; Components: WndTabs

Root: HKU; Subkey: .DEFAULT\Software\{#VISUAL_FIRM}\DevStudio\{#VISUAL_VER}.{#VISUAL_REV}\AddIns\Window Tabs; ValueType: string; ValueData: 1; Components: WndTabs
Root: HKU; Subkey: .DEFAULT\Software\{#VISUAL_FIRM}\DevStudio\{#VISUAL_VER}.{#VISUAL_REV}\AddIns\Window Tabs; ValueType: string; ValueName: Description; ValueData: Displays tabs of all open windows.; Components: WndTabs
Root: HKU; Subkey: .DEFAULT\Software\{#VISUAL_FIRM}\DevStudio\{#VISUAL_VER}.{#VISUAL_REV}\AddIns\Window Tabs; ValueType: string; ValueName: DisplayName; ValueData: WndTabs; Components: WndTabs
Root: HKU; Subkey: .DEFAULT\Software\{#VISUAL_FIRM}\DevStudio\{#VISUAL_VER}.{#VISUAL_REV}\AddIns\Window Tabs; ValueType: string; ValueName: Filename; ValueData: {app}\WndTabs\WndTabs.dll; Components: WndTabs

Root: HKU; Subkey: .DEFAULT\Software\{#VISUAL_FIRM}\DevStudio\{#VISUAL_VER}.{#VISUAL_REV}\AddIns\WTSDK_Samp.DSAddIn.1; ValueType: string; ValueData: 1; Components: WndTabs
Root: HKU; Subkey: .DEFAULT\Software\{#VISUAL_FIRM}\DevStudio\{#VISUAL_VER}.{#VISUAL_REV}\AddIns\WTSDK_Samp.DSAddIn.1; ValueType: string; ValueName: Description; ValueData: A sample of things you can achieve using the WndTabs SDK; Components: WndTabs
Root: HKU; Subkey: .DEFAULT\Software\{#VISUAL_FIRM}\DevStudio\{#VISUAL_VER}.{#VISUAL_REV}\AddIns\WTSDK_Samp.DSAddIn.1; ValueType: string; ValueName: DisplayName; ValueData: WndTabs SDK Sample Add-In; Components: WndTabs
Root: HKU; Subkey: .DEFAULT\Software\{#VISUAL_FIRM}\DevStudio\{#VISUAL_VER}.{#VISUAL_REV}\AddIns\WTSDK_Samp.DSAddIn.1; ValueType: string; ValueName: Filename; ValueData: {app}\WndTabs\WTSDK_Samp.dll; Components: WndTabs

;Root: HKU; Subkey: .DEFAULT\Software\{#VISUAL_FIRM}\DevStudio\{#VISUAL_VER}.{#VISUAL_REV}\Build System; ValueType: dword; ValueName: Always export dependencies; ValueData: $00000000; Components: WndTabs
;Root: HKU; Subkey: .DEFAULT\Software\{#VISUAL_FIRM}\DevStudio\{#VISUAL_VER}.{#VISUAL_REV}\Build System; ValueType: dword; ValueName: Always export makefile; ValueData: $00000000; Components: WndTabs
;Root: HKU; Subkey: .DEFAULT\Software\{#VISUAL_FIRM}\DevStudio\{#VISUAL_VER}.{#VISUAL_REV}\Build System; ValueType: dword; ValueName: Makefile Sharability; ValueData: $00000001; Components: WndTabs
;Root: HKU; Subkey: .DEFAULT\Software\{#VISUAL_FIRM}\DevStudio\{#VISUAL_VER}.{#VISUAL_REV}\Build System; ValueType: dword; ValueName: Enable Build Logging; ValueData: $00000001; Components: WndTabs
;Root: HKU; Subkey: .DEFAULT\Software\{#VISUAL_FIRM}\DevStudio\{#VISUAL_VER}.{#VISUAL_REV}\Build System; ValueType: dword; ValueName: HTML Logs; ValueData: $00000001; Components: WndTabs
;Root: HKU; Subkey: .DEFAULT\Software\{#VISUAL_FIRM}\DevStudio\{#VISUAL_VER}.{#VISUAL_REV}\Build System; ValueType: dword; ValueName: Slow Links for Win95; ValueData: $00000000; Components: WndTabs
;Root: HKU; Subkey: .DEFAULT\Software\{#VISUAL_FIRM}\DevStudio\{#VISUAL_VER}.{#VISUAL_REV}\Build System; ValueType: dword; ValueName: Enable UpdateAllDependencies; ValueData: $00000000; Components: WndTabs

;Root: HKU; Subkey: .DEFAULT\Software\{#VISUAL_FIRM}\DevStudio\{#VISUAL_VER}.{#VISUAL_REV}\Build System\Components\Platforms\Win32 (ALPHA)\Execution Models; ValueType: string; ValueName: Current EM; ValueData: EM; Components: WndTabs
;Root: HKU; Subkey: .DEFAULT\Software\{#VISUAL_FIRM}\DevStudio\{#VISUAL_VER}.{#VISUAL_REV}\Build System\Components\Platforms\Win32 (ALPHA)\Expression Evaluators; ValueType: string; ValueName: Current EE; ValueData: EECXX; Components: WndTabs
;Root: HKU; Subkey: .DEFAULT\Software\{#VISUAL_FIRM}\DevStudio\{#VISUAL_VER}.{#VISUAL_REV}\Build System\Components\Platforms\Win32 (ALPHA)\Symbol Handlers; ValueType: string; ValueName: Current SH; ValueData: SHCV; Components: WndTabs

;Root: HKU; Subkey: .DEFAULT\Software\{#VISUAL_FIRM}\DevStudio\{#VISUAL_VER}.{#VISUAL_REV}\Build System\Components\Platforms\Win32 (ALPHA)\Tools\C/C++ Compiler for Alpha; ValueType: string; ValueName: Executable Path; ValueData: cl.exe; Components: WndTabs
;Root: HKU; Subkey: .DEFAULT\Software\{#VISUAL_FIRM}\DevStudio\{#VISUAL_VER}.{#VISUAL_REV}\Build System\Components\Platforms\Win32 (ALPHA)\Tools\C/C++ Compiler for Alpha; ValueType: string; ValueName: Macro_Prefix; ValueData: CPP; Components: WndTabs
;Root: HKU; Subkey: .DEFAULT\Software\{#VISUAL_FIRM}\DevStudio\{#VISUAL_VER}.{#VISUAL_REV}\Build System\Components\Platforms\Win32 (ALPHA)\Tools\C/C++ Compiler for Alpha; ValueType: string; ValueName: Input_Spec; ValueData: *.c;*.cpp;*.cxx; Components: WndTabs
;Root: HKU; Subkey: .DEFAULT\Software\{#VISUAL_FIRM}\DevStudio\{#VISUAL_VER}.{#VISUAL_REV}\Build System\Components\Platforms\Win32 (ALPHA)\Tools\C/C++ Compiler for Alpha; ValueType: string; ValueName: Output_Spec; Components: WndTabs
;Root: HKU; Subkey: .DEFAULT\Software\{#VISUAL_FIRM}\DevStudio\{#VISUAL_VER}.{#VISUAL_REV}\Build System\Components\Platforms\Win32 (ALPHA)\Tools\C/C++ Compiler for Alpha; ValueType: string; ValueName: Menu Text; Components: WndTabs
;Root: HKU; Subkey: .DEFAULT\Software\{#VISUAL_FIRM}\DevStudio\{#VISUAL_VER}.{#VISUAL_REV}\Build System\Components\Platforms\Win32 (ALPHA)\Tools\C/C++ Compiler for Alpha; ValueType: dword; ValueName: Internal; ValueData: $00000001; Components: WndTabs
;Root: HKU; Subkey: .DEFAULT\Software\{#VISUAL_FIRM}\DevStudio\{#VISUAL_VER}.{#VISUAL_REV}\Build System\Components\Platforms\Win32 (ALPHA)\Tools\C/C++ Compiler for Alpha; ValueType: dword; ValueName: Perform_If_Able; ValueData: $00000000; Components: WndTabs
;Root: HKU; Subkey: .DEFAULT\Software\{#VISUAL_FIRM}\DevStudio\{#VISUAL_VER}.{#VISUAL_REV}\Build System\Components\Platforms\Win32 (ALPHA)\Tools\C/C++ Compiler for Alpha; ValueType: dword; ValueName: Deferred; ValueData: $00000000; Components: WndTabs

;Root: HKU; Subkey: .DEFAULT\Software\{#VISUAL_FIRM}\DevStudio\{#VISUAL_VER}.{#VISUAL_REV}\Build System\Components\Platforms\Win32 (ALPHA)\Tools\COFF Linker for Alpha; ValueType: string; ValueName: Executable Path; ValueData: link.exe; Components: WndTabs
;Root: HKU; Subkey: .DEFAULT\Software\{#VISUAL_FIRM}\DevStudio\{#VISUAL_VER}.{#VISUAL_REV}\Build System\Components\Platforms\Win32 (ALPHA)\Tools\COFF Linker for Alpha; ValueType: string; ValueName: Macro_Prefix; ValueData: LINK32; Components: WndTabs
;Root: HKU; Subkey: .DEFAULT\Software\{#VISUAL_FIRM}\DevStudio\{#VISUAL_VER}.{#VISUAL_REV}\Build System\Components\Platforms\Win32 (ALPHA)\Tools\COFF Linker for Alpha; ValueType: string; ValueName: Input_Spec; ValueData: *.obj;*.res;*.lib;*.def;*.rsc; Components: WndTabs
;Root: HKU; Subkey: .DEFAULT\Software\{#VISUAL_FIRM}\DevStudio\{#VISUAL_VER}.{#VISUAL_REV}\Build System\Components\Platforms\Win32 (ALPHA)\Tools\COFF Linker for Alpha; ValueType: string; ValueName: Output_Spec; Components: WndTabs
;Root: HKU; Subkey: .DEFAULT\Software\{#VISUAL_FIRM}\DevStudio\{#VISUAL_VER}.{#VISUAL_REV}\Build System\Components\Platforms\Win32 (ALPHA)\Tools\COFF Linker for Alpha; ValueType: string; ValueName: Menu Text; Components: WndTabs
;Root: HKU; Subkey: .DEFAULT\Software\{#VISUAL_FIRM}\DevStudio\{#VISUAL_VER}.{#VISUAL_REV}\Build System\Components\Platforms\Win32 (ALPHA)\Tools\COFF Linker for Alpha; ValueType: dword; ValueName: Internal; ValueData: $00000001; Components: WndTabs
;Root: HKU; Subkey: .DEFAULT\Software\{#VISUAL_FIRM}\DevStudio\{#VISUAL_VER}.{#VISUAL_REV}\Build System\Components\Platforms\Win32 (ALPHA)\Tools\COFF Linker for Alpha; ValueType: dword; ValueName: Perform_If_Able; ValueData: $00000000; Components: WndTabs
;Root: HKU; Subkey: .DEFAULT\Software\{#VISUAL_FIRM}\DevStudio\{#VISUAL_VER}.{#VISUAL_REV}\Build System\Components\Platforms\Win32 (ALPHA)\Tools\COFF Linker for Alpha; ValueType: dword; ValueName: Deferred; ValueData: $00000000; Components: WndTabs

;Root: HKU; Subkey: .DEFAULT\Software\{#VISUAL_FIRM}\DevStudio\{#VISUAL_VER}.{#VISUAL_REV}\Build System\Components\Platforms\Win32 (ALPHA)\Transports; ValueType: string; ValueName: Current TL; ValueData: TLLOC; Components: WndTabs

;Root: HKU; Subkey: .DEFAULT\Software\{#VISUAL_FIRM}\DevStudio\{#VISUAL_VER}.{#VISUAL_REV}\Build System\Components\Platforms\Win32 (ALPHA)\Transports\TLLOC; ValueType: dword; ValueName: TL Attributes; ValueData: $00000001; Components: WndTabs
;Root: HKU; Subkey: .DEFAULT\Software\{#VISUAL_FIRM}\DevStudio\{#VISUAL_VER}.{#VISUAL_REV}\Build System\Components\Platforms\Win32 (ALPHA)\Transports\TLLOC; ValueType: string; ValueName: TL Description; ValueData: Local; Components: WndTabs

;Root: HKU; Subkey: .DEFAULT\Software\{#VISUAL_FIRM}\DevStudio\{#VISUAL_VER}.{#VISUAL_REV}\Build System\Components\Platforms\Win32 (ALPHA)\Transports\TLN0T; ValueType: dword; ValueName: TL Attributes; ValueData: $00000002; Components: WndTabs
;Root: HKU; Subkey: .DEFAULT\Software\{#VISUAL_FIRM}\DevStudio\{#VISUAL_VER}.{#VISUAL_REV}\Build System\Components\Platforms\Win32 (ALPHA)\Transports\TLN0T; ValueType: string; ValueName: TL Description; ValueData: Network (TCP/IP); Components: WndTabs

;Root: HKU; Subkey: .DEFAULT\Software\{#VISUAL_FIRM}\DevStudio\{#VISUAL_VER}.{#VISUAL_REV}\Build System\Components\Platforms\Win32 (x86)\Directories; ValueType: string; ValueName: Path Dirs; ValueData: {app}\Common\MSDev98\Bin;{app}\VC98\BIN;{app}\Common\TOOLS;{app}\Common\TOOLS\WINNT;{win}\system32;{win};{win}\system32\WBEM; Components: WndTabs
;Root: HKU; Subkey: .DEFAULT\Software\{#VISUAL_FIRM}\DevStudio\{#VISUAL_VER}.{#VISUAL_REV}\Build System\Components\Platforms\Win32 (x86)\Directories; ValueType: string; ValueName: Include Dirs; ValueData: {app}\VC98\INCLUDE;{app}\VC98\MFC\INCLUDE;{app}\VC98\ATL\INCLUDE; Components: WndTabs
;Root: HKU; Subkey: .DEFAULT\Software\{#VISUAL_FIRM}\DevStudio\{#VISUAL_VER}.{#VISUAL_REV}\Build System\Components\Platforms\Win32 (x86)\Directories; ValueType: string; ValueName: Library Dirs; ValueData: {app}\VC98\LIB;{app}\VC98\MFC\LIB; Components: WndTabs
;Root: HKU; Subkey: .DEFAULT\Software\{#VISUAL_FIRM}\DevStudio\{#VISUAL_VER}.{#VISUAL_REV}\Build System\Components\Platforms\Win32 (x86)\Directories; ValueType: string; ValueName: Source Dirs; ValueData: {app}\VC98\MFC\SRC;{app}\VC98\MFC\INCLUDE;{app}\VC98\ATL\INCLUDE;{app}\VC98\CRT\SRC; Components: WndTabs

;Root: HKU; Subkey: .DEFAULT\Software\{#VISUAL_FIRM}\DevStudio\{#VISUAL_VER}.{#VISUAL_REV}\Build System\Components\Platforms\Win32 (x86)\Execution Models; ValueType: string; ValueName: Current EM; ValueData: EM; Components: WndTabs

;Root: HKU; Subkey: .DEFAULT\Software\{#VISUAL_FIRM}\DevStudio\{#VISUAL_VER}.{#VISUAL_REV}\Build System\Components\Platforms\Win32 (x86)\Expression Evaluators; ValueType: string; ValueName: Current EE; ValueData: EECXX; Components: WndTabs

;Root: HKU; Subkey: .DEFAULT\Software\{#VISUAL_FIRM}\DevStudio\{#VISUAL_VER}.{#VISUAL_REV}\Build System\Components\Platforms\Win32 (x86)\Symbol Handlers; ValueType: string; ValueName: Current SH; ValueData: SHCV; Components: WndTabs

;Root: HKU; Subkey: .DEFAULT\Software\{#VISUAL_FIRM}\DevStudio\{#VISUAL_VER}.{#VISUAL_REV}\Build System\Components\Platforms\Win32 (x86)\Tools\32-bit C/C++ Compiler for 80x86; ValueType: string; ValueName: Executable Path; ValueData: cl.exe; Components: WndTabs
;Root: HKU; Subkey: .DEFAULT\Software\{#VISUAL_FIRM}\DevStudio\{#VISUAL_VER}.{#VISUAL_REV}\Build System\Components\Platforms\Win32 (x86)\Tools\32-bit C/C++ Compiler for 80x86; ValueType: string; ValueName: Macro_Prefix; ValueData: CPP; Components: WndTabs
;Root: HKU; Subkey: .DEFAULT\Software\{#VISUAL_FIRM}\DevStudio\{#VISUAL_VER}.{#VISUAL_REV}\Build System\Components\Platforms\Win32 (x86)\Tools\32-bit C/C++ Compiler for 80x86; ValueType: string; ValueName: Input_Spec; ValueData: *.c;*.cpp;*.cxx; Components: WndTabs
;Root: HKU; Subkey: .DEFAULT\Software\{#VISUAL_FIRM}\DevStudio\{#VISUAL_VER}.{#VISUAL_REV}\Build System\Components\Platforms\Win32 (x86)\Tools\32-bit C/C++ Compiler for 80x86; ValueType: string; ValueName: Output_Spec; Components: WndTabs
;Root: HKU; Subkey: .DEFAULT\Software\{#VISUAL_FIRM}\DevStudio\{#VISUAL_VER}.{#VISUAL_REV}\Build System\Components\Platforms\Win32 (x86)\Tools\32-bit C/C++ Compiler for 80x86; ValueType: string; ValueName: Menu Text; Components: WndTabs
;Root: HKU; Subkey: .DEFAULT\Software\{#VISUAL_FIRM}\DevStudio\{#VISUAL_VER}.{#VISUAL_REV}\Build System\Components\Platforms\Win32 (x86)\Tools\32-bit C/C++ Compiler for 80x86; ValueType: dword; ValueName: Internal; ValueData: $00000001; Components: WndTabs
;Root: HKU; Subkey: .DEFAULT\Software\{#VISUAL_FIRM}\DevStudio\{#VISUAL_VER}.{#VISUAL_REV}\Build System\Components\Platforms\Win32 (x86)\Tools\32-bit C/C++ Compiler for 80x86; ValueType: dword; ValueName: Perform_If_Able; ValueData: $00000000; Components: WndTabs
;Root: HKU; Subkey: .DEFAULT\Software\{#VISUAL_FIRM}\DevStudio\{#VISUAL_VER}.{#VISUAL_REV}\Build System\Components\Platforms\Win32 (x86)\Tools\32-bit C/C++ Compiler for 80x86; ValueType: dword; ValueName: Deferred; ValueData: $00000000; Components: WndTabs

;Root: HKU; Subkey: .DEFAULT\Software\{#VISUAL_FIRM}\DevStudio\{#VISUAL_VER}.{#VISUAL_REV}\Build System\Components\Platforms\Win32 (x86)\Tools\COFF Linker for 80x86; ValueType: string; ValueName: Executable Path; ValueData: link.exe; Components: WndTabs
;Root: HKU; Subkey: .DEFAULT\Software\{#VISUAL_FIRM}\DevStudio\{#VISUAL_VER}.{#VISUAL_REV}\Build System\Components\Platforms\Win32 (x86)\Tools\COFF Linker for 80x86; ValueType: string; ValueName: Macro_Prefix; ValueData: LINK32; Components: WndTabs
;Root: HKU; Subkey: .DEFAULT\Software\{#VISUAL_FIRM}\DevStudio\{#VISUAL_VER}.{#VISUAL_REV}\Build System\Components\Platforms\Win32 (x86)\Tools\COFF Linker for 80x86; ValueType: string; ValueName: Input_Spec; ValueData: *.obj;*.res;*.lib;*.def;*.rsc; Components: WndTabs
;Root: HKU; Subkey: .DEFAULT\Software\{#VISUAL_FIRM}\DevStudio\{#VISUAL_VER}.{#VISUAL_REV}\Build System\Components\Platforms\Win32 (x86)\Tools\COFF Linker for 80x86; ValueType: string; ValueName: Output_Spec; Components: WndTabs
;Root: HKU; Subkey: .DEFAULT\Software\{#VISUAL_FIRM}\DevStudio\{#VISUAL_VER}.{#VISUAL_REV}\Build System\Components\Platforms\Win32 (x86)\Tools\COFF Linker for 80x86; ValueType: string; ValueName: Menu Text; Components: WndTabs
;Root: HKU; Subkey: .DEFAULT\Software\{#VISUAL_FIRM}\DevStudio\{#VISUAL_VER}.{#VISUAL_REV}\Build System\Components\Platforms\Win32 (x86)\Tools\COFF Linker for 80x86; ValueType: dword; ValueName: Internal; ValueData: $00000001; Components: WndTabs
;Root: HKU; Subkey: .DEFAULT\Software\{#VISUAL_FIRM}\DevStudio\{#VISUAL_VER}.{#VISUAL_REV}\Build System\Components\Platforms\Win32 (x86)\Tools\COFF Linker for 80x86; ValueType: dword; ValueName: Perform_If_Able; ValueData: $00000000; Components: WndTabs
;Root: HKU; Subkey: .DEFAULT\Software\{#VISUAL_FIRM}\DevStudio\{#VISUAL_VER}.{#VISUAL_REV}\Build System\Components\Platforms\Win32 (x86)\Tools\COFF Linker for 80x86; ValueType: dword; ValueName: Deferred; ValueData: $00000000; Components: WndTabs

;Root: HKU; Subkey: .DEFAULT\Software\{#VISUAL_FIRM}\DevStudio\{#VISUAL_VER}.{#VISUAL_REV}\Build System\Components\Platforms\Win32 (x86)\Transports; ValueType: string; ValueName: Current TL; ValueData: TLLOC; Components: WndTabs

;Root: HKU; Subkey: .DEFAULT\Software\{#VISUAL_FIRM}\DevStudio\{#VISUAL_VER}.{#VISUAL_REV}\Build System\Components\Platforms\Win32 (x86)\Transports\TLLOC; ValueType: dword; ValueName: TL Attributes; ValueData: $00000001; Components: WndTabs
;Root: HKU; Subkey: .DEFAULT\Software\{#VISUAL_FIRM}\DevStudio\{#VISUAL_VER}.{#VISUAL_REV}\Build System\Components\Platforms\Win32 (x86)\Transports\TLLOC; ValueType: string; ValueName: TL Description; ValueData: Local; Components: WndTabs

;Root: HKU; Subkey: .DEFAULT\Software\{#VISUAL_FIRM}\DevStudio\{#VISUAL_VER}.{#VISUAL_REV}\Build System\Components\Platforms\Win32 (x86)\Transports\TLN0T; ValueType: dword; ValueName: TL Attributes; ValueData: $00000002; Components: WndTabs
;Root: HKU; Subkey: .DEFAULT\Software\{#VISUAL_FIRM}\DevStudio\{#VISUAL_VER}.{#VISUAL_REV}\Build System\Components\Platforms\Win32 (x86)\Transports\TLN0T; ValueType: string; ValueName: TL Description; ValueData: Network (TCP/IP); Components: WndTabs

;Root: HKU; Subkey: .DEFAULT\Software\{#VISUAL_FIRM}\DevStudio\{#VISUAL_VER}.{#VISUAL_REV}\Build System\Components\Tools\<Component 0x3>; ValueType: string; ValueName: Executable Path; ValueData: cl.exe; Components: WndTabs
;Root: HKU; Subkey: .DEFAULT\Software\{#VISUAL_FIRM}\DevStudio\{#VISUAL_VER}.{#VISUAL_REV}\Build System\Components\Tools\<Component 0x3>; ValueType: string; ValueName: Macro_Prefix; ValueData: CPP; Components: WndTabs
;Root: HKU; Subkey: .DEFAULT\Software\{#VISUAL_FIRM}\DevStudio\{#VISUAL_VER}.{#VISUAL_REV}\Build System\Components\Tools\<Component 0x3>; ValueType: string; ValueName: Input_Spec; ValueData: *.c;*.cpp;*.cxx; Components: WndTabs
;Root: HKU; Subkey: .DEFAULT\Software\{#VISUAL_FIRM}\DevStudio\{#VISUAL_VER}.{#VISUAL_REV}\Build System\Components\Tools\<Component 0x3>; ValueType: string; ValueName: Output_Spec; Components: WndTabs
;Root: HKU; Subkey: .DEFAULT\Software\{#VISUAL_FIRM}\DevStudio\{#VISUAL_VER}.{#VISUAL_REV}\Build System\Components\Tools\<Component 0x3>; ValueType: string; ValueName: Menu Text; Components: WndTabs
;Root: HKU; Subkey: .DEFAULT\Software\{#VISUAL_FIRM}\DevStudio\{#VISUAL_VER}.{#VISUAL_REV}\Build System\Components\Tools\<Component 0x3>; ValueType: dword; ValueName: Internal; ValueData: $00000001; Components: WndTabs
;Root: HKU; Subkey: .DEFAULT\Software\{#VISUAL_FIRM}\DevStudio\{#VISUAL_VER}.{#VISUAL_REV}\Build System\Components\Tools\<Component 0x3>; ValueType: dword; ValueName: Perform_If_Able; ValueData: $00000000; Components: WndTabs
;Root: HKU; Subkey: .DEFAULT\Software\{#VISUAL_FIRM}\DevStudio\{#VISUAL_VER}.{#VISUAL_REV}\Build System\Components\Tools\<Component 0x3>; ValueType: dword; ValueName: Deferred; ValueData: $00000000; Components: WndTabs

;Root: HKU; Subkey: .DEFAULT\Software\{#VISUAL_FIRM}\DevStudio\{#VISUAL_VER}.{#VISUAL_REV}\Build System\Components\Tools\<Component 0x4>; ValueType: string; ValueName: Executable Path; ValueData: link.exe; Components: WndTabs
;Root: HKU; Subkey: .DEFAULT\Software\{#VISUAL_FIRM}\DevStudio\{#VISUAL_VER}.{#VISUAL_REV}\Build System\Components\Tools\<Component 0x4>; ValueType: string; ValueName: Macro_Prefix; ValueData: LINK32; Components: WndTabs
;Root: HKU; Subkey: .DEFAULT\Software\{#VISUAL_FIRM}\DevStudio\{#VISUAL_VER}.{#VISUAL_REV}\Build System\Components\Tools\<Component 0x4>; ValueType: string; ValueName: Input_Spec; ValueData: *.obj;*.res;*.lib;*.def;*.rsc; Components: WndTabs
;Root: HKU; Subkey: .DEFAULT\Software\{#VISUAL_FIRM}\DevStudio\{#VISUAL_VER}.{#VISUAL_REV}\Build System\Components\Tools\<Component 0x4>; ValueType: string; ValueName: Output_Spec; Components: WndTabs
;Root: HKU; Subkey: .DEFAULT\Software\{#VISUAL_FIRM}\DevStudio\{#VISUAL_VER}.{#VISUAL_REV}\Build System\Components\Tools\<Component 0x4>; ValueType: string; ValueName: Menu Text; Components: WndTabs
;Root: HKU; Subkey: .DEFAULT\Software\{#VISUAL_FIRM}\DevStudio\{#VISUAL_VER}.{#VISUAL_REV}\Build System\Components\Tools\<Component 0x4>; ValueType: dword; ValueName: Internal; ValueData: $00000001; Components: WndTabs
;Root: HKU; Subkey: .DEFAULT\Software\{#VISUAL_FIRM}\DevStudio\{#VISUAL_VER}.{#VISUAL_REV}\Build System\Components\Tools\<Component 0x4>; ValueType: dword; ValueName: Perform_If_Able; ValueData: $00000000; Components: WndTabs
;Root: HKU; Subkey: .DEFAULT\Software\{#VISUAL_FIRM}\DevStudio\{#VISUAL_VER}.{#VISUAL_REV}\Build System\Components\Tools\<Component 0x4>; ValueType: dword; ValueName: Deferred; ValueData: $00000000; Components: WndTabs

;Root: HKU; Subkey: .DEFAULT\Software\{#VISUAL_FIRM}\DevStudio\{#VISUAL_VER}.{#VISUAL_REV}\Build System\Components\Tools\<Component 0x5>; ValueType: string; ValueName: Executable Path; ValueData: link.exe; Components: WndTabs
;Root: HKU; Subkey: .DEFAULT\Software\{#VISUAL_FIRM}\DevStudio\{#VISUAL_VER}.{#VISUAL_REV}\Build System\Components\Tools\<Component 0x5>; ValueType: string; ValueName: Macro_Prefix; ValueData: LINK32; Components: WndTabs
;Root: HKU; Subkey: .DEFAULT\Software\{#VISUAL_FIRM}\DevStudio\{#VISUAL_VER}.{#VISUAL_REV}\Build System\Components\Tools\<Component 0x5>; ValueType: string; ValueName: Input_Spec; ValueData: *.obj;*.res;*.lib;*.def;*.rsc; Components: WndTabs
;Root: HKU; Subkey: .DEFAULT\Software\{#VISUAL_FIRM}\DevStudio\{#VISUAL_VER}.{#VISUAL_REV}\Build System\Components\Tools\<Component 0x5>; ValueType: string; ValueName: Output_Spec; Components: WndTabs
;Root: HKU; Subkey: .DEFAULT\Software\{#VISUAL_FIRM}\DevStudio\{#VISUAL_VER}.{#VISUAL_REV}\Build System\Components\Tools\<Component 0x5>; ValueType: string; ValueName: Menu Text; Components: WndTabs
;Root: HKU; Subkey: .DEFAULT\Software\{#VISUAL_FIRM}\DevStudio\{#VISUAL_VER}.{#VISUAL_REV}\Build System\Components\Tools\<Component 0x5>; ValueType: dword; ValueName: Internal; ValueData: $00000001; Components: WndTabs
;Root: HKU; Subkey: .DEFAULT\Software\{#VISUAL_FIRM}\DevStudio\{#VISUAL_VER}.{#VISUAL_REV}\Build System\Components\Tools\<Component 0x5>; ValueType: dword; ValueName: Perform_If_Able; ValueData: $00000000; Components: WndTabs
;Root: HKU; Subkey: .DEFAULT\Software\{#VISUAL_FIRM}\DevStudio\{#VISUAL_VER}.{#VISUAL_REV}\Build System\Components\Tools\<Component 0x5>; ValueType: dword; ValueName: Deferred; ValueData: $00000000; Components: WndTabs

;Root: HKU; Subkey: .DEFAULT\Software\{#VISUAL_FIRM}\DevStudio\{#VISUAL_VER}.{#VISUAL_REV}\Build System\Components\Tools\<Component 0xa>; ValueType: string; ValueName: Executable Path; Components: WndTabs
;Root: HKU; Subkey: .DEFAULT\Software\{#VISUAL_FIRM}\DevStudio\{#VISUAL_VER}.{#VISUAL_REV}\Build System\Components\Tools\<Component 0xa>; ValueType: string; ValueName: Macro_Prefix; Components: WndTabs
;Root: HKU; Subkey: .DEFAULT\Software\{#VISUAL_FIRM}\DevStudio\{#VISUAL_VER}.{#VISUAL_REV}\Build System\Components\Tools\<Component 0xa>; ValueType: string; ValueName: Input_Spec; Components: WndTabs
;Root: HKU; Subkey: .DEFAULT\Software\{#VISUAL_FIRM}\DevStudio\{#VISUAL_VER}.{#VISUAL_REV}\Build System\Components\Tools\<Component 0xa>; ValueType: string; ValueName: Output_Spec; Components: WndTabs
;Root: HKU; Subkey: .DEFAULT\Software\{#VISUAL_FIRM}\DevStudio\{#VISUAL_VER}.{#VISUAL_REV}\Build System\Components\Tools\<Component 0xa>; ValueType: string; ValueName: Menu Text; Components: WndTabs
;Root: HKU; Subkey: .DEFAULT\Software\{#VISUAL_FIRM}\DevStudio\{#VISUAL_VER}.{#VISUAL_REV}\Build System\Components\Tools\<Component 0xa>; ValueType: dword; ValueName: Internal; ValueData: $00000000; Components: WndTabs
;Root: HKU; Subkey: .DEFAULT\Software\{#VISUAL_FIRM}\DevStudio\{#VISUAL_VER}.{#VISUAL_REV}\Build System\Components\Tools\<Component 0xa>; ValueType: dword; ValueName: Perform_If_Able; ValueData: $00000000; Components: WndTabs
;Root: HKU; Subkey: .DEFAULT\Software\{#VISUAL_FIRM}\DevStudio\{#VISUAL_VER}.{#VISUAL_REV}\Build System\Components\Tools\<Component 0xa>; ValueType: dword; ValueName: Deferred; ValueData: $00000000; Components: WndTabs

;Root: HKU; Subkey: .DEFAULT\Software\{#VISUAL_FIRM}\DevStudio\{#VISUAL_VER}.{#VISUAL_REV}\Build System\Components\Tools\Browser Database Maker; ValueType: string; ValueName: Executable Path; ValueData: bscmake.exe; Components: WndTabs
;Root: HKU; Subkey: .DEFAULT\Software\{#VISUAL_FIRM}\DevStudio\{#VISUAL_VER}.{#VISUAL_REV}\Build System\Components\Tools\Browser Database Maker; ValueType: string; ValueName: Macro_Prefix; ValueData: BSC32; Components: WndTabs
;Root: HKU; Subkey: .DEFAULT\Software\{#VISUAL_FIRM}\DevStudio\{#VISUAL_VER}.{#VISUAL_REV}\Build System\Components\Tools\Browser Database Maker; ValueType: string; ValueName: Input_Spec; ValueData: *.sbr; Components: WndTabs
;Root: HKU; Subkey: .DEFAULT\Software\{#VISUAL_FIRM}\DevStudio\{#VISUAL_VER}.{#VISUAL_REV}\Build System\Components\Tools\Browser Database Maker; ValueType: string; ValueName: Output_Spec; Components: WndTabs
;Root: HKU; Subkey: .DEFAULT\Software\{#VISUAL_FIRM}\DevStudio\{#VISUAL_VER}.{#VISUAL_REV}\Build System\Components\Tools\Browser Database Maker; ValueType: string; ValueName: Menu Text; Components: WndTabs
;Root: HKU; Subkey: .DEFAULT\Software\{#VISUAL_FIRM}\DevStudio\{#VISUAL_VER}.{#VISUAL_REV}\Build System\Components\Tools\Browser Database Maker; ValueType: dword; ValueName: Internal; ValueData: $00000001; Components: WndTabs
;Root: HKU; Subkey: .DEFAULT\Software\{#VISUAL_FIRM}\DevStudio\{#VISUAL_VER}.{#VISUAL_REV}\Build System\Components\Tools\Browser Database Maker; ValueType: dword; ValueName: Perform_If_Able; ValueData: $00000001; Components: WndTabs
;Root: HKU; Subkey: .DEFAULT\Software\{#VISUAL_FIRM}\DevStudio\{#VISUAL_VER}.{#VISUAL_REV}\Build System\Components\Tools\Browser Database Maker; ValueType: dword; ValueName: Deferred; ValueData: $00000001; Components: WndTabs

;Root: HKU; Subkey: .DEFAULT\Software\{#VISUAL_FIRM}\DevStudio\{#VISUAL_VER}.{#VISUAL_REV}\Build System\Components\Tools\Custom Build; ValueType: string; ValueName: Executable Path; Components: WndTabs
;Root: HKU; Subkey: .DEFAULT\Software\{#VISUAL_FIRM}\DevStudio\{#VISUAL_VER}.{#VISUAL_REV}\Build System\Components\Tools\Custom Build; ValueType: string; ValueName: Macro_Prefix; Components: WndTabs
;Root: HKU; Subkey: .DEFAULT\Software\{#VISUAL_FIRM}\DevStudio\{#VISUAL_VER}.{#VISUAL_REV}\Build System\Components\Tools\Custom Build; ValueType: string; ValueName: Input_Spec; Components: WndTabs
;Root: HKU; Subkey: .DEFAULT\Software\{#VISUAL_FIRM}\DevStudio\{#VISUAL_VER}.{#VISUAL_REV}\Build System\Components\Tools\Custom Build; ValueType: string; ValueName: Output_Spec; Components: WndTabs
;Root: HKU; Subkey: .DEFAULT\Software\{#VISUAL_FIRM}\DevStudio\{#VISUAL_VER}.{#VISUAL_REV}\Build System\Components\Tools\Custom Build; ValueType: string; ValueName: Menu Text; Components: WndTabs
;Root: HKU; Subkey: .DEFAULT\Software\{#VISUAL_FIRM}\DevStudio\{#VISUAL_VER}.{#VISUAL_REV}\Build System\Components\Tools\Custom Build; ValueType: dword; ValueName: Internal; ValueData: $00000000; Components: WndTabs
;Root: HKU; Subkey: .DEFAULT\Software\{#VISUAL_FIRM}\DevStudio\{#VISUAL_VER}.{#VISUAL_REV}\Build System\Components\Tools\Custom Build; ValueType: dword; ValueName: Perform_If_Able; ValueData: $00000000; Components: WndTabs
;Root: HKU; Subkey: .DEFAULT\Software\{#VISUAL_FIRM}\DevStudio\{#VISUAL_VER}.{#VISUAL_REV}\Build System\Components\Tools\Custom Build; ValueType: dword; ValueName: Deferred; ValueData: $00000000; Components: WndTabs

;Root: HKU; Subkey: .DEFAULT\Software\{#VISUAL_FIRM}\DevStudio\{#VISUAL_VER}.{#VISUAL_REV}\Build System\Components\Tools\Library Manager; ValueType: string; ValueName: Executable Path; ValueData: link.exe -lib; Components: WndTabs
;Root: HKU; Subkey: .DEFAULT\Software\{#VISUAL_FIRM}\DevStudio\{#VISUAL_VER}.{#VISUAL_REV}\Build System\Components\Tools\Library Manager; ValueType: string; ValueName: Macro_Prefix; ValueData: LIB32; Components: WndTabs
;Root: HKU; Subkey: .DEFAULT\Software\{#VISUAL_FIRM}\DevStudio\{#VISUAL_VER}.{#VISUAL_REV}\Build System\Components\Tools\Library Manager; ValueType: string; ValueName: Input_Spec; ValueData: *.obj;*.res;*.lib; Components: WndTabs
;Root: HKU; Subkey: .DEFAULT\Software\{#VISUAL_FIRM}\DevStudio\{#VISUAL_VER}.{#VISUAL_REV}\Build System\Components\Tools\Library Manager; ValueType: string; ValueName: Output_Spec; Components: WndTabs
;Root: HKU; Subkey: .DEFAULT\Software\{#VISUAL_FIRM}\DevStudio\{#VISUAL_VER}.{#VISUAL_REV}\Build System\Components\Tools\Library Manager; ValueType: string; ValueName: Menu Text; Components: WndTabs
;Root: HKU; Subkey: .DEFAULT\Software\{#VISUAL_FIRM}\DevStudio\{#VISUAL_VER}.{#VISUAL_REV}\Build System\Components\Tools\Library Manager; ValueType: dword; ValueName: Internal; ValueData: $00000001; Components: WndTabs
;Root: HKU; Subkey: .DEFAULT\Software\{#VISUAL_FIRM}\DevStudio\{#VISUAL_VER}.{#VISUAL_REV}\Build System\Components\Tools\Library Manager; ValueType: dword; ValueName: Perform_If_Able; ValueData: $00000000; Components: WndTabs
;Root: HKU; Subkey: .DEFAULT\Software\{#VISUAL_FIRM}\DevStudio\{#VISUAL_VER}.{#VISUAL_REV}\Build System\Components\Tools\Library Manager; ValueType: dword; ValueName: Deferred; ValueData: $00000000; Components: WndTabs

;Root: HKU; Subkey: .DEFAULT\Software\{#VISUAL_FIRM}\DevStudio\{#VISUAL_VER}.{#VISUAL_REV}\Build System\Components\Tools\OLE Type Library Maker; ValueType: string; ValueName: Executable Path; ValueData: midl.exe; Components: WndTabs
;Root: HKU; Subkey: .DEFAULT\Software\{#VISUAL_FIRM}\DevStudio\{#VISUAL_VER}.{#VISUAL_REV}\Build System\Components\Tools\OLE Type Library Maker; ValueType: string; ValueName: Macro_Prefix; ValueData: MTL; Components: WndTabs
;Root: HKU; Subkey: .DEFAULT\Software\{#VISUAL_FIRM}\DevStudio\{#VISUAL_VER}.{#VISUAL_REV}\Build System\Components\Tools\OLE Type Library Maker; ValueType: string; ValueName: Input_Spec; ValueData: *.odl;*.idl; Components: WndTabs
;Root: HKU; Subkey: .DEFAULT\Software\{#VISUAL_FIRM}\DevStudio\{#VISUAL_VER}.{#VISUAL_REV}\Build System\Components\Tools\OLE Type Library Maker; ValueType: string; ValueName: Output_Spec; Components: WndTabs
;Root: HKU; Subkey: .DEFAULT\Software\{#VISUAL_FIRM}\DevStudio\{#VISUAL_VER}.{#VISUAL_REV}\Build System\Components\Tools\OLE Type Library Maker; ValueType: string; ValueName: Menu Text; Components: WndTabs
;Root: HKU; Subkey: .DEFAULT\Software\{#VISUAL_FIRM}\DevStudio\{#VISUAL_VER}.{#VISUAL_REV}\Build System\Components\Tools\OLE Type Library Maker; ValueType: dword; ValueName: Internal; ValueData: $00000001; Components: WndTabs
;Root: HKU; Subkey: .DEFAULT\Software\{#VISUAL_FIRM}\DevStudio\{#VISUAL_VER}.{#VISUAL_REV}\Build System\Components\Tools\OLE Type Library Maker; ValueType: dword; ValueName: Perform_If_Able; ValueData: $00000000; Components: WndTabs
;Root: HKU; Subkey: .DEFAULT\Software\{#VISUAL_FIRM}\DevStudio\{#VISUAL_VER}.{#VISUAL_REV}\Build System\Components\Tools\OLE Type Library Maker; ValueType: dword; ValueName: Deferred; ValueData: $00000000; Components: WndTabs

;Root: HKU; Subkey: .DEFAULT\Software\{#VISUAL_FIRM}\DevStudio\{#VISUAL_VER}.{#VISUAL_REV}\Build System\Components\Tools\Win32 Resource Compiler; ValueType: string; ValueName: Executable Path; ValueData: rc.exe; Components: WndTabs
;Root: HKU; Subkey: .DEFAULT\Software\{#VISUAL_FIRM}\DevStudio\{#VISUAL_VER}.{#VISUAL_REV}\Build System\Components\Tools\Win32 Resource Compiler; ValueType: string; ValueName: Macro_Prefix; ValueData: RSC; Components: WndTabs
;Root: HKU; Subkey: .DEFAULT\Software\{#VISUAL_FIRM}\DevStudio\{#VISUAL_VER}.{#VISUAL_REV}\Build System\Components\Tools\Win32 Resource Compiler; ValueType: string; ValueName: Input_Spec; ValueData: *.rc; Components: WndTabs
;Root: HKU; Subkey: .DEFAULT\Software\{#VISUAL_FIRM}\DevStudio\{#VISUAL_VER}.{#VISUAL_REV}\Build System\Components\Tools\Win32 Resource Compiler; ValueType: string; ValueName: Output_Spec; Components: WndTabs
;Root: HKU; Subkey: .DEFAULT\Software\{#VISUAL_FIRM}\DevStudio\{#VISUAL_VER}.{#VISUAL_REV}\Build System\Components\Tools\Win32 Resource Compiler; ValueType: string; ValueName: Menu Text; Components: WndTabs
;Root: HKU; Subkey: .DEFAULT\Software\{#VISUAL_FIRM}\DevStudio\{#VISUAL_VER}.{#VISUAL_REV}\Build System\Components\Tools\Win32 Resource Compiler; ValueType: dword; ValueName: Internal; ValueData: $00000001; Components: WndTabs
;Root: HKU; Subkey: .DEFAULT\Software\{#VISUAL_FIRM}\DevStudio\{#VISUAL_VER}.{#VISUAL_REV}\Build System\Components\Tools\Win32 Resource Compiler; ValueType: dword; ValueName: Perform_If_Able; ValueData: $00000000; Components: WndTabs
;Root: HKU; Subkey: .DEFAULT\Software\{#VISUAL_FIRM}\DevStudio\{#VISUAL_VER}.{#VISUAL_REV}\Build System\Components\Tools\Win32 Resource Compiler; ValueType: dword; ValueName: Deferred; ValueData: $00000000; Components: WndTabs

;Root: HKU; Subkey: .DEFAULT\Software\{#VISUAL_FIRM}\DevStudio\{#VISUAL_VER}.{#VISUAL_REV}\DataView; ValueType: dword; ValueName: EnableDebug; ValueData: $00000001; Components: WndTabs
;Root: HKU; Subkey: .DEFAULT\Software\{#VISUAL_FIRM}\DevStudio\{#VISUAL_VER}.{#VISUAL_REV}\DataView; ValueType: dword; ValueName: Verbose; ValueData: $00000001; Components: WndTabs
;Root: HKU; Subkey: .DEFAULT\Software\{#VISUAL_FIRM}\DevStudio\{#VISUAL_VER}.{#VISUAL_REV}\DataView; ValueType: dword; ValueName: LimitSQL; ValueData: $00000001; Components: WndTabs
;Root: HKU; Subkey: .DEFAULT\Software\{#VISUAL_FIRM}\DevStudio\{#VISUAL_VER}.{#VISUAL_REV}\DataView; ValueType: dword; ValueName: LineDumpMax; ValueData: $000001f4; Components: WndTabs
;Root: HKU; Subkey: .DEFAULT\Software\{#VISUAL_FIRM}\DevStudio\{#VISUAL_VER}.{#VISUAL_REV}\DataView; ValueType: dword; ValueName: SQLLoginTimeout; ValueData: $0000000f; Components: WndTabs
;Root: HKU; Subkey: .DEFAULT\Software\{#VISUAL_FIRM}\DevStudio\{#VISUAL_VER}.{#VISUAL_REV}\DataView; ValueType: dword; ValueName: SQLQueryTimeout; ValueData: $0000001e; Components: WndTabs
;Root: HKU; Subkey: .DEFAULT\Software\{#VISUAL_FIRM}\DevStudio\{#VISUAL_VER}.{#VISUAL_REV}\DataView; ValueType: dword; ValueName: ViewSysObjs; ValueData: $00000000; Components: WndTabs

;Root: HKU; Subkey: .DEFAULT\Software\{#VISUAL_FIRM}\DevStudio\{#VISUAL_VER}.{#VISUAL_REV}\Debug; ValueType: dword; ValueName: Version; ValueData: $00000001; Components: WndTabs
;Root: HKU; Subkey: .DEFAULT\Software\{#VISUAL_FIRM}\DevStudio\{#VISUAL_VER}.{#VISUAL_REV}\Debug; ValueType: dword; ValueName: DebugMode; ValueData: $00000000; Components: WndTabs
;Root: HKU; Subkey: .DEFAULT\Software\{#VISUAL_FIRM}\DevStudio\{#VISUAL_VER}.{#VISUAL_REV}\Debug; ValueType: dword; ValueName: ExtendedRegisters; ValueData: $00000000; Components: WndTabs
;Root: HKU; Subkey: .DEFAULT\Software\{#VISUAL_FIRM}\DevStudio\{#VISUAL_VER}.{#VISUAL_REV}\Debug; ValueType: dword; ValueName: OleRpcDebugging; ValueData: $00000001; Components: WndTabs
;Root: HKU; Subkey: .DEFAULT\Software\{#VISUAL_FIRM}\DevStudio\{#VISUAL_VER}.{#VISUAL_REV}\Debug; ValueType: dword; ValueName: ShowReturnValues; ValueData: $00000001; Components: WndTabs
;Root: HKU; Subkey: .DEFAULT\Software\{#VISUAL_FIRM}\DevStudio\{#VISUAL_VER}.{#VISUAL_REV}\Debug; ValueType: dword; ValueName: ShowDataTips; ValueData: $00000001; Components: WndTabs
;Root: HKU; Subkey: .DEFAULT\Software\{#VISUAL_FIRM}\DevStudio\{#VISUAL_VER}.{#VISUAL_REV}\Debug; ValueType: dword; ValueName: AutoWindow; ValueData: $00000001; Components: WndTabs
;Root: HKU; Subkey: .DEFAULT\Software\{#VISUAL_FIRM}\DevStudio\{#VISUAL_VER}.{#VISUAL_REV}\Debug; ValueType: dword; ValueName: Radix; ValueData: $00000001; Components: WndTabs
;Root: HKU; Subkey: .DEFAULT\Software\{#VISUAL_FIRM}\DevStudio\{#VISUAL_VER}.{#VISUAL_REV}\Debug; ValueType: dword; ValueName: CallParameters; ValueData: $00000001; Components: WndTabs
;Root: HKU; Subkey: .DEFAULT\Software\{#VISUAL_FIRM}\DevStudio\{#VISUAL_VER}.{#VISUAL_REV}\Debug; ValueType: dword; ValueName: CallTypes; ValueData: $00000001; Components: WndTabs
;Root: HKU; Subkey: .DEFAULT\Software\{#VISUAL_FIRM}\DevStudio\{#VISUAL_VER}.{#VISUAL_REV}\Debug; ValueType: dword; ValueName: DisassemblyAnnotations; ValueData: $00000001; Components: WndTabs
;Root: HKU; Subkey: .DEFAULT\Software\{#VISUAL_FIRM}\DevStudio\{#VISUAL_VER}.{#VISUAL_REV}\Debug; ValueType: dword; ValueName: DisassemblyCodeBytes; ValueData: $00000000; Components: WndTabs
;Root: HKU; Subkey: .DEFAULT\Software\{#VISUAL_FIRM}\DevStudio\{#VISUAL_VER}.{#VISUAL_REV}\Debug; ValueType: dword; ValueName: DisassemblyLowerCase; ValueData: $00000001; Components: WndTabs
;Root: HKU; Subkey: .DEFAULT\Software\{#VISUAL_FIRM}\DevStudio\{#VISUAL_VER}.{#VISUAL_REV}\Debug; ValueType: dword; ValueName: DisassemblySymbols; ValueData: $00000001; Components: WndTabs
;Root: HKU; Subkey: .DEFAULT\Software\{#VISUAL_FIRM}\DevStudio\{#VISUAL_VER}.{#VISUAL_REV}\Debug; ValueType: dword; ValueName: CPURegisters; ValueData: $00000001; Components: WndTabs
;Root: HKU; Subkey: .DEFAULT\Software\{#VISUAL_FIRM}\DevStudio\{#VISUAL_VER}.{#VISUAL_REV}\Debug; ValueType: dword; ValueName: CPUFlags; ValueData: $00000001; Components: WndTabs
;Root: HKU; Subkey: .DEFAULT\Software\{#VISUAL_FIRM}\DevStudio\{#VISUAL_VER}.{#VISUAL_REV}\Debug; ValueType: dword; ValueName: CPUEffectiveAddress; ValueData: $00000001; Components: WndTabs
;Root: HKU; Subkey: .DEFAULT\Software\{#VISUAL_FIRM}\DevStudio\{#VISUAL_VER}.{#VISUAL_REV}\Debug; ValueType: dword; ValueName: CPUFloatingPoint; ValueData: $00000001; Components: WndTabs
;Root: HKU; Subkey: .DEFAULT\Software\{#VISUAL_FIRM}\DevStudio\{#VISUAL_VER}.{#VISUAL_REV}\Debug; ValueType: dword; ValueName: LocalsToolbar; ValueData: $00000001; Components: WndTabs
;Root: HKU; Subkey: .DEFAULT\Software\{#VISUAL_FIRM}\DevStudio\{#VISUAL_VER}.{#VISUAL_REV}\Debug; ValueType: dword; ValueName: WatchToolbar; ValueData: $00000001; Components: WndTabs
;Root: HKU; Subkey: .DEFAULT\Software\{#VISUAL_FIRM}\DevStudio\{#VISUAL_VER}.{#VISUAL_REV}\Debug; ValueType: dword; ValueName: MemoryToolbar; ValueData: $00000001; Components: WndTabs
;Root: HKU; Subkey: .DEFAULT\Software\{#VISUAL_FIRM}\DevStudio\{#VISUAL_VER}.{#VISUAL_REV}\Debug; ValueType: dword; ValueName: WatchColWidth; ValueData: $00000000; Components: WndTabs
;Root: HKU; Subkey: .DEFAULT\Software\{#VISUAL_FIRM}\DevStudio\{#VISUAL_VER}.{#VISUAL_REV}\Debug; ValueType: dword; ValueName: VariablesColWidth; ValueData: $00000000; Components: WndTabs
;Root: HKU; Subkey: .DEFAULT\Software\{#VISUAL_FIRM}\DevStudio\{#VISUAL_VER}.{#VISUAL_REV}\Debug; ValueType: dword; ValueName: QuickWatchColWidth; ValueData: $00000000; Components: WndTabs
;Root: HKU; Subkey: .DEFAULT\Software\{#VISUAL_FIRM}\DevStudio\{#VISUAL_VER}.{#VISUAL_REV}\Debug; ValueType: dword; ValueName: VariablesToolbar; ValueData: $00000001; Components: WndTabs
;Root: HKU; Subkey: .DEFAULT\Software\{#VISUAL_FIRM}\DevStudio\{#VISUAL_VER}.{#VISUAL_REV}\Debug; ValueType: dword; ValueName: UnicodeStrings; ValueData: $00000000; Components: WndTabs
;Root: HKU; Subkey: .DEFAULT\Software\{#VISUAL_FIRM}\DevStudio\{#VISUAL_VER}.{#VISUAL_REV}\Debug; ValueType: dword; ValueName: EditAndContinueDebugging; ValueData: $00000001; Components: WndTabs
;Root: HKU; Subkey: .DEFAULT\Software\{#VISUAL_FIRM}\DevStudio\{#VISUAL_VER}.{#VISUAL_REV}\Debug; ValueType: dword; ValueName: LoadExports; ValueData: $00000000; Components: WndTabs
;Root: HKU; Subkey: .DEFAULT\Software\{#VISUAL_FIRM}\DevStudio\{#VISUAL_VER}.{#VISUAL_REV}\Debug; ValueType: dword; ValueName: ENCRelink; ValueData: $00000001; Components: WndTabs
;Root: HKU; Subkey: .DEFAULT\Software\{#VISUAL_FIRM}\DevStudio\{#VISUAL_VER}.{#VISUAL_REV}\Debug; ValueType: dword; ValueName: ENCTraceLevel; ValueData: $00000002; Components: WndTabs
;Root: HKU; Subkey: .DEFAULT\Software\{#VISUAL_FIRM}\DevStudio\{#VISUAL_VER}.{#VISUAL_REV}\Debug; ValueType: dword; ValueName: ENCRepro; ValueData: $00000000; Components: WndTabs
;Root: HKU; Subkey: .DEFAULT\Software\{#VISUAL_FIRM}\DevStudio\{#VISUAL_VER}.{#VISUAL_REV}\Debug; ValueType: dword; ValueName: ENCLoadIdbFiles; ValueData: $00000001; Components: WndTabs
;Root: HKU; Subkey: .DEFAULT\Software\{#VISUAL_FIRM}\DevStudio\{#VISUAL_VER}.{#VISUAL_REV}\Debug; ValueType: string; ValueName: DebugCommandLine; Components: WndTabs

;Root: HKU; Subkey: .DEFAULT\Software\{#VISUAL_FIRM}\DevStudio\{#VISUAL_VER}.{#VISUAL_REV}\Dialog Editor; ValueType: dword; ValueName: Grid; ValueData: $00000002; Components: WndTabs
;Root: HKU; Subkey: .DEFAULT\Software\{#VISUAL_FIRM}\DevStudio\{#VISUAL_VER}.{#VISUAL_REV}\Dialog Editor; ValueType: string; ValueName: GridSize; ValueData: 5,5; Components: WndTabs
;Root: HKU; Subkey: .DEFAULT\Software\{#VISUAL_FIRM}\DevStudio\{#VISUAL_VER}.{#VISUAL_REV}\Dialog Editor; ValueType: dword; ValueName: InitialButtons; ValueData: $00000001; Components: WndTabs
;Root: HKU; Subkey: .DEFAULT\Software\{#VISUAL_FIRM}\DevStudio\{#VISUAL_VER}.{#VISUAL_REV}\Dialog Editor; ValueType: dword; ValueName: NetSelectAll; ValueData: $00000000; Components: WndTabs

;Root: HKU; Subkey: .DEFAULT\Software\{#VISUAL_FIRM}\DevStudio\{#VISUAL_VER}.{#VISUAL_REV}\Directories; ValueType: string; ValueName: Install Dirs; ValueData: {app}\Common\MSDev98\Bin; Components: WndTabs

Root: HKU; Subkey: .DEFAULT\Software\{#VISUAL_FIRM}\DevStudio\{#VISUAL_VER}.{#VISUAL_REV}\General; ValueType: dword; ValueName: Tip of the Day; ValueData: $00000000; Components: Preconfig
Root: HKU; Subkey: .DEFAULT\Software\{#VISUAL_FIRM}\DevStudio\{#VISUAL_VER}.{#VISUAL_REV}\General; ValueType: dword; ValueName: PackageCount; ValueData: $00000011; Components: Preconfig

;Root: HKU; Subkey: .DEFAULT\Software\{#VISUAL_FIRM}\DevStudio\{#VISUAL_VER}.{#VISUAL_REV}\General; ValueType: string; ValueName: MFCPath32Bit; ValueData: {app}\VC98\MFC; Components: WndTabs
;Root: HKU; Subkey: .DEFAULT\Software\{#VISUAL_FIRM}\DevStudio\{#VISUAL_VER}.{#VISUAL_REV}\General; ValueType: dword; ValueName: Tip of the Day; ValueData: $00000000; Components: WndTabs
;Root: HKU; Subkey: .DEFAULT\Software\{#VISUAL_FIRM}\DevStudio\{#VISUAL_VER}.{#VISUAL_REV}\General; ValueType: string; ValueName: PropertiesWindow; ValueData: 60,634; Components: WndTabs
;Root: HKU; Subkey: .DEFAULT\Software\{#VISUAL_FIRM}\DevStudio\{#VISUAL_VER}.{#VISUAL_REV}\General; ValueType: dword; ValueName: MaximizeApp; ValueData: $00000001; Components: WndTabs
;Root: HKU; Subkey: .DEFAULT\Software\{#VISUAL_FIRM}\DevStudio\{#VISUAL_VER}.{#VISUAL_REV}\General; ValueType: dword; ValueName: MaximizeDoc; ValueData: $00000000; Components: WndTabs
;Root: HKU; Subkey: .DEFAULT\Software\{#VISUAL_FIRM}\DevStudio\{#VISUAL_VER}.{#VISUAL_REV}\General; ValueType: dword; ValueName: ToolTips; ValueData: $00000001; Components: WndTabs
;Root: HKU; Subkey: .DEFAULT\Software\{#VISUAL_FIRM}\DevStudio\{#VISUAL_VER}.{#VISUAL_REV}\General; ValueType: dword; ValueName: ToolTipKeys; ValueData: $00000001; Components: WndTabs
;Root: HKU; Subkey: .DEFAULT\Software\{#VISUAL_FIRM}\DevStudio\{#VISUAL_VER}.{#VISUAL_REV}\General; ValueType: dword; ValueName: LargeToolBars; ValueData: $00000000; Components: WndTabs
;Root: HKU; Subkey: .DEFAULT\Software\{#VISUAL_FIRM}\DevStudio\{#VISUAL_VER}.{#VISUAL_REV}\General; ValueType: dword; ValueName: WorkspaceAuto; ValueData: $00000001; Components: WndTabs
;Root: HKU; Subkey: .DEFAULT\Software\{#VISUAL_FIRM}\DevStudio\{#VISUAL_VER}.{#VISUAL_REV}\General; ValueType: dword; ValueName: WindowMenuItems; ValueData: $0000000a; Components: WndTabs
;Root: HKU; Subkey: .DEFAULT\Software\{#VISUAL_FIRM}\DevStudio\{#VISUAL_VER}.{#VISUAL_REV}\General; ValueType: dword; ValueName: WindowMenuSorted; ValueData: $00000001; Components: WndTabs
;Root: HKU; Subkey: .DEFAULT\Software\{#VISUAL_FIRM}\DevStudio\{#VISUAL_VER}.{#VISUAL_REV}\General; ValueType: dword; ValueName: MRUListsOnFileMenu; ValueData: $00000000; Components: WndTabs
;Root: HKU; Subkey: .DEFAULT\Software\{#VISUAL_FIRM}\DevStudio\{#VISUAL_VER}.{#VISUAL_REV}\General; ValueType: dword; ValueName: TraditionalMenu; ValueData: $00000000; Components: WndTabs
;Root: HKU; Subkey: .DEFAULT\Software\{#VISUAL_FIRM}\DevStudio\{#VISUAL_VER}.{#VISUAL_REV}\General; ValueType: dword; ValueName: PropertiesPushPin; ValueData: $00000000; Components: WndTabs
;Root: HKU; Subkey: .DEFAULT\Software\{#VISUAL_FIRM}\DevStudio\{#VISUAL_VER}.{#VISUAL_REV}\General; ValueType: dword; ValueName: PinGoToDlg; ValueData: $00000001; Components: WndTabs
;Root: HKU; Subkey: .DEFAULT\Software\{#VISUAL_FIRM}\DevStudio\{#VISUAL_VER}.{#VISUAL_REV}\General; ValueType: dword; ValueName: DlgEdDblClickEditCode; ValueData: $00000001; Components: WndTabs

;Root: HKU; Subkey: .DEFAULT\Software\{#VISUAL_FIRM}\DevStudio\{#VISUAL_VER}.{#VISUAL_REV}\Graphics Editor; ValueType: string; ValueName: DefaultScreenColor; ValueData: 0,128,128; Components: WndTabs
;Root: HKU; Subkey: .DEFAULT\Software\{#VISUAL_FIRM}\DevStudio\{#VISUAL_VER}.{#VISUAL_REV}\Graphics Editor; ValueType: dword; ValueName: PixelGrid; ValueData: $00000001; Components: WndTabs
;Root: HKU; Subkey: .DEFAULT\Software\{#VISUAL_FIRM}\DevStudio\{#VISUAL_VER}.{#VISUAL_REV}\Graphics Editor; ValueType: dword; ValueName: TileGrid; ValueData: $00000000; Components: WndTabs
;Root: HKU; Subkey: .DEFAULT\Software\{#VISUAL_FIRM}\DevStudio\{#VISUAL_VER}.{#VISUAL_REV}\Graphics Editor; ValueType: string; ValueName: TileGridSize; ValueData: 16,15; Components: WndTabs

;Root: HKU; Subkey: .DEFAULT\Software\{#VISUAL_FIRM}\DevStudio\{#VISUAL_VER}.{#VISUAL_REV}\Help\Extension; ValueType: string; ValueName: Filename; ValueData: {app}\Common\MSDev98\Help\exthelp.hlp; Components: WndTabs
;Root: HKU; Subkey: .DEFAULT\Software\{#VISUAL_FIRM}\DevStudio\{#VISUAL_VER}.{#VISUAL_REV}\Help\Extension; ValueType: dword; ValueName: Enable; ValueData: $00000001; Components: WndTabs
;Root: HKU; Subkey: .DEFAULT\Software\{#VISUAL_FIRM}\DevStudio\{#VISUAL_VER}.{#VISUAL_REV}\Help\Extension; ValueType: dword; ValueName: State; ValueData: $00000000; Components: WndTabs

;Root: HKU; Subkey: .DEFAULT\Software\{#VISUAL_FIRM}\DevStudio\{#VISUAL_VER}.{#VISUAL_REV}\Help\Tips; ValueType: binary; ValueName: MSDEV; ValueData: 10 00 00 32 00 50 b9 38 00 00 18 01 00 00 01 00 00 00; Components: WndTabs
;Root: HKU; Subkey: .DEFAULT\Software\{#VISUAL_FIRM}\DevStudio\{#VISUAL_VER}.{#VISUAL_REV}\Help\Tips; ValueType: binary; ValueName: TOOLS; ValueData: 10 00 00 32 2c 01 41 2e 00 00 65 01 00 00 02 00 08 20; Components: WndTabs
Root: HKU; Subkey: .DEFAULT\Software\{#VISUAL_FIRM}\DevStudio\{#VISUAL_VER}.{#VISUAL_REV}\Help\Tips; ValueType: binary; ValueName: VCXX; ValueData: 10 00 00 32 00 00 5a 14 00 00 64 02 00 00 00 00 00 00; Components: WndTabs

Root: HKU; Subkey: .DEFAULT\Software\{#VISUAL_FIRM}\DevStudio\{#VISUAL_VER}.{#VISUAL_REV}\Help\Tips; ValueType: binary; ValueName: MSDEV; ValueData: 10 00 00 32 00 00 b9 38 00 00 18 01 00 00 00 00 80 00; Components: Preconfig
Root: HKU; Subkey: .DEFAULT\Software\{#VISUAL_FIRM}\DevStudio\{#VISUAL_VER}.{#VISUAL_REV}\Help\Tips; ValueType: binary; ValueName: TOOLS; ValueData: 10 00 00 32 00 00 41 2e 00 00 65 01 00 00 01 00 00 00; Components: Preconfig
Root: HKU; Subkey: .DEFAULT\Software\{#VISUAL_FIRM}\DevStudio\{#VISUAL_VER}.{#VISUAL_REV}\Help\Tips; ValueType: binary; ValueName: VCXX; ValueData: 10 00 00 32 00 00 5a 14 00 00 d0 02 00 00 02 00 00 00; Components: Preconfig

;Root: HKU; Subkey: .DEFAULT\Software\{#VISUAL_FIRM}\DevStudio\{#VISUAL_VER}.{#VISUAL_REV}\HTML; ValueType: string; ValueName: Variant; ValueData: HTML - IE 3.0; Components: WndTabs

;Root: HKU; Subkey: .DEFAULT\Software\{#VISUAL_FIRM}\DevStudio\{#VISUAL_VER}.{#VISUAL_REV}\Layout; ValueType: dword; ValueName: Version; ValueData: $00000010; Components: WndTabs
Root: HKU; Subkey: .DEFAULT\Software\{#VISUAL_FIRM}\DevStudio\{#VISUAL_VER}.{#VISUAL_REV}\Layout; ValueType: binary; ValueName: Layout0; ValueData: 

;Root: HKU; Subkey: .DEFAULT\Software\{#VISUAL_FIRM}\DevStudio\{#VISUAL_VER}.{#VISUAL_REV}\Layout; ValueType: binary; ValueName: Window17801; ValueData: 3e 00 05 00 01 00 08 00 08 00 08 00 00 00 00 02 00 00 18 00 2a 00 01 00 65 d6 32 14 b1 1a 75 41 99 91 8c ca 5f c5 25 78 57 54 53 44 4b 5f 53 61 6d 70 43 6f 6d 6d 61 6e 64 4d 65 74 68 6f 64 00; Components: WndTabs
Root: HKU; Subkey: .DEFAULT\Software\{#VISUAL_FIRM}\DevStudio\{#VISUAL_VER}.{#VISUAL_REV}\Layout; ValueType: binary; ValueName: Window17801; ValueData: 60 05 05 00 04 00 11 00 11 00 e5 01 00 00 40 02 00 00 00 00 40 02 00 00 00 00 40 02 00 00 00 00 40 02 00 00 e8 00 28 00 00 00 10 00 00 00 10 00 00 00 01 00 04 00 00 00 00 00 80 00 00 00 00 00 00 00 00 00 00 00 10 00 00 00 00 00 00 00 00 00 00 00 80 00 00 00 00 80 00 00 80 80 00 00 00 00 80 00 80 00 80 00 00 80 80 00 80 80 80 00 c0 c0 c0 00 f0 00 00 00 00 f0 00 00 f0 f0 00 00 00 00 f0 00 f0 00 f0 00 00 f0 f0 00 f0 f0 f0 00 88 88 88 88 88 88 88 88 88 88 88 88 88 88 88 88 88 88 88 88 88 88 88 88 88 88 88 88 18 88 88 88 88 88 88 81 11 88 88 88 88 88 88 11 11 18 88 88 88 88 81 11 11 11 88 88 88 88 11 11 11 11 18 88 88 81 11 11 11 11 11 88 88 88 88 81 11 88 88 88 88 88 88 81 11 88 88 88 88 88 88 81 11 88 88 88 88 88 88 81 11 88 88 88 88 88 88 81 11 88 88 88 88 88 88 81 11 88 88 88 88 88 88 88 88 88 88 88 e8 00 28 00 00 00 10 00 00 00 10 00 00 00 01 00 04 00 00 00 00 00 80 00 00 00 00 00 00 00 00 00 00 00 10 00 00 00 00 00 00 00 00 00 00 00 80 00 00 00 00 80 00 00 80 80 00 00 00 00 80 00 80 00 80 00 00 80 80 00 80 80 80 00 c0 c0 c0 00 f0 00 00 00 00 f0 00 00 f0 f0 00 00 00 00 f0 00 f0 00 f0 00 00 f0 f0 00 f0 f0 f0 00 88 88 88 88 88 88 88 88 88 88 88 88 88 88 88 88 88 88 88 88 88 88 88 88 88 88 88 81 11 88 88 88 88 88 88 81 11 88 88 88 88 88 88 81 11 88 88 88 88 88 88 81 11 88 88 88 88 88 88 81 11 88 88 88 88 88 88 81 11 88 88 88 88 81 11 11 11 11 11 88 88 88 11 11 11 11 18 88 88 88 81 11 11 11 88 88 88 88 88 11 11 18 88 88 88 88 88 81 11 88 88 88 88 88 88 88 18 88 88 88 88 88 88 88 88 88 88 88 e8 00 28 00 00 00 10 00 00 00 10 00 00 00 01 00 04 00 00 00 00 00 80 00 00 00 00 00 00 00 00 00 00 00 10 00 00 00 00 00 00 00 00 00 00 00 80 00 00 00 00 80 00 00 80 80 00 00 00 00 80 00 80 00 80 00 00 80 80 00 80 80 80 00 c0 c0 c0 00 f0 00 00 00 00 f0 00 00 f0 f0 00 00 00 00 f0 00 f0 00 f0 00 00 f0 f0 00 f0 f0 f0 00 88 88 88 88 88 88 88 88 88 88 80 00 00 88 88 88 88 80 0e ee ee 00 88 88 88 0e ee ee ee ee 08 88 80 ee ee ee ee ee e0 88 80 ee e0 00 00 ee e0 88 0e ee 0e ee ee 0e ee 08 0e e0 ee ee ee e0 ee 08 0e ee ee ee ee ee ee 08 0e ee ee ee ee ee ee 08 0e ee 00 ee e0 0e ee 08 80 ee 00 ee e0 0e e0 88 80 ee ee ee ee ee e0 88 88 0e ee ee ee ee 08 88 88 80 0e ee ee 00 88 88 88 88 80 00 00 88 88 88 e8 00 28 00 00 00 10 00 00 00 10 00 00 00 01 00 04 00 00 00 00 00 80 00 00 00 00 00 00 00 00 00 00 00 10 00 00 00 00 00 00 00 00 00 00 00 80 00 00 00 00 80 00 00 80 80 00 00 00 00 80 00 80 00 80 00 00 80 80 00 80 80 80 00 c0 c0 c0 00 f0 00 00 00 00 f0 00 00 f0 f0 00 00 00 00 f0 00 f0 00 f0 00 00 f0 f0 00 f0 f0 f0 00 88 88 88 88 88 88 88 88 88 88 80 00 00 88 88 88 88 80 0a aa aa 00 88 88 88 0a aa aa aa aa 08 88 80 aa aa aa aa aa a0 88 80 aa 0a aa aa 0a a0 88 0a aa 00 aa a0 0a aa 08 0a aa a0 00 00 aa aa 08 0a aa aa aa aa aa aa 08 0a aa aa aa aa aa aa 08 0a aa 00 aa a0 0a aa 08 80 aa 00 aa a0 0a a0 88 80 aa aa aa aa aa a0 88 88 0a aa aa aa aa 08 88 88 80 0a aa aa 00 88 88 88 88 80 00 00 88 88 88 18 00 5e 00 01 01 44 3a 5c 50 52 4f 47 52 41 4d 20 46 49 4c 45 53 5c 4d 49 43 52 4f 53 4f 46 54 20 56 49 53 55 41 4c 20 53 54 55 44 49 4f 5c 43 4f 4d 4d 4f 4e 5c 4d 53 44 45 56 39 38 5c 4d 41 43 52 4f 53 5c 41 4c 49 47 4e 4e 45 58 54 2e 44 53 4d 00 41 6c 69 67 6e 4e 65 78 74 4c 69 6e 65 00 00 18 00 5e 00 01 01 44 3a 5c 50 52 4f 47 52 41 4d 20 46 49 4c 45 53 5c 4d 49 43 52 4f 53 4f 46 54 20 56 49 53 55 41 4c 20 53 54 55 44 49 4f 5c 43 4f 4d 4d 4f 4e 5c 4d 53 44 45 56 39 38 5c 4d 41 43 52 4f 53 5c 41 4c 49 47 4e 4e 45 58 54 2e 44 53 4d 00 41 6c 69 67 6e 50 72 65 76 4c 69 6e 65 00 00 18 00 68 00 01 01 44 3a 5c 50 52 4f 47 52 41 4d 20 46 49 4c 45 53 5c 4d 49 43 52 4f 53 4f 46 54 20 56 49 53 55 41 4c 20 53 54 55 44 49 4f 5c 43 4f 4d 4d 4f 4e 5c 4d 53 44 45 56 39 38 5c 4d 41 43 52 4f 53 5c 52 45 46 4f 52 4d 41 54 43 4f 44 45 2e 44 53 4d 00 4d 61 6b 65 53 65 6c 65 63 74 65 64 43 6f 64 65 4e 69 63 65 72 00 18 00 60 00 01 01 44 3a 5c 50 52 4f 47 52 41 4d 20 46 49 4c 45 53 5c 4d 49 43 52 4f 53 4f 46 54 20 56 49 53 55 41 4c 20 53 54 55 44 49 4f 5c 43 4f 4d 4d 4f 4e 5c 4d 53 44 45 56 39 38 5c 4d 41 43 52 4f 53 5c 52 45 46 4f 52 4d 41 54 43 4f 44 45 2e 44 53 4d 00 4d 61 6b 65 43 6f 64 65 4e 69 63 65 72 00 00 00; Components: Preconfig

;Root: HKU; Subkey: .DEFAULT\Software\{#VISUAL_FIRM}\DevStudio\{#VISUAL_VER}.{#VISUAL_REV}\Layout; ValueType: dword; ValueName: Statusbar; ValueData: $00000001; Components: WndTabs
;Root: HKU; Subkey: .DEFAULT\Software\{#VISUAL_FIRM}\DevStudio\{#VISUAL_VER}.{#VISUAL_REV}\Layout; ValueType: dword; ValueName: Clock; ValueData: $00000000; Components: WndTabs
;Root: HKU; Subkey: .DEFAULT\Software\{#VISUAL_FIRM}\DevStudio\{#VISUAL_VER}.{#VISUAL_REV}\Layout; ValueType: dword; ValueName: ReloadProject; ValueData: $00000000; Components: WndTabs
;Root: HKU; Subkey: .DEFAULT\Software\{#VISUAL_FIRM}\DevStudio\{#VISUAL_VER}.{#VISUAL_REV}\Layout; ValueType: dword; ValueName: DisableFileDep; ValueData: $00000003; Components: WndTabs
Root: HKU; Subkey: .DEFAULT\Software\{#VISUAL_FIRM}\DevStudio\{#VISUAL_VER}.{#VISUAL_REV}\Layout; ValueType: binary; ValueName: FullScreen; ValueData: 44 00 88 00 00 00 00 00 00 00 00 00 05 00 00 00 04 00 00 2c 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 4e 06; Components: WndTabs
;Root: HKU; Subkey: .DEFAULT\Software\{#VISUAL_FIRM}\DevStudio\{#VISUAL_VER}.{#VISUAL_REV}\Layout; ValueType: dword; ValueName: OutputWindowSplitterPos; ValueData: $00000000; Components: WndTabs

;Root: HKU; Subkey: .DEFAULT\Software\{#VISUAL_FIRM}\DevStudio\{#VISUAL_VER}.{#VISUAL_REV}\Macros; ValueType: string; ValueName: {app}\COMMON\MSDEV98\MACROS\SAMPLE.DSM; ValueData: 0; Components: WndTabs
Root: HKU; Subkey: .DEFAULT\Software\{#VISUAL_FIRM}\DevStudio\{#VISUAL_VER}.{#VISUAL_REV}\Macros; ValueType: string; ValueName: {app}\COMMON\MSDEV98\MACROS\ALIGNNEXT.DSM; ValueData: 1; Components: Preconfig
Root: HKU; Subkey: .DEFAULT\Software\{#VISUAL_FIRM}\DevStudio\{#VISUAL_VER}.{#VISUAL_REV}\Macros; ValueType: string; ValueName: {app}\COMMON\MSDEV98\MACROS\REFORMATCODE.DSM; ValueData: 1; Components: Preconfig
Root: HKU; Subkey: .DEFAULT\Software\{#VISUAL_FIRM}\DevStudio\{#VISUAL_VER}.{#VISUAL_REV}\Macros; ValueType: dword; ValueName: Reload; ValueData: $00000002; Components: Preconfig

;Root: HKU; Subkey: .DEFAULT\Software\{#VISUAL_FIRM}\DevStudio\{#VISUAL_VER}.{#VISUAL_REV}\Recent File List; ValueType: dword; ValueName: ProjectCount; ValueData: $00000004; Components: WndTabs
;Root: HKU; Subkey: .DEFAULT\Software\{#VISUAL_FIRM}\DevStudio\{#VISUAL_VER}.{#VISUAL_REV}\Recent File List; ValueType: dword; ValueName: FileCount; ValueData: $00000004; Components: WndTabs

;Root: HKU; Subkey: .DEFAULT\Software\{#VISUAL_FIRM}\DevStudio\{#VISUAL_VER}.{#VISUAL_REV}\Search; ValueType: string; ValueName: FIF_ExtraDirs; Components: WndTabs
;Root: HKU; Subkey: .DEFAULT\Software\{#VISUAL_FIRM}\DevStudio\{#VISUAL_VER}.{#VISUAL_REV}\Search; ValueType: dword; ValueName: FIF_SearchSubfolders; ValueData: $00000001; Components: WndTabs
;Root: HKU; Subkey: .DEFAULT\Software\{#VISUAL_FIRM}\DevStudio\{#VISUAL_VER}.{#VISUAL_REV}\Search; ValueType: dword; ValueName: FIF_Advanced; ValueData: $00000000; Components: WndTabs
;Root: HKU; Subkey: .DEFAULT\Software\{#VISUAL_FIRM}\DevStudio\{#VISUAL_VER}.{#VISUAL_REV}\Search; ValueType: dword; ValueName: FIF_SourcePath; ValueData: $00000000; Components: WndTabs
;Root: HKU; Subkey: .DEFAULT\Software\{#VISUAL_FIRM}\DevStudio\{#VISUAL_VER}.{#VISUAL_REV}\Search; ValueType: dword; ValueName: FIF_IncludePath; ValueData: $00000000; Components: WndTabs
;Root: HKU; Subkey: .DEFAULT\Software\{#VISUAL_FIRM}\DevStudio\{#VISUAL_VER}.{#VISUAL_REV}\Search; ValueType: string; ValueName: Find1; Components: WndTabs
;Root: HKU; Subkey: .DEFAULT\Software\{#VISUAL_FIRM}\DevStudio\{#VISUAL_VER}.{#VISUAL_REV}\Search; ValueType: string; ValueName: Find2; Components: WndTabs
;Root: HKU; Subkey: .DEFAULT\Software\{#VISUAL_FIRM}\DevStudio\{#VISUAL_VER}.{#VISUAL_REV}\Search; ValueType: string; ValueName: Find3; Components: WndTabs
;Root: HKU; Subkey: .DEFAULT\Software\{#VISUAL_FIRM}\DevStudio\{#VISUAL_VER}.{#VISUAL_REV}\Search; ValueType: string; ValueName: Find4; Components: WndTabs
;Root: HKU; Subkey: .DEFAULT\Software\{#VISUAL_FIRM}\DevStudio\{#VISUAL_VER}.{#VISUAL_REV}\Search; ValueType: string; ValueName: Find5; Components: WndTabs
;Root: HKU; Subkey: .DEFAULT\Software\{#VISUAL_FIRM}\DevStudio\{#VISUAL_VER}.{#VISUAL_REV}\Search; ValueType: string; ValueName: Find6; Components: WndTabs
;Root: HKU; Subkey: .DEFAULT\Software\{#VISUAL_FIRM}\DevStudio\{#VISUAL_VER}.{#VISUAL_REV}\Search; ValueType: string; ValueName: Find7; Components: WndTabs
;Root: HKU; Subkey: .DEFAULT\Software\{#VISUAL_FIRM}\DevStudio\{#VISUAL_VER}.{#VISUAL_REV}\Search; ValueType: string; ValueName: Find8; Components: WndTabs
;Root: HKU; Subkey: .DEFAULT\Software\{#VISUAL_FIRM}\DevStudio\{#VISUAL_VER}.{#VISUAL_REV}\Search; ValueType: string; ValueName: Find9; Components: WndTabs
;Root: HKU; Subkey: .DEFAULT\Software\{#VISUAL_FIRM}\DevStudio\{#VISUAL_VER}.{#VISUAL_REV}\Search; ValueType: string; ValueName: Find10; Components: WndTabs
;Root: HKU; Subkey: .DEFAULT\Software\{#VISUAL_FIRM}\DevStudio\{#VISUAL_VER}.{#VISUAL_REV}\Search; ValueType: string; ValueName: Find11; Components: WndTabs
;Root: HKU; Subkey: .DEFAULT\Software\{#VISUAL_FIRM}\DevStudio\{#VISUAL_VER}.{#VISUAL_REV}\Search; ValueType: string; ValueName: Find12; Components: WndTabs
;Root: HKU; Subkey: .DEFAULT\Software\{#VISUAL_FIRM}\DevStudio\{#VISUAL_VER}.{#VISUAL_REV}\Search; ValueType: string; ValueName: Find13; Components: WndTabs
;Root: HKU; Subkey: .DEFAULT\Software\{#VISUAL_FIRM}\DevStudio\{#VISUAL_VER}.{#VISUAL_REV}\Search; ValueType: string; ValueName: Find14; Components: WndTabs
;Root: HKU; Subkey: .DEFAULT\Software\{#VISUAL_FIRM}\DevStudio\{#VISUAL_VER}.{#VISUAL_REV}\Search; ValueType: string; ValueName: Find15; Components: WndTabs
;Root: HKU; Subkey: .DEFAULT\Software\{#VISUAL_FIRM}\DevStudio\{#VISUAL_VER}.{#VISUAL_REV}\Search; ValueType: string; ValueName: Find16; Components: WndTabs
;Root: HKU; Subkey: .DEFAULT\Software\{#VISUAL_FIRM}\DevStudio\{#VISUAL_VER}.{#VISUAL_REV}\Search; ValueType: string; ValueName: Replace1; Components: WndTabs
;Root: HKU; Subkey: .DEFAULT\Software\{#VISUAL_FIRM}\DevStudio\{#VISUAL_VER}.{#VISUAL_REV}\Search; ValueType: string; ValueName: Replace2; Components: WndTabs
;Root: HKU; Subkey: .DEFAULT\Software\{#VISUAL_FIRM}\DevStudio\{#VISUAL_VER}.{#VISUAL_REV}\Search; ValueType: string; ValueName: Replace3; Components: WndTabs
;Root: HKU; Subkey: .DEFAULT\Software\{#VISUAL_FIRM}\DevStudio\{#VISUAL_VER}.{#VISUAL_REV}\Search; ValueType: string; ValueName: Replace4; Components: WndTabs
;Root: HKU; Subkey: .DEFAULT\Software\{#VISUAL_FIRM}\DevStudio\{#VISUAL_VER}.{#VISUAL_REV}\Search; ValueType: string; ValueName: Replace5; Components: WndTabs
;Root: HKU; Subkey: .DEFAULT\Software\{#VISUAL_FIRM}\DevStudio\{#VISUAL_VER}.{#VISUAL_REV}\Search; ValueType: string; ValueName: Replace6; Components: WndTabs
;Root: HKU; Subkey: .DEFAULT\Software\{#VISUAL_FIRM}\DevStudio\{#VISUAL_VER}.{#VISUAL_REV}\Search; ValueType: string; ValueName: Replace7; Components: WndTabs
;Root: HKU; Subkey: .DEFAULT\Software\{#VISUAL_FIRM}\DevStudio\{#VISUAL_VER}.{#VISUAL_REV}\Search; ValueType: string; ValueName: Replace8; Components: WndTabs
;Root: HKU; Subkey: .DEFAULT\Software\{#VISUAL_FIRM}\DevStudio\{#VISUAL_VER}.{#VISUAL_REV}\Search; ValueType: string; ValueName: Replace9; Components: WndTabs
;Root: HKU; Subkey: .DEFAULT\Software\{#VISUAL_FIRM}\DevStudio\{#VISUAL_VER}.{#VISUAL_REV}\Search; ValueType: string; ValueName: Replace10; Components: WndTabs
;Root: HKU; Subkey: .DEFAULT\Software\{#VISUAL_FIRM}\DevStudio\{#VISUAL_VER}.{#VISUAL_REV}\Search; ValueType: string; ValueName: Replace11; Components: WndTabs
;Root: HKU; Subkey: .DEFAULT\Software\{#VISUAL_FIRM}\DevStudio\{#VISUAL_VER}.{#VISUAL_REV}\Search; ValueType: string; ValueName: Replace12; Components: WndTabs
;Root: HKU; Subkey: .DEFAULT\Software\{#VISUAL_FIRM}\DevStudio\{#VISUAL_VER}.{#VISUAL_REV}\Search; ValueType: string; ValueName: Replace13; Components: WndTabs
;Root: HKU; Subkey: .DEFAULT\Software\{#VISUAL_FIRM}\DevStudio\{#VISUAL_VER}.{#VISUAL_REV}\Search; ValueType: string; ValueName: Replace14; Components: WndTabs
;Root: HKU; Subkey: .DEFAULT\Software\{#VISUAL_FIRM}\DevStudio\{#VISUAL_VER}.{#VISUAL_REV}\Search; ValueType: string; ValueName: Replace15; Components: WndTabs
;Root: HKU; Subkey: .DEFAULT\Software\{#VISUAL_FIRM}\DevStudio\{#VISUAL_VER}.{#VISUAL_REV}\Search; ValueType: string; ValueName: Replace16; Components: WndTabs

;Root: HKU; Subkey: .DEFAULT\Software\{#VISUAL_FIRM}\DevStudio\{#VISUAL_VER}.{#VISUAL_REV}\Source Control; ValueType: dword; ValueName: Disabled; ValueData: $00000000; Components: WndTabs

;Root: HKU; Subkey: .DEFAULT\Software\{#VISUAL_FIRM}\DevStudio\{#VISUAL_VER}.{#VISUAL_REV}\Text Editor; ValueType: dword; ValueName: Version; ValueData: $00000001; Components: WndTabs
;Root: HKU; Subkey: .DEFAULT\Software\{#VISUAL_FIRM}\DevStudio\{#VISUAL_VER}.{#VISUAL_REV}\Text Editor; ValueType: string; ValueName: PageSetupParm1; Components: WndTabs
;Root: HKU; Subkey: .DEFAULT\Software\{#VISUAL_FIRM}\DevStudio\{#VISUAL_VER}.{#VISUAL_REV}\Text Editor; ValueType: string; ValueName: PageSetupParm2; ValueData: &P; Components: WndTabs
;Root: HKU; Subkey: .DEFAULT\Software\{#VISUAL_FIRM}\DevStudio\{#VISUAL_VER}.{#VISUAL_REV}\Text Editor; ValueType: string; ValueName: PageSetupParm3; ValueData: 127; Components: WndTabs
;Root: HKU; Subkey: .DEFAULT\Software\{#VISUAL_FIRM}\DevStudio\{#VISUAL_VER}.{#VISUAL_REV}\Text Editor; ValueType: string; ValueName: PageSetupParm4; ValueData: 127; Components: WndTabs
;Root: HKU; Subkey: .DEFAULT\Software\{#VISUAL_FIRM}\DevStudio\{#VISUAL_VER}.{#VISUAL_REV}\Text Editor; ValueType: string; ValueName: PageSetupParm5; ValueData: 127; Components: WndTabs
;Root: HKU; Subkey: .DEFAULT\Software\{#VISUAL_FIRM}\DevStudio\{#VISUAL_VER}.{#VISUAL_REV}\Text Editor; ValueType: string; ValueName: PageSetupParm6; ValueData: 127; Components: WndTabs
;Root: HKU; Subkey: .DEFAULT\Software\{#VISUAL_FIRM}\DevStudio\{#VISUAL_VER}.{#VISUAL_REV}\Text Editor; ValueType: dword; ValueName: PreserveTabs; ValueData: $00000001; Components: WndTabs
;Root: HKU; Subkey: .DEFAULT\Software\{#VISUAL_FIRM}\DevStudio\{#VISUAL_VER}.{#VISUAL_REV}\Text Editor; ValueType: dword; ValueName: VerticalScrollBars; ValueData: $00000001; Components: WndTabs
;Root: HKU; Subkey: .DEFAULT\Software\{#VISUAL_FIRM}\DevStudio\{#VISUAL_VER}.{#VISUAL_REV}\Text Editor; ValueType: dword; ValueName: HorizontalScrollBars; ValueData: $00000001; Components: WndTabs
;Root: HKU; Subkey: .DEFAULT\Software\{#VISUAL_FIRM}\DevStudio\{#VISUAL_VER}.{#VISUAL_REV}\Text Editor; ValueType: dword; ValueName: ShowWizardBar; ValueData: $00000001; Components: WndTabs
;Root: HKU; Subkey: .DEFAULT\Software\{#VISUAL_FIRM}\DevStudio\{#VISUAL_VER}.{#VISUAL_REV}\Text Editor; ValueType: dword; ValueName: SaveBeforeBuild; ValueData: $00000001; Components: WndTabs
;Root: HKU; Subkey: .DEFAULT\Software\{#VISUAL_FIRM}\DevStudio\{#VISUAL_VER}.{#VISUAL_REV}\Text Editor; ValueType: dword; ValueName: SavePrompt; ValueData: $00000000; Components: WndTabs
;Root: HKU; Subkey: .DEFAULT\Software\{#VISUAL_FIRM}\DevStudio\{#VISUAL_VER}.{#VISUAL_REV}\Text Editor; ValueType: dword; ValueName: UndoSize; ValueData: $00010000; Components: WndTabs
;Root: HKU; Subkey: .DEFAULT\Software\{#VISUAL_FIRM}\DevStudio\{#VISUAL_VER}.{#VISUAL_REV}\Text Editor; ValueType: dword; ValueName: VirtualSpace; ValueData: $00000000; Components: WndTabs
;Root: HKU; Subkey: .DEFAULT\Software\{#VISUAL_FIRM}\DevStudio\{#VISUAL_VER}.{#VISUAL_REV}\Text Editor; ValueType: dword; ValueName: OpenNewWindow; ValueData: $00000001; Components: WndTabs
;Root: HKU; Subkey: .DEFAULT\Software\{#VISUAL_FIRM}\DevStudio\{#VISUAL_VER}.{#VISUAL_REV}\Text Editor; ValueType: dword; ValueName: MarginGlyphs; ValueData: $00000001; Components: WndTabs
;Root: HKU; Subkey: .DEFAULT\Software\{#VISUAL_FIRM}\DevStudio\{#VISUAL_VER}.{#VISUAL_REV}\Text Editor; ValueType: dword; ValueName: MarginWidth; ValueData: $00000014; Components: WndTabs
;Root: HKU; Subkey: .DEFAULT\Software\{#VISUAL_FIRM}\DevStudio\{#VISUAL_VER}.{#VISUAL_REV}\Text Editor; ValueType: dword; ValueName: TextDragging; ValueData: $00000001; Components: WndTabs
;Root: HKU; Subkey: .DEFAULT\Software\{#VISUAL_FIRM}\DevStudio\{#VISUAL_VER}.{#VISUAL_REV}\Text Editor; ValueType: dword; ValueName: UndoMove; ValueData: $00000000; Components: WndTabs
;Root: HKU; Subkey: .DEFAULT\Software\{#VISUAL_FIRM}\DevStudio\{#VISUAL_VER}.{#VISUAL_REV}\Text Editor; ValueType: dword; ValueName: NoBackspaceAtBOL; ValueData: $00000000; Components: WndTabs
;Root: HKU; Subkey: .DEFAULT\Software\{#VISUAL_FIRM}\DevStudio\{#VISUAL_VER}.{#VISUAL_REV}\Text Editor; ValueType: dword; ValueName: LineModePaste; ValueData: $00000000; Components: WndTabs
;Root: HKU; Subkey: .DEFAULT\Software\{#VISUAL_FIRM}\DevStudio\{#VISUAL_VER}.{#VISUAL_REV}\Text Editor; ValueType: dword; ValueName: AutoReload; ValueData: $00000000; Components: WndTabs
;Root: HKU; Subkey: .DEFAULT\Software\{#VISUAL_FIRM}\DevStudio\{#VISUAL_VER}.{#VISUAL_REV}\Text Editor; ValueType: dword; ValueName: FIF_SearchSubfolders; ValueData: $00000001; Components: WndTabs
;Root: HKU; Subkey: .DEFAULT\Software\{#VISUAL_FIRM}\DevStudio\{#VISUAL_VER}.{#VISUAL_REV}\Text Editor; ValueType: dword; ValueName: FIF_Advanced; ValueData: $00000000; Components: WndTabs
;Root: HKU; Subkey: .DEFAULT\Software\{#VISUAL_FIRM}\DevStudio\{#VISUAL_VER}.{#VISUAL_REV}\Text Editor; ValueType: dword; ValueName: FIF_SourcePath; ValueData: $00000000; Components: WndTabs
;Root: HKU; Subkey: .DEFAULT\Software\{#VISUAL_FIRM}\DevStudio\{#VISUAL_VER}.{#VISUAL_REV}\Text Editor; ValueType: dword; ValueName: FIF_IncludePath; ValueData: $00000000; Components: WndTabs
;Root: HKU; Subkey: .DEFAULT\Software\{#VISUAL_FIRM}\DevStudio\{#VISUAL_VER}.{#VISUAL_REV}\Text Editor; ValueType: dword; ValueName: ParaBreakAtIndent; ValueData: $00000000; Components: WndTabs
;Root: HKU; Subkey: .DEFAULT\Software\{#VISUAL_FIRM}\DevStudio\{#VISUAL_VER}.{#VISUAL_REV}\Text Editor; ValueType: dword; ValueName: NoROFileEditing; ValueData: $00000000; Components: WndTabs
;Root: HKU; Subkey: .DEFAULT\Software\{#VISUAL_FIRM}\DevStudio\{#VISUAL_VER}.{#VISUAL_REV}\Text Editor; ValueType: dword; ValueName: EnableAutoComplete; ValueData: $00000001; Components: WndTabs
;Root: HKU; Subkey: .DEFAULT\Software\{#VISUAL_FIRM}\DevStudio\{#VISUAL_VER}.{#VISUAL_REV}\Text Editor; ValueType: dword; ValueName: EnableQuickInfo; ValueData: $00000001; Components: WndTabs
;Root: HKU; Subkey: .DEFAULT\Software\{#VISUAL_FIRM}\DevStudio\{#VISUAL_VER}.{#VISUAL_REV}\Text Editor; ValueType: dword; ValueName: EnableParameterHelp; ValueData: $00000001; Components: WndTabs
;Root: HKU; Subkey: .DEFAULT\Software\{#VISUAL_FIRM}\DevStudio\{#VISUAL_VER}.{#VISUAL_REV}\Text Editor; ValueType: dword; ValueName: EnableAutoComments; ValueData: $00000001; Components: WndTabs
;Root: HKU; Subkey: .DEFAULT\Software\{#VISUAL_FIRM}\DevStudio\{#VISUAL_VER}.{#VISUAL_REV}\Text Editor; ValueType: dword; ValueName: NewDebugWindow; ValueData: $00000001; Components: WndTabs
;Root: HKU; Subkey: .DEFAULT\Software\{#VISUAL_FIRM}\DevStudio\{#VISUAL_VER}.{#VISUAL_REV}\Text Editor; ValueType: binary; ValueName: Compatibility; ValueData: 16 00 19 00 00 00 00 00 04 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00; Components: WndTabs

;Root: HKU; Subkey: .DEFAULT\Software\{#VISUAL_FIRM}\DevStudio\{#VISUAL_VER}.{#VISUAL_REV}\Text Editor\Tabs/Language Settings\C/C++; ValueType: string; ValueName: FileExtensions; ValueData: cpp;cxx;c;h;hxx;hpp;inl;tlh;tli;rc;rc2; Components: WndTabs
;Root: HKU; Subkey: .DEFAULT\Software\{#VISUAL_FIRM}\DevStudio\{#VISUAL_VER}.{#VISUAL_REV}\Text Editor\Tabs/Language Settings\C/C++; ValueType: dword; ValueName: InsertSpaces; ValueData: $00000000; Components: WndTabs
Root: HKU; Subkey: .DEFAULT\Software\{#VISUAL_FIRM}\DevStudio\{#VISUAL_VER}.{#VISUAL_REV}\Text Editor\Tabs/Language Settings\C/C++; ValueType: dword; ValueName: InsertSpaces; ValueData: $00000001; Components: Preconfig
;Root: HKU; Subkey: .DEFAULT\Software\{#VISUAL_FIRM}\DevStudio\{#VISUAL_VER}.{#VISUAL_REV}\Text Editor\Tabs/Language Settings\C/C++; ValueType: dword; ValueName: TabSize; ValueData: $00000004; Components: WndTabs
Root: HKU; Subkey: .DEFAULT\Software\{#VISUAL_FIRM}\DevStudio\{#VISUAL_VER}.{#VISUAL_REV}\Text Editor\Tabs/Language Settings\C/C++; ValueType: dword; ValueName: TabSize; ValueData: $00000002; Components: Preconfig
;Root: HKU; Subkey: .DEFAULT\Software\{#VISUAL_FIRM}\DevStudio\{#VISUAL_VER}.{#VISUAL_REV}\Text Editor\Tabs/Language Settings\C/C++; ValueType: dword; ValueName: IndentSize; ValueData: $00000004; Components: WndTabs
Root: HKU; Subkey: .DEFAULT\Software\{#VISUAL_FIRM}\DevStudio\{#VISUAL_VER}.{#VISUAL_REV}\Text Editor\Tabs/Language Settings\C/C++; ValueType: dword; ValueName: IndentSize; ValueData: $00000002; Components: Preconfig
;Root: HKU; Subkey: .DEFAULT\Software\{#VISUAL_FIRM}\DevStudio\{#VISUAL_VER}.{#VISUAL_REV}\Text Editor\Tabs/Language Settings\C/C++; ValueType: dword; ValueName: IndentType; ValueData: $00000002; Components: WndTabs
Root: HKU; Subkey: .DEFAULT\Software\{#VISUAL_FIRM}\DevStudio\{#VISUAL_VER}.{#VISUAL_REV}\Text Editor\Tabs/Language Settings\C/C++; ValueType: dword; ValueName: IndentType; ValueData: $00000001; Components: Preconfig
;Root: HKU; Subkey: .DEFAULT\Software\{#VISUAL_FIRM}\DevStudio\{#VISUAL_VER}.{#VISUAL_REV}\Text Editor\Tabs/Language Settings\C/C++; ValueType: dword; ValueName: InsertOpenToken; ValueData: $00000000; Components: WndTabs
;Root: HKU; Subkey: .DEFAULT\Software\{#VISUAL_FIRM}\DevStudio\{#VISUAL_VER}.{#VISUAL_REV}\Text Editor\Tabs/Language Settings\C/C++; ValueType: dword; ValueName: InsertCloseToken; ValueData: $00000000; Components: WndTabs
;Root: HKU; Subkey: .DEFAULT\Software\{#VISUAL_FIRM}\DevStudio\{#VISUAL_VER}.{#VISUAL_REV}\Text Editor\Tabs/Language Settings\C/C++; ValueType: dword; ValueName: LinesScannedBack; ValueData: $00000064; Components: WndTabs

;Root: HKU; Subkey: .DEFAULT\Software\{#VISUAL_FIRM}\DevStudio\{#VISUAL_VER}.{#VISUAL_REV}\Text Editor\Tabs/Language Settings\Default; ValueType: dword; ValueName: InsertSpaces; ValueData: $00000000; Components: WndTabs
Root: HKU; Subkey: .DEFAULT\Software\{#VISUAL_FIRM}\DevStudio\{#VISUAL_VER}.{#VISUAL_REV}\Text Editor\Tabs/Language Settings\Default; ValueType: dword; ValueName: InsertSpaces; ValueData: $00000001; Components: Preconfig
;Root: HKU; Subkey: .DEFAULT\Software\{#VISUAL_FIRM}\DevStudio\{#VISUAL_VER}.{#VISUAL_REV}\Text Editor\Tabs/Language Settings\Default; ValueType: dword; ValueName: TabSize; ValueData: $00000004; Components: WndTabs
Root: HKU; Subkey: .DEFAULT\Software\{#VISUAL_FIRM}\DevStudio\{#VISUAL_VER}.{#VISUAL_REV}\Text Editor\Tabs/Language Settings\Default; ValueType: dword; ValueName: TabSize; ValueData: $00000002; Components: Preconfig
;Root: HKU; Subkey: .DEFAULT\Software\{#VISUAL_FIRM}\DevStudio\{#VISUAL_VER}.{#VISUAL_REV}\Text Editor\Tabs/Language Settings\Default; ValueType: dword; ValueName: IndentSize; ValueData: $00000004; Components: WndTabs
Root: HKU; Subkey: .DEFAULT\Software\{#VISUAL_FIRM}\DevStudio\{#VISUAL_VER}.{#VISUAL_REV}\Text Editor\Tabs/Language Settings\Default; ValueType: dword; ValueName: IndentSize; ValueData: $00000002; Components: Preconfig
;Root: HKU; Subkey: .DEFAULT\Software\{#VISUAL_FIRM}\DevStudio\{#VISUAL_VER}.{#VISUAL_REV}\Text Editor\Tabs/Language Settings\Default; ValueType: dword; ValueName: IndentType; ValueData: $00000001; Components: WndTabs

;Root: HKU; Subkey: .DEFAULT\Software\{#VISUAL_FIRM}\DevStudio\{#VISUAL_VER}.{#VISUAL_REV}\Text Editor\Tabs/Language Settings\HTML; ValueType: string; ValueName: FileExtensions; ValueData: htm;html;stm;stml;asp;alx; Components: WndTabs
;Root: HKU; Subkey: .DEFAULT\Software\{#VISUAL_FIRM}\DevStudio\{#VISUAL_VER}.{#VISUAL_REV}\Text Editor\Tabs/Language Settings\HTML; ValueType: dword; ValueName: InsertSpaces; ValueData: $00000000; Components: WndTabs
Root: HKU; Subkey: .DEFAULT\Software\{#VISUAL_FIRM}\DevStudio\{#VISUAL_VER}.{#VISUAL_REV}\Text Editor\Tabs/Language Settings\HTML; ValueType: dword; ValueName: InsertSpaces; ValueData: $00000001; Components: Preconfig
;Root: HKU; Subkey: .DEFAULT\Software\{#VISUAL_FIRM}\DevStudio\{#VISUAL_VER}.{#VISUAL_REV}\Text Editor\Tabs/Language Settings\HTML; ValueType: dword; ValueName: TabSize; ValueData: $00000004; Components: WndTabs
Root: HKU; Subkey: .DEFAULT\Software\{#VISUAL_FIRM}\DevStudio\{#VISUAL_VER}.{#VISUAL_REV}\Text Editor\Tabs/Language Settings\HTML; ValueType: dword; ValueName: TabSize; ValueData: $00000002; Components: Preconfig
;Root: HKU; Subkey: .DEFAULT\Software\{#VISUAL_FIRM}\DevStudio\{#VISUAL_VER}.{#VISUAL_REV}\Text Editor\Tabs/Language Settings\HTML; ValueType: dword; ValueName: IndentSize; ValueData: $00000004; Components: WndTabs
Root: HKU; Subkey: .DEFAULT\Software\{#VISUAL_FIRM}\DevStudio\{#VISUAL_VER}.{#VISUAL_REV}\Text Editor\Tabs/Language Settings\HTML; ValueType: dword; ValueName: IndentSize; ValueData: $00000002; Components: Preconfig
;Root: HKU; Subkey: .DEFAULT\Software\{#VISUAL_FIRM}\DevStudio\{#VISUAL_VER}.{#VISUAL_REV}\Text Editor\Tabs/Language Settings\HTML; ValueType: dword; ValueName: IndentType; ValueData: $00000001; Components: WndTabs

;Root: HKU; Subkey: .DEFAULT\Software\{#VISUAL_FIRM}\DevStudio\{#VISUAL_VER}.{#VISUAL_REV}\Text Editor\Tabs/Language Settings\ODL/IDL; ValueType: string; ValueName: FileExtensions; ValueData: odl;idl;odh; Components: WndTabs
;Root: HKU; Subkey: .DEFAULT\Software\{#VISUAL_FIRM}\DevStudio\{#VISUAL_VER}.{#VISUAL_REV}\Text Editor\Tabs/Language Settings\ODL/IDL; ValueType: dword; ValueName: InsertSpaces; ValueData: $00000000; Components: WndTabs
Root: HKU; Subkey: .DEFAULT\Software\{#VISUAL_FIRM}\DevStudio\{#VISUAL_VER}.{#VISUAL_REV}\Text Editor\Tabs/Language Settings\ODL/IDL; ValueType: dword; ValueName: InsertSpaces; ValueData: $00000001; Components: Preconfig
;Root: HKU; Subkey: .DEFAULT\Software\{#VISUAL_FIRM}\DevStudio\{#VISUAL_VER}.{#VISUAL_REV}\Text Editor\Tabs/Language Settings\ODL/IDL; ValueType: dword; ValueName: TabSize; ValueData: $00000004; Components: WndTabs
Root: HKU; Subkey: .DEFAULT\Software\{#VISUAL_FIRM}\DevStudio\{#VISUAL_VER}.{#VISUAL_REV}\Text Editor\Tabs/Language Settings\ODL/IDL; ValueType: dword; ValueName: TabSize; ValueData: $00000002; Components: Preconfig
;Root: HKU; Subkey: .DEFAULT\Software\{#VISUAL_FIRM}\DevStudio\{#VISUAL_VER}.{#VISUAL_REV}\Text Editor\Tabs/Language Settings\ODL/IDL; ValueType: dword; ValueName: IndentSize; ValueData: $00000004; Components: WndTabs
Root: HKU; Subkey: .DEFAULT\Software\{#VISUAL_FIRM}\DevStudio\{#VISUAL_VER}.{#VISUAL_REV}\Text Editor\Tabs/Language Settings\ODL/IDL; ValueType: dword; ValueName: IndentSize; ValueData: $00000002; Components: Preconfig
;Root: HKU; Subkey: .DEFAULT\Software\{#VISUAL_FIRM}\DevStudio\{#VISUAL_VER}.{#VISUAL_REV}\Text Editor\Tabs/Language Settings\ODL/IDL; ValueType: dword; ValueName: IndentType; ValueData: $00000001; Components: WndTabs

;Root: HKU; Subkey: .DEFAULT\Software\{#VISUAL_FIRM}\DevStudio\{#VISUAL_VER}.{#VISUAL_REV}\Text Editor\Tabs/Language Settings\SQL; ValueType: string; ValueName: FileExtensions; ValueData: sql;tsq;ssq; Components: WndTabs
;Root: HKU; Subkey: .DEFAULT\Software\{#VISUAL_FIRM}\DevStudio\{#VISUAL_VER}.{#VISUAL_REV}\Text Editor\Tabs/Language Settings\SQL; ValueType: dword; ValueName: InsertSpaces; ValueData: $00000000; Components: WndTabs
Root: HKU; Subkey: .DEFAULT\Software\{#VISUAL_FIRM}\DevStudio\{#VISUAL_VER}.{#VISUAL_REV}\Text Editor\Tabs/Language Settings\SQL; ValueType: dword; ValueName: InsertSpaces; ValueData: $00000001; Components: Preconfig
;Root: HKU; Subkey: .DEFAULT\Software\{#VISUAL_FIRM}\DevStudio\{#VISUAL_VER}.{#VISUAL_REV}\Text Editor\Tabs/Language Settings\SQL; ValueType: dword; ValueName: TabSize; ValueData: $00000004; Components: WndTabs
Root: HKU; Subkey: .DEFAULT\Software\{#VISUAL_FIRM}\DevStudio\{#VISUAL_VER}.{#VISUAL_REV}\Text Editor\Tabs/Language Settings\SQL; ValueType: dword; ValueName: TabSize; ValueData: $00000002; Components: Preconfig
;Root: HKU; Subkey: .DEFAULT\Software\{#VISUAL_FIRM}\DevStudio\{#VISUAL_VER}.{#VISUAL_REV}\Text Editor\Tabs/Language Settings\SQL; ValueType: dword; ValueName: IndentSize; ValueData: $00000004; Components: WndTabs
Root: HKU; Subkey: .DEFAULT\Software\{#VISUAL_FIRM}\DevStudio\{#VISUAL_VER}.{#VISUAL_REV}\Text Editor\Tabs/Language Settings\SQL; ValueType: dword; ValueName: IndentSize; ValueData: $00000002; Components: Preconfig
;Root: HKU; Subkey: .DEFAULT\Software\{#VISUAL_FIRM}\DevStudio\{#VISUAL_VER}.{#VISUAL_REV}\Text Editor\Tabs/Language Settings\SQL; ValueType: dword; ValueName: IndentType; ValueData: $00000001; Components: WndTabs

;Root: HKU; Subkey: .DEFAULT\Software\{#VISUAL_FIRM}\DevStudio\{#VISUAL_VER}.{#VISUAL_REV}\Text Editor\Tabs/Language Settings\VBS Macro; ValueType: string; ValueName: FileExtensions; ValueData: DSM; Components: WndTabs
;Root: HKU; Subkey: .DEFAULT\Software\{#VISUAL_FIRM}\DevStudio\{#VISUAL_VER}.{#VISUAL_REV}\Text Editor\Tabs/Language Settings\VBS Macro; ValueType: dword; ValueName: InsertSpaces; ValueData: $00000000; Components: WndTabs
Root: HKU; Subkey: .DEFAULT\Software\{#VISUAL_FIRM}\DevStudio\{#VISUAL_VER}.{#VISUAL_REV}\Text Editor\Tabs/Language Settings\VBS Macro; ValueType: dword; ValueName: InsertSpaces; ValueData: $00000001; Components: Preconfig
;Root: HKU; Subkey: .DEFAULT\Software\{#VISUAL_FIRM}\DevStudio\{#VISUAL_VER}.{#VISUAL_REV}\Text Editor\Tabs/Language Settings\VBS Macro; ValueType: dword; ValueName: TabSize; ValueData: $00000004; Components: WndTabs
Root: HKU; Subkey: .DEFAULT\Software\{#VISUAL_FIRM}\DevStudio\{#VISUAL_VER}.{#VISUAL_REV}\Text Editor\Tabs/Language Settings\VBS Macro; ValueType: dword; ValueName: TabSize; ValueData: $00000002; Components: Preconfig
;Root: HKU; Subkey: .DEFAULT\Software\{#VISUAL_FIRM}\DevStudio\{#VISUAL_VER}.{#VISUAL_REV}\Text Editor\Tabs/Language Settings\VBS Macro; ValueType: dword; ValueName: IndentSize; ValueData: $00000004; Components: WndTabs
Root: HKU; Subkey: .DEFAULT\Software\{#VISUAL_FIRM}\DevStudio\{#VISUAL_VER}.{#VISUAL_REV}\Text Editor\Tabs/Language Settings\VBS Macro; ValueType: dword; ValueName: IndentSize; ValueData: $00000002; Components: Preconfig
;Root: HKU; Subkey: .DEFAULT\Software\{#VISUAL_FIRM}\DevStudio\{#VISUAL_VER}.{#VISUAL_REV}\Text Editor\Tabs/Language Settings\VBS Macro; ValueType: dword; ValueName: IndentType; ValueData: $00000001; Components: WndTabs

;Root: HKU; Subkey: .DEFAULT\Software\{#VISUAL_FIRM}\DevStudio\{#VISUAL_VER}.{#VISUAL_REV}\Tools; ValueType: dword; ValueName: NumTools; ValueData: $00000007; Components: WndTabs
;Root: HKU; Subkey: .DEFAULT\Software\{#VISUAL_FIRM}\DevStudio\{#VISUAL_VER}.{#VISUAL_REV}\Tools; ValueType: string; ValueName: MenuName#0; ValueData: Re&gister Control; Components: WndTabs
;Root: HKU; Subkey: .DEFAULT\Software\{#VISUAL_FIRM}\DevStudio\{#VISUAL_VER}.{#VISUAL_REV}\Tools; ValueType: string; ValueName: PathName#0; ValueData: {win}\System32\regsvr32.exe; Components: WndTabs
;Root: HKU; Subkey: .DEFAULT\Software\{#VISUAL_FIRM}\DevStudio\{#VISUAL_VER}.{#VISUAL_REV}\Tools; ValueType: string; ValueName: DefaultArguments#0; ValueData: /v \"$(TargetPath)\"; Components: WndTabs
;Root: HKU; Subkey: .DEFAULT\Software\{#VISUAL_FIRM}\DevStudio\{#VISUAL_VER}.{#VISUAL_REV}\Tools; ValueType: string; ValueName: InitialDirectory#0; ValueData: $(TargetDir); Components: WndTabs
;Root: HKU; Subkey: .DEFAULT\Software\{#VISUAL_FIRM}\DevStudio\{#VISUAL_VER}.{#VISUAL_REV}\Tools; ValueType: dword; ValueName: AskArgument#0; ValueData: $00000000; Components: WndTabs
;Root: HKU; Subkey: .DEFAULT\Software\{#VISUAL_FIRM}\DevStudio\{#VISUAL_VER}.{#VISUAL_REV}\Tools; ValueType: dword; ValueName: GUITool#0; ValueData: $00000001; Components: WndTabs
;Root: HKU; Subkey: .DEFAULT\Software\{#VISUAL_FIRM}\DevStudio\{#VISUAL_VER}.{#VISUAL_REV}\Tools; ValueType: dword; ValueName: OutputRedirect#0; ValueData: $00000000; Components: WndTabs
;Root: HKU; Subkey: .DEFAULT\Software\{#VISUAL_FIRM}\DevStudio\{#VISUAL_VER}.{#VISUAL_REV}\Tools; ValueType: dword; ValueName: CloseWindow#0; ValueData: $00000000; Components: WndTabs
;Root: HKU; Subkey: .DEFAULT\Software\{#VISUAL_FIRM}\DevStudio\{#VISUAL_VER}.{#VISUAL_REV}\Tools; ValueType: dword; ValueName: UseSearchPath#0; ValueData: $00000030; Components: WndTabs
;Root: HKU; Subkey: .DEFAULT\Software\{#VISUAL_FIRM}\DevStudio\{#VISUAL_VER}.{#VISUAL_REV}\Tools; ValueType: dword; ValueName: VisibleOnMenu#0; ValueData: $00000000; Components: WndTabs
;Root: HKU; Subkey: .DEFAULT\Software\{#VISUAL_FIRM}\DevStudio\{#VISUAL_VER}.{#VISUAL_REV}\Tools; ValueType: dword; ValueName: ReloadNoPrompt#0; ValueData: $00000000; Components: WndTabs
;Root: HKU; Subkey: .DEFAULT\Software\{#VISUAL_FIRM}\DevStudio\{#VISUAL_VER}.{#VISUAL_REV}\Tools; ValueType: string; ValueName: MenuName#1; ValueData: Visual Component M&anager; Components: WndTabs
;Root: HKU; Subkey: .DEFAULT\Software\{#VISUAL_FIRM}\DevStudio\{#VISUAL_VER}.{#VISUAL_REV}\Tools; ValueType: string; ValueName: PathName#1; ValueData: {pf}\Internet Explorer\iexplore.exe; Components: WndTabs
;Root: HKU; Subkey: .DEFAULT\Software\{#VISUAL_FIRM}\DevStudio\{#VISUAL_VER}.{#VISUAL_REV}\Tools; ValueType: string; ValueName: DefaultArguments#1; ValueData: {app}\Common\Tools\VCM\vcm.vbd; Components: WndTabs
;Root: HKU; Subkey: .DEFAULT\Software\{#VISUAL_FIRM}\DevStudio\{#VISUAL_VER}.{#VISUAL_REV}\Tools; ValueType: string; ValueName: InitialDirectory#1; ValueData: {app}\Common\Tools\VCM\; Components: WndTabs
;Root: HKU; Subkey: .DEFAULT\Software\{#VISUAL_FIRM}\DevStudio\{#VISUAL_VER}.{#VISUAL_REV}\Tools; ValueType: dword; ValueName: AskArgument#1; ValueData: $00000000; Components: WndTabs
;Root: HKU; Subkey: .DEFAULT\Software\{#VISUAL_FIRM}\DevStudio\{#VISUAL_VER}.{#VISUAL_REV}\Tools; ValueType: dword; ValueName: GUITool#1; ValueData: $00000001; Components: WndTabs
;Root: HKU; Subkey: .DEFAULT\Software\{#VISUAL_FIRM}\DevStudio\{#VISUAL_VER}.{#VISUAL_REV}\Tools; ValueType: dword; ValueName: OutputRedirect#1; ValueData: $00000000; Components: WndTabs
;Root: HKU; Subkey: .DEFAULT\Software\{#VISUAL_FIRM}\DevStudio\{#VISUAL_VER}.{#VISUAL_REV}\Tools; ValueType: dword; ValueName: CloseWindow#1; ValueData: $00000000; Components: WndTabs
;Root: HKU; Subkey: .DEFAULT\Software\{#VISUAL_FIRM}\DevStudio\{#VISUAL_VER}.{#VISUAL_REV}\Tools; ValueType: dword; ValueName: UseSearchPath#1; ValueData: $00000030; Components: WndTabs
;Root: HKU; Subkey: .DEFAULT\Software\{#VISUAL_FIRM}\DevStudio\{#VISUAL_VER}.{#VISUAL_REV}\Tools; ValueType: dword; ValueName: VisibleOnMenu#1; ValueData: $00000000; Components: WndTabs
;Root: HKU; Subkey: .DEFAULT\Software\{#VISUAL_FIRM}\DevStudio\{#VISUAL_VER}.{#VISUAL_REV}\Tools; ValueType: dword; ValueName: ReloadNoPrompt#1; ValueData: $00000000; Components: WndTabs
;Root: HKU; Subkey: .DEFAULT\Software\{#VISUAL_FIRM}\DevStudio\{#VISUAL_VER}.{#VISUAL_REV}\Tools; ValueType: string; ValueName: MenuName#2; ValueData: Error Loo&kup; Components: WndTabs
;Root: HKU; Subkey: .DEFAULT\Software\{#VISUAL_FIRM}\DevStudio\{#VISUAL_VER}.{#VISUAL_REV}\Tools; ValueType: string; ValueName: PathName#2; ValueData: {app}\Common\Tools\errlook.exe; Components: WndTabs
;Root: HKU; Subkey: .DEFAULT\Software\{#VISUAL_FIRM}\DevStudio\{#VISUAL_VER}.{#VISUAL_REV}\Tools; ValueType: string; ValueName: DefaultArguments#2; Components: WndTabs
;Root: HKU; Subkey: .DEFAULT\Software\{#VISUAL_FIRM}\DevStudio\{#VISUAL_VER}.{#VISUAL_REV}\Tools; ValueType: string; ValueName: InitialDirectory#2; ValueData: $ (TargetDir); Components: WndTabs
;Root: HKU; Subkey: .DEFAULT\Software\{#VISUAL_FIRM}\DevStudio\{#VISUAL_VER}.{#VISUAL_REV}\Tools; ValueType: dword; ValueName: AskArgument#2; ValueData: $00000000; Components: WndTabs
;Root: HKU; Subkey: .DEFAULT\Software\{#VISUAL_FIRM}\DevStudio\{#VISUAL_VER}.{#VISUAL_REV}\Tools; ValueType: dword; ValueName: GUITool#2; ValueData: $00000001; Components: WndTabs
;Root: HKU; Subkey: .DEFAULT\Software\{#VISUAL_FIRM}\DevStudio\{#VISUAL_VER}.{#VISUAL_REV}\Tools; ValueType: dword; ValueName: OutputRedirect#2; ValueData: $00000000; Components: WndTabs
;Root: HKU; Subkey: .DEFAULT\Software\{#VISUAL_FIRM}\DevStudio\{#VISUAL_VER}.{#VISUAL_REV}\Tools; ValueType: dword; ValueName: CloseWindow#2; ValueData: $00000000; Components: WndTabs
;Root: HKU; Subkey: .DEFAULT\Software\{#VISUAL_FIRM}\DevStudio\{#VISUAL_VER}.{#VISUAL_REV}\Tools; ValueType: dword; ValueName: UseSearchPath#2; ValueData: $00000030; Components: WndTabs
;Root: HKU; Subkey: .DEFAULT\Software\{#VISUAL_FIRM}\DevStudio\{#VISUAL_VER}.{#VISUAL_REV}\Tools; ValueType: dword; ValueName: VisibleOnMenu#2; ValueData: $00000000; Components: WndTabs
;Root: HKU; Subkey: .DEFAULT\Software\{#VISUAL_FIRM}\DevStudio\{#VISUAL_VER}.{#VISUAL_REV}\Tools; ValueType: dword; ValueName: ReloadNoPrompt#2; ValueData: $00000000; Components: WndTabs
;Root: HKU; Subkey: .DEFAULT\Software\{#VISUAL_FIRM}\DevStudio\{#VISUAL_VER}.{#VISUAL_REV}\Tools; ValueType: string; ValueName: MenuName#3; ValueData: Activ&eX Control Test Container; Components: WndTabs
;Root: HKU; Subkey: .DEFAULT\Software\{#VISUAL_FIRM}\DevStudio\{#VISUAL_VER}.{#VISUAL_REV}\Tools; ValueType: string; ValueName: PathName#3; ValueData: {app}\Common\Tools\tstcon32.exe; Components: WndTabs
;Root: HKU; Subkey: .DEFAULT\Software\{#VISUAL_FIRM}\DevStudio\{#VISUAL_VER}.{#VISUAL_REV}\Tools; ValueType: string; ValueName: DefaultArguments#3; Components: WndTabs
;Root: HKU; Subkey: .DEFAULT\Software\{#VISUAL_FIRM}\DevStudio\{#VISUAL_VER}.{#VISUAL_REV}\Tools; ValueType: string; ValueName: InitialDirectory#3; ValueData: $ (TargetDir); Components: WndTabs
;Root: HKU; Subkey: .DEFAULT\Software\{#VISUAL_FIRM}\DevStudio\{#VISUAL_VER}.{#VISUAL_REV}\Tools; ValueType: dword; ValueName: AskArgument#3; ValueData: $00000000; Components: WndTabs
;Root: HKU; Subkey: .DEFAULT\Software\{#VISUAL_FIRM}\DevStudio\{#VISUAL_VER}.{#VISUAL_REV}\Tools; ValueType: dword; ValueName: GUITool#3; ValueData: $00000001; Components: WndTabs
;Root: HKU; Subkey: .DEFAULT\Software\{#VISUAL_FIRM}\DevStudio\{#VISUAL_VER}.{#VISUAL_REV}\Tools; ValueType: dword; ValueName: OutputRedirect#3; ValueData: $00000000; Components: WndTabs
;Root: HKU; Subkey: .DEFAULT\Software\{#VISUAL_FIRM}\DevStudio\{#VISUAL_VER}.{#VISUAL_REV}\Tools; ValueType: dword; ValueName: CloseWindow#3; ValueData: $00000000; Components: WndTabs
;Root: HKU; Subkey: .DEFAULT\Software\{#VISUAL_FIRM}\DevStudio\{#VISUAL_VER}.{#VISUAL_REV}\Tools; ValueType: dword; ValueName: UseSearchPath#3; ValueData: $00000030; Components: WndTabs
;Root: HKU; Subkey: .DEFAULT\Software\{#VISUAL_FIRM}\DevStudio\{#VISUAL_VER}.{#VISUAL_REV}\Tools; ValueType: dword; ValueName: VisibleOnMenu#3; ValueData: $00000000; Components: WndTabs
;Root: HKU; Subkey: .DEFAULT\Software\{#VISUAL_FIRM}\DevStudio\{#VISUAL_VER}.{#VISUAL_REV}\Tools; ValueType: dword; ValueName: ReloadNoPrompt#3; ValueData: $00000000; Components: WndTabs
;Root: HKU; Subkey: .DEFAULT\Software\{#VISUAL_FIRM}\DevStudio\{#VISUAL_VER}.{#VISUAL_REV}\Tools; ValueType: string; ValueName: MenuName#4; ValueData: OLE/COM Object &Viewer; Components: WndTabs
;Root: HKU; Subkey: .DEFAULT\Software\{#VISUAL_FIRM}\DevStudio\{#VISUAL_VER}.{#VISUAL_REV}\Tools; ValueType: string; ValueName: PathName#4; ValueData: {app}\Common\Tools\oleview.exe; Components: WndTabs
;Root: HKU; Subkey: .DEFAULT\Software\{#VISUAL_FIRM}\DevStudio\{#VISUAL_VER}.{#VISUAL_REV}\Tools; ValueType: string; ValueName: DefaultArguments#4; Components: WndTabs
;Root: HKU; Subkey: .DEFAULT\Software\{#VISUAL_FIRM}\DevStudio\{#VISUAL_VER}.{#VISUAL_REV}\Tools; ValueType: string; ValueName: InitialDirectory#4; ValueData: {app}\Common\Tools\; Components: WndTabs
;Root: HKU; Subkey: .DEFAULT\Software\{#VISUAL_FIRM}\DevStudio\{#VISUAL_VER}.{#VISUAL_REV}\Tools; ValueType: dword; ValueName: AskArgument#4; ValueData: $00000000; Components: WndTabs
;Root: HKU; Subkey: .DEFAULT\Software\{#VISUAL_FIRM}\DevStudio\{#VISUAL_VER}.{#VISUAL_REV}\Tools; ValueType: dword; ValueName: GUITool#4; ValueData: $00000001; Components: WndTabs
;Root: HKU; Subkey: .DEFAULT\Software\{#VISUAL_FIRM}\DevStudio\{#VISUAL_VER}.{#VISUAL_REV}\Tools; ValueType: dword; ValueName: OutputRedirect#4; ValueData: $00000000; Components: WndTabs
;Root: HKU; Subkey: .DEFAULT\Software\{#VISUAL_FIRM}\DevStudio\{#VISUAL_VER}.{#VISUAL_REV}\Tools; ValueType: dword; ValueName: CloseWindow#4; ValueData: $00000000; Components: WndTabs
;Root: HKU; Subkey: .DEFAULT\Software\{#VISUAL_FIRM}\DevStudio\{#VISUAL_VER}.{#VISUAL_REV}\Tools; ValueType: dword; ValueName: UseSearchPath#4; ValueData: $00000030; Components: WndTabs
;Root: HKU; Subkey: .DEFAULT\Software\{#VISUAL_FIRM}\DevStudio\{#VISUAL_VER}.{#VISUAL_REV}\Tools; ValueType: dword; ValueName: VisibleOnMenu#4; ValueData: $00000000; Components: WndTabs
;Root: HKU; Subkey: .DEFAULT\Software\{#VISUAL_FIRM}\DevStudio\{#VISUAL_VER}.{#VISUAL_REV}\Tools; ValueType: dword; ValueName: ReloadNoPrompt#4; ValueData: $00000000; Components: WndTabs
;Root: HKU; Subkey: .DEFAULT\Software\{#VISUAL_FIRM}\DevStudio\{#VISUAL_VER}.{#VISUAL_REV}\Tools; ValueType: string; ValueName: MenuName#5; ValueData: S&py++; Components: WndTabs
;Root: HKU; Subkey: .DEFAULT\Software\{#VISUAL_FIRM}\DevStudio\{#VISUAL_VER}.{#VISUAL_REV}\Tools; ValueType: string; ValueName: PathName#5; ValueData: {app}\Common\Tools\spyxx.exe; Components: WndTabs
;Root: HKU; Subkey: .DEFAULT\Software\{#VISUAL_FIRM}\DevStudio\{#VISUAL_VER}.{#VISUAL_REV}\Tools; ValueType: string; ValueName: DefaultArguments#5; Components: WndTabs
;Root: HKU; Subkey: .DEFAULT\Software\{#VISUAL_FIRM}\DevStudio\{#VISUAL_VER}.{#VISUAL_REV}\Tools; ValueType: string; ValueName: InitialDirectory#5; ValueData: {app}\Common\Tools\; Components: WndTabs
;Root: HKU; Subkey: .DEFAULT\Software\{#VISUAL_FIRM}\DevStudio\{#VISUAL_VER}.{#VISUAL_REV}\Tools; ValueType: dword; ValueName: AskArgument#5; ValueData: $00000000; Components: WndTabs
;Root: HKU; Subkey: .DEFAULT\Software\{#VISUAL_FIRM}\DevStudio\{#VISUAL_VER}.{#VISUAL_REV}\Tools; ValueType: dword; ValueName: GUITool#5; ValueData: $00000001; Components: WndTabs
;Root: HKU; Subkey: .DEFAULT\Software\{#VISUAL_FIRM}\DevStudio\{#VISUAL_VER}.{#VISUAL_REV}\Tools; ValueType: dword; ValueName: OutputRedirect#5; ValueData: $00000000; Components: WndTabs
;Root: HKU; Subkey: .DEFAULT\Software\{#VISUAL_FIRM}\DevStudio\{#VISUAL_VER}.{#VISUAL_REV}\Tools; ValueType: dword; ValueName: CloseWindow#5; ValueData: $00000000; Components: WndTabs
;Root: HKU; Subkey: .DEFAULT\Software\{#VISUAL_FIRM}\DevStudio\{#VISUAL_VER}.{#VISUAL_REV}\Tools; ValueType: dword; ValueName: UseSearchPath#5; ValueData: $00000030; Components: WndTabs
;Root: HKU; Subkey: .DEFAULT\Software\{#VISUAL_FIRM}\DevStudio\{#VISUAL_VER}.{#VISUAL_REV}\Tools; ValueType: dword; ValueName: VisibleOnMenu#5; ValueData: $00000000; Components: WndTabs
;Root: HKU; Subkey: .DEFAULT\Software\{#VISUAL_FIRM}\DevStudio\{#VISUAL_VER}.{#VISUAL_REV}\Tools; ValueType: dword; ValueName: ReloadNoPrompt#5; ValueData: $00000000; Components: WndTabs
;Root: HKU; Subkey: .DEFAULT\Software\{#VISUAL_FIRM}\DevStudio\{#VISUAL_VER}.{#VISUAL_REV}\Tools; ValueType: string; ValueName: MenuName#6; ValueData: MFC &Tracer; Components: WndTabs
;Root: HKU; Subkey: .DEFAULT\Software\{#VISUAL_FIRM}\DevStudio\{#VISUAL_VER}.{#VISUAL_REV}\Tools; ValueType: string; ValueName: PathName#6; ValueData: {app}\Common\Tools\tracer.exe; Components: WndTabs
;Root: HKU; Subkey: .DEFAULT\Software\{#VISUAL_FIRM}\DevStudio\{#VISUAL_VER}.{#VISUAL_REV}\Tools; ValueType: string; ValueName: DefaultArguments#6; Components: WndTabs
;Root: HKU; Subkey: .DEFAULT\Software\{#VISUAL_FIRM}\DevStudio\{#VISUAL_VER}.{#VISUAL_REV}\Tools; ValueType: string; ValueName: InitialDirectory#6; ValueData: {app}\Common\Tools\; Components: WndTabs
;Root: HKU; Subkey: .DEFAULT\Software\{#VISUAL_FIRM}\DevStudio\{#VISUAL_VER}.{#VISUAL_REV}\Tools; ValueType: dword; ValueName: AskArgument#6; ValueData: $00000000; Components: WndTabs
;Root: HKU; Subkey: .DEFAULT\Software\{#VISUAL_FIRM}\DevStudio\{#VISUAL_VER}.{#VISUAL_REV}\Tools; ValueType: dword; ValueName: GUITool#6; ValueData: $00000001; Components: WndTabs
;Root: HKU; Subkey: .DEFAULT\Software\{#VISUAL_FIRM}\DevStudio\{#VISUAL_VER}.{#VISUAL_REV}\Tools; ValueType: dword; ValueName: OutputRedirect#6; ValueData: $00000000; Components: WndTabs
;Root: HKU; Subkey: .DEFAULT\Software\{#VISUAL_FIRM}\DevStudio\{#VISUAL_VER}.{#VISUAL_REV}\Tools; ValueType: dword; ValueName: CloseWindow#6; ValueData: $00000000; Components: WndTabs
;Root: HKU; Subkey: .DEFAULT\Software\{#VISUAL_FIRM}\DevStudio\{#VISUAL_VER}.{#VISUAL_REV}\Tools; ValueType: dword; ValueName: UseSearchPath#6; ValueData: $00000030; Components: WndTabs
;Root: HKU; Subkey: .DEFAULT\Software\{#VISUAL_FIRM}\DevStudio\{#VISUAL_VER}.{#VISUAL_REV}\Tools; ValueType: dword; ValueName: VisibleOnMenu#6; ValueData: $00000000; Components: WndTabs
;Root: HKU; Subkey: .DEFAULT\Software\{#VISUAL_FIRM}\DevStudio\{#VISUAL_VER}.{#VISUAL_REV}\Tools; ValueType: dword; ValueName: ReloadNoPrompt#6; ValueData: $00000000; Components: WndTabs

;Root: HKU; Subkey: .DEFAULT\Software\{#VISUAL_FIRM}\DevStudio\{#VISUAL_VER}.{#VISUAL_REV}\Workspace; ValueType: string; ValueName: LastProject; Components: WndTabs
#endif

Root: HKU; Subkey: .DEFAULT\Environment; ValueType: string; ValueName: path; ValueData: "{app}\Common\Tools\WinNT;{app}\Common\MSDev98\Bin;{app}\Common\Tools;{app}\VC98\bin"
Root: HKU; Subkey: .DEFAULT\Environment; ValueType: string; ValueName: MSDevDir; ValueData: {app}\Common\MSDev98
Root: HKU; Subkey: .DEFAULT\Environment; ValueType: string; ValueName: include; ValueData: "{app}\VC98\atl\include;{app}\VC98\mfc\include;{app}\VC98\include"
Root: HKU; Subkey: .DEFAULT\Environment; ValueType: string; ValueName: lib; ValueData: "{app}\VC98\mfc\lib;{app}\VC98\lib"

Root: HKU; Subkey: .DEFAULT\Software\{#VISUAL_FIRM}\MS Setup (ACME)\User Info; ValueType: string; ValueName: DefName; ValueData: HOMEBREW; Components: Msdn
Root: HKU; Subkey: .DEFAULT\Software\{#VISUAL_FIRM}\MS Setup (ACME)\User Info; ValueType: string; ValueName: DefCompany; ValueData: 4DC; Components: Msdn

#ifdef INSTALL_WNDTABS
Root: HKU; Subkey: .DEFAULT\Software\WndTabs.com\WndTabs\3.2; ValueType: dword; ValueName: DoWizAtStartup; ValueData: $00000001; Components: WndTabs

Root: HKU; Subkey: .DEFAULT\Software\WndTabs.com\WndTabs\3.2\Layout\BCGControlBarVersion; ValueType: dword; ValueName: Major; ValueData: $00000004; Components: WndTabs
Root: HKU; Subkey: .DEFAULT\Software\WndTabs.com\WndTabs\3.2\Layout\BCGControlBarVersion; ValueType: dword; ValueName: Minor; ValueData: $0000004a; Components: WndTabs

Root: HKU; Subkey: .DEFAULT\Software\WndTabs.com\WndTabs\3.2\Layout\BCGKeyboard-0; ValueType: binary; ValueName: Accelerators; ValueData: 1f 00 7b 00 86 04; Components: WndTabs

Root: HKU; Subkey: .DEFAULT\Software\WndTabs.com\WndTabs\3.2\Layout\BCGToolBar-01c9; ValueType: binary; ValueName: Buttons; ValueData: 03 00 ff ff 01 00 15 00 43 42 43 47 54 6f 6f 6c 62 61 72 4d 65 6e 75 42 75 74 74 6f 6e d2 2a 00 00 00 00 04 00 06 00 00 00 11 46 65 72 6d 65 72 20 6c 65 20 26 67 72 6f 75 70 65 00 00 00 00 00 00 00 00 01 00 00 00 01 00 00 00 00 00 00 00 00 00 01 80 cb 2a 00 00 00 00 04 00 ff ff ff ff 1a 46 65 72 6d 65 72 20 6c 65 73 20 26 61 75 74 72 65 73 20 6f 6e 67 6c 65 74 73 01 00 00 00 00 00 00 00 01 00 00 00 00 00 00 00 00 00 00 00 00 00 01 80 53 2a 00 00 00 00 04 00 04 00 00 00 0c 26 54 6f 75 74 20 66 65 72 6d 65 72 00 00 00 00 00 00 00 00 01 00 00 00 01 00 00 00 00 00 00 00 00 00 00 00 00 00 00; Components: WndTabs

Root: HKU; Subkey: .DEFAULT\Software\WndTabs.com\WndTabs\3.2\Layout\BCGToolBar-082; ValueType: binary; ValueName: Buttons; ValueData: 


Root: HKU; Subkey: .DEFAULT\Software\WndTabs.com\WndTabs\3.2\Layout\BCGToolBar-593980; ValueType: string; ValueName: Name; ValueData: WndTabs Dockbar; Components: WndTabs
Root: HKU; Subkey: .DEFAULT\Software\WndTabs.com\WndTabs\3.2\Layout\BCGToolBar-593980; ValueType: binary; ValueName: Buttons; ValueData: 01 00 ff ff 01 00 15 00 43 42 43 47 54 6f 6f 6c 62 61 72 4d 65 6e 75 42 75 74 74 6f 6e 00 00 00 00 00 00 00 00 00 00 00 00 07 57 6e 64 54 61 62 73 00 00 00 00 00 00 00 00 00 00 00 00 01 00 00 00 00 00 00 00 0a 00 01 80 e4 2e 00 00 00 00 00 00 1a 00 00 00 17 26 52 e9 6f 72 64 6f 6e 6e 65 72 20 6c 65 73 20 6f 6e 67 6c 65 74 73 00 00 00 00 00 00 00 00 01 00 00 00 00 00 00 00 00 00 00 00 00 00 01 80 e3 2e 00 00 00 00 00 00 19 00 00 00 18 52 65 26 6e 75 6d e9 72 6f 74 65 72 20 6c 65 73 20 6f 6e 67 6c 65 74 73 00 00 00 00 00 00 00 00 01 00 00 00 00 00 00 00 00 00 00 00 00 00 01 80 00 00 00 00 00 00 00 00 ff ff ff ff 00 00 00 00 00 00 00 00 00 01 00 00 00 00 00 00 00 00 00 00 00 00 00 01 80 ff ff ff ff 00 00 00 00 ff ff ff ff 0a 43 6f 6d 70 6f 73 61 6e 74 73 00 00 00 00 00 00 00 00 01 00 00 00 00 00 00 00 00 00 00 00 01 00 01 80 e7 2a 00 00 00 00 00 00 ff ff ff ff 00 00 00 00 00 00 00 00 00 01 00 00 00 00 00 00 00 00 00 00 00 00 00 01 80 00 00 00 00 00 00 00 00 ff ff ff ff 00 00 00 00 00 00 00 00 00 01 00 00 00 00 00 00 00 00 00 00 00 00 00 01 80 e1 2e 00 00 00 00 00 00 18 00 00 00 0b 26 4f 70 74 69 6f 6e 73 2e 2e 2e 00 00 00 00 00 00 00 00 01 00 00 00 00 00 00 00 00 00 00 00 00 00 01 80 df 2a 00 00 00 00 00 00 ff ff ff ff 11 50 65 72 26 73 6f 6e 6e 61 6c 69 73 65 72 2e 2e 2e 00 00 00 00 00 00 00 00 01 00 00 00 00 00 00 00 00 00 00 00 00 00 01 80 00 00 00 00 00 00 00 00 ff ff ff ff 00 00 00 00 00 00 00 00 00 01 00 00 00 00 00 00 00 00 00 00 00 00 00 01 80 ac 04 00 00 00 00 00 00 16 00 00 00 05 26 41 69 64 65 00 00 00 00 00 00 00 00 01 00 00 00 00 00 00 00 00 00 00 00 00 00 01 80 e0 2e 00 00 00 00 00 00 17 00 00 00 14 41 20 26 70 72 6f 70 6f 73 20 64 65 20 57 6e 64 54 61 62 73 00 00 00 00 00 00 00 00 01 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 0f 57 6e 64 54 61 62 73 20 44 6f 63 6b 62 61 72; Components: WndTabs

Root: HKU; Subkey: .DEFAULT\Software\WndTabs.com\WndTabs\3.2\Layout\BCGToolBar-59413; ValueType: string; ValueName: Name; Components: WndTabs
Root: HKU; Subkey: .DEFAULT\Software\WndTabs.com\WndTabs\3.2\Layout\BCGToolBar-59413; ValueType: binary; ValueName: Buttons; ValueData: 09 00 ff ff 01 00 11 00 43 42 43 47 54 6f 6f 6c 62 61 72 42 75 74 74 6f 6e 88 13 00 00 00 00 00 00 0b 00 00 00 16 53 68 6f 77 20 57 54 53 44 4b 5f 53 61 6d 70 20 44 69 61 6c 6f 67 01 00 00 00 00 00 00 00 00 00 00 00 01 00 00 00 01 80 8a 13 00 00 00 00 00 00 12 00 00 00 14 53 68 6f 77 20 43 6f 6d 6d 61 6e 64 20 43 6f 6e 74 65 78 74 01 00 00 00 00 00 00 00 00 00 00 00 01 00 00 00 01 80 8b 13 00 00 00 00 00 00 13 00 00 00 15 53 68 6f 77 20 46 69 6c 65 20 49 6e 66 6f 72 6d 61 74 69 6f 6e 01 00 00 00 00 00 00 00 00 00 00 00 01 00 00 00 01 80 8c 13 00 00 00 00 00 00 0b 00 00 00 16 53 68 6f 77 20 57 54 53 44 4b 5f 53 61 6d 70 20 44 69 61 6c 6f 67 01 00 00 00 00 00 00 00 00 00 00 00 01 00 00 00 01 80 8e 13 00 00 00 00 00 00 12 00 00 00 14 53 68 6f 77 20 43 6f 6d 6d 61 6e 64 20 43 6f 6e 74 65 78 74 01 00 00 00 00 00 00 00 00 00 00 00 01 00 00 00 01 80 8f 13 00 00 00 00 00 00 13 00 00 00 15 53 68 6f 77 20 46 69 6c 65 20 49 6e 66 6f 72 6d 61 74 69 6f 6e 01 00 00 00 00 00 00 00 00 00 00 00 01 00 00 00 01 80 90 13 00 00 00 00 00 00 0b 00 00 00 16 53 68 6f 77 20 57 54 53 44 4b 5f 53 61 6d 70 20 44 69 61 6c 6f 67 01 00 00 00 00 00 00 00 00 00 00 00 01 00 00 00 01 80 92 13 00 00 00 00 00 00 12 00 00 00 14 53 68 6f 77 20 43 6f 6d 6d 61 6e 64 20 43 6f 6e 74 65 78 74 01 00 00 00 00 00 00 00 00 00 00 00 01 00 00 00 01 80 93 13 00 00 00 00 00 00 13 00 00 00 15 53 68 6f 77 20 46 69 6c 65 20 49 6e 66 6f 72 6d 61 74 69 6f 6e 01 00 00 00 00 00 00 00 00 00 00 00 01 00 00 00 00 00 00 00 00; Components: WndTabs

Root: HKU; Subkey: .DEFAULT\Software\WndTabs.com\WndTabs\3.2\Layout\BCGToolbarParameters; ValueType: dword; ValueName: Tooltips; ValueData: $00000001; Components: WndTabs
Root: HKU; Subkey: .DEFAULT\Software\WndTabs.com\WndTabs\3.2\Layout\BCGToolbarParameters; ValueType: dword; ValueName: ShortcutKeys; ValueData: $00000001; Components: WndTabs
Root: HKU; Subkey: .DEFAULT\Software\WndTabs.com\WndTabs\3.2\Layout\BCGToolbarParameters; ValueType: dword; ValueName: LargeIcons; ValueData: $00000000; Components: WndTabs
Root: HKU; Subkey: .DEFAULT\Software\WndTabs.com\WndTabs\3.2\Layout\BCGToolbarParameters; ValueType: dword; ValueName: MenuAnimation; ValueData: $00000000; Components: WndTabs
Root: HKU; Subkey: .DEFAULT\Software\WndTabs.com\WndTabs\3.2\Layout\BCGToolbarParameters; ValueType: dword; ValueName: RecentlyUsedMenus; ValueData: $00000001; Components: WndTabs
Root: HKU; Subkey: .DEFAULT\Software\WndTabs.com\WndTabs\3.2\Layout\BCGToolbarParameters; ValueType: dword; ValueName: MenuShadows; ValueData: $00000001; Components: WndTabs
Root: HKU; Subkey: .DEFAULT\Software\WndTabs.com\WndTabs\3.2\Layout\BCGToolbarParameters; ValueType: dword; ValueName: ShowAllMenusAfterDelay; ValueData: $00000001; Components: WndTabs
Root: HKU; Subkey: .DEFAULT\Software\WndTabs.com\WndTabs\3.2\Layout\BCGToolbarParameters; ValueType: dword; ValueName: Look2000; ValueData: $00000000; Components: WndTabs
Root: HKU; Subkey: .DEFAULT\Software\WndTabs.com\WndTabs\3.2\Layout\BCGToolbarParameters; ValueType: binary; ValueName: CommandsUsage; ValueData: 02 00 00 00 01 00 e1 2e 00 00 02 00 00 00; Components: WndTabs

Root: HKU; Subkey: .DEFAULT\Software\WndTabs.com\WndTabs\3.2\Layout\ControlBars-Bar0; ValueType: dword; ValueName: BarID; ValueData: $0000e806; Components: WndTabs
Root: HKU; Subkey: .DEFAULT\Software\WndTabs.com\WndTabs\3.2\Layout\ControlBars-Bar0; ValueType: dword; ValueName: XPos; ValueData: $00000000; Components: WndTabs
Root: HKU; Subkey: .DEFAULT\Software\WndTabs.com\WndTabs\3.2\Layout\ControlBars-Bar0; ValueType: dword; ValueName: YPos; ValueData: $fffffffe; Components: WndTabs
Root: HKU; Subkey: .DEFAULT\Software\WndTabs.com\WndTabs\3.2\Layout\ControlBars-Bar0; ValueType: dword; ValueName: Docking; ValueData: $00000001; Components: WndTabs
Root: HKU; Subkey: .DEFAULT\Software\WndTabs.com\WndTabs\3.2\Layout\ControlBars-Bar0; ValueType: dword; ValueName: MRUDockID; ValueData: $00000000; Components: WndTabs
Root: HKU; Subkey: .DEFAULT\Software\WndTabs.com\WndTabs\3.2\Layout\ControlBars-Bar0; ValueType: dword; ValueName: MRUDockLeftPos; ValueData: $00000000; Components: WndTabs
Root: HKU; Subkey: .DEFAULT\Software\WndTabs.com\WndTabs\3.2\Layout\ControlBars-Bar0; ValueType: dword; ValueName: MRUDockTopPos; ValueData: $fffffffe; Components: WndTabs
Root: HKU; Subkey: .DEFAULT\Software\WndTabs.com\WndTabs\3.2\Layout\ControlBars-Bar0; ValueType: dword; ValueName: MRUDockRightPos; ValueData: $0000002c; Components: WndTabs
Root: HKU; Subkey: .DEFAULT\Software\WndTabs.com\WndTabs\3.2\Layout\ControlBars-Bar0; ValueType: dword; ValueName: MRUDockBottomPos; ValueData: $0000001a; Components: WndTabs
Root: HKU; Subkey: .DEFAULT\Software\WndTabs.com\WndTabs\3.2\Layout\ControlBars-Bar0; ValueType: dword; ValueName: MRUFloatStyle; ValueData: $00002004; Components: WndTabs
Root: HKU; Subkey: .DEFAULT\Software\WndTabs.com\WndTabs\3.2\Layout\ControlBars-Bar0; ValueType: dword; ValueName: MRUFloatXPos; ValueData: $80000000; Components: WndTabs
Root: HKU; Subkey: .DEFAULT\Software\WndTabs.com\WndTabs\3.2\Layout\ControlBars-Bar0; ValueType: dword; ValueName: MRUFloatYPos; ValueData: $00000000; Components: WndTabs

Root: HKU; Subkey: .DEFAULT\Software\WndTabs.com\WndTabs\3.2\Layout\ControlBars-Bar1; ValueType: dword; ValueName: BarID; ValueData: $0000e815; Components: WndTabs
Root: HKU; Subkey: .DEFAULT\Software\WndTabs.com\WndTabs\3.2\Layout\ControlBars-Bar1; ValueType: dword; ValueName: Visible; ValueData: $00000000; Components: WndTabs
Root: HKU; Subkey: .DEFAULT\Software\WndTabs.com\WndTabs\3.2\Layout\ControlBars-Bar1; ValueType: dword; ValueName: XPos; ValueData: $fffffffe; Components: WndTabs
Root: HKU; Subkey: .DEFAULT\Software\WndTabs.com\WndTabs\3.2\Layout\ControlBars-Bar1; ValueType: dword; ValueName: YPos; ValueData: $fffffffe; Components: WndTabs
Root: HKU; Subkey: .DEFAULT\Software\WndTabs.com\WndTabs\3.2\Layout\ControlBars-Bar1; ValueType: dword; ValueName: Docking; ValueData: $00000001; Components: WndTabs
Root: HKU; Subkey: .DEFAULT\Software\WndTabs.com\WndTabs\3.2\Layout\ControlBars-Bar1; ValueType: dword; ValueName: MRUDockID; ValueData: $00000000; Components: WndTabs
Root: HKU; Subkey: .DEFAULT\Software\WndTabs.com\WndTabs\3.2\Layout\ControlBars-Bar1; ValueType: dword; ValueName: MRUDockLeftPos; ValueData: $00000000; Components: WndTabs
Root: HKU; Subkey: .DEFAULT\Software\WndTabs.com\WndTabs\3.2\Layout\ControlBars-Bar1; ValueType: dword; ValueName: MRUDockTopPos; ValueData: $00000000; Components: WndTabs
Root: HKU; Subkey: .DEFAULT\Software\WndTabs.com\WndTabs\3.2\Layout\ControlBars-Bar1; ValueType: dword; ValueName: MRUDockRightPos; ValueData: $00000000; Components: WndTabs
Root: HKU; Subkey: .DEFAULT\Software\WndTabs.com\WndTabs\3.2\Layout\ControlBars-Bar1; ValueType: dword; ValueName: MRUDockBottomPos; ValueData: $00000000; Components: WndTabs
Root: HKU; Subkey: .DEFAULT\Software\WndTabs.com\WndTabs\3.2\Layout\ControlBars-Bar1; ValueType: dword; ValueName: MRUFloatStyle; ValueData: $00002000; Components: WndTabs
Root: HKU; Subkey: .DEFAULT\Software\WndTabs.com\WndTabs\3.2\Layout\ControlBars-Bar1; ValueType: dword; ValueName: MRUFloatXPos; ValueData: $80000000; Components: WndTabs
Root: HKU; Subkey: .DEFAULT\Software\WndTabs.com\WndTabs\3.2\Layout\ControlBars-Bar1; ValueType: dword; ValueName: MRUFloatYPos; ValueData: $00000000; Components: WndTabs

Root: HKU; Subkey: .DEFAULT\Software\WndTabs.com\WndTabs\3.2\Layout\ControlBars-Bar2; ValueType: dword; ValueName: BarID; ValueData: $0000e81b; Components: WndTabs
Root: HKU; Subkey: .DEFAULT\Software\WndTabs.com\WndTabs\3.2\Layout\ControlBars-Bar2; ValueType: dword; ValueName: Bars; ValueData: $00000003; Components: WndTabs
Root: HKU; Subkey: .DEFAULT\Software\WndTabs.com\WndTabs\3.2\Layout\ControlBars-Bar2; ValueType: dword; ValueName: Bar#0; ValueData: $00000000; Components: WndTabs
Root: HKU; Subkey: .DEFAULT\Software\WndTabs.com\WndTabs\3.2\Layout\ControlBars-Bar2; ValueType: dword; ValueName: Bar#1; ValueData: $0000e806; Components: WndTabs
Root: HKU; Subkey: .DEFAULT\Software\WndTabs.com\WndTabs\3.2\Layout\ControlBars-Bar2; ValueType: dword; ValueName: Bar#2; ValueData: $00000000; Components: WndTabs

Root: HKU; Subkey: .DEFAULT\Software\WndTabs.com\WndTabs\3.2\Layout\ControlBars-Bar3; ValueType: dword; ValueName: BarID; ValueData: $0000e81e; Components: WndTabs
Root: HKU; Subkey: .DEFAULT\Software\WndTabs.com\WndTabs\3.2\Layout\ControlBars-Bar3; ValueType: dword; ValueName: Bars; ValueData: $00000003; Components: WndTabs
Root: HKU; Subkey: .DEFAULT\Software\WndTabs.com\WndTabs\3.2\Layout\ControlBars-Bar3; ValueType: dword; ValueName: Bar#0; ValueData: $00000000; Components: WndTabs
Root: HKU; Subkey: .DEFAULT\Software\WndTabs.com\WndTabs\3.2\Layout\ControlBars-Bar3; ValueType: dword; ValueName: Bar#1; ValueData: $0000e815; Components: WndTabs
Root: HKU; Subkey: .DEFAULT\Software\WndTabs.com\WndTabs\3.2\Layout\ControlBars-Bar3; ValueType: dword; ValueName: Bar#2; ValueData: $00000000; Components: WndTabs

Root: HKU; Subkey: .DEFAULT\Software\WndTabs.com\WndTabs\3.2\Layout\ControlBars-Summary; ValueType: dword; ValueName: Bars; ValueData: $00000004; Components: WndTabs
Root: HKU; Subkey: .DEFAULT\Software\WndTabs.com\WndTabs\3.2\Layout\ControlBars-Summary; ValueType: dword; ValueName: ScreenCX; ValueData: $00000500; Components: WndTabs
Root: HKU; Subkey: .DEFAULT\Software\WndTabs.com\WndTabs\3.2\Layout\ControlBars-Summary; ValueType: dword; ValueName: ScreenCY; ValueData: $00000400; Components: WndTabs

Root: HKU; Subkey: .DEFAULT\Software\WndTabs.com\WndTabs\3.2\Layout\UserImages; ValueType: binary; ValueData: 

Root: HKU; Subkey: .DEFAULT\Software\WndTabs.com\WndTabs\3.2\Layout\WindowPlacement; ValueType: binary; ValueName: MainWindowRect; ValueData: 00 00 00 00 fe ff ff ff 2c 00 00 00 19 00 00 00; Components: WndTabs
Root: HKU; Subkey: .DEFAULT\Software\WndTabs.com\WndTabs\3.2\Layout\WindowPlacement; ValueType: dword; ValueName: Flags; ValueData: $00000000; Components: WndTabs
Root: HKU; Subkey: .DEFAULT\Software\WndTabs.com\WndTabs\3.2\Layout\WindowPlacement; ValueType: dword; ValueName: ShowCmd; ValueData: $00000001; Components: WndTabs

Root: HKU; Subkey: .DEFAULT\Software\WndTabs.com\WndTabs\3.2\Options; ValueType: dword; ValueName: DoWizAtStartup; ValueData: $00000000; Components: WndTabs
Root: HKU; Subkey: .DEFAULT\Software\WndTabs.com\WndTabs\3.2\Options; ValueType: dword; ValueName: UseWWhiz; ValueData: $00000000; Components: WndTabs
Root: HKU; Subkey: .DEFAULT\Software\WndTabs.com\WndTabs\3.2\Options; ValueType: dword; ValueName: ShowAttribsTT; ValueData: $00000001; Components: WndTabs
Root: HKU; Subkey: .DEFAULT\Software\WndTabs.com\WndTabs\3.2\Options; ValueType: dword; ValueName: UseVA_RTF; ValueData: $00000000; Components: WndTabs
Root: HKU; Subkey: .DEFAULT\Software\WndTabs.com\WndTabs\3.2\Options; ValueType: dword; ValueName: MenuArrows; ValueData: $00000001; Components: WndTabs
Root: HKU; Subkey: .DEFAULT\Software\WndTabs.com\WndTabs\3.2\Options; ValueType: dword; ValueName: ReBarWidth; ValueData: $00000030; Components: WndTabs
Root: HKU; Subkey: .DEFAULT\Software\WndTabs.com\WndTabs\3.2\Options; ValueType: dword; ValueName: VerCheckLastDate; ValueData: $00000000; Components: WndTabs
Root: HKU; Subkey: .DEFAULT\Software\WndTabs.com\WndTabs\3.2\Options; ValueType: dword; ValueName: LastOptionTreeSel; ValueData: $0000000f; Components: WndTabs
Root: HKU; Subkey: .DEFAULT\Software\WndTabs.com\WndTabs\3.2\Options; ValueType: dword; ValueName: AutoRefresh; ValueData: $00000000; Components: WndTabs
Root: HKU; Subkey: .DEFAULT\Software\WndTabs.com\WndTabs\3.2\Options; ValueType: dword; ValueName: FixedRowCount; ValueData: $00000000; Components: WndTabs
Root: HKU; Subkey: .DEFAULT\Software\WndTabs.com\WndTabs\3.2\Options; ValueType: dword; ValueName: Orientation; ValueData: $00000001; Components: WndTabs
Root: HKU; Subkey: .DEFAULT\Software\WndTabs.com\WndTabs\3.2\Options; ValueType: dword; ValueName: Snap; ValueData: $00000000; Components: WndTabs
Root: HKU; Subkey: .DEFAULT\Software\WndTabs.com\WndTabs\3.2\Options; ValueType: dword; ValueName: TabRows; ValueData: $00000001; Components: WndTabs
Root: HKU; Subkey: .DEFAULT\Software\WndTabs.com\WndTabs\3.2\Options; ValueType: dword; ValueName: NoRaggedRight; ValueData: $00000000; Components: WndTabs
Root: HKU; Subkey: .DEFAULT\Software\WndTabs.com\WndTabs\3.2\Options; ValueType: dword; ValueName: RefreshInterval; ValueData: $00000032; Components: WndTabs
Root: HKU; Subkey: .DEFAULT\Software\WndTabs.com\WndTabs\3.2\Options; ValueType: dword; ValueName: DispRC; ValueData: $00000001; Components: WndTabs
Root: HKU; Subkey: .DEFAULT\Software\WndTabs.com\WndTabs\3.2\Options; ValueType: dword; ValueName: DispRID; ValueData: $00000001; Components: WndTabs
Root: HKU; Subkey: .DEFAULT\Software\WndTabs.com\WndTabs\3.2\Options; ValueType: dword; ValueName: DispResLang; ValueData: $00000001; Components: WndTabs
Root: HKU; Subkey: .DEFAULT\Software\WndTabs.com\WndTabs\3.2\Options; ValueType: dword; ValueName: DispResType; ValueData: $00000001; Components: WndTabs
Root: HKU; Subkey: .DEFAULT\Software\WndTabs.com\WndTabs\3.2\Options; ValueType: dword; ValueName: ShowIcons; ValueData: $00000001; Components: WndTabs
Root: HKU; Subkey: .DEFAULT\Software\WndTabs.com\WndTabs\3.2\Options; ValueType: dword; ValueName: ShowNumbers; ValueData: $00000001; Components: WndTabs
Root: HKU; Subkey: .DEFAULT\Software\WndTabs.com\WndTabs\3.2\Options; ValueType: dword; ValueName: StripExt; ValueData: $00000000; Components: WndTabs
Root: HKU; Subkey: .DEFAULT\Software\WndTabs.com\WndTabs\3.2\Options; ValueType: dword; ValueName: StripPath; ValueData: $00000001; Components: WndTabs
Root: HKU; Subkey: .DEFAULT\Software\WndTabs.com\WndTabs\3.2\Options; ValueType: dword; ValueName: FontType; ValueData: $00000001; Components: WndTabs
Root: HKU; Subkey: .DEFAULT\Software\WndTabs.com\WndTabs\3.2\Options; ValueType: dword; ValueName: ButtonTabs; ValueData: $00000000; Components: WndTabs
Root: HKU; Subkey: .DEFAULT\Software\WndTabs.com\WndTabs\3.2\Options; ValueType: dword; ValueName: TabOrdering; ValueData: $00000001; Components: WndTabs
Root: HKU; Subkey: .DEFAULT\Software\WndTabs.com\WndTabs\3.2\Options; ValueType: dword; ValueName: Fill1To9; ValueData: $00000001; Components: WndTabs
Root: HKU; Subkey: .DEFAULT\Software\WndTabs.com\WndTabs\3.2\Options; ValueType: dword; ValueName: PreserveNumbering; ValueData: $00000001; Components: WndTabs
Root: HKU; Subkey: .DEFAULT\Software\WndTabs.com\WndTabs\3.2\Options; ValueType: dword; ValueName: SaveTabNumbers; ValueData: $00000001; Components: WndTabs
Root: HKU; Subkey: .DEFAULT\Software\WndTabs.com\WndTabs\3.2\Options; ValueType: dword; ValueName: CharLimit; ValueData: $00000008; Components: WndTabs
Root: HKU; Subkey: .DEFAULT\Software\WndTabs.com\WndTabs\3.2\Options; ValueType: dword; ValueName: LimitCharacter; ValueData: $000000a7; Components: WndTabs
Root: HKU; Subkey: .DEFAULT\Software\WndTabs.com\WndTabs\3.2\Options; ValueType: dword; ValueName: LimitChars; ValueData: $00000000; Components: WndTabs
Root: HKU; Subkey: .DEFAULT\Software\WndTabs.com\WndTabs\3.2\Options; ValueType: dword; ValueName: LimitIgnoreExt; ValueData: $00000001; Components: WndTabs
Root: HKU; Subkey: .DEFAULT\Software\WndTabs.com\WndTabs\3.2\Options; ValueType: dword; ValueName: LimitResChars; ValueData: $00000000; Components: WndTabs
Root: HKU; Subkey: .DEFAULT\Software\WndTabs.com\WndTabs\3.2\Options; ValueType: dword; ValueName: UseLimitChar; ValueData: $00000001; Components: WndTabs
Root: HKU; Subkey: .DEFAULT\Software\WndTabs.com\WndTabs\3.2\Options; ValueType: dword; ValueName: TrimPrefixes; ValueData: $00000000; Components: WndTabs
Root: HKU; Subkey: .DEFAULT\Software\WndTabs.com\WndTabs\3.2\Options; ValueType: dword; ValueName: TrimSuffixes; ValueData: $00000000; Components: WndTabs
Root: HKU; Subkey: .DEFAULT\Software\WndTabs.com\WndTabs\3.2\Options; ValueType: dword; ValueName: UseTrimPrefixChar; ValueData: $00000001; Components: WndTabs
Root: HKU; Subkey: .DEFAULT\Software\WndTabs.com\WndTabs\3.2\Options; ValueType: dword; ValueName: UseTrimSuffixChar; ValueData: $00000001; Components: WndTabs
Root: HKU; Subkey: .DEFAULT\Software\WndTabs.com\WndTabs\3.2\Options; ValueType: dword; ValueName: TrimPrefixChar; ValueData: $000000bb; Components: WndTabs
Root: HKU; Subkey: .DEFAULT\Software\WndTabs.com\WndTabs\3.2\Options; ValueType: dword; ValueName: TrimSuffixChar; ValueData: $000000ab; Components: WndTabs
Root: HKU; Subkey: .DEFAULT\Software\WndTabs.com\WndTabs\3.2\Options; ValueType: dword; ValueName: UseWindowLimit; ValueData: $00000000; Components: WndTabs
Root: HKU; Subkey: .DEFAULT\Software\WndTabs.com\WndTabs\3.2\Options; ValueType: dword; ValueName: UseWindowLimitDbg; ValueData: $00000000; Components: WndTabs
Root: HKU; Subkey: .DEFAULT\Software\WndTabs.com\WndTabs\3.2\Options; ValueType: dword; ValueName: WindowLimit; ValueData: $0000000a; Components: WndTabs
Root: HKU; Subkey: .DEFAULT\Software\WndTabs.com\WndTabs\3.2\Options; ValueType: dword; ValueName: WindowLimitDbg; ValueData: $0000000a; Components: WndTabs
Root: HKU; Subkey: .DEFAULT\Software\WndTabs.com\WndTabs\3.2\Options; ValueType: dword; ValueName: LimitGroups; ValueData: $00000000; Components: WndTabs
Root: HKU; Subkey: .DEFAULT\Software\WndTabs.com\WndTabs\3.2\Options; ValueType: dword; ValueName: AutoCloseDbgWins; ValueData: $00000000; Components: WndTabs
Root: HKU; Subkey: .DEFAULT\Software\WndTabs.com\WndTabs\3.2\Options; ValueType: dword; ValueName: OpenFolderUseExplore; ValueData: $00000000; Components: WndTabs
Root: HKU; Subkey: .DEFAULT\Software\WndTabs.com\WndTabs\3.2\Options; ValueType: dword; ValueName: AutoOpenAlt; ValueData: $00000001; Components: WndTabs
Root: HKU; Subkey: .DEFAULT\Software\WndTabs.com\WndTabs\3.2\Options; ValueType: dword; ValueName: ShowAddonWTXInfo; ValueData: $00000000; Components: WndTabs
Root: HKU; Subkey: .DEFAULT\Software\WndTabs.com\WndTabs\3.2\Options; ValueType: dword; ValueName: ShowMultiUseReg; ValueData: $00000001; Components: WndTabs
Root: HKU; Subkey: .DEFAULT\Software\WndTabs.com\WndTabs\3.2\Options; ValueType: dword; ValueName: ShowKeyBindingsWarn; ValueData: $00000001; Components: WndTabs
Root: HKU; Subkey: .DEFAULT\Software\WndTabs.com\WndTabs\3.2\Options; ValueType: dword; ValueName: ShowWWhizFlipWarn; ValueData: $00000001; Components: WndTabs
Root: HKU; Subkey: .DEFAULT\Software\WndTabs.com\WndTabs\3.2\Options; ValueType: dword; ValueName: ShowUnsubclassErr; ValueData: $00000001; Components: WndTabs
Root: HKU; Subkey: .DEFAULT\Software\WndTabs.com\WndTabs\3.2\Options; ValueType: dword; ValueName: CascadingAddons; ValueData: $00000001; Components: WndTabs
Root: HKU; Subkey: .DEFAULT\Software\WndTabs.com\WndTabs\3.2\Options; ValueType: dword; ValueName: SupressNoCmdAddons; ValueData: $00000000; Components: WndTabs
Root: HKU; Subkey: .DEFAULT\Software\WndTabs.com\WndTabs\3.2\Options; ValueType: dword; ValueName: ShellKey; ValueData: $00000010; Components: WndTabs
Root: HKU; Subkey: .DEFAULT\Software\WndTabs.com\WndTabs\3.2\Options; ValueType: dword; ValueName: MenuClip; ValueData: $00000002; Components: WndTabs
Root: HKU; Subkey: .DEFAULT\Software\WndTabs.com\WndTabs\3.2\Options; ValueType: dword; ValueName: MenuDS; ValueData: $00000002; Components: WndTabs
Root: HKU; Subkey: .DEFAULT\Software\WndTabs.com\WndTabs\3.2\Options; ValueType: dword; ValueName: MenuFileMan; ValueData: $00000002; Components: WndTabs
Root: HKU; Subkey: .DEFAULT\Software\WndTabs.com\WndTabs\3.2\Options; ValueType: dword; ValueName: MenuWinMan; ValueData: $00000002; Components: WndTabs
Root: HKU; Subkey: .DEFAULT\Software\WndTabs.com\WndTabs\3.2\Options; ValueType: dword; ValueName: ModGoToTab; ValueData: $00000002; Components: WndTabs
Root: HKU; Subkey: .DEFAULT\Software\WndTabs.com\WndTabs\3.2\Options; ValueType: dword; ValueName: VKsGoToTab; ValueData: $00000000; Components: WndTabs
Root: HKU; Subkey: .DEFAULT\Software\WndTabs.com\WndTabs\3.2\Options; ValueType: dword; ValueName: InetKbdStopBuilds; ValueData: $00000001; Components: WndTabs
Root: HKU; Subkey: .DEFAULT\Software\WndTabs.com\WndTabs\3.2\Options; ValueType: dword; ValueName: InetKbdBackForward; ValueData: $00000003; Components: WndTabs
Root: HKU; Subkey: .DEFAULT\Software\WndTabs.com\WndTabs\3.2\Options; ValueType: dword; ValueName: MidBtnCommand; ValueData: $00002a13; Components: WndTabs
Root: HKU; Subkey: .DEFAULT\Software\WndTabs.com\WndTabs\3.2\Options; ValueType: dword; ValueName: WndTabsExtInUse; ValueData: $00000001; Components: WndTabs
Root: HKU; Subkey: .DEFAULT\Software\WndTabs.com\WndTabs\3.2\Options; ValueType: dword; ValueName: DisableSplash; ValueData: $00000001; Components: WndTabs
Root: HKU; Subkey: .DEFAULT\Software\WndTabs.com\WndTabs\3.2\Options; ValueType: dword; ValueName: UseWTTabCtrl; ValueData: $00000001; Components: WndTabs
Root: HKU; Subkey: .DEFAULT\Software\WndTabs.com\WndTabs\3.2\Options; ValueType: dword; ValueName: WTXAllSpecial; ValueData: $00000000; Components: WndTabs
Root: HKU; Subkey: .DEFAULT\Software\WndTabs.com\WndTabs\3.2\Options; ValueType: dword; ValueName: WTXCloseButton; ValueData: $00000001; Components: WndTabs
Root: HKU; Subkey: .DEFAULT\Software\WndTabs.com\WndTabs\3.2\Options; ValueType: dword; ValueName: GroupTabs; ValueData: $00000001; Components: WndTabs
Root: HKU; Subkey: .DEFAULT\Software\WndTabs.com\WndTabs\3.2\Options; ValueType: dword; ValueName: GroupDiffPaths; ValueData: $00000001; Components: WndTabs
Root: HKU; Subkey: .DEFAULT\Software\WndTabs.com\WndTabs\3.2\Options; ValueType: dword; ValueName: GroupRes; ValueData: $00000000; Components: WndTabs
Root: HKU; Subkey: .DEFAULT\Software\WndTabs.com\WndTabs\3.2\Options; ValueType: dword; ValueName: GroupPrj; ValueData: $00000000; Components: WndTabs
Root: HKU; Subkey: .DEFAULT\Software\WndTabs.com\WndTabs\3.2\Options; ValueType: dword; ValueName: ShowGroupDelim; ValueData: $00000001; Components: WndTabs
Root: HKU; Subkey: .DEFAULT\Software\WndTabs.com\WndTabs\3.2\Options; ValueType: dword; ValueName: SortMiniTB; ValueData: $00000001; Components: WndTabs
Root: HKU; Subkey: .DEFAULT\Software\WndTabs.com\WndTabs\3.2\Options; ValueType: dword; ValueName: UseGroupOps; ValueData: $00000001; Components: WndTabs
Root: HKU; Subkey: .DEFAULT\Software\WndTabs.com\WndTabs\3.2\Options; ValueType: dword; ValueName: UseRightMostDot; ValueData: $00000001; Components: WndTabs
Root: HKU; Subkey: .DEFAULT\Software\WndTabs.com\WndTabs\3.2\Options; ValueType: dword; ValueName: RegTxtColor; ValueData: $00000000; Components: WndTabs
Root: HKU; Subkey: .DEFAULT\Software\WndTabs.com\WndTabs\3.2\Options; ValueType: dword; ValueName: SelTxtColor; ValueData: $00ff0000; Components: WndTabs
Root: HKU; Subkey: .DEFAULT\Software\WndTabs.com\WndTabs\3.2\Options; ValueType: string; ValueName: VerCheckLast; Components: WndTabs
Root: HKU; Subkey: .DEFAULT\Software\WndTabs.com\WndTabs\3.2\Options; ValueType: string; ValueName: OptionsDlgTree; ValueData: 1000000010000000; Components: WndTabs
Root: HKU; Subkey: .DEFAULT\Software\WndTabs.com\WndTabs\3.2\Options; ValueType: string; ValueName: TrimablePrefixes; Components: WndTabs
Root: HKU; Subkey: .DEFAULT\Software\WndTabs.com\WndTabs\3.2\Options; ValueType: string; ValueName: TrimableSuffixes; Components: WndTabs
Root: HKU; Subkey: .DEFAULT\Software\WndTabs.com\WndTabs\3.2\Options; ValueType: string; ValueName: AutoCloseDirsDbg; ValueData: "$(DS_INCLUDE);$(DS_SOURCE)"; Components: WndTabs
Root: HKU; Subkey: .DEFAULT\Software\WndTabs.com\WndTabs\3.2\Options; ValueType: string; ValueName: LangDll; ValueData: wndtabslangfrench.dll; Components: WndTabs

Root: HKU; Subkey: .DEFAULT\Software\WndTabs.com\WTSDK_Samp; ValueType: dword; ValueName: ForceAddToolbar; ValueData: $00000000; Components: WndTabs
Root: HKU; Subkey: .DEFAULT\Software\WndTabs.com\WTSDK_Samp; ValueType: dword; ValueName: Enabled; ValueData: $00000001; Components: WndTabs
Root: HKU; Subkey: .DEFAULT\Software\WndTabs.com\WTSDK_Samp; ValueType: dword; ValueName: UseAltIcon; ValueData: $00000001; Components: WndTabs
Root: HKU; Subkey: .DEFAULT\Software\WndTabs.com\WTSDK_Samp; ValueType: dword; ValueName: UseCXXExt; ValueData: $00000000; Components: WndTabs
Root: HKU; Subkey: .DEFAULT\Software\WndTabs.com\WTSDK_Samp; ValueType: dword; ValueName: RedBackground; ValueData: $00000000; Components: WndTabs
Root: HKU; Subkey: .DEFAULT\Software\WndTabs.com\WTSDK_Samp; ValueType: dword; ValueName: ShowStar; ValueData: $00000001; Components: WndTabs
Root: HKU; Subkey: .DEFAULT\Software\WndTabs.com\WTSDK_Samp; ValueType: dword; ValueName: RedBorder; ValueData: $00000001; Components: WndTabs
Root: HKU; Subkey: .DEFAULT\Software\WndTabs.com\WTSDK_Samp; ValueType: dword; ValueName: CPPText; ValueData: $00000000; Components: WndTabs
Root: HKU; Subkey: .DEFAULT\Software\WndTabs.com\WTSDK_Samp; ValueType: dword; ValueName: ROText; ValueData: $00000000; Components: WndTabs
#endif

// Page 38: 
[Run]
#ifdef USE_MODIFYREPAIRDELETE
Filename: {pf}\{#VISUAL_FIRM}\Setup\{#VISUAL_SHORT} {#VISUAL_TYPE} {#VISUAL_VER}{#VISUAL_REV}\UninsHs.exe; Parameters: /r; Flags: runminimized
#endif
Filename: {app}\Common\MSDev98\Bin\MSDEV.EXE; Description: {cm:LaunchProgram,{#VISUAL_SHORT} {#VISUAL_TYPE} {#VISUAL_VER}.{#VISUAL_REV}}; Flags: nowait postinstall skipifsilent

// Page 38=: 
;[UninstallRun]

// Page 41: 
[UninstallDelete]
#ifdef USE_MODIFYREPAIRDELETE
Type: filesandordirs; Name: {pf}\{#VISUAL_FIRM}\Setup\{#VISUAL_SHORT} {#VISUAL_TYPE} {#VISUAL_VER}{#VISUAL_REV}\UninsHs.dat
#endif

; La section [Code] est à la fin et dans un fichier externe pour reprendre la structure de mon script InstallShield
// === CODE : SETUPVISUAL =============================================================================================

#include VISUAL_TOOLS+"\Setup"+VISUAL_SHORT+".isi"

// === INCLUDE ISSI ===================================================================================================: 

#include ISSI_IncludePath+"\_issi.isi"

// Putain qu'est ce que c'est bien InnoSetup, mais comment ais-je pu m'en passer aussi longtemps ?: 
