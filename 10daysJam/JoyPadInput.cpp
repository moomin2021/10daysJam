#include "JoyPadInput.h"
#include "DxLib.h"

// --インスタンスにNULLを代入-- //
JoyPadInput* JoyPadInput::myInstance = nullptr;

// --コンストラクタ-- //
JoyPadInput::JoyPadInput() : leftStickX(0), leftStickY(0), rightStickX(0), rightStickY(0),
button(0), oldButton(0), vibrationPower(0), vibrationTimer(0), isVibration(false)
{

}

// --初期化処理-- //
void JoyPadInput::Initialize() {

}

// --更新処理-- //
void JoyPadInput::Update() {
	// --スティックの状態を取得-- //
	{
		// --左スティック-- //
		GetJoypadAnalogInput(&leftStickX, &leftStickY, DX_INPUT_PAD1);

		// --右スティック-- //
		GetJoypadAnalogInputRight(&rightStickX, &rightStickY, DX_INPUT_PAD1);
	}

	// --最新のパッド情報だったものは1フレーム前のパッド情報として保存-- //
	oldButton = button;

	// --最新のパッド情報を取得-- //
	button = GetJoypadInputState(DX_INPUT_PAD1);

	// --パッドが振動する処理-- //
	if (vibrationTimer > 0) {
		vibrationTimer--;
		StartJoypadVibration(DX_INPUT_PAD1, 1000, 1000);
	}
	else {
		vibrationTimer = 0;
		StopJoypadVibration(DX_INPUT_PAD1);
	}


}