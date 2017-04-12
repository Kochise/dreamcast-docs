// epgdspid.h

#ifndef __EPGDSPID_H__
#define __EPGDSPID_H__

#ifdef __MKTYPLIB__

	// Use with SetActiveView
	typedef enum epgview
	{
		EPG_GRID_VIEW		= 0,
		EPG_CATEGORY_VIEW	= 1,
		EPG_DSS_VIEW		= 2,
		EPG_MAX_VIEW		= 3
	} EPGVIEW;

typedef enum 
{
		TVX_CONTROL_GENERIC = 0,
		TVX_CONTROL_EPG	= 1,
		TVX_CONTROL_FSVIDEO = 2,
		// number of controls as enumed above
		TVX_CONTROL_NUM_OF_TYPES=3
}TVX_CONTROL_TYPES;


#endif

// Dispatch IDs

// IEPGComponent

#define dispidSetItem					1001
#define dispidClear						1002

// IEPG

#define dispidSetActiveView				2001
#define dispidGetActiveView				2002
#define dispidJumpTo					2003
#define dispidTakeFocus					2004

// ITVControlPrivate

#define dispidResume					3001
#define dispidSuspend					3002
#define dispidIdentify					3003
#define dispidAccelCommand				3004

#endif // __EPGDSPID_H__
