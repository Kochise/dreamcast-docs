// --proxygen.h-----------------------------------------------------------------
//
//  Copyright (c) Microsoft Corp. 1986-1996. All Rights Reserved.
//
//	Specification for the required implementation of a proxy generation DLL
//	for an installed address-type.
//
//	Functions in this DLL will be called in the following order:
//
//         RcInitProxies
//              |
//              |<----------------------------------+
//              |                                   |
//				+-----------------------+           |
//				|                       |           |
//		RcGenerateProxy        RcValidateProxy     	|
//				|                       |           |
//				|                       |           |
//				|                       |           |
//			FreeProxy                   |           |
//				|                       |           |
//				+-----------------------+-----------+
//										|
//										|
//	                                    |
//	                                  Close
//
//------------------------------------------------------------------------------

#if !defined(_PROXYGEN_H)
#define _PROXYGEN_H

#include <windows.h>
#include <retcode.h>	// RC
#include <proxyinf.h>	// RECIPIENTINFO structures


//$--RcInitProxies--------------------------------------------------------------
//	Requests that the proxy generation DLL do any initializaton required before
//	calling the GenerateProxy function with individual recipient objects.
//  This function is not permitted to generate any UI as proxy generation
//	should all be done silently without user intervention. If the implementor 
//	desires, this function may do nothing other than make the site specific 
//	information accessible to the GenerateProxy and ValidateProxy functions. 

//	Init is primarily included for efficiency purposes so that the implementor
//	may do any common processing in this function as it is likely that a large 
//	number of proxies will be generated at one time during an address-type 
//	install or update.
//
//	Input Parameters
//		pszSiteProxy	The site proxy for this address-type. Generally used
//						as part of the recipient proxy. May be NULL (this is 
//						address-type dependent) if not used or not set yet.
//		pszServer		The name of the server that the proxy DLL is being
//						used on.
//	
//	Note: these 2 pointers are guaranteed to be stay valid until after Close is
//	called so the DLL need only keep a copy of these pointers rather than copy 
//	the data.  Or, the DLL can copy the data with the same result as the
//	information these structures point to will not change until after Close is 
//	called.
//	
//	Output Parameters
//		hProxySession	Handle to a proxy session.  Any storage associated
//						with this handle which is allocated by Init must be
//						freed by Close
//
//	Returns:
//		RC_SUCCESS		Success
//		RC_IMPLEMENTATION	Proxies are not implemented for this address type. 
//						No proxies will be stored. The Generate and Close entry
//						points to this DLL are undefined. User will not be
//						notified as this is a supported configuration.
//		RC_MEMORY		Memory allocation failure
//		RC_ERROR		General failure.  User will be notified of inability
//						to generate proxies for this address type.
//------------------------------------------------------------------------------
RC RcInitProxies(IN LPWSTR pszSiteProxy,
    			 IN LPWSTR pszServer,
    			 OUT HANDLE *phProxySession);


//$--RcGenerateProxy------------------------------------------------------------
//	Returns a single proxy address as a unicode string. This function is not 
//	permitted to generate any UI as proxy generation should all be done silently
//	without user intervention.
//
//	Input Parameters:
//		hProxySession	Handle to the proxy session previously returned by
//						Init.
//		pRecipientInfo	The recipient specific details for this recipient.
//						Used along with the Site Proxy
//						information and nRetries by Generate to algorithmically
//						generate a site-unique recipient proxy in the 
//						addressing format of the foreign address-type.
//		nRetries		The number of times this function has previously been
//						called with this value for pRecipientInfo. When ProxyGen
//						is called with the same pRecipientInfo but different
//						nRetries values it should endeavour to return a different
//						proxy address.  However, the maximum value which an
//						an implementation supports for nRetries is 
//						implementation specific (may be 0).
//		
//	Output Parameters:
//		ppszProxyAddr	The foreign format (proxy) address which is generated.
//						This must be a unicode string. This is allocated by the 
//						Generate function but must be freed by the calling code
//						by calling FreeProxy.
//						The proxy should be of the form "TYPE:VALUE"
//
//	Returns:
//		RC_SUCCESS		Success
//		RC_MEMORY		Memory allocation failure
//		RC_ERROR		Cannot generate proxy address, Possibile problems are:
//						- nRetries is too high, cannot generate any more unique
//						  proxies.
//						- site specific info incomplete
//						- per recipient info incomplete
//------------------------------------------------------------------------------
RC RcGenerateProxy(IN HANDLE 			hProxySession,
			       IN PRECIPIENTINFO	pRecipientInfo,
			       IN int				nRetries,
			       OUT LPWSTR *			ppszProxyAddr);


//$--RcUpdateProxy------------------------------------------------------------
//	Compares the site proxy part of a proxy to an "old" site proxy. If
//	they match then replace the "old" site proxy in the proxy with the "new
//	site proxy.  All input parameters have the address type as a prefix.
//
//	Input Parameters:
//		hProxySession		Handle to the proxy session previously returned by
//							Init.
//		pRecipientInfo		The recipient specific details for this recipient.
//		pwstrOldSiteProxy	"Old" site proxy.
//		pwstrNewSiteProxy	"New" site proxy.
//		pwstrProxy			The proxy to be modified.
//		pUnused				unused
//		
//	Output Parameters:
//		pwstrProxy			The modified proxy.
//
//	Returns:
//		RC_SUCCESS		Success
//		RC_MEMORY		Memory allocation failure
//		RC_ERROR		Cannot generate new proxy address
//------------------------------------------------------------------------------
RC RcUpdateProxy(IN HANDLE hProxySession,
				 IN PRECIPIENTINFO pRecipientInfo,
				 IN LPWSTR pwstrOldSiteProxy,
				 IN LPWSTR pwstrNewSiteProxy,
				 IN OUT LPWSTR pwstrProxy,
				 IN VOID * pUnused);


//$--RcValidateProxy------------------------------------------------------------
//	Given a unicode string it validates that this string represents a valid
//	address of the appropriate foreign type. This is called to verify manually
//	generated proxies are legal.
//
//	Input Parameters:
//		hProxySession	Handle to the proxy session previously returned by
//						Init.
//		pszProxyAddr	The foreign format (proxy) address to be validated
//                      including the prefixed address type.
//						If the proxy dll can make an invalid proxy (because
//						of invalid characters, etc.) into a valid proxy then
//						return the corrected proxy in this location and
//						return TRUE in *pisValid.  The caller will have made
//						allowances for a possibly longer returned proxy string.
//
//	Output Parameters:
//		pisValid		TRUE if valid, FALSE if not.  TRUE if return code
//						is RC_IMPLEMENTATION. Undefined if return code is
//						RC_ERROR or RC_MEMORY.
//
//	Returns:
//		RC_SUCCESS		Success
//		RC_IMPLEMENTATION	Proxy validation not implemented.  The caller 
//						should assume the entered proxy is valid and let the
//						gateway or foreign system advise otherwise if neccesary.
//		RC_MEMORY		Memory allocation failure
//		RC_ERROR		Implementation specific error.
//------------------------------------------------------------------------------
RC RcValidateProxy(IN HANDLE 	hProxySession,
              	   IN LPWSTR 	pszProxyAddr,
			       OUT BOOL * 	pisValid);


//$--RcValidateSiteProxy------------------------------------------------------------
//	Given a unicode string it validates that this string represents a valid
//	site address of the appropriate foreign type. This is called to verify manually
//	generated site proxies are legal.
//
//	Input Parameters:
//		hProxySession	Handle to the proxy session previously returned by
//						Init.
//		pszSiteProxy	The foreign format site (proxy) address to be validated
//                      including the prefixed address type.
//						If the proxy dll can make an invalid proxy (because
//						of invalid characters, etc.) into a valid proxy then
//						return the corrected proxy in this location and
//						return TRUE in *pisValid.  The caller will have made
//						allowances for a possibly longer returned proxy string.
//
//	Output Parameters:
//		pisValid		TRUE if valid, FALSE if not.  TRUE if return code
//						is RC_IMPLEMENTATION. Undefined if return code is
//						RC_ERROR or RC_MEMORY.
//
//	Returns:
//		RC_SUCCESS		Success
//		RC_IMPLEMENTATION	Proxy validation not implemented.  The caller 
//						should assume the entered site proxy is valid and let the
//						gateway or foreign system advise otherwise if neccesary.
//		RC_MEMORY		Memory allocation failure
//		RC_ERROR		Implementation specific error.
//------------------------------------------------------------------------------
RC RcValidateSiteProxy(IN HANDLE 	hProxySession,
	              	   IN LPWSTR 	pszProxyAddr,
				       OUT BOOL * 	pisValid);


//$--FreeProxy------------------------------------------------------------------
//	Frees the memory previously allocated by 
//	GenerateProxy for a proxy address string.
//
// 	Input Parameter:
//		pszProxy	The proxy string to be freed
//------------------------------------------------------------------------------
VOID FreeProxy(IN LPWSTR pszProxy);


//$--CloseProxies---------------------------------------------------------------
//	Closes a proxy generation session and frees any associated data.  The DLL
//	can now be unloaded. This function is not permitted to generate any UI as 
//	proxy generation should all be done silently without user intervention.
//
//	Input Parameters
//		hProxySession	Handle to the proxy session previously returned by
//						Init.
//	Returns:
//		Nothing. 
void CloseProxies(IN HANDLE hProxySession);

#endif
