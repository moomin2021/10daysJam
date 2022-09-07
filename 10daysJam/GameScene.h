#pragma once
#include "Input.h"
#include<list>
#include<vector>
#include "Util.h"
#include "Player.h"
#include "Enemy.h"
#include "JoyPadInput.h"

class GameScene {

	/// --メンバ変数-- ///
public:

private:
	// --インスタンス-- //
	static GameScene* myInstance;

	// --入力クラス-- //
	Input* input;

	JoyPadInput* pad;

	// --プレイヤークラス-- //
	Player* player;

	// --エネミー-- //
	std::vector<Enemy> enemys;

	int spawnDelay;		//敵のスポーン遅延の残り時間
	int delayMax;		//敵のスポーン位置を確定してからスポーンさせるまでの時間
	int spawnInterval;	//次に敵が発生するまでの間隔
	int spawnTimer;		//敵の発生タイマー
	float enemyLength;	//敵が短針上のどこでスポーンするかの変数 
	Vector2 enemyPos;	//確定した敵のスポーン位置を保存する用変数

	// --時計-- //
	Circle clock;

	// --長針-- //
	Line longHand;

	// --短針-- //
	Line hourHand;
	float reverseSpd = 4.0f;

	/// --メンバ変数END-- ///
	/// --------------- ///
	/// --メンバ関数-- ///
public:
	// --インスタンス取得-- //
	static GameScene* GetInstance();

	// --デストラクタ-- //
	~GameScene();

	// --初期化処理-- //
	void Initialize();

	// --更新処理-- //
	void Update();

	// --描画処理-- //
	void Draw();

	// --自機と敵の当たり判定処理-- //
	void PlayerAndEnemyCol();

	// --敵のスポーン処理-- //
	void EnemySpawn();

	/// <summary>
	/// 円と円の衝突判定
	/// </summary>
	/// <param name="cA"></param>
	/// <param name="cB"></param>
	/// <returns></returns>
	bool CollisionCtoC(Circle cA, Circle cB);

private:
	// --コンストラクタ-- //
	GameScene();

	/// --メンバ関数END-- ///
};