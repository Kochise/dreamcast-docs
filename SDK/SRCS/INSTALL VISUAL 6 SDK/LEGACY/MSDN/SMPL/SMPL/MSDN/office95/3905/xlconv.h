#define iActionIsFormatOk		0
#define iActionInitLoad			1
#define iActionRtNextRecord		2
#define iActionCbNextRecord 	3
#define iActionDataNextRecord 	4
#define iActionAbortLoad		5

#define iefccmdCbFromFile		0
#define iefccmdAllocCb			1
#define iefccmdFreeCb			2
#define iefccmdGetPos			3
#define iefccmdSetPos			4
#define iefccmdMax				5

typedef struct _efcParam
	{
	long lcb;
	BYTE FAR *lprgb;
	FARPROC lpfn;
	} EFCP, FAR * LPEFCP;
