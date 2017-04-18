@rem This batch file works around a problem with launching MSDEV from the
@rem command line, when you're in the _FLATRELEASEDIR.  The problem was 
@rem that it was picking up and trying to use the SH4 version of wininet.dll
@rem instead of the correct one in the %SystemRoot%\system32 directory.
@rem The workaround is to rename wininet.dll temporarily, launch MSDEV,
@rem and then rename it back.
@echo MSDEV.BAT is launching MSDEV (Microsoft Developer Studio) ... please wait.
@if exist wininet.dll goto rename_and_launch
@start msdev.exe %1 %2 %3 %4 %5
@goto finish
:rename_and_launch
@if exist wininet.sh4 del wininet.sh4
@rename wininet.dll wininet.sh4
@start msdev.exe %1 %2 %3 %4 %5
@sleep 5
@rename wininet.sh4 wininet.dll
:finish
