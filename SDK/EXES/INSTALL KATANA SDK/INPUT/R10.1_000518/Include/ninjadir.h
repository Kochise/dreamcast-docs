/*


    COPYRIGHT (C) SEGA ENTERSRISES,LTD.
*/

#ifndef _NINJA_DIR_H_
#define _NINJA_DIR_H_

typedef struct {
	Float		x,y,z;
	Float		r;
	void		*next;
	Uint32		nOP,nTR;
	Uint32		mode;					/* 0:normal 1:D8				*/
} NJS_DIRECT_HEAD;

typedef struct {
	Uint32		GP;
	Uint32		mode;					/* 0:normal 1:environment map	*/
	Float		sg,sb,sa,sr;
	Float		dg,db,da,dr;
	Uint32		TSPPARAM,TEXTUREADDR;
	Uint32		GLOBALPARAM,ISPPARAM;
	Uint32		num;
	Uint32		texid;
} NJS_DIRECT_GLOBAL;

typedef struct {
	Uint32		GP;
	Uint32		mode;
	Uint32		TSPPARAM,TEXTUREADDR;
	Uint32		GLOBALPARAM,ISPPARAM;
	Uint32		num;
	Uint32		texid;
} NJS_DIRECT_GLOBAL_D8;

typedef struct {
	Float		px,py,pz;
	Float		nz,nx,ny;
	Uint32		uv;
	Uint32		param;
} NJS_DIRECT_VERTEX;

typedef struct {
	Float		px,py,pz,one;
	Uint32		base,off;
	Uint32		param;
	Uint32		uv;
} NJS_DIRECT_VERTEX_D8;

typedef struct {
	Float		px,py,pz;
	Float		nx,ny,nz;
	Uint32		col;
	Uint32		dmy;
} NJS_DIRECT_BUF;

typedef struct {
	Float	x,y,z;
	Float	inten,ambient;
	Float	r,g,b;
} NJS_DIRECT_COMPILE_LIGHT;


void	njCnkDirectCullingMode( Uint32 mode );

void	*njCnkDirectObjectCompile( NJS_CNK_OBJECT *obj, void *ptr );
void	*njCnkDirectModelCompile( NJS_CNK_MODEL *model, void *ptr );

void	njCnkDirectVertexVN( Float *vlist, NJS_DIRECT_BUF *buf, Int num );
void	njCnkDirectVertexV( Float *vlist, NJS_DIRECT_BUF *buf, Int num );
void	njCnkDirectVertexVD8( Float *vlist, NJS_DIRECT_BUF *buf, Int num );
void	njCnkDirectVertexVND8( Float *vlist, NJS_DIRECT_BUF *buf, Int num );

void *njCnkDirectPolygon( Sint16 *plist, NJS_DIRECT_BUF *vbuf, Uint32 j, void *ptr, Uint32 *vtx );
void *njCnkDirectTexture( Sint16 *plist, NJS_DIRECT_BUF *vbuf, Uint32 j, void *ptr,  Float div, Uint32 *vtx );

void *njCnkDirectPolygonD8( Sint16 *plist, NJS_DIRECT_BUF *vbuf, Uint32 j, void *ptr, Uint32 *vtx );
void *njCnkDirectTextureD8( Sint16 *plist, NJS_DIRECT_BUF *vbuf, Uint32 j, void *ptr,  Float div, Uint32 *vtx );

void *njCnkDirectPolygonEnvD8( Sint16 *plist, NJS_DIRECT_BUF *vbuf, Uint32 j, void *ptr, Uint32 *vtx );
void *njCnkDirectTextureEnvD8( Sint16 *plist, NJS_DIRECT_BUF *vbuf, Uint32 j, void *ptr, Uint32 *vtx );

void	njDirectDrawObject( NJS_DIRECT_HEAD *model );

void	njSetDirectLight( Float x,Float y,Float z );
void	njSetDirectLightIntensity( Float inten, Float ambient );
void	njSetDirectLightColor( Float r, Float g, Float b );

void	njSetDirectClip();
Sint32	njDirectClip( Float *model, Float *clip );

void	*njCnkDirectModelCompileLight( NJS_CNK_MODEL *model, void *ptr, NJS_DIRECT_COMPILE_LIGHT *l );
void	*njCnkDirectObjectCompileLight( NJS_CNK_OBJECT *obj, void *ptr, NJS_DIRECT_COMPILE_LIGHT *l );

Uint32	njCnkDirectObjectCompileSize( NJS_CNK_OBJECT *obj );
Uint32	njCnkDirectModelCompileSize( NJS_CNK_MODEL *model );
Uint32	njCnkDirectModelCompileLightSize( NJS_CNK_MODEL *model );
Uint32	njCnkDirectObjectCompileLightSize( NJS_CNK_OBJECT *obj );


#endif /* _NINJA_DIR_H_ */

/*
 * End Of File
 */
