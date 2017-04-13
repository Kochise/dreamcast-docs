#define REMOTE_SERVER       1
#define REMOTE_CLIENT       2
#define REMOTE_INIT_MSG		TEXT("APPC Remote")

// commands for the remote server begin with this
#define COMMANDCHAR         TEXT('@')
#define CTRLC               3

#define CLIENT_ATTR         FOREGROUND_INTENSITY|FOREGROUND_GREEN|FOREGROUND_RED|BACKGROUND_BLUE
#define SERVER_ATTR         FOREGROUND_INTENSITY|FOREGROUND_GREEN|FOREGROUND_BLUE|BACKGROUND_RED

//
//Some General purpose Macros
//
#define MINIMUM(x,y)          ((x)>(y)?(y):(x))
#define MAXIMUM(x,y)          ((x)>(y)?(x):(y))

// All because printf does not work
// with NT IO redirection
#define WRITEF(wsprintfargs) 								\
{                                                  			\
	HANDLE 	h = GetStdHandle(STD_OUTPUT_HANDLE);       		\
	wchar_t	VBuff[256];                                		\
	DWORD  	tmp;                                       		\
    wsprintf wsprintfargs;									\
    WriteConsole(h, VBuff, lstrlen(VBuff), &tmp, NULL);		\
}
				  
#define HOSTNAMELEN         16

#define CHARS_PER_LINE      80

// magic number is version number is 00yyyymm (yyyy = year, mm = month)
#define MAGICNUMBER     0x00199406
#define BEGINMARK       '\xfe'
#define ENDMARK         '\xff'
#define LINESTOSEND     200

#define MAX_SESSION     10

typedef struct
{
    DWORD    MagicNumber;					// version of client software
    TCHAR    ClientName[HOSTNAMELEN];		// name of client machine
    DWORD    LinesToSend;					// lines to send on startup
    DWORD    Flag;							// optional flags
}   SESSION_STARTUPINFO;

typedef struct
{
    DWORD MagicNumber; 						// New Remote
    DWORD FileSize;         				// Num bytes sent
}   SESSION_STARTREPLY;

typedef struct
{
    TCHAR    Name[HOSTNAMELEN];     //Name of client Machine;
    BOOL    Active;         //Client at the other end connected
    BOOL    CommandRcvd;    //True if a command recieved
    BOOL    SendOutput;     //True if Sendoutput output
	tpconvid_t tpconv;		//TP and conversation IDs for client's APPC connection
    HANDLE  rSaveFile;      //Sessions read handle to SaveFile
    HANDLE  hThread;        //Session Thread
    HANDLE  MoreData;       //Event handle set if data available to be read
	HANDLE	DoClose;		//Event saying that this session should close
} SESSION_TYPE;



VOID Server(TCHAR *ChildCmd, TCHAR *PipeName);

VOID Client(TCHAR *local_lu, TCHAR *server_lu, TCHAR *tp_name, TCHAR *loc_tp_name, TCHAR *mode_name);

VOID ErrorExit(TCHAR* str);

VOID DisplayClientHlp();

VOID DisplayServerHlp();

ULONG DbgPrint(PCH Format, ...);

// Timeout is ignored for now
DWORD ReadFixBytes(HANDLE hRead, TCHAR *Buffer, DWORD ToRead, DWORD  TimeOut);

VOID Errormsg(TCHAR* str);

extern		TCHAR   	HostName[];
extern		TCHAR   	*ChildCmd;
extern		DWORD  	ClientToServerFlag;
extern		DWORD	LinesToSend;
extern		TCHAR	*UserName;
