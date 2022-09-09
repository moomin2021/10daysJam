#pragma once
// --DXライブラリ-- //
#include "DxLib.h"

// --ゲームシーンクラス-- //
#include "GameScene.h"

// --リザルトシーンクラス-- //
#include "ResultScene.h"

// --スコアクラス-- //
#include "Score.h"

class SceneManager {

	// --シーン番号-- //
	enum SceneNum {
		TITLESCENE,
		GAMESCENE,
		RESULTSCENE
	};

	/// --メンバ変数-- ///
public:

private:
	// --インスタンス-- //
	static SceneManager* myInstance;

#pragma region クラス宣言
	// --ゲームシーン-- //
	GameScene* gameScene;

	// --リザルトシーン-- //
	ResultScene* resultScene;

	// --スコア-- //
	Score* score;
#pragma endregion

	// --シーンの番号-- //
	static int scene;

	/// --メンバ変数END-- ///
	/// --------------- ///
	/// --メンバ関数-- ///
public:
	// --インスタンス取得-- //
	static SceneManager* GetInstance();

	// --デストラクタ-- //
	~SceneManager();

	// --初期化処理-- //
	void Initialize();

	// --更新処理-- //
	void Update();

	// --描画処理-- //
	void Draw();

	// --シーン切り替え-- //
	static void SceneChange(int sceneNum);

private:
	// --コンストラクタ-- //
	SceneManager();

	/// --メンバ関数END-- ///
};