#include "Enemy.h"
using namespace Util;

// --�R���X�g���N�^-- //
Enemy::Enemy() {}

Enemy::Enemy(Vector2 pos, float radius) : obj{ pos, radius } {

}

// --�f�X�g���N�^-- //
Enemy::~Enemy() {

}

// --����������-- //
void Enemy::Initialize() {

}

// --�X�V����-- //
void Enemy::Update(Line hourLine_) {

	switch (state)
	{
	case State::Normal:
		UpdateNormal();
		break;
	case State::Reverse:
		UpdateReverse(hourLine_);
		break;
	case State::Stop:
		break;
	case State::Item :
		//�F�����F�ɕύX
		color = 0xffff00;
		break;
	case State::Enemy:
		//�F��ԂɕύX
		color = 0xff0000;
		break;
	case State::Death:
		UpdateDeath(hourLine_.start,hourLine_.length);
	default:
		break;
	}

}

void Enemy::UpdateNormal()
{
}

void Enemy::UpdateReverse(Line hourLine_)
{
	//�Z�j�ɍ��W��Ǐ]������
	//�Z�j�̎n�_�Ǝ����W���璷�����擾
	Vector2 lenVec = hourLine_.start - obj.pos;
	float rad = hourLine_.radian - 90;

	float len = lenVec.length();
	//�����ƒZ�j�̊p�x���玩���W���Čv�Z���đ��
	obj.pos.x = (len * cosf((rad) / 180 * PI)) + (obj.radius * cosf((rad-90) / 180 * PI))+ hourLine_.start.x;
	obj.pos.y = (len * sinf((rad) / 180 * PI)) + (obj.radius * sinf((rad-90) / 180 * PI))+ hourLine_.start.y;

	//�F�𖾂�߂̃I�����W��
	color = 0xff7c17;
}

void Enemy::UpdateDeath(Vector2 afterPos, float randParam) {
	//�n�܂�Ȃ�
	bezire.divisionNum = 32;
	if (effectTime == 0) {
		//�x�W�G�Ȑ��̍��W������
		//float len = obj.radius;
		for (int i = 0; i < 4; i++) {
			Vector2 pos;
			int rad = Random(0.0f, 360.0f);
			if (i == 0) {
				pos = obj.pos;
			}
			else if (i == 3) {
				pos = afterPos;
			}
			else {
				Vector2 a = obj.pos - afterPos;
				pos.x = Random(-randParam, randParam)+ afterPos.x;
				pos.y = Random(-randParam, randParam)+ afterPos.y;
			}
			bezire.SetControllPoint(pos, i);
		}
		
		//�x�W�G�Ȑ��̍X�V
		bezire.Update();
	}



	if (effectTime < bezire.divisionNum) {
		obj.pos = bezire.pos[effectTime];
		effectTime++;
	}

	//���a�����������ĐF�𐅐F��
	obj.radius = 6.0f;
	color = 0x45efff;

}


void Enemy::OnCollison()
{
	//�X�e�[�g�𔽓]��
	state = State::Reverse;
		//color = 0x7fff7f;
}

// --�`�揈��-- //
void Enemy::Draw(Camera camera_) {
	Circle pos ={
		obj.pos + camera_.GetPos(),
		obj.radius
	};
	DrawCircle(pos, color, true);
}

void Enemy::SetState(State state_)
{
	state = state_;

}

void Enemy::StateChange()
{
	isChange = true;
}


//void Enemy::AllEnemyDeath()
//{
//	enemys.clear();
//}
