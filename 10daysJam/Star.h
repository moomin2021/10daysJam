#pragma once
#include"Util.h"
#include"Particle.h"
#include<vector>

class Star
{
private:
	Circle obj;
	std::vector<Particle> starParticle;
	State state;

	float radian;
	float len;
	float spd = 0.4;

	
public:
	void Initialize(Circle obj_,float radian_,float len_,int maxParticle);

	void Update(Line hourHand);
	void SetSpd(float s);

	void Draw(Camera camera_,int color,int graph);
};

