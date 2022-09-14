#pragma once
// --�R���g���[���[�N���X-- //
#include "JoyPadInput.h"

// --�T�E���h�N���X-- //
#include "Sound.h"

// --�֗��n�N���X-- //
#include "Util.h"

class TitleScene {
	/// --�����o�ϐ�-- ///
public:

private:
	// --�C���X�^���X-- //
	static TitleScene* myInstance;

	// --�R���g���[���[�N���X-- //
	JoyPadInput* pad;

	// --�T�E���h�N���X-- //
	Sound* sound;

#pragma region �摜�n���h���錾
	// --�^�C�g�����S�摜�n���h��-- //
	int titlelogoGraph[4];

	// --�w�i-- //
	int backGroundGraph;

	// --�^�C�g����UI-- //
	int titleUIGraph[2];
#pragma endregion

	// --�I��\���̒��S���W-- //
	Box selectBox;

	//�摜���×p���W�A��
	float graphRad = 0;

	/// --�����o�ϐ�END-- ///
	/// --------------- ///
	/// --�����o�֐�-- ///
public:
	// --�C���X�^���X�擾-- //
	static TitleScene* GetInstance();

	// --�C���X�^���X���-- //
	void Relese();

	// --�f�X�g���N�^-- //
	~TitleScene();

	// --����������-- //
	void Initialize();

	// --�X�V����-- //
	void Update();

	// --�`�揈��-- //
	void Draw();

private:
	// --�R���X�g���N�^-- //
	TitleScene();

	/// --�����o�֐�END-- ///
};