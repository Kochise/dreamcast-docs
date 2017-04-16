// fade.cpp : implementation file
// (continuation of CPaintWnd)

#include "stdafx.h"
#include "MarkPnt.h"
#include "tools.h"
#include "paintwnd.h"

////////////////////////////////////////////////////////////////////////////////
// Image Fading
//
// The idea is to transparently blt a cell of say 8x8 pixels
// which is mostly transparent but has a moving pixel of the
// background color in it.  Each timer tick we do a few of these 


void CPaintWnd::InitFade()
{
    m_iFadeBlockHeight = 16;
    m_iFadeBlockWidth = 16;

    // Set up the array of points in the cell
    m_iNumCellPoints = m_iFadeBlockHeight * m_iFadeBlockWidth; 
    m_pCellPoints = new CPoint [m_iNumCellPoints];
    ASSERT(m_pCellPoints);
    for (int i = 0; i < m_iFadeBlockHeight; i++) {
        for (int j = 0; j < m_iFadeBlockWidth; j++) {
            m_pCellPoints[i * m_iFadeBlockWidth + j].x = j;
            m_pCellPoints[i * m_iFadeBlockWidth + j].y = i;
        }
    }

    // Now randomize the order
    for (i = m_iNumCellPoints; i > 0; i--) {
        int j = rand() % i; // 0 <= j < i
        CPoint pt = m_pCellPoints[j];
        m_pCellPoints[j] = m_pCellPoints[i-1];
        m_pCellPoints[i-1] = pt;
    }

    // Set the initial state
    m_iFadeBand = 0;
    m_iCellPoint = 0;
    CRect rc;
    GetClientRect(&rc);
    m_iNumFadeBands = (rc.bottom - rc.top + 1) / m_iFadeBlockHeight;
}

void CPaintWnd::Fade(int iCycles)
{
    // Get the window size
    CRect rc;
    GetClientRect (&rc);
    BYTE bErase = m_Pal.GetNearestPaletteIndex(PALETTERGB(178, 178, 178));

    while(iCycles--) {
        // work out what line we are working on
        int y = m_iFadeBand * m_iFadeBlockHeight
              + m_pCellPoints[m_iCellPoint].y;

        // get the initial x value
        int x = m_pCellPoints[m_iCellPoint].x;

        // modify the pixels on this line
        BYTE* pPixel = (BYTE*)m_dsPaint.GetPixelAddress(x, y);
        while (x < rc.right) {
            *pPixel = bErase; 
            pPixel += m_iFadeBlockWidth;
            x += m_iFadeBlockWidth;
        }

        // define the dirty region
        rc.top = y;
        rc.bottom = y + 1;

        // Add the band to the dirty region
        AddDirtyRegion(&rc);

        // Update the screen
        RenderAndDrawDirtyList();

        // Set up for next time around
        m_iFadeBand++;
        if (m_iFadeBand >= m_iNumFadeBands) {
            m_iFadeBand = 0;
            m_iCellPoint++;
            if (m_iCellPoint >= m_iNumCellPoints) {
                m_iCellPoint = 0;
            }
        }
    }
}
