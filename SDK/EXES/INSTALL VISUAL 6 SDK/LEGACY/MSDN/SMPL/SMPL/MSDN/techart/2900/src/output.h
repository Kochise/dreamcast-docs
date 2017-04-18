/*
 * output.h
 */

#define MAXLEVEL                32767
#define MAXCONTEXT		256

/*
@class This is a simple class for storing information about the 
current topic being output. It's mainly used to reduce the number
of separate parameters passed to the outputting functions.
*/
class CCurTopicInfo {

public:
    CTopic 			*m_pTopic;		//@cmember Linked list of extracted tags for topic
    CFile 			&m_fileOutput;	//@cmember Output file
    FormatInfo      &m_fmt;			//@cmember Tag definitions from format file
    RUNOPTIONS 		&m_run;			//@cmember Runtime options
    CTopicLog 		&m_log;			//@cmember Topic log, list of all the topics extracted
									//  on this pass.

public:
    //@cmember Constructor, initializes all elements.

	CCurTopicInfo(CTopic *pTopic, CFile &file, FormatInfo &fmt, RUNOPTIONS &run, CTopicLog &log);
};



// Function Prototypes
/////

void OutputFormatString(CCurTopicInfo &cur, CFmtBase *pfmt,	int  nFmt, CTag *ptag);
void OutputFormatString(CCurTopicInfo &cur, const char *sz, CFmtBase *pfmt,	CTag *ptag);
void OutputTopic(CTopic *pTopic, RUNOPTIONS &run, FormatInfo &fmt, CFile &fileOutput, CFile &fileTemp, CTopicLog &log);
void OutputWinHelpHPJFile(const char * szOutputFileName, const char * szAutoduckName);
