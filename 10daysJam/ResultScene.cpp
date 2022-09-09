#include "ResultScene.h"

// --コントローラークラス-- //
#include "JoyPadInput.h"

// --シーンマネージャークラス-- //
#include "SceneManager.h"

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
#pragma endregion
}

// --デストラクタ-- //
ResultScene::~ResultScene() {

}

// --初期化処理-- //
void ResultScene::Initialize() {

}

// --更新処理-- //
void ResultScene::Update() {

}

// --描画処理-- //
void ResultScene::Draw() {

}