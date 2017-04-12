/* this ALWAYS GENERATED file contains the definitions for the interfaces */


/* File created by MIDL compiler version 3.00.44 */
/* at Mon Oct 13 13:47:30 1997
 */
/* Compiler settings for ads.odl:
    Os (OptLev=s), W1, Zp8, env=Win32, ms_ext, c_ext
    error checks: none
*/
//@@MIDL_FILE_HEADING(  )
#include "rpc.h"
#include "rpcndr.h"

#ifndef __iads_h__
#define __iads_h__

#ifdef __cplusplus
extern "C"{
#endif 

/* Forward Declarations */ 

#ifndef __IADs_FWD_DEFINED__
#define __IADs_FWD_DEFINED__
typedef interface IADs IADs;
#endif 	/* __IADs_FWD_DEFINED__ */


#ifndef __IADsContainer_FWD_DEFINED__
#define __IADsContainer_FWD_DEFINED__
typedef interface IADsContainer IADsContainer;
#endif 	/* __IADsContainer_FWD_DEFINED__ */


#ifndef __IADsCollection_FWD_DEFINED__
#define __IADsCollection_FWD_DEFINED__
typedef interface IADsCollection IADsCollection;
#endif 	/* __IADsCollection_FWD_DEFINED__ */


#ifndef __IADsMembers_FWD_DEFINED__
#define __IADsMembers_FWD_DEFINED__
typedef interface IADsMembers IADsMembers;
#endif 	/* __IADsMembers_FWD_DEFINED__ */


#ifndef __IADsPropertyList_FWD_DEFINED__
#define __IADsPropertyList_FWD_DEFINED__
typedef interface IADsPropertyList IADsPropertyList;
#endif 	/* __IADsPropertyList_FWD_DEFINED__ */


#ifndef __IADsPropertyEntry_FWD_DEFINED__
#define __IADsPropertyEntry_FWD_DEFINED__
typedef interface IADsPropertyEntry IADsPropertyEntry;
#endif 	/* __IADsPropertyEntry_FWD_DEFINED__ */


#ifndef __IADsAttrInfo_FWD_DEFINED__
#define __IADsAttrInfo_FWD_DEFINED__
typedef interface IADsAttrInfo IADsAttrInfo;
#endif 	/* __IADsAttrInfo_FWD_DEFINED__ */


#ifndef __IADsPropertyValue_FWD_DEFINED__
#define __IADsPropertyValue_FWD_DEFINED__
typedef interface IADsPropertyValue IADsPropertyValue;
#endif 	/* __IADsPropertyValue_FWD_DEFINED__ */


#ifndef __IADsValue_FWD_DEFINED__
#define __IADsValue_FWD_DEFINED__
typedef interface IADsValue IADsValue;
#endif 	/* __IADsValue_FWD_DEFINED__ */


#ifndef __IADsNamespaces_FWD_DEFINED__
#define __IADsNamespaces_FWD_DEFINED__
typedef interface IADsNamespaces IADsNamespaces;
#endif 	/* __IADsNamespaces_FWD_DEFINED__ */


#ifndef __IADsClass_FWD_DEFINED__
#define __IADsClass_FWD_DEFINED__
typedef interface IADsClass IADsClass;
#endif 	/* __IADsClass_FWD_DEFINED__ */


#ifndef __IADsProperty_FWD_DEFINED__
#define __IADsProperty_FWD_DEFINED__
typedef interface IADsProperty IADsProperty;
#endif 	/* __IADsProperty_FWD_DEFINED__ */


#ifndef __IADsSyntax_FWD_DEFINED__
#define __IADsSyntax_FWD_DEFINED__
typedef interface IADsSyntax IADsSyntax;
#endif 	/* __IADsSyntax_FWD_DEFINED__ */


#ifndef __IADsLocality_FWD_DEFINED__
#define __IADsLocality_FWD_DEFINED__
typedef interface IADsLocality IADsLocality;
#endif 	/* __IADsLocality_FWD_DEFINED__ */


#ifndef __IADsO_FWD_DEFINED__
#define __IADsO_FWD_DEFINED__
typedef interface IADsO IADsO;
#endif 	/* __IADsO_FWD_DEFINED__ */


#ifndef __IADsOU_FWD_DEFINED__
#define __IADsOU_FWD_DEFINED__
typedef interface IADsOU IADsOU;
#endif 	/* __IADsOU_FWD_DEFINED__ */


#ifndef __IADsDomain_FWD_DEFINED__
#define __IADsDomain_FWD_DEFINED__
typedef interface IADsDomain IADsDomain;
#endif 	/* __IADsDomain_FWD_DEFINED__ */


#ifndef __IADsComputer_FWD_DEFINED__
#define __IADsComputer_FWD_DEFINED__
typedef interface IADsComputer IADsComputer;
#endif 	/* __IADsComputer_FWD_DEFINED__ */


#ifndef __IADsComputerOperations_FWD_DEFINED__
#define __IADsComputerOperations_FWD_DEFINED__
typedef interface IADsComputerOperations IADsComputerOperations;
#endif 	/* __IADsComputerOperations_FWD_DEFINED__ */


#ifndef __IADsGroup_FWD_DEFINED__
#define __IADsGroup_FWD_DEFINED__
typedef interface IADsGroup IADsGroup;
#endif 	/* __IADsGroup_FWD_DEFINED__ */


#ifndef __IADsUser_FWD_DEFINED__
#define __IADsUser_FWD_DEFINED__
typedef interface IADsUser IADsUser;
#endif 	/* __IADsUser_FWD_DEFINED__ */


#ifndef __IADsPrintQueue_FWD_DEFINED__
#define __IADsPrintQueue_FWD_DEFINED__
typedef interface IADsPrintQueue IADsPrintQueue;
#endif 	/* __IADsPrintQueue_FWD_DEFINED__ */


#ifndef __IADsPrintQueueOperations_FWD_DEFINED__
#define __IADsPrintQueueOperations_FWD_DEFINED__
typedef interface IADsPrintQueueOperations IADsPrintQueueOperations;
#endif 	/* __IADsPrintQueueOperations_FWD_DEFINED__ */


#ifndef __IADsPrintJob_FWD_DEFINED__
#define __IADsPrintJob_FWD_DEFINED__
typedef interface IADsPrintJob IADsPrintJob;
#endif 	/* __IADsPrintJob_FWD_DEFINED__ */


#ifndef __IADsPrintJobOperations_FWD_DEFINED__
#define __IADsPrintJobOperations_FWD_DEFINED__
typedef interface IADsPrintJobOperations IADsPrintJobOperations;
#endif 	/* __IADsPrintJobOperations_FWD_DEFINED__ */


#ifndef __IADsService_FWD_DEFINED__
#define __IADsService_FWD_DEFINED__
typedef interface IADsService IADsService;
#endif 	/* __IADsService_FWD_DEFINED__ */


#ifndef __IADsServiceOperations_FWD_DEFINED__
#define __IADsServiceOperations_FWD_DEFINED__
typedef interface IADsServiceOperations IADsServiceOperations;
#endif 	/* __IADsServiceOperations_FWD_DEFINED__ */


#ifndef __IADsFileService_FWD_DEFINED__
#define __IADsFileService_FWD_DEFINED__
typedef interface IADsFileService IADsFileService;
#endif 	/* __IADsFileService_FWD_DEFINED__ */


#ifndef __IADsFileServiceOperations_FWD_DEFINED__
#define __IADsFileServiceOperations_FWD_DEFINED__
typedef interface IADsFileServiceOperations IADsFileServiceOperations;
#endif 	/* __IADsFileServiceOperations_FWD_DEFINED__ */


#ifndef __IADsFileShare_FWD_DEFINED__
#define __IADsFileShare_FWD_DEFINED__
typedef interface IADsFileShare IADsFileShare;
#endif 	/* __IADsFileShare_FWD_DEFINED__ */


#ifndef __IADsSession_FWD_DEFINED__
#define __IADsSession_FWD_DEFINED__
typedef interface IADsSession IADsSession;
#endif 	/* __IADsSession_FWD_DEFINED__ */


#ifndef __IADsResource_FWD_DEFINED__
#define __IADsResource_FWD_DEFINED__
typedef interface IADsResource IADsResource;
#endif 	/* __IADsResource_FWD_DEFINED__ */


#ifndef __IADsOpenDSObject_FWD_DEFINED__
#define __IADsOpenDSObject_FWD_DEFINED__
typedef interface IADsOpenDSObject IADsOpenDSObject;
#endif 	/* __IADsOpenDSObject_FWD_DEFINED__ */


#ifndef __IDirectoryObject_FWD_DEFINED__
#define __IDirectoryObject_FWD_DEFINED__
typedef interface IDirectoryObject IDirectoryObject;
#endif 	/* __IDirectoryObject_FWD_DEFINED__ */


#ifndef __IDSObject_FWD_DEFINED__
#define __IDSObject_FWD_DEFINED__
typedef interface IDSObject IDSObject;
#endif 	/* __IDSObject_FWD_DEFINED__ */


#ifndef __IDirectorySearch_FWD_DEFINED__
#define __IDirectorySearch_FWD_DEFINED__
typedef interface IDirectorySearch IDirectorySearch;
#endif 	/* __IDirectorySearch_FWD_DEFINED__ */


#ifndef __IDSSearch_FWD_DEFINED__
#define __IDSSearch_FWD_DEFINED__
typedef interface IDSSearch IDSSearch;
#endif 	/* __IDSSearch_FWD_DEFINED__ */


#ifndef __IDirectoryAttrMgmt_FWD_DEFINED__
#define __IDirectoryAttrMgmt_FWD_DEFINED__
typedef interface IDirectoryAttrMgmt IDirectoryAttrMgmt;
#endif 	/* __IDirectoryAttrMgmt_FWD_DEFINED__ */


#ifndef __IDSAttrMgmt_FWD_DEFINED__
#define __IDSAttrMgmt_FWD_DEFINED__
typedef interface IDSAttrMgmt IDSAttrMgmt;
#endif 	/* __IDSAttrMgmt_FWD_DEFINED__ */


#ifndef __IADsAggregatee_FWD_DEFINED__
#define __IADsAggregatee_FWD_DEFINED__
typedef interface IADsAggregatee IADsAggregatee;
#endif 	/* __IADsAggregatee_FWD_DEFINED__ */


#ifndef __IADsAggregator_FWD_DEFINED__
#define __IADsAggregator_FWD_DEFINED__
typedef interface IADsAggregator IADsAggregator;
#endif 	/* __IADsAggregator_FWD_DEFINED__ */


#ifndef __IADsAccessControlEntry_FWD_DEFINED__
#define __IADsAccessControlEntry_FWD_DEFINED__
typedef interface IADsAccessControlEntry IADsAccessControlEntry;
#endif 	/* __IADsAccessControlEntry_FWD_DEFINED__ */


#ifndef __IADsAccessControlList_FWD_DEFINED__
#define __IADsAccessControlList_FWD_DEFINED__
typedef interface IADsAccessControlList IADsAccessControlList;
#endif 	/* __IADsAccessControlList_FWD_DEFINED__ */


#ifndef __IADsSecurityDescriptor_FWD_DEFINED__
#define __IADsSecurityDescriptor_FWD_DEFINED__
typedef interface IADsSecurityDescriptor IADsSecurityDescriptor;
#endif 	/* __IADsSecurityDescriptor_FWD_DEFINED__ */


#ifndef __IADsLargeInteger_FWD_DEFINED__
#define __IADsLargeInteger_FWD_DEFINED__
typedef interface IADsLargeInteger IADsLargeInteger;
#endif 	/* __IADsLargeInteger_FWD_DEFINED__ */


#ifndef __IADsPathname_FWD_DEFINED__
#define __IADsPathname_FWD_DEFINED__
typedef interface IADsPathname IADsPathname;
#endif 	/* __IADsPathname_FWD_DEFINED__ */


void __RPC_FAR * __RPC_USER MIDL_user_allocate(size_t);
void __RPC_USER MIDL_user_free( void __RPC_FAR * ); 


#ifndef __ActiveDs_LIBRARY_DEFINED__
#define __ActiveDs_LIBRARY_DEFINED__

/****************************************
 * Generated header for library: ActiveDs
 * at Mon Oct 13 13:47:30 1997
 * using MIDL 3.00.44
 ****************************************/
/* [helpstring][version][uuid] */ 


typedef /* [public][public][public][public][public][public][public][public][public][public][public][public][public][public][public][public][public][public][public][public][public][public][public][public][public][public][public][public][public][public][public][public][public][public][public][public][public][public][public][public][public][public][public][public][public][public][public][public][public][public][public][public][public][public] */ 
enum __MIDL___MIDL__intf_0000_0001
    {	ADSTYPE_INVALID	= 0,
	ADSTYPE_DN_STRING	= ADSTYPE_INVALID + 1,
	ADSTYPE_CASE_EXACT_STRING	= ADSTYPE_DN_STRING + 1,
	ADSTYPE_CASE_IGNORE_STRING	= ADSTYPE_CASE_EXACT_STRING + 1,
	ADSTYPE_PRINTABLE_STRING	= ADSTYPE_CASE_IGNORE_STRING + 1,
	ADSTYPE_NUMERIC_STRING	= ADSTYPE_PRINTABLE_STRING + 1,
	ADSTYPE_BOOLEAN	= ADSTYPE_NUMERIC_STRING + 1,
	ADSTYPE_INTEGER	= ADSTYPE_BOOLEAN + 1,
	ADSTYPE_OCTET_STRING	= ADSTYPE_INTEGER + 1,
	ADSTYPE_UTC_TIME	= ADSTYPE_OCTET_STRING + 1,
	ADSTYPE_LARGE_INTEGER	= ADSTYPE_UTC_TIME + 1,
	ADSTYPE_PROV_SPECIFIC	= ADSTYPE_LARGE_INTEGER + 1,
	ADSTYPE_OBJECT_CLASS	= ADSTYPE_PROV_SPECIFIC + 1
    }	ADSTYPEENUM;

typedef ADSTYPEENUM ADSTYPE;

typedef unsigned char BYTE;

typedef unsigned char __RPC_FAR *LPBYTE;

typedef unsigned char __RPC_FAR *PBYTE;

typedef LPWSTR ADS_DN_STRING;

typedef LPWSTR __RPC_FAR *PADS_DN_STRING;

typedef LPWSTR ADS_CASE_EXACT_STRING;

typedef LPWSTR __RPC_FAR *PADS_CASE_EXACT_STRING;

typedef LPWSTR ADS_CASE_IGNORE_STRING;

typedef LPWSTR __RPC_FAR *PADS_CASE_IGNORE_STRING;

typedef LPWSTR ADS_PRINTABLE_STRING;

typedef LPWSTR __RPC_FAR *PADS_PRINTABLE_STRING;

typedef LPWSTR ADS_NUMERIC_STRING;

typedef LPWSTR __RPC_FAR *PADS_NUMERIC_STRING;

typedef DWORD ADS_BOOLEAN;

typedef DWORD __RPC_FAR *LPNDS_BOOLEAN;

typedef DWORD ADS_INTEGER;

typedef DWORD __RPC_FAR *PADS_INTEGER;

typedef /* [public][public][public][public][public][public][public][public][public][public][public][public][public][public][public][public][public][public][public][public][public][public][public][public][public][public][public] */ struct  __MIDL___MIDL__intf_0000_0002
    {
    DWORD dwLength;
    LPBYTE lpValue;
    }	ADS_OCTET_STRING;

typedef struct __MIDL___MIDL__intf_0000_0002 __RPC_FAR *PADS_OCTET_STRING;

typedef SYSTEMTIME ADS_UTC_TIME;

typedef SYSTEMTIME __RPC_FAR *PADS_UTC_TIME;

typedef LARGE_INTEGER ADS_LARGE_INTEGER;

typedef LARGE_INTEGER __RPC_FAR *PADS_LARGE_INTEGER;

typedef LPWSTR ADS_OBJECT_CLASS;

typedef LPWSTR __RPC_FAR *PADS_OBJECT_CLASS;

typedef /* [public][public][public][public][public][public][public][public][public][public][public][public][public][public][public][public][public][public][public][public][public][public][public][public][public][public][public] */ struct  __MIDL___MIDL__intf_0000_0003
    {
    DWORD dwLength;
    LPBYTE lpValue;
    }	ADS_PROV_SPECIFIC;

typedef struct __MIDL___MIDL__intf_0000_0003 __RPC_FAR *PADS_PROV_SPECIFIC;

typedef struct  _adsvalue
    {
    ADSTYPE dwType;
    union 
        {
        ADS_DN_STRING DNString;
        ADS_CASE_EXACT_STRING CaseExactString;
        ADS_CASE_IGNORE_STRING CaseIgnoreString;
        ADS_PRINTABLE_STRING PrintableString;
        ADS_NUMERIC_STRING NumericString;
        ADS_BOOLEAN Boolean;
        ADS_INTEGER Integer;
        ADS_OCTET_STRING OctetString;
        ADS_UTC_TIME UTCTime;
        ADS_LARGE_INTEGER LargeInteger;
        ADS_OBJECT_CLASS ClassName;
        ADS_PROV_SPECIFIC ProviderSpecific;
        }	;
    }	ADSVALUE;

typedef struct _adsvalue __RPC_FAR *PADSVALUE;

typedef struct _adsvalue __RPC_FAR *LPADSVALUE;

typedef struct  _ads_attr_info
    {
    LPWSTR pszAttrName;
    DWORD dwControlCode;
    ADSTYPE dwADsType;
    PADSVALUE pADsValues;
    DWORD dwNumValues;
    }	ADS_ATTR_INFO;

typedef struct _ads_attr_info __RPC_FAR *PADS_ATTR_INFO;

#define	ADS_SECURE_AUTHENTICATION	( 0x1 )

#define	ADS_USE_ENCRYPTION	( 0x2 )

#define	ADS_READONLY_SERVER	( 0x4 )

#define	ADS_PROMPT_CREDENTIALS	( 0x8 )

#define	ADS_ATTR_CLEAR	( 1 )

#define	ADS_ATTR_UPDATE	( 2 )

#define	ADS_ATTR_APPEND	( 3 )

#define	ADS_ATTR_DELETE	( 4 )

typedef struct  _ads_object_info
    {
    LPWSTR pszRDN;
    LPWSTR pszObjectDN;
    LPWSTR pszParentDN;
    LPWSTR pszSchemaDN;
    LPWSTR pszClassName;
    }	ADS_OBJECT_INFO;

typedef struct _ads_object_info __RPC_FAR *PADS_OBJECT_INFO;

typedef /* [public][public][public][public][public][public][public][public] */ 
enum __MIDL___MIDL__intf_0000_0005
    {	ADS_STATUS_S_OK	= 0,
	ADS_STATUS_INVALID_SEARCHPREF	= ADS_STATUS_S_OK + 1,
	ADS_STATUS_INVALID_SEARCHPREFVALUE	= ADS_STATUS_INVALID_SEARCHPREF + 1
    }	ADS_STATUSENUM;

typedef ADS_STATUSENUM ADS_STATUS;

typedef ADS_STATUSENUM __RPC_FAR *PADS_STATUS;

typedef /* [public] */ 
enum __MIDL___MIDL__intf_0000_0006
    {	ADS_DEREF_NEVER	= 0,
	ADS_DEREF_SEARCHING	= 1,
	ADS_DEREF_FINDING	= 2,
	ADS_DEREF_ALWAYS	= 3
    }	ADS_DEREFENUM;

typedef /* [public] */ 
enum __MIDL___MIDL__intf_0000_0007
    {	ADS_SCOPE_BASE	= 0,
	ADS_SCOPE_ONELEVEL	= 1,
	ADS_SCOPE_SUBTREE	= 2
    }	ADS_SCOPEENUM;

#define	ADS_CHASE_REFERRALS_NEVER	( 0 )

#define	ADS_CHASE_REFERRALS_SUBORDINATE	( 0x20 )

#define	ADS_CHASE_REFERRALS_EXTERNAL	( 0x40 )

#define	ADS_CHASE_REFERRALS_ALWAYS	( ADS_CHASE_REFERRALS_SUBORDINATE | ADS_CHASE_REFERRALS_EXTERNAL )

typedef /* [public][public][public][public][public][public][public] */ 
enum __MIDL___MIDL__intf_0000_0008
    {	ADS_SEARCHPREF_ASYNCHRONOUS	= 0,
	ADS_SEARCHPREF_DEREF_ALIASES	= ADS_SEARCHPREF_ASYNCHRONOUS + 1,
	ADS_SEARCHPREF_SIZE_LIMIT	= ADS_SEARCHPREF_DEREF_ALIASES + 1,
	ADS_SEARCHPREF_TIME_LIMIT	= ADS_SEARCHPREF_SIZE_LIMIT + 1,
	ADS_SEARCHPREF_ATTRIBTYPES_ONLY	= ADS_SEARCHPREF_TIME_LIMIT + 1,
	ADS_SEARCHPREF_SEARCH_SCOPE	= ADS_SEARCHPREF_ATTRIBTYPES_ONLY + 1,
	ADS_SEARCHPREF_TIMEOUT	= ADS_SEARCHPREF_SEARCH_SCOPE + 1,
	ADS_SEARCHPREF_PAGESIZE	= ADS_SEARCHPREF_TIMEOUT + 1,
	ADS_SEARCHPREF_PAGED_TIME_LIMIT	= ADS_SEARCHPREF_PAGESIZE + 1,
	ADS_SEARCHPREF_CHASE_REFERRALS	= ADS_SEARCHPREF_PAGED_TIME_LIMIT + 1,
	ADS_SEARCHPREF_SORT_ON	= ADS_SEARCHPREF_CHASE_REFERRALS + 1
    }	ADS_SEARCHPREF_ENUM;

typedef ADS_SEARCHPREF_ENUM ADS_SEARCHPREF;

typedef struct  ads_searchpref_info
    {
    ADS_SEARCHPREF dwSearchPref;
    ADSVALUE vValue;
    ADS_STATUS dwStatus;
    }	ADS_SEARCHPREF_INFO;

typedef struct ads_searchpref_info __RPC_FAR *PADS_SEARCHPREF_INFO;

typedef struct ads_searchpref_info __RPC_FAR *LPADS_SEARCHPREF_INFO;

typedef HANDLE ADS_SEARCH_HANDLE;

typedef HANDLE __RPC_FAR *PADS_SEARCH_HANDLE;

typedef struct  ads_search_column
    {
    LPWSTR pszAttrName;
    ADSTYPE dwADsType;
    PADSVALUE pADsValues;
    DWORD dwNumValues;
    HANDLE hReserved;
    }	ADS_SEARCH_COLUMN;

typedef struct ads_search_column __RPC_FAR *PADS_SEARCH_COLUMN;

typedef struct  _ads_attr_def
    {
    LPWSTR pszAttrName;
    ADSTYPE dwADsType;
    DWORD dwMinRange;
    DWORD dwMaxRange;
    BOOL fMultiValued;
    }	ADS_ATTR_DEF;

typedef struct _ads_attr_def __RPC_FAR *PADS_ATTR_DEF;

typedef struct  _ads_sortkey
    {
    LPWSTR pszAttrType;
    LPWSTR pszReserved;
    BOOLEAN fReverseorder;
    }	ADS_SORTKEY;

typedef struct _ads_sortkey __RPC_FAR *PADS_SORTKEY;


enum __MIDL___MIDL__intf_0000_0009
    {	ADS_PROPERTY_CLEAR	= 1,
	ADS_PROPERTY_UPDATE	= 2,
	ADS_PROPERTY_APPEND	= 3,
	ADS_PROPERTY_DELETE	= 4
    };

enum __MIDL___MIDL__intf_0115_0001
    {	ADS_SETTYPE_FULL	= 1,
	ADS_SETTYPE_PROVIDER	= 2,
	ADS_SETTYPE_SERVER	= 3,
	ADS_SETTYPE_DN	= 4
    };

enum __MIDL___MIDL__intf_0115_0002
    {	ADS_FORMAT_WINDOWS	= 1,
	ADS_FORMAT_WINDOWS_NO_SERVER	= 2,
	ADS_FORMAT_WINDOWS_DN	= 3,
	ADS_FORMAT_WINDOWS_PARENT	= 4,
	ADS_FORMAT_X500	= 5,
	ADS_FORMAT_X500_NO_SERVER	= 6,
	ADS_FORMAT_X500_DN	= 7,
	ADS_FORMAT_X500_PARENT	= 8,
	ADS_FORMAT_SERVER	= 9,
	ADS_FORMAT_PROVIDER	= 10,
	ADS_FORMAT_LEAF	= 11
    };

enum __MIDL___MIDL__intf_0115_0003
    {	ADS_DISPLAY_FULL	= 1,
	ADS_DISPLAY_VALUE_ONLY	= 2
    };

EXTERN_C const IID LIBID_ActiveDs;

#ifndef __IADs_INTERFACE_DEFINED__
#define __IADs_INTERFACE_DEFINED__

/****************************************
 * Generated header for interface: IADs
 * at Mon Oct 13 13:47:30 1997
 * using MIDL 3.00.44
 ****************************************/
/* [object][dual][oleautomation][uuid] */ 



EXTERN_C const IID IID_IADs;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    interface IADs : public IDispatch
    {
    public:
        virtual /* [id][propget] */ HRESULT STDMETHODCALLTYPE get_Name( 
            /* [retval][out] */ BSTR __RPC_FAR *retval) = 0;
        
        virtual /* [id][propget] */ HRESULT STDMETHODCALLTYPE get_Class( 
            /* [retval][out] */ BSTR __RPC_FAR *retval) = 0;
        
        virtual /* [id][propget] */ HRESULT STDMETHODCALLTYPE get_GUID( 
            /* [retval][out] */ BSTR __RPC_FAR *retval) = 0;
        
        virtual /* [id][propget] */ HRESULT STDMETHODCALLTYPE get_ADsPath( 
            /* [retval][out] */ BSTR __RPC_FAR *retval) = 0;
        
        virtual /* [id][propget] */ HRESULT STDMETHODCALLTYPE get_Parent( 
            /* [retval][out] */ BSTR __RPC_FAR *retval) = 0;
        
        virtual /* [id][propget] */ HRESULT STDMETHODCALLTYPE get_Schema( 
            /* [retval][out] */ BSTR __RPC_FAR *retval) = 0;
        
        virtual /* [id] */ HRESULT STDMETHODCALLTYPE GetInfo( void) = 0;
        
        virtual /* [id] */ HRESULT STDMETHODCALLTYPE SetInfo( void) = 0;
        
        virtual /* [id] */ HRESULT STDMETHODCALLTYPE Get( 
            /* [in] */ BSTR bstrName,
            /* [retval][out] */ VARIANT __RPC_FAR *pvProp) = 0;
        
        virtual /* [id] */ HRESULT STDMETHODCALLTYPE Put( 
            /* [in] */ BSTR bstrName,
            /* [in] */ VARIANT vProp) = 0;
        
        virtual /* [id] */ HRESULT STDMETHODCALLTYPE GetEx( 
            /* [in] */ BSTR bstrName,
            /* [retval][out] */ VARIANT __RPC_FAR *pvProp) = 0;
        
        virtual /* [id] */ HRESULT STDMETHODCALLTYPE PutEx( 
            /* [in] */ long lnControlCode,
            /* [in] */ BSTR bstrName,
            /* [in] */ VARIANT vProp) = 0;
        
        virtual /* [id] */ HRESULT STDMETHODCALLTYPE GetInfoEx( 
            /* [in] */ VARIANT vProperties,
            /* [in] */ long lnReserved) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IADsVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            IADs __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            IADs __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            IADs __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfoCount )( 
            IADs __RPC_FAR * This,
            /* [out] */ UINT __RPC_FAR *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfo )( 
            IADs __RPC_FAR * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo __RPC_FAR *__RPC_FAR *ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetIDsOfNames )( 
            IADs __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR __RPC_FAR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID __RPC_FAR *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Invoke )( 
            IADs __RPC_FAR * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS __RPC_FAR *pDispParams,
            /* [out] */ VARIANT __RPC_FAR *pVarResult,
            /* [out] */ EXCEPINFO __RPC_FAR *pExcepInfo,
            /* [out] */ UINT __RPC_FAR *puArgErr);
        
        /* [id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Name )( 
            IADs __RPC_FAR * This,
            /* [retval][out] */ BSTR __RPC_FAR *retval);
        
        /* [id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Class )( 
            IADs __RPC_FAR * This,
            /* [retval][out] */ BSTR __RPC_FAR *retval);
        
        /* [id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_GUID )( 
            IADs __RPC_FAR * This,
            /* [retval][out] */ BSTR __RPC_FAR *retval);
        
        /* [id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_ADsPath )( 
            IADs __RPC_FAR * This,
            /* [retval][out] */ BSTR __RPC_FAR *retval);
        
        /* [id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Parent )( 
            IADs __RPC_FAR * This,
            /* [retval][out] */ BSTR __RPC_FAR *retval);
        
        /* [id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Schema )( 
            IADs __RPC_FAR * This,
            /* [retval][out] */ BSTR __RPC_FAR *retval);
        
        /* [id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetInfo )( 
            IADs __RPC_FAR * This);
        
        /* [id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *SetInfo )( 
            IADs __RPC_FAR * This);
        
        /* [id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Get )( 
            IADs __RPC_FAR * This,
            /* [in] */ BSTR bstrName,
            /* [retval][out] */ VARIANT __RPC_FAR *pvProp);
        
        /* [id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Put )( 
            IADs __RPC_FAR * This,
            /* [in] */ BSTR bstrName,
            /* [in] */ VARIANT vProp);
        
        /* [id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetEx )( 
            IADs __RPC_FAR * This,
            /* [in] */ BSTR bstrName,
            /* [retval][out] */ VARIANT __RPC_FAR *pvProp);
        
        /* [id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *PutEx )( 
            IADs __RPC_FAR * This,
            /* [in] */ long lnControlCode,
            /* [in] */ BSTR bstrName,
            /* [in] */ VARIANT vProp);
        
        /* [id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetInfoEx )( 
            IADs __RPC_FAR * This,
            /* [in] */ VARIANT vProperties,
            /* [in] */ long lnReserved);
        
        END_INTERFACE
    } IADsVtbl;

    interface IADs
    {
        CONST_VTBL struct IADsVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IADs_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IADs_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IADs_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IADs_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define IADs_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define IADs_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define IADs_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)


#define IADs_get_Name(This,retval)	\
    (This)->lpVtbl -> get_Name(This,retval)

#define IADs_get_Class(This,retval)	\
    (This)->lpVtbl -> get_Class(This,retval)

#define IADs_get_GUID(This,retval)	\
    (This)->lpVtbl -> get_GUID(This,retval)

#define IADs_get_ADsPath(This,retval)	\
    (This)->lpVtbl -> get_ADsPath(This,retval)

#define IADs_get_Parent(This,retval)	\
    (This)->lpVtbl -> get_Parent(This,retval)

#define IADs_get_Schema(This,retval)	\
    (This)->lpVtbl -> get_Schema(This,retval)

#define IADs_GetInfo(This)	\
    (This)->lpVtbl -> GetInfo(This)

#define IADs_SetInfo(This)	\
    (This)->lpVtbl -> SetInfo(This)

#define IADs_Get(This,bstrName,pvProp)	\
    (This)->lpVtbl -> Get(This,bstrName,pvProp)

#define IADs_Put(This,bstrName,vProp)	\
    (This)->lpVtbl -> Put(This,bstrName,vProp)

#define IADs_GetEx(This,bstrName,pvProp)	\
    (This)->lpVtbl -> GetEx(This,bstrName,pvProp)

#define IADs_PutEx(This,lnControlCode,bstrName,vProp)	\
    (This)->lpVtbl -> PutEx(This,lnControlCode,bstrName,vProp)

#define IADs_GetInfoEx(This,vProperties,lnReserved)	\
    (This)->lpVtbl -> GetInfoEx(This,vProperties,lnReserved)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [id][propget] */ HRESULT STDMETHODCALLTYPE IADs_get_Name_Proxy( 
    IADs __RPC_FAR * This,
    /* [retval][out] */ BSTR __RPC_FAR *retval);


void __RPC_STUB IADs_get_Name_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [id][propget] */ HRESULT STDMETHODCALLTYPE IADs_get_Class_Proxy( 
    IADs __RPC_FAR * This,
    /* [retval][out] */ BSTR __RPC_FAR *retval);


void __RPC_STUB IADs_get_Class_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [id][propget] */ HRESULT STDMETHODCALLTYPE IADs_get_GUID_Proxy( 
    IADs __RPC_FAR * This,
    /* [retval][out] */ BSTR __RPC_FAR *retval);


void __RPC_STUB IADs_get_GUID_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [id][propget] */ HRESULT STDMETHODCALLTYPE IADs_get_ADsPath_Proxy( 
    IADs __RPC_FAR * This,
    /* [retval][out] */ BSTR __RPC_FAR *retval);


void __RPC_STUB IADs_get_ADsPath_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [id][propget] */ HRESULT STDMETHODCALLTYPE IADs_get_Parent_Proxy( 
    IADs __RPC_FAR * This,
    /* [retval][out] */ BSTR __RPC_FAR *retval);


void __RPC_STUB IADs_get_Parent_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [id][propget] */ HRESULT STDMETHODCALLTYPE IADs_get_Schema_Proxy( 
    IADs __RPC_FAR * This,
    /* [retval][out] */ BSTR __RPC_FAR *retval);


void __RPC_STUB IADs_get_Schema_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [id] */ HRESULT STDMETHODCALLTYPE IADs_GetInfo_Proxy( 
    IADs __RPC_FAR * This);


void __RPC_STUB IADs_GetInfo_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [id] */ HRESULT STDMETHODCALLTYPE IADs_SetInfo_Proxy( 
    IADs __RPC_FAR * This);


void __RPC_STUB IADs_SetInfo_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [id] */ HRESULT STDMETHODCALLTYPE IADs_Get_Proxy( 
    IADs __RPC_FAR * This,
    /* [in] */ BSTR bstrName,
    /* [retval][out] */ VARIANT __RPC_FAR *pvProp);


void __RPC_STUB IADs_Get_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [id] */ HRESULT STDMETHODCALLTYPE IADs_Put_Proxy( 
    IADs __RPC_FAR * This,
    /* [in] */ BSTR bstrName,
    /* [in] */ VARIANT vProp);


void __RPC_STUB IADs_Put_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [id] */ HRESULT STDMETHODCALLTYPE IADs_GetEx_Proxy( 
    IADs __RPC_FAR * This,
    /* [in] */ BSTR bstrName,
    /* [retval][out] */ VARIANT __RPC_FAR *pvProp);


void __RPC_STUB IADs_GetEx_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [id] */ HRESULT STDMETHODCALLTYPE IADs_PutEx_Proxy( 
    IADs __RPC_FAR * This,
    /* [in] */ long lnControlCode,
    /* [in] */ BSTR bstrName,
    /* [in] */ VARIANT vProp);


void __RPC_STUB IADs_PutEx_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [id] */ HRESULT STDMETHODCALLTYPE IADs_GetInfoEx_Proxy( 
    IADs __RPC_FAR * This,
    /* [in] */ VARIANT vProperties,
    /* [in] */ long lnReserved);


void __RPC_STUB IADs_GetInfoEx_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IADs_INTERFACE_DEFINED__ */


#ifndef __IADsContainer_INTERFACE_DEFINED__
#define __IADsContainer_INTERFACE_DEFINED__

/****************************************
 * Generated header for interface: IADsContainer
 * at Mon Oct 13 13:47:30 1997
 * using MIDL 3.00.44
 ****************************************/
/* [object][dual][oleautomation][uuid] */ 



EXTERN_C const IID IID_IADsContainer;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    interface IADsContainer : public IDispatch
    {
    public:
        virtual /* [id][propget] */ HRESULT STDMETHODCALLTYPE get_Count( 
            /* [retval][out] */ long __RPC_FAR *retval) = 0;
        
        virtual /* [id][restricted][propget] */ HRESULT STDMETHODCALLTYPE get__NewEnum( 
            /* [retval][out] */ IUnknown __RPC_FAR *__RPC_FAR *retval) = 0;
        
        virtual /* [id][propget] */ HRESULT STDMETHODCALLTYPE get_Filter( 
            /* [retval][out] */ VARIANT __RPC_FAR *pVar) = 0;
        
        virtual /* [id][propput] */ HRESULT STDMETHODCALLTYPE put_Filter( 
            /* [in] */ VARIANT Var) = 0;
        
        virtual /* [id][propget] */ HRESULT STDMETHODCALLTYPE get_Hints( 
            /* [retval][out] */ VARIANT __RPC_FAR *pvFilter) = 0;
        
        virtual /* [id][propput] */ HRESULT STDMETHODCALLTYPE put_Hints( 
            /* [in] */ VARIANT vHints) = 0;
        
        virtual /* [id] */ HRESULT STDMETHODCALLTYPE GetObject( 
            /* [in] */ BSTR ClassName,
            /* [in] */ BSTR RelativeName,
            /* [retval][out] */ IDispatch __RPC_FAR *__RPC_FAR *ppObject) = 0;
        
        virtual /* [id] */ HRESULT STDMETHODCALLTYPE Create( 
            /* [in] */ BSTR ClassName,
            /* [in] */ BSTR RelativeName,
            /* [retval][out] */ IDispatch __RPC_FAR *__RPC_FAR *ppObject) = 0;
        
        virtual /* [id] */ HRESULT STDMETHODCALLTYPE Delete( 
            /* [in] */ BSTR bstrClassName,
            /* [in] */ BSTR bstrRelativeName) = 0;
        
        virtual /* [id] */ HRESULT STDMETHODCALLTYPE CopyHere( 
            /* [in] */ BSTR SourceName,
            /* [in] */ BSTR NewName,
            /* [out][retval] */ IDispatch __RPC_FAR *__RPC_FAR *ppObject) = 0;
        
        virtual /* [id] */ HRESULT STDMETHODCALLTYPE MoveHere( 
            /* [in] */ BSTR SourceName,
            /* [in] */ BSTR NewName,
            /* [out][retval] */ IDispatch __RPC_FAR *__RPC_FAR *ppObject) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IADsContainerVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            IADsContainer __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            IADsContainer __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            IADsContainer __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfoCount )( 
            IADsContainer __RPC_FAR * This,
            /* [out] */ UINT __RPC_FAR *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfo )( 
            IADsContainer __RPC_FAR * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo __RPC_FAR *__RPC_FAR *ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetIDsOfNames )( 
            IADsContainer __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR __RPC_FAR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID __RPC_FAR *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Invoke )( 
            IADsContainer __RPC_FAR * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS __RPC_FAR *pDispParams,
            /* [out] */ VARIANT __RPC_FAR *pVarResult,
            /* [out] */ EXCEPINFO __RPC_FAR *pExcepInfo,
            /* [out] */ UINT __RPC_FAR *puArgErr);
        
        /* [id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Count )( 
            IADsContainer __RPC_FAR * This,
            /* [retval][out] */ long __RPC_FAR *retval);
        
        /* [id][restricted][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get__NewEnum )( 
            IADsContainer __RPC_FAR * This,
            /* [retval][out] */ IUnknown __RPC_FAR *__RPC_FAR *retval);
        
        /* [id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Filter )( 
            IADsContainer __RPC_FAR * This,
            /* [retval][out] */ VARIANT __RPC_FAR *pVar);
        
        /* [id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_Filter )( 
            IADsContainer __RPC_FAR * This,
            /* [in] */ VARIANT Var);
        
        /* [id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Hints )( 
            IADsContainer __RPC_FAR * This,
            /* [retval][out] */ VARIANT __RPC_FAR *pvFilter);
        
        /* [id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_Hints )( 
            IADsContainer __RPC_FAR * This,
            /* [in] */ VARIANT vHints);
        
        /* [id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetObject )( 
            IADsContainer __RPC_FAR * This,
            /* [in] */ BSTR ClassName,
            /* [in] */ BSTR RelativeName,
            /* [retval][out] */ IDispatch __RPC_FAR *__RPC_FAR *ppObject);
        
        /* [id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Create )( 
            IADsContainer __RPC_FAR * This,
            /* [in] */ BSTR ClassName,
            /* [in] */ BSTR RelativeName,
            /* [retval][out] */ IDispatch __RPC_FAR *__RPC_FAR *ppObject);
        
        /* [id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Delete )( 
            IADsContainer __RPC_FAR * This,
            /* [in] */ BSTR bstrClassName,
            /* [in] */ BSTR bstrRelativeName);
        
        /* [id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *CopyHere )( 
            IADsContainer __RPC_FAR * This,
            /* [in] */ BSTR SourceName,
            /* [in] */ BSTR NewName,
            /* [out][retval] */ IDispatch __RPC_FAR *__RPC_FAR *ppObject);
        
        /* [id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *MoveHere )( 
            IADsContainer __RPC_FAR * This,
            /* [in] */ BSTR SourceName,
            /* [in] */ BSTR NewName,
            /* [out][retval] */ IDispatch __RPC_FAR *__RPC_FAR *ppObject);
        
        END_INTERFACE
    } IADsContainerVtbl;

    interface IADsContainer
    {
        CONST_VTBL struct IADsContainerVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IADsContainer_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IADsContainer_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IADsContainer_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IADsContainer_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define IADsContainer_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define IADsContainer_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define IADsContainer_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)


#define IADsContainer_get_Count(This,retval)	\
    (This)->lpVtbl -> get_Count(This,retval)

#define IADsContainer_get__NewEnum(This,retval)	\
    (This)->lpVtbl -> get__NewEnum(This,retval)

#define IADsContainer_get_Filter(This,pVar)	\
    (This)->lpVtbl -> get_Filter(This,pVar)

#define IADsContainer_put_Filter(This,Var)	\
    (This)->lpVtbl -> put_Filter(This,Var)

#define IADsContainer_get_Hints(This,pvFilter)	\
    (This)->lpVtbl -> get_Hints(This,pvFilter)

#define IADsContainer_put_Hints(This,vHints)	\
    (This)->lpVtbl -> put_Hints(This,vHints)

#define IADsContainer_GetObject(This,ClassName,RelativeName,ppObject)	\
    (This)->lpVtbl -> GetObject(This,ClassName,RelativeName,ppObject)

#define IADsContainer_Create(This,ClassName,RelativeName,ppObject)	\
    (This)->lpVtbl -> Create(This,ClassName,RelativeName,ppObject)

#define IADsContainer_Delete(This,bstrClassName,bstrRelativeName)	\
    (This)->lpVtbl -> Delete(This,bstrClassName,bstrRelativeName)

#define IADsContainer_CopyHere(This,SourceName,NewName,ppObject)	\
    (This)->lpVtbl -> CopyHere(This,SourceName,NewName,ppObject)

#define IADsContainer_MoveHere(This,SourceName,NewName,ppObject)	\
    (This)->lpVtbl -> MoveHere(This,SourceName,NewName,ppObject)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [id][propget] */ HRESULT STDMETHODCALLTYPE IADsContainer_get_Count_Proxy( 
    IADsContainer __RPC_FAR * This,
    /* [retval][out] */ long __RPC_FAR *retval);


void __RPC_STUB IADsContainer_get_Count_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [id][restricted][propget] */ HRESULT STDMETHODCALLTYPE IADsContainer_get__NewEnum_Proxy( 
    IADsContainer __RPC_FAR * This,
    /* [retval][out] */ IUnknown __RPC_FAR *__RPC_FAR *retval);


void __RPC_STUB IADsContainer_get__NewEnum_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [id][propget] */ HRESULT STDMETHODCALLTYPE IADsContainer_get_Filter_Proxy( 
    IADsContainer __RPC_FAR * This,
    /* [retval][out] */ VARIANT __RPC_FAR *pVar);


void __RPC_STUB IADsContainer_get_Filter_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [id][propput] */ HRESULT STDMETHODCALLTYPE IADsContainer_put_Filter_Proxy( 
    IADsContainer __RPC_FAR * This,
    /* [in] */ VARIANT Var);


void __RPC_STUB IADsContainer_put_Filter_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [id][propget] */ HRESULT STDMETHODCALLTYPE IADsContainer_get_Hints_Proxy( 
    IADsContainer __RPC_FAR * This,
    /* [retval][out] */ VARIANT __RPC_FAR *pvFilter);


void __RPC_STUB IADsContainer_get_Hints_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [id][propput] */ HRESULT STDMETHODCALLTYPE IADsContainer_put_Hints_Proxy( 
    IADsContainer __RPC_FAR * This,
    /* [in] */ VARIANT vHints);


void __RPC_STUB IADsContainer_put_Hints_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [id] */ HRESULT STDMETHODCALLTYPE IADsContainer_GetObject_Proxy( 
    IADsContainer __RPC_FAR * This,
    /* [in] */ BSTR ClassName,
    /* [in] */ BSTR RelativeName,
    /* [retval][out] */ IDispatch __RPC_FAR *__RPC_FAR *ppObject);


void __RPC_STUB IADsContainer_GetObject_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [id] */ HRESULT STDMETHODCALLTYPE IADsContainer_Create_Proxy( 
    IADsContainer __RPC_FAR * This,
    /* [in] */ BSTR ClassName,
    /* [in] */ BSTR RelativeName,
    /* [retval][out] */ IDispatch __RPC_FAR *__RPC_FAR *ppObject);


void __RPC_STUB IADsContainer_Create_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [id] */ HRESULT STDMETHODCALLTYPE IADsContainer_Delete_Proxy( 
    IADsContainer __RPC_FAR * This,
    /* [in] */ BSTR bstrClassName,
    /* [in] */ BSTR bstrRelativeName);


void __RPC_STUB IADsContainer_Delete_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [id] */ HRESULT STDMETHODCALLTYPE IADsContainer_CopyHere_Proxy( 
    IADsContainer __RPC_FAR * This,
    /* [in] */ BSTR SourceName,
    /* [in] */ BSTR NewName,
    /* [out][retval] */ IDispatch __RPC_FAR *__RPC_FAR *ppObject);


void __RPC_STUB IADsContainer_CopyHere_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [id] */ HRESULT STDMETHODCALLTYPE IADsContainer_MoveHere_Proxy( 
    IADsContainer __RPC_FAR * This,
    /* [in] */ BSTR SourceName,
    /* [in] */ BSTR NewName,
    /* [out][retval] */ IDispatch __RPC_FAR *__RPC_FAR *ppObject);


void __RPC_STUB IADsContainer_MoveHere_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IADsContainer_INTERFACE_DEFINED__ */


#ifndef __IADsCollection_INTERFACE_DEFINED__
#define __IADsCollection_INTERFACE_DEFINED__

/****************************************
 * Generated header for interface: IADsCollection
 * at Mon Oct 13 13:47:30 1997
 * using MIDL 3.00.44
 ****************************************/
/* [object][dual][oleautomation][uuid] */ 



EXTERN_C const IID IID_IADsCollection;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    interface IADsCollection : public IDispatch
    {
    public:
        virtual /* [propget][id] */ HRESULT STDMETHODCALLTYPE get__NewEnum( 
            /* [retval][out] */ IUnknown __RPC_FAR *__RPC_FAR *ppEnumerator) = 0;
        
        virtual /* [id] */ HRESULT STDMETHODCALLTYPE Add( 
            /* [in] */ BSTR bstrName,
            /* [in] */ VARIANT vItem) = 0;
        
        virtual /* [id] */ HRESULT STDMETHODCALLTYPE Remove( 
            /* [in] */ BSTR bstrItemToBeRemoved) = 0;
        
        virtual /* [id] */ HRESULT STDMETHODCALLTYPE GetObject( 
            /* [in] */ BSTR bstrName,
            /* [retval][out] */ VARIANT __RPC_FAR *pvItem) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IADsCollectionVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            IADsCollection __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            IADsCollection __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            IADsCollection __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfoCount )( 
            IADsCollection __RPC_FAR * This,
            /* [out] */ UINT __RPC_FAR *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfo )( 
            IADsCollection __RPC_FAR * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo __RPC_FAR *__RPC_FAR *ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetIDsOfNames )( 
            IADsCollection __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR __RPC_FAR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID __RPC_FAR *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Invoke )( 
            IADsCollection __RPC_FAR * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS __RPC_FAR *pDispParams,
            /* [out] */ VARIANT __RPC_FAR *pVarResult,
            /* [out] */ EXCEPINFO __RPC_FAR *pExcepInfo,
            /* [out] */ UINT __RPC_FAR *puArgErr);
        
        /* [propget][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get__NewEnum )( 
            IADsCollection __RPC_FAR * This,
            /* [retval][out] */ IUnknown __RPC_FAR *__RPC_FAR *ppEnumerator);
        
        /* [id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Add )( 
            IADsCollection __RPC_FAR * This,
            /* [in] */ BSTR bstrName,
            /* [in] */ VARIANT vItem);
        
        /* [id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Remove )( 
            IADsCollection __RPC_FAR * This,
            /* [in] */ BSTR bstrItemToBeRemoved);
        
        /* [id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetObject )( 
            IADsCollection __RPC_FAR * This,
            /* [in] */ BSTR bstrName,
            /* [retval][out] */ VARIANT __RPC_FAR *pvItem);
        
        END_INTERFACE
    } IADsCollectionVtbl;

    interface IADsCollection
    {
        CONST_VTBL struct IADsCollectionVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IADsCollection_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IADsCollection_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IADsCollection_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IADsCollection_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define IADsCollection_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define IADsCollection_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define IADsCollection_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)


#define IADsCollection_get__NewEnum(This,ppEnumerator)	\
    (This)->lpVtbl -> get__NewEnum(This,ppEnumerator)

#define IADsCollection_Add(This,bstrName,vItem)	\
    (This)->lpVtbl -> Add(This,bstrName,vItem)

#define IADsCollection_Remove(This,bstrItemToBeRemoved)	\
    (This)->lpVtbl -> Remove(This,bstrItemToBeRemoved)

#define IADsCollection_GetObject(This,bstrName,pvItem)	\
    (This)->lpVtbl -> GetObject(This,bstrName,pvItem)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [propget][id] */ HRESULT STDMETHODCALLTYPE IADsCollection_get__NewEnum_Proxy( 
    IADsCollection __RPC_FAR * This,
    /* [retval][out] */ IUnknown __RPC_FAR *__RPC_FAR *ppEnumerator);


void __RPC_STUB IADsCollection_get__NewEnum_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [id] */ HRESULT STDMETHODCALLTYPE IADsCollection_Add_Proxy( 
    IADsCollection __RPC_FAR * This,
    /* [in] */ BSTR bstrName,
    /* [in] */ VARIANT vItem);


void __RPC_STUB IADsCollection_Add_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [id] */ HRESULT STDMETHODCALLTYPE IADsCollection_Remove_Proxy( 
    IADsCollection __RPC_FAR * This,
    /* [in] */ BSTR bstrItemToBeRemoved);


void __RPC_STUB IADsCollection_Remove_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [id] */ HRESULT STDMETHODCALLTYPE IADsCollection_GetObject_Proxy( 
    IADsCollection __RPC_FAR * This,
    /* [in] */ BSTR bstrName,
    /* [retval][out] */ VARIANT __RPC_FAR *pvItem);


void __RPC_STUB IADsCollection_GetObject_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IADsCollection_INTERFACE_DEFINED__ */


#ifndef __IADsMembers_INTERFACE_DEFINED__
#define __IADsMembers_INTERFACE_DEFINED__

/****************************************
 * Generated header for interface: IADsMembers
 * at Mon Oct 13 13:47:30 1997
 * using MIDL 3.00.44
 ****************************************/
/* [object][dual][oleautomation][uuid] */ 



EXTERN_C const IID IID_IADsMembers;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    interface IADsMembers : public IDispatch
    {
    public:
        virtual /* [propget][id] */ HRESULT STDMETHODCALLTYPE get_Count( 
            /* [retval][out] */ long __RPC_FAR *plCount) = 0;
        
        virtual /* [propget][id] */ HRESULT STDMETHODCALLTYPE get__NewEnum( 
            /* [retval][out] */ IUnknown __RPC_FAR *__RPC_FAR *ppEnumerator) = 0;
        
        virtual /* [propget][id] */ HRESULT STDMETHODCALLTYPE get_Filter( 
            /* [retval][out] */ VARIANT __RPC_FAR *pvFilter) = 0;
        
        virtual /* [propput][id] */ HRESULT STDMETHODCALLTYPE put_Filter( 
            /* [in] */ VARIANT pvFilter) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IADsMembersVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            IADsMembers __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            IADsMembers __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            IADsMembers __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfoCount )( 
            IADsMembers __RPC_FAR * This,
            /* [out] */ UINT __RPC_FAR *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfo )( 
            IADsMembers __RPC_FAR * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo __RPC_FAR *__RPC_FAR *ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetIDsOfNames )( 
            IADsMembers __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR __RPC_FAR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID __RPC_FAR *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Invoke )( 
            IADsMembers __RPC_FAR * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS __RPC_FAR *pDispParams,
            /* [out] */ VARIANT __RPC_FAR *pVarResult,
            /* [out] */ EXCEPINFO __RPC_FAR *pExcepInfo,
            /* [out] */ UINT __RPC_FAR *puArgErr);
        
        /* [propget][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Count )( 
            IADsMembers __RPC_FAR * This,
            /* [retval][out] */ long __RPC_FAR *plCount);
        
        /* [propget][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get__NewEnum )( 
            IADsMembers __RPC_FAR * This,
            /* [retval][out] */ IUnknown __RPC_FAR *__RPC_FAR *ppEnumerator);
        
        /* [propget][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Filter )( 
            IADsMembers __RPC_FAR * This,
            /* [retval][out] */ VARIANT __RPC_FAR *pvFilter);
        
        /* [propput][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_Filter )( 
            IADsMembers __RPC_FAR * This,
            /* [in] */ VARIANT pvFilter);
        
        END_INTERFACE
    } IADsMembersVtbl;

    interface IADsMembers
    {
        CONST_VTBL struct IADsMembersVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IADsMembers_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IADsMembers_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IADsMembers_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IADsMembers_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define IADsMembers_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define IADsMembers_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define IADsMembers_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)


#define IADsMembers_get_Count(This,plCount)	\
    (This)->lpVtbl -> get_Count(This,plCount)

#define IADsMembers_get__NewEnum(This,ppEnumerator)	\
    (This)->lpVtbl -> get__NewEnum(This,ppEnumerator)

#define IADsMembers_get_Filter(This,pvFilter)	\
    (This)->lpVtbl -> get_Filter(This,pvFilter)

#define IADsMembers_put_Filter(This,pvFilter)	\
    (This)->lpVtbl -> put_Filter(This,pvFilter)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [propget][id] */ HRESULT STDMETHODCALLTYPE IADsMembers_get_Count_Proxy( 
    IADsMembers __RPC_FAR * This,
    /* [retval][out] */ long __RPC_FAR *plCount);


void __RPC_STUB IADsMembers_get_Count_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [propget][id] */ HRESULT STDMETHODCALLTYPE IADsMembers_get__NewEnum_Proxy( 
    IADsMembers __RPC_FAR * This,
    /* [retval][out] */ IUnknown __RPC_FAR *__RPC_FAR *ppEnumerator);


void __RPC_STUB IADsMembers_get__NewEnum_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [propget][id] */ HRESULT STDMETHODCALLTYPE IADsMembers_get_Filter_Proxy( 
    IADsMembers __RPC_FAR * This,
    /* [retval][out] */ VARIANT __RPC_FAR *pvFilter);


void __RPC_STUB IADsMembers_get_Filter_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [propput][id] */ HRESULT STDMETHODCALLTYPE IADsMembers_put_Filter_Proxy( 
    IADsMembers __RPC_FAR * This,
    /* [in] */ VARIANT pvFilter);


void __RPC_STUB IADsMembers_put_Filter_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IADsMembers_INTERFACE_DEFINED__ */


#ifndef __IADsPropertyList_INTERFACE_DEFINED__
#define __IADsPropertyList_INTERFACE_DEFINED__

/****************************************
 * Generated header for interface: IADsPropertyList
 * at Mon Oct 13 13:47:30 1997
 * using MIDL 3.00.44
 ****************************************/
/* [object][dual][oleautomation][uuid] */ 



EXTERN_C const IID IID_IADsPropertyList;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    interface IADsPropertyList : public IDispatch
    {
    public:
        virtual /* [propget][id] */ HRESULT STDMETHODCALLTYPE get_PropertyCount( 
            /* [retval][out] */ long __RPC_FAR *plCount) = 0;
        
        virtual /* [id] */ HRESULT STDMETHODCALLTYPE Next( 
            /* [retval][out] */ VARIANT __RPC_FAR *pVariant) = 0;
        
        virtual /* [id] */ HRESULT STDMETHODCALLTYPE Skip( 
            /* [in] */ ULONG cElements) = 0;
        
        virtual /* [id] */ HRESULT STDMETHODCALLTYPE Reset( void) = 0;
        
        virtual /* [id] */ HRESULT STDMETHODCALLTYPE Item( 
            /* [in] */ VARIANT varIndex,
            /* [retval][out] */ VARIANT __RPC_FAR *pVariant) = 0;
        
        virtual /* [id] */ HRESULT STDMETHODCALLTYPE GetPropertyItem( 
            /* [in] */ BSTR bstrName,
            /* [in] */ LONG lnADsType,
            /* [retval][out] */ VARIANT __RPC_FAR *pVariant) = 0;
        
        virtual /* [id] */ HRESULT STDMETHODCALLTYPE PutPropertyItem( 
            /* [in] */ VARIANT varData) = 0;
        
        virtual /* [id] */ HRESULT STDMETHODCALLTYPE ResetPropertyItem( 
            /* [in] */ VARIANT varEntry) = 0;
        
        virtual /* [id] */ HRESULT STDMETHODCALLTYPE PurgePropertyList( void) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IADsPropertyListVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            IADsPropertyList __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            IADsPropertyList __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            IADsPropertyList __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfoCount )( 
            IADsPropertyList __RPC_FAR * This,
            /* [out] */ UINT __RPC_FAR *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfo )( 
            IADsPropertyList __RPC_FAR * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo __RPC_FAR *__RPC_FAR *ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetIDsOfNames )( 
            IADsPropertyList __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR __RPC_FAR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID __RPC_FAR *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Invoke )( 
            IADsPropertyList __RPC_FAR * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS __RPC_FAR *pDispParams,
            /* [out] */ VARIANT __RPC_FAR *pVarResult,
            /* [out] */ EXCEPINFO __RPC_FAR *pExcepInfo,
            /* [out] */ UINT __RPC_FAR *puArgErr);
        
        /* [propget][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_PropertyCount )( 
            IADsPropertyList __RPC_FAR * This,
            /* [retval][out] */ long __RPC_FAR *plCount);
        
        /* [id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Next )( 
            IADsPropertyList __RPC_FAR * This,
            /* [retval][out] */ VARIANT __RPC_FAR *pVariant);
        
        /* [id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Skip )( 
            IADsPropertyList __RPC_FAR * This,
            /* [in] */ ULONG cElements);
        
        /* [id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Reset )( 
            IADsPropertyList __RPC_FAR * This);
        
        /* [id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Item )( 
            IADsPropertyList __RPC_FAR * This,
            /* [in] */ VARIANT varIndex,
            /* [retval][out] */ VARIANT __RPC_FAR *pVariant);
        
        /* [id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetPropertyItem )( 
            IADsPropertyList __RPC_FAR * This,
            /* [in] */ BSTR bstrName,
            /* [in] */ LONG lnADsType,
            /* [retval][out] */ VARIANT __RPC_FAR *pVariant);
        
        /* [id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *PutPropertyItem )( 
            IADsPropertyList __RPC_FAR * This,
            /* [in] */ VARIANT varData);
        
        /* [id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *ResetPropertyItem )( 
            IADsPropertyList __RPC_FAR * This,
            /* [in] */ VARIANT varEntry);
        
        /* [id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *PurgePropertyList )( 
            IADsPropertyList __RPC_FAR * This);
        
        END_INTERFACE
    } IADsPropertyListVtbl;

    interface IADsPropertyList
    {
        CONST_VTBL struct IADsPropertyListVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IADsPropertyList_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IADsPropertyList_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IADsPropertyList_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IADsPropertyList_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define IADsPropertyList_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define IADsPropertyList_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define IADsPropertyList_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)


#define IADsPropertyList_get_PropertyCount(This,plCount)	\
    (This)->lpVtbl -> get_PropertyCount(This,plCount)

#define IADsPropertyList_Next(This,pVariant)	\
    (This)->lpVtbl -> Next(This,pVariant)

#define IADsPropertyList_Skip(This,cElements)	\
    (This)->lpVtbl -> Skip(This,cElements)

#define IADsPropertyList_Reset(This)	\
    (This)->lpVtbl -> Reset(This)

#define IADsPropertyList_Item(This,varIndex,pVariant)	\
    (This)->lpVtbl -> Item(This,varIndex,pVariant)

#define IADsPropertyList_GetPropertyItem(This,bstrName,lnADsType,pVariant)	\
    (This)->lpVtbl -> GetPropertyItem(This,bstrName,lnADsType,pVariant)

#define IADsPropertyList_PutPropertyItem(This,varData)	\
    (This)->lpVtbl -> PutPropertyItem(This,varData)

#define IADsPropertyList_ResetPropertyItem(This,varEntry)	\
    (This)->lpVtbl -> ResetPropertyItem(This,varEntry)

#define IADsPropertyList_PurgePropertyList(This)	\
    (This)->lpVtbl -> PurgePropertyList(This)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [propget][id] */ HRESULT STDMETHODCALLTYPE IADsPropertyList_get_PropertyCount_Proxy( 
    IADsPropertyList __RPC_FAR * This,
    /* [retval][out] */ long __RPC_FAR *plCount);


void __RPC_STUB IADsPropertyList_get_PropertyCount_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [id] */ HRESULT STDMETHODCALLTYPE IADsPropertyList_Next_Proxy( 
    IADsPropertyList __RPC_FAR * This,
    /* [retval][out] */ VARIANT __RPC_FAR *pVariant);


void __RPC_STUB IADsPropertyList_Next_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [id] */ HRESULT STDMETHODCALLTYPE IADsPropertyList_Skip_Proxy( 
    IADsPropertyList __RPC_FAR * This,
    /* [in] */ ULONG cElements);


void __RPC_STUB IADsPropertyList_Skip_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [id] */ HRESULT STDMETHODCALLTYPE IADsPropertyList_Reset_Proxy( 
    IADsPropertyList __RPC_FAR * This);


void __RPC_STUB IADsPropertyList_Reset_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [id] */ HRESULT STDMETHODCALLTYPE IADsPropertyList_Item_Proxy( 
    IADsPropertyList __RPC_FAR * This,
    /* [in] */ VARIANT varIndex,
    /* [retval][out] */ VARIANT __RPC_FAR *pVariant);


void __RPC_STUB IADsPropertyList_Item_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [id] */ HRESULT STDMETHODCALLTYPE IADsPropertyList_GetPropertyItem_Proxy( 
    IADsPropertyList __RPC_FAR * This,
    /* [in] */ BSTR bstrName,
    /* [in] */ LONG lnADsType,
    /* [retval][out] */ VARIANT __RPC_FAR *pVariant);


void __RPC_STUB IADsPropertyList_GetPropertyItem_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [id] */ HRESULT STDMETHODCALLTYPE IADsPropertyList_PutPropertyItem_Proxy( 
    IADsPropertyList __RPC_FAR * This,
    /* [in] */ VARIANT varData);


void __RPC_STUB IADsPropertyList_PutPropertyItem_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [id] */ HRESULT STDMETHODCALLTYPE IADsPropertyList_ResetPropertyItem_Proxy( 
    IADsPropertyList __RPC_FAR * This,
    /* [in] */ VARIANT varEntry);


void __RPC_STUB IADsPropertyList_ResetPropertyItem_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [id] */ HRESULT STDMETHODCALLTYPE IADsPropertyList_PurgePropertyList_Proxy( 
    IADsPropertyList __RPC_FAR * This);


void __RPC_STUB IADsPropertyList_PurgePropertyList_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IADsPropertyList_INTERFACE_DEFINED__ */


#ifndef __IADsPropertyEntry_INTERFACE_DEFINED__
#define __IADsPropertyEntry_INTERFACE_DEFINED__

/****************************************
 * Generated header for interface: IADsPropertyEntry
 * at Mon Oct 13 13:47:30 1997
 * using MIDL 3.00.44
 ****************************************/
/* [object][dual][oleautomation][uuid] */ 



EXTERN_C const IID IID_IADsPropertyEntry;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    interface IADsPropertyEntry : public IDispatch
    {
    public:
        virtual /* [id] */ HRESULT STDMETHODCALLTYPE Clear( void) = 0;
        
        virtual /* [id][propget] */ HRESULT STDMETHODCALLTYPE get_Name( 
            /* [retval][out] */ BSTR __RPC_FAR *retval) = 0;
        
        virtual /* [id][propput] */ HRESULT STDMETHODCALLTYPE put_Name( 
            /* [in] */ BSTR bstrName) = 0;
        
        virtual /* [id][propget] */ HRESULT STDMETHODCALLTYPE get_ADsType( 
            /* [retval][out] */ long __RPC_FAR *retval) = 0;
        
        virtual /* [id][propput] */ HRESULT STDMETHODCALLTYPE put_ADsType( 
            /* [in] */ long lnADsType) = 0;
        
        virtual /* [id][propget] */ HRESULT STDMETHODCALLTYPE get_ControlCode( 
            /* [retval][out] */ long __RPC_FAR *retval) = 0;
        
        virtual /* [id][propput] */ HRESULT STDMETHODCALLTYPE put_ControlCode( 
            /* [in] */ long lnControlCode) = 0;
        
        virtual /* [id][propget] */ HRESULT STDMETHODCALLTYPE get_Values( 
            /* [retval][out] */ VARIANT __RPC_FAR *retval) = 0;
        
        virtual /* [id][propput] */ HRESULT STDMETHODCALLTYPE put_Values( 
            /* [in] */ VARIANT vValues) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IADsPropertyEntryVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            IADsPropertyEntry __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            IADsPropertyEntry __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            IADsPropertyEntry __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfoCount )( 
            IADsPropertyEntry __RPC_FAR * This,
            /* [out] */ UINT __RPC_FAR *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfo )( 
            IADsPropertyEntry __RPC_FAR * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo __RPC_FAR *__RPC_FAR *ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetIDsOfNames )( 
            IADsPropertyEntry __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR __RPC_FAR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID __RPC_FAR *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Invoke )( 
            IADsPropertyEntry __RPC_FAR * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS __RPC_FAR *pDispParams,
            /* [out] */ VARIANT __RPC_FAR *pVarResult,
            /* [out] */ EXCEPINFO __RPC_FAR *pExcepInfo,
            /* [out] */ UINT __RPC_FAR *puArgErr);
        
        /* [id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Clear )( 
            IADsPropertyEntry __RPC_FAR * This);
        
        /* [id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Name )( 
            IADsPropertyEntry __RPC_FAR * This,
            /* [retval][out] */ BSTR __RPC_FAR *retval);
        
        /* [id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_Name )( 
            IADsPropertyEntry __RPC_FAR * This,
            /* [in] */ BSTR bstrName);
        
        /* [id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_ADsType )( 
            IADsPropertyEntry __RPC_FAR * This,
            /* [retval][out] */ long __RPC_FAR *retval);
        
        /* [id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_ADsType )( 
            IADsPropertyEntry __RPC_FAR * This,
            /* [in] */ long lnADsType);
        
        /* [id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_ControlCode )( 
            IADsPropertyEntry __RPC_FAR * This,
            /* [retval][out] */ long __RPC_FAR *retval);
        
        /* [id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_ControlCode )( 
            IADsPropertyEntry __RPC_FAR * This,
            /* [in] */ long lnControlCode);
        
        /* [id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Values )( 
            IADsPropertyEntry __RPC_FAR * This,
            /* [retval][out] */ VARIANT __RPC_FAR *retval);
        
        /* [id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_Values )( 
            IADsPropertyEntry __RPC_FAR * This,
            /* [in] */ VARIANT vValues);
        
        END_INTERFACE
    } IADsPropertyEntryVtbl;

    interface IADsPropertyEntry
    {
        CONST_VTBL struct IADsPropertyEntryVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IADsPropertyEntry_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IADsPropertyEntry_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IADsPropertyEntry_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IADsPropertyEntry_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define IADsPropertyEntry_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define IADsPropertyEntry_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define IADsPropertyEntry_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)


#define IADsPropertyEntry_Clear(This)	\
    (This)->lpVtbl -> Clear(This)

#define IADsPropertyEntry_get_Name(This,retval)	\
    (This)->lpVtbl -> get_Name(This,retval)

#define IADsPropertyEntry_put_Name(This,bstrName)	\
    (This)->lpVtbl -> put_Name(This,bstrName)

#define IADsPropertyEntry_get_ADsType(This,retval)	\
    (This)->lpVtbl -> get_ADsType(This,retval)

#define IADsPropertyEntry_put_ADsType(This,lnADsType)	\
    (This)->lpVtbl -> put_ADsType(This,lnADsType)

#define IADsPropertyEntry_get_ControlCode(This,retval)	\
    (This)->lpVtbl -> get_ControlCode(This,retval)

#define IADsPropertyEntry_put_ControlCode(This,lnControlCode)	\
    (This)->lpVtbl -> put_ControlCode(This,lnControlCode)

#define IADsPropertyEntry_get_Values(This,retval)	\
    (This)->lpVtbl -> get_Values(This,retval)

#define IADsPropertyEntry_put_Values(This,vValues)	\
    (This)->lpVtbl -> put_Values(This,vValues)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [id] */ HRESULT STDMETHODCALLTYPE IADsPropertyEntry_Clear_Proxy( 
    IADsPropertyEntry __RPC_FAR * This);


void __RPC_STUB IADsPropertyEntry_Clear_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [id][propget] */ HRESULT STDMETHODCALLTYPE IADsPropertyEntry_get_Name_Proxy( 
    IADsPropertyEntry __RPC_FAR * This,
    /* [retval][out] */ BSTR __RPC_FAR *retval);


void __RPC_STUB IADsPropertyEntry_get_Name_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [id][propput] */ HRESULT STDMETHODCALLTYPE IADsPropertyEntry_put_Name_Proxy( 
    IADsPropertyEntry __RPC_FAR * This,
    /* [in] */ BSTR bstrName);


void __RPC_STUB IADsPropertyEntry_put_Name_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [id][propget] */ HRESULT STDMETHODCALLTYPE IADsPropertyEntry_get_ADsType_Proxy( 
    IADsPropertyEntry __RPC_FAR * This,
    /* [retval][out] */ long __RPC_FAR *retval);


void __RPC_STUB IADsPropertyEntry_get_ADsType_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [id][propput] */ HRESULT STDMETHODCALLTYPE IADsPropertyEntry_put_ADsType_Proxy( 
    IADsPropertyEntry __RPC_FAR * This,
    /* [in] */ long lnADsType);


void __RPC_STUB IADsPropertyEntry_put_ADsType_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [id][propget] */ HRESULT STDMETHODCALLTYPE IADsPropertyEntry_get_ControlCode_Proxy( 
    IADsPropertyEntry __RPC_FAR * This,
    /* [retval][out] */ long __RPC_FAR *retval);


void __RPC_STUB IADsPropertyEntry_get_ControlCode_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [id][propput] */ HRESULT STDMETHODCALLTYPE IADsPropertyEntry_put_ControlCode_Proxy( 
    IADsPropertyEntry __RPC_FAR * This,
    /* [in] */ long lnControlCode);


void __RPC_STUB IADsPropertyEntry_put_ControlCode_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [id][propget] */ HRESULT STDMETHODCALLTYPE IADsPropertyEntry_get_Values_Proxy( 
    IADsPropertyEntry __RPC_FAR * This,
    /* [retval][out] */ VARIANT __RPC_FAR *retval);


void __RPC_STUB IADsPropertyEntry_get_Values_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [id][propput] */ HRESULT STDMETHODCALLTYPE IADsPropertyEntry_put_Values_Proxy( 
    IADsPropertyEntry __RPC_FAR * This,
    /* [in] */ VARIANT vValues);


void __RPC_STUB IADsPropertyEntry_put_Values_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IADsPropertyEntry_INTERFACE_DEFINED__ */


#ifndef __IADsAttrInfo_INTERFACE_DEFINED__
#define __IADsAttrInfo_INTERFACE_DEFINED__

/****************************************
 * Generated header for interface: IADsAttrInfo
 * at Mon Oct 13 13:47:30 1997
 * using MIDL 3.00.44
 ****************************************/
/* [object][uuid] */ 



EXTERN_C const IID IID_IADsAttrInfo;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    interface IADsAttrInfo : public IUnknown
    {
    public:
        virtual HRESULT STDMETHODCALLTYPE ConvertAttrInfoToPropertyEntry( 
            PADS_ATTR_INFO pAttrInfo) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE ConvertPropertyEntryToAttrInfo( 
            PADS_ATTR_INFO __RPC_FAR *ppAttrInfo) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IADsAttrInfoVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            IADsAttrInfo __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            IADsAttrInfo __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            IADsAttrInfo __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *ConvertAttrInfoToPropertyEntry )( 
            IADsAttrInfo __RPC_FAR * This,
            PADS_ATTR_INFO pAttrInfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *ConvertPropertyEntryToAttrInfo )( 
            IADsAttrInfo __RPC_FAR * This,
            PADS_ATTR_INFO __RPC_FAR *ppAttrInfo);
        
        END_INTERFACE
    } IADsAttrInfoVtbl;

    interface IADsAttrInfo
    {
        CONST_VTBL struct IADsAttrInfoVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IADsAttrInfo_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IADsAttrInfo_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IADsAttrInfo_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IADsAttrInfo_ConvertAttrInfoToPropertyEntry(This,pAttrInfo)	\
    (This)->lpVtbl -> ConvertAttrInfoToPropertyEntry(This,pAttrInfo)

#define IADsAttrInfo_ConvertPropertyEntryToAttrInfo(This,ppAttrInfo)	\
    (This)->lpVtbl -> ConvertPropertyEntryToAttrInfo(This,ppAttrInfo)

#endif /* COBJMACROS */


#endif 	/* C style interface */



HRESULT STDMETHODCALLTYPE IADsAttrInfo_ConvertAttrInfoToPropertyEntry_Proxy( 
    IADsAttrInfo __RPC_FAR * This,
    PADS_ATTR_INFO pAttrInfo);


void __RPC_STUB IADsAttrInfo_ConvertAttrInfoToPropertyEntry_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IADsAttrInfo_ConvertPropertyEntryToAttrInfo_Proxy( 
    IADsAttrInfo __RPC_FAR * This,
    PADS_ATTR_INFO __RPC_FAR *ppAttrInfo);


void __RPC_STUB IADsAttrInfo_ConvertPropertyEntryToAttrInfo_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IADsAttrInfo_INTERFACE_DEFINED__ */


#ifdef __cplusplus
EXTERN_C const CLSID CLSID_PropertyEntry;

class PropertyEntry;
#endif

#ifndef __IADsPropertyValue_INTERFACE_DEFINED__
#define __IADsPropertyValue_INTERFACE_DEFINED__

/****************************************
 * Generated header for interface: IADsPropertyValue
 * at Mon Oct 13 13:47:30 1997
 * using MIDL 3.00.44
 ****************************************/
/* [object][dual][oleautomation][uuid] */ 



EXTERN_C const IID IID_IADsPropertyValue;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    interface IADsPropertyValue : public IDispatch
    {
    public:
        virtual /* [id] */ HRESULT STDMETHODCALLTYPE Clear( void) = 0;
        
        virtual /* [id][propget] */ HRESULT STDMETHODCALLTYPE get_ADsType( 
            /* [retval][out] */ long __RPC_FAR *retval) = 0;
        
        virtual /* [id][propput] */ HRESULT STDMETHODCALLTYPE put_ADsType( 
            /* [in] */ long lnADsType) = 0;
        
        virtual /* [id][propget] */ HRESULT STDMETHODCALLTYPE get_DNString( 
            /* [retval][out] */ BSTR __RPC_FAR *retval) = 0;
        
        virtual /* [id][propput] */ HRESULT STDMETHODCALLTYPE put_DNString( 
            /* [in] */ BSTR bstrDNString) = 0;
        
        virtual /* [id][propget] */ HRESULT STDMETHODCALLTYPE get_CaseExactString( 
            /* [retval][out] */ BSTR __RPC_FAR *retval) = 0;
        
        virtual /* [id][propput] */ HRESULT STDMETHODCALLTYPE put_CaseExactString( 
            /* [in] */ BSTR bstrCaseExactString) = 0;
        
        virtual /* [id][propget] */ HRESULT STDMETHODCALLTYPE get_CaseIgnoreString( 
            /* [retval][out] */ BSTR __RPC_FAR *retval) = 0;
        
        virtual /* [id][propput] */ HRESULT STDMETHODCALLTYPE put_CaseIgnoreString( 
            /* [in] */ BSTR bstrCaseIgnoreString) = 0;
        
        virtual /* [id][propget] */ HRESULT STDMETHODCALLTYPE get_PrintableString( 
            /* [retval][out] */ BSTR __RPC_FAR *retval) = 0;
        
        virtual /* [id][propput] */ HRESULT STDMETHODCALLTYPE put_PrintableString( 
            /* [in] */ BSTR bstrPrintableString) = 0;
        
        virtual /* [id][propget] */ HRESULT STDMETHODCALLTYPE get_NumericString( 
            /* [retval][out] */ BSTR __RPC_FAR *retval) = 0;
        
        virtual /* [id][propput] */ HRESULT STDMETHODCALLTYPE put_NumericString( 
            /* [in] */ BSTR bstrNumericString) = 0;
        
        virtual /* [id][propget] */ HRESULT STDMETHODCALLTYPE get_Boolean( 
            /* [retval][out] */ long __RPC_FAR *retval) = 0;
        
        virtual /* [id][propput] */ HRESULT STDMETHODCALLTYPE put_Boolean( 
            /* [in] */ long lnBoolean) = 0;
        
        virtual /* [id][propget] */ HRESULT STDMETHODCALLTYPE get_Integer( 
            /* [retval][out] */ long __RPC_FAR *retval) = 0;
        
        virtual /* [id][propput] */ HRESULT STDMETHODCALLTYPE put_Integer( 
            /* [in] */ long lnInteger) = 0;
        
        virtual /* [id][propget] */ HRESULT STDMETHODCALLTYPE get_OctetString( 
            /* [retval][out] */ VARIANT __RPC_FAR *retval) = 0;
        
        virtual /* [id][propput] */ HRESULT STDMETHODCALLTYPE put_OctetString( 
            /* [in] */ VARIANT vOctetString) = 0;
        
        virtual /* [id][propget] */ HRESULT STDMETHODCALLTYPE get_SecurityDescriptor( 
            /* [retval][out] */ IDispatch __RPC_FAR *__RPC_FAR *retval) = 0;
        
        virtual /* [id][propput] */ HRESULT STDMETHODCALLTYPE put_SecurityDescriptor( 
            /* [in] */ IDispatch __RPC_FAR *pSecurityDescriptor) = 0;
        
        virtual /* [id][propget] */ HRESULT STDMETHODCALLTYPE get_LargeInteger( 
            /* [retval][out] */ IDispatch __RPC_FAR *__RPC_FAR *retval) = 0;
        
        virtual /* [id][propput] */ HRESULT STDMETHODCALLTYPE put_LargeInteger( 
            /* [in] */ IDispatch __RPC_FAR *pLargeInteger) = 0;
        
        virtual /* [id][propget] */ HRESULT STDMETHODCALLTYPE get_UTCTime( 
            /* [retval][out] */ DATE __RPC_FAR *retval) = 0;
        
        virtual /* [id][propput] */ HRESULT STDMETHODCALLTYPE put_UTCTime( 
            /* [in] */ DATE daUTCTime) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IADsPropertyValueVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            IADsPropertyValue __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            IADsPropertyValue __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            IADsPropertyValue __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfoCount )( 
            IADsPropertyValue __RPC_FAR * This,
            /* [out] */ UINT __RPC_FAR *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfo )( 
            IADsPropertyValue __RPC_FAR * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo __RPC_FAR *__RPC_FAR *ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetIDsOfNames )( 
            IADsPropertyValue __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR __RPC_FAR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID __RPC_FAR *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Invoke )( 
            IADsPropertyValue __RPC_FAR * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS __RPC_FAR *pDispParams,
            /* [out] */ VARIANT __RPC_FAR *pVarResult,
            /* [out] */ EXCEPINFO __RPC_FAR *pExcepInfo,
            /* [out] */ UINT __RPC_FAR *puArgErr);
        
        /* [id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Clear )( 
            IADsPropertyValue __RPC_FAR * This);
        
        /* [id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_ADsType )( 
            IADsPropertyValue __RPC_FAR * This,
            /* [retval][out] */ long __RPC_FAR *retval);
        
        /* [id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_ADsType )( 
            IADsPropertyValue __RPC_FAR * This,
            /* [in] */ long lnADsType);
        
        /* [id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_DNString )( 
            IADsPropertyValue __RPC_FAR * This,
            /* [retval][out] */ BSTR __RPC_FAR *retval);
        
        /* [id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_DNString )( 
            IADsPropertyValue __RPC_FAR * This,
            /* [in] */ BSTR bstrDNString);
        
        /* [id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_CaseExactString )( 
            IADsPropertyValue __RPC_FAR * This,
            /* [retval][out] */ BSTR __RPC_FAR *retval);
        
        /* [id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_CaseExactString )( 
            IADsPropertyValue __RPC_FAR * This,
            /* [in] */ BSTR bstrCaseExactString);
        
        /* [id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_CaseIgnoreString )( 
            IADsPropertyValue __RPC_FAR * This,
            /* [retval][out] */ BSTR __RPC_FAR *retval);
        
        /* [id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_CaseIgnoreString )( 
            IADsPropertyValue __RPC_FAR * This,
            /* [in] */ BSTR bstrCaseIgnoreString);
        
        /* [id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_PrintableString )( 
            IADsPropertyValue __RPC_FAR * This,
            /* [retval][out] */ BSTR __RPC_FAR *retval);
        
        /* [id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_PrintableString )( 
            IADsPropertyValue __RPC_FAR * This,
            /* [in] */ BSTR bstrPrintableString);
        
        /* [id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_NumericString )( 
            IADsPropertyValue __RPC_FAR * This,
            /* [retval][out] */ BSTR __RPC_FAR *retval);
        
        /* [id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_NumericString )( 
            IADsPropertyValue __RPC_FAR * This,
            /* [in] */ BSTR bstrNumericString);
        
        /* [id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Boolean )( 
            IADsPropertyValue __RPC_FAR * This,
            /* [retval][out] */ long __RPC_FAR *retval);
        
        /* [id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_Boolean )( 
            IADsPropertyValue __RPC_FAR * This,
            /* [in] */ long lnBoolean);
        
        /* [id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Integer )( 
            IADsPropertyValue __RPC_FAR * This,
            /* [retval][out] */ long __RPC_FAR *retval);
        
        /* [id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_Integer )( 
            IADsPropertyValue __RPC_FAR * This,
            /* [in] */ long lnInteger);
        
        /* [id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_OctetString )( 
            IADsPropertyValue __RPC_FAR * This,
            /* [retval][out] */ VARIANT __RPC_FAR *retval);
        
        /* [id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_OctetString )( 
            IADsPropertyValue __RPC_FAR * This,
            /* [in] */ VARIANT vOctetString);
        
        /* [id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_SecurityDescriptor )( 
            IADsPropertyValue __RPC_FAR * This,
            /* [retval][out] */ IDispatch __RPC_FAR *__RPC_FAR *retval);
        
        /* [id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_SecurityDescriptor )( 
            IADsPropertyValue __RPC_FAR * This,
            /* [in] */ IDispatch __RPC_FAR *pSecurityDescriptor);
        
        /* [id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_LargeInteger )( 
            IADsPropertyValue __RPC_FAR * This,
            /* [retval][out] */ IDispatch __RPC_FAR *__RPC_FAR *retval);
        
        /* [id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_LargeInteger )( 
            IADsPropertyValue __RPC_FAR * This,
            /* [in] */ IDispatch __RPC_FAR *pLargeInteger);
        
        /* [id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_UTCTime )( 
            IADsPropertyValue __RPC_FAR * This,
            /* [retval][out] */ DATE __RPC_FAR *retval);
        
        /* [id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_UTCTime )( 
            IADsPropertyValue __RPC_FAR * This,
            /* [in] */ DATE daUTCTime);
        
        END_INTERFACE
    } IADsPropertyValueVtbl;

    interface IADsPropertyValue
    {
        CONST_VTBL struct IADsPropertyValueVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IADsPropertyValue_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IADsPropertyValue_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IADsPropertyValue_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IADsPropertyValue_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define IADsPropertyValue_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define IADsPropertyValue_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define IADsPropertyValue_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)


#define IADsPropertyValue_Clear(This)	\
    (This)->lpVtbl -> Clear(This)

#define IADsPropertyValue_get_ADsType(This,retval)	\
    (This)->lpVtbl -> get_ADsType(This,retval)

#define IADsPropertyValue_put_ADsType(This,lnADsType)	\
    (This)->lpVtbl -> put_ADsType(This,lnADsType)

#define IADsPropertyValue_get_DNString(This,retval)	\
    (This)->lpVtbl -> get_DNString(This,retval)

#define IADsPropertyValue_put_DNString(This,bstrDNString)	\
    (This)->lpVtbl -> put_DNString(This,bstrDNString)

#define IADsPropertyValue_get_CaseExactString(This,retval)	\
    (This)->lpVtbl -> get_CaseExactString(This,retval)

#define IADsPropertyValue_put_CaseExactString(This,bstrCaseExactString)	\
    (This)->lpVtbl -> put_CaseExactString(This,bstrCaseExactString)

#define IADsPropertyValue_get_CaseIgnoreString(This,retval)	\
    (This)->lpVtbl -> get_CaseIgnoreString(This,retval)

#define IADsPropertyValue_put_CaseIgnoreString(This,bstrCaseIgnoreString)	\
    (This)->lpVtbl -> put_CaseIgnoreString(This,bstrCaseIgnoreString)

#define IADsPropertyValue_get_PrintableString(This,retval)	\
    (This)->lpVtbl -> get_PrintableString(This,retval)

#define IADsPropertyValue_put_PrintableString(This,bstrPrintableString)	\
    (This)->lpVtbl -> put_PrintableString(This,bstrPrintableString)

#define IADsPropertyValue_get_NumericString(This,retval)	\
    (This)->lpVtbl -> get_NumericString(This,retval)

#define IADsPropertyValue_put_NumericString(This,bstrNumericString)	\
    (This)->lpVtbl -> put_NumericString(This,bstrNumericString)

#define IADsPropertyValue_get_Boolean(This,retval)	\
    (This)->lpVtbl -> get_Boolean(This,retval)

#define IADsPropertyValue_put_Boolean(This,lnBoolean)	\
    (This)->lpVtbl -> put_Boolean(This,lnBoolean)

#define IADsPropertyValue_get_Integer(This,retval)	\
    (This)->lpVtbl -> get_Integer(This,retval)

#define IADsPropertyValue_put_Integer(This,lnInteger)	\
    (This)->lpVtbl -> put_Integer(This,lnInteger)

#define IADsPropertyValue_get_OctetString(This,retval)	\
    (This)->lpVtbl -> get_OctetString(This,retval)

#define IADsPropertyValue_put_OctetString(This,vOctetString)	\
    (This)->lpVtbl -> put_OctetString(This,vOctetString)

#define IADsPropertyValue_get_SecurityDescriptor(This,retval)	\
    (This)->lpVtbl -> get_SecurityDescriptor(This,retval)

#define IADsPropertyValue_put_SecurityDescriptor(This,pSecurityDescriptor)	\
    (This)->lpVtbl -> put_SecurityDescriptor(This,pSecurityDescriptor)

#define IADsPropertyValue_get_LargeInteger(This,retval)	\
    (This)->lpVtbl -> get_LargeInteger(This,retval)

#define IADsPropertyValue_put_LargeInteger(This,pLargeInteger)	\
    (This)->lpVtbl -> put_LargeInteger(This,pLargeInteger)

#define IADsPropertyValue_get_UTCTime(This,retval)	\
    (This)->lpVtbl -> get_UTCTime(This,retval)

#define IADsPropertyValue_put_UTCTime(This,daUTCTime)	\
    (This)->lpVtbl -> put_UTCTime(This,daUTCTime)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [id] */ HRESULT STDMETHODCALLTYPE IADsPropertyValue_Clear_Proxy( 
    IADsPropertyValue __RPC_FAR * This);


void __RPC_STUB IADsPropertyValue_Clear_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [id][propget] */ HRESULT STDMETHODCALLTYPE IADsPropertyValue_get_ADsType_Proxy( 
    IADsPropertyValue __RPC_FAR * This,
    /* [retval][out] */ long __RPC_FAR *retval);


void __RPC_STUB IADsPropertyValue_get_ADsType_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [id][propput] */ HRESULT STDMETHODCALLTYPE IADsPropertyValue_put_ADsType_Proxy( 
    IADsPropertyValue __RPC_FAR * This,
    /* [in] */ long lnADsType);


void __RPC_STUB IADsPropertyValue_put_ADsType_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [id][propget] */ HRESULT STDMETHODCALLTYPE IADsPropertyValue_get_DNString_Proxy( 
    IADsPropertyValue __RPC_FAR * This,
    /* [retval][out] */ BSTR __RPC_FAR *retval);


void __RPC_STUB IADsPropertyValue_get_DNString_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [id][propput] */ HRESULT STDMETHODCALLTYPE IADsPropertyValue_put_DNString_Proxy( 
    IADsPropertyValue __RPC_FAR * This,
    /* [in] */ BSTR bstrDNString);


void __RPC_STUB IADsPropertyValue_put_DNString_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [id][propget] */ HRESULT STDMETHODCALLTYPE IADsPropertyValue_get_CaseExactString_Proxy( 
    IADsPropertyValue __RPC_FAR * This,
    /* [retval][out] */ BSTR __RPC_FAR *retval);


void __RPC_STUB IADsPropertyValue_get_CaseExactString_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [id][propput] */ HRESULT STDMETHODCALLTYPE IADsPropertyValue_put_CaseExactString_Proxy( 
    IADsPropertyValue __RPC_FAR * This,
    /* [in] */ BSTR bstrCaseExactString);


void __RPC_STUB IADsPropertyValue_put_CaseExactString_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [id][propget] */ HRESULT STDMETHODCALLTYPE IADsPropertyValue_get_CaseIgnoreString_Proxy( 
    IADsPropertyValue __RPC_FAR * This,
    /* [retval][out] */ BSTR __RPC_FAR *retval);


void __RPC_STUB IADsPropertyValue_get_CaseIgnoreString_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [id][propput] */ HRESULT STDMETHODCALLTYPE IADsPropertyValue_put_CaseIgnoreString_Proxy( 
    IADsPropertyValue __RPC_FAR * This,
    /* [in] */ BSTR bstrCaseIgnoreString);


void __RPC_STUB IADsPropertyValue_put_CaseIgnoreString_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [id][propget] */ HRESULT STDMETHODCALLTYPE IADsPropertyValue_get_PrintableString_Proxy( 
    IADsPropertyValue __RPC_FAR * This,
    /* [retval][out] */ BSTR __RPC_FAR *retval);


void __RPC_STUB IADsPropertyValue_get_PrintableString_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [id][propput] */ HRESULT STDMETHODCALLTYPE IADsPropertyValue_put_PrintableString_Proxy( 
    IADsPropertyValue __RPC_FAR * This,
    /* [in] */ BSTR bstrPrintableString);


void __RPC_STUB IADsPropertyValue_put_PrintableString_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [id][propget] */ HRESULT STDMETHODCALLTYPE IADsPropertyValue_get_NumericString_Proxy( 
    IADsPropertyValue __RPC_FAR * This,
    /* [retval][out] */ BSTR __RPC_FAR *retval);


void __RPC_STUB IADsPropertyValue_get_NumericString_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [id][propput] */ HRESULT STDMETHODCALLTYPE IADsPropertyValue_put_NumericString_Proxy( 
    IADsPropertyValue __RPC_FAR * This,
    /* [in] */ BSTR bstrNumericString);


void __RPC_STUB IADsPropertyValue_put_NumericString_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [id][propget] */ HRESULT STDMETHODCALLTYPE IADsPropertyValue_get_Boolean_Proxy( 
    IADsPropertyValue __RPC_FAR * This,
    /* [retval][out] */ long __RPC_FAR *retval);


void __RPC_STUB IADsPropertyValue_get_Boolean_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [id][propput] */ HRESULT STDMETHODCALLTYPE IADsPropertyValue_put_Boolean_Proxy( 
    IADsPropertyValue __RPC_FAR * This,
    /* [in] */ long lnBoolean);


void __RPC_STUB IADsPropertyValue_put_Boolean_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [id][propget] */ HRESULT STDMETHODCALLTYPE IADsPropertyValue_get_Integer_Proxy( 
    IADsPropertyValue __RPC_FAR * This,
    /* [retval][out] */ long __RPC_FAR *retval);


void __RPC_STUB IADsPropertyValue_get_Integer_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [id][propput] */ HRESULT STDMETHODCALLTYPE IADsPropertyValue_put_Integer_Proxy( 
    IADsPropertyValue __RPC_FAR * This,
    /* [in] */ long lnInteger);


void __RPC_STUB IADsPropertyValue_put_Integer_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [id][propget] */ HRESULT STDMETHODCALLTYPE IADsPropertyValue_get_OctetString_Proxy( 
    IADsPropertyValue __RPC_FAR * This,
    /* [retval][out] */ VARIANT __RPC_FAR *retval);


void __RPC_STUB IADsPropertyValue_get_OctetString_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [id][propput] */ HRESULT STDMETHODCALLTYPE IADsPropertyValue_put_OctetString_Proxy( 
    IADsPropertyValue __RPC_FAR * This,
    /* [in] */ VARIANT vOctetString);


void __RPC_STUB IADsPropertyValue_put_OctetString_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [id][propget] */ HRESULT STDMETHODCALLTYPE IADsPropertyValue_get_SecurityDescriptor_Proxy( 
    IADsPropertyValue __RPC_FAR * This,
    /* [retval][out] */ IDispatch __RPC_FAR *__RPC_FAR *retval);


void __RPC_STUB IADsPropertyValue_get_SecurityDescriptor_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [id][propput] */ HRESULT STDMETHODCALLTYPE IADsPropertyValue_put_SecurityDescriptor_Proxy( 
    IADsPropertyValue __RPC_FAR * This,
    /* [in] */ IDispatch __RPC_FAR *pSecurityDescriptor);


void __RPC_STUB IADsPropertyValue_put_SecurityDescriptor_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [id][propget] */ HRESULT STDMETHODCALLTYPE IADsPropertyValue_get_LargeInteger_Proxy( 
    IADsPropertyValue __RPC_FAR * This,
    /* [retval][out] */ IDispatch __RPC_FAR *__RPC_FAR *retval);


void __RPC_STUB IADsPropertyValue_get_LargeInteger_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [id][propput] */ HRESULT STDMETHODCALLTYPE IADsPropertyValue_put_LargeInteger_Proxy( 
    IADsPropertyValue __RPC_FAR * This,
    /* [in] */ IDispatch __RPC_FAR *pLargeInteger);


void __RPC_STUB IADsPropertyValue_put_LargeInteger_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [id][propget] */ HRESULT STDMETHODCALLTYPE IADsPropertyValue_get_UTCTime_Proxy( 
    IADsPropertyValue __RPC_FAR * This,
    /* [retval][out] */ DATE __RPC_FAR *retval);


void __RPC_STUB IADsPropertyValue_get_UTCTime_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [id][propput] */ HRESULT STDMETHODCALLTYPE IADsPropertyValue_put_UTCTime_Proxy( 
    IADsPropertyValue __RPC_FAR * This,
    /* [in] */ DATE daUTCTime);


void __RPC_STUB IADsPropertyValue_put_UTCTime_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IADsPropertyValue_INTERFACE_DEFINED__ */


#ifndef __IADsValue_INTERFACE_DEFINED__
#define __IADsValue_INTERFACE_DEFINED__

/****************************************
 * Generated header for interface: IADsValue
 * at Mon Oct 13 13:47:30 1997
 * using MIDL 3.00.44
 ****************************************/
/* [object][uuid] */ 



EXTERN_C const IID IID_IADsValue;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    interface IADsValue : public IUnknown
    {
    public:
        virtual HRESULT STDMETHODCALLTYPE ConvertADsValueToPropertyValue( 
            PADSVALUE pADsValue) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE ConvertPropertyValueToADsValue( 
            PADSVALUE pADsValue) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IADsValueVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            IADsValue __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            IADsValue __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            IADsValue __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *ConvertADsValueToPropertyValue )( 
            IADsValue __RPC_FAR * This,
            PADSVALUE pADsValue);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *ConvertPropertyValueToADsValue )( 
            IADsValue __RPC_FAR * This,
            PADSVALUE pADsValue);
        
        END_INTERFACE
    } IADsValueVtbl;

    interface IADsValue
    {
        CONST_VTBL struct IADsValueVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IADsValue_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IADsValue_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IADsValue_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IADsValue_ConvertADsValueToPropertyValue(This,pADsValue)	\
    (This)->lpVtbl -> ConvertADsValueToPropertyValue(This,pADsValue)

#define IADsValue_ConvertPropertyValueToADsValue(This,pADsValue)	\
    (This)->lpVtbl -> ConvertPropertyValueToADsValue(This,pADsValue)

#endif /* COBJMACROS */


#endif 	/* C style interface */



HRESULT STDMETHODCALLTYPE IADsValue_ConvertADsValueToPropertyValue_Proxy( 
    IADsValue __RPC_FAR * This,
    PADSVALUE pADsValue);


void __RPC_STUB IADsValue_ConvertADsValueToPropertyValue_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IADsValue_ConvertPropertyValueToADsValue_Proxy( 
    IADsValue __RPC_FAR * This,
    PADSVALUE pADsValue);


void __RPC_STUB IADsValue_ConvertPropertyValueToADsValue_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IADsValue_INTERFACE_DEFINED__ */


#ifdef __cplusplus
EXTERN_C const CLSID CLSID_PropertyValue;

class PropertyValue;
#endif

#ifndef __IADsNamespaces_INTERFACE_DEFINED__
#define __IADsNamespaces_INTERFACE_DEFINED__

/****************************************
 * Generated header for interface: IADsNamespaces
 * at Mon Oct 13 13:47:30 1997
 * using MIDL 3.00.44
 ****************************************/
/* [object][oleautomation][dual][uuid] */ 



EXTERN_C const IID IID_IADsNamespaces;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    interface IADsNamespaces : public IADs
    {
    public:
        virtual /* [id][propget] */ HRESULT STDMETHODCALLTYPE get_DefaultContainer( 
            /* [retval][out] */ BSTR __RPC_FAR *retval) = 0;
        
        virtual /* [id][propput] */ HRESULT STDMETHODCALLTYPE put_DefaultContainer( 
            /* [in] */ BSTR bstrDefaultContainer) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IADsNamespacesVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            IADsNamespaces __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            IADsNamespaces __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            IADsNamespaces __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfoCount )( 
            IADsNamespaces __RPC_FAR * This,
            /* [out] */ UINT __RPC_FAR *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfo )( 
            IADsNamespaces __RPC_FAR * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo __RPC_FAR *__RPC_FAR *ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetIDsOfNames )( 
            IADsNamespaces __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR __RPC_FAR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID __RPC_FAR *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Invoke )( 
            IADsNamespaces __RPC_FAR * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS __RPC_FAR *pDispParams,
            /* [out] */ VARIANT __RPC_FAR *pVarResult,
            /* [out] */ EXCEPINFO __RPC_FAR *pExcepInfo,
            /* [out] */ UINT __RPC_FAR *puArgErr);
        
        /* [id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Name )( 
            IADsNamespaces __RPC_FAR * This,
            /* [retval][out] */ BSTR __RPC_FAR *retval);
        
        /* [id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Class )( 
            IADsNamespaces __RPC_FAR * This,
            /* [retval][out] */ BSTR __RPC_FAR *retval);
        
        /* [id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_GUID )( 
            IADsNamespaces __RPC_FAR * This,
            /* [retval][out] */ BSTR __RPC_FAR *retval);
        
        /* [id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_ADsPath )( 
            IADsNamespaces __RPC_FAR * This,
            /* [retval][out] */ BSTR __RPC_FAR *retval);
        
        /* [id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Parent )( 
            IADsNamespaces __RPC_FAR * This,
            /* [retval][out] */ BSTR __RPC_FAR *retval);
        
        /* [id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Schema )( 
            IADsNamespaces __RPC_FAR * This,
            /* [retval][out] */ BSTR __RPC_FAR *retval);
        
        /* [id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetInfo )( 
            IADsNamespaces __RPC_FAR * This);
        
        /* [id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *SetInfo )( 
            IADsNamespaces __RPC_FAR * This);
        
        /* [id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Get )( 
            IADsNamespaces __RPC_FAR * This,
            /* [in] */ BSTR bstrName,
            /* [retval][out] */ VARIANT __RPC_FAR *pvProp);
        
        /* [id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Put )( 
            IADsNamespaces __RPC_FAR * This,
            /* [in] */ BSTR bstrName,
            /* [in] */ VARIANT vProp);
        
        /* [id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetEx )( 
            IADsNamespaces __RPC_FAR * This,
            /* [in] */ BSTR bstrName,
            /* [retval][out] */ VARIANT __RPC_FAR *pvProp);
        
        /* [id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *PutEx )( 
            IADsNamespaces __RPC_FAR * This,
            /* [in] */ long lnControlCode,
            /* [in] */ BSTR bstrName,
            /* [in] */ VARIANT vProp);
        
        /* [id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetInfoEx )( 
            IADsNamespaces __RPC_FAR * This,
            /* [in] */ VARIANT vProperties,
            /* [in] */ long lnReserved);
        
        /* [id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_DefaultContainer )( 
            IADsNamespaces __RPC_FAR * This,
            /* [retval][out] */ BSTR __RPC_FAR *retval);
        
        /* [id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_DefaultContainer )( 
            IADsNamespaces __RPC_FAR * This,
            /* [in] */ BSTR bstrDefaultContainer);
        
        END_INTERFACE
    } IADsNamespacesVtbl;

    interface IADsNamespaces
    {
        CONST_VTBL struct IADsNamespacesVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IADsNamespaces_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IADsNamespaces_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IADsNamespaces_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IADsNamespaces_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define IADsNamespaces_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define IADsNamespaces_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define IADsNamespaces_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)


#define IADsNamespaces_get_Name(This,retval)	\
    (This)->lpVtbl -> get_Name(This,retval)

#define IADsNamespaces_get_Class(This,retval)	\
    (This)->lpVtbl -> get_Class(This,retval)

#define IADsNamespaces_get_GUID(This,retval)	\
    (This)->lpVtbl -> get_GUID(This,retval)

#define IADsNamespaces_get_ADsPath(This,retval)	\
    (This)->lpVtbl -> get_ADsPath(This,retval)

#define IADsNamespaces_get_Parent(This,retval)	\
    (This)->lpVtbl -> get_Parent(This,retval)

#define IADsNamespaces_get_Schema(This,retval)	\
    (This)->lpVtbl -> get_Schema(This,retval)

#define IADsNamespaces_GetInfo(This)	\
    (This)->lpVtbl -> GetInfo(This)

#define IADsNamespaces_SetInfo(This)	\
    (This)->lpVtbl -> SetInfo(This)

#define IADsNamespaces_Get(This,bstrName,pvProp)	\
    (This)->lpVtbl -> Get(This,bstrName,pvProp)

#define IADsNamespaces_Put(This,bstrName,vProp)	\
    (This)->lpVtbl -> Put(This,bstrName,vProp)

#define IADsNamespaces_GetEx(This,bstrName,pvProp)	\
    (This)->lpVtbl -> GetEx(This,bstrName,pvProp)

#define IADsNamespaces_PutEx(This,lnControlCode,bstrName,vProp)	\
    (This)->lpVtbl -> PutEx(This,lnControlCode,bstrName,vProp)

#define IADsNamespaces_GetInfoEx(This,vProperties,lnReserved)	\
    (This)->lpVtbl -> GetInfoEx(This,vProperties,lnReserved)


#define IADsNamespaces_get_DefaultContainer(This,retval)	\
    (This)->lpVtbl -> get_DefaultContainer(This,retval)

#define IADsNamespaces_put_DefaultContainer(This,bstrDefaultContainer)	\
    (This)->lpVtbl -> put_DefaultContainer(This,bstrDefaultContainer)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [id][propget] */ HRESULT STDMETHODCALLTYPE IADsNamespaces_get_DefaultContainer_Proxy( 
    IADsNamespaces __RPC_FAR * This,
    /* [retval][out] */ BSTR __RPC_FAR *retval);


void __RPC_STUB IADsNamespaces_get_DefaultContainer_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [id][propput] */ HRESULT STDMETHODCALLTYPE IADsNamespaces_put_DefaultContainer_Proxy( 
    IADsNamespaces __RPC_FAR * This,
    /* [in] */ BSTR bstrDefaultContainer);


void __RPC_STUB IADsNamespaces_put_DefaultContainer_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IADsNamespaces_INTERFACE_DEFINED__ */


#ifndef __IADsClass_INTERFACE_DEFINED__
#define __IADsClass_INTERFACE_DEFINED__

/****************************************
 * Generated header for interface: IADsClass
 * at Mon Oct 13 13:47:30 1997
 * using MIDL 3.00.44
 ****************************************/
/* [object][dual][oleautomation][uuid] */ 



EXTERN_C const IID IID_IADsClass;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    interface IADsClass : public IADs
    {
    public:
        virtual /* [id][propget] */ HRESULT STDMETHODCALLTYPE get_PrimaryInterface( 
            /* [retval][out] */ BSTR __RPC_FAR *retval) = 0;
        
        virtual /* [id][propget] */ HRESULT STDMETHODCALLTYPE get_CLSID( 
            /* [retval][out] */ BSTR __RPC_FAR *retval) = 0;
        
        virtual /* [id][propput] */ HRESULT STDMETHODCALLTYPE put_CLSID( 
            /* [in] */ BSTR bstrCLSID) = 0;
        
        virtual /* [id][propget] */ HRESULT STDMETHODCALLTYPE get_OID( 
            /* [retval][out] */ BSTR __RPC_FAR *retval) = 0;
        
        virtual /* [id][propput] */ HRESULT STDMETHODCALLTYPE put_OID( 
            /* [in] */ BSTR bstrOID) = 0;
        
        virtual /* [id][propget] */ HRESULT STDMETHODCALLTYPE get_Abstract( 
            /* [retval][out] */ VARIANT_BOOL __RPC_FAR *retval) = 0;
        
        virtual /* [id][propput] */ HRESULT STDMETHODCALLTYPE put_Abstract( 
            /* [in] */ VARIANT_BOOL fAbstract) = 0;
        
        virtual /* [id][propget] */ HRESULT STDMETHODCALLTYPE get_Auxiliary( 
            /* [retval][out] */ VARIANT_BOOL __RPC_FAR *retval) = 0;
        
        virtual /* [id][propput] */ HRESULT STDMETHODCALLTYPE put_Auxiliary( 
            /* [in] */ VARIANT_BOOL fAuxiliary) = 0;
        
        virtual /* [id][propget] */ HRESULT STDMETHODCALLTYPE get_MandatoryProperties( 
            /* [retval][out] */ VARIANT __RPC_FAR *retval) = 0;
        
        virtual /* [id][propput] */ HRESULT STDMETHODCALLTYPE put_MandatoryProperties( 
            /* [in] */ VARIANT vMandatoryProperties) = 0;
        
        virtual /* [id][propget] */ HRESULT STDMETHODCALLTYPE get_OptionalProperties( 
            /* [retval][out] */ VARIANT __RPC_FAR *retval) = 0;
        
        virtual /* [id][propput] */ HRESULT STDMETHODCALLTYPE put_OptionalProperties( 
            /* [in] */ VARIANT vOptionalProperties) = 0;
        
        virtual /* [id][propget] */ HRESULT STDMETHODCALLTYPE get_NamingProperties( 
            /* [retval][out] */ VARIANT __RPC_FAR *retval) = 0;
        
        virtual /* [id][propput] */ HRESULT STDMETHODCALLTYPE put_NamingProperties( 
            /* [in] */ VARIANT vNamingProperties) = 0;
        
        virtual /* [id][propget] */ HRESULT STDMETHODCALLTYPE get_DerivedFrom( 
            /* [retval][out] */ VARIANT __RPC_FAR *retval) = 0;
        
        virtual /* [id][propput] */ HRESULT STDMETHODCALLTYPE put_DerivedFrom( 
            /* [in] */ VARIANT vDerivedFrom) = 0;
        
        virtual /* [id][propget] */ HRESULT STDMETHODCALLTYPE get_AuxDerivedFrom( 
            /* [retval][out] */ VARIANT __RPC_FAR *retval) = 0;
        
        virtual /* [id][propput] */ HRESULT STDMETHODCALLTYPE put_AuxDerivedFrom( 
            /* [in] */ VARIANT vAuxDerivedFrom) = 0;
        
        virtual /* [id][propget] */ HRESULT STDMETHODCALLTYPE get_PossibleSuperiors( 
            /* [retval][out] */ VARIANT __RPC_FAR *retval) = 0;
        
        virtual /* [id][propput] */ HRESULT STDMETHODCALLTYPE put_PossibleSuperiors( 
            /* [in] */ VARIANT vPossibleSuperiors) = 0;
        
        virtual /* [id][propget] */ HRESULT STDMETHODCALLTYPE get_Containment( 
            /* [retval][out] */ VARIANT __RPC_FAR *retval) = 0;
        
        virtual /* [id][propput] */ HRESULT STDMETHODCALLTYPE put_Containment( 
            /* [in] */ VARIANT vContainment) = 0;
        
        virtual /* [id][propget] */ HRESULT STDMETHODCALLTYPE get_Container( 
            /* [retval][out] */ VARIANT_BOOL __RPC_FAR *retval) = 0;
        
        virtual /* [id][propput] */ HRESULT STDMETHODCALLTYPE put_Container( 
            /* [in] */ VARIANT_BOOL fContainer) = 0;
        
        virtual /* [id][propget] */ HRESULT STDMETHODCALLTYPE get_HelpFileName( 
            /* [retval][out] */ BSTR __RPC_FAR *retval) = 0;
        
        virtual /* [id][propput] */ HRESULT STDMETHODCALLTYPE put_HelpFileName( 
            /* [in] */ BSTR bstrHelpFileName) = 0;
        
        virtual /* [id][propget] */ HRESULT STDMETHODCALLTYPE get_HelpFileContext( 
            /* [retval][out] */ long __RPC_FAR *retval) = 0;
        
        virtual /* [id][propput] */ HRESULT STDMETHODCALLTYPE put_HelpFileContext( 
            /* [in] */ long lnHelpFileContext) = 0;
        
        virtual /* [id] */ HRESULT STDMETHODCALLTYPE Qualifiers( 
            /* [retval][out] */ IADsCollection __RPC_FAR *__RPC_FAR *ppQualifiers) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IADsClassVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            IADsClass __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            IADsClass __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            IADsClass __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfoCount )( 
            IADsClass __RPC_FAR * This,
            /* [out] */ UINT __RPC_FAR *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfo )( 
            IADsClass __RPC_FAR * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo __RPC_FAR *__RPC_FAR *ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetIDsOfNames )( 
            IADsClass __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR __RPC_FAR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID __RPC_FAR *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Invoke )( 
            IADsClass __RPC_FAR * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS __RPC_FAR *pDispParams,
            /* [out] */ VARIANT __RPC_FAR *pVarResult,
            /* [out] */ EXCEPINFO __RPC_FAR *pExcepInfo,
            /* [out] */ UINT __RPC_FAR *puArgErr);
        
        /* [id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Name )( 
            IADsClass __RPC_FAR * This,
            /* [retval][out] */ BSTR __RPC_FAR *retval);
        
        /* [id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Class )( 
            IADsClass __RPC_FAR * This,
            /* [retval][out] */ BSTR __RPC_FAR *retval);
        
        /* [id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_GUID )( 
            IADsClass __RPC_FAR * This,
            /* [retval][out] */ BSTR __RPC_FAR *retval);
        
        /* [id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_ADsPath )( 
            IADsClass __RPC_FAR * This,
            /* [retval][out] */ BSTR __RPC_FAR *retval);
        
        /* [id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Parent )( 
            IADsClass __RPC_FAR * This,
            /* [retval][out] */ BSTR __RPC_FAR *retval);
        
        /* [id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Schema )( 
            IADsClass __RPC_FAR * This,
            /* [retval][out] */ BSTR __RPC_FAR *retval);
        
        /* [id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetInfo )( 
            IADsClass __RPC_FAR * This);
        
        /* [id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *SetInfo )( 
            IADsClass __RPC_FAR * This);
        
        /* [id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Get )( 
            IADsClass __RPC_FAR * This,
            /* [in] */ BSTR bstrName,
            /* [retval][out] */ VARIANT __RPC_FAR *pvProp);
        
        /* [id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Put )( 
            IADsClass __RPC_FAR * This,
            /* [in] */ BSTR bstrName,
            /* [in] */ VARIANT vProp);
        
        /* [id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetEx )( 
            IADsClass __RPC_FAR * This,
            /* [in] */ BSTR bstrName,
            /* [retval][out] */ VARIANT __RPC_FAR *pvProp);
        
        /* [id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *PutEx )( 
            IADsClass __RPC_FAR * This,
            /* [in] */ long lnControlCode,
            /* [in] */ BSTR bstrName,
            /* [in] */ VARIANT vProp);
        
        /* [id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetInfoEx )( 
            IADsClass __RPC_FAR * This,
            /* [in] */ VARIANT vProperties,
            /* [in] */ long lnReserved);
        
        /* [id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_PrimaryInterface )( 
            IADsClass __RPC_FAR * This,
            /* [retval][out] */ BSTR __RPC_FAR *retval);
        
        /* [id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_CLSID )( 
            IADsClass __RPC_FAR * This,
            /* [retval][out] */ BSTR __RPC_FAR *retval);
        
        /* [id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_CLSID )( 
            IADsClass __RPC_FAR * This,
            /* [in] */ BSTR bstrCLSID);
        
        /* [id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_OID )( 
            IADsClass __RPC_FAR * This,
            /* [retval][out] */ BSTR __RPC_FAR *retval);
        
        /* [id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_OID )( 
            IADsClass __RPC_FAR * This,
            /* [in] */ BSTR bstrOID);
        
        /* [id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Abstract )( 
            IADsClass __RPC_FAR * This,
            /* [retval][out] */ VARIANT_BOOL __RPC_FAR *retval);
        
        /* [id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_Abstract )( 
            IADsClass __RPC_FAR * This,
            /* [in] */ VARIANT_BOOL fAbstract);
        
        /* [id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Auxiliary )( 
            IADsClass __RPC_FAR * This,
            /* [retval][out] */ VARIANT_BOOL __RPC_FAR *retval);
        
        /* [id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_Auxiliary )( 
            IADsClass __RPC_FAR * This,
            /* [in] */ VARIANT_BOOL fAuxiliary);
        
        /* [id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_MandatoryProperties )( 
            IADsClass __RPC_FAR * This,
            /* [retval][out] */ VARIANT __RPC_FAR *retval);
        
        /* [id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_MandatoryProperties )( 
            IADsClass __RPC_FAR * This,
            /* [in] */ VARIANT vMandatoryProperties);
        
        /* [id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_OptionalProperties )( 
            IADsClass __RPC_FAR * This,
            /* [retval][out] */ VARIANT __RPC_FAR *retval);
        
        /* [id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_OptionalProperties )( 
            IADsClass __RPC_FAR * This,
            /* [in] */ VARIANT vOptionalProperties);
        
        /* [id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_NamingProperties )( 
            IADsClass __RPC_FAR * This,
            /* [retval][out] */ VARIANT __RPC_FAR *retval);
        
        /* [id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_NamingProperties )( 
            IADsClass __RPC_FAR * This,
            /* [in] */ VARIANT vNamingProperties);
        
        /* [id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_DerivedFrom )( 
            IADsClass __RPC_FAR * This,
            /* [retval][out] */ VARIANT __RPC_FAR *retval);
        
        /* [id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_DerivedFrom )( 
            IADsClass __RPC_FAR * This,
            /* [in] */ VARIANT vDerivedFrom);
        
        /* [id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_AuxDerivedFrom )( 
            IADsClass __RPC_FAR * This,
            /* [retval][out] */ VARIANT __RPC_FAR *retval);
        
        /* [id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_AuxDerivedFrom )( 
            IADsClass __RPC_FAR * This,
            /* [in] */ VARIANT vAuxDerivedFrom);
        
        /* [id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_PossibleSuperiors )( 
            IADsClass __RPC_FAR * This,
            /* [retval][out] */ VARIANT __RPC_FAR *retval);
        
        /* [id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_PossibleSuperiors )( 
            IADsClass __RPC_FAR * This,
            /* [in] */ VARIANT vPossibleSuperiors);
        
        /* [id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Containment )( 
            IADsClass __RPC_FAR * This,
            /* [retval][out] */ VARIANT __RPC_FAR *retval);
        
        /* [id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_Containment )( 
            IADsClass __RPC_FAR * This,
            /* [in] */ VARIANT vContainment);
        
        /* [id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Container )( 
            IADsClass __RPC_FAR * This,
            /* [retval][out] */ VARIANT_BOOL __RPC_FAR *retval);
        
        /* [id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_Container )( 
            IADsClass __RPC_FAR * This,
            /* [in] */ VARIANT_BOOL fContainer);
        
        /* [id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_HelpFileName )( 
            IADsClass __RPC_FAR * This,
            /* [retval][out] */ BSTR __RPC_FAR *retval);
        
        /* [id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_HelpFileName )( 
            IADsClass __RPC_FAR * This,
            /* [in] */ BSTR bstrHelpFileName);
        
        /* [id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_HelpFileContext )( 
            IADsClass __RPC_FAR * This,
            /* [retval][out] */ long __RPC_FAR *retval);
        
        /* [id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_HelpFileContext )( 
            IADsClass __RPC_FAR * This,
            /* [in] */ long lnHelpFileContext);
        
        /* [id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Qualifiers )( 
            IADsClass __RPC_FAR * This,
            /* [retval][out] */ IADsCollection __RPC_FAR *__RPC_FAR *ppQualifiers);
        
        END_INTERFACE
    } IADsClassVtbl;

    interface IADsClass
    {
        CONST_VTBL struct IADsClassVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IADsClass_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IADsClass_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IADsClass_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IADsClass_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define IADsClass_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define IADsClass_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define IADsClass_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)


#define IADsClass_get_Name(This,retval)	\
    (This)->lpVtbl -> get_Name(This,retval)

#define IADsClass_get_Class(This,retval)	\
    (This)->lpVtbl -> get_Class(This,retval)

#define IADsClass_get_GUID(This,retval)	\
    (This)->lpVtbl -> get_GUID(This,retval)

#define IADsClass_get_ADsPath(This,retval)	\
    (This)->lpVtbl -> get_ADsPath(This,retval)

#define IADsClass_get_Parent(This,retval)	\
    (This)->lpVtbl -> get_Parent(This,retval)

#define IADsClass_get_Schema(This,retval)	\
    (This)->lpVtbl -> get_Schema(This,retval)

#define IADsClass_GetInfo(This)	\
    (This)->lpVtbl -> GetInfo(This)

#define IADsClass_SetInfo(This)	\
    (This)->lpVtbl -> SetInfo(This)

#define IADsClass_Get(This,bstrName,pvProp)	\
    (This)->lpVtbl -> Get(This,bstrName,pvProp)

#define IADsClass_Put(This,bstrName,vProp)	\
    (This)->lpVtbl -> Put(This,bstrName,vProp)

#define IADsClass_GetEx(This,bstrName,pvProp)	\
    (This)->lpVtbl -> GetEx(This,bstrName,pvProp)

#define IADsClass_PutEx(This,lnControlCode,bstrName,vProp)	\
    (This)->lpVtbl -> PutEx(This,lnControlCode,bstrName,vProp)

#define IADsClass_GetInfoEx(This,vProperties,lnReserved)	\
    (This)->lpVtbl -> GetInfoEx(This,vProperties,lnReserved)


#define IADsClass_get_PrimaryInterface(This,retval)	\
    (This)->lpVtbl -> get_PrimaryInterface(This,retval)

#define IADsClass_get_CLSID(This,retval)	\
    (This)->lpVtbl -> get_CLSID(This,retval)

#define IADsClass_put_CLSID(This,bstrCLSID)	\
    (This)->lpVtbl -> put_CLSID(This,bstrCLSID)

#define IADsClass_get_OID(This,retval)	\
    (This)->lpVtbl -> get_OID(This,retval)

#define IADsClass_put_OID(This,bstrOID)	\
    (This)->lpVtbl -> put_OID(This,bstrOID)

#define IADsClass_get_Abstract(This,retval)	\
    (This)->lpVtbl -> get_Abstract(This,retval)

#define IADsClass_put_Abstract(This,fAbstract)	\
    (This)->lpVtbl -> put_Abstract(This,fAbstract)

#define IADsClass_get_Auxiliary(This,retval)	\
    (This)->lpVtbl -> get_Auxiliary(This,retval)

#define IADsClass_put_Auxiliary(This,fAuxiliary)	\
    (This)->lpVtbl -> put_Auxiliary(This,fAuxiliary)

#define IADsClass_get_MandatoryProperties(This,retval)	\
    (This)->lpVtbl -> get_MandatoryProperties(This,retval)

#define IADsClass_put_MandatoryProperties(This,vMandatoryProperties)	\
    (This)->lpVtbl -> put_MandatoryProperties(This,vMandatoryProperties)

#define IADsClass_get_OptionalProperties(This,retval)	\
    (This)->lpVtbl -> get_OptionalProperties(This,retval)

#define IADsClass_put_OptionalProperties(This,vOptionalProperties)	\
    (This)->lpVtbl -> put_OptionalProperties(This,vOptionalProperties)

#define IADsClass_get_NamingProperties(This,retval)	\
    (This)->lpVtbl -> get_NamingProperties(This,retval)

#define IADsClass_put_NamingProperties(This,vNamingProperties)	\
    (This)->lpVtbl -> put_NamingProperties(This,vNamingProperties)

#define IADsClass_get_DerivedFrom(This,retval)	\
    (This)->lpVtbl -> get_DerivedFrom(This,retval)

#define IADsClass_put_DerivedFrom(This,vDerivedFrom)	\
    (This)->lpVtbl -> put_DerivedFrom(This,vDerivedFrom)

#define IADsClass_get_AuxDerivedFrom(This,retval)	\
    (This)->lpVtbl -> get_AuxDerivedFrom(This,retval)

#define IADsClass_put_AuxDerivedFrom(This,vAuxDerivedFrom)	\
    (This)->lpVtbl -> put_AuxDerivedFrom(This,vAuxDerivedFrom)

#define IADsClass_get_PossibleSuperiors(This,retval)	\
    (This)->lpVtbl -> get_PossibleSuperiors(This,retval)

#define IADsClass_put_PossibleSuperiors(This,vPossibleSuperiors)	\
    (This)->lpVtbl -> put_PossibleSuperiors(This,vPossibleSuperiors)

#define IADsClass_get_Containment(This,retval)	\
    (This)->lpVtbl -> get_Containment(This,retval)

#define IADsClass_put_Containment(This,vContainment)	\
    (This)->lpVtbl -> put_Containment(This,vContainment)

#define IADsClass_get_Container(This,retval)	\
    (This)->lpVtbl -> get_Container(This,retval)

#define IADsClass_put_Container(This,fContainer)	\
    (This)->lpVtbl -> put_Container(This,fContainer)

#define IADsClass_get_HelpFileName(This,retval)	\
    (This)->lpVtbl -> get_HelpFileName(This,retval)

#define IADsClass_put_HelpFileName(This,bstrHelpFileName)	\
    (This)->lpVtbl -> put_HelpFileName(This,bstrHelpFileName)

#define IADsClass_get_HelpFileContext(This,retval)	\
    (This)->lpVtbl -> get_HelpFileContext(This,retval)

#define IADsClass_put_HelpFileContext(This,lnHelpFileContext)	\
    (This)->lpVtbl -> put_HelpFileContext(This,lnHelpFileContext)

#define IADsClass_Qualifiers(This,ppQualifiers)	\
    (This)->lpVtbl -> Qualifiers(This,ppQualifiers)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [id][propget] */ HRESULT STDMETHODCALLTYPE IADsClass_get_PrimaryInterface_Proxy( 
    IADsClass __RPC_FAR * This,
    /* [retval][out] */ BSTR __RPC_FAR *retval);


void __RPC_STUB IADsClass_get_PrimaryInterface_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [id][propget] */ HRESULT STDMETHODCALLTYPE IADsClass_get_CLSID_Proxy( 
    IADsClass __RPC_FAR * This,
    /* [retval][out] */ BSTR __RPC_FAR *retval);


void __RPC_STUB IADsClass_get_CLSID_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [id][propput] */ HRESULT STDMETHODCALLTYPE IADsClass_put_CLSID_Proxy( 
    IADsClass __RPC_FAR * This,
    /* [in] */ BSTR bstrCLSID);


void __RPC_STUB IADsClass_put_CLSID_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [id][propget] */ HRESULT STDMETHODCALLTYPE IADsClass_get_OID_Proxy( 
    IADsClass __RPC_FAR * This,
    /* [retval][out] */ BSTR __RPC_FAR *retval);


void __RPC_STUB IADsClass_get_OID_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [id][propput] */ HRESULT STDMETHODCALLTYPE IADsClass_put_OID_Proxy( 
    IADsClass __RPC_FAR * This,
    /* [in] */ BSTR bstrOID);


void __RPC_STUB IADsClass_put_OID_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [id][propget] */ HRESULT STDMETHODCALLTYPE IADsClass_get_Abstract_Proxy( 
    IADsClass __RPC_FAR * This,
    /* [retval][out] */ VARIANT_BOOL __RPC_FAR *retval);


void __RPC_STUB IADsClass_get_Abstract_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [id][propput] */ HRESULT STDMETHODCALLTYPE IADsClass_put_Abstract_Proxy( 
    IADsClass __RPC_FAR * This,
    /* [in] */ VARIANT_BOOL fAbstract);


void __RPC_STUB IADsClass_put_Abstract_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [id][propget] */ HRESULT STDMETHODCALLTYPE IADsClass_get_Auxiliary_Proxy( 
    IADsClass __RPC_FAR * This,
    /* [retval][out] */ VARIANT_BOOL __RPC_FAR *retval);


void __RPC_STUB IADsClass_get_Auxiliary_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [id][propput] */ HRESULT STDMETHODCALLTYPE IADsClass_put_Auxiliary_Proxy( 
    IADsClass __RPC_FAR * This,
    /* [in] */ VARIANT_BOOL fAuxiliary);


void __RPC_STUB IADsClass_put_Auxiliary_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [id][propget] */ HRESULT STDMETHODCALLTYPE IADsClass_get_MandatoryProperties_Proxy( 
    IADsClass __RPC_FAR * This,
    /* [retval][out] */ VARIANT __RPC_FAR *retval);


void __RPC_STUB IADsClass_get_MandatoryProperties_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [id][propput] */ HRESULT STDMETHODCALLTYPE IADsClass_put_MandatoryProperties_Proxy( 
    IADsClass __RPC_FAR * This,
    /* [in] */ VARIANT vMandatoryProperties);


void __RPC_STUB IADsClass_put_MandatoryProperties_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [id][propget] */ HRESULT STDMETHODCALLTYPE IADsClass_get_OptionalProperties_Proxy( 
    IADsClass __RPC_FAR * This,
    /* [retval][out] */ VARIANT __RPC_FAR *retval);


void __RPC_STUB IADsClass_get_OptionalProperties_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [id][propput] */ HRESULT STDMETHODCALLTYPE IADsClass_put_OptionalProperties_Proxy( 
    IADsClass __RPC_FAR * This,
    /* [in] */ VARIANT vOptionalProperties);


void __RPC_STUB IADsClass_put_OptionalProperties_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [id][propget] */ HRESULT STDMETHODCALLTYPE IADsClass_get_NamingProperties_Proxy( 
    IADsClass __RPC_FAR * This,
    /* [retval][out] */ VARIANT __RPC_FAR *retval);


void __RPC_STUB IADsClass_get_NamingProperties_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [id][propput] */ HRESULT STDMETHODCALLTYPE IADsClass_put_NamingProperties_Proxy( 
    IADsClass __RPC_FAR * This,
    /* [in] */ VARIANT vNamingProperties);


void __RPC_STUB IADsClass_put_NamingProperties_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [id][propget] */ HRESULT STDMETHODCALLTYPE IADsClass_get_DerivedFrom_Proxy( 
    IADsClass __RPC_FAR * This,
    /* [retval][out] */ VARIANT __RPC_FAR *retval);


void __RPC_STUB IADsClass_get_DerivedFrom_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [id][propput] */ HRESULT STDMETHODCALLTYPE IADsClass_put_DerivedFrom_Proxy( 
    IADsClass __RPC_FAR * This,
    /* [in] */ VARIANT vDerivedFrom);


void __RPC_STUB IADsClass_put_DerivedFrom_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [id][propget] */ HRESULT STDMETHODCALLTYPE IADsClass_get_AuxDerivedFrom_Proxy( 
    IADsClass __RPC_FAR * This,
    /* [retval][out] */ VARIANT __RPC_FAR *retval);


void __RPC_STUB IADsClass_get_AuxDerivedFrom_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [id][propput] */ HRESULT STDMETHODCALLTYPE IADsClass_put_AuxDerivedFrom_Proxy( 
    IADsClass __RPC_FAR * This,
    /* [in] */ VARIANT vAuxDerivedFrom);


void __RPC_STUB IADsClass_put_AuxDerivedFrom_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [id][propget] */ HRESULT STDMETHODCALLTYPE IADsClass_get_PossibleSuperiors_Proxy( 
    IADsClass __RPC_FAR * This,
    /* [retval][out] */ VARIANT __RPC_FAR *retval);


void __RPC_STUB IADsClass_get_PossibleSuperiors_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [id][propput] */ HRESULT STDMETHODCALLTYPE IADsClass_put_PossibleSuperiors_Proxy( 
    IADsClass __RPC_FAR * This,
    /* [in] */ VARIANT vPossibleSuperiors);


void __RPC_STUB IADsClass_put_PossibleSuperiors_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [id][propget] */ HRESULT STDMETHODCALLTYPE IADsClass_get_Containment_Proxy( 
    IADsClass __RPC_FAR * This,
    /* [retval][out] */ VARIANT __RPC_FAR *retval);


void __RPC_STUB IADsClass_get_Containment_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [id][propput] */ HRESULT STDMETHODCALLTYPE IADsClass_put_Containment_Proxy( 
    IADsClass __RPC_FAR * This,
    /* [in] */ VARIANT vContainment);


void __RPC_STUB IADsClass_put_Containment_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [id][propget] */ HRESULT STDMETHODCALLTYPE IADsClass_get_Container_Proxy( 
    IADsClass __RPC_FAR * This,
    /* [retval][out] */ VARIANT_BOOL __RPC_FAR *retval);


void __RPC_STUB IADsClass_get_Container_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [id][propput] */ HRESULT STDMETHODCALLTYPE IADsClass_put_Container_Proxy( 
    IADsClass __RPC_FAR * This,
    /* [in] */ VARIANT_BOOL fContainer);


void __RPC_STUB IADsClass_put_Container_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [id][propget] */ HRESULT STDMETHODCALLTYPE IADsClass_get_HelpFileName_Proxy( 
    IADsClass __RPC_FAR * This,
    /* [retval][out] */ BSTR __RPC_FAR *retval);


void __RPC_STUB IADsClass_get_HelpFileName_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [id][propput] */ HRESULT STDMETHODCALLTYPE IADsClass_put_HelpFileName_Proxy( 
    IADsClass __RPC_FAR * This,
    /* [in] */ BSTR bstrHelpFileName);


void __RPC_STUB IADsClass_put_HelpFileName_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [id][propget] */ HRESULT STDMETHODCALLTYPE IADsClass_get_HelpFileContext_Proxy( 
    IADsClass __RPC_FAR * This,
    /* [retval][out] */ long __RPC_FAR *retval);


void __RPC_STUB IADsClass_get_HelpFileContext_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [id][propput] */ HRESULT STDMETHODCALLTYPE IADsClass_put_HelpFileContext_Proxy( 
    IADsClass __RPC_FAR * This,
    /* [in] */ long lnHelpFileContext);


void __RPC_STUB IADsClass_put_HelpFileContext_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [id] */ HRESULT STDMETHODCALLTYPE IADsClass_Qualifiers_Proxy( 
    IADsClass __RPC_FAR * This,
    /* [retval][out] */ IADsCollection __RPC_FAR *__RPC_FAR *ppQualifiers);


void __RPC_STUB IADsClass_Qualifiers_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IADsClass_INTERFACE_DEFINED__ */


#ifndef __IADsProperty_INTERFACE_DEFINED__
#define __IADsProperty_INTERFACE_DEFINED__

/****************************************
 * Generated header for interface: IADsProperty
 * at Mon Oct 13 13:47:30 1997
 * using MIDL 3.00.44
 ****************************************/
/* [object][dual][oleautomation][uuid] */ 



EXTERN_C const IID IID_IADsProperty;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    interface IADsProperty : public IADs
    {
    public:
        virtual /* [id][propget] */ HRESULT STDMETHODCALLTYPE get_OID( 
            /* [retval][out] */ BSTR __RPC_FAR *retval) = 0;
        
        virtual /* [id][propput] */ HRESULT STDMETHODCALLTYPE put_OID( 
            /* [in] */ BSTR bstrOID) = 0;
        
        virtual /* [id][propget] */ HRESULT STDMETHODCALLTYPE get_Syntax( 
            /* [retval][out] */ BSTR __RPC_FAR *retval) = 0;
        
        virtual /* [id][propput] */ HRESULT STDMETHODCALLTYPE put_Syntax( 
            /* [in] */ BSTR bstrSyntax) = 0;
        
        virtual /* [id][propget] */ HRESULT STDMETHODCALLTYPE get_MaxRange( 
            /* [retval][out] */ long __RPC_FAR *retval) = 0;
        
        virtual /* [id][propput] */ HRESULT STDMETHODCALLTYPE put_MaxRange( 
            /* [in] */ long lnMaxRange) = 0;
        
        virtual /* [id][propget] */ HRESULT STDMETHODCALLTYPE get_MinRange( 
            /* [retval][out] */ long __RPC_FAR *retval) = 0;
        
        virtual /* [id][propput] */ HRESULT STDMETHODCALLTYPE put_MinRange( 
            /* [in] */ long lnMinRange) = 0;
        
        virtual /* [id][propget] */ HRESULT STDMETHODCALLTYPE get_MultiValued( 
            /* [retval][out] */ VARIANT_BOOL __RPC_FAR *retval) = 0;
        
        virtual /* [id][propput] */ HRESULT STDMETHODCALLTYPE put_MultiValued( 
            /* [in] */ VARIANT_BOOL fMultiValued) = 0;
        
        virtual /* [id] */ HRESULT STDMETHODCALLTYPE Qualifiers( 
            /* [retval][out] */ IADsCollection __RPC_FAR *__RPC_FAR *ppQualifiers) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IADsPropertyVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            IADsProperty __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            IADsProperty __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            IADsProperty __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfoCount )( 
            IADsProperty __RPC_FAR * This,
            /* [out] */ UINT __RPC_FAR *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfo )( 
            IADsProperty __RPC_FAR * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo __RPC_FAR *__RPC_FAR *ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetIDsOfNames )( 
            IADsProperty __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR __RPC_FAR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID __RPC_FAR *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Invoke )( 
            IADsProperty __RPC_FAR * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS __RPC_FAR *pDispParams,
            /* [out] */ VARIANT __RPC_FAR *pVarResult,
            /* [out] */ EXCEPINFO __RPC_FAR *pExcepInfo,
            /* [out] */ UINT __RPC_FAR *puArgErr);
        
        /* [id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Name )( 
            IADsProperty __RPC_FAR * This,
            /* [retval][out] */ BSTR __RPC_FAR *retval);
        
        /* [id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Class )( 
            IADsProperty __RPC_FAR * This,
            /* [retval][out] */ BSTR __RPC_FAR *retval);
        
        /* [id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_GUID )( 
            IADsProperty __RPC_FAR * This,
            /* [retval][out] */ BSTR __RPC_FAR *retval);
        
        /* [id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_ADsPath )( 
            IADsProperty __RPC_FAR * This,
            /* [retval][out] */ BSTR __RPC_FAR *retval);
        
        /* [id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Parent )( 
            IADsProperty __RPC_FAR * This,
            /* [retval][out] */ BSTR __RPC_FAR *retval);
        
        /* [id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Schema )( 
            IADsProperty __RPC_FAR * This,
            /* [retval][out] */ BSTR __RPC_FAR *retval);
        
        /* [id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetInfo )( 
            IADsProperty __RPC_FAR * This);
        
        /* [id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *SetInfo )( 
            IADsProperty __RPC_FAR * This);
        
        /* [id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Get )( 
            IADsProperty __RPC_FAR * This,
            /* [in] */ BSTR bstrName,
            /* [retval][out] */ VARIANT __RPC_FAR *pvProp);
        
        /* [id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Put )( 
            IADsProperty __RPC_FAR * This,
            /* [in] */ BSTR bstrName,
            /* [in] */ VARIANT vProp);
        
        /* [id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetEx )( 
            IADsProperty __RPC_FAR * This,
            /* [in] */ BSTR bstrName,
            /* [retval][out] */ VARIANT __RPC_FAR *pvProp);
        
        /* [id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *PutEx )( 
            IADsProperty __RPC_FAR * This,
            /* [in] */ long lnControlCode,
            /* [in] */ BSTR bstrName,
            /* [in] */ VARIANT vProp);
        
        /* [id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetInfoEx )( 
            IADsProperty __RPC_FAR * This,
            /* [in] */ VARIANT vProperties,
            /* [in] */ long lnReserved);
        
        /* [id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_OID )( 
            IADsProperty __RPC_FAR * This,
            /* [retval][out] */ BSTR __RPC_FAR *retval);
        
        /* [id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_OID )( 
            IADsProperty __RPC_FAR * This,
            /* [in] */ BSTR bstrOID);
        
        /* [id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Syntax )( 
            IADsProperty __RPC_FAR * This,
            /* [retval][out] */ BSTR __RPC_FAR *retval);
        
        /* [id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_Syntax )( 
            IADsProperty __RPC_FAR * This,
            /* [in] */ BSTR bstrSyntax);
        
        /* [id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_MaxRange )( 
            IADsProperty __RPC_FAR * This,
            /* [retval][out] */ long __RPC_FAR *retval);
        
        /* [id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_MaxRange )( 
            IADsProperty __RPC_FAR * This,
            /* [in] */ long lnMaxRange);
        
        /* [id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_MinRange )( 
            IADsProperty __RPC_FAR * This,
            /* [retval][out] */ long __RPC_FAR *retval);
        
        /* [id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_MinRange )( 
            IADsProperty __RPC_FAR * This,
            /* [in] */ long lnMinRange);
        
        /* [id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_MultiValued )( 
            IADsProperty __RPC_FAR * This,
            /* [retval][out] */ VARIANT_BOOL __RPC_FAR *retval);
        
        /* [id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_MultiValued )( 
            IADsProperty __RPC_FAR * This,
            /* [in] */ VARIANT_BOOL fMultiValued);
        
        /* [id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Qualifiers )( 
            IADsProperty __RPC_FAR * This,
            /* [retval][out] */ IADsCollection __RPC_FAR *__RPC_FAR *ppQualifiers);
        
        END_INTERFACE
    } IADsPropertyVtbl;

    interface IADsProperty
    {
        CONST_VTBL struct IADsPropertyVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IADsProperty_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IADsProperty_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IADsProperty_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IADsProperty_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define IADsProperty_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define IADsProperty_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define IADsProperty_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)


#define IADsProperty_get_Name(This,retval)	\
    (This)->lpVtbl -> get_Name(This,retval)

#define IADsProperty_get_Class(This,retval)	\
    (This)->lpVtbl -> get_Class(This,retval)

#define IADsProperty_get_GUID(This,retval)	\
    (This)->lpVtbl -> get_GUID(This,retval)

#define IADsProperty_get_ADsPath(This,retval)	\
    (This)->lpVtbl -> get_ADsPath(This,retval)

#define IADsProperty_get_Parent(This,retval)	\
    (This)->lpVtbl -> get_Parent(This,retval)

#define IADsProperty_get_Schema(This,retval)	\
    (This)->lpVtbl -> get_Schema(This,retval)

#define IADsProperty_GetInfo(This)	\
    (This)->lpVtbl -> GetInfo(This)

#define IADsProperty_SetInfo(This)	\
    (This)->lpVtbl -> SetInfo(This)

#define IADsProperty_Get(This,bstrName,pvProp)	\
    (This)->lpVtbl -> Get(This,bstrName,pvProp)

#define IADsProperty_Put(This,bstrName,vProp)	\
    (This)->lpVtbl -> Put(This,bstrName,vProp)

#define IADsProperty_GetEx(This,bstrName,pvProp)	\
    (This)->lpVtbl -> GetEx(This,bstrName,pvProp)

#define IADsProperty_PutEx(This,lnControlCode,bstrName,vProp)	\
    (This)->lpVtbl -> PutEx(This,lnControlCode,bstrName,vProp)

#define IADsProperty_GetInfoEx(This,vProperties,lnReserved)	\
    (This)->lpVtbl -> GetInfoEx(This,vProperties,lnReserved)


#define IADsProperty_get_OID(This,retval)	\
    (This)->lpVtbl -> get_OID(This,retval)

#define IADsProperty_put_OID(This,bstrOID)	\
    (This)->lpVtbl -> put_OID(This,bstrOID)

#define IADsProperty_get_Syntax(This,retval)	\
    (This)->lpVtbl -> get_Syntax(This,retval)

#define IADsProperty_put_Syntax(This,bstrSyntax)	\
    (This)->lpVtbl -> put_Syntax(This,bstrSyntax)

#define IADsProperty_get_MaxRange(This,retval)	\
    (This)->lpVtbl -> get_MaxRange(This,retval)

#define IADsProperty_put_MaxRange(This,lnMaxRange)	\
    (This)->lpVtbl -> put_MaxRange(This,lnMaxRange)

#define IADsProperty_get_MinRange(This,retval)	\
    (This)->lpVtbl -> get_MinRange(This,retval)

#define IADsProperty_put_MinRange(This,lnMinRange)	\
    (This)->lpVtbl -> put_MinRange(This,lnMinRange)

#define IADsProperty_get_MultiValued(This,retval)	\
    (This)->lpVtbl -> get_MultiValued(This,retval)

#define IADsProperty_put_MultiValued(This,fMultiValued)	\
    (This)->lpVtbl -> put_MultiValued(This,fMultiValued)

#define IADsProperty_Qualifiers(This,ppQualifiers)	\
    (This)->lpVtbl -> Qualifiers(This,ppQualifiers)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [id][propget] */ HRESULT STDMETHODCALLTYPE IADsProperty_get_OID_Proxy( 
    IADsProperty __RPC_FAR * This,
    /* [retval][out] */ BSTR __RPC_FAR *retval);


void __RPC_STUB IADsProperty_get_OID_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [id][propput] */ HRESULT STDMETHODCALLTYPE IADsProperty_put_OID_Proxy( 
    IADsProperty __RPC_FAR * This,
    /* [in] */ BSTR bstrOID);


void __RPC_STUB IADsProperty_put_OID_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [id][propget] */ HRESULT STDMETHODCALLTYPE IADsProperty_get_Syntax_Proxy( 
    IADsProperty __RPC_FAR * This,
    /* [retval][out] */ BSTR __RPC_FAR *retval);


void __RPC_STUB IADsProperty_get_Syntax_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [id][propput] */ HRESULT STDMETHODCALLTYPE IADsProperty_put_Syntax_Proxy( 
    IADsProperty __RPC_FAR * This,
    /* [in] */ BSTR bstrSyntax);


void __RPC_STUB IADsProperty_put_Syntax_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [id][propget] */ HRESULT STDMETHODCALLTYPE IADsProperty_get_MaxRange_Proxy( 
    IADsProperty __RPC_FAR * This,
    /* [retval][out] */ long __RPC_FAR *retval);


void __RPC_STUB IADsProperty_get_MaxRange_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [id][propput] */ HRESULT STDMETHODCALLTYPE IADsProperty_put_MaxRange_Proxy( 
    IADsProperty __RPC_FAR * This,
    /* [in] */ long lnMaxRange);


void __RPC_STUB IADsProperty_put_MaxRange_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [id][propget] */ HRESULT STDMETHODCALLTYPE IADsProperty_get_MinRange_Proxy( 
    IADsProperty __RPC_FAR * This,
    /* [retval][out] */ long __RPC_FAR *retval);


void __RPC_STUB IADsProperty_get_MinRange_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [id][propput] */ HRESULT STDMETHODCALLTYPE IADsProperty_put_MinRange_Proxy( 
    IADsProperty __RPC_FAR * This,
    /* [in] */ long lnMinRange);


void __RPC_STUB IADsProperty_put_MinRange_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [id][propget] */ HRESULT STDMETHODCALLTYPE IADsProperty_get_MultiValued_Proxy( 
    IADsProperty __RPC_FAR * This,
    /* [retval][out] */ VARIANT_BOOL __RPC_FAR *retval);


void __RPC_STUB IADsProperty_get_MultiValued_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [id][propput] */ HRESULT STDMETHODCALLTYPE IADsProperty_put_MultiValued_Proxy( 
    IADsProperty __RPC_FAR * This,
    /* [in] */ VARIANT_BOOL fMultiValued);


void __RPC_STUB IADsProperty_put_MultiValued_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [id] */ HRESULT STDMETHODCALLTYPE IADsProperty_Qualifiers_Proxy( 
    IADsProperty __RPC_FAR * This,
    /* [retval][out] */ IADsCollection __RPC_FAR *__RPC_FAR *ppQualifiers);


void __RPC_STUB IADsProperty_Qualifiers_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IADsProperty_INTERFACE_DEFINED__ */


#ifndef __IADsSyntax_INTERFACE_DEFINED__
#define __IADsSyntax_INTERFACE_DEFINED__

/****************************************
 * Generated header for interface: IADsSyntax
 * at Mon Oct 13 13:47:30 1997
 * using MIDL 3.00.44
 ****************************************/
/* [object][dual][oleautomation][uuid] */ 



EXTERN_C const IID IID_IADsSyntax;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    interface IADsSyntax : public IADs
    {
    public:
        virtual /* [id][propget] */ HRESULT STDMETHODCALLTYPE get_OleAutoDataType( 
            /* [retval][out] */ long __RPC_FAR *retval) = 0;
        
        virtual /* [id][propput] */ HRESULT STDMETHODCALLTYPE put_OleAutoDataType( 
            /* [in] */ long lnOleAutoDataType) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IADsSyntaxVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            IADsSyntax __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            IADsSyntax __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            IADsSyntax __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfoCount )( 
            IADsSyntax __RPC_FAR * This,
            /* [out] */ UINT __RPC_FAR *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfo )( 
            IADsSyntax __RPC_FAR * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo __RPC_FAR *__RPC_FAR *ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetIDsOfNames )( 
            IADsSyntax __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR __RPC_FAR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID __RPC_FAR *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Invoke )( 
            IADsSyntax __RPC_FAR * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS __RPC_FAR *pDispParams,
            /* [out] */ VARIANT __RPC_FAR *pVarResult,
            /* [out] */ EXCEPINFO __RPC_FAR *pExcepInfo,
            /* [out] */ UINT __RPC_FAR *puArgErr);
        
        /* [id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Name )( 
            IADsSyntax __RPC_FAR * This,
            /* [retval][out] */ BSTR __RPC_FAR *retval);
        
        /* [id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Class )( 
            IADsSyntax __RPC_FAR * This,
            /* [retval][out] */ BSTR __RPC_FAR *retval);
        
        /* [id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_GUID )( 
            IADsSyntax __RPC_FAR * This,
            /* [retval][out] */ BSTR __RPC_FAR *retval);
        
        /* [id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_ADsPath )( 
            IADsSyntax __RPC_FAR * This,
            /* [retval][out] */ BSTR __RPC_FAR *retval);
        
        /* [id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Parent )( 
            IADsSyntax __RPC_FAR * This,
            /* [retval][out] */ BSTR __RPC_FAR *retval);
        
        /* [id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Schema )( 
            IADsSyntax __RPC_FAR * This,
            /* [retval][out] */ BSTR __RPC_FAR *retval);
        
        /* [id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetInfo )( 
            IADsSyntax __RPC_FAR * This);
        
        /* [id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *SetInfo )( 
            IADsSyntax __RPC_FAR * This);
        
        /* [id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Get )( 
            IADsSyntax __RPC_FAR * This,
            /* [in] */ BSTR bstrName,
            /* [retval][out] */ VARIANT __RPC_FAR *pvProp);
        
        /* [id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Put )( 
            IADsSyntax __RPC_FAR * This,
            /* [in] */ BSTR bstrName,
            /* [in] */ VARIANT vProp);
        
        /* [id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetEx )( 
            IADsSyntax __RPC_FAR * This,
            /* [in] */ BSTR bstrName,
            /* [retval][out] */ VARIANT __RPC_FAR *pvProp);
        
        /* [id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *PutEx )( 
            IADsSyntax __RPC_FAR * This,
            /* [in] */ long lnControlCode,
            /* [in] */ BSTR bstrName,
            /* [in] */ VARIANT vProp);
        
        /* [id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetInfoEx )( 
            IADsSyntax __RPC_FAR * This,
            /* [in] */ VARIANT vProperties,
            /* [in] */ long lnReserved);
        
        /* [id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_OleAutoDataType )( 
            IADsSyntax __RPC_FAR * This,
            /* [retval][out] */ long __RPC_FAR *retval);
        
        /* [id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_OleAutoDataType )( 
            IADsSyntax __RPC_FAR * This,
            /* [in] */ long lnOleAutoDataType);
        
        END_INTERFACE
    } IADsSyntaxVtbl;

    interface IADsSyntax
    {
        CONST_VTBL struct IADsSyntaxVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IADsSyntax_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IADsSyntax_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IADsSyntax_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IADsSyntax_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define IADsSyntax_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define IADsSyntax_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define IADsSyntax_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)


#define IADsSyntax_get_Name(This,retval)	\
    (This)->lpVtbl -> get_Name(This,retval)

#define IADsSyntax_get_Class(This,retval)	\
    (This)->lpVtbl -> get_Class(This,retval)

#define IADsSyntax_get_GUID(This,retval)	\
    (This)->lpVtbl -> get_GUID(This,retval)

#define IADsSyntax_get_ADsPath(This,retval)	\
    (This)->lpVtbl -> get_ADsPath(This,retval)

#define IADsSyntax_get_Parent(This,retval)	\
    (This)->lpVtbl -> get_Parent(This,retval)

#define IADsSyntax_get_Schema(This,retval)	\
    (This)->lpVtbl -> get_Schema(This,retval)

#define IADsSyntax_GetInfo(This)	\
    (This)->lpVtbl -> GetInfo(This)

#define IADsSyntax_SetInfo(This)	\
    (This)->lpVtbl -> SetInfo(This)

#define IADsSyntax_Get(This,bstrName,pvProp)	\
    (This)->lpVtbl -> Get(This,bstrName,pvProp)

#define IADsSyntax_Put(This,bstrName,vProp)	\
    (This)->lpVtbl -> Put(This,bstrName,vProp)

#define IADsSyntax_GetEx(This,bstrName,pvProp)	\
    (This)->lpVtbl -> GetEx(This,bstrName,pvProp)

#define IADsSyntax_PutEx(This,lnControlCode,bstrName,vProp)	\
    (This)->lpVtbl -> PutEx(This,lnControlCode,bstrName,vProp)

#define IADsSyntax_GetInfoEx(This,vProperties,lnReserved)	\
    (This)->lpVtbl -> GetInfoEx(This,vProperties,lnReserved)


#define IADsSyntax_get_OleAutoDataType(This,retval)	\
    (This)->lpVtbl -> get_OleAutoDataType(This,retval)

#define IADsSyntax_put_OleAutoDataType(This,lnOleAutoDataType)	\
    (This)->lpVtbl -> put_OleAutoDataType(This,lnOleAutoDataType)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [id][propget] */ HRESULT STDMETHODCALLTYPE IADsSyntax_get_OleAutoDataType_Proxy( 
    IADsSyntax __RPC_FAR * This,
    /* [retval][out] */ long __RPC_FAR *retval);


void __RPC_STUB IADsSyntax_get_OleAutoDataType_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [id][propput] */ HRESULT STDMETHODCALLTYPE IADsSyntax_put_OleAutoDataType_Proxy( 
    IADsSyntax __RPC_FAR * This,
    /* [in] */ long lnOleAutoDataType);


void __RPC_STUB IADsSyntax_put_OleAutoDataType_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IADsSyntax_INTERFACE_DEFINED__ */


#ifndef __IADsLocality_INTERFACE_DEFINED__
#define __IADsLocality_INTERFACE_DEFINED__

/****************************************
 * Generated header for interface: IADsLocality
 * at Mon Oct 13 13:47:30 1997
 * using MIDL 3.00.44
 ****************************************/
/* [object][dual][oleautomation][uuid] */ 



EXTERN_C const IID IID_IADsLocality;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    interface IADsLocality : public IADs
    {
    public:
        virtual /* [id][propget] */ HRESULT STDMETHODCALLTYPE get_Description( 
            /* [retval][out] */ BSTR __RPC_FAR *retval) = 0;
        
        virtual /* [id][propput] */ HRESULT STDMETHODCALLTYPE put_Description( 
            /* [in] */ BSTR bstrDescription) = 0;
        
        virtual /* [id][propget] */ HRESULT STDMETHODCALLTYPE get_LocalityName( 
            /* [retval][out] */ BSTR __RPC_FAR *retval) = 0;
        
        virtual /* [id][propput] */ HRESULT STDMETHODCALLTYPE put_LocalityName( 
            /* [in] */ BSTR bstrLocalityName) = 0;
        
        virtual /* [id][propget] */ HRESULT STDMETHODCALLTYPE get_PostalAddress( 
            /* [retval][out] */ BSTR __RPC_FAR *retval) = 0;
        
        virtual /* [id][propput] */ HRESULT STDMETHODCALLTYPE put_PostalAddress( 
            /* [in] */ BSTR bstrPostalAddress) = 0;
        
        virtual /* [id][propget] */ HRESULT STDMETHODCALLTYPE get_SeeAlso( 
            /* [retval][out] */ VARIANT __RPC_FAR *retval) = 0;
        
        virtual /* [id][propput] */ HRESULT STDMETHODCALLTYPE put_SeeAlso( 
            /* [in] */ VARIANT vSeeAlso) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IADsLocalityVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            IADsLocality __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            IADsLocality __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            IADsLocality __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfoCount )( 
            IADsLocality __RPC_FAR * This,
            /* [out] */ UINT __RPC_FAR *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfo )( 
            IADsLocality __RPC_FAR * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo __RPC_FAR *__RPC_FAR *ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetIDsOfNames )( 
            IADsLocality __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR __RPC_FAR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID __RPC_FAR *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Invoke )( 
            IADsLocality __RPC_FAR * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS __RPC_FAR *pDispParams,
            /* [out] */ VARIANT __RPC_FAR *pVarResult,
            /* [out] */ EXCEPINFO __RPC_FAR *pExcepInfo,
            /* [out] */ UINT __RPC_FAR *puArgErr);
        
        /* [id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Name )( 
            IADsLocality __RPC_FAR * This,
            /* [retval][out] */ BSTR __RPC_FAR *retval);
        
        /* [id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Class )( 
            IADsLocality __RPC_FAR * This,
            /* [retval][out] */ BSTR __RPC_FAR *retval);
        
        /* [id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_GUID )( 
            IADsLocality __RPC_FAR * This,
            /* [retval][out] */ BSTR __RPC_FAR *retval);
        
        /* [id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_ADsPath )( 
            IADsLocality __RPC_FAR * This,
            /* [retval][out] */ BSTR __RPC_FAR *retval);
        
        /* [id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Parent )( 
            IADsLocality __RPC_FAR * This,
            /* [retval][out] */ BSTR __RPC_FAR *retval);
        
        /* [id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Schema )( 
            IADsLocality __RPC_FAR * This,
            /* [retval][out] */ BSTR __RPC_FAR *retval);
        
        /* [id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetInfo )( 
            IADsLocality __RPC_FAR * This);
        
        /* [id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *SetInfo )( 
            IADsLocality __RPC_FAR * This);
        
        /* [id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Get )( 
            IADsLocality __RPC_FAR * This,
            /* [in] */ BSTR bstrName,
            /* [retval][out] */ VARIANT __RPC_FAR *pvProp);
        
        /* [id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Put )( 
            IADsLocality __RPC_FAR * This,
            /* [in] */ BSTR bstrName,
            /* [in] */ VARIANT vProp);
        
        /* [id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetEx )( 
            IADsLocality __RPC_FAR * This,
            /* [in] */ BSTR bstrName,
            /* [retval][out] */ VARIANT __RPC_FAR *pvProp);
        
        /* [id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *PutEx )( 
            IADsLocality __RPC_FAR * This,
            /* [in] */ long lnControlCode,
            /* [in] */ BSTR bstrName,
            /* [in] */ VARIANT vProp);
        
        /* [id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetInfoEx )( 
            IADsLocality __RPC_FAR * This,
            /* [in] */ VARIANT vProperties,
            /* [in] */ long lnReserved);
        
        /* [id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Description )( 
            IADsLocality __RPC_FAR * This,
            /* [retval][out] */ BSTR __RPC_FAR *retval);
        
        /* [id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_Description )( 
            IADsLocality __RPC_FAR * This,
            /* [in] */ BSTR bstrDescription);
        
        /* [id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_LocalityName )( 
            IADsLocality __RPC_FAR * This,
            /* [retval][out] */ BSTR __RPC_FAR *retval);
        
        /* [id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_LocalityName )( 
            IADsLocality __RPC_FAR * This,
            /* [in] */ BSTR bstrLocalityName);
        
        /* [id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_PostalAddress )( 
            IADsLocality __RPC_FAR * This,
            /* [retval][out] */ BSTR __RPC_FAR *retval);
        
        /* [id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_PostalAddress )( 
            IADsLocality __RPC_FAR * This,
            /* [in] */ BSTR bstrPostalAddress);
        
        /* [id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_SeeAlso )( 
            IADsLocality __RPC_FAR * This,
            /* [retval][out] */ VARIANT __RPC_FAR *retval);
        
        /* [id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_SeeAlso )( 
            IADsLocality __RPC_FAR * This,
            /* [in] */ VARIANT vSeeAlso);
        
        END_INTERFACE
    } IADsLocalityVtbl;

    interface IADsLocality
    {
        CONST_VTBL struct IADsLocalityVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IADsLocality_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IADsLocality_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IADsLocality_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IADsLocality_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define IADsLocality_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define IADsLocality_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define IADsLocality_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)


#define IADsLocality_get_Name(This,retval)	\
    (This)->lpVtbl -> get_Name(This,retval)

#define IADsLocality_get_Class(This,retval)	\
    (This)->lpVtbl -> get_Class(This,retval)

#define IADsLocality_get_GUID(This,retval)	\
    (This)->lpVtbl -> get_GUID(This,retval)

#define IADsLocality_get_ADsPath(This,retval)	\
    (This)->lpVtbl -> get_ADsPath(This,retval)

#define IADsLocality_get_Parent(This,retval)	\
    (This)->lpVtbl -> get_Parent(This,retval)

#define IADsLocality_get_Schema(This,retval)	\
    (This)->lpVtbl -> get_Schema(This,retval)

#define IADsLocality_GetInfo(This)	\
    (This)->lpVtbl -> GetInfo(This)

#define IADsLocality_SetInfo(This)	\
    (This)->lpVtbl -> SetInfo(This)

#define IADsLocality_Get(This,bstrName,pvProp)	\
    (This)->lpVtbl -> Get(This,bstrName,pvProp)

#define IADsLocality_Put(This,bstrName,vProp)	\
    (This)->lpVtbl -> Put(This,bstrName,vProp)

#define IADsLocality_GetEx(This,bstrName,pvProp)	\
    (This)->lpVtbl -> GetEx(This,bstrName,pvProp)

#define IADsLocality_PutEx(This,lnControlCode,bstrName,vProp)	\
    (This)->lpVtbl -> PutEx(This,lnControlCode,bstrName,vProp)

#define IADsLocality_GetInfoEx(This,vProperties,lnReserved)	\
    (This)->lpVtbl -> GetInfoEx(This,vProperties,lnReserved)


#define IADsLocality_get_Description(This,retval)	\
    (This)->lpVtbl -> get_Description(This,retval)

#define IADsLocality_put_Description(This,bstrDescription)	\
    (This)->lpVtbl -> put_Description(This,bstrDescription)

#define IADsLocality_get_LocalityName(This,retval)	\
    (This)->lpVtbl -> get_LocalityName(This,retval)

#define IADsLocality_put_LocalityName(This,bstrLocalityName)	\
    (This)->lpVtbl -> put_LocalityName(This,bstrLocalityName)

#define IADsLocality_get_PostalAddress(This,retval)	\
    (This)->lpVtbl -> get_PostalAddress(This,retval)

#define IADsLocality_put_PostalAddress(This,bstrPostalAddress)	\
    (This)->lpVtbl -> put_PostalAddress(This,bstrPostalAddress)

#define IADsLocality_get_SeeAlso(This,retval)	\
    (This)->lpVtbl -> get_SeeAlso(This,retval)

#define IADsLocality_put_SeeAlso(This,vSeeAlso)	\
    (This)->lpVtbl -> put_SeeAlso(This,vSeeAlso)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [id][propget] */ HRESULT STDMETHODCALLTYPE IADsLocality_get_Description_Proxy( 
    IADsLocality __RPC_FAR * This,
    /* [retval][out] */ BSTR __RPC_FAR *retval);


void __RPC_STUB IADsLocality_get_Description_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [id][propput] */ HRESULT STDMETHODCALLTYPE IADsLocality_put_Description_Proxy( 
    IADsLocality __RPC_FAR * This,
    /* [in] */ BSTR bstrDescription);


void __RPC_STUB IADsLocality_put_Description_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [id][propget] */ HRESULT STDMETHODCALLTYPE IADsLocality_get_LocalityName_Proxy( 
    IADsLocality __RPC_FAR * This,
    /* [retval][out] */ BSTR __RPC_FAR *retval);


void __RPC_STUB IADsLocality_get_LocalityName_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [id][propput] */ HRESULT STDMETHODCALLTYPE IADsLocality_put_LocalityName_Proxy( 
    IADsLocality __RPC_FAR * This,
    /* [in] */ BSTR bstrLocalityName);


void __RPC_STUB IADsLocality_put_LocalityName_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [id][propget] */ HRESULT STDMETHODCALLTYPE IADsLocality_get_PostalAddress_Proxy( 
    IADsLocality __RPC_FAR * This,
    /* [retval][out] */ BSTR __RPC_FAR *retval);


void __RPC_STUB IADsLocality_get_PostalAddress_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [id][propput] */ HRESULT STDMETHODCALLTYPE IADsLocality_put_PostalAddress_Proxy( 
    IADsLocality __RPC_FAR * This,
    /* [in] */ BSTR bstrPostalAddress);


void __RPC_STUB IADsLocality_put_PostalAddress_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [id][propget] */ HRESULT STDMETHODCALLTYPE IADsLocality_get_SeeAlso_Proxy( 
    IADsLocality __RPC_FAR * This,
    /* [retval][out] */ VARIANT __RPC_FAR *retval);


void __RPC_STUB IADsLocality_get_SeeAlso_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [id][propput] */ HRESULT STDMETHODCALLTYPE IADsLocality_put_SeeAlso_Proxy( 
    IADsLocality __RPC_FAR * This,
    /* [in] */ VARIANT vSeeAlso);


void __RPC_STUB IADsLocality_put_SeeAlso_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IADsLocality_INTERFACE_DEFINED__ */


#ifndef __IADsO_INTERFACE_DEFINED__
#define __IADsO_INTERFACE_DEFINED__

/****************************************
 * Generated header for interface: IADsO
 * at Mon Oct 13 13:47:30 1997
 * using MIDL 3.00.44
 ****************************************/
/* [object][dual][oleautomation][uuid] */ 



EXTERN_C const IID IID_IADsO;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    interface IADsO : public IADs
    {
    public:
        virtual /* [id][propget] */ HRESULT STDMETHODCALLTYPE get_Description( 
            /* [retval][out] */ BSTR __RPC_FAR *retval) = 0;
        
        virtual /* [id][propput] */ HRESULT STDMETHODCALLTYPE put_Description( 
            /* [in] */ BSTR bstrDescription) = 0;
        
        virtual /* [id][propget] */ HRESULT STDMETHODCALLTYPE get_LocalityName( 
            /* [retval][out] */ BSTR __RPC_FAR *retval) = 0;
        
        virtual /* [id][propput] */ HRESULT STDMETHODCALLTYPE put_LocalityName( 
            /* [in] */ BSTR bstrLocalityName) = 0;
        
        virtual /* [id][propget] */ HRESULT STDMETHODCALLTYPE get_PostalAddress( 
            /* [retval][out] */ BSTR __RPC_FAR *retval) = 0;
        
        virtual /* [id][propput] */ HRESULT STDMETHODCALLTYPE put_PostalAddress( 
            /* [in] */ BSTR bstrPostalAddress) = 0;
        
        virtual /* [id][propget] */ HRESULT STDMETHODCALLTYPE get_TelephoneNumber( 
            /* [retval][out] */ BSTR __RPC_FAR *retval) = 0;
        
        virtual /* [id][propput] */ HRESULT STDMETHODCALLTYPE put_TelephoneNumber( 
            /* [in] */ BSTR bstrTelephoneNumber) = 0;
        
        virtual /* [id][propget] */ HRESULT STDMETHODCALLTYPE get_FaxNumber( 
            /* [retval][out] */ BSTR __RPC_FAR *retval) = 0;
        
        virtual /* [id][propput] */ HRESULT STDMETHODCALLTYPE put_FaxNumber( 
            /* [in] */ BSTR bstrFaxNumber) = 0;
        
        virtual /* [id][propget] */ HRESULT STDMETHODCALLTYPE get_SeeAlso( 
            /* [retval][out] */ VARIANT __RPC_FAR *retval) = 0;
        
        virtual /* [id][propput] */ HRESULT STDMETHODCALLTYPE put_SeeAlso( 
            /* [in] */ VARIANT vSeeAlso) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IADsOVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            IADsO __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            IADsO __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            IADsO __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfoCount )( 
            IADsO __RPC_FAR * This,
            /* [out] */ UINT __RPC_FAR *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfo )( 
            IADsO __RPC_FAR * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo __RPC_FAR *__RPC_FAR *ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetIDsOfNames )( 
            IADsO __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR __RPC_FAR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID __RPC_FAR *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Invoke )( 
            IADsO __RPC_FAR * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS __RPC_FAR *pDispParams,
            /* [out] */ VARIANT __RPC_FAR *pVarResult,
            /* [out] */ EXCEPINFO __RPC_FAR *pExcepInfo,
            /* [out] */ UINT __RPC_FAR *puArgErr);
        
        /* [id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Name )( 
            IADsO __RPC_FAR * This,
            /* [retval][out] */ BSTR __RPC_FAR *retval);
        
        /* [id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Class )( 
            IADsO __RPC_FAR * This,
            /* [retval][out] */ BSTR __RPC_FAR *retval);
        
        /* [id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_GUID )( 
            IADsO __RPC_FAR * This,
            /* [retval][out] */ BSTR __RPC_FAR *retval);
        
        /* [id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_ADsPath )( 
            IADsO __RPC_FAR * This,
            /* [retval][out] */ BSTR __RPC_FAR *retval);
        
        /* [id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Parent )( 
            IADsO __RPC_FAR * This,
            /* [retval][out] */ BSTR __RPC_FAR *retval);
        
        /* [id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Schema )( 
            IADsO __RPC_FAR * This,
            /* [retval][out] */ BSTR __RPC_FAR *retval);
        
        /* [id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetInfo )( 
            IADsO __RPC_FAR * This);
        
        /* [id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *SetInfo )( 
            IADsO __RPC_FAR * This);
        
        /* [id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Get )( 
            IADsO __RPC_FAR * This,
            /* [in] */ BSTR bstrName,
            /* [retval][out] */ VARIANT __RPC_FAR *pvProp);
        
        /* [id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Put )( 
            IADsO __RPC_FAR * This,
            /* [in] */ BSTR bstrName,
            /* [in] */ VARIANT vProp);
        
        /* [id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetEx )( 
            IADsO __RPC_FAR * This,
            /* [in] */ BSTR bstrName,
            /* [retval][out] */ VARIANT __RPC_FAR *pvProp);
        
        /* [id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *PutEx )( 
            IADsO __RPC_FAR * This,
            /* [in] */ long lnControlCode,
            /* [in] */ BSTR bstrName,
            /* [in] */ VARIANT vProp);
        
        /* [id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetInfoEx )( 
            IADsO __RPC_FAR * This,
            /* [in] */ VARIANT vProperties,
            /* [in] */ long lnReserved);
        
        /* [id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Description )( 
            IADsO __RPC_FAR * This,
            /* [retval][out] */ BSTR __RPC_FAR *retval);
        
        /* [id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_Description )( 
            IADsO __RPC_FAR * This,
            /* [in] */ BSTR bstrDescription);
        
        /* [id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_LocalityName )( 
            IADsO __RPC_FAR * This,
            /* [retval][out] */ BSTR __RPC_FAR *retval);
        
        /* [id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_LocalityName )( 
            IADsO __RPC_FAR * This,
            /* [in] */ BSTR bstrLocalityName);
        
        /* [id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_PostalAddress )( 
            IADsO __RPC_FAR * This,
            /* [retval][out] */ BSTR __RPC_FAR *retval);
        
        /* [id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_PostalAddress )( 
            IADsO __RPC_FAR * This,
            /* [in] */ BSTR bstrPostalAddress);
        
        /* [id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_TelephoneNumber )( 
            IADsO __RPC_FAR * This,
            /* [retval][out] */ BSTR __RPC_FAR *retval);
        
        /* [id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_TelephoneNumber )( 
            IADsO __RPC_FAR * This,
            /* [in] */ BSTR bstrTelephoneNumber);
        
        /* [id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_FaxNumber )( 
            IADsO __RPC_FAR * This,
            /* [retval][out] */ BSTR __RPC_FAR *retval);
        
        /* [id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_FaxNumber )( 
            IADsO __RPC_FAR * This,
            /* [in] */ BSTR bstrFaxNumber);
        
        /* [id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_SeeAlso )( 
            IADsO __RPC_FAR * This,
            /* [retval][out] */ VARIANT __RPC_FAR *retval);
        
        /* [id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_SeeAlso )( 
            IADsO __RPC_FAR * This,
            /* [in] */ VARIANT vSeeAlso);
        
        END_INTERFACE
    } IADsOVtbl;

    interface IADsO
    {
        CONST_VTBL struct IADsOVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IADsO_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IADsO_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IADsO_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IADsO_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define IADsO_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define IADsO_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define IADsO_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)


#define IADsO_get_Name(This,retval)	\
    (This)->lpVtbl -> get_Name(This,retval)

#define IADsO_get_Class(This,retval)	\
    (This)->lpVtbl -> get_Class(This,retval)

#define IADsO_get_GUID(This,retval)	\
    (This)->lpVtbl -> get_GUID(This,retval)

#define IADsO_get_ADsPath(This,retval)	\
    (This)->lpVtbl -> get_ADsPath(This,retval)

#define IADsO_get_Parent(This,retval)	\
    (This)->lpVtbl -> get_Parent(This,retval)

#define IADsO_get_Schema(This,retval)	\
    (This)->lpVtbl -> get_Schema(This,retval)

#define IADsO_GetInfo(This)	\
    (This)->lpVtbl -> GetInfo(This)

#define IADsO_SetInfo(This)	\
    (This)->lpVtbl -> SetInfo(This)

#define IADsO_Get(This,bstrName,pvProp)	\
    (This)->lpVtbl -> Get(This,bstrName,pvProp)

#define IADsO_Put(This,bstrName,vProp)	\
    (This)->lpVtbl -> Put(This,bstrName,vProp)

#define IADsO_GetEx(This,bstrName,pvProp)	\
    (This)->lpVtbl -> GetEx(This,bstrName,pvProp)

#define IADsO_PutEx(This,lnControlCode,bstrName,vProp)	\
    (This)->lpVtbl -> PutEx(This,lnControlCode,bstrName,vProp)

#define IADsO_GetInfoEx(This,vProperties,lnReserved)	\
    (This)->lpVtbl -> GetInfoEx(This,vProperties,lnReserved)


#define IADsO_get_Description(This,retval)	\
    (This)->lpVtbl -> get_Description(This,retval)

#define IADsO_put_Description(This,bstrDescription)	\
    (This)->lpVtbl -> put_Description(This,bstrDescription)

#define IADsO_get_LocalityName(This,retval)	\
    (This)->lpVtbl -> get_LocalityName(This,retval)

#define IADsO_put_LocalityName(This,bstrLocalityName)	\
    (This)->lpVtbl -> put_LocalityName(This,bstrLocalityName)

#define IADsO_get_PostalAddress(This,retval)	\
    (This)->lpVtbl -> get_PostalAddress(This,retval)

#define IADsO_put_PostalAddress(This,bstrPostalAddress)	\
    (This)->lpVtbl -> put_PostalAddress(This,bstrPostalAddress)

#define IADsO_get_TelephoneNumber(This,retval)	\
    (This)->lpVtbl -> get_TelephoneNumber(This,retval)

#define IADsO_put_TelephoneNumber(This,bstrTelephoneNumber)	\
    (This)->lpVtbl -> put_TelephoneNumber(This,bstrTelephoneNumber)

#define IADsO_get_FaxNumber(This,retval)	\
    (This)->lpVtbl -> get_FaxNumber(This,retval)

#define IADsO_put_FaxNumber(This,bstrFaxNumber)	\
    (This)->lpVtbl -> put_FaxNumber(This,bstrFaxNumber)

#define IADsO_get_SeeAlso(This,retval)	\
    (This)->lpVtbl -> get_SeeAlso(This,retval)

#define IADsO_put_SeeAlso(This,vSeeAlso)	\
    (This)->lpVtbl -> put_SeeAlso(This,vSeeAlso)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [id][propget] */ HRESULT STDMETHODCALLTYPE IADsO_get_Description_Proxy( 
    IADsO __RPC_FAR * This,
    /* [retval][out] */ BSTR __RPC_FAR *retval);


void __RPC_STUB IADsO_get_Description_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [id][propput] */ HRESULT STDMETHODCALLTYPE IADsO_put_Description_Proxy( 
    IADsO __RPC_FAR * This,
    /* [in] */ BSTR bstrDescription);


void __RPC_STUB IADsO_put_Description_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [id][propget] */ HRESULT STDMETHODCALLTYPE IADsO_get_LocalityName_Proxy( 
    IADsO __RPC_FAR * This,
    /* [retval][out] */ BSTR __RPC_FAR *retval);


void __RPC_STUB IADsO_get_LocalityName_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [id][propput] */ HRESULT STDMETHODCALLTYPE IADsO_put_LocalityName_Proxy( 
    IADsO __RPC_FAR * This,
    /* [in] */ BSTR bstrLocalityName);


void __RPC_STUB IADsO_put_LocalityName_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [id][propget] */ HRESULT STDMETHODCALLTYPE IADsO_get_PostalAddress_Proxy( 
    IADsO __RPC_FAR * This,
    /* [retval][out] */ BSTR __RPC_FAR *retval);


void __RPC_STUB IADsO_get_PostalAddress_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [id][propput] */ HRESULT STDMETHODCALLTYPE IADsO_put_PostalAddress_Proxy( 
    IADsO __RPC_FAR * This,
    /* [in] */ BSTR bstrPostalAddress);


void __RPC_STUB IADsO_put_PostalAddress_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [id][propget] */ HRESULT STDMETHODCALLTYPE IADsO_get_TelephoneNumber_Proxy( 
    IADsO __RPC_FAR * This,
    /* [retval][out] */ BSTR __RPC_FAR *retval);


void __RPC_STUB IADsO_get_TelephoneNumber_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [id][propput] */ HRESULT STDMETHODCALLTYPE IADsO_put_TelephoneNumber_Proxy( 
    IADsO __RPC_FAR * This,
    /* [in] */ BSTR bstrTelephoneNumber);


void __RPC_STUB IADsO_put_TelephoneNumber_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [id][propget] */ HRESULT STDMETHODCALLTYPE IADsO_get_FaxNumber_Proxy( 
    IADsO __RPC_FAR * This,
    /* [retval][out] */ BSTR __RPC_FAR *retval);


void __RPC_STUB IADsO_get_FaxNumber_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [id][propput] */ HRESULT STDMETHODCALLTYPE IADsO_put_FaxNumber_Proxy( 
    IADsO __RPC_FAR * This,
    /* [in] */ BSTR bstrFaxNumber);


void __RPC_STUB IADsO_put_FaxNumber_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [id][propget] */ HRESULT STDMETHODCALLTYPE IADsO_get_SeeAlso_Proxy( 
    IADsO __RPC_FAR * This,
    /* [retval][out] */ VARIANT __RPC_FAR *retval);


void __RPC_STUB IADsO_get_SeeAlso_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [id][propput] */ HRESULT STDMETHODCALLTYPE IADsO_put_SeeAlso_Proxy( 
    IADsO __RPC_FAR * This,
    /* [in] */ VARIANT vSeeAlso);


void __RPC_STUB IADsO_put_SeeAlso_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IADsO_INTERFACE_DEFINED__ */


#ifndef __IADsOU_INTERFACE_DEFINED__
#define __IADsOU_INTERFACE_DEFINED__

/****************************************
 * Generated header for interface: IADsOU
 * at Mon Oct 13 13:47:30 1997
 * using MIDL 3.00.44
 ****************************************/
/* [object][dual][oleautomation][uuid] */ 



EXTERN_C const IID IID_IADsOU;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    interface IADsOU : public IADs
    {
    public:
        virtual /* [id][propget] */ HRESULT STDMETHODCALLTYPE get_Description( 
            /* [retval][out] */ BSTR __RPC_FAR *retval) = 0;
        
        virtual /* [id][propput] */ HRESULT STDMETHODCALLTYPE put_Description( 
            /* [in] */ BSTR bstrDescription) = 0;
        
        virtual /* [id][propget] */ HRESULT STDMETHODCALLTYPE get_LocalityName( 
            /* [retval][out] */ BSTR __RPC_FAR *retval) = 0;
        
        virtual /* [id][propput] */ HRESULT STDMETHODCALLTYPE put_LocalityName( 
            /* [in] */ BSTR bstrLocalityName) = 0;
        
        virtual /* [id][propget] */ HRESULT STDMETHODCALLTYPE get_PostalAddress( 
            /* [retval][out] */ BSTR __RPC_FAR *retval) = 0;
        
        virtual /* [id][propput] */ HRESULT STDMETHODCALLTYPE put_PostalAddress( 
            /* [in] */ BSTR bstrPostalAddress) = 0;
        
        virtual /* [id][propget] */ HRESULT STDMETHODCALLTYPE get_TelephoneNumber( 
            /* [retval][out] */ BSTR __RPC_FAR *retval) = 0;
        
        virtual /* [id][propput] */ HRESULT STDMETHODCALLTYPE put_TelephoneNumber( 
            /* [in] */ BSTR bstrTelephoneNumber) = 0;
        
        virtual /* [id][propget] */ HRESULT STDMETHODCALLTYPE get_FaxNumber( 
            /* [retval][out] */ BSTR __RPC_FAR *retval) = 0;
        
        virtual /* [id][propput] */ HRESULT STDMETHODCALLTYPE put_FaxNumber( 
            /* [in] */ BSTR bstrFaxNumber) = 0;
        
        virtual /* [id][propget] */ HRESULT STDMETHODCALLTYPE get_SeeAlso( 
            /* [retval][out] */ VARIANT __RPC_FAR *retval) = 0;
        
        virtual /* [id][propput] */ HRESULT STDMETHODCALLTYPE put_SeeAlso( 
            /* [in] */ VARIANT vSeeAlso) = 0;
        
        virtual /* [id][propget] */ HRESULT STDMETHODCALLTYPE get_BusinessCategory( 
            /* [retval][out] */ BSTR __RPC_FAR *retval) = 0;
        
        virtual /* [id][propput] */ HRESULT STDMETHODCALLTYPE put_BusinessCategory( 
            /* [in] */ BSTR bstrBusinessCategory) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IADsOUVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            IADsOU __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            IADsOU __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            IADsOU __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfoCount )( 
            IADsOU __RPC_FAR * This,
            /* [out] */ UINT __RPC_FAR *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfo )( 
            IADsOU __RPC_FAR * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo __RPC_FAR *__RPC_FAR *ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetIDsOfNames )( 
            IADsOU __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR __RPC_FAR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID __RPC_FAR *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Invoke )( 
            IADsOU __RPC_FAR * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS __RPC_FAR *pDispParams,
            /* [out] */ VARIANT __RPC_FAR *pVarResult,
            /* [out] */ EXCEPINFO __RPC_FAR *pExcepInfo,
            /* [out] */ UINT __RPC_FAR *puArgErr);
        
        /* [id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Name )( 
            IADsOU __RPC_FAR * This,
            /* [retval][out] */ BSTR __RPC_FAR *retval);
        
        /* [id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Class )( 
            IADsOU __RPC_FAR * This,
            /* [retval][out] */ BSTR __RPC_FAR *retval);
        
        /* [id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_GUID )( 
            IADsOU __RPC_FAR * This,
            /* [retval][out] */ BSTR __RPC_FAR *retval);
        
        /* [id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_ADsPath )( 
            IADsOU __RPC_FAR * This,
            /* [retval][out] */ BSTR __RPC_FAR *retval);
        
        /* [id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Parent )( 
            IADsOU __RPC_FAR * This,
            /* [retval][out] */ BSTR __RPC_FAR *retval);
        
        /* [id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Schema )( 
            IADsOU __RPC_FAR * This,
            /* [retval][out] */ BSTR __RPC_FAR *retval);
        
        /* [id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetInfo )( 
            IADsOU __RPC_FAR * This);
        
        /* [id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *SetInfo )( 
            IADsOU __RPC_FAR * This);
        
        /* [id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Get )( 
            IADsOU __RPC_FAR * This,
            /* [in] */ BSTR bstrName,
            /* [retval][out] */ VARIANT __RPC_FAR *pvProp);
        
        /* [id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Put )( 
            IADsOU __RPC_FAR * This,
            /* [in] */ BSTR bstrName,
            /* [in] */ VARIANT vProp);
        
        /* [id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetEx )( 
            IADsOU __RPC_FAR * This,
            /* [in] */ BSTR bstrName,
            /* [retval][out] */ VARIANT __RPC_FAR *pvProp);
        
        /* [id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *PutEx )( 
            IADsOU __RPC_FAR * This,
            /* [in] */ long lnControlCode,
            /* [in] */ BSTR bstrName,
            /* [in] */ VARIANT vProp);
        
        /* [id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetInfoEx )( 
            IADsOU __RPC_FAR * This,
            /* [in] */ VARIANT vProperties,
            /* [in] */ long lnReserved);
        
        /* [id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Description )( 
            IADsOU __RPC_FAR * This,
            /* [retval][out] */ BSTR __RPC_FAR *retval);
        
        /* [id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_Description )( 
            IADsOU __RPC_FAR * This,
            /* [in] */ BSTR bstrDescription);
        
        /* [id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_LocalityName )( 
            IADsOU __RPC_FAR * This,
            /* [retval][out] */ BSTR __RPC_FAR *retval);
        
        /* [id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_LocalityName )( 
            IADsOU __RPC_FAR * This,
            /* [in] */ BSTR bstrLocalityName);
        
        /* [id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_PostalAddress )( 
            IADsOU __RPC_FAR * This,
            /* [retval][out] */ BSTR __RPC_FAR *retval);
        
        /* [id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_PostalAddress )( 
            IADsOU __RPC_FAR * This,
            /* [in] */ BSTR bstrPostalAddress);
        
        /* [id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_TelephoneNumber )( 
            IADsOU __RPC_FAR * This,
            /* [retval][out] */ BSTR __RPC_FAR *retval);
        
        /* [id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_TelephoneNumber )( 
            IADsOU __RPC_FAR * This,
            /* [in] */ BSTR bstrTelephoneNumber);
        
        /* [id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_FaxNumber )( 
            IADsOU __RPC_FAR * This,
            /* [retval][out] */ BSTR __RPC_FAR *retval);
        
        /* [id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_FaxNumber )( 
            IADsOU __RPC_FAR * This,
            /* [in] */ BSTR bstrFaxNumber);
        
        /* [id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_SeeAlso )( 
            IADsOU __RPC_FAR * This,
            /* [retval][out] */ VARIANT __RPC_FAR *retval);
        
        /* [id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_SeeAlso )( 
            IADsOU __RPC_FAR * This,
            /* [in] */ VARIANT vSeeAlso);
        
        /* [id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_BusinessCategory )( 
            IADsOU __RPC_FAR * This,
            /* [retval][out] */ BSTR __RPC_FAR *retval);
        
        /* [id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_BusinessCategory )( 
            IADsOU __RPC_FAR * This,
            /* [in] */ BSTR bstrBusinessCategory);
        
        END_INTERFACE
    } IADsOUVtbl;

    interface IADsOU
    {
        CONST_VTBL struct IADsOUVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IADsOU_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IADsOU_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IADsOU_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IADsOU_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define IADsOU_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define IADsOU_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define IADsOU_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)


#define IADsOU_get_Name(This,retval)	\
    (This)->lpVtbl -> get_Name(This,retval)

#define IADsOU_get_Class(This,retval)	\
    (This)->lpVtbl -> get_Class(This,retval)

#define IADsOU_get_GUID(This,retval)	\
    (This)->lpVtbl -> get_GUID(This,retval)

#define IADsOU_get_ADsPath(This,retval)	\
    (This)->lpVtbl -> get_ADsPath(This,retval)

#define IADsOU_get_Parent(This,retval)	\
    (This)->lpVtbl -> get_Parent(This,retval)

#define IADsOU_get_Schema(This,retval)	\
    (This)->lpVtbl -> get_Schema(This,retval)

#define IADsOU_GetInfo(This)	\
    (This)->lpVtbl -> GetInfo(This)

#define IADsOU_SetInfo(This)	\
    (This)->lpVtbl -> SetInfo(This)

#define IADsOU_Get(This,bstrName,pvProp)	\
    (This)->lpVtbl -> Get(This,bstrName,pvProp)

#define IADsOU_Put(This,bstrName,vProp)	\
    (This)->lpVtbl -> Put(This,bstrName,vProp)

#define IADsOU_GetEx(This,bstrName,pvProp)	\
    (This)->lpVtbl -> GetEx(This,bstrName,pvProp)

#define IADsOU_PutEx(This,lnControlCode,bstrName,vProp)	\
    (This)->lpVtbl -> PutEx(This,lnControlCode,bstrName,vProp)

#define IADsOU_GetInfoEx(This,vProperties,lnReserved)	\
    (This)->lpVtbl -> GetInfoEx(This,vProperties,lnReserved)


#define IADsOU_get_Description(This,retval)	\
    (This)->lpVtbl -> get_Description(This,retval)

#define IADsOU_put_Description(This,bstrDescription)	\
    (This)->lpVtbl -> put_Description(This,bstrDescription)

#define IADsOU_get_LocalityName(This,retval)	\
    (This)->lpVtbl -> get_LocalityName(This,retval)

#define IADsOU_put_LocalityName(This,bstrLocalityName)	\
    (This)->lpVtbl -> put_LocalityName(This,bstrLocalityName)

#define IADsOU_get_PostalAddress(This,retval)	\
    (This)->lpVtbl -> get_PostalAddress(This,retval)

#define IADsOU_put_PostalAddress(This,bstrPostalAddress)	\
    (This)->lpVtbl -> put_PostalAddress(This,bstrPostalAddress)

#define IADsOU_get_TelephoneNumber(This,retval)	\
    (This)->lpVtbl -> get_TelephoneNumber(This,retval)

#define IADsOU_put_TelephoneNumber(This,bstrTelephoneNumber)	\
    (This)->lpVtbl -> put_TelephoneNumber(This,bstrTelephoneNumber)

#define IADsOU_get_FaxNumber(This,retval)	\
    (This)->lpVtbl -> get_FaxNumber(This,retval)

#define IADsOU_put_FaxNumber(This,bstrFaxNumber)	\
    (This)->lpVtbl -> put_FaxNumber(This,bstrFaxNumber)

#define IADsOU_get_SeeAlso(This,retval)	\
    (This)->lpVtbl -> get_SeeAlso(This,retval)

#define IADsOU_put_SeeAlso(This,vSeeAlso)	\
    (This)->lpVtbl -> put_SeeAlso(This,vSeeAlso)

#define IADsOU_get_BusinessCategory(This,retval)	\
    (This)->lpVtbl -> get_BusinessCategory(This,retval)

#define IADsOU_put_BusinessCategory(This,bstrBusinessCategory)	\
    (This)->lpVtbl -> put_BusinessCategory(This,bstrBusinessCategory)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [id][propget] */ HRESULT STDMETHODCALLTYPE IADsOU_get_Description_Proxy( 
    IADsOU __RPC_FAR * This,
    /* [retval][out] */ BSTR __RPC_FAR *retval);


void __RPC_STUB IADsOU_get_Description_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [id][propput] */ HRESULT STDMETHODCALLTYPE IADsOU_put_Description_Proxy( 
    IADsOU __RPC_FAR * This,
    /* [in] */ BSTR bstrDescription);


void __RPC_STUB IADsOU_put_Description_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [id][propget] */ HRESULT STDMETHODCALLTYPE IADsOU_get_LocalityName_Proxy( 
    IADsOU __RPC_FAR * This,
    /* [retval][out] */ BSTR __RPC_FAR *retval);


void __RPC_STUB IADsOU_get_LocalityName_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [id][propput] */ HRESULT STDMETHODCALLTYPE IADsOU_put_LocalityName_Proxy( 
    IADsOU __RPC_FAR * This,
    /* [in] */ BSTR bstrLocalityName);


void __RPC_STUB IADsOU_put_LocalityName_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [id][propget] */ HRESULT STDMETHODCALLTYPE IADsOU_get_PostalAddress_Proxy( 
    IADsOU __RPC_FAR * This,
    /* [retval][out] */ BSTR __RPC_FAR *retval);


void __RPC_STUB IADsOU_get_PostalAddress_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [id][propput] */ HRESULT STDMETHODCALLTYPE IADsOU_put_PostalAddress_Proxy( 
    IADsOU __RPC_FAR * This,
    /* [in] */ BSTR bstrPostalAddress);


void __RPC_STUB IADsOU_put_PostalAddress_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [id][propget] */ HRESULT STDMETHODCALLTYPE IADsOU_get_TelephoneNumber_Proxy( 
    IADsOU __RPC_FAR * This,
    /* [retval][out] */ BSTR __RPC_FAR *retval);


void __RPC_STUB IADsOU_get_TelephoneNumber_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [id][propput] */ HRESULT STDMETHODCALLTYPE IADsOU_put_TelephoneNumber_Proxy( 
    IADsOU __RPC_FAR * This,
    /* [in] */ BSTR bstrTelephoneNumber);


void __RPC_STUB IADsOU_put_TelephoneNumber_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [id][propget] */ HRESULT STDMETHODCALLTYPE IADsOU_get_FaxNumber_Proxy( 
    IADsOU __RPC_FAR * This,
    /* [retval][out] */ BSTR __RPC_FAR *retval);


void __RPC_STUB IADsOU_get_FaxNumber_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [id][propput] */ HRESULT STDMETHODCALLTYPE IADsOU_put_FaxNumber_Proxy( 
    IADsOU __RPC_FAR * This,
    /* [in] */ BSTR bstrFaxNumber);


void __RPC_STUB IADsOU_put_FaxNumber_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [id][propget] */ HRESULT STDMETHODCALLTYPE IADsOU_get_SeeAlso_Proxy( 
    IADsOU __RPC_FAR * This,
    /* [retval][out] */ VARIANT __RPC_FAR *retval);


void __RPC_STUB IADsOU_get_SeeAlso_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [id][propput] */ HRESULT STDMETHODCALLTYPE IADsOU_put_SeeAlso_Proxy( 
    IADsOU __RPC_FAR * This,
    /* [in] */ VARIANT vSeeAlso);


void __RPC_STUB IADsOU_put_SeeAlso_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [id][propget] */ HRESULT STDMETHODCALLTYPE IADsOU_get_BusinessCategory_Proxy( 
    IADsOU __RPC_FAR * This,
    /* [retval][out] */ BSTR __RPC_FAR *retval);


void __RPC_STUB IADsOU_get_BusinessCategory_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [id][propput] */ HRESULT STDMETHODCALLTYPE IADsOU_put_BusinessCategory_Proxy( 
    IADsOU __RPC_FAR * This,
    /* [in] */ BSTR bstrBusinessCategory);


void __RPC_STUB IADsOU_put_BusinessCategory_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IADsOU_INTERFACE_DEFINED__ */


#ifndef __IADsDomain_INTERFACE_DEFINED__
#define __IADsDomain_INTERFACE_DEFINED__

/****************************************
 * Generated header for interface: IADsDomain
 * at Mon Oct 13 13:47:30 1997
 * using MIDL 3.00.44
 ****************************************/
/* [object][oleautomation][dual][uuid] */ 



EXTERN_C const IID IID_IADsDomain;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    interface IADsDomain : public IADs
    {
    public:
        virtual /* [id][propget] */ HRESULT STDMETHODCALLTYPE get_IsWorkgroup( 
            /* [retval][out] */ VARIANT_BOOL __RPC_FAR *retval) = 0;
        
        virtual /* [id][propget] */ HRESULT STDMETHODCALLTYPE get_MinPasswordLength( 
            /* [retval][out] */ long __RPC_FAR *retval) = 0;
        
        virtual /* [id][propput] */ HRESULT STDMETHODCALLTYPE put_MinPasswordLength( 
            /* [in] */ long lnMinPasswordLength) = 0;
        
        virtual /* [id][propget] */ HRESULT STDMETHODCALLTYPE get_MinPasswordAge( 
            /* [retval][out] */ long __RPC_FAR *retval) = 0;
        
        virtual /* [id][propput] */ HRESULT STDMETHODCALLTYPE put_MinPasswordAge( 
            /* [in] */ long lnMinPasswordAge) = 0;
        
        virtual /* [id][propget] */ HRESULT STDMETHODCALLTYPE get_MaxPasswordAge( 
            /* [retval][out] */ long __RPC_FAR *retval) = 0;
        
        virtual /* [id][propput] */ HRESULT STDMETHODCALLTYPE put_MaxPasswordAge( 
            /* [in] */ long lnMaxPasswordAge) = 0;
        
        virtual /* [id][propget] */ HRESULT STDMETHODCALLTYPE get_MaxBadPasswordsAllowed( 
            /* [retval][out] */ long __RPC_FAR *retval) = 0;
        
        virtual /* [id][propput] */ HRESULT STDMETHODCALLTYPE put_MaxBadPasswordsAllowed( 
            /* [in] */ long lnMaxBadPasswordsAllowed) = 0;
        
        virtual /* [id][propget] */ HRESULT STDMETHODCALLTYPE get_PasswordHistoryLength( 
            /* [retval][out] */ long __RPC_FAR *retval) = 0;
        
        virtual /* [id][propput] */ HRESULT STDMETHODCALLTYPE put_PasswordHistoryLength( 
            /* [in] */ long lnPasswordHistoryLength) = 0;
        
        virtual /* [id][propget] */ HRESULT STDMETHODCALLTYPE get_PasswordAttributes( 
            /* [retval][out] */ long __RPC_FAR *retval) = 0;
        
        virtual /* [id][propput] */ HRESULT STDMETHODCALLTYPE put_PasswordAttributes( 
            /* [in] */ long lnPasswordAttributes) = 0;
        
        virtual /* [id][propget] */ HRESULT STDMETHODCALLTYPE get_AutoUnlockInterval( 
            /* [retval][out] */ long __RPC_FAR *retval) = 0;
        
        virtual /* [id][propput] */ HRESULT STDMETHODCALLTYPE put_AutoUnlockInterval( 
            /* [in] */ long lnAutoUnlockInterval) = 0;
        
        virtual /* [id][propget] */ HRESULT STDMETHODCALLTYPE get_LockoutObservationInterval( 
            /* [retval][out] */ long __RPC_FAR *retval) = 0;
        
        virtual /* [id][propput] */ HRESULT STDMETHODCALLTYPE put_LockoutObservationInterval( 
            /* [in] */ long lnLockoutObservationInterval) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IADsDomainVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            IADsDomain __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            IADsDomain __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            IADsDomain __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfoCount )( 
            IADsDomain __RPC_FAR * This,
            /* [out] */ UINT __RPC_FAR *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfo )( 
            IADsDomain __RPC_FAR * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo __RPC_FAR *__RPC_FAR *ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetIDsOfNames )( 
            IADsDomain __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR __RPC_FAR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID __RPC_FAR *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Invoke )( 
            IADsDomain __RPC_FAR * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS __RPC_FAR *pDispParams,
            /* [out] */ VARIANT __RPC_FAR *pVarResult,
            /* [out] */ EXCEPINFO __RPC_FAR *pExcepInfo,
            /* [out] */ UINT __RPC_FAR *puArgErr);
        
        /* [id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Name )( 
            IADsDomain __RPC_FAR * This,
            /* [retval][out] */ BSTR __RPC_FAR *retval);
        
        /* [id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Class )( 
            IADsDomain __RPC_FAR * This,
            /* [retval][out] */ BSTR __RPC_FAR *retval);
        
        /* [id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_GUID )( 
            IADsDomain __RPC_FAR * This,
            /* [retval][out] */ BSTR __RPC_FAR *retval);
        
        /* [id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_ADsPath )( 
            IADsDomain __RPC_FAR * This,
            /* [retval][out] */ BSTR __RPC_FAR *retval);
        
        /* [id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Parent )( 
            IADsDomain __RPC_FAR * This,
            /* [retval][out] */ BSTR __RPC_FAR *retval);
        
        /* [id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Schema )( 
            IADsDomain __RPC_FAR * This,
            /* [retval][out] */ BSTR __RPC_FAR *retval);
        
        /* [id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetInfo )( 
            IADsDomain __RPC_FAR * This);
        
        /* [id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *SetInfo )( 
            IADsDomain __RPC_FAR * This);
        
        /* [id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Get )( 
            IADsDomain __RPC_FAR * This,
            /* [in] */ BSTR bstrName,
            /* [retval][out] */ VARIANT __RPC_FAR *pvProp);
        
        /* [id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Put )( 
            IADsDomain __RPC_FAR * This,
            /* [in] */ BSTR bstrName,
            /* [in] */ VARIANT vProp);
        
        /* [id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetEx )( 
            IADsDomain __RPC_FAR * This,
            /* [in] */ BSTR bstrName,
            /* [retval][out] */ VARIANT __RPC_FAR *pvProp);
        
        /* [id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *PutEx )( 
            IADsDomain __RPC_FAR * This,
            /* [in] */ long lnControlCode,
            /* [in] */ BSTR bstrName,
            /* [in] */ VARIANT vProp);
        
        /* [id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetInfoEx )( 
            IADsDomain __RPC_FAR * This,
            /* [in] */ VARIANT vProperties,
            /* [in] */ long lnReserved);
        
        /* [id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_IsWorkgroup )( 
            IADsDomain __RPC_FAR * This,
            /* [retval][out] */ VARIANT_BOOL __RPC_FAR *retval);
        
        /* [id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_MinPasswordLength )( 
            IADsDomain __RPC_FAR * This,
            /* [retval][out] */ long __RPC_FAR *retval);
        
        /* [id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_MinPasswordLength )( 
            IADsDomain __RPC_FAR * This,
            /* [in] */ long lnMinPasswordLength);
        
        /* [id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_MinPasswordAge )( 
            IADsDomain __RPC_FAR * This,
            /* [retval][out] */ long __RPC_FAR *retval);
        
        /* [id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_MinPasswordAge )( 
            IADsDomain __RPC_FAR * This,
            /* [in] */ long lnMinPasswordAge);
        
        /* [id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_MaxPasswordAge )( 
            IADsDomain __RPC_FAR * This,
            /* [retval][out] */ long __RPC_FAR *retval);
        
        /* [id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_MaxPasswordAge )( 
            IADsDomain __RPC_FAR * This,
            /* [in] */ long lnMaxPasswordAge);
        
        /* [id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_MaxBadPasswordsAllowed )( 
            IADsDomain __RPC_FAR * This,
            /* [retval][out] */ long __RPC_FAR *retval);
        
        /* [id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_MaxBadPasswordsAllowed )( 
            IADsDomain __RPC_FAR * This,
            /* [in] */ long lnMaxBadPasswordsAllowed);
        
        /* [id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_PasswordHistoryLength )( 
            IADsDomain __RPC_FAR * This,
            /* [retval][out] */ long __RPC_FAR *retval);
        
        /* [id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_PasswordHistoryLength )( 
            IADsDomain __RPC_FAR * This,
            /* [in] */ long lnPasswordHistoryLength);
        
        /* [id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_PasswordAttributes )( 
            IADsDomain __RPC_FAR * This,
            /* [retval][out] */ long __RPC_FAR *retval);
        
        /* [id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_PasswordAttributes )( 
            IADsDomain __RPC_FAR * This,
            /* [in] */ long lnPasswordAttributes);
        
        /* [id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_AutoUnlockInterval )( 
            IADsDomain __RPC_FAR * This,
            /* [retval][out] */ long __RPC_FAR *retval);
        
        /* [id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_AutoUnlockInterval )( 
            IADsDomain __RPC_FAR * This,
            /* [in] */ long lnAutoUnlockInterval);
        
        /* [id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_LockoutObservationInterval )( 
            IADsDomain __RPC_FAR * This,
            /* [retval][out] */ long __RPC_FAR *retval);
        
        /* [id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_LockoutObservationInterval )( 
            IADsDomain __RPC_FAR * This,
            /* [in] */ long lnLockoutObservationInterval);
        
        END_INTERFACE
    } IADsDomainVtbl;

    interface IADsDomain
    {
        CONST_VTBL struct IADsDomainVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IADsDomain_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IADsDomain_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IADsDomain_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IADsDomain_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define IADsDomain_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define IADsDomain_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define IADsDomain_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)


#define IADsDomain_get_Name(This,retval)	\
    (This)->lpVtbl -> get_Name(This,retval)

#define IADsDomain_get_Class(This,retval)	\
    (This)->lpVtbl -> get_Class(This,retval)

#define IADsDomain_get_GUID(This,retval)	\
    (This)->lpVtbl -> get_GUID(This,retval)

#define IADsDomain_get_ADsPath(This,retval)	\
    (This)->lpVtbl -> get_ADsPath(This,retval)

#define IADsDomain_get_Parent(This,retval)	\
    (This)->lpVtbl -> get_Parent(This,retval)

#define IADsDomain_get_Schema(This,retval)	\
    (This)->lpVtbl -> get_Schema(This,retval)

#define IADsDomain_GetInfo(This)	\
    (This)->lpVtbl -> GetInfo(This)

#define IADsDomain_SetInfo(This)	\
    (This)->lpVtbl -> SetInfo(This)

#define IADsDomain_Get(This,bstrName,pvProp)	\
    (This)->lpVtbl -> Get(This,bstrName,pvProp)

#define IADsDomain_Put(This,bstrName,vProp)	\
    (This)->lpVtbl -> Put(This,bstrName,vProp)

#define IADsDomain_GetEx(This,bstrName,pvProp)	\
    (This)->lpVtbl -> GetEx(This,bstrName,pvProp)

#define IADsDomain_PutEx(This,lnControlCode,bstrName,vProp)	\
    (This)->lpVtbl -> PutEx(This,lnControlCode,bstrName,vProp)

#define IADsDomain_GetInfoEx(This,vProperties,lnReserved)	\
    (This)->lpVtbl -> GetInfoEx(This,vProperties,lnReserved)


#define IADsDomain_get_IsWorkgroup(This,retval)	\
    (This)->lpVtbl -> get_IsWorkgroup(This,retval)

#define IADsDomain_get_MinPasswordLength(This,retval)	\
    (This)->lpVtbl -> get_MinPasswordLength(This,retval)

#define IADsDomain_put_MinPasswordLength(This,lnMinPasswordLength)	\
    (This)->lpVtbl -> put_MinPasswordLength(This,lnMinPasswordLength)

#define IADsDomain_get_MinPasswordAge(This,retval)	\
    (This)->lpVtbl -> get_MinPasswordAge(This,retval)

#define IADsDomain_put_MinPasswordAge(This,lnMinPasswordAge)	\
    (This)->lpVtbl -> put_MinPasswordAge(This,lnMinPasswordAge)

#define IADsDomain_get_MaxPasswordAge(This,retval)	\
    (This)->lpVtbl -> get_MaxPasswordAge(This,retval)

#define IADsDomain_put_MaxPasswordAge(This,lnMaxPasswordAge)	\
    (This)->lpVtbl -> put_MaxPasswordAge(This,lnMaxPasswordAge)

#define IADsDomain_get_MaxBadPasswordsAllowed(This,retval)	\
    (This)->lpVtbl -> get_MaxBadPasswordsAllowed(This,retval)

#define IADsDomain_put_MaxBadPasswordsAllowed(This,lnMaxBadPasswordsAllowed)	\
    (This)->lpVtbl -> put_MaxBadPasswordsAllowed(This,lnMaxBadPasswordsAllowed)

#define IADsDomain_get_PasswordHistoryLength(This,retval)	\
    (This)->lpVtbl -> get_PasswordHistoryLength(This,retval)

#define IADsDomain_put_PasswordHistoryLength(This,lnPasswordHistoryLength)	\
    (This)->lpVtbl -> put_PasswordHistoryLength(This,lnPasswordHistoryLength)

#define IADsDomain_get_PasswordAttributes(This,retval)	\
    (This)->lpVtbl -> get_PasswordAttributes(This,retval)

#define IADsDomain_put_PasswordAttributes(This,lnPasswordAttributes)	\
    (This)->lpVtbl -> put_PasswordAttributes(This,lnPasswordAttributes)

#define IADsDomain_get_AutoUnlockInterval(This,retval)	\
    (This)->lpVtbl -> get_AutoUnlockInterval(This,retval)

#define IADsDomain_put_AutoUnlockInterval(This,lnAutoUnlockInterval)	\
    (This)->lpVtbl -> put_AutoUnlockInterval(This,lnAutoUnlockInterval)

#define IADsDomain_get_LockoutObservationInterval(This,retval)	\
    (This)->lpVtbl -> get_LockoutObservationInterval(This,retval)

#define IADsDomain_put_LockoutObservationInterval(This,lnLockoutObservationInterval)	\
    (This)->lpVtbl -> put_LockoutObservationInterval(This,lnLockoutObservationInterval)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [id][propget] */ HRESULT STDMETHODCALLTYPE IADsDomain_get_IsWorkgroup_Proxy( 
    IADsDomain __RPC_FAR * This,
    /* [retval][out] */ VARIANT_BOOL __RPC_FAR *retval);


void __RPC_STUB IADsDomain_get_IsWorkgroup_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [id][propget] */ HRESULT STDMETHODCALLTYPE IADsDomain_get_MinPasswordLength_Proxy( 
    IADsDomain __RPC_FAR * This,
    /* [retval][out] */ long __RPC_FAR *retval);


void __RPC_STUB IADsDomain_get_MinPasswordLength_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [id][propput] */ HRESULT STDMETHODCALLTYPE IADsDomain_put_MinPasswordLength_Proxy( 
    IADsDomain __RPC_FAR * This,
    /* [in] */ long lnMinPasswordLength);


void __RPC_STUB IADsDomain_put_MinPasswordLength_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [id][propget] */ HRESULT STDMETHODCALLTYPE IADsDomain_get_MinPasswordAge_Proxy( 
    IADsDomain __RPC_FAR * This,
    /* [retval][out] */ long __RPC_FAR *retval);


void __RPC_STUB IADsDomain_get_MinPasswordAge_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [id][propput] */ HRESULT STDMETHODCALLTYPE IADsDomain_put_MinPasswordAge_Proxy( 
    IADsDomain __RPC_FAR * This,
    /* [in] */ long lnMinPasswordAge);


void __RPC_STUB IADsDomain_put_MinPasswordAge_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [id][propget] */ HRESULT STDMETHODCALLTYPE IADsDomain_get_MaxPasswordAge_Proxy( 
    IADsDomain __RPC_FAR * This,
    /* [retval][out] */ long __RPC_FAR *retval);


void __RPC_STUB IADsDomain_get_MaxPasswordAge_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [id][propput] */ HRESULT STDMETHODCALLTYPE IADsDomain_put_MaxPasswordAge_Proxy( 
    IADsDomain __RPC_FAR * This,
    /* [in] */ long lnMaxPasswordAge);


void __RPC_STUB IADsDomain_put_MaxPasswordAge_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [id][propget] */ HRESULT STDMETHODCALLTYPE IADsDomain_get_MaxBadPasswordsAllowed_Proxy( 
    IADsDomain __RPC_FAR * This,
    /* [retval][out] */ long __RPC_FAR *retval);


void __RPC_STUB IADsDomain_get_MaxBadPasswordsAllowed_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [id][propput] */ HRESULT STDMETHODCALLTYPE IADsDomain_put_MaxBadPasswordsAllowed_Proxy( 
    IADsDomain __RPC_FAR * This,
    /* [in] */ long lnMaxBadPasswordsAllowed);


void __RPC_STUB IADsDomain_put_MaxBadPasswordsAllowed_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [id][propget] */ HRESULT STDMETHODCALLTYPE IADsDomain_get_PasswordHistoryLength_Proxy( 
    IADsDomain __RPC_FAR * This,
    /* [retval][out] */ long __RPC_FAR *retval);


void __RPC_STUB IADsDomain_get_PasswordHistoryLength_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [id][propput] */ HRESULT STDMETHODCALLTYPE IADsDomain_put_PasswordHistoryLength_Proxy( 
    IADsDomain __RPC_FAR * This,
    /* [in] */ long lnPasswordHistoryLength);


void __RPC_STUB IADsDomain_put_PasswordHistoryLength_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [id][propget] */ HRESULT STDMETHODCALLTYPE IADsDomain_get_PasswordAttributes_Proxy( 
    IADsDomain __RPC_FAR * This,
    /* [retval][out] */ long __RPC_FAR *retval);


void __RPC_STUB IADsDomain_get_PasswordAttributes_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [id][propput] */ HRESULT STDMETHODCALLTYPE IADsDomain_put_PasswordAttributes_Proxy( 
    IADsDomain __RPC_FAR * This,
    /* [in] */ long lnPasswordAttributes);


void __RPC_STUB IADsDomain_put_PasswordAttributes_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [id][propget] */ HRESULT STDMETHODCALLTYPE IADsDomain_get_AutoUnlockInterval_Proxy( 
    IADsDomain __RPC_FAR * This,
    /* [retval][out] */ long __RPC_FAR *retval);


void __RPC_STUB IADsDomain_get_AutoUnlockInterval_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [id][propput] */ HRESULT STDMETHODCALLTYPE IADsDomain_put_AutoUnlockInterval_Proxy( 
    IADsDomain __RPC_FAR * This,
    /* [in] */ long lnAutoUnlockInterval);


void __RPC_STUB IADsDomain_put_AutoUnlockInterval_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [id][propget] */ HRESULT STDMETHODCALLTYPE IADsDomain_get_LockoutObservationInterval_Proxy( 
    IADsDomain __RPC_FAR * This,
    /* [retval][out] */ long __RPC_FAR *retval);


void __RPC_STUB IADsDomain_get_LockoutObservationInterval_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [id][propput] */ HRESULT STDMETHODCALLTYPE IADsDomain_put_LockoutObservationInterval_Proxy( 
    IADsDomain __RPC_FAR * This,
    /* [in] */ long lnLockoutObservationInterval);


void __RPC_STUB IADsDomain_put_LockoutObservationInterval_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IADsDomain_INTERFACE_DEFINED__ */


#ifndef __IADsComputer_INTERFACE_DEFINED__
#define __IADsComputer_INTERFACE_DEFINED__

/****************************************
 * Generated header for interface: IADsComputer
 * at Mon Oct 13 13:47:30 1997
 * using MIDL 3.00.44
 ****************************************/
/* [object][dual][oleautomation][uuid] */ 



EXTERN_C const IID IID_IADsComputer;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    interface IADsComputer : public IADs
    {
    public:
        virtual /* [id][propget] */ HRESULT STDMETHODCALLTYPE get_ComputerID( 
            /* [retval][out] */ BSTR __RPC_FAR *retval) = 0;
        
        virtual /* [id][propget] */ HRESULT STDMETHODCALLTYPE get_Site( 
            /* [retval][out] */ BSTR __RPC_FAR *retval) = 0;
        
        virtual /* [id][propget] */ HRESULT STDMETHODCALLTYPE get_Description( 
            /* [retval][out] */ BSTR __RPC_FAR *retval) = 0;
        
        virtual /* [id][propput] */ HRESULT STDMETHODCALLTYPE put_Description( 
            /* [in] */ BSTR bstrDescription) = 0;
        
        virtual /* [id][propget] */ HRESULT STDMETHODCALLTYPE get_Location( 
            /* [retval][out] */ BSTR __RPC_FAR *retval) = 0;
        
        virtual /* [id][propput] */ HRESULT STDMETHODCALLTYPE put_Location( 
            /* [in] */ BSTR bstrLocation) = 0;
        
        virtual /* [id][propget] */ HRESULT STDMETHODCALLTYPE get_PrimaryUser( 
            /* [retval][out] */ BSTR __RPC_FAR *retval) = 0;
        
        virtual /* [id][propput] */ HRESULT STDMETHODCALLTYPE put_PrimaryUser( 
            /* [in] */ BSTR bstrPrimaryUser) = 0;
        
        virtual /* [id][propget] */ HRESULT STDMETHODCALLTYPE get_Owner( 
            /* [retval][out] */ BSTR __RPC_FAR *retval) = 0;
        
        virtual /* [id][propput] */ HRESULT STDMETHODCALLTYPE put_Owner( 
            /* [in] */ BSTR bstrOwner) = 0;
        
        virtual /* [id][propget] */ HRESULT STDMETHODCALLTYPE get_Division( 
            /* [retval][out] */ BSTR __RPC_FAR *retval) = 0;
        
        virtual /* [id][propput] */ HRESULT STDMETHODCALLTYPE put_Division( 
            /* [in] */ BSTR bstrDivision) = 0;
        
        virtual /* [id][propget] */ HRESULT STDMETHODCALLTYPE get_Department( 
            /* [retval][out] */ BSTR __RPC_FAR *retval) = 0;
        
        virtual /* [id][propput] */ HRESULT STDMETHODCALLTYPE put_Department( 
            /* [in] */ BSTR bstrDepartment) = 0;
        
        virtual /* [id][propget] */ HRESULT STDMETHODCALLTYPE get_Role( 
            /* [retval][out] */ BSTR __RPC_FAR *retval) = 0;
        
        virtual /* [id][propput] */ HRESULT STDMETHODCALLTYPE put_Role( 
            /* [in] */ BSTR bstrRole) = 0;
        
        virtual /* [id][propget] */ HRESULT STDMETHODCALLTYPE get_OperatingSystem( 
            /* [retval][out] */ BSTR __RPC_FAR *retval) = 0;
        
        virtual /* [id][propput] */ HRESULT STDMETHODCALLTYPE put_OperatingSystem( 
            /* [in] */ BSTR bstrOperatingSystem) = 0;
        
        virtual /* [id][propget] */ HRESULT STDMETHODCALLTYPE get_OperatingSystemVersion( 
            /* [retval][out] */ BSTR __RPC_FAR *retval) = 0;
        
        virtual /* [id][propput] */ HRESULT STDMETHODCALLTYPE put_OperatingSystemVersion( 
            /* [in] */ BSTR bstrOperatingSystemVersion) = 0;
        
        virtual /* [id][propget] */ HRESULT STDMETHODCALLTYPE get_Model( 
            /* [retval][out] */ BSTR __RPC_FAR *retval) = 0;
        
        virtual /* [id][propput] */ HRESULT STDMETHODCALLTYPE put_Model( 
            /* [in] */ BSTR bstrModel) = 0;
        
        virtual /* [id][propget] */ HRESULT STDMETHODCALLTYPE get_Processor( 
            /* [retval][out] */ BSTR __RPC_FAR *retval) = 0;
        
        virtual /* [id][propput] */ HRESULT STDMETHODCALLTYPE put_Processor( 
            /* [in] */ BSTR bstrProcessor) = 0;
        
        virtual /* [id][propget] */ HRESULT STDMETHODCALLTYPE get_ProcessorCount( 
            /* [retval][out] */ BSTR __RPC_FAR *retval) = 0;
        
        virtual /* [id][propput] */ HRESULT STDMETHODCALLTYPE put_ProcessorCount( 
            /* [in] */ BSTR bstrProcessorCount) = 0;
        
        virtual /* [id][propget] */ HRESULT STDMETHODCALLTYPE get_MemorySize( 
            /* [retval][out] */ BSTR __RPC_FAR *retval) = 0;
        
        virtual /* [id][propput] */ HRESULT STDMETHODCALLTYPE put_MemorySize( 
            /* [in] */ BSTR bstrMemorySize) = 0;
        
        virtual /* [id][propget] */ HRESULT STDMETHODCALLTYPE get_StorageCapacity( 
            /* [retval][out] */ BSTR __RPC_FAR *retval) = 0;
        
        virtual /* [id][propput] */ HRESULT STDMETHODCALLTYPE put_StorageCapacity( 
            /* [in] */ BSTR bstrStorageCapacity) = 0;
        
        virtual /* [id][propget] */ HRESULT STDMETHODCALLTYPE get_NetAddresses( 
            /* [retval][out] */ VARIANT __RPC_FAR *retval) = 0;
        
        virtual /* [id][propput] */ HRESULT STDMETHODCALLTYPE put_NetAddresses( 
            /* [in] */ VARIANT vNetAddresses) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IADsComputerVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            IADsComputer __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            IADsComputer __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            IADsComputer __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfoCount )( 
            IADsComputer __RPC_FAR * This,
            /* [out] */ UINT __RPC_FAR *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfo )( 
            IADsComputer __RPC_FAR * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo __RPC_FAR *__RPC_FAR *ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetIDsOfNames )( 
            IADsComputer __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR __RPC_FAR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID __RPC_FAR *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Invoke )( 
            IADsComputer __RPC_FAR * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS __RPC_FAR *pDispParams,
            /* [out] */ VARIANT __RPC_FAR *pVarResult,
            /* [out] */ EXCEPINFO __RPC_FAR *pExcepInfo,
            /* [out] */ UINT __RPC_FAR *puArgErr);
        
        /* [id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Name )( 
            IADsComputer __RPC_FAR * This,
            /* [retval][out] */ BSTR __RPC_FAR *retval);
        
        /* [id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Class )( 
            IADsComputer __RPC_FAR * This,
            /* [retval][out] */ BSTR __RPC_FAR *retval);
        
        /* [id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_GUID )( 
            IADsComputer __RPC_FAR * This,
            /* [retval][out] */ BSTR __RPC_FAR *retval);
        
        /* [id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_ADsPath )( 
            IADsComputer __RPC_FAR * This,
            /* [retval][out] */ BSTR __RPC_FAR *retval);
        
        /* [id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Parent )( 
            IADsComputer __RPC_FAR * This,
            /* [retval][out] */ BSTR __RPC_FAR *retval);
        
        /* [id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Schema )( 
            IADsComputer __RPC_FAR * This,
            /* [retval][out] */ BSTR __RPC_FAR *retval);
        
        /* [id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetInfo )( 
            IADsComputer __RPC_FAR * This);
        
        /* [id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *SetInfo )( 
            IADsComputer __RPC_FAR * This);
        
        /* [id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Get )( 
            IADsComputer __RPC_FAR * This,
            /* [in] */ BSTR bstrName,
            /* [retval][out] */ VARIANT __RPC_FAR *pvProp);
        
        /* [id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Put )( 
            IADsComputer __RPC_FAR * This,
            /* [in] */ BSTR bstrName,
            /* [in] */ VARIANT vProp);
        
        /* [id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetEx )( 
            IADsComputer __RPC_FAR * This,
            /* [in] */ BSTR bstrName,
            /* [retval][out] */ VARIANT __RPC_FAR *pvProp);
        
        /* [id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *PutEx )( 
            IADsComputer __RPC_FAR * This,
            /* [in] */ long lnControlCode,
            /* [in] */ BSTR bstrName,
            /* [in] */ VARIANT vProp);
        
        /* [id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetInfoEx )( 
            IADsComputer __RPC_FAR * This,
            /* [in] */ VARIANT vProperties,
            /* [in] */ long lnReserved);
        
        /* [id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_ComputerID )( 
            IADsComputer __RPC_FAR * This,
            /* [retval][out] */ BSTR __RPC_FAR *retval);
        
        /* [id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Site )( 
            IADsComputer __RPC_FAR * This,
            /* [retval][out] */ BSTR __RPC_FAR *retval);
        
        /* [id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Description )( 
            IADsComputer __RPC_FAR * This,
            /* [retval][out] */ BSTR __RPC_FAR *retval);
        
        /* [id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_Description )( 
            IADsComputer __RPC_FAR * This,
            /* [in] */ BSTR bstrDescription);
        
        /* [id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Location )( 
            IADsComputer __RPC_FAR * This,
            /* [retval][out] */ BSTR __RPC_FAR *retval);
        
        /* [id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_Location )( 
            IADsComputer __RPC_FAR * This,
            /* [in] */ BSTR bstrLocation);
        
        /* [id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_PrimaryUser )( 
            IADsComputer __RPC_FAR * This,
            /* [retval][out] */ BSTR __RPC_FAR *retval);
        
        /* [id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_PrimaryUser )( 
            IADsComputer __RPC_FAR * This,
            /* [in] */ BSTR bstrPrimaryUser);
        
        /* [id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Owner )( 
            IADsComputer __RPC_FAR * This,
            /* [retval][out] */ BSTR __RPC_FAR *retval);
        
        /* [id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_Owner )( 
            IADsComputer __RPC_FAR * This,
            /* [in] */ BSTR bstrOwner);
        
        /* [id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Division )( 
            IADsComputer __RPC_FAR * This,
            /* [retval][out] */ BSTR __RPC_FAR *retval);
        
        /* [id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_Division )( 
            IADsComputer __RPC_FAR * This,
            /* [in] */ BSTR bstrDivision);
        
        /* [id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Department )( 
            IADsComputer __RPC_FAR * This,
            /* [retval][out] */ BSTR __RPC_FAR *retval);
        
        /* [id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_Department )( 
            IADsComputer __RPC_FAR * This,
            /* [in] */ BSTR bstrDepartment);
        
        /* [id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Role )( 
            IADsComputer __RPC_FAR * This,
            /* [retval][out] */ BSTR __RPC_FAR *retval);
        
        /* [id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_Role )( 
            IADsComputer __RPC_FAR * This,
            /* [in] */ BSTR bstrRole);
        
        /* [id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_OperatingSystem )( 
            IADsComputer __RPC_FAR * This,
            /* [retval][out] */ BSTR __RPC_FAR *retval);
        
        /* [id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_OperatingSystem )( 
            IADsComputer __RPC_FAR * This,
            /* [in] */ BSTR bstrOperatingSystem);
        
        /* [id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_OperatingSystemVersion )( 
            IADsComputer __RPC_FAR * This,
            /* [retval][out] */ BSTR __RPC_FAR *retval);
        
        /* [id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_OperatingSystemVersion )( 
            IADsComputer __RPC_FAR * This,
            /* [in] */ BSTR bstrOperatingSystemVersion);
        
        /* [id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Model )( 
            IADsComputer __RPC_FAR * This,
            /* [retval][out] */ BSTR __RPC_FAR *retval);
        
        /* [id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_Model )( 
            IADsComputer __RPC_FAR * This,
            /* [in] */ BSTR bstrModel);
        
        /* [id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Processor )( 
            IADsComputer __RPC_FAR * This,
            /* [retval][out] */ BSTR __RPC_FAR *retval);
        
        /* [id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_Processor )( 
            IADsComputer __RPC_FAR * This,
            /* [in] */ BSTR bstrProcessor);
        
        /* [id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_ProcessorCount )( 
            IADsComputer __RPC_FAR * This,
            /* [retval][out] */ BSTR __RPC_FAR *retval);
        
        /* [id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_ProcessorCount )( 
            IADsComputer __RPC_FAR * This,
            /* [in] */ BSTR bstrProcessorCount);
        
        /* [id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_MemorySize )( 
            IADsComputer __RPC_FAR * This,
            /* [retval][out] */ BSTR __RPC_FAR *retval);
        
        /* [id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_MemorySize )( 
            IADsComputer __RPC_FAR * This,
            /* [in] */ BSTR bstrMemorySize);
        
        /* [id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_StorageCapacity )( 
            IADsComputer __RPC_FAR * This,
            /* [retval][out] */ BSTR __RPC_FAR *retval);
        
        /* [id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_StorageCapacity )( 
            IADsComputer __RPC_FAR * This,
            /* [in] */ BSTR bstrStorageCapacity);
        
        /* [id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_NetAddresses )( 
            IADsComputer __RPC_FAR * This,
            /* [retval][out] */ VARIANT __RPC_FAR *retval);
        
        /* [id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_NetAddresses )( 
            IADsComputer __RPC_FAR * This,
            /* [in] */ VARIANT vNetAddresses);
        
        END_INTERFACE
    } IADsComputerVtbl;

    interface IADsComputer
    {
        CONST_VTBL struct IADsComputerVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IADsComputer_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IADsComputer_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IADsComputer_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IADsComputer_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define IADsComputer_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define IADsComputer_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define IADsComputer_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)


#define IADsComputer_get_Name(This,retval)	\
    (This)->lpVtbl -> get_Name(This,retval)

#define IADsComputer_get_Class(This,retval)	\
    (This)->lpVtbl -> get_Class(This,retval)

#define IADsComputer_get_GUID(This,retval)	\
    (This)->lpVtbl -> get_GUID(This,retval)

#define IADsComputer_get_ADsPath(This,retval)	\
    (This)->lpVtbl -> get_ADsPath(This,retval)

#define IADsComputer_get_Parent(This,retval)	\
    (This)->lpVtbl -> get_Parent(This,retval)

#define IADsComputer_get_Schema(This,retval)	\
    (This)->lpVtbl -> get_Schema(This,retval)

#define IADsComputer_GetInfo(This)	\
    (This)->lpVtbl -> GetInfo(This)

#define IADsComputer_SetInfo(This)	\
    (This)->lpVtbl -> SetInfo(This)

#define IADsComputer_Get(This,bstrName,pvProp)	\
    (This)->lpVtbl -> Get(This,bstrName,pvProp)

#define IADsComputer_Put(This,bstrName,vProp)	\
    (This)->lpVtbl -> Put(This,bstrName,vProp)

#define IADsComputer_GetEx(This,bstrName,pvProp)	\
    (This)->lpVtbl -> GetEx(This,bstrName,pvProp)

#define IADsComputer_PutEx(This,lnControlCode,bstrName,vProp)	\
    (This)->lpVtbl -> PutEx(This,lnControlCode,bstrName,vProp)

#define IADsComputer_GetInfoEx(This,vProperties,lnReserved)	\
    (This)->lpVtbl -> GetInfoEx(This,vProperties,lnReserved)


#define IADsComputer_get_ComputerID(This,retval)	\
    (This)->lpVtbl -> get_ComputerID(This,retval)

#define IADsComputer_get_Site(This,retval)	\
    (This)->lpVtbl -> get_Site(This,retval)

#define IADsComputer_get_Description(This,retval)	\
    (This)->lpVtbl -> get_Description(This,retval)

#define IADsComputer_put_Description(This,bstrDescription)	\
    (This)->lpVtbl -> put_Description(This,bstrDescription)

#define IADsComputer_get_Location(This,retval)	\
    (This)->lpVtbl -> get_Location(This,retval)

#define IADsComputer_put_Location(This,bstrLocation)	\
    (This)->lpVtbl -> put_Location(This,bstrLocation)

#define IADsComputer_get_PrimaryUser(This,retval)	\
    (This)->lpVtbl -> get_PrimaryUser(This,retval)

#define IADsComputer_put_PrimaryUser(This,bstrPrimaryUser)	\
    (This)->lpVtbl -> put_PrimaryUser(This,bstrPrimaryUser)

#define IADsComputer_get_Owner(This,retval)	\
    (This)->lpVtbl -> get_Owner(This,retval)

#define IADsComputer_put_Owner(This,bstrOwner)	\
    (This)->lpVtbl -> put_Owner(This,bstrOwner)

#define IADsComputer_get_Division(This,retval)	\
    (This)->lpVtbl -> get_Division(This,retval)

#define IADsComputer_put_Division(This,bstrDivision)	\
    (This)->lpVtbl -> put_Division(This,bstrDivision)

#define IADsComputer_get_Department(This,retval)	\
    (This)->lpVtbl -> get_Department(This,retval)

#define IADsComputer_put_Department(This,bstrDepartment)	\
    (This)->lpVtbl -> put_Department(This,bstrDepartment)

#define IADsComputer_get_Role(This,retval)	\
    (This)->lpVtbl -> get_Role(This,retval)

#define IADsComputer_put_Role(This,bstrRole)	\
    (This)->lpVtbl -> put_Role(This,bstrRole)

#define IADsComputer_get_OperatingSystem(This,retval)	\
    (This)->lpVtbl -> get_OperatingSystem(This,retval)

#define IADsComputer_put_OperatingSystem(This,bstrOperatingSystem)	\
    (This)->lpVtbl -> put_OperatingSystem(This,bstrOperatingSystem)

#define IADsComputer_get_OperatingSystemVersion(This,retval)	\
    (This)->lpVtbl -> get_OperatingSystemVersion(This,retval)

#define IADsComputer_put_OperatingSystemVersion(This,bstrOperatingSystemVersion)	\
    (This)->lpVtbl -> put_OperatingSystemVersion(This,bstrOperatingSystemVersion)

#define IADsComputer_get_Model(This,retval)	\
    (This)->lpVtbl -> get_Model(This,retval)

#define IADsComputer_put_Model(This,bstrModel)	\
    (This)->lpVtbl -> put_Model(This,bstrModel)

#define IADsComputer_get_Processor(This,retval)	\
    (This)->lpVtbl -> get_Processor(This,retval)

#define IADsComputer_put_Processor(This,bstrProcessor)	\
    (This)->lpVtbl -> put_Processor(This,bstrProcessor)

#define IADsComputer_get_ProcessorCount(This,retval)	\
    (This)->lpVtbl -> get_ProcessorCount(This,retval)

#define IADsComputer_put_ProcessorCount(This,bstrProcessorCount)	\
    (This)->lpVtbl -> put_ProcessorCount(This,bstrProcessorCount)

#define IADsComputer_get_MemorySize(This,retval)	\
    (This)->lpVtbl -> get_MemorySize(This,retval)

#define IADsComputer_put_MemorySize(This,bstrMemorySize)	\
    (This)->lpVtbl -> put_MemorySize(This,bstrMemorySize)

#define IADsComputer_get_StorageCapacity(This,retval)	\
    (This)->lpVtbl -> get_StorageCapacity(This,retval)

#define IADsComputer_put_StorageCapacity(This,bstrStorageCapacity)	\
    (This)->lpVtbl -> put_StorageCapacity(This,bstrStorageCapacity)

#define IADsComputer_get_NetAddresses(This,retval)	\
    (This)->lpVtbl -> get_NetAddresses(This,retval)

#define IADsComputer_put_NetAddresses(This,vNetAddresses)	\
    (This)->lpVtbl -> put_NetAddresses(This,vNetAddresses)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [id][propget] */ HRESULT STDMETHODCALLTYPE IADsComputer_get_ComputerID_Proxy( 
    IADsComputer __RPC_FAR * This,
    /* [retval][out] */ BSTR __RPC_FAR *retval);


void __RPC_STUB IADsComputer_get_ComputerID_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [id][propget] */ HRESULT STDMETHODCALLTYPE IADsComputer_get_Site_Proxy( 
    IADsComputer __RPC_FAR * This,
    /* [retval][out] */ BSTR __RPC_FAR *retval);


void __RPC_STUB IADsComputer_get_Site_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [id][propget] */ HRESULT STDMETHODCALLTYPE IADsComputer_get_Description_Proxy( 
    IADsComputer __RPC_FAR * This,
    /* [retval][out] */ BSTR __RPC_FAR *retval);


void __RPC_STUB IADsComputer_get_Description_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [id][propput] */ HRESULT STDMETHODCALLTYPE IADsComputer_put_Description_Proxy( 
    IADsComputer __RPC_FAR * This,
    /* [in] */ BSTR bstrDescription);


void __RPC_STUB IADsComputer_put_Description_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [id][propget] */ HRESULT STDMETHODCALLTYPE IADsComputer_get_Location_Proxy( 
    IADsComputer __RPC_FAR * This,
    /* [retval][out] */ BSTR __RPC_FAR *retval);


void __RPC_STUB IADsComputer_get_Location_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [id][propput] */ HRESULT STDMETHODCALLTYPE IADsComputer_put_Location_Proxy( 
    IADsComputer __RPC_FAR * This,
    /* [in] */ BSTR bstrLocation);


void __RPC_STUB IADsComputer_put_Location_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [id][propget] */ HRESULT STDMETHODCALLTYPE IADsComputer_get_PrimaryUser_Proxy( 
    IADsComputer __RPC_FAR * This,
    /* [retval][out] */ BSTR __RPC_FAR *retval);


void __RPC_STUB IADsComputer_get_PrimaryUser_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [id][propput] */ HRESULT STDMETHODCALLTYPE IADsComputer_put_PrimaryUser_Proxy( 
    IADsComputer __RPC_FAR * This,
    /* [in] */ BSTR bstrPrimaryUser);


void __RPC_STUB IADsComputer_put_PrimaryUser_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [id][propget] */ HRESULT STDMETHODCALLTYPE IADsComputer_get_Owner_Proxy( 
    IADsComputer __RPC_FAR * This,
    /* [retval][out] */ BSTR __RPC_FAR *retval);


void __RPC_STUB IADsComputer_get_Owner_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [id][propput] */ HRESULT STDMETHODCALLTYPE IADsComputer_put_Owner_Proxy( 
    IADsComputer __RPC_FAR * This,
    /* [in] */ BSTR bstrOwner);


void __RPC_STUB IADsComputer_put_Owner_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [id][propget] */ HRESULT STDMETHODCALLTYPE IADsComputer_get_Division_Proxy( 
    IADsComputer __RPC_FAR * This,
    /* [retval][out] */ BSTR __RPC_FAR *retval);


void __RPC_STUB IADsComputer_get_Division_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [id][propput] */ HRESULT STDMETHODCALLTYPE IADsComputer_put_Division_Proxy( 
    IADsComputer __RPC_FAR * This,
    /* [in] */ BSTR bstrDivision);


void __RPC_STUB IADsComputer_put_Division_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [id][propget] */ HRESULT STDMETHODCALLTYPE IADsComputer_get_Department_Proxy( 
    IADsComputer __RPC_FAR * This,
    /* [retval][out] */ BSTR __RPC_FAR *retval);


void __RPC_STUB IADsComputer_get_Department_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [id][propput] */ HRESULT STDMETHODCALLTYPE IADsComputer_put_Department_Proxy( 
    IADsComputer __RPC_FAR * This,
    /* [in] */ BSTR bstrDepartment);


void __RPC_STUB IADsComputer_put_Department_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [id][propget] */ HRESULT STDMETHODCALLTYPE IADsComputer_get_Role_Proxy( 
    IADsComputer __RPC_FAR * This,
    /* [retval][out] */ BSTR __RPC_FAR *retval);


void __RPC_STUB IADsComputer_get_Role_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [id][propput] */ HRESULT STDMETHODCALLTYPE IADsComputer_put_Role_Proxy( 
    IADsComputer __RPC_FAR * This,
    /* [in] */ BSTR bstrRole);


void __RPC_STUB IADsComputer_put_Role_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [id][propget] */ HRESULT STDMETHODCALLTYPE IADsComputer_get_OperatingSystem_Proxy( 
    IADsComputer __RPC_FAR * This,
    /* [retval][out] */ BSTR __RPC_FAR *retval);


void __RPC_STUB IADsComputer_get_OperatingSystem_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [id][propput] */ HRESULT STDMETHODCALLTYPE IADsComputer_put_OperatingSystem_Proxy( 
    IADsComputer __RPC_FAR * This,
    /* [in] */ BSTR bstrOperatingSystem);


void __RPC_STUB IADsComputer_put_OperatingSystem_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [id][propget] */ HRESULT STDMETHODCALLTYPE IADsComputer_get_OperatingSystemVersion_Proxy( 
    IADsComputer __RPC_FAR * This,
    /* [retval][out] */ BSTR __RPC_FAR *retval);


void __RPC_STUB IADsComputer_get_OperatingSystemVersion_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [id][propput] */ HRESULT STDMETHODCALLTYPE IADsComputer_put_OperatingSystemVersion_Proxy( 
    IADsComputer __RPC_FAR * This,
    /* [in] */ BSTR bstrOperatingSystemVersion);


void __RPC_STUB IADsComputer_put_OperatingSystemVersion_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [id][propget] */ HRESULT STDMETHODCALLTYPE IADsComputer_get_Model_Proxy( 
    IADsComputer __RPC_FAR * This,
    /* [retval][out] */ BSTR __RPC_FAR *retval);


void __RPC_STUB IADsComputer_get_Model_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [id][propput] */ HRESULT STDMETHODCALLTYPE IADsComputer_put_Model_Proxy( 
    IADsComputer __RPC_FAR * This,
    /* [in] */ BSTR bstrModel);


void __RPC_STUB IADsComputer_put_Model_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [id][propget] */ HRESULT STDMETHODCALLTYPE IADsComputer_get_Processor_Proxy( 
    IADsComputer __RPC_FAR * This,
    /* [retval][out] */ BSTR __RPC_FAR *retval);


void __RPC_STUB IADsComputer_get_Processor_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [id][propput] */ HRESULT STDMETHODCALLTYPE IADsComputer_put_Processor_Proxy( 
    IADsComputer __RPC_FAR * This,
    /* [in] */ BSTR bstrProcessor);


void __RPC_STUB IADsComputer_put_Processor_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [id][propget] */ HRESULT STDMETHODCALLTYPE IADsComputer_get_ProcessorCount_Proxy( 
    IADsComputer __RPC_FAR * This,
    /* [retval][out] */ BSTR __RPC_FAR *retval);


void __RPC_STUB IADsComputer_get_ProcessorCount_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [id][propput] */ HRESULT STDMETHODCALLTYPE IADsComputer_put_ProcessorCount_Proxy( 
    IADsComputer __RPC_FAR * This,
    /* [in] */ BSTR bstrProcessorCount);


void __RPC_STUB IADsComputer_put_ProcessorCount_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [id][propget] */ HRESULT STDMETHODCALLTYPE IADsComputer_get_MemorySize_Proxy( 
    IADsComputer __RPC_FAR * This,
    /* [retval][out] */ BSTR __RPC_FAR *retval);


void __RPC_STUB IADsComputer_get_MemorySize_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [id][propput] */ HRESULT STDMETHODCALLTYPE IADsComputer_put_MemorySize_Proxy( 
    IADsComputer __RPC_FAR * This,
    /* [in] */ BSTR bstrMemorySize);


void __RPC_STUB IADsComputer_put_MemorySize_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [id][propget] */ HRESULT STDMETHODCALLTYPE IADsComputer_get_StorageCapacity_Proxy( 
    IADsComputer __RPC_FAR * This,
    /* [retval][out] */ BSTR __RPC_FAR *retval);


void __RPC_STUB IADsComputer_get_StorageCapacity_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [id][propput] */ HRESULT STDMETHODCALLTYPE IADsComputer_put_StorageCapacity_Proxy( 
    IADsComputer __RPC_FAR * This,
    /* [in] */ BSTR bstrStorageCapacity);


void __RPC_STUB IADsComputer_put_StorageCapacity_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [id][propget] */ HRESULT STDMETHODCALLTYPE IADsComputer_get_NetAddresses_Proxy( 
    IADsComputer __RPC_FAR * This,
    /* [retval][out] */ VARIANT __RPC_FAR *retval);


void __RPC_STUB IADsComputer_get_NetAddresses_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [id][propput] */ HRESULT STDMETHODCALLTYPE IADsComputer_put_NetAddresses_Proxy( 
    IADsComputer __RPC_FAR * This,
    /* [in] */ VARIANT vNetAddresses);


void __RPC_STUB IADsComputer_put_NetAddresses_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IADsComputer_INTERFACE_DEFINED__ */


#ifndef __IADsComputerOperations_INTERFACE_DEFINED__
#define __IADsComputerOperations_INTERFACE_DEFINED__

/****************************************
 * Generated header for interface: IADsComputerOperations
 * at Mon Oct 13 13:47:30 1997
 * using MIDL 3.00.44
 ****************************************/
/* [object][dual][oleautomation][uuid] */ 



EXTERN_C const IID IID_IADsComputerOperations;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    interface IADsComputerOperations : public IADs
    {
    public:
        virtual /* [id] */ HRESULT STDMETHODCALLTYPE Status( 
            /* [retval][out] */ IDispatch __RPC_FAR *__RPC_FAR *ppObject) = 0;
        
        virtual /* [id] */ HRESULT STDMETHODCALLTYPE Shutdown( 
            /* [in] */ VARIANT_BOOL bReboot) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IADsComputerOperationsVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            IADsComputerOperations __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            IADsComputerOperations __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            IADsComputerOperations __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfoCount )( 
            IADsComputerOperations __RPC_FAR * This,
            /* [out] */ UINT __RPC_FAR *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfo )( 
            IADsComputerOperations __RPC_FAR * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo __RPC_FAR *__RPC_FAR *ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetIDsOfNames )( 
            IADsComputerOperations __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR __RPC_FAR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID __RPC_FAR *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Invoke )( 
            IADsComputerOperations __RPC_FAR * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS __RPC_FAR *pDispParams,
            /* [out] */ VARIANT __RPC_FAR *pVarResult,
            /* [out] */ EXCEPINFO __RPC_FAR *pExcepInfo,
            /* [out] */ UINT __RPC_FAR *puArgErr);
        
        /* [id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Name )( 
            IADsComputerOperations __RPC_FAR * This,
            /* [retval][out] */ BSTR __RPC_FAR *retval);
        
        /* [id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Class )( 
            IADsComputerOperations __RPC_FAR * This,
            /* [retval][out] */ BSTR __RPC_FAR *retval);
        
        /* [id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_GUID )( 
            IADsComputerOperations __RPC_FAR * This,
            /* [retval][out] */ BSTR __RPC_FAR *retval);
        
        /* [id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_ADsPath )( 
            IADsComputerOperations __RPC_FAR * This,
            /* [retval][out] */ BSTR __RPC_FAR *retval);
        
        /* [id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Parent )( 
            IADsComputerOperations __RPC_FAR * This,
            /* [retval][out] */ BSTR __RPC_FAR *retval);
        
        /* [id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Schema )( 
            IADsComputerOperations __RPC_FAR * This,
            /* [retval][out] */ BSTR __RPC_FAR *retval);
        
        /* [id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetInfo )( 
            IADsComputerOperations __RPC_FAR * This);
        
        /* [id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *SetInfo )( 
            IADsComputerOperations __RPC_FAR * This);
        
        /* [id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Get )( 
            IADsComputerOperations __RPC_FAR * This,
            /* [in] */ BSTR bstrName,
            /* [retval][out] */ VARIANT __RPC_FAR *pvProp);
        
        /* [id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Put )( 
            IADsComputerOperations __RPC_FAR * This,
            /* [in] */ BSTR bstrName,
            /* [in] */ VARIANT vProp);
        
        /* [id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetEx )( 
            IADsComputerOperations __RPC_FAR * This,
            /* [in] */ BSTR bstrName,
            /* [retval][out] */ VARIANT __RPC_FAR *pvProp);
        
        /* [id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *PutEx )( 
            IADsComputerOperations __RPC_FAR * This,
            /* [in] */ long lnControlCode,
            /* [in] */ BSTR bstrName,
            /* [in] */ VARIANT vProp);
        
        /* [id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetInfoEx )( 
            IADsComputerOperations __RPC_FAR * This,
            /* [in] */ VARIANT vProperties,
            /* [in] */ long lnReserved);
        
        /* [id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Status )( 
            IADsComputerOperations __RPC_FAR * This,
            /* [retval][out] */ IDispatch __RPC_FAR *__RPC_FAR *ppObject);
        
        /* [id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Shutdown )( 
            IADsComputerOperations __RPC_FAR * This,
            /* [in] */ VARIANT_BOOL bReboot);
        
        END_INTERFACE
    } IADsComputerOperationsVtbl;

    interface IADsComputerOperations
    {
        CONST_VTBL struct IADsComputerOperationsVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IADsComputerOperations_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IADsComputerOperations_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IADsComputerOperations_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IADsComputerOperations_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define IADsComputerOperations_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define IADsComputerOperations_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define IADsComputerOperations_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)


#define IADsComputerOperations_get_Name(This,retval)	\
    (This)->lpVtbl -> get_Name(This,retval)

#define IADsComputerOperations_get_Class(This,retval)	\
    (This)->lpVtbl -> get_Class(This,retval)

#define IADsComputerOperations_get_GUID(This,retval)	\
    (This)->lpVtbl -> get_GUID(This,retval)

#define IADsComputerOperations_get_ADsPath(This,retval)	\
    (This)->lpVtbl -> get_ADsPath(This,retval)

#define IADsComputerOperations_get_Parent(This,retval)	\
    (This)->lpVtbl -> get_Parent(This,retval)

#define IADsComputerOperations_get_Schema(This,retval)	\
    (This)->lpVtbl -> get_Schema(This,retval)

#define IADsComputerOperations_GetInfo(This)	\
    (This)->lpVtbl -> GetInfo(This)

#define IADsComputerOperations_SetInfo(This)	\
    (This)->lpVtbl -> SetInfo(This)

#define IADsComputerOperations_Get(This,bstrName,pvProp)	\
    (This)->lpVtbl -> Get(This,bstrName,pvProp)

#define IADsComputerOperations_Put(This,bstrName,vProp)	\
    (This)->lpVtbl -> Put(This,bstrName,vProp)

#define IADsComputerOperations_GetEx(This,bstrName,pvProp)	\
    (This)->lpVtbl -> GetEx(This,bstrName,pvProp)

#define IADsComputerOperations_PutEx(This,lnControlCode,bstrName,vProp)	\
    (This)->lpVtbl -> PutEx(This,lnControlCode,bstrName,vProp)

#define IADsComputerOperations_GetInfoEx(This,vProperties,lnReserved)	\
    (This)->lpVtbl -> GetInfoEx(This,vProperties,lnReserved)


#define IADsComputerOperations_Status(This,ppObject)	\
    (This)->lpVtbl -> Status(This,ppObject)

#define IADsComputerOperations_Shutdown(This,bReboot)	\
    (This)->lpVtbl -> Shutdown(This,bReboot)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [id] */ HRESULT STDMETHODCALLTYPE IADsComputerOperations_Status_Proxy( 
    IADsComputerOperations __RPC_FAR * This,
    /* [retval][out] */ IDispatch __RPC_FAR *__RPC_FAR *ppObject);


void __RPC_STUB IADsComputerOperations_Status_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [id] */ HRESULT STDMETHODCALLTYPE IADsComputerOperations_Shutdown_Proxy( 
    IADsComputerOperations __RPC_FAR * This,
    /* [in] */ VARIANT_BOOL bReboot);


void __RPC_STUB IADsComputerOperations_Shutdown_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IADsComputerOperations_INTERFACE_DEFINED__ */


#ifndef __IADsGroup_INTERFACE_DEFINED__
#define __IADsGroup_INTERFACE_DEFINED__

/****************************************
 * Generated header for interface: IADsGroup
 * at Mon Oct 13 13:47:30 1997
 * using MIDL 3.00.44
 ****************************************/
/* [object][dual][oleautomation][uuid] */ 



EXTERN_C const IID IID_IADsGroup;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    interface IADsGroup : public IADs
    {
    public:
        virtual /* [id][propget] */ HRESULT STDMETHODCALLTYPE get_Description( 
            /* [retval][out] */ BSTR __RPC_FAR *retval) = 0;
        
        virtual /* [id][propput] */ HRESULT STDMETHODCALLTYPE put_Description( 
            /* [in] */ BSTR bstrDescription) = 0;
        
        virtual /* [id] */ HRESULT STDMETHODCALLTYPE Members( 
            /* [retval][out] */ IADsMembers __RPC_FAR *__RPC_FAR *ppMembers) = 0;
        
        virtual /* [id] */ HRESULT STDMETHODCALLTYPE IsMember( 
            /* [in] */ BSTR bstrMember,
            /* [retval][out] */ VARIANT_BOOL __RPC_FAR *bMember) = 0;
        
        virtual /* [id] */ HRESULT STDMETHODCALLTYPE Add( 
            /* [in] */ BSTR bstrNewItem) = 0;
        
        virtual /* [id] */ HRESULT STDMETHODCALLTYPE Remove( 
            /* [in] */ BSTR bstrItemToBeRemoved) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IADsGroupVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            IADsGroup __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            IADsGroup __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            IADsGroup __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfoCount )( 
            IADsGroup __RPC_FAR * This,
            /* [out] */ UINT __RPC_FAR *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfo )( 
            IADsGroup __RPC_FAR * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo __RPC_FAR *__RPC_FAR *ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetIDsOfNames )( 
            IADsGroup __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR __RPC_FAR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID __RPC_FAR *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Invoke )( 
            IADsGroup __RPC_FAR * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS __RPC_FAR *pDispParams,
            /* [out] */ VARIANT __RPC_FAR *pVarResult,
            /* [out] */ EXCEPINFO __RPC_FAR *pExcepInfo,
            /* [out] */ UINT __RPC_FAR *puArgErr);
        
        /* [id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Name )( 
            IADsGroup __RPC_FAR * This,
            /* [retval][out] */ BSTR __RPC_FAR *retval);
        
        /* [id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Class )( 
            IADsGroup __RPC_FAR * This,
            /* [retval][out] */ BSTR __RPC_FAR *retval);
        
        /* [id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_GUID )( 
            IADsGroup __RPC_FAR * This,
            /* [retval][out] */ BSTR __RPC_FAR *retval);
        
        /* [id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_ADsPath )( 
            IADsGroup __RPC_FAR * This,
            /* [retval][out] */ BSTR __RPC_FAR *retval);
        
        /* [id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Parent )( 
            IADsGroup __RPC_FAR * This,
            /* [retval][out] */ BSTR __RPC_FAR *retval);
        
        /* [id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Schema )( 
            IADsGroup __RPC_FAR * This,
            /* [retval][out] */ BSTR __RPC_FAR *retval);
        
        /* [id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetInfo )( 
            IADsGroup __RPC_FAR * This);
        
        /* [id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *SetInfo )( 
            IADsGroup __RPC_FAR * This);
        
        /* [id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Get )( 
            IADsGroup __RPC_FAR * This,
            /* [in] */ BSTR bstrName,
            /* [retval][out] */ VARIANT __RPC_FAR *pvProp);
        
        /* [id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Put )( 
            IADsGroup __RPC_FAR * This,
            /* [in] */ BSTR bstrName,
            /* [in] */ VARIANT vProp);
        
        /* [id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetEx )( 
            IADsGroup __RPC_FAR * This,
            /* [in] */ BSTR bstrName,
            /* [retval][out] */ VARIANT __RPC_FAR *pvProp);
        
        /* [id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *PutEx )( 
            IADsGroup __RPC_FAR * This,
            /* [in] */ long lnControlCode,
            /* [in] */ BSTR bstrName,
            /* [in] */ VARIANT vProp);
        
        /* [id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetInfoEx )( 
            IADsGroup __RPC_FAR * This,
            /* [in] */ VARIANT vProperties,
            /* [in] */ long lnReserved);
        
        /* [id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Description )( 
            IADsGroup __RPC_FAR * This,
            /* [retval][out] */ BSTR __RPC_FAR *retval);
        
        /* [id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_Description )( 
            IADsGroup __RPC_FAR * This,
            /* [in] */ BSTR bstrDescription);
        
        /* [id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Members )( 
            IADsGroup __RPC_FAR * This,
            /* [retval][out] */ IADsMembers __RPC_FAR *__RPC_FAR *ppMembers);
        
        /* [id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *IsMember )( 
            IADsGroup __RPC_FAR * This,
            /* [in] */ BSTR bstrMember,
            /* [retval][out] */ VARIANT_BOOL __RPC_FAR *bMember);
        
        /* [id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Add )( 
            IADsGroup __RPC_FAR * This,
            /* [in] */ BSTR bstrNewItem);
        
        /* [id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Remove )( 
            IADsGroup __RPC_FAR * This,
            /* [in] */ BSTR bstrItemToBeRemoved);
        
        END_INTERFACE
    } IADsGroupVtbl;

    interface IADsGroup
    {
        CONST_VTBL struct IADsGroupVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IADsGroup_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IADsGroup_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IADsGroup_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IADsGroup_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define IADsGroup_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define IADsGroup_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define IADsGroup_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)


#define IADsGroup_get_Name(This,retval)	\
    (This)->lpVtbl -> get_Name(This,retval)

#define IADsGroup_get_Class(This,retval)	\
    (This)->lpVtbl -> get_Class(This,retval)

#define IADsGroup_get_GUID(This,retval)	\
    (This)->lpVtbl -> get_GUID(This,retval)

#define IADsGroup_get_ADsPath(This,retval)	\
    (This)->lpVtbl -> get_ADsPath(This,retval)

#define IADsGroup_get_Parent(This,retval)	\
    (This)->lpVtbl -> get_Parent(This,retval)

#define IADsGroup_get_Schema(This,retval)	\
    (This)->lpVtbl -> get_Schema(This,retval)

#define IADsGroup_GetInfo(This)	\
    (This)->lpVtbl -> GetInfo(This)

#define IADsGroup_SetInfo(This)	\
    (This)->lpVtbl -> SetInfo(This)

#define IADsGroup_Get(This,bstrName,pvProp)	\
    (This)->lpVtbl -> Get(This,bstrName,pvProp)

#define IADsGroup_Put(This,bstrName,vProp)	\
    (This)->lpVtbl -> Put(This,bstrName,vProp)

#define IADsGroup_GetEx(This,bstrName,pvProp)	\
    (This)->lpVtbl -> GetEx(This,bstrName,pvProp)

#define IADsGroup_PutEx(This,lnControlCode,bstrName,vProp)	\
    (This)->lpVtbl -> PutEx(This,lnControlCode,bstrName,vProp)

#define IADsGroup_GetInfoEx(This,vProperties,lnReserved)	\
    (This)->lpVtbl -> GetInfoEx(This,vProperties,lnReserved)


#define IADsGroup_get_Description(This,retval)	\
    (This)->lpVtbl -> get_Description(This,retval)

#define IADsGroup_put_Description(This,bstrDescription)	\
    (This)->lpVtbl -> put_Description(This,bstrDescription)

#define IADsGroup_Members(This,ppMembers)	\
    (This)->lpVtbl -> Members(This,ppMembers)

#define IADsGroup_IsMember(This,bstrMember,bMember)	\
    (This)->lpVtbl -> IsMember(This,bstrMember,bMember)

#define IADsGroup_Add(This,bstrNewItem)	\
    (This)->lpVtbl -> Add(This,bstrNewItem)

#define IADsGroup_Remove(This,bstrItemToBeRemoved)	\
    (This)->lpVtbl -> Remove(This,bstrItemToBeRemoved)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [id][propget] */ HRESULT STDMETHODCALLTYPE IADsGroup_get_Description_Proxy( 
    IADsGroup __RPC_FAR * This,
    /* [retval][out] */ BSTR __RPC_FAR *retval);


void __RPC_STUB IADsGroup_get_Description_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [id][propput] */ HRESULT STDMETHODCALLTYPE IADsGroup_put_Description_Proxy( 
    IADsGroup __RPC_FAR * This,
    /* [in] */ BSTR bstrDescription);


void __RPC_STUB IADsGroup_put_Description_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [id] */ HRESULT STDMETHODCALLTYPE IADsGroup_Members_Proxy( 
    IADsGroup __RPC_FAR * This,
    /* [retval][out] */ IADsMembers __RPC_FAR *__RPC_FAR *ppMembers);


void __RPC_STUB IADsGroup_Members_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [id] */ HRESULT STDMETHODCALLTYPE IADsGroup_IsMember_Proxy( 
    IADsGroup __RPC_FAR * This,
    /* [in] */ BSTR bstrMember,
    /* [retval][out] */ VARIANT_BOOL __RPC_FAR *bMember);


void __RPC_STUB IADsGroup_IsMember_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [id] */ HRESULT STDMETHODCALLTYPE IADsGroup_Add_Proxy( 
    IADsGroup __RPC_FAR * This,
    /* [in] */ BSTR bstrNewItem);


void __RPC_STUB IADsGroup_Add_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [id] */ HRESULT STDMETHODCALLTYPE IADsGroup_Remove_Proxy( 
    IADsGroup __RPC_FAR * This,
    /* [in] */ BSTR bstrItemToBeRemoved);


void __RPC_STUB IADsGroup_Remove_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IADsGroup_INTERFACE_DEFINED__ */


#ifndef __IADsUser_INTERFACE_DEFINED__
#define __IADsUser_INTERFACE_DEFINED__

/****************************************
 * Generated header for interface: IADsUser
 * at Mon Oct 13 13:47:30 1997
 * using MIDL 3.00.44
 ****************************************/
/* [object][dual][oleautomation][uuid] */ 



EXTERN_C const IID IID_IADsUser;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    interface IADsUser : public IADs
    {
    public:
        virtual /* [id][propget] */ HRESULT STDMETHODCALLTYPE get_BadLoginAddress( 
            /* [retval][out] */ BSTR __RPC_FAR *retval) = 0;
        
        virtual /* [id][propget] */ HRESULT STDMETHODCALLTYPE get_BadLoginCount( 
            /* [retval][out] */ long __RPC_FAR *retval) = 0;
        
        virtual /* [id][propget] */ HRESULT STDMETHODCALLTYPE get_LastLogin( 
            /* [retval][out] */ DATE __RPC_FAR *retval) = 0;
        
        virtual /* [id][propget] */ HRESULT STDMETHODCALLTYPE get_LastLogoff( 
            /* [retval][out] */ DATE __RPC_FAR *retval) = 0;
        
        virtual /* [id][propget] */ HRESULT STDMETHODCALLTYPE get_LastFailedLogin( 
            /* [retval][out] */ DATE __RPC_FAR *retval) = 0;
        
        virtual /* [id][propget] */ HRESULT STDMETHODCALLTYPE get_PasswordLastChanged( 
            /* [retval][out] */ DATE __RPC_FAR *retval) = 0;
        
        virtual /* [id][propget] */ HRESULT STDMETHODCALLTYPE get_Description( 
            /* [retval][out] */ BSTR __RPC_FAR *retval) = 0;
        
        virtual /* [id][propput] */ HRESULT STDMETHODCALLTYPE put_Description( 
            /* [in] */ BSTR bstrDescription) = 0;
        
        virtual /* [id][propget] */ HRESULT STDMETHODCALLTYPE get_Division( 
            /* [retval][out] */ BSTR __RPC_FAR *retval) = 0;
        
        virtual /* [id][propput] */ HRESULT STDMETHODCALLTYPE put_Division( 
            /* [in] */ BSTR bstrDivision) = 0;
        
        virtual /* [id][propget] */ HRESULT STDMETHODCALLTYPE get_Department( 
            /* [retval][out] */ BSTR __RPC_FAR *retval) = 0;
        
        virtual /* [id][propput] */ HRESULT STDMETHODCALLTYPE put_Department( 
            /* [in] */ BSTR bstrDepartment) = 0;
        
        virtual /* [id][propget] */ HRESULT STDMETHODCALLTYPE get_EmployeeID( 
            /* [retval][out] */ BSTR __RPC_FAR *retval) = 0;
        
        virtual /* [id][propput] */ HRESULT STDMETHODCALLTYPE put_EmployeeID( 
            /* [in] */ BSTR bstrEmployeeID) = 0;
        
        virtual /* [id][propget] */ HRESULT STDMETHODCALLTYPE get_FullName( 
            /* [retval][out] */ BSTR __RPC_FAR *retval) = 0;
        
        virtual /* [id][propput] */ HRESULT STDMETHODCALLTYPE put_FullName( 
            /* [in] */ BSTR bstrFullName) = 0;
        
        virtual /* [id][propget] */ HRESULT STDMETHODCALLTYPE get_FirstName( 
            /* [retval][out] */ BSTR __RPC_FAR *retval) = 0;
        
        virtual /* [id][propput] */ HRESULT STDMETHODCALLTYPE put_FirstName( 
            /* [in] */ BSTR bstrFirstName) = 0;
        
        virtual /* [id][propget] */ HRESULT STDMETHODCALLTYPE get_LastName( 
            /* [retval][out] */ BSTR __RPC_FAR *retval) = 0;
        
        virtual /* [id][propput] */ HRESULT STDMETHODCALLTYPE put_LastName( 
            /* [in] */ BSTR bstrLastName) = 0;
        
        virtual /* [id][propget] */ HRESULT STDMETHODCALLTYPE get_OtherName( 
            /* [retval][out] */ BSTR __RPC_FAR *retval) = 0;
        
        virtual /* [id][propput] */ HRESULT STDMETHODCALLTYPE put_OtherName( 
            /* [in] */ BSTR bstrOtherName) = 0;
        
        virtual /* [id][propget] */ HRESULT STDMETHODCALLTYPE get_NamePrefix( 
            /* [retval][out] */ BSTR __RPC_FAR *retval) = 0;
        
        virtual /* [id][propput] */ HRESULT STDMETHODCALLTYPE put_NamePrefix( 
            /* [in] */ BSTR bstrNamePrefix) = 0;
        
        virtual /* [id][propget] */ HRESULT STDMETHODCALLTYPE get_NameSuffix( 
            /* [retval][out] */ BSTR __RPC_FAR *retval) = 0;
        
        virtual /* [id][propput] */ HRESULT STDMETHODCALLTYPE put_NameSuffix( 
            /* [in] */ BSTR bstrNameSuffix) = 0;
        
        virtual /* [id][propget] */ HRESULT STDMETHODCALLTYPE get_Title( 
            /* [retval][out] */ BSTR __RPC_FAR *retval) = 0;
        
        virtual /* [id][propput] */ HRESULT STDMETHODCALLTYPE put_Title( 
            /* [in] */ BSTR bstrTitle) = 0;
        
        virtual /* [id][propget] */ HRESULT STDMETHODCALLTYPE get_Manager( 
            /* [retval][out] */ BSTR __RPC_FAR *retval) = 0;
        
        virtual /* [id][propput] */ HRESULT STDMETHODCALLTYPE put_Manager( 
            /* [in] */ BSTR bstrManager) = 0;
        
        virtual /* [id][propget] */ HRESULT STDMETHODCALLTYPE get_TelephoneHome( 
            /* [retval][out] */ VARIANT __RPC_FAR *retval) = 0;
        
        virtual /* [id][propput] */ HRESULT STDMETHODCALLTYPE put_TelephoneHome( 
            /* [in] */ VARIANT vTelephoneHome) = 0;
        
        virtual /* [id][propget] */ HRESULT STDMETHODCALLTYPE get_TelephoneMobile( 
            /* [retval][out] */ VARIANT __RPC_FAR *retval) = 0;
        
        virtual /* [id][propput] */ HRESULT STDMETHODCALLTYPE put_TelephoneMobile( 
            /* [in] */ VARIANT vTelephoneMobile) = 0;
        
        virtual /* [id][propget] */ HRESULT STDMETHODCALLTYPE get_TelephoneNumber( 
            /* [retval][out] */ VARIANT __RPC_FAR *retval) = 0;
        
        virtual /* [id][propput] */ HRESULT STDMETHODCALLTYPE put_TelephoneNumber( 
            /* [in] */ VARIANT vTelephoneNumber) = 0;
        
        virtual /* [id][propget] */ HRESULT STDMETHODCALLTYPE get_TelephonePager( 
            /* [retval][out] */ VARIANT __RPC_FAR *retval) = 0;
        
        virtual /* [id][propput] */ HRESULT STDMETHODCALLTYPE put_TelephonePager( 
            /* [in] */ VARIANT vTelephonePager) = 0;
        
        virtual /* [id][propget] */ HRESULT STDMETHODCALLTYPE get_FaxNumber( 
            /* [retval][out] */ VARIANT __RPC_FAR *retval) = 0;
        
        virtual /* [id][propput] */ HRESULT STDMETHODCALLTYPE put_FaxNumber( 
            /* [in] */ VARIANT vFaxNumber) = 0;
        
        virtual /* [id][propget] */ HRESULT STDMETHODCALLTYPE get_OfficeLocations( 
            /* [retval][out] */ VARIANT __RPC_FAR *retval) = 0;
        
        virtual /* [id][propput] */ HRESULT STDMETHODCALLTYPE put_OfficeLocations( 
            /* [in] */ VARIANT vOfficeLocations) = 0;
        
        virtual /* [id][propget] */ HRESULT STDMETHODCALLTYPE get_PostalAddresses( 
            /* [retval][out] */ VARIANT __RPC_FAR *retval) = 0;
        
        virtual /* [id][propput] */ HRESULT STDMETHODCALLTYPE put_PostalAddresses( 
            /* [in] */ VARIANT vPostalAddresses) = 0;
        
        virtual /* [id][propget] */ HRESULT STDMETHODCALLTYPE get_PostalCodes( 
            /* [retval][out] */ VARIANT __RPC_FAR *retval) = 0;
        
        virtual /* [id][propput] */ HRESULT STDMETHODCALLTYPE put_PostalCodes( 
            /* [in] */ VARIANT vPostalCodes) = 0;
        
        virtual /* [id][propget] */ HRESULT STDMETHODCALLTYPE get_SeeAlso( 
            /* [retval][out] */ VARIANT __RPC_FAR *retval) = 0;
        
        virtual /* [id][propput] */ HRESULT STDMETHODCALLTYPE put_SeeAlso( 
            /* [in] */ VARIANT vSeeAlso) = 0;
        
        virtual /* [id][propget] */ HRESULT STDMETHODCALLTYPE get_AccountDisabled( 
            /* [retval][out] */ VARIANT_BOOL __RPC_FAR *retval) = 0;
        
        virtual /* [id][propput] */ HRESULT STDMETHODCALLTYPE put_AccountDisabled( 
            /* [in] */ VARIANT_BOOL fAccountDisabled) = 0;
        
        virtual /* [id][propget] */ HRESULT STDMETHODCALLTYPE get_AccountExpirationDate( 
            /* [retval][out] */ DATE __RPC_FAR *retval) = 0;
        
        virtual /* [id][propput] */ HRESULT STDMETHODCALLTYPE put_AccountExpirationDate( 
            /* [in] */ DATE daAccountExpirationDate) = 0;
        
        virtual /* [id][propget] */ HRESULT STDMETHODCALLTYPE get_GraceLoginsAllowed( 
            /* [retval][out] */ long __RPC_FAR *retval) = 0;
        
        virtual /* [id][propput] */ HRESULT STDMETHODCALLTYPE put_GraceLoginsAllowed( 
            /* [in] */ long lnGraceLoginsAllowed) = 0;
        
        virtual /* [id][propget] */ HRESULT STDMETHODCALLTYPE get_GraceLoginsRemaining( 
            /* [retval][out] */ long __RPC_FAR *retval) = 0;
        
        virtual /* [id][propput] */ HRESULT STDMETHODCALLTYPE put_GraceLoginsRemaining( 
            /* [in] */ long lnGraceLoginsRemaining) = 0;
        
        virtual /* [id][propget] */ HRESULT STDMETHODCALLTYPE get_IsAccountLocked( 
            /* [retval][out] */ VARIANT_BOOL __RPC_FAR *retval) = 0;
        
        virtual /* [id][propput] */ HRESULT STDMETHODCALLTYPE put_IsAccountLocked( 
            /* [in] */ VARIANT_BOOL fIsAccountLocked) = 0;
        
        virtual /* [id][propget] */ HRESULT STDMETHODCALLTYPE get_LoginHours( 
            /* [retval][out] */ VARIANT __RPC_FAR *retval) = 0;
        
        virtual /* [id][propput] */ HRESULT STDMETHODCALLTYPE put_LoginHours( 
            /* [in] */ VARIANT vLoginHours) = 0;
        
        virtual /* [id][propget] */ HRESULT STDMETHODCALLTYPE get_LoginWorkstations( 
            /* [retval][out] */ VARIANT __RPC_FAR *retval) = 0;
        
        virtual /* [id][propput] */ HRESULT STDMETHODCALLTYPE put_LoginWorkstations( 
            /* [in] */ VARIANT vLoginWorkstations) = 0;
        
        virtual /* [id][propget] */ HRESULT STDMETHODCALLTYPE get_MaxLogins( 
            /* [retval][out] */ long __RPC_FAR *retval) = 0;
        
        virtual /* [id][propput] */ HRESULT STDMETHODCALLTYPE put_MaxLogins( 
            /* [in] */ long lnMaxLogins) = 0;
        
        virtual /* [id][propget] */ HRESULT STDMETHODCALLTYPE get_MaxStorage( 
            /* [retval][out] */ long __RPC_FAR *retval) = 0;
        
        virtual /* [id][propput] */ HRESULT STDMETHODCALLTYPE put_MaxStorage( 
            /* [in] */ long lnMaxStorage) = 0;
        
        virtual /* [id][propget] */ HRESULT STDMETHODCALLTYPE get_PasswordExpirationDate( 
            /* [retval][out] */ DATE __RPC_FAR *retval) = 0;
        
        virtual /* [id][propput] */ HRESULT STDMETHODCALLTYPE put_PasswordExpirationDate( 
            /* [in] */ DATE daPasswordExpirationDate) = 0;
        
        virtual /* [id][propget] */ HRESULT STDMETHODCALLTYPE get_PasswordMinimumLength( 
            /* [retval][out] */ long __RPC_FAR *retval) = 0;
        
        virtual /* [id][propput] */ HRESULT STDMETHODCALLTYPE put_PasswordMinimumLength( 
            /* [in] */ long lnPasswordMinimumLength) = 0;
        
        virtual /* [id][propget] */ HRESULT STDMETHODCALLTYPE get_PasswordRequired( 
            /* [retval][out] */ VARIANT_BOOL __RPC_FAR *retval) = 0;
        
        virtual /* [id][propput] */ HRESULT STDMETHODCALLTYPE put_PasswordRequired( 
            /* [in] */ VARIANT_BOOL fPasswordRequired) = 0;
        
        virtual /* [id][propget] */ HRESULT STDMETHODCALLTYPE get_RequireUniquePassword( 
            /* [retval][out] */ VARIANT_BOOL __RPC_FAR *retval) = 0;
        
        virtual /* [id][propput] */ HRESULT STDMETHODCALLTYPE put_RequireUniquePassword( 
            /* [in] */ VARIANT_BOOL fRequireUniquePassword) = 0;
        
        virtual /* [id][propget] */ HRESULT STDMETHODCALLTYPE get_EmailAddress( 
            /* [retval][out] */ BSTR __RPC_FAR *retval) = 0;
        
        virtual /* [id][propput] */ HRESULT STDMETHODCALLTYPE put_EmailAddress( 
            /* [in] */ BSTR bstrEmailAddress) = 0;
        
        virtual /* [id][propget] */ HRESULT STDMETHODCALLTYPE get_HomeDirectory( 
            /* [retval][out] */ BSTR __RPC_FAR *retval) = 0;
        
        virtual /* [id][propput] */ HRESULT STDMETHODCALLTYPE put_HomeDirectory( 
            /* [in] */ BSTR bstrHomeDirectory) = 0;
        
        virtual /* [id][propget] */ HRESULT STDMETHODCALLTYPE get_Languages( 
            /* [retval][out] */ VARIANT __RPC_FAR *retval) = 0;
        
        virtual /* [id][propput] */ HRESULT STDMETHODCALLTYPE put_Languages( 
            /* [in] */ VARIANT vLanguages) = 0;
        
        virtual /* [id][propget] */ HRESULT STDMETHODCALLTYPE get_Profile( 
            /* [retval][out] */ BSTR __RPC_FAR *retval) = 0;
        
        virtual /* [id][propput] */ HRESULT STDMETHODCALLTYPE put_Profile( 
            /* [in] */ BSTR bstrProfile) = 0;
        
        virtual /* [id][propget] */ HRESULT STDMETHODCALLTYPE get_LoginScript( 
            /* [retval][out] */ BSTR __RPC_FAR *retval) = 0;
        
        virtual /* [id][propput] */ HRESULT STDMETHODCALLTYPE put_LoginScript( 
            /* [in] */ BSTR bstrLoginScript) = 0;
        
        virtual /* [id][propget] */ HRESULT STDMETHODCALLTYPE get_Picture( 
            /* [retval][out] */ VARIANT __RPC_FAR *retval) = 0;
        
        virtual /* [id][propput] */ HRESULT STDMETHODCALLTYPE put_Picture( 
            /* [in] */ VARIANT vPicture) = 0;
        
        virtual /* [id][propget] */ HRESULT STDMETHODCALLTYPE get_HomePage( 
            /* [retval][out] */ BSTR __RPC_FAR *retval) = 0;
        
        virtual /* [id][propput] */ HRESULT STDMETHODCALLTYPE put_HomePage( 
            /* [in] */ BSTR bstrHomePage) = 0;
        
        virtual /* [id] */ HRESULT STDMETHODCALLTYPE Groups( 
            /* [retval][out] */ IADsMembers __RPC_FAR *__RPC_FAR *ppGroups) = 0;
        
        virtual /* [id] */ HRESULT STDMETHODCALLTYPE SetPassword( 
            /* [in] */ BSTR NewPassword) = 0;
        
        virtual /* [id] */ HRESULT STDMETHODCALLTYPE ChangePassword( 
            /* [in] */ BSTR bstrOldPassword,
            /* [in] */ BSTR bstrNewPassword) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IADsUserVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            IADsUser __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            IADsUser __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            IADsUser __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfoCount )( 
            IADsUser __RPC_FAR * This,
            /* [out] */ UINT __RPC_FAR *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfo )( 
            IADsUser __RPC_FAR * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo __RPC_FAR *__RPC_FAR *ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetIDsOfNames )( 
            IADsUser __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR __RPC_FAR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID __RPC_FAR *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Invoke )( 
            IADsUser __RPC_FAR * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS __RPC_FAR *pDispParams,
            /* [out] */ VARIANT __RPC_FAR *pVarResult,
            /* [out] */ EXCEPINFO __RPC_FAR *pExcepInfo,
            /* [out] */ UINT __RPC_FAR *puArgErr);
        
        /* [id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Name )( 
            IADsUser __RPC_FAR * This,
            /* [retval][out] */ BSTR __RPC_FAR *retval);
        
        /* [id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Class )( 
            IADsUser __RPC_FAR * This,
            /* [retval][out] */ BSTR __RPC_FAR *retval);
        
        /* [id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_GUID )( 
            IADsUser __RPC_FAR * This,
            /* [retval][out] */ BSTR __RPC_FAR *retval);
        
        /* [id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_ADsPath )( 
            IADsUser __RPC_FAR * This,
            /* [retval][out] */ BSTR __RPC_FAR *retval);
        
        /* [id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Parent )( 
            IADsUser __RPC_FAR * This,
            /* [retval][out] */ BSTR __RPC_FAR *retval);
        
        /* [id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Schema )( 
            IADsUser __RPC_FAR * This,
            /* [retval][out] */ BSTR __RPC_FAR *retval);
        
        /* [id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetInfo )( 
            IADsUser __RPC_FAR * This);
        
        /* [id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *SetInfo )( 
            IADsUser __RPC_FAR * This);
        
        /* [id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Get )( 
            IADsUser __RPC_FAR * This,
            /* [in] */ BSTR bstrName,
            /* [retval][out] */ VARIANT __RPC_FAR *pvProp);
        
        /* [id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Put )( 
            IADsUser __RPC_FAR * This,
            /* [in] */ BSTR bstrName,
            /* [in] */ VARIANT vProp);
        
        /* [id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetEx )( 
            IADsUser __RPC_FAR * This,
            /* [in] */ BSTR bstrName,
            /* [retval][out] */ VARIANT __RPC_FAR *pvProp);
        
        /* [id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *PutEx )( 
            IADsUser __RPC_FAR * This,
            /* [in] */ long lnControlCode,
            /* [in] */ BSTR bstrName,
            /* [in] */ VARIANT vProp);
        
        /* [id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetInfoEx )( 
            IADsUser __RPC_FAR * This,
            /* [in] */ VARIANT vProperties,
            /* [in] */ long lnReserved);
        
        /* [id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_BadLoginAddress )( 
            IADsUser __RPC_FAR * This,
            /* [retval][out] */ BSTR __RPC_FAR *retval);
        
        /* [id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_BadLoginCount )( 
            IADsUser __RPC_FAR * This,
            /* [retval][out] */ long __RPC_FAR *retval);
        
        /* [id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_LastLogin )( 
            IADsUser __RPC_FAR * This,
            /* [retval][out] */ DATE __RPC_FAR *retval);
        
        /* [id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_LastLogoff )( 
            IADsUser __RPC_FAR * This,
            /* [retval][out] */ DATE __RPC_FAR *retval);
        
        /* [id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_LastFailedLogin )( 
            IADsUser __RPC_FAR * This,
            /* [retval][out] */ DATE __RPC_FAR *retval);
        
        /* [id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_PasswordLastChanged )( 
            IADsUser __RPC_FAR * This,
            /* [retval][out] */ DATE __RPC_FAR *retval);
        
        /* [id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Description )( 
            IADsUser __RPC_FAR * This,
            /* [retval][out] */ BSTR __RPC_FAR *retval);
        
        /* [id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_Description )( 
            IADsUser __RPC_FAR * This,
            /* [in] */ BSTR bstrDescription);
        
        /* [id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Division )( 
            IADsUser __RPC_FAR * This,
            /* [retval][out] */ BSTR __RPC_FAR *retval);
        
        /* [id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_Division )( 
            IADsUser __RPC_FAR * This,
            /* [in] */ BSTR bstrDivision);
        
        /* [id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Department )( 
            IADsUser __RPC_FAR * This,
            /* [retval][out] */ BSTR __RPC_FAR *retval);
        
        /* [id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_Department )( 
            IADsUser __RPC_FAR * This,
            /* [in] */ BSTR bstrDepartment);
        
        /* [id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_EmployeeID )( 
            IADsUser __RPC_FAR * This,
            /* [retval][out] */ BSTR __RPC_FAR *retval);
        
        /* [id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_EmployeeID )( 
            IADsUser __RPC_FAR * This,
            /* [in] */ BSTR bstrEmployeeID);
        
        /* [id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_FullName )( 
            IADsUser __RPC_FAR * This,
            /* [retval][out] */ BSTR __RPC_FAR *retval);
        
        /* [id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_FullName )( 
            IADsUser __RPC_FAR * This,
            /* [in] */ BSTR bstrFullName);
        
        /* [id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_FirstName )( 
            IADsUser __RPC_FAR * This,
            /* [retval][out] */ BSTR __RPC_FAR *retval);
        
        /* [id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_FirstName )( 
            IADsUser __RPC_FAR * This,
            /* [in] */ BSTR bstrFirstName);
        
        /* [id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_LastName )( 
            IADsUser __RPC_FAR * This,
            /* [retval][out] */ BSTR __RPC_FAR *retval);
        
        /* [id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_LastName )( 
            IADsUser __RPC_FAR * This,
            /* [in] */ BSTR bstrLastName);
        
        /* [id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_OtherName )( 
            IADsUser __RPC_FAR * This,
            /* [retval][out] */ BSTR __RPC_FAR *retval);
        
        /* [id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_OtherName )( 
            IADsUser __RPC_FAR * This,
            /* [in] */ BSTR bstrOtherName);
        
        /* [id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_NamePrefix )( 
            IADsUser __RPC_FAR * This,
            /* [retval][out] */ BSTR __RPC_FAR *retval);
        
        /* [id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_NamePrefix )( 
            IADsUser __RPC_FAR * This,
            /* [in] */ BSTR bstrNamePrefix);
        
        /* [id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_NameSuffix )( 
            IADsUser __RPC_FAR * This,
            /* [retval][out] */ BSTR __RPC_FAR *retval);
        
        /* [id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_NameSuffix )( 
            IADsUser __RPC_FAR * This,
            /* [in] */ BSTR bstrNameSuffix);
        
        /* [id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Title )( 
            IADsUser __RPC_FAR * This,
            /* [retval][out] */ BSTR __RPC_FAR *retval);
        
        /* [id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_Title )( 
            IADsUser __RPC_FAR * This,
            /* [in] */ BSTR bstrTitle);
        
        /* [id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Manager )( 
            IADsUser __RPC_FAR * This,
            /* [retval][out] */ BSTR __RPC_FAR *retval);
        
        /* [id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_Manager )( 
            IADsUser __RPC_FAR * This,
            /* [in] */ BSTR bstrManager);
        
        /* [id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_TelephoneHome )( 
            IADsUser __RPC_FAR * This,
            /* [retval][out] */ VARIANT __RPC_FAR *retval);
        
        /* [id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_TelephoneHome )( 
            IADsUser __RPC_FAR * This,
            /* [in] */ VARIANT vTelephoneHome);
        
        /* [id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_TelephoneMobile )( 
            IADsUser __RPC_FAR * This,
            /* [retval][out] */ VARIANT __RPC_FAR *retval);
        
        /* [id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_TelephoneMobile )( 
            IADsUser __RPC_FAR * This,
            /* [in] */ VARIANT vTelephoneMobile);
        
        /* [id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_TelephoneNumber )( 
            IADsUser __RPC_FAR * This,
            /* [retval][out] */ VARIANT __RPC_FAR *retval);
        
        /* [id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_TelephoneNumber )( 
            IADsUser __RPC_FAR * This,
            /* [in] */ VARIANT vTelephoneNumber);
        
        /* [id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_TelephonePager )( 
            IADsUser __RPC_FAR * This,
            /* [retval][out] */ VARIANT __RPC_FAR *retval);
        
        /* [id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_TelephonePager )( 
            IADsUser __RPC_FAR * This,
            /* [in] */ VARIANT vTelephonePager);
        
        /* [id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_FaxNumber )( 
            IADsUser __RPC_FAR * This,
            /* [retval][out] */ VARIANT __RPC_FAR *retval);
        
        /* [id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_FaxNumber )( 
            IADsUser __RPC_FAR * This,
            /* [in] */ VARIANT vFaxNumber);
        
        /* [id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_OfficeLocations )( 
            IADsUser __RPC_FAR * This,
            /* [retval][out] */ VARIANT __RPC_FAR *retval);
        
        /* [id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_OfficeLocations )( 
            IADsUser __RPC_FAR * This,
            /* [in] */ VARIANT vOfficeLocations);
        
        /* [id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_PostalAddresses )( 
            IADsUser __RPC_FAR * This,
            /* [retval][out] */ VARIANT __RPC_FAR *retval);
        
        /* [id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_PostalAddresses )( 
            IADsUser __RPC_FAR * This,
            /* [in] */ VARIANT vPostalAddresses);
        
        /* [id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_PostalCodes )( 
            IADsUser __RPC_FAR * This,
            /* [retval][out] */ VARIANT __RPC_FAR *retval);
        
        /* [id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_PostalCodes )( 
            IADsUser __RPC_FAR * This,
            /* [in] */ VARIANT vPostalCodes);
        
        /* [id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_SeeAlso )( 
            IADsUser __RPC_FAR * This,
            /* [retval][out] */ VARIANT __RPC_FAR *retval);
        
        /* [id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_SeeAlso )( 
            IADsUser __RPC_FAR * This,
            /* [in] */ VARIANT vSeeAlso);
        
        /* [id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_AccountDisabled )( 
            IADsUser __RPC_FAR * This,
            /* [retval][out] */ VARIANT_BOOL __RPC_FAR *retval);
        
        /* [id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_AccountDisabled )( 
            IADsUser __RPC_FAR * This,
            /* [in] */ VARIANT_BOOL fAccountDisabled);
        
        /* [id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_AccountExpirationDate )( 
            IADsUser __RPC_FAR * This,
            /* [retval][out] */ DATE __RPC_FAR *retval);
        
        /* [id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_AccountExpirationDate )( 
            IADsUser __RPC_FAR * This,
            /* [in] */ DATE daAccountExpirationDate);
        
        /* [id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_GraceLoginsAllowed )( 
            IADsUser __RPC_FAR * This,
            /* [retval][out] */ long __RPC_FAR *retval);
        
        /* [id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_GraceLoginsAllowed )( 
            IADsUser __RPC_FAR * This,
            /* [in] */ long lnGraceLoginsAllowed);
        
        /* [id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_GraceLoginsRemaining )( 
            IADsUser __RPC_FAR * This,
            /* [retval][out] */ long __RPC_FAR *retval);
        
        /* [id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_GraceLoginsRemaining )( 
            IADsUser __RPC_FAR * This,
            /* [in] */ long lnGraceLoginsRemaining);
        
        /* [id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_IsAccountLocked )( 
            IADsUser __RPC_FAR * This,
            /* [retval][out] */ VARIANT_BOOL __RPC_FAR *retval);
        
        /* [id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_IsAccountLocked )( 
            IADsUser __RPC_FAR * This,
            /* [in] */ VARIANT_BOOL fIsAccountLocked);
        
        /* [id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_LoginHours )( 
            IADsUser __RPC_FAR * This,
            /* [retval][out] */ VARIANT __RPC_FAR *retval);
        
        /* [id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_LoginHours )( 
            IADsUser __RPC_FAR * This,
            /* [in] */ VARIANT vLoginHours);
        
        /* [id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_LoginWorkstations )( 
            IADsUser __RPC_FAR * This,
            /* [retval][out] */ VARIANT __RPC_FAR *retval);
        
        /* [id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_LoginWorkstations )( 
            IADsUser __RPC_FAR * This,
            /* [in] */ VARIANT vLoginWorkstations);
        
        /* [id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_MaxLogins )( 
            IADsUser __RPC_FAR * This,
            /* [retval][out] */ long __RPC_FAR *retval);
        
        /* [id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_MaxLogins )( 
            IADsUser __RPC_FAR * This,
            /* [in] */ long lnMaxLogins);
        
        /* [id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_MaxStorage )( 
            IADsUser __RPC_FAR * This,
            /* [retval][out] */ long __RPC_FAR *retval);
        
        /* [id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_MaxStorage )( 
            IADsUser __RPC_FAR * This,
            /* [in] */ long lnMaxStorage);
        
        /* [id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_PasswordExpirationDate )( 
            IADsUser __RPC_FAR * This,
            /* [retval][out] */ DATE __RPC_FAR *retval);
        
        /* [id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_PasswordExpirationDate )( 
            IADsUser __RPC_FAR * This,
            /* [in] */ DATE daPasswordExpirationDate);
        
        /* [id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_PasswordMinimumLength )( 
            IADsUser __RPC_FAR * This,
            /* [retval][out] */ long __RPC_FAR *retval);
        
        /* [id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_PasswordMinimumLength )( 
            IADsUser __RPC_FAR * This,
            /* [in] */ long lnPasswordMinimumLength);
        
        /* [id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_PasswordRequired )( 
            IADsUser __RPC_FAR * This,
            /* [retval][out] */ VARIANT_BOOL __RPC_FAR *retval);
        
        /* [id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_PasswordRequired )( 
            IADsUser __RPC_FAR * This,
            /* [in] */ VARIANT_BOOL fPasswordRequired);
        
        /* [id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_RequireUniquePassword )( 
            IADsUser __RPC_FAR * This,
            /* [retval][out] */ VARIANT_BOOL __RPC_FAR *retval);
        
        /* [id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_RequireUniquePassword )( 
            IADsUser __RPC_FAR * This,
            /* [in] */ VARIANT_BOOL fRequireUniquePassword);
        
        /* [id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_EmailAddress )( 
            IADsUser __RPC_FAR * This,
            /* [retval][out] */ BSTR __RPC_FAR *retval);
        
        /* [id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_EmailAddress )( 
            IADsUser __RPC_FAR * This,
            /* [in] */ BSTR bstrEmailAddress);
        
        /* [id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_HomeDirectory )( 
            IADsUser __RPC_FAR * This,
            /* [retval][out] */ BSTR __RPC_FAR *retval);
        
        /* [id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_HomeDirectory )( 
            IADsUser __RPC_FAR * This,
            /* [in] */ BSTR bstrHomeDirectory);
        
        /* [id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Languages )( 
            IADsUser __RPC_FAR * This,
            /* [retval][out] */ VARIANT __RPC_FAR *retval);
        
        /* [id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_Languages )( 
            IADsUser __RPC_FAR * This,
            /* [in] */ VARIANT vLanguages);
        
        /* [id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Profile )( 
            IADsUser __RPC_FAR * This,
            /* [retval][out] */ BSTR __RPC_FAR *retval);
        
        /* [id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_Profile )( 
            IADsUser __RPC_FAR * This,
            /* [in] */ BSTR bstrProfile);
        
        /* [id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_LoginScript )( 
            IADsUser __RPC_FAR * This,
            /* [retval][out] */ BSTR __RPC_FAR *retval);
        
        /* [id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_LoginScript )( 
            IADsUser __RPC_FAR * This,
            /* [in] */ BSTR bstrLoginScript);
        
        /* [id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Picture )( 
            IADsUser __RPC_FAR * This,
            /* [retval][out] */ VARIANT __RPC_FAR *retval);
        
        /* [id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_Picture )( 
            IADsUser __RPC_FAR * This,
            /* [in] */ VARIANT vPicture);
        
        /* [id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_HomePage )( 
            IADsUser __RPC_FAR * This,
            /* [retval][out] */ BSTR __RPC_FAR *retval);
        
        /* [id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_HomePage )( 
            IADsUser __RPC_FAR * This,
            /* [in] */ BSTR bstrHomePage);
        
        /* [id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Groups )( 
            IADsUser __RPC_FAR * This,
            /* [retval][out] */ IADsMembers __RPC_FAR *__RPC_FAR *ppGroups);
        
        /* [id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *SetPassword )( 
            IADsUser __RPC_FAR * This,
            /* [in] */ BSTR NewPassword);
        
        /* [id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *ChangePassword )( 
            IADsUser __RPC_FAR * This,
            /* [in] */ BSTR bstrOldPassword,
            /* [in] */ BSTR bstrNewPassword);
        
        END_INTERFACE
    } IADsUserVtbl;

    interface IADsUser
    {
        CONST_VTBL struct IADsUserVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IADsUser_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IADsUser_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IADsUser_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IADsUser_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define IADsUser_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define IADsUser_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define IADsUser_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)


#define IADsUser_get_Name(This,retval)	\
    (This)->lpVtbl -> get_Name(This,retval)

#define IADsUser_get_Class(This,retval)	\
    (This)->lpVtbl -> get_Class(This,retval)

#define IADsUser_get_GUID(This,retval)	\
    (This)->lpVtbl -> get_GUID(This,retval)

#define IADsUser_get_ADsPath(This,retval)	\
    (This)->lpVtbl -> get_ADsPath(This,retval)

#define IADsUser_get_Parent(This,retval)	\
    (This)->lpVtbl -> get_Parent(This,retval)

#define IADsUser_get_Schema(This,retval)	\
    (This)->lpVtbl -> get_Schema(This,retval)

#define IADsUser_GetInfo(This)	\
    (This)->lpVtbl -> GetInfo(This)

#define IADsUser_SetInfo(This)	\
    (This)->lpVtbl -> SetInfo(This)

#define IADsUser_Get(This,bstrName,pvProp)	\
    (This)->lpVtbl -> Get(This,bstrName,pvProp)

#define IADsUser_Put(This,bstrName,vProp)	\
    (This)->lpVtbl -> Put(This,bstrName,vProp)

#define IADsUser_GetEx(This,bstrName,pvProp)	\
    (This)->lpVtbl -> GetEx(This,bstrName,pvProp)

#define IADsUser_PutEx(This,lnControlCode,bstrName,vProp)	\
    (This)->lpVtbl -> PutEx(This,lnControlCode,bstrName,vProp)

#define IADsUser_GetInfoEx(This,vProperties,lnReserved)	\
    (This)->lpVtbl -> GetInfoEx(This,vProperties,lnReserved)


#define IADsUser_get_BadLoginAddress(This,retval)	\
    (This)->lpVtbl -> get_BadLoginAddress(This,retval)

#define IADsUser_get_BadLoginCount(This,retval)	\
    (This)->lpVtbl -> get_BadLoginCount(This,retval)

#define IADsUser_get_LastLogin(This,retval)	\
    (This)->lpVtbl -> get_LastLogin(This,retval)

#define IADsUser_get_LastLogoff(This,retval)	\
    (This)->lpVtbl -> get_LastLogoff(This,retval)

#define IADsUser_get_LastFailedLogin(This,retval)	\
    (This)->lpVtbl -> get_LastFailedLogin(This,retval)

#define IADsUser_get_PasswordLastChanged(This,retval)	\
    (This)->lpVtbl -> get_PasswordLastChanged(This,retval)

#define IADsUser_get_Description(This,retval)	\
    (This)->lpVtbl -> get_Description(This,retval)

#define IADsUser_put_Description(This,bstrDescription)	\
    (This)->lpVtbl -> put_Description(This,bstrDescription)

#define IADsUser_get_Division(This,retval)	\
    (This)->lpVtbl -> get_Division(This,retval)

#define IADsUser_put_Division(This,bstrDivision)	\
    (This)->lpVtbl -> put_Division(This,bstrDivision)

#define IADsUser_get_Department(This,retval)	\
    (This)->lpVtbl -> get_Department(This,retval)

#define IADsUser_put_Department(This,bstrDepartment)	\
    (This)->lpVtbl -> put_Department(This,bstrDepartment)

#define IADsUser_get_EmployeeID(This,retval)	\
    (This)->lpVtbl -> get_EmployeeID(This,retval)

#define IADsUser_put_EmployeeID(This,bstrEmployeeID)	\
    (This)->lpVtbl -> put_EmployeeID(This,bstrEmployeeID)

#define IADsUser_get_FullName(This,retval)	\
    (This)->lpVtbl -> get_FullName(This,retval)

#define IADsUser_put_FullName(This,bstrFullName)	\
    (This)->lpVtbl -> put_FullName(This,bstrFullName)

#define IADsUser_get_FirstName(This,retval)	\
    (This)->lpVtbl -> get_FirstName(This,retval)

#define IADsUser_put_FirstName(This,bstrFirstName)	\
    (This)->lpVtbl -> put_FirstName(This,bstrFirstName)

#define IADsUser_get_LastName(This,retval)	\
    (This)->lpVtbl -> get_LastName(This,retval)

#define IADsUser_put_LastName(This,bstrLastName)	\
    (This)->lpVtbl -> put_LastName(This,bstrLastName)

#define IADsUser_get_OtherName(This,retval)	\
    (This)->lpVtbl -> get_OtherName(This,retval)

#define IADsUser_put_OtherName(This,bstrOtherName)	\
    (This)->lpVtbl -> put_OtherName(This,bstrOtherName)

#define IADsUser_get_NamePrefix(This,retval)	\
    (This)->lpVtbl -> get_NamePrefix(This,retval)

#define IADsUser_put_NamePrefix(This,bstrNamePrefix)	\
    (This)->lpVtbl -> put_NamePrefix(This,bstrNamePrefix)

#define IADsUser_get_NameSuffix(This,retval)	\
    (This)->lpVtbl -> get_NameSuffix(This,retval)

#define IADsUser_put_NameSuffix(This,bstrNameSuffix)	\
    (This)->lpVtbl -> put_NameSuffix(This,bstrNameSuffix)

#define IADsUser_get_Title(This,retval)	\
    (This)->lpVtbl -> get_Title(This,retval)

#define IADsUser_put_Title(This,bstrTitle)	\
    (This)->lpVtbl -> put_Title(This,bstrTitle)

#define IADsUser_get_Manager(This,retval)	\
    (This)->lpVtbl -> get_Manager(This,retval)

#define IADsUser_put_Manager(This,bstrManager)	\
    (This)->lpVtbl -> put_Manager(This,bstrManager)

#define IADsUser_get_TelephoneHome(This,retval)	\
    (This)->lpVtbl -> get_TelephoneHome(This,retval)

#define IADsUser_put_TelephoneHome(This,vTelephoneHome)	\
    (This)->lpVtbl -> put_TelephoneHome(This,vTelephoneHome)

#define IADsUser_get_TelephoneMobile(This,retval)	\
    (This)->lpVtbl -> get_TelephoneMobile(This,retval)

#define IADsUser_put_TelephoneMobile(This,vTelephoneMobile)	\
    (This)->lpVtbl -> put_TelephoneMobile(This,vTelephoneMobile)

#define IADsUser_get_TelephoneNumber(This,retval)	\
    (This)->lpVtbl -> get_TelephoneNumber(This,retval)

#define IADsUser_put_TelephoneNumber(This,vTelephoneNumber)	\
    (This)->lpVtbl -> put_TelephoneNumber(This,vTelephoneNumber)

#define IADsUser_get_TelephonePager(This,retval)	\
    (This)->lpVtbl -> get_TelephonePager(This,retval)

#define IADsUser_put_TelephonePager(This,vTelephonePager)	\
    (This)->lpVtbl -> put_TelephonePager(This,vTelephonePager)

#define IADsUser_get_FaxNumber(This,retval)	\
    (This)->lpVtbl -> get_FaxNumber(This,retval)

#define IADsUser_put_FaxNumber(This,vFaxNumber)	\
    (This)->lpVtbl -> put_FaxNumber(This,vFaxNumber)

#define IADsUser_get_OfficeLocations(This,retval)	\
    (This)->lpVtbl -> get_OfficeLocations(This,retval)

#define IADsUser_put_OfficeLocations(This,vOfficeLocations)	\
    (This)->lpVtbl -> put_OfficeLocations(This,vOfficeLocations)

#define IADsUser_get_PostalAddresses(This,retval)	\
    (This)->lpVtbl -> get_PostalAddresses(This,retval)

#define IADsUser_put_PostalAddresses(This,vPostalAddresses)	\
    (This)->lpVtbl -> put_PostalAddresses(This,vPostalAddresses)

#define IADsUser_get_PostalCodes(This,retval)	\
    (This)->lpVtbl -> get_PostalCodes(This,retval)

#define IADsUser_put_PostalCodes(This,vPostalCodes)	\
    (This)->lpVtbl -> put_PostalCodes(This,vPostalCodes)

#define IADsUser_get_SeeAlso(This,retval)	\
    (This)->lpVtbl -> get_SeeAlso(This,retval)

#define IADsUser_put_SeeAlso(This,vSeeAlso)	\
    (This)->lpVtbl -> put_SeeAlso(This,vSeeAlso)

#define IADsUser_get_AccountDisabled(This,retval)	\
    (This)->lpVtbl -> get_AccountDisabled(This,retval)

#define IADsUser_put_AccountDisabled(This,fAccountDisabled)	\
    (This)->lpVtbl -> put_AccountDisabled(This,fAccountDisabled)

#define IADsUser_get_AccountExpirationDate(This,retval)	\
    (This)->lpVtbl -> get_AccountExpirationDate(This,retval)

#define IADsUser_put_AccountExpirationDate(This,daAccountExpirationDate)	\
    (This)->lpVtbl -> put_AccountExpirationDate(This,daAccountExpirationDate)

#define IADsUser_get_GraceLoginsAllowed(This,retval)	\
    (This)->lpVtbl -> get_GraceLoginsAllowed(This,retval)

#define IADsUser_put_GraceLoginsAllowed(This,lnGraceLoginsAllowed)	\
    (This)->lpVtbl -> put_GraceLoginsAllowed(This,lnGraceLoginsAllowed)

#define IADsUser_get_GraceLoginsRemaining(This,retval)	\
    (This)->lpVtbl -> get_GraceLoginsRemaining(This,retval)

#define IADsUser_put_GraceLoginsRemaining(This,lnGraceLoginsRemaining)	\
    (This)->lpVtbl -> put_GraceLoginsRemaining(This,lnGraceLoginsRemaining)

#define IADsUser_get_IsAccountLocked(This,retval)	\
    (This)->lpVtbl -> get_IsAccountLocked(This,retval)

#define IADsUser_put_IsAccountLocked(This,fIsAccountLocked)	\
    (This)->lpVtbl -> put_IsAccountLocked(This,fIsAccountLocked)

#define IADsUser_get_LoginHours(This,retval)	\
    (This)->lpVtbl -> get_LoginHours(This,retval)

#define IADsUser_put_LoginHours(This,vLoginHours)	\
    (This)->lpVtbl -> put_LoginHours(This,vLoginHours)

#define IADsUser_get_LoginWorkstations(This,retval)	\
    (This)->lpVtbl -> get_LoginWorkstations(This,retval)

#define IADsUser_put_LoginWorkstations(This,vLoginWorkstations)	\
    (This)->lpVtbl -> put_LoginWorkstations(This,vLoginWorkstations)

#define IADsUser_get_MaxLogins(This,retval)	\
    (This)->lpVtbl -> get_MaxLogins(This,retval)

#define IADsUser_put_MaxLogins(This,lnMaxLogins)	\
    (This)->lpVtbl -> put_MaxLogins(This,lnMaxLogins)

#define IADsUser_get_MaxStorage(This,retval)	\
    (This)->lpVtbl -> get_MaxStorage(This,retval)

#define IADsUser_put_MaxStorage(This,lnMaxStorage)	\
    (This)->lpVtbl -> put_MaxStorage(This,lnMaxStorage)

#define IADsUser_get_PasswordExpirationDate(This,retval)	\
    (This)->lpVtbl -> get_PasswordExpirationDate(This,retval)

#define IADsUser_put_PasswordExpirationDate(This,daPasswordExpirationDate)	\
    (This)->lpVtbl -> put_PasswordExpirationDate(This,daPasswordExpirationDate)

#define IADsUser_get_PasswordMinimumLength(This,retval)	\
    (This)->lpVtbl -> get_PasswordMinimumLength(This,retval)

#define IADsUser_put_PasswordMinimumLength(This,lnPasswordMinimumLength)	\
    (This)->lpVtbl -> put_PasswordMinimumLength(This,lnPasswordMinimumLength)

#define IADsUser_get_PasswordRequired(This,retval)	\
    (This)->lpVtbl -> get_PasswordRequired(This,retval)

#define IADsUser_put_PasswordRequired(This,fPasswordRequired)	\
    (This)->lpVtbl -> put_PasswordRequired(This,fPasswordRequired)

#define IADsUser_get_RequireUniquePassword(This,retval)	\
    (This)->lpVtbl -> get_RequireUniquePassword(This,retval)

#define IADsUser_put_RequireUniquePassword(This,fRequireUniquePassword)	\
    (This)->lpVtbl -> put_RequireUniquePassword(This,fRequireUniquePassword)

#define IADsUser_get_EmailAddress(This,retval)	\
    (This)->lpVtbl -> get_EmailAddress(This,retval)

#define IADsUser_put_EmailAddress(This,bstrEmailAddress)	\
    (This)->lpVtbl -> put_EmailAddress(This,bstrEmailAddress)

#define IADsUser_get_HomeDirectory(This,retval)	\
    (This)->lpVtbl -> get_HomeDirectory(This,retval)

#define IADsUser_put_HomeDirectory(This,bstrHomeDirectory)	\
    (This)->lpVtbl -> put_HomeDirectory(This,bstrHomeDirectory)

#define IADsUser_get_Languages(This,retval)	\
    (This)->lpVtbl -> get_Languages(This,retval)

#define IADsUser_put_Languages(This,vLanguages)	\
    (This)->lpVtbl -> put_Languages(This,vLanguages)

#define IADsUser_get_Profile(This,retval)	\
    (This)->lpVtbl -> get_Profile(This,retval)

#define IADsUser_put_Profile(This,bstrProfile)	\
    (This)->lpVtbl -> put_Profile(This,bstrProfile)

#define IADsUser_get_LoginScript(This,retval)	\
    (This)->lpVtbl -> get_LoginScript(This,retval)

#define IADsUser_put_LoginScript(This,bstrLoginScript)	\
    (This)->lpVtbl -> put_LoginScript(This,bstrLoginScript)

#define IADsUser_get_Picture(This,retval)	\
    (This)->lpVtbl -> get_Picture(This,retval)

#define IADsUser_put_Picture(This,vPicture)	\
    (This)->lpVtbl -> put_Picture(This,vPicture)

#define IADsUser_get_HomePage(This,retval)	\
    (This)->lpVtbl -> get_HomePage(This,retval)

#define IADsUser_put_HomePage(This,bstrHomePage)	\
    (This)->lpVtbl -> put_HomePage(This,bstrHomePage)

#define IADsUser_Groups(This,ppGroups)	\
    (This)->lpVtbl -> Groups(This,ppGroups)

#define IADsUser_SetPassword(This,NewPassword)	\
    (This)->lpVtbl -> SetPassword(This,NewPassword)

#define IADsUser_ChangePassword(This,bstrOldPassword,bstrNewPassword)	\
    (This)->lpVtbl -> ChangePassword(This,bstrOldPassword,bstrNewPassword)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [id][propget] */ HRESULT STDMETHODCALLTYPE IADsUser_get_BadLoginAddress_Proxy( 
    IADsUser __RPC_FAR * This,
    /* [retval][out] */ BSTR __RPC_FAR *retval);


void __RPC_STUB IADsUser_get_BadLoginAddress_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [id][propget] */ HRESULT STDMETHODCALLTYPE IADsUser_get_BadLoginCount_Proxy( 
    IADsUser __RPC_FAR * This,
    /* [retval][out] */ long __RPC_FAR *retval);


void __RPC_STUB IADsUser_get_BadLoginCount_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [id][propget] */ HRESULT STDMETHODCALLTYPE IADsUser_get_LastLogin_Proxy( 
    IADsUser __RPC_FAR * This,
    /* [retval][out] */ DATE __RPC_FAR *retval);


void __RPC_STUB IADsUser_get_LastLogin_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [id][propget] */ HRESULT STDMETHODCALLTYPE IADsUser_get_LastLogoff_Proxy( 
    IADsUser __RPC_FAR * This,
    /* [retval][out] */ DATE __RPC_FAR *retval);


void __RPC_STUB IADsUser_get_LastLogoff_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [id][propget] */ HRESULT STDMETHODCALLTYPE IADsUser_get_LastFailedLogin_Proxy( 
    IADsUser __RPC_FAR * This,
    /* [retval][out] */ DATE __RPC_FAR *retval);


void __RPC_STUB IADsUser_get_LastFailedLogin_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [id][propget] */ HRESULT STDMETHODCALLTYPE IADsUser_get_PasswordLastChanged_Proxy( 
    IADsUser __RPC_FAR * This,
    /* [retval][out] */ DATE __RPC_FAR *retval);


void __RPC_STUB IADsUser_get_PasswordLastChanged_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [id][propget] */ HRESULT STDMETHODCALLTYPE IADsUser_get_Description_Proxy( 
    IADsUser __RPC_FAR * This,
    /* [retval][out] */ BSTR __RPC_FAR *retval);


void __RPC_STUB IADsUser_get_Description_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [id][propput] */ HRESULT STDMETHODCALLTYPE IADsUser_put_Description_Proxy( 
    IADsUser __RPC_FAR * This,
    /* [in] */ BSTR bstrDescription);


void __RPC_STUB IADsUser_put_Description_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [id][propget] */ HRESULT STDMETHODCALLTYPE IADsUser_get_Division_Proxy( 
    IADsUser __RPC_FAR * This,
    /* [retval][out] */ BSTR __RPC_FAR *retval);


void __RPC_STUB IADsUser_get_Division_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [id][propput] */ HRESULT STDMETHODCALLTYPE IADsUser_put_Division_Proxy( 
    IADsUser __RPC_FAR * This,
    /* [in] */ BSTR bstrDivision);


void __RPC_STUB IADsUser_put_Division_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [id][propget] */ HRESULT STDMETHODCALLTYPE IADsUser_get_Department_Proxy( 
    IADsUser __RPC_FAR * This,
    /* [retval][out] */ BSTR __RPC_FAR *retval);


void __RPC_STUB IADsUser_get_Department_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [id][propput] */ HRESULT STDMETHODCALLTYPE IADsUser_put_Department_Proxy( 
    IADsUser __RPC_FAR * This,
    /* [in] */ BSTR bstrDepartment);


void __RPC_STUB IADsUser_put_Department_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [id][propget] */ HRESULT STDMETHODCALLTYPE IADsUser_get_EmployeeID_Proxy( 
    IADsUser __RPC_FAR * This,
    /* [retval][out] */ BSTR __RPC_FAR *retval);


void __RPC_STUB IADsUser_get_EmployeeID_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [id][propput] */ HRESULT STDMETHODCALLTYPE IADsUser_put_EmployeeID_Proxy( 
    IADsUser __RPC_FAR * This,
    /* [in] */ BSTR bstrEmployeeID);


void __RPC_STUB IADsUser_put_EmployeeID_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [id][propget] */ HRESULT STDMETHODCALLTYPE IADsUser_get_FullName_Proxy( 
    IADsUser __RPC_FAR * This,
    /* [retval][out] */ BSTR __RPC_FAR *retval);


void __RPC_STUB IADsUser_get_FullName_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [id][propput] */ HRESULT STDMETHODCALLTYPE IADsUser_put_FullName_Proxy( 
    IADsUser __RPC_FAR * This,
    /* [in] */ BSTR bstrFullName);


void __RPC_STUB IADsUser_put_FullName_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [id][propget] */ HRESULT STDMETHODCALLTYPE IADsUser_get_FirstName_Proxy( 
    IADsUser __RPC_FAR * This,
    /* [retval][out] */ BSTR __RPC_FAR *retval);


void __RPC_STUB IADsUser_get_FirstName_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [id][propput] */ HRESULT STDMETHODCALLTYPE IADsUser_put_FirstName_Proxy( 
    IADsUser __RPC_FAR * This,
    /* [in] */ BSTR bstrFirstName);


void __RPC_STUB IADsUser_put_FirstName_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [id][propget] */ HRESULT STDMETHODCALLTYPE IADsUser_get_LastName_Proxy( 
    IADsUser __RPC_FAR * This,
    /* [retval][out] */ BSTR __RPC_FAR *retval);


void __RPC_STUB IADsUser_get_LastName_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [id][propput] */ HRESULT STDMETHODCALLTYPE IADsUser_put_LastName_Proxy( 
    IADsUser __RPC_FAR * This,
    /* [in] */ BSTR bstrLastName);


void __RPC_STUB IADsUser_put_LastName_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [id][propget] */ HRESULT STDMETHODCALLTYPE IADsUser_get_OtherName_Proxy( 
    IADsUser __RPC_FAR * This,
    /* [retval][out] */ BSTR __RPC_FAR *retval);


void __RPC_STUB IADsUser_get_OtherName_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [id][propput] */ HRESULT STDMETHODCALLTYPE IADsUser_put_OtherName_Proxy( 
    IADsUser __RPC_FAR * This,
    /* [in] */ BSTR bstrOtherName);


void __RPC_STUB IADsUser_put_OtherName_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [id][propget] */ HRESULT STDMETHODCALLTYPE IADsUser_get_NamePrefix_Proxy( 
    IADsUser __RPC_FAR * This,
    /* [retval][out] */ BSTR __RPC_FAR *retval);


void __RPC_STUB IADsUser_get_NamePrefix_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [id][propput] */ HRESULT STDMETHODCALLTYPE IADsUser_put_NamePrefix_Proxy( 
    IADsUser __RPC_FAR * This,
    /* [in] */ BSTR bstrNamePrefix);


void __RPC_STUB IADsUser_put_NamePrefix_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [id][propget] */ HRESULT STDMETHODCALLTYPE IADsUser_get_NameSuffix_Proxy( 
    IADsUser __RPC_FAR * This,
    /* [retval][out] */ BSTR __RPC_FAR *retval);


void __RPC_STUB IADsUser_get_NameSuffix_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [id][propput] */ HRESULT STDMETHODCALLTYPE IADsUser_put_NameSuffix_Proxy( 
    IADsUser __RPC_FAR * This,
    /* [in] */ BSTR bstrNameSuffix);


void __RPC_STUB IADsUser_put_NameSuffix_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [id][propget] */ HRESULT STDMETHODCALLTYPE IADsUser_get_Title_Proxy( 
    IADsUser __RPC_FAR * This,
    /* [retval][out] */ BSTR __RPC_FAR *retval);


void __RPC_STUB IADsUser_get_Title_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [id][propput] */ HRESULT STDMETHODCALLTYPE IADsUser_put_Title_Proxy( 
    IADsUser __RPC_FAR * This,
    /* [in] */ BSTR bstrTitle);


void __RPC_STUB IADsUser_put_Title_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [id][propget] */ HRESULT STDMETHODCALLTYPE IADsUser_get_Manager_Proxy( 
    IADsUser __RPC_FAR * This,
    /* [retval][out] */ BSTR __RPC_FAR *retval);


void __RPC_STUB IADsUser_get_Manager_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [id][propput] */ HRESULT STDMETHODCALLTYPE IADsUser_put_Manager_Proxy( 
    IADsUser __RPC_FAR * This,
    /* [in] */ BSTR bstrManager);


void __RPC_STUB IADsUser_put_Manager_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [id][propget] */ HRESULT STDMETHODCALLTYPE IADsUser_get_TelephoneHome_Proxy( 
    IADsUser __RPC_FAR * This,
    /* [retval][out] */ VARIANT __RPC_FAR *retval);


void __RPC_STUB IADsUser_get_TelephoneHome_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [id][propput] */ HRESULT STDMETHODCALLTYPE IADsUser_put_TelephoneHome_Proxy( 
    IADsUser __RPC_FAR * This,
    /* [in] */ VARIANT vTelephoneHome);


void __RPC_STUB IADsUser_put_TelephoneHome_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [id][propget] */ HRESULT STDMETHODCALLTYPE IADsUser_get_TelephoneMobile_Proxy( 
    IADsUser __RPC_FAR * This,
    /* [retval][out] */ VARIANT __RPC_FAR *retval);


void __RPC_STUB IADsUser_get_TelephoneMobile_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [id][propput] */ HRESULT STDMETHODCALLTYPE IADsUser_put_TelephoneMobile_Proxy( 
    IADsUser __RPC_FAR * This,
    /* [in] */ VARIANT vTelephoneMobile);


void __RPC_STUB IADsUser_put_TelephoneMobile_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [id][propget] */ HRESULT STDMETHODCALLTYPE IADsUser_get_TelephoneNumber_Proxy( 
    IADsUser __RPC_FAR * This,
    /* [retval][out] */ VARIANT __RPC_FAR *retval);


void __RPC_STUB IADsUser_get_TelephoneNumber_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [id][propput] */ HRESULT STDMETHODCALLTYPE IADsUser_put_TelephoneNumber_Proxy( 
    IADsUser __RPC_FAR * This,
    /* [in] */ VARIANT vTelephoneNumber);


void __RPC_STUB IADsUser_put_TelephoneNumber_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [id][propget] */ HRESULT STDMETHODCALLTYPE IADsUser_get_TelephonePager_Proxy( 
    IADsUser __RPC_FAR * This,
    /* [retval][out] */ VARIANT __RPC_FAR *retval);


void __RPC_STUB IADsUser_get_TelephonePager_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [id][propput] */ HRESULT STDMETHODCALLTYPE IADsUser_put_TelephonePager_Proxy( 
    IADsUser __RPC_FAR * This,
    /* [in] */ VARIANT vTelephonePager);


void __RPC_STUB IADsUser_put_TelephonePager_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [id][propget] */ HRESULT STDMETHODCALLTYPE IADsUser_get_FaxNumber_Proxy( 
    IADsUser __RPC_FAR * This,
    /* [retval][out] */ VARIANT __RPC_FAR *retval);


void __RPC_STUB IADsUser_get_FaxNumber_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [id][propput] */ HRESULT STDMETHODCALLTYPE IADsUser_put_FaxNumber_Proxy( 
    IADsUser __RPC_FAR * This,
    /* [in] */ VARIANT vFaxNumber);


void __RPC_STUB IADsUser_put_FaxNumber_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [id][propget] */ HRESULT STDMETHODCALLTYPE IADsUser_get_OfficeLocations_Proxy( 
    IADsUser __RPC_FAR * This,
    /* [retval][out] */ VARIANT __RPC_FAR *retval);


void __RPC_STUB IADsUser_get_OfficeLocations_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [id][propput] */ HRESULT STDMETHODCALLTYPE IADsUser_put_OfficeLocations_Proxy( 
    IADsUser __RPC_FAR * This,
    /* [in] */ VARIANT vOfficeLocations);


void __RPC_STUB IADsUser_put_OfficeLocations_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [id][propget] */ HRESULT STDMETHODCALLTYPE IADsUser_get_PostalAddresses_Proxy( 
    IADsUser __RPC_FAR * This,
    /* [retval][out] */ VARIANT __RPC_FAR *retval);


void __RPC_STUB IADsUser_get_PostalAddresses_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [id][propput] */ HRESULT STDMETHODCALLTYPE IADsUser_put_PostalAddresses_Proxy( 
    IADsUser __RPC_FAR * This,
    /* [in] */ VARIANT vPostalAddresses);


void __RPC_STUB IADsUser_put_PostalAddresses_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [id][propget] */ HRESULT STDMETHODCALLTYPE IADsUser_get_PostalCodes_Proxy( 
    IADsUser __RPC_FAR * This,
    /* [retval][out] */ VARIANT __RPC_FAR *retval);


void __RPC_STUB IADsUser_get_PostalCodes_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [id][propput] */ HRESULT STDMETHODCALLTYPE IADsUser_put_PostalCodes_Proxy( 
    IADsUser __RPC_FAR * This,
    /* [in] */ VARIANT vPostalCodes);


void __RPC_STUB IADsUser_put_PostalCodes_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [id][propget] */ HRESULT STDMETHODCALLTYPE IADsUser_get_SeeAlso_Proxy( 
    IADsUser __RPC_FAR * This,
    /* [retval][out] */ VARIANT __RPC_FAR *retval);


void __RPC_STUB IADsUser_get_SeeAlso_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [id][propput] */ HRESULT STDMETHODCALLTYPE IADsUser_put_SeeAlso_Proxy( 
    IADsUser __RPC_FAR * This,
    /* [in] */ VARIANT vSeeAlso);


void __RPC_STUB IADsUser_put_SeeAlso_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [id][propget] */ HRESULT STDMETHODCALLTYPE IADsUser_get_AccountDisabled_Proxy( 
    IADsUser __RPC_FAR * This,
    /* [retval][out] */ VARIANT_BOOL __RPC_FAR *retval);


void __RPC_STUB IADsUser_get_AccountDisabled_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [id][propput] */ HRESULT STDMETHODCALLTYPE IADsUser_put_AccountDisabled_Proxy( 
    IADsUser __RPC_FAR * This,
    /* [in] */ VARIANT_BOOL fAccountDisabled);


void __RPC_STUB IADsUser_put_AccountDisabled_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [id][propget] */ HRESULT STDMETHODCALLTYPE IADsUser_get_AccountExpirationDate_Proxy( 
    IADsUser __RPC_FAR * This,
    /* [retval][out] */ DATE __RPC_FAR *retval);


void __RPC_STUB IADsUser_get_AccountExpirationDate_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [id][propput] */ HRESULT STDMETHODCALLTYPE IADsUser_put_AccountExpirationDate_Proxy( 
    IADsUser __RPC_FAR * This,
    /* [in] */ DATE daAccountExpirationDate);


void __RPC_STUB IADsUser_put_AccountExpirationDate_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [id][propget] */ HRESULT STDMETHODCALLTYPE IADsUser_get_GraceLoginsAllowed_Proxy( 
    IADsUser __RPC_FAR * This,
    /* [retval][out] */ long __RPC_FAR *retval);


void __RPC_STUB IADsUser_get_GraceLoginsAllowed_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [id][propput] */ HRESULT STDMETHODCALLTYPE IADsUser_put_GraceLoginsAllowed_Proxy( 
    IADsUser __RPC_FAR * This,
    /* [in] */ long lnGraceLoginsAllowed);


void __RPC_STUB IADsUser_put_GraceLoginsAllowed_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [id][propget] */ HRESULT STDMETHODCALLTYPE IADsUser_get_GraceLoginsRemaining_Proxy( 
    IADsUser __RPC_FAR * This,
    /* [retval][out] */ long __RPC_FAR *retval);


void __RPC_STUB IADsUser_get_GraceLoginsRemaining_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [id][propput] */ HRESULT STDMETHODCALLTYPE IADsUser_put_GraceLoginsRemaining_Proxy( 
    IADsUser __RPC_FAR * This,
    /* [in] */ long lnGraceLoginsRemaining);


void __RPC_STUB IADsUser_put_GraceLoginsRemaining_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [id][propget] */ HRESULT STDMETHODCALLTYPE IADsUser_get_IsAccountLocked_Proxy( 
    IADsUser __RPC_FAR * This,
    /* [retval][out] */ VARIANT_BOOL __RPC_FAR *retval);


void __RPC_STUB IADsUser_get_IsAccountLocked_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [id][propput] */ HRESULT STDMETHODCALLTYPE IADsUser_put_IsAccountLocked_Proxy( 
    IADsUser __RPC_FAR * This,
    /* [in] */ VARIANT_BOOL fIsAccountLocked);


void __RPC_STUB IADsUser_put_IsAccountLocked_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [id][propget] */ HRESULT STDMETHODCALLTYPE IADsUser_get_LoginHours_Proxy( 
    IADsUser __RPC_FAR * This,
    /* [retval][out] */ VARIANT __RPC_FAR *retval);


void __RPC_STUB IADsUser_get_LoginHours_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [id][propput] */ HRESULT STDMETHODCALLTYPE IADsUser_put_LoginHours_Proxy( 
    IADsUser __RPC_FAR * This,
    /* [in] */ VARIANT vLoginHours);


void __RPC_STUB IADsUser_put_LoginHours_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [id][propget] */ HRESULT STDMETHODCALLTYPE IADsUser_get_LoginWorkstations_Proxy( 
    IADsUser __RPC_FAR * This,
    /* [retval][out] */ VARIANT __RPC_FAR *retval);


void __RPC_STUB IADsUser_get_LoginWorkstations_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [id][propput] */ HRESULT STDMETHODCALLTYPE IADsUser_put_LoginWorkstations_Proxy( 
    IADsUser __RPC_FAR * This,
    /* [in] */ VARIANT vLoginWorkstations);


void __RPC_STUB IADsUser_put_LoginWorkstations_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [id][propget] */ HRESULT STDMETHODCALLTYPE IADsUser_get_MaxLogins_Proxy( 
    IADsUser __RPC_FAR * This,
    /* [retval][out] */ long __RPC_FAR *retval);


void __RPC_STUB IADsUser_get_MaxLogins_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [id][propput] */ HRESULT STDMETHODCALLTYPE IADsUser_put_MaxLogins_Proxy( 
    IADsUser __RPC_FAR * This,
    /* [in] */ long lnMaxLogins);


void __RPC_STUB IADsUser_put_MaxLogins_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [id][propget] */ HRESULT STDMETHODCALLTYPE IADsUser_get_MaxStorage_Proxy( 
    IADsUser __RPC_FAR * This,
    /* [retval][out] */ long __RPC_FAR *retval);


void __RPC_STUB IADsUser_get_MaxStorage_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [id][propput] */ HRESULT STDMETHODCALLTYPE IADsUser_put_MaxStorage_Proxy( 
    IADsUser __RPC_FAR * This,
    /* [in] */ long lnMaxStorage);


void __RPC_STUB IADsUser_put_MaxStorage_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [id][propget] */ HRESULT STDMETHODCALLTYPE IADsUser_get_PasswordExpirationDate_Proxy( 
    IADsUser __RPC_FAR * This,
    /* [retval][out] */ DATE __RPC_FAR *retval);


void __RPC_STUB IADsUser_get_PasswordExpirationDate_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [id][propput] */ HRESULT STDMETHODCALLTYPE IADsUser_put_PasswordExpirationDate_Proxy( 
    IADsUser __RPC_FAR * This,
    /* [in] */ DATE daPasswordExpirationDate);


void __RPC_STUB IADsUser_put_PasswordExpirationDate_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [id][propget] */ HRESULT STDMETHODCALLTYPE IADsUser_get_PasswordMinimumLength_Proxy( 
    IADsUser __RPC_FAR * This,
    /* [retval][out] */ long __RPC_FAR *retval);


void __RPC_STUB IADsUser_get_PasswordMinimumLength_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [id][propput] */ HRESULT STDMETHODCALLTYPE IADsUser_put_PasswordMinimumLength_Proxy( 
    IADsUser __RPC_FAR * This,
    /* [in] */ long lnPasswordMinimumLength);


void __RPC_STUB IADsUser_put_PasswordMinimumLength_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [id][propget] */ HRESULT STDMETHODCALLTYPE IADsUser_get_PasswordRequired_Proxy( 
    IADsUser __RPC_FAR * This,
    /* [retval][out] */ VARIANT_BOOL __RPC_FAR *retval);


void __RPC_STUB IADsUser_get_PasswordRequired_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [id][propput] */ HRESULT STDMETHODCALLTYPE IADsUser_put_PasswordRequired_Proxy( 
    IADsUser __RPC_FAR * This,
    /* [in] */ VARIANT_BOOL fPasswordRequired);


void __RPC_STUB IADsUser_put_PasswordRequired_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [id][propget] */ HRESULT STDMETHODCALLTYPE IADsUser_get_RequireUniquePassword_Proxy( 
    IADsUser __RPC_FAR * This,
    /* [retval][out] */ VARIANT_BOOL __RPC_FAR *retval);


void __RPC_STUB IADsUser_get_RequireUniquePassword_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [id][propput] */ HRESULT STDMETHODCALLTYPE IADsUser_put_RequireUniquePassword_Proxy( 
    IADsUser __RPC_FAR * This,
    /* [in] */ VARIANT_BOOL fRequireUniquePassword);


void __RPC_STUB IADsUser_put_RequireUniquePassword_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [id][propget] */ HRESULT STDMETHODCALLTYPE IADsUser_get_EmailAddress_Proxy( 
    IADsUser __RPC_FAR * This,
    /* [retval][out] */ BSTR __RPC_FAR *retval);


void __RPC_STUB IADsUser_get_EmailAddress_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [id][propput] */ HRESULT STDMETHODCALLTYPE IADsUser_put_EmailAddress_Proxy( 
    IADsUser __RPC_FAR * This,
    /* [in] */ BSTR bstrEmailAddress);


void __RPC_STUB IADsUser_put_EmailAddress_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [id][propget] */ HRESULT STDMETHODCALLTYPE IADsUser_get_HomeDirectory_Proxy( 
    IADsUser __RPC_FAR * This,
    /* [retval][out] */ BSTR __RPC_FAR *retval);


void __RPC_STUB IADsUser_get_HomeDirectory_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [id][propput] */ HRESULT STDMETHODCALLTYPE IADsUser_put_HomeDirectory_Proxy( 
    IADsUser __RPC_FAR * This,
    /* [in] */ BSTR bstrHomeDirectory);


void __RPC_STUB IADsUser_put_HomeDirectory_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [id][propget] */ HRESULT STDMETHODCALLTYPE IADsUser_get_Languages_Proxy( 
    IADsUser __RPC_FAR * This,
    /* [retval][out] */ VARIANT __RPC_FAR *retval);


void __RPC_STUB IADsUser_get_Languages_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [id][propput] */ HRESULT STDMETHODCALLTYPE IADsUser_put_Languages_Proxy( 
    IADsUser __RPC_FAR * This,
    /* [in] */ VARIANT vLanguages);


void __RPC_STUB IADsUser_put_Languages_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [id][propget] */ HRESULT STDMETHODCALLTYPE IADsUser_get_Profile_Proxy( 
    IADsUser __RPC_FAR * This,
    /* [retval][out] */ BSTR __RPC_FAR *retval);


void __RPC_STUB IADsUser_get_Profile_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [id][propput] */ HRESULT STDMETHODCALLTYPE IADsUser_put_Profile_Proxy( 
    IADsUser __RPC_FAR * This,
    /* [in] */ BSTR bstrProfile);


void __RPC_STUB IADsUser_put_Profile_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [id][propget] */ HRESULT STDMETHODCALLTYPE IADsUser_get_LoginScript_Proxy( 
    IADsUser __RPC_FAR * This,
    /* [retval][out] */ BSTR __RPC_FAR *retval);


void __RPC_STUB IADsUser_get_LoginScript_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [id][propput] */ HRESULT STDMETHODCALLTYPE IADsUser_put_LoginScript_Proxy( 
    IADsUser __RPC_FAR * This,
    /* [in] */ BSTR bstrLoginScript);


void __RPC_STUB IADsUser_put_LoginScript_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [id][propget] */ HRESULT STDMETHODCALLTYPE IADsUser_get_Picture_Proxy( 
    IADsUser __RPC_FAR * This,
    /* [retval][out] */ VARIANT __RPC_FAR *retval);


void __RPC_STUB IADsUser_get_Picture_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [id][propput] */ HRESULT STDMETHODCALLTYPE IADsUser_put_Picture_Proxy( 
    IADsUser __RPC_FAR * This,
    /* [in] */ VARIANT vPicture);


void __RPC_STUB IADsUser_put_Picture_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [id][propget] */ HRESULT STDMETHODCALLTYPE IADsUser_get_HomePage_Proxy( 
    IADsUser __RPC_FAR * This,
    /* [retval][out] */ BSTR __RPC_FAR *retval);


void __RPC_STUB IADsUser_get_HomePage_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [id][propput] */ HRESULT STDMETHODCALLTYPE IADsUser_put_HomePage_Proxy( 
    IADsUser __RPC_FAR * This,
    /* [in] */ BSTR bstrHomePage);


void __RPC_STUB IADsUser_put_HomePage_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [id] */ HRESULT STDMETHODCALLTYPE IADsUser_Groups_Proxy( 
    IADsUser __RPC_FAR * This,
    /* [retval][out] */ IADsMembers __RPC_FAR *__RPC_FAR *ppGroups);


void __RPC_STUB IADsUser_Groups_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [id] */ HRESULT STDMETHODCALLTYPE IADsUser_SetPassword_Proxy( 
    IADsUser __RPC_FAR * This,
    /* [in] */ BSTR NewPassword);


void __RPC_STUB IADsUser_SetPassword_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [id] */ HRESULT STDMETHODCALLTYPE IADsUser_ChangePassword_Proxy( 
    IADsUser __RPC_FAR * This,
    /* [in] */ BSTR bstrOldPassword,
    /* [in] */ BSTR bstrNewPassword);


void __RPC_STUB IADsUser_ChangePassword_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IADsUser_INTERFACE_DEFINED__ */


#ifndef __IADsPrintQueue_INTERFACE_DEFINED__
#define __IADsPrintQueue_INTERFACE_DEFINED__

/****************************************
 * Generated header for interface: IADsPrintQueue
 * at Mon Oct 13 13:47:30 1997
 * using MIDL 3.00.44
 ****************************************/
/* [object][dual][oleautomation][uuid] */ 



EXTERN_C const IID IID_IADsPrintQueue;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    interface IADsPrintQueue : public IADs
    {
    public:
        virtual /* [id][propget] */ HRESULT STDMETHODCALLTYPE get_PrinterPath( 
            /* [retval][out] */ BSTR __RPC_FAR *retval) = 0;
        
        virtual /* [id][propput] */ HRESULT STDMETHODCALLTYPE put_PrinterPath( 
            /* [in] */ BSTR bstrPrinterPath) = 0;
        
        virtual /* [id][propget] */ HRESULT STDMETHODCALLTYPE get_Model( 
            /* [retval][out] */ BSTR __RPC_FAR *retval) = 0;
        
        virtual /* [id][propput] */ HRESULT STDMETHODCALLTYPE put_Model( 
            /* [in] */ BSTR bstrModel) = 0;
        
        virtual /* [id][propget] */ HRESULT STDMETHODCALLTYPE get_Datatype( 
            /* [retval][out] */ BSTR __RPC_FAR *retval) = 0;
        
        virtual /* [id][propput] */ HRESULT STDMETHODCALLTYPE put_Datatype( 
            /* [in] */ BSTR bstrDatatype) = 0;
        
        virtual /* [id][propget] */ HRESULT STDMETHODCALLTYPE get_PrintProcessor( 
            /* [retval][out] */ BSTR __RPC_FAR *retval) = 0;
        
        virtual /* [id][propput] */ HRESULT STDMETHODCALLTYPE put_PrintProcessor( 
            /* [in] */ BSTR bstrPrintProcessor) = 0;
        
        virtual /* [id][propget] */ HRESULT STDMETHODCALLTYPE get_Description( 
            /* [retval][out] */ BSTR __RPC_FAR *retval) = 0;
        
        virtual /* [id][propput] */ HRESULT STDMETHODCALLTYPE put_Description( 
            /* [in] */ BSTR bstrDescription) = 0;
        
        virtual /* [id][propget] */ HRESULT STDMETHODCALLTYPE get_Location( 
            /* [retval][out] */ BSTR __RPC_FAR *retval) = 0;
        
        virtual /* [id][propput] */ HRESULT STDMETHODCALLTYPE put_Location( 
            /* [in] */ BSTR bstrLocation) = 0;
        
        virtual /* [id][propget] */ HRESULT STDMETHODCALLTYPE get_StartTime( 
            /* [retval][out] */ DATE __RPC_FAR *retval) = 0;
        
        virtual /* [id][propput] */ HRESULT STDMETHODCALLTYPE put_StartTime( 
            /* [in] */ DATE daStartTime) = 0;
        
        virtual /* [id][propget] */ HRESULT STDMETHODCALLTYPE get_UntilTime( 
            /* [retval][out] */ DATE __RPC_FAR *retval) = 0;
        
        virtual /* [id][propput] */ HRESULT STDMETHODCALLTYPE put_UntilTime( 
            /* [in] */ DATE daUntilTime) = 0;
        
        virtual /* [id][propget] */ HRESULT STDMETHODCALLTYPE get_DefaultJobPriority( 
            /* [retval][out] */ long __RPC_FAR *retval) = 0;
        
        virtual /* [id][propput] */ HRESULT STDMETHODCALLTYPE put_DefaultJobPriority( 
            /* [in] */ long lnDefaultJobPriority) = 0;
        
        virtual /* [id][propget] */ HRESULT STDMETHODCALLTYPE get_Priority( 
            /* [retval][out] */ long __RPC_FAR *retval) = 0;
        
        virtual /* [id][propput] */ HRESULT STDMETHODCALLTYPE put_Priority( 
            /* [in] */ long lnPriority) = 0;
        
        virtual /* [id][propget] */ HRESULT STDMETHODCALLTYPE get_BannerPage( 
            /* [retval][out] */ BSTR __RPC_FAR *retval) = 0;
        
        virtual /* [id][propput] */ HRESULT STDMETHODCALLTYPE put_BannerPage( 
            /* [in] */ BSTR bstrBannerPage) = 0;
        
        virtual /* [id][propget] */ HRESULT STDMETHODCALLTYPE get_PrintDevices( 
            /* [retval][out] */ VARIANT __RPC_FAR *retval) = 0;
        
        virtual /* [id][propput] */ HRESULT STDMETHODCALLTYPE put_PrintDevices( 
            /* [in] */ VARIANT vPrintDevices) = 0;
        
        virtual /* [id][propget] */ HRESULT STDMETHODCALLTYPE get_NetAddresses( 
            /* [retval][out] */ VARIANT __RPC_FAR *retval) = 0;
        
        virtual /* [id][propput] */ HRESULT STDMETHODCALLTYPE put_NetAddresses( 
            /* [in] */ VARIANT vNetAddresses) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IADsPrintQueueVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            IADsPrintQueue __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            IADsPrintQueue __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            IADsPrintQueue __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfoCount )( 
            IADsPrintQueue __RPC_FAR * This,
            /* [out] */ UINT __RPC_FAR *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfo )( 
            IADsPrintQueue __RPC_FAR * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo __RPC_FAR *__RPC_FAR *ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetIDsOfNames )( 
            IADsPrintQueue __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR __RPC_FAR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID __RPC_FAR *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Invoke )( 
            IADsPrintQueue __RPC_FAR * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS __RPC_FAR *pDispParams,
            /* [out] */ VARIANT __RPC_FAR *pVarResult,
            /* [out] */ EXCEPINFO __RPC_FAR *pExcepInfo,
            /* [out] */ UINT __RPC_FAR *puArgErr);
        
        /* [id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Name )( 
            IADsPrintQueue __RPC_FAR * This,
            /* [retval][out] */ BSTR __RPC_FAR *retval);
        
        /* [id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Class )( 
            IADsPrintQueue __RPC_FAR * This,
            /* [retval][out] */ BSTR __RPC_FAR *retval);
        
        /* [id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_GUID )( 
            IADsPrintQueue __RPC_FAR * This,
            /* [retval][out] */ BSTR __RPC_FAR *retval);
        
        /* [id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_ADsPath )( 
            IADsPrintQueue __RPC_FAR * This,
            /* [retval][out] */ BSTR __RPC_FAR *retval);
        
        /* [id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Parent )( 
            IADsPrintQueue __RPC_FAR * This,
            /* [retval][out] */ BSTR __RPC_FAR *retval);
        
        /* [id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Schema )( 
            IADsPrintQueue __RPC_FAR * This,
            /* [retval][out] */ BSTR __RPC_FAR *retval);
        
        /* [id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetInfo )( 
            IADsPrintQueue __RPC_FAR * This);
        
        /* [id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *SetInfo )( 
            IADsPrintQueue __RPC_FAR * This);
        
        /* [id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Get )( 
            IADsPrintQueue __RPC_FAR * This,
            /* [in] */ BSTR bstrName,
            /* [retval][out] */ VARIANT __RPC_FAR *pvProp);
        
        /* [id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Put )( 
            IADsPrintQueue __RPC_FAR * This,
            /* [in] */ BSTR bstrName,
            /* [in] */ VARIANT vProp);
        
        /* [id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetEx )( 
            IADsPrintQueue __RPC_FAR * This,
            /* [in] */ BSTR bstrName,
            /* [retval][out] */ VARIANT __RPC_FAR *pvProp);
        
        /* [id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *PutEx )( 
            IADsPrintQueue __RPC_FAR * This,
            /* [in] */ long lnControlCode,
            /* [in] */ BSTR bstrName,
            /* [in] */ VARIANT vProp);
        
        /* [id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetInfoEx )( 
            IADsPrintQueue __RPC_FAR * This,
            /* [in] */ VARIANT vProperties,
            /* [in] */ long lnReserved);
        
        /* [id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_PrinterPath )( 
            IADsPrintQueue __RPC_FAR * This,
            /* [retval][out] */ BSTR __RPC_FAR *retval);
        
        /* [id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_PrinterPath )( 
            IADsPrintQueue __RPC_FAR * This,
            /* [in] */ BSTR bstrPrinterPath);
        
        /* [id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Model )( 
            IADsPrintQueue __RPC_FAR * This,
            /* [retval][out] */ BSTR __RPC_FAR *retval);
        
        /* [id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_Model )( 
            IADsPrintQueue __RPC_FAR * This,
            /* [in] */ BSTR bstrModel);
        
        /* [id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Datatype )( 
            IADsPrintQueue __RPC_FAR * This,
            /* [retval][out] */ BSTR __RPC_FAR *retval);
        
        /* [id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_Datatype )( 
            IADsPrintQueue __RPC_FAR * This,
            /* [in] */ BSTR bstrDatatype);
        
        /* [id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_PrintProcessor )( 
            IADsPrintQueue __RPC_FAR * This,
            /* [retval][out] */ BSTR __RPC_FAR *retval);
        
        /* [id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_PrintProcessor )( 
            IADsPrintQueue __RPC_FAR * This,
            /* [in] */ BSTR bstrPrintProcessor);
        
        /* [id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Description )( 
            IADsPrintQueue __RPC_FAR * This,
            /* [retval][out] */ BSTR __RPC_FAR *retval);
        
        /* [id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_Description )( 
            IADsPrintQueue __RPC_FAR * This,
            /* [in] */ BSTR bstrDescription);
        
        /* [id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Location )( 
            IADsPrintQueue __RPC_FAR * This,
            /* [retval][out] */ BSTR __RPC_FAR *retval);
        
        /* [id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_Location )( 
            IADsPrintQueue __RPC_FAR * This,
            /* [in] */ BSTR bstrLocation);
        
        /* [id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_StartTime )( 
            IADsPrintQueue __RPC_FAR * This,
            /* [retval][out] */ DATE __RPC_FAR *retval);
        
        /* [id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_StartTime )( 
            IADsPrintQueue __RPC_FAR * This,
            /* [in] */ DATE daStartTime);
        
        /* [id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_UntilTime )( 
            IADsPrintQueue __RPC_FAR * This,
            /* [retval][out] */ DATE __RPC_FAR *retval);
        
        /* [id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_UntilTime )( 
            IADsPrintQueue __RPC_FAR * This,
            /* [in] */ DATE daUntilTime);
        
        /* [id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_DefaultJobPriority )( 
            IADsPrintQueue __RPC_FAR * This,
            /* [retval][out] */ long __RPC_FAR *retval);
        
        /* [id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_DefaultJobPriority )( 
            IADsPrintQueue __RPC_FAR * This,
            /* [in] */ long lnDefaultJobPriority);
        
        /* [id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Priority )( 
            IADsPrintQueue __RPC_FAR * This,
            /* [retval][out] */ long __RPC_FAR *retval);
        
        /* [id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_Priority )( 
            IADsPrintQueue __RPC_FAR * This,
            /* [in] */ long lnPriority);
        
        /* [id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_BannerPage )( 
            IADsPrintQueue __RPC_FAR * This,
            /* [retval][out] */ BSTR __RPC_FAR *retval);
        
        /* [id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_BannerPage )( 
            IADsPrintQueue __RPC_FAR * This,
            /* [in] */ BSTR bstrBannerPage);
        
        /* [id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_PrintDevices )( 
            IADsPrintQueue __RPC_FAR * This,
            /* [retval][out] */ VARIANT __RPC_FAR *retval);
        
        /* [id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_PrintDevices )( 
            IADsPrintQueue __RPC_FAR * This,
            /* [in] */ VARIANT vPrintDevices);
        
        /* [id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_NetAddresses )( 
            IADsPrintQueue __RPC_FAR * This,
            /* [retval][out] */ VARIANT __RPC_FAR *retval);
        
        /* [id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_NetAddresses )( 
            IADsPrintQueue __RPC_FAR * This,
            /* [in] */ VARIANT vNetAddresses);
        
        END_INTERFACE
    } IADsPrintQueueVtbl;

    interface IADsPrintQueue
    {
        CONST_VTBL struct IADsPrintQueueVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IADsPrintQueue_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IADsPrintQueue_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IADsPrintQueue_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IADsPrintQueue_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define IADsPrintQueue_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define IADsPrintQueue_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define IADsPrintQueue_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)


#define IADsPrintQueue_get_Name(This,retval)	\
    (This)->lpVtbl -> get_Name(This,retval)

#define IADsPrintQueue_get_Class(This,retval)	\
    (This)->lpVtbl -> get_Class(This,retval)

#define IADsPrintQueue_get_GUID(This,retval)	\
    (This)->lpVtbl -> get_GUID(This,retval)

#define IADsPrintQueue_get_ADsPath(This,retval)	\
    (This)->lpVtbl -> get_ADsPath(This,retval)

#define IADsPrintQueue_get_Parent(This,retval)	\
    (This)->lpVtbl -> get_Parent(This,retval)

#define IADsPrintQueue_get_Schema(This,retval)	\
    (This)->lpVtbl -> get_Schema(This,retval)

#define IADsPrintQueue_GetInfo(This)	\
    (This)->lpVtbl -> GetInfo(This)

#define IADsPrintQueue_SetInfo(This)	\
    (This)->lpVtbl -> SetInfo(This)

#define IADsPrintQueue_Get(This,bstrName,pvProp)	\
    (This)->lpVtbl -> Get(This,bstrName,pvProp)

#define IADsPrintQueue_Put(This,bstrName,vProp)	\
    (This)->lpVtbl -> Put(This,bstrName,vProp)

#define IADsPrintQueue_GetEx(This,bstrName,pvProp)	\
    (This)->lpVtbl -> GetEx(This,bstrName,pvProp)

#define IADsPrintQueue_PutEx(This,lnControlCode,bstrName,vProp)	\
    (This)->lpVtbl -> PutEx(This,lnControlCode,bstrName,vProp)

#define IADsPrintQueue_GetInfoEx(This,vProperties,lnReserved)	\
    (This)->lpVtbl -> GetInfoEx(This,vProperties,lnReserved)


#define IADsPrintQueue_get_PrinterPath(This,retval)	\
    (This)->lpVtbl -> get_PrinterPath(This,retval)

#define IADsPrintQueue_put_PrinterPath(This,bstrPrinterPath)	\
    (This)->lpVtbl -> put_PrinterPath(This,bstrPrinterPath)

#define IADsPrintQueue_get_Model(This,retval)	\
    (This)->lpVtbl -> get_Model(This,retval)

#define IADsPrintQueue_put_Model(This,bstrModel)	\
    (This)->lpVtbl -> put_Model(This,bstrModel)

#define IADsPrintQueue_get_Datatype(This,retval)	\
    (This)->lpVtbl -> get_Datatype(This,retval)

#define IADsPrintQueue_put_Datatype(This,bstrDatatype)	\
    (This)->lpVtbl -> put_Datatype(This,bstrDatatype)

#define IADsPrintQueue_get_PrintProcessor(This,retval)	\
    (This)->lpVtbl -> get_PrintProcessor(This,retval)

#define IADsPrintQueue_put_PrintProcessor(This,bstrPrintProcessor)	\
    (This)->lpVtbl -> put_PrintProcessor(This,bstrPrintProcessor)

#define IADsPrintQueue_get_Description(This,retval)	\
    (This)->lpVtbl -> get_Description(This,retval)

#define IADsPrintQueue_put_Description(This,bstrDescription)	\
    (This)->lpVtbl -> put_Description(This,bstrDescription)

#define IADsPrintQueue_get_Location(This,retval)	\
    (This)->lpVtbl -> get_Location(This,retval)

#define IADsPrintQueue_put_Location(This,bstrLocation)	\
    (This)->lpVtbl -> put_Location(This,bstrLocation)

#define IADsPrintQueue_get_StartTime(This,retval)	\
    (This)->lpVtbl -> get_StartTime(This,retval)

#define IADsPrintQueue_put_StartTime(This,daStartTime)	\
    (This)->lpVtbl -> put_StartTime(This,daStartTime)

#define IADsPrintQueue_get_UntilTime(This,retval)	\
    (This)->lpVtbl -> get_UntilTime(This,retval)

#define IADsPrintQueue_put_UntilTime(This,daUntilTime)	\
    (This)->lpVtbl -> put_UntilTime(This,daUntilTime)

#define IADsPrintQueue_get_DefaultJobPriority(This,retval)	\
    (This)->lpVtbl -> get_DefaultJobPriority(This,retval)

#define IADsPrintQueue_put_DefaultJobPriority(This,lnDefaultJobPriority)	\
    (This)->lpVtbl -> put_DefaultJobPriority(This,lnDefaultJobPriority)

#define IADsPrintQueue_get_Priority(This,retval)	\
    (This)->lpVtbl -> get_Priority(This,retval)

#define IADsPrintQueue_put_Priority(This,lnPriority)	\
    (This)->lpVtbl -> put_Priority(This,lnPriority)

#define IADsPrintQueue_get_BannerPage(This,retval)	\
    (This)->lpVtbl -> get_BannerPage(This,retval)

#define IADsPrintQueue_put_BannerPage(This,bstrBannerPage)	\
    (This)->lpVtbl -> put_BannerPage(This,bstrBannerPage)

#define IADsPrintQueue_get_PrintDevices(This,retval)	\
    (This)->lpVtbl -> get_PrintDevices(This,retval)

#define IADsPrintQueue_put_PrintDevices(This,vPrintDevices)	\
    (This)->lpVtbl -> put_PrintDevices(This,vPrintDevices)

#define IADsPrintQueue_get_NetAddresses(This,retval)	\
    (This)->lpVtbl -> get_NetAddresses(This,retval)

#define IADsPrintQueue_put_NetAddresses(This,vNetAddresses)	\
    (This)->lpVtbl -> put_NetAddresses(This,vNetAddresses)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [id][propget] */ HRESULT STDMETHODCALLTYPE IADsPrintQueue_get_PrinterPath_Proxy( 
    IADsPrintQueue __RPC_FAR * This,
    /* [retval][out] */ BSTR __RPC_FAR *retval);


void __RPC_STUB IADsPrintQueue_get_PrinterPath_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [id][propput] */ HRESULT STDMETHODCALLTYPE IADsPrintQueue_put_PrinterPath_Proxy( 
    IADsPrintQueue __RPC_FAR * This,
    /* [in] */ BSTR bstrPrinterPath);


void __RPC_STUB IADsPrintQueue_put_PrinterPath_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [id][propget] */ HRESULT STDMETHODCALLTYPE IADsPrintQueue_get_Model_Proxy( 
    IADsPrintQueue __RPC_FAR * This,
    /* [retval][out] */ BSTR __RPC_FAR *retval);


void __RPC_STUB IADsPrintQueue_get_Model_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [id][propput] */ HRESULT STDMETHODCALLTYPE IADsPrintQueue_put_Model_Proxy( 
    IADsPrintQueue __RPC_FAR * This,
    /* [in] */ BSTR bstrModel);


void __RPC_STUB IADsPrintQueue_put_Model_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [id][propget] */ HRESULT STDMETHODCALLTYPE IADsPrintQueue_get_Datatype_Proxy( 
    IADsPrintQueue __RPC_FAR * This,
    /* [retval][out] */ BSTR __RPC_FAR *retval);


void __RPC_STUB IADsPrintQueue_get_Datatype_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [id][propput] */ HRESULT STDMETHODCALLTYPE IADsPrintQueue_put_Datatype_Proxy( 
    IADsPrintQueue __RPC_FAR * This,
    /* [in] */ BSTR bstrDatatype);


void __RPC_STUB IADsPrintQueue_put_Datatype_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [id][propget] */ HRESULT STDMETHODCALLTYPE IADsPrintQueue_get_PrintProcessor_Proxy( 
    IADsPrintQueue __RPC_FAR * This,
    /* [retval][out] */ BSTR __RPC_FAR *retval);


void __RPC_STUB IADsPrintQueue_get_PrintProcessor_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [id][propput] */ HRESULT STDMETHODCALLTYPE IADsPrintQueue_put_PrintProcessor_Proxy( 
    IADsPrintQueue __RPC_FAR * This,
    /* [in] */ BSTR bstrPrintProcessor);


void __RPC_STUB IADsPrintQueue_put_PrintProcessor_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [id][propget] */ HRESULT STDMETHODCALLTYPE IADsPrintQueue_get_Description_Proxy( 
    IADsPrintQueue __RPC_FAR * This,
    /* [retval][out] */ BSTR __RPC_FAR *retval);


void __RPC_STUB IADsPrintQueue_get_Description_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [id][propput] */ HRESULT STDMETHODCALLTYPE IADsPrintQueue_put_Description_Proxy( 
    IADsPrintQueue __RPC_FAR * This,
    /* [in] */ BSTR bstrDescription);


void __RPC_STUB IADsPrintQueue_put_Description_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [id][propget] */ HRESULT STDMETHODCALLTYPE IADsPrintQueue_get_Location_Proxy( 
    IADsPrintQueue __RPC_FAR * This,
    /* [retval][out] */ BSTR __RPC_FAR *retval);


void __RPC_STUB IADsPrintQueue_get_Location_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [id][propput] */ HRESULT STDMETHODCALLTYPE IADsPrintQueue_put_Location_Proxy( 
    IADsPrintQueue __RPC_FAR * This,
    /* [in] */ BSTR bstrLocation);


void __RPC_STUB IADsPrintQueue_put_Location_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [id][propget] */ HRESULT STDMETHODCALLTYPE IADsPrintQueue_get_StartTime_Proxy( 
    IADsPrintQueue __RPC_FAR * This,
    /* [retval][out] */ DATE __RPC_FAR *retval);


void __RPC_STUB IADsPrintQueue_get_StartTime_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [id][propput] */ HRESULT STDMETHODCALLTYPE IADsPrintQueue_put_StartTime_Proxy( 
    IADsPrintQueue __RPC_FAR * This,
    /* [in] */ DATE daStartTime);


void __RPC_STUB IADsPrintQueue_put_StartTime_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [id][propget] */ HRESULT STDMETHODCALLTYPE IADsPrintQueue_get_UntilTime_Proxy( 
    IADsPrintQueue __RPC_FAR * This,
    /* [retval][out] */ DATE __RPC_FAR *retval);


void __RPC_STUB IADsPrintQueue_get_UntilTime_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [id][propput] */ HRESULT STDMETHODCALLTYPE IADsPrintQueue_put_UntilTime_Proxy( 
    IADsPrintQueue __RPC_FAR * This,
    /* [in] */ DATE daUntilTime);


void __RPC_STUB IADsPrintQueue_put_UntilTime_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [id][propget] */ HRESULT STDMETHODCALLTYPE IADsPrintQueue_get_DefaultJobPriority_Proxy( 
    IADsPrintQueue __RPC_FAR * This,
    /* [retval][out] */ long __RPC_FAR *retval);


void __RPC_STUB IADsPrintQueue_get_DefaultJobPriority_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [id][propput] */ HRESULT STDMETHODCALLTYPE IADsPrintQueue_put_DefaultJobPriority_Proxy( 
    IADsPrintQueue __RPC_FAR * This,
    /* [in] */ long lnDefaultJobPriority);


void __RPC_STUB IADsPrintQueue_put_DefaultJobPriority_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [id][propget] */ HRESULT STDMETHODCALLTYPE IADsPrintQueue_get_Priority_Proxy( 
    IADsPrintQueue __RPC_FAR * This,
    /* [retval][out] */ long __RPC_FAR *retval);


void __RPC_STUB IADsPrintQueue_get_Priority_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [id][propput] */ HRESULT STDMETHODCALLTYPE IADsPrintQueue_put_Priority_Proxy( 
    IADsPrintQueue __RPC_FAR * This,
    /* [in] */ long lnPriority);


void __RPC_STUB IADsPrintQueue_put_Priority_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [id][propget] */ HRESULT STDMETHODCALLTYPE IADsPrintQueue_get_BannerPage_Proxy( 
    IADsPrintQueue __RPC_FAR * This,
    /* [retval][out] */ BSTR __RPC_FAR *retval);


void __RPC_STUB IADsPrintQueue_get_BannerPage_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [id][propput] */ HRESULT STDMETHODCALLTYPE IADsPrintQueue_put_BannerPage_Proxy( 
    IADsPrintQueue __RPC_FAR * This,
    /* [in] */ BSTR bstrBannerPage);


void __RPC_STUB IADsPrintQueue_put_BannerPage_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [id][propget] */ HRESULT STDMETHODCALLTYPE IADsPrintQueue_get_PrintDevices_Proxy( 
    IADsPrintQueue __RPC_FAR * This,
    /* [retval][out] */ VARIANT __RPC_FAR *retval);


void __RPC_STUB IADsPrintQueue_get_PrintDevices_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [id][propput] */ HRESULT STDMETHODCALLTYPE IADsPrintQueue_put_PrintDevices_Proxy( 
    IADsPrintQueue __RPC_FAR * This,
    /* [in] */ VARIANT vPrintDevices);


void __RPC_STUB IADsPrintQueue_put_PrintDevices_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [id][propget] */ HRESULT STDMETHODCALLTYPE IADsPrintQueue_get_NetAddresses_Proxy( 
    IADsPrintQueue __RPC_FAR * This,
    /* [retval][out] */ VARIANT __RPC_FAR *retval);


void __RPC_STUB IADsPrintQueue_get_NetAddresses_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [id][propput] */ HRESULT STDMETHODCALLTYPE IADsPrintQueue_put_NetAddresses_Proxy( 
    IADsPrintQueue __RPC_FAR * This,
    /* [in] */ VARIANT vNetAddresses);


void __RPC_STUB IADsPrintQueue_put_NetAddresses_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IADsPrintQueue_INTERFACE_DEFINED__ */


#ifndef __IADsPrintQueueOperations_INTERFACE_DEFINED__
#define __IADsPrintQueueOperations_INTERFACE_DEFINED__

/****************************************
 * Generated header for interface: IADsPrintQueueOperations
 * at Mon Oct 13 13:47:30 1997
 * using MIDL 3.00.44
 ****************************************/
/* [object][dual][oleautomation][uuid] */ 



EXTERN_C const IID IID_IADsPrintQueueOperations;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    interface IADsPrintQueueOperations : public IADs
    {
    public:
        virtual /* [id][propget] */ HRESULT STDMETHODCALLTYPE get_Status( 
            /* [retval][out] */ long __RPC_FAR *retval) = 0;
        
        virtual /* [id] */ HRESULT STDMETHODCALLTYPE PrintJobs( 
            /* [retval][out] */ IADsCollection __RPC_FAR *__RPC_FAR *pObject) = 0;
        
        virtual /* [id] */ HRESULT STDMETHODCALLTYPE Pause( void) = 0;
        
        virtual /* [id] */ HRESULT STDMETHODCALLTYPE Resume( void) = 0;
        
        virtual /* [id] */ HRESULT STDMETHODCALLTYPE Purge( void) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IADsPrintQueueOperationsVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            IADsPrintQueueOperations __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            IADsPrintQueueOperations __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            IADsPrintQueueOperations __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfoCount )( 
            IADsPrintQueueOperations __RPC_FAR * This,
            /* [out] */ UINT __RPC_FAR *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfo )( 
            IADsPrintQueueOperations __RPC_FAR * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo __RPC_FAR *__RPC_FAR *ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetIDsOfNames )( 
            IADsPrintQueueOperations __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR __RPC_FAR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID __RPC_FAR *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Invoke )( 
            IADsPrintQueueOperations __RPC_FAR * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS __RPC_FAR *pDispParams,
            /* [out] */ VARIANT __RPC_FAR *pVarResult,
            /* [out] */ EXCEPINFO __RPC_FAR *pExcepInfo,
            /* [out] */ UINT __RPC_FAR *puArgErr);
        
        /* [id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Name )( 
            IADsPrintQueueOperations __RPC_FAR * This,
            /* [retval][out] */ BSTR __RPC_FAR *retval);
        
        /* [id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Class )( 
            IADsPrintQueueOperations __RPC_FAR * This,
            /* [retval][out] */ BSTR __RPC_FAR *retval);
        
        /* [id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_GUID )( 
            IADsPrintQueueOperations __RPC_FAR * This,
            /* [retval][out] */ BSTR __RPC_FAR *retval);
        
        /* [id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_ADsPath )( 
            IADsPrintQueueOperations __RPC_FAR * This,
            /* [retval][out] */ BSTR __RPC_FAR *retval);
        
        /* [id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Parent )( 
            IADsPrintQueueOperations __RPC_FAR * This,
            /* [retval][out] */ BSTR __RPC_FAR *retval);
        
        /* [id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Schema )( 
            IADsPrintQueueOperations __RPC_FAR * This,
            /* [retval][out] */ BSTR __RPC_FAR *retval);
        
        /* [id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetInfo )( 
            IADsPrintQueueOperations __RPC_FAR * This);
        
        /* [id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *SetInfo )( 
            IADsPrintQueueOperations __RPC_FAR * This);
        
        /* [id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Get )( 
            IADsPrintQueueOperations __RPC_FAR * This,
            /* [in] */ BSTR bstrName,
            /* [retval][out] */ VARIANT __RPC_FAR *pvProp);
        
        /* [id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Put )( 
            IADsPrintQueueOperations __RPC_FAR * This,
            /* [in] */ BSTR bstrName,
            /* [in] */ VARIANT vProp);
        
        /* [id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetEx )( 
            IADsPrintQueueOperations __RPC_FAR * This,
            /* [in] */ BSTR bstrName,
            /* [retval][out] */ VARIANT __RPC_FAR *pvProp);
        
        /* [id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *PutEx )( 
            IADsPrintQueueOperations __RPC_FAR * This,
            /* [in] */ long lnControlCode,
            /* [in] */ BSTR bstrName,
            /* [in] */ VARIANT vProp);
        
        /* [id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetInfoEx )( 
            IADsPrintQueueOperations __RPC_FAR * This,
            /* [in] */ VARIANT vProperties,
            /* [in] */ long lnReserved);
        
        /* [id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Status )( 
            IADsPrintQueueOperations __RPC_FAR * This,
            /* [retval][out] */ long __RPC_FAR *retval);
        
        /* [id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *PrintJobs )( 
            IADsPrintQueueOperations __RPC_FAR * This,
            /* [retval][out] */ IADsCollection __RPC_FAR *__RPC_FAR *pObject);
        
        /* [id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Pause )( 
            IADsPrintQueueOperations __RPC_FAR * This);
        
        /* [id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Resume )( 
            IADsPrintQueueOperations __RPC_FAR * This);
        
        /* [id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Purge )( 
            IADsPrintQueueOperations __RPC_FAR * This);
        
        END_INTERFACE
    } IADsPrintQueueOperationsVtbl;

    interface IADsPrintQueueOperations
    {
        CONST_VTBL struct IADsPrintQueueOperationsVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IADsPrintQueueOperations_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IADsPrintQueueOperations_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IADsPrintQueueOperations_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IADsPrintQueueOperations_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define IADsPrintQueueOperations_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define IADsPrintQueueOperations_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define IADsPrintQueueOperations_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)


#define IADsPrintQueueOperations_get_Name(This,retval)	\
    (This)->lpVtbl -> get_Name(This,retval)

#define IADsPrintQueueOperations_get_Class(This,retval)	\
    (This)->lpVtbl -> get_Class(This,retval)

#define IADsPrintQueueOperations_get_GUID(This,retval)	\
    (This)->lpVtbl -> get_GUID(This,retval)

#define IADsPrintQueueOperations_get_ADsPath(This,retval)	\
    (This)->lpVtbl -> get_ADsPath(This,retval)

#define IADsPrintQueueOperations_get_Parent(This,retval)	\
    (This)->lpVtbl -> get_Parent(This,retval)

#define IADsPrintQueueOperations_get_Schema(This,retval)	\
    (This)->lpVtbl -> get_Schema(This,retval)

#define IADsPrintQueueOperations_GetInfo(This)	\
    (This)->lpVtbl -> GetInfo(This)

#define IADsPrintQueueOperations_SetInfo(This)	\
    (This)->lpVtbl -> SetInfo(This)

#define IADsPrintQueueOperations_Get(This,bstrName,pvProp)	\
    (This)->lpVtbl -> Get(This,bstrName,pvProp)

#define IADsPrintQueueOperations_Put(This,bstrName,vProp)	\
    (This)->lpVtbl -> Put(This,bstrName,vProp)

#define IADsPrintQueueOperations_GetEx(This,bstrName,pvProp)	\
    (This)->lpVtbl -> GetEx(This,bstrName,pvProp)

#define IADsPrintQueueOperations_PutEx(This,lnControlCode,bstrName,vProp)	\
    (This)->lpVtbl -> PutEx(This,lnControlCode,bstrName,vProp)

#define IADsPrintQueueOperations_GetInfoEx(This,vProperties,lnReserved)	\
    (This)->lpVtbl -> GetInfoEx(This,vProperties,lnReserved)


#define IADsPrintQueueOperations_get_Status(This,retval)	\
    (This)->lpVtbl -> get_Status(This,retval)

#define IADsPrintQueueOperations_PrintJobs(This,pObject)	\
    (This)->lpVtbl -> PrintJobs(This,pObject)

#define IADsPrintQueueOperations_Pause(This)	\
    (This)->lpVtbl -> Pause(This)

#define IADsPrintQueueOperations_Resume(This)	\
    (This)->lpVtbl -> Resume(This)

#define IADsPrintQueueOperations_Purge(This)	\
    (This)->lpVtbl -> Purge(This)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [id][propget] */ HRESULT STDMETHODCALLTYPE IADsPrintQueueOperations_get_Status_Proxy( 
    IADsPrintQueueOperations __RPC_FAR * This,
    /* [retval][out] */ long __RPC_FAR *retval);


void __RPC_STUB IADsPrintQueueOperations_get_Status_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [id] */ HRESULT STDMETHODCALLTYPE IADsPrintQueueOperations_PrintJobs_Proxy( 
    IADsPrintQueueOperations __RPC_FAR * This,
    /* [retval][out] */ IADsCollection __RPC_FAR *__RPC_FAR *pObject);


void __RPC_STUB IADsPrintQueueOperations_PrintJobs_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [id] */ HRESULT STDMETHODCALLTYPE IADsPrintQueueOperations_Pause_Proxy( 
    IADsPrintQueueOperations __RPC_FAR * This);


void __RPC_STUB IADsPrintQueueOperations_Pause_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [id] */ HRESULT STDMETHODCALLTYPE IADsPrintQueueOperations_Resume_Proxy( 
    IADsPrintQueueOperations __RPC_FAR * This);


void __RPC_STUB IADsPrintQueueOperations_Resume_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [id] */ HRESULT STDMETHODCALLTYPE IADsPrintQueueOperations_Purge_Proxy( 
    IADsPrintQueueOperations __RPC_FAR * This);


void __RPC_STUB IADsPrintQueueOperations_Purge_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IADsPrintQueueOperations_INTERFACE_DEFINED__ */


#ifndef __IADsPrintJob_INTERFACE_DEFINED__
#define __IADsPrintJob_INTERFACE_DEFINED__

/****************************************
 * Generated header for interface: IADsPrintJob
 * at Mon Oct 13 13:47:30 1997
 * using MIDL 3.00.44
 ****************************************/
/* [object][dual][oleautomation][uuid] */ 



EXTERN_C const IID IID_IADsPrintJob;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    interface IADsPrintJob : public IADs
    {
    public:
        virtual /* [id][propget] */ HRESULT STDMETHODCALLTYPE get_HostPrintQueue( 
            /* [retval][out] */ BSTR __RPC_FAR *retval) = 0;
        
        virtual /* [id][propget] */ HRESULT STDMETHODCALLTYPE get_User( 
            /* [retval][out] */ BSTR __RPC_FAR *retval) = 0;
        
        virtual /* [id][propget] */ HRESULT STDMETHODCALLTYPE get_UserPath( 
            /* [retval][out] */ BSTR __RPC_FAR *retval) = 0;
        
        virtual /* [id][propget] */ HRESULT STDMETHODCALLTYPE get_TimeSubmitted( 
            /* [retval][out] */ DATE __RPC_FAR *retval) = 0;
        
        virtual /* [id][propget] */ HRESULT STDMETHODCALLTYPE get_TotalPages( 
            /* [retval][out] */ long __RPC_FAR *retval) = 0;
        
        virtual /* [id][propget] */ HRESULT STDMETHODCALLTYPE get_Size( 
            /* [retval][out] */ long __RPC_FAR *retval) = 0;
        
        virtual /* [id][propget] */ HRESULT STDMETHODCALLTYPE get_Description( 
            /* [retval][out] */ BSTR __RPC_FAR *retval) = 0;
        
        virtual /* [id][propput] */ HRESULT STDMETHODCALLTYPE put_Description( 
            /* [in] */ BSTR bstrDescription) = 0;
        
        virtual /* [id][propget] */ HRESULT STDMETHODCALLTYPE get_Priority( 
            /* [retval][out] */ long __RPC_FAR *retval) = 0;
        
        virtual /* [id][propput] */ HRESULT STDMETHODCALLTYPE put_Priority( 
            /* [in] */ long lnPriority) = 0;
        
        virtual /* [id][propget] */ HRESULT STDMETHODCALLTYPE get_StartTime( 
            /* [retval][out] */ DATE __RPC_FAR *retval) = 0;
        
        virtual /* [id][propput] */ HRESULT STDMETHODCALLTYPE put_StartTime( 
            /* [in] */ DATE daStartTime) = 0;
        
        virtual /* [id][propget] */ HRESULT STDMETHODCALLTYPE get_UntilTime( 
            /* [retval][out] */ DATE __RPC_FAR *retval) = 0;
        
        virtual /* [id][propput] */ HRESULT STDMETHODCALLTYPE put_UntilTime( 
            /* [in] */ DATE daUntilTime) = 0;
        
        virtual /* [id][propget] */ HRESULT STDMETHODCALLTYPE get_Notify( 
            /* [retval][out] */ BSTR __RPC_FAR *retval) = 0;
        
        virtual /* [id][propput] */ HRESULT STDMETHODCALLTYPE put_Notify( 
            /* [in] */ BSTR bstrNotify) = 0;
        
        virtual /* [id][propget] */ HRESULT STDMETHODCALLTYPE get_NotifyPath( 
            /* [retval][out] */ BSTR __RPC_FAR *retval) = 0;
        
        virtual /* [id][propput] */ HRESULT STDMETHODCALLTYPE put_NotifyPath( 
            /* [in] */ BSTR bstrNotifyPath) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IADsPrintJobVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            IADsPrintJob __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            IADsPrintJob __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            IADsPrintJob __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfoCount )( 
            IADsPrintJob __RPC_FAR * This,
            /* [out] */ UINT __RPC_FAR *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfo )( 
            IADsPrintJob __RPC_FAR * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo __RPC_FAR *__RPC_FAR *ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetIDsOfNames )( 
            IADsPrintJob __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR __RPC_FAR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID __RPC_FAR *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Invoke )( 
            IADsPrintJob __RPC_FAR * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS __RPC_FAR *pDispParams,
            /* [out] */ VARIANT __RPC_FAR *pVarResult,
            /* [out] */ EXCEPINFO __RPC_FAR *pExcepInfo,
            /* [out] */ UINT __RPC_FAR *puArgErr);
        
        /* [id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Name )( 
            IADsPrintJob __RPC_FAR * This,
            /* [retval][out] */ BSTR __RPC_FAR *retval);
        
        /* [id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Class )( 
            IADsPrintJob __RPC_FAR * This,
            /* [retval][out] */ BSTR __RPC_FAR *retval);
        
        /* [id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_GUID )( 
            IADsPrintJob __RPC_FAR * This,
            /* [retval][out] */ BSTR __RPC_FAR *retval);
        
        /* [id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_ADsPath )( 
            IADsPrintJob __RPC_FAR * This,
            /* [retval][out] */ BSTR __RPC_FAR *retval);
        
        /* [id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Parent )( 
            IADsPrintJob __RPC_FAR * This,
            /* [retval][out] */ BSTR __RPC_FAR *retval);
        
        /* [id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Schema )( 
            IADsPrintJob __RPC_FAR * This,
            /* [retval][out] */ BSTR __RPC_FAR *retval);
        
        /* [id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetInfo )( 
            IADsPrintJob __RPC_FAR * This);
        
        /* [id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *SetInfo )( 
            IADsPrintJob __RPC_FAR * This);
        
        /* [id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Get )( 
            IADsPrintJob __RPC_FAR * This,
            /* [in] */ BSTR bstrName,
            /* [retval][out] */ VARIANT __RPC_FAR *pvProp);
        
        /* [id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Put )( 
            IADsPrintJob __RPC_FAR * This,
            /* [in] */ BSTR bstrName,
            /* [in] */ VARIANT vProp);
        
        /* [id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetEx )( 
            IADsPrintJob __RPC_FAR * This,
            /* [in] */ BSTR bstrName,
            /* [retval][out] */ VARIANT __RPC_FAR *pvProp);
        
        /* [id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *PutEx )( 
            IADsPrintJob __RPC_FAR * This,
            /* [in] */ long lnControlCode,
            /* [in] */ BSTR bstrName,
            /* [in] */ VARIANT vProp);
        
        /* [id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetInfoEx )( 
            IADsPrintJob __RPC_FAR * This,
            /* [in] */ VARIANT vProperties,
            /* [in] */ long lnReserved);
        
        /* [id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_HostPrintQueue )( 
            IADsPrintJob __RPC_FAR * This,
            /* [retval][out] */ BSTR __RPC_FAR *retval);
        
        /* [id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_User )( 
            IADsPrintJob __RPC_FAR * This,
            /* [retval][out] */ BSTR __RPC_FAR *retval);
        
        /* [id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_UserPath )( 
            IADsPrintJob __RPC_FAR * This,
            /* [retval][out] */ BSTR __RPC_FAR *retval);
        
        /* [id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_TimeSubmitted )( 
            IADsPrintJob __RPC_FAR * This,
            /* [retval][out] */ DATE __RPC_FAR *retval);
        
        /* [id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_TotalPages )( 
            IADsPrintJob __RPC_FAR * This,
            /* [retval][out] */ long __RPC_FAR *retval);
        
        /* [id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Size )( 
            IADsPrintJob __RPC_FAR * This,
            /* [retval][out] */ long __RPC_FAR *retval);
        
        /* [id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Description )( 
            IADsPrintJob __RPC_FAR * This,
            /* [retval][out] */ BSTR __RPC_FAR *retval);
        
        /* [id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_Description )( 
            IADsPrintJob __RPC_FAR * This,
            /* [in] */ BSTR bstrDescription);
        
        /* [id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Priority )( 
            IADsPrintJob __RPC_FAR * This,
            /* [retval][out] */ long __RPC_FAR *retval);
        
        /* [id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_Priority )( 
            IADsPrintJob __RPC_FAR * This,
            /* [in] */ long lnPriority);
        
        /* [id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_StartTime )( 
            IADsPrintJob __RPC_FAR * This,
            /* [retval][out] */ DATE __RPC_FAR *retval);
        
        /* [id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_StartTime )( 
            IADsPrintJob __RPC_FAR * This,
            /* [in] */ DATE daStartTime);
        
        /* [id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_UntilTime )( 
            IADsPrintJob __RPC_FAR * This,
            /* [retval][out] */ DATE __RPC_FAR *retval);
        
        /* [id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_UntilTime )( 
            IADsPrintJob __RPC_FAR * This,
            /* [in] */ DATE daUntilTime);
        
        /* [id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Notify )( 
            IADsPrintJob __RPC_FAR * This,
            /* [retval][out] */ BSTR __RPC_FAR *retval);
        
        /* [id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_Notify )( 
            IADsPrintJob __RPC_FAR * This,
            /* [in] */ BSTR bstrNotify);
        
        /* [id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_NotifyPath )( 
            IADsPrintJob __RPC_FAR * This,
            /* [retval][out] */ BSTR __RPC_FAR *retval);
        
        /* [id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_NotifyPath )( 
            IADsPrintJob __RPC_FAR * This,
            /* [in] */ BSTR bstrNotifyPath);
        
        END_INTERFACE
    } IADsPrintJobVtbl;

    interface IADsPrintJob
    {
        CONST_VTBL struct IADsPrintJobVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IADsPrintJob_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IADsPrintJob_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IADsPrintJob_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IADsPrintJob_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define IADsPrintJob_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define IADsPrintJob_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define IADsPrintJob_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)


#define IADsPrintJob_get_Name(This,retval)	\
    (This)->lpVtbl -> get_Name(This,retval)

#define IADsPrintJob_get_Class(This,retval)	\
    (This)->lpVtbl -> get_Class(This,retval)

#define IADsPrintJob_get_GUID(This,retval)	\
    (This)->lpVtbl -> get_GUID(This,retval)

#define IADsPrintJob_get_ADsPath(This,retval)	\
    (This)->lpVtbl -> get_ADsPath(This,retval)

#define IADsPrintJob_get_Parent(This,retval)	\
    (This)->lpVtbl -> get_Parent(This,retval)

#define IADsPrintJob_get_Schema(This,retval)	\
    (This)->lpVtbl -> get_Schema(This,retval)

#define IADsPrintJob_GetInfo(This)	\
    (This)->lpVtbl -> GetInfo(This)

#define IADsPrintJob_SetInfo(This)	\
    (This)->lpVtbl -> SetInfo(This)

#define IADsPrintJob_Get(This,bstrName,pvProp)	\
    (This)->lpVtbl -> Get(This,bstrName,pvProp)

#define IADsPrintJob_Put(This,bstrName,vProp)	\
    (This)->lpVtbl -> Put(This,bstrName,vProp)

#define IADsPrintJob_GetEx(This,bstrName,pvProp)	\
    (This)->lpVtbl -> GetEx(This,bstrName,pvProp)

#define IADsPrintJob_PutEx(This,lnControlCode,bstrName,vProp)	\
    (This)->lpVtbl -> PutEx(This,lnControlCode,bstrName,vProp)

#define IADsPrintJob_GetInfoEx(This,vProperties,lnReserved)	\
    (This)->lpVtbl -> GetInfoEx(This,vProperties,lnReserved)


#define IADsPrintJob_get_HostPrintQueue(This,retval)	\
    (This)->lpVtbl -> get_HostPrintQueue(This,retval)

#define IADsPrintJob_get_User(This,retval)	\
    (This)->lpVtbl -> get_User(This,retval)

#define IADsPrintJob_get_UserPath(This,retval)	\
    (This)->lpVtbl -> get_UserPath(This,retval)

#define IADsPrintJob_get_TimeSubmitted(This,retval)	\
    (This)->lpVtbl -> get_TimeSubmitted(This,retval)

#define IADsPrintJob_get_TotalPages(This,retval)	\
    (This)->lpVtbl -> get_TotalPages(This,retval)

#define IADsPrintJob_get_Size(This,retval)	\
    (This)->lpVtbl -> get_Size(This,retval)

#define IADsPrintJob_get_Description(This,retval)	\
    (This)->lpVtbl -> get_Description(This,retval)

#define IADsPrintJob_put_Description(This,bstrDescription)	\
    (This)->lpVtbl -> put_Description(This,bstrDescription)

#define IADsPrintJob_get_Priority(This,retval)	\
    (This)->lpVtbl -> get_Priority(This,retval)

#define IADsPrintJob_put_Priority(This,lnPriority)	\
    (This)->lpVtbl -> put_Priority(This,lnPriority)

#define IADsPrintJob_get_StartTime(This,retval)	\
    (This)->lpVtbl -> get_StartTime(This,retval)

#define IADsPrintJob_put_StartTime(This,daStartTime)	\
    (This)->lpVtbl -> put_StartTime(This,daStartTime)

#define IADsPrintJob_get_UntilTime(This,retval)	\
    (This)->lpVtbl -> get_UntilTime(This,retval)

#define IADsPrintJob_put_UntilTime(This,daUntilTime)	\
    (This)->lpVtbl -> put_UntilTime(This,daUntilTime)

#define IADsPrintJob_get_Notify(This,retval)	\
    (This)->lpVtbl -> get_Notify(This,retval)

#define IADsPrintJob_put_Notify(This,bstrNotify)	\
    (This)->lpVtbl -> put_Notify(This,bstrNotify)

#define IADsPrintJob_get_NotifyPath(This,retval)	\
    (This)->lpVtbl -> get_NotifyPath(This,retval)

#define IADsPrintJob_put_NotifyPath(This,bstrNotifyPath)	\
    (This)->lpVtbl -> put_NotifyPath(This,bstrNotifyPath)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [id][propget] */ HRESULT STDMETHODCALLTYPE IADsPrintJob_get_HostPrintQueue_Proxy( 
    IADsPrintJob __RPC_FAR * This,
    /* [retval][out] */ BSTR __RPC_FAR *retval);


void __RPC_STUB IADsPrintJob_get_HostPrintQueue_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [id][propget] */ HRESULT STDMETHODCALLTYPE IADsPrintJob_get_User_Proxy( 
    IADsPrintJob __RPC_FAR * This,
    /* [retval][out] */ BSTR __RPC_FAR *retval);


void __RPC_STUB IADsPrintJob_get_User_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [id][propget] */ HRESULT STDMETHODCALLTYPE IADsPrintJob_get_UserPath_Proxy( 
    IADsPrintJob __RPC_FAR * This,
    /* [retval][out] */ BSTR __RPC_FAR *retval);


void __RPC_STUB IADsPrintJob_get_UserPath_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [id][propget] */ HRESULT STDMETHODCALLTYPE IADsPrintJob_get_TimeSubmitted_Proxy( 
    IADsPrintJob __RPC_FAR * This,
    /* [retval][out] */ DATE __RPC_FAR *retval);


void __RPC_STUB IADsPrintJob_get_TimeSubmitted_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [id][propget] */ HRESULT STDMETHODCALLTYPE IADsPrintJob_get_TotalPages_Proxy( 
    IADsPrintJob __RPC_FAR * This,
    /* [retval][out] */ long __RPC_FAR *retval);


void __RPC_STUB IADsPrintJob_get_TotalPages_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [id][propget] */ HRESULT STDMETHODCALLTYPE IADsPrintJob_get_Size_Proxy( 
    IADsPrintJob __RPC_FAR * This,
    /* [retval][out] */ long __RPC_FAR *retval);


void __RPC_STUB IADsPrintJob_get_Size_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [id][propget] */ HRESULT STDMETHODCALLTYPE IADsPrintJob_get_Description_Proxy( 
    IADsPrintJob __RPC_FAR * This,
    /* [retval][out] */ BSTR __RPC_FAR *retval);


void __RPC_STUB IADsPrintJob_get_Description_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [id][propput] */ HRESULT STDMETHODCALLTYPE IADsPrintJob_put_Description_Proxy( 
    IADsPrintJob __RPC_FAR * This,
    /* [in] */ BSTR bstrDescription);


void __RPC_STUB IADsPrintJob_put_Description_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [id][propget] */ HRESULT STDMETHODCALLTYPE IADsPrintJob_get_Priority_Proxy( 
    IADsPrintJob __RPC_FAR * This,
    /* [retval][out] */ long __RPC_FAR *retval);


void __RPC_STUB IADsPrintJob_get_Priority_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [id][propput] */ HRESULT STDMETHODCALLTYPE IADsPrintJob_put_Priority_Proxy( 
    IADsPrintJob __RPC_FAR * This,
    /* [in] */ long lnPriority);


void __RPC_STUB IADsPrintJob_put_Priority_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [id][propget] */ HRESULT STDMETHODCALLTYPE IADsPrintJob_get_StartTime_Proxy( 
    IADsPrintJob __RPC_FAR * This,
    /* [retval][out] */ DATE __RPC_FAR *retval);


void __RPC_STUB IADsPrintJob_get_StartTime_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [id][propput] */ HRESULT STDMETHODCALLTYPE IADsPrintJob_put_StartTime_Proxy( 
    IADsPrintJob __RPC_FAR * This,
    /* [in] */ DATE daStartTime);


void __RPC_STUB IADsPrintJob_put_StartTime_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [id][propget] */ HRESULT STDMETHODCALLTYPE IADsPrintJob_get_UntilTime_Proxy( 
    IADsPrintJob __RPC_FAR * This,
    /* [retval][out] */ DATE __RPC_FAR *retval);


void __RPC_STUB IADsPrintJob_get_UntilTime_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [id][propput] */ HRESULT STDMETHODCALLTYPE IADsPrintJob_put_UntilTime_Proxy( 
    IADsPrintJob __RPC_FAR * This,
    /* [in] */ DATE daUntilTime);


void __RPC_STUB IADsPrintJob_put_UntilTime_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [id][propget] */ HRESULT STDMETHODCALLTYPE IADsPrintJob_get_Notify_Proxy( 
    IADsPrintJob __RPC_FAR * This,
    /* [retval][out] */ BSTR __RPC_FAR *retval);


void __RPC_STUB IADsPrintJob_get_Notify_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [id][propput] */ HRESULT STDMETHODCALLTYPE IADsPrintJob_put_Notify_Proxy( 
    IADsPrintJob __RPC_FAR * This,
    /* [in] */ BSTR bstrNotify);


void __RPC_STUB IADsPrintJob_put_Notify_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [id][propget] */ HRESULT STDMETHODCALLTYPE IADsPrintJob_get_NotifyPath_Proxy( 
    IADsPrintJob __RPC_FAR * This,
    /* [retval][out] */ BSTR __RPC_FAR *retval);


void __RPC_STUB IADsPrintJob_get_NotifyPath_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [id][propput] */ HRESULT STDMETHODCALLTYPE IADsPrintJob_put_NotifyPath_Proxy( 
    IADsPrintJob __RPC_FAR * This,
    /* [in] */ BSTR bstrNotifyPath);


void __RPC_STUB IADsPrintJob_put_NotifyPath_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IADsPrintJob_INTERFACE_DEFINED__ */


#ifndef __IADsPrintJobOperations_INTERFACE_DEFINED__
#define __IADsPrintJobOperations_INTERFACE_DEFINED__

/****************************************
 * Generated header for interface: IADsPrintJobOperations
 * at Mon Oct 13 13:47:30 1997
 * using MIDL 3.00.44
 ****************************************/
/* [object][dual][oleautomation][uuid] */ 



EXTERN_C const IID IID_IADsPrintJobOperations;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    interface IADsPrintJobOperations : public IADs
    {
    public:
        virtual /* [id][propget] */ HRESULT STDMETHODCALLTYPE get_Status( 
            /* [retval][out] */ long __RPC_FAR *retval) = 0;
        
        virtual /* [id][propget] */ HRESULT STDMETHODCALLTYPE get_TimeElapsed( 
            /* [retval][out] */ long __RPC_FAR *retval) = 0;
        
        virtual /* [id][propget] */ HRESULT STDMETHODCALLTYPE get_PagesPrinted( 
            /* [retval][out] */ long __RPC_FAR *retval) = 0;
        
        virtual /* [id][propget] */ HRESULT STDMETHODCALLTYPE get_Position( 
            /* [retval][out] */ long __RPC_FAR *retval) = 0;
        
        virtual /* [id][propput] */ HRESULT STDMETHODCALLTYPE put_Position( 
            /* [in] */ long lnPosition) = 0;
        
        virtual /* [id] */ HRESULT STDMETHODCALLTYPE Pause( void) = 0;
        
        virtual /* [id] */ HRESULT STDMETHODCALLTYPE Resume( void) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IADsPrintJobOperationsVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            IADsPrintJobOperations __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            IADsPrintJobOperations __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            IADsPrintJobOperations __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfoCount )( 
            IADsPrintJobOperations __RPC_FAR * This,
            /* [out] */ UINT __RPC_FAR *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfo )( 
            IADsPrintJobOperations __RPC_FAR * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo __RPC_FAR *__RPC_FAR *ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetIDsOfNames )( 
            IADsPrintJobOperations __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR __RPC_FAR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID __RPC_FAR *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Invoke )( 
            IADsPrintJobOperations __RPC_FAR * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS __RPC_FAR *pDispParams,
            /* [out] */ VARIANT __RPC_FAR *pVarResult,
            /* [out] */ EXCEPINFO __RPC_FAR *pExcepInfo,
            /* [out] */ UINT __RPC_FAR *puArgErr);
        
        /* [id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Name )( 
            IADsPrintJobOperations __RPC_FAR * This,
            /* [retval][out] */ BSTR __RPC_FAR *retval);
        
        /* [id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Class )( 
            IADsPrintJobOperations __RPC_FAR * This,
            /* [retval][out] */ BSTR __RPC_FAR *retval);
        
        /* [id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_GUID )( 
            IADsPrintJobOperations __RPC_FAR * This,
            /* [retval][out] */ BSTR __RPC_FAR *retval);
        
        /* [id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_ADsPath )( 
            IADsPrintJobOperations __RPC_FAR * This,
            /* [retval][out] */ BSTR __RPC_FAR *retval);
        
        /* [id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Parent )( 
            IADsPrintJobOperations __RPC_FAR * This,
            /* [retval][out] */ BSTR __RPC_FAR *retval);
        
        /* [id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Schema )( 
            IADsPrintJobOperations __RPC_FAR * This,
            /* [retval][out] */ BSTR __RPC_FAR *retval);
        
        /* [id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetInfo )( 
            IADsPrintJobOperations __RPC_FAR * This);
        
        /* [id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *SetInfo )( 
            IADsPrintJobOperations __RPC_FAR * This);
        
        /* [id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Get )( 
            IADsPrintJobOperations __RPC_FAR * This,
            /* [in] */ BSTR bstrName,
            /* [retval][out] */ VARIANT __RPC_FAR *pvProp);
        
        /* [id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Put )( 
            IADsPrintJobOperations __RPC_FAR * This,
            /* [in] */ BSTR bstrName,
            /* [in] */ VARIANT vProp);
        
        /* [id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetEx )( 
            IADsPrintJobOperations __RPC_FAR * This,
            /* [in] */ BSTR bstrName,
            /* [retval][out] */ VARIANT __RPC_FAR *pvProp);
        
        /* [id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *PutEx )( 
            IADsPrintJobOperations __RPC_FAR * This,
            /* [in] */ long lnControlCode,
            /* [in] */ BSTR bstrName,
            /* [in] */ VARIANT vProp);
        
        /* [id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetInfoEx )( 
            IADsPrintJobOperations __RPC_FAR * This,
            /* [in] */ VARIANT vProperties,
            /* [in] */ long lnReserved);
        
        /* [id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Status )( 
            IADsPrintJobOperations __RPC_FAR * This,
            /* [retval][out] */ long __RPC_FAR *retval);
        
        /* [id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_TimeElapsed )( 
            IADsPrintJobOperations __RPC_FAR * This,
            /* [retval][out] */ long __RPC_FAR *retval);
        
        /* [id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_PagesPrinted )( 
            IADsPrintJobOperations __RPC_FAR * This,
            /* [retval][out] */ long __RPC_FAR *retval);
        
        /* [id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Position )( 
            IADsPrintJobOperations __RPC_FAR * This,
            /* [retval][out] */ long __RPC_FAR *retval);
        
        /* [id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_Position )( 
            IADsPrintJobOperations __RPC_FAR * This,
            /* [in] */ long lnPosition);
        
        /* [id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Pause )( 
            IADsPrintJobOperations __RPC_FAR * This);
        
        /* [id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Resume )( 
            IADsPrintJobOperations __RPC_FAR * This);
        
        END_INTERFACE
    } IADsPrintJobOperationsVtbl;

    interface IADsPrintJobOperations
    {
        CONST_VTBL struct IADsPrintJobOperationsVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IADsPrintJobOperations_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IADsPrintJobOperations_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IADsPrintJobOperations_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IADsPrintJobOperations_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define IADsPrintJobOperations_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define IADsPrintJobOperations_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define IADsPrintJobOperations_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)


#define IADsPrintJobOperations_get_Name(This,retval)	\
    (This)->lpVtbl -> get_Name(This,retval)

#define IADsPrintJobOperations_get_Class(This,retval)	\
    (This)->lpVtbl -> get_Class(This,retval)

#define IADsPrintJobOperations_get_GUID(This,retval)	\
    (This)->lpVtbl -> get_GUID(This,retval)

#define IADsPrintJobOperations_get_ADsPath(This,retval)	\
    (This)->lpVtbl -> get_ADsPath(This,retval)

#define IADsPrintJobOperations_get_Parent(This,retval)	\
    (This)->lpVtbl -> get_Parent(This,retval)

#define IADsPrintJobOperations_get_Schema(This,retval)	\
    (This)->lpVtbl -> get_Schema(This,retval)

#define IADsPrintJobOperations_GetInfo(This)	\
    (This)->lpVtbl -> GetInfo(This)

#define IADsPrintJobOperations_SetInfo(This)	\
    (This)->lpVtbl -> SetInfo(This)

#define IADsPrintJobOperations_Get(This,bstrName,pvProp)	\
    (This)->lpVtbl -> Get(This,bstrName,pvProp)

#define IADsPrintJobOperations_Put(This,bstrName,vProp)	\
    (This)->lpVtbl -> Put(This,bstrName,vProp)

#define IADsPrintJobOperations_GetEx(This,bstrName,pvProp)	\
    (This)->lpVtbl -> GetEx(This,bstrName,pvProp)

#define IADsPrintJobOperations_PutEx(This,lnControlCode,bstrName,vProp)	\
    (This)->lpVtbl -> PutEx(This,lnControlCode,bstrName,vProp)

#define IADsPrintJobOperations_GetInfoEx(This,vProperties,lnReserved)	\
    (This)->lpVtbl -> GetInfoEx(This,vProperties,lnReserved)


#define IADsPrintJobOperations_get_Status(This,retval)	\
    (This)->lpVtbl -> get_Status(This,retval)

#define IADsPrintJobOperations_get_TimeElapsed(This,retval)	\
    (This)->lpVtbl -> get_TimeElapsed(This,retval)

#define IADsPrintJobOperations_get_PagesPrinted(This,retval)	\
    (This)->lpVtbl -> get_PagesPrinted(This,retval)

#define IADsPrintJobOperations_get_Position(This,retval)	\
    (This)->lpVtbl -> get_Position(This,retval)

#define IADsPrintJobOperations_put_Position(This,lnPosition)	\
    (This)->lpVtbl -> put_Position(This,lnPosition)

#define IADsPrintJobOperations_Pause(This)	\
    (This)->lpVtbl -> Pause(This)

#define IADsPrintJobOperations_Resume(This)	\
    (This)->lpVtbl -> Resume(This)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [id][propget] */ HRESULT STDMETHODCALLTYPE IADsPrintJobOperations_get_Status_Proxy( 
    IADsPrintJobOperations __RPC_FAR * This,
    /* [retval][out] */ long __RPC_FAR *retval);


void __RPC_STUB IADsPrintJobOperations_get_Status_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [id][propget] */ HRESULT STDMETHODCALLTYPE IADsPrintJobOperations_get_TimeElapsed_Proxy( 
    IADsPrintJobOperations __RPC_FAR * This,
    /* [retval][out] */ long __RPC_FAR *retval);


void __RPC_STUB IADsPrintJobOperations_get_TimeElapsed_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [id][propget] */ HRESULT STDMETHODCALLTYPE IADsPrintJobOperations_get_PagesPrinted_Proxy( 
    IADsPrintJobOperations __RPC_FAR * This,
    /* [retval][out] */ long __RPC_FAR *retval);


void __RPC_STUB IADsPrintJobOperations_get_PagesPrinted_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [id][propget] */ HRESULT STDMETHODCALLTYPE IADsPrintJobOperations_get_Position_Proxy( 
    IADsPrintJobOperations __RPC_FAR * This,
    /* [retval][out] */ long __RPC_FAR *retval);


void __RPC_STUB IADsPrintJobOperations_get_Position_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [id][propput] */ HRESULT STDMETHODCALLTYPE IADsPrintJobOperations_put_Position_Proxy( 
    IADsPrintJobOperations __RPC_FAR * This,
    /* [in] */ long lnPosition);


void __RPC_STUB IADsPrintJobOperations_put_Position_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [id] */ HRESULT STDMETHODCALLTYPE IADsPrintJobOperations_Pause_Proxy( 
    IADsPrintJobOperations __RPC_FAR * This);


void __RPC_STUB IADsPrintJobOperations_Pause_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [id] */ HRESULT STDMETHODCALLTYPE IADsPrintJobOperations_Resume_Proxy( 
    IADsPrintJobOperations __RPC_FAR * This);


void __RPC_STUB IADsPrintJobOperations_Resume_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IADsPrintJobOperations_INTERFACE_DEFINED__ */


#ifndef __IADsService_INTERFACE_DEFINED__
#define __IADsService_INTERFACE_DEFINED__

/****************************************
 * Generated header for interface: IADsService
 * at Mon Oct 13 13:47:30 1997
 * using MIDL 3.00.44
 ****************************************/
/* [object][dual][oleautomation][uuid] */ 



EXTERN_C const IID IID_IADsService;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    interface IADsService : public IADs
    {
    public:
        virtual /* [id][propget] */ HRESULT STDMETHODCALLTYPE get_HostComputer( 
            /* [retval][out] */ BSTR __RPC_FAR *retval) = 0;
        
        virtual /* [id][propput] */ HRESULT STDMETHODCALLTYPE put_HostComputer( 
            /* [in] */ BSTR bstrHostComputer) = 0;
        
        virtual /* [id][propget] */ HRESULT STDMETHODCALLTYPE get_DisplayName( 
            /* [retval][out] */ BSTR __RPC_FAR *retval) = 0;
        
        virtual /* [id][propput] */ HRESULT STDMETHODCALLTYPE put_DisplayName( 
            /* [in] */ BSTR bstrDisplayName) = 0;
        
        virtual /* [id][propget] */ HRESULT STDMETHODCALLTYPE get_Version( 
            /* [retval][out] */ BSTR __RPC_FAR *retval) = 0;
        
        virtual /* [id][propput] */ HRESULT STDMETHODCALLTYPE put_Version( 
            /* [in] */ BSTR bstrVersion) = 0;
        
        virtual /* [id][propget] */ HRESULT STDMETHODCALLTYPE get_ServiceType( 
            /* [retval][out] */ long __RPC_FAR *retval) = 0;
        
        virtual /* [id][propput] */ HRESULT STDMETHODCALLTYPE put_ServiceType( 
            /* [in] */ long lnServiceType) = 0;
        
        virtual /* [id][propget] */ HRESULT STDMETHODCALLTYPE get_StartType( 
            /* [retval][out] */ long __RPC_FAR *retval) = 0;
        
        virtual /* [id][propput] */ HRESULT STDMETHODCALLTYPE put_StartType( 
            /* [in] */ long lnStartType) = 0;
        
        virtual /* [id][propget] */ HRESULT STDMETHODCALLTYPE get_Path( 
            /* [retval][out] */ BSTR __RPC_FAR *retval) = 0;
        
        virtual /* [id][propput] */ HRESULT STDMETHODCALLTYPE put_Path( 
            /* [in] */ BSTR bstrPath) = 0;
        
        virtual /* [id][propget] */ HRESULT STDMETHODCALLTYPE get_StartupParameters( 
            /* [retval][out] */ BSTR __RPC_FAR *retval) = 0;
        
        virtual /* [id][propput] */ HRESULT STDMETHODCALLTYPE put_StartupParameters( 
            /* [in] */ BSTR bstrStartupParameters) = 0;
        
        virtual /* [id][propget] */ HRESULT STDMETHODCALLTYPE get_ErrorControl( 
            /* [retval][out] */ long __RPC_FAR *retval) = 0;
        
        virtual /* [id][propput] */ HRESULT STDMETHODCALLTYPE put_ErrorControl( 
            /* [in] */ long lnErrorControl) = 0;
        
        virtual /* [id][propget] */ HRESULT STDMETHODCALLTYPE get_LoadOrderGroup( 
            /* [retval][out] */ BSTR __RPC_FAR *retval) = 0;
        
        virtual /* [id][propput] */ HRESULT STDMETHODCALLTYPE put_LoadOrderGroup( 
            /* [in] */ BSTR bstrLoadOrderGroup) = 0;
        
        virtual /* [id][propget] */ HRESULT STDMETHODCALLTYPE get_ServiceAccountName( 
            /* [retval][out] */ BSTR __RPC_FAR *retval) = 0;
        
        virtual /* [id][propput] */ HRESULT STDMETHODCALLTYPE put_ServiceAccountName( 
            /* [in] */ BSTR bstrServiceAccountName) = 0;
        
        virtual /* [id][propget] */ HRESULT STDMETHODCALLTYPE get_ServiceAccountPath( 
            /* [retval][out] */ BSTR __RPC_FAR *retval) = 0;
        
        virtual /* [id][propput] */ HRESULT STDMETHODCALLTYPE put_ServiceAccountPath( 
            /* [in] */ BSTR bstrServiceAccountPath) = 0;
        
        virtual /* [id][propget] */ HRESULT STDMETHODCALLTYPE get_Dependencies( 
            /* [retval][out] */ VARIANT __RPC_FAR *retval) = 0;
        
        virtual /* [id][propput] */ HRESULT STDMETHODCALLTYPE put_Dependencies( 
            /* [in] */ VARIANT vDependencies) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IADsServiceVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            IADsService __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            IADsService __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            IADsService __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfoCount )( 
            IADsService __RPC_FAR * This,
            /* [out] */ UINT __RPC_FAR *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfo )( 
            IADsService __RPC_FAR * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo __RPC_FAR *__RPC_FAR *ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetIDsOfNames )( 
            IADsService __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR __RPC_FAR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID __RPC_FAR *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Invoke )( 
            IADsService __RPC_FAR * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS __RPC_FAR *pDispParams,
            /* [out] */ VARIANT __RPC_FAR *pVarResult,
            /* [out] */ EXCEPINFO __RPC_FAR *pExcepInfo,
            /* [out] */ UINT __RPC_FAR *puArgErr);
        
        /* [id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Name )( 
            IADsService __RPC_FAR * This,
            /* [retval][out] */ BSTR __RPC_FAR *retval);
        
        /* [id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Class )( 
            IADsService __RPC_FAR * This,
            /* [retval][out] */ BSTR __RPC_FAR *retval);
        
        /* [id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_GUID )( 
            IADsService __RPC_FAR * This,
            /* [retval][out] */ BSTR __RPC_FAR *retval);
        
        /* [id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_ADsPath )( 
            IADsService __RPC_FAR * This,
            /* [retval][out] */ BSTR __RPC_FAR *retval);
        
        /* [id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Parent )( 
            IADsService __RPC_FAR * This,
            /* [retval][out] */ BSTR __RPC_FAR *retval);
        
        /* [id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Schema )( 
            IADsService __RPC_FAR * This,
            /* [retval][out] */ BSTR __RPC_FAR *retval);
        
        /* [id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetInfo )( 
            IADsService __RPC_FAR * This);
        
        /* [id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *SetInfo )( 
            IADsService __RPC_FAR * This);
        
        /* [id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Get )( 
            IADsService __RPC_FAR * This,
            /* [in] */ BSTR bstrName,
            /* [retval][out] */ VARIANT __RPC_FAR *pvProp);
        
        /* [id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Put )( 
            IADsService __RPC_FAR * This,
            /* [in] */ BSTR bstrName,
            /* [in] */ VARIANT vProp);
        
        /* [id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetEx )( 
            IADsService __RPC_FAR * This,
            /* [in] */ BSTR bstrName,
            /* [retval][out] */ VARIANT __RPC_FAR *pvProp);
        
        /* [id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *PutEx )( 
            IADsService __RPC_FAR * This,
            /* [in] */ long lnControlCode,
            /* [in] */ BSTR bstrName,
            /* [in] */ VARIANT vProp);
        
        /* [id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetInfoEx )( 
            IADsService __RPC_FAR * This,
            /* [in] */ VARIANT vProperties,
            /* [in] */ long lnReserved);
        
        /* [id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_HostComputer )( 
            IADsService __RPC_FAR * This,
            /* [retval][out] */ BSTR __RPC_FAR *retval);
        
        /* [id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_HostComputer )( 
            IADsService __RPC_FAR * This,
            /* [in] */ BSTR bstrHostComputer);
        
        /* [id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_DisplayName )( 
            IADsService __RPC_FAR * This,
            /* [retval][out] */ BSTR __RPC_FAR *retval);
        
        /* [id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_DisplayName )( 
            IADsService __RPC_FAR * This,
            /* [in] */ BSTR bstrDisplayName);
        
        /* [id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Version )( 
            IADsService __RPC_FAR * This,
            /* [retval][out] */ BSTR __RPC_FAR *retval);
        
        /* [id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_Version )( 
            IADsService __RPC_FAR * This,
            /* [in] */ BSTR bstrVersion);
        
        /* [id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_ServiceType )( 
            IADsService __RPC_FAR * This,
            /* [retval][out] */ long __RPC_FAR *retval);
        
        /* [id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_ServiceType )( 
            IADsService __RPC_FAR * This,
            /* [in] */ long lnServiceType);
        
        /* [id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_StartType )( 
            IADsService __RPC_FAR * This,
            /* [retval][out] */ long __RPC_FAR *retval);
        
        /* [id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_StartType )( 
            IADsService __RPC_FAR * This,
            /* [in] */ long lnStartType);
        
        /* [id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Path )( 
            IADsService __RPC_FAR * This,
            /* [retval][out] */ BSTR __RPC_FAR *retval);
        
        /* [id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_Path )( 
            IADsService __RPC_FAR * This,
            /* [in] */ BSTR bstrPath);
        
        /* [id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_StartupParameters )( 
            IADsService __RPC_FAR * This,
            /* [retval][out] */ BSTR __RPC_FAR *retval);
        
        /* [id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_StartupParameters )( 
            IADsService __RPC_FAR * This,
            /* [in] */ BSTR bstrStartupParameters);
        
        /* [id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_ErrorControl )( 
            IADsService __RPC_FAR * This,
            /* [retval][out] */ long __RPC_FAR *retval);
        
        /* [id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_ErrorControl )( 
            IADsService __RPC_FAR * This,
            /* [in] */ long lnErrorControl);
        
        /* [id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_LoadOrderGroup )( 
            IADsService __RPC_FAR * This,
            /* [retval][out] */ BSTR __RPC_FAR *retval);
        
        /* [id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_LoadOrderGroup )( 
            IADsService __RPC_FAR * This,
            /* [in] */ BSTR bstrLoadOrderGroup);
        
        /* [id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_ServiceAccountName )( 
            IADsService __RPC_FAR * This,
            /* [retval][out] */ BSTR __RPC_FAR *retval);
        
        /* [id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_ServiceAccountName )( 
            IADsService __RPC_FAR * This,
            /* [in] */ BSTR bstrServiceAccountName);
        
        /* [id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_ServiceAccountPath )( 
            IADsService __RPC_FAR * This,
            /* [retval][out] */ BSTR __RPC_FAR *retval);
        
        /* [id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_ServiceAccountPath )( 
            IADsService __RPC_FAR * This,
            /* [in] */ BSTR bstrServiceAccountPath);
        
        /* [id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Dependencies )( 
            IADsService __RPC_FAR * This,
            /* [retval][out] */ VARIANT __RPC_FAR *retval);
        
        /* [id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_Dependencies )( 
            IADsService __RPC_FAR * This,
            /* [in] */ VARIANT vDependencies);
        
        END_INTERFACE
    } IADsServiceVtbl;

    interface IADsService
    {
        CONST_VTBL struct IADsServiceVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IADsService_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IADsService_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IADsService_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IADsService_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define IADsService_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define IADsService_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define IADsService_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)


#define IADsService_get_Name(This,retval)	\
    (This)->lpVtbl -> get_Name(This,retval)

#define IADsService_get_Class(This,retval)	\
    (This)->lpVtbl -> get_Class(This,retval)

#define IADsService_get_GUID(This,retval)	\
    (This)->lpVtbl -> get_GUID(This,retval)

#define IADsService_get_ADsPath(This,retval)	\
    (This)->lpVtbl -> get_ADsPath(This,retval)

#define IADsService_get_Parent(This,retval)	\
    (This)->lpVtbl -> get_Parent(This,retval)

#define IADsService_get_Schema(This,retval)	\
    (This)->lpVtbl -> get_Schema(This,retval)

#define IADsService_GetInfo(This)	\
    (This)->lpVtbl -> GetInfo(This)

#define IADsService_SetInfo(This)	\
    (This)->lpVtbl -> SetInfo(This)

#define IADsService_Get(This,bstrName,pvProp)	\
    (This)->lpVtbl -> Get(This,bstrName,pvProp)

#define IADsService_Put(This,bstrName,vProp)	\
    (This)->lpVtbl -> Put(This,bstrName,vProp)

#define IADsService_GetEx(This,bstrName,pvProp)	\
    (This)->lpVtbl -> GetEx(This,bstrName,pvProp)

#define IADsService_PutEx(This,lnControlCode,bstrName,vProp)	\
    (This)->lpVtbl -> PutEx(This,lnControlCode,bstrName,vProp)

#define IADsService_GetInfoEx(This,vProperties,lnReserved)	\
    (This)->lpVtbl -> GetInfoEx(This,vProperties,lnReserved)


#define IADsService_get_HostComputer(This,retval)	\
    (This)->lpVtbl -> get_HostComputer(This,retval)

#define IADsService_put_HostComputer(This,bstrHostComputer)	\
    (This)->lpVtbl -> put_HostComputer(This,bstrHostComputer)

#define IADsService_get_DisplayName(This,retval)	\
    (This)->lpVtbl -> get_DisplayName(This,retval)

#define IADsService_put_DisplayName(This,bstrDisplayName)	\
    (This)->lpVtbl -> put_DisplayName(This,bstrDisplayName)

#define IADsService_get_Version(This,retval)	\
    (This)->lpVtbl -> get_Version(This,retval)

#define IADsService_put_Version(This,bstrVersion)	\
    (This)->lpVtbl -> put_Version(This,bstrVersion)

#define IADsService_get_ServiceType(This,retval)	\
    (This)->lpVtbl -> get_ServiceType(This,retval)

#define IADsService_put_ServiceType(This,lnServiceType)	\
    (This)->lpVtbl -> put_ServiceType(This,lnServiceType)

#define IADsService_get_StartType(This,retval)	\
    (This)->lpVtbl -> get_StartType(This,retval)

#define IADsService_put_StartType(This,lnStartType)	\
    (This)->lpVtbl -> put_StartType(This,lnStartType)

#define IADsService_get_Path(This,retval)	\
    (This)->lpVtbl -> get_Path(This,retval)

#define IADsService_put_Path(This,bstrPath)	\
    (This)->lpVtbl -> put_Path(This,bstrPath)

#define IADsService_get_StartupParameters(This,retval)	\
    (This)->lpVtbl -> get_StartupParameters(This,retval)

#define IADsService_put_StartupParameters(This,bstrStartupParameters)	\
    (This)->lpVtbl -> put_StartupParameters(This,bstrStartupParameters)

#define IADsService_get_ErrorControl(This,retval)	\
    (This)->lpVtbl -> get_ErrorControl(This,retval)

#define IADsService_put_ErrorControl(This,lnErrorControl)	\
    (This)->lpVtbl -> put_ErrorControl(This,lnErrorControl)

#define IADsService_get_LoadOrderGroup(This,retval)	\
    (This)->lpVtbl -> get_LoadOrderGroup(This,retval)

#define IADsService_put_LoadOrderGroup(This,bstrLoadOrderGroup)	\
    (This)->lpVtbl -> put_LoadOrderGroup(This,bstrLoadOrderGroup)

#define IADsService_get_ServiceAccountName(This,retval)	\
    (This)->lpVtbl -> get_ServiceAccountName(This,retval)

#define IADsService_put_ServiceAccountName(This,bstrServiceAccountName)	\
    (This)->lpVtbl -> put_ServiceAccountName(This,bstrServiceAccountName)

#define IADsService_get_ServiceAccountPath(This,retval)	\
    (This)->lpVtbl -> get_ServiceAccountPath(This,retval)

#define IADsService_put_ServiceAccountPath(This,bstrServiceAccountPath)	\
    (This)->lpVtbl -> put_ServiceAccountPath(This,bstrServiceAccountPath)

#define IADsService_get_Dependencies(This,retval)	\
    (This)->lpVtbl -> get_Dependencies(This,retval)

#define IADsService_put_Dependencies(This,vDependencies)	\
    (This)->lpVtbl -> put_Dependencies(This,vDependencies)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [id][propget] */ HRESULT STDMETHODCALLTYPE IADsService_get_HostComputer_Proxy( 
    IADsService __RPC_FAR * This,
    /* [retval][out] */ BSTR __RPC_FAR *retval);


void __RPC_STUB IADsService_get_HostComputer_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [id][propput] */ HRESULT STDMETHODCALLTYPE IADsService_put_HostComputer_Proxy( 
    IADsService __RPC_FAR * This,
    /* [in] */ BSTR bstrHostComputer);


void __RPC_STUB IADsService_put_HostComputer_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [id][propget] */ HRESULT STDMETHODCALLTYPE IADsService_get_DisplayName_Proxy( 
    IADsService __RPC_FAR * This,
    /* [retval][out] */ BSTR __RPC_FAR *retval);


void __RPC_STUB IADsService_get_DisplayName_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [id][propput] */ HRESULT STDMETHODCALLTYPE IADsService_put_DisplayName_Proxy( 
    IADsService __RPC_FAR * This,
    /* [in] */ BSTR bstrDisplayName);


void __RPC_STUB IADsService_put_DisplayName_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [id][propget] */ HRESULT STDMETHODCALLTYPE IADsService_get_Version_Proxy( 
    IADsService __RPC_FAR * This,
    /* [retval][out] */ BSTR __RPC_FAR *retval);


void __RPC_STUB IADsService_get_Version_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [id][propput] */ HRESULT STDMETHODCALLTYPE IADsService_put_Version_Proxy( 
    IADsService __RPC_FAR * This,
    /* [in] */ BSTR bstrVersion);


void __RPC_STUB IADsService_put_Version_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [id][propget] */ HRESULT STDMETHODCALLTYPE IADsService_get_ServiceType_Proxy( 
    IADsService __RPC_FAR * This,
    /* [retval][out] */ long __RPC_FAR *retval);


void __RPC_STUB IADsService_get_ServiceType_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [id][propput] */ HRESULT STDMETHODCALLTYPE IADsService_put_ServiceType_Proxy( 
    IADsService __RPC_FAR * This,
    /* [in] */ long lnServiceType);


void __RPC_STUB IADsService_put_ServiceType_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [id][propget] */ HRESULT STDMETHODCALLTYPE IADsService_get_StartType_Proxy( 
    IADsService __RPC_FAR * This,
    /* [retval][out] */ long __RPC_FAR *retval);


void __RPC_STUB IADsService_get_StartType_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [id][propput] */ HRESULT STDMETHODCALLTYPE IADsService_put_StartType_Proxy( 
    IADsService __RPC_FAR * This,
    /* [in] */ long lnStartType);


void __RPC_STUB IADsService_put_StartType_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [id][propget] */ HRESULT STDMETHODCALLTYPE IADsService_get_Path_Proxy( 
    IADsService __RPC_FAR * This,
    /* [retval][out] */ BSTR __RPC_FAR *retval);


void __RPC_STUB IADsService_get_Path_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [id][propput] */ HRESULT STDMETHODCALLTYPE IADsService_put_Path_Proxy( 
    IADsService __RPC_FAR * This,
    /* [in] */ BSTR bstrPath);


void __RPC_STUB IADsService_put_Path_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [id][propget] */ HRESULT STDMETHODCALLTYPE IADsService_get_StartupParameters_Proxy( 
    IADsService __RPC_FAR * This,
    /* [retval][out] */ BSTR __RPC_FAR *retval);


void __RPC_STUB IADsService_get_StartupParameters_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [id][propput] */ HRESULT STDMETHODCALLTYPE IADsService_put_StartupParameters_Proxy( 
    IADsService __RPC_FAR * This,
    /* [in] */ BSTR bstrStartupParameters);


void __RPC_STUB IADsService_put_StartupParameters_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [id][propget] */ HRESULT STDMETHODCALLTYPE IADsService_get_ErrorControl_Proxy( 
    IADsService __RPC_FAR * This,
    /* [retval][out] */ long __RPC_FAR *retval);


void __RPC_STUB IADsService_get_ErrorControl_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [id][propput] */ HRESULT STDMETHODCALLTYPE IADsService_put_ErrorControl_Proxy( 
    IADsService __RPC_FAR * This,
    /* [in] */ long lnErrorControl);


void __RPC_STUB IADsService_put_ErrorControl_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [id][propget] */ HRESULT STDMETHODCALLTYPE IADsService_get_LoadOrderGroup_Proxy( 
    IADsService __RPC_FAR * This,
    /* [retval][out] */ BSTR __RPC_FAR *retval);


void __RPC_STUB IADsService_get_LoadOrderGroup_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [id][propput] */ HRESULT STDMETHODCALLTYPE IADsService_put_LoadOrderGroup_Proxy( 
    IADsService __RPC_FAR * This,
    /* [in] */ BSTR bstrLoadOrderGroup);


void __RPC_STUB IADsService_put_LoadOrderGroup_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [id][propget] */ HRESULT STDMETHODCALLTYPE IADsService_get_ServiceAccountName_Proxy( 
    IADsService __RPC_FAR * This,
    /* [retval][out] */ BSTR __RPC_FAR *retval);


void __RPC_STUB IADsService_get_ServiceAccountName_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [id][propput] */ HRESULT STDMETHODCALLTYPE IADsService_put_ServiceAccountName_Proxy( 
    IADsService __RPC_FAR * This,
    /* [in] */ BSTR bstrServiceAccountName);


void __RPC_STUB IADsService_put_ServiceAccountName_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [id][propget] */ HRESULT STDMETHODCALLTYPE IADsService_get_ServiceAccountPath_Proxy( 
    IADsService __RPC_FAR * This,
    /* [retval][out] */ BSTR __RPC_FAR *retval);


void __RPC_STUB IADsService_get_ServiceAccountPath_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [id][propput] */ HRESULT STDMETHODCALLTYPE IADsService_put_ServiceAccountPath_Proxy( 
    IADsService __RPC_FAR * This,
    /* [in] */ BSTR bstrServiceAccountPath);


void __RPC_STUB IADsService_put_ServiceAccountPath_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [id][propget] */ HRESULT STDMETHODCALLTYPE IADsService_get_Dependencies_Proxy( 
    IADsService __RPC_FAR * This,
    /* [retval][out] */ VARIANT __RPC_FAR *retval);


void __RPC_STUB IADsService_get_Dependencies_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [id][propput] */ HRESULT STDMETHODCALLTYPE IADsService_put_Dependencies_Proxy( 
    IADsService __RPC_FAR * This,
    /* [in] */ VARIANT vDependencies);


void __RPC_STUB IADsService_put_Dependencies_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IADsService_INTERFACE_DEFINED__ */


#ifndef __IADsServiceOperations_INTERFACE_DEFINED__
#define __IADsServiceOperations_INTERFACE_DEFINED__

/****************************************
 * Generated header for interface: IADsServiceOperations
 * at Mon Oct 13 13:47:30 1997
 * using MIDL 3.00.44
 ****************************************/
/* [object][dual][oleautomation][uuid] */ 



EXTERN_C const IID IID_IADsServiceOperations;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    interface IADsServiceOperations : public IADs
    {
    public:
        virtual /* [id][propget] */ HRESULT STDMETHODCALLTYPE get_Status( 
            /* [retval][out] */ long __RPC_FAR *retval) = 0;
        
        virtual /* [id] */ HRESULT STDMETHODCALLTYPE Start( void) = 0;
        
        virtual /* [id] */ HRESULT STDMETHODCALLTYPE Stop( void) = 0;
        
        virtual /* [id] */ HRESULT STDMETHODCALLTYPE Pause( void) = 0;
        
        virtual /* [id] */ HRESULT STDMETHODCALLTYPE Continue( void) = 0;
        
        virtual /* [id] */ HRESULT STDMETHODCALLTYPE SetPassword( 
            /* [in] */ BSTR bstrNewPassword) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IADsServiceOperationsVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            IADsServiceOperations __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            IADsServiceOperations __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            IADsServiceOperations __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfoCount )( 
            IADsServiceOperations __RPC_FAR * This,
            /* [out] */ UINT __RPC_FAR *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfo )( 
            IADsServiceOperations __RPC_FAR * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo __RPC_FAR *__RPC_FAR *ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetIDsOfNames )( 
            IADsServiceOperations __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR __RPC_FAR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID __RPC_FAR *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Invoke )( 
            IADsServiceOperations __RPC_FAR * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS __RPC_FAR *pDispParams,
            /* [out] */ VARIANT __RPC_FAR *pVarResult,
            /* [out] */ EXCEPINFO __RPC_FAR *pExcepInfo,
            /* [out] */ UINT __RPC_FAR *puArgErr);
        
        /* [id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Name )( 
            IADsServiceOperations __RPC_FAR * This,
            /* [retval][out] */ BSTR __RPC_FAR *retval);
        
        /* [id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Class )( 
            IADsServiceOperations __RPC_FAR * This,
            /* [retval][out] */ BSTR __RPC_FAR *retval);
        
        /* [id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_GUID )( 
            IADsServiceOperations __RPC_FAR * This,
            /* [retval][out] */ BSTR __RPC_FAR *retval);
        
        /* [id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_ADsPath )( 
            IADsServiceOperations __RPC_FAR * This,
            /* [retval][out] */ BSTR __RPC_FAR *retval);
        
        /* [id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Parent )( 
            IADsServiceOperations __RPC_FAR * This,
            /* [retval][out] */ BSTR __RPC_FAR *retval);
        
        /* [id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Schema )( 
            IADsServiceOperations __RPC_FAR * This,
            /* [retval][out] */ BSTR __RPC_FAR *retval);
        
        /* [id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetInfo )( 
            IADsServiceOperations __RPC_FAR * This);
        
        /* [id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *SetInfo )( 
            IADsServiceOperations __RPC_FAR * This);
        
        /* [id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Get )( 
            IADsServiceOperations __RPC_FAR * This,
            /* [in] */ BSTR bstrName,
            /* [retval][out] */ VARIANT __RPC_FAR *pvProp);
        
        /* [id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Put )( 
            IADsServiceOperations __RPC_FAR * This,
            /* [in] */ BSTR bstrName,
            /* [in] */ VARIANT vProp);
        
        /* [id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetEx )( 
            IADsServiceOperations __RPC_FAR * This,
            /* [in] */ BSTR bstrName,
            /* [retval][out] */ VARIANT __RPC_FAR *pvProp);
        
        /* [id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *PutEx )( 
            IADsServiceOperations __RPC_FAR * This,
            /* [in] */ long lnControlCode,
            /* [in] */ BSTR bstrName,
            /* [in] */ VARIANT vProp);
        
        /* [id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetInfoEx )( 
            IADsServiceOperations __RPC_FAR * This,
            /* [in] */ VARIANT vProperties,
            /* [in] */ long lnReserved);
        
        /* [id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Status )( 
            IADsServiceOperations __RPC_FAR * This,
            /* [retval][out] */ long __RPC_FAR *retval);
        
        /* [id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Start )( 
            IADsServiceOperations __RPC_FAR * This);
        
        /* [id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Stop )( 
            IADsServiceOperations __RPC_FAR * This);
        
        /* [id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Pause )( 
            IADsServiceOperations __RPC_FAR * This);
        
        /* [id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Continue )( 
            IADsServiceOperations __RPC_FAR * This);
        
        /* [id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *SetPassword )( 
            IADsServiceOperations __RPC_FAR * This,
            /* [in] */ BSTR bstrNewPassword);
        
        END_INTERFACE
    } IADsServiceOperationsVtbl;

    interface IADsServiceOperations
    {
        CONST_VTBL struct IADsServiceOperationsVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IADsServiceOperations_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IADsServiceOperations_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IADsServiceOperations_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IADsServiceOperations_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define IADsServiceOperations_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define IADsServiceOperations_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define IADsServiceOperations_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)


#define IADsServiceOperations_get_Name(This,retval)	\
    (This)->lpVtbl -> get_Name(This,retval)

#define IADsServiceOperations_get_Class(This,retval)	\
    (This)->lpVtbl -> get_Class(This,retval)

#define IADsServiceOperations_get_GUID(This,retval)	\
    (This)->lpVtbl -> get_GUID(This,retval)

#define IADsServiceOperations_get_ADsPath(This,retval)	\
    (This)->lpVtbl -> get_ADsPath(This,retval)

#define IADsServiceOperations_get_Parent(This,retval)	\
    (This)->lpVtbl -> get_Parent(This,retval)

#define IADsServiceOperations_get_Schema(This,retval)	\
    (This)->lpVtbl -> get_Schema(This,retval)

#define IADsServiceOperations_GetInfo(This)	\
    (This)->lpVtbl -> GetInfo(This)

#define IADsServiceOperations_SetInfo(This)	\
    (This)->lpVtbl -> SetInfo(This)

#define IADsServiceOperations_Get(This,bstrName,pvProp)	\
    (This)->lpVtbl -> Get(This,bstrName,pvProp)

#define IADsServiceOperations_Put(This,bstrName,vProp)	\
    (This)->lpVtbl -> Put(This,bstrName,vProp)

#define IADsServiceOperations_GetEx(This,bstrName,pvProp)	\
    (This)->lpVtbl -> GetEx(This,bstrName,pvProp)

#define IADsServiceOperations_PutEx(This,lnControlCode,bstrName,vProp)	\
    (This)->lpVtbl -> PutEx(This,lnControlCode,bstrName,vProp)

#define IADsServiceOperations_GetInfoEx(This,vProperties,lnReserved)	\
    (This)->lpVtbl -> GetInfoEx(This,vProperties,lnReserved)


#define IADsServiceOperations_get_Status(This,retval)	\
    (This)->lpVtbl -> get_Status(This,retval)

#define IADsServiceOperations_Start(This)	\
    (This)->lpVtbl -> Start(This)

#define IADsServiceOperations_Stop(This)	\
    (This)->lpVtbl -> Stop(This)

#define IADsServiceOperations_Pause(This)	\
    (This)->lpVtbl -> Pause(This)

#define IADsServiceOperations_Continue(This)	\
    (This)->lpVtbl -> Continue(This)

#define IADsServiceOperations_SetPassword(This,bstrNewPassword)	\
    (This)->lpVtbl -> SetPassword(This,bstrNewPassword)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [id][propget] */ HRESULT STDMETHODCALLTYPE IADsServiceOperations_get_Status_Proxy( 
    IADsServiceOperations __RPC_FAR * This,
    /* [retval][out] */ long __RPC_FAR *retval);


void __RPC_STUB IADsServiceOperations_get_Status_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [id] */ HRESULT STDMETHODCALLTYPE IADsServiceOperations_Start_Proxy( 
    IADsServiceOperations __RPC_FAR * This);


void __RPC_STUB IADsServiceOperations_Start_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [id] */ HRESULT STDMETHODCALLTYPE IADsServiceOperations_Stop_Proxy( 
    IADsServiceOperations __RPC_FAR * This);


void __RPC_STUB IADsServiceOperations_Stop_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [id] */ HRESULT STDMETHODCALLTYPE IADsServiceOperations_Pause_Proxy( 
    IADsServiceOperations __RPC_FAR * This);


void __RPC_STUB IADsServiceOperations_Pause_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [id] */ HRESULT STDMETHODCALLTYPE IADsServiceOperations_Continue_Proxy( 
    IADsServiceOperations __RPC_FAR * This);


void __RPC_STUB IADsServiceOperations_Continue_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [id] */ HRESULT STDMETHODCALLTYPE IADsServiceOperations_SetPassword_Proxy( 
    IADsServiceOperations __RPC_FAR * This,
    /* [in] */ BSTR bstrNewPassword);


void __RPC_STUB IADsServiceOperations_SetPassword_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IADsServiceOperations_INTERFACE_DEFINED__ */


#ifndef __IADsFileService_INTERFACE_DEFINED__
#define __IADsFileService_INTERFACE_DEFINED__

/****************************************
 * Generated header for interface: IADsFileService
 * at Mon Oct 13 13:47:30 1997
 * using MIDL 3.00.44
 ****************************************/
/* [object][dual][oleautomation][uuid] */ 



EXTERN_C const IID IID_IADsFileService;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    interface IADsFileService : public IADsService
    {
    public:
        virtual /* [id][propget] */ HRESULT STDMETHODCALLTYPE get_Description( 
            /* [retval][out] */ BSTR __RPC_FAR *retval) = 0;
        
        virtual /* [id][propput] */ HRESULT STDMETHODCALLTYPE put_Description( 
            /* [in] */ BSTR bstrDescription) = 0;
        
        virtual /* [id][propget] */ HRESULT STDMETHODCALLTYPE get_MaxUserCount( 
            /* [retval][out] */ long __RPC_FAR *retval) = 0;
        
        virtual /* [id][propput] */ HRESULT STDMETHODCALLTYPE put_MaxUserCount( 
            /* [in] */ long lnMaxUserCount) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IADsFileServiceVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            IADsFileService __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            IADsFileService __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            IADsFileService __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfoCount )( 
            IADsFileService __RPC_FAR * This,
            /* [out] */ UINT __RPC_FAR *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfo )( 
            IADsFileService __RPC_FAR * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo __RPC_FAR *__RPC_FAR *ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetIDsOfNames )( 
            IADsFileService __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR __RPC_FAR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID __RPC_FAR *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Invoke )( 
            IADsFileService __RPC_FAR * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS __RPC_FAR *pDispParams,
            /* [out] */ VARIANT __RPC_FAR *pVarResult,
            /* [out] */ EXCEPINFO __RPC_FAR *pExcepInfo,
            /* [out] */ UINT __RPC_FAR *puArgErr);
        
        /* [id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Name )( 
            IADsFileService __RPC_FAR * This,
            /* [retval][out] */ BSTR __RPC_FAR *retval);
        
        /* [id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Class )( 
            IADsFileService __RPC_FAR * This,
            /* [retval][out] */ BSTR __RPC_FAR *retval);
        
        /* [id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_GUID )( 
            IADsFileService __RPC_FAR * This,
            /* [retval][out] */ BSTR __RPC_FAR *retval);
        
        /* [id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_ADsPath )( 
            IADsFileService __RPC_FAR * This,
            /* [retval][out] */ BSTR __RPC_FAR *retval);
        
        /* [id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Parent )( 
            IADsFileService __RPC_FAR * This,
            /* [retval][out] */ BSTR __RPC_FAR *retval);
        
        /* [id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Schema )( 
            IADsFileService __RPC_FAR * This,
            /* [retval][out] */ BSTR __RPC_FAR *retval);
        
        /* [id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetInfo )( 
            IADsFileService __RPC_FAR * This);
        
        /* [id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *SetInfo )( 
            IADsFileService __RPC_FAR * This);
        
        /* [id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Get )( 
            IADsFileService __RPC_FAR * This,
            /* [in] */ BSTR bstrName,
            /* [retval][out] */ VARIANT __RPC_FAR *pvProp);
        
        /* [id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Put )( 
            IADsFileService __RPC_FAR * This,
            /* [in] */ BSTR bstrName,
            /* [in] */ VARIANT vProp);
        
        /* [id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetEx )( 
            IADsFileService __RPC_FAR * This,
            /* [in] */ BSTR bstrName,
            /* [retval][out] */ VARIANT __RPC_FAR *pvProp);
        
        /* [id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *PutEx )( 
            IADsFileService __RPC_FAR * This,
            /* [in] */ long lnControlCode,
            /* [in] */ BSTR bstrName,
            /* [in] */ VARIANT vProp);
        
        /* [id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetInfoEx )( 
            IADsFileService __RPC_FAR * This,
            /* [in] */ VARIANT vProperties,
            /* [in] */ long lnReserved);
        
        /* [id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_HostComputer )( 
            IADsFileService __RPC_FAR * This,
            /* [retval][out] */ BSTR __RPC_FAR *retval);
        
        /* [id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_HostComputer )( 
            IADsFileService __RPC_FAR * This,
            /* [in] */ BSTR bstrHostComputer);
        
        /* [id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_DisplayName )( 
            IADsFileService __RPC_FAR * This,
            /* [retval][out] */ BSTR __RPC_FAR *retval);
        
        /* [id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_DisplayName )( 
            IADsFileService __RPC_FAR * This,
            /* [in] */ BSTR bstrDisplayName);
        
        /* [id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Version )( 
            IADsFileService __RPC_FAR * This,
            /* [retval][out] */ BSTR __RPC_FAR *retval);
        
        /* [id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_Version )( 
            IADsFileService __RPC_FAR * This,
            /* [in] */ BSTR bstrVersion);
        
        /* [id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_ServiceType )( 
            IADsFileService __RPC_FAR * This,
            /* [retval][out] */ long __RPC_FAR *retval);
        
        /* [id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_ServiceType )( 
            IADsFileService __RPC_FAR * This,
            /* [in] */ long lnServiceType);
        
        /* [id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_StartType )( 
            IADsFileService __RPC_FAR * This,
            /* [retval][out] */ long __RPC_FAR *retval);
        
        /* [id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_StartType )( 
            IADsFileService __RPC_FAR * This,
            /* [in] */ long lnStartType);
        
        /* [id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Path )( 
            IADsFileService __RPC_FAR * This,
            /* [retval][out] */ BSTR __RPC_FAR *retval);
        
        /* [id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_Path )( 
            IADsFileService __RPC_FAR * This,
            /* [in] */ BSTR bstrPath);
        
        /* [id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_StartupParameters )( 
            IADsFileService __RPC_FAR * This,
            /* [retval][out] */ BSTR __RPC_FAR *retval);
        
        /* [id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_StartupParameters )( 
            IADsFileService __RPC_FAR * This,
            /* [in] */ BSTR bstrStartupParameters);
        
        /* [id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_ErrorControl )( 
            IADsFileService __RPC_FAR * This,
            /* [retval][out] */ long __RPC_FAR *retval);
        
        /* [id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_ErrorControl )( 
            IADsFileService __RPC_FAR * This,
            /* [in] */ long lnErrorControl);
        
        /* [id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_LoadOrderGroup )( 
            IADsFileService __RPC_FAR * This,
            /* [retval][out] */ BSTR __RPC_FAR *retval);
        
        /* [id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_LoadOrderGroup )( 
            IADsFileService __RPC_FAR * This,
            /* [in] */ BSTR bstrLoadOrderGroup);
        
        /* [id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_ServiceAccountName )( 
            IADsFileService __RPC_FAR * This,
            /* [retval][out] */ BSTR __RPC_FAR *retval);
        
        /* [id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_ServiceAccountName )( 
            IADsFileService __RPC_FAR * This,
            /* [in] */ BSTR bstrServiceAccountName);
        
        /* [id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_ServiceAccountPath )( 
            IADsFileService __RPC_FAR * This,
            /* [retval][out] */ BSTR __RPC_FAR *retval);
        
        /* [id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_ServiceAccountPath )( 
            IADsFileService __RPC_FAR * This,
            /* [in] */ BSTR bstrServiceAccountPath);
        
        /* [id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Dependencies )( 
            IADsFileService __RPC_FAR * This,
            /* [retval][out] */ VARIANT __RPC_FAR *retval);
        
        /* [id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_Dependencies )( 
            IADsFileService __RPC_FAR * This,
            /* [in] */ VARIANT vDependencies);
        
        /* [id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Description )( 
            IADsFileService __RPC_FAR * This,
            /* [retval][out] */ BSTR __RPC_FAR *retval);
        
        /* [id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_Description )( 
            IADsFileService __RPC_FAR * This,
            /* [in] */ BSTR bstrDescription);
        
        /* [id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_MaxUserCount )( 
            IADsFileService __RPC_FAR * This,
            /* [retval][out] */ long __RPC_FAR *retval);
        
        /* [id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_MaxUserCount )( 
            IADsFileService __RPC_FAR * This,
            /* [in] */ long lnMaxUserCount);
        
        END_INTERFACE
    } IADsFileServiceVtbl;

    interface IADsFileService
    {
        CONST_VTBL struct IADsFileServiceVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IADsFileService_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IADsFileService_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IADsFileService_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IADsFileService_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define IADsFileService_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define IADsFileService_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define IADsFileService_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)


#define IADsFileService_get_Name(This,retval)	\
    (This)->lpVtbl -> get_Name(This,retval)

#define IADsFileService_get_Class(This,retval)	\
    (This)->lpVtbl -> get_Class(This,retval)

#define IADsFileService_get_GUID(This,retval)	\
    (This)->lpVtbl -> get_GUID(This,retval)

#define IADsFileService_get_ADsPath(This,retval)	\
    (This)->lpVtbl -> get_ADsPath(This,retval)

#define IADsFileService_get_Parent(This,retval)	\
    (This)->lpVtbl -> get_Parent(This,retval)

#define IADsFileService_get_Schema(This,retval)	\
    (This)->lpVtbl -> get_Schema(This,retval)

#define IADsFileService_GetInfo(This)	\
    (This)->lpVtbl -> GetInfo(This)

#define IADsFileService_SetInfo(This)	\
    (This)->lpVtbl -> SetInfo(This)

#define IADsFileService_Get(This,bstrName,pvProp)	\
    (This)->lpVtbl -> Get(This,bstrName,pvProp)

#define IADsFileService_Put(This,bstrName,vProp)	\
    (This)->lpVtbl -> Put(This,bstrName,vProp)

#define IADsFileService_GetEx(This,bstrName,pvProp)	\
    (This)->lpVtbl -> GetEx(This,bstrName,pvProp)

#define IADsFileService_PutEx(This,lnControlCode,bstrName,vProp)	\
    (This)->lpVtbl -> PutEx(This,lnControlCode,bstrName,vProp)

#define IADsFileService_GetInfoEx(This,vProperties,lnReserved)	\
    (This)->lpVtbl -> GetInfoEx(This,vProperties,lnReserved)


#define IADsFileService_get_HostComputer(This,retval)	\
    (This)->lpVtbl -> get_HostComputer(This,retval)

#define IADsFileService_put_HostComputer(This,bstrHostComputer)	\
    (This)->lpVtbl -> put_HostComputer(This,bstrHostComputer)

#define IADsFileService_get_DisplayName(This,retval)	\
    (This)->lpVtbl -> get_DisplayName(This,retval)

#define IADsFileService_put_DisplayName(This,bstrDisplayName)	\
    (This)->lpVtbl -> put_DisplayName(This,bstrDisplayName)

#define IADsFileService_get_Version(This,retval)	\
    (This)->lpVtbl -> get_Version(This,retval)

#define IADsFileService_put_Version(This,bstrVersion)	\
    (This)->lpVtbl -> put_Version(This,bstrVersion)

#define IADsFileService_get_ServiceType(This,retval)	\
    (This)->lpVtbl -> get_ServiceType(This,retval)

#define IADsFileService_put_ServiceType(This,lnServiceType)	\
    (This)->lpVtbl -> put_ServiceType(This,lnServiceType)

#define IADsFileService_get_StartType(This,retval)	\
    (This)->lpVtbl -> get_StartType(This,retval)

#define IADsFileService_put_StartType(This,lnStartType)	\
    (This)->lpVtbl -> put_StartType(This,lnStartType)

#define IADsFileService_get_Path(This,retval)	\
    (This)->lpVtbl -> get_Path(This,retval)

#define IADsFileService_put_Path(This,bstrPath)	\
    (This)->lpVtbl -> put_Path(This,bstrPath)

#define IADsFileService_get_StartupParameters(This,retval)	\
    (This)->lpVtbl -> get_StartupParameters(This,retval)

#define IADsFileService_put_StartupParameters(This,bstrStartupParameters)	\
    (This)->lpVtbl -> put_StartupParameters(This,bstrStartupParameters)

#define IADsFileService_get_ErrorControl(This,retval)	\
    (This)->lpVtbl -> get_ErrorControl(This,retval)

#define IADsFileService_put_ErrorControl(This,lnErrorControl)	\
    (This)->lpVtbl -> put_ErrorControl(This,lnErrorControl)

#define IADsFileService_get_LoadOrderGroup(This,retval)	\
    (This)->lpVtbl -> get_LoadOrderGroup(This,retval)

#define IADsFileService_put_LoadOrderGroup(This,bstrLoadOrderGroup)	\
    (This)->lpVtbl -> put_LoadOrderGroup(This,bstrLoadOrderGroup)

#define IADsFileService_get_ServiceAccountName(This,retval)	\
    (This)->lpVtbl -> get_ServiceAccountName(This,retval)

#define IADsFileService_put_ServiceAccountName(This,bstrServiceAccountName)	\
    (This)->lpVtbl -> put_ServiceAccountName(This,bstrServiceAccountName)

#define IADsFileService_get_ServiceAccountPath(This,retval)	\
    (This)->lpVtbl -> get_ServiceAccountPath(This,retval)

#define IADsFileService_put_ServiceAccountPath(This,bstrServiceAccountPath)	\
    (This)->lpVtbl -> put_ServiceAccountPath(This,bstrServiceAccountPath)

#define IADsFileService_get_Dependencies(This,retval)	\
    (This)->lpVtbl -> get_Dependencies(This,retval)

#define IADsFileService_put_Dependencies(This,vDependencies)	\
    (This)->lpVtbl -> put_Dependencies(This,vDependencies)


#define IADsFileService_get_Description(This,retval)	\
    (This)->lpVtbl -> get_Description(This,retval)

#define IADsFileService_put_Description(This,bstrDescription)	\
    (This)->lpVtbl -> put_Description(This,bstrDescription)

#define IADsFileService_get_MaxUserCount(This,retval)	\
    (This)->lpVtbl -> get_MaxUserCount(This,retval)

#define IADsFileService_put_MaxUserCount(This,lnMaxUserCount)	\
    (This)->lpVtbl -> put_MaxUserCount(This,lnMaxUserCount)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [id][propget] */ HRESULT STDMETHODCALLTYPE IADsFileService_get_Description_Proxy( 
    IADsFileService __RPC_FAR * This,
    /* [retval][out] */ BSTR __RPC_FAR *retval);


void __RPC_STUB IADsFileService_get_Description_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [id][propput] */ HRESULT STDMETHODCALLTYPE IADsFileService_put_Description_Proxy( 
    IADsFileService __RPC_FAR * This,
    /* [in] */ BSTR bstrDescription);


void __RPC_STUB IADsFileService_put_Description_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [id][propget] */ HRESULT STDMETHODCALLTYPE IADsFileService_get_MaxUserCount_Proxy( 
    IADsFileService __RPC_FAR * This,
    /* [retval][out] */ long __RPC_FAR *retval);


void __RPC_STUB IADsFileService_get_MaxUserCount_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [id][propput] */ HRESULT STDMETHODCALLTYPE IADsFileService_put_MaxUserCount_Proxy( 
    IADsFileService __RPC_FAR * This,
    /* [in] */ long lnMaxUserCount);


void __RPC_STUB IADsFileService_put_MaxUserCount_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IADsFileService_INTERFACE_DEFINED__ */


#ifndef __IADsFileServiceOperations_INTERFACE_DEFINED__
#define __IADsFileServiceOperations_INTERFACE_DEFINED__

/****************************************
 * Generated header for interface: IADsFileServiceOperations
 * at Mon Oct 13 13:47:30 1997
 * using MIDL 3.00.44
 ****************************************/
/* [object][dual][oleautomation][uuid] */ 



EXTERN_C const IID IID_IADsFileServiceOperations;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    interface IADsFileServiceOperations : public IADsServiceOperations
    {
    public:
        virtual /* [id] */ HRESULT STDMETHODCALLTYPE Sessions( 
            /* [retval][out] */ IADsCollection __RPC_FAR *__RPC_FAR *ppSessions) = 0;
        
        virtual /* [id] */ HRESULT STDMETHODCALLTYPE Resources( 
            /* [retval][out] */ IADsCollection __RPC_FAR *__RPC_FAR *ppResources) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IADsFileServiceOperationsVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            IADsFileServiceOperations __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            IADsFileServiceOperations __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            IADsFileServiceOperations __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfoCount )( 
            IADsFileServiceOperations __RPC_FAR * This,
            /* [out] */ UINT __RPC_FAR *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfo )( 
            IADsFileServiceOperations __RPC_FAR * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo __RPC_FAR *__RPC_FAR *ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetIDsOfNames )( 
            IADsFileServiceOperations __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR __RPC_FAR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID __RPC_FAR *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Invoke )( 
            IADsFileServiceOperations __RPC_FAR * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS __RPC_FAR *pDispParams,
            /* [out] */ VARIANT __RPC_FAR *pVarResult,
            /* [out] */ EXCEPINFO __RPC_FAR *pExcepInfo,
            /* [out] */ UINT __RPC_FAR *puArgErr);
        
        /* [id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Name )( 
            IADsFileServiceOperations __RPC_FAR * This,
            /* [retval][out] */ BSTR __RPC_FAR *retval);
        
        /* [id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Class )( 
            IADsFileServiceOperations __RPC_FAR * This,
            /* [retval][out] */ BSTR __RPC_FAR *retval);
        
        /* [id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_GUID )( 
            IADsFileServiceOperations __RPC_FAR * This,
            /* [retval][out] */ BSTR __RPC_FAR *retval);
        
        /* [id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_ADsPath )( 
            IADsFileServiceOperations __RPC_FAR * This,
            /* [retval][out] */ BSTR __RPC_FAR *retval);
        
        /* [id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Parent )( 
            IADsFileServiceOperations __RPC_FAR * This,
            /* [retval][out] */ BSTR __RPC_FAR *retval);
        
        /* [id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Schema )( 
            IADsFileServiceOperations __RPC_FAR * This,
            /* [retval][out] */ BSTR __RPC_FAR *retval);
        
        /* [id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetInfo )( 
            IADsFileServiceOperations __RPC_FAR * This);
        
        /* [id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *SetInfo )( 
            IADsFileServiceOperations __RPC_FAR * This);
        
        /* [id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Get )( 
            IADsFileServiceOperations __RPC_FAR * This,
            /* [in] */ BSTR bstrName,
            /* [retval][out] */ VARIANT __RPC_FAR *pvProp);
        
        /* [id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Put )( 
            IADsFileServiceOperations __RPC_FAR * This,
            /* [in] */ BSTR bstrName,
            /* [in] */ VARIANT vProp);
        
        /* [id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetEx )( 
            IADsFileServiceOperations __RPC_FAR * This,
            /* [in] */ BSTR bstrName,
            /* [retval][out] */ VARIANT __RPC_FAR *pvProp);
        
        /* [id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *PutEx )( 
            IADsFileServiceOperations __RPC_FAR * This,
            /* [in] */ long lnControlCode,
            /* [in] */ BSTR bstrName,
            /* [in] */ VARIANT vProp);
        
        /* [id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetInfoEx )( 
            IADsFileServiceOperations __RPC_FAR * This,
            /* [in] */ VARIANT vProperties,
            /* [in] */ long lnReserved);
        
        /* [id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Status )( 
            IADsFileServiceOperations __RPC_FAR * This,
            /* [retval][out] */ long __RPC_FAR *retval);
        
        /* [id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Start )( 
            IADsFileServiceOperations __RPC_FAR * This);
        
        /* [id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Stop )( 
            IADsFileServiceOperations __RPC_FAR * This);
        
        /* [id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Pause )( 
            IADsFileServiceOperations __RPC_FAR * This);
        
        /* [id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Continue )( 
            IADsFileServiceOperations __RPC_FAR * This);
        
        /* [id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *SetPassword )( 
            IADsFileServiceOperations __RPC_FAR * This,
            /* [in] */ BSTR bstrNewPassword);
        
        /* [id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Sessions )( 
            IADsFileServiceOperations __RPC_FAR * This,
            /* [retval][out] */ IADsCollection __RPC_FAR *__RPC_FAR *ppSessions);
        
        /* [id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Resources )( 
            IADsFileServiceOperations __RPC_FAR * This,
            /* [retval][out] */ IADsCollection __RPC_FAR *__RPC_FAR *ppResources);
        
        END_INTERFACE
    } IADsFileServiceOperationsVtbl;

    interface IADsFileServiceOperations
    {
        CONST_VTBL struct IADsFileServiceOperationsVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IADsFileServiceOperations_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IADsFileServiceOperations_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IADsFileServiceOperations_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IADsFileServiceOperations_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define IADsFileServiceOperations_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define IADsFileServiceOperations_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define IADsFileServiceOperations_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)


#define IADsFileServiceOperations_get_Name(This,retval)	\
    (This)->lpVtbl -> get_Name(This,retval)

#define IADsFileServiceOperations_get_Class(This,retval)	\
    (This)->lpVtbl -> get_Class(This,retval)

#define IADsFileServiceOperations_get_GUID(This,retval)	\
    (This)->lpVtbl -> get_GUID(This,retval)

#define IADsFileServiceOperations_get_ADsPath(This,retval)	\
    (This)->lpVtbl -> get_ADsPath(This,retval)

#define IADsFileServiceOperations_get_Parent(This,retval)	\
    (This)->lpVtbl -> get_Parent(This,retval)

#define IADsFileServiceOperations_get_Schema(This,retval)	\
    (This)->lpVtbl -> get_Schema(This,retval)

#define IADsFileServiceOperations_GetInfo(This)	\
    (This)->lpVtbl -> GetInfo(This)

#define IADsFileServiceOperations_SetInfo(This)	\
    (This)->lpVtbl -> SetInfo(This)

#define IADsFileServiceOperations_Get(This,bstrName,pvProp)	\
    (This)->lpVtbl -> Get(This,bstrName,pvProp)

#define IADsFileServiceOperations_Put(This,bstrName,vProp)	\
    (This)->lpVtbl -> Put(This,bstrName,vProp)

#define IADsFileServiceOperations_GetEx(This,bstrName,pvProp)	\
    (This)->lpVtbl -> GetEx(This,bstrName,pvProp)

#define IADsFileServiceOperations_PutEx(This,lnControlCode,bstrName,vProp)	\
    (This)->lpVtbl -> PutEx(This,lnControlCode,bstrName,vProp)

#define IADsFileServiceOperations_GetInfoEx(This,vProperties,lnReserved)	\
    (This)->lpVtbl -> GetInfoEx(This,vProperties,lnReserved)


#define IADsFileServiceOperations_get_Status(This,retval)	\
    (This)->lpVtbl -> get_Status(This,retval)

#define IADsFileServiceOperations_Start(This)	\
    (This)->lpVtbl -> Start(This)

#define IADsFileServiceOperations_Stop(This)	\
    (This)->lpVtbl -> Stop(This)

#define IADsFileServiceOperations_Pause(This)	\
    (This)->lpVtbl -> Pause(This)

#define IADsFileServiceOperations_Continue(This)	\
    (This)->lpVtbl -> Continue(This)

#define IADsFileServiceOperations_SetPassword(This,bstrNewPassword)	\
    (This)->lpVtbl -> SetPassword(This,bstrNewPassword)


#define IADsFileServiceOperations_Sessions(This,ppSessions)	\
    (This)->lpVtbl -> Sessions(This,ppSessions)

#define IADsFileServiceOperations_Resources(This,ppResources)	\
    (This)->lpVtbl -> Resources(This,ppResources)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [id] */ HRESULT STDMETHODCALLTYPE IADsFileServiceOperations_Sessions_Proxy( 
    IADsFileServiceOperations __RPC_FAR * This,
    /* [retval][out] */ IADsCollection __RPC_FAR *__RPC_FAR *ppSessions);


void __RPC_STUB IADsFileServiceOperations_Sessions_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [id] */ HRESULT STDMETHODCALLTYPE IADsFileServiceOperations_Resources_Proxy( 
    IADsFileServiceOperations __RPC_FAR * This,
    /* [retval][out] */ IADsCollection __RPC_FAR *__RPC_FAR *ppResources);


void __RPC_STUB IADsFileServiceOperations_Resources_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IADsFileServiceOperations_INTERFACE_DEFINED__ */


#ifndef __IADsFileShare_INTERFACE_DEFINED__
#define __IADsFileShare_INTERFACE_DEFINED__

/****************************************
 * Generated header for interface: IADsFileShare
 * at Mon Oct 13 13:47:30 1997
 * using MIDL 3.00.44
 ****************************************/
/* [object][dual][oleautomation][uuid] */ 



EXTERN_C const IID IID_IADsFileShare;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    interface IADsFileShare : public IADs
    {
    public:
        virtual /* [id][propget] */ HRESULT STDMETHODCALLTYPE get_CurrentUserCount( 
            /* [retval][out] */ long __RPC_FAR *retval) = 0;
        
        virtual /* [id][propget] */ HRESULT STDMETHODCALLTYPE get_Description( 
            /* [retval][out] */ BSTR __RPC_FAR *retval) = 0;
        
        virtual /* [id][propput] */ HRESULT STDMETHODCALLTYPE put_Description( 
            /* [in] */ BSTR bstrDescription) = 0;
        
        virtual /* [id][propget] */ HRESULT STDMETHODCALLTYPE get_HostComputer( 
            /* [retval][out] */ BSTR __RPC_FAR *retval) = 0;
        
        virtual /* [id][propput] */ HRESULT STDMETHODCALLTYPE put_HostComputer( 
            /* [in] */ BSTR bstrHostComputer) = 0;
        
        virtual /* [id][propget] */ HRESULT STDMETHODCALLTYPE get_Path( 
            /* [retval][out] */ BSTR __RPC_FAR *retval) = 0;
        
        virtual /* [id][propput] */ HRESULT STDMETHODCALLTYPE put_Path( 
            /* [in] */ BSTR bstrPath) = 0;
        
        virtual /* [id][propget] */ HRESULT STDMETHODCALLTYPE get_MaxUserCount( 
            /* [retval][out] */ long __RPC_FAR *retval) = 0;
        
        virtual /* [id][propput] */ HRESULT STDMETHODCALLTYPE put_MaxUserCount( 
            /* [in] */ long lnMaxUserCount) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IADsFileShareVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            IADsFileShare __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            IADsFileShare __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            IADsFileShare __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfoCount )( 
            IADsFileShare __RPC_FAR * This,
            /* [out] */ UINT __RPC_FAR *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfo )( 
            IADsFileShare __RPC_FAR * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo __RPC_FAR *__RPC_FAR *ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetIDsOfNames )( 
            IADsFileShare __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR __RPC_FAR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID __RPC_FAR *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Invoke )( 
            IADsFileShare __RPC_FAR * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS __RPC_FAR *pDispParams,
            /* [out] */ VARIANT __RPC_FAR *pVarResult,
            /* [out] */ EXCEPINFO __RPC_FAR *pExcepInfo,
            /* [out] */ UINT __RPC_FAR *puArgErr);
        
        /* [id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Name )( 
            IADsFileShare __RPC_FAR * This,
            /* [retval][out] */ BSTR __RPC_FAR *retval);
        
        /* [id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Class )( 
            IADsFileShare __RPC_FAR * This,
            /* [retval][out] */ BSTR __RPC_FAR *retval);
        
        /* [id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_GUID )( 
            IADsFileShare __RPC_FAR * This,
            /* [retval][out] */ BSTR __RPC_FAR *retval);
        
        /* [id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_ADsPath )( 
            IADsFileShare __RPC_FAR * This,
            /* [retval][out] */ BSTR __RPC_FAR *retval);
        
        /* [id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Parent )( 
            IADsFileShare __RPC_FAR * This,
            /* [retval][out] */ BSTR __RPC_FAR *retval);
        
        /* [id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Schema )( 
            IADsFileShare __RPC_FAR * This,
            /* [retval][out] */ BSTR __RPC_FAR *retval);
        
        /* [id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetInfo )( 
            IADsFileShare __RPC_FAR * This);
        
        /* [id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *SetInfo )( 
            IADsFileShare __RPC_FAR * This);
        
        /* [id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Get )( 
            IADsFileShare __RPC_FAR * This,
            /* [in] */ BSTR bstrName,
            /* [retval][out] */ VARIANT __RPC_FAR *pvProp);
        
        /* [id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Put )( 
            IADsFileShare __RPC_FAR * This,
            /* [in] */ BSTR bstrName,
            /* [in] */ VARIANT vProp);
        
        /* [id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetEx )( 
            IADsFileShare __RPC_FAR * This,
            /* [in] */ BSTR bstrName,
            /* [retval][out] */ VARIANT __RPC_FAR *pvProp);
        
        /* [id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *PutEx )( 
            IADsFileShare __RPC_FAR * This,
            /* [in] */ long lnControlCode,
            /* [in] */ BSTR bstrName,
            /* [in] */ VARIANT vProp);
        
        /* [id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetInfoEx )( 
            IADsFileShare __RPC_FAR * This,
            /* [in] */ VARIANT vProperties,
            /* [in] */ long lnReserved);
        
        /* [id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_CurrentUserCount )( 
            IADsFileShare __RPC_FAR * This,
            /* [retval][out] */ long __RPC_FAR *retval);
        
        /* [id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Description )( 
            IADsFileShare __RPC_FAR * This,
            /* [retval][out] */ BSTR __RPC_FAR *retval);
        
        /* [id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_Description )( 
            IADsFileShare __RPC_FAR * This,
            /* [in] */ BSTR bstrDescription);
        
        /* [id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_HostComputer )( 
            IADsFileShare __RPC_FAR * This,
            /* [retval][out] */ BSTR __RPC_FAR *retval);
        
        /* [id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_HostComputer )( 
            IADsFileShare __RPC_FAR * This,
            /* [in] */ BSTR bstrHostComputer);
        
        /* [id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Path )( 
            IADsFileShare __RPC_FAR * This,
            /* [retval][out] */ BSTR __RPC_FAR *retval);
        
        /* [id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_Path )( 
            IADsFileShare __RPC_FAR * This,
            /* [in] */ BSTR bstrPath);
        
        /* [id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_MaxUserCount )( 
            IADsFileShare __RPC_FAR * This,
            /* [retval][out] */ long __RPC_FAR *retval);
        
        /* [id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_MaxUserCount )( 
            IADsFileShare __RPC_FAR * This,
            /* [in] */ long lnMaxUserCount);
        
        END_INTERFACE
    } IADsFileShareVtbl;

    interface IADsFileShare
    {
        CONST_VTBL struct IADsFileShareVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IADsFileShare_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IADsFileShare_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IADsFileShare_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IADsFileShare_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define IADsFileShare_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define IADsFileShare_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define IADsFileShare_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)


#define IADsFileShare_get_Name(This,retval)	\
    (This)->lpVtbl -> get_Name(This,retval)

#define IADsFileShare_get_Class(This,retval)	\
    (This)->lpVtbl -> get_Class(This,retval)

#define IADsFileShare_get_GUID(This,retval)	\
    (This)->lpVtbl -> get_GUID(This,retval)

#define IADsFileShare_get_ADsPath(This,retval)	\
    (This)->lpVtbl -> get_ADsPath(This,retval)

#define IADsFileShare_get_Parent(This,retval)	\
    (This)->lpVtbl -> get_Parent(This,retval)

#define IADsFileShare_get_Schema(This,retval)	\
    (This)->lpVtbl -> get_Schema(This,retval)

#define IADsFileShare_GetInfo(This)	\
    (This)->lpVtbl -> GetInfo(This)

#define IADsFileShare_SetInfo(This)	\
    (This)->lpVtbl -> SetInfo(This)

#define IADsFileShare_Get(This,bstrName,pvProp)	\
    (This)->lpVtbl -> Get(This,bstrName,pvProp)

#define IADsFileShare_Put(This,bstrName,vProp)	\
    (This)->lpVtbl -> Put(This,bstrName,vProp)

#define IADsFileShare_GetEx(This,bstrName,pvProp)	\
    (This)->lpVtbl -> GetEx(This,bstrName,pvProp)

#define IADsFileShare_PutEx(This,lnControlCode,bstrName,vProp)	\
    (This)->lpVtbl -> PutEx(This,lnControlCode,bstrName,vProp)

#define IADsFileShare_GetInfoEx(This,vProperties,lnReserved)	\
    (This)->lpVtbl -> GetInfoEx(This,vProperties,lnReserved)


#define IADsFileShare_get_CurrentUserCount(This,retval)	\
    (This)->lpVtbl -> get_CurrentUserCount(This,retval)

#define IADsFileShare_get_Description(This,retval)	\
    (This)->lpVtbl -> get_Description(This,retval)

#define IADsFileShare_put_Description(This,bstrDescription)	\
    (This)->lpVtbl -> put_Description(This,bstrDescription)

#define IADsFileShare_get_HostComputer(This,retval)	\
    (This)->lpVtbl -> get_HostComputer(This,retval)

#define IADsFileShare_put_HostComputer(This,bstrHostComputer)	\
    (This)->lpVtbl -> put_HostComputer(This,bstrHostComputer)

#define IADsFileShare_get_Path(This,retval)	\
    (This)->lpVtbl -> get_Path(This,retval)

#define IADsFileShare_put_Path(This,bstrPath)	\
    (This)->lpVtbl -> put_Path(This,bstrPath)

#define IADsFileShare_get_MaxUserCount(This,retval)	\
    (This)->lpVtbl -> get_MaxUserCount(This,retval)

#define IADsFileShare_put_MaxUserCount(This,lnMaxUserCount)	\
    (This)->lpVtbl -> put_MaxUserCount(This,lnMaxUserCount)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [id][propget] */ HRESULT STDMETHODCALLTYPE IADsFileShare_get_CurrentUserCount_Proxy( 
    IADsFileShare __RPC_FAR * This,
    /* [retval][out] */ long __RPC_FAR *retval);


void __RPC_STUB IADsFileShare_get_CurrentUserCount_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [id][propget] */ HRESULT STDMETHODCALLTYPE IADsFileShare_get_Description_Proxy( 
    IADsFileShare __RPC_FAR * This,
    /* [retval][out] */ BSTR __RPC_FAR *retval);


void __RPC_STUB IADsFileShare_get_Description_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [id][propput] */ HRESULT STDMETHODCALLTYPE IADsFileShare_put_Description_Proxy( 
    IADsFileShare __RPC_FAR * This,
    /* [in] */ BSTR bstrDescription);


void __RPC_STUB IADsFileShare_put_Description_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [id][propget] */ HRESULT STDMETHODCALLTYPE IADsFileShare_get_HostComputer_Proxy( 
    IADsFileShare __RPC_FAR * This,
    /* [retval][out] */ BSTR __RPC_FAR *retval);


void __RPC_STUB IADsFileShare_get_HostComputer_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [id][propput] */ HRESULT STDMETHODCALLTYPE IADsFileShare_put_HostComputer_Proxy( 
    IADsFileShare __RPC_FAR * This,
    /* [in] */ BSTR bstrHostComputer);


void __RPC_STUB IADsFileShare_put_HostComputer_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [id][propget] */ HRESULT STDMETHODCALLTYPE IADsFileShare_get_Path_Proxy( 
    IADsFileShare __RPC_FAR * This,
    /* [retval][out] */ BSTR __RPC_FAR *retval);


void __RPC_STUB IADsFileShare_get_Path_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [id][propput] */ HRESULT STDMETHODCALLTYPE IADsFileShare_put_Path_Proxy( 
    IADsFileShare __RPC_FAR * This,
    /* [in] */ BSTR bstrPath);


void __RPC_STUB IADsFileShare_put_Path_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [id][propget] */ HRESULT STDMETHODCALLTYPE IADsFileShare_get_MaxUserCount_Proxy( 
    IADsFileShare __RPC_FAR * This,
    /* [retval][out] */ long __RPC_FAR *retval);


void __RPC_STUB IADsFileShare_get_MaxUserCount_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [id][propput] */ HRESULT STDMETHODCALLTYPE IADsFileShare_put_MaxUserCount_Proxy( 
    IADsFileShare __RPC_FAR * This,
    /* [in] */ long lnMaxUserCount);


void __RPC_STUB IADsFileShare_put_MaxUserCount_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IADsFileShare_INTERFACE_DEFINED__ */


#ifndef __IADsSession_INTERFACE_DEFINED__
#define __IADsSession_INTERFACE_DEFINED__

/****************************************
 * Generated header for interface: IADsSession
 * at Mon Oct 13 13:47:30 1997
 * using MIDL 3.00.44
 ****************************************/
/* [object][dual][oleautomation][uuid] */ 



EXTERN_C const IID IID_IADsSession;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    interface IADsSession : public IADs
    {
    public:
        virtual /* [id][propget] */ HRESULT STDMETHODCALLTYPE get_User( 
            /* [retval][out] */ BSTR __RPC_FAR *retval) = 0;
        
        virtual /* [id][propget] */ HRESULT STDMETHODCALLTYPE get_UserPath( 
            /* [retval][out] */ BSTR __RPC_FAR *retval) = 0;
        
        virtual /* [id][propget] */ HRESULT STDMETHODCALLTYPE get_Computer( 
            /* [retval][out] */ BSTR __RPC_FAR *retval) = 0;
        
        virtual /* [id][propget] */ HRESULT STDMETHODCALLTYPE get_ComputerPath( 
            /* [retval][out] */ BSTR __RPC_FAR *retval) = 0;
        
        virtual /* [id][propget] */ HRESULT STDMETHODCALLTYPE get_ConnectTime( 
            /* [retval][out] */ long __RPC_FAR *retval) = 0;
        
        virtual /* [id][propget] */ HRESULT STDMETHODCALLTYPE get_IdleTime( 
            /* [retval][out] */ long __RPC_FAR *retval) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IADsSessionVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            IADsSession __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            IADsSession __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            IADsSession __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfoCount )( 
            IADsSession __RPC_FAR * This,
            /* [out] */ UINT __RPC_FAR *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfo )( 
            IADsSession __RPC_FAR * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo __RPC_FAR *__RPC_FAR *ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetIDsOfNames )( 
            IADsSession __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR __RPC_FAR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID __RPC_FAR *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Invoke )( 
            IADsSession __RPC_FAR * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS __RPC_FAR *pDispParams,
            /* [out] */ VARIANT __RPC_FAR *pVarResult,
            /* [out] */ EXCEPINFO __RPC_FAR *pExcepInfo,
            /* [out] */ UINT __RPC_FAR *puArgErr);
        
        /* [id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Name )( 
            IADsSession __RPC_FAR * This,
            /* [retval][out] */ BSTR __RPC_FAR *retval);
        
        /* [id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Class )( 
            IADsSession __RPC_FAR * This,
            /* [retval][out] */ BSTR __RPC_FAR *retval);
        
        /* [id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_GUID )( 
            IADsSession __RPC_FAR * This,
            /* [retval][out] */ BSTR __RPC_FAR *retval);
        
        /* [id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_ADsPath )( 
            IADsSession __RPC_FAR * This,
            /* [retval][out] */ BSTR __RPC_FAR *retval);
        
        /* [id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Parent )( 
            IADsSession __RPC_FAR * This,
            /* [retval][out] */ BSTR __RPC_FAR *retval);
        
        /* [id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Schema )( 
            IADsSession __RPC_FAR * This,
            /* [retval][out] */ BSTR __RPC_FAR *retval);
        
        /* [id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetInfo )( 
            IADsSession __RPC_FAR * This);
        
        /* [id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *SetInfo )( 
            IADsSession __RPC_FAR * This);
        
        /* [id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Get )( 
            IADsSession __RPC_FAR * This,
            /* [in] */ BSTR bstrName,
            /* [retval][out] */ VARIANT __RPC_FAR *pvProp);
        
        /* [id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Put )( 
            IADsSession __RPC_FAR * This,
            /* [in] */ BSTR bstrName,
            /* [in] */ VARIANT vProp);
        
        /* [id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetEx )( 
            IADsSession __RPC_FAR * This,
            /* [in] */ BSTR bstrName,
            /* [retval][out] */ VARIANT __RPC_FAR *pvProp);
        
        /* [id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *PutEx )( 
            IADsSession __RPC_FAR * This,
            /* [in] */ long lnControlCode,
            /* [in] */ BSTR bstrName,
            /* [in] */ VARIANT vProp);
        
        /* [id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetInfoEx )( 
            IADsSession __RPC_FAR * This,
            /* [in] */ VARIANT vProperties,
            /* [in] */ long lnReserved);
        
        /* [id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_User )( 
            IADsSession __RPC_FAR * This,
            /* [retval][out] */ BSTR __RPC_FAR *retval);
        
        /* [id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_UserPath )( 
            IADsSession __RPC_FAR * This,
            /* [retval][out] */ BSTR __RPC_FAR *retval);
        
        /* [id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Computer )( 
            IADsSession __RPC_FAR * This,
            /* [retval][out] */ BSTR __RPC_FAR *retval);
        
        /* [id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_ComputerPath )( 
            IADsSession __RPC_FAR * This,
            /* [retval][out] */ BSTR __RPC_FAR *retval);
        
        /* [id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_ConnectTime )( 
            IADsSession __RPC_FAR * This,
            /* [retval][out] */ long __RPC_FAR *retval);
        
        /* [id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_IdleTime )( 
            IADsSession __RPC_FAR * This,
            /* [retval][out] */ long __RPC_FAR *retval);
        
        END_INTERFACE
    } IADsSessionVtbl;

    interface IADsSession
    {
        CONST_VTBL struct IADsSessionVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IADsSession_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IADsSession_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IADsSession_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IADsSession_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define IADsSession_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define IADsSession_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define IADsSession_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)


#define IADsSession_get_Name(This,retval)	\
    (This)->lpVtbl -> get_Name(This,retval)

#define IADsSession_get_Class(This,retval)	\
    (This)->lpVtbl -> get_Class(This,retval)

#define IADsSession_get_GUID(This,retval)	\
    (This)->lpVtbl -> get_GUID(This,retval)

#define IADsSession_get_ADsPath(This,retval)	\
    (This)->lpVtbl -> get_ADsPath(This,retval)

#define IADsSession_get_Parent(This,retval)	\
    (This)->lpVtbl -> get_Parent(This,retval)

#define IADsSession_get_Schema(This,retval)	\
    (This)->lpVtbl -> get_Schema(This,retval)

#define IADsSession_GetInfo(This)	\
    (This)->lpVtbl -> GetInfo(This)

#define IADsSession_SetInfo(This)	\
    (This)->lpVtbl -> SetInfo(This)

#define IADsSession_Get(This,bstrName,pvProp)	\
    (This)->lpVtbl -> Get(This,bstrName,pvProp)

#define IADsSession_Put(This,bstrName,vProp)	\
    (This)->lpVtbl -> Put(This,bstrName,vProp)

#define IADsSession_GetEx(This,bstrName,pvProp)	\
    (This)->lpVtbl -> GetEx(This,bstrName,pvProp)

#define IADsSession_PutEx(This,lnControlCode,bstrName,vProp)	\
    (This)->lpVtbl -> PutEx(This,lnControlCode,bstrName,vProp)

#define IADsSession_GetInfoEx(This,vProperties,lnReserved)	\
    (This)->lpVtbl -> GetInfoEx(This,vProperties,lnReserved)


#define IADsSession_get_User(This,retval)	\
    (This)->lpVtbl -> get_User(This,retval)

#define IADsSession_get_UserPath(This,retval)	\
    (This)->lpVtbl -> get_UserPath(This,retval)

#define IADsSession_get_Computer(This,retval)	\
    (This)->lpVtbl -> get_Computer(This,retval)

#define IADsSession_get_ComputerPath(This,retval)	\
    (This)->lpVtbl -> get_ComputerPath(This,retval)

#define IADsSession_get_ConnectTime(This,retval)	\
    (This)->lpVtbl -> get_ConnectTime(This,retval)

#define IADsSession_get_IdleTime(This,retval)	\
    (This)->lpVtbl -> get_IdleTime(This,retval)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [id][propget] */ HRESULT STDMETHODCALLTYPE IADsSession_get_User_Proxy( 
    IADsSession __RPC_FAR * This,
    /* [retval][out] */ BSTR __RPC_FAR *retval);


void __RPC_STUB IADsSession_get_User_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [id][propget] */ HRESULT STDMETHODCALLTYPE IADsSession_get_UserPath_Proxy( 
    IADsSession __RPC_FAR * This,
    /* [retval][out] */ BSTR __RPC_FAR *retval);


void __RPC_STUB IADsSession_get_UserPath_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [id][propget] */ HRESULT STDMETHODCALLTYPE IADsSession_get_Computer_Proxy( 
    IADsSession __RPC_FAR * This,
    /* [retval][out] */ BSTR __RPC_FAR *retval);


void __RPC_STUB IADsSession_get_Computer_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [id][propget] */ HRESULT STDMETHODCALLTYPE IADsSession_get_ComputerPath_Proxy( 
    IADsSession __RPC_FAR * This,
    /* [retval][out] */ BSTR __RPC_FAR *retval);


void __RPC_STUB IADsSession_get_ComputerPath_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [id][propget] */ HRESULT STDMETHODCALLTYPE IADsSession_get_ConnectTime_Proxy( 
    IADsSession __RPC_FAR * This,
    /* [retval][out] */ long __RPC_FAR *retval);


void __RPC_STUB IADsSession_get_ConnectTime_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [id][propget] */ HRESULT STDMETHODCALLTYPE IADsSession_get_IdleTime_Proxy( 
    IADsSession __RPC_FAR * This,
    /* [retval][out] */ long __RPC_FAR *retval);


void __RPC_STUB IADsSession_get_IdleTime_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IADsSession_INTERFACE_DEFINED__ */


#ifndef __IADsResource_INTERFACE_DEFINED__
#define __IADsResource_INTERFACE_DEFINED__

/****************************************
 * Generated header for interface: IADsResource
 * at Mon Oct 13 13:47:30 1997
 * using MIDL 3.00.44
 ****************************************/
/* [object][dual][oleautomation][uuid] */ 



EXTERN_C const IID IID_IADsResource;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    interface IADsResource : public IADs
    {
    public:
        virtual /* [id][propget] */ HRESULT STDMETHODCALLTYPE get_User( 
            /* [retval][out] */ BSTR __RPC_FAR *retval) = 0;
        
        virtual /* [id][propget] */ HRESULT STDMETHODCALLTYPE get_UserPath( 
            /* [retval][out] */ BSTR __RPC_FAR *retval) = 0;
        
        virtual /* [id][propget] */ HRESULT STDMETHODCALLTYPE get_Path( 
            /* [retval][out] */ BSTR __RPC_FAR *retval) = 0;
        
        virtual /* [id][propget] */ HRESULT STDMETHODCALLTYPE get_LockCount( 
            /* [retval][out] */ long __RPC_FAR *retval) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IADsResourceVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            IADsResource __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            IADsResource __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            IADsResource __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfoCount )( 
            IADsResource __RPC_FAR * This,
            /* [out] */ UINT __RPC_FAR *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfo )( 
            IADsResource __RPC_FAR * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo __RPC_FAR *__RPC_FAR *ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetIDsOfNames )( 
            IADsResource __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR __RPC_FAR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID __RPC_FAR *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Invoke )( 
            IADsResource __RPC_FAR * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS __RPC_FAR *pDispParams,
            /* [out] */ VARIANT __RPC_FAR *pVarResult,
            /* [out] */ EXCEPINFO __RPC_FAR *pExcepInfo,
            /* [out] */ UINT __RPC_FAR *puArgErr);
        
        /* [id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Name )( 
            IADsResource __RPC_FAR * This,
            /* [retval][out] */ BSTR __RPC_FAR *retval);
        
        /* [id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Class )( 
            IADsResource __RPC_FAR * This,
            /* [retval][out] */ BSTR __RPC_FAR *retval);
        
        /* [id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_GUID )( 
            IADsResource __RPC_FAR * This,
            /* [retval][out] */ BSTR __RPC_FAR *retval);
        
        /* [id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_ADsPath )( 
            IADsResource __RPC_FAR * This,
            /* [retval][out] */ BSTR __RPC_FAR *retval);
        
        /* [id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Parent )( 
            IADsResource __RPC_FAR * This,
            /* [retval][out] */ BSTR __RPC_FAR *retval);
        
        /* [id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Schema )( 
            IADsResource __RPC_FAR * This,
            /* [retval][out] */ BSTR __RPC_FAR *retval);
        
        /* [id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetInfo )( 
            IADsResource __RPC_FAR * This);
        
        /* [id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *SetInfo )( 
            IADsResource __RPC_FAR * This);
        
        /* [id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Get )( 
            IADsResource __RPC_FAR * This,
            /* [in] */ BSTR bstrName,
            /* [retval][out] */ VARIANT __RPC_FAR *pvProp);
        
        /* [id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Put )( 
            IADsResource __RPC_FAR * This,
            /* [in] */ BSTR bstrName,
            /* [in] */ VARIANT vProp);
        
        /* [id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetEx )( 
            IADsResource __RPC_FAR * This,
            /* [in] */ BSTR bstrName,
            /* [retval][out] */ VARIANT __RPC_FAR *pvProp);
        
        /* [id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *PutEx )( 
            IADsResource __RPC_FAR * This,
            /* [in] */ long lnControlCode,
            /* [in] */ BSTR bstrName,
            /* [in] */ VARIANT vProp);
        
        /* [id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetInfoEx )( 
            IADsResource __RPC_FAR * This,
            /* [in] */ VARIANT vProperties,
            /* [in] */ long lnReserved);
        
        /* [id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_User )( 
            IADsResource __RPC_FAR * This,
            /* [retval][out] */ BSTR __RPC_FAR *retval);
        
        /* [id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_UserPath )( 
            IADsResource __RPC_FAR * This,
            /* [retval][out] */ BSTR __RPC_FAR *retval);
        
        /* [id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Path )( 
            IADsResource __RPC_FAR * This,
            /* [retval][out] */ BSTR __RPC_FAR *retval);
        
        /* [id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_LockCount )( 
            IADsResource __RPC_FAR * This,
            /* [retval][out] */ long __RPC_FAR *retval);
        
        END_INTERFACE
    } IADsResourceVtbl;

    interface IADsResource
    {
        CONST_VTBL struct IADsResourceVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IADsResource_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IADsResource_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IADsResource_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IADsResource_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define IADsResource_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define IADsResource_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define IADsResource_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)


#define IADsResource_get_Name(This,retval)	\
    (This)->lpVtbl -> get_Name(This,retval)

#define IADsResource_get_Class(This,retval)	\
    (This)->lpVtbl -> get_Class(This,retval)

#define IADsResource_get_GUID(This,retval)	\
    (This)->lpVtbl -> get_GUID(This,retval)

#define IADsResource_get_ADsPath(This,retval)	\
    (This)->lpVtbl -> get_ADsPath(This,retval)

#define IADsResource_get_Parent(This,retval)	\
    (This)->lpVtbl -> get_Parent(This,retval)

#define IADsResource_get_Schema(This,retval)	\
    (This)->lpVtbl -> get_Schema(This,retval)

#define IADsResource_GetInfo(This)	\
    (This)->lpVtbl -> GetInfo(This)

#define IADsResource_SetInfo(This)	\
    (This)->lpVtbl -> SetInfo(This)

#define IADsResource_Get(This,bstrName,pvProp)	\
    (This)->lpVtbl -> Get(This,bstrName,pvProp)

#define IADsResource_Put(This,bstrName,vProp)	\
    (This)->lpVtbl -> Put(This,bstrName,vProp)

#define IADsResource_GetEx(This,bstrName,pvProp)	\
    (This)->lpVtbl -> GetEx(This,bstrName,pvProp)

#define IADsResource_PutEx(This,lnControlCode,bstrName,vProp)	\
    (This)->lpVtbl -> PutEx(This,lnControlCode,bstrName,vProp)

#define IADsResource_GetInfoEx(This,vProperties,lnReserved)	\
    (This)->lpVtbl -> GetInfoEx(This,vProperties,lnReserved)


#define IADsResource_get_User(This,retval)	\
    (This)->lpVtbl -> get_User(This,retval)

#define IADsResource_get_UserPath(This,retval)	\
    (This)->lpVtbl -> get_UserPath(This,retval)

#define IADsResource_get_Path(This,retval)	\
    (This)->lpVtbl -> get_Path(This,retval)

#define IADsResource_get_LockCount(This,retval)	\
    (This)->lpVtbl -> get_LockCount(This,retval)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [id][propget] */ HRESULT STDMETHODCALLTYPE IADsResource_get_User_Proxy( 
    IADsResource __RPC_FAR * This,
    /* [retval][out] */ BSTR __RPC_FAR *retval);


void __RPC_STUB IADsResource_get_User_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [id][propget] */ HRESULT STDMETHODCALLTYPE IADsResource_get_UserPath_Proxy( 
    IADsResource __RPC_FAR * This,
    /* [retval][out] */ BSTR __RPC_FAR *retval);


void __RPC_STUB IADsResource_get_UserPath_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [id][propget] */ HRESULT STDMETHODCALLTYPE IADsResource_get_Path_Proxy( 
    IADsResource __RPC_FAR * This,
    /* [retval][out] */ BSTR __RPC_FAR *retval);


void __RPC_STUB IADsResource_get_Path_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [id][propget] */ HRESULT STDMETHODCALLTYPE IADsResource_get_LockCount_Proxy( 
    IADsResource __RPC_FAR * This,
    /* [retval][out] */ long __RPC_FAR *retval);


void __RPC_STUB IADsResource_get_LockCount_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IADsResource_INTERFACE_DEFINED__ */


#ifndef __IADsOpenDSObject_INTERFACE_DEFINED__
#define __IADsOpenDSObject_INTERFACE_DEFINED__

/****************************************
 * Generated header for interface: IADsOpenDSObject
 * at Mon Oct 13 13:47:30 1997
 * using MIDL 3.00.44
 ****************************************/
/* [object][dual][oleautomation][uuid] */ 



EXTERN_C const IID IID_IADsOpenDSObject;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    interface IADsOpenDSObject : public IDispatch
    {
    public:
        virtual /* [id] */ HRESULT STDMETHODCALLTYPE OpenDSObject( 
            /* [in] */ BSTR lpszDNName,
            /* [in] */ BSTR lpszUserName,
            /* [in] */ BSTR lpszPassword,
            /* [in] */ long lnReserved,
            /* [retval][out] */ IDispatch __RPC_FAR *__RPC_FAR *ppOleDsObj) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IADsOpenDSObjectVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            IADsOpenDSObject __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            IADsOpenDSObject __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            IADsOpenDSObject __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfoCount )( 
            IADsOpenDSObject __RPC_FAR * This,
            /* [out] */ UINT __RPC_FAR *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfo )( 
            IADsOpenDSObject __RPC_FAR * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo __RPC_FAR *__RPC_FAR *ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetIDsOfNames )( 
            IADsOpenDSObject __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR __RPC_FAR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID __RPC_FAR *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Invoke )( 
            IADsOpenDSObject __RPC_FAR * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS __RPC_FAR *pDispParams,
            /* [out] */ VARIANT __RPC_FAR *pVarResult,
            /* [out] */ EXCEPINFO __RPC_FAR *pExcepInfo,
            /* [out] */ UINT __RPC_FAR *puArgErr);
        
        /* [id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *OpenDSObject )( 
            IADsOpenDSObject __RPC_FAR * This,
            /* [in] */ BSTR lpszDNName,
            /* [in] */ BSTR lpszUserName,
            /* [in] */ BSTR lpszPassword,
            /* [in] */ long lnReserved,
            /* [retval][out] */ IDispatch __RPC_FAR *__RPC_FAR *ppOleDsObj);
        
        END_INTERFACE
    } IADsOpenDSObjectVtbl;

    interface IADsOpenDSObject
    {
        CONST_VTBL struct IADsOpenDSObjectVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IADsOpenDSObject_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IADsOpenDSObject_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IADsOpenDSObject_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IADsOpenDSObject_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define IADsOpenDSObject_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define IADsOpenDSObject_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define IADsOpenDSObject_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)


#define IADsOpenDSObject_OpenDSObject(This,lpszDNName,lpszUserName,lpszPassword,lnReserved,ppOleDsObj)	\
    (This)->lpVtbl -> OpenDSObject(This,lpszDNName,lpszUserName,lpszPassword,lnReserved,ppOleDsObj)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [id] */ HRESULT STDMETHODCALLTYPE IADsOpenDSObject_OpenDSObject_Proxy( 
    IADsOpenDSObject __RPC_FAR * This,
    /* [in] */ BSTR lpszDNName,
    /* [in] */ BSTR lpszUserName,
    /* [in] */ BSTR lpszPassword,
    /* [in] */ long lnReserved,
    /* [retval][out] */ IDispatch __RPC_FAR *__RPC_FAR *ppOleDsObj);


void __RPC_STUB IADsOpenDSObject_OpenDSObject_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IADsOpenDSObject_INTERFACE_DEFINED__ */


#ifndef __IDirectoryObject_INTERFACE_DEFINED__
#define __IDirectoryObject_INTERFACE_DEFINED__

/****************************************
 * Generated header for interface: IDirectoryObject
 * at Mon Oct 13 13:47:30 1997
 * using MIDL 3.00.44
 ****************************************/
/* [object][uuid] */ 



EXTERN_C const IID IID_IDirectoryObject;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    interface IDirectoryObject : public IUnknown
    {
    public:
        virtual HRESULT STDMETHODCALLTYPE GetObjectInformation( 
            /* [out] */ PADS_OBJECT_INFO __RPC_FAR *ppObjInfo) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE GetObjectAttributes( 
            /* [in] */ LPWSTR __RPC_FAR *pAttributeNames,
            /* [in] */ DWORD dwNumberAttributes,
            /* [out] */ PADS_ATTR_INFO __RPC_FAR *ppAttributeEntries,
            /* [out] */ DWORD __RPC_FAR *pdwNumAttributesReturned) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE SetObjectAttributes( 
            /* [in] */ PADS_ATTR_INFO pAttributeEntries,
            /* [in] */ DWORD dwNumAttributes,
            /* [out] */ DWORD __RPC_FAR *pdwNumAttributesModified) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE CreateDSObject( 
            /* [in] */ LPWSTR pszRDNName,
            /* [in] */ PADS_ATTR_INFO pAttributeEntries,
            /* [in] */ DWORD dwNumAttributes,
            /* [out] */ IDispatch __RPC_FAR *__RPC_FAR *ppObject) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE DeleteDSObject( 
            /* [in] */ LPWSTR pszRDNName) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IDirectoryObjectVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            IDirectoryObject __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            IDirectoryObject __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            IDirectoryObject __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetObjectInformation )( 
            IDirectoryObject __RPC_FAR * This,
            /* [out] */ PADS_OBJECT_INFO __RPC_FAR *ppObjInfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetObjectAttributes )( 
            IDirectoryObject __RPC_FAR * This,
            /* [in] */ LPWSTR __RPC_FAR *pAttributeNames,
            /* [in] */ DWORD dwNumberAttributes,
            /* [out] */ PADS_ATTR_INFO __RPC_FAR *ppAttributeEntries,
            /* [out] */ DWORD __RPC_FAR *pdwNumAttributesReturned);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *SetObjectAttributes )( 
            IDirectoryObject __RPC_FAR * This,
            /* [in] */ PADS_ATTR_INFO pAttributeEntries,
            /* [in] */ DWORD dwNumAttributes,
            /* [out] */ DWORD __RPC_FAR *pdwNumAttributesModified);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *CreateDSObject )( 
            IDirectoryObject __RPC_FAR * This,
            /* [in] */ LPWSTR pszRDNName,
            /* [in] */ PADS_ATTR_INFO pAttributeEntries,
            /* [in] */ DWORD dwNumAttributes,
            /* [out] */ IDispatch __RPC_FAR *__RPC_FAR *ppObject);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *DeleteDSObject )( 
            IDirectoryObject __RPC_FAR * This,
            /* [in] */ LPWSTR pszRDNName);
        
        END_INTERFACE
    } IDirectoryObjectVtbl;

    interface IDirectoryObject
    {
        CONST_VTBL struct IDirectoryObjectVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IDirectoryObject_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IDirectoryObject_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IDirectoryObject_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IDirectoryObject_GetObjectInformation(This,ppObjInfo)	\
    (This)->lpVtbl -> GetObjectInformation(This,ppObjInfo)

#define IDirectoryObject_GetObjectAttributes(This,pAttributeNames,dwNumberAttributes,ppAttributeEntries,pdwNumAttributesReturned)	\
    (This)->lpVtbl -> GetObjectAttributes(This,pAttributeNames,dwNumberAttributes,ppAttributeEntries,pdwNumAttributesReturned)

#define IDirectoryObject_SetObjectAttributes(This,pAttributeEntries,dwNumAttributes,pdwNumAttributesModified)	\
    (This)->lpVtbl -> SetObjectAttributes(This,pAttributeEntries,dwNumAttributes,pdwNumAttributesModified)

#define IDirectoryObject_CreateDSObject(This,pszRDNName,pAttributeEntries,dwNumAttributes,ppObject)	\
    (This)->lpVtbl -> CreateDSObject(This,pszRDNName,pAttributeEntries,dwNumAttributes,ppObject)

#define IDirectoryObject_DeleteDSObject(This,pszRDNName)	\
    (This)->lpVtbl -> DeleteDSObject(This,pszRDNName)

#endif /* COBJMACROS */


#endif 	/* C style interface */



HRESULT STDMETHODCALLTYPE IDirectoryObject_GetObjectInformation_Proxy( 
    IDirectoryObject __RPC_FAR * This,
    /* [out] */ PADS_OBJECT_INFO __RPC_FAR *ppObjInfo);


void __RPC_STUB IDirectoryObject_GetObjectInformation_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IDirectoryObject_GetObjectAttributes_Proxy( 
    IDirectoryObject __RPC_FAR * This,
    /* [in] */ LPWSTR __RPC_FAR *pAttributeNames,
    /* [in] */ DWORD dwNumberAttributes,
    /* [out] */ PADS_ATTR_INFO __RPC_FAR *ppAttributeEntries,
    /* [out] */ DWORD __RPC_FAR *pdwNumAttributesReturned);


void __RPC_STUB IDirectoryObject_GetObjectAttributes_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IDirectoryObject_SetObjectAttributes_Proxy( 
    IDirectoryObject __RPC_FAR * This,
    /* [in] */ PADS_ATTR_INFO pAttributeEntries,
    /* [in] */ DWORD dwNumAttributes,
    /* [out] */ DWORD __RPC_FAR *pdwNumAttributesModified);


void __RPC_STUB IDirectoryObject_SetObjectAttributes_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IDirectoryObject_CreateDSObject_Proxy( 
    IDirectoryObject __RPC_FAR * This,
    /* [in] */ LPWSTR pszRDNName,
    /* [in] */ PADS_ATTR_INFO pAttributeEntries,
    /* [in] */ DWORD dwNumAttributes,
    /* [out] */ IDispatch __RPC_FAR *__RPC_FAR *ppObject);


void __RPC_STUB IDirectoryObject_CreateDSObject_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IDirectoryObject_DeleteDSObject_Proxy( 
    IDirectoryObject __RPC_FAR * This,
    /* [in] */ LPWSTR pszRDNName);


void __RPC_STUB IDirectoryObject_DeleteDSObject_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IDirectoryObject_INTERFACE_DEFINED__ */


#ifndef __IDSObject_INTERFACE_DEFINED__
#define __IDSObject_INTERFACE_DEFINED__

/****************************************
 * Generated header for interface: IDSObject
 * at Mon Oct 13 13:47:30 1997
 * using MIDL 3.00.44
 ****************************************/
/* [object][uuid] */ 



EXTERN_C const IID IID_IDSObject;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    interface IDSObject : public IUnknown
    {
    public:
        virtual HRESULT STDMETHODCALLTYPE GetObjectInformation( 
            /* [out] */ PADS_OBJECT_INFO __RPC_FAR *ppObjInfo) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE GetObjectAttributes( 
            /* [in] */ LPWSTR __RPC_FAR *pAttributeNames,
            /* [in] */ DWORD dwNumberAttributes,
            /* [out] */ PADS_ATTR_INFO __RPC_FAR *ppAttributeEntries,
            /* [out] */ DWORD __RPC_FAR *pdwNumAttributesReturned) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE SetObjectAttributes( 
            /* [in] */ PADS_ATTR_INFO pAttributeEntries,
            /* [in] */ DWORD dwNumAttributes,
            /* [out] */ DWORD __RPC_FAR *pdwNumAttributesModified) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE CreateDSObject( 
            /* [in] */ LPWSTR pszRDNName,
            /* [in] */ PADS_ATTR_INFO pAttributeEntries,
            /* [in] */ DWORD dwNumAttributes,
            /* [out] */ IDispatch __RPC_FAR *__RPC_FAR *ppObject) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE DeleteDSObject( 
            /* [in] */ LPWSTR pszRDNName) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IDSObjectVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            IDSObject __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            IDSObject __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            IDSObject __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetObjectInformation )( 
            IDSObject __RPC_FAR * This,
            /* [out] */ PADS_OBJECT_INFO __RPC_FAR *ppObjInfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetObjectAttributes )( 
            IDSObject __RPC_FAR * This,
            /* [in] */ LPWSTR __RPC_FAR *pAttributeNames,
            /* [in] */ DWORD dwNumberAttributes,
            /* [out] */ PADS_ATTR_INFO __RPC_FAR *ppAttributeEntries,
            /* [out] */ DWORD __RPC_FAR *pdwNumAttributesReturned);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *SetObjectAttributes )( 
            IDSObject __RPC_FAR * This,
            /* [in] */ PADS_ATTR_INFO pAttributeEntries,
            /* [in] */ DWORD dwNumAttributes,
            /* [out] */ DWORD __RPC_FAR *pdwNumAttributesModified);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *CreateDSObject )( 
            IDSObject __RPC_FAR * This,
            /* [in] */ LPWSTR pszRDNName,
            /* [in] */ PADS_ATTR_INFO pAttributeEntries,
            /* [in] */ DWORD dwNumAttributes,
            /* [out] */ IDispatch __RPC_FAR *__RPC_FAR *ppObject);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *DeleteDSObject )( 
            IDSObject __RPC_FAR * This,
            /* [in] */ LPWSTR pszRDNName);
        
        END_INTERFACE
    } IDSObjectVtbl;

    interface IDSObject
    {
        CONST_VTBL struct IDSObjectVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IDSObject_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IDSObject_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IDSObject_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IDSObject_GetObjectInformation(This,ppObjInfo)	\
    (This)->lpVtbl -> GetObjectInformation(This,ppObjInfo)

#define IDSObject_GetObjectAttributes(This,pAttributeNames,dwNumberAttributes,ppAttributeEntries,pdwNumAttributesReturned)	\
    (This)->lpVtbl -> GetObjectAttributes(This,pAttributeNames,dwNumberAttributes,ppAttributeEntries,pdwNumAttributesReturned)

#define IDSObject_SetObjectAttributes(This,pAttributeEntries,dwNumAttributes,pdwNumAttributesModified)	\
    (This)->lpVtbl -> SetObjectAttributes(This,pAttributeEntries,dwNumAttributes,pdwNumAttributesModified)

#define IDSObject_CreateDSObject(This,pszRDNName,pAttributeEntries,dwNumAttributes,ppObject)	\
    (This)->lpVtbl -> CreateDSObject(This,pszRDNName,pAttributeEntries,dwNumAttributes,ppObject)

#define IDSObject_DeleteDSObject(This,pszRDNName)	\
    (This)->lpVtbl -> DeleteDSObject(This,pszRDNName)

#endif /* COBJMACROS */


#endif 	/* C style interface */



HRESULT STDMETHODCALLTYPE IDSObject_GetObjectInformation_Proxy( 
    IDSObject __RPC_FAR * This,
    /* [out] */ PADS_OBJECT_INFO __RPC_FAR *ppObjInfo);


void __RPC_STUB IDSObject_GetObjectInformation_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IDSObject_GetObjectAttributes_Proxy( 
    IDSObject __RPC_FAR * This,
    /* [in] */ LPWSTR __RPC_FAR *pAttributeNames,
    /* [in] */ DWORD dwNumberAttributes,
    /* [out] */ PADS_ATTR_INFO __RPC_FAR *ppAttributeEntries,
    /* [out] */ DWORD __RPC_FAR *pdwNumAttributesReturned);


void __RPC_STUB IDSObject_GetObjectAttributes_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IDSObject_SetObjectAttributes_Proxy( 
    IDSObject __RPC_FAR * This,
    /* [in] */ PADS_ATTR_INFO pAttributeEntries,
    /* [in] */ DWORD dwNumAttributes,
    /* [out] */ DWORD __RPC_FAR *pdwNumAttributesModified);


void __RPC_STUB IDSObject_SetObjectAttributes_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IDSObject_CreateDSObject_Proxy( 
    IDSObject __RPC_FAR * This,
    /* [in] */ LPWSTR pszRDNName,
    /* [in] */ PADS_ATTR_INFO pAttributeEntries,
    /* [in] */ DWORD dwNumAttributes,
    /* [out] */ IDispatch __RPC_FAR *__RPC_FAR *ppObject);


void __RPC_STUB IDSObject_CreateDSObject_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IDSObject_DeleteDSObject_Proxy( 
    IDSObject __RPC_FAR * This,
    /* [in] */ LPWSTR pszRDNName);


void __RPC_STUB IDSObject_DeleteDSObject_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IDSObject_INTERFACE_DEFINED__ */


#ifndef __IDirectorySearch_INTERFACE_DEFINED__
#define __IDirectorySearch_INTERFACE_DEFINED__

/****************************************
 * Generated header for interface: IDirectorySearch
 * at Mon Oct 13 13:47:30 1997
 * using MIDL 3.00.44
 ****************************************/
/* [object][uuid] */ 



EXTERN_C const IID IID_IDirectorySearch;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    interface IDirectorySearch : public IUnknown
    {
    public:
        virtual HRESULT STDMETHODCALLTYPE SetSearchPreference( 
            /* [in] */ PADS_SEARCHPREF_INFO pSearchPrefs,
            /* [in] */ DWORD dwNumPrefs) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE ExecuteSearch( 
            /* [in] */ LPWSTR pszSearchFilter,
            /* [in] */ LPWSTR __RPC_FAR *pAttributeNames,
            /* [in] */ DWORD dwNumberAttributes,
            /* [out] */ PADS_SEARCH_HANDLE phSearchResult) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE AbandonSearch( 
            /* [in] */ ADS_SEARCH_HANDLE phSearchResult) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE GetFirstRow( 
            /* [in] */ ADS_SEARCH_HANDLE hSearchResult) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE GetNextRow( 
            /* [in] */ ADS_SEARCH_HANDLE hSearchResult) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE GetPreviousRow( 
            /* [in] */ ADS_SEARCH_HANDLE hSearchResult) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE GetNextColumnName( 
            /* [in] */ ADS_SEARCH_HANDLE hSearchHandle,
            /* [out] */ LPWSTR __RPC_FAR *ppszColumnName) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE GetColumn( 
            /* [in] */ ADS_SEARCH_HANDLE hSearchResult,
            /* [in] */ LPWSTR szColumnName,
            /* [out] */ PADS_SEARCH_COLUMN pSearchColumn) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE FreeColumn( 
            /* [in] */ PADS_SEARCH_COLUMN pSearchColumn) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE CloseSearchHandle( 
            /* [in] */ ADS_SEARCH_HANDLE hSearchResult) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IDirectorySearchVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            IDirectorySearch __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            IDirectorySearch __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            IDirectorySearch __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *SetSearchPreference )( 
            IDirectorySearch __RPC_FAR * This,
            /* [in] */ PADS_SEARCHPREF_INFO pSearchPrefs,
            /* [in] */ DWORD dwNumPrefs);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *ExecuteSearch )( 
            IDirectorySearch __RPC_FAR * This,
            /* [in] */ LPWSTR pszSearchFilter,
            /* [in] */ LPWSTR __RPC_FAR *pAttributeNames,
            /* [in] */ DWORD dwNumberAttributes,
            /* [out] */ PADS_SEARCH_HANDLE phSearchResult);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *AbandonSearch )( 
            IDirectorySearch __RPC_FAR * This,
            /* [in] */ ADS_SEARCH_HANDLE phSearchResult);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetFirstRow )( 
            IDirectorySearch __RPC_FAR * This,
            /* [in] */ ADS_SEARCH_HANDLE hSearchResult);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetNextRow )( 
            IDirectorySearch __RPC_FAR * This,
            /* [in] */ ADS_SEARCH_HANDLE hSearchResult);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetPreviousRow )( 
            IDirectorySearch __RPC_FAR * This,
            /* [in] */ ADS_SEARCH_HANDLE hSearchResult);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetNextColumnName )( 
            IDirectorySearch __RPC_FAR * This,
            /* [in] */ ADS_SEARCH_HANDLE hSearchHandle,
            /* [out] */ LPWSTR __RPC_FAR *ppszColumnName);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetColumn )( 
            IDirectorySearch __RPC_FAR * This,
            /* [in] */ ADS_SEARCH_HANDLE hSearchResult,
            /* [in] */ LPWSTR szColumnName,
            /* [out] */ PADS_SEARCH_COLUMN pSearchColumn);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *FreeColumn )( 
            IDirectorySearch __RPC_FAR * This,
            /* [in] */ PADS_SEARCH_COLUMN pSearchColumn);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *CloseSearchHandle )( 
            IDirectorySearch __RPC_FAR * This,
            /* [in] */ ADS_SEARCH_HANDLE hSearchResult);
        
        END_INTERFACE
    } IDirectorySearchVtbl;

    interface IDirectorySearch
    {
        CONST_VTBL struct IDirectorySearchVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IDirectorySearch_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IDirectorySearch_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IDirectorySearch_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IDirectorySearch_SetSearchPreference(This,pSearchPrefs,dwNumPrefs)	\
    (This)->lpVtbl -> SetSearchPreference(This,pSearchPrefs,dwNumPrefs)

#define IDirectorySearch_ExecuteSearch(This,pszSearchFilter,pAttributeNames,dwNumberAttributes,phSearchResult)	\
    (This)->lpVtbl -> ExecuteSearch(This,pszSearchFilter,pAttributeNames,dwNumberAttributes,phSearchResult)

#define IDirectorySearch_AbandonSearch(This,phSearchResult)	\
    (This)->lpVtbl -> AbandonSearch(This,phSearchResult)

#define IDirectorySearch_GetFirstRow(This,hSearchResult)	\
    (This)->lpVtbl -> GetFirstRow(This,hSearchResult)

#define IDirectorySearch_GetNextRow(This,hSearchResult)	\
    (This)->lpVtbl -> GetNextRow(This,hSearchResult)

#define IDirectorySearch_GetPreviousRow(This,hSearchResult)	\
    (This)->lpVtbl -> GetPreviousRow(This,hSearchResult)

#define IDirectorySearch_GetNextColumnName(This,hSearchHandle,ppszColumnName)	\
    (This)->lpVtbl -> GetNextColumnName(This,hSearchHandle,ppszColumnName)

#define IDirectorySearch_GetColumn(This,hSearchResult,szColumnName,pSearchColumn)	\
    (This)->lpVtbl -> GetColumn(This,hSearchResult,szColumnName,pSearchColumn)

#define IDirectorySearch_FreeColumn(This,pSearchColumn)	\
    (This)->lpVtbl -> FreeColumn(This,pSearchColumn)

#define IDirectorySearch_CloseSearchHandle(This,hSearchResult)	\
    (This)->lpVtbl -> CloseSearchHandle(This,hSearchResult)

#endif /* COBJMACROS */


#endif 	/* C style interface */



HRESULT STDMETHODCALLTYPE IDirectorySearch_SetSearchPreference_Proxy( 
    IDirectorySearch __RPC_FAR * This,
    /* [in] */ PADS_SEARCHPREF_INFO pSearchPrefs,
    /* [in] */ DWORD dwNumPrefs);


void __RPC_STUB IDirectorySearch_SetSearchPreference_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IDirectorySearch_ExecuteSearch_Proxy( 
    IDirectorySearch __RPC_FAR * This,
    /* [in] */ LPWSTR pszSearchFilter,
    /* [in] */ LPWSTR __RPC_FAR *pAttributeNames,
    /* [in] */ DWORD dwNumberAttributes,
    /* [out] */ PADS_SEARCH_HANDLE phSearchResult);


void __RPC_STUB IDirectorySearch_ExecuteSearch_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IDirectorySearch_AbandonSearch_Proxy( 
    IDirectorySearch __RPC_FAR * This,
    /* [in] */ ADS_SEARCH_HANDLE phSearchResult);


void __RPC_STUB IDirectorySearch_AbandonSearch_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IDirectorySearch_GetFirstRow_Proxy( 
    IDirectorySearch __RPC_FAR * This,
    /* [in] */ ADS_SEARCH_HANDLE hSearchResult);


void __RPC_STUB IDirectorySearch_GetFirstRow_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IDirectorySearch_GetNextRow_Proxy( 
    IDirectorySearch __RPC_FAR * This,
    /* [in] */ ADS_SEARCH_HANDLE hSearchResult);


void __RPC_STUB IDirectorySearch_GetNextRow_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IDirectorySearch_GetPreviousRow_Proxy( 
    IDirectorySearch __RPC_FAR * This,
    /* [in] */ ADS_SEARCH_HANDLE hSearchResult);


void __RPC_STUB IDirectorySearch_GetPreviousRow_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IDirectorySearch_GetNextColumnName_Proxy( 
    IDirectorySearch __RPC_FAR * This,
    /* [in] */ ADS_SEARCH_HANDLE hSearchHandle,
    /* [out] */ LPWSTR __RPC_FAR *ppszColumnName);


void __RPC_STUB IDirectorySearch_GetNextColumnName_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IDirectorySearch_GetColumn_Proxy( 
    IDirectorySearch __RPC_FAR * This,
    /* [in] */ ADS_SEARCH_HANDLE hSearchResult,
    /* [in] */ LPWSTR szColumnName,
    /* [out] */ PADS_SEARCH_COLUMN pSearchColumn);


void __RPC_STUB IDirectorySearch_GetColumn_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IDirectorySearch_FreeColumn_Proxy( 
    IDirectorySearch __RPC_FAR * This,
    /* [in] */ PADS_SEARCH_COLUMN pSearchColumn);


void __RPC_STUB IDirectorySearch_FreeColumn_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IDirectorySearch_CloseSearchHandle_Proxy( 
    IDirectorySearch __RPC_FAR * This,
    /* [in] */ ADS_SEARCH_HANDLE hSearchResult);


void __RPC_STUB IDirectorySearch_CloseSearchHandle_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IDirectorySearch_INTERFACE_DEFINED__ */


#ifndef __IDSSearch_INTERFACE_DEFINED__
#define __IDSSearch_INTERFACE_DEFINED__

/****************************************
 * Generated header for interface: IDSSearch
 * at Mon Oct 13 13:47:30 1997
 * using MIDL 3.00.44
 ****************************************/
/* [object][uuid] */ 



EXTERN_C const IID IID_IDSSearch;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    interface IDSSearch : public IUnknown
    {
    public:
        virtual HRESULT STDMETHODCALLTYPE SetSearchPreference( 
            /* [in] */ PADS_SEARCHPREF_INFO pSearchPrefs,
            /* [in] */ DWORD dwNumPrefs) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE ExecuteSearch( 
            /* [in] */ LPWSTR pszSearchFilter,
            /* [in] */ LPWSTR __RPC_FAR *pAttributeNames,
            /* [in] */ DWORD dwNumberAttributes,
            /* [out] */ PADS_SEARCH_HANDLE phSearchResult) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE AbandonSearch( 
            /* [in] */ ADS_SEARCH_HANDLE phSearchResult) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE GetFirstRow( 
            /* [in] */ ADS_SEARCH_HANDLE hSearchResult) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE GetNextRow( 
            /* [in] */ ADS_SEARCH_HANDLE hSearchResult) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE GetPreviousRow( 
            /* [in] */ ADS_SEARCH_HANDLE hSearchResult) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE GetNextColumnName( 
            /* [in] */ ADS_SEARCH_HANDLE hSearchHandle,
            /* [out] */ LPWSTR __RPC_FAR *ppszColumnName) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE GetColumn( 
            /* [in] */ ADS_SEARCH_HANDLE hSearchResult,
            /* [in] */ LPWSTR szColumnName,
            /* [out] */ PADS_SEARCH_COLUMN pSearchColumn) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE FreeColumn( 
            /* [in] */ PADS_SEARCH_COLUMN pSearchColumn) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE CloseSearchHandle( 
            /* [in] */ ADS_SEARCH_HANDLE hSearchResult) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IDSSearchVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            IDSSearch __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            IDSSearch __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            IDSSearch __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *SetSearchPreference )( 
            IDSSearch __RPC_FAR * This,
            /* [in] */ PADS_SEARCHPREF_INFO pSearchPrefs,
            /* [in] */ DWORD dwNumPrefs);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *ExecuteSearch )( 
            IDSSearch __RPC_FAR * This,
            /* [in] */ LPWSTR pszSearchFilter,
            /* [in] */ LPWSTR __RPC_FAR *pAttributeNames,
            /* [in] */ DWORD dwNumberAttributes,
            /* [out] */ PADS_SEARCH_HANDLE phSearchResult);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *AbandonSearch )( 
            IDSSearch __RPC_FAR * This,
            /* [in] */ ADS_SEARCH_HANDLE phSearchResult);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetFirstRow )( 
            IDSSearch __RPC_FAR * This,
            /* [in] */ ADS_SEARCH_HANDLE hSearchResult);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetNextRow )( 
            IDSSearch __RPC_FAR * This,
            /* [in] */ ADS_SEARCH_HANDLE hSearchResult);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetPreviousRow )( 
            IDSSearch __RPC_FAR * This,
            /* [in] */ ADS_SEARCH_HANDLE hSearchResult);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetNextColumnName )( 
            IDSSearch __RPC_FAR * This,
            /* [in] */ ADS_SEARCH_HANDLE hSearchHandle,
            /* [out] */ LPWSTR __RPC_FAR *ppszColumnName);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetColumn )( 
            IDSSearch __RPC_FAR * This,
            /* [in] */ ADS_SEARCH_HANDLE hSearchResult,
            /* [in] */ LPWSTR szColumnName,
            /* [out] */ PADS_SEARCH_COLUMN pSearchColumn);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *FreeColumn )( 
            IDSSearch __RPC_FAR * This,
            /* [in] */ PADS_SEARCH_COLUMN pSearchColumn);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *CloseSearchHandle )( 
            IDSSearch __RPC_FAR * This,
            /* [in] */ ADS_SEARCH_HANDLE hSearchResult);
        
        END_INTERFACE
    } IDSSearchVtbl;

    interface IDSSearch
    {
        CONST_VTBL struct IDSSearchVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IDSSearch_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IDSSearch_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IDSSearch_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IDSSearch_SetSearchPreference(This,pSearchPrefs,dwNumPrefs)	\
    (This)->lpVtbl -> SetSearchPreference(This,pSearchPrefs,dwNumPrefs)

#define IDSSearch_ExecuteSearch(This,pszSearchFilter,pAttributeNames,dwNumberAttributes,phSearchResult)	\
    (This)->lpVtbl -> ExecuteSearch(This,pszSearchFilter,pAttributeNames,dwNumberAttributes,phSearchResult)

#define IDSSearch_AbandonSearch(This,phSearchResult)	\
    (This)->lpVtbl -> AbandonSearch(This,phSearchResult)

#define IDSSearch_GetFirstRow(This,hSearchResult)	\
    (This)->lpVtbl -> GetFirstRow(This,hSearchResult)

#define IDSSearch_GetNextRow(This,hSearchResult)	\
    (This)->lpVtbl -> GetNextRow(This,hSearchResult)

#define IDSSearch_GetPreviousRow(This,hSearchResult)	\
    (This)->lpVtbl -> GetPreviousRow(This,hSearchResult)

#define IDSSearch_GetNextColumnName(This,hSearchHandle,ppszColumnName)	\
    (This)->lpVtbl -> GetNextColumnName(This,hSearchHandle,ppszColumnName)

#define IDSSearch_GetColumn(This,hSearchResult,szColumnName,pSearchColumn)	\
    (This)->lpVtbl -> GetColumn(This,hSearchResult,szColumnName,pSearchColumn)

#define IDSSearch_FreeColumn(This,pSearchColumn)	\
    (This)->lpVtbl -> FreeColumn(This,pSearchColumn)

#define IDSSearch_CloseSearchHandle(This,hSearchResult)	\
    (This)->lpVtbl -> CloseSearchHandle(This,hSearchResult)

#endif /* COBJMACROS */


#endif 	/* C style interface */



HRESULT STDMETHODCALLTYPE IDSSearch_SetSearchPreference_Proxy( 
    IDSSearch __RPC_FAR * This,
    /* [in] */ PADS_SEARCHPREF_INFO pSearchPrefs,
    /* [in] */ DWORD dwNumPrefs);


void __RPC_STUB IDSSearch_SetSearchPreference_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IDSSearch_ExecuteSearch_Proxy( 
    IDSSearch __RPC_FAR * This,
    /* [in] */ LPWSTR pszSearchFilter,
    /* [in] */ LPWSTR __RPC_FAR *pAttributeNames,
    /* [in] */ DWORD dwNumberAttributes,
    /* [out] */ PADS_SEARCH_HANDLE phSearchResult);


void __RPC_STUB IDSSearch_ExecuteSearch_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IDSSearch_AbandonSearch_Proxy( 
    IDSSearch __RPC_FAR * This,
    /* [in] */ ADS_SEARCH_HANDLE phSearchResult);


void __RPC_STUB IDSSearch_AbandonSearch_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IDSSearch_GetFirstRow_Proxy( 
    IDSSearch __RPC_FAR * This,
    /* [in] */ ADS_SEARCH_HANDLE hSearchResult);


void __RPC_STUB IDSSearch_GetFirstRow_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IDSSearch_GetNextRow_Proxy( 
    IDSSearch __RPC_FAR * This,
    /* [in] */ ADS_SEARCH_HANDLE hSearchResult);


void __RPC_STUB IDSSearch_GetNextRow_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IDSSearch_GetPreviousRow_Proxy( 
    IDSSearch __RPC_FAR * This,
    /* [in] */ ADS_SEARCH_HANDLE hSearchResult);


void __RPC_STUB IDSSearch_GetPreviousRow_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IDSSearch_GetNextColumnName_Proxy( 
    IDSSearch __RPC_FAR * This,
    /* [in] */ ADS_SEARCH_HANDLE hSearchHandle,
    /* [out] */ LPWSTR __RPC_FAR *ppszColumnName);


void __RPC_STUB IDSSearch_GetNextColumnName_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IDSSearch_GetColumn_Proxy( 
    IDSSearch __RPC_FAR * This,
    /* [in] */ ADS_SEARCH_HANDLE hSearchResult,
    /* [in] */ LPWSTR szColumnName,
    /* [out] */ PADS_SEARCH_COLUMN pSearchColumn);


void __RPC_STUB IDSSearch_GetColumn_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IDSSearch_FreeColumn_Proxy( 
    IDSSearch __RPC_FAR * This,
    /* [in] */ PADS_SEARCH_COLUMN pSearchColumn);


void __RPC_STUB IDSSearch_FreeColumn_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IDSSearch_CloseSearchHandle_Proxy( 
    IDSSearch __RPC_FAR * This,
    /* [in] */ ADS_SEARCH_HANDLE hSearchResult);


void __RPC_STUB IDSSearch_CloseSearchHandle_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IDSSearch_INTERFACE_DEFINED__ */


#ifndef __IDirectoryAttrMgmt_INTERFACE_DEFINED__
#define __IDirectoryAttrMgmt_INTERFACE_DEFINED__

/****************************************
 * Generated header for interface: IDirectoryAttrMgmt
 * at Mon Oct 13 13:47:30 1997
 * using MIDL 3.00.44
 ****************************************/
/* [object][uuid] */ 



EXTERN_C const IID IID_IDirectoryAttrMgmt;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    interface IDirectoryAttrMgmt : public IUnknown
    {
    public:
        virtual HRESULT STDMETHODCALLTYPE EnumAttributes( 
            LPWSTR __RPC_FAR *ppszAttrNames,
            DWORD dwNumAttributes,
            PADS_ATTR_DEF __RPC_FAR *ppAttrDefinition,
            DWORD __RPC_FAR *pdwNumAttributes) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE CreateAttributeDefinition( 
            LPWSTR pszAttributeName,
            PADS_ATTR_DEF pAttributeDefinition) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE ReadAttributeDefinition( 
            LPWSTR pszAttributeName,
            PADS_ATTR_DEF __RPC_FAR *pAttributeDefinition) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE WriteAttributeDefinition( 
            LPWSTR pszAttributeName,
            PADS_ATTR_DEF pAttributeDefinition) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE DeleteAttributeDefinition( 
            LPWSTR pszAttributeName) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IDirectoryAttrMgmtVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            IDirectoryAttrMgmt __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            IDirectoryAttrMgmt __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            IDirectoryAttrMgmt __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *EnumAttributes )( 
            IDirectoryAttrMgmt __RPC_FAR * This,
            LPWSTR __RPC_FAR *ppszAttrNames,
            DWORD dwNumAttributes,
            PADS_ATTR_DEF __RPC_FAR *ppAttrDefinition,
            DWORD __RPC_FAR *pdwNumAttributes);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *CreateAttributeDefinition )( 
            IDirectoryAttrMgmt __RPC_FAR * This,
            LPWSTR pszAttributeName,
            PADS_ATTR_DEF pAttributeDefinition);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *ReadAttributeDefinition )( 
            IDirectoryAttrMgmt __RPC_FAR * This,
            LPWSTR pszAttributeName,
            PADS_ATTR_DEF __RPC_FAR *pAttributeDefinition);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *WriteAttributeDefinition )( 
            IDirectoryAttrMgmt __RPC_FAR * This,
            LPWSTR pszAttributeName,
            PADS_ATTR_DEF pAttributeDefinition);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *DeleteAttributeDefinition )( 
            IDirectoryAttrMgmt __RPC_FAR * This,
            LPWSTR pszAttributeName);
        
        END_INTERFACE
    } IDirectoryAttrMgmtVtbl;

    interface IDirectoryAttrMgmt
    {
        CONST_VTBL struct IDirectoryAttrMgmtVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IDirectoryAttrMgmt_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IDirectoryAttrMgmt_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IDirectoryAttrMgmt_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IDirectoryAttrMgmt_EnumAttributes(This,ppszAttrNames,dwNumAttributes,ppAttrDefinition,pdwNumAttributes)	\
    (This)->lpVtbl -> EnumAttributes(This,ppszAttrNames,dwNumAttributes,ppAttrDefinition,pdwNumAttributes)

#define IDirectoryAttrMgmt_CreateAttributeDefinition(This,pszAttributeName,pAttributeDefinition)	\
    (This)->lpVtbl -> CreateAttributeDefinition(This,pszAttributeName,pAttributeDefinition)

#define IDirectoryAttrMgmt_ReadAttributeDefinition(This,pszAttributeName,pAttributeDefinition)	\
    (This)->lpVtbl -> ReadAttributeDefinition(This,pszAttributeName,pAttributeDefinition)

#define IDirectoryAttrMgmt_WriteAttributeDefinition(This,pszAttributeName,pAttributeDefinition)	\
    (This)->lpVtbl -> WriteAttributeDefinition(This,pszAttributeName,pAttributeDefinition)

#define IDirectoryAttrMgmt_DeleteAttributeDefinition(This,pszAttributeName)	\
    (This)->lpVtbl -> DeleteAttributeDefinition(This,pszAttributeName)

#endif /* COBJMACROS */


#endif 	/* C style interface */



HRESULT STDMETHODCALLTYPE IDirectoryAttrMgmt_EnumAttributes_Proxy( 
    IDirectoryAttrMgmt __RPC_FAR * This,
    LPWSTR __RPC_FAR *ppszAttrNames,
    DWORD dwNumAttributes,
    PADS_ATTR_DEF __RPC_FAR *ppAttrDefinition,
    DWORD __RPC_FAR *pdwNumAttributes);


void __RPC_STUB IDirectoryAttrMgmt_EnumAttributes_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IDirectoryAttrMgmt_CreateAttributeDefinition_Proxy( 
    IDirectoryAttrMgmt __RPC_FAR * This,
    LPWSTR pszAttributeName,
    PADS_ATTR_DEF pAttributeDefinition);


void __RPC_STUB IDirectoryAttrMgmt_CreateAttributeDefinition_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IDirectoryAttrMgmt_ReadAttributeDefinition_Proxy( 
    IDirectoryAttrMgmt __RPC_FAR * This,
    LPWSTR pszAttributeName,
    PADS_ATTR_DEF __RPC_FAR *pAttributeDefinition);


void __RPC_STUB IDirectoryAttrMgmt_ReadAttributeDefinition_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IDirectoryAttrMgmt_WriteAttributeDefinition_Proxy( 
    IDirectoryAttrMgmt __RPC_FAR * This,
    LPWSTR pszAttributeName,
    PADS_ATTR_DEF pAttributeDefinition);


void __RPC_STUB IDirectoryAttrMgmt_WriteAttributeDefinition_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IDirectoryAttrMgmt_DeleteAttributeDefinition_Proxy( 
    IDirectoryAttrMgmt __RPC_FAR * This,
    LPWSTR pszAttributeName);


void __RPC_STUB IDirectoryAttrMgmt_DeleteAttributeDefinition_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IDirectoryAttrMgmt_INTERFACE_DEFINED__ */


#ifndef __IDSAttrMgmt_INTERFACE_DEFINED__
#define __IDSAttrMgmt_INTERFACE_DEFINED__

/****************************************
 * Generated header for interface: IDSAttrMgmt
 * at Mon Oct 13 13:47:30 1997
 * using MIDL 3.00.44
 ****************************************/
/* [object][uuid] */ 



EXTERN_C const IID IID_IDSAttrMgmt;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    interface IDSAttrMgmt : public IUnknown
    {
    public:
        virtual HRESULT STDMETHODCALLTYPE EnumAttributes( 
            LPWSTR __RPC_FAR *ppszAttrNames,
            DWORD dwNumAttributes,
            PADS_ATTR_DEF __RPC_FAR *ppAttrDefinition,
            DWORD __RPC_FAR *pdwNumAttributes) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE CreateAttributeDefinition( 
            LPWSTR pszAttributeName,
            PADS_ATTR_DEF pAttributeDefinition) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE ReadAttributeDefinition( 
            LPWSTR pszAttributeName,
            PADS_ATTR_DEF __RPC_FAR *pAttributeDefinition) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE WriteAttributeDefinition( 
            LPWSTR pszAttributeName,
            PADS_ATTR_DEF pAttributeDefinition) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE DeleteAttributeDefinition( 
            LPWSTR pszAttributeName) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IDSAttrMgmtVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            IDSAttrMgmt __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            IDSAttrMgmt __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            IDSAttrMgmt __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *EnumAttributes )( 
            IDSAttrMgmt __RPC_FAR * This,
            LPWSTR __RPC_FAR *ppszAttrNames,
            DWORD dwNumAttributes,
            PADS_ATTR_DEF __RPC_FAR *ppAttrDefinition,
            DWORD __RPC_FAR *pdwNumAttributes);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *CreateAttributeDefinition )( 
            IDSAttrMgmt __RPC_FAR * This,
            LPWSTR pszAttributeName,
            PADS_ATTR_DEF pAttributeDefinition);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *ReadAttributeDefinition )( 
            IDSAttrMgmt __RPC_FAR * This,
            LPWSTR pszAttributeName,
            PADS_ATTR_DEF __RPC_FAR *pAttributeDefinition);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *WriteAttributeDefinition )( 
            IDSAttrMgmt __RPC_FAR * This,
            LPWSTR pszAttributeName,
            PADS_ATTR_DEF pAttributeDefinition);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *DeleteAttributeDefinition )( 
            IDSAttrMgmt __RPC_FAR * This,
            LPWSTR pszAttributeName);
        
        END_INTERFACE
    } IDSAttrMgmtVtbl;

    interface IDSAttrMgmt
    {
        CONST_VTBL struct IDSAttrMgmtVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IDSAttrMgmt_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IDSAttrMgmt_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IDSAttrMgmt_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IDSAttrMgmt_EnumAttributes(This,ppszAttrNames,dwNumAttributes,ppAttrDefinition,pdwNumAttributes)	\
    (This)->lpVtbl -> EnumAttributes(This,ppszAttrNames,dwNumAttributes,ppAttrDefinition,pdwNumAttributes)

#define IDSAttrMgmt_CreateAttributeDefinition(This,pszAttributeName,pAttributeDefinition)	\
    (This)->lpVtbl -> CreateAttributeDefinition(This,pszAttributeName,pAttributeDefinition)

#define IDSAttrMgmt_ReadAttributeDefinition(This,pszAttributeName,pAttributeDefinition)	\
    (This)->lpVtbl -> ReadAttributeDefinition(This,pszAttributeName,pAttributeDefinition)

#define IDSAttrMgmt_WriteAttributeDefinition(This,pszAttributeName,pAttributeDefinition)	\
    (This)->lpVtbl -> WriteAttributeDefinition(This,pszAttributeName,pAttributeDefinition)

#define IDSAttrMgmt_DeleteAttributeDefinition(This,pszAttributeName)	\
    (This)->lpVtbl -> DeleteAttributeDefinition(This,pszAttributeName)

#endif /* COBJMACROS */


#endif 	/* C style interface */



HRESULT STDMETHODCALLTYPE IDSAttrMgmt_EnumAttributes_Proxy( 
    IDSAttrMgmt __RPC_FAR * This,
    LPWSTR __RPC_FAR *ppszAttrNames,
    DWORD dwNumAttributes,
    PADS_ATTR_DEF __RPC_FAR *ppAttrDefinition,
    DWORD __RPC_FAR *pdwNumAttributes);


void __RPC_STUB IDSAttrMgmt_EnumAttributes_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IDSAttrMgmt_CreateAttributeDefinition_Proxy( 
    IDSAttrMgmt __RPC_FAR * This,
    LPWSTR pszAttributeName,
    PADS_ATTR_DEF pAttributeDefinition);


void __RPC_STUB IDSAttrMgmt_CreateAttributeDefinition_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IDSAttrMgmt_ReadAttributeDefinition_Proxy( 
    IDSAttrMgmt __RPC_FAR * This,
    LPWSTR pszAttributeName,
    PADS_ATTR_DEF __RPC_FAR *pAttributeDefinition);


void __RPC_STUB IDSAttrMgmt_ReadAttributeDefinition_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IDSAttrMgmt_WriteAttributeDefinition_Proxy( 
    IDSAttrMgmt __RPC_FAR * This,
    LPWSTR pszAttributeName,
    PADS_ATTR_DEF pAttributeDefinition);


void __RPC_STUB IDSAttrMgmt_WriteAttributeDefinition_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IDSAttrMgmt_DeleteAttributeDefinition_Proxy( 
    IDSAttrMgmt __RPC_FAR * This,
    LPWSTR pszAttributeName);


void __RPC_STUB IDSAttrMgmt_DeleteAttributeDefinition_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IDSAttrMgmt_INTERFACE_DEFINED__ */


#ifndef __IADsAggregatee_INTERFACE_DEFINED__
#define __IADsAggregatee_INTERFACE_DEFINED__

/****************************************
 * Generated header for interface: IADsAggregatee
 * at Mon Oct 13 13:47:30 1997
 * using MIDL 3.00.44
 ****************************************/
/* [object][uuid] */ 



EXTERN_C const IID IID_IADsAggregatee;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    interface IADsAggregatee : public IUnknown
    {
    public:
        virtual HRESULT STDMETHODCALLTYPE ConnectAsAggregatee( 
            IUnknown __RPC_FAR *pOuterUnknown) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE DisconnectAsAggregatee( void) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE RelinquishInterface( 
            REFIID riid) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE RestoreInterface( 
            REFIID riid) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IADsAggregateeVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            IADsAggregatee __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            IADsAggregatee __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            IADsAggregatee __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *ConnectAsAggregatee )( 
            IADsAggregatee __RPC_FAR * This,
            IUnknown __RPC_FAR *pOuterUnknown);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *DisconnectAsAggregatee )( 
            IADsAggregatee __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *RelinquishInterface )( 
            IADsAggregatee __RPC_FAR * This,
            REFIID riid);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *RestoreInterface )( 
            IADsAggregatee __RPC_FAR * This,
            REFIID riid);
        
        END_INTERFACE
    } IADsAggregateeVtbl;

    interface IADsAggregatee
    {
        CONST_VTBL struct IADsAggregateeVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IADsAggregatee_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IADsAggregatee_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IADsAggregatee_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IADsAggregatee_ConnectAsAggregatee(This,pOuterUnknown)	\
    (This)->lpVtbl -> ConnectAsAggregatee(This,pOuterUnknown)

#define IADsAggregatee_DisconnectAsAggregatee(This)	\
    (This)->lpVtbl -> DisconnectAsAggregatee(This)

#define IADsAggregatee_RelinquishInterface(This,riid)	\
    (This)->lpVtbl -> RelinquishInterface(This,riid)

#define IADsAggregatee_RestoreInterface(This,riid)	\
    (This)->lpVtbl -> RestoreInterface(This,riid)

#endif /* COBJMACROS */


#endif 	/* C style interface */



HRESULT STDMETHODCALLTYPE IADsAggregatee_ConnectAsAggregatee_Proxy( 
    IADsAggregatee __RPC_FAR * This,
    IUnknown __RPC_FAR *pOuterUnknown);


void __RPC_STUB IADsAggregatee_ConnectAsAggregatee_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IADsAggregatee_DisconnectAsAggregatee_Proxy( 
    IADsAggregatee __RPC_FAR * This);


void __RPC_STUB IADsAggregatee_DisconnectAsAggregatee_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IADsAggregatee_RelinquishInterface_Proxy( 
    IADsAggregatee __RPC_FAR * This,
    REFIID riid);


void __RPC_STUB IADsAggregatee_RelinquishInterface_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IADsAggregatee_RestoreInterface_Proxy( 
    IADsAggregatee __RPC_FAR * This,
    REFIID riid);


void __RPC_STUB IADsAggregatee_RestoreInterface_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IADsAggregatee_INTERFACE_DEFINED__ */


#ifndef __IADsAggregator_INTERFACE_DEFINED__
#define __IADsAggregator_INTERFACE_DEFINED__

/****************************************
 * Generated header for interface: IADsAggregator
 * at Mon Oct 13 13:47:30 1997
 * using MIDL 3.00.44
 ****************************************/
/* [object][uuid] */ 



EXTERN_C const IID IID_IADsAggregator;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    interface IADsAggregator : public IUnknown
    {
    public:
        virtual HRESULT STDMETHODCALLTYPE ConnectAsAggregator( 
            IUnknown __RPC_FAR *pAggregatee) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE DisconnectAsAggregator( void) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IADsAggregatorVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            IADsAggregator __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            IADsAggregator __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            IADsAggregator __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *ConnectAsAggregator )( 
            IADsAggregator __RPC_FAR * This,
            IUnknown __RPC_FAR *pAggregatee);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *DisconnectAsAggregator )( 
            IADsAggregator __RPC_FAR * This);
        
        END_INTERFACE
    } IADsAggregatorVtbl;

    interface IADsAggregator
    {
        CONST_VTBL struct IADsAggregatorVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IADsAggregator_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IADsAggregator_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IADsAggregator_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IADsAggregator_ConnectAsAggregator(This,pAggregatee)	\
    (This)->lpVtbl -> ConnectAsAggregator(This,pAggregatee)

#define IADsAggregator_DisconnectAsAggregator(This)	\
    (This)->lpVtbl -> DisconnectAsAggregator(This)

#endif /* COBJMACROS */


#endif 	/* C style interface */



HRESULT STDMETHODCALLTYPE IADsAggregator_ConnectAsAggregator_Proxy( 
    IADsAggregator __RPC_FAR * This,
    IUnknown __RPC_FAR *pAggregatee);


void __RPC_STUB IADsAggregator_ConnectAsAggregator_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IADsAggregator_DisconnectAsAggregator_Proxy( 
    IADsAggregator __RPC_FAR * This);


void __RPC_STUB IADsAggregator_DisconnectAsAggregator_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IADsAggregator_INTERFACE_DEFINED__ */


#ifndef __IADsAccessControlEntry_INTERFACE_DEFINED__
#define __IADsAccessControlEntry_INTERFACE_DEFINED__

/****************************************
 * Generated header for interface: IADsAccessControlEntry
 * at Mon Oct 13 13:47:30 1997
 * using MIDL 3.00.44
 ****************************************/
/* [object][dual][oleautomation][uuid] */ 



EXTERN_C const IID IID_IADsAccessControlEntry;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    interface IADsAccessControlEntry : public IDispatch
    {
    public:
        virtual /* [id][propget] */ HRESULT STDMETHODCALLTYPE get_AccessMask( 
            /* [retval][out] */ long __RPC_FAR *retval) = 0;
        
        virtual /* [id][propput] */ HRESULT STDMETHODCALLTYPE put_AccessMask( 
            /* [in] */ long lnAccessMask) = 0;
        
        virtual /* [id][propget] */ HRESULT STDMETHODCALLTYPE get_AceType( 
            /* [retval][out] */ long __RPC_FAR *retval) = 0;
        
        virtual /* [id][propput] */ HRESULT STDMETHODCALLTYPE put_AceType( 
            /* [in] */ long lnAceType) = 0;
        
        virtual /* [id][propget] */ HRESULT STDMETHODCALLTYPE get_AceFlags( 
            /* [retval][out] */ long __RPC_FAR *retval) = 0;
        
        virtual /* [id][propput] */ HRESULT STDMETHODCALLTYPE put_AceFlags( 
            /* [in] */ long lnAceFlags) = 0;
        
        virtual /* [id][propget] */ HRESULT STDMETHODCALLTYPE get_Flags( 
            /* [retval][out] */ long __RPC_FAR *retval) = 0;
        
        virtual /* [id][propput] */ HRESULT STDMETHODCALLTYPE put_Flags( 
            /* [in] */ long lnFlags) = 0;
        
        virtual /* [id][propget] */ HRESULT STDMETHODCALLTYPE get_ObjectType( 
            /* [retval][out] */ BSTR __RPC_FAR *retval) = 0;
        
        virtual /* [id][propput] */ HRESULT STDMETHODCALLTYPE put_ObjectType( 
            /* [in] */ BSTR bstrObjectType) = 0;
        
        virtual /* [id][propget] */ HRESULT STDMETHODCALLTYPE get_InheritedObjectType( 
            /* [retval][out] */ BSTR __RPC_FAR *retval) = 0;
        
        virtual /* [id][propput] */ HRESULT STDMETHODCALLTYPE put_InheritedObjectType( 
            /* [in] */ BSTR bstrInheritedObjectType) = 0;
        
        virtual /* [id][propget] */ HRESULT STDMETHODCALLTYPE get_Trustee( 
            /* [retval][out] */ BSTR __RPC_FAR *retval) = 0;
        
        virtual /* [id][propput] */ HRESULT STDMETHODCALLTYPE put_Trustee( 
            /* [in] */ BSTR bstrTrustee) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IADsAccessControlEntryVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            IADsAccessControlEntry __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            IADsAccessControlEntry __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            IADsAccessControlEntry __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfoCount )( 
            IADsAccessControlEntry __RPC_FAR * This,
            /* [out] */ UINT __RPC_FAR *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfo )( 
            IADsAccessControlEntry __RPC_FAR * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo __RPC_FAR *__RPC_FAR *ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetIDsOfNames )( 
            IADsAccessControlEntry __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR __RPC_FAR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID __RPC_FAR *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Invoke )( 
            IADsAccessControlEntry __RPC_FAR * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS __RPC_FAR *pDispParams,
            /* [out] */ VARIANT __RPC_FAR *pVarResult,
            /* [out] */ EXCEPINFO __RPC_FAR *pExcepInfo,
            /* [out] */ UINT __RPC_FAR *puArgErr);
        
        /* [id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_AccessMask )( 
            IADsAccessControlEntry __RPC_FAR * This,
            /* [retval][out] */ long __RPC_FAR *retval);
        
        /* [id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_AccessMask )( 
            IADsAccessControlEntry __RPC_FAR * This,
            /* [in] */ long lnAccessMask);
        
        /* [id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_AceType )( 
            IADsAccessControlEntry __RPC_FAR * This,
            /* [retval][out] */ long __RPC_FAR *retval);
        
        /* [id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_AceType )( 
            IADsAccessControlEntry __RPC_FAR * This,
            /* [in] */ long lnAceType);
        
        /* [id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_AceFlags )( 
            IADsAccessControlEntry __RPC_FAR * This,
            /* [retval][out] */ long __RPC_FAR *retval);
        
        /* [id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_AceFlags )( 
            IADsAccessControlEntry __RPC_FAR * This,
            /* [in] */ long lnAceFlags);
        
        /* [id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Flags )( 
            IADsAccessControlEntry __RPC_FAR * This,
            /* [retval][out] */ long __RPC_FAR *retval);
        
        /* [id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_Flags )( 
            IADsAccessControlEntry __RPC_FAR * This,
            /* [in] */ long lnFlags);
        
        /* [id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_ObjectType )( 
            IADsAccessControlEntry __RPC_FAR * This,
            /* [retval][out] */ BSTR __RPC_FAR *retval);
        
        /* [id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_ObjectType )( 
            IADsAccessControlEntry __RPC_FAR * This,
            /* [in] */ BSTR bstrObjectType);
        
        /* [id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_InheritedObjectType )( 
            IADsAccessControlEntry __RPC_FAR * This,
            /* [retval][out] */ BSTR __RPC_FAR *retval);
        
        /* [id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_InheritedObjectType )( 
            IADsAccessControlEntry __RPC_FAR * This,
            /* [in] */ BSTR bstrInheritedObjectType);
        
        /* [id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Trustee )( 
            IADsAccessControlEntry __RPC_FAR * This,
            /* [retval][out] */ BSTR __RPC_FAR *retval);
        
        /* [id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_Trustee )( 
            IADsAccessControlEntry __RPC_FAR * This,
            /* [in] */ BSTR bstrTrustee);
        
        END_INTERFACE
    } IADsAccessControlEntryVtbl;

    interface IADsAccessControlEntry
    {
        CONST_VTBL struct IADsAccessControlEntryVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IADsAccessControlEntry_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IADsAccessControlEntry_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IADsAccessControlEntry_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IADsAccessControlEntry_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define IADsAccessControlEntry_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define IADsAccessControlEntry_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define IADsAccessControlEntry_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)


#define IADsAccessControlEntry_get_AccessMask(This,retval)	\
    (This)->lpVtbl -> get_AccessMask(This,retval)

#define IADsAccessControlEntry_put_AccessMask(This,lnAccessMask)	\
    (This)->lpVtbl -> put_AccessMask(This,lnAccessMask)

#define IADsAccessControlEntry_get_AceType(This,retval)	\
    (This)->lpVtbl -> get_AceType(This,retval)

#define IADsAccessControlEntry_put_AceType(This,lnAceType)	\
    (This)->lpVtbl -> put_AceType(This,lnAceType)

#define IADsAccessControlEntry_get_AceFlags(This,retval)	\
    (This)->lpVtbl -> get_AceFlags(This,retval)

#define IADsAccessControlEntry_put_AceFlags(This,lnAceFlags)	\
    (This)->lpVtbl -> put_AceFlags(This,lnAceFlags)

#define IADsAccessControlEntry_get_Flags(This,retval)	\
    (This)->lpVtbl -> get_Flags(This,retval)

#define IADsAccessControlEntry_put_Flags(This,lnFlags)	\
    (This)->lpVtbl -> put_Flags(This,lnFlags)

#define IADsAccessControlEntry_get_ObjectType(This,retval)	\
    (This)->lpVtbl -> get_ObjectType(This,retval)

#define IADsAccessControlEntry_put_ObjectType(This,bstrObjectType)	\
    (This)->lpVtbl -> put_ObjectType(This,bstrObjectType)

#define IADsAccessControlEntry_get_InheritedObjectType(This,retval)	\
    (This)->lpVtbl -> get_InheritedObjectType(This,retval)

#define IADsAccessControlEntry_put_InheritedObjectType(This,bstrInheritedObjectType)	\
    (This)->lpVtbl -> put_InheritedObjectType(This,bstrInheritedObjectType)

#define IADsAccessControlEntry_get_Trustee(This,retval)	\
    (This)->lpVtbl -> get_Trustee(This,retval)

#define IADsAccessControlEntry_put_Trustee(This,bstrTrustee)	\
    (This)->lpVtbl -> put_Trustee(This,bstrTrustee)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [id][propget] */ HRESULT STDMETHODCALLTYPE IADsAccessControlEntry_get_AccessMask_Proxy( 
    IADsAccessControlEntry __RPC_FAR * This,
    /* [retval][out] */ long __RPC_FAR *retval);


void __RPC_STUB IADsAccessControlEntry_get_AccessMask_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [id][propput] */ HRESULT STDMETHODCALLTYPE IADsAccessControlEntry_put_AccessMask_Proxy( 
    IADsAccessControlEntry __RPC_FAR * This,
    /* [in] */ long lnAccessMask);


void __RPC_STUB IADsAccessControlEntry_put_AccessMask_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [id][propget] */ HRESULT STDMETHODCALLTYPE IADsAccessControlEntry_get_AceType_Proxy( 
    IADsAccessControlEntry __RPC_FAR * This,
    /* [retval][out] */ long __RPC_FAR *retval);


void __RPC_STUB IADsAccessControlEntry_get_AceType_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [id][propput] */ HRESULT STDMETHODCALLTYPE IADsAccessControlEntry_put_AceType_Proxy( 
    IADsAccessControlEntry __RPC_FAR * This,
    /* [in] */ long lnAceType);


void __RPC_STUB IADsAccessControlEntry_put_AceType_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [id][propget] */ HRESULT STDMETHODCALLTYPE IADsAccessControlEntry_get_AceFlags_Proxy( 
    IADsAccessControlEntry __RPC_FAR * This,
    /* [retval][out] */ long __RPC_FAR *retval);


void __RPC_STUB IADsAccessControlEntry_get_AceFlags_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [id][propput] */ HRESULT STDMETHODCALLTYPE IADsAccessControlEntry_put_AceFlags_Proxy( 
    IADsAccessControlEntry __RPC_FAR * This,
    /* [in] */ long lnAceFlags);


void __RPC_STUB IADsAccessControlEntry_put_AceFlags_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [id][propget] */ HRESULT STDMETHODCALLTYPE IADsAccessControlEntry_get_Flags_Proxy( 
    IADsAccessControlEntry __RPC_FAR * This,
    /* [retval][out] */ long __RPC_FAR *retval);


void __RPC_STUB IADsAccessControlEntry_get_Flags_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [id][propput] */ HRESULT STDMETHODCALLTYPE IADsAccessControlEntry_put_Flags_Proxy( 
    IADsAccessControlEntry __RPC_FAR * This,
    /* [in] */ long lnFlags);


void __RPC_STUB IADsAccessControlEntry_put_Flags_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [id][propget] */ HRESULT STDMETHODCALLTYPE IADsAccessControlEntry_get_ObjectType_Proxy( 
    IADsAccessControlEntry __RPC_FAR * This,
    /* [retval][out] */ BSTR __RPC_FAR *retval);


void __RPC_STUB IADsAccessControlEntry_get_ObjectType_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [id][propput] */ HRESULT STDMETHODCALLTYPE IADsAccessControlEntry_put_ObjectType_Proxy( 
    IADsAccessControlEntry __RPC_FAR * This,
    /* [in] */ BSTR bstrObjectType);


void __RPC_STUB IADsAccessControlEntry_put_ObjectType_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [id][propget] */ HRESULT STDMETHODCALLTYPE IADsAccessControlEntry_get_InheritedObjectType_Proxy( 
    IADsAccessControlEntry __RPC_FAR * This,
    /* [retval][out] */ BSTR __RPC_FAR *retval);


void __RPC_STUB IADsAccessControlEntry_get_InheritedObjectType_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [id][propput] */ HRESULT STDMETHODCALLTYPE IADsAccessControlEntry_put_InheritedObjectType_Proxy( 
    IADsAccessControlEntry __RPC_FAR * This,
    /* [in] */ BSTR bstrInheritedObjectType);


void __RPC_STUB IADsAccessControlEntry_put_InheritedObjectType_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [id][propget] */ HRESULT STDMETHODCALLTYPE IADsAccessControlEntry_get_Trustee_Proxy( 
    IADsAccessControlEntry __RPC_FAR * This,
    /* [retval][out] */ BSTR __RPC_FAR *retval);


void __RPC_STUB IADsAccessControlEntry_get_Trustee_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [id][propput] */ HRESULT STDMETHODCALLTYPE IADsAccessControlEntry_put_Trustee_Proxy( 
    IADsAccessControlEntry __RPC_FAR * This,
    /* [in] */ BSTR bstrTrustee);


void __RPC_STUB IADsAccessControlEntry_put_Trustee_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IADsAccessControlEntry_INTERFACE_DEFINED__ */


#ifdef __cplusplus
EXTERN_C const CLSID CLSID_AccessControlEntry;

class AccessControlEntry;
#endif

#ifndef __IADsAccessControlList_INTERFACE_DEFINED__
#define __IADsAccessControlList_INTERFACE_DEFINED__

/****************************************
 * Generated header for interface: IADsAccessControlList
 * at Mon Oct 13 13:47:30 1997
 * using MIDL 3.00.44
 ****************************************/
/* [object][dual][oleautomation][uuid] */ 



EXTERN_C const IID IID_IADsAccessControlList;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    interface IADsAccessControlList : public IDispatch
    {
    public:
        virtual /* [id][propget] */ HRESULT STDMETHODCALLTYPE get_AclRevision( 
            /* [retval][out] */ long __RPC_FAR *retval) = 0;
        
        virtual /* [id][propput] */ HRESULT STDMETHODCALLTYPE put_AclRevision( 
            /* [in] */ long lnAclRevision) = 0;
        
        virtual /* [id][propget] */ HRESULT STDMETHODCALLTYPE get_AceCount( 
            /* [retval][out] */ long __RPC_FAR *retval) = 0;
        
        virtual /* [id][propput] */ HRESULT STDMETHODCALLTYPE put_AceCount( 
            /* [in] */ long lnAceCount) = 0;
        
        virtual /* [id] */ HRESULT STDMETHODCALLTYPE AddAce( 
            /* [in] */ IDispatch __RPC_FAR *pAccessControlEntry) = 0;
        
        virtual /* [id] */ HRESULT STDMETHODCALLTYPE RemoveAce( 
            /* [in] */ IDispatch __RPC_FAR *pAccessControlEntry) = 0;
        
        virtual /* [id] */ HRESULT STDMETHODCALLTYPE CopyAccessList( 
            /* [retval][out] */ IDispatch __RPC_FAR *__RPC_FAR *ppAccessControlList) = 0;
        
        virtual /* [id][restricted][propget] */ HRESULT STDMETHODCALLTYPE get__NewEnum( 
            /* [retval][out] */ IUnknown __RPC_FAR *__RPC_FAR *retval) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IADsAccessControlListVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            IADsAccessControlList __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            IADsAccessControlList __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            IADsAccessControlList __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfoCount )( 
            IADsAccessControlList __RPC_FAR * This,
            /* [out] */ UINT __RPC_FAR *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfo )( 
            IADsAccessControlList __RPC_FAR * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo __RPC_FAR *__RPC_FAR *ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetIDsOfNames )( 
            IADsAccessControlList __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR __RPC_FAR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID __RPC_FAR *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Invoke )( 
            IADsAccessControlList __RPC_FAR * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS __RPC_FAR *pDispParams,
            /* [out] */ VARIANT __RPC_FAR *pVarResult,
            /* [out] */ EXCEPINFO __RPC_FAR *pExcepInfo,
            /* [out] */ UINT __RPC_FAR *puArgErr);
        
        /* [id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_AclRevision )( 
            IADsAccessControlList __RPC_FAR * This,
            /* [retval][out] */ long __RPC_FAR *retval);
        
        /* [id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_AclRevision )( 
            IADsAccessControlList __RPC_FAR * This,
            /* [in] */ long lnAclRevision);
        
        /* [id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_AceCount )( 
            IADsAccessControlList __RPC_FAR * This,
            /* [retval][out] */ long __RPC_FAR *retval);
        
        /* [id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_AceCount )( 
            IADsAccessControlList __RPC_FAR * This,
            /* [in] */ long lnAceCount);
        
        /* [id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *AddAce )( 
            IADsAccessControlList __RPC_FAR * This,
            /* [in] */ IDispatch __RPC_FAR *pAccessControlEntry);
        
        /* [id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *RemoveAce )( 
            IADsAccessControlList __RPC_FAR * This,
            /* [in] */ IDispatch __RPC_FAR *pAccessControlEntry);
        
        /* [id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *CopyAccessList )( 
            IADsAccessControlList __RPC_FAR * This,
            /* [retval][out] */ IDispatch __RPC_FAR *__RPC_FAR *ppAccessControlList);
        
        /* [id][restricted][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get__NewEnum )( 
            IADsAccessControlList __RPC_FAR * This,
            /* [retval][out] */ IUnknown __RPC_FAR *__RPC_FAR *retval);
        
        END_INTERFACE
    } IADsAccessControlListVtbl;

    interface IADsAccessControlList
    {
        CONST_VTBL struct IADsAccessControlListVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IADsAccessControlList_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IADsAccessControlList_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IADsAccessControlList_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IADsAccessControlList_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define IADsAccessControlList_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define IADsAccessControlList_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define IADsAccessControlList_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)


#define IADsAccessControlList_get_AclRevision(This,retval)	\
    (This)->lpVtbl -> get_AclRevision(This,retval)

#define IADsAccessControlList_put_AclRevision(This,lnAclRevision)	\
    (This)->lpVtbl -> put_AclRevision(This,lnAclRevision)

#define IADsAccessControlList_get_AceCount(This,retval)	\
    (This)->lpVtbl -> get_AceCount(This,retval)

#define IADsAccessControlList_put_AceCount(This,lnAceCount)	\
    (This)->lpVtbl -> put_AceCount(This,lnAceCount)

#define IADsAccessControlList_AddAce(This,pAccessControlEntry)	\
    (This)->lpVtbl -> AddAce(This,pAccessControlEntry)

#define IADsAccessControlList_RemoveAce(This,pAccessControlEntry)	\
    (This)->lpVtbl -> RemoveAce(This,pAccessControlEntry)

#define IADsAccessControlList_CopyAccessList(This,ppAccessControlList)	\
    (This)->lpVtbl -> CopyAccessList(This,ppAccessControlList)

#define IADsAccessControlList_get__NewEnum(This,retval)	\
    (This)->lpVtbl -> get__NewEnum(This,retval)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [id][propget] */ HRESULT STDMETHODCALLTYPE IADsAccessControlList_get_AclRevision_Proxy( 
    IADsAccessControlList __RPC_FAR * This,
    /* [retval][out] */ long __RPC_FAR *retval);


void __RPC_STUB IADsAccessControlList_get_AclRevision_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [id][propput] */ HRESULT STDMETHODCALLTYPE IADsAccessControlList_put_AclRevision_Proxy( 
    IADsAccessControlList __RPC_FAR * This,
    /* [in] */ long lnAclRevision);


void __RPC_STUB IADsAccessControlList_put_AclRevision_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [id][propget] */ HRESULT STDMETHODCALLTYPE IADsAccessControlList_get_AceCount_Proxy( 
    IADsAccessControlList __RPC_FAR * This,
    /* [retval][out] */ long __RPC_FAR *retval);


void __RPC_STUB IADsAccessControlList_get_AceCount_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [id][propput] */ HRESULT STDMETHODCALLTYPE IADsAccessControlList_put_AceCount_Proxy( 
    IADsAccessControlList __RPC_FAR * This,
    /* [in] */ long lnAceCount);


void __RPC_STUB IADsAccessControlList_put_AceCount_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [id] */ HRESULT STDMETHODCALLTYPE IADsAccessControlList_AddAce_Proxy( 
    IADsAccessControlList __RPC_FAR * This,
    /* [in] */ IDispatch __RPC_FAR *pAccessControlEntry);


void __RPC_STUB IADsAccessControlList_AddAce_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [id] */ HRESULT STDMETHODCALLTYPE IADsAccessControlList_RemoveAce_Proxy( 
    IADsAccessControlList __RPC_FAR * This,
    /* [in] */ IDispatch __RPC_FAR *pAccessControlEntry);


void __RPC_STUB IADsAccessControlList_RemoveAce_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [id] */ HRESULT STDMETHODCALLTYPE IADsAccessControlList_CopyAccessList_Proxy( 
    IADsAccessControlList __RPC_FAR * This,
    /* [retval][out] */ IDispatch __RPC_FAR *__RPC_FAR *ppAccessControlList);


void __RPC_STUB IADsAccessControlList_CopyAccessList_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [id][restricted][propget] */ HRESULT STDMETHODCALLTYPE IADsAccessControlList_get__NewEnum_Proxy( 
    IADsAccessControlList __RPC_FAR * This,
    /* [retval][out] */ IUnknown __RPC_FAR *__RPC_FAR *retval);


void __RPC_STUB IADsAccessControlList_get__NewEnum_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IADsAccessControlList_INTERFACE_DEFINED__ */


#ifdef __cplusplus
EXTERN_C const CLSID CLSID_AccessControlList;

class AccessControlList;
#endif

#ifndef __IADsSecurityDescriptor_INTERFACE_DEFINED__
#define __IADsSecurityDescriptor_INTERFACE_DEFINED__

/****************************************
 * Generated header for interface: IADsSecurityDescriptor
 * at Mon Oct 13 13:47:30 1997
 * using MIDL 3.00.44
 ****************************************/
/* [object][dual][oleautomation][uuid] */ 



EXTERN_C const IID IID_IADsSecurityDescriptor;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    interface IADsSecurityDescriptor : public IDispatch
    {
    public:
        virtual /* [id][propget] */ HRESULT STDMETHODCALLTYPE get_Revision( 
            /* [retval][out] */ long __RPC_FAR *retval) = 0;
        
        virtual /* [id][propput] */ HRESULT STDMETHODCALLTYPE put_Revision( 
            /* [in] */ long lnRevision) = 0;
        
        virtual /* [id][propget] */ HRESULT STDMETHODCALLTYPE get_Control( 
            /* [retval][out] */ long __RPC_FAR *retval) = 0;
        
        virtual /* [id][propput] */ HRESULT STDMETHODCALLTYPE put_Control( 
            /* [in] */ long lnControl) = 0;
        
        virtual /* [id][propget] */ HRESULT STDMETHODCALLTYPE get_Owner( 
            /* [retval][out] */ BSTR __RPC_FAR *retval) = 0;
        
        virtual /* [id][propput] */ HRESULT STDMETHODCALLTYPE put_Owner( 
            /* [in] */ BSTR bstrOwner) = 0;
        
        virtual /* [id][propget] */ HRESULT STDMETHODCALLTYPE get_OwnerDefaulted( 
            /* [retval][out] */ VARIANT_BOOL __RPC_FAR *retval) = 0;
        
        virtual /* [id][propput] */ HRESULT STDMETHODCALLTYPE put_OwnerDefaulted( 
            /* [in] */ VARIANT_BOOL fOwnerDefaulted) = 0;
        
        virtual /* [id][propget] */ HRESULT STDMETHODCALLTYPE get_Group( 
            /* [retval][out] */ BSTR __RPC_FAR *retval) = 0;
        
        virtual /* [id][propput] */ HRESULT STDMETHODCALLTYPE put_Group( 
            /* [in] */ BSTR bstrGroup) = 0;
        
        virtual /* [id][propget] */ HRESULT STDMETHODCALLTYPE get_GroupDefaulted( 
            /* [retval][out] */ VARIANT_BOOL __RPC_FAR *retval) = 0;
        
        virtual /* [id][propput] */ HRESULT STDMETHODCALLTYPE put_GroupDefaulted( 
            /* [in] */ VARIANT_BOOL fGroupDefaulted) = 0;
        
        virtual /* [id][propget] */ HRESULT STDMETHODCALLTYPE get_DiscretionaryAcl( 
            /* [retval][out] */ IDispatch __RPC_FAR *__RPC_FAR *retval) = 0;
        
        virtual /* [id][propput] */ HRESULT STDMETHODCALLTYPE put_DiscretionaryAcl( 
            /* [in] */ IDispatch __RPC_FAR *pDiscretionaryAcl) = 0;
        
        virtual /* [id][propget] */ HRESULT STDMETHODCALLTYPE get_DaclDefaulted( 
            /* [retval][out] */ VARIANT_BOOL __RPC_FAR *retval) = 0;
        
        virtual /* [id][propput] */ HRESULT STDMETHODCALLTYPE put_DaclDefaulted( 
            /* [in] */ VARIANT_BOOL fDaclDefaulted) = 0;
        
        virtual /* [id][propget] */ HRESULT STDMETHODCALLTYPE get_SystemAcl( 
            /* [retval][out] */ IDispatch __RPC_FAR *__RPC_FAR *retval) = 0;
        
        virtual /* [id][propput] */ HRESULT STDMETHODCALLTYPE put_SystemAcl( 
            /* [in] */ IDispatch __RPC_FAR *pSystemAcl) = 0;
        
        virtual /* [id][propget] */ HRESULT STDMETHODCALLTYPE get_SaclDefaulted( 
            /* [retval][out] */ VARIANT_BOOL __RPC_FAR *retval) = 0;
        
        virtual /* [id][propput] */ HRESULT STDMETHODCALLTYPE put_SaclDefaulted( 
            /* [in] */ VARIANT_BOOL fSaclDefaulted) = 0;
        
        virtual /* [id] */ HRESULT STDMETHODCALLTYPE CopySecurityDescriptor( 
            /* [retval][out] */ IDispatch __RPC_FAR *__RPC_FAR *ppSecurityDescriptor) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IADsSecurityDescriptorVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            IADsSecurityDescriptor __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            IADsSecurityDescriptor __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            IADsSecurityDescriptor __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfoCount )( 
            IADsSecurityDescriptor __RPC_FAR * This,
            /* [out] */ UINT __RPC_FAR *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfo )( 
            IADsSecurityDescriptor __RPC_FAR * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo __RPC_FAR *__RPC_FAR *ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetIDsOfNames )( 
            IADsSecurityDescriptor __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR __RPC_FAR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID __RPC_FAR *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Invoke )( 
            IADsSecurityDescriptor __RPC_FAR * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS __RPC_FAR *pDispParams,
            /* [out] */ VARIANT __RPC_FAR *pVarResult,
            /* [out] */ EXCEPINFO __RPC_FAR *pExcepInfo,
            /* [out] */ UINT __RPC_FAR *puArgErr);
        
        /* [id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Revision )( 
            IADsSecurityDescriptor __RPC_FAR * This,
            /* [retval][out] */ long __RPC_FAR *retval);
        
        /* [id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_Revision )( 
            IADsSecurityDescriptor __RPC_FAR * This,
            /* [in] */ long lnRevision);
        
        /* [id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Control )( 
            IADsSecurityDescriptor __RPC_FAR * This,
            /* [retval][out] */ long __RPC_FAR *retval);
        
        /* [id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_Control )( 
            IADsSecurityDescriptor __RPC_FAR * This,
            /* [in] */ long lnControl);
        
        /* [id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Owner )( 
            IADsSecurityDescriptor __RPC_FAR * This,
            /* [retval][out] */ BSTR __RPC_FAR *retval);
        
        /* [id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_Owner )( 
            IADsSecurityDescriptor __RPC_FAR * This,
            /* [in] */ BSTR bstrOwner);
        
        /* [id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_OwnerDefaulted )( 
            IADsSecurityDescriptor __RPC_FAR * This,
            /* [retval][out] */ VARIANT_BOOL __RPC_FAR *retval);
        
        /* [id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_OwnerDefaulted )( 
            IADsSecurityDescriptor __RPC_FAR * This,
            /* [in] */ VARIANT_BOOL fOwnerDefaulted);
        
        /* [id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Group )( 
            IADsSecurityDescriptor __RPC_FAR * This,
            /* [retval][out] */ BSTR __RPC_FAR *retval);
        
        /* [id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_Group )( 
            IADsSecurityDescriptor __RPC_FAR * This,
            /* [in] */ BSTR bstrGroup);
        
        /* [id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_GroupDefaulted )( 
            IADsSecurityDescriptor __RPC_FAR * This,
            /* [retval][out] */ VARIANT_BOOL __RPC_FAR *retval);
        
        /* [id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_GroupDefaulted )( 
            IADsSecurityDescriptor __RPC_FAR * This,
            /* [in] */ VARIANT_BOOL fGroupDefaulted);
        
        /* [id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_DiscretionaryAcl )( 
            IADsSecurityDescriptor __RPC_FAR * This,
            /* [retval][out] */ IDispatch __RPC_FAR *__RPC_FAR *retval);
        
        /* [id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_DiscretionaryAcl )( 
            IADsSecurityDescriptor __RPC_FAR * This,
            /* [in] */ IDispatch __RPC_FAR *pDiscretionaryAcl);
        
        /* [id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_DaclDefaulted )( 
            IADsSecurityDescriptor __RPC_FAR * This,
            /* [retval][out] */ VARIANT_BOOL __RPC_FAR *retval);
        
        /* [id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_DaclDefaulted )( 
            IADsSecurityDescriptor __RPC_FAR * This,
            /* [in] */ VARIANT_BOOL fDaclDefaulted);
        
        /* [id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_SystemAcl )( 
            IADsSecurityDescriptor __RPC_FAR * This,
            /* [retval][out] */ IDispatch __RPC_FAR *__RPC_FAR *retval);
        
        /* [id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_SystemAcl )( 
            IADsSecurityDescriptor __RPC_FAR * This,
            /* [in] */ IDispatch __RPC_FAR *pSystemAcl);
        
        /* [id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_SaclDefaulted )( 
            IADsSecurityDescriptor __RPC_FAR * This,
            /* [retval][out] */ VARIANT_BOOL __RPC_FAR *retval);
        
        /* [id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_SaclDefaulted )( 
            IADsSecurityDescriptor __RPC_FAR * This,
            /* [in] */ VARIANT_BOOL fSaclDefaulted);
        
        /* [id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *CopySecurityDescriptor )( 
            IADsSecurityDescriptor __RPC_FAR * This,
            /* [retval][out] */ IDispatch __RPC_FAR *__RPC_FAR *ppSecurityDescriptor);
        
        END_INTERFACE
    } IADsSecurityDescriptorVtbl;

    interface IADsSecurityDescriptor
    {
        CONST_VTBL struct IADsSecurityDescriptorVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IADsSecurityDescriptor_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IADsSecurityDescriptor_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IADsSecurityDescriptor_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IADsSecurityDescriptor_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define IADsSecurityDescriptor_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define IADsSecurityDescriptor_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define IADsSecurityDescriptor_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)


#define IADsSecurityDescriptor_get_Revision(This,retval)	\
    (This)->lpVtbl -> get_Revision(This,retval)

#define IADsSecurityDescriptor_put_Revision(This,lnRevision)	\
    (This)->lpVtbl -> put_Revision(This,lnRevision)

#define IADsSecurityDescriptor_get_Control(This,retval)	\
    (This)->lpVtbl -> get_Control(This,retval)

#define IADsSecurityDescriptor_put_Control(This,lnControl)	\
    (This)->lpVtbl -> put_Control(This,lnControl)

#define IADsSecurityDescriptor_get_Owner(This,retval)	\
    (This)->lpVtbl -> get_Owner(This,retval)

#define IADsSecurityDescriptor_put_Owner(This,bstrOwner)	\
    (This)->lpVtbl -> put_Owner(This,bstrOwner)

#define IADsSecurityDescriptor_get_OwnerDefaulted(This,retval)	\
    (This)->lpVtbl -> get_OwnerDefaulted(This,retval)

#define IADsSecurityDescriptor_put_OwnerDefaulted(This,fOwnerDefaulted)	\
    (This)->lpVtbl -> put_OwnerDefaulted(This,fOwnerDefaulted)

#define IADsSecurityDescriptor_get_Group(This,retval)	\
    (This)->lpVtbl -> get_Group(This,retval)

#define IADsSecurityDescriptor_put_Group(This,bstrGroup)	\
    (This)->lpVtbl -> put_Group(This,bstrGroup)

#define IADsSecurityDescriptor_get_GroupDefaulted(This,retval)	\
    (This)->lpVtbl -> get_GroupDefaulted(This,retval)

#define IADsSecurityDescriptor_put_GroupDefaulted(This,fGroupDefaulted)	\
    (This)->lpVtbl -> put_GroupDefaulted(This,fGroupDefaulted)

#define IADsSecurityDescriptor_get_DiscretionaryAcl(This,retval)	\
    (This)->lpVtbl -> get_DiscretionaryAcl(This,retval)

#define IADsSecurityDescriptor_put_DiscretionaryAcl(This,pDiscretionaryAcl)	\
    (This)->lpVtbl -> put_DiscretionaryAcl(This,pDiscretionaryAcl)

#define IADsSecurityDescriptor_get_DaclDefaulted(This,retval)	\
    (This)->lpVtbl -> get_DaclDefaulted(This,retval)

#define IADsSecurityDescriptor_put_DaclDefaulted(This,fDaclDefaulted)	\
    (This)->lpVtbl -> put_DaclDefaulted(This,fDaclDefaulted)

#define IADsSecurityDescriptor_get_SystemAcl(This,retval)	\
    (This)->lpVtbl -> get_SystemAcl(This,retval)

#define IADsSecurityDescriptor_put_SystemAcl(This,pSystemAcl)	\
    (This)->lpVtbl -> put_SystemAcl(This,pSystemAcl)

#define IADsSecurityDescriptor_get_SaclDefaulted(This,retval)	\
    (This)->lpVtbl -> get_SaclDefaulted(This,retval)

#define IADsSecurityDescriptor_put_SaclDefaulted(This,fSaclDefaulted)	\
    (This)->lpVtbl -> put_SaclDefaulted(This,fSaclDefaulted)

#define IADsSecurityDescriptor_CopySecurityDescriptor(This,ppSecurityDescriptor)	\
    (This)->lpVtbl -> CopySecurityDescriptor(This,ppSecurityDescriptor)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [id][propget] */ HRESULT STDMETHODCALLTYPE IADsSecurityDescriptor_get_Revision_Proxy( 
    IADsSecurityDescriptor __RPC_FAR * This,
    /* [retval][out] */ long __RPC_FAR *retval);


void __RPC_STUB IADsSecurityDescriptor_get_Revision_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [id][propput] */ HRESULT STDMETHODCALLTYPE IADsSecurityDescriptor_put_Revision_Proxy( 
    IADsSecurityDescriptor __RPC_FAR * This,
    /* [in] */ long lnRevision);


void __RPC_STUB IADsSecurityDescriptor_put_Revision_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [id][propget] */ HRESULT STDMETHODCALLTYPE IADsSecurityDescriptor_get_Control_Proxy( 
    IADsSecurityDescriptor __RPC_FAR * This,
    /* [retval][out] */ long __RPC_FAR *retval);


void __RPC_STUB IADsSecurityDescriptor_get_Control_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [id][propput] */ HRESULT STDMETHODCALLTYPE IADsSecurityDescriptor_put_Control_Proxy( 
    IADsSecurityDescriptor __RPC_FAR * This,
    /* [in] */ long lnControl);


void __RPC_STUB IADsSecurityDescriptor_put_Control_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [id][propget] */ HRESULT STDMETHODCALLTYPE IADsSecurityDescriptor_get_Owner_Proxy( 
    IADsSecurityDescriptor __RPC_FAR * This,
    /* [retval][out] */ BSTR __RPC_FAR *retval);


void __RPC_STUB IADsSecurityDescriptor_get_Owner_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [id][propput] */ HRESULT STDMETHODCALLTYPE IADsSecurityDescriptor_put_Owner_Proxy( 
    IADsSecurityDescriptor __RPC_FAR * This,
    /* [in] */ BSTR bstrOwner);


void __RPC_STUB IADsSecurityDescriptor_put_Owner_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [id][propget] */ HRESULT STDMETHODCALLTYPE IADsSecurityDescriptor_get_OwnerDefaulted_Proxy( 
    IADsSecurityDescriptor __RPC_FAR * This,
    /* [retval][out] */ VARIANT_BOOL __RPC_FAR *retval);


void __RPC_STUB IADsSecurityDescriptor_get_OwnerDefaulted_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [id][propput] */ HRESULT STDMETHODCALLTYPE IADsSecurityDescriptor_put_OwnerDefaulted_Proxy( 
    IADsSecurityDescriptor __RPC_FAR * This,
    /* [in] */ VARIANT_BOOL fOwnerDefaulted);


void __RPC_STUB IADsSecurityDescriptor_put_OwnerDefaulted_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [id][propget] */ HRESULT STDMETHODCALLTYPE IADsSecurityDescriptor_get_Group_Proxy( 
    IADsSecurityDescriptor __RPC_FAR * This,
    /* [retval][out] */ BSTR __RPC_FAR *retval);


void __RPC_STUB IADsSecurityDescriptor_get_Group_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [id][propput] */ HRESULT STDMETHODCALLTYPE IADsSecurityDescriptor_put_Group_Proxy( 
    IADsSecurityDescriptor __RPC_FAR * This,
    /* [in] */ BSTR bstrGroup);


void __RPC_STUB IADsSecurityDescriptor_put_Group_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [id][propget] */ HRESULT STDMETHODCALLTYPE IADsSecurityDescriptor_get_GroupDefaulted_Proxy( 
    IADsSecurityDescriptor __RPC_FAR * This,
    /* [retval][out] */ VARIANT_BOOL __RPC_FAR *retval);


void __RPC_STUB IADsSecurityDescriptor_get_GroupDefaulted_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [id][propput] */ HRESULT STDMETHODCALLTYPE IADsSecurityDescriptor_put_GroupDefaulted_Proxy( 
    IADsSecurityDescriptor __RPC_FAR * This,
    /* [in] */ VARIANT_BOOL fGroupDefaulted);


void __RPC_STUB IADsSecurityDescriptor_put_GroupDefaulted_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [id][propget] */ HRESULT STDMETHODCALLTYPE IADsSecurityDescriptor_get_DiscretionaryAcl_Proxy( 
    IADsSecurityDescriptor __RPC_FAR * This,
    /* [retval][out] */ IDispatch __RPC_FAR *__RPC_FAR *retval);


void __RPC_STUB IADsSecurityDescriptor_get_DiscretionaryAcl_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [id][propput] */ HRESULT STDMETHODCALLTYPE IADsSecurityDescriptor_put_DiscretionaryAcl_Proxy( 
    IADsSecurityDescriptor __RPC_FAR * This,
    /* [in] */ IDispatch __RPC_FAR *pDiscretionaryAcl);


void __RPC_STUB IADsSecurityDescriptor_put_DiscretionaryAcl_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [id][propget] */ HRESULT STDMETHODCALLTYPE IADsSecurityDescriptor_get_DaclDefaulted_Proxy( 
    IADsSecurityDescriptor __RPC_FAR * This,
    /* [retval][out] */ VARIANT_BOOL __RPC_FAR *retval);


void __RPC_STUB IADsSecurityDescriptor_get_DaclDefaulted_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [id][propput] */ HRESULT STDMETHODCALLTYPE IADsSecurityDescriptor_put_DaclDefaulted_Proxy( 
    IADsSecurityDescriptor __RPC_FAR * This,
    /* [in] */ VARIANT_BOOL fDaclDefaulted);


void __RPC_STUB IADsSecurityDescriptor_put_DaclDefaulted_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [id][propget] */ HRESULT STDMETHODCALLTYPE IADsSecurityDescriptor_get_SystemAcl_Proxy( 
    IADsSecurityDescriptor __RPC_FAR * This,
    /* [retval][out] */ IDispatch __RPC_FAR *__RPC_FAR *retval);


void __RPC_STUB IADsSecurityDescriptor_get_SystemAcl_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [id][propput] */ HRESULT STDMETHODCALLTYPE IADsSecurityDescriptor_put_SystemAcl_Proxy( 
    IADsSecurityDescriptor __RPC_FAR * This,
    /* [in] */ IDispatch __RPC_FAR *pSystemAcl);


void __RPC_STUB IADsSecurityDescriptor_put_SystemAcl_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [id][propget] */ HRESULT STDMETHODCALLTYPE IADsSecurityDescriptor_get_SaclDefaulted_Proxy( 
    IADsSecurityDescriptor __RPC_FAR * This,
    /* [retval][out] */ VARIANT_BOOL __RPC_FAR *retval);


void __RPC_STUB IADsSecurityDescriptor_get_SaclDefaulted_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [id][propput] */ HRESULT STDMETHODCALLTYPE IADsSecurityDescriptor_put_SaclDefaulted_Proxy( 
    IADsSecurityDescriptor __RPC_FAR * This,
    /* [in] */ VARIANT_BOOL fSaclDefaulted);


void __RPC_STUB IADsSecurityDescriptor_put_SaclDefaulted_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [id] */ HRESULT STDMETHODCALLTYPE IADsSecurityDescriptor_CopySecurityDescriptor_Proxy( 
    IADsSecurityDescriptor __RPC_FAR * This,
    /* [retval][out] */ IDispatch __RPC_FAR *__RPC_FAR *ppSecurityDescriptor);


void __RPC_STUB IADsSecurityDescriptor_CopySecurityDescriptor_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IADsSecurityDescriptor_INTERFACE_DEFINED__ */


#ifdef __cplusplus
EXTERN_C const CLSID CLSID_SecurityDescriptor;

class SecurityDescriptor;
#endif

#ifndef __IADsLargeInteger_INTERFACE_DEFINED__
#define __IADsLargeInteger_INTERFACE_DEFINED__

/****************************************
 * Generated header for interface: IADsLargeInteger
 * at Mon Oct 13 13:47:30 1997
 * using MIDL 3.00.44
 ****************************************/
/* [object][dual][oleautomation][uuid] */ 



EXTERN_C const IID IID_IADsLargeInteger;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    interface IADsLargeInteger : public IDispatch
    {
    public:
        virtual /* [id][propget] */ HRESULT STDMETHODCALLTYPE get_HighPart( 
            /* [retval][out] */ long __RPC_FAR *retval) = 0;
        
        virtual /* [id][propput] */ HRESULT STDMETHODCALLTYPE put_HighPart( 
            /* [in] */ long lnHighPart) = 0;
        
        virtual /* [id][propget] */ HRESULT STDMETHODCALLTYPE get_LowPart( 
            /* [retval][out] */ long __RPC_FAR *retval) = 0;
        
        virtual /* [id][propput] */ HRESULT STDMETHODCALLTYPE put_LowPart( 
            /* [in] */ long lnLowPart) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IADsLargeIntegerVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            IADsLargeInteger __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            IADsLargeInteger __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            IADsLargeInteger __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfoCount )( 
            IADsLargeInteger __RPC_FAR * This,
            /* [out] */ UINT __RPC_FAR *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfo )( 
            IADsLargeInteger __RPC_FAR * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo __RPC_FAR *__RPC_FAR *ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetIDsOfNames )( 
            IADsLargeInteger __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR __RPC_FAR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID __RPC_FAR *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Invoke )( 
            IADsLargeInteger __RPC_FAR * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS __RPC_FAR *pDispParams,
            /* [out] */ VARIANT __RPC_FAR *pVarResult,
            /* [out] */ EXCEPINFO __RPC_FAR *pExcepInfo,
            /* [out] */ UINT __RPC_FAR *puArgErr);
        
        /* [id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_HighPart )( 
            IADsLargeInteger __RPC_FAR * This,
            /* [retval][out] */ long __RPC_FAR *retval);
        
        /* [id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_HighPart )( 
            IADsLargeInteger __RPC_FAR * This,
            /* [in] */ long lnHighPart);
        
        /* [id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_LowPart )( 
            IADsLargeInteger __RPC_FAR * This,
            /* [retval][out] */ long __RPC_FAR *retval);
        
        /* [id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_LowPart )( 
            IADsLargeInteger __RPC_FAR * This,
            /* [in] */ long lnLowPart);
        
        END_INTERFACE
    } IADsLargeIntegerVtbl;

    interface IADsLargeInteger
    {
        CONST_VTBL struct IADsLargeIntegerVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IADsLargeInteger_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IADsLargeInteger_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IADsLargeInteger_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IADsLargeInteger_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define IADsLargeInteger_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define IADsLargeInteger_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define IADsLargeInteger_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)


#define IADsLargeInteger_get_HighPart(This,retval)	\
    (This)->lpVtbl -> get_HighPart(This,retval)

#define IADsLargeInteger_put_HighPart(This,lnHighPart)	\
    (This)->lpVtbl -> put_HighPart(This,lnHighPart)

#define IADsLargeInteger_get_LowPart(This,retval)	\
    (This)->lpVtbl -> get_LowPart(This,retval)

#define IADsLargeInteger_put_LowPart(This,lnLowPart)	\
    (This)->lpVtbl -> put_LowPart(This,lnLowPart)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [id][propget] */ HRESULT STDMETHODCALLTYPE IADsLargeInteger_get_HighPart_Proxy( 
    IADsLargeInteger __RPC_FAR * This,
    /* [retval][out] */ long __RPC_FAR *retval);


void __RPC_STUB IADsLargeInteger_get_HighPart_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [id][propput] */ HRESULT STDMETHODCALLTYPE IADsLargeInteger_put_HighPart_Proxy( 
    IADsLargeInteger __RPC_FAR * This,
    /* [in] */ long lnHighPart);


void __RPC_STUB IADsLargeInteger_put_HighPart_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [id][propget] */ HRESULT STDMETHODCALLTYPE IADsLargeInteger_get_LowPart_Proxy( 
    IADsLargeInteger __RPC_FAR * This,
    /* [retval][out] */ long __RPC_FAR *retval);


void __RPC_STUB IADsLargeInteger_get_LowPart_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [id][propput] */ HRESULT STDMETHODCALLTYPE IADsLargeInteger_put_LowPart_Proxy( 
    IADsLargeInteger __RPC_FAR * This,
    /* [in] */ long lnLowPart);


void __RPC_STUB IADsLargeInteger_put_LowPart_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IADsLargeInteger_INTERFACE_DEFINED__ */


#ifdef __cplusplus
EXTERN_C const CLSID CLSID_LargeInteger;

class LargeInteger;
#endif

#ifndef __IADsPathname_INTERFACE_DEFINED__
#define __IADsPathname_INTERFACE_DEFINED__

/****************************************
 * Generated header for interface: IADsPathname
 * at Mon Oct 13 13:47:30 1997
 * using MIDL 3.00.44
 ****************************************/
/* [object][dual][oleautomation][uuid] */ 



EXTERN_C const IID IID_IADsPathname;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    interface IADsPathname : public IDispatch
    {
    public:
        virtual HRESULT STDMETHODCALLTYPE Set( 
            /* [in] */ BSTR bstrADsPath,
            /* [in] */ long lnSetType) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE SetDisplayType( 
            /* [in] */ long lnDisplayType) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE Retrieve( 
            /* [in] */ long lnFormatType,
            /* [out] */ BSTR __RPC_FAR *pbstrADsPath) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE GetNumElements( 
            /* [out] */ long __RPC_FAR *plnNumPathElements) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE GetElement( 
            /* [in] */ long lnElementIndex,
            /* [out] */ BSTR __RPC_FAR *pbstrElement) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE AddLeafElement( 
            /* [in] */ BSTR bstrLeafElement) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE RemoveLeafElement( void) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE CopyPath( 
            /* [out] */ IDispatch __RPC_FAR *__RPC_FAR *ppAdsPath) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IADsPathnameVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            IADsPathname __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            IADsPathname __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            IADsPathname __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfoCount )( 
            IADsPathname __RPC_FAR * This,
            /* [out] */ UINT __RPC_FAR *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfo )( 
            IADsPathname __RPC_FAR * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo __RPC_FAR *__RPC_FAR *ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetIDsOfNames )( 
            IADsPathname __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR __RPC_FAR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID __RPC_FAR *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Invoke )( 
            IADsPathname __RPC_FAR * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS __RPC_FAR *pDispParams,
            /* [out] */ VARIANT __RPC_FAR *pVarResult,
            /* [out] */ EXCEPINFO __RPC_FAR *pExcepInfo,
            /* [out] */ UINT __RPC_FAR *puArgErr);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Set )( 
            IADsPathname __RPC_FAR * This,
            /* [in] */ BSTR bstrADsPath,
            /* [in] */ long lnSetType);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *SetDisplayType )( 
            IADsPathname __RPC_FAR * This,
            /* [in] */ long lnDisplayType);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Retrieve )( 
            IADsPathname __RPC_FAR * This,
            /* [in] */ long lnFormatType,
            /* [out] */ BSTR __RPC_FAR *pbstrADsPath);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetNumElements )( 
            IADsPathname __RPC_FAR * This,
            /* [out] */ long __RPC_FAR *plnNumPathElements);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetElement )( 
            IADsPathname __RPC_FAR * This,
            /* [in] */ long lnElementIndex,
            /* [out] */ BSTR __RPC_FAR *pbstrElement);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *AddLeafElement )( 
            IADsPathname __RPC_FAR * This,
            /* [in] */ BSTR bstrLeafElement);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *RemoveLeafElement )( 
            IADsPathname __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *CopyPath )( 
            IADsPathname __RPC_FAR * This,
            /* [out] */ IDispatch __RPC_FAR *__RPC_FAR *ppAdsPath);
        
        END_INTERFACE
    } IADsPathnameVtbl;

    interface IADsPathname
    {
        CONST_VTBL struct IADsPathnameVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IADsPathname_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IADsPathname_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IADsPathname_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IADsPathname_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define IADsPathname_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define IADsPathname_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define IADsPathname_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)


#define IADsPathname_Set(This,bstrADsPath,lnSetType)	\
    (This)->lpVtbl -> Set(This,bstrADsPath,lnSetType)

#define IADsPathname_SetDisplayType(This,lnDisplayType)	\
    (This)->lpVtbl -> SetDisplayType(This,lnDisplayType)

#define IADsPathname_Retrieve(This,lnFormatType,pbstrADsPath)	\
    (This)->lpVtbl -> Retrieve(This,lnFormatType,pbstrADsPath)

#define IADsPathname_GetNumElements(This,plnNumPathElements)	\
    (This)->lpVtbl -> GetNumElements(This,plnNumPathElements)

#define IADsPathname_GetElement(This,lnElementIndex,pbstrElement)	\
    (This)->lpVtbl -> GetElement(This,lnElementIndex,pbstrElement)

#define IADsPathname_AddLeafElement(This,bstrLeafElement)	\
    (This)->lpVtbl -> AddLeafElement(This,bstrLeafElement)

#define IADsPathname_RemoveLeafElement(This)	\
    (This)->lpVtbl -> RemoveLeafElement(This)

#define IADsPathname_CopyPath(This,ppAdsPath)	\
    (This)->lpVtbl -> CopyPath(This,ppAdsPath)

#endif /* COBJMACROS */


#endif 	/* C style interface */



HRESULT STDMETHODCALLTYPE IADsPathname_Set_Proxy( 
    IADsPathname __RPC_FAR * This,
    /* [in] */ BSTR bstrADsPath,
    /* [in] */ long lnSetType);


void __RPC_STUB IADsPathname_Set_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IADsPathname_SetDisplayType_Proxy( 
    IADsPathname __RPC_FAR * This,
    /* [in] */ long lnDisplayType);


void __RPC_STUB IADsPathname_SetDisplayType_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IADsPathname_Retrieve_Proxy( 
    IADsPathname __RPC_FAR * This,
    /* [in] */ long lnFormatType,
    /* [out] */ BSTR __RPC_FAR *pbstrADsPath);


void __RPC_STUB IADsPathname_Retrieve_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IADsPathname_GetNumElements_Proxy( 
    IADsPathname __RPC_FAR * This,
    /* [out] */ long __RPC_FAR *plnNumPathElements);


void __RPC_STUB IADsPathname_GetNumElements_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IADsPathname_GetElement_Proxy( 
    IADsPathname __RPC_FAR * This,
    /* [in] */ long lnElementIndex,
    /* [out] */ BSTR __RPC_FAR *pbstrElement);


void __RPC_STUB IADsPathname_GetElement_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IADsPathname_AddLeafElement_Proxy( 
    IADsPathname __RPC_FAR * This,
    /* [in] */ BSTR bstrLeafElement);


void __RPC_STUB IADsPathname_AddLeafElement_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IADsPathname_RemoveLeafElement_Proxy( 
    IADsPathname __RPC_FAR * This);


void __RPC_STUB IADsPathname_RemoveLeafElement_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IADsPathname_CopyPath_Proxy( 
    IADsPathname __RPC_FAR * This,
    /* [out] */ IDispatch __RPC_FAR *__RPC_FAR *ppAdsPath);


void __RPC_STUB IADsPathname_CopyPath_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IADsPathname_INTERFACE_DEFINED__ */


#ifdef __cplusplus
EXTERN_C const CLSID CLSID_Pathname;

class Pathname;
#endif
#endif /* __ActiveDs_LIBRARY_DEFINED__ */

/* Additional Prototypes for ALL interfaces */

/* end of Additional Prototypes */

#ifdef __cplusplus
}
#endif

#endif
