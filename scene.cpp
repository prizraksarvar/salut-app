//
// Sarvar Khasanov
//
// Scene with firework
//

#include <windows.h>
#include "scene.h"
#include "user_math.h"
#include "texture_loader.h"

using namespace std;

BOOL Scene::Initialize()
{
	LoadTextures();
	clouds.push_back(Cloud(Vector3f(0,100,0),Vector3f(5,5,0),Vector3f(200,200,0),cloudTexture));
	clouds.push_back(Cloud(Vector3f(300,500,0),Vector3f(5,5,0),Vector3f(200,200,0),cloudTexture));
	return TRUE;
}

void Scene::Deinitialize()
{

}

void Scene::Update(DWORD milliseconds)
{
	float frameTime = (float)milliseconds / 1000.0f;

	ProccessClouds(frameTime);
	ProccessFireworks(frameTime);
	ProccessParticles(frameTime);

	isSwitchedToSecond = !isSwitchedToSecond; // Switch buffers
}

void Scene::AddFirework(Vector3f& point)
{
	Firework* f = new Firework(point);
	GetFireworks().push_back(*f);
	float time = SALUTAPP_FIREWORK_ROCKET_LIFE_TIME;
	Particle& p = Particle();
	p.color = Color4f(1,1,0,1);
	p.life = time - 0.4f;
	p.hideTimeout = SALUTAPP_FIREWORK_ROCKET_HIDE_TIME;
	p.massa = 1;
	p.position = Vector3f(500,0,0);
	p.velocity = Vector3f((point.Vector.x - 500) / (time - 0.2), point.Vector.y / (time - 0.2), 0);
	p.size = Vector3f(5,5,5);
	p.timeBeforeSplit = 0.05;
	GetParticles().push_back(p);
}

void Scene::ProccessClouds(float frameTime)
{
	int c = clouds.size() - 1;
	for (int i = c; i >= 0; i--)
	{
		Cloud& cloud = clouds.at(i);
		cloud.position.Vector.x += cloud.velocity.Vector.x * frameTime;
		cloud.position.Vector.y += cloud.velocity.Vector.y * frameTime;
		if (cloud.position.Vector.x<=0 || cloud.position.Vector.x + cloud.size.Vector.x >= 1000)
		{
			cloud.velocity.Vector.x = -cloud.velocity.Vector.x;
		}
		if (cloud.position.Vector.y <= 0 || cloud.position.Vector.y + cloud.size.Vector.y >= 1000)
		{
			cloud.velocity.Vector.y = -cloud.velocity.Vector.y;
		}
	}
}

void Scene::ProccessFireworks(float frameTime)
{
	vector <Firework>& fireworks = GetFireworks();
	int c = fireworks.size() - 1;
	for (int i = c; i >= 0; i--)
	{
		Firework& f = fireworks.at(i);
		f.timer -= frameTime;
		if (f.timer < 0)
		{
			f.Explode(particles);
			f.life -= frameTime;
			if (f.life < 0)
			{
				continue;
			}
		}
		(isSwitchedToSecond ? this->fireworks : this->fireworksSecond).push_back(f);
	}

	fireworks.clear();
}

void Scene::ProccessParticles(float frameTime)
{
	vector <Particle>& particles = GetParticles();
	int c = particles.size() - 1;

	for (int i = c; i >= 0; i--)
	{
		Particle& particle = particles.at(i);
		particle.life -= frameTime;
		if (particle.hideTimeout < 0)
		{
			continue;
		}

		// Particle hide
		if (particle.life < 0)
		{
			particle.hideTimeout -= frameTime;

			// Colorize before hide
			if (particle.color.RGB.r > particle.color.RGB.g && particle.color.RGB.r > particle.color.RGB.b)
			{
				particle.color.RGB.r *= 1.1f;
				particle.color.RGB.g *= 0.9f;
				particle.color.RGB.b *= 0.9f;
			}
			else if (particle.color.RGB.g > particle.color.RGB.r && particle.color.RGB.g > particle.color.RGB.b)
			{
				particle.color.RGB.r *= 0.9f;
				particle.color.RGB.g *= 1.1f;
				particle.color.RGB.b *= 0.9f;
			}
			else
			{
				particle.color.RGB.r *= 0.9f;
				particle.color.RGB.g *= 0.9f;
				particle.color.RGB.b *= 1.1f;
			}


			if (particle.hideTimeout < 0.5)
			{
				particle.color.RGB.a -= 0.1;
				if (particle.color.RGB.a <= 0)
				{
					continue;
				}
			}
		}

		float airSizeResist = 1; // (1.0f - particle.size.Vector.x / 15);
		// TODO: Need add "air resist" slow down depending of size
		particle.position.Vector.x += particle.velocity.Vector.x * airSizeResist * frameTime;
		particle.position.Vector.y += particle.velocity.Vector.y * airSizeResist * frameTime;
		particle.position.Vector.z += particle.velocity.Vector.z * airSizeResist * frameTime;

		particle.velocity.Vector.y -= particle.massa * 200 * frameTime;

		particle.timeBeforeSplit -= frameTime;
		if (particle.timeBeforeSplit < 0)
		{
			particle.timeBeforeSplit = 0.01f + c * 0.0000001f;
			SplitParticle(particle);
		}

		(isSwitchedToSecond ? this->particles : this->particlesSecond).push_back(particle);
	}
	
	particles.clear();
}

inline void Scene::SplitParticle(Particle& particle)
{
	// TODO: I think need in future make split count depend from mass
	for (int i = particle.size.Vector.x; i > 0; i--)
	{
		Particle newParticle = Particle(particle);
		newParticle.life *= 0.1f;
		newParticle.hideTimeout *= 0.7f;
		newParticle.massa *= 0.1f;
		newParticle.size *= 0.1;
		newParticle.velocity.Vector.x = newParticle.velocity.Vector.x * 0.1 + getRandomFloat(-10, 10);
		newParticle.velocity.Vector.y = newParticle.velocity.Vector.y * 0.1 + getRandomFloat(-10, 10);
		newParticle.velocity.Vector.z = newParticle.velocity.Vector.z * 0.1 + getRandomFloat(-10, 10);
		newParticle.timeBeforeSplit = 1000;
		(isSwitchedToSecond ? this->particles : this->particlesSecond).push_back(newParticle);
	}
}

vector <Particle>& Scene::GetParticles()
{
	return isSwitchedToSecond ? particlesSecond : particles;
}

vector <Firework>& Scene::GetFireworks()
{
	return isSwitchedToSecond ? fireworksSecond : fireworks;
}

void Scene::LoadTextures()
{
	cloudTexture = LoadImage(SALUTAPP_TEXTURE_CLOUD, TRUE);
	skyTexture = LoadImage(SALUTAPP_TEXTURE_SKY, FALSE);
}

unsigned int Scene::GetSkyTexture()
{
	return skyTexture;
}

vector <Cloud>& Scene::GetClouds()
{
	return clouds;
}