// tvdispid.h

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
		keDSSEmailStatus	= 3,
		keEnhancementStatus = 4
	} EPISODESTATUS;

	typedef enum enablevideostatus
	{
		kePrimaryMonitor	= 1
	} ENABLEVIDEOSTATUS;

#endif

#define	keNoKeys			0x00
#define	keNumKeys			0x01
#define	keChannelKeys		0x02
#define	kePageKeys			0x04

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
#define dispidEnableVideo  				3012

// ITVExplorer

#define dispidSetTVMode					4001
#define dispidIsTVMode					4002
#define dispidIsChannelBarUp			4003
#define dispidIsModalDialogUp			4004
#define dispidIsLoaderActive			4005
#define dispidGlobalStartTime			4006
#define dispidGlobalEndTime				4007
#define dispidViewerID					4008
#define dispidWantKeys					4009
#define dispidTVXTune					4010
#define dispidGetCurrentTuningInfo		4011
#define dispidGetPreviousTuningInfo		4012
#define dispidSetReminder				4013
#define dispidHasReminder				4014
#define dispidDeleteReminder			4015
#define dispidHasEnhancement            4016
#define dispidIsCC                      4017

#endif // __TVDISPID_H__
