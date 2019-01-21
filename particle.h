//
// Sarvar Khasanov
//

#ifndef SALUTAPP_PARTICLE_H_
#define SALUTAPP_PARTICLE_H_

#include "color4f.h"
#include "vector3f.h"

// Single particle
typedef struct
{
	Vector3f		position;
	Vector3f		velocity;
	float			life;
	float			hideTimeout;
	Color4f			color;
	Vector3f		size;
	float			massa;
	float			timeBeforeSplit;
} Particle;

#endif