
# Makefile for the kmgenc program.

CFLAGS = -O2 -Wall -DINLINE=inline #-g#
LDFLAGS = -s -lpng -ljpeg #-g

all: kmgenc

kmgenc: kmgenc.o get_image.o get_image_jpg.o get_image_png.o readpng.o
	$(CC) -o $@ $+ $(LDFLAGS)

clean:
	rm -f kmgenc *.o

