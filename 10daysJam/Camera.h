#pragma once
#include"Util.h"

class Camera
{
private:
	//メンバ変数
	Vector2 pos;

public:
//メンバ関数
	Vector2 GetPos()const { return pos; }

	/// <summary>
	/// コンストラクタ
	/// </summary>
	/// <returns></returns>
	Camera();


};

