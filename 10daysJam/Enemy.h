#pragma once
#include <vector>
#include "Util.h"
#include "Camera.h"

class Enemy {
	/// --メンバ変数-- ///
public:
	// --エネミー-- //
	Circle enemy;


private:

	//ステート
	State state = State::Normal;

	int color = 0xffff00;

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
	void Update(Line hourLine_);

	//通常状態の更新処理
	void UpdateNormal();

	//反転状態の更新処理
	void UpdateReverse(Line hourLine_);

	//衝突検知管数
	void OnCollison();

	// --描画処理-- //
	void Draw(Camera camera_);

	Circle GetCircle() const { return enemy; }

	//void AllEnemyDeath();

private:

	/// --メンバ関数END-- ///
};