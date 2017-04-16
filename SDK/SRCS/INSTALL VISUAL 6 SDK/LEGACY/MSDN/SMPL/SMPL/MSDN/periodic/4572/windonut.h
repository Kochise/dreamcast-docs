#include <windows.h>   // Windows
#include <ddraw.h>     // Direct Draw
#include <dsound.h>    // Direct Sound

#include "basedefs.h"     // Dave's stuff

#include "windonutui.h"   // Symbols for resources

#include "memory.h"       // For MEMORY.C
#include "directdraw.h"   // For DIRECTDRAW.C
#include "spritelow.h"    // For SPRITELOW.C
#include "spritehigh.h"   // For SPRITEHIGH.C
#include "wave.h"
#include "directsound.h"

//===============================================================
//
// Public Function Prototypes (called between code segements)
//
// Preface these functions with the filename that they live in,
// that makes it easier to find them once your program gets
// mondo, and you can quickly recognize far calls in your code.
//
//===============================================================

void    WINDONUT_GameHeartBeat(void);
BOOL    WINDONUT_InitGame (void);

void __cdecl Err( LPSTR fmt, ... );         // This is a generic error reporter. Just does a MsgBox

//===============================================================
//
// Global Variables. The GLOBAL and GLOBAL CHAR macros expect
// that *one* of your .C files has the INMAIN symbol defined,
// all the other C files should NOT have the INMAIN symbol
// defined.
//
// If you are using precompiled headers, you will need one
// PCH file for the INMAIN definition, and one for the
// non INMAIN definition.
//
//===============================================================

GLOBAL      HANDLE                   ghInst;
GLOBAL      HWND                     ghWnd;

GLOBAL      LPDIRECTDRAW             glpDirectDraw;  // COM DirectDraw object
GLOBAL      LPDIRECTDRAWSURFACE      glpFrontBuffer; // Pointer to front drawing buffer
GLOBAL      LPDIRECTDRAWSURFACE      glpBackBuffer;  // Pointer to back drawing buffer

GLOBAL      LPSPRITEHIGHCOMP         glpMasterSprite;
GLOBAL      LPDIRECTDRAWPALETTE      glpPalette;

GLOBAL      LPDIRECTSOUNDOBJECT      glpDirectSound;
GLOBAL      LPDIRECTSOUNDWAVE        glpSoundFire;
GLOBAL      LPDIRECTSOUNDWAVE        glpSoundExplosion;
GLOBAL      LPDIRECTSOUNDWAVE        glpSoundThrust;
GLOBAL      LPDIRECTSOUNDWAVE        glpSoundBackground;

GLOBAL      BOOL                     gbGameLoop;

GLOBALCHAR         (szAppName[],"WINDONUT"              );
GLOBALCHAR         (szCaption[],"Donuts for Windows" );
