/*++s 

Copyright (c) 1996 Microsoft Corporation

Module Name:

    IntF.cpp

Abstract:

    Interface for ADS

Author:

Environment:

    User mode

Revision History :

--*/
#ifndef _INTF_H_
#define _INTF_H_

#define DECLARE_IUnknown_METHODS \
        STDMETHOD(QueryInterface)(THIS_ REFIID riid, LPVOID FAR* ppvObj) ;

#define DECLARE_IDispatch_METHODS \
        STDMETHOD(GetTypeInfoCount)(THIS_ UINT FAR* pctinfo) ; \
        \
        STDMETHOD(GetTypeInfo)(\
        THIS_ \
        UINT itinfo,\
        LCID lcid,\
        ITypeInfo FAR* FAR* pptinfo) ;\
        \
        STDMETHOD(GetIDsOfNames)( \
        THIS_ \
        REFIID riid,\
        OLECHAR FAR* FAR* rgszNames,\
        UINT cNames,\
        LCID lcid, \
        DISPID FAR* rgdispid) ;\
        \
        STDMETHOD(Invoke)(\
        THIS_\
        DISPID dispidMember,\
        REFIID riid,\
        LCID lcid,\
        WORD wFlags,\
        DISPPARAMS FAR* pdispparams,\
        VARIANT FAR* pvarResult,\
        EXCEPINFO FAR* pexcepinfo,\
        UINT FAR* puArgErr) ;

#define DECLARE_IADs_METHODS  \
        STDMETHOD(get_Name)(THIS_ BSTR FAR* retval) ;        \
        STDMETHOD(get_ADsPath)(THIS_ BSTR FAR* retval); \
        STDMETHOD(get_GUID)(THIS_ BSTR FAR* retval) ;\
        STDMETHOD(get_Class)(THIS_ BSTR FAR* retval);\
        STDMETHOD(get_Parent)(THIS_ BSTR FAR* retval);\
        STDMETHOD(get_Schema)(THIS_ BSTR FAR* retval);\
        STDMETHOD(SetInfo)(THIS) ;                           \
        STDMETHOD(GetInfo)(THIS) ; \
        STDMETHOD(Get)(THIS_ BSTR bstrName, VARIANT FAR* pvProp) ; \
        STDMETHOD(Put)(THIS_ BSTR bstrName, VARIANT vProp) ;        \
        STDMETHOD(GetEx)(THIS_ BSTR bstrName, VARIANT FAR* pvProp) ; \
        STDMETHOD(PutEx)(THIS_ long lnControlCode, BSTR bstrName, VARIANT vProp) ; \
        STDMETHOD(GetInfoEx)(THIS_ VARIANT vProperties, long lnReserved);


#define DECLARE_IADsStatus_METHODS\
    STDMETHOD(get_Code)(THIS_ long FAR* plStatusCode);\
    STDMETHOD(get_String)(THIS_ BSTR FAR* pbstrStatusString);


#define DECLARE_IADsContainer_METHODS \
        STDMETHOD(get_Count)(THIS_ long FAR* retval) ;      \
        STDMETHOD(get_Filter)(THIS_ VARIANT FAR* pVar) ;    \
        STDMETHOD(put_Filter)(THIS_ VARIANT Var) ;          \
        STDMETHOD(get_Hints)(THIS_ VARIANT FAR* pvFilter);  \
        STDMETHOD(put_Hints)(THIS_ VARIANT vHints)       ;  \
        STDMETHOD(GetObject)(THIS_ BSTR ClassName, BSTR RelativeName, IDispatch * FAR* ppObject) ;\
        STDMETHOD(get__NewEnum)(THIS_ IUnknown * FAR* retval) ; \
        STDMETHOD(Create)(THIS_ BSTR ClassName, BSTR RelativeName, IDispatch * FAR* ppObject) ;\
        STDMETHOD(Delete)(THIS_ BSTR bstrClassName, BSTR bstrRelativeName) ;\
        STDMETHOD(CopyHere)(THIS_ BSTR SourceName, BSTR NewName, IDispatch * FAR* ppObject) ;\
        STDMETHOD(MoveHere)(THIS_ BSTR SourceName, BSTR NewName, IDispatch * FAR* ppObject) ;

#define DECLARE_IADsNamespaces_METHODS \
    STDMETHOD(get_DefaultContainer)(THIS_ BSTR FAR* retval);\
    STDMETHOD(put_DefaultContainer)(THIS_ BSTR bstrDefaultContainer);

/* IADsUser methods */
#define DECLARE_IADsUser_METHODS      \
   STDMETHOD(get_BadLoginAddress)(THIS_ BSTR FAR* retval) ;\
    STDMETHOD(get_BadLoginCount)(THIS_ long FAR* retval) ;\
    STDMETHOD(get_LastLogin)(THIS_ DATE FAR* retval) ;\
    STDMETHOD(get_LastLogoff)(THIS_ DATE FAR* retval) ;\
    STDMETHOD(get_LastFailedLogin)(THIS_ DATE FAR* retval) ;\
    STDMETHOD(get_PasswordLastChanged)(THIS_ DATE FAR* retval) ;\
    STDMETHOD(get_Description)(THIS_ BSTR FAR* retval) ;\
    STDMETHOD(put_Description)(THIS_ BSTR bstrDescription) ;\
    STDMETHOD(get_Division)(THIS_ BSTR FAR* retval) ;\
    STDMETHOD(put_Division)(THIS_ BSTR bstrDivision) ;\
    STDMETHOD(get_Department)(THIS_ BSTR FAR* retval) ;\
    STDMETHOD(put_Department)(THIS_ BSTR bstrDepartment) ;\
    STDMETHOD(get_EmployeeID)(THIS_ BSTR FAR* retval) ;\
    STDMETHOD(put_EmployeeID)(THIS_ BSTR bstrEmployeeID) ;\
    STDMETHOD(get_FullName)(THIS_ BSTR FAR* retval) ;\
    STDMETHOD(put_FullName)(THIS_ BSTR bstrFullName) ;\
    STDMETHOD(get_FirstName)(THIS_ BSTR FAR* retval) ;\
    STDMETHOD(put_FirstName)(THIS_ BSTR bstrFirstName) ;\
    STDMETHOD(get_LastName)(THIS_ BSTR FAR* retval) ;\
    STDMETHOD(put_LastName)(THIS_ BSTR bstrLastName) ;\
    STDMETHOD(get_OtherName)(THIS_ BSTR FAR* retval) ;\
    STDMETHOD(put_OtherName)(THIS_ BSTR bstrOtherName) ;\
    STDMETHOD(get_NamePrefix)(THIS_ BSTR FAR* retval) ;\
    STDMETHOD(put_NamePrefix)(THIS_ BSTR bstrNamePrefix) ;\
    STDMETHOD(get_NameSuffix)(THIS_ BSTR FAR* retval) ;\
    STDMETHOD(put_NameSuffix)(THIS_ BSTR bstrNameSuffix) ;\
    STDMETHOD(get_Title)(THIS_ BSTR FAR* retval) ;\
    STDMETHOD(put_Title)(THIS_ BSTR bstrTitle) ;\
    STDMETHOD(get_Manager)(THIS_ BSTR FAR* retval) ;\
    STDMETHOD(put_Manager)(THIS_ BSTR bstrManager) ;\
    STDMETHOD(get_TelephoneNumber)(THIS_ VARIANT FAR* retval) ;\
    STDMETHOD(put_TelephoneNumber)(THIS_ VARIANT vTelephoneNumber) ;\
    STDMETHOD(get_TelephoneHome)(THIS_ VARIANT FAR* retval) ;\
    STDMETHOD(put_TelephoneHome)(THIS_ VARIANT vTelephoneHome );\
    STDMETHOD(get_TelephoneMobile)(THIS_ VARIANT FAR* retval) ;\
    STDMETHOD(put_TelephoneMobile)(THIS_ VARIANT vTelephoneMobile) ;\
    STDMETHOD(get_TelephonePager)(THIS_ VARIANT FAR* retval) ;\
    STDMETHOD(put_TelephonePager)(THIS_ VARIANT vTelephonePager) ;\
    STDMETHOD(get_FaxNumber)(THIS_ VARIANT FAR* retval) ;\
    STDMETHOD(put_FaxNumber)(THIS_ VARIANT vFaxNumber) ;\
    STDMETHOD(get_OfficeLocations)(THIS_ VARIANT FAR* retval) ;\
    STDMETHOD(put_OfficeLocations)(THIS_ VARIANT vOfficeLocation) ;\
    STDMETHOD(get_PostalAddresses)(THIS_ VARIANT FAR* retval) ;\
    STDMETHOD(put_PostalAddresses)(THIS_ VARIANT vPostalAddresses) ;\
    STDMETHOD(get_PostalCodes)(THIS_ VARIANT FAR* retval) ;\
    STDMETHOD(put_PostalCodes)(THIS_ VARIANT vPostalCodes) ;\
    STDMETHOD(get_SeeAlso)(THIS_ VARIANT FAR* retval) ;\
    STDMETHOD(put_SeeAlso)(THIS_ VARIANT vSeeAlso) ;\
    STDMETHOD(get_AccountDisabled)(THIS_ VARIANT_BOOL FAR* retval) ;\
    STDMETHOD(put_AccountDisabled)(THIS_ VARIANT_BOOL fAccountDisabled) ;\
    STDMETHOD(get_AccountExpirationDate)(THIS_ DATE FAR* retval) ;\
    STDMETHOD(put_AccountExpirationDate)(THIS_ DATE daAccountExpirationDate) ;\
    STDMETHOD(get_GraceLoginsAllowed)(THIS_ long FAR* retval) ;\
    STDMETHOD(put_GraceLoginsAllowed)(THIS_ long lnGraceLoginsAllowed) ;\
    STDMETHOD(get_GraceLoginsRemaining)(THIS_ long FAR* retval) ;\
    STDMETHOD(put_GraceLoginsRemaining)(THIS_ long lnGraceLoginsRemaining) ;\
    STDMETHOD(get_IsAccountLocked)(THIS_ VARIANT_BOOL FAR* retval) ;\
    STDMETHOD(put_IsAccountLocked)(THIS_ VARIANT_BOOL fIsAccountLocked) ;\
    STDMETHOD(get_LoginHours)(THIS_ VARIANT FAR* retval) ;\
    STDMETHOD(put_LoginHours)(THIS_ VARIANT vLoginHours) ;\
    STDMETHOD(get_LoginWorkstations)(THIS_ VARIANT FAR* retval) ;\
    STDMETHOD(put_LoginWorkstations)(THIS_ VARIANT vLoginWorkstations) ;\
    STDMETHOD(get_MaxLogins)(THIS_ long FAR* retval) ;\
    STDMETHOD(put_MaxLogins)(THIS_ long lnMaxLogins) ;\
    STDMETHOD(get_MaxStorage)(THIS_ long FAR* retval) ;\
    STDMETHOD(put_MaxStorage)(THIS_ long lnMaxStorage) ;\
    STDMETHOD(get_PasswordExpirationDate)(THIS_ DATE FAR* retval) ;\
    STDMETHOD(put_PasswordExpirationDate)(THIS_ DATE daPasswordExpirationDate) ;\
    STDMETHOD(get_PasswordMinimumLength)(THIS_ long FAR* retval) ;\
    STDMETHOD(put_PasswordMinimumLength)(THIS_ long lnPasswordMinimumLength) ;\
    STDMETHOD(get_PasswordRequired)(THIS_ VARIANT_BOOL FAR* retval) ;\
    STDMETHOD(put_PasswordRequired)(THIS_ VARIANT_BOOL fPasswordRequired) ;\
    STDMETHOD(get_RequireUniquePassword)(THIS_ VARIANT_BOOL FAR* retval) ;\
    STDMETHOD(put_RequireUniquePassword)(THIS_ VARIANT_BOOL fRequireUniquePassword) ;\
    STDMETHOD(get_EmailAddress)(THIS_ BSTR FAR* retval) ;\
    STDMETHOD(put_EmailAddress)(THIS_ BSTR bstrEmailAddress) ;\
    STDMETHOD(get_HomeDirectory)(THIS_ BSTR FAR* retval) ;\
    STDMETHOD(put_HomeDirectory)(THIS_ BSTR bstrHomeDirectory) ;\
    STDMETHOD(get_Languages)(THIS_ VARIANT FAR* retval) ;\
    STDMETHOD(put_Languages)(THIS_ VARIANT vLanguages) ;\
    STDMETHOD(get_Profile)(THIS_ BSTR FAR* retval) ;\
    STDMETHOD(put_Profile)(THIS_ BSTR bstrProfile) ;\
    STDMETHOD(get_LoginScript)(THIS_ BSTR FAR* retval) ;\
    STDMETHOD(put_LoginScript)(THIS_ BSTR bstrLoginScript) ;\
    STDMETHOD(get_Picture)(THIS_ VARIANT FAR* retval) ;\
    STDMETHOD(put_Picture)(THIS_ VARIANT vPicture) ;\
    STDMETHOD(get_HomePage)(THIS_ BSTR FAR* retval) ;\
    STDMETHOD(put_HomePage)(THIS_ BSTR bstrHomePage) ;\
    STDMETHOD(Groups)(THIS_ IADsMembers FAR* FAR* ppGroups) ;\
    STDMETHOD(SetPassword)(THIS_ BSTR NewPassword) ;\
    STDMETHOD(ChangePassword)(THIS_ BSTR bstrOldPassword, BSTR bstrNewPassword) ;\


/* IADsDomain methods */
#define DECLARE_IADsDomain_METHODS \
        STDMETHOD(get_MinPasswordLength)(THIS_ long FAR* retval) ;\
        STDMETHOD(put_MinPasswordLength)(THIS_ long lnMinPasswordLength) ;\
        STDMETHOD(get_MinPasswordAge)(THIS_ long FAR* retval) ;\
        STDMETHOD(put_MinPasswordAge)(THIS_ long lnMinPasswordAge) ;\
        STDMETHOD(get_MaxPasswordAge)(THIS_ long FAR* retval) ;\
        STDMETHOD(put_MaxPasswordAge)(THIS_ long lnMaxPasswordAge) ;\
        STDMETHOD(get_MaxBadPasswordsAllowed)(THIS_ long FAR* retval) ;\
        STDMETHOD(put_MaxBadPasswordsAllowed)(THIS_ long lnMaxBadPasswordsAllowed) ;\
        STDMETHOD(get_PasswordHistoryLength)(THIS_ long FAR* retval) ;\
        STDMETHOD(put_PasswordHistoryLength)(THIS_ long lnPasswordHistoryLength) ;\
        STDMETHOD(get_PasswordAttributes)(THIS_ long FAR* retval) ;\
        STDMETHOD(put_PasswordAttributes)(THIS_ long lnPasswordAttributes) ;\
        STDMETHOD(get_AutoUnlockInterval)(THIS_ long FAR* retval) ;\
        STDMETHOD(put_AutoUnlockInterval)(THIS_ long lnAutoUnlockInterval) ;\
        STDMETHOD(get_LockoutObservationInterval)(THIS_ long FAR* retval) ;\
        STDMETHOD(put_LockoutObservationInterval)(THIS_ long lnLockoutObservationInterval) ;\
        STDMETHOD(get_IsWorkgroup)(THIS_ VARIANT_BOOL FAR* retval);


/* IADsComputer methods */
#define DECLARE_IADsComputer_METHODS \
        STDMETHOD(get_ComputerID)(THIS_ BSTR FAR* retval) ; \
        STDMETHOD(get_Site)(THIS_ BSTR FAR* retval) ; \
        STDMETHOD(get_Description)(THIS_ BSTR FAR* retval) ; \
        STDMETHOD(put_Description)(THIS_ BSTR bstrDescription) ; \
        STDMETHOD(get_Location)(THIS_ BSTR FAR* retval) ; \
        STDMETHOD(put_Location)(THIS_ BSTR bstrLocation) ; \
        STDMETHOD(get_PrimaryUser)(THIS_ BSTR FAR* retval) ;\
        STDMETHOD(put_PrimaryUser)(THIS_ BSTR bstrPrimaryUser) ;\
        STDMETHOD(get_Owner)(THIS_ BSTR FAR* retval) ;\
        STDMETHOD(put_Owner)(THIS_ BSTR bstrOwner) ;\
        STDMETHOD(get_Division)(THIS_ BSTR FAR* retval) ; \
        STDMETHOD(put_Division)(THIS_ BSTR bstrDivision) ; \
        STDMETHOD(get_Department)(THIS_ BSTR FAR* retval) ; \
        STDMETHOD(put_Department)(THIS_ BSTR bstrDepartment) ; \
        STDMETHOD(get_Role)(THIS_ BSTR FAR* retval) ; \
        STDMETHOD(put_Role)(THIS_ BSTR bstrRole) ; \
        STDMETHOD(get_OperatingSystem)(THIS_ BSTR FAR* retval); \
        STDMETHOD(put_OperatingSystem)(THIS_ BSTR bstrOperatingSystem); \
        STDMETHOD(get_OperatingSystemVersion)(THIS_ BSTR FAR* retval); \
        STDMETHOD(put_OperatingSystemVersion)(THIS_ BSTR bstrOperatingSystemVersion); \
        STDMETHOD(get_Model)(THIS_ BSTR FAR* retval) ; \
        STDMETHOD(put_Model)(THIS_ BSTR bstrModel) ; \
        STDMETHOD(get_Processor)(THIS_ BSTR FAR* retval) ; \
        STDMETHOD(put_Processor)(THIS_ BSTR bstrProcessor) ; \
        STDMETHOD(get_ProcessorCount)(THIS_ BSTR FAR* retval) ; \
        STDMETHOD(put_ProcessorCount)(THIS_ BSTR bstrProcessorCount) ; \
        STDMETHOD(get_MemorySize)(THIS_ BSTR FAR* retval) ; \
        STDMETHOD(put_MemorySize)(THIS_ BSTR bstrMemorySize) ; \
        STDMETHOD(get_StorageCapacity)(THIS_ BSTR FAR* retval) ; \
        STDMETHOD(put_StorageCapacity)(THIS_ BSTR bstrStorageCapacity); \
        STDMETHOD(get_NetAddresses)(THIS_ VARIANT FAR* retval); \
        STDMETHOD(put_NetAddresses)(THIS_ VARIANT vNetAddresses);


#define DECLARE_IADsComputerOperations_METHODS \
        STDMETHOD(Status)(THIS_ IDispatch * FAR* ppObject) ; \
        STDMETHOD(Shutdown)(THIS_ VARIANT_BOOL bReboot) ;


#define DECLARE_IADsGroup_METHODS \
        STDMETHOD(get_Description)(THIS_ BSTR FAR* retval) ; \
        STDMETHOD(put_Description)(THIS_ BSTR bstrDescription) ; \
        STDMETHOD(Members)(THIS_ IADsMembers FAR* FAR* ppMembers) ; \
        STDMETHOD(IsMember)(THIS_ BSTR bstrMember, VARIANT_BOOL FAR* bMember) ;\
        STDMETHOD(Add)(THIS_ BSTR bstrNewItem) ;\
        STDMETHOD(Remove)(THIS_ BSTR bstrItemToBeRemoved) ;

#define DECLARE_IADsMembers_METHODS \
        STDMETHOD(get_Count)(THIS_ long FAR* plCount) ;\
        STDMETHOD(get__NewEnum)(THIS_ IUnknown * FAR* ppEnumerator) ;\
        STDMETHOD(get_Filter)(THIS_ VARIANT FAR* pvFilter) ;\
        STDMETHOD(put_Filter)(THIS_ VARIANT pvFilter) ;\



#define DECLARE_IADsPrintQueue_METHODS \
    STDMETHOD(get_Model)(THIS_ BSTR FAR* retval) ;\
    STDMETHOD(put_Model)(THIS_ BSTR bstrModel) ;\
    STDMETHOD(get_Datatype)(THIS_ BSTR FAR* retval) ;\
    STDMETHOD(put_Datatype)(THIS_ BSTR bstrDatatype) ;\
    STDMETHOD(get_Description)(THIS_ BSTR FAR* retval) ;\
    STDMETHOD(put_Description)(THIS_ BSTR bstrDescription) ;\
    STDMETHOD(get_Location)(THIS_ BSTR FAR* retval) ;\
    STDMETHOD(put_Location)(THIS_ BSTR bstrLocation) ;\
    STDMETHOD(get_Priority)(THIS_ long FAR* retval) ;\
    STDMETHOD(put_Priority)(THIS_ long lnPriority) ;\
    STDMETHOD(get_StartTime)(THIS_ DATE FAR* retval) ;\
    STDMETHOD(put_StartTime)(THIS_ DATE daStartTime) ;\
    STDMETHOD(get_UntilTime)(THIS_ DATE FAR* retval) ;\
    STDMETHOD(put_UntilTime)(THIS_ DATE daUntilTime) ;\
    STDMETHOD(get_DefaultJobPriority)(THIS_ long FAR* retval) ;\
    STDMETHOD(put_DefaultJobPriority)(THIS_ long lnDefaultJobPriority) ;\
    STDMETHOD(get_BannerPage)(THIS_ BSTR FAR* retval) ;\
    STDMETHOD(put_BannerPage)(THIS_ BSTR bstrBannerPage) ;\
    STDMETHOD(get_PrinterPath)(THIS_ BSTR FAR* retval) ;\
    STDMETHOD(put_PrinterPath)(THIS_ BSTR bstrHostComputer) ;\
    STDMETHOD(get_PrintProcessor)(THIS_ BSTR FAR* retval);\
    STDMETHOD(put_PrintProcessor)(THIS_ BSTR bstrPrintProcessor);\
    STDMETHOD(get_PrintDevices)(THIS_ VARIANT FAR* retval);\
    STDMETHOD(put_PrintDevices)(THIS_ VARIANT vPorts);\
    STDMETHOD(get_NetAddresses)(THIS_ VARIANT FAR* retval);\
    STDMETHOD(put_NetAddresses)(THIS_ VARIANT vNetAddresses);\

#define DECLARE_IADsPrintQueueOperations_METHODS \
    STDMETHOD(get_Status)(THIS_ long FAR* retval) ;\
    STDMETHOD(PrintJobs)(THIS_ IADsCollection * FAR* ppObject) ;\
    STDMETHOD(Pause)(THIS) ;\
    STDMETHOD(Resume)(THIS) ;\
    STDMETHOD(Purge)(THIS) ;


#define DECLARE_IADsPrintJob_METHODS \
    STDMETHOD(get_HostPrintQueue)(THIS_ BSTR FAR* retval) ;\
    STDMETHOD(get_User)(THIS_ BSTR FAR* retval) ;\
    STDMETHOD(get_UserPath)(THIS_ BSTR FAR* retval);\
    STDMETHOD(get_Size)(THIS_ long FAR* retval) ;\
    STDMETHOD(get_TimeSubmitted)(THIS_ DATE FAR* retval) ;\
    STDMETHOD(get_TotalPages)(THIS_ long FAR* retval) ;\
    STDMETHOD(get_Description)(THIS_ BSTR FAR* retval) ;\
    STDMETHOD(put_Description)(THIS_ BSTR bstrDescription) ;\
    STDMETHOD(get_Priority)(THIS_ long FAR* retval) ;\
    STDMETHOD(put_Priority)(THIS_ long lnPriority) ;\
    STDMETHOD(get_StartTime)(THIS_ DATE FAR* retval) ;\
    STDMETHOD(put_StartTime)(THIS_ DATE daStartTime) ;\
    STDMETHOD(get_UntilTime)(THIS_ DATE FAR* retval) ;\
    STDMETHOD(put_UntilTime)(THIS_ DATE daUntilTime) ;\
    STDMETHOD(get_Notify)(THIS_ BSTR FAR* retval) ;\
    STDMETHOD(put_Notify)(THIS_ BSTR bstrNotify) ;\
    STDMETHOD(get_NotifyPath)(THIS_ BSTR FAR* retval);\
    STDMETHOD(put_NotifyPath)(THIS_ BSTR bstrNotifyPath);\

#define DECLARE_IADsPrintJobOperations_METHODS \
    STDMETHOD(get_Position)(THIS_ long FAR* retval) ;\
    STDMETHOD(put_Position)(THIS_ long lnPosition) ;\
    STDMETHOD(get_TimeElapsed)(THIS_ long FAR* retval) ;\
    STDMETHOD(get_PagesPrinted)(THIS_ long FAR* retval) ;\
    STDMETHOD(get_Status)(THIS_ long FAR* retval) ;\
    STDMETHOD(Pause)(THIS) ;\
    STDMETHOD(Resume)(THIS) ;\
    STDMETHOD(Remove)(THIS) ;

#define DECLARE_IADsCollection_METHODS \
    STDMETHOD(get__NewEnum)(THIS_ IUnknown * FAR* ppEnumerator) ;\
    STDMETHOD(GetObject)(THIS_ BSTR bstrName, VARIANT FAR* pvItem);\
    STDMETHOD(Add)(THIS_ BSTR bstrName, VARIANT vItem);\
    STDMETHOD(Remove)(THIS_ BSTR bstrItemToBeRemoved);


#define DECLARE_IEnumVARIANT_METHODS \
    STDMETHOD(Next)(ULONG cElements, \
                    VARIANT FAR* pvar,\
                    ULONG FAR* pcElementFetched);\
    STDMETHOD(Skip)(ULONG cElements);\
    STDMETHOD(Reset)();\
    STDMETHOD(Clone)(IEnumVARIANT FAR* FAR* ppenum);


#define DECLARE_IADsService_METHODS \
    STDMETHOD(get_HostComputer)(THIS_ BSTR FAR* pbstrHostComputer) ;\
    STDMETHOD(put_HostComputer)(THIS_ BSTR bstrHostComputer) ;\
    STDMETHOD(get_DisplayName)(THIS_ BSTR FAR* pbstrDisplayName) ;\
    STDMETHOD(put_DisplayName)(THIS_ BSTR bstrDisplayName) ;\
    STDMETHOD(get_Version)(THIS_ BSTR FAR* pbstrVersion) ;\
    STDMETHOD(put_Version)(THIS_ BSTR bstrVersion) ;\
    STDMETHOD(get_ServiceType)(THIS_ long FAR* plServiceType) ;\
    STDMETHOD(put_ServiceType)(THIS_ long lServiceType) ;\
    STDMETHOD(get_StartType)(THIS_ long FAR* plStartType) ;\
    STDMETHOD(put_StartType)(THIS_ long lStartType) ;\
    STDMETHOD(get_Path)(THIS_ BSTR FAR* pbstrPath) ;\
    STDMETHOD(put_Path)(THIS_ BSTR bstrPath) ;\
    STDMETHOD(get_StartupParameters)(THIS_ BSTR FAR* pbstrStartupParameters) ;\
    STDMETHOD(put_StartupParameters)(THIS_ BSTR bstrStartupParameters) ;\
    STDMETHOD(get_ErrorControl)(THIS_ long FAR* plErrorControl) ;\
    STDMETHOD(put_ErrorControl)(THIS_ long lErrorControl) ;\
    STDMETHOD(get_LoadOrderGroup)(THIS_ BSTR FAR* pbstrLoadOrderGroup) ;\
    STDMETHOD(put_LoadOrderGroup)(THIS_ BSTR bstrLoadOrderGroup) ;\
    STDMETHOD(get_ServiceAccountName)(THIS_ BSTR FAR* pbstrServiceAccountName) ;\
    STDMETHOD(put_ServiceAccountName)(THIS_ BSTR bstrServiceAccountName) ;\
    STDMETHOD(get_ServiceAccountPath)(THIS_ BSTR FAR* retval);\
    STDMETHOD(put_ServiceAccountPath)(THIS_ BSTR bstrServiceAccountPath);\
    STDMETHOD(get_Dependencies)(THIS_ VARIANT FAR* pv);\
    STDMETHOD(put_Dependencies)(THIS_ VARIANT v); \


#define  DECLARE_IADsServiceOperations_METHODS \
    STDMETHOD(get_Status)(THIS_ long FAR* retval) ;\
    STDMETHOD(SetPassword)(THIS_ BSTR bstrNewPassword) ;\
    STDMETHOD(Start)(THIS) ;\
    STDMETHOD(Stop)(THIS) ;\
    STDMETHOD(Pause)(THIS) ;\
    STDMETHOD(Continue)(THIS) ;

#define  DECLARE_IADsFileService_METHODS \
    STDMETHOD(get_Description)(THIS_ BSTR FAR* pbstrDescription) ;\
    STDMETHOD(put_Description)(THIS_ BSTR bstrDescription) ;\
    STDMETHOD(get_MaxUserCount)(THIS_ long FAR* plMaxUserCount) ;\
    STDMETHOD(put_MaxUserCount)(THIS_ long lMaxUserCount) ;

#define  DECLARE_IADsFileServiceOperations_METHODS \
    STDMETHOD(Sessions)(THIS_ IADsCollection FAR* FAR* ppSessions) ;\
    STDMETHOD(Resources)(THIS_ IADsCollection FAR* FAR* ppResources) ;


#define  DECLARE_IADsSession_METHODS \
    STDMETHOD(get_User)(THIS_ BSTR FAR* retval) ;\
    STDMETHOD(get_UserPath)(THIS_ BSTR FAR* retval);\
    STDMETHOD(get_Computer)(THIS_ BSTR FAR* retval) ;\
    STDMETHOD(get_ComputerPath)(THIS_ BSTR FAR* retval);\
    STDMETHOD(get_ConnectTime)(THIS_ LONG FAR* retval) ;\
    STDMETHOD(get_IdleTime)(THIS_ LONG FAR* retval) ;


#define  DECLARE_IADsFileShare_METHODS \
    STDMETHOD(get_CurrentUserCount)(THIS_ LONG FAR* retval) ;\
    STDMETHOD(get_Description)(THIS_ BSTR FAR* retval) ;\
    STDMETHOD(put_Description)(THIS_ BSTR bstrDescription) ;\
    STDMETHOD(get_HostComputer)(THIS_ BSTR FAR* retval) ;\
    STDMETHOD(put_HostComputer)(THIS_ BSTR bstrHostComputer) ;\
    STDMETHOD(get_Path)(THIS_ BSTR FAR* retval) ;\
    STDMETHOD(put_Path)(THIS_ BSTR bstrPath) ;\
    STDMETHOD(get_MaxUserCount)(THIS_ LONG FAR* retval) ;\
    STDMETHOD(put_MaxUserCount)(THIS_ LONG  lMaxUserCount) ;

#define DECLARE_IADsResource_METHODS \
    STDMETHOD(get_User)(THIS_ BSTR FAR* retval) ;\
    STDMETHOD(get_UserPath)(THIS_ BSTR FAR* retval);\
    STDMETHOD(get_Path)(THIS_ BSTR FAR* retval) ;\
    STDMETHOD(get_LockCount)(THIS_ long FAR* retval) ;


#define DECLARE_IADsClass_METHODS \
        STDMETHOD(get_PrimaryInterface)(THIS_ BSTR FAR* pbstrGUID) ;\
        STDMETHOD(get_CLSID)(THIS_ BSTR FAR* pbstrCLSID) ;\
        STDMETHOD(put_CLSID)(THIS_ BSTR bstrCLSID) ;\
        STDMETHOD(get_OID)(THIS_ BSTR FAR* pbstrOID) ;\
        STDMETHOD(put_OID)(THIS_ BSTR bstrOID) ;\
        STDMETHOD(get_Abstract)(THIS_ VARIANT_BOOL FAR* pfAbstract) ;\
        STDMETHOD(put_Abstract)(THIS_ VARIANT_BOOL fAbstract) ;\
        STDMETHOD(get_Auxiliary)(THIS_ VARIANT_BOOL FAR* pfAuxiliary) ;\
        STDMETHOD(put_Auxiliary)(THIS_ VARIANT_BOOL fAuxiliary) ;\
        STDMETHOD(get_MandatoryProperties)(THIS_ VARIANT FAR* pvMandatoryProperties) ;\
        STDMETHOD(put_MandatoryProperties)(THIS_ VARIANT vMandatoryProperties) ;\
        STDMETHOD(get_OptionalProperties)(THIS_ VARIANT FAR* pvOptionalProperties) ;\
        STDMETHOD(put_OptionalProperties)(THIS_ VARIANT vOptionalProperties) ;\
        STDMETHOD(get_NamingProperties)(THIS_ VARIANT FAR* pvNamingProperties);\
        STDMETHOD(put_NamingProperties)(THIS_ VARIANT vNamingProperties) ;\
        STDMETHOD(get_DerivedFrom)(THIS_ VARIANT FAR* pvDerivedFrom) ;\
        STDMETHOD(put_DerivedFrom)(THIS_ VARIANT vDerivedFrom) ;\
        STDMETHOD(get_AuxDerivedFrom)(THIS_ VARIANT FAR* pvAuxDerivedFrom) ;\
        STDMETHOD(put_AuxDerivedFrom)(THIS_ VARIANT vAuxDerivedFrom) ;\
        STDMETHOD(get_PossibleSuperiors)(THIS_ VARIANT FAR* pvPossSuperiors);\
        STDMETHOD(put_PossibleSuperiors)(THIS_ VARIANT vPossSuperiors) ;\
        STDMETHOD(get_Containment)(THIS_ VARIANT FAR* pvContainment);\
        STDMETHOD(put_Containment)(THIS_ VARIANT vContainment) ;\
        STDMETHOD(get_Container)(THIS_ VARIANT_BOOL FAR* pfContainer);\
        STDMETHOD(put_Container)(THIS_ VARIANT_BOOL fContainer) ;\
        STDMETHOD(get_HelpFileName)(THIS_ BSTR FAR* pbstrHelpfile) ;\
        STDMETHOD(put_HelpFileName)(THIS_ BSTR bstrHelpfile) ;\
        STDMETHOD(get_HelpFileContext)(THIS_ long FAR* plHelpContext) ;\
        STDMETHOD(put_HelpFileContext)(THIS_ long lHelpContext) ; \
        STDMETHOD(Qualifiers)(THIS_ IADsCollection FAR* FAR* ppQualifiers) ;


#define DECLARE_IADsProperty_METHODS \
        STDMETHOD(get_OID)(THIS_ BSTR FAR* pbstrOID) ;\
        STDMETHOD(put_OID)(THIS_ BSTR bstrOID) ;\
        STDMETHOD(get_Syntax)(THIS_ BSTR FAR* pbstrSyntax) ;\
        STDMETHOD(put_Syntax)(THIS_ BSTR bstrSyntax) ;\
        STDMETHOD(get_MaxRange)(THIS_ long FAR* plMaxRange) ;\
        STDMETHOD(put_MaxRange)(THIS_ long lMaxRange) ;\
        STDMETHOD(get_MinRange)(THIS_ long FAR* plMinRange) ;\
        STDMETHOD(put_MinRange)(THIS_ long lMinRange) ;\
        STDMETHOD(get_MultiValued)(THIS_ VARIANT_BOOL FAR* pfMultiValued) ;\
        STDMETHOD(put_MultiValued)(THIS_ VARIANT_BOOL fMultiValued) ;\
        STDMETHOD(Qualifiers)(THIS_ IADsCollection FAR* FAR* ppQualifiers) ;

#define DECLARE_IADsSyntax_METHODS \
        STDMETHOD(get_OleAutoDataType)(THIS_ long FAR* plOleAutoDataType) ;\
        STDMETHOD(put_OleAutoDataType)(THIS_ long lOleAutoDataType) ;

#define DECLARE_IADsLocality_METHODS \
        STDMETHOD(get_Description)(THIS_ BSTR FAR* retval) ;\
        STDMETHOD(put_Description)(THIS_ BSTR bstrDescription) ;\
        STDMETHOD(get_LocalityName)(THIS_ BSTR FAR* retval) ;\
        STDMETHOD(put_LocalityName)(THIS_ BSTR bstrLocalityName) ;\
        STDMETHOD(get_PostalAddress)(THIS_ BSTR FAR* retval) ;\
        STDMETHOD(put_PostalAddress)(THIS_ BSTR bstrPostalAddress) ;\
        STDMETHOD(get_SeeAlso)(THIS_ VARIANT FAR* retval) ;\
        STDMETHOD(put_SeeAlso)(THIS_ VARIANT vSeeAlso) ;


#define DECLARE_IADsO_METHODS \
        STDMETHOD(get_Description)(THIS_ BSTR FAR* retval) ;\
        STDMETHOD(put_Description)(THIS_ BSTR bstrDescription) ;\
        STDMETHOD(get_LocalityName)(THIS_ BSTR FAR* retval) ;\
        STDMETHOD(put_LocalityName)(THIS_ BSTR bstrLocalityName) ;\
        STDMETHOD(get_PostalAddress)(THIS_ BSTR FAR* retval) ;\
        STDMETHOD(put_PostalAddress)(THIS_ BSTR bstrPostalAddress) ;\
        STDMETHOD(get_TelephoneNumber)(THIS_ BSTR FAR* retval) ;\
        STDMETHOD(put_TelephoneNumber)(THIS_ BSTR bstrTelephoneNumber) ;\
        STDMETHOD(get_FaxNumber)(THIS_ BSTR FAR* retval) ;\
        STDMETHOD(put_FaxNumber)(THIS_ BSTR bstrFaxNumber) ;\
        STDMETHOD(get_SeeAlso)(THIS_ VARIANT FAR* retval) ;\
        STDMETHOD(put_SeeAlso)(THIS_ VARIANT vSeeAlso) ;

#define DECLARE_IADsOU_METHODS \
        STDMETHOD(get_Description)(THIS_ BSTR FAR* retval) ;\
        STDMETHOD(put_Description)(THIS_ BSTR bstrDescription) ;\
        STDMETHOD(get_LocalityName)(THIS_ BSTR FAR* retval) ;\
        STDMETHOD(put_LocalityName)(THIS_ BSTR bstrLocalityName) ;\
        STDMETHOD(get_PostalAddress)(THIS_ BSTR FAR* retval) ;\
        STDMETHOD(put_PostalAddress)(THIS_ BSTR bstrPostalAddress) ;\
        STDMETHOD(get_TelephoneNumber)(THIS_ BSTR FAR* retval) ;\
        STDMETHOD(put_TelephoneNumber)(THIS_ BSTR bstrTelephoneNumber) ;\
        STDMETHOD(get_FaxNumber)(THIS_ BSTR FAR* retval) ;\
        STDMETHOD(put_FaxNumber)(THIS_ BSTR bstrFaxNumber) ;\
        STDMETHOD(get_SeeAlso)(THIS_ VARIANT FAR* retval) ;\
        STDMETHOD(put_SeeAlso)(THIS_ VARIANT vSeeAlso) ;\
        STDMETHOD(get_BusinessCategory)(THIS_ BSTR FAR* retval) ;\
        STDMETHOD(put_BusinessCategory)(THIS_ BSTR bstrBusinessCategory) ;

#define DECLARE_IDSNamespace_METHODS \
        STDMETHOD(OpenDSObject)(     \
            THIS_ LPWSTR lpszDNName, \
            LPWSTR lpszUserName,     \
            LPWSTR lpszPassword,     \
            REFIID riid,             \
            void * * ppADsObj      \
            );

#endif

