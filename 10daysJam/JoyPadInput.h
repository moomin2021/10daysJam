#pragma once
#include "DxLib.h"

class JoyPadInput {
/// --メンバ変数-- ///
public:

private:
	// --インスタンス-- //
	static JoyPadInput* myInstance;

	// --Lスティックを左右どっちの方向に倒してるか-- //
	int leftStickX, leftStickY;

	// --Rスティックを左右どっちの方向に倒してるか-- //
	int rightStickX, rightStickY;

	// --コントローラーのボタンの状態-- //
	int button;

	// --1フレーム前のコントローラーのボタンの状態-- //
	int oldButton;

	// --コントローラーの振動の強さ-- //
	int vibrationPower;

	// --コントローラーの振動の間隔-- //
	int vibrationTimer;

	// --コントローラーが振動するかどうか-- //
	bool isVibration;

/// --メンバ変数END-- ///
/// --------------- ///
/// --メンバ関数-- ///
public:
	// --インスタンス読み込み-- //
	static JoyPadInput* GetInstance();

	// --更新処理-- //
	void Update();

	// --指定されたボタンが押されていたら-- //
	bool GetButton(int button);

	// --指定されたボタンが押された瞬間-- //
	bool GetButtonTrigger(int button);

	// --指定されたボタンが離された瞬間-- //
	bool GetButtonReleased(int button);

	// --左スティックがどれくらい倒されているか-- //
	int GetLeftStickX();
	int GetLeftStickY();

	// --右スティックがどれくらい倒されているか-- //
	int GetRightStickX();
	int GetRightStickY();

	/// <summary>
	/// 左スティックが左右どちらに倒されているか
	/// </summary>
	/// <returns> 右 1, 左 -1 </returns>
	int GetLeftStickHorizontal();

	/// <summary>
	/// 左スティックが上下どちらに倒されているか
	/// </summary>
	/// <returns> 下 1, 上 -1 </returns>
	int GetLeftStickVertical();

	/// <summary>
	/// 右スティックが左右どちらに倒されているか
	/// </summary>
	/// <returns> 右 1, 左 -1 </returns>
	int GetRightStickHorizontal();

	/// <summary>
	/// 右スティックが上下どちらに倒されているか
	/// </summary>
	/// <returns> 下 1, 上 -1 </returns>
	int GetRightStickVertical();

private:
	// --コンストラクタ-- //
	JoyPadInput();

/// --メンバ関数END-- ///
};

// コントローラーのボタン入力定義
// PAD_INPUT_1 Aボタン
// PAD_INPUT_2 Bボタン
// PAD_INPUT_3 Xボタン
// PAD_INPUT_4 Yボタン
// PAD_INPUT_5 LBボタン
// PAD_INPUT_6 RBボタン