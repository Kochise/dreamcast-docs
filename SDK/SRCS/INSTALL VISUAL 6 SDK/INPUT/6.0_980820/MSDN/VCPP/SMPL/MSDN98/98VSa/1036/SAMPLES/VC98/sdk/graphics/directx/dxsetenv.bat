@REM		       Dxsetenv.bat
@REM
@REM This is used to Set your Environment for DirectX Build.
@REM
@REM **Please set the below set statements to match your environment.**


@REM set 32 bit C Compiler 
@REM **Please change the below line to point to your C Compiler Path.**
Set C32_ROOT=d:\devstudio\vc


@REM set DirectX SDK Path
@REM **Please change the below line to point to your DirectX SDK Path.**
Set DXSDKROOT=C:\dxsdk\sdk


@REM **Please Do not Change paths below.***

@REM This is used to set up your Include and Lib Paths.
Set path=%C32_ROOT%\bin;%path%
Set include=%DXSDKROOT%\include;%C32_ROOT%\include;%C32_ROOT%\mfc\include;%include%
Set lib=%DXSDKROOT%\lib;%C32_ROOT%\lib;%C32_ROOT%\mfc\lib;%lib%
