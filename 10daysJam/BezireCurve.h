#pragma once
#include"Util.h"

class BezireCurve
{
public:



	Vector2 pos[64]{};			//���ۂɕ`�悷��摜(�����̎n�_)
	Vector2 controll[4]{};	//	����_�̍��W
	int divisionNum;
	bool isActive;

public:
	BezireCurve();
	~BezireCurve();
	/// <summary>
	/// �X�V����
	/// </summary>
	void Update();
	/// <summary>
	/// ����_�̔z�u
	/// </summary>
	void SetControllPoint(Vector2 pos, int point);


	/// <summary>
	/// �`��
	/// </summary>
	void Draw(int color);

};