#include "Enemy.h"
using namespace Util;

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
	delayMax = 1;
	spawnDelay = delayMax;
	spawnInterval = 20;
	spawnTimer = spawnInterval;
}

// --更新処理-- //
void Enemy::Update(Line hourHand, Circle clock) {
	//スポーンタイマーを減らす
	if (spawnTimer > 0) {
		spawnTimer--;
		//タイマーが0になったらスポーン位置を決める
	}
	else if (spawnTimer == 0) {


		//スポーンタイマーが0になった瞬間のみ位置を決める(短針の位置を参照するため
		if (spawnDelay == delayMax) {
			enemyLength = Random(0.0f, hourHand.length);
			float rad = hourHand.radian - 90;
			enemyPos.x = (enemyLength * cosf(rad / 180 * PI)) + clock.x;
			enemyPos.y = (enemyLength * sinf(rad / 180 * PI)) + clock.y;
			//ディレイタイマーを減らす
			spawnDelay--;
		}//ディレイタイマーが0出ないなら
		else if (spawnDelay > 0) {
			//ディレイタイマーを減らす
			spawnDelay--;
		}//ディレイタイマーが0になったら座標を確定
		else if (spawnDelay == 0) {
			for (int i = 0; i < 10; i++) {
				enemys.push_back({enemyPos.x, enemyPos.y, 8});
				//タイマーをリセット
				spawnTimer = spawnInterval;
				spawnDelay = delayMax;
				break;
			}
		}
	}
}

// --描画処理-- //
void Enemy::Draw() {
	for (int i = 0; i < enemys.size(); i++) {
		DrawCircle(enemys[i], 0xffff00, true);
	}
}

void Enemy::AllEnemyDeath()
{
	enemys.clear();
}
