// MFCTALK.CPP - Implementation file for your Internet Server
//    MFCTalk Extension

#include <afx.h>
#include <afxwin.h>
#include <afxisapi.h>
#include <afxmt.h>		// for locking

#include <winsock.h>	// for address translation

#include "resource.h"
#include "MFCTalk.h"

#pragma comment(lib, "wsock32.lib")	// for winsock

#define MAX_LIST_SIZE 20

///////////////////////////////////////////////////////////////////////
// command-parsing map

BEGIN_PARSE_MAP(CMFCTalkExtension, CHttpServer)

	ON_PARSE_COMMAND(Default, CMFCTalkExtension, ITS_I4)
	ON_PARSE_COMMAND_PARAMS("Times=0")
	DEFAULT_PARSE_COMMAND(Default, CMFCTalkExtension)
	ON_PARSE_COMMAND(Refresh, CMFCTalkExtension, ITS_I4)
	ON_PARSE_COMMAND(Comment, CMFCTalkExtension, ITS_PSTR)
 	ON_PARSE_COMMAND_PARAMS("Says")
END_PARSE_MAP(CMFCTalkExtension)

///////////////////////////////////////////////////////////////////////
// The one and only CMFCTalkExtension object

CMFCTalkExtension theExtension;


///////////////////////////////////////////////////////////////////////
// CMFCTalkExtension implementation

CMFCTalkExtension::CMFCTalkExtension()
{
}

CMFCTalkExtension::~CMFCTalkExtension()
{
	m_ListContent.RemoveAll();
}

BOOL CMFCTalkExtension::GetExtensionVersion(HSE_VERSION_INFO* pVer)
{
	// Call default implementation for initialization
	CHttpServer::GetExtensionVersion(pVer);

	// Load description string
	TCHAR sz[HSE_MAX_EXT_DLL_NAME_LEN+1];
	ISAPIVERIFY(::LoadString(AfxGetResourceHandle(),
			IDS_SERVER, sz, HSE_MAX_EXT_DLL_NAME_LEN));
	_tcscpy(pVer->lpszExtensionDesc, sz);

	srand(1234);	// how random!

	return TRUE;
}

///////////////////////////////////////////////////////////////////////
// CMFCTalkExtension command handlers

void CMFCTalkExtension::GetCharacter()
{
	// make a person who isn't here say something funny

	int nPerson = rand() % 7;
	LPTSTR strPerson;
	LPTSTR strSays;
	
	switch (nPerson)
	{
	case 0:
		strPerson = "Marilyn M.";
		strSays = "Hello, Sailor!";
		break;

	case 1:
		strPerson = "Richard N.";
		strSays = "People have gotta know if their president is a crook.";
		break;

	case 2:
		strPerson = "Bill";
		strSays = "Does anybody know what we closed at?";
		break;

	case 3:
		strPerson = "Mike B.";
		strSays = "I'm the man!";
 		break;

	case 4:
		strPerson = "John K.";
		strSays = "What can I do for my country?";
		break;

	case 5:
		strPerson = "Charles B.";
		strSays = "Some days you're Superman, and some days you're Clark Kent.";
		break;

	case 6:
		strPerson = "Flea";
		strSays = "You've got to play music like you really mean it.";
		break;
 	}

	AddComment(strPerson, strSays);
	return;
} 

void CMFCTalkExtension::WriteChatForm(CHttpServerContext* pCtxt)
{
	// dump HTML to make the form

	*pCtxt << "<h2>Welcome to MFCTalk!</h2><hr>";
	*pCtxt << "<FORM ACTION=\"MFCTalk.dll?Comment\" \"METHOD=\"POST\">";
	*pCtxt << "Type something you'd like to share:<p>";
	*pCtxt << "<INPUT TYPE=\"text\" NAME=\"Says\" SIZE=60><p>";
	*pCtxt << "<INPUT TYPE=\"submit\" VALUE=\"Send\">";
	*pCtxt << "</FORM><FORM ACTION=\"MFCTalk.dll?Refresh\" \"METHOD=\"POST\">";
 	*pCtxt << "<INPUT TYPE=\"submit\" VALUE=\"Refresh\">";
	*pCtxt << "Show Message Times<INPUT TYPE=\"checkbox\" NAME=\"Times\" CHECKED=\"1\">";
	*pCtxt << "</FORM><hr>";
} 

void CMFCTalkExtension::WriteRoomContent(CHttpServerContext* pCtxt, int nTimes)
{
	// through the list backwards (because that's time order)

	m_ListCritical.Lock();

	POSITION pos;
	pos = m_ListContent.GetTailPosition();

	// print something nice if there's no list

	if (pos == NULL)
		*pCtxt << "<i>Nobody has said anything yet.</i><p>";
	else
	{
		CString strThisOne;
		while (pos != NULL)
		{
			LPCTSTR strThisOne = m_ListContent.GetPrev(pos);
			if (nTimes == 0)
			{
				strThisOne = _tcschr(strThisOne, ' ');
				if (strThisOne == NULL)
					continue;
				strThisOne++;
			}
			*pCtxt << strThisOne;
		}
	}

	m_ListCritical.Unlock();
}

void CMFCTalkExtension::Default(CHttpServerContext* pCtxt, int nTimes)
{
	// by default, show the form and show the content

	StartContent(pCtxt);
	WriteTitle(pCtxt);

	WriteChatForm(pCtxt);
	WriteRoomContent(pCtxt, nTimes);

	EndContent(pCtxt);
}

void CMFCTalkExtension::AddComment(LPCTSTR pstrName, LPCTSTR pstrSays)
{
	// someone said something... add it to the list

	m_ListCritical.Lock();

	CString str;
	CTime timing = CTime::GetCurrentTime();

	str = timing.Format("%H:%M:%S ");

	str += "<b>";
	str += pstrName;
	str += "</b>:";
	str += pstrSays;
	str += "<p>";

	m_ListContent.AddTail(str);

	// is the list too big?

	if (m_ListContent.GetCount() > MAX_LIST_SIZE)
		m_ListContent.RemoveHead();

	m_ListCritical.Unlock();
} 

void CMFCTalkExtension::Refresh(CHttpServerContext* pCtxt, int nTimes)
{
	// if we're refreshing, just have a character say something
	// and dump the form and the list again

	if (nTimes)

	GetCharacter();
	Default(pCtxt, nTimes);
}

void CMFCTalkExtension::StartContent(CHttpServerContext* pCtxt)
{
	// remember to say taht the content always expires!

	AddHeader(pCtxt, "Pragma: no-cache\r\n");
	CHttpServer::StartContent(pCtxt);
}

void CMFCTalkExtension::Comment(CHttpServerContext* pCtxt, LPCTSTR pstr)
{
	StartContent(pCtxt);
	WriteTitle(pCtxt);

	// l-trim what they said

	while (_istspace(*pstr))
		pstr++;

	if (*pstr != NULL)
	{
		TCHAR sz[80];
 		DWORD dwSize = 80;

		// query the user's IP address
		if (!pCtxt->GetServerVariable("REMOTE_HOST", sz, &dwSize))
			_tcscpy(sz, "<i>unknown</i>");
		else
		{
			// convert to binary address
			char nAddr[4];
			nAddr[0] = nAddr[1] = nAddr[2] = nAddr[3] = 0;
			int nIndex = 0;
			char *pstr = sz;

			while (*pstr != '\0' && nIndex < 4)
			{
				if (*pstr == '.')
					nIndex++;
				else
				{
					nAddr[nIndex] *= 10;
					nAddr[nIndex] += (*pstr - '0');
				}
				pstr++;
			}

			// ask WinSock for host name
			HOSTENT* pResult;
			pResult = gethostbyaddr((const char*) &nAddr, 4, PF_INET);
			if (pResult == NULL)
				_tcscat(sz, " <i>(unresolved)</i>");
			else
				_tcscpy(sz, pResult->h_name);
		}

		// finally, add it!
		AddComment(sz, pstr);
	}

	// rewrite everything
	 
	WriteChatForm(pCtxt);
	WriteRoomContent(pCtxt, 1);

	EndContent(pCtxt);
}

///////////////////////////////////////////////////////////////////////
// If your extension will not use MFC, you'll need this code to make
// sure the extension objects can find the resource handle for the
// module.  If you convert your extension to not be dependent on MFC,
// remove the comments arounn the following AfxGetResourceHandle()
// and DllMain() functions, as well as the g_hInstance global.

/****

static HINSTANCE g_hInstance;

HINSTANCE AFXISAPI AfxGetResourceHandle()
{
	return g_hInstance;
}

BOOL WINAPI DllMain(HINSTANCE hInst, ULONG ulReason,
					LPVOID lpReserved)
{
	if (ulReason == DLL_PROCESS_ATTACH)
	{
		g_hInstance = hInst;
	}

	return TRUE;
}

****/
