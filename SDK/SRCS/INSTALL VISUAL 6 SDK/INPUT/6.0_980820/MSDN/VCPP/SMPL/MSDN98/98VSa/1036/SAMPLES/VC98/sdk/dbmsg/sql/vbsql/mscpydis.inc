'**************************************************************************
'********************  Setup Copy Disincentive API's  *********************
'**************************************************************************

'' System Dialog IDs
CONST CDALREADYUSED  = 7100
CONST CDBADFILE      = 7200
CONST CDCONFIRMINFO  = 7300
CONST CDGETNAME      = 7400
CONST CDGETNAMEORG   = 7500
CONST CDGETORG       = 7600
CONST CDBADNAME      = 7700
CONST CDBADORG       = 7800

DECLARE FUNCTION FInitSystem1 LIB "mscpydis.dll" (did%, sz$, fNet%) AS INTEGER
DECLARE FUNCTION FInitSystem3 LIB "mscpydis.dll" (did%, sz$, fAlways%) AS INTEGER
DECLARE FUNCTION FCloseSystem LIB "mscpydis.dll" (szSect$, szKey$, szDst$, wResType%, wResId%) AS INTEGER


'*************************************************************************
'****************  Setup Basic Wrapper Declarations  *********************
'*************************************************************************

DECLARE FUNCTION InitSystemRead  (did%, sz$, fNet%) AS INTEGER
DECLARE FUNCTION InitSystemWrite (did%, sz$, fAlways%) AS INTEGER
DECLARE SUB CloseSystem (szSect$, szKey$, szDst$, wResType%, wResId%)

DECLARE FUNCTION InitSystem (did%, sz$, fNet%) AS INTEGER
DECLARE FUNCTION InitSystemDlgs  (fNet%) AS INTEGER
DECLARE SUB BadNameOrg(dlg%)
DECLARE FUNCTION NameOrgOkay (dlg%, szName$, szOrg$) AS INTEGER

'**************************************************************************
FUNCTION InitSystemRead (did%, sz$, fNet%) STATIC AS INTEGER
'$ifdef DEBUG
    n% = 0
    IF (did% < 1) OR (did% > 999) THEN
        n% = 1
    ELSEIF (sz$ <> "") AND (INSTR(sz$,"\") <> 0) THEN
        n% = 2
    END IF

    IF n% > 0 THEN
        BadArgErr n%, "InitSystemRead", STR$(did%)+", "+sz$+", "+STR$(fNet%)
    END IF
'$endif ''DEBUG
    InitSystemRead = FInitSystem1(did%, sz$, fNet%)
END FUNCTION


'**************************************************************************
FUNCTION InitSystemWrite (did%, sz$, fAlways%) STATIC AS INTEGER
'$ifdef DEBUG
    n% = 0
    IF (did% < 1) OR (did% > 999) THEN
        n% = 1
    ELSEIF sz$ <> "" AND INSTR(sz$,"\") <> 0 THEN
        n% = 2
    END IF

    IF n% > 0 THEN
        BadArgErr n%, "InitSystemWrite", STR$(did%)+", "+sz$+", "+STR$(fAlways%)
    END IF
'$endif ''DEBUG
    InitSystemWrite = FInitSystem3(did%, sz$, fAlways%)
END FUNCTION


'*************************************************************************
SUB CloseSystem (szSect$, szKey$, szDst$, wResType%, wResId%) STATIC
'$ifdef DEBUG
    IF FValidInfSect(szSect$) = 0 THEN
        n% = 1
    ELSEIF szKey$ = "" THEN
        n% = 2
    ELSEIF FValidFATDir(szDst$) = 0 THEN
        n% = 3
    ELSE
        n% = 0
    END IF
    IF n% > 0 THEN
        BadArgErr n%, "CloseSystem", szSect$+", "+szKey$+", "+szDst$+", "+STR$(wResType%)+", "+STR$(wResId%)
    END IF
'$endif ''DEBUG

    IF FCloseSystem (szSect$, szKey$, szDst$, wResType%, wResId%) = 0 THEN
'$ifdef DEBUG
        StfApiErr saeFail, "CloseSystem", szSect$+", "+szKey$+", "+szDst$+", "+STR$(wResType%)+", "+STR$(wResId%)
'$endif ''DEBUG
        ERROR STFERR
    END IF
END SUB





'**************************************************************************
FUNCTION InitSystem (did%, sz$, fNet%) STATIC AS INTEGER
    IF InitSystemRead(did%, sz$, fNet%) = 0 THEN
        InitSystem = 0
    ELSEIF InitSystemDlgs(fNet%) = 0 THEN
        InitSystem = 0
    ELSEIF InitSystemWrite(did%, sz$, 0) = 0 THEN
        InitSystem = 0
    ELSE
        InitSystem = 1
    END IF
END FUNCTION



'**************************************************************************
FUNCTION InitSystemDlgs (fNet%) STATIC AS INTEGER

    fOkay%  = 0
    CDDLL$  = "mscuistf.dll"
    szName$ = GetSymbolValue("STF_CD_NAME")
    szOrg$  = GetSymbolValue("STF_CD_ORG")
    sz$ = MID$(GetSymbolValue("STF_CD_TYPE"), 1, 1)

    IF sz$ = "N" THEN
        IF fNet <> 0 THEN
            GOTO ISDN1
        ELSE
            GOTO ISDN2
        END IF
    ELSEIF (sz$ = "U") OR (sz$ = "O") THEN
        GOTO ISDU
    ELSEIF sz$ = "W" THEN
        GOTO ISDA
    ELSE
        GOTO ISDB
    END IF

ISDN1:
    SetSymbolValue "EditTextIn", ""
    SetSymbolValue "EditFocus", ""
ISDN1L1:
    sz$ = UIStartDlg(CDDLL$, CDGETORG, "FEditDlgProc", 0, "")

    IF sz$ = "CONTINUE" THEN
        szOrg$ = RTRIM$(LTRIM$(GetSymbolValue("EditTextOut")))
        IF szOrg$ = "" THEN
            BadNameOrg CDBADORG
            GOTO ISDN1L1
        END IF
        IF NameOrgOkay(CDCONFIRMINFO, szOrg$, "") = 0 THEN
            GOTO ISDN1L1
        END IF
        SetSymbolValue "STF_CD_ORG", szOrg$
        fOkay% = 1
    ELSEIF sz$ = "REACTIVATE" THEN
        GOTO ISDN1L1
    ELSE
        SetSymbolValue "STF_CD_TYPE", "ERROR"
    END IF
    UIPop 1
    GOTO ISDEND

ISDN2:
    sz$ = UIStartDlg(CDDLL$, CDGETNAMEORG, "FNameOrgDlgProc", 0, "")

    IF sz$ = "CONTINUE" THEN
        szName$ = RTRIM$(LTRIM$(GetSymbolValue("NameOut")))
        szOrg$  = RTRIM$(LTRIM$(GetSymbolValue("OrgOut")))
        IF szName$ = "" THEN
            BadNameOrg CDBADNAME
            GOTO ISDN2
        END IF
        IF szOrg$ = "" THEN
            szOrg$ = " "
        END IF
        IF NameOrgOkay(CDCONFIRMINFO, szName$, szOrg$) = 0 THEN
            GOTO ISDN2
        END IF
        SetSymbolValue "STF_CD_NAME", szName$
        SetSymbolValue "STF_CD_ORG", szOrg$
        fOkay% = 1
    ELSE
        SetSymbolValue "STF_CD_TYPE", "ERROR"
    END IF
    UIPop 1
    GOTO ISDEND

ISDU:
    fOkay% = NameOrgOkay(CDALREADYUSED, szName$, szOrg$)
    GOTO ISDEND

ISDA:
    SetSymbolValue "EditTextIn", ""
    SetSymbolValue "EditFocus", ""
ISDAL1:
    sz$ = UIStartDlg(CDDLL$, CDGETNAME, "FEditDlgProc", 0, "")

    IF sz$ = "CONTINUE" THEN
        szName$ = RTRIM$(LTRIM$(GetSymbolValue("EditTextOut")))
        IF szName$ = "" THEN
            BadNameOrg CDBADNAME
            GOTO ISDAL1
        END IF
        IF NameOrgOkay(CDCONFIRMINFO, szName$, "") = 0 THEN
            GOTO ISDAL1
        END IF
        SetSymbolValue "STF_CD_NAME", szName$
        fOkay% = 1
    ELSEIF sz$ = "REACTIVATE" THEN
        GOTO ISDAL1
    ELSE
        SetSymbolValue "STF_CD_TYPE", "ERROR"
    END IF
    UIPop 1
    GOTO ISDEND

ISDB:
    sz$ = UIStartDlg(CDDLL$, CDBADFILE, "FInfoDlgProc", 0, "")

    IF sz$ = "CONTINUE" THEN
        fOkay% = 1
    END IF
    UIPop 1
    GOTO ISDEND

ISDEND:
    InitSystemDlgs = fOkay%
    CDDLL$  = ""
    szName$ = ""
    szOrg$  = ""
    sz$     = ""
END FUNCTION



'**************************************************************************
SUB BadNameOrg(dlg%) STATIC
BNOL1:
    sz$ = UIStartDlg("mscuistf.dll", dlg%, "FInfoDlgProc", 0, "")
    UIPop 1
    sz$ = ""
END SUB


'**************************************************************************
FUNCTION NameOrgOkay (dlg%, szName$, szOrg$) STATIC AS INTEGER
    RemoveSymbol "ConfirmTextIn"
    AddListItem "ConfirmTextIn", szName$
    AddListItem "ConfirmTextIn", szOrg$
ILOL1:
    sz$ = UIStartDlg("mscuistf.dll", dlg%, "FConfirmDlgProc", 0, "")

    IF sz$ = "CONTINUE" THEN
        NameOrgOkay = 1
    ELSE
        NameOrgOkay = 0
    END IF
    UIPop 1
    sz$ = ""
END FUNCTION


