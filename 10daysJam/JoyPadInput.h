#pragma once
#include "DxLib.h"

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
// PAD_INPUT_1 A�{�^��
// PAD_INPUT_2 B�{�^��
// PAD_INPUT_3 X�{�^��
// PAD_INPUT_4 Y�{�^��
// PAD_INPUT_5 LB�{�^��
// PAD_INPUT_6 RB�{�^��