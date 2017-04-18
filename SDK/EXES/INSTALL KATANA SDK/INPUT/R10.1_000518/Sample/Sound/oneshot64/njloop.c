/*
** njloop.c Ver.0.41  1998/4/24
** Copyright (C) 1998 SEGA Enterprises Co.,Ltd
** All Rights Reserved
*/

#include <shinobi.h>

void main(void)
{
#ifdef __GNUC__
	shinobi_workaround();
#endif
	njUserInit();

	while (1) {
		if (njUserMain() < 0) break;
		njWaitVSync();
	}

	njUserExit();
}


/******************************* end of file *******************************/
