DIRS =	block	\
	nonblock

all: $(DIRS)

$(DIRS):
	cd $@
	echo *** $@ *** >>$(MSTOOLS)\samples\listen.tmp
	nmake -a -i -nologo >>$(MSTOOLS)\samples\listen.tmp
	cd ..
	
