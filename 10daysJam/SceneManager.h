#pragma once
// --DXライブラリ-- //
#include "DxLib.h"

// --タイトルシーンクラス-- //
#include "TitleScene.h"

// --ゲームシーンクラス-- //
#include "GameScene.h"

// --リザルトシーンクラス-- //
#include "ResultScene.h"

// --スコアクラス-- //
#include "Score.h"

// --サウンドクラス-- //
#include "Sound.h"

// --入力クラス-- //
#include "Input.h"

// --シーン番号-- //
enum SceneNum {
	TITLESCENE,
	GAMESCENE,
	RESULTSCENE
};

class SceneManager {

	/// --メンバ変数-- ///
public:

private:
	// --インスタンス-- //
	static SceneManager* myInstance;

#pragma region クラス宣言
	// --タイトルシーン-- //
	TitleScene* titleScene;

	// --ゲームシーン-- //
	GameScene* gameScene;

	// --リザルトシーン-- //
	ResultScene* resultScene;

	// --スコア-- //
	Score* score;

	// --サウンド-- //
	Sound* sound;

	// --入力-- //
	Input* input;
#pragma endregion

#pragma region シーン関係変数

	// --シーンの番号-- //
	int scene;

	// --変更するシーン-- //
	static int changeScene;

	// --シーン変更フラグ-- //
	static bool isChangeScene;

	// --シーンを移動する際の時間-- //
	int sceneInterval;

	// --タイマー-- //
	int timer;

	// --円のサイズ-- //
	int circleSize;
	
	// --円の拡縮の速度-- //
	int sizeChangeSpeed;

	// --スクリーンハンドル-- //
	int screenHandle;

	// --フェードアウトするか-- //
	bool isFadeOut;

	// --フェードイン
	bool isFadeIn;

#pragma endregion

	// --ぼかした円の画像-- //
	int circleGraph;

	// --デバッグモードフラグ-- //
	static bool isDebugMode;

	/// --メンバ変数END-- ///
	/// --------------- ///
	/// --メンバ関数-- ///
public:
	// --インスタンス取得-- //
	static SceneManager* GetInstance();

	// --インスタンス解放-- //
	void Relese();

	// --デストラクタ-- //
	~SceneManager();

	// --初期化処理-- //
	void Initialize();

	// --更新処理-- //
	void Update();

	// --描画処理-- //
	void Draw();

	// --シーンを設定-- //
	static void SetScene(int sceneNum);

	// --シーン変更更新処理-- //
	void UpdateChangeScene();

	// --シーン変更描画処理-- //
	void DrawChangeScene();

	// --デバッグモードか取得-- //
	static bool GetDebugMode();

private:
	// --コンストラクタ-- //
	SceneManager();

	/// --メンバ関数END-- ///
};