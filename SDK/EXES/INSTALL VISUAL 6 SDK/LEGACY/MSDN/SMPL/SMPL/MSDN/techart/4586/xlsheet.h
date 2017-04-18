// Machine generated IDispatch driver class(es) created with MFCDSPWZ tool.
/////////////////////////////////////////////////////////////////////////////
// Worksheet wrapper class

class Worksheet : public COleDispatchDriver
{
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
	VARIANT ChartObjects();
	//VARIANT ChartObjects(const VARIANT& Index);
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
