// *************************************************************************
//
//  File: OBJECTTY.H
//
//  Copyright (c) 1994, 1995 Microsoft Corp.
//
//  This is the header file for the obejctity engine. The objectity
//  engine is the core of the SMS API set.
//
//  This file contains externally visible structures, and certain manifests
//  needed by them.
//
//
// *************************************************************************
//

#ifndef _OBJECTITY_H_
#define _OBJECTITY_H_

// ====================================================================
//
//      Manifests.
//
// ====================================================================

typedef DWORD   SMS_STATUS;         // API return codes are all of this type.

#define F_ANY   0                   // Indicates any folder type.


// ====================================================================
//  Scalar values can be strings, integers (DWORDs), time, or binary.
//NOTE: binary not yet implemented.
// ====================================================================
typedef enum {
    SCALAR_STRING,
    SCALAR_INT,
    SCALAR_TIME,
    SCALAR_BINARY
} SCALARTYPE;


// ====================================================================
//      SCALAR
//  This structure is used by the application and the engine to
//  communicate a scalar's details.
//
//  All scalars have a type (SCALARTYPE), a name (a character string),
//  and a value, which is determined by the scalar's type.
//  There are separate fields here for the value in all its guises.
//  Additionally, if the scalar is a string or a binary, a length
//  field indicates the datum's size.
//
//  This length field can also be set by the application when
//  retrieving a scalar. In this case it indicates the size of the
//  receiving buffer (string and binary).
//
// ====================================================================
typedef struct _SCALAR {
    SCALARTYPE scType;          // string, int, time etc
    char *pszName;              // Scalar name.
    char *pszValue;             // Scalar value as a string.
    DWORD dwValue;              // Scalar value as a DWORD.
    time_t tValue;              // Scalar value as a time.
    void *pValue;               // Scalar as a binary.
    DWORD dwLen;                // Size of the scalar value either as a string
                                // or as a binary.
                                // If a get scalar API is called with NULL
                                // for the appropriate value, then the
                                // length of that value is returned here.
    BOOL bStringEquivalence;    // True if a string exists for an INT or
                                // TIME scalar. String will be in pszValue.
    DWORD fAccess;              // Access mode.
} SCALAR;




// --------------------------------------------------------------------
// Manifests used in filter token APIs.
// --------------------------------------------------------------------
#define OTT_AT_START    -1              // Token will be inserted at start of
                                        // expression.
#define OTT_AT_END      -2              // Token will be appended to end of
                                        // expression.



// ====================================================================
//
//  Return codes from the objectity engine.
//
// ====================================================================
#define OTT_OK                      0
#define OTT_MORE_DATA               1
#define OTT_NO_MORE_DATA            2
#define OTT_FOLDER_NO_UPDATE        3
#define OTT_DUPLICATE_CONTAINER_ID  4
#define OTT_DUPLICATE_FOLDER_ID     5
#define OTT_DUPLICATE_FILTER_ID     6
#define OTT_SCALAR_NO_UPDATE        7
#define OTT_SCALAR_WRONG_TYPE       8
#define OTT_INVALID_CONTAINER_ID    9
#define OTT_INVALID_FOLDER_ID       10
#define OTT_INVALID_FILTER_ID       11

#define OTT_CONTAINER_NO_UPDATE     12

#define OTT_PARAMETER_ERROR         13
#define OTT_UNSUPPORTED             14
#define OTT_NOT_FOUND               15
#define OTT_PARENT_NOT_FOUND        16
#define OTT_CANT_DELETE             17
#define OTT_NEW_FOLDER              18

// Error when attempting to multiply link a folder.
#define OTT_FOLDER_LINKED           19

//
// Filter operations.
#define OTT_RANGE_ERROR             20

#define OTT_DUPLICATE_FILTER        21

// Container operations that are out of sequence.
#define OTT_CONTAINER_NOT_POPULATED 22
#define OTT_CONTAINER_POPULATED     23

// Only persistent filters have scalars.
#define OTT_FILTER_NOT_PERSISTENT   24

// Error return if the connection handle of a filter doesn't match
// that of a container to which the filter is being applied.
#define OTT_INVALID_CONNECTION_HANDLE 25

#define OTT_INVALID_FILTER_TYPE     26

// Folder's can't be unlinked if there are multiple handles
// to the same object.
#define OTT_IN_USE_BY_OTHER         27


// The last one, user codes start from here to give
// leaway for future expansion.
//
#define OTT_END                     50


// ====================================================================
//
//  Other manifests.
//
// ====================================================================

// Access rights to containers/folders/scalars.
// -------------------------------------------------------------
#define ACCESS_READ                 0x0001
#define ACCESS_CREATE               0x0002
#define ACCESS_MODIFY               0x0004
#define ACCESS_DELETE               0x0008

// Modification flags
// ------------------
#define MOD_UNMODIFIED              0x0000
#define MOD_CREATED                 0x0001
#define MOD_DELETED                 0x0002
#define MOD_DENY_ACCESS             0x0004

// Tokens are ANDed or ORed into filters.
// -------------------------------------------------------------
typedef enum { OP_AND = 0x03, OP_OR = 0x02 } ANDOR;


// Options for Rewind on a folder.
// -------------------------------------------------------------
#define RW_FOLDER               0x080000000       // Rewind folder lists.
#define RW_SCALAR               0x040000000       // Rewind scalar list only.
#define RW_ALL                  (RW_FOLDER | RW_SCALAR) // Rewind both.







// These structures are used to retrieve container and filter
// information from the engine.
// These are used in enumertaing containers and filters.
// -------------------------------------------------------------
#define BUFF_SIZE 256


// An objectity is either a container or a folder.
// -------------------------------------------------------------
typedef enum {
    T_CONTAINER,
    T_FOLDER
} BASETYPE;



// ====================================================================
//
//  The structures.
//
// ====================================================================

//
// NOTIFY structure.
//
// This struct used for async population. Enables async operation to
// use either event handle or window handle/message.

typedef struct _NOTIFY {
    DWORD dwFreq;       // Notify after this number of rows retrieved.
    HANDLE hEvent;      // Event handle if type=POP_EVENT
    HWND hwnd;          // hwnd if type=POP_WINDOW
    UINT uiMsg;         // Message if type=POP_WINDOW
} NOTIFY;


//
// TOKEN structure.
//
#define TOKEN_STRING_SIZE   4608    // 4.5k
// The manifest is this large because it can used in the package inventory
// rules. In these rules we are allowed to define upto four string fields,
// each of which can be 1k long. This size allows us to accommodate it all.

typedef struct _TOKEN {
    INT tokenType;                  // Returns: type of token (ie USER, AND,
                                        // OR, LEFT_PAREN, RIGHT_PAREN).
    char  szName[BUFF_SIZE];
    char  szValue[BUFF_SIZE];
    DWORD dwOp;

    char  szArchitecture[BUFF_SIZE];
    char  szGroupClass[BUFF_SIZE];
    char  szAttributeName[BUFF_SIZE];
    char  szTokenString[TOKEN_STRING_SIZE]; // Display form of the token.
    BOOL  bIndent;                  // Request display indentation.
} TOKEN;



//
// FILTER_INFO
//
//  This structure is used to provide the user a filter template.
//  An array of these structures is returned via the SmsEnumFilters API.
//  This returns information about all filters registered with the engine.
//
//  It is considered that the user will use this information in order to
//  display information. The information that is provided here is:
//  a) the type and tag of the filter, b) the fields that comprise a
//  particular filter's tokens, and c) the names that should be used
//  for these fields for display purposes. That is, for a GUI application,
//  they provide the labels for edit controls. If a field in the structure
//  is empty (ie NULL) then that field is not used for that particular
//  filter.
//
//  As an example consider a group filter. If the developer wants to
//  present, say, a dialogue box to the end user, they would use the
//  following fields: szName, szValue. Looking at the template they
//  will see that the strings associated with these fields are 'Name'
//  and 'GroupClass'. They would thus display a dialogue box with
//  two edit controls, the first labelled 'Name', the second labelled
//  'GroupClass. Since these are the only two fields that are filled in
//  no other fields should be presented to the user.
//
//
//  Job filter:
//      szName          = 'Type'
//      szValue         = 'Value'
//      szOperator      = 'Operator'
//
//  Machine filter:
//      szArchitecture  = 'Architecture'
//      szGroupClass    = 'GroupClass'
//      szAttributeName = 'Attribute name'
//      szValue         = 'Value'
//      szOperator      = 'Operator'
//
//  Site filter:
//      szName          = 'Type'
//      szValue         = 'Site code'
//      szOperator      = 'Operator'
//
//  Group filter:
//      szName          = 'Name'
//      szValue         = 'GroupClass'
//      szOperator      = 'Operator'
//
//  Architecture filter:
//      szName          = 'Name'
//      szValue         = 'Architecture'
//      szOperator      = 'Operator'
//
//  Package filter:
//      szName          = 'Type'
//      szValue         = 'Value'
//      szOperator      = 'Operator'
//
//  Attribute filter:
//      szArchitecture  = 'Architecture'
//      szGroupClass    = 'GroupClass'
//      szAttributeName = 'Attribute name'
//
//  SiteLimit filter:
//      szName          = 'Site'
//      szValue         = 'Domain'
//
//
#define NAME_SIZE   52

typedef struct _FILTER_INFO {
    char  szTag[NAME_SIZE];         // Filter tag (eg "Architecture filter").
    DWORD filterType;               // Type number (eg ARCHITECTURE_FILTER).

    // The filter descriptor information.
    char szName[NAME_SIZE];
    char szValue[NAME_SIZE];
    char szOperator[NAME_SIZE];

    char szArchitecture[NAME_SIZE];
    char szGroupClass[NAME_SIZE];
    char szAttributeName[NAME_SIZE];
} FILTER_INFO;



// This is what the user gets as a description of a scalar.
// Currently this is only used internally in objectty.cpp (RegisterObjectity).
// I'll proably make this externally visible though very soon now.
typedef struct _SCALAR_INFO {
    char szName[BUFF_SIZE];         // Scalar's name.
    SCALARTYPE scType;              // Type: SCALAR_STRING, INT, TIME etc
    DWORD fAccess;                  // Access mode: ACCESS_READ, MODIFY etc
} SCALAR_INFO;


// Now the C struct form of CFolderInfo. This is what we'll
// return in a call to DescribeFolder().
// This is created during a call to RegisterObjectity. It is stored
// in the CFolderInfo object, itself held in the Folder registry.
// 29-Sep-94. Expanded to deal with Containers as well as folders.


typedef struct _FOLDER_INFO {
    BASETYPE tObjectity;            // T_CONTAINER or T_FOLDER.
    char *pszTag;
    DWORD dwTag;

    DWORD ctFolders;
    DWORD *pFolderTags;

    DWORD ctFilters;
    DWORD *pFilterTags;

    DWORD ctScalars;                // Not used by for containers.
    SCALAR_INFO *pScalars;          // ditto.

    void *pNewFunc;                 // needs cast!! Used when registering
                                    // a container. This is a pointer to
                                    // the container's 'new' function.
} FOLDER_INFO;





#endif  // _OBJECTITY_H_

/* EOF: objectty.h */

