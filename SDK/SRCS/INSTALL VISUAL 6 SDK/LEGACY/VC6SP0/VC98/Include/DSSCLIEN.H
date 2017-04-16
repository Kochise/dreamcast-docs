#ifndef DSSCLIENT_H
#define DSSCLIENT_H
// DSSCLIENT.H
//
// Application-level constants and data structure definitions for DSS applications
//  on the broadcast PC platform.
//
//  Copyright (c) 1996 - 1997 Microsoft Corp
//  All rights reserved.

// Upper edge events

typedef double NDCDATE;            // from WTYPES.H

// Upper edge purchase details

typedef struct BPCDetails {
    SHORT   iChannel;       // channel number.  Might not be in tunable range
    NDCDATE tStartTime;     // starting time
    NDCDATE tExpiry;        // from HPO as two fields (for offers only)
    LONG    lDuration;      // program item duration in seconds
    LONG    iItemID;        // provider-supplied item identifier
    LONG    iLocation;      // for DSS, is transponder of PIP
    LONG    lUserId;        // for DSS, is CAM ID (history use, only)
    LONG    iStorageId;     // provider-specific storage identifier
    BSTR    szTitle;        // title.
    LONG    iRating;        // event rating
    BSTR    szYear;         // item year as string for UI
    BSTR    szDescription;  // Description string
    CURRENCY ViewCost;      // event cost in units of smallest currency
    CURRENCY TapeCost;      // event cost to tape
    PURCHASEACTION iAction; // Action/Status of item (see below)
    LONG    lStatus;        // bitmask indicator of item status
    LONG    iReason;        // explanation for service denial/error
    BSTR    szReason;       // text expression of iReason
    BSTR    rgbCwpBuffer;   // storage for encrypted cwp (DSS)
#ifdef __cplusplus
    inline BPCDetails() {
        memset(this, 0, sizeof(*this));
        iRating = -1;  // make sure we know this didn't come from verifier
    }
    inline BPCDetails(const BPCDetails &det) {
        // shallow copy everything
        memcpy(this, &det, sizeof(*this));
        // deep copy the allocated structures
        if (det.szDescription) szDescription = ::SysAllocString(det.szDescription);
        if (det.szYear) szYear = ::SysAllocString(det.szYear);
        if (det.szTitle) szTitle = ::SysAllocString(det.szTitle);
        if (det.szReason) szReason = ::SysAllocString(det.szReason);
        if (det.rgbCwpBuffer) rgbCwpBuffer  = ::SysAllocString(det.rgbCwpBuffer);
    }
    inline ~BPCDetails() {
        if (szDescription) ::SysFreeString(szDescription);
        if (szYear) ::SysFreeString(szYear);
        if (szTitle) ::SysFreeString(szTitle);
        if (szReason) ::SysFreeString(szReason);
        if (rgbCwpBuffer) ::SysFreeString(rgbCwpBuffer);
#ifdef _DEBUG
        memset(this, 0, sizeof(*this));
#endif
    }
    inline BPCDetails &operator=(const BPCDetails &det) {
        if (this != &det) {
            // shallow copy everything
            memcpy(this, &det, sizeof(*this));
            // deep copy the allocated structures
            if (det.szDescription) szDescription = ::SysAllocString(det.szDescription);
            if (det.szYear) szYear = ::SysAllocString(det.szYear);
            if (det.szTitle) szTitle = ::SysAllocString(det.szTitle);
            if (det.szReason) szReason = ::SysAllocString(det.szReason);
            if (det.rgbCwpBuffer) rgbCwpBuffer  = ::SysAllocString(det.rgbCwpBuffer);
        }
        return *this;
    }
    inline bool operator==(const BPCDetails &det) const {
        return (iItemID == det.iItemID && iStorageId == det.iStorageId);
    }
    inline bool operator!=(const BPCDetails &det) const {
        return !(det == *this);
    }
    inline bool operator<(const BPCDetails &det) const {
        return (iItemID < det.iItemID || (iItemID == det.iItemID && iStorageId < det.iStorageId));
    }
    inline bool operator>(const BPCDetails &det) const {
        return (iItemID > det.iItemID || (iItemID == det.iItemID && iStorageId > det.iStorageId));
    }

#endif
} BPCDETAILS, *LPBPCDETAILS;

typedef struct ProviderMsg {
    LONG    iMsgId;                 // used for association
    BOOL    fIsRead;                // nonzero if read by user
    LONG    lUserId;                // for DSS is 4 byte CAM ID
    NDCDATE odDateTimeStamp;        // OLE DATE type
    NDCDATE odExpiry;               // OLE DATE type
    BSTR    szTitle;                // may not be null for tombstone
    BSTR    szMessageText;          // if null, is tombstone
#ifdef __cplusplus
    inline ProviderMsg() {
        memset(this, 0, sizeof(*this));
    }
    inline ProviderMsg(const ProviderMsg &msg) {
        // shallow copy everything
        memcpy(this, &msg, sizeof(*this));
        // deep copy the allocated structures
        if (msg.szTitle) szTitle = ::SysAllocString(msg.szTitle);
        if (msg.szMessageText) szMessageText = ::SysAllocString(msg.szMessageText);
    }
    inline ~ProviderMsg() {
        if (szTitle) ::SysFreeString(szTitle);
        if (szMessageText) ::SysFreeString(szMessageText);
#ifdef _DEBUG
        memset(this, 0, sizeof(*this));
#endif
    }
    inline ProviderMsg &operator=(const ProviderMsg &msg) {
        if (this != &msg) {
            // shallow copy everything
            memcpy(this, &msg, sizeof(*this));
            // deep copy the allocated structures
            if (msg.szTitle) szTitle = ::SysAllocString(msg.szTitle);
            if (msg.szMessageText) szMessageText = ::SysAllocString(msg.szMessageText);
        }
        return *this;
    }
    inline bool operator==(const ProviderMsg &msg) const {
        return (lUserId == msg.lUserId && iMsgId == msg.iMsgId);
    }
    inline bool operator!=(const ProviderMsg &msg) const {
        return !(msg == *this);
    }
    inline bool operator<(const ProviderMsg &msg) const {
        return (lUserId < msg.lUserId || (lUserId == msg.lUserId && iMsgId < msg.iMsgId));
    }
    inline bool operator>(const ProviderMsg &msg) const {
        return (lUserId > msg.lUserId || (lUserId == msg.lUserId && iMsgId > msg.iMsgId));
    }

#endif
} PROVIDERMSG,*LPPROVIDERMSG;

typedef struct ExplicitOsd {
    DWORD   dwAttributes;
    BSTR    bsString;
#ifdef __cplusplus
    inline ExplicitOsd() { memset(this, 0, sizeof(*this)); }
    inline ExplicitOsd(ExplicitOsd &osd) {
        // shallow copy everything
        memcpy(this, &osd, sizeof(*this));
        // deep copy the allocated structures
        if (osd.bsString) bsString = ::SysAllocString(osd.bsString);
    }
    inline ~ExplicitOsd() {
        if (bsString) ::SysFreeString(bsString);
#ifdef _DEBUG
        memset(this, 0, sizeof(*this));
#endif
    }
    inline ExplicitOsd &operator=(ExplicitOsd &osd) {
        if (this != &osd) {
            // shallow copy everything
            memcpy(this, &osd, sizeof(*this));
            // deep copy the allocated structures
            if (osd.bsString) bsString = ::SysAllocString(osd.bsString);
        }
        return *this;
    }
#endif
} EXPLICITOSD,*LPEXPLICITOSD;

#endif

// End of Source File
