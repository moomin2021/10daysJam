#include "SceneManager.h"

// --便利系クラス-- //
#include "Util.h"

using namespace Util;

// --インスタンスにNULLを代入-- //
SceneManager* SceneManager::myInstance = nullptr;

// --変更するシーンの初期化-- //
int SceneManager::changeScene = 0;

// --シーン変更フラグの初期化-- //
bool SceneManager::isChangeScene = false;

bool SceneManager::isDebugMode = false;

// --インスタンス読み込み-- //
SceneManager* SceneManager::GetInstance() {
	// --インスタンスが無かったら生成する-- //
	if (myInstance == nullptr) myInstance = new SceneManager();

	// --インスタンスを返す-- //
	return myInstance;
}

// --インスタンス解放-- //
void SceneManager::Relese() {
	// --インスタンスが無かったら何もせずに終了する-- //
	if (myInstance == nullptr) return;

	// --インスタンス解放-- //
	delete myInstance;
	myInstance = nullptr;
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

	// --サウンド-- //
	sound = Sound::GetInstance();

	// --入力-- //
	input = Input::GetInstance();
#pragma endregion

	// --シーン-- //
	scene = TITLESCENE;

	// --シーンを移動する際の時間-- //
	sceneInterval = 100;

	// --タイマー-- //
	timer = 0;

	// --円のサイズ-- //
	circleSize = 800;

	// --円の拡縮の速度-- //
	sizeChangeSpeed = 20;

	// --スクリーンハンドル-- //
	screenHandle = MakeScreen(1280, 960, true);

	// --フェードアウトするか-- //
	isFadeOut = true;

	// --フェードイン
	isFadeIn = false;

	circleGraph = LoadGraph("Resources/SceneChangeCircle.png");
}

// --デストラクタ-- //
SceneManager::~SceneManager() {
	titleScene->Relese();
	gameScene->Relese();
	resultScene->Relese();
	score->Relese();
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

	// --最初にタイトルシーンのBGMを再生-- //
	sound->PlayBGM(TITLESCENEBGM);
}

// --更新処理-- //
void SceneManager::Update() {
	// --デバッグモード切替え-- //
	if (input->IsTrigger(KEY_INPUT_F1)) {
		isDebugMode = !isDebugMode;
	}

	if (isChangeScene == false) {
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

	// --シーン変更更新処理-- //
	UpdateChangeScene();
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
		if (gameScene->GetIsMainGame()) {
			score->Draw();
		}
	}

	// --リザルトシーン描画処理-- //
	else if (scene == RESULTSCENE) {
		// --リザルトシーン描画処理-- //
		resultScene->Draw();
	}

	// --シーン変更描画処理-- //
	DrawChangeScene();
}

// --シーン切り替え-- //
void SceneManager::SetScene(int sceneNum) {
	changeScene = sceneNum;
	isChangeScene = true;
}

// --シーン変更処理-- //
void SceneManager::UpdateChangeScene() {
	// --シーン変更フラグ--trueだったら //
	if (isChangeScene == true) {
		// --フェードアウト-- //
		if (isFadeOut == true) {
			if (circleSize > 0) {
				circleSize -= sizeChangeSpeed;
			}

			else if (circleSize <= 0) {
				timer++;
				if (timer >= sceneInterval) {
					sound->StopBGM(scene);
					isFadeOut = false;
					isFadeIn = true;
					scene = changeScene;
					timer = 0;
					sound->PlayBGM(scene);
				}
			}
		}

		// --フェードイン-- //
		else if (isFadeIn == true) {
			circleSize += sizeChangeSpeed;

			if (circleSize >= 800) {
				isFadeOut = true;
				isFadeIn = false;
				isChangeScene = false;
				circleSize = 800;
			}
		}
	}
}

// --シーン変更描画処理-- //
void SceneManager::DrawChangeScene() {
	// --シーン変更フラグがtrueだったら-- //
	if (isChangeScene) {
		SetDrawScreen(screenHandle);

		DrawBox(0, 0, 1280, 960, 0x000000, true);

		SetDrawBlendMode(DX_BLENDMODE_ADD, 255);

		// --色-- //
		Color color = GetColor16("2720e1");

		SetDrawBright(color.red, color.green, color.blue);

		// --横線-- //
		for (int i = 0; i < 1280; i++) {
			DrawRotaGraph(i, 480, 0.20f, 0.0f, circleGraph, true);
		}

		// --横線-- //
		for (int i = 0; i < 960; i++) {
			DrawRotaGraph(640, i, 0.20f, 0.0f, circleGraph, true);
		}

		// --透明な円の外側の装飾-- //
		for (int i = 0; i < circleSize * 2.1f; i++) {
			DrawRotaGraphF(
				640.0f + cosf(Degree2Radian((360.0f / (circleSize * 2.1f)) * i)) * (circleSize + 13),
				480.0f + sinf(Degree2Radian((360.0f / (circleSize * 2.1f)) * i)) * (circleSize + 13),
				0.375f, 0.0f,
				circleGraph, true
			);
		}

		SetDrawBright(255, 255, 255);

		SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 255);

		SetDrawBlendMode(DX_BLENDMODE_SRCCOLOR, 0);

		if (circleSize > 0) {
			DrawCircle(640, 480, circleSize, 0x000000, true);
		}

		SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);

		SetDrawScreen(DX_SCREEN_BACK);

		DrawGraph(0, 0, screenHandle, true);
	}

	// --デバッグモード-- //
	if (isDebugMode == true) {

	}
}

// --デバッグモードか取得-- //
bool SceneManager::GetDebugMode() {
	return isDebugMode;
}