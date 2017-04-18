#include "input.h"
#include "fmt.h"
#include "fmtfile.h"
#include "fmtif.h"
#include "fmttag.h"
#include "fmttopic.h"
#include "fmtpara.h"
#include "fmttext.h"
#include "fmtdiag.h"
#include "fmtconst.h"
#include "fmtext.h"
#include "fmtindex.h"
#include "fmttoken.h"


enum
{
	sectFILE = 1,
	sectTOPIC,
	sectPARAGRAPH,
	sectTYPE,
	sectDIAGRAM,
	sectCONSTANT,
	sectINDEX,
	sectEXTENSION,
	sectToken,
};

 
struct FormatInfo
{
    CFmtListFile    file;
    CFmtListTopic   topic;
    CFmtListPara    paragraph;
    CFmtListText    text;
    CFmtListDiagram diagram;
    CFmtListConst   constant;
    CFmtListIndex   index;
    CFmtListExt     extension;
	CFmtListToken	token;

	CStrArray       asSrcFn;
	
	long lErrLine;

	const char *GetSrcFn(int n) { return *asSrcFn[n]; }
};


int GetFormatFile(const char *szFile, const char *szAutoduckPath, const char *szOutputType, FormatInfo &fmt, BOOL bVerbose);
BOOL ValidateFormats(FormatInfo &fmts);
