#include "dialogs.h"
#define MAXREGPATHLEN	1024     	// Max length of registry path
#define MAXTPLEN	128             // Max length of TP name
#define MAXBINPATHLEN   256             // Max length of file path
#define MAXPARAMLEN  	128	        // Max length of command-line parameters
#define MAXUSERNAMELEN  32		// Max length of username
#define MAXPASSWORDLEN  32		// Max length of password
#define MAXLULEN	8		// Max length of LU name

#define VALIDATE_INT 	1
#define VALIDATE_APPC 	2

#define INFINITE_TIMEOUT  "-1"	     // Value used for infinite timeout
#define INIT_TIMEOUT    5	     // Initial value displayed in timeout box					
#define MAXTIMEOUTLEN	5	     // Max digits in timeout

#ifdef WIN32

typedef struct _KeyEntry {
  LPSTR lpParent;                       // Parent key
  LPSTR lpName;                         // Data field name
  int   iDataType;                      // Type of data	
  LPSTR lpData;				// Data itself
  int   iDataSize;			// Length of data, including nulls
} KEYENTRY;

// The following variable defines the subkeys that are placed in the registry.
// The first field gives the key under which to create the new subkey.  The
// second field is the subkey name.  The third field is the data type.
// The fourth field gives the data itself.  This should always be a string,
// HOWEVER, if the third field isn't REG_SZ, some interpretation will go on,
// as follows:
//   If the third field is REG_MULTI_SZ, you should add an extra null character
//   to the end of the string to simulate an array of strings.
//   If the third field is REG_DWORD, you should enter the numeric value as
//   a string in the fourth field, as in "345" if you want the data to be the
//   number 345.
// The fifth field is the length of the fourth field in bytes, INCLUDING nulls.
// This field is set automatically for REG_DWORD data.
KEYENTRY keyinfo[] = {
  { "Linkage",    "OtherDependencies",    REG_MULTI_SZ, "SnaBase\0", 9 },
  { "Parameters", "SNAServiceType",       REG_DWORD,    "5",         4 },
  { "Parameters", "ConversationSecurity", REG_SZ,       "yes",       4 },
  { "Parameters", "AlreadyVerified",      REG_SZ,       "yes",       4 },
  { "Parameters", "Timeout",              REG_DWORD,    "",	     4 },
  { "Parameters", "Parameters",           REG_SZ,       "",       4 },
  { "Parameters", "LocalLU",              REG_SZ,       "",	     4 },
  { "Parameters", "",                     REG_SZ,       "",          4 },
  { "Parameters", "PathName",             REG_SZ,       "",          4 },
};

// These numbers must correspond to the indices in keyinfo above!
#define SNASRVTYPE 1
#define CONVSEC    2
#define ALREADYVER 3
#define TIMEOUT    4
#define PARAMETERS 5
#define LUNAME     6
#define USER       7	  // Blank field for writing out users & passwords
#define EXENAME    8
#define NUMKEYS    6      // Last three keys only written out if needed

int  InstallServiceNT(HWND, LPSTR, LPSTR);
int  CreateKeys(LPSTR, BOOL, LPSTR, int, int, int, LPSTR, LPSTR, LPSTR);
INT  WriteKeyNT(LPSTR, KEYENTRY, BOOL);

#else

#define USHORT unsigned short
#define INT    int
#define SHORT  short

typedef struct _KeyEntry {
  char *name;                        // Data field name
  char *data;			     // Data itself
} KEYENTRY;

// If you change the fields below, change the #defines too; they are used
// as indices into the keyinfo structure to set the data fields, which are
// initially all NULL.

KEYENTRY keyinfo[] = {
  { "PathName", 	    NULL },
  { "Parameters", 	    NULL },
  { "Queued", 		    NULL },
  { "Timeout", 		    NULL },
  { "ConversationSecurity", NULL },
  { "AlreadyVerified",      NULL },
  { "LocalLU",		    NULL },
  { "",                     NULL },
};
#define PATHNAME    0
#define PARAMETERS  1
#define QUEUED      2
#define TIMEOUT     3
#define CONVSEC     4
#define ALREADYVER  5
#define LUNAME      6
#define USER        7
#define NUMKEYS     6		// Last keys only written out if necessary

int  InstallWindows(HWND, char *, char *, char *, char *, int, int, int, char *);
INT  WriteKeyWindows(char *, char *, char *);

#endif //ifdef WIN32

extern BOOL CALLBACK MainDlgProc (HWND, UINT, WPARAM, LPARAM);
extern BOOL CALLBACK UserDlgProc (HWND, UINT, WPARAM, LPARAM);
BOOL ValidateField(HWND, USHORT);
void InstallCallback(HWND, UINT, WNDPROC *, FARPROC);
extern LRESULT CALLBACK ValidateFieldInt(HWND, WORD, WPARAM, LPARAM);
extern LRESULT CALLBACK ValidateFieldAppc(HWND, WORD, WPARAM, LPARAM);
extern LRESULT CALLBACK InfiniteWndProc(HWND, WORD, WPARAM, LPARAM);
extern LRESULT CALLBACK FiniteWndProc(HWND, WORD, WPARAM, LPARAM);
extern LRESULT CALLBACK ConvSecWndProc(HWND, WORD, WPARAM, LPARAM);
extern LRESULT CALLBACK ServiceWndProc(HWND, WORD, WPARAM, LPARAM);
void ParseCreateError(HWND, UINT);
void DeleteListItem(INT);
INT  ReadString(HWND, INT, char **, INT);
void DisplayError(HWND, UINT);
void DisplayInfo(HWND, UINT);

