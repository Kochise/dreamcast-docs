// tvdispid.h : TV Viewer sample application
//
// Copyright (C) 1997 Microsoft Corporation
// All rights reserved.
//
// This source code is only intended as a supplement to the
// Broadcast Architecture Programmer's Reference.
// For detailed information regarding Broadcast
// Architecture, see the reference.


#ifndef __TVDISPID_H__
#define __TVDISPID_H__

#ifdef __MKTYPLIB__

	// Sync event notifications
	typedef enum tvsyncevent
	{
	//	Loader sync events
	//	Corresponding messages from epgldrx.h
	//	EPGLDR_STARTING
	//	EPGLDR_ACTIVE_COMMIT_STARTING
	//	EPGLDR_ACTIVE_COMMIT_ENDING
	//	EPGLDR_PASSIVE_COMMIT_STARTING
	//	EPGLDR_PASSIVE_COMMIT_ENDING
	//	EPGLDR_ENDING

	//	Viewer sync events
		keViewerLogin						= 107,
		keViewerChange						= 108,
		keCurrentViewerChannelListChange	= 109,

	//	Other sync events
		keSysTimeChange						= 110
	} TVSYNCEVENT;

	// EpisodeStatusChanged notification enums
	typedef enum episodestatus
	{
		keReminderStatus	= 1,
		kePurchaseStatus	= 2,
		keDSSEmailStatus	= 3
	} EPISODESTATUS;

#endif

// Dispatch IDs

// ITVControl

#define dispidOnIdle					3001
#define dispidTuneControl				3002
#define dispidTearDown					3003
#define dispidSyncEvent					3004
#define dispidEpisodeStatusChanged		3005
#define dispidPowerChange				3007
#define dispidOnTVFocus   				3008
#define dispidTVSetOutput				3009
#define dispidGetCC   					3010
#define dispidSetCC		   				3011

// ITVExplorer

#define dispidSetTVMode					4001
#define dispidIsTVMode					4002
#define dispidIsChannelBarUp			4003
#define dispidIsModalDialogUp			4004
#define dispidIsLoaderActive			4005
#define dispidGlobalStartTime			4006
#define dispidGlobalEndTime				4007
#define dispidChannelList				4008
#define dispidViewerID					4009
#define dispidWantNumKeys				4010
#define dispidTVXTune					4011
#define dispidGetCurrentTuningInfo		4012
#define dispidGetPreviousTuningInfo		4013
#define dispidSetReminder				4014
#define dispidHasReminder				4015
#define dispidDeleteReminder			4016
#define dispidHasEnhancement            4017
#define dispidIsCC                      4018

#endif // __TVDISPID_H__
