//=================================================================================================================//
//                                                                                                                 //
//  inilib.h  - Include file for buildhs.c and ini_path.c                                                          //
//              These files are used to read a parsers ini file and generate the appropriate handoff               //
//              set. Ini_path gets the path to the ini file given the parser dll s name and buildhs                //
//              reads the ini file and builds the parsers handoff set.                                             //
//                                                                                                                 //
//  Created     SteveRo     11/8/93                                                                                      //
//                                                                                                                 //
//=================================================================================================================//

#include <bhsupp.h>

#if !defined(_INILIB_)

#define _INILIB_


#define INI_PATH_LENGTH             256                 // Maximum path tha can be specified
#define MAX_HANDOFF_ENTRY_LENGTH    80                  // Longest entry that can be specified ie.. 0x451 = NCP
#define MAX_PROTOCOL_NAME           40                  // Longest name for a protoocl
#define NUMALLOCENTRIES             10
#define RAW_INI_STR_LEN             200

#define PARSERS_SUBDIR              "PARSERS"
#define INI_EXTENSION               "INI"
#define BASE10_FORMAT_STR           "%ld=%s %ld"           
#define BASE16_FORMAT_STR           "%lx=%s %lx"           


// Given "XNS" or "TCP" or whatever BuildINIPath will return fully qual. path to "XNS.INI" or "TCP.INI"
extern LPSTR BuildINIPath( char     *FullPath,          // Buffer that will contain fully qual. path to ini file
                           char     *IniFileName );     // DLL name


// Builds Handoff Set

extern DWORD     WINAPI CreateHandoffTable(LPSTR               secName,
                                           LPSTR               iniFile,
                                           LPHANDOFFTABLE *    hTable,
                                           DWORD               nMaxProtocolEntries,
                                           DWORD               base);

extern HPROTOCOL WINAPI GetProtocolFromTable(LPHANDOFFTABLE  hTable, // lp to Handoff Table...
                                             DWORD           ItemToFind,       // port number etc...
                                             LPDWORD         lpInstData );   // inst data to give to next protocol

extern VOID      WINAPI DestroyHandoffTable( LPHANDOFFTABLE hTable );

extern BOOLEAN WINAPI IsRawIPXEnabled(LPSTR               secName,
                                      LPSTR               iniFile,
                                      LPSTR               CurProtocol );
#endif
