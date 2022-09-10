#pragma once
#include"Util.h"
#include"Camera.h"

enum class ParticleState {
	Normal,
	Endress
};

class Particle {

private: //メンバ変数
	Circle obj;

	float radian;
	float Spd;
	ParticleState state;
	bool isAcive = false;

	Vector2 parent;	//初期化に使う親座標

public:	//メンバ関数
	
	//更新
	void Update();

	//描画
	void Draw(Camera camera_);

	//初期化
	void Initialize(bool stateReset = false);

	//親座標のセッター
	void SetParent(Vector2 pos);

	void SetState(ParticleState state_);

	ParticleState GetState()const { return state; }

};