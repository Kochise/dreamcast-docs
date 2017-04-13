
#define PREFIX "v"
#define INDIRECTACCESS 0
#define COMMON 1
#define MAX_COLUMN_NAME 255 // Max Width Col Name
#define MAX_COLUMNS     254   // Max # of COLUMNS we can Create on our View
                            // DdwMachineID takes one
#define MAX_NAME  255       // SIze of string we can take for the Server name

#define DLLExport __declspec(dllexport)

#define DISP 1
#define NO_DISP 0

//Command Line switches
#define LOGINIDPARAM    'L'
#define PASSWORDPARAM   'P'
#define DBNAMEPARAM     'D'
#define SERVERNAMEPARAM 'S'

struct VIEWDEF {
      char ColName[MAX_COLUMN_NAME];
      int  ComSpec;
      };

DLLExport int GenViews(DBPROCESS *,DBPROCESS *,char * ,int ,int );
int CheckSQLReturn(DBPROCESS * , char *);
int CreateGroupView(DBPROCESS *);
int CreateSNMPVarbindsView(DBPROCESS *);
int DropView ( DBPROCESS * , char *);
int CreateV(char *, struct VIEWDEF *,DBPROCESS *,int ,int,int ,
            char * , char *,int ,char *, int, int);
LRESULT WINAPI dbConnect(HWND , UINT , WPARAM , LPARAM );
int GetConnectionInfo( int);
int SetupDbConnection();
void   MakeUName(char *,char *,char *) ;
int CheckCommandLine(char * );
void GenResults(int);

int  err_handler();

DBPROCESS *dbproc = (DBPROCESS *)NULL;
                  /* dbprocess pointer for dblib connection*/
HANDLE hInst;    /* current instance                */
HWND ghWnd;      /* global window handle for handlers    */
HWND errhWnd;    /* global window handle for current error*/
BOOL SqlTestInit();





