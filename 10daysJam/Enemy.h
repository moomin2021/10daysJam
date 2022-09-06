#pragma once
#include <vector>
#include "Util.h"

class Enemy {
	/// --メンバ変数-- ///
public:

private:
	// --インスタンス-- //
	static Enemy* myInstance;

	// --エネミー-- //
	std::vector<Circle> enemys;

	int spawnDelay;		//敵のスポーン遅延の残り時間
	int delayMax;		//敵のスポーン位置を確定してからスポーンさせるまでの時間
	int spawnInterval;	//次に敵が発生するまでの間隔
	int spawnTimer;		//敵の発生タイマー
	float enemyLength;	//敵が短針上のどこでスポーンするかの変数 
	Vector2 enemyPos;	//確定した敵のスポーン位置を保存する用変数

	/// --メンバ変数END-- ///
	/// --------------- ///
	/// --メンバ関数-- ///
public:
	// --インスタンス取得-- //
	static Enemy* GetInstance();

	// --デストラクタ-- //
	~Enemy();

	// --初期化処理-- //
	void Initialize();

	// --更新処理-- //
	void Update(Line hourHand, Circle clock);

	// --描画処理-- //
	void Draw();

	void AllEnemyDeath();

private:
	// --コンストラクタ-- //
	Enemy();

	/// --メンバ関数END-- ///
};