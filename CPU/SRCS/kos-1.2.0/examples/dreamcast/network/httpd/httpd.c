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
 * $Id: httpd.c,v 1.2 2002/04/20 02:17:07 bardtx Exp $
 */

/* Modified by Dan Potter to port to KOS */

#include <kos.h>
#include <lwip/lwip.h>
#include "httpd.h"

struct http_state {
	file_t	file;
	int	left;
};

/*-----------------------------------------------------------------------------------*/
static void
conn_err(void *arg, err_t err)
{
  struct http_state *hs;

  hs = arg;
  mem_free(hs);
}
/*-----------------------------------------------------------------------------------*/
static void
close_conn(struct tcp_pcb *pcb, struct http_state *hs)
{
  //printf("close_conn\n");

  tcp_arg(pcb, NULL);
  tcp_sent(pcb, NULL);
  tcp_recv(pcb, NULL);
  fs_close(hs->file);
  mem_free(hs);
  tcp_close(pcb);
}
/*-----------------------------------------------------------------------------------*/
static char sendbuffer[65536];
static void
send_data(struct tcp_pcb *pcb, struct http_state *hs)
{
  err_t err;
  u16_t len;

  /* We cannot send more data than space avaliable in the send
     buffer. */     
  if(tcp_sndbuf(pcb) < hs->left) {
    len = tcp_sndbuf(pcb);
  } else {
    len = hs->left;
  }

  if (len > 0) {
	//printf("send_data: sending %d, hs->left = %d\n", len, hs->left);
	assert( len <= 65536 );
  	if (fs_read(hs->file, sendbuffer, len) != len) {
  		dbglog(DBG_ERROR, "http send_data: could not read all %d bytes\n", len);
  	}
	err = tcp_write(pcb, sendbuffer, len, 0);
  }
  
  if(err == ERR_OK) {
    hs->left -= len;
    /*  } else {
	printf("send_data: error %s len %d %d\n", lwip_strerr(err), len, tcp_sndbuf(pcb));*/
  }
}
/*-----------------------------------------------------------------------------------*/
static err_t
http_poll(void *arg, struct tcp_pcb *pcb)
{
  /*  printf("Polll\n");*/
  if(arg == NULL) {
    /*    printf("Null, close\n");*/
    tcp_close(pcb);
  } else {
    send_data(pcb, (struct http_state *)arg);
  }

  return ERR_OK;
}
/*-----------------------------------------------------------------------------------*/
static err_t
http_sent(void *arg, struct tcp_pcb *pcb, u16_t len)
{
  struct http_state *hs;

  hs = arg;

  //printf("http_sent: hs->left = %d\n", hs->left);

  if(hs->left > 0) {    
    send_data(pcb, hs);
  } else {
    close_conn(pcb, hs);
  }

  return ERR_OK;
}
/*-----------------------------------------------------------------------------------*/
static err_t
http_recv(void *arg, struct tcp_pcb *pcb, struct pbuf *p, err_t err)
{
  int i, j;
  char *data;
  char fname[40];
  file_t file;
  struct http_state *hs;

  hs = arg;

  if(err == ERR_OK && p != NULL) {

    /* Inform TCP that we have taken the data. */
    tcp_recved(pcb, p->tot_len);
    
    if(hs->file == NULL) {
      data = p->payload;
      
      if(strncmp(data, "GET ", 4) == 0) {
	for(i = 0; i < 40; i++) {
	  if(((char *)data + 4)[i] == ' ' ||
	     ((char *)data + 4)[i] == '\r' ||
	     ((char *)data + 4)[i] == '\n') {
	    ((char *)data + 4)[i] = 0;
	  }
	}
	strcpy(fname, "/rd");
	strcat(fname, data+4);
	pbuf_free(p);
	
	//printf("http_recv: got a request for '%s'\n", fname);
	file = fs_open(fname, O_RDONLY);
	if (!file) {
	  file = fs_open("/rd/index.html", O_RDONLY);
	}
	hs->file = file;
	hs->left = fs_total(file);
	/*	printf("data %p len %ld\n", hs->file, hs->left);*/

	send_data(pcb, hs);

	/* Tell TCP that we wish be to informed of data that has been
	   successfully sent by a call to the http_sent() function. */
	tcp_sent(pcb, http_sent);
      } else {
	close_conn(pcb, hs);
      }
    } else {
      pbuf_free(p);
    }
  }

  if(err == ERR_OK && p == NULL) {
    close_conn(pcb, hs);
  }
  return ERR_OK;
}
/*-----------------------------------------------------------------------------------*/
static err_t
http_accept(void *arg, struct tcp_pcb *pcb, err_t err)
{
  struct http_state *hs;

  /* Allocate memory for the structure that holds the state of the
     connection. */
  hs = mem_malloc(sizeof(struct http_state));

  if(hs == NULL) {
    printf("http_accept: Out of memory\n");
    return ERR_MEM;
  }
  
  /* Initialize the structure. */
  hs->file = NULL;
  hs->left = 0;

  /* Tell TCP that this is the structure we wish to be passed for our
     callbacks. */
  tcp_arg(pcb, hs);

  /* Tell TCP that we wish to be informed of incoming data by a call
     to the http_recv() function. */
  tcp_recv(pcb, http_recv);

  tcp_err(pcb, conn_err);
  
  tcp_poll(pcb, http_poll, 10);
  return ERR_OK;
}
/*-----------------------------------------------------------------------------------*/
void
httpd_init(void)
{
  struct tcp_pcb *pcb;

  pcb = tcp_new();
  tcp_bind(pcb, IP_ADDR_ANY, 80);
  pcb = tcp_listen(pcb);
  tcp_accept(pcb, http_accept);
}
/*-----------------------------------------------------------------------------------*/

