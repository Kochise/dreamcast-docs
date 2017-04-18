// Machine generated IDispatch driver class(es) created with MFCDSPWZ tool.
/////////////////////////////////////////////////////////////////////////////
// ChartObjects wrapper class

class ChartObjects : public COleDispatchDriver
{
// Attributes
public:
	VARIANT GetBorder();
	void SetBorder(const VARIANT&);
	VARIANT GetCount();
	void SetCount(const VARIANT&);
	VARIANT GetCreator();
	void SetCreator(const VARIANT&);
	VARIANT GetEnabled();
	void SetEnabled(const VARIANT&);
	VARIANT GetHeight();
	void SetHeight(const VARIANT&);
	VARIANT GetInterior();
	void SetInterior(const VARIANT&);
	VARIANT GetLeft();
	void SetLeft(const VARIANT&);
	VARIANT GetLocked();
	void SetLocked(const VARIANT&);
	VARIANT GetOnAction();
	void SetOnAction(const VARIANT&);
	VARIANT GetParent();
	void SetParent(const VARIANT&);
	VARIANT GetPlacement();
	void SetPlacement(const VARIANT&);
	VARIANT GetPrintObject();
	void SetPrintObject(const VARIANT&);
	VARIANT GetRoundedCorners();
	void SetRoundedCorners(const VARIANT&);
	VARIANT GetShadow();
	void SetShadow(const VARIANT&);
	VARIANT GetTop();
	void SetTop(const VARIANT&);
	VARIANT GetVisible();
	void SetVisible(const VARIANT&);
	VARIANT GetWidth();
	void SetWidth(const VARIANT&);
	VARIANT GetZOrder();
	void SetZOrder(const VARIANT&);

// Operations
public:
	VARIANT _NewEnum();
	VARIANT Add(const VARIANT& Left, const VARIANT& Top, const VARIANT& Width, const VARIANT& Height);
	VARIANT Application();
	VARIANT BringToFront();
	VARIANT Copy();
	VARIANT CopyPicture(const VARIANT& Appearance, const VARIANT& Format);
	VARIANT Cut();
	VARIANT Delete();
	VARIANT Duplicate();
	VARIANT Group();
	VARIANT Item(const VARIANT& Index);
	VARIANT Select(const VARIANT& Replace);
	VARIANT SendToBack();
};
