; CLW file contains information for the MFC ClassWizard

[General Info]
Version=1
LastClass=CAddIndexDlg
LastTemplate=CDialog
NewFileInclude1=#include "stdafx.h"
NewFileInclude2=#include "daotable.h"
LastPage=0

ClassCount=8
Class1=CAddDatabaseDlg
Class2=CAddIndexDlg
Class3=CAddQueryDlg
Class4=CDlgAddTable
Class5=CDAOTableApp
Class6=CAboutDlg
Class7=CDAOTableDlg
Class8=CFieldListCtrl

ResourceCount=6
Resource1=IDD_ADD_QUERYDEF_DLG
Resource2=IDD_DAOTABLE_DIALOG
Resource3=IDD_ADD_DATABASE_DLG
Resource4=IDD_ADD_TABLE_DLG
Resource5=IDD_ADD_INDEX_DLG
Resource6=IDD_ABOUTBOX

[CLS:CAddDatabaseDlg]
Type=0
BaseClass=CDialog
HeaderFile=AddDbDlg.h
ImplementationFile=AddDbDlg.cpp

[CLS:CAddIndexDlg]
Type=0
BaseClass=CDialog
HeaderFile=AddIxDlg.h
ImplementationFile=AddIxDlg.cpp
LastObject=CAddIndexDlg

[CLS:CAddQueryDlg]
Type=0
BaseClass=CDialog
HeaderFile=AddQyDlg.h
ImplementationFile=AddQyDlg.cpp

[CLS:CDlgAddTable]
Type=0
BaseClass=CDialog
HeaderFile=addtbdlg.h
ImplementationFile=addtbdlg.cpp

[CLS:CDAOTableApp]
Type=0
BaseClass=CWinApp
HeaderFile=DAOTable.h
ImplementationFile=DAOTable.cpp

[CLS:CAboutDlg]
Type=0
BaseClass=CDialog
HeaderFile=DAOTDlg.cpp
ImplementationFile=DAOTDlg.cpp
LastObject=CAboutDlg

[CLS:CDAOTableDlg]
Type=0
BaseClass=CDialog
HeaderFile=DAOTDlg.h
ImplementationFile=DAOTDlg.cpp

[CLS:CFieldListCtrl]
Type=0
BaseClass=CListCtrl
HeaderFile=ListCtrl.h
ImplementationFile=ListCtrl.cpp

[DLG:IDD_ADD_DATABASE_DLG]
Type=1
Class=CAddDatabaseDlg
ControlCount=9
Control1=IDC_EDIT_DATABASE_NAME,edit,1350633600
Control2=IDC_CHECK_ENCRYPT,button,1342242819
Control3=IDC_RADIO_V10,button,1342308361
Control4=IDC_RADIO_V11,button,1342177289
Control5=IDC_RADIO_V20,button,1342177289
Control6=IDC_RADIO_V30,button,1342177289
Control7=IDC_STATIC,static,1342308352
Control8=ID_HELP,button,1342242816
Control9=IDOK,button,1342242817

[DLG:IDD_ADD_INDEX_DLG]
Type=1
Class=CAddIndexDlg
ControlCount=17
Control1=IDC_TABLE_NAME,edit,1350633600
Control2=IDC_INDEX_NAME,edit,1350631552
Control3=IDC_PRIMARY,button,1342242819
Control4=IDC_IGNORE_NULLS,button,1342242819
Control5=IDC_REQUIRED,button,1342242819
Control6=IDC_UNIQUE,button,1342242819
Control7=IDC_PREVIOUS_INDEX,button,1342242816
Control8=IDC_ADD_INDEX,button,1342242816
Control9=IDC_NEXT_INDEX,button,1342242816
Control10=IDC_DELETE_INDEX,button,1342242816
Control11=IDOK,button,1342242817
Control12=IDC_STATIC,button,1342177287
Control13=IDC_STATIC,button,1342177287
Control14=IDC_STATIC,static,1342308352
Control15=IDC_STATIC,static,1342308352
Control16=ID_HELP,button,1342242816
Control17=IDC_FIELD_LIST,SysListView32,1350631441

[DLG:IDD_ADD_QUERYDEF_DLG]
Type=1
Class=CAddQueryDlg
ControlCount=10
Control1=IDC_TABLE_NAME,edit,1350631552
Control2=IDC_SQL,edit,1353781444
Control3=IDC_ADD_QUERY_DEF,button,1342242816
Control4=IDC_MODIFY_QUERY_DEF,button,1342242816
Control5=IDC_DELETE_QUERYDEF,button,1342242816
Control6=IDOK,button,1342242816
Control7=IDC_STATIC,static,1342308352
Control8=IDC_UPDATABLE,button,1476460547
Control9=IDC_STATIC,static,1342308352
Control10=ID_HELP,button,1342242816

[DLG:IDD_ADD_TABLE_DLG]
Type=1
Class=CDlgAddTable
ControlCount=30
Control1=IDC_TABLE_NAME,edit,1350633600
Control2=IDC_POSITION,edit,1350631552
Control3=IDC_SPIN_ORDINAL_POSITION,msctls_updown32,1342177463
Control4=IDC_NAME,edit,1350631552
Control5=IDC_TYPE,combobox,1344340227
Control6=IDC_THE_SIZE,edit,1350631552
Control7=IDC_DEFAULT_VALUE,edit,1350631552
Control8=IDC_REQUIRED,button,1342242819
Control9=IDC_FIXED_FIELD,button,1342308361
Control10=IDC_VARIABLE_FIELD,button,1342177289
Control11=IDC_AUTO_INCR_FIELD,button,1342373891
Control12=IDC_VALIDATION_RULE,edit,1350631552
Control13=IDC_VALIDATION_TEXT,edit,1350631552
Control14=IDC_PREVIOUS_FIELD,button,1342242816
Control15=IDC_ADD_FIELD,button,1342242816
Control16=IDC_NEXT_FIELD,button,1342242816
Control17=IDC_DELETE_FIELD,button,1342242816
Control18=IDOK,button,1342242817
Control19=IDC_STATIC,static,1342308352
Control20=IDC_STATIC,static,1342308352
Control21=IDC_STATIC,static,1342308352
Control22=IDC_STATIC,static,1342308352
Control23=IDC_STATIC,static,1342308352
Control24=IDC_STATIC,static,1342308352
Control25=IDC_STATIC,button,1342177287
Control26=IDC_STATIC,button,1342177287
Control27=IDC_STATIC,button,1342177287
Control28=IDC_STATIC,static,1342308352
Control29=IDC_STATIC,static,1342308352
Control30=ID_HELP,button,1342242816

[DLG:IDD_ABOUTBOX]
Type=1
Class=CAboutDlg
ControlCount=5
Control1=IDC_STATIC,static,1342177283
Control2=IDC_STATIC,static,1342308480
Control3=IDC_STATIC,static,1342308352
Control4=IDOK,button,1342373889
Control5=IDC_STATIC,static,1342308352

[DLG:IDD_DAOTABLE_DIALOG]
Type=1
Class=CDAOTableDlg
ControlCount=13
Control1=IDC_EDIT_DATABASE_NAME,edit,1350631552
Control2=IDC_BUTTON_CONNECT,button,1342242817
Control3=IDC_COMBO_TABLE_NAME,combobox,1478558018
Control4=IDC_BUTTON_TABLE_FIELDS,button,1476460544
Control5=IDC_BUTTON_TABLE_INDEXES,button,1476460544
Control6=IDC_BUTTON_DELETE_TABLE,button,1476460544
Control7=IDC_COMBO_QUERY_NAME,combobox,1478558018
Control8=IDC_BUTTON_QUERY_DEFINITION,button,1476460544
Control9=ID_HELP,button,1342242816
Control10=IDOK,button,1342242816
Control11=IDC_STATIC,button,1342177287
Control12=IDC_STATIC,button,1342177287
Control13=IDC_STATIC,button,1342177287

