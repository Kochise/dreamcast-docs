/*


    COPYRIGHT (C) SEGA ENTERPRISES,LTD.
*/

#ifndef _NINJA_PTCL_H_
#define _NINJA_PTCL_H_



void	njPtclPolygonStart( Uint32 col );
void	njPtclPolygonEnd( void );
void	njPtclDrawPolygon( NJS_POINT3 *p, Sint32 n, Float h );
void	njPtclDrawPolygon2( NJS_POINT3 *p, Sint32 n, Float h );

void	njPtclSpriteStart( Sint32 texid, Uint32 col, Sint32 flag );
void	njPtclSpriteEnd( void );
void	njPtclDrawSprite( NJS_POINT3 *p, Sint32 n, Float w, Float h );

void	njPtclStripStart( void );
void	njPtclStripEnd( void );
void	njPtclStrip( NJS_POINT3 *p, Uint32 col, Sint32 n );

void	njPtclDrawObject( NJS_CNK_OBJECT *obj, Float h );
Sint32	njPtclDrawModel( NJS_CNK_MODEL *model, Float h );

void	njPtclDrawMotion( NJS_CNK_OBJECT *object, NJS_MOTION *motion, Float frame, Float h );
void	njPtclDrawShapeMotion( NJS_CNK_OBJECT *object, NJS_MOTION *motion, NJS_MOTION *shape, Float frame, Float h );

#endif /* _NINJA_PTCL_H_ */

/*
 * End Of File
 */
