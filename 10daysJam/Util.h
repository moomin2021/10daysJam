#pragma once
#include <Math.h>
#include "Vector2.h"
#include<stdint.h>

enum class State {
	Normal,
	Reverse,
	Stop,
	Item,
	Enemy,
	Death,
};

struct Circle
{
	Vector2 pos;
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

typedef struct Color
{
	uint8_t red;
	uint8_t green;
	uint8_t blue;
}Color;

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

	/// <summary>
	/// 円と円の衝突判定
	/// </summary>
	/// <param name="cA"></param>
	/// <param name="cB"></param>
	/// <returns></returns>
	bool CollisionCtoC(Circle cA, Circle cB);

	/// <summary>
	/// 円と線の衝突判定
	/// </summary>
	/// <param name="c"></param>
	/// <param name="l"></param>
	bool CollisionCtoL(Circle c, Line l, float lineSpd);


	/// <summary>
	/// 16進数をRGBに変更
	/// </summary>
	Color GetColor16(const char str[]);

} // namespace MathUtility