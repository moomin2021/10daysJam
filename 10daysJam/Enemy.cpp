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
void Enemy::Update() {

}

// --�`�揈��-- //
void Enemy::Draw() {
	DrawCircle(enemy, 0xffff00, true);
}

//void Enemy::AllEnemyDeath()
//{
//	enemys.clear();
//}
