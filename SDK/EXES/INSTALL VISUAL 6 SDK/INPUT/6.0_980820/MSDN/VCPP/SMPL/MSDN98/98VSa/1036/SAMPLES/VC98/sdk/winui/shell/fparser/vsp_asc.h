/* #define VwStreamStaticType	VIEW_ASC_INIT */
#define VwStreamDynamicType	VIEW_ASC_DATA
#define VwStreamSaveType	VIEW_ASC_SAVE

/* #define VwStreamStaticName	AscInit */
#define VwStreamDynamicName	AscData
#define VwStreamSaveName	AscSave

#define VwStreamIdName		VwAscOverlayId
#define VwStreamIdCount		1

/* #define VwStreamUserSaveType	VIEW_ASC_USER_SAVE */
#define VwStreamGenSeekName	SeekSpot

#define VwInclude		"vs_asc.h"

#define VwStreamOpenFunc	asc_stream_open
#define VwStreamCloseFunc	asc_stream_close
#define VwStreamSeekFunc	asc_stream_seek
#define VwStreamTellFunc	asc_stream_tell
#define VwStreamReadFunc	asc_stream_read
#define VwStreamSectionFunc	asc_stream_section

#define VwGetInfoFunc		asc_getinfo
#define VwGetRtnsFunc		asc_getrtns
#define VwGetDataFunc		asc_getdata
#define VwSetDataFunc		asc_setdata
#define VwAllocProcFunc		asc_alloc_proc
#define VwFreeProcFunc		asc_free_proc
#define VwLocalUpFunc		asc_local_up
#define VwLocalDownFunc		asc_local_down

