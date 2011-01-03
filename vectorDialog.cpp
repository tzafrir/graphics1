// vectorDialog.cpp : implementation file
//

#include "stdafx.h"
#include "OpenGL.h"
#include "vectorDialog.h"


// vectorDialog dialog

IMPLEMENT_DYNAMIC(vectorDialog, CDialog)

vectorDialog::vectorDialog(double valX, double valY, double valZ, 
												CWnd* pParent /*=NULL*/)
			: CDialog(vectorDialog::IDD, pParent), x(valX), y(valY), z(valZ)
{

}

vectorDialog::~vectorDialog()
{
}

void vectorDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_TEXT_X, x);
	DDX_Text(pDX, IDC_TEXT_Y, y);
	DDX_Text(pDX, IDC_TEXT_Z, z);
}

BEGIN_MESSAGE_MAP(vectorDialog, CDialog)
END_MESSAGE_MAP()


// vectorDialog message handlers
