class CFmtSrchFile : public CFmtSrchBase
{
};


class CFmtFile : public CFmtBase
{
public:
	CFmtFile(void) : CFmtBase(2) {};

private:
	// Member data items here
};


class CFmtListFile  : public CFmtList
{
protected:
	// Override to return the list
	TAGSPEC *FmtTagList(void);
	
	int ParseEntry(CFmtInput &in);

public:
	enum FileTags { tagPre, tagPost, tagOutput };
	enum FileErrs { fmterrFileOutputNum };
};
