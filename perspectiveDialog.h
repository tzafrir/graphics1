#pragma once


// perspectiveDialog dialog

class perspectiveDialog : public CDialog
{
	DECLARE_DYNCREATE(perspectiveDialog)
public:

	static const int PERS_MIN = 0;
	static const int PERS_MAX = 10;
	static const int PERS_DEFAULT = 1;
	static const int PERS_DEFAULT_D = 4;

public:
	perspectiveDialog::perspectiveDialog(float valL = PERS_DEFAULT
										, float valR = PERS_DEFAULT
										, float valT = PERS_DEFAULT
										, float valB = PERS_DEFAULT
										, float valD = PERS_DEFAULT_D
										, CWnd* pParent = NULL);   // standard constructor
	virtual ~perspectiveDialog();
// Overrides
	afx_msg void OnBnClickedOk();

// Dialog Data
	enum { IDD = IDD_DIALOG3};

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	virtual BOOL OnInitDialog();
protected:
	double left;
	double right;
	double bottom;
	double top;
	double dVal;

	DECLARE_MESSAGE_MAP()
public:
	double perspectiveDialog::getLeft() {
		return left;
	}
	double perspectiveDialog::getRight() {
		return right;
	}
	double perspectiveDialog::getTop() {
		return top;
	}
	double perspectiveDialog::getBottom() {
		return bottom;
	}
	double perspectiveDialog::getD() {
		return dVal;
	}
};
