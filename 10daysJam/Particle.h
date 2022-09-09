#pragma once
#include"Util.h"
#include"Camera.h"

class Particle {

private: //�����o�ϐ�
	Circle obj;

	float radian;
	float Spd;
	bool isAcive = false;

	Vector2 parent;

public:	//�����o�֐�
	
	//�X�V
	void Update();

	//�`��
	void Draw(Camera camera_);

	//������
	void Initialize();

	//�e���W�̃Z�b�^�[
	void SetParent(Vector2 pos);

};