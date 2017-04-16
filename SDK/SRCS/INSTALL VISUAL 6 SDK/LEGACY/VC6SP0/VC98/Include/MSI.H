/*****************************************************************************\
*                                                                             *
* msi.h - - Interface for external access to Installer Service                *
*                                                                             *
* Version 0.20                                                                *
*                                                                             *
* NOTES:  All buffers sizes are TCHAR count, null included only on input      *
*         Return argument pointers may be null if not interested in value     *
*                                                                             *
* Copyright (c) 1997, Microsoft Corp.      All rights reserved.               *
*                                                                             *
\*****************************************************************************/

#ifndef _MSI_H_
#define _MSI_H_

// --------------------------------------------------------------------------
// Installer generic handle definitions
// --------------------------------------------------------------------------

typedef unsigned long MSIHANDLE;     // abstract generic handle, 0 == no handle

#ifdef __cplusplus
extern "C" {
#endif

// Close a open handle of any type
// All handles obtained from API calls must be closed when no longer needed
// Normally succeeds, returning TRUE. 

UINT WINAPI MsiCloseHandle(MSIHANDLE hAny);

// Close all handles open in the process, a diagnostic call
// This should NOT be used as a cleanup mechanism -- use PMSIHANDLE class
// Can be called at termination to assure that all handles have been closed
// Returns 0 if all handles have been close, else number of open handles

UINT WINAPI MsiCloseAllHandles();

#ifdef __cplusplus
}
#endif

#ifdef __cplusplus

// C++ wrapper object to automatically free handle when going out of scope

class PMSIHANDLE
{
	MSIHANDLE m_h;
 public:
	PMSIHANDLE():m_h(0){}
	PMSIHANDLE(MSIHANDLE h):m_h(h){}
  ~PMSIHANDLE(){if (m_h!=0) MsiCloseHandle(m_h);}
	void operator =(MSIHANDLE h) {if (m_h) MsiCloseHandle(m_h); m_h=h;}
	operator MSIHANDLE() {return m_h;}
	MSIHANDLE* operator &() {if (m_h) MsiCloseHandle(m_h); m_h = 0; return &m_h;}
};
#endif  //__cplusplus

// Install message type for callback is a combination of the following:
//  A message box style:      MB_*, where MB_OK is the default
//  A message box icon type:  MB_ICON*, where no icon is the default
//  A default button:         MB_DEFBUTTON?, where MB_DEFBUTTON1 is the default
//  One of the following install message types, no default
typedef enum tagINSTALLMESSAGE
{
	INSTALLMESSAGE_OUTOFMEMORY = 0x00000000L, // out of memory message
	INSTALLMESSAGE_ERROR       = 0x01000000L, // formatted error message
	INSTALLMESSAGE_WARNING     = 0x02000000L, // formatted warning message
	INSTALLMESSAGE_USER        = 0x03000000L, // user request message
	INSTALLMESSAGE_INFO        = 0x04000000L, // informative message for log
	INSTALLMESSAGE_DIAGNOSTIC  = 0x05000000L, // debug notification, display if no log
	INSTALLMESSAGE_COMMONDATA  = 0x06000000L, // product info for dialog: language Id, dialog caption
	INSTALLMESSAGE_RESERVED    = 0x07000000L, // reserved for future use
	INSTALLMESSAGE_ACTIONSTART = 0x08000000L, // start of action: action name & description
	INSTALLMESSAGE_ACTIONDATA  = 0x09000000L, // formatted data associated with individual action item
	INSTALLMESSAGE_PROGRESS    = 0x0A000000L, // progress gauge info: units so far, total
	INSTALLMESSAGE_ACTIONDONE  = 0x0B000000L, // end of action sequence, exit modeless dialog
} INSTALLMESSAGE;

// external error handler supplied to installation API functions

typedef int (*INSTALLUI_HANDLERA)(LPVOID pvContext, UINT iMessageType, LPCSTR szMessage);
typedef int (*INSTALLUI_HANDLERW)(LPVOID pvContext, UINT iMessageType, LPCWSTR szMessage);
#ifdef UNICODE
#define INSTALLUI_HANDLER  INSTALLUI_HANDLERW
#else
#define INSTALLUI_HANDLER  INSTALLUI_HANDLERA
#endif // !UNICODE

typedef enum tagINSTALLUILEVEL
{
	INSTALLUILEVEL_NOCHANGE = 0,   // UI level is unchanged
	INSTALLUILEVEL_DEFAULT  = 1,   // default UI is used
	INSTALLUILEVEL_NONE     = 2,   // completely silent installation
	INSTALLUILEVEL_BASIC    = 3,   // simple progress and error handling
	INSTALLUILEVEL_REDUCED  = 4,   // authored UI, wizard dialogs suppressed
	INSTALLUILEVEL_FULL     = 5,   // authored UI with wizards, progress, errors
	
} INSTALLUILEVEL;

typedef enum tagINSTALLSTATE
{
	INSTALLSTATE_BADCONFIG    = -6,  // configuration data corrupt
	INSTALLSTATE_INCOMPLETE   = -5,  // installation suspended or in progress
	INSTALLSTATE_SOURCEABSENT = -4,  // run from source, source is unavailable
	INSTALLSTATE_MOREDATA     = -3,  // return buffer overflow
	INSTALLSTATE_INVALIDARG   = -2,  // invalid function argument
	INSTALLSTATE_UNKNOWN      = -1,  // unrecognized product or feature
	INSTALLSTATE_BROKEN       =  0,  // broken
	INSTALLSTATE_ADVERTISED   =  1,  // advertised
	INSTALLSTATE_ABSENT       =  2,  // uninstalled
	INSTALLSTATE_LOCAL        =  3,  // installed on local drive
	INSTALLSTATE_SOURCE       =  4,  // run from source, CD or net
	INSTALLSTATE_DEFAULT      =  5,  // use default, local or source
} INSTALLSTATE;

typedef enum tagUSERINFOSTATE
{
	USERINFOSTATE_MOREDATA   = -3,  // return buffer overflow
	USERINFOSTATE_INVALIDARG = -2,  // invalid function argument
	USERINFOSTATE_UNKNOWN    = -1,  // unrecognized product
	USERINFOSTATE_ABSENT     =  0,  // user info and PID not initialized
	USERINFOSTATE_PRESENT    =  1,  // user info and PID initialized
} USERINFOSTATE;

typedef enum tagINSTALLLEVEL
{
	INSTALLLEVEL_DEFAULT = 0,      // install authored default
	INSTALLLEVEL_MINIMUM = 1,      // install only required features
	INSTALLLEVEL_MAXIMUM = 0xFFFF, // install all features
} INSTALLLEVEL;                   // intermediate levels dependent on authoring

typedef enum tagREINSTALLMODE  // bit flags
{
	REINSTALLMODE_REPAIR           = 0x00000001,  // repair any defects encountered
	REINSTALLMODE_FILEMISSING      = 0x00000002,  // Reinstall only if file is missing
	REINSTALLMODE_FILEOLDERVERSION = 0x00000004,  // Reinstall if file is missing, or older version
	REINSTALLMODE_FILEEQUALVERSION = 0x00000008,  // Reinstall if file is missing, or equal or older version
	REINSTALLMODE_FILEEXACT        = 0x00000010,  // Reinstall if file is missing, or not exact version
	REINSTALLMODE_FILEVERIFY       = 0x00000020,  // checksum executables, reinstall if missing or corrupt
	REINSTALLMODE_FILEREPLACE      = 0x00000040,  // Reinstall all files, regardless of version
	REINSTALLMODE_MACHINEDATA      = 0x00000080,  // insure required machine reg entries
	REINSTALLMODE_USERDATA         = 0x00000100,  // insure required user reg entries
	REINSTALLMODE_SHORTCUT         = 0x00000200,  // validate shortcuts and progman items
} REINSTALLMODE;

typedef enum tagINSTALLOGMODE  // bit flags
{
	INSTALLLOGMODE_OUTOFMEMORY  = (1 << (INSTALLMESSAGE_OUTOFMEMORY >> 24)),
	INSTALLLOGMODE_ERROR        = (1 << (INSTALLMESSAGE_ERROR       >> 24)),
	INSTALLLOGMODE_WARNING      = (1 << (INSTALLMESSAGE_WARNING     >> 24)),
	INSTALLLOGMODE_USER         = (1 << (INSTALLMESSAGE_USER        >> 24)),
	INSTALLLOGMODE_INFO         = (1 << (INSTALLMESSAGE_INFO        >> 24)),
	INSTALLLOGMODE_DIAGNOSTIC   = (1 << (INSTALLMESSAGE_DIAGNOSTIC  >> 24)),
	INSTALLLOGMODE_COMMONDATA   = (1 << (INSTALLMESSAGE_COMMONDATA  >> 24)),
	INSTALLLOGMODE_RESERVED     = (1 << (INSTALLMESSAGE_RESERVED    >> 24)),
	INSTALLLOGMODE_ACTIONSTART  = (1 << (INSTALLMESSAGE_ACTIONSTART >> 24)),
	INSTALLLOGMODE_ACTIONDATA   = (1 << (INSTALLMESSAGE_ACTIONDATA  >> 24)),
	INSTALLLOGMODE_PROPERTYDUMP = (1 << (INSTALLMESSAGE_PROGRESS    >> 24)),
} INSTALLLOGMODE;

typedef enum tagINSTALLFEATUREATTRIBUTE // bit flags
{
	INSTALLFEATUREATTRIBUTE_FAVORLOCAL   = 0x00000001,
	INSTALLFEATUREATTRIBUTE_FAVORSOURCE  = 0x00000002,
	INSTALLFEATUREATTRIBUTE_FOLLOWPARENT = 0x00000004,
} INSTALLFEATUREATTRIBUTE;


typedef enum tagINSTALLSOURCEACTION
{
	INSTALLSOURCEACTION_ADD          =  1,  // add source to list
	INSTALLSOURCEACTION_REMOVE       =  2,  // remove source from list
	INSTALLSOURCEACTION_REMOVEALL    =  3,  // flush entire sourcelist key
	INSTALLSOURCEACTION_REMOVEALLNET =  4,  // flush all network sources
	INSTALLSOURCEACTION_REMOVEALLURL =  5,  // flush all URL sources
	INSTALLSOURCEACTION_ENABLECD     =  6,  // enable searching on CD sources
	INSTALLSOURCEACTION_DISABLECD    =  7,  // disable searching on CD sources
} INSTALLSOURCEACTION;


#define MAX_FEATURE_CHARS  38   // maximum chars in feature name (same as string GUID)


// Product info attributes: advertised information

#define INSTALLPROPERTY_TRANSFORMS            __TEXT("Transforms")
#define INSTALLPROPERTY_LANGUAGE              __TEXT("Language")
#define INSTALLPROPERTY_PRODUCTNAME           __TEXT("ProductName")

// Product info attributes: installed information

#define INSTALLPROPERTY_INSTALLEDPRODUCTNAME  __TEXT("InstalledProductName")
#define INSTALLPROPERTY_VERSIONSTRING         __TEXT("VersionString")
#define INSTALLPROPERTY_HELPLINK              __TEXT("HelpLink")
#define INSTALLPROPERTY_HELPTELEPHONE         __TEXT("HelpTelephone")
#define INSTALLPROPERTY_INSTALLLOCATION       __TEXT("InstallLocation")
#define INSTALLPROPERTY_INSTALLSOURCE         __TEXT("InstallSource")
#define INSTALLPROPERTY_INSTALLDATE           __TEXT("InstallDate")
#define INSTALLPROPERTY_PUBLISHER             __TEXT("Publisher")
#define INSTALLPROPERTY_LOCALPACKAGE          __TEXT("LocalPackage")
#define INSTALLPROPERTY_URLINFOABOUT          __TEXT("URLInfoAbout")
#define INSTALLPROPERTY_URLUPDATEINFO         __TEXT("URLUpdateInfo")
#define INSTALLPROPERTY_VERSIONMINOR          __TEXT("VersionMinor")
#define INSTALLPROPERTY_VERSIONMAJOR          __TEXT("VersionMajor")



#ifdef __cplusplus
extern "C" {
#endif

// --------------------------------------------------------------------------
// Functions to set the UI handling and logging. The UI will be used for error,
// progress, and log messages for all subsequent calls to Installer Service
// API functions that require UI.
// --------------------------------------------------------------------------

// Enable internal UI

INSTALLUILEVEL WINAPI MsiSetInternalUI(
	INSTALLUILEVEL  dwUILevel,     // UI level
	HWND  *phWnd);                   // handle of owner window

// Enable external UI

INSTALLUI_HANDLERA WINAPI MsiSetExternalUIA(
	INSTALLUI_HANDLERA puiHandler,   // for progress and error handling 
	DWORD              dwMessageFilter, // bit flags designating messages to handle
	LPVOID             pvContext);   // application context
INSTALLUI_HANDLERW WINAPI MsiSetExternalUIW(
	INSTALLUI_HANDLERW puiHandler,   // for progress and error handling 
	DWORD              dwMessageFilter, // bit flags designating messages to handle
	LPVOID             pvContext);   // application context
#ifdef UNICODE
#define MsiSetExternalUI  MsiSetExternalUIW
#else
#define MsiSetExternalUI  MsiSetExternalUIA
#endif // !UNICODE


// Enable logging to a file or extern UI handler for the client process,
// with control over which log messages are passed to the file or handler

UINT WINAPI MsiEnableLogA(
	DWORD     dwLogMode,   // bit flags designating operations to report
	LPCSTR  szLogFile,   // log file, or NULL to direct to external handler
	BOOL      fAppend);    // TRUE to append to existing file, FALSE to replace
UINT WINAPI MsiEnableLogW(
	DWORD     dwLogMode,   // bit flags designating operations to report
	LPCWSTR  szLogFile,   // log file, or NULL to direct to external handler
	BOOL      fAppend);    // TRUE to append to existing file, FALSE to replace
#ifdef UNICODE
#define MsiEnableLog  MsiEnableLogW
#else
#define MsiEnableLog  MsiEnableLogA
#endif // !UNICODE

// --------------------------------------------------------------------------
// Functions to query and configure a product as a whole.
// A component descriptor string may be used instead of the product code.
// --------------------------------------------------------------------------

// Return the installed state for a product

INSTALLSTATE WINAPI MsiQueryProductStateA(
	LPCSTR  szProduct);
INSTALLSTATE WINAPI MsiQueryProductStateW(
	LPCWSTR  szProduct);
#ifdef UNICODE
#define MsiQueryProductState  MsiQueryProductStateW
#else
#define MsiQueryProductState  MsiQueryProductStateA
#endif // !UNICODE

// Return product info

UINT WINAPI MsiGetProductInfoA(
	LPCSTR   szProduct,      // product code, string GUID, or descriptor
	LPCSTR   szAttribute,    // attribute name, case-sensitive
	LPSTR    lpValueBuf,     // returned value, NULL if not desired
	DWORD      *pcchValueBuf); // in/out buffer character count
UINT WINAPI MsiGetProductInfoW(
	LPCWSTR   szProduct,      // product code, string GUID, or descriptor
	LPCWSTR   szAttribute,    // attribute name, case-sensitive
	LPWSTR    lpValueBuf,     // returned value, NULL if not desired
	DWORD      *pcchValueBuf); // in/out buffer character count
#ifdef UNICODE
#define MsiGetProductInfo  MsiGetProductInfoW
#else
#define MsiGetProductInfo  MsiGetProductInfoA
#endif // !UNICODE

// Install a new product.
// Either may be NULL, but the DATABASE property must be specfied

UINT WINAPI MsiInstallProductA(
	LPCSTR      szPackagePath,    // location of package to install
	LPCSTR      szCommandLine);   // command line <property settings>
UINT WINAPI MsiInstallProductW(
	LPCWSTR      szPackagePath,    // location of package to install
	LPCWSTR      szCommandLine);   // command line <property settings>
#ifdef UNICODE
#define MsiInstallProduct  MsiInstallProductW
#else
#define MsiInstallProduct  MsiInstallProductA
#endif // !UNICODE

// Install/uninstall an advertised or installed product
// No action if installed and INSTALLSTATE_DEFAULT specified

UINT WINAPI MsiConfigureProductA(
	LPCSTR      szProduct,        // product code OR descriptor
	int          iInstallLevel,    // how much of the product to install
	INSTALLSTATE eInstallState);   // local/source/default/absent/lock/uncache
UINT WINAPI MsiConfigureProductW(
	LPCWSTR      szProduct,        // product code OR descriptor
	int          iInstallLevel,    // how much of the product to install
	INSTALLSTATE eInstallState);   // local/source/default/absent/lock/uncache
#ifdef UNICODE
#define MsiConfigureProduct  MsiConfigureProductW
#else
#define MsiConfigureProduct  MsiConfigureProductA
#endif // !UNICODE

// Reinstall product, used to validate or correct problems

UINT WINAPI MsiReinstallProductA(
	LPCSTR      szProduct,        // product code OR descriptor
	DWORD         szReinstallMode); // one or more REINSTALLMODE modes
UINT WINAPI MsiReinstallProductW(
	LPCWSTR      szProduct,        // product code OR descriptor
	DWORD         szReinstallMode); // one or more REINSTALLMODE modes
#ifdef UNICODE
#define MsiReinstallProduct  MsiReinstallProductW
#else
#define MsiReinstallProduct  MsiReinstallProductA
#endif // !UNICODE

// Return the product code for a registered component, called once by apps

UINT WINAPI MsiGetProductCodeA(
	LPCSTR   szComponent,   // component Id registered for this product
	LPSTR    lpBuf39);      // returned string GUID, sized for 39 characters
UINT WINAPI MsiGetProductCodeW(
	LPCWSTR   szComponent,   // component Id registered for this product
	LPWSTR    lpBuf39);      // returned string GUID, sized for 39 characters
#ifdef UNICODE
#define MsiGetProductCode  MsiGetProductCodeW
#else
#define MsiGetProductCode  MsiGetProductCodeA
#endif // !UNICODE

// Return the registered user information for an installed product

USERINFOSTATE WINAPI MsiGetUserInfoA(
	LPCSTR  szProduct,        // product code, string GUID
	LPSTR   lpUserNameBuf,    // return user name           
	DWORD    *pcchUserNameBuf, // in/out buffer character count
	LPSTR   lpOrgNameBuf,     // return company name           
	DWORD    *pcchOrgNameBuf,  // in/out buffer character count
	LPSTR   lpSerialBuf,      // return product serial number
	DWORD    *pcchSerialBuf);  // in/out buffer character count
USERINFOSTATE WINAPI MsiGetUserInfoW(
	LPCWSTR  szProduct,        // product code, string GUID
	LPWSTR   lpUserNameBuf,    // return user name           
	DWORD    *pcchUserNameBuf, // in/out buffer character count
	LPWSTR   lpOrgNameBuf,     // return company name           
	DWORD    *pcchOrgNameBuf,  // in/out buffer character count
	LPWSTR   lpSerialBuf,      // return product serial number
	DWORD    *pcchSerialBuf);  // in/out buffer character count
#ifdef UNICODE
#define MsiGetUserInfo  MsiGetUserInfoW
#else
#define MsiGetUserInfo  MsiGetUserInfoA
#endif // !UNICODE

// Obtain and store user info and PID from installation wizard (first run)

UINT WINAPI MsiCollectUserInfoA(
	LPCSTR  szProduct);     // product code, string GUID
UINT WINAPI MsiCollectUserInfoW(
	LPCWSTR  szProduct);     // product code, string GUID
#ifdef UNICODE
#define MsiCollectUserInfo  MsiCollectUserInfoW
#else
#define MsiCollectUserInfo  MsiCollectUserInfoA
#endif // !UNICODE

// --------------------------------------------------------------------------
// Functions to query and configure a feature within a product.
// Separate wrapper functions are provided that accept a descriptor string.
// --------------------------------------------------------------------------

// Return the installed state for a product feature

INSTALLSTATE WINAPI MsiQueryFeatureStateA(
	LPCSTR  szProduct,
	LPCSTR  szFeature);
INSTALLSTATE WINAPI MsiQueryFeatureStateW(
	LPCWSTR  szProduct,
	LPCWSTR  szFeature);
#ifdef UNICODE
#define MsiQueryFeatureState  MsiQueryFeatureStateW
#else
#define MsiQueryFeatureState  MsiQueryFeatureStateA
#endif // !UNICODE

// Indicate intent to use a product feature, increments usage count
// Prompts for CD if not loaded, does not install feature

INSTALLSTATE WINAPI MsiUseFeatureA(
	LPCSTR  szProduct,
	LPCSTR  szFeature);
INSTALLSTATE WINAPI MsiUseFeatureW(
	LPCWSTR  szProduct,
	LPCWSTR  szFeature);
#ifdef UNICODE
#define MsiUseFeature  MsiUseFeatureW
#else
#define MsiUseFeature  MsiUseFeatureA
#endif // !UNICODE

// Return the usage metrics for a product feature

UINT WINAPI MsiGetFeatureUsageA(
	LPCSTR      szProduct,        // product code
	LPCSTR      szFeature,        // feature ID
	DWORD        *pdwUseCount,     // returned use count
	WORD         *pwDateUsed);     // last date used (DOS date format)
UINT WINAPI MsiGetFeatureUsageW(
	LPCWSTR      szProduct,        // product code
	LPCWSTR      szFeature,        // feature ID
	DWORD        *pdwUseCount,     // returned use count
	WORD         *pwDateUsed);     // last date used (DOS date format)
#ifdef UNICODE
#define MsiGetFeatureUsage  MsiGetFeatureUsageW
#else
#define MsiGetFeatureUsage  MsiGetFeatureUsageA
#endif // !UNICODE

// Force the installed state for a product feature

UINT WINAPI MsiConfigureFeatureA(
	LPCSTR  szProduct,
	LPCSTR  szFeature,
	INSTALLSTATE eInstallState);   // local/source/default/absent/lock/uncache
UINT WINAPI MsiConfigureFeatureW(
	LPCWSTR  szProduct,
	LPCWSTR  szFeature,
	INSTALLSTATE eInstallState);   // local/source/default/absent/lock/uncache
#ifdef UNICODE
#define MsiConfigureFeature  MsiConfigureFeatureW
#else
#define MsiConfigureFeature  MsiConfigureFeatureA
#endif // !UNICODE


// Reinstall feature, used to validate or correct problems

UINT WINAPI MsiReinstallFeatureA(
	LPCSTR      szProduct,        // product code
	LPCSTR      szFeature,        // feature ID, NULL for entire product
	DWORD         dwReinstallMode); // one or more REINSTALLMODE modes
UINT WINAPI MsiReinstallFeatureW(
	LPCWSTR      szProduct,        // product code
	LPCWSTR      szFeature,        // feature ID, NULL for entire product
	DWORD         dwReinstallMode); // one or more REINSTALLMODE modes
#ifdef UNICODE
#define MsiReinstallFeature  MsiReinstallFeatureW
#else
#define MsiReinstallFeature  MsiReinstallFeatureA
#endif // !UNICODE

// --------------------------------------------------------------------------
// Functions to return a path to a particular component.
// The state of the feature being used should have been checked previously.
// --------------------------------------------------------------------------

// Return full path to an installed component

INSTALLSTATE WINAPI MsiLocateComponentA(
	LPCSTR szComponent,  // component Id, string GUID
	LPSTR  lpPathBuf,    // returned path
	DWORD   *pcchBuf);    // in/out buffer character count
INSTALLSTATE WINAPI MsiLocateComponentW(
	LPCWSTR szComponent,  // component Id, string GUID
	LPWSTR  lpPathBuf,    // returned path
	DWORD   *pcchBuf);    // in/out buffer character count
#ifdef UNICODE
#define MsiLocateComponent  MsiLocateComponentW
#else
#define MsiLocateComponent  MsiLocateComponentA
#endif // !UNICODE

// Return full component path, performing any necessary installation
// calls MsiQueryFeatureState to detect that all components are installed
// then calls MsiConfigureFeature if any of its components are uninstalled
// then calls MsiLocateComponent to obtain the path the its key file

UINT WINAPI MsiProvideComponentA(
	LPCSTR     szProduct,    // product code in case install required
	LPCSTR     szFeature,    // feature ID in case install required
	LPCSTR     szComponent,  // component ID
	DWORD        dwReserved,   // reserved, must be 0
	LPSTR      lpPathBuf,    // returned path, NULL if not desired
	DWORD       *pcchPathBuf);// in/out buffer character count
UINT WINAPI MsiProvideComponentW(
	LPCWSTR     szProduct,    // product code in case install required
	LPCWSTR     szFeature,    // feature ID in case install required
	LPCWSTR     szComponent,  // component ID
	DWORD        dwReserved,   // reserved, must be 0
	LPWSTR      lpPathBuf,    // returned path, NULL if not desired
	DWORD       *pcchPathBuf);// in/out buffer character count
#ifdef UNICODE
#define MsiProvideComponent  MsiProvideComponentW
#else
#define MsiProvideComponent  MsiProvideComponentA
#endif // !UNICODE

// For an advertised component that registers descriptor strings,
// return full component path, performing any necessary installation.
// If the qualifier is NULL the default component, if present, will 
// be provided. Calls MsiProvideComponentFromDescriptor to install
// and return the path.

UINT WINAPI MsiProvideQualifiedComponentA(
	LPCSTR     szCategory,   // component category ID
	LPCSTR     szQualifier,  // specifies which component to access
	DWORD        dwReserved,   // reserved, must be 0
	LPSTR      lpPathBuf,    // returned path, NULL if not desired
	DWORD       *pcchPathBuf); // in/out buffer character count
UINT WINAPI MsiProvideQualifiedComponentW(
	LPCWSTR     szCategory,   // component category ID
	LPCWSTR     szQualifier,  // specifies which component to access
	DWORD        dwReserved,   // reserved, must be 0
	LPWSTR      lpPathBuf,    // returned path, NULL if not desired
	DWORD       *pcchPathBuf); // in/out buffer character count
#ifdef UNICODE
#define MsiProvideQualifiedComponent  MsiProvideQualifiedComponentW
#else
#define MsiProvideQualifiedComponent  MsiProvideQualifiedComponentA
#endif // !UNICODE

// --------------------------------------------------------------------------
// Functions to iterate registered products, features, and components.
// As with reg keys, they accept a 0-based index into the enumeration.
// --------------------------------------------------------------------------

// Enumerate the registered products, either installed or advertised

UINT WINAPI MsiEnumProductsA(
	DWORD     iProductIndex,    // 0-based index into registered products
	LPSTR   lpProductBuf);    // buffer of char count: 39 (size of string GUID)
UINT WINAPI MsiEnumProductsW(
	DWORD     iProductIndex,    // 0-based index into registered products
	LPWSTR   lpProductBuf);    // buffer of char count: 39 (size of string GUID)
#ifdef UNICODE
#define MsiEnumProducts  MsiEnumProductsW
#else
#define MsiEnumProducts  MsiEnumProductsA
#endif // !UNICODE

// Enumerate the advertised features for a given product.
// If parent is not required, supplying NULL will improve performance.

UINT WINAPI MsiEnumFeaturesA(
	LPCSTR  szProduct,
	DWORD     iFeatureIndex,  // 0-based index into published features
	LPSTR   lpFeatureBuf,   // feature name buffer,   size=MAX_FEATURE_CHARS+1
	LPSTR   lpParentBuf);   // parent feature buffer, size=MAX_FEATURE_CHARS+1
UINT WINAPI MsiEnumFeaturesW(
	LPCWSTR  szProduct,
	DWORD     iFeatureIndex,  // 0-based index into published features
	LPWSTR   lpFeatureBuf,   // feature name buffer,   size=MAX_FEATURE_CHARS+1
	LPWSTR   lpParentBuf);   // parent feature buffer, size=MAX_FEATURE_CHARS+1
#ifdef UNICODE
#define MsiEnumFeatures  MsiEnumFeaturesW
#else
#define MsiEnumFeatures  MsiEnumFeaturesA
#endif // !UNICODE

// Enumerate the installed components for all products

UINT WINAPI MsiEnumComponentsA(
	DWORD    iComponentIndex,  // 0-based index into installed components
	LPSTR   lpComponentBuf);  // buffer of char count: 39 (size of string GUID)
UINT WINAPI MsiEnumComponentsW(
	DWORD    iComponentIndex,  // 0-based index into installed components
	LPWSTR   lpComponentBuf);  // buffer of char count: 39 (size of string GUID)
#ifdef UNICODE
#define MsiEnumComponents  MsiEnumComponentsW
#else
#define MsiEnumComponents  MsiEnumComponentsA
#endif // !UNICODE

// Enumerate the client products for a component

UINT WINAPI MsiEnumClientsA(
	LPCSTR  szComponent,
	DWORD     iProductIndex,    // 0-based index into client products
	LPSTR   lpProductBuf);    // buffer of char count: 39 (size of string GUID)
UINT WINAPI MsiEnumClientsW(
	LPCWSTR  szComponent,
	DWORD     iProductIndex,    // 0-based index into client products
	LPWSTR   lpProductBuf);    // buffer of char count: 39 (size of string GUID)
#ifdef UNICODE
#define MsiEnumClients  MsiEnumClientsW
#else
#define MsiEnumClients  MsiEnumClientsA
#endif // !UNICODE

// Enumerate the qualifiers for an advertised component.

UINT WINAPI MsiEnumComponentQualifiersA(
	LPCSTR   szComponent,         // generic component ID that is qualified
	DWORD     iIndex,	           // 0-based index into qualifiers
	LPSTR    lpQualifierBuf,      // qualifier buffer
	DWORD     *pcchQualifierBuf,   // in/out qualifier buffer character count
	LPSTR    lpDescriptionBuf,    // description buffer
	DWORD     *pcchDescriptionBuf); // in/out description buffer character count
UINT WINAPI MsiEnumComponentQualifiersW(
	LPCWSTR   szComponent,         // generic component ID that is qualified
	DWORD     iIndex,	           // 0-based index into qualifiers
	LPWSTR    lpQualifierBuf,      // qualifier buffer
	DWORD     *pcchQualifierBuf,   // in/out qualifier buffer character count
	LPWSTR    lpDescriptionBuf,    // description buffer
	DWORD     *pcchDescriptionBuf); // in/out description buffer character count
#ifdef UNICODE
#define MsiEnumComponentQualifiers  MsiEnumComponentQualifiersW
#else
#define MsiEnumComponentQualifiers  MsiEnumComponentQualifiersA
#endif // !UNICODE

// --------------------------------------------------------------------------
// Functions to obtain product or package information.
// --------------------------------------------------------------------------

// Open the installation for a product to obtain detailed information

UINT WINAPI MsiOpenProductA(
	LPCSTR   szProduct,    // product code OR descriptor
	MSIHANDLE  *hProduct);   // returned product handle, must be closed
UINT WINAPI MsiOpenProductW(
	LPCWSTR   szProduct,    // product code OR descriptor
	MSIHANDLE  *hProduct);   // returned product handle, must be closed
#ifdef UNICODE
#define MsiOpenProduct  MsiOpenProductW
#else
#define MsiOpenProduct  MsiOpenProductA
#endif // !UNICODE

// Open a product package in order to access product properties

UINT WINAPI MsiOpenPackageA(
	LPCSTR    szPackagePath,     // location of package
	MSIHANDLE  *hProduct);         // returned product handle, must be closed
UINT WINAPI MsiOpenPackageW(
	LPCWSTR    szPackagePath,     // location of package
	MSIHANDLE  *hProduct);         // returned product handle, must be closed
#ifdef UNICODE
#define MsiOpenPackage  MsiOpenPackageW
#else
#define MsiOpenPackage  MsiOpenPackageA
#endif // !UNICODE

// Provide the value for an installation property.

UINT WINAPI MsiGetProductPropertyA(
	MSIHANDLE   hProduct,       // product handle obtained from MsiOpenProduct
	LPCSTR    szProperty,     // property name, case-sensitive
	LPSTR     lpValueBuf,     // returned value, NULL if not desired
	DWORD      *pcchValueBuf); // in/out buffer character count
UINT WINAPI MsiGetProductPropertyW(
	MSIHANDLE   hProduct,       // product handle obtained from MsiOpenProduct
	LPCWSTR    szProperty,     // property name, case-sensitive
	LPWSTR     lpValueBuf,     // returned value, NULL if not desired
	DWORD      *pcchValueBuf); // in/out buffer character count
#ifdef UNICODE
#define MsiGetProductProperty  MsiGetProductPropertyW
#else
#define MsiGetProductProperty  MsiGetProductPropertyA
#endif // !UNICODE


// Determine whether a file is a package
// Returns ERROR_SUCCESS if file is a package.

UINT WINAPI MsiVerifyPackageA(
	LPCSTR      szPackagePath);   // location of package
UINT WINAPI MsiVerifyPackageW(
	LPCWSTR      szPackagePath);   // location of package
#ifdef UNICODE
#define MsiVerifyPackage  MsiVerifyPackageW
#else
#define MsiVerifyPackage  MsiVerifyPackageA
#endif // !UNICODE


// Provide descriptive information for product feature: title and description.
// Returns the install level for the feature, or -1 if feature is unknown.
//   0 = feature is not available on this machine
//   1 = highest priority, feature installed if parent is installed
//  >1 = decreasing priority, feature installation based on InstallLevel property

UINT WINAPI MsiGetFeatureInfoA(
	MSIHANDLE   hProduct,       // product handle obtained from MsiOpenProduct
	LPCSTR    szFeature,      // feature name
	DWORD      *lpAttributes,  // attribute flags for the feature <to be defined>
	LPSTR     lpTitleBuf,     // returned localized name, NULL if not desired
	DWORD      *pcchTitleBuf,  // in/out buffer character count
	LPSTR     lpHelpBuf,      // returned description, NULL if not desired
	DWORD      *pcchHelpBuf);  // in/out buffer character count
UINT WINAPI MsiGetFeatureInfoW(
	MSIHANDLE   hProduct,       // product handle obtained from MsiOpenProduct
	LPCWSTR    szFeature,      // feature name
	DWORD      *lpAttributes,  // attribute flags for the feature <to be defined>
	LPWSTR     lpTitleBuf,     // returned localized name, NULL if not desired
	DWORD      *pcchTitleBuf,  // in/out buffer character count
	LPWSTR     lpHelpBuf,      // returned description, NULL if not desired
	DWORD      *pcchHelpBuf);  // in/out buffer character count
#ifdef UNICODE
#define MsiGetFeatureInfo  MsiGetFeatureInfoW
#else
#define MsiGetFeatureInfo  MsiGetFeatureInfoA
#endif // !UNICODE

// --------------------------------------------------------------------------
// Functions to install missing components and files. These should be used
// as a last resort.
// --------------------------------------------------------------------------

// Install a component unexpectedly missing, provided only for error recovery
// This would typically occur due to failue to establish feature availability
// The product feature having the smallest incremental cost is installed

UINT WINAPI MsiInstallMissingComponentA(
	LPCSTR      szProduct,        // product code
	LPCSTR      szComponent,      // component Id, string GUID
	INSTALLSTATE eInstallState);  // local/source/default, absent invalid
UINT WINAPI MsiInstallMissingComponentW(
	LPCWSTR      szProduct,        // product code
	LPCWSTR      szComponent,      // component Id, string GUID
	INSTALLSTATE eInstallState);  // local/source/default, absent invalid
#ifdef UNICODE
#define MsiInstallMissingComponent  MsiInstallMissingComponentW
#else
#define MsiInstallMissingComponent  MsiInstallMissingComponentA
#endif // !UNICODE

// Install a file unexpectedly missing, provided only for error recovery
// This would typically occur due to failue to establish feature availability
// The missing component is determined from the product's File table, then
// the product feature having the smallest incremental cost is installed

UINT WINAPI MsiInstallMissingFileA(
	LPCSTR      szProduct,        // product code
	LPCSTR      szFile);          // file name, without path
UINT WINAPI MsiInstallMissingFileW(
	LPCWSTR      szProduct,        // product code
	LPCWSTR      szFile);          // file name, without path
#ifdef UNICODE
#define MsiInstallMissingFile  MsiInstallMissingFileW
#else
#define MsiInstallMissingFile  MsiInstallMissingFileA
#endif // !UNICODE

#ifdef __cplusplus
}
#endif

// --------------------------------------------------------------------------
// Error codes for installer access functions - until merged to winerr.h
// --------------------------------------------------------------------------

#ifndef ERROR_INSTALL_FAILURE
#define ERROR_INSTALL_USEREXIT      1602L  // User cancel installation.
#define ERROR_INSTALL_FAILURE       1603L  // Fatal error during installation.
#define ERROR_INSTALL_SUSPEND       1604L  // Installation suspended, incomplete.
#define ERROR_UNKNOWN_PRODUCT       1605L  // Product code not registered.
#define ERROR_UNKNOWN_FEATURE       1606L  // Feature ID not registered.
#define ERROR_UNKNOWN_COMPONENT     1607L  // Component ID not registered.
#define ERROR_UNKNOWN_PROPERTY      1608L  // Unknown property.
#define ERROR_INVALID_HANDLE_STATE  1609L  // Handle is in an invalid state.
#define ERROR_BAD_CONFIGURATION     1610L  // Configuration data corrupt.
#define ERROR_INDEX_ABSENT          1611L  // Component qualifier not present.
#define ERROR_INSTALL_SOURCE_ABSENT 1612L  // Install source unavailable.
#define ERROR_PRODUCT_UNINSTALLED   1614L  // Product is uninstalled.
#define ERROR_BAD_QUERY_SYNTAX      1615L  // SQL query syntax invalid or unsupported.
#define ERROR_INVALID_FIELD         1616L  // Record field does not exist.
#endif

#ifndef ERROR_INSTALL_STARTING
#define ERROR_INSTALL_STARTING             1600L // Preparing to install...
#define ERROR_INSTALL_SERVICE_FAILURE      1601L // Failure accessing installation service.
#define ERROR_INSTALL_PACKAGE_VERSION      1613L // Database version unsupported.
#define ERROR_INVALID_COMMAND_LINE         1617L // Invalid command line argument.
#define ERROR_INSTALL_ALREADY_RUNNING      1618L // An installation is in progress.
#define ERROR_INSTALL_PACKAGE_OPEN_FAILED  1619L // Installation package could not be opened.
#define ERROR_INSTALL_PACKAGE_INVALID      1620L // Installation package invalid.
#define ERROR_INSTALL_UI_FAILURE           1621L // Could not initialize installer user interface.
#define ERROR_INSTALL_LOG_FAILURE          1622L // Error opening installation log file.
#define ERROR_INSTALL_LANGUAGE_UNSUPPORTED 1623L // Product language not supported by system.
#define ERROR_INSTALL_TRANFORM_FAILURE     1624L // Error applying transform to install package.
#define ERROR_INSTALL_PACKAGE_REJECTED     1625L // Install package signature not accepted.
#define ERROR_FUNCTION_NOT_CALLED          1626L // Function could not be executed.
#define ERROR_FUNCTION_FAILED              1627L // Function failed during execution.
#define ERROR_INVALID_TABLE                1628L // Invalid or unknown table specified.
#define ERROR_DATATYPE_MISMATCH            1629L // Data supplied is of wrong type.
#define ERROR_UNSUPPORTED_TYPE             1630L // Data of this type is not supported.
#define ERROR_CREATE_FAILED                1631L // Data of this type is not supported.
#endif

#ifndef ERROR_INSTALL_TEMP_UNWRITABLE      
#define ERROR_INSTALL_TEMP_UNWRITABLE      1632L // Temp folder is full or inaccessible
#endif

#endif // _MSI_H_
