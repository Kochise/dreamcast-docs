#include "dcload-syscalls.h"

int main(void)
{
    int fd;
    unsigned char buffer[2048];
    int count;
    unsigned char wrkmem[65536];

    assign_wrkmem(wrkmem);

    write(1, "dcload console test program\n\n", 30);

    fd = open("console-test.c", O_RDONLY);

    if (fd == -1) {
	write(1, "open failed!\n", 14);
	exit(1);
    }

    write(1, "Contents of console-test.c:\n\n", 30);

    count = read(fd, buffer, 2048);

    if (count == -1) {
	write(1, "read failed!\n", 14);
	exit(1);
    }
    
    write(1, buffer, count);

    close(fd);

    exit(0);
}
 
