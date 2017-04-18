Option Explicit

'-----------------------------------------------------------------------------------------------------
' VBEXCEL
' Version 1.1 3/4/95
' Copyright 1995 Clarity Consulting, Inc.
' May not be sold or otherwise reproduced without express written consent
' of Clarity Consulting, Inc.
'
' Craig Goren
' Clarity Consulting, Inc.
' CIS:      72773,1062
' Internet: cgoren@claritycnslt.com
'
' VBEXCEL is a Visual Basic library that provides an easy method of setting
' up and retrieving a handle to an Excel 5.0 pivot table created from the
' results of an SQL statement.  It also provides includes all EXCEL VBA
' constant declarations.
'
' It requires the use of a VBODBC data source.  To use VBODBC with a
' different data source, see the inline comments on what changes need to be
' made.
'
' Comments, suggestions, and consulting opportunities welcome!
'
' Files
'       1. VBEXCEL.BAS  A VB module
'       2. VBEXCEL.XLS  An Excel template file that is used for pivot tables.
'
' APIs:
'       1. VBEXCEL_OpenAppObj() - Initializes Excel for OLE automation.
'       2. VBEXCEL_OpenPivotWorkbook() - Executes a stored procedure, places the results in an Excel pivot table, and returns an OLE handle to the pivot table in the form of a global variable, since VB can’t SET a passed object variable.  Multiple workbooks can be opened within the application.
'       3. VBEXCEL_WorkBookShow() - Should be used before an OLE automation calls to a workbook.  Makes it visible and active, which some properties and methods require.  Also performs check to make sure Excel is ready to be automated.
'       4. VBEXCEL_GetRangeStr() - Creates a valid range string (e.g. "A5:F12") from row and column integer values.  Helpful because of a bug in VB when the Excel Cells() method is used as a parameter to another Excel method.
'       5. VBEXCEL_WorkBookHide() - Should be used after OLE automation calls, to hide the workbook from the GUI so the user can’t interact with it from within Excel.
'       6. VBEXCEL_ClosePivotWorkbook() - Closes the given workbook and deleted the temporary file.  You still need to set all your workbook object variables to Nothing.
'       7. VBEXCEL_CloseAppObj() - Shuts down Excel if no workbooks are open.  You still need to se all your application object variables to nothing.
'
' Instructions:
'       1. Add VBEXCEL.BAS to your project.
'       2. Copy VBEXCEL.XLS into the project directory.
'       3. Follow the instructions later in this presentation and add the VBODBC files to your project.
'       4. Have the VB application connect to a data source.
'       5. Call VBEXCEL_OpenAppObj to initialize Excel and OLE.
'       6. Call VBEXCEL_OpenPivotWorkbook to create a new pivot table from a SQL statement.
'       7. Assign the global variables (VBEXCEL_NextPivotTable et. al.) to your own, since VB can’t pass object handles as parameters to functions.
'       8. Manipulate the workbook with VBEXCEL_WorkBookShow, VBEXCEL_GetRangeStr, VBEXCEL_WorkBookClose, and your won OLE automation calls.
'       9. Close the workbook with VBEXCEL_ ClosePivotWorkbook.  You still need to set all your own workbook object variables to Nothing.
'       10. Close the application with VBEXCEL_ CloseAppObj.  You still need to set all your own application object variables to Nothing.
'-----------------------------------------------------------------------------------------------------





'Since you can't change a passed object handle in VB (lame!),
'these global variables hold the newly created objects from
'a call to VBEXCEL_CreatePivotTableFromSql
Global VBEXCEL_NextWorkBook As Object
Global VBEXCEL_NextPivotDataSheet As Object
Global VBEXCEL_NextPivotTableSheet As Object
Global VBEXCEL_NextPivotTable As Object
'Excel's application object, the "top of the tree",
'set by VBEXCEL_OpenAppObj
Global VBEXCEL_AppObj As Object


'-------------------------------------------------
'Win APIS for VBEXCEL_OpenAppObj FUNCTION
'-------------------------------------------------
'(alias them so they don't conflict with other project declarations)
Declare Function VBEXCEL_GetModuleHandle Lib "kernel.dll" Alias "GetModuleHandle" (ByVal lpModuleName As String) As Integer
Declare Function VBEXCEL_WinExec Lib "Kernel" Alias "WinExec" (ByVal lpCmdLine As String, ByVal nCmdSHow As Integer) As Integer
Declare Function VBEXCEL_GetProfileString Lib "Kernel" Alias "GetProfileString" (ByVal lpAppName As String, ByVal lpKeyName As String, ByVal lpDefault As String, ByVal lpReturnedString As String, ByVal nSize As Integer) As Integer



'---------------------------------------------------------------------------------
' BEGIN Microsoft Excel Constants
'
'---------------------------------------------------------------------------------
Global Const xlDialogVbaMakeAddin = 478
Global Const xlDialogActiveCellFont = 476
Global Const xlDialogFindFile = 475
Global Const xlDialogSummaryInfo = 474
Global Const xlDialogScenarioMerge = 473
Global Const xlDialogStandardWidth = 472
Global Const xlDialogSeriesOrder = 466
Global Const xlDialogFormatChart = 465
Global Const xlDialogErrorbarY = 464
Global Const xlDialogErrorbarX = 463
Global Const xlDialogSeriesY = 462
Global Const xlDialogSeriesX = 461
Global Const xlDialogSeriesAxes = 460
Global Const xlDialogOptionsListsAdd = 458
Global Const xlDialogSaveCopyAs = 456
Global Const xlDialogSetControlValue = 455
Global Const xlDialogFunctionWizard = 450
Global Const xlDialogPushbuttonProperties = 445
Global Const xlDialogOpenText = 441
Global Const xlDialogEditboxProperties = 438
Global Const xlDialogListboxProperties = 437
Global Const xlDialogLabelProperties = 436
Global Const xlDialogCheckboxProperties = 435
Global Const xlDialogPivotFieldUngroup = 434
Global Const xlDialogPivotFieldGroup = 433
Global Const xlDialogFormatCharttype = 423
Global Const xlDialogTextToColumns = 422
Global Const xlDialogPivotShowPages = 421
Global Const xlDialogScrollbarProperties = 420
Global Const xlDialogWorkbookProtect = 417
Global Const xlDialogWorkbookTabSplit = 415
Global Const xlDialogSubtotalCreate = 398
Global Const xlDialogTabOrder = 394
Global Const xlDialogChartAddData = 392
Global Const xlDialogAddChartAutoformat = 390
Global Const xlDialogGalleryCustom = 388
Global Const xlDialogWorkbookName = 386
Global Const xlDialogWorkbookUnhide = 384
Global Const xlDialogMacroOptions = 382
Global Const xlDialogFontProperties = 381
Global Const xlDialogInsertTitle = 380
Global Const xlDialogDataLabel = 379
Global Const xlDialogMailNextLetter = 378
Global Const xlDialogFilterAdvanced = 370
Global Const xlDialogOptionsGeneral = 356
Global Const xlDialogOptionsTransition = 355
Global Const xlDialogWorkbookInsert = 354
Global Const xlDialogChartTrend = 350
Global Const xlDialogGalleryDoughnut = 344
Global Const xlDialogInsertPicture = 342
Global Const xlDialogMailLogon = 339
Global Const xlDialogRoutingSlip = 336
Global Const xlDialogVbaProcedureDefinition = 330
Global Const xlDialogVbaInsertFile = 328
Global Const xlDialogOptionsChart = 325
Global Const xlDialogAttachToolbars = 323
Global Const xlDialogMenuEditor = 322
Global Const xlDialogAddinManager = 321
Global Const xlDialogOptionsView = 320
Global Const xlDialogOptionsEdit = 319
Global Const xlDialogOptionsCalculation = 318
Global Const xlDialogPivotFieldProperties = 313
Global Const xlDialogPivotTableWizard = 312
Global Const xlDialogScenarioSummary = 311
Global Const xlDialogScenarioEdit = 308
Global Const xlDialogScenarioAdd = 307
Global Const xlDialogScenarioCells = 305
Global Const xlDialogWorkbookNew = 302
Global Const xlDialogFillWorkgroup = 301
Global Const xlDialogPlacement = 300
Global Const xlDialogAssignToTool = 293
Global Const xlDialogChartWizard = 288
Global Const xlDialogSaveWorkspace = 285
Global Const xlDialogWorkbookOptions = 284
Global Const xlDialogWorkbookCopy = 283
Global Const xlDialogWorkbookMove = 282
Global Const xlDialogWorkbookAdd = 281
Global Const xlDialogCustomizeToolbar = 276
Global Const xlDialogGallery3dSurface = 273
Global Const xlDialogGallery3dBar = 272
Global Const xlDialogFormatAuto = 269
Global Const xlDialogMove = 262
Global Const xlDialogSize = 261
Global Const xlDialogInsertObject = 259
Global Const xlDialogZoom = 256
Global Const xlDialogEditionOptions = 251
Global Const xlDialogGalleryRadar = 249
Global Const xlDialogDefineStyle = 229
Global Const xlDialogEditSeries = 228
Global Const xlDialogFormatOverlay = 226
Global Const xlDialogFormatMain = 225
Global Const xlDialogEditColor = 223
Global Const xlDialogPrintPreview = 222
Global Const xlDialogShowToolbar = 220
Global Const xlDialogAttributes = 219
Global Const xlDialogSubscribeTo = 218
Global Const xlDialogCreatePublisher = 217
Global Const xlDialogObjectProtection = 214
Global Const xlDialogAssignToObject = 213
Global Const xlDialogApplyStyle = 212
Global Const xlDialogSaveNewObject = 208
Global Const xlDialogObjectProperties = 207
Global Const xlDialogShowDetail = 204
Global Const xlDialogDemote = 203
Global Const xlDialogPromote = 202
Global Const xlDialogUpdateLink = 201
Global Const xlDialogFillGroup = 200
Global Const xlDialogWorkgroup = 199
Global Const xlDialogGoalSeek = 198
Global Const xlDialogView3d = 197
Global Const xlDialogGallery3dPie = 196
Global Const xlDialogGallery3dLine = 195
Global Const xlDialogGallery3dColumn = 194
Global Const xlDialogGallery3dArea = 193
Global Const xlDialogSortSpecial = 192
Global Const xlDialogConsolidate = 191
Global Const xlDialogStandardFont = 190
Global Const xlDialogSendMail = 189
Global Const xlDialogOpenMail = 188
Global Const xlDialogOverlayChartType = 186
Global Const xlDialogMainChartType = 185
Global Const xlDialogAppSize = 171
Global Const xlDialogAppMove = 170
Global Const xlDialogChangeLink = 166
Global Const xlDialogColorPalette = 161
Global Const xlDialogSetUpdateStatus = 159
Global Const xlDialogNote = 154
Global Const xlDialogFormatFont = 150
Global Const xlDialogCopyChart = 147
Global Const xlDialogSaveWorkbook = 145
Global Const xlDialogOutline = 142
Global Const xlDialogSplit = 137
Global Const xlDialogReplaceFont = 134
Global Const xlDialogApplyNames = 133
Global Const xlDialogSelectSpecial = 132
Global Const xlDialogFormulaReplace = 130
Global Const xlDialogFormatSize = 129
Global Const xlDialogFormatMove = 128
Global Const xlDialogRowHeight = 127
Global Const xlDialogNew = 119
Global Const xlDialogDeleteFormat = 111
Global Const xlDialogDeleteName = 110
Global Const xlDialogCopyPicture = 108
Global Const xlDialogActivate = 103
Global Const xlDialogWorkspace = 95
Global Const xlDialogUnhide = 94
Global Const xlDialogParse = 91
Global Const xlDialogFormatText = 89
Global Const xlDialogFormatLegend = 88
Global Const xlDialogScale = 87
Global Const xlDialogOverlay = 86
Global Const xlDialogMainChart = 85
Global Const xlDialogPatterns = 84
Global Const xlDialogAttachText = 80
Global Const xlDialogAxes = 78
Global Const xlDialogGridlines = 76
Global Const xlDialogCombination = 73
Global Const xlDialogGalleryScatter = 72
Global Const xlDialogGalleryPie = 71
Global Const xlDialogGalleryLine = 70
Global Const xlDialogGalleryColumn = 69
Global Const xlDialogGalleryBar = 68
Global Const xlDialogGalleryArea = 67
Global Const xlDialogFormulaFind = 64
Global Const xlDialogFormulaGoto = 63
Global Const xlDialogCreateNames = 62
Global Const xlDialogDefineName = 61
Global Const xlDialogInsert = 55
Global Const xlDialogEditDelete = 54
Global Const xlDialogPasteSpecial = 53
Global Const xlDialogClear = 52
Global Const xlDialogColumnWidth = 47
Global Const xlDialogCellProtection = 46
Global Const xlDialogBorder = 45
Global Const xlDialogStyle = 44
Global Const xlDialogAlignment = 43
Global Const xlDialogFormatNumber = 42
Global Const xlDialogTable = 41
Global Const xlDialogDataSeries = 40
Global Const xlDialogSort = 39
Global Const xlDialogDataDelete = 36
Global Const xlDialogExtract = 35
Global Const xlDialogCalculation = 32
Global Const xlDialogProtectDocument = 28
Global Const xlDialogDisplay = 27
Global Const xlDialogFont = 26
Global Const xlDialogSetPrintTitles = 23
Global Const xlDialogRun = 17
Global Const xlDialogWindowMove = 14
Global Const xlDialogWindowSize = 13
Global Const xlDialogArrangeAll = 12
Global Const xlDialogPrinterSetup = 9
Global Const xlDialogPrint = 8
Global Const xlDialogPageSetup = 7
Global Const xlDialogFileDelete = 6
Global Const xlDialogSaveAs = 5
Global Const xlDialogOpenLinks = 2
Global Const xlDialogOpen = 1
Global Const xlZero = 2
Global Const xlYes = 1
Global Const xlYearCode = 19
Global Const xlYear = 4
Global Const xlY = 1
Global Const xlXYScatter = -4169
Global Const xlX = -4168
Global Const xlWQ1 = 34
Global Const xlWPG = 3
Global Const xlWorksheetShort = 5
Global Const xlWorksheetCell = 3
Global Const xlWorksheet4 = 1
Global Const xlWorksheet = -4167
Global Const xlWorks2FarEast = 28
Global Const xlWorkbookTab = 6
Global Const xlWorkbook = 1
Global Const xlWMF = 2
Global Const xlWKS = 4
Global Const xlWK3FM3 = 32
Global Const xlWK3 = 15
Global Const xlWK1FMT = 30
Global Const xlWK1ALL = 31
Global Const xlWK1 = 5
Global Const xlWJ2WD1 = 14
Global Const xlWindows = 2
Global Const xlWide = 3
Global Const xlWhole = 1
Global Const xlWeekdayNameChars = 31
Global Const xlWeekday = 2
Global Const xlWatchPane = 11
Global Const xlVisible = 12
Global Const xlVeryHidden = 2
Global Const xlVertical = -4166
Global Const xlVarP = -4165
Global Const xlVar = -4164
Global Const xlValues = -4163
Global Const xlValue = 2
Global Const xlVALU = 8
Global Const xlUpward = -4171
Global Const xlUpperCaseRowLetter = 6
Global Const xlUpperCaseColumnLetter = 7
Global Const xlUpdateSubscriber = 2
Global Const xlUpdateState = 1
Global Const xlUp = -4162
Global Const xlTriangle = 3
Global Const xlTransparent = 2
Global Const xlToRight = -4161
Global Const xlTopToBottom = 1
Global Const xlTop = -4160
Global Const xlToolbarButton = 2
Global Const xlToolbar = 1
Global Const xlToLeft = -4159
Global Const xlTitleBar = 8
Global Const xlTimeSeparator = 18
Global Const xlTimeLeadingZero = 45
Global Const xlTiled = 1
Global Const xlTIF = 9
Global Const xlThousandsSeparator = 4
Global Const xlThin = 2
Global Const xlThick = 4
Global Const xlTextWindows = 20
Global Const xlTextValues = 2
Global Const xlTextPrinter = 36
Global Const xlTextMSDOS = 21
Global Const xlTextMac = 19
Global Const xlTextBox = 16
Global Const xlText = -4158
Global Const xlTemplate = 17
Global Const xlTableBody = 8
Global Const xlSyllabary = 1
Global Const xlSYLK = 2
Global Const xlSum = -4157
Global Const xlSubtract = 3
Global Const xlSubscribers = 6
Global Const xlSubscriber = 2
Global Const xlStrict = 2
Global Const xlStretch = 1
Global Const xlStError = 4
Global Const xlStDevP = -4156
Global Const xlStDev = -4155
Global Const xlStar = 5
Global Const xlStandardSummary = 1
Global Const xlStack = 2
Global Const xlSquare = 1
Global Const xlSortValues = 1
Global Const xlSortLabels = 2
Global Const xlSolid = 1
Global Const xlSingleQuote = 2
Global Const xlSingleAccounting = 4
Global Const xlSingle = 2
Global Const xlSimple = -4154
Global Const xlShowValue = 2
Global Const xlShowPercent = 3
Global Const xlShowLabelAndPercent = 5
Global Const xlShowLabel = 4
Global Const xlShort = 1
Global Const xlSeries = 3
Global Const xlSendPublisher = 2
Global Const xlSemiGray75 = 10
Global Const xlSemiautomatic = 2
Global Const xlSelect = 3
Global Const xlSecondCode = 24
Global Const xlSecondary = 2
Global Const xlScreenSize = 1
Global Const xlScreen = 1
Global Const xlScale = 3
Global Const xlRunningTotal = 5
Global Const xlRTF = 4
Global Const xlRowThenColumn = 1
Global Const xlRowSeparator = 15
Global Const xlRows = 1
Global Const xlRowItem = 4
Global Const xlRowHeader = -4153
Global Const xlRowField = 1
Global Const xlRoutingInProgress = 1
Global Const xlRoutingComplete = 2
Global Const xlRightBracket = 11
Global Const xlRightBrace = 13
Global Const xlRight = -4152
Global Const xlRelRowAbsColumn = 3
Global Const xlRelative = 4
Global Const xlReference = 4
Global Const xlReadWrite = 2
Global Const xlReadOnly = 3
Global Const xlRadar = -4151
Global Const xlR1C1 = -4150
Global Const xlPublishers = 5
Global Const xlPublisher = 1
Global Const xlProduct = -4149
Global Const xlPrinter = 2
Global Const xlPrimary = 1
Global Const xlPrevious = 2
Global Const xlPowerTalk = 2
Global Const xlPower = 4
Global Const xlPortrait = 1
Global Const xlPolynomial = 3
Global Const xlPlusValues = 2
Global Const xlPlus = 9
Global Const xlPLT = 12
Global Const xlPlotArea = 19
Global Const xlPlaceholders = 2
Global Const xlPivotTable = -4148
Global Const xlPie = 5
Global Const xlPicture = -4147
Global Const xlPICT = 1
Global Const xlPIC = 11
Global Const xlPercentOfTotal = 8
Global Const xlPercentOfRow = 6
Global Const xlPercentOfColumn = 7
Global Const xlPercentOf = 3
Global Const xlPercentDifferenceFrom = 4
Global Const xlPercent = 2
Global Const xlPCX = 10
Global Const xlPCT = 13
Global Const xlPart = 2
Global Const xlPaperUser = 256
Global Const xlPaperTabloid = 3
Global Const xlPaperStatement = 6
Global Const xlPaperQuarto = 15
Global Const xlPaperNote = 18
Global Const xlPaperLetterSmall = 2
Global Const xlPaperLetter = 1
Global Const xlPaperLegal = 5
Global Const xlPaperLedger = 4
Global Const xlPaperFolio = 14
Global Const xlPaperFanfoldUS = 39
Global Const xlPaperFanfoldStdGerman = 40
Global Const xlPaperFanfoldLegalGerman = 41
Global Const xlPaperExecutive = 7
Global Const xlPaperEsheet = 26
Global Const xlPaperEnvelopePersonal = 38
Global Const xlPaperEnvelopeMonarch = 37
Global Const xlPaperEnvelopeItaly = 36
Global Const xlPaperEnvelopeDL = 27
Global Const xlPaperEnvelopeC65 = 32
Global Const xlPaperEnvelopeC6 = 31
Global Const xlPaperEnvelopeC5 = 28
Global Const xlPaperEnvelopeC4 = 30
Global Const xlPaperEnvelopeC3 = 29
Global Const xlPaperEnvelopeB6 = 35
Global Const xlPaperEnvelopeB5 = 34
Global Const xlPaperEnvelopeB4 = 33
Global Const xlPaperEnvelope9 = 19
Global Const xlPaperEnvelope14 = 23
Global Const xlPaperEnvelope12 = 22
Global Const xlPaperEnvelope11 = 21
Global Const xlPaperEnvelope10 = 20
Global Const xlPaperDsheet = 25
Global Const xlPaperCsheet = 24
Global Const xlPaperB5 = 13
Global Const xlPaperB4 = 12
Global Const xlPaperA5 = 11
Global Const xlPaperA4Small = 10
Global Const xlPaperA4 = 9
Global Const xlPaperA3 = 8
Global Const xlPaper11x17 = 17
Global Const xlPaper10x14 = 16
Global Const xlPageItem = 6
Global Const xlPageHeader = 2
Global Const xlPageField = 3
Global Const xlOverThenDown = 2
Global Const xlOutside = 3
Global Const xlOr = 2
Global Const xlOpenSource = 3
Global Const xlOpen = 2
Global Const xlOpaque = 3
Global Const xlOneAfterAnother = 1
Global Const xlOn = 1
Global Const xlOLELinks = 2
Global Const xlOLELink = 0
Global Const xlOLEEmbed = 1
Global Const xlOff = -4146
Global Const xlNumbers = 1
Global Const xlNumber = -4145
Global Const xlNotYetRouted = 0
Global Const xlNotPlotted = 1
Global Const xlNotes = -4144
Global Const xlNormal = -4143
Global Const xlNonEnglishFunctions = 34
Global Const xlNone = -4142
Global Const xlNoncurrencyDigits = 29
Global Const xlNoMailSystem = 0
Global Const xlNoDocuments = 3
Global Const xlNoCap = 2
Global Const xlNo = 2
Global Const xlNextToAxis = 4
Global Const xlNext = 1
Global Const xlNarrow = 1
Global Const xlMultiply = 4
Global Const xlMSDOS = 3
Global Const xlMovingAvg = 6
Global Const xlMoveAndSize = 1
Global Const xlMove = 2
Global Const xlMonthNameChars = 30
Global Const xlMonthLeadingZero = 41
Global Const xlMonthCode = 20
Global Const xlMonth = 3
Global Const xlModule = -4141
Global Const xlMixed = 2
Global Const xlMinuteCode = 23
Global Const xlMinusValues = 3
Global Const xlMinimum = 2
Global Const xlMinimized = -4140
Global Const xlMin = -4139
Global Const xlMicrosoftWord = 1
Global Const xlMicrosoftSchedulePlus = 7
Global Const xlMicrosoftProject = 6
Global Const xlMicrosoftPowerPoint = 2
Global Const xlMicrosoftMail = 3
Global Const xlMicrosoftFoxPro = 5
Global Const xlMicrosoftAccess = 4
Global Const xlMetric = 35
Global Const xlMedium = -4138
Global Const xlMDY = 44
Global Const xlMaximum = 2
Global Const xlMaximized = -4137
Global Const xlMax = -4136
Global Const xlMAPI = 1
Global Const xlManualUpdate = 5
Global Const xlManual = -4135
Global Const xlMacrosheetCell = 7
Global Const xlMacintosh = 1
Global Const xlLowerCaseRowLetter = 8
Global Const xlLowerCaseColumnLetter = 9
Global Const xlLow = -4134
Global Const xlLotusHelp = 2
Global Const xlLong = 3
Global Const xlLogical = 4
Global Const xlLogarithmic = -4133
Global Const xlLocalFormat2 = 16
Global Const xlLocalFormat1 = 15
Global Const xlListSeparator = 5
Global Const xlList3 = 12
Global Const xlList2 = 11
Global Const xlList1 = 10
Global Const xlLinearTrend = 9
Global Const xlLinear = -4132
Global Const xlLine = 4
Global Const xlLightVertical = 12
Global Const xlLightUp = 14
Global Const xlLightHorizontal = 11
Global Const xlLightDown = 13
Global Const xlLegend = 24
Global Const xlLeftToRight = 2
Global Const xlLeftBracket = 10
Global Const xlLeftBrace = 12
Global Const xlLeft = -4131
Global Const xlLastCell = 11
Global Const xlLast = 1
Global Const xlLandscape = 2
Global Const xlJustify = -4130
Global Const xlIntlMacro = 25
Global Const xlIntlAddIn = 26
Global Const xlInterrupt = 1
Global Const xlInterpolated = 3
Global Const xlInteger = 2
Global Const xlInside = 2
Global Const xlInfo = -4129
Global Const xlIndex = 9
Global Const xlImmediatePane = 12
Global Const xlIcons = 1
Global Const xlHourCode = 22
Global Const xlHorizontal = -4128
Global Const xlHigh = -4127
Global Const xlHide = 3
Global Const xlHidden = 0
Global Const xlHGL = 6
Global Const xlHairline = 1
Global Const xlGuess = 0
Global Const xlGrowthTrend = 10
Global Const xlGrowth = 2
Global Const xlGridline = 22
Global Const xlGrid = 15
Global Const xlGray8 = 18
Global Const xlGray75 = -4126
Global Const xlGray50 = -4125
Global Const xlGray25 = -4124
Global Const xlGray16 = 17
Global Const xlGeneralFormatName = 26
Global Const xlGeneral = 1
Global Const xlFunction = 1
Global Const xlFullPage = 3
Global Const xlFreeFloating = 3
Global Const xlFormulas = -4123
Global Const xlFormula = 5
Global Const xlFormats = -4122
Global Const xlFloor = 23
Global Const xlFloating = 5
Global Const xlFixedWidth = 2
Global Const xlFixedValue = 1
Global Const xlFitToPage = 2
Global Const xlFirst = 0
Global Const xlFilterInPlace = 1
Global Const xlFilterCopy = 2
Global Const xlFillYears = 8
Global Const xlFillWeekdays = 6
Global Const xlFillValues = 4
Global Const xlFillSeries = 2
Global Const xlFillMonths = 7
Global Const xlFillFormats = 3
Global Const xlFillDefault = 0
Global Const xlFillDays = 5
Global Const xlFillCopy = 1
Global Const xlFill = 5
Global Const xlExternal = 2
Global Const xlExtended = 2
Global Const xlExponential = 5
Global Const xlExcelMenus = 1
Global Const xlExcelLinks = 1
Global Const xlExcel4Workbook = 35
Global Const xlExcel4MacroSheet = 3
Global Const xlExcel4IntlMacroSheet = 4
Global Const xlExcel4 = 33
Global Const xlExcel3 = 29
Global Const xlExcel2FarEast = 27
Global Const xlExcel2 = 16
Global Const xlErrValue = 2015
Global Const xlErrRef = 2023
Global Const xlErrors = 16
Global Const xlErrorHandler = 2
Global Const xlErrNum = 2036
Global Const xlErrNull = 2000
Global Const xlErrName = 2029
Global Const xlErrNA = 2042
Global Const xlErrDiv0 = 2007
Global Const xlEPS = 8
Global Const xlEntireChart = 20
Global Const xlEditionDate = 2
Global Const xlDXF = 5
Global Const xlDRW = 4
Global Const xlDrawingObject = 14
Global Const xlDownward = -4170
Global Const xlDownThenOver = 1
Global Const xlDown = -4121
Global Const xlDoughnut = -4120
Global Const xlDoubleQuote = 1
Global Const xlDoubleOpen = 4
Global Const xlDoubleClosed = 5
Global Const xlDoubleAccounting = 5
Global Const xlDouble = -4119
Global Const xlDot = -4118
Global Const xlDivide = 5
Global Const xlDistributed = -4117
Global Const xlDisabled = 0
Global Const xlDirect = 1
Global Const xlDifferenceFrom = 2
Global Const xlDIF = 9
Global Const xlDiamond = 2
Global Const xlDialogSheet = -4116
Global Const xlDesktop = 9
Global Const xlDescending = 2
Global Const xlDelimited = 1
Global Const xlDefaultAutoFormat = -1
Global Const xlDecimalSeparator = 3
Global Const xlDebugCodePane = 13
Global Const xlDBF4 = 11
Global Const xlDBF3 = 8
Global Const xlDBF2 = 7
Global Const xlDayLeadingZero = 42
Global Const xlDayCode = 21
Global Const xlDay = 1
Global Const xlDateSeparator = 17
Global Const xlDateOrder = 32
Global Const xlDate = 2
Global Const xlDataItem = 7
Global Const xlDataHeader = 3
Global Const xlDataField = 4
Global Const xlDatabase = 1
Global Const xlDashDotDot = 5
Global Const xlDashDot = 4
Global Const xlDash = -4115
Global Const xlCut = 2
Global Const xlCustom = -4114
Global Const xlCurrencyTrailingZeros = 39
Global Const xlCurrencySpaceBefore = 36
Global Const xlCurrencyNegative = 28
Global Const xlCurrencyMinusSign = 38
Global Const xlCurrencyLeadingZeros = 40
Global Const xlCurrencyDigits = 27
Global Const xlCurrencyCode = 25
Global Const xlCurrencyBefore = 37
Global Const xlCSVWindows = 23
Global Const xlCSVMSDOS = 24
Global Const xlCSVMac = 22
Global Const xlCSV = 6
Global Const xlCross = 4
Global Const xlCrissCross = 16
Global Const xlCountrySetting = 2
Global Const xlCountryCode = 1
Global Const xlCountNums = -4113
Global Const xlCount = -4112
Global Const xlCorner = 2
Global Const xlCopy = 1
Global Const xlContinuous = 1
Global Const xlContents = 2
Global Const xlConstants = 2
Global Const xlConsolidation = 3
Global Const xlCommand = 2
Global Const xlCombination = -4111
Global Const xlColumnThenRow = 2
Global Const xlColumnSeparator = 14
Global Const xlColumns = 2
Global Const xlColumnItem = 5
Global Const xlColumnHeader = -4110
Global Const xlColumnField = 2
Global Const xlColumn = 3
Global Const xlColor3 = 9
Global Const xlColor2 = 8
Global Const xlColor1 = 7
Global Const xlCodePage = 2
Global Const xlClosed = 3
Global Const xlClipboardFormatWK1 = 10
Global Const xlClipboardFormatVALU = 1
Global Const xlClipboardFormatToolFacePICT = 26
Global Const xlClipboardFormatToolFace = 25
Global Const xlClipboardFormatText = 0
Global Const xlClipboardFormatTable = 16
Global Const xlClipboardFormatSYLK = 6
Global Const xlClipboardFormatStandardScale = 27
Global Const xlClipboardFormatStandardFont = 28
Global Const xlClipboardFormatScreenPICT = 29
Global Const xlClipboardFormatRTF = 7
Global Const xlClipboardFormatPrintPICT = 3
Global Const xlClipboardFormatPICT = 2
Global Const xlClipboardFormatOwnerLink = 17
Global Const xlClipboardFormatObjectLink = 19
Global Const xlClipboardFormatObjectDesc = 31
Global Const xlClipboardFormatNative = 14
Global Const xlClipboardFormatMovie = 24
Global Const xlClipboardFormatLinkSourceDesc = 32
Global Const xlClipboardFormatLinkSource = 23
Global Const xlClipboardFormatLink = 11
Global Const xlClipboardFormatEmbedSource = 22
Global Const xlClipboardFormatEmbeddedObject = 21
Global Const xlClipboardFormatDspText = 12
Global Const xlClipboardFormatDIF = 4
Global Const xlClipboardFormatCSV = 5
Global Const xlClipboardFormatCGM = 13
Global Const xlClipboardFormatBitmap = 9
Global Const xlClipboardFormatBinary = 15
Global Const xlClipboardFormatBIFF4 = 30
Global Const xlClipboardFormatBIFF3 = 20
Global Const xlClipboardFormatBIFF2 = 18
Global Const xlClipboardFormatBIFF = 8
Global Const xlClipboard = 3
Global Const xlClassic3 = 3
Global Const xlClassic2 = 2
Global Const xlClassic1 = 1
Global Const xlCircle = 8
Global Const xlChronological = 3
Global Const xlChecker = 9
Global Const xlChartTitles = 18
Global Const xlChartShort = 6
Global Const xlChartSeries = 17
Global Const xlChartInPlace = 4
Global Const xlChartAsWindow = 5
Global Const xlChart4 = 2
Global Const xlChart = -4109
Global Const xlChangeAttributes = 6
Global Const xlCGM = 7
Global Const xlCenterAcrossSelection = 7
Global Const xlCenter = -4108
Global Const xlCategory = 1
Global Const xlCascade = 7
Global Const xlCap = 1
Global Const xlCancel = 1
Global Const xlByRows = 1
Global Const xlByColumns = 2
Global Const xlButton = 15
Global Const xlBuiltIn = 0
Global Const xlBottom = -4107
Global Const xlBoth = 1
Global Const xlBMP = 1
Global Const xlBlanks = 4
Global Const xlBitmap = 2
Global Const xlBIFF = 2
Global Const xlBelow = 1
Global Const xlBar = 2
Global Const xlAxis = 21
Global Const xlAverage = -4106
Global Const xlAutoOpen = 1
Global Const xlAutomaticUpdate = 4
Global Const xlAutomatic = -4105
Global Const xlAutoFill = 4
Global Const xlAutoDeactivate = 4
Global Const xlAutoClose = 2
Global Const xlAutoActivate = 3
Global Const xlAscending = 1
Global Const xlArea = 1
Global Const xlAnd = 1
Global Const xlAlternateArraySeparator = 16
Global Const xlAllAtOnce = 2
Global Const xlAll = -4104
Global Const xlAddIn = 18
Global Const xlAdd = 2
Global Const xlAccounting4 = 17
Global Const xlAccounting3 = 6
Global Const xlAccounting2 = 5
Global Const xlAccounting1 = 4
Global Const xlAbsRowRelColumn = 2
Global Const xlAbsolute = 1
Global Const xlAbove = 0
Global Const xlA1 = 1
Global Const xl4DigitYears = 43
Global Const xl3DSurface = -4103
Global Const xl3DPie = -4102
Global Const xl3DLine = -4101
Global Const xl3DEffects2 = 14
Global Const xl3DEffects1 = 13
Global Const xl3DColumn = -4100
Global Const xl3DBar = -4099
Global Const xl3DArea = -4098
Global Const xl24HourClock = 33

Sub VBEXCEL_CloseAppObj ()

'Closes the application object created by VBEXCEL_OpenAppObj.
'Shuts down the instance of Excel if there are no other workbooks open.

On Error Resume Next

'clear clipboard to avoid Excel "save large clipboard" msg
clipboard.Clear

'Close excel if no workbooks are present
If VBEXCEL_AppObj.workbooks.Count < 1 Then
    VBEXCEL_AppObj.Quit
End If
 
Set VBEXCEL_AppObj = Nothing

End Sub

Sub VBEXCEL_ClosePivotWorkbook (workbook As Object)

'Closes the workbook pointed to by Workbook.
'Deletes the temporary file as well.

'The caller is still reqponsible for setting Workbook and other
'object variables to Nothing, since this can't be done as a passed
'parameter.

On Error Resume Next

Dim Filename As String

'rememebr filename, so we can delete it when we're done
Filename = workbook.Path & "\" & workbook.name

'clear the clipboard, since we use it a lot to talk with excel
clipboard.Clear

'close workbook
workbook.[Close] False


'erase temp file
Kill Filename
 

End Sub

Sub VBEXCEL_DelayWait (Secs As Long)

'Pauses VB execution for given number of secs

Dim StartTime As Variant
Dim StopTime As Variant

StartTime = Now
StopTime = DateAdd("s", Secs, StartTime)

While DateDiff("s", Now, StopTime) > 0
    DoEvents
Wend


End Sub

Function VBEXCEL_GetRangeStr (Row1 As Integer, Col1 As Integer, Row2 As Integer, Col2 As Integer) As String

'Creates a valid range string from excel range elements.
'A parameter value of 0 indicated entire row/col.

'Example:
'   VBEXCEL_GetRangeStr(1,2,3,4) = B1:D3
'   VBEXCEL_GetRangeStr(3,0,5,0) = 3:5
'   VBEXCEL_GetRangeStr(0,4,0,6) = D:F

Dim s As String

s = ""

If Col1 > 0 Then s = s & Chr$(Col1 + 64)
If Row1 > 0 Then s = s & CStr(Row1)

s = s & ":"

If Col2 > 0 Then s = s & Chr$(Col2 + 64)
If Row2 > 0 Then s = s & CStr(Row2)

VBEXCEL_GetRangeStr = s


End Function

Function VBEXCEL_OpenAppObj () As Integer

'Retrieves a handle to the application object of the Excel instance,
'and assigns it to global VBEXCEL_AppObj.

'Starts an instance of Excel if not already started.

'Returns 0 for success.


Dim RetryNum As Integer  'counter

'the temporary sheet that is loaded when excel is started
Dim LoadSheet As Object
Dim workbook As Object

'the exename (e.g. excel.exe)
Dim XlsExeName As String
'the exepath (e.g. c:\excel)
Dim XlsExePath As String

Dim ResCode As Integer
Dim ReturnedString As String * 255
Dim ExeStartPos As Integer

Const XLS_CMD_LINE = "/e"           'tells excel not to load a blank "Book1" workbook

'since Excel loads asynchronously, the GetObject call sometimes
'finished BEFORE Excel is ready for OLE automation.  This are tweaking
'parms.
Const XLS_RETRIES = 5  'number of times to retry
Const XLS_DELAY = 3    'delay between retries


'----------------------------------------------------------
'Get EXE name and path based on .XLS association in WIN.INI
'----------------------------------------------------------

'get the WIN.INI extry
ResCode = VBEXCEL_GetProfileString("Extensions", "Xls", "", ByVal ReturnedString, Len(ReturnedString))
If ResCode = 0 Then
    VBEXCEL_OpenAppObj = True
    Exit Function
End If

'parse the entry for the EXE name
ExeStartPos = 0
Do 'find last "\"
    ResCode = InStr(ExeStartPos + 1, ReturnedString, "\")
    If ResCode Then
	ExeStartPos = ResCode
    End If
Loop Until ResCode = 0
'assign exe name to charaters from ExeStartPos to a space
XlsExeName = Mid$(ReturnedString, ExeStartPos + 1, InStr(1, ReturnedString, " ") - ExeStartPos - 1)
'assign exe path to charaters to ExeStartPos-1
XlsExePath = Mid$(ReturnedString, 1, ExeStartPos - 1)



'----------------------------------
'Load EXE
'----------------------------------

'check handle for exe; see if its already running
ResCode = VBEXCEL_GetModuleHandle(XlsExeName)
'if we don't have a module handle, then the app isn't loaded
If ResCode = 0 Then
    'load/execute app minimized with command line options                         'SW_MINNOACTIVE
    ResCode = VBEXCEL_WinExec(XlsExePath & "\" & XlsExeName & " " & XLS_CMD_LINE, 7)
    'check for error, if error return code
    If ResCode <= 32 And ResCode >= 0 Then
	VBEXCEL_OpenAppObj = True
	Exit Function
    End If
End If


'----------------------------------
'Retrieve handle.
'----------------------------------

'loop through retries
For RetryNum = 1 To XLS_RETRIES
    On Error GoTo VBEXCEL_ExcelError:
    'create dummy workbook
    Set LoadSheet = CreateObject("Excel.Sheet.5")
    'got it! exit loop
    Exit For

VBEXCEL_ExcelError:
    'wait specified time before retrying
    VBEXCEL_DelayWait (XLS_DELAY)
    'if trying more than 2 times, inform user that they may need to help out
    If RetryNum > 2 Then
	ResCode = MsgBox("Cannot access Microsoft Excel.  Please make sure Excel isn't displaying any dialog boxes or editing any cells. (Err=" & CStr(Err) & ")", 5 + 48, "OLE Automation Problem")
	If ResCode = 2 Then
	    VBEXCEL_OpenAppObj = True
	    Exit Function
	End If
    End If
    Resume VBEXCEL_ExcelRetry

VBEXCEL_ExcelRetry:

Next RetryNum

'reset error handler
On Error GoTo 0


'assign handle of parent application
Set VBEXCEL_AppObj = LoadSheet.application

'get rid of dummy sheet (this closes it down)
Set LoadSheet = Nothing


End Function

Function VBEXCEL_OpenPivotWorkbook (SP As String, Parms() As String, NumPageFields) As Integer

'Returns 0 for success.

'Given executes the SQL statements, creates a temoporary Excel workbook,
'loads the SQL statement result set into the workbook, and sets up a pivot
'table in the workbook.  The first NumPageFields are set as page fields
'in the pivot table, the rest of the column data are set as data fields
'in the pivot table.

'Uses VBEXCEL.XLS as a template.  Requires that it appear in the VB EXE
'directory.

'Uses VBODBC as data access method for SQL statement.
'If you are using a data access method other than the VBODBC library,
'you need to change one section of this procedure to call your own
'data access API with the Sql parm.

Const TEMPLATE_FILE = "VBEXCEL.XLS"  'The template file
'since Excel loads asynchronously, the GetObject call sometimes
'finished BEFORE Excel is ready for OLE automation.  This are tweaking
'parms.
Const XLS_RETRIES = 5  'number of times to retry
Const XLS_DELAY = 3    'delay between retries

'temporary name and path that the TEMPLATE_FILE will be copied to
Dim TempPath As String
Dim Filename As String

'our temporary file will be GetObject-ed into this
Dim LoadSheet As Object

'The suffix of the copy of the temporary file will be a number.
'Count will record the last suffix used successfully.
Static Count As Integer

Dim RetryNum As Integer
Dim row As Integer
Dim ResCode As Integer
Dim RowBuf() As Variant

Dim RangeStr As String
Dim FieldNum As Integer


'-----------------------------------------------------------
'Get a valid file name
'-----------------------------------------------------------
'Example: C:\TEMP\~VBXLS3.XLS

'the prefix of the temp file used by this application
'that TEMPLATE_FILE is copied to
Const PREFIX = "~VBXLS"
'the suffix of thie temp file used by this application
Const SUFFIX = ".XLS"

'the suffix of the prefix to the temp file numer
Count = Count + 1

'find the path to the temp directory, choosing Temp, Tmp, and then finally
'the current dir.
TempPath = Environ$("Temp")
If TempPath = "" Then
    TempPath = Environ$("Tmp")
End If

'find a free filename
Filename = TempPath & "\" & PREFIX & CStr(Count) & ".XLS"
While Dir$(Filename) <> ""
    Count = Count + 1
    Filename = TempPath & "\" & PREFIX & CStr(Count) & ".XLS"
Wend


'-----------------------------------------------------------
'copy template file
'-----------------------------------------------------------
FileCopy app.Path & "\" & TEMPLATE_FILE, Filename

'-----------------------------------------------------------
'load new copy into excel
'-----------------------------------------------------------
For RetryNum = 1 To XLS_RETRIES
    On Error GoTo VBEXCEL_ExcelError2:
    Set LoadSheet = GetObject(Filename, "Excel.Sheet.5")
    'got it! exit loop
    Exit For

VBEXCEL_ExcelError2:
    'wait specified time before retrying
    VBEXCEL_DelayWait (XLS_DELAY)
    If RetryNum > 2 Then
	'let use see if he/she can help us out
	ResCode = MsgBox("Cannot access Microsoft Excel.  Please make sure Excel isn't displaying any dialog boxes or editing any cells. (Err=" & CStr(Err) & ")", 5 + 48, "OLE Automation Problem")
	If ResCode = 2 Then
	    VBEXCEL_OpenPivotWorkbook = True
	    Exit Function
	End If
    End If
    Resume VBEXCEL_ExcelRetry2
VBEXCEL_ExcelRetry2:
Next RetryNum

On Error GoTo 0
  

'-----------------------------------------------------------
'adjust new object
'-----------------------------------------------------------

'make application visible and minimized, in case its not
VBEXCEL_AppObj.WindowState = xlMinimized
VBEXCEL_AppObj.visible = True
'set global object vars so caller can use
Set VBEXCEL_NextWorkBook = LoadSheet.parent
Set VBEXCEL_NextPivotDataSheet = VBEXCEL_NextWorkBook.worksheets("PivotDataSheet")
Set VBEXCEL_NextPivotTableSheet = VBEXCEL_NextWorkBook.worksheets("PivotTableSheet")

'-----------------------------------------------------------
'Run SQL and place results in PivotDataSheet
'-----------------------------------------------------------

'Note that if you are not using the VBODBC library for data access,
'you need only change the following code to dump the results of Sql
'from your own data source here.

'We use the clipboard to transfer data a tab-delimited line at a time, since
'this is a lot faster then setting individual cells (Ole "dot" operations are
'expensive compared to normal VB operations; they should be minimized).

'open sql statement
'ResCode = VBODBC_OpenSqlStmtDialog(SQL, 0, "Taking Snapshot...")

'open stored proecudure
ResCode = VBODBC_OpenSqlProcDialog(SP, Parms(), 0, "Taking Snapshot...")
If ResCode <> SQL_SUCCESS Then
    ResCode = MsgBox(VBODBC_LastErr.AllErrorInfo, 16, "ODBC Error")
End If

'prep workbook for automation
Call VBEXCEL_WorkBookShow(VBEXCEL_NextWorkBook)

'Populate column header info
row = 1  'init counter

'put tab delimited row into clipboard
clipboard.Clear  'clear first, in case it contains an excel object!
clipboard.SetText VBODBC_ColDesc(0).ColName 'place our dataon cb
VBEXCEL_NextPivotDataSheet.range("A" & CStr(row)).select  'select the target row
VBEXCEL_NextPivotDataSheet.Paste 'paste it in
clipboard.Clear  'clear the clipboard so use doesn't accidently paste our data later

'populate pivot data sheet
ResCode = VBODBC_GetNextRow(RowBuf()) 'get 1st row from SQL statement
clipboard.Clear   'clear first, in case it contains an excel object!
Do Until ResCode <> SQL_SUCCESS
    row = row + 1
    'put tab delimited row into clipboard
    clipboard.SetText RowBuf(0) 'place our data on cb (note 1st elemeber of RowBuf is already tab demlimited!)
    VBEXCEL_NextPivotDataSheet.range("A" & CStr(row)).select  'select the target row
    VBEXCEL_NextPivotDataSheet.Paste   'paste it in
    'get next row, if any
    ResCode = VBODBC_GetNextRow(RowBuf())
Loop
clipboard.Clear  'clear the clipboard so use doesn't accidently paste our data later

'close sql statement
ResCode = VBODBC_CloseSqlStmt()
If ResCode <> SQL_SUCCESS Then
    ResCode = MsgBox(VBODBC_LastErr.AllErrorInfo, 16, "ODBC Error")
End If

'-----------------------------------------------------------
'Create pivot table
'-----------------------------------------------------------

'select the sheet, since excel requires this for the wizard
VBEXCEL_NextPivotTableSheet.select
'build range string that defines entire result set
RangeStr = VBEXCEL_GetRangeStr(1, 1, row, VBODBC_NumCols)
'create with pivot table wizard
'comments:                                   excel db    source of data                              'destination                             name
VBEXCEL_NextPivotTableSheet.PivotTableWizard xlDatabase, VBEXCEL_NextPivotDataSheet.range(RangeStr), VBEXCEL_NextPivotTableSheet.range("A1"), "PivotTable"
'reassign object variable
Set VBEXCEL_NextPivotTable = VBEXCEL_NextPivotTableSheet.PivotTables(1)

'set page fields to first NumPageFields columns
For FieldNum = 1 To NumPageFields
    VBEXCEL_NextPivotTable.PivotFields(FieldNum).Orientation = xlPageField
Next
'set data fields to everything after NumPageFields columns
For FieldNum = NumPageFields + 1 To VBODBC_NumCols
    VBEXCEL_NextPivotTable.PivotFields(FieldNum).Orientation = xlDataField
Next
'put data fileds on top as columns
VBEXCEL_NextPivotTable.PivotFields("Data").Orientation = xlColumnField

'----------------------------------------------------
'Clean up
'----------------------------------------------------
'done with automation!
ResCode = VBEXCEL_WorkBookHide(VBEXCEL_NextWorkBook)



End Function

Function VBEXCEL_WorkBookHide (workbook As Object) As Integer

'Hides a workbook when VB OLE in done, so interactive
'excel user doesn't see it. This should be executed everytime
'your app is done with automation for a while.

'this works!  Changing the order may not work
workbook.Windows(1).activate
workbook.Windows(1).visible = False

'allow user interaction
workbook.application.interactive = True

End Function

Sub VBEXCEL_WorkBookShow (workbook As Object)

'Prepares a workbook for VB OLE manipulation.  This
'should be executed everytime your app is about to use OLE
'on the Workbook, since some properties and methods require
'the object to be visble and active.

'It also insures that OLE automation will work, since it will fail
'if the user has a dialog box or is editing a cell in the Excel
'instance.

Dim ResCode As Integer

On Error GoTo VBEXCEL_WorkBookShow_Error

'this works!  Changing the order may not work
VBEXCEL_WorkBookShow_Try:

'disallow user interaction
workbook.application.interactive = False

workbook.Windows(1).activate
workbook.Windows(1).visible = True

Exit Sub


'uh oh! ole automation error.  Give the user a chance to
'help us out.
VBEXCEL_WorkBookShow_Error:

ResCode = MsgBox("Cannot access Microsoft Excel.  Please make sure Excel isn't displaying any dialog boxes or editing any cells. (" & CStr(Err) & ")", 5 + 48, "OLE Automation Problem")
If ResCode = 2 Then
    Exit Sub
Else
    Resume VBEXCEL_WorkBookShow_Try
End If

End Sub

