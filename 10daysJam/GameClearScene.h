#pragma once

class GameClearScene {
	/// --メンバ変数-- ///
public:

private:
	// --インスタンス-- //
	static GameClearScene* myInstance;

	/// --メンバ変数END-- ///
	/// --------------- ///
	/// --メンバ関数-- ///
public:
	// --インスタンス取得-- //
	static GameClearScene* GetInstance();

	// --デストラクタ-- //
	~GameClearScene();

	// --初期化処理-- //
	void Initialize();

	// --更新処理-- //
	void Update();

	// --描画処理-- //
	void Draw();

private:
	// --コンストラクタ-- //
	GameClearScene();

	/// --メンバ関数END-- ///
};