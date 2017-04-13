//-----------------------------------------------------------------------------
// Microsoft OLE DB QURYDEMO Sample
// Copyright (C) 1995-1998 Microsoft Corporation
//
// @doc
//
// @module QUERY.CPP
//
//-----------------------------------------------------------------------------------
/*
	PROGRAM: QURYDEMO
	========

	PURPOSE:
	========	
	demonstrates a simple MDI (Multiple Document Interface)application
	that allows a user to simultaneously connect to multiple
	hetrogeneous databases and perform SQL queries to get results.

	FUNCTIONS:
	==========
	InitEnvironment() - Initialize OLE
	DisplayProviders() - Display available Providers
	ConnectDatabase() - Connect to a specific data source
	DisplayConnections() - Display List of made connections
	DisplayICommands() - Display list of ICommands
	NewICommandWindow() - Open a new ICommand and update displays
	ChangeCurrentCursor() - Change current cursor display
	ChangeCurrentICommand() - Change current ICommand display
	DisplayNewCrsrAndICommand() - update cusor & ICommand displays
	FreeConnect() - free a IDBCreateCommand
	FreeICommand() - free a ICommand
	CloseICommandWindow() - close a ICommand window
	ExecuteQuery() - execute a user specified query
	CloseIDBCreateCommand() - check if all connections are closed
	FreeEnvironment() - free OLE
	ExecuteCommand() - Execute the ICommand and return an IRowset 
	GetDataFromRowset() - Get the Data from the IRowset
	SetupBindings() - Set the binding structure
	CreateAccessor() - Create Accessor to store the Data
	GetData() - Get the Data out of the rowset
	 

	COMMENTS:
	=========
	Created by Microsoft Corporation.
	
	The application uses MDI Child Window Titles to store values of
	PROVIDER's and Command Objects. These values are also stored in the
	comboboxes that are displayed on the toolbar.

*/
#define STRICT
#define DBINITCONSTANTS
#define INITGUID

#include <stdio.h>
#include <string.h>
#include <windows.h>
#include <stddef.h>				// offsetof
#include <assert.h>				// assert

#include "oledb.h"
#include "oledberr.h"
#include "msdaguid.h"

#include "qurydemo.h"  

// Globals
extern HWND			hWndFrame;			 	// Main Frame Window handle
extern HWND			hWndCrsrList;			// hdbc(s) combobox on the tool bar
extern HWND			hWndStmtList;			// hstmt(s) combobox on the tool bar
extern HWND			hWndMDIClient;			// MDI Client window handle
extern HWND			hWndActiveChild;		// Current active MDI Child window
extern HINSTANCE	hAppInstance;			// Application instance

IMalloc* 			g_pIMalloc = NULL;

int					nChildCount;					// Number of child windows currently open
char				szDispBuffer[MAXDISPLAYSIZE+10];// Display Buffer
unsigned char		rgbData[MAX_COL][MAXDATALEN];	// Results Data Array
long 				dwDataLen[MAX_COL];				// Results Data Length Array

//char				szErrorDescription [MAXDISPLAYSIZE+1];
//char				szErrorSource      [MAXDISPLAYSIZE+1];

//Variables and constants used for provider enumeration
//#define   MAX_VALUE_NAME          300
//#define   MAX_PROVIDER_NUM        10
#define NUMELEM(p1) (sizeof(p1) / sizeof(p1[0]))
#define COLUMN_ALIGNVAL 8
#define ROUND_UP( Size, Amount ) (((DWORD)(Size) +  ((Amount) - 1)) & ~((Amount) - 1))

const ULONG	DEF_SOURCES_CBMAXLEN	= 64;
const ULONG MAX_NUM_PROVIDERS		= 16;

IParseDisplayName*	g_pIParse = NULL;
ULONG	g_cProvNames;
CHAR	g_rgszProvName[MAX_NUM_PROVIDERS][DEF_SOURCES_CBMAXLEN];
WCHAR	g_rgwszParseName[MAX_NUM_PROVIDERS][DEF_SOURCES_CBMAXLEN];

/*
	FUNCTION: InitEnvironment()
	COMMENTS: Allocate an environment handle for OLE function calls.
*/
FAR PASCAL InitEnvironment()
{
	HRESULT		hr;

	// Initialize OLE
	hr = CoInitialize( NULL );

	if (FAILED(hr))
	{
		DumpErrorHResult( hr, (LPSTR)"CoInitialize FAILED!!" );
		return FALSE;
	}

    // Retrieve the task memory allocator
    hr = CoGetMalloc( MEMCTX_TASK, &g_pIMalloc );

	if (FAILED(hr))
	{
		DumpErrorHResult( hr, (LPSTR)"CoGetMalloc FAILED!!" );
		return FALSE;
	}

	// reset child window count
	nChildCount = 0;
	
	// Return TRUE
	return TRUE;
}

/*
	FUNCTION: DisplayProviders(HWND hWnd)
	COMMENTS: Display a list of available Providers.
*/
void FAR PASCAL DisplayProviders(HWND hWnd)
{
    ULONG		iProv;
	HRESULT		hr;

	// Initialize count of provider names
	g_cProvNames = 0;

	//Go to registry and get me the provider names
	hr = EnumerateProviders();  
	if (FAILED (hr))
	{
	  MessageBox(hWndFrame, 
	             "There was an error retrieve providers from the OLE DB Enumerator", 
	             "Enumeration Error", 
				 MB_OK | MB_ICONERROR);
	  return;
	}

	//All returned Providerss in the provided combo box for display.
	SendMessage(hWnd, CB_RESETCONTENT, 0, 0);
	for (iProv=0; iProv<g_cProvNames; iProv++)
	   SendMessage(hWnd, CB_ADDSTRING, 0, (LPARAM)(LPSTR)g_rgszProvName[iProv]);

	SendMessage(hWnd, CB_SETCURSEL, 0, 0);
}

/*
	FUNCTION: EnumerateProviders
	COMMENTS: Display a list of available providers
*/
HRESULT EnumerateProviders
	(
	)
{
	HRESULT				hr;
	ULONG				ul, cRows = 0;
	ISourcesRowset*		pISrcRowset = NULL;
	IRowset*			pIRowset = NULL;
	IAccessor*			pIAccessor = NULL;
	BYTE*				pData = NULL;
	DWORD				dwOffset;
	HACCESSOR			hAccessor = NULL;
	DBBINDING			rgBind[3];
	HROW				rghRows[MAX_NUM_PROVIDERS];
	HROW*				pRows = &rghRows[0];

	enum enumSOURCES_COLUMNS {
		eid_SOURCES_NAME = 1,
		eid_SOURCES_PARSENAME,
		eid_SOURCES_DESCRIPTION,
		eid_SOURCES_TYPE,
		eid_SOURCES_ISPARENT,
		eid_SOURCES_CLSID,
		};

	static struct tagSOURCES
	{
		ULONG	iOrdinal;
		DBTYPE	wType;
		ULONG	cbMaxLen;	
	} s_rgSources[] = {
		eid_SOURCES_NAME,		DBTYPE_STR,		DEF_SOURCES_CBMAXLEN,
		eid_SOURCES_PARSENAME,	DBTYPE_WSTR,	DEF_SOURCES_CBMAXLEN * sizeof(WCHAR),
		eid_SOURCES_TYPE,		DBTYPE_UI4,		sizeof(ULONG),
	};
	
	memset(rghRows, 0, sizeof(rghRows));

	// Initialize the OLE DB Enumerator
	if( FAILED(hr = CoCreateInstance(CLSID_OLEDB_ENUMERATOR, NULL, 
		CLSCTX_INPROC_SERVER, IID_ISourcesRowset, (LPVOID*)&pISrcRowset)) )
	{
		DumpErrorHResult( hr, (LPSTR)"CoCreateInstance FAILED!!" );
		goto EXIT;
	}

	// Retrieve the Rowset
	if( FAILED(hr = pISrcRowset->GetSourcesRowset(NULL, IID_IRowset, 0, NULL, 
		(IUnknown**)&pIRowset)) )
	{
		DumpErrorHResult( hr, (LPSTR)"GetSourcesRowset FAILED!!" );
		goto EXIT;
	}

	memset(rgBind, 0, sizeof(rgBind));

	if( FAILED(hr = pIRowset->QueryInterface(IID_IAccessor, (LPVOID*)&pIAccessor)) )
	{
		DumpErrorHResult( hr, (LPSTR)"QI of IID_IAccessor from pIRowset failed" );
		goto EXIT;
	}

	dwOffset = 0;
	for(ul=0; ul< NUMELEM(s_rgSources); ul++)
	{
		rgBind[ul].dwPart		= DBPART_VALUE | DBPART_LENGTH | DBPART_STATUS;
		rgBind[ul].eParamIO		= DBPARAMIO_NOTPARAM;
		rgBind[ul].iOrdinal		= s_rgSources[ul].iOrdinal;
		rgBind[ul].wType		= s_rgSources[ul].wType;
		rgBind[ul].obValue		= dwOffset + offsetof(COLUMNDATA,bData);
		rgBind[ul].obLength		= dwOffset + offsetof(COLUMNDATA,dwLength);
		rgBind[ul].obStatus		= dwOffset + offsetof(COLUMNDATA,wStatus);
		rgBind[ul].cbMaxLen		= s_rgSources[ul].cbMaxLen;
		rgBind[ul].dwMemOwner	= DBMEMOWNER_CLIENTOWNED;
		dwOffset += rgBind[ul].cbMaxLen + offsetof( COLUMNDATA, bData );
		dwOffset = ROUND_UP( dwOffset, COLUMN_ALIGNVAL );
	}

	if( FAILED(hr = pIAccessor->CreateAccessor(DBACCESSOR_ROWDATA, NUMELEM(s_rgSources), 
		rgBind, dwOffset, &hAccessor, NULL)) )
	{
		DumpErrorHResult( hr, (LPSTR)"Accessor Creation failed!!" );
		goto EXIT;
	}

	// Retrieve the providers
	if( SUCCEEDED(hr = pIRowset->GetNextRows(NULL, 0, MAX_NUM_PROVIDERS, &cRows, &pRows)) )
	{
		// Allocate block of memory to retrieve the row data into.
		pData = new BYTE[dwOffset];
		if( pData == NULL )
		{
			DumpErrorHResult( E_OUTOFMEMORY, (LPSTR)"Unable to allocate memory for buffer");
			goto EXIT;
		}

		// Loop over the rows of data, collecting providers and discarding 
		// enumerators..
		for(ul=0; (ul<cRows) && (ul<MAX_NUM_PROVIDERS); ul++)
		{
			memset(pData, 0, dwOffset);

			if( SUCCEEDED(hr = pIRowset->GetData(rghRows[ul], hAccessor, pData)) )
			{
				if( *((ULONG*)(pData + rgBind[2].obValue)) == DBSOURCETYPE_DATASOURCE )
				{
					// Store Provider Name
					strcpy(g_rgszProvName[g_cProvNames], (CHAR*)(pData + rgBind[0].obValue));
					
					// Store Parse Name
					wcscpy(g_rgwszParseName[g_cProvNames], (WCHAR*)(pData + rgBind[1].obValue));
					
					g_cProvNames++;
				}
			}
		}
	}
	else
	{
		DumpErrorHResult( hr, (LPSTR)"GetNextRows failed to retrieve Providers" );
		goto EXIT;
	}

	// Retrieve the IID_IParseDisplayName interface before returning
	if( FAILED(hr = pISrcRowset->QueryInterface(IID_IParseDisplayName, (LPVOID*)&g_pIParse)) )
	{
		DumpErrorHResult( hr, (LPSTR)"QI for IParseDisplayName failed");
		goto EXIT;
	}

EXIT:
	if( pData )
		delete[] pData;

	if( pIAccessor )
	{
		if( hAccessor )
		{
			if( FAILED(hr = pIAccessor->ReleaseAccessor(hAccessor, NULL)) )
				DumpErrorHResult( hr, (LPSTR)"Release Accessor failed!!" );
		}
		pIAccessor->Release();
	}

	if( pIRowset )
	{
		if( cRows )
		{
			if( FAILED(hr = pIRowset->ReleaseRows(cRows, rghRows, NULL, NULL, NULL)) )
				DumpErrorHResult( hr, (LPSTR)"Release of Row handles failed");
		}
		pIRowset->Release();
	}

	if( pISrcRowset )
		pISrcRowset->Release();
	return hr;
}


//**********************************************************************
// 
// ConnectDatabase
// 
// Purpose:
// 
//     Initializes the PROVIDER and creates a IDBCreateCommand Object.
//     
// Parameters:
//
// 	HWND 			hWnd                - handle to the window
// 
// Return Value:
//     TRUE         - Success
//     FALSE        - Failure
// 
// Function Calls:
//     Function                    Location
// 
//     IDBInitialize::Release      provider's Command object
// 
//     
// Comments:      
// 
// 
//**********************************************************************
BOOL FAR PASCAL ConnectDatabase(HWND hWnd)
{
	// Global IDBInitialize Options
	IMoniker*			pIMoniker			= NULL;	// Moniker
	IDBInitialize * 	pIDBInit			= NULL;	// IDBInitialize Object
	IDBCreateCommand *	pIDBCreateCommand	= NULL;	// IDBCreateCommand
	IDBCreateSession *	pIDBCreateSession	= NULL; // IDBCreateSession
	IDBProperties*		pIDBProperties		= NULL; // IDBProperties
	IOpenRowset *		pIOpenRowset		= NULL;	// IOpenRowset
	IUnknown *			pIUnknown			= NULL;	// IUnknown
	HRESULT				hr;							// HRESULT
	DBPROPSET			rgPropertySet[1];			// Array of property sets
	DBPROP				rgProperties[5];			// Array of property values
	BOOL				bReturn = FALSE;			// Return Value
	short				iPrompt = 0;				// DBPROP_INIT_PROMPT value.
	ULONG				iProp, iPDex;
	ULONG				chEaten;

	// Strings for MSDASQL (CHAR & WCHAR)
	CHAR				szProvName[MAXBUFLEN+1];	// Provider String
	CHAR				szDBName[MAXBUFLEN+1];		// DSN String
	WCHAR				wszBuff[MAXBUFLEN+1];		// WCHAR buffer
	CHAR				szUserName[MAXBUFLEN+1];	// User Name
	CHAR				szPassword[MAXBUFLEN+1];	// Password
	CHAR				szBuffer[MAXBUFLEN+1];		// String Buffer
	LRESULT 			nResult;					// Return Code
	BOOL				fCommandWindow=FALSE;		// Flag to indicate Command support

	// Initialize Property Buffers
	for(iProp=0; iProp<NUMELEM(rgProperties); iProp++)
		VariantInit(&(rgProperties[iProp].vValue));

	// check if enough windows are already open, refuse connection
	if (nChildCount >= MAXCHILDWNDS)
	{
		MessageBox(hWndFrame, MAXCHILDEXCEEDED, MAXCHLDERR, MB_OK | MB_ICONHAND);
		return (FALSE);
	}

	// Retrieve Provider values from the connect dialog box
	GetDlgItemText(hWnd, IDCOMBO_PROVIDER, szProvName, MAXBUFLEN);
	GetDlgItemText(hWnd, IDCOMBO_NAME, 	   szDBName,   MAXBUFLEN);
	GetDlgItemText(hWnd, IDTEXT_USERID,    szUserName, MAXBUFLEN);
	GetDlgItemText(hWnd, IDTEXT_PASSWORD,  szPassword, MAXBUFLEN);
	if ((iPrompt = (short) SendMessage(GetDlgItem(hWnd, IDCOMBO_PROMPT), CB_GETCURSEL, 0, 0)) == CB_ERR)
		iPrompt = 0;

    //Determine the ParseDisplayName
	for(iPDex=0; iPDex<g_cProvNames; iPDex++)
    {
		if( strcmp((const char *)szProvName, (const char *) g_rgszProvName[iPDex])==0 )
			break;
	}

	if( iPDex >= g_cProvNames )
	{
		DumpErrorHResult( E_FAIL, (LPSTR)"Unknown Provider, Please Select Valid Provider" );
		goto error;
	}
		
	if( FAILED(hr = g_pIParse->ParseDisplayName(NULL, g_rgwszParseName[iPDex], &chEaten, &pIMoniker)) ) 
	{
		DumpErrorHResult( hr, (LPSTR)"ParseDisplayName failed");
		goto error;
	}

	if( FAILED(hr = BindMoniker(pIMoniker, 0, IID_IDBInitialize, (LPVOID*)&pIDBInit)) )
	{
		DumpErrorHResult( hr, (LPSTR)"BindMoniker failed");
		goto error;
	}

	iProp = 0;
	// If DataSource name specified, then create property node
	if( *szDBName != '\0' )
	{
		// Fill in Data Source
		rgProperties[iProp].dwPropertyID		=	DBPROP_INIT_DATASOURCE;
		rgProperties[iProp].dwOptions			=	DBPROPOPTIONS_REQUIRED;
		rgProperties[iProp].colid				=	DB_NULLID;
		MultiByteToWideChar(CP_ACP, 0, szDBName, -1, wszBuff, MAXBUFLEN+1);
		V_VT(&(rgProperties[iProp].vValue))		=	VT_BSTR;
		V_BSTR(&(rgProperties[iProp].vValue))	=	SysAllocString(wszBuff);
		iProp++;
	}

	// If User Name specified, then create property node
	if( *szUserName != '\0' )
	{
		rgProperties[iProp].dwPropertyID	=	DBPROP_AUTH_USERID;
		rgProperties[iProp].dwOptions			=	DBPROPOPTIONS_REQUIRED;
		rgProperties[iProp].colid				=	DB_NULLID;
		MultiByteToWideChar(CP_ACP, 0, szUserName, -1, wszBuff, MAXBUFLEN+1);
		V_VT(&(rgProperties[iProp].vValue))		=	VT_BSTR;
		V_BSTR(&(rgProperties[iProp].vValue))	=	SysAllocString(wszBuff);
		iProp++;
	}

	// If Password specified, then create property node
	if( *szPassword != '\0' )
	{
		rgProperties[iProp].dwPropertyID	=	DBPROP_AUTH_PASSWORD;
		rgProperties[iProp].dwOptions			=	DBPROPOPTIONS_REQUIRED;
		rgProperties[iProp].colid				=	DB_NULLID;
		MultiByteToWideChar(CP_ACP, 0, szPassword, -1, wszBuff, MAXBUFLEN+1);
		V_VT(&(rgProperties[iProp].vValue))		=	VT_BSTR;
		V_BSTR(&(rgProperties[iProp].vValue))	=	SysAllocString(wszBuff);
		iProp++;
	}

	// Set prompt level if one was given.
	if (iPrompt)
	{
		rgProperties[iProp].dwPropertyID	=	DBPROP_INIT_PROMPT;
		rgProperties[iProp].dwOptions			=	DBPROPOPTIONS_REQUIRED;
		rgProperties[iProp].colid				=	DB_NULLID;
		rgProperties[iProp].vValue.vt			= VT_I2;
		rgProperties[iProp].vValue.iVal			= iPrompt;
		iProp++;

		rgProperties[iProp].dwPropertyID	=	DBPROP_INIT_HWND;
		rgProperties[iProp].dwOptions			=	DBPROPOPTIONS_REQUIRED;
		rgProperties[iProp].colid				=	DB_NULLID;
		rgProperties[iProp].vValue.vt			= VT_I4;
		rgProperties[iProp].vValue.lVal			= (long) hWnd;
		iProp++;
	}

	if( iProp )
	{
		// Identify Property Set
		rgPropertySet[0].rgProperties		=	rgProperties;
		rgPropertySet[0].cProperties		=	iProp;
		rgPropertySet[0].guidPropertySet	=	DBPROPSET_DBINIT;

		// from the DataSource Object get the Session Object
		hr = pIDBInit->QueryInterface( 
							IID_IDBProperties, 
							(void**)&pIDBProperties );
		if (FAILED(hr))
		{
			GetDetailedErrorInfo(hr, pIDBInit, IID_IDBInitialize, "QI for IDBProperties FAILED!!");
			goto error;
		}

		// Set Connection Properties
		hr = pIDBProperties->SetProperties(1, rgPropertySet);
		if (FAILED(hr))
		{
			GetDetailedErrorInfo(hr, pIDBProperties, IID_IDBProperties, "IDBProperties->SetProperties FAILED!!");
			goto error;
		}
	} 

 	// Initialize the PROVIDER
	if( FAILED(hr = pIDBInit->Initialize()) )
	{
        GetDetailedErrorInfo(hr, pIDBInit, IID_IDBInitialize, "IDBInit->Initialize FAILED!!");
		goto error;
	}

	// from the DataSource Object get the Session Object
	if( FAILED(hr = pIDBInit->QueryInterface( 
						IID_IDBCreateSession, 
						(void**)&pIDBCreateSession)) )
	{
		GetDetailedErrorInfo(hr, pIDBInit, IID_IDBInitialize, "QI for IDBCreateSession FAILED!!");
		goto error;
	}

	// from the Session object, attempt to get an IUnknown
	if( FAILED(hr = pIDBCreateSession->CreateSession(NULL, IID_IUnknown, (IUnknown**)&pIUnknown)) )
	{
		GetDetailedErrorInfo(hr, pIDBCreateSession, IID_IDBCreateSession, "IDBCreateSession->CreateSession FAILED!!");
		goto error;
	}

	// from the Session object, attempt to get the IDBCreateCommand interface
	if( FAILED(hr = pIUnknown->QueryInterface(
						IID_IDBCreateCommand, 
						(void**)&pIDBCreateCommand)) )
	{
		// if no Command object support, attempt to get the IOpenRowset interface
		hr = pIUnknown->QueryInterface(
							IID_IOpenRowset, 
							(void**)&pIOpenRowset);
		if (FAILED(hr))
		{
	        GetDetailedErrorInfo(hr, pIUnknown, IID_IUnknown, "QI for IOpenRowset FAILED!!");
			goto error;
		}
	}
	else
	{
		fCommandWindow = TRUE;
	}

	// update the combo-box with IUnknown from Session object
	wsprintf( szBuffer, PROVIDER_SESSION_FORMAT, (LPSTR)szProvName, pIUnknown );

	nResult = (UINT)SendMessage(hWndCrsrList, CB_ADDSTRING, 0, (LPARAM)(LPSTR)szBuffer);
	SendMessage(hWndCrsrList, CB_SETCURSEL, (WPARAM)nResult, 0);
	SendMessage(hWndCrsrList, CB_SELECTSTRING, 0, (LPARAM)(LPSTR)szBuffer);
	ChangeCurrentCursor(hWndCrsrList);
	
	if (fCommandWindow)
	{
		// Create a Command Object and its associated window.
		NewICommandWindow();
	}
	else
	{
		NewIOpenRowsetWindow();
	}

	bReturn = TRUE;

error:
	if( pIMoniker )
		pIMoniker->Release();

	// Initialize Property Buffers
	for(iProp=0; iProp<NUMELEM(rgProperties); iProp++)
		VariantClear(&(rgProperties[iProp].vValue));

	// If we are successully connected, and the IParse pointer
	// exists release it.
	if( bReturn && g_pIParse )
	{
		g_pIParse->Release();
		g_pIParse = NULL;
	}

	// Release IUnknown (for Session) on error only.
	// The pointer value has been copied to the window.
	if( (!bReturn) && (pIUnknown) )
		pIUnknown->Release();

	if( (pIDBCreateCommand) )
		pIDBCreateCommand->Release();

	if( (pIDBProperties) )
		pIDBProperties->Release();

	if( (pIOpenRowset) )
		pIOpenRowset->Release();

	if( pIDBCreateSession )
		pIDBCreateSession->Release();

	if(pIDBInit)
		pIDBInit->Release();

	return (bReturn);

} 

//**********************************************************************
// 
// DisplayConnections
// 
// Purpose:
// 
//     Display list of available hdbc(s) in the given list box.
//     
// Parameters:
//
// 	HWND 			hWndhdbc               - handle to the window
// 
// Return Value:
// 
// Function Calls:
//     Function                    Location
// 
// 
//     
// Comments:      
// 
// 
//**********************************************************************
void FAR PASCAL DisplayConnections(HWND hWndhdbc)
{
	ULONG 	nConnects;				// # of Connections
	ULONG 	count;					// Count
	char	szBuffer[MAXBUFLEN+1];	// String Buffer

	// Read the information from the  combo-box 
	// on the tool bar and feed it in the given list box.
	SendMessage(hWndhdbc, LB_RESETCONTENT, 0, 0);
	nConnects = SendMessage(hWndCrsrList, CB_GETCOUNT, 0, 0);

	for (count = 0; count < nConnects; count++)
	{
		SendMessage(hWndCrsrList, CB_GETLBTEXT, count, (LPARAM)(LPSTR)szBuffer);
		SendMessage(hWndhdbc, LB_ADDSTRING, 0, (LPARAM)(LPSTR)szBuffer);
	}

	SendMessage(hWndhdbc, LB_SETCURSEL, 0, 0);
}

//**********************************************************************
// 
// DisplayICommands
// 
// Purpose:
// 
//     Initializes the PROVIDER and creates a ICommand Object.
//     Display list of ICommand Objects for the currently selected PROVIDER.
//     
// Parameters:
//
//  HWND 			hWndhdbc				 - handle to the PROVIDER
// 	HWND 			hWndhstmt                - handle to the ICommand
//	int 			nCrsrIndex				 - Count
// 
// Return Value:
// 
// Function Calls:
//     Function                    Location
// 
// 
//     
// Comments:      
// 
// 
//**********************************************************************
void FAR PASCAL DisplayICommands(HWND hWndhstmt, HWND hWndhdbc, int nCrsrIndex)
{
	char				szBuffer[MAXBUFLEN+1];	// MDI child window title
	HWND				hWndChild;				// MDI child window handle
	IDBCreateCommand * 	pIDBCreate1;			// IDBCreateCommand Object #1
	IDBCreateCommand * 	pIDBCreate2;			// IDBCreateCommand Object #2
	ICommand *			pICommand;				// ICommand Object

	// Reset the Command list box in the disconnect dialog box
	SendMessage(hWndhstmt, LB_RESETCONTENT, 0, 0);

	// Go through all available MDI child windows and check if the
	// PROVIDER in the title matches the one selected in the list box.
	// If they match, use the Command in the window title to create
	// a new entry in the Command list box.
	for (hWndChild=GetWindow(hWndMDIClient, GW_CHILD); hWndChild; hWndChild=GetWindow(hWndChild, GW_HWNDNEXT))
	{
		// Class name check is necessary as some of MDI child
		// windows may be iconized by the user and MDIClient
		// in such cases create additional windows (such as icon titles).
		GetClassName(hWndChild, szBuffer, MAXBUFLEN);
		
		if (strcmp(szBuffer, OLEDBMDICLASS))
			continue;

		GetWindowText(hWndChild, szBuffer, MAXBUFLEN);
		sscanf(szBuffer, SCANSESSIONCOMMAND_FORMAT, &pIDBCreate1, &pICommand);

		SendMessage(hWndhdbc, LB_GETTEXT, (WPARAM)nCrsrIndex, (LPARAM)(LPSTR)szBuffer);
		sscanf(szBuffer, SCANSESSION_FORMAT, &pIDBCreate2);

		if (pIDBCreate1 != pIDBCreate2)
			continue;

		wsprintf(szBuffer, ((hWndChild == hWndActiveChild) ?  CURQUERY_STRING:	QUERY_STRING), pICommand);
		SendMessage(hWndhstmt, LB_ADDSTRING, 0, (LPARAM)(LPSTR)szBuffer);
	}
	SendMessage(hWndhstmt, LB_SETSEL, TRUE, 0);
}

//**********************************************************************
// 
// NewICommandWindow
// 
// Purpose:
// 
//     Create a new ICommand Object on the current IDBCreateCommand.
//     
// Parameters:
// 
// Return Value:
// 
// Function Calls:
//     Function                         Location
// 
//	   IDBCreateCommand::CreateCommand	provider's Command object
//     ICommand::Release                provider's Command object
// 	   
//     
// Comments:      
// 
// 
//**********************************************************************
void FAR PASCAL NewICommandWindow()
{
	int 				nCurrenthdbc;				// Current PROVIDER
	char				szBuffer[MAXBUFLEN+1];		// String in PROVIDER ComboBox on Toolbar
	char				szProvName[MAXBUFLEN+1];	// DSN String
	MDICREATESTRUCT		mcs;						// MDI Child Window Create Struc
	
	IDBCreateCommand * 	pIDBCreateCommand	= NULL;	// IDBCreateCommand Object
	IOpenRowset *	 	pIOpenRowset		= NULL;	// IOpenRowset Object
	ICommand *			pICommand			= NULL;	// ICommand Object
	ICommand *			pIUnknown			= NULL;	// IUnknown for session Object
	HRESULT				hr;							// HRESULT
	BOOL				bReturn				= FALSE;// Return Value

        
	// check if there is PROVIDER selected in the Combo-Box
	if ((nCurrenthdbc = (int)SendMessage(hWndCrsrList, CB_GETCURSEL, 0, 0)) == CB_ERR)
	{
		MessageBox(hWndFrame, MAKECONNECT, NOSESSIONERROR, MB_OK | MB_ICONHAND);
		return;
	}
	
	// check if the number of windows exceeds MAXCHILDWNDS
	if (nChildCount >= MAXCHILDWNDS)
	{
		MessageBox(hWndFrame, MAXCHILDEXCEEDED, MAXCHLDERR, MB_OK | MB_ICONHAND);
		return;
	}

	// Scan PROVIDER string and IDBCreateCommand value from the combo-box
	SendMessage(hWndCrsrList, CB_GETLBTEXT, (WPARAM)nCurrenthdbc, (LPARAM)(LPSTR)szBuffer);
	
	sscanf(szBuffer, SCANPROVIDERSESSION_FORMAT, szProvName, &pIUnknown);
		
	// from the Session object, attempt to get the IDBCreateCommand interface
	hr = pIUnknown->QueryInterface(
						IID_IDBCreateCommand, 
						(void**)&pIDBCreateCommand);
	if (FAILED(hr))
	{
		// if no Command object support, attempt to get the IOpenRowset interface
		hr = pIUnknown->QueryInterface(
							IID_IOpenRowset, 
							(void**)&pIOpenRowset);
		if (FAILED(hr))
		{
		    GetDetailedErrorInfo(hr, pIUnknown, IID_IUnknown, "QI for IOpenRowset FAILED!!");
			goto error;
		}
	}
	else
	{
		// Create a command object 
		hr = pIDBCreateCommand->CreateCommand(NULL, IID_ICommand, (IUnknown**)&pICommand);

		if (FAILED(hr))
		{
    	   GetDetailedErrorInfo(hr, pIDBCreateCommand, IID_IDBCreateCommand, "pIDBCreateCommand->CreateCommand FAILED!!");
		   goto error;
		}
	}

		
	// create a new MDI client window. maximized, if the previous is so.
	mcs.szClass = OLEDBMDICLASS;
	mcs.szTitle = UNTITLED;
	mcs.hOwner  = hAppInstance;
	mcs.style   = hWndActiveChild && IsZoomed(hWndActiveChild) ? WS_MAXIMIZE : 0;
	mcs.x = mcs.cx = mcs.y = mcs.cy = CW_USEDEFAULT;
	hWndActiveChild = (HWND)(UINT)SendMessage(hWndMDIClient, WM_MDICREATE, 0, (LPARAM)(LPMDICREATESTRUCT)&mcs);
        
    // check if it was created, if it wasn't free up resource and flag warning
    if (!hWndActiveChild)
    {
		MessageBox(hWndFrame, CREATECHILDERR, EXECERROR, MB_OK|MB_ICONEXCLAMATION|MB_TASKMODAL);
		goto error;
    }
        
	// Display the Provider string, PROVIDER and IDBCreateCommand/IOpenRowset in the title
	// of newly created window. Increment the child window counter
 	wsprintf(szBuffer, QUERY_STRING, pICommand);
		
	SendMessage(hWndStmtList, CB_ADDSTRING, 0, (LPARAM)(LPSTR)szBuffer);
	SendMessage(hWndStmtList, CB_SELECTSTRING, 0, (LPARAM)(LPSTR)szBuffer);
	
 	wsprintf(szBuffer, PROVIDER_SESSION_COMMAND_FORMAT, (LPSTR)szProvName, pIUnknown, pICommand);
	
	SetWindowText(hWndActiveChild, szBuffer);
	nChildCount++;
	
	// Update the Command Combo-Box on the tool bar.
	ChangeCurrentICommand(hWndStmtList);
	bReturn = TRUE;

error:
	// Note that we obtained pIUnknown (Session ptr) from the window.
	// So we leave it alone.

	// Release ICommand on error only.
	// The pointer value has been copied to the window.
	if (pICommand && !bReturn)
		pICommand->Release();

	if (pIDBCreateCommand)
		pIDBCreateCommand->Release();

	if (pIOpenRowset)
		pIOpenRowset->Release();
}




//**********************************************************************
// 
// ChangeCurrentCursor
// 
// Purpose:
// 
//     Change the displayed PROVIDER in the PROVIDER(s) combobox.
//     Also activate the appropriate MDI child window that
//     has the same PROVIDER as the new PROVIDER in the combobox.
//
// Parameters:
//
// 	HWND 			hWndCrsrList               - handle to the window
// 
// Return Value:
// 
// Function Calls:
//     Function                    Location
// 
// 
//     
// Comments:      
// 
// 
//**********************************************************************
void FAR PASCAL ChangeCurrentCursor(HWND hWndCrsrList)
{
	ULONG				nNewhdbc;				// New PROVIDER position
	ULONG				nConnects;				// # of connections
	ULONG				nCount;					// Counter
	char				szBuffer[MAXBUFLEN+1];	// String Buffer
	BOOL				bChangedFocus;			// Activate different MDI child
	HWND				hWndChild;				// MDI Child window
	IDBCreateCommand* 	pIDBCreate1;			// IDBCreateCommand #1
	IDBCreateCommand* 	pIDBCreate2;			// IDBCreateCommand #2
	ICommand*			pICommand;				// ICommand Object

	// check to see if the current selection in the combo-box
	// differs from the previous selection, if it is the same then
	// simply return. Check is made by searching a marked string
	// in the PROVIDER combobox.
	nNewhdbc = (int)SendMessage(hWndCrsrList, CB_GETCURSEL, 0, 0);
	nConnects = (int)SendMessage(hWndCrsrList, CB_GETCOUNT, 0, 0);

	for(nCount = 0; nCount < nConnects; nCount++)
	{
		SendMessage(hWndCrsrList, CB_GETLBTEXT, nCount, (LPARAM)(LPSTR)szBuffer);
		if (strstr(szBuffer, CUR_MARK))
			break;
	}

	if (nCount == nNewhdbc)
		return;

	// if there was a current marked hdbc in the combobox, remove the
	// mark from the string and replace it in the combobox.
	if (nCount != nConnects)
	{
		SendMessage(hWndCrsrList, CB_GETLBTEXT, nCount, (LPARAM)(LPSTR)szBuffer);
		szBuffer[strlen(szBuffer)-2] = '\0';
		SendMessage(hWndCrsrList, CB_INSERTSTRING, nCount, (LPARAM)(LPSTR)szBuffer);
		SendMessage(hWndCrsrList, CB_DELETESTRING, nCount+1, 0);
	}
	
	// Create a new marked string with currently selected hdbc string in
	// the combobox and replace it with the original.
	SendMessage(hWndCrsrList, CB_GETLBTEXT, nNewhdbc, (LPARAM)(LPSTR)szBuffer);
	strcat(szBuffer, CUR_MARK);
	SendMessage(hWndCrsrList, CB_INSERTSTRING, nNewhdbc, (LPARAM)(LPSTR)szBuffer);
	SendMessage(hWndCrsrList, CB_DELETESTRING, nNewhdbc+1, 0);
	SendMessage(hWndCrsrList, CB_SELECTSTRING, 0, (LPARAM)(LPSTR)szBuffer);

	// Reset the ICommand combobox. Search through the MDI child windows
	// and collect all ICommands from window titles that have the same
	// PROVIDER value as the newly selected PROVIDER in the PROVIDER(s) combo-box above.
	SendMessage(hWndStmtList, CB_RESETCONTENT, 0, 0);
	for (bChangedFocus=FALSE, hWndChild=GetWindow(hWndMDIClient, GW_CHILD);	hWndChild; hWndChild = GetWindow(
		hWndChild, GW_HWNDNEXT))
	{
		// Check class name to skip iconized titles or other
		// such non MDI Child windows
		GetClassName(hWndChild, szBuffer, MAXBUFLEN);
		if (strcmp(szBuffer, OLEDBMDICLASS))
			continue;

		GetWindowText(hWndChild, szBuffer, MAXBUFLEN);
		sscanf(szBuffer, SCANSESSIONCOMMAND_FORMAT, &pIDBCreate1, &pICommand);

		SendMessage(hWndCrsrList, CB_GETLBTEXT, (WPARAM)nNewhdbc, (LPARAM)(LPSTR)szBuffer);
		sscanf(szBuffer, SCANSESSION_FORMAT, &pIDBCreate2);

		if (pIDBCreate1 != pIDBCreate2)
			continue;
                
		if (!bChangedFocus)
		{
            // If the first match is found, change the active window
        	// and update the ICommand(s) combobox with a new entry that
	        // has ICommand marked with current marker.
			bChangedFocus = TRUE;
			hWndActiveChild = hWndChild;
			SendMessage(hWndMDIClient, WM_MDIACTIVATE, (WPARAM)hWndChild, 0);
			wsprintf(szBuffer, CURQUERY_STRING, pICommand);
			SendMessage(hWndStmtList, CB_ADDSTRING, 0, (LPARAM)(LPSTR)szBuffer);
			SendMessage(hWndStmtList, CB_SELECTSTRING, 0, (LPARAM)(LPSTR)szBuffer);
		}
		else
		{
			// simply add the ICommand in the ICommand(s) combobox.
			wsprintf(szBuffer, QUERY_STRING, pICommand);
			SendMessage(hWndStmtList, CB_ADDSTRING, 0, (LPARAM)(LPSTR)szBuffer);
		}
	}
}

//**********************************************************************
// 
// ChangeCurrentICommand
// 
// Purpose:
// 
//     Change the current selection in the ICommand(s) combobox.
//     Update the current marker in the combobox and activate
//     proper MDI Child window.
//
// Parameters:
//
// 	HWND 			hWndStmtList               - handle to the window
// 
// Return Value:
// 
// Function Calls:
//     Function                    Location
// 
// 
//     
// Comments:      
// 
// 
//**********************************************************************
void FAR PASCAL ChangeCurrentICommand(HWND hWndStmtList)
{
	ULONG				nNewICommand;			// New Selection in Combo-Box
	ULONG 				nICommands;				// # of ICommands
	ULONG 				nCount;					// Counter
	char				szBuffer[MAXBUFLEN+1];	// String Buffer
	HWND				hWndChild;				// MDI Child Window Handle
	IDBCreateCommand* 	pIDBCreate1;			// IDBCreateCommand Object #1
	IDBCreateCommand* 	pIDBCreate2;			// IDBCreateCommand Object #2
	ICommand*			pICommand1;				// ICommand Object #1
	ICommand*			pICommand2;				// ICommand Object #2

	// Find the index of new selection and total number of ICommand(s)
	nNewICommand = (int)SendMessage(hWndStmtList, CB_GETCURSEL, 0, 0);
	nICommands 	 = (int)SendMessage(hWndStmtList, CB_GETCOUNT,  0, 0);

	// Check if the current selection is same as previous one, if
	// so simply return. Check for marker to determine previous selection
	for(nCount = 0; nCount < nICommands; nCount++)
	{
		SendMessage(hWndStmtList, CB_GETLBTEXT, nCount, (LPARAM)(LPSTR)szBuffer);
		if (strstr(szBuffer, CUR_MARK))
			break;
	}

	if (nCount == nNewICommand)
		return;

	// If a previous selection was found, remove current marker
	// and update it in the ICommand(s) combobox.
	if (nCount != nICommands)
	{
		SendMessage(hWndStmtList, CB_GETLBTEXT, nCount, (LPARAM)(LPSTR)szBuffer);
		szBuffer[strlen(szBuffer)-2] = '\0';
		SendMessage(hWndStmtList, CB_INSERTSTRING, nCount, (LPARAM)(LPSTR)szBuffer);
		SendMessage(hWndStmtList, CB_DELETESTRING, nCount+1, 0);
	}
	
	// Mark the current selection and update it in the ICommand(s) combobox
	SendMessage(hWndStmtList, CB_GETLBTEXT, nNewICommand, (LPARAM)(LPSTR)szBuffer);
	strcat(szBuffer, CUR_MARK);
	SendMessage(hWndStmtList, CB_INSERTSTRING, nNewICommand, (LPARAM)(LPSTR)szBuffer);
	SendMessage(hWndStmtList, CB_DELETESTRING, nNewICommand+1, 0);
	SendMessage(hWndStmtList, CB_SELECTSTRING, 0, (LPARAM)(LPSTR)szBuffer);

	// Scan ICommand value and DSN value from current selection in
	// PROVIDER(s) and ICommand(s) comboboxes.
	sscanf(szBuffer, QUERY_STRING, &pICommand1);
	
	SendMessage( hWndCrsrList, CB_GETLBTEXT, 
				(UINT)SendMessage(hWndCrsrList, CB_GETCURSEL, 0, 0),
				(LPARAM)(LPSTR)szBuffer);

	sscanf(szBuffer, SCANSESSION_FORMAT, &pIDBCreate1);

	// Go through list of MDI Child windows and match the ICommand and PROVIDER
	// values. If a match if found (must be), activate the window
	for (hWndChild=GetWindow(hWndMDIClient, GW_CHILD); hWndChild; hWndChild=GetWindow(hWndChild, GW_HWNDNEXT))
	{
		// Ignore non MDI child windows
		GetClassName(hWndChild, szBuffer, MAXBUFLEN);
		if (strcmp(szBuffer, OLEDBMDICLASS))
			continue;

		GetWindowText(hWndChild, szBuffer, MAXBUFLEN);
		sscanf(szBuffer, SCANSESSIONCOMMAND_FORMAT, &pIDBCreate2, &pICommand2);

		if (pIDBCreate1 == pIDBCreate2 && pICommand1 == pICommand2)
		{
			hWndActiveChild = hWndChild;
			SendMessage(hWndMDIClient, WM_MDIACTIVATE, (WPARAM)hWndChild, 0);
			break;
		}
	}
}

//**********************************************************************
// 
// DisplayNewCrsrAndICommand
// 
// Purpose:
// 
//     Change the current selection in the ICommand(s) combobox.
//     Update the current marker in the combobox and activate
//     proper MDI Child window.
//
// Parameters:
//
// 	HWND 			hWndStmtList               - handle to the window
// 
// Return Value:
// 
// Function Calls:
//     Function                    Location
// 
// 
//     
// Comments:      
// 
// 
//**********************************************************************
void FAR PASCAL DisplayNewCrsrAndICommand()
{
	ULONG 				nConnects;				// # of PROVIDER(s)
	ULONG 				nICommands;				// # of ICommand(s)
	ULONG 				nOldPROVIDER;				// Prev selected PROVIDER in combobox
	ULONG				nOldICommand;			// Prev selected ICommand in combobox
	ULONG				nIndex;					// Counter
	char				szBuffer[MAXBUFLEN+1];	// String Buffer
	HWND				hWndChild;				// MDI Child Window
	IDBCreateCommand* 	pIDBCreate1;			// IDBCreateCommand Object #1
	IDBCreateCommand* 	pIDBCreate2;			// IDBCreateCommand Object #2
	ICommand*			pICommand1;				// ICommand Object #1
	ICommand*			pICommand2;				// ICommand Object #2

	// Scan PROVIDER and ICommand values from newly selected window
	GetWindowText(hWndActiveChild, szBuffer, MAXBUFLEN);
	sscanf(szBuffer, SCANSESSIONCOMMAND_FORMAT, &pIDBCreate1, &pICommand1);

	// Search through list of PROVIDER(s) in PROVIDER combobox and find
	// matching PROVIDER. remove marker from prev selection and add
	// marker to the new selection. Update combobox accordingly.
	nConnects = (int)SendMessage(hWndCrsrList, CB_GETCOUNT,  0, 0);
	nOldPROVIDER   = (int)SendMessage(hWndCrsrList, CB_GETCURSEL, 0, 0);

	for(pIDBCreate2 = (IDBCreateCommand*)(nIndex = 0); pIDBCreate1 != pIDBCreate2; nIndex++)
	{
		SendMessage(hWndCrsrList, CB_GETLBTEXT, nIndex, (LPARAM)(LPSTR)szBuffer);
		sscanf(szBuffer, SCANSESSION_FORMAT, &pIDBCreate2);
	}

	// Change in PROVIDER combobox required.
	if (--nIndex != nOldPROVIDER)
	{
		SendMessage(hWndCrsrList, CB_GETLBTEXT, nOldPROVIDER, (LPARAM)(LPSTR)szBuffer);
		szBuffer[strlen(szBuffer)-2] = '\0';
		SendMessage(hWndCrsrList, CB_INSERTSTRING, nOldPROVIDER, (LPARAM)(LPSTR)szBuffer);
		SendMessage(hWndCrsrList, CB_DELETESTRING, nOldPROVIDER+1, 0);

		SendMessage(hWndCrsrList, CB_GETLBTEXT, nIndex, (LPARAM)(LPSTR)szBuffer);
		strcat(szBuffer, CUR_MARK);
		SendMessage(hWndCrsrList, CB_INSERTSTRING, nIndex, (LPARAM)(LPSTR)szBuffer);
		SendMessage(hWndCrsrList, CB_DELETESTRING, nIndex+1, 0);
		SendMessage(hWndCrsrList, CB_SELECTSTRING, 0, (LPARAM)(LPSTR)szBuffer);

		// Reset the ICommand(s) combobox, search through the list
		// of MDI child windows and find all hstmt(s) associated to
		// new PROVIDER. Build the new list of ICommand(s) for the ICommand
		// combobox. Mark the one ICommand that matches the currently
		// activated MDI child window.
		SendMessage(hWndStmtList, CB_RESETCONTENT, 0, 0);
		for (hWndChild=GetWindow(hWndMDIClient,GW_CHILD);hWndChild;hWndChild=GetWindow(hWndChild,GW_HWNDNEXT))
		{
			GetClassName(hWndChild, szBuffer, MAXBUFLEN);
			if (strcmp(szBuffer, OLEDBMDICLASS))
				continue;

			GetWindowText(hWndChild, szBuffer, MAXBUFLEN);
			sscanf(szBuffer, SCANSESSIONCOMMAND_FORMAT, &pIDBCreate2, &pICommand2);

			if (pIDBCreate1 != pIDBCreate2)
				continue;

			if (hWndActiveChild == hWndChild)
			{
				wsprintf(szBuffer, CURQUERY_STRING, pICommand2);
				SendMessage(hWndStmtList, CB_ADDSTRING, 0, (LPARAM)(LPSTR)szBuffer);
				SendMessage(hWndStmtList, CB_SELECTSTRING, 0, (LPARAM)(LPSTR)szBuffer);
			}
			else
			{
				wsprintf(szBuffer, QUERY_STRING, pICommand2);
				SendMessage(hWndStmtList, CB_ADDSTRING, 0, (LPARAM)(LPSTR)szBuffer);
			}
		}
	}
	// No change in PROVIDER combobox required
	else
	{
		// Go through the list of ICommand(s) in ICommand combobox.
		// Find the one that matches the currently activated MDI child window.
		nOldICommand = (int)SendMessage(hWndStmtList, CB_GETCURSEL, 0, 0);
		nICommands = (int)SendMessage(hWndStmtList, CB_GETCOUNT, 0, 0);

		for(pICommand2 = (ICommand*)(nIndex = 0); pICommand1 != pICommand2; nIndex++)
		{
			SendMessage(hWndStmtList, CB_GETLBTEXT, nIndex, (LPARAM)(LPSTR)szBuffer);
			sscanf(szBuffer, QUERY_STRING, &pICommand2);
		}

		// New index in ICommand differs from previous selection
		if (--nIndex != nOldICommand)
		{
			// Remove the marker from previous selection.
			// Add it to the new string and update the combobox display
			SendMessage(hWndStmtList, CB_GETLBTEXT, nOldICommand, (LPARAM)(LPSTR)szBuffer);
			szBuffer[strlen(szBuffer)-2] = '\0';
			SendMessage(hWndStmtList, CB_INSERTSTRING, nOldICommand, (LPARAM)(LPSTR)szBuffer);
			SendMessage(hWndStmtList, CB_DELETESTRING, nOldICommand+1, 0);

			SendMessage(hWndStmtList, CB_GETLBTEXT, nIndex, (LPARAM)(LPSTR)szBuffer);
			strcat(szBuffer, CUR_MARK);
			SendMessage(hWndStmtList, CB_INSERTSTRING, nIndex, (LPARAM)(LPSTR)szBuffer);
			SendMessage(hWndStmtList, CB_DELETESTRING, nIndex+1, 0);
			SendMessage(hWndStmtList, CB_SELECTSTRING, 0, (LPARAM)(LPSTR)szBuffer);
		}
	}
}

//**********************************************************************
// 
// FreeConnect
// 
// Purpose:
// 
//     Disconnect and Free the currently selected PROVIDER in
//     the PROVIDER listbox in disconnect dialog. Call RELEASE
//     to free the PROVIDER. Close all MDI
//     child windows associated with this PROVIDER. That will
//     automatically free associated ICommand(s).
//
// Parameters:
//
// 	HWND 			hWndhdbc               - handle to the window
// 
// Return Value:
// 
// Function Calls:
//     Function                    Location
// 
//     IDBCreateCommand::Release   provider's Command object
//     
// Comments:      
// 
// 
//**********************************************************************
void FAR PASCAL FreeConnect(HWND hWndhdbc)
{
	int 				nIndex;					// Current Selection in the listbox of disconnect dlg
	int					nCurrent;				// Current Selected PROVIDER(s) combobox
	char				szBuffer[MAXBUFLEN+1];	// String Buffer
	char				szSelect[MAXBUFLEN+1];	// Original Selected PROVIDER(s) combobox
	char				szProvName[MAXBUFLEN+1];// DSN string
	HWND				hWndChild;				// MDI Child window
	IDBCreateCommand * 	pIDBCreate1;			// IDBCreateCmmand Object #1
	IDBCreateCommand * 	pIDBCreate2;			// IDBCreateCmmand Object #2
	IErrorInfo *		pIErrorInfo;			// IErrorInfo Object

	// Check current selection in the list box of disconnect dialog. 
	// Scan PROVIDER value from the current selection.
	if ((nIndex = (int)SendMessage(hWndhdbc, LB_GETCURSEL, 0, 0)) == LB_ERR)
		return;

	SendMessage(hWndhdbc, LB_GETTEXT, (WPARAM)nIndex, (LPARAM)(LPSTR)szBuffer);
	sscanf(szBuffer, SCANPROVIDERSESSION_FORMAT, szProvName, &pIDBCreate1);

	// Go through the list of MDI child windows and find matching PROVIDER(s)
	// close all children who have the same PROVIDER value. Closing them
	// automatically frees associated ICommands. See CloseICommandWindow.
	for(hWndChild = GetWindow(hWndMDIClient, GW_CHILD); hWndChild; )
	{
		// Store next window handle before destroying the currentone
		HWND hWndTemp = GetWindow(hWndChild, GW_HWNDNEXT);
		
		// Ignore non MDI child windows
		GetClassName(hWndChild, szBuffer, MAXBUFLEN);
		if (!strcmp(szBuffer, OLEDBMDICLASS))
		{
			GetWindowText(hWndChild, szBuffer, MAXBUFLEN);
			sscanf(szBuffer, SCANSESSION_TITLEFORMAT, &pIDBCreate2);
			if (pIDBCreate1 == pIDBCreate2)
			{
				// Destroy the window and restart search
				SendMessage(hWndMDIClient, WM_MDIDESTROY, (WPARAM)hWndChild, 0);
				hWndTemp = GetWindow(hWndMDIClient, GW_CHILD);
			}
		}
		hWndChild = hWndTemp;
	}

	// Release the Command Object & return
	if( pIDBCreate1 )
		pIDBCreate1->Release();

	// Release any remaining error objects.  This is idempotent.
	// Otherwise the provider might have an outstanding global-object count.
	GetErrorInfo( 0, &pIErrorInfo );
	if (pIErrorInfo)
		pIErrorInfo->Release();

	// Unload any DLL's no longer being used
	CoFreeUnusedLibraries();
		
	// Update the PROVIDER(s) combobox display by removing the deleted PROVIDER
	// from the list and reselecting the previous selection
	wsprintf(szBuffer, PROVIDER_SESSION_FORMAT, (LPSTR)szProvName, pIDBCreate1);
	nCurrent = (int)SendMessage(hWndCrsrList, CB_GETCURSEL, 0, 0);
	SendMessage(hWndCrsrList, CB_GETLBTEXT, nCurrent, (LPARAM)(LPSTR)szSelect);
	nIndex = (int)SendMessage(hWndCrsrList, CB_FINDSTRING, 0, (LPARAM)(LPSTR)szBuffer);
	SendMessage(hWndCrsrList, CB_DELETESTRING, (WPARAM)nIndex, 0);
	SendMessage(hWndCrsrList, CB_SELECTSTRING, 0, (LPARAM)(LPSTR)szSelect);
	
	// If there is no query window open and the current selected PROVIDER
	// was deleted, make sure to make the next available PROVIDER as current
	if (SendMessage(hWndCrsrList, CB_GETCOUNT, 0, 0) &&
		!GetWindow(hWndMDIClient, GW_CHILD) && (nCurrent == nIndex))
	{
		if ((nCurrent = (int)SendMessage(hWndCrsrList, CB_GETCURSEL, 0, 0))!=CB_ERR)
			return;
		SendMessage(hWndCrsrList, CB_GETLBTEXT, 0, (LPARAM)(LPSTR)szSelect);
		strcat(szSelect, CUR_MARK);
		SendMessage(hWndCrsrList, CB_INSERTSTRING, 0, (LPARAM)(LPSTR)szSelect);
		SendMessage(hWndCrsrList, CB_DELETESTRING, 1, 0);
		SendMessage(hWndCrsrList, CB_SELECTSTRING, 0, (LPARAM)(LPSTR)szSelect);
	}
}

//**********************************************************************
// 
// FreeICommand
// 
// Purpose:
// 
//     Free a ICommand window based upon current selection in
//     ICommand list box in the disconnect dialog.
//
// Parameters:
//
// 	HWND 			hWndhstmt               - handle to the window
// 	HWND 			hWndhdbc                - handle to the window
//  int             nIndex					- Index
// 
// Return Value:
// 
// Function Calls:
//     Function                    Location
// 
// 
//     
// Comments:      
// 
// 
//**********************************************************************
void FAR PASCAL FreeICommand(HWND hWndhstmt, HWND hWndhdbc, int nIndex)
{
	char				szBuffer[MAXBUFLEN+1];	// display buffer
	HWND				hWndChild;				// MDI child window
	IDBCreateCommand* 	pIDBCreate1;			// IDBCreateCommand Object #1
	IDBCreateCommand* 	pIDBCreate2;			// IDBCreateCommand Object #2
	ICommand*			pICommand1;				// ICommand Object #1
	ICommand*			pICommand2;				// ICommand Object #2

	// Scan the ICommand and PROVIDER values from the current selections in
	// respective listboxes of disconnect dialog box.
	SendMessage(hWndhstmt, LB_GETTEXT, nIndex, (LPARAM)(LPSTR)szBuffer);
	sscanf(szBuffer, QUERY_STRING, &pICommand1);
	SendMessage(hWndhdbc, LB_GETTEXT, (UINT)SendMessage(hWndhdbc, LB_GETCURSEL,	0, 0), (LPARAM)(LPSTR)szBuffer);
	sscanf(szBuffer, SCANSESSION_FORMAT, &pIDBCreate1);
        
    // Go through the list of MDI child windows and find matching window
    // that has same values for PROVIDER and ICommand. Destroy the matching window.
    // That will call CloseICommandWindow and free up associated ICommand(s).
	for(hWndChild=GetWindow(hWndMDIClient, GW_CHILD); hWndChild; hWndChild=GetWindow(hWndChild, GW_HWNDNEXT))
	{
		// Ignore non MDI child windows
		GetClassName(hWndChild, szBuffer, MAXBUFLEN);
		if( strcmp(szBuffer, OLEDBMDICLASS) )
			continue;

		GetWindowText(hWndChild, szBuffer, MAXBUFLEN);
		sscanf(szBuffer, SCANSESSIONCOMMAND_FORMAT, &pIDBCreate2, &pICommand2);
		if (pIDBCreate1 == pIDBCreate2 && pICommand1 == pICommand2)
			break;
	}
	SendMessage(hWndMDIClient, WM_MDIDESTROY, (WPARAM)hWndChild, 0);
}

//**********************************************************************
// 
// CloseICommandWindow
// 
// Purpose:
// 
//     Close a ICommand window. 
//     Call ICommand->Release() to free associated ICommand(s).
//
// Parameters:
//
// 	HWND 			hWnd               - handle to the window
// 
// Return Value:
// 
// Function Calls:
//     Function                    Location
// 
//     ICommand::Release           provider's Command object
//     
// Comments:      
// 
// 
//**********************************************************************
void FAR PASCAL CloseICommandWindow(HWND hWnd)
{
	char		szBuffer[MAXBUFLEN+1];	// String buffer
	char		szSelect[MAXBUFLEN+1];	// Current Selected ICommand(s)
	ICommand*	pICommand;				// ICommand Object

	// Scan the ICommand value from the window title
	GetWindowText(hWnd, szBuffer, MAXBUFLEN);
	sscanf(szBuffer, SCANCOMMAND_TITLEFORMAT, &pICommand);

	// Release the Command Object & return
	if( pICommand )
		pICommand->Release();

	// Find the matching ICommand in the ICommand(s) combobox and remove it
	// from the list. Closure of a MDI child window will cause MDIClient
	// to automatically activate a different child window if available.
	// That will automatically refresh the ICommand and PROVIDER displays. 
	// See DisplayNewCrsrAndICommand function.
	wsprintf( szBuffer, QUERY_STRING, pICommand );
	
	SendMessage( hWndStmtList, CB_GETLBTEXT, 
				(WPARAM)SendMessage(hWndStmtList, CB_GETCURSEL, 0, 0),
				(LPARAM)(LPSTR)szSelect );
	
	SendMessage( hWndStmtList, CB_DELETESTRING, 
				(WPARAM)SendMessage(hWndStmtList, CB_FINDSTRING, 0,
				(LPARAM)(LPSTR)szBuffer), 0 );
	
	SendMessage( hWndStmtList, CB_SELECTSTRING,
				(WPARAM)-1, 
				(LPARAM)(LPSTR)szSelect );
	
	// Decrement the child window counter.
	nChildCount--;
}

//**********************************************************************
// 
// ExecuteQuery
// 
// Purpose:
// 
//     Execute the user typed SQL Statements in the currently 
//     active MDI child window. If successful, then prepare
//     the list of results and display it in the child listbox.
//     Display errors in the OLE DB function(s) failed.
//
// Parameters:
//
// Return Value:
// 
// Function Calls:
//     Function                    Location
// 
//     ExecuteCommand              query.cpp
//     GetDataFromRowset           query.cpp
// 
//     
// Comments:      
// 
// 
//**********************************************************************
void FAR PASCAL ExecuteQuery()
{
	CHAR				szBuffer[MAXBUFLEN+1];		// String Buffer
	WCHAR				wszBuffer[MAXBUFLEN+1];		// String Buffer (WCHAR)
	signed short int	swColLength = MAXDATALEN;	// Column Data Length
	HCURSOR				hOldCursor;					// Default Cursor Handle
	IUnknown*			pIUnknown 	= NULL;			// Session Object
	ICommand*			pICommand 	= NULL;			// ICommand Object
	IOpenRowset*		pIOpenRowset= NULL;			// IOpenRowset Object
	IRowset*			pIRowset 	= NULL;			// IRowset Object
	HRESULT				hr;							// HRESULT

	// Check if there is an active window available
	if (!hWndActiveChild)
	{
		MessageBox(hWndFrame, ((SendMessage(hWndCrsrList, CB_GETCOUNT, 0, 0) <=0) ?
			MAKECONNECT : OPENWINDOW ), NOCOMMANDERROR, MB_OK | MB_ICONHAND);
		return;
	}

	// Change cursor shape to hour glass
	hOldCursor = SetCursor(LoadCursor((HINSTANCE)NULL, IDC_WAIT));
        	
	// Scan PROVIDER, session and ICommand values
	GetWindowText(hWndActiveChild, (char*)szBuffer, MAXBUFLEN);
	sscanf(szBuffer, SCANSESSIONCOMMAND_FORMAT, &pIUnknown, &pICommand);

	// Get the user typed SQL
	GetWindowText(GetDlgItem((HWND)GetWindowLong(hWndActiveChild, GWLAPP_HDLG), IDTEXT_SQL), szBuffer, MAXBUFLEN);

	// Convert ANSI String to WCHAR	String
	MultiByteToWideChar(CP_ACP, 0, szBuffer, -1, wszBuffer, MAXBUFLEN+1);

	// Execute the Command Object
	hr = ExecuteCommand( pIUnknown, pICommand, wszBuffer, &pIRowset ); 

	if (FAILED(hr))
		return;

	// Empty IRowset
	if( hr == ResultFromScode(S_FALSE) )
	{ 
		DumpErrorHResult( ResultFromScode(S_OK), (LPSTR)"ExecuteCommand returned No Rowset!!" );
		return;
	}

	// Get Data from the IRowset Object
	GetDataFromRowset( pIRowset );
}


//**********************************************************************
// 
// CloseIDBCreateCommand
// 
// Purpose:
// 
//     Go through all open PROVIDER's (IDBCreateCommand(s) and ICommand(s)) 
//     and close them one by one.
//
// Parameters:
//
// Return Value:
// 
// Function Calls:
//     Function                    Location
// 
//     IDBCreateCommand::Release   provider's Command object
//     
// Comments:      
// 
// 
//**********************************************************************
BOOL FAR PASCAL CloseIDBCreateCommand()
{
	ULONG 				nIndex;					// Index
	ULONG				nCount;					// # of PROVIDER(s)
	char				szBuffer[MAXBUFLEN+1];	// String Buffer
	HWND				hWndChild;				// MDI Child Window
	IDBCreateCommand* 	pIDBCreate1;			// IDBCreateCommand Object #1
	IDBCreateCommand* 	pIDBCreate2;			// IDBCreateCommand Object #2

	// Get count of connected PROVIDER(s) from the PROVIDER(s) combobox on the toolbar
	if (!(nCount = (int)SendMessage(hWndCrsrList, CB_GETCOUNT, 0, 0)))
		return (TRUE);

	// Go through all available MDI child windows and for each PROVIDER,
	// find the matching MDI child window and ask it for closure, thereby
	// freeing the associated ICommand (see CloseICommandWindow). Once all
	// associated ICommand(s) are freed, free the PROVIDER
	for (nIndex = 0; nIndex < nCount; nIndex++)
	{       
		// Scan current indexed PROVIDER from PROVIDER(s) combobox
		SendMessage(hWndCrsrList, CB_GETLBTEXT, (WPARAM)nIndex, (LPARAM)(LPSTR)szBuffer);
		sscanf(szBuffer, SCANSESSION_FORMAT, &pIDBCreate1);
		
		// Search through the list of MDI Child Windows
		for(hWndChild = GetWindow(hWndMDIClient, GW_CHILD); hWndChild; )
		{
			// Store the next child, before destroying the current
			HWND hWndTemp = GetWindow(hWndChild, GW_HWNDNEXT);
		
			// Ignore non MDI child windows
			GetClassName(hWndChild, szBuffer, MAXBUFLEN);
			if (!strcmp(szBuffer, OLEDBMDICLASS))
			{
				GetWindowText(hWndChild, szBuffer, MAXBUFLEN);
				sscanf(szBuffer, SCANSESSION_TITLEFORMAT, &pIDBCreate2);
				if (pIDBCreate1 == pIDBCreate2)
				{
					// Destroy the window and restart search
					SendMessage(hWndMDIClient, WM_MDIDESTROY, (WPARAM)hWndChild, 0);
					hWndTemp = GetWindow(hWndMDIClient, GW_CHILD);
				}
			}
			hWndChild = hWndTemp;
		}

		// Call IDBCreateCommand->Release() 
		// to free the current IDBCreateCommand resource
		if( pIDBCreate1 )
			pIDBCreate1->Release();
	}
	
	// Reset the PROVIDER(s) combobox display and display all connections
	// closed message. Return success to let application exit.
	SendMessage(hWndCrsrList, CB_RESETCONTENT, 0, 0);
	MessageBox(hWndFrame, CLOSEALLSESSION, LOGOUTINFO,	MB_OK | MB_ICONINFORMATION);
	return (TRUE);
}

/*
	FUNCTION: FreeEnvironment()
	COMMENTS: Free the OLE environment.
*/
HRESULT FreeEnvironment()
{
	IErrorInfo	*pIErrorInfo;	//IErrorInfo

    // Release the task memory allocator
	if( g_pIMalloc )
		g_pIMalloc->Release();

	// Release any remaining error objects.  This is idempotent.
	// Otherwise the provider might have an outstanding global-object count.
	GetErrorInfo( 0, &pIErrorInfo );
	if (pIErrorInfo)
		pIErrorInfo->Release();

	// Free the error queues
	SetErrorInfo(0,NULL);

	// Uninitialize OLE
	CoUninitialize();
	return S_OK;
}


//**********************************************************************
// 
// ExecuteCommand
// 
// Purpose:
// 
//    Executes the query command that was previously set on the Command object,
//    and returns a first interface pointer on the resulting Rowset object.
// 
// Parameters:
// 	  IOpenRowset*	pIOpenRowset	- interface pointer to data provider's
//									  IOpenRowset
// 	  ICommand*		pICommand       - interface pointer on data provider's
//						              Command object
// 	  LPWSTR		wszBuffer		- SQL-style query string to be sent
//						              to the Command object or table/file name to
//									  be sent to IOpenRowset
// 	  IRowset**		ppIRowset_out   - out pointer through which to return 
//						              interface pointer on provider's
//							          Rowset object
// 
// Return Value:
//     S_OK        - Success
//     E_*         - Failure
// 
// Function Calls:
//     Function                    Location
//     
//     ICommand::Execute           provider's Command object
//     IMalloc::Free               OLE task memory allocator
//     
// 
//     assert                      c runtime
// 
// 
//     
// Comments:      
// 
//     The interface pointer returned through ppIRowset_out has been AddRef'ed, 
//     it must be Release'd later by the caller.
//
//**********************************************************************
HRESULT ExecuteCommand(
	IUnknown*	pIUnknown,		// Session object
	ICommand*	pICommand,		// Command object
	LPWSTR	 	wszBuffer,		// SQL String (WCHAR) or Table Name
	IRowset**	ppIRowset_out
	)
{
	ICommandText*		pICommandText = NULL;	// ICommandText Object
	IOpenRowset*		pIOpenRowset = NULL;
	DBID				TableID;				// Table ID
	HRESULT				hr = S_OK;				// HRESULT

	// Asserts
	assert(ppIRowset_out != NULL);
    assert(wszBuffer != NULL);

	memset(&TableID, 0, sizeof(DBID));

	// If no command object use IOpenRowset
	if (NULL == pICommand)
	{
		// if no Command object support, attempt to get the IOpenRowset interface
		if( FAILED(hr = pIUnknown->QueryInterface(IID_IOpenRowset, (void**)&pIOpenRowset)) )
		{
	        GetDetailedErrorInfo(hr, pIUnknown, IID_IUnknown, "QI for IOpenRowset FAILED!!");
			goto error;
		}
		// Pass in table/file name
		TableID.eKind = DBKIND_NAME;

		TableID.uName.pwszName = wszBuffer;

		// From IOpenRowset, get a rowset object
		if( FAILED(hr = pIOpenRowset->OpenRowset(
								NULL,							// pUnkOuter
								&TableID,						// pTableID
								NULL,							// pIndexID
								IID_IRowset,					// refiid
								0,								// cProperties
								NULL,							// rgProperties
 								(IUnknown**)ppIRowset_out)) )  		// IRowset pointer
		{
     		GetDetailedErrorInfo(hr, pIOpenRowset, IID_IOpenRowset, "IOpenRowset->OpenRowset FAILED!!");
			goto error;
		}
	}
	else
	{
		// QueryInterface for ICommandText::SetCommandText
		if( SUCCEEDED(hr = pICommand->QueryInterface(IID_ICommandText,(LPVOID*)&pICommandText)) )
		{
			// Tell the command object to copy this command text
			// The command object will then use this query when we call ICommand::Execute
			if( FAILED(hr = pICommandText->SetCommandText(DBGUID_DBSQL, wszBuffer)) )
			{
    		    GetDetailedErrorInfo(hr, pICommandText, IID_ICommandText, "ICommandText->SetCommandText FAILED!!");
				goto error;
			}
		}

		// From the command object, get a rowset object by executing command
		if( FAILED(hr = pICommand->Execute(
							NULL,							// pUnkOuter
							IID_IRowset,					// refiid
							NULL,							// disp parms
							NULL,							// rows affected
 							(IUnknown**)ppIRowset_out)) )  	// IRowset pointer
		{
			GetDetailedErrorInfo(hr, pICommand, IID_ICommand, "ICommand->Execute FAILED!!");
			goto error;
		}
	}

	// NO Rowset Returning Statement
    if( !*ppIRowset_out )
		hr = ResultFromScode(S_FALSE);
error:
	if( pICommandText )
		pICommandText->Release();
	if( pIOpenRowset )
		pIOpenRowset->Release();

	if( FAILED(hr) )
		*ppIRowset_out = NULL;

	return hr;    
}

//**********************************************************************
// 
// GetDataFromRowset
// 
// Purpose:
// 
//     Pulls the data from a Rowset object.
//     
// Parameters:
// 
// 	IRowset*	pIRowset    -  interface pointer on data provider's
//                             Rowset object
// 
// Return Value:
// 
//     S_OK        - Success
//     E_*         - Failure
// 
// Function Calls:
//     Function                    Location
// 
//	   IRowset::QueryInterface	   Clients Rowset pointer
//     SetupBindings               query.cpp
//     CreateAccessor              query.cpp
//     GetData                     query.cpp
//     CleanupRowset               query.cpp
// 
//     IMalloc::Free               OLE task memory allocator
// 
//     assert                      c runtime
// 
// Comments:      
// 
//     At a high level, a consumer pulls the data from a Rowset object by:
//     
//     1. getting metadata for the Rowset's columns
//     2. using that metadata, along with the consumer's own knowledge of
//        how it wants to recieve the data, to create bindings. Bindings
//        represent how the actual data in the Rowset's columns is
//        actually transferred to the consumer's buffer.
//     3. pass the bindings to the Rowset, and get in return an accessor
//        handle that represents that particular set of bindings   
//     4. get the actual data
//     5. clean up the rowset (at a minumum, release the accessor) 
//     
//     GetDataFromRowset performs these steps by calling GetColumnsInfo,
//     SetupBindings, CreateAccessor, GetData, and CleanupRowset
//       
//**********************************************************************
HRESULT GetDataFromRowset(
	IRowset*	pIRowset
	)
{
	char				szBuffer[MAXBUFLEN+1];		// String Buffer
	HWND				hList;						// Result Listbox Handle
	DWORD 				dwText;						// Tab Stop for Listbox
	unsigned short int	nCount;						// Index
	signed short int	swColLength = MAXDATALEN;	// Column Data Length
	int					cch;						// Count of characters
	HRESULT				hr = S_OK;							// HRESULTS
    ULONG				cCol;						// # of Columns in Rowset
    DBCOLUMNINFO*		pColumnInfo;				// Array of DBCOLUMNINFO
    WCHAR*				pStringsBuffer;				// Storage for strings

	// BINDINGS
	ULONG 				cbMaxRowSize;		// buffer size for 1 row's data
	ULONG 				cBind;
	DBBINDING			rgBind[MAX_COL];
	HCURSOR				hOldCursor = NULL;

	// ACCESSORS
	HACCESSOR			hAccessor		= NULL;

	// Asserts
	assert(pIRowset   != NULL);
	assert(g_pIMalloc != NULL);
	
	// Change cursor shape to hour glass
	hOldCursor = SetCursor(LoadCursor((HINSTANCE)NULL, IDC_WAIT));
	
	// Get the Columns Info
	GetColumnsInfo( pIRowset, &cCol, &pColumnInfo, &pStringsBuffer);

	// Call GetColumnsInfo to calculate the number of columns in
	// the result set, if more than the MAX_COL (the array boundary)
	// limit the number to MAX_COL and display truncation warning.
	// if it is 0, the statement probably was a non-SELECT simply return
	if (cCol >= MAX_COL)
	{
		cCol = MAX_COL;
		wsprintf(szDispBuffer, COLTRUNC_WARNG, MAX_COL);
		MessageBox(hWndFrame, szDispBuffer, TRUNCERR, MB_OK | MB_ICONINFORMATION);
	}
	else if (cCol == 0)
	{
		goto error;
	}

	// Reset the display in the list box. Set tabstops to display
	// multiple columns in the list box separated by tabs.
	hList = GetDlgItem((HWND)GetWindowLong(hWndActiveChild, GWLAPP_HDLG), IDLIST_RSLT);

	SendMessage(hList, LB_RESETCONTENT, 0, 0);
	SendMessage(hList, WM_SETREDRAW, FALSE, 0);
	dwText = LISTTABSTOP;
	SendMessage(hList, LB_SETTABSTOPS, (WPARAM)1, (LPARAM)(LPINT)&dwText);

	// Display a description of each column in the result set. 
	// Store the column name in the display buffer and make it
	// the first entry in the results list box of the MDI child window.
	for(nCount=0, szDispBuffer[0]='\0'; nCount < cCol; nCount++)
	{
		if (pColumnInfo[nCount].pwszName)
		{
			cch = WideCharToMultiByte(CP_ACP, 0, pColumnInfo[nCount].pwszName, -1, szBuffer, MAXBUFLEN+1, NULL, NULL);

			// Truncate if needed.
			// We should use GetTextExtents to determine width, but that's too complicated for now.
			szBuffer[MAXCOLNAMELEN] = '\0';

			// Might be empty string for column name.
			if (cch)
				strcat(szDispBuffer, szBuffer);
			else
				strcat(szDispBuffer, "<EMPTY STRING>");
		}
		else
		{
			// Missing the column name; it is unknown.
			strcat(szDispBuffer, "<NULL STRING>");
		}

		dwText = strlen(szDispBuffer);
		szDispBuffer[dwText++] = '\t';
		szDispBuffer[dwText] = '\0';
	}

	// NULL Terminate the Display Buffer
	if (*szDispBuffer)
		szDispBuffer[strlen(szDispBuffer)-1]='\0';
	
	// ADD the Column Info to the Screen
	SendMessage(hList, LB_ADDSTRING, 0, (LPARAM)(LPSTR)szDispBuffer);

	// SetUp Bindings
	if( FAILED(hr = SetupBindings( cCol, pColumnInfo, rgBind, &cBind, &cbMaxRowSize)) )
		goto error;
	
	// Create the Accessor
	if( FAILED(hr = CreateAccessor( pIRowset, rgBind, cBind, &hAccessor)) )
		goto error;

	// GetData
	if( FAILED(hr = GetData( pIRowset, cbMaxRowSize, hAccessor, rgBind, cBind, pColumnInfo, 
		cCol, hList, dwText, LB_ADDSTRING)) )
		goto error;

error:    
	// restore the cursor to default value
	SetCursor(hOldCursor);
  
	// Release the IColumnsInfo Object
	if( pColumnInfo )
		g_pIMalloc->Free( pColumnInfo );
	if( pStringsBuffer )
		g_pIMalloc->Free( pStringsBuffer );	    	
	    
	// Clean-up the Rowset
	CleanupRowset( pIRowset, hAccessor );

    return hr;    
}


//**********************************************************************
// 
// GetColumnsInfo
// 
// Purpose:
// 
//     Get the Columns metadata back for the provider to setup the bundings. 
//     
// Parameters:
//
//	IRowset*		pIRowset			- IRowset pointer to QI off of
// 	ULONG 			cCol                - number of columns in metadata
// 	DBCOLUMNINFO*	pColumnInfo         - pointer to column metadata
// 	WCHAR*			pStringsBuffer      - pointer through which to return
//                                        an array of string data, one
//                                        structure per column bound
// 
// Return Value:
//     S_OK         - Success
//     E_*          - Failure
// 
// Function Calls:
//     Function                    Location
// 
//     assert                      c runtime
//     IRowset::QueryInterface     provider's Rowset object
//     IColumnsInfo::GetColumnInfo provider's ColumnInfo object
//     IColumnsInfo::Release       provider's ColumnInfo object
// 
//     
// Comments:      
// 
// 
//**********************************************************************
HRESULT GetColumnsInfo
	(
	IRowset*		pIRowset,
	ULONG* 			pcCol,
	DBCOLUMNINFO**	ppColumnInfo,
	WCHAR**			ppStringsBuffer
	)
{

	HRESULT				hr=NOERROR;					// HRESULTS
	IColumnsInfo* 		pIColumnsInfo = NULL;		// IColumnsInfo Object

	// QI for IColumnsInfo Object
	if( FAILED(hr = pIRowset->QueryInterface( IID_IColumnsInfo, (void **) &pIColumnsInfo)) )
	{
		GetDetailedErrorInfo(hr, pIRowset, IID_IRowset, "QI for IColumnsInfo FAILED!!");
		goto error;
	}
	
	// Get column information from the command object via IColumnsInfo::GetColumnsInfo 
	if( FAILED(hr = pIColumnsInfo->GetColumnInfo( pcCol, ppColumnInfo, ppStringsBuffer)) )
	{
		GetDetailedErrorInfo(hr, pIColumnsInfo, IID_IColumnsInfo, "IColumnsInfo->GetColumnsInfo FAILED!!");
		goto error;
	}

error:
	// Release the IColumnsInfo Object
	if( pIColumnsInfo )
		pIColumnsInfo->Release();
	return hr;

}

//**********************************************************************
// 
// SetupBindings
// 
// Purpose:
// 
//     Creates bindings that map the data in the rowset's columns to 
//     slots in the consumer's data buffer.
//     
// Parameters:
//
// 	ULONG 			cCol                - number of columns in rowset to bind
// 	DBCOLUMNINFO*	pColumnInfo         - pointer to column metadata
// 	DBBINDING*		rgBind_out          - out pointer through which to return
//                                        an array of binding structures, one
//                                        structure per column bound
// 	ULONG*			pcBind_out          - out pointer through which to return   
//                                        the number of columns bound (number
//                                        of valid elements in rgBind_out)              
// 	ULONG*			pcMaxRowSize_out    - out pointer through which to return
//                                        the buffer size necessary to hold
//                                        the largest row data
// 
// Return Value:
//     S_OK         - Success
//     E_*          - Failure
// 
// Function Calls:
//     Function                    Location
// 
//     assert                      c runtime
// 
//     
// Comments:      
// 
// 
//**********************************************************************
HRESULT SetupBindings
	(
	ULONG 			cCol,
	DBCOLUMNINFO*	pColumnInfo,
	DBBINDING*		rgBind_out,
	ULONG*			pcBind_out,
	ULONG*			pcMaxRowSize_out
	)
{
	#define DEFAULT_CBMAXLENGTH 80	// cbMaxLength for binding
	ULONG dwOffset;				// Length of a Row
	ULONG iCol;					// Column Count
	ULONG iBind;				// Binding Index
	
	// Asserts
    assert(pColumnInfo		!= NULL);
    assert(rgBind_out 		!= NULL);
    assert(pcBind_out 		!= NULL);
    assert(pcMaxRowSize_out != NULL);

   	// Create bindings.
	// Bind everything as a string just to keep things simple.
	dwOffset = 0;
	iBind=0;
	for (iCol=0; iCol < cCol; iCol++)
	{
		// Binding Structure
		rgBind_out[iBind].dwPart	= DBPART_VALUE | DBPART_LENGTH |
									  DBPART_STATUS;
		rgBind_out[iBind].eParamIO  = DBPARAMIO_NOTPARAM;
		rgBind_out[iBind].iOrdinal	= pColumnInfo[iCol].iOrdinal;
		rgBind_out[iBind].wType     = DBTYPE_WSTR;
		rgBind_out[iBind].pTypeInfo = NULL;
		rgBind_out[iBind].obValue   = dwOffset + offsetof(COLUMNDATA,bData);
		rgBind_out[iBind].obLength  = dwOffset + offsetof(COLUMNDATA,dwLength);
		rgBind_out[iBind].obStatus  = dwOffset + offsetof(COLUMNDATA,wStatus);

		// If columns information is a STR, double buffer and 
		// add space for terminator
		if( ((pColumnInfo[iCol].wType == DBTYPE_STR) ||
			 (pColumnInfo[iCol].wType == DBTYPE_WSTR)) && 
			(pColumnInfo[iCol].ulColumnSize != 0xffffffff) )
			rgBind_out[iBind].cbMaxLen = (pColumnInfo[iCol].ulColumnSize + sizeof(CHAR)) * 2;
		else
			rgBind_out[iBind].cbMaxLen = DEFAULT_CBMAXLENGTH;
		rgBind_out[iBind].pObject	= NULL;
		rgBind_out[iBind].pBindExt	= NULL;
		rgBind_out[iBind].dwFlags	= 0;
		rgBind_out[iBind].dwMemOwner = DBMEMOWNER_CLIENTOWNED;
		rgBind_out[iBind].bPrecision = 0;
		rgBind_out[iBind].bScale	= 0;
		
		// LONG DATA hack 
		if(rgBind_out[iBind].cbMaxLen > 1000)
			rgBind_out[iBind].cbMaxLen = 1000;

		dwOffset += rgBind_out[iBind].cbMaxLen + offsetof( COLUMNDATA, bData );
		dwOffset = ROUND_UP( dwOffset, COLUMN_ALIGNVAL );
		iBind++;
	}  

	// Return Values    
	*pcBind_out 	  = iBind;
	*pcMaxRowSize_out = dwOffset;

	return S_OK;
}



//**********************************************************************
// 
// CreateAccessor
// 
// Purpose:
//
//     Passes a set of bindings to the data provider and recieves in return
//     an accessor handle that represents those bindings. 
//      
// Parameters:
// 	IRowset*	pIRowset        - interface pointer on data provider's Rowset
//                                object
// 	DBBINDING*	rgBind          - array of binding structures
// 	ULONG		cBind           - number of binding structures in rgBind
// 	HACCESSOR*	phAccessor_out  - out pointer through which to return an 
//                                accessor handle that represents all the bindings
//                                in rgBind
// 
// Return Value:
//     S_OK        - Success
//     E_*         - Failure
// 
// Function Calls:
//     Function                    Location
// 
//     IRowset::QueryInterface     provider's Rowset object
//     IAccessor::CreateAccessor   provider's Rowset object
//     IAccessor::Release          provider's Rowset object
// 
//     assert                      c runtime
//     
// Comments:      
// 
// 
//**********************************************************************
HRESULT CreateAccessor
	(
	IRowset*	pIRowset,
	DBBINDING*	rgBind,
	ULONG		cBind,
	HACCESSOR*	phAccessor_out 
	)
{
	IAccessor*	pIAccessor = NULL;
	HRESULT 	hr;

	// Asserts
	assert(pIRowset 	  != NULL);
    assert(rgBind 		  != NULL);
    assert(phAccessor_out != NULL);

  	// Get an accessor for our bindings from the rowset, via IAccessor 
	if( FAILED(hr = pIRowset->QueryInterface( IID_IAccessor, (void**)&pIAccessor)) )
	{
		GetDetailedErrorInfo(hr, pIRowset, IID_IRowset, "QI for IAccessor FAILED!!");
		goto error;
	}

	if( FAILED(hr = pIAccessor->CreateAccessor(
						DBACCESSOR_ROWDATA, 
						cBind, 
						rgBind, 
						0, 
						phAccessor_out,
						NULL)) )
	{
		GetDetailedErrorInfo(hr, pIAccessor, IID_IAccessor, "IAccessor->CreateAccessor FAILED!!");
		goto error;
	}

	hr = S_OK;	

error:
	if (pIAccessor)
    	pIAccessor->Release();

	if( FAILED(hr) )
		*phAccessor_out = NULL;
				
	return hr;	
}


//**********************************************************************
// 
// GetData
// 
// Purpose:
// 
//     Reads the data from a rowset.
// 
// Parameters:
//
// 	   IRowset*	 pIRowset           - interface pointer on data provider's
//                                    Rowset object
// 	   ULONG   	 cMaxRowSize        - size of buffer needed to hold the data
//                                    for the largest row
//     HACCESSOR hAccessor          - accessor handle representing the set
//                                    of desired bindings
//     DBBINDING*		rgBind	  	- needed only for pretty printing	
//     ULONG			cBind	  	- for pretty printing  
//     DBCOLUMNINFO*	pColumnInfo - for pretty printing  
//     ULONG			cCol		- for pretty printing  
// 
// 
// Return Value:
//     S_OK        - Success
//     E_*         - Failure
// 
// Function Calls:
//     Function                    Location
// 
//     IRowset::GetNextRows        provider's Rowset object
//     IRowset::GetData            provider's Rowset object
//     IRowset::ReleaseRows        provider's Rowset object
// 
// 
//     malloc, free                c runtime
//     assert                      c runtime
// 
// 
//     
// Comments:      
//
//     GetData reads all the rows in the rowset, sequentially.
//  
// 
//**********************************************************************
HRESULT GetData
	(
	IRowset*		pIRowset,
	ULONG   		cMaxRowSize,
    HACCESSOR   	hAccessor,
    DBBINDING*		rgBind,	  	  
    ULONG			cBind,	  	  
    DBCOLUMNINFO*	pColumnInfo,  
    ULONG			cCol,
	HWND			hList,
	DWORD			dwText,
	DWORD			addString
	)
{
	#define NUMROWS_CHUNK       20	// Number of Rows to Grab at a Time

	ULONG 	cRowsObtained;			// Number of rows obtained
	ULONG	iRow;					// Row Count
	BYTE*	pRowData = NULL;		// Memory for Data
	HROW 	rghRows[NUMROWS_CHUNK];	// Row Handles
	HROW*	pRows = &rghRows[0];	// Pointer to the Row Handles
	ULONG	cMaxColWidth = 0;  		// Needed for Output
	HRESULT hr;						// HRESULT

	// Asserts
	assert(pIRowset 	!= NULL);
    assert(rgBind 		!= NULL);
    assert(pColumnInfo  != NULL);

	// Create a buffer for row data, big enough to hold the biggest row
	pRowData = (BYTE *) malloc( cMaxRowSize );
	if (!pRowData)
        goto error;

    // Process all the rows, NUMROWS_CHUNK rows at a time
	while (1)
	{
		if( FAILED(hr = pIRowset->GetNextRows(
			0,							// cbChapter
			0,							// cRowsToSkip
			NUMROWS_CHUNK,				// cRowsDesired
			&cRowsObtained,				// cRowsObtained
			&pRows)) )					// filled in w/ row handles
		{
	    	GetDetailedErrorInfo(hr, pIRowset, IID_IRowset, "IRowset->GetNextRows FAILED!!");
			goto error;
		}

		// All done, no more rows left to get
		if ( cRowsObtained == 0 )
			break;

		// Loop over rows obtained, getting data for each
		for ( iRow=0; iRow < cRowsObtained; iRow++ )
		{
			if( FAILED(hr = pIRowset->GetData(
				rghRows[iRow],
				hAccessor,
				pRowData)) )
			{
                GetDetailedErrorInfo(hr, pIRowset, IID_IRowset, "IRowset->GetData FAILED!!");
				goto error;
			}

			
			// Print to the Screen
            DumpRow( rgBind, cBind, cMaxColWidth, pRowData, hList, dwText, addString );

			// See if you are over the limit of rows
			if ((iRow + 1) == MAX_ROW)
			{
				wsprintf(szDispBuffer, ROWTRUNC_WARNG, MAX_ROW);
				MessageBox(hWndFrame, szDispBuffer, TRUNCERR, MB_OK | MB_ICONINFORMATION);
				break;
			}

		}

		// Release row handles
		if( FAILED(hr = pIRowset->ReleaseRows( cRowsObtained, rghRows, NULL, NULL, NULL)) )
		{
           GetDetailedErrorInfo(hr, pIRowset, IID_IRowset, "IRowset->ReleaseRows FAILED!!");
		   goto error;
		}

	}	// end while

	hr = S_OK;
error:
	// Set the horizontal scroll extent in the list box and ask for repaint.
	SendMessage(hList, LB_SETHORIZONTALEXTENT, (WPARAM)(cBind*LISTHORZSCROLL+LISTHORZEXT), 0);
	SendMessage(hList, WM_SETREDRAW, TRUE, 0);

	if( cRowsObtained )
		pIRowset->ReleaseRows( cRowsObtained, rghRows, NULL, NULL, NULL);
	
	if( pRowData )
		free( pRowData );
		    					
    return hr;
}

//**********************************************************************
// 
// GetSchemaRowset
// 
// Purpose:
// 
//     Pulls the schema info out of the provider.
//     
// Parameters:
// 
// 	GUID  rguidSchema    	-  SchemaRowset IID
//
//
// Return Value:
// 
// Function Calls:
//     Function                    		  Location
// 
//	   IDBCreateCommand::QueryInterface   QI
//	   IDBSchemaRowset->GetRowset		  Clients Rowset pointer
//     GetDataFromRowset               	  query.cpp
// 
//     IMalloc::Free               		  OLE task memory allocator
// 
//     assert                      		  c runtime
// 
// Comments:      
// 
//       
//**********************************************************************
void FAR PASCAL GetSchemaRowset(GUID rguidSchema)
{
	char				szBuffer[MAXBUFLEN+1];		// String Buffer
	HCURSOR				hOldCursor;					// Default Cursor Handle
	IDBCreateCommand* 	pIDBCreate 		 = NULL;	// IDBCreateCommand Object
	IDBSchemaRowset*	pIDBSchemaRowset = NULL;	// SchemaRowset Object
	ICommand*			pICommand		 = NULL;	// Command Object
	IRowset*			pIRowset		 = NULL;	// Rowset Object
	HRESULT				hr;							// HRESULT

	// Check if there is an active window available
	if( !hWndActiveChild )
	{
		MessageBox( hWndFrame, 
					((SendMessage(hWndCrsrList, CB_GETCOUNT, 0, 0) <=0) ?
					MAKECONNECT : OPENWINDOW ), 
					NOCOMMANDERROR, MB_OK | MB_ICONHAND);
		return;
	}

	// Change cursor shape to hour glass
	hOldCursor = SetCursor(LoadCursor((HINSTANCE)NULL, IDC_WAIT));
        	
	// Scan hdbc, hstmt values
	GetWindowText(hWndActiveChild, (char*)szBuffer, MAXBUFLEN);
	sscanf(szBuffer, SCANSESSIONCOMMAND_FORMAT, &pIDBCreate, &pICommand);
	
	// QueryInterface for IDBSession::IDBSchemaRowset
	hr = pIDBCreate->QueryInterface( IID_IDBSchemaRowset,
									(LPVOID*)&pIDBSchemaRowset );

	if (FAILED(hr))
	{
        GetDetailedErrorInfo(hr, pIDBCreate, IID_IDBCreateCommand, "QI for IDBScemaRowset FAILED!!");
		goto error;
	}
	
	// Get a SchemaRowset back
	hr = pIDBSchemaRowset->GetRowset(
							NULL,						// punkOuter
							rguidSchema,				// schema IID
							0L,							// # of restrictions
							NULL,						// array of restrictions
							IID_IRowset,				// rowset interface
							0L,							// # of properties
							NULL,						// properties
							(IUnknown**)&pIRowset);		// rowset pointer

	if (FAILED(hr))
	{
        GetDetailedErrorInfo(hr, pIDBSchemaRowset, IID_IDBSchemaRowset, "IDBSchemaRowset->GetRowset FAILED!!");
		goto error;
	}

	// Get Data from the IRowset Object
	hr = GetDataFromRowset( pIRowset );

	if (FAILED(hr))
	{
//		DumpErrorHResult( hr, (LPSTR)"GetDataFromRowset returned error!!" );
		goto error;
	}

	// Release Object
	pIDBSchemaRowset->Release();
    pIDBSchemaRowset = NULL;
	
	return;

error:    
	if( pIDBSchemaRowset )
		pIDBSchemaRowset->Release();
	
	return;
}


//**********************************************************************
// 
// CleanupRowset
// 
// Purpose:
//
//     Allows the rowset to perform any necessary cleanup.
//  
// Parameters:
//
// 	IRowset*	pIRowset    - interface pointer on data provider's Rowset
//                            object
// 	HACCESSOR 	hAccessor   - accessor handle to release
// 
// Return Value:
//
//     S_OK        - Success
//     E_*         - Failure
//     
// Function Calls:
//     Function                    Location
// 
//     IRowset::QueryInterface     provider's Rowset object
//     IAccessor::ReleaseAccessor  provider's Rowset object
//     IAccessor::Release          provider's Rowset object
// 
//     assert                      c runtime
// 
//     
// Comments:      
//
//     In this sample, the only cleanup that the rowset needs to do is
//     release the accessor handle. 
// 
//**********************************************************************
HRESULT CleanupRowset
	(
	IRowset*	pIRowset,
	HACCESSOR 	hAccessor
	)
{
	IAccessor*	pIAccessor = NULL;	// Pointer to an Accessor
	HRESULT		hr;					// HRESULT

	// Assert    
    assert(pIRowset != NULL);
    
	if( hAccessor )
	{
		// Tell the rowset object it can release the accessor, via IAccessor
		hr = pIRowset->QueryInterface( IID_IAccessor, (void**)&pIAccessor );

		if (FAILED(hr))
		{
			GetDetailedErrorInfo(hr, pIRowset, IID_IRowset, "QI for IAccessor FAILED!!");
			goto error;
		}

		hr = pIAccessor->ReleaseAccessor( hAccessor, NULL );
		if (FAILED(hr))
		{
			GetDetailedErrorInfo(hr, pIAccessor, IID_IAccessor, "IAccessor->ReleaseAccessor FAILED!!");
			goto error;
		}

		pIAccessor->Release();
		pIAccessor = NULL;
	}

	pIRowset->Release();
	pIRowset = NULL;

	return S_OK;
    
error:    
	if( pIAccessor )
    	pIAccessor->Release();
	if( pIRowset )
		pIRowset->Release();

    return hr;    
}


//**********************************************************************
// 
// DumpRow
// 
// Purpose:
//
//     Display the row to the screen.
//  
// Parameters:
//
// 
// Return Value:
//
//     
// Function Calls:
//     Function                    Location
// 
//     assert                      c runtime
// 
//     
// Comments:      
//
// 
//**********************************************************************
void DumpRow
	(
    DBBINDING* 	rgBind,
    ULONG		cBind,
    ULONG		cMaxColWidth,
    BYTE* 		pData,
	HWND		hList,
	DWORD		dwText,
	DWORD		addString
    )
{
	ULONG 		iBind;			// Binding Count
    COLUMNDATA*	pColumn;		// Data Structure
	int			cb;
	CHAR		szTempString[MAXDISPLAYSIZE+10];	// Temporary Display Buffer, used to check data length

	// Asserts
	assert(rgBind);
	assert( offsetof(COLUMNDATA, wStatus) == 0);	
    
	// Print each column we're bound to.
	for (iBind=0, szDispBuffer[0]='\0'; iBind < cBind; iBind++)
	{
		// Columns are bound differently; not so easy.
		// Print out to at least DEFAULT_CBMAXLENGTH width (pretty),
		// Limit to first dwLength characters.
		pColumn = (COLUMNDATA *) (pData + rgBind[iBind].obStatus);
		
		// Check Status for NULL / OK / CANTCONVERT.
		switch (pColumn->wStatus)
		{
			case DBSTATUS_S_ISNULL:
				strcat(szDispBuffer, (LPSTR)"<NULL>");
				break;
			case DBSTATUS_S_OK:
			case DBSTATUS_S_TRUNCATED:
				// Truncate if needed.
				// - calculate number of bytes needed
				cb = WideCharToMultiByte(CP_ACP, 0, (LPWSTR)pColumn->bData, -1,
							NULL, 0, NULL, NULL);
				if( cb > MAXCOLNDATALENGTH )
				{
					cb = WideCharToMultiByte(CP_ACP, 0, (LPWSTR)pColumn->bData, -1,
						szTempString, MAXCOLNDATALENGTH, NULL, NULL);
					
					szTempString[MAXCOLNDATALENGTH] = '\0';  
					strcat(szTempString, "...");
				}
				else
				{
					cb = WideCharToMultiByte(CP_ACP, 0, (LPWSTR)pColumn->bData, -1,
						szTempString, (MAXDISPLAYSIZE+1), NULL, NULL);
				}

				if(pColumn->wStatus == DBSTATUS_S_TRUNCATED)
					strcat(szTempString, "...");
				strcat(szDispBuffer,szTempString);
		        break;

			case DBSTATUS_E_CANTCONVERTVALUE:
				strcat(szDispBuffer, "<can't convert value>");
				break;
			default:
				{
				CHAR szChar[10] = "";
				strcat(szDispBuffer, "<unknown status of ");
				strcat(szDispBuffer, itoa(pColumn->wStatus, szChar, 10));
				strcat(szDispBuffer, ">");
				}
				break;
		}

		dwText = strlen(szDispBuffer);
		szDispBuffer[dwText++] = '\t';
		szDispBuffer[dwText] = '\0';
	}
	// Take the last \t off the end
	szDispBuffer[--dwText] = '\0';
	SendMessage(hList, addString, 0, (LPARAM)(LPSTR)szDispBuffer);

}    

//**********************************************************************
// 
// GetDetailedErrorInfo
// 
// Purpose:
//
//    Reads error from the error collection and displays it in messageboxes
//  
// Parameters:
//
// 	HRESULT		hr					- OLE DB HRESULT
// 	IUnknown	*  pBadObject       - Object that caused an error
//  GUID		IID_BadInterface    - Interface that contains method that caused the error
// 	LPSTR	 	lpStrBuffer			- Title Bar text
//
// Return Value:
//     
// Comments:      
//	 If any sort of failure is encountered the return values will be NULL
//   strings. Therefore no extended error info will be printed.
//**********************************************************************

HRESULT GetDetailedErrorInfo 
    (
	HRESULT		hresult, 
	IUnknown	*pBadObject,                  
	GUID		IID_BadIntereface,                 
	LPSTR		lpStrBuffer
	)
{
	IErrorInfo *        pErrorInfo = NULL; 
	IErrorInfo *	    pErrorInfoRec = NULL;
	IErrorRecords *     pErrorRecords = NULL;
	ISupportErrorInfo * pSupportErrorInfo = NULL;
	HRESULT             hr = S_OK;
	ULONG               i,ulNumErrorRecs;
	BSTR				bstrDescriptionOfError = NULL;
	BSTR				bstrSourceOfError = NULL;
	CHAR                szBuffer [512];  //Error Info Buffer
   
	// Check to see if this interface posts error messages
	if( SUCCEEDED( pBadObject->QueryInterface(IID_ISupportErrorInfo, 
		(LPVOID FAR*)&pSupportErrorInfo)) ) 
	{
		if( pSupportErrorInfo->InterfaceSupportsErrorInfo(IID_BadIntereface) == S_OK )
		{
			//Get Error Object. Return if no object Exists
			if( !SUCCEEDED(hr = GetErrorInfo(0,&pErrorInfo)) )
			   goto DisplayHResult;

			// If returned a NULL error Object, then just display HR
			if( pErrorInfo == NULL )
				goto DisplayHResult;

			//Get the IErrorRecord interface and get the count of error recs.
			if( FAILED(hr = pErrorInfo->QueryInterface(IID_IErrorRecords,(LPVOID FAR*)&pErrorRecords)) )
			   goto DisplayHResult;

			//Retrieve the number of Error Records
			if( FAILED(hr = pErrorRecords->GetRecordCount(&ulNumErrorRecs)) )
			   goto DisplayHResult;

			//Go through and print messages
			for(i=0; i<ulNumErrorRecs; i++) 
			{
				if( FAILED(hr = pErrorRecords->GetErrorInfo(i, GetUserDefaultLCID(), &pErrorInfoRec)) )
					goto Exit;
				if( FAILED(hr = pErrorInfoRec->GetDescription(&bstrDescriptionOfError)) )
					goto Exit;
				if( FAILED(hr = pErrorInfoRec->GetSource(&bstrSourceOfError)) )
					goto Exit;

				sprintf(szBuffer, "HResult of 0x%0x (%ld) returned\nError Source: %S\nError Description: %S\n", 
					(long)hresult,(long)hresult, 
					bstrSourceOfError ? bstrSourceOfError : L"No Source Description",
					bstrDescriptionOfError ? bstrDescriptionOfError : L"No Error Description");

				MessageBox( NULL, (LPCTSTR)szBuffer, lpStrBuffer, MB_OK);

				if (pErrorInfoRec) 			   
				{
					pErrorInfoRec->Release();
					pErrorInfoRec = NULL;
				}
				if( bstrSourceOfError )
				{
					SysFreeString(bstrSourceOfError);
					bstrSourceOfError = NULL;
				}
				if( bstrDescriptionOfError )
				{
					SysFreeString(bstrDescriptionOfError);
					bstrDescriptionOfError = NULL;
				}
			}
			
			// if we've process all the records we can go to end
			goto Exit;

		} //S_OK
	} //if (SUCCEEDED)

DisplayHResult:
	// In some error cases we may not have extended error information and it still would be good to
	// post the error HRESULT
	sprintf(szBuffer, "HResult of 0x%0x (%ld) returned, no Extended Error Information posted or supported", 
		(long)hresult,(long)hresult);
	MessageBox( NULL, (LPCTSTR)szBuffer, lpStrBuffer, MB_OK);

 Exit : 
	if (pErrorInfo)
		pErrorInfo->Release();
	if (pErrorRecords)
		pErrorRecords->Release();
	if( pSupportErrorInfo )
		pSupportErrorInfo->Release();
	if( pErrorInfoRec )
		pErrorInfoRec->Release();
	if( bstrSourceOfError )
		SysFreeString(bstrSourceOfError);
	if( bstrDescriptionOfError )
		SysFreeString(bstrDescriptionOfError);

 return hr;
} //PrintErrorInfo


//**********************************************************************
// 
// DumpErrorHResult
// 
// Purpose:
//
//     Dump the OLE DB HRESULT in a Message Box with a text Title Bar.
//  
// Parameters:
//
// 	HRESULT		hr		    - OLE DB HRESULT
//
// 	LPSTR	 	lpStrBuffer - Title Bar text
//
// 
// Return Value:
//
//     
// Function Calls:
//     Function                    Location
// 
//     assert                      c runtime
// 
//     
// Comments:      
//
// 
//**********************************************************************
void DumpErrorHResult( HRESULT hr, 	LPSTR lpStrBuffer )
{
	LPVOID	lpMessageBuffer;

	if(0 != FormatMessage(FORMAT_MESSAGE_ALLOCATE_BUFFER |
				FORMAT_MESSAGE_FROM_SYSTEM,
				NULL,
				hr,
				GetUserDefaultLCID(),
				(LPSTR)&lpMessageBuffer,
				0,
				NULL))
	{
		MessageBox( NULL, (LPCTSTR)lpMessageBuffer, lpStrBuffer, MB_OK);
		LocalFree(lpMessageBuffer);
	}
	else
	{
		lpMessageBuffer = LocalAlloc(LPTR, 256);

		if( lpMessageBuffer )
		{
			sprintf((LPSTR)lpMessageBuffer, "HResult of %ld returned", (long)hr);
			MessageBox( NULL, (LPCTSTR)lpMessageBuffer, lpStrBuffer, MB_OK);
			LocalFree(lpMessageBuffer);
		}
	}
}

//**********************************************************************
// 
// NewIOpenRowsetWindow
// 
// Purpose:
// 
//     Create a new ICommand Object on the current IDBCreateCommand.
//     
// Parameters:
// 
// Return Value:
// 
// Function Calls:
//     Function                         Location
// 
//	   IDBCreateCommand::CreateCommand	provider's Command object
//     ICommand::Release                provider's Command object
// 	   
//     
// Comments:      
// 
// 
//**********************************************************************
void FAR PASCAL NewIOpenRowsetWindow()
{
	int 				nCurrenthdbc;			// Current PROVIDER
	char				szBuffer[MAXBUFLEN+1];	// String in PROVIDER ComboBox on Toolbar
	char				szProvName[MAXBUFLEN+1];// DSN String
	MDICREATESTRUCT		mcs;                    // MDI Child Window Create Struc
	
	IOpenRowset * 		pIOpenRowset= NULL;		// IOpenRowset Object

        
	// check if there is PROVIDER selected in the Combo-Box
	if ((nCurrenthdbc = (int)SendMessage(hWndCrsrList, CB_GETCURSEL, 0, 0)) == CB_ERR)
	{
		MessageBox(hWndFrame, MAKECONNECT, NOSESSIONERROR, MB_OK | MB_ICONHAND);
		return;
	}
	
	// check if the number of windows exceeds MAXCHILDWNDS
	if (nChildCount >= MAXCHILDWNDS)
	{
		MessageBox(hWndFrame, MAXCHILDEXCEEDED, MAXCHLDERR, MB_OK | MB_ICONHAND);
		return;
	}

	// Scan PROVIDER string and IDBCreateCommand value from the combo-box
	SendMessage(hWndCrsrList, CB_GETLBTEXT, (WPARAM)nCurrenthdbc, (LPARAM)(LPSTR)szBuffer);
	
 	sscanf(szBuffer, SCANPROVIDERSESSION_FORMAT, szProvName, &pIOpenRowset);

	// create a new MDI client window. maximized, if the previous is so.
	mcs.szClass = OLEDBMDICLASS;
	mcs.szTitle = UNTITLED;
	mcs.hOwner  = hAppInstance;
	mcs.style   = hWndActiveChild && IsZoomed(hWndActiveChild) ? WS_MAXIMIZE : 0;
	mcs.x = mcs.cx = mcs.y = mcs.cy = CW_USEDEFAULT;
	hWndActiveChild = (HWND)(UINT)SendMessage(hWndMDIClient, WM_MDICREATE, 0, (LPARAM)(LPMDICREATESTRUCT)&mcs);
        
    // check if it was created, if it wasn't free up resource and flag warning
    if (!hWndActiveChild)
    {
		MessageBox(hWndFrame, CREATECHILDERR, EXECERROR, MB_OK|MB_ICONEXCLAMATION|MB_TASKMODAL);
		return;
    }
        
	// Display the Provider string, PROVIDER and IOpenRowset in the title
	// of newly created window. Increment the child window counter
	wsprintf(szBuffer, QUERY_STRING, pIOpenRowset);
		
	SendMessage(hWndStmtList, CB_ADDSTRING, 0, (LPARAM)(LPSTR)szBuffer);
	SendMessage(hWndStmtList, CB_SELECTSTRING, 0, (LPARAM)(LPSTR)szBuffer);
	
	wsprintf(szBuffer, PROVIDER_SESSION_COMMAND_FORMAT, (LPSTR)szProvName, pIOpenRowset, NULL);
	
	SetWindowText(hWndActiveChild, szBuffer);
	nChildCount++;
	
	// Update the Command Combo-Box on the tool bar.
	ChangeCurrentICommand(hWndStmtList);
}




