//
// Sarvar Khasanov
//

#ifndef SALUTAPP_ISCENE_H_
#define SALUTAPP_ISCENE_H_

#include <windows.h>
#include <vector>
#include "particle.h"
#include "cloud.h"

using namespace std;

// Interface for all future scene
class IScene {
public:
	virtual BOOL Initialize() = 0;
	virtual void Deinitialize() = 0;
	virtual void Update(DWORD milliseconds) = 0;
	virtual vector <Particle>& GetParticles() = 0;
	virtual void AddFirework(Vector3f& point) = 0;
	virtual unsigned int GetSkyTexture() = 0;
	virtual vector <Cloud>& GetClouds() = 0;
};

#endif