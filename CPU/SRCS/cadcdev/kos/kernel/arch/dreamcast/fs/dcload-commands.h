/* KallistiOS ##version##

   kernel/arch/dreamcast/fs/dcload-commands.h

   Copyright (C)2003 Andrew Kieschnick, imported
   from the GPL'd dc-load-ip sources to a BSD-compatible
   license with permission.

   Adapted to KOS by Dan Potter.

*/

#ifndef __COMMANDS_H__
#define __COMMANDS_H__

#include <sys/cdefs.h>
__BEGIN_DECLS

#include <arch/types.h>

#include "dcload-packet.h"

typedef struct {
  unsigned char id[4] __attribute__ ((packed));
  unsigned int address __attribute__ ((packed));
  unsigned int size __attribute__ ((packed));
  unsigned char data[1] __attribute__ ((packed));
} command_t;

#define DCLN_CMD_EXECUTE  "EXEC" /* execute */
#define DCLN_CMD_LOADBIN  "LBIN" /* begin receiving binary */
#define DCLN_CMD_PARTBIN  "PBIN" /* part of a binary */
#define DCLN_CMD_DONEBIN  "DBIN" /* end receiving binary */
#define DCLN_CMD_SENDBIN  "SBIN" /* send a binary */
#define DCLN_CMD_SENDBINQ "SBIQ" /* send a binary, quiet */
#define DCLN_CMD_VERSION  "VERS" /* send version info */

#define DCLN_CMD_RETVAL   "RETV" /* return value */

#define DCLN_CMD_REBOOT   "RBOT"  /* reboot */

#define COMMAND_LEN  12

extern uint32 dcln_tool_ip;
extern uint8 dcln_tool_mac[6];
extern uint16 dcln_tool_port;
extern int dcln_escape_loop;

void dcln_cmd_loadbin(ip_header_t * ip, udp_header_t * udp, command_t * command);
void dcln_cmd_partbin(ip_header_t * ip, udp_header_t * udp, command_t * command);
void dcln_cmd_donebin(ip_header_t * ip, udp_header_t * udp, command_t * command);
void dcln_cmd_sendbinq(ip_header_t * ip, udp_header_t * udp, command_t * command);
void dcln_cmd_sendbin(ip_header_t * ip, udp_header_t * udp, command_t * command);
void dcln_cmd_version(ip_header_t * ip, udp_header_t * udp, command_t * command);
void dcln_cmd_retval(ip_header_t * ip, udp_header_t * udp, command_t * command);

__END_DECLS

#endif

