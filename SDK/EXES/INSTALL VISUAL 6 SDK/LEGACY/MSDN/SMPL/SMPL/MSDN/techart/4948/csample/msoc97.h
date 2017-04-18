/*************************************************************************
**
**    Office Compatible Interfaces
**
**    Msoc97.h
**
**    (c) Copyright Microsoft Corp. 1996 All Rights Reserved
**
*************************************************************************/


#if !defined(__MSOC97_H__)
#define  __MSOC97_H__

#include <objbase.h>

/////////////////////////////////////////////////////////////////////////////////////
//	Forward References

#ifdef __cplusplus
interface IOfficeCompatible;
interface IMsocOutlook;
interface IMsocDocProps;
interface IMsocBuiltinDocProps;
interface IMsocCustomDocProps;
interface IMsocRouteSlip;
interface IMsocHLink;
interface IMsocHLinks;
interface IMsocAutoCorrect;
interface IMsocAutoCorrectEntries;
interface IMsocOutlookJournalEntry;
#else
typedef interface IOfficeCompatible IOfficeCompatible;
typedef interface IMsocOutlook IMsocOutlook;
typedef interface IMsocDocProps IMsocDocProps;
typedef interface IMsocBuiltinDocProps IMsocBuiltinDocProps;
typedef interface IMsocCustomDocProps IMsocCustomDocProps;
typedef interface IMsocRouteSlip IMsocRouteSlip;
typedef interface IMsocHLink IMsocHLink;
typedef interface IMsocHLinks IMsocHLinks;
typedef interface IMsocAutoCorrect IMsocAutoCorrect;
typedef interface IMsocAutoCorrectEntries IMsocAutoCorrectEntries;
typedef interface IMsocOutlookJournalEntry IMsocOutlookJournalEntry;
#endif




/////////////////////////////////////////////////////////////////////////////////////
//	Global APIs

#if defined MSOC_BUILD

#define MSOCAPI  extern "C" __declspec(dllexport)  HRESULT __stdcall	

#else

#ifdef __cplusplus
#define MSOCAPI  extern "C" __declspec(dllimport)  HRESULT __stdcall	
#else
#define MSOCAPI  __declspec(dllimport)  HRESULT __stdcall	
#endif 

#endif // else MSOC_BUILD

// wzApplicationName should match the App name used in Outlook Log registry
MSOCAPI CreateOfficeCompatible(LPCWSTR pwzApplicationName, LPCWSTR pwzAppDisplayName, IOfficeCompatible** ppMSOC);



/////////////////////////////////////////////////////////////////////////////////////
//	OfficeCompatible Global Interfaces

#undef INTERFACE
#define INTERFACE IOfficeCompatible

DECLARE_INTERFACE(IOfficeCompatible)
{
	STDMETHOD_(void,Release)(THIS) PURE;

	// Get Outlook Interface
	STDMETHOD_(IMsocOutlook *, PioutGetOutlook)(THIS) PURE;

	// Get AutoCorrect Interface
	STDMETHOD_(IMsocAutoCorrect *, PiacGetAutoCorrect)(THIS) PURE;

	// Get Document Properties Interface
	STDMETHOD_(IMsocDocProps *, PidpCreateDocProps)(THIS) PURE;

	// Get Routing Slip Interface
	STDMETHOD_(IMsocRouteSlip *, PirsCreateRoutingSlip)(THIS) PURE;

	// Is Document Posting enabled?
	STDMETHOD_(BOOL,FCanPostDoc)(THIS) PURE;  

	// wzFileName should be the full path to the file to be posted
	STDMETHOD(PostDoc)(THIS_ LPCWSTR wzFileName, LPWSTR wzSubject, HWND hwnd) PURE;
};



/////////////////////////////////////////////////////////////////////////////////////
//	IMsocOutlook interfaces

#undef INTERFACE
#define INTERFACE	IMsocOutlook

DECLARE_INTERFACE(IMsocOutlook)
{
	// Create a new Journal entry
	//   wzFileName is NULL for New docs and is the full path to Opened docs
	STDMETHOD_(IMsocOutlookJournalEntry *, PiojeCreateOutlookJournalEntry)(THIS_ LPCWSTR wzFileName) PURE;
	STDMETHOD_(BOOL,GetLoggingState)(THIS) PURE;
	STDMETHOD_(void,SetLoggingState)(THIS_ BOOL fState) PURE;
};


#undef INTERFACE
#define INTERFACE	IMsocOutlookJournalEntry

DECLARE_INTERFACE(IMsocOutlookJournalEntry)
{
	STDMETHOD(Save)(THIS_ LPCWSTR wzFileName) PURE;

	// Close releases this JournalEntry, you can't use this object after calling Close or CloseProps
	STDMETHOD(Close)(THIS_ LPCWSTR lpwzAuthor, LPCWSTR lpwzKeyWords, LPCWSTR lpwzManager, LPCWSTR lpwzCompany) PURE;
#ifdef __cplusplus
	STDMETHOD(Close)(THIS_ IMsocDocProps *pMsocDocProps) PURE;
#else
	STDMETHOD(CloseProps)(THIS_ IMsocDocProps *pMsocDocProps) PURE;
#endif

	STDMETHOD(Route)(THIS) PURE;
	STDMETHOD(Print)(THIS) PURE;
	STDMETHOD(Send)(THIS) PURE;
	STDMETHOD(Post)(THIS) PURE;
};


/////////////////////////////////////////////////////////////////////////////
//  Document Properties


// optional flags for saving document property set
typedef enum {
	msocfDefault = 0,  // save in the format it is loaded
	msocfSaveAs95,		// save in office 95 format,
	msocfSaveAs97		// save in office 97 format, this way office 95 app can't read
};

/////////////////////////////////////////////////////////////////////////////////
// For backward compatibility reasons, METAFILE thumbnail data structure is 
// saved in 16-bit (short) format

typedef struct  { // mfp 
    short     mm; 
    short      xExt; 
    short      yExt; 
    short		unused; 
} MSOC_METAFILEPICT; 


/////////////////////////////////////////////////////////////////////////////////
// Builtin Document Properties index bit fields
// Builtin docprops have a word (16 bit) index, The bits are divided into three
// parts: Category flag ( the highest 2 bits); Type flag (the next 6 bits); Name
// index (the lowest 8 bits)
// 

#define	STDOLEPROPS		0x8000
#define	MSOEXTPROPS		0x4000

#define	STRINGPROPS		0x2000
#define NUMBERPROPS		0x1000
#define BOOLPROPS		0x0800
#define DATEPROPS		0x0400
#define	NAILPROPS		0X0100

/// Standard Ole properties

// Strings
#define PROP_TITLE        (STDOLEPROPS|STRINGPROPS|0x0000)
#define PROP_SUBJECT      (STDOLEPROPS|STRINGPROPS|0X0001)
#define PROP_AUTHOR       (STDOLEPROPS|STRINGPROPS|0X0002)
#define PROP_KEYWORDS     (STDOLEPROPS|STRINGPROPS|0X0003)
#define PROP_COMMENTS     (STDOLEPROPS|STRINGPROPS|0X0004)
#define PROP_TEMPLATE     (STDOLEPROPS|STRINGPROPS|0X0005)
#define PROP_LASTAUTH     (STDOLEPROPS|STRINGPROPS|0X0006)
#define PROP_REVISION     (STDOLEPROPS|STRINGPROPS|0X0007) // PROP_REVISION is a number formated as a string
#define PROP_APPNAME      (STDOLEPROPS|STRINGPROPS|0X0008)

  // Times
#define PROP_TOTALEDIT    (STDOLEPROPS|DATEPROPS|0x0000)
#define PROP_LASTPRINT    (STDOLEPROPS|DATEPROPS|0x0001)
#define PROP_CREATION     (STDOLEPROPS|DATEPROPS|0x0002)
#define PROP_LASTSAVE     (STDOLEPROPS|DATEPROPS|0x0003)

  // Integer stats
#define PROP_PAGES        (STDOLEPROPS|NUMBERPROPS|0x0000)
#define PROP_WORDS        (STDOLEPROPS|NUMBERPROPS|0x0001)
#define PROP_CHARS        (STDOLEPROPS|NUMBERPROPS|0x0002)
#define PROP_SECURITY     (STDOLEPROPS|NUMBERPROPS|0x0003)

//// Office Extended Document properties
// Strings
#define PROP_CATEGORY    (MSOEXTPROPS|STRINGPROPS|0x0000)
#define PROP_FORMAT      (MSOEXTPROPS|STRINGPROPS|0x0001)
#define PROP_MANAGER     (MSOEXTPROPS|STRINGPROPS|0x0002)
#define PROP_COMPANY     (MSOEXTPROPS|STRINGPROPS|0x0003)
#define PROP_GUID		 (MSOEXTPROPS|STRINGPROPS|0x0004)
#define PROP_LINKBASE    (MSOEXTPROPS|STRINGPROPS|0x0005)

  // Integer statistics
#define PROP_BYTES       (MSOEXTPROPS|NUMBERPROPS|0x0000)
#define PROP_LINES       (MSOEXTPROPS|NUMBERPROPS|0x0001)
#define PROP_PARAS       (MSOEXTPROPS|NUMBERPROPS|0x0002)
#define PROP_SLIDES      (MSOEXTPROPS|NUMBERPROPS|0x0003)
#define PROP_NOTES       (MSOEXTPROPS|NUMBERPROPS|0x0004)
#define PROP_HIDDENSLIDES (MSOEXTPROPS|NUMBERPROPS|0x0005)
#define PROP_MMCLIPS     (MSOEXTPROPS|NUMBERPROPS|0x0006)
#define PROP_CCHWSPACES	 (MSOEXTPROPS|NUMBERPROPS|0x0007)	// count of characters including spaces
#define PROP_VERSION	 (MSOEXTPROPS|NUMBERPROPS|0x0008)   // HIWORD of this dword property gives the major version of office
															// LOWORD of this dword property gives the build No of office
															// NOTE: This property is read only.


  // Booleans
#define PROP_SHAREDDOC   	  (MSOEXTPROPS|BOOLPROPS|0x0000)
#define PROP_HYPERLINKSCHANGED (MSOEXTPROPS|BOOLPROPS|0x0001)


/////////////////////////////////////////////////////////////////////////////////////
//	IMsocDocProps		interface

// Commands for DWQUERYLD
#define QLD_CLINKS      1  /* Return the number of links */
#define QLD_LINKNAME    2  /* Return a pointer to the string for index */
#define QLD_LINKTYPE    3  /* Returns the type of the value of the index */
#define QLD_LINKVAL     4  /* Return value for the index, use same
						      rules as for LPVOIDs in UserDef functions */

typedef DWORD (__stdcall *DWQUERYLD)(DWORD dwCommand, DWORD dwi, LPVOID *lplpvBuf, WCHAR *wzName);

#undef INTERFACE
#define INTERFACE	IMsocDocProps

DECLARE_INTERFACE(IMsocDocProps)
{
	STDMETHOD(Load)(THIS_ LPSTORAGE lpStg) PURE;
	STDMETHOD(Save)(THIS_ LPSTORAGE lpStg, UINT msocf) PURE;
#ifdef __cplusplus
	STDMETHOD(Load)(THIS_ LPCWSTR wzFileName) PURE;
	STDMETHOD(Save)(THIS_ LPCWSTR wzFileName, UINT msocf) PURE;
#else
	STDMETHOD(LoadFile)(THIS_ LPCWSTR wzFileName) PURE;
	STDMETHOD(SaveFile)(THIS_ LPCWSTR wzFileName, UINT msocf) PURE;
#endif 
	STDMETHOD(GetBuiltinDocProps)(THIS_ IMsocBuiltinDocProps** ppBltDocProps) PURE;
	STDMETHOD(GetCustomDocProps)(THIS_ IMsocCustomDocProps** ppCustDocProps) PURE;
	STDMETHOD(ShowDialog)(THIS_ HWND hwndParent, LPWSTR wzCaption, LPWSTR wzFileName, DWQUERYLD pfnDwQuery) PURE;
	STDMETHOD_(BOOL, FLoadedAs97)(THIS) PURE;
	STDMETHOD_(IMsocHLinks*, PihlGetHLinks)(THIS) PURE; 
	STDMETHOD(Release)(THIS) PURE;  
};


//////////////////////////////////////////////////////////////////////////////////
//	IMsocBuiltinDocProps		interface

#if !defined MSOC_BUILD

typedef struct tagSINAIL
{
   DWORD cbData;     // size of *pdata
   DWORD cftag;      // either 0,-1,-2,-3, or positive. This decides the size of pFMTID.
   BYTE *pbFMTID;    // bytes representing the FMTID
   BYTE *pbData;     // bytes representing the data
} SINAIL;

#endif

typedef SINAIL FAR * LPSINAIL;

#undef INTERFACE
#define INTERFACE	IMsocBuiltinDocProps

DECLARE_INTERFACE(IMsocBuiltinDocProps)
{
	STDMETHOD(GetProp)(THIS_ UINT uProp, VARIANT* pvarValue) PURE;
	STDMETHOD(SetProp)(THIS_ UINT uProp, VARIANT* pvarValue) PURE;

	STDMETHOD(GetThumbnail)(THIS_ LPSINAIL *lplpThumbnail) PURE;
	STDMETHOD(SetThumbnail)(THIS_ LPSINAIL lpThumbnail) PURE; 

	// FreeThumbnail must be used to free the lpThumbnail returned from GetThumbnail()
	STDMETHOD_(VOID, FreeThumbnail)(THIS_ LPSINAIL lpThumbnail) PURE;
};

//////////////////////////////////////////////////////////////////////////////////
//	IMsocCustomDocProp		interface
#undef INTERFACE
#define	INTERFACE	IMsocCustomDocProp

DECLARE_INTERFACE(IMsocCustomDocProp)
{
		STDMETHOD(SetName)(THIS_ LPWSTR wzName) PURE;
		STDMETHOD(GetName)(THIS_ LPWSTR wzName, UINT cbMax) PURE;

		STDMETHOD(SetValue)(THIS_ VARIANT* pvarValue) PURE;
		STDMETHOD(GetValue)(THIS_ VARIANT** ppvarValue) PURE;
 
		// method specific to custom document properties.
		STDMETHOD_(DWORD, CchLinkSource)(THIS) PURE;
		STDMETHOD(GetLinkSource)(THIS_ LPWSTR wzLink, UINT cbMax) PURE;
		STDMETHOD(SetLinkSource)(THIS_ LPWSTR  wzLink) PURE;


		STDMETHOD_(BOOL, FGetLinkToContent)(THIS) PURE;  
		STDMETHOD(SetLinkToContent)(THIS_ BOOL fLink) PURE;
		STDMETHOD_(BOOL, FGetLinkValidity)(THIS) PURE; 
		STDMETHOD(SetLinkValidity)(THIS_ BOOL fValidLink) PURE;
		STDMETHOD_(BOOL, FGetVisible)(THIS) PURE; 
		STDMETHOD(SetVisible)(THIS_ BOOL fVisible) PURE;

		STDMETHOD(Delete)(THIS) PURE;  // Deletes this property from CustomDocumentProperties set
		STDMETHOD(Release)(THIS) PURE;  // release and free this object
};

////////////////////////////////////////////////////////////////////////////////////
//	IMsocCustomDocProps		Interface
#undef INTERFACE
#define INTERFACE	IMsocCustomDocProps

DECLARE_INTERFACE(IMsocCustomDocProps)
{
	STDMETHOD_(DWORD, Count)(THIS) PURE;

	// Properties returned by GetProp must be released by calling pDocProp->Release();
	STDMETHOD(GetProp)(THIS_ DWORD dwIdx, IMsocCustomDocProp** ppDocProp) PURE;

	// Adds a blank property to the CustomDocProps collection.  Use pDocProp->Set... to set values
	STDMETHOD(Add)(THIS_ IMsocCustomDocProp**  ppDocProp) PURE;
	STDMETHOD(FindByName)(THIS_ LPWSTR wzName, IMsocCustomDocProp** ppCdp) PURE;
};


/////////////////////////////////////////////////////////////////////////////////////
//	IMsocRouteSlip		interface

// Valid string index
#define RSLIP_APPNAME			0x00000001
#define RSLIP_DOCTYPE			0x00000002
#define RSLIP_DOCTITLE			0x00000003
#define RSLIP_FILENAME			0x00000004
#define RSLIP_MESSAGE			0x00000005
#define RSLIP_SUBJECT			0x00000006
#define RSLIP_SUMMARY			0x00000007
#define RSLIP_ORIGINATOR		0x00000008

// Valid routing options
// Notice RSLIP_ALL_AT_ONCE must be used by itself
// other options can be set together using bit-wise or
#define  RSLIP_ALL_AT_ONCE        0x00000000
#define  RSLIP_ONE_AFTER_ANOTHER  0x00000001
#define  RSLIP_RETURN_WHEN_DONE   0x00000002
#define  RSLIP_TRACK_STATUS       0x00000004



#undef INTERFACE
#define INTERFACE IMsocRouteSlip

DECLARE_INTERFACE(IMsocRouteSlip)
{
	STDMETHOD( SetOption)(THIS_   DWORD dwOption)  PURE;
	STDMETHOD( GetOption)(THIS_   DWORD * pdwOtion)  PURE;
	STDMETHOD( GetRecipients)(THIS_   SAFEARRAY** ppsa) PURE;
	STDMETHOD( SetRecipients)(THIS_   SAFEARRAY* psa)  PURE;
	STDMETHOD( GetInfoToSave)(THIS_   SAFEARRAY** ppsa)  PURE;
	STDMETHOD(  SetInfoToSave)(THIS_   SAFEARRAY* psa)  PURE;
	STDMETHOD(  PrepareToRoute)(THIS)  PURE;
	STDMETHOD(  Route)(THIS_   LPWSTR wzFileName)  PURE;
	STDMETHOD(  Reset)(THIS)  PURE;
	STDMETHOD(  ShowEditDialog)(THIS_   HWND hwndOwner)  PURE;
	STDMETHOD(  ShowSendDialog)(THIS_   HWND hwndOwner)  PURE;
	STDMETHOD( GetStringValue)(THIS_ DWORD dwStr, LPWSTR wzBuf,  int cchMax) PURE;
	STDMETHOD( SetStringValue)(THIS_ DWORD dwStr, LPWSTR wzBuf) PURE;
	STDMETHOD( Release)(THIS) PURE;
};


/////////////////////////////////////////////////////////////////////////////////////
//	IMsocAutoCorrect		interface
#undef INTERFACE
#define INTERFACE IMsocAutoCorrect

DECLARE_INTERFACE(IMsocAutoCorrect)
{
	// ReplaceText: Whether text is automatically replaced from the replacement list
	STDMETHOD_(BOOL, FReplaceText)(THIS) PURE;
    STDMETHOD_(void, SetReplaceText)(THIS_ BOOL fReplaceText) PURE;

    // TwoInitalCapitals:  Whether TWo INitial CApitals are corrected
	STDMETHOD_(BOOL, FTwoInitialCapitals)(THIS) PURE;
    STDMETHOD_(void, SetTwoInitialCapitals)(THIS_ BOOL fTwoInitialCapitals) PURE;

	// CapitalizeNamesOfDays:  Whether monday, tuesday, etc are capitalized
    STDMETHOD_(BOOL, FCapitalizeNamesOfDays)(THIS) PURE;
    STDMETHOD_(void, SetCapitalizeNamesOfDays)(THIS_ BOOL fCapitalizeNamesOfDays) PURE;

	// CapitalizeSentences: whether the first word of sentences are capitalized
    STDMETHOD_(BOOL, FCapitalizeSentences)(THIS) PURE;
    STDMETHOD_(void, SetCapitalizeSentences)(THIS_ BOOL fCapitalizeSentences) PURE;

	// CapsLock:  Whether the cAPS lOCK key being held down is automatically fixed
    STDMETHOD_(BOOL, FCapsLock)(THIS) PURE;
    STDMETHOD_(void, SetCapsLock)(THIS_ BOOL fCapsLock) PURE;

	// Check for AutoCorrection on the string passed in
	// pwchBuffer: text to check,  "This is teh "
	// ichBuffer: index of character just typed (12)
	// pwchTo: buffer to hold new text to replace original text, "the"
	// pcchTo: in:length of buffer pwchTo (100), out: length of replacement text, (3)
	// pcchReplace: out: number of characters to replace (3)
	STDMETHOD_(BOOL, FCorrect)(THIS_ LPCWSTR pwchBuffer, unsigned int ichBuffer, BOOL fCheckNow,
							WCHAR *pwchTo, unsigned int *pcchTo, unsigned int *pcchReplace) PURE;


	STDMETHOD_(void, ShowDialog)(THIS_ HWND hwndParent) PURE;
	STDMETHOD_(IMsocAutoCorrectEntries *, PiaceGetAutoCorrectEntries)(THIS) PURE;
};


#undef INTERFACE
#define INTERFACE IMsocAutoCorrectEntries

DECLARE_INTERFACE(IMsocAutoCorrectEntries)
{
	// Count:  Returns the number of AutoCorrectEntries
	STDMETHOD_(int, Count)(THIS) PURE;

	// GetEntry:  Fills in the values of AutoCorrectEntries(i)
	STDMETHOD(GetEntry)(THIS_ int i, WCHAR *pwchName, int pcchName, WCHAR *pwchValue, int pcchValue) PURE;

	// Delete:  Removes entry i
	STDMETHOD(Delete)(THIS_ int i) PURE;

	// AddEntry:  Creates a new entry
	STDMETHOD(AddEntry)(THIS_ WCHAR *pwchName, WCHAR *pwchValue) PURE;
};

/////////////////////////////////////////////////////////////////////////////////////
//	IMsocHLink		interface
#undef INTERFACE
#define INTERFACE	IMsocHLink
#define	HLINK_NOCHANGE			0
#define HLINK_UPDATED			1
#define HLINK_MARKASDELETE		2

DECLARE_INTERFACE(IMsocHLink)
{
	STDMETHOD(SetAddress)(THIS_ LPWSTR wz) PURE;
	STDMETHOD(SetSubAddress)(THIS_ LPWSTR wz) PURE;
	STDMETHOD(GetAddress)(THIS_ LPWSTR wz) PURE;
	STDMETHOD(GetSubAddress)(THIS_ LPWSTR wz) PURE;
	STDMETHOD_(DWORD, CchAddress)(THIS) PURE;
	STDMETHOD_(DWORD, CchSubAddress)(THIS) PURE;
	STDMETHOD_(DWORD, GetStatus)(THIS) PURE;
	STDMETHOD(MarkAsDeleted)(THIS) PURE; // Mark the hlink in the property stream as deleted.
	STDMETHOD(Release)(THIS) PURE;
	STDMETHOD(SetAppData)(THIS_ DWORD dwData) PURE; // Set app specific data
	STDMETHOD_(DWORD, DwGetAppData)(THIS) PURE; // Get the app specific  data, 0 if not defined
	// Note: It is not valid to delete HLinks from a Microsoft Office application document
	//       Use MarkAsDeleted instead and the link will be deleted when the Office application
	//       loads and saves the document
	STDMETHOD(Delete)(THIS) PURE; // Actually remove the hlink from the property stream
};

/////////////////////////////////////////////////////////////////////////////////////
//	IMsocHLink  Collection	interface
#undef INTERFACE
#define INTERFACE IMsocHLinks

DECLARE_INTERFACE(IMsocHLinks)
{
	STDMETHOD_(DWORD, Count)(THIS) PURE;
	STDMETHOD(GetHLink)(THIS_ DWORD dwIdx, IMsocHLink** ppHLink) PURE;
	// Note: It is not valid to add HLinks to a Microsoft Office application document
	STDMETHOD(AddHLink)(THIS_ IMsocHLink** ppHLink) PURE;	// add a blank hlink
};


/////////////////////////////////////////////////////////////////////////////////
// Return results (HRESULT)

//	Success or Failure
#define  HRSUCCED		0x04000000
#define  HRFAILED		0x84000000

// document properties error codes
#define PROPS_E_INVALIDINDEX	(HRFAILED|0x00000001) // The caller passes in an invalid property index
#define PROPS_E_INVALIDTYPE		(HRFAILED|0x00000002) // The caller passes in a property index with the value type bit field (integer, date, string)
													  // invalid.
													  // NOTE this would not happen if the caller uses the macro defined above
#define PROPS_E_INVALIDVARIANT  (HRFAILED|0x00000003) // The caller passes in an variant with invalid 
													  // V_VT 	
#define PROPS_E_NOTEXISTENT		(HRFAILED|0x00000004) // The property doesn't exist
#define PROPS_E_ALREADYEXIST	(HRFAILED|0x00000005) // A property with the same name already exists
#define PROPS_E_INVALIDCAT		(HRFAILED|0x00000006) // The caller passes in a property index with the category bit field(standard ole, office extension, custom)
													  // invalid.
													  // NOTE this would not happen if the caller uses the macro defined above
#define PROPS_E_BSTRTOOSHORT	(HRFAILED|0X00000007) // The caller passes in VT_BSTR variant for a string 
													  // string value, but the buffer is too short for the value
#define PROPS_E_NEEDRESET		(HRFAILED|0x00000008) // The caller must call IMsocCustomDocProps::Reset before 
													  // calling IMsocCustomDocProps::Next()
#define PROPS_E_INVALIDSTM		(HRFAILED|0x0000000a) // When try to load doc properties, the LPSTORAGE the caller passed in has 
													  // invalid property streams
#define PROPS_E_NOTSTORAGEFILE  (HRFAILED|0x0000000c) // We can not Load/Save doc properties to a file that is not a storage  
#define PROPS_E_EXPECTFILENAME  (HRFAILED|0x0000000d) // In save method of doc properties takes an optional param for the filename
												      // In case the doc properties is newly created, we ask for a filename to save it in
// Document routing error codes
#define RSLIP_E_INVALIDINDEX	(HRFAILED|0x00000010) // The caller passes in an invalid index for routing slip field value
#define RSLIP_E_NOTFOUND		(HRFAILED|0x00000020) // The routing slip field value is not filled out yet 
#define RSLIP_E_SLIPEMPTY		(HRFAILED|0x00000030) // The routing slip is totally empty (no field has been filled out)

// Error code
#define MSOC_E_CANTINITOFFICE   (HRFAILED|0x00000100)
#define MSOC_E_CANTINITOUTLOOK  (HRFAILED|0x00000200)
#define MSOC_E_BADAPPNAME       (HRFAILED|0x00000300)
#define MSOC_E_LOGGINGDISABLED  (HRFAILED|0x00000400)
#define MSOC_E_EXPECTSAVEAS	    (HRFAILED|0x00000500)

#define POSTDOC_E_UNEXPECTED    (HRFAILED|0x00001000)    // An error occurred, document was not posted
#define POSTDOC_E_NOFOLDERS     (HRFAILED|0x00002000)    // No folders were found in the storage.
#define POSTDOC_E_NOSTORAGE     (HRFAILED|0x00003000)    // There was no public subscription storage
#define POSTDOC_E_NOACCESS		(HRFAILED|0x00004000)	 // The user does not have access privileges to
														 // post the document to the selected folder.
#define POSTDOC_E_NOTREGISTERED (HRFAILED|0x00005000)    // Document is not a registered document type

#define POSTDOC_E_SHAREDFOLDER	(HRFAILED|0x00006000)    // Tried to post to a Microsoft 3.x shared folder
#define POSTDOC_E_INVALIDFILE	(HRFAILED|0x00007000)    // Filename was invalid

// document properties success codes
#define PROPS_S_NONEXTLEFT		(HRSUCCED|0x00000003)	 // In IMsocCustomDocProps::Next, we return this code when there is no
														 // single custom proerty left
#define PROPS_S_STMNOTFOUND		(HRSUCCED|0x00000004)	 // When try to load doc properties, the LPSTORAGE the caller passed in 
														 // doesn't have all the property streams we are looking for. We only 
													     // load up the ones we do find.

// post to exchange success code
#define POSTDOC_S_CANCEL        (HRSUCCED|0x00000010)           // User cancelled dialog
#define POSTDOC_S_SUCCESS       (HRSUCCED|0x00000020)           // Document was posted successfully


#endif // __MSOC97_H__