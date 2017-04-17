
; ISSI EXAMPLE SCRIPT
;
; LOGAN's Inno Setup Script Includes (ISSI)
; http://www.albartus.com/issi/
;
; (c) 2005 Jan Albartus / LOGAN Interactive

;; This example shows you how to add a background image that switches on
;; predefined pages to a new bitmap image.

[ISSI]
;; Add background Image
#define ISSI_BackgroundImage "C:\ISSI\issi_example_Images\issi_800x600.bmp"
#define ISSI_ImageWpWelcome "C:\ISSI\issi_example_Images\issi_800x600.bmp"
#define ISSI_ImageWpSelectDir "C:\ISSI\Wizard_Images\1_55x55.bmp"
#define ISSI_ImageWpReady "C:\ISSI\issi_example_Images\issi_55x55.bmp"

;; All pages in order of appearance.. if activated
;#define ISSI_ImageWpLicense "C:\ISSI\Wizard_Images\1_55x55.bmp"
;#define ISSI_ImageWpPassword "C:\ISSI\Wizard_Images\2_55x55.bmp"
;#define ISSI_ImageWpInfoBefore "C:\ISSI\Wizard_Images\3_55x55.bmp"
;#define ISSI_ImageWpUserInfo "C:\ISSI\Wizard_Images\4_55x55.bmp"
;#define ISSI_ImageWpSelectDir "C:\ISSI\Wizard_Images\1_55x55.bmp"
;#define ISSI_ImageWpSelectComponents "C:\ISSI\Wizard_Images\2_55x55.bmp"
;#define ISSI_ImageWpSelectProgramGroup "C:\ISSI\Wizard_Images\3_55x55.bmp"
;#define ISSI_ImageWpSelectTasks "C:\ISSI\Wizard_Images\4_55x55.bmp"
;#define ISSI_ImageWpReady "C:\ISSI\Wizard_Images\1_55x55.bmp"
;#define ISSI_ImageWpPreparing "C:\ISSI\Wizard_Images\2_55x55.bmp"
;#define ISSI_ImageWpInstalling "C:\ISSI\Wizard_Images\3_55x55.bmp"
;#define ISSI_ImageWpInfoAfter "C:\ISSI\Wizard_Images\4_55x55.bmp"

;; OPTIONAL: Overrule the standard background color
;; clBlack (default), clMaroon, clGreen, clOlive, clNavy, clPurple, clTeal,
;; clGray, clSilver, clRed, clLime, clYellow, clBlue, clFuchsia, clAqua, clWhite.
;; OR:
;; value in the form of $bbggrr, where rr, gg, and bb specify the two-digit
;; intensities (in hexadecimal) for red, green, and blue respectively.
#define ISSI_BackgroundImage_BGColor "clWhite"

;; REQUIRED: Include ISSI
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
DefaultDirName={pf}\ISSI Test
;CreateAppDir=no
;CreateUninstallRegKey=no
;Uninstallable=no
outputBaseFileName=ISSI_Background_Image_Switch









