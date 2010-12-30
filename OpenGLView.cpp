// OpenGLView.cpp : implementation of the COpenGLView class
//
#include "stdafx.h"
#include "OpenGL.h"

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

extern vector<Hw1Object*> hw1Objects;
extern void clearHw1Objects();

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

COpenGLView::COpenGLView()
{


	// Set default values
	m_nAxis = ID_AXIS_X;
	m_nAction = ID_ACTION_ROTATE;
	m_nView = ID_VIEW_ORTHOGRAPHIC;	
	m_bIsPerspective = false;

	m_nLightShading = ID_LIGHT_SHADING_FLAT;

	m_lMaterialAmbient = 0.2;
	m_lMaterialDiffuse = 0.8;
	m_lMaterialSpecular = 1.0;
	m_nMaterialShininessFactor = 32;

	//init the first light to be enabled
	m_lights[LIGHT_ID_1].enabled=true;

	m_lZoomRatio = zoomRatioDefault; // hw1 zoom ratio
	m_lPerspectiveLeft = m_lPerspectiveRight = 
		m_lPerspectiveTop = m_lPerspectiveBottom = perspectiveDialog::PERS_DEFAULT;
	lastClicked.SetPoint(0,0);	//hw1
	mouseSensitivity = sensitivityDialog::SENS_DEFAULT;
	// FOG PARAMETERS
	m_fogEnabled = false;
	density = fogDialog::DENSITY_DEF;
	fogColor[0] = fogDialog::FOG_COLOR_R_DEF;
	fogColor[1] = fogDialog::FOG_COLOR_G_DEF;
	fogColor[2] = fogDialog::FOG_COLOR_B_DEF;
	fogColor[3] = fogDialog::FOG_COLOR_A_DEF;
	fogStart = fogDialog::FOG_START_DEF;
	fogEnd = fogDialog::FOG_END_DEF;
	fogMode = fogDialog::FOG_MODE_DEF;
			// FOG PARAMETERS END
	m_bShowNormals = false;
	m_bDrawVertexNormals = false;
	m_bMayDraw = false; // Wait until size and center of object is calculated
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
	numViewsRows = numViewsCol = sqrt(double(numViews));
	activeView = 0;
	for (int i=0 ; i<MAX_VIEWS ; i++){
		for (int k=0 ; k<16 ; k++){
			viewMatrix[i][k] = (k%5 == 0);
		}
	}
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
	setProjection();

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
				1.0*zFactor, 5*1.2*m_lTotalSize*zFactor);					//test

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
	int t = ::glGetError();
	if ( GL_NO_ERROR !=  t)
		;
	glEnable (GL_FOG); //enable the fog
	t = ::glGetError();
	if ( GL_NO_ERROR !=  t)
		;
	glFogf (GL_FOG_START,fogStart);
	t = ::glGetError();
	if ( GL_NO_ERROR !=  t)
		;
	glFogf (GL_FOG_END,fogEnd);
	t = ::glGetError();
	if ( GL_NO_ERROR !=  t)
		;
	glFogi (GL_FOG_MODE, GL_EXP); //set the fog mode to GL_EXP2
	t = ::glGetError();
	if ( GL_NO_ERROR !=  t)
		;
	glFogfv (GL_FOG_COLOR, fogColor); //set the fog color to our color chosen above
	t = ::glGetError();
	if ( GL_NO_ERROR !=  t)
		;
	glFogf (GL_FOG_DENSITY, density/100); //set the density to the value above
	t = ::glGetError();
	if ( GL_NO_ERROR !=  t)
		;
	glHint (GL_FOG_HINT, fogMode); // set the fog to look the	nicest, may slow down on older cards
	t = ::glGetError();
	if ( GL_NO_ERROR !=  t)
		;
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
		glClearColor(m_backColorR/255, m_backColorG/255, m_backColorB/255, 0.0);
	}else{
		glClearColor(0.0, 0.0, 0.0, 0.0);
	}
	if (m_fogEnabled)
			EnableFog();
	//draw_axis();

	for (int  i=0; i<numViewsCol ;i++){
		for (int j=0 ; j<numViewsRows ; j++){
			for(int k=0 ; k<numObjects ; k++){
				glLoadIdentity();	
				// load the view matrix and draw it
				if (m_bIsPerspective) {
					glTranslatef(0.0, 0.0, -m_lPerspectiveDVal*m_lTotalSize);	//test
				}
				if (multipleObjects){
					float scale = sqrt(m_lTotalSize)/2/numObjects;
					glScalef(scale, scale, scale);
					float trans = (k-numObjects/2+0.5)*0.5*m_lTotalSize;
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
				float scale = 3.0/m_lTotalSize;
				glScalef(scale, scale, scale);
				glTranslatef(-m_lCenterX, -m_lCenterY, -m_lCenterZ);
				setupLighting(false);
				drawAllObjects();
			}
		}
	}

	glPopMatrix();
	
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
		glColor3f(1-i/NUM_OBJ, 0, 0+i/NUM_OBJ);
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


void COpenGLView::OnFileLoad() 
{
	TCHAR szFilters[] = _T ("IRIT Data Files (*.itd)|*.itd|All Files (*.*)|*.*||");

	CFileDialog dlg(TRUE, "itd", "*.itd", OFN_FILEMUSTEXIST | OFN_HIDEREADONLY ,szFilters);

	if (dlg.DoModal () == IDOK) {
		m_strItdFileName = dlg.GetPathName();		// Full path and filename
		PngWrapper p;
		
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
		m_lCenterX = (minX + maxX) / 2.0;
		m_lCenterY = (minY + maxY) / 2.0;
		m_lCenterZ = (minZ + maxZ) / 2.0;
		
		// Calculate absolute size:
		double x = m_lCenterX - minX;
		double y = m_lCenterY - minY;
		double z = m_lCenterZ - minZ;
		m_lTotalSize = sqrt(x*x + y*y + z*z);
		mouseSensitivity = sensitivityDialog::SENS_DEFAULT;
		m_bMayDraw = true;
		
		Invalidate();	// force a WM_PAINT for drawing.
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
	m_lZoomRatio = zoomRatioDefault;
	m_lPerspectiveLeft = 
		m_lPerspectiveRight = 
			m_lPerspectiveTop = 
				m_lPerspectiveBottom =
					m_lPerspectiveBottom = perspectiveDialog::PERS_DEFAULT;
	m_lPerspectiveDVal = perspectiveDialog::PERS_DEFAULT_D;
	m_bChoseColor = false;
	m_backChoseColor = false;
	Hw1Polygon::drawingMode = GL_POLYGON;

	SetSensFactor();

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
int Hw1Polygon::drawingMode = GL_POLYGON; // Set to GL_LINE_LOOP to get wireframe mode.
double Hw1Polygon::sizeNormalizeFactor = 0.2;

void Hw1Object::draw(bool shouldDrawBoundingBox, bool hasColor, double cR, double cG, double cB) {
	if (hasColor) {
		// color is an integer in 0-255 range. glColor3fparams are 0.0-1.0 doubles
		glColor3f(cR/255, cG/255, cB/255);
	} else {
		glColor3f(colorR, colorG, colorB);
	}
	for (vector<Hw1Polygon*>::iterator it = polygons->begin();
			it != polygons->end();
			++it) {
		(*it)->draw();
	}
	if (shouldDrawBoundingBox) {
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

void Hw1Polygon::draw() {
	glBegin(drawingMode);
	for (vector<Hw1Vertex*>::iterator it = vertices->begin();
			it != vertices->end();
			++it) {
		Hw1Vertex* v = *it;
		Hw1Normal n = v->getNormal();
		n.normalize();
		glNormal3f(n.x, n.y, n.z);
		glVertex3f(v->getX(), v->getY(), v->getZ());
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


void COpenGLView::Rotate(float angle)
{
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

void COpenGLView::Translate(int x, int y)
{	
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
				glTranslatef(x*transFactorX, (y)*transFactorY,0);
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

void COpenGLView::OnMouseMove(UINT nFlags, CPoint point)
{
	float deltaX = 0, deltaY = 0;
	// get the mouse motion, relative to the point where the left button was clicked
	if((nFlags & MK_LBUTTON) == MK_LBUTTON){
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
		(*it)->draw(m_bDrawBoundingBox, m_bChoseColor, m_lColorR, m_lColorG, m_lColorB);
		(*it)->drawNormals(m_bShowNormals, m_bDrawVertexNormals, m_lTotalSize);
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

	CView::OnLButtonDown(nFlags, point);
}

void COpenGLView::OnViewPolygonsnormals()
{
	m_bShowNormals = (!m_bShowNormals);
}

void COpenGLView::OnViewWireframe()
{
	 // Set to GL_LINE_LOOP to get wireframe mode.
	Hw1Polygon::drawingMode = (Hw1Polygon::drawingMode == GL_POLYGON) ?
								GL_LINE_LOOP : 
								GL_POLYGON;
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
	pCmdUI->SetCheck(Hw1Polygon::drawingMode == GL_LINE_LOOP);
}

inline double _d256(int color) {
	return (double)color / 255.0;
}

void COpenGLView::setupLighting(bool firstCall) {
	// Fullscene ambient
	{
	LightParams &l = m_ambientLight;
	GLfloat fs_ambient[] = { _d256(l.colorR), _d256(l.colorG), _d256(l.colorB), 1.0 };
	glLightModelfv(GL_LIGHT_MODEL_AMBIENT, fs_ambient);
	}

   static const double cutoff = 60.0;
   static const double exponent = 2.0;
   GLfloat spotDirection0[] = { -1.0, 0.0, -3.0, 1.0};
   GLfloat spotDirection1[] = { 1.0, 0.0, -3.0, 1.0};
   GLfloat spotDirection2[] = { 0.0, 1.0, -5.0, 1.0};

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
		LightParams &lp = m_lights[i];
		if (!lp.enabled) continue;
		int lightId = _l[i];
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
	GLfloat specular[] = { 1.0, 1.0, 1.0, 1.0 };
	GLfloat shininess = 40.0;
   glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, specular);
   glMaterialfv(GL_FRONT_AND_BACK, GL_SHININESS, &shininess);
   glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
   glLightModeli(GL_LIGHT_MODEL_LOCAL_VIEWER, GL_TRUE);
   /*
  

   glLightfv(GL_LIGHT0, GL_POSITION, position0);
   glLightfv(GL_LIGHT1, GL_POSITION, position1);
   glLightfv(GL_LIGHT2, GL_POSITION, position2);
   glLightfv(GL_LIGHT0, GL_AMBIENT, ambient);
   glLightfv(GL_LIGHT1, GL_AMBIENT, ambient);
   glLightfv(GL_LIGHT2, GL_AMBIENT, ambient);
   glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuse0);
   glLightfv(GL_LIGHT1, GL_DIFFUSE, diffuse1);
   glLightfv(GL_LIGHT2, GL_DIFFUSE, diffuse2);
   glLightfv(GL_LIGHT0, GL_SPECULAR, diffuse0);
   glLightfv(GL_LIGHT1, GL_SPECULAR, diffuse1);
   glLightfv(GL_LIGHT2, GL_SPECULAR, diffuse2);
   glLightfv(GL_LIGHT0, GL_SPOT_DIRECTION, spotDirection0);
   glLightfv(GL_LIGHT1, GL_SPOT_DIRECTION, spotDirection1);
   glLightfv(GL_LIGHT2, GL_SPOT_DIRECTION, spotDirection2);
   glLightf(GL_LIGHT0, GL_SPOT_CUTOFF, cutoff);
   glLightf(GL_LIGHT1, GL_SPOT_CUTOFF, cutoff);
   glLightf(GL_LIGHT2, GL_SPOT_CUTOFF, cutoff);
   glLightf(GL_LIGHT0, GL_SPOT_EXPONENT, exponent);
   glLightf(GL_LIGHT1, GL_SPOT_EXPONENT, exponent);
   glLightf(GL_LIGHT2, GL_SPOT_EXPONENT, exponent);

   glEnable(GL_LIGHT0);
   glEnable(GL_LIGHT1);
   glEnable(GL_LIGHT2);
*/

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
}

void COpenGLView::OnViewSetfogparameters()
{
	fogDialog dlg(	density, fogColor[0], fogColor[1] ,fogColor[2] , fogColor[3] ,
					fogStart , fogEnd , fogMode);

	if (dlg.DoModal() == IDOK) {
		density = dlg.getDensity();
		fogColor[0] = dlg.getRed();
		fogColor[1] = dlg.getGreen();
		fogColor[2] = dlg.getBlue();
		fogColor[3] = dlg.getAlfa();
		fogStart = dlg.getStart();
		fogEnd = dlg.getEnd();
		fogMode = dlg.getMode();
		Invalidate();
	}
}

void COpenGLView::OnMaterialSetmaterialparameters()
{
	// TODO: Add your command handler code here
}

