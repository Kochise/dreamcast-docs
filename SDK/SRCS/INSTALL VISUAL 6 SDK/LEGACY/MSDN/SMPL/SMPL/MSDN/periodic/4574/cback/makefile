# makefile - Handy makefile for command-line use
#
# Usage:
#	nmake [options] [all|clean]
#
# Options:
#	WIN32=0		Build 16-bit version (default)
#	WIN32=1		Build 32-bit version
#	DEBUG=0		Build retail version
#	DEBUG=1		Build debug version (default)
#	UNICODE=0	Build ANSI/DBCS version (default)
#	UNICODE=1	Build Unicode version

!ifndef WIN32
WIN32=0
!endif

!ifndef UNICODE
UNICODE=0
!endif

!ifndef DEBUG
DEBUG=1
!endif

!if "$(WIN32)" == "1" 
!if "$(UNICODE)" == "1"
!if "$(DEBUG)" == "1"
all:
	nmake -f cback32.mak CFG="Win32 Unicode Debug"
clean:
	@-if exist objdu32\*.* echo y | erase objdu32\*.*
!else
all:
	nmake -f cback32.mak CFG="Win32 Unicode Release"
clean:
	@-if exist obju32\*.* echo y | erase obju32\*.* 
!endif
!else
!if "$(DEBUG)" == "1"
all:
	nmake -f cback32.mak CFG="Win32 ANSI Debug"
clean:
	@-if exist objd32\*.* echo y | erase objd32\*.*
!else
all:
	nmake -f cback32.mak CFG="Win32 ANSI Release"
clean:
	@-if exist obj32\*.* echo y | erase obj32\*.*
!endif
!endif
!else
all:
	nmake -f cback.mak DEBUG=$(DEBUG)
clean:
	@-if exist *.sbr erase *.sbr
	@-if exist *.pdb erase *.pdb
	@-if exist *.pch erase *.pch
	@-if exist *.obj erase *.obj
	@-if exist *.res erase *.res
	@-if exist *.dll erase *.dll
	@-if exist *.bsc erase *.bsc
	@-if exist *.lib erase *.lib
	@-if exist msvc.bnd erase msvc.bnd
	@-if exist tlb16\*.tlb erase tlb16\*.tlb
!endif

