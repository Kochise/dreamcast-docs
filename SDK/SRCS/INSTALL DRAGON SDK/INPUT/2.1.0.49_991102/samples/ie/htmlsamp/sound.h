#ifndef __SOUND_H               // guard against multiple inclusion
#define __SOUND_H

/********************************************************************
 * sound.h
 *
 * Description
 *     DSound wrappers and helpers
 ********************************************************************/

/********************************************************************
 * Includes
 ********************************************************************/
#include <dsound.h>             // DSound data types and prototypes

/********************************************************************
 * Public functions - Create/Destroy
 ********************************************************************/
BOOL                CreateDirectSound(HWND hwnd);
void                DestroyDirectSound(void);

/********************************************************************
 * Public functions - Helpers
 ********************************************************************/
IDirectSoundBuffer *LoadSoundBuffer(LPCTSTR pszResource);

#endif // SOUND_H

