// Machine generated IDispatch wrapper class(es) created with ClassWizard
/////////////////////////////////////////////////////////////////////////////
// Worksheet wrapper class

class Worksheet : public COleDispatchDriver
{
public:
	Worksheet() {}		// Calls COleDispatchDriver default constructor
	Worksheet(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
	Worksheet(const Worksheet& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

// Attributes
public:
	VARIANT GetAutoFilterMode();
	void SetAutoFilterMode(const VARIANT&);
	VARIANT GetCircularReference();
	void SetCircularReference(const VARIANT&);
	VARIANT GetConsolidationFunction();
	void SetConsolidationFunction(const VARIANT&);
	VARIANT GetConsolidationOptions();
	void SetConsolidationOptions(const VARIANT&);
	VARIANT GetConsolidationSources();
	void SetConsolidationSources(const VARIANT&);
	VARIANT GetCreator();
	void SetCreator(const VARIANT&);
	VARIANT GetDisplayAutomaticPageBreaks();
	void SetDisplayAutomaticPageBreaks(const VARIANT&);
	VARIANT GetFilterMode();
	void SetFilterMode(const VARIANT&);
	VARIANT GetIndex();
	void SetIndex(const VARIANT&);
	VARIANT GetName();
	void SetName(const VARIANT&);
	VARIANT GetNext();
	void SetNext(const VARIANT&);
	VARIANT GetOnCalculate();
	void SetOnCalculate(const VARIANT&);
	VARIANT GetOnData();
	void SetOnData(const VARIANT&);
	VARIANT GetOnDoubleClick();
	void SetOnDoubleClick(const VARIANT&);
	VARIANT GetOnEntry();
	void SetOnEntry(const VARIANT&);
	VARIANT GetOnSheetActivate();
	void SetOnSheetActivate(const VARIANT&);
	VARIANT GetOnSheetDeactivate();
	void SetOnSheetDeactivate(const VARIANT&);
	VARIANT GetOutline();
	void SetOutline(const VARIANT&);
	VARIANT GetPageSetup();
	void SetPageSetup(const VARIANT&);
	VARIANT GetParent();
	void SetParent(const VARIANT&);
	VARIANT GetPrevious();
	void SetPrevious(const VARIANT&);
	VARIANT GetProtectContents();
	void SetProtectContents(const VARIANT&);
	VARIANT GetProtectDrawingObjects();
	void SetProtectDrawingObjects(const VARIANT&);
	VARIANT GetProtectScenarios();
	void SetProtectScenarios(const VARIANT&);
	VARIANT GetStandardHeight();
	void SetStandardHeight(const VARIANT&);
	VARIANT GetStandardWidth();
	void SetStandardWidth(const VARIANT&);
	VARIANT GetTransitionExpEval();
	void SetTransitionExpEval(const VARIANT&);
	VARIANT GetTransitionFormEntry();
	void SetTransitionFormEntry(const VARIANT&);
	VARIANT GetType();
	void SetType(const VARIANT&);
	VARIANT GetUsedRange();
	void SetUsedRange(const VARIANT&);
	VARIANT GetVisible();
	void SetVisible(const VARIANT&);

// Operations
public:
	VARIANT Activate();
	VARIANT Application();
	VARIANT Arcs(const VARIANT& Index);
	VARIANT Buttons(const VARIANT& Index);
	VARIANT Calculate();
	VARIANT Cells(const VARIANT& RowIndex, const VARIANT& ColumnIndex);
	VARIANT ChartObjects(const VARIANT& Index);
	VARIANT CheckBoxes(const VARIANT& Index);
	VARIANT CheckSpelling(const VARIANT& CustomDictionary, const VARIANT& IgnoreUppercase, const VARIANT& AlwaysSuggest);
	VARIANT ClearArrows();
	VARIANT Columns(const VARIANT& Index);
	VARIANT Copy(const VARIANT& Before, const VARIANT& After);
	VARIANT Delete();
	VARIANT DrawingObjects(const VARIANT& Index);
	VARIANT Drawings(const VARIANT& Index);
	VARIANT DropDowns(const VARIANT& Index);
	VARIANT _Evaluate(const VARIANT& Name);
	VARIANT Evaluate(const VARIANT& Name);
	VARIANT GroupBoxes(const VARIANT& Index);
	VARIANT GroupObjects(const VARIANT& Index);
	VARIANT Labels(const VARIANT& Index);
	VARIANT Lines(const VARIANT& Index);
	VARIANT ListBoxes(const VARIANT& Index);
	VARIANT Move(const VARIANT& Before, const VARIANT& After);
	VARIANT OLEObjects(const VARIANT& Index);
	VARIANT OptionButtons(const VARIANT& Index);
	VARIANT Ovals(const VARIANT& Index);
	VARIANT Paste(const VARIANT& Destination, const VARIANT& Link);
	VARIANT PasteSpecial(const VARIANT& Format, const VARIANT& Link, const VARIANT& DisplayAsIcon, const VARIANT& IconFileName, const VARIANT& IconIndex, const VARIANT& IconLabel);
	VARIANT Pictures(const VARIANT& Index);
	VARIANT PivotTables(const VARIANT& Index);
	VARIANT PivotTableWizard(const VARIANT& SourceType, const VARIANT& SourceData, const VARIANT& TableDestination, const VARIANT& TableName, const VARIANT& RowGrand, const VARIANT& ColumnGrand, const VARIANT& SaveData, 
		const VARIANT& HasAutoFormat, const VARIANT& AutoPage);
	VARIANT PrintOut(const VARIANT& From, const VARIANT& To, const VARIANT& Copies, const VARIANT& Preview);
	VARIANT PrintPreview();
	VARIANT Protect(const VARIANT& Password, const VARIANT& DrawingObjects, const VARIANT& Contents, const VARIANT& Scenarios);
	VARIANT Range(const VARIANT& Cell1, const VARIANT& Cell2);
	VARIANT Rectangles(const VARIANT& Index);
	VARIANT Rows(const VARIANT& Index);
	VARIANT SaveAs(const VARIANT& Filename, const VARIANT& FileFormat, const VARIANT& Password, const VARIANT& WriteResPassword, const VARIANT& ReadOnlyRecommended, const VARIANT& CreateBackup);
	VARIANT Scenarios(const VARIANT& Index);
	VARIANT ScrollBars(const VARIANT& Index);
	VARIANT Select(const VARIANT& Replace);
	VARIANT ShowAllData();
	VARIANT ShowDataForm();
	VARIANT Spinners(const VARIANT& Index);
	VARIANT TextBoxes(const VARIANT& Index);
	VARIANT Unprotect(const VARIANT& Password);
};
/////////////////////////////////////////////////////////////////////////////
// Range wrapper class

class Range : public COleDispatchDriver
{
public:
	Range() {}		// Calls COleDispatchDriver default constructor
	Range(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
	Range(const Range& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

// Attributes
public:
	VARIANT GetAddIndent();
	void SetAddIndent(const VARIANT&);
	VARIANT GetColumn();
	void SetColumn(const VARIANT&);
	VARIANT GetColumnWidth();
	void SetColumnWidth(const VARIANT&);
	VARIANT GetCount();
	void SetCount(const VARIANT&);
	VARIANT GetCreator();
	void SetCreator(const VARIANT&);
	VARIANT GetCurrentArray();
	void SetCurrentArray(const VARIANT&);
	VARIANT GetCurrentRegion();
	void SetCurrentRegion(const VARIANT&);
	VARIANT GetDependents();
	void SetDependents(const VARIANT&);
	VARIANT GetDirectDependents();
	void SetDirectDependents(const VARIANT&);
	VARIANT GetDirectPrecedents();
	void SetDirectPrecedents(const VARIANT&);
	VARIANT GetEntireColumn();
	void SetEntireColumn(const VARIANT&);
	VARIANT GetEntireRow();
	void SetEntireRow(const VARIANT&);
	VARIANT GetFont();
	void SetFont(const VARIANT&);
	VARIANT GetFormula();
	void SetFormula(const VARIANT&);
	VARIANT GetFormulaArray();
	void SetFormulaArray(const VARIANT&);
	VARIANT GetFormulaHidden();
	void SetFormulaHidden(const VARIANT&);
	VARIANT GetFormulaLocal();
	void SetFormulaLocal(const VARIANT&);
	VARIANT GetFormulaR1C1();
	void SetFormulaR1C1(const VARIANT&);
	VARIANT GetFormulaR1C1Local();
	void SetFormulaR1C1Local(const VARIANT&);
	VARIANT GetHasArray();
	void SetHasArray(const VARIANT&);
	VARIANT GetHasFormula();
	void SetHasFormula(const VARIANT&);
	VARIANT GetHeight();
	void SetHeight(const VARIANT&);
	VARIANT GetHidden();
	void SetHidden(const VARIANT&);
	VARIANT GetHorizontalAlignment();
	void SetHorizontalAlignment(const VARIANT&);
	VARIANT GetInterior();
	void SetInterior(const VARIANT&);
	VARIANT GetLeft();
	void SetLeft(const VARIANT&);
	VARIANT GetListHeaderRows();
	void SetListHeaderRows(const VARIANT&);
	VARIANT GetLocationInTable();
	void SetLocationInTable(const VARIANT&);
	VARIANT GetLocked();
	void SetLocked(const VARIANT&);
	VARIANT GetName();
	void SetName(const VARIANT&);
	VARIANT GetNext();
	void SetNext(const VARIANT&);
	VARIANT GetNumberFormat();
	void SetNumberFormat(const VARIANT&);
	VARIANT GetNumberFormatLocal();
	void SetNumberFormatLocal(const VARIANT&);
	VARIANT GetOrientation();
	void SetOrientation(const VARIANT&);
	VARIANT GetOutlineLevel();
	void SetOutlineLevel(const VARIANT&);
	VARIANT GetPageBreak();
	void SetPageBreak(const VARIANT&);
	VARIANT GetParent();
	void SetParent(const VARIANT&);
	VARIANT GetPivotField();
	void SetPivotField(const VARIANT&);
	VARIANT GetPivotItem();
	void SetPivotItem(const VARIANT&);
	VARIANT GetPivotTable();
	void SetPivotTable(const VARIANT&);
	VARIANT GetPrecedents();
	void SetPrecedents(const VARIANT&);
	VARIANT GetPrefixCharacter();
	void SetPrefixCharacter(const VARIANT&);
	VARIANT GetPrevious();
	void SetPrevious(const VARIANT&);
	VARIANT GetRow();
	void SetRow(const VARIANT&);
	VARIANT GetRowHeight();
	void SetRowHeight(const VARIANT&);
	VARIANT GetShowDetail();
	void SetShowDetail(const VARIANT&);
	VARIANT GetSoundNote();
	void SetSoundNote(const VARIANT&);
	VARIANT GetStyle();
	void SetStyle(const VARIANT&);
	VARIANT GetSummary();
	void SetSummary(const VARIANT&);
	VARIANT GetText();
	void SetText(const VARIANT&);
	VARIANT GetTop();
	void SetTop(const VARIANT&);
	VARIANT GetUseStandardHeight();
	void SetUseStandardHeight(const VARIANT&);
	VARIANT GetUseStandardWidth();
	void SetUseStandardWidth(const VARIANT&);
	VARIANT GetValue();
	void SetValue(const VARIANT&);
	VARIANT GetVerticalAlignment();
	void SetVerticalAlignment(const VARIANT&);
	VARIANT GetWidth();
	void SetWidth(const VARIANT&);
	VARIANT GetWrapText();
	void SetWrapText(const VARIANT&);

// Operations
public:
	VARIANT _Dummy(const VARIANT& Activate, const VARIANT& DirectObject);
	VARIANT _NewEnum();
	VARIANT Activate();
	VARIANT Address(const VARIANT& RowAbsolute, const VARIANT& ColumnAbsolute, const VARIANT& ReferenceStyle, const VARIANT& External, const VARIANT& RelativeTo);
	VARIANT AddressLocal(const VARIANT& RowAbsolute, const VARIANT& ColumnAbsolute, const VARIANT& ReferenceStyle, const VARIANT& External, const VARIANT& RelativeTo);
	VARIANT AdvancedFilter(const VARIANT& Action, const VARIANT& CriteriaRange, const VARIANT& CopyToRange, const VARIANT& Unique);
	VARIANT Application();
	VARIANT ApplyNames(const VARIANT& Names, const VARIANT& IgnoreRelativeAbsolute, const VARIANT& UseRowColumnNames, const VARIANT& OmitColumn, const VARIANT& OmitRow, const VARIANT& Order, const VARIANT& AppendLast);
	VARIANT ApplyOutlineStyles();
	VARIANT Areas(const VARIANT& Index);
	VARIANT AutoComplete(const VARIANT& String);
	VARIANT AutoFill(const VARIANT& Destination, const VARIANT& Type);
	VARIANT AutoFilter(const VARIANT& Field, const VARIANT& Criteria1, const VARIANT& Operator, const VARIANT& Criteria2);
	VARIANT AutoFit();
	VARIANT AutoFormat(const VARIANT& Format, const VARIANT& Number, const VARIANT& Font, const VARIANT& Alignment, const VARIANT& Border, const VARIANT& Pattern, const VARIANT& Width);
	VARIANT AutoOutline();
	VARIANT BorderAround(const VARIANT& LineStyle, const VARIANT& Weight, const VARIANT& ColorIndex, const VARIANT& Color);
	VARIANT Borders(const VARIANT& Index);
	VARIANT Calculate();
	VARIANT Cells(const VARIANT& RowIndex, const VARIANT& ColumnIndex);
	VARIANT Characters(const VARIANT& Start, const VARIANT& Length);
	VARIANT CheckSpelling(const VARIANT& CustomDictionary, const VARIANT& IgnoreUppercase, const VARIANT& AlwaysSuggest);
	VARIANT Clear();
	VARIANT ClearContents();
	VARIANT ClearFormats();
	VARIANT ClearNotes();
	VARIANT ClearOutline();
	VARIANT ColumnDifferences(const VARIANT& Comparison);
	VARIANT Columns(const VARIANT& Index);
	VARIANT Consolidate(const VARIANT& Sources, const VARIANT& Function, const VARIANT& TopRow, const VARIANT& LeftColumn, const VARIANT& CreateLinks);
	VARIANT Copy(const VARIANT& Destination);
	VARIANT CopyFromRecordset(const VARIANT& Data, const VARIANT& MaxRows, const VARIANT& MaxColumns);
	VARIANT CopyPicture(const VARIANT& Appearance, const VARIANT& Format);
	VARIANT CreateNames(const VARIANT& Top, const VARIANT& Left, const VARIANT& Bottom, const VARIANT& Right);
	VARIANT CreatePublisher(const VARIANT& Edition, const VARIANT& Appearance, const VARIANT& ContainsPICT, const VARIANT& ContainsBIFF, const VARIANT& ContainsRTF, const VARIANT& ContainsVALU);
	VARIANT Cut(const VARIANT& Destination);
	VARIANT DataSeries(const VARIANT& Rowcol, const VARIANT& Type, const VARIANT& Date, const VARIANT& Step, const VARIANT& Stop, const VARIANT& Trend);
	VARIANT Delete(const VARIANT& Shift);
	VARIANT DoDialogBox();
	VARIANT End(const VARIANT& Direction);
	VARIANT FillDown();
	VARIANT FillLeft();
	VARIANT FillRight();
	VARIANT FillUp();
	VARIANT Find(const VARIANT& What, const VARIANT& After, const VARIANT& LookIn, const VARIANT& LookAt, const VARIANT& SearchOrder, const VARIANT& SearchDirection, const VARIANT& MatchCase, const VARIANT& MatchByte);
	VARIANT FindNext(const VARIANT& After);
	VARIANT FindPrevious(const VARIANT& After);
	VARIANT FunctionWizard();
	VARIANT GoalSeek(const VARIANT& Goal, const VARIANT& ChangingCell);
	VARIANT Group(const VARIANT& Start, const VARIANT& End, const VARIANT& By, const VARIANT& Periods);
	VARIANT Insert(const VARIANT& Shift);
	VARIANT Item(const VARIANT& RowIndex, const VARIANT& ColumnIndex);
	VARIANT Justify();
	VARIANT ListNames();
	VARIANT NavigateArrow(const VARIANT& TowardPrecedent, const VARIANT& ArrowNumber, const VARIANT& LinkNumber);
	VARIANT NoteText(const VARIANT& Text, const VARIANT& Start, const VARIANT& Length);
	VARIANT Offset(const VARIANT& RowOffset, const VARIANT& ColumnOffset);
	VARIANT Parse(const VARIANT& ParseLine, const VARIANT& Destination);
	VARIANT PasteSpecial(const VARIANT& Paste, const VARIANT& Operation, const VARIANT& SkipBlanks, const VARIANT& Transpose);
	VARIANT PrintOut(const VARIANT& From, const VARIANT& To, const VARIANT& Copies, const VARIANT& Preview, const VARIANT& ActivePrinter, const VARIANT& PrintToFile, const VARIANT& Collate);
	VARIANT PrintPreview();
	VARIANT Range_(const VARIANT& Cell1, const VARIANT& Cell2);
	VARIANT RemoveSubtotal();
	VARIANT Replace(const VARIANT& What, const VARIANT& Replacement, const VARIANT& LookAt, const VARIANT& SearchOrder, const VARIANT& MatchCase, const VARIANT& MatchByte);
	VARIANT Resize(const VARIANT& RowSize, const VARIANT& ColumnSize);
	VARIANT RowDifferences(const VARIANT& Comparison);
	VARIANT Rows(const VARIANT& Index);
	VARIANT Run(const VARIANT& Arg1, const VARIANT& Arg2, const VARIANT& Arg3, const VARIANT& Arg4, const VARIANT& Arg5, const VARIANT& Arg6, const VARIANT& Arg7, const VARIANT& Arg8, const VARIANT& Arg9, const VARIANT& Arg10, 
		const VARIANT& Arg11, const VARIANT& Arg12, const VARIANT& Arg13, const VARIANT& Arg14, const VARIANT& Arg15, const VARIANT& Arg16, const VARIANT& Arg17, const VARIANT& Arg18, const VARIANT& Arg19, const VARIANT& Arg20, 
		const VARIANT& Arg21, const VARIANT& Arg22, const VARIANT& Arg23, const VARIANT& Arg24, const VARIANT& Arg25, const VARIANT& Arg26, const VARIANT& Arg27, const VARIANT& Arg28, const VARIANT& Arg29, const VARIANT& Arg30);
	VARIANT Select();
	VARIANT Show();
	VARIANT ShowDependents(const VARIANT& Remove);
	VARIANT ShowErrors();
	VARIANT ShowPrecedents(const VARIANT& Remove);
	VARIANT Sort(const VARIANT& Key1, const VARIANT& Order1, const VARIANT& Key2, const VARIANT& Type, const VARIANT& Order2, const VARIANT& Key3, const VARIANT& Order3, const VARIANT& Header, const VARIANT& OrderCustom, const VARIANT& MatchCase, 
		const VARIANT& Orientation);
	VARIANT SortSpecial(const VARIANT& SortMethod, const VARIANT& Key1, const VARIANT& Order1, const VARIANT& Type, const VARIANT& Key2, const VARIANT& Order2, const VARIANT& Key3, const VARIANT& Order3, const VARIANT& Header, 
		const VARIANT& OrderCustom, const VARIANT& MatchCase, const VARIANT& Orientation);
	VARIANT SpecialCells(const VARIANT& Type, const VARIANT& Value);
	VARIANT SubscribeTo(const VARIANT& Edition, const VARIANT& Format);
	VARIANT Subtotal(const VARIANT& GroupBy, const VARIANT& Function, const VARIANT& TotalList, const VARIANT& Replace, const VARIANT& PageBreaks, const VARIANT& SummaryBelowData);
	VARIANT Table(const VARIANT& RowInput, const VARIANT& ColumnInput);
	VARIANT TextToColumns(const VARIANT& Destination, const VARIANT& DataType, const VARIANT& TextQualifier, const VARIANT& ConsecutiveDelimiter, const VARIANT& Tab, const VARIANT& Semicolon, const VARIANT& Comma, const VARIANT& Space, 
		const VARIANT& Other, const VARIANT& OtherChar, const VARIANT& FieldInfo);
	VARIANT Ungroup();
	VARIANT Worksheet();
};
