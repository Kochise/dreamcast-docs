// ====================================================================
//
//  File: enumobj.cpp
//
//  Copyright (c) 1996 Microsoft Corp.
//
//  Author:
//      Jonathan Shuval     Microsoft Corp.
//
//  Sample program for illustrating use of the SMS object enumeration
//  APIs.
//
//
// ====================================================================


// ====================================================================
//
//      Includes
//
// ====================================================================
#include <afx.h>
#include <smsapi.h>


// Include the GetStatusName function.
// -------------------------------------
#include "..\common\status.inc"

// ====================================================================
//
//      Defines.
//
// ====================================================================
#define CCH_MAXINPUT 256


// ====================================================================
//
//      Prototypes.
//
// ====================================================================

// Display an error message with its SMS status value.
// -------------------------------------------------------------
void DisplaySmsError( const char *pszMessage, SMS_STATUS stat );


// Connect to the SMS datasource.
// -------------------------------------------------------------
HANDLE ConnectToDatasource();


// Do the real enumerate, recursive.
// -------------------------------------------------------------
void enumObj( HANDLE hConnect,
              SMSBUFF *pPreds,
              DWORD ctPreds,
              char *pszObj,
              int iIndent );


// Prompt the user for input and return the reply.
// -------------------------------------------------------------
void InputString( const char *pszMessage, char *pszResult );



// ====================================================================
//
//      Globals.
//
// ====================================================================
// None.




// ====================================================================
//
//      Start here.
//
// ====================================================================

void main()
{



    // Get and display the SMS API version.
    // ------------------------------------
    char *pszVersion;                   // Receives pointer to the version string.
    SmsAPIVer( &pszVersion );           // Get version
    printf("Using %s\n", pszVersion);   // and print it.


    SMS_STATUS stat;
    DWORD dwLoop;


    //===========================================
    // Connect to the SMS datasource.
    //===========================================
    HANDLE hConnect;
    hConnect = ConnectToDatasource();

    if (hConnect == NULL) {
        return;
    }


    // Get the first-class objects.
    // ============================
    SMSBUFF ObjectTypes[10];
    DWORD ctObjectTypes = 10;

    stat = SmsEnumObjectTypes( hConnect, ObjectTypes, &ctObjectTypes );

    if (stat != SMS_OK) {
        printf("EnumObjectTypes fails: %d\n", stat);
        return;
    }

    printf("There are %d object types...\n", ctObjectTypes);
    for (dwLoop = 0; dwLoop < ctObjectTypes; dwLoop++) {
        printf("\t%s\n", ObjectTypes[dwLoop]);
    }
    printf("\n\n");



    // Now loop for each object type
    // =============================

    for (dwLoop = 0; dwLoop < ctObjectTypes; dwLoop++) {
        printf("\n[%d] Enumerating %s...\n", dwLoop, ObjectTypes[dwLoop]);


        SMSBUFF Predecessors[50];
        DWORD ctPreds = 0;

        enumObj( hConnect, Predecessors, ctPreds, ObjectTypes[dwLoop], 1 );

    }


    printf("**** All done ****\n\n");

    SmsDataSourceDisconnect( hConnect );

}




// ====================================================================
// enumObj
//
//
//
//
// Parameters:
//      HANDLE hConnect         Handle to the connection.
//      SMSBUFF *pPreds         Pointer to the predecessor list.
//      DWORD ctPreds           Number of entries in the predecessor list.
//                              Note: this is not the size of the list,
//                              it is the number of entries that are
//                              filled in in the list.
//      char *pszObj            Name of object to enumerate.
//      int iIndent             Indent level. Just so we can display things
//                              nicely.
//
// Returns;
//      Nothing.
//
// NOTE: assumes that predecessor buffer is big enough.
// ====================================================================
void enumObj( HANDLE hConnect,
              SMSBUFF *pPreds,
              DWORD ctPreds,
              char *pszObj,
              int iIndent )
{
    OBJDESCRIPTOR Objects[50];      // Filled in by the API. Contains
                                    // descriptions of each object.
    DWORD ctObjs = 50;
    SMS_STATUS stat;
    char *pszObjType;               // We display the object type.

    // Leading spaces for indentation. Just so that the display looks ok.
    // ------------------------------------------------------------------
    char szIndent[50];
    szIndent[0] = '\0';
    for (int i = 0; i < iIndent; i++) {
        strcat(szIndent, "    ");
    }


    stat = SmsEnumObjects( hConnect, pszObj, pPreds, ctPreds, Objects, &ctObjs );
    if (stat == SMS_NO_MORE_DATA) {
        return;             // Just means we've finished enumerating this one.
    }
    if (stat != SMS_OK) {
        DisplaySmsError("Bad return from EnumObjects", stat);
        return;
    }


    // Add each object from our returned buffer into the
    // predecessor list and recurse.
    // =================================================
    for (DWORD dwLoop = 0; dwLoop < ctObjs; dwLoop++) {

        // Print out the current object.
        // -----------------------------
        printf("%s%-25s", szIndent, Objects[dwLoop].szName);

        // If we've got a friendly name print it.
        // --------------------------------------
        if (Objects[dwLoop].bGotFriendlyName) {
            printf(" <%s>", Objects[dwLoop].szFriendlyName);
        }

        // If this is an attribute we'll have its range of
        // relational operators.
        // -----------------------------------------------
        if (Objects[dwLoop].bGotRelops) {
            printf(" ['%s' to '%s']",
                OpName[Objects[dwLoop].dwRelopMin],
                OpName[Objects[dwLoop].dwRelopMax]);
        }
        printf("\n");

        // Print object type.
        // ------------------
        switch (Objects[dwLoop].objType) {
        case OT_ARCHLIST:
            pszObjType = "Architecture list";
            break;

        case OT_ARCH:
            pszObjType = "Architecture";
            break;

        case OT_GROUP:
            pszObjType = "Group";
            break;

        case OT_ATTRIBUTE:
            pszObjType = "Attribute";
            break;


        case OT_PLATFORMS:
            pszObjType = "Platform list";
            break;

        case OT_PLATFORM_PDF:
            pszObjType = "PDF Platform";
            break;

        case OT_PLATFORM_WINST:
            pszObjType = "Winst platform";
            break;

        case OT_PLATFORM_NAD:
            pszObjType = "NAD platform";
            break;


        case OT_UNKNOWN:
            pszObjType = "Unknown";
            break;

        }
        printf("%sThis is a: %s\n", szIndent, pszObjType );


        // Recurse to get descendents.
        // ---------------------------
        strcpy( pPreds[ctPreds], pszObj );      // Add current object to pred list
        enumObj( hConnect, pPreds, ctPreds+1, Objects[dwLoop].szName, iIndent+1 );

    }

}





// ====================================================================
// InputString
//
// Prompt the user to input a string and return the string in the
// specified buffer.
//
// Parameters:
//      const char* pszMessage
//          The user prompt to display.
//
//      char* pszResult
//          Pointer to the buffer where the user's input will be returned.
//
// Returns;
//      The user's input is returned via the given buffer.
//
// ====================================================================
void InputString( const char *pszMessage, char *pszResult)
{
    printf("%s: ", pszMessage);
    gets(pszResult);
}


// ====================================================================
//
// ConnectToDatasource
//
// Get the datasource connection information from the user and use it
// to connect to the datasource.
//
// Parameters:  None.
//
// Returns:
//      The connection handle or NULL if the connection failed.
//
// ====================================================================
HANDLE ConnectToDatasource()
{
    // Get the information we need to connect to the
    // data source from the user.
    //==============================================
    char szServer[CCH_MAXINPUT];
    char szUser[CCH_MAXINPUT];
    char szPasswd[CCH_MAXINPUT];
    char szDatabase[CCH_MAXINPUT];

    printf("\n");
    printf("**************************\n");
    printf("* Connect to data source *\n");
    printf("**************************\n");
    InputString("SQL server name", szServer);
    InputString("SQL database name", szDatabase);
    InputString("User name for SQL server", szUser);
    InputString("Password for SQL server", szPasswd);
    printf("\n");


    // Connect to a data source. SQL in this case.
    // ===========================================
    DATASOURCE dsParams;

    dsParams.sqlParams.ds          = DB_SQL;
    dsParams.sqlParams.pszServer   = szServer;
    dsParams.sqlParams.pszUserName = szUser;
    dsParams.sqlParams.pszPasswd   = szPasswd;
    dsParams.sqlParams.pszDbName   = szDatabase;
    dsParams.sqlParams.pFunc       = NULL;         // No encryption.
    dsParams.sqlParams.pszKey      = "";

    HANDLE hConnect;
    SMS_STATUS stat;
    stat = SmsDataSourceConnect( &dsParams, &hConnect);

    if (stat != SMS_OK) {
        hConnect = NULL;
        DisplaySmsError("Connect to data source failed", stat);
    }

    return( hConnect );
}



/* EOF: enumobj.cpp */

