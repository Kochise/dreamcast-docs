class CFmtText;
class CFmtListText;

class CFmtSrchText : public CFmtSrchTag
{
};

class CFmtText : public CFmtTag
{
friend CFmtListText;

public:
    CFmtText(void);

private:
	// Member data items here
};


class CFmtListText  : public CFmtListTag
{
protected:
	// Override to return the list
	TAGSPEC *FmtTagList(void);
	
	int ParseEntry(CFmtInput &in);

public:
	enum TextTags { \
		tagFormat, \
        tagTag, \
		tagIf};
};
