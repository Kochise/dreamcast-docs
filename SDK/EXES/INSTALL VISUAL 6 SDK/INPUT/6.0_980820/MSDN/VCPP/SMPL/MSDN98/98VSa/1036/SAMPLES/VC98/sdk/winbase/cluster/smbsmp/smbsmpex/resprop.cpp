/////////////////////////////////////////////////////////////////////////////
//
//	Copyright (c) 1997 <company name>
//
//	Module Name:
//		ResProp.cpp
//
//	Abstract:
//		Implementation of the resource extension property page classes.
//
//	Author:
//		<name> (<e-mail name>) Mmmm DD, 1997
//
//	Revision History:
//
//	Notes:
//
/////////////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "SmbSmpEx.h"
#include "ResProp.h"
#include "ExtObj.h"
#include "DDxDDv.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CSmbSmpParamsPage property page
/////////////////////////////////////////////////////////////////////////////

IMPLEMENT_DYNCREATE(CSmbSmpParamsPage, CBasePropertyPage)

/////////////////////////////////////////////////////////////////////////////
// Message Maps

BEGIN_MESSAGE_MAP(CSmbSmpParamsPage, CBasePropertyPage)
	//{{AFX_MSG_MAP(CSmbSmpParamsPage)
	ON_EN_CHANGE(IDC_PP_SMBSMP_SHARENAME, OnChangeRequiredField)
	ON_EN_CHANGE(IDC_PP_SMBSMP_PATH, OnChangeRequiredField)
	//}}AFX_MSG_MAP
	// TODO: Modify the following lines to represent the data displayed on this page.
	ON_EN_CHANGE(IDC_PP_SMBSMP_SHARENAME, CBasePropertyPage::OnChangeCtrl)
	ON_EN_CHANGE(IDC_PP_SMBSMP_PATH, CBasePropertyPage::OnChangeCtrl)
	ON_EN_CHANGE(IDC_PP_SMBSMP_REMARK, CBasePropertyPage::OnChangeCtrl)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
//++
//
//	CSmbSmpParamsPage::CSmbSmpParamsPage
//
//	Routine Description:
//		Default constructor.
//
//	Arguments:
//		None.
//
//	Return Value:
//		None.
//
//--
/////////////////////////////////////////////////////////////////////////////
CSmbSmpParamsPage::CSmbSmpParamsPage(void) : CBasePropertyPage(CSmbSmpParamsPage::IDD)
{
	// TODO: Modify the following lines to represent the data displayed on this page.
	//{{AFX_DATA_INIT(CSmbSmpParamsPage)
	m_strShareName = _T("");
	m_strPath = _T("");
	m_strRemark = _T("");
	//}}AFX_DATA_INIT

	// Setup the property array.
	{
		m_rgProps[epropShareName].Set(REGPARAM_SMBSMP_SHARENAME, m_strShareName, m_strPrevShareName);
		m_rgProps[epropPath].Set(REGPARAM_SMBSMP_PATH, m_strPath, m_strPrevPath);
		m_rgProps[epropRemark].Set(REGPARAM_SMBSMP_REMARK, m_strRemark, m_strPrevRemark);
	}  // Setup the property array

	m_iddPropertyPage = IDD_PP_SMBSMP_PARAMETERS;
	m_iddWizardPage = IDD_WIZ_SMBSMP_PARAMETERS;

}  //*** CSmbSmpParamsPage::CSmbSmpParamsPage()

/////////////////////////////////////////////////////////////////////////////
//++
//
//	CSmbSmpParamsPage::DoDataExchange
//
//	Routine Description:
//		Do data exchange between the dialog and the class.
//
//	Arguments:
//		pDX		[IN OUT] Data exchange object 
//
//	Return Value:
//		None.
//
//--
/////////////////////////////////////////////////////////////////////////////
void CSmbSmpParamsPage::DoDataExchange(CDataExchange * pDX)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());

	// TODO: Modify the following lines to represent the data displayed on this page.
	//{{AFX_DATA_MAP(CSmbSmpParamsPage)
	DDX_Control(pDX, IDC_PP_SMBSMP_SHARENAME, m_editShareName);
	DDX_Control(pDX, IDC_PP_SMBSMP_PATH, m_editPath);
	DDX_Text(pDX, IDC_PP_SMBSMP_SHARENAME, m_strShareName);
	DDX_Text(pDX, IDC_PP_SMBSMP_PATH, m_strPath);
	DDX_Text(pDX, IDC_PP_SMBSMP_REMARK, m_strRemark);
	//}}AFX_DATA_MAP

	// Handle numeric parameters.
	// TODO: Change the last argument to TRUE if any of these are signed values.
	if (!BBackPressed())
	{
	}  // if:  back button not pressed

	// TODO: Add any additional field validation here.
	if (pDX->m_bSaveAndValidate)
	{
		// Make sure all required fields are present.
		if (!BBackPressed())
		{
			DDV_RequiredText(pDX, IDC_PP_SMBSMP_SHARENAME, IDC_PP_SMBSMP_SHARENAME_LABEL, m_strShareName);
			DDV_RequiredText(pDX, IDC_PP_SMBSMP_PATH, IDC_PP_SMBSMP_PATH_LABEL, m_strPath);
		}  // if:  back button not pressed
	}  // if:  saving data from dialog

	CBasePropertyPage::DoDataExchange(pDX);

}  //*** CSmbSmpParamsPage::DoDataExchange()

/////////////////////////////////////////////////////////////////////////////
//++
//
//	CSmbSmpParamsPage::OnInitDialog
//
//	Routine Description:
//		Handler for the WM_INITDIALOG message.
//
//	Arguments:
//		None.
//
//	Return Value:
//		TRUE		We need the focus to be set for us.
//		FALSE		We already set the focus to the proper control.
//
//--
/////////////////////////////////////////////////////////////////////////////
BOOL CSmbSmpParamsPage::OnInitDialog(void)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());

	CBasePropertyPage::OnInitDialog();

	// TODO:
	// Limit the size of the text that can be entered in edit controls.

	return TRUE;	// return TRUE unless you set the focus to a control
					// EXCEPTION: OCX Property Pages should return FALSE

}  //*** CSmbSmpParamsPage::OnInitDialog()

/////////////////////////////////////////////////////////////////////////////
//++
//
//	CSmbSmpParamsPage::OnSetActive
//
//	Routine Description:
//		Handler for the PSN_SETACTIVE message.
//
//	Arguments:
//		None.
//
//	Return Value:
//		TRUE	Page successfully initialized.
//		FALSE	Page not initialized.
//
//--
/////////////////////////////////////////////////////////////////////////////
BOOL CSmbSmpParamsPage::OnSetActive(void)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());

	// Enable/disable the Next/Finish button.
	if (BWizard())
		EnableNext(BAllRequiredFieldsPresent());

	return CBasePropertyPage::OnSetActive();

}  //*** CSmbSmpParamsPage::OnSetActive()

/////////////////////////////////////////////////////////////////////////////
//++
//
//	CSmbSmpParamsPage::OnChangeRequiredField
//
//	Routine Description:
//		Handler for the EN_CHANGE message on the Share name or Path edit
//		controls.
//
//	Arguments:
//		None.
//
//	Return Value:
//		None.
//
//--
/////////////////////////////////////////////////////////////////////////////
void CSmbSmpParamsPage::OnChangeRequiredField(void)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());

	OnChangeCtrl();

	if (BWizard())
		EnableNext(BAllRequiredFieldsPresent());

}  //*** CSmbSmpParamsPage::OnChangeRequiredField()

/////////////////////////////////////////////////////////////////////////////
//++
//
//	CSmbSmpParamsPage::BAllRequiredFieldsPresent
//
//	Routine Description:
//		Handler for the EN_CHANGE message on the Share name or Path edit
//		controls.
//
//	Arguments:
//		None.
//
//	Return Value:
//		None.
//
//--
/////////////////////////////////////////////////////////////////////////////
BOOL CSmbSmpParamsPage::BAllRequiredFieldsPresent(void) const
{
	BOOL	bPresent;

	if (0
		|| (m_editShareName.GetWindowTextLength() == 0)
		|| (m_editPath.GetWindowTextLength() == 0)
		)
		bPresent = FALSE;
	else
		bPresent = TRUE;

	return bPresent;

}  //*** CSmbSmpParamsPage::BAllRequiredFieldsPresent()
