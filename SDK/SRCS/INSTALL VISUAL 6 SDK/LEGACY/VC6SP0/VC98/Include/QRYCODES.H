// *************************************************************************
//
//  File: QRYCODES.H
//
//  Copyright (c) 1994, 1995 Microsoft Corp.
//
//
//
//  This file contains the Query operator manifests for queries against
//  machines. This is part of the SMS SDK.
//
//
//  History:
//      JonShu      01-April-1994       Created.
//                                      This was extracted from query.h
//
// *************************************************************************

#ifndef _QUERYCODES_H_
#define _QUERYCODES_H_

// Query Operators.
// ================

#define QOP_NOOP                0

#define QOP_BOOL_EQ             1
#define QOP_BOOL_NEQ            2
#define QOP_BOOL_FIRST          QOP_BOOL_EQ
#define QOP_BOOL_LAST           QOP_BOOL_NEQ

#define QOP_NUMERIC_EQ          3
#define QOP_NUMERIC_NEQ         4
#define QOP_NUMERIC_GT          5
#define QOP_NUMERIC_LT          6
#define QOP_NUMERIC_GTE         7
#define QOP_NUMERIC_LTE         8
#define QOP_NUMERIC_FIRST       QOP_NUMERIC_EQ
#define QOP_NUMERIC_LAST        QOP_NUMERIC_LTE

#define QOP_STR_EQ              9
#define QOP_STR_NEQ             10
#define QOP_STR_GT              11
#define QOP_STR_LT              12
#define QOP_STR_GTE             13
#define QOP_STR_LTE             14
#define QOP_STR_LIKE            15
#define QOP_STR_NOTLIKE         16
#define QOP_STR_FIRST           QOP_STR_EQ
#define QOP_STR_LAST            QOP_STR_NOTLIKE

#define QOP_UPCASE_EQ           17
#define QOP_UPCASE_NEQ          18
#define QOP_UPCASE_GT           19
#define QOP_UPCASE_LT           20
#define QOP_UPCASE_GTE          21
#define QOP_UPCASE_LTE          22
#define QOP_UPCASE_LIKE         23
#define QOP_UPCASE_NOTLIKE      24
#define QOP_UPCASE_FIRST        QOP_UPCASE_EQ
#define QOP_UPCASE_LAST         QOP_UPCASE_NOTLIKE

#define QOP_DATETIME_EQ         25
#define QOP_DATETIME_NEQ        26
#define QOP_DATETIME_GT         27
#define QOP_DATETIME_LT         28
#define QOP_DATETIME_GTE        29
#define QOP_DATETIME_LTE        30
#define QOP_DATETIME_FIRST      QOP_DATETIME_EQ
#define QOP_DATETIME_LAST       QOP_DATETIME_LTE

#define QOP_DATE_EQ             31
#define QOP_DATE_NEQ            32
#define QOP_DATE_GT             33
#define QOP_DATE_LT             34
#define QOP_DATE_GTE            35
#define QOP_DATE_LTE            36
#define QOP_DATE_FIRST          QOP_DATE_EQ
#define QOP_DATE_LAST           QOP_DATE_LTE

#define QOP_TIME_EQ             37
#define QOP_TIME_NEQ            38
#define QOP_TIME_GT             39
#define QOP_TIME_LT             40
#define QOP_TIME_GTE            41
#define QOP_TIME_LTE            42
#define QOP_TIME_FIRST          QOP_TIME_EQ
#define QOP_TIME_LAST           QOP_TIME_LTE

#define QOP_YEAR_EQ             43
#define QOP_YEAR_NEQ            44
#define QOP_YEAR_GT             45
#define QOP_YEAR_LT             46
#define QOP_YEAR_GTE            47
#define QOP_YEAR_LTE            48
#define QOP_YEAR_FIRST          QOP_YEAR_EQ
#define QOP_YEAR_LAST           QOP_YEAR_LTE

#define QOP_MONTH_EQ            49
#define QOP_MONTH_NEQ           50
#define QOP_MONTH_GT            51
#define QOP_MONTH_LT            52
#define QOP_MONTH_GTE           53
#define QOP_MONTH_LTE           54
#define QOP_MONTH_FIRST         QOP_MONTH_EQ
#define QOP_MONTH_LAST          QOP_MONTH_LTE

#define QOP_DAY_EQ              55
#define QOP_DAY_NEQ             56
#define QOP_DAY_GT              57
#define QOP_DAY_LT              58
#define QOP_DAY_GTE             59
#define QOP_DAY_LTE             60
#define QOP_DAY_FIRST           QOP_DAY_EQ
#define QOP_DAY_LAST            QOP_DAY_LTE

#define QOP_HOUR_EQ             61
#define QOP_HOUR_NEQ            62
#define QOP_HOUR_GT             63
#define QOP_HOUR_LT             64
#define QOP_HOUR_GTE            65
#define QOP_HOUR_LTE            66
#define QOP_HOUR_FIRST          QOP_HOUR_EQ
#define QOP_HOUR_LAST           QOP_HOUR_LTE

#define QOP_MINUTE_EQ           67
#define QOP_MINUTE_NEQ          68
#define QOP_MINUTE_GT           69
#define QOP_MINUTE_LT           70
#define QOP_MINUTE_GTE          71
#define QOP_MINUTE_LTE          72
#define QOP_MINUTE_FIRST        QOP_MINUTE_EQ
#define QOP_MINUTE_LAST         QOP_MINUTE_LTE

#define QOP_SECOND_EQ           73
#define QOP_SECOND_NEQ          74
#define QOP_SECOND_GT           75
#define QOP_SECOND_LT           76
#define QOP_SECOND_GTE          77
#define QOP_SECOND_LTE          78
#define QOP_SECOND_FIRST        QOP_SECOND_EQ
#define QOP_SECOND_LAST         QOP_SECOND_LTE

#define QOP_LAST                QOP_SECOND_LAST


//***************************************************************************
// OPERATOR STRING TABLE.
//
// The sequence of the operators in this array is identical to the
// sequence of of the QOP_ symbols in QUERYTOK.H.  If the order of one
// is changed, the order of the other must be changed to match.
// Eventually, this table will be replaced with a string table resource
// of some kind.   See CQueryToken::OperatorToString().
//
//***************************************************************************
static char *OpName[] = {
    /* QOP_NOOP */              "<none>",

    /* BOOL operators */

    /* QOP_BOOL_EQ,  */         "is (boolean)",
    /* QOP_BOOL_NEQ, */         "is not (boolean)",

    /* NUMERIC operators */

    /* QOP_NUMERIC_EQ,  */      "is equal to",
    /* QOP_NUMERIC_NEQ, */      "is not equal to",
    /* QOP_NUMERIC_GT,  */      "is greater than",
    /* QOP_NUMERIC_LT,  */      "is less than",
    /* QOP_NUMERIC_GTE, */      "is greater than or equal to",
    /* QOP_NUMERIC_LTE, */      "is less than or equal to",

    /* Case-sensitive string operators */

    /* QOP_STR_EQ      */       "is",
    /* QOP_STR_NEQ     */       "is not",
    /* QOP_STR_GT      */       "comes after",
    /* QOP_STR_LT      */       "comes before",
    /* QOP_STR_GTE     */       "is same as or comes after",
    /* QOP_STR_LTE     */       "is same as or comes before",
    /* QOP_STR_LIKE    */       "is like",
    /* QOP_STR_NOTLIKE */       "is not like",

    /* Upper-case-evaluation string operators */

    /* QOP_UPCASE_EQ,     */    "is (upper case)",
    /* QOP_UPCASE_NEQ,    */    "is not (upper case)",
    /* QOP_UPCASE_GT,     */    "comes after (upper case)",
    /* QOP_UPCASE_LT,     */    "comes before (upper case)",
    /* QOP_UPCASE_GTE,    */    "is same as or comes after (upper case)",
    /* QOP_UPCASE_LTE,    */    "is same as or comes before (upper case)",
    /* QOP_UPCASE_LIKE,   */    "is like (upper case)",
    /* QOP_UPCASE_NOTLIKE */    "is not like (upper case)",

    /* Date-Time operators */

    /* QOP_DATETIME_EQ,  */     "date/time is",
    /* QOP_DATETIME_NEQ, */     "date/time is not",
    /* QOP_DATETIME_GT,  */     "date/time is after",
    /* QOP_DATETIME_LT,  */     "date/time is before",
    /* QOP_DATETIME_GTE, */     "date/time is on or after",
    /* QOP_DATETIME_LTE, */     "date/time is on or before",

    /* Date operators */

    /* QOP_DATE_EQ,  */         "date is",
    /* QOP_DATE_NEQ, */         "date is not",
    /* QOP_DATE_GT,  */         "date is after",
    /* QOP_DATE_LT,  */         "date is before",
    /* QOP_DATE_GTE, */         "date is on or after",
    /* QOP_DATE_LTE, */         "date is on or before",

    /* Time operators */

    /* QOP_TIME_EQ,  */         "time is",
    /* QOP_TIME_NEQ, */         "time is not",
    /* QOP_TIME_GT,  */         "time is after",
    /* QOP_TIME_LT,  */         "time is before",
    /* QOP_TIME_GTE, */         "time is at or after",
    /* QOP_TIME_LTE, */         "time is at or before",

    /* Year operators */

    /* QOP_YEAR_EQ,  */         "year is",
    /* QOP_YEAR_NEQ, */         "year is not",
    /* QOP_YEAR_GT,  */         "year is after",
    /* QOP_YEAR_LT,  */         "year is before",
    /* QOP_YEAR_GTE, */         "year is on or after",
    /* QOP_YEAR_LTE, */         "year is on or before",

    /* Month operators */

    /* QOP_MONTH_EQ  */         "month is",
    /* QOP_MONTH_NEQ */         "month is not",
    /* QOP_MONTH_GT  */         "month is after",
    /* QOP_MONTH_LT  */         "month is before",
    /* QOP_MONTH_GTE */         "month is on or after",
    /* QOP_MONTH_LTE */         "month is on or before",

    /* Day operators */

    /* QOP_DAY_EQ,  */          "day is",
    /* QOP_DAY_NEQ, */          "day is not",
    /* QOP_DAY_GT,  */          "day is after",
    /* QOP_DAY_LT,  */          "day is before",
    /* QOP_DAY_GTE, */          "day is on or after",
    /* QOP_DAY_LTE, */          "day is on or before",

    /* Hour operators */

    /* QOP_HOUR_EQ,  */         "hour is",
    /* QOP_HOUR_NEQ, */         "hour is not",
    /* QOP_HOUR_GT,  */         "hour is after",
    /* QOP_HOUR_LT,  */         "hour is before",
    /* QOP_HOUR_GTE, */         "hour is at or after",
    /* QOP_HOUR_LTE, */         "hour is at or before",

    /* Minute operators */

    /* QOP_MINUTE_EQ,  */       "minute is",
    /* QOP_MINUTE_NEQ, */       "minute is not",
    /* QOP_MINUTE_GT,  */       "minute is after",
    /* QOP_MINUTE_LT,  */       "minute is before",
    /* QOP_MINUTE_GTE, */       "minute is at or after",
    /* QOP_MINUTE_LTE, */       "minute is at or before",

    /* Second operators */

    /* QOP_SECOND_EQ,  */       "second is",
    /* QOP_SECOND_NEQ, */       "second is not",
    /* QOP_SECOND_GT,  */       "second is after",
    /* QOP_SECOND_LT,  */       "second is before",
    /* QOP_SECOND_GTE, */       "second is at or after",
    /* QOP_SECOND_LTE, */       "second is at or before"
};

#endif  // _QUERYCODES_H_


/* EOF: qrycodes.h */

