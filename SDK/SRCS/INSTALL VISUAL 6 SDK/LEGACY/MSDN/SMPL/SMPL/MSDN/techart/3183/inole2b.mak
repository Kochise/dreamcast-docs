#
# INOLE2B.MAK
# Common Linker Commands
#
# Copyright (c)1993-1994 Microsoft Corporation, All Rights Reserved
#
# Kraig Brockschmidt, Microsoft
# Internet  :  kraigb@microsoft.com
# Compuserve:  >INTERNET:kraigb@microsoft.com
#

#
# This file should be included after the sample's makefile
# has defined INCLS, OBJS, OUTFILE, etc., and included inole2a.mak.
# The separation between inole2a.mak and this file is to allow
# a sample to change default definitions in inole2a.mak before
# including this file to build the sample.
#


$(OUTFILE) : $(OBJS) $(TARGET).res $(DEFFILE)
    echo ++++++++++
    echo Linking $@

!ifndef WIN16
    echo $(LINK)                         > $(TARGET).lrf
    echo -def:$(DEFFILE)                >> $(TARGET).lrf
    echo -out:$(OUTFILE)                >> $(TARGET).lrf
    echo -machine:IX86                  >> $(TARGET).lrf
    echo -align:0x1000                  >> $(TARGET).lrf
    echo $(OBJS1)                       >> $(TARGET).lrf
    echo $(OBJS2)                       >> $(TARGET).lrf
    echo $(OBJS3)                       >> $(TARGET).lrf
    echo $(OBJS4)                       >> $(TARGET).lrf
    echo $(OBJS5)                       >> $(TARGET).lrf
    echo $(OBJS6)                       >> $(TARGET).lrf
    echo $(TARGET).res                  >> $(TARGET).lrf
    echo $(LIBS32)                      >> $(TARGET).lrf
    echo $(LIBS)                        >> $(TARGET).lrf

    link @$(TARGET).lrf
    del $(TARGET).lrf

!else

    echo +                               > $(TARGET).lrf
    echo $(OBJS1) +                     >> $(TARGET).lrf
    echo $(OBJS2) +                     >> $(TARGET).lrf
    echo $(OBJS3) +                     >> $(TARGET).lrf
    echo $(OBJS4) +                     >> $(TARGET).lrf
    echo $(OBJS5) +                     >> $(TARGET).lrf
    echo $(OBJS6)                       >> $(TARGET).lrf
    echo $(OUTFILE) $(LINK)             >> $(TARGET).lrf
    echo nul/li                         >> $(TARGET).lrf
    echo $(LIBS32) +                    >> $(TARGET).lrf
    echo $(LIBS)                        >> $(TARGET).lrf
    echo $(DEFFILE)                     >> $(TARGET).lrf

    link @$(TARGET).lrf
    del $(TARGET).lrf
    rc -v -K $(TARGET).res $(OUTFILE)

!endif
