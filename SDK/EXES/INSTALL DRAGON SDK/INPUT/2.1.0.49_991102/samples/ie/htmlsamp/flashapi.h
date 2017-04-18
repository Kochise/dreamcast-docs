#ifndef _FLASHAPI_H
#define _FLASHAPI_H

struct IDirectSound;

BOOL InitFlashAPI();
void ShutdownFlashAPI();
void FlashSetDirectSound(IDirectSound *pDS);
void FlashIdle();
void FlashMouseDown(int x, int y);
void FlashMouseMove(int x, int y);
void FlashMouseUp(int x, int y);

#endif