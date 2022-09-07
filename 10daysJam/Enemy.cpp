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
void Enemy::Update() {

}

// --描画処理-- //
void Enemy::Draw() {
	DrawCircle(enemy, 0xffff00, true);
}

//void Enemy::AllEnemyDeath()
//{
//	enemys.clear();
//}
