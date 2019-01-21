//===========================================================
//  Filename: remPartMgr.h
//      Particle system based on Policies
//		Very cool approach! I like it :)
//		Read Andrei Alexandrescu Modern C++ Design
//      Copyright 2003
//      Created by Roman E. Marchenko, vortex@library.ntu-kpi.kiev.ua
//      $Id$
//===========================================================

#ifndef _REM_PARTICLE_MANAGER_H_
#define _REM_PARTICLE_MANAGER_H_

#include <time.h>
#include <math.h>
#include "SimpleMath.h"

// Single particle
typedef struct
{
	Vector3f		Pos; // Position of particle in space
	Vector3f		Velocity;
	float			Life;
	Color4f		Color;
	Vector3f		SizeP; // size of particle. 3 dimensions
	Vector3f		Grav;
} CommonParticle;

//-----------------------------------------------------------
//    Initialization Polocies
//    All this polisies must provide 1 operator:
//    inline void operator () (CommonParticle *P)
//-----------------------------------------------------------

struct remInitColor
{
	inline void operator () (CommonParticle *P, double &FrameTime)
	{
		P->Color = Color4f(1.0f/(float)(rand()%10), 
			                  1.0f/(float)(rand()%10), 
							  1.0f/(float)(rand()%10), 0.7f);
	}
}; 

struct remInitColor_Twister
{
	inline void operator () (CommonParticle *P, double &FrameTime)
	{
		P->Color = Color4f(1.0f - (2.0f + P->Pos.Vector.y) / 4.0f, 
			                  (2.0f + P->Pos.Vector.y) / 4.0f, 
							  (2.0f + P->Pos.Vector.y) / 4.0f, 0.7f);
	}
}; 

struct remInitVel_Smoke
{
	inline void operator () (CommonParticle *P, double &FrameTime)
	{
		P->Velocity = Vector3f(0.0f, 2.0f, 0.0f);
	}
}; 

struct remInitVel_Twister
{
	inline void operator () (CommonParticle *P, double &FrameTime)
	{
		P->Velocity = Vector3f(5 * (1 +(float)(rand()%214)/100) , 
								  0.0f, 0.0f);
	}
};

struct remInitPos_Twister
{
	inline void operator () (CommonParticle *P, double &FrameTime)
	{
		float h;
		h = 2.0f - (float)(rand()%40000)/10000;
		P->Pos.Vector.y = h;
		h = 2.0f - (float)(rand()%10000)/10000;
		P->Pos.Vector.x = h + P->Pos.Vector.y / 2;
		P->Pos.Vector.z = 0;
		P->Grav.Vector.x = fabs(P->Pos.Vector.x);
	}
};

struct remInitVel_Explosion
{
	inline void operator () (CommonParticle *P, double &FrameTime)
	{
		P->Velocity = Vector3f(10 - (float)(rand()%200)/10, 
								  10 - (float)(rand()%200)/10, 
								  10 - (float)(rand()%200)/10);
	}
};

struct remInitLife_Twister
{
	inline void operator () (CommonParticle *P, double &FrameTime)
	{
		P->Life = 3;
	}
}; 

struct remInitLife_Smoke
{
	inline void operator () (CommonParticle *P, double &FrameTime)
	{
		P->Life = 1000;
	}
}; 

struct remInitSize
{
	inline void operator () (CommonParticle *P, double &FrameTime)
	{
		P->SizeP = Vector3f(0.2f, 0.2f, 0.0f);
	}
}; 

//-----------------------------------------------------------
//    Update policies
//    Must provide same operator as above
//    void ProcessParticle(CommonParticle *P)
//-----------------------------------------------------------

struct remProcPos_Noise
{
	inline void operator () (CommonParticle *P, double &FrameTime)
	{
		Vector3f g((float)(5-rand()%10), 
					  0.0f, 
					  0.0f);
		g += P->Velocity;
		g.Vector.x *= FrameTime;
		g.Vector.y *= FrameTime;
		g.Vector.z *= FrameTime;
		P->Pos = P->Pos +  g;
	}
}; 

struct remProcPos_Linear
{
	inline void operator () (CommonParticle *P, double &FrameTime)
	{
		Vector3f g = P->Velocity;
		g.Vector.x *= FrameTime;
		g.Vector.y *= FrameTime;
		g.Vector.z *= FrameTime;
		P->Pos = P->Pos + g;
	}
};

struct remProcPos_Twister
{
	inline void operator () (CommonParticle *P, double &FrameTime)
	{
		P->Pos.Vector.x = P->Grav.Vector.x * cos(P->Velocity.Vector.y);
		P->Pos.Vector.z = P->Grav.Vector.x * sin(P->Velocity.Vector.y);
	}
};

struct remProcVel_Twister
{
	inline void operator () (CommonParticle *P, double &FrameTime)
	{
	    P->Velocity.Vector.y += P->Velocity.Vector.x * FrameTime;
	}
};

struct remProcLife
{
	inline void operator () (CommonParticle *P, double &FrameTime)
	{
		P->Life = P->Life - 500.0 * FrameTime;
		P->Color.RGB.a = (float)P->Life/1000.0f;
	}
}; 

//-----------------------------------------------------------
//    Null initialiser
//    Cork for unnecessary policy
//-----------------------------------------------------------

struct remNullPolicy
{
	inline void operator () (CommonParticle *P, double &FrameTime) {}
};

//-----------------------------------------------------------
//    Complete policy for Initialize and Update
//-----------------------------------------------------------

template<class Life, class Pos, class Size, class Vel, class Cl>
class remCompletePolicy
{
public:
	Life	pLife;
	Pos		pPos;
	Size	pSize;
	Vel		pVel;
	Cl		pColor;

	inline void operator () (CommonParticle *P, double &FrameTime)
	{
		pLife(P, FrameTime);
		pVel(P, FrameTime);
		pPos(P, FrameTime);
		pSize(P, FrameTime);
		pColor(P, FrameTime);
	}
};

//-----------------------------------------------------------
//    Composite policy for combininig actions
//-----------------------------------------------------------

template<class PolicyOne, class PolicyTwo>
class remCompositePolicy: public PolicyOne, public PolicyTwo
{
public:
	inline void operator () (CommonParticle *P, double &FrameTime)
	{
		PolicyOne::operator () (P, FrameTime);
		PolicyTwo::operator () (P, FrameTime);
	}
};

template<UINT PCount, class InitPolicy, class UpdatePolicy>
class remParticleManager  
{
public:
	
	InitPolicy		pInit;
	UpdatePolicy	pUpdate;
	CommonParticle	PArr[PCount];
//	UINT			PartCount;
	UINT			CurrCount;
	UINT			i;
	bool			Alive;
	
	inline void Emit(UINT Cnt, Vector3f &PartPos)
	{
		srand((UINT)time(NULL));
		UINT tC = CurrCount;
		for (; (CurrCount < tC + Cnt) && (CurrCount < PCount); CurrCount++)
		{
			PArr[CurrCount].Pos = PartPos;
			double a;
			pInit(&PArr[CurrCount], a);
		}
	}

	inline void Update(double &FrameTime)
	{
		if (Alive)
		{
			for (i = 0; i < CurrCount; i++)
			{
				// Particle dead. Switch with last
				if (PArr[i].Life <= 0)
				{
					PArr[i] = PArr[--CurrCount];
				}
				if (CurrCount == 0) Alive = false;
			}
			for (i = 0; i < CurrCount; i++)
				pUpdate(&PArr[i], FrameTime);
		}
		else CurrCount = 0;
	}

	remParticleManager() 
	{
		Alive = false;
	}
};

// Coomon types of PSystems
typedef remParticleManager
	<100, 
	 remCompletePolicy<remInitLife_Smoke, remNullPolicy, remInitSize, remInitVel_Explosion, remInitColor>,
	 remCompletePolicy<remProcLife, remProcPos_Linear, remNullPolicy, remNullPolicy, remNullPolicy> >
	 pExplosion;

typedef remParticleManager
	<1000, 
	remCompletePolicy<remInitLife_Smoke, remNullPolicy, remInitSize, remInitVel_Smoke, remInitColor>,
	remCompletePolicy<remProcLife, remProcPos_Noise, remNullPolicy, remNullPolicy, remNullPolicy> >
	pSmoke;

typedef remParticleManager
	<1000, 
	remCompletePolicy<remInitLife_Twister, remInitPos_Twister, remInitSize, remInitVel_Twister, remInitColor_Twister>,
	remCompletePolicy<remNullPolicy, remProcPos_Twister, remNullPolicy, remProcVel_Twister, remNullPolicy> >
	pTwister;

typedef remParticleManager
	<1000, 
	remCompletePolicy<remInitLife_Smoke, remNullPolicy, remInitSize, remCompositePolicy<remInitVel_Smoke, remInitVel_Explosion>, remInitColor>,
	remCompletePolicy<remProcLife, remCompositePolicy<remProcPos_Noise, remProcPos_Linear>, remNullPolicy, remNullPolicy, remNullPolicy> >
	pTotalWildness; // :)

#endif
