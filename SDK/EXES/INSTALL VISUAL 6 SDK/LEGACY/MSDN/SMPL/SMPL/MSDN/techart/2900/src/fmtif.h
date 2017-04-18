#define MAXTOPICNAMETOKENS      12
#define MAXTOPICNAMELEN         256


// @enum Name token types
// 
enum NAMETYPE
{
	nameNone,				// @emem Non-value.
	nameLiteral,			// @emem Literal text
	nameLocal,				// @emem Paragraph tag field
	nameLocalStripTemplate,	// @emem Topic tag field - remove template
	nameLocalType,			// @emem Paragraph tag field - use only type
							//   specifier (first word)
	nameTopic,				// @emem Topic tag field
};

// @struct Describes a component of a topic-name token
// string. A name token can be a literal string, a reference to a
// local (tag) field, or a reference to a topic field.

struct NAMETOKEN {
    enum NAMETYPE nType;    //@field Type of token; see <enum NAMETYPE>.
    CString sTag;           //@field Token string, or tag name.
    int  nField;            //@field Number of field referenced.
};
typedef NAMETOKEN *PNAMETOKEN;


// @enum Different types of IF conditions to evaluate.

enum  IFTYPE
{
	ifNone,			//@emem Non-type
	ifTopicExists,	//@emem Lookup log file to see if topic exists - exists($1)
	ifExpression,	//@emem Compare fields in topic, para, or text tag - $1==$topic.1
    ifTagExists,	//@emem See if specified tag exists somewhere in topic - tagexists(parm)
    ifFieldEmpty,	//@emem See if field is empty - fieldempty(1)
};

/*-----------------------------------------------------------------------
    @doc EXTERNAL AUTODUCK
    
    @struct TYPEIF | A condition used to evaluate whether a type
	formatting string should be used within a particular topic block.
*/

	
struct IFCONDITION {
    IFCONDITION *next;			//@field Next entry in list
    enum IFTYPE nType;			//@field Type of if condition. See <t IFTYPE>.
    int  anTokens[2];			//@field How many tokens in the corresponding cell of apNameTok.
    
    //@field Array of pointers to <t NAMETOKEN> structs describing 
    // "if" operand or topic name. Only one cell is used if the 
    // condition is a topic log check.

	NAMETOKEN apNameTok[2][MAXTOPICNAMETOKENS];

    int  nParam1;				//@field Numeric parameter
    CString sParam1;    		//@field String parameter
};
typedef IFCONDITION *PIFCONDITION;


int ParseTopicNameMask(const char *&sz, PNAMETOKEN pNameTok, int &nTokens, int nFields);
int ParseNameToken(const char *&sz, PNAMETOKEN pNameTok, int nFields);

int GetIfCondition(const char *sz, PIFCONDITION &pIf, int nFields = MAXNUMFIELDS);
void InitName(PNAMETOKEN pNameTok, int nTokens);

                        
void PrintName(char *szNameBuf, PNAMETOKEN pNameTok, int nTokens, CTag *ptagTag, CTag *ptagTopic);

BOOL EvalIfCondition(PIFCONDITION pIf, CTopicLog *pLog, CTagList *plistTags, CTag *ptagTag);
