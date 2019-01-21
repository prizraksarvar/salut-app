//
// Sarvar Khasanov
//

#ifndef SALUTAPP_SCENE_H_
#define SALUTAPP_SCENE_H_

#include <windows.h>
#include <vector>
#include "iscene.h"
#include "particle.h"
#include "firework.h"
#include "vector3f.h"
#include "cloud.h"

// Textures settings
#define SALUTAPP_TEXTURE_CLOUD "./resourses/cloud3.png"
#define SALUTAPP_TEXTURE_SKY "./resourses/sky.png"

// Firework add settings
#define SALUTAPP_FIREWORK_ROCKET_LIFE_TIME 1.0f
#define SALUTAPP_FIREWORK_ROCKET_HIDE_TIME 1.2f


using namespace std;

// Scene with firework
class Scene : public IScene
{
public:
	BOOL Initialize();
	void Deinitialize();
	void Update(DWORD milliseconds);
	void AddFirework(Vector3f& point);
	vector <Particle>& GetParticles();
	unsigned int GetSkyTexture();
	vector <Cloud>& GetClouds();
private:
	vector <Particle> particles;
	vector <Particle> particlesSecond;
	vector <Firework> fireworks;
	vector <Firework> fireworksSecond;
	vector <Cloud> clouds;
	unsigned int skyTexture;
	unsigned int cloudTexture;
	BOOL isSwitchedToSecond; // Switcher to second buffer

	void LoadTextures();
	inline void ProccessClouds(float frameTime);
	inline void ProccessFireworks(float frameTime);
	inline void ProccessParticles(float frameTime);
	inline void SplitParticle(Particle& particle); // Split Particle to make firework tails
	vector <Firework>& GetFireworks();
};


#endif