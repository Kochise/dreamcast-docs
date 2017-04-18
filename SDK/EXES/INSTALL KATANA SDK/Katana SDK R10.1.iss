; TYPE    DU SCRIPT : SEGA KATANA
; AUTEUR  DU SCRIPT : Kochise
; VERSION DU SCRIPT : 2008/05/24

; Voici l'avant dernier SDK officiel pour DreamCast
; repackagé par mes soins avec une installation 'perso'.
; La dernière version R11 n'a jamais étée 'rendue'
; publique mais n'apporte rien de significatif à ce que
; j'ai entendu. De toute façon des jeux commerciaux ont
; étés réalisés avec succès avec des versions antérieures
; à ce SDK, donc on s'en contentera.
; Je n'ai pas vérifié les dépendances puisqu'il faut en
; principe CodeWarrior d'installé pour utiliser Katana,
; aussi j'utilise plutôt les fichiers contenus dans ce
; SDK avec les compilateurs GNU que l'on trouve en général
; dans les distros homebrew (DC_Dev par exemple). Sur le
; DVD devrais se trouver un fichier PLATFORM.ZIP qui
; contient tous les derniers cross-compîlers SH4 et ARM7
; ainsi qu'un fichier de configuration pour DevCpp 4.9.9.2.
; Il faut un cable série pour DreamCast et graver l'ISO
; Dc-Load 1.0.4 livré (qui marche, ce n'est pas le cas
; de toutes les images présentent sur l'InterNet) et de
; compiler les exemples fournis.

; === DEFINE KATANA ====================================================================================================
; Bon, principalement les chemins des fichiers sources

; - - 8< - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

; JUST EDIT THIS PLACE FROM ONE SDK REVISION TO ANOTHER

#define SETUP_VERSION  "2.8.5.24"

#define KATANA_FIRM    "Sega of America"
#define KATANA_NAME    "Katana Development Software"
#define KATANA_SHORT   "Katana"
#define KATANA_TYPE    "SDK"
#define KATANA_VER     "R10"
#define KATANA_REV     "1"
#define KATANA_DATE    "000518"
;#define KATANA_DEBUG

; - - 8< - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

#define KATANA_INSTALL "."
#define KATANA_FILES   KATANA_INSTALL+"\INPUT\"+KATANA_VER+"."+KATANA_REV+"_"+KATANA_DATE
#define KATANA_TOOLS   KATANA_INSTALL+"\TOOLS"
#define KATANA_SPLASH  KATANA_TOOLS+"\Splash"
#define KATANA_TEXT    KATANA_TOOLS+"\Text"

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
AppName={#KATANA_NAME}
AppVerName={#KATANA_NAME} {#KATANA_VER}.{#KATANA_REV}
AppId={#KATANA_NAME}
// 53=
;;AppMutex=
AppCopyright=Copyright (c) {#KATANA_FIRM} 2000
AppComments=Europe's Developer Technical Support : +(44) (0) 181-996-4421
AppContact=edts@soepd.sega.co.uk
AppPublisher={#KATANA_FIRM}
AppPublisherURL=http://www.dts.sega.com/
AppSupportURL=http://www.dts.sega.com/NextGen/
AppUpdatesURL=http://www.dts.sega.com/NextGen/
AppVersion={#KATANA_VER}.{#KATANA_REV}
// Page 54=
DefaultDirName={reg:HKLM\SOFTWARE\{#KATANA_FIRM}\{#KATANA_NAME},Path|{sd}\KATANA}
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
OutputBaseFilename=setup_{#KATANA_SHORT}_{#KATANA_TYPE}_{#KATANA_VER}{#KATANA_REV}
UninstallFilesDir={pf}\{#KATANA_FIRM}\Setup\{#KATANA_SHORT} {#KATANA_TYPE} {#KATANA_VER}{#KATANA_REV}
// Page 60=
UninstallDisplayIcon={uninstallexe},0
;;UninstallDisplayName=
;;;UninstallIconName=
;UninstallLogMode=append
;UninstallRestartComputer=no
// Page 61=
;UpdateUninstallLogAppName=yes
DefaultGroupName={#KATANA_FIRM}\{#KATANA_NAME}
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
;;LicenseFile={#KATANA_FILES}\Legal.txt
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
WizardImageFile={#KATANA_SPLASH}\BannerLeft{#KATANA_SHORT}.bmp
;WindowShowCaption=yes
WindowStartMaximized=no
;WindowResizable=yes
// Page 68=
;WindowVisible=no
;WizardImageBackColor=$400000
;WizardImageStretch=yes
;WizardSmallImageBackColor=clWhite
;;SourceDir=
OutputDir=OUTPUT\{#KATANA_SHORT} {#KATANA_TYPE} {#KATANA_VER}.{#KATANA_REV}
// Page 70=
;;;WizardStyle=modern
;UninstallStyle=modern
;;WizardSmallImageFile={#RESEAU_SPLASH}\BannerTopReseauSmall.bmp
AlwaysShowComponentsList=no
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
SetupIconFile={#KATANA_SPLASH}\{#KATANA_SHORT}Eu.ico
;;VersionInfoCompany=
;;VersionInfoDescription=
;;VersionInfoTextVersion=
// Page 73=
VersionInfoVersion={#SETUP_VERSION}
;;;UninstallIconFile={#KATANA_SPLASH}\Trash.ico
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

;#define ISSI_ScriptBackup     "Sega "+KATANA_SHORT+" "+KATANA_TYPE+" "+KATANA_VER+"."+KATANA_REV+".iss"
;#define ISSI_ScriptBackup_Key "restorescriptbackup"

#define ISSI_UPDATE            KATANA_NAME
#define ISSI_UpdateOrInstall
#define ISSI_UpdateTitle       KATANA_NAME
#define ISSI_UpdateAppVersion  KATANA_VER+"."+KATANA_REV

#define ISSI_LicensePrint

;#define ISSI_ScreenSaver "myScreensaver.scr"

; --- APPEARANCE ------------------------------------------------------------------------------------------------------

;#define ISSI_WizardImages

#define ISSI_BeveledApp

;#define ISSI_Image "splash.bmp"

#define ISSI_Splash   KATANA_SPLASH+"\setup.bmp"
#define ISSI_Splash_T 2
#define ISSI_Splash_X 224
#define ISSI_Splash_Y 184
;#define ISSI_Splash_CORNER 8

;#define ISSI_WizardBitmapImage "splash_495x314.bmp"
;#define ISSI_WizardBitmapImage_x 495
;#define ISSI_WizardBitmapImage2 "albartus_com.bmp"
;#define ISSI_WizardBitmapImage2_x 164

#define ISSI_WizardSmallBitmapImage   KATANA_SPLASH+"\BannerTop"+KATANA_SHORT+".bmp"
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

#define ISSI_IncludePath KATANA_TOOLS+"\ISSI"

; === DEFINE ISSI =====================================================================================================

// Page 13=
[Types]
Name: Typique; Description: {cm:KatanaTypesTypique}
Name: Minimal; Description: {cm:KatanaTypesMinimal}
Name: Custom; Description: {cm:KatanaTypesCustom}; Flags: iscustom

// Page 14: 
[Components]
Name: Documentation; Description: {cm:KatanaComponentsDocumentation}; Types: Typique Custom Minimal
Name: Documentation\DocumentationRoot; Description: {cm:KatanaComponentsDocumentationRoot}; Types: Typique Custom Minimal
Name: Utilities; Description: {cm:KatanaComponentsUtl}; Types: Typique Custom Minimal
Name: Utilities\UtlDevHitachi; Description: {cm:KatanaComponentsUtlDevHitachi}; Types: Typique Custom
Name: Utilities\UtlDevHitachi\UtlDevMake; Description: {cm:KatanaComponentsUtlDevMake}; Types: Typique Custom
Name: Utilities\UtlDevHitachi\UtlDevCodeWarrior; Description: {cm:KatanaComponentsUtlDevCodeWarrior}; Types: Typique Custom
Name: Utilities\UtlDevHitachi\UtlDevCodeWarrior\UtlDevCWDLLS; Description: {cm:KatanaComponentsUtlDevCWDLLS}; Types: Typique Custom
Name: Utilities\UtlDevHitachi\UtlDevCodeWarrior\CWDesktopIcon; Description: {cm:KatanaComponentsCWDesktopIcon}; Types: Typique Custom
Name: Utilities\UtlDevHitachi\UtlDevGnu; Description: {cm:KatanaComponentsUtlDevGnu}; Types: Typique Custom
Name: Utilities\UtlDevCodescape; Description: {cm:KatanaComponentsUtlDevCodescape}; Types: Typique Custom Minimal
Name: Utilities\UtlDevCodescape\utlDevPrfdump; Description: {cm:KatanaComponentsutlDevPrfdump}; Types: Typique Custom Minimal
Name: Utilities\UtlDevCodescape\UtlDevGDWorkshop; Description: {cm:KatanaComponentsUtlDevGDWorkshop}; Types: Typique Custom Minimal
Name: Utilities\UtlDevCodescape\UtlDevCDCraft; Description: {cm:KatanaComponentsUtlDevCDCraft}; Types: Typique Custom Minimal
Name: Utilities\UtlDevCodescape\UtlDevScripting; Description: {cm:KatanaComponentsUtlDevScripting}; Types: Typique Custom Minimal
Name: Utilities\UtlDevVMUTool; Description: {cm:KatanaComponentsUtlDevVMUTool}; Types: Typique Custom
Name: Utilities\UtlDevVMUTool\Registered; Description: {cm:KatanaComponentsRegistered}; Types: Typique Custom
Name: Utilities\UtlDevVMUTool\Shared; Description: {cm:KatanaComponentsShared}; Types: Typique Custom
Name: Utilities\UtlDevDACheck; Description: {cm:KatanaComponentsUtlDevDACheck}; Types: Typique Custom Minimal
Name: Utilities\UtlDevDACheck\UtlDevDBFlash; Description: {cm:KatanaComponentsUtlDevDBFlash}; Types: Typique Custom Minimal
Name: Utilities\UtlDevIPMaker; Description: {cm:KatanaComponentsUtlDevIPMaker}; Types: Typique Custom Minimal
Name: Utilities\UtlGfx; Description: {cm:KatanaComponentsUtlGfx}; Types: Typique Custom
Name: Utilities\UtlSnd; Description: {cm:KatanaComponentsUtlSnd}; Types: Typique Custom
Name: Utilities\LibAudio64; Description: {cm:KatanaComponentsLibAudio64}; Types: Typique Custom Minimal
Name: Utilities\LibAudio64\Lib; Description: {cm:KatanaComponentsLibAudio64Lib}; Types: Typique Custom Minimal
Name: Utilities\LibAudio64\Drv; Description: {cm:KatanaComponentsLibAudio64Drv}; Types: Typique Custom Minimal
Name: Utilities\utldevdainterface; Description: {cm:KatanaComponentsutldevdainterface}; Types: Typique Custom
Name: Utilities\CIM_UTL; Description: {cm:KatanaComponentsCIM_UTL}; Types: Typique Custom Minimal
//Name: DesktopIcons; Description: {cm:KatanaComponentsDesktopIcons}; Types: Typique Custom
Name: Libraries; Description: {cm:KatanaComponentsLibraries}; Types: Typique Custom Minimal
Name: Libraries\SetPathsBat; Description: {cm:KatanaComponentsSetPathsBat}; Types: Typique Custom Minimal
Name: Sample; Description: {cm:KatanaComponentsSample}; Types: Typique Custom
Name: Sample\SampleAudio64; Description: {cm:KatanaComponentsSampleAudio64}; Types: Typique Custom
Name: Sample\SampleStdio_stl; Description: {cm:KatanaComponentsSampleStdio_stl}; Types: Typique Custom
Name: Sample\SampleGdfs; Description: {cm:KatanaComponentsSampleGdfs}; Types: Typique Custom
Name: Sample\Samplekm2Demo; Description: {cm:KatanaComponentsSamplekm2Demo}; Types: Typique Custom
Name: Sample\SampleLibc; Description: {cm:KatanaComponentsSampleLibc}; Types: Typique Custom
Name: Sample\SampleMovie; Description: {cm:KatanaComponentsSampleMovie}; Types: Typique Custom
Name: Sample\SamplePeriph; Description: {cm:KatanaComponentsSamplePeriph}; Types: Typique Custom
Name: Sample\SampleSound; Description: {cm:KatanaComponentsSampleSound}; Types: Typique Custom
Name: Sample\SampleSys; Description: {cm:KatanaComponentsSampleSys}; Types: Typique Custom
Name: Sample\SampleGinsu; Description: {cm:KatanaComponentsSampleGinsu}; Types: Typique Custom
Name: Sample\SampleKamui2; Description: {cm:KatanaComponentsSampleKamui2}; Types: Typique Custom
Name: Sample\SampleNet; Description: {cm:KatanaComponentsSampleNet}; Types: Typique Custom
Name: Include; Description: {cm:KatanaComponentsInclude}; Types: Typique Custom
Name: RootDriver; Description: {cm:KatanaComponentsRootDriver}; Types: Typique Custom Minimal
Name: RootSubmission; Description: {cm:KatanaComponentsRootSubmission}; Types: Typique Custom Minimal
Name: Backup; Description: {cm:KatanaComponentsBackup}

// Page 16: 
[Tasks]
Name: desktopicon; Description: {cm:CreateDesktopIcon}; GroupDescription: {cm:AdditionalIcons}
Name: quicklaunchicon; Description: {cm:CreateQuickLaunchIcon}; GroupDescription: {cm:AdditionalIcons}; Flags: unchecked
Name: installaspi; Description: {cm:KatanaTasksInstallAspi}; GroupDescription: {cm:KatanaDescriptionHardware}
Name: flashdebug; Description: {cm:KatanaTasksFlashDebugger}; GroupDescription: {cm:KatanaDescriptionHardware}; Flags: unchecked
;Name: extractinstall; Description: {cm:KatanaTasksBackupInstall}; GroupDescription: {cm:KatanaDescriptionBackup}; Flags: unchecked

// Page 18: 
[Dirs]
Name: {app}; Permissions: everyone-modify

// Page 20: 
[Files]
; NOTE: Ne pas utiliser "Flags: ignoreversion" sur les fichier système partagés
; Doc (~ 155840 KiB)
#ifndef KATANA_DEBUG
Source: {#KATANA_FILES}\Doc\*; DestDir: {app}\Doc; Components: Documentation; Flags: recursesubdirs
#endif
Source: {#KATANA_FILES}\*; DestDir: {app}; Components: Documentation\DocumentationRoot
#ifndef KATANA_DEBUG
; Utilities (~ 287744 KiB)
Source: {#KATANA_FILES}\Utl\*; DestDir: {app}\Utl; Components: Utilities; Flags: skipifsourcedoesntexist
;     Compiler (~ 177746 KiB)
Source: {#KATANA_FILES}\Utl\Dev\Hitachi\*; DestDir: {app}\Utl\Dev\Hitachi; Components: Utilities\UtlDevHitachi; Flags: recursesubdirs
Source: {#KATANA_FILES}\Utl\Dev\Make\*; DestDir: {app}\Utl\Dev\Make; Components: Utilities\UtlDevHitachi\UtlDevMake; Flags: recursesubdirs
Source: {#KATANA_FILES}\Utl\Dev\CodeWarrior\*; DestDir: {app}\Utl\Dev\CodeWarrior; Components: Utilities\UtlDevHitachi\UtlDevCodeWarrior; Flags: recursesubdirs
Source: {#KATANA_FILES}\Utl\Dev\CodeWarrior\Bin\resource\regdll\*; DestDir: {sys}; Components: Utilities\UtlDevHitachi\UtlDevCodeWarrior\UtlDevCWDLLS; Flags: sharedfile uninsnosharedfileprompt
//Source: {#KATANA_FILES}\Utl\Dev\CodeWarrior\*; DestDir: {app}; Components: Utilities\UtlDevHitachi\UtlDevCodeWarrior\CWDesktopIcon
Source: {#KATANA_FILES}\Utl\Dev\Gnu\*; DestDir: {app}\Utl\Dev\Gnu; Components: Utilities\UtlDevHitachi\UtlDevGnu; Flags: recursesubdirs
;     Debugger (~ 31662 KiB)
Source: {#KATANA_FILES}\Utl\Dev\Codescape\*; DestDir: {app}\Utl\Dev\Codescape; Components: Utilities\UtlDevCodescape; Flags: recursesubdirs
Source: {#KATANA_FILES}\utl\Dev\PrfDump\*; DestDir: {app}\Utl\Dev\PrfDump; Components: Utilities\UtlDevCodescape\utlDevPrfdump; Flags: recursesubdirs
Source: {#KATANA_FILES}\Utl\Dev\GDWorkshop\*; DestDir: {app}\Utl\Dev\GDWorkshop; Components: Utilities\UtlDevCodescape\UtlDevGDWorkshop; Flags: recursesubdirs
Source: {#KATANA_FILES}\Utl\Dev\CDCraft\*; DestDir: {app}\Utl\Dev\CDCraft; Components: Utilities\UtlDevCodescape\UtlDevCDCraft; Flags: recursesubdirs
Source: {#KATANA_FILES}\Utl\Dev\Scripting\*; DestDir: {app}\Utl\Dev\Scripting; Components: Utilities\UtlDevCodescape\UtlDevScripting; Flags: recursesubdirs
;     VME (~ 12770 KiB)
Source: {#KATANA_FILES}\utl\Dev\VMUTool\*; DestDir: {app}\Utl\Dev\VMUTool; Components: Utilities\UtlDevVMUTool; Flags: recursesubdirs
Source: {#KATANA_FILES}\utl\dev\vmstool\Register\*; DestDir: {sys}; Components: Utilities\UtlDevVMUTool\Registered; Flags: sharedfile uninsnosharedfileprompt regserver
Source: {#KATANA_FILES}\utl\dev\vmstool\shared\*; DestDir: {sys}; Components: Utilities\UtlDevVMUTool\Shared; Flags: sharedfile uninsnosharedfileprompt
;     Testing (~ 7638 KiB)
Source: {#KATANA_FILES}\Utl\Dev\DACheck\*; DestDir: {app}\Utl\Dev\DACheck; Components: Utilities\UtlDevDACheck; Flags: recursesubdirs
Source: {#KATANA_FILES}\Utl\Dev\DBFlash\*; DestDir: {app}\Utl\Dev\DBFlash; Components: Utilities\UtlDevDACheck\UtlDevDBFlash; Flags: recursesubdirs
;     IPMaker (~ 1963 KiB)
Source: {#KATANA_FILES}\Utl\Dev\IPMaker\*; DestDir: {app}\Utl\Dev\IPMaker; Components: Utilities\UtlDevIPMaker; Flags: recursesubdirs
;     Graphic (~ 17105 KiB)
Source: {#KATANA_FILES}\Utl\Gfx\*; DestDir: {app}\Utl\Gfx; Components: Utilities\UtlGfx; Flags: recursesubdirs
;     Sound (~ 3288 KiB)
Source: {#KATANA_FILES}\Utl\Snd\*; DestDir: {app}\Utl\Snd; Components: Utilities\UtlSnd; Flags: recursesubdirs
;     Audio64 (~ 102 KiB)
//Source: {#KATANA_FILES}\Utl\*; DestDir: {app}\Lib\Audio64; Components: Utilities\LibAudio64
Source: {#KATANA_FILES}\Sample\Audio64\Raw\gd_root\audio64.lib; DestDir: {app}\Lib\Audio64; Components: Utilities\LibAudio64\Lib
Source: {#KATANA_FILES}\Sample\Audio64\Raw\gd_root\audio64.drv; DestDir: {app}\Driver; Components: Utilities\LibAudio64\Drv
;     Dial (~ 161 KiB)
Source: {#KATANA_FILES}\Utl\Dev\DAInterface\*; DestDir: {app}\Utl\Dev\DAInterface; Components: Utilities\utldevdainterface; Flags: recursesubdirs
;     CIM Utility (~ 452 KiB)
Source: {#KATANA_FILES}\Utl\Dev\CIM_Util\*; DestDir: {app}\Utl\Dev\CIM_Util; Components: Utilities\CIM_UTL; Flags: recursesubdirs
; Icons (~ 0 KiB)
//Source: {#KATANA_FILES}\Icons\*; DestDir: {app}; Components: DesktopIcons
; Libraries (~ 22567 KiB)
Source: {#KATANA_FILES}\Lib\*; DestDir: {app}\Lib; Components: Libraries or Sample; Flags: recursesubdirs
Source: {#KATANA_FILES}\SetPaths.bat; DestDir: {app}; Components: Libraries\SetPathsBat
; Samples (~ 540796 KiB)
Source: {#KATANA_FILES}\Sample\*; DestDir: {app}\Sample; Components: Sample
Source: {#KATANA_FILES}\Sample\Audio64\*; DestDir: {app}\Sample\Audio64; Components: Sample\SampleAudio64; Excludes: Raw; Flags: recursesubdirs
Source: {#KATANA_FILES}\Sample\stdio_stl\*; DestDir: {app}\Sample\stdio_stl; Components: Sample\SampleStdio_stl; Flags: recursesubdirs
Source: {#KATANA_FILES}\Sample\Gdfs\*; DestDir: {app}\Sample\Gdfs; Components: Sample\SampleGdfs; Flags: recursesubdirs
Source: {#KATANA_FILES}\Sample\km2Demo\*; DestDir: {app}\Sample\km2Demo; Components: Sample\Samplekm2Demo; Flags: recursesubdirs
Source: {#KATANA_FILES}\Sample\Libc\*; DestDir: {app}\Sample\Libc; Components: Sample\SampleLibc; Flags: recursesubdirs skipifsourcedoesntexist
Source: {#KATANA_FILES}\Sample\Movie\*; DestDir: {app}\Sample\Movie; Components: Sample\SampleMovie; Flags: recursesubdirs
Source: {#KATANA_FILES}\Sample\Periph\*; DestDir: {app}\Sample\Periph; Components: Sample\SamplePeriph; Flags: recursesubdirs
Source: {#KATANA_FILES}\Sample\Sound\*; DestDir: {app}\Sample\Sound; Components: Sample\SampleSound; Flags: recursesubdirs
Source: {#KATANA_FILES}\Sample\Sys\*; DestDir: {app}\Sample\Sys; Components: Sample\SampleSys; Flags: recursesubdirs
Source: {#KATANA_FILES}\Sample\Ginsu\*; DestDir: {app}\Sample\Ginsu; Components: Sample\SampleGinsu; Flags: recursesubdirs
Source: {#KATANA_FILES}\Sample\Kamui2\*; DestDir: {app}\Sample\Kamui2; Components: Sample\SampleKamui2; Flags: recursesubdirs
Source: {#KATANA_FILES}\Sample\Net\*; DestDir: {app}\Sample\Net; Components: Sample\SampleNet; Flags: recursesubdirs
Source: {#KATANA_FILES}\Include\*; DestDir: {app}\Include; Components: Include or Sample; Flags: recursesubdirs
; Driver (~ 113 KiB)
Source: {#KATANA_FILES}\Driver\*; DestDir: {app}\Driver; Components: RootDriver
; Submission (~ 62656 KiB)
Source: {#KATANA_FILES}\Submit\*; DestDir: {app}\Submit; Components: RootSubmission; Flags: recursesubdirs
; Icones
Source: {#KATANA_FILES}\Icons\*; DestDir: {group}\Help and Information
Source: {#KATANA_SPLASH}\trash.ico; DestDir: {pf}\{#KATANA_FIRM}\Setup\{#KATANA_SHORT} {#KATANA_TYPE} {#KATANA_VER}{#KATANA_REV}
; Install
;Source: {#KATANA_INSTALL}\{#KATANA_SHORT} {#KATANA_TYPE} {#KATANA_VER}.{#KATANA_REV}.iss; DestDir: {app}\Inst
;Source: {#KATANA_TOOLS}\Setup{#KATANA_SHORT}.isi; DestDir: {app}\Inst
Source: {#KATANA_TOOLS}\Aspi\*; DestDir: {app}\Inst\Aspi; Flags: recursesubdirs
;Source: {#ISSI_IncludePath}\*; DestDir: {app}\Inst\ISSI; Flags: recursesubdirs
;Source: {#KATANA_SPLASH}\*; DestDir: {app}\Inst\Splash; Flags: recursesubdirs
;Source: {#KATANA_TEXT}\*; DestDir: {app}\Inst\Text; Flags: recursesubdirs
; Backup
Source: {#KATANA_INSTALL}\*; DestDir: {app}\BACKUP; Excludes: \OUTPUT\{#KATANA_SHORT}*\*.bin,\OUTPUT\{#KATANA_SHORT}*\*.exe; Flags: recursesubdirs; Components: Backup
; Tasks: extractinstall
#endif
; UninsHs
#ifdef USE_MODIFYREPAIRDELETE
Source: {#ISSI_IncludePath}\UninsHs.exe; DestDir: {pf}\{#KATANA_FIRM}\Setup\{#KATANA_SHORT} {#KATANA_TYPE} {#KATANA_VER}{#KATANA_REV}; Flags: ignoreversion onlyifdoesntexist
#endif

// Page 26: 
[Icons]
; Sur le bureau
Name: {commondesktop}\CodeWarrior IDE; Filename: {app}\Utl\Dev\CodeWarrior\Bin\IDE.exe; Tasks: desktopicon; Components: Utilities\UtlDevHitachi\UtlDevCodeWarrior
Name: {commondesktop}\Codescape Debugger; Filename: {app}\Utl\Dev\Codescape\CODESCAPE.EXE; Tasks: desktopicon; Components: Utilities\UtlDevCodescape
Name: {commondesktop}\GD Workshop; Filename: {app}\Utl\Dev\GDWorkshop\GDWorkshop.exe; Tasks: desktopicon; Components: Utilities\UtlDevCodescape\UtlDevGDWorkshop
Name: {commondesktop}\Start a new compilation environment; Filename: {sys}\cmd.exe; Parameters: "/e:8192 /k ""{app}\SetPaths.bat"""; WorkingDir: {app}; Tasks: desktopicon
; En démarrage rapide
Name: {userappdata}\Microsoft\Internet Explorer\Quick Launch\CodeWarrior IDE; Filename: {app}\Utl\Dev\CodeWarrior\Bin\IDE.exe; Tasks: quicklaunchicon; Components: Utilities\UtlDevHitachi\UtlDevCodeWarrior
Name: {userappdata}\Microsoft\Internet Explorer\Quick Launch\Codescape Debugger; Filename: {app}\Utl\Dev\Codescape\CODESCAPE.EXE; Tasks: quicklaunchicon; Components: Utilities\UtlDevCodescape
; Les outils
Name: {group}\CodeWarrior IDE; Filename: {app}\Utl\Dev\CodeWarrior\Bin\IDE.exe; Components: Utilities\UtlDevHitachi\UtlDevCodeWarrior
Name: {group}\Codescape Debugger; Filename: {app}\Utl\Dev\Codescape\CODESCAPE.EXE; Components: Utilities\UtlDevCodescape
Name: {group}\Debug Adapter Checker; Filename: {app}\Utl\Dev\DACheck\DAcheck.exe; Components: Utilities\UtlDevDACheck
Name: {group}\GD Workshop; Filename: {app}\Utl\Dev\GDWorkshop\GDWorkshop.exe; Components: Utilities\UtlDevCodescape\UtlDevGDWorkshop
Name: {group}\Read Me First!; Filename: {app}\readme.txt; Components: Documentation\DocumentationRoot
Name: {group}\Start a new compilation environment; Filename: Filename: {sys}\cmd.exe; Parameters: "/e:8192 /k ""{app}\SetPaths.bat"""; WorkingDir: {app}
Name: {group}\Visual Memory Unit Emulator; Filename: {app}\Utl\Dev\VMUTool\VmSimulator\vmu.exe; Components: Utilities\UtlDevVMUTool
; La documentation
Name: {group}\Help and Information\Documentation; Filename: {app}\Doc\index.pdf; Components: Documentation
Name: {group}\Help and Information\Getting Started; Filename: {app}\getstart.txt; Components: Documentation\DocumentationRoot
; Sur les programmes
#ifdef USE_MODIFYREPAIRDELETE
Name: {group}\{cm:KatanaTxtUninstall,{#KATANA_SHORT}}; Filename: {pf}\{#KATANA_FIRM}\Setup\{#KATANA_SHORT} {#KATANA_TYPE} {#KATANA_VER}{#KATANA_REV}\UninsHs.exe
#else
Name: {group}\{cm:KatanaTxtUninstall,{#KATANA_SHORT}}; Filename: {uninstallexe}; IconFilename: {pf}\{#KATANA_FIRM}\Setup\{#KATANA_SHORT} {#KATANA_TYPE} {#KATANA_VER}{#KATANA_REV}\trash.ico
#endif

// Page 29: 
[INI]
#ifdef USE_MODIFYREPAIRDELETE
FileName: {pf}\{#KATANA_FIRM}\Setup\{#KATANA_SHORT} {#KATANA_TYPE} {#KATANA_VER}{#KATANA_REV}\UninsHs.dat; Section: Common; Key: Software; String: {#KATANA_NAME}
FileName: {pf}\{#KATANA_FIRM}\Setup\{#KATANA_SHORT} {#KATANA_TYPE} {#KATANA_VER}{#KATANA_REV}\UninsHs.dat; Section: Common; Key: Install; String: {srcexe}
FileName: {pf}\{#KATANA_FIRM}\Setup\{#KATANA_SHORT} {#KATANA_TYPE} {#KATANA_VER}{#KATANA_REV}\UninsHs.dat; Section: Common; Key: Language; String: {language}
FileName: {pf}\{#KATANA_FIRM}\Setup\{#KATANA_SHORT} {#KATANA_TYPE} {#KATANA_VER}{#KATANA_REV}\UninsHs.dat; Section: Common; Key: Remove; String: {uninstallexe}
FileName: {pf}\{#KATANA_FIRM}\Setup\{#KATANA_SHORT} {#KATANA_TYPE} {#KATANA_VER}{#KATANA_REV}\UninsHs.dat; Section: Common; Key: Group; String: {groupname}
FileName: {pf}\{#KATANA_FIRM}\Setup\{#KATANA_SHORT} {#KATANA_TYPE} {#KATANA_VER}{#KATANA_REV}\UninsHs.dat; Section: Common; Key: Components; String: {code:ComponentList|x}
FileName: {pf}\{#KATANA_FIRM}\Setup\{#KATANA_SHORT} {#KATANA_TYPE} {#KATANA_VER}{#KATANA_REV}\UninsHs.dat; Section: Common; Key: Uninstall; String: {#KATANA_NAME}
FileName: {pf}\{#KATANA_FIRM}\Setup\{#KATANA_SHORT} {#KATANA_TYPE} {#KATANA_VER}{#KATANA_REV}\UninsHs.dat; Section: Common; Key: Dir; String: {app}
#endif

// Page 30 -> 41: 
[InstallDelete]
; Un peu de nettoyage d'une précédente installation
;Type: files; Name: {app}\SetPaths.bat

// Page 31: 
[Languages]
Name: en; MessagesFile: compiler:Default.isl,{#KATANA_TEXT}\CmKatanaEnglish.isl,{#ISSI_IncludePath}\Languages\_issi_English.isl; LicenseFile: {#KATANA_FILES}\Legal.txt
//Name: fr; MessagesFile: compiler:Languages\French.isl,{#KATANA_TEXT}\CmKatanaFrench.isl,{#ISSI_IncludePath}\Languages\_issi_French.isl; LicenseFile: {#KATANA_FILES}\LegalFr.txt

// Page 32: 
[Messages]
; Un peu de pub pour super InnoSetup
BeveledLabel=InnoSetup is installing {#KATANA_NAME} {#KATANA_VER}.{#KATANA_REV}

// Page 33=
[CustomMessages]
; On fait simple, directement l'URL de Sega
issiUrl=http://www.dts.sega.com/
issiUrlText=http://www.dts.sega.com/

// Page 34=
;[LangOptions]

// Page 35=
[Registry]
; Jarte la protection
Root: HKCU; Subkey: Software\{#KATANA_FIRM}; Permissions: everyone-modify
Root: HKLM; Subkey: SOFTWARE\{#KATANA_FIRM}; Permissions: everyone-modify
; Le chemin de l'application
Root: HKLM; Subkey: SOFTWARE\{#KATANA_FIRM}\{#KATANA_NAME}; ValueType: string; ValueName: Path; ValueData: {app}\
; Les registres
Root: HKLM; Subkey: Software\{#KATANA_FIRM}\{#KATANA_NAME}\{#KATANA_VER}.{#KATANA_REV}
; Doc
; Utilities
;     Compiler
Root: HKLM; Subkey: SOFTWARE\Metrowerks\Codewarrior\4.0; ValueType: string; ValueName: Path; ValueData: {app}\utl\dev\codewarrior\bin\ide.exe; Components: Utilities\UtlDevHitachi\UtlDevCodeWarrior
Root: HKLM; Subkey: SOFTWARE\Classes\.mcp; ValueType: string; ValueName: ; ValueData: mcpfile; Components: Utilities\UtlDevHitachi\UtlDevCodeWarrior
Root: HKLM; Subkey: SOFTWARE\Classes\mcpfile; ValueType: string; ValueName: ; ValueData: CodeWarrior Project; Components: Utilities\UtlDevHitachi\UtlDevCodeWarrior
Root: HKLM; Subkey: SOFTWARE\Classes\mcpfile; ValueType: string; ValueName: AlwaysShowExt; ValueData: ; Components: Utilities\UtlDevHitachi\UtlDevCodeWarrior
Root: HKLM; Subkey: SOFTWARE\Classes\mcpfile\DefaultIcon; ValueType: string; ValueName: ; ValueData: {app}\utl\dev\codewarrior\bin\ide.exe; Components: Utilities\UtlDevHitachi\UtlDevCodeWarrior
Root: HKLM; Subkey: SOFTWARE\Classes\mcpfile\shell\Open\command; ValueType: string; ValueName: ; ValueData: "{app}\utl\dev\codewarrior\bin\ide.exe \""%1\"""; Components: Utilities\UtlDevHitachi\UtlDevCodeWarrior
;     VME
;     Testing
//Root: HKLM; Subkey: SOFTWARE\Microsoft\Windows\CurrentVersion\App Paths\CODESCAPE.EXE; ValueType: string; ValueName: ; ValueData: {app}\utl\dev\codescape\CODESCAPE.EXE\CODESCAPE.EXE; Components: Utilities\UtlDevCodescape
Root: HKLM; Subkey: SOFTWARE\Microsoft\Windows\CurrentVersion\App Paths\CODESCAPE.EXE; ValueType: string; ValueName: Path; ValueData: {app}\utl\dev\codescape\CODESCAPE.EXE; Components: Utilities\UtlDevCodescape
;     IPMaker
;     Graphic
;     Sound
;     Audio64
;     Dial
;     CIM Utility
; Icons
; Libraries
; Samples
; Driver
; Submission

// Page 38: 
[Run]
#ifdef USE_MODIFYREPAIRDELETE
Filename: {pf}\{#KATANA_FIRM}\Setup\{#KATANA_SHORT} {#KATANA_TYPE} {#KATANA_VER}{#KATANA_REV}\UninsHs.exe; Parameters: /r; Flags: runminimized
#endif
; Installation de ASPI
Filename: {app}\Inst\Aspi\Install.bat; Parameters: X86; StatusMsg: Installing ASPI drivers for Windows 9x/Me/NT/2000...; Flags: waituntilterminated skipifdoesntexist; MinVersion: 4.0,4.0; OnlyBelowVersion: 0,5.01; Tasks: installaspi
Filename: {app}\Inst\Aspi\Install.bat; Parameters: XP32; StatusMsg: Installing ASPI drivers for Windows XP 32 bits...; Flags: waituntilterminated skipifdoesntexist; MinVersion: 0,5.01; Check: not Is64BitInstallMode; Tasks: installaspi
Filename: {app}\Inst\Aspi\Install.bat; Parameters: XP64; StatusMsg: Installing ASPI drivers for Windows XP 64 bits...; Flags: waituntilterminated skipifdoesntexist; MinVersion: 0,5.01; Check: Is64BitInstallMode; Tasks: installaspi
; Reflashage du débuggeur
Filename: {app}\Utl\Dev\DBFlash\runflash.bat; StatusMsg: Flashing the debugger...; Flags: waituntilterminated skipifdoesntexist; Tasks: flashdebug
; Démarrage du programme
Filename: {app}\SetPaths.bat; Description: {cm:LaunchProgram,SetPaths.bat}; WorkingDir: {app}; Components: Libraries\SetPathsBat; Flags: postinstall skipifdoesntexist skipifsilent

// Page 38=: 
;[UninstallRun]

// Page 41: 
[UninstallDelete]
#ifdef USE_MODIFYREPAIRDELETE
Type: filesandordirs; Name: {pf}\{#KATANA_FIRM}\Setup\{#KATANA_SHORT} {#KATANA_TYPE} {#KATANA_VER}{#KATANA_REV}\UninsHs.dat
#endif

; La section [Code] est à la fin et dans un fichier externe pour reprendre la structure de mon script InstallShield
// === CODE : SETUPKATANA =============================================================================================

#include KATANA_TOOLS+"\Setup"+KATANA_SHORT+".isi"

// === INCLUDE ISSI ===================================================================================================: 

#include ISSI_IncludePath+"\_issi.isi"

// Putain qu'est ce que c'est bien InnoSetup, mais comment ais-je pu m'en passer aussi longtemps ?: 
