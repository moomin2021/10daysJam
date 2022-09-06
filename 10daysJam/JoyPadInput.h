#pragma once

class JoyPadInput {
/// --�����o�ϐ�-- ///
public:

private:
	// --�C���X�^���X-- //
	static JoyPadInput* myInstance;

	// --L�X�e�B�b�N�����E�ǂ����̕����ɓ|���Ă邩-- //
	int leftStickX, leftStickY;

	// --R�X�e�B�b�N�����E�ǂ����̕����ɓ|���Ă邩-- //
	int rightStickX, rightStickY;

	// --�R���g���[���[�̃{�^���̏��-- //
	int button;

	// --1�t���[���O�̃R���g���[���[�̃{�^���̏��-- //
	int oldButton;

	// --�R���g���[���[�̐U���̋���-- //
	int vibrationPower;

	// --�R���g���[���[�̐U���̊Ԋu-- //
	int vibrationTimer;

	// --�R���g���[���[���U�����邩�ǂ���-- //
	bool isVibration;

/// --�����o�ϐ�END-- ///
/// --------------- ///
/// --�����o�֐�-- ///
public:
	// --�C���X�^���X�ǂݍ���-- //
	static JoyPadInput* GetInstance();

	// --�X�V����-- //
	void Update();

	// --�w�肳�ꂽ�{�^����������Ă�����-- //
	bool GetButton(int button);

	// --�w�肳�ꂽ�{�^���������ꂽ�u��-- //
	bool GetButtonTrigger(int button);

	// --�w�肳�ꂽ�{�^���������ꂽ�u��-- //
	bool GetButtonReleased(int button);

	// --���X�e�B�b�N���ǂꂭ�炢�|����Ă��邩-- //
	int GetLeftStickX();
	int GetLeftStickY();

	// --�E�X�e�B�b�N���ǂꂭ�炢�|����Ă��邩-- //
	int GetRightStickX();
	int GetRightStickY();

	/// <summary>
	/// ���X�e�B�b�N�����E�ǂ���ɓ|����Ă��邩
	/// </summary>
	/// <returns> �E 1, �� -1 </returns>
	int GetLeftStickHorizontal();

	/// <summary>
	/// ���X�e�B�b�N���㉺�ǂ���ɓ|����Ă��邩
	/// </summary>
	/// <returns> �� 1, �� -1 </returns>
	int GetLeftStickVertical();

	/// <summary>
	/// �E�X�e�B�b�N�����E�ǂ���ɓ|����Ă��邩
	/// </summary>
	/// <returns> �E 1, �� -1 </returns>
	int GetRightStickHorizontal();

	/// <summary>
	/// �E�X�e�B�b�N���㉺�ǂ���ɓ|����Ă��邩
	/// </summary>
	/// <returns> �� 1, �� -1 </returns>
	int GetRightStickVertical();

private:
	// --�R���X�g���N�^-- //
	JoyPadInput();

/// --�����o�֐�END-- ///
};

// �R���g���[���[�̃{�^�����͒�`
// XINPUT_BUTTON_DPAD_UP		(0)		// �f�W�^�������{�^����
// XINPUT_BUTTON_DPAD_DOWN		(1)		// �f�W�^�������{�^����
// XINPUT_BUTTON_DPAD_LEFT		(2)		// �f�W�^�������{�^����
// XINPUT_BUTTON_DPAD_RIGHT		(3)		// �f�W�^�������{�^���E
// XINPUT_BUTTON_START			(4)		// START�{�^��
// XINPUT_BUTTON_BACK			(5)		// BACK�{�^��
// XINPUT_BUTTON_LEFT_THUMB		(6)		// ���X�e�B�b�N��������
// XINPUT_BUTTON_RIGHT_THUMB	(7)		// �E�X�e�B�b�N��������
// XINPUT_BUTTON_LEFT_SHOULDER	(8)		// LB�{�^��
// XINPUT_BUTTON_RIGHT_SHOULDER	(9)		// RB�{�^��
// XINPUT_BUTTON_A				(12)	// A�{�^��
// XINPUT_BUTTON_B				(13)	// B�{�^��
// XINPUT_BUTTON_X				(14)	// X�{�^��
// XINPUT_BUTTON_Y				(15)	// Y�{�^��