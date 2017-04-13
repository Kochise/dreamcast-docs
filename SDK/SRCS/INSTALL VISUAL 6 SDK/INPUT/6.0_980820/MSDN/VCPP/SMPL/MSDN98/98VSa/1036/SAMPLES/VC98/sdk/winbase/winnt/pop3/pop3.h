
/******************************************************************************\
*       This is a part of the Microsoft Source Code Samples.
*       Copyright (C) 1992-1997 Microsoft Corporation.
*       All rights reserved. 
*       This source code is only intended as a supplement to 
*       Microsoft Development Tools and/or WinHelp documentation.
*       See these sources for detailed information regarding the 
*       Microsoft samples programs.
\******************************************************************************/

//+---------------------------------------------------------------------------
//
//  File:       pop3.h
//
//  Contents:
//
//  Classes:
//
//  Functions:
//
//----------------------------------------------------------------------------

#ifndef __POP3_H__
#define __POP3_H__


////////////////////////////////////////////////////////////////////////////
//
//
//  Strings for the protocol:
//
//
////////////////////////////////////////////////////////////////////////////

#define POP3_GOOD_RESPONSE  "+OK"
#define POP3_BAD_RESPONSE   "-ERR"

#define POP3_SUCCESS(psz)   (*((char *)psz) == '+')
#define POP3_FAILURE(psz)   (*((char *)psz) == '-')

#define POP3_CONTINUE_RESPONSE  "+CONT"


#define POP3_HELO           "HELO"
#define POP3_USER           "USER"
#define POP3_PASS           "PASS"
#define POP3_QUIT           "QUIT"
#define POP3_STAT           "STAT"
#define POP3_LIST           "LIST"
#define POP3_RETR           "RETR"
#define POP3_DELE           "DELE"
#define POP3_NOOP           "NOOP"
#define POP3_LAST           "LAST"
#define POP3_RSET           "RSET"

#define POP3_EHLO           "EHLO"
#define POP3_AUTH           "AUTH"

#define POP3_HELO_ARG       ""
#define POP3_USER_ARG       "%s"
#define POP3_PASS_ARG       "%s"
#define POP3_QUIT_ARG       ""
#define POP3_STAT_ARG       ""
#define POP3_LIST_ARG       "%d"
#define POP3_RETR_ARG       "%d"
#define POP3_DELE_ARG       "%d"
#define POP3_NOOP_ARG       ""
#define POP3_LAST_ARG       ""
#define POP3_RSET_ARG       ""

#define POP3_EHLO_ARG       ""
#define POP3_AUTH_ARG       "%d"

#define POP3_HELO_ID        0
#define POP3_USER_ID        1
#define POP3_PASS_ID        2
#define POP3_QUIT_ID        3
#define POP3_STAT_ID        4
#define POP3_LIST_ID        5
#define POP3_RETR_ID        6
#define POP3_DELE_ID        7
#define POP3_NOOP_ID        8
#define POP3_LAST_ID        9
#define POP3_RSET_ID        10

#define POP3_EHLO_ID        11
#define POP3_AUTH_ID        12

#define MAX_POP3_COMMAND    11
#define POP3_COMMAND_LENGTH 5       // 4 chars and a space

#endif
