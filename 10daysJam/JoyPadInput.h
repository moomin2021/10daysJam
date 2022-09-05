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

	// --����������-- //
	void Initialize();

	// --�X�V����-- //
	void Update();

private:
	// --�R���X�g���N�^-- //
	JoyPadInput();

/// --�����o�֐�END-- ///
};