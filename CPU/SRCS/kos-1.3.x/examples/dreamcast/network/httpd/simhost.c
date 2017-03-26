/*
 * Copyright (c) 2001, Swedish Institute of Computer Science.
 * All rights reserved. 
 *
 * Redistribution and use in source and binary forms, with or without 
 * modification, are permitted provided that the following conditions 
 * are met: 
 * 1. Redistributions of source code must retain the above copyright 
 *    notice, this list of conditions and the following disclaimer. 
 * 2. Redistributions in binary form must reproduce the above copyright 
 *    notice, this list of conditions and the following disclaimer in the 
 *    documentation and/or other materials provided with the distribution. 
 * 3. Neither the name of the Institute nor the names of its contributors 
 *    may be used to endorse or promote products derived from this software 
 *    without specific prior written permission. 
 *
 * THIS SOFTWARE IS PROVIDED BY THE INSTITUTE AND CONTRIBUTORS ``AS IS'' AND 
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE 
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE 
 * ARE DISCLAIMED.  IN NO EVENT SHALL THE INSTITUTE OR CONTRIBUTORS BE LIABLE 
 * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL 
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS 
 * OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) 
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT 
 * LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY 
 * OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF 
 * SUCH DAMAGE. 
 *
 * This file is part of the lwIP TCP/IP stack.
 * 
 * Author: Adam Dunkels <adam@sics.se>
 *
 * $Id: simhost.c,v 1.2 2002/04/20 02:17:07 bardtx Exp $
 */

/* Modified by Dan Potter for KOS */

#include <kos.h>
#include <lwip/lwip.h>
#include <unistd.h>
#include "httpd.h"
/*#include "udpecho.h"
#include "tcpecho.h"
#include "shell.h" */

KOS_INIT_FLAGS(INIT_DEFAULT | INIT_NET);

extern uint8 romdisk[];
KOS_INIT_ROMDISK(romdisk);

void wait_start() {
	uint8 cont;
	cont_cond_t cond;

	for (;;) {
		cont = maple_first_controller();
		if (cont) {
			if (cont_get_cond(cont, &cond) >= 0) {
				if (!(cond.buttons & CONT_START))
					return;
			}
		}

		thd_sleep(10);
	}
}

int main(int argc, char **argv) {
	struct ip_addr ipaddr, gw, netmask;

	/* Change these for your network */
	IP4_ADDR(&ipaddr, 10,3,2,6);
	IP4_ADDR(&netmask, 255,255,255,0);
	IP4_ADDR(&gw, 10,3,2,1);
	lwip_init_static(&ipaddr, &netmask, &gw);

	/* This doesn't work right now */
	// lwip_init_dhcp();
	
	/* tcpecho_init();
	shell_init(); */
	httpd_init();
	/*udpecho_init(); */
	printf("Applications started.\n");

	/* Wait for the user to hit START */
	wait_start();

	return 0;
}





