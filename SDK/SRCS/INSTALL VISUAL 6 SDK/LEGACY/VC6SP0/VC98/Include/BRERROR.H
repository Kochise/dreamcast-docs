//
//  Values are 32 bit values layed out as follows:
//
//   3 3 2 2 2 2 2 2 2 2 2 2 1 1 1 1 1 1 1 1 1 1
//   1 0 9 8 7 6 5 4 3 2 1 0 9 8 7 6 5 4 3 2 1 0 9 8 7 6 5 4 3 2 1 0
//  +---+-+-+-----------------------+-------------------------------+
//  |Sev|C|R|     Facility          |               Code            |
//  +---+-+-+-----------------------+-------------------------------+
//
//  where
//
//      Sev - is the severity code
//
//          00 - Success
//          01 - Informational
//          10 - Warning
//          11 - Error
//
//      C - is the Customer code flag
//
//      R - is a reserved bit
//
//      Facility - is the facility code
//
//      Code - is the facility's status code
//
//
// Define the facility codes
//


//
// Define the severity codes
//


//
// MessageId: BRIDGE_E_INVALID_OUTPUT_ID
//
// MessageText:
//
//  The output subsystem ID is invalid.
//
#define BRIDGE_E_INVALID_OUTPUT_ID       ((HRESULT)0xC0040001L)

//
// MessageId: BRIDGE_E_INVALID_RESV_ID
//
// MessageText:
//
//  The bandwidth reservation ID is invalid.
//
#define BRIDGE_E_INVALID_RESV_ID         ((HRESULT)0xC0040002L)

//
// MessageId: BRIDGE_E_INVALID_ROUTE
//
// MessageText:
//
//  The specified route does not match any entry in the filter table.
//
#define BRIDGE_E_INVALID_ROUTE           ((HRESULT)0xC0040003L)

//
// MessageId: BRIDGE_E_INVALID_STATE
//
// MessageText:
//
//  The specified output driver state code is not valid.
//
#define BRIDGE_E_INVALID_STATE           ((HRESULT)0xC0040004L)

//
// MessageId: BRIDGE_E_ROUTE_EXISTS
//
// MessageText:
//
//  The specified route already exists.
//
#define BRIDGE_E_ROUTE_EXISTS            ((HRESULT)0xC0040005L)

//
// MessageId: BRIDGE_E_INSUFFICIENT_BANDWIDTH
//
// MessageText:
//
//  The bandwidth reservation cannot be created or altered because
//  the maximum bandwidth of the target output subsystem would be exceeded.
//
#define BRIDGE_E_INSUFFICIENT_BANDWIDTH  ((HRESULT)0xC0040006L)

//
// MessageId: BRIDGE_E_OUTPUT_MAX_REACHED
//
// MessageText:
//
//  The bridge has reached its maximum number of output subsystems.
//  No more output subsystems can be installed.
//
#define BRIDGE_E_OUTPUT_MAX_REACHED      ((HRESULT)0xC0040007L)

//
// MessageId: BRIDGE_E_INTERNAL_ERROR
//
// MessageText:
//
//  The bridge encountered an internal error.
//  This error should not occur during normal usage.
//  Please check the event log on the server computer.
//
#define BRIDGE_E_INTERNAL_ERROR          ((HRESULT)0xC0040008L)

//
// MessageId: BRIDGE_E_OUTPUT_VALUE_ERROR
//
// MessageText:
//
//  The output driver returned invalid configuration data.
//  Make sure that the output subsystem driver DLL is compatable with
//  this version of the multicast router.
//
#define BRIDGE_E_OUTPUT_VALUE_ERROR      ((HRESULT)0xC0040009L)

//
// MessageId: BRIDGE_E_INVALID_OUTPUT_VALUE
//
// MessageText:
//
//  The value of the configuration is not a valid datatype.
//
#define BRIDGE_E_INVALID_OUTPUT_VALUE    ((HRESULT)0xC004000AL)

//
// MessageId: BRIDGE_E_OUTPUT_VALUE_REJECTED
//
// MessageText:
//
//  The output driver rejected the configuration data.
//  Make sure the index and data type of the configuration data is valid.
//  Please check the event log on the server computer.
//
#define BRIDGE_E_OUTPUT_VALUE_REJECTED   ((HRESULT)0xC004000BL)

//
// MessageId: BRIDGE_E_OUTPUT_VALUE_NOT_SUPPORTED
//
// MessageText:
//
//  The output driver does not support dynamic configuration.
//
#define BRIDGE_E_OUTPUT_VALUE_NOT_SUPPORTED ((HRESULT)0xC004000CL)

//
// MessageId: BRIDGE_E_OUTPUT_SET_STATE_ERROR
//
// MessageText:
//
//  The output driver refused to change its state.
//  Please check the event log on the server computer.
//
#define BRIDGE_E_OUTPUT_SET_STATE_ERROR  ((HRESULT)0xC004000DL)

//
// MessageId: BRIDGE_E_OUTPUT_DLL_LOAD_FAILED
//
// MessageText:
//
//  The output driver DLL could not be loaded.
//  Please check to make sure that the driver DLL path is correct
//  and that the DLL is compatable with this version of the multicast router.
//  Please check the event log on the server computer.
//
#define BRIDGE_E_OUTPUT_DLL_LOAD_FAILED  ((HRESULT)0xC004000EL)

//
// MessageId: BRIDGE_E_OUTPUT_DLL_INCOMPATABLE
//
// MessageText:
//
//  The output driver DLL is not compatable with this version of the multicast router.
//
#define BRIDGE_E_OUTPUT_DLL_INCOMPATABLE ((HRESULT)0xC004000FL)

//
// MessageId: BRIDGE_E_REGISTRY_ERROR
//
// MessageText:
//
//  A registry operation could not be completed.
//  Please check the event log on the server computer.
//
#define BRIDGE_E_REGISTRY_ERROR          ((HRESULT)0xC0040010L)

//
// MessageId: BRIDGE_E_WINSOCK_ERROR
//
// MessageText:
//
//  An error occurred in the WinSock subsystem.
//  Please check the event log on the server computer.
//
#define BRIDGE_E_WINSOCK_ERROR           ((HRESULT)0xC0040011L)

//
// MessageId: BRIDGE_E_OUTPUT_NOT_LOADED
//
// MessageText:
//
//  The operation could not be completed because the output driver is not loaded.
//  Please load the output driver first.
//
#define BRIDGE_E_OUTPUT_NOT_LOADED       ((HRESULT)0xC0040012L)

//
// MessageId: BRIDGE_E_OUTPUT_STARTUP_FAILED
//
// MessageText:
//
//  The output subsystem could not be started.
//  Please check the event log on the server computer.
//
#define BRIDGE_E_OUTPUT_STARTUP_FAILED   ((HRESULT)0xC0040013L)

//
// MessageId: BRIDGE_E_OUTPUT_SHUTDOWN_PENDING
//
// MessageText:
//
//  The operation could not be completed because the output subsystem is in the process of shutting down.
//
#define BRIDGE_E_OUTPUT_SHUTDOWN_PENDING ((HRESULT)0xC0040014L)

