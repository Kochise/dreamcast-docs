DIRS = \
    bellhop\~   \
    boids\~   \
    d3dex1\~   \
    d3dex2\~   \
    ddex1\~   \
    ddex2\~   \
    ddex3\~   \
    ddex4\~   \
    ddex5\~   \
    diex1\~   \
    diex2\~   \
    diex3\~   \
    diex4\~   \
    diff1\~   \
    donut\~   \
    donuts\~   \
    dpchat\~   \
    dplaunch\~   \
    dpslots\~   \
    ds3dview\~   \
    dsshow\~   \
    dsshow3d\~   \
    dsstream\~   \
    duel\~   \
    dxbug\~   \
    dxview\~   \
    egg\~   \
    faces\~   \
    fastfile\~   \
    fdfilter\~   \
    ffdonuts\~   \
    flip2d\~   \
    flip3d\~   \
    fly\~   \
    foxbear\~   \
    globe\~   \
    hier1\~   \
    hier2\~   \
    mid2strm\~   \
    misc\~   \
    morph\~   \
    mosquito\~   \
    mstream\~   \
    override\~   \
    palette\~   \
    pplane\~   \
    quat\~   \
    rockem\~   \
    scrawl\~   \
    setup\~   \
    shadow\~   \
    stretch\~   \
    stretch2\~   \
    stretch3\~   \
    tex1\~   \
    tex3\~   \
    tex4\~   \
    tex5\~   \
    trans\~   \
    tri3\~   \
    uvis\~   \
    viewer\~   \
    wormhole\~   \
    memtime\~   \


SDKPROJ =Graphics\DirectX


#
# This is a Platform SDK non-leaf-node makefile.  It is used to allow NMAKE, 
#  or a similar tool, to recursively build all of the samples in a directory 
#  tree.  To add or remove a directory from the build process, modify the 
#  DIRS list above.  
#
# The SDKPROJ macro (above) is defined solely for the purpose of echoing
#  the current directory location to the screen.  
#
# Do not modify this makefile except for the DIRS and SDKPROJ macros above.
#

#
# Include sdkpropbld.mak in order to get standard build options, environment
#  variables, and macros.  The sdkpropbld.mak file is installed with the SDK 
#  in the include directory.
# 

!include <sdkpropbld.mak>

# 
# In order to build "all," process each of the entries in the DIRS list.
#

all: $(DIRS)


#
# In order to build each of the entries in the DIRS list, change dir into the
#  directory in question, echo the current location, run nmake recursively, 
#  and change dir back to the original directory level.  This four step process 
#  is encapsulated in sdkbld.mak which is installed with the SDK in the include
#  directory.
#

$(DIRS):
!include <sdkbld.mak>
