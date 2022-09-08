#include "BreakEffect.h"
using namespace Util;

BreakEffect::BreakEffect() {

}

BreakEffect::~BreakEffect() {

}


void BreakEffect::Update() {

	//デスタイマーが0なら殺す
	if (deathTimer <= 0) {
		isAlive = false;
	}//0以上なら
	else if (deathTimer-- > 0) {
		//速度をラジアンを参照して調整
		Vector2 speed;
			speed.x = spd + cosf(radian / 180 * PI);
			speed.y = spd + sinf(radian / 180 * PI);

			//速度を座標に代入
			obj.pos += speed;
	}
}

void BreakEffect::Draw(Camera camera_) {
	Circle pos = obj;
	pos.pos = camera_.GetPos();
	DrawCircle(pos, color, true);
}

void BreakEffect::Initialize(Vector2 pos) {
	color = 0xffffff;
	obj.pos = pos;
	obj.radius = Random(2, 6);
	spd = 5.0f;
	radian = Random(0.0f, 360.0f);
	deathTimer = lifeTime;
	isAlive = true;
}


