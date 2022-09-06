#include "GameClearScene.h"
#include "SceneManager.h"

// --インスタンスにNULLを代入-- //
GameClearScene* GameClearScene::myInstance = nullptr;

// --インスタンス読み込み-- //
GameClearScene* GameClearScene::GetInstance() {
	// --インスタンスが無かったら生成する-- //
	if (myInstance == nullptr) myInstance = new GameClearScene();

	// --インスタンスを返す-- //
	return myInstance;
}

// --コンストラクタ-- //
GameClearScene::GameClearScene() {

}

// --デストラクタ-- //
GameClearScene::~GameClearScene() {

}

// --初期化処理-- //
void GameClearScene::Initialize() {

}

// --更新処理-- //
void GameClearScene::Update() {
	
}

// --描画処理-- //
void GameClearScene::Draw() {

}