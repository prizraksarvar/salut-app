//
// Sarvar Khasanov
//

#ifndef SALUTAPP_CLOUD_H_
#define SALUTAPP_CLOUD_H_

#include "vector3f.h"

// Cloud in sky
struct Cloud {
	Vector3f position;
	Vector3f velocity;
	Vector3f size;
	unsigned int texture;

	Cloud(Vector3f iposition, Vector3f ivelocity, Vector3f isize, unsigned int icloudsTexture)
	{
		position = iposition;
		velocity = ivelocity;
		size = isize;
		texture = icloudsTexture;
	}
};

#endif