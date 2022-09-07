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
	// �l���ő�l�������Ă�����ő�l��Ԃ�
	if (value >= max) return max;

	// �l���ŏ��l��������Ă�����ŏ��l��Ԃ�
	if (value <= min) return min;

	// �ǂ���ɂ����Ă͂܂�Ȃ�������l�����̂܂ܕԂ�
	return value;
}

float Util::Clamp(float value, float max, float min)
{
	// �l���ő�l�������Ă�����ő�l��Ԃ�
	if (value >= max) return max;

	// �l���ŏ��l��������Ă�����ŏ��l��Ԃ�
	if (value <= min) return min;

	// �ǂ���ɂ����Ă͂܂�Ȃ�������l�����̂܂ܕԂ�
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
	//����
	random_device seed_gem;
	//�߂邹��ʂ�����
	mt19937_64 engine(seed_gem());
	//�����͈�
	uniform_real_distribution<float> rand(min, max);

	return rand(engine);
}

float Util::Random(float min, float max)
{
	//����
	random_device seed_gem;
	//�߂邹��ʂ�����
	mt19937_64 engine(seed_gem());
	//�����͈�
	uniform_real_distribution<float> rand(min, max);

	return rand(engine);
}
