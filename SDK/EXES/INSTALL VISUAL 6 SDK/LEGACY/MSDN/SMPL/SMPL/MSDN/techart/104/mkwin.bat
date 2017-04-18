REM Compile DLL
cl -c -ALw -GD -G2s -W3 trace.c 

REM Link DLL
link /NOD /NOE trace.obj,trace.dll,,libw ldllcew,trace.def

REM Build DLL Import Library
implib trace.lib trace.dll

REM Compile App
cl -c -AL -GA -G2s -W3 back.c

REM LINK APP
link /NOD /NOE back.obj,back.exe,,libw llibcew trace,back.def


