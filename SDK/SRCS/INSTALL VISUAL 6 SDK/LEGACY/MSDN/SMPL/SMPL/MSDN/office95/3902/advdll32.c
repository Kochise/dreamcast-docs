#include <windows.h>
#include <oleauto.h>
#include <dispatch.h>
#include <malloc.h>
#include <stdlib.h>

#define DllExport __declspec(dllexport)

double __declspec(dllexport) DoubleArg(double dRadius)
{
	return dRadius * 2 * 3.14159;
}

short __declspec(dllexport) PointerArg(short *pn)
{                                                      
	if (*pn < 0)
		return 0;	// False in Visual Basic
		
	*pn *= 2;
	return -1;		// True in Visual Basic
}                   

short __declspec(dllexport) VariantArg(VARIANT vt)
{   
	int i;
	char *pcBuf;
		                                              
	if (vt.vt == VT_DISPATCH)		// variant is an object
		return -1;
	else if (vt.vt == VT_BSTR) {	// variant is a string
		i = SysStringLen(vt.bstrVal);
		pcBuf = (char *)malloc(i + 1);
		WideCharToMultiByte(CP_ACP, 0, vt.bstrVal, i, pcBuf, i, NULL, NULL);
		i = atoi(pcBuf);
		free(pcBuf);
		return (short)i;
	}
	else if (vt.vt == VT_I2)		// variant is an integer
		return vt.iVal;
	else							// variant is something else
		return -3;
}
                           
short __declspec(dllexport) SType(BSTR *pbstr)
{
	if (pbstr == NULL) 	// pointer is null; will never happen
		return 1;
	if (*pbstr == NULL)	// string (or variant) is allocated by VB 
						// with Dim statement,
						// but not yet assigned
		return 2;
	if (*pbstr[0] == 0)	// string is allocated 
						// and assigned to empty string ("")
		return 3;
	// string has a value; ANSI characters can be accessed at *pbstr
	return 4;
}
		
                          
short __declspec(dllexport) StringArgs(BSTR *pbstrArg1,
	BSTR *pbstrArg2, int cch)
{   
	// return error code if requested characters 
	// less than zero, or input string is unassigned 
	// or has too few characters
				                                               
	if (cch < 0 || *pbstrArg1 == NULL || 
			(int)SysStringByteLen(*pbstrArg1) < cch)
		return -1;		
		                                                                        
	if (*pbstrArg2 != NULL) { 	// argument string is already assigned; 
								// we must free before allocating
		SysFreeString(*pbstrArg2);
	}

	if ((*pbstrArg2 = SysAllocStringByteLen((char *)*pbstrArg1, cch))
			 == NULL)
		return -2;
		
	return 0;
}

typedef SAFEARRAY * FPSAFEARRAY;

short __declspec(dllexport) SumArray(
	FPSAFEARRAY *ppsa, long *plResult)
{          
	short sElem;
	long lLb, lUb, l, lResult;
		          
	if (*ppsa == NULL) // array has not been initialized
		return -4;
	
	if ((*ppsa)->cDims != 1)	// check number of dimensions
		return -5;
						              
	// get the upper and lower bounds of the array
			                            
	if (FAILED(SafeArrayGetLBound(*ppsa, 1, &lLb)) ||
			FAILED(SafeArrayGetUBound(*ppsa, 1, &lUb)))
		return -1;
	
	// loop through the array and add the elements
	
	for (l = lLb, lResult = 0; l <= lUb; l++) {		          
		if (FAILED(SafeArrayGetElement(*ppsa, &l, &sElem)))
			return -2;                           
		lResult += sElem;
	} 
	    
	*plResult = lResult;	         
	return 0;
}
 

typedef struct {
	short s;
	BSTR bstr;
} ARG;

short __declspec(dllexport) StructArg(ARG *parg, char *szArg)
{   
	unsigned int cch;        
	BSTR bstr;
	                  
	if (parg == NULL)
		return -1;
	
	// allocate a local string first; if this fails, 
	// we have not touched the passed-in string
	
	cch = strlen(szArg);
	if ((bstr = SysAllocStringByteLen(szArg, cch)) == NULL)
		return -1;
		
	if (parg->bstr != NULL)	// string is already assigned
		SysFreeString(parg->bstr);
		
	parg->s = (short)cch;
	parg->bstr = bstr;
	
	return parg->s;
} 
              
short __declspec(dllexport) NewArray(FPSAFEARRAY *ppsa)
{              
	SAFEARRAY *psa;
	SAFEARRAYBOUND sa;
	
	sa.lLbound = 1;       
	sa.cElements = 10;
                      
	if (*ppsa == NULL) { //array not yet initialized		       
		if ((psa = SafeArrayCreate(VT_I2, 1, &sa)) == NULL)
			return -2;
		*ppsa = psa;
	}
	else {
		if ((*ppsa)->cDims != 1)	// check array dimensions
			return -1;				// fail if multi-dimension
		                      
		if (FAILED(SafeArrayRedim(*ppsa, &sa)))
			return -3;                    
	}
	
	return 0;
}
		

short __declspec(dllexport) StringArray(FPSAFEARRAY *ppsa)
{       
	LONG l;
	BSTR bstr; 
	SAFEARRAY *psa;
	SAFEARRAYBOUND sa;
		
	sa.lLbound = 0;
	sa.cElements = 3;

	if ((*ppsa)->cDims != 1)	// check array dimensions
		return -1;
		                      
	if (*ppsa == NULL) { // array not yet initialized
		if ((psa = SafeArrayCreate(VT_BSTR, 1, &sa)) == NULL)
			return -2;
		*ppsa = psa;
	}
	else if (FAILED(SafeArrayRedim(*ppsa, &sa)))
		return -3;                    
		
	// loop through the array; get each element and free
	// any existing string, then allocate the new string
	// and put it in the array
	
	for (l = sa.lLbound; l < (long)sa.cElements; l++) {
		if (FAILED(SafeArrayGetElement(*ppsa, &l, &bstr)))
			return -4;                                
		SysFreeString(bstr);
		if ((bstr = SysAllocStringByteLen("test string", 11)) == NULL)
			return -5;      
		if (FAILED(SafeArrayPutElement(*ppsa, &l, bstr)))
			return -6;
	}                
	
	return 0;
}	
            
short __declspec(dllexport) StructArray(FPSAFEARRAY *ppsaArg,
	FPSAFEARRAY *ppsaStr)
{               
	ARG *parg;
	SAFEARRAY *psa;
	BSTR *pbstr;
	ULONG i, cElements;
		                   
	if (*ppsaStr == NULL)
		return -1;
		
	cElements = (*ppsaStr)->rgsabound[0].cElements;
    
  	if (*ppsaArg == NULL) { // create a new array
  	
		if (FAILED(SafeArrayAllocDescriptor(1, &psa)))
	 		return -3;
    
    	// set up the SAFEARRAY structure
    	// and allocate data space
    	                    
		psa->fFeatures = 0;
  		psa->cbElements = sizeof(ARG);                
  		psa->rgsabound[0].cElements = cElements;
  		psa->rgsabound[0].lLbound = (*ppsaStr)->rgsabound[0].lLbound;
  
  		if (FAILED(SafeArrayAllocData(psa))) {
  			SafeArrayDestroyDescriptor(psa);
			return -4;                      
		}
        
        // get a pointer to the new data
        
  		if (FAILED(SafeArrayAccessData(psa, 
  				(void **)&parg))) {
			SafeArrayDestroy(psa);
			return -5;
  		}                            
  	} 
  	else { // redimension the old array
  		if (FAILED(SafeArrayRedim(*ppsaArg, 
  				(*ppsaStr)->rgsabound)))
  			return -6;
		
		// get a pointer to the old data  			
		
  		if (FAILED(SafeArrayAccessData(*ppsaArg, 
  				(void **)&parg)))
  			return -7;
  	}
  	    
	// get a pointer to the string array data
	  	                     
	if (FAILED(SafeArrayAccessData(*ppsaStr, 
			(void **)&pbstr)))
		return -8;
	
	// allocate strings in the structure array and 
	// fill them with strings from the string array.
	// free any old BSTRs in the structure
		  	                     
  	for (i = 0; i < cElements; i++) {
  		SysFreeString(parg[i].bstr);
		parg[i].s = strlen((char *)pbstr[i]);
  		parg[i].bstr = SysAllocStringByteLen((char *)pbstr[i], parg[i].s);
   	}
  	
	// release pointers and move the structure
	// array pointer to the new array if we created one
	  		            
  	SafeArrayUnaccessData(*ppsaStr);
	
	if (*ppsaArg == NULL) {
		SafeArrayUnaccessData(psa);
		*ppsaArg = psa;                         
	}
	else 
		SafeArrayUnaccessData(*ppsaArg);
		
	return 0;
}                 

short __declspec(dllexport) ArrayType(FPSAFEARRAY *ppsa)
{                    
	if (*ppsa == NULL)
		return -1;
	else
		return (*ppsa)->fFeatures;
}
