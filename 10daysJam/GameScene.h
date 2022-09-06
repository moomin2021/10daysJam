#pragma once
#include "Input.h"
#include<list>
#include<vector>
#include "Util.h"

class GameScene {
	/// --メンバ変数-- ///
public:

private:
	// --インスタンス-- //
	static GameScene* myInstance;

	// --入力クラス-- //
	Input* input;

	// --時計-- //
	Circle clock;

	// --プレイヤー-- //
	Circle player;
	float playerPos;	//自機の針の上での処理

	// --長針-- //
	Line longHand;

	// --短針-- //
	Line hourHand;

	// --エネミー--//
	std::list<Circle> enemys;
	float spawnDelay;	//敵の発生の遅延度
	int spawnInterval;	//次に敵が発生するまでの間隔
	int spawnTimer;		//敵の発生タイマー

	// --プレイヤーの速度-- //
	float playerSpd = 2.0f;

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

private:
	// --コンストラクタ-- //
	GameScene();

	/// --メンバ関数END-- ///
};