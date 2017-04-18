#
# WIN16.MAK -- common Win16 macros and rules for MAPI SDK
# derived from (NT)WIN32.MAK in the Win32 SDK
#
#

# =========================================================================
# NTWIN32.MAK - Win32 application master NMAKE definitions file for the
#               Microsoft Win32 SDK for Windows NT programming samples
# -------------------------------------------------------------------------
# This files should be included at the top of all MAKEFILEs as follows:
#  !include <ntwin32.mak>
# -------------------------------------------------------------------------
# NMAKE Options
#
# Use the table below to determine the additional options for NMAKE to
# generate various application debugging, profiling and performance tuning
# information.
#
# Application Information Type         Invoke NMAKE
# ----------------------------         ------------
# For No Debugging Info                nmake nodebug=1
# For Working Set Tuner Info           nmake tune=1
# For Call Attributed Profiling Info   nmake profile=1
#
# Note: Working Set Tuner and Call Attributed Profiling is for available
#       for the Intel x86 and Pentium systems.
#
# Note: The three options above are mutually exclusive (you may use only
#       one to compile/link the application).
#
# Note: creating the environment variables NODEBUG, TUNE, and PROFILE is an
#       alternate method to setting these options via the nmake command line.
#
# Additional NMAKE Options             Invoke NMAKE
# ----------------------------         ------------
# For No ANSI NULL Compliance          nmake no_ansi=1
# (ANSI NULL is defined as PVOID 0)
#
# =========================================================================

!IFNDEF _WIN16_MAK_
_WIN16_MAK_ = 1

# -------------------------------------------------------------------------
# Get CPU Type - exit if CPU environment variable is not defined
# -------------------------------------------------------------------------

# Intel i386, i486, and Pentium systems
CPU = i386
CPUTYPE = 1

# -------------------------------------------------------------------------
# Get Target Operating System - Default to both
# -------------------------------------------------------------------------

TARGETOS = WIN16

# -------------------------------------------------------------------------
# Set Default WINVER - depends on TARGETOS
#
# Defaults to 4.0 for all applications except NT specific.
# -------------------------------------------------------------------------

APPVER = 3.10
    
# binary declarations common to all platforms
cc     = cl
rc     = rc
link   = link
implib = lib

# -------------------------------------------------------------------------
# Platform Dependent Compile Flags - must be specified after $(cc)
#
# Note: Debug switches are on by default for current release
#
# These switches allow for source level debugging with WinDebug for local
# and global variables.
#
# Both compilers now use the same front end - you must still define either
# _X86_, _MIPS_, _PPC_ or _ALPHA_.  These have replaced the i386, MIPS, and ALPHA
# definitions which are not ANSI compliant.
#
# Common compiler flags:
#   -c   - compile without linking
#   -W3  - Set warning level to level 3
#   -Zi  - generate debugging information
#   -Od  - disable all optimizations
#   -Ox  - use maximum optimizations
#   -Zd  - generate only public symbols and line numbers for debugging
#
# i386 specific compiler flags:
#   -Gz  - stdcall
#
# MS MIPS specific compiler flags:
#   none.
#
# -------------------------------------------------------------------------

# declarations common to all compiler options
ccommon = -c -nologo -W3

cflags = $(ccommon) -D_X86_=1 -Zp2 -Gsfy -Gc -Gx- -J
scall  = -Gz

# Generate 286 code -- 386 codegen is too broken
cflags = $(cflags) -G2

INCLUDE = $(MSTOOLS)\h;$(INCLUDE)
LIB = $(MSTOOLS)\lib;$(LIB)
cflags = $(cflags) -DWIN16 # -D_WIN16

!IF "$(WINVERSION)" != ""
cflags = $(cflags) -DWINVER=$(WINVERSION)
!ELSE
cflags = $(cflags) -DWINVER=0x030A
!ENDIF

!IFDEF NODEBUG
cdebug = -Ox
!ELSE
cdebug = -Z7 -Od -Ob1    # use -Zi for MSVC
!ENDIF

# -------------------------------------------------------------------------
# Target Module & Subsystem Dependent Compile Defined Variables - must be
#   specified after $(cc)
#
# The following table indicates the various acceptable combinations of
# the C Run-Time libraries LIBC, LIBCMT, and CRTDLL respect to the creation
# of a EXE and/or DLL target object.  The appropriate compiler flag macros
# that should be used for each combination are also listed.
#
#  Link EXE    Create Exe    Link DLL    Create DLL
#    with        Using         with         Using
# ----------------------------------------------------
#  LIBC        CVARS          None        None      *
#  LIBC        CVARS          LIBC        CVARS
#  LIBC        CVARS          LIBCMT      CVARSMT
#  LIBCMT      CVARSMT        None        None      *
#  LIBCMT      CVARSMT        LIBC        CVARS
#  LIBCMT      CVARSMT        LIBCMT      CVARSMT
#  CRTDLL      CVARSDLL       None        None      *
#  CRTDLL      CVARSDLL       LIBC        CVARS
#  CRTDLL      CVARSDLL       LIBCMT      CVARSMT
#  CRTDLL      CVARSDLL       CRTDLL      CVARSDLL  *
#
# * - Denotes the Recommended Configuration
#
# When building single-threaded applications you can link your executable
# with either LIBC, LIBCMT, or CRTDLL, although LIBC will provide the best
# performance.
#
# When building multi-threaded applications, either LIBCMT or CRTDLL can
# be used as the C-Runtime library, as both are multi-thread safe.
#
# Note: Any executable which accesses a DLL linked with CRTDLL.LIB must
#       also link with CRTDLL.LIB instead of LIBC.LIB or LIBCMT.LIB.
#       When using DLLs, it is recommended that all of the modules be
#       linked with CRTDLL.LIB.
#
# Note: The macros of the form xDLL are used when linking the object with
#       the DLL version of the C Run-Time (that is, CRTDLL.LIB).  They are
#       not used when the target object is itself a DLL.
#
# -------------------------------------------------------------------------

# for Windows applications that use the C Run-Time libraries
cvars      = -AL -GA -GEs
cvarsdll   = -Al -Alfu -Gd -D_WINDLL -D_DLL

# resource compiler
rcflags = /r
rcvars = -DWIN16 -D_WIN16 $(noansi)

rcvars = $(rcvars) -DWINVER=0x030A

# -------------------------------------------------------------------------
# Platform Dependent Link Flags - must be specified after $(link)
#
# Note: $(DLLENTRY) should be appended to each -entry: flag on the link
#       line.
#
# Note: When creating a DLL that uses C Run-Time functions it is
#       recommended to include the entry point function of the name DllMain
#       in the DLL's source code.  Also, the MAKEFILE should include the
#       -entry:_DllMainCRTStartup$(DLLENTRY) option for the creation of
#       this DLL.  (The C Run-Time entry point _DllMainCRTStartup in turn
#       calls the DLL defined DllMain entry point.)
#
# -------------------------------------------------------------------------

# declarations common to all linker options
lcommon = /NOD /NOE /MAP /ONERROR:NOEXE /NOLOGO

# declarations for use on Intel i386, i486, and Pentium systems
lflags   = $(lcommon)

# -------------------------------------------------------------------------
# Target Module Dependent Link Debug Flags - must be specified after $(link)
#
# These switches allow the inclusion of the necessary symbolic information
# for source level debugging with WinDebug, profiling and/or performance
# tuning.
#
# Note: Debug switches are on by default.
# -------------------------------------------------------------------------

!IFDEF NODEBUG
ldebug = 
!ELSE
ldebug = /CO
!ENDIF

# -------------------------------------------------------------------------
# Subsystem Dependent Link Flags - must be specified after $(link)
#
# These switches allow for source level debugging with WinDebug for local
# and global variables.  They also provide the standard application type and
# entry point declarations.
# -------------------------------------------------------------------------

# for Windows applications that use the C Run-Time libraries
conlflags = $(lflags) 
guilflags = $(lflags) 
dlllflags = $(lflags) # -dll

# -------------------------------------------------------------------------
# C Run-Time Target Module Dependent Link Libraries
#
# Below is a table which describes which libraries to use depending on the
# target module type, although the table specifically refers to Graphical
# User Interface apps, the exact same dependencies apply to Console apps.
# That is, you could replace all occurrences of 'GUI' with 'CON' in the
# following:
#
# Desired CRT  Libraries   Desired CRT  Libraries
#   Library     to link      Library     to link
#   for EXE     with EXE     for DLL     with DLL
# ----------------------------------------------------
#   LIBC       GUILIBS       None       None       *
#   LIBC       GUILIBS       LIBC       GUILIBS
#   LIBC       GUILIBS       LIBCMT     GUILIBSMT
#   LIBCMT     GUILIBSMT     None       None       *
#   LIBCMT     GUILIBSMT     LIBC       GUILIBS
#   LIBCMT     GUILIBSMT     LIBCMT     GUILIBSMT
#   CRTDLL     GUILIBSDLL    None       None       *
#   CRTDLL     GUILIBSDLL    LIBC       GUILIBS
#   CRTDLL     GUILIBSDLL    LIBCMT     GUILIBSMT
#   CRTDLL     GUILIBSDLL    CRTDLL     GUILIBSDLL *
#
# * - Recommended Configurations.
#
# Note: Any executable which accesses a DLL linked with CRTDLL.LIB must
#       also link with CRTDLL.LIB instead of LIBC.LIB or LIBCMT.LIB.
#
# -------------------------------------------------------------------------

# These CRT Libraries assume the use of Microsoft Visual C++ 1.5
# If you are using another Compiler product, change the libc* 
# variable to correspond to your import library names.

# for Windows applications that use the C Run-Time libraries
conlibs    = oldnames.lib llibce.lib
guilibs    = commdlg.lib oldnames.lib libw.lib llibcew.lib
guilibsdll = commdlg.lib oldnames.lib libw.lib ldllcew.lib

# for OLE applications
olelibs      = compobj.lib ole2.lib ole2disp.lib $(guilibs)
olelibsmt    = compobj.lib ole2.lib ole2disp.lib $(guilibsmt)
olelibsdll   = compobj.lib ole2.lib ole2disp.lib $(guilibsdll)

#ENDIF _WIN16_MAK_
!ENDIF 
