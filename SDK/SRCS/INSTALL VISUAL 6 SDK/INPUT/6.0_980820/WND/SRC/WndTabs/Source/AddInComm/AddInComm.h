/***************************************************************************/
/* NOTE:                                                                   */
/* This document is copyright (c) by Oz Solomonovich, and is bound by the  */
/* MIT open source license (www.opensource.org/licenses/mit-license.html). */
/* See License.txt for more information.                                   */
/***************************************************************************/

#ifndef __ADDINCOMM_H
#define __ADDINCOMM_H

extern "C" {

#ifndef DECLARE_OPAQUE
#define DECLARE_OPAQUE(name)    typedef struct { int unused; } name##__ ; \
				typedef const name##__ * name; \
				typedef name*  LP##name
#endif

// handle to add-in
DECLARE_OPAQUE(HADDIN);

// this is the prototype of the command handling function for your add-in
typedef int (AddinCmdHandler_t)(LPCTSTR pCmd);


// maximum length of addin names
#define MAX_ADDIN_NAME_LEN      128
#define MAX_ADDIN_VER_STR_LEN   MAX_ADDIN_NAME_LEN


// -- registration --

// registers your add-in.  returns the handle or NULL on error
HADDIN __declspec(dllexport) AICRegisterAddIn(LPCTSTR pName, int iVerMaj, 
    int iVerMin, int iVerExtra, AddinCmdHandler_t *pCmdFn = NULL);

// you must unregister your add-in with this function before the program 
// exits.  the function returns 'true' on success.
bool __declspec(dllexport) AICUnregisterAddIn(HADDIN hAddIn);


// -- add-in information --

// returns the number of addins registered for the running DevStudio 
// instance
int __declspec(dllexport) AICGetAddInCount();

// fills an array with handles to all the registered addins
// you must allocate the memory for the array.  returned handles are 
// read-only.
void __declspec(dllexport) AICGetAddInList(HADDIN addin_array[]);

// get an add-in by it's name.  returned handle is read-only.  
// NULL is returned if the addin isn't registered.
// TIP: don't save this value, because the user might load/unload add-ins
// at runtime from the Tools|Customize|Add-ins dialog.
HADDIN __declspec(dllexport) AICGetAddIn(LPCTSTR pName);

// returns the name of an addin.  returns a temporary string that should be
// copied.
LPCTSTR __declspec(dllexport) AICGetAddInName(HADDIN hAddIn);

// returns the version of the add-in.  in case of error, all integers are
// set to -1
void __declspec(dllexport) AICGetAddInVersion(HADDIN hAddIn, int& iVerMaj,
    int& iVerMin, int& iVerExtra);

// returns a string describing the program and it's version.  if the program
// didn't set a special string, the function returns it's version parameters
// formatted as "#.#.#".  
// the returned is is a temporary and should be copied.
// Non critical, available starting version 1.2.0
LPCTSTR __declspec(dllexport) AICGetAddInVersionString(HADDIN hAddIn);

// set the string describing the program and it's version.  if you don't call
// this function, a default string will be generated
// Non critical, available starting version 1.2.0
void __declspec(dllexport) AICSetAddInVersionString(HADDIN hAddIn, 
    LPCTSTR pszVerStr);


// -- commands --

// send a command to a specified addin.  the return value is specific to the
// add-in executing the command.
int __declspec(dllexport) AICSendCommand(HADDIN hAddIn, LPCTSTR pCommand);


// -- misc --

// DLL version information
void __declspec(dllexport) AICGetDllVersion(int& iVerMaj, int& iVerMin,
                                            int& iVerExtra);


} // extern "C"

#endif // __ADDINCOMM_H
