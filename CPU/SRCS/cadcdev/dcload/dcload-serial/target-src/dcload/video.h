#ifndef __VIDEO_H__
#define __VIDEO_H__

void draw_string(int x, int y, char *string, int colour);
void clrscr(int colour);
void init_video(int cabletype, int pixelmode);
int check_cable(void);
unsigned char *get_font_address(void);

#endif
