#pragma once
#include <vector>
#include "Util.h"
#include "Camera.h"
#include"BezireCurve.h"
#include"Particle.h"



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

	std::vector<Particle> spawnEffect;
	float spawnAddRadius;

	// --画像ハンドル-- //
	int handle[2];

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
	void Draw(Camera camera_,int graph);

	// --描画で使う画像ハンドルを設定-- //
	void SetHandle(int handle[]);

	//自機の円のセッター
	Circle GetCircle() const { return obj; }

	//ステートのセッター
	void SetState(State state_);

	//ステートのゲッター
	State GetState()const { return state; }

	//敵のステート変更フラグのゲッター
	bool GetIsChange()const { return isChange;}

	//ステートチェンジが行われたときに行うコールバック関数
	void StateChange();

	//スポーンした時のエフェクト
	void EffectInitialize(int color);

	//オブジェクトの情報のセッター
	void SetObj(Circle obj_);

	//エネミーが死亡したときに呼ばれるコールバック関数
	void Death();


	//void AllEnemyDeath();

private:

	/// --メンバ関数END-- ///
};