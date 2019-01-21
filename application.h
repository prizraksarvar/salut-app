//
// Sarvar Khasanov
//

#ifndef SALUTAPP_APPLICATION_H_
#define SALUTAPP_APPLICATION_H_

#include <windows.h>

// Contains Information of Application
class Application
{
public:
	HINSTANCE		hInstance;
	const char*		className;

	BOOL RegisterWindowClass(WNDPROC WindowMessageProccess);
};


#endif