#include "dcload-syscalls.h"

void uint_to_string(unsigned int foo, unsigned char *bar)
{
    char hexdigit[16] = "0123456789abcdef";
    int i;

    for(i=7; i>=0; i--) {
        bar[i] = hexdigit[(foo & 0x0f)];
        foo = foo >> 4;
    }
    bar[8] = 0;
}

int main(void)
{
    unsigned int tool_ip;
    unsigned int tool_port;
    unsigned int our_ip;
    unsigned char tmp[9];

    write(1, "dcload gethostinfo test program\n\n", 33);

    our_ip = gethostinfo(&tool_ip, &tool_port);

    uint_to_string(our_ip, tmp);

    write(1, "our ip = 0x", 11);
    write(1, tmp, 9);
    write(1, "\n", 1);

    uint_to_string(tool_ip, tmp);

    write(1, "tool ip = 0x", 12);
    write(1, tmp, 9);
    write(1, "\n", 1);

    uint_to_string(tool_port, tmp);

    write(1, "tool port = 0x", 14);
    write(1, tmp, 9);
    write(1, "\n", 1);

    exit(0);
}
 
