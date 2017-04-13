/*****************************************************************************/
/* SLI Sample Program                                                        */
/*                                                                           */
/* (C) Copyright 1990 - 1993 Data Connection Ltd.                            */
/*                                                                           */
/* This program is a crude 3270 emulator.  It uses the SLI API to access the */
/* LU-LU session.  Outbound data from the host is displayed on the screen    */
/* unformatted.                                                              */
/*                                                                           */
/* If the outbound data is an RQD request an automatic positive response     */
/* is sent.  Inbound data can be entered at the keyboard and is sent on      */
/* the current session.                                                      */
/*                                                                           */
/* The program is invoked with two parameters - the name of the LUA LU       */
/* to use and a logon string.  This is converted to upper case and must      */
/* match an LUA LU in the configuration file.  This LU should be configured  */
/* for a 327? on the host.                                                   */
/*                                                                           */
/* The program can only access hosts that use simple unformatted logon       */
/* requests                                                                  */
/*                                                                           */
/* To exit the program type ] (right square bracket)                         */
/*                                                                           */
/* The CSV CONVERT function is used to convert data between ASCII and        */
/* EBCDIC.  This uses the type G conversion table, so the environment        */
/* variable COMTBLG must be set to point to a suitable file.                 */
/*                                                                           */
/* Keys that work are:                                                       */
/*                                                                           */
/*     Alt-1 to Alt-9 are PF1 to PF9                                         */
/*     F2 sends a CLEAR to the host                                          */
/*     backspace                                                             */
/*     Letters, numbers and symbols                                          */
/*     ] terminates the program                                              */
/*                                                                           */
/*****************************************************************************/


#ifdef WIN32
  #include <windows.h>
#else
  #define INCL_DOS
  #define INCL_DOSERRORS
  #include <os2.h>
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
/* Inbound data is  prefixed with the <enter> key AID plus a two byte      */
/* cursor address.                                                         */
/***************************************************************************/
LUA_VERB_RECORD recv_verb;             /* SLI read verb                    */
LUA_VERB_RECORD other_verb;            /* SLI init, write or term verb     */
LUA_VERB_RECORD rpq_verb;              /* SLI_WRITE for RPQs               */

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
  HANDLE init_event  = 0l;             /* SLI_OPEN semaphore                 */
  HANDLE term_event  = 0l;             /* SLI_CLOSE semaphore                */
  HANDLE rpq_event   = 0l;
  HANDLE std_input;                    /* standard input handle              */
  HANDLE std_output;                   /* standard output handle             */
#else
  ULONG write_sema4 = 0l;              /* write arm verb semaphore           */
  ULONG read_sema4  = 0l;              /* read arm verb semaphore            */
  ULONG init_sema4  = 0l;              /* SLI_OPEN semaphore                 */
  ULONG term_sema4  = 0l;              /* SLI_CLOSE semaphore                */
  ULONG rpq_sema4   = 0l;
#endif

BOOL terminating = FALSE;              /* are we already in closedown() ?    */

unsigned long sense = 0l;              /* sense code                         */

unsigned char lu_name[9] = "        "; /* LU name                            */
unsigned long sid;                     /* SLI session ID                     */
int send_state = BETB;                 /* LU session send state              */

#define LOGON_MAX  25                  /* maximum logon string length        */

UCHAR logon_data[LOGON_MAX+1] = {0};
UCHAR logon_length   = 0;

#ifdef WIN32
  #define OPENPOST        (ULONG) init_event
  #define CLOSEPOST       (ULONG) term_event
  #define RECVPOST        (ULONG) read_event
  #define SENDPOST        (ULONG) write_event
  #define RPQPOST         (ULONG) rpq_event
#else
  #define OPENPOST        (unsigned long) ((UCHAR FAR *) &init_sema4)
  #define CLOSEPOST       (unsigned long) ((UCHAR FAR *) &term_sema4)
  #define RECVPOST        (unsigned long) ((UCHAR FAR *) &read_sema4)
  #define SENDPOST        (unsigned long) ((UCHAR FAR *) &write_sema4)
  #define RPQPOST         (unsigned long) ((UCHAR FAR *) &rpq_sema4)
#endif


/*****************************************************************************/
/* Function declarations.                                                    */
/*****************************************************************************/

#ifdef WIN32
  #define LOADDS
#else
  #define LOADDS _loadds
#endif

void pascal far LOADDS SLI (LUA_VERB_RECORD FAR *);

#ifdef WIN32
  void _CRTAPI1 main(int argc, char *argv[]);
#else
  int             main                (int  argc,char  * *argv);
#endif
void            csv_init            (void);
int             issue_verb          (unsigned int  type);
void            issue_receive       (void);
void            other_done          (LUA_VERB_RECORD *verb);
void            recv_done           (LUA_VERB_RECORD *verb);
void            issue_rsp           (unsigned long  sense);
void            rsp_done            (LUA_VERB_RECORD *verb);
void            closedown           (void);
BOOL            do_send             (void);
void            wait_verb_complete  (LUA_VERB_RECORD *verb);
void            set_semaphore       (LUA_VERB_RECORD *verb);
BOOL            do_keyboard_stuff   (void);
BOOL            check_verb_complete (LUA_VERB_RECORD *verb);
void            parse_data          (UCHAR FAR *, USHORT);
BOOL            issue_rpq           (void);

/**PROC+**********************************************************************/
/* Name:      main                                                           */
/*                                                                           */
/* Purpose:   set up CSV convert verbs                                       */
/*                                                                           */
/* Returns:   none                                                           */
/*                                                                           */
/* Params:    argv, argc                                                     */
/*                                                                           */
/* Operation: Get LU name and logon string from command line                 */
/*            do some initialisation                                         */
/*            Issue SLI_OPEN to get LU-LU   session                          */
/*            Loop reading data from keyboard and host, and send keyboard    */
/*            data to host                                                   */
/**PROC-**********************************************************************/
#ifdef WIN32
  void _CRTAPI1 main(int argc, char *argv[])
#else
int main(argc, argv)
int argc;
char *argv[];
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

  printf("SLI simple 3270 application\n");

  /***************************************************************************/
  /* Validate parameter usage and get LU name.                               */
  /***************************************************************************/
  if (argc != 3)
  {
    printf("Usage: SLI3270 luname \"logon string\"\n");
    exit(1);
  }
  if (strlen(argv[1]) > 8)
  {
    printf("LU name too long\n");
    exit(1);
  }
  if (strlen(argv[2]) > LOGON_MAX)
  {
    printf("Logon string too long");
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
  /* Set up logon message                                                    */
  /***************************************************************************/
  strcpy (logon_data, argv[2]);
  logon_length = strlen(logon_data);
  convert_to_ebc.opcode       = SV_CONVERT;
  convert_to_ebc.direction    = SV_ASCII_TO_EBCDIC;
  convert_to_ebc.char_set     = SV_G;
  convert_to_ebc.source       = logon_data;
  convert_to_ebc.target       = logon_data;
  convert_to_ebc.len          = (unsigned short) logon_length;
  ACSSVC_C((LONG)((UCHAR FAR *)&convert_to_ebc));

  /***************************************************************************/
  /* Set up CSV convert verbs                                                */
  /***************************************************************************/
  csv_init();

#ifdef WIN32
  /***************************************************************************/
  /* Create the necessary events                                             */
  /***************************************************************************/
  write_event = CreateEvent (NULL, TRUE, FALSE, NULL);
  read_event  = CreateEvent (NULL, TRUE, FALSE, NULL);
  init_event  = CreateEvent (NULL, TRUE, FALSE, NULL);
  term_event  = CreateEvent (NULL, TRUE, FALSE, NULL);
  rpq_event   = CreateEvent (NULL, TRUE, FALSE, NULL);


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
  /* Initialize SLI (get LU-LU session)                                      */
  /***************************************************************************/
  if (issue_verb((unsigned int) LUA_OPCODE_SLI_OPEN))
  {
    printf("OPEN failed\n");
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

        write_ok = do_send ();
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
      write_ok = do_send ();
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
      /* We have a SLI_WRITE outstanding so check if it is complete          */
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
      issue_receive ();
      if (recv_verb.common.lua_flag2.async)
      {
        read_state = READ_OUTSTANDING;
      }
      else
      {
        /*********************************************************************/
        /* recv_done will change read_state to RESPONSE_QUEUED or NO_READ    */
        /*********************************************************************/
        recv_done (&recv_verb);
      }
    }
    else if (read_state == READ_OUTSTANDING)
    {
      verb_complete = check_verb_complete (&recv_verb);
      if (verb_complete)
      {
        /*********************************************************************/
        /* recv_done will change read_state to RESPONSE_QUEUED or NO_READ    */
        /*********************************************************************/
        recv_done (&recv_verb);
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
        /* The response is issued using the recv_verb                        */
        /*********************************************************************/
        issue_rsp (sense);
        if (recv_verb.common.lua_flag2.async)
        {
          read_state = RSP_OUTSTANDING;
        }
        else
        {
          rsp_done (&recv_verb);
          read_state = NO_READ;
        }
      }
    }
    else if (read_state == RSP_OUTSTANDING)
    {
      /***********************************************************************/
      /* Check to see if the response is complete                            */
      /***********************************************************************/
      verb_complete = check_verb_complete (&recv_verb);
      if (verb_complete)
      {
        rsp_done (&recv_verb);
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
/* Operation: Build an OPEN or CLOSE verb and issue it.  Wait for the verb   */
/*            to complete                                                    */
/**PROC-**********************************************************************/
int issue_verb(type)
unsigned int  type;
{
  memset(&other_verb, 0, sizeof(other_verb));
  other_verb.common.lua_verb             = LUA_VERB_SLI;
  other_verb.common.lua_opcode           = type;
  if (type == LUA_OPCODE_SLI_OPEN)
  {
    other_verb.common.lua_verb_length    = sizeof(struct LUA_COMMON)+
                            sizeof(other_verb.specific.open.lua_init_type) +
                            sizeof(other_verb.specific.open.lua_resv65) +
                            sizeof(other_verb.specific.open.lua_wait) +
                            sizeof(other_verb.specific.open.lua_ending_delim);
    memcpy(other_verb.common.lua_luname, lu_name, 8);
    other_verb.common.lua_post_handle    = OPENPOST;
    other_verb.specific.open.lua_init_type = LUA_INIT_TYPE_SEC_LOG;
    other_verb.common.lua_data_length    = logon_length;
    other_verb.common.lua_data_ptr       = logon_data;
    other_verb.specific.open.lua_open_extension[0].lua_routine_type =
                                                         LUA_ROUTINE_TYPE_END;
  }
  else
  {
    other_verb.common.lua_verb_length    = sizeof(struct LUA_COMMON);
    other_verb.common.lua_sid            = sid;
    other_verb.common.lua_post_handle    = CLOSEPOST;
  }
  SLI((LUA_VERB_RECORD FAR *) &other_verb);
  if (other_verb.common.lua_flag2.async)
  {
    wait_verb_complete (&other_verb);
  }
  other_done(&other_verb);

  return(other_verb.common.lua_prim_rc != LUA_OK);
}  /* issue_verb                                                             */


/**PROC+**********************************************************************/
/* Name:      issue_receive                                                  */
/*                                                                           */
/* Purpose:   build a recv verb and send it                                  */
/*                                                                           */
/* Returns:   void                                                           */
/*                                                                           */
/* Params:    none                                                           */
/*                                                                           */
/* Operation: Build a read verb for all flows and issue it                   */
/**PROC-**********************************************************************/
void issue_receive (void)
{
  memset(&recv_verb, 0, sizeof(recv_verb));
  memset(read_data, 0, DATASIZE);
  recv_verb.common.lua_verb             = LUA_VERB_SLI;
  recv_verb.common.lua_verb_length      = sizeof(struct LUA_COMMON);
  recv_verb.common.lua_opcode           = LUA_OPCODE_SLI_RECEIVE;
  recv_verb.common.lua_sid              = sid;
  recv_verb.common.lua_max_length       = DATASIZE;
  recv_verb.common.lua_data_ptr         = (char *) read_data;
  recv_verb.common.lua_post_handle      = RECVPOST;
  recv_verb.common.lua_flag1.lu_norm    = 1;
  recv_verb.common.lua_flag1.lu_exp     = 1;
  recv_verb.common.lua_flag1.sscp_norm  = 1;
  recv_verb.common.lua_flag1.sscp_exp   = 1;
  SLI((LUA_VERB_RECORD FAR *)&recv_verb);

}  /* issue_receive                                                          */


/**PROC+**********************************************************************/
/* Name:      other_done                                                     */
/*                                                                           */
/* Purpose:   handle completed open, send or close verb                      */
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
    case LUA_OPCODE_SLI_OPEN:
         if (verb->common.lua_prim_rc == LUA_OK)
         {
           printf("session active\n");
           sid = verb->common.lua_sid;
         }
         else
         {
           printf("OPEN failed, (%4.4x, %8.8lx)\n",
                  verb->common.lua_prim_rc, verb->common.lua_sec_rc);
         }
         break;

    case LUA_OPCODE_SLI_SEND:
         if (verb->common.lua_prim_rc != LUA_OK)
         {
           printf("SEND failed, (%4.4x, %8.8lx)\n",
                  verb->common.lua_prim_rc, verb->common.lua_sec_rc);
         }
         break;

    case LUA_OPCODE_SLI_CLOSE:
         printf("Terminated\n");
         break;

  }
}  /* other_done                                                             */


/**PROC+**********************************************************************/
/* Name:      recv_done                                                      */
/*                                                                           */
/* Purpose:   handle completed receive verb                                  */
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
void recv_done(verb)
LUA_VERB_RECORD *verb;
{
  int            count;         /* number of bytes of data left to display   */
  unsigned char *data;          /* pointer to next data to display           */
  BOOL           rsp_required = FALSE; /* is a resonse required              */

  sense = 0l;

  if (verb->common.lua_prim_rc == LUA_OK)
  {
    if (verb->common.lua_message_type == LUA_MESSAGE_TYPE_LU_DATA)
    {
      if (verb->common.lua_data_length > 0)
      {
        /*********************************************************************/
        /* We now have to parse the data.  For the moment we only look for   */
        /* RPQ requests.                                                     */
        /*********************************************************************/
        parse_data (read_data, (USHORT) (verb->common.lua_data_length));

        /*********************************************************************/
        /* Display outbound data.                                            */
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
    printf("RECEIVE ERROR, primary rc = %4.4x, secondary rc = %8.8lx\n",
           verb->common.lua_prim_rc, verb->common.lua_sec_rc);
    closedown();
  }

  /***************************************************************************/
  /* Continue processing with either another recv or a send  positive rsp.   */
  /* (The callback from issuing response will then issue another recv) If    */
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
}  /* recv_done                                                              */


/**PROC+**********************************************************************/
/* Name:      issue_rsp                                                      */
/*                                                                           */
/* Purpose:   issue a response for a request from the host                   */
/*                                                                           */
/* Returns:   void                                                           */
/*                                                                           */
/* Params:    IN sense - sense code for the response                         */
/*                                                                           */
/* Operation: Build a response and write it out.  Uses the recv verb control */
/*            block because it has the necessary information.                */
/*                                                                           */
/**PROC-**********************************************************************/
void issue_rsp(sense)
unsigned long sense;
{
  recv_verb.common.lua_opcode           = LUA_OPCODE_SLI_SEND;
  recv_verb.common.lua_max_length       = 0;
  recv_verb.common.lua_post_handle      = (ULONG) RECVPOST;
  recv_verb.common.lua_message_type     = LUA_MESSAGE_TYPE_RSP;
  recv_verb.common.lua_verb_length      = sizeof(struct LUA_COMMON) +
                                sizeof(recv_verb.specific.lua_sequence_number);

  recv_verb.common.lua_rh.rri           = 1;        /* response              */
  recv_verb.common.lua_flag1.lu_norm    = 0;
  recv_verb.common.lua_flag1.lu_exp     = 0;
  recv_verb.common.lua_flag1.sscp_norm  = 0;
  recv_verb.common.lua_flag1.sscp_exp   = 0;

  /***************************************************************************/
  /* If we have been given a sense code this must be a negative response     */
  /***************************************************************************/
  if (sense)
  {
    recv_verb.common.lua_data_length      = 4;
    memcpy(read_data, &sense, 4);
    recv_verb.common.lua_rh.ri            = 1;       /* negative rsp         */
  }
  else
  {
    recv_verb.common.lua_data_length      = 0;
    recv_verb.common.lua_rh.ri            = 0;       /* positive rsp         */
  }
  /***************************************************************************/
  /* Send the response back on the flow from which the request came          */
  /***************************************************************************/
  if (recv_verb.common.lua_flag2.lu_norm)
  {
    recv_verb.common.lua_flag1.lu_norm = 1;
  }
  else if (recv_verb.common.lua_flag2.lu_exp)
  {
    recv_verb.common.lua_flag1.lu_exp = 1;
  }
  else if (recv_verb.common.lua_flag2.sscp_norm)
  {
    recv_verb.common.lua_flag1.sscp_norm = 1;
  }
  else if (recv_verb.common.lua_flag2.sscp_exp)
  {
    recv_verb.common.lua_flag1.sscp_exp = 1;
  }
  /***************************************************************************/
  /* Send out the verb                                                       */
  /***************************************************************************/
  SLI((LUA_VERB_RECORD FAR *)&recv_verb);              /* write the response */
}  /* issue_rsp                                                              */


/**PROC+**********************************************************************/
/* Name:      rsp_done                                                       */
/*                                                                           */
/* Purpose:   handle completion of SLI_SEND, when SLI_SEND has written a     */
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
  if (verb->common.lua_prim_rc != LUA_OK)    /* failed to write the response */
  {                                          /* so stop here                 */
    printf("SEND for response failed, (%4.4x, %8.8lx)\n",
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
/* Operation: Issue an SLI_CLOSE and wait for it to complete.  Then exit     */
/*                                                                           */
/**PROC-**********************************************************************/
void closedown (void)
{
  if (!terminating)                /* check we haven't already got here from */
  {                                /* another section of the code            */
    terminating = TRUE;            /* then make sure we can't get here again */
    printf("Closedown\n");
    if (issue_verb((unsigned int) LUA_OPCODE_SLI_CLOSE))
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

  RetCode = DosSemRequest ((HSEM)verb->common.lua_post_handle, 0l);

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
    input_char = getche ();
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
          write_data -= WRITE_EXTRA;
          write_len  += WRITE_EXTRA;
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
/* Name:      do_send                                                        */
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
BOOL do_send (void)

{
  BOOL ok;

  ok = TRUE;


  /***************************************************************************/
  /* Set up the vcb                                                          */
  /***************************************************************************/
  memset(&other_verb, 0, sizeof(other_verb));
  other_verb.common.lua_verb             = LUA_VERB_SLI;
  other_verb.common.lua_verb_length      = sizeof(struct LUA_COMMON) +
                         sizeof(other_verb.specific.lua_sequence_number);
  other_verb.common.lua_opcode           = LUA_OPCODE_SLI_SEND;
  other_verb.common.lua_sid              = sid;
  other_verb.common.lua_message_type     = LUA_MESSAGE_TYPE_LU_DATA;
  other_verb.common.lua_data_length      = write_len;
  other_verb.common.lua_data_ptr         = (char far *) write_data;
  other_verb.common.lua_post_handle      = SENDPOST;
  other_verb.common.lua_rh.dr1i          = 1;

  /***************************************************************************/
  /* On the LU session we must add the <enter> key prefix.  All inbound      */
  /* requests flow RQE with the BBI and CDI flags set depending on the       */
  /* current session state.                                                  */
  /***************************************************************************/
  other_verb.common.lua_rh.ri          = 1;
  if (send_state == BETB)
  {
    /*************************************************************************/
    /* Between bracket, so open bracket and give direction.  Note that we    */
    /* can do this since we will always be contention winner.                */
    /*************************************************************************/
    other_verb.common.lua_rh.bbi         = 1;
    other_verb.common.lua_rh.cdi         = 1;
    send_state = RECV;
  }
  else if (send_state = SEND)
  {
    /*************************************************************************/
    /* In bracket and we have direction, so simply give direction.           */
    /*************************************************************************/
    other_verb.common.lua_rh.cdi         = 1;
    send_state = RECV;
  }
  else
  {
    /*************************************************************************/
    /* In bracket and we do not have direction, so do not send.              */
    /*************************************************************************/
    printf("Wait\n");
    ok = FALSE;
  }

  if (ok)
  {
    /*************************************************************************/
    /* Issue write verb                                                      */
    /*************************************************************************/
    SLI((LUA_VERB_RECORD FAR *) &other_verb);

    /*************************************************************************/
    /* Reset write_data to point to correct point in write_array             */
    /*************************************************************************/
    write_data = write_array + WRITE_EXTRA;
  }

  return(ok);
}  /* do_send ()                                                            */



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
  rpq_verb.common.lua_verb             = LUA_VERB_SLI;
  rpq_verb.common.lua_verb_length      = sizeof(struct LUA_COMMON) +
                         sizeof(rpq_verb.specific.lua_sequence_number);
  rpq_verb.common.lua_opcode           = LUA_OPCODE_SLI_SEND;
  rpq_verb.common.lua_sid              = sid;
  rpq_verb.common.lua_message_type     = LUA_MESSAGE_TYPE_LU_DATA;
  rpq_verb.common.lua_data_length      = RPQ_LENGTH;
  rpq_verb.common.lua_data_ptr         = (char far *) rpq_data;
  rpq_verb.common.lua_post_handle      = RPQPOST;
  rpq_verb.common.lua_rh.dr1i          = 1;

  /***************************************************************************/
  /* On the LU session we must add the <enter> key prefix.  All inbound      */
  /* requests flow RQE with the BBI and CDI flags set depending on the       */
  /* current session state.                                                  */
  /***************************************************************************/
  rpq_verb.common.lua_flag1.lu_norm  = 0;
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
    SLI((LUA_VERB_RECORD FAR *) &rpq_verb);
  }

  return(issue_rpq);
}  /* issue_rpq                                                              */

