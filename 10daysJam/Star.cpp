#include "Star.h"
using namespace Util;
#include"DxLib.h"

void Star::Initialize(Circle obj_, float radian_, float len_, int maxParticle)
{

	len = len_;
	state = State::Normal;
	radian = radian_;
	float rad = radian - 90;
	obj.pos.x += (len * cosf(rad / 180 * PI));
	obj.pos.y += (len * sinf(rad / 180 * PI));

	for (int i = 0; i < maxParticle; i++) {
		Particle newParticle;
		newParticle.SetParent(obj.pos);
		newParticle.SetState(ParticleState::Endress);
		newParticle.Initialize();
		starParticle.push_back(newParticle);
	}
}

void Star::Update(Line hourHand)
{
	if (state == State::Normal) {
		radian += spd;
		float rad = radian - 90;
		obj.pos.x = (len * cosf(rad / 180 * PI)) + hourHand.start.x;
		obj.pos.y = (len * sinf(rad / 180 * PI)) + hourHand.start.y;

		for (int i = 0; i < starParticle.size(); i++) {
			starParticle[i].SetParent(obj.pos);
			starParticle[i].SetRadian(rad - 90);
			starParticle[i].Update();
		}
	}
}

void Star::SetSpd(float s)
{
	spd = s;
}

void Star::Draw(Camera camera_, int color)
{
	SetDrawBlendMode(DX_BLENDMODE_ADD, 256);
	for (int i = 0; i < starParticle.size(); i++) {
		starParticle[i].Draw(camera_, color);
	}
	Circle c;
	c = obj;
	c.pos += camera_.GetPos();
	DrawCircle(c, color, true);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 256);
}
