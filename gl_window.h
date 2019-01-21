//
// Sarvar Khasanov
//
// class GLWindowInit
// class GLWindow
//

#ifndef SALUTAPP_GL_WINDOW_H_
#define SALUTAPP_GL_WINDOW_H_

#include <windows.h>
#include "application.h"
#include "iscene.h"
#include "scene_render.h"

struct Point {
	int x;
	int y;
};

//Window creation info
class GLWindowInit
{
public:
	Application*		application;
	char*				title;
	int					width;
	int					height;
	int					bitsPerPixel;

	void ReshapeGL(int width, int height);
	BOOL ChangeScreenResolution(int width, int height, int bitsPerPixel);
};

// Contains Information Vital To A Window
class GLWindow {									
public:
	Point*				mouseClickPosition;
	HWND				hWnd;
	HDC					hDC;
	HGLRC				hRC;
	GLWindowInit		init;
	BOOL				isVisible;
	DWORD				lastTickCount;
	BOOL				isProgramLooping;
	IScene*				scene;
	SceneRender*		sceneRender;
	Vector3f			viewPosition;
	float				viewAngle;

	BOOL CreateWindowGL();
	BOOL DestroyWindowGL();
	void TerminateApplication();

	BOOL Initialize();
	void Deinitialize();
	void Update(DWORD milliseconds);
	void Draw();
	void MouseClick(Point* clickPosition);
};

#endif