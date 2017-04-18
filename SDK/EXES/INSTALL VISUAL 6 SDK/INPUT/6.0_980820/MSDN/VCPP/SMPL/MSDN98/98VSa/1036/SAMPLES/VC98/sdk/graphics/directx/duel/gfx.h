/*==========================================================================
 *
 *  Copyright (C) 1995-1997 Microsoft Corporation. All Rights Reserved.
 *
 *  File:		gfx.h
 *  Content:	graphics routines include file
 *
 *
 ***************************************************************************/
#include "duel.h"
#include "ddraw.h"

/*
 * Prototypes
 */
BOOL	InitGraphics( void );
void	CleanupGraphics(void);
void    bltSplash( LPRECT );
void    bltScore( char *num, int x, int y );
void    bltObject( int x, int y, LPDIRECTDRAWSURFACE surf, LPRECT src, DWORD flags );
void	EraseScreen( void );
void	FlipScreen( void );
BOOL	RestoreSurfaces( void );
void	SetGamePalette(void);
void	FlipToGDI(void);

