#pragma once
#include"Util.h"

class Camera
{
private:
	//メンバ変数
	Vector2 pos;

	int shakeCount;

public:
//メンバ関数
	Vector2 GetPos()const { return pos; }

	void SetShakeCount(int shakeCount_);

	/// <summary>
	/// コンストラクタ
	/// </summary>
	/// <returns></returns>
	Camera();

	void CameraShake();

	void CameraReset();
};

