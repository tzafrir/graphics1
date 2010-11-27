#pragma once


// sensitivityDialog dialog

class sensitivityDialog : public CDialog
{
	DECLARE_DYNAMIC(sensitivityDialog)
public:
	static const int SENS_MIN = 1;
	static const int SENS_MAX = 100;
	static const int SENS_DEFAULT = 50;
public:
	sensitivityDialog(int val, CWnd* pParent = NULL);   // standard constructor
	virtual ~sensitivityDialog();

// Dialog Data
	enum { IDD = IDD_DIALOG2 };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	DECLARE_MESSAGE_MAP()

protected:
	int sens;
public:
	afx_msg void OnBnClickedOk();

int sensitivityDialog::getVal() {
	return sens;
}

};