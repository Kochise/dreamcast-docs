//#define DEBUG               // when defined, screen is half-size
                            //   for sharing memory with IDE

#define ICON_HT 20
#define ICON_WD 32
#define VGA 0xa000         // The address of our VGA screen
#ifdef DEBUG
#define SCREENWORDS 16000  // half size, for debugging
#else
#define SCREENWORDS 32000  // number of words in video buffer
#endif

typedef unsigned char byte;
typedef unsigned int  word;
typedef byte ICON[ICON_HT][ICON_WD];
typedef char pathstr[80];
typedef struct rgb_struct {
  unsigned char r, g, b;
};
typedef struct rgb_struct cregisters[256];

int read_PCX(pathstr pic_file_name, cregisters *rgb256, ICON TheIcon);
byte far *MakeBuffer(word TheSize);
void Flip(void far *source, word dest);
void PutSprite(word X, word Y, const byte *sprt, const byte far *Where);

