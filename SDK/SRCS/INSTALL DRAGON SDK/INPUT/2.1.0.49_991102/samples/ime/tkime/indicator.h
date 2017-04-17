#ifndef INDICATOR_H
#define INDICATOR_H

#define INDICATOR_WIDTH         32
#define INDICATOR_HEIGHT        32
#define INDICATOR_LEFTEDGE      500
#define INDICATOR_TOPEDGE       45
#define INDICATOR_BITMAP_NAME   TEXT("INDICATOR_BITMAP")

#define INDICATOR_IMEON             0
#define INDICATOR_IMEOFF            1
#define INDICATOR_RKCON             2
#define INDICATOR_RKCOFF            3
#define INDICATOR_HIRA              4
#define INDICATOR_HIRAHALFHEIGHT    5
#define INDICATOR_KATA              6
#define INDICATOR_KATAHALFHEIGHT    7
#define INDICATOR_KATAHALFWIDTH     8
#define INDICATOR_KATAHALFBOTH      9
#define INDICATOR_ENGLISHUPPER      10
#define INDICATOR_ENGLISHLOWER      11
#define INDICATOR_ENGLISHUPPERWIDE  12
#define INDICATOR_ENGLISHLOWERWIDE  13
#define INDICATOR_DOUBLEWIDTH       14
#define INDICATOR_HALFWIDTH         15

typedef struct _KeyboardState
{
    BOOL fIMEOn;
    BOOL fRKCOn;
    BOOL fCapsOn;
    KBDLAYOUT keyboard;
    KBDLAYOUT keyboardRememberOld;
    BOOL fHalfWidth;        // for Katakana keyboard only
    BOOL fHalfHeight;       // for Katakana and Hiragana keyboards
    BOOL fDoubleWidth;      // for Romanji keyboard only
} KeyboardState;

void
ResetSoftKeybdState
    (
    void
    );

void
ResetHardKeybdState
    (
    void
    );

BOOL
IndicatorCreate
    (
    void
    );

void
IndicatorDestroy
    (
    void
    );

void
IndicatorBlt
    (
    LPDIRECTDRAWSURFACE lpDDSBack
    );

extern KeyboardState       g_swkeybdstate;
extern KeyboardState       g_hwkeybdstate;
extern KeyboardState       *g_pkeybdstateCurrent;

#endif
