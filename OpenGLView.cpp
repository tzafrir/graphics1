// OpenGLView.cpp : implementation of the COpenGLView class
//
#include "stdafx.h"
#include "OpenGL.h"
#include "GL\glu.h"

#include "OpenGLDoc.h"
#include "OpenGLView.h"

#include <iostream>
using std::cout;
using std::endl;
#include "MaterialDlg.h"
#include "LightDialog.h"
#include "sensitivityDialog.h"
#include "fogDialog.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

#include "PngWrapper.h"
#include "iritSkel.h"


// For Status Bar access
#include "MainFrm.h"

// Use this macro to display text messages in the status bar.
#define STATUS_BAR_TEXT(str) (((CMainFrame*)GetParentFrame())->getStatusBar().SetWindowText(str))

#include <vector>
using std::vector;
#include "hw1parser.h"
#include "sensitivityDialog.h"
#include "perspectiveDialog.h"
#include "multiViewsDialog.h"
#include "vectorDialog.h"

extern vector<Hw1Object*> hw1Objects;
extern void clearHw1Objects();

#ifndef GL_LIGHT_MODEL_COLOR_CONTROL 
#define GL_LIGHT_MODEL_COLOR_CONTROL 0x81F8 
#endif 

#ifndef GL_SINGLE_COLOR 
#define GL_SINGLE_COLOR 0x81F9 
#endif 

#ifndef GL_SEPARATE_SPECULAR_COLOR 
#define GL_SEPARATE_SPECULAR_COLOR 0x81FA 
#endif

// ugly globals;

int g_w, g_h, g_c;
int selectedObject = -1;
bool m_bUseMipmaps;
bool rotateLock = false;

int findSelectedObject(GLint hits, GLuint buffer[]);
/////////////////////////////////////////////////////////////////////////////
// COpenGLView

IMPLEMENT_DYNCREATE(COpenGLView, CView)

BEGIN_MESSAGE_MAP(COpenGLView, CView)
	//{{AFX_MSG_MAP(COpenGLView)
	ON_WM_ERASEBKGND()
	ON_WM_CREATE()
	ON_WM_DESTROY()
	ON_WM_SIZE()
	ON_COMMAND(ID_FILE_LOAD, OnFileLoad)
	ON_COMMAND(ID_VIEW_ORTHOGRAPHIC, OnViewOrthographic)
	ON_UPDATE_COMMAND_UI(ID_VIEW_ORTHOGRAPHIC, OnUpdateViewOrthographic)
	ON_COMMAND(ID_VIEW_PERSPECTIVE, OnViewPerspective)
	ON_UPDATE_COMMAND_UI(ID_VIEW_PERSPECTIVE, OnUpdateViewPerspective)
	//hw1 start
	ON_COMMAND(ID_VIEW_MODELVIEW, &COpenGLView::OnViewModelview)
	ON_UPDATE_COMMAND_UI(ID_VIEW_MODELVIEW, OnUpdateViewModelview)
	ON_COMMAND(ID_VIEW_CAMERAVIEW, &COpenGLView::OnViewCameraview)
	ON_UPDATE_COMMAND_UI(ID_VIEW_CAMERAVIEW, OnUpdateViewCameraview)

	//hw1 end
	ON_COMMAND(ID_ACTION_ROTATE, OnActionRotate)
	ON_UPDATE_COMMAND_UI(ID_ACTION_ROTATE, OnUpdateActionRotate)
	ON_COMMAND(ID_ACTION_SCALE, OnActionScale)
	ON_UPDATE_COMMAND_UI(ID_ACTION_SCALE, OnUpdateActionScale)
	ON_COMMAND(ID_ACTION_TRANSLATE, OnActionTranslate)
	ON_UPDATE_COMMAND_UI(ID_ACTION_TRANSLATE, OnUpdateActionTranslate)
	ON_COMMAND(ID_AXIS_X, OnAxisX)
	ON_UPDATE_COMMAND_UI(ID_AXIS_X, OnUpdateAxisX)
	ON_COMMAND(ID_AXIS_Y, OnAxisY)
	ON_UPDATE_COMMAND_UI(ID_AXIS_Y, OnUpdateAxisY)
	ON_COMMAND(ID_AXIS_Z, OnAxisZ)
	ON_UPDATE_COMMAND_UI(ID_AXIS_Z, OnUpdateAxisZ)
	ON_COMMAND(ID_LIGHT_SHADING_FLAT, OnLightShadingFlat)
	ON_UPDATE_COMMAND_UI(ID_LIGHT_SHADING_FLAT, OnUpdateLightShadingFlat)
	ON_COMMAND(ID_LIGHT_SHADING_GOURAUD, OnLightShadingGouraud)
	ON_UPDATE_COMMAND_UI(ID_LIGHT_SHADING_GOURAUD, OnUpdateLightShadingGouraud)
	ON_COMMAND(ID_LIGHT_CONSTANTS, OnLightConstants)
	//}}AFX_MSG_MAP
	ON_WM_LBUTTONDBLCLK()
	ON_WM_MOUSEWHEEL()
	ON_WM_MOUSEMOVE()
	ON_COMMAND(ID_Menu, &COpenGLView::OnMenu)
	
	ON_COMMAND(ID_VIEW_VIEW1, &COpenGLView::OnViewView1)
	ON_UPDATE_COMMAND_UI(ID_VIEW_VIEW1, OnUpdateViewView1)
	ON_COMMAND(ID_VIEW_VIEW2, &COpenGLView::OnViewView2)
	ON_UPDATE_COMMAND_UI(ID_VIEW_VIEW2, OnUpdateViewView2)
	ON_COMMAND(ID_VIEW_VIEW3, &COpenGLView::OnViewView3)
	ON_UPDATE_COMMAND_UI(ID_VIEW_VIEW3, OnUpdateViewView3)
	ON_COMMAND(ID_VIEW_VIEW4, &COpenGLView::OnViewView4)
	ON_UPDATE_COMMAND_UI(ID_VIEW_VIEW4, OnUpdateViewView4)
	ON_COMMAND(ID_VIEW_MULTIPLEVIEWS, &COpenGLView::OnViewMultipleviews)
	ON_WM_LBUTTONDOWN()
	ON_COMMAND(ID_VIEW_POLYGONSNORMALS, &COpenGLView::OnViewPolygonsnormals)
	ON_UPDATE_COMMAND_UI(ID_VIEW_POLYGONSNORMALS, &COpenGLView::OnUpdateViewPolygonsnormals)
	ON_COMMAND(ID_VIEW_VERTICESNORMALS, &COpenGLView::OnViewVerticesnormals)
	ON_UPDATE_COMMAND_UI(ID_VIEW_VERTICESNORMALS, &COpenGLView::OnUpdateViewVerticesnormals)
	ON_COMMAND(ID_OPTIONS_MOUSESENSITIVITY, &COpenGLView::OnOptionsMousesensitivity)
	ON_COMMAND(ID_OPTIONS_PERSPECTIVECONTROL, &COpenGLView::OnOptionsPerspectivecontrol)
	ON_COMMAND(ID_VIEW_BOUNDING_BOX, &COpenGLView::OnViewBoundingBox)
	ON_UPDATE_COMMAND_UI(ID_VIEW_BOUNDING_BOX, &COpenGLView::OnUpdateViewBoundingBox)
	ON_UPDATE_COMMAND_UI(ID_VIEW_MULTIPLEVIEWS, &COpenGLView::OnUpdateViewMultipleviews)
	ON_COMMAND(ID_ACTION_SETCOLOR, &COpenGLView::OnActionSetcolor)
	ON_WM_KEYDOWN()
	ON_COMMAND(ID_ACTION_SETBACKGROUNDCOLOR, &COpenGLView::OnActionSetbackgroundcolor)
	ON_COMMAND(ID_ACTION_RESETCOLORS, &COpenGLView::OnActionResetcolors)
	ON_COMMAND(ID_VIEW_MULTIPLEOBJECTS, &COpenGLView::OnViewMultipleobjects)
	ON_UPDATE_COMMAND_UI(ID_VIEW_MULTIPLEOBJECTS, &COpenGLView::OnUpdateViewMultipleobjects)
	ON_COMMAND(ID_VIEW_WIREFRAME, &COpenGLView::OnViewWireframe)
	ON_UPDATE_COMMAND_UI(ID_VIEW_WIREFRAME, &COpenGLView::OnUpdateViewWireframe)
	ON_COMMAND(ID_VIEW_ENABLEFOG, &COpenGLView::OnViewEnablefog)
	ON_COMMAND(ID_VIEW_SETFOGPARAMETERS, &COpenGLView::OnViewSetfogparameters)
	ON_COMMAND(ID_MATERIAL_SETMATERIALPARAMETERS, &COpenGLView::OnMaterialSetmaterialparameters)
	ON_UPDATE_COMMAND_UI(ID_VIEW_ENABLEFOG, &COpenGLView::OnUpdateViewEnablefog)
	ON_COMMAND(ID_VIEW_TESSELLATION, &COpenGLView::OnViewTessellation)
	ON_UPDATE_COMMAND_UI(ID_VIEW_TESSELLATION, &COpenGLView::OnUpdateViewTessellation)
	ON_COMMAND(ID_ACTION_SETFOGCOLOR, &COpenGLView::OnActionSetfogcolor)
	ON_COMMAND(ID_ACTION_USEMODELCOLORS, &COpenGLView::OnActionUsemodelcolors)
	ON_UPDATE_COMMAND_UI(ID_ACTION_USEMODELCOLORS, &COpenGLView::OnUpdateActionUsemodelcolors)
	ON_COMMAND(ID_VIEW_CULLBACKFACES, &COpenGLView::OnViewCullbackfaces)
	ON_UPDATE_COMMAND_UI(ID_VIEW_CULLBACKFACES, &COpenGLView::OnUpdateViewCullbackfaces)
	ON_COMMAND(ID_ACTION_TEXTURETRANSFORMATION, &COpenGLView::OnActionTexturetransformation)
	ON_UPDATE_COMMAND_UI(ID_ACTION_TEXTURETRANSFORMATION, &COpenGLView::OnUpdateActionTexturetransformation)
	ON_COMMAND(ID_MATERIAL_GENERATEUVECTOR, &COpenGLView::OnMaterialGenerateuvector)
	ON_COMMAND(ID_MATERIAL_GENERATEVVECTOR, &COpenGLView::OnMaterialGeneratevvector)
	ON_COMMAND(ID_MATERIAL_USEMIPMAP, &COpenGLView::OnMaterialUsemipmap)
	ON_UPDATE_COMMAND_UI(ID_MATERIAL_USEMIPMAP, &COpenGLView::OnUpdateMaterialUsemipmap)
	ON_COMMAND(ID_UTEXTUREFILLING_REPEAT, &COpenGLView::OnUtexturefillingRepeat)
	ON_UPDATE_COMMAND_UI(ID_UTEXTUREFILLING_REPEAT, &COpenGLView::OnUpdateUtexturefillingRepeat)
	ON_COMMAND(ID_MATERIAL_USEUTEXTURE, &COpenGLView::OnMaterialUseutexture)
	ON_UPDATE_COMMAND_UI(ID_MATERIAL_USEUTEXTURE, &COpenGLView::OnUpdateMaterialUseutexture)
	ON_COMMAND(ID_UTEXTUREFILLING_CLAMP, &COpenGLView::OnUtexturefillingClamp)
	ON_UPDATE_COMMAND_UI(ID_UTEXTUREFILLING_CLAMP, &COpenGLView::OnUpdateUtexturefillingClamp)
	ON_COMMAND(ID_VTEXTUREFILLING_REPEAT, &COpenGLView::OnVtexturefillingRepeat)
	ON_UPDATE_COMMAND_UI(ID_VTEXTUREFILLING_REPEAT, &COpenGLView::OnUpdateVtexturefillingRepeat)
	ON_COMMAND(ID_VTEXTUREFILLING_CLAMP, &COpenGLView::OnVtexturefillingClamp)
	ON_UPDATE_COMMAND_UI(ID_VTEXTUREFILLING_CLAMP, &COpenGLView::OnUpdateVtexturefillingClamp)
	ON_COMMAND(ID_MATERIAL_USEVTEXTURE, &COpenGLView::OnMaterialUsevtexture)
	ON_UPDATE_COMMAND_UI(ID_MATERIAL_USEVTEXTURE, &COpenGLView::OnUpdateMaterialUsevtexture)
	ON_COMMAND(ID_UCOORDINATESSPACE_SCREENSPACE, &COpenGLView::OnUcoordinatesspaceScreenspace)
	ON_UPDATE_COMMAND_UI(ID_UCOORDINATESSPACE_SCREENSPACE, &COpenGLView::OnUpdateUcoordinatesspaceScreenspace)
	ON_COMMAND(ID_UCOORDINATESSPACE_MODELSPACE, &COpenGLView::OnUcoordinatesspaceModelspace)
	ON_UPDATE_COMMAND_UI(ID_UCOORDINATESSPACE_MODELSPACE, &COpenGLView::OnUpdateUcoordinatesspaceModelspace)
	ON_COMMAND(ID_VCOORDINATESSPACE_SCREENSPACE, &COpenGLView::OnVcoordinatesspaceScreenspace)
	ON_UPDATE_COMMAND_UI(ID_VCOORDINATESSPACE_SCREENSPACE, &COpenGLView::OnUpdateVcoordinatesspaceScreenspace)
	ON_COMMAND(ID_VCOORDINATESSPACE_MODELSPACE, &COpenGLView::OnVcoordinatesspaceModelspace)
	ON_UPDATE_COMMAND_UI(ID_VCOORDINATESSPACE_MODELSPACE, &COpenGLView::OnUpdateVcoordinatesspaceModelspace)
	ON_COMMAND(ID_MATERIAL_SELECTOBJECTFORMIPMAPPING, &COpenGLView::OnMaterialSelectobjectformipmapping)
	ON_COMMAND(ID_MATERIAL_SELECTOBJECT, &COpenGLView::OnMaterialSelectobject)
	ON_COMMAND(ID_FILE_LOADGLOBALTEXTURE, &COpenGLView::OnFileLoadglobaltexture)
	END_MESSAGE_MAP()


// A patch to fix GLaux disappearance from VS2005 to VS2008
void auxSolidCone(GLdouble radius, GLdouble height) {
        GLUquadric *quad = gluNewQuadric();
        gluQuadricDrawStyle(quad, GLU_FILL);
        gluCylinder(quad, radius, 0.0, height, 20, 20);
        gluDeleteQuadric(quad);
}

/////////////////////////////////////////////////////////////////////////////
// COpenGLView construction/destruction

double COpenGLView::zoomRatioDefault = 0.6;

COpenGLView::COpenGLView() : globalTexture(NULL)
{
	Init(true);
}

void COpenGLView::Init(bool first) {
	// Set default values
	m_nAxis = ID_AXIS_X;
	m_nAction = ID_ACTION_ROTATE;
	m_bTransformTexture = false;
	m_nView = ID_VIEW_ORTHOGRAPHIC;	
	m_bIsPerspective = false;

	m_nLightShading = ID_LIGHT_SHADING_FLAT;

	m_lMaterialAmbient = 0.2;
	m_lMaterialDiffuse = 0.8;
	m_lMaterialSpecular = 1.0;
	m_nMaterialShininessFactor = 32;

	//init the first light to be enabled
	m_lights[LIGHT_ID_1].enabled=true;

	m_lZoomRatio = (GLfloat)zoomRatioDefault; // hw1 zoom ratio
	m_lPerspectiveLeft = m_lPerspectiveRight = 
		m_lPerspectiveTop = m_lPerspectiveBottom = perspectiveDialog::PERS_DEFAULT;
	lastClicked.SetPoint(0,0);	//hw1
	mouseSensitivity = sensitivityDialog::SENS_DEFAULT;
	// FOG PARAMETERS
	m_fogEnabled = false;
	density = fogDialog::DENSITY_DEF;
	fogColor[0] = 0.5 ;//fogDialog::FOG_COLOR_R_DEF;
	fogColor[1] = 0.5 ;//fogDialog::FOG_COLOR_G_DEF;
	fogColor[2] = 0.5 ;//fogDialog::FOG_COLOR_B_DEF;
	fogColor[3] = 1 ;//fogDialog::FOG_COLOR_A_DEF;
	fogStart = fogDialog::FOG_START_DEF;
	fogEnd = fogDialog::FOG_END_DEF;
	fogMode = fogDialog::FOG_MODE_DEF;
	fogQuality = fogDialog::FOG_QUALITY_DEF;
			// FOG PARAMETERS END
	m_bShowNormals = false;
	m_bDrawVertexNormals = false;
	if (first) {
	m_bMayDraw = false; // Wait until size and center of object is calculated
	}
	m_bTessellation = false;
	m_bDrawBoundingBox = false;
	m_lNormalScale = 1.0;
	nSpace = ID_SPACE_SCREEN;	//hw1
	m_lCenterX = m_lCenterY = m_lCenterZ = 1.0;
	m_lColorR = m_lColorG = m_lColorB = 0.0;
	m_backColorR = m_backColorG = m_backColorB = 0.0;
	m_activeColorR = m_activeColorG = m_activeColorB = 0.5;
	m_lPerspectiveLeft = 
		m_lPerspectiveRight = 
			m_lPerspectiveTop = 
				m_lPerspectiveBottom =
					m_lPerspectiveBottom = perspectiveDialog::PERS_DEFAULT;
	
	m_lPerspectiveDVal = perspectiveDialog::PERS_DEFAULT_D;
	
	m_bChoseColor = false;
	m_backChoseColor = false;
	m_lTotalSize = 1.0;
	multipleViews = false;
	multipleObjects = false;
	numViews = 1;
	numObjects = 1;
	numViewsRows = numViewsCol = (int)sqrt(double(numViews));
	activeView = 0;
	
	for (int i=0 ; i<MAX_VIEWS ; i++){
		for (int k=0 ; k<16 ; k++){
			viewMatrix[i][k] = (k%5 == 0);
		}
	}

	LightParams &dl = m_lights[0];
	dl.posX = dl.posY = dl.posZ = 3.0;
	dl.type = LIGHT_TYPE_POINT;
	for (int i = 1; i < 8; i++) {
		LightParams &lt = m_lights[i];
		lt.enabled = false;
		lt.posX = lt.posY = lt.posZ = 0.0;
		lt.dirX = lt.dirY = lt.dirZ = 0.0;
	}

	m_nLightShading = ID_LIGHT_SHADING_GOURAUD;

	m_bUseModelColors = true;
	m_bDrawWireframe = false;
	m_bCullBackFaces = false;
	
	texGenU[0] = 1.0;
	texGenU[1] = 0.0;
	texGenU[2] = 0.0;
	texGenU[3] = 1.0;

	texGenV[0] = 0.0;
	texGenV[1] = -1.0;
	texGenV[2] = 0.0;
	texGenV[3] = 1.0;

	m_bGenerateTexturesU = false;
	m_bGenerateTexturesV = false;
	m_bGentexUScreenSpace = m_bGentexVScreenSpace = false;

	tex_rotation = 0;
	tex_scaleU = tex_scaleV = 1.0;
	tex_transU = tex_transV = .0;

	s_repeat = true;
	t_repeat = true;

	m_bUseMipmaps = true;
	m_bUserCanSelectAnObject = false;
	m_bObjectWasSelected = true;
	selectX = 0;
	selectY = 0;
	m_bSelectingForMipmapping = false;
}

COpenGLView::~COpenGLView()
{
	clearHw1Objects();
}


/////////////////////////////////////////////////////////////////////////////
// COpenGLView diagnostics

#ifdef _DEBUG
void COpenGLView::AssertValid() const
{
	CView::AssertValid();
}

void COpenGLView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

COpenGLDoc* COpenGLView::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(COpenGLDoc)));
	return (COpenGLDoc*)m_pDocument;
}
#endif //_DEBUG


/////////////////////////////////////////////////////////////////////////////
// COpenGLView Window Creation - Linkage of windows to OpenGL

BOOL COpenGLView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	// An OpenGL window must be created with the following
	// flags and must NOT include CS_PARENTDC for the
	// class style.

	cs.style |= WS_CLIPSIBLINGS | WS_CLIPCHILDREN;

	return CView::PreCreateWindow(cs);
}



int COpenGLView::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
	if (CView::OnCreate(lpCreateStruct) == -1)
		return -1;

	InitializeOpenGL();

	return 0;
}


// This method initialized the OpenGL system.
BOOL COpenGLView::InitializeOpenGL()
{
	m_pDC = new CClientDC(this);

	if ( NULL == m_pDC ) { // failure to get DC
		::AfxMessageBox("Couldn't get a valid DC.");
		return FALSE;
	}

	if ( !SetupPixelFormat() ) {
		::AfxMessageBox("SetupPixelFormat failed.\n");
		return FALSE;
	}

	if ( 0 == (m_hRC = ::wglCreateContext( m_pDC->GetSafeHdc() ) ) ) {
		::AfxMessageBox("wglCreateContext failed.");
		return FALSE;
	}

	if ( FALSE == ::wglMakeCurrent( m_pDC->GetSafeHdc(), m_hRC ) ) {
		::AfxMessageBox("wglMakeCurrent failed.");
		return FALSE;
	}

	// specify black as clear color
	::glClearColor( 0.0f, 0.0f, 0.0f, 0.0f );
	// specify the back of the buffer as clear depth (0 closest, 1 farmost)
	::glClearDepth( 1.0f );
	// enable depth testing (Enable zbuffer - hidden surface removal)
	::glEnable( GL_DEPTH_TEST );
	// Set default black as background color.
	::glClearColor(0.0, 0.0, 0.0, 1.0f);

	return TRUE;
}



BOOL COpenGLView::SetupPixelFormat(PIXELFORMATDESCRIPTOR* pPFD)
{
	// default pixel format for a single-buffered,
	// OpenGL-supporting, hardware-accelerated, 
	// RGBA-mode format. Pass in a pointer to a different
	// pixel format if you want something else
	PIXELFORMATDESCRIPTOR pfd = {
		sizeof(PIXELFORMATDESCRIPTOR),// size of this pfd
		1,                      // version number
		PFD_DRAW_TO_WINDOW |    // support window
		PFD_SUPPORT_OPENGL |  // support OpenGL
		PFD_DOUBLEBUFFER,     // double buffered
		PFD_TYPE_RGBA,          // RGBA type
		24,                     // 24-bit color depth
		0, 0, 0, 0, 0, 0,       // color bits ignored
		0,                      // no alpha buffer
		0,                      // shift bit ignored
		0,                      // no accumulation buffer
		0, 0, 0, 0,             // accum bits ignored
		16,                     // 16-bit z-buffer
		0,                      // no stencil buffer
		0,                      // no auxiliary buffer
		PFD_MAIN_PLANE,         // main layer
		0,                      // reserved
		0, 0, 0                 // layer masks ignored
	};

	int pixelformat;
	PIXELFORMATDESCRIPTOR* pPFDtoUse;

	// let the user override the default pixel format
	pPFDtoUse = (0 == pPFD)? &pfd : pPFD; 

	if ( 0 == (pixelformat = ::ChoosePixelFormat( m_pDC->GetSafeHdc(), pPFDtoUse )) ) {
		::AfxMessageBox("ChoosePixelFormat failed.");
		return FALSE;
	}

	if ( FALSE == ::SetPixelFormat(m_pDC->GetSafeHdc(), pixelformat, pPFDtoUse ) ) {
		::AfxMessageBox("SetPixelFormat failed.");
		return FALSE;
	}

	return TRUE;
}



/////////////////////////////////////////////////////////////////////////////
// COpenGLView message handlers


void COpenGLView::OnSize(UINT nType, int cx, int cy) 
{
	CView::OnSize(nType, cx, cy);

	if ( 0 >= cx || 0 >= cy ) {
		return;
	}

	// save the width and height of the current window
	m_WindowWidth = cx;
	m_WindowHeight = cy;

	// compute the aspect ratio
	// this will keep all dimension scales equal
	m_AspectRatio = (GLdouble)m_WindowWidth/(GLdouble)m_WindowHeight;

	// Now, set up the viewing area-select the full client area
	::glViewport(0, 0, m_WindowWidth, m_WindowHeight);

	if ( GL_NO_ERROR != ::glGetError() ) {
		::AfxMessageBox("Error while trying to set viewport.");
	}

	// select the projection matrix as the recipient of
	// matrix operations (there's three to choose from)
	::glMatrixMode(GL_PROJECTION);
	// initialize the projection matrix to a pristine state
	::glLoadIdentity();

	// select the viewing volume. You do it after you
	// get the aspect ratio and set the viewport
	//SetupViewingFrustum( );
	//SetupViewingOrthoConstAspect();
	

	// now select the modelview matrix and clear it
	// this is the mode we do most of our calculations in
	// so we leave it as the default mode.
	::glMatrixMode(GL_MODELVIEW);

	// hw1: commented out to preserve state between resizes
	//::glLoadIdentity();
}


BOOL COpenGLView::SetupViewingFrustum(void)
{
	double windowSize = 4.0;
	// select a default perspective viewing volumn
	//::gluPerspective( 40.0f, m_AspectRatio, 1.0, 256.0);
	
	double r = (m_lZoomRatio/m_lTotalSize);
	double q = r * m_AspectRatio;
	double zFactor = m_lPerspectiveDVal/perspectiveDialog::PERS_DEFAULT_D;
	glFrustum(-q*m_lPerspectiveLeft, q*m_lPerspectiveRight,
				-r*m_lPerspectiveBottom, r*m_lPerspectiveTop, 
				1.0*zFactor+m_lCenterZ, 10*1.2*m_lTotalSize*zFactor+m_lCenterZ);					//test

	// NOTE: Other commands you could have here are
	// glFrustum, which gives you much more control over
	// the perspective view, or glOrtho which is used for
	// parallel projections. No matter what you use, check
	// the error status when you set the viewing frustum!

	if ( GL_NO_ERROR != ::glGetError() ) {
		::AfxMessageBox("Error while trying to set viewing frustum.");
		return FALSE;
	}

	return TRUE;
}


// This viewing projection gives us a constant aspect ration. This is done by
// increasing the corresponding size of the ortho cube.
BOOL COpenGLView::SetupViewingOrthoConstAspect(void)
{
	double windowSize = 4.0;	// the size of the window in GL coord system.


	if ( m_AspectRatio > 1 ) {	// x is bigger than y.
		// Maintain y size and increase x size (and z) accordingly
		// by MULTIPLYING by the aspect ration.
		::glOrtho(  -windowSize*m_AspectRatio/2.0, windowSize*m_AspectRatio/2.0,
			-windowSize/2.0, windowSize/2.0,
			-windowSize*m_AspectRatio*2.0, windowSize*m_AspectRatio*20.0);
	} else {
		// Maintain x size and increase y size (and z) accordingly, 
		// by DIVIDING the aspect Ration (because it's smaller than 1).
		::glOrtho(  -windowSize/2.0, windowSize/2.0,
			-windowSize/m_AspectRatio/2.0, windowSize/m_AspectRatio/2.0,
			-windowSize/m_AspectRatio*2.0, windowSize/m_AspectRatio*2.0);
	}

	if ( GL_NO_ERROR != ::glGetError() ) {
		::AfxMessageBox("Error while trying to set viewing OrthoConst.");
		return FALSE;
	}

	return TRUE;
}

void COpenGLView::EnableFog (void) {
	glEnable (GL_DEPTH_TEST); //enable the depth testing

	glEnable (GL_FOG); //enable the fog

	glFogf (GL_FOG_START,fogStart);

	glFogf (GL_FOG_END,fogEnd);

	glFogi (GL_FOG_MODE, fogModeConvert(fogMode)); //set the fog mode to GL_EXP2

	glFogfv (GL_FOG_COLOR, fogColor); //set the fog color to our color chosen above

	glFogf (GL_FOG_DENSITY, density/100); //set the density to the value above
	
	glHint (GL_FOG_HINT, fogQulityConvert(fogQuality)); // GL_NICEST, GL_FASTEST, GL_DONT_CARE
}

int COpenGLView::fogQulityConvert(int fogQuality){
	
	switch (fogQuality){
		case fogDialog::HIGH_QUALITY:	return GL_NICEST;
		case fogDialog::FAST_RENDERING:	return GL_FASTEST;
		case fogDialog::SW_CHOOSE:		return GL_DONT_CARE;
	}
	return -1;
}

int COpenGLView::fogModeConvert(int fogMode){
	
	switch (fogMode){
		case fogDialog::MODE_LINEAR:return GL_LINEAR;
		case fogDialog::MODE_EXP:	return GL_EXP;
		case fogDialog::MODE_EXP2:	return GL_EXP2;
	}
	return -1;
}


BOOL COpenGLView::OnEraseBkgnd(CDC* pDC) 
{
	// Windows will clear the window with the background color every time your window 
	// is redrawn, and then OpenGL will clear the viewport with its own background color.

	// return CView::OnEraseBkgnd(pDC);
	return true;
}


/////////////////////////////////////////////////////////////////////////////
// COpenGLView drawing
/////////////////////////////////////////////////////////////////////////////


void COpenGLView::OnDraw(CDC* pDC)
{
	COpenGLDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);		// clear screen and zbuffer

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	setProjection();
	glMatrixMode(GL_MODELVIEW);
	setupLighting(true);
	glPushMatrix();
	if (m_backChoseColor){
		glClearColor((GLclampf)m_backColorR/255, (GLclampf)m_backColorG/255, (GLclampf)m_backColorB/255, 0.0);
	}else{
		glClearColor(0.0, 0.0, 0.0, 0.0);
	}
	if (m_fogEnabled)
		EnableFog();
	else 
		glDisable(GL_FOG);
	//draw_axis();

	if (m_bDrawWireframe) {
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	} else {
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	}

	if (m_bCullBackFaces) {
		glEnable(GL_CULL_FACE);
	}else{
		glDisable(GL_CULL_FACE);
	}

	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
	if (m_bGenerateTexturesU) {
		int mode1 = m_bGentexUScreenSpace ? GL_EYE_LINEAR : GL_OBJECT_LINEAR;
		int mode2 = m_bGentexUScreenSpace ? GL_EYE_PLANE : GL_OBJECT_PLANE;
		glTexGenf(GL_S, GL_TEXTURE_GEN_MODE, (GLfloat)mode1);
		glTexGenfv(GL_S, mode2, texGenU);
		glEnable(GL_TEXTURE_GEN_S);
	} else {
		glDisable(GL_TEXTURE_GEN_S);
	}

	if (m_bGenerateTexturesV) {
		int mode1 = m_bGentexVScreenSpace ? GL_EYE_LINEAR : GL_OBJECT_LINEAR;
		int mode2 = m_bGentexVScreenSpace ? GL_EYE_PLANE : GL_OBJECT_PLANE;
		glTexGenf(GL_T, GL_TEXTURE_GEN_MODE, (GLfloat)mode1);
		glTexGenfv(GL_T, mode2, texGenV);
		glEnable(GL_TEXTURE_GEN_T);
	} else {
		glDisable(GL_TEXTURE_GEN_T);
	}

	int s_mode = s_repeat ? GL_REPEAT : GL_CLAMP;
	int t_mode = t_repeat ? GL_REPEAT : GL_CLAMP;
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, (GLfloat)s_mode);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, (GLfloat)t_mode);

	glMatrixMode(GL_TEXTURE);
	glLoadIdentity();
	glPushMatrix();
	glRotatef(tex_rotation, 0.0, 0.0, 1.0);
	glScalef(tex_scaleU, tex_scaleV, 0.0);
	glTranslatef(tex_transU, tex_transV, 0.0);
	glMatrixMode(GL_MODELVIEW);

	// Selection - before rendering:
	static const int SELECT_BUF_SIZE = 1024;
	GLuint selected[SELECT_BUF_SIZE];

	if (m_bObjectWasSelected) {
		glSelectBuffer(SELECT_BUF_SIZE, selected);
		glRenderMode(GL_SELECT);
		glInitNames();
		glMatrixMode(GL_PROJECTION);
		glPushMatrix();
		glLoadIdentity();
		static const double radius = 10.0;
		GLint viewport[4];
		glGetIntegerv(GL_VIEWPORT, viewport);
		gluPickMatrix(selectX, selectY, radius, radius, viewport);
		setProjection();
		glMatrixMode(GL_MODELVIEW);
	}

	for (int  i=0; i<numViewsCol ;i++){
		for (int j=0 ; j<numViewsRows ; j++){
			for(int k=0 ; k<numObjects ; k++){
				glLoadIdentity();	
				// load the view matrix and draw it
				if (m_bIsPerspective) {
					glTranslatef(0.0, 0.0, -m_lPerspectiveDVal*m_lTotalSize);	//test
				}
				if (multipleObjects){
					GLfloat scale = (GLfloat)sqrt(m_lTotalSize)/2/numObjects;
					glScalef(scale, scale, scale);
					GLfloat trans = (GLfloat)((k-numObjects/2+0.5)*0.5*m_lTotalSize);
					glTranslatef(trans, trans, trans);
				}
				
				if (multipleObjects){	// multiple objects
					glMultMatrixf(viewMatrix[k]);
					::glViewport(0, 0, m_WindowWidth, m_WindowHeight);
				}else{					//multipleviews
					glMultMatrixf(viewMatrix[numViewsRows*i+j]);
					::glViewport(0+i*m_WindowWidth/numViewsCol, 0+j*m_WindowHeight/numViewsRows, 
										m_WindowWidth/numViewsCol, m_WindowHeight/numViewsRows);
				}
				// scale acording to the size of the object
				float scale = (GLfloat)3.0/m_lTotalSize;
				glScalef(scale, scale, scale);
				glTranslatef(-m_lCenterX, -m_lCenterY, -m_lCenterZ);
				setupLighting(false);
				drawAllObjects();
			}
		}
	}

	glPopMatrix();

	if (m_bObjectWasSelected) {
		glMatrixMode(GL_PROJECTION);
		glPopMatrix();
		glMatrixMode(GL_MODELVIEW);
		glFlush();

		int hits = glRenderMode(GL_RENDER);
		int name = findSelectedObject(hits, selected);
		// Add a breakpoint here and check that name != -1

		if (m_bSelectingForMipmapping) {
			for (vector<Hw1Object*>::iterator it = hw1Objects.begin(); it != hw1Objects.end(); ++it) {
				Hw1Object *o = *it;
				if (o->name == name) {
					o->hasMipmaps = !o->hasMipmaps;
					break;
				}
			}
			m_bSelectingForMipmapping = false;
		} else {
			selectedObject = name;
		}
		m_bObjectWasSelected = false;
		
		Invalidate();
	}

	glMatrixMode(GL_TEXTURE);
	glPopMatrix();
	glMatrixMode(GL_MODELVIEW);
	RenderScene();


	glFlush();
	SwapBuffers(wglGetCurrentDC());
}


/////////////////////////////////////////////////////////////////////////////
// COpenGLView OpenGL Finishing and clearing...

void COpenGLView::OnDestroy() 
{
	CView::OnDestroy();

	// this call makes the current RC not current
	if ( FALSE ==  ::wglMakeCurrent( 0, 0 ) ) {
		::AfxMessageBox("wglMakeCurrent failed.");
	}

	// delete the RC
	if ( m_hRC && (FALSE == ::wglDeleteContext( m_hRC )) ) {
		::AfxMessageBox("wglDeleteContext failed.");
	}

	// delete the DC
	if ( m_pDC ) {
		delete m_pDC;
	}
}



/////////////////////////////////////////////////////////////////////////////
// User Defined Functions


void COpenGLView::draw_axis()
{
	glLineWidth(2.0f);
	glColor3f(1.0f, 1.0f, 1.0f);
	
	const GLfloat NUM_OBJ = 9;
	// Draw Axis x
	glPushMatrix();
	for(double i = 0 ; i <= NUM_OBJ ; i++){
		glColor3f((GLfloat)(1-i/NUM_OBJ), 0, (GLfloat)(i/NUM_OBJ));
		glBegin(GL_TRIANGLES);
			glVertex3d(-0.1,0,0);
			glVertex3d(   1,0,0);
			glVertex3d(   1,0.1,0);
		glEnd();
		glRotated( 10, 0.0f, 0.0f, 1.0f );
	}
	glPopMatrix();

	glColor3f(0, 1, 0);
	glBegin(GL_LINES);
	glVertex3d(0,0,0);
	glVertex3d(0,   10,0);
	glEnd();
	glPushMatrix();
	glTranslatef( 0.0f, 1.0f, 0.0f );
	glRotatef( -90.0, 1.0f, 0.0f, 0.0f );
	auxSolidCone(0.05,0.5);
	glPopMatrix();


	glColor3f(0, 0, 1);
	glBegin(GL_LINES);
	glVertex3d(0,0,-0.1);
	glVertex3d(0,0,   1);
	glEnd();
	glPushMatrix();
	glTranslatef( 0.0f, 0.0f, 1.0f );
	auxSolidCone(0.05,0.5);
	glPopMatrix();

	glLineWidth(1);			// return defaul line width


	glColor3f(1,1,1);		// return default color
}


void COpenGLView::RenderScene() {
	// do nothing. This is supposed to be overriden...

	return;
}

typedef struct texture_ {
	unsigned char *bmp;
	int w, h, c;
} texture;

void COpenGLView::OnFileLoad() 
{
	rotateLock = true;
	TCHAR szFilters[] = _T ("IRIT Data Files (*.itd)|*.itd|All Files (*.*)|*.*||");

	CFileDialog dlg(TRUE, "itd", "*.itd", OFN_FILEMUSTEXIST | OFN_HIDEREADONLY ,szFilters);

	if (dlg.DoModal () == IDOK) {
		m_strItdFileName = dlg.GetPathName();		// Full path and filename
		
		m_bMayDraw = false;
		CGSkelProcessIritDataFiles(m_strItdFileName, 1);
		// Open the file and read it.

		// Reset stuff;
		OnMenu();

		double minX, minY, minZ, maxX, maxY, maxZ;
		bool setMinMax = false;
		for (vector<Hw1Object*>::iterator it = hw1Objects.begin();
				it != hw1Objects.end();
				++it) {
			Hw1Object* o = *it;
			if (o->hasTex) {
			  o->loadTexture();
			}
			if (!setMinMax) {
				minX = o->getMinX();
				maxX = o->getMaxX();
				minY = o->getMinY();
				maxY = o->getMaxY();
				minZ = o->getMinZ();
				maxZ = o->getMaxZ();
				setMinMax = true;
			} else {
				minX = min(minX, o->getMinX());
				minY = min(minY, o->getMinY());
				minZ = min(minZ, o->getMinZ());
				maxX = max(maxX, o->getMaxX());
				maxY = max(maxY, o->getMaxY());
				maxZ = max(maxZ, o->getMaxZ());
			}
		}
		m_lCenterX = (GLfloat)((minX + maxX) / 2.0);
		m_lCenterY = (GLfloat)((minY + maxY) / 2.0);
		m_lCenterZ = (GLfloat)((minZ + maxZ) / 2.0);
		
		// Calculate absolute size:
		double x = m_lCenterX - minX;
		double y = m_lCenterY - minY;
		double z = m_lCenterZ - minZ;
		m_lTotalSize = (GLfloat)sqrt(x*x + y*y + z*z);
		mouseSensitivity = sensitivityDialog::SENS_DEFAULT;
		m_bMayDraw = true;

		Invalidate();	// force a WM_PAINT for drawing.
	} 

}


void loadMipmap(string basename, texture* tex) {
	for (int i = 0; i < 6; i++) {
		texture &t = tex[i];
		char c = 'a' + i;
		string fullname = basename + "_" + c + ".png";
		PngWrapper p(fullname.c_str());
		if (!p.ReadPng()) {
			string msg = "Unable to read png file";
			AfxMessageBox(msg.c_str());
			throw 0;
		}
		t.w = p.GetWidth();
		t.h = p.GetHeight();
		t.c = p.GetNumChannels();
		t.bmp = new unsigned char[t.w*t.h*t.c];
		int curPixel = 0;
		for (int _h = 0; _h < t.h; _h++) {
			for (int _w = 0; _w < t.w; _w++) {
				int pixel = p.GetValue(_w, _h);
				if (1 == t.c) {
					t.bmp[curPixel++] = pixel;
					t.bmp[curPixel++] = pixel;
					t.bmp[curPixel++] = pixel;
					continue;
				}
				t.bmp[curPixel++] = GET_R(pixel);
				t.bmp[curPixel++] = GET_G(pixel);
				t.bmp[curPixel++] = GET_B(pixel);
				if (4 == t.c) {
					t.bmp[curPixel++] = GET_A(pixel);
				}
			}
		}
	}
}


// VIEW HANDLERS ///////////////////////////////////////////

// Note: that all the following Message Handlers act in a similar way.
// Each control or command has two functions associated with it.

void COpenGLView::OnViewOrthographic() 
{
	m_nView = ID_VIEW_ORTHOGRAPHIC;
	m_bIsPerspective = false;
	Invalidate();		// redraw using the new view.
}

void COpenGLView::OnUpdateViewOrthographic(CCmdUI* pCmdUI) 
{
	pCmdUI->SetCheck(m_nView == ID_VIEW_ORTHOGRAPHIC);
}

void COpenGLView::OnViewPerspective() 
{
	m_nView = ID_VIEW_PERSPECTIVE;
	m_bIsPerspective = true;
	Invalidate();
}

void COpenGLView::OnUpdateViewPerspective(CCmdUI* pCmdUI) 
{
	pCmdUI->SetCheck(m_nView == ID_VIEW_PERSPECTIVE);
}

void COpenGLView::OnViewModelview()
{
	nSpace = ID_SPACE_OBJECT;
}

void COpenGLView::OnUpdateViewModelview(CCmdUI* pCmdUI) 
{
	pCmdUI->SetCheck(nSpace == ID_SPACE_OBJECT);
}

void COpenGLView::OnViewCameraview()
{
	nSpace = ID_SPACE_SCREEN;
}

void COpenGLView::OnUpdateViewCameraview(CCmdUI* pCmdUI) 
{
	pCmdUI->SetCheck(nSpace == ID_SPACE_SCREEN);
}




// ACTION HANDLERS ///////////////////////////////////////////


// TODO: rename this
void COpenGLView::OnMenu()
{

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();


	for (int i=0 ; i<MAX_VIEWS ; i++){
		for (int k=0 ; k<16 ; k++){
			viewMatrix[i][k] = (k%5 == 0);
		}
	}
	
	Hw1Polygon::normalScale = Hw1Polygon::normalScaleDefault;
	m_lZoomRatio = (GLfloat)zoomRatioDefault;
	m_lPerspectiveLeft = 
		m_lPerspectiveRight = 
			m_lPerspectiveTop = 
				m_lPerspectiveBottom =
					m_lPerspectiveBottom = perspectiveDialog::PERS_DEFAULT;
	m_lPerspectiveDVal = perspectiveDialog::PERS_DEFAULT_D;
	m_bChoseColor = false;
	m_backChoseColor = false;

	SetSensFactor();

	LightParams &dl = m_lights[0];
	dl.posX = dl.posY = dl.posZ = 3.0;
	dl.type = LIGHT_TYPE_POINT;
	for (int i = 1; i < 8; i++) {
		LightParams &lt = m_lights[i];
		lt.enabled = false;
		lt.posX = lt.posY = lt.posZ = 0.0;
		lt.dirX = lt.dirY = lt.dirZ = 0.0;
	}

	m_nLightShading = ID_LIGHT_SHADING_GOURAUD;

	m_bUseModelColors = true;
	m_bDrawWireframe = false;
	m_bCullBackFaces = false;
	
	texGenU[0] = 1.0;
	texGenU[1] = 0.0;
	texGenU[2] = 0.0;
	texGenU[3] = 1.0;

	texGenV[0] = 0.0;
	texGenV[1] = -1.0;
	texGenV[2] = 0.0;
	texGenV[3] = 1.0;

	m_bGenerateTexturesU = false;
	m_bGenerateTexturesV = false;
	m_bGentexUScreenSpace = m_bGentexVScreenSpace = false;

	tex_rotation = 0;
	tex_scaleU = tex_scaleV = 1.0;
	tex_transU = tex_transV = .0;

	s_repeat = true;
	t_repeat = true;

	m_bUseMipmaps = true;
	m_bUserCanSelectAnObject = false;
	m_bObjectWasSelected = true;
	selectX = 0;
	selectY = 0;
	m_bSelectingForMipmapping = false;

	if (globalTexture) {
		delete globalTexture;
		globalTexture = NULL;
	}

	Invalidate();
}

void COpenGLView::OnActionRotate() 
{
	m_nAction = ID_ACTION_ROTATE;
}

void COpenGLView::OnUpdateActionRotate(CCmdUI* pCmdUI) 
{
	pCmdUI->SetCheck(m_nAction == ID_ACTION_ROTATE);
}

void COpenGLView::OnActionTranslate() 
{
	m_nAction = ID_ACTION_TRANSLATE;
}

void COpenGLView::OnUpdateActionTranslate(CCmdUI* pCmdUI) 
{
	pCmdUI->SetCheck(m_nAction == ID_ACTION_TRANSLATE);
}

void COpenGLView::OnActionScale() 
{
	m_nAction = ID_ACTION_SCALE;
}

void COpenGLView::OnUpdateActionScale(CCmdUI* pCmdUI) 
{
	pCmdUI->SetCheck(m_nAction == ID_ACTION_SCALE);
}




// AXIS HANDLERS ///////////////////////////////////////////


// Gets calles when the X button is pressed or when the Axis->X menu is selected.
// The only thing we do here is set the ChildView member variable m_nAxis to the 
// selected axis.
void COpenGLView::OnAxisX() 
{
	m_nAxis = ID_AXIS_X;
}

// Gets called when windows has to repaint either the X button or the Axis pop up menu.
// The control is responsible for its redrawing.
// It sets itself disabled when the action is a Scale action.
// It sets itself Checked if the current axis is the X axis.
void COpenGLView::OnUpdateAxisX(CCmdUI* pCmdUI) 
{
	pCmdUI->SetCheck(m_nAxis == ID_AXIS_X);
}


void COpenGLView::OnAxisY() 
{
	m_nAxis = ID_AXIS_Y;
}

void COpenGLView::OnUpdateAxisY(CCmdUI* pCmdUI) 
{
	pCmdUI->SetCheck(m_nAxis == ID_AXIS_Y);
}


void COpenGLView::OnAxisZ() 
{
	m_nAxis = ID_AXIS_Z;
}

void COpenGLView::OnUpdateAxisZ(CCmdUI* pCmdUI) 
{
	pCmdUI->SetCheck(m_nAxis == ID_AXIS_Z);
}





// OPTIONS HANDLERS ///////////////////////////////////////////




// LIGHT SHADING HANDLERS ///////////////////////////////////////////

void COpenGLView::OnLightShadingFlat() 
{
	m_nLightShading = ID_LIGHT_SHADING_FLAT;
}

void COpenGLView::OnUpdateLightShadingFlat(CCmdUI* pCmdUI) 
{
	pCmdUI->SetCheck(m_nLightShading == ID_LIGHT_SHADING_FLAT);
}


void COpenGLView::OnLightShadingGouraud() 
{
	m_nLightShading = ID_LIGHT_SHADING_GOURAUD;
}

void COpenGLView::OnUpdateLightShadingGouraud(CCmdUI* pCmdUI) 
{
	pCmdUI->SetCheck(m_nLightShading == ID_LIGHT_SHADING_GOURAUD);
}

// LIGHT SETUP HANDLER ///////////////////////////////////////////

void COpenGLView::OnLightConstants() 
{
	CLightDialog dlg;

	for (int id=LIGHT_ID_1;id<MAX_LIGHT;id++)
	{	    
	    dlg.SetDialogData((LightID)id,m_lights[id]);
	}
	dlg.SetDialogData(LIGHT_ID_AMBIENT,m_ambientLight);

	if (dlg.DoModal() == IDOK) 
	{
	    for (int id=LIGHT_ID_1;id<MAX_LIGHT;id++)
	    {
		m_lights[id] = dlg.GetDialogData((LightID)id);
	    }
	    m_ambientLight = dlg.GetDialogData(LIGHT_ID_AMBIENT);
	}	
	Invalidate();
}

// Drawing code for our objects ///////////////////////////////////

double Hw1Polygon::normalScaleDefault = 1.0;
double Hw1Polygon::normalScale = 1.0;
double Hw1Polygon::sizeNormalizeFactor = 0.2;

void Hw1Object::draw(bool shouldDrawBoundingBox, bool useTessellation,
						bool hasColor, double cR, double cG, double cB,
							unsigned char *tex) {
	if (hasColor) {
		// color is an integer in 0-255 range. glColor3fparams are 0.0-1.0 doubles
		glColor3f(cR/255, cG/255, cB/255);
	} else {
		glColor3f(colorR, colorG, colorB);
	}
	if (tex != NULL) {
		c = g_c;
		h = g_h;
		w = g_w;
	}
	if (hasTex || (tex && polygons->at(0)->vertices->at(0)->hasUV)) {
		glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
		GLenum format = (c == 4) ? GL_RGBA : GL_RGB;
		unsigned char* textureSrc = tex ? tex : bmp;
		if (png != "" && hasMipmaps && m_bUseMipmaps) {
			int s = png.find(".png");
			string base = png.substr(0, s);
			static texture maps[6];
			static bool once = true;
			if (once) {
				loadMipmap(base, maps);
				once = false;
			}
			for (int i = 0; i < 6; i++) {
				texture &map = maps[i];
				GLenum _format = (map.c == 4) ? GL_RGBA : GL_RGB;
				glTexImage2D(GL_TEXTURE_2D, i, 4, map.w, map.h, 0, _format, GL_UNSIGNED_BYTE, map.bmp);
			}
		} else {
			glTexImage2D(GL_TEXTURE_2D, 0, 4, w, h, 0, format, GL_UNSIGNED_BYTE, textureSrc);
		}
		glEnable(GL_TEXTURE_2D);
		if (hasMipmaps && m_bUseMipmaps) {
			glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
			glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
		} else {
			glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
			glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		}
	} else {
		glDisable(GL_TEXTURE_2D);
	}
	for (vector<Hw1Polygon*>::iterator it = polygons->begin();
			it != polygons->end();
			++it) {
		(*it)->draw(useTessellation);
	}
	if (shouldDrawBoundingBox || (name == selectedObject)) {
		drawBoundingBox();
	}
}

void Hw1Object::drawBoundingBox() {
	glBegin(GL_LINE_LOOP);
		glVertex3f(minX, minY, minZ);
		glVertex3f(minX, minY, maxZ);
		glVertex3f(minX, maxY, maxZ);
		glVertex3f(minX, maxY, minZ);
	glEnd();
	glBegin(GL_LINE_LOOP);
		glVertex3f(maxX, minY, minZ);
		glVertex3f(maxX, minY, maxZ);
		glVertex3f(maxX, maxY, maxZ);
		glVertex3f(maxX, maxY, minZ);
	glEnd();
	glBegin(GL_LINE_LOOP);
		glVertex3f(minX, minY, minZ);
		glVertex3f(minX, minY, maxZ);
		glVertex3f(maxX, minY, maxZ);
		glVertex3f(maxX, minY, minZ);
	glEnd();
	glBegin(GL_LINE_LOOP);
		glVertex3f(minX, maxY, minZ);
		glVertex3f(minX, maxY, maxZ);
		glVertex3f(maxX, maxY, maxZ);
		glVertex3f(maxX, maxY, minZ);
	glEnd();
	glBegin(GL_LINE_LOOP);
		glVertex3f(minX, minY, minZ);
		glVertex3f(maxX, minY, minZ);
		glVertex3f(maxX, maxY, minZ);
		glVertex3f(minX, maxY, minZ);
	glEnd();
	glBegin(GL_LINE_LOOP);
		glVertex3f(minX, minY, maxZ);
		glVertex3f(maxX, minY, maxZ);
		glVertex3f(maxX, maxY, maxZ);
		glVertex3f(minX, maxY, maxZ);
	glEnd();
}


void Hw1Polygon::draw(bool useTessellation) {

	if (useTessellation){
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
		glBegin(GL_TRIANGLE_FAN);
	} else {
  	glBegin(GL_POLYGON);
	}

	for (vector<Hw1Vertex*>::iterator it = vertices->begin();
			it != vertices->end();
			++it) {
		Hw1Vertex* v = *it;
		Hw1Normal n = v->getNormal();
		n.normalize();
		glNormal3f(n.x, n.y, n.z);
		if (v->hasUV) {
			glTexCoord2f(v->u, v->v);
		}
		pushName(v->name);
		glVertex3f(v->getX(), v->getY(), v->getZ());
		popName();
	}
	glEnd();
}

void Hw1Polygon::drawNormals(bool showNormals, bool drawVertexNormals, double sizeFactor) {
	double actualSizeFactor = sizeFactor * sizeNormalizeFactor * normalScale;
	for (vector<Hw1Vertex*>::iterator it = vertices->begin();
			it != vertices->end();
			++it) {
		Hw1Vertex* v = *it;
		if (drawVertexNormals && v->hasNormal()) {
			Hw1Normal n = v->getNormal();
			n.normalize();
			n.x *= actualSizeFactor;
			n.y *= actualSizeFactor;
			n.z *= actualSizeFactor;

			n.x += v->getX();
			n.y += v->getY();
			n.z += v->getZ();

			glBegin(GL_LINES);
				glVertex3f(v->getX(), v->getY(), v->getZ());
				glVertex3f(n.x, n.y, n.z);
			glEnd();
		}
	}
	if (showNormals) {
		glBegin(GL_LINES);
			Hw1Normal n = normal;
			n.normalize();
			n.x *= actualSizeFactor;
			n.y *= actualSizeFactor;
			n.z *= actualSizeFactor;

			n.x += centerX;
			n.y += centerY;
			n.z += centerZ;
			glVertex3f(centerX, centerY, centerZ);
			glVertex3f(n.x, n.y, n.z);
		glEnd();
	}
}

// End drawing code /////////////////////////////////////////////

void COpenGLView::OnLButtonDblClk(UINT nFlags, CPoint point)
{	
	/*mat16 matrix;
	
	glGetFloatv(GL_MODELVIEW_MATRIX, matrix);
	glLoadIdentity();
	
	glRotatef( 10, (m_nAxis == ID_AXIS_X)*1.0f, (m_nAxis == ID_AXIS_Y)*1.0f, (m_nAxis == ID_AXIS_Z)*1.0f );
	glMultMatrixf(matrix);
	Hw1Polygon::normalScale += 1.5;


	Invalidate();

	CView::OnLButtonDblClk(nFlags, point);*/
}

BOOL COpenGLView::OnMouseWheel(UINT nFlags, short zDelta, CPoint pt)
{
	float sfloat = zDelta/WHEEL_DELTA/4.0;
	Scale(1+sfloat, 1+sfloat, 1+sfloat);
	Invalidate();
	return CView::OnMouseWheel(nFlags, zDelta, pt);
}

void COpenGLView::Scale(float scaleX, float scaleY, float scaleZ){
	/*if (m_bIsPerspective && multipleViews && (ID_SPACE_SCREEN == nSpace)) {
		return;
	} else if (m_bIsPerspective) {
		m_lZoomRatio /= scaleX; //TODO
		return;
	}*/
	for (int i=0 ; i<numViews ; i++){
		if (m_bTransformTexture){
			tex_scaleU *= scaleX;
			tex_scaleV *= scaleY;
		}else{
			glPushMatrix();
			
			for (int k=0 ; k<numObjects ; k++){
				if (multipleObjects){
					glLoadMatrixf(viewMatrix[k]);
				}else{
					glLoadMatrixf(viewMatrix[i]);
				}
				if ((nSpace == ID_SPACE_SCREEN)&&(((activeView == i)&&(multipleViews))||(activeView == k))){
					GLfloat matrix[16];
							
					glGetFloatv(GL_MODELVIEW_MATRIX, matrix);
					glLoadIdentity();
					glScalef(scaleX , scaleY, scaleZ);
					glMultMatrixf(matrix);
				}else if (nSpace == ID_SPACE_OBJECT){
					glScalef(scaleX , scaleY, scaleZ);
				}
				if (multipleObjects){
					glGetFloatv(GL_MODELVIEW_MATRIX, viewMatrix[k]);
				}else{
					glGetFloatv(GL_MODELVIEW_MATRIX, viewMatrix[i]);
				}
			}
			glPopMatrix();
		}
	}
}


void COpenGLView::Rotate(float angle)
{
	if (m_bTransformTexture){
		tex_rotation = (int)(tex_rotation + angle) % 360;
	}else{
		for (int i=0 ; i<numViews ; i++){
			glPushMatrix();
			for (int k=0 ; k<numObjects ; k++){
				if (multipleObjects){
					glLoadMatrixf(viewMatrix[k]);
				}else{
					glLoadMatrixf(viewMatrix[i]);
				}
				if ((nSpace == ID_SPACE_SCREEN)&&(((activeView == i)&&(multipleViews))||(activeView == k))){ // 
					GLfloat matrix[16];
							
					glGetFloatv(GL_MODELVIEW_MATRIX, matrix);
					glLoadIdentity();
					glRotatef( angle, (m_nAxis == ID_AXIS_X)*1.0f, (m_nAxis == ID_AXIS_Y)*1.0f, (m_nAxis == ID_AXIS_Z)*1.0f );
					glMultMatrixf(matrix);
				}else if (nSpace == ID_SPACE_OBJECT){
					glRotatef( angle, (m_nAxis == ID_AXIS_X)*1.0f, (m_nAxis == ID_AXIS_Y)*1.0f, (m_nAxis == ID_AXIS_Z)*1.0f );
				}
				if (multipleObjects){
					glGetFloatv(GL_MODELVIEW_MATRIX, viewMatrix[k]);
				}else{
					glGetFloatv(GL_MODELVIEW_MATRIX, viewMatrix[i]);
				}
			}
			glPopMatrix();
		}
	}
}

void COpenGLView::Translate(int x, int y)
{	
	if (m_bTransformTexture){
		tex_transU += (double)x/10;
		tex_transV += (double)y/10;
	}else{
		for (int i=0 ; i<numViews ; i++){
		float size;
		if(m_bIsPerspective){
			size = 3.666;
		}else{
			size = 4.0;
		}
		const float transFactorX = size*m_AspectRatio/m_WindowWidth; // sqrt(float (numViews));
		const float transFactorY = size/m_WindowHeight; // sqrt(float (numViews));

		glPushMatrix();
		for (int k=0 ; k<numObjects ; k++){
			if (multipleObjects){
				glLoadMatrixf(viewMatrix[k]);
			}else{
				glLoadMatrixf(viewMatrix[i]);
			}
			if ((nSpace == ID_SPACE_SCREEN)&&(((activeView == i)&&(multipleViews))||(activeView == k))) {
				GLfloat matrix[16];
			
				glGetFloatv(GL_MODELVIEW_MATRIX, matrix);
				glLoadIdentity();
				if ((m_nAxis == ID_AXIS_X) || (m_nAxis == ID_AXIS_Y)){
					glTranslatef(x*transFactorX, (y)*transFactorY,0);
				} else if (m_nAxis == ID_AXIS_Z){// it is ID_AXIS_Z
					glTranslatef(x*transFactorX, 0,-(y)*transFactorY);
				}
				glMultMatrixf(matrix);
			} else if (nSpace == ID_SPACE_OBJECT){
				glTranslatef(x*transFactorX, y*(m_nAxis == ID_AXIS_Y)*transFactorY,-y*(m_nAxis == ID_AXIS_Z)*transFactorY);
			}
			if (multipleObjects){
				glGetFloatv(GL_MODELVIEW_MATRIX, viewMatrix[k]);
			}else{
				glGetFloatv(GL_MODELVIEW_MATRIX, viewMatrix[i]);
			}
		}
		glPopMatrix();
		}
	}
}

void COpenGLView::OnMouseMove(UINT nFlags, CPoint point)
{
	if (rotateLock) {
		lastClicked = point;
		rotateLock = false;
		return;
	}
	float deltaX = 0, deltaY = 0;
	// get the mouse motion, relative to the point where the left button was clicked
	if((nFlags & MK_LBUTTON) == MK_LBUTTON && !m_bSelectingForMipmapping){
		deltaX =  point.x - lastClicked.x;
		deltaY =  lastClicked.y - point.y;
		// TODO - fix action on doubleclick file opening
		switch (m_nAction){
			case ID_ACTION_ROTATE	: Rotate(sensFactor*deltaX/10.0);							break;
			case ID_ACTION_TRANSLATE: 
				if (m_bIsPerspective){
					Translate(sensFactor*deltaX*(m_lPerspectiveRight+m_lPerspectiveLeft)*numObjects*sqrt((double(numViews)))/1.5
								,sensFactor*deltaY*(m_lPerspectiveTop+m_lPerspectiveBottom)*numObjects*sqrt((double(numViews)))/1.5);	
				} else {
					Translate(sensFactor*deltaX*sqrt((double)numViews)*numObjects,
								sensFactor*deltaY*sqrt((double)numViews)*numObjects);	
				} 
				break;
			case ID_ACTION_SCALE	: Scale(1+sensFactor*deltaX/800.0*(m_nAxis == ID_AXIS_X),
											1+sensFactor*deltaX/800.0*(m_nAxis == ID_AXIS_Y),
											1+sensFactor*deltaX/800.0*(m_nAxis == ID_AXIS_Z));	break;
		}
	}
	
	Invalidate();
	lastClicked = point;
	CView::OnMouseMove(nFlags, point);
}


void COpenGLView::OnViewView1()
{
	activeView = 0;
}
void COpenGLView::OnUpdateViewView1(CCmdUI* pCmdUI) 
{
	pCmdUI->SetCheck(activeView == 0);
}

void COpenGLView::OnViewView2()
{
	activeView = 1;
}
void COpenGLView::OnUpdateViewView2(CCmdUI* pCmdUI) 
{
	pCmdUI->SetCheck(activeView == 1);
	pCmdUI->Enable(multipleObjects);
}

void COpenGLView::OnViewView3()
{
	activeView = 2;
}
void COpenGLView::OnUpdateViewView3(CCmdUI* pCmdUI) 
{
	pCmdUI->SetCheck(activeView == 2);
	pCmdUI->Enable(multipleObjects);
}

void COpenGLView::OnViewView4()
{
	activeView = 3;
}

void COpenGLView::OnUpdateViewView4(CCmdUI* pCmdUI) 
{
	pCmdUI->SetCheck(activeView == 3);
	pCmdUI->Enable(multipleObjects);
}

void COpenGLView::OnViewMultipleviews()
{
	multiViewsDialog dlg(numViews);
	
	if (dlg.DoModal() == IDOK) {
		numViews =  dlg.getVal();
		double root = sqrt(double (numViews));
		if (root-int(root) == 0){ // check if input is x^2
			numViewsRows = numViewsCol = root;
		}else{
			return;
		}
	}else{	// cancel pressed
		return;
	}
	multipleViews = (numViews > 1);
	if (!multipleViews){		// just turned off
		for (int i=1 ; i< numViews ; i++){
			for (int k=0 ; k<16 ; k++){
				viewMatrix[i][k] = viewMatrix[0][k];
			}
		}
		activeView = 0;
	} else {
		multipleObjects = false;
		numObjects = 1;
	}
}

void COpenGLView::OnUpdateViewMultipleviews(CCmdUI *pCmdUI)
{
	pCmdUI->SetCheck(multipleViews == true);
}

void COpenGLView::OnViewMultipleobjects()
{
	multiViewsDialog dlg(numViews);
	
	multipleObjects = (!multipleObjects);
	OnMenu();
	if (multipleObjects){ //just turned on
		numObjects = 4;
		multipleViews = false;
		for (int i=0 ; i<numObjects ; i++){
			glPushMatrix();
			glLoadMatrixf(viewMatrix[i]);
			// TEST
			glGetFloatv(GL_MODELVIEW_MATRIX, viewMatrix[i]);
			glPopMatrix();
		}
	}else{		//just turned off
		multipleViews = false;
		numViews = numObjects = 1;
	}
}

void COpenGLView::OnUpdateViewMultipleobjects(CCmdUI *pCmdUI)
{
	pCmdUI->SetCheck(multipleObjects == true);
}
void COpenGLView::drawAllObjects() {
	if (!m_bMayDraw) {
		return;
	}
	for (vector<Hw1Object*>::iterator it = hw1Objects.begin();
			it != hw1Objects.end();
			++it) {

		Hw1Object* o = *it;
		o->draw(m_bDrawBoundingBox, m_bTessellation, m_bChoseColor, m_lColorR, m_lColorG, m_lColorB, globalTexture);
		o->drawNormals(m_bShowNormals, m_bDrawVertexNormals, m_lTotalSize);
	}
}

void COpenGLView::OnLButtonDown(UINT nFlags, CPoint point)
{
	if ((multipleViews)&&(!multipleObjects)){	// find and set the active view
		int i,j;
		for (i=0 ; i< numViewsCol ; i++){
			if (lastClicked.x < (i+1)*m_WindowWidth/numViewsCol){
				break;
			}
		}
		for (j=0 ; j< numViewsRows ; j++){
			if (lastClicked.y < (j+1)*m_WindowHeight/numViewsRows){
				break;
			}
		}
		activeView = i*numViewsRows+(numViewsRows-j-1);
	}
	if (m_bUserCanSelectAnObject) {
		m_bObjectWasSelected = true;
		selectX = point.x;
		selectY = (m_WindowHeight - point.y);
		m_bUserCanSelectAnObject = false;
	}
	CView::OnLButtonDown(nFlags, point);
}

void COpenGLView::OnViewPolygonsnormals()
{
	m_bShowNormals = (!m_bShowNormals);
}

void COpenGLView::OnViewWireframe()
{
	 // Set to GL_LINE_LOOP to get wireframe mode.
	m_bDrawWireframe = !m_bDrawWireframe;
}

void COpenGLView::OnUpdateViewPolygonsnormals(CCmdUI *pCmdUI)
{
	pCmdUI->SetCheck(m_bShowNormals == true);
}

void COpenGLView::OnViewVerticesnormals()
{
	m_bDrawVertexNormals = (!m_bDrawVertexNormals);
}

void COpenGLView::OnUpdateViewVerticesnormals(CCmdUI *pCmdUI)
{
	pCmdUI->SetCheck(m_bDrawVertexNormals == true);
}

void COpenGLView::setProjection() {
	if (m_bIsPerspective) {
		SetupViewingFrustum();
	} else {
		SetupViewingOrthoConstAspect();
	}
}

void COpenGLView::OnOptionsMousesensitivity()
{
	sensitivityDialog dlg(mouseSensitivity);

	if (dlg.DoModal() == IDOK) {
		mouseSensitivity = dlg.getVal();
		SetSensFactor();
		Invalidate();
	}
}
void COpenGLView::SetSensFactor(){
	int sensitivity_delta = (mouseSensitivity-sensitivityDialog::SENS_DEFAULT);
	// sensFactor is a float in the range of [0.02...5]
	sensFactor = (sensitivity_delta < 0) ? 
										(double)mouseSensitivity/sensitivityDialog::SENS_DEFAULT
										: 1+(double)sensitivity_delta/10;
	;
}

void COpenGLView::OnOptionsPerspectivecontrol()
{
	perspectiveDialog dlg(m_lPerspectiveLeft, m_lPerspectiveRight, 
							m_lPerspectiveTop, m_lPerspectiveBottom, 
												m_lPerspectiveDVal);

	if (dlg.DoModal() == IDOK) {
		m_lPerspectiveLeft = dlg.getLeft();
		m_lPerspectiveRight = dlg.getRight();
		m_lPerspectiveTop = dlg.getTop();
		m_lPerspectiveBottom = dlg.getBottom();
		m_lPerspectiveDVal = dlg.getD();
		Invalidate();
	}
}

void COpenGLView::OnViewBoundingBox()
{
	m_bDrawBoundingBox = (!m_bDrawBoundingBox);
}

void COpenGLView::OnUpdateViewBoundingBox(CCmdUI *pCmdUI)
{
	pCmdUI->SetCheck(m_bDrawBoundingBox == true);
}

void COpenGLView::OnActionSetcolor()
{
	CColorDialog colorDlg;
	INT_PTR result = colorDlg.DoModal();

	if ( result == IDOK){
		COLORREF color;
		color = colorDlg.GetColor();
		m_lColorR =  GetRValue(color);
		m_lColorG =  GetGValue(color);
		m_lColorB =  GetBValue(color);
		m_bChoseColor = true;
	} else if ( result == IDCANCEL){
		return;
	}
}
void COpenGLView::OnActionSetbackgroundcolor()
{
	CColorDialog colorDlg;
	INT_PTR result = colorDlg.DoModal();

	if ( result == IDOK){
		COLORREF color;
		color = colorDlg.GetColor();
		m_backColorR =  GetRValue(color);
		m_backColorG =  GetGValue(color);
		m_backColorB =  GetBValue(color);
		m_backChoseColor = true;
	} else if ( result == IDCANCEL){
		return;
	}
}
void COpenGLView::OnActionSetfogcolor()
{
	CColorDialog colorDlg;
	INT_PTR result = colorDlg.DoModal();

	if ( result == IDOK){
		COLORREF color;
		color = colorDlg.GetColor();
		fogColor[0] =  GetRValue(color);
		fogColor[1] =  GetGValue(color);
		fogColor[2] =  GetBValue(color);
	} else if ( result == IDCANCEL){
		return;
	}
}

void COpenGLView::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags)
{	
	if (GetKeyState(VK_CONTROL) < 0){ // Ctrl is being pressed
		switch(nChar){
			case VK_LEFT: Rotate(-10*sensFactor); break;
			case VK_RIGHT: Rotate(10*sensFactor); break;
			case VK_UP: Scale(1+0.1*sensFactor, 1+0.1*sensFactor, 1+0.1*sensFactor); break;
			case VK_DOWN: Scale(1-0.1*sensFactor, 1-0.1*sensFactor, 1-0.1*sensFactor); break;
		} 
	}else{
		switch(nChar){
			case VK_LEFT:	Translate(-10*sensFactor,0);	break;
			case VK_RIGHT:	Translate(10*sensFactor,0);	break;
			case VK_UP:		Translate(0,10*sensFactor);	break;
			case VK_DOWN:	Translate(0,-10*sensFactor);	break;
	}
		
	}
	CView::OnKeyDown(nChar, nRepCnt, nFlags);
	Invalidate();
}


void COpenGLView::OnActionResetcolors()
{
	m_lColorR =  0.0;
	m_lColorG =  0.0;
	m_lColorB =  0.0;
	m_bChoseColor = false;

	m_backColorR =  0.0;
	m_backColorG =  0.0;
	m_backColorB =  0.0;
	m_backChoseColor = false;
}

void COpenGLView::OnUpdateViewWireframe(CCmdUI *pCmdUI)
{
	pCmdUI->SetCheck(m_bDrawWireframe || (m_bTessellation == true));
}

inline double _d256(int color) {
	return (double)color / 255.0;
}

void COpenGLView::setupLighting(bool firstCall) {
	// Material properties
	if (m_bUseModelColors) {
		glColorMaterial(GL_FRONT_AND_BACK, GL_DIFFUSE);
		glEnable(GL_COLOR_MATERIAL);
	} else {
		glColorMaterial(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE);
		glDisable(GL_COLOR_MATERIAL);
		GLfloat ambient[] = { m_lMaterialAmbient, m_lMaterialAmbient, m_lMaterialAmbient, 1.0 };
		GLfloat diffuse[] = { m_lMaterialDiffuse, m_lMaterialDiffuse, m_lMaterialDiffuse, 1.0 };
		glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, ambient);
		glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, diffuse);
	}
	{
		GLfloat specular[] = { m_lMaterialSpecular, m_lMaterialSpecular, m_lMaterialSpecular, 1.0 };
		GLfloat shininess[] = { m_nMaterialShininessFactor };
		glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, specular);
		glMaterialfv(GL_FRONT_AND_BACK, GL_SHININESS, shininess);
	}
	// Fullscene ambient
	{
	LightParams &l = m_ambientLight;
	GLfloat fs_ambient[] = { _d256(l.colorR), _d256(l.colorG), _d256(l.colorB), 1.0 };
	glLightModelfv(GL_LIGHT_MODEL_AMBIENT, fs_ambient);
	}

   static const double cutoff = 60.0;
   static const double exponent = 2.0;

	glEnable(GL_LIGHTING);
	int _l[] = { GL_LIGHT0,
		             GL_LIGHT1,
		             GL_LIGHT2,
		             GL_LIGHT3,
		             GL_LIGHT4,
		             GL_LIGHT5,
		             GL_LIGHT6,
					 GL_LIGHT7 };

	for (int i = 0; i < 8; i++) {
		int lightId = _l[i];
		LightParams &lp = m_lights[i];
		if (!lp.enabled) {
			glDisable(lightId);
			continue;
		}
		glEnable(lightId);

		// Control object space / screen space lighting per light by calling
		// this method twice.
		if (firstCall && lp.space == LIGHT_SPACE_LOCAL) continue;
		if (!firstCall && lp.space == LIGHT_SPACE_VIEW) continue;

		// Position + Directional / Point
		GLfloat w = (lp.type == LIGHT_TYPE_DIRECTIONAL) ? 0.0 : 1.0;
		GLfloat pos[] = { lp.posX, lp.posY, lp.posZ, w };
		glLightfv(lightId, GL_POSITION, pos);

		// Colors
		GLfloat rgba[] = {_d256(lp.colorR), _d256(lp.colorG), _d256(lp.colorB), 1.0 };
		glLightfv(lightId, GL_DIFFUSE, rgba);
		glLightfv(lightId, GL_SPECULAR, rgba);

		if (lp.type == LIGHT_TYPE_SPOT) {
			GLfloat direction[] = { lp.dirX, lp.dirY, lp.dirZ };
			glLightf(lightId, GL_SPOT_CUTOFF, cutoff);
			glLightfv(lightId, GL_SPOT_DIRECTION, direction);
			glLightf(lightId, GL_SPOT_EXPONENT, exponent);
		}
	}
	{
   glLightModeli(GL_LIGHT_MODEL_LOCAL_VIEWER, GL_TRUE);
	}


   if (m_nLightShading == ID_LIGHT_SHADING_FLAT) {
	 glShadeModel (GL_FLAT);
   } else {
	 glShadeModel (GL_SMOOTH);
   }

	// END LIGHTING
}

void COpenGLView::OnViewEnablefog()
{
	m_fogEnabled = (!m_fogEnabled);
	Invalidate();
}

void COpenGLView::OnUpdateViewEnablefog(CCmdUI *pCmdUI)
{
	pCmdUI->SetCheck(m_fogEnabled == true);
}

void COpenGLView::OnViewTessellation()
{
	m_bTessellation = (!m_bTessellation);
	
}

void COpenGLView::OnUpdateViewTessellation(CCmdUI *pCmdUI)
{
	pCmdUI->SetCheck(m_bTessellation == true);
}



void COpenGLView::OnViewSetfogparameters()
{
	fogDialog dlg(	density, fogColor[0], fogColor[1] ,fogColor[2] , fogColor[3] ,
				fogStart , fogEnd , fogMode, fogQuality);

	if (dlg.DoModal() == IDOK) {
		density = dlg.getDensity();
		fogColor[0] = dlg.getRed();
		fogColor[1] = dlg.getGreen();
		fogColor[2] = dlg.getBlue();
		fogColor[3] = (double)dlg.getAlpha()/100;
		fogStart = dlg.getStart();
		fogEnd = dlg.getEnd();
		fogMode = dlg.getMode();
		fogQuality = dlg.getQuality();
		Invalidate();
	}
}

void COpenGLView::OnMaterialSetmaterialparameters()
{
	CMaterialDlg dlg;
	if (dlg.DoModal() == IDOK) {
		m_lMaterialAmbient = dlg.m_ambient;
		m_nMaterialShininessFactor = dlg.m_shininess;
		m_lMaterialDiffuse = dlg.m_diffuse;
		m_lMaterialSpecular = dlg.m_specular;
		Invalidate();
	}
}

void Hw1Object::loadTexture() {
	PngWrapper p(png.c_str());
	if (!p.ReadPng()) {
		string msg = "Unable to read png file " + png;
		AfxMessageBox(msg.c_str());
		return;
	}
	w = p.GetWidth();
	h = p.GetHeight();
	c = p.GetNumChannels();
	bmp = new unsigned char[w*h*c];
	int curPixel = 0;
	for (int _h = 0; _h < h; _h++) {
		for (int _w = 0; _w < w; _w++) {
			int pixel = p.GetValue(_w, _h);
			if (1 == c) {
				bmp[curPixel++] = pixel;
				bmp[curPixel++] = pixel;
				bmp[curPixel++] = pixel;
				continue;
			}
			bmp[curPixel++] = GET_R(pixel);
			bmp[curPixel++] = GET_G(pixel);
			bmp[curPixel++] = GET_B(pixel);
			if (4 == c) {
				bmp[curPixel++] = GET_A(pixel);
			}
		}
	}
}

void COpenGLView::OnActionUsemodelcolors()
{
	m_bUseModelColors = (!m_bUseModelColors);
}

void COpenGLView::OnUpdateActionUsemodelcolors(CCmdUI *pCmdUI)
{
	pCmdUI->SetCheck(m_bUseModelColors == true );
}

void COpenGLView::OnViewCullbackfaces()
{
	m_bCullBackFaces = (!m_bCullBackFaces);
}

void COpenGLView::OnUpdateViewCullbackfaces(CCmdUI *pCmdUI)
{
	pCmdUI->SetCheck(m_bCullBackFaces == true );
}

void COpenGLView::OnActionTexturetransformation()
{
	m_bTransformTexture = (!m_bTransformTexture);
}

void COpenGLView::OnUpdateActionTexturetransformation(CCmdUI *pCmdUI)
{
	pCmdUI->SetCheck(m_bTransformTexture == true );
}
void COpenGLView::OnMaterialGenerateuvector()
{
	vectorDialog dlg(texGenU[0], texGenU[1], texGenU[2]);

	if (dlg.DoModal() == IDOK) {
		texGenU[0] = dlg.getX();
		texGenU[1] = dlg.getY();
		texGenU[2] = dlg.getZ();

		m_bGentexUScreenSpace = true;
		Invalidate();
	}
}

void COpenGLView::OnMaterialGeneratevvector()
{
	vectorDialog dlg(texGenV[0], texGenV[1], texGenV[2]);

	if (dlg.DoModal() == IDOK) {
		texGenV[0] = dlg.getX();
		texGenV[1] = dlg.getY();
		texGenV[2] = dlg.getZ();

		m_bGentexVScreenSpace = true;
		Invalidate();
	}
}




void COpenGLView::OnMaterialUsemipmap()
{
	m_bUseMipmaps = (!m_bUseMipmaps);
}

void COpenGLView::OnUpdateMaterialUsemipmap(CCmdUI *pCmdUI)
{
	pCmdUI->SetCheck(m_bUseMipmaps == true );
}

void COpenGLView::OnMaterialUseutexture()
{
	m_bGenerateTexturesU = (!m_bGenerateTexturesU );
}

void COpenGLView::OnUpdateMaterialUseutexture(CCmdUI *pCmdUI)
{
	pCmdUI->SetCheck(m_bGenerateTexturesU == false );
}
void COpenGLView::OnMaterialUsevtexture()
{
	m_bGenerateTexturesV = (!m_bGenerateTexturesV );
}

void COpenGLView::OnUpdateMaterialUsevtexture(CCmdUI *pCmdUI)
{
	pCmdUI->SetCheck(m_bGenerateTexturesV == false );
}

void COpenGLView::OnUtexturefillingRepeat()
{
	s_repeat = true;
}

void COpenGLView::OnUpdateUtexturefillingRepeat(CCmdUI *pCmdUI)
{
	pCmdUI->SetCheck(s_repeat == true );
}

void COpenGLView::OnUtexturefillingClamp()
{
	s_repeat = false;
}

void COpenGLView::OnUpdateUtexturefillingClamp(CCmdUI *pCmdUI)
{
	pCmdUI->SetCheck(s_repeat == false );
}

void COpenGLView::OnVtexturefillingRepeat()
{
	t_repeat = true;
}

void COpenGLView::OnUpdateVtexturefillingRepeat(CCmdUI *pCmdUI)
{
	pCmdUI->SetCheck(t_repeat == true );
}

void COpenGLView::OnVtexturefillingClamp()
{
	t_repeat = false;
}

void COpenGLView::OnUpdateVtexturefillingClamp(CCmdUI *pCmdUI)
{
	pCmdUI->SetCheck(t_repeat == false );
}



void COpenGLView::OnUcoordinatesspaceScreenspace()
{
	m_bGentexUScreenSpace = true;
}

void COpenGLView::OnUpdateUcoordinatesspaceScreenspace(CCmdUI *pCmdUI)
{
	pCmdUI->SetCheck(m_bGentexUScreenSpace == true );
}

void COpenGLView::OnUcoordinatesspaceModelspace()
{
	m_bGentexUScreenSpace = false;
}

void COpenGLView::OnUpdateUcoordinatesspaceModelspace(CCmdUI *pCmdUI)
{
	pCmdUI->SetCheck(m_bGentexUScreenSpace == false );
}

void COpenGLView::OnVcoordinatesspaceScreenspace()
{
	m_bGentexVScreenSpace = true;
}

void COpenGLView::OnUpdateVcoordinatesspaceScreenspace(CCmdUI *pCmdUI)
{
	pCmdUI->SetCheck(m_bGentexVScreenSpace == true );
}

void COpenGLView::OnVcoordinatesspaceModelspace()
{
	m_bGentexVScreenSpace = false;
}

void COpenGLView::OnUpdateVcoordinatesspaceModelspace(CCmdUI *pCmdUI)
{
	pCmdUI->SetCheck(m_bGentexVScreenSpace == false );
}

int findSelectedObject(GLint hits, GLuint buffer[]) {
   GLuint names, *ptr, minZ, *ptrNames = NULL;
   if (hits == 0) return -1;
   ptr = (GLuint *)buffer;
   minZ = 0xffffffff;
   for (int i = 0; i < hits; i++) {	
      names = *ptr;
	  ptr++;
	  if (*ptr < minZ) {
		  minZ = *ptr;
		  ptrNames = ptr+2;
	  }
	  ptr += names+2;
	}
  // Assuming only one name.
  return (int)*ptrNames;
}

void COpenGLView::OnMaterialSelectobjectformipmapping()
{
	m_bUserCanSelectAnObject = true;
	m_bSelectingForMipmapping = true;
}

void COpenGLView::OnMaterialSelectobject()
{
	m_bUserCanSelectAnObject = true;
}

void COpenGLView::OnFileLoadglobaltexture()
{
	rotateLock = true;
	CFileDialog dlg(TRUE, "", "*.*", OFN_FILEMUSTEXIST | OFN_HIDEREADONLY);

	if (dlg.DoModal () == IDOK) {
		string fileName = dlg.GetPathName();
		PngWrapper p(fileName.c_str());
		if (!p.ReadPng()) {
			string msg = "Unable to read png file";
			AfxMessageBox(msg.c_str());
			throw 0;
		}
		g_w = p.GetWidth();
		g_h = p.GetHeight();
		g_c = p.GetNumChannels();
		if (globalTexture != NULL) delete globalTexture;
		globalTexture = new unsigned char[g_w*g_h*g_c];
		int curPixel = 0;
		for (int _h = 0; _h < g_h; _h++) {
			for (int _w = 0; _w < g_w; _w++) {
				int pixel = p.GetValue(_w, _h);
				if (1 == g_c) {
					globalTexture[curPixel++] = pixel;
					globalTexture[curPixel++] = pixel;
					globalTexture[curPixel++] = pixel;
					continue;
				}
				globalTexture[curPixel++] = GET_R(pixel);
				globalTexture[curPixel++] = GET_G(pixel);
				globalTexture[curPixel++] = GET_B(pixel);
				if (4 == g_c) {
					globalTexture[curPixel++] = GET_A(pixel);
				}
			}
		}
	}
}
