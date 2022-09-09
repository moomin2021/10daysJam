#include "TitleScene.h"

// --DX���C�u����-- //
#include "DxLib.h"

// --�C���X�^���X��NULL����-- //
TitleScene* TitleScene::myInstance = nullptr;

// --�C���X�^���X�ǂݍ���-- //
TitleScene* TitleScene::GetInstance() {
	// --�C���X�^���X�����������琶������-- //
	if (myInstance == nullptr) myInstance = new TitleScene();

	// --�C���X�^���X��Ԃ�-- //
	return myInstance;
}

// --�C���X�^���X���-- //
void TitleScene::Relese() {
	// --�C���X�^���X�����������牽�������ɏI������-- //
	if (myInstance == nullptr) return;

	// --�C���X�^���X���-- //
	delete myInstance;
	myInstance = nullptr;
}

// --�R���X�g���N�^-- //
TitleScene::TitleScene() {
#pragma region �摜�ǂݍ���
	// --�^�C�g�����S-- //
	LoadDivGraph("Resources/titleRogo.png", 4, 4, 1, 572, 572, titlelogoGraph);
#pragma endregion
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
#pragma region �^�C�g�����S�`�揈��
	SetDrawBlendMode(DX_BLENDMODE_ADD, 255);
	
	// --0��-- //
	SetDrawBright(39, 32, 225);
	for (int i = 0; i < 14; i++) {
		DrawGraph(354, 194, titlelogoGraph[0], true);
	}

	// --1��-- //
	SetDrawBright(39, 32, 225);
	for (int i = 0; i < 14; i++) {
		DrawGraph(354, 194, titlelogoGraph[1], true);
	}

	// --2��-- //
	SetDrawBright(39, 32, 225);
	for (int i = 0; i < 14; i++) {
		DrawGraph(354, 194, titlelogoGraph[2], true);
	}

	// --3��-- //
	SetDrawBright(39, 32, 225);
	for (int i = 0; i < 14; i++) {
		DrawGraph(354, 194, titlelogoGraph[3], true);
	}

	SetDrawBright(255, 255, 255);

	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 255);
#pragma endregion
}