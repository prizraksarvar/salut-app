//
// Sarvar Khasanov
//
// OpenGL Window
//


#include <Windows.h>
#include <gl/GL.h>
#include <gl/GLU.h>
#include "gl_window.h"
#include "application.h"
#include "iscene.h"
#include "scene.h"

#pragma comment( lib, "opengl32.lib" )
#pragma comment( lib, "glu32.lib" )

void GLWindowInit::ReshapeGL(int iwidth, int iheight)
{
	this->width = iwidth;
	this->height = iheight;
	glViewport(0, 0, (GLsizei)(iwidth), (GLsizei)(iheight));
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(0.0f, (GLfloat)(iwidth) / (GLfloat)(iheight), 1.0f, 100.0f);
	float dim = (float)iwidth / iheight;
	if (iwidth > iheight)
	{
		dim = (float)iheight / iwidth;
	}
	glOrtho(0, width, 0, height, 1.0f, 100.0f);
	glMatrixMode(GL_MODELVIEW);	
	glLoadIdentity();
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glEnable(GL_BLEND);
}

BOOL GLWindowInit::ChangeScreenResolution(int width, int height, int bitsPerPixel)
{
	DEVMODE dmScreenSettings;
	ZeroMemory(&dmScreenSettings, sizeof(DEVMODE));
	dmScreenSettings.dmSize = sizeof(DEVMODE);
	dmScreenSettings.dmPelsWidth = width;
	dmScreenSettings.dmPelsHeight = height;	
	dmScreenSettings.dmBitsPerPel = bitsPerPixel;
	dmScreenSettings.dmFields = DM_BITSPERPEL | DM_PELSWIDTH | DM_PELSHEIGHT;
	if (ChangeDisplaySettings(&dmScreenSettings, CDS_FULLSCREEN) != DISP_CHANGE_SUCCESSFUL)
	{
		return FALSE;
	}
	return TRUE;
}

void GLWindow::TerminateApplication()
{
	PostMessage(this->hWnd, WM_QUIT, 0, 0);
	this->isProgramLooping = FALSE;
}


BOOL GLWindow::CreateWindowGL()
{
	DWORD windowStyle = WS_OVERLAPPEDWINDOW;
	DWORD windowExtendedStyle = WS_EX_APPWINDOW;

	PIXELFORMATDESCRIPTOR pfd =	
	{
		sizeof(PIXELFORMATDESCRIPTOR),
		1,					
		PFD_DRAW_TO_WINDOW |
		PFD_SUPPORT_OPENGL |
		PFD_STEREO |
		PFD_DOUBLEBUFFER,
		PFD_TYPE_RGBA,
		this->init.bitsPerPixel,
		0, 0, 0, 0, 0, 0,
		0,
		0,
		0,
		0, 0, 0, 0,
		16,
		0,
		0,
		PFD_MAIN_PLANE,
		0,
		0, 0, 0
	};

	RECT windowRect = { 0, 0, this->init.width, this->init.height };

	GLuint PixelFormat;

	AdjustWindowRectEx(&windowRect, windowStyle, 0, windowExtendedStyle);

	this->hWnd = CreateWindowEx(windowExtendedStyle,
		this->init.application->className,
		this->init.title,
		windowStyle,
		0, 0,
		windowRect.right - windowRect.left,
		windowRect.bottom - windowRect.top,
		HWND_DESKTOP,
		0,
		this->init.application->hInstance,
		this);

	if (this->hWnd == 0)
	{
		return FALSE;
	}

	this->hDC = GetDC(this->hWnd);
	if (this->hDC == 0)
	{

		DestroyWindow(this->hWnd);
		this->hWnd = 0;
		return FALSE;
	}

	PixelFormat = ChoosePixelFormat(this->hDC, &pfd);
	if (PixelFormat == 0)
	{

		ReleaseDC(this->hWnd, this->hDC);
		this->hDC = 0;
		DestroyWindow(this->hWnd);
		this->hWnd = 0;
		return FALSE;
	}

	if (!SetPixelFormat(this->hDC, PixelFormat, &pfd))
	{
		ReleaseDC(this->hWnd, this->hDC);
		this->hDC = 0;
		DestroyWindow(this->hWnd);
		this->hWnd = 0;
		return FALSE;
	}

	this->hRC = wglCreateContext(this->hDC);
	if (this->hRC == 0)
	{
		ReleaseDC(this->hWnd, this->hDC);
		this->hDC = 0;
		DestroyWindow(this->hWnd);
		this->hWnd = 0;
		return FALSE;
	}


	if (wglMakeCurrent(this->hDC, this->hRC) == FALSE)
	{
		wglDeleteContext(this->hRC);
		this->hRC = 0;
		ReleaseDC(this->hWnd, this->hDC);
		this->hDC = 0;
		DestroyWindow(this->hWnd);
		this->hWnd = 0;
		return FALSE;
	}

	ShowWindow(this->hWnd, SW_NORMAL);
	this->isVisible = TRUE;

	this->init.ReshapeGL(this->init.width, this->init.height);

	this->lastTickCount = GetTickCount();

	return TRUE;
}

BOOL GLWindow::DestroyWindowGL()
{
	if (this->hWnd != 0)
	{
		if (this->hDC != 0)
		{
			wglMakeCurrent(this->hDC, 0);
			if (this->hRC != 0)
			{
				wglDeleteContext(this->hRC);
				this->hRC = 0;

			}
			ReleaseDC(this->hWnd, this->hDC);
			this->hDC = 0;
		}
		DestroyWindow(this->hWnd);
		this->hWnd = 0;
	}

	return TRUE;
}

BOOL GLWindow::Initialize()
{
	viewPosition = Vector3f(0,0,0);
	sceneRender = new SceneRender();
	mouseClickPosition = new Point();
	mouseClickPosition->x = -1;
	mouseClickPosition->y = -1;

	// There we can switch scene in the future
	scene = new Scene();
	if (!scene->Initialize()) {
		return FALSE;
	}
	return TRUE;
}

void GLWindow::Deinitialize()
{
	if (scene!=NULL)
		scene->Deinitialize();
}

void GLWindow::Update(DWORD milliseconds)
{
	scene->Update(milliseconds);
}

void GLWindow::Draw()
{
	sceneRender->Draw(*scene, viewPosition, viewAngle, init.width, init.height);
}

void GLWindow::MouseClick(Point* clickPosition)
{
	scene->AddFirework(Vector3f(clickPosition->x, init.height - clickPosition->y,0));
}