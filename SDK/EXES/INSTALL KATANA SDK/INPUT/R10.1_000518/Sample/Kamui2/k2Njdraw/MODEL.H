/*----------------------------------------------------------------------------------*/

#if !defined( __Model_H )
#define __Model_H

#ifdef __cplusplus
extern "C" {
#endif

/*----------------------------------------------------------------------------------*/

typedef struct {
	KMFLOAT		x;
	KMFLOAT		y;
	KMFLOAT		z;
} KG_POINT, *PKG_POINT;

typedef struct {
	KMFLOAT		x;
	KMFLOAT		y;
	KMFLOAT		z;
} KG_VECTOR, *PKG_VECTOR;

typedef struct {
	KMFLOAT		u;
	KMFLOAT		v;
} KG_TEXTURE, *PKG_TEXTURE;

typedef struct {
	KMWORD		u;
	KMWORD		v;
} KG_TEX, *PKG_TEX;

typedef struct {
	KMFLOAT		a;
	KMFLOAT		r;
	KMFLOAT		g;
	KMFLOAT		b;
} KG_COLOR, *PKG_COLOR;

typedef struct {
	KMBYTE		b;
	KMBYTE		g;
	KMBYTE		r;
	KMBYTE		a;
} KG_PACKED, *PKG_PACKED;

typedef struct {									/* 中間バッファ					*/
	KG_POINT	poi;								/* ワールド座標					*/
	KG_VECTOR	nor;								/* 法線							*/
	KG_TEXTURE	tex;								/* テクスチャ座標				*/
/*	KG_COLOR	base;*/								/* ベースカラー					*/
/*	KG_COLOR	offs;*/								/* オフセットカラー				*/
/*	KMDWORD		attr;*/								/* アトリビュート				*/
} KG_INTERNAL, *PKG_INTERNAL;

typedef struct {
	KG_PACKED	Diff;								/* 拡散光						*/
	KG_PACKED	Spec;								/* 反射光						*/
	KMFLOAT		Exp;								/* 反射率						*/
	KMDWORD		TexID;								/* テクスチャＩＤ				*/
	KMDWORD		Attr;								/* アトリビュート				*/
} KG_MATERIAL, *PKG_MATERIAL;

typedef struct {
	KMWORD		MaterialID;							/* マテリアルＩＤ				*/
	KMWORD		MeshNum;							/* メッシュ数					*/
	PKMWORD		Mesh;								/* メッシュ						*/
	PKMDWORD	attrs;								/* ポリゴンアトリビュート		*/
	PKG_VECTOR	normals;							/* ポリゴンノーマル				*/
	PKG_PACKED	vertcolor;							/* バーテックスカラー			*/
	PKMDWORD	vertuv;								/* バーテックスＵＶ				*/
} KG_MESH, *PKG_MESH;

typedef struct {
	PKG_POINT	PList;								/* 頂点リスト					*/
	PKG_VECTOR	PNormal;							/* 法線リスト					*/
	KMDWORD		PNum;								/* 頂点数						*/
	PKG_MESH	Mesh;								/* メッシュ						*/
	PKG_MATERIAL Material;							/* マテリアル					*/
	KMWORD		MeshNum;							/* メッシュ数					*/
	KMWORD		MaterialNum;						/* マテリアル数					*/
	KMFLOAT		Center[3];							/* 中心座標						*/
	KMFLOAT		Raduis;								/* 外接円径						*/
} KG_MODEL, *PKG_MODEL;

typedef struct _OBJECT_ {
	KMDWORD		Eval;
	PKG_MODEL	Model;
	KG_POINT	Position;
	KG_POINT	Angle;
	KG_POINT	Scale;
	struct _OBJECT_	*Child;
	struct _OBJECT_	*Sibling;
} KG_OBJECT, *PKG_OBJECT;

typedef struct {
	KG_VECTOR	vec;
	KMFLOAT		diff;
	KMFLOAT		spec;
	KMFLOAT		ambi;
} KG_LIGHT, *PKG_LIGHT;

typedef struct {
	PKMDWORD	pCurrentPtr[5];					/* Opaque, OpaqueModifier, .... Punch */
} KG_CURRNETPOINTER, *PKG_CURRNETPOINTER;

typedef struct {
	KMVOID            *filename;  /* texture filename strings     */
	KMDWORD           attr;  /* texture attribute            */
	KMDWORD           texaddr;  /* texture memory list address  */
} KG_TEXNAME, *PKG_TEXNAME;

typedef struct {
	KG_TEXNAME      *textures;  /* texture array                */
	KMDWORD          nbTexture;  /* texture count                */
} KG_TEXLIST, *PKG_TEXLIST;

typedef struct {
	KMSURFACEDESC	TextureSurface;
	KMDWORD			TSP;
	KMDWORD			TEX;
} KG_TEXTURESURFACE, *PKG_TEXTURESURFACE;

typedef struct {
	KMDWORD chunkname;
	KMDWORD	nSize;
	KMDWORD nTextureType;
	KMWORD	nWidth;
	KMWORD	nHeight;
} KG_TEXHEADER, *PKG_TEXHEADER;
/*----------------------------------------------------------------------------------*/
/* フラットモデル用																	*/

typedef enum {
	KG_LIST_OPAQUE	= 0,
	KG_LIST_OPAQUEM	= 1,
	KG_LIST_TRANS	= 2,
	KG_LIST_TRANSM	= 3,
	KG_LIST_PUNCH	= 4
} KG_LIST_TYPE;

typedef struct _FOBJ_ {
	KMDWORD			MeshNum;		/* 4	*/
	struct _FOBJ_	*Child;			/* 4	*/
	struct _FOBJ_	*Sibling;		/* 4	*/
	float			cx,cy,cz;		/* 12	*/
	float			r;				/* 4	*/
	KMDWORD			pad;			/* 4	*/
} KG_FLATOBJECT, *PKG_FLATOBJECT;	/* 32	*/

typedef struct {
	KG_LIST_TYPE	ListType;		/* 4	*/
	KMDWORD			TCW;			/* 4	*/
	KMDWORD			TSP;			/* 4	*/
	KMDWORD			ISP;			/* 4	*/
	KMDWORD			PCW;			/* 4	*/
	KMDWORD			VtxNum;			/* 4	*/
	KMDWORD			pad[2];			/* 8	*/
} KG_FLATGLOBAL, *PKG_FLATGLOBAL;	/* 32	*/

typedef struct {
	KMDWORD			PCW;			/* 4	*/
	float			vx,vy,vz;		/* 12	*/
	float			nx,ny,nz;		/* 12	*/
	float			tu,tv;			/* 8	*/
	float			a,r,g,b;		/* 16	*/
	float			pad[3];			/* 12	*/
} KG_FLATVERTEX, *PKG_FLATVERTEX;	/* 64	*/

typedef struct {
	float			LightVec[3];	/* Light Vector X, Y, Z */
	float			Intensity;		/* Intensity */
	float			Ambient;		/* Ambient */
	float			ScreenXRatio;	/* Screen distance * Aspect X */
	float			ScreenYRatio;	/* Screen distance * Aspect X */
	float			ScreenCenterX;	/* Screen Center X */
	float			ScreenCenterY;	/* Screen Center Y */
}NJDIRECTVERTEXINFO, *PNJDIRECTVERTEXINFO;

typedef struct {
	float			vx, vy, vz;		/* Vertex Point */
	float			nz, nx, ny;		/* Normal */
	KMDWORD			UV;				/* 16bit Packed UV */
	KMDWORD			PCW;
}NJDIRECTVERTEX, *PNJDIRECTVERTEX;

KMVOID kgBasicToFlat(
	PKMVOID pBuffer,
	PKG_OBJECT pBasic ,
	PKG_TEXTURESURFACE pTexSurface,
	KMINT32 mode
);

typedef struct _FOBJ2_ {
	KMFLOAT			cx,cy,cz;		/* 12	*/
	KMFLOAT			r;				/* 4	*/
	KMDWORD			OpaqueNum;		/* 4	*/
	KMDWORD			TransNum;		/* 4	*/
	struct _POBJ2_	*Next;			/* 4	*/
	KMFLOAT			pad;			/* 4	*/
} KG_FLAT2OBJECT, *PKG_FLAT2OBJECT;	/* 32	*/

typedef struct {
	KMFLOAT			og,ob;			/* 8	*/
	KMFLOAT			oa,or;			/* 8	*/
	KMFLOAT			bg,bb;			/* 8	*/
	KMFLOAT			ba,br;			/* 8	*/
	KMDWORD			TSP,TCW;		/* 4	*/
	KMDWORD			PCW,ISP;		/* 4	*/
	KMDWORD			VtxNum;			/* 4	*/
	KMDWORD			pad[3];			/* 12	*/
} KG_FLAT2GLOBAL, *PKG_FLAT2GLOBAL;	/* 64	*/

typedef struct {
	KMFLOAT			vx,vy;			/* 8	*/
	KMFLOAT			vz,nz;			/* 8	*/
	KMFLOAT			nx,ny;			/* 8	*/
	KMDWORD			uv16;			/* 4	*/
	KMDWORD			param;			/* 4	*/
} KG_FLAT2VERTEX, *PKG_FLAT2VERTEX;	/* 32	*/
/*----------------------------------------------------------------------------------*/
#ifdef __cplusplus
}
#endif
#endif
