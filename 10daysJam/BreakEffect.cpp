#include "BreakEffect.h"
using namespace Util;

BreakEffect::BreakEffect() {

}

BreakEffect::~BreakEffect() {

}


void BreakEffect::Update() {

	//�f�X�^�C�}�[��0�Ȃ�E��
	if (deathTimer <= 0) {
		isAlive = false;
	}//0�ȏ�Ȃ�
	else if (deathTimer-- > 0) {
		//���x�����W�A�����Q�Ƃ��Ē���
		Vector2 speed;
			speed.x = spd + cosf(radian / 180 * PI);
			speed.y = spd + sinf(radian / 180 * PI);

			//���x�����W�ɑ��
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


