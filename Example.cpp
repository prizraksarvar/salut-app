/**************************************
*                                     *
*   Jeff Molofee's Basecode Example   *
*          nehe.gamedev.net           *
*                2001                 *
*                                     *
**************************************/

#include <windows.h>											// Header File For Windows
#include <gl\gl.h>												// Header File For The OpenGL32 Library
#include <gl\glu.h>												// Header File For The GLu32 Library
#include "NeHeGL.h"												// Header File For NeHeGL
#include "remPartMgr.h"
#include "SimpleMath.h"

#pragma comment( lib, "opengl32.lib" )							// Search For OpenGL32.lib While Linking
#pragma comment( lib, "glu32.lib" )								// Search For GLu32.lib While Linking

#ifndef CDS_FULLSCREEN											// CDS_FULLSCREEN Is Not Defined By Some
#define CDS_FULLSCREEN 4										// Compilers. By Defining It This Way,
#endif															// We Can Avoid Errors

GL_Window*	g_window;
Keys*		g_keys;

// User Defined Variables
float		angle;												// Used To Rotate The Triangles
int			rot1, rot2;											// Counter Variables

// Our particle systems
pTwister		CoolPMgr;
pExplosion		CoolExpl;
pSmoke			CoolSmoke;
pTotalWildness	CoolWildness;

BOOL GL_Window::Initialize ()					// Any GL Init Code & User Initialiazation Goes Here
{
	g_window	= this;
	g_keys		= this->keys;

	// Start Of User Initialization
	angle		= 0.0f;											// Set Starting Angle To Zero

	glClearColor (0.0f, 0.0f, 0.0f, 0.5f);						// Black Background
	glClearDepth (1.0f);										// Depth Buffer Setup
	glDepthFunc (GL_LEQUAL);									// The Type Of Depth Testing (Less Or Equal)
	glEnable (GL_DEPTH_TEST);									// Enable Depth Testing
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glShadeModel (GL_SMOOTH);									// Select Smooth Shading
	glHint (GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);			// Set Perspective Calculations To Most Accurate

	return TRUE;												// Return TRUE (Initialization Successful)
}

void GL_Window::Deinitialize (void)										// Any User DeInitialization Goes Here
{
}

void Update (DWORD milliseconds)								// Perform Motion Updates Here
{
	double FrameTime = (double)milliseconds / 1000.0f;
	static bool a = false, s = false, d = false, f = false;

	if (g_keys->keyDown [VK_ESCAPE] == TRUE)					// Is ESC Being Pressed?
	{
		g_window->TerminateApplication ();						// Terminate The Program
	}

	if (g_keys->keyDown [VK_F1] == TRUE)						// Is F1 Being Pressed?
	{
		g_window->ToggleFullscreen ();							// Toggle Fullscreen Mode
	}

	// Twister
	if ((g_keys->keyDown ['A'] == TRUE) && (!a))
	{
		CoolPMgr.Alive = !CoolPMgr.Alive;
		if (CoolPMgr.Alive) 
			CoolPMgr.Emit(500, remVector3f(-1.0f, 0.0f, 0.0f));
		a = true;
	}
	if (g_keys->keyDown ['A'] == FALSE) a = false;

	if ((g_keys->keyDown ['S'] == TRUE) && (!s))
	{
		CoolExpl.Alive = true;
		if (CoolExpl.Alive)
			CoolExpl.Emit(100, remVector3f(0.0f, 0.0f, 0.0f));
		s = true;
	}
	if (g_keys->keyDown ['S'] == FALSE) s = false;

	if ((g_keys->keyDown ['D'] == TRUE) && (!d))
	{
		CoolSmoke.Alive = !CoolSmoke.Alive;
		d = true;
	}
	if (g_keys->keyDown ['D'] == FALSE) d = false;

	if ((g_keys->keyDown ['F'] == TRUE) && (!f))
	{
		CoolWildness.Alive = !CoolWildness.Alive;
		f = true;
	}
	if (g_keys->keyDown ['F'] == FALSE) f = false;

	// Update particle systems
	CoolPMgr.Update(FrameTime);
	CoolExpl.Update(FrameTime);
	CoolSmoke.Update(FrameTime);
	CoolWildness.Update(FrameTime);

	static float EmitPeriod;
	EmitPeriod += FrameTime;
	if (EmitPeriod > 0.1)
	{
		CoolSmoke.Emit(10, remVector3f(1.0f, -1.0f, 0.0f));
		CoolWildness.Emit(10, remVector3f(-1.0f, -0.5f, 0.0f));
		EmitPeriod = 0.0;
	}
}

void GL_Window::Draw (void)
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();
	glTranslatef(0.0f, 0.0f, -3.0f);
	glTranslatef(0.0f, -1.0f, -4.0f);
	glBegin(GL_QUADS);
		if (CoolPMgr.Alive) 
		for (int o = 0; o < CoolPMgr.CurrCount; o++)
		{
			glColor4fv(&CoolPMgr.PArr[o].Color.C[0]);
			glVertex3f(CoolPMgr.PArr[o].Pos.V[0] - 0.05f, 
					   CoolPMgr.PArr[o].Pos.V[1] - 0.05f,
					   CoolPMgr.PArr[o].Pos.V[2]);
			glVertex3f(CoolPMgr.PArr[o].Pos.V[0] + 0.05f, 
					   CoolPMgr.PArr[o].Pos.V[1] - 0.05f,
					   CoolPMgr.PArr[o].Pos.V[2]);
			glVertex3f(CoolPMgr.PArr[o].Pos.V[0] + 0.05f, 
					   CoolPMgr.PArr[o].Pos.V[1] + 0.05f,
					   CoolPMgr.PArr[o].Pos.V[2]);
			glVertex3f(CoolPMgr.PArr[o].Pos.V[0] - 0.05f, 
					   CoolPMgr.PArr[o].Pos.V[1] + 0.05f,
					   CoolPMgr.PArr[o].Pos.V[2]);
		}
		if (CoolExpl.Alive) 
		for (int o = 0; o < CoolExpl.CurrCount; o++)
		{
			glColor4fv(&CoolExpl.PArr[o].Color.C[0]);
			glVertex3f(CoolExpl.PArr[o].Pos.V[0] - 0.1f, 
					   CoolExpl.PArr[o].Pos.V[1] - 0.1f,
					   CoolExpl.PArr[o].Pos.V[2]);
			glVertex3f(CoolExpl.PArr[o].Pos.V[0] + 0.1f, 
					   CoolExpl.PArr[o].Pos.V[1] - 0.1f,
					   CoolExpl.PArr[o].Pos.V[2]);
			glVertex3f(CoolExpl.PArr[o].Pos.V[0] + 0.1f, 
					   CoolExpl.PArr[o].Pos.V[1] + 0.1f,
					   CoolExpl.PArr[o].Pos.V[2]);
			glVertex3f(CoolExpl.PArr[o].Pos.V[0] - 0.1f, 
					   CoolExpl.PArr[o].Pos.V[1] + 0.1f,
					   CoolExpl.PArr[o].Pos.V[2]);
		}
		if (CoolSmoke.Alive) 
		for (int o = 0; o < CoolSmoke.CurrCount; o++)
		{
			glColor4fv(&CoolSmoke.PArr[o].Color.C[0]);
			glVertex3f(CoolSmoke.PArr[o].Pos.V[0] - 0.1f, 
					   CoolSmoke.PArr[o].Pos.V[1] - 0.1f,
					   CoolSmoke.PArr[o].Pos.V[2]);
			glVertex3f(CoolSmoke.PArr[o].Pos.V[0] + 0.1f, 
					   CoolSmoke.PArr[o].Pos.V[1] - 0.1f,
					   CoolSmoke.PArr[o].Pos.V[2]);
			glVertex3f(CoolSmoke.PArr[o].Pos.V[0] + 0.1f, 
					   CoolSmoke.PArr[o].Pos.V[1] + 0.1f,
					   CoolSmoke.PArr[o].Pos.V[2]);
			glVertex3f(CoolSmoke.PArr[o].Pos.V[0] - 0.1f, 
					   CoolSmoke.PArr[o].Pos.V[1] + 0.1f,
					   CoolSmoke.PArr[o].Pos.V[2]);
		}
		if (CoolWildness.Alive) 
		for (int o = 0; o < CoolWildness.CurrCount; o++)
		{
			glColor4fv(&CoolWildness.PArr[o].Color.C[0]);
			glVertex3f(CoolWildness.PArr[o].Pos.V[0] - 0.1f, 
					   CoolWildness.PArr[o].Pos.V[1] - 0.1f,
					   CoolWildness.PArr[o].Pos.V[2]);
			glVertex3f(CoolWildness.PArr[o].Pos.V[0] + 0.1f, 
					   CoolWildness.PArr[o].Pos.V[1] - 0.1f,
					   CoolWildness.PArr[o].Pos.V[2]);
			glVertex3f(CoolWildness.PArr[o].Pos.V[0] + 0.1f, 
					   CoolWildness.PArr[o].Pos.V[1] + 0.1f,
					   CoolWildness.PArr[o].Pos.V[2]);
			glVertex3f(CoolWildness.PArr[o].Pos.V[0] - 0.1f, 
					   CoolWildness.PArr[o].Pos.V[1] + 0.1f,
					   CoolWildness.PArr[o].Pos.V[2]);
		}

	glEnd();
	glFlush ();													// Flush The GL Rendering Pipeline
}
