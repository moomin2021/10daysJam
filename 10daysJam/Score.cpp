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

// --�R���X�g���N�^-- //
Score::Score() : displayScore(0), scoreTime(10) {

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
	DrawFormatString(800, 0, 0xFFFFFF, "%06d", displayScore);
	DrawFormatString(0, 200, 0xFFFFFF, "���ۂ̃X�R�A = %d", realScore);
	DrawFormatString(0, 220, 0xFFFFFF, "�\������X�R�A = %d", displayScore);
}

// --�w�肵���������X�R�A���Z-- //
void Score::AddScore(int value) {
	realScore += value;
}