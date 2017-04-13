// ReplaceDlg.cpp : implementation file
//

#include "stdafx.h"
#include "ReplAll.h"
#include "ReplaceDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CReplaceDlg dialog


CReplaceDlg::CReplaceDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CReplaceDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CReplaceDlg)
	//}}AFX_DATA_INIT
}


void CReplaceDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CReplaceDlg)
	DDX_Control(pDX, IDC_REPLTEXT, m_ReplaceText);
	DDX_Control(pDX, IDC_FINDTEXT, m_FindText);
	DDX_Control(pDX, IDC_WHOLEWORD, m_MatchWholeWord);
	DDX_Control(pDX, IDC_REGEXP, m_RegularExpression);
	DDX_Control(pDX, IDC_MATCHCASE, m_MatchCase);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CReplaceDlg, CDialog)
	//{{AFX_MSG_MAP(CReplaceDlg)
	ON_BN_CLICKED(IDC_REGEXPFIND, OnRegexpfind)
	ON_BN_CLICKED(IDC_REGEXPREPLACE, OnRegExpReplace)
	ON_COMMAND(ID_OPTIONS_QUOTEDSTRING, CommandQuotedString)
	ON_COMMAND(ID_OPTIONS_ANYCHARACTER, CommandAnyChar)
	ON_COMMAND(ID_OPTIONS_CHARACTERINRANGE, CommandInRange)
	ON_COMMAND(ID_OPTIONS_CHARACTERNOTINRANGE, CommandNotInRange)
	ON_COMMAND(ID_OPTIONS_BEGINNINGOFLINE, CommandBeginOL)
	ON_COMMAND(ID_OPTIONS_ENDOFLINE, CommandEOL)
	ON_COMMAND(ID_OPTIONS_TAGGEDEXPRESSION, CommandTaggedExp)
	ON_COMMAND(ID_OPTIONS_NOT, CommandNot)
	ON_COMMAND(ID_OPTIONS_OR, CommandOr)
	ON_COMMAND(ID_OPTIONS_0ORMOREMATCHES, Command0OrMore)
	ON_COMMAND(ID_OPTIONS_1ORMOREMATCHES, Command1OrMore)
	ON_COMMAND(ID_OPTIONS_GROUP, CommandGroup)
	ON_COMMAND(ID_OPTIONS_WHITESPACE, CommandWhitespace)
	ON_COMMAND(ID_OPTIONS_ALPHANUMERICCHARACTER, CommandAlphaNumericCharacter)
	ON_COMMAND(ID_OPTIONS_ALPHABETICCHARACTER, CommandAlphaCharacter)
	ON_COMMAND(ID_OPTIONS_DECIMALDIGIT, CommandDecDigit)
	ON_COMMAND(ID_OPTIONS_HEXADECIMALNUMBER, CommandHexNumber)
	ON_COMMAND(ID_OPTIONS_NUMBER, CommandNumber)
	ON_COMMAND(ID_OPTIONS_INTEGER, CommandInteger)
	ON_COMMAND(ID_OPTIONS_CCIDENTIFIER, CommandCIdentifier)
	ON_COMMAND(ID_OPTIONS_ALPHABETICSTRING, CommandAlphabeticString)
	ON_COMMAND(ID_OPTIONS2_FINDWHATTEXT, CommandFindWhatText)
	ON_COMMAND(ID_OPTIONS2_TAGGEDEXPRESSION1, CommandTaggedExpression1)
	ON_COMMAND(ID_OPTIONS2_TAGGEDEXPRESSION2, CommandTaggedExpression2)
	ON_COMMAND(ID_OPTIONS2_TAGGEDEXPRESSION3, CommandTaggedExpression3)
	ON_COMMAND(ID_OPTIONS2_TAGGEDEXPRESSION4, CommandTaggedExpression4)
	ON_COMMAND(ID_OPTIONS2_TAGGEDEXPRESSION5, CommandTaggedExpression5)
	ON_COMMAND(ID_OPTIONS2_TAGGEDEXPRESSION6, CommandTaggedExpression6)
	ON_COMMAND(ID_OPTIONS2_TAGGEDEXPRESSION7, CommandTaggedExpression7)
	ON_COMMAND(ID_OPTIONS2_TAGGEDEXPRESSION8, CommandTaggedExpression8)
	ON_COMMAND(ID_OPTIONS2_TAGGEDEXPRESSION9, CommandTaggedExpression9)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

void CReplaceDlg::CommandAnyChar(WPARAM, LPARAM)
{
	switch (m_lEmulation)
	{
		case dsDevStudio:
			m_FindText.ReplaceSel(_T("."));
			break;
		case dsVC2:
			m_FindText.ReplaceSel(_T("."));
			break;
		case dsBrief:
			m_FindText.ReplaceSel(_T("?"));
			break;
		case dsEpsilon:
			m_FindText.ReplaceSel(_T("."));
			break;
		case dsCustom:
			m_FindText.ReplaceSel(_T("."));
			break;
	}
	m_RegularExpression.SetCheck(1);
}

void CReplaceDlg::CommandInRange(WPARAM, LPARAM)
{
	switch (m_lEmulation)
	{
		case dsDevStudio:
			m_FindText.ReplaceSel(_T("[]"));
			break;
		case dsVC2:
			m_FindText.ReplaceSel(_T("[]"));
			break;
		case dsBrief:
			m_FindText.ReplaceSel(_T("[]"));
			break;
		case dsEpsilon:
			m_FindText.ReplaceSel(_T("[]"));
			break;
		case dsCustom:
			m_FindText.ReplaceSel(_T("[]"));
			break;
	}
	m_RegularExpression.SetCheck(1);
}

void CReplaceDlg::CommandNotInRange(WPARAM, LPARAM)
{
	switch (m_lEmulation)
	{
		case dsDevStudio:
			m_FindText.ReplaceSel(_T("[^]"));
			break;
		case dsVC2:
			m_FindText.ReplaceSel(_T("[^]"));
			break;
		case dsBrief:
			m_FindText.ReplaceSel(_T("[~]"));
			break;
		case dsEpsilon:
			m_FindText.ReplaceSel(_T("[^]"));
			break;
		case dsCustom:
			m_FindText.ReplaceSel(_T("[^]"));
			break;
	}
	m_RegularExpression.SetCheck(1);
}

void CReplaceDlg::CommandBeginOL(WPARAM, LPARAM)
{
	switch (m_lEmulation)
	{
		case dsDevStudio:
			m_FindText.ReplaceSel(_T("^"));
			break;
		case dsVC2:
			m_FindText.ReplaceSel(_T("^"));
			break;
		case dsBrief:
			m_FindText.ReplaceSel(_T("%"));
			break;
		case dsEpsilon:
			m_FindText.ReplaceSel(_T("^"));
			break;
		case dsCustom:
			m_FindText.ReplaceSel(_T("^"));
			break;
	}
	m_RegularExpression.SetCheck(1);
}

void CReplaceDlg::CommandEOL(WPARAM, LPARAM)
{
	switch (m_lEmulation)
	{
		case dsDevStudio:
			m_FindText.ReplaceSel(_T("$"));
			break;
		case dsVC2:
			m_FindText.ReplaceSel(_T("$"));
			break;
		case dsBrief:
			m_FindText.ReplaceSel(_T("$"));
			break;
		case dsEpsilon:
			m_FindText.ReplaceSel(_T("$"));
			break;
		case dsCustom:
			m_FindText.ReplaceSel(_T("$"));
			break;
	}
	m_RegularExpression.SetCheck(1);
}

void CReplaceDlg::CommandTaggedExp(WPARAM, LPARAM)
{
	switch (m_lEmulation)
	{
		case dsDevStudio:
			m_FindText.ReplaceSel(_T("\\(\\)"));
			break;
		case dsVC2:
			m_FindText.ReplaceSel(_T("\\(\\)"));
			break;
		case dsBrief:
			m_FindText.ReplaceSel(_T("{}"));
			break;
		case dsEpsilon:
			m_FindText.ReplaceSel(_T("()"));
			break;
		case dsCustom:
			m_FindText.ReplaceSel(_T("\\(\\)"));
			break;
	}
	m_RegularExpression.SetCheck(1);
}

void CReplaceDlg::CommandNot(WPARAM, LPARAM)
{
	switch (m_lEmulation)
	{
		case dsDevStudio:
			m_FindText.ReplaceSel(_T("\\~"));
			break;
		case dsVC2:
			m_FindText.ReplaceSel(_T("\\~"));
			break;
		case dsBrief:
			m_FindText.ReplaceSel(_T("~"));
			break;
		case dsEpsilon:
			m_FindText.ReplaceSel(_T("~"));
			break;
		case dsCustom:
			m_FindText.ReplaceSel(_T("\\~"));
			break;
	}
	m_RegularExpression.SetCheck(1);
}

void CReplaceDlg::CommandOr(WPARAM, LPARAM)
{
	switch (m_lEmulation)
	{
		case dsDevStudio:
			m_FindText.ReplaceSel(_T("\\!"));
			break;
		case dsVC2:
			m_FindText.ReplaceSel(_T("\\!"));
			break;
		case dsBrief:
			m_FindText.ReplaceSel(_T("|"));
			break;
		case dsEpsilon:
			m_FindText.ReplaceSel(_T("|"));
			break;
		case dsCustom:
			m_FindText.ReplaceSel(_T("\\!"));
			break;
	}
	m_RegularExpression.SetCheck(1);
}

void CReplaceDlg::Command0OrMore(WPARAM, LPARAM)
{
	switch (m_lEmulation)
	{
		case dsDevStudio:
			m_FindText.ReplaceSel(_T("*"));
			break;
		case dsVC2:
			m_FindText.ReplaceSel(_T("*"));
			break;
		case dsBrief:
			m_FindText.ReplaceSel(_T("@"));
			break;
		case dsEpsilon:
			m_FindText.ReplaceSel(_T("*"));
			break;
		case dsCustom:
			m_FindText.ReplaceSel(_T("*"));
			break;
	}
	m_RegularExpression.SetCheck(1);
}

void CReplaceDlg::Command1OrMore(WPARAM, LPARAM)
{
	switch (m_lEmulation)
	{
		case dsDevStudio:
			m_FindText.ReplaceSel(_T("+"));
			break;
		case dsVC2:
			m_FindText.ReplaceSel(_T("+"));
			break;
		case dsBrief:
			m_FindText.ReplaceSel(_T("+"));
			break;
		case dsEpsilon:
			m_FindText.ReplaceSel(_T("+"));
			break;
		case dsCustom:
			m_FindText.ReplaceSel(_T("+"));
			break;
	}
	m_RegularExpression.SetCheck(1);
}

void CReplaceDlg::CommandGroup(WPARAM, LPARAM)
{
	switch (m_lEmulation)
	{
		case dsDevStudio:
			m_FindText.ReplaceSel(_T("\\{\\}"));
			break;
		case dsVC2:
			m_FindText.ReplaceSel(_T("\\{\\}"));
			break;
		case dsBrief:
			m_FindText.ReplaceSel(_T("{}"));
			break;
		case dsEpsilon:
			m_FindText.ReplaceSel(_T("()"));
			break;
		case dsCustom:
			m_FindText.ReplaceSel(_T("\\{\\}"));
			break;
	}
	m_RegularExpression.SetCheck(1);
}

void CReplaceDlg::CommandWhitespace(WPARAM, LPARAM)
{
	switch (m_lEmulation)
	{
		case dsDevStudio:
			m_FindText.ReplaceSel(_T("\\:b+"));
			break;
		case dsVC2:
			m_FindText.ReplaceSel(_T("\\:b+"));
			break;
		case dsBrief:
			m_FindText.ReplaceSel(_T("[ \x09]+"));
			break;
		case dsEpsilon:
			m_FindText.ReplaceSel(_T("[ <tab>]+"));
			break;
		case dsCustom:
			m_FindText.ReplaceSel(_T("\\b:+"));
			break;
	}
	m_RegularExpression.SetCheck(1);
}

void CReplaceDlg::CommandAlphaNumericCharacter(WPARAM, LPARAM)
{
	switch (m_lEmulation)
	{
		case dsDevStudio:
			m_FindText.ReplaceSel(_T("\\:a"));
			break;
		case dsVC2:
			m_FindText.ReplaceSel(_T("\\:a"));
			break;
		case dsBrief:
			m_FindText.ReplaceSel(_T("[a-zA-Z0-9]"));
			break;
		case dsEpsilon:
			m_FindText.ReplaceSel(_T("[a-zA-Z0-9]"));
			break;
		case dsCustom:
			m_FindText.ReplaceSel(_T("\\:a"));
			break;
	}
	m_RegularExpression.SetCheck(1);
}

void CReplaceDlg::CommandAlphaCharacter(WPARAM, LPARAM)
{
	switch (m_lEmulation)
	{
		case dsDevStudio:
			m_FindText.ReplaceSel(_T("\\:c"));
			break;
		case dsVC2:
			m_FindText.ReplaceSel(_T("\\:c"));
			break;
		case dsBrief:
			m_FindText.ReplaceSel(_T("[a-zA-Z]"));
			break;
		case dsEpsilon:
			m_FindText.ReplaceSel(_T("[a-zA-Z]"));
			break;
		case dsCustom:
			m_FindText.ReplaceSel(_T("\\:c"));
			break;
	}
	m_RegularExpression.SetCheck(1);
}

void CReplaceDlg::CommandDecDigit(WPARAM, LPARAM)
{
	switch (m_lEmulation)
	{
		case dsDevStudio:
			m_FindText.ReplaceSel(_T("\\:d"));
			break;
		case dsVC2:
			m_FindText.ReplaceSel(_T("\\:d"));
			break;
		case dsBrief:
			m_FindText.ReplaceSel(_T("[0-9]"));
			break;
		case dsEpsilon:
			m_FindText.ReplaceSel(_T("[0-9]"));
			break;
		case dsCustom:
			m_FindText.ReplaceSel(_T("\\:d"));
			break;
	}
	m_RegularExpression.SetCheck(1);
}

void CReplaceDlg::CommandHexNumber(WPARAM, LPARAM)
{
	switch (m_lEmulation)
	{
		case dsDevStudio:
			m_FindText.ReplaceSel(_T("\\:h"));
			break;
		case dsVC2:
			m_FindText.ReplaceSel(_T("\\:h"));
			break;
		case dsBrief:
			m_FindText.ReplaceSel(_T("[0-9a-fA-F]+"));
			break;
		case dsEpsilon:
			m_FindText.ReplaceSel(_T("[0-9a-fA-F]+"));
			break;
		case dsCustom:
			m_FindText.ReplaceSel(_T("\\:h"));
			break;
	}
	m_RegularExpression.SetCheck(1);
}

void CReplaceDlg::CommandNumber(WPARAM, LPARAM)
{
	switch (m_lEmulation)
	{
		case dsDevStudio:
			m_FindText.ReplaceSel(_T("\\:n"));
			break;
		case dsVC2:
			m_FindText.ReplaceSel(_T("\\:n"));
			break;
		case dsBrief:
			m_FindText.ReplaceSel(
					_T("{[0-9]+.[0-9]@}|{[0-9]@.[0-9]+}|{[0-9]+}"));
			break;
		case dsEpsilon:
			m_FindText.ReplaceSel(_T("([0-9]+.[0-9]*|[0-9]*.[0-9]+|[0-9]+)"));
			break;
		case dsCustom:
			m_FindText.ReplaceSel(_T("\\:n"));
			break;
	}
	m_RegularExpression.SetCheck(1);
}

void CReplaceDlg::CommandInteger(WPARAM, LPARAM)
{
	switch (m_lEmulation)
	{
		case dsDevStudio:
			m_FindText.ReplaceSel(_T("\\:z"));
			break;
		case dsVC2:
			m_FindText.ReplaceSel(_T("\\:z"));
			break;
		case dsBrief:
			m_FindText.ReplaceSel(_T("[0-9]+"));
			break;
		case dsEpsilon:
			m_FindText.ReplaceSel(_T("[0-9]+"));
			break;
		case dsCustom:
			m_FindText.ReplaceSel(_T("\\:z"));
			break;
	}
	m_RegularExpression.SetCheck(1);
}

void CReplaceDlg::CommandCIdentifier(WPARAM, LPARAM)
{
	switch (m_lEmulation)
	{
		case dsDevStudio:
			m_FindText.ReplaceSel(_T("\\:i"));
			break;
		case dsVC2:
			m_FindText.ReplaceSel(_T("\\:i"));
			break;
		case dsBrief:
			m_FindText.ReplaceSel(_T("[a-zA-Z_$][a-zA-Z0-9_$]@"));
			break;
		case dsEpsilon:
			m_FindText.ReplaceSel(_T("[a-zA-Z_$][a-zA-Z0-9_$]*"));
			break;
		case dsCustom:
			m_FindText.ReplaceSel(_T("\\:i"));
			break;
	}
	m_RegularExpression.SetCheck(1);
}

void CReplaceDlg::CommandAlphabeticString(WPARAM, LPARAM)
{
	switch (m_lEmulation)
	{
		case dsDevStudio:
			m_FindText.ReplaceSel(_T("\\:w"));
			break;
		case dsVC2:
			m_FindText.ReplaceSel(_T("\\:w"));
			break;
		case dsBrief:
			m_FindText.ReplaceSel(_T("[a-zA-Z]+"));
			break;
		case dsEpsilon:
			m_FindText.ReplaceSel(_T("[a-zA-Z]+"));
			break;
		case dsCustom:
			m_FindText.ReplaceSel(_T("\\:w"));
			break;
	}
	m_RegularExpression.SetCheck(1);
}

void CReplaceDlg::CommandQuotedString(WPARAM, LPARAM)
{
	switch (m_lEmulation)
	{
		case dsDevStudio:
			m_FindText.ReplaceSel(_T("\\:q"));
			break;
		case dsVC2:
			m_FindText.ReplaceSel(_T("\\:q"));
			break;
		case dsBrief:
			m_FindText.ReplaceSel(_T("\"[~\"]@\""));
			break;
		case dsEpsilon:
			m_FindText.ReplaceSel(_T("\"[~\"]*\""));
			break;
		case dsCustom:
			m_FindText.ReplaceSel(_T("\\:q"));
			break;
	}
	m_RegularExpression.SetCheck(1);
}

void CReplaceDlg::CommandFindWhatText(WPARAM, LPARAM)
{
	switch (m_lEmulation)
	{
		case dsDevStudio:
			m_ReplaceText.ReplaceSel(_T("\\0"));
			break;
		case dsVC2:
			m_ReplaceText.ReplaceSel(_T("\\0"));
			break;
		case dsBrief:
			m_ReplaceText.ReplaceSel(_T("\\0"));
			break;
		case dsEpsilon:
			m_ReplaceText.ReplaceSel(_T("\\0"));
			break;
		case dsCustom:
			m_ReplaceText.ReplaceSel(_T("\\0"));
			break;
	}
	m_RegularExpression.SetCheck(1);
}
void CReplaceDlg::CommandTaggedExpression1(WPARAM, LPARAM)
{
	switch (m_lEmulation)
	{
		case dsDevStudio:
			m_ReplaceText.ReplaceSel(_T("\\1"));
			break;
		case dsVC2:
			m_ReplaceText.ReplaceSel(_T("\\1"));
			break;
		case dsBrief:
			m_ReplaceText.ReplaceSel(_T("\\1"));
			break;
		case dsEpsilon:
			m_ReplaceText.ReplaceSel(_T("\\1"));
			break;
		case dsCustom:
			m_ReplaceText.ReplaceSel(_T("\\1"));
			break;
	}
	m_RegularExpression.SetCheck(1);
}
void CReplaceDlg::CommandTaggedExpression2(WPARAM, LPARAM)
{
	switch (m_lEmulation)
	{
		case dsDevStudio:
			m_ReplaceText.ReplaceSel(_T("\\2"));
			break;
		case dsVC2:
			m_ReplaceText.ReplaceSel(_T("\\2"));
			break;
		case dsBrief:
			m_ReplaceText.ReplaceSel(_T("\\2"));
			break;
		case dsEpsilon:
			m_ReplaceText.ReplaceSel(_T("\\2"));
			break;
		case dsCustom:
			m_ReplaceText.ReplaceSel(_T("\\2"));
			break;
	}
	m_RegularExpression.SetCheck(1);
}
void CReplaceDlg::CommandTaggedExpression3(WPARAM, LPARAM)
{
	switch (m_lEmulation)
	{
		case dsDevStudio:
			m_ReplaceText.ReplaceSel(_T("\\3"));
			break;
		case dsVC2:
			m_ReplaceText.ReplaceSel(_T("\\3"));
			break;
		case dsBrief:
			m_ReplaceText.ReplaceSel(_T("\\3"));
			break;
		case dsEpsilon:
			m_ReplaceText.ReplaceSel(_T("\\3"));
			break;
		case dsCustom:
			m_ReplaceText.ReplaceSel(_T("\\3"));
			break;
	}
	m_RegularExpression.SetCheck(1);
}
void CReplaceDlg::CommandTaggedExpression4(WPARAM, LPARAM)
{
	switch (m_lEmulation)
	{
		case dsDevStudio:
			m_ReplaceText.ReplaceSel(_T("\\4"));
			break;
		case dsVC2:
			m_ReplaceText.ReplaceSel(_T("\\4"));
			break;
		case dsBrief:
			m_ReplaceText.ReplaceSel(_T("\\4"));
			break;
		case dsEpsilon:
			m_ReplaceText.ReplaceSel(_T("\\4"));
			break;
		case dsCustom:
			m_ReplaceText.ReplaceSel(_T("\\4"));
			break;
	}
	m_RegularExpression.SetCheck(1);
}
void CReplaceDlg::CommandTaggedExpression5(WPARAM, LPARAM)
{
	switch (m_lEmulation)
	{
		case dsDevStudio:
			m_ReplaceText.ReplaceSel(_T("\\5"));
			break;
		case dsVC2:
			m_ReplaceText.ReplaceSel(_T("\\5"));
			break;
		case dsBrief:
			m_ReplaceText.ReplaceSel(_T("\\5"));
			break;
		case dsEpsilon:
			m_ReplaceText.ReplaceSel(_T("\\5"));
			break;
		case dsCustom:
			m_ReplaceText.ReplaceSel(_T("\\5"));
			break;
	}
	m_RegularExpression.SetCheck(1);
}
void CReplaceDlg::CommandTaggedExpression6(WPARAM, LPARAM)
{
	switch (m_lEmulation)
	{
		case dsDevStudio:
			m_ReplaceText.ReplaceSel(_T("\\6"));
			break;
		case dsVC2:
			m_ReplaceText.ReplaceSel(_T("\\6"));
			break;
		case dsBrief:
			m_ReplaceText.ReplaceSel(_T("\\6"));
			break;
		case dsEpsilon:
			m_ReplaceText.ReplaceSel(_T("\\6"));
			break;
		case dsCustom:
			m_ReplaceText.ReplaceSel(_T("\\6"));
			break;
	}
	m_RegularExpression.SetCheck(1);
}
void CReplaceDlg::CommandTaggedExpression7(WPARAM, LPARAM)
{
	switch (m_lEmulation)
	{
		case dsDevStudio:
			m_ReplaceText.ReplaceSel(_T("\\7"));
			break;
		case dsVC2:
			m_ReplaceText.ReplaceSel(_T("\\7"));
			break;
		case dsBrief:
			m_ReplaceText.ReplaceSel(_T("\\7"));
			break;
		case dsEpsilon:
			m_ReplaceText.ReplaceSel(_T("\\7"));
			break;
		case dsCustom:
			m_ReplaceText.ReplaceSel(_T("\\7"));
			break;
	}
	m_RegularExpression.SetCheck(1);
}
void CReplaceDlg::CommandTaggedExpression8(WPARAM, LPARAM)
{
	switch (m_lEmulation)
	{
		case dsDevStudio:
			m_ReplaceText.ReplaceSel(_T("\\8"));
			break;
		case dsVC2:
			m_ReplaceText.ReplaceSel(_T("\\8"));
			break;
		case dsBrief:
			m_ReplaceText.ReplaceSel(_T("\\8"));
			break;
		case dsEpsilon:
			m_ReplaceText.ReplaceSel(_T("\\8"));
			break;
		case dsCustom:
			m_ReplaceText.ReplaceSel(_T("\\8"));
			break;
	}
	m_RegularExpression.SetCheck(1);
}
void CReplaceDlg::CommandTaggedExpression9(WPARAM, LPARAM)
{
	switch (m_lEmulation)
	{
		case dsDevStudio:
			m_ReplaceText.ReplaceSel(_T("\\9"));
			break;
		case dsVC2:
			m_ReplaceText.ReplaceSel(_T("\\9"));
			break;
		case dsBrief:
			m_ReplaceText.ReplaceSel(_T("\\9"));
			break;
		case dsEpsilon:
			m_ReplaceText.ReplaceSel(_T("\\9"));
			break;
		case dsCustom:
			m_ReplaceText.ReplaceSel(_T("\\9"));
			break;
	}
	m_RegularExpression.SetCheck(1);
}

/////////////////////////////////////////////////////////////////////////////
// CReplaceDlg message handlers

void CReplaceDlg::OnOK() 
{
	m_FindText.GetWindowText(m_strFindString);
	m_ReplaceText.GetWindowText(m_strReplaceString);

	m_bMatchCase = false;
	m_bRegularExpression = false;
	m_bMatchWholeWord = false;
	
	if (m_MatchWholeWord.GetCheck() == 1)
		m_bMatchWholeWord = true;
	if (m_RegularExpression.GetCheck() == 1)
		m_bRegularExpression = true;
	if (m_MatchCase.GetCheck() == 1)
		m_bMatchCase = true;

	CDialog::OnOK();
}

void CReplaceDlg::OnRegexpfind() 
{
	CMenu ContextMenu;
	ContextMenu.LoadMenu(IDR_REGEXPMENU);
	CMenu* hMenu = ContextMenu.GetSubMenu(0); 
	POINT pt;
	GetCursorPos(&pt);
	hMenu->TrackPopupMenu(TPM_LEFTALIGN | TPM_RIGHTBUTTON, 
			pt.x, pt.y, this, NULL);
}

void CReplaceDlg::OnRegExpReplace() 
{
	CMenu ContextMenu;
	ContextMenu.LoadMenu(IDR_REGEXPMENU);
	CMenu* hMenu = ContextMenu.GetSubMenu(1);
	POINT pt;
	GetCursorPos(&pt);
	hMenu->TrackPopupMenu(TPM_LEFTALIGN | TPM_RIGHTBUTTON, 
			pt.x, pt.y, this, NULL);
}

BOOL CReplaceDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	m_FindText.SetWindowText(m_strFindString);
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}
