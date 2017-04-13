// ====================================================================
//
//  File: tree.cpp
//
//  Copyright (c) 1994, 1995 Microsoft Corp.
//
//  Author:
//      Jonathan Shuval     Microsoft Corp.
//
//
//  This sample builds a tree of the container/folder hierarchy and
//  displays it to the console.
//
//  The information that is displayed is as follows:
//  For each container we display the container's type and tag followed
//  by a list of filters (possibly empty). This lists filters that are
//  acted upon directly at that level.
//  Following the filter list is a folder list. This gives the folder's
//  type and tag, its filter list, and then a list of scalars for the
//  folder.
//  The scalar display shows the scalar name, it's type, and its access
//  mode.
//
//  See the readme.txt file in this directory for more information.
//
// ====================================================================


// ====================================================================
//
//      Includes
//
// ====================================================================
#include <afx.h>
#include <smsapi.h>


// ====================================================================
//
//      Defines.
//
// ====================================================================
#define CCH_MAXSTRING 256


// ====================================================================
//
//      Prototypes.
//
// ====================================================================

// Process a container.
// -------------------------------------------------------------
void doContainer( FOLDER_INFO *pContainer );


// Process a folder.
// -------------------------------------------------------------
void doFolder( DWORD folderType, int indent, DWORD dwConType );


// Adds a container to the container list.
// -------------------------------------------------------------
void AddContainer( DWORD dwConType );


// Given a filter type display its properties.
// -------------------------------------------------------------
void doFilter( DWORD dwFilterType, int indent );


// Locates filter of specified type from the global filter list.
// -------------------------------------------------------------
FILTER_INFO *FindFilter( DWORD filterType );


// Mark folder as already enumerated within this container graph.
// -------------------------------------------------------------
void Enumerated( DWORD dwConType, DWORD folderType );


// Call this to find out if this foldertype already been
// enumerated within this container graph.
// -------------------------------------------------------------
BOOL IsEnumerated(DWORD dwConType, DWORD folderType);


// Prompt the user for input and return the reply.
// -------------------------------------------------------------
void InputString( const char *pszMessage, char *pszResult );


// Display the help message.
// -------------------------------------------------------------
void DisplayHelp();

// Display the greeting.
// -------------------------------------------------------------
void DisplayGreeting();


// Check to see if there was a request for help
// on the command line.
// -------------------------------------------------------------
BOOL DidRequestHelp( int argc, char **argv );





// ====================================================================
//
//      Globals.
//
// ====================================================================
FOLDER_INFO **gpFolders = NULL;     // List of FOLDER_INFOs.
DWORD gctFolders = 0;               // Count of them.


FILTER_INFO *gpFilters = NULL;      // List of FILTER_INFOs.
DWORD gctFilters = 0;               // Count of them.

//
// This struct is used to hold information about what folders
// have already been enumerated for a particular container.
//
typedef struct tagContainerEntry {
    DWORD dwConType;                // Container's type.
    CDWordArray aEnumFolders;       // Folders already enumerated.
} ContainerEntry;


CObArray ContainerList;             // List of containers (contains list
                                    // of ContainerEntry structs.)





// ====================================================================
//
//      Start here.
//
// ====================================================================
void main( int argc, char** argv )
{
    // Check to see if this is a request to display the help
    // screen.  If so, display it. Otherwise, display a greeting
    // banner.
    //=========================================================
    if (DidRequestHelp( argc, argv )) {
        DisplayHelp();
        return;
    }
    else {
        DisplayGreeting();
    }



    // Data.
    // =====

    DWORD ctContainers;
    FOLDER_INFO **pContainers = NULL;
    FOLDER_INFO *pCont = NULL;




    // Enumerate containers.
    // =====================

        // Get number of containers.
    SmsEnumContainers( NULL, &ctContainers );

        // Allocate memory and get the containers.
    pContainers = new FOLDER_INFO *[ctContainers];
    SmsEnumContainers( pContainers, &ctContainers );


    // Enumerate all filters.
    // ======================
        // Get number of filters.
    SmsEnumFilters(NULL, &gctFilters);

        // Allocate memory and get the filters.
    gpFilters = new FILTER_INFO[gctFilters];
    SmsEnumFilters( gpFilters, &gctFilters );


    // Enumerate all folders.
    // ======================
        // Get number of folders.
    SmsEnumFolders( NULL, &gctFolders );

        // Allocate memory and get the folders.
    gpFolders = new FOLDER_INFO *[gctFolders];
    SmsEnumFolders( gpFolders, &gctFolders );


    // Loop through each container.
    // ============================

    for (DWORD i = 0; i < ctContainers; i++) {

        // Process the container
        doContainer( pContainers[i] );
    }

}



// ====================================================================
//
//  doContainer -- process container.
//
//  This is called from main. We print out information for this
//  container, and then process each folder within the container.
//
// ====================================================================

void doContainer( FOLDER_INFO *pContainer )
{
    DWORD dwI;

    // Add this container to our container list.
    // =========================================
    AddContainer( pContainer->dwTag );

    // We are now looking at the FOLDER_INFO for a container.
    // We want to print out the count and list of filters,
    // the folder type count, and then process each folder.
    // ======================================================
    printf("Container: %s [%d]\n", pContainer->pszTag, pContainer->dwTag);

    // Print out list of filters.
    // =============================
    printf("%d filter(s)\n", pContainer->ctFilters);
    DWORD *pFilters = pContainer->pFilterTags;

    for (dwI = 0; dwI < pContainer->ctFilters; dwI++) {
        doFilter( pFilters[dwI], 1 );
    }


    // Print out list of folders.
    // ==========================
    printf("%d folder-type(s)\n", pContainer->ctFolders);

    DWORD *pFolderIDs = pContainer->pFolderTags;
    for (dwI = 0; dwI < pContainer->ctFolders; dwI++) {

        // Now cause the folder to print himself out.
        // ------------------------------------------
        doFolder( pFolderIDs[dwI], 1, pContainer->dwTag );
    }

    // No scalars for container.
    // =========================

    printf("\n\n");
}



// ====================================================================
//
//  FindFilter -- locate filter of specified type from the list of
//  filter descriptors returned by the API SmsEnumFilters.
//
//  Return a pointer to the FILTER_INFO for the filter.
//
//  Called from doFilter.
//
// ====================================================================

FILTER_INFO *FindFilter( DWORD filterType )
{
    FILTER_INFO *pFI;
    for (DWORD dwI = 0; dwI < gctFilters; dwI++) {
        pFI = &gpFilters[dwI];
        if (pFI->filterType == filterType) {
            return(pFI);
        }
    }

    return(NULL);
}


// ====================================================================
//
//  dumpScalar -- given a SCALAR_INFO, display the scalar.
//
//  We display the scalar's name, type, and access mode.
//
//  Params:
//      SCALAR_INFO                 Scalar to display.
//      indent                      indent level
//
//
// ====================================================================

void dumpScalar( SCALAR_INFO *pSc, int indent )
{
    // Indentation.
    // ============
    char szIndent[100];
    memset( szIndent, '\0', 100 );
    for (int iLevel = 0; iLevel < indent; iLevel++) {
        strcat( szIndent, "\t");
    }

    char *pszType, *pszAccess;

    // Determine scalar type, display accordingly.
    // ===========================================
    switch (pSc->scType) {
    case SCALAR_STRING:
        pszType = "string";     break;

    case SCALAR_INT:
        pszType = "integer";    break;

    case SCALAR_TIME:
        pszType = "time";       break;

    case SCALAR_BINARY:
        pszType = "binary";     break;
    }

    // Determine access mode, display accordingly.
    // ===========================================
    switch (pSc->fAccess) {
    case ACCESS_READ:
        pszAccess = "read";     break;

    case ACCESS_CREATE:
        pszAccess = "create";   break;

    case ACCESS_MODIFY:
        pszAccess = "modify";   break;

    case ACCESS_DELETE:
        pszAccess = "delete";   break;
    }


    printf("%s%s (%s, %s)\n", szIndent, pSc->szName, pszType, pszAccess);

}



// ====================================================================
//
//  doScalars -- display a folder's scalar.
//
//  Loop through the list of SCALAR structures that are embedded in the
//  FOLDER_INFO, and display them.
//
//  The 'indent' parameter says how far to indent the resulting display
//  string so it looks almost presentable.
//
//  Params:
//      FOLDER_INFO *pFolder        The structure describing the folder
//                                  under consideration.
//      int indent                  Indent level.
//
//  Returns:
//      Nothing.
//
// ====================================================================

void doScalars( FOLDER_INFO *pFolder, int indent )
{
    SCALAR_INFO *pScalar;

    for (DWORD dwI = 0; dwI < pFolder->ctScalars; dwI++) {
        pScalar = &pFolder->pScalars[dwI];
        dumpScalar( pScalar, indent );
    }
}


// ====================================================================
//
//  doFolder -- Given a folder type print out this folder's information.
//
//  The folder has already been retrieved in SmsEnumFolders, we just
//  access it from there.
//
//  Params:
//      folderType                  Folder type we're interested in.
//      dwConType                   Container's type.
//
//  Returns:
//      Nothing.
//
// ====================================================================

void doFolder( DWORD folderType, int indent, DWORD dwConType )
{

    FOLDER_INFO *pFolder;
    DWORD dwI;
    BOOL bFound = FALSE;

    // Indentation.
    // ============
    char szIndent[100];
    memset( szIndent, '\0', 100 );
    for (int iLevel = 0; iLevel < indent; iLevel++) {
        strcat( szIndent, "\t");
    }


    // Loop through the retrieved folders looking for
    // the one with a tag for folderType.
    // ==============================================
    for (dwI = 0; dwI < gctFolders; dwI++) {
        pFolder = gpFolders[dwI];
        if (pFolder->dwTag == folderType) {
            bFound = TRUE;
            break;
        }
    }


    if (!bFound) {
        printf("<<< Error: couldn't locate folder %d >>>\n", folderType);
        return;
    }


    // Display folder type and tag and filter count.
    // =============================================
    printf("%s********** %s folder [%d] **********\n",
        szIndent,    pFolder->pszTag, pFolder->dwTag);

    // Check to see if it's already been displayed.
    // We only want to do this in the context of the current container.
    // ----------------------------------------------------------------
    if (IsEnumerated(dwConType, folderType)) {
        printf("%sFolder already enumerated in this container\n", szIndent);
        printf("%s********** End of %s folder **********\n\n",
                    szIndent, pFolder->pszTag );
        return;
    }

    printf("%s%d filter(s)\n", szIndent, pFolder->ctFilters);

    // Print out list of filter types.
    // ===============================
    DWORD *pFilters = pFolder->pFilterTags;

    for (dwI = 0; dwI < pFolder->ctFilters; dwI++) {
        doFilter( pFilters[dwI], indent );
    }

    // Print out number of scalars, then display them.
    // ===============================================
    printf("%s%d scalars\n", szIndent, pFolder->ctScalars);
    doScalars( pFolder, indent );


    // Prepare to display sub-folders.
    // ===============================
    printf("%s%d folder-type(s)\n", szIndent, pFolder->ctFolders);


    // Before processing sub-folder types mark this folder as already
    // enumerated in this container. Prevents infinite recursion.
    Enumerated(dwConType, folderType);

    // Print out list of folder types.
    DWORD *pFolderIDs = pFolder->pFolderTags;
    for (dwI = 0; dwI < pFolder->ctFolders; dwI++) {
        // Now cause the folder to print himself out.
        doFolder( pFolderIDs[dwI], indent+1, dwConType );

    }

    printf("%s********** End of %s folder **********\n\n",
                szIndent, pFolder->pszTag );

}



// ====================================================================
//
//  doFilter -- given a filter type display its properties.
//
//  Called from doContainer and doFolder.
//
// ====================================================================

void doFilter( DWORD dwFilterType, int indent )
{

    FILTER_INFO *pFilter = FindFilter( dwFilterType );

    if (!pFilter) {
        printf("<<< Error: couldn't locate filter %d >>>\n", dwFilterType);
        return;
    }

    // Indentation.
    // ============
    char szIndent[100];
    memset( szIndent, '\0', 100 );
    for (int iLevel = 0; iLevel < indent; iLevel++) {
        strcat( szIndent, "\t");
    }

    // Display filter type and tag.
    // ============================
    printf("%s%s (%d)\n", szIndent, pFilter->szTag, dwFilterType);


    // Display filter properties.
    // ==========================
    char *ppszField[10];            // Store pointers here.
    DWORD ctFields = 0;             // Number of pointers.

    char szBuff[256];               // Build up output string here.
    sprintf(szBuff, "%s\t[", szIndent); // Additional level of indent.

    if (*(pFilter->szName)) {
        ppszField[ctFields++] = "Token.szName = ";
        ppszField[ctFields++] = pFilter->szName;
    }

    if (*(pFilter->szValue)) {
        ppszField[ctFields++] = "Token.szValue = ";
        ppszField[ctFields++] = pFilter->szValue;
    }

    if (*(pFilter->szOperator)) {
        ppszField[ctFields++] = "Token.szOperator = ";
        ppszField[ctFields++] = pFilter->szOperator;
    }

    if (*(pFilter->szArchitecture)) {
        ppszField[ctFields++] = "Token.szArchitecture = ";
        ppszField[ctFields++] = pFilter->szArchitecture;
    }

    if (*(pFilter->szGroupClass)) {
        ppszField[ctFields++] = "Token.szGroupClass = ";
        ppszField[ctFields++] = pFilter->szGroupClass;
    }

    if (*(pFilter->szAttributeName)) {
        ppszField[ctFields++] = "Token.szAttributeName = ";
        ppszField[ctFields++] = pFilter->szAttributeName;
    }


    for (DWORD dwI = 0; dwI < ctFields; dwI += 2) {
        printf("\t%s%s\"%s\"\n", szIndent, ppszField[dwI], ppszField[dwI+1]);
    }


}



// ====================================================================
//
//  AddContainer -- adds a container to the container list.
//
// This is only for detecting folders that have already been
// enumerated. Nothing more.
// Trouble is we duplicate!
//
// ====================================================================

void AddContainer( DWORD dwConType )
{
    ContainerEntry *pCEntry;
    pCEntry = new ContainerEntry;
    pCEntry->dwConType = dwConType;

    ContainerList.Add((CObject *)pCEntry );
}



// ====================================================================
//
//  Enumerated -- Mark this folder as already enumerated within this
//  container graph.
//
// ====================================================================

void Enumerated(DWORD dwConType, DWORD folderType)
{
    // Locate the container.
    BOOL bFound = FALSE;
    DWORD dwI;                  // loop index.
    ContainerEntry *pCEntry;

    // We keep a global ContainerList (CObArray) which contains
    // a list of container entries (above).

    // Locate container entry.
    // =======================
    for (dwI = 0; dwI < (DWORD)ContainerList.GetSize(); dwI++) {
        pCEntry = (ContainerEntry *)ContainerList[dwI];
        if (pCEntry->dwConType == dwConType) {
            bFound = TRUE;
            break;
        }
    }

    if (!bFound) {
        printf("<<< Error: container tag %d not found in list >>>\n", dwConType);
        return;
    }

    // Add this folder to our list of enumerated folders.
    // ==================================================
    pCEntry->aEnumFolders.Add( folderType );

}



// ====================================================================
//
//  IsEnumerated -- Has this foldertype already been enumerated within
//  this container graph?
//
// ====================================================================

BOOL IsEnumerated(DWORD dwConType, DWORD folderType)
{
    BOOL bFound = FALSE;
    DWORD dwI;                  // loop index.
    ContainerEntry *pCEntry;

    // We keep a global ContainerList (CObArray) which contains
    // a list of container entries (above).

    // Locate container entry.
    // =======================
    for (dwI = 0; dwI < (DWORD)ContainerList.GetSize(); dwI++) {
        pCEntry = (ContainerEntry *)ContainerList[dwI];
        if (pCEntry->dwConType == dwConType) {
            bFound = TRUE;
            break;
        }
    }

    if (!bFound) {
        printf("<<< Error: container tag %d not found in list >>>\n", dwConType);
        return(FALSE);
    }

    // Now look through the array of enumerated folders.
    // =================================================
    for (dwI = 0; dwI < (DWORD)pCEntry->aEnumFolders.GetSize(); dwI++) {
        if (pCEntry->aEnumFolders[dwI] == folderType) {

            // Found it. Folder already enumerated.
            // ------------------------------------
            return(TRUE);
        }
    }

    // Folder hasn't been enumerated.
    // ------------------------------
    return(FALSE);
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
// DidRequestHelp
//
// Check the program's arguments to see if the user asked for
// the help screen to be displayed.
//
// Parameters:
//      int argc
//          The argc value from main(argc, argv)
//
//      char** argv
//          The argv value from main(argc, argv)
//
// Returns:
//      TRUE if command line parameters included a request
//      for help to be displayed.
//
// ====================================================================
BOOL DidRequestHelp(int argc, char** argv)
{
    if (argc == 2  && (strcmp(argv[1], "-help") == 0)) {
        return(TRUE);
    }
    else {
        return(FALSE);
    }
}


// ====================================================================
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
    // Version information.
    // ====================
    char *pVer;
    SmsAPIVer( &pVer );
    printf("\n%s\n\n", pVer);


    // Description.
    // ============

    printf("********************************************************************\n");
    printf("* tree.exe:                                                        *\n");
    printf("*                                                                  *\n");
    printf("* This is a sample program for the SMS SDK.  It shows how the      *\n");
    printf("* container hierarchy can be displayed.                            *\n");
    printf("*                                                                  *\n");
    printf("* For each container in SMS, the following details are displayed:  *\n");
    printf("*     the container's tag and type                                 *\n");
    printf("*     any filters that are acted upon directly by the container    *\n");
    printf("*                                                                  *\n");
    printf("* Following this is a display of all folders within that container.*\n");
    printf("*                                                                  *\n");
    printf("* For folders the following is displayed:                          *\n");
    printf("*     the folder's type and tag                                    *\n");
    printf("*     any filters that are acted upon by the folder                *\n");
    printf("*     a list of the folder's scalars                               *\n");
    printf("* Note that folder enumeration is recursive, that is, some folders *\n");
    printf("* contain sub-folders.                                             *\n");
    printf("*                                                                  *\n");
    printf("* For filters a list of the filter's attributes are displayed.     *\n");
    printf("*                                                                  *\n");
    printf("* Syntax:                                                          *\n");
    printf("*     tree.exe [-help]                                             *\n");
    printf("*                                                                  *\n");
    printf("* Switches:                                                        *\n");
    printf("*     -help       Display this help screen.                        *\n");
    printf("*                                                                  *\n");
    printf("********************************************************************\n");
    printf("\n");
}



// ====================================================================
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

    // Pause so the description doesn't fly off the screen.
    // ====================================================
    char szReply[CCH_MAXSTRING];
    InputString("Press ENTER to continue", szReply);
    printf("\n");
}






/* EOF: tree.cpp */

