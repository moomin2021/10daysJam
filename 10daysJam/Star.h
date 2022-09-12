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
public:
	void Initialize(Circle obj_,float radian_,float len_,int maxParticle);

	void Update(Line hourHand);

	void Draw(Camera camera_,int color);
};

