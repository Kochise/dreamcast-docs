extern void draw_string(int x, int y, char *string, int colour);
extern void clrscr(int colour);
extern void init_video(int cabletype, int pixelmode);
extern int check_cable(void);
extern unsigned char *get_font_address(void);
