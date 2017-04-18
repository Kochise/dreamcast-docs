
; ISSI EXAMPLE SCRIPT
;
; LOGAN's Inno Setup Script Includes (ISSI)
; http://www.albartus.com/issi/
;
; (c) 2005 Jan Albartus / LOGAN Interactive

[ISSI]
;; Set WizardSmallImageFile for each wpPage
#define ISSI_wpLicense "C:\ISSI\Wizard_Images\1_55x55.bmp"
;#define ISSI_wpSelectDir "C:\ISSI\Wizard_Images\2_55x55.bmp"
#define ISSI_wpSelectProgramGroup "C:\ISSI\Wizard_Images\3_55x55.bmp"
#define ISSI_wpReady "C:\ISSI\Wizard_Images\4_55x55.bmp"

;; All pages in order of appearance.. if activated
;#define ISSI_wpLicense "C:\ISSI\Wizard_Images\1_55x55.bmp"
;#define ISSI_wpPassword "C:\ISSI\Wizard_Images\1_55x55.bmp"
;#define ISSI_wpInfoBefore "C:\ISSI\Wizard_Images\3_55x55.bmp"
;#define ISSI_wpUserInfo "C:\ISSI\Wizard_Images\2_55x55.bmp"
;#define ISSI_wpSelectDir "C:\ISSI\Wizard_Images\1_55x55.bmp"
;#define ISSI_wpSelectComponents "C:\ISSI\Wizard_Images\4_55x55.bmp"
;#define ISSI_wpSelectProgramGroup "C:\ISSI\Wizard_Images\4_55x55.bmp"
;#define ISSI_wpSelectTasks "C:\ISSI\Wizard_Images\3_55x55.bmp"
;#define ISSI_wpReady "C:\ISSI\Wizard_Images\2_55x55.bmp"
;#define ISSI_wpPreparing "C:\ISSI\Wizard_Images\1_55x55.bmp"
;#define ISSI_wpInstalling "C:\ISSI\Wizard_Images\2_55x55.bmp"
;#define ISSI_wpInfoAfter "C:\ISSI\Wizard_Images\3_55x55.bmp"

; ISSI Iclude
#define ISSI_IncludePath "C:\ISSI"
#include ISSI_IncludePath+"\_issi.isi"

[Setup]
AppName=ISSI Example
AppVerName=ISSI Example v1.0
AppVersion=1.0
AppPublisher=LOGAN Interactive
AppPublisherURL=http://www.albartus.com
AppSupportURL=http://www.albartus.com
AppUpdatesURL=http://www.albartus.com
AppCopyright=Jan Albartus
DefaultDirName={pf}\ISSI\
outputBaseFileName=ISSI_WizardSmallImage_Switch
licensefile=license.txt


