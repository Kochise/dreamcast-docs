Attribute VB_Name = "OBJECTTY"
Option Explicit
'// *************************************************************************
'//
'//  File: OBJECTTY.H
'//
'//  Copyright (c) 1994, 1995 Microsoft Corp.
'//
'//  This is the header file for the obejctity engine. The objectity
'//  engine is the core of the SMS API set.
'//
'//  This file contains externally visible structures, and certain manifests
'//  needed by them.
'//
'//
'// *************************************************************************
'//
'
'// ====================================================================
'//
'//      Manifests.
'//
'// ====================================================================
'
'typedef DWORD   SMS_STATUS;         // API return codes are all of this type.
'/* VB: All API's return Long  */
'
 Global Const F_ANY = 0              'Indicates any folder type
'
'
'// ====================================================================
'//  Scalar values can be strings, integers (DWORDs), time, or binary.
'//NOTE: binary not yet implemented.
'// ====================================================================
 Type SCALARTYPE
     enum As Long
 End Type
 
 ' These are initialized in Init_SCALARTYPE_enums()
 Global SCALAR_STRING As SCALARTYPE
 Global SCALAR_INT As SCALARTYPE
 Global SCALAR_TIME As SCALARTYPE
 Global SCALAR_BINARY As SCALARTYPE
'
'
'// ====================================================================
'//      SCALAR
'//  This structure is used by the application and the engine to
'//  communicate a scalar's details.
'//
'//  All scalars have a type (SCALARTYPE), a name (a character string),
'//  and a value, which is determined by the scalar's type.
'//  There are separate fields here for the value in all its guises.
'//  Additionally, if the scalar is a string or a binary, a length
'//  field indicates the datum's size.
'//
'//  This length field can also be set by the application when
'//  retrieving a scalar. In this case it indicates the size of the
'//  receiving buffer (string and binary).
'//
'// ====================================================================
 Type SCALAR
     scType As SCALARTYPE       '// string, int, time etc
     pszName As String          '// Scalar name.
     pszValue As String         '// Scalar value as a string.
     dwValue As Long            '// Scalar value as a DWORD.
     tValue As Long             '// Scalar value as a time.
     pValue() As Byte           '// Scalar as a binary.
     dwLen As Long              '// Size of the scalar value either as a string
                                '// or as a binary.
                                '// If a get scalar API is called with NULL
                                '// for the appropriate value, then the
                                '// length of that value is returned here.
     bStringEquivalence As Long
                                '// True if a string exists for an INT or
                                '// TIME scalar. String will be in pszValue.
     fAccess As Long            '// Access mode.
 End Type
'
'
'
'
'// --------------------------------------------------------------------
'// Manifests used in filter token APIs.
'// --------------------------------------------------------------------
 Global Const OTT_AT_START = -1 '// Token will be inserted at start of
                                '// expression.
 Global Const OTT_AT_END = -2   '// Token will be appended to end of
                                '// expression.
'
'
'
'
'// ====================================================================
'//
'//  Return codes from the objectity engine.
'//
'// ====================================================================
 Global Const OTT_OK = 0
 Global Const OTT_MORE_DATA = 1
 Global Const OTT_NO_MORE_DATA = 2
 Global Const OTT_FOLDER_NO_UPDATE = 3
 Global Const OTT_DUPLICATE_CONTAINER_ID = 4
 Global Const OTT_DUPLICATE_FOLDER_ID = 5
 Global Const OTT_DUPLICATE_FILTER_ID = 6
 Global Const OTT_SCALAR_NO_UPDATE = 7
 Global Const OTT_SCALAR_WRONG_TYPE = 8
 Global Const OTT_INVALID_CONTAINER_ID = 9
 Global Const OTT_INVALID_FOLDER_ID = 10
 Global Const OTT_INVALID_FILTER_ID = 11
'
 Global Const OTT_CONTAINER_NO_UPDATE = 12
'
 Global Const OTT_PARAMETER_ERROR = 13
 Global Const OTT_UNSUPPORTED = 14
 Global Const OTT_NOT_FOUND = 15
 Global Const OTT_PARENT_NOT_FOUND = 16
 Global Const OTT_CANT_DELETE = 17
 Global Const OTT_NEW_FOLDER = 18
'
'// Error when attempting to multiply link a folder.
 Global Const OTT_FOLDER_LINKED = 19
'
'//
'// Filter operations.
 Global Const OTT_RANGE_ERROR = 20
'
 Global Const OTT_DUPLICATE_FILTER = 21
'
'// Container operations that are out of sequence.
 Global Const OTT_CONTAINER_NOT_POPULATED = 22
 Global Const OTT_CONTAINER_POPULATED = 23
'
'// Only persistent filters have scalars.
 Global Const OTT_FILTER_NOT_PERSISTENT = 24
'
'// Error return if the connection handle of a filter doesn't match
'// that of a container to which the filter is being applied.
 Global Const OTT_INVALID_CONNECTION_HANDLE = 25

 Global Const OTT_INVALID_FILTER_TYPE = 26
'
'// Folder's can't be unlinked if there are multiple handles
'// to the same object.
 Global Const OTT_IN_USE_BY_OTHER = 27
'
'
'// The last one, user codes start from here to give
'// leaway for future expansion.
'//
 Global Const OTT_END = 50
'
'
'// ====================================================================
'//
'//  Other manifests.
'//
'// ====================================================================
'
'// Access rights to containers/folders/scalars.
'// -------------------------------------------------------------
 Global Const ACCESS_READ = &H1
 Global Const ACCESS_CREATE = &H2
 Global Const ACCESS_MODIFY = &H4
 Global Const ACCESS_DELETE = &H8
'
'// Modification flags
'// ------------------
 Global Const MOD_UNMODIFIED = &H0
 Global Const MOD_CREATED = &H1
 Global Const MOD_DELETED = &H2
 Global Const MOD_DENY_ACCESS = &H4
'
'// Tokens are ANDed or ORed into filters.
'// -------------------------------------------------------------
 Type ANDOR
     enum As Long
 End Type
 
 ' These are initialized in Init_ANDOR_enums()
 Global OP_AND As ANDOR
 Global OP_OR As ANDOR
'
'// Options for Rewind on a folder.
'// -------------------------------------------------------------
 Global Const RW_FOLDER = &H80000000      '// Rewind folder lists.
 Global Const RW_SCALAR = &H40000000      '// Rewind scalar list only.
 Global Const RW_ALL = RW_FOLDER + RW_SCALAR ' // Rewind both.
'
'
'
'
'
'
'
'// These structures are used to retrieve container and filter
'// information from the engine.
'// These are used in enumertaing containers and filters.
'// -------------------------------------------------------------
 Global Const BUFF_SIZE = 256
'
'
'// An objectity is either a container or a folder.
'// -------------------------------------------------------------
 Type BASETYPE
     enum As Long
 End Type

 ' These are initialized in Init_BASETYPE_enums()
 Global T_CONTAINER As BASETYPE
 Global T_FOLDER As BASETYPE
'
'
'// ====================================================================
'//
'//  The structures.
'//
'// ====================================================================
'
'//
'// NOTIFY structure.
'//
'// This struct used for async population. Enables async operation to
'// use either event handle or window handle/message.
'
 Type NOTIFY
    dwFreq As Long     '// Notify after this number of rows retrieved.
    hEvent As Long     '// Event handle if type=POP_EVENT
    hwnd As Long       '// hwnd if type=POP_WINDOW
    uiMsg As Long      '// Message if type=POP_WINDOW
 End Type
'
'
'//
'// TOKEN structure.
'//
 Global Const TOKEN_STRING_SIZE = 4608 '// 4.5k
'// The manifest is this large because it can used in the package inventory
'// rules. In these rules we are allowed to define upto four string fields,
'// each of which can be 1k long. This size allows us to accommodate it all.
'
 Type TOKEN
     tokenType As Long            '// Returns: type of token (ie USER, AND,
                                         '// OR, LEFT_PAREN, RIGHT_PAREN).
     szName As String
     szValue As String
     dwOp As Long
 
     szArchitecture As String
     szGroupClass As String
     szAttributeName As String
     szTokenString As String           '// Display form of the token.
     bIndent As Long                   '// Request display indentation.
 End Type
'
'
'
'//
'// FILTER_INFO
'//
'//  This structure is used to provide the user a filter template.
'//  An array of these structures is returned via the SmsEnumFilters API.
'//  This returns information about all filters registered with the engine.
'//
'//  It is considered that the user will use this information in order to
'//  display information. The information that is provided here is:
'//  a) the type and tag of the filter, b) the fields that comprise a
'//  particular filter's tokens, and c) the names that should be used
'//  for these fields for display purposes. That is, for a GUI application,
'//  they provide the labels for edit controls. If a field in the structure
'//  is empty (ie NULL) then that field is not used for that particular
'//  filter.
'//
'//  As an example consider a group filter. If the developer wants to
'//  present, say, a dialogue box to the end user, they would use the
'//  following fields: szName, szValue. Looking at the template they
'//  will see that the strings associated with these fields are 'Name'
'//  and 'GroupClass'. They would thus display a dialogue box with
'//  two edit controls, the first labelled 'Name', the second labelled
'//  'GroupClass. Since these are the only two fields that are filled in
'//  no other fields should be presented to the user.
'//
'//NOTE: what about default values?
'//
'//  Job filter:
'//      szName          = 'Type'
'//      szValue         = 'Value'
'//      szOperator      = 'Operator'
'//
'//  Machine filter:
'//      szArchitecture  = 'Architecture'
'//      szGroupClass    = 'GroupClass'
'//      szAttributeName = 'Attribute name'
'//      szValue         = 'Value'
'//      szOperator      = 'Operator'
'//
'//  Site filter:
'//      szName          = 'Type'
'//      szValue         = 'Site code'
'//      szOperator      = 'Operator'
'//
'//  Group filter:
'//      szName          = 'Name'
'//      szValue         = 'GroupClass'
'//      szOperator      = 'Operator'
'//
'//  Architecture filter:
'//      szName          = 'Name'
'//      szValue         = 'Architecture'
'//      szOperator      = 'Operator'
'//
'//  Package filter:
'//      szName          = 'Type'
'//      szValue         = 'Value'
'//      szOperator      = 'Operator'
'//
'//  Attribute filter:
'//      szArchitecture  = 'Architecture'
'//      szGroupClass    = 'GroupClass'
'//      szAttributeName = 'Attribute name'
'//
'//  SiteLimit filter:
'//      szName          = 'Site'
'//      szValue         = 'Domain'
'//
'//
 Global Const NAME_SIZE = 52
'
 Type FILTER_INFO
     szTag As String                 '// Filter tag (eg "Architecture filter").
'     tokenType As Integer
     filterType As Long              '// Type number (eg ARCHITECTURE_FILTER).
 
     szName As String
     szValue As String
     szOperator As String
 
     szArchitecture As String
     szGroupClass As String
     szAttributeName As String
 End Type
'
'
'
'// This is what the user gets as a description of a scalar.
'// Currently this is only used internally in objectty.cpp (RegisterObjectity).
'// I'll proably make this externally visible though very soon now.
 Type SCALAR_INFO
     szName As String                '// Scalar's name.
     scType As SCALARTYPE            '// Type: SCALAR_STRING, INT, TIME etc
     fAccess As Long                 '// Access mode: ACCESS_READ, MODIFY etc
 End Type
'
'
'// Now the C struct form of CFolderInfo. This is what we'll
'// return in a call to DescribeFolder().
'// This is created during a call to RegisterObjectity. It is stored
'// in the CFolderInfo object, itself held in the Folder registry.
'// 29-Sep-94. Expanded to deal with Containers as well as folders.
'
'
 Type FOLDER_INFO
     tObjectity As BASETYPE          '// T_CONTAINER or T_FOLDER.
     pszTag As String
     dwTag As Long
 
     ctFolders As Long
     FolderTags() As Long
 
     ctFilters As Long
     FilterTags() As Long
 
     ctScalars As Long               '// Not used by for containers.
     Scalars() As SCALAR_INFO        '// ditto.
 
     NewFunc As Long                 '// needs cast!! Used when registering
                                     '// a container. This is a pointer to
                                     '// the container's 'new' function.
 End Type

 Sub Init_ANDOR_enums()
     OP_AND.enum = 3
     OP_OR.enum = 2
 End Sub

 Sub Init_BASETYPE_enums()
     T_CONTAINER.enum = 0
     T_FOLDER.enum = 1
 End Sub

 Sub Init_OBJECTTY()
     Init_SCALARTYPE_enums
     Init_ANDOR_enums
     Init_BASETYPE_enums
 End Sub

 Sub Init_SCALARTYPE_enums()
     SCALAR_STRING.enum = 0
     SCALAR_INT.enum = 1
     SCALAR_TIME.enum = 2
     SCALAR_BINARY.enum = 3
 End Sub

