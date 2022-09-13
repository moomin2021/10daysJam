#include "ResultScene.h"

// --DX���C�u����-- //
#include "DxLib.h"

// --�R���g���[���[�N���X-- //
#include "JoyPadInput.h"

// --�V�[���}�l�[�W���[�N���X-- //
#include "SceneManager.h"

// --�X�R�A�N���X-- //
#include "Score.h"

// --�C���X�^���X��NULL����-- //
ResultScene* ResultScene::myInstance = nullptr;

// --�C���X�^���X�ǂݍ���-- //
ResultScene* ResultScene::GetInstance() {
	// --�C���X�^���X�����������琶������-- //
	if (myInstance == nullptr) myInstance = new ResultScene();

	// --�C���X�^���X��Ԃ�-- //
	return myInstance;
}

// --�C���X�^���X���-- //
void ResultScene::Relese() {
	// --�C���X�^���X�����������牽�������ɏI������-- //
	if (myInstance == nullptr) return;

	// --�C���X�^���X���-- //
	delete myInstance;
	myInstance = nullptr;
}

// --�R���X�g���N�^-- //
ResultScene::ResultScene() {
#pragma region �C���X�^���X�ǂݍ���
	// --�R���g���[���[�N���X-- //
	pad = JoyPadInput::GetInstance();

	// --�T�E���h�N���X-- //
	sound = Sound::GetInstance();
#pragma endregion

#pragma region �摜�ǂݍ���
	// --�^�C�g���֖߂�e�L�X�g-- //
	gotitleGraph = LoadGraph("Resources/gotitle.png");

	// --���g���C�e�L�X�g-- //
	retryGraph = LoadGraph("Resources/retry.png");

	// --ASBC�����N�̃e�L�X�g�i���j-- //
	LoadDivGraph("Resources/sabc_small.png", 4, 4, 1, 64, 64, sabcSmallGraph);

	// --ASBC�����N�̃e�L�X�g�i��j-- //
	LoadDivGraph("Resources/sabc_Big.png", 4, 4, 1, 111, 111, sabcBigGraph);

	// --�X�R�A�\���Ɏg���ԍ��̃e�L�X�g-- //
	LoadDivGraph("Resources/numbers_big.png", 10, 10, 1, 64, 120, numberGraph);

	// --�����N�e�L�X�g-- //
	rankGraph = LoadGraph("Resources/rank.png");

	// --�X�R�A�e�L�X�g-- //
	scoreGraph = LoadGraph("Resources/score_small.png");

	// --���U���g�e�L�X�g-- //
	resultGraph = LoadGraph("Resources/result.png");
#pragma endregion

	// --�I��\���̒��S���W-- //
	selectBox = {{640.0f, -300.0f}, 112.5f, 45.5f};

	// --�I�𒆂̃V�[��-- //
	selectScene = 10;
}

// --�f�X�g���N�^-- //
ResultScene::~ResultScene() {

}

// --����������-- //
void ResultScene::Initialize() {

}

// --�X�V����-- //
void ResultScene::Update() {
	// --�p�b�h�㉺���͂��ꂽ��-- //
	if (pad->GetButtonTrigger(PAD_INPUT_UP) || pad->GetButtonTrigger(PAD_INPUT_DOWN)) {
		if (selectScene != GAMESCENE) {
			selectScene = GAMESCENE;
			selectBox.pos.y = 750.0f;
		}

		else if (selectScene != TITLESCENE) {
			selectScene = TITLESCENE;
			selectBox.pos.y = 850.0f;
		}
	}

	if (selectScene <= GAMESCENE) {
		if (pad->GetButtonTrigger(PAD_INPUT_1)) {
			// --�V�[���ݒ�-- //
			SceneManager::SetScene(selectScene);

			// --SE�Đ�-- //
			sound->PlaySE(SELECTSE);
		}
	}
}

// --�`�揈��-- //
void ResultScene::Draw() {
	// --���U���g�e�L�X�g�`��-- //
	SetDrawBlendMode(DX_BLENDMODE_ADD, 255);
	for (int i = 0; i < 3; i++) {
		DrawGraphF(371.5f, 30.0f, resultGraph, true);
	}
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 255);

	// --�X�R�A�Q�[�W�`��-- //
	DrawLine(150, 250, 1130, 250, 0xFFFFFF, 5);
	DrawLine(150, 350, 1130, 350, 0xFFFFFF, 5);
	DrawLine(150, 250, 150, 350, 0xFFFFFF, 5);
	DrawLine(1130, 250, 1130, 350, 0xFFFFFF, 5);

	// --SABC�����N�e�L�X�g�`��-- //
	SetDrawBlendMode(DX_BLENDMODE_ADD, 255);
	for (int i = 0; i < 3; i++) {
		DrawGraph(550, 350, sabcSmallGraph[3], true);
		DrawGraph(700, 350, sabcSmallGraph[2], true);
		DrawGraph(850, 350, sabcSmallGraph[1], true);
		DrawGraph(1000, 350, sabcSmallGraph[0], true);
	}
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 255);

	// --�X�R�A�e�L�X�g�`��-- //
	SetDrawBlendMode(DX_BLENDMODE_ADD, 255);
	for (int i = 0; i < 3; i++) {
		DrawGraph(150, 450, scoreGraph, true);
	}
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 255);

	// --�X�R�A�\���`��-- //
	SetDrawBlendMode(DX_BLENDMODE_ADD, 255);
	int num = Score::GetScore();
	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 6; j++) {
			for (int k = 0; k < 1; k++) {
				DrawGraph(150 + j * 64, 500, numberGraph[num / (int)pow(10, 5 - j)], true);
			}
			num = num % (int)pow(10, 5 - j);
		}
	}
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 255);

	// --�����N�e�L�X�g-- //
	SetDrawBlendMode(DX_BLENDMODE_ADD, 255);
	for (int i = 0; i < 3; i++) {
		DrawGraph(900, 450, rankGraph, true);
	}
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 255);

	// --SABC�����N�e�L�X�g-- //
	SetDrawBlendMode(DX_BLENDMODE_ADD, 255);
	for (int i = 0; i < 3; i++) {
		DrawGraph(1000, 500, sabcBigGraph[0], true);
	}
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 255);

	// --���g���C�e�L�X�g�`��-- //
	SetDrawBlendMode(DX_BLENDMODE_ADD, 255);
	for (int i = 0; i < 3; i++) {
		DrawGraphF(527.5f, 700.0f, retryGraph, true);
	}
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 255);

	// --�^�C�g���փe�L�X�g�`��-- //
	SetDrawBlendMode(DX_BLENDMODE_ADD, 255);
	for (int i = 0; i < 3; i++) {
		DrawGraph(549, 800.0f, gotitleGraph, true);
	}
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 255);

	// --�I��\���`��-- //
	DrawBoxAA(
		selectBox.pos.x - selectBox.radiusX, selectBox.pos.y - selectBox.radiusY,
		selectBox.pos.x + selectBox.radiusX, selectBox.pos.y + selectBox.radiusY,
		0xFFFFFF, false, 3);
}