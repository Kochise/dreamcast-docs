/*
	Model.h

		Abstract base class for a model. The specific extended class will render the given model. 

	Author:	Brett Porter
	Email: brettporter@yahoo.com
	Website: http://www.geocities.com/brettporter/
	Copyright (C)2000, Brett Porter. All Rights Reserved.

	This file may be used only as long as this copyright notice remains intact.
*/

#ifndef MODEL_H
#define MODEL_H

#include <kos.h>		
#include <plx/texture.h>
#include <plx/prim.h>
#include <plx/matrix.h>
#include <plx/context.h>

class Model
{
	public:
		//	Mesh
		struct Mesh
		{
			int m_materialIndex;
			int m_numTriangles;
			int *m_pTriangleIndices;
		};

		//	Material properties
		struct Material
		{
			float m_ambient[4], m_diffuse[4], m_specular[4], m_emissive[4];
			float m_shininess;
			plx_texture_t *m_texture;
			char *m_pTextureFilename;
		};

		//	Triangle structure
		struct Triangle
		{
			float m_vertexNormals[3][3];
			float m_s[3], m_t[3];
			int m_vertexIndices[3];
		};

		//	Vertex structure
		struct Vertex
		{
			char m_boneID;	// for skeletal animation
			float m_location[3];
		};

	public:
		/*	Constructor. */
		Model();

		/*	Destructor. */
		virtual ~Model();

		/*	
			Load the model data into the private variables. 
				filename			Model filename
		*/
		virtual bool loadModelData( const char *filename ) = 0;

		/* Draw the model */
		void draw();

		void reloadTextures();
		
		/* Deletes all allocated Memory and Set variables to either NULL or 0 */
		void destroyModel();

	protected:
		//	Meshes used
		int m_numMeshes;
		Mesh *m_pMeshes;  // check

		//	Materials used
		int m_numMaterials;
		Material *m_pMaterials; // check

		//	Triangles used
		int m_numTriangles;
		Triangle *m_pTriangles; // check

		//	Vertices Used
		int m_numVertices;
		Vertex *m_pVertices; //check
		
		pvr_poly_cxt_t  m_pContext;
		pvr_poly_hdr_t  m_pHeader;
		pvr_dr_state_t  m_pDrState;
};

#endif // ndef MODEL_H
