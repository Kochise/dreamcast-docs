/*
	Ninja Library
	
	COPYRIGHT (C) SEGA ENTERPRISES,LTD.
*/

#ifndef _NINJA_STR_H_
#define _NINJA_STR_H_

typedef Sint8 NJS_SYS_ATTR[NJD_SYS_ATTR_SIZE];

typedef void (*NJS_INT_FUNC)(void);

typedef struct{
	Uint32 NativeLimit;
	Uint32 NativeCurrent;
	Uint32 NativePeak;
	Uint32 InternalVertexBufSize[5];
	Uint32 MaxVertexBufSize[5];
	Uint32 LastTATime;
	Uint32 LastRenderTime;
	Uint32 CurrentVertexBufSize[5];
	Uint32 reserved0;
	Uint32 reserved1;
	Uint32 reserved2;
	Uint32 reserved3;
	Uint32 reserved4;
	Uint32 reserved5;
	Uint32 reserved6;
	Uint32 reserved7;
	Uint32 reserved8;
	Uint32 reserved9;
	Uint32 reserved10;
	Uint32 reserved11;
} NJS_SYSTEMINFO;

typedef struct {
	Sint16  u;
	Sint16  v;
} NJS_TEX;

typedef	struct {
	Uint8   b;
	Uint8   g;
	Uint8   r;
	Uint8   a;
} NJS_BGRA;

typedef union {
	Uint32  color;
	NJS_TEX tex;
	NJS_BGRA argb;
} NJS_COLOR;

typedef struct {
	Float   a;
	Float   r;
	Float   g;
	Float   b;
} NJS_ARGB;

typedef struct {
	Sint16  x;
	Sint16  y;
} NJS_POINT2I;

typedef struct {
	Float  x;
	Float  y;
} NJS_POINT2;

typedef struct {
	Float   x;
	Float   y;
	Float   z;
} NJS_POINT3, NJS_VECTOR;

typedef struct {
	NJS_POINT2  *p;
	NJS_COLOR   *col;
    NJS_COLOR   *tex;
    Uint32      num;
} NJS_POINT2COL;

typedef struct {
	NJS_POINT3  *p;
	NJS_COLOR   *col;
    NJS_COLOR   *tex;
    Uint32      num;
} NJS_POINT3COL;

typedef struct {
	Float   px,py,pz;
	Float   vx,vy,vz;
} NJS_LINE, NJS_PLANE, NJS_PVECTOR;


/* コリジョン用構造体追加 */
typedef struct{
    NJS_POINT3 c;
    Float      r;
} NJS_SPHERE;

typedef struct{
    NJS_POINT3 c1;
    NJS_POINT3 c2;
    Float      r;
} NJS_CAPSULE;

typedef struct{
    NJS_POINT3 v[8];
} NJS_BOX;

typedef struct{
    NJS_POINT3 v[4];
} NJS_RECT;
/* 追加終わり */


typedef struct {
	NJS_MATRIX m;
	Float   px,py,pz;
	Float   vx,vy,vz;
	Angle   roll;
	Float   apx,apy,apz;
	Float   avx,avy,avz;
	Angle   aroll;
} NJS_VIEW;

typedef struct {
	Float   dist;
	Float   w,h;
	Float   cx,cy;
} NJS_SCREEN;


/*--------------------------------------*/
/*      Texture Structure               */
/*--------------------------------------*/
typedef struct{
	Uint32 Type;
	Uint32 BitDepth;
	Uint32 PixelFormat;
	Uint32 nWidth;
	Uint32 nHeight;
	Uint32 TextureSize;
	Uint32 fSurfaceFlags;
	Uint32 *pSurface;
	Uint32 *pVirtual;
	Uint32 *pPhysical;
}NJS_TEXSURFACE;
	
typedef struct{
	void*			   texaddr; /* texture address   			*/
	NJS_TEXSURFACE	texsurface;	/* texture surface 				*/
} NJS_TEXINFO;

typedef struct {
	void            *filename;  /* texture filename strings     */
	Uint32               attr;  /* texture attribute            */
	Uint32            texaddr;  /* texture memory list address  */
} NJS_TEXNAME;

typedef struct {
	NJS_TEXNAME     *textures;  /* texture array                */
	Uint32          nbTexture;  /* texture count                */
} NJS_TEXLIST;

typedef struct {
	Uint32			globalIndex;/* global unique texture ID     */
	Uint32			bank;		/* palette bank 				*/
	Uint32			tspparambuffer;/* TSPParambuffer			*/
	Uint32			texparambuffer;/* TextureParambuffer		*/
	Uint32			texaddr;	/* texture flag					*/
	NJS_TEXINFO		texinfo;	/* texinfo						*/
	Uint16			count;		/* texture count  				*/
	Uint16			dummy;
} NJS_TEXMEMLIST;

typedef struct {
	void 			*palette;	/*	palette pointer				*/
	Uint16 			mode;		/*	color mode					*/
	Sint16 			bank;		/*	bank						*/
	Sint16 			offset;		/*	entry offset				*/
	Sint16 			count;		/*	entry count					*/
}NJS_TEXPALETTE;

typedef struct {
	Uint32	n;
	Uint32	globalIndex;
	Sint32	texerr;
	Sint32	gdstat;
	Sint32	gderr;
	Sint32	reserved0;
	Sint32	reserved1;
	Sint32	reserved2;
}NJS_TEXERRSTAT;

typedef struct{
	Uint32 nTextureType;
	Uint16 nWidth;
	Uint16 nHeight;
}NJS_PVRHEADERDATA;

/*--------------------------------------*/
/*      Model Structure                 */
/*--------------------------------------*/
/*
 * NJS_MODEL
 */
typedef struct {
	NJS_COLOR         diffuse;
	NJS_COLOR        specular;
	Float            exponent;
	Uint32         attr_texId;  /* attribute and texture ID in texlist        */
    Uint32          attrflags;  /* attribute flags */
} NJS_MATERIAL;

typedef struct {
	Uint16          type_matId; /* meshset type and attr index
								   14-15 : meshset type bits
									0-13 : material id(0-4095)  */
	Uint16          nbMesh;     /* mesh count                   */
	Sint16          *meshes;    /* mesh array                   */
	Uint32          *attrs;     /* attribure                    */
    NJS_VECTOR      *normals;   /* mesh normal list             */
	NJS_COLOR       *vertcolor; /* polygon vertex color list    */
	NJS_COLOR       *vertuv;    /* polygon vertex uv list       */
} NJS_MESHSET;

typedef struct {
	NJS_POINT3      *points;    /* vertex list                  */
	NJS_VECTOR      *normals;   /* vertex normal list           */
	Sint32          nbPoint;    /* vertex count                 */
	NJS_MESHSET     *meshsets;  /* meshset list                 */
	NJS_MATERIAL    *mats;      /* material list                */
	Uint16          nbMeshset;  /* meshset count                */
    Uint16          nbMat;      /* material count               */
	NJS_POINT3      center;     /* model center                 */
	Float			r;			/* ??????????? */
} NJS_MODEL;

/*
 * NJS_OBJECT
 */
typedef struct obj {
    Uint32          evalflags;  /* evalation flags              */
	NJS_MODEL       *model;     /* model data pointer           */
	Float           pos[3];     /* translation                  */
	Angle           ang[3];     /* rotation                     */
	Float           scl[3];     /* scaling                      */
	struct obj      *child;     /* child object                 */
	struct obj      *sibling;   /* sibling object               */
} NJS_OBJECT;

/*
 * NJS_MOTION
 */
/* key frame animation */
typedef struct {
	Uint32          keyframe;
	Float           key[3];
} NJS_MKEY_F;

typedef struct {
	Uint32          keyframe;
	Angle           key[3];     /* angle                        */
} NJS_MKEY_A;

typedef struct {
	Uint32          keyframe;
	Angle           angle;      /* angle                        */
	Float           axe[3];     /* axe vector                   */
} NJS_MKEY_AX;

typedef struct 
{
	Uint32          keyframe;
	void            *key;        /* pointer                     */
} NJS_MKEY_P;

typedef struct {
	Uint32          keyframe;
	Float           key;
} NJS_MKEY_F1;

typedef struct {
	Uint32          keyframe;
	Float           key[2];
} NJS_MKEY_F2;

typedef struct {
	Uint32          keyframe;
	Float           nrang;
	Float           frang;
	Angle           iang;
	Angle           oang;
} NJS_MKEY_SPOT;

typedef struct {
	Uint32          keyframe;
	Uint32          key;
} NJS_MKEY_UI32;

typedef struct {
	Uint32          keyframe;
	Sint32          key;
} NJS_MKEY_SI32, NJS_MKEY_A1;

typedef struct {
    Uint32          keyframe;
    Float           key[4];
} NJS_MKEY_QUAT;

/*
 * NJS_MDATA
 */
/* 1 factor : pos or ang or scl or shape or vec */
typedef struct {
	void            *p[1];      /* factor pointer               */
	Uint32          nb[1];      /* factor count                 */
} NJS_MDATA1;

/* 2 factors : pos and ang, pos and vec(light motion), etc      */
typedef struct {
	void            *p[2];      /* factor pointer               */
	Uint32          nb[2];      /* factor count                 */
} NJS_MDATA2;

/* 3 factors : pos and ang and scl, pos and ang and shape, etc  */
typedef struct {
	void            *p[3];      /* factor pointer               */
	Uint32          nb[3];      /* factor count                 */
} NJS_MDATA3;

/* 4 factors : pos and ang and scl and shape, etc               */
typedef struct {
	void            *p[4];      /* factor pointer               */
	Uint32          nb[4];      /* factor count                 */
} NJS_MDATA4;

/* 5 factors : etc               */
typedef struct {
	void            *p[5];      /* factor pointer               */
	Uint32          nb[5];      /* factor count                 */
} NJS_MDATA5;

typedef struct {
	void            *mdata;     /* NJS_MDATA array              */
	Uint32          nbFrame;    /* frame count                  */
	Uint16          type;       /* motion type  NJD_MTYPE_...   */
	Uint16          inp_fn;     /* interpolation & factor count */
} NJS_MOTION;

typedef struct {
	NJS_OBJECT      *object;    /* Object Tree top pointer      */
	NJS_MOTION      *motion;    /* motion                       */
#if 0
	NJS_TEXLIST     *texlist;   /* current texture list         */
#endif
} NJS_ACTION;

typedef struct
{
	NJS_MOTION		*motion[2];		/* motion's pointers */
	Float			frame[2];		/* current frames */
} NJS_MOTION_LINK;

typedef struct
{
	NJS_OBJECT		*object;		/* object's pointer */
	NJS_MOTION_LINK	*motionlink;	/* motion-link's pointer */
} NJS_ACTION_LINK;


/*
 * 3DLIB WORK BUFFER
 */
typedef union {
	Uint32		work;	/* work	*/
	Uint32		clip;	/* clip	*/

} NJS_CLIP_BUF;

typedef struct {
	NJS_CLIP_BUF a;			/* union			: 32		*/
	Float		sx,sy;		/* screen point		: 36 40		*/
	Float		oow;		/* 1/w				: 44		*/
	NJS_POINT3	point;		/* vertex point		:  0  4  8	*/
	Uint32		reserve;	/* clip				: 28		*/
	Float		u,v;		/* U, V				: 48 52		*/
	Float		inten[2];	/* Intensity		: 56 60		*/
	NJS_VECTOR	vector;		/* vertex normal	: 12 16 20	*/
	Uint32		flag;		/* flag				: 24		*/
} NJS_VERTEX_BUF;			/* TotalSize		: 64		*/

typedef struct {
	NJS_CLIP_BUF a;			/* union			: 4	*/
	Float		sx,sy;		/* screen point		:12	*/
	Float		oow;		/* 1/w				:16	*/
	NJS_POINT3	point;		/* vertex point		:44	*/
	Uint32		reserve;	/* clip				:64	*/
	NJS_ARGB	col;
	NJS_VECTOR	vector;		/* vertex normal	:56	*/
	Uint32		flag;		/* flag				:58	*/
} NJS_VERTEX_BUF2;			/* TotalSize		: 64		*/


typedef struct {
	NJS_CLIP_BUF a;			/* union			: 32		*/
	Float		sx,sy;		/* screen point		: 36 40		*/
	Float		oow;		/* 1/w				: 44		*/
	NJS_POINT3	point;		/* vertex point		:  0  4  8	*/
	Uint32		reserve;	/* clip				: 28		*/
	Float		u,v;		/* U, V				: 48 52		*/
	Float		inten[2];	/* Intensity		: 56 60		*/
	NJS_VECTOR	vector;		/* vertex normal	: 12 16 20	*/
	Uint32		flag;		/* flag				: 24		*/
} NJS_VERTEX_BUF_0;

typedef struct {
	NJS_CLIP_BUF a;			/* union			: 4	*/
	Float		sx,sy;		/* screen point		:12	*/
	Float		oow;		/* 1/w				:16	*/
	NJS_POINT3	point;		/* vertex point		:44	*/
	Uint32		reserve;	/* clip				:64	*/
	NJS_ARGB	col;
	NJS_VECTOR	vector;		/* vertex normal	:56	*/
	Uint32		flag;		/* flag				:58	*/
} NJS_VERTEX_BUF_1;

typedef struct {
	NJS_CLIP_BUF a;			/* union			: 4	*/
	Float		sx,sy;		/* screen point		:12	*/
	Float		oow;		/* 1/w				:16	*/
	Float		u,v;		/* U V				:24	*/
	Uint32		col[2];		/* pack col			:32	*/
	NJS_POINT3	point;		/* vertex point		:44	*/
	NJS_VECTOR	vector;		/* vertex normal	:56	*/
	Uint32		flag;		/* flag				:58	*/
	Uint32		reserve;	/* clip				:64	*/
} NJS_VERTEX_BUF_3;

typedef struct {
	NJS_CLIP_BUF a;			/* union			: 32		*/
	Float		sx,sy;		/* screen point		: 36 40		*/
	Float		oow;		/* 1/w				: 44		*/
	NJS_POINT3	point;		/* vertex point		:  0  4  8	*/
	Uint32		reserve;	/* clip				: 28		*/
	Float		u,v;		/* U, V				: 48 52		*/
	Float		inten[2];	/* Intensity		: 56 60		*/
	NJS_VECTOR	vector;		/* vertex normal	: 12 16 20	*/
	Uint32		flag;		/* flag				: 24		*/
} NJS_VERTEX_BUF_7;

typedef struct {
	NJS_VECTOR	vector;		/* vertex normal	:12	*/
	Uint32		clip;		/* clip				:16	*/
	Float		sx,sy;		/* screen point		:24	*/
	Float		oow;		/* 1/w				:28	*/
	Float		inten;		/* intensity		:32	*/
} NJS_VERTEX_BUF_X;


/*--------------------------------------*/
/*      Light Structure                 */
/*--------------------------------------*/
/*
 * NJS_LIGHT_CAL
 */
typedef struct
{
/*************/
	Float       ratten;         /* attenuation rate             */
	Float       ipd;		    /* inner product                */
/*************/
	Float       nrr;            /* limit judgment value         */
	Float       frr;            /* limit judgment value         */
	Float       cosi;           /* limit judgment value         */
	Float       cose;           /* limit judgment value         */
	Float		idev;           /* judgment value of devision   */
	Float		odev;           /* judgment value of devision   */
	Float       rate;           /* attenuation rate(calculated) */
	Float       intns;          /* Intensity (0-1)              */
	Int         exp;            /* exponent(SGI):material       */
/*************/
	Int         reserve;        /*                              */
/*************/
	NJS_POINT3  lpnt;           /* point vector                 */
	NJS_VECTOR  lvctr;          /* directional vector           */
/*************/
	NJS_VECTOR  lmvctr;         /* directional vector           */
/*************/
	NJS_ARGB    atten;          /* intns * argb                 */
	NJS_ARGB    amb;            /* iamb*atten                   */
	NJS_ARGB    dif;            /* idif*atten                   */
	NJS_ARGB    spc;            /* ispc*atten                   */
/*************/
	NJS_ARGB    mamb;           /* amb*material                 */
	NJS_ARGB    mdif;           /* dif*material                 */
	NJS_ARGB    mspc;           /* spc*material                 */
/*************/
} NJS_LIGHT_CAL, *NJS_LIGHT_CAL_PTR;

/*
 * NJS_LIGHT_ATTR
 */
typedef struct {
	Int             lsrc;       /* the kind of light source     */
	Float           iamb;       /* ambient's intensity          */
	Float           idif;       /* deffuse light's intensity    */
	Float           ispc;       /* specular light's intensity   */
	Float           nrang;      /* limit value (nearest)        */
	Float           frang;      /* limit value (farthest)       */
	void*           func;       /* the pointer of Callback func.*/
	Angle           iang;       /* limit value (inside)         */
	Angle           oang;       /* limit value (outside)        */
	NJS_ARGB        argb;       /* light's color                */
} NJS_LIGHT_ATTR, *NJS_LIGHT_ATTR_PTR;

/*
 * NJS_LIGHT
 */
typedef struct {
	NJS_MATRIX      mtrx;       /* matrix                       */
	NJS_POINT3      pnt;        /* point vector                 */
	NJS_VECTOR      vctr;       /* directional vector           */
	Int             stat;       /* status                       */
	Int             reserve;    /* reserve                      */
	NJS_LIGHT_CAL   ltcal;      /* calculation                  */
	NJS_LIGHT_ATTR  attr;       /* attribute                    */
} NJS_LIGHT, *NJS_LIGHT_PTR;

/*
 * NJS_LIGHT_MATERIAL
 */
typedef  struct {
	NJS_ARGB        ambient;    /* Ambient color from Material	*/
	NJS_ARGB        diffuse;    /* Diffuse color from Material	*/
	NJS_ARGB        specular;   /* Specular color from Material	*/
	Float           exponent;   /* Exponent from Material		*/
} NJS_LIGHT_MATERIAL;

/*
 * NJF_LIGHT_FUNC
 */
typedef void (*NJF_LIGHT_FUNC)(NJS_ARGB*, NJS_POINT3*, NJS_VECTOR*, NJS_LIGHT_PTR);

/*--------------------------------------*/
/*      Camera Structure                */
/*--------------------------------------*/

typedef struct {
	Float px, py, pz;
	Float vx, vy, vz;
	Angle roll;
	Angle ang;
	Float n_clip;
	Float f_clip;
	NJS_VECTOR lx,ly;
} NJS_CAMERA;

/*--------------------------------------*/
/*   Light & Camera Motion Structure    */
/*--------------------------------------*/

typedef struct {
	NJS_LIGHT	*light;
	NJS_MOTION	*motion;
} NJS_LACTION;

typedef struct {
	NJS_CAMERA	*camera;
	NJS_MOTION	*motion;
} NJS_CACTION;

typedef struct {
	Float	*pos;
	Angle	*ang;
	Float	*scl;
} NJS_MOTION_DATA;

typedef struct {
	Float	*pos;
	Float	*vect;
	Angle	*roll;
	Angle	*ang;
} NJS_CMOTION_DATA;

typedef struct {
	Float	*pos;
	Float	*vect;
	Float	*rgb;
	Float	*inten;
	Float 	*rang;
	Angle	*ang;
} NJS_LMOTION_DATA;

/*--------------------------------------*/
/*      Scroll Structure                */
/*--------------------------------------*/
/*
 * NJS_SCLATTR
 */
typedef Uint32 NJS_SCLATTR;     /* scroll attribute structure   */

/*
 * NJS_SCLMTRX
 */
typedef Float NJS_SCLMTRX[4];   /* scroll rotation matrix       */

/*
 *NJS_SCROLL
 */
typedef struct {
	Uint16      celps;          /* pixel size of the cells      */
	Uint16      mapw;           /* number of the width of map   */
	Uint16      maph;           /* number of the height of map  */
	Uint16      sw,sh;          /* size of the scroll draw      */
	NJS_TEXLIST* list;			/* texlist ID                   */
	Uint32      *map;           /* map array pointer            */
	Float       px,py;          /* scroll transration           */
	Float       bx,by;          /* map draw scroll              */
	Float       pr;             /* priority                     */
	Uint16      sflag;          /* scale flag                   */
	Float       sx,sy;          /* scale x,y                    */
	Float		spx,spy;		/* center of scale x,y			*/
	Uint16      mflag;          /* matrix flag                  */
	Float       cx,cy;          /* center of rotation x,y       */
	NJS_SCLMTRX m;              /* rotation matrix              */
	Uint32      colmode;        /* color mode                   */
	NJS_POINT2	clip[2];
	NJS_SCLATTR attr;           /* scroll attribute             */
	NJS_COLOR	sclc;
}NJS_SCROLL;

enum{
	_SM00,_SM01,
	_SM10,_SM11
};

/*--------------------------------------*/
/*      Sprite                          */
/*--------------------------------------*/
typedef struct {
	Sint16		sx,sy;			/* size				*/
	Sint16      cx,cy;          /* center           */
	Sint16      u1,v1;          /* upper left       */
	Sint16      u2,v2;          /* lower right      */
	Sint16      texid;          /* texture id       */
	Sint16      attr;           /* attribute        */
} NJS_TEXANIM;

typedef struct {
	NJS_POINT3  p;              /* point            */
	Float       sx,sy;          /* scale            */
	Angle       ang;            /* angle            */
	NJS_TEXLIST *tlist;         /* texture list     */
	NJS_TEXANIM *tanim;         /* animation list   */
} NJS_SPRITE;

/*--------------------------------------*/
/*      Low Level                       */
/*--------------------------------------*/

typedef struct {
	Float	x;
	Float	y;
	Float	z;
	Uint32	col;
} NJS_POLYGON_VTX;

typedef struct {
	Float	x;
	Float	y;
	Float	z;
	Float	u;
	Float	v;
	Uint32	col;
} NJS_TEXTURE_VTX;

typedef struct {
	Float	x;
	Float	y;
	Float	z;
	Float	u;
	Float	v;
	Uint32	bcol;
	Uint32	ocol;
} NJS_TEXTUREH_VTX;

/*--------------------------------------*/
/*      Math                            */
/*--------------------------------------*/
typedef struct {
	int		keys;			/* keyframes between two points which must be interpolated */
	int		*iparam;		/* attribute data (integer) */
	float	*fparam;		/* attribute data (float) */
} NJS_SPLINE;

typedef	struct {
	float	re;					/* real (or scalor) part of quaternion		*/
	float	im[3];				/* imaginary (or vector) part of quaternion	*/
} NJS_QUATERNION;


/*--------------------------------------*/
/*      Multi Pass                      */
/*--------------------------------------*/

typedef struct {
	Bool			bPreSort;
	Sint32			nSize[5];
} NJS_PASS_INFO;

typedef struct {
	Sint32			nNumOfMaxPass;
	NJS_PASS_INFO	sPassInfo[8];
} NJS_VERTEXBUFFER_INFO;


/*--------------------------------------*/
/*      Quad Draw                       */
/*--------------------------------------*/

typedef struct {
	Float	x1,y1,x2,y2;
	Float	u1,v1,u2,v2;
} NJS_QUAD_TEXTURE;

typedef struct {
	Float	x,y,z;
	Float	vx1,vy1;
	Float	vx2,vy2;
	Uint32	dmy;
	Float	u,v;
	Float	vu1,vv1;
	Float	vu2,vv2;
	Uint32	dmy2[2];
} NJS_QUAD_TEXTURE_EX;




#endif /* _NINJA_STR_H_ */
