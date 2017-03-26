/*
 *--------------------------------------------------------------------------
 *  FILE: sg_syrtc.h
 *
 *      Copyright(c) 1998 SEGA System R&D Dept.
 *
 *  PURPOSE:
 *
 *      Real Time Clock in AICA headder
 *
 *  DESCRIPTION:
 *
 *      This is to get date and time in real world.
 *
 *  AUTHOR(S):
 *
 *      1998/3/18  SEKI Masahiro Ver.0.40
 *
 *  MOD HISTORY:
 *
 *      1998/4/1  SEKI Masahiro Ver.0.41 based on specification 0.41
 *           (1) Added syRtcStopServer(), syRtcStartServer(), syRtcGetStat().
 *           (2) Added SYD_RTC_STAT_***.
 *           (3) Modified functions accessing to registers in AICA.
 *               From 2-time-call to 1-time-call.
 *      1998/4.3  SEKI Masahiro Ver.0.42 based on specification 0.42
 *           (1) Removed syRtcStopServer(), syRtcStartServer()
 *           (2) Added syRtcSetServerMode()
 *           (3) Functions have construction arguments are changed to pointer to construction arguments
 *           (4) Modified syRtcGetStat(), syRtcGetDate()
 *      1998/5/8  SEKI Masahiro
 *           (1) Fixed to G2 library docment ver0.42
 *      1998/7/6  SEKI Masahiro
 *           (1) Fixed comments for members of SYS_RTC_DATE
 *      1998/7/22 SEKI Masahiro
 *           (1) Adapted for shaking high rtc register
 *
 *
 *
 *--------------------------------------------------------------------------
 */
#ifndef _SG_RTC_H_
#define _SG_RTC_H_

/**************************************************************************/
/******** Define **********************************************************/
/**************************************************************************/
/******** Function error code *********************************************/
#define SYD_RTC_ERR_OK        (0)         /* No error                     */
#define SYD_RTC_ERR_FATAL     (-1)        /* Fatal error has occured      */

/******** Function error code *********************************************/
#define SYD_RTC_STAT_ACTIVE   (0)         /* RTC Server is running        */
#define SYD_RTC_STAT_PASSIVE  (1)         /* RTC Server is stopping       */

/******** Date definition *************************************************/
#define SYD_RTC_FIRSTYEAR     (1950)     /* RTC count is 0 as 1950-01-01  */
#define SYD_RTC_FIRSTMONTH    (1)        /* 0:00:00                       */
#define SYD_RTC_FIRSTDAY      (1)        /*                               */
#define SYD_RTC_FIRSTHOUR     (0)        /*                               */
#define SYD_RTC_FIRSTMINUTE   (0)        /*                               */
#define SYD_RTC_FIRSTSECOND   (0)        /*                               */

/**************************************************************************/
/******** Structures ******************************************************/
/**************************************************************************/
/******** Structure for date **********************************************/
typedef struct _SYS_RTC_DATE {
    Uint16 year;                   /* year:        1950...2085            */
    Uint8  month;                  /* month:       1...12                 */
    Uint8  day;                    /* day:         1...31                 */
    Uint8  hour;                   /* hour:        0...23                 */
    Uint8  minute;                 /* minute:      0...59                 */
    Uint8  second;                 /* second:      0...59                 */
    Uint8  dayofweek;              /* day of week: 0(Sunday)...6(Saturday)*/
    Uint8  ageofmoon;              /* age of the moon: 0(new moon)...15(full moon)...29 */
} SYS_RTC_DATE;

/**************************************************************************/
/******** Functions *******************************************************/
/**************************************************************************/
/******** Library initialization and termination **************************/
Sint32 syRtcInit( void );
void syRtcFinish( void );

/******** RTC Operation ***************************************************/
void syRtcExecServer( void );
Sint32 syRtcGetDate( SYS_RTC_DATE *date );
Sint32 syRtcSetDate( const SYS_RTC_DATE *date );
void syRtcSetServerMode( const Sint32 mode );
Sint32 syRtcGetStat( void );

/******** Utility functions for date **************************************/
Sint32 syRtcCompareDate( const SYS_RTC_DATE *date1, const SYS_RTC_DATE *date2 );
void syRtcDateToCount( const SYS_RTC_DATE *date, Uint32 *count );
void syRtcCountToDate( const Uint32 count, SYS_RTC_DATE *date );
#endif /* _SG_RTC_H_ */
