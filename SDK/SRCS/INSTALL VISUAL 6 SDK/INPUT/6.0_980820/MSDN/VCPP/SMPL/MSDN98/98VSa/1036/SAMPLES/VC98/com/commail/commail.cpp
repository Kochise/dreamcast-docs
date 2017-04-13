// Copyright (C) 1992-1998 Microsoft Corporation
// All rights reserved.
//
// This source code is only intended as a supplement to the
// Microsoft Visual C++ Language  Reference and related
// electronic documentation provided with Microsoft Visual C++.
// See these sources for detailed information regarding the
// Microsoft Visual C++ product.

// Compile with cl /GX commail.cpp
//To DO
#pragma message ("TO DO: add your Windows system directory (\\winnt\\system32 or \\windows\\system)to Tools.Options.Directories.Include files.")
#import <olemsg32.dll> no_namespace

#include <stdio.h>
#include <assert.h>
#include <tchar.h>

void dump_com_error(_com_error &e)
{
    _tprintf(_T("Oops - hit an error!\n"));
    _tprintf(_T("\a\tCode = %08lx\n"), e.Error());
    _tprintf(_T("\a\tCode meaning = %s\n"), e.ErrorMessage());
    _bstr_t bstrSource(e.Source());
    _bstr_t bstrDescription(e.Description());
    _tprintf(_T("\a\tSource = %s\n"), (LPCTSTR) bstrSource);
    _tprintf(_T("\a\tDescription = %s\n"), (LPCTSTR) bstrDescription);
}

// If this is placed in the scope of the smart pointers, they must be
// explicitly Release(d) before CoUninitialize() is called.  If any reference
// count is non-zero, a protection fault will occur.
struct StartOle {
    StartOle() { CoInitialize(NULL); }
    ~StartOle() { CoUninitialize(); }
} _inst_StartOle;

void AddFileToMessage(
MessagePtr  pMessage,
LPCTSTR pszFilename)
{
    FILE* fInfile = _tfopen(pszFilename, _T("r"));
    TCHAR szBuffer[512];
    LPTSTR pszBuffer, pszMessage = new TCHAR[0x8000];
    *pszMessage = 0;
    int count = 0;

    while ((pszBuffer = _fgetts(szBuffer, sizeof(szBuffer), fInfile)))
    {
        count += sizeof(szBuffer)/sizeof(TCHAR);
        if (count >= 0x8000 || feof(fInfile) || pszBuffer != szBuffer)
            break;
        assert(!ferror(fInfile));
        _tcscat(pszMessage, pszBuffer);
    }
    pMessage->Text = pszMessage;
    delete [] pszMessage;
}

void main()
{
    try {

        SessionPtr pSession("MAPI.Session");

        //To DO
		#pragma message ("TO DO: Place profile name at line 57")
        pSession->Logon("Microsoft Outlook");

        FolderPtr   pFolder = pSession->Outbox;
        MessagesPtr pMessages = pFolder->Messages;
        MessagePtr  pMessage = pMessages->Add();

        pMessage->Subject = "VCCOM: MAPI Example";
        // commsg.txt must be in same directory as the exe or else use an absolute path
        AddFileToMessage(pMessage, _T("commsg.txt"));

        AttachmentsPtr pAttachments = pMessage->Attachments;
        //To DO
        #pragma message ("TO DO: Change the absolute path to this sample code, line 69.  MUST DO.")
        pAttachments->Add("Mapi example source code.txt", 15000L, (long) mapiFileData, "d:\\samples\\com\\commail\\commail.cpp"); 
        
        RecipientsPtr pRecipients = pMessage->Recipients;
        RecipientPtr pRecipient = pRecipients->Add();
        pRecipient->Name = "KerryL";
        pRecipient->Type = (long) mapiTo;
        pRecipient->Resolve();

        pMessage->Send(false, false);
		bstr_t bstrName = pRecipient->Name;
        pSession->Logoff();
        _tprintf(_T("Successfully sent message to %s.\n"), (LPCTSTR) bstrName );

    } catch (_com_error &e) {
        dump_com_error(e);
    }
}

