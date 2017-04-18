/*****************************************************************************/
/* RUI Sample Program                                                        */
/*                                                                           */
/* (C) Copyright 1990 - 1993 Data Connection Ltd.                            */
/*                                                                           */
/* This program is a crude 3270 emulator.  It uses the RUI API to access     */
/* both the SSCP and LU sessions.  Outbound data from the host is            */
/* displayed on the screen unformatted.  Both SSCP and LU data are shown.    */
/* If the outbound data is an RQD request an automatic positive response     */
/* is sent.  Inbound data can be entered at the keyboard and is sent on      */
/* the current session.  This current session can be toggled between the     */
/* SSCP and LU sessions by hitting the [ (left square bracket) key           */
/* followed by <cr> (carriage return), although it switches                  */
/* automatically on receipt of BIND or UNBIND.                               */
/*                                                                           */
/* The program is invoked with a single parameter - the name of the LUA LU   */
/* to use.  This is converted to upper case and must match an LUA LU in      */
/* the configuration file.  This LU should be configured for a 327? on the   */
/* host.                                                                     */
/*                                                                           */
/* It works reasonably well with TSO provided that complex formatted         */
/* logon screens are not used.                                               */
/*                                                                           */
/* To exit the program type ] (right square bracket)                         */
/*                                                                           */
/* The CSV CONVERT function is used to convert data between ASCII and        */
/* EBCDIC.  This uses the type G conversion table, so the environment        */
/* variable COMTBLG must be set to point to a suitable file.                 */
/*                                                                           */
/* Keys that work are:                                                       */
/*                                                                           */
/*     Alt-1 to Alt-0 are PF1 to PF0                                         */
/*     F2 sends a CLEAR to the host                                          */
/*     backspace                                                             */
/*     Letters, numbers and symbols                                          */
/*                                                                           */
/*****************************************************************************/


#ifdef WIN32
  #include <windows.h>
#else
#ifdef DOS5
  #define INCL_DOS
  #define INCL_DOSERRORS
  #include <os2.h>
#else
#define FAR far
typedef unsigned int   BOOL;
typedef int            INT;
typedef unsigned int   UINT;
typedef unsigned long  ULONG;
typedef long           LONG;
typedef unsigned char  UCHAR;
typedef unsigned short USHORT;
#define TRUE    1
#define FALSE   0
#define kbhit   _kbhit
#define getch   _getche
#endif
#endif

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <conio.h>
#include <lua_c.h>
#include <acssvcc.h>


/*****************************************************************************/
/* Program constants                                                         */
/*****************************************************************************/
#define DATASIZE 4096                  /* Max size of RU                     */
#define SWITKEY  0x5B                  /* '['   to switch sessions           */
#define EXITKEY  0x5D                  /* ']'   to exit program              */

#define BETB     1                     /* Between brackets                   */
#define SEND     2                     /* In bracket and can send            */
#define RECV     3                     /* In bracket, but cannot send        */


/*****************************************************************************/
/* State variables                                                           */
/*                                                                           */
/* We can only have one read or write verb outstanding per flow.  These      */
/* state variables keep track of these verbs and what we need to do with     */
/* them.                                                                     */
/*****************************************************************************/

UINT  write_state;
#define NO_WRITE              1
#define WRITE_OUTSTANDING     2        /* waiting for write to complete      */
#define WRITE_QUEUED          3        /* have data to write                 */

UINT  read_state;
#define NO_READ               1
#define READ_OUTSTANDING      2        /* read verb outstanding              */
#define RSP_QUEUED            3        /* have a response to write           */
#define RSP_OUTSTANDING       4        /* waiting for a response to complete */

UINT  rpq_state;
#define NO_RPQ                1
#define RPQ_OUTSTANDING       2        /* waiting for an RPQ to complete     */
#define RPQ_QUEUED            3        /* have RPQ to send                   */

/***************************************************************************/
/* Global variables                                                        */
/*                                                                         */
/* Inbound data is sent as typed on the SSCP session.  On the LU session   */
/* it is prefixed with the <enter> key AID plus a two byte cursor address. */
/***************************************************************************/
LUA_VERB_RECORD read_verb;             /* RUI read verb                    */
LUA_VERB_RECORD other_verb;            /* RUI init, write or term verb     */
LUA_VERB_RECORD rpq_verb;              /* RUI_WRITE for RPQs               */

UCHAR rpq_data[] = {

  0x88,
  0x00, 0x0C, 0x81, 0x80, 0x80, 0x81, 0x85, 0x86, 0x87, 0x88, 0x95, 0xA6,

  0x00, 0x17, 0x81, 0x81, 0x21, 0x00, 0x00, 0x50, 0x00, 0x18, 0x00, 0x00,
  0x0A, 0x02, 0xE5, 0x00, 0x02, 0x00, 0x6F, 0x09, 0x10, 0x07, 0x80,

  0x00, 0x14, 0x81, 0x85, 0x02, 0x00, 0x09, 0x0E, 0x00, 0x00, 0x00, 0x00,
  0x07, 0x00, 0x00, 0x00, 0x02, 0xB9, 0x01, 0x1D,

  0x00, 0x16, 0x81, 0x86, 0x00, 0x08, 0x00, 0xF4, 0xF1, 0x00, 0xF2, 0x00,
  0xF3, 0x00, 0xF4, 0x00, 0xF5, 0x00, 0xF6, 0x00, 0xF7, 0x00,

  0x00, 0x0D, 0x81, 0x87, 0x04, 0x00, 0xF0, 0xF1, 0x00, 0xF2, 0x00, 0xF4,
  0x00,

  0x00, 0x07, 0x81, 0x88, 0x00, 0x01, 0x02,

  0x00, 0x0C, 0x81, 0x95, 0x00, 0x00, 0x7F, 0xFF, 0x7F, 0xFF, 0x01, 0x01,

  0x00, 0x11, 0x81, 0xA6, 0x00, 0x00, 0x0B, 0x01, 0x00, 0x00, 0x50, 0x00,
  0x18, 0x00, 0x50, 0x00, 0x18};

#define RPQ_LENGTH (sizeof(rpq_data))




unsigned char read_data[DATASIZE];     /* Outbound RU                       */
#define WRITE_EXTRA 6
unsigned char write_array[DATASIZE + WRITE_EXTRA] =
                                          {0x7d, 0x40, 0x40, 0x11, 0x40, 0x40};
                                       /* Inbound RU                         */
unsigned char *write_data = write_array + WRITE_EXTRA;
                                       /* Pointer to inbound RU              */
UINT data_offset = 0;                  /* offset into read_data              */
UINT write_len   = 0;                  /* length of write data               */

struct convert convert_to_asc;         /* Outbound convert verb              */
struct convert convert_to_ebc;         /* Inbound convert verb               */

#ifdef WIN32
  HANDLE write_event = 0l;             /* write arm verb semaphore           */
  HANDLE read_event  = 0l;             /* read arm verb semaphore            */
  HANDLE init_event  = 0l;             /* RUI_INIT semaphore                 */
  HANDLE term_event  = 0l;             /* RUI_TERM semaphore                 */
  HANDLE rpq_event   = 0l;
  HANDLE status_event = 0l;            /* RUI status event                   */
  HANDLE std_input;                    /* standard input handle              */
  HANDLE std_output;                   /* standard output handle             */
#else
  ULONG write_sema4 = 0l;              /* write arm verb semaphore           */
  ULONG read_sema4  = 0l;              /* read arm verb semaphore            */
  ULONG init_sema4  = 0l;              /* RUI_INIT semaphore                 */
  ULONG term_sema4  = 0l;              /* RUI_TERM semaphore                 */
  ULONG rpq_sema4   = 0l;
#endif

BOOL terminating = FALSE;              /* are we already in closedown() ?    */
BOOL lu_session  = FALSE;              /* LU session inbound flag            */

unsigned long sense = 0l;              /* sense code                         */

unsigned char lu_name[9] = "        "; /* LU name                            */
unsigned long sid;                     /* RUI session ID                     */
int send_state = BETB;                 /* LU session send state              */


#ifdef WIN32
  #define INITPOST         (ULONG) init_event
  #define TERMPOST         (ULONG) term_event
  #define READPOST         (ULONG) read_event
  #define WRITEPOST        (ULONG) write_event
  #define RPQPOST          (ULONG) rpq_event
#else
  #define INITPOST         (unsigned long) ((UCHAR FAR *) &init_sema4)
  #define TERMPOST         (unsigned long) ((UCHAR FAR *) &term_sema4)
  #define READPOST         (unsigned long) ((UCHAR FAR *) &read_sema4)
  #define WRITEPOST        (unsigned long) ((UCHAR FAR *) &write_sema4)
  #define RPQPOST          (unsigned long) ((UCHAR FAR *) &rpq_sema4)
#endif


/*****************************************************************************/
/* Function declarations.                                                    */
/*****************************************************************************/

#ifdef WIN32
  #define LOADDS
#else
  #define LOADDS _loadds
#endif

void pascal far LOADDS RUI (LUA_VERB_RECORD FAR *);

void            csv_init            (void);
int             issue_verb          (unsigned int  type);
void            issue_read          (void);
void            other_done          (LUA_VERB_RECORD *verb);
void            read_done           (LUA_VERB_RECORD *verb);
void            issue_rsp           (unsigned long  sense);
void            rsp_done            (LUA_VERB_RECORD *verb);
void            closedown           (void);
BOOL            do_write            (void);
void            wait_verb_complete  (LUA_VERB_RECORD *verb);
void            wait_active_status  (LUA_VERB_RECORD *verb);
void            set_semaphore       (LUA_VERB_RECORD *verb);
BOOL            do_keyboard_stuff   (void);
BOOL            check_verb_complete (LUA_VERB_RECORD *verb);
void            parse_data          (UCHAR FAR *, USHORT);
BOOL            issue_rpq           (void);
#ifdef WIN32
extern int      WINAPI GetFmiReturnCode(unsigned short, unsigned short, unsigned short, unsigned char FAR *);
#endif

/**PROC+**********************************************************************/
/* Name:      main                                                           */
/*                                                                           */
/* Purpose:   set up CSV convert verbs                                       */
/*                                                                           */
/* Returns:   none                                                           */
/*                                                                           */
/* Params:    argv, argc                                                     */
/*                                                                           */
/* Operation: Get LU name from command line                                  */
/*            do some initialisation                                         */
/*            Issue RUI_INIT to get LU-SSCP session                          */
/*            Loop reading data from keyboard and host, and send keyboard    */
/*            data to host                                                   */
/**PROC-**********************************************************************/
#ifdef DOS5
int main(int argc, char *argv[])
#else
#ifdef PDOS
int _cdecl main(int argc, char *argv[])
#else
int _CRTAPI1 main(int argc, char *argv[])
#endif
#endif
{
  BOOL whole_data;       /* we have a whole data string to write             */
  BOOL verb_complete;    /* Has a verb completed                             */
  BOOL write_ok;         /* Has write worked?                                */
  BOOL rpq_ok;           /* Has rpq worked                                   */
  int ii;
#ifdef WIN32
  HANDLE handle_list [6];
#endif
#ifdef DOS5
  DEFINEMUXSEMLIST(sem_list,5)
  USHORT           sem_index;
#endif

  printf("RUI simple 3270 application\n");

  /***************************************************************************/
  /* Validate parameter usage and get LU name.                               */
  /***************************************************************************/
  if (argc != 2)
  {
    printf("Usage: RUI3270 luname\n");
    exit(1);
  }
  if (strlen(argv[1]) > 8)
  {
    printf("LU name too long\n");
    exit(1);
  }

  /***************************************************************************/
  /* Convert to upper case                                                   */
  /***************************************************************************/
  ii=0;
  while (argv[1][ii])
  {
    if (argv[1][ii] >= 'a' && argv[1][ii] <= 'z')
    {
      argv[1][ii] = argv[1][ii] - 'a' + 'A';
    }
    ii++;
  }
  memcpy(lu_name, argv[1], strlen(argv[1]));
  printf("lu_name %s\n", lu_name);

  /***************************************************************************/
  /* Set up CSV convert verbs                                                */
  /***************************************************************************/
  csv_init();

#ifdef WIN32
  /***************************************************************************/
  /* Create the necessary events                                             */
  /***************************************************************************/
  write_event  = CreateEvent (NULL, TRUE, FALSE, NULL);
  read_event   = CreateEvent (NULL, TRUE, FALSE, NULL);
  init_event   = CreateEvent (NULL, TRUE, FALSE, NULL);
  term_event   = CreateEvent (NULL, TRUE, FALSE, NULL);
  rpq_event    = CreateEvent (NULL, TRUE, FALSE, NULL);
  status_event = CreateEvent (NULL,FALSE, FALSE, NULL);


  /***************************************************************************/
  /* Get standard input and output handles.                                  */
  /***************************************************************************/
  std_input  = GetStdHandle (STD_INPUT_HANDLE );
  std_output = GetStdHandle (STD_OUTPUT_HANDLE);
  if ((std_input  == INVALID_HANDLE_VALUE) ||
      (std_output == INVALID_HANDLE_VALUE))
  {
    printf("GetStdHandle Failed, %d", GetLastError());
    exit (1);
  }

  /***************************************************************************/
  /* Set up list of handles to wait for                                      */
  /***************************************************************************/
  handle_list[0] = write_event;
  handle_list[1] = read_event;
  handle_list[2] = init_event;
  handle_list[3] = term_event;
  handle_list[4] = rpq_event;
  handle_list[5] = std_input;
#endif
#ifdef DOS5
  /***************************************************************************/
  /* Set semaphores to begin with                                            */
  /***************************************************************************/
  DosSemSet (&init_sema4);
  DosSemSet (&term_sema4);
  DosSemSet (&read_sema4);
  DosSemSet (&write_sema4);
  DosSemSet (&rpq_sema4);

  sem_list.amxs[0].hsem = &init_sema4;
  sem_list.amxs[1].hsem = &term_sema4;
  sem_list.amxs[2].hsem = &read_sema4;
  sem_list.amxs[3].hsem = &write_sema4;
  sem_list.amxs[4].hsem = &rpq_sema4;
#endif

  /***************************************************************************/
  /* Initialize RUI and wait for ACTLU fom host.                             */
  /***************************************************************************/
  if (issue_verb((unsigned int) LUA_OPCODE_RUI_INIT))
  {
    printf("Init failed\n");
    exit(1);
  }

  /***************************************************************************/
  /* Set initial states                                                      */
  /***************************************************************************/
  write_state = NO_WRITE;
  read_state  = NO_READ;
  rpq_state   = NO_RPQ;

  /***************************************************************************/
  /* Loop reading inbound data from the keyboard                             */
  /***************************************************************************/
  while (!terminating)
  {
#ifndef PDOS
    /*************************************************************************/
    /* Determine if we can pause                                             */
    /*************************************************************************/
    if (  (read_state != NO_READ)   &&

          ((write_state != WRITE_QUEUED)    ||
           (rpq_state   != NO_RPQ)          ||
           (read_state  == RSP_OUTSTANDING) ||
           (read_state  == RSP_QUEUED)) &&

          ((rpq_state   != RPQ_QUEUED)        ||
           (write_state == WRITE_OUTSTANDING) ||
           (read_state  == RSP_OUTSTANDING)   ||
           (read_state  == RSP_QUEUED))    &&

          ((read_state != RSP_QUEUED) ||
           (write_state == WRITE_OUTSTANDING)))
    {
#ifdef WIN32
      WaitForMultipleObjects (6, handle_list, FALSE, INFINITE);
#else
      if (!kbhit())
      {
        DosMuxSemWait (&sem_index, &sem_list, 200l);
      }
#endif
    }
#endif

    /*************************************************************************/
    /* First check on the state of write verbs                               */
    /*************************************************************************/
    if ((write_state == NO_WRITE)        &&
        (rpq_state   == NO_RPQ)          &&
        (read_state  != RSP_QUEUED)      &&
        (read_state  != RSP_OUTSTANDING))
    {
      /***********************************************************************/
      /* Don't write here if we need to respond, since we can only have one  */
      /* write outstanding on each flow.                                     */
      /* Here we want to check if we have a whole string of data (i.e.  that */
      /* the user has hit enter).  If so write the data to the HOST          */
      /***********************************************************************/
      whole_data = do_keyboard_stuff ();
      if (whole_data)
      {
        /*********************************************************************/
        /* Attempt to write the data.  May not work because of bracket state */
        /*********************************************************************/

        write_ok = do_write ();
        if (write_ok)
        {
          /*******************************************************************/
          /* If verb completes async change state to indicate this o.w.      */
          /* call the verb done processor                                    */
          /*******************************************************************/
          if (other_verb.common.lua_flag2.async)
          {
            write_state = WRITE_OUTSTANDING;
          }
          else
          {
            other_done (&other_verb);
            write_state = NO_WRITE;
          }
        }
        else
        {
          /*******************************************************************/
          /* Failed to do a write.  Queue up data                            */
          /*******************************************************************/
          write_state = WRITE_QUEUED;
        }
      }
    }
    else if ((write_state == WRITE_QUEUED)    &&
             (rpq_state   == NO_RPQ)          &&
             (read_state  != RSP_OUTSTANDING) &&
             (read_state  != RSP_QUEUED))
    {
      /***********************************************************************/
      /* Attempt to write the data.  May not work because of bracket state   */
      /***********************************************************************/
      write_ok = do_write ();
      if (write_ok)
      {
        /*********************************************************************/
        /* If verb completes async change state to indicate this o.w.  call  */
        /* the verb done processor                                           */
        /*********************************************************************/
        if (other_verb.common.lua_flag2.async)
        {
          write_state = WRITE_OUTSTANDING;
        }
        else
        {
          other_done (&other_verb);
          write_state = NO_WRITE;
        }
      }

    }
    else if (write_state == WRITE_OUTSTANDING)
    {
      /***********************************************************************/
      /* We have a RUI_WRITE outstanding so check if it is complete          */
      /***********************************************************************/
      verb_complete = check_verb_complete (&other_verb);
      if (verb_complete)
      {
        other_done (&other_verb);
        write_state = NO_WRITE;
      }
    }



    /*************************************************************************/
    /* Now check the RPQ state                                               */
    /*************************************************************************/
    if ((rpq_state   == RPQ_QUEUED)        &&
        (write_state != WRITE_OUTSTANDING) &&
        (read_state  != RSP_OUTSTANDING)   &&
        (read_state  != RSP_QUEUED))
    {
      /***********************************************************************/
      /* We have an RPQ queued up.  Try to send it                           */
      /***********************************************************************/
      rpq_ok = issue_rpq ();
      if (rpq_ok)
      {
        /*********************************************************************/
        /* If verb completes async change state to indicate this o.w.  call  */
        /* the verb done processor                                           */
        /*********************************************************************/
        if (rpq_verb.common.lua_flag2.async)
        {
          rpq_state = WRITE_OUTSTANDING;
        }
        else
        {
          other_done (&rpq_verb);
          write_state = NO_RPQ;
        }
      }
    }
    else if (rpq_state == RPQ_OUTSTANDING)
    {
      /***********************************************************************/
      /* Check for verb completion                                           */
      /***********************************************************************/
      verb_complete = check_verb_complete (&rpq_verb);
      if (verb_complete)
      {
        other_done (&rpq_verb);
        rpq_state = NO_RPQ;
      }

    }



    /*************************************************************************/
    /* Now check on read verbs                                               */
    /*************************************************************************/
    if (read_state == NO_READ)
    {
      issue_read ();
      if (read_verb.common.lua_flag2.async)
      {
        read_state = READ_OUTSTANDING;
      }
      else
      {
        /*********************************************************************/
        /* read_done will change read_state to RESPONSE_QUEUED or NO_READ    */
        /*********************************************************************/
        read_done (&read_verb);
      }
    }
    else if (read_state == READ_OUTSTANDING)
    {
      verb_complete = check_verb_complete (&read_verb);
      if (verb_complete)
      {
        /*********************************************************************/
        /* read_done will change read_state to RESPONSE_QUEUED or NO_READ    */
        /*********************************************************************/
        read_done (&read_verb);
      }
    }
    else if (read_state == RSP_QUEUED)
    {
      /***********************************************************************/
      /* We need to respond to a message read.  Do a write if one is         */
      /* availible.                                                          */
      /***********************************************************************/
      if (write_state != WRITE_OUTSTANDING)
      {
        /*********************************************************************/
        /* The response is issued using the read_verb                        */
        /*********************************************************************/
        issue_rsp (sense);
        if (read_verb.common.lua_flag2.async)
        {
          read_state = RSP_OUTSTANDING;
        }
        else
        {
          rsp_done (&read_verb);
          read_state = NO_READ;
        }
      }
    }
    else if (read_state == RSP_OUTSTANDING)
    {
      /***********************************************************************/
      /* Check to see if the response is complete                            */
      /***********************************************************************/
      verb_complete = check_verb_complete (&read_verb);
      if (verb_complete)
      {
        rsp_done (&read_verb);
        read_state = NO_READ;
      }
    }
    else
    {
      /***********************************************************************/
      /* Invalid state                                                       */
      /***********************************************************************/
      printf("invalid state");
    }

  }  /* while not terminating                                                */

  return(0);
}  /* main ()                                                                */


/**PROC+**********************************************************************/
/* Name:      csv_init                                                       */
/*                                                                           */
/* Purpose:   set up CSV convert verbs                                       */
/*                                                                           */
/* Returns:   void                                                           */
/*                                                                           */
/* Params:    none                                                           */
/*                                                                           */
/* Operation: sets uup two CSV convert verbs, one in each direction.  Only   */
/* the length needs to be set when the verb is called                        */
/**PROC-**********************************************************************/
void csv_init (void)
{
  convert_to_asc.opcode       = SV_CONVERT;
  convert_to_asc.direction    = SV_EBCDIC_TO_ASCII;
  convert_to_asc.char_set     = SV_G;
  convert_to_asc.source       = read_data;
  convert_to_asc.target       = read_data;

  convert_to_ebc.opcode       = SV_CONVERT;
  convert_to_ebc.direction    = SV_ASCII_TO_EBCDIC;
  convert_to_ebc.char_set     = SV_G;
  convert_to_ebc.source       = write_data;
  convert_to_ebc.target       = write_data;
}  /* csv_init                                                               */


/**PROC+**********************************************************************/
/* Name:      issue_verb                                                     */
/*                                                                           */
/* Purpose:   build a verb and send it                                       */
/*                                                                           */
/* Returns:   int - non-zero => verb failed                                  */
/*                                                                           */
/* Params:    IN type - type of verb to issue                                */
/*                                                                           */
/* Operation: Build an INIT or TERM verb and issue it.  Wait for the verb    */
/*            to complete                                                    */
/**PROC-**********************************************************************/
int issue_verb(type)
unsigned int  type;
{

  memset(&other_verb, 0, sizeof(other_verb));
  other_verb.common.lua_verb             = LUA_VERB_RUI;
  other_verb.common.lua_verb_length      = sizeof(other_verb);
  other_verb.common.lua_opcode           = type;
  if (type == LUA_OPCODE_RUI_INIT)
  {
    memcpy(other_verb.common.lua_luname, lu_name, 8);
    other_verb.common.lua_post_handle    = INITPOST;
  }
  else
  {
    other_verb.common.lua_sid            = sid;
    other_verb.common.lua_post_handle    = TERMPOST;
  }
  RUI((LUA_VERB_RECORD FAR *) &other_verb);

#ifdef WIN32
  if (type == LUA_OPCODE_RUI_INIT)
  {
    WinRUIGetLastInitStatus(0, status_event, WLUA_NTFY_EVENT, 0);
  }
#endif

  if (other_verb.common.lua_flag2.async)
  {
#ifdef WIN32
    if (type == LUA_OPCODE_RUI_INIT)
    {
      wait_active_status (&other_verb);
      wait_verb_complete (&other_verb);
    }
    else
#endif
    {
      wait_verb_complete (&other_verb);
    }
  }
  other_done(&other_verb);

  return(other_verb.common.lua_prim_rc != LUA_OK);
}  /* issue_verb                                                             */


/**PROC+**********************************************************************/
/* Name:      issue_read                                                     */
/*                                                                           */
/* Purpose:   build a read verb and send it                                  */
/*                                                                           */
/* Returns:   void                                                           */
/*                                                                           */
/* Params:    none                                                           */
/*                                                                           */
/* Operation: Build a read verb for all flows and issue it                   */
/**PROC-**********************************************************************/
void issue_read (void)
{
  memset(&read_verb, 0, sizeof(read_verb));
  memset(read_data, 0, DATASIZE);
  read_verb.common.lua_verb             = LUA_VERB_RUI;
  read_verb.common.lua_verb_length      = sizeof(read_verb);
  read_verb.common.lua_opcode           = LUA_OPCODE_RUI_READ;
  read_verb.common.lua_sid              = sid;
  read_verb.common.lua_max_length       = DATASIZE;
  read_verb.common.lua_data_ptr         = (char *) read_data;
  read_verb.common.lua_post_handle      = READPOST;
  read_verb.common.lua_flag1.lu_norm    = 1;
  read_verb.common.lua_flag1.lu_exp     = 1;
  read_verb.common.lua_flag1.sscp_norm  = 1;
  read_verb.common.lua_flag1.sscp_exp   = 1;
  RUI((LUA_VERB_RECORD FAR *)&read_verb);

}  /* issue_read                                                             */


/**PROC+**********************************************************************/
/* Name:      other_done                                                     */
/*                                                                           */
/* Purpose:   handle completed init, write or term verb                      */
/*                                                                           */
/* Returns:   void                                                           */
/*                                                                           */
/* Params:    IN verb - completed verb                                       */
/*                                                                           */
/* Operation: write status to he screen                                      */
/**PROC-**********************************************************************/
void other_done(verb)
LUA_VERB_RECORD *verb;
{
  switch (verb->common.lua_opcode)
  {
    case LUA_OPCODE_RUI_INIT:
         if (verb->common.lua_prim_rc == LUA_OK)
         {
           printf("LU active\n");
           sid = verb->common.lua_sid;
         }
         else
         {
           printf("INIT failed, (%4.4x, %8.8lx)\n",
                  verb->common.lua_prim_rc, verb->common.lua_sec_rc);
         }
         break;

    case LUA_OPCODE_RUI_WRITE:
         if (verb->common.lua_prim_rc != LUA_OK)
         {
           printf("WRITE failed, (%4.4x, %8.8lx)\n",
                  verb->common.lua_prim_rc, verb->common.lua_sec_rc);
         }
         break;

    case LUA_OPCODE_RUI_TERM:
         printf("Terminated\n");
         break;

  }
}  /* other_done                                                             */


/**PROC+**********************************************************************/
/* Name:      read_done                                                      */
/*                                                                           */
/* Purpose:   handle completed read verb                                     */
/*                                                                           */
/* Returns:   void                                                           */
/*                                                                           */
/* Params:    IN verb - completed read verb                                  */
/*                                                                           */
/* Operation: If the completed verb contains data, first parse it and then   */
/*            display it.                                                    */
/*            If message is a BIND or an UNBIND, set the LU-LU session state */
/*            accordingly                                                    */
/*            Also check for EB, CD and change session state flags           */
/**PROC-**********************************************************************/
void read_done(verb)
LUA_VERB_RECORD *verb;
{
  int            count;         /* number of bytes of data left to display   */
  unsigned char *data;          /* pointer to next data to display           */
  BOOL           rsp_required = FALSE; /* is a resonse required              */

  sense = 0l;

  if (verb->common.lua_prim_rc == LUA_OK)
  {
    if ((verb->common.lua_message_type == LUA_MESSAGE_TYPE_LU_DATA)   ||
        (verb->common.lua_message_type == LUA_MESSAGE_TYPE_SSCP_DATA))
    {
      if (verb->common.lua_data_length > 0)
      {
        /*********************************************************************/
        /* We now have to parse the data.  For the moment we only look for   */
        /* RPQ requests.                                                     */
        /*********************************************************************/
        parse_data (read_data, (USHORT) (verb->common.lua_data_length));

        /*********************************************************************/
        /* Display outbound SSCP or LU data.                                 */
        /*********************************************************************/
        convert_to_asc.len = (unsigned short) verb->common.lua_data_length;
        ACSSVC_C((LONG)((UCHAR FAR *)&convert_to_asc));
        data  = read_data;
        count = strlen(data);
        while (count > 0)
        {
          if (count <= 80)
          {
            printf("%s\n",data);
            count = 0;
          }
          else
          {
            printf("%80.80s\n",data);
            count -= 80;
            data  += 80;
          }
        }
      }

      /***********************************************************************/
      /* Set session state.                                                  */
      /***********************************************************************/
      if (verb->common.lua_rh.ebi)
      {
        printf("EB\n");
        send_state = BETB;
      }
      else if (verb->common.lua_rh.cdi)
      {
        printf("CD\n");
        send_state = SEND;
      }
      else
      {
        send_state = RECV;
      }
    }
    /*************************************************************************/
    /* Handle BIND or UNBIND as a special case.                              */
    /*************************************************************************/
    else if (verb->common.lua_message_type == LUA_MESSAGE_TYPE_BIND)
    {
      if (((read_data[6] & 0x20) == 0x20)  &&      /* Brackets used and BETB */
          ((read_data[7] & 0xF0) == 0x80)  &&      /* HDX-FF, sec con winner */
          ( read_data[14]        == 0x02))         /* LU type 2              */
      {
        printf("BIND\n");
        send_state = BETB;
        lu_session = TRUE;
      }
      else
      {
        printf("BIND rejected\n");
        sense = LUA_INVALID_SESSION_PARAMETERS;
      }
    }
    else if (verb->common.lua_message_type == LUA_MESSAGE_TYPE_UNBIND)
    {
      printf("UNBIND\n");
      send_state = BETB;
      lu_session = FALSE;
    }

    /*************************************************************************/
    /* Respond to any RQD request.                                           */
    /*************************************************************************/
    if ((verb->common.lua_message_type != LUA_MESSAGE_TYPE_RSP)  &&
        (verb->common.lua_rh.ri == 0))                  /* definite response */
    {
      rsp_required = TRUE;
    }
  }
  else         /* primary rc not OK - read failed - stop now */
  {
    printf("READ ERROR, primary rc = %4.4x, secondary rc = %8.8lx\n",
           verb->common.lua_prim_rc, verb->common.lua_sec_rc);
    closedown();
  }

  /***************************************************************************/
  /* Continue processing with either another read or a write positive rsp.   */
  /* (The callback from issuing response will then issue another read) If    */
  /* we've already gone into closedown, stop here                            */
  /***************************************************************************/
  if (!terminating)
  {
    if (rsp_required)
    {
      read_state = RSP_QUEUED;
    }
    else
    {
      read_state = NO_READ;
    }
  }
}  /* read_done                                                              */


/**PROC+**********************************************************************/
/* Name:      issue_rsp                                                      */
/*                                                                           */
/* Purpose:   issue a response for a request from the host                   */
/*                                                                           */
/* Returns:   void                                                           */
/*                                                                           */
/* Params:    IN sense - sense code for the response                         */
/*                                                                           */
/* Operation: Build a response and write it out.  Uses the read verb control */
/*            block because it has the necessary information.                */
/*                                                                           */
/**PROC-**********************************************************************/
void issue_rsp(sense)
unsigned long sense;
{
  read_verb.common.lua_opcode           = LUA_OPCODE_RUI_WRITE;
  read_verb.common.lua_max_length       = 0;
  read_verb.common.lua_post_handle      = (ULONG) READPOST;
  read_verb.common.lua_rh.rri           = 1;       /* response             */
  read_verb.common.lua_flag1.lu_norm    = 0;
  read_verb.common.lua_flag1.lu_exp     = 0;
  read_verb.common.lua_flag1.sscp_norm  = 0;
  read_verb.common.lua_flag1.sscp_exp   = 0;

  /***************************************************************************/
  /* If we have been given a sense code this must be a negative response     */
  /***************************************************************************/
  if (sense)
  {
    read_verb.common.lua_data_length      = 4;
    memcpy(read_data, &sense, 4);
    read_verb.common.lua_rh.ri            = 1;       /* negative rsp         */
  }
  else
  {
    read_verb.common.lua_data_length      = 0;
    read_verb.common.lua_rh.ri            = 0;       /* positive rsp         */
  }
  /***************************************************************************/
  /* Send the response back on the flow from which the request came          */
  /***************************************************************************/
  if (read_verb.common.lua_flag2.lu_norm)
  {
    read_verb.common.lua_flag1.lu_norm = 1;
  }
  else if (read_verb.common.lua_flag2.lu_exp)
  {
    read_verb.common.lua_flag1.lu_exp = 1;
  }
  else if (read_verb.common.lua_flag2.sscp_norm)
  {
    read_verb.common.lua_flag1.sscp_norm = 1;
  }
  else if (read_verb.common.lua_flag2.sscp_exp)
  {
    read_verb.common.lua_flag1.sscp_exp = 1;
  }
  /***************************************************************************/
  /* Send out the verb                                                       */
  /***************************************************************************/
  RUI((LUA_VERB_RECORD FAR *)&read_verb);              /* write the response */
}  /* issue_rsp                                                              */


/**PROC+**********************************************************************/
/* Name:      rsp_done                                                       */
/*                                                                           */
/* Purpose:   handle completion of RUI_WRITE, when RUI_WRITE has written a   */
/*            response                                                       */
/*                                                                           */
/* Returns:   void                                                           */
/*                                                                           */
/* Params:    IN verb - completed verb                                       */
/*                                                                           */
/* Operation: If verb did not complete OK print a message and terminate      */
/*                                                                           */
/**PROC-**********************************************************************/
void rsp_done (verb)
LUA_VERB_RECORD *verb;
{
  if (verb->common.lua_prim_rc != LUA_OK)   /* failed to write the response */
  {                                         /* so stop here                 */
    printf("WRITE for response failed, (%4.4x, %8.8lx)\n",
            verb->common.lua_prim_rc, verb->common.lua_sec_rc);
    closedown();
  }
}  /* rsp_done                                                               */


/**PROC+**********************************************************************/
/* Name:      closedown                                                      */
/*                                                                           */
/* Purpose:   terminate the application cleanly                              */
/*                                                                           */
/* Returns:   void                                                           */
/*                                                                           */
/* Params:    none                                                           */
/*                                                                           */
/* Operation: Issue an RUI_TERM and wait for it to complete.  Then exit      */
/*                                                                           */
/**PROC-**********************************************************************/
void closedown (void)
{
  if (!terminating)                /* check we haven't already got here from */
  {                                /* another section of the code            */
    terminating = TRUE;            /* then make sure we can't get here again */
    printf("Closedown\n");
    if (issue_verb((unsigned int) LUA_OPCODE_RUI_TERM))
    {
      exit(1);
    }
    exit(0);
  }
}  /* closedown                                                              */


/**PROC+**********************************************************************/
/* Name:      check_verb_complete                                            */
/*                                                                           */
/* Purpose:   check for asynchronous verb completion                         */
/*                                                                           */
/* Returns:   BOOL - TRUE => verb has completed                              */
/*                                                                           */
/* Params:    IN - verb - pointer to verb control block                      */
/*                                                                           */
/* Operation: OS specific                                                    */
/*                                                                           */
/**PROC-**********************************************************************/
BOOL check_verb_complete (verb)

LUA_VERB_RECORD * verb;
{
#ifdef DOS5
  /***************************************************************************/
  /* OS/2 case.  The verb is complete when the semaphore is cleared          */
  /***************************************************************************/
  USHORT RetCode;                     /* Holds return code from OS calls     */
  BOOL   verb_complete;               /* Has the verb completed              */

  verb_complete = FALSE;

  RetCode = DosSemRequest ((HSEM) verb->common.lua_post_handle, 0l);

  if (RetCode != NO_ERROR)
  {
    if (RetCode != ERROR_SEM_TIMEOUT)
    {
      /***********************************************************************/
      /* If we get here we've got problems                                   */
      /***********************************************************************/
      printf("Bad DosSemRequest return code, %d", RetCode);
    }
  }
  else
  {
    verb_complete = TRUE;
    set_semaphore (verb);
  }

  return(verb_complete);
#endif

#ifdef PDOS
  /***************************************************************************/
  /* DOS case.  The verb is complete when the lua_post_handle is cleared     */
  /***************************************************************************/
  BOOL   verb_complete;               /* Has the verb completed              */

  verb_complete = FALSE;

  if (!verb->common.lua_post_handle)
  {
    verb_complete = TRUE;
    set_semaphore (verb);
  }

  return(verb_complete);
#endif

#ifdef WIN32
  /***************************************************************************/
  /* Win32 case.  The verb is complete when the semaphore is cleared         */
  /***************************************************************************/
  DWORD  RetCode;

  RetCode = WaitForSingleObject((HANDLE) verb->common.lua_post_handle, 0l);

  if (RetCode == 0)
  {
    set_semaphore (verb);
  }
  return((RetCode == 0));
#endif
}  /* check_verb_complete                                                    */

#ifdef WIN32
/**PROC+**********************************************************************/
/* Name:      wait_active_status                                             */
/*                                                                           */
/* Purpose:   waits for status to become active                              */
/*                                                                           */
/* Returns:   void                                                           */
/*                                                                           */
/* Operation:                                                                */
/*                                                                           */
/**PROC-**********************************************************************/
void wait_active_status(verb)

LUA_VERB_RECORD * verb ;
{
  DWORD RetCode;
  DWORD Status = 0;
  char status_buff[80];

  while (Status != WLUALUACTIVE)
  {
    RetCode = WaitForSingleObject(status_event,(DWORD)-1);
    Status = WinRUIGetLastInitStatus(verb->common.lua_sid, NULL, WLUA_NTFY_EVENT, 0);
    GetFmiReturnCode((unsigned short)Status,(unsigned short) 0xffff,(unsigned short) 80, status_buff);
    printf("%s\n",status_buff);
  }
  printf("LU ACT received\n");

}
#endif


/**PROC+**********************************************************************/
/* Name:      wait_verb_complete                                             */
/*                                                                           */
/* Purpose:   waits for async verb completion                                */
/*                                                                           */
/* Returns:   void                                                           */
/*                                                                           */
/* Params:    IN - verb - pointer to verb control block                      */
/*                                                                           */
/* Operation: Wait for the lua_post_handle to become clear                   */
/*                                                                           */
/**PROC-**********************************************************************/
void wait_verb_complete (verb)

LUA_VERB_RECORD * verb ;
{
#ifdef DOS5
  USHORT RetCode;                     /* Holds return code from OS calls     */

  RetCode = DosSemRequest ((HSEM)verb->common.lua_post_handle, -1l);
#endif

#ifdef PDOS
  while (verb->common.lua_post_handle);
#endif

#ifdef WIN32
  DWORD RetCode;

  RetCode = WaitForSingleObject((HANDLE)verb->common.lua_post_handle,
                                                                   (DWORD)-1l);
#endif
  set_semaphore (verb);

}  /* wait_verb_complete                                                     */


/**PROC+**********************************************************************/
/* Name:      set_semaphore                                                  */
/*                                                                           */
/* Purpose:   sets verb completion flags                                     */
/*                                                                           */
/* Returns:   void                                                           */
/*                                                                           */
/* Params:    IN - verb - pointer to vcb                                     */
/*                                                                           */
/* Operation: set the lua_post_handle to the non-signaled state              */
/*                                                                           */
/**PROC-**********************************************************************/
void set_semaphore (verb)

LUA_VERB_RECORD * verb;
{
#ifdef DOS5
  USHORT RetCode;
  RetCode = DosSemSet ((HSEM)verb->common.lua_post_handle);
#endif

#ifdef PDOS
  /***************************************************************************/
  /* Dos Case.  Set lua_post_handle to 1                                     */
  /***************************************************************************/
  verb->common.lua_post_handle = 1l;
#endif

#ifdef WIN32
  /*W32***********************************************************************/
  /*W32* Win 32 case.  Clear the event                                       */
  /*W32***********************************************************************/
  ResetEvent ((HANDLE) verb->common.lua_post_handle);
#endif
}  /* set_semaphore                                                          */


/**PROC+**********************************************************************/
/* Name:      do_keyboard_stuff                                              */
/*                                                                           */
/* Purpose:   poll keyboard for data                                         */
/*                                                                           */
/* Returns:   BOOL - TRUE => we have data to send                            */
/*                                                                           */
/* Params:    none                                                           */
/*                                                                           */
/* Operation: poll keyboard                                                  */
/*            if some data                                                   */
/*              read it in                                                   */
/*              add it to data buffer                                        */
/*              if data is <enter>                                           */
/*                return TRUE                                                */
/*              endif                                                        */
/*            endif                                                          */
/*            return false                                                   */
/*                                                                           */
/* Also keep track of which session is being used, and if user wishes to     */
/* exit.                                                                     */
/*                                                                           */
/**PROC-**********************************************************************/
BOOL do_keyboard_stuff (void)

{
  BOOL   data_to_send;             /* do we have data to send?               */
  INT    input_char;               /* an input character                     */
#ifdef WIN32
  INPUT_RECORD input_record;       /* input record                           */
  DWORD        no_read;            /* number of input records read           */
#endif

  data_to_send = FALSE;

  /***************************************************************************/
  /* Check if keyboard has been hit                                          */
  /***************************************************************************/
#ifdef WIN32
  while ((!data_to_send) &&
         (!terminating)  &&
         (PeekConsoleInput (std_input, &input_record, 1, &no_read)) &&
         (no_read > 0))
#else
  while ((!data_to_send) && (!terminating) && (kbhit()))
#endif
  {
#ifndef WIN32
    input_char = getch();
    if ((input_char == 0) || (input_char == 0xE0))
#else
    ReadConsoleInput (std_input, &input_record, 1, &no_read);


    if ((input_record.EventType == KEY_EVENT) &&
        (input_record.Event.KeyEvent.bKeyDown) &&
        ((input_record.Event.KeyEvent.dwControlKeyState == LEFT_ALT_PRESSED) ||
         ((input_record.Event.KeyEvent.wVirtualKeyCode >= VK_F1 ) &&
          (input_record.Event.KeyEvent.wVirtualKeyCode <= VK_F24))))
#endif
    {
      /***********************************************************************/
      /* Not an ascii char                                                   */
      /***********************************************************************/
#ifndef WIN32
      input_char = getch ();
#endif


      /***********************************************************************/
      /* Check for function keys and ALT-??                                  */
      /***********************************************************************/
#ifndef WIN32
      if (input_char == 60)               /* F2                              */
#else
      if (input_record.Event.KeyEvent.wVirtualKeyCode == VK_F2)
#endif
      {
        /*********************************************************************/
        /* Send a Clear.                                                     */
        /*********************************************************************/
        printf("sending clear\n");
        *write_data = 0x6d;
        write_len   = 1;
        data_to_send = TRUE;
      }
#ifndef WIN32
      else if ((input_char >= 120) && (input_char <= 129))
#else
      else if ((input_record.Event.KeyEvent.wVirtualKeyCode >= '0') &&
               (input_record.Event.KeyEvent.wVirtualKeyCode <= '9'))
#endif
      {
        /*********************************************************************/
        /* ALT-1 to ALT-0                                                    */
        /* 0xF1 is the AID code for PF1                                                              */
        /* Follow this with the cursor address                               */
        /*********************************************************************/
#ifndef WIN32
        *write_data = 0xF1 + input_char - 120;
#else
        *write_data = 0xF0 + input_record.Event.KeyEvent.wVirtualKeyCode - '0';
#endif
        *(write_data + 1) = 0x40;
        *(write_data + 2) = 0x40;
        write_len = 3;
        data_to_send = TRUE;

      }
    }
    else
#ifdef WIN32
        if ((input_record.EventType == KEY_EVENT ) &&
            (input_record.Event.KeyEvent.bKeyDown))
#endif
    {
      /***********************************************************************/
      /* An ASCII char                                                       */
      /***********************************************************************/
#ifdef WIN32
      input_char = input_record.Event.KeyEvent.uChar.AsciiChar;
#endif
      if (input_char == EXITKEY)
      {
        closedown();
      }
      else if (input_char == SWITKEY)
      {
        /*********************************************************************/
        /* Hit key to switch between sessions                                */
        /*********************************************************************/
        if (lu_session)
        {
          printf("SSCP session\n");
          lu_session = FALSE;
        }
        else
        {
          printf("LU session\n");
          lu_session = TRUE;
        }
      }
      else
      {
        /*********************************************************************/
        /* Key should be real data.  Add it to the string                    */
        /* For Windows NT echo the character to the screen                   */
        /*********************************************************************/

        if (input_char == 13)
        {
#ifdef WIN32
          WriteConsole (std_output, &input_char, 1, &no_read, NULL);
#endif
          /*******************************************************************/
          /* If user pressed return key then send the data.  Reset           */
          /* data_offset for next data.                                      */
          /*******************************************************************/
          write_data[data_offset++] = '\0';
          data_to_send = TRUE;
          data_offset  = 0;

          /*******************************************************************/
          /* Convert data to EBCDIC                                          */
          /*******************************************************************/
          convert_to_ebc.len = (unsigned short) (strlen(write_data) );
          if (convert_to_ebc.len > 0)
          {
            ACSSVC_C((LONG)((UCHAR FAR *)&convert_to_ebc));
          }
          write_len = convert_to_ebc.len;

          /*******************************************************************/
          /* Allow for ENTER AID if necessary                                */
          /*******************************************************************/
          if (lu_session)
          {
            write_data -= WRITE_EXTRA;
            write_len  += WRITE_EXTRA;
          }
        }
        else if (input_char == 8)
        {
#ifdef WIN32
          WriteConsole (std_output, &input_char, 1, &no_read, NULL);
#endif
          /*******************************************************************/
          /* Backspace.  Delete last char                                    */
          /*******************************************************************/
          if (data_offset > 0)
          {
            data_offset--;
          }
        }
        else if (input_char != 0)
        {
#ifdef WIN32
          WriteConsole (std_output, &input_char, 1, &no_read, NULL);
#endif
          write_data[data_offset++] = (UCHAR) input_char;
        }
      }
    }
  }  /* if (kbhit())                                                         */

  return(data_to_send);
}  /* do_keyboard_stuff                                                      */



/**PROC+**********************************************************************/
/* Name:      do_write                                                       */
/*                                                                           */
/* Purpose:   issue a write verb                                             */
/*                                                                           */
/* Returns:   BOOL - TRUE => data sent OK                                    */
/*                                                                           */
/* Params:    none                                                           */
/*                                                                           */
/* Operation: convert data to EBCDIC and send it on the right session        */
/*                                                                           */
/**PROC-**********************************************************************/
BOOL do_write (void)

{
  BOOL ok;

  ok = TRUE;


  /***************************************************************************/
  /* Set up the vcb                                                          */
  /***************************************************************************/
  memset(&other_verb, 0, sizeof(other_verb));
  other_verb.common.lua_verb             = LUA_VERB_RUI;
  other_verb.common.lua_verb_length      = sizeof(read_verb);
  other_verb.common.lua_opcode           = LUA_OPCODE_RUI_WRITE;
  other_verb.common.lua_sid              = sid;
  other_verb.common.lua_data_length      = write_len;
  other_verb.common.lua_data_ptr         = (char far *) write_data;
  other_verb.common.lua_post_handle      = WRITEPOST;
  other_verb.common.lua_rh.bci           = 1;
  other_verb.common.lua_rh.eci           = 1;
  other_verb.common.lua_rh.dr1i          = 1;

  if (lu_session)
  {
    /*************************************************************************/
    /* On the LU session we must add the <enter> key prefix.  All inbound    */
    /* requests flow RQE with the BBI and CDI flags set depending on the     */
    /* current session state.                                                */
    /*************************************************************************/
    other_verb.common.lua_flag1.lu_norm  = 1;
    other_verb.common.lua_rh.ri          = 1;
    if (send_state == BETB)
    {
      /***********************************************************************/
      /* Between bracket, so open bracket and give direction.  Note that we  */
      /* can do this since we will always be contention winner.              */
      /***********************************************************************/
      other_verb.common.lua_rh.bbi         = 1;
      other_verb.common.lua_rh.cdi         = 1;
      send_state = RECV;
    }
    else if (send_state = SEND)
    {
      /***********************************************************************/
      /* In bracket and we have direction, so simply give direction.         */
      /***********************************************************************/
      other_verb.common.lua_rh.cdi         = 1;
      send_state = RECV;
    }
    else
    {
      /***********************************************************************/
      /* In bracket and we do not have direction, so do not send.            */
      /***********************************************************************/
      printf("Wait\n");
      ok = FALSE;
    }
  }
  else
  {
    /*************************************************************************/
    /* On the SSCP session things are straightforward.                       */
    /*************************************************************************/
    other_verb.common.lua_flag1.sscp_norm  = 1;
  }

  if (ok)
  {
    /*************************************************************************/
    /* Issue write verb                                                      */
    /*************************************************************************/
    RUI((LUA_VERB_RECORD FAR *) &other_verb);

    /*************************************************************************/
    /* Reset write_data to point to correct point in write_array             */
    /*************************************************************************/
    write_data = write_array + WRITE_EXTRA;
  }

  return(ok);
}  /* do_write ()                                                            */



/**PROC+**********************************************************************/
/* Name:      parse_data                                                     */
/*                                                                           */
/* Purpose:   parse data from the host                                       */
/*                                                                           */
/* Returns:   void                                                           */
/*                                                                           */
/* Params:    IN  data - pointer to data                                     */
/*                                                                           */
/* Operation: Looks through data for read partition query from host.  Could  */
/* be expanded to format data from host                                      */
/*                                                                           */
/**PROC-**********************************************************************/
void parse_data (data, length)

UCHAR FAR * data;
USHORT      length;
{
  USHORT  field_length;

  switch (*(data++))
  {
    case 0xF3:                       /* write structured field               */
      /***********************************************************************/
      /* Next byte is the WCC - ignore                                       */
      /***********************************************************************/
      data++;
      length -= 2;

      while (length > 0)
      {
        /*********************************************************************/
        /* We're just looking for a Read Partion query                       */
        /*********************************************************************/
        field_length = (((USHORT) *data) << 8) || ((USHORT) *(data + 1));
        if ((*(data+2) == 0x01) &&   /* Read partition                       */
            (*(data+3) == 0xFF) &&   /* Query                                */
            (*(data+4) == 0x02))     /* not a list                           */
        {
          /*******************************************************************/
          /* Build an RPQ and flag it to be sent                             */
          /*******************************************************************/
          rpq_state = RPQ_QUEUED;
        }
        data   += field_length;
        length -= field_length;
      }


      break;

    default:
      break;

  }
}  /* parse_data                                                             */



/**PROC+**********************************************************************/
/* Name:      issue_rpq                                                      */
/*                                                                           */
/* Purpose:   issue a response to a Read partition query                     */
/*                                                                           */
/* Returns:   BOOL - TRUE => sent OK                                         */
/*                                                                           */
/* Params:    none                                                           */
/*                                                                           */
/* Operation: Builds and sends an RPQ reesponse                              */
/*                                                                           */
/**PROC-**********************************************************************/
BOOL issue_rpq (void)

{
  BOOL issue_rpq;

  issue_rpq = TRUE;
  /***************************************************************************/
  /* Set up the vcb                                                          */
  /***************************************************************************/
  memset(&rpq_verb, 0, sizeof(rpq_verb));
  rpq_verb.common.lua_verb             = LUA_VERB_RUI;
  rpq_verb.common.lua_verb_length      = sizeof(rpq_verb);
  rpq_verb.common.lua_opcode           = LUA_OPCODE_RUI_WRITE;
  rpq_verb.common.lua_sid              = sid;
  rpq_verb.common.lua_data_length      = RPQ_LENGTH;
  rpq_verb.common.lua_data_ptr         = (char far *) rpq_data;
  rpq_verb.common.lua_post_handle      = RPQPOST;
  rpq_verb.common.lua_rh.bci           = 1;
  rpq_verb.common.lua_rh.eci           = 1;
  rpq_verb.common.lua_rh.dr1i          = 1;

  /***************************************************************************/
  /* On the LU session we must add the <enter> key prefix.  All inbound      */
  /* requests flow RQE with the BBI and CDI flags set depending on the       */
  /* current session state.                                                  */
  /***************************************************************************/
  rpq_verb.common.lua_flag1.lu_norm  = 1;
  rpq_verb.common.lua_rh.ri          = 1;
  if (send_state == BETB)
  {
    /*************************************************************************/
    /* Between bracket, so open bracket and give direction.  Note that we    */
    /* can do this since we will always be contention winner.                */
    /*************************************************************************/
    rpq_verb.common.lua_rh.bbi         = 1;
    rpq_verb.common.lua_rh.cdi         = 1;
    send_state = RECV;
  }
  else if (send_state = SEND)
  {
    /*************************************************************************/
    /* In bracket and we have direction, so simply give direction.           */
    /*************************************************************************/
    rpq_verb.common.lua_rh.cdi         = 1;
    send_state = RECV;
  }
  else
  {
    /*************************************************************************/
    /* In bracket and we do not have direction, so do not send.              */
    /*************************************************************************/
    printf("Wait\n");
    issue_rpq = FALSE;
  }

  if (issue_rpq)
  {
    RUI((LUA_VERB_RECORD FAR *) &rpq_verb);
  }

  return(issue_rpq);
}  /* issue_rpq                                                              */

