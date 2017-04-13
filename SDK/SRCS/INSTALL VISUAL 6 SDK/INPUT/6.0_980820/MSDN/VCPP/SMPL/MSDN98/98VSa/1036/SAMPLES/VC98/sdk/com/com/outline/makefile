#
# (c) Copyright Microsoft Corp. 1992-1997 All Rights Reserved
#
# Makefile : Builds the OLE 2.0 Outline series sample apps
#        The Outline series includes:
#           Outline.exe -- base version of app (w/o OLE functionality)
#           SvrOutl.exe -- OLE 2.0 Server sample app
#           CntrOutl.exe -- OLE 2.0 Containter (Container) sample app
#        NOTE: apps are built in a subdir of same name as app.
#
# Usage:     NMAKE              (builds all executables)
#    or:     NMAKE APP=outline  (build outline.exe--non-OLE version)
#    or:     NMAKE APP=svroutl  (build svroutl.exe--server-only version)
#    or:     NMAKE APP=cntroutl (build cntroutl.exe--container-only version)
#    or:     NMAKE APP=icntrotl (build icntrotl.exe--InPlace container ver.)
#    or:     NMAKE APP=isvrotl  (build isvrotl.exe--InPlace server ver.)
#    or:     NMAKE clean        (erase all compiled files)
#

!include <olesampl.mak>

!if "$(APP)" == ""
APPS = outline.exe svroutl.exe cntroutl.exe icntrotl.exe isvrotl.exe
!else
APPS = $(APP).exe
!endif

all: $(APPS)

$(APPS):
    cd $*
    $(MAKE) -$(MAKEFLAGS) -nologo
    cd $(MAKEDIR)

##########################################################################
#
# clean (erase) generated files

clean:
    -for %i in (outline svroutl cntroutl icntrotl isvrotl) do del %i\*.obj
    -for %i in (outline svroutl cntroutl icntrotl isvrotl) do del %i\*.res
    -for %i in (outline svroutl cntroutl icntrotl isvrotl) do del %i\*.exe
    -for %i in (outline svroutl cntroutl icntrotl isvrotl) do del %i\*.map
    -for %i in (outline svroutl cntroutl icntrotl isvrotl) do del %i\*.pch
