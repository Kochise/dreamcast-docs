# =========================================================================
# DOSWIN16.MAK - Win16 application master NMAKE definitions file for the
#               Microsoft Windows 3.1 SDK
# -------------------------------------------------------------------------
# NMAKE Options
#
# Use the table below to determine the extra options for NMAKE to
# generate various application debugging information.
#
# Application Information Type         Invoke NMAKE
# ----------------------------         ------------
# For No Debugging Info                nmake nodebug=1
#
# Note: using the environment variables NODEBUG is an
#       alternate method for setting this option.
#

#
#
# -------------------------------------------------------------------------
# Platform Dependent Binaries Declarations
# -------------------------------------------------------------------------
cc     = cl
link   = link
implib = lib
rc     = rc
hc     = hc

hcopts = -n

# -------------------------------------------------------------------------
# Platform Dependent Compile Flags - must be specified after $(cc)
#
# Note: Debug switches are on by default for current release
#
# Common compiler flags:
#   -c   - compile without linking
#   -W3  - Set warning level to level 3
#   -Zi  - generate debugging information
#   -Od  - disable all optimizations
#   -Ox  - use maximum optimizations
#   -Zd  - generate only public symbols and line numbers for debugging
#
# -------------------------------------------------------------------------
# declarations common to all compilers.
ccommon = -c -W3 -I. -Gs -Gt -Zp -nologo
cflags = $(ccommon) -AS -GA
cflagsdll = $(ccommon) -Asnw -Gw

!IFDEF NODEBUG
cdebug =
!ELSE
cdebug = -Zid -Od
!ENDIF

# -------------------------------------------------------------------------
# Target Module & Subsystem Dependant Compile Defined Variables - must be
#   specified after $(cc)
# -------------------------------------------------------------------------
!IFDEF NODEBUG
cvarsdebug =
!ELSE
cvarsdebug = -DDEBUG
!ENDIF

cvars	   = $(cvarsdebug)
cvarsdll   = -D_DLL  $(cvarsdebug)

# resource compiler
rcvars =

# -------------------------------------------------------------------------
# Target Module Dependent Link Debug Flags - must be specified after $(link)
#
# These switches allow for source level debugging with CodeView
#
# Note: Debug switches are on by default.
# -------------------------------------------------------------------------
linkflags = /nod/noe /al:16

!IFDEF NODEBUG
ldebug =/map
!ELSE
ldebug = /CO /LI /MAP
!ENDIF

# for compatibility with older style makefiles
linkdebug = $(ldebug)

# -------------------------------------------------------------------------
# Subsystem Dependent Link Flags - must be specified after $(link)
#
# These switches allow for source level debugging with WinDebug for local
# and global variables.
# -------------------------------------------------------------------------

# For applications that use the C-Runtime libraries
guilflags = map/nod/noe /al:16
guiflags  = map/nod/noe /al:16

# -------------------------------------------------------------------------
# C-Runtime Target Module Dependent Link Libraries
# -------------------------------------------------------------------------

# For applications that use the C-Runtime libraries
guilibs    = libw llibcew commdlg
