#pragma once
#include "Input.h"
#include "JoyPadInput.h"
#include "Util.h"

class Player {
	/// --�����o�ϐ�-- ///
public:
	// --�v���C���[-- //
	Circle player;

private:
	// --�C���X�^���X-- //
	static Player* myInstance;

	// --���̓N���X-- //
	Input* input;

	// --�R���g���[���[�N���X-- //
	JoyPadInput* pad;

	// --���S����̃v���C���[�̋���-- //
	float playerLength;

	// --�v���C���[�̑��x-- //
	float playerSpd;

	// --�X�e�B�b�N�͈̔�-- //
	float range;

	// --�⏕��-- //
	Circle auxiliaryCircle;

	//�F
	int color = 0xffffff;

	/// --�����o�ϐ�END-- ///
	/// --------------- ///
	/// --�����o�֐�-- ///
public:
	// --�C���X�^���X�擾-- //
	static Player* GetInstance();

	// --�f�X�g���N�^-- //
	~Player();

	// --����������-- //
	void Initialize();

	// --�X�V����-- //
	void Update(Line hourHand, Circle clock, float radius);

	// --�`�揈��-- //
	void Draw();

	/// <summary>
	/// �v���C���[�̃Q�b�^�[
	/// </summary>
	/// <returns></returns>
	Circle GetPlayer()const { return player; }

private:
	// --�R���X�g���N�^-- //
	Player();

	/// --�����o�֐�END-- ///
};