#pragma once
// --DX���C�u����-- //
#include "DxLib.h"

// --�^�C�g���V�[���N���X-- //
#include "TitleScene.h"

// --�Q�[���V�[���N���X-- //
#include "GameScene.h"

// --���U���g�V�[���N���X-- //
#include "ResultScene.h"

// --�X�R�A�N���X-- //
#include "Score.h"

// --�T�E���h�N���X-- //
#include "Sound.h"

// --���̓N���X-- //
#include "Input.h"

// --�V�[���ԍ�-- //
enum SceneNum {
	TITLESCENE,
	GAMESCENE,
	RESULTSCENE
};

class SceneManager {

	/// --�����o�ϐ�-- ///
public:

private:
	// --�C���X�^���X-- //
	static SceneManager* myInstance;

#pragma region �N���X�錾
	// --�^�C�g���V�[��-- //
	TitleScene* titleScene;

	// --�Q�[���V�[��-- //
	GameScene* gameScene;

	// --���U���g�V�[��-- //
	ResultScene* resultScene;

	// --�X�R�A-- //
	Score* score;

	// --�T�E���h-- //
	Sound* sound;

	// --����-- //
	Input* input;
#pragma endregion

#pragma region �V�[���֌W�ϐ�

	// --�V�[���̔ԍ�-- //
	int scene;

	// --�ύX����V�[��-- //
	static int changeScene;

	// --�V�[���ύX�t���O-- //
	static bool isChangeScene;

	// --�V�[�����ړ�����ۂ̎���-- //
	int sceneInterval;

	// --�^�C�}�[-- //
	int timer;

	// --�~�̃T�C�Y-- //
	int circleSize;
	
	// --�~�̊g�k�̑��x-- //
	int sizeChangeSpeed;

	// --�X�N���[���n���h��-- //
	int screenHandle;

	// --�t�F�[�h�A�E�g���邩-- //
	bool isFadeOut;

	// --�t�F�[�h�C��
	bool isFadeIn;

#pragma endregion

	// --�ڂ������~�̉摜-- //
	int circleGraph;

	// --�f�o�b�O���[�h�t���O-- //
	static bool isDebugMode;

	/// --�����o�ϐ�END-- ///
	/// --------------- ///
	/// --�����o�֐�-- ///
public:
	// --�C���X�^���X�擾-- //
	static SceneManager* GetInstance();

	// --�C���X�^���X���-- //
	void Relese();

	// --�f�X�g���N�^-- //
	~SceneManager();

	// --����������-- //
	void Initialize();

	// --�X�V����-- //
	void Update();

	// --�`�揈��-- //
	void Draw();

	// --�V�[����ݒ�-- //
	static void SetScene(int sceneNum);

	// --�V�[���ύX�X�V����-- //
	void UpdateChangeScene();

	// --�V�[���ύX�`�揈��-- //
	void DrawChangeScene();

	// --�f�o�b�O���[�h���擾-- //
	static bool GetDebugMode();

private:
	// --�R���X�g���N�^-- //
	SceneManager();

	/// --�����o�֐�END-- ///
};