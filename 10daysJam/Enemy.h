#pragma once
#include <vector>
#include "Util.h"
#include "Camera.h"
#include"BezireCurve.h"

class Enemy {
	/// --メンバ変数-- ///
public:
	// --エネミー-- //
	Circle obj;


private:

	//ステート
	State state = State::Normal;

	int color;

	bool isChange = false;	//ステートの変更が行われたか

	BezireCurve bezire;
	int effectTime = 0;

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
	
	//死亡状態の更新処理
	void UpdateDeath(Vector2 afterPos,float randParam);

	//衝突検知管数
	void OnCollison();

	// --描画処理-- //
	void Draw(Camera camera_);

	Circle GetCircle() const { return obj; }

	void SetState(State state_);

	State GetState()const { return state; }

	bool GetIsChange()const { return isChange;}

	void StateChange();

	//void AllEnemyDeath();

private:

	/// --メンバ関数END-- ///
};