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
	gameScene = GameScene::GetInstance();
}

// --�f�X�g���N�^-- //
SceneManager::~SceneManager() {

}

// --����������-- //
void SceneManager::Initialize() {
	// --�Q�[���V�[������������-- //
	gameScene->Initialize();
}

// --�X�V����-- //
void SceneManager::Update() {
	// --�^�C�g���V�[���X�V����-- //
	if (scene == TITLESCENE) {

	}

	// --�Q�[���V�[���X�V����-- //
	else if (scene == GAMESCENE) {
		// --�Q�[���V�[���X�V����-- //
		gameScene->Update();
	}

	// --�Q�[���N���A�V�[���X�V����-- //
	else if (scene == GAMECLEARSCENE) {

	}

	// --�Q�[���I�[�o�[�V�[���X�V����-- //
	else if (scene == GAMEOVERSCENE) {

	}
}

// --�`�揈��-- //
void SceneManager::Draw() {
	// --�^�C�g���V�[���`�揈��-- //
	if (scene == TITLESCENE) {

	}

	// --�Q�[���V�[���`�揈��-- //
	else if (scene == GAMESCENE) {
		// --�Q�[���V�[���`��-- //
		gameScene->Draw();
	}

	// --�Q�[���N���A�V�[���`�揈��-- //
	else if (scene == GAMECLEARSCENE) {

	}

	// --�Q�[���I�[�o�[�V�[���`�揈��-- //
	else if (scene == GAMEOVERSCENE) {

	}
}

// --�V�[���؂�ւ�-- //
void SceneManager::SceneChange(int sceneNum) {
	scene = sceneNum;
}