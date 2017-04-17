set CDTREE=%_FLATRELEASEDIR%\cd
if "%1" == "" goto aftercd
set CDTREE=%1
:aftercd
rmdir /s /q %CDTREE%
mkdir %CDTREE%

mkdir %CDTREE%\WinCE

@rem Needs to be filtered in the future
copy %_FLATRELEASEDIR%\0winceos.bin %CDTREE%
copy %_FLATRELEASEDIR%%RELEASEDIR_OS%*.dll %CDTREE%\WinCE
copy %_FLATRELEASEDIR%%RELEASEDIR_OS%*.exe %CDTREE%\WinCE
copy %_FLATRELEASEDIR%%RELEASEDIR_OS%*.ttf %CDTREE%\WinCE
copy %_FLATRELEASEDIR%%RELEASEDIR_OS%*.drv %CDTREE%\WinCE
copy %_FLATRELEASEDIR%%RELEASEDIR_OS%*.mpb %CDTREE%\WinCE
