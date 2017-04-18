# ------------------------------------------
# Title:		Default Makefile for use in VC++
# File:		        default.mak
# Revision:             20020210 8:30pm
# 
# Author:		Benjamin D. Hale
# Orignally by:         Jaap Suter
# Contributed to by:    Christer Andersson
# 
# Info:		        This file is contains the make-instructions
#			for the project. Replace DEVDIR with the appropriate
#                       base directory for devkitdc. After you make the 
#                       needed modifications here rename this file to
#                       <project_name>.mak so Visual C++ does not get
#                       confused.
# -------------------------------------------

# -------------------------------------------
# Project name definition makes this whole thing 
# a lot easier to use. Only two total modifications
# (other than what .o files will be needed)
# should be needed to get this working with your
# compiler and Visual C++. Replace "Default" with
# your project's name.
# -------------------------------------------

PROJECT = Default

# -------------------------------------------
# Define some directories;
# -------------------------------------------

# -------------------------------------------
# Base Directory for gcc arm-agb-elf replace with 
# wherever you put your gba devkitadv files.
# -------------------------------------------

DEVDIR  = E:\DevKitDC

# -------------------------------------------
# Source directory (where your project's source files are located.)
# -------------------------------------------

SRCDIR  = E:\Projects\$(PROJECT)

# -------------------------------------------
# Compiler Directories for binaries, includes and libs.
# -------------------------------------------

CMPDIR  = $(DEVDIR)\bin
LIBDIR  = $(DEVDIR)\lib\gcc-lib\sh-sega-dreamcast\3.0.3\msingle
LIBDIR2 = $(DEVDIR)\sh-sega-dreamcast\lib\msingle
INCDIR  = $(DEVDIR)\lib\gcc-lib\arm-agb-elf\3.0.3\include
INCDIR2 = $(DEVDIR)\sh-sega-dreamcast\include

# -------------------------------------------
# END of directory defines
# -------------------------------------------

# -------------------------------------------
# Define what extensions we use;
# -------------------------------------------
.SUFFIXES : .cpp .c .s

# -------------------------------------------
# Define the flags for the compilers;
# -------------------------------------------
CFLAGS  = -I $(INCDIR2) -I $(INCDIR) -I $(SRCDIR) -m1 -msingle -c -g -O2 -Wall
SFLAGS  = -I $(INCDIR2) -I $(INCDIR) -little
LDFLAGS = -L $(LIBDIR) -L $(LIBDIR2) -T LinkScript 

# -------------------------------------------
# Define the list of all O files;
# Just follow the syntax shown to add any 
# other objects your project may need to
# compile properly. You will need to add 
# files to this part to make it work with 
# your project add a \ to the end of all o
# files except the last one. Like below.
# -------------------------------------------

O_FILES			 = crt0.o       \
                           

# -------------------------------------------
# There should be no need to modify anything
# below here.
# -------------------------------------------

# -------------------------------------------
# Define the final dependecy;
# -------------------------------------------
all : $(PROJECT).bin

# -------------------------------------------
# Define the copy from .elf to .bin file
# -------------------------------------------
$(PROJECT).bin : $(PROJECT).elf
	objcopy -v -O binary $(PROJECT).elf $(PROJECT).bin
	-@echo ------------------------------------------ 
	-@echo Done 
	-@echo ------------------------------------------ 
	
# -------------------------------------------
# Define the linker instruction;
# -------------------------------------------
$(PROJECT).elf : $(O_FILES)
	ld $(LDFLAGS) -o $(PROJECT).elf $(O_FILES) -lstdc++ -lgcc -lc  
	-@echo ------------------------------------------ 
	-@echo Linking Done
	-@echo ------------------------------------------ 

# -------------------------------------------
# Define each compile;
# -------------------------------------------
.cpp.o::
	gcc  $(CFLAGS) $< 
	-@echo ------------------------------------------ 
	-@echo CPP-Sources Compiled 
	-@echo ------------------------------------------ 

.c.o::
        gcc  $(CFLAGS) $<
        -@echo ------------------------------------------
        -@echo C-sources Compiled
        -@echo ------------------------------------------

# -------------------------------------------
# Define each assemble;
# -------------------------------------------
{$(SRCDIR)}.s.o:
	as $(SFLAGS) $(SRCDIR)\$*.s -o$@
	-@echo ------------------------------------------ 
	-@echo ASM-Sources Compiled 
	-@echo ------------------------------------------ 
	
# -------------------------------------------
# Any problems with getting this working email
# questions to whatzdat_pimp@hotmail.com .
# This was tested on devkitadv r4 and Visual C++ 6
# on a p3 450/512mb/Windows XP Pro.
# -------------------------------------------
# EOF;

