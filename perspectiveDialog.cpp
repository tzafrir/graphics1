// perspectiveDialog.cpp : implementation file
//

#include "stdafx.h"
#include "OpenGL.h"
#include "perspectiveDialog.h"


// perspectiveDialog dialog

IMPLEMENT_DYNCREATE(perspectiveDialog, CDialog)

perspectiveDialog::perspectiveDialog(float val, CWnd* pParent /*=NULL*/)
	: CDialog(perspectiveDialog::IDD, pParent)
	,ratio(val)
{
}

perspectiveDialog::~perspectiveDialog()
{
}

void perspectiveDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT1, ratio);
	DDV_MinMaxFloat(pDX, ratio, PERS_MIN, PERS_MAX);
}

BOOL perspectiveDialog::OnInitDialog()
{
	CDialog::OnInitDialog();
	return TRUE;  // return TRUE  unless you set the focus to a control
}

BEGIN_MESSAGE_MAP(perspectiveDialog, CDialog)
	ON_BN_CLICKED(IDOK, &perspectiveDialog::OnBnClickedOk)
END_MESSAGE_MAP()


// perspectiveDialog message handlers

void perspectiveDialog::OnBnClickedOk()
{
	// TODO: Add your control notification handler code here
	OnOK();
}

