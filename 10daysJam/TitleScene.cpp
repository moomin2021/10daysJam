#include "TitleScene.h"

// --�C���X�^���X��NULL����-- //
TitleScene* TitleScene::myInstance = nullptr;

// --�C���X�^���X�ǂݍ���-- //
TitleScene* TitleScene::GetInstance() {
	// --�C���X�^���X�����������琶������-- //
	if (myInstance == nullptr) myInstance = new TitleScene();

	// --�C���X�^���X��Ԃ�-- //
	return myInstance;
}

// --�R���X�g���N�^-- //
TitleScene::TitleScene() {

}

// --�f�X�g���N�^-- //
TitleScene::~TitleScene() {

}

// --����������-- //
void TitleScene::Initialize() {

}

// --�X�V����-- //
void TitleScene::Update() {

}

// --�`�揈��-- //
void TitleScene::Draw() {

}