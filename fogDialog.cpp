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
						int valQuality ,
						CWnd* pParent/*=NULL*/)
						: CDialog(fogDialog::IDD, pParent),
							density(valDens),red(valColR),green(valColG),blue(valColB),
							alpha(valColA*100), start(valStart), end(valEnd),mode(valMode), quality(valQuality)
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
	DDX_Slider(pDX, IDC_SLIDER_ALPHA , alpha);
	DDX_CBIndex(pDX, IDC_COMBO_QUALITY, quality);
	DDX_CBIndex(pDX, IDC_COMBO_MODE, mode);
}

BEGIN_MESSAGE_MAP(fogDialog, CDialog)
	ON_BN_CLICKED(IDOK, &fogDialog::OnBnClickedOk)
END_MESSAGE_MAP()

void fogDialog::OnBnClickedOk()
{
	OnOK();
}
