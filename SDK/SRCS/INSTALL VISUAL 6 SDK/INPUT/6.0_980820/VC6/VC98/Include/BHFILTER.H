
//============================================================================
//  MODULE: Filter.h
//
//  Description:
//
//  Bloodhound DLL for Filtering.
//
//  Modification History
//
//  stevehi         03/22/93            Created.
//  raypa           10/25/93            Changed HPROPERTYDB to HPROTOCOL.
//  SteveHi         10/28/93            pull Value out of Object union
//============================================================================



#if !defined(_FILTER_)

#define _FILTER_

//============================================================================
//  types
//============================================================================


typedef HFILTER * LPHFILTER;


typedef DWORD FILTERACTIONTYPE;
typedef DWORD VALUETYPE;


// check for protocols existing in the frame.

// ProtocolPart
// this is the raw data for a Protocol based expression
//
// WHAT???          FIELD          DESCRIPTION                  EXAMPLE
// -------          -----          -----------                  -------
// Count of Protocol(nPropertyDBs) Number of protocols to pass  5
// PropertyDB Table (PropertyDB)    Table of HPROTOCOL        SMB, LLC, MAC
//
// NOTE: the nPropertyDBs field may also be the following, which implies that
// all are selected but that none have actually been put into the structure

#define PROTOCOL_NUM_ANY  (-1)

//...   Use PROTOCOLTABLE defined in BHTYPES.H

typedef PROTOCOLTABLE PROTOCOLTABLETYPE;        // array of HPROTOCOL's 
typedef PROTOCOLTABLETYPE *LPPROTOCOLTABLETYPE;

// filter bits stores who passed what filter per frame to speed up
//  the filter process...  This is actually an array.

typedef DWORD FILTERBITS;

typedef FILTERBITS *LPFILTERBITS;

typedef SYSTEMTIME *LPTIME;
typedef SYSTEMTIME UNALIGNED * ULPTIME;


// The Filter Object is the basic unit of the postfix stack.
// I need to restart the convert property to value if the comparison does not match.
// To do this, I need the original pointer to the property.  Pull the hProperty out of
// the union so that the pointer to the property is saved.

typedef struct _FILTEROBJECT
{
    FILTERACTIONTYPE    Action;     // Object action, see codes below
    HPROPERTY           hProperty;  // property key
    union
    {
        VALUETYPE           Value;           // value of the object.
        HPROTOCOL           hProtocol;       // protocol key.
        LPVOID              lpArray;         // if array, length is ItemCount below.
        LPPROTOCOLTABLETYPE lpProtocolTable; // list of protocols to see if exist in frame.
        LPADDRESS           lpAddress;       // kernel type address, mac or ip
        ULPLARGEINT         lpLargeInt;      // Double DWORD used by NT
        ULPTIME             lpTime;          // pointer to SYSTEMTIME
        LPOBJECT_IDENTIFIER lpOID;           // pointer to OBJECT_IDENTIFIER

    };
    union
    {
        WORD            ByteCount;      // Number of BYTES!
        WORD            ByteOffset;     // offset for array compare
    };

    struct _FILTEROBJECT * pNext;   // reserved
} FILTEROBJECT;

typedef FILTEROBJECT * LPFILTEROBJECT;

#define FILTERINFO_SIZE (sizeof(FILTEROBJECT) )



typedef struct _FILTERDESC
{
    WORD            NumEntries;
    WORD            Flags;          // private
    LPFILTEROBJECT  lpStack;
    LPFILTEROBJECT  lpKeepLast;
    LPVOID          UIInstanceData; // UI specific information.
    LPFILTERBITS    lpFilterBits;   // cache who passed
    LPFILTERBITS    lpCheckBits;    // have we looked at it yet?
    
} FILTERDESC;

typedef FILTERDESC * LPFILTERDESC;

#define FILTERDESC_SIZE sizeof(FILTERDESC)


//============================================================================
//  Macros.
//============================================================================

#define FilterGetUIInstanceData(hfilt)         (((LPFILTERDESC)hfilt)->UIInstanceData)
#define FilterSetUIInstanceData(hfilt,inst)    (((LPFILTERDESC)hfilt)->UIInstanceData = (LPVOID)inst)

//============================================================================
//  defines
//============================================================================

#define FILTERFREEPOOLSTART 20

#define INVALIDELEMENT -1
#define INVALIDVALUE ((VALUETYPE) -9999)

// use filter failed to check the return code on FilterFrame.
#define FILTER_FAIL_WITH_ERROR  -1
#define FILTER_PASSED TRUE
#define FILTER_FAILED FALSE

//  NOTE NOTE NOTE  If you change the values of the following constants, you
//    MUST modify the TableEval table in filtloc.h.

#define FILTERACTION_INVALID            0
#define FILTERACTION_PROPERTY           1
#define FILTERACTION_VALUE              2
#define FILTERACTION_STRING             3
#define FILTERACTION_ARRAY              4
#define FILTERACTION_AND                5
#define FILTERACTION_OR                 6
#define FILTERACTION_XOR                7
#define FILTERACTION_PROPERTYEXIST      8
#define FILTERACTION_CONTAINSNC         9
#define FILTERACTION_CONTAINS           10
#define FILTERACTION_NOT                11
#define FILTERACTION_EQUALNC            12
#define FILTERACTION_EQUAL              13
#define FILTERACTION_NOTEQUALNC         14
#define FILTERACTION_NOTEQUAL           15
#define FILTERACTION_GREATERNC          16
#define FILTERACTION_GREATER            17
#define FILTERACTION_LESSNC             18
#define FILTERACTION_LESS               19
#define FILTERACTION_GREATEREQUALNC     20
#define FILTERACTION_GREATEREQUAL       21
#define FILTERACTION_LESSEQUALNC        22
#define FILTERACTION_LESSEQUAL          23
#define FILTERACTION_PLUS               24
#define FILTERACTION_MINUS              25
#define FILTERACTION_ADDRESS            26
#define FILTERACTION_ADDRESSANY         27
#define FILTERACTION_FROM               28
#define FILTERACTION_TO                 29
#define FILTERACTION_FROMTO             30
#define FILTERACTION_AREBITSON          31
#define FILTERACTION_AREBITSOFF         32
#define FILTERACTION_PROTOCOLSEXIST     33
#define FILTERACTION_PROTOCOLEXIST      34
#define FILTERACTION_ARRAYEQUAL         35
#define FILTERACTION_DEREFPROPERTY      36
#define FILTERACTION_LARGEINT           37
#define FILTERACTION_TIME               38
#define FILTERACTION_ADDR_ETHER         39
#define FILTERACTION_ADDR_TOKEN         40
#define FILTERACTION_ADDR_FDDI          41
#define FILTERACTION_ADDR_IPX           42
#define FILTERACTION_ADDR_IP            43
#define FILTERACTION_OID                44
#define FILTERACTION_OID_CONTAINS       45
#define FILTERACTION_OID_BEGINS_WITH    46
#define FILTERACTION_OID_ENDS_WITH      47
#define FILTERACTION_ADDR_VINES         48

#define FILTERACTION_EXPRESSION         97
#define FILTERACTION_BOOL               98
#define FILTERACTION_NOEVAL             99


#define FILTER_NO_MORE_FRAMES   0xFFFFFFFF
#define FILTER_CANCELED         0xFFFFFFFE
#define FILTER_DIRECTION_NEXT   TRUE
#define FILTER_DIRECTION_PREV   FALSE




//============================================================================
//  Helper functions.
//============================================================================

typedef BOOL (WINAPI *STATUSPROC)(DWORD, HCAPTURE, HFILTER, DWORD);
        // callback to show filter status:
        //      DWORD nFrame
        //      HCAPTURE
        //      HFILTER
        //      DWORD  UI Instance data (hwnd)


//============================================================================
//  Global data.
//============================================================================



//=============================================================================
//  FILTER API's.
//=============================================================================

extern HFILTER  WINAPI CreateFilter(VOID);

extern DWORD    WINAPI DestroyFilter(HFILTER hFilter);

extern HFILTER  WINAPI FilterDuplicate(HFILTER hFilter);

extern DWORD    WINAPI DisableParserFilter(HFILTER hFilter, HPARSER hParser);

extern DWORD    WINAPI EnableParserFilter(HFILTER hFilter, HPARSER hParser);

extern DWORD    WINAPI FilterAddObject(HFILTER hFilter, LPFILTEROBJECT lpFilterObject );

extern VOID     WINAPI FilterFlushBits(HFILTER hFilter);

extern DWORD    WINAPI FilterFrame(HFRAME hFrame, HFILTER hFilter, HCAPTURE hCapture);
    // returns -1 == check BH set last error
    //          0 == FALSE
    //          1 == TRUE

DWORD WINAPI FilterFindFrame (  HFILTER     hFilter,
                                HCAPTURE    hCapture,
                                DWORD       nFrame,
                                STATUSPROC  StatusProc,
                                DWORD       UIInstance,
                                DWORD       TimeDelta,
                                BOOL        FilterDirection );

HFRAME FilterFindPropertyInstance ( HFRAME          hFrame, 
                                    HFILTER         hMasterFilter, 
                                    HCAPTURE        hCapture,
                                    HFILTER         hInstanceFilter,
                                    LPPROPERTYINST	*lpPropRestartKey,
                                    STATUSPROC      StatusProc,
                                    DWORD           UIInstance,
                                    DWORD           TimeDelta,
                                    BOOL            FilterForward );


extern VOID WINAPI SetCurrentFilter(HFILTER);
extern HFILTER  WINAPI GetCurrentFilter(VOID);



#endif
