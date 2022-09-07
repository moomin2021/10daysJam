#include "Enemy.h"
using namespace Util;

// --コンストラクタ-- //
Enemy::Enemy() {}

Enemy::Enemy(Vector2 pos, float radius) : enemy{pos, radius} {

}

// --デストラクタ-- //
Enemy::~Enemy() {

}

// --初期化処理-- //
void Enemy::Initialize() {

}

// --更新処理-- //
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
	//短針に座標を追従させる
}

void Enemy::OnCollison()
{
	color = 0x7fff7f;
}

// --描画処理-- //
void Enemy::Draw() {
	DrawCircle(enemy, color, true);
}

//void Enemy::AllEnemyDeath()
//{
//	enemys.clear();
//}
