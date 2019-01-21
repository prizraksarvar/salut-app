//
// Sarvar Khasanov
//
// Firework
//

#include <windows.h>
#include <vector>
#include <math.h>
#include "firework.h"
#include "particle.h"
#include "color4f.h"
#include "vector3f.h"
#include "user_math.h"

using namespace std;

Firework::Firework(Vector3f& iposition)
{
	this->position = Vector3f(iposition);
	this->particleCount = getRandomInt(SALUTAPP_FIREWORK_PARTICLE_COUNT_MIN, SALUTAPP_FIREWORK_PARTICLE_COUNT_MAX);
	int r = getRandomInt(0, 2);
	this->color = Color4f(1.0f / (float)(rand() % 10) + (r==0 ? 1.0f : 0.4f),
		1.0f / (float)(rand() % 10) + (r == 1 ? 1.0f : 0.4f),
		1.0f / (float)(rand() % 10) + (r == 2 ? 1.0f : 0.4f),
		1.0f);
	this->timer = SALUTAPP_FIREWORK_TIMEOUT;
	this->life = SALUTAPP_FIREWORK_LIFE;
	this->particleSize = getRandomFloat(1,5);
	this->explosionPower = getRandomFloat()/2 + 0.5;
}


void Firework::Explode(vector <Particle>& particles)
{
	float rotation = getRandomFloat(0, 10);
	for (int i = this->particleCount; i > 0; i--)
	{
		Particle p = Particle();
		p.color = Color4f(this->color);
		p.life = SALUTAPP_FIREWORK_PARTICLE_LIFE;
		p.massa = getRandomFloat(-0.1,3);
		p.position = Vector3f(this->position);
		p.size = Vector3f(this->particleSize, this->particleSize, this->particleSize);
		p.timeBeforeSplit = SALUTAPP_FIREWORK_PARTICLE_TIME_BEFORE_SPLIT;
		p.hideTimeout = SALUTAPP_FIREWORK_PARTICLE_HIDE_TIMEOUT;
		
		float speed = getRandomFloat(SALUTAPP_FIREWORK_PARTICLE_SPEED_MIN, SALUTAPP_FIREWORK_PARTICLE_SPEED_MAX);
		float angle = getRandomInt(0, 36)*10.0f + rotation;
		float angleZ = getRandomInt(0, 18)*10.0f + rotation;
		
		float k = speed * cosf(angle);
		float l = speed * sinf(angle);
		float m = speed * sinf(angleZ);

		p.velocity = Vector3f(k*this->explosionPower, l*this->explosionPower, m*this->explosionPower);
		particles.push_back(p);
	}
}
