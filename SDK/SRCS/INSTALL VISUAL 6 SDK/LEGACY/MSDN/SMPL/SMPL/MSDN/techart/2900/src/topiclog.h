// TOPICLOG.H: Topic tag, object, and list definitions.

#define MAXNUMFIELDS   6

#define LOGADD_BREAKLINE 0x01

int RetrieveFileText(char *szFile, char *&szBuf);

//@class Stores the text and other informatoin for
// a tag. Thsi object is stored within a <c CTopic>
// object.

class CTag : public CObject 
{
public:
    //@cmember Tag name.
    CString         sTag;

    //@cmember Count of tag fields.
    int             nFields;

    //@cmember Array of pointers to field text strings.
    // These are cleared from memory when the tag is
    // written to the temp file.
    char            *aszFieldText[MAXNUMFIELDS];

    //@cmember Array of field character count values.
    unsigned int    anFieldLen[MAXNUMFIELDS];

    //@cmember Line from source fiel on which tag started.
    long            lSrcLineNum;

    //@cmember TAGOPTIONS | nState | List of tag options.
	struct TAGOPTIONS {
		unsigned IsExample : 1;
		unsigned WasOutput : 1;
	} nState;

	//@cmember Constructors
	CTag(void);

    //@cmember Destructor
    ~CTag(void);

    //@cmember Frees any tag text memory allocated
	void FreeText(void);
};


typedef CTypedPtrList<CObList, CTag *> CTagList;

//@class Stores information for an Autoduck topic.
// This object is stored within a <c CTopicLog>
// object.

class CTopic : public CObject
{
public:
    //@cmember Constructor
    CTopic(void);

    //@cmember Destructor
    ~CTopic(void);

    //@cmember Writes the topic text to a temporary file.

    int  Write(CFile &f);

    //@cmember Reads the topic text from a temporary file.
    int  Read(CFile &f);

    //@cmember Assigns a linked list of <c CTag> objects
    // to the topic.

    void SetTags(CTagList &list);

    //@cmember Returns TRUE if the topic has an associated
    // tag list.

    BOOL HasTags(void) { return !m_listTags.IsEmpty(); }

    //@cmember Returns the CTag structure for the topic, or
    // NULL if this is an empty topic.

    CTag *GetTopicTag(void);

#ifdef _DEBUG
	//@cmember Dumps the contents of the tag to the output
	
	void Dump( CDumpContext &dc ) const;
#endif

public:
    //@cmember Sets the tag name.
    
    void SetName(const char *sz);

    //@cmember Sets the context string.
    void SetContext(const char *sz);

    //@cmember Sets the offset within the temp file. 

    void SetOffset(long l);

    //@cmember Sets the sorting weight.
    void SetWeight(int n);

    //@cmember Sets the index of the set of doc tags
    // that were active when the tag was parsed.

    void SetDocTag(int n) { m_nDocTag = n; }

    //@cmember Returns index of doc tag for topic.
    const int GetDocTag(void) { return m_nDocTag; }

    //@cmember Sets the index of the topic sourcefile.
    void SetSrcFn(int n) { m_nSrcFn = n; }

    //@cmember Get the source file index.
    int GetSrcFn(void) { return m_nSrcFn; }

    //@cmember Gets source line number for topic.
    long GetSrcLine(void) { return m_lSrcLineNum; }

    //@cmember Sets source line number for topic.
	void SetSrcLine(long l) { m_lSrcLineNum = l; }

public:
    //@cmember Gets null-terminated string for context
    // name.
    const char *GetContext(void);

    //@cmember Gets null-terminated topic name.
    const char *GetName(void);

    //@cmember Gets the head of the <c CTag> list for the topic.
    CTagList &GetTags(void) { return m_listTags; }

    //@cmember Walks the tag list and frees all field text memory.
	void FreeTagText(void);

    //@cmember Compare via output-order attributes: topic name and
	// sort order.

    int Compare(CTopic &t);

	//@cmember Compare via topic id (context string).

	int CompareContext(CTopic &t);

private:
    CString m_sName;              //@field Name of topic                 
    CString m_sCtx;               //@field Context string
    
    int 			m_nWeight;	    //@field Sorting weight (from format file)

    long 			m_lOffset;

    CTagList        m_listTags;

    int             m_nDocTag;
    long            m_lSrcLineNum;
    int             m_nSrcFn;
};



typedef CTypedPtrList<CObList, CTopic *> CTopicList;

class CTopicLog  : public CObject
{
public:
  	CTopicLog();
	~CTopicLog();

public:
    BOOL Search(const char *szID, CTopic *&p);

	void Sort(BOOL bOutputSorted);

    CTopic *GetTopicOutputOrder(UINT i);
    CTopic *GetTopicSortOrder(UINT i);

    UINT GetLogCount(void) { return m_listTopics.GetCount(); }
    UINT GetRealCount(void) { return m_nTopics; }

    enum AddFlags {
        AddOverwrite		= 0x01,
        AddGenerateUnique	= 0x02,
    };

	void Add(CTopic *pAdd, int nOptions);
	POSITION GetHeadPosition( ) const { return m_listTopics.GetHeadPosition(); }
	CTopic *GetNext(POSITION &pos) { return m_listTopics.GetNext( pos ); }

    int Print(const char *szFile, int  bConcat);

    int AddSrcFn(const char *szInput);
    const char *GetSrcFn(int n = -1);
    int GetSrcFnIndex(void) { return m_asSrcFn.GetUpperBound(); }

    int AddDocTag(const char *szTag);
    const char *GetDocTag(int n = -1);
    int GetDocTagIndex(void) { return m_asDocTags.GetUpperBound(); }

#ifdef _DEBUG
	void Dump( CDumpContext &dc ) const;
#endif

private:
    CTopicList		m_listTopics;
    CTopic          **m_apTopicSort;
    CTopic          **m_apTopicOutput;
	UINT 			m_nTopics;
    
    CStrArray       m_asDocTags;
    CStrArray       m_asSrcFn;
    BOOL            m_bIsSorted;
};

