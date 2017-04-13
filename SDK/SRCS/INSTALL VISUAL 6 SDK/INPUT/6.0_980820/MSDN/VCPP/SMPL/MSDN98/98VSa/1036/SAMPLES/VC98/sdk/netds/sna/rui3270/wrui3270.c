/**MOD+***********************************************************************/
/* Module:  wrui3270.exe                                                     */
/*                                                                           */
/* Purpose: simple 3270 emulator                                             */
/*                                                                           */
/* (C) COPYRIGHT DATA CONNECTION LIMITED 1991                                */
/*                                                                           */
/**MOD-***********************************************************************/


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
/*                                                                           */
/* The CSV CONVERT function is used to convert data between ASCII and        */
/* EBCDIC.  This uses the type G conversion table, so the environment        */
/* variable COMTBLG must be set to point to a suitable file.                 */
/*                                                                           */
/* Keys that work are:                                                       */
/*                                                                           */
/*     Alt-1 to Alt-0 are PF1 to PF0                                         */
/*     backspace                                                             */
/*     Letters, numbers and symbols                                          */
/*                                                                           */
/*****************************************************************************/


/*****************************************************************************/
/* SYSTEM INCLUDES                                                           */
/*****************************************************************************/
#include <windows.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <winlua.h>
#include <wincsv.h>

typedef unsigned char  UCHAR;
typedef unsigned short USHORT;
typedef unsigned long  ULONG;


/*****************************************************************************/
/* Program constants                                                         */
/*****************************************************************************/
#define DATASIZE 4096                  /* Max size of RU                     */
#define SWITKEY  0x5B                  /* '['   to switch sessions           */

#define BETB     1                     /* Between brackets                   */
#define SEND     2                     /* In bracket and can send            */
#define RECV     3                     /* In bracket, but cannot send        */

#define APPNAME                "WRUI3270"
#define RUI_WINDOW_MESSAGE     "WinRUI"

#define DISPLAY_BUFFER_SIZE    3200    /* size of circular display buffer    */

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

UCHAR display_buffer[DISPLAY_BUFFER_SIZE] = {0};
UINT  buffer_end   = 0;             /* end of data in display buffer         */
BOOL  wrapped      = FALSE;         /* has buffer wrapped?                   */


/*****************************************************************************/
/* Global Variables                                                          */
/*****************************************************************************/
HANDLE hInst = 0;                   /* current instance                      */
UINT   verb_complete = 0;           /* verb completion message               */
HANDLE hWnd = 0;                    /* Handle to program window              */

BOOL   init_done = FALSE;           /* RUI_INIT completed                    */



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

BOOL terminating = FALSE;              /* are we already in closedown() ?    */
BOOL lu_session  = FALSE;              /* LU session inbound flag            */

unsigned long sense = 0l;              /* sense code                         */

unsigned char lu_name[9] = "        "; /* LU name                            */
unsigned long sid;                     /* RUI session ID                     */
int send_state = BETB;                 /* LU session send state              */
int last_status = WLUAGETLU;           /* Current status of Session     *STAT*/

UCHAR  string[64]={0};




void pascal far LOADDS RUI (LUA_VERB_RECORD FAR *);

extern int      WINAPI GetFmiReturnCode(unsigned short,                /*STAT*/
                                        unsigned short,                /*STAT*/
                                        unsigned short,                /*STAT*/
                                        unsigned char FAR *);          /*STAT*/

void            csv_init            (void);
void            issue_init          (void);
void            issue_read          (void);
void            other_done          (LUA_VERB_RECORD FAR *verb);
void            read_done           (LUA_VERB_RECORD FAR *verb);
void            issue_rsp           (unsigned long  sense);
void            rsp_done            (LUA_VERB_RECORD FAR *verb);
void            closedown           (void);
BOOL            do_write            (void);
void            wait_verb_complete  (LUA_VERB_RECORD FAR *verb);
void            set_semaphore       (LUA_VERB_RECORD FAR *verb);
BOOL            do_keyboard_stuff   (UINT, UCHAR);
BOOL            check_verb_complete (LUA_VERB_RECORD FAR *verb);
void            parse_data          (UCHAR FAR *, USHORT);
BOOL            issue_rpq           (void);
void            verb_complete_proc  (LUA_VERB_RECORD FAR * verb);
void          add_to_display_buffer (UCHAR FAR *);

/*****************************************************************************/
/* Windows function prototypes.                                              */
/*****************************************************************************/
int PASCAL WinMain(HINSTANCE, HINSTANCE, LPSTR, int);
long FAR PASCAL WndProc(HWND, UINT, UINT, LONG);




/***PROC+*********************************************************************/
/* Name:     WinMain                                                         */
/*                                                                           */
/* Purpose:  Main Windows function                                           */
/*                                                                           */
/* Params:   IN current instance handle                                      */
/*           IN previous instance handle                                     */
/*           IN pointer to command line                                      */
/*           IN show window type                                             */
/*                                                                           */
/* Returns:  int                                                             */
/*                                                                           */
/**PROC-**********************************************************************/

int PASCAL WinMain(hInstance, hPrevInstance, lpCmdLine, nCmdShow)

HINSTANCE hInstance;                         /* current instance             */
HINSTANCE hPrevInstance;                     /* previous instance            */
LPSTR     lpCmdLine;                         /* command line                 */
int       nCmdShow;                          /* show-window type (open/icon) */
{
  /***************************************************************************/
  /* LOCAL VARIABLES                                                         */
  /***************************************************************************/
  MSG   msg;                                 /* message                      */
  int   xscreen;
  int   yscreen;
  int   delta;
  WNDCLASS class;
  LUADATA  LUAData;


  if (!hPrevInstance)
  {
    class.style         = CS_HREDRAW | CS_VREDRAW;
    class.lpfnWndProc   = (WNDPROC)WndProc;
    class.cbClsExtra    = 0;
    class.cbWndExtra    = 0;
    class.hInstance     = hInstance;
    class.hIcon         = LoadIcon(NULL, IDI_APPLICATION);
    class.hCursor       = LoadCursor(NULL, IDC_ARROW);
    class.hbrBackground = GetStockObject(WHITE_BRUSH);
    class.lpszMenuName  = NULL;
    class.lpszClassName = APPNAME;

    if (!RegisterClass(&class))
    {
      return (0);
    }
  }

  /***************************************************************************/
  /* save current instance handle                                            */
  /***************************************************************************/
  hInst = hInstance;

  /***************************************************************************/
  /* Set initial states                                                      */
  /***************************************************************************/
  write_state = NO_WRITE;
  read_state  = NO_READ;
  rpq_state   = NO_RPQ;

  /***************************************************************************/
  /* Set up CSV convert verbs                                                */
  /***************************************************************************/
  csv_init();

  /***************************************************************************/
  /* get details of display                                                  */
  /***************************************************************************/
  xscreen = GetSystemMetrics(SM_CXSCREEN);
  yscreen = GetSystemMetrics(SM_CYSCREEN);

  /***************************************************************************/
  /* invent somewhere to put window                                          */
  /***************************************************************************/
  delta = xscreen / 100;

  /***************************************************************************/
  /* create display window                                                   */
  /***************************************************************************/
  hWnd = CreateWindow(APPNAME,                    /* window class            */
        "RUI3270",                                /* window name             */
        WS_OVERLAPPEDWINDOW,                      /* window style            */
        (xscreen/2) + delta,                      /* x position              */
        yscreen / 8,                              /* y position              */
        (xscreen / 2) - (delta * 2),              /* width                   */
        3 * yscreen / 4,                          /* height                  */
        NULL,                                     /* parent handle           */
        NULL,                                     /* menu or child ID        */
        hInstance,                                /* instance                */
        NULL);                                    /* additional info         */

  if (!hWnd)
  {
    return (0);
  }

  ShowWindow(hWnd, nCmdShow);                     /* Shows the window        */
  UpdateWindow(hWnd);                             /* Sends WM_PAINT message  */


  /***************************************************************************/
  /* Register message used for async completion                              */
  /***************************************************************************/
  verb_complete = RegisterWindowMessage(RUI_WINDOW_MESSAGE);

  if (verb_complete == 0)
  {
    return (0);
  }

  WinRUIStartup (0x0001, &LUAData);

  /***************************************************************************/
  /* Issue RUI_INIT to get the ball rolling.  Setup up the LU name           */
  /***************************************************************************/
  _fmemcpy ((UCHAR FAR *)lu_name,
            lpCmdLine,
            _fstrlen(lpCmdLine));
  issue_init ();

  while(GetMessage(&msg,NULL,0,0))
  {
    TranslateMessage(&msg);
    DispatchMessage(&msg);
  }

  return msg.wParam;         /* save exit parameter for return               */
}

/***PROC+*********************************************************************/
/* Name:     WndProc                                                         */
/*                                                                           */
/* Purpose:  Windows call-back routine                                       */
/*                                                                           */
/* Params:   IN window handle                                                */
/*           IN message type                                                 */
/*           IN additional information 1                                     */
/*           IN additional information 2                                     */
/*                                                                           */
/* Returns:  long                                                            */
/*                                                                           */
/* Operation:set up window characteristics and register it                   */
/*           return success or failure                                       */
/*                                                                           */
/**PROC-**********************************************************************/

long FAR PASCAL WndProc(hWnd, message, wParam, lParam)
HWND hWnd;                                /* window handle                   */
UINT message;                             /* type of message                 */
UINT wParam;                              /* additional information          */
LONG lParam;                              /* additional information          */
{
  /***************************************************************************/
  /* LOCAL VARIABLES                                                         */
  /***************************************************************************/
  HDC          hDC;              /* handle to our device context             */
  TEXTMETRIC   tm;               /* holds info on the current font           */
  PAINTSTRUCT  ps;               /*  paint structure                         */
  RECT         rc;               /* holds info on the size oof our window    */
  ULONG        width;            /* width of window in chars                 */
  ULONG        height;           /* height of window in chars                */
  UINT         buffer_offset;    /* offset withing display buffer            */
  UINT         buffer_length;    /* length of data in buffer                 */
  UINT         out_length;       /* lngth of text to output                  */
  UINT         out_length2;      /* and again                                */
  static int   xChar, yChar;     /* width & height of the average char       */
  int          position;         /* number of lines down the screen          */
  BOOL         whole_data;       /* do we have data to send?                 */
  char         status_buff[80];  /* Current status                      *STAT*/

  if ((message == verb_complete) &&
      (!terminating))
  {
    /*************************************************************************/
    /* Message is RUI verb completed.  We are not terminating, so process    */
    /* the message.                                                          */
    /*************************************************************************/
    if (wParam == 0)                                                   /*STAT*/
    {                                                                  /*STAT*/
      verb_complete_proc ((LUA_VERB_RECORD FAR *) lParam);
    }                                                                  /*STAT*/
    else                                                               /*STAT*/
    {                                                                  /*STAT*/
      /***********************************************************************/
      /* Message is Notification of LUA Session State Change            *STAT*/
      /***********************************************************************/
      last_status = WinRUIGetLastInitStatus(lParam,                    /*STAT*/
                                            NULL,                      /*STAT*/
                                            WLUA_NTFY_MSG_SID,         /*STAT*/
                                            0);                        /*STAT*/
      /******************************************************************STAT*/
      /* Cause the window to be re-painted                              *STAT*/
      /******************************************************************STAT*/
      InvalidateRect (hWnd, NULL, TRUE);                               /*STAT*/
    }                                                                  /*STAT*/
    return(0l);
  }

  switch (message)
  {
    case WM_CREATE:
      /***********************************************************************/
      /* Window creation message.  Get some infomation about our font and    */
      /* save it for later                                                   */
      /***********************************************************************/
      hDC= GetDC(hWnd);
      GetTextMetrics (hDC, &tm);
      xChar = (int)tm.tmAveCharWidth;
      yChar = (int)(tm.tmHeight + tm.tmExternalLeading);
      ReleaseDC(hWnd, hDC);
      return 0l;
      break;

    case WM_CHAR:
    case WM_SYSCHAR:
      /***********************************************************************/
      /* Character or Alt+char hit                                           */
      /***********************************************************************/
      if ((init_done)                 &&
          (!terminating)              &&
          (write_state == NO_WRITE)   &&
          (rpq_state   == NO_RPQ)     &&
          (read_state  != RSP_QUEUED) &&
          (read_state  != RSP_OUTSTANDING))
      {
        /*********************************************************************/
        /* Someone pressed a key and we are in a state to deal with it       */
        /*********************************************************************/
        whole_data = do_keyboard_stuff (message, (UCHAR)wParam);
        if (whole_data)
        {
          /*******************************************************************/
          /* We have data to send                                            */
          /* Attempt to write the data out                                   */
          /*******************************************************************/
          if (do_write())
          {
            write_state = WRITE_OUTSTANDING;
          }
          else
          {
            write_state = WRITE_QUEUED;
          }
        }
        return(0l);
      }
      break;

    case WM_PAINT:
      BeginPaint (hWnd, &ps);
      /***********************************************************************/
      /* Determine the size of the Window in characters                      */
      /***********************************************************************/
      GetClientRect (hWnd, &rc);
      height = rc.bottom / yChar;
      width  = rc.right  / xChar;
      /***********************************************************************/
      /* subtract 2 from height for the status line                          */
      /***********************************************************************/
      height -= 2;
      /***********************************************************************/
      /* Work out how early in the buffer we can start                       */
      /***********************************************************************/
      if (!wrapped)
      {
        /*********************************************************************/
        /* buffer is not wrapped                                             */
        /*********************************************************************/
        buffer_length = buffer_end;
        buffer_offset = (buffer_length > (width * height)) ?
                         buffer_end - (width * height) :
                         0;
      }
      else
      {
        /*********************************************************************/
        /* buffer is wrapped                                                 */
        /*********************************************************************/
        buffer_length = DISPLAY_BUFFER_SIZE;
        if (buffer_length > width * height)
        {
          /*******************************************************************/
          /* buffer is too big.  Work out where best to start in the buffer/ */
          /*******************************************************************/
          if (buffer_end > width * height)
          {
            buffer_offset = buffer_end - (width * height);
          }
          else
          {
            buffer_offset = DISPLAY_BUFFER_SIZE +
                            buffer_end -
                            (width * height);
          }
        }
        else
        {
          /*******************************************************************/
          /* We can fit everything in                                        */
          /*******************************************************************/
          buffer_offset = buffer_end;
        }
      }
      /***********************************************************************/
      /* We've worked out where to start printing from, so start printing    */
      /***********************************************************************/
      position = 0;
      out_length = width;
      if (buffer_offset > buffer_end)
      {
        while (buffer_offset < DISPLAY_BUFFER_SIZE)
        {
          if (DISPLAY_BUFFER_SIZE - buffer_offset < width)
          {
            out_length = DISPLAY_BUFFER_SIZE - buffer_offset;
          }
          else
          {
            out_length = width;
          }
          TextOut(ps.hdc,
                  0,
                  yChar * position,
                  display_buffer + buffer_offset,
                  out_length);
          buffer_offset += out_length;
          position++;
        }
        buffer_offset = 0;
      }
      /***********************************************************************/
      /* If last line printed was a partial line, print the rest of the line */
      /***********************************************************************/
      if (out_length < width)
      {
        out_length2 = out_length;
        if (buffer_end < (width - out_length))
        {
          out_length = buffer_end;
        }
        else
        {
          out_length = width - out_length;
        }
        TextOut(ps.hdc,
                xChar * out_length2,
                yChar * (position - 1),
                display_buffer,
                out_length);
        buffer_offset += out_length;

      }
      /***********************************************************************/
      /* Now print to the end of the buffer                                  */
      /***********************************************************************/
      while (buffer_offset < buffer_end)
      {
        if (buffer_end - buffer_offset < width)
        {
          out_length = buffer_end - buffer_offset;
        }
        else
        {
          out_length = width;
        }
        TextOut(ps.hdc,
                0,
                yChar * position,
                display_buffer + buffer_offset,
                out_length);
        buffer_offset += out_length;
        position++;
      }

      /******************************************************************STAT*/
      /* Convert current status into display string                     *STAT*/
      /******************************************************************STAT*/
      GetFmiReturnCode(last_status,                                    /*STAT*/
                       (unsigned short) 0xffff,                        /*STAT*/
                       (unsigned short) 80, status_buff);              /*STAT*/

      /***********************************************************************/
      /* Now fill in the status line                                         */
      /***********************************************************************/
      out_length  = wsprintf (string,
                              "%s     %s     %s",                      /*STAT*/
                   (UCHAR FAR *)((send_state == BETB) ? "BETB" : "INB"),
                   (UCHAR FAR *)((lu_session)         ? "LU"   : "SSCP"),
                   (UCHAR FAR *)status_buff);                         /*STAT*/
      TextOut(ps.hdc,
              0,
              (UINT) (yChar * (height + 2)),
              string,
              out_length);
      /***********************************************************************/
      /* Now write the input line.  Only in NO_WRITE state, o.w.  data is in */
      /* EBCDIC                                                              */
      /***********************************************************************/
      if (write_state == NO_WRITE)
      {
        TextOut(ps.hdc,
                0,
                (UINT) (yChar * (height+1)),
                write_data,
                data_offset);
      }
      EndPaint(hWnd, &ps);
      break;

    case WM_CLOSE:
      if (!terminating)
      {
        /*********************************************************************/
        /* Tell the RUI we are going                                         */
        /*********************************************************************/
        terminating = TRUE;
        WinRUICleanup();
      }
      break;

    case WM_DESTROY:
      PostQuitMessage(0);
      return 0l;
      break;

    default:
      break;
  }
  return (DefWindowProc(hWnd, message, wParam, lParam));
}

/**PROC+**********************************************************************/
/* Name:      verb_complete_proc                                             */
/*                                                                           */
/* Purpose:   deal with verb completion                                      */
/*                                                                           */
/* Returns:   void                                                           */
/*                                                                           */
/* Params:    IN verb - pointer to completed verb                            */
/*                                                                           */
/* Operation: Determine which verb has completed and perform the appropriate */
/* action                                                                    */
/**PROC-**********************************************************************/
VOID verb_complete_proc (verb)

LUA_VERB_RECORD FAR * verb;
{

  switch (verb->common.lua_opcode)
  {
    case LUA_OPCODE_RUI_INIT:
      /***********************************************************************/
      /* Received ACTLU.  Save the SID for use on other verbs, flag init     */
      /* done so that we can write data, and issue first read                */
      /***********************************************************************/
      sid = other_verb.common.lua_sid;
      init_done = TRUE;
      issue_read();
      break;

    case LUA_OPCODE_RUI_READ:
      /***********************************************************************/
      /* Read completed.  Call read dne processor to display data and        */
      /* determine if a response is required.                                */
      /* If no response is required issue a new read                         */
      /* if a response is required issue the response if we can              */
      /***********************************************************************/
      read_done (verb);
      if (terminating == TRUE)
        break;
      if (read_state == NO_READ)
      {
        /*********************************************************************/
        /* No work to do, issue a new read verb                              */
        /*********************************************************************/
        read_state = READ_OUTSTANDING;
        issue_read();
      }
      else if ((read_state  == RSP_QUEUED) &&
               (write_state != WRITE_OUTSTANDING) &&
               (rpq_state   != RPQ_OUTSTANDING))
      {
        /*********************************************************************/
        /* We need to send a response to the RU we have just received.  The  */
        /* write flow is free, so send it                                    */
        /*********************************************************************/
        read_state = RSP_OUTSTANDING;
        issue_rsp (sense);
      }

      if ((rpq_state   == RPQ_QUEUED) &&
          (write_state != WRITE_OUTSTANDING) &&
          (read_state  != RSP_OUTSTANDING))
      {
        /*********************************************************************/
        /* We need to send a read partition query response and we can, so do */
        /* it.                                                               */
        /*********************************************************************/
        if (issue_rpq())
        {
          rpq_state = RPQ_OUTSTANDING;
        }
      }
      break;

    case LUA_OPCODE_RUI_WRITE:
      /***********************************************************************/
      /* Determine what kind of RUI_WRITE completed                          */
      /* either                                                              */
      /* -  writing user data                                                */
      /* -  writing a RPQ response                                           */
      /* -  writing a RSP to host data                                       */
      /***********************************************************************/
      if (write_state == WRITE_OUTSTANDING)
      {
        write_state = NO_WRITE;
        write_data[0] = '\0';
      }
      else if (rpq_state == RPQ_OUTSTANDING)
      {
        rpq_state = NO_RPQ;
      }
      else if (read_state == RSP_OUTSTANDING)
      {
        read_state = NO_READ;
        issue_read();
      }
      /***********************************************************************/
      /* Perform the next action depending on what work their is to do.      */
      /***********************************************************************/
      if (read_state == RSP_QUEUED)
      {
        /*********************************************************************/
        /* We need to issue a RSP to an RU we have received.  Do it          */
        /*********************************************************************/
        read_state = RSP_OUTSTANDING;
        issue_rsp (sense);
      }
      else if (rpq_state == RPQ_QUEUED)
      {
        /*********************************************************************/
        /* We need to issue a response to a read partion query.  Send it if  */
        /* the bracket state allows.                                         */
        /*********************************************************************/
        if (issue_rpq())
        {
          rpq_state = RPQ_OUTSTANDING;
        }
      }
      else if (write_state == WRITE_QUEUED)
      {
        /*********************************************************************/
        /* We have user data to send to the Host.  Send it if the bracket    */
        /* state allows                                                      */
        /*********************************************************************/
        if (do_write())
        {
          write_state = WRITE_OUTSTANDING;
        }
      }
      break;

    default:
      break;
  }
}  /* verb_complete_proc                                                     */

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
/* Name:      issue_init                                                     */
/*                                                                           */
/* Purpose:   build a verb and send it                                       */
/*                                                                           */
/* Returns:   void                                                           */
/*                                                                           */
/* Params:    None                                                           */
/*                                                                           */
/* Operation: Build an INIT verb and issue it.                               */
/**PROC-**********************************************************************/
void issue_init(void)
{
  memset(&other_verb, 0, sizeof(other_verb));
  other_verb.common.lua_verb             = LUA_VERB_RUI;
  other_verb.common.lua_verb_length      = sizeof(other_verb);
  other_verb.common.lua_opcode           = LUA_OPCODE_RUI_INIT;
  memcpy(other_verb.common.lua_luname, lu_name, 8);

  WinRUI(hWnd, (LUA_VERB_RECORD FAR *) &other_verb);

  /***************************************************************************/
  /* The sid is valid immediately.  Save it now.                             */
  /***************************************************************************/
  sid = other_verb.common.lua_sid;

  last_status = WinRUIGetLastInitStatus(0, hWnd, WLUA_NTFY_MSG_SID, 0);/*STAT*/

  if (!other_verb.common.lua_flag2.async)
  {
    /*************************************************************************/
    /* Verb completed immediately.  Post our own completion message          */
    /*************************************************************************/
    PostMessage (hWnd, verb_complete, 0, (LPARAM) (VOID FAR *)&other_verb);
  }

}  /* issue_init                                                             */


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
  read_verb.common.lua_data_ptr         = (char FAR *) read_data;
  read_verb.common.lua_flag1.lu_norm    = 1;
  read_verb.common.lua_flag1.lu_exp     = 1;
  read_verb.common.lua_flag1.sscp_norm  = 1;
  read_verb.common.lua_flag1.sscp_exp   = 1;
  WinRUI(hWnd, (LUA_VERB_RECORD FAR *)&(read_verb));
  if (!read_verb.common.lua_flag2.async)
  {
    /*************************************************************************/
    /* Verb completed immediately.  Post our own completion message          */
    /*************************************************************************/
    PostMessage (hWnd, verb_complete, 0, (LPARAM) (VOID FAR *)&read_verb);
  }

}  /* issue_read                                                             */




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
LUA_VERB_RECORD FAR * verb;
{
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
        add_to_display_buffer (read_data);
      }

      /***********************************************************************/
      /* Set session state.                                                  */
      /***********************************************************************/
      if (verb->common.lua_rh.ebi)
      {
        send_state = BETB;
      }
      else if (verb->common.lua_rh.cdi)
      {
        send_state = SEND;
      }
      else
      {
        send_state = RECV;
      }
      InvalidateRect (hWnd, NULL, TRUE);
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
        InvalidateRect (hWnd, NULL, TRUE);
        send_state = BETB;
        lu_session = TRUE;
      }
      else
      {
        sense = LUA_INVALID_SESSION_PARAMETERS;
      }
    }
    else if (verb->common.lua_message_type == LUA_MESSAGE_TYPE_UNBIND)
    {
      send_state = BETB;
      lu_session = FALSE;
      InvalidateRect (hWnd, NULL, TRUE);
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
  WinRUI(hWnd, (LUA_VERB_RECORD FAR *)&read_verb);     /* write the response */
  if (!read_verb.common.lua_flag2.async)
  {
    /*************************************************************************/
    /* Verb completed immediately.  Post our own completion message          */
    /*************************************************************************/
    PostMessage (hWnd, verb_complete, 0, (LPARAM) (VOID FAR *)&read_verb);
  }
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
/* Operation: If verb did not complete OK terminate                          */
/*                                                                           */
/**PROC-**********************************************************************/
void rsp_done (verb)
LUA_VERB_RECORD FAR * verb;
{
  if (verb->common.lua_prim_rc != LUA_OK)   /* failed to write the response */
  {                                         /* so stop here                 */
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
/* Operation: Issue a WinRUICleanup() to tell RUI the we are about to go,    */
/* and then post a close message so that we do.                              */
/*                                                                           */
/**PROC-**********************************************************************/
void closedown (void)
{
  if (!terminating)                /* check we haven't already got here from */
  {                                /* another section of the code            */
    terminating = TRUE;            /* then make sure we can't get here again */
    WinRUICleanup();
    PostMessage (hWnd, WM_CLOSE, 0, 0l);
  }
}  /* closedown                                                              */



/**PROC+**********************************************************************/
/* Name:      do_keyboard_stuff                                              */
/*                                                                           */
/* Purpose:   poll keyboard for data                                         */
/*                                                                           */
/* Returns:   BOOL - TRUE => we have data to send                            */
/*                                                                           */
/* Params:    none                                                           */
/*                                                                           */
/* Operation: Look for Alt-1 to Alt-9 and ascii chars.                       */
/*                                                                           */
/**PROC-**********************************************************************/
BOOL do_keyboard_stuff (type, key)

UINT  type;
UCHAR key;

{
  BOOL   data_to_send;             /* do we have data to send?               */

  data_to_send = FALSE;

  if (type == WM_SYSCHAR)
  {
    /*************************************************************************/
    /* Alt key pressed                                                       */
    /*************************************************************************/
    if ((key >= '1') &&
        (key <= '9'))
    {
      /***********************************************************************/
      /* ALT-1 to ALT-9 0xF1 is the AID code for PF1.  Follow this with the  */
      /* cursor address                                                      */
      /***********************************************************************/
      *write_data = 0xF1 + key - '1';
      *(write_data + 1) = 0x40;
      *(write_data + 2) = 0x40;
      write_len = 3;
      data_to_send = TRUE;
    }
  }
  else
  {
    /*************************************************************************/
    /* Ordinary ASCII char                                                   */
    /*************************************************************************/
    if (key == SWITKEY)
    {
      /***********************************************************************/
      /* Hit key to switch between sessions                                  */
      /***********************************************************************/
      if (lu_session)
      {
        lu_session = FALSE;
      }
      else
      {
        lu_session = TRUE;
      }
      InvalidateRect (hWnd, NULL, TRUE);
    }
    else
    {
      /***********************************************************************/
      /* Key should be real data.  Add it to the string                      */
      /***********************************************************************/
      if (key == 13)
      {
        /*********************************************************************/
        /* If user pressed return key then send the data.  Reset data_offset */
        /* for next data.                                                    */
        /*********************************************************************/
        write_data[data_offset++] = '\0';
        data_to_send = TRUE;
        data_offset  = 0;

        /*********************************************************************/
        /* Convert data to EBCDIC                                            */
        /*********************************************************************/
        convert_to_ebc.len = (unsigned short) (strlen(write_data) );
        if (convert_to_ebc.len > 0)
        {
          ACSSVC_C((LONG)((UCHAR FAR *)&convert_to_ebc));
        }
        write_len = convert_to_ebc.len;

        /*********************************************************************/
        /* Allow for ENTER AID if necessary                                  */
        /*********************************************************************/
        if (lu_session)
        {
          write_data -= WRITE_EXTRA;
          write_len  += WRITE_EXTRA;
        }
      }
      else if (key == 8)
      {
        /*********************************************************************/
        /* Backspace.  Delete last char                                      */
        /*********************************************************************/
        if (data_offset > 0)
        {
          data_offset--;
        }
      }
      else if (key != 0)
      {
        /*********************************************************************/
        /* ASCII char.  Add it to the data buffer                            */
        /*********************************************************************/
        write_data[data_offset++] = (UCHAR) key;

      }
      /***********************************************************************/
      /* Invalidate our window so that the new data is displayed             */
      /***********************************************************************/
      InvalidateRect (hWnd, NULL, TRUE);
    }
  }


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
    WinRUI(hWnd, (LUA_VERB_RECORD FAR *) &other_verb);
    if (!other_verb.common.lua_flag2.async)
    {
      /***********************************************************************/
      /* Verb completed immediately.  Post our own completion message        */
      /***********************************************************************/
      PostMessage (hWnd, verb_complete, 0, (LPARAM) (VOID FAR *)&other_verb);
    }

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
  rpq_verb.common.lua_rh.bci           = 1;
  rpq_verb.common.lua_rh.eci           = 1;
  rpq_verb.common.lua_rh.dr1i          = 1;

  /***************************************************************************/
  /* All inbound requests flow RQD with the BBI and CDI flags set depending  */
  /* on the current session state.                                           */
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
    issue_rpq = FALSE;
  }

  if (issue_rpq)
  {
    WinRUI(hWnd, (LUA_VERB_RECORD FAR *) &rpq_verb);
    if (!rpq_verb.common.lua_flag2.async)
    {
      /***********************************************************************/
      /* Verb completed immediately.  Post our own completion message        */
      /***********************************************************************/
      PostMessage (hWnd, verb_complete, 0, (LPARAM) (VOID FAR *)&rpq_verb);
    }
  }

  return(issue_rpq);
}  /* issue_rpq                                                              */

/**PROC+**********************************************************************/
/* Name:      add_to_display_buffer                                          */
/*                                                                           */
/* Purpose:   add data to the display buffer                                 */
/*                                                                           */
/* Returns:   void                                                           */
/*                                                                           */
/* Params:    IN data - data to be displayed                                 */
/*                                                                           */
/* Operation: Add the zero terminated data string to the circular display    */
/* buffer.  Cope with wrapping                                               */
/*                                                                           */
/**PROC-**********************************************************************/
void add_to_display_buffer (data)

UCHAR FAR * data;
{
  UINT data_length;         /* length of new data to display                 */
  BOOL need_to_wrap;        /* do we need to wrap to the start of the buffer */
  UINT copy_length;         /* length of data to copy                        */


  data_length = _fstrlen (data);

  /***************************************************************************/
  /* Work out whether the data will go over the end of the dispaly buffer.   */
  /* If it will, wrap it back over the start of the buffer.                  */
  /***************************************************************************/
  need_to_wrap = (buffer_end + data_length > DISPLAY_BUFFER_SIZE);

  if (need_to_wrap)
  {
    copy_length = DISPLAY_BUFFER_SIZE - buffer_end;
    wrapped = TRUE;
  }
  else
  {
    copy_length = data_length;
  }

  /***************************************************************************/
  /* Copy as much data as will fit into the buffer                           */
  /***************************************************************************/
  _fmemcpy ((UCHAR FAR *) (display_buffer + buffer_end),
            data,
            copy_length);

  /***************************************************************************/
  /* If there is more data to copy, copy it to the start of the buffer       */
  /* Set up the new end point.                                               */
  /***************************************************************************/
  if (need_to_wrap)
  {
    _fmemcpy ((UCHAR FAR *)display_buffer,
              data + copy_length,
              data_length - copy_length);

    buffer_end   = data_length - copy_length;
  }
  else
  {
    buffer_end   += data_length;
  }

  /***************************************************************************/
  /* Cause the window to be re-painted                                       */
  /***************************************************************************/
  InvalidateRect (hWnd, NULL, TRUE);

}  /* add_to_display_buffer                                                  */
