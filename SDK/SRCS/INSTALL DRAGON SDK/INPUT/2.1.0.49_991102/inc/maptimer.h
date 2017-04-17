#ifndef _TMR_H_
#define _TMR_H_

#ifdef __cplusplus
extern "C" {
#endif

// {7383A1E8-0ACA-11d2-B0F7-00C04FC324F3}
DEFINE_GUID(IID_ITmr, 
0x57c933ad, 0x1075, 0x11d2, 0xb0, 0xf8, 0x0, 0xc0, 0x4f, 0xc3, 0x24, 0xf3);

#define TMR_CAPS_YEAR_MASK      0x40
#define TMR_CAPS_MONTH_MASK     0x20
#define TMR_CAPS_DAY_MASK       0x10
#define TMR_CAPS_HOUR_MASK      0x08
#define TMR_CAPS_MINUTE_MASK    0x04
#define TMR_CAPS_SECOND_MASK    0x02
#define TMR_CAPS_DOW_MASK       0x01

#define TMR_CAPS_START_BUTTON_MASK      0x80
#define TMR_CAPS_C_BUTTON_MASK          0x40
#define TMR_CAPS_B_BUTTON_MASK          0x20
#define TMR_CAPS_A_BUTTON_MASK          0x10
#define TMR_CAPS_RIGHT_BUTTON_MASK      0x08
#define TMR_CAPS_LEFT_BUTTON_MASK       0x04
#define TMR_CAPS_DOWN_BUTTON_MASK       0x02
#define TMR_CAPS_UP_BUTTON_MASK         0x01

#define TMR_CAPS_ALARM1_MASK     0x80
#define TMR_CAPS_ALARM0_MASK     0x40


struct tmrCapsStruct {
		UCHAR tmrReadCaps;
		UCHAR tmrWriteCaps;
		UCHAR tmrBtnCaps;
		UCHAR tmrAlmCaps;
	};
typedef struct tmrCapsStruct TMR_INFO, *PTMR_INFO;

#define TMR_DOW_MONDAY 0
#define TMR_DOW_TUESDAY 1
#define TMR_DOW_WEDNESDAY 2
#define TMR_DOW_THURSDAY 3
#define TMR_DOW_FRIDAY 4
#define TMR_DOW_SATURDAY 5
#define TMR_DOW_SUNDAY 6

struct tmrTimeStruct {
		USHORT tmrCurrYear;
		USHORT tmrCurrMonth;
		USHORT tmrCurrDay;
		USHORT tmrCurrHour;
		USHORT tmrCurrMinute;
		USHORT tmrCurrSecond;
		USHORT tmrCurrDayOfWeek;
	};
typedef struct tmrTimeStruct TMR_CURR_TIME, *PTMR_CURR_TIME;

#undef INTERFACE
#define INTERFACE ITmr

DECLARE_INTERFACE_(ITmr, IUnknown)
{
    /*** IUnknown methods ***/
    STDMETHOD(QueryInterface)(THIS_ REFIID riid, LPVOID * ppvObj) PURE;
    STDMETHOD_(ULONG, AddRef)(THIS) PURE;
    STDMETHOD_(ULONG, Release)(THIS) PURE;

    /*** ITmr methods ***/
    STDMETHOD(TmrSetTime)(THIS_ PTMR_CURR_TIME pTmrCurrTime) PURE;
    STDMETHOD(TmrGetTime)(THIS_ PTMR_CURR_TIME pTmrCurrTime) PURE;
    STDMETHOD(TmrGetDeviceInfo)(THIS_ PTMR_INFO pTmrCaps) PURE;
	STDMETHOD(TmrSoundAlarm)(THIS_ UCHAR a1w, UCHAR a1v, UCHAR a2w, UCHAR a2v) PURE;
};

typedef struct ITmr *PTMR;

#if !defined(__cplusplus) || defined(CINTERFACE)
#define ITmr_QueryInterface(p,a,b) 	(p)->lpVtbl->QueryInterface(p,a,b)
#define ITmr_AddRef(p) 				(p)->lpVtbl->AddRef(p)
#define ITmr_Release(p) 			(p)->lpVtbl->Release(p)

#define ITmr_TmrGetTime(p, pTm)		(p)->lpVtbl->TmrGetTime(p,pTm)
#define ITmr_TmrSetTime(p, pTm)		(p)->lpVtbl->TmrSetTime(p, pTm)
#define ITmr_TmrGetDeviceInfo(p, pTmrInfo)		(p)->lpVtbl->TmrGetDeviceInfo(p, pTmrInfo)
#define ITmr_TmrSoundAlarm(p, a1w, a1d, a2w, a2d)	(p)->lpVtbl->TmrSoundAlarm(p, a1w, a1d, a2w, a2d)


#else
#define ITmr_QueryInterface(p,a,b)		(p)->QueryInterface(a,b)
#define ITmr_AddRef(p) 					(p)->AddRef()
#define ITmr_Release(p) 				(p)->Release()
#define ITmr_SendTmrBuffer(p,a,b,c,d,e) (p)->SendTmrBuffer(a,b,c,d,e)

#define ITmr_TmrGetTime(p, pTm)					(p)->TmrGetTime(pTm)
#define ITmr_TmrSetTime(p, pTm)					(p)->TmrSetTime(pTm)
#define ITmr_TmrGetDeviceInfo(p, pTmrInfo)		(p)->TmrGetDeviceInfo(pTmrInfo)
#define ITmr_TmrSoundAlarm(p, a1w, a1d, a2w, a2d) 	(p)->TmrSoundAlarm(a1w, a1d,  a2w, a2d)

#endif




#ifdef __cplusplus
};
#endif

#endif //_TMR_H_
