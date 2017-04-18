// spriteno.h : header file
//
// CSpriteNotifyObj class
//
// This is a class of pure virtual functions with no data.  It is used
// by sprite objects to make notification callbacks.  A user of the CSprite
// class can derive an object from CSpriteNotifyObj and pass a pointer to this
// derived class object to the sprite object for notification calls.
// Just like OLE's IClientSite interface really.
//

#ifndef __SPRITENO__
#define __SPRITENO__

#include "sprite.h"

class CSpriteNotifyObj : public CObject
{
public:
    enum CHANGETYPE {
        ZORDER      = 0x0001,
        POSITION    = 0x0002,
        IMAGE       = 0x0004
    };

public:
    virtual void Change(CSprite *pSprite,
                        CHANGETYPE change,
                        LPVOID p1 = NULL,
                        LPVOID p2 = NULL) = 0;
};

#endif // __SPRITENO__
