// vumeter.cpp : implementation file
// @doc

#include "stdafx.h"
#include "animate.h"

#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CVUMeter

CVUMeter::CVUMeter(CPalette* pPal)
{
    m_pPal = pPal;
    m_uiTimer = 0;
    m_iMean = 0;
    m_iPeak = 0;
    m_iNewMean = 0;
    m_iNewPeak = 0;
}

CVUMeter::~CVUMeter()
{
    DestroyWindow();
}


BEGIN_MESSAGE_MAP(CVUMeter, CMeter)
    //{{AFX_MSG_MAP(CVUMeter)
    ON_WM_TIMER()
    ON_WM_CREATE()
    ON_WM_DESTROY()
    //}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CVUMeter message handlers

BOOL CVUMeter::Create(const char* pszCaption,
                DWORD dwStyle,
                const RECT& rect,
                CWnd* pwndParent,
                UINT id,
                CPalette* pPal/* = NULL*/)
{
    // Define the mean value needle
    SetScale(0, 32767, 0);
    SetNeedleColor(RGB(255,255,255), 0);
    SetScaleSplit(29490);
    SetScaleColor(RGB(0,255,0), RGB(255,0,0));
    // Define the peak value needle
    SetScale(0, 32767, 1);
    SetNeedleColor(RGB(255,0,0), 1);

    return CMeter::Create(pszCaption,
                          dwStyle,
                          rect,
                          pwndParent,
                          id,
                          pPal);
}


void CVUMeter::OnTimer(UINT nIDEvent)
{
    // Update the mean value
    if (m_iNewMean != m_iMean) {
        int iDiff = (m_iNewMean - m_iMean) / 3;
        // ensure there is some difference for small changes
        if (iDiff == 0) {
            if (m_iNewMean > m_iMean) {
                iDiff = 1;
            } else {
                iDiff = -1;
            }
        }
        m_iMean += iDiff;
        if (m_iMean < 0) {
            m_iMean = 0;
        }
        CMeter::SetValue(m_iMean, 0);
    }

    if (m_iNewPeak != m_iPeak) {
        // Update the peak value
        if (m_iNewPeak > m_iPeak) {
            m_iPeak = m_iNewPeak;
        } else {
            int iDiff = (m_iNewPeak - m_iPeak) / 10;
            if (iDiff == 0) {
                iDiff = -1;
            }
            m_iPeak += iDiff;
            if (m_iPeak < 0) {
                m_iPeak = 0;
            }
        }
        CMeter::SetValue(m_iPeak, 1);
    }
}

int CVUMeter::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
    if (CMeter::OnCreate(lpCreateStruct) == -1)
        return -1;
    
    //  Create the update timer
    m_uiTimer = SetTimer(1, 100, NULL);
    
    return 0;
}

void CVUMeter::OnDestroy()
{
    CMeter::OnDestroy();
    
    if (m_uiTimer) {
        KillTimer(1);
    }
}

/*
@mfunc void | CVUMeter | SetValue | Set new values for the mean 
and peak needles.
@syntax void SetValue(int iMean, int iPeak);
@parm int | iMean | The new mean value.
@parm int | iPeak | The new peak value.
@rdesc There is no return value.
@xref <c CVUMeter> <c CMeter>
*/


void CVUMeter::SetValue(int iMean, int iPeak)
{
    m_iNewMean = iMean;
    m_iNewPeak = iPeak;
}
