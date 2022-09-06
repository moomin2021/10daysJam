#include "Util.h"
#include "DxLib.h"

void DrawCircle(Circle c, int color, bool fillFlag)
{

	DrawCircle(c.x, c.y, c.radius, color, fillFlag);
}

void DrawLine(Line l, int thickness)
{
	DrawLine(l.start.x, l.start.y, l.end.x, l.end.y, l.color, thickness);
}


int Util::Clamp(int value, int max, int min)
{
	// 値が最大値を上回っていたら最大値を返す
	if (value >= max) return max;

	// 値が最小値を下回っていたら最小値を返す
	if (value <= min) return min;

	// どちらにも当てはまらなかったら値をそのまま返す
	return value;
}

float Util::Clamp(float value, float max, float min)
{
	// 値が最大値を上回っていたら最大値を返す
	if (value >= max) return max;

	// 値が最小値を下回っていたら最小値を返す
	if (value <= min) return min;

	// どちらにも当てはまらなかったら値をそのまま返す
	return value;
}

float Util::Radian2Degree(float radian)
{
	return radian * 180.0f / PI;
}

float Util::Degree2Radian(float degree)
{
	return degree * PI / 180.0f;
}