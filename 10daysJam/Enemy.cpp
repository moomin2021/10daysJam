#include "Enemy.h"
using namespace Util;

// --�R���X�g���N�^-- //
Enemy::Enemy() {}

Enemy::Enemy(Vector2 pos, float radius) : enemy{ pos, radius } {

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
	Vector2 lenVec = hourLine_.start - enemy.pos;
	float len = lenVec.length();
	//�����ƒZ�j�̊p�x���玩���W���Čv�Z���đ��
	enemy.pos.x = (len * cosf((hourLine_.radian - 90) / 180 * PI)) + hourLine_.start.x;
	enemy.pos.y = (len * sinf((hourLine_.radian - 90) / 180 * PI)) + hourLine_.start.y;
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
		enemy.pos + camera_.GetPos(),
		enemy.radius
	};
	DrawCircle(pos, color, true);
}

void Enemy::SetState(State state_)
{
	state = state_;
}

//void Enemy::AllEnemyDeath()
//{
//	enemys.clear();
//}
