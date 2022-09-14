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
#pragma endregion
}

// --デストラクタ-- //
TitleScene::~TitleScene() {

}

// --初期化処理-- //
void TitleScene::Initialize() {

}

// --更新処理-- //
void TitleScene::Update() {
	// --Aボタンを押すとゲームシーンに移動-- //
	if (pad->GetButtonTrigger(PAD_INPUT_1)) {
		// --シーン変更-- //
		SceneManager::SetScene(GAMESCENE);
		// --SEを再生-- //
		sound->PlaySE(SELECTSE);
	}
}

// --描画処理-- //
void TitleScene::Draw() {
	// --背景画像の描画-- //
	DrawGraph(0, 0, backGroundGraph, true);

#pragma region タイトルロゴ描画処理
	SetDrawBlendMode(DX_BLENDMODE_ADD, 255);
	
	// --0番-- //
	SetDrawBright(39, 32, 225);
	for (int i = 0; i < 20; i++) {
		DrawGraph(354, 194, titlelogoGraph[0], true);
	}

	// --1番-- //
	SetDrawBright(39, 32, 225);
	for (int i = 0; i < 20; i++) {
		DrawGraph(354, 194, titlelogoGraph[1], true);
	}

	// --2番-- //
	SetDrawBright(39, 32, 225);
	for (int i = 0; i < 20; i++) {
		DrawGraph(354, 194, titlelogoGraph[2], true);
	}

	// --3番-- //
	SetDrawBright(39, 32, 225);
	for (int i = 0; i < 20; i++) {
		DrawGraph(354, 194, titlelogoGraph[3], true);
	}

	SetDrawBright(255, 255, 255);

	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 255);
#pragma endregion
}