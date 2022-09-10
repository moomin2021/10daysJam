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
#pragma endregion

#pragma region �摜�ǂݍ���
	// --�^�C�g���֖߂�e�L�X�g-- //
	gotitleGraph = LoadGraph("Resources/gotitle.png");

	// --���g���C�e�L�X�g-- //
	retryGraph = LoadGraph("Resources/retry.png");

	// --ASBC�����N�̃e�L�X�g-- //
	LoadDivGraph("Resources/sabc_small.png", 4, 4, 1, 64, 64, sabcGraph);

	// --�X�R�A�\���Ɏg���ԍ��̃e�L�X�g-- //
	LoadDivGraph("Resources/numbers_big.png", 10, 10, 1, 64, 120, numberGraph);

	// --�����N�e�L�X�g-- //
	rankGraph = LoadGraph("Resources/rank.png");

	// --�X�R�A�e�L�X�g-- //
	scoreGraph = LoadGraph("Resources/score_small.png");

	// --���U���g�e�L�X�g-- //
	resultGraph = LoadGraph("Resources/result.png");
#pragma endregion
}

// --�f�X�g���N�^-- //
ResultScene::~ResultScene() {

}

// --����������-- //
void ResultScene::Initialize() {

}

// --�X�V����-- //
void ResultScene::Update() {

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

	// --�����N�e�L�X�g�`��-- //
	SetDrawBlendMode(DX_BLENDMODE_ADD, 255);
	for (int i = 0; i < 3; i++) {
		DrawGraph(550, 350, sabcGraph[3], true);
		DrawGraph(700, 350, sabcGraph[2], true);
		DrawGraph(850, 350, sabcGraph[1], true);
		DrawGraph(1000, 350, sabcGraph[0], true);
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
}