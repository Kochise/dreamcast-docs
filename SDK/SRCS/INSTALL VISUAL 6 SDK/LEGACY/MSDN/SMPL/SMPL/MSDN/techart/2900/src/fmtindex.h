class CFmtIndex;
class CFmtListIndex;

class CFmtIndex : public CFmtBase
{
friend CFmtListIndex;

public:
	CFmtIndex(void);

private:
};


class CFmtListIndex  : public CFmtList
{
protected:
	// Override to return the list
	TAGSPEC *FmtTagList(void);
	
	int ParseEntry(CFmtInput &in);

public:
	enum IndexTags { \
		tagPre, \
		tagPost, \
        tagPreName, \
        tagPostName, \
        tagPreContext,\
        tagPostContext,\
        tagOutput };
};
