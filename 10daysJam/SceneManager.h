#pragma once
#include "DxLib.h"
#include "GameScene.h"

class SceneManager {

	// --�V�[���ԍ�-- //
	enum SceneNum {
		TITLESCENE,
		GAMESCENE,
		GAMECLEARSCENE,
		GAMEOVERSCENE
	};

	/// --�����o�ϐ�-- ///
public:

private:
	// --�C���X�^���X-- //
	static SceneManager* myInstance;

	// --�Q�[���V�[��-- //
	GameScene* gameScene;

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