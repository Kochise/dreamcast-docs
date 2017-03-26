/* KallistiOS ##version##

   inet_addr.c
   Copyright (C)2006 Lawrence Sebald

*/

#include <arpa/inet.h>
#include <stdlib.h>

in_addr_t inet_addr(const char *cp) {
    in_addr_t result = 0;
    long tmp;
    char *ptr;

    tmp = strtoul(cp, &ptr, 10);
    if(tmp > 0xFF || cp == ptr) {
        return (in_addr_t) -1;
    }
    else {
        result = tmp << 24;
    }

    tmp = strtoul(ptr + 1, &ptr, 10);
    if(tmp > 0xFF || cp == ptr) {
        return (in_addr_t) -1;
    }
    else {
        result |= tmp << 16;
    }

    tmp = strtoul(ptr + 1, &ptr, 10);
    if(tmp > 0xFF || cp == ptr) {
        return (in_addr_t) -1;
    }
    else {
        result |= tmp << 8;
    }

    tmp = strtoul(ptr + 1, &ptr, 10);
    if(tmp > 0xFF || cp == ptr) {
        return (in_addr_t) -1;
    }
    else {
        result |= tmp;
    }

    return (in_addr_t) htonl(result);
}
