@echo off

cd "INPUT\6.0_980820\MSDN\OTHER\DOC\MSDN98\98VSa\1036"

if exist "KB.CHM.001" (
    if not exist "KB.CHM" (
        copy /b "KB.CHM.001"+"KB.CHM.002"+"KB.CHM.003" "KB.CHM" 1>nul 2>nul
    )

    del "KB.CHM.001" /q 1>nul 2>nul
	del "KB.CHM.002" /q 1>nul 2>nul
	del "KB.CHM.003" /q 1>nul 2>nul
)

cd "..\..\..\..\..\..\..\.."

@echo on

".\TOOLS\Inno Setup 5\ISCC.exe" "Visual C++ 6.0.iss"
