//
// Sarvar Khasanov
//
// Salut App 
//
// Entry point and proccess event
//

#include <windows.h>
#include <windowsx.h>
#include "salut_app.h"
#include "gl_window.h"

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	Application			application;
	GLWindow			window;
	BOOL				isMessagePumpActive;
	MSG					msg;
	DWORD				tickCount;

	application.className = "OpenGL";
	application.hInstance = hInstance;


	ZeroMemory(&window, sizeof(GLWindow));
	window.init.application = &application;
	window.init.title = SALUTAPP_TITLE;
	window.init.width = 640;
	window.init.height = 640;
	window.init.bitsPerPixel = 32;


	if (!application.RegisterWindowClass((WNDPROC)WindowMessageProccess))
	{
		MessageBox(HWND_DESKTOP, "Error Registering Window Class!", "Error", MB_OK | MB_ICONEXCLAMATION);
		return -1;
	}
	
	window.isProgramLooping = TRUE;

	if (!window.CreateWindowGL())
	{
		MessageBox(HWND_DESKTOP, "Error Creating OpenGL Window", "Error", MB_OK | MB_ICONEXCLAMATION);
		window.isProgramLooping = FALSE;
	} 
	else if (!window.Initialize())
	{
		window.TerminateApplication();
	}

	int limit = 1000 / 62; // ~65 Fps

	while (window.isProgramLooping)
	{
		tickCount = GetTickCount();
		// Fps limitation
		if (tickCount - window.lastTickCount < limit) {
			continue;
		}
		isMessagePumpActive = TRUE;
		while (PeekMessage(&msg, window.hWnd, 0, 0, PM_REMOVE) != 0)
		{
			if (msg.message != WM_QUIT)
			{
				DispatchMessage(&msg);
			}
			else
			{
				isMessagePumpActive = FALSE;
			}
		}
		if (window.isVisible == FALSE)
		{
			WaitMessage();
		}
		else
		{
			window.scene->Update(tickCount - window.lastTickCount);
			window.lastTickCount = tickCount;
			window.sceneRender->Draw(*window.scene, window.viewPosition, window.viewAngle, window.init.width, window.init.height);
			SwapBuffers(window.hDC);
		}
	}

	window.Deinitialize();
	window.DestroyWindowGL();

	UnregisterClass(application.className, application.hInstance);
	return 0;
}


LRESULT CALLBACK WindowMessageProccess(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{

	GLWindow* window = (GLWindow*)(GetWindowLong(hWnd, GWL_USERDATA));

	switch (uMsg)
	{
	case WM_SYSCOMMAND:
	{
		switch (wParam)
		{
		case SC_SCREENSAVE:
		case SC_MONITORPOWER:
			return 0;
		}
		break;
	}
	return 0;

	case WM_CREATE:
	{
		CREATESTRUCT* creation = (CREATESTRUCT*)(lParam);
		window = (GLWindow*)(creation->lpCreateParams);
		SetWindowLong(hWnd, GWL_USERDATA, (LONG)(window));
	}
	return 0;

	case WM_CLOSE:
		window->TerminateApplication();
		return 0;

	case WM_SIZE:
		switch (wParam)
		{
		case SIZE_MINIMIZED:
			window->isVisible = FALSE;
			return 0;

		case SIZE_MAXIMIZED:
			window->isVisible = TRUE;
			window->init.ReshapeGL(LOWORD(lParam), HIWORD(lParam));
			return 0;

		case SIZE_RESTORED:
			window->isVisible = TRUE;
			window->init.ReshapeGL(LOWORD(lParam), HIWORD(lParam));
			return 0;
		}
		break;
	case WM_LBUTTONUP:
		if ((wParam >= 0) && (wParam <= 255))
		{
			window->mouseClickPosition->x = GET_X_LPARAM(lParam);
			window->mouseClickPosition->y = GET_Y_LPARAM(lParam);
			window->MouseClick(window->mouseClickPosition);
			return 0;
		}
		break;
	case WM_LBUTTONDOWN:

		break;
	case WM_KEYDOWN:
		// Controls for 3D view
		/*int step = 20;
		switch (wParam)
		{
		case VK_ESCAPE:
			break;
		case VK_UP:
			window->viewPosition += Vector3f(0, step,0);
			break;
		case VK_DOWN:
			window->viewPosition += Vector3f(0,-step, 0);
			break;
		case VK_LEFT:
			window->viewPosition += Vector3f(step, 0, 0);
			break;
		case VK_RIGHT:
			window->viewPosition += Vector3f(-step, 0, 0);
			break;
		case 'A':
			window->viewPosition += Vector3f(0, 0, step);
			break;
		case 'D':
			window->viewPosition += Vector3f(0, 0, -step);
			break;
		case 'Q':
			window->viewAngle += 0.3;
			break;
		case 'E':
			window->viewAngle -= 0.3;
			break;
		}*/
		break;
	}

	return DefWindowProc(hWnd, uMsg, wParam, lParam);
}
