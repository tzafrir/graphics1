#pragma once
#include "scrollbar1.h"

#ifdef _WIN32_WCE
#error "CDHtmlDialog is not supported for Windows CE."
#endif 

// sensDiag dialog

class sensDiag : public CDHtmlDialog
{
	DECLARE_DYNCREATE(sensDiag)

public:
	sensDiag(CWnd* pParent = NULL);   // standard constructor
	virtual ~sensDiag();
// Overrides
	HRESULT OnButtonOK(IHTMLElement *pElement);
	HRESULT OnButtonCancel(IHTMLElement *pElement);

// Dialog Data
	enum { IDD = IDD_DIALOG1, IDH = IDR_HTML_SENSDIAG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	virtual BOOL OnInitDialog();

	DECLARE_MESSAGE_MAP()
	DECLARE_DHTML_EVENT_MAP()
public:
	CScrollbar1 val;
};
