// OpenGLView.h : interface of the COpenGLView class
//
/////////////////////////////////////////////////////////////////////////////


#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


#include "gl\gl.h"    // Include the standard OpenGL  headers
#include "gl\glu.h"   // Add the utility library


#include "Light.h"
#include "afxdlgs.h"

#include <string>
using std::string;

class COpenGLView : public CView
{
protected: // create from serialization only
	COpenGLView();
	DECLARE_DYNCREATE(COpenGLView)

// Attributes
public:
	COpenGLDoc* GetDocument();

// Operations
public:

private:
	int m_nAxis;				// Axis of Action, X Y or Z
	int m_nAction;				// Rotate, Translate, Scale
	int m_nView;				// Orthographic, perspective
	bool m_bIsPerspective;			// is the view perspective
	
	CString m_strItdFileName;		// file name of IRIT data

	int m_nLightShading;			// shading: Flat, Gouraud.

	double m_lMaterialAmbient;		// The Ambient in the scene
	double m_lMaterialDiffuse;		// The Diffuse in the scene
	double m_lMaterialSpecular;		// The Specular in the scene
	int m_nMaterialShininessFactor;		// The cosine factor for the specular

	LightParams m_lights[MAX_LIGHT];	//configurable lights array
	LightParams m_ambientLight;		//ambient light (only RGB is used)

	static double zoomRatioDefault; // hw1 'constant'

	CPoint lastClicked;				// hw1: 
	int nSpace;						// hw1: object / view space
	int mouseSensitivity;			// hw1
	float sensFactor;				// hw1
	bool m_bShowNormals;			// hw1: draw normals
	bool multipleViews;				// hw1
	bool multipleObjects;			// hw1
	int activeView;					// hw1
	double m_lNormalScale;			// hw1 $$: Larger -> larger normals
	bool m_bDrawVertexNormals;		// hw1
	double m_lCenterX;
	double m_lCenterY;
	double m_lCenterZ;
	double m_lColorR;	// $$$$$
	double m_lColorG;	// $ User chosen color
	double m_lColorB;	// $$$$$
	bool m_bChoseColor; // $^ Set this to true when user chooses a color
	
	double m_backColorR;	// $$$$$
	double m_backColorG;	// $ User background chosen color
	double m_backColorB;	// $$$$$
	bool m_backChoseColor;
	
	double m_activeColorR;	// $$$$$
	double m_activeColorG;	// $ User highlight chosen color
	double m_activeColorB;	// $$$$$
	bool m_bIsActiveView;

	double m_lTotalSize; // 0.5 Diagonal of the bounding box
	double m_lZoomRatio; // Amount of zoom in both perspective/ortho mode (managed by Scale() )
	
	double m_lPerspectiveRight; 
	double m_lPerspectiveLeft;
	double m_lPerspectiveTop;
	double m_lPerspectiveBottom;
	double m_lPerspectiveDVal;

	bool m_fogEnabled ;
	GLfloat density;// = 0.3; //set the density to 0.3 which is acctually quite thick
	GLfloat fogColor[4];// = {0.5, 0.5, 0.5, 1.0};
	GLfloat fogStart;
	GLfloat fogEnd;
	int fogMode;

	bool m_bMayDraw; // For internal use - lock for drawing
	bool m_bDrawBoundingBox; // $$ Should draw bounding box around each object

	bool m_bUseModelColors; // %gui% should use the colors from the model instead of global values
	bool m_bDrawWireframe;
	bool m_bCullBackFaces; // %gui% cull back faces or not

	// %gui%: Need dialog for this group:
	bool m_bGenerateTexturesU; // %gui% Use generated textures instead of using given U coords
	bool m_bGenerateTexturesV; // %gui% Use generated textures instead of using given V coords 
	GLfloat texGenU[3]; // %gui% parameters for U generation. Only expose first 3.
	GLfloat texGenV[3]; // %gui% parameters for V generation. Only expose first 3.
	bool m_bGentexUScreenSpace; // %gui% Generate textures by screen coords or by object space coords
	bool m_bGentexVScreenSpace; // %gui% Generate textures by screen coords or by object space coords

	unsigned char* globalTexture; // %gui% that takes a file name, I have code that reads the file into this.

	// %gui% or clicks - control texture transformation (rotation in U, V, scaling in U, V, translation in U, V)
	int tex_rotation;
	GLfloat tex_scaleU, tex_scaleV, tex_transU, tex_transV;

	bool s_repeat, t_repeat; // %gui% choose for s, t if to repeat or clamp

	bool m_bUseMipmaps; // %gui%

	void drawAllObjects(); // hw1
	void setProjection();
	void setupLighting(bool firstCall);
	void Init();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(COpenGLView)
	public:
	virtual void OnDraw(CDC* pDC);  // overridden to draw this view
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);

	typedef GLfloat mat16[16];
	static const int MAX_VIEWS = 100;			// must be equal to (int)^2
	mat16 viewMatrix[MAX_VIEWS];


	int numViews;
	int numViewsRows;
	int numViewsCol;
	int numObjects;
	bool isActiveView(){
		return m_bIsActiveView;
	}
	protected:
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~COpenGLView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:
	BOOL InitializeOpenGL();
	BOOL SetupPixelFormat(PIXELFORMATDESCRIPTOR* pPFD = 0); // the '= 0' was added.
	BOOL SetupViewingFrustum(void);
	BOOL SetupViewingOrthoConstAspect(void);
	void COpenGLView::EnableFog (void);

	virtual void RenderScene();


	HGLRC    m_hRC;			// holds the Rendering Context
	CDC*     m_pDC;			// holds the Device Context
	int m_WindowWidth;		// hold the windows width
	int m_WindowHeight;		// hold the windows height
	double m_AspectRatio;		// hold the fixed Aspect Ration

private:
	void draw_axis();


// Generated message map functions
protected:
	//{{AFX_MSG(COpenGLView)
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnDestroy();
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnFileLoad();
	afx_msg void OnViewOrthographic();
	afx_msg void OnUpdateViewOrthographic(CCmdUI* pCmdUI);
	afx_msg void OnViewPerspective();
	afx_msg void OnUpdateViewPerspective(CCmdUI* pCmdUI);
	//hw1 start
	afx_msg void OnViewModelview();
	afx_msg void OnUpdateViewModelview(CCmdUI* pCmdUI);
	afx_msg void OnViewCameraview();
	afx_msg void OnUpdateViewCameraview(CCmdUI* pCmdUI);
	afx_msg void OnMenu();
	//hw1 end
	afx_msg void OnActionRotate();
	afx_msg void OnUpdateActionRotate(CCmdUI* pCmdUI);
	afx_msg void OnActionScale();
	afx_msg void OnUpdateActionScale(CCmdUI* pCmdUI);
	afx_msg void OnActionTranslate();
	afx_msg void OnUpdateActionTranslate(CCmdUI* pCmdUI);
	afx_msg void OnAxisX();
	afx_msg void OnUpdateAxisX(CCmdUI* pCmdUI);
	afx_msg void OnAxisY();
	afx_msg void OnUpdateAxisY(CCmdUI* pCmdUI);
	afx_msg void OnAxisZ();
	afx_msg void OnUpdateAxisZ(CCmdUI* pCmdUI);
	afx_msg void OnLightShadingFlat();
	afx_msg void OnUpdateLightShadingFlat(CCmdUI* pCmdUI);
	afx_msg void OnLightShadingGouraud();
	afx_msg void OnUpdateLightShadingGouraud(CCmdUI* pCmdUI);
	afx_msg void OnLightConstants();

	afx_msg void COpenGLView::Scale(float scaleX, float scaleY, float scaleZ);//hw1
	afx_msg void COpenGLView::Rotate(float angle);		//hw1
	afx_msg void COpenGLView::Translate(int x, int y);	//hw1

	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnLButtonDblClk(UINT nFlags, CPoint point);
	afx_msg BOOL OnMouseWheel(UINT nFlags, short zDelta, CPoint pt);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnViewView1();
	afx_msg void OnUpdateViewView1(CCmdUI* pCmdUI);
	afx_msg void OnViewView2();
	afx_msg void OnUpdateViewView2(CCmdUI* pCmdUI);
	afx_msg void OnViewView3();
	afx_msg void OnUpdateViewView3(CCmdUI* pCmdUI);
	afx_msg void OnViewView4();
	afx_msg void OnUpdateViewView4(CCmdUI* pCmdUI);
	afx_msg void OnViewMultipleviews();
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);

	afx_msg void OnViewPolygonsnormals();
	afx_msg void OnUpdateViewPolygonsnormals(CCmdUI *pCmdUI);
	afx_msg void OnViewVerticesnormals();
	afx_msg void OnUpdateViewVerticesnormals(CCmdUI *pCmdUI);
	afx_msg void OnOptionsMousesensitivity();
	afx_msg void COpenGLView::SetSensFactor();
	afx_msg void OnOptionsPerspectivecontrol();
	afx_msg void OnViewBoundingBox();
	afx_msg void OnUpdateViewBoundingBox(CCmdUI *pCmdUI);
	afx_msg void OnUpdateViewMultipleviews(CCmdUI *pCmdUI);
	afx_msg void OnActionSetcolor();
	afx_msg void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
	afx_msg void OnActionSetbackgroundcolor();
	afx_msg void OnActionResetcolors();
	afx_msg void OnViewMultipleobjects();
	afx_msg void OnUpdateViewMultipleobjects(CCmdUI *pCmdUI);
	afx_msg void OnViewWireframe();
	afx_msg void OnUpdateViewWireframe(CCmdUI *pCmdUI);
	afx_msg void OnViewEnablefog();
	afx_msg void OnViewSetfogparameters();
	afx_msg void OnMaterialSetmaterialparameters();
};
#ifndef _DEBUG  // debug version in OpenGLView.cpp
inline COpenGLDoc* COpenGLView::GetDocument()
   { return (COpenGLDoc*)m_pDocument; }
#endif
