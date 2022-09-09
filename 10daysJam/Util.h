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

	// --�������玩��֐�-- //

	/// <summary>
	/// ���ꂽ�l���ő�l�������Ă�����ő�l��Ԃ��A�ŏ��l��������Ă�����ŏ��l��Ԃ��B
	/// �ǂ���ɂ����Ă͂܂�Ȃ��ꍇ�́A�l�����̂܂ܕԂ�
	/// </summary>
	/// <param name="value"> �l </param>
	/// <param name="max"> �ő�l </param>
	/// <param name="min"> �ŏ��l </param>
	/// <returns></returns>
	int Clamp(int value, int max, int min);

	/// <summary>
	/// ���ꂽ�l���ő�l�������Ă�����ő�l��Ԃ��A�ŏ��l��������Ă�����ŏ��l��Ԃ��B
	/// �ǂ���ɂ����Ă͂܂�Ȃ��ꍇ�́A�l�����̂܂ܕԂ�
	/// </summary>
	/// <param name="value"> �l </param>
	/// <param name="max"> �ő�l </param>
	/// <param name="min"> �ŏ��l </param>
	/// <returns></returns>
	float Clamp(float value, float max, float min);

	/// <summary>
	/// �ʓx�@�̒l��x���@�ɂ��ĕԂ�
	/// </summary>
	/// <param name="radian"> �ʓx�@�̒l </param>
	/// <returns></returns>
	float Radian2Degree(float radian);

	/// <summary>
	/// �x���@�̒l���ʓx�@�ɂ��ĕԂ�
	/// </summary>
	/// <param name="degree"> �x���@�̒l </param>
	/// <returns></returns>
	float Degree2Radian(float degree);

	/// <summary>
	/// ���������֐�
	/// </summary>
	/// <param name="min">�ŏ��l</param>
	/// <param name="max">�ő�l</param>
	/// <returns></returns>
	int Random(int min, int max);

	/// <summary>
	/// ���������֐�
	/// </summary>
	/// <param name="min">�ŏ��l</param>
	/// <param name="max">�ő�l</param>
	/// <returns></returns>
	float Random(float min, float max);

	/// <summary>
	/// �~�Ɖ~�̏Փ˔���
	/// </summary>
	/// <param name="cA"></param>
	/// <param name="cB"></param>
	/// <returns></returns>
	bool CollisionCtoC(Circle cA, Circle cB);

	/// <summary>
	/// �~�Ɛ��̏Փ˔���
	/// </summary>
	/// <param name="c"></param>
	/// <param name="l"></param>
	bool CollisionCtoL(Circle c, Line l, float lineSpd);


	/// <summary>
	/// 16�i����RGB�ɕύX
	/// </summary>
	Color GetColor16(const char str[]);

} // namespace MathUtility