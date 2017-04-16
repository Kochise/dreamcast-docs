#############################################################################
#                                                                           #
# DirectShow SDK Master Makefile - ACTIVEX.MAK                              #
#                                                                           #
# Win32 application master NMAKE definitions file for the Microsoft         #
# DirectShow 5.1 for Windows programming samples.                           #
#                                                                           #
# THIS CODE AND INFORMATION IS PROVIDED "AS IS" WITHOUT WARRANTY OF ANY     #
# KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE       #
# IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A PARTICULAR     #
# PURPOSE.                                                                  #
#                                                                           #
# Copyright 1992 - 1998 Microsoft Corporation.  All Rights Reserved.    #
#                                                                           #
# ------------------------------------------------------------------------- #
# This files should be included after all public macro definitions          #
# and before any private targets (so that the default "all" and "clean"     #
# targets are not accidentally overridden. )                                #
#                                                                           #
# e.g.                                                                      #
#                                                                           #
# TARGET_NAME = filter                                                      #
# TARGET_TYPE = DYNLINK                                                     #
#                                                                           #
# SRC_FILES   = file1.cpp \                                                 #
#               file2.cpp \                                                 #
#               file3.c                                                     #
#                                                                           #
# RC_FILE     = filter.rc                                                   #
#                                                                           #
# DEF_FILE    = filter.def                                                  #
#                                                                           #
# END_TASK    = assorted_stuff                                              #
#                                                                           #
# !include "activex.mak"                                     #
#                                                                           #
# assorted_stuff:                                                           #
#   do_this                                                                 #
#   do_that                                                                 #
#   do_the_other                                                            #
#                                                                           #
# ------------------------------------------------------------------------- #
# NMAKE Options (passed by macro)                                           #
#                                                                           #
# Use the table below to determine the additional options for NMAKE to      #
# generate various application debugging, profiling and performance tuning  #
# information.                                                              #
#                                                                           #
# Application Information Type         Invoke NMAKE                         #
# ----------------------------         ------------                         #
# For No Debugging Info                nmake nodebug=1                      #
# For debuggable retail build          nmake nodebug=1 symbols=1            #
# For performance tuning               nmake nodebug=1 perf=1               #
#                                                                           #
# Note: creating the environment variables NODEBUG and PERF is an           #
#       alternative method to setting these options via the nmake           #
#       command line.                                                       #
#                                                                           #
#       perf=1 overrides symbols=1                                          #
#                                                                           #
# Additional NMAKE Options             Invoke NMAKE                         #
# ----------------------------         ------------                         #
# For No ANSI NULL Compliance          nmake no_ansi=1                      #
# (ANSI NULL is defined as PVOID 0)                                         #
#                                                                           #
# Set SYM_FILES=1 in the nmake command line to generate .sym files that     #
# can be used with a kernel level debugger.                                 #
#                                                                           #
# ------------------------------------------------------------------------- #
# NMAKE Targets (common)                                                    #
#                                                                           #
# all           Create executables (default).                               #
# clean         Delete object files, etc.                                   #
#                                                                           #
# Note: use "nmake clean all" to force a clean rebuild.                     #
#                                                                           #
#############################################################################

DISABLE_PCH = 1
NO_COMMON_PCH = 1
NO_PDB_FILES = 1

# START OF MAKEFILE
!IFNDEF _ACTIVEX_MAK_
_ACTIVEX_MAK_ = 1

#----------------------------------------------------------------------------
# recover environment

!ifndef MAKE_ENV
MAKE_ENV = $(MAKEDIR)\~qmakenv.tmp
!endif

!ifndef MAKE_PASS
MAKE_PASS = pass1
!else
!if exist( "$(MAKE_ENV)" )
!include "$(MAKE_ENV)"
!endif
!endif

#----------------------------------------------------------------------------
# Logging

!ifndef MAKE_LOG
MAKE_LOG = $(MAKEDIR)\make.log
!endif

!ifndef MAKE_ECHO
!if "$(OS)" == "Windows_NT"
MAKE_ECHO = $(MAKEDIR)\~qmakech.tmp 2>>&1
!else
MAKE_ECHO = $(MAKEDIR)\~qmakech.tmp
!endif
!endif

!ifndef ECHO_ECHO
ECHO_ECHO = type $(MAKEDIR)\~qmakech.tmp
!endif

!ifndef TYPE_ECHO
!if "$(MAKE_LOGGING)" == "quiet"
TYPE_ECHO = rem
!else
TYPE_ECHO = $(ECHO_ECHO)
!endif
!endif

!ifndef TYPE_ECHO2
!if "$(MAKE_LOGGING)" == "verbose"
TYPE_ECHO2 = $(ECHO_ECHO)
!else
TYPE_ECHO2 = rem
!endif
!endif

!ifndef FILE_ECHO
!ifdef NO_MAKE_LOG
FILE_ECHO = rem
!else
FILE_ECHO = $(ECHO_ECHO) >> $(MAKE_LOG)
!endif
!endif

!ifndef MAKE_CMD
MAKE_CMD = $(MAKEDIR)\~qmakcmd.bat
!endif

#----------------------------------------------------------------------------
# Set up object directory

!ifdef RETAIL
!ifndef NODEBUG
NODEBUG = 1
!endif
!endif

!ifdef DEBUG
!ifdef NODEBUG
!undef NODEBUG
!endif
!endif

!ifdef NODEBUG
DBG_RTL = retail
!else
DBG_RTL = debug
!endif

#----------------------------------------------------------------------------
# resolve pdb/pch clash

!ifndef DISABLE_PCH
!ifndef NO_PDB_FILES
NO_PDB_FILES = 1
!endif
!endif


# BINARY/DIRECTORY
!IFNDEF DIR_LIST

#============================================================================
#
# BINARY
#
#============================================================================

#
# if DIR_LIST is *not* defined this makefile just
# simply must be being included to build a binary
#

#----------------------------------------------------------------------------
# Backward compat section

!if "$(DEP_LIBS)" != ""
!message Should now be using CODE_LIBS instead of DEP_LIBS!!
CODE_LIBS = $(CODE_LIBS) $(DEP_LIBS)
!endif

#----------------------------------------------------------------------------
# Default handling

!ifdef NO_ACTIVEX_DEFAULTS
!ifndef NO_ACTIVEX_LIBS
NO_ACTIVEX_LIBS = 1
!endif
!ifndef NO_ACTIVEX_INCLUDES
NO_ACTIVEX_INCLUDES = 1
!endif
!endif

#----------------------------------------------------------------------------
# set CPU Type

!IF "$(CPU)" != "i386"
!IF "$(CPU)" != "MIPS"
!IF "$(CPU)" != "ALPHA"
!IF "$(CPU)" != "PPC"
!MESSAGE Missing or invalid 'CPU' environment variable
!MESSAGE ( valid options are CPU=i386, MIPS, ALPHA or PPC )
!MESSAGE
!MESSAGE WARNING: Defaulting to CPU=i386!
!MESSAGE
CPU = i386
!ENDIF
!ENDIF
!ENDIF
!ENDIF

#----------------------------------------------------------------------------
# set Target Operating System - Default to both

!IF "$(TARGET_OS)" != "WINNT"
!IF "$(TARGET_OS)" != "WIN95"
!IF "$(TARGET_OS)" != "BOTH"
#!MESSAGE Must specify TARGET_OS environment variable (BOTH, WIN95, WINNT)
TARGET_OS = BOTH
!ENDIF
!ENDIF
!ENDIF

#----------------------------------------------------------------------------
# Set Default WINVER - depends on TARGET_OS
# Defaults to 4.0 for all applications except NT specific.

!IFNDEF WIN_VER
!IF "$(TARGET_OS)" == "WINNT"
WIN_VER = 5.0
!ELSE
WIN_VER = 4.0
!ENDIF
!ENDIF

!IF "$(WIN_VER)" != "5.0"
!IF "$(WIN_VER)" != "4.0"
!ERROR Must specify WIN_VER environment variable (5.0, 4.0)
!ENDIF
!ENDIF
!ENDIF

#----------------------------------------------------------------------------
# Check TARGET_TYPE defined

!if "$(TARGET_TYPE)" != "DYNLINK"
!if "$(TARGET_TYPE)" != "LIBRARY"
!if "$(TARGET_TYPE)" != "PROGRAM"
!error Must define TARGET_TYPE
!endif
!endif
!endif

#----------------------------------------------------------------------------
# Define EXT if not already done

!if "$(TARGET_EXT)" == ""
!if "$(TARGET_TYPE)" == "DYNLINK"
TARGET_EXT = dll
!elseif "$(TARGET_TYPE)" == "LIBRARY"
TARGET_EXT = lib
!elseif "$(TARGET_TYPE)" == "PROGRAM"
TARGET_EXT = exe
!endif
!endif

#----------------------------------------------------------------------------
# Define targets

!if "$(TARGET_TYPE)" == "DYNLINK"
TARGET_LIB = $(DBG_RTL)\$(TARGET_NAME).lib
TARGET_BIN = $(DBG_RTL)\$(TARGET_NAME).$(TARGET_EXT)
!ifndef TARGET_MAP
TARGET_MAP = $(DBG_RTL)\$(TARGET_NAME).map
!endif
!if "$(DEF_FILE)" != ""
TARGET_EXP = $(DBG_RTL)\$(TARGET_NAME).exp
!else
TARGET_EXP =
!endif
!elseif "$(TARGET_TYPE)" == "LIBRARY"
TARGET_LIB = $(DBG_RTL)\$(TARGET_NAME).$(TARGET_EXT)
TARGET_BIN =
TARGET_MAP =
TARGET_EXP =
!elseif "$(TARGET_TYPE)" == "PROGRAM"
TARGET_LIB =
TARGET_BIN = $(DBG_RTL)\$(TARGET_NAME).$(TARGET_EXT)
!ifndef TARGET_MAP
TARGET_MAP = $(DBG_RTL)\$(TARGET_NAME).map
!endif
TARGET_EXP =
!else
TARGET_LIB =
TARGET_BIN =
TARGET_MAP =
TARGET_EXP =
!endif

#----------------------------------------------------------------------------
# Define copy targets

!ifndef NO_COPY

!if "$(TARGET_LIB)" != ""
TARGET_LIB_GOAL = $(MSSDK)\samples\graphics\directshow\$(TARGET_NAME)\lib\$(DBG_RTL)
!ifndef NODEBUG
GOAL_LIB = $(TARGET_LIB_GOAL)\$(TARGET_LIB:debug\=)
!else
GOAL_LIB = $(TARGET_LIB_GOAL)\$(TARGET_LIB:retail\=)
!endif
!endif

!if "$(TARGET_BIN)" != ""
TARGET_BIN_GOAL = $(MSSDK)\samples\graphics\directshow\$(TARGET_NAME)
!ifndef NODEBUG
GOAL_BIN = $(TARGET_BIN_GOAL)\$(TARGET_BIN:debug\=)
!else
GOAL_BIN = $(TARGET_BIN_GOAL)\$(TARGET_BIN:retail\=)
!endif
!endif

!endif

#----------------------------------------------------------------------------
# Tool aliases

cc     = cl
rc     = rc
link   = link
implib = lib
hc     = hcrtf -x
mtl    = mktyplib

#----------------------------------------------------------------------------
# general defs

!IFDEF NO_ANSI
noansi = -DNULL=0
!ENDIF

#----------------------------------------------------------------------------
# compiler flags

ccommon = -c -nologo -Gy -DINC_OLE2 -DSTRICT  \
          -DWIN32 -D_WIN32 $(noansi)

# !ifdef USE_MSVCRT_LIB
!ifndef USE_LIBCMT_LIB

!ifdef NODEBUG
ccommon = $(ccommon) -MD
!else
!ifdef USE_MSVC20
ccommon = $(ccommon) -MD
!else
ccommon = $(ccommon) -MDd
!endif
!endif

!else

!ifdef NODEBUG
ccommon = $(ccommon) -MT
!else
!ifdef USE_MSVC20
ccommon = $(ccommon) -MT
!else
ccommon = $(ccommon) -MTd
!endif
!endif

!endif

!ifndef ACTIVEX_NO_MT
ccommon = $(ccommon) -D_MT
!endif

# !ifdef USE_MSVCRT_LIB
!ifndef USE_LIBCMT_LIB
!if "$(TARGET_TYPE)" == "DYNLINK"
ccommon = $(ccommon) -D_DLL
!endif
!endif

!IF "$(CPU)" == "i386"
ccommon = $(ccommon) -D_X86_=1
!ELSE
!IF "$(CPU)" == "MIPS"
ccommon = $(ccommon) -D_MIPS_=1
!ELSE
!IF "$(CPU)" == "PPC"
ccommon = $(ccommon) -D_PPC_=1
!ELSE
!IF "$(CPU)" == "ALPHA"
ccommon = $(ccommon) -D_ALPHA_=1
!ENDIF
!ENDIF
!ENDIF
!ENDIF

!IF "$(TARGET_OS)" == "WINNT"
ccommon = $(ccommon) -D_WINNT
!ELSE
!IF "$(TARGET_OS)" == "WIN95"
ccommon = $(ccommon) -D_WIN95
!ENDIF
!ENDIF

!IF "$(WIN_VER)" == "5.0"
ccommon = $(ccommon) -DWINVER=0x0500
!ELSE
!IF "$(WIN_VER)" == "4.0"
ccommon = $(ccommon) -DWINVER=0x0400
!ENDIF
!ENDIF

# debug

!ifdef NODEBUG
cdebug = -DDBG=0
!else
!ifdef NODEBUGCODE
cdebug = -DDBG=0
!else
cdebug = -DDBG=1 -DDEBUG -D_DEBUG
!endif
!endif

!ifdef PERF
cdebug = $(cdebug) -DPERF
!endif

!ifdef USE_LEGO
cdebug = $(cdebug) -Zi
!else
!ifdef C_DEBUG
cdebug = $(cdebug) $(C_DEBUG)
!else
!IFDEF NODEBUG
!ifdef SYMBOLS
cdebug = $(cdebug) -Zd
!endif
!ELSE
!ifdef NO_PDB_FILES
cdebug = $(cdebug) -Z7
!else
cdebug = $(cdebug) -Zi
!endif
!ENDIF
!endif
!endif

!ifndef NO_PDB_FILES
cdebug = $(cdebug) -Fd$(DBG_RTL)\$(TARGET_NAME).pdb
!endif

# optimization

!ifdef C_OPTIMIZATION
cdebug = $(cdebug) $(C_OPTIMIZATION)
!else
!IFDEF NODEBUG
!IFDEF PERF
cdebug = $(cdebug) -Ois -GF
!ELSE
cdebug = $(cdebug) -Oxs -GF
!ENDIF
!ELSE
cdebug = $(cdebug) -Oid
!ENDIF
!endif

# calling convention (Intel only)
# - default to stdcall

!IF "$(CPU)" == "i386"
!if "$(C_CALL)" == "cdecl"
ccall = -Gd
!else
ccall = -Gz
!endif
!ELSE
ccall =
!ENDIF

# warning level
# - defaults to level 3

!ifndef C_WARNING
cwarn = -W3
!else
cwarn = $(C_WARNING)
!endif

# exception handling
# - default to standard WIN32
# - can override to use C++ exceptions

!ifdef CPP_EXCEPTION_HANDLING
cexcept = -GX -D_INC_EXCPT
!else
cexcept = -Dtry=__try -Dexcept=__except -Dleave=__leave -Dfinally=__finally
!endif

# combine flags

cflags   = $(ccommon) $(cdebug) $(ccall) $(cexcept) $(cwarn) $(C_DEFINES)

#----------------------------------------------------------------------------
# resource compiler flags

rccommon = -l409 -r -DWIN32 -D_WIN32 $(noansi)

!IF "$(WIN_VER)" == "5.0"
rccommon = $(rccommon) -DWINVER=0x0500
!else
rccommon = $(rccommon) -DWINVER=0x0400
!ENDIF

!ifdef NODEBUG
rcdebug = -DDBG=0
!else
rcdebug = -DDBG=1 -DDEBUG -D_DEBUG
!endif

rcflags = $(rccommon) $(rcdebug) $(RC_DEFINES)

#----------------------------------------------------------------------------
# library flags

# common stuff

libcommon = /NODEFAULTLIB /machine:$(CPU)

# debug type = coff|cv|both

!ifdef USE_LEGO
libdebug = -debugtype:cv,fixup
!else
!ifdef NODEBUG
!ifdef SYMBOLS
libdebug = -debugtype:coff
!endif
!else
libdebug = -debugtype:cv
!endif
!endif

# subsystem, def file, etc. switched
# in according to TARGET_TYPE and EXE_TYPE

!if "$(TARGET_TYPE)" == "DYNLINK"
liblink = /subsystem:windows,$(WIN_VER)
!if "$(DEF_FILE)" != ""
liblink = $(liblink) /def:$(DEF_FILE)
!endif
!else
!if "$(TARGET_TYPE)" == "PROGRAM"
!if "$(EXE_TYPE)" == "console"
liblink = /subsystem:console,$(WIN_VER)
!else
!if "$(EXE_TYPE)" == "windows"
liblink = /subsystem:windows,$(WIN_VER)
!else
!error EXE_TYPE=console|windows must be defined for PROGRAM
!endif
!endif
!else
liblink = /subsystem:windows,$(WIN_VER)
!endif
!endif

libflags = $(libcommon) $(liblink) $(libdebug)

#----------------------------------------------------------------------------
# linker flags

!ifdef USE_DEFAULT_LIB
DEFAULTLIBSWITCH = /NODEFAULTLIB:MSVCRT
!else
DEFAULTLIBSWITCH = /NODEFAULTLIB
!endif

lcommon = $(DEFAULTLIBSWITCH) /INCREMENTAL:NO /NOLOGO /MACHINE:$(CPU)

!ifdef NO_PDB_FILES
lcommon = $(lcommon) /PDB:NONE
!else
lcommon = $(lcommon) /PDB:$(DBG_RTL)\$(TARGET_NAME).pdb
!endif

# declarations for use on Intel i386, i486, and Pentium systems
!IF "$(CPU)" == "i386"
DLLENTRY = @12
lcommon  = $(lcommon) /align:0x1000
!ENDIF

# declarations for use on self hosted MIPS R4x000 systems
!IF "$(CPU)" == "MIPS"
DLLENTRY =
lcommon  = $(lcommon)
!ENDIF

# declarations for use on self hosted PowerPC systems
!IF "$(CPU)" == "PPC"
DLLENTRY =
lcommon  = $(lcommon)
!ENDIF

# declarations for use on self hosted Digital Alpha AXP systems
!IF "$(CPU)" == "ALPHA"
DLLENTRY =
lcommon  = $(lcommon)
!ENDIF

# NODEBUG means a retail build
# PERF is a special case of retail:
#  == retail plus performance stuff

!ifndef DEBUG_TYPE
DEBUG_TYPE = both
!endif

!ifdef USE_LEGO
ldebug = /OPT:REF /RELEASE /debug /debugtype:cv,fixup
!else
!IFDEF NODEBUG
!IFDEF PERF
ldebug = /OPT:REF /RELEASE /debug:mapped,minimal /debugtype:$(DEBUG_TYPE)
!ELSE
!ifdef SYMBOLS
ldebug = /OPT:REF /RELEASE /debug:mapped,minimal /debugtype:$(DEBUG_TYPE)
!else
ldebug = /OPT:REF /RELEASE /debug:none
!endif
!ENDIF
!ELSE
ldebug = /debug:mapped,full /debugtype:$(DEBUG_TYPE)
!ENDIF
!endif

!if "$(TARGET_TYPE)" == "DYNLINK"
!ifndef DLL_BASE
DLL_BASE = 0x1c400000
!endif
llink = /dll /base:$(DLL_BASE) /subsystem:windows,$(WIN_VER)
!if "$(DEF_FILE)" != ""
llink = $(llink)
TARGET_EXP = $(DBG_RTL)\$(TARGET_NAME).exp
!endif
!if "$(DLL_ENTRY)" != ""
!if "$(DLL_ENTRY)" != "none"
llink = $(llink) /entry:$(DLL_ENTRY)$(DLLENTRY)
!endif
!else
llink = $(llink) /entry:DllEntryPoint$(DLLENTRY)
!endif
!else
!if "$(TARGET_TYPE)" == "PROGRAM"
!if "$(EXE_TYPE)" == "console"
llink = /subsystem:console,$(WIN_VER) /entry:mainCRTStartup
!else
!if "$(EXE_TYPE)" == "windows"
llink = /subsystem:windows,$(WIN_VER) /entry:WinMainCRTStartup
!endif
!endif
!endif
!endif

lflags = $(lcommon) $(ldebug) $(llink)

#----------------------------------------------------------------------------
# make type library flags

mtlflags = /nologo $(MTL_DEFINES)

#----------------------------------------------------------------------------
# unicode flags

!ifdef UNICODE
cflags  = $(cflags)  -DUNICODE
rcflags = $(rcflags) -DUNICODE
!endif

#----------------------------------------------------------------------------
# Include path

!ifndef NO_ACTIVEX_INCLUDES
INC_PATH = .;                       \
           $(MSSDK)\include;        \
           $(MSTOOLS)\include;      \
           $(MSSDK)\samples\graphics\DirectShow\classes\base;   \
           $(MSTOOLS)\samples\graphics\DirectShow\classes\base; \
           $(INC_PATH)
!endif

!if "$(INC_PATH)" != ""
INC_FLAGS = $(INC_PATH: =)***
INC_FLAGS = $(INC_FLAGS:;***=)
INC_FLAGS = $(INC_FLAGS:***=)
INC_FLAGS = -I$(INC_FLAGS:;= -I)
!endif

#----------------------------------------------------------------------------
# Next work out what obj files need to be built from
# the list of source files

!if "$(SRC_FILES)" != ""
OBJ_FILES = $(SRC_FILES)
OBJ_FILES = $(OBJ_FILES:.cpp =.cpp*)
OBJ_FILES = $(OBJ_FILES:.c =.c*)
OBJ_FILES = $(OBJ_FILES: =)
!if "$(DBG_RTL)" == "retail"
OBJ_FILES = retail\$(OBJ_FILES:*= retail\)
!else
OBJ_FILES = debug\$(OBJ_FILES:*= debug\)
!endif
OBJ_FILES = $(OBJ_FILES:.cpp=.obj)
OBJ_FILES = $(OBJ_FILES:.c=.obj)
!endif

# Similary for res file wrt rc file

!if "$(RC_FILE)" != ""
!if "$(DBG_RTL)" == "retail"
RES_FILE = retail\$(RC_FILE:.rc=.res)
!else
RES_FILE = debug\$(RC_FILE:.rc=.res)
!endif
!endif

# and TLB file wrt ODL

!if "$(ODL_FILE)" != ""
!if "$(TLB_FILE)" == ""
!if "$(DBG_RTL)" == "retail"
TLB_FILE = retail\$(ODL_FILE:.odl=.tlb)
!else
TLB_FILE = debug\$(ODL_FILE:.odl=.tlb)
!endif
!endif
!endif

#----------------------------------------------------------------------------
# PCH stuff

!ifndef NO_COMMON_PCH

!ifdef NODEBUG
STREAMS_PCH = $(MSSDK)\lib\streams.pch
!else
STREAMS_PCH = $(MSSDK)\lib\streamsd.pch
!endif

!if exist( "$(STREAMS_PCH)" )
NEED_PCH_OBJ = 1
LINK_TASK = $(LINK_TASK) $(DBG_RTL)\_streams.obj
END_TASK  = $(END_TASK) del_own_streams_obj
COMMON_PCH_OBJ = $(DBG_RTL)\_streams.obj
!endif

!endif

!ifndef DISABLE_PCH

!ifdef  PCH_HEADER

pchusage = /Yu$(PCH_HEADER)

!ifdef PCH_NAME
!ifdef PCH_OBJ_NAME
PCH_OBJ = $(DBG_RTL)\$(PCH_OBJ_NAME).obj
!else
PCH_OBJ = $(DBG_RTL)\$(PCH_NAME).obj
!endif
PCH_PCH = $(DBG_RTL)\$(PCH_NAME).pch
!else
!ERROR must specify PCH_NAME when using PCH_HEADER
!endif

cpppch  = $(pchusage) /Fp$(PCH_PCH)

!else

!if exist( "$(STREAMS_PCH)" )
PCH_OBJ  =
PCH_PCH  = $(STREAMS_PCH)
pchusage = /Yustreams.h
cpppch  = $(pchusage) /Fp$(PCH_PCH)
!else
DISABLE_PCH = 1
!endif

!endif

!endif

#----------------------------------------------------------------------------
# Browser files

!if "$(BROWSER)" == "TRUE"
cbrowser   = -FR$(@R).sbr
TARGET_BSC = $(DBG_RTL)\$(TARGET_NAME).bsc
!else
cbrowser   =
TARGET_BSC =
!endif

#----------------------------------------------------------------------------
# Map and Sym files

!if "$(TARGET_MAP)" !=""

!ifdef SYM_FILES
END_TASK = $(END_TASK) $(TARGET_MAP:.map=.sym)
lmap     = -map:$(TARGET_MAP)
!endif

!ifdef MAP_FILES
lmap     = -map:$(TARGET_MAP)
!endif

LINKER_FLAGS = $(LINKER_FLAGS) $(lmap)

!endif

#----------------------------------------------------------------------------
# Define common libraries

# base (not version!)
_CORE_LIBS = kernel32.lib    \
             advapi32.lib    \
             version.lib     \
             largeint.lib

# win libs
_USER_LIBS = user32.lib      \
             gdi32.lib       \
             comctl32.lib

_OLE__LIBS = ole32.lib       \
             oleaut32.lib    \
             uuid.lib

# !ifdef USE_MSVCRT_LIB
!ifndef USE_LIBCMT_LIB

!ifdef NODEBUG
_CRT__LIBS = msvcrt.lib
!else
!ifdef USE_MSVC20
_CRT__LIBS = msvcrt.lib
!else
_CRT__LIBS = msvcrtd.lib
!endif
!endif

!else

!ifdef NODEBUG
_CRT__LIBS = libcmt.lib
!else
!ifdef USE_MSVC20
_CRT__LIBS = libcmt.lib
!else
_CRT__LIBS = libcmtd.lib
!endif
!endif

!endif

_MM___LIBS = vfw32.lib       \
             winmm.lib

!ifdef NODEBUG
_AX1__LIBS = $(MSSDK)\lib\strmbase.lib
!else
_AX1__LIBS = $(MSSDK)\lib\strmbasd.lib
!endif

_AX2__LIBS = $(MSSDK)\lib\quartz.lib

!ifdef PERF
_AX2__LIBS = $(_AX2__LIBS)               \
             $(MSSDK)\lib\measure.lib
!endif

BASE_LIBS = $(_CRT__LIBS) \
            $(_MM___LIBS) \
            $(_CORE_LIBS) \
            $(_USER_LIBS) \
            $(_OLE__LIBS)

!ifndef NO_ACTIVEX_LIBS
LINK_LIBS = $(_AX2__LIBS) $(LINK_LIBS) $(_AX1__LIBS)
!if "$(TARGET_TYPE)" == "DYNLINK"
CODE_LIBS = $(_AX1__LIBS) $(CODE_LIBS)
!endif
!endif

!if "$(TARGET_TYPE)" != "DYNLINK"
LINK_LIBS = $(CODE_LIBS) $(LINK_LIBS)
!endif

LINK_LIBS = $(LINK_LIBS) $(BASE_LIBS)

#----------------------------------------------------------------------------
# Pseudo-targets

.SILENT:
.IGNORE:
.SUFFIXES:
.SUFFIXES: .c .cpp
.PRECIOUS: $(TARGET_LIB) $(TARGET_BIN)

#----------------------------------------------------------------------------
# Rules

CC_COMMAND_LINE  = $(cflags) $(cbrowser) -Fo$(DBG_RTL)\ $(INC_FLAGS) $(@B).c

CPP_COMMAND_LINE = $(cflags) $(cbrowser) -Fo$(DBG_RTL)\ $(INC_FLAGS) $(@B).cpp

.c{$(DBG_RTL)}.obj:
  echo Compiling $(@B).c...               > $(MAKE_ECHO)
  if exist $@ del $@ > NUL
  $(TYPE_ECHO)
  $(FILE_ECHO)
  echo $(cc) $(ccpch) $(CC_COMMAND_LINE)  > $(MAKE_ECHO)
  $(TYPE_ECHO2)
  $(FILE_ECHO)
  $(cc) $(ccpch) $(CC_COMMAND_LINE)       > $(MAKE_ECHO)
  $(TYPE_ECHO)
  $(FILE_ECHO)
  echo.                                   > $(MAKE_ECHO)
  $(TYPE_ECHO2)
  $(FILE_ECHO)

.c.cod:
  echo Compiling $(@B).c - with cod file... > $(MAKE_ECHO)
  if exist $@ del $@ > NUL
  $(TYPE_ECHO)
  $(FILE_ECHO)
  echo $(cc) -Fc $(CC_COMMAND_LINE)         > $(MAKE_ECHO)
  $(TYPE_ECHO2)
  $(FILE_ECHO)
  $(cc) -Fc $(CC_COMMAND_LINE)              > $(MAKE_ECHO)
  $(TYPE_ECHO)
  $(FILE_ECHO)
  echo.                                     > $(MAKE_ECHO)
  $(TYPE_ECHO2)
  $(FILE_ECHO)

.cpp{$(DBG_RTL)}.obj:
  echo Compiling $(@B).cpp...               > $(MAKE_ECHO)
  if exist $@ del $@ > NUL
  $(TYPE_ECHO)
  $(FILE_ECHO)
  echo $(cc) $(cpppch) $(CPP_COMMAND_LINE)  > $(MAKE_ECHO)
  $(TYPE_ECHO2)
  $(FILE_ECHO)
  $(cc) $(cpppch) $(CPP_COMMAND_LINE)       > $(MAKE_ECHO)
  $(TYPE_ECHO)
  $(FILE_ECHO)
  echo.                                     > $(MAKE_ECHO)
  $(TYPE_ECHO2)
  $(FILE_ECHO)

.cpp.cod:
  echo Compiling $(@B).cpp - with cod file... > $(MAKE_ECHO)
  if exist $@ del $@ > NUL
  $(TYPE_ECHO)
  $(FILE_ECHO)
  echo $(cc) -Fc $(CPP_COMMAND_LINE)          > $(MAKE_ECHO)
  $(TYPE_ECHO2)
  $(FILE_ECHO)
  $(cc) -Fc $(CPP_COMMAND_LINE)               > $(MAKE_ECHO)
  $(TYPE_ECHO)
  $(FILE_ECHO)
  echo.                                       > $(MAKE_ECHO)
  $(TYPE_ECHO2)
  $(FILE_ECHO)

#----------------------------------------------------------------------------
# TARGETS - key

#
# default
#

all  : log_start     \
       dump_params   \
       pass1         \
       log_done      \
       clear_params  \
       del_echo

#
# clean
#

clean: dump_params0  \
       pass0         \
       clear_params0 \
       del_echo0     \
       log_reset

#----------------------------------------------------------------------------
# TARGETS - passes

pass0: log_pass0      \
       $(CLEAN_TASK)  \
       delete

pass1: log_pass       \
       make_dir       \
       $(START_TASK)  \
       $(TLB_FILE)    \
       $(LIB_TASK)    \
       $(RES_FILE)    \
       $(PCH_PCH)     \
       $(PCH_OBJ)     \
       $(OBJ_FILES)   \
       $(TARGET_LIB)  \
       $(GOAL_LIB)    \
       $(LINK_TASK)   \
       $(TARGET_BIN)  \
       $(TARGET_BSC)  \
       $(END_TASK)    \
       $(GOAL_BIN)

#----------------------------------------------------------------------------
# TARGETS - logging

log_reset:
  if exist $(MAKE_LOG) del $(MAKE_LOG)

log_start:
  if exist $(MAKE_LOG) del $(MAKE_LOG)
  echo Making $(MAKEDIR)          > $(MAKE_ECHO)
  $(TYPE_ECHO)
  $(FILE_ECHO)
  echo TARGET_LIB = $(TARGET_LIB) > $(MAKE_ECHO)
  $(TYPE_ECHO2)
  $(FILE_ECHO)
  echo TARGET_BIN = $(TARGET_BIN) > $(MAKE_ECHO)
  $(TYPE_ECHO2)
  $(FILE_ECHO)
  echo.                           > $(MAKE_ECHO)
  $(TYPE_ECHO2)
  $(FILE_ECHO)

log_done:
  echo Done! > $(MAKE_ECHO)
  $(TYPE_ECHO)
  $(FILE_ECHO)

#----------------------------------------------------------------------------
# TARGETS - support

make_dir:
  if not exist $(DBG_RTL)\NUL md $(DBG_RTL)

delete:
  echo y | del $(DBG_RTL)\*.* > NUL

# OPK prob.  if exist $(DBG_RTL)\nul del $(DBG_RTL)\** > NUL

del_own_streams_obj:
  if exist $(DBG_RTL)\_streams.obj del $(DBG_RTL)\_streams.obj

#----------------------------------------------------------------------------
# TARGETS - copying

#
# copy *.lib files
#

!ifndef NO_COPY
!if "$(TARGET_LIB)" != ""

$(GOAL_LIB) : $(TARGET_LIB)
  echo Copy $(TARGET_LIB) to $@... > $(MAKE_ECHO)
  $(TYPE_ECHO)
  $(FILE_ECHO)
  if not exist $(TARGET_LIB_GOAL)\NUL md $(TARGET_LIB_GOAL)
  copy $(TARGET_LIB) $(TARGET_LIB_GOAL) > $(MAKE_ECHO)
  $(TYPE_ECHO2)
  $(FILE_ECHO)
  echo. > $(MAKE_ECHO)
  $(TYPE_ECHO2)
  $(FILE_ECHO)

!endif
!endif

#
# copy *.exe, etc. files
#

!ifndef NO_COPY
!if "$(TARGET_BIN)" != ""

$(GOAL_BIN) : $(TARGET_BIN)
  echo Copy $(TARGET_BIN) to $@... > $(MAKE_ECHO)
  $(TYPE_ECHO)
  $(FILE_ECHO)
  if not exist $(TARGET_BIN_GOAL)\NUL md $(TARGET_BIN_GOAL)
  copy $(TARGET_BIN) $(TARGET_BIN_GOAL) > $(MAKE_ECHO)
!ifdef MAP_FILES
  if exist $(TARGET_MAP) copy $(TARGET_MAP) $(TARGET_BIN_GOAL) > NUL
!endif
!ifdef SYM_FILES
  if exist $(TARGET_MAP:.map=.sym) copy $(TARGET_MAP:.map=.sym) $(TARGET_BIN_GOAL) > NUL
!endif
  $(TYPE_ECHO2)
  $(FILE_ECHO)
  echo. > $(MAKE_ECHO)
  $(TYPE_ECHO2)
  $(FILE_ECHO)

!endif
!endif

#----------------------------------------------------------------------------
# TARGETS - target type specific

#
# build library
#

!if "$(TARGET_LIB)" != ""

LIB_COMMAND_LINE = $(libflags)          \
                   $(LIB_FLAGS)         \
                   /out:$(TARGET_LIB)   \
                   $(CODE_LIBS)         \
                   $(OBJ_FILES)         \
                   $(PCH_OBJ)           \
                   $(RES_FILE)

$(TARGET_LIB): $(OBJ_FILES) $(RES_FILE) $(DEF_FILE) $(CODE_LIBS)
  echo Build library $@... > $(MAKE_ECHO)
  $(TYPE_ECHO)
  $(FILE_ECHO)
  echo $(implib) $(LIB_COMMAND_LINE) > $(MAKE_ECHO)
  $(TYPE_ECHO2)
  $(FILE_ECHO)
  $(implib) $(LIB_COMMAND_LINE)      > $(MAKE_ECHO)
  $(TYPE_ECHO)
  $(FILE_ECHO)
  echo.                              > $(MAKE_ECHO)
  $(TYPE_ECHO2)
  $(FILE_ECHO)
!endif

#
# link bin
#

!if "$(TARGET_BIN)" != ""

LINK_COMMAND_LINE =   \
   $(lflags)          \
   $(LINKER_FLAGS)    \
   /out:$(TARGET_BIN) \
   $(TARGET_EXP)      \
   $(OBJ_FILES)       \
   $(PCH_OBJ)         \
   $(COMMON_PCH_OBJ)  \
   $(RES_FILE)        \
   $(CODE_LIBS)       \
   $(LINK_LIBS)

# kill extra whitespace
LINK_COMMAND_LINE = $(LINK_COMMAND_LINE:        = )
LINK_COMMAND_LINE = $(LINK_COMMAND_LINE:    = )
LINK_COMMAND_LINE = $(LINK_COMMAND_LINE:  = )
LINK_COMMAND_LINE = $(LINK_COMMAND_LINE:  = )

$(TARGET_BIN): $(OBJ_FILES) $(RES_FILE) $(DEF_FILE) $(CODE_LIBS) $(TARGET_EXP)
  echo Linking $(TARGET_BIN)...     > $(MAKE_ECHO)
  $(TYPE_ECHO)
  $(FILE_ECHO)
  copy << $(MAKEDIR)\~qlnkcmd.tmp > NUL
  $(LINK_COMMAND_LINE: =^
  )
<<NOKEEP
  echo. $(link)                     > $(MAKE_ECHO)
  type $(MAKEDIR)\~qlnkcmd.tmp     >> $(MAKE_ECHO)
  $(TYPE_ECHO2)
  $(FILE_ECHO)
  $(link) @$(MAKEDIR)\~qlnkcmd.tmp  > $(MAKE_ECHO)
  $(TYPE_ECHO)
  $(FILE_ECHO)
  del $(MAKEDIR)\~qlnkcmd.tmp
  echo.                             > $(MAKE_ECHO)
  $(TYPE_ECHO2)
  $(FILE_ECHO)
!endif

#
# compile resources
#

!if "$(RC_FILE)" != ""
RC_COMMAND_LINE = $(rcflags)     \
                  -Fo$(RES_FILE) \
                  -I.            \
                  $(INC_FLAGS)   \
                  $(RC_FILE)
$(RES_FILE): $(RC_FILE)
  echo Compiling resources...   > $(MAKE_ECHO)
  $(TYPE_ECHO)
  $(FILE_ECHO)
  echo $(rc) $(RC_COMMAND_LINE) > $(MAKE_ECHO)
  $(TYPE_ECHO2)
  $(FILE_ECHO)
  $(rc) $(RC_COMMAND_LINE)      > $(MAKE_ECHO)
  $(TYPE_ECHO)
  $(FILE_ECHO)
  echo.                         > $(MAKE_ECHO)
  $(TYPE_ECHO2)
  $(FILE_ECHO)
!endif

#
# bsc target
#

!if "$(TARGET_BSC)" != ""
!if "$(PREPEND_STRMBASE_BSC)" == "TRUE"
STRMBASE_BSC = $(MSSDK)\samples\graphics\DirectShow\classes\base\$(DBG_RTL)\strmbase.bsc
$(TARGET_BSC) :: $(STRMBASE_BSC)
  copy $(STRMBASE_BSC) $(TARGET_BSC)
!endif
$(TARGET_BSC) :: $(OBJS)
  echo Generating Browser database... > $(MAKE_ECHO)
  $(TYPE_ECHO)
  $(FILE_ECHO)
  if exist $(DBG_RTL)\*.sbr bscmake /nologo /o$(TARGET_BSC) $(DBG_RTL)\*.sbr
  echo. > $(MAKE_ECHO)
  $(TYPE_ECHO)
  $(FILE_ECHO)
!endif

#
# make type library
#

!if "$(ODL_FILE)" != ""
MTL_COMMAND_LINE = $(mtlflags)      \
                   /win32           \
                   /tlb $(TLB_FILE) \
                   /h $(ODL_HEADER) \
                   -I.              \
                   $(INC_FLAGS)     \
                   $(ODL_FILE)
$(TLB_FILE): $(ODL_FILE)
  echo Making type library...     > $(MAKE_ECHO)
  $(TYPE_ECHO)
  $(FILE_ECHO)
  echo $(mtl) $(MTL_COMMAND_LINE) > $(MAKE_ECHO)
  $(TYPE_ECHO2)
  $(FILE_ECHO)
  $(mtl) $(MTL_COMMAND_LINE)      > $(MAKE_ECHO)
  $(TYPE_ECHO)
  $(FILE_ECHO)
  echo.                           > $(MAKE_ECHO)
  $(TYPE_ECHO2)
  $(FILE_ECHO)
!endif

#
# pch file
#

!ifndef DISABLE_PCH
!if "$(PCH_HEADER)" != ""
PCH_COMMAND_LINE = $(cflags)          \
                   -Fo$(PCH_OBJ)      \
                   -Fp$(PCH_PCH)      \
                   -Yc"$(PCH_HEADER)" \
                   -I.                \
                   $(INC_FLAGS)
$(PCH_PCH) $(PCH_OBJ) : $(PCH_HEADER)
  echo Compiling precompiled header... > $(MAKE_ECHO)
  $(TYPE_ECHO)
  $(FILE_ECHO)
  echo $(cc) $(PCH_COMMAND_LINE) > $(MAKE_ECHO)
  $(TYPE_ECHO2)
  $(FILE_ECHO)
  echo #include "$(PCH_HEADER)" > $(MAKEDIR)\~qpchfil.tmp
  $(cc) $(PCH_COMMAND_LINE) /Tp $(MAKEDIR)\~qpchfil.tmp > $(MAKE_ECHO)
  del $(MAKEDIR)\~qpchfil.tmp
  $(TYPE_ECHO2)
  $(FILE_ECHO)
  echo. > $(MAKE_ECHO)
  $(TYPE_ECHO)
  $(FILE_ECHO)

!ifdef OBJ_FILES
$(OBJ_FILES):$(PCH_PCH)
!endif

!else

!if "$(OBJ_FILES)" != ""
!ifdef NODEBUG
$(OBJ_FILES):$(MSSDK)\lib\streams.pch
!else
$(OBJ_FILES):$(MSSDK)\lib\streamsd.pch
!endif
!endif

!endif
!endif

!ifdef NEED_PCH_OBJ
$(DBG_RTL)\_streams.obj : $(MSSDK)\samples\graphics\DirectShow\classes\base\$(DBG_RTL)\_streams.obj
  copy $(MSSDK)\samples\graphics\DirectShow\classes\base\$(DBG_RTL)\_streams.obj $(DBG_RTL) > NUL
!endif

#
# sym files
#

!ifdef SYM_FILES
!if "$(TARGET_MAP)" !=""
$(TARGET_MAP:.map=.sym): $(TARGET_MAP)
  echo Running mapsym...                                  > $(MAKE_ECHO)
  $(TYPE_ECHO)
  $(FILE_ECHO)
  mapsym -nologo -o $(TARGET_MAP:.map=.sym) $(TARGET_MAP) > $(MAKE_ECHO)
  $(TYPE_ECHO2)
  $(FILE_ECHO)
!endif
!endif

#----------------------------------------------------------------------------
# include dependencies

!ifndef NODEPENDS
!if exist("_depend")
!include "_depend"
!endif
!endif

!ELSE

#============================================================================
#
# DIRECTORY
#
#============================================================================

#
# if DIR_LIST *is* defined this makefile is being
# included to build a directory (tree).
#

#----------------------------------------------------------------------------
# directives

.IGNORE:
.SILENT:

#----------------------------------------------------------------------------
# defines


#----------------------------------------------------------------------------
# TARGETS - key

#
# default
#

all  : log_start           \
       dump_params         \
       set_pass_target     \
       pass1               \
       log_done            \
       delete_qmakcmd_bat  \
       clear_params        \
       del_echo

clean: dump_params0        \
       set_pass_target0    \
       pass0               \
       delete_qmakcmd_bat0 \
       clear_params0       \
       del_echo0

#----------------------------------------------------------------------------
# TARGETS - passes

# pass0 - do clean

pass0: log_pass0      \
       $(CLEAN_TASK)  \
       dir_list0      \
       dir_delete

pass1: log_pass       \
       $(START_TASK)  \
       dir_list1      \
       $(END_TASK)

#----------------------------------------------------------------------------
# TARGETS - directory lists

# dir_list0 - do clean

dir_list0: $(DIR_LIST)
  !$(MAKE_CMD) $** pass0

# dir_list1 - build all targets

dir_list1: $(DIR_LIST)
  !$(MAKE_CMD) $** pass1

#----------------------------------------------------------------------------
# TARGETS - support

set_pass_target:
  @echo @echo off                                            >  $(MAKE_CMD)
  @echo cd %1                                                >> $(MAKE_CMD)
  @echo $(MAKE) /nologo MAKE_ENV=$(MAKE_ENV) MAKE_PASS=%2 %2 >> $(MAKE_CMD)
  @echo cd $(MAKEDIR)                                        >> $(MAKE_CMD)

set_pass_target0:
  @echo @echo off                                            >  $(MAKE_CMD)
  @echo cd %1                                                >> $(MAKE_CMD)
  @echo $(MAKE) /nologo MAKE_ENV=$(MAKE_ENV) MAKE_PASS=%2 %2 >> $(MAKE_CMD)
  @echo cd $(MAKEDIR)                                        >> $(MAKE_CMD)

#----------------------------------------------------------------------------
# TARGETS - logging

log_start:
  if exist $(MAKE_LOG) del $(MAKE_LOG)
  echo Making $(MAKEDIR) tree... > $(MAKE_ECHO)
  $(TYPE_ECHO)
  $(FILE_ECHO)

log_done:
  echo Finished $(MAKEDIR) tree... > $(MAKE_ECHO)
  $(TYPE_ECHO)
  $(FILE_ECHO)

#----------------------------------------------------------------------------
# TARGETS - delete

dir_delete:
  if exist ~q*.*    del ~q*.*
  if exist make.log del make.log

delete_log:
  if exist $(MAKE_LOG) del $(MAKE_LOG)

delete_qmakcmd_bat:
  if exist $(MAKE_CMD) del $(MAKE_CMD)

delete_log0:
  if exist $(MAKE_LOG) del $(MAKE_LOG)

delete_qmakcmd_bat0:
  if exist $(MAKE_CMD) del $(MAKE_CMD)

# BINARY/DIRECTORY
!ENDIF

#============================================================================
#
# Common (to BINARY and DIRECTORY)
#
#============================================================================

#----------------------------------------------------------------------------
# TARGETS - environment

dump_params:
  if exist $(MAKE_ENV) del $(MAKE_ENV)
!ifdef NODEBUG
  echo NODEBUG     = $(NODEBUG)     >> $(MAKE_ENV)
!endif
!ifdef PERF
  echo PERF        = $(PERF)        >> $(MAKE_ENV)
!endif
!ifdef SYMBOLS
  echo SYMBOLS     = $(SYMBOLS)     >> $(MAKE_ENV)
!endif
!ifdef MAKE_CMD
  echo MAKE_CMD    = $(MAKE_CMD)    >> $(MAKE_ENV)
!endif
!ifdef MAKE_LOG
  echo MAKE_LOG    = $(MAKE_LOG)    >> $(MAKE_ENV)
!endif
!ifdef MAKE_ECHO
  echo MAKE_ECHO   = $(MAKE_ECHO)   >> $(MAKE_ENV)
!endif
!ifdef ECHO_ECHO
  echo ECHO_ECHO   = $(ECHO_ECHO)   >> $(MAKE_ENV)
!endif
!ifdef MAKEFLAGS
  echo MAKEFLAGS   = $(MAKEFLAGS)   >> $(MAKE_ENV)
!endif
!ifdef DISABLE_PCH
  echo DISABLE_PCH = $(DISABLE_PCH) >> $(MAKE_ENV)
!endif

dump_params0:
  if exist $(MAKE_ENV) del $(MAKE_ENV)
!ifdef NODEBUG
  echo NODEBUG     = $(NODEBUG)     >> $(MAKE_ENV)
!endif
!ifdef PERF
  echo PERF        = $(PERF)        >> $(MAKE_ENV)
!endif
!ifdef SYMBOLS
  echo SYMBOLS     = $(SYMBOLS)     >> $(MAKE_ENV)
!endif
!ifdef MAKE_CMD
  echo MAKE_CMD    = $(MAKE_CMD)    >> $(MAKE_ENV)
!endif
!ifdef MAKE_LOG
  echo MAKE_LOG    = $(MAKE_LOG)    >> $(MAKE_ENV)
!endif
!ifdef MAKE_ECHO
  echo MAKE_ECHO   = $(MAKE_ECHO)   >> $(MAKE_ENV)
!endif
!ifdef ECHO_ECHO
  echo ECHO_ECHO   = $(ECHO_ECHO)   >> $(MAKE_ENV)
!endif
!ifdef MAKEFLAGS
  echo MAKEFLAGS   = $(MAKEFLAGS)   >> $(MAKE_ENV)
!endif
!ifdef DISABLE_PCH
  echo DISABLE_PCH = $(DISABLE_PCH) >> $(MAKE_ENV)
!endif

clear_params:
  if exist $(MAKE_ENV) del $(MAKE_ENV)

clear_params0:
  if exist $(MAKE_ENV) del $(MAKE_ENV)

#----------------------------------------------------------------------------
# TARGETS - logging

del_echo:
  if exist $(MAKE_ECHO) del $(MAKE_ECHO)

del_echo0:
  if exist $(MAKE_ECHO) del $(MAKE_ECHO)

log_pass:
  echo $(MAKE_PASS) - $(MAKEDIR) > $(MAKE_ECHO)
  $(TYPE_ECHO)
  $(FILE_ECHO)

log_pass0:
  echo cleaning - $(MAKEDIR) > $(MAKE_ECHO)
  $(TYPE_ECHO)
  $(FILE_ECHO)

# END OF FILE