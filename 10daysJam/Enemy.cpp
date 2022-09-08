#include "Enemy.h"
using namespace Util;

// --コンストラクタ-- //
Enemy::Enemy() {}

Enemy::Enemy(Vector2 pos, float radius) : enemy{ pos, radius } {

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
	case State::Item :
		//色を黄色に変更
		color = 0xffff00;
		break;
	case State::Enemy:
		//色を赤に変更
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
	//短針に座標を追従させる
	//短針の始点と自座標から長さを取得
	Vector2 lenVec = hourLine_.start - enemy.pos;
	float len = lenVec.length();
	//長さと短針の角度から自座標を再計算して代入
	enemy.pos.x = (len * cosf((hourLine_.radian - 90) / 180 * PI)) + hourLine_.start.x;
	enemy.pos.y = (len * sinf((hourLine_.radian - 90) / 180 * PI)) + hourLine_.start.y;
}

void Enemy::OnCollison()
{
	//ステートを反転に
	state = State::Reverse;
		//color = 0x7fff7f;
}

// --描画処理-- //
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
