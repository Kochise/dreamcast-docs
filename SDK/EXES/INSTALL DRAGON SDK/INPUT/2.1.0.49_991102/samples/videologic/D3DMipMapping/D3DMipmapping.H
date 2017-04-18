/**********************************************************
 * This file has been created with the PowerVR Exporter v2.0
 * 3DStudio MAX R2  plug-in
 *
 * Date: 28.8.99   Time: 17:21
 * Original File: Mipmapping.max 
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

#define NUM_MESHES     2
#define NUM_MATERIALS  5
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
#define M_BACKGROUND  0
#define M_BOX  1

/* MATERIALS */
#define Mt_MATERIAL__5  0
#define Mt_MIPMAP1  1
#define Mt_MIMAP2  2
#define Mt_MIPMAP3  3
#define Mt_MIPMAP4  4


/**********************************************************
 * MATERIALS 
 **********************************************************/

Struct_Material 
   Material[NUM_MATERIALS] = {

/* MATERIAL 0 */
	/* Material Name  */ "Material #5",
	/* Ambient        */ _NULL_,
	/* Difusse        */ "Background.bmp",
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
	/* Material Name  */ "Mipmap1",
	/* Ambient        */ _NULL_,
	/* Difusse        */ "Mipmap_1.bmp",
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
	/* Material Name  */ "Mimap2",
	/* Ambient        */ _NULL_,
	/* Difusse        */ "Mipmap_3.bmp",
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
	/* Material Name  */ "Mipmap3",
	/* Ambient        */ _NULL_,
	/* Difusse        */ "Mipmap_2.bmp",
	/* Specular       */ _NULL_,
	/* Shininess      */ _NULL_,
	/* ShinStrength   */ _NULL_,
	/* SelfIlluminat. */ _NULL_,
	/* Opacity        */ "tMipmap_2.bmp",
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
	/* Material Name  */ "Mipmap4",
	/* Ambient        */ _NULL_,
	/* Difusse        */ "Mipmap_4.bmp",
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

#define background_NumVertex  4
#define background_NumFaces   2
#define background_NumStrips  1
#define background_Flags      0x00000027
#define background_Material   0

float background_Vertices[] = {
	380.9020f,318.9218f,97.9409f,  -355.1573f,318.9218f,97.9409f,  -355.1573f,-323.5045f,97.9409f,  380.9020f,-323.5045f,97.9409f,  
_NULL_ }; /* End of background_Vertices */

float background_UV[] = {
	0.0000f,1.0000f,1.0000f,1.0000f,1.0000f,0.0000f,0.0000f,0.0000f,
_NULL_ }; /* End of background_UV */

float background_Normals[] = {
	0.0000f,-0.0000f,1.0000f,  0.0000f,-0.0000f,1.0000f,  0.0000f,-0.0000f,1.0000f,  0.0000f,-0.0000f,1.0000f,  
_NULL_ }; /* End of background_Normals */

unsigned short background_Faces[] = {
	0,1,2,  2,3,0,  
_NULL_ }; /* End of background_Faces */

unsigned short background_Strips[] = {
	3,0,2,1,
_NULL_ }; /* End of background_pStrips */

unsigned short background_StripLength[] = {
	2,
_NULL_ }; /* End of background_pStripLength */


/* MESH 1 */

#define box_NumVertex  24
#define box_NumFaces   12
#define box_NumStrips  6
#define box_Flags      0x00000027
#define box_Material   1

float box_Vertices[] = {
	-40.0000f,40.0000f,-40.0000f,  40.0000f,40.0000f,-40.0000f,  40.0000f,-40.0000f,-40.0000f,  -40.0000f,-40.0000f,-40.0000f,  -40.0000f,40.0000f,40.0000f,  
	-40.0000f,-40.0000f,40.0000f,  40.0000f,-40.0000f,40.0000f,  40.0000f,40.0000f,40.0000f,  -40.0000f,-40.0000f,40.0000f,  -40.0000f,-40.0000f,-40.0000f,  
	40.0000f,-40.0000f,-40.0000f,  40.0000f,-40.0000f,40.0000f,  -40.0000f,40.0000f,40.0000f,  -40.0000f,40.0000f,-40.0000f,  -40.0000f,-40.0000f,-40.0000f,  
	-40.0000f,-40.0000f,40.0000f,  40.0000f,40.0000f,40.0000f,  40.0000f,40.0000f,-40.0000f,  -40.0000f,40.0000f,-40.0000f,  -40.0000f,40.0000f,40.0000f,  
	40.0000f,-40.0000f,40.0000f,  40.0000f,-40.0000f,-40.0000f,  40.0000f,40.0000f,-40.0000f,  40.0000f,40.0000f,40.0000f,  
_NULL_ }; /* End of box_Vertices */

float box_UV[] = {
	0.0000f,1.0000f,1.0000f,1.0000f,1.0000f,0.0000f,0.0000f,0.0000f,1.0000f,1.0000f,1.0000f,0.0000f,0.0000f,0.0000f,0.0000f,1.0000f,1.0000f,1.0000f,1.0000f,0.0000f,0.0000f,0.0000f,0.0000f,1.0000f,1.0000f,1.0000f,1.0000f,0.0000f,0.0000f,0.0000f,
	0.0000f,1.0000f,1.0000f,1.0000f,1.0000f,0.0000f,0.0000f,0.0000f,0.0000f,1.0000f,1.0000f,1.0000f,1.0000f,0.0000f,0.0000f,0.0000f,0.0000f,1.0000f,
_NULL_ }; /* End of box_UV */

float box_Normals[] = {
	-0.0000f,-0.0000f,-1.0000f,  -0.0000f,-0.0000f,-1.0000f,  -0.0000f,-0.0000f,-1.0000f,  -0.0000f,-0.0000f,-1.0000f,  0.0000f,0.0000f,1.0000f,  0.0000f,0.0000f,1.0000f,  0.0000f,0.0000f,1.0000f,  0.0000f,0.0000f,1.0000f,  0.0000f,-1.0000f,-0.0000f,  0.0000f,-1.0000f,-0.0000f,  0.0000f,-1.0000f,-0.0000f,  0.0000f,-1.0000f,-0.0000f,  -1.0000f,0.0000f,0.0000f,  -1.0000f,0.0000f,0.0000f,  -1.0000f,0.0000f,0.0000f,  
	-1.0000f,0.0000f,0.0000f,  0.0000f,1.0000f,0.0000f,  0.0000f,1.0000f,0.0000f,  0.0000f,1.0000f,0.0000f,  0.0000f,1.0000f,0.0000f,  1.0000f,0.0000f,-0.0000f,  1.0000f,0.0000f,-0.0000f,  1.0000f,0.0000f,-0.0000f,  1.0000f,0.0000f,-0.0000f,  
_NULL_ }; /* End of box_Normals */

unsigned short box_Faces[] = {
	0,1,2,  2,3,0,  4,5,6,  6,7,4,  8,9,10,  10,11,8,  12,13,14,  14,15,12,  16,17,18,  18,19,16,  20,21,22,  22,23,20,  
_NULL_ }; /* End of box_Faces */

unsigned short box_Strips[] = {
	23,20,22,21,19,16,18,17,15,12,14,13,11,8,10,9,7,4,6,5,3,0,2,1,
_NULL_ }; /* End of box_pStrips */

unsigned short box_StripLength[] = {
	2,2,2, 2,2,2, 
_NULL_ }; /* End of box_pStripLength */



/**********************************************************
 * MESHES 
 **********************************************************/

Struct_Mesh 
   Mesh[NUM_MESHES] = {

/* MESH 0 */
	/* NumVertex      */ background_NumVertex,
	/* NumFaces       */ background_NumFaces,
	/* NumStrips      */ background_NumStrips,
	/* Flags          */ background_Flags,
	/* Material       */ background_Material,
	/* Center         */  12.872401f, -2.291351f, 97.940910f,
	/* Vertices       */ (float *)background_Vertices,
	/* UV             */ (float *)background_UV,
	/* Normals        */ (float *)background_Normals,
	/* Packed Vertices*/ (float *)_NULL_,
	/* VertexColor    */ (unsigned int *)_NULL_,
	/* VertexMaterial */ (unsigned int *)_NULL_,
	/* Faces          */ (unsigned short *)background_Faces,
	/* Strips         */ (unsigned short *)background_Strips,
	/* StripLength    */ (unsigned short *)background_StripLength,

/* MESH 1 */
	/* NumVertex      */ box_NumVertex,
	/* NumFaces       */ box_NumFaces,
	/* NumStrips      */ box_NumStrips,
	/* Flags          */ box_Flags,
	/* Material       */ box_Material,
	/* Center         */  -0.000003f, -0.000002f, -1.313267f,
	/* Vertices       */ (float *)box_Vertices,
	/* UV             */ (float *)box_UV,
	/* Normals        */ (float *)box_Normals,
	/* Packed Vertices*/ (float *)_NULL_,
	/* VertexColor    */ (unsigned int *)_NULL_,
	/* VertexMaterial */ (unsigned int *)_NULL_,
	/* Faces          */ (unsigned short *)box_Faces,
	/* Strips         */ (unsigned short *)box_Strips,
	/* StripLength    */ (unsigned short *)box_StripLength

	}; /* End of Meshes *//**********************************************************
 * DEFINITIONS
 **********************************************************/



/**********************************************************
 * TEXTURES DATA 
 **********************************************************/


/**********************************************************
 * TEXTURES 
 **********************************************************/


