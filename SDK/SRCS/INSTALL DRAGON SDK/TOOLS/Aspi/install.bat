@echo off
REM ============================
REM Display Utility Instructions
REM ============================
IF (%1)==("") GOTO INSTRUCT

SET ERRORS=0

REM =================
REM Operating Systems
REM =================
IF (%1)==(X86)  GOTO X86
IF (%1)==(x86)  GOTO X86

IF (%1)==(XP32) GOTO XP32
IF (%1)==(xp32) GOTO XP32
IF (%1)==(Xp32) GOTO XP32
IF (%1)==(xP32) GOTO XP32

IF (%1)==(XP64) GOTO XP64
IF (%1)==(xp64) GOTO XP64
IF (%1)==(Xp64) GOTO XP64
IF (%1)==(xP64) GOTO XP64
GOTO INSTRUCT


REM =====================================
REM Display Menu for Command Line Options
REM =====================================
:INSTRUCT
ECHO "INSTALL.BAT <Operating System Type>"
ECHO "--------------------------------------"
ECHO "X86  - Microsoft Windows 98/ME/NT/2000"
ECHO "XP32 - Microsoft Windows XP X86"
ECHO "XP64 - Microsoft Windows XP Itanium"
PAUSE
GOTO END


REM =========================
REM For Windows 98/ME/NT/2000
REM =========================
:X86
ASPIINST.EXE
GOTO END


REM =====================================
REM For 32 bit Windows XP for X86 Systems
REM =====================================
:XP32
IF NOT EXIST REG_XP.EXE SET ERRORS=ERRORS+1
IF (%ERRORS%)==(5) ECHO "ERROR: Missing REG_XP.EXE"
IF NOT EXIST ASPIXP.SYS   SET ERRORS=ERRORS+1
IF (%ERRORS%)==(1) ECHO "ERROR: Missing ASPIXP.SYS File"
IF NOT EXIST WNASPIXP.DLL SET ERRORS=ERRORS+1
IF (%ERRORS%)==(2) ECHO "ERROR: Missing WNASPIXP.DLL File"
IF NOT %ERRORS%==0 GOTO END

CALL REG_XP.EXE
ECHO "Step 1 of 3 : REGISTRY MODIFIED FOR ASPI32"

COPY ASPIXP.SYS   %WINDIR%\SYSTEM32\DRIVERS\ASPI32.SYS /Y
ECHO "Step 2 of 3 : COPYING ASPI32.SYS"

COPY WNASPIXP.DLL %WINDIR%\SYSTEM32\WNASPI32.DLL /Y
ECHO "Step 3 of 3 : COPYING WNASPI32.DLL"
GOTO END


REM =========================================
REM For 64 bit Windows XP for Itanium Systems
REM =========================================
:XP64
IF NOT EXIST REG_XP.EXE SET ERRORS=ERRORS+1
IF (%ERRORS%)==(5) ECHO "ERROR: Missing REG_XP.EXE"
IF NOT EXIST ASPI64.SYS   SET ERRORS=ERRORS+1
IF (%ERRORS%)==(3) ECHO "ERROR: Missing ASPI64.SYS File"
IF NOT EXIST WNASPI64.DLL SET ERRORS=ERRORS+1
IF (%ERRORS%)==(4) ECHO "ERROR: Missing WNASPI64.DLL File"
IF NOT (%ERRORS%)==(0) GOTO END

CALL REG_XP.EXE
ECHO "Step 1 of 3 : REGISTRY MODIFIED FOR ASPI32"

COPY ASPI64.SYS %WINDIR%\SYSTEM32\DRIVERS\ASPI32.SYS /Y
ECHO "Step 2 of 3 : COPYING ASPI32.SYS"

COPY WNASPI64.DLL %WINDIR%\SYSTEM32\WNASPI32.DLL /Y
ECHO "Step 3 of 3 : COPYING WNASPI32.DLL"
GOTO END

:END
