#include "Score.h"
#include "DxLib.h"
#include "Util.h"
using namespace Util;

// --�C���X�^���X��NULL����-- //
Score* Score::myInstance = nullptr;

// --�X�R�A��0����-- //
int Score::realScore = 0;

// --�C���X�^���X�ǂݍ���-- //
Score* Score::GetInstance() {
	// --�C���X�^���X�����������琶������-- //
	if (myInstance == nullptr) myInstance = new Score();

	// --�C���X�^���X��Ԃ�-- //
	return myInstance;
}

// --�C���X�^���X���-- //
void Score::Relese() {
	// --�C���X�^���X�����������牽�������ɏI������-- //
	if (myInstance == nullptr) return;

	// --�C���X�^���X���-- //
	delete myInstance;
	myInstance = nullptr;
}

// --�R���X�g���N�^-- //
Score::Score() : displayScore(0), scoreTime(10) {
	// --�\������X�R�A-- //
	displayScore = 0;

	// --�X�R�A���Z���鎞��-- //
	scoreTime = 10;

#pragma region �摜�ǂݍ���
	// --����-- //
	LoadDivGraph("Resources/numbers_small.png", 10, 10, 1, 32, 58, numberGraph);

	// --�X�R�A�e�L�X�g-- //
	scoreGraph = LoadGraph("Resources/score_small.png");
#pragma endregion
}

// --�f�X�g���N�^-- //
Score::~Score() {

}

// --����������-- //
void Score::Initialize() {
	// --�\������X�R�A�̏�����-- //
	displayScore = 0;

	// --���ۂ̃X�R�A�̏�����-- //
	realScore = 0;

	// --�X�R�A���Z�̎��ԏ�����-- //
	scoreTime = 10;
}

// --�X�V����-- //
void Score::Update() {
	// --�\������X�R�A�����ۂ̃X�R�A��菬�����Ƃ�-- //
	if (displayScore < realScore) {
		// --���ۂ̃X�R�A�ƕ\������X�R�A�̍���-- //
		int addScore = realScore - displayScore;

		// --2�̃X�R�A�̍��������ԂŊ���-- //
		displayScore += addScore / scoreTime + scoreTime;

		// --���ۂ̃X�R�A�𒴂����瓯���l�ɂ���-- //
		if (displayScore > realScore) {
			displayScore = realScore;
		}
	}
}

// --�`�揈��-- //
void Score::Draw() {
	int num = displayScore;
	SetDrawBlendMode(DX_BLENDMODE_ADD, 255);
	SetDrawBright(119, 28, 28);

	// --�X�R�A�`��-- //
	for (int i = 0; i < 6; i++) {
		for (int j = 0; j < 15; j++) {
			DrawGraph(1088 + i * 32, 0, numberGraph[num / (int)pow(10, 5 - i)], true);
		}
		num = num % (int)pow(10, 5 - i);
	}

	// --�X�R�A�e�L�X�g�`��-- //
	for (int i = 0; i < 15; i++) {
		DrawGraph(1149, 58, scoreGraph, true);
	}

	SetDrawBright(255, 255, 255);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 255);
}

// --�w�肵���������X�R�A���Z-- //
void Score::AddScore(int value) {
	realScore += value;
}

// --�X�R�A���Q��-- //
int Score::GetScore() { return realScore; }