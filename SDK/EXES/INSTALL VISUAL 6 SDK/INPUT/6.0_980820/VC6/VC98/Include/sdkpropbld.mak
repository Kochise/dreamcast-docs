#
# Include sdkpropbld.mak in order to get standard build options, environment
#  variables, and macros.  The sdkpropbld.mak file is installed with the SDK 
#  in the include directory.
# 

!ifdef clean
makeopts = clean=1
!endif # clean

!ifdef nodebug
makeopts = $(makeopts) nodebug=1
!endif
