#include "ResultScene.h"

// --DXライブラリ-- //
#include "DxLib.h"

// --コントローラークラス-- //
#include "JoyPadInput.h"

// --シーンマネージャークラス-- //
#include "SceneManager.h"

// --スコアクラス-- //
#include "Score.h"

// --ゲームシーン-- //
#include "GameScene.h"

// --インスタンスにNULLを代入-- //
ResultScene* ResultScene::myInstance = nullptr;

// --インスタンス読み込み-- //
ResultScene* ResultScene::GetInstance() {
	// --インスタンスが無かったら生成する-- //
	if (myInstance == nullptr) myInstance = new ResultScene();

	// --インスタンスを返す-- //
	return myInstance;
}

// --インスタンス解放-- //
void ResultScene::Relese() {
	// --インスタンスが無かったら何もせずに終了する-- //
	if (myInstance == nullptr) return;

	// --インスタンス解放-- //
	delete myInstance;
	myInstance = nullptr;
}

// --コンストラクタ-- //
ResultScene::ResultScene() {
#pragma region インスタンス読み込み
	// --コントローラークラス-- //
	pad = JoyPadInput::GetInstance();

	// --サウンドクラス-- //
	sound = Sound::GetInstance();
#pragma endregion

#pragma region 画像読み込み
	// --タイトルへ戻るテキスト-- //
	gotitleGraph = LoadGraph("Resources/gotitle.png");

	// --リトライテキスト-- //
	retryGraph = LoadGraph("Resources/retry.png");

	// --ASBCランクのテキスト（小）-- //
	LoadDivGraph("Resources/sabc_small.png", 4, 4, 1, 64, 64, sabcSmallGraph);

	// --ASBCランクのテキスト（大）-- //
	LoadDivGraph("Resources/sabc_Big.png", 4, 4, 1, 111, 111, sabcBigGraph);

	// --スコア表示に使う番号のテキスト-- //
	LoadDivGraph("Resources/numbers_big.png", 10, 10, 1, 64, 120, numberGraph);

	// --ランクテキスト-- //
	rankGraph = LoadGraph("Resources/rank.png");

	// --スコアテキスト-- //
	scoreGraph = LoadGraph("Resources/score_small.png");

	// --リザルトテキスト-- //
	resultGraph = LoadGraph("Resources/result.png");

	// --スコアゲージ-- //
	scoreGaugeGraph = LoadGraph("Resources/scoreGauge.png");

	// --スコアゲージの枠-- //
	scoreGaugeLineGraph = LoadGraph("Resources/scoreGauge_outline.png");

	// --背景-- //
	backGroundGraph = LoadGraph("Resources/backillust.png");
#pragma endregion

	// --選択表示の中心座標-- //
	selectBox = { {640.0f, -300.0f}, 112.5f, 45.5f };

	// --選択中のシーン-- //
	selectScene = 10;

	// --スコアゲージ座標-- //
	gaugeMax = { {1032.0f, 250.0f}, 0.0f, 100.0f };
	gaugeS = { {882.0f, 250.0f}, 0.0f, 100.0f };
	gaugeA = { {732.0f, 250.0f}, 0.0f, 100.0f };
	gaugeB = { {582.0f, 250.0f}, 0.0f, 100.0f };
	gaugeC = { {150.0f, 250.0f}, 0.0f, 100.0f };

	// --各ランクのスコア-- //
	scoreValueMax = 120000;
	scoreValueS = 100000;
	scoreValueA = 60000;
	scoreValueB = 30000;
	scoreValueC = 10000;

	// --入力受付-- //
	isActive = false;

	// --ランクの添字-- //
	rankIndex = 3;

	// --表示するスコア-- //
	displayScore = 0;
}

// --デストラクタ-- //
ResultScene::~ResultScene() {

}

// --初期化処理-- //
void ResultScene::Initialize() {
	// --選択表示の中心座標-- //
	selectBox = { {640.0f, -300.0f}, 112.5f, 45.5f };

	// --選択中のシーン-- //
	selectScene = 10;

	// --スコアゲージ座標-- //
	gaugeMax = { {1032.0f, 250.0f}, 0.0f, 100.0f };
	gaugeS = { {882.0f, 250.0f}, 0.0f, 100.0f };
	gaugeA = { {732.0f, 250.0f}, 0.0f, 100.0f };
	gaugeB = { {582.0f, 250.0f}, 0.0f, 100.0f };
	gaugeC = { {150.0f, 250.0f}, 0.0f, 100.0f };

	// --入力受付-- //
	isActive = false;

	// --ランクの添字-- //
	rankIndex = 3;

	// --表示するスコア-- //
	displayScore = 0;

	graphRad = 0;
}

// --更新処理-- //
void ResultScene::Update() {
	if (isActive == true) {
		// --パッド上下入力されたら-- //
		if (pad->GetButtonTrigger(PAD_INPUT_UP) || pad->GetButtonTrigger(PAD_INPUT_DOWN)) {

			// --SEを流す-- //
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
				// --シーン設定-- //
				SceneManager::SetScene(selectScene);

				if (selectScene == GAMESCENE) {
					GameScene::TutorialSkip(true);
				}
				else if (selectScene == TITLESCENE) {
					GameScene::TutorialSkip(false);
				}

				// --SE再生-- //
				sound->PlaySE(SELECTSE);
			}
		}
	}
	else {
		// --表示するスコアが実際のスコアより小さいとき-- //
		if (displayScore <= Score::GetScore()) {
			// --実際のスコアと表示するスコアの差分-- //
			int addScore = Score::GetScore() - displayScore;

			// --2つのスコアの差分を時間で割る-- //
			displayScore += addScore / 400 + 400;

			// --実際のスコアを超えたら同じ値にする-- //
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

// --描画処理-- //
void ResultScene::Draw() {
	// --背景画像の描画-- //

	SetDrawBlendMode(DX_BLENDMODE_ALPHA,sinf(graphRad / 180 *Util::PI) * 64 + 192 );
	
	DrawGraph(0, 0, backGroundGraph, true);

	// --リザルトテキスト描画-- //
	SetDrawBlendMode(DX_BLENDMODE_ADD, 255);
	for (int i = 0; i < 3; i++) {
		DrawGraphF(371.5f, 30.0f, resultGraph, true);
	}
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 255);

	// --SABCランクテキスト描画-- //
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

	// --スコアゲージの描画-- //
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

	// --スコアゲージ描画-- //
	SetDrawBlendMode(DX_BLENDMODE_ADD, 255);
	for (int i = 0; i < 5; i++) {
		DrawRotaGraph(640, 300, 1.0f, 0.0f, scoreGaugeLineGraph, true);
	}
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 255);

	// --スコアテキスト描画-- //
	SetDrawBlendMode(DX_BLENDMODE_ADD, 255);
	for (int i = 0; i < 3; i++) {
		DrawGraph(150, 450, scoreGraph, true);
	}
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 255);

	// --スコア表示描画-- //
	SetDrawBlendMode(DX_BLENDMODE_ADD, 255);
	int num = displayScore;
	for (int i = 0; i < 6; i++) {
		for (int j = 0; j < 10; j++) {
			DrawGraph(150 + i * 64, 500, numberGraph[num / (int)pow(10, 5 - i)], true);
		}
		num = num % (int)pow(10, 5 - i);
	}
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 255);

	// --ランクテキスト-- //
	SetDrawBlendMode(DX_BLENDMODE_ADD, 255);
	for (int i = 0; i < 3; i++) {
		DrawGraph(900, 450, rankGraph, true);
	}
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 255);

	// --SABCランクテキスト-- //

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

	// --リトライテキスト描画-- //
	SetDrawBlendMode(DX_BLENDMODE_ADD, 255);
	for (int i = 0; i < 3; i++) {
		DrawGraphF(527.5f, 700.0f, retryGraph, true);
	}
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 255);

	// --タイトルへテキスト描画-- //
	SetDrawBlendMode(DX_BLENDMODE_ADD, 255);
	for (int i = 0; i < 3; i++) {
		DrawGraph(549, 800.0f, gotitleGraph, true);
	}
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 255);

	// --選択表示描画-- //
	DrawBoxAA(
		selectBox.pos.x - selectBox.radiusX, selectBox.pos.y - selectBox.radiusY,
		selectBox.pos.x + selectBox.radiusX, selectBox.pos.y + selectBox.radiusY,
		0xFFFFFF, false, 3);
}