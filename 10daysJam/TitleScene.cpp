#include "TitleScene.h"

// --DX���C�u����-- //
#include "DxLib.h"

// --�V�[���}�l�[�W���[�N���X-- //
#include "SceneManager.h"

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
#pragma region �C���X�^���X�ǂݍ���
	// --�R���g���[���[-- //
	pad = JoyPadInput::GetInstance();

	// --�T�E���h-- //
	sound = Sound::GetInstance();
#pragma endregion

#pragma region �摜�ǂݍ���
	// --�^�C�g�����S-- //
	LoadDivGraph("Resources/titleRogo.png", 4, 4, 1, 572, 572, titlelogoGraph);

	// --�w�i-- //
	backGroundGraph = LoadGraph("Resources/backillust.png");
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
	// --A�{�^���������ƃQ�[���V�[���Ɉړ�-- //
	if (pad->GetButtonTrigger(PAD_INPUT_1)) {
		// --�V�[���ύX-- //
		SceneManager::SetScene(GAMESCENE);
		// --SE���Đ�-- //
		sound->PlaySE(SELECTSE);
	}
}

// --�`�揈��-- //
void TitleScene::Draw() {
	// --�w�i�摜�̕`��-- //
	DrawGraph(0, 0, backGroundGraph, true);

#pragma region �^�C�g�����S�`�揈��
	SetDrawBlendMode(DX_BLENDMODE_ADD, 255);
	
	// --0��-- //
	SetDrawBright(39, 32, 225);
	for (int i = 0; i < 20; i++) {
		DrawGraph(354, 194, titlelogoGraph[0], true);
	}

	// --1��-- //
	SetDrawBright(39, 32, 225);
	for (int i = 0; i < 20; i++) {
		DrawGraph(354, 194, titlelogoGraph[1], true);
	}

	// --2��-- //
	SetDrawBright(39, 32, 225);
	for (int i = 0; i < 20; i++) {
		DrawGraph(354, 194, titlelogoGraph[2], true);
	}

	// --3��-- //
	SetDrawBright(39, 32, 225);
	for (int i = 0; i < 20; i++) {
		DrawGraph(354, 194, titlelogoGraph[3], true);
	}

	SetDrawBright(255, 255, 255);

	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 255);
#pragma endregion
}