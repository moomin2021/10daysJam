#pragma once
// --�R���g���[���[�N���X-- //
#include "JoyPadInput.h"

// --�T�E���h�N���X-- //
#include "Sound.h"

// --�֗��֐�-- //
#include "Util.h"

class ResultScene {

	/// --�����o�ϐ�-- ///
public:

private:
	// --�C���X�^���X-- //
	static ResultScene* myInstance;

#pragma region �摜�n���h��
	// --�^�C�g���֖߂�e�L�X�g-- //
	int gotitleGraph;

	// --���g���C�e�L�X�g-- //
	int retryGraph;

	// --ASBC�����N�̃e�L�X�g�i���j-- //
	int sabcSmallGraph[4];

	// --ASBC�����N�̃e�L�X�g�i��j-- //
	int sabcBigGraph[4];

	// --�X�R�A�\���Ɏg���ԍ��̃e�L�X�g-- //
	int numberGraph[10];

	// --�����N�e�L�X�g-- //
	int rankGraph;

	// --�X�R�A�e�L�X�g-- //
	int scoreGraph;

	// --���U���g�e�L�X�g-- //
	int resultGraph;
#pragma endregion

	// --�I��\���̒��S���W-- //
	Box selectBox;

#pragma region �N���X�錾
	// --�R���g���[���[�N���X-- //
	JoyPadInput* pad;

	// --�T�E���h�N���X-- //
	Sound* sound;
#pragma endregion

	// --�I�𒆂̃V�[��-- //
	int selectScene;

	/// --�����o�ϐ�END-- ///
	/// --------------- ///
	/// --�����o�֐�-- ///
public:
	// --�C���X�^���X�擾-- //
	static ResultScene* GetInstance();

	// --�C���X�^���X���-- //
	void Relese();

	// --�f�X�g���N�^-- //
	~ResultScene();

	// --����������-- //
	void Initialize();

	// --�X�V����-- //
	void Update();

	// --�`�揈��-- //
	void Draw();

private:
	// --�R���X�g���N�^-- //
	ResultScene();

	/// --�����o�֐�END-- ///
};