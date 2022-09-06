#include "GameOverScene.h"

// --インスタンスにNULLを代入-- //
GameOverScene* GameOverScene::myInstance = nullptr;

// --インスタンス読み込み-- //
GameOverScene* GameOverScene::GetInstance() {
	// --インスタンスが無かったら生成する-- //
	if (myInstance == nullptr) myInstance = new GameOverScene();

	// --インスタンスを返す-- //
	return myInstance;
}

// --コンストラクタ-- //
GameOverScene::GameOverScene() {

}

// --デストラクタ-- //
GameOverScene::~GameOverScene() {

}

// --初期化処理-- //
void GameOverScene::Initialize() {

}

// --更新処理-- //
void GameOverScene::Update() {

}

// --描画処理-- //
void GameOverScene::Draw() {

}