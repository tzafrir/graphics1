// fogDialog.cpp : implementation file
//

#include "stdafx.h"
#include "OpenGL.h"
#include "fogDialog.h"


// fogDialog dialog

IMPLEMENT_DYNAMIC(fogDialog, CDialog)

fogDialog::fogDialog(	double valDens, double valColR , double valColG ,
						double valColB , double valColA , double valStart ,
						double valEnd , 
						int valMode , 
						CWnd* pParent/*=NULL*/)
						: CDialog(fogDialog::IDD, pParent),
							density(valDens),red(valColR),green(valColG),blue(valColB),
							alfa(valColA), start(valStart), end(valEnd),mode(valMode)
{
}


fogDialog::~fogDialog()
{
}

void fogDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT_START, start);
	DDX_Text(pDX, IDC_EDIT_END, end);
	DDX_Slider(pDX, IDC_SLIDER_DENS , density);
}


BEGIN_MESSAGE_MAP(fogDialog, CDialog)
END_MESSAGE_MAP()


// fogDialog message handlers
