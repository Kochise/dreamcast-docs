// RegDB.c -- Implements the semantics of the registry interface for this
//            application. The visible interfaces and data structures are
//            defined in RegDB.h.

/*
 *
                                Overview
                                --------

The NT Registry is an object database consisting of keys and values. Keys
have names and may contain other keys and values. A value is a name paired
with a data object and a data type. The keys in the registry are analogous
to the directories in a file system. In that vein the values are analogous
to files.

Access to a key and its associated set of values is mediated by a key handle.
Four key handles are given as predefined constants. Those handles correspond
to the roots of key trees which have special signifigance. Handles for the
other keys in the registry database may be constructed via the Registry's
Open and Create interfaces using an existing key handle and a relative path
string.

The predefined key handles are:


    HKEY_LOCAL_MACHINE -- This handle refers to a tree of keys and values
                          which characterize the state of the local machine.
                          It contains state information global to everyone
                          who uses the machine.

    HKEY_CLASSES_ROOT  -- This handle refers to a subtree within
                          HKEY_LOCAL_MACHINE. It defines the associations
                          between file extensions and document types as well
                          as the command strings for shell and DDE/OLE actions.

    HKEY_USERS         -- This handle refers to a tree of information about
                          the people who use this machine. The top level of
                          the tree consists of a .DEFAULT key and one or more
                          entries for specific people. The specific entries
                          are created dynamically and are initially based on
                          the content of the .DEFAULT key. The key names for
                          the specific entries are SIDs which define the
                          permissions given to the corresponding people.

    HKEY_CURRENT_USER  -- This handle refers to a specific user key within
                          HKEY_USERS. It denotes the information tree for
                          the currently active user id.


                          Application Conventions
                          -----------------------

Applications need to manipulate three of the above key trees. At installation
time an application should adjust HKEY_CLASSES_ROOT to define the documents
which it handles together with their file extensions and its shell and
DDE/OLE command strings. At the same time it needs to add information global
to all users to the HKEY_USERS\.DEFAULT key.

Subsequently an application will need to place per-user information in the
HKEY_CURRENT_USER subtree. That information will include preferences as well
as historical information such as lists of recently opened files.

The conventions appropriate to the HKEY_CLASSES_ROOT will not be described
or demonstrated in this sample application. The focus here will be on
HKEY_USERS\.DEFAULT and HKEY_CURRENT_USER subtrees.

Within both of those subtrees information related to version 2.5 of the
Bazooka application published by Trey Software will be clustered in the
subkey:

      software\"Trey Software"\Bazooka\2.5

and in general applications will use a path with the structure

      software \ <company name> \ <application name> \ <version number>

to access their state information.

After an application has been installed almost all registry changes will
involve HKEY_CURRENT_USER and will concern a specific user's preferences
or history.

 */

#include "multipad.h"

// #include <windows.H>
// #include <winbase.h>
#include <malloc.h>
#include "regdb.h"

HKEY hkGlobal  = NULL;  // Key Handle for global registry data
HKEY hkPerUser = NULL;  // Key Handle for per-user registry data

BOOL fTextWrapDefault = FALSE; // Set from registry data.

HANDLE hmtxRegGlobal  = NULL; // Mutex for serializing Local Machine Data.
HANDLE hmtxRegPerUser = NULL; // Mutex for serializing Current User Data

BOOL RunningAsAdministrator()
{
   BOOL  fAdmin;
   HANDLE htkThread;
   TOKEN_GROUPS *ptg = NULL;
   DWORD cbTokenGroups;
   DWORD iGroup;
   SID_IDENTIFIER_AUTHORITY SystemSidAuthority= SECURITY_NT_AUTHORITY;
   PSID psidAdmin;

   // This function returns TRUE if the user identifier associated with this
   // process is a member of the the Administrators group.

   // First we must open a handle to the access token for this thread.

   if (!OpenThreadToken(GetCurrentThread(), TOKEN_QUERY, FALSE, &htkThread))
      if (GetLastError() == ERROR_NO_TOKEN)
      {
         // If the thread does not have an access token, we'll examine the
         // access token associated with the process.

         if (!OpenProcessToken(GetCurrentProcess(), TOKEN_QUERY, &htkThread))
         return FALSE;
      }
      else return FALSE;

   // Then we must query the size of the group information associated with
   // the token. Note that we expect a FALSE result from GetTokenInformation
   // because we've given it a NULL buffer. On exit cbTokenGroups will tell
   // the size of the group information.

   if (GetTokenInformation(htkThread, TokenGroups, NULL, 0, &cbTokenGroups))
      return FALSE;

   // Here we verify that GetTokenInformation failed for lack of a large
   // enough buffer.

   if (GetLastError() != ERROR_INSUFFICIENT_BUFFER)
      return FALSE;

   // Now we allocate a buffer for the group information.
   // Since _alloca allocates on the stack, we don't have
   // to explicitly deallocate it. That happens automatically
   // when we exit this function.

   if (!(ptg= _alloca(cbTokenGroups))) return FALSE;

   // Now we ask for the group information again.
   // This may fail if an administrator has added this account
   // to an additional group between our first call to
   // GetTokenInformation and this one.

   if (!GetTokenInformation(htkThread, TokenGroups, ptg, cbTokenGroups,
                                       &cbTokenGroups
                           )
      )
      return FALSE;

   // Now we must create a System Identifier for the Admin group.

   if (!AllocateAndInitializeSid
          (&SystemSidAuthority, 2, SECURITY_BUILTIN_DOMAIN_RID,
                                   DOMAIN_ALIAS_RID_ADMINS,
                                   0, 0, 0, 0, 0, 0,
                                   &psidAdmin
          )
      )
      return FALSE;

   // Finally we'll iterate through the list of groups for this access
   // token looking for a match against the SID we created above.

   fAdmin= FALSE;

   for (iGroup= 0; iGroup < ptg->GroupCount; iGroup++)
      if (EqualSid(ptg->Groups[iGroup].Sid, psidAdmin))
      {
         fAdmin= TRUE;

         break;
      }

   // Before we exit we must explicity deallocate the SID
   // we created.

   FreeSid(psidAdmin);

   return(fAdmin);
}


BOOL InstallApp(PSZ pszPathBuff)
{
   // This function attempts to install global data for this
   // application in the HKEY_LOCAL_MACHINE portion of the
   // registry database.

   // The parameter pszPathBuff refers to a null terminated
   // string which defines where the new key should be located
   // in the LOCAL_MACHINE tree.

   // We requires that the current user have administrative
   // privileges. That requirement insures that the owner
   // tag for the global registry entries will be the
   // Administrator group and not a particular user id.

   // We also assume that hmtxRegGlobal is held when this function is called.

   // First we'll see whether this user has admin privileges...
   // Only administrators can install this application...

   if (!RunningAsAdministrator())
   {
      MPError(hwndFrame, MB_OK | MB_ICONHAND, IDS_CANTINSTALL, NULL);

      return FALSE;
   }

   // Then we bring up a dialog to get the global configuration information
   // we'll be storing in the HKEY_LOCAL_MACHINE tree. The dialog proc
   // will call StoreAppConfig with that configuration data.

   if (!DialogBoxParam(hInst, MAKEINTRESOURCE(DLG_INSTALL),
                       hwndFrame, InstallDlgProc,
                       (LPARAM) pszPathBuff
                      )
      ) return FALSE;
}

BOOL StoreAppConfig(HWND hwnd, PSZ pszPathBuff, PSZ pszInstallName,
                    PSZ pszInstallOrg, BOOL fTextWrapDefault
                   )
{
   // This function attempts to install global data for this
   // application in the HKEY_LOCAL_MACHINE portion of the
   // registry database. It is called from InstallDlgProc.

   // The parameter hwnd denotes the window associated with this
   // call to StoreAppConfig. It's used with the calls to MPError
   // below.

   // The parameter pszPathBuff refers to a null terminated
   // string which defines where the new key should be located
   // in the LOCAL_MACHINE tree.

   // The pszInstallName and pszInstallOrg parameters are text strings
   // which denote the person and the organization which has installed
   // this app in the HKEY_LOCAL_MACHINE portion of the registry.

   // The fTextWrapDefault is a boolean value which will be stored
   // in the DEFAULT subkey. Values in the DEFAULT subkey are copied
   // into the HKEY_PER_USER area during user initialization. (See
   // the InitUser function below.)

   // We assume that hmtxRegGlobal is held when this function is called.

   HKEY  hkGlobal     = NULL;
   HKEY  hkDefaults   = NULL;
   PSID  psidAdmins   = NULL;
   PSID  psidEveryone = NULL;
   PACL  paclKey      = NULL;

   BOOL  fInstalled   = FALSE;

   long  lResult;
   DWORD dwDisposition;

   BYTE  abEmptyStringSet[2];

   SID_IDENTIFIER_AUTHORITY SystemSidAuthority= SECURITY_NT_AUTHORITY;
   SID_IDENTIFIER_AUTHORITY  WorldSidAuthority= SECURITY_WORLD_SID_AUTHORITY;

   SECURITY_ATTRIBUTES sa;
   SECURITY_DESCRIPTOR sdPermissions;
   // Next we'll setup the security attributes we're going to
   // use with the application's global key.

   sa.nLength              = sizeof(SECURITY_ATTRIBUTES);
   sa.bInheritHandle       = FALSE;
   sa.lpSecurityDescriptor = &sdPermissions;

   // Here we're creating a System Identifier (SID) to represent
   // the Admin group.

   if (!AllocateAndInitializeSid
          (&SystemSidAuthority, 2, SECURITY_BUILTIN_DOMAIN_RID,
                                   DOMAIN_ALIAS_RID_ADMINS,
                                   0, 0, 0, 0, 0, 0,
                                   &psidAdmins
          )
      )
      goto security_failure;

   // Now we'll construct a System Identifier which represents
   // all users.

   if (!AllocateAndInitializeSid
          (&WorldSidAuthority, 1, SECURITY_WORLD_RID,
           0, 0, 0, 0, 0, 0, 0,
           &psidEveryone
          )
      )
      goto security_failure;

   if (!InitializeSecurityDescriptor(&sdPermissions,
                                     SECURITY_DESCRIPTOR_REVISION1
                                    )
      )
      goto security_failure;

   // We want the admin group to own this key.

   if (!SetSecurityDescriptorOwner(&sdPermissions, psidAdmins, 0))
      goto security_failure;

   // Finally we must allocate and construct the discretionary
   // access control list (DACL) for the key.

   // Note that _alloca allocates memory on the stack frame
   // which will automatically be deallocated when this routine
   // exits.

   if (!(paclKey= (PACL) _alloca(ACL_BUFFER_SIZE)))
      goto memory_limited;

   if (!InitializeAcl(paclKey, ACL_BUFFER_SIZE, ACL_REVISION2))
      goto security_failure;

   // Our DACL will contain two access control entries (ACEs). One which allows
   // members of the Admin group complete access to the key, and one which gives
   // read-only access to everyone.

   if (!AddAccessAllowedAce(paclKey, ACL_REVISION2, KEY_ALL_ACCESS, psidAdmins))
      goto security_failure;

   if (!AddAccessAllowedAce(paclKey, ACL_REVISION2, KEY_READ, psidEveryone))
      goto security_failure;

   // We must bind this DACL to the security descriptor...

   if (!SetSecurityDescriptorDacl(&sdPermissions, TRUE, paclKey, FALSE))
      goto security_failure;

   // Now we'll attempt to create the key with the security attributes...

   lResult= RegCreateKeyEx(HKEY_LOCAL_MACHINE, pszPathBuff, 0,
                           "Application Global Data", REG_OPTION_NON_VOLATILE,
                           KEY_ALL_ACCESS,
                           &sa, &hkGlobal, &dwDisposition
                          );

   if (lResult != ERROR_SUCCESS) goto registry_access_error;

   // Usually the disposition value will indicate that we've created a
   // new key. Sometimes it may instead state that we've opened an existing
   // key. This can happen when installation is incomplete and interrupted,
   // say by loss of electrical power.

   if (   dwDisposition != REG_CREATED_NEW_KEY
       && dwDisposition != REG_OPENED_EXISTING_KEY
      ) goto registry_access_error;

   // Now we'll add two values to the global key.

   // These values are simple strings which identify the name and
   // organization associated with this installation.

   lResult= RegSetValueEx(hkGlobal, KEY_VALUE_INSTALL_NAME, 0, REG_SZ,
                                    pszInstallName, strlen(pszInstallName)+1
                         );

   if (lResult != ERROR_SUCCESS) goto registry_access_error;

   lResult= RegSetValueEx(hkGlobal, KEY_VALUE_INSTALL_ORG, 0, REG_SZ,
                                    pszInstallOrg, strlen(pszInstallOrg)+1
                         );

   if (lResult != ERROR_SUCCESS) goto registry_access_error;

   // We've created the global key. Now we must create the "Defaults" subkey
   // and set its value(s).

   lResult= RegCreateKeyEx(hkGlobal, DEFAULTS_PATH, 0,
                           "Defaults for Per-User Data",
                           REG_OPTION_NON_VOLATILE, KEY_ALL_ACCESS,
                           &sa, &hkDefaults, &dwDisposition
                          );

   if (lResult != ERROR_SUCCESS) goto registry_access_error;

   // Usually the disposition value will indicate that we've created a
   // new key. Sometimes it may instead state that we've opened an existing
   // key. This can happen when installation is incomplete and interrupted,
   // say by loss of electrical power.

   if (   dwDisposition != REG_CREATED_NEW_KEY
       && dwDisposition != REG_OPENED_EXISTING_KEY
      ) goto registry_access_error;

   // Now we'll add a collection of values to the Defaults subkey.
   // When per-user data is constructed for a particular userid, these
   // values will define the initial state of the per-user data.

   // In this demo application we store two items -- a word-wrap flag
   // and a file name set.

   lResult= RegSetValueEx(hkDefaults, WORD_WRAP_DEFAULT, 0, REG_DWORD,
                          (LPBYTE) &fTextWrapDefault,
                          sizeof(fTextWrapDefault)
                         );

   if (lResult != ERROR_SUCCESS) goto registry_access_error;

   abEmptyStringSet[0]= '\0';
   abEmptyStringSet[1]= '\0';

   lResult= RegSetValueEx(hkDefaults, LAST_FILE_SET, 0, REG_MULTI_SZ,
                          (LPBYTE) &abEmptyStringSet, 2
                         );

   if (lResult != ERROR_SUCCESS) goto registry_access_error;

   // Finally, we'll force our registry data out to disk via the
   // flush key api:

   lResult= RegFlushKey(hkGlobal);

   // Then we'll write out the REG_INSTALLED flag. Note that its
   // value is unimportant. Only its existence matters.

   fInstalled= TRUE;

   lResult= RegSetValueEx(hkGlobal, REG_INSTALLED, 0, REG_DWORD,
                          (LPBYTE) &fInstalled, sizeof(fInstalled)
                         );

   if (lResult != ERROR_SUCCESS) goto registry_access_error;

   RegCloseKey(hkGlobal);

   RegCloseKey(hkDefaults);

   FreeSid(psidAdmins);

   return TRUE;

registry_access_error:

   MPError(hwnd, MB_OK | MB_ICONHAND, IDS_REG_ACCESS_ERROR, NULL);

   // We've constructed some, but not all of the global key state.
   // So we must remove any keys we created. The Defaults key must
   // be deleted first before the Global key can be deleted.

   if (hkDefaults) RegDeleteKey(hkGlobal, DEFAULTS_PATH);

   if (hkGlobal) RegDeleteKey(HKEY_LOCAL_MACHINE, pszPathBuff);

   goto clean_up_after_failure;

memory_limited:

   MPError(hwnd, MB_OK | MB_ICONHAND, IDS_MEMORY_LIMITED, NULL);
   goto clean_up_after_failure;

security_failure:

   MPError(hwnd, MB_OK | MB_ICONHAND, IDS_SECURITY_FAIL_I, NULL);

clean_up_after_failure:

   if (psidAdmins  ) FreeSid(psidAdmins  );
   if (psidEveryone) FreeSid(psidEveryone);

   return FALSE;
}

PSID GetCurrentUserInfo()
{
   // This function returns security information about the person who owns
   // this thread.

   HANDLE htkThread;

   TOKEN_USER *ptu;
   DWORD      cbtu;

   TOKEN_GROUPS *ptg = NULL;
   SID_IDENTIFIER_AUTHORITY SystemSidAuthority= SECURITY_NT_AUTHORITY;

   // First we must open a handle to the access token for this thread.

   if (!OpenThreadToken(GetCurrentThread(), TOKEN_QUERY, FALSE, &htkThread))
      if (GetLastError() == ERROR_NO_TOKEN)
      {
         // If the thread does not have an access token, we'll examine the
         // access token associated with the process.

         if (!OpenProcessToken(GetCurrentProcess(), TOKEN_QUERY, &htkThread))
         return NULL;
      }
      else return NULL;


   if (GetTokenInformation(htkThread, TokenUser, NULL, 0, &cbtu))
      return NULL;

   // Here we verify that GetTokenInformation failed for lack of a large
   // enough buffer.

   if (GetLastError() != ERROR_INSUFFICIENT_BUFFER)
      return NULL;

   // Now we allocate a buffer for the group information.
   // Since _alloca allocates on the stack, we don't have
   // to explicitly deallocate it. That happens automatically
   // when we exit this function.

   if (!(ptu= LocalAlloc(LPTR, cbtu))) return NULL;

   // Now we ask for the user information again.
   // This may fail if an administrator has changed SID information
   // for this user.

   if (!GetTokenInformation(htkThread, TokenUser, ptu, cbtu, &cbtu))
      return FALSE;

// if (GetTokenInformation(htkThread, TokenUser, &tu, sizeof(tu), &cbtu))
//    return NULL;

   return ptu;
}

BOOL InitUser(HKEY hkGlobal, PSZ pszPathBuff)
{
   // This function sets up the per-user key area for a new user.
   // It will be called the very first time a user runs the application.

   // The initial per-user information is copied over from a set of defaults
   // stored in the global key area.

   // We assume that hkGlobal is a registry key for the global area
   // used by this application. We assume pszPathBuff defines where
   // the per-user data should be stored in the CURRENT_USER tree.

   // We also assume that hmtxRegPerUser is held when this function is called.

   HKEY hkPerUser  = NULL;
   HKEY hkDefaults = NULL;

   BOOL fInstalled= FALSE;

   LONG lResult;

   DWORD dwType, cbData;

   PSZ pszFileList;

   DWORD dwDisposition;

   TOKEN_USER *ptu = NULL;

   PSID psidUser   = NULL,
        psidAdmins = NULL;

   PACL  paclKey = NULL;

   BOOL fWordWrap;
   PSZ  pszFileSet = NULL;

   SID_IDENTIFIER_AUTHORITY SystemSidAuthority= SECURITY_NT_AUTHORITY;

   SECURITY_ATTRIBUTES sa;
   SECURITY_DESCRIPTOR sdPermissions;


   // First we'll setup the security attributes we're going to
   // use with the application's global key.

   sa.nLength              = sizeof(SECURITY_ATTRIBUTES);
   sa.bInheritHandle       = FALSE;
   sa.lpSecurityDescriptor = &sdPermissions;

   // Here we're creating a System Identifier (SID) to represent
   // the Admin group.

   if (!AllocateAndInitializeSid
          (&SystemSidAuthority, 2, SECURITY_BUILTIN_DOMAIN_RID,
                                   DOMAIN_ALIAS_RID_ADMINS,
                                   0, 0, 0, 0, 0, 0,
                                   &psidAdmins
          )
      )
      goto security_failure;

   // We also need a SID for the current user.

   if (   !(ptu= GetCurrentUserInfo())
       || !(psidUser= ptu->User.Sid)
      ) goto security_failure;

   if (!InitializeSecurityDescriptor(&sdPermissions,
                                     SECURITY_DESCRIPTOR_REVISION1
                                    )
      )
      goto security_failure;

   // We want the current user to own this key.

   if (!SetSecurityDescriptorOwner(&sdPermissions, psidUser, 0))
      goto security_failure;

   // Finally we must allocate and construct the discretionary
   // access control list (DACL) for the key.

   // Note that _alloca allocates memory on the stack frame
   // which will automatically be deallocated when this routine
   // exits.

   if (!(paclKey= (PACL) _alloca(ACL_BUFFER_SIZE)))
      goto memory_limited;

   if (!InitializeAcl(paclKey, ACL_BUFFER_SIZE, ACL_REVISION2))
      goto security_failure;

   // Our DACL will two access control entries (ACEs). The first ACE
   // provides full access to the current user. The second ACE gives
   // the Admin group full access. By default all other users will have
   // no access to the key.

   // The reason for admin access is to allow an administrator to
   // run special utilties to cleanup inconsistencies and disasters
   // in the per-user data area.

   if (!AddAccessAllowedAce(paclKey, ACL_REVISION2, KEY_ALL_ACCESS, psidUser))
      goto security_failure;

   if (!AddAccessAllowedAce(paclKey, ACL_REVISION2, KEY_ALL_ACCESS, psidAdmins))
      goto security_failure;

   // We must bind this DACL to the security descriptor...

   if (!SetSecurityDescriptorDacl(&sdPermissions, TRUE, paclKey, FALSE))
      goto security_failure;

   // Now we'll attempt to create the key with the security attributes...

   lResult= RegCreateKeyEx(HKEY_CURRENT_USER, pszPathBuff, 0,
                           "Application Per-User Data", REG_OPTION_NON_VOLATILE,
                           KEY_ALL_ACCESS,
                           &sa, &hkPerUser, &dwDisposition
                          );

   if (lResult != ERROR_SUCCESS) goto registry_access_error;

   // Usually the disposition value will indicate that we've created a
   // new key. Sometimes it may instead state that we've opened an existing
   // key. This can happen when installation is incomplete and interrupted,
   // say by loss of electrical power.

   if (   dwDisposition != REG_CREATED_NEW_KEY
       && dwDisposition != REG_OPENED_EXISTING_KEY
      ) goto registry_access_error;

   // Now we must open the Defaults subkey in the global area.

   lResult= RegOpenKeyEx(hkGlobal, DEFAULTS_PATH, 0, KEY_READ, &hkDefaults);

   if (lResult != ERROR_SUCCESS)
   {
      // Can't open the "Defaults" subkey for read access.
      // This shouldn't happen normally. The algorithmic sequence for
      // installing this application and then creating user profile
      // data should prevent it.

      // It is possible for someone running RegEdit32 to delete the key,
      // however.

      goto registry_damage_error;
   }

   // Now we'll copy two default values to the per-user key:
   //
   //   -- a word-wrap flag
   //   -- a list of file names

   cbData= sizeof(fWordWrap);

   lResult= RegQueryValueEx(hkDefaults, WORD_WRAP_DEFAULT, NULL,
                            &dwType, (LPBYTE) &fWordWrap, &cbData
                           );

   if (   lResult != ERROR_SUCCESS
       || dwType  != REG_DWORD
      ) goto registry_damage_error;


   lResult= RegSetValueEx(hkPerUser, WORD_WRAP_DEFAULT, 0, REG_DWORD,
                          (LPBYTE) &fWordWrap, sizeof(fWordWrap)
                         );

   if (lResult != ERROR_SUCCESS) goto registry_access_error;

   cbData= 0;

   lResult= RegQueryValueEx(hkDefaults, LAST_FILE_SET, NULL, &dwType,
                            NULL, &cbData
                           );

   if (   lResult != ERROR_SUCCESS
       || dwType != REG_MULTI_SZ
      )
     goto registry_damage_error;

   pszFileList= (PSZ) _alloca(cbData);

   if (!pszFileList) goto memory_limited;

   lResult= RegQueryValueEx(hkDefaults, LAST_FILE_SET, NULL, &dwType,
                            (LPBYTE) pszFileList, &cbData
                           );

   if (lResult != ERROR_SUCCESS) goto registry_damage_error;

   lResult= RegSetValueEx(hkPerUser, LAST_FILE_SET, 0, REG_MULTI_SZ,
                          (LPBYTE) pszFileList, cbData
                         );

   if (lResult != ERROR_SUCCESS) goto registry_access_error;

   // Now we force our registry subtree out to disk
   // via the flush key api:

   lResult= RegFlushKey(hkPerUser);

   // Finally we store the REG_INSTALLED value in the registry to
   // indicate that installation has completed. Note that its value
   // is irrelevant. Only its presence or absence is meaningful.

   fInstalled= TRUE;

   lResult= RegSetValueEx(hkPerUser, REG_INSTALLED, 0, REG_DWORD,
                          (LPBYTE) &fInstalled, sizeof(fInstalled)
                         );

   RegCloseKey(hkPerUser);
   RegCloseKey(hkDefaults);

   FreeSid(psidAdmins);

   LocalFree(ptu);

   return(TRUE);

registry_damage_error:

   // We'll display a warning that the registry info has
   // been damaged.

   MPError(hwndFrame, MB_OK | MB_ICONHAND, IDS_MUTEX_LOGIC_ERR, NULL);

   // Then we discard the REG_INSTALLED flag to insure that a reinstallation
   // can proceed.

   RegDeleteValue(hkGlobal, REG_INSTALLED);

   goto clean_up_registry_keys;

registry_access_error:

   MPError(hwndFrame, MB_OK | MB_ICONHAND, IDS_REG_ACCESS_ERROR, NULL);

clean_up_registry_keys:

   // We've constructed some, but not all of the global key state.
   // So we must remove any keys we created. The Defaults key must
   // be deleted first before the Global key can be deleted.

   if (hkPerUser) RegDeleteKey(HKEY_CURRENT_USER, pszPathBuff);

   if (hkDefaults) RegCloseKey(hkDefaults);

   goto clean_up_after_failure;

memory_limited:

   MPError(hwndFrame, MB_OK | MB_ICONHAND, IDS_MEMORY_LIMITED, NULL);
   goto clean_up_after_failure;

security_failure:

   MPError(hwndFrame, MB_OK | MB_ICONHAND, IDS_SECURITY_FAIL_I, NULL);

clean_up_after_failure:

   if (psidAdmins) FreeSid(psidAdmins  );
   if (ptu       ) LocalFree(psidUser);

   return FALSE;
}

BOOL CreateAppKeys()
{
   long lResult;
   BOOL fSuccess;
   BYTE abPathBuffer[MAX_PATH];
   BYTE abMutexName [MAX_PATH];

   BOOL  fInstalled= FALSE;
   DWORD dwType, cbData;

   // Here we're constructing registry key handles for global data and
   // per-user data. The global data is kept in the HKEY_LOCAL_MACHINE
   // tree, and the per-user data is kept in the HKEY_CURRENT_USER tree.
   // For both trees the data for this program is kept in the same
   // relative location.

   // The registry handles are returned in the global variables hkGlobal
   // and hkPerUser. In addition two global mutex handles (hmtxRegGlobal
   // and hmtxRegPerUser are created. The mutexes are used to serialize
   // registry accesses among instances of this application at start-up.
   // That serialization is necessary to insure that a complete registry
   // environment is present when the application starts.

   // Note that individual registry reads and writes do not need to be
   // serialized -- only collections of reads and writes which must be
   // consistent with each other.

   // Note all so the use of the registry value REG_INSTALLED. It is the
   // last value written to the HKEY_LOCAL_MACHINE and HKEY_CURRENT_USER
   // registry tree during the installation sequence. Whenever this application
   // starts, it looks for REG_INSTALLED as a sign that the registry has
   // been properly setup. If it doesn't find it, we assume that either
   // setup hasn't been done or has been done incompletely.

   // First we'll construct a relative path to the keys we're going to
   // open. The path has the structure:

   //    Software \ <Company Name> \ <Application Name> \ <Version Number>

   wsprintf(abPathBuffer, "Software\\%s\\%s\\%s",
            COMPANY_NAME, APPLICATION_NAME, VERSION_NUMBER
           );

   // Since two instance of this application could be running simultaneously,
   // we use a named mutext to serialize registry accesses.

   wsprintf(abMutexName, "Software/%s/%s/%s/Globals",
            COMPANY_NAME, APPLICATION_NAME, VERSION_NUMBER
           );

   if (!(hmtxRegGlobal= CreateMutex(NULL, FALSE, abMutexName))) goto failure_exit;

   wsprintf(abMutexName, "Software/%s/%s/%s/PerUser",
            COMPANY_NAME, APPLICATION_NAME, VERSION_NUMBER
           );

   if (!(hmtxRegPerUser= CreateMutex(NULL, FALSE, abMutexName))) goto failure_exit;


   // First we'll attempt to open a key to the global data...

   for (lResult= ~ERROR_SUCCESS; lResult != ERROR_SUCCESS; )
   {
      // We serialize the code in this loop via hmtxRegGlobal.

      lResult= WaitForSingleObject(hmtxRegGlobal, 0xFFFFFFFF);

      if (   lResult != WAIT_ABANDONED
          && lResult != WAIT_OBJECT_0
         ) goto failure_exit;

      lResult= RegOpenKeyEx(HKEY_LOCAL_MACHINE, abPathBuffer, 0, KEY_READ,
                                                &hkGlobal
                           );

      // Note that we also look for the REG_INSTALLED flag.

      cbData= sizeof(fInstalled);

      if (   ERROR_SUCCESS != lResult
          || ERROR_SUCCESS != RegQueryValueEx(hkGlobal, REG_INSTALLED, 0,
                                              &dwType, (LPBYTE) &fInstalled,
                                              &cbData
                                             )
         )
      {
         hkGlobal= NULL;

         // If we can't open the global key, this probably means that the
         // application hasn't been installed yet. So we'll try to install it.

         // If the installation succeeds, we'll try opening the global key
         // again. Otherwise we'll just fail.

         fSuccess= InstallApp(abPathBuffer);

         ReleaseMutex(hmtxRegGlobal);

         if (fSuccess) continue;
         else goto failure_exit;
      }

      ReleaseMutex(hmtxRegGlobal);
   }

   for (lResult= ~ERROR_SUCCESS; lResult != ERROR_SUCCESS; )
   {
      // We serialize the code in this loop via hmtxRegPerUser.

      lResult= WaitForSingleObject(hmtxRegPerUser, 0xFFFFFFFF);

      if (   lResult != WAIT_ABANDONED
          && lResult != WAIT_OBJECT_0
         ) goto failure_exit;

      // Now we'll try to open an handle to the per-user key for this user and
      // this application.

      lResult= RegOpenKeyEx(HKEY_CURRENT_USER, abPathBuffer, 0, KEY_ALL_ACCESS,
                                               &hkPerUser
                           );

      // Note that we also look for the REG_INSTALLED flag.

      cbData= sizeof(fInstalled);

      if (   ERROR_SUCCESS != lResult
          || ERROR_SUCCESS != RegQueryValueEx(hkPerUser, REG_INSTALLED, 0,
                                              &dwType, (LPBYTE) &fInstalled,
                                              &cbData
                                             )
         )
      {
         // The per-user open call failed. We infer that this is the first
         // time this user has invoked this application. So next we'll try
         // to initial a per-user area for them.

         hkPerUser= NULL;

         fSuccess= InitUser(hkGlobal, abPathBuffer);

         ReleaseMutex(hmtxRegPerUser);

         if (fSuccess) continue;
         else goto failure_exit;
      }

      ReleaseMutex(hmtxRegPerUser);
   }

   return TRUE;

failure_exit:

   // When we're exiting because of a failure, we must clean up
   // by closing any handles we've created along the way.

   if (hmtxRegGlobal) CloseHandle(hmtxRegGlobal);

   if (hmtxRegPerUser) CloseHandle(hmtxRegPerUser);

   if (hkGlobal) RegCloseKey(hkGlobal);

   return FALSE;
}

BOOL LoadConfiguration()
{
   // This routine loads the per-user configuration data.

   // Two items are kept as configuration data:
   //
   //   fTextWrapDefault -- a BOOL which defines whether the text windows
   //                       fold text at the right edge of the window.
   //
   //   A REG_MULTI_SZ list of file names.
   //
   //     This list represents the files which were open at the end of the
   //     last RegMPad session. We'll attempt to reopen those files.

   LONG  lResult, cbData;
   DWORD dwType;
   PSZ   pszFileList= NULL;

   CHAR *pc;

   cbData= sizeof(fTextWrapDefault);

   lResult= RegQueryValueEx(hkPerUser, WORD_WRAP_DEFAULT, NULL,
                            &dwType, (LPBYTE) &fTextWrapDefault, &cbData
                           );

   if (lResult != ERROR_SUCCESS) return FALSE;

   cbData= 0;

   lResult= RegQueryValueEx(hkPerUser, LAST_FILE_SET, NULL, &dwType,
                            NULL, &cbData
                           );

   if (   lResult != ERROR_SUCCESS
       || dwType  != REG_MULTI_SZ
      ) return FALSE;

   pszFileList= (PSZ) _alloca(cbData);

   if (!pszFileList) return FALSE;

   lResult= RegQueryValueEx(hkPerUser, LAST_FILE_SET, NULL, &dwType,
                            (LPBYTE) pszFileList, &cbData
                           );

   if (lResult != ERROR_SUCCESS) return FALSE;

   for (pc= pszFileList; *pc; )
   {
      if (!AlreadyOpen(pc)) AddFile(pc);

      for (; *pc++; );
   }

   return TRUE;
}

BOOL SaveConfiguration()
{
   // This routine saves the per-user configuration data to the registry.
   // That data consists of two items:
   //
   //   fTextWrapDefault -- a BOOL which defines whether the text windows
   //                       fold text at the right edge of the window.
   //
   //   A REG_MULTI_SZ list of file names.
   //
   //     This list represents the files which were open at the end of the
   //     last RegMPad session.

   LONG  lResult;
   HWND  hwnd;
   PBYTE pb, pbNext;
   LONG  cb, cbTotal;

   lResult= RegSetValueEx(hkPerUser, WORD_WRAP_DEFAULT, 0, REG_DWORD,
                          (CONST LPBYTE) &fTextWrapDefault,
                          sizeof(fTextWrapDefault)
                         );

   if (lResult != ERROR_SUCCESS) return FALSE;

   for (hwnd= GetWindow(hwndMDIClient, GW_CHILD), cbTotal= 1;
        hwnd;
        hwnd= GetWindow(hwnd, GW_HWNDNEXT)
       )
   {
      // Skip if this is an icon title window...

      if (GetWindow(hwnd, GW_OWNER)) continue;

      if (GetWindowWord(hwnd, GWW_UNTITLED)) continue;

      cbTotal += GetWindowTextLength(hwnd) + 1;
   }

   pb= (PBYTE) _alloca(cbTotal);

   if (!pb) return FALSE;

   for (hwnd= GetWindow(hwndMDIClient, GW_CHILD), pbNext= pb;
        hwnd;
        hwnd= GetWindow(hwnd, GW_HWNDNEXT)
       )
   {
      // Skip if this is an icon title window...

      if (GetWindow(hwnd, GW_OWNER)) continue;

      if (GetWindowWord(hwnd, GWW_UNTITLED)) continue;

      cb= GetWindowTextLength(hwnd);

      GetWindowText(hwnd, pbNext, cb+1);

      pbNext+= cb+1;
   }

   *pbNext= 0;

   lResult= RegSetValueEx(hkPerUser, LAST_FILE_SET, 0, REG_MULTI_SZ,
                          pb, cbTotal
                         );

   return (lResult == ERROR_SUCCESS)? TRUE : FALSE;
}
