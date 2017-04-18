Option Explicit
'// *************************************************************************
'//
'//  File: QRYCODES.H
'//
'//  Copyright (c) 1994, Microsoft Corp.
'//
'//
'//
'//  This file contains the Query operator manifests for queries against
'//  machines. This is part of the SMS SDK.
'//
'//
'//  History:
'//      JonShu      01-April-1994       Created.
'//                                      This was extracted from query.h
'//      GFF@SEA     17-Mar-95           VBified.
'//
'// *************************************************************************
'
'// Query Operators.
'// ================
'
 Global Const QOP_NOOP = 0
'
 Global Const QOP_BOOL_EQ = 1
 Global Const QOP_BOOL_NEQ = 2
 Global Const QOP_BOOL_FIRST = QOP_BOOL_EQ
 Global Const QOP_BOOL_LAST = QOP_BOOL_NEQ
'
 Global Const QOP_NUMERIC_EQ = 3
 Global Const QOP_NUMERIC_NEQ = 4
 Global Const QOP_NUMERIC_GT = 5
 Global Const QOP_NUMERIC_LT = 6
 Global Const QOP_NUMERIC_GTE = 7
 Global Const QOP_NUMERIC_LTE = 8
 Global Const QOP_NUMERIC_FIRST = QOP_NUMERIC_EQ
 Global Const QOP_NUMERIC_LAST = QOP_NUMERIC_LTE
'
 Global Const QOP_STR_EQ = 9
 Global Const QOP_STR_NEQ = 10
 Global Const QOP_STR_GT = 11
 Global Const QOP_STR_LT = 12
 Global Const QOP_STR_GTE = 13
 Global Const QOP_STR_LTE = 14
 Global Const QOP_STR_LIKE = 15
 Global Const QOP_STR_NOTLIKE = 16
 Global Const QOP_STR_FIRST = QOP_STR_EQ
 Global Const QOP_STR_LAST = QOP_STR_NOTLIKE
'
 Global Const QOP_UPCASE_EQ = 17
 Global Const QOP_UPCASE_NEQ = 18
 Global Const QOP_UPCASE_GT = 19
 Global Const QOP_UPCASE_LT = 20
 Global Const QOP_UPCASE_GTE = 21
 Global Const QOP_UPCASE_LTE = 22
 Global Const QOP_UPCASE_LIKE = 23
 Global Const QOP_UPCASE_NOTLIKE = 24
 Global Const QOP_UPCASE_FIRST = QOP_UPCASE_EQ
 Global Const QOP_UPCASE_LAST = QOP_UPCASE_NOTLIKE
'
 Global Const QOP_DATETIME_EQ = 25
 Global Const QOP_DATETIME_NEQ = 26
 Global Const QOP_DATETIME_GT = 27
 Global Const QOP_DATETIME_LT = 28
 Global Const QOP_DATETIME_GTE = 29
 Global Const QOP_DATETIME_LTE = 30
 Global Const QOP_DATETIME_FIRST = QOP_DATETIME_EQ
 Global Const QOP_DATETIME_LAST = QOP_DATETIME_LTE
'
 Global Const QOP_DATE_EQ = 31
 Global Const QOP_DATE_NEQ = 32
 Global Const QOP_DATE_GT = 33
 Global Const QOP_DATE_LT = 34
 Global Const QOP_DATE_GTE = 35
 Global Const QOP_DATE_LTE = 36
 Global Const QOP_DATE_FIRST = QOP_DATE_EQ
 Global Const QOP_DATE_LAST = QOP_DATE_LTE
'
 Global Const QOP_TIME_EQ = 37
 Global Const QOP_TIME_NEQ = 38
 Global Const QOP_TIME_GT = 39
 Global Const QOP_TIME_LT = 40
 Global Const QOP_TIME_GTE = 41
 Global Const QOP_TIME_LTE = 42
 Global Const QOP_TIME_FIRST = QOP_TIME_EQ
 Global Const QOP_TIME_LAST = QOP_TIME_LTE
'
 Global Const QOP_YEAR_EQ = 43
 Global Const QOP_YEAR_NEQ = 44
 Global Const QOP_YEAR_GT = 45
 Global Const QOP_YEAR_LT = 46
 Global Const QOP_YEAR_GTE = 47
 Global Const QOP_YEAR_LTE = 48
 Global Const QOP_YEAR_FIRST = QOP_YEAR_EQ
 Global Const QOP_YEAR_LAST = QOP_YEAR_LTE
'
 Global Const QOP_MONTH_EQ = 49
 Global Const QOP_MONTH_NEQ = 50
 Global Const QOP_MONTH_GT = 51
 Global Const QOP_MONTH_LT = 52
 Global Const QOP_MONTH_GTE = 53
 Global Const QOP_MONTH_LTE = 54
 Global Const QOP_MONTH_FIRST = QOP_MONTH_EQ
 Global Const QOP_MONTH_LAST = QOP_MONTH_LTE
'
 Global Const QOP_DAY_EQ = 55
 Global Const QOP_DAY_NEQ = 56
 Global Const QOP_DAY_GT = 57
 Global Const QOP_DAY_LT = 58
 Global Const QOP_DAY_GTE = 59
 Global Const QOP_DAY_LTE = 60
 Global Const QOP_DAY_FIRST = QOP_DAY_EQ
 Global Const QOP_DAY_LAST = QOP_DAY_LTE
'
 Global Const QOP_HOUR_EQ = 61
 Global Const QOP_HOUR_NEQ = 62
 Global Const QOP_HOUR_GT = 63
 Global Const QOP_HOUR_LT = 64
 Global Const QOP_HOUR_GTE = 65
 Global Const QOP_HOUR_LTE = 66
 Global Const QOP_HOUR_FIRST = QOP_HOUR_EQ
 Global Const QOP_HOUR_LAST = QOP_HOUR_LTE
'
 Global Const QOP_MINUTE_EQ = 67
 Global Const QOP_MINUTE_NEQ = 68
 Global Const QOP_MINUTE_GT = 69
 Global Const QOP_MINUTE_LT = 70
 Global Const QOP_MINUTE_GTE = 71
 Global Const QOP_MINUTE_LTE = 72
 Global Const QOP_MINUTE_FIRST = QOP_MINUTE_EQ
 Global Const QOP_MINUTE_LAST = QOP_MINUTE_LTE
'
 Global Const QOP_SECOND_EQ = 73
 Global Const QOP_SECOND_NEQ = 74
 Global Const QOP_SECOND_GT = 75
 Global Const QOP_SECOND_LT = 76
 Global Const QOP_SECOND_GTE = 77
 Global Const QOP_SECOND_LTE = 78
 Global Const QOP_SECOND_FIRST = QOP_SECOND_EQ
 Global Const QOP_SECOND_LAST = QOP_SECOND_LTE
'
 Global Const QOP_LAST = QOP_SECOND_LAST
'
'
'//***************************************************************************
'// OPERATOR STRING TABLE.
'//
'// The sequence of the operators in this array is identical to the
'// sequence of of the QOP_ symbols in QUERYTOK.H.  If the order of one
'// is changed, the order of the other must be changed to match.
'// Eventually, this table will be replaced with a string table resource
'// of some kind.   See CQueryToken::OperatorToString().
'//
'//***************************************************************************
'This array is initialized in Init_OpName_array()
 Global OpName$(0 To QOP_LAST)

 Sub Init_OpName_array ()
     OpName(QOP_NOOP) = "<none>"
 
     'BOOL operators
 
     OpName(QOP_BOOL_EQ) = "is (boolean)"
     OpName(QOP_BOOL_NEQ) = "is not (boolean)"
 
     'NUMERIC operators
 
     OpName(QOP_NUMERIC_EQ) = "is equal to"
     OpName(QOP_NUMERIC_NEQ) = "is not equal to"
     OpName(QOP_NUMERIC_GT) = "is greater than"
     OpName(QOP_NUMERIC_LT) = "is less than"
     OpName(QOP_NUMERIC_GTE) = "is greater than or equal to"
     OpName(QOP_NUMERIC_LTE) = "is less than or equal to"
 
     'Case-sensitive string operators
 
     OpName(QOP_STR_EQ) = "is"
     OpName(QOP_STR_NEQ) = "is not"
     OpName(QOP_STR_GT) = "comes after"
     OpName(QOP_STR_LT) = "comes before"
     OpName(QOP_STR_GTE) = "is same as or comes after"
     OpName(QOP_STR_LTE) = "is same as or comes before"
     OpName(QOP_STR_LIKE) = "is like"
     OpName(QOP_STR_NOTLIKE) = "is not like"
 
     'Upper-case-evaluation string operators
 
     OpName(QOP_UPCASE_EQ) = "is (upper case)"
     OpName(QOP_UPCASE_NEQ) = "is not (upper case)"
     OpName(QOP_UPCASE_GT) = "comes after (upper case)"
     OpName(QOP_UPCASE_LT) = "comes before (upper case)"
     OpName(QOP_UPCASE_GTE) = "is same as or comes after (upper case)"
     OpName(QOP_UPCASE_LTE) = "is same as or comes before (upper case)"
     OpName(QOP_UPCASE_LIKE) = "is like (upper case)"
     OpName(QOP_UPCASE_NOTLIKE) = "is not like (upper case)"
 
     'Date-Time operators
 
     OpName(QOP_DATETIME_EQ) = "date/time is"
     OpName(QOP_DATETIME_NEQ) = "date/time is not"
     OpName(QOP_DATETIME_GT) = "date/time is after"
     OpName(QOP_DATETIME_LT) = "date/time is before"
     OpName(QOP_DATETIME_GTE) = "date/time is on or after"
     OpName(QOP_DATETIME_LTE) = "date/time is on or before"
 
     'Date operators
 
     OpName(QOP_DATE_EQ) = "date is"
     OpName(QOP_DATE_NEQ) = "date is not"
     OpName(QOP_DATE_GT) = "date is after"
     OpName(QOP_DATE_LT) = "date is before"
     OpName(QOP_DATE_GTE) = "date is on or after"
     OpName(QOP_DATE_LTE) = "date is on or before"
 
     'Time operators
 
     OpName(QOP_TIME_EQ) = "time is"
     OpName(QOP_TIME_NEQ) = "time is not"
     OpName(QOP_TIME_GT) = "time is after"
     OpName(QOP_TIME_LT) = "time is before"
     OpName(QOP_TIME_GTE) = "time is at or after"
     OpName(QOP_TIME_LTE) = "time is at or before"
 
     'Year operators
 
     OpName(QOP_YEAR_EQ) = "year is"
     OpName(QOP_YEAR_NEQ) = "year is not"
     OpName(QOP_YEAR_GT) = "year is after"
     OpName(QOP_YEAR_LT) = "year is before"
     OpName(QOP_YEAR_GTE) = "year is on or after"
     OpName(QOP_YEAR_LTE) = "year is on or before"
 
     'Month operators
 
     OpName(QOP_MONTH_EQ) = "month is"
     OpName(QOP_MONTH_NEQ) = "month is not"
     OpName(QOP_MONTH_GT) = "month is after"
     OpName(QOP_MONTH_LT) = "month is before"
     OpName(QOP_MONTH_GTE) = "month is on or after"
     OpName(QOP_MONTH_LTE) = "month is on or before"
 
     'Day operators
 
     OpName(QOP_DAY_EQ) = "day is"
     OpName(QOP_DAY_NEQ) = "day is not"
     OpName(QOP_DAY_GT) = "day is after"
     OpName(QOP_DAY_LT) = "day is before"
     OpName(QOP_DAY_GTE) = "day is on or after"
     OpName(QOP_DAY_LTE) = "day is on or before"
 
     'Hour operators
 
     OpName(QOP_HOUR_EQ) = "hour is"
     OpName(QOP_HOUR_NEQ) = "hour is not"
     OpName(QOP_HOUR_GT) = "hour is after"
     OpName(QOP_HOUR_LT) = "hour is before"
     OpName(QOP_HOUR_GTE) = "hour is at or after"
     OpName(QOP_HOUR_LTE) = "hour is at or before"
 
     'Minute operators
 
     OpName(QOP_MINUTE_EQ) = "minute is"
     OpName(QOP_MINUTE_NEQ) = "minute is not"
     OpName(QOP_MINUTE_GT) = "minute is after"
     OpName(QOP_MINUTE_LT) = "minute is before"
     OpName(QOP_MINUTE_GTE) = "minute is at or after"
     OpName(QOP_MINUTE_LTE) = "minute is at or before"
 
     'Second operators
 
     OpName(QOP_SECOND_EQ) = "second is"
     OpName(QOP_SECOND_NEQ) = "second is not"
     OpName(QOP_SECOND_GT) = "second is after"
     OpName(QOP_SECOND_LT) = "second is before"
     OpName(QOP_SECOND_GTE) = "second is at or after"
     OpName(QOP_SECOND_LTE) = "second is at or before"
 End Sub

 Sub Init_QRYCODES ()
     Init_OpName_array
 End Sub

