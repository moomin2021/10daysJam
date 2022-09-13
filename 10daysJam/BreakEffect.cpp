#include "BreakEffect.h"
#include"DxLib.h"
using namespace Util;

BreakEffect::BreakEffect() {
	
}

BreakEffect::~BreakEffect() {

}


void BreakEffect::Update() {

	//�f�X�^�C�}�[��0�����a��0�ȉ��Ȃ�E��
	if (deathTimer <= 0 || obj.radius <= 0) {
		isAlive = false;
	}//0�ȏ�Ȃ�
	else if (deathTimer-- > 0) {
		//���x�����W�A�����Q�Ƃ��Ē���
		Vector2 speed;
			speed.x = spd * cosf(radian / 180 * PI);
			speed.y = spd * sinf(radian / 180 * PI);

			//���x�����W�ɑ��
			obj.pos += speed;

			//���a����������������
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


