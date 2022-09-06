#pragma once

class Player {
	/// --メンバ変数-- ///
public:

private:
	// --インスタンス-- //
	static Player* myInstance;

	/// --メンバ変数END-- ///
	/// --------------- ///
	/// --メンバ関数-- ///
public:
	// --インスタンス取得-- //
	static Player* GetInstance();

	// --デストラクタ-- //
	~Player();

	// --初期化処理-- //
	void Initialize();

	// --更新処理-- //
	void Update();

	// --描画処理-- //
	void Draw();

private:
	// --コンストラクタ-- //
	Player();

	/// --メンバ関数END-- ///
};