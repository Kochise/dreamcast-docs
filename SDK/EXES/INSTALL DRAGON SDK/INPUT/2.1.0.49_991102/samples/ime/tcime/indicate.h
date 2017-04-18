#ifndef _INDICATE_H
#define _INDICATE_H

#define INDICATOR_WIDTH         32
#define INDICATOR_HEIGHT        32
#define INDICATOR_LEFTEDGE      500
#define INDICATOR_TOPEDGE       45
#define INDICATOR_BITMAP_NAME   TEXT("INDICATOR_BITMAP")

#define INDICATOR_IMEON             0
#define INDICATOR_IMEOFF            1
#define INDICATOR_FULLSHAPE         2
#define INDICATOR_HALFSHAPE         3
#define INDICATOR_CAPSON            4
#define INDICATOR_CAPSOFF           5


void SetIMEState(KeyboardState* pnewkeybdstate);

void ResetSoftKeybdState(void);

void ResetHardKeybdState(void);

BOOL IndicatorCreate(void);

void IndicatorDestroy(void);

void IndicatorBlt(LPDIRECTDRAWSURFACE lpDDSBack);


extern KeyboardState       g_swkeybdstate;
extern KeyboardState       g_hwkeybdstate;
extern KeyboardState      *g_pkeybdstateCurrent;

#endif
