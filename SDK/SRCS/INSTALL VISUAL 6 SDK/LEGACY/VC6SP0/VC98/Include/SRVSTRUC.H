//
// Structure related defines
//

#define SRV_SERVBSIZE(a)                            \
            ((WORD)(a->srvio.packetsize) > (WORD)0  \
            ? (WORD)(a->srvio.packetsize)           \
            : (WORD)512)

#define SRV_DEFAULT_SERVBSIZE   512
#define MAX_NETLIBS             16      // Maximum server side net-libs
#define SRV_SERVNETFUNCS	11

#ifdef BRIDGE
  #define SRV_CLIENTNETFUNCS    12
#endif

typedef long (CDECL *LGFARPROC)();

typedef struct srv_handler {
	
  struct srv_handler * previous;
  struct srv_handler * next;
  struct srv_handler * last;
  int (* handler)(void *);

} SRV_HANDLER;

typedef struct srv_pevents {		
	 SRV_HANDLER * srv_attention;
	 SRV_HANDLER * srv_connect;
	 SRV_HANDLER * srv_disconnect;
	 SRV_HANDLER * srv_rpc;
	 SRV_HANDLER * srv_language;
	 SRV_HANDLER * srv_start;
	 SRV_HANDLER * srv_stop;
	 SRV_HANDLER * srv_sleep;
	 SRV_HANDLER * srv_restart;
	 SRV_HANDLER * srv_transmgr;
	 SRV_HANDLER * srv_oledb;
} SRV_PEVENTS;

typedef struct srv_events {
    int (*srv_hndl_attention)(void *);  // ( SRV_PROC   * )
    int (*srv_hndl_connect)(void *);    // ( SRV_PROC   * )
    int (*srv_hndl_disconnect)(void *); // ( SRV_PROC   * )
    int (*srv_hndl_restart)(void *);    // ( SRV_SERVER * )
    int (*srv_hndl_rpc)(void *);        // ( SRV_PROC   * )
    int (*srv_hndl_sleep)(void *);      // ( SRV_SERVER * )
    int (*srv_hndl_language)(void *);   // ( SRV_PROC   * )
    int (*srv_hndl_start)(void *);      // ( SRV_SERVER * )
    int (*srv_hndl_stop)(void *);	// ( SRV_SERVER * )
    int (*srv_hndl_attention_ack)(void *);  // ( SRV_PROC * )
    int (*srv_hndl_transmgr)(void *);	// ( SRV_PROC * )
    int (*srv_hndl_insertexec)(void *);	// ( SRV_PROC * )
    int (*srv_hndl_oledb)(void *);	// ( SRV_PROC * )
} SRV_EVENTS;

typedef struct srv_subchannel {
	struct srv_proc * srvproc;
   HANDLE threadHDL;
   THREAD threadID;
	HANDLE ss_handle;
	HANDLE cs_handle;
	HANDLE hEvent;
	BOOL status;
	struct srv_proc * site_srvproc;
	DWORD index;
	struct srv_proc ** master_list;
} SRV_SUBCHANNEL;

//
// define structures
//

typedef struct translation_info
{
    BOOL flag;                      // data translation flag
    void (*int2)(short*);           // 2-byte integer swap function
    void (*int4)(long*);            // 4-byte integer swap function
    void (*recvflt)(float*);        // receive 8-byte float translation function
    void (*sendflt)(float*);        // send 8-byte float translation function
    void (*recvflt4)(float*);       // receive 4-byte float translation function
    void (*sendflt4)(float*);       // send 4-byte float translation function
    void (*recvchar)(char *, int);  // ASCII translation function
    void (*sendchar)(char *, int);  // ASCII translation function
    void (*twoint4)(char *);        // 2 4-byte integer swap function
    void (*twoint2)(char *);        // 2 2-byte interger swap function
} TRANSLATION_INFO;


typedef struct srv_params
{
    struct srv_server    * server;
    struct srv_proc      * srvproc;
    struct srv_queuehead * queuehead;
    struct srv_comport	 * comport;
    THREAD                 threadID;
    HANDLE                 threadHDL;
} SRV_PARAMS;

#if defined( _MSSQLRISC_)
  #pragma pack(2)
#endif

//  SRV_LOGIN
//     The (TDS 4.0) login record received from the server client at login time.
//

typedef struct srv_loginrec {
    BYTE lhostname[SRV_MAXNAME];    // name of host or generic
    BYTE lhostnlen;         // length of lhostname
    BYTE lusername[SRV_MAXNAME];    // name of user
    BYTE lusernlen;         // length of lusername
    BYTE lpw[SRV_MAXNAME];  // password (plaintext)
    BYTE lpwnlen;           // length of lpw
	BYTE lhostproc[SRV_HOSTIDLEN];	 // host process identification
	BYTE lunused[SRV_MAXNAME-SRV_HOSTIDLEN - 6];	 // unused
    BYTE lapptype [6];	    // Application specific.
    BYTE lhplen;            // length of host process id
    BYTE lint2;             // type of int2 on this host
    BYTE lint4;             // type of int4 on this host
    BYTE lchar;             // type of char
    BYTE lflt;              // type of float
    BYTE ldate;             // type of datetime
    BYTE lusedb;            // notify on exec of use db cmd
    BYTE ldmpld;            // disallow use of dump/load and bulk insert
    BYTE linterface;        // SQL interface type
    BYTE ltype;             // type of network connection
    BYTE spare[7];          // NOTE: Apparently used by System-10
    BYTE lappname[SRV_MAXNAME]; // application name
    BYTE lappnlen;          // length of appl name
    BYTE lservname[SRV_MAXNAME];    // name of server
    BYTE lservnlen;         // length of lservname
    BYTE lrempw[0xff];      // passwords for remote servers
    BYTE lrempwlen;         // length of lrempw
    BYTE ltds[4];           // tds version
    BYTE lprogname[DBPROGNLEN]; // client program name
    BYTE lprognlen;         // length of client program name
    BYTE lprogvers[4];      // client program version
    BYTE lnoshort;          // NEW: auto convert of short datatypes
    BYTE lflt4;             // NEW: type of flt4 on this host
    BYTE ldate4;            // NEW: type of date4 on this host
    BYTE llanguage[SRV_MAXNAME];    // NEW: initial language
    BYTE llanglen;          // NEW: length of language
    BYTE lsetlang;          // NEW: notify on language change
    short slhier;           // NEW: security label hierarchy
    BYTE slcomp[8];         // NEW: security components
    short slspare;          // NEW: security label spare
    BYTE slrole;            // NEW: security login role
    BYTE lcharset[SRV_MAXNAME]; // character set name (unused)
    BYTE lcharsetlen;       // length of character set (unused)
    BYTE lsetcharset;       // notify on character set change (unused)
    BYTE lpacketsize[SRV_PKTLEN]; // length of TDS packets
    BYTE lpacketsizelen;    // length of lpacketsize
    BYTE ldummy[3];         // NEW: pad to longword

} SRV_LOGINREC;

//
//  SRV_LOGIN_OLDTDS
//     The login record received from "old" TDS 2.0 or 3.4 server clients.
//     The format is basically the same as 4.0, it is just shorter (no server
//     name or password, etc appended at the end).
//
typedef struct srv_login_oldtds {
    BYTE lhostname[SRV_MAXNAME];    // name of host or generic
    BYTE lhostnlen;         // length of lhostname
    BYTE lusername[SRV_MAXNAME];    // name of user
    BYTE lusernlen;         // length of lusername
    BYTE lpw[SRV_MAXNAME];  // password (plaintext)
    BYTE lpwnlen;           // length of lpw
    BYTE lhostproc[SRV_MAXNAME];    // host process identification
    BYTE lhplen;            // length of host process id
    BYTE lint2;             // type of int2 on this host
    BYTE lint4;             // type of int4 on this host
    BYTE lchar;             // type of char
    BYTE lflt;              // type of float
    BYTE ldate;             // type of datetime
    BYTE lusedb;            // notify on exec of use db cmd
    BYTE ldmpld;            // disallow use of dump/load and bulk insert
    BYTE linterface;        // SQL interface type
    BYTE spare[8];          // spare fields
    BYTE lappname[SRV_MAXNAME]; // application name
    BYTE lappnlen;          // length of appl name
    BYTE ldummy;         // pad length to even boundary

} SRV_LOGIN_OLDTDS;
#if defined( _MSSQLRISC_)
  #pragma pack()
#endif

// Define structure for ODS statistics

typedef struct srv_stats {
    int NumReads;
    int NumWrites;
} SRV_STATS;



// Define list elements used in queuing
// network request.

typedef struct srv_queuehead {
    struct srv_queuehead * Flink;
    struct srv_queuehead * Blink;
    struct srv_listhead  * ListHead;
} SRV_QUEUEHEAD, *PSRV_QUEUEHEAD;


typedef struct srv_listhead {
    struct srv_listentry * Flink;
    struct srv_listentry * Blink;
    int    NumListEntries;
    int    NumReadRequest;
    int    MaxQueueLength;
    long   ListLock;
    HANDLE ListEvent;
} SRV_LISTHEAD, *PSRV_LISTHEAD;

typedef struct srv_listentry {
    struct srv_listentry * Flink;
    struct srv_listentry * Blink;
    struct srv_proc      * pSrvProc;
} SRV_LISTENTRY, *PSRV_LISTENTRY;

// Define routines to manage list entries.

//
//  VOID
//  InitializeListHead(
//  PSRV_LISTENTRY ListHead
//      );
//

#define InitializeListHead(TYPE, ListHead) (\
    (ListHead)->Flink = (ListHead)->Blink = (TYPE)(ListHead))

//
//  BOOLEAN
//  IsListEmpty(
//  PSRV_LISTENTRY ListHead
//      );
//

#define IsListEmpty(ListHead) (\
    ( ((ListHead)->Flink == (ListHead)) ? TRUE : FALSE ) )

//
//  SRV_LISTENTRY
//  RemoveHeadList(
//  TYPE,
//  TYPE ListHead
//      );
//

#define RemoveHeadList(TYPE,ListHead) \
    (TYPE)(ListHead)->Flink;\
    {\
    TYPE FirstEntry;\
        FirstEntry = (ListHead)->Flink;\
    FirstEntry->Flink->Blink = (TYPE)(ListHead);\
        (ListHead)->Flink = FirstEntry->Flink;\
    }

//
//  VOID
//  RemoveEntryList(
//  PSRV_LISTENTRY Entry
//      );
//

#define RemoveEntryList(Entry) {\
    PSRV_LISTENTRY _EX_Entry;\
        _EX_Entry = (Entry);\
        _EX_Entry->Blink->Flink = _EX_Entry->Flink;\
        _EX_Entry->Flink->Blink = _EX_Entry->Blink;\
    }

//
//  VOID
//  InsertTailList(
//  PSRV_LISTHEAD  ListHead,
//  PSRV_LISTENTRY Entry
//      );
//

#define InsertTailList(ListHead,Entry) \
    (Entry)->Flink = (ListHead);\
    (Entry)->Blink = (ListHead)->Blink;\
    (ListHead)->Blink->Flink = (Entry);\
    (ListHead)->Blink = (Entry);\
    InterlockedIncrement(&(ListHead)->NumListEntries);

//
//  VOID
//  InsertHeadList(
//  PSRV_LISTHEAD  ListHead,
//  PSRV_LISTENTRY Entry
//      );
//

#define InsertHeadList(ListHead,Entry) \
    (Entry)->Flink = (ListHead)->Flink;\
    (Entry)->Blink = (ListHead);\
    (ListHead)->Flink->Blink = (Entry);\
    (ListHead)->Flink = (Entry);\
    InterlockedIncrement(&(ListHead)->NumListEntries);

//
//  VOID
//  InsertHeadQueue(
//  PSRV_QUEUEHEAD  ListHead,
//  PSRV_QUEUEHEAD  Entry
//      );
//

#define InsertHeadQueue(ListHead,Entry) \
    (Entry)->Flink = (ListHead)->Flink;\
    (Entry)->Blink = (ListHead);\
    (ListHead)->Flink->Blink = (Entry);\
    (ListHead)->Flink = (Entry);

//
//  VOID
//  InsertTailQueue(
//  PSRV_QUEUEHEAD  ListHead,
//  PSRV_QUEUEHEAD  Entry
//      );
//

#define InsertTailQueue(ListHead,Entry) \
    (Entry)->Flink = (ListHead);\
    (Entry)->Blink = (ListHead)->Blink;\
    (ListHead)->Blink->Flink = (Entry);\
    (ListHead)->Blink = (Entry);

//
//  VOID
//  RemoveEntryQueue(
//  PSRV_QUEUEHEAD Entry
//      );
//

#define RemoveEntryQueue(Entry) {\
    PSRV_QUEUEHEAD _EX_Entry;\
        _EX_Entry = (Entry);\
        _EX_Entry->Blink->Flink = _EX_Entry->Flink;\
        _EX_Entry->Flink->Blink = _EX_Entry->Blink;\
    }


// Configuration structure.

typedef struct srv_config {
    unsigned  connections;          // maximum allowed client connections
    unsigned  stacksize;            // stack size of new threads created
    BOOL      log_file_open;        // flag indicating log file open
    HANDLE    log_handle;           // handle of openned log file
    char      log_file_name[SRV_MAXFILENAME];    // name of log file
    BOOL      print_recv;           // dump reads to screen
    BOOL      print_send;           // dump sends to screen
    BOOL      remote_access;        // flag indicating remote server access
    unsigned  max_remote_sites;     // simultaneous remote sites accessing
    unsigned  max_remote_connections;   // maximum allowed in/out remote connections
    WORD      numConnectsPerThread; // Number of connections to monitor per network thread
    WORD      MaxWorkingThreads;    // Max number of working threads
    WORD      MinWorkingThreads;    // Min Number of working threads
    WORD      ConcurrentThreads;    // Min Number of working threads
    DWORD     WorkingThreadTimeout; // Time to wait before exiting when idle
    unsigned  max_packets;          // maximum number of network packets buffered
    //
    // Multi Server Side Net-Library support
    //
    WORD      numNetLibs;
    WORD      spare;
    LGFARPROC SSNetLibs[MAX_NETLIBS][SRV_SERVNETFUNCS];         // NetLib Function ptrs
    HANDLE    SSModules[MAX_NETLIBS];                           // NetLib Module handles
    char      connect_names[MAX_NETLIBS][SRV_MAXFILENAME];      // NetLib connection names
    char      connect_dlls[MAX_NETLIBS][SRV_MAXFILENAME];       // NetLib names
    char      connect_versions[MAX_NETLIBS][SRV_MAXFILENAME];   // NetLib versions
    char      server_name[SRV_MAXFILENAME]; // Server name
    BOOL      local_only;           // flag indicating local access only
    BOOL      unpack_rpc;           // flag indicating if RPCs should be unpacked
    unsigned  max_packetsize;       // maximum network packet size
	unsigned  dflt_packetsize;		// The default packet size.

    int       ThreadPriority;  // Priority of thread in class.
    BOOL ansi;	// flag indicating if ANSI codepage is used
    BYTE      tdsversion[4];
    BYTE      progversion[4];
    DWORD     threadaffinity;			// thread affinity option
#ifdef BRIDGE
    HANDLE      CSModule;                       // Client NetLib Module handle
    LGFARPROC   CSNetLib[SRV_CLIENTNETFUNCS];   // NetLib Function ptrs
    char        client_name[SRV_MAXFILENAME];   // Client side name
    BOOL        bAuditConnects;                 // flag indicating if connects should be logged
#endif
} SRV_CONFIG;

//
//  SRV_TDSHDR
//  The first 8 bytes of each network packet constitute the packet
//  header.
//
typedef struct srv_tdshdr {
    BYTE        type;       // io packet type
    BYTE        status;     // io packet status
    DBUSMALLINT length;     // io packet length
    DBUSMALLINT channel;    // io packet subchannel
    BYTE        packet;     // io packet number
    BYTE        window;     // io packet window size

} SRV_TDSHDR;

//  SRV_INPUTBUF
//  This structure maintains the read information when
//  pre-reading packets.
//

typedef struct srv_inputbuf {
    BYTE * pBuffer;
    DWORD  ioStatus;
    DWORD  ioRecvCnt;
    struct srv_inputbuf * pNext;
} SRV_INPUTBUF;

// SRV_COMPORT_QUEUE
// Queue entry for completion port requests.
//
typedef struct srv_comport_queue
{
	struct srv_comport_queue*	Flink;
	struct srv_comport_queue*	Blink;
} SRV_COMPORT_QUEUE;

// SRV_COMPORT_BUF
//	Description of a buffer passed through the srv_post_completion_queue
//  entry point. These buffers are typically posted by the server to
//	perform work on a worker thread that can't be handled by the currently
//	executing thread.
//
typedef struct srv_comportbuf 
{
	SRV_COMPORT_QUEUE	queue;

	// Overlapped structure passed through srv_post_completion_queue
	// overlapped.Offset contains the address of this structure such that
	// 
	OVERLAPPED	overlapped;
	DWORD		message_size;
	BYTE		message [1];
} SRV_COMPORT_BUF;

// WARNING! There is code that assumes it can get to the "last" input
// buffer by looking at the current->pNext buffer. (i.e. It assumes
// SRV_NUMINPUTBUFS == 2).
//
#define SRV_NUMINPUTBUFS 2

//
//  SRV_IO
//  This is the data structure used for reading and writing client
//  connection data for a particular server task.
//
typedef struct srv_io {
    void * server_ep;       // server side endpoint
#ifdef BRIDGE
    void * client_ep;       // client side endpoint
    BOOL       fCSerror;        // flag indicate client-side error
#endif
    HANDLE      cs_sub_handle;  // client-side subchannel local handle
    BYTE  * outbuff;        // send: start of send buffer
    BYTE  * p_outbuff;      // send: next place in buffer
    WORD        n_outbuff;      // send: room left in send buffer
    BYTE  * inbuff;         // recv: start of read buffer
    BYTE  * p_inbuff;       // recv: next place in buffer
    WORD        n_inbuff;       // recv: room left in read buffer
    int         SQLspanned;     // flag indicating that the SQL command
                                //  has spanned more that 1 network buffer.
    int cbflag;	  				// flag indicating that a client buffer is
                                //  available.
    DBUSMALLINT channel;        // io packet subchannel
    BYTE        packet;         // io packet number
    BYTE        window;         // io packet window size
    HANDLE      ioEvent;        // io event handle
    OVERLAPPED  ioOverlapped;   // io overlapped structure.
    SRV_INPUTBUF * pNextInBuf;  // current io input buffer index
    SRV_INPUTBUF   ioInputBuffers[SRV_NUMINPUTBUFS]; // io input buffers
    HANDLE      ss_sub_handle;  // server-side subchannel local handle
    WORD packetsize;	    // TDS packet size
} SRV_IO;

//
//  SRV_COLDESC: column description array (used by srv_describe & srv_sendrow)
//
typedef struct srv_coldesc {
    unsigned long otype;        // output data type
    unsigned long olen;         // length
    unsigned long itype;        // input data type
    unsigned long ilen;         // length
    BYTE    *data;		// data buffer address
    DBINT    user_type;		// user-defined data type
    BYTE     precision; 	// precision
    BYTE     scale;		// scale
} SRV_COLDESC;

//
//  SRV_RPCp: RPC parameter information
//
typedef struct srv_rpcp {
    BYTE          len;          // length of RPC parameter name
    BYTE    * rpc_name;     // pointer to the RPC parameter name
    BYTE          status;       // return status, 1 = passed by reference
    unsigned long user_type;    // User-defined data type
    BYTE          type;         // data type
    unsigned long maxlen;       // maximum possible data length
    unsigned long actual_len;   // actual data length
    void    * value;        // the actual data
} SRV_RPCp;

typedef struct srv_comport {
    HANDLE hdl;
    DWORD  cpu;
} SRV_COMPORT;

//
//  SRV_PROC:   This is the main connection structure
//
typedef struct srv_proc 
{
    WORD          tdsversion;   // version of tds detected from client
                                //   0x3400 = 3.4, 0x4000 = 4.0
    WORD          status;       // status of this SRV_PROC
    SRV_IO        srvio;        // I/O structure of srvproc
    SRV_LOGINREC  login;        // login record received from the client
    void        * langbuff;     // pointer to language buffer
    unsigned long langlen;      // length of language buffer
    unsigned int  event;        // event variable
    void        * server;       // pointer to associated SRV_SERVER structure
    char        * threadstack;  // stack pointer of event thread stack
    THREAD        threadID;     // thead ID associated with this SRV_PROC
    HANDLE        threadHDL;    // thread handle for resume and suspend
    HANDLE        iowakeup;     // event handle to wait on for overlapped io
                                // and more. Passed on to SQL Server and netlibs.
    HANDLE        exited;       // semaphore indicating that thread
                                //  associated with this SRV_PROC has exited
    DBINT         rowsent;      // # of rows sent to client
    SRV_COLDESC * coldescp;     // pointer to column description array
    DBUSMALLINT   coldescno;    // count of column descriptions
    BYTE        * colnamep;     // pointer to column name list
    WORD          colnamelen;   // length of column name list
    void        * userdata;     // pointer to user's private data area
    void        * event_data;   // pointer to event data area
    BYTE          serverlen;    // length of server name
    BYTE        * servername;   // name of server
    
    //  RPC info
    //
    BYTE           rpc_active;          // flag indicating active RPC (TRUE=active)
    BYTE           rpc_server_len;      // length of RPC server name
    BYTE         * rpc_server;          // name of RPC server
    BYTE           rpc_database_len;    // length of RPC database name
    BYTE         * rpc_database;        // name of RPC database
    BYTE           rpc_owner_len;       // length of RPC owner name
    BYTE         * rpc_owner;           // name of RPC owner
    BYTE           rpc_proc_len;        // length of RPC or stored procecedure name
    BYTE         * rpc_proc_name;       // name of RPC or stored procedure
    unsigned int   rpc_proc_number;     // number of RPC "procedure_name;number"
    unsigned int   rpc_linenumber;      // line number batch error occurred on.
    unsigned short rpc_options;         // recompile option flag (bit 0)
    unsigned short rpc_num_params;      // number of RPC parameters
    SRV_RPCp    ** rpc_params;          // array of pointers to each RPC paramater
    
    // Return information for non-remote procedure call client command.
    // This information is provided by the function srv_returnval().
    // flag indicating active non-RPC values (TRUE = active)
    //
    BYTE non_rpc_active;

    // number of non-RPC parameters
    //
    unsigned short non_rpc_num_params;

    // array of pointers to each non-RPC paramater
    //
    SRV_RPCp ** non_rpc_params;
    
    // temporary work buffer
    //
    char temp_buffer[100];

    // array of subchannel structures
    //
    SRV_SUBCHANNEL * (*subprocs);

    // Data Translation information
    //
    TRANSLATION_INFO     translation_info;
    struct srv_listentry IOListEntry;
    struct srv_listentry CommandListEntry;
    PSRV_LISTHEAD        pNetListHead;
    BOOL                 bNewPacket;
    long	             StatusCrit;	// critical section to check attentions
    void               * serverdata;    // private data area used ONLY by SQL Server
    SRV_SUBCHANNEL     * subchannel;

    // Pre && Post Handler pointers
    //
    SRV_PEVENTS * pre_events;
    SRV_PEVENTS * post_events;

    // current position in language buffer used by processRPC
	// 
    void * p_langbuff;	

	BOOL    fSecureLogin;

	// Set by the server when making an outbound call to an XP.
	//
	BOOL    fInExtendedProc;

	// If TRUE indicates the current buffer is from
	// srv_post_completion_queue and the buffer should be
	// deallocated when the current work is completed.  If
	// FALSE the current buffer came from the network and a
	// new read should be posted on the net.
	//
	unsigned    fLocalPost:1;

	// If TRUE an XP associated with this srvproc made a call back into
	// the server on a bound connection. This flag is used to allow the
	// calling session to wait for logout processing of the XP to complete
	//
	unsigned	fMadeBoundCall:1;

	// Filler to align after flags above.
	//
	unsigned	uFill1:30;

	// List of requests posted using srv_post_completion_queue. Entries are
	// dynamically allocated inside srv_post_completion_queue and enqueued
	// in netIOCompletionRoutine. After the request has been processed the
	// entry is removed from this queue and deallocated.
	//
	// NOTE: Must hold SRV_PROC spinlock while altering queue.
	//
	SRV_COMPORT_QUEUE	comport_queue;

    // Data pointers reserved for the Starfighter team
    //
    void * pSF1;    // Currently in use by SQLTrace
    void * pSF2;    // Reserved

    // Pre and Post handler semephores used during handler instals
    // and deinstals.
    //
    HANDLE hPreHandlerMutex;
    HANDLE hPostHandlerMutex;
	BOOL   bSAxp;		// Used by XP's to determine if running as SA

} SRV_PROC;

typedef struct srv_control 
{
    unsigned int status;        // status of process
    unsigned int connects;      // current number of connections

    SRV_PROC * (* srvprocs);    // array of SRV_PROC connection structures

    // semaphore indicating that the connects counter is being accessed or
    // modified
    //
    HANDLE connects_sem;
    
    // semaphore indicating that thread has started
    //
    HANDLE start_sem;
    
    // semaphore indicating that some event has occurred
    //
    HANDLE event_sem;
    
    // semaphore indicating that log file is being written to
    //
    HANDLE log_sem;
    
    // shutdown critical section
    //
    long ShutDownCrit;

    // Network list critical section
    //
    long NetQueueCrit;

    // Thread Pool critical section
    //
    long ThreadPoolCrit;

    // print screen critical section
    //
    long ScrnPrnt;

    unsigned int remote_sites;      // current number of remote sites connected
    unsigned int remote_connects;   // current number of in/out remote connections

    // semaphore indicating that the remote sites counter is being accessed or
    // modified
    //
    HANDLE remote_sites_sem;

    // semaphore indicating that the remote connections counter is being accessed or
    // modified
    //
    HANDLE remote_connects_sem;

    // network request queue list
    //
    SRV_QUEUEHEAD netQueueList;
    int           numNetQueueEntries;
    int           maxNetQueueEntries;

    // command queue list
    //
    PSRV_LISTHEAD CommandQueueHead;

    // Server statistics.
    //
    SRV_STATS   Stats;

    DWORD * pSharedCounter;

    HANDLE srvproc_mutex;

    DWORD  dwWorkingThreadCnt;
    DWORD  maxWorkingThreadCnt;

    SRV_COMPORT *comport;
    BYTE   num_comports;

    BYTE   ProcessorCnt;

} SRV_CONTROL;

typedef struct srv_server {
    LGFARPROC  SSNetLib[SRV_SERVNETFUNCS];  // Server Side NetLib functions
    HANDLE     SSModule;                    // Server Side DLL
    DWORD      ep_size;
    void * listen_ep;
#ifdef BRIDGE
    LGFARPROC CSNetLib[SRV_CLIENTNETFUNCS]; // Client Side NetLib functions
    HANDLE    CSModule;                     // Client Side DLL
    char      client_name[SRV_MAXFILENAME];
#endif
    THREAD net_threadID;        // thead ID of client network event thread
    HANDLE net_threadHDL;       // thread handle for resume and suspend

    //
    // connection information
    //
    char connect_name[SRV_MAXFILENAME];
    char connect_dll[SRV_MAXFILENAME];
    char connect_version[SRV_MAXFILENAME];

    //
    // temporary work buffer
    //
    char temp_buffer[100];
    //
    // server configuration information
    //
    SRV_CONFIG config;
    // server control information
    //
    SRV_CONTROL * control;

    // define the event handlers         
    //
    SRV_EVENTS * events;

    // Pre && Post Handler pointers
    SRV_PEVENTS * pre_events;
    SRV_PEVENTS * post_events;

    // Pre and Post handler semephores
    //
    HANDLE hPreHandlerMutex;    // Single writer
    HANDLE hPostHandlerMutex;
    HANDLE hPreHandlerSem;      // Multiple reader
    HANDLE hPostHandlerSem;

} SRV_SERVER;

// Private structure used to export server entry points as ODS callbacks
// for SQLServer use only.
//
typedef struct ods_callbacks
{
    int (*sql_getbindtoken) (void*, char*);
	void (*sql_getdtcxact) (void*, void**);
    int (*sql_startinexec) (void*);
    void (*sql_stopinexec) (void*);
    // Place new callbacks at the end of the structure.

} ODS_CALLBACKS;
