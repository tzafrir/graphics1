#pragma once


// multiViewsDialog dialog

class multiViewsDialog : public CDialog
{
	DECLARE_DYNAMIC(multiViewsDialog)
public:
	static const int VIEWS_MIN = 0;
	static const int VIEWS_MAX = 100;

public:
	multiViewsDialog(int val = 1, CWnd* pParent = NULL);   // standard constructor
	virtual ~multiViewsDialog();

// Dialog Data
	enum { IDD = IDD_MULTIVIEWS_DLG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	
	int numViews;
	DECLARE_MESSAGE_MAP()
public:
	int multiViewsDialog::getVal() {
		return numViews;
	}
};



