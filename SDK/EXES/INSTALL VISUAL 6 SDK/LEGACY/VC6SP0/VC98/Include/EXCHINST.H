// --exchinst.h-----------------------------------------------------------------
//
// Functions for installing Exchange objects.
//
// Copyright 1986 - 1998 Microsoft Corporation.  All Rights Reserved.
// -----------------------------------------------------------------------------

#ifndef _EXCHINST_H
#define _EXCHINST_H

#ifdef __cplusplus
extern "C" {
#endif // __cplusplus

#define OBJECT_GUID_MAIL_GATEWAY   "61DF5950-E40A-11ce-A2C9-00AA0040E865"
#define OBJECT_GUID_MAILBOX_AGENT  "75BB4220-E40A-11ce-A2C9-00AA0040E865"

//$--HrEnumOrganizations--------------------------------------------------------
//  Enumerates the organization name(s).
// -----------------------------------------------------------------------------
HRESULT HrEnumOrganizations(          // RETURNS: return code
    IN  LPSTR lpszRootDN,                // distinguished name of DIT root
    IN  LPSTR lpszServer,                // server name
    OUT LPSTR *lppszOrganizations);      // organizations

//$--HrEnumSites----------------------------------------------------------------
//  Enumerates the site name(s).
// -----------------------------------------------------------------------------
HRESULT HrEnumSites(                  // RETURNS: return code
    IN  LPSTR lpszServer,                // server name
    IN  LPSTR lpszOrganizationDN,        // distinguished name of organization
    OUT LPSTR *lppszSites);              // sites

//$--HrEnumContainers-----------------------------------------------------------
//  Enumerates the container name(s).
// -----------------------------------------------------------------------------
HRESULT HrEnumContainers(             // RETURNS: return code
    IN  LPSTR lpszServer,                // server name
    IN  LPSTR lpszSiteDN,                // distinguished name of site
    IN  BOOL  fSubtree,                  // sub-tree?
    OUT LPSTR *lppszContainers);         // containers
 
//$--HrEnumSiteAdmins-----------------------------------------------------------
//  Enumerates the administrators for a given site.
// -----------------------------------------------------------------------------
HRESULT HrEnumSiteAdmins(             // RETURNS: return code
    IN  LPSTR lpszServer,                // server name
    IN  LPSTR lpszSiteDN,                // distinguished name of site
    OUT LPSTR *lppszAdmins);             // administrator accounts

//$--HrEnumProductServices------------------------------------------------------
//  Enumerates the services for a product.
// -----------------------------------------------------------------------------
HRESULT HrEnumProductServices(        // RETURNS: return code
    IN  LPSTR lpszProductGuid,           // product GUID
    OUT LPSTR *lppszServices,            // service names
    OUT LPSTR *lppszDisplayNames);       // service display names

//$--HrInstallService-----------------------------------------------------------
//  Installs a service associated with an Exchange object.
// -----------------------------------------------------------------------------
HRESULT HrInstallService(            // RETURNS: return code
    IN LPSTR  lpszServer,               // server name
    IN LPSTR  lpszSiteDN,               // distinguished name of site
    IN LPSTR  lpszServiceDisplayName,   // service display name
    IN LPSTR  lpszServiceName,          // service name
    IN LPSTR  lpszCommonName,           // object relative distinguished name
    IN LPSTR  lpszObjectGuid,           // object GUID
    IN LPSTR  lpszProductGuid,          // product GUID
    IN LPSTR  lpszExeName,              // executable name
    IN LPCSTR lpszDependencies,         // dependencies
    IN LPSTR  lpszAccount,              // account
    IN LPSTR  lpszPassword);            // password

//$--HrGetServiceServerName-----------------------------------------------------
//  Get the Exchange server name associated with the service.
// -----------------------------------------------------------------------------
HRESULT HrGetServiceServerName(      // RETURNS: return code
    IN  LPSTR  lpszServiceName,         // service name
    OUT LPSTR  *lppszServerName);       // server name

//$--HrGetServiceSiteDN---------------------------------------------------------
//  Get the site DN of the Exchange object associated with the service.
// -----------------------------------------------------------------------------
HRESULT HrGetServiceSiteDN(          // RETURNS: return code
    IN  LPSTR  lpszServiceName,         // service name
    OUT LPSTR  *lppszSiteDN);           // site distinguished name

//$--HrGetServiceCommonName-----------------------------------------------------
//  Get the common name of the Exchange object associated with the service.
// -----------------------------------------------------------------------------
HRESULT HrGetServiceCommonName(      // RETURNS: return code
    IN  LPSTR  lpszServiceName,         // service name
    OUT LPSTR  *lppszCommonName);       // object relative distinguished name
 
//$--HrGetServiceObjectGUID-----------------------------------------------------
//  Get the object GUID associated with the service.
// -----------------------------------------------------------------------------
HRESULT HrGetServiceObjectGUID(      // RETURNS: return code
    IN  LPSTR  lpszServiceName,         // service name
    OUT LPSTR  *lppszObjectGUID);      // object GUID

//$--HrGetServiceProductGUID----------------------------------------------------
//  Get the product GUID associated with the service.
// -----------------------------------------------------------------------------
HRESULT HrGetServiceProductGUID(     // RETURNS: return code
    IN  LPSTR  lpszServiceName,        // service name
    OUT LPSTR  *lppszProductGUID);     // product GUID

//$--HrGetServiceDisplayName----------------------------------------------------
//  Get the display name associated with the service.
// -----------------------------------------------------------------------------
HRESULT HrGetServiceDisplayName(     // RETURNS: return code
    IN  LPSTR  lpszServiceName,        // service name
    OUT LPSTR  *lppszDisplayName);     // display name

//$--HrGetServiceExecutableName-------------------------------------------------
//  Get the executable name associated with the service.
// -----------------------------------------------------------------------------
HRESULT HrGetServiceExecutableName(  // RETURNS: return code
    IN  LPSTR  lpszServiceName,        // service name
    OUT LPSTR  *lppszExecutableName);  // executable name

//$--HrGetServiceAccountName----------------------------------------------------
//  Get the account name associated with the service.
// -----------------------------------------------------------------------------
HRESULT HrGetServiceAccountName(     // RETURNS: return code
    IN  LPSTR  lpszServiceName,        // service name
    OUT LPSTR  *lppszAccountName);     // account name

//$--HrRemoveRegistry-----------------------------------------------------------
//  Remove the registry for the service.
// -----------------------------------------------------------------------------
HRESULT HrRemoveRegistry(              // RETURNS: nothing
    IN LPCSTR lpszServiceName);        // service name

//$--HrRemoveService------------------------------------------------------------
//  Removes a service.
// -----------------------------------------------------------------------------
HRESULT HrRemoveService(             // RETURNS: return code
    IN LPCSTR lpszServiceName);        // service name

//$--HrInstallServicePerfMon----------------------------------------------------
//  Installs service performance monitoring.
// -----------------------------------------------------------------------------
HRESULT HrInstallServicePerfMon(         // RETURNS: return code
    IN LPSTR lpszServiceName,              // service name
    IN LPSTR lpszClassName,                // class name
    IN LPSTR lpszLibraryName,              // library name
    IN LPSTR lpszLibraryOpenFunction,      // open function
    IN LPSTR lpszLibraryCollectFunction,   // collect function
    IN LPSTR lpszLibraryCloseFunction) ;   // close function

//$--HrRemoveServicePerfMon-----------------------------------------------------
//  Removes service performance monitoring.
// -----------------------------------------------------------------------------
HRESULT HrRemoveServicePerfMon(          // RETURNS: return code
    IN  LPSTR lpszServiceName,             // service name
    IN  LPSTR lpszClassName,               // class name
    OUT BOOL   *lpfUnloadCounters);         // unload counters?

//$--HrCreateGatewayProfile-----------------------------------------------------
//  Creates a gateway profile.
// -----------------------------------------------------------------------------
HRESULT HrCreateGatewayProfile(          // RETURNS: return code
    IN LPSTR lpszServiceName,              // service name
    IN LPSTR lpszProfileName);             // profile name

//$--HrCreateMailboxAgentProfile------------------------------------------------
//  Creates a mailbox agent profile.
// -----------------------------------------------------------------------------
HRESULT HrCreateMailboxAgentProfile(     // RETURNS: return code
    IN LPSTR lpszServiceName,              // service name
    IN LPSTR lpszProfileName);             // profile name

//$--HrRemoveProfile------------------------------------------------------------
//  Removes a profile.
//------------------------------------------------------------------------------
HRESULT HrRemoveProfile(                 // RETURNS: return code
    IN LPSTR lpszProfileName);                // profile name

//$--HrMAPIProfileExists--------------------------------------------------------
//  Checks for an existing profile.
// -----------------------------------------------------------------------------
HRESULT HrMAPIProfileExists(            // RETURNS: return code
    IN LPPROFADMIN lpProfAdmin,         // profile admin object
    IN LPSTR       lpszProfileName);    // profile name

//$--HrInstallGateway-----------------------------------------------------------
// Installs a gateway into a given site.
// -----------------------------------------------------------------------------
HRESULT HrInstallGateway(           // RETURNS: return code
    IN LPSTR lpszServer,            // server name
    IN LPSTR lpszSiteDN,            // distinguished name of site
    IN LPSTR lpszDisplayName,       // display name
    IN LPSTR lpszCommonName,        // common name
    IN LPSTR lpszExtensionName,     // admin extension name
    IN LPSTR lpszExtensionData,     // extension data file
    IN LPSTR lpszAddressType,       // address type handled by this gateway
    IN LPSTR lpszAccountName,       // account name
    IN BOOL  fCanPreserveDNs);      // can this gateway preserve DNs?

//$--HrRemoveGateway------------------------------------------------------------
//  Removes a gateway from a given site.
// -----------------------------------------------------------------------------
HRESULT HrRemoveGateway(            // RETURNS: return code
    IN LPSTR lpszServer,            // server name
    IN LPSTR lpszSiteDN,            // distinguished name of site
    IN LPSTR lpszCommonName);       // common name

//$--HrGatewayExists------------------------------------------------------------
//  Checks if a gateway exists on a given site.
// -----------------------------------------------------------------------------
HRESULT HrGatewayExists(            // RETURNS: return code
    IN LPSTR lpszServer,            // server name
    IN LPSTR lpszSiteDN,            // distinguished name of site
    IN LPSTR lpszCommonName);       // common name

//$--HrInstallMailboxAgent------------------------------------------------------
//  Installs a mailbox agent into a given site.
// -----------------------------------------------------------------------------
HRESULT HrInstallMailboxAgent(      // RETURNS: return code
    IN LPSTR lpszServer,            // server name
    IN LPSTR lpszSiteDN,            // distinguished name of site
    IN LPSTR lpszDisplayName,       // display name
    IN LPSTR lpszRDN,               // relative distinguished name
    IN LPSTR lpszExtensionName,     // admin extension name
    IN LPSTR lpszExtensionData,     // extension data file
    IN LPSTR lpszAccountName);      // account name

//$--HrRemoveMailboxAgent-------------------------------------------------------
// Removes a mailbox agent from a given site.
// -----------------------------------------------------------------------------
HRESULT HrRemoveMailboxAgent(       // RETURNS: return code
    IN LPSTR lpszServer,            // server name
    IN LPSTR lpszSiteDN,            // distinguished name of site
    IN LPSTR lpszRDN);              // relative distinguished name

//$--HrMailboxAgentExists-------------------------------------------------------
// Checks if a mailbox agent exists on a given site.
// -----------------------------------------------------------------------------
HRESULT HrMailboxAgentExists(       // RETURNS: return code
    IN LPSTR lpszServer,            // server name
    IN LPSTR lpszSiteDN,            // distinguished name of site
    IN LPSTR lpszRDN);              // relative distinguished name

//$--HrInstallAddressType-------------------------------------------------------
//  Installs an address type object into a given site.
// -----------------------------------------------------------------------------
HRESULT HrInstallAddressType(       // RETURNS: return code
    IN LPSTR lpszServer,            // server name
    IN LPSTR lpszSiteDN,            // distinguished name of site
    IN LPSTR lpszDisplayName,       // display name
    IN LPSTR lpszCommonName,        // common name
    IN DWORD  dwFileVersionMS,      // high-order 32 bits of file version number
    IN DWORD  dwFileVersionLS,      // low-order 32 bits of file version number
    IN LPSTR lpszProxyGenDLL,       // proxy generator DLL file name
    IN LPSTR lpszMachineType);      // machine type (e.g. "i386")

//$--HrRemoveAddressType--------------------------------------------------------
//  Removes an address type from a given site.
// -----------------------------------------------------------------------------
HRESULT HrRemoveAddressType(        // RETURNS: return code
    IN LPSTR lpszServer,            // server name
    IN LPSTR lpszSiteDN,            // distinguished name of site
    IN LPSTR lpszCommonName,        // common name
    IN LPSTR lpszMachineType);      // machine type (e.g. "i386")

//$--HrAddressTypeExists--------------------------------------------------------
//  Checks if an address type exists on a given site.
// -----------------------------------------------------------------------------
HRESULT HrAddressTypeExists(        // RETURNS: return code
    IN LPSTR lpszServer,            // server name
    IN LPSTR lpszSiteDN,            // distinguished name of site
    IN LPSTR lpszCommonName,        // common name
    IN LPSTR lpszMachineType);      // machine type (e.g. "i386")

//$--HrGetAddressTypeVersion----------------------------------------------------
//  Get the version of an address type object in a given site.
// -----------------------------------------------------------------------------
HRESULT HrGetAddressTypeVersion(    // RETURNS: return code
    IN LPSTR lpszServer,            // server name
    IN LPSTR lpszSiteDN,            // distinguished name of site
    IN LPSTR lpszCommonName,        // common name
    IN LPSTR lpszMachineType,       // machine type (e.g. "i386")
    OUT DWORD *lpdwFileVersionMS,   // high-order 32 bits of file version
    OUT DWORD *lpdwFileVersionLS);  // low-order 32 bits of file version

//$--HrInstallAddressTemplate---------------------------------------------------
//  Installs an address template into a given site.
// -----------------------------------------------------------------------------
HRESULT HrInstallAddressTemplate(   // RETURNS: return code
    IN LPSTR lpszServer,            // server name
    IN LPSTR lpszSiteDN,            // distinguished name of site
    IN LPSTR lpszDisplayName,       // display name
    IN LPSTR lpszCommonName,        // common name
    IN LPSTR lpszAddressSyntax,     // address syntax generator file
    IN LPSTR lpszAddressType,       // address type supported by this template
    IN LPSTR lpszPerMessageDDT,     // per-message dialog file
    IN LPSTR lpszPerRecipientDDT,   // per-recipient dialog file
    IN LPSTR lpszAddressEntryDDT,   // address entry dialog file
    IN LPSTR lpszLanguage,          // language supported by this template
    IN LPSTR lpszHelpData16,        // help data for 16-bit clients
    IN LPSTR lpszHelpData32,        // help data for 32-bit clients
    IN LPSTR lpszHelpFile);         // client help file name

//$--HrRemoveAddressTemplate----------------------------------------------------
//  Removes an address template from a given site.
// -----------------------------------------------------------------------------
HRESULT HrRemoveAddressTemplate(    // RETURNS: return code
    IN LPSTR lpszServer,            // server name
    IN LPSTR lpszSiteDN,            // distinguished name of site
    IN LPSTR lpszCommonName,        // common name
    IN LPSTR lpszAddressType,       // address type supported by this template
    IN LPSTR lpszLanguage);         // language supported by this template

//$--HrAddressTemplateExists----------------------------------------------------
//  Checks if an address template exists on a given site.
// -----------------------------------------------------------------------------
HRESULT HrAddressTemplateExists(    // RETURNS: return code
    IN LPSTR lpszServer,            // server name
    IN LPSTR lpszSiteDN,            // distinguished name of site
    IN LPSTR lpszCommonName,        // common name
    IN LPSTR lpszAddressType,       // address type supported by this template
    IN LPSTR lpszLanguage);         // language supported by this template

//$--HrInstallAdminExtension----------------------------------------------------
//  Installs an admin extension object into a given site.
// -----------------------------------------------------------------------------
HRESULT HrInstallAdminExtension(    // RETURNS: return code
    IN LPSTR lpszServer,            // server name
    IN LPSTR lpszSiteDN,            // distinguished name of site
    IN LPSTR lpszDisplayName,       // display name
    IN LPSTR lpszCommonName,        // common name
    IN DWORD dwFileVersionMS,       // high-order 32 bits of file version number
    IN DWORD dwFileVersionLS,       // low-order 32 bits of file version number
    IN LPSTR lpszExtensionDLL,      // admin extension DLL file name
    IN LPSTR lpszMachineType);      // machine type (e.g. "i386")


//$--HrRemoveAdminExtension-----------------------------------------------------
//  Removes an admin extension from a given site.
// -----------------------------------------------------------------------------
HRESULT HrRemoveAdminExtension(     // RETURNS: return code
    IN LPSTR lpszServer,            // server name
    IN LPSTR lpszSiteDN,            // distinguished name of site
    IN LPSTR lpszCommonName,        // common name
    IN LPSTR lpszMachineType);      // machine type (e.g. "i386")

//$--HrAdminExtensionExists-----------------------------------------------------
//  Checks if an admin extension exists on a given site.
// -----------------------------------------------------------------------------
HRESULT HrAdminExtensionExists(     // RETURNS: return code
    IN LPSTR lpszServer,            // server name
    IN LPSTR lpszSiteDN,            // distinguished name of site
    IN LPSTR lpszCommonName,        // common name
    IN LPSTR lpszMachineType);      // machine type (e.g. "i386")

//$--HrGetAdminExtensionVersion-------------------------------------------------
//  Get the version of an admin extension object in a given site.
// -----------------------------------------------------------------------------
HRESULT HrGetAdminExtensionVersion(     // RETURNS: return code
    IN LPSTR lpszServer,                // server name
    IN LPSTR lpszSiteDN,                // distinguished name of site
    IN LPSTR lpszCommonName,            // common name
    IN LPSTR lpszMachineType,           // machine type (e.g. "i386")
    OUT DWORD *lpdwFileVersionMS,       // high-order 32 bits of file version
    OUT DWORD *lpdwFileVersionLS);      // low-order 32 bits of file version

//$--HrInstallContainer---------------------------------------------------------
//  Installs a container in the directory.
// -----------------------------------------------------------------------------
HRESULT HrInstallContainer(         // RETURNS: return code
    IN LPSTR lpszServer,            // server name
    IN LPSTR lpszBasePoint,         // base point
    IN LPSTR lpszCommonName,        // common name
    IN LPSTR lpszDisplayName,       // display name
    IN LPSTR lpszContainerInfo);    // container information

//$--HrRemoveContainer----------------------------------------------------------
//  Removes a container from the directory.
// -----------------------------------------------------------------------------
HRESULT HrRemoveContainer(          // RETURNS: return code
    IN LPSTR lpszServer,            // server name
    IN LPSTR lpszBasePoint,         // base point
    IN LPSTR lpszCommonName);       // common name

//$--HrContainerExists----------------------------------------------------------
//  Checks if a container exists in the directory.
// -----------------------------------------------------------------------------
HRESULT HrContainerExists(          // RETURNS: return code
    IN LPSTR lpszServer,            // server name
    IN LPSTR lpszBasePoint,         // base point
    IN LPSTR lpszCommonName);       // common name

//$--HrInstallAddressTemplateContainer------------------------------------------
//  Installs an address template container in the directory.
// -----------------------------------------------------------------------------
HRESULT HrInstallAddressTemplateContainer(  // RETURNS: return code
    IN LPSTR lpszServer,                    // server name
    IN LPSTR lpszSiteDN,                    // site distinguished name
    IN LPSTR lpszLanguage,                  // language supported by container
    IN LPSTR lpszDisplayName);              // display name

//$--HrRemoveAddressTemplateContainer-------------------------------------------
//  Removes an address template container from the directory.
// -----------------------------------------------------------------------------
HRESULT HrRemoveAddressTemplateContainer(   // RETURNS: return code
    IN LPSTR lpszServer,                    // server name
    IN LPSTR lpszSiteDN,                    // site distinguished name
    IN LPSTR lpszLanguage);                 // language supported by container

//$--HrAddressTemplateContainerExists-------------------------------------------
//  Checks if an address template container exists in the directory.
// -----------------------------------------------------------------------------
HRESULT HrAddressTemplateContainerExists(   // RETURNS: return code
    IN LPSTR lpszServer,                    // server name
    IN LPSTR lpszSiteDN,                    // site distinguished name
    IN LPSTR lpszLanguage);                 // language supported by container

//$--HrInstallGatewayProxy------------------------------------------------------
//  Installs a gateway proxy into a given site.
// -----------------------------------------------------------------------------
HRESULT HrInstallGatewayProxy(      // RETURNS: return code
    IN LPSTR lpszServer,            // server name
    IN LPSTR lpszSiteDN,            // distinguished name of site
    IN LPSTR lpszProxy);            // gateway proxy

//$--HrRemoveGatewayProxy-------------------------------------------------------
//  Removes a gateway proxy from a given site.
// -----------------------------------------------------------------------------
HRESULT HrRemoveGatewayProxy(       // RETURNS: return code
    IN LPSTR lpszServer,            // server name
    IN LPSTR lpszSiteDN,            // distinguished name of site
    IN LPSTR lpszProxy);            // gateway proxy

//$--FHasAdminPrivs-------------------------------------------------------------
//  Returns TRUE if the current user is an administrator.
// -----------------------------------------------------------------------------
BOOL FHasAdminPrivs(                // RETURNS: TRUE/FALSE
    void);                          // no arguments


//$--HrInstallMessageConverter--------------------------------------------------
// Installs a message conversion DLL.
// -----------------------------------------------------------------------------
HRESULT HrInstallMessageConverter(      // RETURNS: return code
    IN LPSTR lpszConverter,             // converter name
    IN LPSTR lpszDllName,               // name of conversion DLL
    IN LPSTR lpszMessageClasses,        // message classes
    IN LPSTR lpszOptions,               // options string
    IN LPSTR lpszPoint);                // conversion point

//$--HrRemoveMessageConverter--------------------------------------------------
//  Delete a message conversion DLL.
// ----------------------------------------------------------------------------
HRESULT HrRemoveMessageConverter(       // RETURNS: return code
    IN LPCSTR lpszConverter);           // converter name


//$--HrAdminProgramExists------------------------------------------------------
//  Check if the admin program has been installed on the local computer.
// ----------------------------------------------------------------------------
HRESULT HrAdminProgramExists(           // RETURNS: return code
    void);                              // nothing

//$--HrSetGatewayBit------------------------------------------------------------
//  This function will set the gateway bit on a given server.
// -----------------------------------------------------------------------------
HRESULT HrSetGatewayBit(                // RETURNS: return code
    IN  LPSTR lpszServer,               // server name
    IN  LPSTR lpszSiteDN,               // site distinguished name
    IN  LPSTR lpszServerName);          // server name

#ifdef __cplusplus
}
#endif

#endif