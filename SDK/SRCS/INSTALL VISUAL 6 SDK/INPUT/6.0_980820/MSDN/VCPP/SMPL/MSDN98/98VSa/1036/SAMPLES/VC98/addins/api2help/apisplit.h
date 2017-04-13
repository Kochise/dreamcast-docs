// Copyright (C) 1992-1998 Microsoft Corporation
// All rights reserved.

void Main(CString, BOOL HTML, BOOL RTF);
void ConvertWSToSpace (CString& str);
void RemoveUnnecessary(CString&);
int GetParameters(CString& Parameters, CString& Prototype, CArray<CString,CString>& ParamList);
void GetFunctAndScope(CString& FuncName, CArray<CString,CString>& Scoping, CString& NewFunc);
void GetReturnType(CString& str, CArray<CString,CString>& ReturnsArray, CString& Suggested, int AppendStar);
void GenerateHelpFile(CString PathThis, CString strClassFunctionName, CString FunctionName, CArray<CString,CString>& Parameters, CArray<CString,CString>& ParameterNames, CString Return, CString ContextID, CString TopicName);
void GenerateHTML(CString HTMLPath, CString strClassFunctionName, CString FunctionName, CArray<CString,CString>& Parameters, CArray<CString,CString>& ParameterNames, CString Return);
void GetListOfParamNames(CArray<CString,CString>& ParamList, CArray<CString,CString>& ParamNames);
