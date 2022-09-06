#pragma once
#include <Math.h>
#include "Vector2.h"

enum class State {
	Normal,
	Reverse,
	Stop
};

struct  Circle
{
	float x;
	float y;
	float radius;
};

struct Line {
	Vector2 start;
	Vector2 end;
	float length;
	float radian;
	int color;
	State state = State::Normal;
};

void DrawCircle(Circle c, int color, bool fillFlag);

void DrawLine(Line l, int thickness = 1);

namespace Util {

	const float PI = 3.141592654f;

	// --ここから自作関数-- //

	/// <summary>
	/// 入れた値が最大値を上回っていたら最大値を返し、最小値を下回っていたら最小値を返す。
	/// どちらにも当てはまらない場合は、値をそのまま返す
	/// </summary>
	/// <param name="value"> 値 </param>
	/// <param name="max"> 最大値 </param>
	/// <param name="min"> 最小値 </param>
	/// <returns></returns>
	int Clamp(int value, int max, int min);

	/// <summary>
	/// 入れた値が最大値を上回っていたら最大値を返し、最小値を下回っていたら最小値を返す。
	/// どちらにも当てはまらない場合は、値をそのまま返す
	/// </summary>
	/// <param name="value"> 値 </param>
	/// <param name="max"> 最大値 </param>
	/// <param name="min"> 最小値 </param>
	/// <returns></returns>
	float Clamp(float value, float max, float min);

	/// <summary>
	/// 弧度法の値を度数法にして返す
	/// </summary>
	/// <param name="radian"> 弧度法の値 </param>
	/// <returns></returns>
	float Radian2Degree(float radian);

	/// <summary>
	/// 度数法の値を弧度法にして返す
	/// </summary>
	/// <param name="degree"> 度数法の値 </param>
	/// <returns></returns>
	float Degree2Radian(float degree);

	/// <summary>
	/// 乱数生成関数
	/// </summary>
	/// <param name="min">最小値</param>
	/// <param name="max">最大値</param>
	/// <returns></returns>
	int Random(int min, int max);

	/// <summary>
	/// 乱数生成関数
	/// </summary>
	/// <param name="min">最小値</param>
	/// <param name="max">最大値</param>
	/// <returns></returns>
	float Random(float min, float max);

} // namespace MathUtility