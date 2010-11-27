#pragma once

#ifdef _WIN32_WCE
#error "CDHtmlDialog is not supported for Windows CE."
#endif 

// perspectiveDialog dialog

class perspectiveDialog : public CDialog
{
	DECLARE_DYNCREATE(perspectiveDialog)
public:
	/*PERS_DEFAULT = 1.0;
	PERS_MAX =10.0;
	PERS_MIN =0.01;*/
	static const int PERS_MIN = 0;
	static const int PERS_MAX = 10;
	static const int PERS_DEFAULT = 1;

public:
	perspectiveDialog(float val = PERS_DEFAULT, CWnd* pParent = NULL);   // standard constructor
	virtual ~perspectiveDialog();
// Overrides
	afx_msg void OnBnClickedOk();

// Dialog Data
	enum { IDD = IDD_DIALOG3};

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	virtual BOOL OnInitDialog();
protected:
	float ratio;

	DECLARE_MESSAGE_MAP()
public:
	float perspectiveDialog::getVal() {
		return ratio;
	}
};
