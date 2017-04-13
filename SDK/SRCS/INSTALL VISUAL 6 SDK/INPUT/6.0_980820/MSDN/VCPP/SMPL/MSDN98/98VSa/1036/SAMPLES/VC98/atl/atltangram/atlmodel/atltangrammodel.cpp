// ATLTangramModel.cpp : Implementation of CATLTangramModel
//
// This is a part of the Active Template Library.
// Copyright (C) 1996-1998 Microsoft Corporation
// All rights reserved.
//
// This source code is only intended as a supplement to the
// Active Template Library Reference and related
// electronic documentation provided with the library.
// See these sources for detailed information regarding the
// Active Template Library product.

#include "stdafx.h"
#include "ATLModel.h"
#include "ATLTangramModel.h"

// Headers required by STL.
#include <new.h>
#include <algorithm>
#include <xmemory>
#include <list>

// Utilities
#include "util.h"
#include "util.cpp"

// Other include files
#include "math.h"

///////////////////////////////////////////////////////////
//
// Constants
//
static const double PI = 3.141592654;

/////////////////////////////////////////////////////////////////////////////
// CATLTangramModel

///////////////////////////////////////////////////////////
//
//                      IATLTangramModel Interface
//
///////////////////////////////////////////////////////////
//
//  GetNumberOfVertices
//
HRESULT CATLTangramModel::GetNumberOfVertices(long* pcVertices)
{
	// Preconditions.
	if (IsValidAddress(pcVertices, sizeof(long), TRUE))
	{
		*pcVertices = m_cVertices ;
		return S_OK ;
	}
	else
	{
		ASSERT(0) ;
		return E_INVALIDARG ;
	}
}

///////////////////////////////////////////////////////////
//
//  GetVertices
//
HRESULT CATLTangramModel::GetVertices(long cVertices, TangramPoint2d* points)
{
	// Preconditions
	if (cVertices < m_cVertices)
	{
		ASSERT(0) ;
		return E_OUTOFMEMORY ;
	}

	if (cVertices < 1)
	{
		ASSERT(0) ;
		return E_INVALIDARG ;
	}

	if (!IsValidAddress(points, sizeof(TangramPoint2d)*cVertices, TRUE))
	{
		ASSERT(0) ;
		return E_POINTER ;
	}

	if (m_pVertices == NULL || m_cVertices < 1)
	{
		ASSERT(0) ;
		return E_FAIL ;
	}

	// Now we can do the actual work.

	// Apply the transform before returning the vertices.
	applyTransform() ;
	for(long i = 0 ; i < m_cVertices ; i++)
	{
		points[i] = m_pTransformVertices[i] ;
	}
	return S_OK ;
}

///////////////////////////////////////////////////////////
//
// SetVetices
//
HRESULT CATLTangramModel::SetVertices(long cVertices, TangramPoint2d* points)
{
	// Preconditions
	if (cVertices < 1)
	{
		ASSERT(0) ;
		return E_INVALIDARG ;
	}

	if (!IsValidAddress(points, sizeof(TangramPoint2d)*cVertices, FALSE))
	{
		ASSERT(0) ;
		return E_POINTER ;
	}

	// Delete existing arrays.
	delete [] m_pVertices ;
	delete [] m_pTransformVertices ;

	// Create new arrays.
	m_cVertices = cVertices ;
	m_pVertices = new TangramPoint2d[m_cVertices] ;
	m_pTransformVertices = new TangramPoint2d[m_cVertices] ;

	// Initialize array.
	for(long i = 0 ; i < m_cVertices ; i++)
	{
		m_pVertices[i] = points[i] ;
	}

	// Signal that model has changed.
	Fire_OnModelChange() ;

	return S_OK ;
}

///////////////////////////////////////////////////////////
//
//                  ITransform Interface
//
///////////////////////////////////////////////////////////
//
// Translate
//
HRESULT CATLTangramModel::Translate(double x, double y)
{
	m_ptdTranslate.x = x ;
	m_ptdTranslate.y = y ;

	Fire_OnModelChange();

	return S_OK ;
}

///////////////////////////////////////////////////////////
//
// GetRotation
//
HRESULT CATLTangramModel::GetRotation(double* pRotation)
{
	// Preconditions.
	if (!IsValidAddress(pRotation, sizeof(double), TRUE))
	{
		ASSERT(0) ;
		return E_POINTER;
	}

	// Return value in degrees. May be negative.
	*pRotation = m_dDegrees;
	return S_OK ;
}

///////////////////////////////////////////////////////////
//
// Rotate the model.
//
HRESULT CATLTangramModel::Rotate(double dDegrees)
{
	m_dDegrees = dDegrees ;

	double dRads= fmod(dDegrees,360.0)*PI/180.0;
	m_cosDegrees = cos(dRads) ;
	m_sinDegrees = sin(dRads) ;

	Fire_OnModelChange() ;

	return S_OK ;
}

///////////////////////////////////////////////////////////
//
// GetTranslation
//
HRESULT CATLTangramModel::GetTranslation(TangramPoint2d* ppoint)
{
	// Preconditions.
	if (!IsValidAddress(ppoint, sizeof(TangramPoint2d), TRUE))
	{
		ASSERT(0) ;
		return E_POINTER ;
	}

	ppoint->x = m_ptdTranslate.x ;
	ppoint->y = m_ptdTranslate.y ;

	return S_OK ;
}

///////////////////////////////////////////////////////////
//
// applyTransform Helper function.
//
void CATLTangramModel::applyTransform()
{
	if (m_dDegrees == 0.0)
	{
		// Optimization for unrotated polygon.
		for(long i = 0 ; i < m_cVertices; i++)
		{
			m_pTransformVertices[i].x = m_pVertices[i].x + m_ptdTranslate.x ;
			m_pTransformVertices[i].y = m_pVertices[i].y + m_ptdTranslate.y ;
		}
	}
	else
	{
		for(long i = 0 ; i < m_cVertices; i++)
		{
			m_pTransformVertices[i].x = m_pVertices[i].x*m_cosDegrees - m_pVertices[i].y*m_sinDegrees + m_ptdTranslate.x ;
			m_pTransformVertices[i].y = m_pVertices[i].x*m_sinDegrees + m_pVertices[i].y*m_cosDegrees + m_ptdTranslate.y ;
		}
	}
}
