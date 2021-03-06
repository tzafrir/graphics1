#pragma once

// Machine generated IDispatch wrapper class(es) created by Microsoft Visual C++

// NOTE: Do not modify the contents of this file.  If this class is regenerated by
//  Microsoft Visual C++, your modifications will be overwritten.

/////////////////////////////////////////////////////////////////////////////
// CScrollbar1 wrapper class

class CScrollbar1 : public CWnd
{
protected:
	DECLARE_DYNCREATE(CScrollbar1)
public:
	CLSID const& GetClsid()
	{
		static CLSID const clsid
			= { 0xDFD181E0, 0x5E2F, 0x11CE, { 0xA4, 0x49, 0x0, 0xAA, 0x0, 0x4A, 0x80, 0x3D } };
		return clsid;
	}
	virtual BOOL Create(LPCTSTR lpszClassName, LPCTSTR lpszWindowName, DWORD dwStyle,
						const RECT& rect, CWnd* pParentWnd, UINT nID, 
						CCreateContext* pContext = NULL)
	{ 
		return CreateControl(GetClsid(), lpszWindowName, dwStyle, rect, pParentWnd, nID); 
	}

    BOOL Create(LPCTSTR lpszWindowName, DWORD dwStyle, const RECT& rect, CWnd* pParentWnd, 
				UINT nID, CFile* pPersist = NULL, BOOL bStorage = FALSE,
				BSTR bstrLicKey = NULL)
	{ 
		return CreateControl(GetClsid(), lpszWindowName, dwStyle, rect, pParentWnd, nID,
		pPersist, bStorage, bstrLicKey); 
	}

// Attributes
public:
enum
{
    fmDropEffectNone = 0,
    fmDropEffectCopy = 1,
    fmDropEffectMove = 2,
    fmDropEffectCopyOrMove = 3
}fmDropEffect;
enum
{
    fmActionCut = 0,
    fmActionCopy = 1,
    fmActionPaste = 2,
    fmActionDragDrop = 3
}fmAction;
enum
{
    fmModeInherit = -2,
    fmModeOn = -1,
    fmModeOff = 0
}fmMode;
enum
{
    fmMousePointerDefault = 0,
    fmMousePointerArrow = 1,
    fmMousePointerCross = 2,
    fmMousePointerIBeam = 3,
    fmMousePointerSizeNESW = 6,
    fmMousePointerSizeNS = 7,
    fmMousePointerSizeNWSE = 8,
    fmMousePointerSizeWE = 9,
    fmMousePointerUpArrow = 10,
    fmMousePointerHourGlass = 11,
    fmMousePointerNoDrop = 12,
    fmMousePointerAppStarting = 13,
    fmMousePointerHelp = 14,
    fmMousePointerSizeAll = 15,
    fmMousePointerCustom = 99
}fmMousePointer;
enum
{
    fmScrollBarsNone = 0,
    fmScrollBarsHorizontal = 1,
    fmScrollBarsVertical = 2,
    fmScrollBarsBoth = 3
}fmScrollBars;
enum
{
    fmScrollActionNoChange = 0,
    fmScrollActionLineUp = 1,
    fmScrollActionLineDown = 2,
    fmScrollActionPageUp = 3,
    fmScrollActionPageDown = 4,
    fmScrollActionBegin = 5,
    fmScrollActionEnd = 6,
    _fmScrollActionAbsoluteChange = 7,
    fmScrollActionPropertyChange = 8,
    fmScrollActionControlRequest = 9,
    fmScrollActionFocusRequest = 10
}fmScrollAction;
enum
{
    fmCycleAllForms = 0,
    fmCycleCurrentForm = 2
}fmCycle;
enum
{
    fmZOrderFront = 0,
    fmZOrderBack = 1
}fmZOrder;
enum
{
    fmBorderStyleNone = 0,
    fmBorderStyleSingle = 1
}fmBorderStyle;
enum
{
    fmTextAlignLeft = 1,
    fmTextAlignCenter = 2,
    fmTextAlignRight = 3
}fmTextAlign;
enum
{
    fmAlignmentLeft = 0,
    fmAlignmentRight = 1
}fmAlignment;
enum
{
    fmBordersNone = 0,
    fmBordersBox = 1,
    fmBordersLeft = 2,
    fmBordersTop = 3
}fmBorders;
enum
{
    fmBackStyleTransparent = 0,
    fmBackStyleOpaque = 1
}fmBackStyle;
enum
{
    fmButtonStylePushButton = 0,
    fmButtonStyleToggleButton = 1
}fmButtonStyle;
enum
{
    fmPicPositionCenter = 0,
    fmPicPositionTopLeft = 1,
    fmPicPositionTopCenter = 2,
    fmPicPositionTopRight = 3,
    fmPicPositionCenterLeft = 4,
    fmPicPositionCenterRight = 5,
    fmPicPositionBottomLeft = 6,
    fmPicPositionBottomCenter = 7,
    fmPicPositionBottomRight = 8
}fmPicPosition;
enum
{
    fmVerticalScrollBarSideRight = 0,
    fmVerticalScrollBarSideLeft = 1
}fmVerticalScrollBarSide;
enum
{
    fmLayoutEffectNone = 0,
    fmLayoutEffectInitiate = 1,
    _fmLayoutEffectRespond = 2
}fmLayoutEffect;
enum
{
    fmSpecialEffectFlat = 0,
    fmSpecialEffectRaised = 1,
    fmSpecialEffectSunken = 2,
    fmSpecialEffectEtched = 3,
    fmSpecialEffectBump = 6
}fmSpecialEffect;
enum
{
    fmDragStateEnter = 0,
    fmDragStateLeave = 1,
    fmDragStateOver = 2
}fmDragState;
enum
{
    fmPictureSizeModeClip = 0,
    fmPictureSizeModeStretch = 1,
    fmPictureSizeModeZoom = 3
}fmPictureSizeMode;
enum
{
    fmPictureAlignmentTopLeft = 0,
    fmPictureAlignmentTopRight = 1,
    fmPictureAlignmentCenter = 2,
    fmPictureAlignmentBottomLeft = 3,
    fmPictureAlignmentBottomRight = 4
}fmPictureAlignment;
enum
{
    fmButtonEffectFlat = 0,
    fmButtonEffectSunken = 2
}fmButtonEffect;
enum
{
    fmOrientationAuto = -1,
    fmOrientationVertical = 0,
    fmOrientationHorizontal = 1
}fmOrientation;
enum
{
    fmSnapPointTopLeft = 0,
    fmSnapPointTopCenter = 1,
    fmSnapPointTopRight = 2,
    fmSnapPointCenterLeft = 3,
    fmSnapPointCenter = 4,
    fmSnapPointCenterRight = 5,
    fmSnapPointBottomLeft = 6,
    fmSnapPointBottomCenter = 7,
    fmSnapPointBottomRight = 8
}fmSnapPoint;
enum
{
    fmPicturePositionLeftTop = 0,
    fmPicturePositionLeftCenter = 1,
    fmPicturePositionLeftBottom = 2,
    fmPicturePositionRightTop = 3,
    fmPicturePositionRightCenter = 4,
    fmPicturePositionRightBottom = 5,
    fmPicturePositionAboveLeft = 6,
    fmPicturePositionAboveCenter = 7,
    fmPicturePositionAboveRight = 8,
    fmPicturePositionBelowLeft = 9,
    fmPicturePositionBelowCenter = 10,
    fmPicturePositionBelowRight = 11,
    fmPicturePositionCenter = 12
}fmPicturePosition;
enum
{
    fmDisplayStyleText = 1,
    fmDisplayStyleList = 2,
    fmDisplayStyleCombo = 3,
    fmDisplayStyleCheckBox = 4,
    fmDisplayStyleOptionButton = 5,
    fmDisplayStyleToggle = 6,
    fmDisplayStyleDropList = 7
}fmDisplayStyle;
enum
{
    fmShowListWhenNever = 0,
    fmShowListWhenButton = 1,
    fmShowListWhenFocus = 2,
    fmShowListWhenAlways = 3
}fmShowListWhen;
enum
{
    fmShowDropButtonWhenNever = 0,
    fmShowDropButtonWhenFocus = 1,
    fmShowDropButtonWhenAlways = 2
}fmShowDropButtonWhen;
enum
{
    fmMultiSelectSingle = 0,
    fmMultiSelectMulti = 1,
    fmMultiSelectExtended = 2
}fmMultiSelect;
enum
{
    fmListStylePlain = 0,
    fmListStyleOption = 1
}fmListStyle;
enum
{
    fmEnterFieldBehaviorSelectAll = 0,
    fmEnterFieldBehaviorRecallSelection = 1
}fmEnterFieldBehavior;
enum
{
    fmDragBehaviorDisabled = 0,
    fmDragBehaviorEnabled = 1
}fmDragBehavior;
enum
{
    fmMatchEntryFirstLetter = 0,
    fmMatchEntryComplete = 1,
    fmMatchEntryNone = 2
}fmMatchEntry;
enum
{
    fmDropButtonStylePlain = 0,
    fmDropButtonStyleArrow = 1,
    fmDropButtonStyleEllipsis = 2,
    fmDropButtonStyleReduce = 3
}fmDropButtonStyle;
enum
{
    fmStyleDropDownCombo = 0,
    fmStyleDropDownList = 2
}fmStyle;
enum
{
    fmTabOrientationTop = 0,
    fmTabOrientationBottom = 1,
    fmTabOrientationLeft = 2,
    fmTabOrientationRight = 3
}fmTabOrientation;
enum
{
    fmTabStyleTabs = 0,
    fmTabStyleButtons = 1,
    fmTabStyleNone = 2
}fmTabStyle;
enum
{
    fmIMEModeNoControl = 0,
    fmIMEModeOn = 1,
    fmIMEModeOff = 2,
    fmIMEModeDisable = 3,
    fmIMEModeHiragana = 4,
    fmIMEModeKatakana = 5,
    fmIMEModeKatakanaHalf = 6,
    fmIMEModeAlphaFull = 7,
    fmIMEModeAlpha = 8,
    fmIMEModeHangulFull = 9,
    fmIMEModeHangul = 10,
    fmIMEModeHanziFull = 11,
    fmIMEModeHanzi = 12
}fmIMEMode;
enum
{
    fmTransitionEffectNone = 0,
    fmTransitionEffectCoverUp = 1,
    fmTransitionEffectCoverRightUp = 2,
    fmTransitionEffectCoverRight = 3,
    fmTransitionEffectCoverRightDown = 4,
    fmTransitionEffectCoverDown = 5,
    fmTransitionEffectCoverLeftDown = 6,
    fmTransitionEffectCoverLeft = 7,
    fmTransitionEffectCoverLeftUp = 8,
    fmTransitionEffectPushUp = 9,
    fmTransitionEffectPushRight = 10,
    fmTransitionEffectPushDown = 11,
    fmTransitionEffectPushLeft = 12
}fmTransitionEffect;
enum
{
    _fmListBoxStylesNone = 0,
    _fmListBoxStylesListBox = 1,
    _fmListBoxStylesComboBox = 2
}fmListBoxStyles;
enum
{
    _fmRepeatDirectionHorizontal = 0,
    _fmRepeatDirectionVertical = 1
}fmRepeatDirection;
enum
{
    _fmEnAutoSizeNone = 0,
    _fmEnAutoSizeHorizontal = 1,
    _fmEnAutoSizeVertical = 2,
    _fmEnAutoSizeBoth = 3
}fmEnAutoSize;


// Operations
public:

// IScrollbar

// Functions
//

	void put_Cancel(BOOL newValue)
	{
		static BYTE parms[] = VTS_BOOL ;
		InvokeHelper(0x80010038, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
	}
	BOOL get_Cancel()
	{
		BOOL result;
		InvokeHelper(0x80010038, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
		return result;
	}
	void put_ControlSource(LPCTSTR newValue)
	{
		static BYTE parms[] = VTS_BSTR ;
		InvokeHelper(0x80018001, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
	}
	CString get_ControlSource()
	{
		CString result;
		InvokeHelper(0x80018001, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
		return result;
	}
	void put_ControlTipText(LPCTSTR newValue)
	{
		static BYTE parms[] = VTS_BSTR ;
		InvokeHelper(0x80010045, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
	}
	CString get_ControlTipText()
	{
		CString result;
		InvokeHelper(0x80010045, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
		return result;
	}
	void put_Default(BOOL newValue)
	{
		static BYTE parms[] = VTS_BOOL ;
		InvokeHelper(0x80010037, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
	}
	BOOL get_Default()
	{
		BOOL result;
		InvokeHelper(0x80010037, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
		return result;
	}
	void _SetHeight(long Height)
	{
		static BYTE parms[] = VTS_I4 ;
		InvokeHelper(0x60020008, DISPATCH_METHOD, VT_EMPTY, NULL, parms, Height);
	}
	void _GetHeight(long * Height)
	{
		static BYTE parms[] = VTS_PI4 ;
		InvokeHelper(0x60020009, DISPATCH_METHOD, VT_EMPTY, NULL, parms, Height);
	}
	void put_Height(float newValue)
	{
		static BYTE parms[] = VTS_R4 ;
		InvokeHelper(0x80010006, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
	}
	float get_Height()
	{
		float result;
		InvokeHelper(0x80010006, DISPATCH_PROPERTYGET, VT_R4, (void*)&result, NULL);
		return result;
	}
	void put_HelpContextID(long newValue)
	{
		static BYTE parms[] = VTS_I4 ;
		InvokeHelper(0x80010032, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
	}
	long get_HelpContextID()
	{
		long result;
		InvokeHelper(0x80010032, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
		return result;
	}
	void put_InSelection(BOOL newValue)
	{
		static BYTE parms[] = VTS_BOOL ;
		InvokeHelper(0x80018003, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
	}
	BOOL get_InSelection()
	{
		BOOL result;
		InvokeHelper(0x80018003, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
		return result;
	}
	long get_LayoutEffect()
	{
		long result;
		InvokeHelper(0x80018004, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
		return result;
	}
	void _SetLeft(long Left)
	{
		static BYTE parms[] = VTS_I4 ;
		InvokeHelper(0x60020011, DISPATCH_METHOD, VT_EMPTY, NULL, parms, Left);
	}
	void _GetLeft(long * Left)
	{
		static BYTE parms[] = VTS_PI4 ;
		InvokeHelper(0x60020012, DISPATCH_METHOD, VT_EMPTY, NULL, parms, Left);
	}
	void put_Left(float newValue)
	{
		static BYTE parms[] = VTS_R4 ;
		InvokeHelper(0x80010003, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
	}
	float get_Left()
	{
		float result;
		InvokeHelper(0x80010003, DISPATCH_PROPERTYGET, VT_R4, (void*)&result, NULL);
		return result;
	}
	void put_Name(LPCTSTR newValue)
	{
		static BYTE parms[] = VTS_BSTR ;
		InvokeHelper(0x80010000, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
	}
	CString get_Name()
	{
		CString result;
		InvokeHelper(0x80010000, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
		return result;
	}
	void _GetOldHeight(long * OldHeight)
	{
		static BYTE parms[] = VTS_PI4 ;
		InvokeHelper(0x60020017, DISPATCH_METHOD, VT_EMPTY, NULL, parms, OldHeight);
	}
	float get_OldHeight()
	{
		float result;
		InvokeHelper(0x80018005, DISPATCH_PROPERTYGET, VT_R4, (void*)&result, NULL);
		return result;
	}
	void _GetOldLeft(long * OldLeft)
	{
		static BYTE parms[] = VTS_PI4 ;
		InvokeHelper(0x60020019, DISPATCH_METHOD, VT_EMPTY, NULL, parms, OldLeft);
	}
	float get_OldLeft()
	{
		float result;
		InvokeHelper(0x80018006, DISPATCH_PROPERTYGET, VT_R4, (void*)&result, NULL);
		return result;
	}
	void _GetOldTop(long * OldTop)
	{
		static BYTE parms[] = VTS_PI4 ;
		InvokeHelper(0x6002001b, DISPATCH_METHOD, VT_EMPTY, NULL, parms, OldTop);
	}
	float get_OldTop()
	{
		float result;
		InvokeHelper(0x80018007, DISPATCH_PROPERTYGET, VT_R4, (void*)&result, NULL);
		return result;
	}
	void _GetOldWidth(long * OldWidth)
	{
		static BYTE parms[] = VTS_PI4 ;
		InvokeHelper(0x6002001d, DISPATCH_METHOD, VT_EMPTY, NULL, parms, OldWidth);
	}
	float get_OldWidth()
	{
		float result;
		InvokeHelper(0x80018008, DISPATCH_PROPERTYGET, VT_R4, (void*)&result, NULL);
		return result;
	}
	LPDISPATCH get_Object()
	{
		LPDISPATCH result;
		InvokeHelper(0x80018009, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
		return result;
	}
	LPDISPATCH get_Parent()
	{
		LPDISPATCH result;
		InvokeHelper(0x80010008, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
		return result;
	}
	void put_RowSource(LPCTSTR newValue)
	{
		static BYTE parms[] = VTS_BSTR ;
		InvokeHelper(0x8001800e, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
	}
	CString get_RowSource()
	{
		CString result;
		InvokeHelper(0x8001800e, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
		return result;
	}
	void put_RowSourceType(short newValue)
	{
		static BYTE parms[] = VTS_I2 ;
		InvokeHelper(0x8001800f, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
	}
	short get_RowSourceType()
	{
		short result;
		InvokeHelper(0x8001800f, DISPATCH_PROPERTYGET, VT_I2, (void*)&result, NULL);
		return result;
	}
	void put_TabIndex(short newValue)
	{
		static BYTE parms[] = VTS_I2 ;
		InvokeHelper(0x8001000f, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
	}
	short get_TabIndex()
	{
		short result;
		InvokeHelper(0x8001000f, DISPATCH_PROPERTYGET, VT_I2, (void*)&result, NULL);
		return result;
	}
	void put_TabStop(BOOL newValue)
	{
		static BYTE parms[] = VTS_BOOL ;
		InvokeHelper(0x8001000e, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
	}
	BOOL get_TabStop()
	{
		BOOL result;
		InvokeHelper(0x8001000e, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
		return result;
	}
	void put_Tag(LPCTSTR newValue)
	{
		static BYTE parms[] = VTS_BSTR ;
		InvokeHelper(0x8001000b, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
	}
	CString get_Tag()
	{
		CString result;
		InvokeHelper(0x8001000b, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
		return result;
	}
	void _SetTop(long Top)
	{
		static BYTE parms[] = VTS_I4 ;
		InvokeHelper(0x6002002b, DISPATCH_METHOD, VT_EMPTY, NULL, parms, Top);
	}
	void _GetTop(long * Top)
	{
		static BYTE parms[] = VTS_PI4 ;
		InvokeHelper(0x6002002c, DISPATCH_METHOD, VT_EMPTY, NULL, parms, Top);
	}
	void put_Top(float newValue)
	{
		static BYTE parms[] = VTS_R4 ;
		InvokeHelper(0x80010004, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
	}
	float get_Top()
	{
		float result;
		InvokeHelper(0x80010004, DISPATCH_PROPERTYGET, VT_R4, (void*)&result, NULL);
		return result;
	}
	void put_BoundValue(VARIANT * newValue)
	{
		static BYTE parms[] = VTS_PVARIANT ;
		InvokeHelper(0x80018010, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
	}
	VARIANT get_BoundValue()
	{
		VARIANT result;
		InvokeHelper(0x80018010, DISPATCH_PROPERTYGET, VT_VARIANT, (void*)&result, NULL);
		return result;
	}
	void put_Visible(BOOL newValue)
	{
		static BYTE parms[] = VTS_BOOL ;
		InvokeHelper(0x80010007, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
	}
	BOOL get_Visible()
	{
		BOOL result;
		InvokeHelper(0x80010007, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
		return result;
	}
	void _SetWidth(long Width)
	{
		static BYTE parms[] = VTS_I4 ;
		InvokeHelper(0x60020033, DISPATCH_METHOD, VT_EMPTY, NULL, parms, Width);
	}
	void _GetWidth(long * Width)
	{
		static BYTE parms[] = VTS_PI4 ;
		InvokeHelper(0x60020034, DISPATCH_METHOD, VT_EMPTY, NULL, parms, Width);
	}
	void put_Width(float newValue)
	{
		static BYTE parms[] = VTS_R4 ;
		InvokeHelper(0x80010005, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
	}
	float get_Width()
	{
		float result;
		InvokeHelper(0x80010005, DISPATCH_PROPERTYGET, VT_R4, (void*)&result, NULL);
		return result;
	}
	void Move(VARIANT Left, VARIANT Top, VARIANT Width, VARIANT Height, VARIANT Layout)
	{
		static BYTE parms[] = VTS_VARIANT VTS_VARIANT VTS_VARIANT VTS_VARIANT VTS_VARIANT ;
		InvokeHelper(0x80018100, DISPATCH_METHOD, VT_EMPTY, NULL, parms, &Left, &Top, &Width, &Height, &Layout);
	}
	void ZOrder(VARIANT zPosition)
	{
		static BYTE parms[] = VTS_VARIANT ;
		InvokeHelper(0x80018105, DISPATCH_METHOD, VT_EMPTY, NULL, parms, &zPosition);
	}
	void Select(BOOL SelectInGroup)
	{
		static BYTE parms[] = VTS_BOOL ;
		InvokeHelper(0x80018102, DISPATCH_METHOD, VT_EMPTY, NULL, parms, SelectInGroup);
	}
	void SetFocus()
	{
		InvokeHelper(0x80018103, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
	}
	long _GethWnd()
	{
		long result;
		InvokeHelper(0x6002003b, DISPATCH_METHOD, VT_I4, (void*)&result, NULL);
		return result;
	}
	long _GetID()
	{
		long result;
		InvokeHelper(0x6002003c, DISPATCH_METHOD, VT_I4, (void*)&result, NULL);
		return result;
	}
	void _Move(long Left, long Top, long Width, long Height)
	{
		static BYTE parms[] = VTS_I4 VTS_I4 VTS_I4 VTS_I4 ;
		InvokeHelper(0x6002003d, DISPATCH_METHOD, VT_EMPTY, NULL, parms, Left, Top, Width, Height);
	}
	void _ZOrder(long zPosition)
	{
		static BYTE parms[] = VTS_I4 ;
		InvokeHelper(0x6002003e, DISPATCH_METHOD, VT_EMPTY, NULL, parms, zPosition);
	}
	void put_BackColor(long newValue)
	{
		static BYTE parms[] = VTS_I4 ;
		InvokeHelper(DISPID_BACKCOLOR, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
	}
	long get_BackColor()
	{
		long result;
		InvokeHelper(DISPID_BACKCOLOR, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
		return result;
	}
	void put_ForeColor(long newValue)
	{
		static BYTE parms[] = VTS_I4 ;
		InvokeHelper(DISPID_FORECOLOR, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
	}
	long get_ForeColor()
	{
		long result;
		InvokeHelper(DISPID_FORECOLOR, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
		return result;
	}
	void put_Enabled(BOOL newValue)
	{
		static BYTE parms[] = VTS_BOOL ;
		InvokeHelper(DISPID_ENABLED, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
	}
	BOOL get_Enabled()
	{
		BOOL result;
		InvokeHelper(DISPID_ENABLED, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
		return result;
	}
	void put_MousePointer(long newValue)
	{
		static BYTE parms[] = VTS_I4 ;
		InvokeHelper(0xfffffdf7, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
	}
	long get_MousePointer()
	{
		long result;
		InvokeHelper(0xfffffdf7, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
		return result;
	}
	void put_Value(long newValue)
	{
		static BYTE parms[] = VTS_I4 ;
		InvokeHelper(0x0, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
	}
	long get_Value()
	{
		long result;
		InvokeHelper(0x0, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
		return result;
	}
	void put_Min(long newValue)
	{
		static BYTE parms[] = VTS_I4 ;
		InvokeHelper(0x64, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
	}
	long get_Min()
	{
		long result;
		InvokeHelper(0x64, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
		return result;
	}
	void put_Max(long newValue)
	{
		static BYTE parms[] = VTS_I4 ;
		InvokeHelper(0x65, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
	}
	long get_Max()
	{
		long result;
		InvokeHelper(0x65, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
		return result;
	}
	void put_SmallChange(long newValue)
	{
		static BYTE parms[] = VTS_I4 ;
		InvokeHelper(0x66, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
	}
	long get_SmallChange()
	{
		long result;
		InvokeHelper(0x66, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
		return result;
	}
	void put_LargeChange(long newValue)
	{
		static BYTE parms[] = VTS_I4 ;
		InvokeHelper(0x67, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
	}
	long get_LargeChange()
	{
		long result;
		InvokeHelper(0x67, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
		return result;
	}
	void put_ProportionalThumb(BOOL newValue)
	{
		static BYTE parms[] = VTS_BOOL ;
		InvokeHelper(0x68, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
	}
	BOOL get_ProportionalThumb()
	{
		BOOL result;
		InvokeHelper(0x68, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
		return result;
	}
	void put_Orientation(long newValue)
	{
		static BYTE parms[] = VTS_I4 ;
		InvokeHelper(0x69, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
	}
	long get_Orientation()
	{
		long result;
		InvokeHelper(0x69, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
		return result;
	}
	void put_Delay(long newValue)
	{
		static BYTE parms[] = VTS_I4 ;
		InvokeHelper(0x6a, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
	}
	long get_Delay()
	{
		long result;
		InvokeHelper(0x6a, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
		return result;
	}
	void put_MouseIcon(LPDISPATCH newValue)
	{
		static BYTE parms[] = VTS_DISPATCH ;
		InvokeHelper(0xfffffdf6, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
	}
	void putref_MouseIcon(LPDISPATCH newValue)
	{
		static BYTE parms[] = VTS_DISPATCH ;
		InvokeHelper(0xfffffdf6, DISPATCH_PROPERTYPUTREF, VT_EMPTY, NULL, parms, newValue);
	}
	LPDISPATCH get_MouseIcon()
	{
		LPDISPATCH result;
		InvokeHelper(0xfffffdf6, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
		return result;
	}

// Properties
//



};
