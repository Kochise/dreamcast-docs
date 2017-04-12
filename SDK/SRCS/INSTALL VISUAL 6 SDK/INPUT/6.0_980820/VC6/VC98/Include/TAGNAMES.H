// --tagnames.h-------------------------------------------------
// 
// Tag strings used for 822-style header output.
//
// Copyright (C) Microsoft Corp., 1986-1996.  All rights reserved.
//
// -------------------------------------------------------------

#ifndef _TAGNAMES_H
#define _TAGNAMES_H

#ifdef __cplusplus

// convenient size constants
const ULONG     ulMaxOutStringLen   =   (80 + 1);   // maximum length of output strings
const ULONG     ulMaxIDLen          =   255;        // maximum UID length
const ULONG     ulMinIDLen          =   4;          // minimum UID length
const UINT      cbDateTimeString    =   (28 + 1);   // length of date time string

// convenient string constants
const LPCSTR   lpszNewLine         =   "\r\n";// blank line
const LPCSTR   lpszNullData        =   "";    // null data
const LPCSTR   lpszBlank           =   "";    // empty string
const LPCSTR   lpszColon           =   ":";   // colon string
const LPCSTR   lpszSpace           =   " ";   // space string
const LPCSTR   lpszUniversalTime   =   " UT"; // universal time string
const LPCSTR   lpszMTAName         =   "/M="; // MTA name prefix
const LPCSTR   lpszPRMDId          =   "/P="; // PRMD name prefix
const LPCSTR   lpszADMDName        =   "/A="; // ADMD name prefix
const LPCSTR   lpszCountry         =   "/C="; // country name prefix
const LPCSTR   lpszCountryEnd      =   "/;";  // country name postfix

// Month abbreviations
const LPCSTR   lpszSundayA         =   "Sun, ";
const LPCSTR   lpszMondayA         =   "Mon, ";
const LPCSTR   lpszTuesdayA        =   "Tue, ";
const LPCSTR   lpszWednesdayA      =   "Wed, ";
const LPCSTR   lpszThursdayA       =   "Thu, ";
const LPCSTR   lpszFridayA         =   "Fri, ";
const LPCSTR   lpszSaturdayA       =   "Sat, ";

const LPCWSTR  lpszSundayW         =   L"Sun, ";
const LPCWSTR  lpszMondayW         =   L"Mon, ";
const LPCWSTR  lpszTuesdayW        =   L"Tue, ";
const LPCWSTR  lpszWednesdayW      =   L"Wed, ";
const LPCWSTR  lpszThursdayW       =   L"Thu, ";
const LPCWSTR  lpszFridayW         =   L"Fri, ";
const LPCWSTR  lpszSaturdayW       =   L"Sat, ";

// Day of week abbreviations
const LPCSTR   lpszJanuaryA        =   "Jan ";
const LPCSTR   lpszFebruaryA       =   "Feb ";
const LPCSTR   lpszMarchA          =   "Mar ";
const LPCSTR   lpszAprilA          =   "Apr ";
const LPCSTR   lpszMayA            =   "May ";
const LPCSTR   lpszJuneA           =   "Jun ";
const LPCSTR   lpszJulyA           =   "Jul ";
const LPCSTR   lpszAugustA         =   "Aug ";
const LPCSTR   lpszSeptemberA      =   "Sep ";
const LPCSTR   lpszOctoberA        =   "Oct ";
const LPCSTR   lpszNovemberA       =   "Nov ";
const LPCSTR   lpszDecemberA       =   "Dec ";

const LPCWSTR  lpszJanuaryW        =   L"Jan ";
const LPCWSTR  lpszFebruaryW       =   L"Feb ";
const LPCWSTR  lpszMarchW          =   L"Mar ";
const LPCWSTR  lpszAprilW          =   L"Apr ";
const LPCWSTR  lpszMayW            =   L"May ";
const LPCWSTR  lpszJuneW           =   L"Jun ";
const LPCWSTR  lpszJulyW           =   L"Jul ";
const LPCWSTR  lpszAugustW         =   L"Aug ";
const LPCWSTR  lpszSeptemberW      =   L"Sep ";
const LPCWSTR  lpszOctoberW        =   L"Oct ";
const LPCWSTR  lpszNovemberW       =   L"Nov ";
const LPCWSTR  lpszDecemberW       =   L"Dec ";

// Trace action strings
const LPCSTR   lpszExpanded        =   "Expanded";
const LPCSTR   lpszRedirected      =   "Redirected";
const LPCSTR   lpszRelayed         =   "Relayed";
const LPCSTR   lpszRerouted        =   "Rerouted";

// priority strings
const LPCSTR   lpszNonUrgent       =   "Non-Urgent";
const LPCSTR   lpszNormalUrgency   =   "Normal";
const LPCSTR   lpszUrgent          =   "Urgent";

// importance strings
const LPCSTR   lpszLowImp          =   "Low";
const LPCSTR   lpszNormalImp       =   "Normal";
const LPCSTR   lpszHighImp         =   "High";

// Common character constants
const CHAR chColon           =   ':';
const CHAR chReturn          =   '\r';
const CHAR chNewLine         =   '\n';
const CHAR chSpace           =   ' ';
const CHAR chForwardSlash    =   '/';
const CHAR chNull            =   '\0';   // used for null data

// "Tag" strings
const LPCSTR lpszTagTnefAttach     =    "X-Tnef-Attach";
const LPCSTR lpszTagMailFrom       =    "MAIL FROM";
const LPCSTR lpszTagRcptTo         =    "RCPT TO";
const LPCSTR lpszTagData           =    "DATA:\r\n";
const LPCSTR lpszTagMsgClass       =    "X-Message-Class";
const LPCSTR lpszTagDate           =    "Date";
const LPCSTR lpszTagMsgID          =    "X-Message-ID";
const LPCSTR lpszTagExternalRcvdBy =    "External-Received-By";
const LPCSTR lpszTagExternalRcvdAt =    "External-Received-At";
const LPCSTR lpszTagExternalAttmBy =    "External-Attempted-By";
const LPCSTR lpszTagExternalDefdAt =    "External-Deferred-At";
const LPCSTR lpszTagInternalRcvdBy =    "Internal-Received-By";
const LPCSTR lpszTagInternalRcvdAt =    "Internal-Received-At";
const LPCSTR lpszTagInternalAttmBy =    "Internal-Attempted-By";
const LPCSTR lpszTagInternalDefdAt =    "Internal-Deferred-At";
const LPCSTR lpszTagFrom           =    "From";
const LPCSTR lpszTagTo             =    "TO";
const LPCSTR lpszTagCC             =    "CC";
const LPCSTR lpszTagBCC            =    "BCC";
const LPCSTR lpszTagSubject        =    "Subject";
const LPCSTR lpszTagPriority       =    "Priority";
const LPCSTR lpszTagImportance     =    "Importance";
const LPCSTR lpszTagBodyHdr        =    "----beginbody";
const LPCSTR lpszTagBodyEnd        =    "\r\n----endbody\r\n";
const LPCSTR lpszTagAttachHdr      =    "----beginattach";
const LPCSTR lpszTagAttachEnd      =    "\r\n----endattach\r\n";
const LPCSTR lpszTagSubjectID      =    "X-Message-Subject-ID";
const LPCSTR lpszTagNotSentTo      =    "Your message was not delivered to";
const LPCSTR lpszTagReason         =    "for the following reason";
const LPCSTR lpszTagDiagCode       =    "Diagnostic code";
const LPCSTR lpszTagNDRCode        =    "NDR code";
const LPCSTR lpszTagSentTo         =    "Your message was successfully delivered to";
const LPCSTR lpszTagAtTime         =    "at";
const LPCSTR lpszTagReadBy         =    "Your message was read by";
const LPCSTR lpszTagNotReadBy      =    "Your message was not read by";
const LPCSTR lpszTagDiscCode       =    "Discard code";
const LPCSTR lpszTagNRNCode        =    "Non-receipt code";
const LPCSTR lpszTagTnefHdr        =    "MAPIMAIL.DAT";

// Convenient functional macros
inline VOID AddSpace(LPSTR lpsz)   { strcat(lpsz, lpszSpace); }    // space
inline VOID AddColon(LPSTR lpsz)   { strcat(lpsz, lpszColon); }    // time separator

// Look up table size and offset constants.
const UINT  nDays            =   7;  // 7 days per week
const UINT  nMonths          =   12; // 12 months per year
const UINT  nActions         =   4;  // number of trace entry actions
const UINT  nActOffset       =   2;  // trace entry action "offset" from 0
const UINT  nPriorities      =   3;  // number of priority values
const UINT  nPrioOffset      =   1;  // priority value "offset" from 0
const UINT  nImportances     =   3;  // number of importance values

// Look up tables

// $--STRINGVALUEPAIR----------------------------------------------------------
//
// A paired string and integer value.
//
// ----------------------------------------------------------------------------
typedef struct
{
    LONG    lValue;        // integer value
    LPCWSTR lpszString;    // string value
} STRINGVALUEPAIRW;

typedef struct
{
    LONG    lValue;        // integer value
    LPCSTR  lpszString;    // string value
} STRINGVALUEPAIRA;

#ifdef UNICODE
#define STRINGVALUEPAIR STRINGVALUEPAIRW
#else
#define STRINGVALUEPAIR STRINGVALUEPAIRA
#endif

#endif  // __cplusplus

#endif
