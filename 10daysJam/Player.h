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
private:
	// --インスタンス-- //
	static Player* myInstance;

#pragma region クラスの宣言
	// --入力クラス-- //
	Input* input;

	// --コントローラークラス-- //
	JoyPadInput* pad;
#pragma endregion

#pragma region プレイヤー関係変数の宣言
public:
	// --プレイヤー-- //
	Circle player;

private:
	// --中心からのプレイヤーの距離-- //
	float playerLength;

	// --プレイヤーの速度-- //
	float playerSpeed;

	// --プレイヤーの画像ハンドル-- //
	int playerGraph[2];
#pragma endregion

	// --短針の角度-- //
	float hourHandAngle;

#pragma region その他変数宣言
	// --スティックの範囲-- //
	float stickRange;

	// --補助線-- //
	Circle auxiliaryCircle;

	// --色-- //
	int color = 0xffffff;

	// --操作モード-- //
	int controlMode;
#pragma endregion

	/// --メンバ変数END-- ///
	/// --------------- ///
	/// --メンバ関数-- ///
public:
	// --インスタンス取得-- //
	static Player* GetInstance();

	// --インスタンス解放-- //
	void Relese();

	// --デストラクタ-- //
	~Player();

	// --初期化処理-- //
	void Initialize();

	// --更新処理-- //
	void Update(Line hourHand, Circle clock, float radius);

	// --描画処理-- //
	void Draw(Camera camera_ ,int bright);

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