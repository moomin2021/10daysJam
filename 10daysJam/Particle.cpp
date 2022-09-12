#include"Particle.h"
#include"Util.h"
using namespace Util;

void Particle::Update() {


	//速度、角度で座標に加算
	obj.pos.x += Spd * cosf(radian / 180 * PI);
	obj.pos.y += Spd * sinf(radian / 180 * PI);

	//大きさをランダムに減らす
	obj.radius -= Random(0.0f, 0.5f);

	radian += Random(0.0f, 5.0f);

	//大きさが0以下かつステートがエンドレスなら再初期化
	if (obj.radius <= 0) {
		if (state == ParticleState::Endress) {
			Initialize();
		}
		else {
			isAcive = false;
		}
	}

}

void Particle::Draw(Camera camera_,int color){
	Circle a = { obj.pos + camera_.GetPos(),obj.radius };
	DrawCircle(a, color, true);
}

void Particle::Initialize(bool stateReset) {
	obj.pos = parent;
	obj.radius = Random(3.0f, 8.0f);
	radian = Random(0.0f, 360.0f);
	isAcive = true;
	Spd = Random(0.0f, 3.0f);
	if (stateReset) {
		state = ParticleState::Normal;
	}
	
}

void Particle::SetParent(Vector2 pos) {
	parent = pos;
}

void Particle::SetState(ParticleState state_)
{
	state = state_;
}

void Particle::SetSpeed(float s)
{
	Spd = s;
}

void Particle::SetColor(int color_)
{
	color = color_;
}

void Particle::SetRadian(int radian_)
{
	radian = radian_;
}
