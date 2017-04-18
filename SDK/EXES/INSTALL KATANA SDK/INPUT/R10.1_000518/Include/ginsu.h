/*=============================================================================
	GINSU.H
		-- Header file for "Ginsu" -- application switching library
-------------------------------------------------------------------------------*/

#if !defined(__GINSU_H__)
#define __GINSU_H__

#ifdef __cplusplus
extern "C" {
#endif 

/*=============================================================================
    GINSU_COMMAND_XFER is a private data structure used to pass information to
    and from the GINXFER.BIN program.
    
    Definitions
    -----------
        BOOT    = the startup program, generally GINBOOT.BIN (renamed to 1ST_READ.BIN)
        FIRST   = the first application to transfer to -- for sampler discs, this would be an intro application
        DEFAULT = the regular application to return to -- for sampler discs, this would be the main menu app
        NEXT    = the application to transfer to
        APP     = the application currently running and transfering to another (BOOT, FIRST, DEFAULT, NEXT are also APPs)
        XFER    = a small program that aids in the the transfer (not an APP)
    
    Basic Operation
    ---------------
        An application (APP) has an incoming GINSU_COMMAND_XFER that defines
        it's operational parameters (cmdline, CDDA offset, working dir, et al).
        
        When the APP is ready to transfer control to another program (NEXT), it
        calls the ginsu library which loads the NEXT binary image and the XFER
        program. APP:ginsu then sets up the GINSU_COMMAND_XFER for the XFER program,
        which it then calls.
        
        The XFER program scans the NEXT binary image for it's incoming
        GINSU_COMMAND_XFER data space. It then copies the structure from XFER to NEXT.
        
        In essence, each APP has two pertinent GINSU_COMMAND_XFER structures: an
        incoming one and an outgoing one.
    
    Possible Sequences
    ------------------
        1) APP->XFER->NEXT
        
                This is the general case of an app transfering to another app(NEXT)
        
        2) APP->XFER->DEFAULT
        
                The NEXT application is identified by the runDefault portion of the structure
        
        
        2) BOOT->XFER->FIRST
        
                BOOT reads the ini and determines the FIRST and DEFAULT programs.
                The default program becomes persistent through all future transfers.
                BOOT transfers to the FIRST program
        
        
    NOTE: The structure definition is MANUALLY mirrored in GINXFER.SRC
-------------------------------------------------------------------------------*/
/*
const long GCX_HEADER_ID = 'GINS';
const long GCX_VERSION_ID= 1;
const long GCX_VERIFY_ID = 0x3ac59e76;
*/
#define GCX_HEADER_ID       'GINS'
#define GCX_VERSION_ID      1
#define GCX_VERIFY_ID       0x3ac59e76

#define GCX_SIZE_SMALL_INFO 64
#define GCX_SIZE_LARGE_INFO 256
#define GCX_SIZE_RESERVED	(0x2000-0x380)
  
typedef struct GINSU_COMMAND_XFER
{
    long    gcx_Header;                             /*  00 [err]    always 'GINS'                           */
    long    gcx_Version;                            /*  04 [err]    always 1                                */
    long    gcx_Verify;                             /*  08 [err]    always GCX_VERIFY_ID                    */
    long    gcx_Size;                               /*  0c [err]    set to sizeof()                         */
    void*   gcx_LoadAddr;                           /*  10    [out] tell XFER address where NEXT is loaded  */
    int     gcx_LoadSectorCount;                    /*  14    [out] tell XFER size of NEXT binary image     */
    long    gcx_FirstGDDA;                          /*  18 [in/out] tell NEXT where it's CDDA starts        */
    long    gcx_LaunchViaXFERFlag;                  /*  1c    [out] used to determine Ginsu activity        */
    long    gcx_ExecFunctionAddr;                   /*  20 [in]     used to identify exec function          */
    long    _pad6;                                  /*  24                                                  */
    long    _pad5;                                  /*  28                                                  */
    long    _pad4;                                  /*  2c                                                  */
    long    _pad3;                                  /*  30                                                  */
    long    _pad2;                                  /*  34                                                  */
    long    _pad1;                                  /*  38                                                  */
    long    _pad0;                                  /*  3c                                                  */
    char    gcx_RunDefault  [GCX_SIZE_SMALL_INFO];  /*  40 [in/out] default for NEXT; always copied forward */
    char    gcx_XFerProgram [GCX_SIZE_SMALL_INFO];  /*  80 [in/out] transfer program; always copied forward */
    char    gcx_BasePath    [GCX_SIZE_SMALL_INFO];  /*  c0 [in/out] working directory for NEXT              */
    char    gcx_CmdLine     [GCX_SIZE_LARGE_INFO];  /* 100 [in/out] command line params                     */
	char	gcx_UserData	[GCX_SIZE_LARGE_INFO];	/* 200 [in/out] user program data space					*/
    char    gcx_CornerIcon  [GCX_SIZE_SMALL_INFO];  /* 300 [in/out] pathname of corner icon graphic         */
	char	gcx_PathDefault	[GCX_SIZE_SMALL_INFO];	/* 340 [in/out] working directory for default program   */
	char	_reserved		[GCX_SIZE_RESERVED];	/* 380          reserved                                */
}   GINSU_COMMAND_XFER_TYPE;						/*2000 END												*/

extern GINSU_COMMAND_XFER_TYPE InternalGCX;

/*=============================================================================
-------------------------------------------------------------------------------*/

typedef enum
{
	GS_OK					= 0,
	GS_ERROR				= 1,			/* unspecified error, general failure 							*/
	GS_NO_LOAD_XFER			= 2,			/* gsExitTo() failed to open the XFER program or any fallbacks	*/
	GS_NO_LOAD_NEXT			= 3,			/* gsExitTo() failed to open the NEXT program or any fallbacks	*/
	GS_BAD_XFER_HEADER		= 4,			/* the XFER program in gsExitTo() has a bad header				*/
	GS_INI_ALREADY_OPEN 	= 5,			/* attempt to open an INI, when one is already open				*/
	GS_NO_LOAD_INI			= 6,			/* gsIniOpen() failed to open the ini file or any fallbacks		*/
	GS_INI_TOO_BIG			= 7,			/* the ini file specified is too large for the library to handle*/
	GS_INI_NOT_OPEN			= 8,			/* attempt to close or access ini data that isn't open			*/
	GS_INI_SYNTAX_ERROR		= 9,			/* syntax error in ini file										*/
	GS_INI_SEMANTIC_ERROR	=10,			/* sematic error in ini file									*/
	GS_FILENAME_TOO_LONG	=11,			/* filename specified is too long								*/
	GS_PATHNAME_TOO_LONG	=12,			/* pathname specified is too long								*/
	GS_USER_PARTIAL_COPY	=13,			/* set/get user data length was too long, truncated				*/
	GS_FORCE_APP_EXIT		=14,			/* application should exit ASAP									*/
	
	_forcesize_			= 0x7fffffff
}	GS_STATUS;

  
/*=============================================================================
  BASIC FUNCTIONS:
  	* Application Transfer
	* Application Parameter Reading
-------------------------------------------------------------------------------*/
  
GS_STATUS	gsInit					(void);
GS_STATUS	gsExec					(void);
GS_STATUS	gsExit					(void);
GS_STATUS	gsExitTo				(const char* cmdline, const char* path, int gddaoffset);

int			gsGDDALogicalToPhysical	(int logical);
const char* gsGetBasePath			(void);
const char* gsGetCornerIconPath		(void);
int 		gsGetArgC				(void);
const char* gsGetArgV				(int index);

GS_STATUS	gsSetUserData			(const void* src, int size);
GS_STATUS	gsGetUserData			(void* dest, int size);

int			gsIsActive				(void);

GDFS		gs_FsOpenEx				(const char* fullname);

/*=============================================================================
  EXTENDED FUNCTIONS:
  	* Data file parsing
	* Reading key-value information
	
	These function require GDFS to be initialized.
	The open function takes a GS_INI_BUFFER_SIZE buffer which it needs until
	the close call. All other functions must be between the open and the close.
-------------------------------------------------------------------------------*/
typedef const void* GS_APP_ID;
/*const int GS_INI_BUFFER_SIZE = 256*1024;*/
#define GS_INI_BUFFER_SIZE 	(256*1024)

GS_STATUS	gsSetDefaultExecutable	(const char* exename, const char* pathname);
GS_STATUS	gsSetXFerExecutable		(const char* exename);
GS_STATUS	gsSetBasePath			(const char* dirname);
GS_STATUS	gsSetCornerIconPath		(const char* dirname);
GS_STATUS	gsSetFirstGDDA			(int index);

GS_STATUS	gsIniOpen				(void* mem256k);
GS_STATUS	gsIniOpenFrom			(void* mem256k, const char* filename);
GS_STATUS	gsIniClose				(void);

GS_APP_ID	gsFindApp				(const char* appname);
GS_APP_ID	gsGetAppN				(int index);
const char*	gsGetKeyValue			(GS_APP_ID appID, const char* key);

/*=============================================================================
-------------------------------------------------------------------------------*/
#ifdef __cplusplus
}
#endif 

#endif

/*============================================================================= END-OF-INCLUDE */
