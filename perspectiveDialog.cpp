// perspectiveDialog.cpp : implementation file
//

#include "stdafx.h"
#include "OpenGL.h"
#include "perspectiveDialog.h"
#include <limits>


// perspectiveDialog dialog

IMPLEMENT_DYNCREATE(perspectiveDialog, CDialog)

perspectiveDialog::perspectiveDialog(float valL, float valR,float valT,float valB,float valD,
														CWnd* pParent /*=NULL*/)
	: CDialog(perspectiveDialog::IDD, pParent)
	,left(valL), right(valR), top(valT), bottom(valB), dVal(valD)
{
}

perspectiveDialog::~perspectiveDialog()
{
}

void perspectiveDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT_L, left);
	DDX_Text(pDX, IDC_EDIT_R, right);
	DDX_Text(pDX, IDC_EDIT_T, top);
	DDX_Text(pDX, IDC_EDIT_B, bottom);
	DDX_Text(pDX, IDC_EDIT_D, dVal);
	DDV_MinMaxFloat(pDX, left, PERS_MIN, PERS_MAX);
	DDV_MinMaxFloat(pDX, right, PERS_MIN, PERS_MAX);
	DDV_MinMaxFloat(pDX, top, PERS_MIN, PERS_MAX);
	DDV_MinMaxFloat(pDX, bottom, PERS_MIN, PERS_MAX);
	DDV_MinMaxFloat(pDX, dVal, PERS_MIN, INT_MAX);
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

