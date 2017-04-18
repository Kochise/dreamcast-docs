#ifndef __LCD_LIB__
#define __LCD_LIB__

void lcdInit(void);
void lcdSync(void);
void lcdDisp(void);
void lcdSetFrameBuf(void);
void lcdFillData(Uint8);
void lcdSetData(const Uint8 *,int,int,int);

#define LCD_MALLOC(dat) malloc(dat)

#define LCD_XSIZE   48
#define LCD_YSIZE   32
#define LCD_TXSIZE  64
#define LCD_FBUF_MASK     0x0f
#define LCD_FBUF_TRANS    0x80
#define LCD_FBUF_PRIORITY 0x70
#define LCD_PRIORITY_MIN 0
#define LCD_PRIORITY_MAX 7
#define LCD_FORCE_WRITE (LCD_PRIORITY_MAX+1)
#define LCD_NORMAL  (LCD_PRIORITY_MIN-1)

#define LCD_PRI(dat)    ((dat)&LCD_FBUF_PRIORITY)
#define LCD_TRANS(dat)  ((dat)&LCD_FBUF_TRANS)

/*#define _REAL_LCD_*/
#define _VIRTUAL_LCD_

#endif