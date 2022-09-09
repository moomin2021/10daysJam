#pragma once
#include"Util.h"
#include"Camera.h"

class Particle {

private: //メンバ変数
	Circle obj;

	float radian;
	float Spd;
	bool isAcive = false;

	Vector2 parent;

public:	//メンバ関数
	
	//更新
	void Update();

	//描画
	void Draw(Camera camera_);

	//初期化
	void Initialize();

	//親座標のセッター
	void SetParent(Vector2 pos);

};