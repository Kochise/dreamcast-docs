/*=========================================================
     LCD sample library and apprication program
                         programmed by Jun Fuxima (CS1)
==========================================================*/

#include <shinobi.h>
#include "lcdlib.h"

/*==========================================================
   LCD system system works  v0.0.1
==========================================================*/

NJS_TEXNAME     lcdtexname[4];
NJS_TEXLIST     lcdtexlist = {lcdtexname,4};
NJS_TEXINFO     lcdtexinfo[4];
NJS_TEXMEMLIST  lcdtexmem[4];

Uint32   lcdFrameCount;
int revtest = 0;
static Uint32   lcdDispPerFrame;
static Uint8    lcdDispBuffer[LCD_XSIZE * LCD_YSIZE * 4];
static Uint16   lcdFrameBuffer[LCD_TXSIZE * LCD_YSIZE * 4];

/*==========================================================
   LCD system initializing routine  v0.0.2
        *buf ... for LCD display buffer (MATRIX)
                 size: 32x48(dot) x4(screen)
==========================================================*/
void lcdInit(void)
{
    int cnt;

/*
    lcdDispBuffer = LCD_MALLOC(LCD_XSIZE * LCD_YSIZE * 4);
    lcdFrameBuffer = LCD_MALLOC(LCD_TXSIZE * LCD_YSIZE * 2 * 4);
*/
    lcdDispPerFrame = 2; /* 30 frame/sec */
    lcdFrameCount = lcdDispPerFrame;

    for (cnt = 0;cnt < LCD_XSIZE * LCD_YSIZE * 4;cnt++) {
        lcdDispBuffer[cnt] = 0;
    }

    njSetTextureInfo(&lcdtexinfo[0],lcdFrameBuffer        ,NJD_TEXFMT_RECTANGLE|NJD_TEXFMT_ARGB_1555,64,32);
    njSetTextureInfo(&lcdtexinfo[1],lcdFrameBuffer+64*32  ,NJD_TEXFMT_RECTANGLE|NJD_TEXFMT_ARGB_1555,64,32);
    njSetTextureInfo(&lcdtexinfo[2],lcdFrameBuffer+64*32*2,NJD_TEXFMT_RECTANGLE|NJD_TEXFMT_ARGB_1555,64,32);
    njSetTextureInfo(&lcdtexinfo[3],lcdFrameBuffer+64*32*3,NJD_TEXFMT_RECTANGLE|NJD_TEXFMT_ARGB_1555,64,32);
    njSetTextureName(&lcdtexname[0],&lcdtexinfo[0],0,NJD_TEXATTR_TYPE_MEMORY | NJD_TEXATTR_GLOBALINDEX);
    njSetTextureName(&lcdtexname[1],&lcdtexinfo[1],1,NJD_TEXATTR_TYPE_MEMORY | NJD_TEXATTR_GLOBALINDEX);
    njSetTextureName(&lcdtexname[2],&lcdtexinfo[2],2,NJD_TEXATTR_TYPE_MEMORY | NJD_TEXATTR_GLOBALINDEX);
    njSetTextureName(&lcdtexname[3],&lcdtexinfo[3],3,NJD_TEXATTR_TYPE_MEMORY | NJD_TEXATTR_GLOBALINDEX);

    njInitTexture(lcdtexmem,4);
    njLoadTexture(&lcdtexlist);
    njSetTexture(&lcdtexlist);
}

/*==========================================================
   LCD system VSYNC trapped routine  v0.0.1
        *buf ... for LCD LCD display buffer (MATRIX)
==========================================================*/
void _dummyfx(void);
void lcdSync(void)
{
    Sint32 ret;
    int cnt;

    if (--lcdFrameCount == 0) {
        lcdFrameCount = lcdDispPerFrame;
        lcdSetFrameBuf();

        if(revtest != 0) {
            for(cnt=0;cnt<32*48;cnt++) {
                lcdDispBuffer[cnt]^=0x08;
            }
        }

        ret = pdVmsLcdWrite(PDD_PORT_A1, lcdDispBuffer, PDD_LCD_FLAG_HVFLIP);
    }
    lcdDisp();
}

/*==========================================================
   LCD system virtual displaying routine  v0.0.1
       (now only PAD1 display)
==========================================================*/
#define LCD_COLOR_ARGB1555(a,r,g,b) (((a)<<15)+((r)<<10)+((g)<<5)+(b))

void lcdDisp(void)
{
    int cnt1,cnt2;
    NJS_SPRITE  sp;
    NJS_TEXANIM an[] = {{LCD_XSIZE, LCD_YSIZE, 0, 0, 0, 0, 191, 255, 0, 0}};

    sp.p.x = 64;
    sp.p.y = 48;
    sp.sx=sp.sy = 4;
    sp.tlist = &lcdtexlist;
    sp.tanim = an;

    njSetTexture(&lcdtexlist);
    njSetTextureNum(0);

#if 1 /* Dummy loop */
#define _LOOPCNT 300
    for(cnt1 = 0; cnt1 < _LOOPCNT; cnt1++) {
        for(cnt2 = 0; cnt2 < _LOOPCNT; cnt2++) {
            _dummyfx();
        }
    }
#endif

    njReLoadTextureNum(0, lcdFrameBuffer, NJD_TEXATTR_TYPE_MEMORY, 0);
    njDrawSprite2D(&sp, 0, -150.f, NJD_SPRITE_ALPHA);
}

int _dmy;

void _dummyfx(void)
{
    _dmy++;
}
/*==========================================================
   LCD system DispBuffer to FrameBuffer routine v0.0.1
==========================================================*/
void lcdSetFrameBuf(void)
{
    int xcnt;
    int ycnt;
    int work;
    Uint8   *buf = lcdDispBuffer;
    Uint16  *fbuf = lcdFrameBuffer;

    for (ycnt = 0; ycnt<LCD_YSIZE; ycnt++) {
        for (xcnt = 0; xcnt<LCD_XSIZE; xcnt++) {
            if ((*buf & LCD_FBUF_MASK) < 8) {
                work = LCD_COLOR_ARGB1555(1,24,24,18);
            } else {
                work = LCD_COLOR_ARGB1555(1,0,0,0);
            }
            fbuf[ycnt * LCD_TXSIZE + xcnt] = work;
            buf++;
        }
    }
}
/*==========================================================
   LCD system DispBuffer fill routine v0.0.1
      data ... fill data
==========================================================*/
void lcdFillData(Uint8 data)
{
    int xcnt;
    int ycnt;
    Uint8   *buf = lcdDispBuffer;

    for (ycnt = 0; ycnt < LCD_YSIZE; ycnt++) {
        for (xcnt = 0; xcnt < LCD_XSIZE; xcnt++) {
            buf[ycnt * LCD_XSIZE + xcnt] = data;
        }
    }
}
/*==========================================================
   LCD system Object setting routine v0.0.1
      *objbuf ... OBJ pattern buffer (xsize,ysize,data,...)
==========================================================*/
void lcdSetData(const Uint8 *objbuf, int xpos, int ypos, int priority)
{
    int xcnt;
    int ycnt;
    int xsize;
    int ysize;
    int index;
    Uint8   *buf = lcdDispBuffer;

    xsize = objbuf[0] * 256 + objbuf[1];
    ysize = objbuf[2] * 256 + objbuf[3];
    objbuf += 4;

    if (priority < LCD_PRIORITY_MIN) {
        for (ycnt = ypos; ycnt < (ysize + ypos); ycnt++) {
            for (xcnt = xpos; xcnt<(xsize + xpos); xcnt++) {
                if ((xcnt >= 0) && (xcnt < LCD_XSIZE) && (ycnt >= 0) && (ycnt < LCD_YSIZE)) {
                    index = ycnt * LCD_XSIZE + xcnt;
                    if (((LCD_PRI(buf[index]) <= LCD_PRI(*objbuf)) || LCD_TRANS(buf[index])) && (LCD_TRANS(*objbuf)==0)) {
                        buf[index] = *objbuf;
                    }
                }
                objbuf++;
            }
        }
    } else {
        priority = priority << 4;
        for (ycnt = ypos; ycnt < (ysize + ypos); ycnt++) {
            for (xcnt = xpos; xcnt < (xsize + xpos); xcnt++) {
                if ((xcnt >= 0) && (xcnt < LCD_XSIZE) && (ycnt >= 0) && (ycnt < LCD_YSIZE)) {
                    index = ycnt * LCD_XSIZE + xcnt;
                    if (LCD_TRANS(*objbuf) == 0) {
                        if (((buf[index] & LCD_FBUF_PRIORITY) < priority) || ((buf[index] & LCD_FBUF_TRANS)==0)) {
                           buf[index]=(*objbuf & LCD_FBUF_MASK) | priority;
                        }
                    }
                }
                objbuf++;
            }
        }
    }
}
