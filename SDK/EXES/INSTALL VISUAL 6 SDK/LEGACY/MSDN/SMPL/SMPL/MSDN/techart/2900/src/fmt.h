// *********************************************************
// FMT.H ***************************************************
// *********************************************************

#define MAXTAGSIZE	   64
#define MAXFMTTOKENS   10

const chFmtEscape		= '^';
const chFmtDefSep 		= '=';
const chFmtSectOpen 	= '[';  
const chFmtSectClose	= ']';
const chFmtTagOpen  	= '.';
const chFmtComment 		= ';';


//@doc FMT GENERIC

//@struct Stores a tag name/tag ID combination.

struct TAGSPEC
{
    int  iTag;          //@field Numeric ID for tag
    char *szName;       //@field Textual name
};



class CFmtSrchBase;
class CFmtList;

// *********************************************************

void CopyFlags(CString &, const char *);

// *********************************************************

//@doc FMT INPUT

//@class Provides input services for the formatting file
// parser.

class CFmtInput : public CAdInput
{
public:
	//@cmember Constructor
	CFmtInput(void);
	
	//@cmember Saves output type string
	void SetOutputType(const char *szOutputType);

	//@cmember Breaks the input buffer into a series of null-terminated
	// strings and stores the starting positions of the strings in
	// <md .m_aszTokens>.

	void Tokenize(char *szSrc = NULL);

	//@cmember Opens the specified input file.

	int OpenFmtFile(const char *szName, const char *szAutoduckPath);

    //@cmember Find an Autoduck format file given a target filename
    // and location.

	int GetPath(const char *szTarget, const char *szAutoduckPath);

	//@cmember Array of fields for fmt file entry.
	char *m_aszTokens[MAXFMTTOKENS];

	//@cmember Number of tokens
	int m_nTokens;

	//@cmember Output type from command line.
	CString m_sOutputType;

	//@cmember Receives the full format file path name.

	char m_szFilename[_MAX_PATH+1];
	
	//@cmember Input file number
	int m_nFile;
};



// *********************************************************

//@doc FMT SRCHBASE

//@class Base class for format search query classes.

class CFmtSrchBase
{
};



// *********************************************************

//@doc FMT TAGBASE

//@class Base class for formatting tag classes.

class CFmtBase : public CObject
{
friend CFmtList;

public:
    //@cmember Constructor, initializes format string array.
	CFmtBase(int nFmtStrings = 0);
    
    //@cmember Destructor
	~CFmtBase();

    //@cmember Base function for matching a search query
    // request to a tag. Some classes can use this as is.
	virtual int Match(CFmtSrchBase *psrch) { return 1; }

    //@cmember Base function for validating that all components
    // of a tag definition are present.

    virtual int Validate(void) { return 0; }

#ifdef _DEBUG
    //@cmember Dumps the format strings for the tag.
	void CFmtBase::Dump(CDumpContext &dc) const;
#endif

    //@cmember Sets source information for the tag.
	void SetSource(int nInput, long lLine) { m_nInput = nInput; m_lSrcLine = lLine; }

    //@cmember Returns a specified format string.
    CString &GetFmtString(int nFmt);

    //@cmember Returns the line number on which the tag started
    // in the format file.
	long GetSrcLineNum(void) { return m_lSrcLine; }

	//@cmember Returns the numeric identifier for the source format
    // file.
	int GetSrcFn(void) { return m_nInput; }

protected:
	//@cmember Stores the format strings for the file.
	CStrArray    m_aFmtStrings;
    
    //@cmember Numeric index of source format file for tag.
    int          m_nInput;

    //@cmember Line number on which tag started.
    long         m_lSrcLine;
};


// *********************************************************

//@doc FMT TAGLIST

//@class Stores a series of tag definitions and handles
// the parsing from the format file. Tag definitions are kept
// in separate <c CFmtList> objects, separated by tag type.

class CFmtList : public CObject
{
//@group Public (External) Functions

public:
	//@cmember Constructor.

	CFmtList();

	//@cmember Destructor.

	~CFmtList();
	
	//@cmember Parses the format file section.
	
	int GetSection(CFmtInput &in);

	//@cmember Retrieves a format file entry.

	CFmtBase *Get(CFmtSrchBase *psrch);

    //@cmember Adds a format file entry.

    int Add(CFmtBase *p);

	//@cmember Validates the entire format file section.

	virtual int Validate(void) { return 0; }

#ifdef _DEBUG
	//@cmember Debug out
	void CFmtList::Dump( CDumpContext &dc ) const;
#endif

//@group Functions Overridden in Derived Classes

protected:
	//@cmember Returns the list of tag name / tag ID pairs for the
	// overridden format file section.

	virtual TAGSPEC *FmtTagList(void) { return NULL; }
	
	//@cmember Parses a format file section entry.

	virtual int ParseEntry(CFmtInput &in) { return 0; }

//@group Helper Functions for Derived Classes

protected:
	//@cmember Checks the output type named in a format entry
	// against an output type named on the command line.

	int CheckOutputType(CFmtInput &in, int nField);

	//@cmember Creates a new parent tag. If <md .m_pNew> already 
	// has a tag, validates & adds <md .m_pNew>.
	
	int CheckAddTag(void);


	//@cmember Identifies current formatting string
	// by setting fields in the <c CFmtInput> structure.

	int SetFmtString(CFmtInput &in, int nField);

protected:

	//@cmember | tagState | m_nState | Input state flags.
	struct tagState{
		unsigned Tag   : 1;
		unsigned Multi : 1;
		unsigned Done  : 1;
		unsigned Skip  : 1;
	} m_nState;


	//@cmember File position of line in <md .m_szLineBuf>.

	long m_lPosCur;

	//@cmember File position of beginning of format
	// string last marked in input file.

	long m_lPosStart;

	//@cmember File position of next input line.

	long m_lPosNext;

	//@cmember Tag ID of last tag found.
	int  m_nTag;

private:

    //@cmember Gets the numeric identifier for the
    // format file tag. Sets <md .m_nTag> to the tag ID.
	const char *GetFmtTag(CFmtInput &in);

	//@cmember Checks whether a format string is terminated
    // on the current line, and if so, constructs a CString
    // to store the string.

	int CheckFmtString(CFmtInput &in);
    
    //@cmember List of format source files. Declared static
    // so all format lists can share.
    static CStrArray m_asInput;

protected:

    //@cmember Stores the list of tag defintions.
	CTypedPtrList<CObList, CFmtBase *> m_listTags;

    //@cmember Points to the current tag being parsed.
	CFmtBase	*m_pNew;
};



