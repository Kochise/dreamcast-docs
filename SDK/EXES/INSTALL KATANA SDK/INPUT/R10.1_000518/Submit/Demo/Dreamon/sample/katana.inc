#--------------------------------------------------------------------------------------------#
#  CONFIDENTIAL AND PROPRIETARY:                                                             #
#       Copyright 1998/1999 Sega Enterprises.  All rights reserved.                          #
#       This sample source code is provided for demonstration purposes only.                 #
#       Use and distribution of Sega proprietary material is governed by                     #
#       developer licensing agreement.                                                       #
#--------------------------------------------------------------------------------------------#

#--------------------------------------------------------------------------------------------#
#  Name:     Katana.inc                                                                      #
#  Title:    Katana Makefile                                                                 #
#  Created:  January 22, 1998                                                                #
#                                                                                            #
#  Version:  8.0                                                                             #
#  Platform: Set5.24 | Hitachi | Shinobi | Kamui | Kamui 2 | Ninja                           #
#                                                                                            #
#  Description:                                                                              #
#       Shared Makefile definitions required to build Katana projects.                       #
#                                                                                            #
#  History:										     				   #
#       05/19/99 - Now supports multiple source directories (Ray Tran)		     	     	   #                                                                           	
#       05/11/99 - Adapted to support Kamui2 and multiple graphic libraries (Thomas Szirtes) #
#       02/20/99 - Modified for GNU make (Dylan Bromley)                                     #
#       11/11/98 - Added support for BIN files and C++ browsing (Gary Lake).                 #
#       10/01/98 - Updated for Set5 (Gary Lake).                                             #
#       05/15/98 - Updated for Set4 P2-J (Gary Lake).                                        #
#       04/28/98 - Modified for Set4 (Gary Lake).                                            #
#       01/22/98 - Program created (Gary Lake).                                              #
#--------------------------------------------------------------------------------------------#

PROJECT_OBJS = $(addprefix $(OBJDIR)\,$(notdir $(subst \,/,$(addsuffix .obj,$(basename $(PROJECT_SRC))))))
PROJECT_TEMP_SRC = $(addprefix $(OBJDIR)\,$(notdir $(subst \,/,$(PROJECT_SRC))))

.SILENT :
.SUFFIXES : .c .cpp .src .bin .lib .elf



#--------------------------------------------------------------------------------------------#
# Standard definitions                                                                       #
#--------------------------------------------------------------------------------------------#

#--- Compiler, Linker, and Assembler ---#
MAKE		= gmake.exe
CC		= shc.exe
CPP		= shcpp.exe
ASM		= asmsh.exe
LINK		= lnk.exe
LIBR		= lbr.exe
DWFCONV		= dwfcnv.exe
BINCONV		= rof2bin.exe

#--- Output files ---#
OUTDIR          = exe
OBJDIR          = obj

#--- Makefile definitions ---#
TRUE		= 1
FALSE		= 0

#--- Default libraries and object files ---#
ifeq ($(GFXLIB),KAMUI2)
DEF_LIBS        = "$(KATANA_ROOT)\lib\shinobi.lib","$(KATANA_ROOT)\lib\kamui2.lib"
else
DEF_LIBS        = "$(KATANA_ROOT)\lib\shinobi.lib","$(KATANA_ROOT)\lib\ninja.lib"
endif

#--- If building a .bin file ---#
ifeq ($(BIN), TRUE)

#--- Binary files cannot contain debug info ---#
DEBUG		= FALSE

TDEF_OBJS	= $(KATANA_ROOT)\lib\strt1.obj\
		  $(KATANA_ROOT)\lib\strt2.obj
else
TDEF_OBJS	= $(KATANA_ROOT)\lib\strt1.obj\
		  $(KATANA_ROOT)\lib\strt2.obj\
		  $(KATANA_ROOT)\lib\systemid.obj\
		  $(KATANA_ROOT)\lib\toc.obj\
		  $(KATANA_ROOT)\lib\sg_sec.obj\
		  $(KATANA_ROOT)\lib\sg_arejp.obj\
		  $(KATANA_ROOT)\lib\sg_areus.obj\
		  $(KATANA_ROOT)\lib\sg_areec.obj\
		  $(KATANA_ROOT)\lib\sg_are00.obj\
		  $(KATANA_ROOT)\lib\sg_are01.obj\
		  $(KATANA_ROOT)\lib\sg_are02.obj\
		  $(KATANA_ROOT)\lib\sg_are03.obj\
		  $(KATANA_ROOT)\lib\sg_are04.obj\
		  $(KATANA_ROOT)\lib\sg_ini.obj\
		  $(KATANA_ROOT)\lib\aip.obj\
		  $(KATANA_ROOT)\lib\zero.obj\
		  $(KATANA_ROOT)\lib\snasm.obj\
		  $(KATANA_ROOT)\lib\lock.obj\
		  $(KATANA_ROOT)\lib\syscalls.obj\
		  $(KATANA_ROOT)\lib\close.obj\
		  $(KATANA_ROOT)\lib\open.obj\
		  $(KATANA_ROOT)\lib\read.obj\
		  $(KATANA_ROOT)\lib\write.obj\
		  $(KATANA_ROOT)\lib\lseek.obj
endif

ifndef EXTRA_OBJS
EXTRA_OBJS = NONE
endif

ifeq ($(EXTRA_OBJS), NONE)
DEF_OBJS = $(TDEF_OBJS)
else
DEF_OBJS = $(TDEF_OBJS) $(EXTRA_OBJS)
endif

#--------------------------------------------------------------------------------------------#
# Compiler switches                                                                          #
#--------------------------------------------------------------------------------------------#

#--- Default optimization flag ---#
ifndef OPTIMIZE
OPTIMIZE	= 1
endif

#--- Debugging on/off ---#
ifeq ($(DEBUG),TRUE)
C_DEBUG		= -optimize=$(OPTIMIZE) -debug
else
C_DEBUG		= -optimize=$(OPTIMIZE) -speed -nodebug
endif

#--- Assembler output ---#
ifeq ($(LIST),TRUE)
C_LIST		= -listfile="$*.lst"
else
C_LIST		=
endif


#--------------------------------------------------------------------------------------------#
# Compiler defines                                                                           #
#--------------------------------------------------------------------------------------------#

C_DEFS		= __SHC__,__SET4__,__SET5__,__KATANA__,_CLX_,_CLX2_,_STRICT_UNION_


#--------------------------------------------------------------------------------------------#
# Compiler options                                                                           #
#--------------------------------------------------------------------------------------------#
ifeq ($(GFXLIB),KAMUI2)
C_OPTS		= -cpu=sh4\
		  -division=cpu\
		  -endian=little\
		  -fpu=single\
		  -pic=0\
		  -macsave=0\
		  -string=const\
		  -comment=nonest\
		  -sjis\
		  -section=p=P,c=C,d=D,b=B\
		  -extra=a=800\
		  -show=obj,source,expansion,w=80,l=0\
		  -define=$(C_DEFS)\
                  -include="$(KATANA_ROOT)\include","$(KATANA_ROOT)\include\kamui2",.
else
C_OPTS		= -cpu=sh4\
		  -division=cpu\
		  -endian=little\
		  -fpu=single\
		  -pic=0\
		  -macsave=0\
		  -string=const\
		  -comment=nonest\
		  -sjis\
		  -section=p=P,c=C,d=D,b=B\
		  -extra=a=800\
		  -show=obj,source,expansion,w=80,l=0\
		  -define=$(C_DEFS)\
                  -include="$(KATANA_ROOT)\include","$(KATANA_ROOT)\include\kamui1",.
endif

C_FLAGS		= -sub="$(OBJDIR)\shc.sub" $(C_DEBUG) $(C_LIST)

#--------------------------------------------------------------------------------------------#
# Assembler switches                                                                         #
#--------------------------------------------------------------------------------------------#

#--- Debugging on/off ---#
ifeq ($(DEBUG),TRUE)
ASM_DEBUG	= -debug=d
else
ASM_DEBUG	=
endif

#--- Assembler output ---#
ifeq ($(LIST),TRUE)
ASM_LIST	= -list="$*.lst"
else
ASM_LIST	=
endif


#--------------------------------------------------------------------------------------------#
# Assembler options                                                                          #
#--------------------------------------------------------------------------------------------#

ASM_OPTS	= -cpu=sh4\
		  -endian=little\
		  -sjis\
		  -private

ASM_FLAGS	= $(ASM_OPTS) $(ASM_DEBUG) $(ASM_LIST)


#--------------------------------------------------------------------------------------------#
# Linker switches                                                                            #
#--------------------------------------------------------------------------------------------#

#--- Debugging on/off ---#
ifeq ($(DEBUG),TRUE)
LINK_DEBUG	= -debug
else
LINK_DEBUG	=
endif

#--- Linker map file output ---#
ifeq ($(LIST),TRUE)
LINK_LIST	= -print=$*.map
else
LINK_LIST	=
endif


#--------------------------------------------------------------------------------------------#
# Linker options                                                                             #
#--------------------------------------------------------------------------------------------#

#--- If building a .bin file ---#
ifeq ($(BIN),TRUE)
LINK_OPTS	= -noecho\
		  -align_section\
		  -form=a\
		  -start=DSGLH(8C010000)
else
LINK_OPTS	= -noecho\
		  -align_section\
		  -form=a\
		  -elf\
		  -entry=SG_SEC\
		  -start=IP(8C008000),DSGLH(8C010000)
endif

ifndef PROJECT_LIBS
PROJECT_LIBS = NONE
endif

ifeq   ($(PROJECT_LIBS),NONE)
LINK_FLAGS      = -library=$(DEF_LIBS)\
		  $(LINK_OPTS) $(LINK_DEBUG) $(LINK_LIST)
else
LINK_FLAGS      = -library=$(DEF_LIBS),$(PROJECT_LIBS)\
		  $(LINK_OPTS) $(LINK_DEBUG) $(LINK_LIST)
endif

#--------------------------------------------------------------------------------------------#
# Build source files                                                                         #
#--------------------------------------------------------------------------------------------#


$(OBJDIR)\\%.c: $(PROJECT_SRC)
	echo Compiling $(filter %$*.c, $?)
	echo.> "$(OBJDIR)\shc.sub"
	echo $(C_OPTS) >> "$(OBJDIR)\shc.sub"
	$(CC) $(filter %$*.c, $?) -ob=$(OBJDIR)\$*.obj $(C_FLAGS) 
	del "$(OBJDIR)\shc.sub"
ifeq ($(DEBUG),TRUE)
	$(DWFCONV) -sysrof="$(OBJDIR)\$*.o" "$(OBJDIR)\$*.obj"
	copy "$(OBJDIR)\$*.o" "$(OBJDIR)\$*.obj"
endif

$(OBJDIR)\\%.src: $(PROJECT_SRC)
	echo Assembling $(filter %$*.src, $?)
	$(ASM) $(filter %$*.src, $?) -O="$(OBJDIR)\$*.obj" $(ASM_FLAGS) 

$(OBJDIR)\\%.cpp: $(PROJECT_SRC)
	echo cpp Compiling $(filter %$*.cpp, $?)
	echo.> "$(OBJDIR)\shc.sub"
	echo $(C_OPTS) >> "$(OBJDIR)\shc.sub"
ifeq ($(DEBUG), TRUE)
	$(CPP) $(filter %$*.cpp, $?) -ob="$(OBJDIR)\$*.obj" $(C_FLAGS) -browser
	$(DWFCONV) -browser="$(OBJDIR)\cppdtb\$(*F).dtb" -sysrof="$(OBJDIR)\$*.o" "$(OBJDIR)\$*.obj"
	copy "$(OBJDIR)\$*.o" "$(OBJDIR)\$*.obj"
	del "$(OBJDIR)\shc.sub"
else
	$(CPP) $(filter %$*.cpp, $?) -ob="$(OBJDIR)\$*.obj" $(C_FLAGS)
	del "$(OBJDIR)\shc.sub"
endif

$(OBJDIR)\\%.ic: $(PROJECT_SRC)
	echo Compiling and Asm $(filter %$*.ic, $?)
	echo.> "$(OBJDIR)\shc.sub"
	echo $(C_OPTS) -code=asmcode >> "$(OBJDIR)\shc.sub"
	$(CC) $(filter %$*.ic, $?) -ob=$(OBJDIR)\$*.src $(C_FLAGS) 
	del "$(OBJDIR)\shc.sub"
	$(ASM) $(OBJDIR)\$*.src -O="$(OBJDIR)\$*.obj" $(ASM_FLAGS) 
	
$(OBJDIR)\\%.obj: $(PROJECT_TEMP_SRC)
	echo ALL OBJECT FILES CREATED

#--------------------------------------------------------------------------------------------#
# Link project files                                                                         #
#--------------------------------------------------------------------------------------------#

ifeq ($(BIN), TRUE)
$(OUTDIR)\\$(PROJECT).bin : $(OUTDIR)\create.dir $(OBJDIR)\create.dir $(PROJECT_OBJS)
else
$(OUTDIR)\\$(PROJECT).elf : $(OUTDIR)\create.dir $(OBJDIR)\create.dir $(PROJECT_OBJS)
endif
	echo.> "$(OUTDIR)\lnk.sub"
	for %%x in ($(DEF_OBJS)) do echo input %%x >> "$(OUTDIR)\lnk.sub"
	for %%x in ($(PROJECT_OBJS)) do echo input %%x >> "$(OUTDIR)\lnk.sub"
ifneq ($(PROJECT_LIBS),NONE)
	for %%x in ($(PROJECT_LIBS)) do echo library %%x >> "$(OUTDIR)\lnk.sub"
endif
	echo exit >> $(OUTDIR)\lnk.sub
	$(LINK) $(LINK_FLAGS) -sub="$(OUTDIR)\lnk.sub" -output="$(OUTDIR)\$(PROJECT).elf"
ifeq ($(BIN), TRUE)
	$(BINCONV) -q "$(OUTDIR)\$(PROJECT).elf"
	del "$(OUTDIR)\$(PROJECT).elf"
endif

#--------------------------------------------------------------------------------------------#
# CodeWarrior directives                                                                     #
#--------------------------------------------------------------------------------------------#
CW:
	CW_COM Cw_Bat.bat
	Cw_Bat.bat
	del Cw_Bat.bat

#--------------------------------------------------------------------------------------------#
# Makefile directives                                                                        #
#--------------------------------------------------------------------------------------------#

#--- Clean project files ---#

CLEAN :
	echo y | del "$(OUTDIR)\*" | echo Output files removed
	echo y | del "$(OBJDIR)\*" | echo Object files removed

#--- Clean only obj files ---#

CLEAN_OBJ:
	echo y | del "$(OBJDIR)\*" | echo Object files removed
	

#--- Make all ---#

ALL :
	$(MAKE) -f "$(PROJECT).mak" clean
	$(MAKE) -f "$(PROJECT).mak"

#--- Global make directives ---#

ALL_SAMPLES:
	-dir /b /s *.mak > All_Samples_SEGA_DTS.txt
	batmake All_Samples_SEGA_DTS.txt out_sega_dts.bat all_make_error.txt $(MAKE) -f
	del All_Samples_SEGA_DTS.txt
	out_sega_dts.bat
	del out_sega_dts.bat

ALL_SAMPLES_CLEAN:
	-dir /b /s *.mak > All_Samples_SEGA_DTS.txt
	batmake All_Samples_SEGA_DTS.txt out_sega_dts.bat all_make_error.txt $(MAKE) -f clean
	del All_Samples_SEGA_DTS.txt
	out_sega_dts.bat
	del out_sega_dts.bat
	
ALL_SAMPLES_ALL:
	-dir /b /s *.mak > All_Samples_SEGA_DTS.txt
	batmake All_Samples_SEGA_DTS.txt out_sega_dts.bat all_make_error.txt $(MAKE) -f ALL
	del All_Samples_SEGA_DTS.txt
	out_sega_dts.bat
	del out_sega_dts.bat

ALL_CLEAN_OBJ:
	-dir /b /s *.mak > All_Samples_OBJ_Sega_Dts.txt
	batmake All_Samples_SEGA_DTS.txt out_sega_dts.bat all_make_error.txt $(MAKE) -f CLEAN_OBJ
	del All_Samples_OBJ_Sega_Dts.txt
	out_sega_dts.bat
	del out_sega_dts.bat
	 
#--- Create directories ---#

$(OUTDIR)\create.dir :
	-if not exist "$(OUTDIR)\nul" mkdir "$(OUTDIR)"
	echo.> "$(OUTDIR)\create.dir"

$(OBJDIR)\create.dir :
	-if not exist "$(OBJDIR)\nul" mkdir "$(OBJDIR)"
	echo.> "$(OBJDIR)\create.dir"
