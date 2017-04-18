
/**MOD+***********************************************************************/
/* Module:   semfperf.h                                                      */
/*                                                                           */
/* Purpose:  performance monitor dll structures                              */
/*                                                                           */
/* (C) COPYRIGHT DATA CONNECTION LIMITED 1991, 1992, 1993, 1994              */
/*                                                                           */
/*****************************************************************************/
/* SCAL SGF 16/06/94  Make default scales flexible                           */
/* MAXL AB  23/06/95  We now support 250 link services                       */
/**MOD-***********************************************************************/

#include <snapmon.h>

/************************************************************************MAXL*/
/* #define for the maximum number of LS available                       *MAXL*/
/************************************************************************MAXL*/
#define MAX_LINK_SVCS 250

typedef struct _LinkPerfShrHdr {
    ULONG          NumberOfLinkServices;
} LinkPerfShrHdr;

