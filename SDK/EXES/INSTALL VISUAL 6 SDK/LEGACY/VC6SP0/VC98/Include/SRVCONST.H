//
// Symbol types.  These are passed to srv_symbol to translate Open Data Services
// symbols.
//
#define SRV_ERROR      0
#define SRV_DONE       1
#define SRV_DATATYPE   2
#define SRV_EVENT      4

// define srv_symbol() SRV_ERRORs
//
#define SRV_ENO_OS_ERR     0
#define SRV_INFO           1
#define SRV_FATAL_PROCESS  10
#define SRV_FATAL_SERVER   19

// define event values
//
#define SRV_CONTINUE       0
#define SRV_LANGUAGE       1
#define SRV_CONNECT        2
#define SRV_RPC            3
#define SRV_RESTART        4
#define SRV_DISCONNECT     5
#define SRV_ATTENTION      6
#define SRV_SLEEP          7
#define SRV_START          8
#define SRV_STOP           9
#define SRV_EXIT           10
#define SRV_CANCEL         11
#define SRV_SETUP          12
#define SRV_CLOSE          13
#define SRV_PRACK          14
#define SRV_PRERROR        15
#define SRV_ATTENTION_ACK  16
#define SRV_SKIP	   17
#define SRV_TRANSMGR	   18
#define SRV_INSERTEXEC	   19
#define SRV_OLEDB	   20

#define SRV_INTERNAL_HANDLER 99
#define SRV_PROGRAMMER_DEFINED  100

// define configuration values
//
#define SRV_SERVERNAME          0   // not a configuration option
#define SRV_CONNECTIONS         1
#define SRV_LOGFILE             2
#define SRV_STACKSIZE           3
#define SRV_PRINT_RECV          4
#define SRV_PRINT_SEND          5
#define SRV_VERSION             6
#define SRV_REMOTE_ACCESS       7
#define SRV_REMOTE_SITES        8
#define SRV_REMOTE_CONNECTIONS  9
#define SRV_MAX_PACKETS         10
#define SRV_MAXWORKINGTHREADS	11
#define SRV_MINWORKINGTHREADS	12
#define SRV_THREADTIMEOUT	13
#define SRV_CONCURRENTTHREADS	14
#define SRV_LOCAL_ONLY		15
#define SRV_UNPACK_RPC		16
#define SRV_MAX_PACKETSIZE	17
#define SRV_THREADPRIORITY	18
#define SRV_ANSI_CODEPAGE	19
#define SRV_REMOTENAME		20
#define SRV_TDS_VERSION 	21
#define SRV_PROG_VERSION	22
#ifdef BRIDGE
  #define SRV_CONNECTION_NAMES	23
  #define SRV_CURRENT_CONNECTS	24
  #define SRV_AUDIT_CONNECTS	25
#endif
#define	SRV_DEFAULT_PACKETSIZE	26
#define SRV_PASSTHROUGH		27
#define SRV_THREADAFFINITY	28

// define thread priority values
//
#define SRV_PRIORITY_LOW      THREAD_PRIORITY_LOWEST
#define SRV_PRIORITY_NORMAL   THREAD_PRIORITY_NORMAL
#define SRV_PRIORITY_HIGH     THREAD_PRIORITY_HIGHEST
#define SRV_PRIORITY_CRITICAL THREAD_PRIORITY_TIME_CRITICAL

// define server values
//
#if !defined( NULL )

#define NULL        0   // The null character

#endif

#if !defined( TRUE )

#define TRUE        1   // Boolean true value

#endif

#if !defined( FALSE )

#define FALSE       0   // Boolean false value

#endif

#if !defined( SUCCEED )

#define SUCCEED     1   // Successful return value

#endif

#if !defined( FAIL )

#define FAIL        0   // Unsuccessful return value

#endif

#if !defined( SRV_DUPLICATE_HANDLER )

#define SRV_DUPLICATE_HANDLER	2

#endif

#define SRV_NULLTERM   -1   // Indicates a null terminated string

#if !defined( STDEXIT)

#define STDEXIT     0   // Normal exit valule

#endif

#if !defined( ERREXIT)

#define ERREXIT     1   // Error exit value

#endif

//  Message types
//
#define SRV_MSG_INFO    1
#define SRV_MSG_ERROR   2


// define SRV_PROC->status values
//
#define SRV_LOGGING_IN 0x1   // slot is free for used
#define SRV_FREE       0x2   // slot is free for used
#define SRV_SUSPENDED  0x4   // thread is in suspended state
#define SRV_DEAD       0x8   // thread is dead
#define SRV_KILL       0x10   // thread needs to be killed
#define SRV_RUNNING    0x20   // thread is running
#define SRV_ATTN       0x40   // client has sent an attention signal for this thread
#define SRV_WAITING    0x80   // waiting for next command
#define SRV_IOERROR    0x100	// io error occured
#define SRV_QUEUED     0x200	// srvproc has been placed on command queue
#define SRV_INEXEC     0x400	// inserting data into local table
#ifdef BRIDGE
#define SRV_ATTN_MIMIC 0x800	  // client side does not support OOB
#endif

//  Done packet status fields.
//
#define SRV_DONE_FINAL  (DBUSMALLINT) 0x0000
#define SRV_DONE_MORE   (DBUSMALLINT) 0x0001
#define SRV_DONE_ERROR  (DBUSMALLINT) 0x0002
#define SRV_DONE_INXACT (DBUSMALLINT) 0x0004
#define SRV_DONE_PROC   (DBUSMALLINT) 0x0008
#define SRV_DONE_COUNT  (DBUSMALLINT) 0x0010
#define SRV_DONE_ATTN   (DBUSMALLINT) 0x0020
#define SRV_DONE_RPC_IN_BATCH   (DBUSMALLINT) 0x0080

//  RPC return parameter type
//
#define SRV_PARAMRETURN 0x0001

//  Event types
//
#define SRV_EQUEUED (BYTE) 0x1
#define SRV_EIMMEDIATE (BYTE) 0x2

//  Field types used as field argument to srv_pfield().
//
//#define SRV_LANGUAGE 1   already defined above
//#define SRV_EVENT    4   already defined above

#define SRV_SPID       10
#define SRV_NETSPID    11
#define SRV_TYPE       12
#define SRV_STATUS     13
#define SRV_RMTSERVER  14
#define SRV_HOST       15
#define SRV_USER       16
#define SRV_PWD        17
#define SRV_CPID       18
#define SRV_APPLNAME   19
#define SRV_TDS        20
#define SRV_CLIB       21
#define SRV_LIBVERS    22
#define SRV_ROWSENT    23
#define SRV_BCPFLAG    24
#define SRV_NATLANG    25
#define SRV_PIPEHANDLE 26
#define SRV_NETWORK_MODULE	    27
#define SRV_NETWORK_VERSION	 28
#define SRV_NETWORK_CONNECTION 29
#define SRV_LSECURE	  30
#define SRV_SAXP	  31

// define the different TDS versions.
//
#define SRV_TDS_NONE   0
#define SRV_TDS_2_0    1
#define SRV_TDS_3_4    2
#define SRV_TDS_4_2    3
#define SRV_TDS_6_0    4

// define initial number of network threads
// to start when ODS is started.

#define SRV_INITIALNETTHREADCNT 1

// define RPC_ACTIVE flags

#define SRV_RPC_ACTIVE              1
#define SRV_RPC_DISABLE_OUTPARAMS   2
     
// define the ENV_CHANGE types
#define SRV_ENV_PACKETSIZE 	4

//
// Flush status for write_buffer
//
#define SRV_NO_FLUSH	0
#define SRV_FLUSH_EOM	1
#define SRV_FLUSH_MORE	2

//
// Numeric array to convert precision to internal length.
//
extern unsigned char SrvPrecToLen[];
extern unsigned char SrvLenToPrec[];
