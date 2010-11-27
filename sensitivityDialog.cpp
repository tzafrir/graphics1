// sensitivityDialog.cpp : implementation file
//

#include "stdafx.h"
#include "OpenGL.h"
#include "sensitivityDialog.h"


// sensitivityDialog dialog

IMPLEMENT_DYNAMIC(sensitivityDialog, CDialog)

sensitivityDialog::sensitivityDialog(int val, CWnd* pParent /*=NULL*/)
	: CDialog(sensitivityDialog::IDD, pParent)
	,sens(val)
{
}

sensitivityDialog::~sensitivityDialog()
{
}

void sensitivityDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT2, sens);
	DDV_MinMaxInt(pDX, sens, SENS_MIN, SENS_MAX);
}


BEGIN_MESSAGE_MAP(sensitivityDialog, CDialog)
	ON_BN_CLICKED(IDOK, &sensitivityDialog::OnBnClickedOk)
END_MESSAGE_MAP()


// sensitivityDialog message handlers

void sensitivityDialog::OnBnClickedOk()
{
	// TODO: Add your control notification handler code here
	OnOK();
}
