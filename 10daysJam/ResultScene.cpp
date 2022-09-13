#include "ResultScene.h"

// --DXライブラリ-- //
#include "DxLib.h"

// --コントローラークラス-- //
#include "JoyPadInput.h"

// --シーンマネージャークラス-- //
#include "SceneManager.h"

// --スコアクラス-- //
#include "Score.h"

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
#pragma endregion

	// --選択表示の中心座標-- //
	selectBox = {{640.0f, -300.0f}, 112.5f, 45.5f};

	// --選択中のシーン-- //
	selectScene = 10;
}

// --デストラクタ-- //
ResultScene::~ResultScene() {

}

// --初期化処理-- //
void ResultScene::Initialize() {

}

// --更新処理-- //
void ResultScene::Update() {
	// --パッド上下入力されたら-- //
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
			// --シーン設定-- //
			SceneManager::SetScene(selectScene);

			// --SE再生-- //
			sound->PlaySE(SELECTSE);
		}
	}
}

// --描画処理-- //
void ResultScene::Draw() {
	// --リザルトテキスト描画-- //
	SetDrawBlendMode(DX_BLENDMODE_ADD, 255);
	for (int i = 0; i < 3; i++) {
		DrawGraphF(371.5f, 30.0f, resultGraph, true);
	}
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 255);

	// --スコアゲージ描画-- //
	DrawLine(150, 250, 1130, 250, 0xFFFFFF, 5);
	DrawLine(150, 350, 1130, 350, 0xFFFFFF, 5);
	DrawLine(150, 250, 150, 350, 0xFFFFFF, 5);
	DrawLine(1130, 250, 1130, 350, 0xFFFFFF, 5);

	// --SABCランクテキスト描画-- //
	SetDrawBlendMode(DX_BLENDMODE_ADD, 255);
	for (int i = 0; i < 3; i++) {
		DrawGraph(550, 350, sabcSmallGraph[3], true);
		DrawGraph(700, 350, sabcSmallGraph[2], true);
		DrawGraph(850, 350, sabcSmallGraph[1], true);
		DrawGraph(1000, 350, sabcSmallGraph[0], true);
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

	// --ランクテキスト-- //
	SetDrawBlendMode(DX_BLENDMODE_ADD, 255);
	for (int i = 0; i < 3; i++) {
		DrawGraph(900, 450, rankGraph, true);
	}
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 255);

	// --SABCランクテキスト-- //
	SetDrawBlendMode(DX_BLENDMODE_ADD, 255);
	for (int i = 0; i < 3; i++) {
		DrawGraph(1000, 500, sabcBigGraph[0], true);
	}
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