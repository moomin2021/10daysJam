#pragma once
// --�R���g���[���[�N���X-- //
#include "JoyPadInput.h"

class TitleScene {
	/// --�����o�ϐ�-- ///
public:

private:
	// --�C���X�^���X-- //
	static TitleScene* myInstance;

	// --�R���g���[���[�N���X-- //
	JoyPadInput* pad;

	// --�^�C�g�����S�摜�n���h��-- //
	int titlelogoGraph[4];

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