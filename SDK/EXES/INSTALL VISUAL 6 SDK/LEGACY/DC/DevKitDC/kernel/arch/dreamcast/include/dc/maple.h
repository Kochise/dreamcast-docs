/* KallistiOS 1.1.6

   kernel/arch/dreamcast/include/dc/maple.h
   (C)2000-2001 Jordan DeLong

   $Id: maple.h,v 1.3 2002/01/05 07:33:51 bardtx Exp $

   Thanks to Marcus Comstedt for information on the Maple Bus.
*/

#ifndef __DC_MAPLE_H
#define __DC_MAPLE_H

#include <sys/cdefs.h>
__BEGIN_DECLS

#include <arch/types.h>

/* Command and response codes */
#define MAPLE_RESPONSE_FILEERR		-5
#define MAPLE_RESPONSE_AGAIN 		-4
#define MAPLE_RESPONSE_BADCMD		-3
#define MAPLE_RESPONSE_BADFUNC		-2
#define MAPLE_RESPONSE_NONE		-1
#define MAPLE_COMMAND_DEVINFO		1
#define MAPLE_COMMAND_ALLINFO		2
#define MAPLE_COMMAND_RESET		3
#define MAPLE_COMMAND_KILL		4
#define MAPLE_RESPONSE_DEVINFO		5
#define MAPLE_RESPONSE_ALLINFO		6
#define MAPLE_RESPONSE_OK		7
#define MAPLE_RESPONSE_DATATRF		8
#define MAPLE_COMMAND_GETCOND		9
#define MAPLE_COMMAND_GETMINFO		10
#define MAPLE_COMMAND_BREAD		11
#define MAPLE_COMMAND_BWRITE		12
#define MAPLE_COMMAND_BSYNC		13
#define MAPLE_COMMAND_SETCOND		14

/* Function codes */
#define MAPLE_FUNC_PURUPURU		(1<<16)
#define MAPLE_FUNC_MOUSE		(1<<17)
#define MAPLE_FUNC_CONTROLLER		(1<<24)
#define MAPLE_FUNC_MEMCARD		(1<<25)
#define MAPLE_FUNC_LCD			(1<<26)
#define MAPLE_FUNC_CLOCK		(1<<27)
#define MAPLE_FUNC_MICROPHONE		(1<<28)
#define MAPLE_FUNC_ARGUN		(1<<29)
#define MAPLE_FUNC_KEYBOARD		(1<<30)
#define MAPLE_FUNC_LIGHTGUN		(1<<31)

/* frame struct */
typedef struct {
	int8 cmd;			/* command (defined above) */
	uint8 to;			/* recipient address */
	uint8 from;			/* sender address */
	void *data;			/* ptr to parameter data */
	uint8 datalen;			/* length in words of data */
} maple_frame_t;

/* transfer descriptor struct */
typedef struct {
	uint8 lastdesc;			/* set to nonzero if this is the last descriptor */
	uint8 port;			/* port for transfer to go to, 0-3 */
	uint8 length;			/* length of data - 1 word */
	uint32 *recvaddr;		/* where the result gets written to */
	maple_frame_t *frames;		/* array of frames in this transfer */
	uint8 numframes;		/* number of frames in frames */
} maple_tdesc_t;

typedef struct {
	uint32		func;
	uint32		function_data[3];
	uint8		area_code;
	uint8		connector_direction;
	char		product_name[30];
	char		product_license[60];
	uint16		standby_power;
	uint16		max_power;
} maple_devinfo_t;

void	maple_init();
void	maple_shutdown();
uint32	*maple_add_trans(maple_tdesc_t tdesc, uint32 *buffer);
void	maple_read_frame(uint32 *buffer, maple_frame_t *frame);
uint8	maple_create_addr(uint8 port, uint8 unit);
int	maple_docmd_block(int8 cmd, uint8 addr, uint8 datalen, void *data, maple_frame_t *retframe);
int	maple_rescan_bus(int quiet);


/* A couple of convienence functions to load maple peripherals */

/* Retrieve function code... */
uint32 maple_device_func(int port, int unit);

/* First with a given function code... */
uint8 maple_first_device(int code);

/* First controller */
uint8 maple_first_controller();

/* First mouse */
uint8 maple_first_mouse();

/* First keyboard */
uint8 maple_first_kb();

/* First LCD unit */
uint8 maple_first_lcd();

/* First VMU */
uint8 maple_first_vmu();

__END_DECLS

#endif /* __DC_MAPLE_H */

