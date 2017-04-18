rem This batch file must be invoked from the directory containing the exe to be profiled.  If used from the IDE, do not change directories before running as a custom batch file.

rem Line count profiling takes more time than other modes.  See Help about limiting the scope of profiling if profiling a large application.

@rem off
prep /om /lv %1.exe
if errorlevel 1 goto done
profile %1 %2 %3 %4 %5 %6 %7 %8 %9
if errorlevel 1 goto done
prep /m %1
if errorlevel 1 goto done
plist %1
:done
