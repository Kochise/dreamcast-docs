
# Makefile for the genromfs program.

CFLAGS = -O2 -Wall -DINLINE=inline #-g#
LDFLAGS = -s -lpng -ljpeg -lz #-g

all: vqenc

vqenc: vqenc.o get_image.o get_image_jpg.o get_image_png.o readpng.o
	$(CC) -o $@ $+ $(LDFLAGS)

clean:
	rm -f vqenc *.o

install: all 
	install -m 755 vqenc /usr/bin
