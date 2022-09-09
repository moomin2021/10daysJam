#include "SceneManager.h"

// --�C���X�^���X��NULL����-- //
SceneManager* SceneManager::myInstance = nullptr;

// --�V�[���̏�����-- //
int SceneManager::scene = GAMESCENE;

// --�C���X�^���X�ǂݍ���-- //
SceneManager* SceneManager::GetInstance() {
	// --�C���X�^���X�����������琶������-- //
	if (myInstance == nullptr) myInstance = new SceneManager();

	// --�C���X�^���X��Ԃ�-- //
	return myInstance;
}

// --�R���X�g���N�^-- //
SceneManager::SceneManager() {
	// --�C���X�^���X�ǂݍ���-- //
#pragma region �C���X�^���X�ǂݍ���
	// --�^�C�g���V�[��-- //
	titleScene = TitleScene::GetInstance();

	// --�Q�[���V�[��-- //
	gameScene = GameScene::GetInstance();

	// --���U���g�V�[��-- //
	resultScene = ResultScene::GetInstance();

	// --�X�R�A-- //
	score = Score::GetInstance();
#pragma endregion
}

// --�f�X�g���N�^-- //
SceneManager::~SceneManager() {
	titleScene->Relese();
	gameScene->Relese();
	resultScene->Relese();
	delete score;
}

// --����������-- //
void SceneManager::Initialize() {
	// --�Q�[���V�[������������-- //
#pragma region �N���X������
	// --�^�C�g���V�[��-- //
	titleScene->Initialize();

	// --�Q�[���V�[��-- //
	gameScene->Initialize();

	// --���U���g�V�[��-- //
	resultScene->Initialize();
#pragma endregion
}

// --�X�V����-- //
void SceneManager::Update() {
	// --�^�C�g���V�[���X�V����-- //
	if (scene == TITLESCENE) {
		titleScene->Update();
	}

	// --�Q�[���V�[���X�V����-- //
	else if (scene == GAMESCENE) {
		// --�Q�[���V�[���X�V����-- //
		gameScene->Update();

		// --�X�R�A�X�V����-- //
		score->Update();
	}

	// --���U���g�V�[���X�V����-- //
	else if (scene == RESULTSCENE) {
		// --���U���g�V�[���X�V����-- //
		resultScene->Update();
	}
}

// --�`�揈��-- //
void SceneManager::Draw() {
	// --�^�C�g���V�[���`�揈��-- //
	if (scene == TITLESCENE) {
		titleScene->Draw();
	}

	// --�Q�[���V�[���`�揈��-- //
	else if (scene == GAMESCENE) {
		// --�Q�[���V�[���`��-- //
		gameScene->Draw();

		// --�X�R�A�`��-- //
		score->Draw();
	}

	// --���U���g�V�[���`�揈��-- //
	else if (scene == RESULTSCENE) {
		// --���U���g�V�[���`�揈��-- //
		resultScene->Draw();
	}
}

// --�V�[���؂�ւ�-- //
void SceneManager::SceneChange(int sceneNum) {
	scene = sceneNum;
}