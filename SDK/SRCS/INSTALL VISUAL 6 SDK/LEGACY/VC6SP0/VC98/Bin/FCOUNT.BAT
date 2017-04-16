@echo off
prep /om /fc %1.exe
if errorlevel 1 goto done
profile %1 %2 %3 %4 %5 %6 %7 %8 %9
if errorlevel 1 goto done
prep /m %1
if errorlevel 1 goto done
plist %1
:done
