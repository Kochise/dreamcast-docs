/* Title: GP2X minimal library v0.B
   Written by rlyeh, (c) 2005.

   Please check readme for licensing and other conditions. */

#include "minimal.h"

/* Typedef: gp2x_rect
   This type definition is used to blit bitmaps and/or sprites into screen.
   It contains the following public fields { x,y,w,h,solid,*data; }

   Note:
   - Set and use the fields manually.
   - <gp2x_blitter_rect> expects the gp2x_rect to be filled ok.

   Fields:
   x - Horizontal coordinate in pixels.
   y - Vertical coordinate in pixels.
   w - Width size in pixels.
   h - Height size in pixels.
   solid - 0 for transparent sprites (black is transparent). 1 for solid rects.
   data - pointer to your sprite/rect data.

   See also:
   <gp2x_blitter_rect> */

/* Typedef: gp2x_font
   This type definition is used to create a custom font.
   It contains the following public fields { x,y,w,h,fg,bg,solid,*data; }

   Note:
   - Use <gp2x_printf_init> to set the variables into a gp2x_font struct.
   Do not set them manually.

   Fields:
   w - Width of each character, in pixels.
   h - Height of each character, in pixels.
   fg - Foreground font color.
   bg - Background font color (when solid is not 0).
   solid - When 1, background font color is used.
           When 0, transparent background font is used.
   data - Pointer to your font bitmap.

   See also:
   <gp2x_printf>, <gp2x_printf_init> */

/* Enumeration: GP2X joystick values
   This enumeration contains all the possible values which <gp2x_joystick_read> may return.

   Constants:
   GP2X_UP        - joystick up
   GP2X_DOWN      - joystick down
   GP2X_LEFT      - joystick left
   GP2X_RIGHT     - joystick right
   GP2X_PUSH      - joystick push
   GP2X_L         - button L
   GP2X_R         - button R
   GP2X_A         - button A
   GP2X_B         - button B
   GP2X_X         - button X
   GP2X_Y         - button Y
   GP2X_START     - button START
   GP2X_SELECT    - button SELECT
   GP2X_VOL_DOWN  - button volume down (-)
   GP2X_VOL_UP    - button volume up (+)

   See also:
   <gp2x_joystick_read> */

/* Macro: gp2x_dualcore_data(address)

   This macro retrieves or sets a value into a shared address; it works for both 920T and 940T cores.

   Memory map for our shared area for the current library:

    range 0x00000000-0x00000FFF (4  kb) is reserved                             

    range 0x00001000-0x00007FFF (8  kb) is free, and non-cacheable

    range 0x00008000-0x00F00000 (15 Mb) is free, and cacheable

   Usage:
   To be written

   See also:
   <gp2x_dualcore_pause>, <gp2x_dualcore_sync>, <gp2x_dualcore_exec> */


/* Variable: gp2x_ticks
   Internal variable which holds current conversion between desired ticks and GP2X ticks.

   Note:
   - Do not modify this variable directly. Use <gp2x_init> instead.

   See also:
   <gp2x_timer_read>, <gp2x_timer_delay> */


/* Variable: gp2x_video_YUV
   This struct allows you to work directly with YUV video layer.
   It contains three pointers which are updated in each <gp2x_video_YUV_flip> call.
   There are for YUV regions, each one with its own framebuffer. Each framebuffer orientation is top-left (common orientation).

   Contains:
   screen8  - 08 bits pointer to the hidden video surface.
   screen16 - 16 bits pointer to the hidden video surface.
   screen32 - 32 bits pointer to the hidden video surface. This is the default pointer when working in Y/Cb/Cr video mode.

   Note:
   - Use <gp2x_video_YUV_flip> to flip video surfaces and to update the screen pointers.
   - Use <gp2x_video_YUV_color> to calculate colors when you are working in Y/Cb/Cr video mode.

   Example:
   > gp2x_video_YUV[1].screen32[160+120*320]=gp2x_video_YUV_color(255,255,255);  //write white at (160,120)
   > gp2x_video_YUV_flip(1); */

   gp2x_video_layer gp2x_video_YUV[4];

/* Variable: gp2x_video_RGB
   This struct allows you to work directly with RGB video layer.
   It contains three pointers which are updated in each <gp2x_video_RGB_flip> call.
   There is a single RGB region, with a single framebuffer. The framebuffer orientation is top-left (common orientation).

   Contains:
   screen8  - 08 bits pointer to the hidden video surface. This is the default pointer when working in palettized video mode.
   screen16 - 16 bits pointer to the hidden video surface. This is the default pointer when working in hicolor video mode.
   screen32 - 32 bits pointer to the hidden video surface.

   Note:
   - Use <gp2x_video_RGB_flip> to flip video surfaces and to update the screen pointers.
   - Use <gp2x_video_RGB_color15> to calculate colors when you are working in hicolor video mode.
   - Use <gp2x_video_RGB_color8> to set colors when working in palettized video mode.
   - Use <gp2x_video_RGB_setpalette> to flush any change in the palette.

   Example:
   > gp2x_video_RGB[0].screen16[160+120*320]=gp2x_video_RGB_color15(255,255,255, 0); //write white at (160,120)
   > gp2x_video_RGB_flip(0);
   >
   > or...
   >
   > gp2x_video_RGB_color8(255,255,255, 1);
   > gp2x_video_RGB_setpalette();
   > gp2x_video_RGB[0].screen8[160+120*320]=1;                                       //write white at (160,120)
   > gp2x_video_RGB_flip(0); */

   gp2x_video_layer gp2x_video_RGB[1];


static          pthread_t       gp2x_sound_thread, gp2x_video_logo_thread;
static          unsigned long   gp2x_dev[8]={0,0,0,0,0,0,0,0}, gp2x_ticks_per_second;
static          unsigned short *gp2x_sound_buffer;
static volatile unsigned short *gp2x_memregs;
static volatile unsigned short  gp2x_video_RGB_palette[512], gp2x_video_OSD_palette[512];
static volatile unsigned long   gp2x_ticks;
static volatile unsigned long  *gp2x_memregl, gp2x_sound_pausei, gp2x_exit;
       volatile unsigned long  *gp2x_dualcore_ram;


/*
   ,--------------------.
   |                    |X
   |    GP2X - VIDEO    |X
   |                    |X
   `--------------------'X
    XXXXXXXXXXXXXXXXXXXXXX 
*/


/* Function: gp2x_video_waitvsync
   This function halts the program until a vertical sync is done.

   See also:
   <gp2x_video_waithsync> */

void gp2x_video_waitvsync(void)
{
  while(gp2x_memregs[0x1182>>1]&(1<<4));
}

/* Function: gp2x_video_waithsync
   This function halts the program until an horizontal sync is done.

   See also:
   <gp2x_video_waitvsync> */

void gp2x_video_waithsync(void)
{
  while(gp2x_memregs[0x1182>>1]&(1<<5));
}

/* Function: gp2x_video_setgammacorrection
   This function sets the Gamma correction value for the whole display.

   Parameters:
   gamma (0.00 .. 2.00) - from 0.00 (darkest) to 2.00 (brightest).

   Default:
   - gamma is set to 1.00 */

void gp2x_video_setgammacorrection(float gamma)
{
  int i;

  //enable gamma
  gp2x_memregs[0x2880>>1]&=~(1<<12);

  gp2x_memregs[0x295C>>1]=0;
  for(i=0,gamma=2.0-gamma;i<256;i++)
  {
   unsigned char g=(unsigned char)(0.5+255.0*pow(i/255.0,gamma));
   gp2x_memregs[0x295E>>1]=(g<<8)|g; gp2x_memregs[0x295E>>1]=g;
  }
}

/* Function: gp2x_video_setdithering
   This function sets the dithering values for all the video layers.

   Note:
   - This function only works when merging layers of different bits per pixel.
   
   Parameters:
   mode (0,1,2) - set mode to 0 for 2x2 dithering, 1 for 4x4 dithering, and 2 to disable dithering.

   Default:
   - mode is set to 0 (2x2 dithering). */

void gp2x_video_setdithering(int mode)
{
  gp2x_memregs[0x2946>>1]=mode;
}

/* Function: gp2x_video_setluminance
   This function sets the contrast/brigness values for the YUV/OSD layers.

   Parameters:
   contrast (0..7) - adjusts contrast where as 0=1.00, 1=1.125... 7=1.875 are contrast values.
   brightness (0..255) - adjusts brightness.

   Default:
   - contrast is set to 0
   - brightness is set to 0 */

void gp2x_video_setluminance(int contrast, int brightness)
{
  gp2x_memregs[0x2934>>1]=((contrast&0x07)<<8)|brightness;
}





/*
   ,-----------------------.
   |                       |X
   |  GP2X - VIDEO - OSD   |X
   |                       |X
   `-----------------------'X
    XXXXXXXXXXXXXXXXXXXXXXXXX 
*/

#if 0
//Prototypes following...
//This function returns a VUYA (A/Y/Cb0/Cr0) 32bits color pixel from a given R,G,B triad and alpha value.
unsigned long gp2x_video_OSD_color(int R, int G, int B, int A)
{
  int Y = ( (  66 * R + 129 * G +  25 * B + 128) >> 8) + 16,
      U = ( ( -38 * R -  74 * G + 112 * B + 128) >> 8) + 128,
      V = ( ( 112 * R -  94 * G -  18 * B + 128) >> 8) + 128;

  return ((A&0xFF)<<24) | ((Y&0xFF)<<16) | ((U&0xFF)<<8) | ((V&0xFF)<<0);
}

void gp2x_video_OSD_setpalette(void)
{
  unsigned short *g=(unsigned short *)gp2x_video_OSD_palette; int i=512;
  gp2x_memregs[0x2954>>1]=0;                                                     
  while(i--) gp2x_memregs[0x2956>>1]=*g++; 
}

void gp2x_video_OSD_flip(void)
{
  unsigned long address=0;

  gp2x_memregs[0x2916>>1]=(unsigned short)(address & 0xFFFF);
  gp2x_memregs[0x2918>>1]=(unsigned short)(address >> 16);
  gp2x_memregs[0x291A>>1]=(unsigned short)(address & 0xFFFF);
  gp2x_memregs[0x291C>>1]=(unsigned short)(address >> 16);
}

void gp2x_video_OSD_write_header(void)
{
 unsigned long *top_header;
 unsigned long *region_header;

 global_mix = 0..1
 alpha_value = 0..15

 transparent = 0..1
 transparent color = 0..255

 top = 11 bits
 bottom = 11 bits
 x = 11 bits
 y = 11 bits

 if(global_mix)
 {
  alpha_value,transparent,transparent_color = valid;
 }
 else
 {
  alpha_value = from palette
 }

 //OSD enable
 memregs[0x2880>>1]|=(1<<7);

 *top_header=&region_header;

 //set no next region address
 *(region_header+0)=0;

 //set last region header, uncompressed data, 8bpp, 1 pel
 *(region_header+1)=(1<<30)|(0<<29)|(2<<28)|(0<<27)
 //set global/palettized region alpha value
                   |(global_mix<<26)|(alpha_value<<22)
 //set top/bottom region
                   |(top<<11)|(bottom<<0);
 
 *(region_header+2)=(transparent<<30)|(transparent_color<<22)|(x<<11)|(y<<0);
}
#endif



/*
   ,-----------------------.
   |                       |X
   | GP2X - VIDEO - CURSOR |X
   |                       |X
   `-----------------------'X
    XXXXXXXXXXXXXXXXXXXXXXXXX 
*/

static  int          gp2x_video_cursor_phys;
static void         *gp2x_video_cursor_virt;
static unsigned char gp2x_video_cursor_default[] = {
1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
1,2,1,0,0,0,0,0,0,0,0,0,0,0,0,0,
1,2,2,1,0,0,0,0,0,0,0,0,0,0,0,0,
1,2,2,2,1,0,0,0,0,0,0,0,0,0,0,0,
1,2,2,2,2,1,0,0,0,0,0,0,0,0,0,0,
1,2,2,2,2,2,1,0,0,0,0,0,0,0,0,0,
1,2,2,2,2,2,2,1,0,0,0,0,0,0,0,0,
1,2,2,2,2,2,2,2,1,0,0,0,0,0,0,0,
1,2,2,2,2,2,2,2,2,1,0,0,0,0,0,0,
1,2,2,2,2,1,1,1,1,1,1,0,0,0,0,0,
1,2,2,2,1,0,0,0,0,0,0,0,0,0,0,0,
1,2,2,1,0,0,0,0,0,0,0,0,0,0,0,0,
1,2,1,0,0,0,0,0,0,0,0,0,0,0,0,0,
1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0
};


/* Function: gp2x_video_cursor_show
   This function shows or hides the cursor.

   Parameters:
   yes (0,1) - set 1 for showing cursor, and 0 to hiding it.

   Default:
   - yes is set to 0 (hide).

   See also:
   <gp2x_video_cursor_move>, <gp2x_video_cursor_setalpha>, <gp2x_video_cursor_setup> */

void gp2x_video_cursor_show(int yes)
{
  gp2x_memregs[0x2880>>1] &=  ~(1<<9);
  gp2x_memregs[0x2880>>1] |= (yes<<9);
}

/* Function: gp2x_video_cursor_move
   This function updates the cursor coordinates.

   Parameters:
   x (-32767..32768) - x cursor position.
   y (-32767..32768) - y cursor position.

   Default:
   - (x,y) are set to center of screen.

   See also:
   <gp2x_video_cursor_show>, <gp2x_video_cursor_setalpha>, <gp2x_video_cursor_setup> */

void gp2x_video_cursor_move(int x, int y)
{
  gp2x_memregs[0x2920>>1] = x;
  gp2x_memregs[0x2922>>1] = y; 
}

/* Function: gp2x_video_cursor_setalpha
   This function sets the alpha blending of both background and foreground cursor colors.

   Parameters:
   FG_A (0..15) - Foreground alpha blending value.
   BG_A (0..15) - Background alpha blending value.

   Default:
   - FG_A and BG_A both are set to 15 (100% solid, no transparency).

   See also:
   <gp2x_video_cursor_show>, <gp2x_video_cursor_move>, <gp2x_video_cursor_setup> */

void gp2x_video_cursor_setalpha(int FG_A, int BG_A)
{
  gp2x_memregs[0x291e>>1] &= ~((0xF<<12)|(0xF<<8));
  gp2x_memregs[0x291e>>1] |=  (FG_A<<12)|(BG_A<<8);
}

/* Function: gp2x_video_cursor_setup
   This function sets the shape, size, colour and alpha blending of the cursor.

   Parameters:
   *src - pointer to a data area containing the cursor shape.
          each byte in the area corresponds to a pixel in the cursor shape.
          you can define your own foreground (FG), background (BG) and transparent (any other else) colors.
   size (8,16,32,64) - square size of the cursor shape.
   FG (0..255) - byte which identifies foreground pixels in your *src area. Usually set to 1.
   FG_R (0..255) - red component for your foreground shape color
   FG_B (0..255) - green component for your foreground shape color
   FG_G (0..255) - blue component for your foreground shape color
   FG_A (0..15) - alpha blending for foreground shape color 
   BG (0..255) - byte which identifies foreground pixels in your *src area. Usually set to 0 or 2.
   BG_R (0..255) - red component for background shape color
   BG_B (0..255) - green component for background shape color
   BG_G (0..255) - blue component for background shape color
   BG_A (0..15) - alpha blending for background shape color 

   Default:
   - The default cursor holds an arrow sprite of 16 pixels.
     Its foreground color defaults to white, and background one to black. 
     There is no transparency set for the default cursor.

   See also:
   <gp2x_video_cursor_show>, <gp2x_video_cursor_move>, <gp2x_video_cursor_setalpha> */

void gp2x_video_cursor_setup(unsigned char *src, int size, unsigned char FG, int FG_R, int FG_G, int FG_B, int FG_A, unsigned char BG, int BG_R, int BG_G, int BG_B, int BG_A)
{
  unsigned char *dst=(unsigned char *)gp2x_video_cursor_virt;
  int x, c;

  //convert shape
  for(*dst=x=c=0;x<size*size; )
  {
   *dst|=(*src==FG ? 0 : (*src==BG ? 1 : 2) ) << c; c+=2;

   src++;

   if(!((++x)%4)) *(++dst)=c=0;
  }

  //set fg/bg alpha and cursor dimensions
  gp2x_memregs[0x291e>>1] =  (FG_A<<12)|(BG_A<<8) | size; 

  //set cursor position at center of screen
  gp2x_video_cursor_move((320-size)/2,(240-size)/2); 

  //set cursor colors
  gp2x_memregs[0x2924>>1] = (FG_G<<8)|FG_R;
  gp2x_memregs[0x2926>>1] = FG_B;
  gp2x_memregs[0x2928>>1] = (BG_G<<8)|BG_R;
  gp2x_memregs[0x292a>>1] = BG_B;

  //set cursor bitmap
  gp2x_memregs[0x292c>>1]=(unsigned short)(gp2x_video_cursor_phys & 0xFFFF);
  gp2x_memregs[0x292e>>1]=(unsigned short)(gp2x_video_cursor_phys >> 16);
  gp2x_memregs[0x2930>>1]=(unsigned short)(gp2x_video_cursor_phys & 0xFFFF);
  gp2x_memregs[0x2932>>1]=(unsigned short)(gp2x_video_cursor_phys >> 16);
}




/*
   ,---------------------.
   |                     |X
   | GP2X - VIDEO - LOGO |X
   |                     |X
   `---------------------'X
    XXXXXXXXXXXXXXXXXXXXXXX 
*/

static unsigned char gp2x_video_logo_default[] = {
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,0,
0,1,1,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,1,1,0,
0,1,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,1,0,
0,1,2,2,2,2,2,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,2,2,2,1,1,2,2,2,1,0,
0,1,2,2,2,2,1,1,2,2,2,2,2,2,2,2,2,2,2,2,2,2,1,2,2,1,1,2,2,2,1,0,
0,1,2,2,2,1,1,1,1,1,1,1,1,1,2,1,1,1,1,1,1,1,1,1,2,1,1,2,2,2,1,0,
0,1,2,2,2,1,2,1,2,2,2,2,2,1,2,1,2,2,2,2,2,1,2,1,2,1,1,2,2,2,1,0,
0,1,2,2,2,1,2,1,2,2,2,2,2,1,2,1,2,2,2,2,2,1,2,1,2,1,1,2,2,2,1,0,
0,1,2,2,2,1,2,1,2,2,2,2,2,1,2,1,2,2,2,2,2,1,2,1,2,1,1,2,2,2,1,0,
0,1,2,2,2,1,2,1,2,2,2,2,2,1,2,1,2,2,2,2,2,1,2,1,2,1,1,2,2,2,1,0,
0,1,2,2,2,1,2,1,2,2,2,2,2,1,2,1,2,2,2,2,2,1,2,1,2,1,1,2,2,2,1,0,
0,1,2,2,2,1,2,1,2,2,2,2,2,1,2,1,2,2,2,2,2,1,2,1,2,1,1,2,2,2,1,0,
0,1,2,2,2,1,1,1,2,2,2,2,2,1,1,1,2,2,2,2,2,1,1,1,2,1,1,2,2,2,1,0,
0,1,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,1,0,
0,1,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,1,0,
0,1,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,1,0,
0,1,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,1,0,
0,1,2,2,2,2,2,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,2,2,2,1,1,2,2,2,1,0,
0,1,2,2,2,2,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,2,2,1,1,2,2,2,1,0,
0,1,2,2,2,1,1,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,1,1,2,1,1,2,2,2,1,0,
0,1,2,2,2,1,1,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,1,1,2,1,1,2,2,2,1,0,
0,1,2,2,2,1,1,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,1,1,2,1,1,2,2,2,1,0,
0,1,2,2,2,1,1,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,1,1,2,1,1,2,2,2,1,0,
0,1,2,2,2,1,1,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,1,1,2,1,1,2,2,2,1,0,
0,1,2,2,2,1,1,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,1,1,2,1,1,2,2,2,1,0,
0,1,2,2,2,1,1,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,1,1,2,1,1,2,2,2,1,0,
0,1,2,2,2,1,1,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,1,1,2,1,1,2,2,2,1,0,
0,1,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,1,0,
0,1,1,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,1,1,0,
0,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,0,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 };

static void *gp2x_video_logo_anim(void *blah)
{
  int i; struct timespec ts; ts.tv_sec=3, ts.tv_nsec=25000000; //0.025 seconds delay

  nanosleep(&ts, NULL);

  ts.tv_sec=0;

  for(i=0xF;i>=0x0 && !gp2x_exit;i--) { gp2x_video_cursor_setalpha(((i*0xE)/0xF)+1,((i*0xD)/0xF)+2);
                                        nanosleep(&ts, NULL); }

  return NULL;
  //pthread_exit( NULL );
}

/* Function: gp2x_video_logo_enable
   This function displays the minimal logo watermarked at bottom right of screen.
   Adding this logo to your application makes rlyeh (me) happier and glad with you :-)

   Note:
   - Note that this function uses the cursor layer to work, so you cannot display a cursor and the minimal logo at same time.

   Parameters:
   yes (0,1) - 1 enables logo. 0 disables it.

   Default:
   - yes is set to 0. Logo is disabled by default. */

void gp2x_video_logo_enable(int yes)
{
 gp2x_video_cursor_show(0);

 if(yes) { gp2x_video_cursor_setup(gp2x_video_logo_default, 32, 2,32,32,255,0xF, 1,255,255,255,0xF);
           gp2x_video_cursor_move(320-32,240-32);
           gp2x_video_cursor_show(1);
           pthread_create( &gp2x_video_logo_thread, NULL, gp2x_video_logo_anim, NULL); }
}




/*
   ,--------------------.
   |                    |X
   | GP2X - VIDEO - RGB |X
   |                    |X
   `--------------------'X
    XXXXXXXXXXXXXXXXXXXXXX 
*/



/* Function: gp2x_video_RGB_color8
   This function sets the palettized color entry C to a given triad of R,G,B components.
   All color changes will get updated at next <gp2x_video_RGB_setpalette> call.

   Note:
   - Use <gp2x_video_RGB_setpalette> to flush all palette changes.

   Parameters:
   C (0..255) - Palettized color entry to change
   R (0..255) - Red component
   G (0..255) - Green component
   B (0..255) - Blue component 

   See also:
   <gp2x_video_RGB_setpalette> */ 

void gp2x_video_RGB_color8 (int R, int G, int B, int C)
{
  gp2x_video_RGB_palette[((C)<<1)+0]=((G)<<8)|(B),gp2x_video_RGB_palette[((C)<<1)+1]=(R); 
}


/* Function: gp2x_video_RGB_color15
   This function returns the 16bits color for a given triad of R,G,B components.
   It returns a short in 5515:RGAB format.

   Parameters:
   R (0..255) - Red component
   G (0..255) - Green component 
   B (0..255) - Blue component 
   A (0,1) - General purpose boolean value. Usually sets to 0. */

unsigned short gp2x_video_RGB_color15(int R, int G, int B, int A)
{
  return ((((R)&0xF8)<<8)|(((G)&0xF8)<<3)|(((B)&0xF8)>>3)|((A)<<5));
}

/* Function: gp2x_video_RGB_color16
   This function returns the 16bits color for a given triad of R,G,B components.
   It returns a short in 565:RGB format.

   Parameters:
   R (0..255) - Red component
   G (0..255) - Green component 
   B (0..255) - Blue component */

unsigned short gp2x_video_RGB_color16(int R, int G, int B)
{
  return ((((R)&0xF8)<<8)|(((G)&0xFC)<<3)|(((B)&0xF8)>>3));
}


/* Function: gp2x_video_RGB_setpalette
   This function updates the whole 8 bits palette into screen.
   To change each palette color use <gp2x_video_RGB_color8>

   See also:
   <gp2x_video_RGB_color8> */

void gp2x_video_RGB_setpalette(void)
{
  unsigned short *g=(unsigned short *)gp2x_video_RGB_palette; int i=512;
  gp2x_memregs[0x2958>>1]=0;                                                     
  while(i--) gp2x_memregs[0x295A>>1]=*g++; 
}


/* Function: gp2x_video_RGB_setcolorkey
   This function sets the colorkey transparent value for all RGB colorkeyed regions.

   Notes:
   - This R,G,B triad uses 0..15 units instead of 0..255.
   - All regions marked as 0x10 will transparent those pixels which match the given R,G,B triad.
  
   Parameters:
   R (0..15) - red component
   G (0..15) - green component
   B (0..15) - blue component 

   Default:
   - R,G,B are set to 0.

   See also:
   <gp2x_video_RGB_setwindows> */

void gp2x_video_RGB_setcolorkey(int R, int G, int B)
{
 gp2x_memregs[0x2902>>1]=((G&0xF)<<4)+(B&0xF), gp2x_memregs[0x2904>>1]=R&0xF;
}


/* Function: gp2x_video_RGB_setscaling
   This function adjusts a given resolution to fit the whole display (320,240).

   Notes:
   - Draw at (0,0) coordinates always, whatever resolution you are working with.
   - Call this function once. Do not call this function in every frame.
  
   Parameters:
   W (1..) - virtual width in pixels to scale to 320.
   H (1..) - virtual height in pixels to scale to 240.

   Default:
   - (W,H) are set to (320,240). */

void gp2x_video_RGB_setscaling(int W, int H)
{
  int bpp=(gp2x_memregs[0x28DA>>1]>>9)&0x3;

  // scale horizontal
  gp2x_memregs[0x2906>>1]=(unsigned short)((float)1024.0    *(W/320.0));
  // scale vertical
  gp2x_memregl[0x2908>>2]=(unsigned  long)((float)320.0*bpp *(H/240.0)); 
}


/* Function: gp2x_video_RGB_flip
   This function flips video buffers. It updates pointers located at <gp2x_video_RGB> struct too.
   The current pointers will point to the hidden display until a new gp2x_video_RGB_flip() call is done.

   Note:
   - This function does not wait for the vertical/horizontal retraces. You should use <gp2x_video_waitvsync> or <gp2x_video_waithsync> if needed.
   - RGB has one layer, one region and four windows. Everything works merged in the same layer.
   - It is a mistake confusing 'layer', 'region', 'part' and 'window'. They are not the same.

   Parameters:
   layer (0) - RGB layer to flip. Note that currently there is support for RGB layer 0 only.

   See also:
   <gp2x_video_YUV_flip> */

void gp2x_video_RGB_flip(int layer)
{
  unsigned long address=gp2x_video_RGB[layer].i[gp2x_video_RGB[layer].i[7]];

  if(++gp2x_video_RGB[layer].i[7]==4) gp2x_video_RGB[layer].i[7]=0;
  gp2x_video_RGB[layer].screen32=(unsigned long  *)gp2x_video_RGB[layer].p[gp2x_video_RGB[layer].i[7]];
  gp2x_video_RGB[layer].screen16=(unsigned short *)gp2x_video_RGB[layer].screen32;
  gp2x_video_RGB[layer].screen8 =(unsigned char  *)gp2x_video_RGB[layer].screen32;

  gp2x_memregs[0x290E>>1]=gp2x_memregs[0x2912>>1]=(unsigned short)(address & 0xFFFF);
  gp2x_memregs[0x2910>>1]=gp2x_memregs[0x2914>>1]=(unsigned short)(address >> 16);
}


/* Function: gp2x_video_RGB_setwindows
   This function enables, disables and sets screen up to four RGB windows.

   Notes:
   - You can disable a window by setting a negative value.
   - Any positive value will cause the window to be alpha blended (0..0x0F), to act as a sprite (0x10), or to be solid (0x11).
   - Alpha values are in 0..15 range. Think about it like a 0% to 100% blending in steps of 6.25%.
   - <gp2x_video_RGB_setcolorkey> sets the transparent pixel color for *all* regions.
  
   Parameters:
   window0 (-1..17) - -1 to disable window0, 0..0xF for alpha blending window0, 0x10 for transparent window0, 0x11 for solid window0
   window1 (-1..17) - -1 to disable window1, 0..0xF for alpha blending window1, 0x10 for transparent window1, 0x11 for solid window1
   window2 (-1..17) - -1 to disable window2, 0..0xF for alpha blending window2, 0x10 for transparent window2, 0x11 for solid window2
   window3 (-1..17) - -1 to disable window3, 0..0xF for alpha blending window3, 0x10 for transparent window3, 0x11 for solid window3
   x,y ((0,0)..(320,240)) - Screen coordinate which breaks resolution into 4 regions. Check diagrams below for a few examples.

   >
   > +-------+-------+ (x,y) = (160,120)  +-----------+---+ (x,y) = (240,180)  +---------------+ (x,y) = (319,239)
   > |       |       |                    |           |   |                    |               |
   > |   0   |   1   |                    |           |   |                    |               |
   > |       |       |                    |     0     | 1 |                    |               |
   > +-------P-------+                    |           |   |                    |       0       |
   > |       |       |                    |           |   |                    |               |
   > |   2   |   3   |                    +-----------P---+                    |               |
   > |       |       |                    |     2     | 3 |                    |               |
   > +-------+-------+                    +-----------+---+                    +---------------P
   >
   >
   > +-------+-------+ (x,y) = (160,239)  +---------------+ (x,y) = (0,239)    +---------------+ (x,y) = (0,120)
   > |       |       |                    |               |                    |               |
   > |       |       |                    |               |                    |       1       |
   > |       |       |                    |               |                    |               |
   > |   0   |   1   |                    |       1       |                    P---------------+
   > |       |       |                    |               |                    |               |
   > |       |       |                    |               |                    |       3       |
   > |       |       |                    |               |                    |               |
   > +-------P-------+                    P---------------+                    +---------------+
   >
   >
   > P---------------+ (x,y) = (0,0)      +---+-----------+ (x,y) = (80,60)    +-------P-------+ (x,y) = (160,0)
   > |               |                    | 0 |     1     |                    |       |       |
   > |               |                    +---P-----------+                    |       |       |
   > |               |                    |   |           |                    |       |       |
   > |       3       |                    |   |           |                    |   2   |   3   |
   > |               |                    | 2 |     3     |                    |       |       |
   > |               |                    |   |           |                    |       |       |
   > |               |                    |   |           |                    |       |       |
   > +---------------+                    +---+-----------+                    +-------+-------+
   >
   >
   > +---------------P (x,y) = (319,0)    +---------------+ (x,y) = (319,120)    
   > |               |                    |               |                    
   > |               |                    |       0       |                    
   > |               |                    |               |                    
   > |       2       |                    +---------------P                    
   > |               |                    |               |                    
   > |               |                    |       2       |                    
   > |               |                    |               |                     
   > +---------------+                    +---------------+                     etc...
   >

   Default:
   - (window0,window1,window2,window3) are set to (0x11,-1,-1,-1).
   - (x,y) are set to (319,239).

   See also:
   <gp2x_video_RGB_setcolorkey> */

void gp2x_video_RGB_setwindows(int window0, int window1, int window2, int window3, int x, int y)
{
  int window,mode,mode2,x1,y1,x2,y2;

  //enable all RGB windows
  gp2x_memregs[0x2880>>1]|=(1<<6)|(1<<5)|(1<<4)|(1<<3)|(1<<2);

  for(window=0;window<4;window++) //windows 0..3
  {
   if(window==0) x1=0, y1=0, x2=x,   y2=y  , mode=window0;
   if(window==1) x1=x, y1=0, x2=319, y2=y  , mode=window1;
   if(window==2) x1=0, y1=y, x2=x,   y2=239, mode=window2;
   if(window==3) x1=x, y1=y, x2=319, y2=239, mode=window3;

   if(mode<0) { gp2x_memregs[0x28da>>1]&=~(1<<(window<<1)); }
   else {
          mode2=(mode>0x0F?0xF:mode);

          //set alpha 0..0xE / colorkey,solid 0xF value
          if(window<3)
          {
           gp2x_memregs[0x28de>>1]&=~(mode2<<(window<<2)); 
           gp2x_memregs[0x28de>>1]|= (mode2<<(window<<2));
          }
          else
          {
           gp2x_memregs[0x28e0>>1]&=~(mode2<<((window-3)<<2)); 
           gp2x_memregs[0x28e0>>1]|= (mode2<<((window-3)<<2)); 
          }

          //set window as blended (2), transparent/colorkey (1), solid (0)          
          gp2x_memregs[0x28dc>>1]&=~(3                                      <<(window<<1));   
          gp2x_memregs[0x28dc>>1]|= ((mode==0x11 ? 0 : (mode==0x10 ? 1 : 2))<<(window<<1)); 
          
          //window coordinates
          gp2x_memregs[(0x28e2+window*8)>>1]=x1;     
          gp2x_memregs[(0x28e4+window*8)>>1]=x2;
          gp2x_memregs[(0x28e6+window*8)>>1]=y1;
          gp2x_memregs[(0x28e8+window*8)>>1]=y2;

          //enable window
          gp2x_memregs[0x28da>>1]|=(3<<(window<<1)); 
        }
  }
}




/*
   ,--------------------.            
   |                    |X
   | GP2X - VIDEO - YUV |X
   |                    |X
   `--------------------'X
    XXXXXXXXXXXXXXXXXXXXXX 
*/


/* Function: gp2x_video_YUV_color
   This function returns a YUY2 (Cr0/Y1/Cb0/Y0) 32bits color pixel from a given R,G,B triad.

   Parameters:
   R (0..255) - red component
   G (0..255) - green component
   B (0..255) - blue component

   Credits:
   RobBrown */

unsigned long gp2x_video_YUV_color(int R, int G, int B)
{
   int Y = ( (R<<9) + (G<<8) + (B<<8) + (R<<14) + (G<<15) + (B<<11) + (B<<12) + 0x108000 ) & 0xFF0000,
       U = ( (B<<7) - (B<<4) - (R<<5) - (R<<2) - (R<<1) - (G<<6) - (G<<3) - (G<<1) + 0x8080 ) & 0xFF00,
       V = ( (R<<23) - (R<<20) - (G<<21) - (G<<22) + (G<<17) - (B<<20) - (B<<17) + 0x80800000 ) & 0xFF000000;
 
   return (V | Y | U | (Y>>16));
}

#if 0
unsigned long gp2x_video_YUV_color(int R, int G, int B)
{
  int Y = ( (  66 * R + 129 * G +  25 * B + 128) >> 8) + 16,
      U = ( ( -38 * R -  74 * G + 112 * B + 128) >> 8) + 128,
      V = ( ( 112 * R -  94 * G -  18 * B + 128) >> 8) + 128;

  return ((V&0xFF)<<24) | ((Y&0xFF)<<16) | ((U&0xFF)<<8) | ((Y&0xFF)<<0);
}
#endif

/* Function: gp2x_video_YUV_setscaling
   This function adjusts a given resolution to fit the whole display (320,240).

   Notes:
   - Draw at (0,0) coordinates of each framebuffer always, whatever resolution you are working with.
   - Call this function once. Do not call this function in every frame.
  
   Parameters:
   region (0..3) - YUV region (0..3)
   W (1..) - virtual width in pixels to scale to 320.
   H (1..) - virtual height in pixels to scale to 240.

   Default:
   - (W,H) are set to (320,240) for each region. */

void gp2x_video_YUV_setscaling(int region, int W, int H)
{
  int reg=(region&1 ? 0x28B0:0x2886), bottom=(region&2);

  gp2x_memregs[(reg+0x0+bottom)>>1]       = (unsigned short)((float)1024.0  *(W/320.0));
  gp2x_memregs[(reg+0x4+(bottom<<=1))>>1] = (unsigned short)((float)320.0*2 *(H/240.0)); 
  gp2x_memregs[(reg+0x6+bottom)>>1]       = 0;
}


/* Function: gp2x_video_YUV_flip
   This function flips video buffers. It updates pointers located at <gp2x_video_YUV> struct too.
   The current pointers will point to the hidden display until a new gp2x_video_YUV_flip() call is done.

   Note:
   - This function does not wait for the vertical/horizontal retraces. You should use <gp2x_video_waitvsync> or <gp2x_video_waithsync> if needed.
   - YUV has 2 layers (A/B), 4 regions and no windows.
   - It is a mistake confusing 'window', 'region', 'part' and 'layer'. They are not the same.

   Parameters:
   region (0..3) - YUV layer to flip 

   See also:
   <gp2x_video_RGB_flip> */

void gp2x_video_YUV_flip(int region)
{
  int regions[4]={0x28A0,0x28CA,0x28A8,0x28D2};
  unsigned long address=gp2x_video_YUV[region].i[gp2x_video_YUV[region].i[7]];

  if(gp2x_video_YUV[region].i[6]&1) address+=320*240*2;
  if(gp2x_video_YUV[region].i[6]&2) address+=320*2;

  if(++gp2x_video_YUV[region].i[7]==2) gp2x_video_YUV[region].i[7]=0;
  gp2x_video_YUV[region].screen32=(unsigned long  *)gp2x_video_YUV[region].p[gp2x_video_YUV[region].i[7]]; 
  gp2x_video_YUV[region].screen16=(unsigned short *)gp2x_video_YUV[region].screen32;
  gp2x_video_YUV[region].screen8 =(unsigned char  *)gp2x_video_YUV[region].screen32;
  
  gp2x_memregs[(regions[region]+0)>>1]=(unsigned short)(address & 0xFFFF);  
  gp2x_memregs[(regions[region]+2)>>1]=(unsigned short)(address >> 16);
  gp2x_memregs[(regions[region]+4)>>1]=(unsigned short)(address & 0xFFFF);
  gp2x_memregs[(regions[region]+6)>>1]=(unsigned short)(address >> 16);
}


/* Function: gp2x_video_YUV_setparts
   This function enables, disables and sets up screen to four YUV parts.

   Notes:
   - You can disable a region by setting a negative value.
   - Any positive value will active the region, and force mirroring or not.
  
   Parameters:
   part0 (-1..3) - -1 disables part0, 0 sets no mirroring, 1 sets vertical mirroring, 2 sets horizontal mirroring, 3 sets both mirrors
   part1 (-1..3) - -1 disables part1, 0 sets no mirroring, 1 sets vertical mirroring, 2 sets horizontal mirroring, 3 sets both mirrors
   part2 (-1..3) - -1 disables part2, 0 sets no mirroring, 1 sets vertical mirroring, 2 sets horizontal mirroring, 3 sets both mirrors
   part3 (-1..3) - -1 disables part3, 0 sets no mirroring, 1 sets vertical mirroring, 2 sets horizontal mirroring, 3 sets both mirrors
   x,y ((0,0)..(320,240)) - Screen coordinate which breaks resolution into 4 parts. Check diagrams below for a few examples.

   >
   > +-------+-------+ (x,y) = (160,120)  +-----------+---+ (x,y) = (240,180)  +---------------+ (x,y) = (319,239)
   > |       |       |                    |           |   |                    |               |
   > |   0   |   1   |                    |           |   |                    |               |
   > |       |       |                    |     0     | 1 |                    |               |
   > +-------P-------+                    |           |   |                    |       0       |
   > |       |       |                    |           |   |                    |               |
   > |   2   |   3   |                    +-----------P---+                    |               |
   > |       |       |                    |     2     | 3 |                    |               |
   > +-------+-------+                    +-----------+---+                    +---------------P
   >
   >
   > +-------+-------+ (x,y) = (160,239)  +---------------+ (x,y) = (0,239)    +---------------+ (x,y) = (0,120)
   > |       |       |                    |               |                    |               |
   > |       |       |                    |               |                    |       1       |
   > |       |       |                    |               |                    |               |
   > |   0   |   1   |                    |       1       |                    P---------------+
   > |       |       |                    |               |                    |               |
   > |       |       |                    |               |                    |       3       |
   > |       |       |                    |               |                    |               |
   > +-------P-------+                    P---------------+                    +---------------+
   >
   >
   > P---------------+ (x,y) = (0,0)      +---+-----------+ (x,y) = (80,60)    +-------P-------+ (x,y) = (160,0)
   > |               |                    | 0 |     1     |                    |       |       |
   > |               |                    +---P-----------+                    |       |       |
   > |               |                    |   |           |                    |       |       |
   > |       3       |                    |   |           |                    |   2   |   3   |
   > |               |                    | 2 |     3     |                    |       |       |
   > |               |                    |   |           |                    |       |       |
   > |               |                    |   |           |                    |       |       |
   > +---------------+                    +---+-----------+                    +-------+-------+
   >
   >
   > +---------------P (x,y) = (319,0)    +---------------+ (x,y) = (319,120)    
   > |               |                    |               |                    
   > |               |                    |       0       |                    
   > |               |                    |               |                    
   > |       2       |                    +---------------P                    
   > |               |                    |               |                    
   > |               |                    |       2       |                    
   > |               |                    |               |                     
   > +---------------+                    +---------------+                     etc...
   >

   Default:
   - (part0,part1,part2,part3) are set to (-1,-1,-1,-1).
   - (x,y) are set to (319,239). */

void gp2x_video_YUV_setparts(int part0, int part1, int part2, int part3, int x, int y)
{
  int e0=part0>=0, e1=part1>=0, e2=part2>=0, e3=part3>=0;

  if(!e0) part0=0; gp2x_video_YUV[0].i[6]=part0; 
  if(!e1) part1=0; gp2x_video_YUV[1].i[6]=part1; 
  if(!e2) part2=0; gp2x_video_YUV[2].i[6]=part2; 
  if(!e3) part3=0; gp2x_video_YUV[3].i[6]=part3; 

  //enable top regions A (0), B (1)
  gp2x_memregs[0x2880>>1]&=~((1<<1)|(1<<0));
  gp2x_memregs[0x2880>>1]|= (e1<<1)|(e0<<0);

  //enable bottom regions A (4), B (9)
  gp2x_memregs[0x2882>>1]&=~((1<<9)|(1<<4));   
  gp2x_memregs[0x2882>>1]|= (e3<<9)|(e2<<4);   

  //set vertical mirroring and/or horizontal mirroring for each region
  gp2x_memregs[0x2882>>1]&=~((3<<7)|(3<<5)|(3<<2)|(3<<0));
  gp2x_memregs[0x2882>>1]|= (part1<<7)|(part3<<5)|(part0<<2)|(part2<<0);

  //set coordinates for A top, A bottom, B top and B bottom regions
  gp2x_memregs[0x2896>>1]=0;     
  gp2x_memregs[0x2898>>1]=x;   
  gp2x_memregs[0x289A>>1]=0;     
  gp2x_memregs[0x289C>>1]=y;   
  gp2x_memregs[0x289E>>1]=239;   
  gp2x_memregs[0x28C0>>1]=x;     
  gp2x_memregs[0x28C2>>1]=319;   
  gp2x_memregs[0x28C4>>1]=0;     
  gp2x_memregs[0x28C6>>1]=y;   
  gp2x_memregs[0x28C8>>1]=239;

  //flush mirroring changes (if any) into current framebuffers
  gp2x_video_YUV_flip(0); gp2x_video_YUV_flip(1); gp2x_video_YUV_flip(2); gp2x_video_YUV_flip(3);
  gp2x_video_YUV_flip(0); gp2x_video_YUV_flip(1); gp2x_video_YUV_flip(2); gp2x_video_YUV_flip(3);
}







/*
   ,--------------------.
   |                    |X
   |   GP2X - BLITTER   |X
   |                    |X
   `--------------------'X
    XXXXXXXXXXXXXXXXXXXXXX 
*/


/* Function: gp2x_blitter_rect
   This function blits a <gp2x_rect> into screen.

   Note:
   This function does not perform any clipping.
  
   Parameters:
   *r - Pointer to a <gp2x_rect> struct */

void (*gp2x_blitter_rect)(gp2x_rect *r);

void gp2x_blitter_rect15(gp2x_rect *r)
{
  int x, y; unsigned short *data=(unsigned short *)r->data, *offset=&gp2x_video_RGB[0].screen16[r->x+r->y*320];

  x=r->w, y=r->h; if(r->solid)
                  while(y--) { while(x--) *offset++=*data++; offset+=320-(x=r->w); }
                  else
                  while(y--) { while(x--) { if(*data) *offset=*data; offset++, data++; }
                               offset+=320-(x=r->w); }
}

void gp2x_blitter_rect8(gp2x_rect *r)
{
  int x, y; unsigned char *data=(unsigned char *)r->data,   *offset=&gp2x_video_RGB[0].screen8[r->x+r->y*320]; 

  x=r->w, y=r->h; if(r->solid)
                  while(y--) { while(x--) *offset++=*data++; offset+=320-(x=r->w); }
                  else
                  while(y--) { while(x--) { if(*data) *offset=*data; offset++, data++; }
                               offset+=320-(x=r->w); }
}



/*
   ,--------------------.
   |                    |X
   |   GP2X - JOYSTICK  |X
   |                    |X
   `--------------------'X
    XXXXXXXXXXXXXXXXXXXXXX 
*/



/* Function: gp2x_joystick_read
   This function returns the active <GP2X joystick values>.

   Note:
   Call this function once per frame keep your joystick values updated.

   Usage:
   In order to detect simultaneous values you will have to mask the value.

   See also:
   <GP2X joystick values>

   Example:
   > unsigned long pad=gp2x_joystick_read();
   >
   > if(pad&GP2X_R) if(pad&GP2X_L) ... //both L and R are pressed. */

unsigned long gp2x_joystick_read(void)
{
  unsigned long value=(gp2x_memregs[0x1198>>1] & 0x00FF);

  if(value==0xFD) value=0xFA;
  if(value==0xF7) value=0xEB;
  if(value==0xDF) value=0xAF;
  if(value==0x7F) value=0xBE;
 
  return ~((gp2x_memregs[0x1184>>1] & 0xFF00) | value | (gp2x_memregs[0x1186>>1] << 16));
}



/*
   ,--------------------.
   |                    |X
   |    GP2X - TIMER    |X
   |                    |X
   `--------------------'X
    XXXXXXXXXXXXXXXXXXXXXX 
*/



/* UNUSED
unsigned long gp2x_timer_read3(void)
{
  static unsigned long last=0, ticks=0;
         unsigned long current=gp2x_memregl[0xA00>>2];

  current+=(current < last ? (0xFFFFFFFF-last) : -last);

  return (ticks += ( (last=current) / gp2x_ticks_per_second ));
}

unsigned long gp2x_timer_read2(void)
{
  static unsigned long last=0, ticks=0;

  ticks += ((gp2x_memregl[0x0A00>>2]-last)/gp2x_ticks_per_second);
  last   =   gp2x_memregl[0x0A00>>2];
  return ticks;
} 
*/


/* Function: gp2x_timer_delay
   This function halts the program for a given delay in <gp2x_ticks> units.

   Parameters:
   ticks (1..) - delay in <gp2x_ticks> units.

   See also:
   <gp2x_timer_read>, <gp2x_ticks> */

void gp2x_timer_delay(unsigned long ticks)
{
  unsigned long target=gp2x_memregl[0x0A00>>2]+ticks*gp2x_ticks_per_second;
  while(gp2x_memregl[0x0A00>>2]<target);
//unsigned long mark=gp2x_timer_read(); while(gp2x_timer_read()-mark<ticks);
}

/* Function: gp2x_timer_read
   This function returns elapsed ticks in <gp2x_ticks> units since last <gp2x_init> call.

   Note:
   - There is no currently way to reset <gp2x_ticks> value to 0.

   See also:
   <gp2x_timer_delay>, <gp2x_ticks> */

unsigned long gp2x_timer_read(void)
{
  return gp2x_memregl[0x0A00>>2]/gp2x_ticks_per_second;
}




/*
   ,--------------------.
   |                    |X
   |    GP2X - SOUND    |X
   |                    |X
   `--------------------'X
    XXXXXXXXXXXXXXXXXXXXXX 
*/


/* Function: gp2x_sound_frame
   This function is automatically called by the library, and expects a sound buffer to be filled in.

   Notes:
   - This function is not included in the library itself.
   - Supply this function in your own program.
   - Do not call this function directly.

   Parameters:
   *blah - unused in this release.
   *buffer - pointer to store the sound data.
   samples - number of *samples*, *NOT* bytes.

   Examples:
   Check samples section. */

extern void gp2x_sound_frame(void *blah, void *buffer, int samples);

/* Function: gp2x_sound_volume
   This function sets the sound volume.

   Parameters:
   L (0..100) - volume percentage for the left channel
   R (0..100) - volume percentage for the right channel

   Note:
   - A higher percentage than 100 will distort your sound.

   Default:
   - L is set to 100.
   - R is set to 100.

   See also:
   <gp2x_sound_pause>

   Credits:
   snaff */

void gp2x_sound_volume(int L /*0..100*/, int R /*0..100*/)
{
 L=(((L*0x50)/100)<<8)|((R*0x50)/100);          
 ioctl(gp2x_dev[4], SOUND_MIXER_WRITE_PCM, &L); 
}

/* Function: gp2x_sound_pause
   This function pauses and unpauses the sound.

   Parameters:
   yes (0,1) - set it to 1 to enable pause (mute sound), and 0 to disable pause (play sound).

   See also:
   <gp2x_sound_volume> */

void gp2x_sound_pause(int yes) { gp2x_sound_pausei=yes; }

static void *gp2x_sound_play(void *blah)
{
  int flip1=0, flip2=gp2x_sound_buffer[1];
  //struct timespec ts; ts.tv_sec=0, ts.tv_nsec=(gp2x_sound_buffer[3]<<16)|gp2x_sound_buffer[2];

  while(!gp2x_exit)     { //nanosleep(&ts, NULL);
                          if(!gp2x_sound_pausei) { gp2x_sound_frame(blah, (void *)(&gp2x_sound_buffer[4+flip1]), gp2x_sound_buffer[0]);
                                                   write(gp2x_dev[3],     (void *)(&gp2x_sound_buffer[4+flip2]), gp2x_sound_buffer[1]);

                                                   flip1+=gp2x_sound_buffer[1]; if(flip1==gp2x_sound_buffer[1]*8) flip1=0;
                                                   flip2+=gp2x_sound_buffer[1]; if(flip2==gp2x_sound_buffer[1]*8) flip2=0;   }}
  return NULL;
  //pthread_exit( NULL );
}





/*
   ,--------------------.
   |                    |X
   |   GP2X - DUALCORE  |X
   |                    |X
   `--------------------'X
    XXXXXXXXXXXXXXXXXXXXXX 
*/



static void gp2x_initqueue(gp2x_queue *q, unsigned long queue_items, unsigned long *position920t, unsigned long *position940t)
{
  q->head  = q->tail  = q->items = 0;
  q->max_items = queue_items;
  if(position920t) q->place920t=position920t; else q->place920t=(unsigned long *)malloc(sizeof(unsigned long) * queue_items);
  if(position940t) q->place940t=position940t;
  memset(q->place920t, 0, sizeof(unsigned long) * queue_items);
}

static void gp2x_enqueue(gp2x_queue *q, unsigned long data)
{	
  while(q->items==q->max_items); /*waiting for tail to decrease...*/
  q->place920t[q->head = (q->head < q->max_items ? q->head+1 : 0)] = data;
  q->items++;
}

/* UNUSED
 static unsigned long gp2x_dequeue(gp2x_queue *q)
{
  while(!q->items); //waiting for head to increase...
  q->items--;
  return q->place920t[q->tail = (q->tail < q->max_items ? q->tail+1 : 0)];
} */


static void gp2x_save_registers(int mode)  //0=save, 1=restore, 2=restore & exit 
{                 
 static unsigned short *reg=NULL; unsigned long ints, i,c;
 unsigned short savereg[]={     //0x0904>>1,0x0904>>1, //Clocks & power management
                                //0x0912>>1,0x0912>>1, //Clocks & power management
                                //0x091C>>1,0x091C>>1, //Clocks & power management
                                //0x3B40>>1,0x3B48>>1, //Dual CPU
                                0x2880>>1,0x28AE>>1, //YUV A
                                0x28B0>>1,0x28D8>>1, //YUV B
                                0x28DA>>1,0x28E8>>1, //RGB
                                0x290C>>1,0x290C>>1, //RGB - line width
                                0x291E>>1,0x2932>>1, //Cursor
//                              0x1800>>1,0x1836>>1, //Scale processor
//                              0x2800>>1,0x2848>>1, //Display controller
//                              0x2880>>1,0x2980>>1, //Multilayer controller
//                              0x3000>>1,0x30F2>>1, //Image signal processor
                                0,0};

 if(reg==NULL) reg=(unsigned short *)malloc(0x10000);

 ints=gp2x_memregl[0x0808>>2];
 gp2x_memregl[0x0808>>2] = 0xFF8FFFE7;  //mask interrupts

 if(mode) {for(c=0;savereg[c];c+=2) for(i=savereg[c];i<=savereg[c+1];i++) gp2x_memregl[i]=reg[i];}
     else {for(c=0;savereg[c];c+=2) for(i=savereg[c];i<=savereg[c+1];i++) reg[i]=gp2x_memregl[i];}
     
 if(mode==2) { free(reg); reg=NULL; }

 gp2x_memregl[0x0808>>2]=ints;
}

              
/* Function: gp2x_dualcore_pause
   This function pauses the secondary ARM 940T coprocessor.

   Note:
   - Call this function only from your 920T program.

   Parameters:
   yes (0,1) - set it to 1 to enable pause (halt 940T), and 0 to disable pause (run 940T).

   See also:
   <gp2x_dualcore_sync>, <gp2x_dualcore_exec>, <gp2x_dualcore_data(address)> */

       void gp2x_dualcore_pause(int yes) { if(yes) gp2x_memregs[0x0904>>1] &= 0xFFFE; else gp2x_memregs[0x0904>>1] |= 1; }
static void gp2x_940t_reset(int yes)     { gp2x_memregs[0x3B48>>1] = ((yes&1) << 7) | (0x03); }
static void gp2x_940t_pause(int yes)     { gp2x_dualcore_pause(yes); }


/* Function: gp2x_dualcore_sync
   This function halts the 920T code until the 940T has finished all its tasks.

   Note:
   - Call this function only from your 920T program.

   See also:
   <gp2x_dualcore_pause>, <gp2x_dualcore_exec>, <gp2x_dualcore_data(address)> */

void gp2x_dualcore_sync(void)
{
  gp2x_queue *q=(gp2x_queue *)gp2x_1stcore_data_ptr(GP2X_QUEUE_ARRAY_PTR);
  while(q->items);
}

/* Function: gp2x_dualcore_exec
   This function executes a 940T command.

   Note:
   - Call this function only from your 920T program.

   See also:
   <gp2x_dualcore_pause>, <gp2x_dualcore_sync>, <gp2x_dualcore_data(address)> */

void gp2x_dualcore_exec(unsigned long command) { gp2x_enqueue((gp2x_queue *)gp2x_1stcore_data_ptr(GP2X_QUEUE_ARRAY_PTR),command); }


/* Function: gp2x_dualcore_launch_program
   This function sets the 940T program, and launchs it.

   Note:
   - Call this function only from your 920T program.

   Parameters:
   *area - pointer to the 940T raw binary.
   size (1..) - size of 940T raw binary, in bytes.

   See also:
   <gp2x_dualcore_launch_program_from_disk>, <gp2x_dualcore_launch_subprogram(name)> */

void gp2x_dualcore_launch_program(unsigned long *area, unsigned long size)
{
  unsigned long i=0, *arm940t_ram=(unsigned long *)gp2x_dualcore_ram;
  
  gp2x_940t_reset(1);

  gp2x_memregs[0x3B40>>1] = 0;                               //disable interrupts
  gp2x_memregs[0x3B42>>1] = 0;
  gp2x_memregs[0x3B44>>1] = 0xffff;
  gp2x_memregs[0x3B46>>1] = 0xffff;

  gp2x_940t_pause(0);            
                             
  while(i < size) *arm940t_ram++=area[i++];

  gp2x_initqueue((gp2x_queue *)gp2x_1stcore_data_ptr(GP2X_QUEUE_ARRAY_PTR), GP2X_QUEUE_MAX_ITEMS, (unsigned long *)gp2x_1stcore_data_ptr(GP2X_QUEUE_DATA_PTR), (unsigned long *)gp2x_2ndcore_data_ptr(GP2X_QUEUE_DATA_PTR));

  gp2x_940t_reset(0);
}

/* Function: gp2x_dualcore_launch_program_from_disk
   This function sets the 940T program, and launchs it.

   Note:
   - Call this function only from your 920T program.

   Parameters:
   *file - string to the file which contains the 940T raw binary.
   offset (0..) - amount of bytes to skip at the beginning of the file.
   size (1..) - size of 940T raw binary, in bytes.

   See also:
   <gp2x_dualcore_launch_program>, <gp2x_dualcore_launch_subprogram(name)> */

void gp2x_dualcore_launch_program_from_disk(const char *file, unsigned long offset, unsigned long size)
{
 FILE *in; void *data;

 if((in=fopen(file, "rb"))==NULL) return;
 if((data=malloc(size))==NULL) { fclose(in); return; }
 fseek(in, 0L, offset);
 fread(data, 1, size, in);
 gp2x_dualcore_launch_program((unsigned long *)data, size);
 free(data);
 fclose(in);
}

/* macro: gp2x_dualcore_declare_subprogram(name)
   To be written                              */

/* macro: gp2x_dualcore_launch_subprogram(name)
   To be written                              */

/*
#define gp2x_dualcore_declare_subprogram(name) extern void gp2x_dualcore_launch_## name ##_subprogram(void);
#define gp2x_dualcore_launch_subprogram(name)  gp2x_dualcore_launch_## name ##_subprogram()
*/





/*
   ,--------------------.
   |                    |X
   |    GP2X - FONT     |X
   |                    |X
   `--------------------'X
    XXXXXXXXXXXXXXXXXXXXXX 
*/



/* The font is generated from Xorg 6x10-L1.bdf */
static unsigned char gp2x_fontf[256][10] = {
{ 0x00>>2, 0xA8>>2, 0x00>>2, 0x88>>2, 0x00>>2, 0x88>>2, 0x00>>2, 0xA8>>2, 0x00>>2, 0x00>>2, },
{ 0x00>>2, 0x00>>2, 0x20>>2, 0x70>>2, 0xF8>>2, 0x70>>2, 0x20>>2, 0x00>>2, 0x00>>2, 0x00>>2, },
{ 0xA8>>2, 0x54>>2, 0xA8>>2, 0x54>>2, 0xA8>>2, 0x54>>2, 0xA8>>2, 0x54>>2, 0xA8>>2, 0x54>>2, },
{ 0x00>>2, 0x90>>2, 0x90>>2, 0xF0>>2, 0x90>>2, 0x90>>2, 0x78>>2, 0x10>>2, 0x10>>2, 0x10>>2, },
{ 0x00>>2, 0xE0>>2, 0x80>>2, 0xC0>>2, 0x80>>2, 0xB8>>2, 0x20>>2, 0x30>>2, 0x20>>2, 0x20>>2, },
{ 0x00>>2, 0x70>>2, 0x80>>2, 0x80>>2, 0x70>>2, 0x70>>2, 0x48>>2, 0x70>>2, 0x48>>2, 0x48>>2, },
{ 0x00>>2, 0x80>>2, 0x80>>2, 0x80>>2, 0xF0>>2, 0x78>>2, 0x40>>2, 0x70>>2, 0x40>>2, 0x40>>2, },
{ 0x00>>2, 0x20>>2, 0x50>>2, 0x20>>2, 0x00>>2, 0x00>>2, 0x00>>2, 0x00>>2, 0x00>>2, 0x00>>2, },
{ 0x00>>2, 0x00>>2, 0x20>>2, 0x20>>2, 0xF8>>2, 0x20>>2, 0x20>>2, 0xF8>>2, 0x00>>2, 0x00>>2, },
{ 0x00>>2, 0x90>>2, 0xD0>>2, 0xD0>>2, 0xB0>>2, 0x90>>2, 0x40>>2, 0x40>>2, 0x40>>2, 0x78>>2, },
{ 0x00>>2, 0x90>>2, 0x90>>2, 0x60>>2, 0x40>>2, 0x78>>2, 0x10>>2, 0x10>>2, 0x10>>2, 0x10>>2, },
{ 0x20>>2, 0x20>>2, 0x20>>2, 0x20>>2, 0x20>>2, 0xE0>>2, 0x00>>2, 0x00>>2, 0x00>>2, 0x00>>2, },
{ 0x00>>2, 0x00>>2, 0x00>>2, 0x00>>2, 0x00>>2, 0xE0>>2, 0x20>>2, 0x20>>2, 0x20>>2, 0x20>>2, },
{ 0x00>>2, 0x00>>2, 0x00>>2, 0x00>>2, 0x00>>2, 0x3C>>2, 0x20>>2, 0x20>>2, 0x20>>2, 0x20>>2, },
{ 0x20>>2, 0x20>>2, 0x20>>2, 0x20>>2, 0x20>>2, 0x3C>>2, 0x00>>2, 0x00>>2, 0x00>>2, 0x00>>2, },
{ 0x20>>2, 0x20>>2, 0x20>>2, 0x20>>2, 0x20>>2, 0xFC>>2, 0x20>>2, 0x20>>2, 0x20>>2, 0x20>>2, },
{ 0xFC>>2, 0x00>>2, 0x00>>2, 0x00>>2, 0x00>>2, 0x00>>2, 0x00>>2, 0x00>>2, 0x00>>2, 0x00>>2, },
{ 0x00>>2, 0x00>>2, 0xFC>>2, 0x00>>2, 0x00>>2, 0x00>>2, 0x00>>2, 0x00>>2, 0x00>>2, 0x00>>2, },
{ 0x00>>2, 0x00>>2, 0x00>>2, 0x00>>2, 0x00>>2, 0xFF>>2, 0x00>>2, 0x00>>2, 0x00>>2, 0x00>>2, },
{ 0x00>>2, 0x00>>2, 0x00>>2, 0x00>>2, 0x00>>2, 0x00>>2, 0x00>>2, 0xFC>>2, 0x00>>2, 0x00>>2, },
{ 0x00>>2, 0x00>>2, 0x00>>2, 0x00>>2, 0x00>>2, 0x00>>2, 0x00>>2, 0x00>>2, 0x00>>2, 0xFC>>2, },
{ 0x20>>2, 0x20>>2, 0x20>>2, 0x20>>2, 0x20>>2, 0x3C>>2, 0x20>>2, 0x20>>2, 0x20>>2, 0x20>>2, },
{ 0x20>>2, 0x20>>2, 0x20>>2, 0x20>>2, 0x20>>2, 0xE0>>2, 0x20>>2, 0x20>>2, 0x20>>2, 0x20>>2, },
{ 0x20>>2, 0x20>>2, 0x20>>2, 0x20>>2, 0x20>>2, 0xFC>>2, 0x00>>2, 0x00>>2, 0x00>>2, 0x00>>2, },
{ 0x00>>2, 0x00>>2, 0x00>>2, 0x00>>2, 0x00>>2, 0xFC>>2, 0x20>>2, 0x20>>2, 0x20>>2, 0x20>>2, },
{ 0x20>>2, 0x20>>2, 0x20>>2, 0x20>>2, 0x20>>2, 0x20>>2, 0x20>>2, 0x20>>2, 0x20>>2, 0x20>>2, },
{ 0x00>>2, 0x18>>2, 0x60>>2, 0x80>>2, 0x60>>2, 0x18>>2, 0x00>>2, 0xF8>>2, 0x00>>2, 0x00>>2, },
{ 0x00>>2, 0xC0>>2, 0x30>>2, 0x08>>2, 0x30>>2, 0xC0>>2, 0x00>>2, 0xF8>>2, 0x00>>2, 0x00>>2, },
{ 0x00>>2, 0x00>>2, 0x00>>2, 0xF8>>2, 0x50>>2, 0x50>>2, 0x50>>2, 0x50>>2, 0x00>>2, 0x00>>2, },
{ 0x00>>2, 0x08>>2, 0x10>>2, 0xF8>>2, 0x20>>2, 0xF8>>2, 0x40>>2, 0x80>>2, 0x00>>2, 0x00>>2, },
{ 0x00>>2, 0x30>>2, 0x48>>2, 0x40>>2, 0xE0>>2, 0x40>>2, 0x48>>2, 0xB0>>2, 0x00>>2, 0x00>>2, },
{ 0x00>>2, 0x00>>2, 0x00>>2, 0x00>>2, 0x20>>2, 0x00>>2, 0x00>>2, 0x00>>2, 0x00>>2, 0x00>>2, },
{ 0x00>>2, 0x00>>2, 0x00>>2, 0x00>>2, 0x00>>2, 0x00>>2, 0x00>>2, 0x00>>2, 0x00>>2, 0x00>>2, },
{ 0x00>>2, 0x20>>2, 0x20>>2, 0x20>>2, 0x20>>2, 0x20>>2, 0x00>>2, 0x20>>2, 0x00>>2, 0x00>>2, },
{ 0x00>>2, 0x50>>2, 0x50>>2, 0x50>>2, 0x00>>2, 0x00>>2, 0x00>>2, 0x00>>2, 0x00>>2, 0x00>>2, },
{ 0x00>>2, 0x50>>2, 0x50>>2, 0xF8>>2, 0x50>>2, 0xF8>>2, 0x50>>2, 0x50>>2, 0x00>>2, 0x00>>2, },
{ 0x00>>2, 0x20>>2, 0x70>>2, 0xA0>>2, 0x70>>2, 0x28>>2, 0x70>>2, 0x20>>2, 0x00>>2, 0x00>>2, },
{ 0x00>>2, 0x48>>2, 0xA8>>2, 0x50>>2, 0x20>>2, 0x50>>2, 0xA8>>2, 0x90>>2, 0x00>>2, 0x00>>2, },
{ 0x00>>2, 0x40>>2, 0xA0>>2, 0xA0>>2, 0x40>>2, 0xA8>>2, 0x90>>2, 0x68>>2, 0x00>>2, 0x00>>2, },
{ 0x00>>2, 0x20>>2, 0x20>>2, 0x20>>2, 0x00>>2, 0x00>>2, 0x00>>2, 0x00>>2, 0x00>>2, 0x00>>2, },
{ 0x00>>2, 0x10>>2, 0x20>>2, 0x40>>2, 0x40>>2, 0x40>>2, 0x20>>2, 0x10>>2, 0x00>>2, 0x00>>2, },
{ 0x00>>2, 0x40>>2, 0x20>>2, 0x10>>2, 0x10>>2, 0x10>>2, 0x20>>2, 0x40>>2, 0x00>>2, 0x00>>2, },
{ 0x00>>2, 0x00>>2, 0x88>>2, 0x50>>2, 0xF8>>2, 0x50>>2, 0x88>>2, 0x00>>2, 0x00>>2, 0x00>>2, },
{ 0x00>>2, 0x00>>2, 0x20>>2, 0x20>>2, 0xF8>>2, 0x20>>2, 0x20>>2, 0x00>>2, 0x00>>2, 0x00>>2, },
{ 0x00>>2, 0x00>>2, 0x00>>2, 0x00>>2, 0x00>>2, 0x00>>2, 0x30>>2, 0x20>>2, 0x40>>2, 0x00>>2, },
{ 0x00>>2, 0x00>>2, 0x00>>2, 0x00>>2, 0xF8>>2, 0x00>>2, 0x00>>2, 0x00>>2, 0x00>>2, 0x00>>2, },
{ 0x00>>2, 0x00>>2, 0x00>>2, 0x00>>2, 0x00>>2, 0x00>>2, 0x20>>2, 0x70>>2, 0x20>>2, 0x00>>2, },
{ 0x00>>2, 0x08>>2, 0x08>>2, 0x10>>2, 0x20>>2, 0x40>>2, 0x80>>2, 0x80>>2, 0x00>>2, 0x00>>2, },
{ 0x00>>2, 0x20>>2, 0x50>>2, 0x88>>2, 0x88>>2, 0x88>>2, 0x50>>2, 0x20>>2, 0x00>>2, 0x00>>2, },
{ 0x00>>2, 0x20>>2, 0x60>>2, 0xA0>>2, 0x20>>2, 0x20>>2, 0x20>>2, 0xF8>>2, 0x00>>2, 0x00>>2, },
{ 0x00>>2, 0x70>>2, 0x88>>2, 0x08>>2, 0x30>>2, 0x40>>2, 0x80>>2, 0xF8>>2, 0x00>>2, 0x00>>2, },
{ 0x00>>2, 0xF8>>2, 0x08>>2, 0x10>>2, 0x30>>2, 0x08>>2, 0x88>>2, 0x70>>2, 0x00>>2, 0x00>>2, },
{ 0x00>>2, 0x10>>2, 0x30>>2, 0x50>>2, 0x90>>2, 0xF8>>2, 0x10>>2, 0x10>>2, 0x00>>2, 0x00>>2, },
{ 0x00>>2, 0xF8>>2, 0x80>>2, 0xB0>>2, 0xC8>>2, 0x08>>2, 0x88>>2, 0x70>>2, 0x00>>2, 0x00>>2, },
{ 0x00>>2, 0x30>>2, 0x40>>2, 0x80>>2, 0xB0>>2, 0xC8>>2, 0x88>>2, 0x70>>2, 0x00>>2, 0x00>>2, },
{ 0x00>>2, 0xF8>>2, 0x08>>2, 0x10>>2, 0x10>>2, 0x20>>2, 0x40>>2, 0x40>>2, 0x00>>2, 0x00>>2, },
{ 0x00>>2, 0x70>>2, 0x88>>2, 0x88>>2, 0x70>>2, 0x88>>2, 0x88>>2, 0x70>>2, 0x00>>2, 0x00>>2, },
{ 0x00>>2, 0x70>>2, 0x88>>2, 0x98>>2, 0x68>>2, 0x08>>2, 0x10>>2, 0x60>>2, 0x00>>2, 0x00>>2, },
{ 0x00>>2, 0x00>>2, 0x20>>2, 0x70>>2, 0x20>>2, 0x00>>2, 0x20>>2, 0x70>>2, 0x20>>2, 0x00>>2, },
{ 0x00>>2, 0x00>>2, 0x20>>2, 0x70>>2, 0x20>>2, 0x00>>2, 0x30>>2, 0x20>>2, 0x40>>2, 0x00>>2, },
{ 0x00>>2, 0x08>>2, 0x10>>2, 0x20>>2, 0x40>>2, 0x20>>2, 0x10>>2, 0x08>>2, 0x00>>2, 0x00>>2, },
{ 0x00>>2, 0x00>>2, 0x00>>2, 0xF8>>2, 0x00>>2, 0xF8>>2, 0x00>>2, 0x00>>2, 0x00>>2, 0x00>>2, },
{ 0x00>>2, 0x40>>2, 0x20>>2, 0x10>>2, 0x08>>2, 0x10>>2, 0x20>>2, 0x40>>2, 0x00>>2, 0x00>>2, },
{ 0x00>>2, 0x70>>2, 0x88>>2, 0x10>>2, 0x20>>2, 0x20>>2, 0x00>>2, 0x20>>2, 0x00>>2, 0x00>>2, },
{ 0x00>>2, 0x70>>2, 0x88>>2, 0x98>>2, 0xA8>>2, 0xB0>>2, 0x80>>2, 0x70>>2, 0x00>>2, 0x00>>2, },
{ 0x00>>2, 0x20>>2, 0x50>>2, 0x88>>2, 0x88>>2, 0xF8>>2, 0x88>>2, 0x88>>2, 0x00>>2, 0x00>>2, },
{ 0x00>>2, 0xF0>>2, 0x48>>2, 0x48>>2, 0x70>>2, 0x48>>2, 0x48>>2, 0xF0>>2, 0x00>>2, 0x00>>2, },
{ 0x00>>2, 0x70>>2, 0x88>>2, 0x80>>2, 0x80>>2, 0x80>>2, 0x88>>2, 0x70>>2, 0x00>>2, 0x00>>2, },
{ 0x00>>2, 0xF0>>2, 0x48>>2, 0x48>>2, 0x48>>2, 0x48>>2, 0x48>>2, 0xF0>>2, 0x00>>2, 0x00>>2, },
{ 0x00>>2, 0xF8>>2, 0x80>>2, 0x80>>2, 0xF0>>2, 0x80>>2, 0x80>>2, 0xF8>>2, 0x00>>2, 0x00>>2, },
{ 0x00>>2, 0xF8>>2, 0x80>>2, 0x80>>2, 0xF0>>2, 0x80>>2, 0x80>>2, 0x80>>2, 0x00>>2, 0x00>>2, },
{ 0x00>>2, 0x70>>2, 0x88>>2, 0x80>>2, 0x80>>2, 0x98>>2, 0x88>>2, 0x70>>2, 0x00>>2, 0x00>>2, },
{ 0x00>>2, 0x88>>2, 0x88>>2, 0x88>>2, 0xF8>>2, 0x88>>2, 0x88>>2, 0x88>>2, 0x00>>2, 0x00>>2, },
{ 0x00>>2, 0x70>>2, 0x20>>2, 0x20>>2, 0x20>>2, 0x20>>2, 0x20>>2, 0x70>>2, 0x00>>2, 0x00>>2, },
{ 0x00>>2, 0x38>>2, 0x10>>2, 0x10>>2, 0x10>>2, 0x10>>2, 0x90>>2, 0x60>>2, 0x00>>2, 0x00>>2, },
{ 0x00>>2, 0x88>>2, 0x90>>2, 0xA0>>2, 0xC0>>2, 0xA0>>2, 0x90>>2, 0x88>>2, 0x00>>2, 0x00>>2, },
{ 0x00>>2, 0x80>>2, 0x80>>2, 0x80>>2, 0x80>>2, 0x80>>2, 0x80>>2, 0xF8>>2, 0x00>>2, 0x00>>2, },
{ 0x00>>2, 0x88>>2, 0x88>>2, 0xD8>>2, 0xA8>>2, 0x88>>2, 0x88>>2, 0x88>>2, 0x00>>2, 0x00>>2, },
{ 0x00>>2, 0x88>>2, 0x88>>2, 0xC8>>2, 0xA8>>2, 0x98>>2, 0x88>>2, 0x88>>2, 0x00>>2, 0x00>>2, },
{ 0x00>>2, 0x70>>2, 0x88>>2, 0x88>>2, 0x88>>2, 0x88>>2, 0x88>>2, 0x70>>2, 0x00>>2, 0x00>>2, },
{ 0x00>>2, 0xF0>>2, 0x88>>2, 0x88>>2, 0xF0>>2, 0x80>>2, 0x80>>2, 0x80>>2, 0x00>>2, 0x00>>2, },
{ 0x00>>2, 0x70>>2, 0x88>>2, 0x88>>2, 0x88>>2, 0x88>>2, 0xA8>>2, 0x70>>2, 0x08>>2, 0x00>>2, },
{ 0x00>>2, 0xF0>>2, 0x88>>2, 0x88>>2, 0xF0>>2, 0xA0>>2, 0x90>>2, 0x88>>2, 0x00>>2, 0x00>>2, },
{ 0x00>>2, 0x70>>2, 0x88>>2, 0x80>>2, 0x70>>2, 0x08>>2, 0x88>>2, 0x70>>2, 0x00>>2, 0x00>>2, },
{ 0x00>>2, 0xF8>>2, 0x20>>2, 0x20>>2, 0x20>>2, 0x20>>2, 0x20>>2, 0x20>>2, 0x00>>2, 0x00>>2, },
{ 0x00>>2, 0x88>>2, 0x88>>2, 0x88>>2, 0x88>>2, 0x88>>2, 0x88>>2, 0x70>>2, 0x00>>2, 0x00>>2, },
{ 0x00>>2, 0x88>>2, 0x88>>2, 0x88>>2, 0x50>>2, 0x50>>2, 0x50>>2, 0x20>>2, 0x00>>2, 0x00>>2, },
{ 0x00>>2, 0x88>>2, 0x88>>2, 0x88>>2, 0xA8>>2, 0xA8>>2, 0xD8>>2, 0x88>>2, 0x00>>2, 0x00>>2, },
{ 0x00>>2, 0x88>>2, 0x88>>2, 0x50>>2, 0x20>>2, 0x50>>2, 0x88>>2, 0x88>>2, 0x00>>2, 0x00>>2, },
{ 0x00>>2, 0x88>>2, 0x88>>2, 0x50>>2, 0x20>>2, 0x20>>2, 0x20>>2, 0x20>>2, 0x00>>2, 0x00>>2, },
{ 0x00>>2, 0xF8>>2, 0x08>>2, 0x10>>2, 0x20>>2, 0x40>>2, 0x80>>2, 0xF8>>2, 0x00>>2, 0x00>>2, },
{ 0x00>>2, 0x70>>2, 0x40>>2, 0x40>>2, 0x40>>2, 0x40>>2, 0x40>>2, 0x70>>2, 0x00>>2, 0x00>>2, },
{ 0x00>>2, 0x80>>2, 0x80>>2, 0x40>>2, 0x20>>2, 0x10>>2, 0x08>>2, 0x08>>2, 0x00>>2, 0x00>>2, },
{ 0x00>>2, 0x70>>2, 0x10>>2, 0x10>>2, 0x10>>2, 0x10>>2, 0x10>>2, 0x70>>2, 0x00>>2, 0x00>>2, },
{ 0x00>>2, 0x20>>2, 0x50>>2, 0x88>>2, 0x00>>2, 0x00>>2, 0x00>>2, 0x00>>2, 0x00>>2, 0x00>>2, },
{ 0x00>>2, 0x00>>2, 0x00>>2, 0x00>>2, 0x00>>2, 0x00>>2, 0x00>>2, 0x00>>2, 0xF8>>2, 0x00>>2, },
{ 0x20>>2, 0x10>>2, 0x00>>2, 0x00>>2, 0x00>>2, 0x00>>2, 0x00>>2, 0x00>>2, 0x00>>2, 0x00>>2, },
{ 0x00>>2, 0x00>>2, 0x00>>2, 0x70>>2, 0x08>>2, 0x78>>2, 0x88>>2, 0x78>>2, 0x00>>2, 0x00>>2, },
{ 0x00>>2, 0x80>>2, 0x80>>2, 0xB0>>2, 0xC8>>2, 0x88>>2, 0xC8>>2, 0xB0>>2, 0x00>>2, 0x00>>2, },
{ 0x00>>2, 0x00>>2, 0x00>>2, 0x70>>2, 0x88>>2, 0x80>>2, 0x88>>2, 0x70>>2, 0x00>>2, 0x00>>2, },
{ 0x00>>2, 0x08>>2, 0x08>>2, 0x68>>2, 0x98>>2, 0x88>>2, 0x98>>2, 0x68>>2, 0x00>>2, 0x00>>2, },
{ 0x00>>2, 0x00>>2, 0x00>>2, 0x70>>2, 0x88>>2, 0xF8>>2, 0x80>>2, 0x70>>2, 0x00>>2, 0x00>>2, },
{ 0x00>>2, 0x30>>2, 0x48>>2, 0x40>>2, 0xF0>>2, 0x40>>2, 0x40>>2, 0x40>>2, 0x00>>2, 0x00>>2, },
{ 0x00>>2, 0x00>>2, 0x00>>2, 0x78>>2, 0x88>>2, 0x88>>2, 0x78>>2, 0x08>>2, 0x88>>2, 0x70>>2, },
{ 0x00>>2, 0x80>>2, 0x80>>2, 0xB0>>2, 0xC8>>2, 0x88>>2, 0x88>>2, 0x88>>2, 0x00>>2, 0x00>>2, },
{ 0x00>>2, 0x20>>2, 0x00>>2, 0x60>>2, 0x20>>2, 0x20>>2, 0x20>>2, 0x70>>2, 0x00>>2, 0x00>>2, },
{ 0x00>>2, 0x08>>2, 0x00>>2, 0x18>>2, 0x08>>2, 0x08>>2, 0x08>>2, 0x48>>2, 0x48>>2, 0x30>>2, },
{ 0x00>>2, 0x80>>2, 0x80>>2, 0x88>>2, 0x90>>2, 0xE0>>2, 0x90>>2, 0x88>>2, 0x00>>2, 0x00>>2, },
{ 0x00>>2, 0x60>>2, 0x20>>2, 0x20>>2, 0x20>>2, 0x20>>2, 0x20>>2, 0x70>>2, 0x00>>2, 0x00>>2, },
{ 0x00>>2, 0x00>>2, 0x00>>2, 0xD0>>2, 0xA8>>2, 0xA8>>2, 0xA8>>2, 0x88>>2, 0x00>>2, 0x00>>2, },
{ 0x00>>2, 0x00>>2, 0x00>>2, 0xB0>>2, 0xC8>>2, 0x88>>2, 0x88>>2, 0x88>>2, 0x00>>2, 0x00>>2, },
{ 0x00>>2, 0x00>>2, 0x00>>2, 0x70>>2, 0x88>>2, 0x88>>2, 0x88>>2, 0x70>>2, 0x00>>2, 0x00>>2, },
{ 0x00>>2, 0x00>>2, 0x00>>2, 0xB0>>2, 0xC8>>2, 0x88>>2, 0xC8>>2, 0xB0>>2, 0x80>>2, 0x80>>2, },
{ 0x00>>2, 0x00>>2, 0x00>>2, 0x68>>2, 0x98>>2, 0x88>>2, 0x98>>2, 0x68>>2, 0x08>>2, 0x08>>2, },
{ 0x00>>2, 0x00>>2, 0x00>>2, 0xB0>>2, 0xC8>>2, 0x80>>2, 0x80>>2, 0x80>>2, 0x00>>2, 0x00>>2, },
{ 0x00>>2, 0x00>>2, 0x00>>2, 0x70>>2, 0x80>>2, 0x70>>2, 0x08>>2, 0xF0>>2, 0x00>>2, 0x00>>2, },
{ 0x00>>2, 0x40>>2, 0x40>>2, 0xF0>>2, 0x40>>2, 0x40>>2, 0x48>>2, 0x30>>2, 0x00>>2, 0x00>>2, },
{ 0x00>>2, 0x00>>2, 0x00>>2, 0x88>>2, 0x88>>2, 0x88>>2, 0x98>>2, 0x68>>2, 0x00>>2, 0x00>>2, },
{ 0x00>>2, 0x00>>2, 0x00>>2, 0x88>>2, 0x88>>2, 0x50>>2, 0x50>>2, 0x20>>2, 0x00>>2, 0x00>>2, },
{ 0x00>>2, 0x00>>2, 0x00>>2, 0x88>>2, 0x88>>2, 0xA8>>2, 0xA8>>2, 0x50>>2, 0x00>>2, 0x00>>2, },
{ 0x00>>2, 0x00>>2, 0x00>>2, 0x88>>2, 0x50>>2, 0x20>>2, 0x50>>2, 0x88>>2, 0x00>>2, 0x00>>2, },
{ 0x00>>2, 0x00>>2, 0x00>>2, 0x88>>2, 0x88>>2, 0x98>>2, 0x68>>2, 0x08>>2, 0x88>>2, 0x70>>2, },
{ 0x00>>2, 0x00>>2, 0x00>>2, 0xF8>>2, 0x10>>2, 0x20>>2, 0x40>>2, 0xF8>>2, 0x00>>2, 0x00>>2, },
{ 0x00>>2, 0x18>>2, 0x20>>2, 0x10>>2, 0x60>>2, 0x10>>2, 0x20>>2, 0x18>>2, 0x00>>2, 0x00>>2, },
{ 0x00>>2, 0x20>>2, 0x20>>2, 0x20>>2, 0x20>>2, 0x20>>2, 0x20>>2, 0x20>>2, 0x00>>2, 0x00>>2, },
{ 0x00>>2, 0x60>>2, 0x10>>2, 0x20>>2, 0x18>>2, 0x20>>2, 0x10>>2, 0x60>>2, 0x00>>2, 0x00>>2, },
{ 0x00>>2, 0x48>>2, 0xA8>>2, 0x90>>2, 0x00>>2, 0x00>>2, 0x00>>2, 0x00>>2, 0x00>>2, 0x00>>2, },
{ 0x00>>2, 0x00>>2, 0x00>>2, 0x00>>2, 0x00>>2, 0x00>>2, 0x00>>2, 0x00>>2, 0x00>>2, 0x00>>2, },
{ 0x00>>2, 0x00>>2, 0x00>>2, 0x00>>2, 0x00>>2, 0x00>>2, 0x00>>2, 0x00>>2, 0x00>>2, 0x00>>2, },
{ 0x00>>2, 0x00>>2, 0x00>>2, 0x00>>2, 0x00>>2, 0x00>>2, 0x00>>2, 0x00>>2, 0x00>>2, 0x00>>2, },
{ 0x00>>2, 0x00>>2, 0x00>>2, 0x00>>2, 0x00>>2, 0x00>>2, 0x00>>2, 0x00>>2, 0x00>>2, 0x00>>2, },
{ 0x00>>2, 0x00>>2, 0x00>>2, 0x00>>2, 0x00>>2, 0x00>>2, 0x00>>2, 0x00>>2, 0x00>>2, 0x00>>2, },
{ 0x00>>2, 0x00>>2, 0x00>>2, 0x00>>2, 0x00>>2, 0x00>>2, 0x00>>2, 0x00>>2, 0x00>>2, 0x00>>2, },
{ 0x00>>2, 0x00>>2, 0x00>>2, 0x00>>2, 0x00>>2, 0x00>>2, 0x00>>2, 0x00>>2, 0x00>>2, 0x00>>2, },
{ 0x00>>2, 0x00>>2, 0x00>>2, 0x00>>2, 0x00>>2, 0x00>>2, 0x00>>2, 0x00>>2, 0x00>>2, 0x00>>2, },
{ 0x00>>2, 0x00>>2, 0x00>>2, 0x00>>2, 0x00>>2, 0x00>>2, 0x00>>2, 0x00>>2, 0x00>>2, 0x00>>2, },
{ 0x00>>2, 0x00>>2, 0x00>>2, 0x00>>2, 0x00>>2, 0x00>>2, 0x00>>2, 0x00>>2, 0x00>>2, 0x00>>2, },
{ 0x00>>2, 0x00>>2, 0x00>>2, 0x00>>2, 0x00>>2, 0x00>>2, 0x00>>2, 0x00>>2, 0x00>>2, 0x00>>2, },
{ 0x00>>2, 0x00>>2, 0x00>>2, 0x00>>2, 0x00>>2, 0x00>>2, 0x00>>2, 0x00>>2, 0x00>>2, 0x00>>2, },
{ 0x00>>2, 0x00>>2, 0x00>>2, 0x00>>2, 0x00>>2, 0x00>>2, 0x00>>2, 0x00>>2, 0x00>>2, 0x00>>2, },
{ 0x00>>2, 0x00>>2, 0x00>>2, 0x00>>2, 0x00>>2, 0x00>>2, 0x00>>2, 0x00>>2, 0x00>>2, 0x00>>2, },
{ 0x00>>2, 0x00>>2, 0x00>>2, 0x00>>2, 0x00>>2, 0x00>>2, 0x00>>2, 0x00>>2, 0x00>>2, 0x00>>2, },
{ 0x00>>2, 0x00>>2, 0x00>>2, 0x00>>2, 0x00>>2, 0x00>>2, 0x00>>2, 0x00>>2, 0x00>>2, 0x00>>2, },
{ 0x00>>2, 0x00>>2, 0x00>>2, 0x00>>2, 0x00>>2, 0x00>>2, 0x00>>2, 0x00>>2, 0x00>>2, 0x00>>2, },
{ 0x00>>2, 0x00>>2, 0x00>>2, 0x00>>2, 0x00>>2, 0x00>>2, 0x00>>2, 0x00>>2, 0x00>>2, 0x00>>2, },
{ 0x00>>2, 0x00>>2, 0x00>>2, 0x00>>2, 0x00>>2, 0x00>>2, 0x00>>2, 0x00>>2, 0x00>>2, 0x00>>2, },
{ 0x00>>2, 0x00>>2, 0x00>>2, 0x00>>2, 0x00>>2, 0x00>>2, 0x00>>2, 0x00>>2, 0x00>>2, 0x00>>2, },
{ 0x00>>2, 0x00>>2, 0x00>>2, 0x00>>2, 0x00>>2, 0x00>>2, 0x00>>2, 0x00>>2, 0x00>>2, 0x00>>2, },
{ 0x00>>2, 0x00>>2, 0x00>>2, 0x00>>2, 0x00>>2, 0x00>>2, 0x00>>2, 0x00>>2, 0x00>>2, 0x00>>2, },
{ 0x00>>2, 0x00>>2, 0x00>>2, 0x00>>2, 0x00>>2, 0x00>>2, 0x00>>2, 0x00>>2, 0x00>>2, 0x00>>2, },
{ 0x00>>2, 0x00>>2, 0x00>>2, 0x00>>2, 0x00>>2, 0x00>>2, 0x00>>2, 0x00>>2, 0x00>>2, 0x00>>2, },
{ 0x00>>2, 0x00>>2, 0x00>>2, 0x00>>2, 0x00>>2, 0x00>>2, 0x00>>2, 0x00>>2, 0x00>>2, 0x00>>2, },
{ 0x00>>2, 0x00>>2, 0x00>>2, 0x00>>2, 0x00>>2, 0x00>>2, 0x00>>2, 0x00>>2, 0x00>>2, 0x00>>2, },
{ 0x00>>2, 0x00>>2, 0x00>>2, 0x00>>2, 0x00>>2, 0x00>>2, 0x00>>2, 0x00>>2, 0x00>>2, 0x00>>2, },
{ 0x00>>2, 0x00>>2, 0x00>>2, 0x00>>2, 0x00>>2, 0x00>>2, 0x00>>2, 0x00>>2, 0x00>>2, 0x00>>2, },
{ 0x00>>2, 0x00>>2, 0x00>>2, 0x00>>2, 0x00>>2, 0x00>>2, 0x00>>2, 0x00>>2, 0x00>>2, 0x00>>2, },
{ 0x00>>2, 0x00>>2, 0x00>>2, 0x00>>2, 0x00>>2, 0x00>>2, 0x00>>2, 0x00>>2, 0x00>>2, 0x00>>2, },
{ 0x00>>2, 0x00>>2, 0x00>>2, 0x00>>2, 0x00>>2, 0x00>>2, 0x00>>2, 0x00>>2, 0x00>>2, 0x00>>2, },
{ 0x00>>2, 0x00>>2, 0x00>>2, 0x00>>2, 0x00>>2, 0x00>>2, 0x00>>2, 0x00>>2, 0x00>>2, 0x00>>2, },
{ 0x00>>2, 0x00>>2, 0x00>>2, 0x00>>2, 0x00>>2, 0x00>>2, 0x00>>2, 0x00>>2, 0x00>>2, 0x00>>2, },
{ 0x00>>2, 0x00>>2, 0x00>>2, 0x00>>2, 0x00>>2, 0x00>>2, 0x00>>2, 0x00>>2, 0x00>>2, 0x00>>2, },
{ 0x00>>2, 0x20>>2, 0x00>>2, 0x20>>2, 0x20>>2, 0x20>>2, 0x20>>2, 0x20>>2, 0x00>>2, 0x00>>2, },
{ 0x00>>2, 0x00>>2, 0x20>>2, 0x78>>2, 0xA0>>2, 0xA0>>2, 0xA0>>2, 0x78>>2, 0x20>>2, 0x00>>2, },
{ 0x00>>2, 0x30>>2, 0x48>>2, 0x40>>2, 0xE0>>2, 0x40>>2, 0x48>>2, 0xB0>>2, 0x00>>2, 0x00>>2, },
{ 0x00>>2, 0x00>>2, 0x00>>2, 0x88>>2, 0x70>>2, 0x50>>2, 0x70>>2, 0x88>>2, 0x00>>2, 0x00>>2, },
{ 0x00>>2, 0x88>>2, 0x88>>2, 0x50>>2, 0x20>>2, 0xF8>>2, 0x20>>2, 0x20>>2, 0x20>>2, 0x00>>2, },
{ 0x00>>2, 0x20>>2, 0x20>>2, 0x20>>2, 0x00>>2, 0x20>>2, 0x20>>2, 0x20>>2, 0x00>>2, 0x00>>2, },
{ 0x00>>2, 0x70>>2, 0x80>>2, 0xE0>>2, 0x90>>2, 0x48>>2, 0x38>>2, 0x08>>2, 0x70>>2, 0x00>>2, },
{ 0x50>>2, 0x00>>2, 0x00>>2, 0x00>>2, 0x00>>2, 0x00>>2, 0x00>>2, 0x00>>2, 0x00>>2, 0x00>>2, },
{ 0x00>>2, 0x70>>2, 0x88>>2, 0xA8>>2, 0xC8>>2, 0xA8>>2, 0x88>>2, 0x70>>2, 0x00>>2, 0x00>>2, },
{ 0x00>>2, 0x38>>2, 0x48>>2, 0x58>>2, 0x28>>2, 0x00>>2, 0x78>>2, 0x00>>2, 0x00>>2, 0x00>>2, },
{ 0x00>>2, 0x00>>2, 0x00>>2, 0x24>>2, 0x48>>2, 0x90>>2, 0x48>>2, 0x24>>2, 0x00>>2, 0x00>>2, },
{ 0x00>>2, 0x00>>2, 0x00>>2, 0x00>>2, 0x78>>2, 0x08>>2, 0x00>>2, 0x00>>2, 0x00>>2, 0x00>>2, },
{ 0x00>>2, 0x00>>2, 0x00>>2, 0x00>>2, 0x78>>2, 0x00>>2, 0x00>>2, 0x00>>2, 0x00>>2, 0x00>>2, },
{ 0x00>>2, 0x70>>2, 0x88>>2, 0xE8>>2, 0xC8>>2, 0xC8>>2, 0x88>>2, 0x70>>2, 0x00>>2, 0x00>>2, },
{ 0xF8>>2, 0x00>>2, 0x00>>2, 0x00>>2, 0x00>>2, 0x00>>2, 0x00>>2, 0x00>>2, 0x00>>2, 0x00>>2, },
{ 0x00>>2, 0x20>>2, 0x50>>2, 0x20>>2, 0x00>>2, 0x00>>2, 0x00>>2, 0x00>>2, 0x00>>2, 0x00>>2, },
{ 0x00>>2, 0x00>>2, 0x20>>2, 0x20>>2, 0xF8>>2, 0x20>>2, 0x20>>2, 0xF8>>2, 0x00>>2, 0x00>>2, },
{ 0x30>>2, 0x48>>2, 0x10>>2, 0x20>>2, 0x78>>2, 0x00>>2, 0x00>>2, 0x00>>2, 0x00>>2, 0x00>>2, },
{ 0x70>>2, 0x08>>2, 0x30>>2, 0x08>>2, 0x70>>2, 0x00>>2, 0x00>>2, 0x00>>2, 0x00>>2, 0x00>>2, },
{ 0x10>>2, 0x20>>2, 0x00>>2, 0x00>>2, 0x00>>2, 0x00>>2, 0x00>>2, 0x00>>2, 0x00>>2, 0x00>>2, },
{ 0x00>>2, 0x00>>2, 0x00>>2, 0x88>>2, 0x88>>2, 0x88>>2, 0xC8>>2, 0xB0>>2, 0x80>>2, 0x00>>2, },
{ 0x00>>2, 0x78>>2, 0xE8>>2, 0xE8>>2, 0x68>>2, 0x28>>2, 0x28>>2, 0x28>>2, 0x00>>2, 0x00>>2, },
{ 0x00>>2, 0x00>>2, 0x00>>2, 0x00>>2, 0x20>>2, 0x00>>2, 0x00>>2, 0x00>>2, 0x00>>2, 0x00>>2, },
{ 0x00>>2, 0x00>>2, 0x00>>2, 0x00>>2, 0x00>>2, 0x00>>2, 0x00>>2, 0x00>>2, 0x10>>2, 0x20>>2, },
{ 0x20>>2, 0x60>>2, 0x20>>2, 0x20>>2, 0x70>>2, 0x00>>2, 0x00>>2, 0x00>>2, 0x00>>2, 0x00>>2, },
{ 0x00>>2, 0x30>>2, 0x48>>2, 0x48>>2, 0x30>>2, 0x00>>2, 0x78>>2, 0x00>>2, 0x00>>2, 0x00>>2, },
{ 0x00>>2, 0x00>>2, 0x00>>2, 0x90>>2, 0x48>>2, 0x24>>2, 0x48>>2, 0x90>>2, 0x00>>2, 0x00>>2, },
{ 0x40>>2, 0xC0>>2, 0x40>>2, 0x40>>2, 0xE4>>2, 0x0C>>2, 0x14>>2, 0x3C>>2, 0x04>>2, 0x00>>2, },
{ 0x40>>2, 0xC0>>2, 0x40>>2, 0x40>>2, 0xE8>>2, 0x14>>2, 0x04>>2, 0x08>>2, 0x1C>>2, 0x00>>2, },
{ 0xC0>>2, 0x20>>2, 0x40>>2, 0x20>>2, 0xC8>>2, 0x18>>2, 0x28>>2, 0x78>>2, 0x08>>2, 0x00>>2, },
{ 0x00>>2, 0x20>>2, 0x00>>2, 0x20>>2, 0x20>>2, 0x40>>2, 0x88>>2, 0x70>>2, 0x00>>2, 0x00>>2, },
{ 0x40>>2, 0x20>>2, 0x70>>2, 0x88>>2, 0x88>>2, 0xF8>>2, 0x88>>2, 0x88>>2, 0x00>>2, 0x00>>2, },
{ 0x10>>2, 0x20>>2, 0x70>>2, 0x88>>2, 0x88>>2, 0xF8>>2, 0x88>>2, 0x88>>2, 0x00>>2, 0x00>>2, },
{ 0x20>>2, 0x50>>2, 0x70>>2, 0x88>>2, 0x88>>2, 0xF8>>2, 0x88>>2, 0x88>>2, 0x00>>2, 0x00>>2, },
{ 0x48>>2, 0xB0>>2, 0x70>>2, 0x88>>2, 0x88>>2, 0xF8>>2, 0x88>>2, 0x88>>2, 0x00>>2, 0x00>>2, },
{ 0x50>>2, 0x00>>2, 0x70>>2, 0x88>>2, 0x88>>2, 0xF8>>2, 0x88>>2, 0x88>>2, 0x00>>2, 0x00>>2, },
{ 0x20>>2, 0x50>>2, 0x70>>2, 0x88>>2, 0x88>>2, 0xF8>>2, 0x88>>2, 0x88>>2, 0x00>>2, 0x00>>2, },
{ 0x00>>2, 0x3C>>2, 0x50>>2, 0x90>>2, 0x9C>>2, 0xF0>>2, 0x90>>2, 0x9C>>2, 0x00>>2, 0x00>>2, },
{ 0x00>>2, 0x70>>2, 0x88>>2, 0x80>>2, 0x80>>2, 0x80>>2, 0x88>>2, 0x70>>2, 0x20>>2, 0x40>>2, },
{ 0x40>>2, 0xF8>>2, 0x80>>2, 0x80>>2, 0xF0>>2, 0x80>>2, 0x80>>2, 0xF8>>2, 0x00>>2, 0x00>>2, },
{ 0x10>>2, 0xF8>>2, 0x80>>2, 0x80>>2, 0xF0>>2, 0x80>>2, 0x80>>2, 0xF8>>2, 0x00>>2, 0x00>>2, },
{ 0x20>>2, 0xF8>>2, 0x80>>2, 0x80>>2, 0xF0>>2, 0x80>>2, 0x80>>2, 0xF8>>2, 0x00>>2, 0x00>>2, },
{ 0x50>>2, 0xF8>>2, 0x80>>2, 0x80>>2, 0xF0>>2, 0x80>>2, 0x80>>2, 0xF8>>2, 0x00>>2, 0x00>>2, },
{ 0x40>>2, 0x20>>2, 0x70>>2, 0x20>>2, 0x20>>2, 0x20>>2, 0x20>>2, 0x70>>2, 0x00>>2, 0x00>>2, },
{ 0x10>>2, 0x20>>2, 0x70>>2, 0x20>>2, 0x20>>2, 0x20>>2, 0x20>>2, 0x70>>2, 0x00>>2, 0x00>>2, },
{ 0x20>>2, 0x50>>2, 0x70>>2, 0x20>>2, 0x20>>2, 0x20>>2, 0x20>>2, 0x70>>2, 0x00>>2, 0x00>>2, },
{ 0x50>>2, 0x00>>2, 0x70>>2, 0x20>>2, 0x20>>2, 0x20>>2, 0x20>>2, 0x70>>2, 0x00>>2, 0x00>>2, },
{ 0x00>>2, 0xF0>>2, 0x48>>2, 0x48>>2, 0xE8>>2, 0x48>>2, 0x48>>2, 0xF0>>2, 0x00>>2, 0x00>>2, },
{ 0x28>>2, 0x50>>2, 0x88>>2, 0xC8>>2, 0xA8>>2, 0x98>>2, 0x88>>2, 0x88>>2, 0x00>>2, 0x00>>2, },
{ 0x40>>2, 0x20>>2, 0x70>>2, 0x88>>2, 0x88>>2, 0x88>>2, 0x88>>2, 0x70>>2, 0x00>>2, 0x00>>2, },
{ 0x10>>2, 0x20>>2, 0x70>>2, 0x88>>2, 0x88>>2, 0x88>>2, 0x88>>2, 0x70>>2, 0x00>>2, 0x00>>2, },
{ 0x20>>2, 0x50>>2, 0x70>>2, 0x88>>2, 0x88>>2, 0x88>>2, 0x88>>2, 0x70>>2, 0x00>>2, 0x00>>2, },
{ 0x28>>2, 0x50>>2, 0x70>>2, 0x88>>2, 0x88>>2, 0x88>>2, 0x88>>2, 0x70>>2, 0x00>>2, 0x00>>2, },
{ 0x50>>2, 0x00>>2, 0x70>>2, 0x88>>2, 0x88>>2, 0x88>>2, 0x88>>2, 0x70>>2, 0x00>>2, 0x00>>2, },
{ 0x00>>2, 0x00>>2, 0x00>>2, 0x88>>2, 0x50>>2, 0x20>>2, 0x50>>2, 0x88>>2, 0x00>>2, 0x00>>2, },
{ 0x00>>2, 0x70>>2, 0x98>>2, 0x98>>2, 0xA8>>2, 0xC8>>2, 0xC8>>2, 0x70>>2, 0x00>>2, 0x00>>2, },
{ 0x40>>2, 0x20>>2, 0x88>>2, 0x88>>2, 0x88>>2, 0x88>>2, 0x88>>2, 0x70>>2, 0x00>>2, 0x00>>2, },
{ 0x10>>2, 0x20>>2, 0x88>>2, 0x88>>2, 0x88>>2, 0x88>>2, 0x88>>2, 0x70>>2, 0x00>>2, 0x00>>2, },
{ 0x20>>2, 0x50>>2, 0x00>>2, 0x88>>2, 0x88>>2, 0x88>>2, 0x88>>2, 0x70>>2, 0x00>>2, 0x00>>2, },
{ 0x50>>2, 0x00>>2, 0x88>>2, 0x88>>2, 0x88>>2, 0x88>>2, 0x88>>2, 0x70>>2, 0x00>>2, 0x00>>2, },
{ 0x10>>2, 0x20>>2, 0x88>>2, 0x88>>2, 0x50>>2, 0x20>>2, 0x20>>2, 0x20>>2, 0x00>>2, 0x00>>2, },
{ 0x00>>2, 0x80>>2, 0xF0>>2, 0x88>>2, 0xF0>>2, 0x80>>2, 0x80>>2, 0x80>>2, 0x00>>2, 0x00>>2, },
{ 0x00>>2, 0x70>>2, 0x88>>2, 0x90>>2, 0xA0>>2, 0x90>>2, 0x88>>2, 0xB0>>2, 0x00>>2, 0x00>>2, },
{ 0x40>>2, 0x20>>2, 0x00>>2, 0x70>>2, 0x08>>2, 0x78>>2, 0x88>>2, 0x78>>2, 0x00>>2, 0x00>>2, },
{ 0x10>>2, 0x20>>2, 0x00>>2, 0x70>>2, 0x08>>2, 0x78>>2, 0x88>>2, 0x78>>2, 0x00>>2, 0x00>>2, },
{ 0x20>>2, 0x50>>2, 0x00>>2, 0x70>>2, 0x08>>2, 0x78>>2, 0x88>>2, 0x78>>2, 0x00>>2, 0x00>>2, },
{ 0x28>>2, 0x50>>2, 0x00>>2, 0x70>>2, 0x08>>2, 0x78>>2, 0x88>>2, 0x78>>2, 0x00>>2, 0x00>>2, },
{ 0x00>>2, 0x50>>2, 0x00>>2, 0x70>>2, 0x08>>2, 0x78>>2, 0x88>>2, 0x78>>2, 0x00>>2, 0x00>>2, },
{ 0x20>>2, 0x50>>2, 0x20>>2, 0x70>>2, 0x08>>2, 0x78>>2, 0x88>>2, 0x78>>2, 0x00>>2, 0x00>>2, },
{ 0x00>>2, 0x00>>2, 0x00>>2, 0x78>>2, 0x14>>2, 0x7C>>2, 0x90>>2, 0x7C>>2, 0x00>>2, 0x00>>2, },
{ 0x00>>2, 0x00>>2, 0x00>>2, 0x70>>2, 0x88>>2, 0x80>>2, 0x88>>2, 0x70>>2, 0x20>>2, 0x40>>2, },
{ 0x40>>2, 0x20>>2, 0x00>>2, 0x70>>2, 0x88>>2, 0xF8>>2, 0x80>>2, 0x70>>2, 0x00>>2, 0x00>>2, },
{ 0x10>>2, 0x20>>2, 0x00>>2, 0x70>>2, 0x88>>2, 0xF8>>2, 0x80>>2, 0x70>>2, 0x00>>2, 0x00>>2, },
{ 0x20>>2, 0x50>>2, 0x00>>2, 0x70>>2, 0x88>>2, 0xF8>>2, 0x80>>2, 0x70>>2, 0x00>>2, 0x00>>2, },
{ 0x00>>2, 0x50>>2, 0x00>>2, 0x70>>2, 0x88>>2, 0xF8>>2, 0x80>>2, 0x70>>2, 0x00>>2, 0x00>>2, },
{ 0x40>>2, 0x20>>2, 0x00>>2, 0x60>>2, 0x20>>2, 0x20>>2, 0x20>>2, 0x70>>2, 0x00>>2, 0x00>>2, },
{ 0x20>>2, 0x40>>2, 0x00>>2, 0x60>>2, 0x20>>2, 0x20>>2, 0x20>>2, 0x70>>2, 0x00>>2, 0x00>>2, },
{ 0x20>>2, 0x50>>2, 0x00>>2, 0x60>>2, 0x20>>2, 0x20>>2, 0x20>>2, 0x70>>2, 0x00>>2, 0x00>>2, },
{ 0x00>>2, 0x50>>2, 0x00>>2, 0x60>>2, 0x20>>2, 0x20>>2, 0x20>>2, 0x70>>2, 0x00>>2, 0x00>>2, },
{ 0x00>>2, 0xC0>>2, 0x30>>2, 0x70>>2, 0x88>>2, 0x88>>2, 0x88>>2, 0x70>>2, 0x00>>2, 0x00>>2, },
{ 0x28>>2, 0x50>>2, 0x00>>2, 0xB0>>2, 0xC8>>2, 0x88>>2, 0x88>>2, 0x88>>2, 0x00>>2, 0x00>>2, },
{ 0x40>>2, 0x20>>2, 0x00>>2, 0x70>>2, 0x88>>2, 0x88>>2, 0x88>>2, 0x70>>2, 0x00>>2, 0x00>>2, },
{ 0x10>>2, 0x20>>2, 0x00>>2, 0x70>>2, 0x88>>2, 0x88>>2, 0x88>>2, 0x70>>2, 0x00>>2, 0x00>>2, },
{ 0x20>>2, 0x50>>2, 0x00>>2, 0x70>>2, 0x88>>2, 0x88>>2, 0x88>>2, 0x70>>2, 0x00>>2, 0x00>>2, },
{ 0x28>>2, 0x50>>2, 0x00>>2, 0x70>>2, 0x88>>2, 0x88>>2, 0x88>>2, 0x70>>2, 0x00>>2, 0x00>>2, },
{ 0x00>>2, 0x50>>2, 0x00>>2, 0x70>>2, 0x88>>2, 0x88>>2, 0x88>>2, 0x70>>2, 0x00>>2, 0x00>>2, },
{ 0x00>>2, 0x00>>2, 0x20>>2, 0x00>>2, 0xF8>>2, 0x00>>2, 0x20>>2, 0x00>>2, 0x00>>2, 0x00>>2, },
{ 0x00>>2, 0x00>>2, 0x00>>2, 0x78>>2, 0x98>>2, 0xA8>>2, 0xC8>>2, 0xF0>>2, 0x00>>2, 0x00>>2, },
{ 0x40>>2, 0x20>>2, 0x00>>2, 0x88>>2, 0x88>>2, 0x88>>2, 0x98>>2, 0x68>>2, 0x00>>2, 0x00>>2, },
{ 0x10>>2, 0x20>>2, 0x00>>2, 0x88>>2, 0x88>>2, 0x88>>2, 0x98>>2, 0x68>>2, 0x00>>2, 0x00>>2, },
{ 0x20>>2, 0x50>>2, 0x00>>2, 0x88>>2, 0x88>>2, 0x88>>2, 0x98>>2, 0x68>>2, 0x00>>2, 0x00>>2, },
{ 0x00>>2, 0x50>>2, 0x00>>2, 0x88>>2, 0x88>>2, 0x88>>2, 0x98>>2, 0x68>>2, 0x00>>2, 0x00>>2, },
{ 0x00>>2, 0x10>>2, 0x20>>2, 0x88>>2, 0x88>>2, 0x98>>2, 0x68>>2, 0x08>>2, 0x88>>2, 0x70>>2, },
{ 0x00>>2, 0x00>>2, 0x80>>2, 0xF0>>2, 0x88>>2, 0x88>>2, 0x88>>2, 0xF0>>2, 0x80>>2, 0x80>>2, },
{ 0x00>>2, 0x50>>2, 0x00>>2, 0x88>>2, 0x88>>2, 0x98>>2, 0x68>>2, 0x08>>2, 0x88>>2, 0x70>>2, },
};

static gp2x_font gp2x_default_font;

void (*gp2x_printfchar)(gp2x_font *f, unsigned char c);

void gp2x_printfchar15(gp2x_font *f, unsigned char c)
{
  unsigned short *dst=&gp2x_video_RGB[0].screen16[f->x+f->y*320],w,h=f->h;
//unsigned char  *src=f->data[ (c%16)*f->w + (c/16)*f->h ];
  unsigned char  *src=&f->data[c*10];

 if(f->solid)
         while(h--)
         {
          w=f->wmask;
          while(w)
          {
           if( *src & w ) *dst++=f->fg; else *dst++=f->bg;
           w>>=1;
          }
          src++;    

          dst+=320-(f->w);
         }
 else
         while(h--)
         {
          w=f->wmask;
          while(w)
          {
           if( *src & w ) *dst=f->fg;
           dst++;
           w>>=1;
          }
          src++;

          dst+=320-(f->w);
         }
}

void gp2x_printfchar8(gp2x_font *f, unsigned char c)
{
  unsigned char *dst=&gp2x_video_RGB[0].screen8[f->x+f->y*320],w,h=f->h;
  unsigned char *src=&f->data[c*10];

 if(f->solid)
         while(h--)
         {
          w=f->wmask;
          while(w)
          {
           if( *src & w ) *dst++=0xFF; else *dst++=0xFE;
           w>>=1;
          }
          src++;    

          dst+=320-(f->w);
         }
 else
         while(h--)
         {
          w=f->wmask;
          while(w)
          {
           if( *src & w ) *dst=0xFF;
           dst++;
           w>>=1;
          }
          src++;    

          dst+=320-(f->w);
         }
}

/* Function: gp2x_printf
   This function printfs a string into the RGB layer.

   Note:
   - This function does not perform any clipping.

   Parameters:
   *f - <gp2x_font> or NULL. NULL will use the default 6x10 font.
   x (0..320) - Horizontal coordinate for the given string
       If *x* is negative, gp2x_printf() will continue on last known horizontal position.
   y (0..240) - Vertical coordinate for the given string 
       If *y* is negative, gp2x_printf() will continue on last known vertical position.
   format - C formatted standard string.

   See also:
   <gp2x_printf_init>

   Example:
   > a=1;
   > gp2x_printf(NULL, 0, 0,"Hello %dst world\n",a);
   > gp2x_printf(NULL,-1,-1,"Hello %dnd world\n",++a);
   >
   > ...it outputs...
   >
   > Hello 1st world                (at top-left of screen)
   > Hello 2nd world                (under the previous line) */
 
void gp2x_printf(gp2x_font *f, int x, int y, const char *format, ...)
{
 char buffer[4096]; int c; gp2x_font *g=&gp2x_default_font;
 va_list  args;

 va_start(args, format);
 vsprintf(buffer, format, args);

 if(f!=NULL) g=f;

 if(x<0) x=g->x; else g->x=x; 
 if(y<0) y=g->y; else g->y=y;

 for(c=0;buffer[c];c++)
 {
  switch(buffer[c])
  {
   case '\b': g->x=x;g->y=y; break;

   case '\n': g->y+=g->h;
   case '\r': g->x=x;
              break;

   default:   gp2x_printfchar(g, (unsigned char)buffer[c]);
              g->x+=g->w;
              break;
  }
 }
}

/* Function: gp2x_printf_init
   This function allows you to set your own fixed <gp2x_font>.

   Parameters:
   *f - Pointer to a <gp2x_font> struct.
   w (1..) - Width of each character, in pixels.
   h (1..) - Height of each character, in pixels.
   *data - Pointer to your font bitmap.
   fg - Foreground font color.
   bg - Background font color (when solid is not 0).
   solid (0,1) - When 1, background font color is used.
           When 0, transparent background font is used.
  
   See also:
   <gp2x_printf> */

void gp2x_printf_init(gp2x_font *f, int w, int h, void *data, int fg, int bg, int solid)
{
 f->x=f->y=0;
 f->wmask=1<<(w-1);
 f->w=w;
 f->h=h;
 f->data=(unsigned char *)data;
 f->fg=fg;
 f->bg=bg;
 f->solid=solid;
}





/*
   ,--------------------.
   |                    |X
   |   GP2X - LIBRARY   |X
   |                    |X
   `--------------------'X
    XXXXXXXXXXXXXXXXXXXXXX 
*/



/* Function: gp2x_init
   This function sets up the whole library.

   Notes:
   - *You have to call this function before any other function*.
   - If you are merging both SDL and Minimal Library in your project,
   you will have to call gp2x_init after any SDL_Init() / SDL_SetVideoMode() / SDL_CreateRGBSurface() call.

   Parameters:                     
   ticks_per_second (1..7372800) - sets internal <gp2x_ticks>. Eg, set it to 1000 to work in milliseconds.
   bpp (8,15,16) - sets the bits per pixel video mode
   rate (11025,22050,44100) - sets the sound frequency rate
   bits (16) - sets the sound bits. GP2X supports 16 bits only.
   stereo (0,1) - sets the stereo mode. 1 for stereo, 0 for mono.
   Hz (unused) - sets sound poll frequency, in hertzs. Unused in this release.
   solid_font (0,1) - sets default 6x10 font to have solid background or not.

   See also:
   <gp2x_deinit> */


void gp2x_init(int ticks_per_second, int bpp, int rate, int bits, int stereo, int Hz, int solid_font)
{
  struct fb_fix_screeninfo fixed_info;
  static int first=1;

  //init misc variables
  if(first) gp2x_sound_pausei=1, gp2x_sound_thread=0, gp2x_exit=0, gp2x_ticks=0, gp2x_ticks_per_second=7372800/ticks_per_second;

  //init font
  gp2x_printf_init(&gp2x_default_font,6,10,gp2x_fontf,0xFFFF,0x0000,solid_font);

  //open devices
  if(!gp2x_dev[0])  gp2x_dev[0] = open("/dev/fb0",   O_RDWR);
  if(!gp2x_dev[1])  gp2x_dev[1] = open("/dev/fb1",   O_RDWR);
  if(!gp2x_dev[2])  gp2x_dev[2] = open("/dev/mem",   O_RDWR); 
  if(!gp2x_dev[3])  gp2x_dev[3] = open("/dev/dsp",   O_WRONLY);
  if(!gp2x_dev[4])  gp2x_dev[4] = open("/dev/mixer", O_RDWR);

  //map memory for our cursor + 4 YUV regions (double buffered each one)
  gp2x_video_cursor_virt=(void *)mmap(0,  0x4000, PROT_READ|PROT_WRITE, MAP_SHARED, gp2x_dev[2], (gp2x_video_cursor_phys=0x04000000-0x4B000*8-0x4000) );
  gp2x_video_YUV[0].p[0]=(void *)mmap(0, 0x4B000, PROT_READ|PROT_WRITE, MAP_SHARED, gp2x_dev[2], (gp2x_video_YUV[0].i[0]=0x04000000-0x4B000*8) );
  gp2x_video_YUV[0].p[1]=(void *)mmap(0, 0x4B000, PROT_READ|PROT_WRITE, MAP_SHARED, gp2x_dev[2], (gp2x_video_YUV[0].i[1]=0x04000000-0x4B000*7) );
  gp2x_video_YUV[1].p[0]=(void *)mmap(0, 0x4B000, PROT_READ|PROT_WRITE, MAP_SHARED, gp2x_dev[2], (gp2x_video_YUV[1].i[0]=0x04000000-0x4B000*6) );
  gp2x_video_YUV[1].p[1]=(void *)mmap(0, 0x4B000, PROT_READ|PROT_WRITE, MAP_SHARED, gp2x_dev[2], (gp2x_video_YUV[1].i[1]=0x04000000-0x4B000*5) );
  gp2x_video_YUV[2].p[0]=(void *)mmap(0, 0x4B000, PROT_READ|PROT_WRITE, MAP_SHARED, gp2x_dev[2], (gp2x_video_YUV[2].i[0]=0x04000000-0x4B000*4) );
  gp2x_video_YUV[2].p[1]=(void *)mmap(0, 0x4B000, PROT_READ|PROT_WRITE, MAP_SHARED, gp2x_dev[2], (gp2x_video_YUV[2].i[1]=0x04000000-0x4B000*3) );
  gp2x_video_YUV[3].p[0]=(void *)mmap(0, 0x4B000, PROT_READ|PROT_WRITE, MAP_SHARED, gp2x_dev[2], (gp2x_video_YUV[3].i[0]=0x04000000-0x4B000*2) );
  gp2x_video_YUV[3].p[1]=(void *)mmap(0, 0x4B000, PROT_READ|PROT_WRITE, MAP_SHARED, gp2x_dev[2], (gp2x_video_YUV[3].i[1]=0x04000000-0x4B000*1) );

  //map memory for GP2X hw registers, and for dualcore usage
  gp2x_dualcore_ram=(unsigned long  *)mmap(0, 0x1000000-0x4B000*8-0x4000, PROT_READ|PROT_WRITE, MAP_SHARED, gp2x_dev[2], 0x03000000);
//gp2x_dualcore_ram=(unsigned long  *)mmap(0, 0x2000000,                  PROT_READ|PROT_WRITE, MAP_SHARED, gp2x_dev[2], 0x02000000); /*for HH*/
       gp2x_memregl=(unsigned long  *)mmap(0, 0x10000,                    PROT_READ|PROT_WRITE, MAP_SHARED, gp2x_dev[2], 0xc0000000);
       gp2x_memregs=(unsigned short *)gp2x_memregl;

  if(first) { printf(MINILIB_VERSION "\n");
              gp2x_save_registers(0);
              gp2x_940t_reset(1);
              gp2x_940t_pause(1);
              gp2x_sound_volume(100,100);
              gp2x_memregs[0x0F16>>1] = 0x830a; usleep(100000);
              gp2x_memregs[0x0F58>>1] = 0x100c; usleep(100000); }

  ioctl(gp2x_dev[0], FBIOGET_FSCREENINFO, &fixed_info); 
  gp2x_video_RGB[0].p[2]=gp2x_video_RGB[0].p[0]=(void *)mmap(0, 320*240*2, PROT_WRITE, MAP_SHARED, gp2x_dev[0], 0);
  gp2x_video_RGB[0].i[2]=gp2x_video_RGB[0].i[0]=fixed_info.smem_start;

  ioctl(gp2x_dev[1], FBIOGET_FSCREENINFO, &fixed_info);
  gp2x_video_RGB[0].p[3]=gp2x_video_RGB[0].p[1]=(void *)mmap(0, 320*240*2, PROT_WRITE, MAP_SHARED, gp2x_dev[1], 0);
  gp2x_video_RGB[0].i[3]=gp2x_video_RGB[0].i[1]=fixed_info.smem_start;

  //set YUV pixel width for A/B top/bottom regions 
  gp2x_memregs[0x2892>>1] = gp2x_memregs[0x2894>>1] = gp2x_memregs[0x28BC>>1] = gp2x_memregs[0x28BE>>1] = 320*4; /*YUV*/
  //set YUV input memory for regions/skip alpha blending/priority to region A
  gp2x_memregs[0x2884>>1]=0;     
  //set RGB pixel width (8,15/16)
  gp2x_memregs[0x290C>>1]=320*((bpp+1)/8);  
  //set RGB bpp (8,15/16) ; enable RGB window 1
  gp2x_memregs[0x28DA>>1]=(((bpp+1)/8)<<9)|0x0AB;                                                                /*RGB: 8/15/16/24bpp and 5 layers active*/

  //clear icounters+pcounters at gp2x_video_layer structs
  memset(&gp2x_video_RGB[0].i[6], 0, sizeof(unsigned long)*2);
  memset(&gp2x_video_YUV[0].i[6], 0, sizeof(unsigned long)*2);
  memset(&gp2x_video_YUV[1].i[6], 0, sizeof(unsigned long)*2);
  memset(&gp2x_video_YUV[2].i[6], 0, sizeof(unsigned long)*2);
  memset(&gp2x_video_YUV[3].i[6], 0, sizeof(unsigned long)*2);

  //set some video settings
  if(first) {   gp2x_video_setluminance(0,0);
                gp2x_video_setdithering(0); 
                gp2x_video_setgammacorrection(1.0);                                                            
                gp2x_video_RGB_setcolorkey(0,0,0);
                gp2x_video_RGB_setscaling(320,240);
                gp2x_video_RGB_setwindows(0x11,-1,-1,-1,319,239);
                gp2x_video_YUV_setscaling(0,320,240);
                gp2x_video_YUV_setscaling(1,320,240);
                gp2x_video_YUV_setscaling(2,320,240);
                gp2x_video_YUV_setscaling(3,320,240);
                gp2x_video_YUV_setparts(-1,-1,-1,-1,319,239);
                gp2x_video_cursor_setup(gp2x_video_cursor_default, 16, 2,255,255,255,0xF, 1,0,0,0,0xF);
                gp2x_video_cursor_show(0); }

  //set default 8bpp palette 
  if(bpp==8) { gp2x_video_RGB_color8(0x00,0x00,0x00,0);
               gp2x_video_RGB_color8(0x00,0x00,0x00,254);
               gp2x_video_RGB_color8(0xFF,0xFF,0xFF,255);
               gp2x_video_RGB_setpalette(); }

  //clear video (FIXME: should clean YUV p[] areas too)
  memset(gp2x_video_RGB[0].p[0], 0, 320*240*2);
  memset(gp2x_video_RGB[0].p[1], 0, 320*240*2);

  //enable 8bpp quadruple buffering
  if(bpp==8) gp2x_video_RGB[0].i[2]+=320*240, gp2x_video_RGB[0].p[2]=(void*)(((short*)gp2x_video_RGB[0].p[2])+320*240/2),
             gp2x_video_RGB[0].i[3]+=320*240, gp2x_video_RGB[0].p[3]=(void*)(((short*)gp2x_video_RGB[0].p[3])+320*240/2);

  //update screen8/screen16/screen32 pointers
  gp2x_video_RGB_flip(0);
  gp2x_video_YUV_flip(0); gp2x_video_YUV_flip(1); gp2x_video_YUV_flip(2); gp2x_video_YUV_flip(3);

  //configure some misc functions
  if(bpp==8) gp2x_blitter_rect=gp2x_blitter_rect8,  gp2x_printfchar=gp2x_printfchar8;
       else  gp2x_blitter_rect=gp2x_blitter_rect15, gp2x_printfchar=gp2x_printfchar15;

  //set sound
  ioctl(gp2x_dev[3], SNDCTL_DSP_SPEED,  &rate);
  ioctl(gp2x_dev[3], SNDCTL_DSP_SETFMT, &bits);
  ioctl(gp2x_dev[3], SNDCTL_DSP_STEREO, &stereo);

  //set some default options, launches sound engine, and ready to rock... :-)
  if(first) {   audio_buf_info abi;
                //int frag = (0x80000|6)+(rate>8250)+(rate>16500)+(rate>33000)+(stereo==1)+(bits==16);
                int frag = 0x80000|7;
                //int frag=0xf0008;
                
                ioctl(gp2x_dev[3], SNDCTL_DSP_SETFRAGMENT, &frag);
                ioctl(gp2x_dev[3], SNDCTL_DSP_GETOSPACE, &abi);

                gp2x_sound_buffer=(unsigned short *)malloc(16*(4+(abi.fragsize<<(stereo+(bits==16)))));
                gp2x_sound_buffer[1]=(gp2x_sound_buffer[0]=(abi.fragsize)) << (stereo + (bits==16));
                gp2x_sound_buffer[2]=(1000000000/Hz)&0xFFFF;
                gp2x_sound_buffer[3]=(1000000000/Hz)>>16;

                //gp2x_sound_buffer=(unsigned short *)malloc(16*(4+((rate/Hz)<<((stereo==1)+(bits==16)))));
                //gp2x_sound_buffer[1]=(gp2x_sound_buffer[0]=((rate/Hz)))   <<((stereo==1)+(bits==16));
                //gp2x_sound_buffer[2]=(1000000000/Hz)&0xFFFF;
                //gp2x_sound_buffer[3]=(1000000000/Hz)>>16;

                pthread_create( &gp2x_sound_thread, NULL, gp2x_sound_play, NULL);
                atexit(gp2x_deinit);  
                first=0;  }
}


/* Function: gp2x_deinit
   This function unsets the whole library and returns to GP2X menu.

   Note:    
   - You can exit() your program, or call this function directly.

   See also:
   <gp2x_init> */

extern int fcloseall(void);
void gp2x_deinit(void)
{
  gp2x_init(1000, 16, 44100,16,1,60, 1);

  while((gp2x_exit++)<1000000);

  gp2x_save_registers(2); 

  gp2x_940t_reset(1);
  gp2x_940t_pause(1);

  gp2x_video_setdithering(2); 
  gp2x_video_setluminance(0,0);
  gp2x_video_setgammacorrection(1.0);
  gp2x_video_cursor_show(0);
  gp2x_video_RGB_setscaling(320,240);
  gp2x_video_RGB_setcolorkey(0,0,0);
  gp2x_video_RGB_setwindows(0x11,-1,-1,-1,319,239);
  gp2x_video_YUV_setparts(-1,-1,-1,-1,319,239);

  munmap((void *)gp2x_dualcore_ram, 0x1000000-0x4B000*8-0x4000);
  munmap((void *)gp2x_memregl,      0x10000);
  munmap(gp2x_video_YUV[0].p[0],    0x4B000);
  munmap(gp2x_video_YUV[0].p[1],    0x4B000);
  munmap(gp2x_video_YUV[1].p[0],    0x4B000);
  munmap(gp2x_video_YUV[1].p[1],    0x4B000);
  munmap(gp2x_video_YUV[2].p[0],    0x4B000);
  munmap(gp2x_video_YUV[2].p[1],    0x4B000);
  munmap(gp2x_video_YUV[3].p[0],    0x4B000);
  munmap(gp2x_video_YUV[3].p[1],    0x4B000);
  munmap(gp2x_video_RGB[0].p[0],    320*240*2);
  munmap(gp2x_video_RGB[0].p[1],    320*240*2);
  munmap(gp2x_video_cursor_virt,    0x4000);

  { int i; for(i=0;i<8;i++) if(gp2x_dev[i]) close(gp2x_dev[i]); }

  fcloseall();

  free((void *)gp2x_sound_buffer);

  chdir("/usr/gp2x");
  execl("gp2xmenu","gp2xmenu",NULL);
}
