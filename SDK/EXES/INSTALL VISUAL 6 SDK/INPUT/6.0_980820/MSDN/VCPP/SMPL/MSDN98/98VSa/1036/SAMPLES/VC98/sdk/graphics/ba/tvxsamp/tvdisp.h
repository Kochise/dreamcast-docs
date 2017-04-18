// tvdisp.h : TV Viewer sample application
//
// Copyright (C) 1997 Microsoft Corporation
// All rights reserved.
//
// This source code is only intended as a supplement to the
// Broadcast Architecture Programmer's Reference.
// For detailed information regarding Broadcast
// Architecture, see the reference.
//
/////////////////////////////////////////////////////////////////////////////
// ITVViewer wrapper class

class ITVViewer : public COleDispatchDriver
{
public:
	ITVViewer() {}		// Calls COleDispatchDriver default constructor
	ITVViewer(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
	ITVViewer(const ITVViewer& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

// Attributes
public:

// Operations
public:
	void SetTVMode(BOOL fTVMode);
	BOOL IsTVMode();
	BOOL IsChannelBarUp();
	BOOL IsModalDialogUp();
	BOOL IsLoaderActive();
	DATE GlobalStartTime();
	DATE GlobalEndTime();
	LPUNKNOWN ChannelList();
	long ViewerID();
	void WantNumKeys(BOOL fWantNumKeys);
	void Tune(long lTuningSpace, long lChannelNumber, long lVideoStream, long lAudioStream, LPCTSTR bsIPStream);
	void GetCurrentTuningInfo(long* lTuningSpace, long* lChannelNumber, long* lVideoStream, long* lAudioStream, BSTR* pbsIPAddress);
	void GetPreviousTuningInfo(long* lTuningSpace, long* lChannelNumber, long* lVideoStream, long* lAudioStream, BSTR* pbsIPAddress);
	void SetReminder(LPUNKNOWN pEpisode, BOOL bRecord);
	BOOL HasReminder(LPUNKNOWN pEpisode, BOOL bRecord);
	void DeleteReminder(LPUNKNOWN pEpisode, BOOL bRecord);
	BOOL HasEnhancement(LPUNKNOWN pEpisode);
	BOOL IsCC();
};
/////////////////////////////////////////////////////////////////////////////
// ITVControl wrapper class

class ITVControl : public COleDispatchDriver
{
public:
	ITVControl() {}		// Calls COleDispatchDriver default constructor
	ITVControl(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
	ITVControl(const ITVControl& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

// Attributes
public:

// Operations
public:
	BOOL OnIdle();
	void Tune(long ltsNew, long lcnNew, long lvsNew, long lasNew, LPCTSTR bsIPNew, long ltsPrev, long lcnPrev, long lvsPrev, long lasPrev, LPCTSTR bsIPPrev);
	void TearDown();
	void SyncEvent(long iEvent, LPCTSTR pParm1, LPCTSTR pParm2);
	void EpisodeStatusChanged(long iChange, LPUNKNOWN pEpi);
	void PowerChange(BOOL bPowerOn, BOOL bUIAllowed);
	void OnTVFocus();
	void SetOutput(LPCTSTR bsDeviceName);
	BOOL GetCC();
	void SetCC(BOOL bCC);
};
