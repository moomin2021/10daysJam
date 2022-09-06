#include "GameClearScene.h"
#include "SceneManager.h"

// --�C���X�^���X��NULL����-- //
GameClearScene* GameClearScene::myInstance = nullptr;

// --�C���X�^���X�ǂݍ���-- //
GameClearScene* GameClearScene::GetInstance() {
	// --�C���X�^���X�����������琶������-- //
	if (myInstance == nullptr) myInstance = new GameClearScene();

	// --�C���X�^���X��Ԃ�-- //
	return myInstance;
}

// --�R���X�g���N�^-- //
GameClearScene::GameClearScene() {

}

// --�f�X�g���N�^-- //
GameClearScene::~GameClearScene() {

}

// --����������-- //
void GameClearScene::Initialize() {

}

// --�X�V����-- //
void GameClearScene::Update() {
	
}

// --�`�揈��-- //
void GameClearScene::Draw() {

}