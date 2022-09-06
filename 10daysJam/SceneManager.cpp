#include "SceneManager.h"

// --インスタンスにNULLを代入-- //
SceneManager* SceneManager::myInstance = nullptr;

// --シーンの初期化-- //
int SceneManager::scene = GAMESCENE;

// --インスタンス読み込み-- //
SceneManager* SceneManager::GetInstance() {
	// --インスタンスが無かったら生成する-- //
	if (myInstance == nullptr) myInstance = new SceneManager();

	// --インスタンスを返す-- //
	return myInstance;
}

// --コンストラクタ-- //
SceneManager::SceneManager() {
	gameScene = GameScene::GetInstance();
}

// --デストラクタ-- //
SceneManager::~SceneManager() {

}

// --初期化処理-- //
void SceneManager::Initialize() {
	// --ゲームシーン初期化処理-- //
	gameScene->Initialize();
}

// --更新処理-- //
void SceneManager::Update() {
	// --タイトルシーン更新処理-- //
	if (scene == TITLESCENE) {

	}

	// --ゲームシーン更新処理-- //
	else if (scene == GAMESCENE) {
		// --ゲームシーン更新処理-- //
		gameScene->Update();
	}

	// --ゲームクリアシーン更新処理-- //
	else if (scene == GAMECLEARSCENE) {

	}

	// --ゲームオーバーシーン更新処理-- //
	else if (scene == GAMEOVERSCENE) {

	}
}

// --描画処理-- //
void SceneManager::Draw() {
	// --タイトルシーン描画処理-- //
	if (scene == TITLESCENE) {

	}

	// --ゲームシーン描画処理-- //
	else if (scene == GAMESCENE) {
		// --ゲームシーン描画-- //
		gameScene->Draw();
	}

	// --ゲームクリアシーン描画処理-- //
	else if (scene == GAMECLEARSCENE) {

	}

	// --ゲームオーバーシーン描画処理-- //
	else if (scene == GAMEOVERSCENE) {

	}
}

// --シーン切り替え-- //
void SceneManager::SceneChange(int sceneNum) {
	scene = sceneNum;
}