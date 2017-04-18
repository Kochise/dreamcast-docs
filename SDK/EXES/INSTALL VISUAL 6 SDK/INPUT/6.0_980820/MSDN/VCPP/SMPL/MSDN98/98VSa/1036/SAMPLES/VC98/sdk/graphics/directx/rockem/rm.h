/*==========================================================================
 *
 *  Copyright (C) 1995-1997 Microsoft Corporation. All Rights Reserved.
 *
 *  File: rm.h
 *
 ***************************************************************************/

#ifndef __RM_H_
#define __RM_H_

// Includes....
#include "d3drmwin.h"

// Defines....
#define NUM_DEBRIS	25
#define DEBRIS_LIFE	75
#define NUM_HIT_DEBRIS	4

// Structures
struct Debris
{
    LPDIRECT3DRMFRAME		m_pFrame;
    LPDIRECT3DRMMESHBUILDER	m_pMeshBuilder;
    BOOL			m_bInUse;
    D3DVECTOR			m_vel;
    D3DVECTOR			m_acc;
    int				m_life;
};

// Prototypes....
BOOL InitScene();
void TermScene();

BOOL RenderScene();

HRESULT LoadTextures(char *sName, void *pArg, LPDIRECT3DRMTEXTURE *hTexture);

#endif

