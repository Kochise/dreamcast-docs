IE sample DLL -- IEUI Replaceable UI DLL
-----------------------------------------

* Purpose:
This sample shows how to create a replaceable UI DLL that allows you to customize certain
UI components in the HTML control. For example, you can change the error messages and the 
way the prompt dialog works.

* Required Files\Syntax:
IE components

* Used by:
mshtml.dll

* Registry entry:
[HKEY_CLASSES_ROOT\CLSID\{B048FC81-122D-11D3-9590-00C04FAEA6D4}\InProcServer32]
@="ieui.dll"
