// Copyright (C) 1992-1998 Microsoft Corporation
// All rights reserved.


//This code is the basis for which the add-in to MSDevStudio
//      for generating help files will stem. As of now it splits apart
//      the prototype for a function

//This will work on almost every function declaration
//      1)      DO NOT use on function pointer declarations. For example:
//                              "DWORD (CALLBACK* Get)(LPOLESTREAM, void FAR*, DWORD);"
//                      will fail. The parser gets confused on the (CALLBACK* Get).
//      2)      The question arises as to which which do you run this macro on,
//                              in the header declaration, or in the actual source code.
//                              If you are generating help for a function not in a class, it
//                              is probably best to run it on the header file declaration.
//                              If the function is in a class, try to run it on the source
//                              declaration     because the parser can detect the class scoping
//                              (although, as of right now parses this class scoping, but does
//                              nothing with it, except storing it into an array).
//      3)      Many OLE 2 declarations are declared with macros,
//                              WINOLEAPI_(BOOL) OleIsRunning(LPOLEOBJECT pObject);
//                              the parser is fine with this as long as there are no spaces in
//                              between the WINOLEAPI_ and (BOOL).
//      4)      The parser gets confused if the prototype is something like:
//                      void foo(CArray<CObject, CObject> bar); This happens when there is
//                      a template in the parameter list and a comma appears within this
//                      template declaration. The parser gets confused and tries to set
//                      each as a parameter, ie CArray<CObject is one parameter, and
//                      CObject> bar is another.



#include <stdafx.h>
#include <afxtempl.h>
#include <fstream.h>
#include "resource.h"
#include "apisplit.h"

//The following value is described in the comment for GetReturnType
#define DEFAULT_RETURN 1

inline void WriteString(CString strStr, CFile& file)
{ file.Write(strStr, strStr.GetLength()); }

inline void WriteString(int nIDS, CFile& file)
{
	CString strStringToWrite;
	strStringToWrite.LoadString(nIDS);
	WriteString(strStringToWrite, file);
}

void GenerateHTML(CString strHTMLPath, CString strClassFunctionName,
		CString strFunctionName,
		CArray<CString,CString>& Parameters,
		CArray<CString,CString>& ParameterNames, CString strReturn)
{
	CFile Stream(strHTMLPath,
			CFile::modeCreate|CFile::modeWrite|CFile::shareExclusive);
	WriteString(IDS_HTML1, Stream);
	WriteString(strFunctionName, Stream);
	WriteString(IDS_HTML2, Stream);
	WriteString(strClassFunctionName, Stream);
	WriteString(IDS_HTML3, Stream);

	WriteString(strReturn+" "+strFunctionName,Stream);

	WriteString(IDS_HTML4, Stream);

	if (Parameters.GetSize() != 0)
	{
		for (int i = 0 ; i < Parameters.GetSize()-1 ; i++)
		{
			WriteString(IDS_HTML5, Stream);
			WriteString(Parameters.GetAt(i), Stream);
			WriteString(IDS_HTML6, Stream);
		}
		WriteString(IDS_HTML5, Stream);
		WriteString(Parameters.GetAt(Parameters.GetSize()-1), Stream);
		WriteString(IDS_HTML7, Stream);
	}
	else
		WriteString(IDS_HTML8, Stream);

	WriteString(IDS_HTML9, Stream);

	for (int i = 0 ; i < ParameterNames.GetSize() ;i++)
	{
		WriteString(IDS_HTML10, Stream);
		WriteString(ParameterNames.GetAt(i), Stream);
		WriteString(IDS_HTML11, Stream);
	}
	//For some reason, the following <dt></dt> sequence is needed to keep
	//  things straight.in the resulting HTML
	WriteString(IDS_HTML12, Stream);
}

void GenerateHelpFile(CString strRTFPath, CString strClassFunctionName,
					  CString strFunctionName,
					  CArray<CString,CString>& Parameters,
					  CArray<CString,CString>& ParameterNames,
					  CString strReturn, CString ContextID, CString TopicName)
{
	CString sStringToWrite;
	CFile Stream(strRTFPath,
			CFile::modeCreate|CFile::modeWrite|CFile::shareExclusive);

	WriteString(IDS_RTF1, Stream);
	WriteString(IDS_RTF2, Stream);
	WriteString(IDS_RTF3, Stream);

	//Send the context ID for the page being generated
	WriteString(ContextID, Stream);
	//Dump secondary help header
	WriteString(IDS_RTF4, Stream);
	WriteString("SIMPLE Help Topic 1", Stream);

	//More header info
	WriteString(IDS_RTF5, Stream);

	//Dump the name this is known as in help topics.index dialog
	WriteString(TopicName, Stream);

	//Output prototype dependant information
	WriteString(IDS_RTF6, Stream);
	WriteString(strClassFunctionName, Stream);
	WriteString(IDS_RTF7, Stream);

	WriteString(strReturn+" "+strFunctionName+"(\n", Stream);
	WriteString("\\par ", Stream);

	if (Parameters.GetSize() != 0)
	{
		for (int i = 0 ; i < Parameters.GetSize()-1 ; i++)
		{
			WriteString("  "+Parameters.GetAt(i)+",\n", Stream);
			WriteString("\\par\n", Stream);
		}
		WriteString("  "+Parameters.GetAt(Parameters.GetSize()-1), Stream);
	}

	WriteString(IDS_RTF8, Stream);

	for (int i = 0 ; i < ParameterNames.GetSize() ;i++)
	{
		WriteString(ParameterNames.GetAt(i)+"\n", Stream);
		WriteString(IDS_RTF9, Stream);
	}
	WriteString(IDS_RTF10, Stream);
	Stream.Close();
}

//Because double spaces only get in the way, this routine removes them.
//It also removes spaces around '::' so that we can find scope resolution
void RemoveUnnecessary(CString& str)
{
	//First, strip out all those pesky, unwanted double spaces
	str.TrimLeft();
	str.TrimRight();
	int nLoc = str.Find("  ");
	while (nLoc > 0)
	{
		str = str.Left(nLoc) + str.Right(str.GetLength()-nLoc-1);
		nLoc = str.Find("  ");
	}

	//Now get rid of and ' ::' or ':: '
	nLoc = str.Find(" ::");
	while(nLoc > 0)
	{
		str = str.Left(nLoc) + str.Right(str.GetLength()-nLoc-1);
		nLoc = str.Find(" ::");
	}
	nLoc = str.Find(":: ");
	while(nLoc > 0)
	{
		str = str.Left(nLoc+2) + str.Right(str.GetLength()-nLoc-3);
		nLoc = str.Find(":: ");
	}
}

void GetFunctAndScope(CString& strFuncName, CArray<CString,CString>& Scoping,
					  CString& strNewFunc)
{
	strNewFunc = strFuncName;
	int nLoc = strNewFunc.Find("::");
	while (nLoc > 0)
	{
		Scoping.Add(strNewFunc.Left(nLoc));
		strNewFunc = strNewFunc.Right(strNewFunc.GetLength()-nLoc-2);
		nLoc = strNewFunc.Find("::");
	}
}

void ConvertWSToSpace (CString& str)
{
	//To fix the problem of when there is a comment describing parameters,
	//      the first step is to scan the string, and see if there are any '//'
	int nLoc = str.Find("//");
	while (nLoc != -1)
	{
		//There is a '//', so we then take the string from there to the
		//  end of the string, and find a '\n'
		CString strComment = str.Right(str.GetLength()-nLoc);
		str = str.Left(nLoc);
		//within comment, search for the '\n'
		int nCRLoc = strComment.Find('\n');
		if (nCRLoc != -1)
		{
			CString strDecommented = strComment.Right(
					strComment.GetLength()-nCRLoc);
			str += strDecommented;
			//An enhancement would be to save this comment, and use it
			//  to describe the parameter in the help file
			nLoc = str.Find("//");
		}
		else
		{
			nLoc = -1;
		}
	}

	//Next, a search for the old style comments (/**/) is performed
	nLoc = str.Find("/*");
	while(nLoc != -1)
	{
		CString strComment = str.Right(str.GetLength()-nLoc);
		str = str.Left(nLoc);
		//within the comment, search for the closing '*/'
		int nEndComm = strComment.Find("*/");
		if (nEndComm != -1)
		{
			CString strDecommented = strComment.Right(
					strComment.GetLength()-nEndComm-2);
			str += strDecommented;
			//An enhancement would be to save this comment,
			//  and use it to describe the parameter in the help file
			nLoc = str.Find("/*");
		}
		else
		{
			nLoc = -1;
		}
	}
	nLoc = str.Find("\t");
	while(nLoc != -1)
	{
		char foo = str.GetAt(nLoc);
		str.SetAt(nLoc, ' ');
		nLoc = str.Find("\t");

	}
	nLoc = str.Find("\n");
	while(nLoc != -1)
	{
		char foo = str.GetAt(nLoc);
		str.SetAt(nLoc, ' ');
		nLoc = str.Find("\n");
	}
	/*for (int i = 0 ; i < str.GetLength()-1 ; i++)
		if ((str[i] == '\t') || (str[i] == '\n'))
			str.SetAt(i, ' ');*/
}

void GetReturnType(CString& str, CArray<CString,CString>& ReturnsArray,
				   CString& strSuggested, int nAppendStar)
{
	//There are many conflicts that could arise from
	//      finding the return type, for example look at the prototype
	//      from the windows header files for FreeLibrary:
	//      WINBASEAPI BOOL WINAPI FreeLibrary(HMODULE hLibModule);
	//  If we start at FreeLibrary and scan backwards for the first
	//      word, we have WINAPI as the return type. If we start at
	//      the beginning of the line and scan foreward for the first
	//      word, we have WINBASEAPI as the return type. Things could
	//      also get more complicated, we could start throwing FAR's,
	//      _declspec's, and much more (static _declspec BOOL FAR foo(char*))
	//  The way this is remedied is as follows:
	//      1) Count the number of items that appears before the function name
	//      2) if Count == 0, no return type is assumed
	//               if Count == 1, use the found return type
	//               if Count >= 2, use the DEFAULT_RETURN word as the return type
	//      If the wrong word is grabbed, it is trivial to change it in the
	//      help file, but under most circumstances this should work.*/

	//we know the string is of the form:  words words ...  funcname
	str = str.Left(str.ReverseFind(' '));
	str.TrimRight();

	if (str.GetLength() != 0)
	{
		int nEndOfItem = str.Find(' ');
		while ((str.GetLength() != 0) && (nEndOfItem != -1))
		{
			ReturnsArray.Add(str.Left(nEndOfItem));

			str = str.Right(str.GetLength()-nEndOfItem);
			str.TrimLeft();
			str.TrimRight();
			nEndOfItem = str.Find(' ');
		}
		ReturnsArray.Add(str);

		//Right now there could possibly be a problem with pointers, if the
		//      prototype is of the form HWND *foo(...) the pointer is attached to
		//  the function name, when in actuality the '*' belongs with HWND.
		//  Also there is the case when the prototype is HWND * foo(...), it
		//  ends up that * is viewed as a return type, that is fixed up here.
		for (int i = 0 ; i < ReturnsArray.GetSize() ; i++)
		{
			//Check to see if the element is a '*'
			if (ReturnsArray.GetAt(i) == "*")
			{
				//Delete it...
				ReturnsArray.RemoveAt(i);
				//Change old value before it
				ReturnsArray.SetAt(i-1, ReturnsArray.GetAt(i-1) + "*");
			}
		}

		//Check for the HWND *foo(...) case
		for (i = nAppendStar ; i > 0 ; i--)
			ReturnsArray.SetAt(ReturnsArray.GetSize()-1,
					ReturnsArray.GetAt(ReturnsArray.GetSize()-1) + " *");

		//Here we decide which value we use as the return type,
		//      there probably is a better way of calculating this, but that
		//  will be
		//      left until later.
		if (ReturnsArray.GetSize() == 1)
			strSuggested = ReturnsArray.GetAt(0);
		else
		{
			//If DEFAULT_RETURN is greater than the actual number of possible
			//  return types, then give back the last possible one
			if (DEFAULT_RETURN > ReturnsArray.GetSize())
				strSuggested = ReturnsArray.GetAt(ReturnsArray.GetSize()-1);
			else
				strSuggested = ReturnsArray.GetAt(DEFAULT_RETURN);
		}
	}
}

void GetListOfParamNames(CArray<CString,CString>& ParamList,
				CArray<CString,CString>& ParamNames)
{
	for (int i = 0 ; i < ParamList.GetSize() ; i++)
	{
		CString strTemp = ParamList.GetAt(i);
		strTemp = strTemp.Right(strTemp.GetLength()-strTemp.ReverseFind(' ')-1);
		while (strTemp[0] == '*')
			strTemp = strTemp.Right(strTemp.GetLength()-1);
		ParamNames.Add(strTemp);
	}
}

int GetParameters(CString& strParameters, CString& strPrototype,
				CArray<CString,CString>& ParamList)
{
	//Start off by getting to the end of the argument list
	strParameters = strPrototype.Left(strPrototype.ReverseFind(')'));
	strParameters.TrimRight();

	int nBeginningOfParameters = strParameters.ReverseFind('(');
	strParameters = strParameters.Right(strParameters.GetLength()-
			nBeginningOfParameters-1);
	strParameters.TrimLeft();

	//now pull off each parameter
	if (strParameters.GetLength() != 0)
	{
		int nComma = strParameters.Find(',');
		while (nComma != -1)
		{
			ParamList.Add(strParameters.Left(nComma));
			strParameters = strParameters.Right(strParameters.GetLength()-
					nComma-1);
			strParameters.TrimLeft();
			strParameters.TrimRight();
			nComma = strParameters.Find(',');
		}
		ParamList.Add(strParameters);
	}
	return nBeginningOfParameters;
}
