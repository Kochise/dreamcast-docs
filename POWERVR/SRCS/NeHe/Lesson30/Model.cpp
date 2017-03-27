/*
	Model.cpp

		Abstract base class for a model. The specific extended class will render the given model. 

	Author:	Brett Porter
	Email: brettporter@yahoo.com
	Website: http://www.geocities.com/brettporter/
	Copyright (C)2000, Brett Porter. All Rights Reserved.

	This file may be used only as long as this copyright notice remains intact.
*/

#include "Model.h"

Model::Model()
{
	m_numMeshes = 0;
	m_pMeshes = NULL;
	m_numMaterials = 0;
	m_pMaterials = NULL;
	m_numTriangles = 0;
	m_pTriangles = NULL;
	m_numVertices = 0;
	m_pVertices = NULL;
	
	pvr_dr_init(m_pDrState);
	
}

Model::~Model()
{
    destroyModel();
}

void Model::destroyModel() {
     
    int i;
    
	for ( i = 0; i < m_numMeshes; i++ ) {
		delete[] m_pMeshes[i].m_pTriangleIndices;
		
    }
	for ( i = 0; i < m_numMaterials; i++ ) {
        if(m_pMaterials[i].m_texture != NULL) { 
            plx_txr_destroy(m_pMaterials[i].m_texture);
        }
		delete[] m_pMaterials[i].m_pTextureFilename;
    }	
    
	m_numMeshes = 0;
	if ( m_pMeshes != NULL )
	{
		delete[] m_pMeshes;
		m_pMeshes = NULL;
	}

	m_numMaterials = 0;
	if ( m_pMaterials != NULL )
	{
		delete[] m_pMaterials;
		m_pMaterials = NULL;
	}

	m_numTriangles = 0;
	if ( m_pTriangles != NULL )
	{
		delete[] m_pTriangles;
		m_pTriangles = NULL;
	}

	m_numVertices = 0;
	if ( m_pVertices != NULL )
	{
		delete[] m_pVertices;
		m_pVertices = NULL;
	}  
}

void Model::draw() 
{
	// Draw by group
	for ( int i = 0; i < m_numMeshes; i++ )
	{
		int materialIndex = m_pMeshes[i].m_materialIndex;
		if ( materialIndex >= 0 )
		{
			// Lighting (PLX does not do lighting so no port)
            //glMaterialfv( GL_FRONT, GL_AMBIENT, m_pMaterials[materialIndex].m_ambient );
			//glMaterialfv( GL_FRONT, GL_DIFFUSE, m_pMaterials[materialIndex].m_diffuse );
			//glMaterialfv( GL_FRONT, GL_SPECULAR, m_pMaterials[materialIndex].m_specular );
			//glMaterialfv( GL_FRONT, GL_EMISSION, m_pMaterials[materialIndex].m_emissive );
			//glMaterialf( GL_FRONT, GL_SHININESS, m_pMaterials[materialIndex].m_shininess );

			if ( m_pMaterials[materialIndex].m_texture > 0 )
			{   
                /* Create a textured polygon context */
                pvr_poly_cxt_txr(&m_pContext, 
                                 PVR_LIST_OP_POLY, 
                                 PVR_TXRFMT_RGB565, 
                                 m_pMaterials[materialIndex].m_texture->w, 
                                 m_pMaterials[materialIndex].m_texture->h, 
                                 m_pMaterials[materialIndex].m_texture->ptr, 
                                 PVR_FILTER_BILINEAR);
			}
			else {
                /* Create a colored polygon context */ 
			    pvr_poly_cxt_col(&m_pContext, PVR_LIST_OP_POLY);
            }
				
		} else {
			// Material properties?
			/* Create a colored polygon context */ 
			pvr_poly_cxt_col(&m_pContext, PVR_LIST_OP_POLY);
		}
		
		m_pContext.gen.culling = PVR_CULLING_NONE;    // Disable culling or else model wont look right
		pvr_poly_compile(&m_pHeader, &m_pContext);    // Compile the context into a header
		pvr_prim(&m_pHeader, sizeof(pvr_poly_hdr_t)); // Submit the header to the PVR

		for ( int j = 0; j < m_pMeshes[i].m_numTriangles; j++ )
		{
		    int triangleIndex = m_pMeshes[i].m_pTriangleIndices[j];
		    const Triangle* pTri = &m_pTriangles[triangleIndex];

            for ( int k = 0; k < 3; k++ )
            {    
                int index = pTri->m_vertexIndices[k];
               
                if(k == 2) {  
                    
                    plx_vert_ifdm3(&m_pDrState,                        // DR state variable
                                    PVR_CMD_VERTEX_EOL,                // Flag
                                    m_pVertices[index].m_location[0],  // X
                                    m_pVertices[index].m_location[1],  // Y
                                    m_pVertices[index].m_location[2],  // Z
                                    0xffffffff,                        // Color
                                    pTri->m_s[k],                      // U
                                    pTri->m_t[k]);                     // V
                } else { 
                    
                    plx_vert_ifdm3(&m_pDrState,                        // DR state variable
                                    PVR_CMD_VERTEX,                    // Flag
                                    m_pVertices[index].m_location[0],  // X
                                    m_pVertices[index].m_location[1],  // Y
                                    m_pVertices[index].m_location[2],  // Z
                                    0xffffffff,                        // Color
                                    pTri->m_s[k],                      // U
                                    pTri->m_t[k]);      
                }
            }
        }
    }
}

void Model::reloadTextures()
{
    char pfn[100];
    
	for ( int i = 0; i < m_numMaterials; i++ )
		if ( strlen( m_pMaterials[i].m_pTextureFilename ) > 0 ) {
            sprintf(pfn, "/rd/%s", m_pMaterials[i].m_pTextureFilename); 
			m_pMaterials[i].m_texture = plx_txr_load(pfn, 0, PVR_TXRLOAD_16BPP);
			if( m_pMaterials[i].m_texture == NULL) { printf("Model texture was not loaded"); }
        }
		else
			m_pMaterials[i].m_texture = NULL;
}


