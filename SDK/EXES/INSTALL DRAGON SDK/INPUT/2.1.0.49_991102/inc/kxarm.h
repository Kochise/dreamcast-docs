;++
;
; Copyright (c) 1997  Microsoft Corporation
;
; Module Name:
;
;    kxarm.h
;
; Abstract:
;
;    This is an implementation of the WINCE/ARM Calling Sequence
;    Specification.
;
; Environment:
;    String Library
;
; Revision History:
;--

		GBLS    VBar
VBar	SETS    "|"
		GBLL	HaveExceptHandler
		GBLS	AreaName
		GBLS	FuncName
		GBLS	PrologName
		GBLS	FuncEndName
		GBLS	ExceptHandler
		GBLS	ExceptData
AreaName SETS	"|.text|"
HaveExceptHandler SETL {FALSE}

	MACRO
	TEXTAREA
	AREA |.text|,ALIGN=2,CODE,READONLY
AreaName SETS "|.text|"
	MEND

    MACRO
    THUMBAREA
    AREA |.text|,ALIGN=2,CODE,READONLY,THUMB
AreaName SETS "|.text|"
    MEND

	MACRO
	STARTUPTEXT
	AREA |.astart|,ALIGN=2,CODE
AreaName SETS "|.astart|"
	MEND

	MACRO
	START_REGION	$NameBegin
	LCLS    TempName
TempName SETS    VBar:CC:"$NameBegin":CC:VBar
	EXPORT	$TempName[DATA]
$TempName
	MEND

	MACRO
	END_REGION		$NameEnd
	LCLS    TempName
TempName SETS    VBar:CC:"$NameEnd":CC:VBar
	EXPORT	$TempName[DATA]
$TempName
	MEND

	MACRO
	NESTED_ENTRY	$Name
FuncName    SETS    VBar:CC:"$Name":CC:VBar
PrologName  SETS    VBar:CC:"$Name":CC:"_Prolog":CC:VBar
FuncEndName SETS    VBar:CC:"$Name":CC:"_end":CC:VBar
	LCLS	ExceptBit
	IF HaveExceptHandler
ExceptBit   SETS	"0x80000000"
	ELSE
ExceptBit   SETS	"0"
	ENDIF

	AREA |.pdata|,ALIGN=2,PDATA
	DCD	    $FuncName
    DCD     (($PrologName-$FuncName)/4) :OR: ((($FuncEndName-$FuncName)/4):SHL:8) :OR: 0x40000000 :OR: $ExceptBit

	AREA $AreaName,CODE,READONLY
	ALIGN	2
	EXPORT	$FuncName
	IF HaveExceptHandler
    DCD $ExceptHandler
    DCD $ExceptData
HaveExceptHandler SETL {FALSE}
	ENDIF
$FuncName
	ROUT
	MEND

	MACRO
	PROLOG_END
$PrologName
	MEND

	MACRO
	LEAF_ENTRY	$Name
FuncName SETS    VBar:CC:"$Name":CC:VBar
PrologName SETS	"Invalid Prolog"
FuncEndName SETS    VBar:CC:"$Name":CC:"_end":CC:VBar
	ALIGN	2
	EXPORT	$FuncName
$FuncName
	ROUT
	MEND

	MACRO
	ALTERNATE_ENTRY	$Name
	LCLS    TempName
TempName SETS    VBar:CC:"$Name":CC:VBar
	EXPORT	$TempName
$TempName
	MEND

	MACRO
	ENTRY_END	$Name
$FuncEndName
	MEND

	MACRO
	EXCEPTION_HANDLER	$Handler
ExceptHandler SETS    VBar:CC:"$Handler":CC:VBar
ExceptData SETS "0"
HaveExceptHandler SETL {TRUE}
	MEND

	MACRO
	EXCEPTION_HANDLER_DATA	$Handler, $HandlerData
ExceptHandler SETS    VBar:CC:"$Handler":CC:VBar
ExceptData SETS    VBar:CC:"$HandlerData":CC:VBar
HaveExceptHandler SETL {TRUE}
	MEND

	MACRO
	EXCEPTION_HANDLER_MILLICODE	$Handler, $HandlerData
ExceptHandler SETS    "$Handler"
ExceptData SETS    "$HandlerData"
HaveExceptHandler SETL {TRUE}
	MEND

	END
