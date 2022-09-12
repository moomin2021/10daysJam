#include"Particle.h"
#include"Util.h"
#include"DxLib.h"
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

void Particle::Draw(Camera camera_, int color, int graph) {
	Circle a = { obj.pos + camera_.GetPos(),obj.radius };
	//if (isAcive)DrawCircle(a, color, true);

	Color c = HexadecimalColor(color);
	int posX1 = a.pos.x - obj.radius;
	int posX2 = a.pos.x + obj.radius;
	int posY1 = a.pos.y - obj.radius;
	int posY2 = a.pos.y + obj.radius;
	SetDrawBright(c.red, c.green, c.blue);
	for (int i = 0; i < 2; i++) {
		DrawExtendGraph(posX1, posY1, posX2, posY2, graph, true);
	}
	SetDrawBright(255, 255, 255);
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
