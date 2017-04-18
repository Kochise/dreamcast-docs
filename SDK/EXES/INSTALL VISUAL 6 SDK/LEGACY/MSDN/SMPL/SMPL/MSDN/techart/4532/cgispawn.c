//////////////////////////////////////////////////////////////////////////
//
// CGISPAWN.C - a WIN32 application
//
// This program is a generic CGI compliant application that does the 
// the following:
//		1. take name/value pairs and environment from HTML form and
//         place it in an INFILE (a temporary file)
//		2. create a temporary OUTFILE 
//		3. call an application as specified by the HTML form name/value pair
//		   SPAWN, foo.exe (foo.exe must accept the two command line args
//		   INFILE and OUTFILE. It must then open OUTFILE and write HTML 
//		   tagged text to it.)
//		4. Opens OUTFILE (after waiting on foo.exe) and writes contents
//		   to stdout.
//
// The beauty of this program is that you can write CGI compliant apps that 
// need not write to stdout/stdin (a requirement of CGI). A good example is
// using VB to write an application that takes the query information sent 
// by a form (which is written to the INFILE by this app) and using ODBC 
// search a database. The results of the search can then be formatted in 
// the OUTFILE using HTML.
//
// EXAMPLE Format of INFILE
//
//	[NameValuePairs]
//	SPAWN,/JAGINFO/JAGLOVE/VBCGI.EXE
//  ...other pairs
//	[Environment]
//	CONTENT_LENGTH=68
//	CONTENT_TYPE=application/x-www-form-urlencoded
//	GATEWAY_INTERFACE=CGI/1.1
//	HTTP_ACCEPT=application/pdf,application/sgml,audio/x-midi,application/x-rtf,video/msvideo,video/quicktime,video/mpeg,image/jpeg,image/gif,application/postscript,audio/wav,text/plain,text/html,audio/x-aiff,audio/basic,*/*
//	REMOTE_ADDR=22.22.22.100
//	REQUEST_METHOD=POST
//	SCRIPT_NAME=bin\cgispawn.exe
//	SERVER_NAME=22.22.22.100
//	SERVER_PROTOCOL=HTTP/1.0
//	SERVER_PORT=80
//	SERVER_SOFTWARE=HTTPS/0.94
//	HTTP_USER_AGENT=NCSA Mosaic(tm) Version 2.0.0a9 for Windows/
//
//  NOTE: very little error checking as this is a sample
//
//////////////////////////////////////////////////////////////////////////

#include <windows.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "global.h"
#include "cgispawn.h"

main(int argc, char *argv[], char *env[]) {

	//default timeout value
	lTimeOut = 30000;

	//get the path as specified by the HTTPS server
	if (!GetHTTPServerPath((LPSTR)ServerPath))  {
		ErrMsg("HTTPS server path not found in environment", ERR_EXIT, 0);
	}

	//get name/value pairs
	if ((m = GetNameValuePairs((entry *)&entries, (LPSTR)&FileToSpawn)) == 0)  {
		ErrMsg("No name/value pairs sent to server", ERR_EXIT, 1);
	}

	if (!IsRegisteredApp(FileToSpawn)) {
		ErrMsg("CGI app is not registered on server", ERR_EXIT, 2);
	}

	//get temp path from the system environment
	if (!GetTempPath(MAX_PATH, temppath))  {
		ErrMsg("Unable to get temp path on server", ERR_EXIT, 3);
	}

	//create a temp filename for the infile
	if (!GetTempFileName(temppath, "GTW", 0, TempInFile))  {
		ErrMsg("Unable to create TempInFile on server", ERR_EXIT, 4);
	}

	//create a temp filename for the outfile
	if (!GetTempFileName(temppath, "GTW", 0, TempOutFile))  {
		DeleteFile(TempInFile);
		ErrMsg("Unable to create TempOutFile on server", ERR_EXIT, 5);
	}

	//prepare the infile for use
	if ((hTempInFile = CreateFile(TempInFile, GENERIC_READ | GENERIC_WRITE, 0, NULL, CREATE_ALWAYS, 
	                               FILE_ATTRIBUTE_NORMAL, 0 )) == INVALID_HANDLE_VALUE)  {
		ErrMsg("Unable to create TempInFile on server", ERR_EXIT, 4);
	}

	//create the outfile and close it. It's name will be passed to the spawned app for
	//use by that app.
	if ((hTempOutFile = CreateFile(TempOutFile, GENERIC_READ | GENERIC_WRITE, 0, NULL, CREATE_ALWAYS, 
	                        FILE_ATTRIBUTE_NORMAL, 0 )) == INVALID_HANDLE_VALUE)  {
		CloseHandle(hTempInFile);
		DeleteFile(TempInFile);
		ErrMsg("Unable to create TempOutFile on server", ERR_EXIT, 4);
	}

	CloseHandle(hTempOutFile);
	
	//write the name/value pairs to the INFILE
	WriteNameValuePairsToFile(hTempInFile, (entry*)&entries, m, (LPSTR)&FileToSpawn, &lTimeOut);

	//write the environment to the INFILE
	WriteEnvToFile(hTempInFile, env);

	//flush and close INFILE
	FlushFileBuffers(hTempInFile);
	CloseHandle(hTempInFile);

	//prepend the server path to the file that is to be spawned
	strcat(ServerPath, FileToSpawn);

	//prepare the commandline to be passed to the spawned app
	sprintf(szCommandLine, "%s %s %s",  ServerPath, TempInFile, TempOutFile);

	//start a new process calling the specified application. This will wait on
	//the process to complete before returning
	SpawnNewProcess((LPSTR)ServerPath, (LPSTR)szCommandLine, (STARTUPINFO *)&si, 
				 (PROCESS_INFORMATION *)&pi, lTimeOut, TempOutFile);

	//having just returned from the called app, open the file and send the formatted
	//text to stdout	
	WriteFileToSTDOUT(TempOutFile);

	//delete the temporary files
	DeleteFile(TempInFile);
	DeleteFile(TempOutFile);
	
	return 0;
}

