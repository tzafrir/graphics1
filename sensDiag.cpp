// sensDiag.cpp : implementation file
//

#include "stdafx.h"
#include "OpenGL.h"
#include "sensDiag.h"


// sensDiag dialog

IMPLEMENT_DYNCREATE(sensDiag, CDHtmlDialog)

sensDiag::sensDiag(CWnd* pParent /*=NULL*/)
	: CDHtmlDialog(sensDiag::IDD, sensDiag::IDH, pParent)
{

}

sensDiag::~sensDiag()
{
}

void sensDiag::DoDataExchange(CDataExchange* pDX)
{
	CDHtmlDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_SCROLLBAR1, val);
}

BOOL sensDiag::OnInitDialog()
{
	CDHtmlDialog::OnInitDialog();
	return TRUE;  // return TRUE  unless you set the focus to a control
}

BEGIN_MESSAGE_MAP(sensDiag, CDHtmlDialog)
END_MESSAGE_MAP()

BEGIN_DHTML_EVENT_MAP(sensDiag)
	DHTML_EVENT_ONCLICK(_T("ButtonOK"), OnButtonOK)
	DHTML_EVENT_ONCLICK(_T("ButtonCancel"), OnButtonCancel)
END_DHTML_EVENT_MAP()



// sensDiag message handlers

HRESULT sensDiag::OnButtonOK(IHTMLElement* /*pElement*/)
{
	OnOK();
	return S_OK;
}

HRESULT sensDiag::OnButtonCancel(IHTMLElement* /*pElement*/)
{
	OnCancel();
	return S_OK;
}
