#pragma once
// --DX���C�u����-- //
#include "DxLib.h"

// --�Q�[���V�[���N���X-- //
#include "GameScene.h"

// --���U���g�V�[���N���X-- //
#include "ResultScene.h"

// --�X�R�A�N���X-- //
#include "Score.h"

class SceneManager {

	// --�V�[���ԍ�-- //
	enum SceneNum {
		TITLESCENE,
		GAMESCENE,
		RESULTSCENE
	};

	/// --�����o�ϐ�-- ///
public:

private:
	// --�C���X�^���X-- //
	static SceneManager* myInstance;

#pragma region �N���X�錾
	// --�Q�[���V�[��-- //
	GameScene* gameScene;

	// --���U���g�V�[��-- //
	ResultScene* resultScene;

	// --�X�R�A-- //
	Score* score;
#pragma endregion

	// --�V�[���̔ԍ�-- //
	static int scene;

	/// --�����o�ϐ�END-- ///
	/// --------------- ///
	/// --�����o�֐�-- ///
public:
	// --�C���X�^���X�擾-- //
	static SceneManager* GetInstance();

	// --�f�X�g���N�^-- //
	~SceneManager();

	// --����������-- //
	void Initialize();

	// --�X�V����-- //
	void Update();

	// --�`�揈��-- //
	void Draw();

	// --�V�[���؂�ւ�-- //
	static void SceneChange(int sceneNum);

private:
	// --�R���X�g���N�^-- //
	SceneManager();

	/// --�����o�֐�END-- ///
};