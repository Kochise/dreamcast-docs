/* png example for KOS 1.1.x
 * Jeffrey McBeth / Morphogenesis
 * <mcbeth@morphogenesis.2y.net>
 *
 * Heavily borrowed from from 2-D example
 * AndrewK / Napalm 2001
 * <andrewk@napalm-x.com>
 */

#include <kos.h>
#include <png/png.h>
#include <zlib/zlib.h>
#include <zlib.h>
#include <dcutils/pvrutils.h>

/* font data */
extern char wfont[];

/* textures */
unsigned int font_tex;
unsigned int back_tex;
char *data;

/* init background */
void back_init()
{
    back_tex = ta_txr_allocate(512*512*2);
    png_to_texture("/rd/background.png", back_tex, PNG_NO_ALPHA);
}

/* init font */
void font_init()
{
    int i,x,y,c;
    unsigned short * temp_tex;
    
    font_tex = ta_txr_allocate(256*256*2);
    temp_tex = (unsigned short *)malloc(256*128*2);
    
    c = 0;
    for(y = 0; y < 128 ; y+=16)
        for(x = 0; x < 256 ; x+=8) {
            for(i = 0; i < 16; i++) {
                temp_tex[x + (y+i) * 256 + 0] = 0xffff * ((wfont[c+i] & 0x80)>>7);
                temp_tex[x + (y+i) * 256 + 1] = 0xffff * ((wfont[c+i] & 0x40)>>6);
                temp_tex[x + (y+i) * 256 + 2] = 0xffff * ((wfont[c+i] & 0x20)>>5);
                temp_tex[x + (y+i) * 256 + 3] = 0xffff * ((wfont[c+i] & 0x10)>>4);
                temp_tex[x + (y+i) * 256 + 4] = 0xffff * ((wfont[c+i] & 0x08)>>3);
                temp_tex[x + (y+i) * 256 + 5] = 0xffff * ((wfont[c+i] & 0x04)>>2);
                temp_tex[x + (y+i) * 256 + 6] = 0xffff * ((wfont[c+i] & 0x02)>>1);
                temp_tex[x + (y+i) * 256 + 7] = 0xffff * (wfont[c+i] & 0x01);
            }
            c+=16;
        }
    txr_twiddle_copy(temp_tex, 256, 128, font_tex, 256, 256, 0);
}

void text_init()
{
  int length = zlib_getlength("/rd/text.gz");
  gzFile f;

  data = (char *)malloc(length+1); // I am not currently freeing it

  f = gzopen("/rd/text.gz", "r");
  gzread(f, data, length);
  data[length] = 0;
  gzclose(f);
    
  printf("length [%d]\n", length);
}

/* draw background */
void draw_back(void)
{
    poly_hdr_t poly;
    vertex_ot_t vert;

    ta_poly_hdr_txr(&poly, TA_OPAQUE, TA_RGB565_TWID, 512, 512, back_tex, TA_BILINEAR_FILTER);
    ta_commit_poly_hdr(&poly);
    
    vert.r = vert.g = vert.b = 1.0f;
    vert.a = 1.0f;
    vert.oa = vert.or = vert.ob = 0.0f;
    vert.flags = TA_VERTEX_NORMAL;
    
    vert.x = 1;
    vert.y = 1;
    vert.z = 1;
    vert.u = 0.0;
    vert.v = 0.0;
    ta_commit_vertex(&vert, sizeof(vert));
    
    vert.x = 640;
    vert.y = 1;
    vert.z = 1;
    vert.u = 1.0;
    vert.v = 0.0;
    ta_commit_vertex(&vert, sizeof(vert));
    
    vert.x = 1;
    vert.y = 480;
    vert.z = 1;
    vert.u = 0.0;
    vert.v = 1.0;
    ta_commit_vertex(&vert, sizeof(vert));
    
    vert.x = 640;
    vert.y = 480;
    vert.z = 1;
    vert.u = 1.0;
    vert.v = 1.0;
    vert.flags = TA_VERTEX_EOL;
    ta_commit_vertex(&vert, sizeof(vert));
}

/* draw one character */
void draw_char(float x1, float y1, float z1, float a, float r, float g, float b, int c, float xs, float ys)
{
    vertex_ot_t     vert;
    int             ix, iy;
    float           u1, v1, u2, v2;
    
    ix = (c % 32) * 8;
    iy = (c / 32) * 16;
    u1 = (ix + 0.5f) * 1.0f / 256.0f;
    v1 = (iy + 0.5f) * 1.0f / 256.0f;
    u2 = (ix+7.5f) * 1.0f / 256.0f;
    v2 = (iy+15.5f) * 1.0f / 256.0f;
    
    vert.flags = TA_VERTEX_NORMAL;
    vert.x = x1;
    vert.y = y1 + 16.0f * ys;
    vert.z = z1;
    vert.u = u1;
    vert.v = v2;
    vert.dummy1 = vert.dummy2 = 0;
    vert.a = a;
    vert.r = r;
    vert.g = g;
    vert.b = b;
    vert.oa = vert.or = vert.og = vert.ob = 0.0f;
    ta_commit_vertex(&vert, sizeof(vert));
    
    vert.x = x1;
    vert.y = y1;
    vert.u = u1;
    vert.v = v1;
    ta_commit_vertex(&vert, sizeof(vert));
    
    vert.x = x1 + 8.0f * xs;
    vert.y = y1 + 16.0f * ys;
    vert.u = u2;
    vert.v = v2;
    ta_commit_vertex(&vert, sizeof(vert));
    
    vert.flags = TA_VERTEX_EOL;
    vert.x = x1 + 8.0f * xs;
    vert.y = y1;
    vert.u = u2;
    vert.v = v1;
    ta_commit_vertex(&vert, sizeof(vert));
}

/* draw a string */
void draw_string(float x, float y, float z, float a, float r, float g, float b, char *str, float xs, float ys) {
  poly_hdr_t poly;
  float orig_x = x;
  ta_poly_hdr_txr(&poly, TA_TRANSLUCENT, TA_ARGB4444_TWID, 256, 256,
		  font_tex, TA_BILINEAR_FILTER);
  ta_commit_poly_hdr(&poly);
  
  while (*str) {
    if (*str == '\n')
    {
      x = orig_x;
      y += 40;
      str++;
      continue;
    }
    draw_char(x, y, z, a, r, g, b, *str++, xs, ys);
	x+=8*xs;
  }
}

/* base y coordinate */
int y = 0;

/* draw one frame */
void draw_frame(void)
{
    ta_begin_render();
    draw_back();
    ta_commit_eol();

    /* 1720 and 480 are magic numbers directly related to the text scrolling
     * 1720 is enough room for the whole text to scroll from the bottom of
     * the screen to off the top.  31 lines * 40 pixels + 480 pixel high screen
     * 480 is the height of the screen (starts the text at the bottom)
     */
    draw_string(0, y % 1720 + 440, 3, 1, 1,1,1, data, 2, 2);
    

    ta_commit_eol();
    ta_finish_frame();

    y--;
}

/* romdisk */
extern uint8 romdisk_boot[];

int main(void)
{
    cont_cond_t cond;

    /* init kos  */
    kos_init_all(IRQ_ENABLE | TA_ENABLE | THD_ENABLE, romdisk_boot);
    dbgio_enable();
    
    /* init font */
    font_init();
    
    /* init background */
    back_init();

    /* init text */
    text_init();
    
    /* keep drawing frames until start is pressed */
    while(1) {
        if (cont_get_cond(maple_first_controller(), &cond) < 0)
            break;
        
        if (!(cond.buttons & CONT_START))
            break;

	draw_frame();
    }

    /* shutdown kos */
    kos_shutdown_all();

    return 0;
}

