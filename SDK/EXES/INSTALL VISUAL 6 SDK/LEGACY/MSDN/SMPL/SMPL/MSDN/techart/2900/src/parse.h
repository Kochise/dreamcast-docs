/*
 * parse.h
 */

const chPound       = '#';
const chAtSign      = '@';
const chNewline  	= '\n';
const chTab      	= '\t';
const chComma    	= ',';
const chMinus    	= '-';
const chFalse    	= '0';
const chTrue     	= '1';
const chQuote    	= '"';
const chDollar   	= '$';
const chPeriod   	= '.';
const chSpace    	= ' ';
const chAsterisk 	= '*';
const chQuestion 	= '?';
const chAmpersand	= '&';
const chColon    	= ':';
const chCaret		= '^';
const chPipe     	= '|';
const chOpenParen	= '(';
const chCloseParen	= ')';
const chOpenBracket	= '[';
const chCloseBracket= ']';
const chOpenCurly 	= '{';
const chCloseCurly 	= '}';
const chOpenAngle	= '<';
const chCloseAngle	= '>';
const chHyphen		= '-';
const chUnderscore  = '_';
const chBackslash	= '\\';
const chSlash		= '/';
const chTilde		= '~';
const chExclamation	= '!';
const chNull 		= '\0';
const chEqual       = '=';
const chSingleQuote = '\'';
const chSemicolon   = ';';
const chDoubleQuote = '"';

// Array of pointers to strings

typedef CTypedPtrArray<CPtrArray, CString *> CStrArray;

// Function Prototypes

#define isidchar(ch)((isalnum(ch) || ch == chUnderscore))

#define istagchar(ch)(isidchar(ch) || ch == chHyphen)

#define iswhite(c)((c == ' ' || c == '\t'))

#define isnoise(c)((c == '*' || c == '-' || c == '+' || c == ';'))

const char *TrimWhite(const char *sz, const char *szStart);
const char *EatWhite(const char *sz);
const char *EatWhiteNl(const char *sz, int *pn);
const char *SeekChar(const char *sz, char ch);
const char *SeekComment(const char *sz);
const char *SeekNumber(const char *sz);
const char *SeekLetter(const char *sz);
const char *SeekEnd(const char *szSrc, const char *szStopChars, int nMax);
const char *SeekEnd(const char *szSrc, char chStopChar, int nMax);

const char *MakeNumber(const char *sz, int &i);
const char *MatchParen(const char *sz, char chEndMatch, int nSkipEmbedded = TRUE);

void ZeroMem(void *p, size_t nLen);
