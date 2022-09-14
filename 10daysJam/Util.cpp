#include "Util.h"
#include "DxLib.h"
#include<random>
using namespace std;

void DrawCircle(Circle c, int color, bool fillFlag)
{

	DrawCircle(c.pos.x, c.pos.y, c.radius, color, fillFlag);
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

int Util::Random(int min, int max)
{
	int min_, max_;
	if (min < max) {
		max_ = max;
		min_ = min;
	}
	else {
		max_ = min;
		min_ = max;
	}

	//乱数
	random_device seed_gem;
	//めるせんぬついすた
	mt19937_64 engine(seed_gem());
	//乱数範囲
	uniform_real_distribution<float> rand(min_, max_);
	return rand(engine);
}

float Util::Random(float min, float max)
{
	float min_, max_;
	if (min < max) {
		max_ = max;
		min_ = min;
	}
	else {
		max_ = min;
		min_ = max;
	}

	//乱数
	random_device seed_gem;
	//めるせんぬついすた
	mt19937_64 engine(seed_gem());
	//乱数範囲
	uniform_real_distribution<float> rand(min_, max_);

	return rand(engine);
}

bool Util::CollisionCtoC(Circle cA, Circle cB)
{
	bool flag;
	Vector2 vecAtoB;
	float radius;
	vecAtoB.x = cB.pos.x - cA.pos.x;
	vecAtoB.y = cB.pos.y - cA.pos.y;
	radius = cA.radius + cB.radius;

	if (vecAtoB.length() <= radius) {
		flag = true;
	}
	else {
		flag = false;
	}

	return flag;
}

bool Util::CollisionCtoL(Circle c, Line l, float lineSpd)
{
	//必要変数宣言
	Vector2 vecLine, vecCircle, vecCircle2, vecN, vecNtoC;
	float len;
	float rad = l.radian - 90;

	if (lineSpd <= 1)lineSpd = 1;

	for (int i = 0; i < (int)lineSpd; i++) {
		//線の終点座標を変更

		l.end.x = (l.length * cosf((rad) / 180 * PI)) + l.start.x;
		l.end.y = (l.length * sinf((rad) / 180 * PI)) + l.start.y;

		//線のベクトルを取得
		vecLine = l.end - l.start;
		//正規化
		vecLine = vecLine.normalize();
		vecCircle = c.pos - l.start;
		vecCircle2 = c.pos - l.end;
		len = vecLine.dot(vecCircle);
		vecN = vecLine * len;
		vecNtoC = vecCircle - vecN;

		if (fabs(vecNtoC.length()) < c.radius) {
			if (vecLine.dot(vecCircle) * vecLine.dot(vecCircle2) <= 0.0f) {
				return true;
			}
			else if (fabs(vecCircle.length()) < c.radius || fabs(vecCircle2.length()) < c.radius) {

				return true;
			}
		}
		else rad--;
	}
	return false;
}

Color Util::GetColor16(const char str[])
{
	uint32_t rgb = (uint32_t)strtol((const char*)&str[0], NULL, 16);

	Color color;

	color.red = (rgb >> 16);
	color.green = (rgb >> 8);
	color.blue = (rgb >> 0);

	return color;
}

Color Util::HexadecimalColor(int color_) {

	Color c;
	c.red = (color_ >> 16);
	c.blue = (color_ >> 0) ;
	c.green = (color_ >> 8);

	return c;
}

int Util::ColorHexadecimal(Color color_)
{
	int a;
	a = color_.red * pow(16, 4) + color_.green * pow(16, 2) + color_.blue;
	return a;
}

void Util::SetDrawBright2(int color)
{
	Color c = HexadecimalColor(color);
	SetDrawBright(c.red, c.green,c.blue);
}
