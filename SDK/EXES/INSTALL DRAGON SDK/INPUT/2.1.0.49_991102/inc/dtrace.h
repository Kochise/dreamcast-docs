#ifndef __DTRACE_H__
#define __DTRACE_H__

#ifdef __cplusplus
extern "C" {
#endif  /* __cplusplus */

//
// DTrace Header.
//
// All source files being instrumented for DTrace must include DTrace.h
// A file called "DTags.h" should appear in the local directory or include
// path wherever DTrace.h is included
// One file from each module should also include "DTags.h" locally to instantiate
// variables
// In order to enable logging, each module should invoke the macro LOG_INIT
// In order to start a log, the named event "DTRACE_TRIGGER"
// can be set or Start DTrace in DCTool


#include <windows.h>

													 
#ifndef DTRACE									 
													 
#define LOG_INIT									 
#define LOG_EVENT(event)					
#define LOG_POINT(function,point)			
#define LOG_ENTER(function)					
#define LOG_EXIT(function)					
#define LOG_START(resource)					
#define LOG_STOP(resource)					
#define LOG_POINT_DATA(function,point,data)				 
#define LOG_TICK_nS										 
														 
#define TAG_FILE_START
#define TAG_RANGE_START(rangestart,desc)		
#define TAG_SUBRANGE(name,desc)			
#define TAG_FN(tag,description,enter,exit)		
#define TAG_RESOURCE(tag,description,start,stop)
#define TAG_EVENT(tag,description,data)			
#define TAG_SUB(tag,sub,description,data)		
#define TAG_RANGE_END
#define TAG_FILE_END							
													 
#else // DTRACE is defined

// split the range from 0..4095
#define	TAG_RANGE_APP				(0)
#define	TAG_RANGE_APP2				(200)
#define TAG_RANGE_D3D_RM			(300)
#define TAG_RANGE_D3D_IM			(500)
#define TAG_RANGE_DDRAW				(700)
#define TAG_RANGE_DSOUND			(900)
#define TAG_RANGE_DSOUNDHAL			(1000)
#define TAG_RANGE_MICROSTK			(1100)
#define TAG_RANGE_DSHOW  			(1500)
#define TAG_RANGE_MPEG				(1700)
#define TAG_RANGE_DDHAL				(2000)
#define TAG_RANGE_MAPLE             (2500)
#define TAG_RANGE_DINPUT            (2600)
#define TAG_RANGE_SERIAL            (2700)
#define TAG_RANGE_CDROM             (2800)
#define TAG_RANGE_UNKNOWN			(3000)
#define TAG_RANGE_MAPLEDEV          (3200)
									
													 
typedef struct _SDTraceLog									 
{									
	unsigned long *pNext;			
	int remaining;
	unsigned long *pStart;
	int size;
	DWORD threadId;
	DWORD fEnable;
} SDTraceLog;

extern int gDTraceLogEnable;				// this is a shared flag to turn on/off the log
extern unsigned long *gpTimerReg;		// Pointer to hardware timer register
extern SDTraceLog *gpLog;  
// extern int gDTraceSlot;

#define LOG_TICK_nS 40

#define LOG_WRITE(val)								\
{													\
	if( gDTraceLogEnable )							\
	{												\
		/* SDTraceLog *pLog = (SDTraceLog *)(TlsGetValue(gDTraceSlot)); */			\
		/* DEBUGMSG(1,(TEXT("th %08x pLog %08x slot %d\r\n"),GetCurrentThreadId(),pLog,gDTraceSlot)); */ \
		if ( gpLog->remaining > 0 )					\
		{							   				\
			unsigned long *pNext;	                \
			gpLog->remaining--;						\
			pNext = gpLog->pNext;	                \
			gpLog->pNext = pNext+2;					\
			*pNext++ = *gpTimerReg;					\
			*pNext++ = (val);						\
		}											\
	}												\
}

/*	SDTraceLog **gppDTraceLog;	   */			\

#define LOG_INIT RegisterTags();

#define LOG_TAG(range_and_tag,subtag)			LOG_WRITE(((int)(range_and_tag)<<4)+(subtag))
#define LOG_TAG_DATA(range_and_tag,subtag,data)	LOG_WRITE(((data)<<16)+((int)(range_and_tag)<<4)+(subtag))

#define LOG_EVENT(event)						LOG_TAG(PVTAG_##event,0)
#define LOG_POINT(function,subtag)				LOG_TAG(PVTAG_##function,subtag)
#define LOG_ENTER(function)						LOG_TAG(PVTAG_##function,1)
#define LOG_EXIT(function)						LOG_TAG(PVTAG_##function,2)
#define LOG_START(resource)						LOG_TAG(PVTAG_##resource,1)
#define LOG_STOP(resource)						LOG_TAG(PVTAG_##resource,2)
#define LOG_DATA(tag,subtag,data)				LOG_TAG_DATA(PVTAG_##tag,subtag,data)

#define TAG_FILE_START
#define TAG_RANGE_START(rangestart,desc)		enum EPVTagRange_##rangestart					\
												{												\
													PVTAGSTART_##rangestart = rangestart,
#define TAG_SUBRANGE(name,desc)						PVSUBRANGE__##name,
#define TAG_FN(tag,description,enter,exit)			PVTAG_##tag,
#define TAG_RESOURCE(tag,description,start,stop)	PVTAG_##tag,
#define TAG_EVENT(tag,description,data)				PVTAG_##tag,
#define TAG_SUB(tag,sub,description,data)
#define TAG_RANGE_END							};
#define TAG_FILE_END

#include <DTags.h>

#undef TAG_FILE_START
#undef TAG_RANGE_START
#undef TAG_SUBRANGE
#undef TAG_FN
#undef TAG_RESOURCE
#undef TAG_EVENT
#undef TAG_SUB
#undef TAG_RANGE_END
#undef TAG_FILE_END

void DTraceAddTag( int tagType, int tag, int subtag, TCHAR *description, TCHAR *datadesc1, TCHAR *datadesc2 );
void DTraceInitLog(
	int *pDTraceLogEnable,
	/* int *pDTraceSlot, */
	SDTraceLog **ppLog,
	unsigned long **ppTimerReg );

#define TAG_FILE_START							void RegisterTags()							\
												{											\
													/* int rt_rangestart;	*/				\
													DTraceInitLog( &gDTraceLogEnable, &gpLog, &gpTimerReg );
#define TAG_RANGE_START(rangestart,desc)			DTraceAddTag( 0, (int)(PVTAGSTART_##rangestart), 0, TEXT(desc), (TCHAR *)"", (TCHAR *)"" );
#define TAG_SUBRANGE(name,desc)						DTraceAddTag( 1, (int)(PVSUBRANGE__##name), 0, TEXT(desc), (TCHAR *)"", (TCHAR *)"" );
#define TAG_FN(tag,description,enter,exit)			DTraceAddTag( 8+2, (int)(PVTAG_##tag), 0, TEXT(description), TEXT(enter), TEXT(exit) );
#define TAG_RESOURCE(tag,description,start,stop)	DTraceAddTag( 16+2, (int)(PVTAG_##tag), 0, TEXT(description), TEXT(start), TEXT(stop) );
#define TAG_EVENT(tag,description,data)				DTraceAddTag( 24+2, (int)(PVTAG_##tag), 0, TEXT(description), TEXT(data), (TCHAR *)"" );
#define TAG_SUB(tag,sub,description,data)			DTraceAddTag( 3, (int)(PVTAG_##tag), sub, TEXT(description), TEXT(data), (TCHAR *)"" );
#define TAG_RANGE_END
#define TAG_FILE_END							}											\
												int gDTraceLogEnable=0;						\
												unsigned long *gpTimerReg;					\
												/* int gDTraceSlot; */						\
												SDTraceLog *gpLog;

#endif // ifndef/else DTRACE

#ifdef __cplusplus
}
#endif  /* __cplusplus */

#endif // __DTRACE_H__
