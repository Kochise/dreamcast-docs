@echo WinCE Dreamcast Command Line Environment (%1) (2.1.0.49)
@echo --------------------------------------------------------
@cd "%WCEDREAMCASTROOT%"
@tools\getsh4path >>setsh4path.bat
@call setsh4path.bat
@del setsh4path.bat

@if "%OS%"=="Windows_NT" goto setvcpath_nt
@set path="%COMPILER_LOCATION%;%NMAKE_LOCATION%;%NMAKE_LOCATION%\..\..\Common\MSDev98\Bin;%path%"
@set include="%WCEDREAMCASTROOT%\inc"
@set lib="%WCEDREAMCASTROOT%\lib\retail"
@goto settoolspath
:setvcpath_nt
@set path=%COMPILER_LOCATION%;%NMAKE_LOCATION%;%NMAKE_LOCATION%\..\..\Common\MSDev98\Bin;%path%
@set include=%WCEDREAMCASTROOT%\inc
@set lib=%WCEDREAMCASTROOT%\lib\retail

:settoolspath
@if "%OS%"=="Windows_NT" goto settoolspath_nt
@set path="%WCEDREAMCASTROOT%\tools;%WCEDREAMCASTROOT%\tools\GDWorkshop;%path%"
@goto settarget
:settoolspath_nt
@set path=%WCEDREAMCASTROOT%\tools;%WCEDREAMCASTROOT%\tools\GDWorkshop;%path%

:settarget
@set CEVersion=212
@set CESubsystem=windowsce,2.12
@set CEConfigName=Dreamcast
@call set_imginit
@set COUNTRY=USA
@set _HOSTCPUTYPE=i386
@set _PUBLICROOT=%WCEDREAMCASTROOT%
@set _DEPTREES=winceos gemini mcputech dshowdm6
@set _TGTPROJ=DRAGON
@set _FLATRELEASEDIR=%WCEDREAMCASTROOT%\release\%1
@echo _FLATRELEASEDIR=%_FLATRELEASEDIR%
@cd "%WCEDREAMCASTROOT%"
