#pragma once
#include "Input.h"
#include "JoyPadInput.h"
#include "Util.h"

class Player {
	/// --メンバ変数-- ///
public:

private:
	// --インスタンス-- //
	static Player* myInstance;

	// --入力クラス-- //
	Input* input;

	// --コントローラークラス-- //
	JoyPadInput* pad;

	// --プレイヤー-- //
	Circle player;
	float playerPos;	//自機の針の上での処理

	// --プレイヤーの速度-- //
	float playerSpd;

	/// --メンバ変数END-- ///
	/// --------------- ///
	/// --メンバ関数-- ///
public:
	// --インスタンス取得-- //
	static Player* GetInstance();

	// --デストラクタ-- //
	~Player();

	// --初期化処理-- //
	void Initialize();

	// --更新処理-- //
	void Update(Line hourHand, Circle clock);

	// --描画処理-- //
	void Draw();

	/// <summary>
	/// プレイヤーのゲッター
	/// </summary>
	/// <returns></returns>
	Circle GetPlayer()const { return player; }

private:
	// --コンストラクタ-- //
	Player();

	/// --メンバ関数END-- ///
};