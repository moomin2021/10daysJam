#pragma once

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

	// --初期化処理-- //
	void Initialize();

	// --更新処理-- //
	void Update();

private:
	// --コンストラクタ-- //
	JoyPadInput();

/// --メンバ関数END-- ///
};