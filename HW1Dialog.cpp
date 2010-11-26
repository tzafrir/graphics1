

// HW1Dialog.cpp : implementation file
//

#include "stdafx.h"
#include "HW1Dialog.h"

// HW0Dialog dialog

IMPLEMENT_DYNAMIC(HW1Dialog, CDialog)

HW1Dialog::HW1Dialog(int val /*=50*/, CWnd* pParent /*=NULL*/)
	: CDialog(HW1Dialog::IDD, pParent)
	, val(val)
{
}

HW0Dialog::~HW1Dialog()
{
}

void HW0Dialog::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT1, HW1Dialog::SENS_DEFAULT);
	DDV_MinMaxFloat(pDX, val, HW1Dialog::SENS_MIN, HW1Dialog::SENS_MAX);
}


// HW0Dialog message handlers

float HW1Dialog::getVal() {
	return val;
}
