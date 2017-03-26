/* Some serial routines 

   These routines can pretty easily be changed or replaced if you want
   to port this program to another system.

 */

#include "serial.h"

#define DEBUG printf

#include <fcntl.h>
#include <termios.h>

int serfd;

int ser_init(char *dev, int baud) {
	struct termios tios;

	serfd = open(dev, O_RDWR);
	if (serfd == -1) {
		DEBUG("couldn't open device %s at baud %d\n", dev, baud);
	}
	
	if (tcgetattr(serfd, &tios) < 0) {
		perror("couldn't get current termio parameters");
		return -1;
	}
	
	/* Input flags */
	tios.c_iflag = 0;
	
	/* Output flags */
	tios.c_oflag = 0;
	
	/* Control flags */
	tios.c_cflag = (tios.c_cflag & ~(CSIZE | PARENB))
		| (CS8 | CRTSCTS | CLOCAL);
	
	/* Local flags */
	tios.c_lflag = 0;
	
	/* Translate the baud rate */
	if (baud == 38400)
		baud = B38400;
	else if (baud == 57600)
		baud = B57600;
	else if (baud == 115200)
		baud = B115200;
	else {
		DEBUG("unknown baud rate %d, using 57600\n", baud);
		baud = B57600;
	}
	
	cfsetispeed(&tios, baud);
	cfsetospeed(&tios, baud);
	
	if (tcsetattr(serfd, TCSANOW, &tios) < 0) {
		perror("Couldn't set termio parameters for serial");
		return -1;
	}

	return 0;
}


void ser_close() {
	close(serfd);
}

void ser_putch(int ch) {
	char chbuf[1] = { (char)ch };
	if (write(serfd, chbuf, 1) < 0) {
		perror("couldn't write serial byte");
	}
}

int ser_getch() {
	char chbuf[1] = { 0 };
	if (read(serfd, chbuf, 1) < 1) {
		perror("couldn't read serial byte");
	}
	return chbuf[0];
}




