#pragma once
#include <vector>
#include "Util.h"

class Enemy {
	/// --メンバ変数-- ///
public:
	// --エネミー-- //
	Circle enemy;

private:

	/// --メンバ変数END-- ///
	/// --------------- ///
	/// --メンバ関数-- ///
public:
	// --コンストラクタ-- //
	Enemy();
	Enemy(Vector2 pos, float radius);

	// --デストラクタ-- //
	~Enemy();

	// --初期化処理-- //
	void Initialize();

	// --更新処理-- //
	void Update();

	// --描画処理-- //
	void Draw();

	//void AllEnemyDeath();

private:

	/// --メンバ関数END-- ///
};