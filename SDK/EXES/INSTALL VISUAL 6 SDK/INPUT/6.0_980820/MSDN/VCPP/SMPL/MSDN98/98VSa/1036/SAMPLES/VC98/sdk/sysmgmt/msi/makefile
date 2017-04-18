DIRS = \
    ApiTstDb\~ \
    CustAct1\~ \
    CustExe1\~ \
    MSIMerg\~  \
    MSIVal\~   \
    SampProd\~ \
    Sequence\~ \


SdkPROJ =SysMgmt\MSI


#
# This is a Platform Sdk non-leaf-node makefile.  It is used to allow NMAKE,
#  or a similar tool, to recursively build all of the samples in a directory 
#  tree.  To add or remove a directory from the build process, modify the 
#  DIRS list above.  
#
# The SdkPROJ macro (above) is defined solely for the purpose of echoing
#  the current directory location to the screen.  
#
# Do not modify this makefile except for the DIRS and SdkPROJ macros above.
#

#
# Include SdkPropBld.Mak in order to get standard build options, environment
#  variables, and macros.  The SdkPropBld.Mak file is installed with the Sdk
#  in the include directory.
# 

!include <SdkPropBld.Mak>

# 
# In order to build "all," process each of the entries in the DIRS list.
#

all: $(DIRS)


#
# In order to build each of the entries in the DIRS list, change dir into the
#  directory in question, echo the current location, run nmake recursively, 
#  and change dir back to the original directory level.  This four step process 
#  is encapsulated in SdkBld.Mak which is installed with the Sdk in the include
#  directory.
#

$(DIRS):
!include <SdkBld.Mak>
