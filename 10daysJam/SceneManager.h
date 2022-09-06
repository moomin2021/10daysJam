#pragma once
#include "DxLib.h"
#include "GameScene.h"

class SceneManager {

	// --シーン番号-- //
	enum SceneNum {
		TITLESCENE,
		GAMESCENE,
		GAMECLEARSCENE,
		GAMEOVERSCENE
	};

	/// --メンバ変数-- ///
public:

private:
	// --インスタンス-- //
	static SceneManager* myInstance;

	// --ゲームシーン-- //
	GameScene* gameScene;

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