/* KallistiOS ##version##

   slinkie/syscalls.c

   Copyright (C)2004 Dan Potter

 */

#include <stdio.h>
#include <string.h>
#include <net/net.h>
#include <slinkie/commands.h>
#include <slinkie/syscalls.h>
#include <slinkie/exec.h>
#include <slinkie/main.h>

static uint32 serial_hi = 0;

// This code is common to read, write, lseek, and dirread.
static int sc_rw_common(int fd, const uint8 * buffer, int amt, const char * code) {
	pkt_3i_t * rsp;

	// Send out the request
	rsp = (pkt_3i_t *)net_tx_build();
	memcpy(rsp->tag, code, 4);
	rsp->value0 = htonl(fd);
	rsp->value1 = htonl((uint32)buffer);
	rsp->value2 = htonl(amt);
	rsp->value3 = htonl(serial_hi++);
	net_resp_complete(sizeof(pkt_3i_t));

	// Wait for completion
	net_loop();

	return net_rpc_ret;
}

static int sc_read(int fd, const uint8 * buffer, int amt) {
	return sc_rw_common(fd, buffer, amt, SC_READ);
}

static int sc_write(int fd, uint8 * buffer, int amt) {
	return sc_rw_common(fd, buffer, amt, SC_WRITE);
}

// This code is common to open, stat, and unlink.
static int sc_os_common(const char * fn, uint32 val1, uint32 val2, const char * tag) {
	pkt_2is_t * rsp;
	
	// Send out the request
	rsp = (pkt_2is_t *)net_tx_build();
	memcpy(rsp->tag, tag, 4);
	rsp->value0 = htonl(val1);
	rsp->value1 = htonl(val2);
	strcpy(rsp->data, fn);
	net_resp_complete(sizeof(pkt_2is_t) + strlen(fn) + 1);

	// Wait for completion
	net_loop();

	return net_rpc_ret;
}

static int sc_open(const char * fn, uint32 flags, uint32 umask) {
	return sc_os_common(fn, flags, umask, SC_OPEN);
}

// This code is shared by close and dirclose.
static int sc_close_common(int fd, const char * tag) {
	pkt_i_t * rsp;

	// Send out the request
	rsp = (pkt_i_t *)net_tx_build();
	memcpy(rsp->tag, tag, 4);
	rsp->value0 = htonl(fd);
	net_resp_complete(sizeof(pkt_i_t));

	// Wait for completion
	net_loop();

	return net_rpc_ret;
}

static int sc_close(int fd) {
	return sc_close_common(fd, SC_CLOSE);
}

static int sc_unlink(const char * fn) {
	return sc_os_common(fn, 0, 0, SC_UNLINK);
}

static int sc_lseek(int fd, int amt, int whence) {
	return sc_rw_common(fd, (uint8 *)amt, whence, SC_LSEEK);
}

static int sc_stat(const char * fn, uint8 * buffer) {
	return sc_os_common(fn, (ptr_t)buffer, 60, SC_STAT);
}

static void sc_exit() {
	printf("sc_exit called\n");
	exec_exit();
}

static int sc_diropen(const char * dirname) {
	pkt_s_t * rsp;

	// Send out the request
	rsp = (pkt_s_t *)net_tx_build();
	memcpy(rsp->tag, SC_DIROPEN, 4);
	strcpy(rsp->data, dirname);
	net_resp_complete(sizeof(pkt_s_t) + strlen(dirname) + 1);

	// Wait for completion
	net_loop();

	return net_rpc_ret;
}

static int sc_dirclose(int fd) {
	return sc_close_common(fd, SC_DIRCLOSE);
}

static uint8 dirent_buffer[256+11];
static uint32 sc_dirread(int fd) {
	int rv = sc_rw_common(fd, dirent_buffer, 256+11, SC_DIRREAD);
	if (rv > 0)
		return (ptr_t)dirent_buffer;
	else
		return 0;
}

static int sc_invalid() {
	printf("sc_invalid called\n");
	return -1;
}

typedef int (*sc_t)(uint32 param1, uint32 param2, uint32 param3);
#define DECL(X) (sc_t)X
static sc_t syscalls[] = {
	DECL(sc_read),
	DECL(sc_write),
	DECL(sc_open),
	DECL(sc_close),
	DECL(sc_invalid),	// creat
	DECL(sc_invalid),	// link
	DECL(sc_unlink),
	DECL(sc_invalid),	// chdir
	DECL(sc_invalid),	// chmod
	DECL(sc_lseek),
	DECL(sc_invalid),	// fstat
	DECL(sc_invalid),	// time
	DECL(sc_stat),
	DECL(sc_invalid),	// utime
	DECL(sc_invalid),	// assign_wrkmem
	DECL(sc_exit),
	DECL(sc_diropen),
	DECL(sc_dirclose),
	DECL(sc_dirread),
	DECL(sc_invalid)	// gethostinfo
};

int syscall(int scidx, uint32 param1, uint32 param2, uint32 param3) {
	int rv;

	if (scidx < 0 || scidx > (sizeof(syscalls)/sizeof(syscalls[0])))
		return -1;
	// printf("syscall(%d)\n", scidx);
	
	sl_mode = SLMODE_IMME;
	nif->if_start(nif);

	rv = syscalls[scidx](param1, param2, param3);

	nif->if_stop(nif);
	sl_mode = SLMODE_COOP;

	return rv;
}
