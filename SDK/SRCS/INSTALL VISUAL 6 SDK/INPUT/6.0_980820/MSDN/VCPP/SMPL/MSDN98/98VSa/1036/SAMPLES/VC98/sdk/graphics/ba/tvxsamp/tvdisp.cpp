// tvdisp.cpp : TV Viewer sample application
//
// Copyright (C) 1997 Microsoft Corporation
// All rights reserved.
//
// This source code is only intended as a supplement to the
// Broadcast Architecture Programmer's Reference.
// For detailed information regarding Broadcast
// Architecture, see the reference.
//

#include "stdafx.h"
#include "tvdisp.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif



/////////////////////////////////////////////////////////////////////////////
// ITVViewer properties

/////////////////////////////////////////////////////////////////////////////
// ITVViewer operations

void ITVViewer::SetTVMode(BOOL fTVMode)
{
	static BYTE parms[] =
		VTS_BOOL;
	InvokeHelper(0xfa1, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 fTVMode);
}

BOOL ITVViewer::IsTVMode()
{
	BOOL result;
	InvokeHelper(0xfa2, DISPATCH_METHOD, VT_BOOL, (void*)&result, NULL);
	return result;
}

BOOL ITVViewer::IsChannelBarUp()
{
	BOOL result;
	InvokeHelper(0xfa3, DISPATCH_METHOD, VT_BOOL, (void*)&result, NULL);
	return result;
}

BOOL ITVViewer::IsModalDialogUp()
{
	BOOL result;
	InvokeHelper(0xfa4, DISPATCH_METHOD, VT_BOOL, (void*)&result, NULL);
	return result;
}

BOOL ITVViewer::IsLoaderActive()
{
	BOOL result;
	InvokeHelper(0xfa5, DISPATCH_METHOD, VT_BOOL, (void*)&result, NULL);
	return result;
}

DATE ITVViewer::GlobalStartTime()
{
	DATE result;
	InvokeHelper(0xfa6, DISPATCH_METHOD, VT_DATE, (void*)&result, NULL);
	return result;
}

DATE ITVViewer::GlobalEndTime()
{
	DATE result;
	InvokeHelper(0xfa7, DISPATCH_METHOD, VT_DATE, (void*)&result, NULL);
	return result;
}

LPUNKNOWN ITVViewer::ChannelList()
{
	LPUNKNOWN result;
	InvokeHelper(0xfa8, DISPATCH_METHOD, VT_UNKNOWN, (void*)&result, NULL);
	return result;
}

long ITVViewer::ViewerID()
{
	long result;
	InvokeHelper(0xfa9, DISPATCH_METHOD, VT_I4, (void*)&result, NULL);
	return result;
}

void ITVViewer::WantNumKeys(BOOL fWantNumKeys)
{
	static BYTE parms[] =
		VTS_BOOL;
	InvokeHelper(0xfaa, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 fWantNumKeys);
}

void ITVViewer::Tune(long lTuningSpace, long lChannelNumber, long lVideoStream, long lAudioStream, LPCTSTR bsIPStream)
{
	static BYTE parms[] =
		VTS_I4 VTS_I4 VTS_I4 VTS_I4 VTS_BSTR;
	InvokeHelper(0xfab, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 lTuningSpace, lChannelNumber, lVideoStream, lAudioStream, bsIPStream);
}

void ITVViewer::GetCurrentTuningInfo(long* lTuningSpace, long* lChannelNumber, long* lVideoStream, long* lAudioStream, BSTR* pbsIPAddress)
{
	static BYTE parms[] =
		VTS_PI4 VTS_PI4 VTS_PI4 VTS_PI4 VTS_PBSTR;
	InvokeHelper(0xfac, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 lTuningSpace, lChannelNumber, lVideoStream, lAudioStream, pbsIPAddress);
}

void ITVViewer::GetPreviousTuningInfo(long* lTuningSpace, long* lChannelNumber, long* lVideoStream, long* lAudioStream, BSTR* pbsIPAddress)
{
	static BYTE parms[] =
		VTS_PI4 VTS_PI4 VTS_PI4 VTS_PI4 VTS_PBSTR;
	InvokeHelper(0xfad, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 lTuningSpace, lChannelNumber, lVideoStream, lAudioStream, pbsIPAddress);
}

void ITVViewer::SetReminder(LPUNKNOWN pEpisode, BOOL bRecord)
{
	static BYTE parms[] =
		VTS_UNKNOWN VTS_BOOL;
	InvokeHelper(0xfae, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 pEpisode, bRecord);
}

BOOL ITVViewer::HasReminder(LPUNKNOWN pEpisode, BOOL bRecord)
{
	BOOL result;
	static BYTE parms[] =
		VTS_UNKNOWN VTS_BOOL;
	InvokeHelper(0xfaf, DISPATCH_METHOD, VT_BOOL, (void*)&result, parms,
		pEpisode, bRecord);
	return result;
}

void ITVViewer::DeleteReminder(LPUNKNOWN pEpisode, BOOL bRecord)
{
	static BYTE parms[] =
		VTS_UNKNOWN VTS_BOOL;
	InvokeHelper(0xfb0, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 pEpisode, bRecord);
}

BOOL ITVViewer::HasEnhancement(LPUNKNOWN pEpisode)
{
	BOOL result;
	static BYTE parms[] =
		VTS_UNKNOWN;
	InvokeHelper(0xfb1, DISPATCH_METHOD, VT_BOOL, (void*)&result, parms,
		pEpisode);
	return result;
}

BOOL ITVViewer::IsCC()
{
	BOOL result;
	InvokeHelper(0xfb2, DISPATCH_METHOD, VT_BOOL, (void*)&result, NULL);
	return result;
}


/////////////////////////////////////////////////////////////////////////////
// ITVControl properties

/////////////////////////////////////////////////////////////////////////////
// ITVControl operations

BOOL ITVControl::OnIdle()
{
	BOOL result;
	InvokeHelper(0xbb9, DISPATCH_METHOD, VT_BOOL, (void*)&result, NULL);
	return result;
}

void ITVControl::Tune(long ltsNew, long lcnNew, long lvsNew, long lasNew, LPCTSTR bsIPNew, long ltsPrev, long lcnPrev, long lvsPrev, long lasPrev, LPCTSTR bsIPPrev)
{
	static BYTE parms[] =
		VTS_I4 VTS_I4 VTS_I4 VTS_I4 VTS_BSTR VTS_I4 VTS_I4 VTS_I4 VTS_I4 VTS_BSTR;
	InvokeHelper(0xbba, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 ltsNew, lcnNew, lvsNew, lasNew, bsIPNew, ltsPrev, lcnPrev, lvsPrev, lasPrev, bsIPPrev);
}

void ITVControl::TearDown()
{
	InvokeHelper(0xbbb, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
}

void ITVControl::SyncEvent(long iEvent, LPCTSTR pParm1, LPCTSTR pParm2)
{
	static BYTE parms[] =
		VTS_I4 VTS_BSTR VTS_BSTR;
	InvokeHelper(0xbbc, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 iEvent, pParm1, pParm2);
}

void ITVControl::EpisodeStatusChanged(long iChange, LPUNKNOWN pEpi)
{
	static BYTE parms[] =
		VTS_I4 VTS_UNKNOWN;
	InvokeHelper(0xbbd, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 iChange, pEpi);
}

void ITVControl::PowerChange(BOOL bPowerOn, BOOL bUIAllowed)
{
	static BYTE parms[] =
		VTS_BOOL VTS_BOOL;
	InvokeHelper(0xbbf, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 bPowerOn, bUIAllowed);
}

void ITVControl::OnTVFocus()
{
	InvokeHelper(0xbc0, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
}

void ITVControl::SetOutput(LPCTSTR bsDeviceName)
{
	static BYTE parms[] =
		VTS_BSTR;
	InvokeHelper(0xbc1, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 bsDeviceName);
}

BOOL ITVControl::GetCC()
{
	BOOL result;
	InvokeHelper(0xbc2, DISPATCH_METHOD, VT_BOOL, (void*)&result, NULL);
	return result;
}

void ITVControl::SetCC(BOOL bCC)
{
	static BYTE parms[] =
		VTS_BOOL;
	InvokeHelper(0xbc3, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 bCC);
}
