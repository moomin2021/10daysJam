#include "JoyPadInput.h"
#include "DxLib.h"

// --インスタンスにNULLを代入-- //
JoyPadInput* JoyPadInput::myInstance = nullptr;

// --インスタンス読み込み-- //
JoyPadInput* JoyPadInput::GetInstance() {
	// --インスタンスが無かったら生成する-- //
	if (myInstance == nullptr) myInstance = new JoyPadInput();

	// --インスタンスを返す-- //
	return myInstance;
}

// --コンストラクタ-- //
JoyPadInput::JoyPadInput() : leftStickX(0), leftStickY(0), rightStickX(0), rightStickY(0),
button(0), oldButton(0), vibrationPower(0), vibrationTimer(0), isVibration(false)
{

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

// --指定されたボタンが押されていたら-- //
bool JoyPadInput::GetButton(int button) { return (this->button & button); }

// --指定されたボタンが押された瞬間-- //
bool JoyPadInput::GetButtonTrigger(int button) { return (this->button & button) && !(oldButton & button); }

// --指定されたボタンが離された瞬間-- //
bool JoyPadInput::GetButtonReleased(int button) { return !(this->button & button) && (oldButton & button); }

// --左スティックがどれくらい倒されているか-- //
int JoyPadInput::GetLeftStickX() { return leftStickX; }
int JoyPadInput::GetLeftStickY() { return leftStickY; }

// --右スティックがどれくらい倒されているか-- //
int JoyPadInput::GetRightStickX() { return rightStickX; }
int JoyPadInput::GetRightStickY() { return rightStickY; }

// --左スティックが左右どちらに倒されているか-- //
int JoyPadInput::GetLeftStickHorizontal() {
	if (leftStickX > 300) return 1;
	if (leftStickX < -300) return -1;
	return 0;
}

// --左スティックが上下どちらに倒されているか-- //
int JoyPadInput::GetLeftStickVertical() {
	if (leftStickY > 300) return 1;
	if (leftStickY < -300) return -1;
	return 0;
}

// --右スティックが左右どちらに倒されているか-- //
int JoyPadInput::GetRightStickHorizontal() {
	if (rightStickX > 300) return 1;
	if (rightStickX < -300) return -1;
	return 0;
}

// --右スティックが上下どちらに倒されているか-- //
int JoyPadInput::GetRightStickVertical() {
	if (rightStickY > 300) return 1;
	if (rightStickY < -300) return -1;
	return 0;
}

int JoyPadInput::Get() {
	return button;
}