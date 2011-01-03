#pragma once


// vectorDialog dialog

class vectorDialog : public CDialog
{
	DECLARE_DYNAMIC(vectorDialog)

public:
	vectorDialog(double x = 0, double y = 0, double z = 0, 
							CWnd* pParent = NULL);   // standard constructor
	virtual ~vectorDialog();

// Dialog Data
	enum { IDD = IDD_VECTOR_DLG };

	double vectorDialog::getX() {
		return x;
	}
	double vectorDialog::getY() {
		return y;
	}
	double vectorDialog::getZ() {
		return z;
	}

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	double x;
	double y;
	double z;

	DECLARE_MESSAGE_MAP()
};
