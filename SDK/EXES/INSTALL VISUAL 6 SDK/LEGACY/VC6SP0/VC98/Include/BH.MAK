
#==============================================================================
#   Microsoft (R) Bloodhound (tm).
#
#   MODULE: bh.mak
#
#   Modification History
#
#   raypa                11/17/92        Created for Win32.
#   Tom MCConnell        02/04/93        Made it based on ntwin32.mak for portibility
#   raypa                02/12/93        Added BHDLL_LIBS macro.
#   Tom Laird-McConnell  11/15/93        Changed to use subsystem:native
#   Tom Laird-McConnell  11/17/93        Added Splitsym stuff
#   raypa                12/06/93        Partially rewrote for MIPS and ALPHA.
#   raypa                12/06/93        No longer include WIN32.MAK.
#   Tom Laird-McConnell  07/25/94        Rewrote to base it on ntwin32.mak for portibility
#==============================================================================

!include <ntwin32.mak>

#==============================================================================
#   This section verifies Bloodhound Build environment variables
#==============================================================================
!IFNDEF BH_ROOT
!ERROR BH_ROOT must be set to the root of the Bloodhound tree
!ENDIF

!IFNDEF BASEDIR
!ERROR BASEDIR must be set to the root of the DDK tree
!ENDIF

!IFNDEF CPU
!ERROR CPU must be set to a valid cpu (such as i386, MIPS, ALPHA)
!ENDIF

!IFNDEF BHVER
!ERROR BHVER must be set to the name of the build
!ENDIF

!IF "$(CPU)" == "i386"
!IFNDEF WIN4DDK
!ERROR WIN4DDK must be set to the root of the Win4 (Chicago) DDK directory
!ENDIF
!ENDIF

!IFNDEF TOOLS_TYPE
!ERROR TOOLS_TYPE must be set to MSTOOLS or MSVC as appropriate
!ENDIF

#==============================================================================
#   The following macros makes it easier to get at files in the tree.
#==============================================================================

BH_BUILD        = $(BH_ROOT)\build
BH_INCL         = $(BH_ROOT)\include
BH_BIN          = $(BH_ROOT)\bin
BH_LIB          = $(BH_ROOT)\lib

!IFDEF NT_528
BH_NTDDK        = $(BASEDIR)
!ELSE
BH_NTDDK        = $(BH_BASEDIR)
!ENDIF

#==============================================================================
#   The following are macros around the actual build tools.
#==============================================================================

library         = lib
implib          = lib
mapsym          = $(BH_BIN)\i386\mapsympe
LODCTR          = $(BH_BIN)\$(CPU)\lodctr.exe
UNLODCTR        = $(BH_BIN)\$(CPU)\unlodctr.exe

# these should be defined in ntwin32.mak
#link            = link
#rc              = rc
#cvtres          = cvtres
#hc              = hc
#mc              = mc

#==============================================================================
#   Our build environment dependent stuff
#==============================================================================
!IF "$(TOOLS_TYPE)" == "MSTOOLS"
CRTDLL_LIB = msvcrt.lib
!ELSE
#CRTDLL_LIB = MSVCRT.LIB
#stevehi: for 10a, force it to be crtdll.lib
CRTDLL_LIB = msvcrt.lib
!ENDIF

!IF DEFINED(LEGO) || DEFINED(FULLEGO)
!IF "$(TOOLS_TYPE)" == "MSTOOLS"
!ERROR You must use MSVC 2.0 for LEGO
!ENDIF
!IFNDEF NODEBUG
!ERROR You must define NODEBUG for LEGO
!ENDIF
!ENDIF

#==============================================================================
#   NDIS 3.0 driver for Windows NT
#==============================================================================

DRIVER_INCLUDES       = -I$(BH_ROOT)\include \
                        -I$(BH_NTDDK)\inc \
                        -I$(BH_NTDDK)\src\network\inc \
                        -I$(BH_NTDDK)\private\ntos\inc \
                        -I$(BH_NTDDK)\public\sdk\inc

DRIVER_COMMON_DEFINES = -DNDIS_NT \
                        -DCONDITION_HANDLING=1 \
                        -DWIN32_LEAN_AND_MEAN=1 \
                        -DNT_UP=1 \
                        -DNT_INST=0 \
                        -D_IDWBUILD \
!IFNDEF NODEBUG
                        -DDBG=1 \
!ELSE
                        -DDBG=0 \
!ENDIF
                        -DDEVL=1 \
                        -DNOFIREWALLS

!IFNDEF NODEBUG
DRIVER_DEBUG    = -DDEBUG
!ELSE
DRIVER_DEBUG    =
!ENDIF

DRIVER_PAGE_FLAG     = -DPAGED_CODE_ENABLED

DRIVER_COMMON_CFLAGS = -DMSINTERNAL -D_NTSDK $(DRIVER_PAGE_FLAG)

#==============================================================================
#   The following section handles Intel processor-dependent definitions.
#==============================================================================

!IF "$(CPU)" == "i386"

# we always want symbols on i386 builds
BUILD_SYMBOLS   = YES

BH_CPU          = -D_X86_=1

# Optional CFLAG overides for this platform
!IF "$(TOOLS_TYPE)" == "MSTOOLS"
# BUGBUG: With cl386 Version 8.0.3190a the optimizations in the compiler have bugs
# which break our code...we should try turning optimizations back on with a new compiler
# We assume that MSTOOLS is old compiler and VC20 is new compiler, and so override the
# optimization flags given us by NTWIN32.MAK
BH_OPTCFLAGS = -Od -Z7
!ELSE
BH_OPTCFLAGS = -Od -Z7
!ENDIF

#
# Platform dependent Driver defines
#
!IFDEF NT_528
NTDDK_LIBPATH   = $(BH_NTDDK)\lib\i386\free
!ELSE
NTDDK_LIBPATH   = $(BH_NTDDK)\lib\i386
!ENDIF

!IFDEF NTBUILD_TREE 
NTDDK_LIBPATH   = $(BH_NTDDK)\public\sdk\lib\i386
!ENDIF

DRIVER_ENTRY    = DriverEntry@8
DRIVER_DEFINES  = $(DRIVER_COMMON_DEFINES) $(DRIVER_DEBUG) -D_X86_=1 -Di386=1 -DSTD_CALL
DRIVER_CFLAGS   = $(DRIVER_COMMON_CFLAGS) $(DRIVER_INCLUDES) $(DRIVER_DEFINES) -nologo -c -Zel -Zp8 -W3 -Gz -H63 -G4 -Ogitb1
DRIVER_LIBS     = $(NTDDK_LIBPATH)\ntoskrnl.lib \
                  $(NTDDK_LIBPATH)\libcntpr.lib \
                  $(NTDDK_LIBPATH)\hal.lib \
                  $(NTDDK_LIBPATH)\ndis.lib

#
# LEGO STUFF
#
!IF DEFINED(LEGO) || DEFINED(FULLLEGO)
path=$(BH_ROOT)\lego\tools\x86;$(PATH)
!ENDIF

!IF DEFINED(FULLEGO)
Lib=$(BH_ROOT)\lego\msvc20.lib\x86;$(LIB)
!ENDIF

!ENDIF

#==============================================================================
#   The following section handles Mips processor-dependent definitions.
#==============================================================================

!IF "$(CPU)" == "MIPS"

BH_CPU          = -D_MIPS_=1

# Optional CFLAG overides for this platform
BH_OPTCFLAGS = -Z7

#
# Platform dependent Driver defines
#
!IFDEF NT_528
NTDDK_LIBPATH   = $(BH_NTDDK)\lib\mips\free
!ELSE
NTDDK_LIBPATH   = $(BH_NTDDK)\lib\mips
!ENDIF

DRIVER_ENTRY    = DriverEntry
DRIVER_DEFINES  = $(DRIVER_COMMON_DEFINES) $(DRIVER_DEBUG) -DMIPS=1 -D_MIPS_=1 -DNO_EXT_KEYS -DMIPSEL -DR4000 -D_M_MRX000=4000 -DBETA=0 -D__stdcall= -D__cdecl=
DRIVER_CFLAGS   = $(DRIVER_COMMON_CFLAGS) $(DRIVER_INCLUDES) $(DRIVER_DEFINES) -nologo -c -W3 -Ox -QmipsOb2000 -Gt0
DRIVER_LIBS     = $(NTDDK_LIBPATH)\ntoskrnl.lib $(NTDDK_LIBPATH)\hal.lib $(NTDDK_LIBPATH)\ndis.lib

#
# LEGO STUFF
#
!IF DEFINED(LEGO) || DEFINED(FULLLEGO)
!ERROR Lego is only valid for x86
!ENDIF

!ENDIF

#==============================================================================
#   The following section handles Mips processor-dependent definitions.
#==============================================================================

!IF "$(CPU)" == "PPC"

BH_CPU          = -D_PPC_=1

# Optional CFLAG overides for this platform
BH_OPTCFLAGS = -Z7

#
# Platform dependent Driver defines
#
!IFDEF NT_528
NTDDK_LIBPATH   = $(BH_NTDDK)\lib\ppc\free
!ELSE
NTDDK_LIBPATH   = $(BH_NTDDK)\lib\ppc
!ENDIF

!IFDEF NTBUILD_TREE
NTDDK_LIBPATH	= $(BH_NTDDK)\public\sdk\lib\ppc
!ENDIF


DRIVER_ENTRY    = DriverEntry
DRIVER_DEFINES  = $(DRIVER_COMMON_DEFINES) $(DRIVER_DEBUG) -DPPC=1 -D_PPC_=1 -DNO_EXT_KEYS -DBETA=0 -D__stdcall= -D__cdecl=
DRIVER_CFLAGS   = $(DRIVER_COMMON_CFLAGS) $(DRIVER_INCLUDES) $(DRIVER_DEFINES) -nologo -c -W3 -Ox
DRIVER_LIBS     = $(NTDDK_LIBPATH)\ntoskrnl.lib $(NTDDK_LIBPATH)\hal.lib $(NTDDK_LIBPATH)\ndis.lib

#
# LEGO STUFF
#
!IF DEFINED(LEGO) || DEFINED(FULLLEGO)
!ERROR Lego is only valid for x86
!ENDIF

!ENDIF

#==============================================================================
#   The following section handles ALPHA processor-dependent definitions.
#==============================================================================

!IF "$(CPU)" == "ALPHA"

BH_CPU          = -D_ALPHA_=1

# Optional CFLAG overides for this platform
BH_OPTCFLAGS = -Z7

#
# Platform dependent Driver defines
#
!IFDEF NT_528
NTDDK_LIBPATH   = $(BH_NTDDK)\lib\alpha\free
!ELSE
NTDDK_LIBPATH   = $(BH_NTDDK)\lib\alpha
!ENDIF

DRIVER_ENTRY    = DriverEntry
DRIVER_DEFINES  = $(DRIVER_DEBUG) -DALPHA=1 -D_ALPHA_=1 -DNO_EXT_KEYS -DWIN32_LEAN_AND_MEAN=1 \
                  -DCONDITION_HANDLING=1 -DNT_INST=0 -DNT_UP=1 -DDBG=0 -DDEVL=1 -DBETA=0 \
                  -DNOFIREWALLS -D__stdcall= -D_cdecl= -D__cdecl= -Dcdecl=

DRIVER_CFLAGS   = $(DRIVER_COMMON_CFLAGS) $(DRIVER_INCLUDES) $(DRIVER_DEFINES) -nologo /c /W3 /Ox -d2"switch no*check*" -d2"switch mscdev"

DRIVER_LIBS     = $(NTDDK_LIBPATH)\ntoskrnl.lib \
                  $(NTDDK_LIBPATH)\libcntpr.lib \
                  $(NTDDK_LIBPATH)\hal.lib \
                  $(NTDDK_LIBPATH)\ndis.lib

#
# LEGO STUFF
#
!IF DEFINED(LEGO) || DEFINED(FULLLEGO)
!ERROR Lego is only valid for x86
!ENDIF

!ENDIF

#==============================================================================
#   No processor type has been defined.
#==============================================================================

!IFNDEF CPU
!ERROR  Must specify CPU environment variable (CPU=i386 or CPU=MIPS)!
!ENDIF

#==============================================================================
#   Common macros for Bloodhound projects.
#==============================================================================

!IFNDEF NODEBUG

CHECKMEM        = 1
DOCHECKMEM      = -DCHECKMEM
BH_CDEBUG       = $(cdebug) -DDEBUG

!ELSE

CHECKMEM        =
DOCHECKMEM      =
BH_CDEBUG       = $(cdebug)

!ENDIF

#
# optional debug flags, particularly for LEGO
#
!IF !DEFINED(LEGO) && !DEFINED(FULLLEGO)
# this is the normal ntwin32.mak debug flags, with symbol generation
# always turned on
BH_LDEBUG       = $(ldebug) -debug:full -debugtype:both
!ELSE
# these are the LEGO flags
BH_LDEBUG       = -debug -debugtype:both,fixup /opt:ref
BH_CDEBUG       = $(BH_CDEBUG) -Gy
!ENDIF

BH_SUBSYSTEM    = WINDOWS

#
# Compiler FLAGS
#
# Note we override to always generate symbolic information, as we always use splitsym
# and we optional override with BH_OPFLAGS for optimization bugs in compilers
#
BH_CFLAGS       = $(cflags) $(cvarsdll) $(BH_CDEBUG) $(BH_OPTCFLAGS) \
!IFNDEF SMS
                  -DNTAS_ONLY \
!ENDIF
                  -D_NTSDK -nologo -WX -I$(BH_INCL)
#                  -D_NTSDK -nologo     -I$(BH_INCL)

#
# LINK FLAGS
#
BH_LFLAGS       = $(lflags) $(BH_LDEBUG) -machine:$(CPU) -MAP:$*.map

#
# Lib Flags
#
BH_LIBFLAGS     = -machine:$(CPU)

#
# DLL Link Flags
#
BHDLL_LFLAGS    = $(BH_LFLAGS) -entry:DLLEntry$(DLLENTRY) -dll

#
# Executable Libraries
#
BH_LIBS      	= $(CRTDLL_LIB) $(winlibs)
#stevehi force crtdll instead of msvcrt.dll
#BH_LIBS = $(guilibsdll)

#
# DLL Libraries
#
#BHDLL_LIBS      = $(guilibsdll)
# stevehi force crtdll instead of msvcrt.dll
BHDLL_LIBS      	= $(CRTDLL_LIB) $(winlibs)

BH_LIBS      	= $(BH_LIBS) $(BH_BUILD)\dbcs.lib
BHDLL_LIBS      = $(BHDLL_LIBS) $(BH_BUILD)\dbcs.lib


DRIVER_LFLAGS   = -out:nt\bhnt.sys \
                  -debug:MINIMAL \
                  -debugtype:coff \
                  -machine:$(CPU) \
                  -align:0x200 \
                  -subsystem:native \
                  -debug:notmapped \
                  -debugtype:coff \
                  -base:0x10000 \
                  -entry:$(DRIVER_ENTRY)

BH_COMMON       = $(BH_INCL)\nal.h \
                  $(BH_INCL)\bh.h \
                  $(BH_INCL)\bhtypes.h \
                  $(BH_INCL)\buffer.h \
                  $(BH_INCL)\frame.h \
                  $(BH_INCL)\parser.h \
                  $(BH_INCL)\bherr.h
