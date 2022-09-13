#include "BreakEffect.h"
#include"DxLib.h"
using namespace Util;

BreakEffect::BreakEffect() {
	
}

BreakEffect::~BreakEffect() {

}


void BreakEffect::Update() {

	//デスタイマーが0か半径が0以下なら殺す
	if (deathTimer <= 0 || obj.radius <= 0) {
		isAlive = false;
	}//0以上なら
	else if (deathTimer-- > 0) {
		//速度をラジアンを参照して調整
		Vector2 speed;
			speed.x = spd * cosf(radian / 180 * PI);
			speed.y = spd * sinf(radian / 180 * PI);

			//速度を座標に代入
			obj.pos += speed;

			//半径を少し小さくする
			obj.radius -= 0.25f;
	}
}

void BreakEffect::Draw(Camera camera_,int graph) {
	Circle pos = obj;
	pos.pos += camera_.GetPos();
	//DrawCircle(pos, color, true);
	pos.radius += 4;

	int posX1 = pos.pos.x - pos.radius;
	int posX2 = pos.pos.x + pos.radius;
	int posY1 = pos.pos.y - pos.radius;
	int posY2 = pos.pos.y + pos.radius;
	DrawExtendGraph(posX1, posY1, posX2, posY2, graph, true);
}

void BreakEffect::Initialize(Vector2 pos) {
	color = 0xffffff;
	obj.pos = pos;
	obj.radius = Random(4, 12);
	spd = Random(8.0f,15.0f);
	radian = Random(0.0f, 360.0f);
	deathTimer = lifeTime;
	isAlive = true;
}


