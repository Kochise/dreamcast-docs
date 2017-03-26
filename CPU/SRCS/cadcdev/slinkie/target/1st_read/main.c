/*

  1st_read/main.c
  Copyright (C)2004 Dan Potter

*/

#include <slinkie/exec.h>

extern uint8 payload[];
extern uint8 payload_end[];

void start() {
	uint32 * src = (uint32 *)payload;
	uint32 * dst = (uint32 *)0x8c004000;
	int i;

	for (i=0; i<0xc000/4; i++)
		*dst++ = *src++;

	((void (*)())0x8c004000)();
}
