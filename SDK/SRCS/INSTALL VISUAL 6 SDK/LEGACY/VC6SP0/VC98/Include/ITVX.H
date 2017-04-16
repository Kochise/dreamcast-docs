////////////////////
// TVExplorer Interface Definition
//
//

#ifndef __ITVX_H__
#define __ITVX_H__

#include "mstv.h"
#include "tvdisp.h"
#include "tvdispid.h"
#include "epgdisp.h"
#include "epgdspid.h"

// {3F8A2EA2-C171-11cf-868C-00805F2C11CE}
DEFINE_GUID(IID_IEnumChannel, 
0x3f8a2ea2, 0xc171, 0x11cf, 0x86, 0x8c, 0x0, 0x80, 0x5f, 0x2c, 0x11, 0xce);

interface IEnumChannel : public IUnknown
{
public:
    virtual /* [local] */ HRESULT __stdcall Next( 
        /* [in] */ ULONG celt,
        /* [out] */ CHANNEL_INFO __RPC_FAR *rgelt,
        /* [out] */ ULONG __RPC_FAR *pceltFetched) = 0;
        
    virtual /* [local] */ HRESULT __stdcall Skip( 
        /* [in] */ ULONG celt) = 0;
    
    virtual /* [local] */ HRESULT __stdcall Reset( void) = 0;
    
    virtual /* [local] */ HRESULT __stdcall Clone( 
        /* [out] */ IEnumChannel __RPC_FAR *__RPC_FAR *ppenum) = 0;
    
};

// {3F8A2EA6-C171-11cf-868C-00805F2C11CE}
DEFINE_GUID(IID_IEPGOptions, 
0x3f8a2ea6, 0xc171, 0x11cf, 0x86, 0x8c, 0x0, 0x80, 0x5f, 0x2c, 0x11, 0xce);

interface IEPGOptions : public IUnknown
{
public:
	virtual HRESULT __stdcall DefaultAction( void) = 0;
};

// {3F8A2EA7-C171-11cf-868C-00805F2C11CE}
DEFINE_GUID(IID_IEPGItem, 
0x3f8a2ea7, 0xc171, 0x11cf, 0x86, 0x8c, 0x0, 0x80, 0x5f, 0x2c, 0x11, 0xce);

interface IEPGItem : public IUnknown
{
	virtual HRESULT __stdcall TuningInfo (LONG* plTuningSpace, LONG* plChannelNumber) = 0;
	virtual HRESULT __stdcall StartTime (DATE* pStartTime) = 0;
	virtual HRESULT __stdcall EndTime(DATE* pEndTime) = 0;
	virtual HRESULT __stdcall Length (long* pLength) = 0; 
	virtual HRESULT __stdcall OnNow (VARIANT_BOOL* pOnNow) = 0; 
	virtual HRESULT __stdcall Title (BSTR* pstrTitle) = 0;
	virtual HRESULT __stdcall BodyText (BSTR* pstrBodyText) = 0;
	virtual HRESULT __stdcall PreviewGraphic (BSTR* pstrPreviewGraphic) = 0;
	virtual HRESULT __stdcall NumIcons (long* pNumIcon) = 0;
	virtual HRESULT __stdcall GetIcon (long iIconNumber, BSTR* pstrIconName) = 0;
	virtual HRESULT __stdcall NumOptions (long* pNumOptions) = 0;
	virtual HRESULT __stdcall OptionPrompt (BSTR* pstrPrompt) = 0;
	virtual HRESULT __stdcall GetOption (long iOptionNumber, long* plID, BSTR* pstrText) = 0;
};

// {3F8A2EA8-C171-11cf-868C-00805F2C11CE}
DEFINE_GUID(IID_IEPGEpisode, 
0x3f8a2ea8, 0xc171, 0x11cf, 0x86, 0x8c, 0x0, 0x80, 0x5f, 0x2c, 0x11, 0xce);

interface IEPGEpisode : public IEPGItem
{
	virtual HRESULT __stdcall TimeSlotID(long* lTimeSlotID) = 0;
	virtual HRESULT __stdcall ChannelID(long* lChannelID) = 0;
	virtual HRESULT __stdcall EpisodeID(long* lEpisodeID) = 0;

	virtual HRESULT __stdcall PayPerView(VARIANT_BOOL *pf) = 0;

	virtual HRESULT __stdcall RatingID(long* lRatingID) = 0;

	virtual HRESULT __stdcall CallLetters(BSTR* ppszCallLetters) = 0;

	virtual HRESULT __stdcall PPVViewCost(CURRENCY* cy) = 0;
	virtual HRESULT __stdcall PPVTapeCost(CURRENCY* cy) = 0;

	virtual HRESULT __stdcall IsRemindItem(VARIANT_BOOL *pf) = 0;
	virtual HRESULT __stdcall IsRecordItem(VARIANT_BOOL *pf) = 0;
	virtual HRESULT __stdcall Repetition(int* iRep) = 0;
	virtual HRESULT __stdcall RemindRecordIdx(long* idxRR) = 0;
	virtual HRESULT __stdcall IsContinuous(VARIANT_BOOL *pf) = 0;
	virtual HRESULT __stdcall IsOnLater(VARIANT_BOOL *pf) = 0;
	virtual HRESULT __stdcall IsOnSoon(VARIANT_BOOL *pf) = 0;

	virtual HRESULT __stdcall IsPurchaseItem(VARIANT_BOOL *pf) = 0;
	virtual HRESULT __stdcall IsListGuideItem(VARIANT_BOOL *pf) = 0;
	virtual HRESULT __stdcall PurchaseIdx(long* idxPur) = 0;

	virtual HRESULT __stdcall ThemeID(long* lThemeID) = 0;

	virtual HRESULT __stdcall PPVCanBeCancelled(VARIANT_BOOL *pf) = 0;
	virtual HRESULT __stdcall PPVTokenAddress(long *lPaymentToken, long *lPaymentAddress) = 0;
	virtual HRESULT __stdcall IsPurchasable(IDispatch** ppOutDetails) = 0;

	virtual HRESULT __stdcall AbbreviatedTitle(BSTR* pstrAbbrevTitle) = 0;

	virtual HRESULT __stdcall HasEnhancement(VARIANT_BOOL *pf, long *lTSEnhMappingID, long *lEpiEnhMappingID) = 0;
	virtual HRESULT __stdcall Layout(long lEnhMappingID, BSTR* EnhTitle, BSTR* EnhLayout, BSTR* EnhAddress) = 0;
};

// {3F8A2EA9-C171-11cf-868C-00805F2C11CE}
DEFINE_GUID(IID_IEPGCategory, 
0x3f8a2ea9, 0xc171, 0x11cf, 0x86, 0x8c, 0x0, 0x80, 0x5f, 0x2c, 0x11, 0xce);

interface IEPGCategory : public IEPGItem
{
	virtual HRESULT __stdcall IsOtherTimes(VARIANT_BOOL *pf) = 0;
	virtual HRESULT __stdcall TimeSlotID(long* lTimeSlotID) = 0;
	virtual HRESULT __stdcall SearchText(BSTR* bsText) = 0;
};

// {3F8A2EAA-C171-11cf-868C-00805F2C11CE}
DEFINE_GUID(IID_IEPGDSSMailItem, 
0x3f8a2eaa, 0xc171, 0x11cf, 0x86, 0x8c, 0x0, 0x80, 0x5f, 0x2c, 0x11, 0xce);

interface IEPGDSSMailItem : public IEPGItem
{
	virtual HRESULT __stdcall MarkRead() = 0;
	virtual HRESULT __stdcall DeleteMail() = 0;
	virtual HRESULT __stdcall IsRead(VARIANT_BOOL* pIsRead) = 0;
};

#endif // __ITVX_H__
