all: makejitter

CFLAGS = -O2 -Wall -I../../../kos-ports/include #-g#

makejitter: makejitter.o

clean:
	rm -f makejitter jitter_table.h *.o

install: all install-bin

install-bin:
	install -m 755 makejitter /usr/bin

