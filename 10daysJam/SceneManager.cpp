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
	// --インスタンス読み込み-- //
#pragma region インスタンス読み込み
	// --タイトルシーン-- //
	titleScene = TitleScene::GetInstance();

	// --ゲームシーン-- //
	gameScene = GameScene::GetInstance();

	// --リザルトシーン-- //
	resultScene = ResultScene::GetInstance();

	// --スコア-- //
	score = Score::GetInstance();
#pragma endregion
}

// --デストラクタ-- //
SceneManager::~SceneManager() {
	titleScene->Relese();
	gameScene->Relese();
	resultScene->Relese();
	delete score;
}

// --初期化処理-- //
void SceneManager::Initialize() {
	// --ゲームシーン初期化処理-- //
#pragma region クラス初期化
	// --タイトルシーン-- //
	titleScene->Initialize();

	// --ゲームシーン-- //
	gameScene->Initialize();

	// --リザルトシーン-- //
	resultScene->Initialize();
#pragma endregion
}

// --更新処理-- //
void SceneManager::Update() {
	// --タイトルシーン更新処理-- //
	if (scene == TITLESCENE) {
		titleScene->Update();
	}

	// --ゲームシーン更新処理-- //
	else if (scene == GAMESCENE) {
		// --ゲームシーン更新処理-- //
		gameScene->Update();

		// --スコア更新処理-- //
		score->Update();
	}

	// --リザルトシーン更新処理-- //
	else if (scene == RESULTSCENE) {
		// --リザルトシーン更新処理-- //
		resultScene->Update();
	}
}

// --描画処理-- //
void SceneManager::Draw() {
	// --タイトルシーン描画処理-- //
	if (scene == TITLESCENE) {
		titleScene->Draw();
	}

	// --ゲームシーン描画処理-- //
	else if (scene == GAMESCENE) {
		// --ゲームシーン描画-- //
		gameScene->Draw();

		// --スコア描画-- //
		score->Draw();
	}

	// --リザルトシーン描画処理-- //
	else if (scene == RESULTSCENE) {
		// --リザルトシーン描画処理-- //
		resultScene->Draw();
	}
}

// --シーン切り替え-- //
void SceneManager::SceneChange(int sceneNum) {
	scene = sceneNum;
}