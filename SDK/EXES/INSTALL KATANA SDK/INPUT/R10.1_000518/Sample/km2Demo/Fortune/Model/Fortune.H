/**********************************************************
 * This file has been created with the PowerVR Exporter v2.0
 * 3DStudio MAX R2  plug-in
 *
 * Date: 16.8.99   Time: 16:03
 * Original File: Fortune.max 
 *
 * Options: 
 *
 *   Meshes        = ON
 *   Materials     = ON
 *   Cameras       = OFF
 *   Lights        = OFF
 *   Paths         = OFF
 *   Animations    = OFF
 *
 *   UVs           = ON
 *   Normals       = ON
 *   Colors        = OFF
 *   Materials     = OFF
 *
 *   Strips        = ON
 *   No Face-list  = OFF
 *   DWORD List    = OFF
 *   Packed Format = OFF
 *
 **********************************************************/

#define STRUCT_MESH_DEFINED 

typedef struct { unsigned int      nNumVertex;
                 unsigned int      nNumFaces;
                 unsigned int      nNumStrips;
                 unsigned int      nFlags;
                 unsigned int      nMaterial;
                 float             fCenter[3];
                 float             *pVertex;
                 float             *pUV;
                 float             *pNormals;
                 float             *pPackedVertex;
                 unsigned int      *pVertexColor;
                 unsigned int      *pVertexMaterial;
                 unsigned short    *pFaces;
                 unsigned short    *pStrips;
                 unsigned short    *pStripLength;
               }   Struct_Mesh;


#define STRUCT_MATERIALS_DEFINED 

typedef struct { char     *sMatName;
                 char     *sAmbientFile;
                 char     *sDifusseFile;
                 char     *sSpecularFile;
                 char     *sShininessFile;
                 char     *sShinStrenghtFile;
                 char     *sSelfIlluminationFile;
                 char     *sOpacityFile;
                 char     *sFilterColorFile;
                 char     *sBumpFile;
                 char     *sReflectionFile;
                 char     *sRefractionFile;
                 unsigned nMatAmbientColor;
                 unsigned nMatDiffuseColor;
                 unsigned nMatSpecularColor;
                 float    fMatShininess;
                 float    fMatShineStrength;
                 float    fMatOpacity;
                 unsigned nMatShadingType;
               }   Struct_Material;


/**********************************************************
 * GENERAL DEFINITIONS
 **********************************************************/

#ifndef _NULL_
#define _NULL_ 0
#endif

#define NUM_MESHES     4
#define NUM_MATERIALS  29
#define NUM_LIGHTS     0
#define NUM_CAMERAS    0
#define NUM_PATHS       0

/* MESH FLAGS */
#ifndef MF_MATERIAL
#define MF_MATERIAL        1
#define MF_UV              2
#define MF_NORMALS         4
#define MF_VERTEXCOLOR     8
#define MF_VERTEXMATERIAL  16
#define MF_STRIPS          32
#define MF_NOFACELIST      64
#endif


/* MESHES */
#define M_CARD  0
#define M_CARDLIGHTMAP  1
#define M_CARDENVMAP  2
#define M_TABLE  3

/* MATERIALS */
#define Mt_CARD1  0
#define Mt_CARD2  1
#define Mt_CARD3  2
#define Mt_CARD4  3
#define Mt_CARD5  4
#define Mt_CARD6  5
#define Mt_CARD7  6
#define Mt_CARD8  7
#define Mt_CARD9  8
#define Mt_CARD10  9
#define Mt_CARD11  10
#define Mt_CARD12  11
#define Mt_CARD13  12
#define Mt_CARD14  13
#define Mt_CARD15  14
#define Mt_CARD16  15
#define Mt_CARD17  16
#define Mt_CARD18  17
#define Mt_CARD19  18
#define Mt_CARD20  19
#define Mt_CARD21  20
#define Mt_CARD22  21
#define Mt_CARD23  22
#define Mt_CARD24  23
#define Mt_CARD25  24
#define Mt_CARD26  25
#define Mt_LIGHTMAP  26
#define Mt_ENVMAP  27
#define Mt_TABLE  28


/**********************************************************
 * MATERIALS 
 **********************************************************/

Struct_Material 
   Material[NUM_MATERIALS] = {

/* MATERIAL 0 */
	/* Material Name  */ "Card1",
	/* Ambient        */ _NULL_,
	/* Difusse        */ "Card1.jpg",
	/* Specular       */ _NULL_,
	/* Shininess      */ _NULL_,
	/* ShinStrength   */ _NULL_,
	/* SelfIlluminat. */ _NULL_,
	/* Opacity        */ _NULL_,
	/* FilterColor    */ _NULL_,
	/* Bump           */ _NULL_,
	/* Reflection     */ _NULL_,
	/* Refraction     */ _NULL_,
	/* Ambient color  */ 0xff191919,
	/* Diffuse color  */ 0xff7f7f7f,
	/* Specular color */ 0xffe5e5e5,
	/* Shininess      */ 0.250000f,
	/* Shin strength  */ 0.050000f,
	/* Global Opacity */ 1.000000f,
	/* Shading type   */ 3,

/* MATERIAL 1 */
	/* Material Name  */ "Card2",
	/* Ambient        */ _NULL_,
	/* Difusse        */ "Card2.jpg",
	/* Specular       */ _NULL_,
	/* Shininess      */ _NULL_,
	/* ShinStrength   */ _NULL_,
	/* SelfIlluminat. */ _NULL_,
	/* Opacity        */ _NULL_,
	/* FilterColor    */ _NULL_,
	/* Bump           */ _NULL_,
	/* Reflection     */ _NULL_,
	/* Refraction     */ _NULL_,
	/* Ambient color  */ 0xff191919,
	/* Diffuse color  */ 0xff7f7f7f,
	/* Specular color */ 0xffe5e5e5,
	/* Shininess      */ 0.250000f,
	/* Shin strength  */ 0.050000f,
	/* Global Opacity */ 1.000000f,
	/* Shading type   */ 3,

/* MATERIAL 2 */
	/* Material Name  */ "Card3",
	/* Ambient        */ _NULL_,
	/* Difusse        */ "Card3.jpg",
	/* Specular       */ _NULL_,
	/* Shininess      */ _NULL_,
	/* ShinStrength   */ _NULL_,
	/* SelfIlluminat. */ _NULL_,
	/* Opacity        */ _NULL_,
	/* FilterColor    */ _NULL_,
	/* Bump           */ _NULL_,
	/* Reflection     */ _NULL_,
	/* Refraction     */ _NULL_,
	/* Ambient color  */ 0xff191919,
	/* Diffuse color  */ 0xff7f7f7f,
	/* Specular color */ 0xffe5e5e5,
	/* Shininess      */ 0.250000f,
	/* Shin strength  */ 0.050000f,
	/* Global Opacity */ 1.000000f,
	/* Shading type   */ 3,

/* MATERIAL 3 */
	/* Material Name  */ "Card4",
	/* Ambient        */ _NULL_,
	/* Difusse        */ "Card4.jpg",
	/* Specular       */ _NULL_,
	/* Shininess      */ _NULL_,
	/* ShinStrength   */ _NULL_,
	/* SelfIlluminat. */ _NULL_,
	/* Opacity        */ _NULL_,
	/* FilterColor    */ _NULL_,
	/* Bump           */ _NULL_,
	/* Reflection     */ _NULL_,
	/* Refraction     */ _NULL_,
	/* Ambient color  */ 0xff191919,
	/* Diffuse color  */ 0xff7f7f7f,
	/* Specular color */ 0xffe5e5e5,
	/* Shininess      */ 0.250000f,
	/* Shin strength  */ 0.050000f,
	/* Global Opacity */ 1.000000f,
	/* Shading type   */ 3,

/* MATERIAL 4 */
	/* Material Name  */ "Card5",
	/* Ambient        */ _NULL_,
	/* Difusse        */ "Card5.jpg",
	/* Specular       */ _NULL_,
	/* Shininess      */ _NULL_,
	/* ShinStrength   */ _NULL_,
	/* SelfIlluminat. */ _NULL_,
	/* Opacity        */ _NULL_,
	/* FilterColor    */ _NULL_,
	/* Bump           */ _NULL_,
	/* Reflection     */ _NULL_,
	/* Refraction     */ _NULL_,
	/* Ambient color  */ 0xff191919,
	/* Diffuse color  */ 0xff7f7f7f,
	/* Specular color */ 0xffe5e5e5,
	/* Shininess      */ 0.250000f,
	/* Shin strength  */ 0.050000f,
	/* Global Opacity */ 1.000000f,
	/* Shading type   */ 3,

/* MATERIAL 5 */
	/* Material Name  */ "Card6",
	/* Ambient        */ _NULL_,
	/* Difusse        */ "Card6.jpg",
	/* Specular       */ _NULL_,
	/* Shininess      */ _NULL_,
	/* ShinStrength   */ _NULL_,
	/* SelfIlluminat. */ _NULL_,
	/* Opacity        */ _NULL_,
	/* FilterColor    */ _NULL_,
	/* Bump           */ _NULL_,
	/* Reflection     */ _NULL_,
	/* Refraction     */ _NULL_,
	/* Ambient color  */ 0xff191919,
	/* Diffuse color  */ 0xff7f7f7f,
	/* Specular color */ 0xffe5e5e5,
	/* Shininess      */ 0.250000f,
	/* Shin strength  */ 0.050000f,
	/* Global Opacity */ 1.000000f,
	/* Shading type   */ 3,

/* MATERIAL 6 */
	/* Material Name  */ "Card7",
	/* Ambient        */ _NULL_,
	/* Difusse        */ "Card7.jpg",
	/* Specular       */ _NULL_,
	/* Shininess      */ _NULL_,
	/* ShinStrength   */ _NULL_,
	/* SelfIlluminat. */ _NULL_,
	/* Opacity        */ _NULL_,
	/* FilterColor    */ _NULL_,
	/* Bump           */ _NULL_,
	/* Reflection     */ _NULL_,
	/* Refraction     */ _NULL_,
	/* Ambient color  */ 0xff191919,
	/* Diffuse color  */ 0xff7f7f7f,
	/* Specular color */ 0xffe5e5e5,
	/* Shininess      */ 0.250000f,
	/* Shin strength  */ 0.050000f,
	/* Global Opacity */ 1.000000f,
	/* Shading type   */ 3,

/* MATERIAL 7 */
	/* Material Name  */ "Card8",
	/* Ambient        */ _NULL_,
	/* Difusse        */ "Card8.jpg",
	/* Specular       */ _NULL_,
	/* Shininess      */ _NULL_,
	/* ShinStrength   */ _NULL_,
	/* SelfIlluminat. */ _NULL_,
	/* Opacity        */ _NULL_,
	/* FilterColor    */ _NULL_,
	/* Bump           */ _NULL_,
	/* Reflection     */ _NULL_,
	/* Refraction     */ _NULL_,
	/* Ambient color  */ 0xff191919,
	/* Diffuse color  */ 0xff7f7f7f,
	/* Specular color */ 0xffe5e5e5,
	/* Shininess      */ 0.250000f,
	/* Shin strength  */ 0.050000f,
	/* Global Opacity */ 1.000000f,
	/* Shading type   */ 3,

/* MATERIAL 8 */
	/* Material Name  */ "Card9",
	/* Ambient        */ _NULL_,
	/* Difusse        */ "Card9.jpg",
	/* Specular       */ _NULL_,
	/* Shininess      */ _NULL_,
	/* ShinStrength   */ _NULL_,
	/* SelfIlluminat. */ _NULL_,
	/* Opacity        */ _NULL_,
	/* FilterColor    */ _NULL_,
	/* Bump           */ _NULL_,
	/* Reflection     */ _NULL_,
	/* Refraction     */ _NULL_,
	/* Ambient color  */ 0xff191919,
	/* Diffuse color  */ 0xff7f7f7f,
	/* Specular color */ 0xffe5e5e5,
	/* Shininess      */ 0.250000f,
	/* Shin strength  */ 0.050000f,
	/* Global Opacity */ 1.000000f,
	/* Shading type   */ 3,

/* MATERIAL 9 */
	/* Material Name  */ "Card10",
	/* Ambient        */ _NULL_,
	/* Difusse        */ "Card10.jpg",
	/* Specular       */ _NULL_,
	/* Shininess      */ _NULL_,
	/* ShinStrength   */ _NULL_,
	/* SelfIlluminat. */ _NULL_,
	/* Opacity        */ _NULL_,
	/* FilterColor    */ _NULL_,
	/* Bump           */ _NULL_,
	/* Reflection     */ _NULL_,
	/* Refraction     */ _NULL_,
	/* Ambient color  */ 0xff191919,
	/* Diffuse color  */ 0xff7f7f7f,
	/* Specular color */ 0xffe5e5e5,
	/* Shininess      */ 0.250000f,
	/* Shin strength  */ 0.050000f,
	/* Global Opacity */ 1.000000f,
	/* Shading type   */ 3,

/* MATERIAL 10 */
	/* Material Name  */ "Card11",
	/* Ambient        */ _NULL_,
	/* Difusse        */ "Card11.jpg",
	/* Specular       */ _NULL_,
	/* Shininess      */ _NULL_,
	/* ShinStrength   */ _NULL_,
	/* SelfIlluminat. */ _NULL_,
	/* Opacity        */ _NULL_,
	/* FilterColor    */ _NULL_,
	/* Bump           */ _NULL_,
	/* Reflection     */ _NULL_,
	/* Refraction     */ _NULL_,
	/* Ambient color  */ 0xff191919,
	/* Diffuse color  */ 0xff7f7f7f,
	/* Specular color */ 0xffe5e5e5,
	/* Shininess      */ 0.250000f,
	/* Shin strength  */ 0.050000f,
	/* Global Opacity */ 1.000000f,
	/* Shading type   */ 3,

/* MATERIAL 11 */
	/* Material Name  */ "Card12",
	/* Ambient        */ _NULL_,
	/* Difusse        */ "Card12.jpg",
	/* Specular       */ _NULL_,
	/* Shininess      */ _NULL_,
	/* ShinStrength   */ _NULL_,
	/* SelfIlluminat. */ _NULL_,
	/* Opacity        */ _NULL_,
	/* FilterColor    */ _NULL_,
	/* Bump           */ _NULL_,
	/* Reflection     */ _NULL_,
	/* Refraction     */ _NULL_,
	/* Ambient color  */ 0xff191919,
	/* Diffuse color  */ 0xff7f7f7f,
	/* Specular color */ 0xffe5e5e5,
	/* Shininess      */ 0.250000f,
	/* Shin strength  */ 0.050000f,
	/* Global Opacity */ 1.000000f,
	/* Shading type   */ 3,

/* MATERIAL 12 */
	/* Material Name  */ "Card13",
	/* Ambient        */ _NULL_,
	/* Difusse        */ "Card13.jpg",
	/* Specular       */ _NULL_,
	/* Shininess      */ _NULL_,
	/* ShinStrength   */ _NULL_,
	/* SelfIlluminat. */ _NULL_,
	/* Opacity        */ _NULL_,
	/* FilterColor    */ _NULL_,
	/* Bump           */ _NULL_,
	/* Reflection     */ _NULL_,
	/* Refraction     */ _NULL_,
	/* Ambient color  */ 0xff191919,
	/* Diffuse color  */ 0xff7f7f7f,
	/* Specular color */ 0xffe5e5e5,
	/* Shininess      */ 0.250000f,
	/* Shin strength  */ 0.050000f,
	/* Global Opacity */ 1.000000f,
	/* Shading type   */ 3,

/* MATERIAL 13 */
	/* Material Name  */ "Card14",
	/* Ambient        */ _NULL_,
	/* Difusse        */ "Card14.jpg",
	/* Specular       */ _NULL_,
	/* Shininess      */ _NULL_,
	/* ShinStrength   */ _NULL_,
	/* SelfIlluminat. */ _NULL_,
	/* Opacity        */ _NULL_,
	/* FilterColor    */ _NULL_,
	/* Bump           */ _NULL_,
	/* Reflection     */ _NULL_,
	/* Refraction     */ _NULL_,
	/* Ambient color  */ 0xff191919,
	/* Diffuse color  */ 0xff7f7f7f,
	/* Specular color */ 0xffe5e5e5,
	/* Shininess      */ 0.250000f,
	/* Shin strength  */ 0.050000f,
	/* Global Opacity */ 1.000000f,
	/* Shading type   */ 3,

/* MATERIAL 14 */
	/* Material Name  */ "Card15",
	/* Ambient        */ _NULL_,
	/* Difusse        */ "Card15.jpg",
	/* Specular       */ _NULL_,
	/* Shininess      */ _NULL_,
	/* ShinStrength   */ _NULL_,
	/* SelfIlluminat. */ _NULL_,
	/* Opacity        */ _NULL_,
	/* FilterColor    */ _NULL_,
	/* Bump           */ _NULL_,
	/* Reflection     */ _NULL_,
	/* Refraction     */ _NULL_,
	/* Ambient color  */ 0xff191919,
	/* Diffuse color  */ 0xff7f7f7f,
	/* Specular color */ 0xffe5e5e5,
	/* Shininess      */ 0.250000f,
	/* Shin strength  */ 0.050000f,
	/* Global Opacity */ 1.000000f,
	/* Shading type   */ 3,

/* MATERIAL 15 */
	/* Material Name  */ "Card16",
	/* Ambient        */ _NULL_,
	/* Difusse        */ "Card16.jpg",
	/* Specular       */ _NULL_,
	/* Shininess      */ _NULL_,
	/* ShinStrength   */ _NULL_,
	/* SelfIlluminat. */ _NULL_,
	/* Opacity        */ _NULL_,
	/* FilterColor    */ _NULL_,
	/* Bump           */ _NULL_,
	/* Reflection     */ _NULL_,
	/* Refraction     */ _NULL_,
	/* Ambient color  */ 0xff191919,
	/* Diffuse color  */ 0xff7f7f7f,
	/* Specular color */ 0xffe5e5e5,
	/* Shininess      */ 0.250000f,
	/* Shin strength  */ 0.050000f,
	/* Global Opacity */ 1.000000f,
	/* Shading type   */ 3,

/* MATERIAL 16 */
	/* Material Name  */ "Card17",
	/* Ambient        */ _NULL_,
	/* Difusse        */ "Card17.jpg",
	/* Specular       */ _NULL_,
	/* Shininess      */ _NULL_,
	/* ShinStrength   */ _NULL_,
	/* SelfIlluminat. */ _NULL_,
	/* Opacity        */ _NULL_,
	/* FilterColor    */ _NULL_,
	/* Bump           */ _NULL_,
	/* Reflection     */ _NULL_,
	/* Refraction     */ _NULL_,
	/* Ambient color  */ 0xff191919,
	/* Diffuse color  */ 0xff7f7f7f,
	/* Specular color */ 0xffe5e5e5,
	/* Shininess      */ 0.250000f,
	/* Shin strength  */ 0.050000f,
	/* Global Opacity */ 1.000000f,
	/* Shading type   */ 3,

/* MATERIAL 17 */
	/* Material Name  */ "Card18",
	/* Ambient        */ _NULL_,
	/* Difusse        */ "Card18.jpg",
	/* Specular       */ _NULL_,
	/* Shininess      */ _NULL_,
	/* ShinStrength   */ _NULL_,
	/* SelfIlluminat. */ _NULL_,
	/* Opacity        */ _NULL_,
	/* FilterColor    */ _NULL_,
	/* Bump           */ _NULL_,
	/* Reflection     */ _NULL_,
	/* Refraction     */ _NULL_,
	/* Ambient color  */ 0xff191919,
	/* Diffuse color  */ 0xff7f7f7f,
	/* Specular color */ 0xffe5e5e5,
	/* Shininess      */ 0.250000f,
	/* Shin strength  */ 0.050000f,
	/* Global Opacity */ 1.000000f,
	/* Shading type   */ 3,

/* MATERIAL 18 */
	/* Material Name  */ "Card19",
	/* Ambient        */ _NULL_,
	/* Difusse        */ "Card19.jpg",
	/* Specular       */ _NULL_,
	/* Shininess      */ _NULL_,
	/* ShinStrength   */ _NULL_,
	/* SelfIlluminat. */ _NULL_,
	/* Opacity        */ _NULL_,
	/* FilterColor    */ _NULL_,
	/* Bump           */ _NULL_,
	/* Reflection     */ _NULL_,
	/* Refraction     */ _NULL_,
	/* Ambient color  */ 0xff191919,
	/* Diffuse color  */ 0xff7f7f7f,
	/* Specular color */ 0xffe5e5e5,
	/* Shininess      */ 0.250000f,
	/* Shin strength  */ 0.050000f,
	/* Global Opacity */ 1.000000f,
	/* Shading type   */ 3,

/* MATERIAL 19 */
	/* Material Name  */ "Card20",
	/* Ambient        */ _NULL_,
	/* Difusse        */ "Card20.jpg",
	/* Specular       */ _NULL_,
	/* Shininess      */ _NULL_,
	/* ShinStrength   */ _NULL_,
	/* SelfIlluminat. */ _NULL_,
	/* Opacity        */ _NULL_,
	/* FilterColor    */ _NULL_,
	/* Bump           */ _NULL_,
	/* Reflection     */ _NULL_,
	/* Refraction     */ _NULL_,
	/* Ambient color  */ 0xff191919,
	/* Diffuse color  */ 0xff7f7f7f,
	/* Specular color */ 0xffe5e5e5,
	/* Shininess      */ 0.250000f,
	/* Shin strength  */ 0.050000f,
	/* Global Opacity */ 1.000000f,
	/* Shading type   */ 3,

/* MATERIAL 20 */
	/* Material Name  */ "Card21",
	/* Ambient        */ _NULL_,
	/* Difusse        */ "Card21.jpg",
	/* Specular       */ _NULL_,
	/* Shininess      */ _NULL_,
	/* ShinStrength   */ _NULL_,
	/* SelfIlluminat. */ _NULL_,
	/* Opacity        */ _NULL_,
	/* FilterColor    */ _NULL_,
	/* Bump           */ _NULL_,
	/* Reflection     */ _NULL_,
	/* Refraction     */ _NULL_,
	/* Ambient color  */ 0xff191919,
	/* Diffuse color  */ 0xff7f7f7f,
	/* Specular color */ 0xffe5e5e5,
	/* Shininess      */ 0.250000f,
	/* Shin strength  */ 0.050000f,
	/* Global Opacity */ 1.000000f,
	/* Shading type   */ 3,

/* MATERIAL 21 */
	/* Material Name  */ "Card22",
	/* Ambient        */ _NULL_,
	/* Difusse        */ "Card22.jpg",
	/* Specular       */ _NULL_,
	/* Shininess      */ _NULL_,
	/* ShinStrength   */ _NULL_,
	/* SelfIlluminat. */ _NULL_,
	/* Opacity        */ _NULL_,
	/* FilterColor    */ _NULL_,
	/* Bump           */ _NULL_,
	/* Reflection     */ _NULL_,
	/* Refraction     */ _NULL_,
	/* Ambient color  */ 0xff191919,
	/* Diffuse color  */ 0xff7f7f7f,
	/* Specular color */ 0xffe5e5e5,
	/* Shininess      */ 0.250000f,
	/* Shin strength  */ 0.050000f,
	/* Global Opacity */ 1.000000f,
	/* Shading type   */ 3,

/* MATERIAL 22 */
	/* Material Name  */ "Card23",
	/* Ambient        */ _NULL_,
	/* Difusse        */ "Card23.jpg",
	/* Specular       */ _NULL_,
	/* Shininess      */ _NULL_,
	/* ShinStrength   */ _NULL_,
	/* SelfIlluminat. */ _NULL_,
	/* Opacity        */ _NULL_,
	/* FilterColor    */ _NULL_,
	/* Bump           */ _NULL_,
	/* Reflection     */ _NULL_,
	/* Refraction     */ _NULL_,
	/* Ambient color  */ 0xff191919,
	/* Diffuse color  */ 0xff7f7f7f,
	/* Specular color */ 0xffe5e5e5,
	/* Shininess      */ 0.250000f,
	/* Shin strength  */ 0.050000f,
	/* Global Opacity */ 1.000000f,
	/* Shading type   */ 3,

/* MATERIAL 23 */
	/* Material Name  */ "Card24",
	/* Ambient        */ _NULL_,
	/* Difusse        */ "Card24.jpg",
	/* Specular       */ _NULL_,
	/* Shininess      */ _NULL_,
	/* ShinStrength   */ _NULL_,
	/* SelfIlluminat. */ _NULL_,
	/* Opacity        */ _NULL_,
	/* FilterColor    */ _NULL_,
	/* Bump           */ _NULL_,
	/* Reflection     */ _NULL_,
	/* Refraction     */ _NULL_,
	/* Ambient color  */ 0xff191919,
	/* Diffuse color  */ 0xff7f7f7f,
	/* Specular color */ 0xffe5e5e5,
	/* Shininess      */ 0.250000f,
	/* Shin strength  */ 0.050000f,
	/* Global Opacity */ 1.000000f,
	/* Shading type   */ 3,

/* MATERIAL 24 */
	/* Material Name  */ "Card25",
	/* Ambient        */ _NULL_,
	/* Difusse        */ "Card25.jpg",
	/* Specular       */ _NULL_,
	/* Shininess      */ _NULL_,
	/* ShinStrength   */ _NULL_,
	/* SelfIlluminat. */ _NULL_,
	/* Opacity        */ _NULL_,
	/* FilterColor    */ _NULL_,
	/* Bump           */ _NULL_,
	/* Reflection     */ _NULL_,
	/* Refraction     */ _NULL_,
	/* Ambient color  */ 0xff191919,
	/* Diffuse color  */ 0xff7f7f7f,
	/* Specular color */ 0xffe5e5e5,
	/* Shininess      */ 0.250000f,
	/* Shin strength  */ 0.050000f,
	/* Global Opacity */ 1.000000f,
	/* Shading type   */ 3,

/* MATERIAL 25 */
	/* Material Name  */ "Card26",
	/* Ambient        */ _NULL_,
	/* Difusse        */ "Card26.jpg",
	/* Specular       */ _NULL_,
	/* Shininess      */ _NULL_,
	/* ShinStrength   */ _NULL_,
	/* SelfIlluminat. */ _NULL_,
	/* Opacity        */ _NULL_,
	/* FilterColor    */ _NULL_,
	/* Bump           */ _NULL_,
	/* Reflection     */ _NULL_,
	/* Refraction     */ _NULL_,
	/* Ambient color  */ 0xff191919,
	/* Diffuse color  */ 0xff7f7f7f,
	/* Specular color */ 0xffe5e5e5,
	/* Shininess      */ 0.250000f,
	/* Shin strength  */ 0.050000f,
	/* Global Opacity */ 1.000000f,
	/* Shading type   */ 3,

/* MATERIAL 26 */
	/* Material Name  */ "Lightmap",
	/* Ambient        */ _NULL_,
	/* Difusse        */ "Shadow.jpg",
	/* Specular       */ _NULL_,
	/* Shininess      */ _NULL_,
	/* ShinStrength   */ _NULL_,
	/* SelfIlluminat. */ _NULL_,
	/* Opacity        */ _NULL_,
	/* FilterColor    */ _NULL_,
	/* Bump           */ _NULL_,
	/* Reflection     */ _NULL_,
	/* Refraction     */ _NULL_,
	/* Ambient color  */ 0xff191919,
	/* Diffuse color  */ 0xff7f7f7f,
	/* Specular color */ 0xffe5e5e5,
	/* Shininess      */ 0.250000f,
	/* Shin strength  */ 0.050000f,
	/* Global Opacity */ 1.000000f,
	/* Shading type   */ 3,

/* MATERIAL 27 */
	/* Material Name  */ "EnvMap",
	/* Ambient        */ _NULL_,
	/* Difusse        */ "Reflect.jpg",
	/* Specular       */ _NULL_,
	/* Shininess      */ _NULL_,
	/* ShinStrength   */ _NULL_,
	/* SelfIlluminat. */ _NULL_,
	/* Opacity        */ _NULL_,
	/* FilterColor    */ _NULL_,
	/* Bump           */ _NULL_,
	/* Reflection     */ _NULL_,
	/* Refraction     */ _NULL_,
	/* Ambient color  */ 0xff191919,
	/* Diffuse color  */ 0xff7f7f7f,
	/* Specular color */ 0xffe5e5e5,
	/* Shininess      */ 0.250000f,
	/* Shin strength  */ 0.050000f,
	/* Global Opacity */ 1.000000f,
	/* Shading type   */ 3,

/* MATERIAL 28 */
	/* Material Name  */ "Table",
	/* Ambient        */ _NULL_,
	/* Difusse        */ "Table.jpg",
	/* Specular       */ _NULL_,
	/* Shininess      */ _NULL_,
	/* ShinStrength   */ _NULL_,
	/* SelfIlluminat. */ _NULL_,
	/* Opacity        */ _NULL_,
	/* FilterColor    */ _NULL_,
	/* Bump           */ _NULL_,
	/* Reflection     */ _NULL_,
	/* Refraction     */ _NULL_,
	/* Ambient color  */ 0xff191919,
	/* Diffuse color  */ 0xff7f7f7f,
	/* Specular color */ 0xffe5e5e5,
	/* Shininess      */ 0.250000f,
	/* Shin strength  */ 0.050000f,
	/* Global Opacity */ 1.000000f,
	/* Shading type   */ 3

	};  /* END OF MATERIAL DEFINITIONS */



/**********************************************************
 * MESHES DATA 
 **********************************************************/

/* MESH 0 */

#define card_NumVertex  4
#define card_NumFaces   2
#define card_NumStrips  1
#define card_Flags      0x00000027
#define card_Material   0

float card_Vertices[] = {
	35.0169f,0.3041f,50.1230f,  -34.8686f,0.3041f,50.1230f,  -34.8686f,0.3041f,-49.9674f,  35.0169f,0.3041f,-49.9674f,  
_NULL_ }; /* End of card_Vertices */

float card_UV[] = {
	0.4927f,1.0042f,-0.0018f,1.0042f,-0.0018f,0.0052f,0.4927f,0.0052f,
_NULL_ }; /* End of card_UV */

float card_Normals[] = {
	0.0000f,-1.0000f,0.0000f,  0.0000f,-1.0000f,0.0000f,  0.0000f,-1.0000f,0.0000f,  0.0000f,-1.0000f,0.0000f,  
_NULL_ }; /* End of card_Normals */

unsigned short card_Faces[] = {
	0,1,2,  2,3,0,  
_NULL_ }; /* End of card_Faces */

unsigned short card_Strips[] = {
	3,0,2,1,
_NULL_ }; /* End of card_pStrips */

unsigned short card_StripLength[] = {
	2,
_NULL_ }; /* End of card_pStripLength */


/* MESH 1 */

#define cardlightmap_NumVertex  4
#define cardlightmap_NumFaces   2
#define cardlightmap_NumStrips  1
#define cardlightmap_Flags      0x00000027
#define cardlightmap_Material   26

float cardlightmap_Vertices[] = {
	35.0171f,0.2879f,50.1230f,  -34.8684f,0.2879f,50.1230f,  -34.8684f,0.2879f,-49.9674f,  35.0171f,0.2879f,-49.9674f,  
_NULL_ }; /* End of cardlightmap_Vertices */

float cardlightmap_UV[] = {
	0.9995f,0.9995f,0.0005f,0.9995f,0.0005f,0.0005f,0.9995f,0.0005f,
_NULL_ }; /* End of cardlightmap_UV */

float cardlightmap_Normals[] = {
	0.0000f,-1.0000f,0.0000f,  0.0000f,-1.0000f,0.0000f,  0.0000f,-1.0000f,0.0000f,  0.0000f,-1.0000f,0.0000f,  
_NULL_ }; /* End of cardlightmap_Normals */

unsigned short cardlightmap_Faces[] = {
	0,1,2,  2,3,0,  
_NULL_ }; /* End of cardlightmap_Faces */

unsigned short cardlightmap_Strips[] = {
	3,0,2,1,
_NULL_ }; /* End of cardlightmap_pStrips */

unsigned short cardlightmap_StripLength[] = {
	2,
_NULL_ }; /* End of cardlightmap_pStripLength */


/* MESH 2 */

#define cardenvmap_NumVertex  4
#define cardenvmap_NumFaces   2
#define cardenvmap_NumStrips  1
#define cardenvmap_Flags      0x00000027
#define cardenvmap_Material   27

float cardenvmap_Vertices[] = {
	35.0171f,0.2700f,50.1230f,  -34.8684f,0.2700f,50.1230f,  -34.8684f,0.2700f,-49.9674f,  35.0171f,0.2700f,-49.9674f,  
_NULL_ }; /* End of cardenvmap_Vertices */

float cardenvmap_UV[] = {
	0.9995f,0.9995f,0.0005f,0.9995f,0.0005f,0.0005f,0.9995f,0.0005f,
_NULL_ }; /* End of cardenvmap_UV */

float cardenvmap_Normals[] = {
	0.0000f,-1.0000f,0.0000f,  0.0000f,-1.0000f,0.0000f,  0.0000f,-1.0000f,0.0000f,  0.0000f,-1.0000f,0.0000f,  
_NULL_ }; /* End of cardenvmap_Normals */

unsigned short cardenvmap_Faces[] = {
	0,1,2,  2,3,0,  
_NULL_ }; /* End of cardenvmap_Faces */

unsigned short cardenvmap_Strips[] = {
	3,0,2,1,
_NULL_ }; /* End of cardenvmap_pStrips */

unsigned short cardenvmap_StripLength[] = {
	2,
_NULL_ }; /* End of cardenvmap_pStripLength */


/* MESH 3 */

#define table_NumVertex  4
#define table_NumFaces   2
#define table_NumStrips  1
#define table_Flags      0x00000027
#define table_Material   28

float table_Vertices[] = {
	402.1795f,12.3554f,300.8123f,  -399.9596f,12.3554f,300.8123f,  -399.9596f,12.3554f,-302.3962f,  402.1795f,12.3554f,-302.3962f,  
_NULL_ }; /* End of table_Vertices */

float table_UV[] = {
	0.0000f,1.0000f,1.0000f,1.0000f,1.0000f,0.0000f,0.0000f,0.0000f,
_NULL_ }; /* End of table_UV */

float table_Normals[] = {
	0.0000f,-1.0000f,0.0000f,  0.0000f,-1.0000f,0.0000f,  0.0000f,-1.0000f,0.0000f,  0.0000f,-1.0000f,0.0000f,  
_NULL_ }; /* End of table_Normals */

unsigned short table_Faces[] = {
	0,1,2,  2,3,0,  
_NULL_ }; /* End of table_Faces */

unsigned short table_Strips[] = {
	3,0,2,1,
_NULL_ }; /* End of table_pStrips */

unsigned short table_StripLength[] = {
	2,
_NULL_ }; /* End of table_pStripLength */



/**********************************************************
 * MESHES 
 **********************************************************/

Struct_Mesh 
   Mesh[NUM_MESHES] = {

/* MESH 0 */
	/* NumVertex      */ card_NumVertex,
	/* NumFaces       */ card_NumFaces,
	/* NumStrips      */ card_NumStrips,
	/* Flags          */ card_Flags,
	/* Material       */ card_Material,
	/* Center         */  0.074140f, 0.304066f, 0.077789f,
	/* Vertices       */ (float *)card_Vertices,
	/* UV             */ (float *)card_UV,
	/* Normals        */ (float *)card_Normals,
	/* Packed Vertices*/ (float *)_NULL_,
	/* VertexColor    */ (unsigned int *)_NULL_,
	/* VertexMaterial */ (unsigned int *)_NULL_,
	/* Faces          */ (unsigned short *)card_Faces,
	/* Strips         */ (unsigned short *)card_Strips,
	/* StripLength    */ (unsigned short *)card_StripLength,

/* MESH 1 */
	/* NumVertex      */ cardlightmap_NumVertex,
	/* NumFaces       */ cardlightmap_NumFaces,
	/* NumStrips      */ cardlightmap_NumStrips,
	/* Flags          */ cardlightmap_Flags,
	/* Material       */ cardlightmap_Material,
	/* Center         */  0.074368f, 0.287877f, 0.077789f,
	/* Vertices       */ (float *)cardlightmap_Vertices,
	/* UV             */ (float *)cardlightmap_UV,
	/* Normals        */ (float *)cardlightmap_Normals,
	/* Packed Vertices*/ (float *)_NULL_,
	/* VertexColor    */ (unsigned int *)_NULL_,
	/* VertexMaterial */ (unsigned int *)_NULL_,
	/* Faces          */ (unsigned short *)cardlightmap_Faces,
	/* Strips         */ (unsigned short *)cardlightmap_Strips,
	/* StripLength    */ (unsigned short *)cardlightmap_StripLength,

/* MESH 2 */
	/* NumVertex      */ cardenvmap_NumVertex,
	/* NumFaces       */ cardenvmap_NumFaces,
	/* NumStrips      */ cardenvmap_NumStrips,
	/* Flags          */ cardenvmap_Flags,
	/* Material       */ cardenvmap_Material,
	/* Center         */  0.074368f, 0.270041f, 0.077789f,
	/* Vertices       */ (float *)cardenvmap_Vertices,
	/* UV             */ (float *)cardenvmap_UV,
	/* Normals        */ (float *)cardenvmap_Normals,
	/* Packed Vertices*/ (float *)_NULL_,
	/* VertexColor    */ (unsigned int *)_NULL_,
	/* VertexMaterial */ (unsigned int *)_NULL_,
	/* Faces          */ (unsigned short *)cardenvmap_Faces,
	/* Strips         */ (unsigned short *)cardenvmap_Strips,
	/* StripLength    */ (unsigned short *)cardenvmap_StripLength,

/* MESH 3 */
	/* NumVertex      */ table_NumVertex,
	/* NumFaces       */ table_NumFaces,
	/* NumStrips      */ table_NumStrips,
	/* Flags          */ table_Flags,
	/* Material       */ table_Material,
	/* Center         */  1.109985f, 12.355425f, -0.791958f,
	/* Vertices       */ (float *)table_Vertices,
	/* UV             */ (float *)table_UV,
	/* Normals        */ (float *)table_Normals,
	/* Packed Vertices*/ (float *)_NULL_,
	/* VertexColor    */ (unsigned int *)_NULL_,
	/* VertexMaterial */ (unsigned int *)_NULL_,
	/* Faces          */ (unsigned short *)table_Faces,
	/* Strips         */ (unsigned short *)table_Strips,
	/* StripLength    */ (unsigned short *)table_StripLength

	}; /* End of Meshes *//**********************************************************
 * DEFINITIONS
 **********************************************************/



/**********************************************************
 * TEXTURES DATA 
 **********************************************************/


/**********************************************************
 * TEXTURES 
 **********************************************************/


