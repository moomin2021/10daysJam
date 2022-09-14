#include "ResultScene.h"

// --DX���C�u����-- //
#include "DxLib.h"

// --�R���g���[���[�N���X-- //
#include "JoyPadInput.h"

// --�V�[���}�l�[�W���[�N���X-- //
#include "SceneManager.h"

// --�X�R�A�N���X-- //
#include "Score.h"

// --�Q�[���V�[��-- //
#include "GameScene.h"

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

	// --�X�R�A�Q�[�W-- //
	scoreGaugeGraph = LoadGraph("Resources/scoreGauge.png");

	// --�X�R�A�Q�[�W�̘g-- //
	scoreGaugeLineGraph = LoadGraph("Resources/scoreGauge_outline.png");

	// --�w�i-- //
	backGroundGraph = LoadGraph("Resources/backillust.png");
#pragma endregion

	// --�I��\���̒��S���W-- //
	selectBox = { {640.0f, -300.0f}, 112.5f, 45.5f };

	// --�I�𒆂̃V�[��-- //
	selectScene = 10;

	// --�X�R�A�Q�[�W���W-- //
	gaugeMax = { {1032.0f, 250.0f}, 0.0f, 100.0f };
	gaugeS = { {882.0f, 250.0f}, 0.0f, 100.0f };
	gaugeA = { {732.0f, 250.0f}, 0.0f, 100.0f };
	gaugeB = { {582.0f, 250.0f}, 0.0f, 100.0f };
	gaugeC = { {150.0f, 250.0f}, 0.0f, 100.0f };

	// --�e�����N�̃X�R�A-- //
	scoreValueMax = 120000;
	scoreValueS = 100000;
	scoreValueA = 60000;
	scoreValueB = 30000;
	scoreValueC = 10000;

	// --���͎�t-- //
	isActive = false;

	// --�����N�̓Y��-- //
	rankIndex = 3;

	// --�\������X�R�A-- //
	displayScore = 0;
}

// --�f�X�g���N�^-- //
ResultScene::~ResultScene() {

}

// --����������-- //
void ResultScene::Initialize() {
	// --�I��\���̒��S���W-- //
	selectBox = { {640.0f, -300.0f}, 112.5f, 45.5f };

	// --�I�𒆂̃V�[��-- //
	selectScene = 10;

	// --�X�R�A�Q�[�W���W-- //
	gaugeMax = { {1032.0f, 250.0f}, 0.0f, 100.0f };
	gaugeS = { {882.0f, 250.0f}, 0.0f, 100.0f };
	gaugeA = { {732.0f, 250.0f}, 0.0f, 100.0f };
	gaugeB = { {582.0f, 250.0f}, 0.0f, 100.0f };
	gaugeC = { {150.0f, 250.0f}, 0.0f, 100.0f };

	// --���͎�t-- //
	isActive = false;

	// --�����N�̓Y��-- //
	rankIndex = 3;

	// --�\������X�R�A-- //
	displayScore = 0;

	graphRad = 0;
}

// --�X�V����-- //
void ResultScene::Update() {
	if (isActive == true) {
		// --�p�b�h�㉺���͂��ꂽ��-- //
		if (pad->GetButtonTrigger(PAD_INPUT_UP) || pad->GetButtonTrigger(PAD_INPUT_DOWN)) {

			// --SE�𗬂�-- //
			sound->PlaySE(BUTTONSE);

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

				if (selectScene == GAMESCENE) {
					GameScene::TutorialSkip(true);
				}
				else if (selectScene == TITLESCENE) {
					GameScene::TutorialSkip(false);
				}

				// --SE�Đ�-- //
				sound->PlaySE(SELECTSE);
			}
		}
	}
	else {
		// --�\������X�R�A�����ۂ̃X�R�A��菬�����Ƃ�-- //
		if (displayScore <= Score::GetScore()) {
			// --���ۂ̃X�R�A�ƕ\������X�R�A�̍���-- //
			int addScore = Score::GetScore() - displayScore;

			// --2�̃X�R�A�̍��������ԂŊ���-- //
			displayScore += addScore / 400 + 400;

			// --���ۂ̃X�R�A�𒴂����瓯���l�ɂ���-- //
			if (displayScore >= Score::GetScore()) {
				displayScore = Score::GetScore();
				isActive = true;
			}
		}

		if (scoreValueC > displayScore) {
			gaugeC.width = (432.0f / scoreValueC) * displayScore;
			rankIndex = 3;
		}

		else if (scoreValueB > displayScore) {
			gaugeC.width = 432.0f;
			gaugeB.width = (150.0f / (scoreValueB - scoreValueC)) * (displayScore - scoreValueC);
			rankIndex = 3;
		}

		else if (scoreValueA > displayScore) {
			gaugeB.width = 150.0f;
			gaugeA.width = (150.0f / (scoreValueA - scoreValueB)) * (displayScore - scoreValueB);
			rankIndex = 2;
		}

		else if (scoreValueS > displayScore) {
			gaugeA.width = 150.0f;
			gaugeS.width = (150.0f / (scoreValueS - scoreValueA)) * (displayScore - scoreValueA);
			rankIndex = 1;
		}

		else if (scoreValueMax > displayScore) {
			gaugeS.width = 150.0f;
			gaugeMax.width = (98.0f / (scoreValueMax - scoreValueS)) * (displayScore - scoreValueS);
			rankIndex = 0;
		}
		else if (displayScore > scoreValueMax) {
			gaugeMax.width = 98.0f;
		}
	}

	graphRad += 3.0f;
	if (graphRad > 360.0f) {
		graphRad -= 360.0f;
	}
}

// --�`�揈��-- //
void ResultScene::Draw() {
	// --�w�i�摜�̕`��-- //

	SetDrawBlendMode(DX_BLENDMODE_ALPHA,sinf(graphRad / 180 *Util::PI) * 64 + 192 );
	
	DrawGraph(0, 0, backGroundGraph, true);

	// --���U���g�e�L�X�g�`��-- //
	SetDrawBlendMode(DX_BLENDMODE_ADD, 255);
	for (int i = 0; i < 3; i++) {
		DrawGraphF(371.5f, 30.0f, resultGraph, true);
	}
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 255);

	// --SABC�����N�e�L�X�g�`��-- //
	SetDrawBlendMode(DX_BLENDMODE_ADD, 255);
	for (int i = 0; i < 20; i++) {
		SetDrawBright(21, 39, 19);
		DrawGraph(550, 350, sabcSmallGraph[3], true);
	}
	for (int i = 0; i < 10; i++) {
		SetDrawBright(97, 94, 19);
		DrawGraph(700, 350, sabcSmallGraph[2], true);
		SetDrawBright(97, 42, 17);
		DrawGraph(850, 350, sabcSmallGraph[1], true);
		SetDrawBright(119, 28, 28);
		DrawGraph(1000, 350, sabcSmallGraph[0], true);
	}
	SetDrawBright(255, 255, 255);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 255);

	// --�X�R�A�Q�[�W�̕`��-- //
	SetDrawBlendMode(DX_BLENDMODE_ADD, 255);
	for (int i = 0; i < 8; i++) {
		SetDrawBright(119, 28, 28);
		DrawExtendGraph(gaugeMax.pos.x, gaugeMax.pos.y, gaugeMax.pos.x + gaugeMax.width, gaugeMax.pos.y + gaugeMax.height, scoreGaugeGraph, true);
		SetDrawBright(97, 42, 17);
		DrawExtendGraph(gaugeS.pos.x, gaugeS.pos.y, gaugeS.pos.x + gaugeS.width, gaugeS.pos.y + gaugeS.height, scoreGaugeGraph, true);
		SetDrawBright(97, 94, 19);
		DrawExtendGraph(gaugeA.pos.x, gaugeA.pos.y, gaugeA.pos.x + gaugeA.width, gaugeA.pos.y + gaugeA.height, scoreGaugeGraph, true);
		SetDrawBright(21, 39, 19);
		DrawExtendGraph(gaugeB.pos.x, gaugeB.pos.y, gaugeB.pos.x + gaugeB.width, gaugeB.pos.y + gaugeB.height, scoreGaugeGraph, true);
		SetDrawBright(26, 121, 113);
		DrawExtendGraph(gaugeC.pos.x, gaugeC.pos.y, gaugeC.pos.x + gaugeC.width, gaugeC.pos.y + gaugeC.height, scoreGaugeGraph, true);
	}
	SetDrawBright(255, 255, 255);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 255);

	// --�X�R�A�Q�[�W�`��-- //
	SetDrawBlendMode(DX_BLENDMODE_ADD, 255);
	for (int i = 0; i < 5; i++) {
		DrawRotaGraph(640, 300, 1.0f, 0.0f, scoreGaugeLineGraph, true);
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
	int num = displayScore;
	for (int i = 0; i < 6; i++) {
		for (int j = 0; j < 10; j++) {
			DrawGraph(150 + i * 64, 500, numberGraph[num / (int)pow(10, 5 - i)], true);
		}
		num = num % (int)pow(10, 5 - i);
	}
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 255);

	// --�����N�e�L�X�g-- //
	SetDrawBlendMode(DX_BLENDMODE_ADD, 255);
	for (int i = 0; i < 3; i++) {
		DrawGraph(900, 450, rankGraph, true);
	}
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 255);

	// --SABC�����N�e�L�X�g-- //

	SetDrawBlendMode(DX_BLENDMODE_ADD, sinf(graphRad / 180 * Util::PI) * 64 + 192);
	Color color;
	if (rankIndex == 3) color = Util::GetColor16("0x152713");
	if (rankIndex == 2) color = Util::GetColor16("0x615e13");
	if (rankIndex == 1) color = Util::GetColor16("0x612a11");
	if (rankIndex == 0) color = Util::GetColor16("0x771c1c");
	SetDrawBright(color.red, color.green, color.blue);
	for (int i = 0; i < 16; i++) {
		DrawGraph(1000, 500, sabcBigGraph[rankIndex], true);
	}
	SetDrawBright(255, 255, 255);
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