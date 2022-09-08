#pragma once
#include"Util.h"
#include"Camera.h"

class BreakEffect
{
	//メンバ変数
private:
	Circle obj = {};	//オブジェクト

	int color = 0;	//色

	bool isAlive = false;	//生存フラグ

	const int lifeTime = 50;	//寿命

	int deathTimer =0;	//ですタイマー

	float spd = 0;	//エフェクトの進行速度


	float radian = 0;	//エフェクトの進行角度

	//メンバ関数
public:
	BreakEffect();

	~BreakEffect();

	void Update();

	void Draw(Camera camera_);

	void Initialize(Vector2 pos);

	bool GetAllive()const { return isAlive; }
};

