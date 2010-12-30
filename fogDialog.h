#pragma once

#include "gl\gl.h"    // Include the standard OpenGL  headers
// fogDialog dialog

class fogDialog : public CDialog
{
	DECLARE_DYNAMIC(fogDialog)

public:
	static const int DENSITY_DEF = 30;
	static const int FOG_COLOR_R_DEF = 0;
	static const int FOG_COLOR_G_DEF = 0;
	static const int FOG_COLOR_B_DEF = 0;
	static const int FOG_COLOR_A_DEF = 1;

	static const int FOG_START_DEF = 1;
	static const int FOG_END_DEF= 100;
	static const int FOG_MODE_DEF = GL_LINEAR;	//{GL_EXP, GL_EXP2, GL_LINEAR}

	fogDialog(	double valDens = DENSITY_DEF,
				double valColR = FOG_COLOR_R_DEF,
				double valColG = FOG_COLOR_G_DEF,
				double valColB = FOG_COLOR_B_DEF,
				double valColA = FOG_COLOR_A_DEF,
				double valStart = FOG_START_DEF,
				double valEnd = FOG_END_DEF,
				int valMode = FOG_MODE_DEF,
				CWnd* pParent = NULL);   // standard constructor
	virtual ~fogDialog();

// Dialog Data
	enum { IDD = IDD_FOG_DLG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	int density ;
	double red ;
	double green ;
	double blue ;
	double alfa ;
	double start ;
	double end ;
	int mode ;

	DECLARE_MESSAGE_MAP()

public:
	double fogDialog::getDensity() {
		return density;
	}
	double fogDialog::getRed() {
		return red;
	}
	double fogDialog::getGreen() {
		return green;
	}
	double fogDialog::getBlue() {
		return blue;
	}
	double fogDialog::getAlfa() {
		return alfa;
	}
	double fogDialog::getStart() {
		return start;
	}
	double fogDialog::getEnd() {
		return end;
	}
	double fogDialog::getMode() {
		return mode;
	}
};
