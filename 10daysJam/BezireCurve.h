#pragma once
#include"Util.h"

class BezireCurve
{
public:



	Vector2 pos[64]{};			//実際に描画する画像(線分の始点)
	Vector2 controll[4]{};	//	制御点の座標
	int divisionNum;
	bool isActive;

public:
	BezireCurve();
	~BezireCurve();
	/// <summary>
	/// 更新処理
	/// </summary>
	void Update();
	/// <summary>
	/// 制御点の配置
	/// </summary>
	void SetControllPoint(Vector2 pos, int point);


	/// <summary>
	/// 描画
	/// </summary>
	void Draw(int color);

};