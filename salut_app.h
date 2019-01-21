//
// Sarvar Khasanov
//

#ifndef SALUTAPP_SALUTAPP_H_
#define SALUTAPP_SALUTAPP_H_

#include <windows.h>

#define SALUTAPP_TITLE "Salut App"

// Application entry point
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow);

// Proccess window events
LRESULT CALLBACK WindowMessageProccess(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

#endif
