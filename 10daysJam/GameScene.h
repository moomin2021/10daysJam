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

	// --エネミークラス-- //
	Enemy* enemy;

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