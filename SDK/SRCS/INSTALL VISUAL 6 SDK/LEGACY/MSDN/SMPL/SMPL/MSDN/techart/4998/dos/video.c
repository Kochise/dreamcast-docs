/* VIDEO.C
   VGA Mode 13h video routines for "Moby" demo.
   Copyright (c) 1996 Microsoft Corporation
*/

#include "video.h"
#include <alloc.h>       // farcalloc()
#include <conio.h>       // clrscr(), getch(), kbhit()
#include <dos.h>         // FP_SEG, geninterrupt()
#include <stdlib.h>      // abs(), exit(), randomize(), random()
#include <stdio.h>        // FILE vars
/*
#ifdef __cplusplus                     // don't mangle function names
  extern "C" {
#endif
void Decode256(void);
#ifdef __cplusplus
}
#endif
*/

// STRUCTURES

struct pcx_header_struct {
  unsigned char signature, version, code, bits_per_plane;
  int xmin, ymin, xmax, ymax;        // image dimensions
  int hres, vres;                    // resolution of originating device
  struct rgb_struct palette[16];
  unsigned char reserved, num_planes;
  int bytes_per_line;
  unsigned char other_stuff[60];
  };


// GLOBALS

// The following are needed by the assembler routine
word DataLength;
word Plane;
word ColumnCount = 0;
word BytesPerLine;
byte RepeatCount = 0;
int LineEnd = 0;
int ScreenWidth = 0;
int Margin = 0;
int far *Scratch;
unsigned int VideoSeg, VideoOffs;
unsigned int buffer_size;

union REGS inregs, outregs;
struct SREGS segregs;

//byte far *Virscr1=NULL, *Virscr2=NULL;  // Pointers to both virtual screens
//word Vaddr1, Vaddr2;                    // Segments of both virtual screens


// STRUCTURES

struct rgb_struct rgb_pal[15];
struct pcx_header_struct pcx_header;

//           //
// CONSTANTS //
//           //

  const TRUE = 1;
  const FALSE = 0;

//                     //
// FUNCTION PROTOTYPES //
//                     //

  // GENERAL VIDEO TOOLS
  void SetMCGA     ();
  void SetText     ();
  void Cls         (byte Col, word Where);
  void Putpixel    (word X, word Y, byte Col, word Where);
  void WaitRetrace ();
  void Pal         (byte Col, byte  R, byte  G, byte  B);

  // MID-LEVEL FUNCTIONS
  void SetUpVirtual();
  void ShutDown    ();
   int sgn         (int a);

byte far *MakeBuffer(word TheSize)
  {
  return (byte far*)malloc(TheSize);
  }  // MakeBuffer

// SetMCGA() - This function gets you into 320x200x256 mode.               //

void SetMCGA() {
  _AX = 0x0013;
  geninterrupt (0x10);
  }

// SetText() - This function gets you into text mode.                      //

void SetText() {
  _AX = 0x0003;
  geninterrupt (0x10);
  }

// Cls() - This clears the screen at location Where to color Col           //

void Cls(byte Col, word Where) {
  asm {
    push    es           // save ES
    mov     cx, 32000    // this is our loop counter.  we want to clear
                         //   64000 bytes of memory, so why do we use 32000?
                         //   1 word = 2 bytes, and we are moving a word at
                         //   a time
    mov     es, [Where]  // move address in Where to ES
    xor     di, di       // zero out DI
    mov     al, [Col]    // move color to AL
    mov     ah, al       // move color to AH (Remember, will be moving
                         //   a WORDS, so we need two copies)
    rep     stosw        // copy AX to Where and drecrement CX by 1
                         //   until CX equals 0
    pop     es           // restore ES
    }
  }


// Putpixel() - This puts a pixel on the screen by writing directly to
//              memory.
void Putpixel (word X, word Y, byte Col, word Where) {
  asm {
    push    ds           // save DS
    push    es           // save ES
    mov     ax, [Where]  // move segment of Where to AX
    mov     es, ax       // set ES to segment of Where
    mov     bx, [X]      // set BX to X
    mov     dx, [Y]      // set DX to Y
    push    bx           // save BX (our X value)
    mov     bx, dx       // now BX and DX are equal to Y
    mov     dh, dl       // copy DL to DH (multiply Y by 256)
    xor     dl, dl       // zero out DL
    shl     bx, 6        // shift BX left 6 places (multiply Y by 64).
    add     dx, bx       // add BX to DX (Y*64 + Y*256 = Y*320)
    pop     bx           // restore BX (X coordinate)
    add     bx, dx       // add BX to DX (Y*320 + X).  this gives you
                         //   the offset in memory you want
    mov     di, bx       // move the offset to DI
    xor     al, al       // zero out AL
    mov     ah, [Col]    // move value of Col into AH
    mov     es:[di], ah  // move Col to the offset in memory (DI)
    pop     es           // restore ES
    pop     ds           // restore DS
    }
  }


// WaitRetrace() - This waits until you are in a Vertical Retrace.         //

void WaitRetrace() {

  asm mov dx,0x03DA

  l1: asm {
    in      al,dx;
    and     al,0x08;
    jnz     l1;
    }
  l2: asm {
    in      al,dx;
    and     al,0x08;
    jz      l2;
    }

  }


// Pal() - This sets the Red, Green, and Blue values of a certain color.   //

void Pal (byte Col, byte  R, byte  G, byte  B) {
  asm {
    mov     dx, 0x3C8    // load DX with 3C8 (write palette function)
    mov     al, [Col]    // move color to AL
    out     dx, al       // write DX to the VGA (tell VGA that we want to
                         //   work with the color in AL
    inc     dx           // load DX with 3C9 (write RGB colors)
    mov     al, [R]      // move Red   to AL
    out     dx, al       // write DX to VGA (tell VGA that we want to use
                         //   the Red value in AL
    mov     al, [G]      // move Green to AL
    out     dx, al       // write DX to VGA
    mov     al, [B]      // move Blue  to AL
    out     dx, al       // write DX to VGA
    }
  }


// Flip() - This copies the entire buffer at "source" to destination.
// It is assumed the destination is the screen so we don't worry about
// the offset part of the pointer.
void Flip(void far *source, word dest) {

  asm {
    push    ds           // save DS
    mov     ax, [dest]   // copy segment of destination to AX
    mov     es, ax       // set ES to point to destination
    lds     si, source     // set DS:SI to point to source
    xor     di, di       // zero out DI
    mov     cx, SCREENWORDS    // set counter
    rep     movsw        // move DS:SI to ES:DI by words. Decrement
                         //   CX by 1 each time until CX is 0
    pop     ds           // restore DS
    }
  }

/*
   PutSprite() - Puts an icon, except its color 0 (black) pixels, onto
              the screen "where", at position X,Y
*/
void PutSprite(word X, word Y, const byte *sprt, const byte far *Where) {

  asm {
    push    ds           // save DS
    push    es           // save ES
    lds     si, [sprt]   // DS:SI points to sprite
    mov     ax, X        // screen coordinates in AX and BX
    mov     bx, Y
    }
  _Redraw: asm {
    push    ax           // save AX (X coordinate)
    les     di, [Where]  // ES:DI points to destination (screen)
                         // Now we calculate the offset within the screen
    mov     ax, bx       // set AX to BX (X)
    mov     bh, bl       // copy BL to BH (multiply Y by 256)
    xor     bl, bl       // zero out BL
    shl     ax, 6        // multiply AX by 64 (Y * 64)
    add     bx, ax       // add AX to BX (Y*64 + Y*256 = Y*320)
    pop     ax           // restore BX (X coordinate)
    add     ax, bx       // add BX to AX (Y*320 + X).  this gives you
                         //   the offset in memory you want
    add     di, ax       // add this offset to the destination pointer
    mov     dl, ICON_HT  // set DL to height of sprite
    xor     ch, ch       // zero out CH
    mov     cl, ICON_WD  // set CL to width of sprite
    cld                  // clear direction flag
    mov     ax, cx       // save width in AX
    }
  _DrawLoop: asm {
    push    di           // save DI (offset of line beginning)
    mov     cx, ax       // width in CX for counter
    }
  _LineLoop: asm {       // DRAW THE DATA
    mov     bl,byte ptr [si]  // load byte of data from sprite to BL
    or      bl, bl       // no effect, but triggers zero flag if bl != 0
    jnz     _Store       // if previous statement did not trigger zero flag
                         //   (BL was not color 0) then write it to the screen).
    }
  _NoPaint: asm {        // SKIP OVER COLOR 0
    inc     si           // Skip to next source pixel
    inc     di           // Skip to next dest. pixel
    loop    _LineLoop    // decrement CX and jump to _LineLoop if CX is
                         //   not 0 (end of line)
    jmp     _NextLine    // if CX is 0 (end of line) jump to _NextLine
    }
  _Store: asm {          // COPY THE DATA
    movsb                // move the byte that DS:SI is pointing to into
                         //   ES:DI and increment SI and DI.
    loop    _LineLoop    // decrement CX and jump to _LineLoop if CX is
    }                      //   not 0 (end of line)

  _NextLine: asm {       // START A NEW LINE
    pop     di           // restore address of line just drawn
    dec     dl           // decrement DL (height)
    jz      _Exit        // when DL equals 0, you are done drawing the sprite
    add     di, 320      // if not end of sprite, add 320 to DI so that we
                         //   start drawing the sprite on the next line
    jmp     _DrawLoop    // go back to _DrawLoop and start drawing the next
    }                      //   line

  _Exit: asm {           // WE ARE DONE DRAWING THE SPRITE
    pop     es           // restore ES
    pop     ds           // restore DS
    }
  }


/* set_color_registers()
   =====================
   Changes the VGA hardware palette
*/
void set_color_registers(cregisters rgb)
  {
// Each group of three bytes represents the RGB values of one of the color
// registers. We take the 6 most significant bits to bring the values
// within the range 0-63 expected by the registers.
  int x;
  for (x = 0; x < 256; x++)
    {
    rgb[x].r >>= 2;
    rgb[x].g >>= 2;
    rgb[x].b >>= 2;
    }

  inregs.h.ah = 0x10;             // function
  inregs.h.al = 0x12;             // subfunction
  segregs.es = FP_SEG(rgb);       // list of colors to put in
  inregs.x.dx = FP_OFF(rgb);
  inregs.x.bx = 0;                // first register to change
  inregs.x.cx = 0x100;            // how many regs to change
  int86x(0x10, &inregs, &outregs, &segregs);
  return;
  }

/* Decode256()
   Reads a PCX file into a memory buffer. This is normally the
   video buffer but in this case we use a variable.
*/
void Decode256()
  {
  /* Main use of registers:

    AL   data byte to be written to video
    BX   end of input buffer
    CL   number of times data byte is to be written
    DX   temporary storage of EndOfLine
    ES   segment of output buffer
    DI   index into output buffer
    SI   index into input buffer
  */
  asm {
    push    si                        // save C register variables
    push    di                        // ditto
    push    bp

    les     si, Scratch               // index into input buffer in SI
      // ES  not used here - we don't use LDS because we want to preserve DS
    mov     bx, DataLength            // end of input buffer
    add     bx, si                    // adjust datalength - SI may not be 0
    mov     es, VideoSeg              // base address of output window
    mov     di, VideoOffs             // index into window
    xor     cx, cx                    // clean up loop counter
    mov     cl, RepeatCount           // restore count from last byte
    cld                               // clear DF
    cmp     cl, 0                     // was last byte a count?
    jne     _multi_data              // yes, so next is data
    }
  // --- Loop through input buffer ---

  _getbyte:                        // last byte was not a count
  asm {
    cmp     di, LineEnd               // reached end of line?
    jb      _NoLineEnd               // no
    add     di, Margin
    mov     dx, ScreenWidth
    add     LineEnd, dx
    }
  _NoLineEnd:
  asm {
    cmp     si, bx                    // end of input buffer?
    je      _exit                    // yes, quit
    push    ds                        // save Pascal's data segment
    push    si                        // Get segment of input buffer into DS
    lds     si, Scratch               //   while preserving SI
    pop     si
    lodsb                             // get byte from DS:SI into AL, increment SI
    pop     ds                        // restore program data
    cmp     al, 192                   // test high bits
    jb      _one_data                // not set, not a count
    // It's a count byte
    xor     al, 192                   // get count from 6 low bits
    mov     cl, al                    // store repeat count
    cmp     si, bx                    // end of input buffer?
    je      _exit                    // yes, quit
    }

  _multi_data:
    asm {
    push    ds                        // save program data
    push    si
    lds     si, Scratch
    pop     si
    lodsb                             // get byte from DS:SI into AL, increment SI
    pop     ds                        // restore program data
    rep     stosb                     // write byte CX times
    jmp     _getbyte
    }
  _one_data:
  asm {
    stosb                             // byte into video
    jmp     _getbyte
    }
  // --- Finished with buffer
  _exit:
  asm {
    mov     VideoOffs, di             // save status for next run thru buffer
    mov     RepeatCount, cl
    pop     bp
    pop     di                        // restore any C register variables
    pop     si
  }
  return;
  } // Decode256()


/* read_PCX()
   ==========
   Reads a 256-color PCX file into an array variable. This is a bare-bones
   function; no checking is done to see if the file is of the correct
   type and size.
*/
int read_PCX(pathstr pic_file_name, cregisters *RGB256, ICON TheIcon)
  {
  FILE *pcx_file;
  long palette_start, total_read;
  byte palette_flag;
  int x;

  pcx_file = fopen(pic_file_name, "rb");
  if (pcx_file != NULL) fread(&pcx_header, 1, 128, pcx_file);
  else return 0;

  // The last 769 bytes of the file are palette information, starting with
  //   a one-byte identifier.
  palette_start = filelength(fileno(pcx_file)) - 769;

  // Verify presence of palette section. Old PCX files may lack it.
  fseek(pcx_file, palette_start, SEEK_SET);
  palette_flag = getc(pcx_file);
  if ((palette_flag != 12) || (pcx_header.version < 5)
     || (fread(RGB256, 3, 256, pcx_file) < 256))
    {
    fclose(pcx_file);
    return 0;
    }

  // Some stuff the assembly routine needs to know
  VideoOffs = FP_OFF(TheIcon);
  VideoSeg = FP_SEG(TheIcon);
  Margin = 0;                // offset from start of destination buffer
  LineEnd = pcx_header.bytes_per_line;
  ScreenWidth = 0;          // ??? 320??? Do we need this at all?
  RepeatCount = 0;          // used by Decode256(); preserved between loops

  // Set up file input buffer. Since we're dealing with small images, we
  // don't need a very big buffer.
  buffer_size = 2048;
  Scratch = (int far*)malloc(buffer_size);
  if (!Scratch)  return 0;             // ERROR

// Read the file in chunks.
  fseek(pcx_file, 128, SEEK_SET);
  total_read = 128;
  do
    {
    // Read a chunk
    DataLength = fread(Scratch, 1, buffer_size, pcx_file);
    total_read += DataLength;
    if (total_read > palette_start)
      DataLength -= (total_read - palette_start);

    // Decode it and put it in the memory location pointed to by
    // VideoOffs and VideoSeg.
    Decode256();
    }
  while ((!feof(pcx_file)) && (total_read < palette_start));

  // Destroy the buffer.
  free(Scratch);
  fclose(pcx_file);
  // Success!
  return 1;
  }

