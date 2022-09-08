#pragma once
#include "Input.h"
#include "JoyPadInput.h"
#include "Util.h"
#include"Camera.h"

class Player {
	// --コントローラーモードの列挙型-- //
	enum ControlMode {
		MODE1,
		MODE2,
		MODE3
	};

	/// --メンバ変数-- ///
public:
	// --プレイヤー-- //
	Circle player;

private:
	// --インスタンス-- //
	static Player* myInstance;

	/// --クラス宣言-- ///
#pragma region
	// --入力クラス-- //
	Input* input;

	// --コントローラークラス-- //
	JoyPadInput* pad;
#pragma endregion

	/// --プレイヤー関係変数の宣言-- ///
#pragma region

	// --中心からのプレイヤーの距離-- //
	float playerLength;

	// --プレイヤーの速度-- //
	float playerSpeed;

	// --スティックの範囲-- //
	float stickRange;

	// --補助線-- //
	Circle auxiliaryCircle;

	//色
	int color = 0xffffff;

	// --操作モード-- //
	int controlMode;

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
	void Draw(Camera camera_);

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