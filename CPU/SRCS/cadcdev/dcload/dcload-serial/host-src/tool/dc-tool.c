/* 
 * dc-tool, a tool for use with the dcload serial loader
 *
 * Copyright (C) 2001 Andrew Kieschnick <andrewk@napalm-x.com>
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.
 *
 */

#include <bfd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#ifdef _WIN32
#include <string.h>
#include <windows.h>
#else
#include <termios.h>
#endif
#include <sys/time.h>
#include <unistd.h>
#include <utime.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include "minilzo.h"
#include "syscalls.h"
#include "dc-io.h"

int _nl_msg_cat_cntr;
int gdb_server_socket = -1;

#define DCLOADBUFFER	16384 /* was 8192 */
#ifdef _WIN32
#define DATA_BITS	8
#define PARITY_SET	NOPARITY
#define STOP_BITS	ONESTOPBIT
#endif

#define VERSION "1.0.4"

#ifndef O_BINARY
#define O_BINARY 0
#endif

#define HEAP_ALLOC(var,size) \
        long __LZO_MMODEL var [ ((size) + (sizeof(long) - 1)) / sizeof(long) ]

static HEAP_ALLOC(wrkmem, LZO1X_1_MEM_COMPRESS);

#ifndef HAVE_GETOPT
/* The following code for getopt is from the libc-source of FreeBSD,
 * it might be changed a little bit.
 * Florian Schulze (florian.proff.schulze@gmx.net)
 */

/*
 * Copyright (c) 1987, 1993, 1994
 *      The Regents of the University of California.  All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 * 3. All advertising materials mentioning features or use of this software
 *    must display the following acknowledgement:
 *      This product includes software developed by the University of
 *      California, Berkeley and its contributors.
 * 4. Neither the name of the University nor the names of its contributors
 *    may be used to endorse or promote products derived from this software
 *    without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE REGENTS AND CONTRIBUTORS ``AS IS'' AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED.  IN NO EVENT SHALL THE REGENTS OR CONTRIBUTORS BE LIABLE
 * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS
 * OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 * LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY
 * OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF
 * SUCH DAMAGE.
 */

int     opterr = 1,             /* if error message should be printed */
        optind = 1,             /* index into parent argv vector */
        optopt,                 /* character checked for validity */
        optreset;               /* reset getopt */
char    *optarg;                /* argument associated with option */

#define BADCH   (int)'?'
#define BADARG  (int)':'
#define EMSG    ""

char *__progname="dc-tool";

/*
 * getopt --
 *      Parse argc/argv argument vector.
 */
int
getopt(nargc, nargv, ostr)
int nargc;
char * const *nargv;
const char *ostr;
{
    extern char *__progname;
    static char *place = EMSG;              /* option letter processing */
    char *oli;                              /* option letter list index */
    int ret;
    
    if (optreset || !*place) {              /* update scanning pointer */
	optreset = 0;
	if (optind >= nargc || *(place = nargv[optind]) != '-') {
	    place = EMSG;
	    return (-1);
	}
	if (place[1] && *++place == '-') {      /* found "--" */
	    ++optind;
	    place = EMSG;
	    return (-1);
	}
    }                                       /* option letter okay? */
    if ((optopt = (int)*place++) == (int)':' ||
	!(oli = strchr(ostr, optopt))) {
	/*
	 * if the user didn't specify '-' as an option,
	 * assume it means -1.
	 */
	if (optopt == (int)'-')
	    return (-1);
	if (!*place)
	    ++optind;
	if (opterr && *ostr != ':')
	    (void)fprintf(stderr,
			  "%s: illegal option -- %c\n", __progname, optopt);
	return (BADCH);
    }
    if (*++oli != ':') {                    /* don't need argument */
	optarg = NULL;
	if (!*place)
	    ++optind;
    }
    else {                                  /* need an argument */
	if (*place)                     /* no white space */
	    optarg = place;
	else if (nargc <= ++optind) {   /* no arg */
	    place = EMSG;
	    if (*ostr == ':')
		ret = BADARG;
	    else
		ret = BADCH;
	    if (opterr)
		(void)fprintf(stderr,
			      "%s: option requires an argument -- %c\n",
			      __progname, optopt);
	    return (ret);
	}
	else                            /* white space */
	    optarg = nargv[optind];
	place = EMSG;
	++optind;
    }
    return (optopt);                        /* dump back option letter */
}
#else
#include <unistd.h>
#endif

extern char *optarg;
#ifndef _WIN32
int dcfd;
struct termios oldtio;
#else
HANDLE hCommPort;
#endif

#ifdef _WIN32
int serial_read(void *buffer, int count)
{
    BOOL fSuccess;
    
    fSuccess = ReadFile(hCommPort, buffer, count, (DWORD *)&count, NULL);
    if( !fSuccess )
	return -1;
    return count;
}

int serial_write(void *buffer, int count)
{
    BOOL fSuccess;
    
    fSuccess = WriteFile(hCommPort, buffer, count, (DWORD *)&count, NULL);
    if( !fSuccess )
	return -1;
    return count;
}

int serial_putc(char ch)
{
    BOOL fSuccess;
    int count = 1;
    
    fSuccess = WriteFile(hCommPort, &ch, count, (DWORD *)&count, NULL);
    if( !fSuccess )
        return -1;
    return count;
}
#else
int serial_read(void *buffer, int count)
{
    return read(dcfd,buffer,count);
}

int serial_write(void *buffer, int count)
{
    return write(dcfd,buffer,count);
}

int serial_putc(char ch)
{
    return write(dcfd,&ch,1);
}
#endif

/* read count bytes from dc into buf */
void blread(void *buf, int count)
{
    int retval;
    unsigned char *tmp = buf;

    while (count) {
	retval = serial_read(tmp, count);
	if (retval == -1)
	    printf("blread: read error!\n");
	else {
	    tmp += retval;
	    count -= retval;
	}
    }
}

char serial_getc()
{
    int retval;
    char tmp;

    retval = serial_read(&tmp, 1);
    if (retval == -1) {
        printf("serial_getc: read error!\n");
	tmp = (char)NULL;
    }
    return tmp;
}

/* send 4 bytes */
int send_uint(unsigned int value)
{
    unsigned int tmp = value;
    
    /* send little-endian */    
    serial_putc((char)(tmp & 0xFF));
    serial_putc((char)((tmp >> 0x08) & 0xFF));
    serial_putc((char)((tmp >> 0x10) & 0xFF));
    serial_putc((char)((tmp >> 0x18) & 0xFF));

    /* get little-endian */
    tmp =  ((unsigned int) (serial_getc() & 0xFF));
    tmp |= ((unsigned int) (serial_getc() & 0xFF) << 0x08);
    tmp |= ((unsigned int) (serial_getc() & 0xFF) << 0x10);
    tmp |= ((unsigned int) (serial_getc() & 0xFF) << 0x18);

    if (tmp != value)
	return 0;

    return 1;
}

/* receive 4 bytes */
unsigned int recv_uint(void)
{
    unsigned int tmp;

    /* get little-endian */
    tmp =  ((unsigned int) (serial_getc() & 0xFF));
    tmp |= ((unsigned int) (serial_getc() & 0xFF) << 0x08);
    tmp |= ((unsigned int) (serial_getc() & 0xFF) << 0x10);
    tmp |= ((unsigned int) (serial_getc() & 0xFF) << 0x18);

    return (tmp);
}

/* receive total bytes from dc and store in data */
void recv_data(void *data, unsigned int total, unsigned int verbose)
{
    unsigned char type, sum, ok;
    unsigned int size, newsize;
    unsigned char *tmp;

    if (verbose) { 
	printf("recv_data: ");
	fflush(stdout);
    }
    
    while (total) {

	blread(&type, 1);

	size = recv_uint();

	switch (type) {
	case 'U':		// uncompressed
	    if (verbose) {
		printf("U");
		fflush(stdout);
	    }
	    blread(data, size);
	    blread(&sum, 1);
	    ok = 'G';
	    serial_write(&ok, 1);
	    total -= size;
	    (unsigned char *) data += size;
	    break;
	case 'C':		// compressed
	    if (verbose) {
		printf("C");
		fflush(stdout);
	    }
	    tmp = malloc(size);
	    blread(tmp, size);
	    blread(&sum, 1);
	    if (lzo1x_decompress(tmp, size, data, &newsize, 0) == LZO_E_OK) {
		ok = 'G';
		serial_write(&ok, 1);
		total -= newsize;
		(unsigned char *) data += newsize;
	    } else {
		ok = 'B';
		serial_write(&ok, 1);
		printf("\nrecv_data: decompression failed!\n");
	    }
	    free(tmp);
	    break;
	default:
	    break;
	}
    }
    if (verbose) {
	printf("\n");
	fflush(stdout);
    }
}

/* send size bytes to dc from addr */
void send_data(unsigned char * addr, unsigned int size, unsigned int verbose)
{
    unsigned int i;
    unsigned char *location = (unsigned char *) addr;
    unsigned char sum = 0;
    unsigned char data;
    unsigned int csize;
    unsigned int sendsize;
    unsigned char c;
    unsigned char * buffer;

    buffer = malloc(DCLOADBUFFER + DCLOADBUFFER / 64 + 16 + 3);

    if (verbose) {
	printf("send_data: ");
	fflush(stdout);
    }

    while (size) {
	if (size > DCLOADBUFFER)
	    sendsize = DCLOADBUFFER;
	else
	    sendsize = size;
	lzo1x_1_compress((unsigned char *)addr, sendsize, buffer, &csize, wrkmem);
	if (csize < sendsize) {
	    // send compressed
	    if (verbose) { 
		printf("C");
		fflush(stdout);
	    }
	    c = 'C';
	    serial_write(&c, 1);
	    send_uint(csize);
	    data = 'B';
	    while(data != 'G') {
		location = buffer;
		serial_write(location, csize);
		sum = 0;
		for (i = 0; i < csize; i++) {
		    data = *(location++);
		    sum ^= data;
		}
		serial_write(&sum, 1);
		blread(&data, 1);
	    }
	} else { 
	    // send uncompressed
	    if (verbose) {
		printf("U");
		fflush(stdout);
	    }
	    c = 'U';
	    serial_write(&c, 1);
	    send_uint(sendsize);
	    serial_write((unsigned char *)addr, sendsize);
	    sum = 0;
	    for (i = 0; i < sendsize; i++) {
		sum ^= ((unsigned char *)addr)[i];
	    }
	    serial_write(&sum, 1);
	    blread(&data, 1);
	}
	size -= sendsize;
	addr += sendsize;
    }
    if (verbose) {
	printf("\n");
	fflush(stdout);
    }
}

#ifdef _WIN32
void output_error(void)
{
    char *lpMsgBuf;
    
    FormatMessage(
	FORMAT_MESSAGE_ALLOCATE_BUFFER |
	FORMAT_MESSAGE_FROM_SYSTEM |
	FORMAT_MESSAGE_IGNORE_INSERTS,
	NULL,
	GetLastError(),
	MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT), // Default language
	(LPTSTR) &lpMsgBuf, 0, NULL // Process any inserts in lpMsgBuf.
	);
    printf("%s\n",(char *)lpMsgBuf);
    LocalFree( (LPVOID) lpMsgBuf );
}
#endif

/* setup serial port */
int open_serial(char *devicename, unsigned int speed, unsigned int *speedtest)
{
    *speedtest = speed;
#ifndef _WIN32
    struct termios newtio;
    speed_t speedsel;

    dcfd = open(devicename, O_RDWR | O_NOCTTY);
    if (dcfd < 0) {
	perror(devicename);
	exit(-1);
    }

    tcgetattr(dcfd, &oldtio);	// save current serial port settings
    memset(&newtio, 0, sizeof(newtio));	// clear struct for new port settings

    newtio.c_cflag = CRTSCTS | CS8 | CLOCAL | CREAD;
    newtio.c_iflag = IGNPAR;
    newtio.c_oflag = 0;
    newtio.c_lflag = 0;
    newtio.c_cc[VTIME] = 0;	// inter-character timer unused
    newtio.c_cc[VMIN] = 1;	// blocking read until 1 character arrives


    for (speedsel=0; !speedsel;) {
	switch(speed) {
#ifdef B1500000
	case 1500000:
	    speedsel = B1500000;
	    break;
#endif
#ifdef B500000
	case 500000:
	    speedsel = B500000;
	    break;
#endif
	case 115200:
	    speedsel = B115200;
	    break;
	case 57600:
	    speedsel = B57600;
	    break;
	case 38400:
	    speedsel = B38400;
	    break;
	case 19200:
	    speedsel = B19200;
	    break;
	case 9600:
	    speedsel = B9600;
	    break;
	default:
	    printf("Unsupported baudrate (%d) - switching to default (%d)\n", speed, BAUD_RATE);
	    *speedtest = speed = BAUD_RATE;
	    break;
	}
    }
    
    cfsetispeed(&newtio, speedsel);
    cfsetospeed(&newtio, speedsel);

    // we don't error on these because it *may* still work
    if (tcflush(dcfd, TCIFLUSH) < 0) {
	perror("tcflush");
    }
    if (tcsetattr(dcfd, TCSANOW, &newtio) < 0) {
	perror("tcsetattr");
	printf("warning: your baud rate is likely set incorrectly\n");
    }

#else
    BOOL fSuccess;
    COMMTIMEOUTS ctmoCommPort;
    DCB dcbCommPort;
    
    /* Setup the com port */
    hCommPort = CreateFile(devicename, GENERIC_READ | GENERIC_WRITE, 0,
			   NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, 0);
    
    if( hCommPort == INVALID_HANDLE_VALUE ) {   
	printf( "*Error opening com port\n");
	output_error();
	return -1;
    }
    
    ctmoCommPort.ReadIntervalTimeout = MAXDWORD;
    ctmoCommPort.ReadTotalTimeoutMultiplier = MAXDWORD;
    ctmoCommPort.ReadTotalTimeoutConstant = MAXDWORD;
    ctmoCommPort.WriteTotalTimeoutMultiplier = 0;
    ctmoCommPort.WriteTotalTimeoutConstant = 0;
    SetCommTimeouts( hCommPort, &ctmoCommPort );
    dcbCommPort.DCBlength = sizeof(DCB);
    
    fSuccess = GetCommState( hCommPort, &dcbCommPort );
    if( !fSuccess ) {
	printf( "*Error getting com port state\n" );
	output_error();
	return -1;
    }
    
    dcbCommPort.BaudRate = speed;
    dcbCommPort.ByteSize = DATA_BITS;
    dcbCommPort.Parity = PARITY_SET;
    dcbCommPort.StopBits = STOP_BITS;
    
    fSuccess = SetCommState( hCommPort, &dcbCommPort );
    if( !fSuccess ) {
	printf( "*Error setting com port state\n" );
	output_error();
	return -1;
    }
#endif
    return 0;
}

/* prepare for program exit */
void finish_serial(void)
{
#ifdef _WIN32
    FlushFileBuffers(hCommPort);
#else
    tcflush(dcfd, TCIOFLUSH);
    tcsetattr(dcfd, TCSANOW, &oldtio);
#endif
}

/* close the host serial port */
void close_serial(void)
{
#ifdef _WIN32
    FlushFileBuffers(hCommPort);
    CloseHandle(hCommPort);
#else
    tcflush(dcfd, TCIOFLUSH);
    close(dcfd);
#endif
}

int speedhack = 0;
/* speedhack controls whether dcload will use N=12 (normal, 4.3% error) or
 * N=13 (alternate, -3.1% error) for 115200
 */

/* use_extclk controls whether the DC's serial port will use an external clock */
int use_extclk = 0;

int change_speed(char *device_name, unsigned int speed)
{
    unsigned char c;
    unsigned int dummy, rv = 0xdeadbeef;

    c = 'S';
    serial_write(&c, 1);
    blread(&c, 1);
    if (speedhack && (speed == 115200))
	send_uint(111600); /* get dcload to pick N=13 rather than N=12 */
    else if (use_extclk)
	send_uint(0);
    else
	send_uint(speed);
    printf("Changing speed to %d bps... ", speed);
    close_serial();
    if (open_serial(device_name, speed, &dummy)<0)
	return 1;
    send_uint(rv);
    rv = recv_uint();
    printf("done\n");
}

int open_gdb_socket(int port)
{
  struct sockaddr_in server_addr;

  server_addr.sin_family = AF_INET;
  server_addr.sin_port = htons( port );
  server_addr.sin_addr.s_addr = htonl( INADDR_LOOPBACK );

  if ( (gdb_server_socket = socket( PF_INET, SOCK_STREAM, IPPROTO_TCP )) < 0 ) {
	perror( "error creating gdb server socket" );
	return -1;
  }

  if ( bind( gdb_server_socket, (struct sockaddr*)&server_addr, sizeof( server_addr ) ) < 0 ) {
	perror( "error binding gdb server socket" );
	return -1;
  }

  if ( listen( gdb_server_socket, 0 ) < 0 ) {
	perror( "error listening to gdb server socket" );
	return -1;
  }
}

void usage(void)
{
    printf("\ndc-tool %s by <andrewk@napalm-x.com>\n\n",VERSION);
    printf("-x <filename> Upload and execute <filename>\n");
    printf("-u <filename> Upload <filename>\n");
    printf("-d <filename> Download to <filename>\n");
    printf("-a <address>  Set address to <address> (default: 0x8c010000)\n");
    printf("-s <size>     Set size to <size>\n");
    printf("-t <device>   Use <device> to communicate with dc (default: %s)\n", SERIALDEVICE);
    printf("-b <baudrate> Use <baudrate> (default: %d)\n", BAUD_RATE);
    printf("-e            Try alternate 115200 (must also use -b 115200)\n");
    printf("-E            Use an external clock for the DC's serial port\n");
    printf("-n            Do not attach console and fileserver\n");
    printf("-p            Use dumb terminal rather than console/fileserver\n");
    printf("-q            Do not clear screen before download\n");
    printf("-c <path>     Chroot to <path> (must be super-user)\n");
    printf("-i <isofile>  Enable cdfs redirection using iso image <isofile>\n");
    printf("-g            Start a GDB server\n");
    printf("-h            Usage information (you\'re looking at it)\n\n");
    exit(0);
}

unsigned int upload(unsigned char *filename, unsigned int address)
{
    int inputfd;
    int size;
    unsigned char *inbuf;
    struct timeval starttime, endtime;
    unsigned char c;
    double stime, etime;
    bfd *somebfd;

    lzo_init();

    somebfd = bfd_openr(filename, 0);

    if (somebfd) { /* try bfd first */
	if (bfd_check_format(somebfd, bfd_object)) {
	    asection *section;
	    
	    printf("File format is %s, ", somebfd->xvec->name);
	    address = somebfd->start_address;
	    size = 0;
	    printf("start address is 0x%x\n", address);

	    gettimeofday(&starttime, 0);

	    for (section = somebfd->sections; section != NULL; section = section->next)
		if ((section->flags & SEC_HAS_CONTENTS) && (section->flags & SEC_LOAD)) {
		    printf("Section %s, ",section->name);
		    printf("lma 0x%x, ",section->lma);
		    printf("size %d\n",section->_raw_size);
		    if (section->_raw_size) {
			size += section->_raw_size;
			inbuf = malloc(section->_raw_size);
			bfd_get_section_contents(somebfd, section, inbuf, 0, section->_raw_size);

			c = 'B';
			serial_write(&c, 1);
			blread(&c, 1);
			
			send_uint(section->lma);
			send_uint(section->_raw_size);
			
			send_data(inbuf, section->_raw_size, 1);
			
			free(inbuf);
		    }
		}   
	    bfd_close(somebfd);
	} else {

/* if that fails, send raw bin */
		    
	    printf("File format is raw binary, start address is 0x%x\n", address);
    	    inputfd = open(filename, O_RDONLY | O_BINARY);
	    
	    if (inputfd < 0) {
		perror(filename);
		exit(-1);
	    }
	    
	    size = lseek(inputfd, 0, SEEK_END);
	    lseek(inputfd, 0, SEEK_SET);
	    
	    inbuf = malloc(size);
	    
	    read(inputfd, inbuf, size);
	    
	    close(inputfd);
	    
	    gettimeofday(&starttime, 0);
	    
	    c = 'B';
	    serial_write(&c, 1);
	    blread(&c, 1);
	    
	    send_uint(address);
	    send_uint(size);
	    
	    send_data(inbuf, size, 1);

	}

    gettimeofday(&endtime, 0);

    stime = starttime.tv_sec + starttime.tv_usec / 1000000.0;
    etime = endtime.tv_sec + endtime.tv_usec / 1000000.0;

    printf("effective: %.2f bytes / sec\n", (double) size / (etime - stime));
    printf("%.2f seconds to transfer %d bytes\n", (etime - stime), size);
    fflush(stdout);
    
    }
    return address;
}

void download(unsigned char *filename, unsigned int address,
	      unsigned int size, unsigned int quiet)
{
    int outputfd;

    unsigned char c;
    unsigned int wrkmem = 0x8cff0000;
    unsigned char *data;
    struct timeval starttime, endtime;
    double stime, etime;

    outputfd = open(filename, O_WRONLY | O_CREAT | O_TRUNC | O_BINARY, 0644);

    if (outputfd < 0) {
	perror(filename);
	exit(-1);
    }

    data = malloc(size);

    if (!quiet)
	serial_write("F", 1);
    else
	serial_write("G", 1);
    
    serial_read(&c, 1);
    
    send_uint(address);
    
    send_uint(size);
    
    send_uint(wrkmem);
    
    gettimeofday(&starttime, 0);
    
    recv_data(data, size, 1);
    
    gettimeofday(&endtime, 0);
    
    printf("Received %d bytes\n", size);
    
    stime = starttime.tv_sec + starttime.tv_usec / 1000000.0;
    etime = endtime.tv_sec + endtime.tv_usec / 1000000.0;
    
    printf("effective: %.2f bytes / sec\n", (double) size / (etime - stime));
    printf("%.2f seconds to transfer %d bytes\n", (etime - stime), size);
    fflush(stdout);
    
    write(outputfd, data, size);
    
    close(outputfd);
}

void execute(unsigned int address, unsigned int console)
{
    unsigned char c;

    printf("Sending execute command (0x%x, console=%d)...",address,console);

    serial_write("A", 1);
    serial_read(&c, 1);

    send_uint(address);
    send_uint(console);

    printf("executing\n");
}

void do_console(unsigned char *path, unsigned char *isofile)
{
    unsigned char command;
    int isofd;

    if (isofile) {
	isofd = open(isofile, O_RDONLY | O_BINARY);
	if (isofd < 0)
	    perror(isofile);
    }
	
    if (path)
	if (chroot(path))
	    perror(path);


    while (1) {
	fflush(stdout);
	serial_read(&command, 1);

	switch (command) {
	case 0:
	    finish_serial();
	    exit(0);
	    break;
	case 1:
	    dc_fstat();
	    break;
	case 2:
	    dc_write();
	    break;
	case 3:
	    dc_read();
	    break;
	case 4:
	    dc_open();
	    break;
	case 5:
	    dc_close();
	    break;
	case 6:
	    dc_creat();
	    break;
	case 7:
	    dc_link();
	    break;
	case 8:
	    dc_unlink();
	    break;
	case 9:
	    dc_chdir();
	    break;
	case 10:
	    dc_chmod();
	    break;
	case 11:
	    dc_lseek();
	    break;
	case 12:
	    dc_time();
	    break;
	case 13:
	    dc_stat();
	    break;
	case 14:
	    dc_utime();
	    break;
	case 15:
	    printf("command 15 should not happen... (but it did)\n");
	    break;
	case 16:
	    dc_opendir();
	    break;
	case 17:
	    dc_closedir();
	    break;
	case 18:
	    dc_readdir();
	    break;
	case 19:
	    dc_cdfs_redir_read_sectors(isofd);
	    break;
	case 20:
	    dc_gdbpacket();
	    break;
	default:
	    printf("Unimplemented command (%d) \n", command);
	    printf("Assuming program has exited, or something...\n");
	    finish_serial();
	    exit(0);
	    break;
	}
    }
    if (isofd)
	close(isofd);
}

/* dumb terminal mode
 * for programs that don't use dcload I/O functions
 * FIXME: should allow setting a different baud rate from what dcload uses
 * FIXME: should allow input
 */

void do_dumbterm(void)
{
    unsigned char c;

    printf("\nDumb terminal mode isn't implemented, so you get this half-assed one.\n\n");
    
    fflush(stdout);

    while (1) {
	blread(&c, 1);
	printf("%c", c);
	fflush(stdout);
    }
}

int main(int argc, char *argv[])
{
    unsigned int address = 0x8c010000;
    unsigned int size = 0;
    unsigned char *filename = 0;
    unsigned char *path = 0;
    unsigned int console = 1;
    unsigned int dumbterm = 0;
    unsigned int quiet = 0;
    unsigned char command = 0;
    unsigned int dummy, speed = BAUD_RATE;
    char *device_name = SERIALDEVICE;
    unsigned int cdfs_redir = 0;
    unsigned char *isofile = 0;
    int someopt;

    if (argc < 2)
	usage();

    someopt = getopt(argc, argv, "x:u:d:a:s:t:b:c:i:npqheEg");
    while (someopt > 0) {
	switch (someopt) {
	case 'x':
	    if (command) {
		printf("You can only specify one of -x, -u, and -d\n");
		exit(0);
	    }
	    command = 'x';
	    filename = malloc(strlen(optarg) + 1);
	    strcpy(filename, optarg);
	    break;
	case 'u':
	    if (command) {
		printf("You can only specify one of -x, -u, and -d\n");
		exit(0);
	    }
	    command = 'u';
	    filename = malloc(strlen(optarg) + 1);
	    strcpy(filename, optarg);
	    break;
	case 'd':
	    if (command) {
		printf("You can only specify one of -x, -u, and -d\n");
		exit(0);
	    }
	    command = 'd';
	    filename = malloc(strlen(optarg) + 1);
	    strcpy(filename, optarg);
	    break;
	case 'c':
	    path = malloc(strlen(optarg) + 1);
	    strcpy(path, optarg);
	    break;
	case 'i':
	    cdfs_redir = 1;
	    isofile = malloc(strlen(optarg) + 1);
	    strcpy(isofile, optarg);
	    break;
	case 'a':
	    address = strtoul(optarg, NULL, 0);
	    break;
	case 's':
	    size = strtoul(optarg, NULL, 0);
	    break;
	case 't':
	    device_name = malloc(strlen(optarg) + 1);
	    strcpy(device_name, optarg);
	    break;
	case 'b':
	    speed = strtoul(optarg, NULL, 0);
	    break;
	case 'n':
	    console = 0;
	    break;
	case 'p':
	    console = 0;
	    dumbterm = 1;
	    break;
	case 'q':
	    quiet = 1;
	    break;
	case 'h':
	    usage();
	    break;
	case 'e':
	    speedhack = 1;
	    break;
	case 'E':
	    use_extclk = 1;
	    break;
	case 'g':
	    printf("Starting a GDB server on port 2159\n");
	    open_gdb_socket(2159);
	    break;
	default:
	    break;
	}
	someopt = getopt(argc, argv, "x:u:d:a:s:t:b:c:i:npqhe");
    }

    if ((command == 'x') || (command == 'u')) {
	struct stat statbuf;
	if(stat(filename, &statbuf)) {
	    perror(filename);
	    exit(1);
	}
    }	

    if (console)
	printf("Console enabled\n");

    if (dumbterm)
	printf("Dumb terminal enabled\n");

    if (quiet)
	printf("Quiet download\n");

    if (path)
	printf("Chroot enabled\n");

    if (cdfs_redir)
	printf("Cdfs redirection enabled\n");

    if (speedhack)
	printf("Alternate 115200 enabled\n");

    /* test for resonable baud - this is for POSIX systems */
    if (speed != BAUD_RATE) {
	if (open_serial(device_name, speed, &speed)<0)
	    return 1;
        close_serial();
    }

    if (open_serial(device_name, BAUD_RATE, &dummy)<0)
        return 1;
    
    if (speed != BAUD_RATE)
	change_speed(device_name, speed);
    
    switch (command) {
    case 'x':
	if (cdfs_redir) {
	    unsigned char c;
	    c = 'H';
	    serial_write(&c, 1);
	    blread(&c, 1);
	}
	printf("Upload <%s>\n", filename);
	address = upload(filename, address);
	printf("Executing at <0x%x>\n", address);
	execute(address, console);
	if (console)
	    do_console(path, isofile);
	else if (dumbterm)
	    do_dumbterm();
	break;
    case 'u':
	printf("Upload <%s> at <0x%x>\n", filename, address);
	upload(filename, address);
	change_speed(device_name, BAUD_RATE);
	break;
    case 'd':
	if (!size) {
	    printf("You must specify a size (-s <size>) with download (-d <filename>)\n");
	    exit(0);
	}
	printf("Download %d bytes at <0x%x> to <%s>\n", size, address,
	       filename);
	download(filename, address, size, quiet);
	change_speed(device_name, BAUD_RATE);
	break;
    default:
	if (dumbterm)
	    do_dumbterm();
	else
	    usage();
	break;
    }
    exit(0);
}
