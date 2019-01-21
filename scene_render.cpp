//
// Sarvar Khasanov
//
// Render scene on window
//

#include <windows.h>
#include <vector>
#include <gl\gl.h>
#include <gl\glu.h>
#include "scene_render.h"
#include "iscene.h"
#include "particle.h"
#include "cloud.h"

using namespace std;

void SceneRender::Draw(IScene& scene, Vector3f pos, float angle, int width, int height)
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();
	glTranslatef(0.0f, 0.0f, 0.0f);
	glTranslatef(pos.V[0], pos.V[1], -20 + pos.V[2]);

	GLfloat ambientLight[] = { 0.2f, 0.2f, 0.2f, 1.0f };
	glLightModelfv(GL_LIGHT_MODEL_AMBIENT, ambientLight);

	GLfloat directedLight[] = { 0.7f, 0.7f, 0.7f, 1.0f };
	GLfloat directedLightPos[] = { -10.0f, 15.0f, 20.0f, 0.0f };
	glLightfv(GL_LIGHT0, GL_DIFFUSE, directedLight);
	glLightfv(GL_LIGHT0, GL_POSITION, directedLightPos);


	LoadSky(scene.GetSkyTexture(), width, height);
	DrawClouds(scene);
	DrawParticles(scene);
	

	glFlush();
}

inline void SceneRender::LoadSky(unsigned int texture, int width, int height)
{
	glEnable(GL_TEXTURE_2D);

	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);
	glColor3f(1.0f, 0.2f, 0.2f);
	glBindTexture(GL_TEXTURE_2D, texture);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glBegin(GL_QUADS);

	int z = 0;
	glVertex3f(0, 0, z); glTexCoord2f(0, 0);
	glVertex3f(0, height, z); glTexCoord2f(0, 1);
	glVertex3f(width, height, z); glTexCoord2f(1, 1);
	glVertex3f(width, 0, z); glTexCoord2f(1, 0);
	glEnd();
	glDisable(GL_TEXTURE_2D);
}

inline void SceneRender::DrawParticles(IScene& scene)
{
	vector <Particle> particles = scene.GetParticles();
	glBegin(GL_POINTS);

	float size = 0.2f;

	for (int i = particles.size() - 1; i >= 0; i--)
	{
		Particle& p = particles.at(i);
		glColor4fv(&p.color.C[0]);
		glVertex3f(p.position.V[0] - size * p.size.Vector.x,
			p.position.V[1] - size * p.size.Vector.y,
			p.position.V[2] * 0);
	}

	glEnd();
}

inline void SceneRender::DrawClouds(IScene& scene)
{
	vector <Cloud> clouds = scene.GetClouds();

	float size = 0.2f;

	for (int i = clouds.size() - 1; i >= 0; i--)
	{
		Cloud& cloud = clouds.at(i);
		glEnable(GL_TEXTURE_2D);

		glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);
		glColor4f(0, 0, 0, 0);
		glBindTexture(GL_TEXTURE_2D, cloud.texture);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
		glBegin(GL_QUADS);

		int z = 0;
		glVertex3f(cloud.position.V[0], cloud.position.V[1], z); 
		glTexCoord2f(0, 0);
		glVertex3f(cloud.position.V[0], cloud.position.V[1] + cloud.size.V[1], z); 
		glTexCoord2f(0, 1);
		glVertex3f(cloud.position.V[0] + cloud.size.V[0], cloud.position.V[1] + cloud.size.V[1], z); 
		glTexCoord2f(1, 1);
		glVertex3f(cloud.position.V[0] + cloud.size.V[0], cloud.position.V[1], z); 
		glTexCoord2f(1, 0);
		glEnd();
		glDisable(GL_TEXTURE_2D);
	}
}

void SceneRender::DrawCircle(Particle& p, float radius, Vector3f pos)
{
	glBegin(GL_TRIANGLE_FAN);
	int segmentsCount = 3;
	glVertex3f(p.position.V[0], p.position.V[1], p.position.V[2]);
	for (int ii = 0; ii <= segmentsCount; ii++)
	{
		float theta = 2.0f * 3.1415926f * float(ii) / float(segmentsCount);

		float x = radius * cosf(theta);
		float y = radius * sinf(theta);

		glVertex3f(p.position.V[0] + x + pos.Vector.x, p.position.V[1] + y + pos.Vector.y, p.position.V[2] + pos.Vector.z);
	}

	glEnd();
}