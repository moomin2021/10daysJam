#include "Enemy.h"

// --インスタンスにNULLを代入-- //
Enemy* Enemy::myInstance = nullptr;

// --インスタンス読み込み-- //
Enemy* Enemy::GetInstance() {
	// --インスタンスが無かったら生成する-- //
	if (myInstance == nullptr) myInstance = new Enemy();

	// --インスタンスを返す-- //
	return myInstance;
}

// --コンストラクタ-- //
Enemy::Enemy() {

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

}