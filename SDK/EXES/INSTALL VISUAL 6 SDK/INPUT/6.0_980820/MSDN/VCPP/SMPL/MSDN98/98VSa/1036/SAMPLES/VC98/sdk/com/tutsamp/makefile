#/*+=========================================================================
#  File:       MAKEFILE
#
#  Summary:    Makefile for building all of the COM Tutorial Samples.
#              It assumes that you have set up your environment to compile
#              Win32 applications using the Win32 SDK with Visual C++ v.
#              2.x+ or later or other compatible 32-bit C++ compiler. This
#              makefile assumes that the tutorial code samples reside
#              within the directory structure of an installed Win32 SDK.
#              If you have extracted the sample branch to a location
#              outside the Win32 SDK then use MAKEALL.BAT to compile all
#              all samples in the branch instead of this makefile.
#
#              In general, to set up your system to build and test the
#              Win32 code samples in this Tutorial series, see the
#              global TUTORIAL.HTM file for details.  This MAKEFILE is
#              Microsoft NMAKE compatible and the 'debug' build can be
#              achieved by simply issuing the NMAKE command in a command
#              prompt window.
#
#  Builds:     All COM Tutorial Code Samples in proper order.
#
#  Origin:     8-23-97: atrent - For incorporation into Platform SDK.
#
#--Usage:-------------------------------------------------------------------
#  NMAKE Options
#
#  Use the table below to determine the additional options for NMAKE to
#  generate various application debugging, profiling and performance tuning
#  information.
#
#  Application Information Type         Invoke NMAKE
#  ----------------------------         ------------
#  For Debugging Info (default)         nmake -a
#  For No Debugging Info                nmake -a nodebug=1
#  For Working Set Tuner Info           nmake -a tune=1
#  For Call Attributed Profiling Info   nmake -a profile=1
#
#  Note: The three options above are mutually exclusive (you may use only
#        one to compile/link the application).
#
#  Note: creating the environment variables NODEBUG, TUNE, and PROFILE
#        is an alternate method to setting these options via the nmake
#        command line.
#
#  Additional NMAKE Options             Invoke NMAKE
#  ----------------------------         ------------
#  For No ANSI NULL Compliance          nmake -a no_ansi=1
#    (ANSI NULL is defined as PVOID 0)
#  To clean up temporary binaries       nmake clean
#  To clean up all generated files      nmake cleanall
#  To register all servers              nmake regall
#  To unregister all servers            nmake unregall
#
#---------------------------------------------------------------------------
#  This file is part of the Microsoft COM Tutorial Code Samples.
#
#  Copyright (C) Microsoft Corporation, 1997.  All rights reserved.
#
#  This source code is intended only as a supplement to Microsoft
#  Development Tools and/or on-line documentation.  See these other
#  materials for detailed information regarding Microsoft code samples.
#
#  THIS CODE AND INFORMATION IS PROVIDED "AS IS" WITHOUT WARRANTY OF ANY
#  KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE
#  IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A
#  PARTICULAR PURPOSE.
#=========================================================================+*/

DIRLIST  =  apputil  \
            readtut  \
            exeskel  \
            dllskel  \
            dlluser  \
            comobj   \
            comuser  \
            register \
            dllserve \
            dllclien \
            licserve \
            licclien \
            marshal  \
            marshal2 \
            locserve \
            locclien \
            aptserve \
            aptclien \
            remclien \
            freserve \
            freclien \
            conserve \
            conclien \
            stoserve \
            stoclien \
            perserve \
            pertext  \
            perdraw  \
            perclien \
            dcdmarsh \
            dcdserve \
            dcomdraw

# The final target.
all: $(DIRLIST)

$(DIRLIST):
        cd $@
        @echo *** ole\com\$@ *** >>$(MSTOOLS)\samples\olecom.tmp
        @nmake -a -i -nologo >>$(MSTOOLS)\samples\olecom.tmp
        cd ..

regall:
  call regall.bat

unregall:
  call unregall.bat

clean:
  call makeall.bat clean

cleanall:
  call unregall.bat
  call makeall.bat cleanall
