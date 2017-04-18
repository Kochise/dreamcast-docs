/*--------------*/
/* TEXTURE      */
/*--------------*/

#define TEXN(_texname)     {(_texname), 0x0, 0}
#define TEXN3(_texname, _attr, _texaddr) {(_texname), _attr, _texaddr}
#define TEXTURE_START
#define TEXTURENAME         KG_TEXNAME
#define TEXTURELIST         KG_TEXLIST
#define NO_TEXTURE          0
#define TEXTURE_END
#define TextureList
#define TextureNum


/*--------------*/
/* cast OBJTYPE */
/*--------------*/
#define _OBJPOINTERTYPE (PKG_OBJECT)


/*-----------*/
/* Start/End */
/*-----------*/
/* Basic/Chunk */
#define START          ={
#define END            };

/*----*/
/* Uv */
/*----*/
/* Basic */
#define UV( _u, _v) (((((long)(_v))<<16)&0xffff0000)|((long)(_u))& 0x0000ffff)


/*-------*/
/* Angle */
/*-------*/
/* Basic/Chunk */
#define _NJAVAL             (65536.0F/360.0000F)
#define _NJANG1(_a) (long)(_NJAVAL*(_a))
#define _NJANG( _x, _y, _z)                               \
    {(long)(_NJAVAL*(_x)), (long)(_NJAVAL*(_y)), (long)(_NJAVAL*(_z))}

/*------*/
/* ARGB */
/*------*/
/* Basic/Chunk */
#define _ARGB( _a, _r, _g, _b)                                           \
                ( (unsigned long)((_a)<<24)|(unsigned long)((_r)<<16)    \
                 |(unsigned long)((_g)<<8)|(_b) )
#define ARGB( _a, _r, _g, _b) _ARGB( _a, _r, _g, _b)
#define _NJARGB( _a, _r, _g, _b) _ARGB( _a, _r, _g, _b)

/*----------*/
/* Material */
/*----------*/
/* Basic */
#define MATERIAL            KG_MATERIAL
#define MATSTART           {

#define Diffuse( _a, _r, _g, _b)  {_b, _g, _r, _a}
#define Specular( _a, _r, _g, _b) {_b, _g, _r, _a}
#define Exponent( _exp)           (_exp)
#define AttrTexId( _attr, _tid)   ((_attr)|(_tid))
#define AttrFlags( _atf)          ((_atf))

#define MATEND             },


/*--------*/
/* Vertex */
/*--------*/
/* Basic/Chunk */
#define VERT( _x, _y, _z)   (_x), (_y), (_z)
#define NORM( _x, _y, _z)   (_x), (_y), (_z)
#define POINT		    KG_POINT
#define NORMAL		    KG_VECTOR

/*---------*/
/* Polygon */
/*---------*/
/* Basic */
#define POLYGON              KMWORD

/*-------*/
/* Strip */
/*-------*/
/* Basic */
#define Strip( _flag, _len) ((_flag)|(_len))

/*---------------*/
/* PolygonNormal */
/*---------------*/
/* Basic */
#define POLYNORMAL          KG_VECTOR
#define STRIPNORMAL         KG_VECTOR

#define PNORM( _x, _y, _z)  (_x), (_y), (_z)

/*-------------*/
/* VertexColor */
/*-------------*/
/* Basic */
#define VERTCOLOR           KG_PACKED

/*----------*/
/* VertexUv */
/*----------*/
/* Basic */
#define VERTUV              KMDWORD

/*---------*/
/* Meshset */
/*---------*/
/* Basic */
#define MESHSET             KG_MESH
#define MESHSTART           {
#define MESHEND             },

#define TypeMatId(_type, _mid) ((_type)|(_mid))
#define MeshNum
#define Meshes
#define PolyAttrs
#define PolyNormal
#define VertColor
#define VertUV

/*-------*/
/* Model */
/*-------*/
/* Basic/Chunk */
#define Center
#define Radius

/* Basic */
#define MODEL                KG_MODEL
#define Model

#define Points
#define Normal
#define Meshset
#define PointNum
#define MeshsetNum
#define Materials
#define MatNum

#define VList
#define PList
#define VLIST                KMDWORD
#define PLIST                KMWORD

/*--------*/
/* Object */
/*--------*/
/* Basic */
#define OBJECT               KG_OBJECT

#define OBJECT_START
#define OBJECT_END

#define EvalFlags( _ef)        (_ef)
#define Position( _x, _y, _z)  (_x), (_y), (_z)
#define Angle( _x, _y, _z)     _NJANG(_x, _y, _z)
#define Scale( _x,  _y,  _z)   (_x), (_y), (_z)
#define Child               _OBJPOINTERTYPE
#define Sibling             _OBJPOINTERTYPE

#define OPosition(_x, _y, _z)  (_x), (_y), (_z)
#define OAngle(_x, _y, _z)     _NJANG(_x, _y, _z)
#define OScale(_x, _y, _z)     (_x), (_y), (_z)


/* Basic/Chunk */
#define DEFAULT_START
#define DEFAULT_END

#define iff_NJINFO  'NJIN'     /* data infomation             */

#define iff_NJCM    'NJCM'     /* ninja chunk model tree      */
#define iff_NJBM    'NJBM'     /* ninja basic model tree      */
#define iff_NJTL    'NJTL'     /* ninja texlist               */
#define iff_NJLI    'NJLI'     /* ninja light                 */ 
#define iff_NJCA    'NJCA'     /* ninja camera                */ 

#define iff_NMDM    'NMDM'     /* ninja model motion          */ 
#define iff_NLIM    'NLIM'     /* ninja light motion          */ 
#define iff_NCAM    'NCAM'     /* ninja camera motion         */ 
#define iff_NSSM    'NSSM'     /* ninja simple shape motion   */ 

#define iff_NJAD    'NJAD'     /* absolute address            */
#define iff_POF0    'POF0'     /* pointer offset list type 0  */ 
#define iff_POF1    'POF1'     /* pointer offset list type 1  */ 

/*
 * texture chunk name
 */
/* pvr */
#define iff_PVRT    'PVRT'     /* PowerVR texture             */ 
#define iff_GBIX    'GBIX'     /* globalIndex                 */ 
#define iff_PVRI    'PVRI'     /* texture Info                */ 

/* pvm */
#define iff_PVMH    'PVMH'     /* PVM hedder                  */ 
#define iff_COMM    'COMM'     /* Comment                     */ 
#define iff_CONV    'CONV'     /* PVM Converter               */ 
#define iff_MDLN    'MDLN'     /* model name                  */ 
#define iff_IMGC    'IMGC'     /* Image Container             */ 

/*--------------------------------------*/
/*      Binary Read define                */
/*--------------------------------------*/
#define NJD_POF_TYPE_PAD   0x00
#define NJD_POF_TYPE_CHAR  0x40
#define NJD_POF_TYPE_SHORT 0x80
#define NJD_POF_TYPE_LONG  0xc0
#define NJD_POF_CHAR_MASK  0xc0
#define NJD_POF_DATA_MASK  0x3f

