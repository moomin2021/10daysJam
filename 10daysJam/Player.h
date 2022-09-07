#pragma once
#include "Input.h"
#include "JoyPadInput.h"
#include "Util.h"

class Player {
	/// --メンバ変数-- ///
public:
	// --プレイヤー-- //
	Circle player;

private:
	// --インスタンス-- //
	static Player* myInstance;

	// --入力クラス-- //
	Input* input;

	// --コントローラークラス-- //
	JoyPadInput* pad;

	// --中心からのプレイヤーの距離-- //
	float playerLength;

	// --プレイヤーの速度-- //
	float playerSpd;

	// --スティックの範囲-- //
	float range;

	// --補助線-- //
	Circle auxiliaryCircle;

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
	void Update(Line hourHand, Circle clock, float radius);

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