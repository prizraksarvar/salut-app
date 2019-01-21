//
// Sarvar Khasanov
//

#ifndef SALUTAPP_FIREWORK_H_
#define SALUTAPP_FIREWORK_H_

#include <vector>
#include "vector3f.h"
#include "color4f.h"
#include "particle.h"

// Firework settings
#define SALUTAPP_FIREWORK_TIMEOUT 0.8f
#define SALUTAPP_FIREWORK_LIFE 0
#define SALUTAPP_FIREWORK_PARTICLE_COUNT_MIN 20
#define SALUTAPP_FIREWORK_PARTICLE_COUNT_MAX 400

// Firework Particle settings
#define SALUTAPP_FIREWORK_PARTICLE_LIFE 0.5f
#define SALUTAPP_FIREWORK_PARTICLE_TIME_BEFORE_SPLIT 0.1f
#define SALUTAPP_FIREWORK_PARTICLE_HIDE_TIMEOUT 1.2f
#define SALUTAPP_FIREWORK_PARTICLE_SPEED_MIN 100
#define SALUTAPP_FIREWORK_PARTICLE_SPEED_MAX 500

using namespace std;

class Firework
{
public:
	Vector3f		position;
	float			timer; // Time to fly from ground to explode
	float			life; // Time to particle explode
	Color4f			color;
	int				particleCount;
	float			particleSize;
	float			explosionPower;
	
	Firework(Vector3f& iposition);
	void Explode(vector <Particle>& particles);
};

#endif
