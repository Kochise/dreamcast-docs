/* KallistiOS ##version##

 input.h

 (c)2002 Dan Potter

 Adapted from Kosh, (c)2000 Jordan DeLong

 $Id: input.h,v 1.1 2003/02/27 03:46:29 bardtx Exp $
*/

#ifndef __CONIO_INPUT_H
#define __CONIO_INPUT_H

/* size of the input buffer */
#define CONIO_INPUT_BUFFSIZE	256

/* functions */
void conio_input_frame();
void conio_input_init();
void conio_input_shutdown();

typedef void (*conio_input_callback_t)(const char *str);
void conio_input_callback(conio_input_callback_t cb);

/* Default conio input system: call with block = 1 to wait for the user
   to type something; the output will be placed in dst, which should
   be at least dstcnt bytes large. Returns 0 on success, -1 on failure. */
int conio_input_getline(int block, char *dst, int dstcnt);

#endif
