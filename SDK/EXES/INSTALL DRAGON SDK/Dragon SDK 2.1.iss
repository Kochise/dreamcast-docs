; TYPE    DU SCRIPT : MICROSOFT DRAGON
; AUTEUR  DU SCRIPT : Kochise
; VERSION DU SCRIPT : 2006/03/13

; === DEFINE DRAGON ====================================================================================================
; Bon, principalement les chemins des fichiers sources

; - - 8< - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

; JUST EDIT THIS PLACE FROM ONE SDK REVISION TO ANOTHER

#define SETUP_VERSION  "2.6.7.10"

#define DRAGON_FIRM    "Microsoft"
#define DRAGON_NAME    "Windows CE for Dreamcast SDK"
#define DRAGON_SHORT   "Dragon"
#define DRAGON_TYPE    "SDK"
#define DRAGON_VER     "2"
#define DRAGON_REV     "1"
#define DRAGON_BUILD   "0.49"
#define DRAGON_DATE    "991102"
;#define DRAGON_DEBUG

; - - 8< - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

#define DRAGON_INSTALL "."
#define DRAGON_FILES   DRAGON_INSTALL+"\INPUT\"+DRAGON_VER+"."+DRAGON_REV+"."+DRAGON_BUILD+"_"+DRAGON_DATE
#define DRAGON_TOOLS   DRAGON_INSTALL+"\TOOLS"
#define DRAGON_SPLASH  DRAGON_TOOLS+"\Splash"
#define DRAGON_TEXT    DRAGON_TOOLS+"\Text"

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
AppName={#DRAGON_NAME}
AppVerName={#DRAGON_NAME} {#DRAGON_VER}.{#DRAGON_REV}
AppId={#DRAGON_NAME}
// 53=
;;AppMutex=
AppCopyright=Copyright (c) {#DRAGON_FIRM} 2000
AppComments=dclicens@microsoft.com
AppContact=Wince4DC@Microsoft.com
AppPublisher={#DRAGON_FIRM}
AppPublisherURL=http://www.microsoft.com/
AppSupportURL=http://www.microsoft.com/
AppUpdatesURL=http://www.microsoft.com/
AppVersion={#DRAGON_VER}.{#DRAGON_REV}
// Page 54=
DefaultDirName={reg:HKLM\SOFTWARE\{#DRAGON_FIRM}\{#DRAGON_NAME},Path|{sd}\WCEDreamcast}
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
OutputBaseFilename=setup_{#DRAGON_SHORT}_{#DRAGON_TYPE}_{#DRAGON_VER}{#DRAGON_REV}
UninstallFilesDir={pf}\{#DRAGON_FIRM}\Setup\{#DRAGON_SHORT} {#DRAGON_TYPE} {#DRAGON_VER}{#DRAGON_REV}
// Page 60=
UninstallDisplayIcon={uninstallexe},0
;;UninstallDisplayName=
;;;UninstallIconName=
;UninstallLogMode=append
;UninstallRestartComputer=no
// Page 61=
;UpdateUninstallLogAppName=yes
DefaultGroupName={#DRAGON_FIRM}\{#DRAGON_NAME}
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
;;LicenseFile={#DRAGON_FILES}\Legal.txt
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
WizardImageFile={#DRAGON_SPLASH}\BannerLeft{#DRAGON_SHORT}.bmp
;WindowShowCaption=yes
WindowStartMaximized=no
;WindowResizable=yes
// Page 68=
;WindowVisible=no
;WizardImageBackColor=$400000
;WizardImageStretch=yes
;WizardSmallImageBackColor=clWhite
;;SourceDir=
OutputDir=OUTPUT\{#DRAGON_SHORT} {#DRAGON_TYPE} {#DRAGON_VER}.{#DRAGON_REV}.{#DRAGON_BUILD}
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
SetupIconFile={#DRAGON_SPLASH}\{#DRAGON_SHORT}Us.ico
;;VersionInfoCompany=
;;VersionInfoDescription=
;;VersionInfoTextVersion=
// Page 73=
VersionInfoVersion={#SETUP_VERSION}
;;;UninstallIconFile={#DRAGON_SPLASH}\Trash.ico
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

;#define ISSI_ScriptBackup     "Microsoft "+DRAGON_SHORT+" "+DRAGON_TYPE+" "+DRAGON_VER+"."+DRAGON_REV+".iss"
;#define ISSI_ScriptBackup_Key "restorescriptbackup"

#define ISSI_UPDATE            DRAGON_NAME
#define ISSI_UpdateOrInstall
#define ISSI_UpdateTitle       DRAGON_NAME
#define ISSI_UpdateAppVersion  DRAGON_VER+"."+DRAGON_REV

#define ISSI_LicensePrint

;#define ISSI_ScreenSaver "myScreensaver.scr"

; --- APPEARANCE ------------------------------------------------------------------------------------------------------

;#define ISSI_WizardImages

#define ISSI_BeveledApp

;#define ISSI_Image "splash.bmp"

#define ISSI_Splash   DRAGON_SPLASH+"\setup.bmp"
#define ISSI_Splash_T 2
#define ISSI_Splash_X 320
#define ISSI_Splash_Y 240
;#define ISSI_Splash_CORNER 8

;#define ISSI_WizardBitmapImage "splash_495x314.bmp"
;#define ISSI_WizardBitmapImage_x 495
;#define ISSI_WizardBitmapImage2 "albartus_com.bmp"
;#define ISSI_WizardBitmapImage2_x 164

#define ISSI_WizardSmallBitmapImage   DRAGON_SPLASH+"\BannerTop"+DRAGON_SHORT+".bmp"
#define ISSI_WizardSmallBitmapImage_x 140

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

#define ISSI_IncludePath DRAGON_TOOLS+"\ISSI"

; === DEFINE ISSI =====================================================================================================

// Page 13=
[Types]
Name: Typique; Description: {cm:DragonTypesTypique}
Name: Minimal; Description: {cm:DragonTypesMinimal}
Name: Custom; Description: {cm:DragonTypesCustom}; Flags: iscustom

// Page 14: 
[Components]
Name: Utilities; Description: {cm:DragonComponentsUtilities}; Types: Typique Custom Minimal
Name: Sample; Description: {cm:DragonComponentsSample}; Types: Typique Custom
Name: Documentation; Description: {cm:DragonComponentsDocumentation}; Types: Typique Custom Minimal
Name: Backup; Description: {cm:DragonComponentsBackup}

// Page 16: 
[Tasks]
;Name: desktopicon; Description: {cm:CreateDesktopIcon}; GroupDescription: {cm:AdditionalIcons}
;Name: quicklaunchicon; Description: {cm:CreateQuickLaunchIcon}; GroupDescription: {cm:AdditionalIcons}; Flags: unchecked
Name: installaspi; Description: {cm:DragonTasksInstallAspi}; GroupDescription: {cm:DragonDescriptionHardware}
Name: flashdebug; Description: {cm:DragonTasksFlashDebugger}; GroupDescription: {cm:DragonDescriptionHardware}; Flags: unchecked
;Name: extractinstall; Description: {cm:DragonTasksBackupInstall}; GroupDescription: {cm:DragonDescriptionBackup}; Flags: unchecked

// Page 18: 
[Dirs]
Name: {app}; Permissions: everyone-modify

// Page 20: 
[Files]
; NOTE: Ne pas utiliser "Flags: ignoreversion" sur les fichier système partagés
; Doc (~ 7317 KiB)
#ifndef DRAGON_DEBUG
Source: {#DRAGON_FILES}\docs\*; DestDir: {app}\docs; Components: Documentation; Flags: recursesubdirs
#endif
Source: {#DRAGON_FILES}\*; DestDir: {app}
#ifndef DRAGON_DEBUG
; Includes (~ 10097 KiB)
Source: {#DRAGON_FILES}\inc\*; DestDir: {app}\inc; Components: Utilities; Flags: recursesubdirs
; Libraries (~ 8739 KiB)
Source: {#DRAGON_FILES}\lib\*; DestDir: {app}\lib; Components: Utilities; Flags: recursesubdirs
; Release (~ 262964 KiB)
Source: {#DRAGON_FILES}\release\common\*; DestDir: {app}\release\debug; Components: Utilities; Flags: recursesubdirs
Source: {#DRAGON_FILES}\release\debug\*; DestDir: {app}\release\debug; Components: Utilities; Flags: recursesubdirs
Source: {#DRAGON_FILES}\release\common\*; DestDir: {app}\release\retail; Components: Utilities; Flags: recursesubdirs
Source: {#DRAGON_FILES}\release\retail\*; DestDir: {app}\release\retail; Components: Utilities; Flags: recursesubdirs
; Sample (~ 66130 KiB)
Source: {#DRAGON_FILES}\samples\*; DestDir: {app}\samples; Components: Sample; Flags: recursesubdirs
; Utilities (~ 24936 KiB)
Source: {#DRAGON_FILES}\tools\*; DestDir: {app}\tools; Components: Utilities; Flags: recursesubdirs
; Icones
Source: {#DRAGON_SPLASH}\trash.ico; DestDir: {pf}\{#DRAGON_FIRM}\Setup\{#DRAGON_SHORT} {#DRAGON_TYPE} {#DRAGON_VER}{#DRAGON_REV}
; Install
;Source: {#DRAGON_INSTALL}\{#DRAGON_SHORT} {#DRAGON_TYPE} {#DRAGON_VER}.{#DRAGON_REV}.iss; DestDir: {app}\Inst
;Source: {#DRAGON_TOOLS}\Setup{#DRAGON_SHORT}.isi; DestDir: {app}\Inst
Source: {#DRAGON_TOOLS}\Aspi\*; DestDir: {app}\Inst\Aspi; Flags: recursesubdirs
;Source: {#DRAGON_TOOLS}\LobbySample\*; DestDir: {app}\Inst\LobbySample; Flags: recursesubdirs
;Source: {#DRAGON_TOOLS}\Original\*; DestDir: {app}\Inst\Original; Flags: recursesubdirs
;Source: {#ISSI_IncludePath}\*; DestDir: {app}\Inst\ISSI; Flags: recursesubdirs
;Source: {#DRAGON_SPLASH}\*; DestDir: {app}\Inst\Splash; Flags: recursesubdirs
;Source: {#DRAGON_TEXT}\*; DestDir: {app}\Inst\Text; Flags: recursesubdirs
; Backup
Source: {#DRAGON_INSTALL}\*; DestDir: {app}\BACKUP; Excludes: \OUTPUT\{#DRAGON_SHORT}*\*.bin,\OUTPUT\{#DRAGON_SHORT}*\*.exe; Flags: recursesubdirs; Components: Backup
; Tasks: extractinstall
#endif
; UninsHs
#ifdef USE_MODIFYREPAIRDELETE
Source: {#ISSI_IncludePath}\UninsHs.exe; DestDir: {pf}\{#DRAGON_FIRM}\Setup\{#DRAGON_SHORT} {#DRAGON_TYPE} {#DRAGON_VER}{#DRAGON_REV}; Flags: ignoreversion onlyifdoesntexist
#endif

// Page 26: 
[Icons]
; Les outils
Name: {group}\Configuration Tool; Filename: {app}\tools\configtool.exe; WorkingDir: {app}; Components: Utilities
Name: {group}\Dreamcast Tool; Filename: {app}\tools\dctool.exe; WorkingDir: {app}; Components: Utilities
Name: {group}\GD Workshop; Filename: {app}\tools\GDWorkshop\GD Workshop.exe; WorkingDir: {app}\tools\GDWorkshop; Components: Utilities
Name: {group}\License Agreement; Filename: {app}\license.txt; Components: Utilities
Name: {group}\Release Notes; Filename: {app}\docs\relnotes.htm; Components: Documentation
Name: {group}\SynthAuthor; Filename: {app}\tools\synthauthor\synthauthor.exe; WorkingDir: {app}\tools\synthauthor; Components: Utilities
Name: {group}\WinCE Debug Command Line; Filename: {sys}\cmd.exe; Parameters: "/x /k ""{app}\wce.bat"" debug"; WorkingDir: {app}
Name: {group}\WinCE Retail Command Line; Filename: {sys}\cmd.exe; Parameters: "/x /k ""{app}\wce.bat"" retail"; WorkingDir: {app}
; La documentation
Name: {group}\Windows CE for Dreamcast SDK Help; Filename: {app}\docs\drmcast.chm; Components: Documentation
; Sur les programmes
#ifdef USE_MODIFYREPAIRDELETE
Name: {group}\{cm:DragonTxtUninstall,{#DRAGON_SHORT}}; Filename: {pf}\{#DRAGON_FIRM}\Setup\{#DRAGON_SHORT} {#DRAGON_TYPE} {#DRAGON_VER}{#DRAGON_REV}\UninsHs.exe
#else
Name: {group}\{cm:DragonTxtUninstall,{#DRAGON_SHORT}}; Filename: {uninstallexe}; IconFilename: {pf}\{#DRAGON_FIRM}\Setup\{#DRAGON_SHORT} {#DRAGON_TYPE} {#DRAGON_VER}{#DRAGON_REV}\trash.ico
#endif

// Page 29: 
[INI]
#ifdef USE_MODIFYREPAIRDELETE
FileName: {pf}\{#DRAGON_FIRM}\Setup\{#DRAGON_SHORT} {#DRAGON_TYPE} {#DRAGON_VER}{#DRAGON_REV}\UninsHs.dat; Section: Common; Key: Software; String: {#DRAGON_NAME}
FileName: {pf}\{#DRAGON_FIRM}\Setup\{#DRAGON_SHORT} {#DRAGON_TYPE} {#DRAGON_VER}{#DRAGON_REV}\UninsHs.dat; Section: Common; Key: Install; String: {srcexe}
FileName: {pf}\{#DRAGON_FIRM}\Setup\{#DRAGON_SHORT} {#DRAGON_TYPE} {#DRAGON_VER}{#DRAGON_REV}\UninsHs.dat; Section: Common; Key: Language; String: {language}
FileName: {pf}\{#DRAGON_FIRM}\Setup\{#DRAGON_SHORT} {#DRAGON_TYPE} {#DRAGON_VER}{#DRAGON_REV}\UninsHs.dat; Section: Common; Key: Remove; String: {uninstallexe}
FileName: {pf}\{#DRAGON_FIRM}\Setup\{#DRAGON_SHORT} {#DRAGON_TYPE} {#DRAGON_VER}{#DRAGON_REV}\UninsHs.dat; Section: Common; Key: Group; String: {groupname}
FileName: {pf}\{#DRAGON_FIRM}\Setup\{#DRAGON_SHORT} {#DRAGON_TYPE} {#DRAGON_VER}{#DRAGON_REV}\UninsHs.dat; Section: Common; Key: Components; String: {code:ComponentList|x}
FileName: {pf}\{#DRAGON_FIRM}\Setup\{#DRAGON_SHORT} {#DRAGON_TYPE} {#DRAGON_VER}{#DRAGON_REV}\UninsHs.dat; Section: Common; Key: Uninstall; String: {#DRAGON_NAME}
FileName: {pf}\{#DRAGON_FIRM}\Setup\{#DRAGON_SHORT} {#DRAGON_TYPE} {#DRAGON_VER}{#DRAGON_REV}\UninsHs.dat; Section: Common; Key: Dir; String: {app}
#endif

// Page 30 -> 41: 
[InstallDelete]
; Un peu de nettoyage d'une précédente installation
;Type: files; Name: {app}\SetPaths.bat

// Page 31: 
[Languages]
Name: en; MessagesFile: compiler:Default.isl,{#DRAGON_TEXT}\CmDragonEnglish.isl,{#ISSI_IncludePath}\Languages\_issi_English.isl; LicenseFile: {#DRAGON_FILES}\license.txt
//Name: fr; MessagesFile: compiler:Languages\French.isl,{#DRAGON_TEXT}\CmDragonFrench.isl,{#ISSI_IncludePath}\Languages\_issi_French.isl; LicenseFile: {#DRAGON_FILES}\license.txt

// Page 32: 
[Messages]
; Un peu de pub pour super InnoSetup
BeveledLabel=InnoSetup is installing {#DRAGON_NAME} {#DRAGON_VER}.{#DRAGON_REV}

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
Root: HKCU; Subkey: Software\{#DRAGON_FIRM}; Permissions: everyone-modify
Root: HKLM; Subkey: SOFTWARE\{#DRAGON_FIRM}; Permissions: everyone-modify
; Le chemin de l'application
Root: HKLM; Subkey: SOFTWARE\{#DRAGON_FIRM}\{#DRAGON_NAME}; ValueType: string; ValueName: Path; ValueData: {app}\
; Les registres
Root: HKLM; Subkey: Software\{#DRAGON_FIRM}\{#DRAGON_NAME}\{#DRAGON_VER}.{#DRAGON_REV}.{#DRAGON_BUILD}
; Dragon
Root: HKLM; Subkey: SOFTWARE\Classes\CLSID\{{2815F6D8-D670-11d2-9B9C-00A0C9C9F60E}; ValueType: string; ValueData: VCTransport Class
Root: HKLM; Subkey: SOFTWARE\Classes\CLSID\{{2815F6D8-D670-11d2-9B9C-00A0C9C9F60E}\InprocServer32; ValueType: string; ValueData: {app}\tools\VCCE\Server\vchans.dll
Root: HKLM; Subkey: SOFTWARE\Classes\CLSID\{{2815F6D8-D670-11d2-9B9C-00A0C9C9F60E}\InprocServer32; ValueType: string; ValueName: ThreadingModel; ValueData: Free
Root: HKLM; Subkey: SOFTWARE\Classes\CLSID\{{2815F6D8-D670-11d2-9B9C-00A0C9C9F60E}\ProgID; ValueType: string; ValueData: VCTransport.VCTransport.1
Root: HKLM; Subkey: SOFTWARE\Classes\CLSID\{{2815F6D8-D670-11d2-9B9C-00A0C9C9F60E}\VersionIndependentProgID; ValueType: string; ValueData: VCTransport.VCTransport

Root: HKLM; Subkey: SOFTWARE\Classes\CLSID\{{BA7F08EC-BD20-11D2-9D07-00C04FD929DC}; ValueType: dword; ValueName: Co-Components removal; ValueData: 00000001
Root: HKLM; Subkey: SOFTWARE\Classes\CLSID\{{BA7F08EC-BD20-11D2-9D07-00C04FD929DC}\ConfigurationFile; ValueType: string; ValueData: {app}\tools\config.cfg
Root: HKLM; Subkey: SOFTWARE\Classes\CLSID\{{BA7F08EC-BD20-11D2-9D07-00C04FD929DC}\Description; ValueType: string; ValueData: This tool allows the developer to choose which components go into the Dreamcast Windows CE image, and build the BIN image.  It also provides the functionality to run an application automatically when the Windows CE OS boots up.
Root: HKLM; Subkey: SOFTWARE\Classes\CLSID\{{BA7F08EC-BD20-11D2-9D07-00C04FD929DC}\InprocServer32; ValueType: string; ValueData: {app}\tools\makeimgconfig.dll
Root: HKLM; Subkey: SOFTWARE\Classes\CLSID\{{BA7F08EC-BD20-11D2-9D07-00C04FD929DC}\InprocServer32; ValueType: string; ValueName: ThreadingModel; ValueData: both
Root: HKLM; Subkey: SOFTWARE\Classes\CLSID\{{BA7F08EC-BD20-11D2-9D07-00C04FD929DC}\OutputFile; ValueType: string; ValueData: {app}\Release\debug\common.bib
Root: HKLM; Subkey: SOFTWARE\Classes\CLSID\{{BA7F08EC-BD20-11D2-9D07-00C04FD929DC}\ProgID; ValueType: string; ValueData: Dreamcast Image Configuration Tool
Root: HKLM; Subkey: SOFTWARE\Classes\CLSID\{{BA7F08EC-BD20-11D2-9D07-00C04FD929DC}\VersionIndependentProgID; ValueType: string; ValueData: MAKEIMGCONFIG Developer Studio Add-in

Root: HKLM; Subkey: SOFTWARE\Classes\CLSID\{{DCE1DA35-E177-11d2-9B9C-00A0C9C9F60E}; ValueType: string; ValueData: Server Class
Root: HKLM; Subkey: SOFTWARE\Classes\CLSID\{{DCE1DA35-E177-11d2-9B9C-00A0C9C9F60E}\InprocServer32; ValueType: string; ValueData: {app}\tools\VCCE\Server\ceshsrv.dll
Root: HKLM; Subkey: SOFTWARE\Classes\CLSID\{{DCE1DA35-E177-11d2-9B9C-00A0C9C9F60E}\InprocServer32; ValueType: string; ValueName: ThreadingModel; ValueData: Free
Root: HKLM; Subkey: SOFTWARE\Classes\CLSID\{{DCE1DA35-E177-11d2-9B9C-00A0C9C9F60E}\ProgID; ValueType: string; ValueData: Server.Server.1
Root: HKLM; Subkey: SOFTWARE\Classes\CLSID\{{DCE1DA35-E177-11d2-9B9C-00A0C9C9F60E}\VersionIndependentProgID; ValueType: string; ValueData: Server.Server

Root: HKLM; Subkey: SOFTWARE\Classes\CLSID\{{DCE1DA36-E177-11d2-9B9C-00A0C9C9F60E}; ValueType: string; ValueData: ManualServer Class
Root: HKLM; Subkey: SOFTWARE\Classes\CLSID\{{DCE1DA36-E177-11d2-9B9C-00A0C9C9F60E}\InprocServer32; ValueType: string; ValueData: {app}\tools\VCCE\Server\mansrv.dll
Root: HKLM; Subkey: SOFTWARE\Classes\CLSID\{{DCE1DA36-E177-11d2-9B9C-00A0C9C9F60E}\InprocServer32; ValueType: string; ValueName: ThreadingModel; ValueData: Free
Root: HKLM; Subkey: SOFTWARE\Classes\CLSID\{{DCE1DA36-E177-11d2-9B9C-00A0C9C9F60E}\ProgID; ValueType: string; ValueData: ManualServer.ManualServer.1
Root: HKLM; Subkey: SOFTWARE\Classes\CLSID\{{DCE1DA36-E177-11d2-9B9C-00A0C9C9F60E}\Programmable
Root: HKLM; Subkey: SOFTWARE\Classes\CLSID\{{DCE1DA36-E177-11d2-9B9C-00A0C9C9F60E}\VersionIndependentProgID; ValueType: string; ValueData: ManualServer.ManualServer

Root: HKLM; Subkey: SOFTWARE\Classes\Dreamcast Image Configuration Tool\CLSID; ValueType: string; ValueData: {{BA7F08EC-BD20-11D2-9D07-00C04FD929DC}

Root: HKLM; Subkey: SOFTWARE\Classes\Interface\{{BA7F08ED-BD20-11D2-9D07-00C04FD929DC}; ValueType: string; ValueData: ICommands
Root: HKLM; Subkey: SOFTWARE\Classes\Interface\{{BA7F08ED-BD20-11D2-9D07-00C04FD929DC}\ProxyStubClsid; ValueType: string; ValueData: {{00020424-0000-0000-C000-000000000046}
Root: HKLM; Subkey: SOFTWARE\Classes\Interface\{{BA7F08ED-BD20-11D2-9D07-00C04FD929DC}\ProxyStubClsid32; ValueType: string; ValueData: {{00020424-0000-0000-C000-000000000046}
Root: HKLM; Subkey: SOFTWARE\Classes\Interface\{{BA7F08ED-BD20-11D2-9D07-00C04FD929DC}\TypeLib; ValueType: string; ValueData: {{BA7F08F1-BD20-11D2-9D07-00C04FD929DC}
Root: HKLM; Subkey: SOFTWARE\Classes\Interface\{{BA7F08ED-BD20-11D2-9D07-00C04FD929DC}\TypeLib; ValueType: string; ValueName: Version; ValueData: 1.0

Root: HKLM; Subkey: SOFTWARE\Classes\MAKEIMGCONFIG Developer Studio Add-in\CLSID; ValueType: string; ValueData: {{BA7F08EC-BD20-11D2-9D07-00C04FD929DC}

Root: HKLM; Subkey: SOFTWARE\Classes\ManualServer.ManualServer; ValueType: string; ValueData: ManualServer Class
Root: HKLM; Subkey: SOFTWARE\Classes\ManualServer.ManualServer\CurVer; ValueType: string; ValueData: ManualServer.ManualServer.1
Root: HKLM; Subkey: SOFTWARE\Classes\ManualServer.ManualServer.1; ValueType: string; ValueData: ManualServer Class
Root: HKLM; Subkey: SOFTWARE\Classes\ManualServer.ManualServer.1\CLSID; ValueType: string; ValueData: {{DCE1DA36-E177-11d2-9B9C-00A0C9C9F60E}

Root: HKLM; Subkey: SOFTWARE\Classes\Server.Server; ValueType: string; ValueData: Server Class
Root: HKLM; Subkey: SOFTWARE\Classes\Server.Server\CurVer; ValueType: string; ValueData: Server.Server.1
Root: HKLM; Subkey: SOFTWARE\Classes\Server.Server.1; ValueType: string; ValueData: Server Class
Root: HKLM; Subkey: SOFTWARE\Classes\Server.Server.1\CLSID; ValueType: string; ValueData: {{DCE1DA35-E177-11d2-9B9C-00A0C9C9F60E}

Root: HKLM; Subkey: SOFTWARE\Classes\TypeLib\{{BA7F08F1-BD20-11D2-9D07-00C04FD929DC}\1.0; ValueType: string; ValueData: MAKEIMGCONFIG Developer Studio Add-in
Root: HKLM; Subkey: SOFTWARE\Classes\TypeLib\{{BA7F08F1-BD20-11D2-9D07-00C04FD929DC}\1.0\0\win32; ValueType: string; ValueData: {app}\tools\makeimgconfig.dll
Root: HKLM; Subkey: SOFTWARE\Classes\TypeLib\{{BA7F08F1-BD20-11D2-9D07-00C04FD929DC}\1.0\FLAGS; ValueType: string; ValueData: 0
Root: HKLM; Subkey: SOFTWARE\Classes\TypeLib\{{BA7F08F1-BD20-11D2-9D07-00C04FD929DC}\1.0\HELPDIR; ValueType: string; ValueData: {app}\tools\

Root: HKLM; Subkey: SOFTWARE\Classes\VCTransport.VCTransport; ValueType: string; ValueData: VCTransport Class
Root: HKLM; Subkey: SOFTWARE\Classes\VCTransport.VCTransport\CurVer; ValueType: string; ValueData: VCTransport.VCTransport.1
Root: HKLM; Subkey: SOFTWARE\Classes\VCTransport.VCTransport.1; ValueType: string; ValueData: VCTransport Class
Root: HKLM; Subkey: SOFTWARE\Classes\VCTransport.VCTransport.1\CLSID; ValueType: string; ValueData: {{2815F6D8-D670-11d2-9B9C-00A0C9C9F60E}

Root: HKLM; Subkey: SOFTWARE\{#DRAGON_FIRM}\{#DRAGON_SHORT} {#DRAGON_TYPE}; ValueType: string; ValueName: Version; ValueData: 2.1.0.49
Root: HKLM; Subkey: SOFTWARE\{#DRAGON_FIRM}\{#DRAGON_SHORT} {#DRAGON_TYPE}; ValueType: string; ValueName: Install Directory; ValueData: {app}
Root: HKLM; Subkey: SOFTWARE\{#DRAGON_FIRM}\{#DRAGON_SHORT} {#DRAGON_TYPE}; ValueType: string; ValueName: Release Directory; ValueData: {app}\Release\debug
Root: HKLM; Subkey: SOFTWARE\{#DRAGON_FIRM}\{#DRAGON_SHORT} {#DRAGON_TYPE}; ValueType: string; ValueName: Tools Directory; ValueData: {app}\Tools
Root: HKLM; Subkey: SOFTWARE\{#DRAGON_FIRM}\{#DRAGON_SHORT} {#DRAGON_TYPE}; ValueType: string; ValueName: MakeImg Directory; ValueData: {app}\Tools

Root: HKLM; Subkey: SOFTWARE\{#DRAGON_FIRM}\{#DRAGON_SHORT} {#DRAGON_TYPE}\ConfigTool; ValueType: dword; ValueName: Co-Components removal; ValueData: 00000001
Root: HKLM; Subkey: SOFTWARE\{#DRAGON_FIRM}\{#DRAGON_SHORT} {#DRAGON_TYPE}\ConfigTool; ValueType: string; ValueName: ConfigurationFile; ValueData: {app}\Tools\config.cfg
Root: HKLM; Subkey: SOFTWARE\{#DRAGON_FIRM}\{#DRAGON_SHORT} {#DRAGON_TYPE}\ConfigTool; ValueType: string; ValueName: UserFile; ValueData: {app}\Tools\user.cfg

Root: HKLM; Subkey: SOFTWARE\Microsoft\HTML Help Collections\Developer Collections\0x0409; ValueType: string; ValueName: Preferred; ValueData: 0x0440c05be
Root: HKLM; Subkey: SOFTWARE\Microsoft\HTML Help Collections\Developer Collections\0x0409\0x0440c05be; ValueType: string; ValueData: Windows CE Toolkit 2.0 for Dreamcast Documentation
Root: HKLM; Subkey: SOFTWARE\Microsoft\HTML Help Collections\Developer Collections\0x0409\0x0440c05be; ValueType: string; ValueName: Filename; ValueData: {app}\docs\WCEDrmCast.col

Root: HKLM; Subkey: SOFTWARE\Microsoft\Windows\CurrentVersion\App Paths\DRAGON.EXE; ValueType: string; ValueData: {app}\DRAGON.EXE
Root: HKLM; Subkey: SOFTWARE\Microsoft\Windows\CurrentVersion\App Paths\DRAGON.EXE; ValueType: string; ValueName: Path; ValueData: {app}

;Root: HKU; Subkey: S-1-5-21-839522115-484061587-725345543-1003\Software\Microsoft\DevStudio\6.0\AddIns\Dreamcast Image Configuration Tool; ValueType: string; ValueData: "0"
;Root: HKU; Subkey: S-1-5-21-839522115-484061587-725345543-1003\Software\Microsoft\DevStudio\6.0\AddIns\Dreamcast Image Configuration Tool; ValueType: string; ValueName: Description; ValueData: "This tool allows the developer to choose which components go into the Dreamcast Windows CE image, and build the BIN image.  It also provides the functionality to run an application automatically when the Windows CE OS boots up."
;Root: HKU; Subkey: S-1-5-21-839522115-484061587-725345543-1003\Software\Microsoft\DevStudio\6.0\AddIns\Dreamcast Image Configuration Tool; ValueType: string; ValueName: DisplayName; ValueData: "Dreamcast Image Configuration Tool"
;Root: HKU; Subkey: S-1-5-21-839522115-484061587-725345543-1003\Software\Microsoft\DevStudio\6.0\AddIns\Dreamcast Image Configuration Tool; ValueType: string; ValueName: Filename; ValueData: {app}\Tools\makeimgconfig.dll

// Page 38: 
[Run]
#ifdef USE_MODIFYREPAIRDELETE
Filename: {pf}\{#DRAGON_FIRM}\Setup\{#DRAGON_SHORT} {#DRAGON_TYPE} {#DRAGON_VER}{#DRAGON_REV}\UninsHs.exe; Parameters: /r; Flags: runminimized
#endif
; Installation de ASPI
Filename: {app}\Inst\Aspi\Install.bat; Parameters: X86; StatusMsg: Installing ASPI drivers for Windows 9x/Me/NT/2000...; Flags: waituntilterminated skipifdoesntexist; MinVersion: 4.0,4.0; OnlyBelowVersion: 0,5.01; Tasks: installaspi
Filename: {app}\Inst\Aspi\Install.bat; Parameters: XP32; StatusMsg: Installing ASPI drivers for Windows XP 32 bits...; Flags: waituntilterminated skipifdoesntexist; MinVersion: 0,5.01; Check: not Is64BitInstallMode; Tasks: installaspi
Filename: {app}\Inst\Aspi\Install.bat; Parameters: XP64; StatusMsg: Installing ASPI drivers for Windows XP 64 bits...; Flags: waituntilterminated skipifdoesntexist; MinVersion: 0,5.01; Check: Is64BitInstallMode; Tasks: installaspi
; Reflashage du débuggeur
Filename: {app}\Utl\Dev\DBFlash\runflash.bat; StatusMsg: Flashing the debugger...; Flags: waituntilterminated skipifdoesntexist; Tasks: flashdebug
; Démarrage du programme
;Filename: {app}\SetPaths.bat; Description: {cm:LaunchProgram,SetPaths.bat}; WorkingDir: {app}; Components: Libraries\SetPathsBat; Flags: postinstall skipifdoesntexist skipifsilent

// Page 38=: 
;[UninstallRun]

// Page 41: 
[UninstallDelete]
#ifdef USE_MODIFYREPAIRDELETE
Type: filesandordirs; Name: {pf}\{#DRAGON_FIRM}\Setup\{#DRAGON_SHORT} {#DRAGON_TYPE} {#DRAGON_VER}{#DRAGON_REV}\UninsHs.dat
#endif

; La section [Code] est à la fin et dans un fichier externe pour reprendre la structure de mon script InstallShield
// === CODE : SETUPDRAGON =============================================================================================

#include DRAGON_TOOLS+"\Setup"+DRAGON_SHORT+".isi"

// === INCLUDE ISSI ===================================================================================================: 

#include ISSI_IncludePath+"\_issi.isi"

// Putain qu'est ce que c'est bien InnoSetup, mais comment ais-je pu m'en passer aussi longtemps ?: 
