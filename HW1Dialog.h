#pragma once


// HW1Dialog dialog

class HW1Dialog : public CDialog
{
	DECLARE_DYNAMIC(HW1Dialog)
private:
	static const int SENS_MIN = 1;
	static const int SENS_MAX = 100;
	static const int SENS_DEFAULT = 50;

public:
	HW1Dialog(float val = SENS_DEFAULT, CWnd* pParent = NULL);   // standard constructor
	float getVal();
	virtual ~HW1Dialog();

// Dialog Data
	enum { IDD };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnEnChangeEdit1();
protected:
	float val;

};