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

	// --�^�C�g����UI-- //
	LoadDivGraph("Resources/titleUI.png", 2, 2, 1, 348, 64, titleUIGraph);
#pragma endregion

	// --�I��\���̒��S���W-- //
	selectBox = { {640.0f, -300.0f}, 174.0f, 32.0f };
}

// --�f�X�g���N�^-- //
TitleScene::~TitleScene() {

}

// --����������-- //
void TitleScene::Initialize() {
	// --�I��\���̒��S���W-- //
	selectBox = { {640.0f, -300.0f}, 174.0f, 32.0f };

	graphRad = 0;
}

// --�X�V����-- //
void TitleScene::Update() {
	// --A�{�^���������ƃQ�[���V�[���Ɉړ�-- //
	if (pad->GetButtonTrigger(PAD_INPUT_1)) {
		if (selectBox.pos.y == 750.0f) {
			// --�V�[���ύX-- //
			SceneManager::SetScene(GAMESCENE);

			// --SE���Đ�-- //
			sound->PlaySE(SELECTSE);
		}
		else if (selectBox.pos.y == 850.0f) {
			// --SE���Đ�-- //
			sound->PlaySE(SELECTSE);

			// --�Q�[���G���h�t���O��true�ɂ���-- //
			SceneManager::EndTrue();
		}
	}

	if (pad->GetButtonTrigger(PAD_INPUT_UP) || pad->GetButtonTrigger(PAD_INPUT_DOWN)) {
		// --SE���Đ�-- //
		sound->PlaySE(BUTTONSE);

		if (selectBox.pos.y != 750.0f) {
			selectBox.pos.y = 750.0f;
		}

		else if (selectBox.pos.y != 850.0f) {
			selectBox.pos.y = 850.0f;
		}
	}

	graphRad += 3;
	if (graphRad > 360) {
		graphRad -= 360;
	}
}

// --�`�揈��-- //
void TitleScene::Draw() {
	// --�w�i�摜�̕`��-- //
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, sinf(graphRad / 180 * Util::PI) * 64 + 192);
	DrawGraph(0, 0, backGroundGraph, true);

#pragma region �^�C�g�����S�`�揈��
	SetDrawBlendMode(DX_BLENDMODE_ADD, sinf(graphRad / 180  * Util::PI) * 64 + 128);

	// --0��-- //
	Util::SetDrawBright2(LIGHTBLUE);
	for (int i = 0; i < 20; i++) {
		DrawGraph(354, 60, titlelogoGraph[0], true);
	}

	// --1��-- //
	//SetDrawBright(39, 32, 225);
	for (int i = 0; i < 20; i++) {
		DrawGraph(354, 60, titlelogoGraph[1], true);
	}

	// --2��-- //
	Util::SetDrawBright2(PURPLE);
	for (int i = 0; i < 20; i++) {
		DrawGraph(354, 60, titlelogoGraph[2], true);
	}

	// --3��-- //
	Util::SetDrawBright2(GREEN);
	for (int i = 0; i < 20; i++) {
		DrawGraph(354, 60, titlelogoGraph[3], true);
	}

	SetDrawBright(255, 255, 255);

	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 255);

	SetDrawBlendMode(DX_BLENDMODE_ADD, 255);
	for (int i = 0; i < 3; i++) {
		DrawRotaGraph(640, 750, 1.0f, 0.0f, titleUIGraph[0], true);
		DrawRotaGraph(640, 850, 1.0f, 0.0f, titleUIGraph[1], true);
	}
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 255);

	DrawBoxAA(
		selectBox.pos.x - selectBox.radiusX, selectBox.pos.y - selectBox.radiusY,
		selectBox.pos.x + selectBox.radiusX, selectBox.pos.y + selectBox.radiusY,
		0xFFFFFF, false, 3);

#pragma endregion
}