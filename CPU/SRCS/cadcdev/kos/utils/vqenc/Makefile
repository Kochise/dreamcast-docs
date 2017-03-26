
# Makefile for the genromfs program.

# Use for OSX w/Fink
#CFLAGS = -O2 -Wall -DINLINE=inline -I/sw/include #-g#
#LDFLAGS = -s -L/sw/lib -lpng -ljpeg -lz #-g

# Use for other systems
CFLAGS = -O2 -Wall -DINLINE=inline #-g#
LDFLAGS = -s -lpng -ljpeg -lz #-g

all: vqenc

vqenc: vqenc.o get_image.o get_image_jpg.o get_image_png.o readpng.o
	$(CC) -o $@ $+ $(LDFLAGS)

clean:
	rm -f vqenc *.o

install: all 
	install -m 755 vqenc /usr/bin
