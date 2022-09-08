#pragma once
#include"Util.h"
#include"Camera.h"

class BreakEffect
{
	//�����o�ϐ�
private:
	Circle obj = {};	//�I�u�W�F�N�g

	int color = 0;	//�F

	bool isAlive = false;	//�����t���O

	const int lifeTime = 50;	//����

	int deathTimer =0;	//�ł��^�C�}�[

	float spd = 0;	//�G�t�F�N�g�̐i�s���x


	float radian = 0;	//�G�t�F�N�g�̐i�s�p�x

	//�����o�֐�
public:
	BreakEffect();

	~BreakEffect();

	void Update();

	void Draw(Camera camera_);

	void Initialize(Vector2 pos);

	bool GetAllive()const { return isAlive; }
};

