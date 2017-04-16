#include <afx.h>
#include <afxtempl.h>
#include "parse.h"
#include "topiclog.h"
#include "errmsg.h"

/**************************************************************************
 Tag Class
 **************************************************************************/

CTag::CTag(void)
{
    nFields = 0;
    ZeroMem(aszFieldText, sizeof(char *)*MAXNUMFIELDS);
    ZeroMem(anFieldLen, sizeof(int)*MAXNUMFIELDS);
    ZeroMem(&nState, sizeof(nState));
    lSrcLineNum = 0;
}



CTag::~CTag(void)
{
	FreeText();
}

void CTag::FreeText(void)
{
    int i;

    for(i = 0; i < nFields; i++)
    {
        if(aszFieldText[i])
		{
            delete aszFieldText[i];
			aszFieldText[i] = NULL;
		}
    }
}


/**************************************************************************
 Topic Class
 **************************************************************************/

CTopic::CTopic(void)
{
    m_nWeight = 0;
    m_lOffset = 0;
    m_nDocTag = -1;
	m_lSrcLineNum = 0;
    m_nSrcFn = 0;
}

CTopic::~CTopic(void)
{
    CTag *ptag;

    POSITION pos = m_listTags.GetHeadPosition();
    while( pos )
    {
        ptag = m_listTags.GetNext(pos);
        delete ptag;
    }
}


void CTopic::FreeTagText(void)
{
    CTag *ptag;

    POSITION pos = m_listTags.GetHeadPosition();
    while(pos)
    {
        ptag = m_listTags.GetNext(pos);
        
        ptag->FreeText();
    }
}

void CTopic::SetName(const char *sz)
{
    ASSERT(sz);

    m_sName = sz;
}


void CTopic::SetContext(const char *sz)
{
    ASSERT(sz);

    m_sCtx = sz;
}


void CTopic::SetWeight(int n)
{
    m_nWeight = n;
}


void CTopic::SetOffset(long l)
{
    m_lOffset = l;
}


void CTopic::SetTags(CTagList& listTags)
{
    POSITION pos = listTags.GetHeadPosition();
    while( pos )
        m_listTags.AddTail( listTags.GetNext(pos) );
}


const char *CTopic::GetName(void)
{
    return m_sName;
}


const char *CTopic::GetContext(void)
{
    return m_sCtx;
}



int CTopic::CompareContext(CTopic &t)
{
    return _stricmp(m_sCtx, t.m_sCtx);
}


int CTopic::Compare(CTopic &t)
{
    if(m_nWeight < t.m_nWeight)
        return -1;
    else if(m_nWeight > t.m_nWeight)
        return 1;

    return _stricmp(m_sName, t.m_sName);
}


CTag *CTopic::GetTopicTag(void)
{
    if(m_listTags.IsEmpty()) 
        return NULL;
    else 
        return m_listTags.GetHead(); 
}


int CTopic::Write(CFile &f)
{
TRY
{
    if(m_listTags.GetCount() == 0)
        return 0;
    
    m_lOffset = f.GetPosition();

    CTag *p;
    int i;

    POSITION pos = m_listTags.GetHeadPosition();
    while(pos)
    {
        p = m_listTags.GetNext( pos );

        for(i = 0; i < p->nFields; i++)
        {
            f.Write(p->aszFieldText[i], p->anFieldLen[i]);
			
			delete p->aszFieldText[i];

            p->aszFieldText[i] = NULL;
        }
    }

    return 0;
}
CATCH(CFileException, e)
{
    return e->m_cause;
}
END_CATCH
}




int CTopic::Read(CFile &f)
{
TRY
{
    if(!HasTags())
        return 0;
    
    long lPos = f.Seek( m_lOffset, CFile::begin );
	ASSERT(lPos == m_lOffset);

    CTag *  p;

    int     i;
    POSITION pos = m_listTags.GetHeadPosition();
    while( pos )
    {
        p = m_listTags.GetNext(pos);

        for(i = 0; i < p->nFields; i++)
		{
	        p->aszFieldText[i] = new char[p->anFieldLen[i]+1];

            f.Read(p->aszFieldText[i], p->anFieldLen[i]);
            p->aszFieldText[i][p->anFieldLen[i]] = '\0';
        }
    }

    return 0;
}
CATCH(CFileException, e)
{
    return e->m_cause;
}
END_CATCH
}


#ifdef _DEBUG
void CTopic::Dump( CDumpContext &dc ) const
{
    dc << "CTopic " 		<< m_sName
       << " ID: "   		<< m_sCtx
       << " Source #: " 	<< m_nSrcFn 
       << " Doc tags #: " 	<< m_nDocTag
       << " Tags: \r\n";

    CTag *p;
    int i;
    POSITION pos = m_listTags.GetHeadPosition();
    while(pos)
    {
        p = m_listTags.GetNext(pos);

        dc << "\t" << "Tag: " << p->sTag << " with "
           << p->nFields << " fields;";


        for(i = 0; i < p->nFields; i++)
        {
            dc << " " << p->anFieldLen[i];
        }

        dc << "\r\n";
    }
}
#endif

/**************************************************************************
 Topic Log Class
 **************************************************************************/

CTopicLog::CTopicLog(void)
{
    m_apTopicSort = NULL;
    m_apTopicOutput = NULL;
    m_nTopics = 0;
    m_bIsSorted = NULL;
}


CTopicLog::~CTopicLog()
{

    if(m_apTopicSort)
        delete[] m_apTopicSort;

    CTopic *p;
    CString s;
    
    POSITION pos = m_listTopics.GetHeadPosition();
	while( pos != NULL)
    {
        p = m_listTopics.GetNext(pos);
        delete p;
    }

    m_listTopics.RemoveAll();

	int i, n;
    for(i = 0, n = m_asDocTags.GetSize(); i < n; i++)
        delete m_asDocTags[i];

	m_asDocTags.RemoveAll();

    for(i = 0, n = m_asSrcFn.GetSize(); i < n; i++)
        delete m_asSrcFn[i];

	m_asSrcFn.RemoveAll();
}


void CTopicLog::Add(CTopic *pTopic, int nOptions)
{
	const char *szAddContext = pTopic->GetContext();
	
	POSITION pos = m_listTopics.GetHeadPosition();
	POSITION posCur;
	CTopic *p, *pMatch = NULL;
	
	while( pos != NULL)
	{
		posCur = pos;
		p = m_listTopics.GetNext( pos );

		if(strcmp(p->GetContext(), szAddContext) == 0)
		{
			pMatch = p;
			break;
		}
	}

	// If overwriting empty, delete any matching item
	// and add the new one to the end.

	if(((nOptions & AddOverwrite) && pMatch) ||
	   ((nOptions & AddGenerateUnique) && pMatch && !pMatch->HasTags()))
	{
		m_listTopics.RemoveAt(posCur);
		delete pMatch;
	}

	// If generating unique, and we find a match, take
	// a walk through the topic list and keep looking
	// for dupes until we have a unique context string.

	else if((nOptions & AddGenerateUnique) && pMatch)
	{
		CString sNewContext;
		CTopic *pNext;
		char szNum[10];
		int n = 1;
		do
		{
			sprintf(szNum, "_%d", n);
			sNewContext = szAddContext;
			sNewContext += szNum;
			pMatch = NULL;
			while( pos )
			{
				pNext = m_listTopics.GetNext( pos );
				if(sNewContext.Compare(pNext->GetContext()) == 0)
				{
					pMatch = pNext;
					break;
				}
			}
			n++;

		} while(pMatch);
		
		pTopic->SetContext(sNewContext);
	}

	// Add the topic

	m_listTopics.AddTail(pTopic);
}


BOOL CTopicLog::Search(const char *szID, CTopic *&p)
{
    ASSERT(m_apTopicSort);
		
	p = NULL;

	int iFirst, iLast, i, nRet;

	iFirst = 0;
	iLast = m_listTopics.GetCount()-1;
	while(iFirst <= iLast)
	{
		i = (iFirst + iLast) / 2;

		ASSERT(m_apTopicSort[i]);

		nRet = _stricmp(szID, m_apTopicSort[i]->GetContext());

		if(nRet > 0)
		{
			iFirst = i+1;
		}
		else if(nRet < 0)
		{
			iLast = i-1;
		}
		else
		{
			p = m_apTopicSort[i];
			return TRUE;
		}
	}
	
	return FALSE;
}


int CompareLogsWeighted(const void *elem1, const void *elem2)
{
    CTopic *p1, *p2;

    p1 = *(CTopic **)elem1;
    p2 = *(CTopic **)elem2;

    ASSERT(p1 && p2);

    return p1->Compare(*p2);
}

int CompareLogs(const void * elem1, const void * elem2)
{
    CTopic *p1, *p2;

    p1 = *(CTopic **)elem1;
    p2 = *(CTopic **)elem2;

    ASSERT(p1 && p2);

    return p1->CompareContext(*p2);
}

void CTopicLog::Sort(BOOL bOutputSorted)
{
    if(m_apTopicSort)
    {
        delete[] m_apTopicSort;
        delete[] m_apTopicOutput;
    }

    m_apTopicSort = new CTopic*[GetLogCount()];
    m_apTopicOutput = new CTopic*[GetLogCount()];

    CTopic *pTopic;
	UINT nLogTopics;
    CString s;

	nLogTopics = 0;
    m_nTopics = 0;
    POSITION pos = m_listTopics.GetHeadPosition();

    while(pos)
    {
        pTopic = m_listTopics.GetNext( pos );

        m_apTopicSort[nLogTopics++] = pTopic;

        if(pTopic->HasTags())
            m_apTopicOutput[m_nTopics++] = pTopic;
    }

    m_bIsSorted = FALSE;
        
    qsort(m_apTopicSort, nLogTopics, sizeof(CTopic *), 
    		CompareLogs);

    if(bOutputSorted)
	{
    	qsort(m_apTopicOutput, m_nTopics, sizeof(CTopic *), 
            CompareLogsWeighted);
	}

    m_bIsSorted = TRUE;
}


CTopic *CTopicLog::GetTopicSortOrder(UINT i)
{
    ASSERT(m_apTopicSort);
    ASSERT(i >= 0 && i < m_nTopics);

    if(i >= 0 && i < m_nTopics)
        return m_apTopicSort[i];

    return NULL;
}


CTopic *CTopicLog::GetTopicOutputOrder(UINT i)
{
    ASSERT(m_apTopicOutput);
    ASSERT(i >= 0 && i < m_nTopics);

    if(i >= 0 && i < m_nTopics)
        return m_apTopicOutput[i];

    return NULL;
}



#ifdef _DEBUG
void CTopicLog::Dump( CDumpContext &dc ) const
{
	POSITION pos = m_listTopics.GetHeadPosition();

    dc << "CTopicLog: " << m_listTopics.GetCount() 
       << " topics.\r\n";

    CString s;
    CObject *p;
    while(pos != NULL)
    {
        p = m_listTopics.GetNext( pos );

        dc << *p;   
    }
}
#endif



int CTopicLog::Print(
    const char *szFile,         // @parm File to print to.
    int  bConcat)               // @parm Whether to concatenate
{
TRY
{
    CFile file;
	CFileException e;
	CFileStatus r;
	const char *sz;

	int nOpenFlags;

    if(bConcat & file.GetStatus(szFile, r))
		nOpenFlags = CFile::modeReadWrite;
	else
		nOpenFlags = CFile::modeCreate | CFile::modeWrite;

	if(!file.Open(szFile, nOpenFlags, &e))
		return e.m_cause;

	if(bConcat)
		file.SeekToEnd();

    CTopic *pTopic;
    CString s;
	UINT nTopics = GetLogCount();

    for(UINT i = 0; i < nTopics; i++)
    {
        pTopic = m_apTopicSort[i];

        if(pTopic->HasTags())
        {
			sz = pTopic->GetContext();
			file.Write(sz, strlen(sz));
			file.Write("\r\n", 2);
        }
    }

	file.Close();

    return 0;
}
CATCH(CFileException, e)
{
	return e->m_cause;
}
END_CATCH
}



int CTopicLog::AddSrcFn(const char *szInput)
{
    CString *psNew = new CString(szInput);

    int n = m_asSrcFn.GetSize();

    m_asSrcFn.SetSize(n+1);
    m_asSrcFn[n] = psNew;

    return n;
}

const char *CTopicLog::GetSrcFn(int n)
{
    if(-1 == n)
    {
        n = m_asSrcFn.GetUpperBound();
    }

    ASSERT(n >= 0 && n < m_asSrcFn.GetSize());

    return *m_asSrcFn[n];
}

int CTopicLog::AddDocTag(const char *szInput)
{
    CString *psNew = new CString(szInput);

    int n = m_asDocTags.GetSize();

    m_asDocTags.SetSize(n+1);
    m_asDocTags[n] = psNew;

    return n;
}

const char *CTopicLog::GetDocTag(int n)
{
    if(-1 == n)
    {
        n = m_asDocTags.GetUpperBound();
    }

    ASSERT(n >= 0 && n < m_asDocTags.GetSize());

    return *m_asDocTags[n];
}

