/* 
 * dcload-ip commands for dcload-ip lwIP interface
 *
 * Copyright (C) 2002 Andrew Kieschnick <adk@napalm-x.com>
 *
 */

#ifndef __DCLOAD_LWIP_COMMANDS_H__
#define __DCLOAD_LWIP_COMMANDS_H__

typedef struct {
  unsigned char id[4] __attribute__ ((packed));
  unsigned int address __attribute__ ((packed));
  unsigned int size __attribute__ ((packed));
  unsigned char data[1] __attribute__ ((packed));
} command_t;

#define CMD_EXECUTE  "EXEC" /* execute */
#define CMD_LOADBIN  "LBIN" /* begin receiving binary */
#define CMD_PARTBIN  "PBIN" /* part of a binary */
#define CMD_DONEBIN  "DBIN" /* end receiving binary */
#define CMD_SENDBIN  "SBIN" /* send a binary */
#define CMD_SENDBINQ "SBIQ" /* send a binary, quiet */
#define CMD_VERSION  "VERS" /* send version info */

#define CMD_RETVAL   "RETV" /* return value */

#define CMD_REBOOT   "RBOT"  /* reboot */

#define COMMAND_LEN  12

void cmd_loadbin(struct udp_pcb *pcb, struct pbuf *p, command_t *command);
void cmd_partbin(struct udp_pcb *pcb, struct pbuf *p, command_t *command);
void cmd_donebin(struct udp_pcb *pcb, struct pbuf *p, command_t *command);
void cmd_sendbinq(struct udp_pcb *pcb, struct pbuf *p, command_t *command);
void cmd_retval(struct udp_pcb *pcb, struct pbuf *p, command_t *command);



#endif
