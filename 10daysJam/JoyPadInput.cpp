#include "JoyPadInput.h"
#include "DxLib.h"

// --�C���X�^���X��NULL����-- //
JoyPadInput* JoyPadInput::myInstance = nullptr;

// --�C���X�^���X�ǂݍ���-- //
JoyPadInput* JoyPadInput::GetInstance() {
	// --�C���X�^���X�����������琶������-- //
	if (myInstance == nullptr) myInstance = new JoyPadInput();

	// --�C���X�^���X��Ԃ�-- //
	return myInstance;
}

// --�R���X�g���N�^-- //
JoyPadInput::JoyPadInput() : leftStickX(0), leftStickY(0), rightStickX(0), rightStickY(0),
button(0), oldButton(0), vibrationPower(0), vibrationTimer(0), isVibration(false)
{

}

// --�X�V����-- //
void JoyPadInput::Update() {
	// --�X�e�B�b�N�̏�Ԃ��擾-- //
	{
		// --���X�e�B�b�N-- //
		GetJoypadAnalogInput(&leftStickX, &leftStickY, DX_INPUT_PAD1);

		// --�E�X�e�B�b�N-- //
		GetJoypadAnalogInputRight(&rightStickX, &rightStickY, DX_INPUT_PAD1);
	}

	// --�ŐV�̃p�b�h��񂾂������̂�1�t���[���O�̃p�b�h���Ƃ��ĕۑ�-- //
	oldButton = button;

	// --�ŐV�̃p�b�h�����擾-- //
	button = GetJoypadInputState(DX_INPUT_PAD1);

	// --�p�b�h���U�����鏈��-- //
	if (vibrationTimer > 0) {
		vibrationTimer--;
		StartJoypadVibration(DX_INPUT_PAD1, 1000, 1000);
	}
	else {
		vibrationTimer = 0;
		StopJoypadVibration(DX_INPUT_PAD1);
	}
}

// --�w�肳�ꂽ�{�^����������Ă�����-- //
bool JoyPadInput::GetButton(int button) { return (this->button & button); }

// --�w�肳�ꂽ�{�^���������ꂽ�u��-- //
bool JoyPadInput::GetButtonTrigger(int button) { return (this->button & button) && !(oldButton & button); }

// --�w�肳�ꂽ�{�^���������ꂽ�u��-- //
bool JoyPadInput::GetButtonReleased(int button) { return !(this->button & button) && (oldButton & button); }

// --���X�e�B�b�N���ǂꂭ�炢�|����Ă��邩-- //
int JoyPadInput::GetLeftStickX() { return leftStickX; }
int JoyPadInput::GetLeftStickY() { return leftStickY; }

// --�E�X�e�B�b�N���ǂꂭ�炢�|����Ă��邩-- //
int JoyPadInput::GetRightStickX() { return rightStickX; }
int JoyPadInput::GetRightStickY() { return rightStickY; }

// --���X�e�B�b�N�����E�ǂ���ɓ|����Ă��邩-- //
int JoyPadInput::GetLeftStickHorizontal() {
	if (leftStickX > 300) return 1;
	if (leftStickX < -300) return -1;
	return 0;
}

// --���X�e�B�b�N���㉺�ǂ���ɓ|����Ă��邩-- //
int JoyPadInput::GetLeftStickVertical() {
	if (leftStickY > 300) return 1;
	if (leftStickY < -300) return -1;
	return 0;
}

// --�E�X�e�B�b�N�����E�ǂ���ɓ|����Ă��邩-- //
int JoyPadInput::GetRightStickHorizontal() {
	if (rightStickX > 300) return 1;
	if (rightStickX < -300) return -1;
	return 0;
}

// --�E�X�e�B�b�N���㉺�ǂ���ɓ|����Ă��邩-- //
int JoyPadInput::GetRightStickVertical() {
	if (rightStickY > 300) return 1;
	if (rightStickY < -300) return -1;
	return 0;
}

int JoyPadInput::Get() {
	return button;
}