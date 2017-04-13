// ====================================================================
//
//  File: pdf.cpp
//
//  Copyright (C) 1996 Microsoft Corp.
//
//  Author:
//      Jonathan Shuval     Microsoft Corp.
//
//  This program illustrates how to import a pdf file into SMS using
//  the SMS API set.
//
//  This sample is referenced in the Back Office documentation for SMS
//
// ====================================================================


#define PDF_NO_ERROR                0
#define PDF_ERROR                   1
#define PDF_ERROR_FILENOTFOUND      2
#define PDF_ERROR_NOTPDF            3
#define PDF_ERROR_VERSION           4
#define PDF_ERROR_MISSINGINFO       5

#define FILE_VERSION_PDF            "1.0"

// ====================================================================
//
//  Includes.
//
// ====================================================================
#include <afx.h>
#include <smsapi.h>             // Header for the APIs.

// Include the GetStatusName and DisplaySmsEror functions.
// -------------------------------------------------------
#include "..\common\status.inc"


// ====================================================================
//  Defines.
// ====================================================================
#define CCH_MAXINPUT    256
#define MAX_BUF         2048    // Max local buf size.
                                // No key info can exceed this.

// ====================================================================
//  Globals
// ====================================================================
CString gsFilename;             // PDF filename.
CString gsWorkingPath;          // Directory containing PDF file.


// ====================================================================
//
//  Local prototypes.
//
// ====================================================================

// Connect to the SMS datasource.
// -------------------------------------------------------------
HANDLE ConnectToDatasource();


// Display the help message.
// -------------------------------------------------------------
void DisplayHelp();


// Display the greeting.
// -------------------------------------------------------------
void DisplayGreeting();


// Check if there was a request for help on the command line.
// -------------------------------------------------------------
BOOL DidRequestHelp( int argc, char **argv );


// Display an error message with its SMS status value.
// -------------------------------------------------------------
void DisplaySmsError( const char *pszMessage, SMS_STATUS stat );


// Get the string equivalence for an SMS status code.
// -------------------------------------------------------------
const char *GetStatusName( SMS_STATUS stat );


// Prompt the user for input and return the reply.
// -------------------------------------------------------------
void InputString( const char *pszMessage, char *pszResult );


// Set the value of string and integer scalars.
// -------------------------------------------------------------
void SetScalarString(HANDLE hFolder, char *pszName, const char *pszValue);
void SetScalarInt(HANDLE hFolder, char *pszName, DWORD dwValue);


// Display specified folder (and sub-folders).
// -------------------------------------------------------------
void ViewFolder( HANDLE hFolder );


// Display a folder's scalars.
// -------------------------------------------------------------
void DisplayScalars( HANDLE hFolder );



// Decomposes string of comma-separated platforms into bit field.
// -------------------------------------------------------------
DWORD GetPlatforms( char *buf );


// Controlling function. Calls workers to parse the pdf and
// create the folder(s).
// -------------------------------------------------------------
DWORD Import( HANDLE hConnect, HANDLE hContainer, const char *pPathToPDF);


// Parse basic package identification info.
// -------------------------------------------------------------
DWORD ParsePackageDef( HANDLE hPkgFolder );


// Parse properties for program items.
// -------------------------------------------------------------
DWORD ParseProgramItemProperties( HANDLE hPkgFolder );


// Parse properties for setup variations.
// -------------------------------------------------------------
DWORD ParseSetupVariations( HANDLE hPkgFolder );


// Parse properties for setup for sharing.
// -------------------------------------------------------------
DWORD ParseSetupForSharing( HANDLE hPkgFolder );


// Functions for parsing inventory rules.
// -------------------------------------------------------------
DWORD ParseInventoryRules( HANDLE hPkgFolder );
void FillFileTokens(TOKEN *pToken, char *pszBuf );


// Test if specified file exists.
// -------------------------------------------------------------
BOOL FileExists(const char *pszPath);


// Initialise the (global) platform aray. This contains
// CPlatform objects each of which contains a string form of the
// platform name and a binary value to be used when setting the
// platforms scalar.
// -------------------------------------------------------------
void InitPlatforms();





// ====================================================================
//  The work starts here.
// ====================================================================

void main( int argc, char **argv )
{
    // Check to see if this is a request to display the help
    // screen. If so, display it. Otherwise, display a greeting
    // banner.
    // =========================================================
    if (DidRequestHelp(argc, argv)) {
        DisplayHelp();
        return;
    }
    else {
        DisplayGreeting();
    }


    SMS_STATUS stat;                    // Return from the APIs.
    HANDLE hConnect;                    // Connection handle.
    HANDLE hContainer;                  // Handle to a container.


    // Get and display the SMS API version.
    // ------------------------------------
    char *pszVersion;                   // Receives pointer to version string.
    SmsAPIVer( &pszVersion );           // Get version
    printf("Using %s\n", pszVersion);   // and print it.


    //===========================================
    // Connect to the SMS datasource.
    //===========================================
    hConnect = ConnectToDatasource();
    if (hConnect == NULL) {
        return;
    }

    //===========================================
    // Get the pdf file name and validate it.
    //===========================================
	char szPDF[128];

	if(argc == 2)
	{
		// Assume pdf file on command line
		strcpy(szPDF, argv[1]);
		printf("Using pdf file : %s\n",szPDF);
	}
	else
	{
		InputString("PDF file name", szPDF);
	}

    if (!FileExists( szPDF )) {
        printf("Can't find pdf file: %s\n", szPDF);
		printf("Make sure it's in the current directory\n");
        SmsDataSourceDisconnect( hConnect );
        return;
    }

    // Open package container.
    // ========================
    stat = SmsOpenContainer( C_PACKAGE, hConnect, &hContainer );
    if (stat != SMS_OK) {
        DisplaySmsError("SmsOpenContainer failed", stat);
        SmsDataSourceDisconnect( hConnect );
        return;
    }

    // Does the work.
    // ==============
    DWORD dwRet = Import( hConnect, hContainer, szPDF );
    if (dwRet != 0) {
        printf("Error %d, file not processed\n", dwRet);
    }

    // Close everything.
    // =================
    SmsCloseContainer( hContainer );
    SmsDataSourceDisconnect( hConnect );

}



//*************************************************************************
//
//  Import()
//
//  Imports a PDF and initializes the member object pointed to by
//  <pPackage>.  This function calls other lower level parsing functions.
//
//  Parameters:
//      HANDLE hConnect                     Connection handle.
//      HANDLE hContainer                   Container handle.
//      const char *pPathToPDF              Path to the PDF file.
//
//
//  Returns:
//
//      DWORD                               0 on success, or a specific
//                                          error code.
//
//*************************************************************************
DWORD Import( HANDLE hConnect, HANDLE hContainer, const char *pPathToPDF )
{
    gsFilename = pPathToPDF;        // Hold globally as CString.


    // Compute the working directory/path based on analysis
    // of the filename.
    // ====================================================

    int iLastSlash = gsFilename.ReverseFind('\\');

    if (iLastSlash != -1) {
        gsWorkingPath = gsFilename.Left(iLastSlash) + "\\";
    }

    // Create a package folder.
    // ========================
    SMS_STATUS stat;
    HANDLE hPkgFolder;
    stat = SmsCreateFolder( hContainer, F_PACKAGE, "", &hPkgFolder );
    if (stat != SMS_OK) {
        DisplaySmsError("SmsCreateFolder (package) failed", stat);
        return(PDF_ERROR);
    }

    // Initialise the platforms array.
    // ===============================
    InitPlatforms();


    // Start working.
    // ==============

    DWORD dwRet = PDF_NO_ERROR;

    dwRet = ParsePackageDef( hPkgFolder );
    if (dwRet != 0) {
        printf("ParsePackageDef failed: %d\n", dwRet);
        return(dwRet);
    }

    dwRet = ParseSetupVariations( hPkgFolder );
    if (dwRet != 0) {
        printf("ParseSetupVariations failed: %d\n", dwRet);
        return(dwRet);
    }

    dwRet = ParseSetupForSharing( hPkgFolder );
    if (dwRet != 0) {
        printf("ParseSetupForSharing failed: %d\n", dwRet);
        return(dwRet);
    }

    dwRet = ParseProgramItemProperties( hPkgFolder );
    if (dwRet != 0) {
        printf("ParseProgramItemProperties failed: %d\n", dwRet);
        return(dwRet);
    }

    dwRet = ParseInventoryRules( hPkgFolder );
    if (dwRet != 0) {
        printf("ParseInventoryRules failed: %d\n", dwRet);
        return(dwRet);
    }


    // If we got this far then everything must have been ok.
    // We can link and commit the folder.
    // =====================================================
    stat = SmsLinkFolder( hPkgFolder );
    if (stat != SMS_OK) {
        DisplaySmsError("SmsLinkFolder for package failed", stat);
        return(PDF_ERROR);
    }
    stat = SmsCommitFolder( hPkgFolder );
    if (stat != SMS_OK) {
        DisplaySmsError("SmsCommitFolder for package failed", stat);
        return(PDF_ERROR);
    }
    // Display the folder.
    // ===================
    printf("This is what the folder looks like:\n");
    ViewFolder( hPkgFolder );


    return(dwRet);
}





//***************************************************************************
//
//  ParsePackageDef
//
//  Parses out basic package identification info.
//
//  Parameters:
//      HANDLE hPkgFolder               Folder to newly created package
//                                      folder.
//  Returns:
//      DWORD                           0 on success or a PDF_ error code.
//
//***************************************************************************
DWORD ParsePackageDef( HANDLE hPkgFolder )
{
    CString sWork;
    char *pszTmp = new char[MAX_BUF];
    char szBuff[MAX_BUF];
    DWORD dwCheck = 0;
    DWORD dwRet = PDF_ERROR;
	CString sDirectory;
	char sDirBuff[MAX_BUF];

	if(!GetCurrentDirectory(MAX_BUF, 
							sDirBuff))
	{
		dwRet = PDF_ERROR_FILENOTFOUND;
		goto Exit;	
	}

	sDirectory = sDirBuff;
	sDirectory += '\\';
	gsFilename = sDirectory + gsFilename;

    // Verify file exists.
    // ===================

    if (!FileExists((const char *)gsFilename)) {
        dwRet = PDF_ERROR_FILENOTFOUND;
        goto Exit;
    }

    // Verify we have a PDF of the correct version.
    // ============================================

    dwCheck = GetPrivateProfileString(  "PDF",
                                        "Version",
                                        "",
                                        pszTmp,
                                        MAX_BUF,
                                        gsFilename);

    if (!dwCheck) {
        printf("This file is not a valid PDF file.\n");
        dwRet = PDF_ERROR_NOTPDF;
        goto Exit;
    }

    if (_strnicmp(pszTmp, FILE_VERSION_PDF, strlen(FILE_VERSION_PDF)) != 0) {
        printf("\n");
        printf("This file does not have the correct PDF version.\n");
        printf("Acceptable PDF version is %s\n", FILE_VERSION_PDF);
        dwRet = PDF_ERROR_VERSION;
        goto Exit;
    }

    // [Package Definition]
    // ====================

    // Product
    // =======

    dwCheck = GetPrivateProfileString(  "Package Definition",
                                        "Product",
                                        "",
                                        pszTmp,
                                        MAX_BUF,
                                        gsFilename);

    if (!dwCheck) {
        dwRet = PDF_ERROR_MISSINGINFO;
        goto Exit;
    }

    sWork = pszTmp;
    sWork += " ";

    // Version
    // =======

    GetPrivateProfileString("Package Definition",
                            "Version",
                            "",
                            pszTmp,
                            MAX_BUF,
                            gsFilename);

    sWork += pszTmp;  // product + version

    SetScalarString( hPkgFolder, "Name", (const char *)sWork);

    // Comment
    // =======

    GetPrivateProfileString("Package Definition",
                            "Comment",
                            "",
                            pszTmp,
                            MAX_BUF,
                            gsFilename);

    SetScalarString( hPkgFolder, "Comment", pszTmp );



    // Source directory for Workstations.
    // If it's not in the pdf ask the user for it. It's mandatory.
    // ===========================================================
    GetPrivateProfileString("Package Definition",
                            "ImportDirectory",
                            "",
                            pszTmp,
                            MAX_BUF,
                            gsFilename);
    if (strlen(pszTmp) == 0) {
        printf("\n");
        printf("If this package is destined to be set up for workstations\n");
        printf("you must enter a value for the ImportDirectory.\n");
        printf("If you do not do so then the package will not be completely\n");
        printf("set up and you must alter it via the SMS Admin utility\n");
        printf( "Please enter a value (relative to path %s) or just hit ENTER: ",
                            (const char *)gsWorkingPath);
        gets( pszTmp );
    }
    if (strlen(pszTmp) != 0) {
        strcpy( szBuff, (const char *)gsWorkingPath );
        strcat( szBuff, pszTmp );
        SetScalarString( hPkgFolder, "Workstation root", szBuff );
    }



    // Source directory for Shared Server Apps.
    // If it's not in the pdf ask the user for it. It's mandatory.
    // ===========================================================
    GetPrivateProfileString("Package Definition",
                            "SetupDirectory",
                            "",
                            pszTmp,
                            MAX_BUF,
                            gsFilename);
    if (strlen(pszTmp) == 0) {
        printf("If this package is destined to be set up for sharing\n");
        printf("you must enter a value for the SetupDirectory.\n");
        printf("If you do not do so then the package will not be completely\n");
        printf("set up and you must alter it via the SMS Admin utility\n");
        printf( "Please enter a value (relative to path %s) or just hit ENTER: ",
                            (const char *)gsWorkingPath);
        gets( pszTmp );
    }
    if (strlen(pszTmp) != 0) {
        strcpy( szBuff, (const char *)gsWorkingPath );
        strcat( szBuff, pszTmp );
        SetScalarString( hPkgFolder, "Server root", szBuff );
    }


    // Get package access specifications from PDF. If there are specifications
    // set them in the package. If there are no specifications leave it alone.
    // =======================================================================

    GetPrivateProfileString("Package Definition",
                            "WorkstationAccess",
                            "",
                            pszTmp,
                            MAX_BUF,
                            gsFilename);

    if (strlen(pszTmp) > 0) {
        DWORD dwPerms = 0;

        if (strstr( pszTmp, "UserRead" )) {
            dwPerms |= PACKAGE_USER_READ;
        }
        if (strstr( pszTmp, "UserWrite" )) {
            dwPerms |= PACKAGE_USER_WRITE;
        }
        if (strstr( pszTmp, "GuestRead" )) {
            dwPerms |= PACKAGE_GUEST_READ;
        }
        if (strstr( pszTmp, "GuestWrite" )) {
            dwPerms |= PACKAGE_GUEST_WRITE;
        }

        SetScalarInt( hPkgFolder, "Workstation permissions", dwPerms );
    }

    dwRet = 0;

Exit:
    delete pszTmp;
    return(dwRet);
}



//***************************************************************************
//
//  ParseProgramItemProperties
//
//  Parses out properties for program items.
//
//  Returns:
//
//      DWORD                           0 on success or a PDF_ error code.
//
//***************************************************************************
DWORD ParseProgramItemProperties( HANDLE hPkgFolder )
{
    DWORD dwRet = 0;
    char *buf = new char[MAX_BUF];      // Temporary working buffer

    SMS_STATUS stat;

    for (int i = 1; ; i++) {

        // Create a new progitem folder.
        // Do this once per iteration.
        // If all goes well it will be linked and committed at the end
        // of each iteration.
        // ===========================================================
        HANDLE hPIFolder;
        stat = SmsCreateFolder( hPkgFolder, F_PROGITEM, "", &hPIFolder );
        if (stat != SMS_OK) {
            DisplaySmsError("SmsCreateFolder (program item) failed", stat);
            return( PDF_ERROR );
        }

        char Section[128];
        sprintf(Section, "Program Item Properties %d", i);

        dwRet = GetPrivateProfileString(Section,
                                        "CommandLine",
                                        "",
                                        buf,
                                        MAX_BUF,
                                        gsFilename);

        if (dwRet == 0) {           // When no more program item sections
            break;                  // are available.
        }


        // If here, we have started reading a program item.
        // ================================================

        SetScalarString( hPIFolder, "Command line", buf );

        //-----------------------------------------------------

        dwRet = GetPrivateProfileString(Section,
                                        "Description",
                                        "",
                                        buf,
                                        MAX_BUF,
                                        gsFilename);

        SetScalarString( hPIFolder, "Description", buf );

        //-----------------------------------------------------

        dwRet = GetPrivateProfileString(Section,
                                        "ConfigurationScript",
                                        "",
                                        buf,
                                        MAX_BUF,
                                        gsFilename);

        if (strlen(buf)) {
            SetScalarString( hPIFolder, "Configure script file", buf );
        }

        //-----------------------------------------------------

        dwRet = GetPrivateProfileString(Section,
                                        "RegistryName",
                                        "",
                                        buf,
                                        MAX_BUF,
                                        gsFilename);

        SetScalarString( hPIFolder, "Registry name", buf );

        //-----------------------------------------------------

        dwRet = GetPrivateProfileString(Section,
                                        "RunMinimized",
                                        "",
                                        buf,
                                        MAX_BUF,
                                        gsFilename);

        if (_stricmp(buf, "TRUE") == 0) {
            SetScalarInt( hPIFolder,  "Run minimized", TRUE );
        } else {
            SetScalarInt( hPIFolder,  "Run minimized", FALSE );
        }

        //-----------------------------------------------------

        dwRet = GetPrivateProfileString(Section,
                                        "RunLocalCopyIfPresent",
                                        "",
                                        buf,
                                        MAX_BUF,
                                        gsFilename);

        if (_stricmp(buf, "TRUE") == 0) {
            SetScalarInt( hPIFolder,  "Search local flag", TRUE );
        } else {
            SetScalarInt( hPIFolder,  "Search local flag", FALSE );
        }

        //-----------------------------------------------------

        dwRet = GetPrivateProfileString(Section,
                                        "DriveMode",
                                        "",
                                        buf,
                                        MAX_BUF,
                                        gsFilename);


        if (strstr(buf, "UNC")) {
            SetScalarInt( hPIFolder, "Drive mode", PI_DRIVEMODE_UNC );
        }

        if (strstr(buf, "ANY_DRIVE_LETTER")) {
            SetScalarInt( hPIFolder, "Drive mode", PI_DRIVEMODE_ANY_LETTER );
        }

        if (strstr(buf, "SPECIFIC_DRIVE_LETTER")) {
            // Specific drive letter.
            char *p = strstr(buf, ":");
            SetScalarInt( hPIFolder, "Drive mode", PI_DRIVEMODE_SPECIFIC_LETTER );
            SetScalarString( hPIFolder, "Drive letter", &p[-1] );
        }

        //-----------------------------------------------------


        dwRet = GetPrivateProfileString(Section,
                                        "SupportedPlatforms",
                                        "",
                                        buf,
                                        MAX_BUF,
                                        gsFilename);

        // 'buf' contains an array of strings comma-separated.
        // Each of these strings corresponds to a platform.
        // An example would be:
        //  "Windows 3.1, Windows NT 3.1 (MIPS), ..."
        // We'll call a function to analyse these strings and set
        // the appropriate bits in a DWORD. This is the value that
        // we will store in the scalar.
        DWORD dwPlatforms = GetPlatforms( buf );
        SetScalarInt( hPIFolder, "Platforms", dwPlatforms );


        //-----------------------------------------------------


        // Read in the icon.

        dwRet = GetPrivateProfileString(Section,
                                        "SetupIcon",
                                        "",
                                        buf,
                                        MAX_BUF,
                                        gsFilename);

        CString sFile = gsWorkingPath + buf;

        FILE *fIcon = fopen((const char *)sFile, "rb");

        if (fIcon) {
            BYTE *pIconFileImage;
            DWORD dwImageSize;

            fseek(fIcon, 0, SEEK_END);
            dwImageSize = (DWORD)ftell(fIcon);
            fseek(fIcon, 0, SEEK_SET);
            pIconFileImage = new BYTE[dwImageSize];
            DWORD dwResult = fread(pIconFileImage, sizeof(BYTE), dwImageSize, fIcon);
            if (dwResult == dwImageSize) {
                SCALAR sc;
                sc.pszName = "Icon";
                sc.scType = SCALAR_BINARY;
                sc.pValue = pIconFileImage;
                sc.dwLen = dwImageSize;
                SmsSetScalar( hPIFolder, &sc );
            } else {
                printf("Can't read icon file %s\n", (const char *)sFile);
                delete pIconFileImage;
            }
            fclose(fIcon);
        } else {
            printf("Can't access icon file %s\n", (const char *)sFile);
        }

        //-----------------------------------------------------

        dwRet = GetPrivateProfileString(Section,
                                        "DisplayIconInProgGroup",
                                        "TRUE",
                                        buf,
                                        MAX_BUF,
                                        gsFilename);

        if (_stricmp(buf, "TRUE") == 0) {
            SetScalarInt( hPIFolder,  "Display Icon in Program Group", TRUE );
        } else {
            SetScalarInt( hPIFolder,  "Display Icon in Program Group", FALSE );
        }



        // Add the program item folder to the package folder.
        // ==================================================
        stat = SmsLinkFolder( hPIFolder );
        stat = SmsCommitFolder( hPIFolder );
        stat = SmsCloseFolder( hPIFolder );
    }

    delete buf;
    return 0;
}

//***************************************************************************
//
//  ParseSetupVariations
//
//
//  Returns:
//
//      DWORD                           0 on success or a PDF_ error code.
//
//***************************************************************************
DWORD ParseSetupVariations( HANDLE hPkgFolder )
{
    CStringArray asVariations;
    DWORD dwRet;
    char *buf = new char[MAX_BUF];

    dwRet = GetPrivateProfileString("Package Definition",
                                    "SetupVariations",
                                    "",
                                    buf,
                                    MAX_BUF,
                                    gsFilename);

    char *p = strtok(buf, ",");

    while (p) {
        while (*p == ' ')
            p++;  // Move past leading blanks

        asVariations.Add(p);
        p = strtok(NULL, ",");
    }


    // Now parse out the individual variations.
    // ========================================


    for (int i = 0; i < asVariations.GetSize(); i++) {


        // Create a new WCL folder.
        // Do this once per iteration.
        // If all goes well it will be linked and committed at the end
        // of each iteration.
        // ===========================================================
        HANDLE hWclFolder;
        SMS_STATUS stat;
        stat = SmsCreateFolder( hPkgFolder, F_WCL, "", &hWclFolder );
        if (stat != SMS_OK) {
            DisplaySmsError("SmsCreateFolder (wcl) failed", stat);
            return( PDF_ERROR );
        }

        CString sVariation = asVariations[i] + CString(" Setup");

        //------------------------------------------------------

        dwRet = GetPrivateProfileString(sVariation,
                                        "CommandLine",
                                        "",
                                        buf,
                                        MAX_BUF,
                                        gsFilename);

        SetScalarString( hWclFolder, "Command", buf );

        //------------------------------------------------------

        dwRet = GetPrivateProfileString(sVariation,
                                        "CommandName",
                                        "",
                                        buf,
                                        MAX_BUF,
                                        gsFilename);

        SetScalarString( hWclFolder, "Name", buf );

        //------------------------------------------------------
        // since wclFlags is zero initialized we only need to OR
        // it together with any bitfields needing set
        DWORD wclFlags = 0;

        dwRet = GetPrivateProfileString(sVariation,
                                        "UserInputRequired",
                                        "",
                                        buf,
                                        MAX_BUF,
                                        gsFilename);

        if (_stricmp(buf, "TRUE") != 0) {
            wclFlags |= WCL_AUTOMATED_COMMAND_LINE;
        }


        SetScalarInt( hWclFolder, "Flags", wclFlags );

        //------------------------------------------------------


        dwRet = GetPrivateProfileString(sVariation,
                                        "SupportedPlatforms",
                                        "",
                                        buf,
                                        MAX_BUF,
                                        gsFilename);

        DWORD dwPlatforms = GetPlatforms( buf );
        SetScalarInt( hWclFolder, "Platforms", dwPlatforms );


        //------------------------------------------------------


        // Add WCL to package. -- link and commit wcl folder.
        // ===================

        stat = SmsLinkFolder( hWclFolder );
        stat = SmsCommitFolder( hWclFolder );
        stat = SmsCloseFolder( hWclFolder );

    }

    delete buf;
    return 0;
}


//***************************************************************************
//
//  ParseSetupForSharing
//
//
//  Returns:
//
//      DWORD                           0 on success or a PDF_ error code.
//
//***************************************************************************
DWORD ParseSetupForSharing( HANDLE hPkgFolder )
{
    BOOL bSharePkg = FALSE;
    DWORD dwRet;

    char *buf = new char[MAX_BUF];

    //-------------------------------------------------

    dwRet = GetPrivateProfileString("Setup Package for Sharing",
                                    "ShareName",
                                    "",
                                    buf,
                                    MAX_BUF,
                                    gsFilename);

      SetScalarString( hPkgFolder, "Share name", buf );

    //-------------------------------------------------

    dwRet = GetPrivateProfileString("Setup Package for Sharing",
                                    "ShareAccess",
                                    "",
                                    buf,
                                    MAX_BUF,
                                    gsFilename);

    DWORD dwFlags = 0;

    if (strstr(buf, "UserRead")) {
        dwFlags |= PACKAGE_USER_READ;
    }
    if (strstr(buf, "UserWrite")) {
        dwFlags |= PACKAGE_USER_WRITE;
    }
    if (strstr(buf, "GuestRead")) {
        dwFlags |= PACKAGE_GUEST_READ;
    }
    if (strstr(buf, "GuestWrite")) {
        dwFlags |= PACKAGE_GUEST_WRITE;
    }

    SetScalarInt( hPkgFolder, "Share permissions", dwFlags );

    if (dwFlags) {
        bSharePkg = TRUE;
    }

    //-------------------------------------------------


    delete buf;
    return 0;
}


//***************************************************************************
//
//  FillFileTokens
//
//
//
//
//***************************************************************************
void FillFileTokens(TOKEN *pToken, char *pszBuf )
{
    char *pszBuff2 = new char[MAX_BUF];
    char *pszBuff3 = new char[MAX_BUF];

    DWORD dwRet;
    LONG offset, length, value;
    int hr, min, mm, dd, yy;
    CString sToken;
    const CString sQuote("\"");

    //--------------------------------------------------------------

    dwRet = GetPrivateProfileString(pszBuf, "FILE", "", pszBuff2, MAX_BUF, gsFilename);

    sToken = "FILE " + sQuote + pszBuff2 + sQuote;

    //--------------------------------------------------------------


    dwRet = GetPrivateProfileString(pszBuf, "SIZE", "", pszBuff2, MAX_BUF, gsFilename);

    if (dwRet) {
        sToken += CString(" SIZE ") + pszBuff2;
    }

    //--------------------------------------------------------------


    dwRet = GetPrivateProfileString(pszBuf,
                                    "COLLECT",
                                    "",
                                    pszBuff2,
                                    MAX_BUF,
                                    gsFilename);

    if (dwRet && (_stricmp(pszBuff2, "TRUE") == 0)) {
        sToken += CString(" COLLECT ");
    }


    //--------------------------------------------------------------


    dwRet = GetPrivateProfileString(pszBuf,
                                    "CHECKSUM",
                                    "",
                                    pszBuff2,
                                    MAX_BUF,
                                    gsFilename);

    if (dwRet) {
        sscanf(pszBuff2, "%d,%d,%d", &offset, &length, &value);
        sToken += CString(" CHECKSUM ") + pszBuff2;
    }

    //--------------------------------------------------------------


    dwRet = GetPrivateProfileString(pszBuf, "CRC", "", pszBuff2, MAX_BUF, gsFilename);

    if (dwRet) {
        sscanf(pszBuff2, "%d,%d,%d", &offset, &length, &value);
        sToken += CString(" CRC ") + pszBuff2;
    }

    //--------------------------------------------------------------


    dwRet = GetPrivateProfileString(pszBuf, "DATE", "", pszBuff2, MAX_BUF, gsFilename);

    if (dwRet) {
        sscanf(pszBuff2, "%d,%d,%d", &mm, &dd, &yy);
        sprintf( pszBuff3, "%d/%d/%d", mm, dd, yy );
        sToken += CString(" DATE ") + pszBuff3;
    }


    //--------------------------------------------------------------


    dwRet = GetPrivateProfileString(pszBuf, "TIME", "", pszBuff2, MAX_BUF, gsFilename);

    if (dwRet) {
        sscanf(pszBuff2, "%d,%d", &hr, &min);
        sprintf( pszBuff3, "%d:%d", hr, min );
        sToken += CString(" TIME ") + pszBuff3;
    }

    //--------------------------------------------------------------


    dwRet = GetPrivateProfileString(pszBuf, "BYTE", "", pszBuff2, MAX_BUF, gsFilename);

    if (dwRet) {
        sscanf(pszBuff2, "%d,%d", &offset, &value);
        sToken += CString(" BYTE ") + pszBuff2;
    }

    //--------------------------------------------------------------


    dwRet = GetPrivateProfileString(pszBuf, "WORD", "", pszBuff2, MAX_BUF, gsFilename);

    if (dwRet) {
        sscanf(pszBuff2, "%d,%d", &offset, &value);
        sToken += CString(" WORD ") + pszBuff2;
    }


    //--------------------------------------------------------------


    dwRet = GetPrivateProfileString(pszBuf, "LONG", "", pszBuff2, MAX_BUF, gsFilename);

    if (dwRet) {
        sscanf(pszBuff2, "%d,%d", &offset, &value);
        sToken += CString(" LONG ") + pszBuff2;
    }


    //--------------------------------------------------------------
    // String values

    dwRet = GetPrivateProfileString(pszBuf,
                                    "TOKEN 1",
                                    "",
                                    pszBuff2,
                                    MAX_BUF,
                                    gsFilename);

    if (dwRet) {
        // All this to remove the comma after the offset.
        sscanf(pszBuff2, "%d, \"%[^\"]", &offset, pszBuff3);
        sprintf( pszBuff2, "%d \"%s\"", offset, pszBuff3 );
        sToken += CString(" STRING ") + pszBuff2;
    }

    dwRet = GetPrivateProfileString(pszBuf,
                                    "TOKEN 2",
                                    "",
                                    pszBuff2,
                                    MAX_BUF,
                                    gsFilename);

    if (dwRet) {
        sscanf(pszBuff2, "%d, \"%[^\"]", &offset, pszBuff3);
        sprintf( pszBuff2, "%d \"%s\"", offset, pszBuff3 );
        sToken += CString(" STRING ") + pszBuff2;
    }


    dwRet = GetPrivateProfileString(pszBuf,
                                    "TOKEN 3",
                                    "",
                                    pszBuff2,
                                    MAX_BUF,
                                    gsFilename);

    if (dwRet) {
        sscanf(pszBuff2, "%d, \"%[^\"]", &offset, pszBuff3);
        sprintf( pszBuff2, "%d \"%s\"", offset, pszBuff3 );
        sToken += CString(" STRING ") + pszBuff2;
    }


    dwRet = GetPrivateProfileString(pszBuf,
                                    "TOKEN 4",
                                    "",
                                    pszBuff2,
                                    MAX_BUF,
                                    gsFilename);

    if (dwRet) {
        sscanf(pszBuff2, "%d, \"%[^\"]", &offset, pszBuff3);
        sprintf( pszBuff2, "%d \"%s\"", offset, pszBuff3 );
        sToken += CString(" STRING ") + pszBuff2;
    }


    //--------------------------------------------------------------

    // Store the string in the token.
    // ==============================
    strcpy( pToken->szTokenString, (const char *)sToken );


    delete pszBuff2;
    delete pszBuff3;
}




//***************************************************************************
//
//  ParseInventoryRules
//
//  Parameters:
//      HANDLE hPkgFolder               Handle to package folder.
//
//  Returns:
//
//      DWORD                           0 on success or a PDF_ error code.
//
//  NOTE: This doesn't handle nested grouping.
//
//***************************************************************************
DWORD ParseInventoryRules( HANDLE hPkgFolder )
{
    char *pszBuff1 = new char[MAX_BUF];
    char *pszBuff2 = new char[MAX_BUF];

    char rulenum[64];
    DWORD dwRet;
    INT iStart, iEnd, iNextToken;
    iNextToken = 0;

    ANDOR opAndOr = OP_AND;

    HANDLE hInvFolder;
    SMS_STATUS stat;
    stat = SmsCreateFolder( hPkgFolder, F_INVENTORY, "", &hInvFolder );
    if (stat != SMS_OK) {
        DisplaySmsError("SmsCreateFolder (inventory) failed", stat);
        return( PDF_ERROR );
    }

    // First, we build up the expression by traversin the
    // DetectionRule parts of the [Setup Package for Inventory]
    // section.
    // ========================================================

    for (int i = 1; 1; i++) {

        sprintf(rulenum, "Detection Rule Part %d", i);

        dwRet = GetPrivateProfileString("Setup Package for Inventory",
                                        rulenum,
                                        "",
                                        pszBuff1,
                                        MAX_BUF,
                                        gsFilename);

        if (!dwRet) {
            break;
        }

        TOKEN Token;
        memset( &Token, 0, sizeof(TOKEN) );

        // If here, we have a rule token.
        // ==============================

        if (_stricmp(pszBuff1, "AND") == 0) {
            opAndOr = OP_AND;
            iNextToken++;
        }

        else if (_stricmp(pszBuff1, "OR") == 0) {
            opAndOr = OP_OR;
            iNextToken++;
        }

        else if (_stricmp(pszBuff1, ")") == 0) {
            // Save the end index and then call SmsManipulateTokens.
            // Note that we subtract 1 from NextToken. This is because
            // we want the index of the *last* token in the range, and
            // not what the next one will be.
            iEnd = iNextToken-1;
            stat = SmsManipulateTokens( hInvFolder, TOK_GROUP, iStart, iEnd );
            if (stat != SMS_OK) {
                DisplaySmsError("SmsManipulateToken fails", stat);
            }
        }

        else if (_stricmp(pszBuff1, "(") == 0) {
            // Start of a group.
            // We will need to know and save the start and end indecies.
            // These we then pass through to SmsManipulateTokens.
            // This means that we need to keep track of the token indecies
            // all the way through.
            iStart = iNextToken;
        }

        else {
            // This is the real part of the token.
            FillFileTokens(&Token, pszBuff1);
            stat = SmsAddToken( hInvFolder, opAndOr, &Token, AT_END );
            if (stat != SMS_OK) {
                DisplaySmsError("SmsAddToken fails", stat);
            }
            iNextToken++;
        }

#ifdef DEBUG
    // Retrieve and print out tokens - with their indecies.
    DWORD ctTknsX=0;
    stat = SmsGetTokenCount( hInvFolder, &ctTknsX );
    printf("Tokens so far: %d Next token: %d\n", ctTknsX, iNextToken);
    for (int i = 0; i < (int)ctTknsX; i++) {
        stat = SmsGetToken( hInvFolder, i, &Token );
        printf(" [%d] <%s>\n", i, Token.szTokenString);
    }
    printf("=======\n");
#endif  // DEBUG

    }


    // Set 'Inventory this package' scalar if appropriate.
    // We only want to do this if there were indeed any inventory
    // rules specified. We check this by looking to see if the
    // filter contains tokens.
    // ==========================================================
    DWORD ctTokens=0;
    stat = SmsGetTokenCount( hInvFolder, &ctTokens );

    if (ctTokens > 0) {
        // Grab this stuff from the section dealing with package folder.
        // We deal with it here in the inventory folder.
        // -------------------------------------------------------------
        dwRet = GetPrivateProfileString("Setup Package for Inventory",
                                        "InventoryThisPackage",
                                        "",
                                        pszBuff1,
                                        MAX_BUF,
                                        gsFilename);

        DWORD dwFlags;
        if (_stricmp(pszBuff1, "TRUE") == 0) {
            dwFlags = 1;
        } else {
            dwFlags = 0;
        }
        SetScalarInt( hInvFolder, "Inventory this package", dwFlags );
    }

    // Cleanup.
    // ========

    delete pszBuff1;
    delete pszBuff2;


    // Only link and commit if there were any inventory rules.
    // =======================================================
    if (ctTokens > 0) {
        stat = SmsLinkFolder( hInvFolder );
        stat = SmsCommitFolder( hInvFolder );
    }
    stat = SmsCloseFolder( hInvFolder );

    return(0);
}



// Ancilliary routines

//***************************************************************************
//
//
//
//***************************************************************************

BOOL FileExists(const char *pszPath)
{
    BOOL bRet;
    CFileStatus status;

    if (CFile::GetStatus( pszPath, status )) {
        bRet = TRUE;
    } else {
        bRet = FALSE;
    }

    return(bRet);
}


//*************************************************************************
//
//  We are given a string buffer which contains a series of comma-delimited
//  platform names.
//  We analyse this string breaking it down into the individual platforms.
//  Each (valid) platform will then cause a corresponding bit-pattern to be
//  ORed into the resulting DWORD that we return.
//
//*************************************************************************

// Build up an array with platform names, for each name also have
// its corresponding bit value.
class CPlatform : public CObject
{
public:
    CPlatform() {};
    CPlatform( CString sPlatform, DWORD bPlatform ) {
        this->sPlatform = sPlatform;
        this->bPlatform = bPlatform;
    }
    ~CPlatform() {};
    CString sPlatform;          // String name of platform (eg "Macintosh").
    DWORD bPlatform;            // Bit value used in platform scalar.
};

CObArray aPlatforms;

// Setup the array.
void InitPlatforms()
{
    CPlatform *pPlat;

    pPlat = new CPlatform( "Macintosh",   PLTFRM_MACINTOSH );
    aPlatforms.Add( pPlat );

    pPlat = new CPlatform( "MS-DOS 5.0",  PLTFRM_DOS5 );
    aPlatforms.Add( pPlat );

    pPlat = new CPlatform( "MS-DOS 6.0",  PLTFRM_DOS6 );
    aPlatforms.Add( pPlat );

    pPlat = new CPlatform( "MS-DOS 6.2",  PLTFRM_DOS6 );
    aPlatforms.Add( pPlat );

    pPlat = new CPlatform( "MS-DOS 6.21", PLTFRM_DOS6 );
    aPlatforms.Add( pPlat );

    pPlat = new CPlatform( "MS-DOS 6.22", PLTFRM_DOS6 );
    aPlatforms.Add( pPlat );

    pPlat = new CPlatform( "Windows 3.1", PLTFRM_WIN16 );
    aPlatforms.Add( pPlat );

    pPlat = new CPlatform( "Windows NT 3.1 (Alpha)", PLTFRM_WIN32_ALPHA );
    aPlatforms.Add( pPlat );

    pPlat = new CPlatform( "Windows NT 3.1 (MIPS)",  PLTFRM_WIN32_MIPS );
    aPlatforms.Add( pPlat );

    pPlat = new CPlatform( "Windows NT 3.1 (x86)",   PLTFRM_WIN32_X86 );
    aPlatforms.Add( pPlat );

    pPlat = new CPlatform( "Windows NT 3.5 (Alpha)", PLTFRM_WIN32_ALPHA );
    aPlatforms.Add( pPlat );

    pPlat = new CPlatform( "Windows NT 3.5 (MIPS)",  PLTFRM_WIN32_MIPS );
    aPlatforms.Add( pPlat );

    pPlat = new CPlatform( "Windows NT 3.5 (x86)",   PLTFRM_WIN32_X86 );
    aPlatforms.Add( pPlat );

    pPlat = new CPlatform( "Windows NT 3.51 (Alpha)",PLTFRM_WIN32_ALPHA );
    aPlatforms.Add( pPlat );

    pPlat = new CPlatform( "Windows NT 3.51 (MIPS)", PLTFRM_WIN32_MIPS );
    aPlatforms.Add( pPlat );

    pPlat = new CPlatform( "Windows NT 3.51 (x86)",  PLTFRM_WIN32_X86 );
    aPlatforms.Add( pPlat );

    pPlat = new CPlatform( "Windows NT 4.0 (Alpha)", PLTFRM_WIN32_ALPHA );
    aPlatforms.Add( pPlat );

    pPlat = new CPlatform( "Windows NT 4.0 (MIPS)",  PLTFRM_WIN32_MIPS );
    aPlatforms.Add( pPlat );

    pPlat = new CPlatform( "Windows NT 4.0 (x86)",   PLTFRM_WIN32_X86 );
    aPlatforms.Add( pPlat );

    pPlat = new CPlatform( "Windows95", PLTFRM_WIN95 );
    aPlatforms.Add( pPlat );
}

DWORD GetPlatforms( char *buf )
{
    DWORD dwPlatforms = 0;
    CPlatform *pPlatform;
    CString sBuff = buf;            // Easier to work with.

    // We have an array of platform names. Check each one of
    // these against our string setting the appropriate value
    // for each platform that we find.
    // ======================================================
    for (int iLoop = 0; iLoop < aPlatforms.GetSize(); iLoop++) {
        pPlatform = (CPlatform *)aPlatforms[iLoop];
        if (sBuff.Find( pPlatform->sPlatform ) != -1) {
            // Found a match. Get the bit value.
            dwPlatforms |= pPlatform->bPlatform;
        }
    }

    return(dwPlatforms);
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
        printf("Connect to data source failed: %d\n", stat);
    }

    return( hConnect );
}





// ====================================================================
//
// DidRequestHelp
//
// Check the program's arguments to see if the user asked for
// the help screen to be displayed.
//
// Parameters:
//      int argc
//          The argc value from main(argc, argv)
//
//      char **argv
//          The argv value from main(argc, argv)
//
// Returns:
//      TRUE if command line parameters included a request
//      for help to be displayed.
//
// ====================================================================
BOOL DidRequestHelp( int argc, char **argv )
{
    if (argc == 2  && (strcmp(argv[1], "-help") == 0)) {
        return(TRUE);
    }
    else {
        return(FALSE);
    }

}




// ====================================================================
//
// DisplayHelp
//
// This function displays the samples help screen.
//
// Parameters:
//      None
//
// Returns:
//      Nothing.
//
// ====================================================================
void DisplayHelp()
{
    printf("\n\n");
    printf("***********************************************************\n");
    printf("* pdf.exe:                                                *\n");
    printf("*                                                         *\n");
    printf("* SMS API Example: Import a PDF file into an SMS database.*\n");
    printf("*                                                         *\n");
    printf("* This sample shows hows the SMS APIs can be used to      *\n");
    printf("* import a pdf file.                                      *\n");
    printf("*                                                         *\n");
    printf("* The user will be asked to provide the SMS database      *\n");
    printf("* details, and then the name of a pdf file.               *\n");
    printf("*                                                         *\n");
    printf("*                                                         *\n");
    printf("*                                                         *\n");
    printf("* Syntax:                                                 *\n");
    printf("*     pdf.exe [-help] file.pdf                            *\n");
    printf("*                                                         *\n");
    printf("* Switches:                                               *\n");
    printf("*     -help       Display this help message.              *\n");
    printf("*                                                         *\n");
    printf("***********************************************************\n");
    printf("\n");
}



// ====================================================================
//
// DisplayGreeting
//
// Display the initial greeting banner.
//
// Parameters:
//     None.
//
// Returns:
//     Nothing.
//
// ====================================================================
void DisplayGreeting()
{
    // For this sample, the greeting is identical to the help screen.
    //===============================================================
    DisplayHelp();
}


// ====================================================================
//
// InputString
//
// Prompt the user to input a string and return the string in the
// specified buffer.
//
// Parameters:
//      const char *pszMessage
//          The user prompt to display.
//
//      char *pszResult
//          Pointer to the buffer where the user's input will be returned.
//
// Returns;
//      The user's input is returned via the given buffer.
//
// ====================================================================
void InputString( const char *pszMessage, char *pszResult )
{
    printf("%s: ", pszMessage);
    gets(pszResult);
}




#ifdef XXX
//**************************************************************************
// ViewFolder
//
//  Display the folder contents.  This version only displays the folder name
//  and type, number of scalars, and the scalars. Other information not
//  relevant.
//
//  NOTE: no error checking.
//
// Parameters:
//      HANDLE hFolder
//          The handle of the folder to view.
//
// Returns: Nothing.
//
//**************************************************************************
void ViewFolder( HANDLE hFolder )
{
    char szFolderID[SMS_DATA_BUFF_SIZE + 1];        // This folder's ID.
    char szfType[SMS_DATA_BUFF_SIZE + 1];           // Folder's tag.
    DWORD fType;                        // Folder's type.
    DWORD ctScalars;                    // How many scalars in this folder.
    SMS_STATUS stat;


    // Get folder ID and type.
    // -----------------------
    stat = SmsGetFolderID( hFolder, szFolderID );
    if (stat == SMS_NEW_FOLDER) {
        strcpy( szFolderID, "New folder without an ID yet" );

    }
    else if (stat != SMS_OK) {
        DisplaySmsError("ViewFolder: can't get folder ID", stat);
        strcpy( szFolderID, "Couldn't get the folder ID" );
    }

    printf("============== '%s' ===========\n", szFolderID);

    stat = SmsGetFolderType( hFolder, &fType, szfType );
    if (stat != SMS_OK) {
        DisplaySmsError("ViewFolder: can't get folder type", stat);
    }

    printf("SCALARS FOR FOLDER '%s'\n", szFolderID);

    // Get count of scalars.
    // ---------------------
    stat = SmsGetScalarCount( hFolder, &ctScalars );
    if (stat != SMS_OK) {
        DisplaySmsError("ViewFolder: can't get scalar count", stat);
    }
    printf("'%s' (%s) contains %d scalars\n", szFolderID, szfType, ctScalars);


    // Display the scalars.
    // --------------------
    DisplayScalars( hFolder );


    // Get the folder count
    DWORD ctFolders;
    stat = SmsGetFolderCount(hFolder, F_ANY, &ctFolders);
    printf("'%s' (%s) contains %d sub-folders\n", szFolderID, szfType, ctFolders);
    for (DWORD dwFolder = 0; dwFolder < ctFolders; ++dwFolder) {
        printf("Getting subfolder\n");
        HANDLE hSubFolder;
        stat = SmsGetNextFolder(hFolder, F_ANY, &hSubFolder);
        if (stat != SMS_OK) {
            DisplaySmsError("SmsGetNextFolder failed", stat);
            break;
        }

        ViewFolder(hSubFolder);

        // Close the sub-folder to avoid a memory leak.
        //============================================
        stat = SmsCloseFolder(hSubFolder);
        if (stat != SMS_OK) {
            DisplaySmsError("Failed to close an open folder", stat);
            break;
        }
    }


    SmsRewind(hFolder, RW_FOLDER | RW_SCALAR);

}  /* ViewFolder */


//*************************************************************************
// DisplayScalars
//
// Display a folder's scalars.
//
// Parameters:
//      HANDLE hfolder
//          This is the folder handle.
//
// Returns: Nothing.
//
// ====================================================================
void DisplayScalars( HANDLE hFolder )
{
    SMS_STATUS stat = SMS_OK;
    SCALAR scalar;
    char *pszTime;          // For conversion of time scalars.

    // The scalars do not have their own string value buffer, so
    // we allocate the buffers here and set pointers to them in the
    // scalar structure.
    //=============================================================
    char szName[SMS_DATA_BUFF_SIZE+1];
    char szValue[SMS_DATA_BUFF_SIZE+1];
    scalar.pszName  = szName;
    scalar.pszValue = szValue;
    scalar.pValue = NULL;


    while (1) {

        scalar.dwLen = sizeof(szValue)-1;       // must tell him the size

        stat = SmsGetNextScalar( hFolder, &scalar);
        if (stat == SMS_NO_MORE_DATA) {
            break;
        }

        if (stat != SMS_OK && stat != SMS_MORE_DATA) {
            DisplaySmsError("SmsGetNextScalar failed in method DisplayScalars", stat);
            break;
        }

        if (stat == SMS_MORE_DATA) {

            printf("Receive buffer too small, should be %d. Data truncated\n",
                            scalar.dwLen);
        }

        // Check scalar type, display accordingly.
        // ---------------------------------------
        switch (scalar.scType) {
        case SCALAR_STRING:
            printf("\t%30s: %s\n", scalar.pszName, scalar.pszValue);
            break;

        case SCALAR_INT:
            printf("\t%30s: %ld\n", scalar.pszName, scalar.dwValue);
            break;

        case SCALAR_TIME:
            // Check if we have a string equivalence. If so use it.
            if (scalar.bStringEquivalence) {
                printf("\t%30s: %s\n", scalar.pszName, scalar.pszValue);

            } else {
                pszTime = ctime( &scalar.tValue );
                printf("\t%30s: %s", scalar.pszName, pszTime);
            }
            break;

        case SCALAR_BINARY:
            // In this sample we won't display the binary data.
            // Just tell the user its size.
            printf("\t%30s: (Binary - this is its size) %ld\n", scalar.pszName, scalar.dwLen);
            break;
        }
    }

    // Why did we exit (other than no more scalars)?
    //==============================================
    if (stat != SMS_NO_MORE_DATA) {
        printf("Bad return from Scalar access: %d\n", stat);
    }

    printf("\n");
}
#endif  // XXX



//**************************************************************************
// SetScalarString
//
// This function sets the value specified scalar to the given string
// value.
//
// Parameters:
//      HANDLE hFolder
//          The handle of the folder containing the scalar to modify.
//      char *pszName
//          The name of the scalar.
//      const char *pszValue
//          The string that will be assigned to the scalar's value.
//
// Returns:
//      Nothing.
//
// Note that the scalar specified must be of type SCALAR_STRING.
//
//***************************************************************************
void SetScalarString(HANDLE hFolder, char* pszName, const char *pszValue)
{
    SCALAR sc;
    sc.pszName  = pszName;
    sc.scType   = SCALAR_STRING;
    sc.pszValue = (char *)pszValue;

    SMS_STATUS stat = SmsSetScalar(hFolder, &sc);

    if (stat != SMS_OK) {
        CString sErr = "SmsSetScalar ('";
        sErr += pszName;
        sErr += "') failed";
        DisplaySmsError( (const char *)sErr, stat);
    }

}




//**************************************************************************
// SetScalarInt
//
// This function sets the value of the specified scalar to
// the given DWORD value.
//
// Parameters:
//      HANDLE hFolder
//          The handle of the folder containing the scalar to modify.
//      char* pszName
//          The name of the scalar.
//      DWORD dwValue
//          The DWORD value to set the scalar to.
//
// Returns:
//      Nothing.
//
// Note that the scalar specified must be of type SCALAR_INT.
//
//***************************************************************************
void SetScalarInt(HANDLE hFolder, char *pszName, DWORD dwValue)
{
    SCALAR sc;
    sc.pszName = pszName;
    sc.scType = SCALAR_INT;
    sc.dwValue = dwValue;


    SMS_STATUS stat = SmsSetScalar(hFolder, &sc);

    if (stat != SMS_OK) {
        CString sErr = "SmsSetScalar ('";
        sErr += pszName;
        sErr += "') failed";
        DisplaySmsError( (const char *)sErr, stat);
    }
}


//**************************************************************************
// ViewFolder
//
//  Display the folder contents.  This version only displays the folder name
//  and type, number of scalars, and the scalars. Other information not
//  relevant.
//
//  NOTE: no error checking.
//
// Parameters:
//      HANDLE hFolder
//          The handle of the folder to view.
//
// Returns: Nothing.
//
//**************************************************************************
void ViewFolder( HANDLE hFolder )
{
    char szFolderID[SMS_DATA_BUFF_SIZE + 1];        // This folder's ID.
    char szfType[SMS_DATA_BUFF_SIZE + 1];           // Folder's tag.
    DWORD fType;                        // Folder's type.
    DWORD ctScalars;                    // How many scalars in this folder.
    SMS_STATUS stat;


    // Get folder ID and type.
    // -----------------------
    stat = SmsGetFolderID( hFolder, szFolderID );
    if (stat == SMS_NEW_FOLDER) {
        strcpy( szFolderID, "New folder without an ID yet" );

    }
    else if (stat != SMS_OK) {
        DisplaySmsError("ViewFolder: can't get folder ID", stat);
        strcpy( szFolderID, "Couldn't get the folder ID" );
    }

    printf("============== '%s' ===========\n", szFolderID);

    stat = SmsGetFolderType( hFolder, &fType, szfType );
    if (stat != SMS_OK) {
        DisplaySmsError("ViewFolder: can't get folder type", stat);
    }

    printf("SCALARS FOR FOLDER '%s'\n", szFolderID);

    // Get count of scalars.
    // ---------------------
    stat = SmsGetScalarCount( hFolder, &ctScalars );
    if (stat != SMS_OK) {
        DisplaySmsError("ViewFolder: can't get scalar count", stat);
    }
    printf("'%s' (%s) contains %d scalars\n", szFolderID, szfType, ctScalars);


    // Display the scalars.
    // --------------------
    DisplayScalars( hFolder );


    // Get the folder count
    DWORD ctFolders;
    stat = SmsGetFolderCount(hFolder, F_ANY, &ctFolders);
    printf("'%s' (%s) contains %d sub-folders\n", szFolderID, szfType, ctFolders);
    for (DWORD dwFolder = 0; dwFolder < ctFolders; ++dwFolder) {
        printf("Getting subfolder\n");
        HANDLE hSubFolder;
        stat = SmsGetNextFolder(hFolder, F_ANY, &hSubFolder);
        if (stat != SMS_OK) {
            DisplaySmsError("SmsGetNextFolder failed", stat);
            break;
        }

        ViewFolder(hSubFolder);

        // Close the sub-folder to avoid a memory leak.
        //============================================
        stat = SmsCloseFolder(hSubFolder);
        if (stat != SMS_OK) {
            DisplaySmsError("Failed to close an open folder", stat);
            break;
        }
    }


    SmsRewind(hFolder, RW_FOLDER | RW_SCALAR);

}  /* ViewFolder */


//*************************************************************************
// DisplayScalars
//
// Display a folder's scalars.
//
// Parameters:
//      HANDLE hfolder
//          This is the folder handle.
//
// Returns: Nothing.
//
// ====================================================================
void DisplayScalars( HANDLE hFolder )
{
    SMS_STATUS stat = SMS_OK;
    SCALAR scalar;
    char *pszTime;          // For conversion of time scalars.

    // The scalars do not have their own string value buffer, so
    // we allocate the buffers here and set pointers to them in the
    // scalar structure.
    //=============================================================
    char szName[SMS_DATA_BUFF_SIZE+1];
    char szValue[SMS_DATA_BUFF_SIZE+1];
    scalar.pszName  = szName;
    scalar.pszValue = szValue;
    scalar.pValue = NULL;


    while (1) {

        scalar.dwLen = sizeof(szValue)-1;       // must tell him the size

        stat = SmsGetNextScalar( hFolder, &scalar);
        if (stat == SMS_NO_MORE_DATA) {
            break;
        }

        if (stat != SMS_OK && stat != SMS_MORE_DATA) {
            DisplaySmsError("SmsGetNextScalar failed in method DisplayScalars", stat);
            break;
        }

        if (stat == SMS_MORE_DATA) {

            printf("Receive buffer too small, should be %d. Data truncated\n",
                            scalar.dwLen);
        }

        // Check scalar type, display accordingly.
        // ---------------------------------------
        switch (scalar.scType) {
        case SCALAR_STRING:
            printf("\t%30s: %s\n", scalar.pszName, scalar.pszValue);
            break;

        case SCALAR_INT:
            printf("\t%30s: %ld\n", scalar.pszName, scalar.dwValue);
            break;

        case SCALAR_TIME:
            // Check if we have a string equivalence. If so use it.
            if (scalar.bStringEquivalence) {
                printf("\t%30s: %s\n", scalar.pszName, scalar.pszValue);

            } else {
                pszTime = ctime( &scalar.tValue );
                printf("\t%30s: %s", scalar.pszName, pszTime);
            }
            break;

        case SCALAR_BINARY:
            // In this sample we won't display the binary data.
            // Just tell the user its size.
            printf("\t%30s: (Binary - this is its size) %ld\n", scalar.pszName, scalar.dwLen);
            break;
        }
    }

    // Why did we exit (other than no more scalars)?
    //==============================================
    if (stat != SMS_NO_MORE_DATA) {
        printf("Bad return from Scalar access: %d\n", stat);
    }

    printf("\n");
}


/* EOF: pdf.cpp */
