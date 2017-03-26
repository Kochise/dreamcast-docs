#ifndef __SERIAL_H
#define __SERIAL_H

int ser_init(char* dev, int baud);
void ser_close();
void ser_putch(int ch);
int ser_getch();

#endif	/* __SERIAL_H */
