#pragma once

class Enemy {
	/// --メンバ変数-- ///
public:

private:
	// --インスタンス-- //
	static Enemy* myInstance;

	/// --メンバ変数END-- ///
	/// --------------- ///
	/// --メンバ関数-- ///
public:
	// --インスタンス取得-- //
	static Enemy* GetInstance();

	// --デストラクタ-- //
	~Enemy();

	// --初期化処理-- //
	void Initialize();

	// --更新処理-- //
	void Update();

	// --描画処理-- //
	void Draw();

private:
	// --コンストラクタ-- //
	Enemy();

	/// --メンバ関数END-- ///
};