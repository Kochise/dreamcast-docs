#ifdef WIN32

#ifdef UNICODE
    #define FROM_OLE_STRING(str) str
    #define TO_OLE_STRING(str) str 
#else
    #define FROM_OLE_STRING(str) ConvertToAnsi(str)
    char FAR* ConvertToAnsi(OLECHAR FAR* szW);  
    #define TO_OLE_STRING(str) ConvertToUnicode(str)
    OLECHAR FAR* ConvertToUnicode(char FAR* szA);   
    // Maximum length of string that can be converted between Ansi & Unicode
    #define STRCONVERT_MAXLEN 300         
#endif

#else  // WIN16
  #define TCHAR char
  #define TEXT(sz) sz 
  #define FROM_OLE_STRING(str) str  
  #define TO_OLE_STRING(str) str  
  #define LPTSTR LPSTR
#endif
      
#include "mydisp.h"
#include "tlb.h"

// MAX len of string table entries
#define STR_LEN   200

// String table constants
#define IDS_SERVERNAME             1
// These exception strings IDs that is will used in EXCEPINFO.wCode   
#define IDS_Unexpected             1001
#define IDS_OutOfMemory            1002   
#define IDS_InvalidIndex           1003
#define IDS_CollectionFull         1004
#define IDS_CannotFindTypeLibrary  1005
#define IDS_TypeLibraryCreationFailed 1006    
#define IDS_WrongType               1007
#define IDS_InvalidProgid           1008
#define IDS_CouldNotCreateObject    1009
#define IDS_ObjectDoesNotSupportAutomation   1010       
#define IDS_ObjectDoesNotProvideTypeInfo  1011
#define IDS_NotDualInterface 1012

// Function prototypes
BOOL InitDLL (HINSTANCE hInstance);
extern "C" STDAPI DllGetClassObject(REFCLSID rclsid, REFIID riid, LPVOID FAR *ppv);   
extern "C" STDAPI DllCanUnloadNow(void);

//Forward declarations.
class CArrayBound;
 
class FAR CBrowseHelperCF : public IClassFactory
{
public:
    // IUnknown methods 
    STDMETHOD(QueryInterface)(REFIID riid, LPVOID FAR* ppvObj);
    STDMETHOD_(ULONG, AddRef)(void);
    STDMETHOD_(ULONG, Release)(void); 
    
    // IClassFactory methods
    STDMETHOD(CreateInstance)(IUnknown FAR* punkOuter, REFIID riid, void FAR* FAR* ppv);
    STDMETHOD(LockServer)(BOOL fLock);    
    
    CBrowseHelperCF();
    
private:
    ULONG m_cRef;                   // Reference count
}; 

    
class FAR CBrowseHelper : public IBrowseHelper
{
public:
    // IBrowseHelper automation exposed methods
    STDMETHOD_(ITypeLibrary FAR*, BrowseTypeLibrary)(BSTR bstrPath);     
    
    STDMETHOD_(REFCLSID, GetInterfaceID)();    
    static HRESULT Create(CBrowseHelper FAR* FAR* ppBrowseHelper); // Creates and intializes Applicaton object 
    CBrowseHelper();
    ~CBrowseHelper();
};

class FAR CTypeLibrary : public ITypeLibrary
{
public:
    // ITypeLibrary automation exposed properties & methods 
    STDMETHOD_(BSTR, get_Name)();
    STDMETHOD_(BSTR, get_Documentation)();
    STDMETHOD_(long, get_HelpContext)();
    STDMETHOD_(BSTR, get_HelpFile)();
    STDMETHOD_(long, get_LocaleID)();
    STDMETHOD_(int, get_MajorVersion)();
    STDMETHOD_(int, get_MinorVersion)();
	STDMETHOD_(BSTR, get_GUIDAsString)();
    STDMETHOD_(ICollection FAR*, get_TypeInfos)();   
    
    STDMETHOD_(REFCLSID, GetInterfaceID)();    
    static HRESULT Create(LPTYPELIB ptlib, CTypeLibrary FAR* FAR* ppTypeLibrary); // Creates and intializes TypeLibrary object 
    CTypeLibrary();
    ~CTypeLibrary();
    
private:    
    BSTR m_bstrName;               // Type Library name
    BSTR m_bstrDocumentation;      // Documentation
    unsigned long m_ulHelpContext; // HelpContext
    BSTR m_bstrHelpFile;           // HelpFile
    GUID m_guid;                   // GUID
	LPOLESTR m_pszGUID;            // String form of GUID
    LCID m_lcid;                   // Locale ID
    unsigned short m_wMajorVer;    // Major version
    unsigned short m_wMinorVer;    // Minor version
    LPTYPELIB m_ptlib;             // ITypeLib* of type library.
    LPDISPATCH m_pdispTypeInfos;   // Collection of typeinfos contained by this typelib
};

// CTypeInfo is the base class for all the TypeInfos (CInterface, CDispinterface,
// CModule, CCoClass, CEnum, CStruct, CUnion, CAlias)
class FAR CTypeInfo : public ITypeInformation
{
public:
    // ITypeInfo automation exposed properties & methods 
    STDMETHOD_(BSTR, get_Name)();
    STDMETHOD_(BSTR, get_Documentation)();
    STDMETHOD_(long, get_HelpContext)();
    STDMETHOD_(BSTR, get_HelpFile)();
    STDMETHOD_(TYPEKIND, get_TypeInfoKind)();
    STDMETHOD_(short, get_TypeFlags)();
    STDMETHOD_(BSTR, get_GUIDAsString)();
    
    STDMETHOD_(REFCLSID, GetInterfaceID)();
    STDMETHOD(_InitTypeInfo)(LPTYPEINFO ptinfo); // Called by derived class to intialize this base class
    static HRESULT Create(LPTYPEINFO ptinfo, CTypeInfo FAR* FAR* ppTypeInfo); // Creates and intializes TypeInfo object 
    CTypeInfo();
    ~CTypeInfo();

protected:
	short m_wTypeFlags;            // TYPEFLAGS

private:    
    BSTR m_bstrName;               // TypeInfo name
    BSTR m_bstrDocumentation;      // Documentation 
    unsigned long m_ulHelpContext; // Help context
    BSTR m_bstrHelpFile;           // Help file
    TYPEKIND m_typekind;           // Type of TypeInfo. See TYPEKIND enumeration.
    GUID m_guid;                   // GUID
	LPOLESTR m_pszGUID;            // String form of GUID
};

class FAR CInterface : public CTypeInfo       
{
public:
    // IInterface automation exposed properties & methods 
    STDMETHOD_(ICollection FAR*, get_Functions)();
    STDMETHOD_(IInterface FAR*, get_BaseInterface)();
    
    STDMETHOD_(REFCLSID, GetInterfaceID)();    
    static HRESULT Create(LPTYPEINFO ptinfo, CInterface FAR* FAR* ppInterface); // Creates and intializes Interface object 
    CInterface();
    ~CInterface();
    
private:
    LPTYPEINFO m_ptinfo;             // ITypeInfo* of interface typeinfo.
    LPDISPATCH m_pdispFunctions;     // Collection of functions in interface.
	LPDISPATCH m_pdispBaseInterface; // Base interface of this interface.
};

class FAR CDispinterface : public CTypeInfo
{
public:
    // IDispinterface automation exposed properties & methods 
    STDMETHOD_(ICollection FAR*, get_Properties)();
    STDMETHOD_(ICollection FAR*, get_Methods)();
	STDMETHOD_(IInterface FAR*, get_Interface)();
    
    STDMETHOD_(REFCLSID, GetInterfaceID)();    
    static HRESULT Create(LPTYPEINFO ptinfo, CDispinterface FAR* FAR* ppDispinterface); // Creates and intializes Dispinterface object 
    CDispinterface();
    ~CDispinterface();
    
private:
    LPTYPEINFO m_ptinfo;              // ITypeInfo* of dispinterface typeinfo.
    LPDISPATCH m_pdispProperties;     // Collection of properties in dispinterface
    LPDISPATCH m_pdispMethods;        // Collection of methods in dispinterface
	LPDISPATCH m_pdispInterface;      // Interface part of dual interface, if this is a dual interface
};  

class FAR CModule : public CTypeInfo       
{
public:
    // IModule automation exposed properties & methods 
    STDMETHOD_(ICollection FAR*, get_Functions)();    
    
    STDMETHOD_(REFCLSID, GetInterfaceID)();   
    static HRESULT Create(LPTYPEINFO ptinfo, CModule FAR* FAR* ppInterface); // Creates and intializes Module object 
    CModule();
    ~CModule();
    
private:                             
    LPTYPEINFO m_ptinfo;              // ITypeInfo* of module typeinfo.
    LPDISPATCH m_pdispFunctions;      // Collection of functions in module
};

class FAR CCoClass : public CTypeInfo
{
public:   
    // ICoClass automation exposed properties & methods 
    STDMETHOD_(ICollection FAR*, get_Interfaces)();     
    
    STDMETHOD_(REFCLSID, GetInterfaceID)();    
    static HRESULT Create(LPTYPEINFO ptinfo, CCoClass FAR* FAR* ppCoClass); // Creates and intializes CoClass object     
    CCoClass();
    ~CCoClass();
    
private:
    LPTYPEINFO m_ptinfo;              // ITypeInfo* of coclass typeinfo.
    LPDISPATCH m_pdispInterfaces;     // Collection of interfaces/dispinterfaces in coclass
}; 

class FAR CEnum : public CTypeInfo
{
public:
    // IEnum automation exposed properties & methods
    STDMETHOD_(ICollection FAR*, get_Elements)();    
    
    STDMETHOD_(REFCLSID, GetInterfaceID)();    
    static HRESULT Create(LPTYPEINFO ptinfo, CEnum FAR* FAR* ppEnum); // Creates and intializes Enum object 
    CEnum();
    ~CEnum();
    
private:
    LPTYPEINFO m_ptinfo;             // ITypeInfo* of enum typeinfo.
    LPDISPATCH m_pdispElements;      // Collection of elements in enum.
};

class FAR CStruct : public CTypeInfo
{
public: 
     // IStruct automation exposed properties & methods 
    STDMETHOD_(ICollection FAR*, get_Members)(); 
    
    STDMETHOD_(REFCLSID, GetInterfaceID)();    
    static HRESULT Create(LPTYPEINFO ptinfo, CStruct FAR* FAR* ppStruct); // Creates and intializes Struct object 
    CStruct();
    ~CStruct();
    
private:
    LPTYPEINFO m_ptinfo;            // ITypeInfo* of struct typeinfo.
    LPDISPATCH m_pdispMembers;      // Collection of members in struct.
};

class FAR CUnion : public CTypeInfo
{  
public:
    // IUnion automation exposed properties & methods  
    STDMETHOD_(ICollection FAR*, get_Members)();   
    
    STDMETHOD_(REFCLSID, GetInterfaceID)();    
    static HRESULT Create(LPTYPEINFO ptinfo, CUnion FAR* FAR* ppUnion); // Creates and intializes Struct object 
    CUnion();
    ~CUnion();
    
private:
    LPTYPEINFO m_ptinfo;            // ITypeInfo* of union typeinfo.
    LPDISPATCH m_pdispMembers;      // Collection of members in union.
};


class FAR CAlias : public CTypeInfo
{ 
public:    
    // IAlias automation exposed properties & methods  
    STDMETHOD_(ITypeDesc FAR*, get_BaseType)(); 
    
    STDMETHOD_(REFCLSID, GetInterfaceID)();    
    static HRESULT Create(LPTYPEINFO ptinfo, CAlias FAR* FAR* ppAlias); // Creates and intializes Alias object 
    CAlias();
    ~CAlias();
    
private:
    LPTYPEINFO m_ptinfo;             // ITypeInfo* of alias typeinfo.
    LPDISPATCH m_pdispTypeDescBase;  // IDispatch of ITypeDesc which describes the base type of this alias.
};  

// CFunction represents all functions (including methods).
class FAR CFunction : public IFunction
{
public:
    // IFunction automation exposed properties & methods 
    STDMETHOD_(BSTR, get_Name)();
    STDMETHOD_(BSTR, get_Documentation)();
    STDMETHOD_(long, get_HelpContext)();
    STDMETHOD_(BSTR, get_HelpFile)();
    STDMETHOD_(ITypeDesc FAR*, get_ReturnType)();
    STDMETHOD_(ICollection FAR*, get_Parameters)(); 
    STDMETHOD_(MEMBERID, get_Memberid)();
    STDMETHOD_(CALLCONV, get_CallConvention)(); 
    STDMETHOD_(FUNCKIND, get_FuncKind)();
    STDMETHOD_(INVOKEKIND, get_InvocationKind)();
	STDMETHOD_(short, get_NumberOfOptionalParams)();
    STDMETHOD_(short, get_OffsetInVtbl)();
	STDMETHOD_(unsigned short, get_FuncFlags)();
    STDMETHOD_(OBJTYPE, get_Kind)();      
    
    STDMETHOD_(REFCLSID, GetInterfaceID)();    
    static HRESULT Create(LPTYPEINFO ptinfo, unsigned short nIndex, CFunction FAR* FAR* ppFunction); // Creates and intializes Function object 
    CFunction();
    ~CFunction();
    
private:   
    BSTR m_bstrName;                     // Function name.
    BSTR m_bstrDocumentation;            // Documentation.
    unsigned long m_ulHelpContext;       // Help context.
    BSTR m_bstrHelpFile;                 // Help file.
    LPDISPATCH m_pdispTypeDesc;          // IDispatch of ITypeDesc that described return type.
    LPDISPATCH m_pdispParameters;        // Collection of parameters function.
    LPFUNCDESC m_pfuncdesc;              // FUNCDESC of function.
    LPTYPEINFO m_ptinfoFunction;         // TypeInfo of which this function is an element.
};

// CProperty represents dispinterface properties and structure & union members.
class FAR CProperty : public IProperty
{
public:
    // IProperty automation exposed properties & methods 
    STDMETHOD_(BSTR, get_Name)();
    STDMETHOD_(BSTR, get_Documentation)();
    STDMETHOD_(long, get_HelpContext)();
    STDMETHOD_(BSTR, get_HelpFile)();
    STDMETHOD_(ITypeDesc FAR*, get_Type)();
    STDMETHOD_(MEMBERID, get_Memberid)(); 
    STDMETHOD_(OBJTYPE, get_Kind)();  
    
    STDMETHOD_(REFCLSID, GetInterfaceID)();   
    static HRESULT Create(LPTYPEINFO ptinfo, LPVARDESC pvardesc, CProperty FAR* FAR* ppProperty); // Creates and intializes Property object 
    CProperty();
    ~CProperty();
    
private:        
    BSTR m_bstrName;                     // Property name.
    BSTR m_bstrDocumentation;            // Documentation.
    unsigned long m_ulHelpContext;       // Help Context.
    BSTR m_bstrHelpFile;                 // Helpfile.
    MEMBERID m_memid;                    // MEMBERID of property.
    LPDISPATCH m_pdispTypeDesc;          // ITypeDesc that describes type of property.
};

class FAR CConstant : public IConstant
{
public:
    // IConstant automation exposed properties & methods
    STDMETHOD_(BSTR, get_Name)();
    STDMETHOD_(BSTR, get_Documentation)();
    STDMETHOD_(long, get_HelpContext)();
    STDMETHOD_(BSTR, get_HelpFile)();
    STDMETHOD_(ITypeDesc FAR*, get_Type)();    
    STDMETHOD_(VARIANT, get_Value)();      
    STDMETHOD_(MEMBERID, get_Memberid)(); 
    STDMETHOD_(OBJTYPE, get_Kind)();  
    
    STDMETHOD_(REFCLSID, GetInterfaceID)();    
    static HRESULT Create(LPTYPEINFO ptinfo, LPVARDESC pvardesc, CConstant FAR* FAR* ppConstant); // Creates and intializes Constant object 
    CConstant();
    ~CConstant();
    
private:        
    BSTR m_bstrName;                       // Constant name
    BSTR m_bstrDocumentation;              // Documentation
    unsigned long m_ulHelpContext;         // Help context
    BSTR m_bstrHelpFile;                   // Helpfile
    LPDISPATCH m_pdispTypeDesc;            // ITypeDesc that describes type of constant.
    MEMBERID m_memid;                      // MEMBERID.
    VARIANT m_vValue;                      // Constant value.
};

class FAR CParameter : public IParameter
{
public:
    // IParameter automation exposed properties & methods 
    STDMETHOD_(BSTR, get_Name)();
    STDMETHOD_(ITypeDesc FAR*, get_Type)(); 
    STDMETHOD_(int, get_IDLFlags)();
    STDMETHOD_(OBJTYPE, get_Kind)();    
    
    STDMETHOD_(REFCLSID, GetInterfaceID)();    
    static HRESULT Create(LPTYPEINFO ptinfo, BSTR bstrName, TYPEDESC FAR* ptypedesc, 
         IDLDESC FAR* pidldesc, CParameter FAR* FAR* ppParameter);  // Creates and intializes Parameter object 
    CParameter();
    ~CParameter();
    
private:  
    BSTR m_bstrName;                      // Parameter name.
    unsigned short m_wIDLFlags;           // specifies in/out/in-out/none
    LPDISPATCH m_pdispTypeDesc;           // ITypeDesc* that describes type of parameter.
};  

// Describes a type
class FAR CTypeDesc : public ITypeDesc
{
public:   
    // ITypeDesc automation exposed properties & methods
    STDMETHOD_(short, get_Type)();
    STDMETHOD_(ITypeInformation FAR*, get_UserDefinedDesc)();
    STDMETHOD_(IArrayDesc FAR*, get_ArrayDesc)();
    STDMETHOD_(ITypeDesc FAR*, get_PointerDesc)();  

    STDMETHOD_(REFCLSID, GetInterfaceID)();    
    static HRESULT Create(LPTYPEINFO ptinfo, TYPEDESC FAR* ptypedesc, CTypeDesc FAR* FAR* ppTypeDesc); // Creates and intializes TypeDesc object 
    CTypeDesc();
    ~CTypeDesc();
    
private:
    VARTYPE m_vartype;                  // Type
    LPDISPATCH m_pdispUserDefinedDesc;  // If m_vartype==VT_USERDEFINED, contains ITypeInformation* of user-defined type., 
    LPDISPATCH m_pdispArrayDesc;        // if m_vartype==VT_CARRAY, contains IArrayDesc* 
    LPDISPATCH m_pdispPointerDesc;      // if m_vartype==VT_PTR contains ITypeDesc* of type pointed to.
};

// Describes C-Style array
class FAR CArrayDesc : public IArrayDesc
{
public:     
    // IArrayDesc automation exposed properties & methods
    STDMETHOD_(ITypeDesc FAR*, get_ElementType)();
    STDMETHOD_(ICollection FAR*, get_ArrayBounds)();   

    STDMETHOD_(REFCLSID, GetInterfaceID)();    
    static HRESULT Create(LPTYPEINFO ptinfo, ARRAYDESC FAR* parraydesc, CArrayDesc FAR* FAR* ppArrayDesc); // Creates and intializes ArrayDesc object 
    CArrayDesc();
    ~CArrayDesc();
    
private:
    LPDISPATCH m_pdispTypeDescElement;     // ITypeDesc that descibed type of array element.
    LPDISPATCH m_pdispArrayBounds;         // IArrayBound that describes array bounds.
};

class FAR CArrayBound : public IArrayBound
{
public:
    // IArrayBound automation exposed properties & methods
    STDMETHOD_(long, get_ElementsCount)();
    STDMETHOD_(long, get_LowerBound)();  

    STDMETHOD_(REFCLSID, GetInterfaceID)();    
    static HRESULT Create(unsigned long cElements, long lLBound, CArrayBound FAR* FAR* ppArrayBound); // Creates and intializes ArrayBound object
    
private:
    unsigned long m_cElements;             // Count of elements in array.
    long m_lLBound;                        // Lower bound of array.
};

// Generic collection class that holds all collections.
class FAR CCollection : public ICollection
{
public:
    // ICollection automation exposed properties & methods
    STDMETHOD_(long, get_Count)();
    STDMETHOD_(LPDISPATCH, get_Item)(long lIndex);
    STDMETHOD_(LPUNKNOWN, get__NewEnum)();
    
    // CCollection methods 
    STDMETHOD_(void, Add)(LPDISPATCH pdispItem);  
    STDMETHOD_(REFCLSID, GetInterfaceID)();   
    static HRESULT Create(ULONG lMaxSize, long lLBound, CCollection FAR* FAR* ppCollection); // Creates and intializes Collection object 
    CCollection();
    ~CCollection();
    
private:
    SAFEARRAY FAR *m_psa;          // Safe array that holds Collection collection items.
    ULONG m_cElements;             // Number of items in Collection collection.
    ULONG m_cMax;                  // Maximum number of items Collection collection can hold.
    long m_lLBound;                // Lower bound of index of Collection collection.
};

class FAR CEnumVariant : public IEnumVARIANT
{
public:
    // IUnknown methods 
    STDMETHOD(QueryInterface)(REFIID riid, LPVOID FAR* ppvObj);
    STDMETHOD_(ULONG, AddRef)();
    STDMETHOD_(ULONG, Release)();

    // IEnumVARIANT methods 
    STDMETHOD(Next)(ULONG cElements, VARIANT FAR* pvar, ULONG FAR* pcElementFetched);
    STDMETHOD(Skip)(ULONG cElements);
    STDMETHOD(Reset)();
    STDMETHOD(Clone)(IEnumVARIANT FAR* FAR* ppenum);
    
    static HRESULT Create(SAFEARRAY FAR*, ULONG, CEnumVariant FAR* FAR*); // Creates and intializes Enumerator
    CEnumVariant();
    ~CEnumVariant();
    
private:
    ULONG m_cRef;           // Reference count                                 
    ULONG m_cElements;      // Number of elements in enumerator. 
    long m_lLBound;         // Lower bound of index.
    long m_lCurrent;        // Current index.
    SAFEARRAY FAR* m_psa;   // Safe array that holds elements.
};  
