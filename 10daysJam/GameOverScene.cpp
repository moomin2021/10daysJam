#include "GameOverScene.h"

// --�C���X�^���X��NULL����-- //
GameOverScene* GameOverScene::myInstance = nullptr;

// --�C���X�^���X�ǂݍ���-- //
GameOverScene* GameOverScene::GetInstance() {
	// --�C���X�^���X�����������琶������-- //
	if (myInstance == nullptr) myInstance = new GameOverScene();

	// --�C���X�^���X��Ԃ�-- //
	return myInstance;
}

// --�R���X�g���N�^-- //
GameOverScene::GameOverScene() {

}

// --�f�X�g���N�^-- //
GameOverScene::~GameOverScene() {

}

// --����������-- //
void GameOverScene::Initialize() {

}

// --�X�V����-- //
void GameOverScene::Update() {

}

// --�`�揈��-- //
void GameOverScene::Draw() {

}