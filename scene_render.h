//
// Sarvar Khasanov
//

#ifndef SALUTAPP_SCENE_RENDER_H_
#define SALUTAPP_SCENE_RENDER_H_

#include "iscene.h"

class SceneRender
{
public:
	void Draw(IScene& scene, Vector3f pos, float angle, int width, int height);
private:
	inline void DrawCircle(Particle& p, float radius, Vector3f pos);
	inline void LoadSky(unsigned int texture, int width, int height);
	inline void DrawParticles(IScene& scene);
	inline void DrawClouds(IScene& scene);
};

#endif