Attribute VB_Name = "ADsConst"
''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''
' Active Directory Service Interfaces 1.0
'
' Copyright (c) 1995-1997  Microsoft Corporation
'
' ADsConst.Bas - Error codes, Status codes, Class names and
'                Schema definitions for ADSI.
'

'''''''''''''''''''''''' HRESULT Value Definitions '''''''''''''''''''''''''
'
' HRESULT definitions
'
'  Values are 32 bit values layed out as follows:
'
'   3 3 2 2 2 2 2 2 2 2 2 2 1 1 1 1 1 1 1 1 1 1
'   1 0 9 8 7 6 5 4 3 2 1 0 9 8 7 6 5 4 3 2 1 0 9 8 7 6 5 4 3 2 1 0
'  +---+-+-+-----------------------+-------------------------------+
'  |Sev|C|R|     Facility          |               Code            |
'  +---+-+-+-----------------------+-------------------------------+
'
'  where
'
'      Sev - is the severity code
'
'          00 - Success
'          01 - Informational
'          10 - Warning
'          11 - Error
'
'      C - is the Customer code flag
'
'      R - is a reserved bit
'
'      Facility - is the facility code
'
'      Code - is the facility's status code
'
'
' Note: An error codes of the form &H8007xxxx indicates Win32 error xxxx.
'
''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''
Public Const FACILITY_WINDOWS = 8
Public Const FACILITY_STORAGE = 3
Public Const FACILITY_RPC = 1
Public Const FACILITY_SSPI = 9
Public Const FACILITY_WIN32 = 7
Public Const FACILITY_CONTROL = 10
Public Const FACILITY_NULL = 0
Public Const FACILITY_ITF = 4
Public Const FACILITY_DISPATCH = 2

''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''
'
' MessageId: E_ADS_BAD_PATHNAME
'
' MessageText:
'
'  An invalid OLE DS pathname was passed
'
''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''
Public Const E_ADS_BAD_PATHNAME = &H80005000


''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''
'
' MessageId: E_ADS_INVALID_DOMAIN_OBJECT
'
' MessageText:
'
'  An unknown OLE DS domain object was requested
'
''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''
Public Const E_ADS_INVALID_DOMAIN_OBJECT = &H80005001


''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''
'
' MessageId: E_ADS_INVALID_USER_OBJECT
'
' MessageText:
'
'  An unknown OLE DS user object was requested
'
''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''
Public Const E_ADS_INVALID_USER_OBJECT = &H80005002


''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''
'
' MessageId: E_ADS_INVALID_COMPUTER_OBJECT
'
' MessageText:
'
'  An unknown OLE DS computer object was requested
'
''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''
Public Const E_ADS_INVALID_COMPUTER_OBJECT = &H80005003


''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''
'
' MessageId: E_ADS_UNKNOWN_OBJECT
'
' MessageText:
'
'  An unknown OLE DS object was requested
'
''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''
Public Const E_ADS_UNKNOWN_OBJECT = &H80005004


''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''
'
' MessageId: E_ADS_PROPERTY_NOT_SET
'
' MessageText:
'
'  The specified OLE DS property was not set
'
''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''
Public Const E_ADS_PROPERTY_NOT_SET = &H80005005


''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''
'
' MessageId: E_ADS_PROPERTY_NOT_SUPPORTED
'
' MessageText:
'
'  The specified OLE DS property is not supported
'
''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''
Public Const E_ADS_PROPERTY_NOT_SUPPORTED = &H80005006


''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''
'
' MessageId: E_ADS_PROPERTY_INVALID
'
' MessageText:
'
'  The specified OLE DS property is invalid
'
''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''
Public Const E_ADS_PROPERTY_INVALID = &H80005007


''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''
'
' MessageId: E_ADS_BAD_PARAMETER
'
' MessageText:
'
'  One or more input parameters are invalid
'
''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''
Public Const E_ADS_BAD_PARAMETER = &H80005008


''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''
'
' MessageId: E_ADS_OBJECT_UNBOUND
'
' MessageText:
'
'  The specified OLE DS object is not bound to a remote resource
'
''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''
Public Const E_ADS_OBJECT_UNBOUND = &H80005009


''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''
'
' MessageId: E_ADS_PROPERTY_NOT_MODIFIED
'
' MessageText:
'
'  The specified OLE DS object has not been modified
'
''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''
Public Const E_ADS_PROPERTY_NOT_MODIFIED = &H8000500A


''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''
'
' MessageId: E_ADS_PROPERTY_MODIFIED
'
' MessageText:
'
'  The specified OLE DS object has not been modified
'
''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''
Public Const E_ADS_PROPERTY_MODIFIED = &H8000500B


''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''
'
' MessageId: E_ADS_CANT_CONVERT_DATATYPE
'
' MessageText:
'
'  The OLE DS datatype cannot be converted to/from a native DS datatype
'
''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''
Public Const E_ADS_CANT_CONVERT_DATATYPE = &H8000500C


''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''
'
' MessageId: E_ADS_PROPERTY_NOT_FOUND
'
' MessageText:
'
'  The OLE DS property cannot be found in the cache.
'
''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''
Public Const E_ADS_PROPERTY_NOT_FOUND = &H8000500D


''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''
'
' MessageId: E_ADS_OBJECT_EXISTS
'
' MessageText:
'
'  The OLE DS object exists.
'
Public Const E_ADS_OBJECT_EXISTS = &H8000500E

''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''
'
' MessageId: E_ADS_SCHEMA_VIOLATION
'
' MessageText:
'
'  The attempted action violates the DS schema rules.
'
Public Const E_ADS_SCHEMA_VIOLATION = &H8000500F

''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''
'
' Printer Status Values
'
''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''
Public Const ADS_PRINTER_PAUSED = &H1
Public Const ADS_PRINTER_PENDING_DELETION = &H2
Public Const ADS_PRINTER_ERROR = &H3
Public Const ADS_PRINTER_PAPER_JAM = &H4
Public Const ADS_PRINTER_PAPER_OUT = &H5
Public Const ADS_PRINTER_MANUAL_FEED = &H6
Public Const ADS_PRINTER_PAPER_PROBLEM = &H7
Public Const ADS_PRINTER_OFFLINE = &H8
Public Const ADS_PRINTER_IO_ACTIVE = &H100
Public Const ADS_PRINTER_BUSY = &H200
Public Const ADS_PRINTER_PRINTING = &H400
Public Const ADS_PRINTER_OUTPUT_BIN_FULL = &H800
Public Const ADS_PRINTER_NOT_AVAILABLE = &H1000
Public Const ADS_PRINTER_WAITING = &H2000
Public Const ADS_PRINTER_PROCESSING = &H4000
Public Const ADS_PRINTER_INITIALIZING = &H8000
Public Const ADS_PRINTER_WARMING_UP = &H10000
Public Const ADS_PRINTER_TONER_LOW = &H20000
Public Const ADS_PRINTER_NO_TONER = &H40000
Public Const ADS_PRINTER_PAGE_PUNT = &H80000
Public Const ADS_PRINTER_USER_INTERVENTION = &H100000
Public Const ADS_PRINTER_OUT_OF_MEMORY = &H200000
Public Const ADS_PRINTER_DOOR_OPEN = &H400000
Public Const ADS_PRINTER_SERVER_UNKNOWN = &H800000
Public Const ADS_PRINTER_POWER_SAVE = &H1000000

''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''
'
' Job Status Values
'
''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''
Public Const ADS_JOB_PAUSED = &H1
Public Const ADS_JOB_ERROR = &H2
Public Const ADS_JOB_DELETING = &H4
Public Const ADS_JOB_SPOOLING = &H8
Public Const ADS_JOB_PRINTING = &H10
Public Const ADS_JOB_OFFLINE = &H20
Public Const ADS_JOB_PAPEROUT = &H40
Public Const ADS_JOB_PRINTED = &H80
Public Const ADS_JOB_DELETED = &H100


''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''
'
' Service Status Values
'
''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''
Public Const ADS_SERVICE_STOPPED = &H1
Public Const ADS_SERVICE_START_PENDING = &H2
Public Const ADS_SERVICE_STOP_PENDING = &H3
Public Const ADS_SERVICE_RUNNING = &H4
Public Const ADS_SERVICE_CONTINUE_PENDING = &H5
Public Const ADS_SERVICE_PAUSE_PENDING = &H6
Public Const ADS_SERVICE_PAUSED = &H7
Public Const ADS_SERVICE_ERROR = &H8


''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''
'
' Service Type Valid Values
'
''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''
Public Const ADS_SERVICE_OWN_PROCESS = &H10
Public Const ADS_SERVICE_SHARE_PROCESS = &H20
Public Const ADS_SERVICE_KERNEL_DRIVER = &H1
Public Const ADS_SERVICE_FILE_SYSTEM_DRIVER = &H2


''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''
'
' Start Type Valid Values
'
''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''
Public Const ADS_SERVICE_BOOT_START = &H0
Public Const ADS_SERVICE_SYSTEM_START = &H1
Public Const ADS_SERVICE_AUTO_START = &H2
Public Const ADS_SERVICE_DEMAND_START = &H3
Public Const ADS_SERVICE_DISABLED = &H4
 

''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''
'
' Error Control Values
'
''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''
Public Const ADS_SERVICE_ERROR_IGNORE = 0
Public Const ADS_SERVICE_ERROR_NORMAL = 1
Public Const ADS_SERVICE_ERROR_SEVERE = 2
Public Const ADS_SERVICE_ERROR_CRITICAL = 3

Public Const NAMESPACE_CLASS_NAME         = "Namespace"
Public Const DOMAIN_CLASS_NAME            = "Domain"
Public Const COMPUTER_CLASS_NAME          = "Computer"
Public Const USER_CLASS_NAME              = "User"
Public Const GROUP_CLASS_NAME             = "Group"
Public Const SERVICE_CLASS_NAME           = "Service"
Public Const FILESERVICE_CLASS_NAME       = "FileService"
Public Const SESSION_CLASS_NAME           = "Session"
Public Const RESOURCE_CLASS_NAME          = "Resource"
Public Const FILESHARE_CLASS_NAME         = "FileShare"
Public Const PRINTER_CLASS_NAME           = "PrintQueue"
Public Const PRINTJOB_CLASS_NAME          = "PrintJob"
Public Const SCHEMA_CLASS_NAME            = "Schema"
Public Const CLASS_CLASS_NAME             = "Class"
Public Const PROPERTY_CLASS_NAME          = "Property"
Public Const SYNTAX_CLASS_NAME            = "Syntax"
                                                                   
Public Const NO_SCHEMA                    = ""
Public Const DOMAIN_SCHEMA_NAME           = "Domain"
Public Const COMPUTER_SCHEMA_NAME         = "Computer"
Public Const USER_SCHEMA_NAME             = "User"
Public Const GROUP_SCHEMA_NAME            = "Group"
Public Const SERVICE_SCHEMA_NAME          = "Service"
Public Const PRINTER_SCHEMA_NAME          = "PrintQueue"
Public Const PRINTJOB_SCHEMA_NAME         = "PrintJob"
Public Const FILESERVICE_SCHEMA_NAME      = "FileService"
Public Const SESSION_SCHEMA_NAME          = "Session"
Public Const RESOURCE_SCHEMA_NAME         = "Resource"
Public Const FILESHARE_SCHEMA_NAME        = "FileShare"
Public Const FPNW_FILESERVICE_SCHEMA_NAME = "FPNWFileService"
Public Const FPNW_SESSION_SCHEMA_NAME     = "FPNWSession"
Public Const FPNW_RESOURCE_SCHEMA_NAME    = "FPNWResource"
Public Const FPNW_FILESHARE_SCHEMA_NAME   = "FPNWFileShare"
