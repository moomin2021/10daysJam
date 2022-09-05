#include "JoyPadInput.h"
#include "DxLib.h"

// --�C���X�^���X��NULL����-- //
JoyPadInput* JoyPadInput::myInstance = nullptr;

// --�R���X�g���N�^-- //
JoyPadInput::JoyPadInput() : leftStickX(0), leftStickY(0), rightStickX(0), rightStickY(0),
button(0), oldButton(0), vibrationPower(0), vibrationTimer(0), isVibration(false)
{

}

// --����������-- //
void JoyPadInput::Initialize() {

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