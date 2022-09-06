#pragma once
#include "Input.h"
#include "JoyPadInput.h"
#include "Util.h"

enum class State {
	normal,
	reverse
};

class Player {
	/// --�����o�ϐ�-- ///
public:

private:
	// --�C���X�^���X-- //
	static Player* myInstance;

	// --���̓N���X-- //
	Input* input;

	// --�R���g���[���[�N���X-- //
	JoyPadInput* pad;

	// --�v���C���[-- //
	Circle player;
	float playerPos;	//���@�̐j�̏�ł̏���

	// --�v���C���[�̑��x-- //
	float playerSpd;

	//�v���C���[�̏��
	State state;

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
	void Update(Line hourHand, Circle clock);

	// --�`�揈��-- //
	void Draw();

	/// <summary>
	/// �v���C���[�̃Q�b�^�[
	/// </summary>
	/// <returns></returns>
	Circle GetPlayer()const { return player; }

	/// <summary>
	/// �v���C���[�̃X�e�[�g�̃Z�b�^�[
	/// </summary>
	void SetState(State state_);

	State GetState() const { return state; }

private:
	// --�R���X�g���N�^-- //
	Player();

	/// --�����o�֐�END-- ///
};