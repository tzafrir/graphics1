#pragma once

#include "gl\gl.h"    // Include the standard OpenGL  headers
// fogDialog dialog

class fogDialog : public CDialog
{
	DECLARE_DYNAMIC(fogDialog)

public:
	static const int DENSITY_DEF = 30;
	static const int FOG_COLOR_R_DEF = 1;
	static const int FOG_COLOR_G_DEF = 1;
	static const int FOG_COLOR_B_DEF = 1;
	static const int FOG_COLOR_A_DEF = 1;

	static const int FOG_START_DEF = 1;
	static const int FOG_END_DEF= 50;
	static const int FOG_MODE_DEF = GL_LINEAR;	//{GL_EXP, GL_EXP2, GL_LINEAR}
	static const int FOG_QUALITY_DEF = GL_NICEST; // GL_NICEST

	fogDialog(	double valDens = DENSITY_DEF,
				double valColR = FOG_COLOR_R_DEF,
				double valColG = FOG_COLOR_G_DEF,
				double valColB = FOG_COLOR_B_DEF,
				double valColA = FOG_COLOR_A_DEF,
				double valStart = FOG_START_DEF,
				double valEnd = FOG_END_DEF,
				int valMode = FOG_MODE_DEF,
				int quality = FOG_QUALITY_DEF,
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
	int alpha ;
	double start ;
	double end ;
	int mode ;
	int quality;

	DECLARE_MESSAGE_MAP()

public:
	int fogDialog::getDensity() {
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
	double fogDialog::getAlpha() {
		return alpha;
	}
	double fogDialog::getStart() {
		return start;
	}
	double fogDialog::getEnd() {
		return end;
	}
	int fogDialog::getMode() {
		return mode;
	}
	int fogDialog::getQuality() {
		return quality;
	}
};
