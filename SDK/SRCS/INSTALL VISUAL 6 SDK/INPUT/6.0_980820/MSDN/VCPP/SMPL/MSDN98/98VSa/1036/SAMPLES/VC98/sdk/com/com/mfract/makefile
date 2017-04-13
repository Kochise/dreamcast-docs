DIRLIST  =  idl     \
            engines \
            app

all: $(DIRLIST)

$(DIRLIST):
        @echo *******************************
        @echo *** BUILDING COM\MFRACT samples
        @echo *******************************
        cd $@
        @nmake -a -i -nologo
        cd ..
