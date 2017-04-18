/*
 * parse.c
 */

#include <afx.h>
#include <afxtempl.h>
#include "parse.h"


void ZeroMem(void *p, size_t nLen)
{
	memset(p, 0, nLen);
}

const char *MatchParen(
	const char *sz, 
	char chEndMatch, 
	int nSkipEmbedded)
{
    ++sz;
	while(*sz && *sz != chEndMatch)
    {
		if(nSkipEmbedded)
		{
	        switch(*sz)
	        {
	        case chOpenParen:
	            sz = MatchParen(sz, chCloseParen, TRUE);
	            if(*sz)
	                ++sz;
	            break;

	        case chOpenBracket:
	            sz = MatchParen(sz, chCloseBracket, TRUE);
	            if(*sz)
	                ++sz;
	            break;

			case chOpenAngle:
				sz = MatchParen(sz, chCloseAngle, TRUE);
				if(*sz)
					++sz;
				break;
			
			default:
				++sz;
				break;
			}
		}
		else
		{
			switch(*sz)
			{
	        case chOpenParen:
	        case chOpenBracket:
			case chOpenAngle:
				return sz;
			
			default:
				++sz;
				break;
			}
		}
    }

	return sz;
}


/*
@func Searches backward through a line and retreats past white space
characters.

@rdesc Position of first non-white character preceding starting point,
or <p szStart>, whichever comes first..

@ex The following example returns the space following letter "w": |

Foobaria pentaria how                          grubstake
                    ^                          ^
          result ---+                          +--starting point
*/

const char *TrimWhite(
    const char *sz,       //@parm Starting point for backwards search
    const char *szBound)  //@parm First legal position to search (backwards 
          		          // boundary)
{
    ASSERT(sz);
    ASSERT(szBound);
    ASSERT(sz > szBound);

    for(sz--; sz != szBound && isspace(*sz); sz--);

    return sz;
}



/*-----------------------------------------------------------------------
@doc EXTERNAL AUTODUCK
        
@func char * | EatWhite | Advances past whitespace characters and
returns first non-white character.
            
@parm char * | sz | Specifies beginning of white text.
    
@rdesc Returns a pointer to the first non-white character following
<p sz>.

*/
const char *EatWhite(const char *sz)
{
    ASSERT(sz);
    
    while(isspace(*sz))
        sz++;

    return sz;
}


/*-----------------------------------------------------------------------
@doc EXTERNAL AUTODUCK
        
@func char * | EatWhiteNl | Advances past whitespace characters and
returns first non-white character. Keeps track of current line
number.
            
@parm char * | sz | Specifies beginning of white text.

@parm int * | pnLine | Specifies a pointer to the current
line count. 
    
@rdesc Returns a pointer to the first non-white character following
<p sz>.

*/
const char *EatWhiteNl(const char *sz, int *pnLineNum)
{
    // Skip leading whitespace

    while (isspace(*sz))
    {
        if (*sz++ == '\n')
        {
            ++(*pnLineNum);
        }
    }
    return sz;
}



/*-----------------------------------------------------------------------
@doc EXTERNAL AUTODUCK
        
@func char * | SeekChar | Advances past whitespace characters to
the specified character.
            
@parm char * | sz | Specifies beginning of text.
    
@rdesc Returns a pointer to the character or NULL if the first non-white
character is not the specified character.

*/
const char *SeekChar(const char *sz, char ch)
{
    sz = EatWhite(sz);
    if(*sz != ch)
        return NULL;
    return sz;
}


/*-----------------------------------------------------------------------
@doc EXTERNAL AUTODUCK
        
@func char * | SeekNumber | Advances past whitespace characters to
the first numeric character.
            
@parm char * | sz | Specifies beginning of text.
    
@rdesc Returns a pointer to the number or NULL if the first non-white
character is not a number.

*/
const char *SeekNumber(const char *sz)
{
    sz = EatWhite(sz);
    if(!isdigit(*sz))
        return NULL;
    return sz;
}


/*-----------------------------------------------------------------------
@doc EXTERNAL AUTODUCK
        
@func char * | SeekLetter | Advances past whitespace characters to
the first alphabetic character.
            
@parm char * | sz | Specifies beginning of text.
    
@rdesc Returns a pointer to the letter or NULL if the first non-white
character is not a letter.

*/
const char *SeekLetter(const char *sz)
{
    sz = EatWhite(sz);
    if(!isalpha(*sz))
        return NULL;
    return sz;
}


/*-----------------------------------------------------------------------
@doc EXTERNAL AUTODUCK
        
@func char * | MakeNumber | Constructs an integer value from text.
            
@parm char * | sz | Specifies beginning of integer text.
    
@parm int * | pi | Specifies where to store the integer value.
    
@rdesc Returns a pointer to the first non-number character following
<p sz>.

*/
const char *MakeNumber(const char *sz, int &i)
{
    int bNeg;

    ASSERT(sz);
    
    if(*sz == chMinus)
    {
        sz++;
        if(!isdigit(*sz))
            return NULL;
            
        bNeg = TRUE;
    }
    else
    {
        bNeg = FALSE;
    }

    for(i = 0; isdigit(*sz); sz++)
        i = i*10 + (*sz-'0');

    if(bNeg)
        i *= -1;

    return sz;
}



const char *SeekEnd(const char *szSrc, const char *szStopChars, int nMax)
{
    int i;

    ASSERT(szSrc);
    ASSERT(szStopChars);
    ASSERT(nMax > 0);

    // Seek a stop char.
    for(i = 0; i < nMax && *szSrc && !strchr(szStopChars, *szSrc); 
        szSrc++, i++);

	// Detect overflow situation
	if(nMax == i && (szSrc[i] && !strchr(szStopChars, *szSrc)))
		return NULL;

    return szSrc;
}



const char *SeekEnd(const char *szSrc, char chStopChar, int nMax)
{
    int i;

    ASSERT(szSrc);
    ASSERT(nMax > 0);

    // Seek a stop char.
    for(i = 0; i < nMax && *szSrc && *szSrc != chStopChar; szSrc++, i++);

	// Detect overflow situation
	if(nMax == i && (szSrc[i] && *szSrc != chStopChar))
		return NULL;

    return szSrc;
}




