#pragma once
// --�R���g���[���[�N���X-- //
#include "JoyPadInput.h"

class ResultScene {
	/// --�����o�ϐ�-- ///
public:

private:
	// --�C���X�^���X-- //
	static ResultScene* myInstance;

#pragma region �N���X�錾
	// --�R���g���[���[�N���X-- //
	JoyPadInput* pad;
#pragma endregion

	// --�w�i�摜�n���h��-- //
	int backGroundGraph;

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