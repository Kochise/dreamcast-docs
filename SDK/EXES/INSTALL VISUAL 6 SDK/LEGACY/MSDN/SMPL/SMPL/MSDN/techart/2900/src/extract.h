/*
 * extract.h
 */

#define TAGBUFSIZE          (24*1024)

//@enum Types of comments recognized by Autoduck.

enum COMMENTTYPES
{
    commentSemicolon = 1,   //@emem Assembly comment.
    commentSlashstar,       //@emem Multiline C/C++ comment.
    commentSlashslash,      //@emem Single line C++ comment.
    commentApostrophe,      //@emem Basic comment
};


class CPendingTag
{
public:
	int  nParseType;
	int  nPendingFields;
	BOOL bTopic;

	CTag *ptag;
	CTag *ptagParent;
	CPendingTag(void) { nParseType = nPendingFields = bTopic = 0; ptag = ptagParent = NULL; }
};

typedef CTypedPtrList<CPtrList, CPendingTag *> CPendingList;


//@class Source input file and state

class CSrcInput : public CAdInput
{
public:
    char m_achCommentStart[MAXLINEBUFSIZE+1]; // @field Store pre-comment text
    char m_achTagBuf[TAGBUFSIZE+1];         // @field Stores tag text
    char *m_szTagCur;						// @field Next position within
	const char *m_szParseCur;				// @field Current parsing position
    int m_nSourceType;                      // @field Type of source file, defined in <e SOURCETYPES>.
    int m_nLineTag;                         // @field Offset from topic line to tag start.
	int m_nFile;							// @cmember Index of input file
    enum CommentTypes
    {
        commentSemicolon,
        commentSlashStart,
        commentApostrophe,
        commentSlashSlash,
    };

    int m_nCommentType;

    struct SrcInputState
    {
        unsigned Comment : 1;
        unsigned BeginComment : 1;
        unsigned EndComment : 1;
        unsigned Autoduck : 1;
        unsigned Topic : 1;
        unsigned HaveTopicTag : 1;
        unsigned Tag : 1;
        unsigned GrowingTag : 1;
        unsigned NestedTopic : 1;
        unsigned MultilineSourceline : 1;
		unsigned PendingTopic : 1;
		unsigned SkipTopic : 1;
		unsigned SkipAux : 1;
        unsigned AuxTopicOpen : 1;
		unsigned AuxTopicTag : 1;
		unsigned AuxPara : 1;
		unsigned AuxParaTag : 1;
    } m_nState;

	CPendingList m_pendMain;		//@cmember Tags from the main topic
									// requiring source fields
	CPendingList m_pendAux;			//@cmember Tags from aux topic requiring
									// source fields

    CString m_sTag;                 // @cmember Current tag - to be parsed next time.
									// <e EXTRACTINFO.szTagBuf>
    CString m_sTagAux;              // @cmember Topic tag to parse on top of regular tag
	CTagList m_listTags;			// @cmember Main topic tag list.
	CTagList m_listAuxTags;	        // @field Auxiliary topic tag list.
    CString m_sDocFlags;            // @field Current doc flags - always stored regardless
									// of whether they meet the extraction request.

public:
	void CueParse(CPendingList &m_pendMain, CTag *ptag, int nTargetFields, int nParseType, BOOL bTopic);
	void CueParse(CPendingList &pend, CTag *ptag, CTag *ptagParent, FormatInfo &fmt);
    void ResetState(void) { CAdInput::ResetState(); ZeroMem(&m_nState, sizeof(m_nState)); }
	void EmptyParse(void);
    CSrcInput();
	~CSrcInput();
};


void ExtractTopics(CFile &out, RUNOPTIONS &run, CTopicLog  &log, FormatInfo &fmt);
