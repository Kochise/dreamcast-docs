#------------------------------------------------------------------------------
# GinBoot.mak
#------------------------------------------------------------------------------

PROJECT         = 1st_read

PROJECT_OBJS    =   \
        $(OBJDIR)\GinBoot.obj\
        $(OBJDIR)\sbinit.obj\

PROJECT_LIBS    =   \
        ginsu,\
        ninja,\
        nindows,\
        sg_sydds

GFX_API		= NINJA

#DEBUG           = TRUE
#LIST            = TRUE
BIN             = TRUE
#GNU		= TRUE

include $(KATANA_ROOT)\sample\katana.inc
