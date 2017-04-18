//***************************************************************************
//
//  LifeDoc.cpp
//
//***************************************************************************

#include <afxwin.h>

#include "Resource.h"
#include "LifeDoc.h"
#include "SizeDlg.h"

IMPLEMENT_DYNCREATE (CLifeDoc, CDocument)

BEGIN_MESSAGE_MAP (CLifeDoc, CDocument)
    ON_COMMAND (ID_OPTIONS_STEP, OnOptionsStep)
    ON_COMMAND (ID_OPTIONS_OPEN_BOUNDARY, OnOptionsOpenBoundary)
    ON_COMMAND (ID_OPTIONS_CLOSED_BOUNDARY, OnOptionsClosedBoundary)
    ON_UPDATE_COMMAND_UI (ID_OPTIONS_OPEN_BOUNDARY,
        OnUpdateOptionsOpenBoundaryUI)
    ON_UPDATE_COMMAND_UI (ID_OPTIONS_CLOSED_BOUNDARY,
        OnUpdateOptionsClosedBoundaryUI)
END_MESSAGE_MAP ()

CLifeDoc::CLifeDoc ()
{
    m_cx = -1;
    m_cy = -1;
}

BOOL CLifeDoc::OnNewDocument ()
{
    if (!CDocument::OnNewDocument ())
        return FALSE;

    if ((m_cx == -1) && (m_cy == -1)) {
        m_cx = 24;
        m_cy = 24;
    }
    else { // Prompt for grid size
        CGridSizeDialog dlg;
        dlg.m_cx = m_cx;
        dlg.m_cy = m_cy;

        dlg.DoModal ();

        m_cx = dlg.m_cx;
        m_cy = dlg.m_cy;
    }

    int nByteCount = ((m_cx * m_cy) + 7) / 8;

    try { // Allocate grid memory
        m_byGrid.SetSize (nByteCount);
        m_byBuffer.SetSize (nByteCount);
    }
    catch (CMemoryException* e) { // Just in case...
        e->Delete ();
        return FALSE;
    }

    for (int i=0; i<nByteCount; i++) {
        m_byGrid[i] = 0;
        m_byBuffer[i] = 0;
    }
    return TRUE;
}

void CLifeDoc::DeleteContents ()
{
    m_byGrid.RemoveAll ();
    m_byBuffer.RemoveAll ();
}

void CLifeDoc::Serialize (CArchive& archive)
{
    if (archive.IsStoring ())
        archive << (WORD) m_cx << (WORD) m_cy;
    else {
        WORD cx, cy;
        archive >> cx >> cy;
        m_cx = (int) cx;
        m_cy = (int) cy;
    }
    m_byGrid.Serialize (archive);
    m_byBuffer.SetSize (m_byGrid.GetSize ());
}

void CLifeDoc::OnOptionsStep ()
{
    Evolve ();
}

void CLifeDoc::OnOptionsOpenBoundary ()
{
    m_bOpenEdge = TRUE;
}

void CLifeDoc::OnOptionsClosedBoundary ()
{
    m_bOpenEdge = FALSE;
}

void CLifeDoc::OnUpdateOptionsOpenBoundaryUI (CCmdUI* pCmdUI)
{
    pCmdUI->SetCheck (m_bOpenEdge ? 1 : 0);
}

void CLifeDoc::OnUpdateOptionsClosedBoundaryUI (CCmdUI* pCmdUI)
{
    pCmdUI->SetCheck (m_bOpenEdge ? 0 : 1);
}

CSize CLifeDoc::GetGridSize ()
{
    return CSize (m_cx, m_cy);
}

BOOL CLifeDoc::GetCell (int nRow, int nCol)
{
    if ((nRow < 0) || (nRow >= m_cy) ||
        (nCol < 0) || (nCol >= m_cx))
        return FALSE;

    int nBitNumber = ((nRow * m_cx) + nCol) % 8;
    int nByteNumber = ((nRow * m_cx) + nCol) / 8;

    return m_byGrid[nByteNumber] & (1 << nBitNumber);
}

BOOL CLifeDoc::ToggleCell (int nRow, int nCol)
{
    if ((nRow < 0) || (nRow >= m_cy) ||
        (nCol < 0) || (nCol >= m_cx))
        return FALSE;

    int nBitNumber = ((nRow * m_cx) + nCol) % 8;
    int nByteNumber = ((nRow * m_cx) + nCol) / 8;

    m_byGrid[nByteNumber] ^= (1 << nBitNumber);
    SetModifiedFlag ();

    return m_byGrid[nByteNumber] & (1 << nBitNumber);
}

int CLifeDoc::Evolve ()
{
    int nPrevRow, nPrevCol;
    int nNextRow, nNextCol;
    int nNeighbors, i, j;
    int nLiveCells = 0;
    BOOL bAlive;

    for (i=0; i<m_cy; i++) { // Do rows on the outside loop...
        if (m_bOpenEdge) {
            nPrevRow = (i == 0) ? m_cy - 1 : i - 1;
            nNextRow = (i == (m_cy - 1)) ? 0 : i + 1;
        }
        else {
            nPrevRow = (i == 0) ? -1 : i - 1;
            nNextRow = (i == (m_cy - 1)) ? -1 : i + 1;
        }

        for (j=0; j<m_cx; j++) { // ...and columns on the inside
            if (m_bOpenEdge) {
                nPrevCol = (j == 0) ? m_cx - 1 : j - 1;
                nNextCol = (j == (m_cx - 1)) ? 0 : j + 1;
            }
            else {
                nPrevCol = (j == 0) ? -1 : j - 1;
                nNextCol = (j == (m_cx - 1)) ? -1 : j + 1;
            }

            nNeighbors = 0;

            if (GetCell (nPrevRow, nPrevCol))
                nNeighbors++;
            if (GetCell (nPrevRow, j))
                nNeighbors++;
            if (GetCell (nPrevRow, nNextCol))
                nNeighbors++;

            if (GetCell (i, nPrevCol))
                nNeighbors++;
            if (GetCell (i, nNextCol))
                nNeighbors++;

            if (GetCell (nNextRow, nPrevCol))
                nNeighbors++;
            if (GetCell (nNextRow, j))
                nNeighbors++;
            if (GetCell (nNextRow, nNextCol))
                nNeighbors++;

            bAlive = GetCell (i, j);

            if ((bAlive && ((nNeighbors == 2) ||
                (nNeighbors == 3))) || (!bAlive && (nNeighbors == 3))) {
                SetBackgroundCell (i, j, TRUE);
                nLiveCells++;
            }
            else
                SetBackgroundCell (i, j, FALSE);
        }
    }

    int nByteCount = ((m_cx * m_cy) + 7) / 8;
    for (i=0; i<nByteCount; i++)
        m_byGrid[i] = m_byBuffer[i];

    SetModifiedFlag ();
    UpdateAllViews (NULL, 1);
    return nLiveCells;
}

void CLifeDoc::SetBackgroundCell (int nRow, int nCol, BOOL bState)
{
    int nBitNumber = ((nRow * m_cx) + nCol) % 8;
    int nByteNumber = ((nRow * m_cx) + nCol) / 8;

    if (bState)
        m_byBuffer[nByteNumber] |= (1 << nBitNumber);
    else
        m_byBuffer[nByteNumber] &= ~(1 << nBitNumber);
}
