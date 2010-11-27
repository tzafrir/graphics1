// multiViewsDialog.cpp : implementation file
//

#include "stdafx.h"
#include "OpenGL.h"
#include "multiViewsDialog.h"


// multiViewsDialog dialog

IMPLEMENT_DYNAMIC(multiViewsDialog, CDialog)

multiViewsDialog::multiViewsDialog(int val, CWnd* pParent /*=NULL*/)
	: CDialog(multiViewsDialog::IDD, pParent)
	, numViews(val)
{

}

multiViewsDialog::~multiViewsDialog()
{
}

void multiViewsDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT1, numViews);
	DDV_MinMaxInt(pDX, numViews, VIEWS_MIN, VIEWS_MAX);
}


BEGIN_MESSAGE_MAP(multiViewsDialog, CDialog)
END_MESSAGE_MAP()


// multiViewsDialog message handlers
