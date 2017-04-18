#include "windows.h"
#include "assert.h"
#include "xlconv.h"
#include "biff.h"
#include "string.h"

#define IsXDigit(ch) ((ch >= '0' && ch <= '9') || (ch >= 'A' && ch <= 'F') || (ch >= 'a' && ch <= 'f'))
#define BFromXDigit(ch) ((ch >= '0' && ch <= '9') ? (ch - '0') : ((ch >= 'A' && ch <= 'F') ? (ch - ('A' - 10)) : (ch - ('a' - 10))))

#define cbSzBIFF5 14
#define cbSzOther 12

short FAR PASCAL IsFormatOk(EFCP FAR *);
short FAR PASCAL InitLoad(EFCP FAR *);
short FAR PASCAL AbortLoad(void);
short FAR PASCAL RtNextRecord(void);
short FAR PASCAL CbNextRecord(void);
short FAR PASCAL DataNextRecord(EFCP FAR *);

#define cbBufSize 4096
#define cbOffset 7

#define otChart     5
#define cbOToffset 4

#define fTrue TRUE
#define fFalse FALSE

#define wKeep 0
#define wSkip 1
#define wAbort 2

#define RgbFromStream(hp, cb)	CbFromFile(hp, cb)
#define CbFromFile(rgb, cb)		((lpfnCallBack)(iefccmdCbFromFile,(char FAR *)(rgb), (cb)))
#define AllocCb(rgb, cb)		((lpfnCallBack)(iefccmdAllocCb,(char FAR *)(rgb), (cb)))
#define FreeCb(rgb, cb)			((lpfnCallBack)(iefccmdFreeCb,(char FAR *)(rgb), (cb)))
#define StreamSetpos(l)			((lpfnCallBack)(iefccmdSetPos,(char FAR *)(l), 0))
#define Stream2Setpos(pos, ib) 	StreamSetpos((long)((long)(pos)*cbSector+(ib)))
#define StreamGetpos(lpl)		((lpfnCallBack)(iefccmdGetPos,(char FAR *)(lpl), 0))
#define bltbh(src, dst, cb)		memmove((dst),(src),(cb))

#define min(a,b) (((a) < (b)) ? (a) : (b))
