#include "cdfs.h"


/*
 * Serial port handling code
 */

void serial_init(int baudrate)
{
  volatile unsigned char *s = (unsigned char *)(void *)0xffe80000;
  *((volatile unsigned short *)(s+8)) = 0;
  *((volatile unsigned short *)(s)) = 0;
  s[4] = 50000000/(32*baudrate)-1;
  *((volatile unsigned short *)(s+24)) = 12;
  *((volatile unsigned short *)(s+24)) = 8;
  *((volatile unsigned short *)(s+32)) = 0;
  *((volatile unsigned short *)(s+16)) = 0x60;
  *((volatile unsigned short *)(s+36)) = 0;
  *((volatile unsigned short *)(s+8)) = 0x30;
}

void send(unsigned char c)
{
  volatile unsigned char *s = (unsigned char *)(void *)0xffe8000c;
  int v;
  while(!((v=((volatile unsigned short *)s)[2]) & 0x20));
  *s = c;
  ((volatile unsigned short *)s)[2] = v & 0x9f;
}

void flush()
{
  volatile unsigned short *s = (unsigned short *)(void *)0xffe80010;
  int v;
  *s &= 0xbf;
  while(!((v=*s) & 0x40));
  *s = v & 0xbf;
}

void sendstr(char *str)
{
  while(*str++)
    send(((unsigned char *)str)[-1]);
}

void sendnum(int n)
{
  char buf[16], *p;
  if(n<0) {
    send('-');
    n = -n;
  }
  p=buf+16;
  *--p = '\0';
  do {
    *--p = '0'+(n%10);
    n /= 10;
  } while(n);
  sendstr(p);
}


/* Dummy stub to make libgcc happy... */
void atexit() { }


/*
 * Simple demo program.
 * Displays the root directory and the contents of READ_ME.TXT
 * on the serial port.
 *
 */
int main()
{
  int fd;
  DIR *d;

  serial_init(57600);

  /*
   * First, cdfs_init() has to be called to reactivate the drive and
   * initialize the GDROM syscalls
   */
  cdfs_init();

  /*
   * Print the contents of the root directory
   */
  d = opendir("/");
  if(!d)
    sendstr("opendir failed.\r\n");
  else {
    struct dirent *de;
    while((de = readdir(d))) {
      /* Found an entry */
      if(de->d_size < 0) {
	sendstr(" DIR: ");
	sendstr(de->d_name);
	sendstr("\n");
      } else {
	sendstr("FILE: ");
	sendstr(de->d_name);
	sendstr(" : ");
	sendnum(de->d_size);
	sendstr(" bytes\r\n");
      }
    }
    /* End of dir */
    closedir(d);
  }

  /*
   * Print the contents of READ_ME.TXT
   */
  fd = open("READ_ME.TXT", O_RDONLY);
  if(fd<0)
    sendstr("File not found.\r\n");
  else {
    static char buf[2048];
    int i, r;
    /* Read 2048 bytes at a time and display them */
    while((r = read(fd, buf, sizeof(buf)))>0)
      for(i=0; i<r; i++)
	send(buf[i]);
    /* Error or EOF reached */
    if(r<0)
      sendstr("ERROR!\r\n");
    close(fd);
  }

  flush();

  return 0;
}
