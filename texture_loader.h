//
// Sarvar Khasanov
//

#ifndef SALUTAPP_TEXTURE_LOADER_RENDER_H_
#define SALUTAPP_TEXTURE_LOADER_RENDER_H_

#include <Windows.h>
#include <string>
#include <gl/GL.h>
#include <gl/GLU.h>

// Load image for OpenGL
GLuint LoadImage(const char *fileName, BOOL hasAlfa);

#endif
