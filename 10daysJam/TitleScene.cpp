#include "TitleScene.h"

// --DXライブラリ-- //
#include "DxLib.h"

// --シーンマネージャークラス-- //
#include "SceneManager.h"

// --インスタンスにNULLを代入-- //
TitleScene* TitleScene::myInstance = nullptr;

// --インスタンス読み込み-- //
TitleScene* TitleScene::GetInstance() {
	// --インスタンスが無かったら生成する-- //
	if (myInstance == nullptr) myInstance = new TitleScene();

	// --インスタンスを返す-- //
	return myInstance;
}

// --インスタンス解放-- //
void TitleScene::Relese() {
	// --インスタンスが無かったら何もせずに終了する-- //
	if (myInstance == nullptr) return;

	// --インスタンス解放-- //
	delete myInstance;
	myInstance = nullptr;
}

// --コンストラクタ-- //
TitleScene::TitleScene() {
#pragma region インスタンス読み込み
	// --コントローラー-- //
	pad = JoyPadInput::GetInstance();

	// --サウンド-- //
	sound = Sound::GetInstance();
#pragma endregion

#pragma region 画像読み込み
	// --タイトルロゴ-- //
	LoadDivGraph("Resources/titleRogo.png", 4, 4, 1, 572, 572, titlelogoGraph);

	// --背景-- //
	backGroundGraph = LoadGraph("Resources/backillust.png");

	// --タイトルのUI-- //
	LoadDivGraph("Resources/titleUI.png", 2, 2, 1, 348, 64, titleUIGraph);

	// --十字キー-- //
	LoadDivGraph("Resources/selectUI.png", 4, 4, 1, 385, 205, selectUIGraph);

	// --ボタン-- //
	LoadDivGraph("Resources/controller_button.png", 3, 3, 1, 82, 82, buttonGraph);
#pragma endregion

	// --選択表示の中心座標-- //
	selectBox = { {640.0f, -300.0f}, 174.0f, 32.0f };

	pos = { 1180, 857.5f };
}

// --デストラクタ-- //
TitleScene::~TitleScene() {

}

// --初期化処理-- //
void TitleScene::Initialize() {
	// --選択表示の中心座標-- //
	selectBox = { {640.0f, -300.0f}, 174.0f, 32.0f };

	graphRad = 0;
}

// --更新処理-- //
void TitleScene::Update() {
	// --Aボタンを押すとゲームシーンに移動-- //
	if (pad->GetButtonTrigger(PAD_INPUT_1)) {
		if (selectBox.pos.y == 750.0f) {
			// --シーン変更-- //
			SceneManager::SetScene(GAMESCENE);

			// --SEを再生-- //
			sound->PlaySE(SELECTSE);
		}
		else if (selectBox.pos.y == 850.0f) {
			// --SEを再生-- //
			sound->PlaySE(SELECTSE);

			// --ゲームエンドフラグをtrueにする-- //
			SceneManager::EndTrue();
		}
	}

	if (pad->GetButtonTrigger(PAD_INPUT_UP) || pad->GetButtonTrigger(PAD_INPUT_DOWN)) {
		// --SEを再生-- //
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

// --描画処理-- //
void TitleScene::Draw() {
	// --背景画像の描画-- //
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, sinf(graphRad / 180 * Util::PI) * 64 + 128);
	DrawGraph(0, 0, backGroundGraph, true);

#pragma region タイトルロゴ描画処理
	SetDrawBlendMode(DX_BLENDMODE_ADD, sinf(graphRad / 180  * Util::PI) * 64 + 128);

	// --0番-- //
	Util::SetDrawBright2(LIGHTBLUE);
	for (int i = 0; i < 20; i++) {
		DrawGraph(354, 60, titlelogoGraph[0], true);
	}

	// --1番-- //
	//SetDrawBright(39, 32, 225);
	for (int i = 0; i < 20; i++) {
		DrawGraph(354, 60, titlelogoGraph[1], true);
	}

	// --2番-- //
	Util::SetDrawBright2(PURPLE);
	for (int i = 0; i < 20; i++) {
		DrawGraph(354, 60, titlelogoGraph[2], true);
	}

	// --3番-- //
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

	// --十字キー描画-- //
	DrawRotaGraphF(1087.5f, 857.5f, 1.0f, 0.0f, selectUIGraph[3], true);
	SetDrawBlendMode(DX_BLENDMODE_ADD, 255);
	Util::SetDrawBright2(RED);
	for (int i = 0; i < 5; i++) {
		DrawRotaGraphF(1087.5f, 857.5f, 1.0f, 0.0f, selectUIGraph[2], true);
	}
	SetDrawBright(255, 255, 255);

	for (int i = 0; i < 20; i++) {
		DrawRotaGraphF(1087.5f, 857.5f, 1.0f, 0.0f, selectUIGraph[0], true);
	}
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 255);
	DrawRotaGraphF(1087.5f, 857.5f, 1.0f, 0.0f, selectUIGraph[1], true);

	DrawRotaGraphF(pos.x, pos.y - 55, 0.8f, 0.0f, buttonGraph[0], true);
	DrawRotaGraphF(pos.x - 55, pos.y, 0.8f, 0.0f, buttonGraph[0], true);
	SetDrawBlendMode(DX_BLENDMODE_ADD, 255);
	Util::SetDrawBright2(GREEN);
	for (int i = 0; i < 20; i++) {
		DrawRotaGraphF(pos.x, pos.y + 55, 0.8f, 0.0f, buttonGraph[1], true);
	}
	SetDrawBright(255, 255, 255);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 255);
	DrawRotaGraphF(pos.x + 55, pos.y, 0.8f, 0.0f, buttonGraph[2], true);

#pragma endregion
}