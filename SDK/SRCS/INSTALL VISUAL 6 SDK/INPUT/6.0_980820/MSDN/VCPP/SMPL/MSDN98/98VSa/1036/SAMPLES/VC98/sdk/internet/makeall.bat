@Echo Off

rem LOG=NO stops child makefiles from making $(OBJDIR)\$(PROJ).Log

set LOG=NO
nmake -i >>samples.log

rem to make retail versions all of the samples uncomment the following line

rem nmake -i nodebug=1 >> samples.log
