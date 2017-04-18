/**********************************************************
 * This file has been created with the PowerVR Exporter v2.0
 * 3DStudio MAX R2  plug-in
 *
 * Date: 9.7.99   Time: 14:55
 * Original File: Textures.max 
 *
 * Options: 
 *
 *   Meshes        = ON
 *   Materials     = OFF
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


/**********************************************************
 * GENERAL DEFINITIONS
 **********************************************************/

#ifndef _NULL_
#define _NULL_ 0
#endif

#define NUM_MESHES     1
#define NUM_MATERIALS  10
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
#define M_BOX  0


/**********************************************************
 * MESHES DATA 
 **********************************************************/

/* MESH 0 */

#define box_NumVertex  4
#define box_NumFaces   2
#define box_NumStrips  1
#define box_Flags      0x00000026
#define box_Material   0

float box_Vertices[] = {
	100.4175f,-100.0000f,0.0000f,  -99.5825f,-100.0000f,0.0000f,  -99.5825f,100.0000f,-0.0000f,  100.4175f,100.0000f,-0.0000f,  
_NULL_ }; /* End of box_Vertices */

float box_UV[] = {
	0.0000f,1.0000f,1.0000f,1.0000f,1.0000f,0.0000f,0.0000f,0.0000f,
_NULL_ }; /* End of box_UV */

float box_Normals[] = {
	-0.0000f,-0.0000f,-1.0000f,  -0.0000f,-0.0000f,-1.0000f,  -0.0000f,-0.0000f,-1.0000f,  -0.0000f,-0.0000f,-1.0000f,  
_NULL_ }; /* End of box_Normals */

unsigned short box_Faces[] = {
	0,1,2,  2,3,0,  
_NULL_ }; /* End of box_Faces */

unsigned short box_Strips[] = {
	3,0,2,1,
_NULL_ }; /* End of box_pStrips */

unsigned short box_StripLength[] = {
	2,
_NULL_ }; /* End of box_pStripLength */



/**********************************************************
 * MESHES 
 **********************************************************/

Struct_Mesh 
   Mesh[NUM_MESHES] = {

/* MESH 0 */
	/* NumVertex      */ box_NumVertex,
	/* NumFaces       */ box_NumFaces,
	/* NumStrips      */ box_NumStrips,
	/* Flags          */ box_Flags,
	/* Material       */ box_Material,
	/* Center         */  0.417538f, 0.000000f, 0.000000f,
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


