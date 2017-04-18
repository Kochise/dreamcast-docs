#include "stdafx.h"
#include "gravity.h"
#include "uni.h"
#include "unidlg.h"
#include "timedlg.h"

//
// Universe Parameters
//
double CUniverse::G = G_G ; // Gravitational Constant   
double CUniverse::SECS_PER_TICK = G_SECS_PER_TICK; // one day           
double CUniverse::WIDTH = G_WIDTH ;
double CUniverse::HEIGHT = G_HEIGHT ;
UINT CUniverse::TIME = G_TIME ;


BOOL CUniverse::DoUniDialog()
{
	//Now uses doubles instead of ints...
    CUniDlg dlg;
    dlg.m_G = G;
    dlg.m_width = WIDTH;
    dlg.m_height = HEIGHT;
    if (dlg.DoModal() == IDOK) {
	 	G = dlg.m_G ;
		WIDTH = dlg.m_width ;
		HEIGHT = dlg.m_height ;
      return TRUE;
    }
    return FALSE;
}


BOOL CUniverse::DoTimeDialog()
{
    CTimeDlg dlg;
    dlg.m_time = TIME;
    dlg.m_SecsPerTick = SECS_PER_TICK;
    if (dlg.DoModal() == IDOK) {
	    TIME =dlg.m_time ;
	    SECS_PER_TICK = dlg.m_SecsPerTick;
      return TRUE;
    }
    return FALSE;
}

void CUniverse::Save(CArchive& ar)
{
    if (ar.IsStoring()) {
        ar << G ;
		  ar << SECS_PER_TICK ;
		  ar << WIDTH ;
		  ar << HEIGHT ;
		  ar << (DWORD)TIME ;
    } else  {
        ar >> G;
		  ar >> SECS_PER_TICK ;
		  ar >> WIDTH ;
		  ar >> HEIGHT ;
		  DWORD dw ;
		  ar >> dw; TIME = (UINT)dw;	  
    }
	
}
