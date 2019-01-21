//
// Sarvar Khasanov
//
// Functions for help load texture
//

#include "texture_loader.h"
#undef _UNICODE
#include "il.h"

#pragma comment( lib, "./libs/DevIL.lib" )

GLuint LoadImage(const char *fileName, BOOL hasAlfa)
{
	ilInit();
	ILboolean result = ilLoadImage(fileName);
	if (!result) {
		ILenum err = ilGetError();
		const char* s = ilGetString(err);
		return FALSE;
	}
	ILubyte * bytes = ilGetData();
	int size = ilGetInteger(IL_IMAGE_SIZE_OF_DATA);
	int width = ilGetInteger(IL_IMAGE_WIDTH);
	int height = ilGetInteger(IL_IMAGE_HEIGHT);

	GLuint texture;
	glGenTextures(1, &texture);
	glBindTexture(GL_TEXTURE_2D, texture);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	if (hasAlfa)
	{
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, bytes);
	}
	else
	{
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, bytes);
	}
	GLenum g = glGetError();
	return texture;
}