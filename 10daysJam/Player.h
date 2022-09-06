#pragma once
#include "Input.h"
#include "JoyPadInput.h"
#include "Util.h"

enum class State {
	normal,
	reverse
};

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

	//プレイヤーの状態
	State state;

	//色
	int color = 0xffffff;

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

	/// <summary>
	/// プレイヤーのステートのセッター
	/// </summary>
	void SetState(State state_);

	State GetState() const { return state; }

private:
	// --コンストラクタ-- //
	Player();

	/// --メンバ関数END-- ///
};