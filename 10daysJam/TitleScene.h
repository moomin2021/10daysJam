#pragma once

class TitleScene {
	/// --メンバ変数-- ///
public:

private:
	// --インスタンス-- //
	static TitleScene* myInstance;

	/// --メンバ変数END-- ///
	/// --------------- ///
	/// --メンバ関数-- ///
public:
	// --インスタンス取得-- //
	static TitleScene* GetInstance();

	// --デストラクタ-- //
	~TitleScene();

	// --初期化処理-- //
	void Initialize();

	// --更新処理-- //
	void Update();

	// --描画処理-- //
	void Draw();

private:
	// --コンストラクタ-- //
	TitleScene();

	/// --メンバ関数END-- ///
};