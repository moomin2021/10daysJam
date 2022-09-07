#include "Enemy.h"
using namespace Util;

// --�R���X�g���N�^-- //
Enemy::Enemy() {}

Enemy::Enemy(Vector2 pos, float radius) : enemy{pos, radius} {

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
}

void Enemy::OnCollison()
{
	color = 0x7fff7f;
}

// --�`�揈��-- //
void Enemy::Draw() {
	DrawCircle(enemy, color, true);
}

//void Enemy::AllEnemyDeath()
//{
//	enemys.clear();
//}
