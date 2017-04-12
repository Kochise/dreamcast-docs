@echo off
set help_dir=help
if "%1"=="" goto params
echo Building HTML Help Project %1.hhp
echo.
hhc %help_dir%\%1.hhp
if errorlevel 2 goto :Error
if not exist "%help_dir%\%1.chm" goto :Error
echo.
if exist Debug\nul   copy "%help_dir%\%1.chm" Debug
if exist Release\nul copy "%help_dir%\%1.chm" Release
echo.
goto :done

:Error
echo %1.hhp(1) : error: Problem encountered creating help file
goto :done

:Params
echo Syntax: %0 [projectname]

:done
set help_dir=
echo.
